#!/bin/bash
# Stages what the Windows build's programs read into DEST (default /mnt/c/soa-win, i.e. C:\soa-win;
# port/PLAN.md 5b, W; README.md "Windows"), and only that: the whitelist scripts/windows-stage.list
# (each entry with why; scripts/windows_stage.py reads it). The programs (soa.exe, soa-server.exe,
# soa-emu.exe, soa-viewer.exe, soaruntime_tests.exe, at their build-win/ paths) find the stage as
# their checkout upwards from the .exe, as on Linux, by the list's marker files (*/CMakeLists.txt);
# then the data they open (data/, apk/, standin-assets*/, the selftests' fixtures) and work/ by exact
# name. Never anything else: no .claude/ (worktrees), build/, .git, docs or sources, nor any work/
# file the list doesn't name. Incremental (rsync).
#
# What a stage removes from DEST: every file the list doesn't name (an older stage's whole-checkout
# copy, a file no longer tracked under a listed directory, a stray work/ file), then empty
# directories. It keeps run/ (the Windows runs' output) and the side copies of a listed .exe
# (build-win/**/NAME.MTIME-SIZE.exe, see --clean), and the --phone / --viewer data when staged
# without that option. It then checks that nothing outside the list is left (else exit 1). --quick
# neither removes nor checks (the Windows gate tests run it at once, in parallel).
#
# The 3.7.0 download is staged once, as the zip (4 GB), which soa.exe, soa-server.exe (its CDN, the
# master DB) and the movie player read in place, as on Linux: the download is
# work/SOA-3.7.0-canonical-data.zip (docs/environment.md "How the programs find the game files"),
# so the selftests that read it run on the stage too.
#
# Every copy is verified (a copy through WSL's drive mount under memory pressure has left an older
# .exe in place without an error): each staged .exe and the key data files (the zip, libSOA.so, the
# master DBs, the gacha pools, the 3.7.0 APK, the viewer's package) against their source, by size
# and whole-second mtime, and byte for byte (cmp) whatever this run copied and, unless --quick, every
# .exe file. A mismatch is copied once more; if it still differs, the script fails naming the files (exit 1).
#
# --phone: also the shared pre-downloaded phone (work/phone-3.7.0, 4 GB: scripts/shared-phone.sh), the
# Windows runs' phone source (control/soadrive/winhost.py links each run's phone from it with hard
# links on the Windows drive). Its files.txt is re-stamped there: the drive keeps whole-second
# mtimes through WSL, not the source's nanoseconds (the content is the same: sha256sums.txt).
#
# --viewer: also soa-viewer.exe's game, the 3.8.0 XAPK (0.9 GB; 380-ok): apk/*.xapk into DEST/apk/, read in
# place there (in a git worktree the main checkout's apk/, which holds the untracked file); without
# one, the unpacked one (work/extracted/xapk, tools/extract.sh; 380-ok).
#
# --quick: the checkout's listed files and the .exe files only (seconds), when the work/ data is
# staged already (scripts/windows-test.sh before each Windows gate test).
#
# --dry-run: prints what would be staged (SOURCE -> DEST/PATH) and what would be removed from DEST;
# writes nothing.
#
# --clean: only removes the old run output from DEST and exits: DEST/run/ (the Windows runs' phones
# and server state, control/soadrive/winhost.py local_dir; scripts/windows-test.sh removes a passing
# run's own) and the side copies of .exe files a running program kept from being replaced
# (build-win/**/NAME.MTIME-SIZE.exe). For an idle stage: a run in progress loses its files.
#
# Usage: scripts/windows-stage.sh [--phone] [--viewer] [--quick] [--dry-run] [DEST]        then e.g.
#        scripts/windows-stage.sh --clean [DEST]
#   cd /mnt/c/soa-win && ./build-win/server/soa-server.exe --selftest
#   cd /mnt/c/soa-win && ./build-win/runtime/soaruntime_tests.exe
set -euo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
phone=0 viewer=0 quick=0 clean=0 dry=0
while [ $# -gt 0 ]; do
  case $1 in
    --phone) phone=1; shift ;;
    --viewer) viewer=1; shift ;;
    --quick) quick=1; shift ;;
    --clean) clean=1; shift ;;
    --dry-run) dry=1; shift ;;
    -h|--help) sed -n '2,52p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
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
cd "$repo"
lister=(python3 scripts/windows_stage.py)
opts=()
[ "$phone" = 1 ] && opts+=(--phone)
[ "$viewer" = 1 ] && opts+=(--viewer)
[ "$quick" = 1 ] && opts+=(--quick)
# The plan: "file<TAB>ROOT<TAB>REL" (ROOT/REL -> DEST/REL) and "mirror<TAB>ROOT<TAB>DIR" lines
plan=$(mktemp)
copied=$(mktemp)
trap 'rm -f "$plan" "$copied" "$copied.new"' EXIT
"${lister[@]}" plan "${opts[@]}" > "$plan"
if [ "$quick" = 0 ] && ! grep -q $'\twork/SOA-3.7.0-canonical-data.zip$' "$plan"; then
  echo "windows-stage.sh: warning: no work/SOA-3.7.0-canonical-data.zip: the stage has no 3.7.0 download (README.md \"Game files\")" >&2
