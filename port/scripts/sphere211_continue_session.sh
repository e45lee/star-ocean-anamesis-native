#!/bin/sh
# Scripted session (agent a5-sphere): a lost Sphere 211 battle, continued and retired (port option
# the in-process local server; server module server/src/api/sphere211/sphere211.cpp). Boot -> title (test setup in the
# state DB, as sphere211_session.sh: the season's heal / reroll tickets, 5 Sphere 211 rentals two
# days ago) -> notice board -> LOGIN BONUS -> the Sphere 211 rental bonus popup -> home -> スフィア211
# -> the start cell with enemy level 250 (the server's test hook: sphere_meta test_enemy_level, set
# in the state DB for this battle only) and a rental in the 4th slot -> the party falls -> the
# defeat dialog's はい (Sphere211MissionContinue, 100 coins) -> the pause menu's ミッションリタイア ->
# はい (Sphere211MissionFailed) -> the board -> the stamina the battle took healed with a ticket
# (Sphere211StaminaHeal 8 -> 9). About 5 minutes. A separate script because sphere211_session.sh's
# five battles already take the game near its memory budget.
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/sphere211_continue_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
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
SOA_SERVER_SEED_RNG=${SOA_SERVER_SEED_RNG:-605} timeout -k 10 2400 "$SOA" --data "$TMP/data" \
  --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@"; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
fail() { echo "FAIL: $*"; c quit || true; exit 1; }
# tapw REGEX TIMEOUT EVERY TRIES -- CMD...: the commands, resent until REGEX is logged (flowctl.py
# tap-until: for taps the game drops under load).
tapw() { python3 $FLOW tap-until "$TMP/fifo" "$L" "$@"; }
sql() { .venv/bin/python - "$TMP/data/server.sqlite3" "$@" <<'PY'
import sqlite3, sys
c = sqlite3.connect(sys.argv[1], timeout=60)
for q in sys.argv[2:]: c.execute(q)
c.commit()
PY
}
state() { .venv/bin/python - "$TMP/data/server.sqlite3" <<'PY'
import sqlite3, sys
c = sqlite3.connect(sys.argv[1])
r = c.execute("select season_id, floor_level, streak, treasure_total, stamina, clear_asset, lot_floor_num from sphere").fetchone()
print("sphere season %s floor %s streak %s treasure_total %s stamina %s clear_asset %s lot %s" % r)
print("cells", c.execute("select count(*) from sphere_cell").fetchone()[0],
      "cleared", c.execute("select count(*) from sphere_cell where cleared = 1").fetchone()[0])
print("boxes", c.execute("select count(*) from sphere_box").fetchone()[0])
print("departed", c.execute("select count(*) from sphere_departed").fetchone()[0])
for s, f in c.execute("select season_id, floor_level from sphere_rank"): print("rank season %s best floor %s" % (s, f))
PY
}
# battle NAME [rent]: the cell's detail is open; single play -> the rental list (the first lender
# with "rent", else 選択しない) -> auto party -> start -> the battle -> the result pages until the
# board (phase 5) is back.
battle() {
  n0=$(wc -l < "$L")
  c wait:4000 shot:$S/$1-detail.png tap:364:905 wait:5000 shot:$S/$1-rental.png
  if [ "${2:-}" = rent ]; then c tap:364:383; else c tap:628:1120; fi
  c wait:4000 tap:364:898
  logw 'Sphere211AutoMemberSelect: 4 members proposed' 30 || fail "$1: no auto member select"
  c wait:4000 shot:$S/$1-party.png tap:140:898 wait:3000 tap:515:713
  logw 'Sphere211MissionStart: floor' 60 || fail "$1: no Sphere211MissionStart"
  c wait:15000 shot:$S/$1-battle.png
  logw 'Sphere211MissionEnd: |Sphere211MissionFailed' 500 || { c shot:$S/$1-stuck.png; fail "$1: the battle didn't end"; }
  tail -n +"$n0" "$L" | grep -q 'Sphere211MissionFailed' && fail "$1: the battle was lost"
  c wait:10000 shot:$S/$1-result.png
  i=0
  while ! python3 $FLOW wait-log "$L" 'port_debug: phase 5 ' 4 > /dev/null 2>&1; do
    c tap:364:1050; i=$((i + 1)); [ $i -lt 12 ] || fail "$1: the result pages didn't end"
  done
  c wait:6000
}

# The title (phase 1).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
# Test setup in the state DB (the server made it at boot): the season's heal and reroll tickets,
# and 5 Sphere 211 rentals two days ago, unpaid (the season named in the log's client-master line).
season=$(grep -o 'Sphere211: season [0-9]*' "$L" | head -1 | grep -o '[0-9]*$')
[ -n "$season" ] || fail "no Sphere211 season in the log"
master=$(grep -o '(master [^)]*basmaster-3.7.0.sqlite3' "$L" | head -1 | cut -c9-)
[ -f "$master" ] || fail "the server's master DB isn't named in the log"
.venv/bin/python - "$TMP/data/server.sqlite3" "$season" "$master" <<'PY'
import sqlite3, sys, time
c = sqlite3.connect(sys.argv[1], timeout=60)
m = sqlite3.connect("file:%s?mode=ro" % sys.argv[3], uri=True)
for i, t in m.execute("select id, type from master_item where id_label like 'item_sphere_stamina_%' or id_label like 'item_sphere_re_%'"):
    c.execute("insert into stock values (?, ?, 2) on conflict(master_item_id) do update set count = 2", (i, t))
