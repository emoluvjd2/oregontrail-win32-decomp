"""Check that the score callback's out-of-envelope command table is verified.

Requires the local public candidate build, both proof inputs, and pefile.
The altered table entries leave every byte of the function body unchanged.
"""
import importlib.util
from pathlib import Path
import shutil
import struct
import tempfile
import unittest

import pefile

ROOT = Path(__file__).resolve().parents[2]
BUILD = ROOT / 'artifacts/otmatch/public-diagnostic'
SPEC = importlib.util.spec_from_file_location(
    'operand_verifier', Path(__file__).with_name('verify-main-window-operands.py'))
VERIFIER = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VERIFIER)


class ScoreCommandEvidenceTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(
            prefix='score-evidence-', dir=ROOT / 'artifacts')
        self.addCleanup(self.temporary.cleanup)
        self.directory = Path(self.temporary.name)
        for name in ['otwin-match-candidates.dll', 'otwin-match-candidates.map']:
            shutil.copy2(BUILD / name, self.directory / name)
        self.image = self.directory / 'otwin-match-candidates.dll'
        lines = (self.directory / 'otwin-match-candidates.map').read_text().splitlines()
        self.callback = next(int(parts[2], 16) for line in lines
                             if len(parts := line.split()) >= 3
                             and parts[1] == '_OtTrailGameShutdownDialogProc_00430350_Product@16')

    def verify(self):
        return VERIFIER.verify(self.directory, 'FUN_00430350_00030350',
                               'score-list-callback-operands.csv')

    def replace_table_entry(self, index, target):
        with pefile.PE(str(self.image)) as pe:
            offset = pe.get_offset_from_rva(
                self.callback + 0x1ec + index * 4 - pe.OPTIONAL_HEADER.ImageBase)
        data = bytearray(self.image.read_bytes())
        data[offset:offset + 4] = struct.pack('<I', target)
        self.image.write_bytes(data)

    def test_original_table_passes(self):
        self.assertEqual(self.verify()['status'], 'pass')

    def test_save_redirected_to_cancel_fails(self):
        self.replace_table_entry(0, self.callback + 0xf7)
        with self.assertRaisesRegex(ValueError, 'command table targets differ'):
            self.verify()

    def test_default_redirected_to_delete_fails(self):
        self.replace_table_entry(2, self.callback + 0x167)
        with self.assertRaisesRegex(ValueError, 'command table targets differ'):
            self.verify()


if __name__ == '__main__':
    unittest.main()
