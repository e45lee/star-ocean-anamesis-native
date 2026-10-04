# Release package launcher (Windows): runs the original 3.7.0 client, unmodified, in the emulator
# (soa-emu.exe) against the local game server (soa-server.exe), which this script starts and stops.
# Both find the game files beside them or in .\game (README.txt).
#
# Usage: run-emulator.cmd [options] [soa-emu options...]
#   --home DIR               data: DIR\phone (the client), DIR\server (the server's state),
#                            DIR\server.log + server.log.err (default %LOCALAPPDATA%\soa\emulator-370)
#   --port N                 the game port (default 44300; HTTP: N + 80)
#   --new-player, --enable-events, --event-keywords W, --seed FILE   soa-server's options
#   the others go to soa-emu.exe (e.g. --fullscreen)
$ErrorActionPreference = "Stop"
$here = $PSScriptRoot
$emu = Join-Path $here "soa-emu.exe"
$srv = Join-Path $here "soa-server.exe"
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
$phone = Join-Path $home_dir "phone"; $state = Join-Path $home_dir "server"; $slog = Join-Path $home_dir "server.log"
New-Item -ItemType Directory -Force -Path $phone, $state | Out-Null
Write-Host "== starting soa-server (game 127.0.0.1:$port, http 127.0.0.1:$httpPort; data $state)"
$sp = Start-Process -FilePath $srv -WorkingDirectory $here -NoNewWindow -PassThru -RedirectStandardOutput $slog `
    -RedirectStandardError "$slog.err" -ArgumentList (@("--listen", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort",
    "--data", "`"$state`"") + $srvArgs)
try {
    $up = $false
    for ($t = 0; $t -lt 480; $t++) {
        if ((Test-Path "$slog.err") -and (Select-String -Path $slog, "$slog.err" -Pattern '^soa-server: game' -Quiet)) { $up = $true; break }
        if ($sp.HasExited) { break }
        Start-Sleep -Milliseconds 500
    }
    if (-not $up) { Write-Host "run-emulator: soa-server didn't start (see README.txt); log: $slog.err"; exit 1 }
    if (-not (Select-String -Path "$slog.err" -Pattern '^soa-server: CDN' -Quiet)) {
        Write-Host "run-emulator: soa-server found no 3.7.0 download (see README.txt); log: $slog.err"; exit 1
    }
    Write-Host "== starting soa-emu (phone data $phone)"
    $ep = Start-Process -FilePath $emu -WorkingDirectory $here -NoNewWindow -PassThru -ArgumentList (@("--data", "`"$phone`"",
        "--server", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort") + $emuArgs)
    $ep.WaitForExit()
    exit $ep.ExitCode
} finally {
    if (-not $sp.HasExited) { Stop-Process -Id $sp.Id -Force }
}
