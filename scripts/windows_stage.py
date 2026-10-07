#!/usr/bin/env python3
"""The Windows stage's whitelist (scripts/windows-stage.list) for scripts/windows-stage.sh: what is
staged, from where, and what in a stage is not on the list. Standard library only.

  windows_stage.py plan [--phone] [--viewer] [--quick]   what to copy: one line per item,
      "file<TAB>SRC_ROOT<TAB>REL" (SRC_ROOT/REL to DEST/REL) or "mirror<TAB>SRC_ROOT<TAB>REL"
      (the directory SRC_ROOT/REL to DEST/REL, files not in the source deleted); warnings on stderr;
      exit 1 when a tracked entry is missing (a stale list)
  windows_stage.py extras DEST          the files in DEST that aren't on the list, one per line
  windows_stage.py prune DEST [-n]      removes them (-n: only lists them); then empty directories

The list's syntax (one entry per line, `#` starts the comment that says why):
  PATH            a file
  DIR/            every file under DIR: the tracked ones for a directory of the checkout (git ls-files;
                  a stage also drops a file that is no longer tracked there), the whole directory
                  otherwise (mirrored)
  DIR/*.EXT       the files the pattern matches (fnmatch on the last component; of files the checkout
                  doesn't track, only the first, by name: one XAPK; 380-ok)
  ... --phone / --viewer   staged only with that option (a stage without it keeps what is there)
  ... --viewer-else        with --viewer, when the --viewer entries before it found nothing
Sources: a path git tracks comes from the checkout; any other from the checkout, else from the main
checkout of a worktree (whose work/ link points into it: work/, the XAPK in apk/; 380-ok). Never staged
whatever the list doesn't name (.claude/, worktrees, build/, .git, other work/ files...).
Always kept in a stage: run/ (the Windows runs' output: scripts/windows-stage.sh --clean) and the
side copies of a listed .exe (NAME.MTIME-SIZE.exe beside NAME.exe: control/soadrive/winhost.py
staged_binary, when Windows refused to replace a running program).
"""
import fnmatch
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(HERE)
LIST = os.path.join(HERE, "windows-stage.list")
KEEP_DIRS = ("run",)
SIDE_COPY = re.compile(r"^(.*)\.[0-9a-f]+-[0-9a-f]+\.exe$")


class Entry:
    def __init__(self, path, flags, why, line):
        self.path, self.flags, self.why, self.line = path, flags, why, line
        self.is_dir = path.endswith("/")
        self.is_glob = any(c in path for c in "*?[")

    @property
    def option(self):
        """--phone / --viewer, or None (always staged)."""
        for f in self.flags:
            if f in ("--phone", "--viewer"):
                return f
            if f == "--viewer-else":
                return "--viewer"
        return None

    def matches(self, rel):
        """rel (a stage path) is this entry's."""
        if self.is_dir:
            return rel.startswith(self.path)
        if self.is_glob:
            d, base = os.path.split(self.path)
            return os.path.dirname(rel) == d and fnmatch.fnmatchcase(os.path.basename(rel), base)
        return rel == self.path


def parse(path=LIST):
    entries = []
    with open(path, encoding="utf-8") as f:
        for n, raw in enumerate(f, 1):
            text, _, why = raw.partition("#")
            words = text.split()
            if not words:
                continue
            p, flags = words[0], words[1:]
            bad = [w for w in flags if w not in ("--phone", "--viewer", "--viewer-else")]
            if bad or p.startswith("/") or ".." in p.split("/") or not why.strip():
                raise ValueError("%s:%d: bad entry (PATH [--phone|--viewer|--viewer-else]  # why): %s" % (path, n, raw.rstrip()))
            entries.append(Entry(p, flags, why.strip(), n))
    return entries


def mark(entries, files):
    """Sets each entry's `tracked`: it names tracked files (a directory or a pattern: some)."""
    tset = set(files)
    for e in entries:
        e.tracked = any(e.matches(p) for p in files) if (e.is_dir or e.is_glob) else e.path in tset
    return tset


def tracked(repo):
    """The checkout's tracked files (relative paths)."""
    out = subprocess.run(["git", "-C", repo, "ls-files", "-z"], capture_output=True, check=True).stdout
    return [p for p in out.decode("utf-8", "surrogateescape").split("\0") if p]


def main_checkout(repo):
    """A worktree's main checkout (where its work/ link points), None otherwise."""
    w = os.path.join(repo, "work")
    if os.path.islink(w):
        m = os.path.dirname(os.path.realpath(w))
        if m != os.path.realpath(repo):
            return m
    return None


