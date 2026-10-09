#!/usr/bin/env python3
r"""Generate the server's reply types: server/src/api/gen/reply_types.{h,cpp}, one plain C++ struct per client
info class the server sends (CBoostCharacterResultInfo, CLimitBreakInfo, ...) and its `to_value` (the
msgpack::Value map the handler puts into its reply), from two inputs (server/src/api/gen/README.md):

  1. the client: server/src/api/gen/client_infos.json (tools/gen_infos.py --json, from the 3.7.0 lib): each
     class's fields (the ASON key its Initialize names, the value type its property reads), its children
     (another info, an InfoBaseArray<T>, an IInfoBaseMap<K, T> or an InfoBaseValueArray<T>) and the keys of a
     reply's `data` (CInfoManager's children);
  2. the server: server/src/api/gen/reply_types.txt, what the server sends of each class: the keys in the
     order they go on the wire, which are optional, where the msgpack type sent isn't the client's (a bool
     for a u32 property) and the keys the client's class doesn't read. The order and the types are today's
     replies' (tools/reply_shapes.py measures them on the replay corpora); the replays prove each
     converted handler byte-identical (tools/server_replay_diff.sh).

reply_types.txt, one struct per line (a `#` line before it is its comment, copied):
    CLASS[ as NAME]: FIELD...
  NAME: the struct's name when a class is sent in more than one shape (default: CLASS).
  FIELD: [+]KEY[?][:TYPE]
    KEY   a field of CLASS (the client's key); with `+`, a key the client's class doesn't read (TYPE required)
    ?     optional: std::optional<T>, the key sent only when set (else always sent; a scalar's default 0)
    TYPE  a scalar: u8 u32 u64 s32 f64 bool str (default: the client's type; a client `float` is f64, the
          float64 the server sends), or for a child the struct of its element (default: the element class's
          own struct), with `[]` when a map container is sent as an array (the client's map reader gets an
          array: sent so today)
The C++ types: u32 / u64 / s32 / u8 / double / bool / std::string; an info child its struct; an array a
std::vector; a map an InfoMap<K, T> (core/info_map.h: insertion order, keys sent as decimal strings, as the
maps of Value were); a value array a std::vector of its scalar.

Usage:
  tools/gen_server_infos.py            # write the two files
  tools/gen_server_infos.py --check    # exit 1 if they differ (T0 `generated`)
"""
import argparse
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
GEN = os.path.join(REPO, "server/src/api/gen")
SCHEMA = os.path.join(GEN, "client_infos.json")
SPEC = os.path.join(GEN, "reply_types.txt")
OUT_H = os.path.join(GEN, "reply_types.h")
OUT_CPP = os.path.join(GEN, "reply_types.cpp")

SCALARS = {"u8": "u8", "u32": "u32", "u64": "u64", "s32": "s32", "f64": "double", "bool": "bool", "str": "std::string"}
CLIENT = {"u8": "u8", "u32": "u32", "u64": "u64", "s32": "s32", "float": "f64", "bool": "bool", "string": "str"}
# What each client type's GetValue<T> (by hash) takes besides its own kind (port/src/native/params/params_parser.cpp:
# the integers take a bool's byte (GetValueUInt), a bool is GetValueUInt != 0, a float any number).
TAKES = {"u32": {"bool", "u32", "u64", "u8", "s32"}, "u64": {"u32", "u64", "u8"}, "u8": {"u32", "u8"},
         "s32": {"u32", "s32", "u64"}, "f64": {"f64", "u32", "s32"}, "bool": {"bool", "u32", "u8"}, "str": {"str"}}
CPP_WORDS = {"class", "default", "delete", "new", "operator", "template", "this", "union", "type_id"}


class Fail(Exception):
    pass


def ident(key):
    s = re.sub(r"\W", "_", key)
    return s + "_" if s in CPP_WORDS or s[0].isdigit() else s


