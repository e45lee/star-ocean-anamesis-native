"""Session `seeded`: the end-to-end session of the 3.7.0 client against a server, the seeded player
(LOCAL00001; the server's --campaign-seed mf01_001, so that the campaign's 1-05 is open on the
mission map): emulator/scripts/emulator_session.sh (emulator/README.md "Networking", "Checks").

Usage: emulator/scripts/emulator_session.sh [soa-emu] [soa-server] [out dir]
  (--new-player: the `newplayer` session.) Defaults: build/emulator/soa-emu; build/server/soa-server;
  a fresh mktemp dir (kept: logs, screenshots, the packet log, the server's state dumps; the phone's
  data is deleted at the end unless KEEP_DATA=1). The client binary may be soa (soa --server: the
  port's client on the wire; port/scripts/rebase_server_diff.sh does that).
Env:
  EMU_DATA=DIR   the phone to use as it is (e.g. a KEEP_DATA=1 run's OUT/emu); never deleted
  SOA_PHONE      without EMU_DATA: unset -> OUT/emu linked from the shared pre-downloaded phone
                 (scripts/shared-phone.sh) when it is built, else empty (the client downloads);
                 none -> an empty phone: the full download; DIR -> OUT/emu from DIR
  SESSION_PLAY=0 stop at home (no popups, battle or gacha)
  NO_RETRY=1     no リトライ fallback for the title's first request
  FRESH_KVS=1    delete the phone's local KVS (data/shared_prefs/Aska.xml) first
  SERVER_ARGS    extra soa-server arguments
The milestones, in order: NoLoginStart answered; StartBridge, the bridge POST, UpdateSession (the
wire); Login -> LoginResult (+ the GetPlayerRes that ends the request); the data check or the
download (manifests, the bundles, the master bundle); home (the notice board); the login popups;
ミッション -> GetMissionList; Mere -> 1-05 -> MissionStart; the battle -> MissionEnd and its battle
log as the server decoded it; mf01_001 cleared; the results -> the map; ガチャ -> a 10-draw ->
SaleGacha, the coins debited and ten draws in the state; home. Prints PASS / FAIL per milestone and
a final PASS / FAIL (exit 0 / 1). Kills only the processes it started.
Targets: emu (default), port-server, port-inproc (the wire's own milestones are skipped there)."""
import os
import subprocess
import sys

from .. import popups as _popups, ui370
from ..flows import gacha, launch, mission
from ..milestones import Failed
from ..proc import REPO
from ..targets import Abort, Config, Layout, Run
from . import common

TARGETS = ("emu", "port-server", "port-inproc")
WRAPPER = "emulator/scripts/emulator_session.sh"

# The screenshot names this session's files always had (the shared flows' names -> OUT/NAME.png).
SHOTS = {
    "03-planets": "planets", "04-mission-map": "mission-map", "05-mission-detail": "mission-detail", "06-party": "party",
    "07-start-confirm": "start-confirm", "08-battle": "battle", "09-result": "result", "10-map-after-clear": "map-after-clear",
    "11-home-after-battle": "home-after-battle", "12-gacha": "gacha", "13-gacha-detail": "gacha-detail",
    "14-gacha-confirm": "gacha-confirm", "15-summon": "summon", "16-gacha-result": "gacha-result",
    "17-gacha-closed": "gacha-result-closed", "18-home-end": "home-end",
}

BATTLE_LOG_CHECK = r'''
import re, sys, msgpack
log = msgpack.unpackb(open(sys.argv[1], "rb").read(), raw=False, strict_map_key=False)
t = log.get("mission_time", 0)
enemies = sum(e.get("num", 0) for e in log.get("DefeatedEnemyInfo", []))
evals = len(log.get("BattleEvaluationInfo", []))
srv = open(sys.argv[2], errors="replace").read()
m = re.findall(r"MissionEnd mission \d+: .* time (\d+) ms", srv)
ok = not log.get("is_defeat", True) and t > 0 and enemies > 0 and evals > 0 and m and int(m[-1]) == t
print(f"mission_time {t} ms, {enemies} enemies defeated, {evals} evaluations, server time {m[-1] if m else '-'} ms")
sys.exit(0 if ok else 1)
'''


def emu_options(ap):
    ap.add_argument("client", nargs="?", default=os.path.join(REPO, "build/emulator/soa-emu"),
                    help="the client: soa-emu (default build/emulator/soa-emu), or soa (soa --server)")
    ap.add_argument("server", nargs="?", default=os.path.join(REPO, "build/server/soa-server"), help="soa-server")
    ap.add_argument("out", nargs="?", default=None, help="the out dir (default a fresh mktemp dir)")


options = emu_options


