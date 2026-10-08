"""Session `tutorial`: the tutorial battle from a FRESH state (soa --server inproc, the 3.7.0 client):
a data dir with no save (no shared_prefs/Game.xml) and no local-server state (no server.sqlite3),
new-player mode (--new-player: the server starts without a player). Flow:
  title -> Login (error 19001) -> terms -> name entry -> CreatePlayer -> Login -> data check ->
  tutorial opening (mc00_010 ...) -> the battle tutorial ms00_001 (the NPC party) -> ... -> home
  (UpdateTutorial 7) -> the home tutorial (present box, gacha; UpdateTutorial 9)
with CCharacterObject::OnDamage traced (SOA_TRACE), then checks:
  - the server created the player (never seeded from a save);
  - every hit's damage is finite and positive; the battle ended (MissionEnd) and home was reached;
  - the milestones of tests/tutorial_milestones.txt (tools/compare_tutorial.py check port), the same
    list emulator/scripts/emulator_session.sh --new-player checks against the 3.7.0 client.
On a release package (SOA_PACKAGE_DIR, README.md "Packaging") the run gets no --new-player: a
package ships no seed save, so the server must start the fresh account by itself
(docs/server-rules.md#seed; checked: its "no seed save" line, and never "seeding from").
OUT keeps the log (fresh.log), one screenshot per round (fresh/lNNN.png), the packets
(packets-fresh/) and the server's state (server.sqlite3) for the parity report:
tools/compare_tutorial.py compare OUT EMU_OUT. (The `entry` session runs a seeded player first and
then this flow without the checks.)

Usage: port/scripts/tutorial_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SOA_PHONE (a pre-downloaded phone, its saves removed; none: the client downloads after
CreatePlayer's Login), NEWPLAYER_NAME (default Claire), TUTORIAL_STEPS (rounds, default 200), WATCH=1.
Prints "PASS: ..." or "FAIL: ..." and exits non-zero on failure.
Targets: port-inproc (the checks read the in-process server's lines)."""
import os
import re
import sqlite3
import subprocess
import sys

from .. import popups, ui370
from ..flows import launch, mission, tutorial
from ..milestones import Failed
from ..proc import REPO
from ..targets import PACKAGE_DIR
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "its checks read the in-process server's log lines (tools/compare_tutorial.py check port)"
WRAPPER = "port/scripts/tutorial_session.sh"
ONDAMAGE = "_ZN16CCharacterObject8OnDamageERKN24IAttackCollisionCallback23CallbackArgument_DamageEfb"
# the tutorial flow's screenshot names -> the files tools/compare_tutorial.py reads (tests/tutorial_milestones.txt)
SHOTS = {"05-tutorial-map": "90-mission-map", "06-companions": "93-companions", "07-home-tutorial": "95-home-tutorial",
         "08-home-tutorial-gacha": "96-home-tutorial-gacha", "09-home": "99-home"}


def options(ap):
    common.port_options(ap, extra=False)


def new_player_run(o, name="fresh", trace=True):
    env = {"SOA_TRACE": ONDAMAGE} if trace else {}
    # a package: no flag, its server has no seed save (docs/server-rules.md#seed)
    cfg = common.port_config(o, [] if PACKAGE_DIR else ["--new-player"], limit=3600, client_save=False, env=env)
    return common.port_run(o, cfg, SHOTS, name=name)


def new_player(s, player, steps, on_round=None, stop_home=True):
    """title -> Login (19001) -> terms -> the name -> CreatePlayer -> the data -> the opening scene ->
    the tutorial's rounds -> the mission-menu step -> home -> the home tutorial (UpdateTutorial 9)."""
    launch.title(s, "01-title")
    s.tap_until("TAP TO START -> Login -> error 19001 (no player)", 120, ui370.TITLE,
                lambda: s.in_packets(r"< ProtocolError .*status=19001"), every=10)
    common.settle(s, "02-terms", hold=2)
    common.tap_to_screen(s, "同意する -> the name dialog", ui370.TERMS_AGREE, "03-name")
    # The name: tap the field until the keyboard opens, type, 決定; checks CreatePlayer's name.
    try:
        s.ok(popups.name_entry(s.fifo, s.client_log, player, s.layout.shot_path("04-name-typed"), alive=s.alive)[3:])
    except Failed as e:
        s.fail("the name entry failed (%s)" % e)
    s.wait_for('the server created the player "%s"' % player, 30,
               lambda: s.in_client(r"CreatePlayer: LOCAL[0-9]* \(%s\)" % re.escape(player)))
    # Login, then the 3.7.0 client's data check (or download) before the opening scene.
    launch.data_check(s, lambda: s.in_packets(r"> MissionTalk") or s.in_client(mission.phase(3)), "the tutorial opening",
                      "00-download-dialog", "00-download-done", first_tap=None)
    # a fixed wait: the opening scene's buttons, as flows/tutorial.py entry() says
    s.ctl("wait:15000", s.shot_cmd("05-opening"))
    tutorial.auto_mode(s)
    home = lambda: s.in_client(mission.phase(4))
    tutorial.rounds(s, 4, steps, shot_fmt="l%03d", on_round=on_round, stop=home)
    if not home():
        s.wait_for("UpdateTutorial(4) (the mission-menu step)", 60, tutorial.tut(s, 4))
        tutorial.home_part(s, popups=False)
    else:
        s.wait_for("UpdateTutorial(7) (home)", 60, tutorial.tut(s, 7))


