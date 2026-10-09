#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
r"""Generate the server's request argument structs: server/src/api/gen/request_args.h, one `*Args` struct per
method (or group of methods with one signature) and its `from(const Request&)`, from two inputs
(server/src/api/gen/README.md "Requests"):

  1. the wire: server/net/gen/wire_decode.inc (tools/api_wire.py, from docs/api-wire.txt, the request
     layouts measured on the client's serializers): each method's arguments after the RequestHeader, which
     the decoder maps positionally into a Request (integers -> ints, str[N] / blob -> strs, vec64 / vec32 ->
     vecs; a DeviceType `dev` is dropped);
  2. the server: server/src/api/gen/request_args.txt, the arguments' names and the types the handlers read
     them as. A `#` line before a struct is its comment, copied.

request_args.txt, one struct per line:
    METHOD[, METHOD...][ as NAME]: FIELD...
  NAME: the struct (default METHODArgs). Every METHOD must have the same layout.
  FIELD, in the request's order:
    NAME[:TYPE][N][?][=DEFAULT]
      TYPE   u32 (default for an integer up to 32 bits), u64 (default for u64), s32, str (a string or
             blob: default), u64vec (a vec64: default), or an id type of soaserver/ids.h (CharacterUid,
             ItemUid, RoleId, ...: constructed from the integer)
      [N]    N consecutive integers into an array (`skill:u64[3]`)
      ?      0 means none: std::optional<TYPE> (ids.h nonzero)
      =D     the value when the request is short (default 0 / "" / empty)
    -        an argument the handlers don't read (skipped)
    ...      the rest of the arguments aren't read
The generator checks the fields against the layout: as many integers, strings and vectors (unless `...`).

Usage:
  tools/gen_request_args.py            # write the header
  tools/gen_request_args.py --check    # exit 1 if it differs (T0 `generated`)
"""
import argparse
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
GEN = os.path.join(REPO, "server/src/api/gen")
SPEC = os.path.join(GEN, "request_args.txt")
OUT = os.path.join(GEN, "request_args.h")
DECODER = os.path.join(REPO, "server/net/gen/wire_decode.inc")

INT_TOKENS = {"u8", "s8", "u16", "s16", "u32", "s32", "f32", "u64"}
SCALARS = {"u32": "u32", "u64": "u64", "s32": "s32", "str": "std::string", "u64vec": "std::vector<u64>"}


TOKENS = {}  # server method -> its layout as the decoder table spells it


class Fail(Exception):
    pass


def layouts():
    """{server method: [kind per argument: 'int' / 'int64' / 'str' / 'vec']} from the decoder table."""
    out = {}
    for ln in open(DECODER, encoding="utf-8"):
        m = re.match(r'^\s*\{"(\w+)", "(\w+)", 0x[0-9a-f]+u, \w+, "([^"]*)"', ln)
        if not m:
            continue
        kinds = []
        for t in m.group(3).split():
            if t == "dev":
                continue
            if t in INT_TOKENS:
                kinds.append("int64" if t == "u64" else "int")
            elif t.startswith("str[") or t == "blob":
                kinds.append("str")
            elif t in ("vec64", "vec32"):
                kinds.append("vec")
            else:
                raise Fail("%s: layout token %s" % (m.group(2), t))
        out[m.group(2)] = kinds
        TOKENS[m.group(2)] = m.group(3) or "(none)"
    return out


class Field:
    def __init__(self, tok, where):
        self.skip = tok == "-"
        if self.skip:
            self.kind, self.count = None, 1
            return
        m = re.match(r"^([a-z_]\w*)(?::(\w+))?(?:\[(\d+)\])?(\?)?(?:=(.+))?$", tok)
        if not m:
            raise Fail("%s: bad field %r" % (where, tok))
        self.name, self.type, n, self.optional, self.default = m.group(1), m.group(2), m.group(3), m.group(4) == "?", m.group(5)
        self.count = int(n) if n else 1
        if self.type in ("str",):
            self.kind = "str"
        elif self.type == "u64vec":
            self.kind = "vec"
        else:
            self.kind = "int"
        if self.count > 1 and (self.kind != "int" or self.optional):
            raise Fail("%s.%s: an array is of plain integers" % (where, self.name))

    def resolve(self, kinds, where):
        """The C++ type, from the layout's argument kinds this field takes."""
        if self.kind == "int":
            if any(k not in ("int", "int64") for k in kinds):
                raise Fail("%s.%s: an integer field on a %s argument" % (where, self.name, kinds))
            t = self.type or ("u64" if kinds[0] == "int64" else "u32")
        else:
            if any(k != self.kind for k in kinds):
                raise Fail("%s.%s: a %s field on a %s argument" % (where, self.name, self.kind, kinds))
            t = self.type or ("str" if self.kind == "str" else "u64vec")
        self.cpp = SCALARS.get(t, t)
        self.id_type = t not in SCALARS


