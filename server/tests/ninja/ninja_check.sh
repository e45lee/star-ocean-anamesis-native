#!/bin/sh
# Builds server/tests/ninja/ninja_check (the Ninja reference + its vector check) and runs it.
# Usage: server/tests/ninja/ninja_check.sh [args for ninja_check]
set -eu
here=$(cd "$(dirname "$0")" && pwd)
out=${NINJA_CHECK_BIN:-${TMPDIR:-/tmp}/ninja_check}
c++ -std=c++17 -O2 -Wall -Wextra -o "$out" "$here/ninja_check.cpp" "$here"/../../net/ninja/ninja_*.cpp -lcrypto
exec "$out" "$@"
