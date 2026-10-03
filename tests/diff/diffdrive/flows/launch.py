"""Title -> Login -> the data check -> home -> the login popups (PLAN-consolidate D5, D6): the same
on every target; milestones from the packet log and the client's log only."""
import os
import sys
import time

from .. import screens, ui370
from ..proc import REPO
from ..targets import Abort

sys.path.insert(0, os.path.join(REPO, "control"))
import flowctl  # noqa: E402  (control/flowctl.py: login_popups)

# The screens title() and login_to_home() take (RMSE limits against the emulator's; None: shown,
# not gated). Home: the still parts at the still limit, the character masked.
HOME = (0.08, (screens.HOME_CHARACTER,))
SCREENS = {
    "01-title": 0.08,
    "02a-notice": None,
    "02b-login-bonus": 0.08,
    "02-home": HOME,
}


def title(s):
    """Boot -> the title's NoLoginStart answered (a communication-error dialog's リトライ, where TAP
    TO START is, when the first request was lost) -> 01-title."""
    if not s.poll(150, lambda: s.in_packets(r"< NoLoginStartRes")):
        s.note("no NoLoginStart answer yet: tapping リトライ")
        s.tap_until("NoLoginStart -> NoLoginStartRes (after リトライ)", 120, ui370.TITLE, lambda: s.in_packets(r"< NoLoginStartRes"))
    else:
        s.ok("NoLoginStart -> NoLoginStartRes")
    # A communication-error dialog (1002) over the title after the first answer, seen on soa-emu
    # (emulator/scripts/summer_demo.sh handles it the same way): the title is bright where the
    # dialog is dark; its リトライ (where TAP TO START is) sends NoLoginStart again (the packet
    # comparison counts a repeated NoLoginStart once).
    probe = s.scratch("title-probe.png")
    for i in range(4):
        s.send(["wait:5000", "shot:" + probe])
        if (screens.mean(probe) or 0) > 0.45:
            break
        s.note("an error dialog over the title: リトライ (%d)" % (i + 1))
        k = s.n_packets(r"< NoLoginStartRes")
        s.ctl("tap:" + ui370.TITLE)
        s.poll(60, s.more_than(r"< NoLoginStartRes", k))
    s.shot("01-title")


def data_check(s, until, name):
    """After Login: the phone has the data, so the client only checks its manifests and goes on to
    `until`; when it lacks something (e.g. the master the server edited for the run's clock) its
    dialogs' buttons (決定, ダウンロード, 完了) are tapped in turn until `until`."""
    # The dialog comes (or the client goes on) a few seconds after the manifests: wait for those
    # (the last, version_latest_Individual.bin), then 12 s, not a blind 90 s (the master the server
    # edits for the run's clock is on no phone: every run of every flow shows the dialog).
    manifests = lambda: s.in_client(r"I/http: GET \S*/version_latest_Individual\.bin")
    if s.poll(90, lambda: until() or manifests()) and s.poll(12, until):
        s.ok(name)
        return
    s.note("a data dialog: tapping 決定 / ダウンロード / 完了 in turn")
    end, i = time.monotonic() + 600, 0
    while not s.poll(6, until):
        if not s.alive() or time.monotonic() > end:
            s.miss(name + " (after the data dialogs)")
            raise Abort(name)
        s.ctl("tap:" + (ui370.DATA_DECIDE, ui370.DATA_DOWNLOAD, ui370.DATA_DONE)[i % 3])
        i += 1
    s.ok(name + " (after a download)")


def popups(s, notice, bonus):
    """The notice board (閉じる until its web view closes) and the LOGIN BONUS popup
    (control/flowctl.py login_popups), with a screenshot of each."""
    sh = lambda n: os.path.join(s.shots, n + ".png")
    try:
        flowctl.login_popups(s.fifo, s.client_log, sh(notice), sh(bonus), "-")
        s.ok("login popups closed")
    except SystemExit as e:
        s.miss("login popups (%s)" % e)
        raise Abort("login popups")


def login_to_home(s):
    """TAP TO START -> Login -> LoginResult -> the data check -> the notice board -> the popups -> 02-home."""
    s.tap_until("TAP TO START -> Login", 120, ui370.TITLE, lambda: s.in_packets(r"> Login "))
    s.wait_for("Login -> LoginResult", 60, lambda: s.in_packets(r"< LoginResult"))
    data_check(s, lambda: s.in_client(r"ShowWebView\(http"), "home (the notice board)")
    popups(s, "02a-notice", "02b-login-bonus")
    s.ctl("wait:3000")
    s.shot("02-home")
