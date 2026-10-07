"""Compile a focused VC4 candidate and inspect it without awarding progress.

Requires pefile and capstone in the invoking Python environment. The existing
PowerShell matcher remains verification authority; use --verify for that check.
"""
import argparse
import csv
import os
from pathlib import Path
import re
import subprocess
import shutil
import json

import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('name')
    parser.add_argument('sources', nargs='+')
    parser.add_argument('--symbol')
    parser.add_argument('--flag', action='append', default=[])
    parser.add_argument('--disasm', action='store_true')
    parser.add_argument('--verify', action='store_true')
    parser.add_argument('--out', default='artifacts/otmatch/local-probe')
    parser.add_argument('--base-objects', help='Strictly link other real objects from this build directory')
    parser.add_argument('--replace-object', action='append', default=[], help='Object basename replaced by a trial source')
    args = parser.parse_args()
    os.chdir(ROOT)
    out = (ROOT / args.out).resolve()
    out.mkdir(parents=True, exist_ok=True)
    vc = ROOT / 'toolchain/MSDEV'
    env = dict(os.environ, PATH=str(vc / 'BIN') + os.pathsep + os.environ['PATH'],
               INCLUDE=str(vc / 'INCLUDE'), LIB=str(vc / 'LIB'))
    objects = []
    for source in args.sources:
        obj = out / (re.sub(r'[^a-zA-Z0-9_]', '_', str(Path(source).with_suffix(''))) + '.obj')
        command = [str(vc / 'BIN/CL.EXE'), '/nologo', '/c', '/Gd', '/Zl', '/O1',
                   *args.flag, '/Fo' + str(obj), source]
        result = subprocess.run(command, env=env, capture_output=True, text=True)
        if result.returncode:
            raise SystemExit(result.stdout + result.stderr)
        objects.append(str(obj))
    if args.base_objects:
        excluded = {Path(p).name.lower() for p in objects} | {p.lower() for p in args.replace_object}
        objects += [str(p.resolve()) for p in Path(args.base_objects).glob('*.obj')
                    if p.name.lower() not in excluded and p.name.lower() not in
                    {'match_dll_anchors_lcmt.obj', 'match_dll_anchors_dllcrt.obj'}]
    # VC4's export-library subprocess cannot handle modern, long absolute
    # paths for hundreds of objects. Stage real inputs and link by basename.
    for obj in objects:
        destination = out / Path(obj).name
        if Path(obj).resolve() != destination:
            shutil.copy2(obj, destination)
    objects = [Path(obj).name for obj in objects]
    dll = out / 'candidate.dll'
    mapfile = out / 'candidate.map'
    link_args = ['/nologo', '/dll', '/noentry',
        '/incremental:no', '/opt:noref', '/debug', '/pdb:candidate.pdb', '/out:candidate.dll',
        '/map:candidate.map', *objects, 'libc.lib', 'kernel32.lib', 'user32.lib',
        'gdi32.lib', 'winmm.lib', 'comdlg32.lib']
    if args.base_objects:
        link_args.insert(0, '/INCLUDE:_WinMainCRTStartup')
    response = out / 'link.rsp'
    response.write_text('\n'.join('"' + arg + '"' for arg in link_args))
    result = subprocess.run([str(vc / 'BIN/LINK.EXE'), *link_args], cwd=out, env=env, capture_output=True, text=True)
    if result.returncode:
        raise SystemExit(result.stdout + result.stderr)
    with (ROOT / 'tools/otmatch/functions.vc40-real-cpp.csv').open(newline='') as f:
        rows = [row for row in csv.DictReader(f) if row['name'] == args.name]
    if len(rows) != 1:
        raise SystemExit('Expected exactly one manifest row for ' + args.name)
    row = rows[0]
    if args.symbol:
        row['candidate_symbol'] = args.symbol
    symbols = []
    for line in mapfile.read_text().splitlines():
        parts = line.split()
        if len(parts) >= 3 and parts[1] == row['candidate_symbol']:
            symbols.append(int(parts[2], 16))
    if len(symbols) != 1:
        raise SystemExit('Candidate symbol missing or ambiguous: ' + row['candidate_symbol'])
    original = ROOT / 'Sample/Oregon Trail CD/OTWIN32' / row['program']
    target_pe, candidate_pe = pefile.PE(str(original)), pefile.PE(str(dll))
    size = int(row['size'], 0)
    target_va = int(row['original_va'], 0)
    target = target_pe.get_data(target_va - target_pe.OPTIONAL_HEADER.ImageBase, size)
    candidate = candidate_pe.get_data(symbols[0] - candidate_pe.OPTIONAL_HEADER.ImageBase, size)
    masked = set()
    for token in re.split(r'[\s,;]+', row['mask'].strip()):
        if not token:
            continue
        ends = [int(v, 0) for v in token.split('-')]
        masked.update(range(ends[0], ends[-1] + 1))
    diff = [i for i in range(size) if i not in masked and target[i] != candidate[i]]
    print(f'{args.name}: {len(diff)}/{size-len(masked)} unmasked byte differences (diagnostic only)')
    print('Difference offsets:', diff[:100])
    # An additional diagnostic exposes instruction differences separately
    # from relocated operands. Never use this heuristic as match authority.
    original_rva = target_va - target_pe.OPTIONAL_HEADER.ImageBase
    candidate_rva = symbols[0] - candidate_pe.OPTIONAL_HEADER.ImageBase
    relocations = lambda p: {e.rva for block in getattr(p, 'DIRECTORY_ENTRY_BASERELOC', [])
                             for e in block.entries if e.type == 3}
    original_relocs, candidate_relocs = relocations(target_pe), relocations(candidate_pe)
    fields = {i for i in range(size - 3) if original_rva+i in original_relocs and candidate_rva+i in candidate_relocs}
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    left = {i.address: i for i in decoder.disasm(target, 0)}
    right = {i.address: i for i in decoder.disasm(candidate, 0)}
    for offset, ins in left.items():
        other = right.get(offset)
        if (other and ins.mnemonic == other.mnemonic and ins.size == other.size
                and ins.mnemonic in {'call', 'jmp'} and ins.imm_size == other.imm_size == 4
                and ins.imm_offset == other.imm_offset):
            fields.add(offset + ins.imm_offset)
    relocated = {i for field in fields for i in range(field, field+4)}
    shape_diff = [i for i in range(size) if i not in relocated and target[i] != candidate[i]]
    print(f'Relocation-normalized diagnostic: {len(shape_diff)} differences at {shape_diff[:50]}')
    (out / 'diagnostic.json').write_text(json.dumps(dict(name=args.name, symbol=row['candidate_symbol'],
        manifest_differences=diff, shape_differences=shape_diff, operand_fields=sorted(fields)), indent=2))
    (out / 'original.bin').write_bytes(target)
    (out / 'candidate.bin').write_bytes(candidate)
    if args.disasm:
        decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        for title, body, base in [('Original', target, target_va), ('Candidate', candidate, symbols[0])]:
            print('\n' + title)
            for ins in decoder.disasm(body, base):
                print(f'{ins.address-base:03x} {ins.mnemonic:8} {ins.op_str}')
    # The probe builds one fixture; preserve masks and policy metadata while
    # clearing obsolete layout anchors and the canonical object qualifier.
    row.update(candidate_dll='', candidate_object='', candidate_rva='', candidate_va='')
    manifest = out / 'functions.csv'
    with manifest.open('w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=list(row))
        writer.writeheader()
        writer.writerow(row)
    if args.verify:
        subprocess.run(['powershell', '-NoProfile', '-ExecutionPolicy', 'Bypass', '-File',
            str(ROOT / 'tools/otmatch/match-functions.ps1'), '-ManifestPath', str(manifest),
            '-OriginalPath', str(original), '-CandidatePath', str(dll),
            '-CandidateMapPath', str(mapfile), '-ResultsCsvPath', str(out / 'results.csv'),
            '-SummaryOnly', '-AllowMismatches'], check=True)


if __name__ == '__main__':
    main()
