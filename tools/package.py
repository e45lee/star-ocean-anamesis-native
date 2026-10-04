#!/usr/bin/env python3
"""Release packages of the desktop port and the 3.7.0 emulator (README.md "Packaging").

  scripts/package.sh [--linux] [--windows] [--out DIR] [--no-build] [--version V]

Builds the optimized programs (scripts/build.sh --release, --windows --release: build-release/,
build-win-release/) unless --no-build, then makes, per platform:

  soa-port-<V>-<platform>.zip           soa (the 3.7.0 client with its in-process server: run-port) +
                                        soa-server (the server as its own program: run-port-server
                                        runs soa --server against it)
  soa-emulator-<V>-<platform>.zip       soa-emu (the unmodified 3.7.0 client) + soa-server (its server;
                                        it also runs alone) + the run-emulator launcher
  soa-<V>-<platform>-debug-symbols.zip  the programs' separate debug info (line tables)

Each zip holds one top folder (soa-port-<V>-<platform>/ ...) with the binaries (stripped), the
launchers, README.txt (from scripts/package/README.txt.in: per program, which game files it needs and
where to put them), LICENSE.txt (ours, GPLv3), THIRD-PARTY-NOTICES.txt (the licenses of the libraries
we link: the vcpkg ports' copyright files, dynarmic and the externals it links, IJG libjpeg 9, zstd
1.3.4) and ONLY data we made:

  data/gacha_pools.sqlite3   the reconstructed gacha pools (tools/build_gacha_pools.py) WITHOUT the
                             game's text: gacha.name (master_text titles) and rule.text (our notes,
                             quoting banner text) are emptied here; the server takes the titles from
                             the user's master at run time (gacha_pools::name_from_master)
  standin-assets/...         our made-up stand-in images (tools/make_standin_banners.py)

No game file goes in: not the APK / XAPK (380-ok: excluded), the download, a master DB (data/basmaster-*.sqlite3 are
decryptions of the game's own), version.bin, libSOA.so, port/fakeapi/responses, decompiles. The
programs derive what they need from the user's own game files at run time (soaserver/master_source.h).
This script holds no decryption logic.

Enforced twice before a zip is written (check()): every file must match the package's ALLOW list,
and no file may look like a game file (GAME_FILE checks: the ADLD magic, the game's asset
extensions, an ELF for arm64, a SQLite file with master_* tables or a gacha.name / rule.text left,
the names basmaster / version.bin / libSOA) unless it is one of our stand-ins, which must be tracked
in git under standin-assets/ and differ from any same-named file of a download tree given with
--download-ref. A violation fails the run (exit 1) and no zip is left behind.
"""
import argparse
import fnmatch
import hashlib
import os
import re
import shutil
import sqlite3
import stat
import subprocess
import sys
import tempfile
import zipfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PKG_SRC = os.path.join(ROOT, "scripts", "package")
LLVM_MINGW = os.environ.get("SOA_LLVM_MINGW", os.path.expanduser("~/tools/llvm-mingw"))

PLATFORMS = {
    "linux-x64": dict(build="build-release", exe="", triplet="x64-linux", windows=False),
    "windows-x64": dict(build="build-win-release", exe=".exe", triplet="x64-mingw-static", windows=True),
}

# What each package holds: (program target dir, program name).
PROGRAMS = {
    "port": [("port", "soa"), ("server", "soa-server")],
    "emulator": [("emulator", "soa-emu"), ("server", "soa-server")],
    "viewer": [("emulator-viewer", "soa-viewer")],
}
KINDS = ["port", "emulator", "viewer"]
# The packages whose programs run a local server: they get our data (the gacha pools, the
# stand-ins). No seed save (the user, 2026-10-04): data/saves/seed/Game.xml is a real player's,
# sanitized; without one a new local server starts a fresh account (docs/server-rules.md#seed).
WITH_DATA = {"port", "emulator"}

