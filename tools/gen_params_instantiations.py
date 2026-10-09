#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
r"""Generate port/src/native/params/gen/params_instantiations.inc: the property template instantiations of a
libSOA.so (the params subsystem's natives bind every one; port/src/native/params/README.md).

From the dynamic symbols:
  * CParameterPropertyValue<T, N, Conv>::Deserialize(AMap const*) (T in unsigned, int, float, bool,
    unsigned char, unsigned long; Conv CPropertyConverter or CPropertyConverterRadian) and its vtable;
  * CParameterPropertyString<std::string, N>::Deserialize(AMap const*), CParameterPropertyBase<N>::
    CryptString<std::string> and the string property's vtable.
Each row is checked against the code it binds: the value Deserialize calls the GetValue<T>(map, unsigned)
its T names; CryptString XORs with N & 0xff (an `eor wX, wY, #imm` whose immediate is that); a string
Deserialize calls its own N's CryptString. A row that doesn't fit fails the run (a new code shape needs a
look before it is bound). The differential tests (params/property-*) run every row against the guest.

Usage:
  tools/gen_params_instantiations.py [--lib PATH] [-o OUT]   # default: the 3.7.0 lib, write OUT
  tools/gen_params_instantiations.py --check FILE           # exit 1 if FILE differs (header line not compared)
"""
import argparse
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import genlib  # noqa: E402 (before elfinfo: the default lib)

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs  # noqa: E402

REPO = os.path.dirname(HERE)
DEFAULT_OUT = os.path.join(REPO, "port/src/native/params/gen/params_instantiations.inc")

TYPES = {"j": "u32", "i": "s32", "f": "float", "b": "bool", "h": "u8", "m": "u64"}
STR = "NSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE"
CRYPT_ARG = "INSt6__ndk112basic_stringIcNS2_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS6_22CSTLStringAllocatorInfEEEEEEEvRT_RKSB_"
MAP = "EPKN4Aska4ASON6AValue4AMapE"
RE_VALUE = re.compile(r"^_ZN23CParameterPropertyValueI([jifbhm])Lj(\d+)E(18CPropertyConverter|24CPropertyConverterRadian)E11Deserialize" + MAP + "$")
RE_STRING = re.compile(r"^_ZN24CParameterPropertyStringI" + re.escape(STR) + r"Lj(\d+)EE11Deserialize" + MAP + "$")


def getvalue_sym(t):
    return "_ZN16CParameterParser8GetValueI%sEENSt6__ndk14pairIT_bEEPKN4Aska4ASON6AValue4AMapEj" % t


def crypt_sym(n):
    return "_ZN22CParameterPropertyBaseILj%dEE11CryptString%s" % (n, CRYPT_ARG)


def calls(L, md, va, size):
    """The names of the functions `va` calls (bl), PLT entries resolved."""
    out = []
    for ins in md.disasm(L.read(va, size), va):
        if ins.mnemonic == "bl":
            out.append(L.name(int(ins.op_str.lstrip("#"), 16)).replace("PLT:", ""))
    return out


def xor_keys(L, md, va, size):
    """The byte keys of the eor instructions in `va`: an immediate (its low byte: `eor w, w, #0xffffff80`
    is ^ 0x80 on a byte), or a register a `mov w, #imm` set."""
    movs, keys = {}, []
    for ins in md.disasm(L.read(va, size), va):
        ops = [o.strip() for o in ins.op_str.split(",")]
        if ins.mnemonic == "mov" and len(ops) == 2 and ops[1].startswith("#"):
            movs[ops[0]] = int(ops[1][1:], 0)
        elif ins.mnemonic == "eor" and len(ops) == 3:
            if ops[2].startswith("#"):
                keys.append(int(ops[2][1:], 0) & 0xff)
            elif ops[2] in movs:
                keys.append(movs[ops[2]] & 0xff)
            else:
                keys.append(None)
    return keys


def generate(lib_path):
    from elfinfo import Lib
    L = Lib(lib_path)
    md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
    sizes = {}
    for sec in (".dynsym",):
        for s in L.elf.get_section_by_name(sec).iter_symbols():
            if s.name and s["st_value"]:
                sizes[s.name] = s["st_size"]
    values, strings, errors = [], [], []
    for name in sorted(L.by_name):
        m = RE_VALUE.match(name)
        if m:
            t, n, conv = m.group(1), int(m.group(2)), m.group(3)
            va = L.by_name[name]
            called = calls(L, md, va, sizes[name])
            if called != [getvalue_sym(t)]:
                errors.append("%s calls %s" % (name, called))
            ztv = "_ZTV23CParameterPropertyValueI%sLj%dE%sE" % (t, n, conv)
            if ztv not in L.by_name:
                errors.append("no vtable " + ztv)
            values.append((TYPES[t], n, re.sub(r"^\d+", "", conv), name, ztv, va))
            continue
        m = RE_STRING.match(name)
        if m:
            n = int(m.group(1))
            va = L.by_name[name]
            crypt = crypt_sym(n)
            if crypt not in L.by_name:
                errors.append("no CryptString for %d" % n)
                continue
            called = calls(L, md, va, sizes[name])
            if crypt not in called and not any(c.startswith(crypt) for c in called):
                errors.append("%s calls %s" % (name, called))
            imms = xor_keys(L, md, L.by_name[crypt], sizes[crypt])
            if imms != [n & 0xff]:
                errors.append("%s: xor keys %s, expected [%#x]" % (crypt, imms, n & 0xff))
            ztv = "_ZTV24CParameterPropertyStringI%sLj%dEE" % (STR, n)
            if ztv not in L.by_name:
                errors.append("no vtable " + ztv)
            strings.append((n, name, crypt, ztv, va))
    if errors:
        sys.exit("gen_params_instantiations: rows that don't fit:\n  " + "\n  ".join(errors[:40]))
    values.sort(key=lambda r: r[5])
    strings.sort(key=lambda r: r[4])
    out = ["// Generated by tools/gen_params_instantiations.py (the property template instantiations); do not edit.",
           "// " + genlib.stamp(lib_path),
           "// PARAMS_VALUE(T, N, Conv, Deserialize symbol, vtable symbol): CParameterPropertyValue<T, N, Conv>, %d rows." % len(values),
           "// PARAMS_STRING(N, Deserialize symbol, CryptString symbol, vtable symbol): CParameterPropertyString<std::string, N>",
           "// and CParameterPropertyBase<N>::CryptString, %d rows. In code-address order." % len(strings),
           "#define PARAMS_VALUES(X) \\"]
    for t, n, conv, name, ztv, _ in values:
        out.append('    X(%s, %d, %s, "%s", "%s") \\' % (t, n, conv, name, ztv))
    out.append("    /* end of PARAMS_VALUES */")
    out.append("")
    out.append("#define PARAMS_STRINGS(X) \\")
    for n, name, crypt, ztv, _ in strings:
        out.append('    X(%d, "%s", "%s", "%s") \\' % (n, name, crypt, ztv))
    out.append("    /* end of PARAMS_STRINGS */")
    out.append("")
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lib", default=genlib.lib_path())
    ap.add_argument("-o", "--out", default=DEFAULT_OUT)
    ap.add_argument("--check", metavar="FILE")
    a = ap.parse_args()
    text = generate(a.lib)
    if a.check:
        have = open(a.check).read().split("\n")
        want = text.split("\n")
        if have[2:] != want[2:]:
            sys.exit("%s differs from the generator's output for %s" % (a.check, a.lib))
        return
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    with open(a.out, "w") as f:
        f.write(text)
    print("%s written" % os.path.relpath(a.out, REPO))


if __name__ == "__main__":
    main()
