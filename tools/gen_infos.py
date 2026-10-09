#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
r"""Generate port/src/native/info/gen/info_classes.h: the client's info classes (InfoBase and every class
derived from it: CPlayerInfo, CPersonInfo, ..., the response parts) as recovered layouts, and what each
one's Initialize does, for the info subsystem's natives (port/src/native/info/README.md "Info classes").

An info is an InfoBase (0x38: vtable, the property map, the child map) followed by its properties
(params_layout.h: CParameterPropertyValue<T, N, Conv> 0x30, CParameterPropertyString<N> 0x40) and its
child infos, embedded (another info class, or a container: InfoBaseArray<T> / IInfoBaseMap<K, T> /
InfoBaseValueArray<T, P>, an InfoBase with a CSTLVector or CSTLMap at +0x38, 0x50 in all). The
constructors are inlined almost everywhere, so the layouts are read from constructed objects, under
unicorn (tools/uemu.py: the lib with its relocations applied):
  1. objects the lib builds: CInfoManager's constructor (every info the client keeps, each found by its
     vtable), each exported default constructor (C2 / C1), and each InfoBaseArray<T>::DeserializeArray
     run on a one-element array (its T, taken when it reaches InfoBase::DeserializeChild). Each object is
     walked from its vtable: the properties by their vtables from +0x38, a child by its class's vtable,
     recursively; every reading of a class must agree;
  2. Initialize, run on a probe (every word of the object points at a fake vtable whose calls are
     recorded): the steps it takes, which must be the one shape the natives implement: per property,
     CHash32::operator=(key) on m_name, m_named = 1, at most one store of the default (as wide as the
     value), then the property map's __emplace_unique_key_args(NameHash(), property); per child,
     pParseName(), CHash32(that), the child map's __emplace_unique_impl, the child's Initialize. The
     steps must name only the shape's properties and children (a property never named is a game quirk,
     kept, listed per class).
A class whose readings don't agree, or whose Initialize does something else, is left to the guest
(listed in the output). The output: per class a typed layout (static_asserted), its property table and its
Initialize steps; the classes in dependency order.
Beside it, JSON (server/src/api/gen/client_infos.json): the same classes as the wire sees them, each field's
ASON key and value type in its Initialize's order, the containers' elements and CInfoManager's children (a
reply's `data` keys), for the server's reply types (tools/gen_server_infos.py; server/src/api/gen/README.md).

Usage:
  tools/gen_infos.py [--lib PATH] [-o OUT] [--json JSON]   # default: the 3.7.0 lib, write OUT and JSON
  tools/gen_infos.py --check FILE [--check-json JSON]      # exit 1 if FILE (header line not compared) or JSON differs
  tools/gen_infos.py --dump CLASS            # print one class's shape and steps (mangled or plain name)
"""
import argparse
import re
import os
import struct
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
import genlib  # noqa: E402 (before elfinfo: the default lib)

from unicorn import UC_HOOK_MEM_WRITE  # noqa: E402

REPO = os.path.dirname(HERE)
DEFAULT_OUT = os.path.join(REPO, "port/src/native/info/gen/info_classes.h")
DEFAULT_JSON = os.path.join(REPO, "server/src/api/gen/client_infos.json")

STR = "NSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE"
TYPES = {"j": ("u32", 4), "i": ("s32", 4), "f": ("float", 4), "b": ("bool", 1), "h": ("u8", 1), "m": ("u64", 8)}
KINDS = {"u32": "kU32", "s32": "kS32", "float": "kFloat", "bool": "kBool", "u8": "kU8", "u64": "kU64"}

SYM_ALLOCATE = "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj"
SYM_FREE = "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv"
SYM_HASH_ASSIGN = "_ZN9Framework7CHash32aSEPKc"
SYM_HASH_CTOR_STR = "_ZN9Framework7CHash32C1EPKc"
SYM_HASH_D1 = "_ZN9Framework7CHash32D1Ev"
SYM_EMPLACE_PROP = ("_ZNSt6__ndk16__treeINS_12__value_typeIjP18IParameterPropertyEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9"
                    "Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE25__emplace_unique_key_argsIjJjRS3_EEENS_4pairINS_15"
                    "__tree_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbEERKT_DpOT0_")
SYM_EMPLACE_CHILD = ("_ZNSt6__ndk16__treeINS_12__value_typeIjP8InfoBaseEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13"
                     "CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE21__emplace_unique_implIJNS9_7CHash32ERS3_EEENS_4pairINS_15__tree_"
                     "iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbEEDpOT_")
SYM_DESER_CHILD = "_ZN8InfoBase16DeserializeChildEPKN4Aska4ASON6AValue4AMapE"
SYM_NAMEHASH_RE = "_ZNK22CParameterPropertyBaseILj%dEE8NameHashEv"
INFOBASE = "8InfoBase"
MANAGER = "12CInfoManager"
CONTAINER_PREFIX = {"13InfoBaseArrayI": "array", "12IInfoBaseMapI": "map", "18InfoBaseValueArrayI": "valarray"}
CONTAINER_SIZE = 0x50  # InfoBase + a CSTLVector / CSTLMap (0x18) at +0x38

# Classes whose layout isn't properties and children only (the walk can't read it; a new entry needs a look).
UNFIT_LAYOUT = {
    "14CBattleLogInfo": "members of another kind after the properties (the constructor writes +0x548..)",
    "22CCharacterDecoSendInfo": "an array of CCharacterDecoObjectInfo after the properties (+0xc8: new[], a count, delete[] by its destructor)",
}

# Classes whose Initialize isn't the shape the natives implement (a new entry needs a look at the code).
UNFIT_INIT = {
    "11CPlayerInfo": "a string property gets a default text (push_back by push_back)",
}


class Fail(Exception):
    pass


def demangle_type(m):
    return subprocess.run(["c++filt", "-t"], input=m, capture_output=True, text=True).stdout.strip()


def plain(m):
    """'17CPersonStatusInfo' -> 'CPersonStatusInfo' (a plain class name; None for a template)."""
    i = 0
    while i < len(m) and m[i].isdigit():
        i += 1
    n = int(m[:i]) if i else 0
    return m[i:] if i and len(m) == i + n else None


def parse_prop_vt(sym):
    import re
    m = re.match(r"^_ZTV23CParameterPropertyValueI([jifbhm])Lj(\d+)E(18CPropertyConverter|24CPropertyConverterRadian)E$", sym)
    if m:
        return ("value", TYPES[m.group(1)][0], int(m.group(2)), "radian" in m.group(3).lower())
    m = re.match(r"^_ZTV24CParameterPropertyStringI" + re.escape(STR) + r"Lj(\d+)EE$", sym)
    if m:
        return ("string", None, int(m.group(1)), False)
    return None


