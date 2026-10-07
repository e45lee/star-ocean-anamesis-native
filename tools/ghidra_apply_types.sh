#!/bin/sh
# Usage: tools/ghidra_apply_types.sh [--v380] [SUBSYSTEM...]   (default: every scaffolded subsystem)   (380-ok)
# Applies port/decomp/<subsystem>/types.json (the structs of <subsystem>_layout.h, from
# tools/subsystem.py export-types) and symbols.tsv to the Ghidra project the decompile tools use
# (tools/common.sh: work/ghidra-quick-v370, kept in ghidra/quick-v370), so later decompiles show
# the recovered types (data types /soa/<subsystem>/...; each class's methods get `this` typed as a
# pointer to it; bookmarks "soa/<subsystem>").
# The integrator runs it, serially, after merging subsystem branches: agents never write the project
# (port/PLAN.md task 6, "Parallelism"). It takes every slot lock of the project pool, applies the
# types to the base project, saves a copy to ghidra/, and drops the pool's other copies (the next
# decompile recreates them from the base).
set -eu
case "${1:-}" in --v370) shift;; --v380) SOA_V380=1; shift;; esac  # 380-ok: the viewer's lib
. "$(dirname "$0")/common.sh"
ghidra_project_ready
if [ $# -eq 0 ]; then
  set -- $(cd "$REPO/port/decomp" 2>/dev/null && for d in */; do [ -f "$d/symbols.tsv" ] && printf '%s\n' "${d%/}"; done)
fi
[ $# -gt 0 ] || { echo "no scaffolded subsystems under port/decomp/"; exit 0; }
for s in "$@"; do
  [ -f "$REPO/port/decomp/$s/types.json" ] || { echo "no port/decomp/$s/types.json (tools/subsystem.py export-types $s)" >&2; exit 2; }
done
# Every slot lock, in order (the decompile tools take them non-blocking, so they wait).
i=0; locks=
while [ $i -lt "$GHIDRA_SLOTS" ]; do
  p=$GHIDRA_QUICK; [ $i -gt 0 ] && p=$GHIDRA_QUICK-$i
  fd=$((20 + i)); eval "exec $fd>\"$p.slot.lock\""; flock "$fd"; locks="$locks $fd"
  i=$((i + 1))
done
# Ghidra rejects paths with a "." component: stage the inputs under work/.
stage=$WORK/ghidra/apply-types-$$; mkdir -p "$stage"
for s in "$@"; do
  cp "$REPO/port/decomp/$s/types.json" "$stage/$s.types.json"
  cp "$REPO/port/decomp/$s/symbols.tsv" "$stage/$s.symbols.tsv"
  "$GHIDRA_HOME/support/analyzeHeadless" "$GHIDRA_QUICK" quick -process "$GHIDRA_PROG" -noanalysis \
    -scriptPath "$REPO/tools/ghidra_scripts" -postScript ApplySubsystemTypes.java "$stage/$s.types.json" "$stage/$s.symbols.tsv" \
    > "$stage/$s.log" 2>&1 || { echo "FAIL: $s (log: $stage/$s.log)" >&2; exit 1; }
  grep -h "soa/$s:" "$stage/$s.log" | sed 's/^.*> //' || true
done
# The pool's copies are stale now: drop them (recreated from the base on the next decompile).
i=1
while [ $i -lt "$GHIDRA_SLOTS" ]; do rm -rf "${GHIDRA_QUICK:?}-$i"; i=$((i + 1)); done
mkdir -p "$(dirname "$GHIDRA_TRACKED")"; rm -rf "${GHIDRA_TRACKED:?}.tmp"
cp -r "$GHIDRA_QUICK" "$GHIDRA_TRACKED.tmp" && rm -rf "${GHIDRA_TRACKED:?}" && mv "$GHIDRA_TRACKED.tmp" "$GHIDRA_TRACKED"
rm -rf "${stage:?}"
echo "applied: $*; the project copy is in $GHIDRA_TRACKED"
