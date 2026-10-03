#!/bin/sh
# Fails if a 3.8.0 reference appears outside the places that may keep one (port/PLAN.md, P4).
# The port runs the 3.7.0 client; 3.8.0 stays only with the viewer and in the history.
#
# Usage: tools/check_no_380.sh [-c]   (-c: print per-file counts instead of the lines)
#
# A reference is a tracked text line matching REGEX (the pattern of the P4 inventory). Allowed:
#   - the paths in ALLOW: the viewer (emulator-viewer/, its run scripts (Linux, Windows), tools/extract.sh, which
#     unpacks its XAPK; runtime/src/jni/java_playcore.cpp + its install call in jvm.*, the Play Core
#     classes only the viewer's lib uses, kept in the shared runtime), the history (docs/history/,
#     the verdiff / rebase / restore370 history tools), the Ghidra projects, apk/, the offline
#     master DB, and soa_save/ + its tests/test_script.py (the save editor: it edits the offline game's saves and reads its
#     names from the offline master DB in the XAPK; moving it to 3.7.0 would change its output);
#   - lines naming the viewer (soa-viewer, emulator-viewer, run-viewer-380): its rows in README.md,
#     CMakeLists.txt and the plans;
#   - links into docs/history/ (docs/history/... and history/... paths are cut before matching);
#   - lines carrying the marker 380-ok: code that still depends on a 3.8.0 file or names the
#     offline build on purpose (each says why next to the marker).
# PENDING files belong to a task still running that rewrites them anyway: their hits are counted
# and printed as a warning, not a failure. Empty since 2026-10-01: P3 landed, and agent
# no380-docs rewrote the last hits of docs/client-changes.md, docs/server-rules.md and
# server/src/api/daily/login_bonus.cpp for the 3.7.0 client (the 3.8.0-only notes moved to
# docs/history/client-changes-3.8.0.md and server-rules-3.8.0.md). Keep it empty.
set -eu
cd "$(dirname "$0")/.."

REGEX='3\.8\.0|[xX][aA][pP][kK]|config\.arm64_v8a|assetinstalltime|playcore|home_sa\b|basmaster-3\.8\.0|smoke-base-380'

ALLOW="
:!emulator-viewer
:!scripts/run-viewer-380.sh
:!scripts/windows/run-viewer-380.cmd
:!docs/history
:!ghidra
:!apk
:!data/basmaster-3.8.0.sqlite3
:!tools/check_no_380.sh
:!tools/verdiff.py
:!tools/verdiff_index.py
:!tools/verdiff_decomp.sh
:!tools/rebase_inventory.py
:!tools/restore370_audit.py
:!tools/extract.sh
:!soa_save
:!tests/test_script.py
:!runtime/src/jni/java_playcore.cpp
:!runtime/src/jni/jvm.cpp
:!runtime/src/jni/jvm.h
"

PENDING=""

# shellcheck disable=SC2086
all=$(git grep -nIE "$REGEX" -- . $ALLOW \
  | grep -vE 'soa-viewer|emulator-viewer|run-viewer-380|380-ok' \
  | R="$REGEX" perl -ne '($t = $_) =~ s#(docs/)?history/[^ )`"]*##g; print if $t =~ /^[^:]+:[0-9]+:.*($ENV{R})/' \
  || true)
pend_re=$(printf '%s\n' $PENDING | sed 's/[.]/[.]/g; s/^/^/; s/$/:/' | paste -sd'|')
hits=$(printf '%s\n' "$all" | grep -vE "${pend_re:-^$}" | grep . || true)
if [ -n "$PENDING" ]; then
  # shellcheck disable=SC2086
  for p in $PENDING; do
    n=$(printf '%s\n' "$all" | grep -c "^$p:" || true)
    [ "$n" -gt 0 ] && echo "check_no_380: pending (P3): $p: $n lines" >&2
  done
fi

if [ -z "$hits" ]; then
  echo "check_no_380: PASS (no 3.8.0 references outside the allowed places)"
  exit 0
fi
if [ "${1:-}" = -c ]; then
  printf '%s\n' "$hits" | cut -d: -f1 | sort | uniq -c | sort -nr
else
  printf '%s\n' "$hits"
fi
n=$(printf '%s\n' "$hits" | wc -l)
f=$(printf '%s\n' "$hits" | cut -d: -f1 | sort -u | wc -l)
echo "check_no_380: FAIL ($n lines in $f files)" >&2
exit 1
