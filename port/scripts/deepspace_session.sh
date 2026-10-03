#!/bin/sh
# Scripted session of the restored deep space mode (the in-process local server; server module
# server/src/api/deepspace/deepspace.cpp): boot -> home -> deep space (CPhase_DeepSpace, phase 6:
# the home's deep space button when the restored home has it, else the `phase:6` control
# command) -> the first area -> its first mission -> party select, one bonus tapped
# (DeepSpaceAutoMemberSelect) -> start (DeepSpaceMissionStart) -> the server clock fast-forwarded
# past the expedition (control command `clock:+SECONDS`) -> back in -> the returned ship
# collected (DeepSpaceMissionEnd) -> the result pages. Then a second expedition returned at once
# (今すぐ帰還, DeepSpaceMissionEndNow) and collected. The run has the Galaxy Pass (--galaxy-pass:
# +2 ships, api/shop/subscription.cpp): two expeditions then depart at once, the second on a pass ship
# (the seed's limit breaks give one ship), and the 実績 (achievements) button shows the deep space
# achievements (types 44 / 45); 一括達成 receives the two expedition achievements into the present box.
# Screenshots go to OUT/shots, the server's deep-space tables to OUT/state-*.txt, the log to
# OUT/log.txt. Exit status 1 if an API didn't answer as expected.
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/deepspace_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
export SOA_HEADLESS="${SOA_HEADLESS:-1}"  # soa --headless (no window); SOA_HEADLESS=0 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos" "${OUT:?}"/state-*.txt
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
SOA_SERVER_SEED_RNG=${SOA_SERVER_SEED_RNG:-1} timeout -k 10 2400 "$SOA" --data "$TMP/data" \
  --size 729x1296 --galaxy-pass --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
# tapw REGEX TIMEOUT EVERY TRIES -- CMD...: the commands, resent until REGEX is logged (flowctl.py
# tap-until: for taps the game drops under load).
tapw() { python3 $FLOW tap-until "$TMP/fifo" "$L" "$@"; }
state() { .venv/bin/python - "$TMP/data/server.sqlite3" <<'PY'
import sqlite3, sys
c = sqlite3.connect(sys.argv[1])
for r in c.execute("select area_id, exp from ds_area order by area_id"): print("area", *r)
for r in c.execute("select ship_id, mission_id, closed_at - started_at, uids from ds_ship order by ship_id"): print("ship", *r)
print("offers", c.execute("select count(*) from ds_offer").fetchone()[0])
print("free_coin", c.execute("select free_coin from player").fetchone()[0])
print("presents", c.execute("select count(*) from presents").fetchone()[0])
PY
}

# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S"
# The restored 3.7.0 login opens the notice popup over home, then the LOGIN BONUS popup (as in
# restore_session.sh): flowctl.py login-popups closes both. Left open, the LOGIN BONUS popup stays
# up over deep space (the phase:6 control command bypasses it) and its 閉じる button (y 1063)
# swallows the result page's OK tap (364:1050), shifting every later tap.
python3 $FLOW login-popups "$TMP/fifo" "$L" $S/02-notice.png $S/02-login-bonus.png $S/03-home.png

# Deep space: CPhase_DeepSpace sends DeepSpaceActiveList.
c phase:6; logw 'DeepSpaceActiveList: ' 60
c wait:5000 shot:$S/04-deepspace.png
# The focused area (the first one), then its mission list.
c tap:360:680 wait:4000 shot:$S/05-missions.png
# The first mission (0.5H): party select; tap its second bonus: auto member select.
c tap:360:790 wait:5000 shot:$S/06-party.png
c tap:350:790; logw 'DeepSpaceAutoMemberSelect bonus' 30
c wait:4000 shot:$S/07-auto.png
# 決定 -> the confirmation (探査時間) -> 探査開始.
c tap:630:1120 wait:3000 shot:$S/08-confirm.png tap:515:1003; logw 'DeepSpaceMissionStart area' 30
c wait:6000 shot:$S/09-started.png
state > "$OUT/state-1-started.txt"; cat "$OUT/state-1-started.txt"

# Fast-forward the server clock past the expedition (the 0.5H mission: 30 minutes), leave to
# home and come back: the next DeepSpaceActiveList reports the ship back.
c clock:+1900 tap:100:1120 wait:3000 tap:100:1120; logw 'port_debug: phase 4 ' 60
c wait:5000 phase:6; logw 'DeepSpaceActiveList: .* 0 ships out, 1 back' 60
c wait:5000 shot:$S/10-returned.png
# The area, the returned mission: DeepSpaceMissionEnd and the result pages.
c tap:360:680 wait:4000 shot:$S/11-area.png tap:360:790; logw 'DeepSpaceMissionEnd ship' 30
c wait:6000 shot:$S/12-result-items.png tap:364:1050 wait:5000 shot:$S/13-result-characters.png
c tap:364:1050 wait:5000 shot:$S/14-after.png
state > "$OUT/state-2-collected.txt"; cat "$OUT/state-2-collected.txt"

