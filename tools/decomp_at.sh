#!/bin/sh
# Usage: tools/decomp_at.sh [--v380] [--into SUBSYSTEM[/TOPIC]] [<out-basename>] <ghidra-hex-addr>...
# The lib: the 3.7.0 client by default; --v380 / --v370 as in decomp.sh (tools/common.sh).
# Like decomp.sh but by address (Ghidra address = ELF vaddr + 0x100000); --into as in decomp.sh
# (stamped into port/decomp/<subsystem>/<topic>.c + symbols.tsv; without it scratch output in
# work/decomp/<out>.resolved.c).
set -eu
cmd="tools/decomp_at.sh"; for a in "$@"; do cmd="$cmd '$a'"; done
into=
while :; do
  case "${1:-}" in
    --v370) shift;;
    --v380) SOA_V380=1; shift;;
    --into) into=${2:?--into needs SUBSYSTEM[/TOPIC]}; shift 2;;
    --into=*) into=${1#--into=}; shift;;
    *) break;;
  esac
done
. "$(dirname "$0")/common.sh"
if [ -n "$into" ]; then out=into-$(printf %s "$into" | tr / -)-$$; else out=$1; shift; fi
[ $# -gt 0 ] || { echo "usage: tools/decomp_at.sh [--v380] [--into SUBSYSTEM[/TOPIC]] [<out-basename>] <ghidra-hex-addr>..." >&2; exit 2; }
mkdir -p "$WORK/ghidra" "$WORK/decomp"
ghidra_project_ready
run() { "$GHIDRA_HOME/support/analyzeHeadless" "$SLOT" quick -process "$GHIDRA_PROG" -noanalysis -readOnly \
  -scriptPath "$REPO/tools/ghidra_scripts" -postScript DecompileAt.java "$WORK/decomp/$out.c" "$@" > "$WORK/ghidra/$out.log" 2>&1; }
ghidra_run SLOT run "$@"
"$PYTHON" "$REPO/tools/resolve_decomp.py" < "$WORK/decomp/$out.c" > "$WORK/decomp/$out.resolved.c"
if [ -n "$into" ]; then
  GHIDRA_HOME=$GHIDRA_HOME "$PYTHON" "$REPO/tools/decomp_stamp.py" --into "$into" --tool-script DecompileAt.java \
    --command "$cmd" "$WORK/decomp/$out.resolved.c"
  rm -f "$WORK/decomp/$out.c" "$WORK/decomp/$out.resolved.c" "$WORK/ghidra/$out.log"
fi