def plan(repo=REPO, entries=None, options=(), quick=False, warn=None):
    """[(kind, src_root, rel)]: kind "file" (src_root/rel -> DEST/rel) or "mirror" (a directory).
    Raises ValueError for a tracked entry that matches nothing. --quick: the checkout's tracked
    files and build-win/ only (the work/ data and the options' entries are left as they are)."""
    warn = warn or (lambda m: print("windows_stage.py: warning: " + m, file=sys.stderr))
    entries = parse() if entries is None else entries
    files = tracked(repo)
    mark(entries, files)
    roots = [repo] + [m for m in [main_checkout(repo)] if m]
    out, found = [], {}
    for e in entries:
        opt = e.option
        if opt and opt not in options:
            continue
        if "--viewer-else" in e.flags and found.get("--viewer"):
            continue
        if e.tracked:
            items = [("file", repo, p) for p in files if e.matches(p)]
        elif quick and not e.path.startswith("build-win/"):
            continue
        else:
            items = []
            for r in roots:
                if e.is_dir:
                    if os.path.isdir(os.path.join(r, e.path)):
                        items = [("mirror", r, e.path.rstrip("/"))]
                elif e.is_glob:
                    d = os.path.dirname(e.path)
                    names = sorted(os.listdir(os.path.join(r, d))) if os.path.isdir(os.path.join(r, d)) else []
                    items = [("file", r, d + "/" + n) for n in names if e.matches(d + "/" + n) and os.path.isfile(os.path.join(r, d, n))][:1]
                elif os.path.isfile(os.path.join(r, e.path)):
                    items = [("file", r, e.path)]
                if items:
                    break
            if not items:
                if e.path.startswith(("work/", "build-win/", "apk/")) or opt:
                    warn("%s (scripts/windows-stage.list:%d) not found: not staged" % (e.path, e.line))
                else:
                    raise ValueError("scripts/windows-stage.list:%d: %s matches nothing in the checkout" % (e.line, e.path))
        if opt and items:
            found[opt] = True
        out += items
    return out


def allowed(rel, entries, tset):
    """rel (a file of a stage) is on the list: an entry's, and, under a directory or pattern entry
    of tracked files, still tracked."""
    parts = rel.split("/")
    if parts[0] in KEEP_DIRS:
        return True
    m = SIDE_COPY.match(rel)
    if m and rel.startswith("build-win/") and allowed(m.group(1) + ".exe", entries, tset):
        return True
    for e in entries:
        if e.matches(rel):
            if (e.is_dir or e.is_glob) and e.tracked and rel not in tset:
                continue  # (a stale copy of a file no longer tracked there)
            return True
    return False


def extras(dest, entries=None, repo=REPO):
    """The files (and symbolic links) in dest that aren't on the list, sorted. Mirrored directories
    (the phone) and run/ aren't walked: they are the list's as a whole."""
    entries = parse() if entries is None else entries
    tset = mark(entries, tracked(repo))
    whole = {e.path.rstrip("/") for e in entries if e.is_dir and not e.tracked}
    whole |= set(KEEP_DIRS)
    out = []
    for d, dirs, names in os.walk(dest):
        rd = os.path.relpath(d, dest).replace(os.sep, "/")
        rd = "" if rd == "." else rd + "/"
        keep = []
        for n in sorted(dirs):
            p = rd + n
            if p in whole:
                continue
            if os.path.islink(os.path.join(d, n)):
                out.append(p)
            else:
                keep.append(n)
        dirs[:] = keep
        out += [rd + n for n in names if not allowed(rd + n, entries, tset)]
    return sorted(out)


def prune(dest, entries=None, repo=REPO, dry=False):
    """Removes extras(dest), then the directories left empty (not dest itself); returns the list."""
    ex = extras(dest, entries, repo)
    if dry:
        return ex
    for p in ex:
        os.remove(os.path.join(dest, p))
    # then the directories left empty, outside run/ and the mirrored ones (an empty directory there
    # is the source's: the phone's)
    whole = {e.path.rstrip("/") for e in (parse() if entries is None else entries) if e.is_dir and not getattr(e, "tracked", True)}
    whole |= set(KEEP_DIRS)
    walked = []
    for d, dirs, _ in os.walk(dest):
        rd = os.path.relpath(d, dest).replace(os.sep, "/")
        dirs[:] = [n for n in dirs if (n if rd == "." else rd + "/" + n) not in whole]
        if rd != ".":
            walked.append(d)
    for d in reversed(walked):
        if not os.listdir(d):
            os.rmdir(d)
    return ex


def _main(argv):
    if not argv or argv[0] in ("-h", "--help"):
        print(__doc__)
        return 0 if argv else 2
    cmd, rest = argv[0], argv[1:]
    try:
        if cmd == "plan":
            opts = [a for a in rest if a in ("--phone", "--viewer")]
            for kind, root, rel in plan(options=opts, quick="--quick" in rest):
                print("%s\t%s\t%s" % (kind, root, rel))
            return 0
        if cmd in ("extras", "prune") and rest:
            dest = rest[0]
            if not os.path.isdir(dest):
                return 0
            ex = extras(dest) if cmd == "extras" else prune(dest, dry="-n" in rest[1:])
            for p in ex:
                print(p)
            return 0
    except ValueError as e:
        print("FAIL: windows_stage.py: %s" % e, file=sys.stderr)
        return 1
    print(__doc__, file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(_main(sys.argv[1:]))
