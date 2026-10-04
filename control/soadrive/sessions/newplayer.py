"""Session `newplayer`: a new player on the 3.7.0 client against a server started without one
(--new-player): emulator/scripts/emulator_session.sh --new-player.

Usage: emulator/scripts/emulator_session.sh --new-player [soa-emu] [soa-server] [out dir]
Env: as the `seeded` session (EMU_DATA, SOA_PHONE, NO_RETRY, FRESH_KVS, SERVER_ARGS, KEEP_DATA),
plus NEWPLAYER_NAME (default Claire) and NEWPLAYER_STEPS (the tutorial's rounds, default 150).
The milestones: NoLoginStart; the wire (StartBridge, the bridge POST, UpdateSession); Login ->
ProtocolError 19001 (no player); terms (同意する) -> the name (the keyboard) -> 決定 -> CreatePlayer
(carrying the name) -> Login with the CDN keys; the data check or the download; the opening scene
(MissionTalk); the tutorial: rounds of taps through the scenes and the battle tutorial ms00_001
(UpdateTutorial 1-3, MissionStart / MissionEnd), the mission-menu step (UpdateTutorial 4-6), home
(7) and the home tutorial (9); the new player in the server's state; the milestones of
tests/tutorial_milestones.txt (tools/compare_tutorial.py check emu OUT -> OUT/milestones.txt).
On a release package (SOA_PACKAGE_DIR, README.md "Packaging") the server gets no --new-player: a
package ships no seed save, so it must start the fresh account by itself (docs/server-rules.md#seed;
checked: its "no seed save" line).
Every hit's damage is traced (SOA_TRACE on CCharacterObject::OnDamage) and a screenshot is kept per
round (OUT/tutorial-NNN.png) for tools/compare_tutorial.py compare.
Targets: emu (default), port-server, port-inproc."""
import os
import re
import subprocess
import sys
import time

from .. import ui370
from ..flows import launch, tutorial
from ..proc import REPO
from ..targets import PACKAGE_DIR, Abort
from . import common, seeded

TARGETS = ("emu", "port-server", "port-inproc")
WRAPPER = "emulator/scripts/emulator_session.sh --new-player"
ONDAMAGE = "_ZN16CCharacterObject8OnDamageERKN24IAttackCollisionCallback23CallbackArgument_DamageEfb"

SHOTS = {"05-tutorial-map": "tutorial-map", "06-companions": "tutorial-companions", "07-home-tutorial": "home-tutorial",
         "08-home-tutorial-gacha": "home-tutorial-gacha", "09-home": "home"}

options = seeded.emu_options


def body(s, name):
    s.predownloaded = seeded.data_on_phone(s)
    launch.title(s, "title", retry=not common.env_on("NO_RETRY"))
    seeded.wire_login(s)
    s.wait_for("Login -> ProtocolError 19001 (no player)", 60, lambda: s.in_packets(r"< ProtocolError .*status=19001"))
    s.ctl("wait:3000", s.shot_cmd("terms"))
    # The terms dialog's 同意する, then the name dialog's field until the client opens its keyboard
    # (the dialog fades in; a tap during the fade is dropped).
    end = time.monotonic() + 90
    while not s.in_client(r"StartKeyboardActivity\("):
        if not s.alive():
            s.fail("name entry (the client exited)")
        if time.monotonic() > end:
            s.fail("terms -> name entry (no keyboard within 90s)")
        s.ctl("tap:" + ui370.TERMS_AGREE, "wait:2500", "tap:" + ui370.NAME_FIELD)
        s.poll(6, lambda: s.in_client(r"StartKeyboardActivity\("))
    s.ok("terms (同意する) -> name entry (keyboard)")
    # The game renders no frames while its keyboard is open (the host repaints the last one with its
    # text box); text: finishes the entry at once, then a screenshot of the filled field.
    s.ctl("wait:500", "text:" + name, "wait:1500", s.shot_cmd("name-typed"))
    s.tap_until("決定 -> CreatePlayer -> CreatePlayerRes", 60, ui370.NAME_DECIDE, lambda: s.in_packets(r"< CreatePlayerRes"))
    s.check('CreatePlayer carries the name "%s"' % name, s.in_packets(r'> CreatePlayer .*"%s"' % re.escape(name)))
    s.wait_for("Login -> LoginResult (the new player, the CDN keys)", 60, lambda: s.in_packets(r"< LoginResult .*AssetPath"))
    launch.data_check(s, lambda: s.in_packets(r"> MissionTalk"), "the opening scene (MissionTalk)", "download-dialog",
                      "download-done", first_tap=None)
    # Auto mode and fast-forward, then rounds of taps (flows/tutorial.py) until the mission-menu step.
    s.ctl("wait:15000", s.shot_cmd("opening"))
    tutorial.auto_mode(s)
    tutorial.rounds(s, 4, int(os.environ.get("NEWPLAYER_STEPS") or 150), shot_fmt="tutorial-%03d")
    for k in (1, 2, 3):
        s.check("UpdateTutorial(%d)" % k, tutorial.tut(s, k)())
    s.check("battle tutorial: MissionStart -> MissionStartRes", s.in_packets(r"< MissionStartRes"))
    s.check("battle tutorial: MissionEnd (battle log) -> MissionEndRes", s.in_packets(r"< MissionEndRes"))
    s.wait_for("UpdateTutorial(4) (the mission menu)", 30, tutorial.tut(s, 4))
    tutorial.home_part(s, popups=False, home_wait=8000)
    if PACKAGE_DIR:
        s.check("the server: no seed save, a fresh account (no --new-player)",
                s.in_server(r"no seed save .*starting a fresh account") and not s.in_server(r"seeding from"))
    st = s.state("newplayer")
    s.check('server state: the new player "%s"' % name, re.search(r"^player LOCAL[0-9]* \(%s," % re.escape(name), st, re.M))
    if s.in_packets(r"< ProtocolError .*status=1[0-9][0-9][0-9] "):
        s.miss("a communication-error ProtocolError (packet log)")
    # The shared milestone list (tests/tutorial_milestones.txt; the port's tutorial_session.sh checks
    # the same): the requests in order and the battle party's stats (the MissionEnd battle log).
    r = subprocess.run([sys.executable, os.path.join(REPO, "tools/compare_tutorial.py"), "check", "emu", s.dir, "--name", name],
                       capture_output=True, text=True)
    with open(os.path.join(s.dir, "milestones.txt"), "w") as f:
        f.write(r.stdout + r.stderr)
    lines = (r.stdout + r.stderr).splitlines()
    if r.returncode == 0:
        s.ok("tutorial milestones (%d of tests/tutorial_milestones.txt)" % sum(1 for x in lines if x.startswith("PASS  ")))
    else:
        s.miss("tutorial milestones: %s" % ";".join(x for x in lines if x.startswith("FAIL  "))[:3 * 200])


def main(o):
    name = os.environ.get("NEWPLAYER_NAME") or "Claire"
    try:
        # a package: no flag, its server has no seed save (docs/server-rules.md#seed)
        s = seeded.emu_run(o, [] if PACKAGE_DIR else ["--new-player"], env={"SOA_TRACE": ONDAMAGE}, shots=SHOTS)
    except Abort:
        return 1
    common.drive(s, lambda s: body(s, name))
    return seeded.finish(s)
