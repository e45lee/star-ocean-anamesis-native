#!/usr/bin/env python3
"""Inventory for rebasing the port from the 3.8.0 offline libSOA.so onto 3.7.0 (docs/history/PLAN-rebase-370.md, P0).

History tool once the rebase's inventory moved to docs/history/ (P4); the port runs 3.7.0 only.

Writes docs/history/REBASE-370.md (the checklist P1/P2/P3/P4 work from) and the full tables under docs/history/rebase-370/:
  natives.tsv           every `soa --list-native` row: family, primary class, tags, 3.7.0 status
  address_bound.tsv     the `@0x...` natives remapped through the containing function
  hardcoded.tsv         hard-coded lib addresses / symbol+offset in hand-written native sources
  gen_files.tsv         generated files and their generators
  refs-380.tsv          every 3.8.0 / XAPK / playcore / home_sa reference outside emulator-viewer/
  coverage-*.tsv        3.7.0 coverage (soa-emu) and 3.8.0 coverage (soa) summaries, derived from
                        SOA_COVERAGE / SOA_PROFILE runs (the raw runs stay in work/rebase/)

Inputs: work/verdiff/{changed,only,layout}.tsv (tools/verdiff.py), the two libraries
(work/libSOA-3.7.0.so and the 3.8.0 lib), the sources, and `build/port/soa --list-native` (or, when soa isn't built,
the symbol and note columns of the previous docs/history/rebase-370/natives.tsv: a clean checkout works).

Usage:
  tools/rebase_inventory.py [--soa build/port/soa | --list-native FILE] [--check]
  tools/rebase_inventory.py --coverage KIND=DIR ...   re-derive a coverage summary from a raw run
        KIND: emu-seeded, emu-newplayer (soa-emu, 3.7.0), port-restore, port-tutorial (soa, 3.8.0)
--check: exit 1 when a native, a generated file, a client-changes.md heading, a restore module or a
3.8.0-specific server-rules section has no classification, or when hand-written code (outside the
3.8.0-only modules ALLOWED_380) still holds a 3.8.0 address (and print what is missing).

Which lib an address belongs to (since P2-e the tree targets 3.7.0): a generated file says so in
its header (tools/genlib.py's stamp `// libSOA.so: <path> (<version>, sha256 ...)`); a literal in
hand-written code is resolved in both libs and scored by how exactly it lands (a function start,
the start of a string, a GOT slot, an object; a string the line quotes or a symbol it names wins
outright); the better fit is its lib (ties: the file's majority). `@0x` natives: a function start
in one lib only. hardcoded.tsv records the lib and the other lib's counterpart of every value.
"""
import argparse
import bisect
import collections
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
try:
    import capstone  # noqa: F401
    import elftools  # noqa: F401
except ImportError:  # re-run under the repository's venv (capstone, pyelftools)
    venv = os.path.join(REPO, ".venv", "bin", "python")
    if os.path.exists(venv) and os.path.realpath(sys.prefix) != os.path.realpath(os.path.join(REPO, ".venv")):
        os.execv(venv, [venv] + sys.argv)
    raise
sys.path.insert(0, os.path.join(REPO, "tools"))
import verdiff  # noqa: E402

LIB380 = os.path.join(REPO, "work/extracted/config.arm64_v8a/lib/arm64-v8a/libSOA.so")
LIB370 = os.path.join(REPO, "work/libSOA-3.7.0.so")
VD = os.path.join(REPO, "work/verdiff")
NATIVE = os.path.join(REPO, "port/src/native")
OUTDIR = os.path.join(REPO, "docs/history/rebase-370")
DOC = os.path.join(REPO, "docs/history/REBASE-370.md")
SNAP = os.path.join(OUTDIR, "natives.tsv")   # its symbol and note columns are the --list-native snapshot
HEAT_RUN = "port-restore"     # the coverage run whose native call counts / samples mark "hot"
HOT_CALLS, HOT_SAMPLES = 100000, 20

missing = []                  # --check failures


def rel(p):
    return os.path.relpath(p, REPO)


def demangle(names):
    if not names:
        return []
    r = subprocess.run(["c++filt"], input="\n".join(names), capture_output=True, text=True).stdout
    return r.split("\n")[:len(names)]


def read_tsv(path, header=True):
    rows = []
    with open(path) as f:
        lines = f.read().split("\n")
    if header:
        lines = lines[1:]
    for l in lines:
        if l and not l.startswith("#"):
            rows.append(l.split("\t"))
    return rows


def md_escape(s):
    return s.replace("|", "\\|")


def short(s, n=110):
    return s if len(s) <= n else s[:n - 1] + "…"


# ---------------------------------------------------------------------------------------------
# Images: both libs with verdiff's naming (exports, plus unnamed statics "anon:<prev>#k" and
# std::function lambdas "lambda:<encl>#k.slot", paired by name across builds).
class Img:
    def __init__(self, path):
        self.I = verdiff.Image(path)
        self.anon = verdiff.anon_names(self.I)
        for a, n in self.anon.items():
            self.I.funcs.setdefault(n, (a, self.I.extent(a)))
        self.name_at = dict(self.I.by_addr)
        self.name_at.update({a: n for a, n in self.anon.items() if a not in self.name_at})
        self.starts = self.I.starts
        objs = sorted((a, s, n) for n, (a, s) in self.I.objects.items() if s)
        self.obj_starts = [o[0] for o in objs]
        self.objs = objs
        self.lo = min(s["p_vaddr"] for s in self.I.segs)
        self.hi = max(s["p_vaddr"] + s["p_memsz"] for s in self.I.segs)
        self.text = self.I.secs[".text"]

    def func_of(self, va):
        """(name, start, offset) of the function containing va, or None."""
        if not (self.text[0] <= va < self.text[1]):
            return None
        i = bisect.bisect_right(self.starts, va) - 1
        if i < 0:
            return None
        s = self.starts[i]
        if va >= s + self.I.extent(s):
            return None
        n = self.name_at.get(s)
        return (n, s, va - s) if n else None

    def obj_of(self, va):
        i = bisect.bisect_right(self.obj_starts, va) - 1
        if i < 0:
            return None
        a, s, n = self.objs[i]
        return (n, a, va - a) if va < a + s else None

    def section(self, va):
        for n, (a, b) in self.I.secs.items():
            if a <= va < b:
                return n
        return None

    def resolve(self, va):
        """What a library address points at: (kind, key, offset, description) or None.
        kind fn: key = function name; obj: object name; str: the whole NUL-terminated .rodata
        string containing va; got: the GOT slot's symbol; near: the closest exported symbol below
        (data with no object around it)."""
        sec = self.section(va)
        if sec is None:
            return None
        if sec == ".text":
            f = self.func_of(va)
            return ("fn",) + (f[0], f[2], "%s+%#x" % (f[0], f[2])) if f else None
        o = self.obj_of(va)
        if o:
            return ("obj", o[0], o[2], "%s+%#x" % (o[0], o[2]))
        if sec == ".got":
            slot = va & ~7
            n = self.I.got2name.get(slot)
            return ("got", n, va - slot, "GOT[%s]" % n) if n else None
        if sec == ".rodata":
            s0 = va
            while s0 > self.I.secs[".rodata"][0] and self.I.read(s0 - 1, 1) != b"\0" and va - s0 < 4096:
                s0 -= 1
            s = self.I.cstr(s0, 4096) or b""
            if len(s) >= 4 and verdiff.printable(s) and va - s0 <= len(s):
                return ("str", s, va - s0, "str:%r+%d" % (s[:40].decode("latin1"), va - s0))
            return None
        if sec in (".data", ".bss", ".data.rel.ro", ".init_array", ".fini_array"):
            # a vtable without a symbol (std::function lambdas): name it by a code pointer next to it
            cands = []
            for k in (0, 8, 16, 24, 32, 40, 48, 56, 64, -8, -16):
                r = self.I.reloc_at.get(va + k)
                if not r:
                    continue
                tn = None
                if r[0] == "rel" and self.text[0] <= r[1] < self.text[1]:
                    tn = self.name_at.get(r[1])
                elif r[0] == "sym" and r[1] in self.I.funcs:
                    tn = r[1]
                if tn:
                    cands.append((tn, k))
            if cands:
                return ("slot", tuple(cands), 0, "vtable with slot %s (at %+d)" % cands[0])
            i = bisect.bisect_right(self.I.addrs, va) - 1
            if i >= 0 and va - self.I.addrs[i] < 0x1000:
                a = self.I.addrs[i]
                return ("near", self.I.by_addr[a], va - a, "%s+%#x (nearest symbol)" % (self.I.by_addr[a], va - a))
        return None

    def find(self, kind, key, off, changed):
        """The 3.7.0 address of what resolve() found in the other build (as a string), or why not."""
        if kind == "fn":
            if key in changed:
                return "changed"
            o = self.I.funcs.get(key)
            return "%#x" % (o[0] + off) if o else "none"
        if kind == "slot":
            if not hasattr(self, "_sites"):
                self._sites = collections.defaultdict(list)
                for site, r in self.I.reloc_at.items():
                    if r[0] == "rel":
                        self._sites[r[1]].append(site)
                    elif r[1] in self.I.funcs:
                        self._sites[self.I.funcs[r[1]][0]].append(site)
            # the first code slot whose target is stored in exactly one data word of 3.7.0
            amb = 0
            for name, k in key:
                o = self.I.funcs.get(name)
                sites = [s for s in self._sites.get(o[0], []) if self.section(s) in (".data.rel.ro", ".data")] if o else []
                if len(sites) == 1:
                    return "%#x" % (sites[0] - k)
                amb = max(amb, len(sites))
            return "none" if not amb else "ambiguous (every slot's target is shared)"
        if kind == "near":
            o = self.I.objects.get(key) or self.I.funcs.get(key)
            if not o:
                o = next(((a, 0) for a, n in self.I.by_addr.items() if n == key), None)
            return ("%#x (nearest-symbol guess: check)" % (o[0] + off)) if o else "none"
        if kind == "obj":
            o = self.I.objects.get(key) or self.I.funcs.get(key)
            if not o and key in self.I.by_addr.values():
                o = next(((a, 0) for a, n in self.I.by_addr.items() if n == key), None)
            return "%#x" % (o[0] + off) if o else "none"
        if kind == "got":
            if not hasattr(self, "_got_by_name"):
                self._got_by_name = {n: a for a, n in self.I.got2name.items()}
            a = self._got_by_name.get(key)
            return "%#x" % (a + off) if a else "none"
        if kind == "str":
            if not hasattr(self, "_rodata"):
                a, b = self.I.secs[".rodata"]
                self._rodata = (a, self.I.read(a, b - a))
            base, data = self._rodata
            pat = b"\0" + key + b"\0"
            i = data.find(pat)
            if i < 0 and data.startswith(key + b"\0"):
                i = -1
                return "%#x" % (base + off)
            if i < 0:
                return "string not in 3.7.0"
            if data.find(pat, i + 1) >= 0:
                return "%#x (string occurs more than once)" % (base + i + 1 + off)
            return "%#x" % (base + i + 1 + off)
        return "?"

    def fit(self, va, line=""):
        """How exactly va lands in this lib (0 = not at all .. 9 = the line names what is there),
        and resolve()'s result."""
        r = self.resolve(va)
        if not r:
            return 0, None
        kind, key, off, _ = r
        sc = {"fn": 3 if off == 0 else (1 if off % 4 == 0 else 0), "str": 3 if off == 0 else 1, "got": 3 if off == 0 else 0,
              "obj": 3 if off == 0 else 1, "slot": 2, "near": 1}.get(kind, 0)
        if kind == "slot" and any(k == 0 for _, k in key):
            sc = 3     # a std::function / class vtable's address point (its first code slot)
        if kind == "obj" and key.startswith("_ZTV") and off == 0:
            sc = 1     # a vtable symbol's start is not what code points at (the address point is +0x10)
        if kind == "str" and len(key) - off >= 2:     # the line quotes the string (or its tail) at va
            tail = key[off:].decode("latin1")
            if '"%s"' % tail in line or ('"%s' % tail[:24] in line and len(tail) >= 6):
                sc = 9
        if kind == "fn" and off == 0 and isinstance(key, str):
            base = re.sub(r"^(anon|lambda):", "", key).split("#")[0]
            nm = verdiff.demangle([base])[0] if base.startswith("_Z") else base
            short_nm = re.sub(r"\(.*", "", nm).split("::")[-1]
            if base in line or (len(short_nm) >= 6 and re.search(r"\b%s\b" % re.escape(short_nm), line)):
                sc = 9
        return sc, r

    def insn(self, va):
        b = self.I.read(va, 4)
        if not b:
            return "?"
        for i in verdiff.Cs(verdiff.CS_ARCH_ARM64, verdiff.CS_MODE_ARM).disasm(b, va):
            return i.mnemonic
        return "?"


