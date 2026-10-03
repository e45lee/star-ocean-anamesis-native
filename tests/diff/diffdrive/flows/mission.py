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
