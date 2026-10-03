#!/usr/bin/env python3
"""Waiting helpers for the scripted sessions (battle_session.sh, gacha_session.sh, debug_session.sh).

  flowctl.py wait-screen FIFO SHOT REF [TIMEOUT]
      Take screenshots (to SHOT) until one matches REF (ImageMagick RMSE on a 182x324 copy
      <= FLOW_MAX_RMSE, default 0.08), like smoke.py. Exit 1 on timeout (default 120 s).
  flowctl.py wait-log LOG REGEX [TIMEOUT]
      Wait until a line of LOG (soa's output) matches REGEX, counting only lines written after
      the previous wait-log on the same LOG (state in LOG.pos). Exit 1 on timeout (default 120 s).
  flowctl.py shot FIFO SHOT
      One screenshot.
  flowctl.py tap-until FIFO LOG REGEX [TIMEOUT [EVERY [TRIES]]] -- CMD...
      Send CMD... (e.g. tap:270:1085, as soactl.py) and wait for REGEX like wait-log; when it
      hasn't appeared after EVERY seconds (default 20) the commands are sent again (at most
      TRIES times in all, default 5), for taps the game drops under load (during a fade-in, a
      busy frame). No resend once any 'port_debug: phase ' line was logged after the commands
      (a transition to somewhere else started: a second tap could land on the next screen). Exit
      1 when REGEX isn't logged within TIMEOUT seconds (default 120). When the game is quick,
      this is exactly `soactl.py FIFO CMD...` followed by `wait-log LOG REGEX TIMEOUT`.
  flowctl.py login-popups FIFO LOG NOTICE_SHOT BONUS_SHOT HOME_SHOT
      After the restored 3.7.0 login reaches home (phase 4): close the notice board (閉じる at
      364:1133, retried until the client logs its web view closing) and then the LOGIN BONUS
      popup (閉じる at 364:1063, tapped while a screenshot shows the popup's title: it can have
      a second page, and it can appear late), then the favor login bonus popup (フレンドリー
      プレゼント; 閉じる at 364:928, tapped while a screenshot shows its button; waited for when
      the log has the in-process server's "favor login bonus" line), with a screenshot of each
      and of the home after them. A shot path of '-' isn't kept. Exit 1 if a popup doesn't close.
  flowctl.py name-entry FIFO LOG NAME TYPED_SHOT
      The new-player name dialog (after the terms' 同意する): tap the name field (364:647) until
      the client opens its keyboard (StartKeyboardActivity; the dialog fades in and a tap during
      the fade is dropped), only then type NAME (text:, which a keyboard opened later would
      clear), screenshot, then 決定 (364:790) until the client sends CreatePlayer. Exit 1 unless
      CreatePlayer carries NAME.
"""
import os
import re
import shutil
import subprocess
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
MAX_RMSE = float(os.environ.get("FLOW_MAX_RMSE", "0.08"))


def send(fifo, *cmds, timeout=60):
    return subprocess.run([sys.executable, os.path.join(HERE, "soactl.py"), "--timeout", str(timeout), fifo] + list(cmds),
                          capture_output=True).returncode == 0


def rmse(a, b):
    r = subprocess.run(["compare", "-metric", "RMSE", "-resize", "182x324", a, b, "null:"], capture_output=True, text=True)
    out = r.stderr.strip()
    try:
        return float(out[out.index("(") + 1:out.index(")")])
    except ValueError:
        return 1.0


class Log:
    """Reads soa's log from the position the previous wait-log left (LOG.pos)."""

    def __init__(self, path):
        self.path, self.posf = path, path + ".pos"
        self.pos = int(open(self.posf).read()) if os.path.exists(self.posf) else 0

    def size(self):
        return os.path.getsize(self.path)

    def lines(self):
        """The complete lines written since the position, as (start offset, end offset, text);
        the caller moves the position (self.pos = end) past the lines it consumed."""
        with open(self.path, "rb") as f:
            f.seek(self.pos)
            data = f.read()
        end = data.rfind(b"\n") + 1
        out, off = [], self.pos
        for raw in data[:end].split(b"\n")[:-1]:
            out.append((off, off + len(raw) + 1, raw.decode("utf-8", "replace")))
            off += len(raw) + 1
        return out

    def save(self):
        open(self.posf, "w").write(str(self.pos))

    def wait(self, rx, timeout, stop=None, stop_from=0):
        """The first new line matching rx within timeout s (None on timeout). With stop (a regex),
        returns ('stop', line) at the first line at or after offset stop_from matching it instead."""
        deadline = time.monotonic() + timeout
        while True:
            for off, end, line in self.lines():
                self.pos = end
                if rx.search(line):
                    self.save()
                    return line
                if stop is not None and off >= stop_from and stop.search(line):
                    self.save()
                    return ("stop", line)
            if time.monotonic() >= deadline:
                self.save()
                return None
            time.sleep(0.5)


