"""Flow `tutorial`: a new player (the server starts without one: --new-player; no client save) from
the title to home: Login refused with 19001 -> the terms -> the name -> CreatePlayer -> the
tutorial's scenes, its battle ms00_001, the mission-menu step, home and the home tutorial
(UpdateTutorial 9). emulator/scripts/emulator_session.sh --new-player's taps; the milestones of
tests/tutorial_milestones.txt (tools/compare_tutorial.py check) on every target."""
import os
import subprocess
import time

from .. import screens, ui370
from ..proc import REPO
from ..targets import Abort
from . import launch

NAME = "tutorial"
EST = 840
CLOCK = "2026-10-01 12:00:05"
PLAYER = "Claire"


def config(Config):
    return Config(["--new-player"], CLOCK, client_save=False, new_player=True)


# home: the still parts at the still limit, the character masked (screens.HOME_CHARACTER)
HOME = (0.08, (screens.HOME_CHARACTER,))
SCREENS = {
    "01-title": 0.08,
    "02-terms": 0.08,
    "03-name-typed": 0.08,
    "04-opening": None,
    "05-tutorial-map": 0.10,
    "06-companions": 0.08,
    "07-home-tutorial": 0.08,  # the tutorial dialog over a dimmed home
    "08-home-tutorial-gacha": 0.08,
    "08c-notice": None,
    "08d-login-bonus": 0.08,
    "09-home": HOME,
}

TUTORIAL_TAPS = ["tap:364:506", "wait:400", "tap:364:562", "wait:400", "tap:527:1090", "wait:400", "tap:527:785", "wait:400",
                 "tap:527:697", "wait:400", "tap:175:890", "wait:300", "tap:440:430", "wait:300", "tap:650:1005", "wait:300",
                 "tap:505:1075", "wait:300", "tap:450:1215"]


def tut(s, k):
    return lambda: s.in_packets(r"> UpdateTutorial .*args: %d$" % k)


def entry(s):
    """The title -> Login refused (19001) -> the terms -> the name -> CreatePlayer -> Login -> the
    data check -> the opening scene (MissionTalk); auto mode and fast-forward on."""
    launch.title(s)
    s.tap_until("TAP TO START -> Login", 120, ui370.TITLE, lambda: s.in_packets(r"> Login "))
    s.wait_for("Login -> ProtocolError 19001 (no player)", 60, lambda: s.in_packets(r"< ProtocolError .*status=19001"))
    s.ctl("wait:3000")
    s.shot("02-terms")
    # 同意する, then the name field until the client opens its keyboard (a tap during the fade is lost).
    end = time.monotonic() + 90
    while not s.in_client(r"StartKeyboardActivity\("):
        if not s.alive() or time.monotonic() > end:
            s.miss("terms -> name entry (no keyboard)")
            raise Abort("name entry")
        s.ctl("tap:" + ui370.TERMS_AGREE, "wait:2500", "tap:" + ui370.NAME_FIELD)
        s.poll(6, lambda: s.in_client(r"StartKeyboardActivity\("))
    s.ok("terms (同意する) -> name entry (keyboard)")
    # The game renders no frames while its keyboard is open (the host repaints the last one with its
    # text box); text: finishes the entry at once, then a screenshot of the filled field.
    s.send(["wait:500", "text:" + PLAYER, "wait:1500", "shot:" + os.path.join(s.shots, "03-name-typed.png")])
    s.tap_until("決定 -> CreatePlayer -> CreatePlayerRes", 60, ui370.NAME_DECIDE, lambda: s.in_packets(r"< CreatePlayerRes"))
    s.check('CreatePlayer carries "%s"' % PLAYER, s.in_packets(r'> CreatePlayer .*"%s"' % PLAYER))
    s.wait_for("Login -> LoginResult (the new player)", 60, lambda: s.in_packets(r"< LoginResult"))
    launch.data_check(s, lambda: s.in_packets(r"> MissionTalk"), "the opening scene (MissionTalk)")
    s.ctl("wait:15000")
    s.shot("04-opening", settle=False)
    auto_mode(s)


def auto_mode(s):
    """A scene's auto mode and fast-forward (the opening scene's buttons)."""
    s.ctl("tap:612:1240", "wait:1000", "tap:115:45", "wait:1000")


