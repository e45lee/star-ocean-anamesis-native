"""Build FakeApiCaller response files (port option --fake-server DIR) from JSON.

    tools/fakeapi_msgp.py IN.json OUT.msgp     # one file
    tools/fakeapi_msgp.py SRC_DIR DIR          # every SRC_DIR/<name>.json -> DIR/<name>.msgp

The body is what the API's CApiNotify::On*Res handler deserializes: a map
{"data": {<key>: ...}, "status": n}. Keys and nesting are in port/fakeapi/schema.txt (the live
tree under "data") and port/fakeapi/fields.txt (each info class's fields). JSON ints become
msgpack uints when non-negative (ASON type 2), strings stay UTF-8, floats are doubles.
The file name is the canned name without "FakeApi/", e.g. mission_start.msgp (see the table in
docs/notes.md "Offline server (FakeApiCaller)").
"""
import json
import os
import sys

import msgpack


def build(src, dst):
    with open(src) as f:
        body = json.load(f)
    with open(dst, "wb") as f:
        f.write(msgpack.packb(body, use_bin_type=False))
    print("%s -> %s" % (src, dst))


def main():
    a, b = sys.argv[1:3]
    if os.path.isdir(a):
        os.makedirs(b, exist_ok=True)
        for n in sorted(os.listdir(a)):
            if n.endswith(".json"):
                build(os.path.join(a, n), os.path.join(b, n[:-5] + ".msgp"))
    else:
        build(a, b)


if __name__ == "__main__":
    main()
