"""Session `sphere211-continue`: a lost Sphere 211 battle, continued and retired (the in-process local
server; server/src/api/sphere211/sphere211.cpp). Boot -> title (the test setup in the state DB, as
the sphere211 session) -> notice board -> LOGIN BONUS -> the Sphere 211 rental bonus popup -> home ->
スフィア211 -> the start cell with enemy level 250 (the server's test hook, for this battle only) and
a rental in the 4th slot -> the party falls -> the defeat dialog's はい (Sphere211MissionContinue,
100 coins) -> the pause menu's ミッションリタイア -> はい (Sphere211MissionFailed) -> the board -> the
stamina the battle took healed with a ticket (Sphere211StaminaHeal 8 -> 9) -> the board's 実績 tabs ->
with no coins, the start cell lost again: the client declines by itself (Sphere211MissionContinue(..., 0):
the run ends as failed) -> the board. About 7 minutes.

Usage: port/scripts/sphere211_continue_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SEED_RNG (default 605), SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc (the phase lines, the in-process server's state)."""
import re

from ..flows import mission
from . import _sphere, common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it writes the in-process server's state DB and waits on the port's phase lines"
WRAPPER = "port/scripts/sphere211_continue_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def main(o):
    s = common.port_run(o, _sphere.port_config(o))
    c = s.ctl

    def body(s):
        _sphere.login_to_board(s)
        _sphere.sql(s, "update sphere set debug_enemy_level = 250 where id = 1")
        c("tap:364:670")
        c("wait:4000", s.shot_cmd("06-lose-detail"), "tap:364:905", "wait:5000", s.shot_cmd("06-rental-list"), "tap:364:383", "wait:4000",
          s.shot_cmd("06-rental-party"))
        c("tap:364:898")
        s.wait_log(r"Sphere211AutoMemberSelect: 4 members proposed", 30, name="lost battle: auto member select")
        c("wait:4000", s.shot_cmd("06-party"))
        started = r"Sphere211MissionStart: floor .* enemy level 250"
        mission.start_mission(s, "lost battle: ミッション開始 -> 決定 (the start)", mission.log_more(s.client_log, started), d=mission.SPHERE211)
        s.wait_log(started, 60, name="lost battle: Sphere211MissionStart")
        if not s.in_client(r"MissionStart: rental helper .* as member 4"):
            s.fail("the rental didn't join as member 4")
        _sphere.sql(s, "update sphere set debug_enemy_level = null where id = 1")
        if s.tap_log(r"Sphere211MissionContinue: ", 400, 10, 40, "tap:489:786", name="continue after the defeat", fatal=None) is None:
            c(s.shot_cmd("07-stuck"))
            s.fail("no continue after the defeat")
        c(s.shot_cmd("07-continued"))
        if s.tap_log(r"Sphere211MissionFailed: ", 90, 15, 5, "tap:80:50", "wait:2500", "tap:364:607", "wait:2500", "tap:525:790",
                     name="retire", fatal=None) is None:
            c(s.shot_cmd("08-stuck"))
            s.fail("no retire")
        s.wait_log(mission.phase(5), 120, name="back on the board after the retire")
        c("wait:6000", s.shot_cmd("08-board"), "tap:590:992", "wait:3000", s.shot_cmd("09-heal-items"), "tap:364:515", "wait:3000",
          s.shot_cmd("09-heal"), "tap:515:790")
        s.wait_log(r"Sphere211StaminaHeal: sphere stamina 8 -> 9", 30, name="Sphere211StaminaHeal")
        c("wait:3000", s.shot_cmd("09-healed"), "tap:364:790", "wait:2000")
        # The board's 実績 button: the achievement dialog, its four tabs, then 閉じる.
        c("tap:655:340", "wait:5000", s.shot_cmd("10-achievements-event"), "tap:290:303", "wait:2500", s.shot_cmd("10-achievements-daily"),
          "tap:440:303", "wait:2500", s.shot_cmd("10-achievements-weekly"), "tap:590:303", "wait:2500", s.shot_cmd("10-achievements-other"),
          "tap:213:1053", "wait:2000")
        # A second lost battle with no coins: CPauseMenu::OpenContinue declines by itself
        # (Sphere211MissionContinue(..., 0)); the server ends the run as failed. Whether the client
        # also sends Sphere211MissionFailed afterwards is noted (got["failed_after_decline"]).
        _sphere.sql(s, "update sphere set debug_enemy_level = 250 where id = 1", "update player set free_coin = 0, pay_coin = 0")
        c("wait:3000", "tap:364:670", "wait:4000", s.shot_cmd("11-decline-detail"), "tap:364:905", "wait:5000", "tap:628:1120", "wait:4000",
          "tap:364:898")
        s.wait_log(r"Sphere211AutoMemberSelect: 4 members proposed", 30, name="declined battle: auto member select")
        c("wait:4000", s.shot_cmd("11-decline-party"))
        s.tap_log(r"Sphere211MissionStart: floor .* enemy level 250", 60, 15, 3, "tap:140:898", "wait:3000", "tap:515:713",
                  name="declined battle: Sphere211MissionStart")
        _sphere.sql(s, "update sphere set debug_enemy_level = null where id = 1")
        s.wait_log(r"Sphere211MissionContinue: declined", 400, name="the automatic decline (no coins): the battle ends as failed")
        c("wait:15000", s.shot_cmd("12-declined"))
        i = 0
        while s.cursor.wait(mission.phase(5), 4, alive=s.alive) is None:
            c("tap:364:1050")
            i += 1
            if i >= 15:
                c(s.shot_cmd("12-stuck"))
                s.fail("not back on the board after the declined battle")
        c("wait:4000", s.shot_cmd("12-board"))

    if not common.drive(s, body):
        return 1
    log = open(s.client_log, errors="replace").read()
    tail = log.split("Sphere211MissionContinue: declined", 1)[1] if "Sphere211MissionContinue: declined" in log else ""
    print("after the decline the client %s Sphere211MissionFailed" % ("sent" if "Sphere211MissionFailed: streak reset" in tail else "didn't send"))
    fails = common.checks(
        ("Sphere211MissionContinue: 100 coins" in log, "no paid continue"),
        ("Sphere211MissionContinue: declined" in log, "no declined continue"),
        ("Sphere211MissionFailed: streak reset" in log, "no retire"),
        ("Sphere211StaminaHeal: sphere stamina 8 -> 9" in log, "no heal"))
    if re.search(r"refused with error|Sphere211.* refused", log):
        print("\n".join(ln for ln in log.splitlines() if "refused" in ln))
        fails.append("a request was refused")
    return common.verdict(s, fails, "rental bonus popup, a lost Sphere 211 battle with a rental continued (100 coins) and retired from the "
                          "pause menu, the stamina healed")
