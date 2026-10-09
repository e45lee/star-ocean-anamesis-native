# Shared by viewer_boot.sh and viewer_session.sh (sourced, not run): start soa-viewer headless,
# drive it through its control FIFO (control/soactl.py: taps and screenshots only; the viewer
# has no natives, so no phase: / call: commands) and check screens against the reference
# screenshots in emulator-viewer/scripts/ref/ (182x324, RMSE as port/scripts/smoke.py).
#
# The caller sets: out (the output dir). Optional env: VIEWER_DATA (the phone's data dir; default
# a fresh $out/phone, deleted at the end unless KEEP_DATA=1), VIEWER_RECORD=1 (record the
# references that are missing: delete ref/NAME.png to re-record it), VIEWER_RMSE (the match
# threshold, default 0.08).
set -u
here=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
repo=$(cd "$here/../.." && pwd)
soactl="$repo/control/soactl.py"
refdir="$here/ref"
W=729 H=1296            # the window; tap coordinates are window pixels
MAX_RSS_KB=$((6 * 1024 * 1024))
RMSE_MAX=${VIEWER_RMSE:-0.08}
record=${VIEWER_RECORD:-0}
command -v compare > /dev/null || { echo "FAIL: ImageMagick's compare isn't installed"; exit 1; }

vpid= results=() failed=0
t0=$(date +%s)
elapsed() { echo $(( $(date +%s) - t0 )); }

