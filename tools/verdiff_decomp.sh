#!/bin/sh
# Usage: tools/verdiff_decomp.sh <mangled-symbol>...
# History tool (the 3.7.0 vs 3.8.0 comparison, docs/history/libsoa-3.7.0-vs-3.8.0.md); the port runs 3.7.0 only.
# Decompile each symbol from BOTH builds (3.7.0 online and 3.8.0 offline) for side-by-side
# reading. Output: work/decomp/v370-<name>.c and work/decomp/v380-<name>.c, where <name> is the
# demangled Class::Method with non-identifier characters replaced by '_'.
# The two Ghidra runs (one per build, all symbols batched) run in parallel.
set -eu
T=$(dirname "$0")
REPO=$(cd "$T/.." && pwd)
tag=verdiff-batch-$$
set -- "$@"
regs=""
for s in "$@"; do regs="$regs ^$s\$"; done
# shellcheck disable=SC2086
"$T/decomp.sh" --v370 "$tag-v370" $regs > /dev/null &
p1=$!
# shellcheck disable=SC2086
"$T/decomp.sh" --v380 "$tag-v380" $regs > /dev/null &
p2=$!
wait $p1; wait $p2
"$REPO/.venv/bin/python" - "$REPO/work/decomp" "$tag" <<'PY'
import os, re, sys
d, tag = sys.argv[1], sys.argv[2]
for ver in ("v370", "v380"):
    src = open(os.path.join(d, "%s-%s.resolved.c" % (tag, ver))).read()
    for chunk in re.split(r"(?m)^(?=// ==== )", src):
        if not chunk.startswith("// ===="):
            continue
        dem = chunk.split("\n", 1)[0][8:]
        dem = re.sub(r"^\S+ (?=[A-Za-z_][\w:]*::)", "", dem)   # drop Ghidra's return type
        name = re.sub(r"\(.*", "", dem)
        name = re.sub(r"[^A-Za-z0-9_]+", "_", name.replace("::", "__")).strip("_")[:120]
        out = os.path.join(d, "%s-%s.c" % (ver, name))
        open(out, "w").write(chunk)
        print(out)
    for ext in (".c", ".resolved.c"):
        os.remove(os.path.join(d, "%s-%s%s" % (tag, ver, ext)))
PY
