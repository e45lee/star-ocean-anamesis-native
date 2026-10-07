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
#   server options, passed to soa-server.exe (they set the server's rules and state):
#     --new-player, --seed FILE, --seed-rng N, --clock "YYYY-MM-DD HH:MM:SS", --start-coins N,
#     --galaxy-pass, --enable-events, --event-keywords L, --restore-tower, --download PATH,
#     --master FILE, --log-packets DIR, --english (the English files: with --lang en
#     for soa, the English game)
#   any other options go to soa.exe, e.g. --fullscreen, --size 729x1296, --apk FILE (soa.exe --help)
$ErrorActionPreference = "Stop"
$here = $PSScriptRoot
$soa = Join-Path $here "soa.exe"
$srv = Join-Path $here "soa-server.exe"
$local = if ($env:LOCALAPPDATA) { $env:LOCALAPPDATA } else { Join-Path $env:USERPROFILE "AppData\Local" }
$data = Join-Path $local "soa\port-370"
$port = 44310
$srvArgs = @(); $soaArgs = @()
# Start-Process joins its arguments with spaces: quote the ones that need it
function Q([string]$s) { if ($s -eq "" -or $s -match '[\s"]') { '"' + ($s -replace '(\\*)"', '$1$1\"' -replace '(\\+)$', '$1$1') + '"' } else { $s } }
function Full([string]$p) { if ([System.IO.Path]::IsPathRooted($p)) { $p } else { Join-Path (Get-Location).Path $p } }
for ($i = 0; $i -lt $args.Count; $i++) {
    $a = [string]$args[$i]
    $hasValue = $i + 1 -lt $args.Count
    switch -regex ($a) {
        '^(-h|--help)$' { Get-Content $PSCommandPath | Where-Object { $_ -match '^#' } | ForEach-Object { $_ -replace '^# ?', '' }; exit 0 }
        '^--data$' { if (-not $hasValue) { Write-Host "run-port-server: $a needs a value"; exit 2 }; $data = [string]$args[++$i]; continue }
        '^--port$' { if (-not $hasValue) { Write-Host "run-port-server: $a needs a value"; exit 2 }; $port = [int]$args[++$i]; continue }
        '^(--new-player|--galaxy-pass|--enable-events|--restore-tower|--english)$' { $srvArgs += $a; continue }
        '^(--seed|--download|--download-dir|--master|--log-packets)$' {
            if (-not $hasValue) { Write-Host "run-port-server: $a needs a value"; exit 2 }
            # paths: from the caller's directory
            $srvArgs += $a; $srvArgs += (Q (Full ([string]$args[++$i]))); continue }
        '^(--seed-rng|--clock|--start-coins|--event-keywords)$' {
            if (-not $hasValue) { Write-Host "run-port-server: $a needs a value"; exit 2 }
            $srvArgs += $a; $srvArgs += (Q ([string]$args[++$i])); continue }
        '^(--server|--http)$' { Write-Host "run-port-server: $a is set by this script (see --port)"; exit 2 }
        default { $soaArgs += (Q $a) }
    }
}
$httpPort = $port + 80
New-Item -ItemType Directory -Force -Path (Join-Path $data "server") | Out-Null
$data = (Resolve-Path $data).Path
$state = Join-Path $data "server"; $slog = Join-Path $data "server.log"; $sout = Join-Path $data "server.out.log"
Remove-Item -Force -ErrorAction SilentlyContinue $slog, $sout
# --seed: a new server state takes the player of the phone's save, as soa.exe's in-process server
# does with the same data dir (a save without a player is skipped with a warning); a --seed among
# the user's options comes later and wins
$sp = Start-Process -FilePath $srv -WorkingDirectory $here -NoNewWindow -PassThru -RedirectStandardOutput $sout `
    -RedirectStandardError $slog -ArgumentList (@("--listen", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort",
    "--data", (Q $state), "--seed", (Q (Join-Path $data "data\shared_prefs\Game.xml"))) + $srvArgs)
$null = $sp.Handle  # (keeps the exit code readable)
Write-Host "== soa-server (pid $($sp.Id)): game 127.0.0.1:$port, http 127.0.0.1:$httpPort; state $state, log $slog"
$ep = $null
try {
    $up = $false
    for ($t = 0; $t -lt 480; $t++) {
        if ((Test-Path $slog) -and (Select-String -Path $slog -Pattern '^soa-server: ready' -Quiet)) { $up = $true; break }
        if ($sp.HasExited) { break }
        Start-Sleep -Milliseconds 500
    }
    if (-not $up) {
        Write-Host "run-port-server: soa-server didn't start (see README.txt); log: $slog"
        if (Test-Path $slog) { Get-Content $slog -Tail 5 }
        exit 1
    }
    # (the CDN line comes before the ready line: scripts/lib/with-server.sh)
    if (-not (Select-String -Path $slog -Pattern '^soa-server: CDN' -Quiet)) {
        Write-Host "run-port-server: soa-server found no 3.7.0 download (see README.txt); log: $slog"; exit 1
    }
    $ep = Start-Process -FilePath $soa -WorkingDirectory $here -NoNewWindow -PassThru -ArgumentList (@("--data", (Q $data),
        "--server", "127.0.0.1:$port", "--http", "127.0.0.1:$httpPort") + $soaArgs)
    $null = $ep.Handle
    Write-Host "== soa (pid $($ep.Id)) --server 127.0.0.1:$port; data $data"
    $ep.WaitForExit()
    exit $ep.ExitCode
} finally {
    if ($ep -and -not $ep.HasExited) { Stop-Process -Id $ep.Id -Force -ErrorAction SilentlyContinue }
    if (-not $sp.HasExited) { Stop-Process -Id $sp.Id -Force -ErrorAction SilentlyContinue }
}