def tap_until(fifo, log, pat, timeout, every, tries, cmds):
    rx, other_phase = re.compile(pat), re.compile(r"port_debug: phase ")
    lg = Log(log)
    deadline = time.monotonic() + timeout
    sent, resend = 0, True
    while True:
        if resend and sent < tries:
            sent_at = lg.size()  # only lines after this count as "another phase started"
            send(fifo, *cmds, timeout=400)
            sent += 1
            if sent > 1:
                print(f"retry {sent}/{tries}: {' '.join(cmds)}", file=sys.stderr)
        left = deadline - time.monotonic()
        if left <= 0:
            break
        r = lg.wait(rx, min(every, left) if resend and sent < tries else left, stop=other_phase if resend else None, stop_from=sent_at)
        if isinstance(r, str):
            print("ok", r)
            return
        if isinstance(r, tuple):  # another phase started: something took the tap, don't resend
            print(f"note: {r[1]} after {' '.join(cmds)}; not resending", file=sys.stderr)
            resend = False
    sys.exit(f"FAIL: no log line matching {pat!r} within {timeout:.0f} s ({sent} x {' '.join(cmds)})")


# The LOGIN BONUS popup's title (LOGIN BONUS -ログインボーナス-): the 729x1296 frame's 560x170+85+120
# crop scaled to 12x12 RGB, from a session screenshot. Other popups' and the home's crops differ by
# a mean 0.13+ (0-1 scale), the popup's own across days and sessions by < 0.01.
LOGIN_BONUS_TITLE = bytes.fromhex(
    "222a452835410e121d0d0f1d0e101b0c19260a202f0b0c161b1918151c290c14260d192d787b8a436e8b2b63852f63842b5c7f306d95"
    "32759e2f648a336a8d29608653677d626e7e575d763b71942f79a83a8abe45a4d845a7e244a9e644a4d93d92c32c86b27d8a967e9399"
    "5b5f73426d8e205a8e20609f2773b9327dc53571b22872ba256aa81e63975d677b71889b74777f355b7f385f8d4a6b96466b9c5077a5"
    "9e979b4e749d4366933e5a84a89d9262828c717e8748628399979f938e98aba19a6f86a0a0a3a7a69c9ca8a49b918b92b1ac9ea3af9e"
    "727c84536781858d95858691a69a957993adaeaba686919ab6ac9f87888d757881a7a1926e757d8d858ca08f8fa89690a991887c879b"
    "a49994ac968fa68e88aa948c938b88817a7d8494938f82836882946d7f9363688152749b747c9368758f5b667f5f627a9184807f787b"
    "9eb0b65d667e47a2c25b84b25a76ad4d7bb45687ba4d87bd4c74a52683af6f77875b6f7e4b96a621617b3876938a89ac7e7d9d7f82a1"
    "91869f727790888ca265abba2b6d82569baa3c6677162a430f1933484b72334061464e743b44672c3a5a3a3c5928465c0f2d42678a93")


def is_login_bonus(shot):
    r = subprocess.run(["convert", shot, "-resize", "729x1296!", "-crop", "560x170+85+120", "+repage", "-resize", "12x12!",
                        "-depth", "8", "rgb:-"], capture_output=True)
    f = r.stdout
    if len(f) != len(LOGIN_BONUS_TITLE):
        return False
    return sum(abs(a - b) for a, b in zip(f, LOGIN_BONUS_TITLE)) / len(f) / 255 < 0.06


