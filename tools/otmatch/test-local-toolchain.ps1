[CmdletBinding()]
param(
    [string]$VcToolsRoot = 'toolchain\MSDEV',
    [string]$OriginalPath = 'Sample\Oregon Trail CD\OTWIN32\Oregon32.exe'
)

# An isolated diagnostic build of a real recovered function. This does not
# replace the canonical candidate graph or award project progress credit.
$ErrorActionPreference = 'Stop'
$repoRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$savedPath = $env:PATH
$savedInclude = $env:INCLUDE
$savedLib = $env:LIB
Push-Location $repoRoot
try {
    $vc = (Resolve-Path -LiteralPath $VcToolsRoot).Path
    $env:PATH = "$vc\BIN;$env:PATH"
    $env:INCLUDE = "$vc\INCLUDE"
    $env:LIB = "$vc\LIB"
    $out = 'artifacts\otmatch\smoke'
    New-Item -ItemType Directory -Force $out | Out-Null
    $obj = "$out\src_otwin_graphics_draw_beveled_rect.obj"
    & "$vc\BIN\CL.EXE" /nologo /c /O1 /MT "/Fo$obj" src\otwin\graphics\draw_beveled_rect.cpp
    if ($LASTEXITCODE -ne 0) { throw 'VC4 compilation failed.' }
    & "$vc\BIN\LINK.EXE" /nologo /dll /noentry /incremental:no /machine:ix86 /opt:noref "/out:$out\smoke.dll" "/map:$out\smoke.map" $obj gdi32.lib
    if ($LASTEXITCODE -ne 0) { throw 'VC4 linking failed.' }
    Write-Host 'PASS: VC4 compiled and linked recovered C++.'
    if (-not (Test-Path -LiteralPath $OriginalPath -PathType Leaf)) {
        Write-Warning "Original image missing: $OriginalPath. Byte comparison was not run."
        return
    }
    $rows = @(Import-Csv tools\otmatch\functions.vc40-real-cpp.csv |
        Where-Object { $_.name -eq 'OtDrawBeveledRect_0000b4c0' })
    if ($rows.Count -ne 1) { throw 'Expected exactly one OtDrawBeveledRect manifest row.' }
    $rows | Export-Csv "$out\functions.csv" -NoTypeInformation
    # Invoke in a child shell because the matcher uses exit for its result.
    & powershell.exe -NoProfile -ExecutionPolicy Bypass -File "$PSScriptRoot\match-functions.ps1" `
        -ManifestPath "$out\functions.csv" -OriginalPath $OriginalPath `
        -CandidatePath "$out\smoke.dll" -CandidateMapPath "$out\smoke.map" `
        -ResultsCsvPath "$out\results.csv" -SummaryOnly
    if ($LASTEXITCODE -ne 0) { throw "Byte comparison failed; inspect $out\results.csv." }
} finally {
    $env:PATH = $savedPath
    $env:INCLUDE = $savedInclude
    $env:LIB = $savedLib
    Pop-Location
}
