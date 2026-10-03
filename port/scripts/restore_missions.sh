#!/bin/sh
# The mission side of the local server (the in-process local server), end to end:
#  1. a battle of mf01_003, whose surprise enemy appears (--surprise, a port test
#     option; the server otherwise rolls master_mission.surprise_rate 10.25 %): the result shows
#     the surprise drops, the first clear unlocks mf01_004 (log + state dump);
#  2. a step-up gacha advancing a step: gacha_pickup_role_1011 (step 1 of 10, open at
#     --clock 2021-05-25, the first banner of the gacha screen's おすすめガチャ) drawn through the
#     gacha screen (10連ガチャ -> 決定), then step 2 on the same banner; the server logs each step;
#  3. the error dialog: the player's stamina is set to 0 in the server's state, and the start of
#     mf01_001 is refused with 10004; the client's own error handling shows
#     error_message_text_10004 (スタミナが不足しています, "エラー:10004"); its 閉じる button
#     (tap 364:712) then follows the client's own HndlType: back to the title (verified, d2-after-ok.png).
# Screenshots go to OUT/shots, the state dumps to OUT/state-*.txt, the log to OUT/log.txt.
# Ends with PASS (exit 0) or FAIL (exit 1).
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/restore_missions.sh <soa> <out-dir> <scratch-dir>   (from any directory)
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
HEADLESS=--headless; [ "${WATCH:-0}" != 1 ] || HEADLESS=--windowed  # soa --headless (no window); WATCH=1 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos" "${OUT:?}"/state-*.txt
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
timeout -k 10 2400 "$SOA" $HEADLESS --seed-rng "${SEED_RNG:-1}" --surprise --clock "2021-05-25 12:00:00" --data "$TMP/data" \
  --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt; DB=$TMP/data/server.sqlite3
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
state() { .venv/bin/python tools/server_state.py "$DB" > "$OUT/state-$1.txt"; cat "$OUT/state-$1.txt"; }
sql() { .venv/bin/python -c "import sqlite3,sys; c=sqlite3.connect(sys.argv[1]); c.execute('pragma foreign_keys = on'); c.execute(sys.argv[2]); c.commit()" "$DB" "$1"; }

fail() { echo "FAIL: $*"; c quit || true; exit 1; }
# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4),
# the notice board and the LOGIN BONUS popup.
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S"
python3 $FLOW login-popups "$TMP/fifo" "$L" - - - || fail "the login popups didn't close"
c wait:3000 shot:$S/02-home.png
state 1-boot

# 1. mf01_003 with its surprise enemy.
c mission:mf01_003 phase:0xf; logw 'port_debug: phase 15 ' || fail "no CPhase_Battle"
logw 'MissionStart mission .*surprise enemy' 60 || fail "no MissionStart with the surprise enemy"
c wait:1500 shot:$S/03-battle-loading.png
i=10
while ! grep -q 'mission_end.msgp' "$L" && [ $i -lt 90 ]; do
  c wait:4000 shot:$S/$i-battle.png; i=$((i + 1))
done
logw 'mission_end.msgp' 30 || fail "the battle didn't end (no MissionEnd)"
c wait:4000 shot:$S/a0-result.png
c wait:4000 shot:$S/a1-result.png
i=2
while ! grep -q 'port_debug: phase 4 ' "$L.tail" 2>/dev/null && [ $i -lt 14 ]; do
  c tap:510:1040 wait:4000 shot:$S/a$(printf %02d $i)-result.png; i=$((i + 1))
  sed -n '/mission_end.msgp/,$p' "$L" > "$L.tail"
done
rm -f "$L.tail"
logw 'port_debug: phase 4 ' 30
c wait:6000 shot:$S/b0-home.png
state 2-after-surprise-battle
grep -E 'MissionEnd mission .* (drops|unlocked)' "$L" || true

# 2. Step-up gacha: step 1, then step 2 of gacha_pickup_role_1011's chain, through the gacha
# screen (the footer's ガチャ; at 2021-05-25 its first recommended banner, ステップ 1/10).
draw() {  # draw STEP: 10連ガチャ -> 決定, the presentation, the result (次へ, 閉じる): back on the banner
  python3 $FLOW tap-until "$TMP/fifo" "$L" "step-up chain .* step $1 -> $(($1 + 1))" 40 15 3 -- tap:540:945 wait:3000 tap:515:800 \
    || fail "step $1 of the step-up gacha wasn't drawn"
  c wait:6000 shot:$S/c$1-summon.png tap:364:1190 wait:12000 tap:364:650 wait:4000 tap:364:650 wait:4000 tap:577:1199 wait:5000
  c shot:$S/c$1-result.png tap:364:1002 wait:4000 tap:364:1002 wait:4000 shot:$S/c$1-banner-after.png
}
python3 $FLOW tap-until "$TMP/fifo" "$L" 'request GetGachaInData' 60 20 3 -- tap:425:1250 || fail "ガチャ didn't open the gacha"
c wait:8000 tap:100:175 wait:3000 tap:360:320 wait:5000 shot:$S/c0-stepup-banner.png
draw 1
draw 2
python3 $FLOW tap-until "$TMP/fifo" "$L" 'port_debug: phase 4 ' 60 15 4 -- tap:60:1250 || fail "ホーム didn't lead home"
c wait:6000 shot:$S/c9-home-after-stepup.png
state 3-after-stepup

# 3. Stamina 0: the start of mf01_001 is refused (10004) and the client shows its error dialog.
sql "update player set stamina = 0, stamina_at = strftime('%s','now')"
c mission:mf01_001 phase:0xf; logw 'refused by the local server with error 10004' 90 || fail "MissionStart wasn't refused with 10004"
c wait:3000 shot:$S/d0-error-dialog.png
c tap:364:712 wait:6000 shot:$S/d1-after-ok.png
c wait:6000 shot:$S/d2-after-ok.png
state 4-after-refusal
c quit
wait $pid || true
trap - EXIT

ok=1
grep -q 'MissionEnd mission [0-9]*: unlocked mf01_004' "$L" || { echo "FAIL: mf01_003's first clear didn't unlock mf01_004"; ok=0; }
grep -qE 'MissionEnd mission [0-9]* drops: surprise yes' "$L" || { echo "FAIL: no surprise drops"; ok=0; }
grep -q 'step-up chain 478440451 step 1 -> 2' "$L" || { echo "FAIL: no step-up step 1 -> 2"; ok=0; }
grep -q 'step-up chain .* step 2 -> 3' "$L" || { echo "FAIL: no step-up step 2 -> 3"; ok=0; }
c1=$(grep -o 'coins free [0-9]*' "$OUT/state-2-after-surprise-battle.txt" | awk '{print $3}')
c2=$(grep -o 'coins free [0-9]*' "$OUT/state-3-after-stepup.txt" | awk '{print $3}')
[ "$c2" -lt "$c1" ] || { echo "FAIL: the step-up draws debited no coins ($c1 -> $c2)"; ok=0; }
[ $ok = 1 ] || exit 1
echo "PASS: a surprise-enemy battle (drops, mf01_004 unlocked), two steps of a step-up gacha ($c1 -> $c2 coins), MissionStart refused at stamina 0 (10004 dialog)"