# ---------------------------------------------------------------------------------------------
def load_list_native(args):
    rows = None
    if args.list_native:
        rows = read_tsv(args.list_native, header=False)
    else:
        soa = args.soa or os.path.join(REPO, "build/port/soa")
        if os.path.exists(soa):
            r = subprocess.run([soa, "--list-native"], capture_output=True, text=True, cwd=REPO, timeout=300)
            if r.returncode == 0 and r.stdout.count("\n") > 1000:
                rows = [l.split("\t") for l in r.stdout.split("\n") if l]
        if rows is None:
            print("no soa build: natives from the snapshot %s" % rel(SNAP), file=sys.stderr)
            rows = [(r[0], r[8]) for r in read_tsv(SNAP, header=False) if r[0] != "symbol"]
    out = []
    for r in rows:
        note = r[1] if len(r) > 1 else ""
        out.append((r[0], note))
    return out


def load_verdiff():
    changed = {}
    for r in read_tsv(os.path.join(VD, "changed.tsv")):
        sym, dem, cls, oa, na, os_, ns, nd, same, what = r[:10]
        aliases = r[10].split(",") if len(r) > 10 and r[10] else []
        e = dict(symbol=sym, dem=dem, cls=cls, old_addr=oa, new_addr=na, old_size=int(os_), new_size=int(ns),
                 diff=int(nd), what=what, diff_file="work/verdiff/fn/%s.diff" % re.sub(r"[^A-Za-z0-9_]", "_", sym)[:150])
        changed[sym] = e
        for a in aliases:
            changed[a] = e
    only = {"3.7.0": {}, "3.8.0": {}}
    for r in read_tsv(os.path.join(VD, "only.tsv")):
        only[r[0]][r[1]] = dict(dem=r[2], addr=r[3], size=r[4])
    layout = []
    for r in read_tsv(os.path.join(VD, "layout.tsv")):
        layout.append(dict(cls=r[0], size_old=r[1], size_new=r[2], methods=int(r[3]), shifted=int(r[4]),
                           shifts=r[5] if len(r) > 5 else ""))
    sigs = []   # report.md "Signature changes": 3.7.0 name -> 3.8.0 name
    rep = open(os.path.join(VD, "report.md")).read()
    m = re.search(r"## Signature changes(.*?)\n## ", rep, re.S)
    if m:
        for l in m.group(1).split("\n"):
            mm = re.match(r"\| `(.*?)` \| `(.*?)` \| (.*?) \| (\d+) \| (.*) \|$", l)
            if mm:
                sigs.append(dict(old=mm.group(1), new=mm.group(2), size=mm.group(3), diff=int(mm.group(4)), what=mm.group(5)))
    return changed, only, layout, sigs


# ---------------------------------------------------------------------------------------------
# Source index: string literals, mangled names and hex literals of port/src/native.
def family_of(path):
    r = os.path.relpath(path, NATIVE).split(os.sep)
    if len(r) == 1:
        return "(top)"
    if r[0] in ("ui", "engine") and len(r) > 2 and r[1] in ("cocos", "screen", "math"):
        return r[0] + "/" + r[1]
    return r[0]


def is_test(path):
    return path.endswith("_test.cpp") or "/zz_" in path or path.endswith("_tests.cpp")


def is_gen(path):
    return "/gen/" in path


class Sources:
    LIT = re.compile(r'"((?:[^"\\\n]|\\.)*)"')
    MANG = re.compile(r"\b(_Z\w+)")

    def __init__(self):
        self.files = []
        for d, _, fs in os.walk(NATIVE):
            for f in fs:
                if f.endswith((".cpp", ".h", ".inc")):
                    self.files.append(os.path.join(d, f))
        self.files.sort()
        self.text = {}
        self.lits = collections.defaultdict(set)    # literal -> files
        self.syms = collections.defaultdict(set)    # mangled -> files
        for p in self.files:
            t = open(p, errors="replace").read()
            self.text[p] = t
            for m in self.LIT.finditer(t):
                self.lits[m.group(1)].add(p)
            for m in self.MANG.finditer(t):
                self.syms[m.group(1)].add(p)
        self.lit_list = list(self.lits)

    def note_files(self, note):
        if note in self.lits:
            return self.lits[note]
        # a note built from parts: a literal that is a long prefix of the note
        best, bl = set(), 0
        for l in self.lit_list:
            if len(l) >= 8 and note.startswith(l) and len(l) > bl:
                best, bl = self.lits[l], len(l)
        if best:
            return best
        stem = re.split(r" \(|: | \[", note)[0]
        if len(stem) >= 6 and stem in self.lits:
            return self.lits[stem]
        return set()


GEN_HDR = re.compile(r"(GENERATED by|Generated by|Generated from|Generated:|Generated\b)\s*(.*)")


# ---------------------------------------------------------------------------------------------
# Generated files: curated (generator, regeneration command for 3.7.0, notes).
# Every file under port/src/native/**/gen/ and every *.inc under port/src must have an entry.
SL = "SOA_LIB=work/libSOA-3.7.0.so .venv/bin/python"
GEN = {
    "port/src/native/api/gen/api_notify_a2c.cpp": ("tools/gen_apinotify_a2c.py", SL + " tools/gen_apinotify_a2c.py port/src/native/api/gen/api_notify_a2c.cpp", "a2c of CApiNotify::DeserializeToInfo"),
    "port/src/native/arena/gen/arena_a2c.cpp": ("tools/gen_arena_a2c.py", SL + " tools/gen_arena_a2c.py port/src/native/arena/gen/arena_a2c.cpp", "function list tools/arena_funcs.txt (names)"),
    "port/src/native/engine/math/gen/aska_math_a2c.cpp": ("tools/gen_aska_math_a2c.py", SL + " tools/gen_aska_math_a2c.py port/src/native/engine/math/gen/aska_math_a2c.cpp", "collision_spec() runs `nm` on the hard-coded 3.8.0 lib path: make it use SOA_LIB first"),
    "port/src/native/ui/cocos/gen/cocos_a2c.cpp": ("tools/gen_cocos_a2c.py", SL + " tools/gen_cocos_a2c.py port/src/native/ui/cocos/gen/cocos_a2c.cpp", "function list is 3.8.0 `addr:size` literals: remap to 3.7.0 (or to symbols) first"),
    "port/src/native/containers/gen/containers_a2c.cpp": ("tools/gen_containers_a2c.py", SL + " tools/gen_containers_a2c.py port/src/native/containers/gen/containers_a2c.cpp [executed.txt native.txt]", "the executed-only families (Yayoi, playcore, Global) take an executed list: use a 3.7.0 coverage run; playcore is 3.8.0-only"),
    "port/src/native/containers/gen/containers_tables.inc": ("tools/gen_containers_tables.py", SL + " tools/gen_containers_tables.py > port/src/native/containers/gen/containers_tables.inc", "elfinfo (SOA_LIB)"),
    "port/src/native/dynamics/gen/dynamics_a2c.cpp": ("tools/gen_dynamics_a2c.py", SL + " tools/gen_dynamics_a2c.py port/src/native/dynamics/gen/dynamics_a2c.cpp", "3.8.0 `addr:size` literals and the executed set read from work/profile/restore-20260929 (3.8.0 addresses): remap both"),
    "port/src/native/ui/cocos/gen/cocos_guireader_a2c.cpp": ("tools/gen_guireader_a2c.py", SL + " tools/gen_guireader_a2c.py port/src/native/ui/cocos/gen/cocos_guireader_a2c.cpp", ""),
    "port/src/native/params/gen/infobase_a2c.cpp": ("tools/gen_infobase_a2c.py", SL + " tools/gen_infobase_a2c.py port/src/native/params/gen/infobase_a2c.cpp", ""),
    "port/src/native/params/gen/infobase_table.inc": ("selftest infobase/gen-table (port/src/native/params/infobase_gen.cpp)", "SOA_INFOBASE_GEN=port/src/native/params/gen/infobase_table.inc build/port/soa --selftest infobase/gen-table   (needs P1: soa on the 3.7.0 lib)", "dumped from the running guest image"),
    "port/src/native/params/gen/parameter_elements.inc": ("tools/gen_loader_tables.py", SL + " tools/gen_loader_tables.py > port/src/native/params/gen/parameter_elements.inc", "elfinfo (SOA_LIB)"),
    "port/src/native/params/gen/parameter_layouts.inc": ("selftest param/elements/layout", "SOA_PARAM_LAYOUT_DUMP=port/src/native/params/gen/parameter_layouts.inc build/port/soa --selftest param/elements/layout   (needs P1)", "dumped from the running guest image"),
    "port/src/native/params/gen/parameter_tables.inc": ("tools/gen_parameter_tables.py", SL + " tools/gen_parameter_tables.py > port/src/native/params/gen/parameter_tables.inc", "elfinfo (SOA_LIB)"),
    "port/src/native/models/gen/models_a2c.cpp": ("tools/gen_models_a2c.py", SL + " tools/gen_models_a2c.py port/src/native/models/gen/models_a2c.cpp port/src/native/models/gen/models_a2c_insn.cpp", "also writes models_anim_tab.inc and models_a2c_insn.cpp; list tools/models_funcs.txt"),
    "port/src/native/models/gen/models_a2c_insn.cpp": ("tools/gen_models_a2c.py", "(with models_a2c.cpp)", "the translator's instruction self-test"),
    "port/src/native/models/gen/models_anim_tab.inc": ("tools/gen_models_a2c.py (+ tools/models_readable.py)", "(with models_a2c.cpp)", "rows carry 3.8.0 addresses next to the symbols"),
    "port/src/native/objbase/gen/objbase_a2c.cpp": ("tools/gen_objbase_a2c.py", SL + " tools/gen_objbase_a2c.py port/src/native/objbase/gen/objbase_a2c.cpp", "lists tools/objbase_funcs.txt, objbase_verified.txt"),
    "port/src/native/engine/gen/objmgr_a2c.cpp": ("tools/gen_objmgr_a2c.py", SL + " tools/gen_objmgr_a2c.py port/src/native/engine/gen/objmgr_a2c.cpp", ""),
    "port/src/native/particles/gen/particles_a2c.cpp": ("tools/gen_particles_a2c.py", SL + " tools/gen_particles_a2c.py port/src/native/particles/gen/particles_a2c.cpp", "lists tools/particles_funcs.txt, particles_render_funcs.txt"),
    "port/src/native/render/gen/render_a2c.cpp": ("tools/gen_render_a2c.py", SL + " tools/gen_render_a2c.py port/src/native/render/gen/render_a2c.cpp", "includes ShadowManager::ShadowCasterCulling (changed body, layout shift 0x5b0>0x630)"),
    "port/src/native/ui/screen/gen/screen_a2c.cpp": ("tools/gen_screens_a2c.py", SL + " tools/gen_screens_a2c.py port/src/native/ui/screen/gen/screen_a2c.cpp", ""),
    "port/src/native/api/gen/wire_table.inc": ("tools/api_wire.py --gen-inc", SL + " tools/api_wire.py --gen-inc port/src/native/api/gen/wire_table.inc", "elfinfo (SOA_LIB)"),
    "port/src/native/api/gen/fakeapi_tables.inc": ("none in tree (ad hoc from the FakeApiCaller methods; docs/notes.md \"Offline server (FakeApiCaller)\")", "write a generator, or remap the vaddr columns with docs/history/rebase-370/address_bound.tsv", "3.8.0 vaddrs of file names, lambda vtables and operator()s: the 96 `@0x` natives come from here"),
    "port/src/native/api/api_notify_table.inc": ("none in tree (CApiNotify handler list)", "symbols only: keep if every symbol is identical in 3.7.0 (checked below)", ""),
    "port/src/native/api/api_notify_count.inc": ("none in tree (count of api_notify_table.inc)", "follows api_notify_table.inc", ""),
    "port/src/native/battle/gen/battle_factor_ids.inc": ("none in tree (from the disassembly of CFactorSeed*::GetTypeId / CheckSameId; battle_factor_ids.cpp)", "symbols only: keep if every symbol is identical in 3.7.0 (checked below)", ""),
    "port/src/native/battle/battle_core_callees.inc": ("hand-written list (callees stubbed by the battle tests)", "symbols only: keep", ""),
    "port/src/native/libs/gen/libcxx_hash_table.inc": ("none in tree (identical __rehash instantiations)", "symbols only: keep if every symbol is identical in 3.7.0 (checked below)", ""),
    "port/src/native/restore/gen/restore370_statics.inc": ("tools/restore370_audit.py --emit", "delete with restore370 (P3)", "3.7.0 adrp -> 3.8.0 static map; meaningless after the rebase"),
}

GEN_TOOL_FOR = {   # a2c family tag in --list-native notes -> generated file
    "models": "port/src/native/models/gen/models_a2c.cpp",
    "Aska containers / Yayoi / Global": "port/src/native/containers/gen/containers_a2c.cpp",
    "InfoBase containers": "port/src/native/params/gen/infobase_a2c.cpp",
    "particles": "port/src/native/particles/gen/particles_a2c.cpp",
    "arena": "port/src/native/arena/gen/arena_a2c.cpp",
    "objbase": "port/src/native/objbase/gen/objbase_a2c.cpp",
    "dynamics": "port/src/native/dynamics/gen/dynamics_a2c.cpp",
    "render": "port/src/native/render/gen/render_a2c.cpp",
    "screen": "port/src/native/ui/screen/gen/screen_a2c.cpp",
    "Cocos": "port/src/native/ui/cocos/gen/cocos_a2c.cpp",
    "CApiNotify": "port/src/native/api/gen/api_notify_a2c.cpp",
    "aska math": "port/src/native/engine/math/gen/aska_math_a2c.cpp",
    "Aska::ObjectManager": "port/src/native/engine/gen/objmgr_a2c.cpp",
    "Aska::SimpleMessageDispatcher": "port/src/native/engine/gen/objmgr_a2c.cpp",
    "Cocos: layout reader": "port/src/native/ui/cocos/gen/cocos_guireader_a2c.cpp",
    "Cocos: timeline": "port/src/native/ui/cocos/gen/cocos_guireader_a2c.cpp",
    "Event scene": "port/src/native/ui/cocos/gen/cocos_a2c.cpp",
}


