#!/bin/sh
# Full verification of the shared pre-downloaded 3.7.0 phone (scripts/shared-phone.sh): every file's
# sha256 against the stamped sha256sums.txt, no file added or missing, and nothing writable.
# Usage: scripts/check-phone-370.sh [phone dir]   (default: SOA_SHARED_PHONE, else work/phone-3.7.0)
# Prints PASS / FAIL (exit 0 / 1). About 1 s for the 4.0 GB when the files are in the page cache.
set -u
repo=$(cd "$(dirname "$0")/.." && pwd)
. "$repo/scripts/shared-phone.sh"
d=$(cd "${1:-$(shared_phone_dir "$repo")}" 2>/dev/null && pwd) || { echo "FAIL: no phone ${1:-$(shared_phone_dir "$repo")}"; exit 1; }
[ -f "$d/sha256sums.txt" ] && [ -f "$d/PHONE.txt" ] || { echo "FAIL: $d is not a stamped phone (scripts/make-phone-370.sh)"; exit 1; }
cd "$d" || exit 1
rc=0
want=$(grep '^sha256sums.txt: ' PHONE.txt | cut -d' ' -f2)
[ "$(sha256sum sha256sums.txt | cut -d' ' -f1)" = "$want" ] || { echo "FAIL: sha256sums.txt doesn't match PHONE.txt"; rc=1; }
bad=$(cut -c67- sha256sums.txt | tr '\n' '\0' | xargs -0 -P 8 -n 500 sha256sum 2>&1 | LC_ALL=C sort -k2 | diff - sha256sums.txt | grep '^[<>]' | head -n 20)
[ -z "$bad" ] || { echo "FAIL: files differ from sha256sums.txt:"; echo "$bad"; rc=1; }
list=$(mktemp)
cut -c67- sha256sums.txt | LC_ALL=C sort > "$list"
extra=$(find data -type f -print | LC_ALL=C sort | diff - "$list" | grep '^[<>]' | head -n 20)
rm -f "$list"
[ -z "$extra" ] || { echo "FAIL: files added (<) or missing (>):"; echo "$extra"; rc=1; }
w=$(find . -perm /222 -print | head -n 5)
[ -z "$w" ] || { echo "FAIL: writable (chmod -R a-w $d):"; echo "$w"; rc=1; }
shared_phone_check "$d" > /dev/null || { echo "FAIL: sizes / mtimes differ from files.txt"; rc=1; }
[ $rc = 0 ] && echo "PASS: $d: $(wc -l < sha256sums.txt) files match sha256sums.txt ($want)" || echo "FAIL: $d"
exit $rc
