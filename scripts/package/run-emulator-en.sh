#!/bin/sh
# Release package launcher (Linux): run-emulator.sh in English: soa-server --english (it builds and
# serves the English files: the master, the story, the UI art, from the English tables in
# data/english/ and your game files) and soa-emu --lang en (the client's language switch). The same
# options as run-emulator.sh (./run-emulator.sh --help); the same data folder.
here=$(cd "$(dirname "$0")" && pwd)
exec "$here/run-emulator.sh" --english --lang en "$@"
