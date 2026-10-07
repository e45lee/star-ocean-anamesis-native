# The Windows server-plus-client launchers' shared half (Windows PowerShell 5.1; dot-source it:
# `. (Join-Path $PSScriptRoot "lib\with-server.ps1")`): the PowerShell twin of scripts/lib/with-server.sh,
# with the same server options. soa-server.exe started, waited for, and stopped with the client, also
# on Ctrl+C or when the window is closed (the caller's try / finally: WsStop).
# Used by scripts/windows/run-emulator-370.ps1 and the release packages' run-emulator.ps1 /
# run-port-server.ps1 (shipped beside them as lib\with-server.ps1, tools/package.py).
#
#   WsInit NAME                    the launcher's name for messages
#   WsServerOption ARGS I          ARGS[I] is one of the server options the launchers pass on to
#                                  soa-server: appends it (and its value, quoted; a path made
#                                  absolute from the caller's directory) to $WsSrvArgs and returns
#                                  the number of arguments used; else 0
#   WsNeed ARGS I                  exits 2 unless the option ARGS[I] has a value
#   WsCheckPort N                  exits 2 unless N is a port number (returns it as an int)
#   WsQ S                          S quoted for Start-Process's command line (it joins with spaces)
#   WsStartServer EXE DIR OUT ERR ARGS
#                                  EXE ARGS in DIR, its standard output into OUT, its standard error
#                                  (soa-server's log) into ERR; sets $WsServer
#   WsWaitReady                    until soa-server prints its "ready" line (the first start decrypts
#                                  the master and indexes the download: up to a minute; four at most);
#                                  exits 1 when it stops first or serves no CDN
#   WsRunClient EXE DIR ARGS       the client; returns its exit code
#   WsStop                         stops the client and the server (for the caller's finally)
#
# The server's lines read here (tools/server_log_patterns.txt): "soa-server: game ...", then
# "soa-server: CDN ..." when it has a download, then "soa-server: ready".

$WsName = "launcher"
$WsSrvArgs = @()
$WsServer = $null
$WsClient = $null
$WsServerLogs = @()

function WsInit([string]$name) { $script:WsName = $name }

# Start-Process joins its arguments with spaces: quote the ones that need it
function WsQ([string]$s) {
    if ($s -eq "" -or $s -match '[\s"]') { '"' + ($s -replace '(\\*)"', '$1$1\"' -replace '(\\+)$', '$1$1') + '"' } else { $s }
}

function WsFull([string]$p) { if ([System.IO.Path]::IsPathRooted($p)) { $p } else { Join-Path (Get-Location).Path $p } }

function WsNeed([object[]]$argv, [int]$i) {
    if ($i + 1 -ge $argv.Count) { Write-Host "${WsName}: $($argv[$i]) needs a value"; exit 2 }
}

function WsServerOption([object[]]$argv, [int]$i) {
    $a = [string]$argv[$i]
    switch -regex ($a) {
        '^(--new-player|--galaxy-pass|--enable-events|--restore-tower|--english|--surprise)$' {
            $script:WsSrvArgs += $a; return 1 }
        '^(--seed|--download|--download-dir|--master|--db|--log-packets|--campaign-master-db)$' {  # paths
            WsNeed $argv $i
            $script:WsSrvArgs += $a; $script:WsSrvArgs += (WsQ (WsFull ([string]$argv[$i + 1]))); return 2 }
        '^(--seed-rng|--clock|--start-coins|--stamina-heal-time|--event-keywords|--fail|--campaign-seed)$' {
            WsNeed $argv $i
            $script:WsSrvArgs += $a; $script:WsSrvArgs += (WsQ ([string]$argv[$i + 1])); return 2 }
    }
    return 0
}

function WsCheckPort([string]$n) {
    if ($n -notmatch '^[0-9]+$') { Write-Host "${WsName}: --port takes a number"; exit 2 }
    $p = [int]$n
    if ($p -lt 1 -or $p -gt 65455) { Write-Host "${WsName}: --port takes 1..65455 (its HTTP port is N+80)"; exit 2 }
    return $p
}

function WsStartServer([string]$exe, [string]$dir, [string]$out, [string]$err, [object[]]$argList) {
    Remove-Item -Force -ErrorAction SilentlyContinue $out, $err
    $script:WsServerLogs = @($out, $err)
    $script:WsServer = Start-Process -FilePath $exe -WorkingDirectory $dir -NoNewWindow -PassThru `
        -RedirectStandardOutput $out -RedirectStandardError $err -ArgumentList $argList
    $null = $script:WsServer.Handle  # (keeps the exit code readable)
}

function WsWaitReady {
    $err = $WsServerLogs[1]
    $up = $false
    for ($t = 0; $t -lt 480; $t++) {
        if ((Test-Path $err) -and (Select-String -Path $err -Pattern '^soa-server: ready' -Quiet)) { $up = $true; break }
        if ($WsServer.HasExited) { break }
        Start-Sleep -Milliseconds 500
    }
    if (-not $up) {
        Write-Host "${WsName}: soa-server didn't start (see README.txt); log: $err"
        if (Test-Path $err) { Get-Content $err -Tail 5 }
        exit 1
    }
    # (the CDN line comes before the ready line)
    if (-not (Select-String -Path $err -Pattern '^soa-server: CDN' -Quiet)) {
        Write-Host "${WsName}: soa-server found no 3.7.0 download (see README.txt); log: $err"; exit 1
    }
}

function WsRunClient([string]$exe, [string]$dir, [object[]]$argList) {
    $script:WsClient = Start-Process -FilePath $exe -WorkingDirectory $dir -NoNewWindow -PassThru -ArgumentList $argList
    $null = $script:WsClient.Handle
    $script:WsClient.WaitForExit()
    return $script:WsClient.ExitCode
}

function WsStop {
    if ($WsClient -and -not $WsClient.HasExited) { Stop-Process -Id $WsClient.Id -Force -ErrorAction SilentlyContinue }
    if ($WsServer -and -not $WsServer.HasExited) { Stop-Process -Id $WsServer.Id -Force -ErrorAction SilentlyContinue }
}
