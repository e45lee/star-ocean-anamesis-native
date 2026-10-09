#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Audit 3.7.0 function bodies that the pre-rebase restore run installed on 3.8.0 symbols (port/src/native/restore/restore370.cpp).

History tool: the restore370 image (3.7.0 bodies on the offline lib) is gone since the 3.7.0
rebase; kept for the record.

For each 3.7.0 function (mangled name), and every non-exported function it reaches by a direct
branch (static helpers, lambda bodies reached through std::function vtables it builds), lists:
  - calls through the PLT (these run the live 3.8.0 / native version, unless also kept),
  - direct references (adrp) into the 3.7.0 image's writable data that aren't relocated:
    non-exported statics, which are private and zero in the restore image (see loader.h),
  - moves of small constants into w1 right before a CUIVoiceManager call (menu-voice ids differ
    between the builds).

It also follows the std::function vtables (`__func`) a body builds, so lambda bodies are covered.

--emit FILE writes the private-static relocation table the loader applies (restore370_statics.inc):
each adrp in the audited code that reaches a non-exported 3.7.0 static is re-pointed at the 3.8.0
static at the same offset from the same preceding exported symbol (the live copy, which the 3.8.0
initialisers built), when that keeps the page offset.

Usage: tools/restore370_audit.py [--calls] [--emit FILE] SYM...   (SOA_LIB defaults to work/libSOA-3.7.0.so)
"""
import argparse
import os
import sys

os.environ.setdefault("SOA_LIB", os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "work", "libSOA-3.7.0.so"))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs  # noqa: E402
from capstone.arm64 import ARM64_OP_IMM, ARM64_OP_MEM  # noqa: E402
from elfinfo import Lib  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("names", nargs="+", metavar="SYM", help="mangled names of the 3.7.0 functions to audit")
    ap.add_argument("--calls", action="store_true", help="also list each function's PLT calls")
    ap.add_argument("--emit", metavar="FILE", help="write the private-static relocation table here")
    a = ap.parse_args()
    show_calls, emit, names = a.calls, a.emit, a.names
    L = Lib(os.environ["SOA_LIB"])
    dynsym = L.elf.get_section_by_name(".dynsym")
    exported = {s["st_value"] for s in dynsym.iter_symbols() if s["st_value"] and s["st_shndx"] != "SHN_UNDEF"}
    sizes = {}
    for secname in (".dynsym", ".symtab"):
        sec = L.elf.get_section_by_name(secname)
        if sec:
            for s in sec.iter_symbols():
                if s["st_value"] and s["st_size"]:
                    sizes.setdefault(s["st_value"], s["st_size"])
    rw = []
    for sec in L.elf.iter_sections():
        if sec["sh_flags"] & 1 and sec.name in (".data", ".bss", ".tm_clone_table"):
            rw.append((sec["sh_addr"], sec["sh_addr"] + sec["sh_size"], sec.name))
    fde = sorted(L.addrs)
    relative = {}
    for sec in L.elf.iter_sections():
        if sec.name == ".rela.dyn":
            for r in sec.iter_relocations():
                if r["r_info_type"] == 1027:  # R_AARCH64_RELATIVE
                    relative[r["r_offset"]] = r["r_addend"]
    L8 = Lib(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "work", "extracted", "config.arm64_v8a", "lib", "arm64-v8a", "libSOA.so"))
    exp370 = sorted((s["st_value"], s.name, s["st_size"]) for s in dynsym.iter_symbols() if s["st_value"] and s["st_shndx"] != "SHN_UNDEF")
    exp380 = {s.name: (s["st_value"], s["st_size"]) for s in L8.elf.get_section_by_name(".dynsym").iter_symbols() if s["st_value"]}
    import bisect as _b
    exp370_addrs = [e[0] for e in exp370]

    def map_static(t):
        i = _b.bisect_right(exp370_addrs, t) - 1
        a, n, sz = exp370[i]
        if n not in exp380:
            return None, n
        a8, sz8 = exp380[n]
        return a8 + (t - a), n
    patches = []
    starts = sorted(set(L.addrs) | {v for v in relative.values() if 0x1000000 <= v < 0x2700000})
    rr = L.elf.get_section_by_name(".data.rel.ro")
    relro = (rr["sh_addr"], rr["sh_addr"] + rr["sh_size"])
    tx = L.elf.get_section_by_name(".text")
    text = (tx["sh_addr"], tx["sh_addr"] + tx["sh_size"])
    md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
    md.detail = True

    # function extents from .eh_frame (local functions have no symbol size)
    from elftools.dwarf.callframe import FDE
    fdes = {}
    for e in L.elf.get_dwarf_info().EH_CFI_entries():
        if isinstance(e, FDE):
            fdes[e.header["initial_location"]] = e.header["address_range"]

    def fsize(a):
        if a in sizes:
            return sizes[a]
        i = _b.bisect_right(starts, a)
        if i < len(starts):
            return min(starts[i] - a, 8192)
        import bisect
        i = bisect.bisect_right(fde, a)
        return (fde[i] - a) if i < len(fde) else 0x400

    seen = set()
    todo = [(L.by_name[n], n) for n in names if n in L.by_name]
    for n in names:
        if n not in L.by_name:
            print("not found:", n)
    bad = 0
    while todo:
        addr, label = todo.pop()
        if addr in seen:
            continue
        seen.add(addr)
        size = fsize(addr)
        code = L.read(addr, size)
        insns = list(md.disasm(code, addr))
        calls, statics, voices = [], [], []
        pages = {}
        for k, i in enumerate(insns):
            if i.mnemonic == "adrp":
                pages[i.operands[0].reg] = i.operands[1].imm
            elif i.mnemonic in ("add", "ldr", "str", "ldrb", "strb", "ldrh", "strh", "ldp", "stp", "ldrsw", "ldur", "stur"):
                ops = i.operands
                tgt = None
                if i.mnemonic == "add" and len(ops) == 3 and ops[1].reg in pages and ops[2].type == ARM64_OP_IMM:
                    tgt = pages[ops[1].reg] + ops[2].imm
                else:
                    for o in ops:
                        if o.type == ARM64_OP_MEM and o.mem.base in pages:
                            tgt = pages[o.mem.base] + o.mem.disp
                if tgt is not None:
                    for lo, hi, sn in rw:
                        if lo <= tgt < hi:
                            statics.append((i.address, tgt, sn, L.name(tgt)))
                            m, anchor = map_static(tgt)
                            # find the adrp that set this base register
                            for j in range(k - 1, max(-1, k - 40), -1):
                                pj = insns[j]
                                if pj.mnemonic == "adrp" and pj.operands[0].reg == (ops[1].reg if i.mnemonic == "add" else [o for o in ops if o.type == ARM64_OP_MEM][0].mem.base):
                                    patches.append((pj.address, tgt, m, anchor))
                                    break
                    if i.mnemonic == "add" and relro[0] <= tgt < relro[1]:
                        # a local vtable (std::function __func of a lambda built here): follow
                        # its code slots, so the lambda bodies are audited too
                        for slot in range(0, 9):
                            f = relative.get(tgt + 8 * slot)
                            if f and text[0] <= f < text[1] and f not in seen:
                                todo.append((f, "vslot " + L.name(f)))
            elif i.mnemonic in ("bl", "b") and i.operands[0].type == ARM64_OP_IMM:
                t = i.operands[0].imm
                if addr <= t < addr + size:
                    continue
                nm = L.name(t)
                calls.append(nm)
                if "CUIVoiceManager" in nm:
                    for j in range(max(0, k - 6), k):
                        if insns[j].mnemonic == "mov" and insns[j].op_str.startswith("w1,"):
                            voices.append((insns[j].address, insns[j].op_str, nm))
                if t not in L.plt and t not in exported :
                    todo.append((t, nm))
        # std::function vtables built here (adrp+add of a local vtable): follow their slots.
        print("== %s @%#x (%d bytes)%s" % (label, addr, size, "" if addr in exported else " [local]"))
        if show_calls:
            for c in sorted(set(calls)):
                print("   call", c)
        for a, t, sn, nm in statics:
            print("   STATIC %#x -> %#x %s %s" % (a, t, sn, nm))
            bad += 1
        for a, op, nm in voices:
            print("   VOICE %#x %s -> %s" % (a, op, nm))
    print("%d private-static references" % bad)
    if emit:
        out = ["// Generated by tools/restore370_audit.py --emit (do not edit): adrp instructions in the kept",
               "// 3.7.0 bodies that reach a non-exported static, re-pointed at the live 3.8.0 static.",
               "// {3.7.0 adrp vaddr, 3.7.0 target vaddr, 3.8.0 target vaddr}"]
        done = set()
        for a, t, m, anchor in sorted(set(patches)):
            if a in done:
                continue
            done.add(a)
            if m is None or (m - t) % 0x1000:
                out.append("// %#x -> %#x: no 3.8.0 counterpart with the same page offset (anchor %s)" % (a, t, anchor))
                print("UNMAPPED static %#x -> %#x (%s)" % (a, t, anchor))
                continue
            out.append("{%#x, %#x, %#x},  // %s+%#x" % (a, t, m, anchor, 0))
        open(emit, "w").write("\n".join(out) + "\n")


if __name__ == "__main__":
    main()