# start_viewer BIN [extra soa-viewer args...]: headless, its own data dir, the control FIFO.
# A Windows BIN (build-win/emulator-viewer/soa-viewer.exe; README.md "Windows") runs the staged copy
# in $SOA_WIN_STAGE (default /mnt/c/soa-win: scripts/windows-stage.sh --viewer stages the XAPK in apk/) from
# there, with its phone on the Windows drive and the TCP control channel (control/soadrive/winhost.py).
win=0
start_viewer() {
    local bin=$1; shift
    [ -x "$bin" ] || { echo "FAIL: $bin not built (scripts/build.sh --target soa-viewer)"; exit 1; }
    phone=${VIEWER_DATA:-$out/phone}
    mkdir -p "$phone" "$out/shots"
    log=$out/viewer.log fifo=$out/fifo
    rm -f "$fifo"
    # the machine-wide game slot pool (control/soaslot.sh): held until the script exits
    SOASLOT_PY="$repo/control/soaslot.py"; . "$repo/control/soaslot.sh"; soaslot_take soa-viewer
    if [[ $bin == *.exe ]]; then
        win=1
        local py=("$repo/tools/py" -c 'import sys; from soadrive import winhost as w; print(eval(sys.argv[1]))')
        bin=$("${py[@]}" "w.staged_binary('$bin')") || { echo "FAIL: $bin not staged"; exit 1; }
        ls "${SOA_WIN_STAGE:-/mnt/c/soa-win}"/apk/*.xapk > /dev/null 2>&1 || [ -d "${SOA_WIN_STAGE:-/mnt/c/soa-win}/work/extracted/xapk" ] ||
            { echo "FAIL: the XAPK isn't staged (scripts/windows-stage.sh --viewer)"; exit 1; }
        [ -n "${VIEWER_DATA:-}" ] || phone=$("${py[@]}" "w.local_dir('$phone')")
        # port 0: the viewer picks one and logs it (in mirrored networking a port tried from WSL
        # stays refused to Windows for a while: soadrive/proc.py free_ports)
        (cd "${SOA_WIN_STAGE:-/mnt/c/soa-win}" && exec timeout -k 10 "${VIEWER_TIMEOUT:-1800}" "$bin" --data "$(wslpath -w "$phone")" \
            --headless --size ${W}x$H --control tcp:127.0.0.1:0 "$@") > "$log" 2>&1 &
        vpid=$!
        local port=
        for _ in $(seq 1 240); do
            port=$("${py[@]}" "w.control_port('$log') or ''")
            [ -n "$port" ] && break
            kill -0 "$vpid" 2>/dev/null || break
            sleep 0.5
        done
        fifo=tcp:127.0.0.1:${port:-0}
    else
        timeout -k 10 "${VIEWER_TIMEOUT:-1800}" "$bin" --data "$phone" --headless --size ${W}x$H --control "$fifo" "$@" > "$log" 2>&1 &
        vpid=$!
    fi
    trap cleanup EXIT
}
cleanup() {
    if [ -n "$vpid" ] && kill -0 "$vpid" 2>/dev/null; then
        kill "$vpid" 2>/dev/null
        for _ in 1 2 3 4 5 6 7 8 9 10; do kill -0 "$vpid" 2>/dev/null || break; sleep 1; done
        kill -9 "$vpid" 2>/dev/null
    fi
    if [ -z "${VIEWER_DATA:-}" ] && [ "${KEEP_DATA:-0}" != 1 ] && [ -d "$out/phone" ]; then
        # (a Windows run's phone: $out/phone links to it on the Windows drive)
        [ -L "$out/phone" ] && rm -rf "$(readlink -f "$out/phone")" && rm -f "$out/phone"
        rm -rf "${out:?}/phone"
    fi
}
alive() {
    kill -0 "$vpid" 2>/dev/null || { echo "soa-viewer exited"; return 1; }
    local rss
    rss=$(ps -o rss= --ppid "$vpid" 2>/dev/null | sort -n | tail -1)
    [ -z "$rss" ] || [ "$rss" -le $MAX_RSS_KB ] || { echo "soa-viewer above 6 GB RSS"; return 1; }
}
ctl() {
    if [ "$win" = 1 ]; then "$repo/tools/py" "$soactl" --timeout 60 --windows-paths "$fifo" "$@" > /dev/null 2>&1
    else "$repo/tools/py" "$soactl" --timeout 60 "$fifo" "$@" > /dev/null 2>&1; fi
}
in_log() { grep -q -- "$1" "$log" 2>/dev/null; }
pass() { results+=("PASS  $1 ($(elapsed)s)"); echo "PASS  $1 ($(elapsed)s)"; }
miss() { results+=("FAIL  $1"); echo "FAIL  $1"; failed=1; }
finish() {
    ctl quit
    if grep -qE "Unhandled SIG|\*\*\* host signal" "$log" 2>/dev/null; then miss "soa-viewer crashed (see $log)"; fi
    echo "---"
    printf '%s\n' "${results[@]}"
    local warnings
    warnings=$(grep -c '^W/jni\|^W/loader\|^W/hle' "$log" 2>/dev/null || true)
    echo "log: $log; screenshots in $out/shots; JVM/loader/HLE warnings: $warnings"
    if [ $failed = 0 ]; then echo "PASS"; exit 0; fi
    echo "FAIL"; exit 1
}

# The RMSE (0..1) of screenshot $1 against reference $2, both at 182x324; with $3 = a crop
# geometry in that space (e.g. 182x30+0+294), of that region only.
rmse() {
    local a=$1 b=$2 crop=${3:-}
    local args=(-resize 182x324!)
    [ -n "$crop" ] && args+=(-crop "$crop" +repage)
    local r
    r=$(compare -metric RMSE <(convert "$a" "${args[@]}" png:-) <(convert "$b" "${args[@]}" png:-) null: 2>&1)
    r=${r#*(}; r=${r%)*}
    [[ $r =~ ^[0-9.e-]+$ ]] && echo "$r" || echo 1
}
# matches NAME [CROP]: a fresh screenshot is within RMSE_MAX of ref/NAME.png.
matches() {
    local shot=$out/shots/$1.png
    rm -f "$shot"
    ctl "shot:$shot" || return 1
    [ -s "$shot" ] || return 1
    local r
    r=$(rmse "$shot" "$refdir/$1.png" "${2:-}")
    awk -v r="$r" -v m="$RMSE_MAX" 'BEGIN { exit !(r <= m) }'
}

# reach NAME LIMIT [TAP [CROP]]: waits up to LIMIT seconds until the screen matches ref/NAME.png
# (CROP: compare that region only); with TAP (X:Y), taps there first and again every 5 s while
# the screen doesn't match (a tap during a fade-in is dropped). Records PASS / FAIL for NAME.
# A missing ref/NAME.png with VIEWER_RECORD=1: taps once, waits ${VIEWER_SETTLE:-10} s and saves
# the screen as ref/NAME.png (182x324, 256 colours).
reach() {
    local name=$1 limit=$2 tap=${3:-} crop=${4:-}
    if [ "$record" = 1 ] && [ ! -e "$refdir/$name.png" ]; then
        [ -n "$tap" ] && ctl "tap:$tap"
        sleep "${VIEWER_SETTLE:-10}"
        mkdir -p "$refdir"
        ctl "shot:$out/shots/$name.png"
        convert "$out/shots/$name.png" -resize 182x324! -strip -colors 256 "PNG8:$refdir/$name.png"
        pass "$name (recorded)"
        return 0
    fi
    local end=$(( $(date +%s) + limit )) next=0
    while ! matches "$name" "$crop"; do
        alive > /dev/null || { miss "$name ($(alive))"; finish; }
        [ "$(date +%s)" -lt $end ] || {
            miss "$name (no match within ${limit}s; last RMSE $(rmse "$out/shots/$name.png" "$refdir/$name.png" "$crop"); see $out/shots/$name.png)"
            return 1
        }
        if [ -n "$tap" ] && [ "$(date +%s)" -ge $next ]; then ctl "tap:$tap"; next=$(( $(date +%s) + 5 )); fi
        sleep 1
    done
    pass "$name"
    sleep 1.5  # let it settle before the next tap
}
# wait_log NAME LIMIT PATTERN: waits until the viewer's log has PATTERN.
wait_log() {
    local name=$1 limit=$2 pat=$3
    local end=$(( $(date +%s) + limit ))
    while ! in_log "$pat"; do
        alive > /dev/null || { miss "$name ($(alive))"; finish; }
        [ "$(date +%s)" -lt $end ] || { miss "$name (not in the log within ${limit}s)"; return 1; }
        sleep 1
    done
    pass "$name"
}
