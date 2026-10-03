#!/usr/bin/env python3
r"""Generate port/src/native/api/gen/fakeapi_tables.inc from a libSOA.so (FakeApiCaller).

The port's FakeApiCaller (port/src/native/api/fakeapi.cpp) needs, per request method, the
FunctionID, the vaddr of its "FakeApi/<name>.msgp" string, the vaddr of its lambda's std::function
vtable (the address point the closure stores), that vtable's operator() (slot 6) and the
CApiNotify handler the operator() forwards to; plus the methods that only store a Status and the
ones that return a constant. All of it is read from the library's code:

  * the FakeApiCaller vtable (_ZTV13FakeApiCaller) gives the methods; entries that aren't
    FakeApiCaller's own (inherited IApiCaller stubs) are skipped; rows are in code-address order;
  * a request method calls FakeApiCaller::AddLocalFile: the FunctionID is the w1 immediate
    (movz/movk), the file name and the lambda vtable are adrp+add pairs (the one into a
    "FakeApi/" string, the one into .data.rel.ro);
  * the operator() is the vtable's slot 6 (address point + 0x30, an R_AARCH64_RELATIVE addend);
  * its handler is the CApiNotify::On*Res it calls; a lambda that builds an ASON (Aska::ASON::*,
    for CParameterManager::Deserialize) is a login lambda (handler nullptr: the fake login);
  * "status only": mov wN/xN, #V; str xN, [x8]; ret. "const": mov w0, #V; ret (or a bare ret: -1).

Usage:
  tools/gen_fakeapi_tables.py [--lib PATH] [-o OUT]       # default: the 3.7.0 lib, write OUT
  tools/gen_fakeapi_tables.py --ghidra-check TABLE DECOMP # TABLE's lambdas vs a Ghidra decompile:
      tools/decomp_at.sh --v370 NAME $(awk -F', ' '/X\("_ZN13/ {printf "%x ", strtonum($5) + 0x100000}' TABLE)
      tools/gen_fakeapi_tables.py --ghidra-check TABLE work/decomp/NAME.resolved.c
  tools/gen_fakeapi_tables.py --lib LIB --check FILE      # exit 1 if FILE differs from LIB's table
                                                          # (the header line isn't compared)

The header line always names the 3.7.0 lib (the committed table's), whatever --lib is.

The table was first written by hand-run scripts from the offline build's lib; this generator
reproduced that file byte for byte (--lib <that lib> --check <that table>), which is how it was
validated before it generated the 3.7.0 table (docs/history/REBASE-370.md "P1").
"""
import argparse
import os
import struct
import sys

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs
from capstone.arm64 import ARM64_OP_IMM, ARM64_OP_MEM, ARM64_OP_REG

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import genlib  # noqa: E402 (the output header's lib stamp)
from elfinfo import Lib  # noqa: E402

REPO = os.path.dirname(HERE)
DEFAULT_LIB = os.path.join(REPO, "work/libSOA-3.7.0.so")
DEFAULT_OUT = os.path.join(REPO, "port/src/native/api/gen/fakeapi_tables.inc")

ADD_LOCAL_FILE = "_ZN13FakeApiCaller12AddLocalFileEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDEPKcNSt6__ndk18functionIFNS0_6StatusEPaRjEEE"
DESERIALIZE = "_ZN17CParameterManager11DeserializeEPKN4Aska4ASON6AValue4AMapE"
FAKE_PREFIXES = ("_ZN13FakeApiCaller", "_ZNK13FakeApiCaller")


