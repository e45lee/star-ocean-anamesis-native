#!/bin/sh
# Release package launcher (Linux): runs the desktop port in English (./soa --lang en: the client's
# language switch, and its built-in server serves the English files, which it builds on the first
# start from the English tables in data/english/ and your game files). Otherwise as run-port.sh;
# options go to soa (./soa --help), e.g. --fullscreen, --data DIR, --new-player.
here=$(cd "$(dirname "$0")" && pwd)
exec "$here/soa" --lang en "$@"
