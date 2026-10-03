#!/bin/sh
# Scripted route into the gacha (729x1296 window), for coverage/profiling and as a gacha check:
# title -> Login -> the data check -> home (notice board, LOGIN BONUS) -> the footer's ガチャ
# (CPhase_Gacha, phase 17: GetGachaInData to the in-process local server) -> the four tabs ->
# おすすめガチャ's first banner (gacha_role_0001, 10連で★4以上) -> 10連ガチャ -> 決定 (SaleGacha:
# 2500 free coins) -> the summon presentation -> the reveals -> the result list (次へ, 閉じる) ->
# ホーム. Every step waits for its log line, then screenshots; the server state
# (tools/server_state.py) is dumped before and after the draw (OUT/state-*.txt): the coins must be
# debited and the drawn characters added. Ends with PASS (exit 0) or FAIL (exit 1).
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/gacha_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_COVERAGE / SOA_PROFILE pass through to soa.
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
timeout -k 10 1800 "$SOA" $HEADLESS --seed-rng "${SEED_RNG:-1}" --data "$TMP/data" \
  --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
tapw() { python3 $FLOW tap-until "$TMP/fifo" "$L" "$@"; }
fail() { echo "FAIL: $*"; c quit || true; exit 1; }
state() { .venv/bin/python tools/server_state.py "$TMP/data/server.sqlite3" > "$OUT/state-$1.txt"; }

# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S"
python3 $FLOW login-popups "$TMP/fifo" "$L" - - $S/02-home.png || fail "the login popups didn't close"
state 1-home
# The footer's ガチャ: CPhase_Gacha asks for the open gachas.
tapw 'request GetGachaInData' 60 20 3 -- tap:425:1250 || fail "ガチャ didn't open the gacha (no GetGachaInData)"
logw 'GetGachaInData: [1-9][0-9]* gachas open' 30 || fail "no gachas open"
c wait:8000 shot:$S/03-gacha.png
c tap:275:175 wait:3000 shot:$S/04-tab-chara.png
c tap:450:175 wait:3000 shot:$S/05-tab-weapon.png
c tap:625:175 wait:3000 shot:$S/06-tab-event.png
# おすすめガチャ -> the first banner -> 10連ガチャ -> 決定 (SaleGacha).
c tap:100:175 wait:3000 shot:$S/07-tab-recommended.png
c tap:360:320 wait:4000 shot:$S/08-gacha-detail.png
c tap:540:945 wait:2500 shot:$S/09-draw-confirm.png
tapw 'request (Sale)?Gacha ' 30 10 3 -- tap:515:800 || fail "決定 didn't draw"
logw 'Gacha [0-9]* \([a-z_0-9]*\): 10 draws for [0-9]* free' 30 || fail "the server didn't draw 10"
state 2-drawn
# The presentation: 召喚開始, the summon, the reveals (each tapped on), then the result list.
c wait:6000 shot:$S/10-summon-start.png
c tap:364:1190 wait:3000 shot:$S/11-summon.png wait:9000 shot:$S/12-summon.png
c tap:364:650 wait:4000 shot:$S/13-reveal.png tap:364:650 wait:4000 shot:$S/14-reveal.png
c tap:577:1199 wait:5000 shot:$S/15-result.png
c tap:364:1002 wait:4000 shot:$S/16-result-2.png tap:364:1002 wait:4000 shot:$S/17-after-result.png
tapw 'port_debug: phase 4 ' 60 15 4 -- tap:60:1250 || fail "ホーム didn't lead home"
c wait:8000 shot:$S/18-home.png profile-dump
c quit
wait $pid || true
trap - EXIT

ok=1
coins() { grep -o 'coins free [0-9]*' "$1" | awk '{print $3}'; }
roster() { grep -o '^roster: [0-9]*' "$1" | awk '{print $2}'; }
c1=$(coins "$OUT/state-1-home.txt"); c2=$(coins "$OUT/state-2-drawn.txt")
r1=$(roster "$OUT/state-1-home.txt"); r2=$(roster "$OUT/state-2-drawn.txt")
echo "server state: free coins $c1 -> $c2, roster $r1 -> $r2"
[ "$c2" -lt "$c1" ] || { echo "FAIL: no coins were debited"; ok=0; }
grep -q 'refused with error' "$L" && { grep 'refused with error' "$L"; echo "FAIL: a request was refused"; ok=0; }
grep -qE 'Unhandled SIG|\*\*\* host signal' "$L" && { echo "FAIL: soa crashed"; ok=0; }
grep -E 'I/server: (GetGachaInData|(Sale)?Gacha) ' "$L" | sed 's/^/  /'
[ $ok = 1 ] || exit 1
echo "PASS: the gacha listed, a 10-draw debited $((c1 - c2)) coins (roster $r1 -> $r2), the presentation and the result, back home"
