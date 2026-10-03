#!/bin/sh
# Usage: port/scripts/agent-worktree.sh <name> [base-ref]
# Creates an isolated checkout for parallel porting work: a git worktree at
# .claude/worktrees/<name> on branch port/<name> (from base-ref, default linux-port), sharing the
# untracked inputs (work/, .venv, and vcpkg's .vcpkg/; deps/ and third_party/ for older branches) by
# symlink, with its own build dir.
set -eu
REPO=$(cd "$(dirname "$0")/../.." && pwd)
name=$1; base=${2:-linux-port}
WT=$REPO/.claude/worktrees/$name
if [ ! -d "$WT" ]; then
  git -C "$REPO" worktree add -q -b "port/$name" "$WT" "$base"
fi
# vcpkg in the main checkout (cloned and bootstrapped there if missing), shared by every worktree.
[ -n "${VCPKG_ROOT:-}" ] || "$REPO/scripts/vcpkg-bootstrap.sh" > /dev/null
for p in work deps third_party .venv .vcpkg; do
  [ -e "$REPO/$p" ] && [ ! -e "$WT/$p" ] && ln -s "$REPO/$p" "$WT/$p"
done
cmake -S "$WT" -B "$WT/build" -DCMAKE_BUILD_TYPE=RelWithDebInfo > "$WT/build.log" 2>&1
cmake --build "$WT/build" -j16 >> "$WT/build.log" 2>&1
echo "$WT"
