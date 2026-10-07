[CmdletBinding()]
param(
    [string]$VcToolsRoot = 'toolchain\MSDEV',
    [string]$OutputDirectory = 'artifacts\otmatch\public-diagnostic',
    [switch]$Rebuild
)

# The public snapshot omits recovery files still named by TU metadata.
# Retain every flag for present sources and explicitly report omitted entries.
# Do not edit the canonical metadata, synthesize stubs, or allow unresolved links.
$ErrorActionPreference = 'Stop'
$repoRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
Push-Location $repoRoot
try {
    New-Item -ItemType Directory -Force $OutputDirectory | Out-Null
    $output = (Resolve-Path -LiteralPath $OutputDirectory).Path
    $present = @()
    $missing = @()
    foreach ($row in Import-Csv (Join-Path $PSScriptRoot 'vc4-tu-metadata.csv')) {
        if (Test-Path -LiteralPath $row.source_path -PathType Leaf) {
            $present += $row
        } else {
            $missing += $row
        }
    }
    $metadata = Join-Path $output 'present-tu-metadata.csv'
    if ($present.Count -eq 0) { throw 'No present-source compiler metadata found.' }
    $present | Export-Csv $metadata -NoTypeInformation
    $missing | Export-Csv (Join-Path $output 'omitted-tu-metadata.csv') -NoTypeInformation
    Write-Host "Public snapshot: $($missing.Count) absent-source metadata entries omitted."
    & (Join-Path $PSScriptRoot 'build-match-candidates.ps1') `
        -Toolchain LegacyMsvc -VcToolsRoot $VcToolsRoot -OutputDirectory $output `
        -DefaultOptimization /Od -SemanticOptimization /O1 -TuMetadataPath $metadata `
        -Rebuild:$Rebuild
} finally {
    Pop-Location
}
