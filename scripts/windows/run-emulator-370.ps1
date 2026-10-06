# Runs the original 3.7.0 online client, unmodified, in the emulator on Windows
# (build-win\emulator\soa-emu.exe) against soa-server.exe, which this script starts and stops.
# The Windows twin of scripts/run-emulator-370.sh (README.md "Windows").
#
# Usage: scripts\windows\run-emulator-370.cmd [options] [soa-emu options...]
#   -Home DIR / --home DIR   data: DIR\phone (the client), DIR\server (the server's state),
#                            DIR\server.log + server.log.err (default %LOCALAPPDATA%\soa\emulator-370:
#                            DIR\phone is soa-emu.exe's own default)
#   --port N                 the game port (default 44300; HTTP: N + 80)
#   --new-player, --enable-events, --event-keywords W, --seed FILE   soa-server's options
#   the others go to soa-emu.exe (e.g. --fullscreen, --headless)
# The first start downloads about 3 GB of game data from the local server.
# Needs: build-win\ (scripts/build.sh --windows), work\libSOA-3.7.0.so, the 3.7.0 APK in apk\,
# data\basmaster-3.7.0.sqlite3 and the 3.7.0 download for the server,
# work\SOA-3.7.0-canonical-data.zip (read in place; README.md "Game files").
$ErrorActionPreference = "Stop"
$repo = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
$emu = Join-Path $repo "build-win\emulator\soa-emu.exe"
$srv = Join-Path $repo "build-win\server\soa-server.exe"
$home_dir = Join-Path $env:LOCALAPPDATA "soa\emulator-370"
$port = 44300
$srvArgs = @(); $emuArgs = @()
for ($i = 0; $i -lt $args.Count; $i++) {
    $a = [string]$args[$i]
    switch -regex ($a) {
        '^(-h|--help)$' { Get-Content $PSCommandPath | Where-Object { $_ -match '^#' } | ForEach-Object { $_ -replace '^# ?', '' }; exit 0 }
        '^(-Home|--home)$' { $home_dir = [string]$args[++$i]; continue }
        '^--port$' { $port = [int]$args[++$i]; continue }
        '^(--new-player|--enable-events)$' { $srvArgs += $a; continue }
        '^(--event-keywords|--seed)$' { $srvArgs += $a; $srvArgs += [string]$args[++$i]; continue }
        default { $emuArgs += $a }
    }
}
$httpPort = $port + 80
foreach ($f in @($emu, $srv)) {
    if (-not (Test-Path $f)) { Write-Error "run-emulator-370: $f isn't built; run scripts/build.sh --windows" }
}
foreach ($f in @("work\libSOA-3.7.0.so", "apk\STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk", "data\basmaster-3.7.0.sqlite3")) {
    if (-not (Test-Path (Join-Path $repo $f))) { Write-Error "run-emulator-370: $f is missing; see README.md" }
}
# the download: the zip, read in place
$download = Join-Path $repo "work\SOA-3.7.0-canonical-data.zip"
if (-not (Test-Path $download)) { Write-Error "run-emulator-370: the 3.7.0 download, work\SOA-3.7.0-canonical-data.zip, is missing; see README.md" }
$phone = Join-Path $home_dir "phone"; $state = Join-Path $home_dir "server"; $slog = Join-Path $home_dir "server.log"
New-Item -ItemType Directory -Force -Path $phone, $state | Out-Null
Write-Host "== starting soa-server (game 127.0.0.1:$port, http 127.0.0.1:$httpPort; data $state)"
$sp = Start-Process -FilePath $srv -WorkingDirectory $repo -NoNewWindow -PassThru -RedirectStandardOutput $slog `
    -RedirectStandardError "$slog.err" -ArgumentList (@("--listen", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort",
    "--data", "`"$state`"", "--download-dir", "`"$download`"") + $srvArgs)
try {
    $up = $false
    for ($t = 0; $t -lt 240; $t++) {
        # (its stdout and stderr: Start-Process keeps them in two files)
        if ((Test-Path "$slog.err") -and (Select-String -Path $slog, "$slog.err" -Pattern '^soa-server: game' -Quiet)) { $up = $true; break }
        if ($sp.HasExited) { break }
        Start-Sleep -Milliseconds 500
    }
    if (-not $up) { Write-Host "run-emulator-370: soa-server didn't start; log: $slog.err"; exit 1 }
    Write-Host "== starting soa-emu (phone data $phone)"
    $ep = Start-Process -FilePath $emu -WorkingDirectory $repo -NoNewWindow -PassThru -ArgumentList (@("--data", "`"$phone`"",
        "--server", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort") + $emuArgs)
    $ep.WaitForExit()
    exit $ep.ExitCode
} finally {
    if (-not $sp.HasExited) { Stop-Process -Id $sp.Id -Force }
}
