#!/bin/sh
# Usage: tools/decomp_at.sh [--v380] <out-basename> <ghidra-hex-addr>...
# The lib: the 3.7.0 client by default; --v380 / --v370 as in decomp.sh (tools/common.sh).
# Like decomp.sh but by address (Ghidra address = ELF vaddr + 0x100000).
set -eu
case "${1:-}" in --v370) shift;; --v380) SOA_V380=1; shift;; esac
. "$(dirname "$0")/common.sh"
out=$1; shift
mkdir -p "$WORK/ghidra" "$WORK/decomp"
ghidra_project_ready
run() { "$GHIDRA_HOME/support/analyzeHeadless" "$SLOT" quick -process "$GHIDRA_PROG" -noanalysis -readOnly \
  -scriptPath "$REPO/tools/ghidra_scripts" -postScript DecompileAt.java "$WORK/decomp/$out.c" "$@" > "$WORK/ghidra/$out.log" 2>&1; }
ghidra_run SLOT run "$@"
"$PYTHON" "$REPO/tools/resolve_decomp.py" < "$WORK/decomp/$out.c" > "$WORK/decomp/$out.resolved.c"
