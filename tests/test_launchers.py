"""The server-plus-client launchers (scripts/lib/with-server.sh, sourced by the release packages'
run-port-server.sh / run-emulator.sh and scripts/run-*-with-server / run-emulator-370.sh) on a
staged package with stand-in programs: soa-server waited for until its ready line, the client's exit
status passed on, the server stopped after the client; a server without a download, one that
exits early, and the options' arity. Linux only (bash); no game."""
import os
import pathlib
import re
import shutil
import signal
import subprocess
import sys
import time

import pytest

import package

ROOT = pathlib.Path(__file__).resolve().parent.parent

pytestmark = pytest.mark.skipif(sys.platform == "win32", reason="bash launchers")

# soa-server's stand-in: records its arguments and pid, prints the lines the launchers read
# (FAKE_SERVER: "ok", "nocdn" or "die"), then serves until stopped
FAKE_SERVER = """#!/bin/bash
echo "$$" > "$FAKE_DIR/server.pid"
printf '%s\\n' "$@" > "$FAKE_DIR/server.args"
case ${FAKE_SERVER:-ok} in die) echo "soa-server: no game files" >&2; exit 1;; esac
sleep 0.3
echo "soa-server: game 127.0.0.1:1, http 127.0.0.1:81 (bridge x)" >&2
[ "${FAKE_SERVER:-ok}" = nocdn ] || echo "soa-server: CDN http://x/download/1/Android/<name> (1 files)" >&2
echo "soa-server: ready" >&2
exec sleep 60
"""
# the client's stand-in: records its arguments, checks the server is up, exits with FAKE_RC
FAKE_CLIENT = """#!/bin/bash
printf '%s\\n' "$@" > "$FAKE_DIR/client.args"
kill -0 "$(cat "$FAKE_DIR/server.pid")" || exit 99
echo "$$" > "$FAKE_DIR/client.pid"
[ -z "${FAKE_WEDGED:-}" ] || { trap '' TERM; while :; do sleep 0.1; done; }  # (ignores SIGTERM, as a wedged client)
exit ${FAKE_RC:-0}
"""


def stage(tmp_path, kind):
    root = tmp_path / kind
    root.mkdir()
    for f in package.launcher_files(kind, False):
        shutil.copy2(ROOT / "scripts/package" / f, root / f)
    for rel, src in package.launcher_libs(kind, False).items():
        (root / rel).parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(src, root / rel)
    client = {"port": "soa", "emulator": "soa-emu"}[kind]
    for name, text in (("soa-server", FAKE_SERVER), (client, FAKE_CLIENT)):
        (root / name).write_text(text)
        (root / name).chmod(0o755)
    return root


def run(root, launcher, args, tmp_path, **env):
    e = dict(os.environ, HOME=str(tmp_path / "home"), FAKE_DIR=str(tmp_path), **env)
    return subprocess.run([str(root / launcher)] + args, env=e, capture_output=True, text=True, timeout=60)


def server_gone(tmp_path, which="server"):
    pid = int((tmp_path / f"{which}.pid").read_text())
    for _ in range(40):
        try:
            os.kill(pid, 0)
        except ProcessLookupError:
            return True
        time.sleep(0.1)
    os.kill(pid, signal.SIGKILL)
    return False


@pytest.mark.parametrize("kind,launcher", [("port", "run-port-server.sh"), ("emulator", "run-emulator.sh")])
def test_launcher_runs_both_and_stops_the_server(tmp_path, kind, launcher):
    root = stage(tmp_path, kind)
    r = run(root, launcher, ["--port", "45000", "--seed-rng", "7", "--english", "--seed", "save.xml", "--fullscreen"], tmp_path, FAKE_RC="3")
    assert r.returncode == 3, r.stdout + r.stderr  # the client's status
    assert server_gone(tmp_path), "soa-server still runs after the client"
    sargs = (tmp_path / "server.args").read_text().split("\n")
    cargs = (tmp_path / "client.args").read_text().split("\n")
    assert "127.0.0.1:45000" in sargs and "127.0.0.1:45080" in sargs
    assert sargs[sargs.index("--seed-rng") + 1] == "7" and "--english" in sargs
    assert sargs[len(sargs) - 1 - sargs[::-1].index("--seed") + 1] == os.path.join(os.getcwd(), "save.xml")  # (absolute)
    assert "--fullscreen" in cargs and "--english" not in cargs and "--seed-rng" not in cargs
    assert cargs[cargs.index("--server") + 1] == "127.0.0.1:45000"


@pytest.mark.parametrize("mode,why", [("nocdn", "found no 3.7.0 download"), ("die", "didn't start")])
def test_launcher_fails_without_a_download_or_a_server(tmp_path, mode, why):
    root = stage(tmp_path, "port")
    r = run(root, "run-port-server.sh", ["--port", "45010"], tmp_path, FAKE_SERVER=mode)
    assert r.returncode == 1 and why in r.stderr, r.stderr
    assert not (tmp_path / "client.args").exists()
    if mode == "nocdn":
        assert server_gone(tmp_path)


