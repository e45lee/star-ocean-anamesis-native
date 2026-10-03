"""Session `login`: the in-process gate of the 3.7.0 rebase (docs/history/PLAN-rebase-370.md P1):
soa on the 3.7.0 client with its defaults, --server inproc (the local server library on the
FakeApiCaller route, plus its CDN in-process) and --natives route, from the title to home:
NoLoginStart, TAP TO START, Login, the downloader (its check, or the whole download on an empty
phone), home (the notice board), the login popups (notice, LOGIN BONUS). Prints "PASS: ..." at the
end, or "FAIL: ..." with exit status 1.

Usage: port/scripts/rebase_inproc_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env:
  SOA_PHONE       the phone (scripts/shared-phone.sh): unset -> linked from the shared
                  pre-downloaded phone work/phone-3.7.0 when it is built; DIR -> from DIR, a phone
                  with the game data downloaded already: the client only checks its data against
                  the in-process CDN. SOA_PHONE=none: the data dir starts empty and the client
                  downloads the 3 GB from the in-process CDN first (the download dialogs; about 3-4
                  minutes more; scripts/make-phone-370.sh's run).
  CLIENT_SAVE=client|seed|phone  the client save copied into shared_prefs/Game.xml: the committed
                  data/saves/client/Game.xml (default), the seed data/saves/seed/Game.xml, or the
                  phone's own (SOA_PHONE only). The local KVS (Aska.xml) is always deleted.
  SEED_RNG (soa --seed-rng; default 1); WATCH=1 shows the window
Screenshots go to OUT/shots, the log to OUT/log.txt, the packets to OUT/packets, the popups' line
to OUT/popups.txt, the server state (tools/server_state.py) to OUT/state-home.txt. Kills only the
soa it started. Targets: port-inproc (the in-process server is what it checks)."""
import os
import shutil

from ..flows import launch
from ..proc import REPO
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it checks the in-process route's own log lines (the FakeApiCaller, --natives route)"
WRAPPER = "port/scripts/rebase_inproc_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def main(o):
    save = os.environ.get("CLIENT_SAVE", "client")
    if save not in ("client", "seed", "phone"):
        print("FAIL: CLIENT_SAVE=%s" % save)
        return 1
    if save == "phone" and not os.environ.get("SOA_PHONE"):
        print("FAIL: CLIENT_SAVE=phone needs SOA_PHONE")
        return 1
    cfg = common.port_config(o, limit=1500, client_save="session" if save == "client" else False)
    s = common.port_run(o, cfg)
    if save == "seed":
        # installed after the phone is made (Run.start), before the client boots: a start hook
        s.before_client = lambda: shutil.copyfile(os.path.join(REPO, "data/saves/seed/Game.xml"),
                                                  os.path.join(s.phone, "data/shared_prefs/Game.xml"))
    elif save == "phone":
        s.before_client = lambda: os.path.exists(os.path.join(s.phone, "data/shared_prefs/Game.xml")) or s.fail(
            "CLIENT_SAVE=phone: %s has no save (the shared phone never does)" % os.environ.get("SOA_PHONE"))
    popups = []

    def body(s):
        launch.title(s, "01-title")
        popups.append(launch.login_to_home(s, "04-notice", "05-login-bonus", None, "02-download-dialog", "03-download-done"))
        with open(os.path.join(o.out, "popups.txt"), "w") as f:
            f.write(popups[-1] + "\n")
        s.ctl("wait:5000", s.shot_cmd("07-home"))
        s.state("home")

    if not common.drive(s, body):
        return 1
    has = lambda rx: common.log_has(s, rx)
    home = open(os.path.join(o.out, "state-home.txt")).read() if os.path.exists(os.path.join(o.out, "state-home.txt")) else ""
    fails = common.checks(
        (has(r"p370: patch: CParameterUtility::FindGlobalStringWithKey hooked"), "platform370's patch wasn't installed"),
        (has(r"replaced by native code \(--natives route\)"), "not --natives route"),
        (has(r"fakeapi: fid a01c67ef: player_get.msgp from the local server"), "Login wasn't answered by the local server"),
        (has(r"version_latest_Individual"), "the client didn't check its data against the in-process CDN"),
        (popups and "notice yes, login bonus x" in popups[-1] and "login bonus x0" not in popups[-1],
         "the notice board and the LOGIN BONUS popup didn't both open and close"),
        (any(ln.startswith("player LOCAL00001 ") for ln in home.splitlines()), "no LOCAL00001 player in the server state"),
    ) + common.common_log_checks(s)
    gets = s.count(s.client_log, r"I/http: GET")
    return common.verdict(s, fails, "3.7.0 client in-process: title, Login, data check (%d HTTP GETs from the in-process CDN), "
                          "home, login popups" % gets)