# The allow-list: a packaged file's path (inside the top folder) must match one of these.
ALLOW = {
    "port": ["soa", "soa.exe", "soa-server", "soa-server.exe", "run-port.sh", "run-port.cmd",
             "run-port-server.sh", "run-port-server.cmd", "run-port-server.ps1"],
    "emulator": ["soa-emu", "soa-server", "soa-emu.exe", "soa-server.exe", "run-emulator.sh", "run-emulator.cmd", "run-emulator.ps1"],
    "viewer": ["soa-viewer", "soa-viewer.exe", "run-viewer.sh", "run-viewer.cmd"],
}
ALLOW_COMMON = ["README.txt", "LICENSE.txt", "THIRD-PARTY-NOTICES.txt", "BUILD-INFO.txt", "game/PUT-GAME-FILES-HERE.txt"]
ALLOW_DATA = [
    "data/gacha_pools.sqlite3",
    "standin-assets/Image/etc2/*.aif",
]
ALLOW_DEBUG = ["*.debug", "*.exe.debug", "README.txt"]

# Game-file patterns (GAME_FILE): any file matching one fails the check unless it is an approved stand-in.
GAME_EXTS = {".aif", ".asf", ".spk", ".msgp", ".csf", ".apk", ".xapk", ".so", ".aac", ".mp4", ".bin", ".bmd", ".bca"}  # 380-ok: .xapk excluded
GAME_NAMES = re.compile(r"(basmaster|^version.*\.bin$|libSOA)", re.I)

# The vcpkg ports' helper packages (build scripts, no code in the binaries).
VCPKG_SKIP = re.compile(r"^(vcpkg-.*|boost-cmake|boost-uninstall|doc|man|pkgconfig|unofficial-.*|boost_.*|boost-1\..*|Vorbis|ogg|opengl|boost)$")
DYNARMIC_EXTERNALS = ["fmt", "mcl", "robin-map", "xbyak", "zycore", "zydis"]  # (x86-64: no biscuit / oaknut; catch is tests)


def log(*a):
    print("package:", *a, flush=True)


def run(cmd, **kw):
    log("$", " ".join(cmd))
    subprocess.run(cmd, check=True, **kw)


def git(*args):
    return subprocess.run(["git", "-C", ROOT, *args], check=True, capture_output=True, text=True).stdout.strip()


# ---- build ---------------------------------------------------------------------------------------
def build(plat):
    args = ["--windows"] if PLATFORMS[plat]["windows"] else []
    run([os.path.join(ROOT, "scripts", "build.sh"), *args, "--release", "--target", "soa", "soa-server", "soa-emu", "soa-viewer"], cwd=ROOT)


def tool(plat, name):
    if PLATFORMS[plat]["windows"]:
        return os.path.join(LLVM_MINGW, "bin", "llvm-" + name)
    return name


def strip_into(plat, src, dst, dbg):
    """Copies the program `src` to `dst` without debug info, its debug info to `dbg` (linked by
    .gnu_debuglink on Linux; on Windows a DWARF copy beside, which gdb / lldb load by hand)."""
    shutil.copy2(src, dst)
    run([tool(plat, "objcopy"), "--only-keep-debug", src, dbg])
    run([tool(plat, "strip"), "--strip-debug", "--strip-unneeded", dst] if not PLATFORMS[plat]["windows"] else [tool(plat, "strip"), "--strip-debug", dst])
    if not PLATFORMS[plat]["windows"]:
        run(["objcopy", "--add-gnu-debuglink=" + dbg, dst], cwd=os.path.dirname(dbg))
    os.chmod(dst, 0o755)


# ---- data we made --------------------------------------------------------------------------------
def clean_pools(src, dst):
    """The gacha pools without the game's text (see the module doc)."""
    shutil.copyfile(src, dst)
    db = sqlite3.connect(dst)
    db.execute("update gacha set name = ''")
    db.execute("update rule set text = ''")
    db.execute("insert or replace into meta(key, value) values ('packaged', "
               "'gacha.name and rule.text emptied: the titles come from the master at run time; rules: docs/server-rules.md')")
    db.commit()
    db.execute("vacuum")
    db.close()


