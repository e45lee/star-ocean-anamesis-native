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

    def screen(name, xy, shot=None, **kw):
        return common.tap_to_screen(s, name, xy, shot, **kw)

    def req(name, xy, rx, shot=None, **kw):
        """A request's tap, once: the client plays an animation before some requests (BoostCharacter
        came 12 s after its tap), so a resent tap would land on the screen after it. An animation
        follows most of them too: the screen after it must hold still a while."""
        return common.tap_to_log(s, name, xy, rx, shot, secs=60, tries=1, fatal=True, settle_hold=3, **kw)

    def body(s):
        common.port_login(s, notice=None, bonus=None)
        common.settle(s, mask=common.HOME_MASK)
        # ---- character menu -> ステータス強化: the ★5 at LV50 (first row, fifth) to its cap with 14 EXP items
        common.tap_to_phase(s, "キャラクター -> the character menu", "180:1245", 11, "03-character-menu", secs=120,
                            mask=common.HOME_MASK, fatal=True)
        screen("ステータス強化", "364:547", "04-strengthen-select")
        screen("the ★5 at LV50", "630:330", "05-strengthen")
        screen("the EXP items", "364:540")
        # the count's +, 19 times (the count stops at the cap: 14); one tap's change is a digit, and
        # BoostCharacter's "14 x item" checks the count, so the taps are only paced
        c(*(["tap:607:760", "wait:150"] * 19))
        common.settle(s, "06-strengthen-count")
        screen("強化: 決定", "515:993", "07-strengthen-confirm")
        # (the strengthening animation waited out: the session used to tap it short at 364:700)
        req("BoostCharacter", "515:993", r"BoostCharacter [0-9a-f]+: 14 x item", "08-strengthen-anim")
        s.keep_shot("09-strengthen-result", s.layout.shot_path("08-strengthen-anim"))
        # ---- close: "レベルが上限に到達しました ... 進化しますか?" comes by itself (the session's 戻る after
        # 閉じる tapped nothing) -> 進化する -> 実行
        screen("the result: 閉じる -> the evolution offer", "364:910", "10-evolve-offer", hold=3)
        screen("進化する", "515:800", "11-evolve")
        screen("進化: 実行", "620:1120", "12-evolve-confirm")
        req("EvolutionCharacter", "515:810", r"EvolutionCharacter [0-9a-f]+: role", "13-evolve-result")
        # the result, the new skill, "進化したため、レベルが1になりました": each closed, made again until the
        # screen changes (a close dropped under load left the next taps on the wrong dialog), then 戻る
        screen("the evolution result closed", "364:910", "14-evolve-skill")
        screen("the new skill's dialog closed", "364:800", "15-evolve-level1")
        screen("the level-1 dialog closed", "212:712")
        screen("戻る", "100:1120", "16-character-menu")
        # ---- 限界突破: the first ★5 of the second row, the first material (×1), 実行
        screen("限界突破", "364:658", "17-limitbreak-select")
        screen("the first ★5 of the second row", "95:460", "18-limitbreak")
        # the material opens the confirmation (a tap on it while the screen still fades in is dropped:
        # seen once under load, the confirmation never opened)
        screen("the material -> the confirmation", "243:822", "19-limitbreak-confirm")
        req("LimitBreakCharacter", "515:800", r"LimitBreakCharacter [0-9a-f]+: limit break 0 -> 1", "20-limitbreak-result")
        common.settle(s, "21-limitbreak-result2", hold=3)
        # ---- アイテム -> 武器カスタム -> the slotted sword -> the first gear -> セット開始 -> セット実行 -> 決定
        # (the limit-break result's 閉じる first: the footer doesn't take taps under it)
        screen("the limit-break result: 閉じる", "364:910")
        common.tap_to_phase(s, "アイテム -> the item menu", "300:1250", 9, "22-item-menu")
        screen("武器カスタム", "364:570", "23-custom")
        screen("the slotted sword", "364:400", "24-custom-gears")
        screen("the first gear", "300:610", "25-custom-selected")
        screen("セット開始", "620:1120", "26-custom-detail")
        screen("セット実行", "515:1012", "27-custom-confirm")
        # (the animation waited out: the session used to tap it short at 364:700)
        req("AttachGear", "515:712", r"AttachGear: gear [0-9]+ -> weapon", "28-custom-done")
        s.keep_shot("29-custom-customised", s.layout.shot_path("28-custom-done"))
        # ---- ギア解除 (one ウェルチ特製グリス) -> はい -> 解除実行
        screen("閉じる", "364:800")
        screen("ギア解除", "620:1120", "30-remove-confirm")
        screen("はい", "515:800", "31-remove-detail")
        req("RemoveGear", "515:1012", r"RemoveGear: [0-9]+ gear\(s\) off weapon", "32-remove-done")
        screen("the gear removed: 閉じる", "364:800", "33-remove-closed")
        # ---- 戻る -> ギア精製モード: one gear as material (素材選択 1 -> the first gear -> 決定) -> 精製開始 -> 決定
        # the session's 212:1012 (a dialog's left 閉じる): after the gear came back no dialog is up and it
        # taps nothing, kept for the run where one is
        common.tap_settled(s, "212:1012")
        screen("戻る", "100:1120", "34-custom-top")
        screen("ギア精製モード", "620:1120", "35-purify")
        screen("素材選択 1", "125:620")
        # a tick on the first gear (a second tap would take it off; GenerateGear's rank value checks it)
        common.tap_settled(s, "300:450")
        screen("素材: 決定", "620:1120", "36-purify-material")
        screen("精製開始", "620:1120")
        req("GenerateGear", "515:712", r"GenerateGear: rank value", "37-purify-result")
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
