#!/usr/bin/env python3
"""The natives' guest addresses: one generated, stamped table per subsystem, from the lib.

    tools/gen_addresses.py [--lib LIB] [SUBSYS...]     write port/src/native/<s>/gen/<s>_addresses.h
    tools/gen_addresses.py --check [SUBSYS...]         exit 1 if a header differs (T0 `generated`,
                                                       tools/check_generated.py)
    tools/gen_addresses.py --refs 0xVADDR              the functions that reference VADDR (to fill in
                                                       an `at` / ambiguous `str` entry's `ref`)

A native that needs a guest global, a string the guest passes on (an assert's file and message) or a
.rodata table names it in its subsystem's port/src/native/<s>/addresses.txt; nothing types a 3.7.0
vaddr into C++ any more (docs/code-review-2026-10-06.md P2). Each entry is found in the lib, so a new
build of the lib is a regeneration (AGENTS.md "regenerate ... address tables"), and soa refuses
natives on any lib but the one the tables were made from (kLibSha256 in common's table,
native/common/lib_check.cpp). Entries used by more than one subsystem go in common's
(port/src/native/common/addresses.txt, namespace soa::native); the same address under two entries is
an error.

addresses.txt, one entry per line ('#' starts a comment outside a string):

    namespace soa::native::fakeapi                  (optional; default soa::native::<s>, common: soa::native)
    NAME  sym  SYMBOL                               a data symbol of .dynsym (a global, a static member)
    NAME  str  "TEXT"            [ref FUNC]         the string TEXT (C escapes; the NUL after it): where
                                                    TEXT\\0 occurs, also as the tail of a longer string
    NAME  str  "...TAIL"         [ref FUNC]         a whole string (a NUL before it) ending with TAIL
    NAME  at   0xVADDR [TYPE]     ref FUNC          an address without a symbol or text to find it by
                                                    (a function-local static, a .rodata table); FUNC
                                                    must reference it

FUNC is a function's symbol; `ref FUNC` keeps only the candidates FUNC's code addresses (ADRP + ADD /
LDR / STR, LDR literal), so a string that occurs several times, or an `at` vaddr, is tied to the code
that uses it. A `str` with more than one candidate left is an error. TYPE (`at` only) adds the value
the table holds in the lib to the comment: f32, u32[N], ...

The generated header (do not edit) holds `inline constexpr std::uint64_t NAME = 0x...;` in the
namespace, each with what it is in a comment, and the lib's stamp (genlib.stamp(): path, version,
sha256). Code adds main_lib()->base (or uses its subsystem's at_vaddr / static_at helper).
"""
import argparse
import ast
import glob
import os
import re
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import genlib  # noqa: E402 (the default lib is 3.7.0's)

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs  # noqa: E402
from capstone.arm64 import ARM64_INS_ADD, ARM64_INS_ADR, ARM64_INS_ADRP, ARM64_OP_IMM, ARM64_OP_MEM, ARM64_OP_REG  # noqa: E402
from elftools.elf.elffile import ELFFile  # noqa: E402

REPO = genlib.REPO
NATIVE = os.path.join(REPO, "port", "src", "native")

LINE = re.compile(r'^(?P<name>[A-Za-z_]\w*)\s+(?P<kind>sym|str|at)\s+(?P<what>"(?:[^"\\]|\\.)*"|\S+)'
                  r'(?:\s+(?P<type>[a-z]\d+(?:\[\d+\])?))?(?:\s+ref\s+(?P<ref>\S+))?\s*(?:#\s*(?P<note>.*))?$')
TYPES = {"f32": ("<f", 4), "f64": ("<d", 8), "u32": ("<I", 4), "s32": ("<i", 4), "u64": ("<Q", 8), "u16": ("<H", 2),
         "u8": ("<B", 1)}