def notices(plat, out):
    b = os.path.join(ROOT, PLATFORMS[plat]["build"])
    share = os.path.join(b, "vcpkg_installed", PLATFORMS[plat]["triplet"], "share")
    parts, seen = [], set()

    def add(title, path, extract=None):
        with open(path, encoding="utf-8", errors="replace") as f:
            text = f.read()
        if extract:
            text = extract(text)
        h = hashlib.sha1(text.encode()).hexdigest()
        if h in seen:
            parts.append(f"== {title}\n(the same license text as above)\n")
            return
        seen.add(h)
        parts.append(f"== {title}\n{text.strip()}\n")

    for p in sorted(os.listdir(share)):
        cp = os.path.join(share, p, "copyright")
        if VCPKG_SKIP.match(p) and not p == "boost-headers":
            continue
        if os.path.isfile(cp):
            add(f"{p} (vcpkg port)", cp)
    deps = os.path.join(b, "_deps")
    add("dynarmic (github.com/lioncash/dynarmic, the ARM64 JIT)", os.path.join(deps, "dynarmic-src", "LICENSE.txt"))
    for e in DYNARMIC_EXTERNALS:
        d = os.path.join(deps, "dynarmic-src", "externals", e)
        lic = [f for f in sorted(os.listdir(d)) if re.match(r"(LICEN[CS]E|COPYING|COPYRIGHT)", f, re.I)]
        add(f"{e} (linked into dynarmic)", os.path.join(d, lic[0]))
    add("IJG libjpeg 9b (The Independent JPEG Group's software)", os.path.join(deps, "jpeg9-src", "README"),
        lambda t: t[t.index("LEGAL ISSUES\n====="):t.index("REFERENCES\n=====")] if "REFERENCES\n=====" in t else t)
    add("zstd 1.3.4 (Facebook, BSD)", os.path.join(deps, "zstd134-src", "LICENSE"))
    with open(out, "w", encoding="utf-8", newline="\r\n" if PLATFORMS[plat]["windows"] else "\n") as f:
        f.write("Third-party software in these programs\n"
                "======================================\n\n"
                "The programs link the libraries below (statically). Their licenses follow.\n"
                "The game itself (STAR OCEAN: anamnesis, (C) SQUARE ENIX) is NOT included: you supply your own copy.\n\n")
        f.write("\n".join(parts))


# ---- README --------------------------------------------------------------------------------------
def render(template, flags, values):
    """{{IF name}} / {{IF !name}} ... [{{ELSE}} ...] {{END}} blocks (nested), {{NAME}} values and
    {{# comments}}. A tag alone on its line takes its line break with it."""
    template = re.sub(r"\{\{#[^}]*\}\}", "", template)  # {{# comments}} (e.g. the 380-ok markers)
    toks = re.split(r"((?<=\n)\{\{(?:IF [^}]+|ELSE|END)\}\}\n|\{\{(?:IF [^}]+|ELSE|END)\}\})", template)
    out, stack = [], []  # stack: [this block's condition, in the ELSE part, all enclosing on]

    def on():
        return all(c != e for c, e, _ in stack) if stack else True

    for t in toks:
        tag = t.rstrip("\n") if t.startswith("{{") else t
        if tag.startswith("{{IF "):
            cond = tag[5:-2].strip()
            stack.append([flags.get(cond.lstrip("!"), False) != cond.startswith("!"), False, None])
        elif tag == "{{ELSE}}":
            stack[-1][1] = True
        elif tag == "{{END}}":
            stack.pop()
        elif on():
            out.append(t)
    if stack:
        raise SystemExit("package: README template: an {{IF}} without {{END}}")
    text = re.sub(r"\{\{([A-Z_]+)\}\}", lambda m: values[m.group(1)], "".join(out))
    if "{{" in text:
        raise SystemExit("package: README template: unresolved " + text[text.index("{{"):][:40])
    return text


