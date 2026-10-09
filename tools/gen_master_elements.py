#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
r"""Generate port/src/native/master/gen/master_elements.h: the master tables' element classes (the T of
CMasterParameterBaseSqlite_Simple<T> / _Category<T>, 166 in 3.7.0) as recovered layouts, one row per
property, for the master subsystem's natives (port/src/native/master/README.md "Elements").

An element is a CParameterElementBase (0x10) followed by its properties, each a
CParameterPropertyValue<T, N, Conv> (0x30) or CParameterPropertyString<std::string, N> (0x40)
(params_layout.h). Its default constructor is inlined into the templates, so the layout is read from
the code in three independent ways that must agree:
  1. the constructor's stores (static, capstone): in DeserializeMsgPack<T> (or the exported C2
     constructor, or DeserializeParameter), the element's vtable store and then each property's final
     vtable store, up to the call of T::Initialize: offset, value/string, T, N, Conv;
  2. the destructor (D2, exported for every element), run under unicorn on an element built from (1):
     it must put back CParameterPropertyBase<N>'s vtable at each property (a string property's
     CParameterPropertyString<N> first) and call ~CHash32 once per property;
  3. T::Initialize, run under unicorn on an element built from (1) whose value bytes are 0xcc: the
     properties it names (CHash32::operator=(char const*) on each m_name: the key), sets m_named and
     links (AddProperty, in its order), and the default each value property gets (the bytes written
     at +0x28, as many as sizeof(T)). Nothing else may be written.
When the exported C2 constructor exists it is also run and must leave exactly what (1) says (and the
CHash32() of each m_name). An element that doesn't fit fails the run: a new code shape needs a look.

Usage:
  tools/gen_master_elements.py [--lib PATH] [-o OUT]   # default: the 3.7.0 lib, write OUT
  tools/gen_master_elements.py --check FILE            # exit 1 if FILE differs (header line not compared)
  tools/gen_master_elements.py --dump CLASS            # print one element's rows
"""
import argparse
import os
import re
import struct
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import genlib  # noqa: E402 (before elfinfo: the default lib)

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs  # noqa: E402
from capstone.arm64 import ARM64_OP_IMM, ARM64_OP_MEM, ARM64_OP_REG, ARM64_REG_SP, ARM64_REG_X0, ARM64_REG_X18, ARM64_REG_X30  # noqa: E402
from unicorn import UC_HOOK_MEM_WRITE  # noqa: E402

REPO = os.path.dirname(HERE)
DEFAULT_OUT = os.path.join(REPO, "port/src/native/master/gen/master_elements.h")

STR = "NSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE"
RE_VALUE_VT = re.compile(r"^_ZTV23CParameterPropertyValueI([jifbhm])Lj(\d+)E(18CPropertyConverter|24CPropertyConverterRadian)E$")
RE_STRING_VT = re.compile(r"^_ZTV24CParameterPropertyStringI" + re.escape(STR) + r"Lj(\d+)EE$")
RE_BASE_VT = re.compile(r"^_ZTV22CParameterPropertyBaseILj(\d+)EE$")
TYPES = {"j": ("u32", 4), "i": ("s32", 4), "f": ("float", 4), "b": ("bool", 1), "h": ("u8", 1), "m": ("u64", 8)}
RE_TEMPLATE = re.compile(r"^_ZNK?\d+CMasterParameterBaseSqlite_(Simple|Category)I(\d+)")

SYM_ALLOCATE = "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj"
SYM_FREE = "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv"
SYM_ADDPROP = "_ZN21CParameterElementBase11AddPropertyEP18IParameterProperty"
SYM_HASH_ASSIGN = "_ZN9Framework7CHash32aSEPKc"
SYM_HASH_D1 = "_ZN9Framework7CHash32D1Ev"
SYM_HASH_C1 = "_ZN9Framework7CHash32C1Ev"
SYM_ELEMBASE_VT = "_ZTV21CParameterElementBase"
SYM_HASH_VT = "_ZTVN9Framework7CHash32E"


class Fail(Exception):
    pass


def mangled(cls):
    return "%d%s" % (len(cls), cls)


def element_classes(L):
    """The element classes: T of every CMasterParameterBaseSqlite_Simple<T> / _Category<T> symbol."""
    out = {}
    for name in L.by_name:
        m = RE_TEMPLATE.match(name)
        if m:
            n = int(m.group(2))
            i = m.end(2)
            cls = name[i:i + n]
            out.setdefault(cls, set()).add(m.group(1))
    return out


