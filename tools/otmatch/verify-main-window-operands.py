"""Check reviewed relocated operands for recovered product functions.

Run alongside match-functions.ps1: this checks the identities and string contents
that a normalized byte match alone cannot establish. Requires pefile.
"""
import argparse
import csv
import hashlib
import json
from pathlib import Path
import re
import struct

import pefile

ROOT = Path(__file__).resolve().parents[2]


def require(condition, message):
    if not condition:
        raise ValueError(message)


def imports(pe):
    return {entry.address: descriptor.dll.decode().lower() + '!' +
            (entry.name.decode() if entry.name else '#' + str(entry.ordinal))
            for descriptor in pe.DIRECTORY_ENTRY_IMPORT for entry in descriptor.imports}


def verify(directory, function='FUN_004035b0_000035b0', proof_name='main-window-creation-operands.csv'):
    original_path = ROOT / 'Sample/Oregon Trail CD/OTWIN32/Oregon32.exe'
    candidate_path = directory / 'otwin-match-candidates.dll'
    map_path = directory / 'otwin-match-candidates.map'
    # Parsing bytes avoids retaining Windows file mappings when a failed
    # evidence check raises, including the deliberately corrupted test cases.
    original = pefile.PE(data=original_path.read_bytes())
    candidate = pefile.PE(data=candidate_path.read_bytes())
    manifest_path = ROOT / 'tools/otmatch/functions.vc40-real-cpp.csv'
    with manifest_path.open(newline='') as stream:
        manifest = list(csv.DictReader(stream))
    row = next(r for r in manifest if r['name'] == function)
    symbols = {}
    for line in map_path.read_text().splitlines():
        parts = line.split()
        if len(parts) >= 3 and re.fullmatch(r'[0-9a-fA-F]{4}:[0-9a-fA-F]{8}', parts[0]) and re.fullmatch(r'[0-9a-fA-F]{8}', parts[2]):
            symbols.setdefault(parts[1], []).append(int(parts[2], 16))

    def symbol(name):
        addresses = symbols.get(name, [])
        require(len(addresses) == 1, 'Missing or ambiguous map symbol: ' + name)
        return addresses[0]

    original_va = int(row['original_va'], 0)
    candidate_va = symbol(row['candidate_symbol'])
    left_imports, right_imports = imports(original), imports(candidate)
    proof_path = ROOT / 'tools/otmatch/evidence' / proof_name
    with proof_path.open(newline='') as stream:
        proof = list(csv.DictReader(stream))
    masks = ' '.join(f"{r['offset']}-{int(r['offset']) + 3}" for r in proof)
    require(row['mask'] == masks, 'Manifest masks differ from the reviewed operand table')
    evidence = []
    for field in proof:
        offset, kind = int(field['offset']), field['kind']
        targets = []
        for pe, va in [(original, original_va), (candidate, candidate_va)]:
            rva = va - pe.OPTIONAL_HEADER.ImageBase
            raw = pe.get_data(rva + offset, 4)
            require(len(raw) == 4, 'Operand outside image')
            if kind in {'call', 'allocator-call', 'jump', 'wip-call', 'bitmap-call', 'bitmap-jump'}:
                opcode = b'\xe9' if kind in {'jump', 'bitmap-jump'} else b'\xe8'
                require(pe.get_data(rva + offset - 1, 1) == opcode, 'Expected rel32 branch')
                targets.append(va + offset + 4 + struct.unpack('<i', raw)[0])
            else:
                require(any(e.type == 3 and e.rva == rva + offset
                            for block in pe.DIRECTORY_ENTRY_BASERELOC for e in block.entries),
                        'Address operand lacks a HIGHLOW relocation')
                targets.append(struct.unpack('<I', raw)[0])
        left, right = targets
        require(left == int(field['original_target'], 0), f'Unexpected original target at {offset}')
        identity = field['candidate_identity']
        if kind == 'owner-eh':
            size = int(row['size'], 0)
            require(left == original_va + size and right == candidate_va + size,
                    'Unexpected bitmap-owner exception-handler position')
            metadata = []
            cleanups = []
            for pe, base, handler in [(original, original_va, left), (candidate, candidate_va, right)]:
                image_base = pe.OPTIONAL_HEADER.ImageBase
                code = pe.get_data(handler - image_base, 10)
                require(code[0] == 0xb8 and code[5] == 0xe9, 'Unexpected owner EH handler')
                target = handler + 10 + struct.unpack('<i', code[6:])[0]
                require(target == (0x430810 if pe is original else symbol('___CxxFrameHandler')),
                        'Wrong owner C++ frame handler')
                descriptor = struct.unpack('<I', code[1:5])[0]
                info = struct.unpack('<8I', pe.get_data(descriptor - image_base, 32))
                require(info[0] == 0x19930520 and 0 < info[1] <= 64 and info[3:] == (0, 0, 0, 0, 0),
                        'Unexpected owner EH metadata')
                entries = list(struct.iter_unpack('<2I', pe.get_data(info[2] - image_base, info[1] * 8)))
                require(all(base <= address < base + size or address == base + size + 10
                            for _, address in entries), 'Unwind action outside verified code')
                metadata.append([(state, address - base) for state, address in entries])
                cleanup = bytearray(pe.get_data(handler + 10 - image_base, 13))
                require(cleanup[4] == 0xe8 and cleanup[-1] == 0xc3, 'Unexpected owner delete cleanup')
                target = handler + 19 + struct.unpack('<i', cleanup[5:9])[0]
                require(target == (0x430730 if pe is original else symbol('??3@YAXPAX@Z')),
                        'Wrong owner allocation deallocator')
                cleanup[5:9] = bytes(4)
                cleanups.append(cleanup)
            require(metadata[0] == metadata[1] and cleanups[0] == cleanups[1],
                    'Owner unwind metadata or final cleanup differs')
        elif kind == 'score-command-table':
            # The five command targets follow the function envelope. Verify
            # each entry; masking the table's address alone is insufficient.
            expected_offsets = (0xb8, 0xf7, 0xa9, 0x118, 0x167)
            for pe, base, table in [(original, original_va, left), (candidate, candidate_va, right)]:
                require(table == base + 0x1ec, 'Unexpected score command table position')
                table_rva = table - pe.OPTIONAL_HEADER.ImageBase
                targets = struct.unpack('<5I', pe.get_data(table_rva, 20))
                require(tuple(target - base for target in targets) == expected_offsets,
                        'Score command table targets differ')
                relocations = {entry.rva for block in pe.DIRECTORY_ENTRY_BASERELOC
                               for entry in block.entries if entry.type == 3}
                require(all(table_rva + i * 4 in relocations for i in range(5)),
                        'Score command table entry lacks a HIGHLOW relocation')
        elif kind == 'status-eh':
            require(left == original_va + 0x11f and right == candidate_va + 0x11f,
                    'Unexpected status callback exception-handler position')
        elif kind == 'status-eh-data':
            # Both cleanup funclets and the frame-handler jump are within the
            # strictly compared callback envelope; their call identities are
            # separate reviewed rows. Verify the complete two-state unwind map.
            for pe, base, descriptor in [(original, original_va, left), (candidate, candidate_va, right)]:
                image_base = pe.OPTIONAL_HEADER.ImageBase
                info = struct.unpack('<8I', pe.get_data(descriptor - image_base, 32))
                require(info[:2] == (0x19930520, 2) and info[3:] == (0, 0, 0, 0, 0),
                        'Unexpected status owner exception metadata')
                unwind = struct.unpack('<4I', pe.get_data(info[2] - image_base, 16))
                require(unwind == (0xffffffff, base + 0x129, 0, base + 0x114),
                        'Unexpected status owner destruction unwind actions')
        elif kind == 'composite-eh':
            require(left == original_va + 287 and right == candidate_va + 287,
                    'Unexpected composite exception-handler position')
        elif kind == 'composite-eh-data':
            for pe, base, descriptor in [(original, original_va, left), (candidate, candidate_va, right)]:
                image_base = pe.OPTIONAL_HEADER.ImageBase
                info = struct.unpack('<8I', pe.get_data(descriptor - image_base, 32))
                require(info[:2] == (0x19930520, 1) and info[3:] == (0, 0, 0, 0, 0),
                        'Unexpected composite exception metadata')
                unwind = struct.unpack('<2I', pe.get_data(info[2] - image_base, 8))
                require(unwind == (0xffffffff, base + 297), 'Unexpected bitmap allocation cleanup')
        elif kind == 'journey-eh':
            require(left == original_va + 302 and right == candidate_va + 302,
                    'Unexpected journey exception-handler position')
            descriptions = []
            for pe, base, handler in [(original, original_va, left), (candidate, candidate_va, right)]:
                image_base = pe.OPTIONAL_HEADER.ImageBase
                code = pe.get_data(handler - image_base, 10)
                require(code[0] == 0xb8 and code[5] == 0xe9, 'Unexpected EH handler code')
                descriptor = struct.unpack('<I', code[1:5])[0]
                frame_handler = handler + 10 + struct.unpack('<i', code[6:10])[0]
                expected_handler = 0x430810 if pe is original else symbol('___CxxFrameHandler')
                require(frame_handler == expected_handler, 'Wrong C++ frame handler')
                info = struct.unpack('<8I', pe.get_data(descriptor - image_base, 32))
                require(info[:2] == (0x19930520, 2) and info[3:] == (0, 0, 0, 0, 0),
                        'Unexpected C++ exception metadata')
                unwind = struct.unpack('<4I', pe.get_data(info[2] - image_base, 16))
                require(unwind == (0xffffffff, base + 161, 0xffffffff, base + 312),
                        'Unexpected constructor unwind actions')
                cleanup = bytearray(pe.get_data(base + 312 - image_base, 13))
                require(cleanup[:5] == bytes.fromhex('8b45f050e8'), 'Wrong allocation cleanup')
                target = base + 321 + struct.unpack('<i', cleanup[5:9])[0]
                require(target == (0x430730 if pe is original else symbol('??3@YAXPAX@Z')),
                        'Constructor cleanup does not call operator delete')
                cleanup[5:9] = bytes(4)
                descriptions.append(cleanup)
            require(descriptions[0] == descriptions[1], 'Constructor cleanup bodies differ')
        elif kind == 'import':
            require(left_imports.get(left) == right_imports.get(right), f'Import mismatch at {offset}')
            require(left_imports.get(left) == identity.split('!')[0].lower() + '!' + identity.split('!')[1],
                    f'Unexpected import at {offset}')
        else:
            require(right == symbol(identity), f'Wrong candidate target at {offset}: {identity}')
            if kind == 'string':
                a = original.get_string_at_rva(left - original.OPTIONAL_HEADER.ImageBase)
                b = candidate.get_string_at_rva(right - candidate.OPTIONAL_HEADER.ImageBase)
                require(a == b, f'String mismatch at {offset}: {a!r} != {b!r}')
            elif kind == 'allocator-call':
                normalized = []
                for pe, target in [(original, left), (candidate, right)]:
                    body = bytearray(pe.get_data(target - pe.OPTIONAL_HEADER.ImageBase, 16))
                    require(body[:8] == bytes.fromhex('8b4424046a0150e8'), 'Unexpected operator new body')
                    allocator = target + 12 + struct.unpack('<i', body[8:12])[0]
                    expected = 0x431f00 if pe is original else symbol('__nh_malloc')
                    require(allocator == expected, 'Wrong operator new allocator')
                    body[8:12] = bytes(4)
                    normalized.append(body)
                require(normalized[0] == normalized[1], 'Operator new differs from original')
            elif kind in {'bitmap-call', 'bitmap-jump'}:
                # Existing Product lifecycle implementations have the same field and
                # ownership semantics, but are not claimed as byte-identical aliases.
                lifecycle = {
                    0x40b720: '??0PositionedBitmapDescriptorState_0040ba40@@QAE@XZ',
                    0x40b760: '??1PositionedBitmapDescriptorState_0040ba40@@QAE@XZ',
                }
                require(lifecycle.get(left) == identity, 'Wrong bitmap lifecycle dependency')
            elif kind == 'wip-call':
                require(any(int(r['original_va'], 0) == left and r['candidate_symbol'] == identity
                            and r['expected_status'] == 'wip' for r in manifest),
                        f'Call does not identify the documented WIP dependency: {identity}')
            elif kind in {'call', 'jump'}:
                require(any(int(r['original_va'], 0) == left and r['candidate_symbol'] == identity
                            and r['expected_status'] == 'match' for r in manifest),
                        f'Call target is not an accepted manifest mapping: {identity}')
        evidence.append(dict(offset=offset, kind=kind, original_target=hex(left),
                             candidate_target=hex(right), identity=identity, status='pass'))
    return dict(status='pass', operands=evidence, sha256={str(p.relative_to(ROOT)):
        hashlib.sha256(p.read_bytes()).hexdigest() for p in
        [original_path, candidate_path, map_path, manifest_path, proof_path]})


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--directory', type=Path, default=ROOT / 'artifacts/otmatch/public-diagnostic')
    parser.add_argument('--output', type=Path)
    parser.add_argument('--function', default='FUN_004035b0_000035b0')
    parser.add_argument('--proof', default='main-window-creation-operands.csv')
    args = parser.parse_args()
    result = verify(args.directory.resolve(), args.function, args.proof)
    output = args.output or args.directory / 'main-window-operands.json'
    output.write_text(json.dumps(result, indent=2))
    print(f"PASS: {len(result['operands'])} operand identities and associated string/EH checks.")
