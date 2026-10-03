"""The gacha from home (PLAN-consolidate's flows/gacha.py): the footer's ガチャ -> the recommended
tab's first banner -> 10連ガチャ -> 決定 -> SaleGacha -> the summon -> the results -> home. Used by
the `seeded` flow and the `gacha` shard."""
import re

from .. import screens, ui370

HOME = (0.08, (screens.HOME_CHARACTER,))
SCREENS = {
    "12-gacha": 0.08,
    "13-gacha-detail": (0.08, (screens.GACHA_CAROUSEL,)),
    "14-gacha-confirm": 0.08,
    "15-summon": None,
    "16-gacha-result": 0.08,
    "17-gacha-closed": (0.08, (screens.GACHA_CAROUSEL,)),
    "18-home-end": HOME,
}


def open_gacha(s, shot="12-gacha"):
    """The footer's ガチャ -> GetGachaInData -> the gacha screen."""
    s.tap_until("ガチャ -> GetGachaInData", 60, ui370.FOOTER_GACHA, lambda: s.in_packets(r"< GetGachaInDataRes"))
    s.ctl("wait:10000")
    s.shot(shot)


def ten_draw(s, st_before, opened=False):
    """A 10-draw of the first recommended banner; checks the coins debited (against st_before, the
    state text before) and the ten draws recorded. opened: the gacha screen is open already."""
    if not opened:
        open_gacha(s)
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
    c2 = re.search(r" coins free (\d+) ", st_before)
    c3 = re.search(r" coins free (\d+) ", st3)
    s.check("coins debited (%s -> %s)" % (c2 and c2.group(1), c3 and c3.group(1)), bool(c2 and c3 and int(c3.group(1)) < int(c2.group(1))))
    s.check("server state: 10 draws recorded", len(re.findall(r"^  gacha ", st3, re.M)) == 10)
    s.ctl("tap:" + ui370.FOOTER_HOME, "wait:8000")
    s.shot("18-home-end")
    return st3