def rounds(s, k, limit=150, shot_fmt=None, on_round=None, stop=None):
    """Rounds of taps (one every ~9 s, paced by a screenshot) through the scenes and the battle
    until UpdateTutorial(k). shot_fmt (e.g. "tutorial-%03d"): every round's screenshot kept under
    that name (tools/compare_tutorial.py aligns them); on_round(i, path) after each shot. Returns
    the number of rounds. stop: another predicate that ends the rounds (e.g. home reached)."""
    i = 0
    while i < limit and not tut(s, k)() and not (stop and stop()):
        if not s.alive():
            s.miss("tutorial (the client exited)")
            raise Abort("tutorial")
        # (the shot paces the rounds: send() returns once it is written, after the wait)
        path = s.layout.shot_path(shot_fmt % i) if shot_fmt else s.scratch("round.png")
        if on_round:
            s.send(["wait:6000", "shot:" + path])
            on_round(i, path)
            s.send(TUTORIAL_TAPS)
        else:
            s.send(["wait:6000", "shot:" + path] + TUTORIAL_TAPS)
        i += 1
    return i


def home_part(s, popups=True, home_wait=3000):
    """From the mission-menu step (UpdateTutorial 4): planet Mere's map, 1-01 (ここをタップ) ->
    ストーリー開始 -> the story, skipped -> UpdateTutorial(6) -> "summoned companions" 次へ -> ホーム
    -> the home tutorial -> UpdateTutorial(9) -> the notice board and the LOGIN BONUS (popups=False:
    left open, as the sessions' home shot always showed the board) -> home."""
    s.ctl("wait:10000")
    s.shot("05-tutorial-map")
    s.ctl("tap:360:640", "wait:3000", "tap:515:714")
    s.wait_for("1-01's story starts (MissionTalk mc01_010)", 90, lambda: s.in_packets(r"> MissionTalk .* 3991905094 "))
    # スキップ, then はい, until the story ends: either tap is lost while its dialog fades in (seen
    # under load: the skip dialog open, はい never tapped), so the pair is repeated.
    s.ctl("wait:12000")
    end = time.monotonic() + 120
    while not s.in_packets(r"> EndMissionTalk .* 3991905094 ") and s.alive() and time.monotonic() < end:
        s.ctl("tap:" + ui370.STORY_SKIP, "wait:2500", "tap:" + ui370.STORY_SKIP_YES)
        s.poll(8, lambda: s.in_packets(r"> EndMissionTalk .* 3991905094 "))
    s.wait_for("UpdateTutorial(6) (the story of 1-01)", 120, tut(s, 6))
    s.ctl("wait:8000")
    s.shot("06-companions")
    s.ctl("tap:527:1090", "wait:3000", "tap:60:1240")
    s.wait_for("UpdateTutorial(7) (home)", 120, tut(s, 7))
    # The home tutorial: the present box (次へ), the gacha button (閉じる) -> UpdateTutorial(9).
    s.ctl("wait:8000")
    s.shot("07-home-tutorial", settle=False)
    s.ctl("tap:525:1085", "wait:3000")
    s.shot("08-home-tutorial-gacha", settle=False)
    s.ctl("tap:525:1090")
    s.wait_for("UpdateTutorial(9) (the tutorial cleared)", 90, tut(s, 9))
    # The notice board (its page text only in-process: the port's web-view stand-in,
    # docs/client-changes.md, hence "info") and the LOGIN BONUS, then home.
    if popups:
        launch.popups(s, "08c-notice", "08d-login-bonus")
    s.ctl("wait:%d" % home_wait)
    s.shot("09-home")


def run(s):
    entry(s)
    # Rounds of taps until the mission-menu step (UpdateTutorial 4).
    rounds(s, 4)
    for k in (1, 2, 3):
        s.check("UpdateTutorial(%d)" % k, tut(s, k)())
    s.check("battle tutorial: MissionStart -> MissionStartRes", s.in_packets(r"< MissionStartRes"))
    s.check("battle tutorial: MissionEnd -> MissionEndRes", s.in_packets(r"< MissionEndRes"))
    s.wait_for("UpdateTutorial(4) (the mission menu)", 30, tut(s, 4))
    home_part(s)
    st = s.state("newplayer")
    s.check('server state: the new player "%s"' % PLAYER, ("(%s," % PLAYER) in st)
    s.check("no communication-error ProtocolError", not s.in_packets(r"< ProtocolError .*status=1[0-9]{3}\b"))
    # tests/tutorial_milestones.txt: the requests in order and the battle party's stats (the
    # MissionEnd battle log in packets/; every target writes it).
    r = subprocess.run(["python3", os.path.join(REPO, "tools/compare_tutorial.py"), "check", "emu", s.dir, "--name", PLAYER],
                       capture_output=True, text=True)
    with open(os.path.join(s.dir, "tutorial-milestones.txt"), "w") as f:
        f.write(r.stdout + r.stderr)
    fails = [x for x in r.stdout.splitlines() if x.startswith("FAIL  ")]
    s.check("tutorial milestones (tests/tutorial_milestones.txt)%s" % ("" if not fails else ": " + "; ".join(fails[:3])),
            r.returncode == 0)
