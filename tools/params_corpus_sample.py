#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Cut the committed sample of the params corpus from recorded ones (port/src/native/params/README.md "Tests").

`soa --live-check params:dump:out=FILE` records every distinct input of CParameterElementBase::Deserialize to
FILE.corpus (params_corpus.h: the element's properties and the map; hundreds of MB per flow, mostly master-data
rows). The selftest params/corpus replays port/src/native/params/testdata/*.corpus, plus every *.corpus in
$SOA_PARAMS_CORPUS when that is set (the whole recordings). This keeps, per element class and property-list
shape, the first --per records of each input file (the order they were deserialized in), so every class
and shape the flows met is in the sample. Classes whose rows could hold the player's own data (the "Player"
parameter) are left out.

Usage: tools/params_corpus_sample.py [--per N] -o OUT IN.corpus...
"""
import argparse
import struct
import sys

EXCLUDE = (b"Player",)


def records(path):
    b = open(path, "rb").read()
    if b[:4] != b"PRMC":
        sys.exit("%s: not a params corpus" % path)
    version = b[4:8]
    pos = 8
    while pos + 4 <= len(b):
        (n,) = struct.unpack_from("<I", b, pos)
        yield version, b[pos + 4:pos + 4 + n]
        pos += 4 + n


def shape(rec):
    """(element vtable symbol, ((offset, property vtable symbol)...)) of a record."""
    p = 0

    def take(fmt):
        nonlocal p
        v = struct.unpack_from(fmt, rec, p)
        p += struct.calcsize(fmt)
        return v[0]

    def s():
        nonlocal p
        n = take("<I")
        v = rec[p:p + n]
        p += n
        return v

    el = s()
    props = []
    for _ in range(take("<I")):
        off, ztv, kind = take("<q"), s(), take("<B")
        p += 0x28
        if kind == 0:
            p += 8
        else:
            take("<Q")
            s()
        props.append((off, ztv))
    return el, tuple(props)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--per", type=int, default=4)
    ap.add_argument("-o", "--out", required=True)
    ap.add_argument("inputs", nargs="+")
    a = ap.parse_args()
    out, seen, version = [], set(), None
    for path in a.inputs:
        taken = {}
        for v, rec in records(path):
            version = version or v
            el, props = shape(rec)
            if any(x in el for x in EXCLUDE) or rec in seen:
                continue
            k = (el, props)
            if taken.get(k, 0) >= a.per:
                continue
            taken[k] = taken.get(k, 0) + 1
            seen.add(rec)
            out.append(rec)
    with open(a.out, "wb") as f:
        f.write(b"PRMC" + (version or struct.pack("<I", 1)))
        for rec in out:
            f.write(struct.pack("<I", len(rec)) + rec)
    shapes = len({shape(r) for r in out})
    print("%s: %d records, %d shapes, %d bytes" % (a.out, len(out), shapes, sum(len(r) + 4 for r in out) + 8))


if __name__ == "__main__":
    main()
