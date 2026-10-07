# Release package launcher (Windows): runs the desktop port (soa.exe) with its own network code
# against the local game server running as a separate program (soa-server.exe), which this script
# starts first and stops when soa.exe exits (also on Ctrl+C or when the window is closed). Both find
# the game files beside them or in .\game (README.txt). run-port.cmd (the server inside soa.exe)
# stays the usual way to play.
#
# Usage: run-port-server.cmd [options]
#   --data DIR               soa.exe's data dir, as soa.exe --data (default %LOCALAPPDATA%\soa\port-370,
#                            the same as run-port.cmd: the phone's data and save); the server keeps
#                            its state in DIR\server\ and logs into DIR\server.log (its standard
#                            output, normally empty, into DIR\server.out.log)
#   --port N                 the game server's port (default 44310); its HTTP/CDN port is N+80
#   server options, passed to soa-server.exe (they set the server's rules and state; lib\with-server.ps1):
#     --new-player, --seed FILE, --seed-rng N, --clock "YYYY-MM-DD HH:MM:SS", --start-coins N,
#     --galaxy-pass, --enable-events, --event-keywords L, --restore-tower, --surprise,
#     --stamina-heal-time S, --fail SPEC, --download PATH, --download-dir DIR, --master FILE,
#     --db FILE, --log-packets DIR, --campaign-master-db FILE, --campaign-seed N, --english (the
#     English files: with --lang en for soa, the English game)
#   any other options go to soa.exe, e.g. --fullscreen, --size 729x1296, --apk FILE (soa.exe --help)
$ErrorActionPreference = "Stop"
$here = $PSScriptRoot
. (Join-Path $here "lib\with-server.ps1")
WsInit "run-port-server"
$soa = Join-Path $here "soa.exe"
$srv = Join-Path $here "soa-server.exe"
$local = if ($env:LOCALAPPDATA) { $env:LOCALAPPDATA } else { Join-Path $env:USERPROFILE "AppData\Local" }
$data = Join-Path $local "soa\port-370"
$port = 44310
$soaArgs = @()
for ($i = 0; $i -lt $args.Count; $i++) {
    $a = [string]$args[$i]
    switch -regex ($a) {
        '^(-h|--help)$' { Get-Content $PSCommandPath | Where-Object { $_ -match '^#' } | ForEach-Object { $_ -replace '^# ?', '' }; exit 0 }
        '^--data$' { WsNeed $args $i; $data = [string]$args[++$i]; continue }
        '^--port$' { WsNeed $args $i; $port = WsCheckPort ([string]$args[++$i]); continue }
        '^(--server|--http)$' { Write-Host "run-port-server: $a is set by this script (see --port)"; exit 2 }
        default {
            $n = WsServerOption $args $i
            if ($n -gt 0) { $i += $n - 1 } else { $soaArgs += (WsQ $a) }
        }
    }
}
$httpPort = $port + 80
New-Item -ItemType Directory -Force -Path (Join-Path $data "server") | Out-Null
$data = (Resolve-Path $data).Path
$state = Join-Path $data "server"; $slog = Join-Path $data "server.log"; $sout = Join-Path $data "server.out.log"
# --seed: a new server state takes the player of the phone's save, as soa.exe's in-process server
# does with the same data dir (a save without a player is skipped with a warning); a --seed among
# the user's options comes later and wins
WsStartServer $srv $here $sout $slog (@("--listen", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort",
    "--data", (WsQ $state), "--seed", (WsQ (Join-Path $data "data\shared_prefs\Game.xml"))) + $WsSrvArgs)
Write-Host "== soa-server (pid $($WsServer.Id)): game 127.0.0.1:$port, http 127.0.0.1:$httpPort; state $state, log $slog"
try {
    WsWaitReady
    Write-Host "== soa --server 127.0.0.1:$port; data $data"
    exit (WsRunClient $soa $here (@("--data", (WsQ $data), "--server", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort") + $soaArgs))
} finally {
    WsStop
}
