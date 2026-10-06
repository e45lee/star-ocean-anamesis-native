"""Session `campaign`: the original (3.7.0) story campaign, restored (the in-process local server):
from the title, through the real UI, into Episode 1, the planet select, the mission map, a battle
mission and the story after it.

  title -> home -> Mission (episode list, CPhase_SelectPart) -> Episode 1 -> CPhase_Mission
  (planet select) -> planet Mere -> mission map -> 1-05 (mf01_001) -> single play -> no rental
  -> party 1 -> mission start -> battle (MissionStart / MissionEnd answered by the local server)
  -> result -> back on the mission map: 1-05 CLEAR, the next story mission (mc01_030) unlocked
  -> its story scene (MissionTalk) -> the mission after it (ms01_002) unlocked.

The player is a returning one: --campaign-seed mf01_001 counts every mission on the unlock chain
before 1-05 as cleared, and the one-time menu tutorials as seen. Every step waits for its screen or
log line, then screenshots (<out>/shots).

Usage: port/scripts/campaign_session.sh <soa> <out-dir> <scratch-dir> [soa flags...]   (from any directory;
e.g. `--lang en` for the English story, PLAN-english C4)
Env: CAMPAIGN_SEED (soa --campaign-seed; default mf01_001); CAMPAIGN_MASTER_DB (soa
--campaign-master-db; default the server's); HOME_MISSION_X (default 270); SOA_PHONE; WATCH=1.
Targets: port-inproc (the phase lines and the in-process server's campaign lines)."""
import os
import re

from ..flows import mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it waits on the port's phase lines and the in-process server's campaign lines"
WRAPPER = "port/scripts/campaign_session.sh"


def options(ap):
    common.port_options(ap)


def main(o):
    seed = os.environ.get("CAMPAIGN_SEED") or "mf01_001"
    args = ["--campaign-seed", seed]
    if os.environ.get("CAMPAIGN_MASTER_DB"):
        args += ["--campaign-master-db", os.environ["CAMPAIGN_MASTER_DB"]]
    s = common.port_run(o, common.port_config(o, args, limit=2400, seed_rng=None))
    x = os.environ.get("HOME_MISSION_X") or "270"

    def body(s):
        common.port_login(s)
        # ミッション -> the episode list; Episode 1 is the third banner (scroll down first).
        s.ctl("wait:500")
        common.episode_list(s, "%s:1085" % x)
        s.ctl("wait:5000", "drag:364:850:364:400", "wait:2000", s.shot_cmd("03-episodes"))
        s.tap_log(mission.phase(5), 120, 20, 3, "tap:364:805", name="Episode 1 -> the planet select")
        s.ctl("wait:8000", s.shot_cmd("04-planets"))
        # The next planet (Mere), then Start: its mission map.
        s.ctl("tap:660:520", "wait:3000", s.shot_cmd("05-planet-mere"))
        s.ctl("tap:587:795", "wait:7000", s.shot_cmd("06-mission-map"))
        # 1-05 (mf01_001, "New") -> detail -> single play -> no rental -> party 1 -> start -> confirm.
        s.ctl("tap:363:665", "wait:4000", s.shot_cmd("07-mission-detail"))
        s.ctl("tap:364:905", "wait:5000", s.shot_cmd("08-rental"))
        s.ctl("tap:620:1120", "wait:5000", s.shot_cmd("09-party"))
        mission.open_mission_confirm(s)
        s.ctl(s.shot_cmd("10-confirm"))
        mission.start_mission(s, "ミッション開始 -> 決定 (the start)", mission.log_more(s.client_log, mission.phase(15)), secs=120, opened=True)
        s.wait_log(mission.phase(15), 120, name="決定 -> CPhase_Battle")
        s.wait_log(r"campaign: MissionStart", 60, name="campaign: MissionStart")
        s.ctl("wait:15000", s.shot_cmd("11-battle"))
        mission.battle_shots(s, 12, 60, 5000)
        s.wait_log(r"campaign: cleared mf01_001", 30, name="campaign: cleared mf01_001")
        s.ctl("wait:4000", s.shot_cmd("60-result"))
        # The result pages (OK at the same spot) until the game is back on the mission map (phase 5).
        mission.results_until(s, mission.phase(5), 61, 75, 4000, name="the result pages -> the mission map")
        s.ctl("wait:8000", s.shot_cmd("80-map-after-clear"))
        # The story mission that 1-05 unlocked (mc01_030, "New" above 1-05) -> detail -> play.
        s.ctl("tap:490:530", "wait:4000", s.shot_cmd("81-story-detail"))
        s.ctl("tap:515:720", "wait:10000", s.shot_cmd("82-story"))  # ストーリー開始
        # A few lines of the scene, then スキップ -> はい; the scene's end sends MissionTalk.
        for i in (83, 84, 85):
            s.ctl("tap:364:1000", "wait:3000", s.shot_cmd("%d-story" % i))
        s.ctl("tap:115:1240", "wait:2000", s.shot_cmd("86-skip"), "tap:515:742")
        s.wait_log(r"campaign: story scene played: mc01_030", 90, name="campaign: story scene played: mc01_030")
        s.ctl("wait:8000", s.shot_cmd("96-after-story"), "wait:6000", s.shot_cmd("97-map"))

    ok = common.drive(s, body)
    for ln in open(s.client_log, errors="replace").read().splitlines():
        if re.search(r"restore:|campaign:", ln):
            print("  " + ln)
    if not ok:
        return 1
    fails = common.checks(
        (s.in_client(r"campaign: cleared %s" % re.escape(seed)), "%s wasn't cleared" % seed),
        (s.in_client(r"campaign: story scene played: mc01_030"), "the story scene mc01_030 wasn't recorded"))
    return common.verdict(s, fails, "episode 1 -> %s cleared -> mc01_030 played" % seed)