def emu_run(o, server_args, env=None, shots=None):
    """The emulator session's Run: the emu-session layout (OUT/emu.log, OUT/NAME.png, ...), the
    server's own defaults (seed, no clock) with --seed-rng 1, the session's env knobs."""
    import tempfile
    for b, what in ((o.client, "soa-emu"), (o.server, "soa-server")):
        if o.target != "port-inproc" and not os.access(b, os.X_OK):
            print("FAIL: %s not built (scripts/build.sh --target %s)" % (b, what))
            raise Abort(what)
    o.out = os.path.abspath(o.out or tempfile.mkdtemp(prefix="emulator-session.", dir=os.environ.get("TMPDIR", "/tmp")))
    os.makedirs(o.out, exist_ok=True)
    print("binaries: client %s, soa-server %s" % (os.path.realpath(o.client), os.path.realpath(o.server)))
    # a stale soa-server (older than this checkout's server sources) answers with the old rules
    newer = subprocess.run(["find", os.path.join(REPO, "server"), "(", "-name", "*.cpp", "-o", "-name", "*.h", ")", "-newer",
                            o.server, "-print", "-quit"], capture_output=True, text=True).stdout.strip()
    if newer:
        print("WARNING: %s is older than sources under %s/server: rebuild it (cmake --build build --target soa-server)" % (o.server, REPO))
    phone = os.environ.get("EMU_DATA") or None
    cfg = Config(server_args + (os.environ.get("SERVER_ARGS", "").split()), None, seed=False, seed_rng=1, limit=3000,
                 explicit_data=False, state_master=False, fresh_kvs=common.env_on("FRESH_KVS"), phone=phone, env=env,
                 # the given client for emu (soa-emu, or soa on the wire: rebase_server_diff.sh); the port
                 # targets take it only when it is a soa
                 binary=o.client if o.target == "emu" or os.path.basename(o.client) in ("soa", "soa.exe") else None,
                 server_binary=o.server)
    return Run(o.target, Layout.emu_session(o.out, phone, o.target, shots), cfg, keep=common.env_on("KEEP_DATA"), slot=o.slot)


def finish(s):
    """The emulator session's end: the milestones, the logs, PASS / FAIL."""
    print("---")
    print("\n".join(s.results))
    print("logs: %s %s %s; screenshots and state dumps in %s" % (s.client_log, s.server_log, s.packets, s.dir))
    print("FAIL" if s.failed else "PASS")
    return 1 if s.failed else 0


def wire_login(s):
    """TAP TO START -> (the wire: StartBridge, the bridge POST, UpdateSession) -> Login."""
    if s.target == "port-inproc":
        launch.tap_to_start(s)
        return
    s.tap_until("StartBridge -> ResultStart", 120, ui370.TITLE, lambda: s.in_packets(r"< ResultStart"))
    s.wait_for("bridge POST (/bridge)", 60, lambda: s.in_packets(r"bridge: UUID="))
    s.wait_for("UpdateSession -> ResultUpdateSession", 60, lambda: s.in_packets(r"< ResultUpdateSession"))


def data_on_phone(s):
    return s.predownloaded and os.path.isdir(os.path.join(s.phone, "data/files/download/UI"))


def body(s):
    s.predownloaded = data_on_phone(s)
    launch.title(s, "title", retry=not common.env_on("NO_RETRY"))
    wire_login(s)
    s.wait_for("Login -> LoginResult (decoded)", 60, lambda: s.in_packets(r"< LoginResult .* data\{"))
    if s.target != "port-inproc":
        s.wait_for("Login's GetPlayerRes", 30, lambda: s.in_packets(r"< GetPlayerRes .*ends the login request"))
    # a fixed wait: a picture of the screen 8 s after the login (the data check after it waits for itself)
    s.ctl("wait:8000", s.shot_cmd("after-login"))
    if s.predownloaded:
        s.note("the game data is on the phone (EMU_DATA / SOA_PHONE); no download")
    launch.data_check(s, lambda: s.in_client(r"ShowWebView\(http"), "home (notice board)", "download-dialog", "download-done")
    if not s.predownloaded:
        s.check("master bundle (B/1115774b/b9a9e011.bin)", s.in_client(r"/Android/B/1115774b/b9a9e011\.bin"))
    if os.environ.get("SESSION_PLAY", "1") == "0":
        common.settle(s, "home-notice", hold=2)
        common.tap_to_screen(s, "the notice board: 閉じる", "364:1133", "home", mask=common.HOME_MASK)
        return
    try:
        line = _popups.login_popups(s.fifo, s.client_log, s.layout.shot_path("notice"), s.layout.shot_path("login-bonus"),
                                    s.layout.shot_path("home"), alive=s.alive)
        with open(os.path.join(s.dir, "popups.txt"), "w") as f:
            f.write(line + "\n")
        s.ok("login " + line[3:])
    except Failed as e:
        with open(os.path.join(s.dir, "popups.txt"), "w") as f:
            f.write("FAIL: %s\n" % e)
        s.fail("login popups (FAIL: %s)" % e)
    s.state("1-home")
    st2 = mission.campaign_105(s)
    blogs = sorted((os.path.join(os.path.dirname(s.packets), f) for f in os.listdir(os.path.dirname(s.packets))
                    if f.endswith("-MissionEnd-battle_log.msgp")), key=os.path.getmtime)
    if blogs:
        r = subprocess.run([sys.executable, "-c", BATTLE_LOG_CHECK, blogs[-1], s.server_log], capture_output=True, text=True)
        s.check("battle log decoded by the server (%s)" % (r.stdout.strip() or r.stderr.strip()[-200:]), r.returncode == 0)
    else:
        s.miss("battle log (no MissionEnd battle_log in the packet log)")
    gacha.ten_draw(s, st2)
    s.check("no ProtocolError in the packet log", not s.in_packets(r"< ProtocolError"))
    warnings = s.count(s.client_log, r"^W/jni|^W/loader|^W/http")
    print("requests: %d game, %d HTTP GET; JVM/HLE/HTTP warnings: %d" % (s.count(s.packets, r" > "), s.count(s.client_log, r"I/http: GET"),
                                                                       warnings))


def main(o):
    try:
        s = emu_run(o, ["--campaign-seed", "mf01_001"], shots=SHOTS)
    except Abort:
        return 1
    common.drive(s, body)
    return finish(s)

