"""Generate port/src/native/params/gen/parameter_elements.inc from libSOA.so.

The master-record element types (CMasterParameter*Element & co.) each get one instance of
CMasterParameterBaseSqlite::DeserializeMsgPack<T>. This lists them with the symbols of their
lifecycle functions (several are inlined in some types and have no symbol: empty strings) and
the record size, read from the unordered_map<u32, T> node allocation in DeserializeMsgPack<T>
(node = {next, hash, u32 key, T} = 0x18 + sizeof(T)):

  ELEMENT(i, "T", sizeof, "DeserializeMsgPack<T>", "_ZTV T", "T::T()", "T::Initialize()",
          "T::T(const T&)", "T::operator=(const T&)", "T::~T() (D2)", "T::~T() (D0, deleting)",
          "vtable ~T() leaves at +0 (a base element's when T derives from one)")

  CONNECTOR(i, "QueryToMsgPack(mode, key, ...)", "QueryToMsgPack(sql, ...)", "queries[]", "table name")
                                        CSimpleSqliteConnector<E, S> instances
  SIMPLE_DESERIALIZE_PARAMETER(i, "Simple<T>::DeserializeParameter(map&, const AArray*)", "T")
  SIMPLE_FROM_ID_LIST(i, "Simple<T>::ParameterFromIdList(...)", "T")
  SIMPLE_RELEASE_THUNK("sym")          non-virtual thunks to Simple<T>::ReleaseParameter
  SIMPLE_QUERY_MAP(i, "Simple<T>::ParameterByQuery(const char*, unordered_map<u32, T>&, QueryParam*, u32)", "T")
                                        the instances with the common code shape

The property layout of each type (offsets, property kinds, names and defaults) is dumped from
the running game by the param/elements/layout test into parameter_layouts.inc.

Usage: .venv/bin/python tools/gen_loader_tables.py > port/src/native/params/gen/parameter_elements.inc
"""
import re
import sys

from capstone import CS_ARCH_ARM64, CS_MODE_ARM, Cs
import genlib  # (before a2c / elfinfo: the default lib is 3.7.0's; tools/genlib.py)
from elfinfo import lib

L = lib()
md = Cs(CS_ARCH_ARM64, CS_MODE_ARM)
dyn = {s.name: s["st_value"] for s in L.elf.get_section_by_name(".dynsym").iter_symbols() if s.name and s["st_value"]}
ALLOC = "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj"


def node_size(sym):
    """The size DeserializeMsgPack<T> allocates its unordered_map<u32, T> nodes with: the first
    constant of at least 0x40 moved into x0 right before a call to the STL allocator (smaller
    ones are other maps' nodes; bucket arrays and strings have computed sizes). Some instances
    call an out-of-line insert helper, which follows them in the binary: hence the long scan."""
    a = dyn[sym]
    last_mov = None
    for ins in md.disasm(L.read(a, 0x1800), a):
        m = re.match(r"(w0|x0), #(0x[0-9a-f]+|\d+)$", ins.op_str)
        if ins.mnemonic == "mov" and m:
            last_mov = (ins.address, int(m.group(2), 0))
        if ins.mnemonic == "bl":
            t = int(ins.op_str[1:], 16)
            if (L.plt.get(t) or L.by_addr.get(t)) == ALLOC and last_mov and ins.address - last_mov[0] <= 16 and last_mov[1] >= 0x40:
                return last_mov[1]
    return None


def size_from_allocations(t):
    """sizeof(T) from other template code: new(nothrow) T in Simple<T>::ParameterByQuery, or the
    make_shared block (0x18 + sizeof(T)) in Simple/Category<T>::pParameterFromHash."""
    tt = "%d%s" % (len(t), t)
    cands = [("_ZNK33CMasterParameterBaseSqlite_SimpleI%sE16ParameterByQueryEPKcPN4Aska5Yayoi10QueryParamEj" % tt, "_ZnwmRKSt9nothrow_t", 0),
             ("_ZNK33CMasterParameterBaseSqlite_SimpleI%sE18pParameterFromHashEj" % tt, "_Znwm", 0x18),
             ("_ZNK35CMasterParameterBaseSqlite_CategoryI%sE18pParameterFromHashEPKcj" % tt, "_Znwm", 0x18)]
    for sym, fn, extra in cands:
        if sym not in dyn:
            continue
        a = dyn[sym]
        last_mov = None
        for ins in md.disasm(L.read(a, 0x1000), a):
            m = re.match(r"(w0|x0), #(0x[0-9a-f]+|\d+)$", ins.op_str)
            if ins.mnemonic == "mov" and m:
                last_mov = (ins.address, int(m.group(2), 0))
            if ins.mnemonic == "bl":
                tg = int(ins.op_str[1:], 16)
                if (L.plt.get(tg) or L.by_addr.get(tg)) == fn and last_mov and ins.address - last_mov[0] <= 16 and last_mov[1] - extra >= 0x40:
                    return last_mov[1] - extra
    return None


