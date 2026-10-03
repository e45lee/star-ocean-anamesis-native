#!/bin/sh
# Builds everything (the port, soa-server, the 3.7.0 emulator, the 3.8.0 viewer soa-viewer, the runtime tests,
# aif2png) into build/:
#   1. vcpkg: $VCPKG_ROOT, else .vcpkg/, cloned and bootstrapped if missing (scripts/vcpkg-bootstrap.sh);
#   2. configure build/ with vcpkg's toolchain (the first configure builds the vcpkg.json ports into
#      build/vcpkg_installed/ and fetches dynarmic and libjpeg 9 into build/_deps/);
#   3. build.
# The generator is Ninja when `ninja` is installed (else Unix Makefiles), and compiles go through
# ccache when it is installed (CCACHE_BASEDIR = the checkout, so worktrees share the cache). Both are
# picked when build/ is configured; delete build/ to switch an existing tree.
# Linux prerequisites vcpkg can't provide: README.md, "Setup".
#
# Usage: scripts/build.sh [cmake --build options...]   e.g. scripts/build.sh --target soa
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo"

vcpkg_root=$(scripts/vcpkg-bootstrap.sh)
jobs=$(nproc 2>/dev/null || echo 4)
[ "$jobs" -gt 8 ] && jobs=8
# ccache: paths under the checkout are hashed relative to it, so another worktree's objects match.
export CCACHE_BASEDIR="$repo" CCACHE_NOHASHDIR=true
# precompiled headers (dynarmic, the port): cacheable with these (ccache manual, "Precompiled headers")
export CCACHE_SLOPPINESS="${CCACHE_SLOPPINESS:-pch_defines,time_macros,include_file_mtime,include_file_ctime}"
if [ ! -f build/CMakeCache.txt ]; then
  gen=; command -v ninja > /dev/null 2>&1 && gen="-G Ninja"
  launcher=; command -v ccache > /dev/null 2>&1 &&
    launcher="-DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache"
  echo "== configuring build/ (vcpkg: $vcpkg_root${gen:+, Ninja}${launcher:+, ccache})"
  # shellcheck disable=SC2086
  VCPKG_MAX_CONCURRENCY=${VCPKG_MAX_CONCURRENCY:-$jobs} \
    cmake -S . -B build $gen $launcher -DCMAKE_TOOLCHAIN_FILE="$vcpkg_root/scripts/buildsystems/vcpkg.cmake"
fi
echo "== building (cmake --build build -j$jobs $*)"
cmake --build build -j"$jobs" "$@"
echo "== done: build/port/soa, build/server/soa-server, build/emulator/soa-emu, build/emulator-viewer/soa-viewer"
