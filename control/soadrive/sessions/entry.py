"""Session `entry`: the restored entry flow (the in-process local server; docs/client-changes.md
"Entry flow", docs/server-rules.md#entry), in two boots:
  1. the seeded player (the committed client save): title -> Login -> data check -> the notice
     board and the LOGIN BONUS -> home;
  2. a new player (--new-player, no save): title -> Login (error 19001) -> terms -> name entry ->
     CreatePlayer -> Login -> data check -> the tutorial (the opening scene in auto mode with its
     choices, the battle tutorial ms00_001, the mission-menu step: 1-01's story, the companions,
     home) -> the home tutorial (present box, gacha) until UpdateTutorial(9).
Prints PASS / FAIL (the home tutorial finished) and exits non-zero on FAIL. Screenshots go to
OUT/seeded and OUT/newplayer, logs to OUT/seeded.log and OUT/newplayer.log, the server state to
OUT/state-*.txt.

Usage: port/scripts/newplayer_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SOA_PHONE (scripts/shared-phone.sh; none: the client downloads its data after each Login:
session:newplayer-download), NEWPLAYER_NAME (default Claire), NEWPLAYER_STEPS (rounds, default
200), WATCH=1.
Targets: port-inproc (the in-process server's lines)."""
import os
import re

from ..flows import mission
from . import common, tutorial

TARGETS = ("port-inproc",)
TARGETS_WHY = "its checks read the in-process server's log lines"
WRAPPER = "port/scripts/newplayer_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def main(o):
    player = os.environ.get("NEWPLAYER_NAME") or "Claire"
    steps = int(os.environ.get("NEWPLAYER_STEPS") or 200)
    # ---- 1. the seeded player ----
    seeded = common.port_run(o, common.port_config(o, limit=3600), name="seeded")

    def seeded_body(s):
        common.port_login(s, "01-title", "02-notice", "02-login-bonus", "03-home")
        s.state("seeded")

    common.drive(seeded, seeded_body)
    # ---- 2. the new player ----
    s = tutorial.new_player_run(o, "newplayer", trace=False)
    common.drive(s, lambda s: tutorial.new_player(s, player, steps))
    s.state("newplayer")
    log = open(s.client_log, errors="replace").read() if os.path.exists(s.client_log) else ""
    for ln in log.splitlines():
        if re.search(r"port_debug: phase|request (Login|CreatePlayer|UpdateTutorial|MissionTalk|MissionStart|MissionEnd)", ln):
            print(ln)
    fails = common.checks(
        (seeded.in_client(mission.phase(4)), "the seeded player never reached home"),
        (re.search(r"CreatePlayer: LOCAL[0-9]* \(%s\)" % re.escape(player), log), 'the server didn\'t create the player "%s"' % player),
        (s.in_client(mission.phase(4)), "the new player never reached home"),
        (re.search(r"request UpdateTutorial \(fid [0-9a-f]*\): 7$", log, re.M), "no UpdateTutorial(7): the tutorial didn't finish"),
        (re.search(r"request UpdateTutorial \(fid [0-9a-f]*\): 9$", log, re.M), "the home tutorial didn't finish (no UpdateTutorial 9)"),
    )
    if seeded.failed:
        fails.insert(0, "the seeded player's login")
    return common.verdict(s, fails, 'seeded player -> home; new player "%s" -> CreatePlayer -> tutorial -> home (UpdateTutorial 7) '
                          "-> home tutorial (UpdateTutorial 9)" % player)
