#!/bin/sh
# Builds the shared pre-downloaded 3.7.0 phone (scripts/shared-phone.sh) that the port's and the
# emulator's session scripts link their phones from by default.
#
# Usage: scripts/make-phone-370.sh [soa] [--from PHONE] [--out DIR]     (from any directory)
#   soa      default build/port/soa
#   --from   take the data from PHONE (a phone with the game data downloaded, e.g. a KEEP_DATA=1
#            emulator/scripts/emulator_session.sh run's OUT/emu) instead of downloading it
#   --out    build the phone in DIR (default SOA_SHARED_PHONE, else work/phone-3.7.0). To rebuild
#            the shared phone while sessions run on it, build into work/phone-3.7.0.new, check it
#            (scripts/check-phone-370.sh), then swap the directories with two mv's: running
#            sessions keep their hard-linked inodes, new ones link the new phone.
# Env: SOA_SHARED_PHONE (default work/phone-3.7.0), SCRATCH (default a mktemp dir, deleted),
#      SOA_EPISODE_PACKS=1 (the download session keeps the client save's episode flag: the phone
#      gets the episode packs EP1-3; port/scripts/phone370.sh phone370_client_save)
#
# Without --from: one in-process session to home on an empty phone with the default server
# options (port/scripts/rebase_inproc_session.sh with SOA_PHONE=none: the client downloads all of
# its data from the in-process CDN, 3-4 minutes). Then only data/files/download is kept (the
# run-specific state is left out: shared_prefs/Aska.xml and Game.xml, server.sqlite3, the shader
# cache, data/cache, the decrypted master download/temp.sqlite3, logs), stamped (PHONE.txt;
# files.txt: size, mtime and path of every file, for the cheap check; sha256sums.txt, for
# scripts/check-phone-370.sh) and made read-only (chmod -R a-w). An existing shared phone is
# replaced only once the new one is complete.
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
. "$repo/scripts/shared-phone.sh"
soa=$repo/build/port/soa from= out=
while [ $# -gt 0 ]; do
    case $1 in
        --from) from=$(cd "${2:?--from PHONE}" && pwd); shift 2 ;;
        --out) out=${2:?--out DIR}; case $out in /*) ;; *) out=$PWD/$out ;; esac; shift 2 ;;
        *) soa=$(cd "$(dirname "$1")" && pwd)/$(basename "$1"); shift ;;
    esac
done
dest=${out:-$(shared_phone_dir "$repo")}
scratch=${SCRATCH:-$(mktemp -d "${TMPDIR:-/tmp}/make-phone-370.XXXXXX")}
mkdir -p "$scratch"
t0=$(date +%s)
if [ -z "$from" ]; then
    [ -x "$soa" ] || { echo "FAIL: $soa not built"; exit 1; }
    echo "downloading the 3.7.0 data: port/scripts/rebase_inproc_session.sh (SOA_PHONE=none; out $scratch/out)"
    SOA_PHONE=none "$repo/port/scripts/rebase_inproc_session.sh" "$soa" "$scratch/out" "$scratch/run" > "$scratch/session.txt" 2>&1 || true
    tail -n 2 "$scratch/session.txt"
    grep -q '^PASS' "$scratch/session.txt" || { echo "FAIL: the download session failed (kept: $scratch)"; exit 1; }
    src=$scratch/run/data
    how="downloaded by port/scripts/rebase_inproc_session.sh ($(cd "$repo" && git rev-parse --short HEAD 2>/dev/null || echo ?), soa $soa)"
else
    src=$from
    how="taken from $from"
fi
[ -f "$src/data/files/download/version.bin" ] || { echo "FAIL: $src has no data/files/download/version.bin"; exit 1; }

new=$dest.new.$$
rm -rf "${new:?}"
mkdir -p "$new/data/files"
cp -a "$src/data/files/download" "$new/data/files/download"
# Run-specific files the client leaves in download/: the decrypted master and its journals.
rm -f "$new/data/files/download/"temp.sqlite3*
(
    cd "$new"
    find data -type f -printf '%s %T@ %p\n' | LC_ALL=C sort -k3 > files.txt
    find data -type f -print0 | LC_ALL=C sort -z | xargs -0 sha256sum > sha256sums.txt
    {
        echo "shared pre-downloaded 3.7.0 phone (scripts/make-phone-370.sh; scripts/shared-phone.sh)"
        echo "built: $(date -Iseconds)"
        echo "source: $how"
        echo "episode packs: $(cd data/files/download && ls -d EP[0-9]* 2>/dev/null | tr '\n' ' ' | sed 's/ $//')"
        echo "files: $(wc -l < files.txt)"
        echo "bytes: $(awk '{ s += $1 } END { print s }' files.txt)"
        echo "sha256sums.txt: $(sha256sum sha256sums.txt | cut -d' ' -f1)"
    } > PHONE.txt
)
if [ -e "$dest" ]; then
    chmod -R u+w "$dest"
    rm -rf "${dest:?}"
fi
mv "$new" "$dest"
chmod -R a-w "$dest"
[ -n "${SCRATCH:-}" ] || rm -rf "${scratch:?}"
cat "$dest/PHONE.txt"
shared_phone_check "$dest"
echo "PASS: shared phone $dest ($(($(date +%s) - t0)) s)"
