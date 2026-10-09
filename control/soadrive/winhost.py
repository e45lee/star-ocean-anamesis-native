"""Windows clients from WSL (port/PLAN.md 5b, W; README.md "Windows"): a target whose binary is a
`.exe` (build-win/...) runs the staged copy in C:\\soa-win (scripts/windows-stage.sh) through WSL
interop. What differs from a Linux client:

  - the program runs from the stage (its cwd: the repository's copy there), with the stage's data
    (data/, the download as work/SOA-3.7.0-canonical-data.zip, the shared phone work/phone-3.7.0);
  - every path it is given is a Windows path (`winpath`): C:\\... for /mnt/c/..., else
    \\\\wsl.localhost\\DISTRO\\... (fine for logs, screenshots and packet logs, not for SQLite, which
    can't lock there: the phone and the server's state dir are kept on the Windows drive, `local_dir`);
  - the control channel is TCP (`--control tcp:127.0.0.1:PORT`, runtime/src/app/host.cpp): WSL's
    mirrored networking shares 127.0.0.1 with Windows (the FIFO is Linux-only; a named pipe can't be
    opened from WSL);
  - its ports (proc.free_ports(n, win=True)) come from outside WSL's own ephemeral range (ip_local_port_range): in
    mirrored networking Windows can't bind those (WSAEADDRINUSE);
  - its stdout / stderr come through the interop pipe into the log as on Linux; ending the interop
    process (TERM / KILL of the group) ends the Windows process.
"""
import errno
import filecmp
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


# what replacing a running program on the Windows drive fails with (not a failed copy: ENOMEM, EIO, ...)
BUSY = (errno.EACCES, errno.EPERM, errno.EBUSY, errno.ETXTBSY)


class CopyMismatch(RuntimeError):
    """A copy onto the Windows drive that isn't the source, also after a retry."""


def copy_verified(src, dst):
    """shutil.copy2(src, dst), then dst compared with src (size and bytes); a mismatch is copied
    again once, then raises CopyMismatch. (Copies through WSL's drive mount under memory pressure
    have left a stale or short file behind without an error: scripts/windows-stage.sh verifies its
    copies the same way.)"""
    for attempt in (1, 2):
        shutil.copy2(src, dst)
        filecmp.clear_cache()  # (its cache is keyed on size and mtime, which a bad copy may share)
        if os.path.getsize(dst) == os.path.getsize(src) and filecmp.cmp(src, dst, shallow=False):
            return
        if attempt == 1:
            os.remove(dst)
    raise CopyMismatch("%s: its copy %s differs from it after two copies (the Windows drive; memory?)" % (src, dst))


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
        # (whole seconds: the drive keeps no finer mtimes through WSL)
        if not os.path.exists(dst) or int(os.path.getmtime(dst)) < int(os.path.getmtime(b)) or os.path.getsize(dst) != os.path.getsize(b):
            os.makedirs(os.path.dirname(dst), exist_ok=True)
            try:
                copy_verified(b, dst)
            except OSError as e:
                if e.errno not in BUSY:
                    raise
                # Windows refuses to replace a program that is running (another run's): this build
                # goes beside it under its own name (same directory: the repository is found upwards)
                st = os.stat(b)
                dst = os.path.splitext(dst)[0] + ".%x-%x.exe" % (int(st.st_mtime), st.st_size)
                if not os.path.exists(dst):
                    copy_verified(b, dst)
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




def control_port(log):
    """The port a Windows program's `--control tcp:127.0.0.1:0` listens on, from its log line
    ("I/control: listening on tcp:127.0.0.1:PORT"); None until it is there."""
    try:
        with open(log, errors="replace") as f:
            for line in f:
                if line.startswith("I/control: listening on tcp:"):
                    return int(line.rsplit(":", 1)[1])
    except (OSError, ValueError):
        pass
    return None


def make_phone(dst, env):
    """A Windows run's phone (targets.make_phone): SOA_PHONE resolved as scripts/shared-phone.sh does
    (the stage's shared phone by default); a stamped phone linked by scripts/windows/link-phone.ps1
    (Windows hard links: seconds, where cp -al through WSL takes minutes), any other one copied
    (shared_phone_link). Returns (a note, whether the data is on it)."""
    import subprocess
    from .targets import Abort
    r = subprocess.run(["bash", "-c", '. scripts/shared-phone.sh; shared_phone_resolve "$1" >&2; echo "$SOA_PHONE"; '
                        'echo "$SHARED_PHONE_COPY"', "-", REPO], cwd=REPO, capture_output=True, text=True, env=env)
    lines = r.stdout.splitlines()
    src, copy = (lines[0] if lines else ""), (lines[1].split() if len(lines) > 1 else [])
    if r.returncode != 0:
        raise Abort("preparing the phone: " + (r.stdout + r.stderr).strip()[-300:])
    if not src:
        os.makedirs(os.path.join(dst, "data", "shared_prefs"), exist_ok=True)
        return "empty (the client downloads)" + (": " + r.stderr.strip()[-200:] if r.stderr.strip() else ""), False
    if os.path.isfile(os.path.join(src, "PHONE.txt")) and on_drive(src) and on_drive(os.path.dirname(dst)):
        ps = os.path.join(REPO, "scripts", "windows", "link-phone.ps1")
        r = subprocess.run(["powershell.exe", "-NoProfile", "-ExecutionPolicy", "Bypass", "-File", winpath(ps), winpath(src),
                            winpath(dst)] + copy, capture_output=True, text=True)
        if r.returncode != 0:
            raise Abort("linking the phone (link-phone.ps1): " + (r.stdout + r.stderr).strip()[-400:])
        os.makedirs(os.path.join(dst, "data", "shared_prefs"), exist_ok=True)
        return "linked from %s (%s)" % (src, r.stdout.strip().splitlines()[-1] if r.stdout.strip() else "?"), True
    r = subprocess.run(["bash", "-c", '. scripts/shared-phone.sh; shared_phone_link "$1" "$2"', "-", src, dst], cwd=REPO,
                       capture_output=True, text=True, env=env)
    if r.returncode != 0:
        raise Abort("preparing the phone: " + (r.stdout + r.stderr).strip()[-300:])
    return "copied from %s" % src, True