class Scanner:
    """Linear register tracking over one function: where vtable addresses (a GOT slot's symbol + 0x10) are
    stored, relative to the stack or to x0 at entry."""

    def __init__(self, L, md):
        self.L, self.md = L, md

    def stores(self, va, size, stop_calls):
        L = self.L
        regs = {ARM64_REG_X0: ("arg0", 0)}
        out = []  # (key, offset, symbol, addend)
        for ins in self.md.disasm(L.read(va, size), va):
            ops = ins.operands
            mn = ins.mnemonic
            if mn == "bl":
                target = L.name(ops[0].imm).replace("PLT:", "")
                if target in stop_calls:
                    return out, True
                for r in list(regs):
                    if ARM64_REG_X0 <= r <= ARM64_REG_X18 or r == ARM64_REG_X30:
                        del regs[r]
                continue
            if mn == "adrp":
                regs[ops[0].reg] = ("page", ops[1].imm)
                continue
            if mn == "ldr" and len(ops) == 2 and ops[1].type == ARM64_OP_MEM and regs.get(ops[1].mem.base, ("",))[0] == "page":
                slot = regs[ops[1].mem.base][1] + ops[1].mem.disp
                regs[ops[0].reg] = ("got", L.got2name.get(slot))
                continue
            if mn == "add" and len(ops) == 3 and ops[2].type == ARM64_OP_IMM:
                src = ARM64_REG_SP if ops[1].reg == ARM64_REG_SP else ops[1].reg
                v = ("sp", 0) if src == ARM64_REG_SP else regs.get(src)
                if v and v[0] == "got" and v[1]:
                    regs[ops[0].reg] = ("sym", v[1], ops[2].imm)
                elif v and v[0] in ("sp", "arg0"):
                    regs[ops[0].reg] = (v[0], v[1] + ops[2].imm)
                else:
                    regs.pop(ops[0].reg, None)
                continue
            if mn == "mov" and len(ops) == 2 and ops[1].type == ARM64_OP_REG:
                if ops[1].reg == ARM64_REG_SP:
                    regs[ops[0].reg] = ("sp", 0)
                elif ops[1].reg in regs:
                    regs[ops[0].reg] = regs[ops[1].reg]
                else:
                    regs.pop(ops[0].reg, None)
                continue
            if mn in ("str", "stur", "stp"):
                mem = ops[-1].mem
                base = ("sp", 0) if mem.base == ARM64_REG_SP else regs.get(mem.base)
                vals = ops[:-1]
                for k, o in enumerate(vals):
                    v = regs.get(o.reg)
                    if base and base[0] in ("sp", "arg0") and v and v[0] == "sym":
                        out.append((base[0], base[1] + mem.disp + 8 * k, v[1], v[2]))
                if ins.writeback and mem.base != ARM64_REG_SP:
                    regs.pop(mem.base, None)
                continue
            # anything else that writes a register forgets it
            try:
                _, written = ins.regs_access()
            except Exception:
                written = []
            for r in written:
                regs.pop(r, None)
        return out, False


def parse_prop_vt(sym):
    m = RE_VALUE_VT.match(sym)
    if m:
        t, n, conv = m.group(1), int(m.group(2)), m.group(3)
        return ("value", TYPES[t][0], n, "CPropertyConverterRadian" if "Radian" in conv else "CPropertyConverter")
    m = RE_STRING_VT.match(sym)
    if m:
        return ("string", None, int(m.group(1)), None)
    m = RE_BASE_VT.match(sym)
    if m:
        return ("base", None, int(m.group(1)), None)
    return None


def ctor_shape(L, sc, cls, sizes):
    """[(offset, kind, T, N, Conv, vtable symbol)] from the first function whose inlined (or own) default
    constructor stores the element's vtable and then its properties' before calling T::Initialize."""
    m = mangled(cls)
    elem_vt = "_ZTV" + m
    init = "_ZN%s10InitializeEv" % m
    cands = [k for k in L.by_name if k.startswith("_ZNK26CMasterParameterBaseSqlite18DeserializeMsgPackI" + m + "E")]
    cands += ["_ZN%sC2Ev" % m]
    cands += [k for k in L.by_name if k.startswith("_ZN33CMasterParameterBaseSqlite_SimpleI" + m + "E20DeserializeParameter")]
    cands += [k for k in L.by_name if k.startswith("_ZN35CMasterParameterBaseSqlite_CategoryI" + m + "E20DeserializeParameter")]
    tried = []
    for c in cands:
        if c not in L.by_name:
            continue
        stores, stopped = sc.stores(L.by_name[c], sizes[c], {init})
        tried.append(c)
        # The element's vtable store whose properties follow it from +0x10 (other stores of the same
        # values are register spills).
        for key, e in [(k, o) for k, o, s, a in stores if s == elem_vt and a == 16]:
            final = {}
            for k, o, s, a in stores:
                if k == key and o > e and a == 16 and parse_prop_vt(s):
                    final[o - e] = s
            props, at = [], 0x10
            while at in final:
                p = parse_prop_vt(final[at])
                if p[0] == "base":
                    break
                props.append((at,) + p + (final[at],))
                at += 0x30 if p[0] == "value" else 0x40
            if props and (at not in final):
                return props, c
    raise Fail("%s: no constructor shape in %s" % (cls, tried))


