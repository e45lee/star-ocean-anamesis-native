#!/bin/sh
# Fails if a 3.8.0 reference appears outside the places that may keep one (port/PLAN.md, P4).
# The port runs the 3.7.0 client; 3.8.0 stays only with the viewer and in the history.
#
# Usage: tools/check_no_380.sh [-c]   (-c: print per-file counts instead of the lines)
#
# A reference is a tracked text line matching REGEX (the pattern of the P4 inventory). Allowed:
#   - the paths in ALLOW: the viewer (emulator-viewer/, its run scripts (Linux, Windows; the release
#     package's: scripts/package/run-viewer.*), tools/extract.sh, which
#     unpacks its XAPK; runtime/src/jni/java_playcore.cpp, the Play Core classes only the viewer's
#     lib uses, kept in the shared runtime), the history (docs/history/,
#     the verdiff / rebase / restore370 history tools), the Ghidra projects, apk/, the offline
#     master DB, and soa_save/ (the save editor: it edits the offline game's saves and reads its
#     names from the offline master DB in the XAPK; moving it to 3.7.0 would change its output);
#     data/english/ (the English of the game's own texts, e.g. the 3.7.0 service-end dialog that
#     tells the player to update to 3.8.0);
#   - lines of Markdown files and CMakeLists.txt that name the viewer (soa-viewer, emulator-viewer,
#     run-viewer-380): its rows in README.md, CMakeLists.txt and the plans; elsewhere a marker;
#   - links into docs/history/ (docs/history/... and history/... paths are cut before matching);
#   - lines carrying the marker 380-ok: code that still depends on a 3.8.0 file or names the
#     offline build on purpose (each says why next to the marker), e.g. the decompile tools'
#     --v380 (the viewer's lib) and the Play Core install call in runtime/src/jni/jvm.*.
# A git error fails the check (it never passes for want of output).
set -eu
cd "$(dirname "$0")/.."

REGEX='3\.8\.0|\b[vV]380\b|SOA_V380|[xX][aA][pP][kK]|config\.arm64_v8a|assetinstalltime|playcore|home_sa\b|basmaster-3\.8\.0|smoke-base-380'

ALLOW="
:!emulator-viewer
:!scripts/run-viewer-380.sh
:!scripts/windows/run-viewer-380.cmd
:!scripts/package/run-viewer.sh
:!scripts/package/run-viewer.cmd
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
:!data/english
:!runtime/src/jni/java_playcore.cpp
"

raw=$(mktemp)
trap 'rm -f "$raw"' EXIT
# shellcheck disable=SC2086
rc=0; git grep -nIE "$REGEX" -- . $ALLOW > "$raw" || rc=$?
[ "$rc" -le 1 ] || { echo "check_no_380: FAIL (git grep exited $rc)" >&2; exit 2; }
hits=$(grep -vE '^([^:]*\.md|([^:]*/)?CMakeLists\.txt):[0-9]+:.*(soa-viewer|emulator-viewer|run-viewer-380)' "$raw" \
  | grep -v '380-ok' \
  | R="$REGEX" perl -ne '($t = $_) =~ s#(docs/)?history/[^ )`"]*##g; print if $t =~ /^[^:]+:[0-9]+:.*($ENV{R})/' || true)

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
