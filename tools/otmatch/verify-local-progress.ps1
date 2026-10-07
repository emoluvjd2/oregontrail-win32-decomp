[CmdletBinding()]
param(
    [switch]$ReuseResults
)

# Rebuild and measure the public source graph against the original game.
# -ReuseResults only rechecks existing results and operand evidence.
$ErrorActionPreference = 'Stop'
$repoRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
Push-Location $repoRoot
try {
    $output = 'artifacts\otmatch\public-diagnostic'
    if (-not $ReuseResults) {
        & powershell -NoProfile -ExecutionPolicy Bypass -File `
            tools\otmatch\build-public-candidates.ps1
        if ($LASTEXITCODE -ne 0) { throw 'Public candidate build failed.' }

        & powershell -NoProfile -ExecutionPolicy Bypass -File `
            tools\otmatch\match-functions.ps1 `
            -ManifestPath tools\otmatch\functions.vc40-real-cpp.csv `
            -OriginalPath 'Sample\Oregon Trail CD\OTWIN32\Oregon32.exe' `
            -OriginalDllPath 'Sample\Oregon Trail CD\OTWIN32\OREGON32.DLL' `
            -CandidatePath "$output\otwin-match-candidates.dll" `
            -CandidateMapPath "$output\otwin-match-candidates.map" `
            -CandidateLcmtPath "$output\otwin-match-candidates-lcmt.dll" `
            -CandidateLcmtMapPath "$output\otwin-match-candidates-lcmt.map" `
            -CandidateDllcrtPath "$output\otwin-match-candidates-dllcrt.dll" `
            -CandidateDllcrtMapPath "$output\otwin-match-candidates-dllcrt.map" `
            -ResultsCsvPath "$output\after-results.csv" -AllowMismatches -SummaryOnly
        # The public snapshot still lacks some WIP symbols. The matcher returns
        # nonzero for those; the summarizer independently rejects every failed
        # accepted row, stale artifact, and incomplete inventory.
    }

    & python tools\otmatch\summarize-local-progress.py
    if ($LASTEXITCODE -ne 0) { throw 'Strict local progress validation failed.' }

    & powershell -NoProfile -ExecutionPolicy Bypass -File `
        tools\otmatch\audit-vc4-product-sources.ps1 -SummaryOnly `
        -ResultsJsonPath "$output\source-policy-audit.json"
    if ($LASTEXITCODE -ne 0) { throw 'Product source-policy audit failed.' }

    $proofs = @(
        @('FUN_004035b0_000035b0', 'main-window-creation'),
        @('OtLoadCompositeAssetSet_00006010', 'composite-map'),
        @('OtInitializeJourneyRuntime_0001a120', 'journey-initialization'),
        @('OtGetPartyHealthClassStringId', 'party-health-class'),
        @('OtStatusDialogProc_0001d040', 'status-callback'),
        @('FUN_0041d400_0001d400', 'status-setup'),
        @('FUN_0041d650_0001d650', 'status-population'),
        @('FUN_0041efb0_0001efb0', 'drop-supplies'),
        @('OtInitStartDateDialog_00024730', 'start-date'),
        @('OtRefreshTrailStatusPanel_0002d5d0', 'trail-status-panel'),
        @('FUN_00430000_00030000', 'score-list-drawing'),
        @('FUN_00430180_00030180', 'score-list-setup'),
        @('FUN_00430350_00030350', 'score-list-callback')
    )
    foreach ($proof in $proofs) {
        & python tools\otmatch\verify-main-window-operands.py `
            --function $proof[0] --proof "$($proof[1])-operands.csv" `
            --output "$output\$($proof[1])-operands.json"
        if ($LASTEXITCODE -ne 0) { throw "Operand identity check failed: $($proof[0])" }
    }
    Write-Host "Verified progress: $output\local-progress.json"
} finally {
    Pop-Location
}
