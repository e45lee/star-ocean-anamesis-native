#!/bin/sh
# Scripted session of the growth screens under the in-process local server (agent server-rules): the restored 3.7.0
# character menu (CPartyComposition, footer "キャラクター", phase 11) and the item menu (phase 9):
#   status strengthening (BoostCharacter) of a ★5 to its level cap -> evolution to ★6
#   (EvolutionCharacter) -> limit break (LimitBreakCharacter) -> weapon custom (CCustomGear):
#   set a gear on a slotted weapon (AttachGear), take it off again (RemoveGear) and purify gear
#   (GenerateGear).
# The materials (EXP, limit-break and evolution items, slotted swords at limit break 5, their gear,
# grease and carrots) are written into the server's state DB before boot.
# Screenshots go to OUT/shots, the log to OUT/log.txt; the script checks the server's log for
# each request and its effect and exits 1 on a failure. GROWTH_KEEP=1 leaves the game running.
#
# The phone: the shared pre-downloaded one, linked (port/scripts/phone370.sh); SOA_PHONE=DIR another,
# SOA_PHONE=none an empty one (the client then downloads its 3 GB from the in-process CDN after Login).
# Usage: port/scripts/growth_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
set -eu
SOA=$1; OUT=$2; TMP=$3
# Paths relative to the caller's directory stay valid; the rest of the script runs from the repo root.
abs() { case $1 in /*) echo "$1" ;; *) echo "$PWD/$1" ;; esac; }
SOA=$(abs "$SOA"); OUT=$(abs "$OUT"); TMP=$(abs "$TMP"); cd "$(dirname "$0")/../.."
export SOA_HEADLESS="${SOA_HEADLESS:-1}"  # soa --headless (no window); SOA_HEADLESS=0 to watch
CTL=control/soactl.py; FLOW=control/flowctl.py
rm -rf "${TMP:?}/data" "${TMP:?}/fifo" "${OUT:?}/shots" "${OUT:?}/log.txt" "${OUT:?}/log.txt.pos"
mkdir -p "$OUT/shots"
# The phone: the shared pre-downloaded one linked, SOA_PHONE's, or empty (port/scripts/phone370.sh);
# the 3.7.0 client makes its own local KVS.
. port/scripts/phone370.sh
phone370_prepare "$TMP/data"
phone370_client_save "$TMP/data/data/shared_prefs"
.venv/bin/python - "$TMP/data/server.sqlite3" <<'PY'
import sqlite3, sys
m = sqlite3.connect("work/../data/basmaster-3.7.0.sqlite3")
st = sqlite3.connect(sys.argv[1])
st.execute("create table stock (master_item_id integer primary key, item_type integer, count integer)")
st.execute("create table items (uid integer primary key, master_item_id integer, item_type integer, level integer default 1, "
           "exp integer default 0, limit_break integer default 0, locked integer default 0, created_at integer)")
st.execute("create table if not exists gear_items (uid integer primary key, type integer default 0, master_item_id integer, "
           "param2 integer default 0, item_uid integer default 0, slot integer default 0, is_new integer default 1, created_at integer)")
def add(i, n):
    t = m.execute("select type from master_item where id = ?", (i,)).fetchone()[0]
    st.execute("insert or replace into stock values (?,?,?)", (i, t, n))
def label(l): return m.execute("select id from master_item where id_label = ?", (l,)).fetchone()[0]
for l in ["item_exp_all_05", "item_exp_all_04"]: add(label(l), 200)
for (i,) in m.execute("select id from master_item where id_label like 'item_limitbreak_%'"): add(i, 200)
for r in m.execute("select master_item1_id, master_item2_id, master_item3_id, master_item4_id from master_role_evolution"):
    for i in r:
        if i: add(i, 500)
for l in ["item_grease", "item_carrot1", "item_carrot2", "item_carrot3"]: add(label(l), 5)
kind = m.execute("select master_weapon_kind_id from master_weapon where master_weapon_kind_id_label = 'W01Sw' limit 1").fetchone()[0]
slot_w = m.execute("select i.id from master_item i join master_weapon w on w.id = i.master_weapon_id where w.master_weapon_kind_id = ? "
                   "and i.max_gear_slot_num >= 3 order by i.rarity desc, i.id limit 1", (kind,)).fetchone()[0]
cheap = m.execute("select i.id from master_item i join master_weapon w on w.id = i.master_weapon_id where w.master_weapon_kind_id = ? "
                  "and i.type = 1 and i.rarity = 3 order by i.id limit 1", (kind,)).fetchone()[0]
uid = 0x7d0f0000
for k in range(2):
    st.execute("insert into items (uid, master_item_id, item_type, limit_break, created_at) values (?,?,1,5,0)", (uid, slot_w)); uid += 1
for k in range(4):
    st.execute("insert into items (uid, master_item_id, item_type, created_at) values (?,?,1,0)", (uid, cheap)); uid += 1
for k, (g,) in enumerate(m.execute("select i.id from master_item i join master_gear g on g.id = i.master_gear_id where i.type = 15 "
                                   "and g.master_weapon_kind_id = ? order by i.rarity desc, i.id limit 3", (kind,))):
    st.execute("insert into gear_items (uid, type, master_item_id, created_at) values (?,0,?,0)", (0x7c0f0000 + k, g))
st.commit()
PY
SOA_SERVER_SEED_RNG=${SOA_SERVER_SEED_RNG:-1} timeout -k 10 2400 "$SOA" --data "$TMP/data" \
  --size 729x1296 --control "$TMP/fifo" > "$OUT/log.txt" 2>&1 &
pid=$!
[ "${GROWTH_KEEP:-0}" = 1 ] || trap 'kill $pid 2>/dev/null || true' EXIT
while [ ! -p "$TMP/fifo" ]; do sleep 1; done
S=$OUT/shots; L=$OUT/log.txt
c() { python3 $CTL --timeout 400 "$TMP/fifo" "$@" > /dev/null; }
logw() { python3 $FLOW wait-log "$L" "$1" "${2:-120}"; }
ok=1
check() { if grep -qE "$1" "$L"; then echo "PASS: $2"; else echo "FAIL: $2 ($1)"; ok=0; fi; }

# The title (phase 1), TAP TO START -> Login -> the data check (or the download) -> home (phase 4).
phone370_title "$TMP/fifo" "$L"; c shot:$S/01-title.png
phone370_login "$TMP/fifo" "$L" "$S"
# notice board, then the 3.7.0 LOGIN BONUS popup (flowctl.py login-popups; the sessions since home370)
python3 $FLOW login-popups "$TMP/fifo" "$L" - - $S/02-home.png

# ---- character menu -> ステータス強化: the ★5 at LV50 (first row, fifth) to its cap with 14 EXP items
c tap:180:1245; logw 'port_debug: phase 11 '
c wait:6000 shot:$S/03-character-menu.png tap:364:547 wait:5000 shot:$S/04-strengthen-select.png
c tap:630:330 wait:4000 shot:$S/05-strengthen.png tap:364:540 wait:3000
plus=""; for i in $(seq 1 19); do plus="$plus tap:607:760 wait:150"; done
c $plus wait:3000 shot:$S/06-strengthen-count.png tap:515:993 wait:4000 shot:$S/07-strengthen-confirm.png tap:515:993
logw 'BoostCharacter [0-9a-f]+: 14 x item' 30
c wait:6000 shot:$S/08-strengthen-anim.png tap:364:700 wait:4000 shot:$S/09-strengthen-result.png
# ---- close -> 戻る: "レベルが上限に到達しました ... 進化しますか?" -> 進化する -> 実行
c tap:364:910 wait:2500 tap:100:1120 wait:3000 shot:$S/10-evolve-offer.png tap:515:800 wait:5000 shot:$S/11-evolve.png
c tap:620:1120 wait:3000 shot:$S/12-evolve-confirm.png tap:515:810
logw 'EvolutionCharacter [0-9a-f]+: role' 30
c wait:11000 shot:$S/13-evolve-result.png tap:364:910 wait:2500 shot:$S/14-evolve-skill.png tap:364:800 wait:3000 shot:$S/15-evolve-level1.png
# "進化したため、レベルが1になりました" -> 閉じる -> 戻る to the menu
c tap:212:712 wait:2500 tap:100:1120 wait:3000 shot:$S/16-character-menu.png

# ---- 限界突破: the first ★5 of the second row, the first material (×1), 実行
c tap:364:658 wait:5000 shot:$S/17-limitbreak-select.png tap:95:460 wait:4000 shot:$S/18-limitbreak.png
c tap:243:822 wait:3000 shot:$S/19-limitbreak-confirm.png tap:515:800
logw 'LimitBreakCharacter [0-9a-f]+: limit break 0 -> 1' 30
c wait:8000 shot:$S/20-limitbreak-result.png wait:4000 shot:$S/21-limitbreak-result2.png

# ---- the footer's アイテム: the item menu (phase 9) -> 武器カスタム -> the slotted sword -> the first gear -> セット開始 -> セット実行 -> 決定
# (the limit-break result's 閉じる first: the footer doesn't take taps under it)
c tap:364:910 wait:3000
python3 $FLOW tap-until "$TMP/fifo" "$L" 'port_debug: phase 9 ' 60 20 3 -- tap:300:1250 > /dev/null || { echo "FAIL: アイテム didn't open the item menu"; ok=0; }
c wait:5000 shot:$S/22-item-menu.png tap:364:570 wait:6000 shot:$S/23-custom.png
c tap:364:400 wait:4000 shot:$S/24-custom-gears.png tap:300:610 wait:3000 shot:$S/25-custom-selected.png
c tap:620:1120 wait:3000 shot:$S/26-custom-detail.png tap:515:1012 wait:3000 shot:$S/27-custom-confirm.png tap:515:712
logw 'AttachGear: gear [0-9]+ -> weapon' 30
c wait:5000 shot:$S/28-custom-done.png tap:364:700 wait:3000 shot:$S/29-custom-customised.png
# ---- ギア解除 (one ウェルチ特製グリス) -> はい -> 解除実行
c tap:364:800 wait:2500 tap:620:1120 wait:3000 shot:$S/30-remove-confirm.png tap:515:800 wait:4000 shot:$S/31-remove-detail.png
c tap:515:1012
logw 'RemoveGear: [0-9]+ gear\(s\) off weapon' 30
c wait:5000 shot:$S/32-remove-done.png tap:364:800 wait:3000 shot:$S/33-remove-closed.png
# ---- 戻る -> ギア精製モード: one gear as material (素材選択 1 -> the first gear -> 決定) -> 精製開始 -> 決定
c tap:212:1012 wait:2000 tap:100:1120 wait:3000 shot:$S/34-custom-top.png tap:620:1120 wait:4000 shot:$S/35-purify.png
c tap:125:620 wait:4000 tap:300:450 wait:1500 tap:620:1120 wait:4000 shot:$S/36-purify-material.png
c tap:620:1120 wait:3000 tap:515:712
logw 'GenerateGear: rank value' 30
c wait:6000 shot:$S/37-purify-result.png

check 'BoostCharacter [0-9a-f]+: 14 x item .* level 50/0 -> 60/0' "strengthening to the cap"
check 'EvolutionCharacter [0-9a-f]+: role .* \(rarity 5\) -> .* \(rarity 6\)' "evolution to ★6"
check 'LimitBreakCharacter [0-9a-f]+: limit break 0 -> 1' "limit break"
check 'AttachGear: gear [0-9]+ -> weapon [0-9]+ slot' "gear set on the weapon"
check 'RemoveGear: [0-9]+ gear\(s\) off weapon' "gear taken off with grease"
check 'GenerateGear: rank value 150 -> rarity [1-5], [1-9] gear' "gear purified from one ★5 gear (rank value 150)"
if [ "${GROWTH_KEEP:-0}" != 1 ]; then
  c quit
  wait $pid || true
  trap - EXIT
fi
grep -aE 'BoostCharacter|EvolutionCharacter|LimitBreakCharacter|AttachGear|RemoveGear|GenerateGear|refused' "$L" | grep -v getprop || true
[ $ok = 1 ] && echo "PASS: growth screens" || exit 1
