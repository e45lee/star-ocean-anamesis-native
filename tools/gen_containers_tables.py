"""Generate port/src/native/containers/gen/containers_tables.inc from libSOA.so.

The Aska node containers are templates over a node type T: TPoolLegacy<T, false> (a fixed pool of
nodes plus a TBitArray of used slots), TBinaryTree<T> (an unbalanced search tree whose nodes come
from the pool or from operator new), THash<T> (a TBinaryTree per hash bucket) and
TCategorizeHash<T> (a THash whose equal keys chain into categories). Every instantiation of a
method compiles to the same code except for sizeof(T) and the inlined T() constructor. This lists
each T with its node size, its constructor (read from the operator-new path of
TBinaryTree<T>::AllocNode as a list of stores) and the symbols of each method:

  TREE(i, "T", sizeof(T), "vtable TPoolLegacy<T>", "vtable TBinaryTree<T>", "vtable THash<T>",
       "vtable TCategorizeHash<T>")                  ("" when T has no THash / TCategorizeHash)
  CTOR(i, offset, bytes, kind, value, "symbol")     one store of T(): kind 0 = zero, 1 = the
                                                     constant `value`, 2 = &symbol + value,
                                                     3 = the node's own address + value
  CATEGORY(i, offset)                                TCategorizeHash<T>: T's category links
                                                     (previous at offset, next at offset + 8)
  METHOD(i, KIND, "mangled")                         one method of tree i
  POOL(j, "T", sizeof(T), bitarray_call, "vtable TPoolLegacy<T>")   every TPoolLegacy<T, false>
  POOL_METHOD(j, KIND, "mangled")

Usage: .venv/bin/python tools/gen_containers_tables.py > port/src/native/containers/gen/containers_tables.inc
"""
import re
import subprocess

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs
from elftools.elf.relocation import RelocationSection
import genlib  # (before a2c / elfinfo: the default lib is 3.7.0's; tools/genlib.py)
from elfinfo import lib

L = lib()
md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
dyn = {}
for s in L.elf.get_section_by_name(".dynsym").iter_symbols():
    if s.name and s["st_value"]:
        dyn[s.name] = (s["st_value"], s["st_size"])
got = {}
for sec in L.elf.iter_sections():
    if isinstance(sec, RelocationSection):
        symtab = L.elf.get_section(sec["sh_link"])
        for r in sec.iter_relocations():
            if r["r_info_sym"]:
                got[r["r_offset"]] = symtab.get_symbol(r["r_info_sym"]).name

names = sorted(dyn)
dem = dict(zip(names, subprocess.run(["c++filt"], input="\n".join(names), capture_output=True, text=True).stdout.split("\n")))


def insns(sym):
    a, n = dyn[sym]
    return list(md.disasm(L.read(a, n), a))


def call_target(ins):
    if ins.mnemonic in ("bl", "b") and ins.op_str.startswith("#"):
        t = int(ins.op_str[1:], 16)
        return L.plt.get(t) or L.by_addr.get(t)
    return None


def secure_pool_info(sym):
    """(sizeof(T), calls TBitArray::Alloc): evaluates the size computation before the
    operator new[](size, align, bool) call with n = 1 (w1 on entry, copied to another register)."""
    regs = {}
    n_reg = None
    size = None
    bitarray = False
    for ins in insns(sym):
        ops = [o.strip() for o in ins.op_str.split(",")]
        m = ins.mnemonic
        if m == "mov" and ops[1] == "w1" and n_reg is None:
            n_reg = ops[0][1:]
            regs[n_reg] = 1
            continue
        if m == "mov" and ops[1] == "w1" and n_reg is not None:
            pass

        def val(o):
            o = o.strip()
            if o.startswith("#"):
                return int(o[1:], 0)
            r = o[1:]
            return regs.get(r)

        writes = m.startswith("ld") or m in ("mov", "lsl", "lsr", "add", "sub", "mul", "madd", "umaddl", "and", "orr", "csel", "cset", "ubfx", "movk", "neg", "adrp", "eor", "asr", "umulh", "csinv", "adds", "subs")
        dst = ops[0][1:] if writes and ops[0][:1] in "wx" else None
        try:
            if m == "mov" and len(ops) == 2:
                regs[dst] = val(ops[1])
            elif m == "lsl" and len(ops) == 3:
                regs[dst] = val(ops[1]) << val(ops[2])
            elif m == "add" and len(ops) == 4 and ops[3].startswith("lsl"):
                regs[dst] = val(ops[1]) + (val(ops[2]) << int(ops[3].split("#")[1], 0))
            elif m == "add" and len(ops) == 3:
                regs[dst] = val(ops[1]) + val(ops[2])
            elif m == "sub" and len(ops) == 4 and ops[3].startswith("lsl"):
                regs[dst] = val(ops[1]) - (val(ops[2]) << int(ops[3].split("#")[1], 0))
            elif m == "mul":
                regs[dst] = val(ops[1]) * val(ops[2])
            elif dst:
                regs.pop(dst, None)
        except TypeError:
            if dst:
                regs.pop(dst, None)
        t = call_target(ins)
        if t == "_Znammb" and size is None:
            size = regs.get("0")
        if t == "_ZN4Aska9TBitArrayIjLb0EE5AllocEjPKj":
            bitarray = True
    return size, bitarray


