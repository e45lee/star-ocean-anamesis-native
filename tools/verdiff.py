"""Behaviour diff between two libSOA.so builds (default: 3.7.0 online vs 3.8.0 offline).

History tool: it made the 3.7.0 vs 3.8.0 comparison (docs/history/libsoa-3.7.0-vs-3.8.0.md);
the port runs 3.7.0 only. Still usable on any two builds.

Usage: verdiff.py [--old LIB] [--new LIB] [--out DIR] [-j N]

For every function present in both builds (by symbol name) the instruction streams are
disassembled with capstone and normalised: PC-relative addresses (adrp+add/ldr/str pairs, adr,
literal loads) and branch targets are replaced by what they point at: a symbol (+offset), a
PLT import, a GOT slot's symbol, a .rodata string's text, or the content of other .rodata
constants. Branches inside the function become offsets from its start. So a function whose only
differences are relocation/layout shifts compares equal; anything left is a real change,
including same-size changes a size diff misses.

Unnamed functions (static functions, not in .dynsym) are found through .eh_frame and named by
position ("anon:<preceding named function>#k"), so calls to them compare across builds and they
are diffed like named ones.

Also diffed: .rodata strings, vtable slots (by target symbol), .init_array (by the normalised
bodies of the static-init functions), and the JNI entry points (JNI_OnLoad plus the
JNINativeMethod tables handed to RegisterNatives).

Outputs in DIR (default work/verdiff): report.md, changed.tsv, strings.tsv, vtables.tsv,
and fn/<name>.diff (normalised unified diffs of the changed functions).
"""
import argparse
import bisect
import difflib
import os
import re
import struct
import subprocess
import sys
from collections import defaultdict
from multiprocessing import Pool

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OLD = os.path.join(REPO, "work/libSOA-3.7.0.so")
NEW = os.path.join(REPO, "work/extracted/config.arm64_v8a/lib/arm64-v8a/libSOA.so")

BRANCH = {"b", "bl", "cbz", "cbnz", "tbz", "tbnz"}
SEP = " \u27c2 "   # "raw SEP resolved": base page from an adrp in another block (raw form is canonical)
SEPL = " \u27c2l "  # "raw SEPL resolved": base page from the linear path (resolved form is canonical)


def same_line(x, y):
    if x == y:
        return True
    xp, yp = split2(x), split2(y)
    if xp and yp:
        return xp[0] == yp[0] or xp[1] == yp[1]
    return False


def split2(l):
    for sep in (SEPL, SEP):
        if sep in l:
            return l.split(sep, 1)
    return None


def key(l):
    if SEPL in l:
        return l.split(SEPL, 1)[1]
    return l.split(SEP, 1)[0]


def same(a, b):
    return len(a) == len(b) and all(same_line(x, y) for x, y in zip(a, b))


HEX = re.compile(r"#(-?0x[0-9a-f]+|-?\d+)")


def printable(b):
    return b and all(32 <= c < 127 or c in (9, 10, 13) for c in b)


