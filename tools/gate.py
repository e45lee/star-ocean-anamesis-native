#!/usr/bin/env python3
"""Runs a tier of the gate tests (tests/tiers.json; tests/TIERS.md).

    tools/gate.sh T0                              every commit: build + the fast checks
    tools/gate.sh T1 --for PATH...                T0, then what tools/tests_for.py picks for the paths
    tools/gate.sh T1 --git-diff REV               ... for the paths changed since REV
    tools/gate.sh T2                              T0, then every T2 test (the batch gate)
    tools/gate.sh T3                              every T3 test (occasional)
    tools/gate.sh TEST...                         these tests by name (e.g. shard:battle session:gacha)
  options: --out DIR (default a fresh /tmp/gate.XXXX), --list (print the plan only), --no-t0,
           --markdown (the table of tests/TIERS.md),
           --keep (keep the scratch dirs), --jobs N (non-game checks at once, default 4)

The build runs first, alone. Then everything else at once: the checks on --jobs workers, the game
tests in parallel (each queues for a game slot itself: control/soaslot.py, so the machine is never
overloaded), the selected tests/diff shards and flows in one tests/diff run (its own parallelism).
Every test gets OUT/<name>/ (its output; {out}) and a scratch dir ({tmp}, deleted unless --keep);
{base} is the revision compared with (--git-diff REV, else HEAD~1: the parent build of replay-parent),
and a time limit of 3x its measured time (at least 10 minutes), counted from when it starts: a
game test takes its slot here first (passed down, so its script doesn't queue again). Prints a table (PASS / FAIL, the
time against the measured one) and OUT/summary.txt; exit 1 when anything FAILs. A test with a
`known` failure in tests/tiers.json (one that fails without the change) is reported KNOWN, with
the reason, and doesn't fail the gate.
"""
import argparse
import concurrent.futures
import json
import os
import re
import shutil
import signal
import subprocess
import sys
import tempfile
import threading
import time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(REPO, "tools"))
import tests_for  # noqa: E402

sys.path.insert(0, os.path.join(REPO, "control"))
import soaslot  # noqa: E402  (the game slot pool)

PROCS, PLOCK = [], threading.Lock()
BASE = ["HEAD~1"]  # {base}: the revision the change is compared with (--git-diff REV, else HEAD~1)


def slug(name):
    return re.sub(r"[^\w.-]", "-", name)


def run_cmd(cmd, out, tmp, limit, log, slot=-1):
    """Runs cmd under `timeout -k 10 limit`; with a slot (a game test), the slot is the test's:
    passed down (SOA_SLOT_HELD: its scripts don't queue again), so the limit never counts a wait."""
    os.makedirs(out, exist_ok=True)
    os.makedirs(tmp, exist_ok=True)
    cmd = cmd.replace("{out}", out).replace("{tmp}", tmp).replace("{base}", BASE[0])
    env = dict(os.environ, SOA_SLOT_HELD="1") if slot >= 0 else None
    with open(log, "w") as f:
        f.write("$ %s\n" % cmd)
        f.flush()
        p = subprocess.Popen(["timeout", "-k", "10", str(limit), "bash", "-c", cmd], cwd=REPO, stdout=f, stderr=subprocess.STDOUT,
                             start_new_session=True, env=env, pass_fds=(slot,) if slot >= 0 else ())
        with PLOCK:
            PROCS.append(p)
        rc = p.wait()
    return rc


def run_test(t, outdir, keep):
    name = slug(t["name"])
    out, tmp = os.path.join(outdir, name), os.path.join(outdir, ".tmp", name)
    # A game test (one client at a time) queues for its slot here, before its clock starts.
    slot = soaslot.acquire("gate " + t["name"], quiet=True) if t.get("game", 0) else -1
    t0 = time.monotonic()
    try:
        rc = run_cmd(t["cmd"], out, tmp, max(600, 3 * t["secs"]), os.path.join(outdir, name + ".log"), slot)
    finally:
        soaslot.release(slot)
    if not keep:
        shutil.rmtree(tmp, ignore_errors=True)
    return {"name": t["name"], "tier": t["tier"], "ok": rc == 0, "rc": rc, "secs": int(time.monotonic() - t0), "est": t["secs"],
            "log": os.path.join(outdir, name + ".log")}


