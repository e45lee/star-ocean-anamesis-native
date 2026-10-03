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
# Usage: scripts/windows-stage.sh [DEST]        then e.g.
#   cd /mnt/c/soa-win && ./build-win/server/soa-server.exe --selftest
#   cd /mnt/c/soa-win && ./build-win/runtime/soaruntime_tests.exe
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
dest=${1:-/mnt/c/soa-win}
mkdir -p "$dest"
cd "$repo"
# the tracked files (not the work/ link itself), then the work/ data the programs read
git ls-files -z | grep -zv '^work$' | rsync -a --from0 --files-from=- ./ "$dest/"
mkdir -p "$dest/work"
for w in download-3.7.0 libSOA-3.7.0.so; do
  [ -e "work/$w" ] && rsync -aL --delete "work/$w" "$dest/work/"
done
# the Windows programs, at their build-win/ paths
if [ -d build-win ]; then
  (cd build-win && find . -name '*.exe' -print0) | rsync -a --from0 --files-from=- build-win/ "$dest/build-win/"
fi
echo "staged into $dest ($(wslpath -w "$dest" 2>/dev/null || echo "$dest"))"
