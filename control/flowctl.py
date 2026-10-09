#!/usr/bin/env -S sh -c 'exec "${0%/*}/../tools/py" "$0" "$@"'
"""Waiting helpers for the scripted sessions (a thin CLI over control/soadrive: milestones.py, popups.py).

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
  flowctl.py gacha-confirm FIFO PROBE_SHOT
      After a tap on 10連ガチャ: until the draw confirmation shows (screenshots to PROBE_SHOT), tap
      10連ガチャ again on the banner detail, 閉じる on a pick-up's character detail (the carousel's
      pages: a tap on 決定's spot there opens one); at most 6 looks (popups.gacha_confirm). Exit 1
      if the confirmation doesn't show.
"""

import os
import re
import sys
import time

from soadrive import fifo, popups, screens
from soadrive.milestones import Failed, LogCursor, tap_until_log

MAX_RMSE = float(os.environ.get("FLOW_MAX_RMSE", "0.08"))
# kept for importers of the old module (the fingerprints live in soadrive/popups.py)
LOGIN_BONUS_TITLE, FAVOR_BONUS_CLOSE = popups.LOGIN_BONUS_TITLE, popups.FAVOR_BONUS_CLOSE
is_login_bonus, is_favor_bonus = popups.is_login_bonus, popups.is_favor_bonus
Log = LogCursor


def send(fifo_path, *cmds, timeout=60):
    return fifo.send(fifo_path, list(cmds), timeout)


def _err(s):
    print(s, file=sys.stderr, flush=True)


def login_popups(fifo_path, log, notice_shot, bonus_shot, home_shot):
    try:
        print(popups.login_popups(fifo_path, log, notice_shot, bonus_shot, home_shot))
    except Failed as e:
        sys.exit("FAIL: %s" % e)


def name_entry(fifo_path, log, name, typed_shot):
    try:
        print(popups.name_entry(fifo_path, log, name, typed_shot))
    except Failed as e:
        sys.exit("FAIL: %s" % e)


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    cmd = sys.argv[1]
    if cmd == "wait-screen":
        fifo_path, shot, ref = sys.argv[2:5]
        timeout = float(sys.argv[5]) if len(sys.argv) > 5 else 120
        deadline = time.monotonic() + timeout
        best = 1.0
        while time.monotonic() < deadline:
            if send(fifo_path, "shot:" + shot, timeout=30) and os.path.exists(shot):
                best = min(best, screens.rmse(shot, ref))
                if best <= MAX_RMSE:
                    print(f"ok {os.path.basename(shot)} rmse={best:.4g}")
                    return
            time.sleep(1)
        sys.exit(f"FAIL {os.path.basename(shot)}: no match for {ref} (best rmse {best:.4g})")
    elif cmd == "wait-log":
        log, pat = sys.argv[2:4]
        timeout = float(sys.argv[4]) if len(sys.argv) > 4 else 120
        line = LogCursor(log).wait(re.compile(pat), timeout)
        if line is None:
            sys.exit(f"FAIL: no log line matching {pat!r} within {timeout:.0f} s")
        print("ok", line)
    elif cmd == "tap-until":
        if "--" not in sys.argv:
            sys.exit(__doc__)
        k = sys.argv.index("--")
        head, cmds = sys.argv[2:k], sys.argv[k + 1:]
        if len(head) < 3 or not cmds:
            sys.exit(__doc__)
        fifo_path, log, pat = head[:3]
        num = [float(x) for x in head[3:]]
        timeout = num[0] if num else 120
        line, sent = tap_until_log(lambda c: send(fifo_path, *c, timeout=400), log, pat, timeout,
                                   num[1] if len(num) > 1 else 20, int(num[2]) if len(num) > 2 else 5, cmds, note=_err)
        if line is None:
            sys.exit(f"FAIL: no log line matching {pat!r} within {timeout:.0f} s ({sent} x {' '.join(cmds)})")
        print("ok", line)
    elif cmd == "login-popups":
        login_popups(*sys.argv[2:7])
    elif cmd == "name-entry":
        name_entry(*sys.argv[2:6])
    elif cmd == "gacha-confirm":
        fifo_path, probe = sys.argv[2:4]
        if not popups.gacha_confirm(lambda c: send(fifo_path, *c, timeout=60), probe, note=_err):
            sys.exit("FAIL: the draw confirmation didn't open")
        print("ok the draw confirmation is up")
    elif cmd == "shot":
        fifo_path, shot = sys.argv[2:4]
        sys.exit(0 if send(fifo_path, "shot:" + shot) else 1)
    else:
        sys.exit(__doc__)


if __name__ == "__main__":
    main()
