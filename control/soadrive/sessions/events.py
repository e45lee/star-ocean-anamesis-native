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

from .. import popups
from ..flows import mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it waits on the port's phase lines and the in-process server's event lines"
WRAPPER = "port/scripts/events_session.sh"
P5 = mission.phase(5)


def options(ap):
    common.port_options(ap, extra=False)
    ap.add_argument("clock", nargs="?", default="", help='the server clock "YYYY-MM-DD HH:MM:SS" (the story part\'s layouts)')


def screen(s, name, xy, shot=None, **kw):
    """A tap to the next screen (common.tap_to_screen); the session counts its FAILs and goes on."""
    kw.setdefault("mask", common.EVENT_MASK)  # the banner carousel: a change no tap made
    return common.tap_to_screen(s, name, xy, shot, fatal=False, **kw)


def battle(s, tag, helper):
    """From a mission's detail: single play -> helper (x:y, or 選択しない) -> party 1 -> start ->
    the battle -> the result pages -> the menu (phase 5)."""
    screen(s, tag + " シングルプレイ開始", "364:905", tag + "-helper")
    screen(s, tag + " helper -> the party", helper, tag + "-party", is_screen=popups.is_party_start)
    started = r"MissionStart mission [0-9]* \(master_event_mission\)"
    if mission.start_mission(s, tag + " ミッション開始 -> 決定 (the start)", mission.log_more(s.client_log, started), fatal=False):
        s.wait_log(started, 60, name=tag + " MissionStart", fatal=False)
    s.wait_log(r"MissionEnd mission [0-9]*: player exp", 300, name=tag + " won", fatal=False)
    common.settle(s, tag + "-result", hold=2)
    mission.results_until(s, P5, 0, 15, 4000, fmt=None, name=tag + " result -> menu", fatal=False)
    common.settle(s, tag + "-after")


def story(s, tag, node):
    screen(s, tag + " the story's node", node, tag + "-detail")
    common.tap_to_log(s, tag + " scene", "515:715", mission.phase(3), tries=1, secs=30, wait_still=False)
    # the scene's first frames: its スキップ shows once the scene holds still a while
    common.settle(s, tag + "-scene", hold=2)
    screen(s, tag + " スキップ", "115:1240", tag + "-skip")
    common.tap_to_log(s, tag + " cleared", "515:742", r"events: story mission [0-9]* played", secs=60, tries=1, wait_still=False)
    s.wait_log(P5, 60, name=tag + " -> board", fatal=False)
    common.settle(s, tag + "-board", hold=2)


def main(o):
    cfg = common.port_config(o, ["--clock", o.clock] if o.clock else [], limit=2400)
    s = common.port_run(o, cfg)

    def body(s):
        common.port_login(s, "01-title", "02-notice", "03-login-bonus", "04-home")
        common.settle(s, mask=common.HOME_MASK)
        line = s.last_line(r"events: [0-9]+ event areas open")
        if line:
            print("  " + line)
        # ---- the event list and a daily material mission ----
        common.tap_to_phase(s, "events", "90:1085", 5, "10-events", mask=common.HOME_MASK)
        screen(s, "素材 tab", "515:370", "11-materials")
        # The tab lists the materials by order_id, highest first; the day's EXP mission is the last:
        # scroll to the end, then its banner is the bottom one.
        common.scroll_to_end(s, "drag:364:950:364:450", "12-materials-end", mask=common.EVENT_MASK)
        screen(s, "the day's EXP mission", "364:985", "13-daily")
        screen(s, "its mission", "364:415", "14-daily-detail")
        battle(s, "20-daily", "620:1120")
        s.check("daily: next mission unlocked", s.in_client(r"MissionEnd mission [0-9]*: unlocked"))
        screen(s, "戻る", "100:1120")
        screen(s, "イベント tab", "210:370", "30-event-tab")
        # ---- a story event ----
        if o.clock == "2020-05-29 15:00:00":
            screen(s, "the kimono event", "364:525", "31-kimono")
            story(s, "32-story", "362:650")
            # the battle the story unlocked (me99_1027), with the NPC 鬼炎のアルベル as the 4th member
            screen(s, "the battle the story unlocked", "620:660", "40-battle-detail")
            battle(s, "41-npc", "364:525")
            s.check("npc helper", s.in_client(r"event NPC helper [0-9]* .* as member 4"))
        elif o.clock == "2021-06-10 15:00:00":
            screen(s, "the idol event", "364:830", "31-idol4")
            story(s, "32-story", "362:330")
        else:
            screen(s, "the first event", "364:525", "31-first-event")
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