class Lib:
    def __init__(self, path):
        self.path = path
        self.data = open(path, "rb").read()
        with open(path, "rb") as f:
            elf = ELFFile(f)
            self.secs = [(s.name, s["sh_addr"], s["sh_size"], s["sh_offset"], s["sh_type"]) for s in elf.iter_sections()
                         if s["sh_addr"]]
            self.syms = {}
            for s in elf.get_section_by_name(".dynsym").iter_symbols():
                if s.name and s["st_value"]:
                    self.syms[s.name] = (s["st_value"], s["st_size"], s["st_info"]["type"])
        self.md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
        self.md.detail = True
        self._refs = {}

    def section(self, va):
        for name, addr, size, off, typ in self.secs:
            if addr <= va < addr + size:
                return name, addr, size, off, typ
        return None

    def read(self, va, n):
        s = self.section(va)
        if not s or s[4] == "SHT_NOBITS":
            return None
        return self.data[s[3] + va - s[1]:s[3] + va - s[1] + n]

    def data_sections(self):
        return [s for s in self.secs if s[0] in (".rodata",)]

    def refs(self, func):
        """Every address FUNC's code computes (ADRP + ADD / LDR / STR, ADR, LDR literal)."""
        if func in self._refs:
            return self._refs[func]
        if func not in self.syms:
            raise SystemExit(f"ref {func}: no such symbol in {self.path}")
        va, size, _ = self.syms[func]
        code = self.read(va, size)
        page, out = {}, set()
        for ins in self.md.disasm(code, va):
            ops = ins.operands
            if ins.id == ARM64_INS_ADRP:
                page[ops[0].reg] = ops[1].imm
            elif ins.id == ARM64_INS_ADR:
                out.add(ops[1].imm)
            elif ins.id == ARM64_INS_ADD and len(ops) == 3 and ops[1].type == ARM64_OP_REG and ops[2].type == ARM64_OP_IMM:
                if ops[1].reg in page:
                    out.add(page[ops[1].reg] + ops[2].imm)
            else:
                for o in ops:
                    if o.type == ARM64_OP_MEM and o.mem.base in page and not o.mem.index:
                        out.add(page[o.mem.base] + o.mem.disp)
                if ins.mnemonic.startswith("ldr") and len(ops) == 2 and ops[1].type == ARM64_OP_IMM:
                    out.add(ops[1].imm)  # LDR (literal)
        self._refs[func] = out
        return out

    def find_string(self, text, whole):
        """vaddrs where `text` + NUL is (whole: with a NUL or the section start before it)."""
        needle = text + b"\0"
        out = []
        for name, addr, size, off, typ in self.data_sections():
            blob = self.data[off:off + size]
            i = blob.find(needle)
            while i >= 0:
                out.append(addr + i)
                i = blob.find(needle, i + 1)
        if whole:
            out = [a for a in out if self.read(a - 1, 1) in (b"\0", None)]
        return out

    def find_tail(self, tail):
        """vaddrs of whole strings ending with `tail`."""
        out = []
        for a in self.find_string(tail, whole=False):
            s = a
            while self.read(s - 1, 1) not in (b"\0", None):
                s -= 1
            out.append(s)
        return sorted(set(out))

    def cstr(self, va):
        b = self.read(va, 4096)
        return b.split(b"\0", 1)[0]


def c_escape(b, limit=110):
    s = b.decode("utf-8", "backslashreplace").replace("\\", "\\\\").replace("\n", "\\n").replace("\t", "\\t").replace('"', '\\"')
    return '"' + (s if len(s) <= limit else "..." + s[-(limit - 3):]) + '"'


def parse(path):
    ns, entries = None, []
    for no, raw in enumerate(open(path, encoding="utf-8"), 1):
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        if line.startswith("namespace "):
            ns = line.split()[1]
            continue
        m = LINE.match(line)
        if not m:
            raise SystemExit(f"{path}:{no}: can't parse: {line}")
        e = m.groupdict()
        e["where"] = f"{os.path.relpath(path, REPO)}:{no}"
        entries.append(e)
    return ns, entries


def resolve(lib, e):
    """(vaddr, comment) of one entry."""
    kind, what, ref = e["kind"], e["what"], e["ref"]
    if kind == "sym":
        if what not in lib.syms:
            raise SystemExit(f"{e['where']}: {what}: no such symbol")
        va, size, typ = lib.syms[what]
        return va, f"{what} ({typ[4:].lower()}, {size} bytes)"
    if kind == "str":
        if not what.startswith('"'):
            raise SystemExit(f"{e['where']}: str takes a quoted string")
        text = ast.literal_eval(what).encode("utf-8")
        tail = text.startswith(b"...")
        cands = lib.find_tail(text[3:]) if tail else lib.find_string(text, whole=False)
        if ref:
            r = lib.refs(ref)
            cands = [a for a in cands if a in r]
        if len(cands) != 1:
            raise SystemExit(f"{e['where']}: {what}: {len(cands)} candidates "
                             f"({', '.join(hex(a) for a in cands[:8])}){'' if ref else '; add ref FUNC'}")
        va = cands[0]
        return va, c_escape(lib.cstr(va)) + (f", used by {ref}" if ref else "")
    # at
    va = int(what, 0)
    if not ref:
        raise SystemExit(f"{e['where']}: an `at` entry needs ref FUNC")
    if va not in lib.refs(ref):
        raise SystemExit(f"{e['where']}: {ref} doesn't reference {what} in this lib (re-derive it from the decompile)")
    sec = lib.section(va)
    note = f"{sec[0] if sec else '?'}, used by {ref}"
    if e["type"]:
        m = re.match(r"([a-z]\d+)(?:\[(\d+)\])?$", e["type"])
        fmt, n = TYPES[m.group(1)], int(m.group(2) or 1)
        b = lib.read(va, fmt[1] * n)
        if b is None:
            raise SystemExit(f"{e['where']}: {what} has no file bytes (.bss) for a TYPE")
        vals = [struct.unpack_from(fmt[0], b, k * fmt[1])[0] for k in range(n)]
        shown = ", ".join(repr(v) if isinstance(v, float) else hex(v) for v in vals[:8]) + (", ..." if n > 8 else "")
        note = f"{e['type']} {{{shown}}}, " + note
    return va, note


