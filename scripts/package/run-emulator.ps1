# Release package launcher (Windows): runs the original 3.7.0 client, unmodified, in the emulator
# (soa-emu.exe) against the local game server (soa-server.exe), which this script starts and stops.
# Both find the game files beside them or in .\game (README.txt).
#
# Usage: run-emulator.cmd [options] [soa-emu options...]
#   --home DIR               data: DIR\phone (the client), DIR\server (the server's state),
#                            DIR\server.log + server.log.err (default %LOCALAPPDATA%\soa\emulator-370)
#   --port N                 the game port (default 44300; HTTP: N + 80)
#   soa-server's options (lib\with-server.ps1): --new-player, --seed FILE, --seed-rng N,
#     --clock "YYYY-MM-DD HH:MM:SS", --start-coins N, --galaxy-pass, --enable-events,
#     --event-keywords W, --restore-tower, --surprise, --stamina-heal-time S, --fail SPEC,
#     --download PATH, --download-dir DIR, --master FILE, --db FILE, --log-packets DIR,
#     --campaign-master-db FILE, --campaign-seed N, --english (the English files; with soa-emu's
#     --lang en: the English game, as run-emulator-en.cmd does)
#   the others go to soa-emu.exe (e.g. --fullscreen)
$ErrorActionPreference = "Stop"
$here = $PSScriptRoot
. (Join-Path $here "lib\with-server.ps1")
WsInit "run-emulator"
$emu = Join-Path $here "soa-emu.exe"
$srv = Join-Path $here "soa-server.exe"
$home_dir = Join-Path $env:LOCALAPPDATA "soa\emulator-370"
$port = 44300
$emuArgs = @()
for ($i = 0; $i -lt $args.Count; $i++) {
    $a = [string]$args[$i]
    switch -regex ($a) {
        '^(-h|--help)$' { Get-Content $PSCommandPath | Where-Object { $_ -match '^#' } | ForEach-Object { $_ -replace '^# ?', '' }; exit 0 }
        '^(-Home|--home)$' { WsNeed $args $i; $home_dir = [string]$args[++$i]; continue }
        '^--port$' { WsNeed $args $i; $port = WsCheckPort ([string]$args[++$i]); continue }
        default {
            $n = WsServerOption $args $i
            if ($n -gt 0) { $i += $n - 1 } else { $emuArgs += (WsQ $a) }
        }
    }
}
$httpPort = $port + 80
$phone = Join-Path $home_dir "phone"; $state = Join-Path $home_dir "server"; $slog = Join-Path $home_dir "server.log"
New-Item -ItemType Directory -Force -Path $phone, $state | Out-Null
Write-Host "== starting soa-server (game 127.0.0.1:$port, http 127.0.0.1:$httpPort; data $state)"
WsStartServer $srv $here $slog "$slog.err" (@("--listen", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort",
    "--data", (WsQ $state)) + $WsSrvArgs)
try {
    WsWaitReady
    Write-Host "== starting soa-emu (phone data $phone)"
    exit (WsRunClient $emu $here (@("--data", (WsQ $phone), "--server", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort") + $emuArgs))
} finally {
    WsStop
}
