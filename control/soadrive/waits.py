"""Condition waits for sessions and flows (docs/code-review-2026-10-06.md T3): a step used to be "tap,
wait N ms, screenshot"; under load N is too short (the next tap lands on a screen still fading in
and is lost, or on the wrong screen), idle it wastes the difference. These wait for what the tap
leads to instead: a log line (tap_to_log, tap_to_phase: the port's phase lines, a server request),
a counted line in any log (tap_to_count, tap_to_server), a screen (tap_to_screen: a popups.is_*
fingerprint, or any screen other than the one tapped), and in every case the screen settled
(settle, screens.Watch) before the next tap. tap_settled: a tap whose effect is too small to see or
that a second tap would undo. A fixed wait stays only where nothing can be observed; the caller
says why next to it. Every target (soa, soa --server, soa-emu) has the screens and the packet
log; the phase lines are soa's only. sessions/common.py re-exports these."""
import os
import re
import time

from . import milestones, screens
from .flows import launch
from .targets import Abort

HOME_MASK = screens.HOME_MOVING  # home: only its header and side buttons hold still
GACHA_MASK = (screens.GACHA_CAROUSEL,)  # the gacha screen: its banner carousel turns


def last_phase(s):
    """The last `port_debug: phase N` the client logged, for a failure's message."""
    m = re.search(r"phase (\d+)", s.last_line(milestones.PORT_PHASE) or "")
    return "phase %s" % m.group(1) if m else "no phase line"


def look(s, name=".look.png"):
    """A screenshot now (in the run's scratch dir); its path, or None when none was written."""
    path = s.scratch(name)
    if os.path.exists(path):
        os.remove(path)
    s.send(["shot:" + path])
    return path if os.path.exists(path) else None


def gave_up(s, name, expected, fatal, watch=None):
    """FAIL name with what was expected, the last phase seen and how the screen looked (miss() keeps
    the screen as OUT/.../fail-NN.png); Abort when fatal, a note only when fatal is None."""
    if not s.alive():
        why = s.gone()
    else:
        seen = last_phase(s)
        if watch is not None and watch.rmse is not None and watch.rmse > watch.limit:
            seen += ", the screen still moving (RMSE %.3f)" % watch.rmse
        why = "expected %s; last seen: %s" % (expected, seen)
    if fatal is None:
        s.note("%s (%s)" % (name, why))
        return None
    s.miss("%s (%s)" % (name, why))
    if fatal:
        raise Abort(name)
    return None


def _keep(s, shot, path):
    if shot and path and os.path.exists(path):
        s.keep_shot(shot, path)


def settle(s, shot=None, secs=30, mask=(), is_screen=None, differs_from=None, name=None, fatal=False, limit=0.01, hold=1):
    """Waits until the screen settles (screens.Watch: two screenshots 0.6 s apart within `limit`,
    `mask` blanked, no flat transition frame, `hold` times in a row; or a screen that moves only a
    little, a pulse or an idle character, for hold x 3 s), and is_screen(path) (a popups.is_*
    fingerprint) and differs from the screenshot differs_from, when given; keeps it as the shot
    SHOT. hold > 1: after an animation that may pause. Returns its path (the run's scratch
    .settle.png), or None after secs: with `name` a FAIL (gave_up; fatal as there), without one a
    note (the last screenshot is kept as SHOT anyway)."""
    w = screens.Watch(s.send, s.scratch(".settle.png"), mask, limit, hold=hold)
    end = time.monotonic() + secs
    first = True
    while True:
        settled = w.look(0 if first else None)
        first = False
        if settled and (is_screen is None or is_screen(w.path)) and (differs_from is None or w.differs(differs_from)):
            w.done()
            _keep(s, shot, w.path)
            if name:
                s.ok(name)
            return w.path
        if not s.alive() or time.monotonic() > end:
            break
    w.done()
    if name:
        what = is_screen.__name__ if is_screen else "a new screen" if differs_from else "a still screen"
        return gave_up(s, name, "%s within %ds" % (what, secs), fatal, w)
    _keep(s, shot, w.path)
    s.note("%s: the screen didn't settle%s within %ds (RMSE %s): taken as it was" %
           (shot or "settle", " or change" if differs_from else "", secs, "%.3f" % w.rmse if w.rmse is not None else "-"))
    return None


def tap_settled(s, xy, shot=None, mask=(), secs=20):
    """A tap whose effect is small or toggles (a list row ticked, a count stepped): made once, then
    the screen settled. No retap (a second tap would take a tick off); the request the next steps
    send checks it."""
    s.ctl("tap:" + xy)
    return settle(s, shot, secs, mask)


