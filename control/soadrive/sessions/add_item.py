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
from . import common

TARGETS = ("port-inproc", "port-server")
WRAPPER = "port/scripts/add_item_session.sh"

WEAPON_TAB, FIRST_BANNER, DRAW_1, DECIDE = "450:175", "360:315", "190:948", "515:800"
ITEM_MENU, ITEM_LIST, SELL_MENU, ROW1, BACK, OK = "300:1250", "364:345", "364:900", "364:400", "100:1120", "630:1120"


def options(ap):
    common.port_options(ap, extra=False)


def server_step(s, rx, name, secs=40):
    """Waits for the next server-log line matching rx (counted from the step's start)."""
    before = milestones.count(s.server_log, rx)
    return lambda: s.wait_for(name, secs, lambda: milestones.count(s.server_log, rx) > before)


def body(s):
    c = s.ctl
    common.port_login(s, notice=None, bonus=None)
    s.tap_until("ガチャ -> GetGachaInData", 60, ui370.FOOTER_GACHA, lambda: s.in_packets(r"< GetGachaInDataRes"))
    c("wait:10000", "tap:" + WEAPON_TAB, "wait:3000", s.shot_cmd("03-weapon-gachas"), "tap:" + FIRST_BANNER, "wait:4000",
      "tap:" + DRAW_1, "wait:3000", s.shot_cmd("04-confirm"))
    done = server_step(s, r"I/server: \S*Gacha \d+ \(.*1 draws for", "1回ガチャ: one weapon drawn")
    c("tap:" + DECIDE)
    done()
    c("wait:8000", "tap:" + ui370.SUMMON_START, "wait:12000", "tap:" + ui370.SUMMON_REVEAL, "wait:4000", "tap:" + ui370.SUMMON_REVEAL,
      "wait:4000", "tap:" + ui370.SUMMON_ALL_SKIP, "wait:5000", s.shot_cmd("05-result"), "tap:" + ui370.GACHA_RESULT_NEXT, "wait:3000")
    # the item list, without a re-login: the new weapon is there
    c("tap:" + ITEM_MENU, "wait:5000", "tap:" + ITEM_LIST, "wait:5000", s.shot_cmd("06-item-list"), "tap:" + BACK, "wait:4000")
    # アイテム売却: the weapon -> 決定 -> 決定 (-> the ★3 warning's 決定)
    c("tap:" + SELL_MENU, "wait:5000", s.shot_cmd("07-sell"), "tap:" + ROW1, "wait:1000", "tap:" + OK, "wait:3000", s.shot_cmd("08-sell-confirm"))
    done = server_step(s, r"SellItem(Array)?: \+[0-9]+ FOL \(1 items\)", "the drawn weapon sold", 30)
    c("tap:515:1000", "wait:3000")
    if not milestones.count(s.server_log, r"SellItem(Array)?: \+[0-9]+ FOL \(1 items\)"):
        c(s.shot_cmd("09-sell-warning"), "tap:" + DECIDE, "wait:3000")
    done()
    c("wait:2000", s.shot_cmd("10-sold"))


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
