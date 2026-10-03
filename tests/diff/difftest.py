#!/usr/bin/env python3
"""tests/diff: the port against the emulator, flow by flow (tests/diff/README.md).

    tests/diff/run.sh [FLOW...] [--target emu,port-server,port-inproc] [--out DIR] [--keep]
                      [--sequential] [--inject TARGET:SERVER-ARGS]

Each flow runs once per target, the targets in parallel (each its own fresh server state, phone,
ports and run dir), then each port target is compared with the emulator (the reference). Prints
a summary; exits 1 when any flow FAILs.
"""
import argparse
import os
import shlex
import sys
import threading
import time
import traceback

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), "control"))
import compare  # noqa: E402  (tests/diff/compare.py: the report)
from soadrive import targets  # noqa: E402  (control/soadrive: the driver library)
from soadrive.targets import soaslot  # noqa: E402
from soadrive.flows import event, seeded, shard_battle, shard_gacha, shard_login, shard_tutorial, tutorial  # noqa: E402

# The full flows (the end-of-batch gate: `run.sh` with no flow names) and the shards (short flows
# for per-change gating: tools/tests_for.py picks them; tests/diff/README.md "Shards").
FULL = (seeded, tutorial, event)
SHARDS = (shard_login, shard_battle, shard_gacha) + shard_tutorial.STAGES
FLOWS = {f.NAME: f for f in FULL + SHARDS}
REF = "emu"


def run_target(flow, target, rdir, opts, inject, out, prepared=None):
    cfg = flow.config(targets.Config)
    if inject:
        cfg.server_args += inject
    if prepared:
        cfg.prepared = prepared
    r = targets.Run(target, rdir, cfg, keep=opts.keep)
    out[target] = r
    t0 = time.monotonic()
    try:
        r.start()
        if inject:
            r.note("injected server arguments: %s" % " ".join(inject))
        flow.run(r)
    except targets.Abort as e:
        if not r.failed:
            r.miss("aborted: %s" % e)
    except Exception:
        r.miss("driver error: " + traceback.format_exc().strip().splitlines()[-1])
        traceback.print_exc()
    finally:
        try:
            r.stop()
        except Exception:
            traceback.print_exc()
        r.elapsed_total = int(time.monotonic() - t0) - getattr(r, "queued", 0)


def run_flow(name, tgts, o, inject, out, results, start_gate):
    """One flow: its targets in parallel (each queued for a game slot, control/soaslot.py), then
    the comparison. results[name] = (ok, summary line, report text)."""
    flow = FLOWS[name]
    fdir = os.path.join(out, name)
    os.makedirs(fdir, exist_ok=True)
    t0 = time.monotonic()
    prepared = None
    if hasattr(flow, "prepare"):
        try:
            prepared = flow.prepare(os.path.join(fdir, "prepared"), targets.binaries()["server"])
        except Exception as e:
            text = "# tests/diff flow %s\n\nFAIL: preparing the server state: %s\n" % (name, e)
            open(os.path.join(fdir, "report.txt"), "w").write(text)
            results[name] = (False, "FAIL %-14s %4ds  (no prepared state)" % (name, 0), text)
            return
    runs, threads = {}, []
    for t in tgts:
        with start_gate:  # staggered starts: boots don't all compete for the CPU in the same second
            th = threading.Thread(target=run_target, args=(flow, t, os.path.join(fdir, t), o, inject.get(t), runs, prepared))
            th.start()
            time.sleep(0 if o.sequential else 2)
        if o.sequential:
            th.join()
        threads.append(th)
    for th in threads:
        th.join()
    runs = {t: runs[t] for t in tgts if t in runs}
    ok = compare.report(flow, runs, REF, os.path.join(fdir, "report.txt"))
    line = "%s %-14s %4ds  %s" % ("PASS" if ok else "FAIL", name, int(time.monotonic() - t0),
                                  "  ".join("%s %ds" % (t, r.elapsed_total) for t, r in runs.items()))
    results[name] = (ok, line, open(os.path.join(fdir, "report.txt")).read())
    print(results[name][2] + "\n" + line, flush=True)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("flows", nargs="*", help="flows and shards (default the full flows: %s; `shards`: every shard; all: %s)"
                    % (" ".join(f.NAME for f in FULL), " ".join(FLOWS)))
    ap.add_argument("--target", default=",".join(targets.TARGETS), help="comma list (default all; emu is the reference)")
    ap.add_argument("--out", default=None, help="the out dir (default a fresh /tmp/tests-diff.XXXX)")
    ap.add_argument("--keep", action="store_true", help="keep the run phones")
    ap.add_argument("--sequential", action="store_true", help="one run at a time (default: every flow and target at once, "
                    "bounded by the game slot pool, control/soaslot.py)")
    ap.add_argument("--inject", action="append", default=[], metavar="TARGET:ARGS",
                    help="extra server arguments for one target only, e.g. 'port-inproc:--start-coins 1000' "
                         "(the deliberate-difference check: the run must FAIL)")
    o = ap.parse_args()
    flows = o.flows or [f.NAME for f in FULL]
    if flows == ["shards"]:
        flows = [f.NAME for f in SHARDS]
    for f in flows:
        if f not in FLOWS:
            ap.error("unknown flow %s (%s)" % (f, " ".join(FLOWS)))
    tgts = [t.strip() for t in o.target.split(",") if t.strip()]
    for t in tgts:
        if t not in targets.TARGETS:
            ap.error("unknown target %s (%s)" % (t, " ".join(targets.TARGETS)))
    inject = {}
    for x in o.inject:
        t, _, a = x.partition(":")
        inject.setdefault(t, []).extend(shlex.split(a))
    out = os.path.abspath(o.out) if o.out else None
    if not out:
        import tempfile
        out = tempfile.mkdtemp(prefix="tests-diff.", dir=os.environ.get("TMPDIR", "/tmp"))
    os.makedirs(out, exist_ok=True)
    print("tests/diff: flows %s, targets %s, out %s" % (" ".join(flows), " ".join(tgts), out), flush=True)

    # Every flow at once (the slot pool bounds how many clients run); the longest first, so the
    # wall time is the longest flow's when there are enough slots. --sequential: one run at a time.
    t0 = time.monotonic()
    results, gate, threads = {}, threading.Lock(), []
    order = sorted(flows, key=lambda f: -getattr(FLOWS[f], "EST", 300))
    for name in order:
        th = threading.Thread(target=run_flow, args=(name, tgts, o, inject, out, results, gate))
        th.start()
        if o.sequential:
            th.join()
        threads.append(th)
    for th in threads:
        th.join()
    wall = int(time.monotonic() - t0)
    summary = [results[f][1] for f in flows if f in results]
    all_ok = all(results[f][0] for f in flows if f in results) and all(f in results for f in flows)
    summary.append("wall time %ds (%d flows x %d targets, %s)" % (wall, len(flows), len(tgts),
                                                                 "sequential" if o.sequential else "parallel, %d game slots" % soaslot.n_slots()))
    with open(os.path.join(out, "summary.txt"), "w") as f:
        f.write("\n".join(summary) + "\n")
    print("---")
    print("\n".join(summary))
    print("%s (reports: %s/<flow>/report.txt)" % ("PASS" if all_ok else "FAIL", out))
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
