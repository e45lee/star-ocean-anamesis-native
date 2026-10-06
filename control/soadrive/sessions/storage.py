"""Session `storage`: the equipment storage (装備倉庫) and the overflow box (一時保管庫) of the item
menu, against the local server (docs/server-rules.md#storage). Before boot the server's state gets 500
loose ★3 weapons (the inventory's item_stock: full) and a present of three other weapons. Boot 1:
アイテム -> 装備倉庫にしまう three (DepositItem) -> 取り出す one (WithdrawItemFromStorage) -> 戻る ->
装備倉庫から売却 one (SellItemsFromStorage) -> ホーム -> the present box's weapons (two fit, the
third goes to the overflow box: "overflow box: +1") -> 一時保管庫から取り出す (GetOneTimeStorageInfo:
the entry) -> 戻る (ClearNewOneTimeStorageItem). Boot 2, the same phone (the re-login check):
装備倉庫から取り出す lists the one stored item (GetStorageInfo) -> しまう one more -> 一時保管庫 ->
the entry, 決定 x2 (BulkWithdrawItemFromOneTimeStorage: one item out). The milestones are the
server's log lines (both targets), the end state the server's state DB: two stored items, the box
empty, the inventory full. Screenshots go to OUT/shots (the re-login's r*).
Prints "PASS: ..." (exit 0) or the failed checks and "FAIL: ..." (exit 1).

Usage: port/scripts/storage_session.sh [--target port-inproc|port-server] <soa> <out-dir> <scratch-dir>
Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc (default), port-server (the weapons go into the state DB before the server opens it)."""
import sqlite3
import time

from .. import milestones
from ..proc import repo_file
from . import common

TARGETS = ("port-inproc", "port-server")
WRAPPER = "port/scripts/storage_session.sh"

ITEM_MENU = "tap:300:1250"
DEPOSIT, WITHDRAW, SELL, ONE_TIME = "364:615", "364:727", "364:838", "364:948"  # the item menu scrolled down
ROW1, ROW2, ROW3 = "364:400", "364:500", "364:600"
DECIDE, CONFIRM, CLOSE, BACK = "630:1120", "515:1000", "364:800", "100:1120"
SWITCH = "625:235"  # しまう / 取り出す, top right of the storage screens
PLANTED_UID0 = 0x7d0f0000  # below the server's own item uids (core/ids.h kItemUid0 + n)


def options(ap):
    common.port_options(ap, extra=False)


def plant(db):
    """500 loose ★3 weapons (the master's first two, alternating) and a present of 3 x a third one,
    in the state DB's pre-migration tables (the server migrates and seeds the file when it opens it)."""
    m = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
    st = sqlite3.connect(db)
    st.execute("pragma foreign_keys = on")
    st.execute("create table items (uid integer primary key, master_item_id integer, item_type integer, level integer default 1, "
               "exp integer default 0, limit_break integer default 0, locked integer default 0, created_at integer)")
    st.execute("create table presents (id integer primary key autoincrement, content_type integer, content_id integer, "
               "num integer, reason_type integer, reason_param integer, created_at integer, received_at integer)")
    ws = [r[0] for r in m.execute("select id from master_item where type = 1 and rarity = 3 and sale_fol > 0 order by id limit 3")]
    cap = int(m.execute("select value from master_global where key = 'item_stock_max'").fetchone()[0])
    for k in range(cap):
        st.execute("insert into items (uid, master_item_id, item_type, created_at) values (?,?,1,0)", (PLANTED_UID0 + k, ws[1 + k % 2]))
    st.execute("insert into presents (content_type, content_id, num, reason_type, reason_param, created_at) values (1, ?, 3, 0, 0, ?)",
               (ws[0], int(time.time()) - 60))
    st.commit()
    return cap


def server_step(s, rx, name, secs=40):
    """Waits for the next server-log line matching rx (counted from the step's start)."""
    before = milestones.count(s.server_log, rx)
    return lambda: s.wait_for(name, secs, lambda: milestones.count(s.server_log, rx) > before)


def item_menu(s, shot):
    c = s.ctl
    c("tap:60:1245", "wait:5000", ITEM_MENU, "wait:5000", "drag:364:900:364:300", "wait:2500", s.shot_cmd(shot))


