"""Session `coins`: paid currency (docs/unimplemented-apis.md part 3 step 7; docs/server-rules.md
#paid-currency): title -> Login -> home; the player's stones planted at 50 free / 0 paid -> ガチャ (the
wallet refreshed) -> a banner -> 1回ガチャ (500): the client's own check finds the stones short and its
sale-stopped dialog, patched (platform370, the user's decision of 2026-10-05), opens the coin shop;
its age check (GetBirthYearMonth refused with 10009) shows the birth dialog (shot) -> 登録する, 登録する
(UpdateBirthYearMonth 2000-01) -> the coin shop (shot) -> the L set: CoinDepositCreate, the local store's purchase, CoinDepositAndroidUpdate (the
server's line `deposit N completed`) -> the state: 980 paid + 80 free stones, a completed coin_deposit
row (shots) -> home with the header's stones (shot); then a second boot on the same phone and state:
Login, home (shot), the state still holds the purchase, and a second coins-short draw opens the coin
shop with GetBirthYearMonth answered (no birth dialog; the month kept). Shots go to OUT/shots, the logs to
OUT/log.txt and OUT/log-relogin.txt. Ends with PASS (exit 0) or FAIL (exit 1).

Usage: port/scripts/coins_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SEED_RNG, WATCH=1.
Targets: port-inproc (default), port-server (the server-log milestones; the state DB read directly)."""
import sqlite3

from ..flows import mission
from . import common

TARGETS = ("port-inproc", "port-server")
TARGETS_WHY = "it writes the server's state DB while the client runs (the stones planted) and reads the server's log"
WRAPPER = "port/scripts/coins_session.sh"

PAID, FREE = 980, 80  # the L set (coin_description__20191001_003: ※980個＋おまけ80個)
START = 50  # the planted free stones: under a single draw's 500


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


def n_server(s, rx):
    """How many lines of the server log match rx (the --server log runs across both boots)."""
    import re
    try:
        return sum(1 for ln in open(s.server_log, errors="replace") if re.search(rx, ln))
    except OSError:
        return 0


def birth(s):
    """The stored birth month (player.birth_year, birth_month), read-only."""
    db = sqlite3.connect("file:%s?mode=ro" % s.state_db, uri=True)
    try:
        return tuple(db.execute("select birth_year, birth_month from player").fetchone())
    finally:
        db.close()


def plant_coins(s):
    """The server's coins down to START free, 0 paid (the client learns it from the next wallet)."""
    db = sqlite3.connect(s.state_db)
    try:
        db.execute("pragma foreign_keys = on")
        db.execute("update player set free_coin = ?, pay_coin = 0", (START,))
        db.commit()
    finally:
        db.close()


