#!/usr/bin/env -S sh -c 'exec "${0%/*}/../../tools/py" "$0" "$@"'
"""The hot methods of one subsystem, by class, with their callers (port/PLAN.md task 6).

Usage: hot_methods.py SUBSYSTEM NAME=DIR [NAME=DIR...] [--top N] [--callers K] [--markdown]

Each DIR is a SOA_PROFILE + SOA_COVERAGE run (as for rebuild_queue.py, which assigns every guest function to a
subsystem the same way). Prints the subsystem's classes (profile_report.py's families) by guest self time and,
per class, its methods by self samples: per flow, the inclusive samples (the method anywhere on the stack), and
the K hottest immediate callers outside the method itself (caller -> samples that went through that call).
This is the list a code agent starts from: the biggest wins and who drives them.
"""
import argparse
import collections
import os

from profile_report import IDLE_HLE, demangle_all, family_of, load_tsv
from rebuild_queue import scaffolded_scopes, subsystem_of_family


def short(dem, n=110):
    return dem if len(dem) <= n else dem[: n - 3] + "..."


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("subsystem")
    ap.add_argument("runs", nargs="+", help="NAME=DIR")
    ap.add_argument("--top", type=int, default=12, help="methods per class")
    ap.add_argument("--classes", type=int, default=40, help="classes")
    ap.add_argument("--callers", type=int, default=3)
    ap.add_argument("--markdown", action="store_true")
    a = ap.parse_args()
    runs = []
    for r in a.runs:
        name, _, d = r.partition("=")
        runs.append((name, d) if d else (os.path.basename(os.path.normpath(r)), r))

    funcs = [(int(r[0], 16), int(r[1]), r[3]) for r in load_tsv(os.path.join(runs[0][1], "functions.tsv"))]
    dem = demangle_all([n for _, _, n in funcs])
    scopes = scaffolded_scopes()
    fam, sub = {}, {}
    last = "(before first export)"
    for o, s, n in funcs:
        f = family_of(dem[n])
        if f is None:
            f = "~" + last
        else:
            last = f
        fam[n] = f
        owner = next((s for s, rx in scopes if not n.startswith("FUN_") and rx.search(dem[n])), None)
        sub[n] = owner or subsystem_of_family(f.lstrip("~")) or subsystem_of_family(f) or "(unassigned)"
    vaddr = {n: o for o, _, n in funcs}

    self_s = collections.Counter()
    self_run = collections.defaultdict(collections.Counter)
    incl = collections.Counter()
    callers = collections.defaultdict(collections.Counter)
    busy = 0
    for name, d in runs:
        for line in open(os.path.join(d, "stacks.folded")):
            st, n = line.rstrip("\n").rsplit(" ", 1)
            n = int(n)
            frames = [f for f in st.split(";")[1:] if f not in ("[hle]<return-to-host>", "[native]<return-to-host>")]
            if not frames:
                continue
            leaf = frames[-1]
            if leaf.startswith("[hle]") and leaf[5:] in IDLE_HLE:
                continue
            busy += n
            if sub.get(leaf) == a.subsystem:
                self_s[leaf] += n
                self_run[name][leaf] += n
            seen = set()
            for i, f in enumerate(frames):
                if sub.get(f) != a.subsystem or f in seen:
                    continue
                seen.add(f)
                incl[f] += n
                j = i - 1
                while j >= 0 and frames[j] == f:
                    j -= 1
                if j >= 0:
                    callers[f][frames[j]] += n

    by_class = collections.defaultdict(list)
    for f in set(self_s) | set(incl):
        by_class[fam[f].lstrip("~")].append(f)
    cls_self = {c: sum(self_s[f] for f in fs) for c, fs in by_class.items()}
    total = sum(cls_self.values())
    names = [n for n, _ in runs]
    print(f"# `{a.subsystem}`: {total} guest self samples ({100.0 * total / busy:.1f}% of {busy} busy), "
          f"{len(self_s)} methods with self samples, {len(by_class)} classes\n")
    for c in sorted(by_class, key=lambda c: -cls_self[c])[: a.classes]:
        fs = sorted(by_class[c], key=lambda f: (-self_s[f], -incl[f]))
        print(f"## {c}: {cls_self[c]} self ({100.0 * cls_self[c] / busy:.2f}%)\n")
        if a.markdown:
            print("| Method | vaddr | Self | " + " | ".join(names) + " | Incl | Callers (samples) |")
            print("|---|---|---|" + "---|" * len(names) + "---|---|")
        for f in fs[: a.top]:
            cl = ", ".join(f"{short(dem.get(x, x), 70)} ({w})" for x, w in callers[f].most_common(a.callers))
            row = [short(dem[f]), f"{vaddr[f]:x}", str(self_s[f])] + [str(self_run[n][f]) for n in names] + [str(incl[f]), cl]
            print(("| " + " | ".join(row) + " |") if a.markdown else "  ".join(row))
        if len(fs) > a.top:
            rest = sum(self_s[f] for f in fs[a.top:])
            print(f"\n... {len(fs) - a.top} more methods, {rest} self samples")
        print()


if __name__ == "__main__":
    main()
