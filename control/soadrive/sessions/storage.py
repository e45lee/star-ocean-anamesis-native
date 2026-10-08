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


def step(s, name, rx, xy, shot=None, secs=40):
    """A tap that sends a request: the server's line (common.tap_to_server), then the screen after it."""
    return common.tap_to_server(s, name, rx, ["tap:" + xy], shot, secs)


def screen(s, name, xy, shot=None, **kw):
    return common.tap_to_screen(s, name, xy, shot, **kw)


def select(s, *rows):
    """Rows of a list ticked: a tick changes little and a second tap takes it off, so no retap;
    the request after them (its server line with the count) checks them."""
    for xy in rows:
        common.tap_settled(s, xy)


def item_menu(s, shot, from_home):
    if not from_home:
        common.tap_to_phase(s, "ホーム", "60:1245", 4, mask=common.HOME_MASK, fatal=True)
    common.tap_to_phase(s, "アイテム", ITEM_MENU[4:], 9, fatal=True, mask=common.HOME_MASK)
    s.ctl("drag:364:900:364:300")
    common.settle(s, shot)


def boot1(s):
    common.port_login(s, notice=None, bonus=None)
    common.settle(s, mask=common.HOME_MASK)
    item_menu(s, "03-item-menu", True)
    # 装備倉庫にしまう: three weapons -> 決定 -> 決定
    screen(s, "装備倉庫にしまう", DEPOSIT, "04-deposit")
    select(s, ROW1, ROW2, ROW3)
    screen(s, "しまう: 決定", DECIDE, "05-deposit-confirm")
    step(s, "DepositItem: three weapons stored", r"DepositItem: 3 items into the storage", CONFIRM, "06-deposited")
    screen(s, "stored: 閉じる", CLOSE)
    # 取り出す: the first stored one
    screen(s, "取り出す", SWITCH, "07-withdraw")
    select(s, ROW1)
    screen(s, "取り出す: 決定", DECIDE)
    step(s, "WithdrawItemFromStorage: one weapon back", r"WithdrawItemFromStorage: 1 items back", CONFIRM, "08-withdrawn")
    screen(s, "withdrawn: 閉じる", CLOSE)
    screen(s, "戻る", BACK)
    # 装備倉庫から売却: the first stored one; the ★3 warning's 決定
    screen(s, "装備倉庫から売却", SELL)
    select(s, ROW1)
    screen(s, "売却: 決定", DECIDE, "09-sell-confirm")
    screen(s, "売却: 決定 -> the ★3 warning", CONFIRM, "10-sell-warning")
    step(s, "SellItemsFromStorage: one weapon sold", r"SellItemsFromStorage: \+[0-9]+ FOL \(1 items\)", "515:800", "11-sold")
    screen(s, "sold: 閉じる", CLOSE)
    # the present box: the weapons' present (the first row; 全件取得 leaves equipment out) -> two
    # weapons fit, the third goes to the overflow box
    common.tap_to_phase(s, "ホーム", "60:1245", 4, mask=common.HOME_MASK, fatal=True)
    common.tap_to_phase(s, "プレゼント", "668:320", 14, "12-presents", fatal=True)
    step(s, "the present's third weapon went to the overflow box", r"overflow box: \+1 of item", "364:385", "13-received", 60)
    screen(s, "received: 閉じる", CLOSE)
    # 一時保管庫から取り出す: the entry (NEW); 戻る clears the badge
    item_menu(s, "14-item-menu", False)
    step(s, "GetOneTimeStorageInfo: the entry listed", r"GetOneTimeStorageInfo: 1 entries", ONE_TIME, "15-one-time")
    step(s, "ClearNewOneTimeStorageItem: the badge cleared", r"ClearNewOneTimeStorageItem: 1 entries", BACK, "16-back", 30)


def boot2(s):
    common.port_login(s, notice=None, bonus=None)
    common.settle(s, mask=common.HOME_MASK)
    item_menu(s, "r03-item-menu", True)
    step(s, "after a re-login the storage holds the one weapon", r"GetStorageInfo: 1 items in the storage", WITHDRAW, "r04-storage")
    # しまう one more (room in the inventory for the box's weapon)
    screen(s, "しまう", SWITCH)
    select(s, ROW1)
    screen(s, "しまう: 決定", DECIDE)
    step(s, "DepositItem: one more stored", r"DepositItem: 1 items into the storage", CONFIRM)
    screen(s, "stored: 閉じる", CLOSE)
    screen(s, "戻る", BACK)
    # 一時保管庫: the entry -> the count dialog's 決定 -> 決定 -> 決定
    step(s, "after a re-login the overflow box holds its entry", r"GetOneTimeStorageInfo: 1 entries", ONE_TIME, "r05-one-time")
    # the entry ticked (選択中; a count dialog for a stack, whose 決定 is at 515:992: with one item
    # none opens, and that tap hits nothing)
    common.tap_settled(s, ROW1, "r06-count")
    common.tap_settled(s, "515:992")
    screen(s, "決定", DECIDE, "r07-confirm")
    step(s, "the box's weapon taken out", r"(Bulk)?WithdrawItemFromOneTimeStorage: 1 items from the overflow box", CONFIRM, "r08-taken")
    screen(s, "taken: 閉じる", CLOSE, "r09-empty")


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
