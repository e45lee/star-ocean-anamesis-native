#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Fails on a non-trivial thread_local in our code (runtime/README.md "Per-thread state";
runtime/src/core/thread_record.h).

    tools/check_thread_local.py [BUILD_DIR]     (default build/, as T0's build step left it;
                                                 build-win/ works too: MinGW's emulated TLS)

A thread_local may be a pointer, an integer, a flag, an enum or a POD buffer, constant-initialized.
One whose type has a destructor, or that has a dynamic initializer, belongs in the thread's record
instead: thread_object<T, Tag>() (live::thread_scratch<T>() in a live check).

The compiler knows which ones are non-trivial, so this reads the built objects, not the sources:
  - a destructor: a call to __cxa_thread_atexit (registering the thread's destructor), attributed
    to the function whose section holds it (an inline function has its own COMDAT section; a
    plain one is reported as ".text" with its object file);
  - a dynamic initializer: a TLS guard variable (a function-local thread_local) or a TLS init
    function (_ZTH..., a namespace-scope one).
Allowed: cpp-httplib's own (its header has about ten; soa-server's wire layer; on Windows
server/net/thread_atexit_win32.cpp runs their destructors).
Then the programs other than soa-server must not reference __cxa_thread_atexit at all (which also
catches a third-party library's).
"""
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

ALLOW = re.compile(r"^(guard variable for |TLS init function for |TLS wrapper function for )?httplib::")
# The programs that must reference no __cxa_thread_atexit (soa-server: cpp-httplib's).
PROGRAMS = ["port/soa", "runtime/soaruntime_tests", "emulator/soa-emu", "emulator-viewer/soa-viewer",
            "webview/soa-webview-render"]
SKIP_DIRS = {"_deps", "vcpkg_installed", "mingw-posix"}


def run(*cmd):
    return subprocess.run(cmd, capture_output=True, text=True).stdout


def demangle(names):
    if not names:
        return []
    out = subprocess.run(["c++filt"], input="\n".join(names) + "\n", capture_output=True, text=True).stdout
    return out.splitlines()


def check_object(path):
    """The problems in one object file (list of strings)."""
    problems = []
    syms = run("nm", path)
    if re.search(r"^\s+U __cxa_thread_atexit$", syms, re.M):
        secs, sec = set(), None
        for line in run("objdump", "-r", path).splitlines():  # (ELF and COFF)
            m = re.match(r"^RELOCATION RECORDS FOR \[([^\]]+)\]", line)
            if m:
                sec = m.group(1)
            elif "__cxa_thread_atexit" in line and sec:
                secs.add(sec)
        mangled = []
        for s in sorted(secs):  # .text.NAME (ELF), .text$NAME (COFF), .text
            m = re.match(r"^\.text[.$](.+)$", s)
            mangled.append(m.group(1) if m else "")
        for raw, name in zip(mangled, demangle([m or "-" for m in mangled])):
            if not raw:
                problems.append(f"{path}: a thread_local with a destructor in a function in .text")
            elif not ALLOW.match(name):
                problems.append(f"{path}: a thread_local with a destructor in {name}")
    inits = [l.split()[-1] for l in syms.splitlines() if re.match(r"^\S+ [TW] _ZTH", l)]
    for name in demangle(inits):
        if not ALLOW.match(name):
            problems.append(f"{path}: a thread_local with a dynamic initializer: {name}")
    # (MinGW's emulated TLS: the guard variable is a "__emutls_v." control block)
    for name in demangle(re.findall(r"__emutls_v\.(_ZGV\S+)$", syms, re.M)):
        if not ALLOW.match(name):
            problems.append(f"{path}: a thread_local with a dynamic initializer: {name[len('guard variable for '):]}")
    if "_ZGV" in syms and "__emutls_v." not in syms:
        for line in run("nm", "-C", "-f", "sysv", path).splitlines():
            f = [x.strip() for x in line.split("|")]
            if len(f) >= 7 and f[0].startswith("guard variable for ") and re.match(r"\.t(bss|data)", f[6]):
                if not ALLOW.match(f[0]):
                    problems.append(f"{path}: a thread_local with a dynamic initializer: {f[0][len('guard variable for '):]}")
    return problems


def main():
    bdir = sys.argv[1] if len(sys.argv) > 1 else "build"
    os.chdir(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
    if not os.path.isdir(bdir):
        print(f"FAIL: no {bdir}/ (scripts/build.sh)")
        return 1
    objs = []
    for root, dirs, files in os.walk(bdir):
        dirs[:] = [d for d in dirs if not (root == bdir and d in SKIP_DIRS)]
        objs += [os.path.join(root, f) for f in files if f.endswith((".o", ".obj"))]
    problems = []
    with ThreadPoolExecutor(max_workers=8) as ex:
        for p in ex.map(check_object, sorted(objs)):
            problems += p
    nprog = 0
    for prog in PROGRAMS:
        exe = os.path.join(bdir, prog)
        if not os.path.exists(exe):
            exe += ".exe"  # (the Windows build: tools/check_thread_local.py build-win)
            if not os.path.exists(exe):
                continue
        nprog += 1
        if "__cxa_thread_atexit" in run("nm", exe) + run("nm", "-D", exe):
            problems.append(f"{exe}: references __cxa_thread_atexit (a thread_local with a destructor, ours or a library's)")
    for p in problems:
        print("FAIL:", p)
    if problems:
        print("FAIL: non-trivial thread_local: use thread_object<T, Tag>() (runtime/src/core/thread_record.h; "
              "runtime/README.md \"Per-thread state\")")
        return 1
    if not objs:
        print(f"FAIL: no object files in {bdir}/")
        return 1
    if nprog == 0:
        # the programs' check (a library's thread_local with a destructor) would have checked nothing
        print(f"FAIL: none of the programs ({', '.join(PROGRAMS)}) in {bdir}/ (scripts/build.sh)")
        return 1
    print(f"PASS: no non-trivial thread_local ({len(objs)} objects, {nprog} programs; cpp-httplib's allowed)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
