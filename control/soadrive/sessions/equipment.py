"""Session `equipment`: an accessory's factor inheritance and the equipment screen's 自動設定 (the
local server: server/src/api/items/items.cpp, server/src/api/growth/growth.cpp;
docs/server-rules.md#accessory-inheritance, #equip-auto). Test setup in the server DB before the
boot (as the growth session): two inheritance accessories (master_item.max_inheritance_num), an
ordinary ★4 one and two one-handed swords (W01Sw, a weak and a strong one). Boot 1: title -> Login
-> home -> アイテム -> 武器・アクセサリー強化 -> アクセ -> the first inheritance accessory as the base ->
素材選択: the ordinary one (the other inheritance accessory is greyed out) -> 決定 -> 強化開始 -> the
three confirmations (InheritAccessory: the compose's points and FOL (the preview's 強化ポイント 5050:
the ★4 material's (level 1 + 100) x 5000 / 100, x weapon_compose_bonus_rate on a big success; the
★4 material's use_fol_one, 6000, the preview's 必要FOL, not the ★5 base's), the factor inherited) -> the
result -> キャラクター -> 装備・技・アシスト変更 -> ドーン (the fifth of the first row) -> 自動設定 -> 決定
(EquipAuto: the strong sword, the inheritance accessory, the skills). Boot 2 (the same phone):
Login -> home; the inheritance, the material gone and the equipment kept in the server state, and the
equipment screen shows them again.
Screenshots in OUT/shots, the logs OUT/log.txt and OUT/log-relogin.txt. Ends with PASS (exit 0) or
FAIL (exit 1). About 6 minutes.

Usage: port/scripts/equipment_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
Targets: port-inproc (default), port-server (the server's lines are read from soa-server's log)."""
import sqlite3

from ..proc import repo_file
from . import common

TARGETS = ("port-inproc", "port-server")
WRAPPER = "port/scripts/equipment_session.sh"

ITEM = "300:1250"           # the footer's アイテム
STRENGTHEN = "364:458"      # the item menu: 武器・アクセサリー強化
ACCESSORY_TAB = "460:238"   # the item select: アクセ
FIRST_ROW = "364:400"       # the list's first row (the base: the first inheritance accessory)
MATERIAL_SLOT = "121:770"   # the strengthening screen: the first 素材選択
SECOND_ROW = "364:500"      # the material list: the row after the base's (the ordinary accessory)
OK_RIGHT = "620:1120"       # 決定 / 強化開始 / 自動設定 (the lower right button)
DIALOG_OK = "515:800"       # the strengthening confirmations: 決定
RESULT_CLOSE = "364:1012"   # the result: 閉じる
CHARACTER = "180:1245"      # the footer's キャラクター
EQUIP = "364:435"           # the character menu: 装備・技・アシスト変更
DAWN = "630:330"            # the character select (rarity, descending): ドーン, the fifth of the first row
AUTO_OK = "515:713"         # 自動設定's confirmation: 決定
UID0 = 0x7d0f0000


def options(ap):
    common.port_options(ap, extra=False)


