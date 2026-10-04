#!/usr/bin/env python3
"""Runs a named session (control/soadrive/sessions/<name>.py) against a target.

    control/run.py [--target emu|port-server|port-inproc] SESSION [the session's arguments...]
    port/scripts/x_session.sh [--target T] ARGS...   (a wrapper: the same)
    control/run.py --list                     the sessions, their targets and their wrappers

The session scripts (port/scripts/*_session.sh, emulator/scripts/emulator_session.sh,
summer_demo.sh, ...) are thin wrappers over this: `exec control/run.py SESSION "$@"`, with the
same arguments, environment knobs, output files and exit codes as before. Each session has a
default target (the program its wrapper always ran) and runs against any target it lists; one it
doesn't support is refused with the reason.

The run takes one game slot (control/soaslot.py) for its lifetime (every client it starts runs
under it), prints its steps, and ends with the session's verdict: exit 0 (PASS) or 1 (FAIL). Every
boot's end state is checked when it stops (G9: foreign keys, master references, schema version;
soadrive/targets.py Run.state_check): a violation fails the session.
"""
import argparse
import importlib
import os
import pkgutil
import signal
import sys
import traceback

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import soaslot  # noqa: E402
from soadrive import sessions, targets  # noqa: E402


def session_names():
    return sorted(m.name.replace("_", "-") for m in pkgutil.iter_modules(sessions.__path__) if not m.name.startswith("_")
                  and m.name != "common")


def load(name):
    return importlib.import_module("soadrive.sessions." + name.replace("-", "_"))


def main(argv):
    if argv and argv[0] == "--list":
        for n in session_names():
            m = load(n)
            print("%-20s %-28s %s" % (n, ",".join(m.TARGETS), getattr(m, "WRAPPER", "")))
        return 0
    target = None
    if len(argv) >= 2 and argv[0] == "--target":
        target, argv = argv[1], argv[2:]
    elif argv and argv[0].startswith("--target="):
        target, argv = argv[0].split("=", 1)[1], argv[1:]
    if not argv or argv[0] in ("-h", "--help"):
        print(__doc__ + "\nsessions: " + " ".join(session_names()))
        return 0 if argv else 2
    name, rest = argv[0], argv[1:]
    # the wrappers pass their own arguments after the name: `--target T` may come first among them
    if target is None and len(rest) >= 2 and rest[0] == "--target":
        target, rest = rest[1], rest[2:]
    if name.replace("_", "-") not in session_names():
        print("run.py: unknown session %s (%s)" % (name, " ".join(session_names())), file=sys.stderr)
        return 2
    mod = load(name)
    target = target or mod.TARGETS[0]
    if target not in targets.TARGETS:
        print("run.py: unknown target %s (%s)" % (target, " ".join(targets.TARGETS)), file=sys.stderr)
        return 2
    if target not in mod.TARGETS:
        print("FAIL: session %s doesn't run against %s: %s" % (name, target, getattr(mod, "TARGETS_WHY", "it uses that "
              "program's own features")))
        return 1
    ap = argparse.ArgumentParser(prog=getattr(mod, "WRAPPER", "control/run.py " + name), description=mod.__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    mod.options(ap)
    o = ap.parse_args(rest)
    o.target, o.session = target, name
    # TERM / HUP (a gate's timeout, a closed terminal) end the session like Ctrl-C: its clients run
    # in their own process groups, so the Run's stop() (in a finally) is what ends them
    def stop(signum, _frame):
        raise KeyboardInterrupt("signal %d" % signum)
    for sig in (signal.SIGTERM, signal.SIGHUP):
        signal.signal(sig, stop)
    # one game slot for the whole session (its clients run one at a time under it)
    o.slot = soaslot.acquire("%s %s" % (getattr(mod, "WRAPPER", name), target))
    try:
        rc = mod.main(o)
        # G9 (server/PLAN-schema.md S11): each boot's end state was checked when it stopped
        # (targets.Run.state_check); a violation fails the session whatever its own verdict said
        bad = [summary for _run, ok, summary in targets.Run.STATE_CHECKS if not ok]
        if bad and not rc:
            print("FAIL: the server's end state: %s" % "; ".join(bad))
            return 1
        return rc
    except targets.Abort:
        return 1
    except KeyboardInterrupt:
        print("FAIL: interrupted")
        return 1
    except Exception:
        traceback.print_exc()
        print("FAIL: driver error in session %s" % name)
        return 1
    finally:
        soaslot.release(o.slot)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
