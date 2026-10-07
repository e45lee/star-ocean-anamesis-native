"""Repository-relative locations. Large/derived files live under work/ (git-ignored)."""
import os
import pathlib

REPO = pathlib.Path(__file__).resolve().parent.parent
# Game build these tools target; derived data files are versioned with it.
GAME_VERSION = "3.8.0"
APK_DIR = REPO / "apk"
WORK = REPO / "work"
SAMPLES = REPO / "samples"


def xapk() -> pathlib.Path:
    found = sorted(APK_DIR.glob("*.xapk"))
    if not found:
        raise FileNotFoundError(f"no .xapk in {APK_DIR} (the APKPure download; README 'Game files')")
    return found[0]


def main_checkout(repo=REPO) -> pathlib.Path:
    """The main checkout of the checkout `repo`: for a git worktree (.claude/worktrees/NAME) the
    checkout whose .git it shares (git's common dir's parent), else the target of a work/ link's
    parent, else `repo` itself. The same rule as scripts/lib/checkout.sh and the programs'
    (soa::install::main_checkout_of)."""
    import subprocess

    repo = pathlib.Path(repo).absolute()
    try:
        top = subprocess.run(["git", "-C", str(repo), "rev-parse", "--show-toplevel"], capture_output=True, text=True).stdout.strip()
        if top and pathlib.Path(top).resolve() == repo.resolve():  # (not a folder inside another repository)
            common = subprocess.run(["git", "-C", str(repo), "rev-parse", "--path-format=absolute", "--git-common-dir"],
                                    capture_output=True, text=True).stdout.strip()
            if common:
                return pathlib.Path(common).parent
    except OSError:  # no git
        pass
    work = repo / "work"
    if work.is_symlink():
        return work.resolve().parent
    return repo


def repo_file(rel, repo=REPO):
    """repo/rel when it is a non-empty file or a folder, else the main checkout's (a worktree lacks
    the untracked files: data/basmaster-3.7.0.sqlite3, apk/, work/ ...); None when neither has it."""
    for root in dict.fromkeys((pathlib.Path(repo), main_checkout(repo))):
        p = root / rel
        if p.is_dir() or (p.is_file() and p.stat().st_size > 0):
            return p
    return None


def master_db(path=None):
    """The master DB the tools read: `path` (e.g. their --db) when given and present, else
    data/basmaster-3.7.0.sqlite3 here or in the main checkout; None when none exists."""
    if path and os.path.isfile(path) and os.path.getsize(path) > 0:
        return pathlib.Path(path)
    return repo_file("data/basmaster-3.7.0.sqlite3")
