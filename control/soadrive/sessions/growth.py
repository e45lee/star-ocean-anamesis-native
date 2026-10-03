"""Session `growth`: the growth screens under the in-process local server: the restored 3.7.0
character menu (CPartyComposition, footer キャラクター, phase 11) and the item menu (phase 9):
status strengthening (BoostCharacter) of a ★5 to its level cap -> evolution to ★6
(EvolutionCharacter) -> limit break (LimitBreakCharacter) -> weapon custom (CCustomGear): set a gear
on a slotted weapon (AttachGear), take it off again (RemoveGear) and purify gear (GenerateGear).
The materials (EXP, limit-break and evolution items, slotted swords at limit break 5, their gear,
grease and carrots) are written into the server's state DB before boot. Screenshots go to OUT/shots,
the log to OUT/log.txt; checks the server's log for each request and its effect ("PASS: x" /
"FAIL: x" per check, then "PASS: growth screens") and exits 1 on a failure. GROWTH_KEEP=1 leaves
the game running.

Usage: port/scripts/growth_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: GROWTH_KEEP, SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc (the phase lines; the materials go into the in-process server's state)."""
import re
import sqlite3

from ..flows import mission
from ..proc import repo_file
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "the materials are written into the in-process server's state DB before boot"
WRAPPER = "port/scripts/growth_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def materials(db):
    m = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
    st = sqlite3.connect(db)
    st.execute("pragma foreign_keys = on")  # PLAN-schema S1: every connection that writes the state
    st.execute("create table stock (master_item_id integer primary key, item_type integer, count integer)")
    st.execute("create table items (uid integer primary key, master_item_id integer, item_type integer, level integer default 1, "
               "exp integer default 0, limit_break integer default 0, locked integer default 0, created_at integer)")
    st.execute("create table if not exists gear_items (uid integer primary key, type integer default 0, master_item_id integer, "
               "param2 integer default 0, item_uid integer default 0, slot integer default 0, is_new integer default 1, created_at integer)")

    def add(i, n):
        t = m.execute("select type from master_item where id = ?", (i,)).fetchone()[0]
        st.execute("insert into stock (master_item_id, item_type, count) values (?,?,?) "
                   "on conflict(master_item_id) do update set item_type = excluded.item_type, count = excluded.count", (i, t, n))

    label = lambda lb: m.execute("select id from master_item where id_label = ?", (lb,)).fetchone()[0]
    for lb in ["item_exp_all_05", "item_exp_all_04"]:
        add(label(lb), 200)
    for (i,) in m.execute("select id from master_item where id_label like 'item_limitbreak_%'"):
        add(i, 200)
    for r in m.execute("select master_item1_id, master_item2_id, master_item3_id, master_item4_id from master_role_evolution"):
        for i in r:
            if i:
                add(i, 500)
    for lb in ["item_grease", "item_carrot1", "item_carrot2", "item_carrot3"]:
        add(label(lb), 5)
    kind = m.execute("select master_weapon_kind_id from master_weapon where master_weapon_kind_id_label = 'W01Sw' limit 1").fetchone()[0]
    slot_w = m.execute("select i.id from master_item i join master_weapon w on w.id = i.master_weapon_id where w.master_weapon_kind_id = ? "
                       "and i.max_gear_slot_num >= 3 order by i.rarity desc, i.id limit 1", (kind,)).fetchone()[0]
    cheap = m.execute("select i.id from master_item i join master_weapon w on w.id = i.master_weapon_id where w.master_weapon_kind_id = ? "
                      "and i.type = 1 and i.rarity = 3 order by i.id limit 1", (kind,)).fetchone()[0]
    uid = 0x7d0f0000
    for _ in range(2):
        st.execute("insert into items (uid, master_item_id, item_type, limit_break, created_at) values (?,?,1,5,0)", (uid, slot_w))
        uid += 1
    for _ in range(4):
        st.execute("insert into items (uid, master_item_id, item_type, created_at) values (?,?,1,0)", (uid, cheap))
        uid += 1
    for k, (g,) in enumerate(m.execute("select i.id from master_item i join master_gear g on g.id = i.master_gear_id where i.type = 15 "
                                       "and g.master_weapon_kind_id = ? order by i.rarity desc, i.id limit 3", (kind,)).fetchall()):
        st.execute("insert into gear_items (uid, type, master_item_id, created_at) values (?,0,?,0)", (0x7c0f0000 + k, g))
    st.commit()