class Lib:
    """The lib, its relocated image (unicorn), the info classes by typeinfo and their vtables."""

    def __init__(self, path):
        from elfinfo import Lib as ElfLib
        import uemu
        self.L = L = ElfLib(path)
        self.E = uemu.Emu(L)
        self.S = L.by_name
        self._classes()

    def q(self, a):
        return self.E.q(a)

    def _classes(self):
        S, E = self.S, self.E
        ti = {n: a for n, a in S.items() if n.startswith("_ZTI")}
        addr2ti = {a: n for n, a in ti.items()}
        si = S["_ZTVN10__cxxabiv120__si_class_type_infoE"] + 16
        vmi = S["_ZTVN10__cxxabiv121__vmi_class_type_infoE"] + 16

        def parent(n):
            a = ti[n]
            k = E.q(a)
            if k == si:
                return addr2ti.get(E.q(a + 16))
            if k == vmi:  # (the containers: InfoBase first, then the CSTLVector / CSTLMap)
                return addr2ti.get(E.q(a + 24))
            return None
        self.chain = {}
        for n in ti:
            c, p = [n[4:]], n
            for _ in range(8):
                p = parent(p) if p in ti else None
                if not p:
                    break
                c.append(p[4:])
            if INFOBASE in c[1:]:
                self.chain[n[4:]] = c
        # every vtable of these classes (exported or local): [0][typeinfo][slots...]
        want = {ti["_ZTI" + m]: m for m in self.chain}
        self.vt_class = {}  # address point -> class
        for seg in self.L.segs:
            if seg["p_flags"] & 1:
                continue
            lo, n = seg["p_vaddr"], seg["p_memsz"]
            data = E.read(lo, n)
            for i in range(8, n - 16, 8):
                v = struct.unpack_from("<Q", data, i)[0]
                if v in want and struct.unpack_from("<Q", data, i - 8)[0] == 0:
                    slot0 = struct.unpack_from("<Q", data, i + 8)[0]
                    if self.L.segs[0]["p_vaddr"] <= slot0 < self.L.segs[0]["p_vaddr"] + self.L.segs[0]["p_memsz"]:
                        self.vt_class[lo + i + 8] = want[v]
        self.vt_sym = {a + 16: n for n, a in S.items() if n.startswith("_ZTV")}

    def container(self, m):
        for x in self.chain[m]:
            for p, k in CONTAINER_PREFIX.items():
                if x.startswith(p):
                    return k
        return None


class Shape:
    def __init__(self, cls, kind, size, props=(), children=()):
        self.cls, self.kind, self.size, self.props, self.children = cls, kind, size, list(props), list(children)
        self.tail = 0  # plain bytes after the last property or child (sizeof - size): set by generate()

    def sig(self):
        return (self.cls, self.kind, self.size, tuple(self.props), tuple((o, c.sig()) for o, c in self.children))


def walk(X, read_q, limit, e, m):
    """The info of class m at e in a constructed object (read_q(off) -> qword, offsets < limit). An info
    vtable after the properties is a child where m's Initialize initializes one (X.kids), or before the
    last of those (a child Initialize leaves out: a game quirk); else the object ended (a sibling follows)."""
    k = X.container(m)
    if k:
        return Shape(m, k, CONTAINER_SIZE)
    props, children = [], []
    at = e + 0x38
    while at + 8 <= limit:
        v = read_q(at)
        s = X.vt_sym.get(v)
        p = parse_prop_vt(s) if s else None
        if p:
            if m in X.extent and at - e >= X.extent[m]:
                break  # (past the last property or child Initialize names: not this object's)
            props.append((at - e, p[0], p[1], p[2], p[3], s))
            at += 0x30 if p[0] == "value" else 0x40
            continue
        c = X.vt_class.get(v)
        kids = X.kids.get(m, ())
        if c and c != MANAGER and ((at - e) in kids or any(k > at - e for k in kids)):
            ch = walk(X, read_q, limit, at, c)
            children.append((at - e, ch))
            at += ch.size
            continue
        break
    return Shape(m, "plain", at - e, props, children)


class Runner:
    """Unicorn runs: allocation, the hash and map calls hooked (recorded, not run)."""

    def __init__(self, X):
        self.X = X
        E, S = X.E, X.S
        self.ev = []
        E.hook_addr(S[SYM_ALLOCATE], lambda e: (self.ev.append(("alloc", e.x(0))), e.alloc(e.x(0), 0xEE))[1])
        E.hook_addr(S[SYM_FREE], lambda e: self.ev.append(("free",)))
        E.hook_addr(S[SYM_HASH_ASSIGN], lambda e: (self.ev.append(("name", e.x(0), e.cstr(e.x(1)).decode())), e.x(0))[1])
        E.hook_addr(S[SYM_HASH_CTOR_STR], lambda e: (self.ev.append(("hashc", e.cstr(e.x(1)).decode())), e.x(0))[1])
        E.hook_addr(S[SYM_HASH_D1], lambda e: e.x(0))
        E.hook_addr(S[SYM_EMPLACE_PROP], lambda e: self.ev.append(("emp", e.x(0), e.q(e.x(3)))))
        E.hook_addr(S[SYM_EMPLACE_CHILD], lambda e: self.ev.append(("empc", e.x(0), e.q(e.x(2)))))
        E.hook_import("strlen", lambda e: len(e.cstr(e.x(0))))

        def memcpy(e):
            e.uc.mem_write(e.x(0), e.read(e.x(1), e.x(2)))
            return e.x(0)
        E.hook_import("memcpy", memcpy)
        E.hook_import("memmove", memcpy)
        E.hook_import("memset", lambda e: (e.uc.mem_write(e.x(0), bytes([e.x(1) & 255]) * e.x(2)), e.x(0))[1])
        self.capture = None
        E.hook_addr(S[SYM_DESER_CHILD], self._deser_child)
        self.watch = None
        E.uc.hook_add(UC_HOOK_MEM_WRITE, self._on_write)
        # the probe: every word points at a fake vtable whose slots record the call
        self.PROBE, self.PSIZE = 0x50000000, 0x20000
        E.uc.mem_map(self.PROBE, self.PSIZE)
        self.FV = 0x58000000
        E.uc.mem_map(self.FV, 0x1000)
        self.KEY = E.alloc(16)
        E.uc.mem_write(self.KEY, b"probe_child\0")
        stubs = []
        for slot in range(8):
            E._next_hook -= 4
            a = E._next_hook
            E.hooks[a] = self._vcall(slot)
            stubs.append(a)
        E.uc.mem_write(self.FV, struct.pack("<8Q", *stubs))

    def _vcall(self, slot):
        def f(e):
            this = e.x(0)
            self.ev.append(("vcall", this, slot))
            if slot == 2:
                return struct.unpack("<I", e.read(this + 0x20, 4))[0]
            if slot == 3:
                return self.KEY
            return 0
        return f

    def _on_write(self, uc, access, addr, size, value, _):
        if self.watch and self.watch[0] <= addr < self.watch[1]:
            self.ev.append(("w", addr, size, value & ((1 << (8 * size)) - 1)))

    def _deser_child(self, e):
        if self.capture is not None:
            import uemu
            n = min(0x8000, uemu.STACK_TOP - e.x(0)) if e.x(0) < uemu.STACK_TOP else 0x8000
            self.capture.append((e.x(0), e.read(e.x(0), n)))
            self.ev.append(("captured",))
        return 1

    def call(self, sym, *args, watch=None):
        self.ev.clear()
        self.watch = watch
        try:
            self.X.E.call(self.X.S[sym], *args)
        finally:
            self.watch = None
        return list(self.ev)