def boot1(s):
    c = s.ctl
    common.port_login(s, notice=None, bonus=None)
    item_menu(s, "03-item-menu")
    # 装備倉庫にしまう: three weapons -> 決定 -> 決定
    c("tap:" + DEPOSIT, "wait:5000", s.shot_cmd("04-deposit"), "tap:" + ROW1, "wait:800", "tap:" + ROW2, "wait:800", "tap:" + ROW3,
      "wait:800", "tap:" + DECIDE, "wait:3000", s.shot_cmd("05-deposit-confirm"))
    done = server_step(s, r"DepositItem: 3 items into the storage", "DepositItem: three weapons stored")
    c("tap:" + CONFIRM)
    done()
    c("wait:4000", s.shot_cmd("06-deposited"), "tap:" + CLOSE, "wait:2000")
    # 取り出す: the first stored one
    c("tap:" + SWITCH, "wait:5000", s.shot_cmd("07-withdraw"), "tap:" + ROW1, "wait:800", "tap:" + DECIDE, "wait:3000")
    done = server_step(s, r"WithdrawItemFromStorage: 1 items back", "WithdrawItemFromStorage: one weapon back")
    c("tap:" + CONFIRM)
    done()
    c("wait:4000", s.shot_cmd("08-withdrawn"), "tap:" + CLOSE, "wait:2000", "tap:" + BACK, "wait:4000")
    # 装備倉庫から売却: the first stored one; the ★3 warning's 決定
    c("tap:" + SELL, "wait:5000", "tap:" + ROW1, "wait:800", "tap:" + DECIDE, "wait:3000", s.shot_cmd("09-sell-confirm"), "tap:" + CONFIRM,
      "wait:3000", s.shot_cmd("10-sell-warning"))
    done = server_step(s, r"SellItemsFromStorage: \+[0-9]+ FOL \(1 items\)", "SellItemsFromStorage: one weapon sold")
    c("tap:515:800")
    done()
    c("wait:4000", s.shot_cmd("11-sold"), "tap:" + CLOSE, "wait:2000")
    # the present box: the weapons' present (the first row; 全件取得 leaves equipment out) -> two
    # weapons fit, the third goes to the overflow box
    done = server_step(s, r"overflow box: \+1 of item", "the present's third weapon went to the overflow box", 60)
    c("tap:60:1245", "wait:6000", "tap:668:320", "wait:5000", s.shot_cmd("12-presents"), "tap:364:385")
    done()
    c("wait:4000", s.shot_cmd("13-received"), "tap:" + CLOSE, "wait:2000")
    # 一時保管庫から取り出す: the entry (NEW); 戻る clears the badge
    item_menu(s, "14-item-menu")
    done = server_step(s, r"GetOneTimeStorageInfo: 1 entries", "GetOneTimeStorageInfo: the entry listed")
    c("tap:" + ONE_TIME)
    done()
    c("wait:4000", s.shot_cmd("15-one-time"))
    done = server_step(s, r"ClearNewOneTimeStorageItem: 1 entries", "ClearNewOneTimeStorageItem: the badge cleared", 30)
    c("tap:" + BACK)
    done()
    c("wait:3000", s.shot_cmd("16-back"))


def boot2(s):
    c = s.ctl
    common.port_login(s, notice=None, bonus=None)
    item_menu(s, "r03-item-menu")
    done = server_step(s, r"GetStorageInfo: 1 items in the storage", "after a re-login the storage holds the one weapon")
    c("tap:" + WITHDRAW)
    done()
    c("wait:4000", s.shot_cmd("r04-storage"))
    # しまう one more (room in the inventory for the box's weapon)
    c("tap:" + SWITCH, "wait:5000", "tap:" + ROW1, "wait:800", "tap:" + DECIDE, "wait:3000")
    done = server_step(s, r"DepositItem: 1 items into the storage", "DepositItem: one more stored")
    c("tap:" + CONFIRM)
    done()
    c("wait:4000", "tap:" + CLOSE, "wait:2000", "tap:" + BACK, "wait:4000")
    # 一時保管庫: the entry -> the count dialog's 決定 -> 決定 -> 決定
    done = server_step(s, r"GetOneTimeStorageInfo: 1 entries", "after a re-login the overflow box holds its entry")
    c("tap:" + ONE_TIME)
    done()
    c("wait:4000", s.shot_cmd("r05-one-time"), "tap:" + ROW1, "wait:3000", s.shot_cmd("r06-count"), "tap:515:992", "wait:2000",
      "tap:" + DECIDE, "wait:3000", s.shot_cmd("r07-confirm"))
    done = server_step(s, r"(Bulk)?WithdrawItemFromOneTimeStorage: 1 items from the overflow box", "the box's weapon taken out")
    c("tap:" + CONFIRM)
    done()
    c("wait:4000", s.shot_cmd("r08-taken"), "tap:" + CLOSE, "wait:2000", s.shot_cmd("r09-empty"))


def main(o):
    s = common.port_run(o, common.port_config(o, limit=2400))
    cap = [0]
    s.before_client = lambda: cap.__setitem__(0, plant(s.state_db))
    if not common.drive(s, boot1):
        return 1
    s2 = common.port_run_again(o, common.port_config(o, limit=1800), "log-relogin.txt")
    ok2 = common.drive(s2, boot2)
    fails = [] if ok2 else ["the re-login boot didn't finish"]
    st = sqlite3.connect("file:%s?mode=ro" % s2.state_db, uri=True)
    stored = st.execute("select count(*) from items where stored_at is not null").fetchone()[0]
    inv = st.execute("select count(*) from items where stored_at is null").fetchone()[0]
    box = st.execute("select count(*) from one_time_storage").fetchone()[0]
    print("end state: %d stored, %d in the inventory (of %d), %d box entries" % (stored, inv, cap[0], box))
    fails += common.checks((stored == 2, "the storage holds %d items, not 2" % stored), (box == 0, "the overflow box isn't empty"),
                           (inv == cap[0], "the inventory holds %d, not %d" % (inv, cap[0])))
    for run in (s, s2):
        if milestones.count(run.server_log, r"refused with error"):
            fails.append("a request was refused (%s)" % run.server_log)
    return common.verdict(s2, fails, "the equipment storage (deposit, withdraw, sell) and the overflow box (filled by a present on a "
                          "full inventory, listed, badge cleared, taken out) work and survive a re-login")