c.execute("create table if not exists sphere_rental_day (day integer primary key, season_id integer, count integer default 0, paid integer default 0)")
c.execute("insert or replace into sphere_rental_day values (?, ?, 5, 0)", (int(time.time()) - 2 * 86400, int(sys.argv[2])))
c.commit()
PY
# TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_login "$TMP/fifo" "$L" "$S"
# The restored 3.7.0 login: the notice board, then the LOGIN BONUS popup, over home (flowctl.py
# login-popups closes them).
python3 $FLOW login-popups "$TMP/fifo" "$L" $S/02-notice.png $S/03-login-bonus.png $S/04-home.png || fail "the login popups didn't close"
# Then the Sphere 211 rental bonus popup (CPopupManager::CheckStart case 5): "前日、5人のユーザーが
# あなたをレンタルしました ... フロア再設定チケットが1個届いています" -> 閉じる.
grep -q 'Sphere211 rental bonus: 5 rentals' "$L" || fail "the Sphere 211 rental bonus wasn't paid"
c wait:3000 shot:$S/04b-rental-bonus.png tap:364:800 wait:3000 shot:$S/04c-home.png

# The home's スフィア211 button: phase 5 with the extra dungeon (MissionUtility type 5).
tapw 'GetSphere211Info: season' 60 20 3 -- tap:455:1085 || fail "the home button didn't open Sphere 211"
c wait:6000 shot:$S/05-board.png
grep -q 'Sphere211: floor 1 (floor row [0-9]*), map 2554458071 ' "$L" \
  || fail "floor 1 isn't the map this script's taps are for (SOA_SERVER_SEED_RNG=1 lots map 2554458071): $(grep 'Sphere211: floor 1' "$L")"
state > "$OUT/state-1-floor1.txt"; cat "$OUT/state-1-floor1.txt"

# A lost battle on the start cell (enemy level 250 through the test hook), with a rental in the 4th
# slot: the defeat dialog's はい (continue, 100 coins; tapped until the server logs it: the dialog
# comes when the party falls), then the pause menu's ミッションリタイア -> はい (retire), back on the
# board. The stamina it took (9 -> 8) is healed with a ticket (+ -> the ticket -> 決定 -> 閉じる).
sql "insert or replace into sphere_meta values ('test_enemy_level', 250)"
c tap:364:670; c wait:4000 shot:$S/06-lose-detail.png tap:364:905 wait:5000 shot:$S/06-rental-list.png tap:364:383 wait:4000 shot:$S/06-rental-party.png
c tap:364:898; logw 'Sphere211AutoMemberSelect: 4 members proposed' 30 || fail "lost battle: no auto member select"
c wait:4000 shot:$S/06-party.png tap:140:898 wait:3000 tap:515:713
logw 'Sphere211MissionStart: floor .* enemy level 250' 60 || fail "lost battle: no Sphere211MissionStart"
grep -q 'MissionStart: rental helper .* as member 4' "$L" || fail "the rental didn't join as member 4"
sql "delete from sphere_meta where key = 'test_enemy_level'"
tapw 'Sphere211MissionContinue: ' 400 10 40 -- tap:489:786 || { c shot:$S/07-stuck.png; fail "no continue after the defeat"; }
c shot:$S/07-continued.png
tapw 'Sphere211MissionFailed: ' 90 15 5 -- tap:80:50 wait:2500 tap:364:607 wait:2500 tap:525:790 || { c shot:$S/08-stuck.png; fail "no retire"; }
logw 'port_debug: phase 5 ' 120 || fail "not back on the board after the retire"
c wait:6000 shot:$S/08-board.png tap:590:992 wait:3000 shot:$S/09-heal-items.png tap:364:515 wait:3000 shot:$S/09-heal.png tap:515:790
logw 'Sphere211StaminaHeal: sphere stamina 8 -> 9' 30 || fail "no stamina heal"
c wait:3000 shot:$S/09-healed.png tap:364:790 wait:2000

# The board's 実績 button: the achievement dialog, its four tabs (the Sphere 211 weekly challenge
# and floor achievements are served with the Sphere 211 answers), then 閉じる.
c tap:655:340 wait:5000 shot:$S/10-achievements-event.png tap:290:303 wait:2500 shot:$S/10-achievements-daily.png \
  tap:440:303 wait:2500 shot:$S/10-achievements-weekly.png tap:590:303 wait:2500 shot:$S/10-achievements-other.png tap:213:1053 wait:2000
c quit
wait $pid || true
trap - EXIT

ok=1
grep -q 'Sphere211MissionContinue: 100 coins' "$L" || { echo "FAIL: no paid continue"; ok=0; }
grep -q 'Sphere211MissionFailed: streak reset' "$L" || { echo "FAIL: no retire"; ok=0; }
grep -q 'Sphere211StaminaHeal: sphere stamina 8 -> 9' "$L" || { echo "FAIL: no heal"; ok=0; }
grep -q 'refused with error\|Sphere211.* refused' "$L" && { grep 'refused' "$L"; echo "FAIL: a request was refused"; ok=0; }
[ $ok = 1 ] && echo "PASS: rental bonus popup, a lost Sphere 211 battle with a rental continued (100 coins) and retired from the pause menu, the stamina healed" || exit 1
