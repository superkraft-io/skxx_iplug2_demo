# How to use:  powershell -NoProfile -ExecutionPolicy Bypass -File "lockfile.ps1" -Path "file to lock"

param(
  [Parameter(Mandatory)]
  [string]$Path
)

if (-not (Test-Path -LiteralPath $Path)) {
  New-Item -ItemType File -Path $Path -Force | Out-Null
}

# Open exclusive handle (locks file)
$script:fs = [System.IO.File]::Open(
  $Path,
  [System.IO.FileMode]::OpenOrCreate,
  [System.IO.FileAccess]::ReadWrite,
  [System.IO.FileShare]::None
)

# Subscribe to Ctrl+C (portable between Windows PowerShell 5.1 and PowerShell 7)
$handler = [System.ConsoleCancelEventHandler]{
  param($sender, $e)
  $e.Cancel = $true
  try { $script:fs.Dispose() } catch {}
  Write-Host "Released lock on '$Path'."
  [Environment]::Exit(0)
}
[Console]::add_CancelKeyPress($handler)

Write-Host "Locked '$Path'. Press Ctrl+C to release."

try {
  while ($true) { Start-Sleep -Seconds 1 }
}
finally {
  try { $script:fs.Dispose() } catch {}
  [Console]::remove_CancelKeyPress($handler)
}