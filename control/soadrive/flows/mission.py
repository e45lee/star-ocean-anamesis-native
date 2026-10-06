"""Missions from home (PLAN-consolidate's flows/mission.py): the campaign's 1-05 (mf01_001, open with
soa-server --campaign-seed mf01_001) through the mission map, its battle and result pages, back
home. Used by the `seeded` flow and the `battle` shard.

Also every program's mission start through the UI (start_mission: ミッション開始 -> the confirmation
-> 決定, each tap checked on a screenshot and retried), used by the campaign, events, tower,
simulator and Sphere 211 sessions, tests/diff's battle and event flows and deep space's expedition."""
import os
import re
import time

from .. import milestones, popups, screens, ui370
from ..targets import Abort

# The screens this part takes (RMSE limits against the emulator's; None: shown, not gated).
HOME = (0.08, (screens.HOME_CHARACTER,))
SCREENS = {
    "03-planets": 0.08,
    "04-mission-map": 0.08,
    "05-mission-detail": 0.08,
    "06-party": 0.08,
    "07-start-confirm": 0.08,
    "08-battle": None,
    "09-result": None,
    "10-map-after-clear": 0.08,
    "11-home-after-battle": HOME,
}


def campaign_105(s):
    """Home -> ミッション -> the planet select (or the map of the planet last played) -> Mere -> 出撃
    -> 1-05 -> the battle -> the results -> the map -> home. Returns the state text after the battle."""
    n = s.n_packets(r"< GetMissionListRes")
    s.tap_until("ミッション -> GetMissionList", 60, ui370.HOME_MISSION, s.more_than(r"< GetMissionListRes", n))
    s.ctl("wait:6000")
    planets = s.shot("03-planets")
    if (screens.mean(planets, "120x60+527+750") or 0) > 0.45:
        s.ctl("tap:" + ui370.PLANET_MERE, "wait:3000", "tap:" + ui370.PLANET_SORTIE, "wait:7000")
    else:
        s.note("the mission map of the planet last played (no planet select)")
    s.shot("04-mission-map")
    s.ctl("tap:" + ui370.MAP_105, "wait:4000")
    s.shot("05-mission-detail")
    s.ctl("tap:" + ui370.SINGLE_PLAY, "wait:5000", "tap:" + ui370.RENTAL_NONE, "wait:5000")
    s.shot("06-party")
    open_mission_confirm(s)
    s.shot("07-start-confirm")
    start_mission(s, "1-05 -> MissionStart -> MissionStartRes", lambda: s.in_packets(r"< MissionStartRes"), opened=True)
    s.ctl("wait:15000")
    s.shot("08-battle", settle=False)
    s.wait_for("the battle: MissionEnd (battle log) -> MissionEndRes", 600, lambda: s.in_packets(r"< MissionEndRes"))
    st = s.state("2-after-battle")
    s.check("server state: mf01_001 cleared", re.search(r"mission mf01_001: cleared 1", st) is not None)
    n = s.n_packets(r"< GetMissionListRes")
    s.ctl("wait:3000")
    s.shot("09-result", settle=False)
    s.tap_until("the result pages -> the mission map (GetMissionList)", 90, ui370.RESULT_OK, s.more_than(r"< GetMissionListRes", n))
    s.ctl("wait:4000")
    s.shot("10-map-after-clear")
    s.ctl("tap:" + ui370.FOOTER_HOME, "wait:8000")
    s.shot("11-home-after-battle")
    return st


# ---- a mission's start through the UI: ミッション開始 -> ミッションを開始しますか? -> 決定 ----------------------
# A tap can be lost (while a screen fades in, under load): session:tower once lost ミッション開始 (the
# party screen stayed, MissionStart never sent) and a blind 決定 then lands on the party's third card.
# So every tap here is followed by a screenshot, and the next one is made only on the screen it is for.
class Dialog:
    """A start dialog: the tap that opens it (on the screen `is_from` recognizes), the tap that
    confirms it (on the dialog, `is_open`), and the names of the SOA_TEST_DROP_TAP test switch."""
    def __init__(self, what, open_xy, ok_xy, is_from, is_open, drop_open, drop_ok):
        self.what, self.open_xy, self.ok_xy, self.is_from, self.is_open = what, open_xy, ok_xy, is_from, is_open
        self.drop_open, self.drop_ok = drop_open, drop_ok


# the party screen's ミッション開始 -> ミッションを開始しますか? 閉じる / 決定 (the campaign, events, tower, the
# simulator: the same buttons at the same spots on every program)
MISSION = Dialog("the start confirmation", ui370.PARTY_START, ui370.CONFIRM_OK, popups.is_party_start,
                 popups.is_mission_confirm, "mission-start", "mission-decide")
# Sphere 211: its party's ミッション開始 (left of 自動編成) -> the same confirmation
SPHERE211 = Dialog("the start confirmation", ui370.SPHERE211_START, ui370.CONFIRM_OK, popups.is_sphere211_party,
                   popups.is_mission_confirm, "mission-start", "mission-decide")
# deep space: the party screen's 決定 -> 以下の内容で探査を開始します 戻る / 探査開始
DEEPSPACE = Dialog("the expedition's confirmation", ui370.DEEPSPACE_DECIDE, ui370.DEEPSPACE_START,
                   popups.is_deepspace_party, popups.is_deepspace_confirm, "deepspace-start", "deepspace-decide")