class Field:
    def __init__(self, tok, cls, schema):
        m = re.match(r"^(\+?)([A-Za-z_][\w]*)(\??)(?::([\w]+)(\[\])?)?$", tok)
        if not m:
            raise Fail("%s: bad field %r" % (cls, tok))
        self.extra, self.key, self.optional = m.group(1) == "+", m.group(2), m.group(3) == "?"
        ty, self.as_array = m.group(4), m.group(5) == "[]"
        self.name = ident(self.key)
        client = {f["key"]: f for f in schema["classes"][cls]["fields"]}
        f = client.get(self.key)
        self.note = ""
        if self.extra:
            if f:
                raise Fail("%s.%s: the client's class reads it (drop the +)" % (cls, self.key))
            if not ty:
                raise Fail("%s.+%s: a key the client doesn't read needs its type" % (cls, self.key))
            self.note = "not read by %s" % cls
            f = {"key": self.key}
        elif not f:
            raise Fail("%s.%s: not a field of the client's class (mark a key it doesn't read +KEY:TYPE)" % (cls, self.key))
        self.child = None  # (container kind, client class, key type or value type)
        if "class" in f:
            c = schema["classes"][f["class"]]
            self.child = (c["kind"], f["class"], c.get("key") or c.get("value"))
            if c["kind"] == "valarray":
                self.scalar, self.elem = CLIENT[c["value"]], None
            else:
                self.elem = ty or (c["elem"] if c["kind"] in ("array", "map") else f["class"])
                self.scalar = None
            if self.as_array and c["kind"] != "map":
                raise Fail("%s.%s: [] on a %s" % (cls, self.key, c["kind"]))
        elif ty in SCALARS or not ty:
            self.elem = None
            want = CLIENT[f["type"]] if "type" in f else None
            self.scalar = ty or want
            if want and self.scalar != want:
                if self.scalar not in TAKES[want]:
                    raise Fail("%s.%s: sent as %s, which the client's %s doesn't take" % (cls, self.key, self.scalar, f["type"]))
                self.note = "sent as %s; the client's property is %s" % (self.scalar, f["type"])
        else:
            if not self.extra:
                raise Fail("%s.%s: %s for a scalar" % (cls, self.key, ty))
            self.elem, self.scalar = ty, None
            self.child = ("info", None, None) if not self.as_array else ("array", None, None)

    def cpp(self, structs):
        if self.scalar and not self.child:
            t = SCALARS[self.scalar]
        elif self.child[0] == "valarray":
            t = "std::vector<%s>" % SCALARS[self.scalar]
        else:
            if self.elem not in structs:
                raise Fail("%s: no struct %s in reply_types.txt" % (self.key, self.elem))
            if self.child[0] == "info":
                t = self.elem
            elif self.child[0] == "array" or self.as_array:
                t = "std::vector<%s>" % self.elem
            else:
                t = "InfoMap<%s, %s>" % (self.child[2], self.elem)
        return "std::optional<%s>" % t if self.optional else t

    def default(self):
        if self.optional or self.child or self.scalar == "str":
            return ""
        return " = false" if self.scalar == "bool" else " = 0"


def parse(spec, schema):
    structs, order, doc = {}, [], []
    for n, ln in enumerate(open(spec, encoding="utf-8"), 1):
        ln = ln.rstrip("\n")
        if not ln.strip():
            doc = []
            continue
        if ln.startswith("#"):
            doc.append(ln[1:].strip())
            continue
        m = re.match(r"^(\w+)(?: as (\w+))?:\s*(.*)$", ln)
        if not m:
            raise Fail("reply_types.txt:%d: not CLASS[ as NAME]: FIELD..." % n)
        cls, name = m.group(1), m.group(2) or m.group(1)
        if cls not in schema["classes"] or schema["classes"][cls]["kind"] != "info":
            raise Fail("reply_types.txt:%d: %s isn't one of the client's info classes" % (n, cls))
        if name in structs:
            raise Fail("reply_types.txt:%d: %s twice" % (n, name))
        try:
            fields = [Field(t, cls, schema) for t in m.group(3).split()]
        except Fail as ex:
            raise Fail("reply_types.txt:%d: %s" % (n, ex))
        keys = [f.key for f in fields]
        if len(set(keys)) != len(keys):
            raise Fail("reply_types.txt:%d: a key twice" % n)
        structs[name] = (cls, fields, doc)
        order.append(name)
        doc = []
    return structs, order