class Runner:
    def __init__(self, L):
        import uemu
        self.L = L
        self.E = E = uemu.Emu(L)
        S = L.by_name
        self.names, self.adds, self.frees, self.hash_dtors, self.allocs = [], [], [], [], []
        E.hook_addr(S[SYM_ALLOCATE], self._allocate)
        E.hook_addr(S[SYM_FREE], lambda e: self.frees.append(e.x(0)))
        E.hook_addr(S[SYM_ADDPROP], lambda e: self.adds.append(e.x(1) - e.x(0)))
        E.hook_addr(S[SYM_HASH_ASSIGN], lambda e: (self.names.append((e.x(0), e.cstr(e.x(1)))), e.x(0))[1])
        E.hook_addr(S[SYM_HASH_D1], lambda e: self.hash_dtors.append(e.x(0)))
        E.hook_import("strlen", lambda e: len(e.cstr(e.x(0))))
        self.writes = []
        E.uc.hook_add(UC_HOOK_MEM_WRITE, self._on_write)
        self.watch = None

    def _allocate(self, e):
        p = e.alloc(e.x(0), 0xEE)
        self.allocs.append((e.x(0), p))
        return p

    def _on_write(self, uc, access, addr, size, value, _):
        if self.watch and self.watch[0] <= addr < self.watch[1]:
            self.writes.append((addr - self.watch[0], size, value & ((1 << (8 * size)) - 1)))

    def vt(self, sym):
        return self.L.by_name[sym] + 16

    def build(self, cls, props, size, fill):
        """An element as the default constructor leaves it (values: `fill`)."""
        E = self.E
        buf = E.alloc(size, fill)
        E.uc.mem_write(buf, struct.pack("<QQ", self.vt("_ZTV" + mangled(cls)), 0))
        for off, kind, t, n, conv, vt in props:
            # vtable, m_next, m_named (+ padding as the ctor leaves it: untouched), CHash32 (vtable, 0)
            E.uc.mem_write(buf + off, struct.pack("<QQ", self.vt(vt), 0))
            E.uc.mem_write(buf + off + 0x10, b"\0")
            E.uc.mem_write(buf + off + 0x18, struct.pack("<QI", self.vt(SYM_HASH_VT), 0))
            if kind == "string":
                E.uc.mem_write(buf + off + 0x28, b"\0" * 24)
        return buf

    def run(self, sym, *args, watch=None):
        for v in (self.names, self.adds, self.frees, self.hash_dtors, self.writes, self.allocs):
            v.clear()
        self.watch = watch
        try:
            self.E.call(self.L.by_name[sym], *args)
        finally:
            self.watch = None


def element(L, R, sc, sizes, cls):
    props, src = ctor_shape(L, sc, cls, sizes)
    last = props[-1]
    size = last[0] + (0x30 if last[1] == "value" else 0x40)
    m = mangled(cls)
    E = R.E

    # 2. the destructor
    buf = R.build(cls, props, size, 0)
    R.run("_ZN%sD2Ev" % m, buf, watch=(buf, buf + size))
    vt_writes = {}
    for off, sz, v in R.writes:
        if sz == 8:
            vt_writes.setdefault(off, []).append(L.name(v - 16) if v >= 16 else "?")
    for off, kind, t, n, conv, vt in props:
        got = vt_writes.get(off, [])
        want = (["_ZTV24CParameterPropertyStringI%sLj%dEE" % (STR, n)] if kind == "string" else []) + ["_ZTV22CParameterPropertyBaseILj%dEE" % n]
        if got != want:
            raise Fail("%s: ~%s at +%#x writes %s, expected %s" % (cls, cls, off, got, want))
    if sorted(h - buf for h in R.hash_dtors) != sorted(p[0] + 0x18 for p in props):
        raise Fail("%s: ~%s destroys the hashes at %s" % (cls, cls, [hex(h - buf) for h in R.hash_dtors]))
    if R.frees:
        raise Fail("%s: ~%s frees %s on an empty element" % (cls, cls, R.frees))

    # 3. Initialize
    buf = R.build(cls, props, size, 0xCC)
    before = R.E.read(buf, size)
    R.run("_ZN%s10InitializeEv" % m, buf, watch=(buf, buf + size))
    after = R.E.read(buf, size)
    named = {a - buf - 0x18: n.decode("utf-8") for a, n in R.names}
    # a key of 23 bytes or more is a long std::string: allocated ((n + 16) & ~15) and freed around its use
    want = [(len(n) + 16) & ~15 for _, n in R.names if len(n) >= 23]
    if [a for a, _ in R.allocs] != want or sorted(R.frees) != sorted(p for _, p in R.allocs):
        raise Fail("%s: Initialize allocates %s and frees %d, the long keys need %s" % (cls, R.allocs, len(R.frees), want))
    order = list(R.adds)
    by_off = {p[0]: p for p in props}
    # (some elements declare a property their Initialize never names nor links: a game quirk, kept)
    if not set(order) <= set(by_off) or len(set(order)) != len(order) or sorted(named) != sorted(order):
        raise Fail("%s: Initialize adds %s and names %s, the properties are at %s" % (
            cls, [hex(o) for o in order], [hex(o) for o in named], [hex(o) for o in by_off]))
    rows = []
    allowed = set()
    for off, kind, t, n, conv, vt in props:
        default = None
        if off not in order:
            rows.append(dict(off=off, kind=kind, t=t, n=n, conv=conv, vt=vt, name=None, default=None))
            continue
        allowed.add(off + 0x10)
        if kind == "value":
            w = TYPES[[k for k, v in TYPES.items() if v[0] == t][0]][1]
            region = after[off + 0x28:off + 0x30]
            changed = [i for i in range(8) if region[i] != 0xCC]
            if changed and max(changed) >= w:
                raise Fail("%s: Initialize writes %d bytes of the %s at +%#x" % (cls, max(changed) + 1, t, off))
            default = region[:w] if changed else None
            for i in range(w):
                allowed.add(off + 0x28 + i)
        if after[off + 0x10] != 1:
            raise Fail("%s: Initialize leaves m_named %d at +%#x" % (cls, after[off + 0x10], off))
        rows.append(dict(off=off, kind=kind, t=t, n=n, conv=conv, vt=vt, name=named[off], default=default))
    for i in range(size):
        if before[i] != after[i] and i not in allowed:
            raise Fail("%s: Initialize writes +%#x (%02x -> %02x), not a property's flag or value" % (cls, i, before[i], after[i]))
    for r in rows:
        r["index"] = order.index(r["off"]) if r["off"] in order else -1

    # the exported default constructor, when there is one
    c2 = "_ZN%sC2Ev" % m
    if c2 in L.by_name:
        buf = E.alloc(size, 0xCC)
        R.run(c2, buf)
        got = R.E.read(buf, size)
        want = bytearray(R.E.read(R.build(cls, props, size, 0xCC), size))
        if bytes(got) != bytes(want):
            diff = [i for i in range(size) if got[i] != want[i]]
            raise Fail("%s: the C2 constructor differs from the shape at %s" % (cls, [hex(i) for i in diff[:8]]))
    return dict(cls=cls, size=size, src=src, props=rows)