# A second expedition, returned at once (今すぐ帰還: DeepSpaceMissionEndNow for coins), then
# collected.
c tap:360:790 wait:5000 tap:350:790; logw 'DeepSpaceAutoMemberSelect bonus' 30
c wait:4000 tap:630:1120 wait:3000 tap:515:1003; logw 'DeepSpaceMissionStart area' 30
c wait:6000 shot:$S/15-started-2.png tap:655:797 wait:4000 shot:$S/16-quick-return.png
c tap:515:890; logw 'DeepSpaceMissionEndNow ship' 30
c wait:5000 shot:$S/17-quick-returned.png tap:364:800 wait:5000 shot:$S/18-returned-2.png
c tap:360:790; logw 'DeepSpaceMissionEnd ship' 30
c wait:6000 shot:$S/19-result-2.png tap:364:1050 wait:5000 tap:364:1050 wait:5000 shot:$S/20-after-2.png
state > "$OUT/state-3-quick.txt"; cat "$OUT/state-3-quick.txt"

# Two expeditions at once: the 0.5H mission (ship 1), then the 1H mission (ship 2, a pass ship;
# the auto select takes the characters not out).
c tap:360:790 wait:5000 tap:350:790; logw 'DeepSpaceAutoMemberSelect bonus' 30
c wait:4000 tap:630:1120 wait:3000 tap:515:1003; logw 'DeepSpaceMissionStart area .*: ship 1/' 30
c wait:6000 tap:320:868 wait:5000 shot:$S/21-party-2.png tap:350:790; logw 'DeepSpaceAutoMemberSelect bonus' 30
c wait:4000 tap:630:1120 wait:3000 tap:515:1003; logw 'DeepSpaceMissionStart area .*: ship 2/' 30
c wait:6000 shot:$S/22-two-ships.png
state > "$OUT/state-4-pass.txt"; cat "$OUT/state-4-pass.txt"
# 実績: the deep space achievements.
# (The screen opens on a tab with an achieved row: その他, where the expedition counts are.)
c tap:655:262 wait:5000 shot:$S/23-achievements.png tap:590:303 wait:3000 shot:$S/24-achievements-other.png
# 一括達成: the achieved rows' rewards go to the present box.
c tap:515:1053; logw 'request Achievement(Receive|ListReceive|ReceiveList) ' 30
c wait:5000 shot:$S/25-achievements-received.png
state > "$OUT/state-5-achievements.txt"; cat "$OUT/state-5-achievements.txt"
c quit
wait $pid || true
trap - EXIT

ok=1
grep -q '^ship ' "$OUT/state-1-started.txt" || { echo "FAIL: no ship out after DeepSpaceMissionStart"; ok=0; }
grep -q '^ship ' "$OUT/state-2-collected.txt" && { echo "FAIL: the ship wasn't collected"; ok=0; }
grep -q '^ship ' "$OUT/state-3-quick.txt" && { echo "FAIL: the quick-returned ship wasn't collected"; ok=0; }
c1=$(grep '^free_coin ' "$OUT/state-2-collected.txt" | awk '{print $2}'); c2=$(grep '^free_coin ' "$OUT/state-3-quick.txt" | awk '{print $2}')
[ "$c2" -lt "$c1" ] || { echo "FAIL: the quick return cost nothing ($c1 -> $c2)"; ok=0; }
p4=$(grep '^presents ' "$OUT/state-4-pass.txt" | awk '{print $2}'); p5=$(grep '^presents ' "$OUT/state-5-achievements.txt" | awk '{print $2}')
[ "$p5" -ge $((p4 + 2)) ] || { echo "FAIL: the two expedition achievements' rewards didn't reach the present box ($p4 -> $p5)"; ok=0; }
grep -q 'request AchievementActiveList' "$L" || { echo "FAIL: the achievements screen didn't ask for its list"; ok=0; }
grep -q 'DeepSpaceActiveList: .* (2 by the pass)' "$L" || { echo "FAIL: the Galaxy Pass ships weren't counted"; ok=0; }
[ "$(grep -c '^ship ' "$OUT/state-4-pass.txt")" = 2 ] || { echo "FAIL: two expeditions weren't out at once (pass ship)"; ok=0; }
grep -E 'DeepSpace(ActiveList|AutoMemberSelect|MissionStart|MissionEnd|MissionEndNow)' "$L" | grep 'I/server: Deep' || true
grep -q 'refused with error' "$L" && { grep 'refused with error' "$L"; echo "FAIL: a request was refused"; ok=0; }
[ $ok = 1 ] && echo "PASS: deep space expedition started, returned, collected; quick return; a Galaxy Pass ship" || exit 1
