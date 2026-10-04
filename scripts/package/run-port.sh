#!/bin/sh
# Release package launcher (Linux): runs the desktop port (./soa: the 3.7.0 client with its local
# server built in). It finds the game files beside it or in ./game (README.txt). Options go to soa
# (./soa --help), e.g. --fullscreen, --data DIR, --new-player.
here=$(cd "$(dirname "$0")" && pwd)
exec "$here/soa" "$@"
