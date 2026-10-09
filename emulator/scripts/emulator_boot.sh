#!/bin/bash
# Boot check of the 3.7.0 emulator (emulator/README.md "Status"): builds nothing.
#
# Usage: emulator/scripts/emulator_boot.sh [soa-emu binary] [out dir] [extra soa-emu args...]
#   defaults: build/emulator/soa-emu (the repository build: scripts/build.sh), a fresh mktemp dir (kept; the log, screenshots and data are there)
#
# Runs soa-emu headless in a scratch data dir with no server and checks that the unmodified 3.7.0
# client reaches its network path:
#   1. the title phase sends NoLoginStart: the client resolves production-game.so-ana.com
#      (log: "getaddrinfo(production-game.so-ana.com"; soa-emu maps it to --server's host);
#   2. that fails (nothing listens on --server's port: connection refused) and the
#      communication-error dialog opens
#      (通信エラーが発生しました, error 1003: the screenshot's dialog band, on black);
#   3. tapping リトライ (Retry) goes back to the network (a second connection attempt) and the
#      dialog opens again.
# Prints PASS or FAIL (exit 0 / 1). Kills only the soa-emu it started.
set -u
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../.." && pwd)
bin=${1:-$repo/build/emulator/soa-emu}
out=${2:-$(mktemp -d "${TMPDIR:-/tmp}/emulator-boot.XXXXXX")}
shift $(( $# > 2 ? 2 : $# ))
soactl="$repo/control/soactl.py"
[ -x "$bin" ] || { echo "FAIL: $bin not built (scripts/build.sh --target soa-emu)"; exit 1; }
mkdir -p "$out/data"
log=$out/log.txt fifo=$out/fifo
W=729 H=1296            # the window; tap coordinates are window pixels
RETRY="364:713"         # the dialog's リトライ button
MAX_RSS_KB=$((6 * 1024 * 1024))

t0=$(date +%s%N)
elapsed() { awk -v a="$t0" -v b="$(date +%s%N)" 'BEGIN { printf "%.1f", (b - a) / 1e9 }'; }

# No server: the client's server address (soa-emu --server, default 127.0.0.1:44300) is moved to a
# free port nothing listens on, so a soa-server another session runs can't answer.
free_port=$("$repo/tools/py" -c 'import socket; s = socket.socket(); s.bind(("127.0.0.1", 0)); print(s.getsockname()[1])')
# The machine-wide game slot pool (control/soaslot.sh): one slot for this script's client, held
# until the script exits; queued here when the machine is full.
SOASLOT_PY="$repo/control/soaslot.py"; . "$repo/control/soaslot.sh"; soaslot_take "emulator_boot.sh"
timeout -k 10 600 "$bin" --data "$out/data" --headless --size ${W}x$H --control "$fifo" --server 127.0.0.1:$free_port "$@" > "$log" 2>&1 &
pid=$!
cleanup() {
    if kill -0 "$pid" 2>/dev/null; then
        kill "$pid" 2>/dev/null
        for _ in 1 2 3 4 5 6 7 8 9 10; do kill -0 "$pid" 2>/dev/null || break; sleep 1; done
        kill -9 "$pid" 2>/dev/null
    fi
}
trap cleanup EXIT
fail() { echo "FAIL: $* (log: $log)"; exit 1; }

# Polls until "$@" succeeds; fails after $limit seconds or when soa-emu dies / grows too big.
wait_for() {
    local what=$1 limit=$2; shift 2
    local end=$(( $(date +%s) + limit ))
    while ! "$@"; do
        kill -0 "$pid" 2>/dev/null || fail "soa-emu exited while waiting for $what"
        local rss
        rss=$(ps -o rss= --ppid "$pid" 2>/dev/null | sort -n | tail -1)
        [ -n "$rss" ] && [ "$rss" -gt $MAX_RSS_KB ] && fail "soa-emu above 6 GB RSS"
        [ "$(date +%s)" -lt $end ] || fail "timed out after ${limit}s waiting for $what"
        sleep 1
    done
}

lookups() { grep -c 'getaddrinfo(production-game.so-ana.com' "$log" 2>/dev/null || true; }
lookups_above() { [ "$(lookups)" -gt "$1" ]; }
# A network attempt: a lookup of the game server, or (once the name resolved: the client keeps
# the address) a connection to its port 443.
attempts() { grep -c 'getaddrinfo(production-game.so-ana.com\|connect(fd [0-9]*): port 443 ' "$log" 2>/dev/null || true; }
attempts_above() { [ "$(attempts)" -gt "$1" ]; }

# The communication-error dialog: the dialog's band across the middle of the screen
# (rows 505 and 620 at x=364: dark teal / dark slate) over the black background (rows 300, 970).
is_error_dialog() {
    "$repo/tools/py" - "$1" <<'EOF'
import struct, sys, zlib
d = open(sys.argv[1], 'rb').read()
i, idat = 8, b''
while i < len(d):
    n, = struct.unpack('>I', d[i:i + 4]); t = d[i + 4:i + 8]; c = d[i + 8:i + 8 + n]
    if t == b'IHDR': w, h = struct.unpack('>II', c[:8])
    if t == b'IDAT': idat += c
    i += 12 + n
raw = zlib.decompress(idat); st = w * 3 + 1  # soa writes filter-0 RGB rows
px = lambda x, y: raw[y * st + 1 + x * 3:y * st + 4 + x * 3]
dark = lambda p: max(p) < 16
band = px(364, 505); panel = px(364, 620)
ok = dark(px(364, 300)) and dark(px(364, 970)) and band[2] > 60 and band[2] > band[0] + 40 and 10 < panel[2] < 80
sys.exit(0 if ok else 1)
EOF
}
dialog_shown() {
    local shot=$out/$1.png
    rm -f "$shot"
    "$repo/tools/py" "$soactl" --timeout 30 "$fifo" "shot:$shot" > /dev/null 2>&1 || return 1
    is_error_dialog "$shot"
}

# 1. The title's NoLoginStart reaches the network.
wait_for "the client's first server lookup" 240 lookups_above 0
t_net=$(elapsed)
# 2. The communication-error dialog.
wait_for "the communication-error dialog" 120 dialog_shown error1
t_dialog=$(elapsed)
# 3. Retry: back to the network, and the dialog again.
n=$(attempts)
"$repo/tools/py" "$soactl" --timeout 30 "$fifo" "tap:$RETRY" > /dev/null || fail "control FIFO"
wait_for "the retry's connection attempt" 60 attempts_above "$n"
wait_for "the dialog after the retry" 60 dialog_shown error2
t_retry=$(elapsed)

"$repo/tools/py" "$soactl" --timeout 10 "$fifo" quit > /dev/null 2>&1
warnings=$(grep -c '^W/jni\|^W/loader' "$log" || true)
echo "network path at ${t_net}s, error dialog at ${t_dialog}s, retry -> dialog again at ${t_retry}s; JVM/HLE warnings: $warnings"
echo "screenshots: $out/error1.png $out/error2.png"
echo "PASS"
