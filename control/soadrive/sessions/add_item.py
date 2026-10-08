"""Session `add-item`: a response's new weapon reaches the client at once (AddItem as a map
{uid: CItemInfo}, docs/server-rules.md#conventions; before, the server sent an array, which the
client ignores, and the weapon appeared only with the next full player load). Boot: the footer's
ガチャ -> 武器ガチャ -> the first banner -> 1回ガチャ -> 決定 (Gacha: one weapon) -> the summon ->
アイテム -> 所持アイテム一覧 (a shot: the seeded player has no loose weapon, so the list shows the new
one, 装備所持 1) -> アイテム売却 -> the weapon -> 決定 -> 決定 (and the ★3 warning's 決定) ->
SellItemArray. The client sells only items it holds, so the sale of the drawn weapon's uid (the
server's state: gacha_history's item gone from items) with no Login / GetPlayer between the draw and
the sale proves the client took the AddItem. Milestones: the server log and the packet log (both
targets). Screenshots go to OUT/shots.
Prints "PASS: ..." (exit 0) or the failed checks and "FAIL: ..." (exit 1).

Usage: port/scripts/add_item_session.sh [--target port-inproc|port-server] <soa> <out-dir> <scratch-dir>
Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc (default), port-server."""
import re
import sqlite3

from .. import milestones, ui370
from ..flows import gacha
from . import common

TARGETS = ("port-inproc", "port-server")
WRAPPER = "port/scripts/add_item_session.sh"

WEAPON_TAB, FIRST_BANNER, DRAW_1, DECIDE = "450:175", "360:315", "190:948", "515:800"
ITEM_MENU, ITEM_LIST, SELL_MENU, ROW1, BACK, OK = "300:1250", "364:345", "364:900", "364:400", "100:1120", "630:1120"


def options(ap):
    common.port_options(ap, extra=False)


def body(s):
    screen = lambda name, xy, shot=None, **kw: common.tap_to_screen(s, name, xy, shot, **kw)
    common.port_login(s, notice=None, bonus=None)
    common.settle(s, mask=common.HOME_MASK)
    common.tap_to_count(s, "ガチャ -> GetGachaInData", s.packets, r"< GetGachaInDataRes", ["tap:" + ui370.FOOTER_GACHA],
                        mask=common.GACHA_MASK)
    screen("武器 tab", WEAPON_TAB, "03-weapon-gachas", mask=common.GACHA_MASK)
    screen("the first banner", FIRST_BANNER)
    screen("1回ガチャ -> the confirmation", DRAW_1, "04-confirm")
    common.tap_to_server(s, "1回ガチャ: one weapon drawn", r"I/server: \S*Gacha \d+ \(.*1 draws for", ["tap:" + DECIDE], changes=False)
    gacha.summon(s, shot="05-result")
    screen("the result: 閉じる", ui370.GACHA_RESULT_NEXT, mask=common.GACHA_MASK)
    # the item list, without a re-login: the new weapon is there
    common.tap_to_phase(s, "アイテム", ITEM_MENU, 9, fatal=True)
    screen("所持アイテム一覧", ITEM_LIST, "06-item-list")
    screen("戻る", BACK)
    # アイテム売却: the weapon -> 決定 -> 決定 (-> the ★3 warning's 決定)
    screen("アイテム売却", SELL_MENU, "07-sell")
    common.tap_settled(s, ROW1)
    screen("売却: 決定", OK, "08-sell-confirm")
    sold = r"SellItem(Array)?: \+[0-9]+ FOL \(1 items\)"
    n = milestones.count(s.server_log, sold)
    s.ctl("tap:515:1000")
    if not s.poll(8, lambda: milestones.count(s.server_log, sold) > n):
        # a ★3 or better: its warning first
        common.settle(s, "09-sell-warning")
        common.tap_to_server(s, "the drawn weapon sold", sold, ["tap:" + DECIDE], "10-sold", secs=30)
    else:
        s.ok("the drawn weapon sold")
        common.settle(s, "10-sold")


def main(o):
    s = common.port_run(o, common.port_config(o, limit=1500))
    if not common.drive(s, body):
        return 1
    st = sqlite3.connect("file:%s?mode=ro" % s.state_db, uri=True)
    row = st.execute("select item_uid, gacha_id from gacha_history where role_id is null order by rowid desc limit 1").fetchone()
    loose = st.execute("select count(*) from items where stored_at is null and uid not in "
                       "(select weapon_uid from roster where weapon_uid is not null union select accessory_uid from roster "
                       "where accessory_uid is not null)").fetchone()[0]
    # the packet log between the draw's answer and the sale: no full player load
    text = open(s.packets, errors="replace").read()
    a, b = text.find("< GachaRes"), text.find("> SellItem")
    between = text[a:b] if 0 <= a < b else ""
    reload_ = re.findall(r"> (Login|SimpleLogin|GetPlayer|NoLoginStart) ", between)
    print("drawn weapon: %s; loose items left: %d; full loads between the draw and the sale: %s" % (row, loose, reload_ or "none"))
    fails = common.checks((row is not None, "no weapon draw recorded"),
                          (row is not None and row[0] is None, "the drawn weapon wasn't sold (gacha_history keeps its uid)"),
                          (0 <= a < b, "no GachaRes before a SellItem in the packet log"),
                          (not reload_, "a full player load came between the draw and the sale: %s" % reload_)) + common.common_log_checks(s)
    return common.verdict(s, fails, "a drawn weapon is in the item list at once (AddItem as a map) and the client sells it, no re-login")
