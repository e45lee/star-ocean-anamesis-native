#!/usr/bin/env python3
"""Per-subsystem scaffolding for the native rebuild (port/PLAN.md task 6; port/src/native/README.md
"Per-subsystem workflow").

A subsystem owns two folders and nothing else, so parallel branches each adding one never touch a
shared file:
  port/src/native/<s>/README.md          scope, types, natives, dependencies, RE notes
  port/src/native/<s>/<s>_layout.h       the recovered guest structs (types first), static_asserted
  port/src/native/<s>/subsystem.cmake    its own build settings (port/CMakeLists.txt includes every one)
  port/decomp/<s>/symbols.tsv            the guest functions it decompiled / typed / made native
  port/decomp/<s>/scope.txt              the demangled-name regexes it owns (the profile's ranking)
  port/decomp/<s>/types.json             <s>_layout.h's structs for Ghidra (export-types)
  port/decomp/<s>/<topic>.c              stamped decompiles (tools/decomp.sh --into <s>/<topic>)
Sources need no registration: port/CMakeLists.txt globs src/**/*.cpp in basename order (D8), and
natives register themselves (NATIVE_METHOD for a class's member, NATIVE_FUNCTION otherwise). Name the
files <s>_*.cpp. Recovered types are classes with their methods attached (port/PLAN.md task 6): the
guest's Class::Method is a member function of the recovered class, bound with NATIVE_METHOD
(native/common/native_method.h).

Usage:
  tools/subsystem.py new NAME [--title TEXT] [--scope REGEX]...   scaffold (never overwrites)
  tools/subsystem.py list                                         the index: symbols by status, structs, natives
  tools/subsystem.py check [NAME...]                              the files are there and well-formed; the
                                                                  layout header compiles alone; types.json current
  tools/subsystem.py skeleton NAME [--class C]... [--append]      class skeletons from symbols.tsv: the guest's
                                                                  Class::Method as members (ctors, virtuals in
                                                                  vtable order, the rest), to paste into
                                                                  <s>_layout.h (--append adds the missing ones)
  tools/subsystem.py export-types NAME...                         <s>_layout.h -> port/decomp/<s>/types.json
                                                                  (clang -fdump-record-layouts; each class's
                                                                  methods from symbols.tsv, for Ghidra's `this`)
Ghidra: tools/ghidra_apply_types.sh [NAME...] applies types.json + symbols.tsv to the Ghidra project
(the integrator, serially; agents never write the project).
Options: --root DIR (the repository; default this checkout).
"""
import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "port", "scripts"))
from profile_report import qualified_name, split_qualified  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NAME_RE = re.compile(r"^[a-z][a-z0-9_]*$")
SYMBOLS_COLUMNS = ["vaddr", "ghidra", "size", "symbol", "demangled", "topic", "status", "note"]
STATUSES = {"decompiled", "typed", "native", "tested", "skip"}
# Folders of src/native/ that predate the scaffolding (not subsystems of the rebuild).
LEGACY = {"api", "common", "restore", "ui"}


def paths(root, s):
    n = os.path.join(root, "port", "src", "native", s)
    d = os.path.join(root, "port", "decomp", s)
    return {
        "readme": os.path.join(n, "README.md"),
        "layout": os.path.join(n, f"{s}_layout.h"),
        "cmake": os.path.join(n, "subsystem.cmake"),
        "symbols": os.path.join(d, "symbols.tsv"),
        "scope": os.path.join(d, "scope.txt"),
        "types": os.path.join(d, "types.json"),
    }


def subsystems(root):
    d = os.path.join(root, "port", "decomp")
    if not os.path.isdir(d):
        return []
    return sorted(s for s in os.listdir(d) if os.path.isfile(os.path.join(d, s, "symbols.tsv")))


# ---- templates ----------------------------------------------------------------------------------

def readme_text(s, title):
    return f"""# `{s}`: {title}

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/{s}/scope.txt`](../../../decomp/{s}/scope.txt).
- Decompiles and the function list: [`port/decomp/{s}/`](../../../decomp/{s}/) (`symbols.tsv`; `tools/decomp.sh --into {s}/<topic>`).
- Types: [`{s}_layout.h`]({s}_layout.h); for Ghidra, `tools/subsystem.py export-types {s}` -> `port/decomp/{s}/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

| Class | Guest size | Found from (ctor, decompile) | Status |
|---|---|---|---|

## Natives

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
none yet.

## RE notes
"""


