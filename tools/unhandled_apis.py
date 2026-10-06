#!/usr/bin/env python3
"""List the API methods the local server has no handler for, and how each is answered today.

Joins `soa-server --list-apis` (method, FunctionID, handler file or "-") with the 3.7.0 client's
FakeApiCaller tables (port/src/native/api/gen/fakeapi_tables.inc) and prints one TSV row per
unhandled method:

  method  fid  in_process

where in_process is how the port's in-process route (the default) answers it:
  empty          a request method (its lambda names FakeApi/<file>): the route asks the local server,
                 which has no handler, so it answers an empty map {} and logs `no handler: <Method>`
  no-reply       the offline build only stores a status; nothing is answered (a waiting screen hangs)
  not-callable   not in the 3.7.0 client's FakeApiCaller (debug and removed features)

Over the wire (soa-server, soa-emu, --server HOST) every unhandled method is answered with an empty
success reply (`data.Time` only). docs/unimplemented-apis.md is the readable version of this list.

Usage: tools/unhandled_apis.py [--server build/server/soa-server] [--summary]
"""
import argparse
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TABLES = os.path.join(ROOT, "port/src/native/api/gen/fakeapi_tables.inc")


def table_sections(text):
    """{'requests': text, 'status': text} from the generated FAKEAPI_* macros."""
    out, cur = {}, None
    for line in text.split("\n"):
        if line.startswith("#define FAKEAPI_REQUESTS"):
            cur = "requests"
        elif line.startswith("#define FAKEAPI_STATUS_ONLY"):
            cur = "status"
        elif line.startswith("#define"):
            cur = None
        elif cur:
            out[cur] = out.get(cur, "") + line + "\n"
    return out


def classify(method, sections):
    pat = re.compile(r"FakeApiCaller\d+%sE" % re.escape(method))
    for line in sections.get("requests", "").split("\n"):
        if pat.search(line):
            return "empty"
    if pat.search(sections.get("status", "")):
        return "no-reply"
    return "not-callable"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--server", default=os.path.join(ROOT, "build/server/soa-server"))
    ap.add_argument("--summary", action="store_true", help="counts only")
    a = ap.parse_args(argv)
    apis = subprocess.run([a.server, "--list-apis"], capture_output=True, text=True, check=True).stdout
    rows = [l.split("\t") for l in apis.splitlines() if l.count("\t") >= 2]
    sections = table_sections(open(TABLES).read())
    unhandled = [(m, fid, classify(m, sections)) for m, fid, h in rows if h == "-"]
    if a.summary:
        kinds = {}
        for _, _, k in unhandled:
            kinds[k.split(":")[0]] = kinds.get(k.split(":")[0], 0) + 1
        print(f"{len(rows)} methods, {len(unhandled)} unhandled: " + ", ".join(f"{k} {n}" for k, n in sorted(kinds.items())))
        return 0
    for row in unhandled:
        print("\t".join(row))
    return 0


if __name__ == "__main__":
    sys.exit(main())
