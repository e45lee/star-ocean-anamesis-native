"""Session `sphere211`: the restored Sphere 211 (the in-process local server;
server/src/api/sphere211/sphere211.cpp): boot -> notice board -> LOGIN BONUS -> the Sphere 211
rental bonus popup (5 rentals injected into the state DB) -> home -> スフィア211 (GetSphere211Info:
the season's floor 1) -> a dive along the shortest path of the lotted map. Each cell = detail ->
シングルプレイ開始 -> (a rental in the 4th slot on the first cell) -> 自動編成
(Sphere211AutoMemberSelect) -> ミッション開始 -> 決定 (Sphere211MissionStart) -> the battle (auto) ->
Sphere211MissionEnd -> the result pages -> the board; the stamina heal ticket after the first cell
(Sphere211StaminaHeal 8 -> 9). Four cells, then 帰還 (ReturnSphere211: the boxes analysed, the
characters back, the dive stays on floor 1), the boss with the strongest party again, the goal ->
次のフロアへ -> Sphere211FloorClear -> the reroll item (Sphere211UseRerollItem) -> floor select 2F
-> Sphere211SelectedFloor -> 帰還 again on floor 2. About 20 minutes. The cell taps are screen
positions of the map the server lots with --seed-rng 605 (start -> 2 -> 3 -> 6 -> boss 7 -> goal);
the session checks the map id and stops if another map came up. Before each tap the board is
re-entered from home, so the camera is on its start view. The enemies are set to level 30 with
the server's test hook (sphere.debug_enemy_level): the session checks the flow, not the balance.
Screenshots go to OUT/shots, the server's Sphere 211 tables to OUT/state-*.txt, the log to
OUT/log.txt. Exit status 1 if a step didn't answer as expected.

Usage: port/scripts/sphere211_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SEED_RNG (default 605), SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc (the phase lines, the in-process server's state)."""
import re

from ..flows import mission
from . import _sphere, common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it writes the in-process server's state DB and waits on the port's phase lines"
WRAPPER = "port/scripts/sphere211_session.sh"
TOP = ["drag:364:300:364:900:1200", "wait:1500", "drag:364:300:364:900:1200", "wait:1500", "drag:364:300:364:900:1200", "wait:3000"]


def options(ap):
    common.port_options(ap, extra=False)