def readme(plat, kind, version, out):
    w = PLATFORMS[plat]["windows"]
    with open(os.path.join(PKG_SRC, "README.txt.in"), encoding="utf-8") as f:
        t = f.read()
    top = f"soa-{kind}-{version}-{plat}"
    flags = {"windows": w, "linux": not w, "port": kind == "port", "emulator": kind == "emulator", "viewer": kind == "viewer"}
    values = {"VERSION": version, "TOP": top, "EXE": ".exe" if w else "", "PLATFORM": "Windows (x64)" if w else "Linux (x86-64)",
              "COMMIT": git("rev-parse", "--short=12", "HEAD")}
    with open(out, "w", encoding="utf-8", newline="\r\n" if w else "\n") as f:
        f.write(render(t, flags, values))


# ---- the check -----------------------------------------------------------------------------------
def tracked_standins():
    out = {}
    for rel in git("ls-files", "standin-assets").splitlines():
        with open(os.path.join(ROOT, rel), "rb") as f:
            out[rel] = hashlib.sha1(f.read()).hexdigest()
    return out


def game_file_reasons(path, rel):
    """Why `path` looks like a game file ([] when it doesn't)."""
    why = []
    base = os.path.basename(rel)
    ext = os.path.splitext(base)[1].lower()
    if ext in GAME_EXTS:
        why.append(f"a game asset extension ({ext})")
    if GAME_NAMES.search(base):
        why.append("a game file name")
    with open(path, "rb") as f:
        head = f.read(64)
    if head[:4] == b"ADLD":
        why.append("ADLD (the game's encrypted container)")
    if head[:4] == b"\x7fELF" and len(head) > 20 and int.from_bytes(head[18:20], "little") == 0xB7:
        why.append("an ARM64 ELF (the game's library)")
    if head[:4] == b"PK\x03\x04":
        why.append("a zip (an APK?)")
    if head.startswith(b"SQLite format 3\0"):
        db = sqlite3.connect(f"file:{path}?mode=ro", uri=True)
        tables = [r[0] for r in db.execute("select name from sqlite_master where type = 'table'")]
        if any(t.startswith("master_") for t in tables):
            why.append("a SQLite file with master_* tables (a game master DB)")
        if "gacha" in tables and db.execute("select count(*) from gacha where ifnull(name, '') != ''").fetchone()[0]:
            why.append("gacha pools with the game's titles (gacha.name)")
        if "rule" in tables and db.execute("select count(*) from rule where ifnull(text, '') != ''").fetchone()[0]:
            why.append("gacha pools with rule texts")
        db.close()
    return why


def check(stage, kind, download_ref):
    """The allow-list and the game-file scan over the staged folder; returns the list of problems."""
    allow = ALLOW_DEBUG if kind == "debug" else ALLOW[kind] + ALLOW_COMMON + (ALLOW_DATA if kind in WITH_DATA else [])
    standins = tracked_standins()
    problems = []
    top = os.listdir(stage)
    if len(top) != 1:
        return [f"expected one top folder, found {top}"]
    root = os.path.join(stage, top[0])
    for d, _, files in os.walk(root):
        for n in files:
            p = os.path.join(d, n)
            rel = os.path.relpath(p, root).replace(os.sep, "/")
            if os.path.islink(p):
                problems.append(f"{rel}: a symlink")
                continue
            if not any(fnmatch.fnmatchcase(rel, a) for a in allow):
                problems.append(f"{rel}: not on the allow-list")
            why = game_file_reasons(p, rel)
            if why and rel.startswith("standin-assets/"):
                with open(p, "rb") as f:
                    h = hashlib.sha1(f.read()).hexdigest()
                if standins.get(rel) != h:
                    problems.append(f"{rel}: not a tracked stand-in (or changed)")
                    continue
                if download_ref:
                    orig = os.path.join(download_ref, rel[len("standin-assets/"):])
                    if os.path.exists(orig):
                        problems.append(f"{rel}: the download has a file of this name: a stand-in must be ours")
                continue
            for w in why:
                problems.append(f"{rel}: {w}")
    return problems


