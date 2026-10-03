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

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from diffdrive import compare, targets  # noqa: E402
from diffdrive.flows import event, seeded, tutorial  # noqa: E402

FLOWS = {f.NAME: f for f in (seeded, tutorial, event)}
REF = "emu"


def run_target(flow, target, rdir, opts, inject, out):
    cfg = flow.config(targets.Config)
    if inject:
        cfg.server_args += inject
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
        r.elapsed_total = int(time.monotonic() - t0)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("flows", nargs="*", help="flows (default all: %s)" % " ".join(FLOWS))
    ap.add_argument("--target", default=",".join(targets.TARGETS), help="comma list (default all; emu is the reference)")
    ap.add_argument("--out", default=None, help="the out dir (default a fresh /tmp/tests-diff.XXXX)")
    ap.add_argument("--keep", action="store_true", help="keep the run phones")
    ap.add_argument("--sequential", action="store_true", help="one target at a time")
    ap.add_argument("--inject", action="append", default=[], metavar="TARGET:ARGS",
                    help="extra server arguments for one target only, e.g. 'port-inproc:--start-coins 1000' "
                         "(the deliberate-difference check: the run must FAIL)")
    o = ap.parse_args()
    flows = o.flows or list(FLOWS)
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

    summary, all_ok = [], True
    for name in flows:
        flow = FLOWS[name]
        fdir = os.path.join(out, name)
        os.makedirs(fdir, exist_ok=True)
        t0 = time.monotonic()
        runs = {}
        threads = []
        for t in tgts:
            th = threading.Thread(target=run_target, args=(flow, t, os.path.join(fdir, t), o, inject.get(t), runs))
            th.start()
            if o.sequential:
                th.join()
            threads.append(th)
            time.sleep(3)  # staggered starts: the boots don't all compete for the CPU at once
        for th in threads:
            th.join()
        runs = {t: runs[t] for t in tgts if t in runs}
        ok = compare.report(flow, runs, REF, os.path.join(fdir, "report.txt"))
        all_ok &= ok
        line = "%s %-9s %4ds  %s" % ("PASS" if ok else "FAIL", name, int(time.monotonic() - t0),
                                    "  ".join("%s %ds" % (t, r.elapsed_total) for t, r in runs.items()))
        summary.append(line)
        print(open(os.path.join(fdir, "report.txt")).read(), flush=True)
    with open(os.path.join(out, "summary.txt"), "w") as f:
        f.write("\n".join(summary) + "\n")
    print("---")
    print("\n".join(summary))
    print("%s (reports: %s/<flow>/report.txt)" % ("PASS" if all_ok else "FAIL", out))
    return 0 if all_ok else 1


if __name__ == "__main__":
    sys.exit(main())
