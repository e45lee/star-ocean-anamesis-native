"""Run individual libSOA.so functions under unicorn (arm64) for cross-checking."""
import os
import sys

from unicorn import UC_ARCH_ARM64, UC_MODE_ARM, Uc
from unicorn.arm64_const import UC_ARM64_REG_LR, UC_ARM64_REG_SP, UC_ARM64_REG_X0, UC_ARM64_REG_CPACR_EL1

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from elfinfo import lib  # noqa: E402

STACK, HEAP, STOP = 0x7F000000, 0x60000000, 0x7FFFF000


def page(x):
    return x & ~0xFFF


class Emu:
    def __init__(self):
        L = self.L = lib()
        self.uc = uc = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
        uc.reg_write(UC_ARM64_REG_CPACR_EL1, 3 << 20)  # enable FP/SIMD
        for s in L.segs:
            lo, hi = page(s["p_vaddr"]), page(s["p_vaddr"] + s["p_memsz"] + 0xFFF)
            uc.mem_map(lo, hi - lo)
            o = s["p_offset"]
            uc.mem_write(s["p_vaddr"], L.data[o:o + s["p_filesz"]])
        uc.mem_map(STACK - 0x100000, 0x100000)
        uc.mem_map(HEAP, 0x100000)
        uc.mem_map(STOP, 0x1000)
        self.heap = HEAP

    def alloc(self, data=b"", size=None):
        size = size or len(data)
        p = self.heap
        self.heap += (size + 15) & ~15
        if data:
            self.uc.mem_write(p, data)
        return p

    def call(self, func, *args):
        va = self.L.by_name[func] if isinstance(func, str) else func
        uc = self.uc
        for i, a in enumerate(args):
            uc.reg_write(UC_ARM64_REG_X0 + i, a)
        uc.reg_write(UC_ARM64_REG_SP, STACK - 0x1000)
        uc.reg_write(UC_ARM64_REG_LR, STOP)
        uc.emu_start(va, STOP)
        return uc.reg_read(UC_ARM64_REG_X0)
