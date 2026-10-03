#!/bin/sh
# Scripted route into a battle (729x1296 window), for coverage/profiling and as a battle check:
# title -> Login -> the data check -> home (notice board, LOGIN BONUS) -> ミッション (the episode
# list, CPhase_SelectPart, phase 8) -> back home -> the port control commands `mission:mf01_001`
# (the mission CPhase_Battle starts; FLOW_MISSION overrides it) + `phase:0xf` (CPhase_Battle, the
# switch a mission's start button makes) -> MissionStart to the in-process local server -> the
# battle (the party acts on its own) -> MissionEnd -> the Mission Result pages -> home.
# (campaign_session.sh reaches the same battle through the mission map's UI.)
# Every step waits for its log line (phase changes, the server's request lines), then screenshots.
# The server state (tools/server_state.py) is dumped at home and after the battle (OUT/state-*.txt).
# Ends with PASS (exit 0) or FAIL (exit 1).
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/battle_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Env: SOA_COVERAGE / SOA_PROFILE pass through to soa.
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
export SOA_HEADLESS="${SOA_HEADLESS:-1}"  # soa --headless (no window); SOA_HEADLESS=0 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
MISSION=${FLOW_MISSION:-mf01_001}
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos" "${OUT:?}"/state-*.txt
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
SOA_SERVER_SEED_RNG=${SOA_SERVER_SEED_RNG:-1} timeout -k 10 1800 "$SOA" --data "$TMP/data" \
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
state home
# ミッション (the 3.7.0 home's second main button) -> the episode list (phone370_episode_list: via
# Ep選択 when it opens the last episode's map), then 戻る -> home.
phone370_episode_list "$TMP/fifo" "$L" || fail "ミッション didn't open the episode list"
c wait:6000 shot:$S/03-episodes.png
tapw 'port_debug: phase 4 ' 60 20 3 -- tap:100:1120 || fail "戻る didn't lead home"
c wait:6000 shot:$S/04-home.png
c mission:$MISSION phase:0xf; logw 'port_debug: phase 15 ' 60 || fail "no CPhase_Battle"
logw 'MissionStart mission [0-9]* \(master_mission\)' 60 || fail "no MissionStart"
c wait:1500 shot:$S/05-battle-loading.png
# The party fights on its own; a shot every 4 s until the battle sends MissionEnd.
i=10
while ! grep -q 'mission_end.msgp' "$L" && [ $i -lt 90 ]; do
  c wait:4000 shot:$S/$i-battle.png; i=$((i + 1))
done
logw 'MissionEnd mission [0-9]*: player exp' 30 || fail "the battle didn't end (no MissionEnd)"
c wait:4000 shot:$S/90-result.png
# The result pages (rank / points / FOL / time, party EXP, the follow list), each closed with OK at
# the spot all of them cover, until the game is back home (phase 4).
i=91
while ! python3 $FLOW wait-log "$L" 'port_debug: phase 4 ' 4 > /dev/null 2>&1; do
  c tap:510:1040 wait:1000 shot:$S/$i-result.png; i=$((i + 1)); [ $i -lt 105 ] || fail "the result pages didn't lead home"
done
c wait:8000 shot:$S/99-home.png profile-dump
state after-battle
c quit
wait $pid || true
trap - EXIT

ok=1
grep -q "selected mission $MISSION " "$L" || { echo "FAIL: mission:$MISSION wasn't selected"; ok=0; }
grep -q 'MissionEnd mission [0-9]*: player exp' "$L" || { echo "FAIL: no MissionEnd"; ok=0; }
grep -q 'refused with error' "$L" && { grep 'refused with error' "$L"; echo "FAIL: a request was refused"; ok=0; }
grep -qE 'Unhandled SIG|\*\*\* host signal' "$L" && { echo "FAIL: soa crashed"; ok=0; }
# The server state: the player's EXP and FOL went up with the battle.
exp0=$(grep -o 'exp [0-9]*' "$OUT/state-home.txt" | head -1); exp1=$(grep -o 'exp [0-9]*' "$OUT/state-after-battle.txt" | head -1)
[ -n "$exp0" ] && [ "$exp0" != "$exp1" ] || { echo "FAIL: the player's EXP didn't change in the server state ($exp0 -> $exp1)"; ok=0; }
grep -E 'MissionStart mission|MissionEnd mission' "$L" | sed 's/^/  /'
[ $ok = 1 ] || exit 1
echo "PASS: $MISSION fought (MissionStart, MissionEnd), the result pages, back home"
