"""Session `selftest-live`: soa's self-tests (soa --selftest FILTER: the guest code, no natives installed)
run on a live screen instead of the title: the layout tests of render / scene / anim prove their classes
on the running game's objects (port/src/native/render/render_test_util.h, on_frame), and the title
has no 3D models. The client is soa on the wire (--server: with --selftest no natives are installed,
so the in-process route isn't there either) against a fresh soa-server, the seeded player (LOCAL00001;
--campaign-seed mf01_001): the title, TAP TO START, Login, the data check (the shared pre-downloaded
phone, linked), home (the notice board closed); with --at battle also the login popups, ミッション ->
Mere -> 1-05 -> MissionStart, 15 s into the battle. Then OUT/start-tests is created
(SOA_SELFTEST_START_FILE), the tests run on the game's threads and soa exits with their result.

Usage: control/run.py --target port-server selftest-live SOA OUT TMP FILTER [--at home|battle]
  (port/scripts/selftest_live.sh SOA OUT TMP FILTER [--at home|battle])
OUT/log.txt is soa's log: the tests' "ok / FAIL" lines and the summary ("N/M native tests passed").
Prints PASS (every selected test passed) or FAIL; exit 0 / 1.
Targets: port-server."""
import os
import time

from .. import popups as _popups, ui370
from ..flows import launch
from ..milestones import Failed
from ..targets import Abort
from . import common, seeded

TARGETS = ("port-server",)
WRAPPER = "port/scripts/selftest_live.sh"


def options(ap):
    common.port_options(ap, extra=False)
    ap.add_argument("filter", help="the self-tests to run (soa --selftest FILTER)")
    ap.add_argument("--at", choices=("home", "battle"), default="home", help="the screen the tests run on")


def main(o):
    start = os.path.join(os.path.abspath(o.out), "start-tests")
    os.makedirs(o.out, exist_ok=True)
    if os.path.exists(start):
        os.remove(start)
    cfg = common.port_config(o, server_args=["--campaign-seed", "mf01_001"], limit=2400,
                             env={"SOA_SELFTEST_START_FILE": start})
    cfg.client_args = ["--selftest", o.filter]  # soa-server: SOA_SERVER (default build/server/soa-server)
    try:
        s = common.port_run(o, cfg)
    except Abort:
        return 1

    def body(s):
        s.predownloaded = seeded.data_on_phone(s)
        launch.title(s, "01-title")
        seeded.wire_login(s)
        s.wait_for("Login -> LoginResult (decoded)", 60, lambda: s.in_packets(r"< LoginResult .* data\{"))
        s.wait_for("Login's GetPlayerRes", 30, lambda: s.in_packets(r"< GetPlayerRes .*ends the login request"))
        s.ctl("wait:8000")
        launch.data_check(s, lambda: s.in_client(r"ShowWebView\(http"), "home (notice board)", "00-download-dialog",
                          "00-download-done")
        if o.at == "home":
            s.ctl("wait:5000", "tap:364:1133", "wait:10000", s.shot_cmd("02-home"))
        else:
            try:
                _popups.login_popups(s.fifo, s.client_log, s.layout.shot_path("02-notice"), s.layout.shot_path("02-login-bonus"),
                                     s.layout.shot_path("02-home"), alive=s.alive)
                s.ok("login popups")
            except Failed as e:
                s.fail("login popups (FAIL: %s)" % e)
            n = s.n_packets(r"< GetMissionListRes")
            s.tap_until("ミッション -> GetMissionList", 60, ui370.HOME_MISSION, s.more_than(r"< GetMissionListRes", n))
            s.ctl("wait:6000")
            s.ctl("tap:" + ui370.PLANET_MERE, "wait:3000", "tap:" + ui370.PLANET_SORTIE, "wait:7000")
            s.ctl("tap:" + ui370.MAP_105, "wait:4000")
            s.ctl("tap:" + ui370.SINGLE_PLAY, "wait:5000", "tap:" + ui370.RENTAL_NONE, "wait:5000")
            s.ctl("tap:" + ui370.PARTY_START, "wait:3000")
            s.tap_until("1-05 -> MissionStart -> MissionStartRes", 60, ui370.CONFIRM_OK, lambda: s.in_packets(r"< MissionStartRes"))
            s.ctl("wait:15000", s.shot_cmd("08-battle"))
        open(start, "w").close()
        s.ok("tests started at %s" % o.at)
        end = time.monotonic() + 900
        while s.alive() and time.monotonic() < end:
            if s.in_client(r"native tests passed"):
                break
            time.sleep(1)

    common.drive(s, body)
    log = open(s.client_log, errors="replace").read()
    for ln in log.splitlines():
        if ln.startswith("ok  ") or ln.startswith("FAIL") or ln.startswith("    FAIL"):
            print(ln)
    summary = [ln for ln in log.splitlines() if "native tests passed" in ln]
    fails = []
    if not summary:
        fails.append("the tests didn't finish (see %s)" % s.client_log)
    else:
        a, b = summary[-1].split()[0].split("/")
        if a != b:
            fails.append(summary[-1].strip())
    return common.verdict(s, fails, "%s at %s" % (summary[-1].strip() if summary else "-", o.at))