def dtor_vtable(t, depth=0):
    """The vtable a T::~T() (D2) leaves at +0: its own, unless it ends by tail-calling a base
    element's destructor (then that one's)."""
    n = "_ZN%d%sD2Ev" % (len(t), t)
    if n not in dyn or depth > 4:
        return "_ZTV%d%s" % (len(t), t)
    a = dyn[n]
    for ins in md.disasm(L.read(a, 0x4000), a):
        if ins.mnemonic == "b" and ins.op_str.startswith("#"):
            tn = L.plt.get(int(ins.op_str[1:], 16)) or L.by_addr.get(int(ins.op_str[1:], 16)) or ""
            m = re.match(r"^_ZN(\d+)(\w+)D2Ev$", tn)
            if m and m.group(2)[:int(m.group(1))] != t and "Element" in m.group(2):
                return dtor_vtable(m.group(2)[:int(m.group(1))], depth + 1)
        if ins.mnemonic in ("ret", "b"):
            break
    return "_ZTV%d%s" % (len(t), t)


rows = []
pat = re.compile(r"^_ZNK26CMasterParameterBaseSqlite18DeserializeMsgPackI(\d+)")
for name in sorted(dyn):
    m = pat.match(name)
    if not m:
        continue
    n = int(m.group(1))
    t = name[m.end():m.end() + n]
    p = "_ZN%d%s" % (n, t)
    size = node_size(name)
    if size is None:
        alt = size_from_allocations(t)
        if alt is None:
            print("// %s: no node allocation found" % t, file=sys.stderr)
            continue
        size = alt + 0x18

    def s(x):
        return x if x in dyn else ""
    rows.append((t, size - 0x18, name, s("_ZTV%d%s" % (n, t)), s(p + "C2Ev"), s(p + "10InitializeEv"), s(p + "C2ERKS_"),
                 s(p + "aSERKS_"), s(p + "D2Ev"), s(p + "D0Ev"), dtor_vtable(t)))


def shape(sym):
    """Machine code with call targets, branch targets and GOT/page references normalised: equal
    shapes are the same template code over different types."""
    import hashlib
    a = dyn[sym]
    toks = []
    pages = set()
    for ins in md.disasm(L.read(a, 0x800), a):
        op = ins.op_str
        if ins.mnemonic == "adrp":
            pages.add(op.split(",")[0])
        if ins.mnemonic in ("bl", "b") and op.startswith("#"):
            t = int(op[1:], 16)
            op = "CALL" if ins.mnemonic == "bl" else ("rel%+d" % (t - a) if a <= t < a + 0x800 else "TAIL")
        elif ins.mnemonic.startswith("b.") or ins.mnemonic in ("cbz", "cbnz", "tbz", "tbnz"):
            op = re.sub(r"#0x[0-9a-f]+$", lambda m: "rel%+d" % (int(m.group(0)[1:], 16) - a), op)
        elif ins.mnemonic == "adrp":
            op = re.sub(r"#0x[0-9a-f]+", "PAGE", op)
        elif ins.mnemonic in ("ldr", "add") and re.match(r"x\d+, \[?(x\d+), #0x[0-9a-f]+\]?$", op) and \
                re.match(r"x\d+, \[?(x\d+)", op).group(1) in pages:
            pages.discard(re.match(r"x\d+, \[?(x\d+)", op).group(1))
            op = re.sub(r"#0x[0-9a-f]+", "PAGEOFF", op)
        toks.append(ins.mnemonic + " " + op)
        if ins.mnemonic == "ret":
            break
    return hashlib.md5("\n".join(toks).encode()).hexdigest()


