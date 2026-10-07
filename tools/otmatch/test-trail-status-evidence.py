"""Reject status-panel operand mistakes that relocation masks cannot detect.

Requires the local public candidate build, the original game, and pefile.
Fixtures change only masked address operands or referenced string data.
"""
import importlib.util
from pathlib import Path
import re
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


class TrailStatusEvidenceTests(unittest.TestCase):
    def setUp(self):
        temporary = tempfile.TemporaryDirectory(
            prefix='status-evidence-', dir=ROOT / 'artifacts')
        self.addCleanup(temporary.cleanup)
        self.directory = Path(temporary.name)
        for name in ['otwin-match-candidates.dll', 'otwin-match-candidates.map']:
            shutil.copy2(BUILD / name, self.directory / name)
        self.image = self.directory / 'otwin-match-candidates.dll'
        self.symbols = {}
        for line in (self.directory / 'otwin-match-candidates.map').read_text().splitlines():
            parts = line.split()
            if (len(parts) >= 3 and ':' in parts[0]
                    and re.fullmatch(r'[0-9a-fA-F]{8}', parts[2])):
                self.symbols[parts[1]] = int(parts[2], 16)
        self.panel = self.symbols[
            '?OtRefreshTrailStatusPanel_0042d5d0_ProductWip@'
            'TrailStatusPanelState_0042d5d0_ProductWip@@QAEXPAX@Z']

    def verify(self):
        return VERIFIER.verify(self.directory, 'OtRefreshTrailStatusPanel_0002d5d0',
                               'trail-status-panel-operands.csv')

    def replace_bytes(self, address, replacement):
        pe = pefile.PE(data=self.image.read_bytes())
        offset = pe.get_offset_from_rva(address - pe.OPTIONAL_HEADER.ImageBase)
        data = bytearray(self.image.read_bytes())
        data[offset:offset + len(replacement)] = replacement
        self.image.write_bytes(data)

    def test_reviewed_operands_pass(self):
        self.assertEqual(self.verify()['status'], 'pass')

    def test_location_using_application_module_fails(self):
        self.replace_bytes(self.panel + 273, struct.pack(
            '<I', self.symbols['_g_applicationModule_00405a40_20260603']))
        with self.assertRaisesRegex(ValueError, 'Wrong candidate target at 273'):
            self.verify()

    def test_hud_using_resource_module_fails(self):
        self.replace_bytes(self.panel + 897, struct.pack(
            '<I', self.symbols['_g_resourceModule']))
        with self.assertRaisesRegex(ValueError, 'Wrong candidate target at 897'):
            self.verify()

    def test_changed_motion_label_fails(self):
        self.replace_bytes(self.symbols['_g_trailMotionResting_0042d5d0'], b'Testing')
        with self.assertRaisesRegex(ValueError, 'String mismatch at 1464'):
            self.verify()

    def test_legacy_health_wrapper_fails(self):
        operand = self.panel + 1309
        target = self.symbols['_OtGetPartyHealthClassStringIdAlt3_004195c0_39pct']
        self.replace_bytes(operand, struct.pack('<i', target - operand - 4))
        with self.assertRaisesRegex(ValueError, 'Wrong candidate target at 1309'):
            self.verify()


if __name__ == '__main__':
    unittest.main()
