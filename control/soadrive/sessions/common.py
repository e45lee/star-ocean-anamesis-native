"""What the sessions share: their command lines (the port's `SOA OUT TMP [soa flags...]`), starting
a Run in the session layouts, the drive / verdict pattern, the port's login."""
import argparse
import os
import re

from ..flows import launch
from ..targets import Abort, Config, Layout, Run
# the condition waits (soadrive/waits.py), for the sessions as common.NAME
from ..waits import (EVENT_MASK, GACHA_MASK, HOME_MASK, gave_up, last_phase, look, settle, tap_settled, tap_to_count,  # noqa: F401
                     tap_to_log, tap_to_phase, tap_to_screen, tap_to_server)


def env_on(name, default="0"):
    return os.environ.get(name, default) == "1"


# ---- the port's sessions: port/scripts/<name>_session.sh SOA OUT TMP [soa flags...] -------------------
def port_options(ap, extra=True):
    ap.add_argument("soa", help="the soa binary (build/port/soa)")
    ap.add_argument("out", help="the out dir: log.txt, shots/, state-*.txt, packets/")
    ap.add_argument("tmp", help="the scratch dir: the phone (data/, with the in-process server's state) and the FIFO")
    if extra:
        ap.add_argument("soa_args", nargs=argparse.REMAINDER, help="more soa flags")


def port_config(o, server_args=(), limit=1800, seed_rng=True, **kw):
    """The port's sessions: soa --headless (WATCH=1: --windowed) --seed-rng SEED_RNG (default 1)
    --data TMP/data --size 729x1296 --control TMP/fifo, the committed client save (episode flag 0),
    the in-process server's own defaults (its master, CDN, seed save and state DB in the phone),
    the packet log in OUT/packets (milestones every target has); a session's extra soa flags last.
    seed_rng None: no --seed-rng (the sessions that never passed one)."""
    kw.setdefault("client_save", "session")
    if seed_rng is True:
        seed_rng = int(os.environ.get("SEED_RNG") or 1)
    return Config(server_args, None, seed=False, seed_rng=seed_rng,
                  client_args=list(getattr(o, "soa_args", None) or []), limit=limit, windowed=env_on("WATCH"),
                  explicit_data=False, state_master=False, **kw)


def port_run(o, cfg, shot_names=None, name=None):
    """A Run of the port session layout (targets.Layout.port_session) for o.target; name: one of
    the session's boots (its own log, shots dir and phone)."""
    o.soa, o.out, o.tmp = (os.path.abspath(x) for x in (o.soa, o.out, o.tmp))
    os.makedirs(o.out, exist_ok=True)
    os.makedirs(o.tmp, exist_ok=True)
    if o.target != "emu":
        cfg.binary = cfg.binary or o.soa
    return Run(o.target, Layout.port_session(o.out, o.tmp, o.target, shot_names, name), cfg, slot=o.slot)


def port_run_again(o, cfg, log_name):
    """A later boot on the same phone (TMP/data, kept as it is: its saves, the in-process server's
    state) with its own log OUT/LOG_NAME; the session's other outputs stay."""
    lay = Layout.port_session(o.out, o.tmp, o.target)
    lay.client_log = os.path.join(o.out, log_name)
    if o.target == "port-inproc":
        lay.server_log = lay.client_log
    lay.continued = True
    base = os.path.splitext(log_name)[0]
    lay.steps = os.path.join(o.out, "steps-%s.txt" % base)
    lay.packets = os.path.join(o.out, "packets-%s" % base, "packets.log")  # its own: milestones are read from it
    cfg.phone, cfg.fresh_kvs, cfg.client_save = lay.phone, False, False
    if o.target != "emu":
        cfg.binary = cfg.binary or o.soa
    return Run(o.target, lay, cfg, slot=o.slot)


def counted(s, name):
    """The verdict of the sessions that count their failed checks: 'PASS NAME' / 'FAIL NAME (N)'."""
    n = sum(1 for r in s.results if r.startswith("FAIL"))
    print("FAIL %s (%d)" % (name, n) if n else "PASS %s" % name, flush=True)
    return 1 if n else 0


def drive(s, body):
    """s.start(), body(s), s.stop() (always). True when body ran to its end, False after an Abort."""
    try:
        s.start()
        body(s)
        return True
    except Abort as e:
        if not s.failed:  # stopped without a step's FAIL (e.g. the client never opened its FIFO)
            s.miss("stopped: %s" % e)
        return False
    finally:
        s.stop()


def verdict(s, fails, line):
    """The port sessions' end: each failed check as 'FAIL: ...', then 'PASS: line' (exit 0) or
    exit 1. A step the run didn't reach was printed already (FAIL: ...)."""
    for f in fails:
        print("FAIL: " + f, flush=True)
    if fails or s.failed:
        return 1
    print("PASS: " + line, flush=True)
    return 0


def checks(*pairs):
    """[(ok, message if not ok), ...] -> the messages of the failed ones."""
    return [msg for ok, msg in pairs if not ok]


def log_has(s, rx):
    return s.grep(s.client_log, rx)


def common_log_checks(s, crash=True):
    """The checks most port sessions end with: no refused request, no crash."""
    out = []
    refused = [ln for ln in open(s.client_log, errors="replace").read().splitlines() if "refused with error" in ln]
    if refused:
        print("\n".join(refused))
        out.append("a request was refused")
    if crash and log_has(s, r"Unhandled SIG|\*\*\* host signal"):
        out.append("soa crashed")
    return out


def port_login(s, title="01-title", notice="02-notice", bonus="02-login-bonus", home="02-home",
               dialog_shot="00-download-dialog", done_shot="00-download-done", bonus_wait=None):
    """The port sessions' start (phone370_title + phone370_login + flowctl.py login-popups, now the
    shared launch flow): the title, TAP TO START -> Login -> the data check (or the download) ->
    home -> the notice board, the LOGIN BONUS. Returns the popups' summary line."""
    launch.title(s, title)
    return launch.login_to_home(s, notice, bonus, home, dialog_shot, done_shot, bonus_wait)


def state_value(text, rx, cast=int):
    m = re.search(rx, text, re.M)
    return cast(m.group(1)) if m else None


def episode_list(s, xy="270:1085"):
    """home's ミッション -> the episode list (phase 8). When the last episode played has its data
    on the phone, ミッション opens that episode's map instead (phase 5): Ep選択 (655:485 on a world
    map, else 655:375: Episode 1's planet select) -> the list (port/scripts/phone370.sh
    phone370_episode_list; port-only: the phase lines)."""
    line = s.tap_log(r"port_debug: phase (5|8) ", 60, 20, 3, "tap:" + xy, name="ミッション -> the episode list or a map")
    if "phase 8 " in line:
        return
    settle(s)  # the map faded in: a tap during the fade is lost
    if s.tap_log(launch.phase(8), 12, 12, 1, "tap:655:485", name="Ep選択 (a world map) -> the episode list", fatal=None) is None:
        # the other spot: Episode 1's planet select
        s.tap_log(launch.phase(8), 60, 20, 3, "tap:655:375", name="Ep選択 (the planet select) -> the episode list")
