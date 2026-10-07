#!/bin/sh
# Makes vcpkg available for the build and prints its root:
#   $VCPKG_ROOT if set (used as is: any vcpkg recent enough to contain vcpkg.json's builtin-baseline),
#   else the main checkout's .vcpkg/ (from a git worktree too: git's common dir's parent, so every
#   worktree shares one clone without a link): an untracked clone of github.com/microsoft/vcpkg,
#   checked out at vcpkg.json's "builtin-baseline" commit (the pinned port versions) and
#   bootstrapped (the vcpkg tool binary, downloaded by vcpkg's own bootstrap script).
# The root CMakeLists.txt finds the same root and uses its toolchain file; the ports are built by
# the first configure (manifest mode, vcpkg.json) into build/vcpkg_installed/, cached in vcpkg's
# binary cache (~/.cache/vcpkg/archives) for every later build or worktree.
#
# Usage: scripts/vcpkg-bootstrap.sh     (prints the vcpkg root on stdout; progress on stderr)
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
baseline=$(sed -n 's/.*"builtin-baseline": *"\([0-9a-f]*\)".*/\1/p' "$repo/vcpkg.json")
[ -n "$baseline" ] || { echo "vcpkg-bootstrap: no builtin-baseline in $repo/vcpkg.json" >&2; exit 1; }

if [ -n "${VCPKG_ROOT:-}" ]; then
  root=$VCPKG_ROOT
  [ -f "$root/scripts/buildsystems/vcpkg.cmake" ] || { echo "vcpkg-bootstrap: VCPKG_ROOT=$root is not a vcpkg checkout" >&2; exit 1; }
else
  . "$repo/scripts/lib/checkout.sh"
  main=$(main_checkout "$repo")
  root=$main/.vcpkg
  if [ ! -d "$root/.git" ]; then
    echo "== cloning vcpkg into $root" >&2
    git clone -q https://github.com/microsoft/vcpkg "$root" >&2
  fi
  if [ "$(git -C "$root" rev-parse HEAD)" != "$baseline" ]; then
    git -C "$root" cat-file -e "$baseline^{commit}" 2>/dev/null || git -C "$root" fetch -q origin >&2
    echo "== vcpkg at $baseline (vcpkg.json builtin-baseline)" >&2
    git -C "$root" -c advice.detachedHead=false checkout -q "$baseline" >&2
  fi
fi
if [ ! -x "$root/vcpkg" ]; then
  echo "== bootstrapping vcpkg ($root/bootstrap-vcpkg.sh)" >&2
  "$root/bootstrap-vcpkg.sh" -disableMetrics >&2
fi
echo "$root"
