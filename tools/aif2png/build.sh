#!/bin/sh
# Builds tools/aif2png/aif2png: the repository build's `aif2png` target (scripts/build.sh: vcpkg,
# IJG libjpeg 9 by FetchContent, cmake/deps.cmake), copied next to its source, where
# tools/extract_banners.py looks for it.
set -e
here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/../.." && pwd)
"$root/scripts/build.sh" --target aif2png
cp "$root/build/tools/aif2png/aif2png" "$here/aif2png"