# ---------------------------------------------------------------------------------------------
# docs/client-changes.md headings and port restore modules: keep / delete / re-check (judgement,
# kept here so that --check catches a new heading or module nobody classified). Keys are heading
# prefixes (after stripping markdown backticks).
CLIENT = [
    ("master_global.service_stop_day dropped", "delete (re-check the title)", "3.7.0's NowTime / LocalTime never read the row (verdiff 2.4). The 3.7.0 title's service-end check still reads it: that is platform370's FindGlobalStringWithKey patch (emulator), and soa-server's CDN master already drops the row."),
    ("The game's save (Game.xml) written", "re-check (likely delete)", "The 3.7.0 client takes the player from Login / GetPlayer; soa-emu runs without it. Check the home's summary under 3.7.0 first."),
    ("Sphere 211 season dates moved", "keep", "Calendar replay is version-independent; soa-server's CDN master carries the same edit (server-rules \"The served master is the client master edits\")."),
    ("Event dates moved", "keep", "As above: calendar replay, server-side."),
    ("Enabled events opened", "keep", "As above."),
    ("The 3.7.0 texts added", "delete", "The 3.7.0 master (the download's / the CDN's) already has all 66,945 master_text rows."),
    ("Event exchange shops moved", "keep", "Calendar replay, server-side."),
    ("Stand-in images for lost assets", "keep", "The art is missing from the 3.7.0 download too."),
    ("Tower banner rows added", "keep", "The 3.7.0 master lacks banner801..805 (that is where the problem is)."),
    ("Local-server refusals reach the client's error handling", "keep (--server inproc only)", "FakeApiCaller route only; with --server HOST:PORT the 3.7.0 NetworkApiCaller reports error codes itself."),
    ("req:Name:args in the fake server's drive file", "keep (inproc test tool)", "Test tooling on the FakeApiCaller route."),
    ("Login-bonus popup after login", "delete", "3.7.0's CPhase_Login::Progress calls CPopupManager::AddPopup() itself (mask 0x7b); the emulator's seeded session closes the notice board and LOGIN BONUS popups without help."),
    ("Favorability", "delete", "3.7.0's favor getters read CParameterManager's favor map; restore_favor*.cpp only re-implement them on 3.8.0."),
    ("Home and menus", "delete (section)", "Its sub-entries are 3.8.0 workarounds; see below."),
    ("Changed under --restore", "delete", "CCharacterPictureBook::CheckTime wrapper: 3.7.0's CreateCollectList passes NowTime() itself."),
    ("Served by the local server (no client change)", "keep", "Server-side; drop the sentences about 3.8.0's missing AddPopup."),
    ("Not restored (3.8.0 behaviour kept), with reasons", "delete", "3.7.0 runs its own code for all of these; the platform stubs become platform370's Java answers (as in soa-emu)."),
    ("Restored 3.7.0 code (the restore image)", "delete", "The restore image only exists to run 3.7.0 bodies on 3.8.0 symbols."),
    ("Party building: CPartyComposition", "delete", "restore370 group party: native 3.7.0 code after the rebase."),
    ("Character sort and filter keyed by character id", "delete", "restore370 group sort."),
    ("Home character select: CAdjutantSelect", "delete", "restore370 group adjutant."),
    ("Home: CHome", "delete", "restore370 group home."),
    ("Footer and status bar: CCommon", "delete", "restore370 group common."),
    ("Other menu: COtherMenu", "delete", "restore370 group othermenu."),
    ("Popups after login (the restored login's", "delete", "3.7.0's login arms the popups itself."),
    ("Port-specific code changes", "keep (section)", "Mostly the FakeApiCaller route; see below."),
    ("Notice board page: web pages the local server hosts", "re-check", "Native on CWebView::OpenView, whose body changed between the builds (see the changed-function table): decide against the 3.7.0 body and platform370's ShowWebView answer (emulator shows the notice board through Java)."),
    ("IApiCaller::UpdatePartySet, SetAssist and UpdateView on the FakeApiCaller route", "keep (--server inproc only)", "FakeApiCaller route."),
    ("Gear requests and AchievementListReceive on the FakeApiCaller route", "keep (--server inproc only)", "FakeApiCaller route."),
    ("FakeApiCaller::DeepSpaceActiveList on the FakeApiCaller route", "keep (--server inproc only)", "FakeApiCaller route."),
    ("The Sphere 211 requests on the FakeApiCaller route", "keep (--server inproc only)", "FakeApiCaller route."),
    ("Event ranking and world-boss requests on the FakeApiCaller route", "keep (--server inproc only)", "FakeApiCaller route."),
    ("Entry flow: title, login, new player, tutorial", "delete", "restore370 groups login / playerinit / phase / tutorial / title."),
    ("How 3.7.0 bodies are installed", "delete", "restore370 mechanism."),
    ("Group login:", "delete", "restore370."),
    ("Group playerinit:", "delete", "restore370."),
    ("Group phase:", "delete", "restore370."),
    ("Group tutorial:", "delete", "restore370."),
    ("Group title (off by default):", "delete", "restore370."),
    ("FakeApiCaller session queries", "keep (--server inproc only)", "FakeApiCaller route: LoggedIn / IsSuccess / IsFailure / ErrorCode."),
    ("The tower (試練の遺跡) opened", "keep", "Port-specific (3.7.0's IsOpenTowerMission returned 0 too). The wrapped CTowerMissionMenu::Setup / Initialize bodies are identical in 3.7.0 (restore-module table), so the null dereference and the missing common-resource scene are there too: the wrappers stay."),
    ("The story campaign", "split: delete / keep", "Episode-tap lambda, CMissionMenu::NextPhase, EventScenario::Exit: 3.7.0 behaviour restored -> delete. FakeApiCaller::GetWorldMapInfoList and the Load_PartyInfo GetPlayer queue: inproc route -> re-check (3.7.0's login already sends GetPlayer)."),
    ("Emulator mode (soa-emu, emulator/)", "keep (moves to platform370/)", "The 3.7.0 platform layer; P0 platform370 extraction."),
    ("Emulator viewer (3.8.0)", "keep", "The viewer keeps 3.8.0 (decision 2)."),
    ("Data overrides (no code change)", "keep (section)", "See the entries."),
    ("Code changes", "keep (section)", "See the entries."),
]

RESTORE_MODULES = {
    "port/src/native/restore/restore370.cpp": ("delete", "the restore image (3.7.0 bodies on 3.8.0 symbols)"),
    "port/src/native/restore/restore370.h": ("delete", "restore370"),
    "port/src/native/restore/restore370_test.cpp": ("delete", "restore370 tests"),
    "port/src/native/restore/gen/restore370_statics.inc": ("delete", "restore370 statics map"),
    "port/src/restore/restore_test.cpp": ("delete", "restore/link etc. (restore image tests)"),
    "port/src/native/restore/restore_favor.cpp": ("delete", "3.7.0 favor getters re-implemented on 3.8.0"),
    "port/src/native/restore/restore_favor.h": ("delete", "restore_favor"),
    "port/src/native/restore/restore_favor_test.cpp": ("delete", "against the 3.7.0 oracle"),
    "port/src/native/restore/restore_favor_achievement.cpp": ("delete", "3.7.0 favor level on 3.8.0 body"),
    "port/src/native/restore/restore_home.cpp": ("delete", "CheckTime(t = NowTime()) for the 3.8.0 CreateCollectList"),
    "port/src/native/restore/restore_home.h": ("delete", "restore_home"),
    "port/src/native/restore/restore_home_test.cpp": ("delete", "restore_home tests"),
    "port/src/native/restore/restore_campaign.cpp": ("split", "EventScenario::Exit / CMissionMenu::NextPhase restore 3.7.0 -> delete; Load_PartyInfo GetPlayer queue -> re-check"),
    "port/src/native/restore/restore_tower.cpp": ("keep (move out of restore/)", "port-specific tower opening; the wrapped CTowerMissionMenu Setup / Initialize are identical in 3.7.0"),
}

# docs/server-rules.md sections that mention 3.8.0-only client behaviour (marker regex below).
SERVER_MARK = re.compile(r"3\.8\.0|home_sa|service_stop_day|offline|FakeApiCaller|Game\.xml|frozen|gutted|restore370|restored 3\.7\.0", re.I)
SERVER = [
    ("Conventions", "re-check", "The frozen-clock convention (service_stop_day row dropped) is 3.8.0's NowTime; 3.7.0 never reads the row. Keep the source-label conventions."),
    ("2.2 MissionStart", "keep", "Rules are version-independent; the in-process battle-log read is the inproc route."),
    ("2.3 MissionEnd (win)", "keep", "The in-process battle log read is the inproc route; --server reads the serialized log."),
    ("4.1 What's open", "keep", "Gacha windows; the service_stop_day remark is history."),
    ("7. Login bonus", "keep (edit)", "Drop \"the popup needs the popup checks armed\" workaround: 3.7.0's login arms them."),
    ("8. Favor (affinity, 好感度)", "keep (edit)", "Rules stay; the sentence about the restored 3.7.0 favor getters becomes moot."),
    ("Register of (c) and (d) rules the player can see", "keep", "FakeApiCaller refusal row applies to inproc only."),
    ("Notes for the server-core implementation", "re-check", "Frozen client clock notes are 3.8.0-only."),
    ("Server core: what server/ implements", "keep (section)", "See the subsections."),
    ("Architecture", "keep", "FakeApiCaller route = --server inproc."),
    ("Seed (first run)", "keep", ""),
    ("Syncing the game's save", "re-check (likely delete)", "Exists because the offline 3.8.0 client shows its cached save summary over the response."),
    ("Player load (NoLoginStart, Login, SimpleLogin, GetPlayer, CreatePlayer)", "re-check", "\"The offline boot's only request is NoLoginStart\" is 3.8.0; 3.7.0 logs in (soa-emu: StartBridge, Login, GetPlayerRes)."),
    ("Party (UpdateParty", "keep", "Now reachable on screen in 3.7.0 (the caller was gutted in 3.8.0): test it."),
    ("Party sets (UpdatePartySet", "re-check", "The (d) evidence cites the 3.8.0 list code."),
    ("UI tutorial flags (UpdateView", "keep", ""),
    ("Home character (UpdateHome", "re-check", "home_pc_id is sent as a role id for 3.8.0's CHome::GetAdjutant; check what 3.7.0's CHome / CAdjutantSelect expect (soa-emu works with it today)."),
    ("Play state (GetPlayMission", "keep (inproc)", "FakeApiCaller maps them to player_get.msgp."),
    ("Player-visible (c) and (d) rules", "keep", ""),
    ("Entry flow: login, new player, tutorial", "keep (edit)", "Rules stay; references to the restore370 groups become \"3.7.0 code\"."),
    ("Session and login", "keep", "FakeApiCaller::LoggedIn is the inproc route."),
    ("Tutorial progress", "keep", "UpdateView through the FakeApiCaller route (inproc)."),
    ("Status of the new-player flow", "re-check", "Written against the restored CHome group on 3.8.0."),
    ("soa-server: the wire layer", "keep", "The 3.7.0 wire layer; \"soa falls back to FakeApiCaller's static files\" is inproc."),
    ("soa-server: the CDN", "keep", "The served master = the client master edits."),
    ("Growth and economy", "keep (section)", ""),
    ("Login bonus", "keep (edit)", "Drop the AddPopup(3) client workaround paragraph."),
    ("Achievements", "keep", ""),
    ("Verification", "re-check", "The growth screens weren't reachable in the 3.8.0 UI; under 3.7.0 they are: verify on screen."),
    ("Refusals and error codes", "keep", "FakeApiCaller route (inproc); NetworkApiCaller reports codes on --server."),
    ("Campaign progression", "keep (edit)", "The note on the client clock frozen at service_stop_day is 3.8.0."),
    ("Rental helpers", "keep", "3.7.0 and 3.8.0 identical."),
    ("Premium and favor login bonuses", "keep", ""),
    ("Favor achievements", "keep", ""),
    ("Fixes found on the growth screens", "re-check", "Found on the restored (3.8.0-hosted) screens."),
    ("Deep space", "keep", "DeepSpaceActiveList on the FakeApiCaller route is inproc."),
    ("Requests as the client sends them", "keep", ""),
    ("Coin ships", "keep", ""),
    ("Sphere 211", "keep", ""),
    ("Rules", "keep", ""),
    ("Events", "keep (section)", ""),
    ("Other data", "keep (edit)", "The 3.7.0 texts insert is unnecessary with the 3.7.0 master (client-changes: delete)."),
    ("Two clocks", "keep", ""),
    ("Event extras", "keep", ""),
    ("Gear (ギア", "keep", ""),
    ("Fixes to the core's responses", "keep", ""),
    ("MissionStart", "keep", ""),
    ("Battle status from the client's own computation", "keep (inproc)", "Reads the client's computation in-process."),
    ("Response keys", "keep", ""),
    ("Tower", "keep", ""),
    ("What is listed", "keep", ""),
    ("Enabling events by keyword", "keep", ""),
    ("Gacha", "keep", ""),
    ("Character growth", "keep", ""),
    ("Items and stamina", "keep", ""),
    ("Stamina", "re-check", "Written against the frozen 3.8.0 clock."),
    ("Exchange shops on the event calendar", "keep", ""),
    ("Shops", "keep", ""),
    ("Presents", "keep", ""),
    ("Story missions", "keep", ""),
    ("Terms and name", "keep", ""),
    ("Tutorial battle", "keep", ""),
    ("New player", "keep", ""),
    ("Event rankings", "keep", ""),
    ("Favor event drop bonus", "keep", ""),
    ("World bosses and big hunts", "keep", ""),
    ("Step-up", "keep", ""),
    ("Single and bulk draws", "keep", ""),
    ("Type-8 campaigns", "keep", ""),
    ("Gear", "keep", ""),
    ("Passes", "keep", ""),
    ("State", "keep", ""),
    ("Response shapes", "keep", ""),
    ("Clocks", "keep", ""),
    ("Not done", "keep", ""),
    ("Server missions", "keep", ""),
    ("MissionEnd drops", "keep", ""),
    ("Battle status additions", "keep", ""),
    ("Gacha: step-up and box", "keep", ""),
    ("Present box lines", "keep", ""),
    ("Battle evaluation values", "keep", ""),
    ("Server rules added by agent", "keep", ""),
    ("Home (agent home370", "re-check", "Answers written for the restored CHome on 3.8.0."),
    ("Titles (称号", "keep", ""),
    ("Notice board page", "re-check", "The local server's pages for the port's CWebView::OpenView native; under 3.7.0 the Java web view (platform370) shows them."),
    ("NPC helpers", "keep", ""),
    ("Tests and session", "keep", ""),
    ("Season", "keep", ""),
    ("Player rank", "keep", ""),
    ("Stocks and wallet", "keep", ""),
    ("2.1 Opening missions", "keep", ""),
    ("2.4 Drops", "keep", ""),
    ("2.5 Battle evaluation", "keep", ""),
    ("2.6 Failure, continue, restart", "keep", ""),
    ("3. Battle party status", "keep", ""),
    ("4.4 Step-up and box gacha", "keep", ""),
    ("4.5 Gacha pools", "keep", ""),
    ("5.", "keep", ""),
    ("6. Presents", "keep", ""),
    ("9. Shops", "keep", ""),
    ("10. Achievements", "keep", ""),
    ("11. Other modes", "keep", ""),
    ("12. Home", "re-check", "Written for the restored CHome on 3.8.0."),
    ("1. Player, stamina and player rank", "keep", ""),
    ("2. Missions", "keep", ""),
    ("4. Gacha", "keep", ""),
    ("4.2 Cost", "keep", ""),
    ("4.3 Rates and pool", "keep", ""),
    ("5. Growth", "keep", ""),
    ("Heat-up", "keep", ""),
    ("Time bonus", "keep", ""),
]