# Elements whose layout the three readings can't establish: left to the guest (their constructor isn't
# straight-line code the scan reads). A new entry needs a look at the code first.
UNFIT = {
    "CMasterParameterHome3DMapElement": "constructed only in a local function (DeserializeParameter's allocate_shared)",
    "CMasterParameterLanguageElement": "constructed only in a local function (DeserializeParameter's allocate_shared)",
    "CMasterParameterRoleDuplicationItemElement": "constructed only in a local function (DeserializeParameter's allocate_shared)",
    "CMasterSphere211FloorAssetBoxElement": "constructed only in a local function (DeserializeParameter's allocate_shared)",
    "CMasterSphere211OverwriteEnemyLevelElement": "constructed only in a local function (DeserializeParameter's allocate_shared)",
    "CMasterParameterWorldMapMissionElement": "0x10..0xd80 is built by a loop (an array of properties), not read by the scan",
}

KINDS = {"u32": "kU32", "s32": "kS32", "float": "kFloat", "bool": "kBool", "u8": "kU8", "u64": "kU64"}


def methods(L, cls):
    """The element's exported methods: (role, symbol); an alias of an earlier symbol's address is left out."""
    m = mangled(cls)
    seen, out = set(), []
    for role, sym in (("Initialize", "_ZN%s10InitializeEv" % m), ("Ctor", "_ZN%sC2Ev" % m), ("Ctor", "_ZN%sC1Ev" % m),
                      ("CtorCopy", "_ZN%sC2ERKS_" % m), ("CtorCopy", "_ZN%sC1ERKS_" % m), ("Assign", "_ZN%saSERKS_" % m),
                      ("Dtor", "_ZN%sD2Ev" % m), ("Dtor", "_ZN%sD1Ev" % m), ("DtorDelete", "_ZN%sD0Ev" % m)):
        a = L.by_name.get(sym)
        if a and a not in seen:
            seen.add(a)
            out.append((role, sym))
    return out


# CMasterParameterBaseSqlite_Simple<T>'s methods the natives bind (master_simple.h), by symbol suffix
# after "_ZN[K]33CMasterParameterBaseSqlite_SimpleI<T>E".
SIMPLE_SUFFIXES = {
    "18pParameterFromHashEj": "pParameterFromHash",
    "16ParameterByQueryEPKcPN4Aska5Yayoi10QueryParamEj": "ParameterByQuery",
    "16ParameterByQueryEPKcRN9Framework16CSTLUnorderedMapIjS0_NSt6__ndk14hashIjEENS6_8equal_toIjEEEEPN4Aska5Yayoi10QueryParamEj":
        "ParameterByQueryMap",
    "12MakeCacheKeyEPKcPN4Aska5Yayoi10QueryParamEj": "MakeCacheKey",
    "20InsertCustomizeCacheEjRKNSt6__ndk110shared_ptrIS0_EE": "InsertCustomizeCache",
    "10ClearCacheEv": "ClearCache",
    "20SetStoreAllCacheSizeEv": "SetStoreAllCacheSize",
    "10InitializeEv": "Initialize",
    "D2Ev": "Dtor",
    "D1Ev": "Dtor",
    "11DeserializeEPKN4Aska4ASON6AValue4AMapE": "Deserialize",
    "16ReleaseParameterEPKc": "ReleaseParameter",
    "20DeserializeParameterERN9Framework16CSTLUnorderedMapIjNSt6__ndk110shared_ptrIS0_EENS4_4hashIjEENS4_8equal_toIjEEEEPKN4Aska4ASON6AValue6AArrayE":
        "DeserializeParameter",
}
MSGPACK = ("_ZNK26CMasterParameterBaseSqlite18DeserializeMsgPackI%sEEvRKN4Aska12TSharedArrayIaEERKlPT_PN9Framework16CSTLUnorderedMap"
           "IjS9_NSt6__ndk14hashIjEENSD_8equal_toIjEEEE")
