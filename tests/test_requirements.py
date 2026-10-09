"""requirements.txt is complete: every third-party module a tracked Python file imports (at the top
level or inside a function) is listed there.

The check reads every tracked *.py with `ast`, drops the standard library (sys.stdlib_module_names)
and the repository's own modules (every tracked .py's stem and every directory holding tracked .py
files), maps import names to package names (Crypto -> pycryptodome, ...) and fails naming each
module whose package is missing, with the files that import it.
"""
import ast
import os
import re
import subprocess
import sys

import pytest

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# import name -> the package requirements.txt lists
PACKAGE_OF = {
    "Crypto": "pycryptodome",
    "PIL": "pillow",
    "cv2": "opencv-python-headless",
    "elftools": "pyelftools",
    "keystone": "keystone-engine",
    "yaml": "pyyaml",
}

# Not pip requirements: PyGhidra ships with the Ghidra install (requirements.txt says how to install
# it), and ghidra / java / jpype exist only inside a PyGhidra session; bpy / mathutils are Blender's
# own modules (tools/asf2gltf/render_blender.py runs inside `blender -b -P`).
NOT_PIP = {"pyghidra", "ghidra", "java", "jpype", "bpy", "mathutils"}


def norm(name):
    return re.sub(r"[-_.]+", "-", name).lower()


def tracked_py():
    try:
        out = subprocess.run(["git", "ls-files", "-z", "*.py"], cwd=REPO, capture_output=True, check=True).stdout
    except (OSError, subprocess.CalledProcessError):
        pytest.skip("not a git checkout")
    return [p for p in out.decode().split("\0") if p]


def requirements():
    names = set()
    with open(os.path.join(REPO, "requirements.txt")) as f:
        for line in f:
            line = line.split("#", 1)[0].strip()
            if line and not line.startswith("-"):
                names.add(norm(re.split(r"[\[<>=!~; ]", line, 1)[0]))
    return names


def imports_of(path):
    """The top-level names of the absolute imports in one file (function-level ones included)."""
    with open(os.path.join(REPO, path), "rb") as f:
        src = f.read()
    tree = ast.parse(src, path)
    out = set()
    for node in ast.walk(tree):
        if isinstance(node, ast.Import):
            out |= {a.name.split(".")[0] for a in node.names}
        elif isinstance(node, ast.ImportFrom) and node.level == 0 and node.module:
            out.add(node.module.split(".")[0])
    return out


def missing_requirements(listed):
    """{module: [files importing it]} for the third-party modules whose package isn't in `listed`."""
    files = tracked_py()
    own = set()
    for p in files:
        own.add(os.path.splitext(os.path.basename(p))[0])
        d = os.path.dirname(p)
        while d:
            own.add(os.path.basename(d))
            d = os.path.dirname(d)
    missing = {}
    for p in files:
        for mod in imports_of(p):
            if mod in sys.stdlib_module_names or mod in own or mod in NOT_PIP:
                continue
            if norm(PACKAGE_OF.get(mod, mod)) not in listed:
                missing.setdefault(mod, []).append(p)
    return missing


def test_requirements_list_every_third_party_import():
    missing = missing_requirements(requirements())
    assert not missing, "imported but not in requirements.txt: " + "; ".join(
        "%s (%s; package %s)" % (m, ", ".join(sorted(fs)[:3]), PACKAGE_OF.get(m, m)) for m, fs in sorted(missing.items()))


def test_the_check_names_an_unlisted_package():
    listed = requirements()
    assert "pyelftools" in listed and "msgpack" in listed
    missing = missing_requirements(listed - {"pyelftools", "msgpack"})
    assert set(missing) == {"elftools", "msgpack"}
    assert "tools/elfinfo.py" in missing["elftools"]


def test_the_check_sees_function_level_imports(tmp_path):
    p = tmp_path / "x.py"
    p.write_text("import os\ndef f():\n    import msgpack\n    from PIL import Image\n    from . import sibling\n")
    rel = os.path.relpath(p, REPO)
    assert imports_of(rel) == {"os", "msgpack", "PIL"}
