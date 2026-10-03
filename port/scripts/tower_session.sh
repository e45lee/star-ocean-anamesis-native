#!/bin/sh
# The tower (試練の遺跡), opened by the opt-in --restore-tower (3.7.0 had it closed;
# server module server/src/api/tower/tower.cpp, client changes port/src/native/restore/restore_tower.cpp,
# docs/client-changes.md "Tower", docs/notes.md "Tower layout"). From the title through the real UI:
#
#   title -> home -> スフィア211 button (phase 5: CExtraDungeonMenu, now two parts) -> 試練の遺跡
#   (CTowerMissionMenu) -> the floor list (the open tower areas; the server lists them, the client
#   master has stand-in banner rows for the five permanent areas) -> the top area -> its 1st floor
#   -> detail -> single play -> 選択しない -> party 1 -> battle (MissionStart / MissionEnd of a
#   master_tower_mission row) -> result pages -> the floor's list again: 1F CLEAR, 2F New.
#   Then 戻る -> the floor list -> 戻る (the extra-dungeon menu).
#
# Every step waits for its log line, then screenshots (<out>/shots). About 5 minutes.
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/tower_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
# Exit status 1 when a step isn't reached.
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
HEADLESS=--headless; [ "${WATCH:-0}" != 1 ] || HEADLESS=--windowed  # soa --headless (no window); WATCH=1 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py; REF=work/port-test/smoke-base
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos"
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
timeout -k 10 2100 "$SOA" $HEADLESS --seed-rng "${SEED_RNG:-1}" --data "$TMP/data" \
  --size 729x1296 --restore-tower --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
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
tapw() { python3 $FLOW tap-until "$TMP/fifo" "$L" "$@"; }
checkt() {
  n=$1; shift
  if tapw "$@" > /dev/null; then echo "ok   $n"; else echo "FAIL $n (no '$1')"; fails=$((fails + 1)); fi
}
fail() { echo "FAIL: $*"; c quit || true; exit 1; }

# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S" && echo "ok   login"
python3 $FLOW login-popups "$TMP/fifo" "$L" $S/02-notice.png $S/03-login-bonus.png $S/04-home.png || fail "the login popups didn't close"
grep -E 'server: tower: [0-9]+ areas' "$L" | tail -1 | sed 's/^/  /'
grep -q 'tower: stand-in banner banner80' "$L" && echo "ok   stand-in banners in the client master" \
  || { echo "FAIL stand-in banners"; fails=$((fails + 1)); }

# The home's スフィア211 button: with the tower open, the extra-dungeon menu lists 試練の遺跡 and
# スフィア211 (MissionUtility::GetExtraDungeonList).
checkt extra-dungeon 'port_debug: phase 5 ' 60 20 3 -- tap:455:1085
c wait:6000 shot:$S/05-extra-dungeon.png
# 試練の遺跡: the floor list (CTowerMissionMenu::Setup; the play_plate stand-ins are made here).
c tap:364:470 wait:8000 shot:$S/06-floors.png
check "tower menu (play_plate stand-ins)" "layout node 'play_plate/3' missing" 30
# The top area -> its missions (1F only).
c tap:364:400 wait:6000 shot:$S/07-area.png
c tap:364:415 wait:4000 shot:$S/08-detail.png
# single play -> 選択しない -> party 1 -> ミッション開始 -> 決定
c tap:364:905 wait:5000 shot:$S/09-helper.png tap:628:1120 wait:5000 shot:$S/10-party.png
c tap:364:900 wait:3000 shot:$S/11-confirm.png tap:515:712
check "tower MissionStart" 'MissionStart mission [0-9]* \(master_tower_mission\)' 60
c wait:12000 shot:$S/12-battle.png
check "tower battle won" 'MissionEnd mission [0-9]*: player exp' 400
check "next floor unlocked" 'MissionEnd mission [0-9]*: unlocked' 10
check "lists refreshed" 'server: tower: [0-9]+ areas, [0-9]+ missions listed' 10
c wait:6000 shot:$S/13-result.png
# the result pages (OK at 510:1050) until the tower menu is back (phase 5)
i=0
while ! python3 $FLOW wait-log "$L" 'port_debug: phase 5 ' 4 > /dev/null 2>&1; do
  c tap:510:1050; i=$((i + 1)); [ $i -lt 15 ] || { echo "FAIL result pages"; fails=$((fails + 1)); break; }
done
c wait:8000 shot:$S/14-area-after.png
# 戻る -> the floor list -> 戻る -> the extra-dungeon menu
c tap:100:1120 wait:5000 shot:$S/15-floors-again.png tap:100:1120 wait:5000 shot:$S/16-back.png
c quit || true
wait $pid || true
trap - EXIT

# The server's state: the cleared floor
.venv/bin/python - "$TMP/data/server.sqlite3" "$(grep -o '(master [^)]*basmaster-3.7.0.sqlite3' "$L" | head -1 | cut -c9-)" <<'PY' | tee "$OUT/state.txt"
import sqlite3, sys
c = sqlite3.connect(sys.argv[1])
m = sqlite3.connect("file:%s?mode=ro" % sys.argv[2], uri=True)
for (mid,) in c.execute("select mission_id from mission where cleared = 1"):
    r = m.execute("select id_label, master_tower_area_id from master_tower_mission where id = ?", (mid,)).fetchone()
    if r: print("tower mission cleared: %s (area %s)" % r)
PY
grep -q '^tower mission cleared' "$OUT/state.txt" || { echo "FAIL no tower mission cleared in the state DB"; fails=$((fails + 1)); }
if grep -q 'Unhandled SIG\|host signal' "$L"; then echo "FAIL crash (see $L)"; fails=$((fails + 1)); fi
if [ $fails -eq 0 ]; then echo "PASS tower_session"; else echo "FAIL tower_session ($fails)"; exit 1; fi