ALLOC_CALLS = {SYM_ALLOCATE: "Allocate", "_Znwm": "new", "_ZnwmRKSt9nothrow_t": "new(nothrow)"}


def alloc_sizes(L, md, va, size):
    """The constant sizes the function passes to the allocators: {"Allocate": {n...}, "new": ...} (a size not
    set by a mov right before the call isn't listed)."""
    out, last = {}, {}
    for ins in md.disasm(L.read(va, size), va):
        ops = ins.op_str.split(", ")
        if ins.mnemonic == "mov" and len(ops) == 2 and ops[0] in ("w0", "x0") and ops[1].startswith("#"):
            last = {"x0": int(ops[1][1:], 0)}
            continue
        if ins.mnemonic == "bl":
            t = L.name(int(ins.op_str.lstrip("#"), 16)).replace("PLT:", "")
            if t in ALLOC_CALLS and "x0" in last:
                out.setdefault(ALLOC_CALLS[t], set()).add(last["x0"])
            last = {}
        elif ops and ops[0] in ("w0", "x0"):
            last = {}
    return out


def table_methods(L, md, sizes, e):
    """The table's (role, symbol) rows, each checked: the allocation sizes its code passes are the
    element's (a node of 0x18 + size, a shared_ptr block of 0x18 + size, the element itself)."""
    m = mangled(e["cls"])
    rows, seen = [], set()
    for k in ("_ZN33", "_ZNK33"):
        prefix = k + "CMasterParameterBaseSqlite_SimpleI" + m + "E"
        for suffix, role in SIMPLE_SUFFIXES.items():
            sym = prefix + suffix
            a = L.by_name.get(sym)
            if a and a not in seen:
                if role == "Dtor" and ("_ZTV33CMasterParameterBaseSqlite_SimpleI" + m + "E") not in L.by_name:
                    continue  # (the destructor writes the vtable back: bound only when the symbol is there)
                seen.add(a)
                rows.append((role, sym))
    sym = MSGPACK % m
    if sym in L.by_name:
        rows.append(("DeserializeMsgPack", sym))
    n = e["size"]
    want = {"DeserializeMsgPack": {"Allocate": {0x18 + n}}, "pParameterFromHash": {"new": {0x18 + n}, "Allocate": {0x28}},
            "DeserializeParameter": {"new": {0x18 + n}, "Allocate": {0x28}},
            "ParameterByQuery": {"new(nothrow)": {n}, "new": {0x20}}, "InsertCustomizeCache": {"Allocate": {0x28}}}
    for role, sym in rows:
        if role not in want:
            continue
        got = alloc_sizes(L, md, L.by_name[sym], sizes[sym])
        for kind, ns in want[role].items():
            if got.get(kind, ns) != ns:
                raise Fail("%s: %s allocates %s %s, expected %s" % (e["cls"], role, kind, sorted(got[kind]), sorted(ns)))
    return rows


# ---- the connectors (CSimpleSqliteConnector<Table, Entity>) ----

CONN_METHODS = {
    "QueryToMsgPack(unsigned int, unsigned int, Aska::TSharedArray<signed char>&, long&)": "msgpack_id",
    "QueryToMsgPack(char const*, Aska::TSharedArray<signed char>&, long&, Aska::Yayoi::QueryParam*, unsigned int)": "msgpack_sql",
    "QueryToResultObject(unsigned int, Aska::Yayoi::QueryParam*, unsigned int, Aska::Yayoi::TEntityObject<Aska::Yayoi::SQLiteDriver>&)":
        "result_id",
    "QueryToResultObject(char const*, Aska::Yayoi::QueryParam*, unsigned int, Aska::Yayoi::TEntityObject<Aska::Yayoi::SQLiteDriver>&)":
        "result_sql",
}


def split_class(dem):
    """'CSimpleSqliteConnector<...>::rest' -> (class, rest), the template's brackets balanced."""
    d = 0
    for i, ch in enumerate(dem):
        if ch == "<":
            d += 1
        elif ch == ">":
            d -= 1
            if d == 0:
                return dem[:i + 1], dem[i + 3:]
    return None, None


