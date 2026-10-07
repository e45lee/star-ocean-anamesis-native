#!/bin/bash
# The smoke test's screens on the 3.7.0 emulator: the reference check of the port's smoke
# baselines (port/scripts/smoke.py, tests/smoke-base). soa-emu runs the same 3.7.0 client
# under the JIT with no natives against a soa-server with the same state (the seed save,
# --seed-rng 1, the clock at SMOKE_CLOCK), and is driven through the same screens with the same
# taps: title -> Login -> the data check -> the notice board and the LOGIN BONUS -> home ->
# キャラクター -> 装備・技・アシスト変更 -> a character -> 戻る -> ホーム -> その他. Each screen waits
# (up to EMU_STEP_TIMEOUT s, default 90) until it matches the baseline's (RMSE <= the smoke's
# limits), and the best RMSE per screen is reported. They are the same client, so the screens
# should match up to animation (the home character's idle motion, the mascot's line).
#
# Usage: port/scripts/smoke_vs_emu.sh <out-dir> [baseline-dir]   (from any directory)
#   SOA_PHONE       the phone (port/scripts/phone370.sh: default the shared pre-downloaded one,
#                   linked into OUT/emu, deleted after)
#   SMOKE_CLOCK     the server clock (default 2026-09-30 12:00:00, as smoke.py)
# Output: OUT/NN-name.png, OUT/rmse.txt, OUT/strip.png (the emulator's row over the baseline's),
# the logs. Exit 1 when a screen doesn't match. Kills only the processes it started.
set -u
out=${1:?usage: smoke_vs_emu.sh OUT [BASELINE]}
repo=$(cd "$(dirname "$0")/../.." && pwd)
case $out in /*) ;; *) out=$PWD/$out ;; esac
base=${2:-$repo/tests/smoke-base}
case $base in /*) ;; *) base=$PWD/$base ;; esac
cd "$repo"
emu=$repo/build/emulator/soa-emu srv=$repo/build/server/soa-server
clock=${SMOKE_CLOCK:-2026-09-30 12:00:00}
. "$repo/scripts/lib/checkout.sh"
master=$(repo_file "$repo" data/basmaster-3.7.0.sqlite3) || master=$repo/data/basmaster-3.7.0.sqlite3
rm -rf "${out:?}"; mkdir -p "$out/server"
elog=$out/emu.log slog=$out/server.log fifo=$out/fifo
read -r game_port http_port < <(python3 -c '
import socket
s = [socket.socket() for _ in range(2)]
for x in s: x.bind(("127.0.0.1", 0))
print(*[x.getsockname()[1] for x in s])')
# The phone, as smoke.py prepares it (port/scripts/phone370.sh: the shared phone linked, without its
# local KVS), and the client save.
. port/scripts/phone370.sh
phone370_prepare "$out/emu"
phone370_client_save "$out/emu/data/shared_prefs"

spid= epid=
cleanup() {
    for p in $epid $spid; do
        kill -0 "$p" 2>/dev/null || continue
        kill "$p" 2>/dev/null
        for _ in 1 2 3 4 5 6 7 8 9 10; do kill -0 "$p" 2>/dev/null || break; sleep 1; done
        kill -9 "$p" 2>/dev/null
    done
    rm -rf "${out:?}/emu"
}
trap cleanup EXIT
timeout -k 10 1800 "$srv" --listen 127.0.0.1:$game_port --http 127.0.0.1:$http_port --data "$out/server" --master "$master" \
    --download-dir "$repo/work/SOA-3.7.0-canonical-data.zip" --seed-rng 1 --clock "$clock" > "$slog" 2>&1 &
spid=$!
for _ in $(seq 1 120); do grep -q "^soa-server: game" "$slog" 2>/dev/null && break; kill -0 $spid 2>/dev/null || break; sleep 0.5; done
grep -q "^soa-server: game" "$slog" || { echo "FAIL: soa-server didn't start (log: $slog)"; exit 1; }
timeout -k 10 1800 "$emu" --data "$out/emu" --headless --size 729x1296 --control "$fifo" \
    --server 127.0.0.1:$game_port --http 127.0.0.1:$http_port > "$elog" 2>&1 &
epid=$!
while [ ! -p "$fifo" ]; do sleep 1; kill -0 $epid 2>/dev/null || { echo "FAIL: soa-emu exited (log $elog)"; exit 1; }; done

ctl() { python3 control/soactl.py --timeout 120 "$fifo" "$@" > /dev/null 2>&1; }
fails=0
: > "$out/rmse.txt"
# screen NAME LIMIT: wait until the emulator's screen matches the baseline's; the best RMSE.
screen() {
    local name=$1 limit=$2 best=1 d end=$(( $(date +%s) + ${EMU_STEP_TIMEOUT:-90} ))
    while :; do
        ctl "shot:$out/probe.png"
        if [ -f "$out/probe.png" ]; then
            d=$(compare -metric RMSE -resize 182x324 "$out/probe.png" "$base/$name.png" null: 2>&1 | sed 's/.*(\(.*\))/\1/')
            if awk -v d="$d" -v b="$best" 'BEGIN { exit !(d < b) }'; then best=$d; cp "$out/probe.png" "$out/$name.png"; fi
            awk -v d="$d" -v l="$limit" 'BEGIN { exit !(d <= l) }' && break
        fi
        [ "$(date +%s)" -lt $end ] || break
        sleep 1
    done
    rm -f "$out/probe.png"
    if awk -v d="$best" -v l="$limit" 'BEGIN { exit !(d <= l) }'; then echo "ok   $name rmse=$best" | tee -a "$out/rmse.txt"
    else echo "FAIL $name rmse=$best (limit $limit)" | tee -a "$out/rmse.txt"; fails=$((fails + 1)); fi
}

# The title (after the server answered NoLoginStart), TAP TO START until Login.
for _ in $(seq 1 300); do grep -q 'request NoLoginStart' "$slog" && break; sleep 1; done
screen 01-title 0.08
python3 control/flowctl.py tap-until "$fifo" "$slog" 'request Login ' 90 10 6 -- tap:364:1000 > /dev/null || { echo "FAIL: no Login"; exit 1; }
# The data check; a download dialog when the phone lacks the server's edited master (ダウンロード,
# then 完了), until home opens the notice board.
for i in $(seq 1 60); do
    grep -q 'ShowWebView(http' "$elog" && break
    [ $i -gt 6 ] && ctl tap:515:800 wait:3000 tap:364:790
    sleep 5
done
python3 control/flowctl.py login-popups "$fifo" "$elog" - - - > "$out/popups.txt" 2>&1 || { echo "FAIL: login popups ($(tail -1 "$out/popups.txt"))"; exit 1; }
screen 02-home 0.12;      ctl wait:500 tap:180:1250
screen 03-charmenu 0.08;  ctl wait:500 tap:364:435
screen 04-charlist 0.08;  ctl wait:500 tap:364:600
screen 05-chardetail 0.08; ctl wait:500 tap:100:1120
screen 06-closed 0.08;    ctl wait:500 tap:60:1250
screen 07-home 0.12;      ctl wait:500 tap:665:1250
screen 08-other 0.08
ctl quit
montage "$out"/0*.png "$base"/0*.png -tile 8x -geometry 182x324+2+2 "$out/strip.png" 2>/dev/null || true
if [ $fails = 0 ]; then echo "PASS: every smoke screen matches on soa-emu"; else echo "FAIL: $fails screens differ on soa-emu"; exit 1; fi
