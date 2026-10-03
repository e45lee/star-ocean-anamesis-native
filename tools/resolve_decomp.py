"""Replace Ghidra's func_0xADDR / PTR_...  placeholders with demangled symbol names.

Usage: resolve_decomp.py < in.c > out.c
"""
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from elfinfo import GHIDRA_BASE, lib  # noqa: E402

L = lib()
names = {}


def resolve(m):
    g = int(m.group(1), 16)
    n = L.name(g - GHIDRA_BASE)
    names.setdefault(n, None)
    return "<<" + n + ">>"


src = re.sub(r"func_0x([0-9a-f]+)", resolve, sys.stdin.read())
# Inline short C strings referenced as &UNK_ / &DAT_.
def inline_str(m):
    try:
        s = L.cstr(int(m.group(2), 16) - GHIDRA_BASE, 200)
    except ValueError:
        return m.group(0)
    if s and all(32 <= c < 127 for c in s):
        return m.group(0) + '/*"' + s.decode() + '"*/'
    return m.group(0)
src = re.sub(r"&(UNK|DAT)_([0-9a-f]{8})", inline_str, src)

raw = [n.removeprefix("PLT:").split("+")[0] for n in names]
dem = subprocess.run(["c++filt"], input="\n".join(raw), capture_output=True, text=True).stdout.split("\n")
for n, r, d in zip(names, raw, dem):
    short = re.sub(r"std::__ndk1::basic_string<char, std::__ndk1::char_traits<char>, Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf> >", "string", d)
    src = src.replace("<<" + n + ">>", short + ("" if "+" not in n else "+" + n.split("+")[1]))
sys.stdout.write(src)
