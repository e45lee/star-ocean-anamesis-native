#!/bin/sh
# Every SOA_* variable that became a flag (common/include/soa/env.h kRemoved) makes each program
# that has the flag print exactly one line "<program>: NAME is gone: use FLAG" at startup, and a
# program prints none for a variable it has no flag for, nor with none set. Runs each binary with
# --help (no game, no window; about a second). Exit 1 on a mismatch.
# Usage: tests/env_removed.sh [BUILD_DIR]   (default build/)
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
build=${1:-$repo/build}
exec "$repo/tools/py" - "$repo" "$build" <<'PY'
import os, re, subprocess, sys
repo, build = sys.argv[1], sys.argv[2]
src = open(os.path.join(repo, "common/include/soa/env.h")).read()
masks = {"kSoa": 1, "kServer": 2, "kEmu": 4, "kViewer": 8, "kRender": 16}
masks["kRuntimePrograms"] = 1 | 4 | 8
table = []
for name, use, progs in re.findall(r'\{"(SOA_[A-Z0-9_]+)", "([^"]+)", ([^}]+)\}', src):
    m = 0
    for p in progs.split("|"):
        m |= masks[p.strip()]
    table.append((name, use, m))
assert len(table) >= 29, "kRemoved not parsed"
progs = [("soa", "port/soa", 1), ("soa-server", "server/soa-server", 2), ("soa-emu", "emulator/soa-emu", 4),
         ("soa-viewer", "emulator-viewer/soa-viewer", 8), ("soa-webview-render", "webview/soa-webview-render", 16)]
live = ["SOA_TAG_CHECK", "SOA_TAG_CHECK_EVERY", "SOA_TAG_CHECK_OUT", "SOA_TAG_CHECK_ONLY", "SOA_TAG_CHECK_TRACE", "SOA_TAG_CHECK_DUMP"]
bad = 0
def run(binary, env):
    e = {k: v for k, v in os.environ.items() if not k.startswith("SOA_")}
    e.update(env)
    r = subprocess.run([binary, "--help"], env=e, capture_output=True, text=True, timeout=60)
    return [l for l in r.stderr.splitlines() if " is gone: use " in l]
for prog, rel, bit in progs:
    binary = os.path.join(build, rel)
    if not os.path.exists(binary):
        print("FAIL  %s: %s not built" % (prog, binary)); bad += 1; continue
    env = {name: "1" for name, _, _ in table}
    env.update({n: "1" for n in live})
    want = ["%s: %s is gone: use %s" % (prog, name, use) for name, use, m in table if m & bit]
    if bit == 1:
        want += ["%s: %s is gone: use --live-check" % (prog, n) for n in live]
    got = run(binary, env)
    if sorted(got) != sorted(want):
        bad += 1
        print("FAIL  %s: missing %s; unexpected %s" % (prog, sorted(set(want) - set(got)), sorted(set(got) - set(want))))
        if len(got) != len(set(got)): print("      (a line printed twice)")
    else:
        print("ok    %s: %d warnings, one per removed variable it has a flag for" % (prog, len(want)))
    none = run(binary, {"SOA_TRACE": "x", "SOA_PROFILE_HZ": "100"})
    if none:
        bad += 1; print("FAIL  %s: warned with no removed variable set: %s" % (prog, none))
print("env_removed: %s" % ("FAIL" if bad else "PASS"))
sys.exit(1 if bad else 0)
PY
