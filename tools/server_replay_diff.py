#!/usr/bin/env python3
"""RG4 of server/PLAN-readability.md: replays every corpus with two soa-server builds and compares.

    tools/server_replay_diff.sh [--out DIR] [--keep] BIN_A BIN_B [CORPUS_DIR...]

BIN_A / BIN_B are two soa-server binaries (the parent's and the child's; the same one twice checks
that the replay is stable). The corpora default to every server/tests/replay/*/ (README.md there).
Each corpus is replayed (`soa-server <DIR/options> --replay DIR --out OUT`, in the corpus's time
zone, from the repository root) by both, and compared:
  1. the error codes (errors.txt), every reply body (<n>-<Method>.msgp) and the end state
     (state.sql: every table's rows, sorted, and the data dir's side files): byte-identical;
  2. the server log (paths masked): tier 1, the lines matching tools/server_log_patterns.txt (the
     lines scripts read), byte-identical; tier 2, any other difference is printed, and must be
     declared in the commit message (server/PLAN-readability.md 4.1).
Exit 0: identical; 2: only tier-2 log differences; 1: anything else differs (or a replay failed).
"""
import argparse
import difflib
import os
import re
import shutil
import subprocess
import sys
import tempfile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def corpora(given):
    if given:
        return [os.path.abspath(c) for c in given]
    base = os.path.join(REPO, "server/tests/replay")
    return sorted(os.path.join(base, d) for d in os.listdir(base) if os.path.exists(os.path.join(base, d, "requests.txt")))


def corpus_tz(c):
    for ln in open(os.path.join(c, "requests.txt")):
        m = re.match(r"# tz: (\S+)", ln)
        if m:
            return m.group(1)
        if not ln.startswith("#"):
            break
    return "UTC"


def start(binary, corpus, out):
    opts = [ln.rstrip("\n") for ln in open(os.path.join(corpus, "options")) if ln.strip()] if os.path.exists(os.path.join(corpus, "options")) else []
    env = dict(os.environ, TZ=corpus_tz(corpus))
    if os.path.isdir(out):
        shutil.rmtree(out)
    return subprocess.Popen([binary] + opts + ["--replay", corpus, "--out", out], cwd=REPO, env=env, stdout=subprocess.PIPE,
                            stderr=subprocess.STDOUT, text=True)


def patterns():
    pats = []
    for ln in open(os.path.join(REPO, "tools/server_log_patterns.txt"), encoding="utf-8"):
        if ln.startswith("#") or "\t" not in ln:
            continue
        pats.append(re.compile(ln.rstrip("\n").split("\t", 1)[1]))
    return pats


def masked_log(out):
    text = open(os.path.join(out, "server.log"), encoding="utf-8", errors="replace").read()
    text = text.replace(out, "<OUT>").replace(REPO, "<REPO>")
    real = os.path.realpath(REPO)
    if real != REPO:
        text = text.replace(real, "<REPO>")
    return text.splitlines()


def read(p):
    try:
        return open(p, "rb").read()
    except OSError:
        return None


def reply_block(out, n):
    """The replies.txt block of request n (for showing a body difference)."""
    lines, keep = [], False
    for ln in open(os.path.join(out, "replies.txt"), encoding="utf-8", errors="replace"):
        if ln.startswith("== "):
            keep = ln.split()[1] == n
        if keep:
            lines.append(ln.rstrip("\n"))
    return lines


def udiff(a, b, na, nb, limit=60):
    d = list(difflib.unified_diff(a, b, na, nb, lineterm="", n=2))
    return d[:limit] + (["... (%d more lines)" % (len(d) - limit)] if len(d) > limit else [])


def compare(name, a, b, pats):
    fails, declared = [], []
    ea, eb = read(os.path.join(a, "errors.txt")), read(os.path.join(b, "errors.txt"))
    if ea != eb:
        fails.append("error codes differ:\n" + "\n".join(udiff((ea or b"").decode().splitlines(), (eb or b"").decode().splitlines(), "A", "B")))
    bodies = sorted(set(f for f in os.listdir(a) if f.endswith(".msgp")) | set(f for f in os.listdir(b) if f.endswith(".msgp")),
                    key=lambda f: int(f.split("-")[0]))
    for f in bodies:
        if read(os.path.join(a, f)) != read(os.path.join(b, f)):
            n = f.split("-")[0]
            fails.append("reply %s differs:\n" % f + "\n".join(udiff(reply_block(a, n), reply_block(b, n), "A", "B")))
    sa, sb = read(os.path.join(a, "state.sql")), read(os.path.join(b, "state.sql"))
    if sa != sb:
        fails.append("end state differs:\n" + "\n".join(udiff((sa or b"").decode(errors="replace").splitlines(),
                                                            (sb or b"").decode(errors="replace").splitlines(), "A", "B")))
    la, lb = masked_log(a), masked_log(b)
    ta = [ln for ln in la if any(p.search(ln) for p in pats)]
    tb = [ln for ln in lb if any(p.search(ln) for p in pats)]
    if ta != tb:
        fails.append("log lines that scripts read differ (tier 1):\n" + "\n".join(udiff(ta, tb, "A", "B")))
    elif la != lb:
        declared.append("other log lines differ (tier 2: declare them in the commit message):\n" + "\n".join(udiff(la, lb, "A", "B")))
    return fails, declared


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("bin_a")
    ap.add_argument("bin_b")
    ap.add_argument("corpora", nargs="*")
    ap.add_argument("--out", help="the work dir (default a fresh temporary one, removed unless --keep or a difference)")
    ap.add_argument("--keep", action="store_true")
    a = ap.parse_args()
    bins = [os.path.abspath(a.bin_a), os.path.abspath(a.bin_b)]
    for bn in bins:
        if not os.access(bn, os.X_OK):
            sys.exit("server_replay_diff: %s isn't an executable" % bn)
    work = os.path.abspath(a.out) if a.out else tempfile.mkdtemp(prefix="server-replay-diff.")
    os.makedirs(work, exist_ok=True)
    pats = patterns()
    status = 0
    for c in corpora(a.corpora):
        name = os.path.basename(c.rstrip("/"))
        outs = [os.path.join(work, name, "a"), os.path.join(work, name, "b")]
        os.makedirs(os.path.join(work, name), exist_ok=True)
        procs = [start(bn, c, o) for bn, o in zip(bins, outs)]
        res = [p.communicate() for p in procs]
        if any(p.returncode for p in procs):
            for p, (o, _), bn in zip(procs, res, bins):
                if p.returncode:
                    print("FAIL  %s: %s --replay exited %d:\n%s" % (name, bn, p.returncode, o))
            status = 1
            continue
        fails, declared = compare(name, outs[0], outs[1], pats)
        n = sum(1 for ln in open(os.path.join(c, "requests.txt")) if ln[:1] not in ("#", "\n", ""))
        if fails:
            status = 1
            print("FAIL  %s (%d requests)" % (name, n))
            for f in fails + declared:
                print("  " + f.replace("\n", "\n    "))
        elif declared:
            status = max(status, 2)
            print("LOG   %s (%d requests): bodies, codes and state identical; log differs" % (name, n))
            for f in declared:
                print("  " + f.replace("\n", "\n    "))
        else:
            print("PASS  %s (%d requests): bodies, codes, state and log identical" % (name, n))
    print({0: "PASS: identical", 2: "LOG: only tier-2 log differences (declare them)", 1: "FAIL"}[status] + " (work dir %s)" % work)
    if status == 0 and not a.keep and not a.out:
        shutil.rmtree(work)
    return status


if __name__ == "__main__":
    sys.exit(main())
