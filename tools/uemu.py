"""A relocated libSOA.so under unicorn: the lib's segments with every dynamic relocation applied
(imports bound to trap stubs), a bump heap, and Python hooks on function addresses."""
import struct
import sys

from elftools.elf.relocation import RelocationSection
from unicorn import UC_ARCH_ARM64, UC_HOOK_CODE, UC_MODE_ARM, Uc
from unicorn.arm64_const import (UC_ARM64_REG_CPACR_EL1, UC_ARM64_REG_LR, UC_ARM64_REG_PC, UC_ARM64_REG_SP,
                                 UC_ARM64_REG_X0)

STACK_TOP, STACK_SIZE = 0x7F000000, 0x100000
HEAP, HEAP_SIZE = 0x60000000, 0x1000000
STUBS, NSTUBS = 0x70000000, 0x10000
STOP = 0x7FFFF000


class Emu:
    def __init__(self, L):
        self.L = L
        self.uc = uc = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
        uc.reg_write(UC_ARM64_REG_CPACR_EL1, 3 << 20)
        for s in L.segs:
            lo, hi = s["p_vaddr"] & ~0xFFF, (s["p_vaddr"] + s["p_memsz"] + 0xFFF) & ~0xFFF
            uc.mem_map(lo, hi - lo)
            o = s["p_offset"]
            uc.mem_write(s["p_vaddr"], L.data[o:o + s["p_filesz"]])
        uc.mem_map(STACK_TOP - STACK_SIZE, STACK_SIZE)
        uc.mem_map(HEAP, HEAP_SIZE)
        uc.mem_map(STUBS, NSTUBS * 4)
        uc.mem_write(STUBS, b"\xc0\x03\x5f\xd6" * NSTUBS)  # RET
        uc.mem_map(STOP, 0x1000)
        self.heap = HEAP
        self.stub_names = {}  # stub addr -> import name
        self.hooks = {}       # addr -> fn(emu) -> x0 or None (the stub's RET returns)
        self._next_hook = STUBS + 4 * NSTUBS
        self._relocate()
        uc.hook_add(UC_HOOK_CODE, self._on_code, begin=STUBS, end=STUBS + NSTUBS * 4)

    def _relocate(self):
        L, uc = self.L, self.uc
        dynsym = L.elf.get_section_by_name(".dynsym")
        syms = list(dynsym.iter_symbols())
        stub_of = {}
        for sec in L.elf.iter_sections():
            if not isinstance(sec, RelocationSection):
                continue
            for r in sec.iter_relocations():
                t, off, add = r["r_info_type"], r["r_offset"], r["r_addend"]
                if t == 1027:  # RELATIVE
                    v = add
                else:
                    s = syms[r["r_info_sym"]]
                    if s["st_shndx"] != "SHN_UNDEF" and s["st_value"]:
                        v = s["st_value"] + (add if t != 1026 else 0)
                    else:
                        if s.name not in stub_of:
                            a = STUBS + 4 * len(stub_of)
                            stub_of[s.name] = a
                            self.stub_names[a] = s.name
                        v = stub_of[s.name] + (add if t == 257 else 0)
                uc.mem_write(off, struct.pack("<Q", v))
        self.stub_of = stub_of

    def hook_import(self, name, fn):
        a = self.stub_of.get(name)
        if a is not None:
            self.hooks[a] = fn

    def hook_addr(self, addr, fn):
        """Replace the function at addr (inside the lib): it jumps to a fresh stub."""
        self._next_hook -= 4
        a = self._next_hook
        # B to the stub can't reach; patch the entry with LDR x16, #8; BR x16; .quad stub
        code = struct.pack("<IIQ", 0x58000050, 0xD61F0200, a)
        self.uc.mem_write(addr, code)
        self.hooks[a] = fn

    def _on_code(self, uc, addr, size, _):
        fn = self.hooks.get(addr)
        if fn is None:
            raise RuntimeError("unhooked import %s" % self.stub_names.get(addr, hex(addr)))
        r = fn(self)
        if r is not None:
            uc.reg_write(UC_ARM64_REG_X0, r & 0xFFFFFFFFFFFFFFFF)

    # ---- helpers ----
    def x(self, i):
        return self.uc.reg_read(UC_ARM64_REG_X0 + i)

    def alloc(self, size, fill=0):
        p = self.heap
        self.heap += (size + 15) & ~15
        self.uc.mem_write(p, bytes([fill]) * size)
        return p

    def read(self, a, n):
        return bytes(self.uc.mem_read(a, n))

    def q(self, a):
        return struct.unpack("<Q", self.read(a, 8))[0]

    def cstr(self, a):
        out = b""
        while True:
            c = self.read(a, 64)
            i = c.find(b"\0")
            if i >= 0:
                return out + c[:i]
            out += c
            a += 64

    def call(self, va, *args):
        uc = self.uc
        for i, v in enumerate(args):
            uc.reg_write(UC_ARM64_REG_X0 + i, v)
        uc.reg_write(UC_ARM64_REG_SP, STACK_TOP - 0x1000)
        uc.reg_write(UC_ARM64_REG_LR, STOP)
        uc.emu_start(va, STOP, count=50_000_000)
        return uc.reg_read(UC_ARM64_REG_X0)
