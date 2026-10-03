#!/bin/sh
# The original (3.7.0) story campaign, restored (the in-process local server): from the title, through the real UI,
# into Episode 1, the planet select, the mission map, a battle mission and the story after it.
#
#   title -> home -> Mission (episode list, CPhase_SelectPart) -> Episode 1 -> CPhase_Mission
#   (planet select) -> planet Mere -> mission map -> 1-05 (mf01_001) -> single play -> no rental
#   -> party 1 -> mission start -> battle (MissionStart / MissionEnd answered by the local server)
#   -> result -> back on the mission map: 1-05 CLEAR, the next story mission (mc01_030) unlocked
#   -> its story scene (MissionTalk) -> the mission after it (ms01_002) unlocked.
#
# The player is a returning one: --campaign-seed mf01_001 counts every mission on the unlock
# chain before 1-05 as cleared (server/campaign.cpp), and the one-time menu tutorials as seen.
# Every step waits for its screen or log line, then screenshots (<out>/shots).
#
# Usage: port/scripts/campaign_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: CAMPAIGN_SEED (soa --campaign-seed; default mf01_001); CAMPAIGN_MASTER_DB (soa
# --campaign-master-db; default the server's, data/basmaster-3.7.0.sqlite3).
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# The in-process server takes its CDN from work/download-3.7.0.
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
# The in-process local server (server core + campaign) on the FakeApiCaller route.
timeout -k 10 2400 "$SOA" $HEADLESS --campaign-seed "$CAMPAIGN_SEED" ${CAMPAIGN_MASTER_DB:+--campaign-master-db "$CAMPAIGN_MASTER_DB"} --data "$TMP/data" --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
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
# The restored 3.7.0 login opens the notice popup over home, then the LOGIN BONUS popup of the
# day's first login (the server grants the day on the title's NoLoginStart and reports it again on
# the Login; the 3.7.0 login arms the popups): flowctl.py login-popups closes both (閉じる), retried
# until they're gone.
python3 $FLOW login-popups "$TMP/fifo" "$L" $S/02-notice.png $S/02-login-bonus.png $S/02-home.png
# Mission -> the episode list; Episode 1 is the third banner (scroll down first). The restored
# 3.7.0 home (restore370 group `home`) has four main buttons: イベント, ミッション (x 270),
# スフィア211, ディープスペース (the offline build's home had ミッション alone at x 90).
# (phone370_episode_list: via Ep選択 when ミッション opens the last episode's map.)
c wait:500; phone370_episode_list "$TMP/fifo" "$L" ${HOME_MISSION_X:-270} 1085 || { echo "FAIL: ミッション didn't open the episode list"; c quit; exit 1; }
c wait:5000 drag:364:850:364:400 wait:2000 shot:$S/03-episodes.png
tapw 'port_debug: phase 5 ' 120 20 3 -- tap:364:805
c wait:8000 shot:$S/04-planets.png
# The next planet (Mere), then Start: its mission map.
c tap:660:520 wait:3000 shot:$S/05-planet-mere.png
c tap:587:795 wait:7000 shot:$S/06-mission-map.png
# 1-05 (mf01_001, "New") -> detail -> single play -> no rental -> party 1 -> start -> confirm.
c tap:363:665 wait:4000 shot:$S/07-mission-detail.png
c tap:364:905 wait:5000 shot:$S/08-rental.png
c tap:620:1120 wait:5000 shot:$S/09-party.png
c tap:364:900 wait:3000 shot:$S/10-confirm.png
tapw 'port_debug: phase 15 ' 120 20 3 -- tap:515:712
logw 'campaign: MissionStart' 60
c wait:15000 shot:$S/11-battle.png
i=12
while ! grep -q 'mission_end.msgp' "$L" && [ $i -lt 60 ]; do
  c wait:5000 shot:$S/$i-battle.png; i=$((i + 1))
done
logw 'campaign: cleared mf01_001' 30
c wait:4000 shot:$S/60-result.png
# The result pages (OK at the same spot) until the game is back on the mission map (phase 5).
i=61
while ! sed -n '/campaign: cleared mf01_001/,$p' "$L" | grep -q 'port_debug: phase 5 ' && [ $i -lt 75 ]; do
  c tap:510:1040 wait:4000 shot:$S/$i-result.png; i=$((i + 1))
done
logw 'port_debug: phase 5 ' 30
c wait:8000 shot:$S/80-map-after-clear.png
# The story mission that 1-05 unlocked (mc01_030, "New" above 1-05) -> detail -> play.
c tap:490:530 wait:4000 shot:$S/81-story-detail.png
# ストーリー開始 (story start; the detail of a story mission has 閉じる / ストーリー開始 side by side)
c tap:515:720 wait:10000 shot:$S/82-story.png
# A few lines of the scene, then スキップ (skip) -> はい (yes); the scene's end sends MissionTalk.
for i in 83 84 85; do c tap:364:1000 wait:3000 shot:$S/$i-story.png; done
c tap:115:1240 wait:2000 shot:$S/86-skip.png tap:515:742
logw 'campaign: story scene played: mc01_030' 90
c wait:8000 shot:$S/96-after-story.png
c wait:6000 shot:$S/97-map.png
c quit
wait $pid || true
trap - EXIT
grep -E 'restore:|campaign:' "$L" | sed 's/^/  /'
ok=1
grep -q "campaign: cleared ${CAMPAIGN_SEED}" "$L" || { echo "FAIL: ${CAMPAIGN_SEED} wasn't cleared"; ok=0; }
grep -q 'campaign: story scene played: mc01_030' "$L" || { echo "FAIL: the story scene mc01_030 wasn't recorded"; ok=0; }
[ $ok = 1 ] && echo "PASS: episode 1 -> ${CAMPAIGN_SEED} cleared -> mc01_030 played" || exit 1
