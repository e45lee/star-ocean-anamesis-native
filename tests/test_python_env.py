"""The one Python environment (README.md "Setup"): tools/py runs .venv's interpreter with this
checkout's code importable through soa-checkout.pth (scripts/setup-venv.sh), and says what to run
when the environment is missing."""
import os
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
