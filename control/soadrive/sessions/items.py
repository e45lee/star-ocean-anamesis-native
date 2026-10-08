"""Session `items`: the item menu's lock, sale and enhancement against the local server, the
requests the in-process route once lost the arguments of (FakeApiCaller::LockItem / UnlockItem(u32
count, ...) are varargs: docs/client-changes.md "The varargs requests' uids"). Before boot the
server's state gets 12 loose ★3 weapons. Boot 1: アイテム -> 所持アイテム一覧 -> ロックモード, the
first row (LockItem) -> 戻る -> アイテム売却 one unlocked weapon (SellItemArray) -> 武器・アクセサリー
強化: the locked weapon as the base, one material (ItemComposeArray). The server's state DB then
holds one locked item, 10 items, the base at level 2. Boot 2, the same phone (the re-login check):
the list shows the lock (screenshot); the server still has it; ロックモード, the first row again
(UnlockItem): nothing locked. The milestones are the server's log lines (both targets). Screenshots
go to OUT/shots (the re-login's r*).
Prints "PASS: ..." (exit 0) or the failed checks and "FAIL: ..." (exit 1).

Usage: port/scripts/items_session.sh [--target port-inproc|port-server] <soa> <out-dir> <scratch-dir>
Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc (default), port-server (the weapons go into the state DB before the server opens it)."""
import sqlite3

from .. import milestones
from ..proc import repo_file
from . import common

TARGETS = ("port-inproc", "port-server")
WRAPPER = "port/scripts/items_session.sh"

ITEM_MENU = "tap:300:1250"
LIST, ENHANCE, SELL = "364:347", "364:458", "364:903"  # the item menu, not scrolled
ROW1, ROW2, ROW6 = "364:400", "364:500", "364:900"
LOCK_MODE = "615:1120"  # ロックモード / ロック解除 (leaves the mode)
DECIDE, CONFIRM, WARN_OK, CLOSE, BACK = "615:1120", "515:1000", "515:800", "364:800", "100:1120"
MATERIAL_SLOT = "121:770"
RESULT_CLOSE = "364:1012"
PLANTED = 12
PLANTED_UID0 = 0x7d0f0000  # below the server's own item uids (core/ids.h kItemUid0 + n)


def options(ap):
    common.port_options(ap, extra=False)


def plant(db):
    """12 loose ★3 weapons (the master's first two, alternating) in the state DB's pre-migration
    items table (the server migrates and seeds the file when it opens it)."""
    m = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
    st = sqlite3.connect(db)
    st.execute("create table items (uid integer primary key, master_item_id integer, item_type integer, level integer default 1, "
               "exp integer default 0, limit_break integer default 0, locked integer default 0, created_at integer)")
    ws = [r[0] for r in m.execute("select id from master_item where type = 1 and rarity = 3 and sale_fol > 0 order by id limit 2")]
    for k in range(PLANTED):
        st.execute("insert into items (uid, master_item_id, item_type, created_at) values (?,?,1,0)", (PLANTED_UID0 + k, ws[k % 2]))
    st.commit()


def screen(s, name, xy, shot=None, **kw):
    return common.tap_to_screen(s, name, xy, shot, **kw)


def step(s, name, rx, xy, shot=None, **kw):
    """A request's tap, its server line, the screen after it (common.tap_to_server)."""
    return common.tap_to_server(s, name, rx, ["tap:" + xy], shot, **kw)


def lock_mode(s):
    """ロックモード / ロック解除: a toggle (a second tap would undo it), made once on a settled screen."""
    common.tap_settled(s, LOCK_MODE)


def item_menu(s):
    common.settle(s, mask=common.HOME_MASK)
    common.tap_to_phase(s, "アイテム", ITEM_MENU[4:], 9, mask=common.HOME_MASK, fatal=True)


