"""Emulate <Class>::Initialize() of InfoBase response classes (unicorn) and print each registered
property: the msgpack key (the string hashed by Framework::CHash32::operator=), the offset of its
CHash32 in the object and the value offset (hash + 0x10), and the store width that resets it.
Calls to other functions are skipped, except base-class Initialize()s, which are followed.

Usage: tools/info_fields_emu.py Class [Class...]   (e.g. CMissionElementInfo CPlanetInfo)
"""
import os
import subprocess
import sys

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs
from unicorn import UC_ARCH_ARM64, UC_HOOK_CODE, UC_HOOK_MEM_UNMAPPED, UC_MODE_ARM, Uc
from unicorn.arm64_const import (UC_ARM64_REG_CPACR_EL1, UC_ARM64_REG_LR, UC_ARM64_REG_PC, UC_ARM64_REG_SP,
                                 UC_ARM64_REG_X0, UC_ARM64_REG_X1)

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from elfinfo import lib  # noqa: E402

L = lib()
md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
STACK, OBJ, STOP, VT = 0x7F000000, 0x60000000, 0x7FFFF000, 0x61000000
names = {a: n for n, a in L.by_name.items()}
hash_eq = L.by_name["_ZN9Framework7CHash32aSEPKc"]


def run(cls):
    uc = Uc(UC_ARCH_ARM64, UC_MODE_ARM)
    uc.reg_write(UC_ARM64_REG_CPACR_EL1, 3 << 20)
    for s in L.segs:
        lo, hi = s["p_vaddr"] & ~0xFFF, (s["p_vaddr"] + s["p_memsz"] + 0xFFF) & ~0xFFF
        uc.mem_map(lo, hi - lo)
        uc.mem_write(s["p_vaddr"], L.data[s["p_offset"]:s["p_offset"] + s["p_filesz"]])
    uc.mem_map(STACK - 0x100000, 0x100000)
    uc.mem_map(OBJ, 0x100000)
    uc.mem_map(VT, 0x1000)
    uc.mem_map(STOP, 0x1000)
    for i in range(0, 0x1000, 8):  # fake vtable: every slot "returns"
        uc.mem_write(VT + i, (STOP + 0x800).to_bytes(8, "little"))
    for i in range(0, 0x10000, 8):
        uc.mem_write(OBJ + i, VT.to_bytes(8, "little"))
    sym = "_ZN%d%s10InitializeEv" % (len(cls), cls)
    entry = L.by_name[sym]
    out = []
    pending = []

    def hook(uc, addr, size, _):
        if addr == STOP + 0x800:  # a skipped virtual call
            uc.reg_write(UC_ARM64_REG_PC, uc.reg_read(UC_ARM64_REG_LR))
            return
        insn = next(md.disasm(bytes(uc.mem_read(addr, 4)), addr))
        if pending and insn.mnemonic.startswith("str") and "[x" in insn.op_str:
            pass
        if insn.mnemonic == "bl":
            tgt = int(insn.op_str.lstrip("#"), 16)
            n = names.get(tgt, "")
            real = L.name(tgt) if hasattr(L, "name") else n
            if tgt == hash_eq or "CHash32aSEPKc" in str(real):
                x0, x1 = uc.reg_read(UC_ARM64_REG_X0), uc.reg_read(UC_ARM64_REG_X1)
                s = bytes(uc.mem_read(x1, 64)).split(b"\0")[0].decode(errors="replace")
                out.append((x0 - OBJ, s))
            elif str(real).split("+")[0].endswith("10InitializeEv") and tgt != entry:
                # follow the base class (resolving a PLT stub to its symbol)
                r = str(real).split("+")[0]
                if r.startswith("PLT:") and r[4:] in L.by_name:
                    uc.reg_write(UC_ARM64_REG_LR, addr + 4)
                    uc.reg_write(UC_ARM64_REG_PC, L.by_name[r[4:]])
                return
            uc.reg_write(UC_ARM64_REG_PC, addr + 4)
        elif insn.mnemonic == "blr":
            uc.reg_write(UC_ARM64_REG_PC, addr + 4)
        elif insn.mnemonic == "b" and not insn.op_str.startswith("#0x" + format(entry, "x")[:3]):
            tgt = int(insn.op_str.lstrip("#"), 16)
            if abs(tgt - addr) > 0x4000:  # tail call
                uc.reg_write(UC_ARM64_REG_PC, uc.reg_read(UC_ARM64_REG_LR))

    uc.hook_add(UC_HOOK_CODE, hook)
    uc.reg_write(UC_ARM64_REG_SP, STACK - 0x1000)
    uc.reg_write(UC_ARM64_REG_X0, OBJ)
    uc.reg_write(UC_ARM64_REG_LR, STOP)
    try:
        uc.emu_start(entry, STOP, count=200000)
    except Exception as e:
        print("  (stopped: %s at %#x)" % (e, uc.reg_read(UC_ARM64_REG_PC)))
    return out


for cls in sys.argv[1:]:
    print(cls)
    for off, s in run(cls):
        print("  %-32s hash @+%#x  value @+%#x" % (s, off, off + 0x10))