# ---- zip ------------------------------------------------------------------------------------------
def write_zip(stage, out):
    tmp = out + ".tmp"
    with zipfile.ZipFile(tmp, "w", zipfile.ZIP_DEFLATED, compresslevel=9) as z:
        for d, dirs, files in os.walk(stage):
            dirs.sort()
            for n in sorted(files):
                p = os.path.join(d, n)
                rel = os.path.relpath(p, stage).replace(os.sep, "/")
                zi = zipfile.ZipInfo.from_file(p, rel)
                zi.compress_type = zipfile.ZIP_DEFLATED
                mode = 0o755 if os.stat(p).st_mode & stat.S_IXUSR else 0o644
                zi.external_attr = (stat.S_IFREG | mode) << 16
                with open(p, "rb") as f:
                    z.writestr(zi, f.read(), compresslevel=9)
            for n in dirs:  # empty dirs (game/ has a file, so none today)
                pass
    os.replace(tmp, out)


# Each package's launchers (scripts/package/): on Windows NAME.cmd, plus NAME.ps1 when the .cmd
# hands over to one; on Linux NAME.sh.
LAUNCHERS = {"port": ["run-port", "run-port-server"], "emulator": ["run-emulator"], "viewer": ["run-viewer"]}


def launcher_files(kind, windows):
    out = []
    for base in LAUNCHERS[kind]:
        if windows:
            out += [base + ".cmd"] + ([base + ".ps1"] if os.path.isfile(os.path.join(PKG_SRC, base + ".ps1")) else [])
        else:
            out.append(base + ".sh")
    return out


