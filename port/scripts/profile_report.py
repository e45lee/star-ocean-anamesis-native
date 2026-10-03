#!/usr/bin/env python3
"""Summarize a SOA_PROFILE / SOA_COVERAGE run for picking porting targets.

Usage: profile_report.py DIR [DIR...] [--soa build/port/soa | --native-list FILE] [--top N]

DIR is what SOA_PROFILE / SOA_COVERAGE pointed at (functions.tsv, coverage.tsv, stacks.folded,
calls.tsv, meta.txt). Several DIRs (e.g. the smoke run and a longer session) are merged: samples
and call counts add up, coverage is the union.

Sections:
  - summary: where the time went (guest code, native replacements, HLE busy, HLE waiting)
  - top functions by guest self time (inclusive time from the sampled call stacks)
  - families by guest time, and by executed-function count: executed vs total functions/bytes
  - host time: HLE imports and native replacements
  - native coverage: executed functions / time already native
  - large families that never executed (candidates to stub, not port)

Families are the demangled prefix: a namespace plus its class for Aska::/Framework::/std::
(e.g. "Aska::Yayoi", "std::__ndk1"), the class for other methods ("CUIUtility"), and the C prefix
for free functions ("sqlite3_*"). Local (unexported) functions are named FUN_<ghidra address> and
assigned to "~<family>" of the nearest preceding exported function, as a hint only (same object
file, most of the time).
"""
import argparse
import collections
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# HLE imports where a sampled thread is waiting rather than working.
IDLE_HLE = {
    "native_wait",  # a native replacement blocked in a host wait (prof_native_wait)
    "pthread_cond_wait", "pthread_cond_timedwait", "sem_wait", "sem_timedwait", "nanosleep", "usleep", "sleep",
    "ALooper_pollAll", "ALooper_pollOnce", "epoll_wait", "poll", "select", "pthread_join", "sched_yield",
    "eglSwapBuffers", "clock_nanosleep", "futex", "syscall", "read", "recv", "recvfrom", "accept",
    "pthread_mutex_lock", "slCreateEngine",
}
NAMESPACES = {"Aska", "Framework", "std", "__cxxabiv1", "cocos2d", "Json", "msgpack", "picojson", "google", "(anonymous namespace)"}


def qualified_name(dem):
    """Demangled function -> its qualified name, without return type and parameters."""
    s = dem.replace("(anonymous namespace)", "{anon}")
    depth, end, i = 0, len(s), 0
    while i < len(s):
        if s.startswith("operator", i) and (i == 0 or s[i - 1] in ": "):
            end = i + len("operator")
            break
        ch = s[i]
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        elif ch == "(" and depth == 0:
            end = i
            break
        i += 1
    prefix = s[:end]
    depth, cut = 0, 0
    for j, ch in enumerate(prefix):
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        elif ch == " " and depth == 0:
            cut = j + 1
    return prefix[cut:]


def split_qualified(q):
    out, cur, depth, i = [], "", 0, 0
    while i < len(q):
        ch = q[i]
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        if depth == 0 and q.startswith("::", i):
            out.append(cur)
            cur, i = "", i + 2
            continue
        cur += ch
        i += 1
    out.append(cur)
    return [c for c in out if c]


def strip_templates(s):
    out, depth = "", 0
    for ch in s:
        if ch == "<":
            if depth == 0:
                out += "<>"
            depth += 1
        elif ch == ">":
            depth -= 1
        elif depth == 0:
            out += ch
    return out


def family_of(dem):
    if dem.startswith("FUN_"):
        return None
    for pre in ("non-virtual thunk to ", "virtual thunk to "):
        if dem.startswith(pre):
            dem = dem[len(pre):]
    parts = split_qualified(qualified_name(dem))
    comps = [strip_templates(p).replace("{anon}", "(anonymous)") for p in parts[:-1]]
    if not comps:
        base = strip_templates(parts[0] if parts else dem)
        m = re.match(r"_*([A-Za-z]+[0-9]*_)", base)
        if m:
            return m.group(1) + "*"
        return "(free functions)"
    if comps[0] in NAMESPACES and len(comps) >= 2:
        return comps[0] + "::" + comps[1]
    return comps[0]