def lookup(table, heading):
    h = heading.replace("`", "")
    best = None
    for key, dec, why in table:
        if h.startswith(key):
            if best is None or len(key) > len(best[0]):
                best = (key, dec, why)
    return best


def md_sections(path, levels=(2, 3, 4)):
    """[(level, heading, start_line, body_text)]"""
    lines = open(path).read().split("\n")
    out, cur = [], None
    for i, l in enumerate(lines, 1):
        m = re.match(r"^(#{2,4}) (.*)", l)
        if m and len(m.group(1)) in levels:
            if cur:
                out.append(cur)
            cur = [len(m.group(1)), m.group(2).strip(), i, []]
        elif cur:
            cur[3].append(l)
    if cur:
        out.append(cur)
    return [(a, b, c, "\n".join(d)) for a, b, c, d in out]


# ---------------------------------------------------------------------------------------------
# Coverage summaries (SOA_COVERAGE / SOA_PROFILE runs) -> docs/history/rebase-370/coverage-<kind>.tsv
COV_KINDS = {"emu-seeded": "370", "emu-newplayer": "370", "port-restore": "380", "port-tutorial": "380"}


def canon_name(img, raw):
    m = re.match(r"FUN_([0-9a-f]+)$", raw)
    if m:
        va = int(m.group(1), 16) - 0x100000
        return img.name_at.get(va) or ("?%#x" % va), va
    a = img.I.funcs.get(raw)
    if a:
        return img.name_at.get(a[0], raw), a[0]
    return raw, None


def summarise_coverage(kind, d, imgs):
    img = imgs[COV_KINDS[kind]]
    meta = dict(l.split(" ", 1) for l in open(os.path.join(d, "meta.txt")).read().split("\n") if " " in l)
    if meta.get("coverage", "0").strip() != "1":
        sys.exit("%s: %s/meta.txt says coverage 0 (SOA_COVERAGE wasn't set, or the run was killed)" % (kind, d))
    first = {}
    for r in read_tsv(os.path.join(d, "coverage.tsv"), header=True):
        n, va = canon_name(img, r[2])
        first[n] = (va, float(r[1]))
    self_s, incl_s = collections.Counter(), collections.Counter()
    nat_self, nat_incl = collections.Counter(), collections.Counter()
    sf = os.path.join(d, "stacks.folded")
    if os.path.exists(sf):
        for l in open(sf):
            stack, _, c = l.rstrip("\n").rpartition(" ")
            if not c.isdigit():
                continue
            c = int(c)
            fr = [f for f in stack.split(";")[1:] if f and not f.startswith("[") or f.startswith("[native]")]
            seen = set()
            for i, f in enumerate(fr):
                isn = f.startswith("[native]")
                raw = f[8:] if isn else f
                n = canon_name(img, raw)[0]
                key = ("N", n) if isn else ("G", n)
                if key in seen:
                    continue
                seen.add(key)
                (nat_incl if isn else incl_s)[n] += c
                if i == len(fr) - 1:
                    (nat_self if isn else self_s)[n] += c
    calls = collections.Counter()
    cf = os.path.join(d, "calls.tsv")
    if os.path.exists(cf):
        for r in read_tsv(cf, header=True):
            if r[0] == "native":
                calls[canon_name(img, r[3])[0]] += int(r[1])
    path = os.path.join(OUTDIR, "coverage-%s.tsv" % kind)
    with open(path, "w") as f:
        f.write("# %s: %s (lib %s), %s s, %s armed entries, %s executed. Derived by tools/rebase_inventory.py --coverage.\n"
                % (kind, rel(d) if d.startswith(REPO) else d, COV_KINDS[kind], meta.get("seconds", "?").strip(),
                   meta.get("armed", "?").strip(), meta.get("executed", "?").strip()))
        f.write("kind\tfunction (G: guest function as its vaddr in this lib, named by the tool; N: native symbol)\tfirst_hit_s\tself_samples\tincl_samples\tnative_calls\n")
        for n, (va, t) in sorted(first.items(), key=lambda x: x[1][1]):
            f.write("G\t%s\t%.2f\t%d\t%d\t\n" % ("%x" % va if va is not None else n, t, self_s[n], incl_s[n]))
        for n in sorted(set(calls) | set(nat_incl)):
            f.write("N\t%s\t\t%d\t%d\t%d\n" % (n, nat_self[n], nat_incl[n], calls[n]))
    print("wrote", rel(path), file=sys.stderr)


def load_coverage(imgs):
    cov = {}
    for k in COV_KINDS:
        p = os.path.join(OUTDIR, "coverage-%s.tsv" % k)
        if not os.path.exists(p):
            continue
        g, n = {}, {}
        img = imgs[COV_KINDS[k]]
        hdr = open(p).readline().strip()
        for r in read_tsv(p, header=False)[1:]:
            if r[0] == "G":
                if re.fullmatch(r"[0-9a-f]+", r[1]):
                    va = int(r[1], 16)
                    name = img.name_at.get(va) or ("?%#x" % va)
                else:
                    va, name = None, r[1]
                g[name] = ("%#x" % va if va is not None else "", float(r[2]), int(r[3]), int(r[4]))
            else:
                n[r[1]] = (int(r[3]), int(r[4]), int(r[5] or 0))
        cov[k] = dict(g=g, n=n, hdr=hdr)
    return cov


