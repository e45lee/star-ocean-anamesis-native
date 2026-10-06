#!/bin/bash
# Stages a Windows-side copy of the repository for the Windows build's programs (port/PLAN.md 5b,
# W; README.md "Windows"): the tracked files (git ls-files), what they read from work/
# (SOA-3.7.0-canonical-data.zip, libSOA-3.7.0.so) and build-win/'s .exe files, into DEST (default
# /mnt/c/soa-win, i.e. C:\soa-win). Incremental (rsync). The programs find the repository upwards
# from the .exe, as on Linux.
#
# The 3.7.0 download is staged once, as the zip (4 GB), which soa.exe, soa-server.exe (its CDN, the
# master DB) and the movie player read in place: in a checkout the programs take
# work/download-3.7.0, else work/SOA-3.7.0-canonical-data.zip (docs/environment.md "How the programs
# find the game files"). A work/download-3.7.0 folder left in DEST by an older stage is removed. So
# the selftests that compare the folder with the zip (soa-server --selftest cdn/download-zip) and
# the ones that read the folder skip on the stage: they run on Linux.
#
# Every copy is verified (a copy through WSL's drive mount under memory pressure has left an older
# .exe in place without an error): each staged .exe and the key data files (the zip, libSOA.so, the
# master DBs, the gacha pools, the 3.7.0 APK, the viewer's package) against their source, by size
# and whole-second mtime, and byte for byte (cmp) the .exe files and whatever this run copied. A
# mismatch is copied once more; if it still differs, the script fails naming the files (exit 1).
#
# --phone: also the shared pre-downloaded phone (work/phone-3.7.0, 4 GB: scripts/shared-phone.sh), the
# Windows runs' phone source (control/soadrive/winhost.py links each run's phone from it with hard
# links on the Windows drive). Its files.txt is re-stamped there: the drive keeps whole-second
# mtimes through WSL, not the source's nanoseconds (the content is the same: sha256sums.txt).
#
# --viewer: also soa-viewer.exe's game, the 3.8.0 XAPK (0.9 GB; 380-ok): apk/*.xapk into DEST/apk/, read in
# place there (in a git worktree the main checkout's apk/, which holds the untracked file); without
# one, the unpacked one (work/extracted/..., tools/extract.sh).
#
# --quick: the tracked files and the .exe files only (seconds), when the work/ data is staged already
# (scripts/windows-test.sh before each Windows gate test).
#
# --clean: only removes the old run output from DEST and exits: DEST/run/ (the Windows runs' phones
# and server state, control/soadrive/winhost.py local_dir; scripts/windows-test.sh removes a passing
# run's own) and the side copies of .exe files a running program kept from being replaced
# (build-win/**/NAME.MTIME-SIZE.exe). For an idle stage: a run in progress loses its files.
#
# Usage: scripts/windows-stage.sh [--phone] [--viewer] [--quick] [DEST]        then e.g.
#        scripts/windows-stage.sh --clean [DEST]
#   cd /mnt/c/soa-win && ./build-win/server/soa-server.exe --selftest
#   cd /mnt/c/soa-win && ./build-win/runtime/soaruntime_tests.exe
set -euo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
phone=0 viewer=0 quick=0 clean=0
while [ $# -gt 0 ]; do
  case $1 in
    --phone) phone=1; shift ;;
    --viewer) viewer=1; shift ;;
    --quick) quick=1; shift ;;
    --clean) clean=1; shift ;;
    -h|--help) sed -n '2,42p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
    -*) echo "windows-stage.sh: unknown option $1" >&2; exit 2 ;;
    *) break ;;
  esac
done
dest=${1:-/mnt/c/soa-win}
if [ "$clean" = 1 ]; then
  [ -d "$dest" ] || { echo "windows-stage.sh: no stage $dest" >&2; exit 1; }
  before=$(du -sm "$dest" 2>/dev/null | cut -f1)
  rm -rf "$dest/run"
  [ -d "$dest/build-win" ] && find "$dest/build-win" -regextype posix-extended -regex '.*\.[0-9a-f]+-[0-9a-f]+\.exe' -delete
  echo "cleaned $dest: ${before} MB -> $(du -sm "$dest" 2>/dev/null | cut -f1) MB"
  exit 0