def demangle_all(names):
    mangled = [n for n in names if n.startswith("_Z")]
    res = {n: n for n in names}
    if mangled:
        try:
            p = subprocess.run(["c++filt"], input="\n".join(mangled), capture_output=True, text=True, check=True)
            for m, d in zip(mangled, p.stdout.split("\n")):
                res[m] = d
        except (OSError, subprocess.CalledProcessError):
            pass
    return res


def load_tsv(path):
    rows = []
    if not os.path.exists(path):
        return rows
    for line in open(path):
        if line.startswith("#") or not line.strip():
            continue
        rows.append(line.rstrip("\n").split("\t"))
    return rows


def fmt_bytes(n):
    return f"{n / 1024:.0f}K" if n < 1024 * 1024 else f"{n / 1048576:.1f}M"


def table(rows, headers, aligns=None):
    widths = [len(h) for h in headers]
    for r in rows:
        for i, c in enumerate(r):
            widths[i] = max(widths[i], len(str(c)))
    aligns = aligns or ["<"] + [">"] * (len(headers) - 1)
    line = lambda r: "  ".join(f"{str(c):{a}{w}}" for c, a, w in zip(r, aligns, widths))
    out = [line(headers), "  ".join("-" * w for w in widths)]
    out += [line(r) for r in rows]
    return "\n".join(out)