def parse(spec, lays):
    structs, doc = [], []
    for n, ln in enumerate(open(spec, encoding="utf-8"), 1):
        ln = ln.rstrip("\n")
        if not ln.strip():
            doc = []
            continue
        if ln.startswith("#"):
            doc.append(ln[2:] if ln.startswith("# ") else ln[1:])
            continue
        m = re.match(r"^([\w, ]+?)(?: as (\w+))?:\s*(.*)$", ln)
        if not m:
            raise Fail("request_args.txt:%d: not METHOD[, METHOD...][ as NAME]: FIELD..." % n)
        methods = [x.strip() for x in m.group(1).split(",")]
        name = m.group(2) or methods[0] + "Args"
        toks = m.group(3).split()
        rest = bool(toks) and toks[-1] == "..."
        if rest:
            toks = toks[:-1]
        fields = [Field(t, name) for t in toks]
        for meth in methods:
            if meth not in lays:
                raise Fail("request_args.txt:%d: %s isn't in wire_decode.inc" % (n, meth))
        lay = lays[methods[0]]
        for meth in methods[1:]:
            if lays[meth] != lay:
                raise Fail("request_args.txt:%d: %s and %s have different layouts" % (n, methods[0], meth))
        # each field takes the next arguments of its kind
        at = {"int": 0, "str": 0, "vec": 0}
        by_kind = {"int": [k for k in lay if k.startswith("int")], "str": [k for k in lay if k == "str"],
                   "vec": [k for k in lay if k == "vec"]}
        pos = 0
        for f in fields:
            if f.skip:
                if pos >= len(lay):
                    raise Fail("request_args.txt:%d: %s: `-` past the arguments" % (n, name))
                k = "int" if lay[pos].startswith("int") else lay[pos]
                f.kind, f.index = k, at[k]
                at[k] += 1
                pos += 1
                continue
            f.index = at[f.kind]
            got = by_kind[f.kind][f.index:f.index + f.count]
            if len(got) != f.count:
                raise Fail("request_args.txt:%d: %s.%s: the layout %s has no such %s argument" % (n, name, f.name, lay, f.kind))
            f.resolve(got, name)
            at[f.kind] += f.count
            pos += f.count
        if not rest:
            for k in at:
                if at[k] != len(by_kind[k]):
                    raise Fail("request_args.txt:%d: %s reads %d %s argument(s), the layout %s has %d (end with ... to leave the rest)" % (
                        n, name, at[k], k, lay, len(by_kind[k])))
        structs.append((name, methods, fields, doc, lay))
        doc = []
    return structs


def read_expr(f):
    """The expression that reads field f (one element for an array: `{k}` for its offset)."""
    if f.kind == "str":
        return "str_at(r, %d)" % f.index if not f.default else '(r.strs.size() > %d ? r.strs[%d] : std::string(%s))' % (
            f.index, f.index, f.default)
    if f.kind == "vec":
        return "(r.vecs.size() > %d ? r.vecs[%d] : std::vector<u64>())" % (f.index, f.index)
    raw = "int_at(r, %s%s)" % ("%d" % f.index if f.count == 1 else "%d + k" % f.index, ", %s" % f.default if f.default else "")
    if f.optional:
        return "nonzero<%s>(%s)" % (f.cpp, raw)
    if f.id_type:
        return "%s((%s::rep)%s)" % (f.cpp, f.cpp, raw)
    return raw if f.cpp == "u64" else "(%s)%s" % (f.cpp, raw)


def emit(structs):
    out = ["// Generated by tools/gen_request_args.py from request_args.txt (the arguments' names and types) and",
           "// server/net/gen/wire_decode.inc (the request layouts); do not edit. server/src/api/gen/README.md.",
           "#pragma once",
           "#include <optional>",
           "#include <string>",
           "#include <vector>",
           "",
           '#include "core/request_args.h"  // int_at, str_at',
           '#include "soaserver/ids.h"',
           '#include "soaserver/server.h"',
           "",
           "namespace soa::server::args {",
           ""]
    for name, methods, fields, doc, lay in structs:
        out += ["// " + d if d else "//" for d in doc]
        out.append("// %s: the wire's arguments %s." % (", ".join(methods), TOKENS[methods[0]]))
        out.append("struct %s {" % name)
        reads = []
        for f in fields:
            if f.skip:
                continue
            t = "std::optional<%s>" % f.cpp if f.optional else f.cpp
            init = "" if (f.optional or f.id_type or f.kind != "int") else " = 0"
            if f.count > 1:
                out.append("    %s %s[%d]%s;" % (t, f.name, f.count, " = {}"))
                reads.append("        for (size_t k = 0; k < %d; k++) a.%s[k] = %s;" % (f.count, f.name, read_expr(f)))
            else:
                out.append("    %s %s%s;" % (t, f.name, init))
                reads.append("        a.%s = %s;" % (f.name, read_expr(f)))
        out.append("    static %s from(const Request& r) {" % name)
        out.append("        %s a;" % name)
        if not reads:
            out.append("        (void)r;")
        out += reads
        out.append("        return a;")
        out.append("    }")
        out.append("};")
        out.append("")
    out += ["}  // namespace soa::server::args", ""]
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--lib", help="(ignored: tools/check_generated.py passes it to every generator)")
    a = ap.parse_args()
    try:
        text = emit(parse(SPEC, layouts()))
    except Fail as ex:
        sys.exit("gen_request_args: %s" % ex)
    if a.check:
        if not os.path.exists(OUT) or open(OUT, encoding="utf-8").read() != text:
            sys.exit("%s is stale: run tools/gen_request_args.py" % os.path.relpath(OUT, REPO))
        return
    with open(OUT, "w", encoding="utf-8") as f:
        f.write(text)
    print("%s written" % os.path.relpath(OUT, REPO))


if __name__ == "__main__":
    main()