class Image(Lib):
    def __init__(self, path):
        super().__init__(path)
        self.md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
        self.md.detail = True
        self.sizes = {}
        for secname in (".dynsym", ".symtab"):
            sec = self.elf.get_section_by_name(secname)
            if not sec:
                continue
            for s in sec.iter_symbols():
                if s.name and s["st_value"]:
                    self.sizes.setdefault(s["st_value"], s["st_size"])
        self.relative = {}  # offset -> pointer value
        self.symrel = {}    # offset -> symbol name (R_AARCH64_ABS64 against a symbol)
        rela = self.elf.get_section_by_name(".rela.dyn")
        dynsym = self.elf.get_section_by_name(".dynsym")
        for r in rela.iter_relocations():
            t = r["r_info_type"]
            if t == 1027:  # R_AARCH64_RELATIVE
                self.relative[r["r_offset"]] = r["r_addend"]
            elif t == 257 and r["r_info_sym"]:  # R_AARCH64_ABS64
                sym = dynsym.get_symbol(r["r_info_sym"])
                if sym["st_value"]:
                    self.relative[r["r_offset"]] = sym["st_value"] + r["r_addend"]
                    self.symrel[r["r_offset"]] = sym.name
        self.sym_index = {}  # name -> .dynsym index (orders symbols that share an address)
        for i, sym in enumerate(self.elf.get_section_by_name(".dynsym").iter_symbols()):
            self.sym_index.setdefault(sym.name, i)
        sec = self.elf.get_section_by_name(".data.rel.ro")
        self.relro = (sec["sh_addr"], sec["sh_addr"] + sec["sh_size"])

    def ptr(self, va):
        """The pointer stored at va (its relocation's addend, or the raw bytes)."""
        if va in self.relative:
            return self.relative[va]
        return struct.unpack("<Q", self.read(va, 8))[0]

    def fname(self, va):
        """The exported/static symbol at exactly va, or None."""
        n = self.by_addr.get(va)
        return n

    def target_name(self, va):
        if va in self.plt:
            return self.plt[va]
        return self.by_addr.get(va, "?")

    def insns(self, va):
        """The function's instructions: by its symbol size, or (a local function such as a
        lambda's operator(), which has no symbol) up to its first ret / unconditional b."""
        size = self.sizes.get(va)
        if size:
            return list(self.md.disasm(self.read(va, size), va))
        out = []
        for ins in self.md.disasm(self.read(va, 0x1000), va):
            out.append(ins)
            if ins.mnemonic in ("ret", "b", "br"):
                break
        return out


def reg_name(md, r):
    return md.reg_name(r)


def analyse_request(img, va, insns):
    """fid, file vaddr, lambda vtable vaddr of a request method (it calls AddLocalFile)."""
    md = img.md
    regs = {}       # register -> value (adrp/add/movz/movk tracking, straight-line)
    fid = None
    file_va = vt_va = None
    for ins in insns:
        m = ins.mnemonic
        ops = ins.operands
        if m == "adrp":
            regs[reg_name(md, ops[0].reg)] = ops[1].imm
        elif m == "add" and len(ops) == 3 and ops[2].type == ARM64_OP_IMM and reg_name(md, ops[1].reg) in regs:
            v = regs[reg_name(md, ops[1].reg)] + ops[2].imm
            regs[reg_name(md, ops[0].reg)] = v
            s = None
            try:
                s = img.cstr(v, 64)
            except ValueError:
                pass
            if s and s.startswith(b"FakeApi/"):
                file_va = v
            elif img.relro[0] <= v < img.relro[1]:
                vt_va = v  # the last one: the address point (vtable + 0x10)
        elif m in ("mov", "movz") and ops[1].type == ARM64_OP_IMM:
            regs[reg_name(md, ops[0].reg)] = ops[1].imm & 0xffffffff
        elif m == "movk" and ops[1].type == ARM64_OP_IMM:
            r = reg_name(md, ops[0].reg)
            shift = ops[1].shift.value if ops[1].shift.type else 0
            regs[r] = (regs.get(r, 0) & ~(0xffff << shift) | (ops[1].imm << shift)) & 0xffffffff
        elif m == "bl":
            if img.target_name(ops[0].imm) == ADD_LOCAL_FILE:
                fid = regs.get("w1")
                break
    return fid, file_va, vt_va


def calls_of(img, va):
    out = []
    for ins in img.insns(va):
        if ins.mnemonic in ("bl", "b") and ins.operands[0].type == ARM64_OP_IMM:
            out.append(img.target_name(ins.operands[0].imm))
    return out


