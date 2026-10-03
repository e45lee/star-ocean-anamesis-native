#!/bin/bash
# Builds soa-server as of a git revision, for RG4 (tools/server_replay_diff.sh PARENT CHILD):
#   tools/server_build_at.sh REV OUTDIR      -> OUTDIR/soa-server (the server alone, no port)
#   REV "." is the working tree as it is (tracked and untracked, not ignored files): e.g. a scratch
#   change that must not be committed.
# The revision's CMakeLists.txt, cmake/, vcpkg.json and server/ are extracted into OUTDIR/src and
# configured with the server only (SOA_BUILD_PORT/EMULATOR/... OFF), reusing this checkout's vcpkg
# and build/vcpkg_installed (no dependency rebuild). Incremental when OUTDIR is reused.
# The replay runs soa-server from this checkout's root, so it finds data/ and port/server-data there
# (or upwards from OUTDIR when that is inside the checkout, e.g. build/rg4-parent).
set -euo pipefail
[ $# -eq 2 ] || { echo "usage: $0 REV OUTDIR" >&2; exit 2; }
rev=$1 out=$2
repo=$(cd "$(dirname "$0")/.." && pwd)
mkdir -p "$out"
out=$(cd "$out" && pwd)
src="$out/src"
toolchain=$(sed -n 's/^CMAKE_TOOLCHAIN_FILE:FILEPATH=//p' "$repo/build/CMakeCache.txt" 2>/dev/null || true)
[ -n "$toolchain" ] || toolchain="$repo/.vcpkg/scripts/buildsystems/vcpkg.cmake"
rm -rf "${src:?}.new"
mkdir -p "$src.new"
if [ "$rev" = . ]; then
  (cd "$repo" && git ls-files -co --exclude-standard -- CMakeLists.txt cmake vcpkg.json server | tar -cf - -T -) | tar -x -C "$src.new"
else
  git -C "$repo" archive "$rev" CMakeLists.txt cmake vcpkg.json server | tar -x -C "$src.new"
fi
# keep unchanged files' timestamps (an incremental build): replace only what differs
mkdir -p "$src"
rsync -a --checksum --delete "$src.new/" "$src/"
rm -rf "${src:?}.new"
if [ ! -f "$out/build/CMakeCache.txt" ]; then
  cmake -S "$src" -B "$out/build" -DCMAKE_TOOLCHAIN_FILE="$toolchain" -DVCPKG_INSTALLED_DIR="$repo/build/vcpkg_installed" \
    -DVCPKG_MANIFEST_INSTALL=OFF -DSOA_BUILD_PORT=OFF -DSOA_BUILD_EMULATOR=OFF -DSOA_BUILD_PLATFORM370=OFF \
    -DSOA_BUILD_VIEWER=OFF -DSOA_BUILD_TOOLS=OFF -DSOA_BUILD_WEBVIEW=OFF > "$out/configure.log" 2>&1 || { tail -20 "$out/configure.log"; exit 1; }
fi
cmake --build "$out/build" -j8 --target soa-server > "$out/build.log" 2>&1 || { tail -30 "$out/build.log"; exit 1; }
cp "$out/build/server/soa-server" "$out/soa-server"
if [ "$rev" = . ]; then echo "$out/soa-server (the working tree)"; else echo "$out/soa-server ($(git -C "$repo" rev-parse --short "$rev"))"; fi
