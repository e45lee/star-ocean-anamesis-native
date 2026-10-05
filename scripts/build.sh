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
# --windows (first argument): the Windows cross build instead, into build-win/ (port/PLAN.md 5b;
# README.md, "Windows"): llvm-mingw's clang ($SOA_LLVM_MINGW, else work/tools/llvm-mingw), vcpkg's
# x64-mingw-static triplet (cmake/vcpkg-triplets/), cmake/toolchains/llvm-mingw-x64.cmake, the
# vcpkg feature "angle" (EGL / GLES).
#
# --release (after --windows, if any): the optimized build the release packages are made from
# (scripts/package.sh; README.md "Packaging"), into build-release/ (build-win-release/):
# CMAKE_BUILD_TYPE=Release (-O3, NDEBUG) plus -g1 (line tables: the packages' separate debug
# symbols), no aif2png; on Linux libstdc++
# and libgcc linked statically (the binaries need only glibc, libEGL and libGLESv2). No
# -march / -ffast-math: the natives are bit-exact only with the default x86-64 code (no FMA).
#
# Usage: scripts/build.sh [--windows] [--release] [cmake --build options...]   e.g. scripts/build.sh --target soa
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo"
bdir=build
cfg_extra=
windows=
if [ "${1:-}" = "--windows" ]; then
  shift
  windows=1
  bdir=build-win
  llvm_mingw=${SOA_LLVM_MINGW:-$repo/work/tools/llvm-mingw}
  [ -x "$llvm_mingw/bin/x86_64-w64-mingw32-clang++" ] ||
    { echo "build.sh: llvm-mingw not found at $llvm_mingw (set SOA_LLVM_MINGW; README.md, \"Windows\")" >&2; exit 1; }
  # first on PATH: vcpkg's mingw toolchain builds the ports with the x86_64-w64-mingw32-gcc/g++ it finds
  export PATH="$llvm_mingw/bin:$PATH" SOA_LLVM_MINGW="$llvm_mingw"
  cfg_extra="-DVCPKG_TARGET_TRIPLET=x64-mingw-static -DVCPKG_HOST_TRIPLET=x64-linux
    -DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=$repo/cmake/toolchains/llvm-mingw-x64.cmake
    -DVCPKG_MANIFEST_FEATURES=angle"
fi
rel_flags= rel_link=
if [ "${1:-}" = "--release" ]; then
  shift
  bdir=$bdir-release
  cfg_extra="$cfg_extra -DCMAKE_BUILD_TYPE=Release -DSOA_BUILD_TOOLS=OFF"
  rel_flags="-O3 -DNDEBUG -g1"
  [ -z "$windows" ] && rel_link="-static-libstdc++ -static-libgcc"
fi

vcpkg_root=$(scripts/vcpkg-bootstrap.sh)
jobs=$(nproc 2>/dev/null || echo 4)
[ "$jobs" -gt 8 ] && jobs=8
# ccache: paths under the checkout are hashed relative to it, so another worktree's objects match.
export CCACHE_BASEDIR="$repo" CCACHE_NOHASHDIR=true
# precompiled headers (dynarmic, the port): cacheable with these (ccache manual, "Precompiled headers")
export CCACHE_SLOPPINESS="${CCACHE_SLOPPINESS:-pch_defines,time_macros,include_file_mtime,include_file_ctime}"
if [ ! -f "$bdir/CMakeCache.txt" ]; then
  gen=; command -v ninja > /dev/null 2>&1 && gen="-G Ninja"
  launcher=; command -v ccache > /dev/null 2>&1 &&
    launcher="-DCMAKE_C_COMPILER_LAUNCHER=ccache -DCMAKE_CXX_COMPILER_LAUNCHER=ccache"
  echo "== configuring $bdir/ (vcpkg: $vcpkg_root${gen:+, Ninja}${launcher:+, ccache})"
  # shellcheck disable=SC2086
  VCPKG_MAX_CONCURRENCY=${VCPKG_MAX_CONCURRENCY:-$jobs} \
    cmake -S . -B "$bdir" $gen $launcher -DCMAKE_TOOLCHAIN_FILE="$vcpkg_root/scripts/buildsystems/vcpkg.cmake" $cfg_extra \
      ${rel_flags:+"-DCMAKE_C_FLAGS_RELEASE=$rel_flags" "-DCMAKE_CXX_FLAGS_RELEASE=$rel_flags"} \
      ${rel_link:+"-DCMAKE_EXE_LINKER_FLAGS=$rel_link"}
fi
echo "== building (cmake --build $bdir -j$jobs $*)"
cmake --build "$bdir" -j"$jobs" "$@"
if [ -z "$windows" ]; then
  echo "== done: $bdir/port/soa, $bdir/server/soa-server, $bdir/emulator/soa-emu, $bdir/emulator-viewer/soa-viewer"
else
  echo "== done: $bdir/port/soa.exe, $bdir/server/soa-server.exe, $bdir/emulator/soa-emu.exe, $bdir/emulator-viewer/soa-viewer.exe"
  echo "   (from WSL: scripts/windows-stage.sh, then run them in /mnt/c/soa-win; README.md \"Windows\")"
fi
