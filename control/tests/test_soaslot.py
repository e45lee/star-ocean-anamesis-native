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


def test_queue_and_release(tmp_path):
    e = env(tmp_path, 2)
    holders = [subprocess.Popen([sys.executable, os.path.join(CONTROL, "soaslot.py"), "run", "--", "sleep", "3"], env=e)
               for _ in range(2)]
    time.sleep(1)
    t0 = time.monotonic()
    r = subprocess.run([sys.executable, os.path.join(CONTROL, "soaslot.py"), "run", "--name", "third", "--", "true"], env=e,
                       capture_output=True, text=True)
    waited = time.monotonic() - t0
    for h in holders:
        h.wait()
    assert r.returncode == 0
    assert "waiting for a slot" in r.stderr
    assert waited >= 1.0  # queued until a holder exited


def test_exec_keeps_pid_and_slot(tmp_path):
    e = env(tmp_path, 1)
    p = subprocess.Popen([sys.executable, os.path.join(CONTROL, "soaslot.py"), "run", "--", "sleep", "2"], env=e)
    time.sleep(0.8)
    # the same PID now runs sleep (exec), and it holds the slot
    assert open("/proc/%d/comm" % p.pid).read().strip() == "sleep"
    os.environ.update(SOA_SLOT_DIR=str(tmp_path), SOA_SLOTS="1", SOA_SLOT_MIN_FREE_GB="0", SOA_SLOT_STAGGER="0")
    try:
        assert soaslot.try_acquire("probe") is None
        p.wait()
        got = soaslot.try_acquire("probe")
        assert got is not None
        soaslot.release(got[0])
    finally:
        for k in ("SOA_SLOT_DIR", "SOA_SLOTS", "SOA_SLOT_MIN_FREE_GB", "SOA_SLOT_STAGGER"):
            os.environ.pop(k, None)


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