def readers(buf):
    return (lambda o: struct.unpack_from("<Q", buf, o)[0]), len(buf)


def collect(shape, into, where):
    into.setdefault(shape.cls, []).append((where, shape))
    for o, c in shape.children:
        collect(c, into, where + "+%#x" % o)


def capture_shapes(X, R):
    """{class: [(where, Shape)]} from every object the lib builds that we can run."""
    E, S = X.E, X.S
    found = {}
    X.manager_children = {}  # offset -> class of each info CInfoManager's constructor builds (the --json schema)
    X.other_members = {}
    X.sizes = {}  # class -> {(sizeof the lib's code uses, where)}
    # 1. CInfoManager's constructor: every info it keeps
    size = 0x20000
    buf = E.alloc(size, 0xEE)
    R.call("_ZN12CInfoManagerC1Ev", buf)
    data = E.read(buf, size)
    rq, lim = readers(data)
    at = 0x38
    while at + 8 <= lim:
        c = X.vt_class.get(rq(at))
        if c and c != MANAGER:
            sh = walk(X, rq, lim, at, c)
            collect(sh, found, "CInfoManager+%#x" % at)
            X.manager_children[at] = c
            at += sh.size
        else:
            at += 8
    # 2. the exported default constructors
    for m in sorted(X.chain):
        if m == MANAGER:
            continue
        for sym in ("_ZN%sC2Ev" % m, "_ZN%sC1Ev" % m):
            if sym in S:
                buf = E.alloc(0x8000, 0xEE)
                R.call(sym, buf)
                data = E.read(buf, 0x8000)
                rq, lim = readers(data)
                if X.vt_class.get(rq(0)) != m:
                    raise Fail("%s: %s doesn't store the class's vtable" % (m, sym))
                sh = walk(X, rq, lim, 0, m)
                tail = [i for i in range(sh.size, lim) if data[i] != 0xEE]
                if tail:
                    X.other_members[m] = "%s writes +%#x.. past the properties and children (%#x): members of another kind" % (
                        sym, tail[0], sh.size)
                    continue
                collect(sh, found, sym)
                break
    # 3. InfoBaseArray<T>::DeserializeArray on one map: its T, constructed (and initialized) on the stack
    item = E.alloc(0x20, 0)
    E.uc.mem_write(item, struct.pack("<IIQQQ", 7, 0, 0, 0, 0))  # an AValue: kind 7 (map), {pairs 0, count 0}
    arr = E.alloc(0x10, 0)
    E.uc.mem_write(arr, struct.pack("<QI", item, 1))
    for sym in sorted(S):
        if not (sym.startswith("_ZN13InfoBaseArrayI") and sym.endswith("E16DeserializeArrayEPKN4Aska4ASON6AValue6AArrayE")):
            continue
        t = sym[len("_ZN13InfoBaseArrayI"):-len("E16DeserializeArrayEPKN4Aska4ASON6AValue6AArrayE")]
        if t not in X.chain:
            continue
        this = E.alloc(0x50, 0)  # an empty vector at +0x38
        R.capture = []
        try:
            R.call(sym, this, arr)
        except Exception:  # (after the capture the run goes on with what the harness doesn't model)
            pass
        caps, R.capture = R.capture, None
        # the vector's first storage (push_back into an empty vector: capacity 1) is sizeof(T)
        after = R.ev[[e[0] for e in R.ev].index("captured") + 1:] if ("captured",) in R.ev else []
        allocs = [e[1] for e in after if e[0] == "alloc"]
        if allocs:
            X.sizes.setdefault(t, set()).add((allocs[0], sym))
        for addr, data in caps[:1]:
            rq, lim = readers(data)
            if X.vt_class.get(rq(0)) == t:
                collect(walk(X, rq, lim, 0, t), found, sym)
    # 4. IInfoBaseMap<K, T>::DeserializeChild on a one-pair map: its T, copied into the new tree node (heap,
    # 0xEE around it), taken when the node's Initialize is called (another emulator: Initialize is patched)
    for t, (where, data) in map_captures(X).items():
        rq, lim = readers(data)
        if X.vt_class.get(rq(0)) != t:
            raise Fail("%s: the node's Initialize is called on another class's object (%s)" % (t, where))
        sh = walk(X, rq, lim, 0, t)
        tail = [i for i in range(sh.size, lim) if data[i] != 0xEE]
        if tail and tail[0] < sh.size + 8:
            continue  # (no end seen: not a reading)
        collect(sh, found, where)
    return found


class Stop(Exception):
    pass


def map_captures(X):
    import re
    import uemu
    E = uemu.Emu(X.L)
    S = X.S
    last = [0]

    def allocate(e):
        last[0] = e.x(0)
        return e.alloc(e.x(0) + 0x100, 0xEE)
    E.hook_addr(S[SYM_ALLOCATE], allocate)
    E.hook_addr(S[SYM_FREE], lambda e: None)
    E.hook_addr(S[SYM_HASH_D1], lambda e: e.x(0))
    E.hook_import("memset", lambda e: (e.uc.mem_write(e.x(0), bytes([e.x(1) & 255]) * e.x(2)), e.x(0))[1])

    def memcpy(e):
        e.uc.mem_write(e.x(0), e.read(e.x(1), e.x(2)))
        return e.x(0)
    E.hook_import("memcpy", memcpy)
    E.hook_import("memmove", memcpy)
    E.hook_import("strlen", lambda e: len(e.cstr(e.x(0))))
    got = {}
    cur = []

    def at_init(t):
        def f(e):
            got[t] = (cur[0], e.read(e.x(0), 0x2000))
            # the node (its key at +0x20, T at +0x28) was the last allocation: sizeof(T) is its size - 0x28
            X.sizes.setdefault(t, set()).add((last[0] - 0x28, cur[0]))
            raise Stop()
        return f
    rx = re.compile(r"^_ZN12IInfoBaseMapI([a-z])(\d+\w+?)E16DeserializeChildEPKN4Aska4ASON6AValue4AMapE$")
    jobs = []
    for sym in sorted(S):
        mm = rx.match(sym)
        if mm and mm.group(2) in X.chain and "_ZN%s10InitializeEv" % mm.group(2) in S:
            jobs.append((sym, mm.group(2)))
    for sym, t in jobs:
        E.hook_addr(S["_ZN%s10InitializeEv" % t], at_init(t))
    # `this`: a fake vtable whose slot 4 (ConvertParserValueToKey) gives key 1; the tree at +0x38
    E._next_hook -= 4
    key_stub = E._next_hook
    E.hooks[key_stub] = lambda e: 1
    fv = E.alloc(0x40, 0)
    E.uc.mem_write(fv + 0x20, struct.pack("<Q", key_stub))
    pair = E.alloc(0x40, 0)
    E.uc.mem_write(pair, struct.pack("<IIQQQ", 0, 0, 0, 0, 0) + struct.pack("<IIQQQ", 7, 0, 0, 0, 0))
    amap = E.alloc(0x10, 0)
    E.uc.mem_write(amap, struct.pack("<QI", pair, 1))
    for sym, t in jobs:
        this = E.alloc(0x50, 0)
        E.uc.mem_write(this, struct.pack("<Q", fv))
        cur[:] = [sym]
        try:
            E.call(S[sym], this, amap)
        except Exception:
            pass
    return got


