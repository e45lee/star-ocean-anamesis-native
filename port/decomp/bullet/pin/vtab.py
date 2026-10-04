#!/usr/bin/env python3
"""vtab.py SYM...: print the game's vtable slots (relocations resolved to symbol names)."""
import sys, subprocess, bisect
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection
import os
L = os.path.join(os.path.abspath(os.path.join(os.path.dirname(__file__), "../../../..")), "work/libSOA-3.7.0.so")
e = ELFFile(open(L, "rb"))
dyn = e.get_section_by_name(".dynsym")
syms = {}; addrs = {}
for s in dyn.iter_symbols():
    if s["st_value"]:
        syms.setdefault(s.name, (s["st_value"], s["st_size"]))
        addrs.setdefault(s["st_value"], s.name)
rel = {}
for sec in e.iter_sections():
    if isinstance(sec, RelocationSection):
        st = e.get_section(sec["sh_link"])
        for r in sec.iter_relocations():
            t = r["r_info_type"]
            if t == 1027:  # RELATIVE
                rel[r["r_offset"]] = addrs.get(r["r_addend"], hex(r["r_addend"]))
            elif r["r_info_sym"]:
                rel[r["r_offset"]] = st.get_symbol(r["r_info_sym"]).name + (f"+{r['r_addend']}" if r["r_addend"] else "")
def dem(n): return subprocess.run(["c++filt", n], capture_output=True, text=True).stdout.strip()
for name in sys.argv[1:]:
    a, sz = syms[name]
    print("==", dem(name), sz)
    for i in range(0, sz, 8):
        print(f"  +{i:3d} {dem(rel.get(a+i, '0'))}")
