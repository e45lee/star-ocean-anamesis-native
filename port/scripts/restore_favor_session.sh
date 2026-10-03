#!/bin/sh
# Favorability session of the restored game (the in-process local server; docs/server-rules.md section 8,
# docs/client-changes.md "Favorability"): boot once so the local server seeds itself, give the
# owned characters favor points in the server DB (test setup: the home character 9,900 points,
# one tap short of level 2; the others spread over levels 1..4), boot again, then
#   home (favor heart, level 1) -> two taps on the home character (UpdateFavorByTap, +50 each:
#   the second crosses 10,000 and plays the rank-up; the heart becomes level 2) -> a battle
#   (mf01_001 through the `mission:` / `phase:0xf` route: MissionEnd adds favor) -> the result
#   screens -> home.
# Screenshots go to OUT/shots, the log to OUT/log.txt, the favor table to OUT/favor-*.txt.
#
# Ends with PASS (exit 0) or FAIL (exit 1).
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/restore_favor_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
HEADLESS=--headless; [ "${WATCH:-0}" != 1 ] || HEADLESS=--windowed  # soa --headless (no window); WATCH=1 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos" "${OUT:?}"/favor-*.txt
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
favor() {
  .venv/bin/python - "$TMP/data/server.sqlite3" > "$OUT/favor-$1.txt" <<'PY'
import sqlite3, sys
s = sqlite3.connect(sys.argv[1])
for r in s.execute("select same_role_id, point, tap_count from favor order by same_role_id"): print(*r)
PY
}
boot() {
  rm -f "$TMP/fifo" "$L.pos"
  timeout -k 10 2400 "$SOA" $HEADLESS --seed-rng "${SEED_RNG:-1}" --data "$TMP/data" \
    --size 729x1296 --control "$TMP/fifo" > "$L" 2>&1 &
  pid=$!
  while [ ! -p "$TMP/fifo" ]; do sleep 1; done
  # The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase
  # 4), the notice board and the LOGIN BONUS popup (the first boot's: the second has none).
  phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
  phone370_login "$TMP/fifo" "$L"
  FLOW_BONUS_WAIT=20 python3 $FLOW login-popups "$TMP/fifo" "$L" - - - || fail "the login popups didn't close"
}
fail() { echo "FAIL: $*"; c quit || true; exit 1; }
trap 'kill $pid 2>/dev/null || true' EXIT

# 1. First boot: the server seeds its state from data/saves/seed/Game.xml.
boot
c quit; wait $pid || true
# 2. Test setup: favor points per same role (the home character's first).
.venv/bin/python - "$TMP/data/server.sqlite3" work/../data/basmaster-3.7.0.sqlite3 <<'PY'
import sqlite3, sys
s, m = sqlite3.connect(sys.argv[1]), sqlite3.connect(sys.argv[2])
s.execute("pragma foreign_keys = on")  # PLAN-schema S1: every connection that writes the state
home = s.execute("select r.role_id from player p join roster r on r.uid = p.home_uid").fetchone()[0]
home_same = m.execute("select same_role_id from master_role where id = ?", (home,)).fetchone()[0]
sames = sorted({m.execute("select same_role_id from master_role where id = ?", (r,)).fetchone()[0]
                for (r,) in s.execute("select distinct role_id from roster")})
sames = [x for x in sames if m.execute("select 1 from master_favor_schedule where id = ?", (x,)).fetchone()]
pts = [0, 5000, 10000, 20000, 30000, 45000, 60000, 80000]
for i, x in enumerate(sames):
    s.execute("insert into favor (same_role_id, point, tap_count, tapped_at, event_drop_at) values (?, ?, 0, 0, '') "
              "on conflict(same_role_id) do update set point = excluded.point, tap_count = excluded.tap_count, "
              "tapped_at = excluded.tapped_at, event_drop_at = excluded.event_drop_at",
              (x, 9900 if x == home_same else pts[i % len(pts)]))
s.commit()
PY
favor 0-setup
# 3. Second boot: home, taps, battle.
boot
c wait:8000 shot:$S/02-home-level1.png
# A character with favor can visit the home instead of the home character (the client's own lot,
# with its お気に入りに戻す button at 90:635, which brings the home character back; on the home
# character's home the spot is empty). Taps on a visitor send nothing.
c tap:90:635 wait:6000
python3 $FLOW tap-until "$TMP/fifo" "$L" 'favor: tap same_role [0-9]* \+50: 9900 -> 9950' 40 10 3 -- tap:420:560 || fail "the first tap on the home character sent no UpdateFavorByTap"
c wait:6000 shot:$S/03-tap-9950.png
python3 $FLOW tap-until "$TMP/fifo" "$L" 'favor: tap same_role [0-9]* \+50: 9950 -> 10000 \(level 1 -> 2\)' 40 10 3 -- tap:420:560 || fail "the second tap didn't reach level 2"
c wait:1500 shot:$S/04-levelup.png wait:6500 shot:$S/05-level2.png
favor 1-after-taps
c mission:${FLOW_MISSION:-mf01_001} phase:0xf; logw 'port_debug: phase 15 ' || fail "no CPhase_Battle"
i=10
while ! grep -q 'mission_end.msgp' "$L" && [ $i -lt 70 ]; do
  c wait:4000 shot:$S/$i-battle.png; i=$((i + 1))
done
logw 'mission_end.msgp' 30 || fail "the battle didn't end (no MissionEnd)"
c wait:4000 shot:$S/80-result.png
# The result pages (OK) until home (phase 4).
i=81
while ! python3 $FLOW wait-log "$L" 'port_debug: phase 4 ' 4 > /dev/null 2>&1; do
  c tap:510:1040 wait:1000 shot:$S/$i-result.png; i=$((i + 1)); [ $i -lt 95 ] || fail "the result pages didn't lead home"
done
c wait:8000 shot:$S/99-home.png
favor 2-after-battle
grep 'favor:' "$L" || true
c quit
wait $pid || true
trap - EXIT

# The favor table: the home character's points (9,900 at setup) after the taps (10,000) and the battle.
home=$(grep -o 'favor: tap same_role [0-9]*' "$L" | head -1 | awk '{print $4}')
p() { awk -v r="$home" '$1 == r { print $2 }' "$OUT/favor-$1.txt"; }
echo "home character (same_role $home): $(p 0-setup) -> $(p 1-after-taps) after the taps -> $(p 2-after-battle) after the battle"
ok=1
[ "$(p 0-setup)" = 9900 ] || { echo "FAIL: the setup didn't give the home character 9900 points"; ok=0; }
[ "$(p 1-after-taps)" = 10000 ] || { echo "FAIL: two taps didn't add 100 points"; ok=0; }
grep -q 'favor: mission (stamina [0-9]*) same_role' "$L" || { echo "FAIL: MissionEnd added no favor"; ok=0; }
grep -q 'refused with error' "$L" && { grep 'refused with error' "$L"; echo "FAIL: a request was refused"; ok=0; }
[ $ok = 1 ] || exit 1
echo "PASS: favor taps (level 1 -> 2 with the rank-up), favor from a battle"
