"""Helpers for poking at libSOA.so: resolve PLT stubs and symbols, read .rodata.

Ghidra loads the library at image base 0x100000, so Ghidra addresses are
ELF virtual addresses + GHIDRA_BASE.
"""
import bisect
import os
import sys
from functools import lru_cache

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

# Default: the 3.7.0 client the port runs. tools/common.sh exports SOA_LIB (the viewer's lib with
# decomp.sh --v380). (380-ok)
LIB_370 = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "work", "libSOA-3.7.0.so")
LIB = os.environ.get("SOA_LIB") or LIB_370
GHIDRA_BASE = 0x100000


class Lib:
    def __init__(self, path=LIB):
        self.f = open(path, "rb")
        self.elf = ELFFile(self.f)
        self.data = open(path, "rb").read()
        self.segs = [s for s in self.elf.iter_segments() if s["p_type"] == "PT_LOAD"]
        self._syms()
        self._plt()

    def v2o(self, va):
        for s in self.segs:
            if s["p_vaddr"] <= va < s["p_vaddr"] + s["p_filesz"]:
                return va - s["p_vaddr"] + s["p_offset"]
        raise ValueError(hex(va))

    def read(self, va, n):
        o = self.v2o(va)
        return self.data[o:o + n]

    def cstr(self, va, maxlen=512):
        b = self.read(va, maxlen)
        return b.split(b"\0", 1)[0]

    def _syms(self):
        self.by_name, by_addr = {}, {}
        for secname in (".dynsym", ".symtab"):
            sec = self.elf.get_section_by_name(secname)
            if not sec:
                continue
            for s in sec.iter_symbols():
                if s.name and s["st_value"]:
                    self.by_name.setdefault(s.name, s["st_value"])
                    by_addr.setdefault(s["st_value"], s.name)
        self.addrs = sorted(by_addr)
        self.by_addr = by_addr

    def _plt(self):
        # Map GOT slot -> symbol name from .rela.plt, then decode each PLT stub
        # (adrp x16; ldr x17,[x16,#off]; add x16,..; br x17) to find its GOT slot.
        got2name = {}
        dynsym = self.elf.get_section_by_name(".dynsym")
        for sec in self.elf.iter_sections():
            if isinstance(sec, RelocationSection):
                for r in sec.iter_relocations():
                    if r["r_info_sym"]:
                        got2name[r["r_offset"]] = dynsym.get_symbol(r["r_info_sym"]).name
        self.got2name = got2name
        self.plt = {}
        plt = self.elf.get_section_by_name(".plt")
        base, code = plt["sh_addr"], plt.data()
        md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
        md.detail = True
        for off in range(0x20, len(code), 16):
            ins = list(md.disasm(code[off:off + 8], base + off))
            if len(ins) == 2 and ins[0].mnemonic == "adrp" and ins[1].mnemonic == "ldr":
                page = ins[0].operands[1].imm
                disp = ins[1].operands[1].mem.disp
                self.plt[base + off] = got2name.get(page + disp, "?")

    def name(self, va):
        if va in self.plt:
            return "PLT:" + self.plt[va]
        i = bisect.bisect_right(self.addrs, va) - 1
        if i >= 0:
            a = self.addrs[i]
            return self.by_addr[a] + ("" if a == va else "+%#x" % (va - a))
        return "?"


@lru_cache(None)
def lib():
    return Lib()


if __name__ == "__main__":
    L = lib()
    for arg in sys.argv[1:]:
        g = int(arg, 16)
        va = g - GHIDRA_BASE
        print(f"{g:#x} -> {L.name(va)}")