# The favor login bonus popup (CFavorCharacterLoginBonus, フレンドリープレゼント, CPopupManager case 6:
# after the LOGIN BONUS): its 閉じる button at 364:928, as a 12x4 RGB signature of the 300x80 crop
# around it (on the home that spot is the home character, where a tap sends UpdateFavorByTap).
FAVOR_BONUS_CLOSE = bytes.fromhex("183755183755183655193756153453113051123051153453193756183755183755193755031741031741061943000d3940516f6d7d9340547125385b00113c051942031741031741102d6f102d6f112e700b296d2a46814661943c588e24407d0d296d112e71102d70102d701c3b5d1b3b5d1b3a5d1d3b5d1636591131561432571936591d3b5c1c3a5b1c395a1c3a5a")


def is_favor_bonus(shot):
    r = subprocess.run(["convert", shot, "-resize", "729x1296!", "-crop", "300x80+215+890", "+repage", "-resize", "12x4!",
                        "-depth", "8", "rgb:-"], capture_output=True)
    f = r.stdout
    if len(f) != len(FAVOR_BONUS_CLOSE):
        return False
    return sum(abs(a - b) for a, b in zip(f, FAVOR_BONUS_CLOSE)) / len(f) / 255 < 0.06


def login_popups(fifo, log, notice_shot, bonus_shot, home_shot):
    lg = Log(log)
    scratch = os.path.join(os.path.dirname(os.path.abspath(log)), ".flowctl-popup.png")
    keep = lambda p: p if p != "-" else scratch
    # 1. the notice board: the client opens its web view (ShowWebView(http...)), 閉じる closes it
    # (SetRootURI("") + ShowWebView()).
    opened = lg.wait(re.compile(r"ShowWebView\(http"), float(os.environ.get("FLOW_NOTICE_WAIT", "120")))
    if opened is None:
        print("note: no notice board opened", file=sys.stderr)
    else:
        closed = re.compile(r"ShowWebView\(\) not supported")
        cmds = ["wait:8000", "shot:" + keep(notice_shot), "tap:364:1133"]
        for n in range(10):
            send(fifo, *cmds, timeout=400)
            if lg.wait(closed, 8) is not None:
                break
            print(f"retry {n + 2}: the notice board is still open", file=sys.stderr)
            cmds = ["tap:364:1133"]
        else:
            sys.exit("FAIL: the notice board didn't close")
    # 2. the LOGIN BONUS popup (after the notice board; each page's 閉じる at 364:1063, which on
    # the home is the gap between the ミッション and スフィア211 buttons).
    deadline = time.monotonic() + float(os.environ.get("FLOW_BONUS_WAIT", "40"))
    seen, taps, cmds = False, 0, ["wait:4000", "shot:" + keep(home_shot)]
    while True:
        send(fifo, *cmds, timeout=400)
        if is_login_bonus(keep(home_shot)):
            if not seen and bonus_shot != "-":
                shutil.copyfile(keep(home_shot), bonus_shot)
            seen, taps = True, taps + 1
            if taps > 8:
                sys.exit("FAIL: the LOGIN BONUS popup didn't close")
            cmds = ["tap:364:1063", "wait:3000", "shot:" + keep(home_shot)]
        elif seen:
            break
        elif time.monotonic() > deadline:
            print("note: no LOGIN BONUS popup", file=sys.stderr)
            break
        else:
            cmds = ["wait:2000", "shot:" + keep(home_shot)]
    # 3. the favor login bonus popup (フレンドリープレゼント), when the server granted one: the
    # in-process server logs it ("favor login bonus"); otherwise one look at the screen.
    with open(log, "rb") as f:
        granted = re.search(rb"favor login bonus [0-9]+: [1-9]", f.read()) is not None
    deadline = time.monotonic() + (20 if granted else 0)
    favor, cmds = 0, ["wait:2000", "shot:" + keep(home_shot)]
    while True:
        send(fifo, *cmds, timeout=400)
        if is_favor_bonus(keep(home_shot)):
            favor += 1
            if favor > 6:
                sys.exit("FAIL: the favor login bonus popup didn't close")
            cmds = ["tap:364:928", "wait:3000", "shot:" + keep(home_shot)]
        elif favor or time.monotonic() > deadline:
            break
        else:
            cmds = ["wait:2000", "shot:" + keep(home_shot)]
    if os.path.exists(scratch):
        os.remove(scratch)
    print(f"ok popups closed (notice {'yes' if opened else 'no'}, login bonus {'x%d' % taps if seen else 'no'}"
          f"{', favor bonus x%d' % favor if favor else ''})")