class Image:
    def __init__(self, path):
        self.path = path
        self.data = open(path, "rb").read()
        self.elf = ELFFile(open(path, "rb"))
        self.segs = [s for s in self.elf.iter_segments() if s["p_type"] == "PT_LOAD"]
        self.secs = {}
        for s in self.elf.iter_sections():
            if s["sh_addr"]:
                self.secs[s.name] = (s["sh_addr"], s["sh_addr"] + s["sh_size"])
        self._syms()
        self._relocs()
        self._plt()
        self._eh_funcs()
        self._discover()

    # --- raw access -------------------------------------------------------------------------
    def v2o(self, va):
        for s in self.segs:
            if s["p_vaddr"] <= va < s["p_vaddr"] + s["p_filesz"]:
                return va - s["p_vaddr"] + s["p_offset"]
        return None

    def read(self, va, n):
        o = self.v2o(va)
        return None if o is None else self.data[o:o + n]

    def cstr(self, va, maxlen=256):
        b = self.read(va, maxlen)
        if b is None:
            return None
        return b.split(b"\0", 1)[0]

    def section_of(self, va):
        for n, (a, b) in self.secs.items():
            if a <= va < b:
                return n
        return None

    # --- symbols ----------------------------------------------------------------------------
    def _syms(self):
        self.funcs = {}      # name -> (addr, size)
        self.objects = {}    # name -> (addr, size)
        by_addr = {}
        dynsym = self.elf.get_section_by_name(".dynsym")
        for s in dynsym.iter_symbols():
            if not s.name or not s["st_value"]:
                continue
            t = s["st_info"]["type"]
            if t == "STT_FUNC":
                self.funcs[s.name] = (s["st_value"], s["st_size"])
            elif t == "STT_OBJECT":
                self.objects[s.name] = (s["st_value"], s["st_size"])
            # Prefer the shortest name at an address (C1 over C2 is arbitrary but stable).
            cur = by_addr.get(s["st_value"])
            if cur is None or (len(s.name), s.name) < (len(cur), cur):
                by_addr[s["st_value"]] = s.name
        self.by_addr = by_addr
        self.addrs = sorted(by_addr)

    def _relocs(self):
        """reloc_at: address -> ('sym', name, addend) | ('rel', target)."""
        self.reloc_at = {}
        self.got2name = {}
        dynsym = self.elf.get_section_by_name(".dynsym")
        for sec in self.elf.iter_sections():
            if not isinstance(sec, RelocationSection):
                continue
            for r in sec.iter_relocations():
                if r["r_info_sym"]:
                    n = dynsym.get_symbol(r["r_info_sym"]).name
                    self.reloc_at[r["r_offset"]] = ("sym", n, r["r_addend"])
                    self.got2name[r["r_offset"]] = n
                else:
                    self.reloc_at[r["r_offset"]] = ("rel", r["r_addend"])

    def _plt(self):
        self.plt = {}
        plt = self.elf.get_section_by_name(".plt")
        base, code = plt["sh_addr"], plt.data()
        for off in range(0x20, len(code), 16):
            w0, w1 = struct.unpack_from("<II", code, off)
            if w0 & 0x9F000000 != 0x90000000:
                continue
            pc = base + off
            immlo, immhi = (w0 >> 29) & 3, (w0 >> 5) & 0x7FFFF
            imm = (immhi << 2) | immlo
            if imm & (1 << 20):
                imm -= 1 << 21
            page = (pc & ~0xFFF) + (imm << 12)
            disp = ((w1 >> 10) & 0xFFF) * 8
            self.plt[pc] = self.got2name.get(page + disp, "?")

    def _eh_funcs(self):
        """All function extents from .eh_frame FDEs: start -> size."""
        self.eh = {}
        try:
            dw = self.elf.get_dwarf_info()
            for e in dw.EH_CFI_entries():
                if "initial_location" in e.header:
                    self.eh[e.header["initial_location"]] = e.header["address_range"]
        except Exception as ex:  # pragma: no cover
            print("eh_frame parse failed:", ex, file=sys.stderr)
        self.eh_starts = sorted(self.eh)

    def _discover(self):
        """Function starts beyond .dynsym: .eh_frame FDEs, BL targets, and code pointers in
        relocated data (vtable slots). Lambdas behind std::function are named from their
        __func vtable's typeinfo: "lambda:<enclosing mangled fn>#<k>.<slot>", k = rank of the
        lambda's $_N among the enclosing function's lambdas (the per-TU $_N numbering shifts
        when lambdas elsewhere in the file are added or removed)."""
        t0, t1 = self.secs[".text"]
        code = self.read(t0, t1 - t0)
        starts = set(self.eh)
        for i, w in enumerate(struct.unpack("<%dI" % (len(code) // 4), code[: len(code) // 4 * 4])):
            if w & 0xFC000000 == 0x94000000:
                off = w & 0x3FFFFFF
                if off & (1 << 25):
                    off -= 1 << 26
                t = t0 + i * 4 + off * 4
                if t0 <= t < t1:
                    starts.add(t)
        for va, r in self.reloc_at.items():
            if r[0] == "rel" and t0 <= r[1] < t1:
                starts.add(r[1])
        # std::function __func vtables: [offset-to-top=0][typeinfo*][slots...]
        lam_raw = {}
        ra = self.reloc_at
        for va, r in ra.items():
            if r[0] != "rel" or self.section_of(r[1]) not in (".data.rel.ro", ".data"):
                continue
            tn = ra.get(r[1] + 8)
            if not tn or tn[0] != "rel" or self.section_of(tn[1]) != ".rodata":
                continue
            name = self.cstr(tn[1], 1024)
            if not name or not name.startswith(b"NSt6__ndk110__function6__funcI"):
                continue
            slots = []
            k = va + 8
            while True:
                rr = ra.get(k)
                if not rr or rr[0] != "rel" or not (t0 <= rr[1] < t1):
                    break
                slots.append(rr[1])
                k += 8
            if slots:
                lam_raw[va] = (name.decode("latin1"), slots)
        by_encl = defaultdict(set)
        parsed = {}
        for va, (name, slots) in lam_raw.items():
            m = None
            for mm in re.finditer(r"E(\d+)(\$_\d+)", name):
                if int(mm.group(1)) == len(mm.group(2)):
                    m = mm
                    break
            if m and name.startswith("NSt6__ndk110__function6__funcIZ"):
                encl = name[len("NSt6__ndk110__function6__funcIZ"):m.start()]
                n = int(m.group(2)[2:])
                by_encl[encl].add(n)
                parsed[va] = (encl, n)
        self.lambda_names = {}
        for va, (name, slots) in lam_raw.items():
            if va in parsed:
                encl, n = parsed[va]
                base = "lambda:%s#%d" % (encl, sorted(by_encl[encl]).index(n))
            else:
                base = "lambda:" + name[len("NSt6__ndk110__function6__funcI"):][:200]
            for i, a in enumerate(slots):
                if a not in self.by_addr:
                    self.lambda_names.setdefault(a, "%s.%d" % (base, i))
        starts |= set(self.lambda_names)
        starts |= {a for a, _ in self.funcs.values() if t0 <= a < t1}
        self.starts = sorted(starts)

    def extent(self, a):
        """Size of an unnamed function: up to the next known start (FDE size if it has one)."""
        if a in self.eh:
            return self.eh[a]
        i = bisect.bisect_right(self.starts, a)
        nxt = self.starts[i] if i < len(self.starts) else self.secs[".text"][1]
        return min(nxt - a, 65536)

    def nearest(self, va):
        i = bisect.bisect_right(self.addrs, va) - 1
        if i < 0:
            return None, 0
        a = self.addrs[i]
        return self.by_addr[a], va - a


class Normaliser:
    def __init__(self, img, anon_names=None):
        self.img = img
        self.anon = anon_names or {}   # addr -> name for unnamed functions
        self.md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
        t = img.secs[".text"]
        self.text = t

    def code_name(self, va):
        img = self.img
        if va in img.plt:
            # a call through the PLT and a direct call to the same function are the same thing
            return img.plt[va] if img.plt[va] in img.funcs else "PLT:" + img.plt[va]
        if va in img.by_addr:
            return img.by_addr[va]
        if va in self.anon:
            return self.anon[va]
        # inside an unnamed function? use it; else nearest symbol
        i = bisect.bisect_right(img.starts, va) - 1
        if i >= 0:
            s = img.starts[i]
            if va < s + img.extent(s):
                base = img.by_addr.get(s) or self.anon.get(s)
                if base:
                    return "%s+%#x" % (base, va - s)
                return "anon+?"
        n, off = img.nearest(va)
        return "%s+%#x" % (n, off) if n else "?%#x" % va

    def data_name(self, va, width=16, load=False):
        img = self.img
        sec = img.section_of(va)
        if sec in (".text", ".plt"):
            return self.code_name(va)
        if sec == ".got":
            r = img.reloc_at.get(va)
            if r and r[0] == "sym":
                return "GOT:" + r[1] + ("+%d" % r[2] if r[2] else "")
            if r:
                return "GOT->" + self.data_name(r[1])
            return "GOT:?"
        if va in img.by_addr:
            return img.by_addr[va]
        if sec == ".rodata":
            s = None if load else img.cstr(va)
            if s is not None and (s == b"" or printable(s)):
                # lambda type names carry the per-TU $_N counter, which shifts between builds
                return "str:" + re.sub(r"\d+\$_\d+", "$_N", repr(s.decode("latin1")))
            n, off = img.nearest(va)
            if n and img.objects.get(n) and off < img.objects[n][1]:
                return "%s+%#x" % (n, off)
            # Constant content (16 bytes), with self-relative int32 words that point into code
            # (switch tables) masked, since those move with the layout.
            if width < 4:
                b = img.read(va, width)
                return "rodata#" + (b.hex() if b else "?")
            words = []
            for i in range(width // 4):
                b = img.read(va + 4 * i, 4)
                if not b:
                    break
                v = struct.unpack("<i", b)[0]
                words.append("~" if v < 0 and img.section_of(va + v) == ".text" else b.hex())
            return "rodata#" + "".join(words)
        n, off = img.nearest(va)
        if n and n in img.objects and off < max(img.objects[n][1], 1):
            return "%s+%#x" % (n, off)
        # Unnamed data. A relocated pointer slot is named by what it points at; anything else
        # (static variables, unnamed tables) only by its section, since its offset from the
        # nearest symbol moves with the layout.
        r = img.reloc_at.get(va)
        if r and r[0] == "sym":
            return "%s:&%s" % (sec, r[1])
        if r:
            t = r[1]
            return "%s:&%s" % (sec, self.code_name(t) if img.section_of(t) == ".text" else
                               "str:" + repr(img.cstr(t).decode("latin1")) if img.section_of(t) == ".rodata" and printable(img.cstr(t)) else
                               img.section_of(t) or "?")
        return "%s:anon" % sec

    def normalise(self, start, size):
        code = self.unpatch(self.img.read(start, size) or b"", start)
        out = []
        pages = {}
        end = start + size
        last_cmp = None
        insns = list(self.md.disasm_lite(code, start))
        # Fallback pages for bases whose adrp is in another basic block (killed on the linear
        # path, or later in address order): the last adrp to that register seen so far, else the
        # first one in the function. Lines resolved this way carry the raw form too
        # ("raw" SEP "resolved") and compare equal if either part matches (see same()).
        stale = {}
        for _a, _s, _mn, _ops in insns:
            if _mn == "adrp":
                r, i = _ops.split(", ")
                stale.setdefault(r, int(i[1:], 16))
        for addr, sz, mn, ops in insns:
            line = None
            if mn == "adrp":
                reg, imm = ops.split(", ")
                pages[reg] = stale[reg] = int(imm[1:], 16)
                line = "adrp %s" % reg
            elif mn == "adr":
                reg, imm = ops.split(", ")
                line = "adr %s, <%s>" % (reg, self.target(int(imm[1:], 16), start, end))
            elif mn in BRANCH or mn.startswith("b."):
                m = re.search(r"#(0x[0-9a-f]+)$", ops)
                if m:
                    t = int(m.group(1), 16)
                    line = "%s %s<%s>" % (mn, ops[:m.start()], self.target(t, start, end))
            elif mn.startswith("ld") or mn.startswith("st") or mn.startswith("prfm"):
                m = re.search(r"\[(x\d+)(?:, #(0x[0-9a-f]+|\d+))?\]", ops)
                fb = m and m.group(1) not in pages and m.group(1) in stale and "!" not in ops
                if m and (m.group(1) in pages or fb):
                    va = (pages.get(m.group(1)) or stale[m.group(1)]) + int(m.group(2) or "0", 0)
                    w = {"b": 1, "h": 2, "w": 4, "s": 4, "x": 8, "d": 8, "q": 16}.get(ops[0], 16)
                    if mn in ("ldrb", "strb", "ldrsb"):
                        w = 1
                    elif mn in ("ldrh", "strh", "ldrsh"):
                        w = 2
                    elif mn == "ldrsw":
                        w = 4
                    elif mn.endswith("p"):
                        w *= 2
                    line = "%s %s<%s>" % (mn, ops[:m.start()], self.data_name(va, w, load=True))
                    # also keep the raw form when the page came from the linear path: the adrp may
                    # still belong to another block
                    line = mn + " " + ops + (SEP if fb else SEPL) + line
                elif re.fullmatch(r"[wxsdq]\d+, #0x[0-9a-f]+", ops) and mn in ("ldr", "ldrsw"):
                    reg, imm = ops.split(", ")
                    va = int(imm[1:], 16)
                    b = self.img.read(va, 8)
                    line = "%s %s, =%s" % (mn, reg, b.hex() if b else "?")
            elif mn == "cmp":
                m = re.fullmatch(r"[wx]\d+, #(0x[0-9a-f]+|\d+)", ops)
                last_cmp = int(m.group(1), 0) if m else None
            elif mn == "add":
                m = re.fullmatch(r"(x\d+|sp), (x\d+), #(0x[0-9a-f]+|\d+)", ops)
                fb = m and m.group(2) not in pages and m.group(2) in stale
                if m and (m.group(2) in pages or fb):
                    va = (pages.get(m.group(2)) or stale[m.group(2)]) + int(m.group(3), 0)
                    line = "add %s, <%s>" % (m.group(1), self.jump_table(va, start, end, last_cmp) or self.data_name(va))
                    if fb:
                        line = mn + " " + ops + SEP + line
            if line is None:
                line = mn + " " + ops
            # register-kill tracking for adrp pages (linear, approximate)
            if mn != "adrp" and pages and not (mn.startswith("st") or mn.startswith("cm") or mn in BRANCH
                                               or mn.startswith("b.") or mn in ("tst", "prfm", "ret", "br", "blr")):
                regs = [r.strip() for r in ops.split(",")[:2 if mn.startswith("ld") and mn.endswith("p") else 1]]
                for d in regs:
                    if d[:1] == "w":
                        d = "x" + d[1:]
                    pages.pop(d, None)
            out.append(line)
        # __LINE__ arguments (assert / debug allocators taking file + line) move with any source
        # edit: mask `mov w1..w3, #imm` in the 6 instructions before such a call.
        for i, l in enumerate(out):
            if (l.startswith("bl <") or l.startswith("b <")) and ("gDoAssert" in l or l.endswith("PKcj>")):
                for k in range(max(0, i - 6), i):
                    if re.match(r"mov w[123], #", out[k]):
                        out[k] = out[k].split("#")[0] + "#LINE"
        return out

    def unpatch(self, code, start):
        """Undo lld's Cortex-A53 erratum 843419 fix: an instruction after an adrp at page
        offset 0xff8/0xffc may be replaced by `b veneer`, where the veneer holds the original
        instruction followed by `b back`. Put the original instruction back."""
        end = start + len(code)
        buf = None
        for off in range(0, len(code) - 3, 4):
            w = struct.unpack_from("<I", code, off)[0]
            if w & 0xFC000000 != 0x14000000:
                continue
            pc = start + off
            imm = w & 0x3FFFFFF
            if imm & (1 << 25):
                imm -= 1 << 26
            t = pc + imm * 4
            if start <= t < end:
                continue
            v = self.img.read(t, 8)
            if not v:
                continue
            w1 = struct.unpack_from("<I", v, 4)[0]
            if w1 & 0xFC000000 != 0x14000000:
                continue
            imm1 = w1 & 0x3FFFFFF
            if imm1 & (1 << 25):
                imm1 -= 1 << 26
            if t + 4 + imm1 * 4 != pc + 4:
                continue
            if buf is None:
                buf = bytearray(code)
            buf[off:off + 4] = v[:4]
        return bytes(buf) if buf is not None else code

    def jump_table(self, va, start, end, last_cmp=None):
        """A .rodata table of int32 offsets relative to its own base whose targets land inside
        the function (clang's switch tables): name it by the target offsets in the function."""
        if self.img.section_of(va) != ".rodata":
            return None
        offs = []
        for i in range(last_cmp + 1 if last_cmp is not None and last_cmp < 4096 else 4096):
            b = self.img.read(va + 4 * i, 4)
            if not b:
                break
            t = va + struct.unpack("<i", b)[0]
            if not (start <= t < end):
                break
            offs.append(t - start)
        if len(offs) < 2:
            return None
        return "jt[" + ",".join("%x" % o for o in offs) + "]"

    def target(self, t, start, end):
        if start <= t < end:
            return "L%#x" % (t - start)
        return self.code_name(t)


# ---------------------------------------------------------------------------------------------
# multiprocessing workers (images are loaded once per worker)
_W = {}


def _winit(old, new, anon_old, anon_new):
    _W["old"] = Normaliser(Image(old), anon_old)
    _W["new"] = Normaliser(Image(new), anon_new)


def _wcmp(job):
    name, (ao, so), (an, sn) = job
    a = _W["old"].normalise(ao, so)
    b = _W["new"].normalise(an, sn)
    if same(a, b):
        return name, None
    a, b = canonical(a, b)
    if a == b:
        return name, None
    return name, (a, b)


LBL = re.compile(r"<L0x([0-9a-f]+)>")
JT = re.compile(r"<jt\[([0-9a-f,]+)\]>")


def strip_labels(l):
    return JT.sub("<jt>", LBL.sub("<L>", l))


def canonical(a, b):
    """Make two normalised streams comparable:
    - fallback-resolved lines -> their raw form (linear-resolved ones -> resolved form), except
      where only the other form matches the aligned line on the other side;
    - branch labels inside the function: the streams are aligned with labels stripped, and each
      new-build label is renamed to the old-build offset of the aligned instruction, so code
      inserted elsewhere doesn't make every later branch differ. A label whose target has no
      aligned counterpart is shown as L'<offset>."""
    ka, kb = [key(l) for l in a], [key(l) for l in b]
    sa, sb = [strip_labels(l) for l in ka], [strip_labels(l) for l in kb]
    sm = difflib.SequenceMatcher(None, sa, sb, autojunk=False)
    inv = {}
    for t, i1, i2, j1, j2 in sm.get_opcodes():
        if t == "equal":
            for i, j in zip(range(i1, i2), range(j1, j2)):
                inv[j] = i
        elif t == "replace" and i2 - i1 == j2 - j1:
            for i, j in zip(range(i1, i2), range(j1, j2)):
                if same_line(a[i], b[j]):
                    kb[j] = ka[i]
                    inv[j] = i
    def relabel(off_hex):
        j = int(off_hex, 16) // 4
        return ("%#x" % (inv[j] * 4)) if j in inv else ("'%#x" % (j * 4))
    kb = [JT.sub(lambda m: "<jt[" + ",".join(relabel(x) for x in m.group(1).split(",")) + "]>",
                 LBL.sub(lambda m: "<L" + relabel(m.group(1)) + ">", l)) for l in kb]
    ka = [JT.sub(lambda m: "<jt[" + ",".join("%#x" % int(x, 16) for x in m.group(1).split(",")) + "]>", l) for l in ka]
    return ka, kb


def anon_names(img):
    named = sorted({a for a, _ in img.funcs.values()})
    out, count = dict(img.lambda_names), defaultdict(int)
    for a in img.starts:
        if a in img.by_addr or a in out:
            continue
        i = bisect.bisect_right(named, a) - 1
        prev = img.by_addr[named[i]] if i >= 0 else "start"
        count[prev] += 1
        out[a] = "anon:%s#%d" % (prev, count[prev])
    return out


def demangle(names):
    if not names:
        return []
    r = subprocess.run(["c++filt"], input="\n".join(names), capture_output=True, text=True).stdout
    return r.split("\n")[:len(names)]


RUNTIME = re.compile(r"^(anon:start|__|std::|_Unwind|non-virtual thunk to std::)")


def class_of(dem):
    """Class/feature bucket from a demangled name: the qualified scope before the last ::."""
    if dem.startswith("anon:"):
        return "(unnamed static functions)"
    if RUNTIME.match(dem) or dem.startswith("lambda:"):
        return "(runtime / toolchain)"
    if "::[lambda #" in dem:
        return class_of(dem.split("::[lambda #")[0] + "()")
    s = re.sub(r"^non-virtual thunk to ", "", dem)
    s = re.sub(r"\(.*$", "", s)          # drop params
    s = re.sub(r"^[^:<(]* (?=[A-Za-z_][\w:]*::)", "", s)  # drop a template's return type
    s = re.sub(r"<[^<>]*>", "", s)
    s = re.sub(r"<[^<>]*>", "", s)
    parts = s.split("::")
    if len(parts) >= 2:
        return "::".join(parts[:-1])
    return "(free functions)"


def characterise(a, b, name, size_a, size_b):
    """One-line human description of how new (b) differs from old (a)."""
    def calls(ls):
        c = defaultdict(int)
        for l in ls:
            m = re.match(r"(bl|b) (<[^>]*>)", l)
            if m and not m.group(2).startswith("<L"):
                c[m.group(2)[1:-1]] += 1
        return c

    def strs(ls):
        return {m for l in ls for m in re.findall(r"str:('(?:[^'\\]|\\.)*'|\"(?:[^\"\\]|\\.)*\")", l)}

    notes = []
    if size_b <= 8 and size_a > 8:
        rt = [l for l in b if not l.startswith("ret")]
        notes.append("3.8.0 stubbed out (%s)" % ("; ".join(rt) or "ret") )
    ca, cb = calls(a), calls(b)
    rem = [k for k in ca if k not in cb]
    add = [k for k in cb if k not in ca]
    dm = demangle([k.split("+")[0].removeprefix("PLT:") for k in rem + add])
    short = [re.sub(r"\(.*", "", d) for d in dm]
    if rem:
        notes.append("calls removed: " + ", ".join(short[:len(rem)][:8]) + (" ..." if len(rem) > 8 else ""))
    if add:
        notes.append("calls added: " + ", ".join(short[len(rem):][:8]) + (" ..." if len(add) > 8 else ""))
    sa, sb = strs(a), strs(b)
    if sa - sb:
        notes.append("strings removed: " + ", ".join(sorted(sa - sb))[:200])
    if sb - sa:
        notes.append("strings added: " + ", ".join(sorted(sb - sa))[:200])
    if not notes:
        # same calls: look at the kind of instruction differences
        sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
        ch = [(t, a[i1:i2], b[j1:j2]) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != "equal"]
        n = sum(max(len(x), len(y)) for _, x, y in ch)
        imm = [(x, y) for t, x, y in ch if t == "replace" and len(x) == len(y)]
        offs = lambda l: re.sub(r"#-?(0x[0-9a-f]+|\d+)", "#N", l)
        if ch and len(imm) == len(ch) and all(offs(p) == offs(q) for x, y in imm for p, q in zip(x, y)) \
                and any("[" in p for x, _ in imm for p in x):
            notes.append("only field offsets / immediates differ (object layout changed)")
        elif len(ch) == 1 and imm and len(imm[0][0]) <= 2:
            notes.append("constant/operand change: %s -> %s" % (" ; ".join(imm[0][0]), " ; ".join(imm[0][1])))
        else:
            notes.append("control/data flow changed (%d differing instrs)" % n)
    if size_b < size_a * 0.6 and size_b > 8:
        notes.insert(0, "3.8.0 cut down %d -> %d bytes" % (size_a, size_b))
    elif size_b > size_a * 1.4:
        notes.insert(0, "3.8.0 grew %d -> %d bytes" % (size_a, size_b))
    return "; ".join(notes)


# ---------------------------------------------------------------------------------------------
# Layout check
NEW_FUNCS = ("_Znwm", "_Znam", "_ZnwmRKSt9nothrow_t", "_ZnamRKSt9nothrow_t")


def mangled_scope(cls):
    parts = cls.split("::")
    if any(not re.fullmatch(r"[A-Za-z_]\w*", p) for p in parts):
        return None
    return "".join("%d%s" % (len(p), p) for p in parts)


def alloc_sizes(img, norm, ctor_addrs):
    """Sizes passed to operator new right before a call to one of ctor_addrs."""
    t0, t1 = img.secs[".text"]
    code = img.read(t0, t1 - t0)
    words = struct.unpack("<%dI" % (len(code) // 4), code[: len(code) // 4 * 4])
    new_addrs = {a for a, n in img.plt.items() if n in NEW_FUNCS} | {img.funcs[n][0] for n in NEW_FUNCS if n in img.funcs}
    sizes = defaultdict(set)
    for i, w in enumerate(words):
        if w & 0xFC000000 != 0x94000000:
            continue
        off = w & 0x3FFFFFF
        if off & (1 << 25):
            off -= 1 << 26
        tgt = t0 + i * 4 + off * 4
        if tgt not in ctor_addrs:
            continue
        pc = t0 + i * 4
        lo = max(t0, pc - 96)
        ins = list(norm.md.disasm_lite(img.read(lo, pc - lo), lo))
        nb = None
        for k in range(len(ins) - 1, -1, -1):
            a, _, mn, ops = ins[k]
            if mn == "bl" and int(ops[1:], 16) in new_addrs:
                nb = k
                break
        if nb is None:
            continue
        for k in range(nb - 1, max(-1, nb - 12), -1):
            a, _, mn, ops = ins[k]
            m = re.fullmatch(r"(?:mov|movz|orr) [wx]0, (?:[wx]zr, )?#(0x[0-9a-f]+|\d+)", mn + " " + ops) if mn in ("mov", "movz", "orr") else None
            if m:
                sizes[ctor_addrs[tgt]].add(int(m.group(1), 0))
                break
    return sizes


def layout_check(O, N, no, nn, classes):
    """Per class: allocation sizes in both builds and the field-offset remapping seen in
    same-named methods (aligned memory operands that differ only in their offset)."""
    out = {}
    fo = defaultdict(list)
    for n in O.funcs:
        if n in N.funcs and n.startswith("_ZN"):
            fo[n] = True
    ctors_o, ctors_n = {}, {}
    scopes = {c: mangled_scope(c) for c in classes}
    for c, sc in scopes.items():
        if not sc:
            continue
        for img, d in ((O, ctors_o), (N, ctors_n)):
            for suf in ("C1E", "C2E"):
                for n, (a, _) in img.funcs.items():
                    if n.startswith("_ZN" + sc + suf):
                        d[a] = c
                for a, n in img.plt.items():
                    if n.startswith("_ZN" + sc + suf):
                        d[a] = c
    so = alloc_sizes(O, no, ctors_o)
    sn = alloc_sizes(N, nn, ctors_n)
    for c, sc in scopes.items():
        if not sc:
            continue
        pre = ("_ZN" + sc, "_ZNK" + sc)
        names = [n for n in fo if n.startswith(pre) and re.match(r"\d", n[len("_ZNK" if n.startswith("_ZNK") else "_ZN") + len(sc):] or "x")]
        shifts = defaultdict(int)
        nshift = 0
        for n in names:
            a = no.normalise(*O.funcs[n])
            b = nn.normalise(*N.funcs[n])
            if same(a, b):
                continue
            a, b = canonical(a, b)
            sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
            hit = False
            for t, i1, i2, j1, j2 in sm.get_opcodes():
                if t != "replace" or i2 - i1 != j2 - j1:
                    continue
                for x, y in zip(a[i1:i2], b[j1:j2]):
                    mx = re.fullmatch(r"(\w+ [^\[]*)\[(x\d+), #(0x[0-9a-f]+|\d+)\](.*)", x)
                    my = re.fullmatch(r"(\w+ [^\[]*)\[(x\d+), #(0x[0-9a-f]+|\d+)\](.*)", y)
                    if mx and my and mx.group(1) == my.group(1) and mx.group(2) == my.group(2) and mx.group(4) == my.group(4) \
                            and mx.group(2) not in ("x29",) and x.find("sp") < 0:
                        shifts[(int(mx.group(3), 0), int(my.group(3), 0))] += 1
                        hit = True
                    mx = re.fullmatch(r"add (x\d+), (x\d+), #(0x[0-9a-f]+|\d+)", x)
                    my = re.fullmatch(r"add (x\d+), (x\d+), #(0x[0-9a-f]+|\d+)", y)
                    if mx and my and mx.group(1, 2) == my.group(1, 2) and mx.group(2) != "sp":
                        shifts[(int(mx.group(3), 0), int(my.group(3), 0))] += 1
                        hit = True
            nshift += hit
        out[c] = dict(size_old=sorted(v for k, v in so.items() if k == c for v in v),
                      size_new=sorted(v for k, v in sn.items() if k == c for v in v),
                      methods=len(names), methods_shifted=nshift,
                      shifts=sorted(shifts.items(), key=lambda kv: kv[0]))
    return out


def rodata_strings(img, minlen=4):
    a, b = img.secs[".rodata"]
    data = img.read(a, b - a)
    out = set()
    for m in re.finditer(rb"[\x20-\x7e\t\n\r]{%d,}\x00" % minlen, data):
        out.add(m.group(0)[:-1].decode("latin1"))
    # UTF-8 (Japanese) strings too
    for m in re.finditer(rb"(?:[\x20-\x7e]|[\xc2-\xf4][\x80-\xbf]{1,3}){%d,}\x00" % minlen, data):
        try:
            out.add(m.group(0)[:-1].decode("utf-8"))
        except UnicodeDecodeError:
            pass
    return out


def vtables(img, norm):
    """name -> list of slot target names."""
    out = {}
    for n, (a, sz) in img.objects.items():
        if not n.startswith("_ZTV") or not sz:
            continue
        slots = []
        for off in range(16, sz, 8):  # skip offset-to-top and RTTI
            r = img.reloc_at.get(a + off)
            if r is None:
                v = struct.unpack("<Q", img.read(a + off, 8))[0]
                slots.append("0" if v == 0 else "#%x" % v)
            elif r[0] == "sym":
                slots.append(r[1] + ("+%d" % r[2] if r[2] else ""))
            else:
                slots.append(norm.data_name(r[1]) if img.section_of(r[1]) != ".text" else norm.code_name(r[1]))
        out[n] = slots
    return out


def init_array(img, norm):
    a, b = img.secs[".init_array"]
    out = []
    for va in range(a, b, 8):
        r = img.reloc_at.get(va)
        t = r[1] if r and r[0] == "rel" else None
        out.append(t)
    return out


def jni_tables(img, norm):
    """JNINativeMethod {name, sig, fn} triples found in relocated data -> (name, sig, target name)."""
    out = []
    ra = img.reloc_at
    for va in sorted(ra):
        r0, r1, r2 = ra.get(va), ra.get(va + 8), ra.get(va + 16)
        if not (r0 and r1 and r2 and r0[0] == r1[0] == "rel"):
            continue
        if img.section_of(r0[1]) != ".rodata" or img.section_of(r1[1]) != ".rodata":
            continue
        if r2[0] == "sym":
            tgt = r2[1]
        elif img.section_of(r2[1]) == ".text":
            tgt = norm.code_name(r2[1])
        else:
            continue
        sig = img.cstr(r1[1])
        nm = img.cstr(r0[1])
        if sig and sig.startswith(b"(") and b")" in sig and nm and printable(nm):
            out.append((nm.decode(), sig.decode(), tgt))
    return out


def fn_extent(img, norm, a):
    """Size of a function with no symbol size / FDE: up to the first ret or outward tail b."""
    code = img.read(a, 4096) or b""
    for ad, sz, mn, ops in norm.md.disasm_lite(code, a):
        if mn == "ret":
            return ad + 4 - a
        if mn == "b" and ops.startswith("#"):
            t = int(ops[1:], 16)
            if t < a or t > ad + 4096:
                return ad + 4 - a
    return 64


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--old", default=OLD)
    ap.add_argument("--new", default=NEW)
    ap.add_argument("--out", default=os.path.join(REPO, "work/verdiff"))
    ap.add_argument("-j", type=int, default=8)
    args = ap.parse_args()
    os.makedirs(os.path.join(args.out, "fn"), exist_ok=True)

    print("loading images", file=sys.stderr)
    O, N = Image(args.old), Image(args.new)

    # 1. name unnamed functions by position: "anon:<preceding named function>#k". The link
    #    order is the same in both builds, so this pairs them; they are then diffed like the rest.
    anon = {"old": anon_names(O), "new": anon_names(N)}
    for img, which in ((O, "old"), (N, "new")):
        for a, n in anon[which].items():
            img.funcs[n] = (a, img.extent(a))
    print("unnamed functions: %d / %d" % (len(anon["old"]), len(anon["new"])), file=sys.stderr)

    # 2. compare functions present in both (dedupe aliases by address pair)
    common = sorted(set(O.funcs) & set(N.funcs))
    seen, cjobs = {}, []
    for n in common:
        k = (O.funcs[n][0], N.funcs[n][0])
        if k in seen:
            continue
        seen[k] = n
        if O.funcs[n][1] == 0 and N.funcs[n][1] == 0:
            continue
        cjobs.append((n, O.funcs[n], N.funcs[n]))
    print("comparing %d functions" % len(cjobs), file=sys.stderr)
    changed = {}
    with Pool(args.j, _winit, (args.old, args.new, anon["old"], anon["new"])) as p:
        for i, (n, r) in enumerate(p.imap_unordered(_wcmp, cjobs, chunksize=64)):
            if r:
                changed[n] = r
    aliases = defaultdict(list)
    for n in common:
        k = (O.funcs[n][0], N.funcs[n][0])
        if seen[k] != n:
            aliases[seen[k]].append(n)

    only_old = sorted(set(O.funcs) - set(N.funcs))
    only_new = sorted(set(N.funcs) - set(O.funcs))

    isanon = lambda n: n.startswith(("anon:", "lambda:"))
    anon_only_old = [n for n in only_old if isanon(n)]
    anon_only_new = [n for n in only_new if isanon(n)]
    only_old = [n for n in only_old if not isanon(n)]
    only_new = [n for n in only_new if not isanon(n)]

    # 4. strings, vtables, init_array, JNI
    no, nn = Normaliser(O, anon["old"]), Normaliser(N, anon["new"])
    so, sn = rodata_strings(O), rodata_strings(N)
    s_rem, s_add = sorted(so - sn), sorted(sn - so)
    vo, vn = vtables(O, no), vtables(N, nn)
    vt_changed = {}
    for k in sorted(set(vo) & set(vn)):
        if vo[k] != vn[k]:
            diffs = [(i, x, y) for i, (x, y) in enumerate(zip(vo[k], vn[k])) if x != y]
            if len(vo[k]) != len(vn[k]):
                diffs.append(("len", len(vo[k]), len(vn[k])))
            vt_changed[k] = diffs
    vt_only_old = sorted(set(vo) - set(vn))
    vt_only_new = sorted(set(vn) - set(vo))

    def init_names(img, norm, lst):
        res = []
        for t in lst:
            if t is None:
                res.append(("?", [], []))
                continue
            sz = img.eh.get(t) or fn_extent(img, norm, t)
            body = norm.normalise(t, sz)
            refs = []
            for l in body:
                for m in re.findall(r"<((?:GOT:|str:)[^>]*|[A-Za-z_][^>+]*)>", (split2(l) or [l])[-1]):
                    if not m.startswith("L0x") and m not in refs:
                        refs.append(m)
            res.append(("init@%#x" % t, body, refs))
        return res
    io, inn = init_names(O, no, init_array(O, no)), init_names(N, nn, init_array(N, nn))

    jo, jn = jni_tables(O, no), jni_tables(N, nn)
    jo_n = {(a, b): c for a, b, c in jo}
    jn_n = {(a, b): c for a, b, c in jn}

    # ---- signature changes: same qualified name, different parameters ------------------------
    def base(d):
        return re.sub(r"\(.*", "", d)
    do_, dn_ = dict(zip(only_old, demangle(only_old))), dict(zip(only_new, demangle(only_new)))
    bo, bn = defaultdict(list), defaultdict(list)
    for n, d in do_.items():
        bo[base(d)].append(n)
    for n, d in dn_.items():
        bn[base(d)].append(n)
    sig_rows = []
    for b_ in sorted(set(bo) & set(bn)):
        if len(bo[b_]) != 1 or len(bn[b_]) != 1 or b_.startswith(("std::", "void std::")):
            continue
        on, nn_ = bo[b_][0], bn[b_][0]
        a = no.normalise(*O.funcs[on])
        b2 = nn.normalise(*N.funcs[nn_])
        a, b2 = canonical(a, b2)
        sm = difflib.SequenceMatcher(None, a, b2, autojunk=False)
        nd = sum(max(i2 - i1, j2 - j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != "equal")
        sig_rows.append((do_[on], dn_[nn_], O.funcs[on][1], N.funcs[nn_][1], nd,
                         characterise(a, b2, on, O.funcs[on][1], N.funcs[nn_][1]) if nd else "same body"))
        safe = re.sub(r"[^A-Za-z0-9_]", "_", on)[:150]
        with open(os.path.join(args.out, "fn", "sig_" + safe + ".diff"), "w") as f:
            f.write("# %s\n# -> %s\n" % (do_[on], dn_[nn_]))
            f.writelines(l + "\n" for l in difflib.unified_diff(a, b2, "3.7.0", "3.8.0", n=3, lineterm=""))

    # ---- layout check ----------------------------------------------------------------------
    names0 = sorted(changed)
    classes = sorted({class_of(d) for d in demangle(names0)} - {"(runtime / toolchain)", "(free functions)"})
    print("layout check over %d classes" % len(classes), file=sys.stderr)
    lay = layout_check(O, N, no, nn, classes)
    with open(os.path.join(args.out, "layout.tsv"), "w") as f:
        f.write("class\tnew_size_3.7.0\tnew_size_3.8.0\tmethods_in_both\tmethods_with_offset_changes\toffset_map_old>new(count)\n")
        for c, r in sorted(lay.items()):
            f.write("%s\t%s\t%s\t%d\t%d\t%s\n" % (c, ",".join("%#x" % v for v in r["size_old"]), ",".join("%#x" % v for v in r["size_new"]),
                                                  r["methods"], r["methods_shifted"],
                                                  " ".join("%#x>%#x(%d)" % (a, b, k) for (a, b), k in r["shifts"])))

    # ---- write outputs -------------------------------------------------------------------
    names = sorted(changed)
    dem = dict(zip(names, demangle(names)))
    LAMBDA_SLOTS = {0: "~D1", 1: "~D0", 2: "clone", 3: "clone(p)", 4: "destroy", 5: "destroy_dealloc",
                    6: "operator()", 7: "target", 8: "target_type"}
    lam = [n for n in names if n.startswith("lambda:")]
    encl = {}
    for n in lam:
        m = re.fullmatch(r"lambda:(.*)#(\d+)\.(\d+)", n)
        if m:
            encl[n] = (m.group(1), int(m.group(2)), int(m.group(3)))
    ed = dict(zip(sorted({e[0] for e in encl.values()}),
                  demangle(["_Z" + e for e in sorted({e[0] for e in encl.values()})])))
    def nested_name(e):
        # fallback when the enclosing name has substitutions (S_, NS2_) relative to the typeinfo
        # name and can't be demangled on its own: read the <len><id> components after N
        parts, i = [], 1 if e.startswith("N") else 0
        while i < len(e) and e[i].isdigit():
            m = re.match(r"\d+", e[i:])
            ln = int(m.group(0))
            i += len(m.group(0))
            parts.append(e[i:i + ln])
            i += ln
        return "::".join(parts) + "()" if parts else e
    for n, (e, k, sl) in encl.items():
        d = ed[e] if not ed[e].startswith("_Z") else nested_name(e)
        dem[n] = "%s::[lambda #%d].%s" % (re.sub(r"\(.*", "", d), k, LAMBDA_SLOTS.get(sl, sl))
    rows = []
    for n in names:
        a, b = changed[n]
        so_, sn_ = O.funcs[n][1], N.funcs[n][1]
        ch = characterise(a, b, n, so_, sn_)
        sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
        ndiff = sum(max(i2 - i1, j2 - j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != "equal")
        rows.append(dict(name=n, dem=dem[n], cls=class_of(dem[n]), old_addr=O.funcs[n][0],
                         new_addr=N.funcs[n][0], old_size=so_, new_size=sn_, ndiff=ndiff, what=ch,
                         aliases=",".join(aliases.get(n, []))))
        safe = re.sub(r"[^A-Za-z0-9_]", "_", n)[:150]
        with open(os.path.join(args.out, "fn", safe + ".diff"), "w") as f:
            f.write("# %s\n# 3.7.0 @%#x size %d   3.8.0 @%#x size %d\n" % (dem[n], O.funcs[n][0], so_, N.funcs[n][0], sn_))
            f.writelines(l + "\n" for l in difflib.unified_diff(a, b, "3.7.0", "3.8.0", n=3, lineterm=""))

    with open(os.path.join(args.out, "changed.tsv"), "w") as f:
        f.write("symbol\tdemangled\tclass\told_addr\tnew_addr\told_size\tnew_size\tdiff_instrs\tsame_size\tcharacterisation\taliases\n")
        for r in sorted(rows, key=lambda r: (r["cls"], r["dem"])):
            f.write("%s\t%s\t%s\t%#x\t%#x\t%d\t%d\t%d\t%d\t%s\t%s\n" % (
                r["name"], r["dem"], r["cls"], r["old_addr"], r["new_addr"], r["old_size"], r["new_size"],
                r["ndiff"], r["old_size"] == r["new_size"], r["what"], r["aliases"]))
    with open(os.path.join(args.out, "only.tsv"), "w") as f:
        f.write("build\tsymbol\tdemangled\taddr\tsize\n")
        for tag, lst, img in (("3.7.0", only_old, O), ("3.8.0", only_new, N)):
            for n, d in zip(lst, demangle(lst)):
                f.write("%s\t%s\t%s\t%#x\t%d\n" % (tag, n, d, img.funcs[n][0], img.funcs[n][1]))
    with open(os.path.join(args.out, "strings.tsv"), "w") as f:
        f.write("change\tstring\n")
        for s in s_rem:
            f.write("removed\t%r\n" % s)
        for s in s_add:
            f.write("added\t%r\n" % s)
    with open(os.path.join(args.out, "vtables.tsv"), "w") as f:
        f.write("vtable\tslot\t3.7.0\t3.8.0\n")
        for k, ds in vt_changed.items():
            for i, x, y in ds:
                f.write("%s\t%s\t%s\t%s\n" % (k, i, x, y))
        for k in vt_only_old:
            f.write("%s\tonly-in-3.7.0\t\t\n" % k)
        for k in vt_only_new:
            f.write("%s\tonly-in-3.8.0\t\t\n" % k)

    # report.md
    by_cls = defaultdict(list)
    for r in rows:
        by_cls[r["cls"]].append(r)
    size_same = [r for r in rows if r["old_size"] == r["new_size"]]
    L = []
    w = L.append
    w("# libSOA 3.7.0 (online) vs 3.8.0 (offline): behaviour diff\n")
    w("Generated by `tools/verdiff.py`. Old: `%s`, new: `%s`.\n" % (os.path.relpath(args.old, REPO), os.path.relpath(args.new, REPO)))
    w("Functions are compared as normalised instruction streams (relocations, PC-relative addresses and "
      "branch targets replaced by symbols / strings / constant contents), so every function listed below "
      "really behaves differently. Per-function normalised diffs: `work/verdiff/fn/<symbol>.diff`.\n")
    w("## Summary\n")
    w("- Functions in both builds (distinct bodies compared): %d" % len(cjobs))
    w("- **Changed: %d** (%d of them the same size, which a size diff misses)" % (len(rows), len(size_same)))
    w("- Only in 3.7.0: %d functions; only in 3.8.0: %d (list: `only.tsv`)" % (len(only_old), len(only_new)))
    w("- Unnamed (static) functions (from .eh_frame, named `anon:<preceding symbol>#k` and diffed too): "
      "%d in 3.7.0, %d in 3.8.0; unpaired: %d / %d" % (len(anon["old"]), len(anon["new"]), len(anon_only_old), len(anon_only_new)))
    w("- .rodata strings: %d removed, %d added (`strings.tsv`)" % (len(s_rem), len(s_add)))
    w("- Vtables: %d changed, %d only in 3.7.0, %d only in 3.8.0 (`vtables.tsv`)" % (len(vt_changed), len(vt_only_old), len(vt_only_new)))
    w("- .init_array: %d entries in 3.7.0, %d in 3.8.0" % (len(io), len(inn)))
    w("- JNI RegisterNatives methods: %d in 3.7.0, %d in 3.8.0\n" % (len(jo), len(jn)))

    w("## Changed functions by class\n")
    w("`Δ` = number of differing normalised instructions. Sizes in bytes (3.7.0 → 3.8.0). "
      "Lambda rows cover the std::function bodies created inside a method; lambdas are paired by rank "
      "within their enclosing method, so after a removed lambda the later ones may be mispaired. "
      "Per-slot detail is in `changed.tsv` (`Class::Method::[lambda #k].operator()` etc.).\n")
    for cls in sorted(by_cls, key=lambda c: (c.startswith("("), -sum(r["ndiff"] for r in by_cls[c]), c)):
        rs = sorted(by_cls[cls], key=lambda r: -r["ndiff"])
        w("### %s (%d)\n" % (cls, len(rs)))
        w("| Function | Size | Δ | What changed |")
        w("|---|---|---|---|")
        lam_rows = defaultdict(list)
        for r in rs:
            if "::[lambda #" in r["dem"]:
                lam_rows[r["dem"].split("::[lambda #")[0]].append(r)
                continue
            fn = r["dem"][len(cls) + 2:] if r["dem"].startswith(cls + "::") else r["dem"]
            fn = re.sub(r"std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >", "string", fn)
            w("| `%s` | %d → %d | %d | %s |" % (fn.replace("|", "\\|")[:120], r["old_size"], r["new_size"], r["ndiff"],
                                              r["what"].replace("|", "\\|")))
        for e, lr in sorted(lam_rows.items()):
            ks = sorted({int(re.search(r"\[lambda #(\d+)\]", r["dem"]).group(1)) for r in lr})
            ops = [r for r in lr if r["dem"].endswith("operator()")]
            w("| `%s` lambdas (std::function bodies) | | %d | %d lambda(s) differ (#%s; %d operator() bodies) |" % (
                  e[len(cls) + 2:] if e.startswith(cls + "::") else e, sum(r["ndiff"] for r in lr), len(ks),
                  ",".join(map(str, ks)), len(ops)))
        w("")

    w("## Layout check\n")
    w("For each class with a changed function: the size passed to `operator new` before a call to its "
      "constructor (both builds), and the field-offset remapping seen in same-named methods (aligned "
      "memory operands / `add xD, xN, #imm` that differ only in the offset; base registers are not proven "
      "to be `this`, so treat a map as evidence, not proof). Full data: `layout.tsv`.\n")
    w("| Class | new size 3.7.0 | new size 3.8.0 | Methods (both) | with offset changes | Offset map old→new (count) |")
    w("|---|---|---|---|---|---|")
    for c, r in sorted(lay.items(), key=lambda kv: (-kv[1]["methods_shifted"], kv[0])):
        so_ = ",".join("%#x" % v for v in r["size_old"]) or "-"
        sn_ = ",".join("%#x" % v for v in r["size_new"]) or "-"
        mark = "**" if (so_ != sn_ or r["methods_shifted"]) else ""
        sh = " ".join("%#x→%#x(%d)" % (a, b, k) for (a, b), k in r["shifts"][:24]) + (" …" if len(r["shifts"]) > 24 else "")
        w("| %s%s%s | %s | %s | %d | %d | %s |" % (mark, c, mark, so_, sn_, r["methods"], r["methods_shifted"], sh))
    w("")

    w("## Signature changes\n")
    w("Functions whose qualified name exists once in each build with different parameters (callers were "
      "changed with them). Diffs: `fn/sig_<3.7.0 symbol>.diff`.\n")
    w("| 3.7.0 | 3.8.0 | Size | Δ | What changed |")
    w("|---|---|---|---|---|")
    for d_o, d_n, so_, sn_, nd, ch in sig_rows:
        w("| `%s` | `%s` | %d → %d | %d | %s |" % (d_o[:140].replace("|", "\\|"), d_n[:140].replace("|", "\\|"), so_, sn_, nd, ch.replace("|", "\\|")))
    w("")

    w("## Functions only in one build\n")
    for tag, lst in (("3.7.0", only_old), ("3.8.0", only_new)):
        cl = defaultdict(int)
        for d in demangle(lst):
            cl[class_of(d)] += 1
        w("**Only in %s** (%d): " % (tag, len(lst)) + ", ".join("%s (%d)" % (k, v) for k, v in sorted(cl.items(), key=lambda x: -x[1])) + "\n")

    w("**std::function lambdas without a counterpart** (grouped by enclosing method; a lambda only in "
      "3.7.0 is typically a removed UI/network callback):\n")
    for tag, lst in (("3.7.0", anon_only_old), ("3.8.0", anon_only_new)):
        grp = defaultdict(set)
        for n in lst:
            m = re.fullmatch(r"lambda:(N.*)#(\d+)\.\d+", n)
            if m:
                grp[m.group(1)].add(int(m.group(2)))
        if not grp:
            continue
        keys = sorted(grp, key=lambda k: -len(grp[k]))
        dm = dict(zip(keys, demangle(["_Z" + k for k in keys])))
        w("- only in %s: " % tag + ", ".join("`%s` (%d)" % (re.sub(r"\(.*", "", dm[k] if not dm[k].startswith("_Z") else nested_name(k)), len(grp[k])) for k in keys))
    w("")

    w("## Vtables\n")
    if vt_changed:
        w("| Vtable | Slot | 3.7.0 | 3.8.0 |")
        w("|---|---|---|---|")
        for k, ds in vt_changed.items():
            for i, x, y in ds:
                w("| `%s` | %s | `%s` | `%s` |" % (demangle([k])[0], i, x, y))
    else:
        w("No vtable of a class present in both builds changed any slot target.")
    if vt_only_old:
        w("\nOnly in 3.7.0: " + ", ".join("`%s`" % d for d in demangle(vt_only_old)))
    if vt_only_new:
        w("\nOnly in 3.8.0: " + ", ".join("`%s`" % d for d in demangle(vt_only_new)))
    w("")

    w("## .init_array\n")
    shape = lambda body: tuple(l.split(" ", 1)[0] for l in body)
    sm = difflib.SequenceMatcher(None, [shape(x[1]) for x in io], [shape(x[1]) for x in inn], autojunk=False)
    init_rows = []
    for t, i1, i2, j1, j2 in sm.get_opcodes():
        if t == "equal":
            for i, j in zip(range(i1, i2), range(j1, j2)):
                x, y = canonical(io[i][1], inn[j][1])
                if x != y:
                    init_rows.append((i, io[i], inn[j]))
            continue
        for k in range(max(i2 - i1, j2 - j1)):
            init_rows.append((i1 + k, io[i1 + k] if i1 + k < i2 else None, inn[j1 + k] if j1 + k < j2 else None))
    w("%d entries in 3.7.0, %d in 3.8.0; the static initialisers are aligned by instruction shape and "
      "compared normalised. Differences:\n" % (len(io), len(inn)))
    if not init_rows:
        w("None.\n")
    else:
        w("| # | 3.7.0 | 3.8.0 | references |")
        w("|---|---|---|---|")
        desc = lambda e: "%s (%d instrs)" % (e[0], len(e[1])) if e else "—"
        for i, a_, b_ in init_rows:
            refs = (b_ or a_)[2][:6]
            w("| %s | %s | %s | %s |" % (i, desc(a_), desc(b_), ", ".join("`%s`" % r[:60] for r in refs).replace("|", "\\|")))
        w("")

    w("## JNI entry points\n")
    w("JNI_OnLoad: %s\n" % ("changed" if "JNI_OnLoad" in changed else "unchanged"))
    ko, kn = set(jo_n), set(jn_n)
    w("RegisterNatives tables: %d methods in 3.7.0, %d in 3.8.0.\n" % (len(ko), len(kn)))
    for k in sorted(ko - kn):
        w("- only 3.7.0: `%s%s` → `%s`" % (k[0], k[1], jo_n[k]))
    for k in sorted(kn - ko):
        w("- only 3.8.0: `%s%s` → `%s`" % (k[0], k[1], jn_n[k]))
    for k in sorted(ko & kn):
        tgt = jo_n[k]
        st = "**body changed**" if tgt in changed else ("target differs: `%s`" % jn_n[k] if tgt != jn_n[k] else "unchanged")
        w("- `%s%s` → `%s`: %s" % (k[0], k[1], tgt, st))
    w("")

    w("## .rodata strings\n")
    w("Removed in 3.8.0 (%d), first 300:\n" % len(s_rem))
    w("```")
    for s in s_rem[:300]:
        w(repr(s)[:160])
    w("```\n")
    w("Added in 3.8.0 (%d), first 300:\n" % len(s_add))
    w("```")
    for s in s_add[:300]:
        w(repr(s)[:160])
    w("```\n")
    with open(os.path.join(args.out, "report.md"), "w") as f:
        f.write("\n".join(L) + "\n")
    print("changed %d (same-size %d); report in %s" % (len(rows), len(size_same), args.out), file=sys.stderr)


if __name__ == "__main__":
    main()