def spec_files(subsystems):
    files = sorted(glob.glob(os.path.join(NATIVE, "*", "addresses.txt")))
    if subsystems:
        files = [f for f in files if os.path.basename(os.path.dirname(f)) in subsystems]
    return files


def render(lib, spec, all_specs_seen):
    sub = os.path.basename(os.path.dirname(spec))
    ns, entries = parse(spec)
    ns = ns or ("soa::native" if sub == "common" else f"soa::native::{sub}")
    rel = os.path.relpath(spec, REPO)
    lines = [f"// Generated by tools/gen_addresses.py from {rel}; do not edit (regenerate).",
             f"// libSOA.so {genlib.version(lib.path)}, sha256 {genlib.sha256(lib.path)}",
             "// The guest addresses (ELF vaddrs: add main_lib()->base) the natives of this subsystem use.",
             "#pragma once", "", "#include <cstdint>", ""]
    if sub == "common":
        lines += ["namespace soa::native {", "// The lib these tables were generated from (native/common/lib_check.cpp checks the",
                  "// loaded one: natives are refused on any other build).",
                  f'inline constexpr char kLibSha256[] = "{genlib.sha256(lib.path)}";', "}  // namespace soa::native", ""]
    lines.append(f"namespace {ns} {{")
    for e in entries:
        # (names are unique over every table: a subsystem's namespace sees common's, and a name
        # declared in both would silently shadow it)
        if e["name"] in all_specs_seen:
            raise SystemExit(f"{e['where']}: {e['name']} is also {all_specs_seen[e['name']]}")
        all_specs_seen[e["name"]] = e["where"]
        va, note = resolve(lib, e)
        if va in all_specs_seen:
            raise SystemExit(f"{e['where']}: {hex(va)} is also {all_specs_seen[va]}: one entry (in common's "
                             "addresses.txt when two subsystems use it)")
        all_specs_seen[va] = f"{e['name']} ({e['where']})"
        if e["note"]:
            note += f"; {e['note']}"
        lines.append(f"inline constexpr std::uint64_t {e['name']} = {va:#x};  // {note}")
    lines.append(f"}}  // namespace {ns}")
    out = os.path.join(os.path.dirname(spec), "gen", f"{sub}_addresses.h")
    return out, "\n".join(lines) + "\n"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lib", default=genlib.lib_path())
    ap.add_argument("--check", action="store_true", help="compare with the headers instead of writing them")
    ap.add_argument("--refs", metavar="VADDR", help="print the functions whose code references VADDR")
    ap.add_argument("subsystems", nargs="*")
    a = ap.parse_args()
    lib = Lib(a.lib)
    if a.refs:
        want = int(a.refs, 0)
        for name, (va, size, typ) in sorted(lib.syms.items(), key=lambda kv: kv[1][0]):
            if typ == "STT_FUNC" and size and want in lib.refs(name):
                print(f"{va:#x} {name}")
        return
    seen, ok = {}, True
    # (every table is resolved, also with SUBSYS given, so a duplicate across subsystems is found)
    for spec in spec_files(None):
        out, text = render(lib, spec, seen)
        if a.subsystems and os.path.basename(os.path.dirname(spec)) not in a.subsystems:
            continue
        rel = os.path.relpath(out, REPO)
        if a.check:
            have = open(out).read() if os.path.exists(out) else None
            if have != text:
                print(f"stale: {rel} (run tools/gen_addresses.py)")
                ok = False
            else:
                print(f"same: {rel}")
        else:
            os.makedirs(os.path.dirname(out), exist_ok=True)
            if not os.path.exists(out) or open(out).read() != text:
                open(out, "w").write(text)
                print(f"wrote {rel}")
            else:
                print(f"same: {rel}")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