fi
if [ "$dry" = 1 ]; then
  echo "== would stage into $dest (scripts/windows-stage.list):"
  awk -F'\t' '{ printf "%s%s/%s -> %s%s\n", ($1 == "mirror" ? "(mirror) " : ""), $2, $3, $3, ($1 == "mirror" ? "/" : "") }' "$plan"
  echo "== $(wc -l < "$plan") item(s)"
  if [ -d "$dest" ]; then
    echo "== would remove from $dest (not on the list):"
    "${lister[@]}" prune "$dest" -n
  fi
  exit 0
fi
mkdir -p "$dest"
# rsync with the copied files' DEST paths logged under PREFIX (--modify-window: the drive's mtimes
# are whole seconds; without it every run would copy everything again)
# A failed rsync is retried (up to 3 tries, 20 s apart): writes to the Windows drive through WSL's
# drvfs fail now and then with "Cannot allocate memory" under load, and a retry gets through. A
# --files-from=- list is kept in a file first, since a retry can't re-read stdin.
stage_copy() {
  local prefix=$1; shift
  local args=() a list="" try
  for a in "$@"; do
    if [ "$a" = "--files-from=-" ]; then list=$(mktemp); cat > "$list"; args+=("--files-from=$list"); else args+=("$a"); fi
  done
  for try in 1 2 3; do
    rsync --modify-window=1 --out-format="$prefix%n" "${args[@]}" > "$copied.new" && break
    [ "$try" = 3 ] && { [ -n "$list" ] && rm -f "$list"; echo "FAIL: windows-stage.sh: rsync failed 3 times ($*)" >&2; exit 1; }
    echo "windows-stage.sh: rsync failed (try $try of 3; drvfs ENOMEM under load?): retrying in 20 s" >&2
    sleep 20
  done
  [ -n "$list" ] && rm -f "$list"
  grep -v '/$' "$copied.new" >> "$copied" || true
}
# the listed files, one rsync per source root (the checkout; a worktree's main checkout), following
# links (work/ is one in a worktree)
while IFS= read -r root; do
  awk -F'\t' -v r="$root" '$1 == "file" && $2 == r { printf "%s%c", $3, 0 }' "$plan" |
    stage_copy "" -aL --from0 --files-from=- "$root/" "$dest/"
done < <(awk -F'\t' '$1 == "file" { print $2 }' "$plan" | sort -u)
# the listed directories that aren't the checkout's (the phone; the unpacked viewer game): mirrored
while IFS=$'\t' read -r kind root rel; do
  [ "$kind" = mirror ] || continue
  mkdir -p "$dest/$(dirname "$rel")"
  stage_copy "$(dirname "$rel")/" -aL --delete "$root/$rel" "$dest/$(dirname "$rel")/"
  if [ "$rel" = work/phone-3.7.0 ]; then
    (cd "$dest/work/phone-3.7.0" && rm -f files.txt && find data -type f -printf '%s %T@ %p\n' | LC_ALL=C sort -k3 > files.txt)
  fi
done < "$plan"
# what an older stage left that isn't on the list (a whole-checkout copy, stray work/ files, ...);
# not on --quick: the Windows gate tests run it in parallel, and one's prune would take another's
# rsync temporary files for strays
if [ "$quick" = 0 ]; then
  removed=$("${lister[@]}" prune "$dest")
  [ -z "$removed" ] || echo "windows-stage.sh: removed $(printf '%s\n' "$removed" | wc -l) file(s) not on scripts/windows-stage.list from $dest"
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
# (byte for byte: all of them on a full stage; on --quick only what it copied: reading the 2 GB of
# .exe files back through the drive mount takes over a minute)
nexe=0
while IFS=$'\t' read -r kind root rel; do
  [ "$kind" = file ] || continue
  case $rel in
    *.exe) verify "$root/$rel" "$rel" $((1 - quick)); nexe=$((nexe + 1)) ;;
    data/*.sqlite3|apk/*|work/*) verify "$root/$rel" "$rel" ;;
  esac
done < "$plan"
if [ ${#bad[@]} -gt 0 ]; then
  echo "FAIL: windows-stage.sh: ${#bad[@]} staged file(s) differ from their source after a second copy (WSL's drive mount; low memory?):" >&2
  printf '  %s\n' "${bad[@]}" >&2
  exit 1
fi
# --- nothing outside the list (a full stage)
extra=$([ "$quick" = 1 ] || "${lister[@]}" extras "$dest")
if [ -n "$extra" ]; then
  echo "FAIL: windows-stage.sh: $dest holds files not on scripts/windows-stage.list:" >&2
  printf '%s\n' "$extra" | head -20 | sed 's/^/  /' >&2
  exit 1
fi
echo "staged into $dest ($(wslpath -w "$dest" 2>/dev/null || echo "$dest")): scripts/windows-stage.list only; verified $nexe .exe files and the data files"
