"""tools/subsystem.py: scaffolding subsystems on parallel branches never conflicts (pytest; no game, no build).

The native rebuild runs one agent per subsystem (port/PLAN.md task 6, "Parallelism"), so two branches
that each scaffold and fill a subsystem must touch only their own folders and merge cleanly.
"""
import os
import shutil
import subprocess
import sys

import pytest

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TOOL = os.path.join(REPO, "tools", "subsystem.py")
# The shared files a subsystem must never need to edit (copied into the scratch repository).
SHARED = ["port/CMakeLists.txt", "port/src/native/README.md", "port/PLAN.md"]


def run(cwd, *args):
    r = subprocess.run(list(args), cwd=cwd, capture_output=True, text=True)
    assert r.returncode == 0, f"{args}: {r.stdout}{r.stderr}"
    return r.stdout


def git(cwd, *args):
    return run(cwd, "git", "-c", "user.name=t", "-c", "user.email=t@t", "-c", "commit.gpgsign=false", *args)


def fill(root, name):
    """What an agent's branch adds: the scaffold, a struct, a native source, a decompile, symbols."""
    run(root, sys.executable, TOOL, "--root", root, "new", name, "--title", f"dummy {name}", "--scope", f"^C{name.title()}::")
    with open(os.path.join(root, f"port/src/native/{name}/{name}_layout.h")) as f:
        text = f.read()
    text = text.replace(f"}}  // namespace soa::native::{name}",
                        f"struct C{name.title()} {{\n    const void* vtable;\n    u32 m_id;\n    u8 unk_0c[4];\n}};\n"
                        f"static_assert(sizeof(C{name.title()}) == 0x10);\n\n}}  // namespace soa::native::{name}")
    with open(os.path.join(root, f"port/src/native/{name}/{name}_layout.h"), "w") as f:
        f.write(text)
    with open(os.path.join(root, f"port/src/native/{name}/{name}_natives.cpp"), "w") as f:
        f.write(f'#include "native/{name}/{name}_layout.h"\n')
    with open(os.path.join(root, f"port/decomp/{name}/{name}.c"), "w") as f:
        f.write(f"// ==== C{name.title()}::Get()\n// vaddr 0x1000 | ghidra 0x101000 | size 8 | symbol x | lib l | d\n")
    with open(os.path.join(root, f"port/decomp/{name}/symbols.tsv"), "a") as f:
        f.write(f"0x1000\t0x101000\t8\t_ZN{name}\tC{name.title()}::Get()\t{name}\tnative\t\n")
    if shutil.which("clang++"):
        run(root, sys.executable, TOOL, "--root", root, "export-types", name)


@pytest.fixture
def scratch(tmp_path):
    root = str(tmp_path / "repo")
    for p in SHARED:
        os.makedirs(os.path.dirname(os.path.join(root, p)), exist_ok=True)
        shutil.copy(os.path.join(REPO, p), os.path.join(root, p))
    git(root, "init", "-q", "-b", "main")
    git(root, "add", ".")
    git(root, "commit", "-qm", "base")
    return root


def test_two_subsystems_on_two_branches_merge_cleanly(scratch):
    for name in ("dummya", "dummyb"):
        git(scratch, "checkout", "-q", "-b", name, "main")
        fill(scratch, name)
        git(scratch, "add", ".")
        git(scratch, "commit", "-qm", name)
        changed = run(scratch, "git", "diff", "--name-only", "main", name).split()
        own = (f"port/src/native/{name}/", f"port/decomp/{name}/")
        assert changed and all(p.startswith(own) for p in changed), f"{name} touched shared files: {changed}"
    git(scratch, "checkout", "-q", "main")
    git(scratch, "merge", "-q", "--no-edit", "dummya")
    git(scratch, "merge", "-q", "--no-edit", "dummyb")  # raises on a conflict
    out = run(scratch, sys.executable, TOOL, "--root", scratch, "list")
    assert "dummya" in out and "dummyb" in out
    check = [sys.executable, TOOL, "--root", scratch, "check"] + ([] if shutil.which("clang++") else ["--no-compile"])
    out = run(scratch, *check)
    assert "ok   dummya" in out and "ok   dummyb" in out


def test_new_refuses_to_overwrite_and_bad_names(scratch):
    run(scratch, sys.executable, TOOL, "--root", scratch, "new", "dummyc")
    for name in ("dummyc", "Bad-Name", "ui"):
        r = subprocess.run([sys.executable, TOOL, "--root", scratch, "new", name], capture_output=True, text=True)
        assert r.returncode != 0


@pytest.mark.skipif(not shutil.which("clang++"), reason="export-types needs clang++")
def test_check_finds_a_stale_types_json(scratch):
    fill(scratch, "dummyd")
    hdr = os.path.join(scratch, "port/src/native/dummyd/dummyd_layout.h")
    with open(hdr) as f:
        text = f.read()
    with open(hdr, "w") as f:
        f.write(text.replace("u8 unk_0c[4];", "u32 m_flags;"))
    r = subprocess.run([sys.executable, TOOL, "--root", scratch, "check"], capture_output=True, text=True)
    assert r.returncode == 1 and "stale" in r.stdout


def test_repo_subsystems_check():
    args = [sys.executable, TOOL, "check"] + ([] if shutil.which("clang++") else ["--no-compile"])
    r = subprocess.run(args, capture_output=True, text=True)
    assert r.returncode == 0, r.stdout + r.stderr