def run_diff(tests, outdir, keep):
    """The tests/diff shards and flows in one run; a result per test from its summary.txt."""
    flows = []
    for t in tests:
        m = re.match(r"tests/diff/run\.sh ((?:[\w-]+ )*)--out", t["cmd"])
        flows.append(m.group(1).split() if m and m.group(1) else ["seeded", "tutorial", "event"])
    allf = [f for fl in flows for f in fl]
    out = os.path.join(outdir, "tests-diff")
    t0 = time.monotonic()
    cmd = "tests/diff/run.sh %s --out %s" % (" ".join(allf), out) + (" --keep" if keep else "")
    # its runs queue for their slots inside (their time limits start after the wait): the run's
    # own limit only catches a hung driver
    rc = run_cmd(cmd, out, os.path.join(outdir, ".tmp", "tests-diff"), 4 * 3600, os.path.join(outdir, "tests-diff.log"))
    wall = int(time.monotonic() - t0)
    lines = open(os.path.join(out, "summary.txt")).read().splitlines() if os.path.exists(os.path.join(out, "summary.txt")) else []
    res = []
    for t, fl in zip(tests, flows):
        oks, secs = [], []
        for f in fl:
            ln = next((x for x in lines if re.match(r"(PASS|FAIL) %s\s" % re.escape(f), x)), None)
            oks.append(bool(ln and ln.startswith("PASS")))
            m = re.match(r"\S+ \S+\s+(\d+)s", ln or "")
            secs.append(int(m.group(1)) if m else wall)
        res.append({"name": t["name"], "tier": t["tier"], "ok": all(oks) and bool(lines), "rc": rc, "secs": max(secs or [wall]),
                    "est": t["secs"], "log": os.path.join(out, (fl[0] if len(fl) == 1 else ""), "report.txt")})
    return res


def plan(a):
    tiers = tests_for.load_tiers()
    by = {t["name"]: t for t in tiers}
    names = []
    for x in a.what:
        if x in ("T0", "T1", "T2", "T3"):
            if x != "T3" and not a.no_t0:
                names += [t["name"] for t in tiers if t["tier"] == "T0"]
            if x == "T1":
                paths = list(a.for_paths)
                if a.git_diff:
                    paths += tests_for.changed_paths(a.git_diff)
                if not paths:
                    sys.exit("gate: T1 needs --for PATH... or --git-diff REV (the change)")
                tests, _, _, _, _ = tests_for.select(paths)
                names += [t["name"] for t in tests]
            elif x in ("T2", "T3"):
                names += [t["name"] for t in tiers if t["tier"] == x]
        elif x in by:
            names.append(x)
        else:
            sys.exit("gate: unknown tier or test %s (tests/tiers.json)" % x)
    seen, out = set(), []
    for n in names:
        if n not in seen:
            seen.add(n)
            out.append(by[n])
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("what", nargs="*", help="T0, T1, T2, T3 or test names")
    ap.add_argument("--for", dest="for_paths", nargs="*", default=[])
    ap.add_argument("--git-diff")
    ap.add_argument("--out")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--no-t0", action="store_true")
    ap.add_argument("--keep", action="store_true")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--markdown", action="store_true", help="print tests/TIERS.md's table from tests/tiers.json")
    a = ap.parse_args()
    if a.markdown:
        return markdown()
    tests = plan(a)
    if a.git_diff:
        BASE[0] = a.git_diff
    if a.list or not tests:
        for t in tests:
            print("%-4s %-28s %5ds  %s" % (t["tier"], t["name"], t["secs"], t["cmd"]))
        print("%d tests" % len(tests))
        return 0
    outdir = os.path.abspath(a.out) if a.out else tempfile.mkdtemp(prefix="gate.", dir=os.environ.get("TMPDIR", "/tmp"))
    os.makedirs(outdir, exist_ok=True)
    print("gate %s: %d tests, out %s" % (" ".join(a.what), len(tests), outdir), flush=True)

    def stop(*_):
        with PLOCK:
            for p in PROCS:
                if p.poll() is None:
                    try:
                        os.killpg(p.pid, signal.SIGTERM)
                    except ProcessLookupError:
                        pass
        sys.exit(130)
    signal.signal(signal.SIGINT, stop)
    signal.signal(signal.SIGTERM, stop)

    t0 = time.monotonic()
    results = []
    build = [t for t in tests if t["kind"] == "build"]
    for t in build:
        r = run_test(t, outdir, a.keep)
        results.append(r)
        print("%s %-28s %4ds" % ("PASS" if r["ok"] else "FAIL", r["name"], r["secs"]), flush=True)
        if not r["ok"]:
            print("gate: the build failed (%s); nothing else runs" % r["log"])
            return finish(results, outdir, t0)
    rest = [t for t in tests if t["kind"] != "build"]
    diff = [t for t in rest if t["cmd"].startswith("tests/diff/run.sh")]
    games = [t for t in rest if t not in diff and t.get("game", 0)]
    checks = [t for t in rest if t not in diff and not t.get("game", 0)]
    with concurrent.futures.ThreadPoolExecutor(max_workers=max(1, a.jobs) + len(games) + 1) as ex:
        futs = [ex.submit(run_test, t, outdir, a.keep) for t in checks + games]
        if diff:
            futs.append(ex.submit(run_diff, diff, outdir, a.keep))
        for f in concurrent.futures.as_completed(futs):
            rs = f.result()
            for r in (rs if isinstance(rs, list) else [rs]):
                results.append(r)
                print("%s %-28s %4ds%s" % ("PASS" if r["ok"] else "FAIL", r["name"], r["secs"],
                                           "  (host GPU failure)" if not r["ok"] and host_gpu(r) else ""), flush=True)
    return finish(results, outdir, t0)


