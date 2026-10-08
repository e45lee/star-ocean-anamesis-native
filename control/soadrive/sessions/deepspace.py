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
    # the crew as "uid,uid" (ds_ship_member by slot, PLAN-schema S7; the text ds_ship.uids was)
    crew = "(select group_concat(uid, ',') from (select uid from ds_ship_member m where m.ship_id = s.ship_id order by slot))"
    out += ["ship %s %s %s %s" % r for r in c.execute("select ship_id, mission_id, closed_at - started_at, %s from ds_ship s order by ship_id" % crew)]
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

    def start(rx, name, shot=None):
        """The party (its crew auto-selected) -> 決定 -> the expedition's confirmation -> 探査開始, each
        tap checked on a screenshot and retried (flows/mission.py start_mission), until rx is logged."""
        mission.open_mission_confirm(s, mission.DEEPSPACE)
        if shot:
            c(s.shot_cmd(shot))
        mission.start_mission(s, "決定 -> 探査開始 (%s)" % name, mission.log_more(s.client_log, rx), d=mission.DEEPSPACE, opened=True)
        w(rx, 30, name=name)

    def screen(name, xy, shot=None, **kw):
        return common.tap_to_screen(s, name, xy, shot, **kw)

    def req(name, xy, rx, shot=None):
        return common.tap_to_log(s, name, xy, rx, shot, secs=30, every=10, fatal=True)

    def deepspace(rx, name, shot):
        """phase:6 (CPhase_DeepSpace, which sends DeepSpaceActiveList; the command bypasses the home
        screen's button), then the deep space screen faded in."""
        before = common.look(s, ".before-deepspace.png")
        c("phase:6")
        w(rx, 60, name=name)
        common.settle(s, shot, differs_from=before)

    def results(second, after):
        """The result pages' OK, made again while the page stays (a dropped OK shifted every later tap)."""
        screen("the result's items page closed", "364:1050", second)
        screen("the result's characters page closed", "364:1050", after)

    def body(s):
        # The login popups closed: left open, the LOGIN BONUS popup stays up over deep space (the
        # phase:6 control command bypasses it) and its 閉じる swallows the result page's OK tap.
        common.port_login(s, "01-title", "02-notice", "02-login-bonus", "03-home")
        common.settle(s, mask=common.HOME_MASK)
        deepspace(r"DeepSpaceActiveList: ", "DeepSpaceActiveList", "04-deepspace")
        screen("the focused area: its mission list", "360:680", "05-missions")
        screen("the first mission (0.5H): party select", "360:790", "06-party")
        req("DeepSpaceAutoMemberSelect", "350:790", r"DeepSpaceAutoMemberSelect bonus", "07-auto")
        start(r"DeepSpaceMissionStart area", "DeepSpaceMissionStart", "08-confirm")
        common.settle(s, "09-started")
        st[1] = ds_state(s, "1-started")
        # Fast-forward the server clock past the expedition (30 minutes), leave to home and come back.
        c("clock:+1900")
        screen("戻る", "100:1120")
        common.tap_to_phase(s, "戻る -> home", "100:1120", 4, mask=common.HOME_MASK, fatal=True)
        deepspace(r"DeepSpaceActiveList: .* 0 ships out, 1 back", "DeepSpaceActiveList: the ship back", "10-returned")
        screen("the area", "360:680", "11-area")
        req("DeepSpaceMissionEnd", "360:790", r"DeepSpaceMissionEnd ship", "12-result-items")
        results("13-result-characters", "14-after")
        st[2] = ds_state(s, "2-collected")
        # A second expedition, returned at once (今すぐ帰還: DeepSpaceMissionEndNow for coins), collected.
        screen("the first mission: party select", "360:790")
        req("DeepSpaceAutoMemberSelect (2)", "350:790", r"DeepSpaceAutoMemberSelect bonus")
        start(r"DeepSpaceMissionStart area", "DeepSpaceMissionStart (2)")
        common.settle(s, "15-started-2")
        screen("今すぐ帰還", "655:797", "16-quick-return")
        req("DeepSpaceMissionEndNow", "515:890", r"DeepSpaceMissionEndNow ship", "17-quick-returned")
        screen("returned: 閉じる", "364:800", "18-returned-2")
        req("DeepSpaceMissionEnd (2)", "360:790", r"DeepSpaceMissionEnd ship", "19-result-2")
        results("19b-result-2-characters", "20-after-2")
        st[3] = ds_state(s, "3-quick")
        # Two expeditions at once: the 0.5H mission (ship 1), then the 1H mission (ship 2, a pass ship).
        screen("the first mission: party select", "360:790")
        req("DeepSpaceAutoMemberSelect (3)", "350:790", r"DeepSpaceAutoMemberSelect bonus")
        start(r"DeepSpaceMissionStart area .*: ship 1/", "DeepSpaceMissionStart: ship 1")
        common.settle(s)
        screen("the 1H mission: party select", "320:868", "21-party-2")
        req("DeepSpaceAutoMemberSelect (4)", "350:790", r"DeepSpaceAutoMemberSelect bonus")
        start(r"DeepSpaceMissionStart area .*: ship 2/", "DeepSpaceMissionStart: ship 2")
        common.settle(s, "22-two-ships")
        st[4] = ds_state(s, "4-pass")
        # 実績: the deep space achievements (the screen opens on a tab with an achieved row: その他).
        screen("実績", "655:262", "23-achievements")
        # (it opens on その他 already: the tab's tap changes nothing, so it isn't checked)
        common.tap_settled(s, "590:303", "24-achievements-other")
        # 一括達成: the rewards go to the present box
        req("AchievementReceive", "515:1053", r"request Achievement(Receive|ListReceive|ReceiveList) ", "25-achievements-received")
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