def trunc(s, n):
    return s if len(s) <= n else s[: n - 1] + "…"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("dirs", nargs="+")
    ap.add_argument("--soa", default=os.path.join(REPO, "build/port/soa"), help="soa binary (for --list-native)")
    ap.add_argument("--native-list", help="output of `soa --list-native` (instead of running --soa)")
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--width", type=int, default=90, help="max width of function names")
    a = ap.parse_args()

    # ---- function table
    funcs = []  # (offset, size, name)
    for r in load_tsv(os.path.join(a.dirs[0], "functions.tsv")):
        funcs.append((int(r[0], 16), int(r[1]), r[3]))
    if not funcs:
        sys.exit(f"{a.dirs[0]}/functions.tsv missing")
    by_name = {n: i for i, (_, _, n) in enumerate(funcs)}
    by_off = {o: i for i, (o, _, _) in enumerate(funcs)}
    dem = demangle_all([n for _, _, n in funcs])
    fam = []
    last = "(before first export)"
    for o, s, n in funcs:
        f = family_of(dem[n])
        if f is None:
            fam.append("~" + last)
        else:
            fam.append(f)
            last = f
    exported = [not n.startswith("FUN_") for _, _, n in funcs]

    # ---- native registry
    natives = {}  # func index -> symbol
    native_lines = None
    if a.native_list:
        native_lines = open(a.native_list).read().splitlines()
    elif os.path.exists(a.soa):
        try:
            native_lines = subprocess.run([a.soa, "--list-native"], capture_output=True, text=True, timeout=30).stdout.splitlines()
        except (OSError, subprocess.TimeoutExpired):
            native_lines = None
    for line in native_lines or []:
        sym = line.split("\t")[0]
        i = by_off.get(int(sym[1:], 16)) if sym.startswith("@") else by_name.get(sym)
        if i is not None:
            natives[i] = sym

    # ---- runs
    executed = set()
    calls = collections.Counter()  # (kind, name) -> calls
    self_s = collections.Counter()  # frame name -> samples (leaf)
    incl_s = collections.Counter()  # func index -> samples (inclusive)
    meta_total = collections.Counter()
    fam_incl = collections.Counter()
    thread_busy = collections.Counter()  # thread root -> busy samples
    truncated = 0
    for d in a.dirs:
        for r in load_tsv(os.path.join(d, "coverage.tsv")):
            i = by_off.get(int(r[0], 16))
            if i is not None:
                executed.add(i)
        for r in load_tsv(os.path.join(d, "calls.tsv")):
            calls[(r[0], r[3])] += int(r[1])
        mp = os.path.join(d, "meta.txt")
        if os.path.exists(mp):
            for line in open(mp):
                k, v = line.split()
                meta_total[k] += float(v)
        sp = os.path.join(d, "stacks.folded")
        if os.path.exists(sp):
            for line in open(sp):
                st, n = line.rstrip("\n").rsplit(" ", 1)
                n = int(n)
                frames = [f for f in st.split(";") if f not in ("[hle]<return-to-host>", "[native]<return-to-host>")]
                leaf = frames[-1]
                self_s[leaf] += n
                if leaf.startswith("[hle]") and leaf[5:] in IDLE_HLE:
                    continue  # not work: waiting in host code
                root = frames[0][7:]
                if root == "_ZN4Aska6Thread4MainEPv":  # Aska threads: name them by their Handler
                    root = next((f for f in frames[1:] if f != root and not f.startswith("[")), root)
                thread_busy[root] += n
                if "[truncated]" in frames:
                    truncated += n
                seen, fseen = set(), set()
                for f in frames[1:]:
                    i = by_name.get(f)
                    if i is not None and i not in seen:
                        seen.add(i)
                        incl_s[i] += n
                        if fam[i] not in fseen:
                            fseen.add(fam[i])
                            fam_incl[fam[i]] += n

    # functions executed per coverage, plus functions seen in samples (in case coverage was off)
    have_cov = any(os.path.exists(os.path.join(d, "coverage.tsv")) for d in a.dirs)
    for f in self_s:
        i = by_name.get(f)
        if i is not None:
            executed.add(i)
    native_called = {i for i, s in natives.items() if calls.get(("native", s))}
    for (kind, name), n in calls.items():
        if kind == "native" and name in by_name:
            native_called.add(by_name[name])

    extra = [f[8:] for f in self_s if f.startswith("[native]") and f[8:] not in dem]
    dem.update(demangle_all(extra))

    # ---- sample categories
    guest_self = collections.Counter()
    native_self = collections.Counter()
    hle_busy, hle_idle, other = collections.Counter(), collections.Counter(), collections.Counter()
    for f, n in self_s.items():
        if f.startswith("[native]"):
            native_self[f[8:]] += n
        elif f.startswith("[hle]"):
            (hle_idle if f[5:] in IDLE_HLE else hle_busy)[f[5:]] += n
        elif f in by_name:
            guest_self[by_name[f]] += n
        else:
            other[f] += n
    tg, tn, thb, thi, to = (sum(c.values()) for c in (guest_self, native_self, hle_busy, hle_idle, other))
    busy = tg + tn + thb + to
    pct = lambda x, t: f"{100.0 * x / t:.1f}%" if t else "-"

    out = []
    P = out.append
    P("# SOA guest profile")
    P("")
    P(f"runs: {', '.join(a.dirs)}")
    if meta_total:
        P(f"wall time {meta_total['seconds']:.0f} s, {int(meta_total['samples'])} samples at {int(meta_total['hz'] / max(1, len(a.dirs)))} Hz"
          f" across all guest threads; sampler CPU {meta_total['sampler_cpu_s']:.1f} s")
    P("")
    P("## Where the time goes (samples on all guest threads)")
    P("")
    P(table([
        ["guest ARM64 code (JIT)", tg, pct(tg, busy)],
        ["native replacements", tn, pct(tn, busy)],
        ["HLE imports, working (GL, libc, ...)", thb, pct(thb, busy)],
        ["other ([truncated]/[unknown] leaf)", to, pct(to, busy)],
        ["= busy total", busy, "100%"],
        ["HLE imports, waiting (cond/sem wait, sleep, poll)", thi, "(idle)"],
    ], ["category", "samples", "% busy"]))
    P("")
    total_exec = len(executed | native_called)
    if busy:
        P(f"Stacks: {pct(truncated, busy)} of busy samples have a truncated stack (unwinding failed part-way).")
        P("")
    P("## Busy samples by thread (outermost guest function)")
    P("")
    P(table([[n, pct(n, busy), trunc(dem.get(k, k), a.width)] for k, n in thread_busy.most_common(12)], ["samples", "%busy", "thread entry"], [">", ">", "<"]))
    P("")
    P("## Native coverage")
    P("")
    P(f"- function table: {len(funcs)} entries ({sum(exported)} exported, {len(funcs) - sum(exported)} local)")
    if have_cov:
        P(f"- executed guest functions: {len(executed)} ({pct(len(executed), len(funcs))} of the table),"
          f" {fmt_bytes(sum(funcs[i][1] for i in executed))} of code")
    P(f"- native replacements registered: {len(natives)} (resolved in this library); called during the run: {len(native_called)}")
    if total_exec:
        P(f"- executed functions that are native: {len(native_called)} / {total_exec} = {pct(len(native_called), total_exec)}")
    if tg + tn:
        P(f"- time in native replacements vs guest code: {tn} / {tg + tn} samples = {pct(tn, tg + tn)}")
    P("")

    P(f"## Top {a.top} functions by guest self time")
    P("")
    rows = []
    for i, n in guest_self.most_common(a.top):
        rows.append([n, pct(n, busy), incl_s[i], trunc(dem[funcs[i][2]], a.width), fam[i]])
    P(table(rows, ["self", "%busy", "incl", "function", "family"], [">", ">", ">", "<", "<"]))
    P("")

    P(f"## Top {a.top} functions by inclusive time (guest + native, excluding HLE waits)")
    P("")
    rows = []
    for i, n in incl_s.most_common(a.top):
        rows.append([n, pct(n, busy), guest_self[i], trunc(dem[funcs[i][2]], a.width), fam[i]])
    P(table(rows, ["incl", "%busy", "self", "function", "family"], [">", ">", ">", "<", "<"]))
    P("")

    # ---- families
    fstat = collections.defaultdict(lambda: collections.Counter())
    for i, (o, s, n) in enumerate(funcs):
        F = fstat[fam[i]]
        F["fns"] += 1
        F["bytes"] += s
        if i in executed or i in native_called:
            F["exec"] += 1
            F["exec_bytes"] += s
        if i in natives:
            F["native"] += 1
        F["self"] += guest_self.get(i, 0)
        if i in natives:
            F["self_native"] += native_self.get(natives[i], 0)

    def fam_rows(keys):
        rows = []
        for k in keys:
            F = fstat[k]
            rows.append([trunc(k, 44), F["self"], pct(F["self"], busy), fam_incl.get(k, 0), f"{F['exec']}/{F['fns']}",
                         f"{fmt_bytes(F['exec_bytes'])}/{fmt_bytes(F['bytes'])}", F["native"]])
        return rows

    fam_heads = ["family", "self", "%busy", "incl", "exec/fns", "exec/bytes", "native"]
    P(f"## Top {a.top} families by guest self time")
    P("")
    P(table(fam_rows(sorted(fstat, key=lambda k: -fstat[k]["self"])[: a.top]), fam_heads))
    P("")
    P(f"## Top {a.top} families by executed functions")
    P("")
    P(table(fam_rows(sorted(fstat, key=lambda k: (-fstat[k]["exec"], -fstat[k]["self"]))[: a.top]), fam_heads))
    P("")
    P(f"## Top {a.top} families by executed code bytes (exported families only)")
    P("")
    P(table(fam_rows([k for k in sorted(fstat, key=lambda k: -fstat[k]["exec_bytes"]) if not k.startswith("~")][: a.top]), fam_heads))
    P("")

    P("## Host time: HLE imports (busy) and native replacements")
    P("")
    rows = [["hle", n, pct(n, busy), calls.get(("hle", k), 0), k] for k, n in hle_busy.most_common(25)]
    rows += [["native", n, pct(n, busy), calls.get(("native", k), 0), trunc(dem.get(k, k), a.width)] for k, n in native_self.most_common(15)]
    P(table(rows, ["kind", "samples", "%busy", "calls", "function"], ["<", ">", ">", ">", "<"]))
    P("")
    P("HLE waiting (idle): " + ", ".join(f"{k} {n}" for k, n in hle_idle.most_common(8)))
    P("")
    top_calls = sorted(((n, k) for k, n in calls.items() if k[0] == "native"), reverse=True)[:15]
    if top_calls:
        P("Most-called native replacements: " + ", ".join(f"{trunc(dem.get(k[1], k[1]), 50)} {n}" for n, k in top_calls))
        P("")

    if have_cov:
        P(f"## Largest families never executed (stub/skip candidates; top {a.top} by bytes)")
        P("")
        dead = [k for k in fstat if fstat[k]["exec"] == 0 and not k.startswith("~")]
        dead.sort(key=lambda k: -fstat[k]["bytes"])
        P(table([[trunc(k, 50), fstat[k]["fns"], fmt_bytes(fstat[k]["bytes"])] for k in dead[: a.top]], ["family", "fns", "bytes"]))
        P("")
    print("\n".join(out))


if __name__ == "__main__":
    main()