def markdown():
    """tests/TIERS.md's table (between its tiers-table markers), from tests/tiers.json."""
    rows = ["| Tier | Test | Time | Clients | What | Command |", "|---|---|---|---|---|---|"]
    for t in tests_for.load_tiers():
        secs = t["secs"]
        tm = "%d s" % secs if secs < 120 else "%.1f min" % (secs / 60)
        what = t["covers"].replace("|", "/") + (" **Known failure:** %s" % t["known"] if t.get("known") else "")
        rows.append("| %s | `%s` | %s | %s | %s | `%s` |" % (t["tier"], t["name"], tm, t.get("game", 0) or "-", what,
                                                         t["cmd"].replace("|", "\\|")))
    path = os.path.join(REPO, "tests/TIERS.md")
    text = open(path).read()
    a, b = "<!-- tiers-table: tools/gate.py --markdown -->\n", "<!-- /tiers-table -->"
    if a in text and b in text:
        text = text[:text.index(a) + len(a)] + "\n".join(rows) + "\n" + text[text.index(b):]
        open(path, "w").write(text)
        print("wrote tests/TIERS.md's table (%d tests)" % (len(rows) - 2))
    else:
        print("\n".join(rows))
    return 0


HOST_GPU = re.compile(r"HOST-GPU-FAILURE|in the host GPU driver|lost the host GPU|the client is gone: host GPU")


def host_gpu(r):
    """A failed test whose client lost the host's GPU (control/soadrive/targets.py labels it): the
    machine's problem, not the change's; rerun it once the host recovers."""
    try:
        return HOST_GPU.search(open(r["log"], errors="replace").read()) is not None
    except OSError:
        return False


def finish(results, outdir, t0):
    wall = int(time.monotonic() - t0)
    order = {t["name"]: i for i, t in enumerate(tests_for.load_tiers())}
    results.sort(key=lambda r: order.get(r["name"], 999))
    known = {t["name"]: t["known"] for t in tests_for.load_tiers() if t.get("known")}
    lines = ["%-5s %-4s %-28s %6s %8s  %s" % ("", "tier", "test", "time", "measured", "log")]
    for r in results:
        st = "PASS" if r["ok"] else "KNOWN" if r["name"] in known else "FAIL"
        gpu = st == "FAIL" and host_gpu(r)
        lines.append("%-5s %-4s %-28s %5ds %7ds  %s%s" % (st, r["tier"], r["name"], r["secs"], r["est"], r["log"],
                                                        "  [host GPU failure: rerun]" if gpu else ""))
    for r in results:
        if not r["ok"] and r["name"] in known:
            lines.append("KNOWN %s: %s" % (r["name"], known[r["name"]]))
    bad = [r for r in results if not r["ok"] and r["name"] not in known]
    gpu = [r["name"] for r in bad if host_gpu(r)]
    if gpu:
        lines.append("HOST GPU: %s failed because a client lost the host's GPU (D3D12 device removed, GLX, the NVIDIA "
                     "driver): not the change's fault; rerun them once the host recovers" % " ".join(gpu))
    ok = not bad
    lines.append("%s: %d tests, %d failed%s, wall time %ds (out %s)" % (
        "PASS" if ok else "FAIL", len(results), len(bad),
        ", %d known failures" % sum(1 for r in results if not r["ok"] and r["name"] in known) if any(
            not r["ok"] and r["name"] in known for r in results) else "", wall, outdir))
    text = "\n".join(lines)
    open(os.path.join(outdir, "summary.txt"), "w").write(text + "\n")
    print("---\n" + text)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
