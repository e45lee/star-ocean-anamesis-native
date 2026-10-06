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


def server_step(s, rx, name, secs=40):
    """Waits for the next server-log line matching rx (counted from the step's start)."""
    before = milestones.count(s.server_log, rx)
    return lambda: s.wait_for(name, secs, lambda: milestones.count(s.server_log, rx) > before)


def item_menu(s):
    s.ctl("tap:60:1245", "wait:5000", ITEM_MENU, "wait:5000")


def boot1(s):
    c = s.ctl
    common.port_login(s, notice=None, bonus=None)
    item_menu(s)
    # 所持アイテム一覧 -> ロックモード -> the first row
    c("tap:" + LIST, "wait:5000", "tap:" + LOCK_MODE, "wait:2500")
    done = server_step(s, r"LockItem: 1 items locked", "LockItem: the first weapon locked (one uid)")
    c("tap:" + ROW1)
    done()
    c("wait:2000", s.shot_cmd("03-locked"), "tap:" + LOCK_MODE, "wait:1500", "tap:" + BACK, "wait:3000")
    # アイテム売却: the second row -> 決定 -> 決定 -> the ★3 warning's 決定
    c("tap:" + SELL, "wait:5000", "tap:" + ROW2, "wait:1000", "tap:" + DECIDE, "wait:3000", "tap:" + CONFIRM, "wait:3000",
      s.shot_cmd("04-sell-warning"))
    done = server_step(s, r"SellItem(Array)?: \+[0-9]+ FOL \(1 items\)", "SellItem: one weapon sold")
    c("tap:" + WARN_OK)
    done()
    c("wait:4000", s.shot_cmd("05-sold"), "tap:" + CLOSE, "wait:2000", "tap:" + BACK, "wait:3000")
    # 武器・アクセサリー強化: the locked weapon (first row) as the base, the sixth row as the material
    c("tap:" + ENHANCE, "wait:5000", "tap:" + ROW1, "wait:5000", "tap:" + MATERIAL_SLOT, "wait:4000", "tap:" + ROW6, "wait:1000",
      "tap:" + DECIDE, "wait:4000", s.shot_cmd("06-compose"), "tap:" + DECIDE, "wait:3000", "tap:" + WARN_OK, "wait:3000")
    done = server_step(s, r"ItemCompose [0-9a-f]+: \+[0-9]+ points", "ItemCompose: the base enhanced with one material")
    c("tap:" + WARN_OK)
    done()
    c("wait:10000", s.shot_cmd("07-composed"), "tap:" + RESULT_CLOSE, "wait:2500")


def boot2(s):
    c = s.ctl
    common.port_login(s, notice=None, bonus=None)
    item_menu(s)
    c("tap:" + LIST, "wait:5000", s.shot_cmd("r03-list"), "tap:" + LOCK_MODE, "wait:2500")
    done = server_step(s, r"UnlockItem: 1 items unlocked", "UnlockItem: the locked weapon unlocked after a re-login")
    c("tap:" + ROW1)
    done()
    c("wait:2000", s.shot_cmd("r04-unlocked"), "tap:" + LOCK_MODE, "wait:1500")


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
