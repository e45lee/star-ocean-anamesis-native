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
What is open depends on the day and the hour (without a clock: the replayed calendar's), so the
session first works out what the client's event menu lists (client_menu below: the server's last
ActiveEventMissionList, the client's copy of the master, the client's clock and time rules): the
daily part runs when an EXP material area (event_exp_*) is listed, the event tab's first event is
opened when the tab lists one; otherwise the part is skipped with a note naming the client clock
(at the two dates above a missing EXP mission is a FAIL).
The T2 test (tests/tiers.json) runs at 2020-05-29 15:00:00, where every part is known to be there.
Every step waits for its screen or log line, then screenshots (<out>/shots).

Usage: port/scripts/events_session.sh <soa> <out-dir> <scratch-dir> [clock "YYYY-MM-DD HH:MM:SS"]
Env: SOA_PHONE (scripts/shared-phone.sh), SEED_RNG, WATCH=1. Ends with "events_session: PASS", or
"events_session: FAIL (N)" and exit status 1 when a step isn't reached.
Targets: port-inproc (the phase lines and the in-process server's event lines)."""
import glob
import os
import re
import sqlite3
import time

from .. import popups
from ..flows import mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it waits on the port's phase lines and the in-process server's event lines"
WRAPPER = "port/scripts/events_session.sh"
P5 = mission.phase(5)
KNOWN_CLOCKS = ("2020-05-29 15:00:00", "2021-06-10 15:00:00")  # the story part's layouts (the docstring)


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


def mktime_local(y, mo, d, h, mi, sec):
    """A local wall time as Unix seconds, daylight saving included: common/include/soa/local_time.h's
    rule (soa::mktime_local), which the server and the client's mktime (platform370) follow. Of the
    host mktime's two readings (tm_isdst 0: standard, 1: daylight) the self-consistent one; both (the
    repeated autumn hour): the earlier; neither (the skipped spring hour): the standard one."""
    t0 = time.mktime((y, mo, d, h, mi, sec, 0, 0, 0))
    t1 = time.mktime((y, mo, d, h, mi, sec, 0, 0, 1))
    v0, v1 = time.localtime(t0).tm_isdst == 0, time.localtime(t1).tm_isdst > 0
    if v0 and v1:
        return min(t0, t1)
    return t1 if v1 else t0


def _client_time(text):
    """(b) A date-time string as the client reads it (CTimeUtility::str2time_t): the local time,
    daylight saving included (platform370's mktime, docs/client-changes.md "Local time: daylight
    saving"; the shipped client, --no-dst-fix, read it as standard time). None when unparsable."""
    m = re.match(r"(\d{4})[-/](\d{2})[-/](\d{2}) (\d{1,2}):(\d{2})(?::(\d{2}))?", text or "")
    if not m:
        return None
    return mktime_local(*(int(x or 0) for x in m.groups()))


def _last_event_list(packets_dir):
    """The last response with an ActiveEventMissionList (the list the event menu reads; the menu
    itself sends no request), its data.Time and the file's time: (areas, time text, mtime)."""
    import msgpack  # requirements.txt

    def number(path):
        m = re.match(r"(\d+)-", os.path.basename(path))
        return int(m.group(1)) if m else -1

    for path in sorted(glob.glob(os.path.join(packets_dir, "*Res*.msgp")) + glob.glob(os.path.join(packets_dir, "*Result*.msgp")),
                       key=number, reverse=True):
        try:
            body = msgpack.unpackb(open(path, "rb").read(), raw=False, strict_map_key=False)
        except Exception:
            continue
        data = body.get("data") if isinstance(body, dict) else None
        if isinstance(data, dict) and isinstance(data.get("ActiveEventMissionList"), dict):
            return data["ActiveEventMissionList"].get("EventArea") or {}, data.get("Time"), os.path.getmtime(path)
    return None, None, None


def client_menu(s):
    """What the event menu lists, by the client's rules (MissionUtility::GetEventAreaList, docs:
    server/src/api/events/event_missions.cpp): of the areas in the server's last
    ActiveEventMissionList, those whose master_event_term (opened_day opened_time .. closed_day
    closed_time) or whose master_event_weekly row for the weekday of the client clock (that date's
    opened_time .. closed_time) covers the client clock, read from the client's own master copy
    (the served one: the dated tables moved into the client's years). The client clock is the
    server's data.Time plus the time since, both read the client's way (_client_time).
    Returns {"clock": text, "materials": [id_label...], "events": [id_label...]} (materials: the 素材
    tab, master_event_area.event_tab 1; events: the イベント tab), or None without the data."""
    areas, now_text, stamp = _last_event_list(os.path.dirname(s.packets))
    master = os.path.join(s.phone, "cdn", "basmaster-served.sqlite3")
    if areas is None or not os.path.exists(master):
        return None
    base = _client_time(now_text)
    if base is None:
        return None
    now = base + max(0.0, time.time() - stamp)
    local = time.localtime(now)
    day = time.strftime("%Y/%m/%d", local)
    week = (local.tm_wday + 1) % 7  # tm_wday: 0 Sunday (Python's: 0 Monday)
    out = {"clock": time.strftime("%Y-%m-%d %H:%M:%S", local), "materials": [], "events": []}
    db = sqlite3.connect("file:%s?mode=ro" % master, uri=True)
    try:
        for area in areas:
            row = db.execute("select id_label, event_tab from master_event_area where id = ?", (int(area),)).fetchone()
            if not row:
                continue
            spans = [(t[0] + " " + (t[1] or "00:00:00"), t[2] + " " + (t[3] or "23:59:59"))
                     for t in db.execute("select opened_day, opened_time, closed_day, closed_time from master_event_term "
                                         "where master_event_area_id = ? and opened_day != '' and closed_day != ''", (int(area),))]
            spans += [(day + " " + (w[0] or "0:00"), day + " " + (w[1] or "23:59"))
                      for w in db.execute("select opened_time, closed_time from master_event_weekly "
                                          "where master_event_area_id = ? and week_id = ?", (int(area), week))]
            if any((_client_time(a) or now + 1) <= now <= (_client_time(b) or now - 1) for a, b in spans):
                out["materials" if row[1] == 1 else "events"].append(row[0])
    finally:
        db.close()
    return out


def main(o):
    cfg = common.port_config(o, ["--clock", o.clock] if o.clock else [], limit=2400)
    s = common.port_run(o, cfg)

    def body(s):
        common.port_login(s, "01-title", "02-notice", "03-login-bonus", "04-home")
        common.settle(s, mask=common.HOME_MASK)
        line = s.last_line(r"events: [0-9]+ event areas open")
        if line:
            print("  " + line)
        # ---- what the menu lists (with a clock: the known layouts; without: the day and hour's) ----
        menu = client_menu(s)
        if menu is None:
            s.miss("the event menu's contents (no ActiveEventMissionList or served master)")
            menu = {"clock": "?", "materials": [], "events": []}
        print("  the event menu at the client clock %s: materials %s; events %d" % (menu["clock"], " ".join(sorted(menu["materials"])), len(menu["events"])))
        daily = any(label.startswith("event_exp_") for label in menu["materials"])
        # ---- the event list and a daily material mission ----
        common.tap_to_phase(s, "events", "90:1085", 5, "10-events", mask=common.HOME_MASK)
        screen(s, "素材 tab", "515:370", "11-materials")
        # The tab lists the materials by order_id, highest first; the EXP areas (event_exp_*) have
        # the lowest, so the bottom banner is one of them: scroll to the end, then tap it.
        common.scroll_to_end(s, "drag:364:950:364:450", "12-materials-end", mask=common.EVENT_MASK)
        if not daily and o.clock in KNOWN_CLOCKS:
            s.miss("an EXP material mission listed at %s (the client clock %s)" % (o.clock, menu["clock"]))
        if daily:
            screen(s, "the day's EXP mission", "364:985", "13-daily")
            screen(s, "its mission", "364:415", "14-daily-detail")
            battle(s, "20-daily", "620:1120")
            s.check("daily: next mission unlocked", s.in_client(r"MissionEnd mission [0-9]*: unlocked"))
        else:
            s.note("no EXP material mission listed at the client clock %s: the daily part is skipped" % menu["clock"])
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
        elif menu["events"]:
            screen(s, "the first event", "364:525", "31-first-event")
            print("  (no known layout for this clock: the story part is skipped)")
        else:
            s.note("no event listed at the client clock %s: the event tab is empty" % menu["clock"])

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
