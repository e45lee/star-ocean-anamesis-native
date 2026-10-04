#!/bin/sh
# Release package launcher (Linux): runs soa-viewer (the offline client, unmodified, in the
# emulator). It finds the game's XAPK beside it or in ./game (README.txt). Options go to
# soa-viewer (./soa-viewer --help), e.g. --fullscreen, --data DIR.
here=$(cd "$(dirname "$0")" && pwd)
exec "$here/soa-viewer" "$@"