def normalized(L, md, va, size, keep_cmp=False):
    """The code with its addresses taken out (branch targets as names, page / GOT offsets dropped): two
    instantiations of one template compare equal unless their code differs."""
    out = []
    for ins in md.disasm(L.read(va, size), va):
        op = ins.op_str
        if ins.mnemonic in ("bl", "b") or ins.mnemonic.startswith("b.") or ins.mnemonic in ("cbz", "cbnz", "tbz", "tbnz"):
            t = int(op.split("#")[-1], 16)
            op = op.rsplit("#", 1)[0] + ("+%d" % (t - va) if va <= t < va + size else "<call>")
        elif ins.mnemonic == "adrp":
            op = op.split(",")[0]
        elif ins.mnemonic in ("ldr", "add") and ("#0x" in op) and not keep_cmp:
            op = re.sub(r"#0x[0-9a-f]+\]", "#imm]", op)
            if ins.mnemonic == "add":
                op = re.sub(r"#0x[0-9a-f]+$", "#imm", op)
        elif ins.mnemonic == "cmp" and not keep_cmp:
            op = re.sub(r"#0x[0-9a-f]+|#\d+", "#n", op)
        out.append(ins.mnemonic + " " + op)
    return out


# Connectors whose code isn't the common shape (a key list or query table of their own): left to the guest.
UNFIT_CONNECTORS = {"MasterDB::CCommonDrop", "MasterDB::CEventMission", "MasterDB::CMasterDeepSpaceMission", "MasterDB::CTitle",
                    "MasterDB::CWeaponLimitBreak"}


def connector_table(cls):
    return cls[len("CSimpleSqliteConnector<"):].split(",")[0]


def connectors(L, md, sizes):
    """Every connector class: its four query methods (each the same code as every other's, but for
    the addresses and the query count), its vtable, its queries / keys statics, BuildQuery<CLocalEntity>,
    the query count (QueryToResultObject's `cmp w, #count - 1`)."""
    names = sorted(n for n in L.by_name if "22CSimpleSqliteConnector" in n)
    dem = subprocess.run(["c++filt"], input="\n".join(names), capture_output=True, text=True).stdout.split("\n")
    by_class = {}
    for n, d in zip(names, dem):
        if d.startswith("vtable for CSimpleSqliteConnector<"):
            cls = d[len("vtable for "):]
            if "CLocalEntity" not in cls:
                by_class.setdefault(cls, {})["vtable"] = n
            continue
        if not d.startswith("CSimpleSqliteConnector<"):
            continue
        cls, rest = split_class(d)
        if rest in CONN_METHODS:
            by_class.setdefault(cls, {})[CONN_METHODS[rest]] = n
        elif rest.endswith("::GetQuery(int) const::queries"):
            by_class.setdefault(cls, {})["queries"] = n
        elif rest.endswith("::GetPrimaryKeies() const::keies"):
            by_class.setdefault(cls, {})["keies"] = n
    rows, errors, ref = [], [], {}
    for cls in sorted(by_class):
        r = by_class[cls]
        if not all(k in r for k in ("vtable", "queries", "keies", "msgpack_id", "msgpack_sql", "result_id", "result_sql")):
            errors.append("%s: missing %s" % (cls, sorted(k for k in ("vtable", "queries", "keies", "msgpack_id", "msgpack_sql",
                                                                         "result_id", "result_sql") if k not in r)))
            continue
        # the query count and BuildQuery from QueryToResultObject(unsigned)
        va = L.by_name[r["result_id"]]
        nq, bq = None, None
        for ins in md.disasm(L.read(va, sizes[r["result_id"]]), va):
            if ins.mnemonic == "cmp" and nq is None:
                nq = int(ins.op_str.split("#")[-1], 0) + 1
            if ins.mnemonic == "bl":
                t = L.name(int(ins.op_str.lstrip("#"), 16)).replace("PLT:", "")
                if "10BuildQuery" in t:
                    bq = t
        if nq is None or bq is None:
            errors.append("%s: no query count / BuildQuery" % cls)
            continue
        r["count"], r["build_query"] = nq, bq
        # the same code as the others' (and the statics it loads are its own)
        for k in ("msgpack_id", "msgpack_sql", "result_id", "result_sql"):
            code = normalized(L, md, L.by_name[r[k]], sizes[r[k]])
            if k not in ref:
                ref[k] = (cls, code)
            elif code != ref[k][1]:
                errors.append("%s: %s's code isn't %s's" % (cls, k, ref[k][0]))
        got = set()
        for k, want in (("result_id", "queries"), ("msgpack_id", "keies")):
            regs = {}
            for ins in md.disasm(L.read(L.by_name[r[k]], sizes[r[k]]), L.by_name[r[k]]):
                ops = ins.op_str.split(", ")
                if ins.mnemonic == "adrp":
                    regs[ops[0]] = int(ops[1].lstrip("#"), 16)
                elif ins.mnemonic == "ldr" and len(ops) == 3 and ops[1].lstrip("[") in regs and ops[2].startswith("#"):
                    slot = regs[ops[1].lstrip("[")] + int(ops[2].rstrip("]").lstrip("#"), 16)
                    got.add(L.got2name.get(slot))
            if r[want] not in got:
                errors.append("%s: %s doesn't load %s" % (cls, k, want))
        rows.append((cls, r))
    bad = {e.split(": ")[0] for e in errors}
    unfit_now = {connector_table(c) for c in bad}
    rows = [(c, r) for c, r in rows if c not in bad]
    errors = [e for e in errors if connector_table(e.split(": ")[0]) not in UNFIT_CONNECTORS]
    for t in UNFIT_CONNECTORS - unfit_now:
        errors.append("connector %s fits now: take it out of UNFIT_CONNECTORS" % t)
    return rows, errors


