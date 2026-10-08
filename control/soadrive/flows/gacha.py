"""The gacha from home (PLAN-consolidate's flows/gacha.py): the footer's ガチャ -> the recommended
tab's first banner -> 10連ガチャ -> 決定 -> SaleGacha -> the summon -> the results -> home. Used by
the `seeded` flow and the `gacha` shard."""
import os
import re
import time

from .. import popups as _popups, screens, ui370, waits

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
    waits.settle(s, shot, mask=waits.GACHA_MASK, hold=2)


def close_result(s, tries=8):
    """The result list: 次へ (a 10-draw's second page, the chips), then 閉じる at the same spot, each
    on a settled screen and made again while the result screen is up (a tap on it is sometimes
    dropped: tests/diff shard:gacha's 17-gacha-closed stayed on the chips page on one target in some
    runs, 2026-10-03), until it is gone."""
    probe = s.scratch("gacha-result-probe.png")
    for i in range(tries):
        waits.settle(s, secs=20)
        s.send(["shot:" + probe])
        if not (os.path.exists(probe) and _popups.is_gacha_result(probe)):
            return True
        s.ctl("tap:" + ui370.GACHA_RESULT_NEXT)
    s.miss("the gacha result didn't close")
    return False


def open_confirm(s, tries=6):
    """After a tap on 10連ガチャ: make sure the draw confirmation is up before 決定 is tapped
    (popups.gacha_confirm: 10連ガチャ again on the banner detail, 閉じる on a pick-up's character detail)."""
    if _popups.gacha_confirm(s.send, s.scratch("gacha-confirm-probe.png"), s.note, tries):
        return True
    s.miss("the draw confirmation didn't open")
    return False


def summon(s, name="the summon -> the result", shot=None, secs=150, fatal=True, loading_shot=None):
    """After the draw's answer: the loading screen (召喚中, its progress bar) -> 召喚開始 -> the
    presentation -> ALL SKIP -> the result (ガチャリザルト). Not timed: a look every 2 s, and on the
    presentation (popups.is_summon_skip) ALL SKIP, on anything else (the loading, a flash) 召喚開始,
    until the result shows (popups.is_gacha_result; a tap on the result's spots of these two hits
    nothing). Keeps the result as SHOT (and the first look, the loading screen, as LOADING_SHOT).
    PASS / FAIL name (Abort when fatal)."""
    probe = s.scratch("summon-probe.png")
    end = time.monotonic() + secs
    while True:
        s.send(["wait:2000", "shot:" + probe])
        if loading_shot and os.path.exists(probe):
            s.keep_shot(loading_shot, probe)
            loading_shot = None
        if os.path.exists(probe) and _popups.is_gacha_result(probe):
            break
        if not s.alive() or time.monotonic() > end:
            return waits.gave_up(s, name, "the gacha result within %ds" % secs, fatal)
        s.ctl("tap:" + (ui370.SUMMON_ALL_SKIP if os.path.exists(probe) and _popups.is_summon_skip(probe) else ui370.SUMMON_START))
    s.ok(name)
    return waits.settle(s, shot, hold=2)


def ten_draw(s, st_before, opened=False):
    """A 10-draw of the first recommended banner; checks the coins debited (against st_before, the
    state text before) and the ten draws recorded. opened: the gacha screen is open already."""
    if not opened:
        open_gacha(s)
    # おすすめ: the tab the screen opens on (no change to wait for), then its first banner
    waits.tap_settled(s, ui370.GACHA_TAB_RECOMMENDED, mask=waits.GACHA_MASK)
    waits.tap_to_screen(s, "the first banner", ui370.GACHA_FIRST_BANNER, "13-gacha-detail", mask=waits.GACHA_MASK)
    s.ctl("tap:" + ui370.GACHA_10)
    open_confirm(s)
    s.shot("14-gacha-confirm")
    s.tap_until("10-draw: 決定 -> SaleGacha -> SaleGachaRes", 60, ui370.GACHA_DECIDE, lambda: s.in_packets(r"< SaleGachaRes"))
    summon(s, shot="16-gacha-result", loading_shot="15-summon")
    close_result(s)
    waits.settle(s, "17-gacha-closed", mask=waits.GACHA_MASK)
    st3 = s.state("3-after-gacha")
    c2 = re.search(r" coins free (\d+) ", st_before)
    c3 = re.search(r" coins free (\d+) ", st3)
    s.check("coins debited (%s -> %s)" % (c2 and c2.group(1), c3 and c3.group(1)), bool(c2 and c3 and int(c3.group(1)) < int(c2.group(1))))
    s.check("server state: 10 draws recorded", len(re.findall(r"^  gacha ", st3, re.M)) == 10)
    waits.tap_to_screen(s, "ホーム", ui370.FOOTER_HOME, "18-home-end", mask=waits.HOME_MASK)
    return st3
