"""The one Python environment (README.md "Setup"): tools/py runs .venv's interpreter with this
checkout's code importable through soa-checkout.pth (scripts/setup-venv.sh), and says what to run
when the environment is missing."""
import os
import re
import shutil
import subprocess
import sys

import pytest

pytestmark = pytest.mark.skipif(sys.platform == "win32", reason="POSIX shell")


def test_checkout_code_imports_from_this_checkout(repo):
    # each module from this checkout, not the main checkout whose .venv a worktree links to
    code = ("import soa_save, soadrive, soaslot, soactl, elfinfo, profile_report\n"
            "for m in (soa_save, soadrive, soaslot, soactl, elfinfo, profile_report): print(m.__file__)")
    out = subprocess.run([str(repo / "tools" / "py"), "-c", code], capture_output=True, text=True, check=True, cwd="/")
    files = out.stdout.split()
    assert len(files) == 6
    for f in files:
        assert os.path.commonpath([f, str(repo)]) == str(repo), f


def test_tools_py_is_the_venv(repo):
    out = subprocess.run([str(repo / "tools" / "py"), "-c", "import sys; print(sys.prefix)"], capture_output=True, text=True, check=True)
    assert out.stdout.strip() == str(repo / ".venv")


def fake_checkout(tmp_path, repo):
    (tmp_path / "tools").mkdir()
    shutil.copy(repo / "tools" / "py", tmp_path / "tools" / "py")
    return tmp_path / "tools" / "py"


def test_tools_py_without_venv(tmp_path, repo):
    r = subprocess.run([str(fake_checkout(tmp_path, repo)), "-c", "pass"], capture_output=True, text=True)
    assert r.returncode == 127
    assert "no Python environment" in r.stderr and "scripts/setup-venv.sh" in r.stderr


def test_tools_py_without_pth(tmp_path, repo):
    py = fake_checkout(tmp_path, repo)
    (tmp_path / ".venv" / "bin").mkdir(parents=True)
    (tmp_path / ".venv" / "lib" / "python3.12" / "site-packages").mkdir(parents=True)
    os.symlink(sys.executable, tmp_path / ".venv" / "bin" / "python")
    r = subprocess.run([str(py), "-c", "pass"], capture_output=True, text=True)
    assert r.returncode == 127
    assert "soa-checkout.pth" in r.stderr and "scripts/setup-venv.sh" in r.stderr


SHEBANG = re.compile(r"""#!/usr/bin/env -S sh -c 'exec "\$\{0%/\*\}/([./a-z]*py)" "\$0" "\$@"'""")
# Not run through tools/py: decompile notes and prototypes kept as documents; the English tools
# (en-prefix's, still on python3; CR8 follow-up)
NOT_RUN = ("docs/", "port/decomp/", "tools/english", "tools/check_english_official.py")


def test_python_shebangs_run_tools_py(repo):
    """Every tracked .py with a shebang (all the executable ones) starts through tools/py."""
    files = subprocess.run(["git", "ls-files", "-s", "*.py"], cwd=repo, capture_output=True, text=True, check=True).stdout
    bad = []
    for ln in files.splitlines():
        mode, path = ln.split()[0], ln.split("\t", 1)[1]
        if path.startswith(NOT_RUN):
            continue
        with open(repo / path, errors="replace") as f:
            first = f.readline().rstrip("\n")
        if not first.startswith("#!"):
            if mode == "100755":
                bad.append(path + ": executable without a shebang")
            continue
        m = SHEBANG.fullmatch(first)
        if not m or os.path.normpath(os.path.join(os.path.dirname(path), m.group(1))) != "tools/py":
            bad.append(path + ": " + first)
    assert not bad, "\n".join(bad)


def test_a_tool_runs_without_python3_on_path(repo, tmp_path):
    # PATH holds only what the shebang and tools/py use: env, sh, dirname; no python3
    for tool in ("env", "sh", "dirname"):
        os.symlink(shutil.which(tool), tmp_path / tool)
    r = subprocess.run([str(repo / "control" / "soaslot.py"), "--help"], env={"PATH": str(tmp_path)},
                       capture_output=True, text=True)
    assert r.returncode == 0, r.stderr
    assert "slot pool" in r.stdout