def main(o):
    player = os.environ.get("NEWPLAYER_NAME") or "Claire"
    steps = int(os.environ.get("TUTORIAL_STEPS") or 200)
    s = new_player_run(o)
    battle_shot = []

    def on_round(i, path):
        if not battle_shot and s.in_client(r"I/trace: _ZN16CCharacterObject8OnDamage"):
            battle_shot.append(path)

    def body(s):
        if os.path.exists(s.state_db):
            s.fail("the data dir %s has a server state" % s.phone)
        s.wait_for("the title (phase 1)", 300, lambda: s.in_client(mission.phase(1)))
        if s.in_client(r"seeding from"):
            s.fail("the server seeded a player from a save (not a fresh state)")
        new_player(s, player, steps, on_round)
        # the server opens its state at the first request: these lines come with Login
        if s.in_client(r"seeding from"):
            s.fail("the server seeded a player from a save (not a fresh state)")
        if PACKAGE_DIR:
            s.check("the server: no seed save, a fresh account (no --new-player)",
                    s.in_client(r"no seed save .*starting a fresh account"))

    ran = common.drive(s, body)
    s.state("fresh")
    if os.path.exists(s.state_db):
        sqlite3.connect(s.state_db).backup(sqlite3.connect(os.path.join(o.out, "server.sqlite3")))
    if not ran:
        return 1
    log = open(s.client_log, errors="replace").read()
    # every hit's damage: CCharacterObject::OnDamage's s0 (SOA_TRACE: the call's s0, inside the
    # parentheses; the s0 after "->" is the result)
    dmg = []
    for ln in log.splitlines():
        if "I/trace: _ZN16CCharacterObject8OnDamage" in ln:
            m = re.search(r"\(x0=[^)]*\)", ln)
            v = re.search(r" s0=([^ )]*)", m.group(0)) if m else None
            if v:
                dmg.append(v.group(1))
    bad = sum(1 for d in dmg if not re.match(r"^[0-9.eE+-]+$", d) or not 0 < float(d) <= 1e7)
    r = subprocess.run([sys.executable, os.path.join(REPO, "tools/compare_tutorial.py"), "check", "port", o.out, "--name", player],
                       capture_output=True, text=True)
    with open(os.path.join(o.out, "milestones.txt"), "w") as f:
        f.write(r.stdout + r.stderr)
    passed = [x for x in r.stdout.splitlines() if x.startswith("PASS  ")]
    fails = common.checks(
        ("request MissionStart" in log, "no MissionStart (the tutorial battle never started)"),
        ("request MissionEnd" in log, "no MissionEnd (the tutorial battle didn't finish)"),
        (dmg, "no damage was traced (SOA_TRACE CCharacterObject::OnDamage)"),
        (not bad, "%d hits with a non-positive or non-finite damage" % bad),
        (r.returncode == 0, "tutorial milestones: %s" % ";".join(x for x in r.stdout.splitlines() if x.startswith("FAIL  "))[:600]),
    )
    vals = [float(d) for d in dmg if re.match(r"^[0-9.eE+-]+$", d)]
    rng = "%.0f..%.0f" % (min(vals), max(vals)) if vals else "-"
    return common.verdict(s, fails, 'fresh state -> CreatePlayer "%s" -> tutorial battle ms00_001 (%d hits, damage %s) -> home '
                          "(UpdateTutorial 7) -> home tutorial (UpdateTutorial 9); %d tutorial milestones%s"
                          % (player, len(dmg), rng, len(passed), "; battle shot %s" % battle_shot[0] if battle_shot else ""))