def name_entry(fifo, log, name, typed_shot):
    lg = Log(log)
    kb = re.compile(r"StartKeyboardActivity\(")
    for n in range(12):
        send(fifo, "wait:1500", "tap:364:647", timeout=400)
        if lg.wait(kb, 4) is not None:
            break
        print(f"retry {n + 2}: no keyboard yet", file=sys.stderr)
        if n % 3 == 2:  # the terms' 同意する may have been dropped: tap it again
            send(fifo, "tap:364:689", "wait:2500", timeout=400)
    else:
        sys.exit("FAIL: the name field never opened the keyboard (StartKeyboardActivity)")
    # While the keyboard is open the game renders no frames, so no screenshot before the text.
    send(fifo, "wait:500", "text:" + name, "wait:1500", "shot:" + typed_shot, timeout=400)
    cp = re.compile(r"request CreatePlayer \(fid [0-9a-f]+\): (.*)$")
    line = None
    for n in range(5):
        send(fifo, "tap:364:790", timeout=400)
        line = lg.wait(cp, 10)
        if line is not None:
            break
        print(f"retry {n + 2}: no CreatePlayer yet", file=sys.stderr)
    if line is None:
        sys.exit("FAIL: 決定 never sent CreatePlayer")
    sent = cp.search(line).group(1).strip()
    if sent != '"%s"' % name:
        sys.exit(f"FAIL: CreatePlayer sent the name {sent}, not \"{name}\"")
    print(f"ok CreatePlayer \"{name}\"")


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    cmd = sys.argv[1]
    if cmd == "wait-screen":
        fifo, shot, ref = sys.argv[2:5]
        timeout = float(sys.argv[5]) if len(sys.argv) > 5 else 120
        deadline = time.monotonic() + timeout
        best = 1.0
        while time.monotonic() < deadline:
            if send(fifo, "shot:" + shot, timeout=30) and os.path.exists(shot):
                best = min(best, rmse(shot, ref))
                if best <= MAX_RMSE:
                    print(f"ok {os.path.basename(shot)} rmse={best:.4g}")
                    return
            time.sleep(1)
        sys.exit(f"FAIL {os.path.basename(shot)}: no match for {ref} (best rmse {best:.4g})")
    elif cmd == "wait-log":
        log, pat = sys.argv[2:4]
        timeout = float(sys.argv[4]) if len(sys.argv) > 4 else 120
        rx = re.compile(pat)
        posf = log + ".pos"
        pos = int(open(posf).read()) if os.path.exists(posf) else 0
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            with open(log, "rb") as f:
                f.seek(pos)
                data = f.read()
            end = data.rfind(b"\n") + 1
            for raw in data[:end].split(b"\n")[:-1]:
                pos += len(raw) + 1
                line = raw.decode("utf-8", "replace")
                if rx.search(line):
                    open(posf, "w").write(str(pos))
                    print("ok", line)
                    return
            time.sleep(0.5)
        open(posf, "w").write(str(pos))
        sys.exit(f"FAIL: no log line matching {pat!r} within {timeout:.0f} s")
    elif cmd == "tap-until":
        if "--" not in sys.argv:
            sys.exit(__doc__)
        k = sys.argv.index("--")
        head, cmds = sys.argv[2:k], sys.argv[k + 1:]
        if len(head) < 3 or not cmds:
            sys.exit(__doc__)
        fifo, log, pat = head[:3]
        num = [float(x) for x in head[3:]]
        tap_until(fifo, log, pat, num[0] if num else 120, num[1] if len(num) > 1 else 20,
                  int(num[2]) if len(num) > 2 else 5, cmds)
    elif cmd == "login-popups":
        login_popups(*sys.argv[2:7])
    elif cmd == "name-entry":
        name_entry(*sys.argv[2:6])
    elif cmd == "shot":
        fifo, shot = sys.argv[2:4]
        sys.exit(0 if send(fifo, "shot:" + shot) else 1)
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
