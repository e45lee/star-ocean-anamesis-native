#!/usr/bin/env python3
"""Fails on environment access outside common/include/soa/env.h (docs/environment.md, AGENTS.md
"Settings are command-line flags").

    tools/check_env_access.py            (T0 `env-access`; reads the tracked C/C++ sources)

The programs read their diagnostics and test switches through soa/env.h (env_str / env_on /
env_int / env_list: one on/off rule, numbers range-checked), and never set the environment to
carry game or run state (port/src/core/options.h: RunOptions). So a call of getenv / setenv /
unsetenv / putenv (or the Windows spellings) is an error anywhere but in the places below, which
implement the environment rather than use it. Comments and string literals don't count.
"""
import os
import re
import subprocess
import sys

REPO = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))

CALLS = re.compile(r"\b(getenv|secure_getenv|_wgetenv|_dupenv_s|setenv|unsetenv|putenv|_putenv|_putenv_s|_wputenv|"
                   r"clearenv|SetEnvironmentVariable[AW]?|GetEnvironmentVariable[AW]?)\s*\(")

# path -> why it may touch the environment directly
ALLOWED = {
    "common/include/soa/env.h": "the accessors themselves",
    "common/include/soa/paths.h": "the platform's own variables (HOME, LOCALAPPDATA, USERPROFILE) for the data dir",
    "common/src/posix_compat_win32.cpp": "setenv / unsetenv for MinGW (over _putenv_s)",
    "common/win32/posix_compat.h": "setenv / unsetenv for MinGW (the declarations)",
    "common/tests/env_tests.cpp": "the env.h tests set what they read",
    "common/tests/paths_tests.cpp": "the paths.h tests set HOME and read TEMP",
    "runtime/src/hle/libc.cpp": "the guest's getenv (TZ, HOME, TMPDIR from the host)",
    "port/src/native/ui/local_time_test.cpp": "the platform370/local-time selftest sets TZ around its zones and restores it",
}
EXTS = (".c", ".cc", ".cpp", ".h", ".hpp", ".inc")
ROOTS = ("common", "runtime", "port", "server", "emulator", "emulator-viewer", "platform370", "webview", "tests",
         "tools", "control")


def strip(src):
    """`src` with comments, string and character literals blanked (newlines kept, so lines still count)."""
    out, i, n = [], 0, len(src)
    while i < n:
        c = src[i]
        if src.startswith("//", i):
            j = src.find("\n", i)
            j = n if j < 0 else j
            i = j
        elif src.startswith("/*", i):
            j = src.find("*/", i + 2)
            j = n if j < 0 else j + 2
            out.append("\n" * src.count("\n", i, j))
            i = j
        elif c == "R" and src.startswith('R"', i) and (i == 0 or not (src[i - 1].isalnum() or src[i - 1] == "_")):
            k = src.find("(", i + 2)
            delim = ")" + src[i + 2:k] + '"'
            j = src.find(delim, k)
            j = n if j < 0 else j + len(delim)
            out.append('""' + "\n" * src.count("\n", i, j))
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and src[j] != c and src[j] != "\n":
                j += 2 if src[j] == "\\" else 1
            out.append(c + c)
            i = j + 1
        else:
            out.append(c)
            i += 1
    return "".join(out)


def violations(path, text):
    for no, line in enumerate(strip(text).split("\n"), 1):
        for m in CALLS.finditer(line):
            yield no, m.group(1)


def main():
    files = subprocess.run(["git", "-C", REPO, "ls-files", "--", *ROOTS], capture_output=True, text=True,
                           check=True).stdout.split()
    bad = 0
    for f in files:
        if not f.endswith(EXTS) or f in ALLOWED:
            continue
        try:
            text = open(os.path.join(REPO, f), encoding="utf-8", errors="replace").read()
        except FileNotFoundError:  # (deleted in the work tree)
            continue
        for no, fn in violations(f, text):
            print(f"{f}:{no}: {fn}() outside soa/env.h: read the variable through env::env_str / env_on / env_int "
                  "(common/include/soa/env.h), or keep the state in RunOptions instead of the environment")
            bad += 1
    for f in ALLOWED:
        if not os.path.exists(os.path.join(REPO, f)):
            print(f"tools/check_env_access.py: the allowed file {f} is gone: drop it from ALLOWED")
            bad += 1
    if bad:
        sys.exit(1)
    print("env-access: ok (%d sources)" % sum(f.endswith(EXTS) for f in files))


if __name__ == "__main__":
    main()