def topo(structs, order):
    out, done = [], set()

    def visit(s):
        if s in done:
            return
        done.add(s)
        for f in structs[s][1]:
            if f.elem:
                if f.elem not in structs:
                    raise Fail("%s.%s: no struct %s in reply_types.txt" % (s, f.key, f.elem))
                visit(f.elem)
        out.append(s)
    for s in order:
        visit(s)
    return out


def emit(schema, structs, order):
    names = topo(structs, order)
    h = ["// Generated by tools/gen_server_infos.py from client_infos.json (the client's info classes) and",
         "// reply_types.txt (what the server sends of them); do not edit. server/src/api/gen/README.md.",
         "#pragma once",
         "#include <optional>",
         "#include <string>",
         "#include <vector>",
         "",
         '#include "core/info_map.h"',
         '#include "soaserver/ids.h"',
         '#include "soaserver/msgpack.h"',
         "",
         "namespace soa::server::infos {",
         ""]
    c = ["// Generated by tools/gen_server_infos.py; do not edit. server/src/api/gen/README.md.",
         '#include "api/gen/reply_types.h"',
         "",
         "namespace soa::server::infos {",
         ""]
    for s in names:
        cls, fields, doc = structs[s]
        client = [f["key"] for f in schema["classes"][cls]["fields"]]
        sent = {f.key for f in fields}
        h += ["// " + d for d in doc]
        h.append("// %s%s: the keys in the order sent.%s" % (
            cls, " (as %s)" % s if s != cls else "",
            (" The client's keys not sent: %s." % ", ".join(k for k in client if k not in sent)) if any(k not in sent for k in client) else ""))
        h.append("struct %s {" % s)
        for f in fields:
            note = ("  // " + f.note) if f.note else ""
            h.append("    %s %s%s;%s" % (f.cpp(structs), f.name, f.default(), note))
        h.append("};")
        h.append("Value to_value(const %s& v);" % s)
        h.append("")
        c.append("Value to_value(const %s& v) {" % s)
        c.append("    Value o = Value::object();")
        for f in fields:
            src = "*v.%s" % f.name if f.optional else "v.%s" % f.name
            if f.scalar and not f.child:
                put = 'o["%s"] = %s;' % (f.key, "(unsigned)" + src if f.scalar == "u8" else src)
            elif f.child[0] == "valarray" or f.child[0] == "array" or f.as_array:
                put = 'o["%s"] = to_array(%s);' % (f.key, src)
            elif f.child[0] == "map":
                put = 'o["%s"] = to_map(%s);' % (f.key, src)
            else:
                put = 'o["%s"] = to_value(%s);' % (f.key, src)
            c.append(("    if (v.%s) %s" % (f.name, put)) if f.optional else "    " + put)
        c.append("    return o;")
        c.append("}")
        c.append("")
    h += ["}  // namespace soa::server::infos", ""]
    c += ["}  // namespace soa::server::infos", ""]
    return "\n".join(h), "\n".join(c)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--check", action="store_true")
    ap.add_argument("--lib", help="(ignored: tools/check_generated.py passes it to every generator)")
    a = ap.parse_args()
    schema = json.load(open(SCHEMA, encoding="utf-8"))
    try:
        structs, order = parse(SPEC, schema)
        h, c = emit(schema, structs, order)
    except Fail as ex:
        sys.exit("gen_server_infos: %s" % ex)
    if a.check:
        for path, text in ((OUT_H, h), (OUT_CPP, c)):
            if not os.path.exists(path) or open(path, encoding="utf-8").read() != text:
                sys.exit("%s is stale: run tools/gen_server_infos.py" % os.path.relpath(path, REPO))
        return
    for path, text in ((OUT_H, h), (OUT_CPP, c)):
        with open(path, "w", encoding="utf-8") as f:
            f.write(text)
    print("%s, %s written: %d structs" % (os.path.relpath(OUT_H, REPO), os.path.relpath(OUT_CPP, REPO), len(structs)))


if __name__ == "__main__":
    main()