def emit_connectors(lib_path, rows):
    out = ["// Generated by tools/gen_master_elements.py (the master tables' connectors); do not edit.",
           "// " + genlib.stamp(lib_path),
           "// Every CSimpleSqliteConnector<Table, Entity> (%d): its vtable, its four query methods (checked: the same" % len(rows),
           "// code as every other's but for the addresses and the query count), its CLocalEntity's queries / keys",
           "// statics, SQLiteDriver::BuildQuery<CLocalEntity> (yayoi's, called) and the query count. Left to the guest",
           "// (another shape): " + ", ".join(sorted(UNFIT_CONNECTORS)) + ".",
           "// X(vtable, QueryToMsgPack(unsigned, unsigned, ...), QueryToMsgPack(char const*, ...),",
           "//   QueryToResultObject(unsigned, ...), QueryToResultObject(char const*, ...), queries, keies, BuildQuery, count)",
           "#define MASTER_CONNECTORS(X) \\"]
    for cls, r in rows:
        out.append('    X("%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", %d) \\' % (
            r["vtable"], r["msgpack_id"], r["msgpack_sql"], r["result_id"], r["result_sql"], r["queries"], r["keies"],
            r["build_query"], r["count"]))
    out.append("    /* end of MASTER_CONNECTORS */")
    out.append("")
    return "\n".join(out)


def generate(lib_path, only=None):
    from elfinfo import Lib
    L = Lib(lib_path)
    md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
    md.detail = True
    sizes = {s.name: s["st_size"] for s in L.elf.get_section_by_name(".dynsym").iter_symbols() if s.name and s["st_value"]}
    sc = Scanner(L, md)
    R = Runner(L)
    classes = element_classes(L)
    out, errors, unfit = [], [], []
    for cls in sorted(classes):
        if only and cls != only:
            continue
        try:
            e = element(L, R, sc, sizes, cls)
            if cls in UNFIT:
                errors.append("%s: fits now; take it out of UNFIT" % cls)
            e["methods"] = methods(L, cls)
            e["table"] = table_methods(L, md, sizes, e)
            out.append(e)
        except Fail as e:
            if cls in UNFIT:
                unfit.append(cls)
            else:
                errors.append(str(e))
        except Exception as e:  # unicorn errors: a call the harness doesn't model
            errors.append("%s: %r" % (cls, e))
    if not only:
        conns, cerr = connectors(L, md, sizes)
        errors += cerr
        out_conns[:] = conns
    return L, out, unfit, errors


out_conns = []


def cpp_default(p):
    d = p["default"]
    if p["t"] == "float":
        v = struct.unpack("<f", d)[0]
        return "%s (%s)" % (repr(v), d.hex())
    return str(int.from_bytes(d, "little", signed=p["t"] == "s32"))


