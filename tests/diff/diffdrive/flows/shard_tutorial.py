"""The tutorial shards: the `tutorial` flow in stages, each from the server state the full flow has
at the stage's start (diffdrive/prepared.py: the `tutorial` replay corpus cut after its
UpdateTutorial(N), replayed by soa-server). The 3.7.0 client resumes the tutorial from the
server's Player.tutorial_status at Login (seen on every target, 2026-10-03): status 1 -> the second
scene (MissionTalk mc00_015), 2 -> the battle tutorial (MissionStart ms00_001), 3 -> the third
scene, 4 -> the mission-menu step (the planet select with its 出撃 hint).

  tutorial-entry   a new player (no state): title, 19001, terms, name, CreatePlayer, the opening
                   scene -> UpdateTutorial(1)
  tutorial-scene   from status 1: the second scene -> UpdateTutorial(2) -> MissionStart
  tutorial-battle  from status 2: the battle tutorial (the NPC party, MissionEnd) -> UpdateTutorial(3)
  tutorial-home    from status 3: the third scene -> UpdateTutorial(4), the mission menu, 1-01's
                   story, home, the home tutorial -> UpdateTutorial(9), the login popups

Each checks its slice of tests/tutorial_milestones.txt (the requests in order; the battle's party
stats) and is compared like any flow (packets, server state, screens). A stage ends once the requests that follow its last UpdateTutorial have stopped
(quiet()), so the packet logs end at the same point on every target.
"""
import os
import sqlite3
import sys
import time

from .. import prepared, screens, ui370
from ..proc import REPO
from . import launch, tutorial

sys.path.insert(0, os.path.join(REPO, "tools"))
import compare_tutorial  # noqa: E402  (tools/compare_tutorial.py: the milestone list and checks)

# After the corpus's requests (12:00-12:18 of the recording day): the server clock starts later.
CLOCK = "2026-10-01 12:30:05"


def quiet(s, secs=10, limit=90):
    """Waits until the packet log hasn't grown for `secs` s (the burst of requests after a step)."""
    last, since, end = -1, time.monotonic(), time.monotonic() + limit
    while time.monotonic() < end and s.alive():
        n = os.path.getsize(s.packets) if os.path.exists(s.packets) else 0
        if n != last:
            last, since = n, time.monotonic()
        elif time.monotonic() - since >= secs:
            return True
        time.sleep(1)
    return False


def milestones(s, first, last, party=False):
    """The milestone list's requests from `first` to `last` (inclusive; as the list writes them),
    in order in this run's packet log; with party=True also the battle party's stats."""
    want, members, _ = compare_tutorial.load_spec(tutorial.PLAYER)
    want = want[want.index(first):want.index(last) + 1]
    have = compare_tutorial.emu_requests(s.packets) if os.path.exists(s.packets) else []
    for w, ok in compare_tutorial.check_order(have, want):
        s.check("milestone: " + w, ok)
    if party:
        got = compare_tutorial.emu_party(s.dir)
        for p in members:
            s.check("battle party member %s" % " ".join("%g" % x for x in p), p in got)
        s.check("battle party: no other members", not (got - set(members)))


class Stage:
    """A shard module: NAME, EST, config, SCREENS, prepare, run (difftest.FLOWS)."""

    def __init__(self, name, est, status, screens, body, doc):
        self.NAME, self.EST, self.status, self.SCREENS, self.body, self.__doc__ = name, est, status, screens, body, doc

    def config(self, Config):
        return Config(["--new-player"], CLOCK if self.status else tutorial.CLOCK, new_player=True)

    def prepare(self, pdir, server_bin):
        if not self.status:
            return None
        return prepared.state("tutorial", prepared.cut_after("tutorial", "UpdateTutorial", arg=str(self.status)), pdir, server_bin)

    def run(self, s):
        self.body(s)
        s.check("no communication-error ProtocolError", not s.in_packets(r"< ProtocolError .*status=1[0-9]{3}\b"))


def resume(s, until, name):
    """A player in the tutorial logs in: the title, TAP TO START, Login, the data check, and the
    client's first tutorial request (`until`)."""
    launch.title(s)
    s.tap_until("TAP TO START -> Login", 120, ui370.TITLE, lambda: s.in_packets(r"> Login "))
    s.wait_for("Login -> LoginResult (a player in the tutorial)", 60, lambda: s.in_packets(r"< LoginResult"))
    launch.data_check(s, lambda: s.in_packets(until), name)


def entry(s):
    tutorial.entry(s)
    tutorial.rounds(s, 1)
    s.wait_for("UpdateTutorial(1) (the opening scene)", 30, tutorial.tut(s, 1))
    quiet(s)
    s.shot("10-stage-end", settle=False)
    milestones(s, "NoLoginStart", "UpdateTutorial 1")
    s.check("server state: tutorial_status 1", tutorial_status(s) == "1")
    st = s.state("newplayer")
    s.check('server state: the new player "%s"' % tutorial.PLAYER, ("(%s," % tutorial.PLAYER) in st)


