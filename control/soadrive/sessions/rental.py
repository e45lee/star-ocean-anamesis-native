"""Session `rental`: a rental helper (the in-process local server's follow / rental rules): from the
title through the real UI: home -> ミッション -> Episode 1 -> planet Mere -> the mission map -> 1-05
(mf01_001) -> single play -> the rental list -> the first rental -> the party (the rental is the 4th
card) -> start -> the battle with the helper as member 4 -> the result pages. Then (RENTAL_DAY2=1,
the default) a second boot on the same phone a day later: the rental bonus is paid at login and
its popup shown (CRentalBonus::Setup traced).

Usage: port/scripts/rental_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: CAMPAIGN_SEED (soa --campaign-seed; default mf01_001), RENTAL_CLOCK (the first day's clock,
default "2026-09-30 12:00:00"), RENTAL_DAY2 (default 1), HOME_MISSION_X (default 270), SOA_PHONE,
WATCH=1. Prints "PASS: ..." per part, or "FAIL: ..." with exit status 1.
Targets: port-inproc (the phase lines and the in-process server's lines)."""
import datetime
import os

from .. import popups
from ..flows import mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it waits on the port's phase lines and the in-process server's rental lines"
WRAPPER = "port/scripts/rental_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def episode1_map(s, x):
    """ミッション -> the episode list -> Episode 1 (the third banner: scrolled to) -> the planet select."""
    common.settle(s, mask=common.HOME_MASK)
    common.episode_list(s, "%s:1080" % x)
    common.settle(s)
    s.ctl("drag:364:850:364:400")
    common.settle(s)
    common.tap_to_phase(s, "Episode 1 -> the planet select", "364:805", 5, secs=120, fatal=True)


def main(o):
    seed = os.environ.get("CAMPAIGN_SEED") or "mf01_001"
    clock1 = os.environ.get("RENTAL_CLOCK") or "2026-09-30 12:00:00"
    x = os.environ.get("HOME_MISSION_X") or "270"
    s = common.port_run(o, common.port_config(o, ["--campaign-seed", seed, "--clock", clock1], limit=2400, seed_rng=None))

    def screen(s, name, xy, shot=None, **kw):
        return common.tap_to_screen(s, name, xy, shot, **kw)

    def day1(s):
        common.port_login(s, notice=None, bonus=None)
        episode1_map(s, x)
        screen(s, "Mere", "660:520")
        screen(s, "出撃 -> the mission map", "587:795")
        screen(s, "1-05 -> its detail", "363:665", "03-detail")
        screen(s, "シングルプレイ開始 -> the rental list", "364:905", "04-rental")
        # the first rental -> the party select (the rental is the 4th card) -> start -> confirm
        screen(s, "the first rental -> the party", "364:375", "05-party", is_screen=popups.is_party_start)
        mission.open_mission_confirm(s)
        s.ctl(s.shot_cmd("06-confirm"))
        rx = r"MissionStart: rental helper"
        mission.start_mission(s, "ミッション開始 -> 決定 (the start)", mission.log_more(s.client_log, rx), opened=True)
        s.wait_log(rx, 60, name="MissionStart with the rental helper")
        # a fixed wait: a picture of the fight, nothing to wait for (battle_shots then waits for its end)
        s.ctl("wait:15000", s.shot_cmd("07-battle"))
        mission.battle_shots(s, 8, 40, 5000, fmt="%02d-battle")
        s.wait_log(r"mission_end\.msgp", 30, name="the battle ended (MissionEnd)")
        common.settle(s, "60-result", hold=2)
        screen(s, "the result: OK", "510:1040")
        screen(s, "the result: OK", "510:1040", "61-result")
        screen(s, "the result's next page", "364:1050", "62-result-exp")

    if not common.drive(s, day1):
        return 1
    fails = common.checks(
        (s.in_client(r"MissionStart: rental helper .* as member 4"), "the rental helper didn't join the battle as member 4"),
        (s.in_client(r"MissionEnd mission [0-9]*: player exp"), "the battle didn't end (no MissionEnd)"))
    if common.verdict(s, fails, "rental helper listed, picked, fought as member 4"):
        return 1
    if os.environ.get("RENTAL_DAY2", "1") != "1":
        return 0
    # ---- day 2: the rental bonus popup ----
    clock2 = (datetime.datetime.strptime(clock1, "%Y-%m-%d %H:%M:%S") + datetime.timedelta(hours=24)).strftime("%Y-%m-%d %H:%M:%S")
    cfg = common.port_config(o, ["--campaign-seed", seed, "--clock", clock2], limit=2400, seed_rng=None,
                             env={"SOA_TRACE": "_ZN12CRentalBonus5SetupEv"})
    s2 = common.port_run_again(o, cfg, "log-day2.txt")

    def day2(s):
        common.port_login(s, "70-title", None, None, None)
        s.wait_log(r"CRentalBonus5SetupEv\(", 60, name="the rental bonus popup (CRentalBonus::Setup)")
        common.settle(s, "71-rental-bonus", hold=2)
        common.tap_to_screen(s, "the rental bonus: 閉じる", "364:810", "72-home", mask=common.HOME_MASK)

    if not common.drive(s2, day2):
        return 1
    fails = common.checks((s2.in_client(r"rental bonus: [0-9]* rentals on day"), "no rental bonus paid on day 2"))
    return common.verdict(s2, fails, "rental bonus paid the next day and its popup shown (%s)" % s2.layout.shot_path("71-rental-bonus"))