def run_probe(X, R, m):
    P = R.PROBE
    X.E.uc.mem_write(P, struct.pack("<Q", R.FV) * (R.PSIZE // 8))
    return R.call("_ZN%s10InitializeEv" % m, P, watch=(P, P + R.PSIZE))


def probe_children(X, R, m):
    """The offsets of the children m's Initialize puts in the child map (whatever else it does)."""
    try:
        evs = run_probe(X, R, m)
    except Exception:
        evs = list(R.ev)
    return [e[2] - R.PROBE for e in evs if e[0] == "empc" and e[1] == R.PROBE + 0x20]


def probe_initialize(X, R, m):
    """The steps of m's Initialize, from a run on the probe; None and a reason when they aren't the shape."""
    P = R.PROBE
    evs = run_probe(X, R, m)
    steps, allocs, frees = [], [], 0
    rest = []
    for e in evs:
        if e[0] == "alloc":
            allocs.append(e[1])
        elif e[0] == "free":
            frees += 1
        else:
            rest.append(e)
    evs = rest
    i, n = 0, len(evs)

    def at(j):
        return evs[j] if j < n else None
    while i < n:
        e = evs[i]
        if e[0] == "name":
            k = e[1] - P - 0x18
            key = e[2]
            i += 1
            if at(i) != ("w", P + k + 0x10, 1, 1):
                return None, "property +%#x (%s): no m_named = 1 next (%s)" % (k, key, at(i))
            i += 1
            dw = []
            while at(i) and at(i)[0] == "w" and P + k + 0x28 <= at(i)[1] < P + k + 0x30:
                dw.append((at(i)[1] - P - k - 0x28, at(i)[2], at(i)[3]))
                i += 1
            if len(dw) > 1 or (dw and dw[0][0] != 0):
                return None, "property +%#x (%s): default stores %s" % (k, key, dw)
            if at(i) != ("vcall", P + k, 2) or at(i + 1) != ("emp", P + 8, P + k):
                return None, "property +%#x (%s): not NameHash + emplace next (%s, %s)" % (k, key, at(i), at(i + 1))
            i += 2
            steps.append(("prop", k, key, dw[0][1:] if dw else None))
        elif e[0] == "vcall" and e[2] == 3:
            c = e[1] - P
            if not (at(i + 1) and at(i + 1)[0] == "hashc" and at(i + 1)[1] == "probe_child" and at(i + 2) == ("empc", P + 0x20, P + c)
                    and at(i + 3) == ("vcall", P + c, 2)):
                return None, "child +%#x: not pParseName, CHash32, emplace, Initialize (%s)" % (c, evs[i:i + 4])
            steps.append(("child", c))
            i += 4
        elif e[0] == "w":
            steps.append(("store", e[1] - P, e[2], e[3]))  # (a member of another kind: CInfoManager's)
            i += 1
        else:
            return None, "unexpected %s" % (e,)
    long_keys = [(len(s[2]) + 16) & ~15 for s in steps if s[0] == "prop" and len(s[2]) >= 23]
    if allocs != long_keys or frees != len(long_keys):
        return None, "allocates %s, frees %d; the long keys need %s" % (allocs, frees, long_keys)
    return steps, None


def check_steps(X, shape, steps):
    """The steps against the layout: each property / child is one of the shape's, each named once, a default
    as wide as the value."""
    props = {p[0]: p for p in shape.props}
    kids = {o: c for o, c in shape.children}
    seen = set()
    for s in steps:
        if s[0] == "store":
            raise Fail("Initialize stores %d bytes at +%#x, not a property's" % (s[2], s[1]))
        if s[1] in seen:
            raise Fail("+%#x twice" % s[1])
        seen.add(s[1])
        if s[0] == "prop":
            p = props.get(s[1])
            if not p:
                raise Fail("Initialize names +%#x (%s), not a property" % (s[1], s[2]))
            if p[1] == "string":
                if s[3] is not None:
                    raise Fail("a default for the string at +%#x" % s[1])
            elif s[3] is not None:
                w = [v for v in TYPES.values() if v[0] == p[2]][0][1]
                if s[3][0] != w:
                    raise Fail("+%#x (%s %s): a default %d bytes wide" % (s[1], p[2], s[2], s[3][0]))
        else:
            if s[1] not in kids:
                raise Fail("Initialize treats +%#x as a child" % s[1])
    # (a property never named, a child never initialized: game quirks, kept)
    return [p[0] for p in shape.props if p[0] not in seen] + [o for o in kids if o not in seen]


def build(X, shapes, m, buf, at):
    """An object of class m at buf + at as the default constructor leaves it (InfoCode::Ctor)."""
    E = X.E
    sh = shapes[m]
    a = buf + at
    E.uc.mem_write(a, struct.pack("<QQQQQQQ", X.S["_ZTV" + m] + 16, a + 0x10, 0, 0, a + 0x28, 0, 0))
    if sh.kind != "plain":
        body = (a + 0x40, 0, 0) if sh.kind == "map" else (0, 0, 0)
        E.uc.mem_write(a + 0x38, struct.pack("<QQQ", *body))
        return
    hvt = X.S["_ZTVN9Framework7CHash32E"] + 16
    for p in sh.props:
        E.uc.mem_write(a + p[0], struct.pack("<QQ", X.S[p[5]] + 16, 0))
        E.uc.mem_write(a + p[0] + 0x10, b"\0")
        E.uc.mem_write(a + p[0] + 0x18, struct.pack("<QI", hvt, 0))
        if p[1] == "string":
            E.uc.mem_write(a + p[0] + 0x28, b"\0" * 24)
    for o, c in sh.children:
        build(X, shapes, c.cls, buf, at + o)


def check_destructor(X, R, shapes, m, sym):
    """"" when m's destructor (or copy constructor) writes only inside the layout (its tail, plain data, only
    a copy constructor), else what it writes past it."""
    size = shapes[m].size
    buf = X.E.alloc(size + 0x400, 0xEE)
    build(X, shapes, m, buf, 0)
    try:
        if "ERKS_" in sym:  # a copy constructor: into a second buffer, from the built object
            dst = X.E.alloc(size + 0x400, 0xEE)
            evs = R.call(sym, dst, buf, watch=(dst, dst + size + 0x400))
            buf = dst
        else:
            evs = R.call(sym, buf, watch=(buf, buf + size + 0x400))
    except Exception as ex:
        return "%s doesn't run on the layout (%r)" % (sym, ex)
    end = size if "ERKS_" in sym else size - shapes[m].tail
    past = [e[1] - buf for e in evs if e[0] == "w" and e[1] >= buf + end]
    return ("%s writes +%#x past the properties and children (%#x): members of another kind" % (sym, past[0], size)) if past else ""


def check_namehash(X, shapes):
    """Every property vtable's slot 2 is CParameterPropertyBase<N>::NameHash: `add x0, x0, #0x18` and a tail
    call (through the PLT) of one function, `ldr w0, [x0, #8]; ret` (CHash32's hash): the natives read
    m_name's hash instead of calling it."""
    E, L = X.E, X.L
    targets = set()
    for sh in shapes.values():
        for p in sh.props:
            vt = X.S[p[5]] + 16
            f = E.q(vt + 16)
            name = L.by_addr.get(f)
            if name != SYM_NAMEHASH_RE % p[3]:
                raise Fail("%s: slot 2 of %s is %s" % (sh.cls, p[5], name))
            add, b = struct.unpack("<II", E.read(f, 8))
            if add != 0x91006000 or b & 0xFC000000 != 0x14000000:
                raise Fail("%s isn't add x0, x0, #0x18; b ..." % name)
            off = b & 0x3FFFFFF
            off -= (1 << 26) if off & (1 << 25) else 0
            targets.add(f + 4 + 4 * off)
    callee = [L.plt.get(t, L.by_addr.get(t)) for t in targets]
    if len(callee) != 1 or callee[0] not in X.S or E.read(X.S[callee[0]], 8) != struct.pack("<II", 0xB9400800, 0xD65F03C0):
        raise Fail("NameHash's callee isn't one `ldr w0, [x0, #8]; ret`: %s" % callee)


def generate(lib_path):
    X = Lib(lib_path)
    R = X.runner = Runner(X)
    # the children each Initialize initializes (the walk's tell of a child from a sibling)
    X.kids = {}
    for m in sorted(X.chain):
        if "_ZN%s10InitializeEv" % m in X.S and not X.container(m):
            X.kids[m] = set(probe_children(X, R, m))
    # where each Initialize's last property or child ends: a property after it would be another object's
    X.extent = {}
    for m in X.kids:
        try:
            steps, _ = probe_initialize(X, R, m)
        except Exception:
            steps = None
        if steps:
            X.extent[m] = max(s[1] + 0x30 for s in steps if s[0] == "prop") if any(s[0] == "prop" for s in steps) else 0x38
    found = capture_shapes(X, R)
    errors, shapes, unshaped = [], {}, []
    # sizeof as the lib's code uses it: more than the properties and children is a tail of plain bytes when
    # nothing the generator runs writes it (the constructor's EE reading, the destructor below); less is an error
    tails = {}
    for m, ss in X.sizes.items():
        for sz, where in ss:
            for _, sh in found.get(m, []):
                if sh.size > sz and m not in X.other_members:
                    X.other_members[m] = "%s uses sizeof %#x, the properties and children end at %#x" % (where, sz, sh.size)
                elif sh.size < sz:
                    if tails.get(m, sz - sh.size) != sz - sh.size:
                        X.other_members[m] = "%s: two sizeofs" % where
                    tails[m] = sz - sh.size
    for m in sorted(X.chain):
        rs = found.get(m) or []
        if m in X.other_members:
            unshaped.append(m)
            if m not in UNFIT_LAYOUT:
                errors.append("%s: %s" % (m, X.other_members[m]))
            continue
        if not rs:
            unshaped.append(m)
            continue
        sigs = {}
        for where, sh in rs:
            sigs.setdefault(sh.sig(), []).append(where)
        if len(sigs) > 1:
            errors.append("%s: the readings differ: %s" % (m, "; ".join("%s: %#x, %d properties" % (w[0], s[2], len(s[3]))
                                                                        for s, w in sigs.items())))
            continue
        shapes[m] = rs[0][1]
    for m, n in tails.items():
        if m in shapes:
            shapes[m].tail = n
            shapes[m].size += n
    check_namehash(X, shapes)
    # each exported destructor and copy constructor, run on an object built from the layout (0xEE after
    # it): it may write only inside the layout (a write past it: members of another kind the walk didn't see)
    for m in sorted(shapes):
        if shapes[m].kind != "plain":
            continue
        for group in (("D2Ev", "D1Ev"), ("C2ERKS_", "C1ERKS_")):
            syms = [x for x in ("_ZN%s%s" % (m, g) for g in group) if x in X.S]
            why = check_destructor(X, R, shapes, m, syms[0]) if syms else ""
            if why and m not in X.other_members:
                if m not in UNFIT_LAYOUT:
                    errors.append("%s: %s" % (m, why))
                X.other_members[m] = why
    for m in list(shapes):
        if m in X.other_members:
            del shapes[m]
            unshaped.append(m)
    for m in UNFIT_LAYOUT:
        if m not in X.other_members:
            errors.append("%s fits now: take it out of UNFIT_LAYOUT" % m)
    inits, unfit, never = {}, {}, {}
    for m in sorted(X.chain):
        if "_ZN%s10InitializeEv" % m not in X.S or X.container(m):
            continue
        if m in UNFIT_INIT:
            unfit[m] = UNFIT_INIT[m]
            continue
        if m not in shapes and m != MANAGER:
            unfit[m] = "no layout (no object of the class was built)"
            continue
        try:
            steps, why = probe_initialize(X, R, m)
        except Exception as ex:
            steps, why = None, repr(ex)
        if steps is None:
            errors.append("%s: Initialize: %s" % (m, why))
            continue
        if m == MANAGER:  # (no layout: the manager's other members aren't generated; its steps are taken as they are)
            inits[m] = steps
            continue
        try:
            never[m] = check_steps(X, shapes[m], steps)
        except Fail as ex:
            errors.append("%s: %s" % (m, ex))
            continue
        inits[m] = steps
    for m in UNFIT_INIT:
        if m in inits:
            errors.append("%s fits now: take it out of UNFIT_INIT" % m)
    return X, shapes, inits, unfit, never, unshaped, errors


# ---- output ----

def cpp_name(m):
    return plain(m) or demangle_type(m)


def ident(m):
    p = plain(m)
    if p:
        return p
    import re
    return "T_" + re.sub(r"\W+", "_", demangle_type(m)).strip("_")


def member_type(p):
    if p[1] == "string":
        return "params::CParameterPropertyString<%d>" % p[3]
    return "params::CParameterPropertyValue<%s, %d%s>" % (p[2], p[3], ", params::CPropertyConverterRadian" if p[4] else "")


def parse_name(X, m):
    """The class's pParseName() (vtable slot 3: a constant string), its key in a parent's child map."""
    if not hasattr(X, "parse_names"):
        X.parse_names = {}
    if m not in X.parse_names:
        try:
            f = X.E.q(X.S["_ZTV" + m] + 16 + 8 * 3)
            r = X.E.call(f, 0)
            X.parse_names[m] = X.E.cstr(r).decode() if r else None
        except Exception:
            X.parse_names[m] = None
    return X.parse_names[m]


def container_elem(X, m):
    """A container's element: ("info", T) (InfoBaseArray<T>), ("map", key size, T) (IInfoBaseMap<K, T>) or
    ("value", (T, N)) (InfoBaseValueArray<T, CParameterPropertyValue<T, N, CPropertyConverter>>)."""
    import re
    for x in X.chain[m]:
        r = re.match(r"^13InfoBaseArrayI(\d+\w+)E$", x)
        if r:
            return ("info", r.group(1))
        r = re.match(r"^12IInfoBaseMapI([jm])(\d+\w+)E$", x)
        if r:
            return ("map", 4 if r.group(1) == "j" else 8, r.group(2))
        r = re.match(r"^18InfoBaseValueArrayI([jifbhm])23CParameterPropertyValueI\1Lj(\d+)E18CPropertyConverterEE$", x)
        if r:
            return ("value", (TYPES[r.group(1)][0], int(r.group(2))))
    raise Fail("%s: no container template in %s" % (m, X.chain[m]))


def container_fns(X, m):
    """The guest functions a container's natives call: (copy one element into the map: __emplace_hint_unique_key_args,
    destroy the map's nodes: __tree::destroy, assign: vector::assign<E*> / __tree::__assign_multi); None when the lib
    has none (one symbol each, or none)."""
    e = container_elem(X, m)
    if e[0] == "value":
        t, n = e[1]
        tm = [k for k, v in TYPES.items() if v[0] == t][0]
        elem = "23CParameterPropertyValueI%sLj%dE18CPropertyConverterE" % (tm, n)
    else:
        elem = e[-1]
    if e[0] == "map":
        pre = "_ZNSt6__ndk16__treeINS_12__value_typeI%s%sEENS_19__map_value_compare" % ("j" if e[1] == 4 else "m", elem)
        want = {"copy": "30__emplace_hint_unique_key_args", "destroy": "7destroyEPNS_11__tree_nodeI", "assign": "14__assign_multiI"}
    else:
        pre = "_ZNSt6__ndk16vectorI%sN9Framework13CSTLAllocatorI" % elem
        want = {"assign": "6assignIPS"}
    out = {}
    for k, frag in want.items():
        c = [n for n in X.S if n.startswith(pre) and frag in n]
        if len(c) > 1:
            raise Fail("%s: %d candidates for %s" % (m, len(c), k))
        out[k] = c[0] if c else None
    return out


def order(X, shapes, names):
    out, done = [], set()

    def visit(m):
        if m in done or m not in shapes:
            return
        done.add(m)
        sh = shapes[m]
        if sh.kind == "plain":
            for o, c in sh.children:
                visit(c.cls)
        else:
            e = container_elem(X, m)
            if e[0] != "value":
                visit(e[-1])
        out.append(m)
    for m in names:
        visit(m)
    return out


def step_line(st):
    if st[0] == "prop":
        w, v = st[3] if st[3] else (0, 0)
        return '    {InfoStep::kProperty, 0x%03x, "%s", %d, 0x%x},' % (st[1], st[2], w, v)
    if st[0] == "store":
        return "    {InfoStep::kStore, 0x%03x, nullptr, %d, 0x%x}," % (st[1], st[2], st[3])
    return "    {InfoStep::kChild, 0x%03x, nullptr, 0, 0}," % st[1]


def emit(lib_path, X, shapes, inits, unfit, never, unshaped):
    every = order(X, shapes, sorted(shapes))
    names = [m for m in every if shapes[m].kind == "plain"]
    containers = [m for m in every if shapes[m].kind != "plain"]
    keys_of = {m: dict((s[1], s[2]) for s in steps if s[0] == "prop") for m, steps in inits.items()}
    # one Initialize per address (an alias of another class's is that class's code)
    init_sym, by_addr = {}, {}
    for m in names:
        if m in inits:
            sym = "_ZN%s10InitializeEv" % m
            a = X.S[sym]
            if a in by_addr:
                if inits[by_addr[a]] != inits[m]:
                    raise Fail("%s and %s share an Initialize but not its steps" % (m, by_addr[a]))
                continue
            by_addr[a] = m
            init_sym[m] = sym
    ckind = {"array": "kArray", "map": "kMap", "valarray": "kValueArray"}
    out = ["// Generated by tools/gen_infos.py (the info classes); do not edit.",
           "// " + genlib.stamp(lib_path),
           "// Each info: InfoBase (info_layout.h), its properties (params_layout.h) and its children (infos, or",
           "// containers: InfoContainer), read from objects the lib builds, and what its Initialize does, run under",
           "// unicorn (port/src/native/info/README.md \"Info classes\"). %d infos, %d containers; %d Initialize step" % (
               len(names), len(containers), len(init_sym)),
           "// lists. Initialize left to the guest: %s." % "; ".join(
               "%s (%s)" % (cpp_name(m), why) for m, why in sorted(unfit.items())),
           "#ifndef SOA_NATIVE_INFO_GEN_INFO_CLASSES_H",
           "#define SOA_NATIVE_INFO_GEN_INFO_CLASSES_H",
           "",
           "#include <cstddef>",
           "#include <cstdint>",
           "",
           '#include "../../params/params_layout.h"',
           '#include "../info_layout.h"',
           "",
           "namespace soa::native::info {",
           "",
           "// The infos and the containers (InfoBaseArray<T>, IInfoBaseMap<K, T>, InfoBaseValueArray<T, P>:",
           "// InfoContainer, their element's class or property), each after what it holds.",
           ""]
    table = []
    for m in every:
        sh = shapes[m]
        if sh.kind != "plain":
            e = container_elem(X, m)
            if e[0] == "value":
                elem = "nullptr, 0, {0, InfoPropKind::%s, false, %d}" % (KINDS[e[1][0]], e[1][1])
            else:
                t = e[-1]
                ok = t in shapes and shapes[t].kind == "plain"
                elem = "%s, %d, {}" % ("&kInfo_%s" % ident(t) if ok else "nullptr", e[1] if e[0] == "map" else 0)
            fns = container_fns(X, m)
            q = lambda k: ('"%s"' % fns[k]) if fns.get(k) else "nullptr"
            out.append('inline constexpr InfoClass kInfo_%s{"%s", "_ZTV%s", InfoKind::%s, 0x%x, {}, {}, {}, %s, %s, %s, %s};' % (
                ident(m), cpp_name(m), m, ckind[sh.kind], CONTAINER_SIZE, elem, q("copy"), q("destroy"), q("assign")))
            continue
        cls = ident(m)
        keys = keys_of.get(m, {})
        out.append("// %s: 0x%x bytes, %d properties, %d children%s." % (
            cpp_name(m), sh.size, len(sh.props), len(sh.children),
            "; never named / initialized (sic): " + ", ".join("+%#x" % o for o in never[m]) if never.get(m) else ""))
        out.append("class %s {" % cls)
        out.append("public:")
        out.append("    InfoBase base;  // 0x000")
        used = set()
        members = []
        items = [(p[0], "p", p) for p in sh.props] + [(o, "c", c) for o, c in sh.children]
        for off, k, x in sorted(items, key=lambda t: t[0]):
            if k == "p":
                nm = keys.get(off)
                base = "m_" + (nm if nm else "unnamed_%03x" % off)
                note = ('"%s"' % nm) if nm else ("never named (sic)" if m in inits else "")
                ty = member_type(x)
            else:
                ty = ident(x.cls) if x.kind == "plain" else "InfoContainer"
                key = parse_name(X, x.cls)
                base = ("m_" + re.sub(r"\W", "_", key)) if key else "m_child_%03x" % off
                note = '%s ("%s")' % (cpp_name(x.cls), key) if key else cpp_name(x.cls)
            name = base if base not in used else "%s_%03x" % (base, off)
            used.add(name)
            members.append((off, name))
            out.append("    %s %s;  // 0x%03x %s" % (ty, name, off, note))
        if sh.tail:
            members.append((sh.size - sh.tail, "m_tail"))
            out.append("    u8 m_tail[0x%x];  // 0x%03x plain data after the last member (copied as it is; the constructor leaves it)" % (
                sh.tail, sh.size - sh.tail))
        out.append("};")
        for off, name in members:
            out.append("static_assert(offsetof(%s, %s) == 0x%03x);" % (cls, name, off))
        out.append("static_assert(sizeof(%s) == 0x%x);" % (cls, sh.size))
        if sh.props:
            out.append("inline constexpr InfoProp k%sProps[] = {" % cls)
            for p in sh.props:
                kind = "kString" if p[1] == "string" else KINDS[p[2]]
                out.append("    {0x%03x, InfoPropKind::%s, %s, %d}," % (p[0], kind, "true" if p[4] else "false", p[3]))
            out.append("};")
        if sh.children:
            out.append("inline constexpr InfoChild k%sChildren[] = {" % cls)
            for o, c in sh.children:
                out.append("    {0x%03x, &kInfo_%s}," % (o, ident(c.cls)))
            out.append("};")
        if m in inits:
            out.append("inline constexpr InfoStep k%sInit[] = {" % cls)
            for st in inits[m]:
                out.append(step_line(st))
            out.append("};")
        tail = ", nullptr, 0, {}, nullptr, nullptr, nullptr, 0x%x" % sh.tail if sh.tail else ""
        out.append('inline constexpr InfoClass kInfo_%s{"%s", "_ZTV%s", InfoKind::kInfo, sizeof(%s), %s, %s, %s%s};' % (
            cls, cpp_name(m), m, cls,
            ("k%sProps" % cls) if sh.props else "{}", ("k%sChildren" % cls) if sh.children else "{}",
            ("k%sInit" % cls) if m in inits else "{}", tail))
        if m in init_sym:
            table.append('    X(%s, "%s") \\' % (cls, init_sym[m]))
        out.append("")
    out.append("")
    manager = MANAGER in inits
    if manager:
        out.append("// CInfoManager: the client's infos (an InfoBase whose children are every info it keeps). Only its base is")
        out.append("// generated (its other members aren't read); its Initialize's steps are taken as they are: its members'")
        out.append("// stores, its properties, its children (%d steps)." % len(inits[MANAGER]))
        out.append("class CInfoManager {")
        out.append("public:")
        out.append("    InfoBase base;  // 0x000 (the rest: not generated)")
        out.append("};")
        out.append("inline constexpr InfoStep kCInfoManagerInit[] = {")
        out += [step_line(st) for st in inits[MANAGER]]
        out.append("};")
        out.append('inline constexpr InfoClass kInfo_CInfoManager{"CInfoManager", "_ZTV12CInfoManager", InfoKind::kInfo, sizeof(CInfoManager), {}, {}, kCInfoManagerInit};')
        out.append("")
        table.append('    X(CInfoManager, "_ZN12CInfoManager10InitializeEv") \\')
    out.append("// X(Class): every info above.")
    out.append("#define INFO_CLASSES(X) \\")
    out += ["    X(%s) \\" % ident(m) for m in names + ([MANAGER] if manager else [])]
    out.append("    /* end of INFO_CLASSES */")
    out.append("")
    ctors, seen = [], set()
    for m in names:
        for sym in ("_ZN%sC2Ev" % m, "_ZN%sC1Ev" % m):
            a = X.S.get(sym)
            if a and a not in seen:
                seen.add(a)
                ctors.append('    X(%s, "%s") \\' % (ident(m), sym))
    out.append("// X(Class, default constructor symbol): every exported one of an info above (one per address).")
    out.append("#define INFO_CONSTRUCTORS(X) \\")
    out += ctors
    out.append("    /* end of INFO_CONSTRUCTORS */")
    out.append("")
    # the copies, destructors, assignments and moves of the infos without a container anywhere inside
    # (a container's copy copies its elements: not taken yet)
    def can(m, role):
        """Whether the natives can do `role` for class m: each container inside has what that needs (an
        array its element's layout; a map its element's and the guest functions; an assignment the
        guest's assign)."""
        sh = shapes[m]
        if sh.kind == "plain":
            return all(can(c.cls, role) for o, c in sh.children)
        e = container_elem(X, m)
        fns = container_fns(X, m)
        elem_ok = e[0] == "value" or (e[-1] in shapes and shapes[e[-1]].kind == "plain" and can(e[-1], role))
        if role in ("Assign", "MoveAssign"):
            return fns.get("assign") is not None
        if role in ("CtorCopy", "Move"):
            return elem_ok and (e[0] != "map" or fns.get("copy") is not None)
        return elem_ok and (e[0] != "map" or fns.get("destroy") is not None)  # Dtor
    roles = [("CtorCopy", "C2ERKS_"), ("CtorCopy", "C1ERKS_"), ("Dtor", "D2Ev"), ("Dtor", "D1Ev"), ("Assign", "aSERKS_"),
             ("Move", "C2EOS_"), ("Move", "C1EOS_"), ("MoveAssign", "aSEOS_")]
    rows = []
    for m in names:
        for role, suffix in roles:
            if not can(m, role):
                continue
            sym = "_ZN%s%s" % (m, suffix)
            a = X.S.get(sym)
            if a and a not in seen:
                seen.add(a)
                rows.append('    X(%s, %s, "%s") \\' % (ident(m), role, sym))
    out.append("// X(Class, role, symbol): the exported copy constructors, destructors, operator=s and moves of the")
    out.append("// infos above whose containers the natives can handle (one per address).")
    out.append("#define INFO_COPIES(X) \\")
    out += rows
    out.append("    /* end of INFO_COPIES */")
    out.append("")
    # IInfoBaseMap<K, T>::DeserializeChild of the maps whose element the natives build, move, destroy and
    # initialize (T an info with a layout, its containers handled), one per address
    maps = []
    for m in containers:
        e = container_elem(X, m)
        if e[0] != "map" or e[2] not in shapes or shapes[e[2]].kind != "plain":
            continue
        if not container_fns(X, m).get("destroy") or not all(can(e[2], r) for r in ("Move", "Dtor")):
            continue
        base = [x for x in X.chain[m] if x.startswith("12IInfoBaseMapI")][0]
        sym = "_ZN%s16DeserializeChildEPKN4Aska4ASON6AValue4AMapE" % base
        a = X.S.get(sym)
        if a and a not in seen:
            seen.add(a)
            maps.append('    X(%s, "%s") \\' % (ident(m), sym))
    out.append("// X(map container, symbol): IInfoBaseMap<K, T>::DeserializeChild for the maps whose T the natives")
    out.append("// construct, move into a node, destroy and initialize (one per address; the container names K and T).")
    out.append("#define INFO_MAP_DESERIALIZERS(X) \\")
    out += maps
    out.append("    /* end of INFO_MAP_DESERIALIZERS */")
    out.append("")
    out.append("// X(Class, Initialize symbol): every info above whose Initialize the natives take (one per address).")
    out.append("#define INFO_INITIALIZERS(X) \\")
    out += table
    out.append("    /* end of INFO_INITIALIZERS */")
    out.append("")
    out.append("}  // namespace soa::native::info")
    out.append("")
    out.append("#endif  // SOA_NATIVE_INFO_GEN_INFO_CLASSES_H")
    out.append("")
    return "\n".join(out)


# ---- the wire schema (--json): what the client reads from a reply, for the server's reply types ----

def probe_keys(X, R, m):
    """[(offset, key)] of the properties m's Initialize names, in its order, whatever else it does (CPlayerInfo's
    default text): the keys of a class whose Initialize isn't the shape the natives take."""
    try:
        evs = run_probe(X, R, m)
    except Exception:
        evs = list(R.ev)
    return [(e[1] - R.PROBE - 0x18, e[2]) for e in evs if e[0] == "name"]


def schema(lib_path, X, R, shapes, inits):
    """The client's reply shapes as data (server/src/api/gen/client_infos.json, read by tools/gen_server_infos.py):
    per info its fields in its Initialize's order (a property's ASON key and value type; a child's key, its
    pParseName, and class), per container its element (and a map's key width), and CInfoManager's children (the
    keys of a reply's `data`) and properties. A property no Initialize names has no key: the client never reads
    it (left out). An info without a layout has its keys only (types null)."""
    import json
    classes = {}

    def container(m, kind):
        e = container_elem(X, m)
        c = {"kind": kind}
        if e[0] == "value":
            c["value"] = e[1][0]
        else:
            c["elem"] = ident(e[-1])
            if e[0] == "map":
                c["key"] = "u32" if e[1] == 4 else "u64"
            # a container whose element is a container (a map of lists: no object of it is built, so
            # it has no shape): from its template arguments
            k = X.container(e[-1])
            if e[-1] not in shapes and k and ident(e[-1]) not in classes:
                classes[ident(e[-1])] = container(e[-1], k)
        return c
    for m in sorted(shapes, key=ident):
        sh = shapes[m]
        if sh.kind != "plain":
            classes[ident(m)] = container(m, sh.kind)
            continue
        props = {p[0]: p for p in sh.props}
        kids = dict(sh.children)
        if m in inits:
            steps = [(s[1], s[2] if s[0] == "prop" else None) for s in inits[m] if s[0] in ("prop", "child")]
        else:
            keyed = probe_keys(X, R, m)
            steps = keyed + [(o, None) for o in sorted(kids)]
            if not keyed:
                steps = [(p[0], None) for p in sh.props] + steps
        fields = []
        for off, key in steps:
            if off in props:
                p = props[off]
                if not key:
                    continue
                f = {"key": key, "type": "string" if p[1] == "string" else p[2]}
                if p[4]:
                    f["radian"] = True
                fields.append(f)
            elif off in kids:
                key = parse_name(X, kids[off].cls)
                if key:
                    fields.append({"key": key, "class": ident(kids[off].cls)})
        classes[ident(m)] = {"kind": "info", "fields": fields}
    manager = []
    for s in inits.get(MANAGER, []):
        c = X.manager_children.get(s[1]) if s[0] == "child" else None
        key = parse_name(X, c) if c else None
        if key:
            manager.append({"key": key, "class": ident(c)})
    # an info no object of which is built (no layout: CWorldMapCellInfo, CPartyInfo, ...): its keys from its
    # Initialize, their value types unknown (null: the server's reply_types.txt must name them)
    for m in sorted(X.chain):
        if m in shapes or m == MANAGER or X.container(m) or "_ZN%s10InitializeEv" % m not in X.S:
            continue
        keyed = probe_keys(X, R, m)
        if keyed:
            classes[ident(m)] = {"kind": "info", "untyped": True, "fields": [{"key": k, "type": None} for _, k in keyed]}
    classes = dict(sorted(classes.items()))
    doc = {"generated": "tools/gen_infos.py --json (the info classes' wire schema); do not edit",
           "lib": genlib.stamp(lib_path), "classes": classes, "manager": manager,
           # CInfoManager's own properties: the scalar keys of a reply's `data` (Time, PresentBoxCount, ...),
           # their types unknown (the manager has no layout)
           "manager_props": [k for _, k in probe_keys(X, R, MANAGER)]}
    return json.dumps(doc, indent=1, ensure_ascii=False) + "\n"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lib", default=genlib.lib_path())
    ap.add_argument("-o", "--out", default=DEFAULT_OUT)
    ap.add_argument("--json", default=DEFAULT_JSON, help="the wire schema's file (written with OUT)")
    ap.add_argument("--check", metavar="FILE")
    ap.add_argument("--check-json", metavar="FILE")
    ap.add_argument("--dump", metavar="CLASS")
    a = ap.parse_args()
    X, shapes, inits, unfit, never, unshaped, errors = generate(a.lib)
    if a.dump:
        m = a.dump if a.dump in X.chain else "%d%s" % (len(a.dump), a.dump)
        sh = shapes.get(m)
        print(m, hex(sh.size) if sh else "no layout", unfit.get(m, ""))
        if sh:
            for p in sh.props:
                print("  +%#05x %-6s %-5s N=%-4d %s" % (p[0], p[1], p[2] or "", p[3], "radian" if p[4] else ""))
            for o, c in sh.children:
                print("  +%#05x child %s (%#x)" % (o, cpp_name(c.cls), c.size))
        for s in inits.get(m, []):
            print("  step", s[0], hex(s[1]), *s[2:])
        return
    if errors:
        sys.exit("gen_infos: classes that don't fit:\n  " + "\n  ".join(errors[:60]))
    text = emit(a.lib, X, shapes, inits, unfit, never, unshaped)
    wire = schema(a.lib, X, X.runner, shapes, inits)
    if a.check or a.check_json:
        if a.check:
            have = open(a.check).read().split("\n")
            if have[2:] != text.split("\n")[2:]:
                sys.exit("%s differs from the generator's output for %s" % (a.check, a.lib))
        if a.check_json:
            import json
            have, want = json.load(open(a.check_json)), json.loads(wire)
            have.pop("lib", None), want.pop("lib", None)
            if have != want:
                sys.exit("%s differs from the generator's output for %s" % (a.check_json, a.lib))
        return
    os.makedirs(os.path.dirname(a.out), exist_ok=True)
    with open(a.out, "w") as f:
        f.write(text)
    os.makedirs(os.path.dirname(a.json), exist_ok=True)
    with open(a.json, "w", encoding="utf-8") as f:
        f.write(wire)
    print("%s written: %d layouts, %d Initialize step lists; %s" % (os.path.relpath(a.out, REPO), len(shapes), len(inits),
                                                                    os.path.relpath(a.json, REPO)))


if __name__ == "__main__":
    main()
