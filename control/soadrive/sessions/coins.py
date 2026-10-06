"""Session `coins`: paid currency (docs/unimplemented-apis.md part 3 step 7; docs/server-rules.md
#paid-currency): title -> Login -> home -> ショップ -> アイテムショップ; the server's coins are cut to 10 free /
0 paid while the client still shows the seed's (the 3.7.0 client opens the coin shop only when the server
refuses a payment the client thought it could make: 20003) -> a 2,500-stone set -> 交換する: the
server refuses it with 20003 and the client offers 紋章石を購入する (shot) -> the coin shop (shot) -> the
L set: CoinDepositCreate, the local store's purchase, CoinDepositAndroidUpdate (the server's line
`deposit N completed`) -> the state: 980 paid + 80 free stones, a completed coin_deposit row (shots)
-> home with the header's 紋章石 1,070 (shot); then a second boot on the same phone and state: Login,
home (shot), and the state still holds the purchase. Shots go to OUT/shots, the logs to OUT/log.txt
and OUT/log-relogin.txt. Ends with PASS (exit 0) or FAIL (exit 1).

Usage: port/scripts/coins_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SEED_RNG, WATCH=1.
Targets: port-inproc (default), port-server (the server-log milestones; the state DB read directly)."""
import sqlite3

from ..flows import mission
from . import common

TARGETS = ("port-inproc", "port-server")
TARGETS_WHY = "it writes the server's state DB while the client runs (the coins cut) and reads the server's log"
WRAPPER = "port/scripts/coins_session.sh"

PAID, FREE = 980, 80  # the L set (coin_description__20191001_003: ※980個＋おまけ80個)


def options(ap):
    common.port_options(ap, extra=False)


def wallet(s):
    """(free, paid, completed deposits) from the server's state, read-only."""
    db = sqlite3.connect("file:%s?mode=ro" % s.state_db, uri=True)
    try:
        free, paid = db.execute("select free_coin, pay_coin from player").fetchone()
        done = db.execute("select count(*) from coin_deposit where completed_at is not null and paid = ? and free = ?",
                          (PAID, FREE)).fetchone()[0]
        return free, paid, done
    finally:
        db.close()


def cut_coins(s):
    """The server's coins down to 10 free, 0 paid; the client keeps showing what it had."""
    db = sqlite3.connect(s.state_db)
    try:
        db.execute("pragma foreign_keys = on")
        db.execute("update player set free_coin = 10, pay_coin = 0")
        db.commit()
    finally:
        db.close()


def log_checks(s):
    """common_log_checks without the one refusal the session provokes (ExItemShop, 20003)."""
    out = []
    refused = [ln for ln in open(s.client_log, errors="replace").read().splitlines()
               if "refused with error" in ln and not ("33d09fb7" in ln and "20003" in ln)]
    if refused:
        print("\n".join(refused))
        out.append("a request was refused")
    if common.log_has(s, r"Unhandled SIG|\*\*\* host signal"):
        out.append("soa crashed")
    return out


def main(o):
    s = common.port_run(o, common.port_config(o, limit=2400))
    got = {}

    def body(s):
        common.port_login(s, notice=None, bonus=None)
        # ショップ -> アイテムショップ (over the wire ItemShopList answers the wallet too, so the coins
        # are cut after it) -> [毎月1回]覚醒補助セット【赤】 (2,500 stones) -> 交換する -> 交換する
        s.ctl("tap:545:1250", "wait:4000", "tap:364:345", "wait:6000", s.shot_cmd("10-item-shop"))
        cut_coins(s)
        s.ctl("tap:300:880", "wait:3000", "tap:515:1000", "wait:3000")
        s.ctl("tap:515:800")
        s.wait_for("交換する -> ExItemShop refused with 20003", 60, lambda: s.in_server(r"ExItemShop refused: not enough coins \(error 20003\)"))
        s.ctl("wait:3000", s.shot_cmd("11-coins-short"))
        # 紋章石を購入する -> the coin shop (GetBirthYearMonth first: the age check)
        s.ctl("tap:364:678", "wait:6000", s.shot_cmd("12-coin-shop"))
        # the L set (the fifth row from the top: the list runs テラ .. S)
        s.ctl("tap:364:870")
        s.wait_for("the L set -> CoinDepositCreate, the store, CoinDepositAndroidUpdate", 90,
                   lambda: s.in_server(r"CoinDepositAndroidUpdate: deposit [0-9]+ completed"))
        # the store's purchase consumed (FinishPurchaseProduct), then the result dialog
        s.wait_for("the purchase consumed (ConsumeProduct)", 60, lambda: s.in_client(r"I/java: ConsumeProduct\("))
        s.ctl("wait:5000", s.shot_cmd("13-purchased"))
        got["after"] = wallet(s)
        s.check("980 paid + 80 free stones credited, the purchase recorded (%s)" % (got["after"],),
                got["after"] == (10 + FREE, PAID, 1))
        # the result's 閉じる, the coin shop's 閉じる, then home (the footer)
        s.ctl("tap:364:800", "wait:2500", s.shot_cmd("14-result-closed"), "tap:364:1000", "wait:2500", s.shot_cmd("15-shop-closed"),
              "tap:213:1000", "wait:2500")  # the exchange confirmation underneath: 閉じる
        s.tap_log(mission.phase(4), 60, 15, 4, "tap:60:1250", name="ホーム -> home")
        s.ctl("wait:5000", s.shot_cmd("16-home-stones"))
        got["home"] = wallet(s)
        s.check("nothing else bought on the way (%s)" % (got["home"],), got["home"] == got["after"])

    if not common.drive(s, body):
        return 1
    s2 = common.port_run_again(o, common.port_config(o, limit=1800), "log-relogin.txt")

    def body2(s2):
        common.port_login(s2, title="30-title", notice=None, bonus=None, home="31-home")
        s2.ctl("wait:3000", s2.shot_cmd("32-home-stones-relogin"))
        got["relogin"] = wallet(s2)
        s2.check("the purchase still there after a re-login (%s)" % (got["relogin"],), got["relogin"] == (10 + FREE, PAID, 1))

    if not common.drive(s2, body2):
        return 1
    fails = log_checks(s) + log_checks(s2)
    return common.verdict(s, fails if not s2.failed else fails + ["the re-login boot failed"],
                          "paid currency: the coin shop opened on 20003, the L set bought (%s free / paid / records), "
                          "still there after a re-login" % (got.get("relogin"),))
