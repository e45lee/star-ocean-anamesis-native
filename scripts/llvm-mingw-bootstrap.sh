#!/bin/sh
# Makes llvm-mingw (the Windows cross toolchain: clang, libc++, the UCRT; README.md "Windows") available
# for scripts/build.sh --windows and prints its root:
#   $SOA_LLVM_MINGW if set (used as is: any recent ucrt ubuntu-x86_64 release of
#   github.com/mstorsjo/llvm-mingw),
#   else work/tools/llvm-mingw in the checkout: a link to the pinned release below, unpacked beside it
#   in work/tools/. A missing or different release is downloaded (checked against its SHA-256),
#   unpacked and the link pointed at it; older releases stay in work/tools/ until deleted by hand.
# Worktrees share the main checkout's through their work link. Tools never go in $HOME (AGENTS.md).
# To move to a newer release, change VERSION and SHA256 (sha256sum of the .tar.xz) together.
#
# Usage: scripts/llvm-mingw-bootstrap.sh     (prints the llvm-mingw root on stdout; progress on stderr)
set -eu
VERSION=20260922
SHA256=bb7bb7654b33d5aa8712acb837c963b2e0c56352560c76105270a3268c665c21
NAME=llvm-mingw-$VERSION-ucrt-ubuntu-22.04-x86_64
URL=https://github.com/mstorsjo/llvm-mingw/releases/download/$VERSION/$NAME.tar.xz

repo=$(cd "$(dirname "$0")/.." && pwd)
clang=bin/x86_64-w64-mingw32-clang++

if [ -n "${SOA_LLVM_MINGW:-}" ]; then
  [ -x "$SOA_LLVM_MINGW/$clang" ] ||
    { echo "llvm-mingw-bootstrap: SOA_LLVM_MINGW=$SOA_LLVM_MINGW has no $clang" >&2; exit 1; }
  echo "$SOA_LLVM_MINGW"
  exit 0
fi

[ "$(uname -m)" = x86_64 ] ||
  { echo "llvm-mingw-bootstrap: the pinned release runs on x86_64 Linux only (set SOA_LLVM_MINGW)" >&2; exit 1; }
[ -e "$repo/work" ] || mkdir "$repo/work"
tools=$repo/work/tools
mkdir -p "$tools"
if [ ! -x "$tools/$NAME/$clang" ]; then
  tmp=$tools/.$NAME.download
  rm -rf "$tmp"
  mkdir "$tmp"
  echo "== downloading $URL" >&2
  curl -fL --retry 3 -o "$tmp/$NAME.tar.xz" "$URL" >&2
  echo "$SHA256  $tmp/$NAME.tar.xz" | sha256sum -c --quiet - >&2 ||
    { echo "llvm-mingw-bootstrap: $NAME.tar.xz does not match its pinned SHA-256" >&2; rm -rf "$tmp"; exit 1; }
  echo "== unpacking into $tools/$NAME" >&2
  tar -C "$tmp" -xJf "$tmp/$NAME.tar.xz"
  rm -rf "${tools:?}/$NAME"
  mv "$tmp/$NAME" "$tools/$NAME"
  rm -rf "$tmp"
fi
if [ "$(readlink "$tools/llvm-mingw" 2>/dev/null)" != "$NAME" ]; then
  [ ! -e "$tools/llvm-mingw" ] || [ -L "$tools/llvm-mingw" ] ||
    { echo "llvm-mingw-bootstrap: $tools/llvm-mingw is not a link; move it away (or set SOA_LLVM_MINGW)" >&2; exit 1; }
  echo "== work/tools/llvm-mingw -> $NAME" >&2
  ln -sfn "$NAME" "$tools/llvm-mingw"
fi
echo "$tools/llvm-mingw"