def classify_simple(img, insns):
    """('status', V) / ('const', V) / None for a short method."""
    real = [i for i in insns]
    if not real:
        return None
    md = img.md
    # status only: mov wN|xN, #V ; str xN, [x8] ; ret   (or str xzr, [x8] ; ret)
    if real[-1].mnemonic == "ret":
        body = real[:-1]
        if len(body) in (1, 2) and body[-1].mnemonic == "str" and body[-1].operands[1].type == ARM64_OP_MEM \
                and reg_name(md, body[-1].operands[1].mem.base) == "x8" and body[-1].operands[1].mem.disp == 0:
            src = reg_name(md, body[-1].operands[0].reg)
            if src in ("xzr", "wzr") and len(body) == 1:
                return ("status", 0)
            if len(body) == 2 and body[0].mnemonic in ("mov", "movz") and body[0].operands[1].type == ARM64_OP_IMM \
                    and reg_name(md, body[0].operands[0].reg)[1:] == src[1:]:
                return ("status", body[0].operands[1].imm)
        if len(body) == 0:
            return ("const", -1)
        if len(body) == 1 and body[0].mnemonic in ("mov", "movz") and body[0].operands[1].type == ARM64_OP_IMM \
                and reg_name(md, body[0].operands[0].reg) in ("w0", "x0"):
            return ("const", body[0].operands[1].imm)
        if len(body) == 1 and body[0].mnemonic == "mov" and body[0].operands[1].type == ARM64_OP_REG \
                and reg_name(md, body[0].operands[0].reg) in ("w0", "x0") and reg_name(md, body[0].operands[1].reg) in ("wzr", "xzr"):
            return ("const", 0)
    return None


def method_short(sym):
    p = sym[len("_ZN13FakeApiCaller"):] if sym.startswith("_ZN13") else sym[len("_ZNK13FakeApiCaller"):]
    n = 0
    while p[n].isdigit():
        n += 1
    k = int(p[:n])
    return p[n:n + k]


def generate(path):
    img = Image(path)
    vt = img.by_name["_ZTV13FakeApiCaller"]
    vt_size = img.sizes[vt]
    seen = set()
    methods = []
    for off in range(0x10, vt_size, 8):
        fn = img.ptr(vt + off)
        if not fn:
            continue
        # By name: identical tiny methods (a bare ret) share one address (code folding).
        name = img.symrel.get(vt + off) or img.fname(fn)
        if not name or name in seen or not name.startswith(FAKE_PREFIXES):
            continue
        if "D0Ev" in name or "D1Ev" in name or "D2Ev" in name:
            continue
        seen.add(name)
        methods.append((name, fn))
    # Source order: the methods' code addresses (the order FakeApiCaller.cpp defines them).
    methods.sort(key=lambda m: (m[1], img.sym_index.get(m[0], 0)))
    requests, status, const = [], [], []
    for name, fn in methods:
        insns = img.insns(fn)
        calls = [img.target_name(i.operands[0].imm) for i in insns if i.mnemonic == "bl" and i.operands[0].type == ARM64_OP_IMM]
        if ADD_LOCAL_FILE in calls:
            fid, file_va, lvt = analyse_request(img, fn, insns)
            if fid is None or file_va is None or lvt is None:
                raise SystemExit("%s: couldn't read fid/file/vtable (%r %r %r)" % (name, fid, file_va, lvt))
            op = img.ptr(lvt + 0x30)
            op_calls = calls_of(img, op)
            if DESERIALIZE in op_calls or any(c.startswith("_ZN4Aska4ASON") for c in op_calls):
                handler = None
            else:
                hs = [c for c in op_calls if c.startswith("_ZN10CApiNotify")]
                if len(set(hs)) != 1:
                    raise SystemExit("%s: lambda %#x calls %r" % (name, op, op_calls))
                handler = hs[0]
            requests.append((name, fid, file_va, lvt, op, handler, img.cstr(file_va).decode()))
            continue
        c = classify_simple(img, insns)
        if c is None:
            # Progress, IsRequesting, Release, ...: hand-written natives, not table rows.
            continue
        (status if c[0] == "status" else const).append((name, c[1]))
    return requests, status, const


