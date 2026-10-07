#!/bin/sh
# Usage: tools/decomp.sh [--v380] [--into SUBSYSTEM[/TOPIC]] [<out-basename>] <regex>...   (380-ok)
# Decompiles from the 3.7.0 client the port runs (work/libSOA-3.7.0.so). --v380 (or SOA_V380=1): (380-ok)
# from the viewer's offline lib instead (tools/common.sh). --v370 is accepted (the default).
# Decompile functions whose (demangled) name matches from an unanalyzed Ghidra project, then
# resolve PLT/string references.
#   without --into: scratch output in work/decomp/<out>.resolved.c (<out-basename> required);
#   --into SUBSYSTEM[/TOPIC]: no <out-basename>; the stamped decompile goes to
#     port/decomp/<subsystem>/<topic>.c (TOPIC defaults to SUBSYSTEM) and each function gets a row
#     in port/decomp/<subsystem>/symbols.tsv (tools/decomp_stamp.py; the subsystem must exist:
#     tools/subsystem.py new <subsystem>). Committed: the decompiles a rewrite used.
set -eu
cmd="tools/decomp.sh"; for a in "$@"; do cmd="$cmd '$a'"; done
into=
while :; do
  case "${1:-}" in
    --v370) shift;;
    --v380) SOA_V380=1; shift;;  # 380-ok: the viewer's lib
    --into) into=${2:?--into needs SUBSYSTEM[/TOPIC]}; shift 2;;
    --into=*) into=${1#--into=}; shift;;
    *) break;;
  esac
done
. "$(dirname "$0")/common.sh"
if [ -n "$into" ]; then out=into-$(printf %s "$into" | tr / -)-$$; else out=$1; shift; fi
[ $# -gt 0 ] || { echo "usage: tools/decomp.sh [--v380] [--into SUBSYSTEM[/TOPIC]] [<out-basename>] <regex>..." >&2; exit 2; }  # 380-ok
P=$GHIDRA_QUICK
mkdir -p "$WORK/ghidra" "$WORK/decomp"
ghidra_project_ready
run() { "$GHIDRA_HOME/support/analyzeHeadless" "$SLOT" quick -process "$GHIDRA_PROG" -noanalysis -readOnly \
  -scriptPath "$REPO/tools/ghidra_scripts" -postScript DecompileMatching.java "$WORK/decomp/$out.c" "$@" > "$WORK/ghidra/$out.log" 2>&1; }
ghidra_run SLOT run "$@"
"$PYTHON" "$REPO/tools/resolve_decomp.py" < "$WORK/decomp/$out.c" > "$WORK/decomp/$out.resolved.c"
grep '^// ====' "$WORK/decomp/$out.resolved.c" || true
if [ -n "$into" ]; then
  GHIDRA_HOME=$GHIDRA_HOME "$PYTHON" "$REPO/tools/decomp_stamp.py" --into "$into" --tool-script DecompileMatching.java \
    --command "$cmd" "$WORK/decomp/$out.resolved.c"
  rm -f "$WORK/decomp/$out.c" "$WORK/decomp/$out.resolved.c" "$WORK/ghidra/$out.log"
fi