def _tap(s, d, xy, drop, wait_ms):
    """tap xy, then wait; the test switch SOA_TEST_DROP_TAP=NAME[,NAME] (control/README.md) drops the
    first tap of each step named (the forced lost tap that shows the retries work)."""
    dropped = s.__dict__.setdefault("_dropped_taps", set())
    if drop in os.environ.get("SOA_TEST_DROP_TAP", "").split(",") and drop not in dropped:
        dropped.add(drop)
        s.note("test: SOA_TEST_DROP_TAP: the tap at %s (%s) dropped" % (xy, drop))
        s.ctl("wait:%d" % wait_ms)
    else:
        s.ctl("tap:" + xy, "wait:%d" % wait_ms)


def _look(s):
    probe = s.scratch(".start-probe.png")
    if os.path.exists(probe):
        os.remove(probe)
    s.send(["shot:" + probe])
    return probe if os.path.exists(probe) else None


def open_mission_confirm(s, d=MISSION, tries=8, wait_ms=3000, tap=True, fatal=True):
    """From the party screen: tap d.open_xy (ミッション開始) and look until the confirmation is up. On
    the party screen (the tap lost) tap again; on anything else (the screen still fading) look again.
    True when it opened; else FAIL (and Abort when fatal: a 決定 tapped on the party screen hits a
    member's card)."""
    if tap:
        _tap(s, d, d.open_xy, d.drop_open, wait_ms)
    for i in range(tries):
        probe = _look(s)
        if probe and d.is_open(probe):
            return True
        if not s.alive():
            break
        if probe and d.is_from(probe):
            s.note("%s isn't up: tapping %s again (%d)" % (d.what, d.open_xy, i + 1))
            _tap(s, d, d.open_xy, d.drop_open, wait_ms)
        else:
            s.note("neither the party screen nor %s: looking again (%d)" % (d.what, i + 1))
            s.ctl("wait:2000")
    name = "%s didn't open" % d.what
    if fatal:
        s.fail(name if s.alive() else "%s (%s)" % (name, s.gone()))
    s.miss(name)
    return False


def start_mission(s, name, started, d=MISSION, secs=60, opened=False, fatal=True):
    """The party screen (or, opened, the confirmation already up) -> the confirmation (checked on a
    screenshot) -> 決定, until started() (the start's packet or log line; mission.log_more makes one
    for a log). After 決定 a look every few seconds: the confirmation still up -> 決定 again; the
    party screen back -> ミッション開始 again; a loading screen -> wait. PASS / FAIL for name (Abort
    when fatal). Returns True when started."""
    if not opened:
        open_mission_confirm(s, d)
    _tap(s, d, d.ok_xy, d.drop_ok, 1000)
    end = time.monotonic() + secs
    while True:
        if s.poll(6, started):
            s.ok(name)
            return True
        if not s.alive() or time.monotonic() > end:
            break
        probe = _look(s)
        if probe and d.is_open(probe):
            s.note("%s is still up: tapping %s again" % (d.what, d.ok_xy))
            _tap(s, d, d.ok_xy, d.drop_ok, 1000)
        elif probe and d.is_from(probe):
            s.note("back on the party screen without a start: %s again" % d.open_xy)
            if open_mission_confirm(s, d, fatal=False):
                _tap(s, d, d.ok_xy, d.drop_ok, 1000)
    why = s.gone() if not s.alive() else "not within %ds" % secs
    s.miss("%s (%s)" % (name, why))
    if fatal:
        raise Abort(name)
    return False


def log_more(path, rx):
    """A predicate for start_mission: a line matching rx in the log at path after the ones there now."""
    n = milestones.count(path, rx)
    return lambda: milestones.count(path, rx) > n


# ---- the port's shortcut into a battle (soa only: the `mission:` / `phase:` control commands and
# the port_debug phase lines; port/scripts' battle, restore, party, favor, missions sessions) -------
def phase(n):
    return r"port_debug: phase %d " % n


def port_start(s, mission):
    """`mission:M phase:0xf`: CPhase_Battle with mission M (the switch a mission's start button
    makes) -> MissionStart to the in-process server."""
    s.ctl("mission:" + mission, "phase:0xf")
    s.wait_log(phase(15), 120, name="CPhase_Battle (mission:%s phase:0xf)" % mission)


def battle_shots(s, first, last, every_ms, fmt="%d-battle", ended=r"mission_end\.msgp"):
    """A screenshot every every_ms while the party fights on its own, until the client log shows the
    battle's end (MissionEnd's body) or `last` shots were taken. Returns the next index."""
    i = first
    while not s.in_client(ended) and i < last and s.alive():
        s.ctl("wait:%d" % every_ms, s.shot_cmd(fmt % i))
        i += 1
    return i


def results_until(s, done_rx, first, last, wait_ms, fmt="%d-result", name="the result pages -> back", fatal=True, ok=ui370.RESULT_OK):
    """The Mission Result pages, each closed with OK (ui370.RESULT_OK: the spot all of them cover)
    and screenshotted (fmt None: not), until the client logs done_rx (the cursor: after the
    battle's end). Not blind: each tap is made only after a 4 s look for done_rx (a page's lost OK
    is tapped again; once the screen after them is up, no more taps). FAIL after `last` (fatal: and
    stop). Returns the next index."""
    i = first
    while s.cursor.wait(done_rx, 4, alive=s.alive) is None:
        if i >= last or not s.alive():
            if fatal:
                s.fail(name)
            s.miss(name)
            return i
        s.ctl("tap:" + ok, "wait:%d" % wait_ms, *([s.shot_cmd(fmt % i)] if fmt else []))
        i += 1
    s.ok(name)
    return i