def layout_text(s, title):
    guard = f"SOA_NATIVE_{s.upper()}_LAYOUT_H"
    return f"""// {s}_layout.h: the guest data layouts of the `{s}` subsystem ({title}).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/{s}/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types {s}` turns the structs into port/decomp/{s}/types.json for Ghidra.
#ifndef {guard}
#define {guard}

#include <cstddef>
#include <cstdint>

namespace soa::native::{s} {{

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// The form (replace with the first recovered class; `tools/subsystem.py skeleton {s}` writes the
// member declarations from port/decomp/{s}/symbols.tsv):
//
// // CExample: guest size 0x18; layout from CExample::CExample (port/decomp/{s}/example.c).
// class CExample {{
// public:
//     // Guest methods as members (bound with NATIVE_METHOD, native/common/native_method.h):
//     void Ctor();                    // CExample::CExample()  _ZN8CExampleC2Ev (a C++ constructor can't be bound)
//     void Dtor();                    // CExample::~CExample() _ZN8CExampleD2Ev
//     u32 GetId() const;              // CExample::GetId() const
//     static CExample* Instance();    // a static member: bound with NATIVE_FUNCTION(sym, wrap<&CExample::Instance>(), ...)
//     // Virtuals in vtable order, as plain members: the object lives in guest memory with the guest's
//     // vtable, so no C++ `virtual` (a host vptr would change the layout); vtable is a field.
//     void Update(float dt);          // vtable slot 2  CExample::Update(float)
//
//     const void* vtable;  // 0x00: _ZTV8CExample + 0x10
//     u32 m_id;            // 0x08
//     u8 unk_0c[4];        // 0x0c: written by CExample::Reset, meaning unknown
//     u64 m_value;         // 0x10
// }};
// static_assert(offsetof(CExample, m_id) == 0x08);
// static_assert(offsetof(CExample, m_value) == 0x10);
// static_assert(sizeof(CExample) == 0x18);

}}  // namespace soa::native::{s}

#endif  // {guard}
"""


def cmake_text(s):
    return f"""# port/src/native/{s}/subsystem.cmake: build settings of the `{s}` subsystem only. port/CMakeLists.txt
# includes every port/src/native/*/subsystem.cmake (sorted) after defining the soa target, so a
# subsystem never edits the shared CMakeLists.txt.
# Sources need no listing: port/CMakeLists.txt globs src/**/*.cpp and links them in basename order
# (static-initializer order, D8); name this subsystem's files {s}_*.cpp so they sort together.
# Add here what is this subsystem's own, e.g. a host library at a clean boundary:
#   target_link_libraries(soa PRIVATE ZLIB::ZLIB)
"""


def scope_text(s, scopes):
    body = "\n".join(scopes) + ("\n" if scopes else "")
    return f"""# port/decomp/{s}/scope.txt: the guest functions the `{s}` subsystem owns, as Python regexes on the
# demangled name (one per line; `#` comments). tools/rebuild_queue.py ranks subsystems by these;
# tools/subsystem.py check warns about a function claimed by two subsystems.
{body}"""


# ---- new ----------------------------------------------------------------------------------------

def cmd_new(a):
    s = a.name
    if not NAME_RE.match(s):
        sys.exit(f"subsystem: bad name {s!r}: [a-z][a-z0-9_]* (it names a folder, a header and a namespace)")
    if s in LEGACY:
        sys.exit(f"subsystem: {s!r} is an existing src/native folder (not scaffolded)")
    for r in a.scope:
        re.compile(r)
    p = paths(a.root, s)
    files = {
        p["readme"]: readme_text(s, a.title),
        p["layout"]: layout_text(s, a.title),
        p["cmake"]: cmake_text(s),
        p["symbols"]: "\t".join(SYMBOLS_COLUMNS) + "\n",
        p["scope"]: scope_text(s, a.scope),
        p["types"]: json.dumps(types_doc(s, []), indent=1) + "\n",
    }
    existing = [f for f in files if os.path.exists(f)]
    if existing:
        sys.exit("subsystem: not overwriting " + ", ".join(os.path.relpath(f, a.root) for f in existing))
    for f, text in files.items():
        os.makedirs(os.path.dirname(f), exist_ok=True)
        with open(f, "w") as fh:
            fh.write(text)
        print("created", os.path.relpath(f, a.root))


# ---- export-types -------------------------------------------------------------------------------

