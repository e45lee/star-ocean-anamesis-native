#!/bin/sh
# Scripted session of the restored Sphere 211 (the in-process local server; server module
# server/src/api/sphere211/sphere211.cpp): boot -> notice board -> LOGIN BONUS -> home -> the home's
# スフィア211 button (phase 5, GetSphere211Info: the season's floor 1) -> a dive along the shortest
# path of the lotted map. Each cell = detail -> シングルプレイ開始 -> party select -> 自動編成
# (Sphere211AutoMemberSelect proposes the 4 strongest characters that haven't sortied) ->
# ミッション開始 -> 決定 (Sphere211MissionStart) -> the battle (auto) -> Sphere211MissionEnd -> the
# result pages -> the board. Four cells, then 帰還 (ReturnSphere211: the boxes analysed, the
# characters back, the dive stays on floor 1), the boss with the strongest party again, the goal
# (目標地点) -> 次のフロアへ -> Sphere211FloorClear (floor result, the warp analysis) -> floor select
# 2F -> Sphere211SelectedFloor -> 帰還 again on floor 2. About 20 minutes.
# Also (agent a5-sphere): the Sphere 211 rental bonus popup after the login (a rental day injected
# into the state DB: 5 rentals the day before, paid on the Login as Sphere211RentalBonus /
# Sphere211RentalCount); a rental character in the party's 4th slot (the rental list after
# シングルプレイ開始) on the first cell; the stamina heal ticket after it (Sphere211StaminaHeal:
# 8 -> 9); the reroll item at the floor select (Sphere211UseRerollItem). A lost battle, continue and
# retire are in sphere211_continue_session.sh (one more battle here would take the game past its
# memory budget: each battle added about 0.7 GB before PLAN-next D7; now about 70 MB, the run peaks near 2.3 GB). The heal and reroll tickets of every season are put into the player's
# stock at the title screen (the account has none; the game sold them in event shops).
# The cell taps are screen positions of the map the server lots with SOA_SERVER_SEED_RNG=605
# (Asset_easy_normal_0003: start -> 2 -> 3 -> 6 -> boss 7 -> goal; since the favor login bonus lots
# at the login (a4-helpers), seed 1 lots another map); the script checks the map id in the log and
# stops if another map came up. Before each tap the board is re-entered from home,
# so the camera is on its start view (the camera follows the last cleared cell otherwise).
# Screenshots go to OUT/shots, the server's Sphere 211 tables to OUT/state-*.txt, the log to
# OUT/log.txt. Exit status 1 if a step didn't answer as expected.
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/sphere211_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
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
c.execute("pragma foreign_keys = on")  # PLAN-schema S1: every connection that writes the state
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
  # ミッション開始 -> 決定, resent until the server logs the start (a tap can be dropped under load).
  c wait:4000 shot:$S/$1-party.png
  tapw 'Sphere211MissionStart: floor' 60 15 3 -- tap:140:898 wait:3000 tap:515:713 || fail "$1: no Sphere211MissionStart"
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
c.execute("pragma foreign_keys = on")  # PLAN-schema S1: every connection that writes the state
m = sqlite3.connect("file:%s?mode=ro" % sys.argv[3], uri=True)
for i, t in m.execute("select id, type from master_item where id_label like 'item_sphere_stamina_%' or id_label like 'item_sphere_re_%'"):
    c.execute("insert into stock (master_item_id, item_type, count) values (?, ?, 2) on conflict(master_item_id) do update set count = 2", (i, t))
c.execute("create table if not exists sphere_rental_day (day integer primary key, season_id integer, count integer default 0, paid integer default 0)")
c.execute("insert or replace into sphere_rental_day (day, season_id, count, paid) values (?, ?, 5, 0)", (int(time.time()) - 2 * 86400, int(sys.argv[2])))
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

# The board's camera moves after a battle (it follows the cleared cell), so before each tap the
# board is left (戻る -> home) and entered again: a fresh board shows the start view. The upper
# cells need the board scrolled: three slow drags down (drag:...:MS, so they register under load)
# reach its top edge, which shows the goal (364,625), the right boss (490,790) and cell 6 (490,965).
# The first entry after a clear plays the unlock animation of the new cells (the camera pans to
# them and the board takes no input meanwhile), so the board is entered twice.
enter_once() {
  c tap:100:1120; logw 'port_debug: phase 4 ' 30 || fail "戻る didn't lead home"
  c wait:5000; tapw 'request GetSphere211Info' 60 20 3 -- tap:455:1085 || fail "the home button didn't reopen Sphere 211"
}
reenter() { enter_once; c wait:15000; enter_once; c wait:8000; }
TOP="drag:364:300:364:900:1200 wait:1500 drag:364:300:364:900:1200 wait:1500 drag:364:300:364:900:1200 wait:3000"

# 帰還 NAME: the return dialog -> 帰還 (ReturnSphere211) -> the treasure analysis, the items,
# "every character is back".
return_dive() {
  c tap:590:1120 wait:3000 shot:$S/$1-return-dialog.png tap:515:972
  logw 'ReturnSphere211: ' 30 || fail "$1: no ReturnSphere211"
  c wait:6000 shot:$S/$1-treasure-data.png tap:364:1095 wait:5000 shot:$S/$1-treasure-items.png tap:364:1095 wait:4000 shot:$S/$1-returned.png
  c tap:364:800 wait:3000 shot:$S/$1-board-after.png
}

