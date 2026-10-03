"""Session `deepspace`: the restored deep space mode (the in-process local server;
server/src/api/deepspace/deepspace.cpp): boot -> home -> deep space (CPhase_DeepSpace, phase 6, the
`phase:6` control command) -> the first area -> its first mission -> party select, one bonus tapped
(DeepSpaceAutoMemberSelect) -> start (DeepSpaceMissionStart) -> the server clock fast-forwarded past
the expedition (`clock:+SECONDS`) -> back in -> the returned ship collected (DeepSpaceMissionEnd) ->
the result pages. Then a second expedition returned at once (今すぐ帰還, DeepSpaceMissionEndNow) and
collected. The run has the Galaxy Pass (--galaxy-pass: +2 ships): two expeditions then depart at
once, the second on a pass ship, and 実績 shows the deep space achievements; 一括達成 receives the
two expedition achievements into the present box. Screenshots go to OUT/shots, the server's
deep-space tables to OUT/state-*.txt, the log to OUT/log.txt. Exit status 1 if an API didn't answer
as expected.

Usage: port/scripts/deepspace_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc (the `phase:` / `clock:` control commands)."""
import os
import re
import sqlite3

from ..flows import mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it uses the port's `phase:6` and `clock:+S` control commands"
WRAPPER = "port/scripts/deepspace_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def ds_state(s, tag):
    c = sqlite3.connect(s.state_db)
    out = ["area %s %s" % r for r in c.execute("select area_id, exp from ds_area order by area_id")]
    out += ["ship %s %s %s %s" % r for r in c.execute("select ship_id, mission_id, closed_at - started_at, uids from ds_ship order by ship_id")]
    out.append("offers %s" % c.execute("select count(*) from ds_offer").fetchone()[0])
    out.append("free_coin %s" % c.execute("select free_coin from player").fetchone()[0])
    out.append("presents %s" % c.execute("select count(*) from presents").fetchone()[0])
    c.close()
    text = "\n".join(out) + "\n"
    with open(os.path.join(s.layout.state_dir, "state-%s.txt" % tag), "w") as f:
        f.write(text)
    print(text, end="", flush=True)
    return text