PRIM = {
    "bool": ("int", False, 1), "char": ("int", True, 1), "signed char": ("int", True, 1),
    "unsigned char": ("int", False, 1), "short": ("int", True, 2), "unsigned short": ("int", False, 2),
    "int": ("int", True, 4), "unsigned int": ("int", False, 4), "long": ("int", True, 8),
    "unsigned long": ("int", False, 8), "long long": ("int", True, 8), "unsigned long long": ("int", False, 8),
    "float": ("float", None, 4), "double": ("float", None, 8), "char16_t": ("int", False, 2),
    "char32_t": ("int", False, 4), "wchar_t": ("int", True, 4),
}
for _n in (8, 16, 32, 64):
    for _p in ("", "std::"):
        PRIM[f"{_p}uint{_n}_t"] = ("int", False, _n // 8)
        PRIM[f"{_p}int{_n}_t"] = ("int", True, _n // 8)
    PRIM[f"u{_n}"] = ("int", False, _n // 8)
    PRIM[f"s{_n}"] = ("int", True, _n // 8)
PRIM["size_t"] = PRIM["std::size_t"] = ("int", False, 8)
PRIM["uintptr_t"] = PRIM["std::uintptr_t"] = ("int", False, 8)


def types_doc(s, structs):
    return {"subsystem": s, "generated_by": f"tools/subsystem.py export-types {s}",
            "header": f"port/src/native/{s}/{s}_layout.h", "structs": structs}


def dump_layouts(header, ns):
    """clang's record layouts of the structs the header declares in `ns`. (-fdump-record-layouts dumps
    the records whose layout was computed; the TU asks for each top-level struct's sizeof. The
    -complete variant would dump everything but crashes clang 18 on libstdc++'s <cstddef>.)"""
    clang = shutil.which("clang++") or shutil.which("clang++-18")
    if not clang:
        raise RuntimeError("clang++ not found (export-types reads clang's record layouts)")
    with open(header) as f:
        src = re.sub(r"//[^\n]*|/\*.*?\*/", "", f.read(), flags=re.S)
    names = set(re.findall(r"^\s*(?:struct|class|union)\s+(?:alignas\([^)]*\)\s+)?([A-Za-z_]\w*)\s*(?:final\s*)?[:{]",
                           src, re.M))
    # Class templates have no layout of their own: their instantiations do. A namespace-scope alias
    # `using TArrayU32 = TArray<u32>;` instantiates one; it is exported under clang's name for it
    # ("TArray<unsigned int>"; parse_layouts), so a header names the instantiations Ghidra should get.
    names -= set(re.findall(r"template\s*<[^{};]*?>\s*(?:struct|class|union)\s+([A-Za-z_]\w*)", src))
    names |= set(re.findall(r"^using\s+([A-Za-z_]\w*)\s*=\s*[^;]*<[^;]*;", src, re.M))
    names = sorted(names)
    with tempfile.NamedTemporaryFile("w", suffix=".cpp", delete=False) as f:
        f.write(f'#include "{os.path.abspath(header)}"\n')
        for n in names:
            f.write(f"static_assert(sizeof({ns}::{n}) > 0);\n")
        tu = f.name
    try:
        r = subprocess.run([clang, "-std=c++20", "-fsyntax-only", "-Xclang", "-fdump-record-layouts", tu],
                           capture_output=True, text=True)
    finally:
        os.unlink(tu)
    if r.returncode:
        raise RuntimeError(f"{header} doesn't compile on its own (clang++ -std=c++20):\n{r.stderr[-4000:]}")
    return r.stdout


FIELD_RE = re.compile(r"^\s*(\d+)(?::(\d+)-(\d+))? \|( +)(.*)$")


def parse_layouts(text, ns):
    """Structs of namespace `ns` from clang's -fdump-record-layouts output."""
    structs, cur, depth1 = [], None, None
    for line in text.splitlines():
        if line.startswith("*** Dumping AST Record Layout"):
            cur = None
            continue
        m = FIELD_RE.match(line)
        if m and cur is None:
            decl = m.group(5)
            mm = re.match(r"(?:struct|class|union) (.+?)(?: \(empty\))?$", decl)
            rest = mm.group(1)[len(ns) + 2:] if mm and mm.group(1).startswith(ns + "::") else None
            if rest is not None and m.group(1) == "0" and "::" not in re.sub(r"<.*>", "", rest):
                cur = {"name": short_type(rest, ns), "union": decl.startswith("union"), "fields": []}
                depth1 = len(m.group(4)) + 2
                structs.append(cur)
            else:
                cur = False  # another record: skip to the next dump
            continue
        if not cur:
            continue
        sm = re.match(r"^\s*\| \[sizeof=(\d+), dsize=\d+, align=(\d+)", line)
        if sm:
            cur["size"], cur["align"] = int(sm.group(1)), int(sm.group(2))
            cur = False
            continue
        if not m or len(m.group(4)) != depth1:
            continue
        off, decl = int(m.group(1)), m.group(5).strip()
        if m.group(2) is not None:
            cur["fields"].append({"offset": off, "name": decl.rsplit(" ", 1)[-1], "type": {"kind": "bitfield"},
                                  "comment": f"bits {m.group(2)}-{m.group(3)}: {decl}"})
            continue
        vm = re.match(r"\((.+) vtable pointer\)$", decl)
        if vm:
            cur["fields"].append({"offset": off, "name": "vtable", "type": {"kind": "ptr", "to": None}})
            continue
        bm = re.match(r"(?:struct|class) (.+?) \((?:primary |virtual )?base\)$", decl)
        if bm:
            base = short_type(bm.group(1), ns)
            base = base if "<" in base else base.rsplit("::", 1)[-1]
            cur["fields"].append({"offset": off, "name": "base_" + base, "type": {"kind": "struct", "name": base}})
            continue
        tm = re.match(r"(.*?)\s*([A-Za-z_]\w*)$", decl)
        if not tm:
            continue
        cur["fields"].append({"offset": off, "name": tm.group(2), "ctype": tm.group(1)})
    return [s for s in structs if "size" in s]


def short_type(name, ns):
    """A record name without this subsystem's namespace, also inside template arguments."""
    return re.sub(r"\b(?:struct|class|union|enum) ", "", name.replace(ns + "::", ""))


def type_of(ctype, ns, known):
    ctype = short_type(ctype, ns)
    ctype = re.sub(r"\b(const|volatile|struct|class|union|enum)\b", "", ctype).strip()
    ctype = re.sub(r"\s+", " ", ctype)
    am = re.match(r"^(.*)\[(\d+)\]$", ctype)
    if am:
        inner = type_of(am.group(1), ns, known)
        return {"kind": "array", "of": inner, "count": int(am.group(2))}
    if ctype.endswith("*") or ctype.endswith("&"):
        base = ctype[:-1].strip()
        short = base[len(ns) + 2:] if base.startswith(ns + "::") else base
        return {"kind": "ptr", "to": short if short in known else None}
    short = ctype[len(ns) + 2:] if ctype.startswith(ns + "::") else ctype
    if short in PRIM:
        k, signed, size = PRIM[short]
        t = {"kind": k, "size": size}
        if k == "int":
            t["signed"] = signed
        return t
    if short in known:
        return {"kind": "struct", "name": short}
    return {"kind": "bytes", "ctype": ctype}


def size_of(t, sizes):
    k = t["kind"]
    if k in ("int", "float"):
        return t["size"]
    if k == "ptr":
        return 8
    if k == "struct":
        return sizes.get(t["name"])
    if k == "array":
        e = size_of(t["of"], sizes)
        return None if e is None else e * t["count"]
    return t.get("size")


def export_structs(root, s):
    p = paths(root, s)
    ns = f"soa::native::{s}"
    structs = parse_layouts(dump_layouts(p["layout"], ns), ns)
    known = {st["name"] for st in structs}
    sizes = {st["name"]: st["size"] for st in structs}
    for st in structs:
        fs = st["fields"]
        for i, f in enumerate(fs):
            if "ctype" in f:
                f["type"] = type_of(f.pop("ctype"), ns, known)
            nxt = st["size"] if st["union"] or i + 1 == len(fs) else fs[i + 1]["offset"]
            sz = size_of(f["type"], sizes)
            if sz is not None and not st["union"]:
                sz = min(sz, max(nxt - f["offset"], 0))  # a base class's tail padding reused by the next field
            if sz is None:  # unknown type / bitfield: the bytes up to the next field
                sz = max(nxt - f["offset"], 0) if f["type"]["kind"] != "bitfield" else 0
                if f["type"]["kind"] == "bytes":
                    f["type"]["size"] = sz
            f["size"] = sz
    # Each class's methods (symbols.tsv, grouped by the demangled class name): Ghidra types their `this`.
    if os.path.exists(p["symbols"]):
        rows, _ = read_symbols(p["symbols"])
        by_short = {}
        for cls, ms in class_methods(rows).items():
            by_short.setdefault(cls.rsplit("::", 1)[-1], []).extend(ms)
        for st in structs:
            ms = [m for m in by_short.get(st["name"], []) if "thunk to " not in m[0]["demangled"]]  # thunks' this is adjusted
            if ms:
                st["methods"] = [{"ghidra": m[0]["ghidra"], "symbol": m[0]["symbol"], "name": m[1]}
                                 for m in sorted(ms, key=lambda m: int(m[0]["vaddr"], 16))]
    return types_doc(s, structs)


def cmd_export_types(a):
    for s in a.names:
        doc = export_structs(a.root, s)
        out = paths(a.root, s)["types"]
        with open(out, "w") as f:
            f.write(json.dumps(doc, indent=1) + "\n")
        print(f"{os.path.relpath(out, a.root)}: {len(doc['structs'])} struct(s)")


# ---- classes from symbols.tsv ---------------------------------------------------------------------

def split_params(sig):
    """'Foo::Bar(int, std::x<a, b>*) const' -> (['int', 'std::x<a, b>*'], const)."""
    i = sig.find("(")
    if i < 0:
        return [], False
    depth, cur, out, j = 0, "", [], i + 1
    while j < len(sig):
        ch = sig[j]
        if ch in "<(":
            depth += 1
        elif ch in ">)":
            if depth == 0 and ch == ")":
                break
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
        j += 1
    if cur.strip() and cur.strip() != "void":
        out.append(cur.strip())
    return out, sig[j + 1:].strip().startswith("const")


def class_methods(rows):
    """{class (qualified): [(row, method name, params, const)]} from symbols.tsv rows."""
    out = {}
    for r in rows:
        dem = r["demangled"]
        for pre in ("non-virtual thunk to ", "virtual thunk to "):
            if dem.startswith(pre):
                dem = dem[len(pre):]
        parts = split_qualified(qualified_name(dem))
        if len(parts) < 2:
            continue
        params, const = split_params(dem)
        out.setdefault("::".join(parts[:-1]), []).append((r, parts[-1], params, const))
    return out


PARAM_TYPES = {
    "int": "s32", "unsigned int": "u32", "bool": "bool", "float": "float", "double": "double", "long": "s64",
    "unsigned long": "u64", "long long": "s64", "unsigned long long": "u64", "short": "s16", "unsigned short": "u16",
    "char": "char", "signed char": "s8", "unsigned char": "u8", "char const*": "const char*", "char*": "char*",
    "void*": "void*", "void const*": "const void*",
}


def param_decl(t, short_names):
    """A guest parameter type as a host declaration type (guest classes by pointer -> void* unless declared here)."""
    t = t.strip()
    if t in PARAM_TYPES:
        return PARAM_TYPES[t]
    base = t.rstrip("*& ").replace(" const", "").strip()
    ind = t[len(t.rstrip("*&")):] if t.endswith(("*", "&")) else ""
    short = base.rsplit("::", 1)[-1]
    if ind and short in short_names and "<" not in base:
        return ("const " if " const" in t else "") + short + "*" * max(1, ind.count("*") + ind.count("&"))
    if ind:
        return "void*"
    return "u64"  # a by-value guest type: fix by hand


def mangled_class(sym):
    """'_ZN5CHome11GetAdjutantE...' -> '5CHome' (the nested name minus its last component), or None."""
    if not sym.startswith("_ZN"):
        return None
    i = 3
    while i < len(sym) and sym[i] in "KVr":
        i += 1
    comps = []
    while i < len(sym) and sym[i].isdigit():
        j = i
        while sym[j].isdigit():
            j += 1
        n = int(sym[i:j])
        comps.append(sym[i:j + n])
        i = j + n
    if i < len(sym) and sym[i] in "CD" and len(sym) > i + 1 and sym[i + 1].isdigit():  # ctor / dtor
        comps.append("ctor")
    if len(comps) < 2:
        return None
    cls = comps[:-1]
    return cls[0] if len(cls) == 1 else "N" + "".join(cls) + "E"


def vtable_slots(lib_path, mangled_cls):
    """[(slot, vaddr of the target)] of the class's vtable (_ZTV<class>), after offset-to-top and typeinfo."""
    try:
        from elftools.elf.elffile import ELFFile
        from elftools.elf.relocation import RelocationSection
    except ImportError:  # run it with .venv/bin/python for the vtables
        return []
    with open(lib_path, "rb") as f:
        elf = ELFFile(f)
        ds = elf.get_section_by_name(".dynsym")
        vt = ds.get_symbol_by_name("_ZTV" + mangled_cls)
        if not vt:
            return []
        a, size = vt[0]["st_value"], vt[0]["st_size"]
        rel = {}
        for sec in elf.iter_sections():
            if isinstance(sec, RelocationSection) and sec.name == ".rela.dyn":
                for r in sec.iter_relocations():
                    if a <= r["r_offset"] < a + size:
                        tgt = r["r_addend"]
                        if r["r_info_sym"]:
                            tgt = ds.get_symbol(r["r_info_sym"])["st_value"] + r["r_addend"]
                        rel[r["r_offset"]] = tgt
        return [((off - a) // 8 - 2, rel.get(off, 0)) for off in range(a + 16, a + size, 8)]


_ELF_NAMES = {}


def elf_name(lib_path, addr):
    """The demangled ELF symbol at addr (cxa_pure_virtual etc.), or the address."""
    if lib_path not in _ELF_NAMES:
        names = {}
        try:
            from elftools.elf.elffile import ELFFile
            with open(lib_path, "rb") as f:
                for sym in ELFFile(f).get_section_by_name(".dynsym").iter_symbols():
                    if sym.name and sym["st_value"]:
                        names.setdefault(sym["st_value"], sym.name)
        except (ImportError, OSError):
            pass
        _ELF_NAMES[lib_path] = names
    n = _ELF_NAMES[lib_path].get(addr)
    if not n:
        return f"{addr:#x}"
    r = subprocess.run(["c++filt", n], capture_output=True, text=True)
    return f"{r.stdout.strip() or n} ({addr:#x})"


def skeleton_blocks(rows, classes=None, lib_path=None):
    """[(class short name or None, text)]."""
    by_class = class_methods(rows)
    short_names = {c.rsplit("::", 1)[-1] for c in by_class}
    lib_path = lib_path or os.path.join(REPO, "work", "libSOA-3.7.0.so")
    out = []
    for cls in sorted(by_class):
        short = cls.rsplit("::", 1)[-1]
        if classes and short not in classes and cls not in classes:
            continue
        if "<" in cls:
            out.append((None, f"// {cls}: a template instantiation: recover its layout by hand ({len(by_class[cls])} method(s) in symbols.tsv)"))
            continue
        methods = by_class[cls]
        by_addr = {int(m[0]["vaddr"], 16): m for m in methods}
        mcls = next((mangled_class(m[0]["symbol"]) for m in methods if mangled_class(m[0]["symbol"])), None)
        slots = vtable_slots(lib_path, mcls) if mcls and os.path.exists(lib_path) else []
        lines = [f"// {cls}: guest methods from port/decomp/<s>/symbols.tsv; size and fields: fill in from the decompile.",
                 f"class {short} {{", "public:"]
        done = set()
        thunk_addrs = {int(m[0]["vaddr"], 16): m[0]["demangled"] for m in methods
                       if m[0]["demangled"].startswith(("non-virtual thunk", "virtual thunk"))}

        def decl(m, comment_extra=""):
            r, name, params, const = m
            ps = ", ".join(param_decl(t, short_names) for t in params)
            if name in (short, "~" + short):  # Itanium variants: C1 complete, C2 base, D0 deleting, D1 complete, D2 base
                v = re.search(r"([CD][012])E", r["symbol"])
                kind = v.group(1) if v else ("C1" if name == short else "D1")
                name_d = {"C1": "Ctor", "C2": "CtorBase", "C3": "Ctor", "D0": "DtorDelete", "D1": "Dtor", "D2": "DtorBase"}[kind]
                ret = "void"
            else:
                name_d, ret = name, "void"
            if not name_d.isidentifier() or name_d.startswith("operator"):
                return f"    // {r['demangled']}  {r['symbol']}: an operator: name it by hand"
            return (f"    {ret} {name_d}({ps}){' const' if const else ''};  // {comment_extra}{r['demangled']}  "
                    f"{r['symbol']}  (return type: from the decompile)")

        thunks = [m for m in methods if m[0]["demangled"].startswith(("non-virtual thunk", "virtual thunk"))]
        methods = [m for m in methods if m not in thunks]
        by_addr = {int(m[0]["vaddr"], 16): m for m in methods}
        for m in thunks:
            done.add(int(m[0]["vaddr"], 16))
        ctors = [m for m in methods if m[1] in (short, "~" + short)]
        if ctors:
            lines.append("    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)")
            for m in ctors:
                lines.append(decl(m))
                done.add(int(m[0]["vaddr"], 16))
        if slots:
            lines.append(f"    // Virtuals in vtable order (_ZTV{mcls}), as plain members: no C++ `virtual` (the guest's vtable is the field)")
            for slot, tgt in slots:
                if tgt in by_addr and tgt not in done:
                    lines.append(decl(by_addr[tgt], f"vtable slot {slot}: "))
                    done.add(tgt)
                elif tgt in by_addr:
                    lines.append(f"    // vtable slot {slot}: {by_addr[tgt][0]['demangled']} (declared above)")
                elif tgt in thunk_addrs:
                    lines.append(f"    // vtable slot {slot}: {thunk_addrs[tgt]} (a this-adjusting thunk of a member above)")
                elif tgt:
                    lines.append(f"    // vtable slot {slot}: {elf_name(lib_path, tgt)} (not in symbols.tsv: inherited, or not decompiled yet)")
        for m in thunks:
            lines.append(f"    // {m[0]['demangled']}  {m[0]['symbol']}: a this-adjusting thunk (bind it to the same member)")
        rest = [m for m in methods if int(m[0]["vaddr"], 16) not in done]
        if rest:
            lines.append("    // Methods (a static one: declare it static and bind it with NATIVE_FUNCTION(sym, wrap<&C::F>(), ...))")
            for m in rest:
                lines.append(decl(m))
        lines += ["", "    const void* vtable;  // 0x00 (if the class has one)" if slots else "    // fields at the guest's offsets",
                  "    // ... fields, unknown bytes as u8 unk_XX[n] ...", "};",
                  f"// static_assert(offsetof({short}, ...) == 0x..);", f"// static_assert(sizeof({short}) == 0x..);"]
        out.append((short, "\n".join(lines)))
    return out


def cmd_skeleton(a):
    p = paths(a.root, a.name)
    rows, probs = read_symbols(p["symbols"])
    if probs:
        sys.exit("symbols.tsv: " + "; ".join(probs))
    blocks = skeleton_blocks(rows, set(a.cls) if a.cls else None, a.lib)
    if not a.append:
        print("\n\n".join(t for _, t in blocks))
        return
    with open(p["layout"]) as f:
        hdr = f.read()
    keep = [t for short, t in blocks
            if short and not re.search(rf"^\s*(class|struct) {short}\b", hdr, re.M)]  # declared already: never overwritten
    close = f"}}  // namespace soa::native::{a.name}"
    if close not in hdr:
        sys.exit(f"{p['layout']}: no '{close}' line to insert before")
    hdr = hdr.replace(close, "\n\n".join(keep) + "\n\n" + close if keep else close)
    with open(p["layout"], "w") as f:
        f.write(hdr)
    print(f"{os.path.relpath(p['layout'], a.root)}: {len(keep)} class skeleton(s) added")


# ---- list / check -------------------------------------------------------------------------------

def read_symbols(path):
    rows, problems = [], []
    with open(path) as f:
        lines = f.read().splitlines()
    if not lines or lines[0].split("\t") != SYMBOLS_COLUMNS:
        problems.append(f"header must be: {' '.join(SYMBOLS_COLUMNS)}")
        return rows, problems
    seen = set()
    last = -1
    for n, line in enumerate(lines[1:], 2):
        if not line.strip():
            continue
        cols = line.split("\t")
        if len(cols) != len(SYMBOLS_COLUMNS):
            problems.append(f"line {n}: {len(cols)} columns, want {len(SYMBOLS_COLUMNS)}")
            continue
        row = dict(zip(SYMBOLS_COLUMNS, cols))
        try:
            va = int(row["vaddr"], 16)
        except ValueError:
            problems.append(f"line {n}: vaddr {row['vaddr']!r}")
            continue
        if va in seen:
            problems.append(f"line {n}: vaddr {va:#x} twice")
        if va < last:
            problems.append(f"line {n}: not sorted by vaddr")
        if row["status"] not in STATUSES:
            problems.append(f"line {n}: status {row['status']!r} (one of {', '.join(sorted(STATUSES))})")
        seen.add(va)
        last = va
        rows.append(row)
    return rows, problems


def read_scope(path):
    out = []
    if os.path.exists(path):
        with open(path) as f:
            for line in f:
                line = line.strip()
                if line and not line.startswith("#"):
                    out.append(line)
    return out


def count_natives(root, s):
    d = os.path.join(root, "port", "src", "native", s)
    n = 0
    for dp, _, fs in os.walk(d):
        for f in fs:
            if f.endswith(".cpp"):
                with open(os.path.join(dp, f), errors="replace") as fh:
                    n += len(re.findall(r"^\s*NATIVE_(?:FUNCTION|ROUTE_FUNCTION)\w*\(", fh.read(), re.M))
    return n


def cmd_list(a):
    subs = subsystems(a.root)
    if not subs:
        print("no scaffolded subsystems (tools/subsystem.py new NAME)")
        return
    print(f"{'subsystem':16} {'symbols':>7} {'native':>6} {'structs':>7} {'natives':>7}  title")
    for s in subs:
        p = paths(a.root, s)
        rows, _ = read_symbols(p["symbols"])
        nat = sum(r["status"] in ("native", "tested") for r in rows)
        try:
            with open(p["types"]) as f:
                nst = len(json.load(f)["structs"])
        except (OSError, ValueError, KeyError):
            nst = 0
        title = ""
        if os.path.exists(p["readme"]):
            with open(p["readme"]) as f:
                m = re.match(r"# `[^`]*`: (.*)", f.readline())
                title = m.group(1) if m else ""
        print(f"{s:16} {len(rows):7} {nat:6} {nst:7} {count_natives(a.root, s):7}  {title}")


def cmd_check(a):
    subs = a.names or subsystems(a.root)
    bad = 0
    claims = {}
    for s in subs:
        p = paths(a.root, s)
        probs = []
        for k in ("readme", "layout", "cmake", "symbols", "scope", "types"):
            if not os.path.exists(p[k]):
                probs.append(f"missing {os.path.relpath(p[k], a.root)}")
        if os.path.exists(p["symbols"]):
            probs += read_symbols(p["symbols"])[1]
        for r in read_scope(p["scope"]):
            try:
                re.compile(r)
            except re.error as e:
                probs.append(f"scope.txt: {r!r}: {e}")
            claims.setdefault(r, []).append(s)
        if os.path.exists(p["layout"]) and not a.no_compile:
            try:
                doc = export_structs(a.root, s)
                with open(p["types"]) as f:
                    if json.load(f) != json.loads(json.dumps(doc)):
                        probs.append(f"types.json is stale: tools/subsystem.py export-types {s}")
            except RuntimeError as e:
                probs.append(str(e))
            except (OSError, ValueError) as e:
                probs.append(f"types.json: {e}")
        print(f"{'FAIL' if probs else 'ok  '} {s}")
        for pr in probs:
            print("     ", pr)
        bad += bool(probs)
    for r, owners in claims.items():
        if len(owners) > 1:
            print(f"warning: scope {r!r} claimed by {', '.join(owners)}")
    if not subs:
        print("ok (no scaffolded subsystems)")
    sys.exit(1 if bad else 0)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--root", default=REPO)
    sp = ap.add_subparsers(dest="cmd", required=True)
    n = sp.add_parser("new")
    n.add_argument("name")
    n.add_argument("--title", default="(describe)")
    n.add_argument("--scope", action="append", default=[], help="a demangled-name regex it owns (repeatable)")
    sp.add_parser("list")
    c = sp.add_parser("check")
    c.add_argument("names", nargs="*")
    c.add_argument("--no-compile", action="store_true", help="skip the layout header compile and types.json check")
    k = sp.add_parser("skeleton")
    k.add_argument("name")
    k.add_argument("--class", dest="cls", action="append", default=[], help="only this class (repeatable)")
    k.add_argument("--append", action="store_true", help="add the classes not declared yet to <s>_layout.h")
    k.add_argument("--lib", help="the ELF for the vtables (default work/libSOA-3.7.0.so)")
    e = sp.add_parser("export-types")
    e.add_argument("names", nargs="+")
    a = ap.parse_args()
    {"new": cmd_new, "list": cmd_list, "check": cmd_check, "export-types": cmd_export_types, "skeleton": cmd_skeleton}[a.cmd](a)


if __name__ == "__main__":
    main()