def stage_package(plat, kind, version, work, dbg_dir):
    P = PLATFORMS[plat]
    top = f"soa-{kind}-{version}-{plat}"
    stage = os.path.join(work, kind)
    root = os.path.join(stage, top)
    os.makedirs(root)
    for sub, name in PROGRAMS[kind]:
        exe = name + P["exe"]
        src = os.path.join(ROOT, P["build"], sub, exe)
        if not os.path.isfile(src):
            raise SystemExit(f"package: {src} isn't built (run without --no-build)")
        if os.path.getmtime(src) < int(git("log", "-1", "--format=%ct")):
            log(f"WARNING: {src} is older than the last commit (BUILD-INFO.txt names HEAD): rebuild, or run without --no-build")
        strip_into(plat, src, os.path.join(root, exe), os.path.join(dbg_dir, exe + ".debug"))
    for f in launcher_files(kind, P["windows"]):
        shutil.copy2(os.path.join(PKG_SRC, f), os.path.join(root, f))
        if f.endswith(".sh"):
            os.chmod(os.path.join(root, f), 0o755)
    if kind in WITH_DATA:
        os.makedirs(os.path.join(root, "data"))
        clean_pools(os.path.join(ROOT, "data", "gacha_pools.sqlite3"), os.path.join(root, "data", "gacha_pools.sqlite3"))
        for rel in git("ls-files", "standin-assets").splitlines():
            os.makedirs(os.path.join(root, os.path.dirname(rel)), exist_ok=True)
            shutil.copyfile(os.path.join(ROOT, rel), os.path.join(root, rel))
    os.makedirs(os.path.join(root, "game"))
    with open(os.path.join(root, "game", "PUT-GAME-FILES-HERE.txt"), "w", newline="\r\n" if P["windows"] else "\n") as f:
        f.write("Put the game files here (README.txt, \"Game files\"):\n" + (
            "  the offline game's .xapk (APKPure's download)\n" if kind == "viewer" else  # 380-ok: soa-viewer's
            "  STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk\n"
            "  SOA-3.7.0-canonical-data.zip, or its contents extracted into a folder here\n"))
    readme(plat, kind, version, os.path.join(root, "README.txt"))
    shutil.copyfile(os.path.join(ROOT, "LICENSE"), os.path.join(root, "LICENSE.txt"))
    notices(plat, os.path.join(root, "THIRD-PARTY-NOTICES.txt"))
    with open(os.path.join(root, "BUILD-INFO.txt"), "w") as f:
        f.write(f"version {version}\ncommit {git('rev-parse', 'HEAD')}\nplatform {plat}\n"
                f"build {P['build']}: CMAKE_BUILD_TYPE=Release, -O3 -DNDEBUG -g1 (debug info in the debug-symbols zip)\n")
    return stage, top


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--linux", action="store_true")
    ap.add_argument("--windows", action="store_true")
    ap.add_argument("--out", default=os.path.join(ROOT, "dist"))
    ap.add_argument("--no-build", action="store_true", help="package the existing build-release/ / build-win-release/")
    ap.add_argument("--version", default=None, help="default: YYYY.MM.DD-<commit>")
    ap.add_argument("--download-ref", default=None,
                    help="a 3.7.0 download tree: stand-ins are checked not to be files of it (default work/download-3.7.0 when present)")
    a = ap.parse_args()
    plats = [p for p, on in (("linux-x64", a.linux), ("windows-x64", a.windows)) if on] or ["linux-x64", "windows-x64"]
    version = a.version or (git("log", "-1", "--format=%cd", "--date=format:%Y.%m.%d") + "-" + git("rev-parse", "--short=8", "HEAD"))
    if git("status", "--porcelain", "--untracked-files=no"):
        log("note: the checkout has uncommitted changes; BUILD-INFO.txt names HEAD")
    ref = a.download_ref or os.path.join(ROOT, "work", "download-3.7.0")
    ref = ref if os.path.isdir(ref) else None
    os.makedirs(a.out, exist_ok=True)
    made, failed = [], False
    for plat in plats:
        if not a.no_build:
            build(plat)
        with tempfile.TemporaryDirectory(prefix="soa-package-") as work:
            dbg_root = os.path.join(work, "debug", f"soa-{version}-{plat}-debug-symbols")
            os.makedirs(dbg_root)
            stages = [(k, *stage_package(plat, k, version, work, dbg_root)) for k in KINDS]
            with open(os.path.join(dbg_root, "README.txt"), "w") as f:
                f.write("Debug info (DWARF line tables) of the programs in the soa release packages of the same version.\n"
                        + ("Linux: put the .debug files beside the programs; gdb finds them through .gnu_debuglink.\n"
                           if not PLATFORMS[plat]["windows"] else
                           "Windows: load them by hand (gdb: symbol-file soa.exe.debug; lldb: target symbols add).\n"))
            stages.append(("debug", os.path.join(work, "debug"), None))
            for kind, stage, _ in stages:
                problems = check(stage, kind, ref)
                name = f"soa-{kind}-{version}-{plat}.zip" if kind != "debug" else f"soa-{version}-{plat}-debug-symbols.zip"
                if problems:
                    failed = True
                    log(f"FAIL {name}: {len(problems)} problem(s):")
                    for p in problems:
                        log("   ", p)
                    continue
                out = os.path.join(a.out, name)
                write_zip(stage, out)
                made.append(out)
                log(f"ok   {name} ({os.path.getsize(out) / 1e6:.1f} MB)")
    if failed:
        log("FAIL: nothing was written for the packages above")
        return 1
    log("done:", *[os.path.relpath(m) for m in made])
    return 0


if __name__ == "__main__":
    sys.exit(main())
