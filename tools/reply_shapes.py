#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""The shapes the server's replies give the client's info classes: per class, the key orders and value types
the replay corpora's replies send, against what the client reads (server/src/api/gen/client_infos.json).

    tools/reply_shapes.py [--server BIN | --dir OUT...] [--class NAME...] [--sites N] [--tsv]

Replays every corpus of server/tests/replay/ with BIN (default build/server/soa-server; as
tools/server_replay_diff.sh does), or reads replay outputs already made (--dir: a `--replay --out` directory,
or a tree of them, e.g. server_replay_diff.sh --keep's work dir). Each reply's `data` is walked from
CInfoManager's children (the keys the client deserializes: `Player` -> CPlayerInfo, `Item` -> CItemInfoList
...), recursively through the classes' children and containers. Per class it prints:
  - each distinct key order sent (with how many maps and a site: corpus/n-Method:path), and whether the
    orders agree with one order (a merge of them all), which a generated serializer can then reproduce;
  - per key the msgpack types sent, and the client's type where they differ (a bool for a u32 property:
    the client's by-hash GetValue<unsigned> takes it, port/src/native/params/params_parser.cpp ToUInt);
  - keys that aren't the class's (another class's, a module's hook) and the client's fields never sent.
--tsv prints one line per class instead: class, merged order (key:type, `?` when sometimes absent) or
CONFLICT. For the reply types (tools/gen_server_infos.py, server/src/api/gen/README.md): the proof of a
converted handler is still the byte-identical replay (tools/server_replay_diff.sh), not this report.
"""
import argparse
import collections
import json
import os
import re
import shutil
import subprocess
import tempfile

import msgpack

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
import server_replay_diff as rd  # noqa: E402

SCHEMA = os.path.join(REPO, "server/src/api/gen/client_infos.json")


def wire_type(v):
    if isinstance(v, bool):
        return "bool"
    if isinstance(v, int):
        return "uint" if v >= 0 else "int"
    if isinstance(v, float):
        return "float"
    if isinstance(v, str):
        return "str"
    if isinstance(v, dict):
        return "map"
    if isinstance(v, list):
        return "arr"
    return "nil" if v is None else type(v).__name__


# the msgpack types a client value type is sent as today without a remark (an int's sign aside)
NATURAL = {"u32": {"uint"}, "u64": {"uint"}, "u8": {"uint"}, "s32": {"uint", "int"}, "float": {"float", "uint", "int"},
           "bool": {"bool"}, "string": {"str"}}


class Shapes:
    def __init__(self, schema):
        self.cls = schema["classes"]
        self.manager = {m["key"]: m["class"] for m in schema["manager"]}
        self.orders = collections.defaultdict(collections.Counter)  # class -> Counter(tuple of keys)
        self.site = {}  # (class, order) -> first site
        self.types = collections.defaultdict(lambda: collections.defaultdict(collections.Counter))  # class -> key -> types
        self.extra = collections.defaultdict(collections.Counter)  # class -> extra key -> count
        self.data_extra = collections.Counter()
        self.mismatch = collections.Counter()  # (class, path kind) -> count: a value not the container's shape

    def walk(self, v, c, site):
        k = self.cls.get(c)
        if k is None:
            return
        if k["kind"] == "info":
            if not isinstance(v, dict):
                self.mismatch[(c, "%s, not a map" % wire_type(v))] += 1
                return
            order = tuple(v)
            self.orders[c][order] += 1
            self.site.setdefault((c, order), site)
            fields = {f["key"]: f for f in k["fields"]}
            for key, x in v.items():
                f = fields.get(key)
                if f is None:
                    self.extra[c][key] += 1
                    continue
                self.types[c][key][wire_type(x)] += 1
                if "class" in f:
                    self.walk(x, f["class"], "%s.%s" % (site, key))
        elif k["kind"] in ("array", "map"):
            if k["kind"] == "array" and isinstance(v, list):
                for i, x in enumerate(v):
                    self.walk(x, k["elem"], "%s[%d]" % (site, i))
            elif k["kind"] == "map" and isinstance(v, dict):
                for key, x in v.items():
                    self.walk(x, k["elem"], "%s{%s}" % (site, key))
            else:
                self.mismatch[(c, "%s: a %s" % (k["kind"], wire_type(v)))] += 1
        elif k["kind"] == "valarray" and not isinstance(v, list):
            self.mismatch[(c, "valarray: a %s" % wire_type(v))] += 1

    def body(self, body, site):
        data = body.get("data") if isinstance(body, dict) else None
        if not isinstance(data, dict):
            return
        for key, v in data.items():
            c = self.manager.get(key)
            if c is None:
                self.data_extra[key] += 1
            else:
                self.walk(v, c, "%s:%s" % (site, key))


def merge(orders):
    """One order every observed order is a subsequence of (keys first seen kept in place), or None."""
    keys = []
    for o in orders:
        for k in o:
            if k not in keys:
                keys.append(k)
    after = collections.defaultdict(set)
    for o in orders:
        for i, a in enumerate(o):
            for b in o[i + 1:]:
                after[a].add(b)
    out, left = [], list(keys)
    while left:
        free = [k for k in left if not any(k in after[j] for j in left if j != k)]
        if not free:
            return None
        out.append(free[0])
        left.remove(free[0])
    return out


def replay_all(server, work):
    outs = []
    for c in rd.corpora(None):
        out = os.path.join(work, os.path.basename(c))
        p = rd.start(os.path.abspath(server), c, out)
        p.communicate()
        outs.append(out)
    return outs


def bodies(dirs):
    for d in dirs:
        for root, _, files in os.walk(d):
            for f in sorted(files, key=lambda f: (len(f), f)):
                if f.endswith(".msgp") and re.match(r"^\d+-", f):
                    p = os.path.join(root, f)
                    yield os.path.relpath(p, d).replace(".msgp", ""), open(p, "rb").read()


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--server", default=os.path.join(REPO, "build/server/soa-server"))
    ap.add_argument("--dir", nargs="+")
    ap.add_argument("--class", dest="classes", nargs="+")
    ap.add_argument("--sites", type=int, default=1, help="sites shown per order")
    ap.add_argument("--tsv", action="store_true")
    a = ap.parse_args()
    S = Shapes(json.load(open(SCHEMA, encoding="utf-8")))
    work = None
    try:
        if a.dir:
            dirs = a.dir
        else:
            work = tempfile.mkdtemp(prefix="soa-reply-shapes-")
            dirs = replay_all(a.server, work)
        for d in dirs:
            for name, b in bodies([d]):
                try:
                    body = msgpack.unpackb(b, raw=False, strict_map_key=False)
                except Exception:
                    continue
                S.body(body, "%s/%s" % (os.path.basename(d.rstrip("/")), name))
    finally:
        if work:
            shutil.rmtree(work, ignore_errors=True)
    classes = sorted(a.classes or S.orders)
    for c in classes:
        orders = S.orders.get(c, {})
        m = merge(list(orders)) if orders else None
        fields = {f["key"]: f for f in S.cls[c]["fields"]} if S.cls.get(c, {}).get("kind") == "info" else {}
        total = sum(orders.values())
        if a.tsv:
            if m is None:
                print("%s\tCONFLICT" % c)
                continue
            cells = []
            for k in m:
                ts = "/".join(sorted(S.types[c][k])) or "?"
                always = sum(n for o, n in orders.items() if k in o) == total
                cells.append("%s:%s%s" % (k, ts, "" if always else "?"))
            print("%s\t%s" % (c, " ".join(cells)))
            continue
        print("== %s: %d maps, %d orders%s" % (c, total, len(orders), "" if m else " (CONFLICT: no one order)"))
        for o, n in orders.most_common():
            print("   %5d  %s   [%s]" % (n, " ".join(o), S.site[(c, o)]))
        if m:
            print("   merged: %s" % " ".join(m))
        for k, ts in sorted(S.types[c].items()):
            f = fields.get(k, {})
            want = f.get("type") or ("class " + f.get("class", "?"))
            odd = set(ts) - NATURAL.get(f.get("type"), {"map", "arr"})
            if odd:
                print("   type   %s: sent %s, client %s" % (k, dict(ts), want))
        for k, n in S.extra[c].most_common():
            print("   extra  %s (%d): not a field of %s" % (k, n, c))
        unsent = [k for k in fields if k not in S.types[c]]
        if unsent:
            print("   never sent: %s" % " ".join(unsent))
    if not a.classes and not a.tsv:
        for (c, why), n in sorted(S.mismatch.items()):
            print("!! %s: %s (%d)" % (c, why, n))
        print("data keys that aren't CInfoManager children: %s" % ", ".join("%s (%d)" % kv for kv in S.data_extra.most_common()))


if __name__ == "__main__":
    main()