# The battles are won or lost by the client's own (unseeded) battle: with seed 605 the level-65
# cell 6 and the level-90 boss were lost in some runs (the defeat dialog times out: "制限時間に
# 達しました"). The session checks the flow, not the balance, so the enemies are set to level 30
# with the server's test hook (sphere.debug_enemy_level; the dive's row exists since the board
# opened) for the whole dive.
sql "update sphere set debug_enemy_level = 30 where id = 1"
# The path: the start cell, 2, 3 (on the start view), then 6 (scrolled). The auto party takes the
# strongest characters first, so by the boss only level-50 ones are left, which lose to its
# level 90: 帰還 first (the characters come back, the boxes so far are analysed, the dive stays
# on floor 1), then the boss 7 with the strongest party again.
c tap:364:670; battle 10-cell1 rent
grep -q 'MissionStart: rental helper .* as member 4' "$L" || fail "the rental didn't join as member 4"
# The stamina the battle took (9 -> 8) healed with the season's ticket: S stamina ＋ -> the ticket ->
# 決定 -> 閉じる.
c tap:590:992 wait:3000 shot:$S/15-heal-items.png tap:364:515 wait:3000 shot:$S/15-heal.png tap:515:790
logw 'Sphere211StaminaHeal: sphere stamina 8 -> 9' 30 || fail "no stamina heal"
c wait:3000 shot:$S/15-healed.png tap:364:790 wait:2000
reenter; c tap:364:480; battle 20-cell2
reenter; c tap:364:285; battle 30-cell3
reenter; c $TOP shot:$S/35-board.png tap:490:965; battle 40-cell6
grep -q 'Sphere211MissionEnd: .*streak 4' "$L" || fail "four battles weren't cleared in a row"
reenter; return_dive 45
state > "$OUT/state-2-returned.txt"; cat "$OUT/state-2-returned.txt"
reenter; c $TOP shot:$S/49-board.png tap:490:790; battle 50-boss
state > "$OUT/state-3-cleared.txt"; cat "$OUT/state-3-cleared.txt"

# The goal (目標地点, New) -> 次のフロアへ -> 決定: Sphere211FloorClear.
reenter; c $TOP shot:$S/60-goal.png tap:364:625 wait:3000 shot:$S/62-next-floor.png tap:515:713
logw 'Sphere211FloorClear\(' 30 || fail "no Sphere211FloorClear"
c wait:5000 shot:$S/63-floor-result.png tap:364:970 wait:12000 shot:$S/64-floor-select.png
# 再設定 with the season's reroll ticket (Sphere211UseRerollItem re-lots the next-floor count)
c tap:220:962 wait:3000 shot:$S/64b-reroll-confirm.png tap:515:795
logw 'Sphere211UseRerollItem: next-floor lot' 30 || fail "no reroll"
c wait:5000 shot:$S/64c-rerolled.png
c tap:364:570 wait:1500 tap:510:962 wait:3000 shot:$S/65-confirm.png tap:515:713
logw 'Sphere211SelectedFloor\(1\): floor 1 -> 2' 30 || fail "no Sphere211SelectedFloor to floor 2"
c wait:8000 shot:$S/66-floor2.png
state > "$OUT/state-4-floor2.txt"; cat "$OUT/state-4-floor2.txt"

# 帰還 on floor 2: the floor-1 boss and floor-clear boxes analysed, everyone back.
return_dive 70
sql "update sphere set debug_enemy_level = null where id = 1"
state > "$OUT/state-5-returned.txt"; cat "$OUT/state-5-returned.txt"
c quit
wait $pid || true
trap - EXIT

ok=1
grep -q '^sphere .* floor 1 ' "$OUT/state-1-floor1.txt" || { echo "FAIL: the dive didn't start on floor 1"; ok=0; }
grep -q '^sphere .* floor 1 streak 0 ' "$OUT/state-2-returned.txt" || { echo "FAIL: mid-dive 帰還 didn't keep floor 1 / reset the streak"; ok=0; }
grep -q '^departed 0' "$OUT/state-2-returned.txt" || { echo "FAIL: characters still out after the first 帰還"; ok=0; }
grep -q '^sphere .* floor 1 streak 1 ' "$OUT/state-3-cleared.txt" || { echo "FAIL: the boss battle didn't count"; ok=0; }
grep -q '^sphere .* floor 2 streak 0 ' "$OUT/state-5-returned.txt" || { echo "FAIL: not on floor 2 with the streak reset after 帰還"; ok=0; }
grep -q '^boxes 0' "$OUT/state-5-returned.txt" || { echo "FAIL: boxes left unopened"; ok=0; }
grep -q '^departed 0' "$OUT/state-5-returned.txt" || { echo "FAIL: characters still out after 帰還"; ok=0; }
grep -q '^rank season [0-9]* best floor 2' "$OUT/state-5-returned.txt" || { echo "FAIL: the ranking's best floor isn't 2"; ok=0; }
grep -E 'I/server: (GetSphere211Info|Sphere211|ReturnSphere211)' "$L" | grep -v 'Sphere211: season' || true
grep -q 'refused with error\|Sphere211.* refused' "$L" && { grep 'refused' "$L"; echo "FAIL: a request was refused"; ok=0; }
grep -q 'MissionStart: rental helper' "$L" || { echo "FAIL: no rental"; ok=0; }
[ $ok = 1 ] && echo "PASS: Sphere 211 entered from home (rental bonus popup), 4 battles (a rental on the first, stamina healed after it), 帰還, the boss, floor 1 cleared, the floor count rerolled, floor 2 entered, 帰還 analysed the boxes" || exit 1