CHECKS = (
    (r"BoostCharacter [0-9a-f]+: 14 x item .* level 50/0 -> 60/0", "strengthening to the cap"),
    (r"EvolutionCharacter [0-9a-f]+: role .* \(rarity 5\) -> .* \(rarity 6\)", "evolution to ★6"),
    (r"LimitBreakCharacter [0-9a-f]+: limit break 0 -> 1", "limit break"),
    (r"AttachGear: gear [0-9]+ -> weapon [0-9]+ slot", "gear set on the weapon"),
    (r"RemoveGear: [0-9]+ gear\(s\) off weapon", "gear taken off with grease"),
    (r"GenerateGear: rank value 150 -> rarity [1-5], [1-9] gear", "gear purified from one ★5 gear (rank value 150)"),
)


def main(o):
    s = common.port_run(o, common.port_config(o, limit=2400))
    s.before_client = lambda: materials(s.state_db)
    c = s.ctl

    def body(s):
        common.port_login(s, notice=None, bonus=None)
        # ---- character menu -> ステータス強化: the ★5 at LV50 (first row, fifth) to its cap with 14 EXP items
        c("tap:180:1245")
        s.wait_log(mission.phase(11), 120, name="キャラクター -> the character menu")
        c("wait:6000", s.shot_cmd("03-character-menu"), "tap:364:547", "wait:5000", s.shot_cmd("04-strengthen-select"))
        c("tap:630:330", "wait:4000", s.shot_cmd("05-strengthen"), "tap:364:540", "wait:3000")
        c(*(["tap:607:760", "wait:150"] * 19 + ["wait:3000", s.shot_cmd("06-strengthen-count"), "tap:515:993", "wait:4000",
                                                s.shot_cmd("07-strengthen-confirm"), "tap:515:993"]))
        s.wait_log(r"BoostCharacter [0-9a-f]+: 14 x item", 30, name="BoostCharacter")
        c("wait:6000", s.shot_cmd("08-strengthen-anim"), "tap:364:700", "wait:4000", s.shot_cmd("09-strengthen-result"))
        # ---- close -> 戻る: "レベルが上限に到達しました ... 進化しますか?" -> 進化する -> 実行
        c("tap:364:910", "wait:2500", "tap:100:1120", "wait:3000", s.shot_cmd("10-evolve-offer"), "tap:515:800", "wait:5000",
          s.shot_cmd("11-evolve"))
        c("tap:620:1120", "wait:3000", s.shot_cmd("12-evolve-confirm"), "tap:515:810")
        s.wait_log(r"EvolutionCharacter [0-9a-f]+: role", 30, name="EvolutionCharacter")
        c("wait:11000", s.shot_cmd("13-evolve-result"), "tap:364:910", "wait:2500", s.shot_cmd("14-evolve-skill"), "tap:364:800", "wait:3000",
          s.shot_cmd("15-evolve-level1"))
        # "進化したため、レベルが1になりました" -> 閉じる -> 戻る to the menu
        c("tap:212:712", "wait:2500", "tap:100:1120", "wait:3000", s.shot_cmd("16-character-menu"))
        # ---- 限界突破: the first ★5 of the second row, the first material (×1), 実行
        c("tap:364:658", "wait:5000", s.shot_cmd("17-limitbreak-select"), "tap:95:460", "wait:4000", s.shot_cmd("18-limitbreak"))
        # the material, then 実行; resent when the server saw nothing (a tap on the material while
        # the screen still fades in is dropped: seen once under load, the confirmation never opened)
        s.tap_log(r"LimitBreakCharacter [0-9a-f]+: limit break 0 -> 1", 50, 15, 3, "tap:243:822", "wait:3000",
                  s.shot_cmd("19-limitbreak-confirm"), "tap:515:800", name="LimitBreakCharacter")
        c("wait:8000", s.shot_cmd("20-limitbreak-result"), "wait:4000", s.shot_cmd("21-limitbreak-result2"))
        # ---- アイテム -> 武器カスタム -> the slotted sword -> the first gear -> セット開始 -> セット実行 -> 決定
        # (the limit-break result's 閉じる first: the footer doesn't take taps under it)
        c("tap:364:910", "wait:3000")
        s.tap_log(mission.phase(9), 60, 20, 3, "tap:300:1250", name="アイテム -> the item menu", fatal=False)
        c("wait:5000", s.shot_cmd("22-item-menu"))
        # 武器カスタム (no log line: resent until the screen changes; once dropped under load)
        s.tap_until_changed("武器カスタム", "364:570", s.layout.shot_path("22-item-menu"), wait_ms=6000)
        c(s.shot_cmd("23-custom"))
        c("tap:364:400", "wait:4000", s.shot_cmd("24-custom-gears"), "tap:300:610", "wait:3000", s.shot_cmd("25-custom-selected"))
        c("tap:620:1120", "wait:3000", s.shot_cmd("26-custom-detail"), "tap:515:1012", "wait:3000", s.shot_cmd("27-custom-confirm"),
          "tap:515:712")
        s.wait_log(r"AttachGear: gear [0-9]+ -> weapon", 30, name="AttachGear")
        c("wait:5000", s.shot_cmd("28-custom-done"), "tap:364:700", "wait:3000", s.shot_cmd("29-custom-customised"))
        # ---- ギア解除 (one ウェルチ特製グリス) -> はい -> 解除実行
        c("tap:364:800", "wait:2500", "tap:620:1120", "wait:3000", s.shot_cmd("30-remove-confirm"), "tap:515:800", "wait:4000",
          s.shot_cmd("31-remove-detail"))
        c("tap:515:1012")
        s.wait_log(r"RemoveGear: [0-9]+ gear\(s\) off weapon", 30, name="RemoveGear")
        c("wait:5000", s.shot_cmd("32-remove-done"), "tap:364:800", "wait:3000", s.shot_cmd("33-remove-closed"))
        # ---- 戻る -> ギア精製モード: one gear as material (素材選択 1 -> the first gear -> 決定) -> 精製開始 -> 決定
        c("tap:212:1012", "wait:2000", "tap:100:1120", "wait:3000", s.shot_cmd("34-custom-top"), "tap:620:1120", "wait:4000",
          s.shot_cmd("35-purify"))
        c("tap:125:620", "wait:4000", "tap:300:450", "wait:1500", "tap:620:1120", "wait:4000", s.shot_cmd("36-purify-material"))
        c("tap:620:1120", "wait:3000", "tap:515:712")
        s.wait_log(r"GenerateGear: rank value", 30, name="GenerateGear")
        c("wait:6000", s.shot_cmd("37-purify-result"))
        if common.env_on("GROWTH_KEEP"):
            print("GROWTH_KEEP=1: soa keeps running (PID %d); stop it with control/soactl.py %s quit" % (s.client.pid, s.fifo))
            s.client = None  # not stopped below

    ok = common.drive(s, body)
    log = open(s.client_log, errors="replace").read()
    fails = 0
    for rx, what in CHECKS:
        if re.search(rx, log):
            print("PASS: " + what)
        else:
            print("FAIL: %s (%s)" % (what, rx))
            fails += 1
    for ln in log.splitlines():
        if re.search(r"BoostCharacter|EvolutionCharacter|LimitBreakCharacter|AttachGear|RemoveGear|GenerateGear|refused", ln) \
                and "getprop" not in ln:
            print(ln)
    if fails or not ok or s.failed:
        return 1
    print("PASS: growth screens")
    return 0
