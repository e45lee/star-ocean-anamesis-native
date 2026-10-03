"""List the response fields each CParameterManager info class accepts (static, from libSOA.so).

Every InfoBase subclass registers its properties in `<Class>::Initialize()`, naming each one
with `Framework::CHash32::operator=(const char*)` on a string literal. This prints, per class
with an exported Initialize, the literals it hashes, in order; those are the msgpack keys the
class's Deserialize accepts. Child infos are listed by their pParseName (see
port/fakeapi/schema.txt for the live tree).

Usage: tools/fakeapi_fields.py [class-regex]
"""
import bisect
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs  # noqa: E402
from elfinfo import lib  # noqa: E402

L = lib()
md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
pat = re.compile(sys.argv[1]) if len(sys.argv) > 1 else None
addrs = sorted(set(L.addrs))
ident = re.compile(rb"^[A-Za-z_][A-Za-z0-9_]{0,63}$")


def demangle(names):
    out = subprocess.run(["c++filt"], input="\n".join(names), capture_output=True, text=True).stdout.split("\n")
    return dict(zip(names, out))


inits = [(n, a) for n, a in L.by_name.items() if n.endswith("10InitializeEv") and ("Info" in n or "Result" in n)]
dem = demangle([n for n, _ in inits])
rows = []
for n, a in inits:
    cls = dem[n].rsplit("::Initialize", 1)[0]
    if pat and not pat.search(cls):
        continue
    i = bisect.bisect_right(addrs, a)
    end = min(addrs[i] if i < len(addrs) else a + 0x4000, a + 0x4000)
    regs, keys = {}, []
    for ins in md.disasm(L.read(a, end - a), a):
        ops = [x.strip() for x in ins.op_str.split(",")]
        if ins.mnemonic == "adrp":
            regs[ops[0]] = int(ops[1][1:], 16)
        elif ins.mnemonic == "add" and len(ops) == 3 and ops[1] in regs and ops[2].startswith("#"):
            v = regs[ops[1]] + int(ops[2][1:], 16)
            regs[ops[0]] = v
            try:
                s = L.cstr(v, 80)
            except ValueError:
                continue
            if ident.match(s) and s.decode() not in keys:
                keys.append(s.decode())
        elif ins.mnemonic == "ret":
            break
    if keys:
        rows.append((cls, keys))
for cls, keys in sorted(rows):
    print("%s: %s" % (cls, ", ".join(keys)))
