"""Session `events`: event missions, restored (the in-process local server;
server/src/api/events/event_missions.cpp), from the title through the real UI:

  title -> home -> イベント (CPhase_Mission, mission type 1: CEventMissionMenu) -> 素材 tab -> the
  day's EXP material mission (the last banner of the tab: lowest order_id) -> its first mission ->
  single play -> no helper -> party 1 -> battle (MissionStart / MissionEnd of a
  master_event_mission row) -> result pages -> back on the list: CLEAR, the next mission New.
  With a known clock (below), also a story event: イベント tab -> the event -> its first story
  (ストーリー開始 -> スキップ -> はい) -> the scene's end clears it (EndMissionTalk -> the local
  server) -> the board shows CLEAR and the next node New; on 2020-05-29 the battle it unlocks is
  then played with an event NPC helper (the helper list shows only the mission's NPCs).

Which events are open is the server's runtime decision (event calendar, clock, assets present);
the tap positions of the story part are the layout on the two dates below (test data only):
  2020-05-29 15:00:00  滅びの星に鬼が舞う (event_kimono_91): story mc99_553 -> battle me99_1027 (NPC)
  2021-06-10 15:00:00  夢追い少女と銀河の歌星 (event_idol4_89, rerun): story mc99_591
Without a clock (the replayed calendar) the daily part runs and the event tab is only shown.
Every step waits for its screen or log line, then screenshots (<out>/shots).

Usage: port/scripts/events_session.sh <soa> <out-dir> <scratch-dir> [clock "YYYY-MM-DD HH:MM:SS"]
Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1. Ends with "events_session: PASS", or
"events_session: FAIL (N)" and exit status 1 when a step isn't reached.
Targets: port-inproc (the phase lines and the in-process server's event lines)."""
import re

from ..flows import mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it waits on the port's phase lines and the in-process server's event lines"
WRAPPER = "port/scripts/events_session.sh"
P5 = mission.phase(5)


def options(ap):
    common.port_options(ap, extra=False)
    ap.add_argument("clock", nargs="?", default="", help='the server clock "YYYY-MM-DD HH:MM:SS" (the story part\'s layouts)')


def battle(s, tag, helper):
    """From a mission's detail: single play -> helper (x:y, or 選択しない) -> party 1 -> start ->
    the battle -> the result pages -> the menu (phase 5)."""
    s.ctl("tap:364:905", "wait:5000", s.shot_cmd(tag + "-helper"), "tap:" + helper, "wait:5000", s.shot_cmd(tag + "-party"))
    s.ctl("tap:364:900", "wait:3000", "tap:515:712")
    s.wait_log(r"MissionStart mission [0-9]* \(master_event_mission\)", 60, name=tag + " MissionStart", fatal=False)
    s.wait_log(r"MissionEnd mission [0-9]*: player exp", 300, name=tag + " won", fatal=False)
    s.ctl("wait:4000", s.shot_cmd(tag + "-result"))
    mission.results_until(s, P5, 0, 15, 4000, fmt=None, name=tag + " result -> menu", fatal=False)
    s.ctl("wait:5000", s.shot_cmd(tag + "-after"))


def story(s, tag, node):
    s.ctl("tap:" + node, "wait:4000", s.shot_cmd(tag + "-detail"), "tap:515:715")
    s.wait_log(mission.phase(3), 30, name=tag + " scene", fatal=False)
    s.ctl("wait:12000", s.shot_cmd(tag + "-scene"), "tap:115:1240", "wait:2000", s.shot_cmd(tag + "-skip"), "tap:515:742")
    s.wait_log(r"events: story mission [0-9]* played", 60, name=tag + " cleared", fatal=False)
    s.wait_log(P5, 60, name=tag + " -> board", fatal=False)
    s.ctl("wait:8000", s.shot_cmd(tag + "-board"))


def main(o):
    cfg = common.port_config(o, ["--clock", o.clock] if o.clock else [], limit=2400)
    s = common.port_run(o, cfg)

    def body(s):
        common.port_login(s, "01-title", "02-notice", "03-login-bonus", "04-home")
        line = s.last_line(r"events: [0-9]+ event areas open")
        if line:
            print("  " + line)
        # ---- the event list and a daily material mission ----
        s.tap_log(P5, 60, 20, 3, "tap:90:1085", name="events", fatal=False)
        s.ctl("wait:8000", s.shot_cmd("10-events"), "tap:515:370", "wait:4000", s.shot_cmd("11-materials"))
        # The tab lists the materials by order_id, highest first; the day's EXP mission is the last:
        # scroll to the end, then its banner is the bottom one.
        s.ctl("drag:364:950:364:450", "wait:3000", s.shot_cmd("12-materials-end"), "tap:364:985", "wait:6000",
              s.shot_cmd("13-daily"))
        s.ctl("tap:364:415", "wait:4000", s.shot_cmd("14-daily-detail"))
        battle(s, "20-daily", "620:1120")
        s.check("daily: next mission unlocked", s.in_client(r"MissionEnd mission [0-9]*: unlocked"))
        s.ctl("tap:100:1120", "wait:5000", "tap:210:370", "wait:4000", s.shot_cmd("30-event-tab"))
        # ---- a story event ----
        if o.clock == "2020-05-29 15:00:00":
            s.ctl("tap:364:525", "wait:8000", s.shot_cmd("31-kimono"))
            story(s, "32-story", "362:650")
            # the battle the story unlocked (me99_1027), with the NPC 鬼炎のアルベル as the 4th member
            s.ctl("tap:620:660", "wait:4000", s.shot_cmd("40-battle-detail"))
            battle(s, "41-npc", "364:525")
            s.check("npc helper", s.in_client(r"event NPC helper [0-9]* .* as member 4"))
        elif o.clock == "2021-06-10 15:00:00":
            s.ctl("tap:364:830", "wait:8000", s.shot_cmd("31-idol4"))
            story(s, "32-story", "362:330")
        else:
            s.ctl("tap:364:525", "wait:8000", s.shot_cmd("31-first-event"))
            print("  (no known layout for this clock: the story part is skipped)")

    common.drive(s, body)
    for ln in open(s.client_log, errors="replace").read().splitlines():
        if re.search(r"events:|restore: CEvent|MissionEnd mission|NPC helper", ln):
            print("  " + ln)
    fails = sum(1 for r in s.results if r.startswith("FAIL"))
    if fails:
        print("events_session: FAIL (%d)" % fails)
        return 1
    print("events_session: PASS")
    return 0