# Simple<T>::ParameterByQuery(const char*, unordered_map<u32, T>&, QueryParam*, u32): the common
# shape (the thin wrapper: IsLoadable, Open, QueryToMsgPack(sql), DeserializeMsgPack<T>, Close).
qm = re.compile(r"^_ZNK33CMasterParameterBaseSqlite_SimpleI(\d+)(\w+?)E16ParameterByQueryEPKcRN9Framework16CSTLUnorderedMap")
ref = shape("_ZNK33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE16ParameterByQueryEPKcRN9Framework16CSTLUnorderedMapIjS0_"
            "NSt6__ndk14hashIjEENS6_8equal_toIjEEEEPN4Aska5Yayoi10QueryParamEj")
query_map = []
for name in sorted(dyn):
    m = qm.match(name)
    if m and shape(name) == ref:
        query_map.append((name, m.group(2)[:int(m.group(1))]))


# CSimpleSqliteConnector<E, S>: per connector, its QueryToMsgPack(mode, key, ...) and
# QueryToMsgPack(sql, ...) symbols, the static queries[] array QueryToResultObject(mode) uses and
# the table name BuildQuery substitutes for __TABLE_NAME__.
def connector_info(qro):
    a = dyn[qro]
    md.detail = False
    queries = build = None
    page = {}
    for ins in md.disasm(L.read(a, 0x100), a):
        m = re.match(r"(x\d+), #(0x[0-9a-f]+)$", ins.op_str)
        if ins.mnemonic == "adrp" and m:
            page[m.group(1)] = int(m.group(2), 16)
        m = re.match(r"(x\d+), \[(x\d+), #(0x[0-9a-f]+)\]$", ins.op_str)
        if ins.mnemonic == "ldr" and m and m.group(2) in page:
            n = L.got2name.get(page[m.group(2)] + int(m.group(3), 16), "")
            if "GetQuery" in n and "queries" in n:
                queries = n
        if ins.mnemonic == "bl":
            n = L.plt.get(int(ins.op_str[1:], 16)) or L.by_addr.get(int(ins.op_str[1:], 16)) or ""
            if "10BuildQuery" in n:
                build = n
        if ins.mnemonic == "ret":
            break
    if not queries or not build:
        return None
    b = dyn[build]
    movs = set()
    taddr = None
    page = {}
    for ins in md.disasm(L.read(b, 0x80), b):
        m = re.match(r"w\d+, #(0x[0-9a-f]+|\d+)$", ins.op_str)
        if ins.mnemonic == "mov" and m:
            movs.add(int(m.group(1), 0))
        m = re.match(r"(x\d+), #(0x[0-9a-f]+)$", ins.op_str)
        if ins.mnemonic == "adrp" and m:
            page[m.group(1)] = int(m.group(2), 16)
        m = re.match(r"(x\d+), (x\d+), #(0x[0-9a-f]+)$", ins.op_str)
        if ins.mnemonic == "add" and m and m.group(2) in page and taddr is None:
            taddr = page[m.group(2)] + int(m.group(3), 16)
    if taddr is None:
        return None
    # the table name: the string loaded next to its length (the literal may be merged into a
    # longer one, so take the longest "master_..." word among the constant lengths)
    names = [L.read(taddr, n).decode(errors="replace") for n in movs if 0 < n < 128]
    names = [t for t in names if re.match(r"^master_\w+$", t)]
    if not names:
        return None
    table = max(names, key=len)
    return queries, table


conn_rows = []
# two manglings: CSimpleSqliteConnector<E, TEntity_Slave<SQLiteDriver, E, NoCache>> and <E, E>
families = [("19QueryToResultObjectEjPNS3_10QueryParamEjRNS3_13TEntityObjectIS5_EE",
             "14QueryToMsgPackEjjRNS2_12TSharedArrayIaEERl", "14QueryToMsgPackEPKcRNS2_12TSharedArrayIaEERlPNS3_10QueryParamEj"),
            ("19QueryToResultObjectEjPN4Aska5Yayoi10QueryParamEjRNS4_13TEntityObjectINS4_12SQLiteDriverEEE",
             "14QueryToMsgPackEjjRN4Aska12TSharedArrayIaEERl", "14QueryToMsgPackEPKcRN4Aska12TSharedArrayIaEERlPNS5_5Yayoi10QueryParamEj")]
