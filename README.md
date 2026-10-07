# The Oregon Trail (Win32) — matching decompilation

Reconstructed C++ for the 1996 Windows release of *The Oregon Trail*, targeting
`Oregon32.exe` and `OREGON32.DLL`.

"Matching" here means the recovered source, compiled with the original
Microsoft Visual C++ 4.0 toolchain, must reproduce the original function bytes.
A function counts only when the matcher agrees byte-for-byte across its whole
envelope, with relocated operands masked and their identity proven.

This is an unofficial research project. It is not affiliated with, sponsored by,
or endorsed by MECC, The Learning Company, Houghton Mifflin Harcourt, Microsoft,
or any other rights holder.

## Status

**61.92% instruction coverage in the local verification** — 39,939 of 64,499 instructions.

Twelve newly matched functions add 4,013 instructions to the frozen 55.70%
upstream baseline. All 748 baseline matches remain intact. The new work covers
main-window creation, composite-map construction, journey initialization,
the status dialog callback and its setup/text population, drop-supplies setup,
start-date setup, the trail status-panel refresh, and the List of Legends
dialog's setup, drawing and commands.
[Local results](docs/local-progress.json) retain the original instruction counts;
`build/report.json` remains the unchanged upstream report.

| Image | Functions | Instructions | Body bytes |
| --- | ---: | ---: | ---: |
| `OREGON32.DLL` | 69/69 (100.00%) | 2,753/2,753 (100.00%) | 7,765/7,765 (100.00%) |
| `Oregon32.exe` | 691/788 (87.69%) | 37,186/61,746 (60.22%) | 117,017/199,963 (58.52%) |
| **Combined** | **760/857 (88.68%)** | **39,939/64,499 (61.92%)** | **124,782/207,728 (60.07%)** |

**Instructions are the headline, not function count.** The functions still
outstanding are much larger than the ones already closed, so a function
percentage materially overstates how much of the program is recovered. The
denominator is the full Ghidra inventory of both shipped images, not a sum of
the manifest's envelopes — it counts everything in the program, including code
nobody has attempted yet.

A function is credited only when all of the following hold: the matcher reports
`match`; the manifest's `expected_status` is `match`, so a matching
work-in-progress earns nothing until its source is reviewed and promoted; the
implementation is C++ or a genuine VC4 library body, never hand-written
assembly; at least one byte is compared after masking; and credited C++ is
reachable from the canonical product graph.

The headline is provisional in one respect worth stating plainly: it measures
normalized code shape, and remains so until every masked operand's identity is
proven in both images. It is not whole-image identity.

`docs/decompilation-metrics.md` defines all of this precisely.

## What is not here

This is a source-only snapshot. Deliberately excluded:

- the game — `Oregon32.exe`, `OREGON32.DLL`, the disc, and every extracted asset;
- Microsoft Visual C++ 4.0, which is required to build and is not redistributable;
- the Ghidra project and the function inventories exported from it;
- the recovery workbench (`src/otwin/_recovery/`), the legacy exact-match
  scaffolding (`src/otwin/_exact/`), the C# asset viewer, and the per-function
  recovery notes.

The original harness and inventory-generation workflow remains unavailable.
The public-source build wrapper can nevertheless reproduce all accepted function
matches with VC4 and both original images. It omits metadata for absent recovery
files, links the real product sources without unresolved-symbol stubs, and uses
the instruction inventory preserved in `build/report.json` for local totals.

From a configured Windows checkout, run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/otmatch/verify-local-progress.ps1
```

This builds all three candidates, compares all 857 manifest rows, checks the
product source policy and the twelve new functions' relocated operand identities,
and writes `artifacts/otmatch/public-diagnostic/local-progress.json`.
Unfinished functions, including missing WIP symbols, receive no credit. See
[local setup](LOCAL_SETUP.txt) for toolchain paths and analysis commands.
The local result is function-level verification; full gameplay has not been tested.

The status-panel recovery also corrects which module supplies its strings:
landmark names come from the resource DLL, while HUD labels come from the
application. Its health-class call uses the original member ABI; the existing
health-class match now targets that product implementation instead of a legacy
wrapper. Operand evidence checks the still-unmatched gauge and health-score
dependencies without crediting their bodies.

Use only external inputs you are legally entitled to possess.

## Layout

| Path | What |
| --- | --- |
| `src/otwin/<subsystem>/` | Recovered source by subsystem — app, audio, graphics, hunt, river, trade, trail |
| `tools/otmatch/` | The manifest, the VC4 candidate build, the byte matcher, and the link anchors |
| `harness.toml`, `harness-match.sh` | Measurement configuration and the scoring driver |
| `docs/decompilation-metrics.md` | How the headline is defined and gated |

`*_notes.cpp` files alongside the product source hold readable documentation of
what a function does; they are not compiled into the candidate.

## The matching contract

`tools/otmatch/functions.vc40-real-cpp.csv` is the authority: 857 rows naming
each function's location in both images, how many bytes to compare, and which
operand bytes are relocated and must therefore be masked.

Masking is not a loophole. Two independently linked images legitimately place
their own globals at different addresses, so an operand pointing at internal
data can never be expected to agree. Identity is demanded exactly where both
sides should name the same *external* thing — an import.

Scoring is performed by `decomp-harness`, a separate matching harness pinned by
revision in `harness-match.sh` so a result always identifies the exact
implementation that produced it. That harness is not currently published, so the
pin will not resolve for outside readers.

## Progress reporting

`build/report.json` is a [decomp.dev](https://decomp.dev) progress report in
objdiff's report schema, uploaded by `.github/workflows/progress.yml`.

objdiff cannot generate it: objdiff diffs whole target objects against whole
base objects, and this project has no target objects — its contract is a
manifest of function envelopes inside two shipped PE images. decomp.dev's
integration guide permits generating its schema from a project's own tooling, so
`tools/otmatch/gen_decomp_dev_report.py` does, joining the matcher results, both
Ghidra inventories, and the manifest. Its output round-trips through objdiff's
own report parser.

The committed `build/report.json` preserves the upstream 55.70% snapshot; CI
validates and publishes that snapshot. The newer local measurement is recorded
separately in `docs/local-progress.json` and reproduced with
`verify-local-progress.ps1`. It does not change the published denominator or
pretend to regenerate the unavailable Ghidra inventories.

## Evidence policy

Source is reconstructed from the shipped binaries, their disassembly, and
reproducible compiler and linker experiments. Unlicensed original source,
editor or tag databases, and development-project files are not accepted as
evidence, and public availability of such an artifact is not evidence of
permission to use it.

## License

There is no blanket license. See [`LICENSE_SCOPE.md`](LICENSE_SCOPE.md).
