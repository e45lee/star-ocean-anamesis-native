#!/bin/bash
# One co-op client for the prototype (docs/multiplayer/prototype/README.md): its own soa-server
# (multiplayer opened by MP_STUDY_OPEN, see README "The server patch") and a headless soa-emu whose
# lobby connections go to the prototype's lobby port. Logs in, closes the login popups, opens the
# mission map of planet Mere and the mission detail of 1-05, then HOLDS: drive it through
# OUT/fifo with control/soactl.py (mp_drive.sh has the taps) until OUT/HOLD is deleted.
#
# Usage: mp_client.sh OUT LOBBY_PORT [STATE_DB]
#   OUT         a new directory (logs, packets, screenshots, the server state, the phone)
#   LOBBY_PORT  the prototype's --lobby-port
#   STATE_DB    optional: a soa-server state DB to start from (copied to OUT/server/), e.g. player 2's
#               (make_player2.sh); default: a new state seeded with LOCAL00001
# Env: SOA_EMU, SOA_SERVER (default build/emulator/soa-emu, build/server/soa-server; the server must
#      have open-multiplay.patch applied, README "Running it"), MASTER, DOWNLOAD (default
#      data/basmaster-3.7.0.sqlite3, work/download-3.7.0), SOA_PHONE as emulator_session.sh.
# Every process it starts is killed when it exits (by PID).
set -u
out=${1:?OUT}; lobby_port=${2:?LOBBY_PORT}; state_db=${3:-}
here=$(cd "$(dirname "$0")" && pwd)
repo=$(cd "$here/../../.." && pwd)
emu=${SOA_EMU:-$repo/build/emulator/soa-emu}
srv=${SOA_SERVER:-$repo/build/server/soa-server}
master=${MASTER:-$repo/data/basmaster-3.7.0.sqlite3}
download=${DOWNLOAD:-$repo/work/download-3.7.0}
soactl=$repo/control/soactl.py flowctl=$repo/control/flowctl.py
mkdir -p "$out/server" "$out/packets"
[ -n "$state_db" ] && cp "$state_db" "$out/server/server.sqlite3"
. "$repo/scripts/shared-phone.sh"
shared_phone_resolve "$repo"
if [ -n "${SOA_PHONE:-}" ]; then shared_phone_link "$SOA_PHONE" "$out/emu" || exit 1; else mkdir -p "$out/emu"; fi
read -r game_port http_port < <(python3 -c '
import socket
s = [socket.socket() for _ in range(2)]
for x in s: x.bind(("127.0.0.1", 0))
print(*[x.getsockname()[1] for x in s])')
elog=$out/emu.log slog=$out/server.log plog=$out/packets/packets.log fifo=$out/fifo
spid= epid=
cleanup() {
    for p in $epid $spid; do kill "$p" 2>/dev/null; done
    sleep 2
    for p in $epid $spid; do kill -9 "$p" 2>/dev/null; done
}
trap cleanup EXIT
MP_STUDY_OPEN=1 timeout -k 10 3600 "$srv" --listen 127.0.0.1:$game_port --http 127.0.0.1:$http_port \
    --data "$out/server" --master "$master" --download-dir "$download" --log-packets "$out/packets" \
    --seed-rng 1 --campaign-seed mf01_001 > "$slog" 2>&1 &
spid=$!
for _ in $(seq 1 120); do grep -q "^soa-server: game" "$slog" 2>/dev/null && break; sleep 0.5; done
timeout -k 10 3600 "$emu" --data "$out/emu" --headless --size 729x1296 --control "$fifo" \
    --server 127.0.0.1:$game_port --lobby 127.0.0.1:$lobby_port --http 127.0.0.1:$http_port > "$elog" 2>&1 &
epid=$!
echo "client: soa-server $spid, soa-emu $epid, fifo $fifo"
ctl() { python3 "$soactl" --timeout 60 "$fifo" "$@" > /dev/null 2>&1; }
until_do() {  # until_do SECONDS TAP PATTERN FILE: tap every 4 s until PATTERN is in FILE
    local end=$(( $(date +%s) + $1 )) next=0
    while ! grep -q -- "$3" "$4" 2>/dev/null; do
        kill -0 $epid 2>/dev/null || { echo "FAIL: soa-emu exited"; exit 1; }
        [ "$(date +%s)" -lt $end ] || { echo "FAIL: $3 not within $1 s"; exit 1; }
        if [ -n "$2" ] && [ "$(date +%s)" -ge $next ]; then ctl "tap:$2"; next=$(( $(date +%s) + 4 )); fi
        sleep 1
    done
}
until_do 150 "" "< NoLoginStartRes" "$plog"
sleep 5
until_do 120 364:713 "< ResultStart" "$plog"
until_do 60 "" "< GetPlayerRes" "$plog"
sleep 8
# home: the small download dialog's buttons, if any, until the notice board (ShowWebView)
end=$(( $(date +%s) + 300 )) i=0
while ! grep -q "ShowWebView(http" "$elog"; do
    [ "$(date +%s)" -lt $end ] || { echo "FAIL: home"; exit 1; }
    case $((i % 3)) in 0) ctl tap:364:1043;; 1) ctl tap:515:800;; 2) ctl tap:364:790;; esac
    i=$((i + 1)); sleep 6
done
python3 "$flowctl" login-popups "$fifo" "$elog" "$out/notice.png" "$out/login-bonus.png" "$out/home.png" > "$out/popups.txt" 2>&1
n=$(grep -c "> GetMissionList" "$plog")
end=$(( $(date +%s) + 60 )) next=0
while [ "$(grep -c "< GetMissionListRes" "$plog")" -le "$n" ]; do
    [ "$(date +%s)" -lt $end ] || { echo "FAIL: mission select"; exit 1; }
    if [ "$(date +%s)" -ge $next ]; then ctl tap:270:1085; next=$(( $(date +%s) + 4 )); fi
    sleep 1
done
ctl wait:6000 "shot:$out/planets.png"
bright=$(convert "$out/planets.png" -crop 120x60+527+750 -colorspace gray -format '%[fx:mean > 0.45 ? 1 : 0]' info: 2>/dev/null)
[ "$bright" = 1 ] && ctl tap:660:520 wait:3000 tap:587:795 wait:7000
ctl tap:363:665 wait:4000 "shot:$out/mission-detail.png"
echo "HOLD: drive via $fifo; rm $out/HOLD to stop"
touch "$out/HOLD"
while [ -e "$out/HOLD" ] && kill -0 $epid 2>/dev/null; do sleep 2; done
python3 "$soactl" --timeout 10 "$fifo" quit > /dev/null 2>&1