def main(o):
    s = common.port_run(o, common.port_config(o, ["--galaxy-pass"], limit=2400))
    c, w = s.ctl, s.wait_log
    st = {}

    def body(s):
        # The login popups closed: left open, the LOGIN BONUS popup stays up over deep space (the
        # phase:6 control command bypasses it) and its 閉じる swallows the result page's OK tap.
        common.port_login(s, "01-title", "02-notice", "02-login-bonus", "03-home")
        # Deep space: CPhase_DeepSpace sends DeepSpaceActiveList.
        c("phase:6")
        w(r"DeepSpaceActiveList: ", 60, name="DeepSpaceActiveList")
        c("wait:5000", s.shot_cmd("04-deepspace"))
        c("tap:360:680", "wait:4000", s.shot_cmd("05-missions"))  # the focused area, its mission list
        c("tap:360:790", "wait:5000", s.shot_cmd("06-party"))  # the first mission (0.5H): party select
        c("tap:350:790")
        w(r"DeepSpaceAutoMemberSelect bonus", 30, name="DeepSpaceAutoMemberSelect")
        c("wait:4000", s.shot_cmd("07-auto"))
        c("tap:630:1120", "wait:3000", s.shot_cmd("08-confirm"), "tap:515:1003")  # 決定 -> 探査開始
        w(r"DeepSpaceMissionStart area", 30, name="DeepSpaceMissionStart")
        c("wait:6000", s.shot_cmd("09-started"))
        st[1] = ds_state(s, "1-started")
        # Fast-forward the server clock past the expedition (30 minutes), leave to home and come back.
        c("clock:+1900", "tap:100:1120", "wait:3000", "tap:100:1120")
        w(mission.phase(4), 60, name="home")
        c("wait:5000", "phase:6")
        w(r"DeepSpaceActiveList: .* 0 ships out, 1 back", 60, name="DeepSpaceActiveList: the ship back")
        c("wait:5000", s.shot_cmd("10-returned"))
        c("tap:360:680", "wait:4000", s.shot_cmd("11-area"), "tap:360:790")
        w(r"DeepSpaceMissionEnd ship", 30, name="DeepSpaceMissionEnd")
        c("wait:6000", s.shot_cmd("12-result-items"), "tap:364:1050", "wait:5000", s.shot_cmd("13-result-characters"))
        c("tap:364:1050", "wait:5000", s.shot_cmd("14-after"))
        st[2] = ds_state(s, "2-collected")
        # A second expedition, returned at once (今すぐ帰還: DeepSpaceMissionEndNow for coins), collected.
        c("tap:360:790", "wait:5000", "tap:350:790")
        w(r"DeepSpaceAutoMemberSelect bonus", 30, name="DeepSpaceAutoMemberSelect (2)")
        c("wait:4000", "tap:630:1120", "wait:3000", "tap:515:1003")
        w(r"DeepSpaceMissionStart area", 30, name="DeepSpaceMissionStart (2)")
        c("wait:6000", s.shot_cmd("15-started-2"), "tap:655:797", "wait:4000", s.shot_cmd("16-quick-return"))
        c("tap:515:890")
        w(r"DeepSpaceMissionEndNow ship", 30, name="DeepSpaceMissionEndNow")
        c("wait:5000", s.shot_cmd("17-quick-returned"), "tap:364:800", "wait:5000", s.shot_cmd("18-returned-2"))
        c("tap:360:790")
        w(r"DeepSpaceMissionEnd ship", 30, name="DeepSpaceMissionEnd (2)")
        c("wait:6000", s.shot_cmd("19-result-2"), "tap:364:1050", "wait:5000", "tap:364:1050", "wait:5000", s.shot_cmd("20-after-2"))
        st[3] = ds_state(s, "3-quick")
        # Two expeditions at once: the 0.5H mission (ship 1), then the 1H mission (ship 2, a pass ship).
        c("tap:360:790", "wait:5000", "tap:350:790")
        w(r"DeepSpaceAutoMemberSelect bonus", 30, name="DeepSpaceAutoMemberSelect (3)")
        c("wait:4000", "tap:630:1120", "wait:3000", "tap:515:1003")
        w(r"DeepSpaceMissionStart area .*: ship 1/", 30, name="DeepSpaceMissionStart: ship 1")
        c("wait:6000", "tap:320:868", "wait:5000", s.shot_cmd("21-party-2"), "tap:350:790")
        w(r"DeepSpaceAutoMemberSelect bonus", 30, name="DeepSpaceAutoMemberSelect (4)")
        c("wait:4000", "tap:630:1120", "wait:3000", "tap:515:1003")
        w(r"DeepSpaceMissionStart area .*: ship 2/", 30, name="DeepSpaceMissionStart: ship 2")
        c("wait:6000", s.shot_cmd("22-two-ships"))
        st[4] = ds_state(s, "4-pass")
        # 実績: the deep space achievements (the screen opens on a tab with an achieved row: その他).
        c("tap:655:262", "wait:5000", s.shot_cmd("23-achievements"), "tap:590:303", "wait:3000", s.shot_cmd("24-achievements-other"))
        c("tap:515:1053")  # 一括達成: the rewards go to the present box
        w(r"request Achievement(Receive|ListReceive|ReceiveList) ", 30, name="AchievementReceive")
        c("wait:5000", s.shot_cmd("25-achievements-received"))
        st[5] = ds_state(s, "5-achievements")

    if not common.drive(s, body):
        return 1
    val = lambda text, key: common.state_value(text, r"^%s ([0-9]+)" % key)
    c1, c2 = val(st[2], "free_coin"), val(st[3], "free_coin")
    p4, p5 = val(st[4], "presents"), val(st[5], "presents")
    ships = lambda text: len(re.findall(r"^ship ", text, re.M))
    fails = common.checks(
        (ships(st[1]), "no ship out after DeepSpaceMissionStart"),
        (not ships(st[2]), "the ship wasn't collected"),
        (not ships(st[3]), "the quick-returned ship wasn't collected"),
        (c1 is not None and c2 is not None and c2 < c1, "the quick return cost nothing (%s -> %s)" % (c1, c2)),
        (p4 is not None and p5 is not None and p5 >= p4 + 2,
         "the two expedition achievements' rewards didn't reach the present box (%s -> %s)" % (p4, p5)),
        (s.in_client(r"request AchievementActiveList"), "the achievements screen didn't ask for its list"),
        (s.in_client(r"DeepSpaceActiveList: .* \(2 by the pass\)"), "the Galaxy Pass ships weren't counted"),
        (ships(st[4]) == 2, "two expeditions weren't out at once (pass ship)"),
    )
    for ln in open(s.client_log, errors="replace").read().splitlines():
        if re.search(r"DeepSpace(ActiveList|AutoMemberSelect|MissionStart|MissionEnd|MissionEndNow)", ln) and "I/server: Deep" in ln:
            print(ln)
    fails += common.common_log_checks(s, crash=False)
    return common.verdict(s, fails, "deep space expedition started, returned, collected; quick return; a Galaxy Pass ship")