fi
mkdir -p "$dest"
cd "$repo"
# What this run copied (paths relative to DEST): compared byte for byte below.
copied=$(mktemp)
trap 'rm -f "$copied" "$copied.new"' EXIT
# rsync with the copied files' DEST paths logged under PREFIX (--modify-window: the drive's mtimes
# are whole seconds; without it every run would copy everything again)
stage_copy() {
  local prefix=$1; shift
  rsync --modify-window=1 --out-format="$prefix%n" "$@" > "$copied.new" ||
    { echo "FAIL: windows-stage.sh: rsync failed ($*)" >&2; exit 1; }
  grep -v '/$' "$copied.new" >> "$copied" || true
}
# the tracked files (not the work/ link itself), then the work/ data the programs read
git ls-files -z | grep -zv '^work$' | stage_copy "" -a --from0 --files-from=- ./ "$dest/"
mkdir -p "$dest/work"
if [ "$quick" = 0 ]; then
  # the download: the zip only (an older stage's folder copy goes)
  if [ -e "$dest/work/download-3.7.0" ]; then
    echo "windows-stage.sh: removing $dest/work/download-3.7.0 (the stage reads work/SOA-3.7.0-canonical-data.zip)"
    rm -rf "$dest/work/download-3.7.0"
  fi
  [ -e work/SOA-3.7.0-canonical-data.zip ] ||
    echo "windows-stage.sh: warning: no work/SOA-3.7.0-canonical-data.zip: the stage has no 3.7.0 download (README.md \"Game files\")" >&2
  for w in libSOA-3.7.0.so SOA-3.7.0-canonical-data.zip; do
    [ -e "work/$w" ] && stage_copy "work/" -aL "work/$w" "$dest/work/"
  done
fi
if [ "$phone" = 1 ]; then
  [ -f work/phone-3.7.0/PHONE.txt ] || { echo "windows-stage.sh: no shared phone in work/phone-3.7.0 (scripts/make-phone-370.sh)" >&2; exit 1; }
  rsync -aL --delete --modify-window=1 work/phone-3.7.0 "$dest/work/"
  (cd "$dest/work/phone-3.7.0" && rm -f files.txt && find data -type f -printf '%s %T@ %p\n' | LC_ALL=C sort -k3 > files.txt)
fi
viewer_pkg=
if [ "$viewer" = 1 ]; then
  pkg=$(ls apk/*.xapk 2>/dev/null | head -n1 || true)  # 380-ok: soa-viewer.exe's game
  main=$(dirname "$(readlink -f work)")
  [ -n "$pkg" ] || pkg=$(ls "$main"/apk/*.xapk 2>/dev/null | head -n1 || true)  # 380-ok: (a worktree: the main checkout's)
  if [ -n "$pkg" ]; then
    mkdir -p "$dest/apk"
    stage_copy "apk/" -aL "$pkg" "$dest/apk/"  # soa-viewer.exe's game, read in place
    viewer_pkg=$pkg
  else
    mkdir -p "$dest/work/extracted"
    rsync -aL --delete --modify-window=1 work/extracted/xapk "$dest/work/extracted/"  # 380-ok: soa-viewer.exe's game
  fi
fi
# the Windows programs, at their build-win/ paths
exes=()
if [ -d build-win ]; then
  mapfile -d '' exes < <(cd build-win && find . -name '*.exe' ! -regex '.*\.[0-9a-f]+-[0-9a-f]+\.exe' -printf '%P\0')
  [ ${#exes[@]} = 0 ] || printf '%s\0' "${exes[@]}" | stage_copy "build-win/" -a --from0 --files-from=- build-win/ "$dest/build-win/"
fi

# --- verification: every .exe and the key data files against their source
# same SRC DST DEEP: same size, mtime within a second, and with DEEP the same bytes
same() {
  [ -f "$2" ] || return 1
  local s d
  s=$(stat -Lc '%s %Y' "$1") d=$(stat -Lc '%s %Y' "$2")
  [ "${s% *}" = "${d% *}" ] || return 1
  [ $(( ${s#* } - ${d#* } )) -le 1 ] && [ $(( ${d#* } - ${s#* } )) -le 1 ] || return 1
  [ "$3" = 0 ] || cmp -s "$1" "$2"
}
bad=()
# verify SRC REL [DEEP]: DEST/REL is SRC's copy, else copied once more, else a failure
verify() {
  local src=$1 dst=$dest/$2 deep=${3:-0}
  grep -qxF -- "$2" "$copied" && deep=1
  same "$src" "$dst" "$deep" && return 0
  echo "windows-stage.sh: $dst isn't a copy of $src (size, mtime$([ "$deep" = 0 ] || echo ", bytes")): copying it again" >&2
  if rm -f "$dst" && cp -L --preserve=timestamps "$src" "$dst" && same "$src" "$dst" 1; then return 0; fi
  bad+=("$dst (from $src)")
}
for e in "${exes[@]}"; do verify "build-win/$e" "build-win/$e" 1; done
for f in data/basmaster-3.7.0.sqlite3 data/gacha_pools.sqlite3 "apk/STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk" \
         work/libSOA-3.7.0.so work/SOA-3.7.0-canonical-data.zip; do
  case $f in work/*) [ "$quick" = 0 ] || [ -e "$dest/$f" ] || continue ;; esac
  [ -e "$f" ] && verify "$f" "$f"
done
[ -z "$viewer_pkg" ] || verify "$viewer_pkg" "apk/$(basename "$viewer_pkg")"
if [ ${#bad[@]} -gt 0 ]; then
  echo "FAIL: windows-stage.sh: ${#bad[@]} staged file(s) differ from their source after a second copy (WSL's drive mount; low memory?):" >&2
  printf '  %s\n' "${bad[@]}" >&2
  exit 1
fi
echo "staged into $dest ($(wslpath -w "$dest" 2>/dev/null || echo "$dest")); verified ${#exes[@]} .exe files and the data files"
