"""Session `missions`: the mission side of the local server (the in-process local server), end to end:
 1. a battle of mf01_003, whose surprise enemy appears (--surprise, a port test option; the server
    otherwise rolls master_mission.surprise_rate 10.25 %): the result shows the surprise drops, the
    first clear unlocks mf01_004 (log + state dump);
 2. a step-up gacha advancing a step: gacha_pickup_role_1011 (step 1 of 10, open at --clock
    2021-05-25, the first banner of the gacha screen's おすすめガチャ) drawn through the gacha
    screen (10連ガチャ -> 決定), then step 2 on the same banner; the server logs each step;
 3. the error dialog: the player's stamina is set to 0 in the server's state, and the start of
    mf01_001 is refused with 10004; the client's own error handling shows error_message_text_10004
    (スタミナが不足しています); its 閉じる button (364:712) then goes back to the title.
Screenshots go to OUT/shots, the state dumps to OUT/state-*.txt, the log to OUT/log.txt. Ends with
PASS (exit 0) or FAIL (exit 1).

Usage: port/scripts/restore_missions.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1.
Targets: port-inproc (the `mission:` / `phase:` shortcut, --surprise)."""
import re
import sqlite3
import sys

from ..flows import mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it enters battles through the port's `mission:` / `phase:0xf` control commands"
WRAPPER = "port/scripts/restore_missions.sh"


def options(ap):
    common.port_options(ap, extra=False)


def main(o):
    s = common.port_run(o, common.port_config(o, ["--surprise", "--clock", "2021-05-25 12:00:00"], limit=2400))
    st = {}
    show = lambda text: sys.stdout.write(text) and sys.stdout.flush()

    def draw(s, step):
        """10連ガチャ -> 決定, the presentation, the result (次へ, 閉じる): back on the banner."""
        s.tap_log(r"step-up chain .* step %d -> %d" % (step, step + 1), 40, 15, 3, "tap:540:945", "wait:3000", "tap:515:800",
                  name="step %d of the step-up gacha" % step)
        s.ctl("wait:6000", s.shot_cmd("c%d-summon" % step), "tap:364:1190", "wait:12000", "tap:364:650", "wait:4000", "tap:364:650",
              "wait:4000", "tap:577:1199", "wait:5000")
        s.ctl(s.shot_cmd("c%d-result" % step), "tap:364:1002", "wait:4000", "tap:364:1002", "wait:4000",
              s.shot_cmd("c%d-banner-after" % step))

    def body(s):
        common.port_login(s, notice=None, bonus=None, home=None)
        s.ctl("wait:3000", s.shot_cmd("02-home"))
        show(s.state("1-boot"))
        # 1. mf01_003 with its surprise enemy.
        mission.port_start(s, "mf01_003")
        s.wait_log(r"MissionStart mission .*surprise enemy", 60, name="MissionStart with the surprise enemy")
        s.ctl("wait:1500", s.shot_cmd("03-battle-loading"))
        mission.battle_shots(s, 10, 90, 4000)
        s.wait_log(r"mission_end\.msgp", 30, name="the battle ended (MissionEnd)")
        s.ctl("wait:4000", s.shot_cmd("a0-result"), "wait:4000", s.shot_cmd("a1-result"))
        mission.results_until(s, mission.phase(4), 2, 14, 4000, fmt="a%02d-result", name="the result pages -> home")
        s.ctl("wait:6000", s.shot_cmd("b0-home"))
        st[2] = s.state("2-after-surprise-battle")
        show(st[2])
        for ln in open(s.client_log, errors="replace").read().splitlines():
            if re.search(r"MissionEnd mission .* (drops|unlocked)", ln):
                print(ln)
        # 2. Step-up gacha: step 1, then step 2 of gacha_pickup_role_1011's chain, through the gacha
        # screen (the footer's ガチャ; at 2021-05-25 its first recommended banner, ステップ 1/10).
        s.tap_log(r"request GetGachaInData", 60, 20, 3, "tap:425:1250", name="ガチャ -> GetGachaInData")
        s.ctl("wait:8000", "tap:100:175", "wait:3000", "tap:360:320", "wait:5000", s.shot_cmd("c0-stepup-banner"))
        draw(s, 1)
        draw(s, 2)
        s.tap_log(mission.phase(4), 60, 15, 4, "tap:60:1250", name="ホーム -> home")
        s.ctl("wait:6000", s.shot_cmd("c9-home-after-stepup"))
        st[3] = s.state("3-after-stepup")
        show(st[3])
        # 3. Stamina 0: the start of mf01_001 is refused (10004) and the client shows its error dialog.
        c = sqlite3.connect(s.state_db)
        c.execute("pragma foreign_keys = on")
        c.execute("update player set stamina = 0, stamina_at = strftime('%s','now')")
        c.commit()
        c.close()
        s.ctl("mission:mf01_001", "phase:0xf")
        s.wait_log(r"refused by the local server with error 10004", 90, name="MissionStart refused with 10004")
        s.ctl("wait:3000", s.shot_cmd("d0-error-dialog"))
        s.ctl("tap:364:712", "wait:6000", s.shot_cmd("d1-after-ok"))
        s.ctl("wait:6000", s.shot_cmd("d2-after-ok"))
        show(s.state("4-after-refusal"))

    if not common.drive(s, body):
        return 1
    c1 = common.state_value(st[2], r"coins free ([0-9]+)")
    c2 = common.state_value(st[3], r"coins free ([0-9]+)")
    fails = common.checks(
        (s.in_client(r"MissionEnd mission [0-9]*: unlocked mf01_004"), "mf01_003's first clear didn't unlock mf01_004"),
        (s.in_client(r"MissionEnd mission [0-9]* drops: surprise yes"), "no surprise drops"),
        (s.in_client(r"step-up chain 478440451 step 1 -> 2"), "no step-up step 1 -> 2"),
        (s.in_client(r"step-up chain .* step 2 -> 3"), "no step-up step 2 -> 3"),
        (c1 is not None and c2 is not None and c2 < c1, "the step-up draws debited no coins (%s -> %s)" % (c1, c2)))
    return common.verdict(s, fails, "a surprise-enemy battle (drops, mf01_004 unlocked), two steps of a step-up gacha (%s -> %s coins), "
                          "MissionStart refused at stamina 0 (10004 dialog)" % (c1, c2))