def boot1(s):
    common.port_login(s, notice=None, bonus=None)
    item_menu(s)
    # 所持アイテム一覧 -> ロックモード -> the first row (its lock icon: a small change)
    screen(s, "所持アイテム一覧", LIST)
    lock_mode(s)
    step(s, "LockItem: the first weapon locked (one uid)", r"LockItem: 1 items locked", ROW1, "03-locked", changes=False)
    lock_mode(s)
    screen(s, "戻る", BACK)
    # アイテム売却: the second row -> 決定 -> 決定 -> the ★3 warning's 決定
    screen(s, "アイテム売却", SELL)
    common.tap_settled(s, ROW2)
    screen(s, "売却: 決定", DECIDE)
    screen(s, "売却: 決定 -> the ★3 warning", CONFIRM, "04-sell-warning")
    step(s, "SellItem: one weapon sold", r"SellItem(Array)?: \+[0-9]+ FOL \(1 items\)", WARN_OK, "05-sold")
    screen(s, "sold: 閉じる", CLOSE)
    screen(s, "戻る", BACK, "05b-item-menu")
    # 武器・アクセサリー強化: the locked weapon (first row) as the base, the sixth row as the material
    screen(s, "武器・アクセサリー強化", ENHANCE)
    screen(s, "the base: the first row", ROW1)
    screen(s, "the material slot", MATERIAL_SLOT)
    common.tap_settled(s, ROW6)
    screen(s, "the material: 決定", DECIDE, "06-compose")
    screen(s, "強化: 決定", DECIDE)
    screen(s, "the dialog's 決定", WARN_OK)
    # the enhancement's animation waited out (settled three times in a row)
    step(s, "ItemCompose: the base enhanced with one material", r"ItemCompose [0-9a-f]+: \+[0-9]+ points", WARN_OK, "07-composed",
         hold=3)
    screen(s, "the result: 閉じる", RESULT_CLOSE)


def boot2(s):
    common.port_login(s, notice=None, bonus=None)
    item_menu(s)
    screen(s, "所持アイテム一覧", LIST, "r03-list")
    lock_mode(s)
    step(s, "UnlockItem: the locked weapon unlocked after a re-login", r"UnlockItem: 1 items unlocked", ROW1, "r04-unlocked",
         changes=False)
    lock_mode(s)


def state(db):
    st = sqlite3.connect("file:%s?mode=ro" % db, uri=True)
    locked = [r[0] for r in st.execute("select uid from items where locked = 1")]
    n = st.execute("select count(*) from items").fetchone()[0]
    top = st.execute("select max(level) from items").fetchone()[0]
    st.close()
    return locked, n, top


def main(o):
    s = common.port_run(o, common.port_config(o, limit=1800))
    s.before_client = lambda: plant(s.state_db)
    if not common.drive(s, boot1):
        return 1
    locked, n, top = state(s.state_db)
    print("after boot 1: locked %s, %d items, top level %s" % ([hex(u) for u in locked], n, top))
    fails = common.checks((len(locked) == 1, "%d items locked, not 1" % len(locked)),
                          (n == PLANTED - 2, "%d items, not %d (one sold, one material)" % (n, PLANTED - 2)),
                          (top == 2, "the base is level %s, not 2" % top))
    lock_uid = locked[0] if len(locked) == 1 else None
    s2 = common.port_run_again(o, common.port_config(o, limit=1200), "log-relogin.txt")
    if lock_uid is not None:
        # the lock survives the re-login: the server's answer to the second boot's player load has it
        s2.before_client = lambda: fails.extend(
            [] if state(s2.state_db)[0] == [lock_uid] else ["the lock didn't survive the first boot's end"])
    ok2 = common.drive(s2, boot2)
    if not ok2:
        fails.append("the re-login boot didn't finish")
    locked2, n2, _ = state(s2.state_db)
    print("after boot 2: locked %s, %d items" % ([hex(u) for u in locked2], n2))
    fails += common.checks((not locked2, "still locked after UnlockItem: %s" % locked2), (n2 == PLANTED - 2, "%d items after the re-login" % n2))
    for run in (s, s2):
        if milestones.count(run.server_log, r"refused with error"):
            fails.append("a request was refused (%s)" % run.server_log)
    return common.verdict(s2, fails, "the item lock (LockItem / UnlockItem with their variadic uid), a sale and an enhancement reach "
                          "the server and survive a re-login")
