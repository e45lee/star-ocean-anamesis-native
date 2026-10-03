#!/bin/sh
# Stages a Windows-side copy of the repository for the Windows build's programs (port/PLAN.md 5b,
# W; README.md "Windows"): the tracked files (git ls-files), what they read from work/
# (download-3.7.0, libSOA-3.7.0.so) and build-win/'s .exe files, into DEST (default /mnt/c/soa-win,
# i.e. C:\soa-win). Incremental (rsync). The programs find the repository upwards from the .exe,
# as on Linux.
#
# Why a copy: from WSL a Windows .exe can run in place (\\wsl.localhost\...), but SQLite can't lock
# files over that share ("database is locked"), the worktree's work/ symlink isn't followed, and
# the tests' /tmp is \tmp on the current drive. On a Windows machine, clone the repository instead.
#
# --phone: also the shared pre-downloaded phone (work/phone-3.7.0, 4 GB: scripts/shared-phone.sh), the
# Windows runs' phone source (control/soadrive/winhost.py links each run's phone from it with hard
# links on the Windows drive). Its files.txt is re-stamped there: the drive keeps whole-second
# mtimes through WSL, not the source's nanoseconds (the content is the same: sha256sums.txt).
#
# --viewer: also the unpacked 3.8.0 XAPK (work/extracted/xapk, 0.9 GB): soa-viewer.exe's game.
#
# --quick: the tracked files and the .exe files only (seconds), when the work/ data is staged already
# (scripts/windows-test.sh before each Windows gate test).
#
# Usage: scripts/windows-stage.sh [--phone] [--viewer] [--quick] [DEST]        then e.g.
#   cd /mnt/c/soa-win && ./build-win/server/soa-server.exe --selftest
#   cd /mnt/c/soa-win && ./build-win/runtime/soaruntime_tests.exe
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
phone=0 viewer=0 quick=0
while [ $# -gt 0 ]; do
  case $1 in
    --phone) phone=1; shift ;;
    --viewer) viewer=1; shift ;;
    --quick) quick=1; shift ;;
    *) break ;;
  esac
done
dest=${1:-/mnt/c/soa-win}
mkdir -p "$dest"
cd "$repo"
# the tracked files (not the work/ link itself), then the work/ data the programs read
git ls-files -z | grep -zv '^work$' | rsync -a --from0 --files-from=- ./ "$dest/"
mkdir -p "$dest/work"
[ "$quick" = 1 ] || for w in download-3.7.0 libSOA-3.7.0.so; do
  [ -e "work/$w" ] && rsync -aL --delete "work/$w" "$dest/work/"
done
if [ "$phone" = 1 ]; then
  [ -f work/phone-3.7.0/PHONE.txt ] || { echo "windows-stage.sh: no shared phone in work/phone-3.7.0 (scripts/make-phone-370.sh)" >&2; exit 1; }
  # --modify-window: the drive's mtimes are whole seconds
  rsync -aL --delete --modify-window=1 work/phone-3.7.0 "$dest/work/"
  (cd "$dest/work/phone-3.7.0" && rm -f files.txt && find data -type f -printf '%s %T@ %p\n' | LC_ALL=C sort -k3 > files.txt)
fi
if [ "$viewer" = 1 ]; then
  mkdir -p "$dest/work/extracted"
  rsync -aL --delete --modify-window=1 work/extracted/xapk "$dest/work/extracted/"  # 380-ok: soa-viewer.exe's game
fi
# the Windows programs, at their build-win/ paths
if [ -d build-win ]; then
  (cd build-win && find . -name '*.exe' -print0) | rsync -a --from0 --files-from=- build-win/ "$dest/build-win/"
fi
echo "staged into $dest ($(wslpath -w "$dest" 2>/dev/null || echo "$dest"))"
