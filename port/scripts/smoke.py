#!/usr/bin/env -S sh -c 'exec "${0%/*}/../../tools/py" "$0" "$@"'
"""End-to-end regression run of the port on the 3.7.0 client (the in-process server).

Usage: smoke.py SOA OUT_DIR [BASELINE_DIR] [extra soa args...]

The session is title -> (TAP TO START, Login, the data check, the notice board and the LOGIN BONUS
popup) -> home -> キャラクター (the character menu) -> 装備・技・アシスト変更 (the character list) ->
a character's detail -> 戻る -> ホーム -> その他 (the other menu). Screenshots land in
OUT_DIR/NN-name.png, with a side-by-side strip in OUT_DIR/strip.png.

- The way from the title to home isn't matched by screen: it waits for log lines (the title's
  phase 1, Login, the data check, home's phase 4; port/scripts/phone370.sh) and closes the login
  popups (control/flowctl.py login-popups), in both modes.
- Without a baseline, each later step waits a fixed time, generously, and the screenshots become
  a new baseline.
- With a baseline (an earlier run's OUT_DIR, normally tests/smoke-base), each step polls
  screenshots until the screen matches the baseline's (soadrive.screens.rmse on a downscaled copy <=
  SMOKE_MAX_RMSE, default 0.08; the home character animates and the mascot's line changes, so the
  home screens get 0.12) and only then taps. That keeps the run independent of machine load. A
  step that never matches within SMOKE_STEP_TIMEOUT seconds (default 90) fails the run.

The phone: the shared pre-downloaded 3.7.0 phone, linked (port/scripts/phone370.sh; SOA_PHONE=DIR
another, SOA_PHONE=none an empty one: the client downloads its 3 GB first). The client save is
data/saves/client/Game.xml; the local server seeds itself from data/saves/seed/Game.xml with
--seed-rng 1 (SEED_RNG) and its clock fixed at SMOKE_CLOCK (default 2026-09-30 12:00:00), so the
home (stamina, the login bonus day, the open events) is the same on every run. OUT_DIR/data (the
run's phone) is deleted after a PASS unless SMOKE_KEEP_DATA=1. Exit status 0 = pass.
soa runs headless (--headless: no window, same rendering); WATCH=1 shows the window (--windowed).
The offline port's baselines (its title -> character list flow) are in work/port-test/smoke-base-380 (380-ok).
"""
import os
import shutil
import subprocess
import sys
import time

from soadrive.screens import rmse  # (182x324 copies; 1.0 when it can't compare)

REPO = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
MAX_RMSE = float(os.environ.get("SMOKE_MAX_RMSE", "0.08"))
STEP_TIMEOUT = float(os.environ.get("SMOKE_STEP_TIMEOUT", "90"))
CLOCK = os.environ.get("SMOKE_CLOCK", "2026-09-30 12:00:00")