def render(requests, status, const, lib=DEFAULT_LIB):
    out = []
    w = out.append
    w('// Generated by tools/gen_fakeapi_tables.py from the 3.7.0 libSOA.so (FakeApiCaller methods); see docs/notes.md "Offline server (FakeApiCaller)".')
    w('// ' + genlib.stamp(lib))
    w("// Requests: {method, FunctionID, file name (vaddr), lambda vtable (vaddr), lambda operator() (vaddr), CApiNotify handler}.")
    w("// handler == nullptr: the Login lambda (fakes a login first).")
    w("#define FAKEAPI_REQUESTS(X) \\")
    for name, fid, file_va, lvt, op, handler, fname in requests:
        h = '"%s"' % handler if handler else "nullptr"
        w('    X("%s", 0x%08x, %#x, %#x, %#x, %s) /* %s -> %s */ \\' % (name, fid, file_va, lvt, op, h, method_short(name), fname))
    w("")
    w("// Methods that only store a Status through x8: {method, status}.")
    w("#define FAKEAPI_STATUS_ONLY(X) \\")
    for name, v in status:
        w('    X("%s", %d) \\' % (name, v))
    w("")
    w("// Methods that return a constant in x0 (or nothing): {method, value or -1 for none}.")
    w("#define FAKEAPI_CONST(X) \\")
    for name, v in const:
        w('    X("%s", %d) \\' % (name, v))
    w("")
    w("// end of tables")
    return "\n".join(out) + "\n"


def ghidra_check(table_path, decomp_path):
    """Checks every request row of the table against a Ghidra decompile of its lambda operator()s
    (tools/decomp_at.sh [--v370] OUT <op + 0x100000>...): each forwards to the row's
    CApiNotify::On*Res with (owner + 0x60, *data), and the login rows build an ASON for
    CParameterManager::Deserialize, then call OnGetPlayerRes. Returns the number of mismatches."""
    import re
    txt = open(decomp_path).read()
    dec = {}
    for b in re.split(r"^// ==== @", txt, flags=re.M)[1:]:
        a = int(b[:8], 16) - 0x100000
        hs = set(re.findall(r"CApiNotify::(On\w+)\(", b))
        for m in re.findall(r"PTR_(_ZN10CApiNotify\w+?EPaRj)_0", b):
            p = m[len("_ZN10CApiNotify"):]
            n = re.match(r"\d+", p).group(0)
            hs.add(p[len(n):len(n) + int(n)])
        dec[a] = ("Aska::ASON::Init" in b and "Deserialize" in b, hs, "+ 0x60" in b)
    rows = re.findall(r'X\("(\w+)", (0x\w+), (0x\w+), (0x\w+), (0x\w+), ([^)]*)\)', open(table_path).read())
    bad = 0
    for sym, fid, f, vt, op, h in rows:
        if int(op, 16) not in dec:
            print("not decompiled: %s %s" % (sym, op))
            bad += 1
            continue
        login, hs, notify = dec[int(op, 16)]
        if h == "nullptr":
            good = login and hs == {"OnGetPlayerRes"}
        else:
            p = h.strip('"')[len("_ZN10CApiNotify"):]
            n = re.match(r"\d+", p).group(0)
            good = hs == {p[len(n):len(n) + int(n)]} and notify
        if not good:
            print("MISMATCH %s %s %s: decompile calls %s" % (sym, op, h, sorted(hs)))
            bad += 1
    print("Ghidra check: %d of %d lambdas match" % (len(rows) - bad, len(rows)))
    return bad


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lib", default=DEFAULT_LIB)
    ap.add_argument("-o", "--out", default=None)
    ap.add_argument("--check", default=None, help="compare with this file instead of writing")
    ap.add_argument("--ghidra-check", nargs=2, metavar=("TABLE", "DECOMP"),
                    help="check TABLE's lambdas against a decomp_at.sh output (.resolved.c) of their operator()s")
    a = ap.parse_args()
    if a.ghidra_check:
        return 1 if ghidra_check(*a.ghidra_check) else 0
    text = render(*generate(a.lib), lib=a.lib)
    if a.check:
        # The first line (the header naming the generator) isn't compared: the first (offline-build) table predated it.
        # Nor the lib stamp (`// libSOA.so: ...`).
        def body(t):
            return "".join(l for l in t.split("\n", 1)[1].splitlines(True) if not l.startswith("// libSOA.so:"))
        old, text = body(open(a.check).read()), body(text)
        if old == text:
            print("same: %s" % a.check)
            return 0
        import difflib
        sys.stdout.writelines(difflib.unified_diff(old.splitlines(True), text.splitlines(True), a.check, "generated"))
        return 1
    out = a.out or DEFAULT_OUT
    open(out, "w").write(text)
    print("wrote %s" % out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
