"""tools/server_evidence.py's verdicts for tools/check_server_docs.sh (pytest, on a made-up tree):
--check decides by exit code, and --waivers takes a commit's "Evidence removed:" line for that
commit's loss only."""
import os
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOOL = os.path.join(REPO, "tools", "server_evidence.py")


def tree(root, code, patterns=""):
    """A minimal checkout: one server source, the two docs, the log patterns."""
    os.makedirs(os.path.join(root, "server", "src"), exist_ok=True)
    os.makedirs(os.path.join(root, "docs"), exist_ok=True)
    os.makedirs(os.path.join(root, "tools"), exist_ok=True)
    open(os.path.join(root, "server", "src", "a.cpp"), "w").write(code)
    open(os.path.join(root, "docs", "server-rules.md"), "w").write("# Rules\n\n<a id=\"coins\"></a>\n## Coins\n")
    open(os.path.join(root, "docs", "api.md"), "w").write("# API\n")
    open(os.path.join(root, "tools", "server_log_patterns.txt"), "w").write(patterns)


def evidence(root, *args):
    r = subprocess.run([sys.executable, TOOL, "--root", str(root)] + list(args), capture_output=True, text=True)
    return r.returncode, r.stdout + r.stderr


CLEAN = '// (a) master_coin: the price. docs/server-rules.md#coins\nvoid f() { LOG("coin shop opened"); }\n'


def test_check_exit_codes(tmp_path):
    tree(tmp_path, CLEAN, "coin shop opened\tthe shop\n")
    assert evidence(tmp_path, "--check")[0] == 0
    tree(tmp_path, CLEAN + "// agent foo wrote this\n", "coin shop opened\tthe shop\n")
    rc, out = evidence(tmp_path, "--check")
    assert rc == 10 and "agent mentions" in out
    tree(tmp_path, CLEAN.replace("#coins", "#nowhere"), "coin shop opened\tthe shop\n")
    assert evidence(tmp_path, "--check")[0] == 10  # a broken link
    tree(tmp_path, CLEAN, "coin shop closed\tthe shop\n")  # a log line scripts wait on is gone
    assert evidence(tmp_path, "--check")[0] == 11


def git(root, *args):
    subprocess.run(["git", "-c", "user.name=t", "-c", "user.email=t@example.com"] + list(args), cwd=root, check=True,
                   capture_output=True)


def commit(root, code, msg):
    tree(root, code)
    git(root, "add", "server", "docs", "tools")
    git(root, "commit", "-q", "-m", msg)


TWO = "// (a) master_coin: the price\n// (d) master_gem: an assumption\nvoid f() {}\n"


def test_a_waiver_covers_only_its_own_commit(tmp_path):
    git(tmp_path, "init", "-q")
    commit(tmp_path, TWO, "base")
    git(tmp_path, "tag", "base")
    commit(tmp_path, TWO.replace("(d) master_gem", "master_gem"), "drop a label\n\nEvidence removed: the (d) on gems")
    rc, out = evidence(tmp_path, "--against", "base", "--waivers")
    assert rc == 0 and "waived" in out
    assert evidence(tmp_path, "--against", "base")[0] == 1  # without --waivers a loss is a loss
    # a second commit loses more, without saying so: the first commit's line doesn't cover it
    commit(tmp_path, "// master_coin: the price\nvoid f() {}\n", "tidy")
    rc, out = evidence(tmp_path, "--against", "base", "--waivers")
    assert rc == 1 and "tidy" in out and "NOT WAIVED" in out
    # nor do uncommitted changes, which have no message
    git(tmp_path, "reset", "-q", "--hard", "HEAD~1")
    tree(tmp_path, "void f() {}\n")
    rc, out = evidence(tmp_path, "--against", "base", "--waivers")
    assert rc == 1 and "uncommitted" in out
