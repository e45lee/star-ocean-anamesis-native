"""Gate checks that must not pass by default (pytest, no build needed): port/scripts/selftest_resilient.sh
decides on the last boot's exit code too, and tools/check_thread_local.py fails when it found no
program to check."""
import os
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def fake_soa(tmp_path, rc, extra=""):
    """A stand-in for `soa --selftest`: two passing tests, the summary, then exit rc."""
    p = tmp_path / "soa"
    p.write_text("#!/bin/sh\n"
                 "echo 'run   t1' >&2; echo 'ok    t1  1.0 ms' >&2\n"
                 "echo 'run   t2' >&2; echo 'ok    t2  1.0 ms' >&2\n"
                 "echo '2/2 native tests passed' >&2\n%s"
                 "exit %d\n" % (extra, rc))
    p.chmod(0o755)
    return str(p)


def selftest(tmp_path, soa):
    env = dict(os.environ, SOA=soa, SOA_SLOTS="0", MAX_RUNS="2")
    env.pop("SOA_SLOT_HELD", None)
    return subprocess.run([os.path.join(REPO, "port/scripts/selftest_resilient.sh"), str(tmp_path / "out")], env=env,
                          capture_output=True, text=True, timeout=60)


def test_selftest_passes_a_clean_boot(tmp_path):
    r = selftest(tmp_path, fake_soa(tmp_path, 0))
    assert r.returncode == 0, r.stdout


def test_selftest_fails_a_crash_after_the_summary(tmp_path):
    r = selftest(tmp_path, fake_soa(tmp_path, 139))  # the summary, then SIGSEGV in the shutdown
    assert r.returncode == 1 and "rc=139" in r.stdout


def test_thread_local_check_needs_a_program(tmp_path):
    """A build dir with objects but none of the programs: the programs' check checked nothing."""
    bdir = tmp_path / "build"
    bdir.mkdir()
    src = tmp_path / "a.c"
    src.write_text("int a(void) { return 1; }\n")
    subprocess.run(["cc", "-c", str(src), "-o", str(bdir / "a.o")], check=True)
    r = subprocess.run([sys.executable, os.path.join(REPO, "tools/check_thread_local.py"), str(bdir)], capture_output=True,
                       text=True)
    assert r.returncode == 1 and "none of the programs" in r.stdout
