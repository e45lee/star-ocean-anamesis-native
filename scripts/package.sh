#!/bin/sh
# Builds the release packages (ZIP files) of the desktop port, the 3.7.0 emulator and the offline
# viewer for Linux and Windows: optimized builds (scripts/build.sh --release), only our binaries and the data we made,
# no game files (checked: an allow-list and a game-file scan). README.md "Packaging"; tools/package.py.
#
# Usage: scripts/package.sh [--linux] [--windows] [--out DIR] [--no-build] [--version V] [--download-ref DIR]
#   (both platforms unless one is named; zips into dist/ unless --out)
set -eu
repo=$(cd "$(dirname "$0")/.." && pwd)
exec "$repo/tools/py" "$repo/tools/package.py" "$@"
