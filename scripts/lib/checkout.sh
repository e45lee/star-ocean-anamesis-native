# Where the checkout is, for the shell scripts (POSIX sh; source it: . "$repo/scripts/lib/checkout.sh").
# The same rule as the programs' (C++ soa::install::main_checkout_of, common/include/soa/install.h)
# and the Python tools' (soa_save.paths.main_checkout / repo_file).
#
#   main_checkout DIR   the main checkout of the checkout DIR: for a git worktree
#                       (.claude/worktrees/NAME) the checkout whose .git it shares (git's common
#                       dir's parent), else the target of a work/ link's parent, else DIR itself
#   repo_file DIR REL   DIR/REL when it is a non-empty file or a folder, else the main checkout's
#                       (a worktree lacks the untracked files: data/basmaster-3.7.0.sqlite3, apk/,
#                       work/ ...); nothing (status 1) when neither has it

main_checkout() {
  _co_dir=$(cd "$1" && pwd)
  # git only when DIR is the top of its own work tree (not a folder inside some other repository)
  if [ "$(git -C "$_co_dir" rev-parse --show-toplevel 2>/dev/null)" = "$(cd "$_co_dir" && pwd -P)" ]; then
    _co_common=$(git -C "$_co_dir" rev-parse --path-format=absolute --git-common-dir 2>/dev/null) || _co_common=
    if [ -n "$_co_common" ]; then
      (cd "$_co_common/.." && pwd)
      return 0
    fi
  fi
  if [ -L "$_co_dir/work" ]; then
    dirname "$(readlink -f "$_co_dir/work")"
    return 0
  fi
  echo "$_co_dir"
}

repo_file() {
  for _co_root in "$1" "$(main_checkout "$1")"; do
    if [ -s "$_co_root/$2" ] || [ -d "$_co_root/$2" ]; then
      echo "$_co_root/$2"
      return 0
    fi
  done
  return 1
}
