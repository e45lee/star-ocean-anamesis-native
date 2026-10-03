"""List functions that BL to a given symbol (directly or via its PLT stub).

Usage: callers.py <mangled-symbol>...
"""
import os
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from elfinfo import lib  # noqa: E402

L = lib()
text = L.elf.get_section_by_name(".text")
base, code = text["sh_addr"], text.data()
words = struct.unpack("<%dI" % (len(code) // 4), code[: len(code) // 4 * 4])

for sym in sys.argv[1:]:
    tg = {a for a, n in L.plt.items() if n == sym}
    if sym in L.by_name:
        tg.add(L.by_name[sym])
    hits = []
    for i, w in enumerate(words):
        if w & 0xFC000000 == 0x94000000:  # BL
            off = w & 0x3FFFFFF
            if off & (1 << 25):
                off -= 1 << 26
            if base + i * 4 + off * 4 in tg:
                hits.append(base + i * 4)
    funcs = {}
    for h in hits:
        f = L.name(h).split("+")[0]
        funcs[f] = funcs.get(f, 0) + 1
    dem = subprocess.run(["c++filt"], input="\n".join(funcs), capture_output=True, text=True).stdout.split("\n")
    print(f"== {sym}: {len(hits)} calls in {len(funcs)} functions")
    for (f, c), d in zip(funcs.items(), dem):
        print(f"  {c:3d}  {d}")
