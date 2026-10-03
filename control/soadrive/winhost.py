"""Windows clients from WSL (port/PLAN.md 5b, W; README.md "Windows"): a target whose binary is a
`.exe` (build-win/...) runs the staged copy in C:\\soa-win (scripts/windows-stage.sh) through WSL
interop. What differs from a Linux client:

  - the program runs from the stage (its cwd: the repository's copy there), with the stage's data
    (data/, work/download-3.7.0, the shared phone work/phone-3.7.0);
  - every path it is given is a Windows path (`winpath`): C:\\... for /mnt/c/..., else
    \\\\wsl.localhost\\DISTRO\\... (fine for logs, screenshots and packet logs, not for SQLite, which
    can't lock there: the phone and the server's state dir are kept on the Windows drive, `local_dir`);
  - the control channel is TCP (`--control tcp:127.0.0.1:PORT`, runtime/src/app/host.cpp): WSL's
    mirrored networking shares 127.0.0.1 with Windows (the FIFO is Linux-only; a named pipe can't be
    opened from WSL);
  - its stdout / stderr come through the interop pipe into the log as on Linux; ending the interop
    process (TERM / KILL of the group) ends the Windows process.
"""
import hashlib
import os
import shutil

from .proc import REPO

STAGE = os.environ.get("SOA_WIN_STAGE", "/mnt/c/soa-win")


def is_windows(binary):
    return bool(binary) and binary.lower().endswith(".exe")


def on_drive(p):
    """p (resolved) is on a Windows drive (/mnt/X/...)."""
    r = os.path.realpath(p)
    return len(r) >= 6 and r.startswith("/mnt/") and r[5].isalpha() and (len(r) == 6 or r[6] == "/")


def winpath(p):
    """The Windows spelling of a local path (symbolic links resolved: a run dir linked onto C: maps to C:)."""
    r = os.path.realpath(p)
    if on_drive(r):
        rest = r[7:].replace("/", "\\")
        return r[5].upper() + ":\\" + rest
    distro = os.environ.get("WSL_DISTRO_NAME", "Ubuntu")
    return "\\\\wsl.localhost\\" + distro + r.replace("/", "\\")


def stage_file(rel):
    """A file or directory of the stage (STAGE/rel), or None when it isn't staged."""
    p = os.path.join(STAGE, rel)
    return p if os.path.exists(p) else None


def staged_binary(binary):
    """The stage's copy of a build-win program, refreshed from the build when that one is newer
    (one file: cheap; scripts/windows-stage.sh stages the rest). A path already on a Windows drive
    is used as it is."""
    b = os.path.abspath(binary)
    if on_drive(b):
        return b
    rel = os.path.relpath(b, REPO)
    if rel.startswith(".."):
        # another checkout's build-win/: keep its path below build-win/
        i = b.find("/build-win/")
        if i < 0:
            raise FileNotFoundError("%s: not under a build-win/ directory, nor on a Windows drive" % binary)
        rel = b[i + 1:]
    dst = os.path.join(STAGE, rel)
    if os.path.exists(b):
        if not os.path.exists(dst) or os.path.getmtime(dst) < os.path.getmtime(b) or os.path.getsize(dst) != os.path.getsize(b):
            os.makedirs(os.path.dirname(dst), exist_ok=True)
            shutil.copy2(b, dst)
    if not os.path.exists(dst):
        raise FileNotFoundError("%s: not built (scripts/build.sh --windows) nor staged (scripts/windows-stage.sh)" % binary)
    return dst


def local_dir(p):
    """A directory the Windows program keeps SQLite files in: p itself when it is on a Windows drive;
    else a directory under STAGE/run/soadrive/ named after p, with p made a symbolic link to it (so
    the Linux side reads the same files at p)."""
    if on_drive(p):
        os.makedirs(p, exist_ok=True)
        return p
    a = os.path.abspath(p)
    d = os.path.join(STAGE, "run", "soadrive", hashlib.sha1(a.encode()).hexdigest()[:10] + "-" + os.path.basename(a))
    if os.path.islink(a):
        os.remove(a)
    elif os.path.isdir(a):
        shutil.rmtree(a)
    if os.path.isdir(d):
        shutil.rmtree(d)
    os.makedirs(d)
    os.makedirs(os.path.dirname(a), exist_ok=True)
    os.symlink(d, a)
    return d
