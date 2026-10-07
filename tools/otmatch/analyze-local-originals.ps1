[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$GhidraRoot,
    [string]$OriginalDirectory = 'Sample\Oregon Trail CD\OTWIN32',
    [switch]$Reexport
)

$ErrorActionPreference = 'Stop'
$repoRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
Push-Location $repoRoot
try {
    $headless = Join-Path (Resolve-Path -LiteralPath $GhidraRoot).Path 'support\analyzeHeadless.bat'
    $original = (Resolve-Path -LiteralPath $OriginalDirectory).Path
    $project = Join-Path $repoRoot 'artifacts\ghidra\projects'
    $output = Join-Path $repoRoot 'artifacts\ghidra\exports'
    New-Item -ItemType Directory -Force $project, $output | Out-Null
    $arguments = @($project, 'OregonTrailLocal')
    if ($Reexport) {
        $arguments += @('-process', '*', '-noanalysis')
    } else {
        if (Test-Path (Join-Path $project 'OregonTrailLocal.gpr')) {
            throw 'Project already exists. Use -Reexport to refresh exports while preserving annotations.'
        }
        foreach ($name in @('Oregon32.exe', 'OREGON32.DLL')) {
            if (-not (Test-Path -LiteralPath (Join-Path $original $name))) { throw "Missing $name" }
        }
        $arguments += @('-import', (Join-Path $original 'Oregon32.exe'), (Join-Path $original 'OREGON32.DLL'))
    }
    $arguments += @('-scriptPath', $PSScriptRoot, '-postScript', 'ExportLocalAnalysis.java', $output,
        '-analysisTimeoutPerFile', '300', '-max-cpu', '2', '-log', (Join-Path $repoRoot 'artifacts\ghidra\analysis.log'))
    & $headless @arguments
    if ($LASTEXITCODE -ne 0) { throw "Ghidra exited with code $LASTEXITCODE" }
    foreach ($name in @('Oregon32.exe', 'OREGON32.DLL')) {
        if (-not (Test-Path -LiteralPath (Join-Path $output "$name\function_metrics.csv"))) {
            throw "Export missing for $name. Inspect artifacts\ghidra\analysis.log."
        }
    }
    Write-Host "Local analysis exported to $output. This is not the unpublished upstream inventory."
} finally {
    Pop-Location
}
