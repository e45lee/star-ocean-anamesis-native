#!/usr/bin/env -S sh -c 'exec "${0%/*}/../../tools/py" "$0" "$@"'
"""Rank the guest families a flow executes that baseline runs don't.

Usage: coverage_diff.py FLOW_DIR [BASE_DIR...] [--top N]

FLOW_DIR and each BASE_DIR hold a SOA_COVERAGE run (coverage.tsv, functions.tsv). Prints the
families (grouped like profile_report.py) of functions executed in FLOW_DIR and in none of the
BASE_DIRs, by executed code bytes, with a few example functions each.
Default bases: work/profile/{smoke,session,session2}.
"""
import collections
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from profile_report import demangle_all, family_of  # noqa: E402

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))


def executed(d):
    out = set()
    with open(os.path.join(d, "coverage.tsv")) as f:
        for line in f:
            if line.startswith("#"):
                continue
            p = line.rstrip("\n").split("\t")
            if len(p) >= 3:
                out.add(p[2])
    return out


def sizes(d):
    out = {}
    with open(os.path.join(d, "functions.tsv")) as f:
        for line in f:
            if line.startswith("#"):
                continue
            p = line.rstrip("\n").split("\t")
            if len(p) >= 4:
                out[p[3]] = int(p[1])
    return out


def main():
    args = sys.argv[1:]
    top = 40
    if "--top" in args:
        i = args.index("--top")
        top = int(args[i + 1])
        del args[i:i + 2]
    if not args:
        sys.exit(__doc__)
    flow, bases = args[0], args[1:] or [os.path.join(REPO, "work/profile", b) for b in ("smoke", "session", "session2")]
    new = executed(flow)
    for b in bases:
        if os.path.exists(os.path.join(b, "coverage.tsv")):
            new -= executed(b)
    size = sizes(flow)
    dem = demangle_all(sorted(new))
    fam = collections.defaultdict(list)
    for n in new:
        fam[family_of(dem[n]) or "(local FUN_*)"].append(n)
    rows = sorted(fam.items(), key=lambda kv: -sum(size.get(n, 0) for n in kv[1]))
    print(f"# {flow}: {len(new)} functions executed that {', '.join(os.path.basename(b.rstrip('/')) for b in bases)} never ran")
    print(f"{'family':45} {'fns':>5} {'bytes':>8}  examples")
    for f, ns in rows[:top]:
        ex = ", ".join(sorted((dem[n].split("(")[0] for n in ns), key=lambda s: -size.get(s, 0))[:3])
        print(f"{f[:45]:45} {len(ns):5} {sum(size.get(n, 0) for n in ns):8}  {ex[:110]}")


if __name__ == "__main__":
    main()