def ctor_stores(sym, size):
    """The stores of T() on the operator new(nothrow) path of AllocNode: [(off, bytes, kind, value, sym)]."""
    code = insns(sym)
    i = next(k for k, ins in enumerate(code) if call_target(ins) == "_ZnwmRKSt9nothrow_t")
    node = "x0"
    regs = {"xzr": (0, 0, ""), "wzr": (0, 0, "")}
    page = {}
    out = []
    for ins in code[i + 1:]:
        m, ops = ins.mnemonic, [o.strip() for o in ins.op_str.split(",")]
        if m == "mov" and ops[1] == node and ops[0].startswith("x"):
            node = ops[0]
            continue
        if m in ("cbz", "cbnz"):
            continue
        if m == "ldr" and ops[0].startswith("w") and "#0x8c" in ins.op_str:
            break
        if m == "adrp":
            page[ops[0]] = int(ops[1][1:], 16)
            continue
        if m == "ldr" and len(ops) == 3 and ops[1][1:] in page and ops[1].startswith("["):
            base = page[ops[1][1:]]
            off = int(ops[2].rstrip("]")[1:], 0)
            regs[ops[0]] = (2, 0, got[base + off])
            continue
        if m == "add" and ops[1] in regs and regs[ops[1]][0] == 2 and ops[2].startswith("#"):
            k, v, s = regs[ops[1]]
            regs[ops[0]] = (2, v + int(ops[2][1:], 0), s)
            continue
        if m == "movi":
            regs["q" + ops[0][1:].split(".")[0]] = (0, 0, "")
            regs["q" + ops[0][1:].split(".")[0] + "hi"] = (0, 0, "")
            continue
        if m == "add" and ops[1] == node and ops[2].startswith("#"):  # a pointer into the node
            regs[ops[0]] = (3, int(ops[2][1:], 0), "")
            continue
        if m == "fmov" and ops[0].startswith("d") and ops[1] in regs:
            regs["q" + ops[0][1:]] = regs[ops[1]]
            regs["q" + ops[0][1:] + "hi"] = (0, 0, "")
            continue
        if m == "mov" and re.match(r"v\d+\.d\[1\]$", ops[0]) and ops[1] in regs:
            regs["q" + ops[0][1:].split(".")[0] + "hi"] = regs[ops[1]]
            continue
        if m == "mov" and ops[1].startswith("#"):
            regs[ops[0]] = (1, int(ops[1][1:], 0), "")
            continue
        if m in ("str", "stur", "strh", "strb", "stp"):
            nb = {"str": None, "stur": None, "strh": 2, "strb": 1, "stp": None}[m]
            if m == "stp":
                srcs, mem = ops[:2], ops[2:]
            else:
                srcs, mem = ops[:1], ops[1:]
            if mem[0].rstrip("]") != "[" + node:
                raise ValueError(f"{sym}: unexpected store {ins.mnemonic} {ins.op_str}")
            off = int(mem[1].rstrip("]")[1:], 0) if len(mem) > 1 else 0
            for s in srcs:
                w = nb or {"x": 8, "w": 4, "q": 16}[s[0]]
                key = s if s in regs else ("xzr" if s in ("xzr", "wzr") else s)
                if key not in regs:
                    raise ValueError(f"{sym}: unknown source {s} in {ins.op_str}")
                k, v, sy = regs[key]
                if w == 16:
                    out.append((off, 8) + regs[key])
                    out.append((off + 8, 8) + regs.get(key + "hi", (0, 0, "")))
                else:
                    out.append((off, w, k, v, sy))
                off += w
            continue
        raise ValueError(f"{sym}: unhandled {ins.mnemonic} {ins.op_str}")
    return out


