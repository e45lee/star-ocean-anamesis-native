#!/bin/bash
# Formats the local server's C++ sources with server/.clang-format (server/PLAN-readability.md R2/R3).
#   tools/format_server.sh            format every server/ C++ file in place
#   tools/format_server.sh --check    list the files that aren't formatted; exit 1 if any
#   tools/format_server.sh [--check] FILE...   only these files
# The files: the tracked and untracked (not ignored) *.cpp, *.h and *.inc under server/, except the
# Ninja cipher tables (net/ninja/) and the generated decoder table (net/gen/), as
# server/.clang-format-ignore lists them.
# clang-format: $CLANG_FORMAT, else `clang-format` on PATH. It must be major version 18 (the style was
# measured with Ubuntu's clang-format 18.1.3; another version formats some constructs differently).
set -euo pipefail
repo=$(cd "$(dirname "$0")/.." && pwd)
cd "$repo"
cf=${CLANG_FORMAT:-clang-format}
want=18
ver=$("$cf" --version 2>/dev/null | sed -n 's/.*clang-format version \([0-9]*\)\..*/\1/p' | head -1) || true
if [ -z "$ver" ]; then
  echo "format_server: $cf not found (set CLANG_FORMAT, or install clang-format $want)" >&2
  exit 2
fi
if [ "$ver" != "$want" ]; then
  echo "format_server: $cf is version $ver; the style was measured with $want (set CLANG_FORMAT to a clang-format $want)" >&2
  exit 2
fi
check=0
if [ "${1:-}" = --check ]; then check=1; shift; fi
if [ $# -gt 0 ]; then
  files=("$@")
else
  mapfile -t files < <(git ls-files -co --exclude-standard server | grep -E '\.(cpp|h|inc)$' | grep -vE '^server/net/(ninja/|gen/)')
fi
bad=0
for f in "${files[@]}"; do
  case "$f" in server/net/ninja/*|server/net/gen/*) continue ;; esac
  if [ $check = 1 ]; then
    if ! "$cf" --style=file:server/.clang-format "$f" | cmp -s - "$f"; then echo "not formatted: $f"; bad=1; fi
  else
    "$cf" --style=file:server/.clang-format -i "$f"
  fi
done
if [ $check = 1 ]; then
  [ $bad = 0 ] && echo "format_server: ${#files[@]} files formatted"
  exit $bad
fi
echo "format_server: formatted ${#files[@]} files"