def plant(db):
    """Test setup (before the server seeds the state, as the growth session's): the accessories and
    swords as `items` rows of a version-0 state (the server migrates them)."""
    m = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
    st = sqlite3.connect(db)
    st.execute("pragma foreign_keys = on")  # PLAN-schema S1: every connection that writes the state
    st.execute("create table items (uid integer primary key, master_item_id integer, item_type integer, level integer default 1, "
               "exp integer default 0, limit_break integer default 0, locked integer default 0, created_at integer)")
    inherit = [r[0] for r in m.execute("select id from master_item where type = 3 and max_inheritance_num > 0 order by id limit 2")]
    plain = m.execute("select id from master_item where type = 3 and max_inheritance_num is null and rarity = 4 order by id limit 1").fetchone()[0]
    swords = [r[0] for r in m.execute(
        "select i.id from master_item i join master_weapon w on w.id = i.master_weapon_id where i.type = 1 and "
        "w.master_weapon_kind_id_label = 'W01Sw' and i.attack > 0 order by i.attack, i.id")]
    rows = [(inherit[0], 3), (inherit[1], 3), (plain, 3), (swords[0], 1), (swords[-1], 1)]
    for k, (item, kind) in enumerate(rows):
        st.execute("insert into items (uid, master_item_id, item_type, created_at) values (?,?,?,0)", (UID0 + k, item, kind))
    st.commit()
    st.close()
    # the compose's FOL: use_fol_one at the material's rarity (★4: 6000, the screen's 必要FOL), not
    # the base's (★5: 10000; docs/server-rules.md, ItemCompose)
    fol = m.execute("select c.use_fol_one from master_item i join master_item_accessory_compose c on c.rarity = i.rarity where i.id = ?",
                    (plain,)).fetchone()[0]
    # the compose's points: (the material's level 1 + 100) x boosted_point of its rarity / 100 (the
    # preview's 強化ポイント, 5050 for the ★4; docs/server-rules.md#compose-points)
    bp = m.execute("select c.boosted_point from master_item i join master_item_accessory_compose c on c.rarity = i.rarity where i.id = ?",
                   (plain,)).fetchone()[0]
    big = m.execute("select value from master_global where key = 'weapon_compose_bonus_rate'").fetchone()
    return {"base": UID0, "inherit2": UID0 + 1, "plain": UID0 + 2, "plain_item": plain, "weak": UID0 + 3, "strong": UID0 + 4, "fol": fol,
            "points": (1 + 100) * bp // 100, "big_rate": float(big[0]) if big else 1.5}


def state(db):
    c = sqlite3.connect(db, timeout=60)
    q = lambda sql, *a: c.execute(sql, a).fetchone()
    r = {
        "inherited": q("select inherited_master_item_id from items where uid = ?", UID0)[0],
        "exp": q("select exp from items where uid = ?", UID0)[0],
        "level": q("select level from items where uid = ?", UID0)[0],
        "plain_left": q("select count(*) from items where uid = ?", UID0 + 2)[0],
        "inherit2_left": q("select count(*) from items where uid = ?", UID0 + 1)[0],
    }
    row = q("select uid, weapon_uid, accessory_uid, equip_skill1 from roster where accessory_uid = ?", UID0)
    r["equip"] = row
    c.close()
    return r


def main(o):
    s = common.port_run(o, common.port_config(o, limit=2400))
    got = {}
    s.before_client = lambda: got.update(plant(s.state_db))
    def screen(name, xy, shot=None, **kw):
        return common.tap_to_screen(s, name, xy, shot, **kw)

    def body(s):
        common.port_login(s, notice=None, bonus=None)
        common.settle(s, mask=common.HOME_MASK)
        st0 = s.state("1-home")
        got["fol0"] = common.state_value(st0, r" fol ([0-9]+)")
        # ---- the inheritance
        common.tap_to_phase(s, "アイテム", ITEM, 9, "03-item-menu", mask=common.HOME_MASK, fatal=True)
        screen("武器・アクセサリー強化", STRENGTHEN)
        screen("アクセ", ACCESSORY_TAB, "04-accessories")
        screen("the base: the first row", FIRST_ROW, "05-base")
        screen("素材選択", MATERIAL_SLOT, "06-materials")
        common.tap_settled(s, SECOND_ROW)  # the material ticked (no retap: a second would untick it)
        screen("the material: 決定", OK_RIGHT, "07-preview")
        screen("強化開始", OK_RIGHT, "08-confirm-inherit")
        screen("the inheritance's 決定", DIALOG_OK, "09-confirm-lost")
        screen("the lost material's 決定", DIALOG_OK, "10-confirm-rare")
        # the last confirmation -> InheritAccessory (made again after 20 s without the line: one more
        # confirmation); the 強化成功 animation waited out (the session used to tap it short at 364:700)
        common.tap_to_server(s, "the confirmations -> InheritAccessory", r"InheritAccessory [0-9a-f]+: inherited item", ["tap:" + DIALOG_OK],
                             "11-inherited", secs=20, hold=3)
        s.keep_shot("11-result", s.layout.shot_path("11-inherited"))
        screen("the result: 閉じる", RESULT_CLOSE, "11-closed")
        got["big"] = s.in_server(r"InheritAccessory [0-9a-f]+: \+[0-9]+ points \(big success\)")
        st1 = s.state("2-inherited")
        got["fol1"] = common.state_value(st1, r" fol ([0-9]+)")
        # ---- 自動設定
        common.tap_to_phase(s, "キャラクター -> the character menu", CHARACTER, 11, every=8, tries=6, fatal=True)
        screen("装備・技・アシスト変更", EQUIP, "12-characters")
        screen("ドーン", DAWN, "13-equipment")
        screen("自動設定", OK_RIGHT, "14-auto-confirm")
        common.tap_to_server(s, "決定 -> EquipAuto", r"EquipAuto [0-9a-f]+: weapon", ["tap:" + AUTO_OK], "15-auto-equipped", secs=20)
        got["st1"] = state(s.state_db)

    if not common.drive(s, body):
        return 1
    # ---- boot 2: the re-login keeps them
    s2 = common.port_run_again(o, common.port_config(o, limit=2400), "log-relogin.txt")

    def again(s2):
        common.port_login(s2, title="20-title", notice=None, bonus=None, home="21-home")
        common.settle(s2, mask=common.HOME_MASK)
        common.tap_to_phase(s2, "キャラクター -> the character menu (after the re-login)", CHARACTER, 11, secs=120, mask=common.HOME_MASK,
                            fatal=True)
        common.tap_to_screen(s2, "装備・技・アシスト変更", EQUIP)
        common.tap_to_screen(s2, "ドーン", DAWN, "22-equipment-after-relogin")
        got["st2"] = state(s2.state_db)

    if not common.drive(s2, again):
        return 1
    st1, st2 = got.get("st1") or {}, got.get("st2") or {}
    print("after the inheritance and 自動設定: %s; after the re-login: %s; FOL %s -> %s" % (st1, st2, got.get("fol0"), got.get("fol1")))
    eq = st2.get("equip") or (None, None, None, None)
    fails = common.checks(
        (st2.get("inherited") == got.get("plain_item"), "the base didn't keep the ordinary accessory's item as its inheritance"),
        ((st2.get("level"), st2.get("exp")) == (1, int(got["points"] * got["big_rate"]) if got.get("big") else got.get("points")),
         "the base has level %s with %s points, not the preview's %s (level 1%s)" %
         (st2.get("level"), st2.get("exp"), got.get("points"), ", a big success x%s" % got.get("big_rate") if got.get("big") else "")),
        (got.get("fol0") is not None and got.get("fol1") is not None and got["fol0"] - got["fol1"] == got.get("fol"),
         "the inheritance paid %s FOL, not the material's use_fol_one %s (the preview's 必要FOL)" %
         (got["fol0"] - got["fol1"] if got.get("fol0") is not None and got.get("fol1") is not None else None, got.get("fol"))),
        (st2.get("plain_left") == 0, "the material wasn't used up"),
        (st2.get("inherit2_left") == 1, "the other inheritance accessory went"),
        (eq[1] == got.get("strong"), "自動設定 didn't equip the strong sword (weapon %s)" % eq[1]),
        (eq[2] == got.get("base"), "自動設定 didn't equip the inheritance accessory (accessory %s)" % eq[2]),
        (eq[3] is not None, "自動設定 set no skill"),
        (st2 == st1, "the state changed across the re-login"),
    ) + common.common_log_checks(s)
    return common.verdict(s2, fails, "an inheritance accessory took in an ordinary one's factor (a compose: points and FOL); 自動設定 "
                          "equipped the strong sword, that accessory and the skills; all kept across a re-login")
