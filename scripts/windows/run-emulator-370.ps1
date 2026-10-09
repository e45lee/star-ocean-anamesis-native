# Runs the original 3.7.0 online client, unmodified, in the emulator on Windows
# (build-win\emulator\soa-emu.exe) against soa-server.exe, which this script starts and stops.
# The Windows twin of scripts/run-emulator-370.sh (README.md "Windows").
#
# Usage: scripts\windows\run-emulator-370.cmd [options] [soa-emu options...]
#   -Home DIR / --home DIR   data: DIR\phone (the client), DIR\server (the server's state),
#                            DIR\server.log + server.log.err (default %LOCALAPPDATA%\soa\emulator-370:
#                            DIR\phone is soa-emu.exe's own default)
#   --port N                 the game port (default 44300; HTTP: N + 80)
#   soa-server's options, as scripts/run-emulator-370.sh takes them (scripts/lib/with-server.ps1):
#     --new-player, --seed FILE, --seed-rng N, --clock "YYYY-MM-DD HH:MM:SS", --start-coins N, --gacha-surprise PCT,
#     --galaxy-pass, --enable-events, --event-keywords W, --restore-tower, --surprise,
#     --stamina-heal-time S, --fail SPEC, --download PATH, --download-dir DIR, --master FILE,
#     --db FILE, --log-packets DIR, --campaign-master-db FILE, --campaign-seed N, --english
#   the others go to soa-emu.exe (e.g. --fullscreen, --headless)
# The first start downloads about 3 GB of game data from the local server.
# Needs: build-win\ (scripts/build.sh --windows), work\libSOA-3.7.0.so, the 3.7.0 APK in apk\,
# data\basmaster-3.7.0.sqlite3 and the 3.7.0 download for the server,
# work\SOA-3.7.0-canonical-data.zip (read in place; README.md "Game files").
$ErrorActionPreference = "Stop"
$repo = (Resolve-Path (Join-Path $PSScriptRoot "..\..")).Path
. (Join-Path $repo "scripts\lib\with-server.ps1")
WsInit "run-emulator-370"
$emu = Join-Path $repo "build-win\emulator\soa-emu.exe"
$srv = Join-Path $repo "build-win\server\soa-server.exe"
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
foreach ($f in @($emu, $srv)) {
    if (-not (Test-Path $f)) { Write-Error "run-emulator-370: $f isn't built; run scripts/build.sh --windows" }
}
foreach ($f in @("work\libSOA-3.7.0.so", "apk\STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk", "data\basmaster-3.7.0.sqlite3")) {
    if (-not (Test-Path (Join-Path $repo $f))) { Write-Error "run-emulator-370: $f is missing; see README.md" }
}
# the download: the zip, read in place (a --download / --download-dir among the options comes later and wins)
$download = Join-Path $repo "work\SOA-3.7.0-canonical-data.zip"
if (-not (Test-Path $download)) { Write-Error "run-emulator-370: the 3.7.0 download, work\SOA-3.7.0-canonical-data.zip, is missing; see README.md" }
$phone = Join-Path $home_dir "phone"; $state = Join-Path $home_dir "server"; $slog = Join-Path $home_dir "server.log"
New-Item -ItemType Directory -Force -Path $phone, $state | Out-Null
Write-Host "== starting soa-server (game 127.0.0.1:$port, http 127.0.0.1:$httpPort; data $state)"
WsStartServer $srv $repo $slog "$slog.err" (@("--listen", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort",
    "--data", (WsQ $state), "--download-dir", (WsQ $download)) + $WsSrvArgs)
try {
    WsWaitReady
    Write-Host "== starting soa-emu (phone data $phone)"
    exit (WsRunClient $emu $repo (@("--data", (WsQ $phone), "--server", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort") + $emuArgs))
} finally {
    WsStop
}
