"""Missions from home (PLAN-consolidate's flows/mission.py): the campaign's 1-05 (mf01_001, open with
soa-server --campaign-seed mf01_001) through the mission map, its battle and result pages, back
home. Used by the `seeded` flow and the `battle` shard."""
import re

from .. import screens, ui370

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
    s.ctl("tap:" + ui370.PARTY_START, "wait:3000")
    s.shot("07-start-confirm")
    s.tap_until("1-05 -> MissionStart -> MissionStartRes", 60, ui370.CONFIRM_OK, lambda: s.in_packets(r"< MissionStartRes"))
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


def results_until(s, done_rx, first, last, wait_ms, fmt="%d-result", name="the result pages -> back", fatal=True):
    """The Mission Result pages, each closed with OK (ui370.RESULT_OK: the spot all of them cover)
    and screenshotted (fmt None: not), until the client logs done_rx (the cursor: after the
    battle's end). FAIL after `last` (fatal: and stop). Returns the next index."""
    i = first
    while s.cursor.wait(done_rx, 4, alive=s.alive) is None:
        if i >= last or not s.alive():
            if fatal:
                s.fail(name)
            s.miss(name)
            return i
        s.ctl("tap:" + ui370.RESULT_OK, "wait:%d" % wait_ms, *([s.shot_cmd(fmt % i)] if fmt else []))
        i += 1
    s.ok(name)
    return i
