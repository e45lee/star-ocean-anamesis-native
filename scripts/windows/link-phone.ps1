# Builds a run's phone from the stamped shared pre-downloaded phone on Windows: the Windows twin of
# scripts/shared-phone.sh's shared_phone_link (control/soadrive/winhost.py calls it). Real
# directories and a hard link per downloaded file (CreateHardLink, in a few seconds; cp -al through
# WSL takes about ten minutes for the 26,055 files), real copies of what the client writes in place.
#
# Usage: powershell -File scripts\windows\link-phone.ps1 SRC DST [COPY...]
#   SRC   the shared phone (work\phone-3.7.0, staged by scripts/windows-stage.sh --phone)
#   DST   the run's phone (deleted first)
#   COPY  paths under data\files\download copied instead of linked (shared-phone.sh SHARED_PHONE_COPY)
param([Parameter(Mandatory = $true)][string]$Src, [Parameter(Mandatory = $true)][string]$Dst,
      [Parameter(ValueFromRemainingArguments = $true)][string[]]$Copy)
$ErrorActionPreference = "Stop"
Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class SoaHardLink {
    [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
    public static extern bool CreateHardLink(string link, string target, IntPtr security);
}
"@
$dl = "data\files\download"
$s = (Resolve-Path (Join-Path $Src $dl)).Path
if (Test-Path $Dst) { Remove-Item -Recurse -Force $Dst }
$d = Join-Path $Dst $dl
New-Item -ItemType Directory -Force -Path $d, (Join-Path $Dst "data\shared_prefs"), (Join-Path $Dst "data\cache") | Out-Null
foreach ($dir in [IO.Directory]::EnumerateDirectories($s, "*", [IO.SearchOption]::AllDirectories)) {
    [IO.Directory]::CreateDirectory($d + $dir.Substring($s.Length)) | Out-Null
}
$n = 0
foreach ($f in [IO.Directory]::EnumerateFiles($s, "*", [IO.SearchOption]::AllDirectories)) {
    if (-not [SoaHardLink]::CreateHardLink($d + $f.Substring($s.Length), $f, [IntPtr]::Zero)) {
        throw "CreateHardLink for $f failed (error $([Runtime.InteropServices.Marshal]::GetLastWin32Error()))"
    }
    $n++
}
foreach ($p in $Copy) {
    $sp = Join-Path $s $p; $dp = Join-Path $d $p
    if (-not (Test-Path $sp)) { continue }
    Remove-Item -Recurse -Force $dp
    Copy-Item -Recurse $sp $dp
    # the shared files are read-only (the stage keeps chmod a-w as the read-only attribute); the copies are the run's
    Get-ChildItem -Recurse -Force $dp | Where-Object { -not $_.PSIsContainer } | ForEach-Object { $_.IsReadOnly = $false }
    if ((Get-Item $dp) -is [IO.FileInfo]) { (Get-Item $dp).IsReadOnly = $false }
}
Write-Output "linked $n files"
