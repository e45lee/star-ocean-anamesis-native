"""Run the client's own Ninja (sqex) encryption code from libSOA.so under unicorn.

Ground truth for server/net/ninja/ninja_ref.cpp: the ARM64 functions of the client lib (default the
3.7.0 one, tools/elfinfo.py) are called directly; the few imports they use (memcpy, memset, operator new[]/delete[],
time) are implemented here. Addresses are ELF vaddrs (Ghidra = vaddr + 0x100000).
"""
import os
import struct

from unicorn import UC_ARCH_ARM64, UC_HOOK_CODE, UC_MODE_ARM, Uc
from unicorn.arm64_const import (UC_ARM64_REG_CPACR_EL1, UC_ARM64_REG_LR, UC_ARM64_REG_PC, UC_ARM64_REG_SP,
                                 UC_ARM64_REG_TPIDR_EL0, UC_ARM64_REG_X0, UC_ARM64_REG_X1, UC_ARM64_REG_X8)

from elfinfo import lib
from elftools.elf.relocation import RelocationSection

STACK, HEAP, STUBS, TLS, STOP = 0x7F000000, 0x60000000, 0x7E000000, 0x7D000000, 0x7FFFF000
HEAP_SIZE = 0x4000000

# Functions (ELF vaddr) as first read in the offline build's libSOA.so (380-ok); for the lib in use
# (default 3.7.0) they are re-based on the nearest exported symbol (the code is identical, only shifted).
ANCHORS = {"sqex": ("_ZN4sqex14IsValidVersionEPKvj", 0x113BE7C),
           "gpd": ("_ZN4Aska5Yayoi7GameRPC18GameProtocoledData8SetLoginERKNS1_13RequestHeaderEPKaS7_jS7_jhPNS_8Cryption5NinjaE",
                   0x1439004),
           "vt": ("_ZTVN4Aska8Cryption17AllocatorForNinjaE", 0x29CDA68)}
F38 = {
    "creator_ctor": ("sqex", 0x113C2F8),        # SqexEncryptionCreator(this, allocator)
    "create_by_id": ("sqex", 0x113C33C),        # (creator, alg_id, r2, key) -> algorithm
    "create_by_index": ("sqex", 0x113C314),     # (creator, r1 % 96 -> table @027e3164, r2, key)
    "create_from_envelope": ("sqex", 0x113C6B4),  # (creator, data, len, key)
    "destroy": ("sqex", 0x113C750),             # (creator, algorithm)
    "encrypt": ("sqex", 0x113BFCC),             # (algorithm, data, len) -> {ptr, len | err << 32}
    "decrypt": ("sqex", 0x113C0F4),             # (algorithm, data, len) -> {ptr, len | err << 32}
    "rng_seed": ("sqex", 0x113B528),            # Ninja message RNG init (ninja+0x30, seed)
    "ninja_encrypt": ("gpd", 0x143928C),        # (ninja, plain, len, out, cap) -> len or status
    "alloc_vtable": ("vt", 0x29CDA68 + 0x10),   # AllocatorForNinja
}
F = {}