def test_ctrl_c_stops_a_wedged_client_and_the_server(tmp_path):
    """Ctrl-C (twice, as a terminal and a wrapper both forward it): SIGTERM, then SIGKILL for a
    client that ignores it; the server stopped too; status 130."""
    root = stage(tmp_path, "port")
    e = dict(os.environ, HOME=str(tmp_path / "home"), FAKE_DIR=str(tmp_path), FAKE_WEDGED="1")
    p = subprocess.Popen([str(root / "run-port-server.sh"), "--port", "45020"], env=e, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    for _ in range(100):
        if (tmp_path / "client.pid").exists():
            break
        time.sleep(0.1)
    p.send_signal(signal.SIGINT)
    time.sleep(0.2)
    p.send_signal(signal.SIGINT)
    assert p.wait(timeout=30) == 130
    assert server_gone(tmp_path) and server_gone(tmp_path, "client")


@pytest.mark.parametrize("args", [["--port"], ["--port", "x1"], ["--seed"], ["--data"], ["--server", "h:1"]])
def test_launcher_options_arity(tmp_path, args):
    root = stage(tmp_path, "port")
    r = run(root, "run-port-server.sh", args, tmp_path)
    assert r.returncode == 2 and "run-port-server:" in r.stderr and "unbound" not in r.stderr, r.stderr


def test_every_launcher_sources_the_shared_half():
    """The four bash launchers parse the same server options (with-server.sh's list) and wait on the
    server's ready line; the packages ship what they source."""
    lib = (ROOT / "scripts/lib/with-server.sh").read_text()
    for rel in ("scripts/run-emulator-370.sh", "scripts/run-port-with-server.sh", "scripts/package/run-emulator.sh",
                "scripts/package/run-port-server.sh"):
        text = (ROOT / rel).read_text()
        assert re.search(r'^\. "\$(here|repo)/(scripts/)?lib/with-server\.sh"$', text, re.M), rel
        assert "soa-server: game" not in text, rel + ": waits on the ready line (with-server.sh)"
    assert "soa-server: ready" in lib
    for kind in ("port", "emulator"):
        assert "lib/with-server.sh" in package.launcher_libs(kind, False) and "lib/with-server.sh" in package.ALLOW[kind]
    # the ready line is printed by soa-server after the game and CDN lines
    main = (ROOT / "server/app/main.cpp").read_text()
    assert main.index('"soa-server: game ') < main.index('"soa-server: CDN ') < main.index('"soa-server: ready\\n"')


def _option_groups_sh(text):
    body = text[text.index("ws_server_option() {"):]
    body = body[:body.index("\n}\n")]
    return [sorted(m.split(" | ")) for m in re.findall(r"^\s+(--[^)]*)\)", body, re.M)]


def _option_groups_ps1(text):
    body = text[text.index("function WsServerOption"):]
    body = body[:body.index("\n}\n")]
    return [sorted(m.split("|")) for m in re.findall(r"'\^\((--[^)]*)\)\$'", body)]


def test_powershell_launchers_share_the_module():
    """The PowerShell launchers dot-source scripts/lib/with-server.ps1, whose server options are
    with-server.sh's (the same three groups: flags, paths, values); the Windows packages ship it."""
    sh = _option_groups_sh((ROOT / "scripts/lib/with-server.sh").read_text())
    ps = _option_groups_ps1((ROOT / "scripts/lib/with-server.ps1").read_text())
    assert len(sh) == 3 and ps == sh, (sh, ps)
    for rel in ("scripts/windows/run-emulator-370.ps1", "scripts/package/run-emulator.ps1", "scripts/package/run-port-server.ps1"):
        text = (ROOT / rel).read_text()
        assert re.search(r'^\. \(Join-Path \$(here|repo) "(scripts\\)?lib\\with-server\.ps1"\)$', text, re.M), rel
        assert "soa-server: ready" not in text and "Select-String" not in text, rel + ": waits through the module"
    for kind in ("port", "emulator"):
        assert "lib/with-server.ps1" in package.launcher_libs(kind, True) and "lib/with-server.ps1" in package.ALLOW[kind]
    assert "scripts/lib/with-server.ps1" in (ROOT / "scripts/windows-stage.list").read_text()


def test_scripts_wait_on_the_ready_line():
    """Scripts and drivers that start soa-server wait for its ready line, not the game line (the CDN
    line comes between them; on Windows soa-server's stderr is buffered)."""
    out = subprocess.run(["git", "grep", "-n", "soa-server: game", "--", "control", "emulator", "port/scripts", "scripts", "tools"],
                         cwd=ROOT, capture_output=True, text=True)
    assert out.returncode in (0, 1), out.stderr
    hits = [h for h in out.stdout.splitlines() if not h.startswith(("scripts/lib/with-server.", "tools/server_log_patterns.txt"))]
    assert not hits, hits