def log_checks(s):
    """common_log_checks without the refusals the session provokes: the first GetBirthYearMonth
    (10009, the age check asking for the birth month) and ExItemShop's 20003."""
    out = []
    refused = [ln for ln in open(s.client_log, errors="replace").read().splitlines()
               if "refused with error" in ln and not ("33d09fb7" in ln and "20003" in ln)
               and not ("59a48d41" in ln and "10009" in ln)]
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
        # a player with few stones: 50 free, 0 paid; the gacha screen's GetGachaInData answers the
        # wallet, so the client shows 50 there
        plant_coins(s)
        s.tap_until("ガチャ -> GetGachaInData", 60, "425:1250", lambda: s.in_server(r"request GetGachaInData"), every=20)
        s.ctl("wait:8000", "tap:360:320", "wait:5000", s.shot_cmd("10-gacha-banner"))
        # 1回ガチャ (500 stones): the client's own check finds the coins short; OpenBuyEndDialog, patched
        # (platform370, the user's decision), opens the coin shop instead of the sale-stopped dialog
        s.ctl("tap:190:950")
        s.wait_for("1回ガチャ, coins short -> the coin shop (OpenBuyEndDialog patched)", 60,
                   lambda: s.in_client(r"patch: OpenBuyEndDialog .* -> OpenCoinShopDialog"))
        # the coin shop asks for the birth month first (GetBirthYearMonth refused with 10009: the
        # client's birth dialog, b: CCoinShop::ToShop's result lambda @0197c2f8) -> 登録する with its
        # default (2000-01) -> the confirmation's 登録する -> UpdateBirthYearMonth -> the coin shop
        s.wait_for("the coin shop's age check: GetBirthYearMonth refused with 10009", 60,
                   lambda: s.in_server(r"GetBirthYearMonth refused: no birth month entered \(error 10009\)"))
        s.ctl("wait:4000", s.shot_cmd("11-birth-dialog"))
        s.ctl("tap:364:648", "wait:3000", s.shot_cmd("11-birth-confirm"))  # 登録する -> 2000年1月生まれ, よろしいですか？
        s.tap_until("登録する (confirmed) -> UpdateBirthYearMonth", 60, "515:790", lambda: s.in_server(r"UpdateBirthYearMonth: 2000-01"), every=15)
        s.ctl("wait:6000", s.shot_cmd("12-coin-shop"))
        # the L set (the fifth row from the top: the list runs テラ .. S)
        s.ctl("tap:364:870")
        s.wait_for("the L set -> CoinDepositCreate, the store, CoinDepositAndroidUpdate", 90,
                   lambda: s.in_server(r"CoinDepositAndroidUpdate: deposit [0-9]+ completed"))
        # the store's purchase consumed (FinishPurchaseProduct), then the result dialog
        s.wait_for("the purchase consumed (ConsumeProduct)", 60, lambda: s.in_client(r"I/java: ConsumeProduct\("))
        s.ctl("wait:5000", s.shot_cmd("13-purchased"))
        got["after"] = wallet(s)
        s.check("980 paid + 80 free stones credited, the purchase recorded (%s)" % (got["after"],),
                got["after"] == (START + FREE, PAID, 1))
        # the result's 閉じる, the coin shop's 閉じる, then home (the footer)
        s.ctl("tap:364:800", "wait:2500", s.shot_cmd("14-result-closed"), "tap:364:1000", "wait:2500", s.shot_cmd("15-shop-closed"))
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
        s2.check("the purchase still there after a re-login (%s)" % (got["relogin"],), got["relogin"] == (START + FREE, PAID, 1))
        # the birth month kept: a coins-short draw goes straight to the coin shop (GetBirthYearMonth
        # answered, no birth dialog)
        plant_coins(s2)
        asked, refused = n_server(s2, r"request GetBirthYearMonth"), n_server(s2, r"GetBirthYearMonth refused")
        gacha = n_server(s2, r"request GetGachaInData")
        s2.tap_until("ガチャ -> GetGachaInData", 60, "425:1250", lambda: n_server(s2, r"request GetGachaInData") > gacha, every=20)
        s2.ctl("wait:8000", "tap:360:320", "wait:5000", "tap:190:950")
        s2.wait_for("1回ガチャ, coins short -> the coin shop", 60, lambda: s2.in_client(r"patch: OpenBuyEndDialog .* -> OpenCoinShopDialog"))
        s2.ctl("wait:6000", s2.shot_cmd("33-coin-shop-relogin"))
        s2.check("the birth month kept: GetBirthYearMonth answered, not refused, after the re-login",
                 n_server(s2, r"request GetBirthYearMonth") > asked and n_server(s2, r"GetBirthYearMonth refused") == refused
                 and birth(s2) == (2000, 1))

    if not common.drive(s2, body2):
        return 1
    fails = log_checks(s) + log_checks(s2)
    return common.verdict(s, fails if not s2.failed else fails + ["the re-login boot failed"],
                          "paid currency: the coin shop opened from a coins-short gacha draw, the L set bought (%s free / paid / records), "
                          "still there after a re-login" % (got.get("relogin"),))
