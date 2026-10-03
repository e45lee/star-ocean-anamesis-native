"""Find functions that reference a data/GOT address via an ADRP+LDR/ADD pair.

Usage: xref_got.py <ghidra-addr-or-symbol>...
"""
import os
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from elfinfo import GHIDRA_BASE, lib  # noqa: E402

L = lib()
text = L.elf.get_section_by_name(".text")
base, code = text["sh_addr"], text.data()
words = struct.unpack("<%dI" % (len(code) // 4), code[: len(code) // 4 * 4])


def targets(arg):
    if arg in L.by_name:
        va = L.by_name[arg]
        # Also match the GOT slot that holds this symbol's address.
        slots = [g for g, n in L.got2name.items() if n == arg]
        return [va] + slots
    return [int(arg, 16) - GHIDRA_BASE]


def scan(tvas):
    hits = set()
    pages = {t & ~0xFFF: t for t in tvas}
    for i, w in enumerate(words):
        if w & 0x9F000000 != 0x90000000:
            continue
        pc = base + i * 4
        imm = ((w >> 29) & 3) | (((w >> 5) & 0x7FFFF) << 2)
        if imm & (1 << 20):
            imm -= 1 << 21
        page = (pc & ~0xFFF) + (imm << 12)
        if page not in pages:
            continue
        rd = w & 31
        lo = pages[page] & 0xFFF
        for j in range(1, 8):  # look for the paired LDR/ADD with the low 12 bits
            if i + j >= len(words):
                break
            w2 = words[i + j]
            if w2 & 0xFFC00000 == 0xF9400000 and (w2 >> 5) & 31 == rd and ((w2 >> 10) & 0xFFF) * 8 == lo:
                hits.add(pc); break
            if w2 & 0xFF800000 == 0x91000000 and (w2 >> 5) & 31 == rd and (w2 >> 10) & 0xFFF == lo:
                hits.add(pc); break
    return hits


for arg in sys.argv[1:]:
    hs = scan(targets(arg))
    funcs = sorted({L.name(h).split("+")[0] for h in hs})
    dem = subprocess.run(["c++filt"], input="\n".join(funcs), capture_output=True, text=True).stdout.split("\n")
    print(f"== {arg}: {len(hs)} refs in {len(funcs)} functions")
    for d in dem:
        if d:
            print("  ", d)