# (screenshot name, seconds to wait before it when there's no baseline, action after it).
# "login" = TAP TO START -> Login -> the data check -> home -> the login popups.
STEPS = [
    ("01-title", 0, "login"),
    ("02-home", 6, "tap:180:1250"),        # footer キャラクター (phase 11)
    ("03-charmenu", 8, "tap:364:435"),     # 装備・技・アシスト変更
    ("04-charlist", 8, "tap:364:600"),     # the third row's middle character
    ("05-chardetail", 8, "tap:100:1120"),  # 戻る
    ("06-closed", 6, "tap:60:1250"),       # footer ホーム (phase 4)
    ("07-home", 10, "tap:665:1250"),       # footer その他 (phase 12)
    ("08-other", 8, "quit"),
]


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    soa = os.path.abspath(sys.argv[1])
    out = os.path.abspath(sys.argv[2])
    base = os.path.abspath(sys.argv[3]) if len(sys.argv) > 3 and sys.argv[3] else None
    extra = sys.argv[4:]

    os.makedirs(out, exist_ok=True)
    data = os.path.join(out, "data")
    for f in os.listdir(out):
        if f[:2].isdigit() and f.endswith(".png"):
            os.remove(os.path.join(out, f))
    logpath = os.path.join(out, "log.txt")
    for f in (logpath + ".pos", os.path.join(out, "strip.png")):
        if os.path.exists(f):
            os.remove(f)
    # The phone (phone370_prepare: the shared phone linked, SOA_PHONE's, or empty; no local KVS)
    # and the client save.
    # (phone370_client_save: the committed save with no episode pack on its books.)
    # The machine-wide game slot pool (control/soaslot.py): queued here; soa inherits the slot.
    import soaslot
    slot = soaslot.acquire("smoke")
    subprocess.run(["sh", "-c", '. port/scripts/phone370.sh && phone370_prepare "$1" && phone370_client_save "$1/data/shared_prefs"', "sh", data],
                   cwd=REPO, check=True, env=dict(os.environ, SOA_SLOT_HELD="1"))
    fifo = os.path.join(out, "control.fifo")
    if os.path.exists(fifo):
        os.remove(fifo)  # soa creates it

    log = open(logpath, "w")
    # --headless unless WATCH=1 (no window, same rendering); the server's RNG fixed (SEED_RNG, default 1); the
    # game screen the window's size on any desktop (--render-size window: the hi-res pixels don't depend on it)
    headless = "--windowed" if os.environ.get("WATCH") == "1" else "--headless"
    proc = subprocess.Popen([soa, headless, "--seed-rng", os.environ.get("SEED_RNG", "1"), "--data", data, "--size", "729x1296",
                             "--render-size", "window", "--clock", CLOCK, "--control", fifo] + extra,
                            cwd=REPO, stdout=log, stderr=subprocess.STDOUT, pass_fds=(slot,) if slot >= 0 else ())

    for _ in range(1200):
        if os.path.exists(fifo) or proc.poll() is not None:
            break
        time.sleep(0.1)

    def send(*cmds, timeout=60):
        if proc.poll() is not None:
            return False
        try:
            return subprocess.run([sys.executable, os.path.join(REPO, "control/soactl.py"), "--timeout",
                               str(timeout), fifo] + list(cmds), capture_output=not os.environ.get("SMOKE_DEBUG"),
                                  timeout=timeout + 30).returncode == 0
        except subprocess.TimeoutExpired:
            return False

    def sh(script, timeout):
        """A phone370.sh / flowctl.py step (exit status 0 = reached)."""
        try:
            r = subprocess.run(["sh", "-c", ". port/scripts/phone370.sh && " + script, "sh", fifo, logpath, out],
                               cwd=REPO, capture_output=True, text=True, timeout=timeout)
        except subprocess.TimeoutExpired:
            return False, "timed out"
        return r.returncode == 0, (r.stdout + r.stderr).strip()

    failures = []
    results = []
    try:
        # The title: its phase-1 log line first (the boot takes a while under the JIT).
        ok, msg = sh('tools/py control/flowctl.py wait-log "$2" "port_debug: phase 1 " 300', 330)
        if not ok:
            failures.append("no title (phase 1): " + msg.splitlines()[-1] if msg else "no title")
        for name, delay, action in ([] if failures else STEPS):
            final = os.path.join(out, name + ".png")
            if base is None:
                send(f"wait:{max(delay, 3) * 1000}", "shot:" + final, timeout=delay + 60)
            else:
                ref = os.path.join(base, name + ".png")
                # The home screens show the save's animated 3D home character and the mascot's
                # changing line; they get a looser limit.
                limit = max(MAX_RMSE, 0.12) if name.endswith("-home") else MAX_RMSE
                probe = os.path.join(out, "probe.png")
                deadline = time.monotonic() + STEP_TIMEOUT
                best = 1.0
                while True:
                    if proc.poll() is not None:
                        break
                    if send("shot:" + probe, timeout=30) and os.path.exists(probe):
                        d = rmse(probe, ref)
                        best = min(best, d)
                        if d <= limit:
                            break
                    if time.monotonic() > deadline:
                        break
                    time.sleep(1)
                if os.path.exists(probe):
                    os.replace(probe, final)
                ok = best <= limit
                results.append(f"{'ok' if ok else 'FAIL'} {name}.png rmse={best:.4g}")
                print(results[-1], flush=True)
                if not ok:
                    failures.append(name)
                    break
            if proc.poll() is not None:
                failures.append(f"soa exited early (status {proc.returncode})")
                break
            if action == "login":
                # TAP TO START -> Login -> the data check (or download) -> home (phase 4), then the
                # notice board and the LOGIN BONUS popup.
                ok, msg = sh('phone370_login "$1" "$2"', 900)
                if ok:
                    ok, msg = sh('tools/py control/flowctl.py login-popups "$1" "$2" - - -', 300)
                print(("ok   " if ok else "FAIL ") + "login: " + (msg.splitlines()[-1] if msg else ""), flush=True)
                if not ok:
                    failures.append("login: " + msg)
                    break
                continue
            send("wait:500", action)
            time.sleep(1.5)
        try:
            rc = proc.wait(timeout=30)
        except subprocess.TimeoutExpired:
            proc.kill()
            rc = "killed"
        if rc not in (0, None) and not failures:
            failures.append(f"soa exited with status {rc}")
    finally:
        if proc.poll() is None:
            proc.kill()
            proc.wait()
        if os.path.exists(fifo):
            os.remove(fifo)

    shots = [os.path.join(out, n + ".png") for n, _, _ in STEPS if os.path.exists(os.path.join(out, n + ".png"))]
    if shots:
        args = []
        for s in shots:
            args += ["-i", s]
        chain = "".join(f"[{i}]scale=182:324[v{i}];" for i in range(len(shots)))
        chain += "".join(f"[v{i}]" for i in range(len(shots))) + f"hstack={len(shots)}" if len(shots) > 1 else "[v0]null"
        subprocess.run(["ffmpeg", "-loglevel", "error", "-y"] + args + ["-filter_complex", chain,
                        os.path.join(out, "strip.png")])
    if len(shots) != len(STEPS) and not failures:
        failures.append(f"only {len(shots)}/{len(STEPS)} screenshots")
    for f in failures:
        print("FAIL:", f)
    if not failures and os.environ.get("SMOKE_KEEP_DATA", "0") != "1":
        shutil.rmtree(data, ignore_errors=True)
    print("smoke: PASS" if not failures else "smoke: FAIL (see strip.png and log.txt in " + out + ")")
    sys.exit(1 if failures else 0)


if __name__ == "__main__":
    main()
