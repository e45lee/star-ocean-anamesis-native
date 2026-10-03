#!/bin/sh
# Rental helpers (the in-process local server; server/src/api/social/rental.cpp, docs/server-rules.md "Rental helpers"):
# title -> home -> Mission -> Episode 1 -> planet Mere -> mission map -> 1-05 (mf01_001) -> single
# play -> the rental list (the server's BattleRental: clones of the player's roster) -> pick the
# first -> the party select shows it as member 4 -> mission start -> MissionStart puts it in the
# battle -> battle -> result (EXP page with the rental as the 4th card).
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/rental_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Runs as a returning player (--campaign-seed CAMPAIGN_SEED, default mf01_001; see campaign_session.sh).
# Then (RENTAL_DAY2=1, the default) the rental bonus: a second boot on the same data a day later
# (the first at --clock RENTAL_CLOCK, default 2026-09-30 12:00:00; the second 24 h on) pays the
# day's rental into the present box, and the home shows the CRentalBonus popup (レンタルボーナス
# 獲得！) after the notice board and the LOGIN BONUS (docs/server-rules.md "Rental helpers").
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
HEADLESS=--headless; [ "${WATCH:-0}" != 1 ] || HEADLESS=--windowed  # soa --headless (no window); WATCH=1 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos"
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
CAMPAIGN_SEED=${CAMPAIGN_SEED:-mf01_001}
CLOCK1=${RENTAL_CLOCK:-2026-09-30 12:00:00}
timeout -k 10 2400 "$SOA" $HEADLESS --campaign-seed "$CAMPAIGN_SEED" --clock "$CLOCK1" --data "$TMP/data" --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
# tapw REGEX TIMEOUT EVERY TRIES -- CMD...: the commands, resent until REGEX is logged (flowctl.py
# tap-until: for taps the game drops under load).
tapw() { python3 $FLOW tap-until "$TMP/fifo" "$L" "$@"; }

# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S"
# notice board, then the 3.7.0 LOGIN BONUS popup (閉じる; flowctl.py login-popups), then ミッション
# (x 270 on the 3.7.0 home)
python3 $FLOW login-popups "$TMP/fifo" "$L" - - $S/02-home.png
phone370_episode_list "$TMP/fifo" "$L" ${HOME_MISSION_X:-270} 1080 || { echo "FAIL: ミッション didn't open the episode list"; c quit; exit 1; }
c wait:5000 drag:364:850:364:400 wait:2000
tapw 'port_debug: phase 5 ' 120 20 3 -- tap:364:805
c wait:8000 tap:660:520 wait:3000 tap:587:795 wait:7000 tap:363:665 wait:4000 shot:$S/03-detail.png
# single play -> the rental list
c tap:364:905 wait:5000 shot:$S/04-rental.png
# the first rental -> the party select (the rental is the 4th card) -> start -> confirm
c tap:364:375 wait:5000 shot:$S/05-party.png
c tap:364:900 wait:3000 shot:$S/06-confirm.png tap:515:712
logw 'MissionStart: rental helper' 60
c wait:15000 shot:$S/07-battle.png
i=8
while ! grep -q 'mission_end.msgp' "$L" && [ $i -lt 40 ]; do
  c wait:5000 shot:$S/$(printf %02d $i)-battle.png; i=$((i + 1))
done
logw 'mission_end.msgp' 30
c wait:4000 shot:$S/60-result.png tap:510:1040 wait:4000 tap:510:1040 wait:4000 shot:$S/61-result.png
c tap:364:1050 wait:5000 shot:$S/62-result-exp.png
c quit
wait $pid || true
grep -q 'MissionStart: rental helper .* as member 4' "$L" || { echo "FAIL: the rental helper didn't join the battle as member 4"; exit 1; }
grep -q 'MissionEnd mission [0-9]*: player exp' "$L" || { echo "FAIL: the battle didn't end (no MissionEnd)"; exit 1; }
echo "PASS: rental helper listed, picked, fought as member 4"
[ "${RENTAL_DAY2:-1}" = 1 ] || exit 0

# ---- day 2: the rental bonus popup
CLOCK2=$(date -d "$CLOCK1 24 hours" '+%Y-%m-%d %H:%M:%S')
L=$OUT/log-day2.txt
rm -f "$TMP/fifo" "$L" "$L.pos"
SOA_TRACE="_ZN12CRentalBonus5SetupEv" timeout -k 10 2400 "$SOA" $HEADLESS --campaign-seed "$CAMPAIGN_SEED" --clock "$CLOCK2" --data "$TMP/data" \
  --size 729x1296 --control "$TMP/fifo" > "$L" 2>&1 &
pid=$!
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
# The same phone, a day later: the title, Login, the data check, home.
phone370_title "$TMP/fifo" "$L"; c shot:$S/70-title.png
phone370_login "$TMP/fifo" "$L"
python3 $FLOW login-popups "$TMP/fifo" "$L" - - -
logw 'CRentalBonus5SetupEv\(' 60
c wait:3000 shot:$S/71-rental-bonus.png tap:364:810 wait:3000 shot:$S/72-home.png
c quit
wait $pid || true
grep -q 'rental bonus: [0-9]* rentals on day' "$L" || { echo "FAIL: no rental bonus paid on day 2"; exit 1; }
echo "PASS: rental bonus paid the next day and its popup shown ($S/71-rental-bonus.png)"
