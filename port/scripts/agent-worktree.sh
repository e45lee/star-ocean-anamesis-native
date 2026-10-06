#!/bin/sh
# Usage: port/scripts/agent-worktree.sh <name> [base-ref]
# Creates an isolated checkout for parallel work: a git worktree at .claude/worktrees/<name> on
# branch port/<name> (from base-ref, default main), sharing the main checkout's untracked inputs
# by symlink (work/ and .venv), then builds it into its own build/ with scripts/build.sh (vcpkg's
# toolchain, Ninja and ccache when installed, -j nproc capped at 8). vcpkg is the main checkout's
# .vcpkg/, which scripts/vcpkg-bootstrap.sh finds through git (no link), and the ports are restored
# from vcpkg's binary cache (scripts/build.sh header: the same keys from every checkout).
# The links are ignored by git and refused by the pre-commit hook: never commit them.
set -eu
# The main checkout, also when this script runs from another worktree (its common git dir's parent).
REPO=$(cd "$(git -C "$(dirname "$0")" rev-parse --path-format=absolute --git-common-dir)/.." && pwd)
name=${1:?usage: port/scripts/agent-worktree.sh <name> [base-ref]}; base=${2:-main}
WT=$REPO/.claude/worktrees/$name
if [ ! -d "$WT" ]; then
  git -C "$REPO" worktree add -q -b "port/$name" "$WT" "$base"
fi
for p in work .venv; do
  [ -e "$REPO/$p" ] && [ ! -e "$WT/$p" ] && ln -s "$REPO/$p" "$WT/$p"
done
"$WT/scripts/build.sh" > "$WT/build.log" 2>&1 ||
  { echo "agent-worktree.sh: build failed, see $WT/build.log" >&2; exit 1; }
echo "$WT"
