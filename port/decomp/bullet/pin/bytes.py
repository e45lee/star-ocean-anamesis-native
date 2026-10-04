#!/usr/bin/env python3
"""bytes.py BUILD_DIR [-v] [--strict]: of the size-equal functions, how many are byte-identical once the
instructions carrying a relocation in the .o are masked (both sides)."""
import glob, sys
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection
import os
G = os.path.join(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../..")), "work/libSOA-3.7.0.so")
LO, HI = 0x261c000, 0x265b000
ge = ELFFile(open(G, "rb"))
gsym = {}
for s in ge.get_section_by_name(".dynsym").iter_symbols():
    if LO <= s["st_value"] < HI and s["st_info"]["type"] == "STT_FUNC": gsym[s.name] = (s["st_value"], s["st_size"])
def gread(a, n):
    for seg in ge.iter_segments():
        if seg["p_type"] == "PT_LOAD" and seg["p_vaddr"] <= a < seg["p_vaddr"] + seg["p_filesz"]:
            seg.stream.seek(seg["p_offset"] + a - seg["p_vaddr"]); return seg.stream.read(n)
LO12 = "--strict" not in sys.argv  # --strict: no :lo12: masking (only B/BL and ADRP)
same = set(); diffs = {}
for o in glob.glob(sys.argv[1] + "/*.o"):
    e = ELFFile(open(o, "rb"))
    rel = {}
    for sec in e.iter_sections():
        if isinstance(sec, RelocationSection) and sec.name.startswith(".rela.text"):
            tgt = sec["sh_info"]
            for r in sec.iter_relocations(): rel.setdefault(tgt, set()).add(r["r_offset"] & ~3)
    st = e.get_section_by_name(".symtab")
    for s in st.iter_symbols():
        if s["st_info"]["type"] != "STT_FUNC" or s.name not in gsym: continue
        ga, gs = gsym[s.name]
        if gs != s["st_size"]: continue
        sec = e.get_section(s["st_shndx"]); data = sec.data()[s["st_value"]: s["st_value"] + gs]
        gd = gread(ga, gs); masks = rel.get(s["st_shndx"], set())
        ok = True; nd = 0
        for i in range(0, gs, 4):
            if s["st_value"] + i in masks: continue
            a, b = data[i:i+4], gd[i:i+4]
            if a != b:
                w = int.from_bytes(a, "little"); v = int.from_bytes(b, "little")
                # local branches inside the same function are pc-relative and identical; others count
                if (w & 0x7C000000) == 0x14000000 and (w >> 26) == (v >> 26): continue   # B/BL
                if (w & 0x9F000000) == 0x90000000 and (w & 0x9F00001F) == (v & 0x9F00001F): continue  # ADRP
                if LO12 and (w & 0x003FFC00) == 0 and (w & ~0x003FFC00) == (v & ~0x003FFC00): continue  # :lo12: imm
                nd += 1
        if nd == 0: same.add(ga)
        else: diffs[ga] = (nd, s.name)
print(f"{sys.argv[1]}: byte-identical {len(same - set(diffs))}, differ {len(diffs)} (unique game functions of the same size)")
if "-v" in sys.argv:
    for nd, n in sorted(diffs.values(), reverse=True)[:40]: print(f"  {nd:4d} {n}")