T_RE = re.compile(r"^Aska::(TBinaryTree|THash|TCategorizeHash)<(.+)>::(~?\w+)\((.*)\)( const)?$")
P_RE = re.compile(r"^Aska::TPoolLegacy<(.+), false>::(~?\w+)\((.*)\)$")
trees = {}
pools = {}
for s in names:
    d = dem[s]
    m = T_RE.match(d)
    if m:
        cls, t, meth, args, _ = m.groups()
        if cls == "TBinaryTree" and t.startswith("Aska::TBinaryTree"):
            continue
        kind = {"TBinaryTree": "BT", "THash": "H", "TCategorizeHash": "CH"}[cls]
        name = meth.replace("~", "D")
        if meth.startswith("~"):
            name = "D0" if s.endswith("D0Ev") else "D2" if s.endswith("D2Ev") else "D1"
        if args == "void const*, unsigned int":
            name += "_h"
        elif args.endswith("**)") or args.endswith("**"):
            name += "_node"
        trees.setdefault(t, {})[f"{kind}_{name}"] = s
        continue
    m = P_RE.match(d)
    if m:
        t, meth, args = m.groups()
        name = meth.replace("~", "D")
        if meth.startswith("~"):
            name = "D0" if s.endswith("D0Ev") else "D2"
        pools.setdefault(t, {})[f"P_{name}"] = s

print("// Generated by tools/gen_containers_tables.py from libSOA.so -- do not edit.")
print("// " + genlib.stamp())
sections = {}


def emit(kind, line):
    sections.setdefault(kind, []).append(line)

pool_list = sorted(pools)
sizes = {}
for j, t in enumerate(pool_list):
    sp = pools[t].get("P_SecurePool")
    size, bitarray = secure_pool_info(sp) if sp else (0, False)
    sizes[t] = size
    vt = "_ZTV" + pools[t]["P_D2"][2:].replace("D2Ev", "E")
    emit("POOL", f'POOL({j}, "{t}", {size or 0}, {int(bitarray)}, "{vt}")')
    for k, s in sorted(pools[t].items()):
        emit("POOL_METHOD", f'POOL_METHOD({j}, {k}, "{s}")')

for i, t in enumerate(sorted(trees)):
    ms = trees[t]
    size = sizes.get(t) or 0
    vts = []
    for kind in ("BT", "H", "CH"):
        d2 = ms.get(f"{kind}_D2")
        vts.append("_ZTV" + d2[2:].replace("D2Ev", "E") if d2 else "")
    pvt = "_ZTV" + pools[t]["P_D2"][2:].replace("D2Ev", "E") if t in pools else ""
    emit("TREE", f'TREE({i}, "{t}", {size}, "{pvt}", "{vts[0]}", "{vts[1]}", "{vts[2]}")')
    if "BT_AllocNode" in ms:
        try:
            for off, nb, kind, v, sy in ctor_stores(ms["BT_AllocNode"], size):
                emit("CTOR", f'CTOR({i}, {off:#x}, {nb}, {kind}, {v:#x}, "{sy}")')
        except (ValueError, StopIteration) as e:
            emit("CTOR", f"// no constructor for {t}: {e}")
            ms.pop("BT_AllocNode")
    if "CH_Remove_node" in ms:
        code = insns(ms["CH_Remove_node"])
        nxt = next(int(m.group(1), 0) for ins in code for m in [re.match(r"x9, \[x8, #(0x[0-9a-f]+)\]$", ins.op_str)] if ins.mnemonic == "ldr" and m)
        assert any(ins.mnemonic == "ldp" and ins.op_str == f"x9, x10, [x8, #{nxt - 8:#x}]" for ins in code), t
        emit("CATEGORY", f"CATEGORY({i}, {nxt - 8:#x})")
    for k, s in sorted(ms.items()):
        emit("METHOD", f'METHOD({i}, {k}, "{s}")')
for kind, lines in sections.items():
    print(f"#ifdef {kind}")
    print("\n".join(lines))
    print("#endif")