def scene(s):
    resume(s, r"> MissionTalk", "the second scene (MissionTalk mc00_015)")
    s.ctl("wait:15000")
    s.shot("04-scene", settle=False)
    tutorial.auto_mode(s)
    tutorial.rounds(s, 2)
    s.wait_for("UpdateTutorial(2) (the second scene)", 30, tutorial.tut(s, 2))
    s.wait_for("the battle tutorial starts (MissionStart -> MissionStartRes)", 60, lambda: s.in_packets(r"< MissionStartRes"))
    quiet(s)
    s.shot("10-stage-end", settle=False)
    milestones(s, "MissionTalk 0 2699394681 0 0", "MissionStart 0 3645708271 1 0 0 0 0")
    s.check("server state: tutorial_status 2", tutorial_status(s) == "2")


def battle(s):
    resume(s, r"> MissionStart", "the battle tutorial (MissionStart ms00_001)")
    s.wait_for("MissionStart -> MissionStartRes", 60, lambda: s.in_packets(r"< MissionStartRes"))
    s.ctl("wait:15000")
    s.shot("04-battle", settle=False)
    tutorial.rounds(s, 3)
    s.wait_for("UpdateTutorial(3) (the battle tutorial won)", 30, tutorial.tut(s, 3))
    quiet(s)
    s.shot("10-stage-end", settle=False)
    milestones(s, "MissionStart 0 3645708271 1 0 0 0 0", "MissionTalk 0 2345151930 0 0", party=True)
    s.check("server state: tutorial_status 3", tutorial_status(s) == "3")


def home(s):
    # From status 3 (the third scene), not 4: resumed at status 4 the client shows the planet
    # select with its 出撃 hint but 出撃 does nothing (the planet's name is missing: "ess.png"; seen
    # on all three targets, 2026-10-03), while coming from the scene it works as in the full flow.
    resume(s, r"> MissionTalk", "the third scene (MissionTalk mc00_025)")
    s.ctl("wait:15000")
    s.shot("04-scene", settle=False)
    tutorial.auto_mode(s)
    tutorial.rounds(s, 4)
    s.wait_for("UpdateTutorial(4) (the mission menu)", 30, tutorial.tut(s, 4))
    # The full flow's tap rounds pass the planet select (the planet, then 出撃) on their way: the
    # same rounds until Mere's map (bright land, where the planet select is space).
    probe = s.scratch("sortie.png")
    for i in range(4):
        s.send(["wait:6000", "shot:" + probe])
        if (screens.mean(probe, "729x300+0+200") or 0) > 0.2:
            break
        s.send(tutorial.TUTORIAL_TAPS)
    s.check("the tap rounds -> Mere's mission map", (screens.mean(probe, "729x300+0+200") or 0) > 0.2)
    tutorial.home_part(s)
    milestones(s, "MissionTalk 0 2345151930 0 0", "UpdateTutorial 9")
    s.check("server state: tutorial_status 9", tutorial_status(s) == "9")


def tutorial_status(s):
    try:
        c = sqlite3.connect("file:%s?mode=ro" % s.state_db, uri=True)
        r = c.execute("select tutorial_status from player").fetchone()  # PLAN-schema S3 (meta before)
        c.close()
        return str(r[0]) if r else None
    except sqlite3.Error:
        return None


STAGE_END = {"10-stage-end": None}
ENTRY = Stage("tutorial-entry", 180, 0,
              {"01-title": 0.08, "02-terms": 0.08, "03-name-typed": 0.08, "04-opening": None, **STAGE_END}, entry,
              "a new player: the title, 19001, the terms, the name, CreatePlayer, the opening scene -> UpdateTutorial(1)")
SCENE = Stage("tutorial-scene", 270, 1, {"01-title": 0.08, "04-scene": None, **STAGE_END}, scene,
              "from tutorial_status 1: the second scene -> UpdateTutorial(2) -> MissionStart")
BATTLE = Stage("tutorial-battle", 330, 2, {"01-title": 0.08, "04-battle": None, **STAGE_END}, battle,
               "from tutorial_status 2: the battle tutorial ms00_001 (the NPC party) -> UpdateTutorial(3)")
HOME = Stage("tutorial-home", 340, 3,
             {"01-title": 0.08, "04-scene": None, **{k: v for k, v in tutorial.SCREENS.items() if k[:2] in ("05", "06", "07", "08", "09")}},
             home, "from tutorial_status 3: the third scene, the mission menu, 1-01's story, home, the home tutorial -> UpdateTutorial(9)")
STAGES = (ENTRY, SCENE, BATTLE, HOME)