def main(o):
    s = common.port_run(o, _sphere.port_config(o))
    c = s.ctl
    st = {}

    def enter_once():
        c("tap:100:1120")
        s.wait_log(mission.phase(4), 30, name="戻る -> home")
        c("wait:5000")
        s.tap_log(r"request GetSphere211Info", 60, 20, 3, "tap:455:1085", name="スフィア211 -> the board again")

    def reenter():
        # the first entry after a clear plays the unlock animation (no input meanwhile): entered twice
        enter_once()
        c("wait:15000")
        enter_once()
        c("wait:8000")

    def return_dive(tag):
        c("tap:590:1120", "wait:3000", s.shot_cmd(tag + "-return-dialog"), "tap:515:972")
        s.wait_log(r"ReturnSphere211: ", 30, name=tag + ": ReturnSphere211")
        c("wait:6000", s.shot_cmd(tag + "-treasure-data"), "tap:364:1095", "wait:5000", s.shot_cmd(tag + "-treasure-items"), "tap:364:1095",
          "wait:4000", s.shot_cmd(tag + "-returned"))
        c("tap:364:800", "wait:3000", s.shot_cmd(tag + "-board-after"))

    def body(s):
        st[1] = _sphere.login_to_board(s)
        _sphere.sql(s, "update sphere set debug_enemy_level = 30 where id = 1")
        c("tap:364:670")
        _sphere.battle(s, "10-cell1", rent=True)
        if not s.in_client(r"MissionStart: rental helper .* as member 4"):
            s.fail("the rental didn't join as member 4")
        # The stamina the battle took (9 -> 8) healed with the season's ticket.
        c("tap:590:992", "wait:3000", s.shot_cmd("15-heal-items"), "tap:364:515", "wait:3000", s.shot_cmd("15-heal"), "tap:515:790")
        s.wait_log(r"Sphere211StaminaHeal: sphere stamina 8 -> 9", 30, name="Sphere211StaminaHeal")
        c("wait:3000", s.shot_cmd("15-healed"), "tap:364:790", "wait:2000")
        reenter()
        c("tap:364:480")
        _sphere.battle(s, "20-cell2")
        reenter()
        c("tap:364:285")
        _sphere.battle(s, "30-cell3")
        reenter()
        c(*(TOP + [s.shot_cmd("35-board"), "tap:490:965"]))
        _sphere.battle(s, "40-cell6")
        if not s.in_client(r"Sphere211MissionEnd: .*streak 4"):
            s.fail("four battles weren't cleared in a row")
        reenter()
        return_dive("45")
        st[2] = _sphere.state(s, "2-returned")
        reenter()
        c(*(TOP + [s.shot_cmd("49-board"), "tap:490:790"]))
        _sphere.battle(s, "50-boss")
        st[3] = _sphere.state(s, "3-cleared")
        # The goal (目標地点) -> 次のフロアへ -> 決定: Sphere211FloorClear.
        reenter()
        c(*(TOP + [s.shot_cmd("60-goal"), "tap:364:625", "wait:3000", s.shot_cmd("62-next-floor"), "tap:515:713"]))
        s.wait_log(r"Sphere211FloorClear\(", 30, name="Sphere211FloorClear")
        c("wait:5000", s.shot_cmd("63-floor-result"), "tap:364:970", "wait:12000", s.shot_cmd("64-floor-select"))
        # 再設定 with the season's reroll ticket (Sphere211UseRerollItem re-lots the next-floor count)
        c("tap:220:962", "wait:3000", s.shot_cmd("64b-reroll-confirm"), "tap:515:795")
        s.wait_log(r"Sphere211UseRerollItem: next-floor lot", 30, name="Sphere211UseRerollItem")
        c("wait:5000", s.shot_cmd("64c-rerolled"))
        c("tap:364:570", "wait:1500", "tap:510:962", "wait:3000", s.shot_cmd("65-confirm"), "tap:515:713")
        s.wait_log(r"Sphere211SelectedFloor\(1\): floor 1 -> 2", 30, name="Sphere211SelectedFloor: floor 2")
        c("wait:8000", s.shot_cmd("66-floor2"))
        _sphere.state(s, "4-floor2")
        # 帰還 on floor 2: the floor-1 boss and floor-clear boxes analysed, everyone back.
        return_dive("70")
        _sphere.sql(s, "update sphere set debug_enemy_level = null where id = 1")
        st[5] = _sphere.state(s, "5-returned")

    if not common.drive(s, body):
        return 1
    has = lambda text, rx: re.search(rx, text, re.M) is not None
    fails = common.checks(
        (has(st[1], r"^sphere .* floor 1 "), "the dive didn't start on floor 1"),
        (has(st[2], r"^sphere .* floor 1 streak 0 "), "mid-dive 帰還 didn't keep floor 1 / reset the streak"),
        (has(st[2], r"^departed 0"), "characters still out after the first 帰還"),
        (has(st[3], r"^sphere .* floor 1 streak 1 "), "the boss battle didn't count"),
        (has(st[5], r"^sphere .* floor 2 streak 0 "), "not on floor 2 with the streak reset after 帰還"),
        (has(st[5], r"^boxes 0"), "boxes left unopened"),
        (has(st[5], r"^departed 0"), "characters still out after 帰還"),
        (has(st[5], r"^rank season [0-9]* best floor 2"), "the ranking's best floor isn't 2"),
    )
    log = open(s.client_log, errors="replace").read()
    for ln in log.splitlines():
        if re.search(r"I/server: (GetSphere211Info|Sphere211|ReturnSphere211)", ln) and "Sphere211: season" not in ln:
            print(ln)
    if re.search(r"refused with error|Sphere211.* refused", log):
        print("\n".join(ln for ln in log.splitlines() if "refused" in ln))
        fails.append("a request was refused")
    if "MissionStart: rental helper" not in log:
        fails.append("no rental")
    return common.verdict(s, fails, "Sphere 211 entered from home (rental bonus popup), 4 battles (a rental on the first, stamina "
                          "healed after it), 帰還, the boss, floor 1 cleared, the floor count rerolled, floor 2 entered, 帰還 analysed the boxes")