# ---------------------------------------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--soa")
    ap.add_argument("--list-native")
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--coverage", action="append", default=[], metavar="KIND=DIR")
    args = ap.parse_args()
    os.makedirs(OUTDIR, exist_ok=True)

    print("loading images", file=sys.stderr)
    imgs = {"380": Img(LIB380), "370": Img(LIB370)}
    N, O = imgs["380"], imgs["370"]
    for c in args.coverage:
        k, _, d = c.partition("=")
        if k not in COV_KINDS:
            sys.exit("--coverage: kind must be one of " + ", ".join(COV_KINDS))
        summarise_coverage(k, os.path.abspath(d), imgs)

    natives = load_list_native(args)
    changed, only, layout, sigs = load_verdiff()
    print("indexing sources", file=sys.stderr)
    S = Sources()
    cov = load_coverage(imgs)

    # ---- per-native classification ---------------------------------------------------------
    syms = [s for s, _ in natives if not s.startswith("@")]
    dem = dict(zip(syms, demangle(syms)))
    only380_base = collections.defaultdict(list)
    for s, e in only["3.7.0"].items():
        only380_base[re.sub(r"\(.*", "", e["dem"])].append(s)

    heat = cov.get(HEAT_RUN, {}).get("n", {})
    gen_script_syms = {}   # mangled names a generator script lists -> its generated file
    for gfile, meta in GEN.items():
        m = re.match(r"tools/(gen_\w+_a2c\.py)", meta[0])
        if m and gfile.endswith("_a2c.cpp"):
            for s in re.findall(r"\b(_Z\w+)", open(os.path.join(REPO, "tools", m.group(1))).read()):
                gen_script_syms.setdefault(s, gfile)
    note_cache = {}
    rows = []
    for sym, note in natives:
        base_note = re.sub(r"( \[conditional\])+$", "", note)
        r = dict(sym=sym, note=note, tags=[], fam="?", files=[], dem=dem.get(sym, sym))
        # family: the file registering the note, else the files naming the symbol
        if base_note not in note_cache:
            note_cache[base_note] = S.note_files(base_note)
        nf = note_cache[base_note]
        sf = S.syms.get(sym, set()) if not sym.startswith("@") else set()
        if sym.startswith("@"):
            sf = {p for p in S.files if sym[1:] in S.text[p]}
        fams_n = {family_of(p) for p in nf if not is_test(p)} or {family_of(p) for p in nf}
        mfile = re.search(r"\b(\w+)\.cpp\b", note)    # notes that name their file
        if mfile:
            named = [p for p in S.files if os.path.basename(p) == mfile.group(1) + ".cpp"]
            if named:
                fams_n = {family_of(named[0])}
        cand = None
        if len(fams_n) == 1:
            cand = fams_n.pop()
        else:
            pool = [p for p in sf if not is_test(p)] or list(sf)
            if fams_n:
                pool = [p for p in pool if family_of(p) in fams_n] or pool
            c = collections.Counter(family_of(p) for p in pool)
            if c:
                cand = sorted(c.items(), key=lambda kv: (-kv[1], kv[0]))[0][0]
            elif fams_n:
                cand = sorted(fams_n)[0]
        r["fam"] = cand or "?"
        r["files"] = sorted(rel(p) for p in (nf | sf) if not is_test(p))[:4]
        # 3.7.0 status
        if sym.startswith("@"):
            va = int(sym[1:], 16)
            f = N.func_of(va)
            f7 = O.func_of(va)
            r["tags"].append("address")
            r["fn380"] = f
            def names_note(fn_):   # how many words of the native's note its name has
                if not fn_:
                    return 0
                return sum(1 for w_ in set(re.findall(r"[A-Za-z]{5,}", note))
                           if (w_ == "lambda" and fn_[0].startswith("lambda:")) or (w_ != "lambda" and w_ in fn_[0]))
            if f7 and f7[2] == 0 and (not (f and f[2] == 0) or names_note(f7) > names_note(f)):
                # already a 3.7.0 address (P1 / P2-e): name the 3.8.0 counterpart for the record
                n7 = f7[0]
                o8 = N.I.funcs.get(n7)
                r["dem"] = n7
                r["va370"] = va
                r["status"] = "3.7.0 already (%s; 3.8.0: %s)" % (n7, "%#x" % o8[0] if o8 else "none")
            elif f:
                n, s, off = f
                r["dem"] = "%s+%#x" % (n, off)
                o = O.I.funcs.get(n)
                if n in changed:
                    r["status"] = "unmappable: containing function changed"
                elif not o:
                    r["status"] = "unmappable: %s not in 3.7.0" % n
                elif off >= o[1] and o[1]:
                    r["status"] = "unmappable: offset past the 3.7.0 extent"
                else:
                    va7 = o[0] + off
                    m8, m7 = N.insn(va), O.insn(va7)
                    r["va370"] = va7
                    r["status"] = "remap %#x -> %#x" % (va, va7) + ("" if m8 == m7 else " (insn %s vs %s: check)" % (m8, m7))
            else:
                r["status"] = "unmappable: no containing function"
            if "unmappable" in r["status"]:
                r["tags"].append("unmappable")
        elif sym in changed:
            r["tags"].append("changed")
            r["status"] = "changed: " + changed[sym]["what"]
        elif sym in only["3.8.0"]:
            r["tags"].append("only380")
            b = re.sub(r"\(.*", "", dem.get(sym, sym))
            cp = only380_base.get(b)
            r["status"] = "only in 3.8.0" + (" (3.7.0 counterpart: %s)" % ", ".join(cp) if cp else "")
        elif sym in O.I.funcs or sym in O.I.objects:
            r["tags"].append("identical")
            r["status"] = "identical"
        else:
            r["tags"].append("unresolved")
            r["status"] = "not in 3.7.0 and not in verdiff's lists"
        # a2c / transcribed
        gen_hits = sorted(rel(p) for p in sf if is_gen(p))
        a2c_math = note.startswith("aska math") and any(g.endswith("aska_math_a2c.cpp") for g in gen_hits)
        if "(a2c" in note or "(transcribed" in note or "a2c transcription" in note or a2c_math:
            r["tags"].append("a2c")
            gf = gen_script_syms.get(sym)
            ks = sorted((k for k in GEN_TOOL_FOR if note.startswith(k)), key=len)
            if not gf and ks:
                gf = GEN_TOOL_FOR[ks[-1]]
            if not gf:
                a2cs = [g for g in gen_hits if g.endswith("_a2c.cpp")]
                gf = a2cs[0] if a2cs else None
            if not gf and r["fam"] == "ui/cocos":
                gf = "port/src/native/ui/cocos/gen/cocos_a2c.cpp|cocos_guireader_a2c.cpp"
            if not gf and "(transcribed" in note:
                gf = "hand-transcribed, no generator (%s)" % ",".join(r["files"][:2])
            r["gen"] = gf or "?"
            if not gf:
                missing.append("a2c native without a generated file: %s (%s)" % (sym, note))
        if gen_hits:
            r["tags"].append("gen")
            r.setdefault("gen", ",".join(gen_hits))
            r["gen_hits"] = gen_hits
        h = heat.get(N.name_at.get(N.I.funcs.get(sym, (0,))[0], sym) if not sym.startswith("@") else sym)
        if h:
            r["calls"], r["samples"] = h[2], h[1]
            if h[2] >= HOT_CALLS or h[1] >= HOT_SAMPLES:
                r["tags"].append("hot")
        if r["fam"] == "?":
            missing.append("native with no family (no source file registers its note or names its symbol): %s\t%s" % (sym, note))
        rows.append(r)

    def primary(r):
        t = r["tags"]
        for k in ("changed", "only380", "address", "a2c", "identical", "unresolved"):
            if k in t:
                return k
        return "?"
    for r in rows:
        r["primary"] = primary(r)
        if r["primary"] in ("unresolved", "?"):
            missing.append("unclassified native: %s\t%s" % (r["sym"], r["note"]))

    # ---- (g) layout ------------------------------------------------------------------------
    layout_hdrs = [p for p in S.files if p.endswith("_layout.h")]
    cls_of = {r["sym"]: verdiff.class_of(r["dem"]) for r in rows if not r["sym"].startswith("@")}
    lay_rows = []
    for L in layout:
        c = L["cls"]
        last = c.split("::")[-1]
        nats = [r for r in rows if cls_of.get(r["sym"]) == c]
        hdr_hits = []
        for p in S.files:
            if re.search(r"\b%s\b" % re.escape(last), S.text[p]) and (p.endswith("_layout.h") or "static_assert" in S.text[p]):
                for i, l in enumerate(S.text[p].split("\n"), 1):
                    if re.search(r"\b%s\b" % re.escape(last), l) and ("static_assert" in l or p.endswith("_layout.h")):
                        hdr_hits.append("%s:%d" % (rel(p), i))
        src_hits = sorted({rel(p) for p in S.files if re.search(r"\b%s\b" % re.escape(last), S.text[p])})
        for r in nats:
            r["tags"].append("layout%s" % ("!" if L["shifted"] else ""))
        lay_rows.append(dict(L, natives=nats, hdr_hits=hdr_hits, src_hits=src_hits))

    # ---- (f) hard-coded addresses in hand-written sources ----------------------------------
    def set_lib(h, lib_):
        h["lib"] = lib_
        kind, key, off, desc = h["r7"] if lib_ == "370" else h["r8"]
        h["kind"], h["target"] = kind, desc
        h["to370"] = h["as370"] if lib_ == "370" else h["cp370"]
        h["other"] = h["cp380"] if lib_ == "370" else h["cp370"]

    ALLOWED_380 = ("port/src/native/restore/", "port/src/restore/", "port/src/native/containers/containers_playcore.cpp",
                   "port/src/native/common/oracle")   # 3.8.0-only modules (P3 deletes them)
    HEX = re.compile(r"\b0x([0-9a-fA-F]{7})\b")
    SYMOFF = re.compile(r'(?:sym_addr|guest::sym|\bsym)\(\s*"(_Z\w+)"\s*\)\s*([+-])\s*(0x[0-9a-fA-F]+|\d+)')
    hard = []
    for p in S.files:
        if is_gen(p):
            continue
        for i, l in enumerate(S.text[p].split("\n"), 1):
            code = l.split("//")[0]
            comment = l.strip().startswith(("//", "*", "/*")) or code.strip() == ""
            for m in HEX.finditer(l):
                v = int(m.group(1), 16)
                in_comment = comment or m.start() >= len(code)
                # an ELF vaddr; a Ghidra address (vaddr + 0x100000) only when the line says so
                cands = [(v, False)]
                if re.search(r"ghidra|@0[0-9a-f]{7}", l, re.I):
                    cands.insert(0, (v - 0x100000, True))
                best = None   # (score, va, ghidra, (score, resolution) in 3.7.0, in 3.8.0)
                for va, ghidra in cands:
                    f7, f8 = O.fit(va, l), N.fit(va, l)
                    f7 = f7 if f7[1] and not (f7[1][0] == "fn" and va & 3) else (0, None)
                    f8 = f8 if f8[1] and not (f8[1][0] == "fn" and va & 3) else (0, None)
                    if re.search(r"\(3\.7\.0\)", l):     # a comment pins the line's values to 3.7.0
                        f7 = (max(f7[0], 9), f7[1]) if f7[1] else f7
                    sc = max(f7[0], f8[0])
                    if sc and (best is None or sc > best[0]):
                        best = (sc, va, ghidra, f7, f8)
                if not best:
                    continue
                _, va, ghidra, f7, f8 = best

                def as_ghidra(t):
                    return "%#x (Ghidra %#x)" % (int(t.split()[0], 16), int(t.split()[0], 16) + 0x100000) if ghidra and t.startswith("0x") else t
                h = dict(file=rel(p), line=i, val="0x" + m.group(1), va=va, ghidra=ghidra, comment=in_comment, test=is_test(p),
                         hist=bool(in_comment and re.search(r"3\.8\.0", l)), text=l.strip(), tie=f7[0] == f8[0],
                         # as a 3.7.0 value: itself, its 3.8.0 counterpart; as a 3.8.0 value: its 3.7.0 counterpart
                         r7=f7[1], r8=f8[1],
                         as370=as_ghidra("%#x" % va), cp380=as_ghidra(N.find(*f7[1][:3], changed)) if f7[1] else "none",
                         cp370=as_ghidra(O.find(*f8[1][:3], changed)) if f8[1] else "none")
                set_lib(h, "370" if f7[0] >= f8[0] else "380")
                hard.append(h)
            for m in SYMOFF.finditer(code):
                s_, sign, off = m.group(1), m.group(2), int(m.group(3), 0)
                if s_ in N.I.funcs or s_ in O.I.funcs:
                    st = "changed" if s_ in changed else ("only380" if s_ in only["3.8.0"] else "identical body: offset holds")
                    hard.append(dict(file=rel(p), line=i, val="%s%s%#x" % (s_, sign, off), va=None, ghidra=False, kind="symoff",
                                     target=s_, to370=st, comment=False, test=is_test(p), lib="both" if st.startswith("identical") else "380",
                                     tie=False, other="", hist=False, text=l.strip()))
    # ties (both libs fit equally well): the file's majority of decided values
    maj = collections.defaultdict(collections.Counter)
    for h in hard:
        if h["kind"] != "symoff" and not h["tie"]:
            maj[h["file"]][h["lib"]] += 1
    for h in hard:
        if h["kind"] != "symoff" and h["tie"]:
            c = maj[h["file"]]
            if c and c.most_common(1)[0][0] != h["lib"] and (h["r7"] if c.most_common(1)[0][0] == "370" else h["r8"]):
                set_lib(h, c.most_common(1)[0][0])
    for h in hard:
        # needs a change: a 3.8.0 value in code (comments naming 3.8.0 addresses are history)
        h["same"] = not (h["lib"] == "380" and not h["hist"])
        h["allowed"] = h["file"].startswith(ALLOWED_380)
        if h["lib"] == "380" and not h["hist"] and not h["allowed"] and not h["comment"]:
            missing.append("3.8.0 address in hand-written code: %s:%d %s (%s; 3.7.0: %s)" % (h["file"], h["line"], h["val"], h["target"], h["to370"]))

    # ---- generated files ---------------------------------------------------------------------
    gen_files = sorted({rel(p) for p in S.files if is_gen(p)} |
                       {rel(os.path.join(d, f)) for d, _, fs in os.walk(os.path.join(REPO, "port/src")) for f in fs if f.endswith(".inc")})
    trial = {}
    tp = os.path.join(OUTDIR, "regen-trial.tsv")
    if os.path.exists(tp):
        for r in read_tsv(tp):
            trial[(r[1], r[2])] = r
    gen_rows = []
    for g in gen_files:
        p = os.path.join(REPO, g)
        t = open(p, errors="replace").read()
        hdr = ""
        for l in t.split("\n")[:4]:
            m = GEN_HDR.search(l)
            if m:
                hdr = short(l.strip("/ "), 140)
                break
        meta = GEN.get(g)
        if not meta:
            missing.append("generated file without an entry in rebase_inventory.GEN: " + g)
            meta = ("?", "?", "")
        gsyms = set(re.findall(r'"(_Z\w+)"', t))
        nch = sorted(s for s in gsyms if s in changed)
        n38 = sorted(s for s in gsyms if s in only["3.8.0"])
        nmiss = sorted(s for s in gsyms if s not in O.I.funcs and s not in O.I.objects and s not in only["3.8.0"])
        addrs = [int(x, 16) for x in re.findall(r"\b0x([0-9a-f]{7})\b", t)]
        addrs = [a for a in addrs if N.text[0] <= a < N.hi]
        mlib = re.search(r"libSOA\.so: \S+ \(([^,]+), sha256 ([0-9a-f]{12})", "\n".join(t.split("\n")[:8]))
        glib = "%s (`%s…`)" % (mlib.group(1), mlib.group(2)) if mlib else "no stamp"
        gen_rows.append(dict(file=g, lib=glib, hdr=hdr, nnat=sum(1 for r in rows if g in r.get("gen_hits", ())), gen=meta[0], cmd=meta[1], note=meta[2], lines=t.count("\n"), nsyms=len(gsyms),
                             changed=nch, only380=n38, miss370=nmiss, naddr=len(addrs),
                             t380=trial.get((g, "380")), t370=trial.get((g, "370"))))
    # generator scripts: hard-coded lib path, 3.8.0 address literals, input lists
    gscripts = sorted({m.group(0) for r in gen_rows for m in re.finditer(r"tools/[\w.]+\.py", r["gen"])})
    gs_rows = []
    for gs in gscripts:
        t = open(os.path.join(REPO, gs)).read()
        uses_env = "genlib (default 3.7.0)" if "import genlib" in t else "elfinfo" in t or "a2c.py" in t or "spec_from_file_location('a2c'" in t or "a2c" in t and "importlib" in t
        hard380 = len(re.findall(r"config\.arm64_v8a", t))
        lits = [int(x, 16) for x in re.findall(r"\b0x([12][0-9a-f]{6})\b", t)]
        lits = [a for a in lits if N.func_of(a)]
        lists = sorted(set(re.findall(r"'(\w+_funcs\.txt|\w+_verified\.txt|\w+_executed\.txt)'", t)))
        prof = sorted(set(re.findall(r"work/profile/[\w.-]+", t)))
        lst = []
        for lf in lists:
            lp = os.path.join(REPO, "tools", lf)
            if os.path.exists(lp):
                names = [l.split("#")[0].split()[0] for l in open(lp) if l.split("#")[0].strip()]
                lst.append("%s: %d names, %d changed, %d only-3.8.0, %d not in 3.7.0" % (
                    lf, len(names), sum(n in changed for n in names), sum(n in only["3.8.0"] for n in names),
                    sum(n not in O.I.funcs and n not in only["3.8.0"] for n in names if n.startswith("_Z"))))
        gs_rows.append(dict(script=gs, env=uses_env, hard380=hard380, lits=len(lits), lists=lst, prof=prof))

    # ---- 3.8.0 references (P4) ---------------------------------------------------------------
    REFPAT = r"3\.8\.0|[xX][aA][pP][kK]|config\.arm64_v8a|assetinstalltime|playcore|home_sa\b|basmaster-3\.8\.0|smoke-base-380"
    ORAPAT = r"call370|oracle_lib|SOA_ORACLE_370|load_oracle_library|restore370|load_restore_library|SOA_RESTORE_370_LIB"
    SELF = ("tools/rebase_inventory.py", "docs/history/REBASE-370.md", "docs/history/rebase-370/")

    def git_grep(pat):
        r = subprocess.run(["git", "grep", "-n", "-I", "-E", pat, "--", ".", ":!emulator-viewer", ":!docs/history",
                            ":!docs/history/rebase-370", ":!tools/rebase_inventory.py", ":!docs/history/REBASE-370.md"],
                           capture_output=True, text=True, cwd=REPO)
        out = []
        for l in r.stdout.split("\n"):
            m = re.match(r"([^:]+):(\d+):(.*)", l)
            if m and not m.group(1).startswith(SELF):
                out.append((m.group(1), int(m.group(2)), m.group(3)))
        return out

    def ref_group(f):
        if f.endswith(".md") or f.startswith("docs/"):
            return "docs"
        if f.startswith("tools/"):
            return "tools"
        if f.startswith(("scripts/", "port/scripts/", "emulator/scripts/", "tests/", "server/scripts/")) or f.endswith(".sh"):
            return "scripts"
        if f.startswith("runtime/"):
            return "runtime (shared with the 3.8.0 viewer)"
        if "/gen/" in f:
            return "code (generated)"
        if f.startswith(("port/src", "server/", "emulator/src", "platform370/", "soa_save/")) or f.endswith((".cpp", ".h", ".py", ".c")):
            return "code"
        return "other"
    refs = git_grep(REFPAT)
    oracle = git_grep(ORAPAT)

    # ---- coverage comparison (item 4) ---------------------------------------------------------
    nat_canon = set()
    for r in rows:
        if r["sym"].startswith("@"):
            if r.get("fn380"):
                nat_canon.add(r["fn380"][0])
        else:
            a = N.I.funcs.get(r["sym"])
            nat_canon.add(N.name_at.get(a[0], r["sym"]) if a else r["sym"])
    covcmp = None
    emu = {k: v for k, v in cov.items() if k.startswith("emu")}
    prt = {k: v for k, v in cov.items() if k.startswith("port")}
    if emu:
        ex = {}
        for k, v in emu.items():
            for n, (va, t, s_, i_) in v["g"].items():
                e = ex.setdefault(n, dict(va=va, runs=[], self=0, incl=0))
                e["runs"].append(k.split("-", 1)[1])
                e["self"] += s_
                e["incl"] += i_
        port_ran = set()
        for v in prt.values():
            port_ran |= set(v["g"]) | set(v["n"])
        buckets = collections.defaultdict(list)
        for n, e in ex.items():
            if n.startswith("?"):
                b = "unnamed (no function start known to verdiff)"
            elif n in only["3.7.0"] or n not in N.I.funcs:
                b = "3.7.0-only (no 3.8.0 counterpart)"
            elif n in changed:
                b = "changed body (3.8.0 counterpart differs)"
            elif n in nat_canon:
                b = "native in the port (identical body)"
            elif n in port_ran:
                b = "guest in both (the port ran it as guest code)"
            else:
                b = "identical, never run by the port: guest code after the rebase"
            e["bucket"] = b
            buckets[b].append(n)
        covcmp = dict(ex=ex, buckets=buckets)
        with open(os.path.join(OUTDIR, "coverage-gap.tsv"), "w") as f:
            f.write("# 3.7.0 functions executed in the soa-emu runs (%s), bucketed against the port's natives and its coverage runs (%s).\n"
                    % (", ".join(sorted(emu)), ", ".join(sorted(prt)) or "none"))
            f.write("# the bucket 'native in the port' is left out (see natives.tsv)\n")
            f.write("bucket\tvaddr370\tfunction\truns\tself_samples\tincl_samples\tclass\n")
            names_all = sorted(ex)
            dd = dict(zip(names_all, demangle(names_all)))
            for n in sorted(ex, key=lambda n: (ex[n]["bucket"], -ex[n]["incl"], n)):
                e = ex[n]
                if e["bucket"].startswith("native in the port"):
                    continue
                f.write("%s\t%s\t%s\t%s\t%d\t%d\t%s\n" % (e["bucket"].split(" (")[0].split(":")[0], e["va"], short(dd.get(n, n), 160),
                                                        ",".join(e["runs"]), e["self"], e["incl"], verdiff.class_of(dd.get(n, n))))
            covcmp["dem"] = dd

    # ---- doc sections (item 3) ----------------------------------------------------------------
    cc_rows = []
    for lvl, h, ln, body in md_sections(os.path.join(REPO, "docs/client-changes.md")):
        d = lookup(CLIENT, h)
        if not d:
            missing.append("docs/client-changes.md heading without a decision: %s (line %d)" % (h, ln))
            d = ("?", "?", "?")
        cc_rows.append(dict(level=lvl, h=h, line=ln, dec=d[1], why=d[2]))
    rm_rows = []
    rfiles = sorted({rel(os.path.join(d, f)) for base in ("port/src/native/restore", "port/src/restore")
                     for d, _, fs in os.walk(os.path.join(REPO, base)) for f in fs})
    for f in rfiles:
        d = RESTORE_MODULES.get(f)
        if not d:
            missing.append("restore module without a decision: " + f)
            d = ("?", "?")
        t = open(os.path.join(REPO, f), errors="replace").read()
        regs = sorted(set(re.findall(r'NATIVE_FUNCTION\w*\(\s*"(_Z\w+)"', t)))
        st = ["%s: %s" % (dem.get(s) or demangle([s])[0], "changed" if s in changed else ("only-3.8.0" if s in only["3.8.0"] else "identical"))
              for s in regs]
        rm_rows.append(dict(file=f, dec=d[0], why=d[1], natives=st))
    sr_rows = []
    for lvl, h, ln, body in md_sections(os.path.join(REPO, "docs/server-rules.md")):
        marks = sorted(set(m.group(0) for m in SERVER_MARK.finditer(body + " " + h)))
        if not marks:
            continue
        d = lookup(SERVER, h)
        if not d:
            missing.append("docs/server-rules.md section mentioning %s without a decision: %s (line %d)" % (", ".join(marks), h, ln))
            d = ("?", "?", "?")
        sr_rows.append(dict(level=lvl, h=h, line=ln, marks=marks, dec=d[1], why=d[2]))

    # ---- write TSVs ---------------------------------------------------------------------------
    with open(os.path.join(OUTDIR, "natives.tsv"), "w") as f:
        f.write("# every soa --list-native row (tools/rebase_inventory.py); status is empty for identical bodies; gen = generated files naming the symbol (port/src/native/...)\n")
        f.write("symbol\tfamily\tprimary\ttags\tstatus\tgen\tcalls\tsamples\tnote\n")
        for r in rows:
            f.write("\t".join([r["sym"], r["fam"], r["primary"], ",".join(r["tags"]), "" if r["status"] == "identical" else r["status"],
                               r.get("gen", "").replace("port/src/native/", ""), str(r.get("calls", "")), str(r.get("samples", "")),
                               r["note"]]) + "\n")
    with open(os.path.join(OUTDIR, "address_bound.tsv"), "w") as f:
        f.write("key\tnote\tfunction_380\toffset\tstatus\tva370\tfiles\n")
        for r in rows:
            if "address" in r["tags"]:
                fn = r.get("fn380")
                f.write("%s\t%s\t%s\t%s\t%s\t%s\t%s\n" % (r["sym"], r["note"], fn[0] if fn else "", "%#x" % fn[2] if fn else "",
                                                         r["status"], "%#x" % r["va370"] if "va370" in r else "", ",".join(r["files"])))
    with open(os.path.join(OUTDIR, "hardcoded.tsv"), "w") as f:
        f.write("file\tline\tvalue\tlib\tkind\tghidra\ttarget\tto_370\tother_lib\tcomment\ttest\ttext\n")
        for h in hard:
            lib_ = h["lib"] + (" (tie)" if h.get("tie") else "") + (" (3.8.0-only module)" if h["allowed"] and h["lib"] == "380" else "") + (" (history comment)" if h["hist"] else "")
            f.write("%s\t%d\t%s\t%s\t%s\t%d\t%s\t%s\t%s\t%d\t%d\t%s\n" % (h["file"], h["line"], h["val"], lib_, h["kind"], h["ghidra"], h["target"],
                                                                         h["to370"], h["other"], h["comment"], h["test"], h["text"][:200]))
    with open(os.path.join(OUTDIR, "refs-380.tsv"), "w") as f:
        f.write("group\tfile\tline\ttext\n")
        for fl, ln, tx in refs:
            f.write("%s\t%s\t%d\t%s\n" % (ref_group(fl), fl, ln, tx.strip()[:220]))
        for fl, ln, tx in oracle:
            f.write("oracle/restore-image\t%s\t%d\t%s\n" % (fl, ln, tx.strip()[:220]))

    # ---- write the doc ------------------------------------------------------------------------
    W = []
    w = W.append
    prim = collections.Counter(r["primary"] for r in rows)
    tagc = collections.Counter(t for r in rows for t in r["tags"])
    fams = sorted({r["fam"] for r in rows})
    fam_c = {fa: collections.Counter() for fa in fams}
    for r in rows:
        fam_c[r["fam"]]["all"] += 1
        fam_c[r["fam"]][r["primary"]] += 1
        for t in r["tags"]:
            if t in ("hot", "layout", "layout!", "gen"):
                fam_c[r["fam"]][t] += 1
    hard_code = [h for h in hard if not h["comment"] and not h["test"]]
    hard_bad = [h for h in hard_code if not h["same"]]
    hard_by_fam = collections.Counter(family_of(os.path.join(REPO, h["file"])) for h in hard_bad)
    shifted = [L for L in lay_rows if L["shifted"]]

    w("# Rebase to 3.7.0: inventory (P0)")
    w("")
    w("Generated by `tools/rebase_inventory.py` (re-run it after any change; `--check` fails when something is unclassified). "
      "The plan is `docs/history/PLAN-rebase-370.md`. Full tables: `docs/history/rebase-370/*.tsv` (natives.tsv has every `--list-native` row). "
      "Inputs: `work/verdiff/` (`tools/verdiff.py`, 3.7.0 = `work/libSOA-3.7.0.so` vs 3.8.0 = the XAPK's lib), "
      "`build/port/soa --list-native` (without a build: the snapshot in `docs/history/rebase-370/natives.tsv`), the sources, and the coverage summaries `docs/history/rebase-370/coverage-*.tsv`.")
    w("")
    # The phases' progress notes (hand-written, between the markers) are kept across re-runs.
    try:
        old_doc = open(DOC).read()
    except OSError:
        old_doc = ""
    m = re.search(r"<!-- progress \(hand-written; kept by tools/rebase_inventory.py\) -->.*?<!-- /progress -->", old_doc, re.S)
    if m:
        w(m.group(0))
        w("")
    w("## Summary")
    w("")
    w("| Category | Count | Action | Section |")
    w("|---|---|---|---|")
    w("| Natives (`--list-native` rows) | %d | | 1 |" % len(rows))
    w("| (a) symbol natives on identical bodies | %d | keep; re-verify against the 3.7.0 guest | 1 |" % prim["identical"])
    chg_syms = {r["sym"] for r in rows if r["primary"] == "changed"}
    w("| (b) natives on changed bodies | %d rows, %d symbols (a symbol registered by two families is listed twice: coordinate those) | decide per function (drop to guest / port 3.7.0) | 1.1 |" % (prim["changed"], len(chg_syms)))
    w("| (c) natives on 3.8.0-only functions | %d | drop | 1.2 |" % prim["only380"])
    w("| (d) address-bound `@0x…` natives | %d (%d 3.7.0 already, %d unmappable) | remap (table gives the 3.7.0 address) | 1.3 |" % (
        tagc["address"], sum(1 for r in rows if r.get("status", "").startswith("3.7.0 already")), tagc["unmappable"]))
    w("| (e) a2c / transcribed natives (identical bodies) | %d (+%d on changed or 3.8.0-only bodies) | regenerate from 3.7.0 | 1.4, 2 |" % (prim["a2c"], sum(1 for r in rows if "a2c" in r["tags"] and r["primary"] != "a2c")))
    w("| … natives named in a generated file (registration tables, alias lists; tag `gen`) | %d | regenerate the file, re-check | 2 |" % tagc["gen"])
    w("| (f) hard-coded lib addresses in hand-written code (non-test, non-comment) | %d values: %d 3.7.0, %d 3.8.0 (%d of them in 3.8.0-only modules; %d not mappable automatically) | remap | 1.5 |" % (
        len(hard_code), sum(1 for h in hard_code if h["lib"] in ("370", "both")), len(hard_bad), sum(1 for h in hard_bad if h["allowed"]),
        sum(1 for h in hard_bad if not h["to370"].startswith("0x"))))
    w("| (g) layout.tsv classes | %d (%d with moved offsets) | check `*_layout.h` / byte offsets | 1.6 |" % (len(lay_rows), len(shifted)))
    w("| … natives that are methods of a class with moved offsets | %d | check | 1.6 |" % tagc["layout!"])
    w("| Hot natives (≥%d calls or ≥%d samples in the %s run) | %d | keep perf parity | 1 |" % (HOT_CALLS, HOT_SAMPLES, HEAT_RUN, tagc["hot"]))
    w("| Generated files (`gen/`, `*.inc`) | %d | regenerate (commands in 2) | 2 |" % len(gen_rows))
    w("| client-changes.md entries | %d (%s) | per entry | 3.1 |" % (len(cc_rows), ", ".join("%s %d" % kv for kv in collections.Counter(c["dec"].split(" ")[0] for c in cc_rows).most_common())))
    w("| restore modules | %d files | per file | 3.2 |" % len(rm_rows))
    w("| server-rules.md sections touching 3.8.0 behaviour | %d (%s) | per section | 3.3 |" % (len(sr_rows), ", ".join("%s %d" % kv for kv in collections.Counter(c["dec"].split(" ")[0] for c in sr_rows).most_common())))
    if covcmp:
        b = covcmp["buckets"]
        w("| 3.7.0 functions run by soa-emu | %d | | 4 |" % len(covcmp["ex"]))
        w("| … identical, never run by the port (guest after the rebase) | %d | profile; port later | 4 |" % len(b.get("identical, never run by the port: guest code after the rebase", [])))
        w("| … 3.7.0-only / changed bodies | %d / %d | guest code | 4 |" % (len(b.get("3.7.0-only (no 3.8.0 counterpart)", [])), len(b.get("changed body (3.8.0 counterpart differs)", []))))
    w("| 3.8.0 / XAPK / playcore / home_sa references (outside emulator-viewer/) | %d lines in %d files | P4 | 5 |" % (len(refs), len({r[0] for r in refs})))
    w("| 3.7.0 oracle / restore-image references | %d lines in %d files | P3 | 5 |" % (len(oracle), len({r[0] for r in oracle})))
    if missing:
        w("| **Unclassified (fails `--check`)** | %d | fix the tool's tables | |" % len(missing))
    w("")

    # P2 split
    w("### Proposed P2 split (by native family)")
    w("")
    w("Counts per family below (1). Work units: changed + address-bound + a2c natives, natives named in generated files, hard-coded values that move, natives on classes with moved offsets. The identical natives only need the family's selftests and live check re-run against the 3.7.0 guest.")
    w("")
    SPLIT = [
        ("P2-a models and containers", ["models", "containers", "libs", "engine", "engine/math"]),
        ("P2-b battle", ["battle", "event", "audio", "input", "gacha"]),
        ("P2-c UI, params and infobase", ["ui", "ui/cocos", "ui/screen", "params", "api", "restore", "common", "(top)"]),
        ("P2-d render, particles, dynamics, arena, objbase", ["render", "particles", "dynamics", "arena", "objbase"]),
    ]
    assigned = {f for _, fs in SPLIT for f in fs}
    w("| Agent | Families | Natives | Changed | Address | a2c | In gen files | Moved layouts | Hard-coded to remap | Hot |")
    w("|---|---|---|---|---|---|---|---|---|---|")
    for name, fs in SPLIT + [("(unassigned)", sorted(set(fams) - assigned))]:
        fs = [f for f in fs if f in fam_c]
        if not fs:
            continue
        s = collections.Counter()
        for f in fs:
            s.update(fam_c[f])
        w("| %s | %s | %d | %d | %d | %d | %d | %d | %d | %d |" % (name, ", ".join(fs), s["all"], s["changed"], s["address"], s["a2c"], s["gen"],
                                                                  s["layout!"], sum(hard_by_fam[f] for f in fs), s["hot"]))
    w("| P2-e generated tables and address remaps | the table generators (section 2), the %d `@0x` natives, `fakeapi_tables.inc` | | | %d | | | | | |" % (tagc["address"], tagc["address"]))
    w("")
    w("The restore family's natives (%d, %d of them on changed bodies) are deleted in P3 rather than ported. " % (fam_c.get("restore", {}).get("all", 0), fam_c.get("restore", {}).get("changed", 0)) +
      "P2-e runs first (the a2c regeneration and the remapped tables unblock the others); the families can then go in parallel. "
      "The a2c regeneration is per generator (section 2), so each family agent regenerates its own `gen/` file.")
    w("")

    # 1. natives by family
    w("## 1. Natives")
    w("")
    w("Primary class (one per native; the others are tags in `natives.tsv`): changed > only380 > address > a2c > identical. Tag `gen` = named in a generated file (needs that file regenerated). "
      "Family = the folder under `port/src/native/` of the file that registers the native (its note string), else the files naming its symbol. "
      "Hot = ≥%d calls or ≥%d self+child samples in `coverage-%s.tsv` (a 185 s `restore_session.sh` run; host-side self time per C++ function needs `SOA_PROFILE_HOST=1` + `port/scripts/host_profile.py` on the same build, not done here)." % (HOT_CALLS, HOT_SAMPLES, HEAT_RUN))
    w("")
    w("| Family | All | identical | changed | only380 | address | a2c | in gen files | layout (moved) | hot |")
    w("|---|---|---|---|---|---|---|---|---|---|")
    for fa in sorted(fams, key=lambda f: -fam_c[f]["all"]):
        c = fam_c[fa]
        w("| %s | %d | %d | %d | %d | %d | %d | %d | %d (%d) | %d |" % (fa, c["all"], c["identical"], c["changed"], c["only380"], c["address"], c["a2c"], c["gen"],
                                                                     c["layout"] + c["layout!"], c["layout!"], c["hot"]))
    w("")
    w("### 1.1 (b) Natives on changed bodies: decision needed")
    w("")
    w("Diff: `work/verdiff/fn/<symbol>.diff`; 3.7.0 decompile: `tools/decomp.sh --v370 <out> '<regex>'`.")
    w("")
    w("| Family | Symbol | Sizes 3.7.0 → 3.8.0 | Δ instrs | verdiff | Native note |")
    w("|---|---|---|---|---|---|")
    for r in sorted((r for r in rows if r["primary"] == "changed"), key=lambda r: (r["fam"], r["dem"])):
        e = changed[r["sym"]]
        w("| %s | `%s` | %d → %d | %d | %s | %s%s |" % (r["fam"], md_escape(short(r["dem"], 100)), e["old_size"], e["new_size"], e["diff"], md_escape(short(e["what"], 90)),
                                                  md_escape(r["note"]), " **hot**" if "hot" in r["tags"] else ""))
    w("")
    w("### 1.2 (c) Natives on 3.8.0-only functions: drop")
    w("")
    w("| Family | Symbol | Note | 3.7.0 counterpart |")
    w("|---|---|---|---|")
    for r in sorted((r for r in rows if r["primary"] == "only380"), key=lambda r: (r["fam"], r["dem"])):
        cp = re.search(r"counterpart: (.*)\)", r["status"])
        w("| %s | `%s` | %s | %s |" % (r["fam"], md_escape(short(r["dem"], 100)), md_escape(r["note"]), ("`%s`" % cp.group(1)) if cp else ""))
    if sigs:
        w("")
        w("verdiff's signature changes (same qualified name, other parameters):")
        w("")
        for s in sigs:
            w("- `%s` → `%s` (%s, Δ %d)" % (md_escape(short(s["old"], 100)), md_escape(short(s["new"], 100)), s["size"], s["diff"]))
    w("")
    w("### 1.3 (d) Address-bound natives")
    w("")
    w("The 3.8.0 address, the function containing it (verdiff naming: exports, `anon:<prev>#k` statics, `lambda:<encl>#k.slot` std::function slots, paired by name across builds), and the 3.7.0 address at the same offset when that function's body is identical. A mnemonic mismatch at the two addresses is flagged. Full table: `docs/history/rebase-370/address_bound.tsv`.")
    w("")
    ab = [r for r in rows if "address" in r["tags"]]
    abc = collections.Counter(re.sub(r" \(insn.*", " (insn mismatch)", re.sub(r"^3\.7\.0 already.*", "3.7.0 already", r["status"]).split(" 0x")[0]) for r in ab)
    w("Status: " + ", ".join("%s %d" % kv for kv in abc.most_common()) + ".")
    w("")
    w("| Key | Note | 3.8.0 function + offset | Status |")
    w("|---|---|---|---|")
    for r in ab:
        w("| `%s` | %s | `%s` | %s |" % (r["sym"], md_escape(r["note"]), md_escape(short(r["dem"], 90)), md_escape(r["status"])))
    w("")
    w("### 1.4 (e) a2c / transcribed natives")
    w("")
    a2 = collections.Counter((r.get("gen", "?"), r["primary"]) for r in rows if "a2c" in r["tags"])
    gens = sorted({g for g, _ in a2})
    w("| Generated file | Natives | on identical bodies | on changed bodies | other |")
    w("|---|---|---|---|---|")
    for g in gens:
        tot = sum(v for (gg, _), v in a2.items() if gg == g)
        w("| `%s` | %d | %d | %d | %d |" % (g, tot, a2[(g, "a2c")], a2[(g, "changed")], tot - a2[(g, "a2c")] - a2[(g, "changed")]))
    w("")
    w("### 1.5 (f) Hard-coded lib addresses in hand-written sources")
    w("")
    w("7-hex-digit literals outside `gen/` that point into either lib (ELF vaddrs; Ghidra addresses = vaddr + 0x100000 only where the line says so), and `sym(\"…\") ± offset` into functions. "
      "Each value's lib is the one it fits better (the tool's docstring: a function start, a string start, a GOT slot, or a string / symbol the line names; ties go to the file's majority); "
      "by lib: %s (`hardcoded.tsv` column `lib`; `other_lib` is the counterpart in the other lib). A 3.8.0 value "
      % ", ".join("%s %d" % kv for kv in collections.Counter(h["lib"] for h in hard).most_common()) +
      "is resolved to what it points at, then found in 3.7.0: a function + offset (\"changed\" = the function's body changed, the offset doesn't carry), a data object + offset, "
      "a .rodata string (found by content), a GOT slot (by its symbol), a std::function / lambda vtable (by the code pointer in it), or the nearest exported symbol (a guess, marked). "
      "%d values in all; %d in code of non-test files, of which %d need a new value; %d in tests; %d in comments. By kind: %s. Full list: `docs/history/rebase-370/hardcoded.tsv`." %
      (len(hard), len(hard_code), len(hard_bad), sum(1 for h in hard if h["test"] and not h["comment"]), sum(1 for h in hard if h["comment"]),
       ", ".join("%s %d" % kv for kv in collections.Counter(h["kind"] for h in hard).most_common())))
    unm = [h for h in hard_bad if not h["to370"].startswith("0x")]
    if unm:
        w("")
        w("Not mapped automatically, non-test code (%d): %s." % (len(unm), "; ".join("`%s:%d` %s → %s" % (h["file"].replace("port/src/native/", ""), h["line"], md_escape(short(h["target"], 60)), h["to370"]) for h in unm[:40])))
    w("")
    byf = collections.defaultdict(list)
    for h in hard_bad:
        byf[h["file"]].append(h)
    w("| File | Values needing a new address | Examples (line: value, target → 3.7.0) |")
    w("|---|---|---|")
    for fl in sorted(byf, key=lambda x: -len(byf[x])):
        hs = byf[fl]
        ex_ = "; ".join("%d: `%s` %s → %s" % (h["line"], h["val"], md_escape(short(h["target"], 50)), h["to370"]) for h in hs[:3])
        w("| `%s` | %d | %s |" % (fl, len(hs), ex_))
    w("")
    tst = collections.Counter(h["file"] for h in hard if h["test"] and not h["comment"] and not h["same"])
    if tst:
        w("Tests with 3.8.0 literals (they fail or test the wrong function after the rebase): " + ", ".join("`%s` (%d)" % kv for kv in tst.most_common()) + ".")
        w("")
    w("### 1.6 (g) Layout differences (`work/verdiff/layout.tsv`)")
    w("")
    w("Only classes whose methods' field offsets moved matter for natives; the others are listed because verdiff checked them (no moved offset found). "
      "`*_layout.h` headers in the tree: %s." % ", ".join("`%s`" % rel(p) for p in layout_hdrs))
    w("")
    w("| Class | Moved offsets (3.7.0>3.8.0 (uses)) | Natives on its methods | `_layout.h` / static_assert hits | Other sources naming it |")
    w("|---|---|---|---|---|")
    for L in sorted(lay_rows, key=lambda L: (-L["shifted"], L["cls"])):
        if not L["shifted"]:
            continue
        w("| `%s` | %s | %d%s | %s | %s |" % (L["cls"], short(L["shifts"], 120), len(L["natives"]),
                                         (" (" + ", ".join(sorted({r["primary"] for r in L["natives"]})) + ")") if L["natives"] else "",
                                         ", ".join(L["hdr_hits"][:4]) or "none", ", ".join("`%s`" % s for s in L["src_hits"][:5]) or "none"))
    w("")
    nos = [L for L in lay_rows if not L["shifted"]]
    w("No moved offsets (%d): %s." % (len(nos), ", ".join("`%s`%s" % (L["cls"], " (%d natives)" % len(L["natives"]) if L["natives"] else "") for L in nos)))
    w("")

    # 2. generated files
    w("## 2. Generated files")
    w("")
    w("Every `port/src/native/**/gen/*` and `*.inc`. Generators that load the lib through `tools/elfinfo.py` (directly or via `a2c.py`) honour `SOA_LIB`; "
      "the regeneration command sets it to the 3.7.0 lib. `syms` = quoted mangled names in the file, checked against verdiff; `addrs` = 3.8.0 lib addresses in the file. "
      "Trial = a run of the generator against each lib (`docs/history/rebase-370/regen-trial.tsv`, made once by the P0 agent): rc and how many lines differ from the committed file.")
    w("")
    w("| File | Lib (header stamp) | Generator | Natives named | syms (changed / only-3.8.0 / not in 3.7.0) | addrs | Trial 3.8.0 (P0) | Trial 3.7.0 (P0) | Regenerate | Notes |")
    w("|---|---|---|---|---|---|---|---|---|---|")

    def tri(t):
        if not t:
            return "–"
        what = re.sub(r"\(\{.*?\}\)", "", t[6]).split(",")[0] if re.search(r"\d+ (bodies|transcribed)", t[6]) else ""
        return ("rc %s, %s diff lines%s" % (t[3], t[5], (", " + md_escape(short(what, 40))) if what else "")) if t[3] == "0" else ("**rc %s**: %s" % (t[3], md_escape(short(t[6], 80))))
    for g in gen_rows:
        w("| `%s` | %s | %s | %d | %d (%d / %d / %d) | %d | %s | %s | `%s` | %s |" % (g["file"], g["lib"], md_escape(g["gen"]), g["nnat"], g["nsyms"], len(g["changed"]), len(g["only380"]), len(g["miss370"]),
                                                                          g["naddr"], tri(g["t380"]), tri(g["t370"]), md_escape(g["cmd"]), md_escape(g["note"])))
    w("")
    ch_gen = [(g["file"], s) for g in gen_rows for s in g["changed"] + g["only380"]]
    if ch_gen:
        w("Symbols in generated files whose 3.7.0 body changed or that are 3.8.0-only: " + "; ".join("`%s`: `%s`" % (f.split("/")[-1], md_escape(short(demangle([s])[0], 80))) for f, s in ch_gen[:40]) + ("…" if len(ch_gen) > 40 else "") + ".")
        w("")
    w("P0's trial findings (`regen-trial.tsv`, before P2-e; all fixed in P2-e, see Progress):")
    w("")
    w("- Every generator runs against the 3.7.0 lib (rc 0), but the a2c outputs differ by thousands of lines: the addresses in comments, tables and constants move, so review the diffs normalised.")
    w("- `gen_dynamics_a2c.py` against 3.7.0 transcribes **6 bodies instead of 96**: its function list is 3.8.0 `addr:size` literals plus an executed set read from `work/profile/restore-20260929` (3.8.0 addresses). Remap both (or switch to names) before regenerating.")
    w("- `gen_containers_a2c.py` does not reproduce the committed file even against 3.8.0 (26,566 diff lines): the committed file was made with its `executed.txt native.txt` arguments (the executed-only Yayoi / playcore / Global families). Regenerate with a 3.7.0 coverage list (`docs/history/rebase-370/coverage-emu-*.tsv`) and drop playcore (3.8.0-only).")
    w("- `gen_aska_math_a2c.py`'s `collision_spec()` runs `nm` on the hard-coded 3.8.0 lib path, so a 3.7.0 run mixes libs; it also doesn't reproduce the committed file exactly against 3.8.0 (388 lines). `gen_cocos_a2c.py` (734 lines against 3.8.0) lists 3.8.0 `addr:size` literals.")
    w("- `gen_parameter_tables.py` and `api_wire.py --gen-inc` give identical output for both libs; `gen_containers_tables.py` differs by 4 lines and `gen_loader_tables.py` by 438.")
    w("")
    w("Generator scripts:")
    w("")
    w("| Script | Lib via SOA_LIB | Hard-coded 3.8.0 lib path | 3.8.0 function addresses in the script | Input lists | 3.8.0 profile inputs |")
    w("|---|---|---|---|---|---|")
    for s in gs_rows:
        w("| `%s` | %s | %s | %s | %s | %s |" % (s["script"], s["env"] if isinstance(s["env"], str) else "yes" if s["env"] else "**no**", ("**%d**" % s["hard380"]) if s["hard380"] else "no",
                                             ("**%d**" % s["lits"]) if s["lits"] else "0", "; ".join(s["lists"]) or "", ", ".join(s["prof"])))
    w("")

    # 3. client changes
    w("## 3. 3.8.0-only client changes and server rules")
    w("")
    w("### 3.1 `docs/client-changes.md`")
    w("")
    w("| Line | Entry | Decision | Reason |")
    w("|---|---|---|---|")
    for c in cc_rows:
        w("| %d | %s%s | **%s** | %s |" % (c["line"], "  " * (c["level"] - 2), md_escape(short(c["h"].replace("`", ""), 100)), c["dec"], md_escape(c["why"])))
    w("")
    w("### 3.2 Restore modules (`port/src/native/restore/`, `port/src/restore/`)")
    w("")
    w("| File | Decision | Reason | Natives registered (verdiff status of the symbol) |")
    w("|---|---|---|---|")
    for m in rm_rows:
        w("| `%s` | **%s** | %s | %s |" % (m["file"], m["dec"], md_escape(m["why"]), md_escape("; ".join(short(x, 90) for x in m["natives"])) or "–"))
    w("")
    w("Other code that exists for 3.8.0 only, for P3: the 3.7.0 oracle (`t.call370`, `oracle_lib`, `SOA_ORACLE_370`) and the restore image loader: %d lines in %d files (`docs/history/rebase-370/refs-380.tsv`, group `oracle/restore-image`): %s." %
      (len(oracle), len({o[0] for o in oracle}), ", ".join("`%s` (%d)" % kv for kv in collections.Counter(o[0] for o in oracle).most_common(25))))
    w("")
    w("### 3.3 `docs/server-rules.md` sections that mention 3.8.0-specific client behaviour")
    w("")
    w("Sections whose text matches `%s`." % SERVER_MARK.pattern)
    w("")
    w("| Line | Section | Matches | Decision | Reason |")
    w("|---|---|---|---|---|")
    for c in sr_rows:
        w("| %d | %s%s | %s | **%s** | %s |" % (c["line"], "  " * (c["level"] - 2), md_escape(short(c["h"].replace("`", ""), 90)), ", ".join(c["marks"]), c["dec"], md_escape(c["why"])))
    w("")

    # 4. coverage
    w("## 4. 3.7.0 coverage (soa-emu) vs the port")
    w("")
    if not covcmp:
        w("No coverage summaries (`docs/history/rebase-370/coverage-emu-*.tsv`); run the sessions with `SOA_COVERAGE` and `--coverage KIND=DIR`.")
    else:
        for k, v in sorted(cov.items()):
            w("- `coverage-%s.tsv`: %s" % (k, v["hdr"].lstrip("# ")))
        w("")
        w("**What these runs don't cover.** Both soa-emu sessions used a pre-downloaded phone (`EMU_DATA`, 'the game data is on the phone; no download'), so the downloader ran only its manifest / verify / version checks, not a bulk download "
          "(a run without `EMU_DATA` downloads ~3 GB from soa-server's CDN). `CPhase_Relogin` and `CPhase_SyncServerTime` never ran: no script triggers a session expiry or a server-time resync. "
          "Those paths stay guest code after the rebase like the rest; profile them once a session reaches them.")
        w("")
        w("How they were made: `SOA_COVERAGE=DIR SOA_PROFILE=DIR` (runtime/src/core/profile.cpp; soa-emu links the runtime, so it works there too) over "
          "`EMU_DATA=<a downloaded phone> FRESH_KVS=1 emulator/scripts/emulator_session.sh [--new-player]` and `port/scripts/restore_session.sh` / `tutorial_session.sh`, "
          "raw output in `work/rebase/cov-*/prof`, then `tools/rebase_inventory.py --coverage KIND=DIR`. "
          "**Coverage is first-use only** (a one-shot trap per function entry, no execution counts); the counts below are profiler samples at 1 kHz "
          "(self / inclusive over all threads), the closest thing to an execution weight. A 3.7.0 function with 0 samples ran, but briefly.")
        w("")
        w("| Bucket | Functions | Inclusive samples |")
        w("|---|---|---|")
        for b, ns in sorted(covcmp["buckets"].items(), key=lambda x: -len(x[1])):
            w("| %s | %d | %d |" % (b, len(ns), sum(covcmp["ex"][n]["incl"] for n in ns)))
        w("")
        dd = covcmp["dem"]
        for b in ("3.7.0-only (no 3.8.0 counterpart)", "changed body (3.8.0 counterpart differs)", "identical, never run by the port: guest code after the rebase"):
            ns = covcmp["buckets"].get(b, [])
            if not ns:
                continue
            w("#### %s: %d" % (b, len(ns)))
            w("")
            bycls = collections.defaultdict(list)
            for n in ns:
                bycls[verdiff.class_of(dd.get(n, n))].append(n)
            w("By class (top 60 by inclusive samples; full list `docs/history/rebase-370/coverage-gap.tsv`):")
            w("")
            w("| Class | Functions | Self / incl. samples | Runs | Examples |")
            w("|---|---|---|---|---|")
            for c, cn in sorted(bycls.items(), key=lambda x: (-sum(covcmp["ex"][n]["incl"] for n in x[1]), -len(x[1])))[:60]:
                si = sum(covcmp["ex"][n]["self"] for n in cn)
                ii = sum(covcmp["ex"][n]["incl"] for n in cn)
                runs = sorted({r_ for n in cn for r_ in covcmp["ex"][n]["runs"]})
                exs = ", ".join("`%s`" % md_escape(short(re.sub(r"\(.*", "()", dd.get(n, n)), 60)) for n in sorted(cn, key=lambda n: -covcmp["ex"][n]["incl"])[:3])
                w("| `%s` | %d | %d / %d | %s | %s |" % (md_escape(c), len(cn), si, ii, ",".join(runs), exs))
            w("")
        key = ["CPhase_Relogin", "CPhase_SyncServerTime", "CGameResourceDownloader", "NetworkApiCaller", "CPhase_Login", "CPhase_DataDownload", "CTitle", "Downloader"]
        w("Named in the plan (functions per class executed by soa-emu, by bucket):")
        w("")
        for k in key:
            cn = [n for n in covcmp["ex"] if k in dd.get(n, n)]
            if not cn:
                w("- `%s`: none executed in these runs" % k)
                continue
            bc = collections.Counter(covcmp["ex"][n]["bucket"].split(" (")[0].split(":")[0] for n in cn)
            w("- `%s`: %d functions (%s)" % (k, len(cn), ", ".join("%s %d" % kv for kv in bc.most_common())))
        w("")

    # 5. references
    w("## 5. 3.8.0 references (P4)")
    w("")
    w("`git grep -E '%s'` outside `emulator-viewer/` and `docs/history/` (and this inventory). Full list with lines: `docs/history/rebase-370/refs-380.tsv`. "
      "`runtime/` is shared with the 3.8.0 viewer (e.g. `java_playcore.cpp` serves it): move such code behind the viewer, don't just delete it." % REFPAT)
    w("")
    grp = collections.defaultdict(lambda: collections.Counter())
    for fl, ln, tx in refs:
        grp[ref_group(fl)][fl] += 1
    for gname in sorted(grp, key=lambda g: -sum(grp[g].values())):
        c = grp[gname]
        w("**%s**: %d lines in %d files: %s" % (gname, sum(c.values()), len(c), ", ".join("`%s` (%d)" % kv for kv in c.most_common())))
        w("")

    if missing:
        w("## Unclassified (fix the tool's tables)")
        w("")
        for m in missing[:200]:
            w("- " + md_escape(m))
        w("")
    open(DOC, "w").write("\n".join(W) + "\n")
    print("wrote %s and docs/history/rebase-370/*.tsv: %d natives (%s); %d unclassified" % (rel(DOC), len(rows), ", ".join("%s %d" % kv for kv in prim.most_common()), len(missing)), file=sys.stderr)
    if args.check and missing:
        for m in missing[:50]:
            print("UNCLASSIFIED:", m, file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
