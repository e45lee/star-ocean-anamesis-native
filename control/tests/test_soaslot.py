"""control/soaslot.py: the slot pool without a game (pytest)."""
import os
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
CONTROL = os.path.dirname(HERE)
sys.path.insert(0, CONTROL)
import soaslot  # noqa: E402


def env(tmp_path, n):
    return dict(os.environ, SOA_SLOT_DIR=str(tmp_path), SOA_SLOTS=str(n), SOA_SLOT_MIN_FREE_GB="0", SOA_SLOT_STAGGER="0")


def until(pred, secs=10):
    """Polls pred until it holds (True) or secs pass (False): no fixed sleeps, which a loaded
    machine outruns."""
    end = time.monotonic() + secs
    while time.monotonic() < end:
        if pred():
            return True
        time.sleep(0.05)
    return False


def runs_sleep(pid):
    """The process has exec'd its command (`run` keeps the PID): it holds its slot by then."""
    try:
        return open("/proc/%d/comm" % pid).read().strip() == "sleep"
    except OSError:
        return False


def test_queue_and_release(tmp_path):
    e = env(tmp_path, 2)
    holders = [subprocess.Popen([sys.executable, os.path.join(CONTROL, "soaslot.py"), "run", "--", "sleep", "3"], env=e)
               for _ in range(2)]
    assert until(lambda: all(runs_sleep(h.pid) for h in holders))
    r = subprocess.run([sys.executable, os.path.join(CONTROL, "soaslot.py"), "run", "--name", "third", "--", "true"], env=e,
                       capture_output=True, text=True)
    still = [h.poll() for h in holders]
    for h in holders:
        h.wait()
    assert r.returncode == 0
    assert "waiting for a slot" in r.stderr
    assert still.count(None) <= 1  # queued until a holder exited


def test_exec_keeps_pid_and_slot(tmp_path, monkeypatch):
    e = env(tmp_path, 1)
    p = subprocess.Popen([sys.executable, os.path.join(CONTROL, "soaslot.py"), "run", "--", "sleep", "2"], env=e)
    # the same PID now runs sleep (exec), and it holds the slot
    assert until(lambda: runs_sleep(p.pid))
    for k in ("SOA_SLOT_DIR", "SOA_SLOTS", "SOA_SLOT_MIN_FREE_GB", "SOA_SLOT_STAGGER"):
        monkeypatch.setenv(k, e[k])
    assert soaslot.try_acquire("probe") is None
    p.wait()
    got = soaslot.try_acquire("probe")
    assert got is not None
    soaslot.release(got[0])


def test_shell_take_and_nested(tmp_path):
    e = env(tmp_path, 1)
    script = ('. control/soaslot.sh; soaslot_take outer; echo "held=$SOA_SLOT_HELD";'
              'soaslot_take inner; echo nested-ok')  # a nested take is a no-op (no deadlock with 1 slot)
    r = subprocess.run(["sh", "-c", script], env=e, cwd=os.path.dirname(CONTROL), capture_output=True, text=True, timeout=20)
    assert "held=1" in r.stdout and "nested-ok" in r.stdout


def test_pool_off(tmp_path):
    e = env(tmp_path, 0)
    r = subprocess.run([sys.executable, os.path.join(CONTROL, "soaslot.py"), "run", "--", "true"], env=e, timeout=10)
    assert r.returncode == 0


def test_starts_are_staggered(tmp_path):
    e = dict(env(tmp_path, 4), SOA_SLOT_STAGGER="1.5")
    t0 = time.monotonic()
    for _ in range(3):
        subprocess.run([sys.executable, os.path.join(CONTROL, "soaslot.py"), "run", "--", "true"], env=e, check=True)
    assert time.monotonic() - t0 >= 3.0  # the 2nd and 3rd start waited 1.5 s each


def test_software_gl(tmp_path):
    """SOA_SLOT_SOFTWARE_GL (or run --software-gl) puts the clients on llvmpipe; off by default."""
    e = env(tmp_path, 1)
    for k in ("SOA_SLOT_SOFTWARE_GL", "GALLIUM_DRIVER", "LIBGL_ALWAYS_SOFTWARE", "SOA_SLOT_HELD"):
        e.pop(k, None)
    # a WSL profile's GALLIUM_DRIVER=d3d12 (the host GPU) is overridden when the switch is on
    r = subprocess.run([sys.executable, os.path.join(CONTROL, "soaslot.py"), "run", "--software-gl", "--", "sh", "-c",
                        'echo "[$GALLIUM_DRIVER]"'], env=dict(e, GALLIUM_DRIVER="d3d12"), capture_output=True, text=True)
    assert r.stdout.strip() == "[llvmpipe]"
    py = [sys.executable, os.path.join(CONTROL, "soaslot.py"), "run"]
    show = ["--", "sh", "-c", 'echo "[$GALLIUM_DRIVER][$LIBGL_ALWAYS_SOFTWARE]"']
    assert subprocess.run(py + show, env=e, capture_output=True, text=True).stdout.strip() == "[][]"
    assert subprocess.run(py + ["--software-gl"] + show, env=e, capture_output=True, text=True).stdout.strip() == "[llvmpipe][1]"
    r = subprocess.run(py + show, env=dict(e, SOA_SLOT_SOFTWARE_GL="1"), capture_output=True, text=True)
    assert r.stdout.strip() == "[llvmpipe][1]"
    # the shell side, also when the slot is already held (a script started by a holder)
    script = '. control/soaslot.sh; soaslot_take t; echo "[$GALLIUM_DRIVER][$LIBGL_ALWAYS_SOFTWARE]"'
    for held in ("", "1"):
        e2 = dict(e, SOA_SLOT_SOFTWARE_GL="1", **({"SOA_SLOT_HELD": held} if held else {}))
        r = subprocess.run(["sh", "-c", script], env=e2, cwd=os.path.dirname(CONTROL), capture_output=True, text=True, timeout=20)
        assert r.stdout.strip() == "[llvmpipe][1]", (held, r.stdout, r.stderr)
    r = subprocess.run(["sh", "-c", script], env=e, cwd=os.path.dirname(CONTROL), capture_output=True, text=True, timeout=20)
    assert r.stdout.strip() == "[][]"


def test_software_gl_threads(tmp_path):
    """llvmpipe's LP_NUM_THREADS: 4 by default under the switch, a caller's value wins."""
    e = env(tmp_path, 1)
    for k in ("GALLIUM_DRIVER", "LIBGL_ALWAYS_SOFTWARE", "LP_NUM_THREADS", "SOA_SLOT_HELD"):
        e.pop(k, None)
    py = [sys.executable, os.path.join(CONTROL, "soaslot.py"), "run", "--software-gl", "--", "sh", "-c", 'echo "[$LP_NUM_THREADS]"']
    assert subprocess.run(py, env=e, capture_output=True, text=True).stdout.strip() == "[4]"
    assert subprocess.run(py, env=dict(e, LP_NUM_THREADS="8"), capture_output=True, text=True).stdout.strip() == "[8]"