for name in sorted(dyn):
    if not name.startswith("_ZN22CSimpleSqliteConnectorI"):
        continue
    for qro, qm_s, qs_s in families:
        if not name.endswith("E" + qro):
            continue
        pre = name[:-len(qro)]
        qm, qs = pre + qm_s, pre + qs_s
        info = connector_info(name)
        if info is None or qm not in dyn or qs not in dyn:
            print("// %s: connector not recognised" % pre, file=sys.stderr)
            continue
        conn_rows.append((qm, qs, info[0], info[1]))


# non-virtual thunks to Simple<T>::ReleaseParameter (IParameter base at +0x10): sub x0, #0x10; b.
release_thunks = []
for name in sorted(dyn):
    if re.match(r"^_ZThn16_N33CMasterParameterBaseSqlite_SimpleI.*E16ReleaseParameterEPKc$", name):
        ins = list(md.disasm(L.read(dyn[name], 8), dyn[name]))
        target = "_ZN" + name[len("_ZThn16_N"):]
        if len(ins) == 2 and ins[0].op_str == "x0, x0, #0x10" and ins[1].mnemonic == "b" and \
                target in (L.plt.get(int(ins[1].op_str[1:], 16)), L.by_addr.get(int(ins[1].op_str[1:], 16))):
            release_thunks.append(name)


# Simple<T>::DeserializeParameter(unordered_map<u32, shared_ptr<T>>&, const AArray*)
deser_param = []
dp = re.compile(r"^_ZN33CMasterParameterBaseSqlite_SimpleI(\d+)(\w+?)E20DeserializeParameterERN9Framework16CSTLUnorderedMapIjNSt6__ndk1"
                r"10shared_ptrIS0_EENS4_4hashIjEENS4_8equal_toIjEEEEPKN4Aska4ASON6AValue6AArrayE$")
for name in sorted(dyn):
    m = dp.match(name)
    if m:
        deser_param.append((name, m.group(2)[:int(m.group(1))]))


# Simple<T>::ParameterFromIdList(const vector<u32>&, unordered_map<u32, T>&, const char* column)
from_id_list = []
fl = re.compile(r"^_ZNK33CMasterParameterBaseSqlite_SimpleI(\d+)(\w+?)E19ParameterFromIdListERKN9Framework10CSTLVectorIjEERNS2_16"
                r"CSTLUnorderedMapIjS0_NSt6__ndk14hashIjEENS8_8equal_toIjEEEEPKc$")
for name in sorted(dyn):
    m = fl.match(name)
    if m:
        from_id_list.append((name, m.group(2)[:int(m.group(1))]))

print("// Generated by tools/gen_loader_tables.py from libSOA.so -- do not edit.")
print("// " + genlib.stamp())
print("#ifdef ELEMENT")
for i, r in enumerate(rows):
    print('ELEMENT(%d, "%s", %#x, "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s", "%s")' % ((i,) + r))
print("#endif")
print("#ifdef CONNECTOR")
for i, r in enumerate(conn_rows):
    print('CONNECTOR(%d, "%s", "%s", "%s", "%s")' % ((i,) + r))
print("#endif")
print("#ifdef SIMPLE_DESERIALIZE_PARAMETER")
for i, (n, t) in enumerate(deser_param):
    print('SIMPLE_DESERIALIZE_PARAMETER(%d, "%s", "%s")' % (i, n, t))
print("#endif")
print("#ifdef SIMPLE_FROM_ID_LIST")
for i, (n, t) in enumerate(from_id_list):
    print('SIMPLE_FROM_ID_LIST(%d, "%s", "%s")' % (i, n, t))
print("#endif")
print("#ifdef SIMPLE_RELEASE_THUNK")
for n in release_thunks:
    print('SIMPLE_RELEASE_THUNK("%s")' % n)
print("#endif")
print("#ifdef SIMPLE_QUERY_MAP")
for i, (n, t) in enumerate(query_map):
    print('SIMPLE_QUERY_MAP(%d, "%s", "%s")' % (i, n, t))
print("#endif")