class Client:
    def __init__(self, path=None):
        if path:
            os.environ["SOA_LIB"] = path
        L = self.L = lib()
        for k, (anchor, va) in F38.items():
            sym, base = ANCHORS[anchor]
            F[k] = va - base + L.by_name[sym]
        uc = self.uc = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
        uc.reg_write(UC_ARM64_REG_CPACR_EL1, 3 << 20)
        for s in L.segs:
            lo = s["p_vaddr"] & ~0xFFF
            hi = (s["p_vaddr"] + s["p_memsz"] + 0xFFF) & ~0xFFF
            uc.mem_map(lo, hi - lo)
            o = s["p_offset"]
            uc.mem_write(s["p_vaddr"], L.data[o:o + s["p_filesz"]])
        for base, size in ((STACK - 0x200000, 0x200000), (HEAP, HEAP_SIZE), (STUBS, 0x100000), (TLS, 0x1000),
                           (STOP, 0x1000)):
            uc.mem_map(base, size)
        uc.reg_write(UC_ARM64_REG_TPIDR_EL0, TLS)
        self.heap = HEAP
        self.time_value = 1600000000
        self.clock = 0x0123456789ABC  # CLOCK_MONOTONIC ns for the packet-header scramble
        self.stub_names = {}
        dynsym = L.elf.get_section_by_name(".dynsym")
        slot = 0
        for sec in L.elf.iter_sections():
            if not isinstance(sec, RelocationSection):
                continue
            for r in sec.iter_relocations():
                t, off = r["r_info_type"], r["r_offset"]
                if t == 1027:  # RELATIVE
                    uc.mem_write(off, struct.pack("<Q", r["r_addend"]))
                elif r["r_info_sym"]:
                    sym = dynsym.get_symbol(r["r_info_sym"])
                    if sym["st_value"]:  # defined in the lib itself
                        uc.mem_write(off, struct.pack("<Q", sym["st_value"] + r["r_addend"]))
                    else:
                        a = STUBS + slot * 16
                        slot += 1
                        self.stub_names[a] = sym.name
                        uc.mem_write(off, struct.pack("<Q", a))
        # operator new[]/delete[] are defined in the lib (the engine's allocator, which needs the
        # game's memory manager): intercept them at their entry points too.
        for name in ("_Znammb", "_Znam", "_Znwm", "_ZdaPv", "_ZdlPv", "_ZN4Aska13MemoryManager6MallocEm",
                     "_ZN4Aska6Global25GetAvailableMemoryManagerEv"):
            va = L.by_name.get(name)
            if va:
                self.stub_names[va] = name
                uc.hook_add(UC_HOOK_CODE, self._stub, begin=va, end=va)
        uc.hook_add(UC_HOOK_CODE, self._stub, begin=STUBS, end=STUBS + 0x100000 - 1)
        self.allocs = {}

    # --- memory
    def alloc(self, size, data=b""):
        p = self.heap
        self.heap += (max(size, 1) + 31) & ~15
        if self.heap > HEAP + HEAP_SIZE:
            raise MemoryError("emulated heap exhausted")
        self.uc.mem_write(p, b"\0" * size)
        if data:
            self.uc.mem_write(p, bytes(data))
        self.allocs[p] = size
        return p

    def read(self, p, n):
        return bytes(self.uc.mem_read(p, n))

    def write(self, p, b):
        self.uc.mem_write(p, bytes(b))

    def u64(self, p):
        return struct.unpack("<Q", self.read(p, 8))[0]

    # --- imports
    def _stub(self, uc, addr, size, _):
        name = self.stub_names.get(addr)
        x = [uc.reg_read(UC_ARM64_REG_X0 + i) for i in range(3)]
        if name in ("memcpy", "memmove"):
            uc.mem_write(x[0], bytes(uc.mem_read(x[1], x[2])) if x[2] else b"")
            r = x[0]
        elif name == "memcmp":
            a, b = bytes(uc.mem_read(x[0], x[2])), bytes(uc.mem_read(x[1], x[2]))
            r = 0 if a == b else (1 if a > b else 0xFFFFFFFF)
        elif name == "memset":
            uc.mem_write(x[0], bytes([x[1] & 0xFF]) * x[2])
            r = x[0]
        elif name in ("_Znam", "_Znwm", "_Znammb", "_Znwmmb", "malloc", "_ZnamRKSt9nothrow_t", "_ZnwmRKSt9nothrow_t"):
            r = self.alloc(x[0])
        elif name == "_ZN4Aska13MemoryManager6MallocEm":  # (manager, size)
            r = self.alloc(x[1])
        elif name == "_ZN4Aska6Global25GetAvailableMemoryManagerEv":
            r = 1  # a dummy manager for Malloc above
        elif name in ("_ZdaPv", "_ZdlPv", "free"):
            r = 0
        elif name == "clock_gettime":
            self.clock += 1234567
            uc.mem_write(x[1], struct.pack("<qq", self.clock // 1000000000, self.clock % 1000000000))
            r = 0
        elif name == "time":
            r = self.time_value
            if x[0]:
                uc.mem_write(x[0], struct.pack("<Q", r))
        else:
            raise RuntimeError("unimplemented import %s" % name)
        uc.reg_write(UC_ARM64_REG_X0, r)
        uc.reg_write(UC_ARM64_REG_PC, uc.reg_read(UC_ARM64_REG_LR))

    def call(self, fn, *args, x8=0):
        """AAPCS64 call: integer arguments in x0..x7, the rest in 8-byte stack slots."""
        uc = self.uc
        uc.reg_write(UC_ARM64_REG_X8, x8)
        for i, a in enumerate(args[:8]):
            uc.reg_write(UC_ARM64_REG_X0 + i, a & 0xFFFFFFFFFFFFFFFF)
        sp = STACK - 0x1000
        for i, a in enumerate(args[8:]):
            uc.mem_write(sp + 8 * i, struct.pack("<Q", a & 0xFFFFFFFFFFFFFFFF))
        uc.reg_write(UC_ARM64_REG_SP, sp)
        uc.reg_write(UC_ARM64_REG_LR, STOP)
        uc.emu_start(fn, STOP)
        return uc.reg_read(UC_ARM64_REG_X0), uc.reg_read(UC_ARM64_REG_X1)

    # --- the sqex encryption objects
    def sym(self, name):
        return self.L.by_name[name]

    def new_ninja(self, key, seed=0x5EED1234):
        """A Aska::Cryption::Ninja laid out like TPeer+0x20 (TPeer ctor @015db738): KeyStore (33 bytes)
        at +0, AllocatorForNinja at +0x28, the message RNG at +0x30, SqexEncryptionCreator at +0x428."""
        n = self.alloc(0x460)
        self.write(n + 0x28, struct.pack("<Q", F["alloc_vtable"]))
        self.call(F["rng_seed"], n + 0x30, seed)
        self.call(F["creator_ctor"], n + 0x428, n + 0x28)
        self.write(n, key[:32] + b"\0")
        return n

    def new_creator(self):
        if not hasattr(self, "creator"):
            self.allocator = self.alloc(16, struct.pack("<Q", F["alloc_vtable"]))
            self.creator = self.alloc(0x40)
            self.call(F["creator_ctor"], self.creator, self.allocator)
        return self.creator

    def encrypt(self, alg_id, r2, key, plain):
        """Client encrypt of `plain` with algorithm `alg_id` and parameter r2 -> (envelope, buffer address)."""
        c = self.new_creator()
        k = self.alloc(33, key + b"\0")
        a, _ = self.call(F["create_by_id"], c, alg_id, r2, k)
        if not a:
            raise RuntimeError("no algorithm %#x" % alg_id)
        p = self.alloc(len(plain), plain)
        ptr, x1 = self.call(F["encrypt"], a, p, len(plain))
        self.call(F["destroy"], c, a)
        if x1 >> 32:
            return None, x1 >> 32
        return self.read(ptr, x1 & 0xFFFFFFFF), ptr

    def decrypt(self, key, env):
        """Client decrypt of an envelope -> (plaintext or None, error code)."""
        c = self.new_creator()
        k = self.alloc(33, key + b"\0")
        p = self.alloc(len(env), env)
        a, _ = self.call(F["create_from_envelope"], c, p, len(env), k)
        if not a:
            return None, -1
        ptr, x1 = self.call(F["decrypt"], a, p, len(env))
        self.call(F["destroy"], c, a)
        err = x1 >> 32
        if err or not ptr:
            return None, err
        return self.read(ptr, x1 & 0xFFFFFFFF), 0
