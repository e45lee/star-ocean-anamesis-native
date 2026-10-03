"""Flow `seeded`: the seeded player (LOCAL00001, data/saves/seed/Game.xml) logs in, the popups, the
campaign's 1-05 (mf01_001: soa-server --campaign-seed mf01_001) through the mission map and its
battle, a 10-draw of the first recommended banner, home. emulator/scripts/emulator_session.sh's
seeded run, on every target."""
import re

from .. import screens, ui370
from . import launch

NAME = "seeded"
CLOCK = "2026-10-01 12:00:05"


def config(Config):
    return Config(["--campaign-seed", "mf01_001"], CLOCK)


# The screens compared between the targets: the RMSE limit against the emulator's (None: shown in
# the report, not gated). The home screens animate (the character's idle motion, the mascot's
# line): 0.12, as the smoke test's home limit.
# home: the still parts at the still limit, the character masked (screens.HOME_CHARACTER)
HOME = (0.08, (screens.HOME_CHARACTER,))
SCREENS = {
    "01-title": 0.08,
    "02a-notice": None,
    "02b-login-bonus": 0.08,
    "02-home": HOME,
    "03-planets": 0.08,
    "04-mission-map": 0.08,
    "05-mission-detail": 0.08,
    "06-party": 0.08,
    "07-start-confirm": 0.08,
    "08-battle": None,
    "09-result": None,
    "10-map-after-clear": 0.08,
    "11-home-after-battle": HOME,
    "12-gacha": 0.08,
    "13-gacha-detail": (0.08, (screens.GACHA_CAROUSEL,)),
    "14-gacha-confirm": 0.08,
    "15-summon": None,
    "16-gacha-result": 0.08,
    "17-gacha-closed": (0.08, (screens.GACHA_CAROUSEL,)),
    "18-home-end": HOME,
}


def run(s):
    launch.title(s)
    launch.login_to_home(s)
    s.state("1-home")

    # ミッション -> the planet select (or the map of the planet last played) -> Mere -> 出撃 -> 1-05.
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

    # The footer's ガチャ -> the recommended tab's first banner -> 10連ガチャ -> 決定 -> SaleGacha.
    s.tap_until("ガチャ -> GetGachaInData", 60, ui370.FOOTER_GACHA, lambda: s.in_packets(r"< GetGachaInDataRes"))
    s.ctl("wait:10000")
    s.shot("12-gacha")
    s.ctl("tap:" + ui370.GACHA_TAB_RECOMMENDED, "wait:3000", "tap:" + ui370.GACHA_FIRST_BANNER, "wait:4000")
    s.shot("13-gacha-detail")
    s.ctl("tap:" + ui370.GACHA_10, "wait:2500")
    s.shot("14-gacha-confirm")
    s.tap_until("10-draw: 決定 -> SaleGacha -> SaleGachaRes", 60, ui370.GACHA_DECIDE, lambda: s.in_packets(r"< SaleGachaRes"))
    s.ctl("wait:6000")
    s.shot("15-summon", settle=False)
    s.ctl("tap:" + ui370.SUMMON_START, "wait:12000", "tap:" + ui370.SUMMON_REVEAL, "wait:4000", "tap:" + ui370.SUMMON_REVEAL,
          "wait:4000", "tap:" + ui370.SUMMON_ALL_SKIP, "wait:5000")
    s.shot("16-gacha-result")
    s.ctl("tap:" + ui370.GACHA_RESULT_NEXT, "wait:4000", "tap:" + ui370.GACHA_RESULT_NEXT, "wait:3000")
    s.shot("17-gacha-closed")
    st3 = s.state("3-after-gacha")
    c2 = re.search(r" coins free (\d+) ", st)
    c3 = re.search(r" coins free (\d+) ", st3)
    s.check("coins debited (%s -> %s)" % (c2 and c2.group(1), c3 and c3.group(1)), bool(c2 and c3 and int(c3.group(1)) < int(c2.group(1))))
    s.check("server state: 10 draws recorded", len(re.findall(r"^  gacha ", st3, re.M)) == 10)
    s.ctl("tap:" + ui370.FOOTER_HOME, "wait:8000")
    s.shot("18-home-end")
    s.check("no ProtocolError in the packet log", not s.in_packets(r"< ProtocolError"))
