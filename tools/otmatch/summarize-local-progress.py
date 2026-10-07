"""Report strict local gains against the preserved upstream instruction inventory."""
import csv
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DIRECTORY = ROOT / 'artifacts/otmatch/public-diagnostic'
report_path = ROOT / 'build/report.json'
manifest_path = ROOT / 'tools/otmatch/functions.vc40-real-cpp.csv'
results_path = DIRECTORY / 'after-results.csv'
published = json.loads(report_path.read_text())
manifest_hash = hashlib.sha256(manifest_path.read_bytes()).hexdigest()
with manifest_path.open(newline='') as stream:
    manifest = list(csv.DictReader(stream))
with results_path.open(newline='', encoding='utf-8-sig') as stream:
    rows = list(csv.DictReader(stream))
current = {(r['program'].lower(), r['name'], r['original_rva']): r for r in rows}
if len(current) != len(rows):
    raise SystemExit('Duplicate function rows in matcher results')

# The frozen inventory records the 748 accepted baseline functions and their
# instruction counts. No unpublished Ghidra project or local baseline CSV is
# needed to calculate gains; addresses distinguish duplicate runtime names.
accepted = set()
sizes = {}
for unit in published['units']:
    for function in unit.get('functions', []):
        bindings = [r for r in manifest if r['name'] == function['name']
                    and int(r['original_va'], 0) == int(function['address'])]
        if len(bindings) != 1:
            raise SystemExit('Ambiguous inventory binding: ' + function['name'])
        row = bindings[0]
        key = (row['program'].lower(), row['name'], '0x%08x' % int(row['original_rva'], 0))
        if key in sizes:
            raise SystemExit('Duplicate inventory function: ' + repr(key))
        sizes[key] = int(function['size'])
        if function['fuzzy_match_percent'] == 100:
            accepted.add(key)

if set(current) != set(sizes):
    raise SystemExit('Results do not cover the complete published inventory')
if any(r['manifest_sha256'] != manifest_hash for r in current.values()):
    raise SystemExit('Results are stale: rerun the full matcher with the current manifest')
# A reused CSV must describe the actual candidate binaries and maps on disk.
artifacts = {(r[field], r['candidate_file_sha256' if field == 'candidate_path' else 'candidate_map_sha256'])
             for r in current.values()
             for field in ('candidate_path', 'candidate_map_path') if r[field]}
for name, expected_hash in artifacts:
    artifact = Path(name)
    actual_hash = hashlib.sha256(artifact.read_bytes()).hexdigest()
    if actual_hash != expected_hash:
        raise SystemExit('Stale candidate artifact: ' + name)
regressions = [key for key, row in current.items()
               if (key in accepted or row['expected_status'] == 'match')
               and (row['verification_status'] != 'pass'
                    or row['expected_status'] != 'match')]
if regressions:
    raise SystemExit('Accepted functions regressed: ' + repr(regressions))
gains = [key for key, row in current.items()
         if key not in accepted and row['actual_status'] == 'match'
         and row['expected_status'] == 'match' and row['verification_status'] == 'pass']
instructions = sum(sizes[key] for key in gains)
measures = published['measures']
if (int(measures['matched_functions']) != len(accepted)
        or int(measures['matched_code']) != sum(sizes[key] for key in accepted)
        or int(measures['total_code']) != sum(sizes.values())):
    raise SystemExit('Published measures do not agree with the frozen inventory')
matched = int(measures['matched_code']) + instructions
total = int(measures['total_code'])
result = {
    'basis': 'Local strict matcher results with preserved upstream instruction counts',
    'published_report_sha256': hashlib.sha256(report_path.read_bytes()).hexdigest(),
    'results_sha256': hashlib.sha256(results_path.read_bytes()).hexdigest(),
    'manifest_sha256': manifest_hash,
    'baseline_functions_preserved': len(accepted),
    'new_matches': [name for _, name, _ in gains],
    'new_match_details': [dict(name=key[1], original_rva=key[2],
        instructions=sizes[key], body_bytes=int(current[key]['size'], 0)) for key in gains],
    'added_instructions': instructions,
    'matched_functions': len(accepted) + len(gains),
    'total_functions': int(measures['total_functions']),
    'matched_instructions': matched,
    'total_instructions': total,
    'instruction_percent': 100 * matched / total,
    'regressions': regressions,
}
output = DIRECTORY / 'local-progress.json'
output.write_text(json.dumps(result, indent=2) + '\n')
print(json.dumps(result, indent=2))