def emit(lib_path, els, unfit):
    out = ["// Generated by tools/gen_master_elements.py (the master tables' element classes); do not edit.",
           "// " + genlib.stamp(lib_path),
           "// Each element: CParameterElementBase, then its properties (params_layout.h), read from the inlined default",
           "// constructor (the source named per class), the destructor and Initialize, run under unicorn",
           "// (port/src/native/master/README.md \"Elements\"). Per property: the key (CHash32 of it in m_name), its",
           "// place in the AddProperty list (link #, -1: never named nor linked by Initialize: a game quirk) and the",
           "// default Initialize stores. %d elements; left to the guest: %s." % (len(els), ", ".join(unfit) or "none"),
           "#ifndef SOA_NATIVE_MASTER_GEN_MASTER_ELEMENTS_H",
           "#define SOA_NATIVE_MASTER_GEN_MASTER_ELEMENTS_H",
           "",
           "#include <cstddef>",
           "#include <cstdint>",
           "",
           '#include "../../params/params_layout.h"',
           "",
           "namespace soa::native::master {",
           "",
           "using u8 = std::uint8_t;",
           "using u32 = std::uint32_t;",
           "using s32 = std::int32_t;",
           "using u64 = std::uint64_t;",
           "",
           "// One property of an element: what the generic element code (master_element.cpp) needs.",
           "enum class PropKind : std::uint8_t { kU32, kS32, kFloat, kBool, kU8, kU64, kString };",
           "struct ElementProp {",
           "    std::uint16_t offset;      // in the element",
           "    PropKind kind;",
           "    bool radian;               // CPropertyConverterRadian (float)",
           "    std::uint32_t n;           // the template's N",
           "    const char* key;           // the ASON key Initialize names it with (null: never named)",
           "    std::int16_t link;         // its place in the AddProperty list (-1: not linked)",
           "    std::uint64_t def;         // the default Initialize stores (the value's bytes; 0 for a string)",
           "};",
           "struct ElementMethod {",
           "    const char* role;          // Initialize, Ctor, CtorCopy, Assign, Dtor, DtorDelete",
           "    const char* symbol;",
           "};",
           ""]
    table = []
    for e in els:
        cls = e["cls"]
        linked = sum(1 for p in e["props"] if p["index"] >= 0)
        out.append("// %s: 0x%x bytes, %d properties (%d linked); layout from %s." % (cls, e["size"], len(e["props"]), linked, e["src"]))
        out.append("class %s {" % cls)
        out.append("public:")
        out.append("    params::CParameterElementBase base;  // 0x000")
        for p in e["props"]:
            name = "m_" + (p["name"] if p["name"] else "unnamed_%03x" % p["off"])
            p["member"] = name
            if p["kind"] == "string":
                ty = "params::CParameterPropertyString<%d>" % p["n"]
                note = '"%s" (#%d)' % (p["name"], p["index"]) if p["name"] else "never named (sic)"
            else:
                ty = "params::CParameterPropertyValue<%s, %d%s>" % (p["t"], p["n"], ", params::CPropertyConverterRadian" if p["conv"] == "CPropertyConverterRadian" else "")
                note = ('"%s" (#%d, default %s)' % (p["name"], p["index"], cpp_default(p))) if p["name"] else "never named (sic)"
            out.append("    %s %s;  // 0x%03x %s" % (ty, name, p["off"], note))
        out.append("};")
        for p in e["props"]:
            out.append("static_assert(offsetof(%s, %s) == 0x%03x);" % (cls, p["member"], p["off"]))
        out.append("static_assert(sizeof(%s) == 0x%x);" % (cls, e["size"]))
        out.append("inline constexpr ElementProp k%sProps[] = {" % cls)
        for p in e["props"]:
            kind = "kString" if p["kind"] == "string" else KINDS[p["t"]]
            key = '"%s"' % p["name"] if p["name"] else "nullptr"
            d = int.from_bytes(p["default"], "little") if p["default"] else 0
            out.append("    {0x%03x, PropKind::%s, %s, %d, %s, %d, 0x%x}," % (
                p["off"], kind, "true" if p["conv"] == "CPropertyConverterRadian" else "false", p["n"], key, p["index"], d))
        out.append("};")
        out.append("inline constexpr ElementMethod k%sMethods[] = {" % cls)
        for role, sym in e["methods"]:
            out.append('    {"%s", "%s"},' % (role, sym))
        out.append("};")
        out.append("inline constexpr ElementMethod k%sTable[] = {" % cls)
        for role, sym in e["table"]:
            out.append('    {"%s", "%s"},' % (role, sym))
        if not e["table"]:
            out.append('    {nullptr, nullptr},  // (not a CMasterParameterBaseSqlite_Simple<> element)')
        out.append("};")
        out.append("")
        table.append("    X(%s, \"_ZTV%s\") \\" % (cls, mangled(cls)))
    out.append("// X(Class, vtable symbol): every element above.")
    out.append("#define MASTER_ELEMENTS(X) \\")
    out += table
    out.append("    /* end of MASTER_ELEMENTS */")
    out.append("")
    out.append("}  // namespace soa::native::master")
    out.append("")
    out.append("#endif  // SOA_NATIVE_MASTER_GEN_MASTER_ELEMENTS_H")
    out.append("")
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lib", default=genlib.lib_path())
    ap.add_argument("-o", "--out", default=DEFAULT_OUT)
    ap.add_argument("--check", metavar="FILE")
    ap.add_argument("--dump", metavar="CLASS")
    a = ap.parse_args()
    L, els, unfit, errors = generate(a.lib, a.dump)
    if a.dump:
        for e in els:
            print(e["cls"], hex(e["size"]), e["src"])
            for p in e["props"]:
                print("  +%#05x %-6s %-5s N=%-4d %-24s #%d %-32s %s" % (p["off"], p["kind"], p["t"] or "", p["n"], p["conv"] or "", p["index"], p["name"] or "(unnamed)", p["default"].hex() if p["default"] else "-"))
            for role, sym in e["methods"] + e["table"]:
                print("  %-10s %s" % (role, sym))
        return
    if errors:
        sys.exit("gen_master_elements: elements that don't fit:\n  " + "\n  ".join(errors[:40]))
    text = emit(a.lib, els, unfit)
    conn_out = os.path.join(os.path.dirname(a.check or a.out), "master_connectors.inc")
    conn_text = emit_connectors(a.lib, out_conns)
    if a.check:
        for path, t in ((a.check, text), (conn_out, conn_text)):
            have = open(path).read().split("\n")
            if have[2:] != t.split("\n")[2:]:
                sys.exit("%s differs from the generator's output for %s" % (path, a.lib))
        return
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    with open(a.out, "w") as f:
        f.write(text)
    with open(conn_out, "w") as f:
        f.write(conn_text)
    print("%s written: %d elements (%d left to the guest)" % (os.path.relpath(a.out, REPO), len(els), len(unfit)))


if __name__ == "__main__":
    main()
