#!/bin/sh
# End-to-end session of the restored online game (the in-process local server: the local server
# emulator, server): boot -> home -> a battle (mf01_001 through the `mission:` /
# `phase:0xf` route) -> the Mission Result screens with the server's EXP, FOL and drops -> home
# -> the gacha screen (`phase:0x11`) -> a 10-draw that debits 紋章石 -> the result -> home.
# Prints "PASS: ..." at the end, or "FAIL: ..." with exit status 1 (a step that isn't reached, the
# battle not cleared, no coins debited or no draw recorded by the server).
# Screenshots at each step go to OUT/shots; the server's state (tools/server_state.py) is dumped
# after boot, after the battle and after the draw (OUT/state-*.txt), and the log is OUT/log.txt.
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/restore_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# The client save is the all-characters test save; the server seeds itself from
# data/saves/seed/Game.xml into a fresh <scratch-dir>/data/server.sqlite3 and writes its player
# summary into the client save before boot. --seed-rng (SEED_RNG, default 1) fixes the server's RNG.
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
HEADLESS=--headless; [ "${WATCH:-0}" != 1 ] || HEADLESS=--windowed  # soa --headless (no window); WATCH=1 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py; REF=work/port-test/smoke-base
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos" "${OUT:?}"/state-*.txt
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
timeout -k 10 1800 "$SOA" $HEADLESS --seed-rng "${SEED_RNG:-1}" --data "$TMP/data" \
  --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
step=boot
trap 'rc=$?; kill $pid 2>/dev/null || true; [ $step = done ] || { echo "FAIL: stopped at step $step"; exit 1; }; exit $rc' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
screen() { python3 $FLOW wait-screen "$TMP/fifo" "$S/$1.png" "$REF/$2.png" "${3:-180}"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
# tapw REGEX TIMEOUT EVERY TRIES -- CMD...: the commands, resent until REGEX is logged (flowctl.py).
tapw() { python3 $FLOW tap-until "$TMP/fifo" "$L" "$@"; }
state() { .venv/bin/python tools/server_state.py "$TMP/data/server.sqlite3" > "$OUT/state-$1.txt"; cat "$OUT/state-$1.txt"; }

# Home differs from the smoke baseline (the server's player: name, rank, stamina, coins, FOL,
# home character), so wait for the log instead of the baseline screen.
# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
step=login; phone370_login "$TMP/fifo" "$L" "$S"
# The restored 3.7.0 login (native/restore/restore370.cpp) opens the notice popup over home (an empty web
# view on the desktop): close it (閉じる). Then the LOGIN BONUS popup of the day's first login (the
# server grants the day on the title's NoLoginStart and reports it again on the Login; the 3.7.0
# login arms the popups): 閉じる. flowctl.py login-popups retries both until they're closed.
step=popups; python3 $FLOW login-popups "$TMP/fifo" "$L" $S/02-notice.png $S/02-login-bonus.png $S/02-home.png
state 1-boot

# Battle: MissionStart (stamina, the party set's own characters) ... MissionEnd (EXP, FOL, drops).
step=battle; c mission:${FLOW_MISSION:-mf01_001} phase:0xf; logw 'port_debug: phase 15 '
c wait:1500 shot:$S/03-battle-loading.png
i=10
while ! grep -q 'mission_end.msgp' "$L" && [ $i -lt 70 ]; do
  c wait:4000 shot:$S/$i-battle.png; i=$((i + 1))
done
logw 'mission_end.msgp' 30
c wait:4000 shot:$S/80-result.png
c wait:4000 shot:$S/81-result.png
i=82
while ! grep -q 'port_debug: phase 4 ' "$L.tail" 2>/dev/null && [ $i -lt 95 ]; do
  c tap:510:1040 wait:4000 shot:$S/$i-result.png; i=$((i + 1))
  sed -n '/mission_end.msgp/,$p' "$L" > "$L.tail"
done
rm -f "$L.tail"
logw 'port_debug: phase 4 ' 30
c wait:8000 shot:$S/99-home.png
state 2-after-battle

# Gacha: GetGachaInData (the banners open now, the wallet), then a 10-draw of the first
# recommended banner, its presentation and result list, then home.
step=gacha; c phase:0x11; logw 'port_debug: phase 17 '
c wait:10000 shot:$S/a0-gacha-screen.png
c tap:100:175 wait:3000 shot:$S/a1-tab-recommended.png
c tap:360:320 wait:4000 shot:$S/a2-gacha-detail.png
c tap:540:945 wait:2500 shot:$S/a3-draw-confirm.png
step=draw; tapw 'request SaleGacha' 60 20 3 -- tap:515:800
logw 'from the local server' 60
c wait:6000 shot:$S/a4-summon-start.png
c tap:364:1190 wait:6000 shot:$S/a5-summon.png wait:6000 shot:$S/a6-summon.png
c tap:364:650 wait:4000 shot:$S/a7-reveal.png tap:364:650 wait:4000 shot:$S/a8-reveal.png
c tap:577:1199 wait:5000 shot:$S/a9-result.png
# The result: 次へ (the characters' limit breaks), then 閉じる (the chips) at the same spot, then
# the footer's ホーム.
c tap:364:1002 wait:4000 shot:$S/b0-after-result.png
c tap:364:1002 wait:3000 shot:$S/b1-result-closed.png
step=home; tapw 'port_debug: phase 4 ' 60 15 4 -- tap:60:1245
c wait:8000 shot:$S/b2-home.png
state 3-after-gacha
c quit
wait $pid || true
step=done

ok=1
grep -q "mission ${FLOW_MISSION:-mf01_001}: cleared 1" "$OUT/state-2-after-battle.txt" || { echo "FAIL: the battle wasn't cleared"; ok=0; }
c2=$(sed -n 's/.* coins free \([0-9]*\) .*/\1/p' "$OUT/state-2-after-battle.txt"); c3=$(sed -n 's/.* coins free \([0-9]*\) .*/\1/p' "$OUT/state-3-after-gacha.txt")
[ -n "$c2" ] && [ -n "$c3" ] && [ "$c3" -lt "$c2" ] || { echo "FAIL: the draw debited no coins ($c2 -> $c3)"; ok=0; }
grep -q '^  gacha ' "$OUT/state-3-after-gacha.txt" || { echo "FAIL: the server recorded no draw"; ok=0; }
grep -q 'refused with error' "$L" && { grep 'refused with error' "$L"; echo "FAIL: a request was refused"; ok=0; }
[ $ok = 1 ] || exit 1
echo "PASS: login, popups, battle cleared, 10-draw debited $c2 -> $c3 coins, back home"
