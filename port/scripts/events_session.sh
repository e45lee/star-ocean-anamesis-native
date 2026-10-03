#!/bin/sh
# Event missions, restored (the in-process local server; server/src/api/events/event_missions.cpp): from the title through the real UI.
#
#   title -> home -> イベント (CPhase_Mission, mission type 1: CEventMissionMenu) -> 素材 tab ->
#   the day's EXP material mission (the last banner of the tab: lowest order_id) -> its first
#   mission -> single play -> no helper -> party 1 -> battle (MissionStart / MissionEnd of a
#   master_event_mission row) -> result pages -> back on the list: CLEAR, the next mission New.
#   With a known clock (below), also a story event: イベント tab -> the event -> its first story
#   (ストーリー開始 -> スキップ -> はい) -> the scene's end clears it (EndMissionTalk -> the local
#   server) -> the board shows CLEAR and the next node New; on 2020-05-29 the battle it unlocks is
#   then played with an event NPC helper (the helper list shows only the mission's NPCs).
#
# Which events are open is the server's runtime decision (event calendar, clock, assets present);
# the tap positions of the story part are the layout on the two dates below (test data only):
#   2020-05-29 15:00:00  滅びの星に鬼が舞う (event_kimono_91): story mc99_553 -> battle me99_1027 (NPC)
#   2021-06-10 15:00:00  夢追い少女と銀河の歌星 (event_idol4_89, rerun): story mc99_591
# Without a clock (the replayed calendar) the daily part runs and the event tab is only shown.
# Every step waits for its screen or log line, then screenshots (<out>/shots).
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/events_session.sh <soa> <out-dir> <scratch-dir> [clock "YYYY-MM-DD HH:MM:SS"]
# Exit status 1 when a step isn't reached.
set -eu
SOA=$1; OUT=$2; TMP=$3; CLOCK=${4:-}
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
export SOA_HEADLESS="${SOA_HEADLESS:-1}"  # soa --headless (no window); SOA_HEADLESS=0 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py; REF=work/port-test/smoke-base
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos"
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
if [ -n "$CLOCK" ]; then
  SOA_SERVER_SEED_RNG=${SOA_SERVER_SEED_RNG:-1} timeout -k 10 2400 "$SOA" --data "$TMP/data" \
    --size 729x1296 --clock "$CLOCK" --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
else
  SOA_SERVER_SEED_RNG=${SOA_SERVER_SEED_RNG:-1} timeout -k 10 2400 "$SOA" --data "$TMP/data" \
    --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
fi
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
fails=0
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
screen() { python3 $FLOW wait-screen "$TMP/fifo" "$S/$1.png" "$REF/$2.png" "${3:-180}"; }
# check NAME REGEX [TIMEOUT]: a log line; a miss is reported and counted.
check() {
  if python3 $FLOW wait-log "$L" "$2" "${3:-60}" > /dev/null; then echo "ok   $1"; else echo "FAIL $1 (no '$2')"; fails=$((fails + 1)); fi
}
# tapw REGEX TIMEOUT EVERY TRIES -- CMD...: the commands, resent until REGEX is logged (flowctl.py
# tap-until: for taps the game drops under load).
tapw() { python3 $FLOW tap-until "$TMP/fifo" "$L" "$@"; }
# checkt NAME REGEX TIMEOUT EVERY TRIES -- CMD...: tapw, the result reported and counted like check.
checkt() {
  n=$1; shift
  if tapw "$@" > /dev/null; then echo "ok   $n"; else echo "FAIL $n (no '$1')"; fails=$((fails + 1)); fi
}
# The result pages after a won battle (OK at the same spot) until the menu is back (phase 5).
results() {
  i=0
  while ! awk "/$1/{n=NR} END{exit !n}" "$L" || ! awk "/$1/{n=NR} /port_debug: phase 5 /{p=NR} END{exit !(p>n)}" "$L"; do
    [ $i -ge 15 ] && break
    c tap:510:1040 wait:4000; i=$((i + 1))
  done
  check "$2" 'port_debug: phase 5 ' 30
}
# A battle from the mission detail: single play -> helper (x:y, or 選択しない) -> party 1 -> start.
battle() {
  c tap:364:905 wait:5000 shot:$S/$1-helper.png tap:$2 wait:5000 shot:$S/$1-party.png
  c tap:364:900 wait:3000 tap:515:712
  check "$1 MissionStart" 'MissionStart mission [0-9]* \(master_event_mission\)' 60
  check "$1 won" 'MissionEnd mission [0-9]*: player exp' 300
  c wait:4000 shot:$S/$1-result.png
  results 'MissionEnd mission' "$1 result -> menu"
  c wait:5000 shot:$S/$1-after.png
}

# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S" && echo "ok   login"
# The notice board, then the LOGIN BONUS popup (a second page on some days): flowctl.py
# login-popups taps 閉じる until each is gone.
python3 $FLOW login-popups "$TMP/fifo" "$L" $S/02-notice.png $S/03-login-bonus.png $S/04-home.png
grep -E 'events: [0-9]+ event areas open' "$L" | tail -1 | sed 's/^/  /'

# ---- the event list and a daily material mission ------------------------------------------
checkt events 'port_debug: phase 5 ' 60 20 3 -- tap:90:1085
c wait:8000 shot:$S/10-events.png
c tap:515:370 wait:4000 shot:$S/11-materials.png
# The tab lists the materials by order_id, highest first; the day's EXP mission is the last:
# scroll to the end, then its banner is the bottom one.
c drag:364:950:364:450 wait:3000 shot:$S/12-materials-end.png tap:364:985 wait:6000 shot:$S/13-daily.png
c tap:364:415 wait:4000 shot:$S/14-daily-detail.png
battle 20-daily 620:1120
if grep -q 'MissionEnd mission [0-9]*: unlocked' "$L"; then echo "ok   daily: next mission unlocked"; else echo "FAIL daily unlock"; fails=$((fails + 1)); fi
c tap:100:1120 wait:5000 tap:210:370 wait:4000 shot:$S/30-event-tab.png

# ---- a story event -----------------------------------------------------------------------
story() {  # story NAME NODE_X:Y
  c tap:$2 wait:4000 shot:$S/$1-detail.png tap:515:715
  check "$1 scene" 'port_debug: phase 3 ' 30
  c wait:12000 shot:$S/$1-scene.png tap:115:1240 wait:2000 shot:$S/$1-skip.png tap:515:742
  check "$1 cleared" 'events: story mission [0-9]* played' 60
  check "$1 -> board" 'port_debug: phase 5 ' 60
  c wait:8000 shot:$S/$1-board.png
}
case "$CLOCK" in
"2020-05-29 15:00:00")
  c tap:364:525 wait:8000 shot:$S/31-kimono.png
  story 32-story 362:650
  # the battle the story unlocked (me99_1027), with the NPC 鬼炎のアルベル as the 4th member
  c tap:620:660 wait:4000 shot:$S/40-battle-detail.png
  battle 41-npc 364:525
  if grep -q 'event NPC helper [0-9]* .* as member 4' "$L"; then echo "ok   npc helper"; else echo "FAIL npc helper"; fails=$((fails + 1)); fi
  ;;
"2021-06-10 15:00:00")
  c tap:364:830 wait:8000 shot:$S/31-idol4.png
  story 32-story 362:330
  ;;
*)
  c tap:364:525 wait:8000 shot:$S/31-first-event.png
  echo "  (no known layout for this clock: the story part is skipped)"
  ;;
esac

c quit
wait $pid || true
trap - EXIT
grep -E 'events:|restore: CEvent|MissionEnd mission|NPC helper' "$L" | sed 's/^/  /'
[ $fails -eq 0 ] && echo "events_session: PASS" || { echo "events_session: FAIL ($fails)"; exit 1; }