def tap_to_screen(s, name, xy, shot=None, is_screen=None, secs=40, tries=3, retap_after=6, mask=(), changed=0.02,
                  fatal=True, cmds=None):
    """Taps xy (or sends cmds) and waits until the screen it leads to settles (settle):
    is_screen(path) (a popups.is_* fingerprint), or without one any screen that differs from the
    one tapped (RMSE above `changed` at screens.WATCH_SIZE). A lost tap (the screen still the one
    tapped, and settled, `retap_after` s after the tap) is made again, at most `tries` taps in all.
    PASS / FAIL name (gave_up: Abort when fatal); keeps the screen as SHOT. Returns its path or
    None. For taps whose effect is a log line (a phase, a request), tap_to_log is the better wait;
    for a tap that changes little or toggles, tap_settled."""
    before = s.scratch(".before.png")
    if look(s, ".before.png") is None:
        before = None
    w = screens.Watch(s.send, s.scratch(".screen.png"), mask)
    taps, tapped, settled = 0, 0.0, False
    end = time.monotonic() + secs
    while True:
        if taps == 0 or (taps < tries and before and time.monotonic() - tapped >= retap_after
                         and settled and not w.differs(before, changed)):
            if taps:
                s.note("%s: the screen didn't change; tapping again (%d)" % (name, taps + 1))
            s.ctl(*(cmds or ["tap:" + xy]))
            taps, tapped = taps + 1, time.monotonic()
        settled = w.look()
        if settled and (is_screen(w.path) if is_screen else (before is None or w.differs(before, changed))):
            w.done()
            _keep(s, shot, w.path)
            s.ok(name)
            return w.path
        if not s.alive() or time.monotonic() > end:
            break
    w.done()
    _keep(s, shot, w.path)
    what = is_screen.__name__ if is_screen else "a screen other than the one tapped"
    return gave_up(s, name, "%s within %ds (%d x %s)" % (what, secs, taps, " ".join(cmds or ["tap:" + xy])), fatal, w)


def tap_to_log(s, name, xy, rx, shot=None, secs=60, every=20, tries=3, mask=(), fatal=False, settle_secs=30, cmds=None,
               stop=milestones.PORT_PHASE, wait_still=True, settle_hold=1):
    """Taps xy (or sends cmds) until the client log has a line matching rx after the log's cursor
    (Run.tap_log: resent every `every` s, at most `tries` times, not once another phase began), then
    waits for the screen to change from the one tapped and settle (settle, `settle_hold`; not with
    wait_still=False: e.g. the keyboard, under which the game draws nothing) and keeps it as SHOT.
    PASS / FAIL name (gave_up: what was expected, the last phase seen; Abort when fatal). Returns
    the line, or None."""
    cmds = list(cmds or ["tap:" + xy])
    before = s.scratch(".before.png") if wait_still else None
    if before and look(s, ".before.png") is None:
        before = None
    line, sent = milestones.tap_until_log(lambda c: s.send(c), s.cursor, rx, secs, every, tries, cmds, stop=stop,
                                          note=lambda m: s.note(m[6:] if m.startswith("note: ") else m), alive=s.alive)
    if line is None:
        return gave_up(s, name, "a log line matching %r within %ds (%d x %s)" % (rx, secs, sent, " ".join(cmds)), fatal)
    s.ok(name)
    if wait_still:
        settle(s, shot, settle_secs, mask, differs_from=before, hold=settle_hold)
    return line


def tap_to_phase(s, name, xy, n, shot=None, secs=60, every=20, tries=3, mask=(), fatal=False, settle_secs=30, cmds=None):
    """tap_to_log for the port's `port_debug: phase N` line (soa only)."""
    return tap_to_log(s, name, xy, launch.phase(n), shot, secs, every, tries, mask, fatal, settle_secs, cmds)


def tap_to_count(s, name, path, rx, cmds, shot=None, secs=40, changes=True, fatal=True, hold=1):
    """cmds (a tap that sends a request), then one more line matching rx in the log at path (counted:
    the server's log, the packet log, which every target writes); sent once more when none came (a
    tap dropped while a screen fades in; only after `secs`, so a slow answer isn't asked twice);
    then the screen after it settled (and, when it `changes`, differing from the one tapped), kept
    as SHOT. PASS / FAIL name (Abort when fatal). True when the line came."""
    n = milestones.count(path, rx)
    screen = look(s, ".count-before.png")
    for attempt in range(2):
        s.ctl(*cmds)
        if s.poll(secs, lambda: milestones.count(path, rx) > n):
            s.ok(name)
            settle(s, shot, differs_from=screen if changes else None, hold=hold)
            return True
        if not s.alive():
            break
        s.note("%s: no line yet; sending %s again" % (name, " ".join(cmds)))
    gave_up(s, name, "a line matching %r in %s within %ds" % (rx, os.path.basename(path), secs), fatal)
    return False


def tap_to_server(s, name, rx, cmds, shot=None, secs=40, changes=True, fatal=True, hold=1):
    """tap_to_count on the server's log (soa's own log in-process, soa-server's otherwise)."""
    return tap_to_count(s, name, s.server_log, rx, cmds, shot, secs, changes, fatal, hold)
