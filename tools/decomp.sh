#!/bin/sh
# Usage: tools/decomp.sh [--v380] <out-basename> <regex>...
# Decompiles from the 3.7.0 client the port runs (work/libSOA-3.7.0.so). --v380 (or SOA_V380=1):
# from the viewer's offline lib instead (tools/common.sh). --v370 is accepted (the default).
# Decompile functions whose (demangled) name matches from an unanalyzed Ghidra project, then
# resolve PLT/string references. Output: work/decomp/<out>.resolved.c
set -eu
case "${1:-}" in --v370) shift;; --v380) SOA_V380=1; shift;; esac
. "$(dirname "$0")/common.sh"
out=$1; shift
P=$GHIDRA_QUICK
mkdir -p "$WORK/ghidra" "$WORK/decomp"
ghidra_project_ready
run() { "$GHIDRA_HOME/support/analyzeHeadless" "$SLOT" quick -process "$GHIDRA_PROG" -noanalysis -readOnly \
  -scriptPath "$REPO/tools/ghidra_scripts" -postScript DecompileMatching.java "$WORK/decomp/$out.c" "$@" > "$WORK/ghidra/$out.log" 2>&1; }
ghidra_run SLOT run "$@"
"$PYTHON" "$REPO/tools/resolve_decomp.py" < "$WORK/decomp/$out.c" > "$WORK/decomp/$out.resolved.c"
grep '^// ====' "$WORK/decomp/$out.resolved.c"
