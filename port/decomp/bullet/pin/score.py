#!/usr/bin/env python3
"""score.py BUILD_DIR... : exact-size matches of functions (Bullet block) and vtable sizes vs the game."""
import glob, subprocess, sys
import os
REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../.."))
LIB = os.path.join(REPO, "work/libSOA-3.7.0.so")
LO, HI = 0x261c000, 0x265b000
gf, gv = {}, {}
for l in subprocess.run(["nm", "-D", "--defined-only", "-S", LIB], capture_output=True, text=True).stdout.splitlines():
    p = l.split()
    if len(p) < 4: continue
    a, s, t, n = int(p[0], 16), int(p[1], 16), p[2], p[3]
    if t in "TtWw" and LO <= a < HI: gf[n] = s
    if n.startswith("_ZTV") and t in "VDdR": gv[n] = s
def load(d):
    f, v = {}, {}
    out = subprocess.run("nm -S --defined-only " + " ".join(glob.glob(d + "/*.o")), shell=True, capture_output=True, text=True).stdout
    for l in out.splitlines():
        p = l.split()
        if len(p) != 4: continue
        s, t, n = int(p[1], 16), p[2], p[3]
        if t in "TtWw": f[n] = s
        if n.startswith("_ZTV"): v[n] = s
    return f, v
verbose = "-v" in sys.argv
for d in [a for a in sys.argv[1:] if a != "-v"]:
    f, v = load(d)
    com = [n for n in gf if n in f]
    eq = [n for n in com if f[n] == gf[n]]
    vc = [n for n in gv if n in v and n.find("bt") >= 0]
    ve = [n for n in vc if v[n] == gv[n]]
    missing = [n for n in gf if n not in f]
    tot = sum(gf[n] for n in com); dif = sum(abs(gf[n]-f[n]) for n in com)
    print(f"{d}: funcs {len(eq)}/{len(com)} exact (game block {len(gf)}, missing {len(missing)}), sum|d|={dif}/{tot}; vtables {len(ve)}/{len(vc)}")
    if verbose:
        for n in sorted(com, key=lambda n: -abs(gf[n]-f[n]))[:25]:
            if gf[n] != f[n]: print(f"   {gf[n]:6d} {f[n]:6d} {n}")
        for n in vc:
            if v[n] != gv[n]: print(f"   vt {gv[n]} {v[n]} {n}")
        for n in missing[:15]: print("   missing", n)
