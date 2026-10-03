"""Title -> Login -> the data check (or the download) -> home -> the login popups (PLAN-consolidate
D5, D6): the same on every target; milestones from the packet log and the client's log only.
Screenshot names are parameters (a session keeps the names its files always had)."""
import time

from .. import popups as _popups, screens, ui370
from ..milestones import Failed
from ..targets import Abort

# The screens title() and login_to_home() take (RMSE limits against the emulator's; None: shown,
# not gated). Home: the still parts at the still limit, the character masked.
HOME = (0.08, (screens.HOME_CHARACTER,))
SCREENS = {
    "01-title": 0.08,
    "02a-notice": None,
    "02b-login-bonus": 0.08,
    "02-home": HOME,
}


def title(s, shot="01-title", retry=True):
    """Boot -> the title's NoLoginStart answered (a communication-error dialog's リトライ, where TAP
    TO START is, when the first request was lost; retry=False: FAIL instead) -> the title shot."""
    if not s.poll(150, lambda: s.in_packets(r"< NoLoginStartRes")):
        if not retry:
            s.fail("NoLoginStart -> NoLoginStartRes (no retry: not sent by itself)")
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
    if shot:
        s.shot(shot)


def download(s, first_tap=ui370.DATA_DECIDE, dialog_shot=None, done_shot=None):
    """The full game-data download after a Login on an empty phone (about 3 GB, 1,032 GETs: the
    episode data is missing (決定), the manifests, the download dialog (ダウンロード), the bundles
    until no GET for 30 s). The caller taps 完了 (ui370.DATA_DONE) until its next milestone."""
    bulk = lambda: s.in_client(r"manifest/etc2/hi/version_latest_Bulk\.bin|version_latest_Bulk")
    if first_tap:
        s.tap_until("manifests (version_latest_Bulk.bin)", 120, first_tap, bulk, every=8)
        s.ctl("wait:5000")
    else:
        s.wait_for("manifests (version_latest_Bulk.bin)", 60, bulk)
        s.ctl("wait:8000")
    if dialog_shot:
        s.shot(dialog_shot, settle=False)
    s.tap_until("game data download started (B/...)", 120, ui370.DATA_DOWNLOAD, lambda: s.in_client(r"I/http: GET .*/Android/B/"),
                every=10)
    gets = {"n": -1, "since": time.monotonic()}

    def stopped():  # no new GET for 30 s
        n = s.count(s.client_log, r"I/http: GET")
        if n != gets["n"]:
            gets["n"], gets["since"] = n, time.monotonic()
            return False
        return time.monotonic() - gets["since"] >= 30

    s.wait_for("game data download finished", 1200, stopped)
    if done_shot:
        s.shot(done_shot, settle=False)


def data_check(s, until, name, dialog_shot=None, done_shot=None, first_tap=ui370.DATA_DECIDE):
    """After Login. A phone with the data (the shared phone, linked): the client only checks its
    manifests and goes on to `until`; when it lacks something (e.g. the master the server edited
    for the run's clock) its dialogs' buttons (決定, ダウンロード, 完了) are tapped in turn until
    `until`. An empty phone (SOA_PHONE=none): the full download (download(); first_tap: the
    first dialog's button, None for a new player's, who has none), then 完了 until `until`."""
    if not s.predownloaded:
        s.note("an empty phone: the client downloads its data")
        download(s, first_tap, dialog_shot, done_shot)
        s.tap_until(name, 120, ui370.DATA_DONE, until, every=8)
        return
    # The dialog comes (or the client goes on) a few seconds after the manifests: wait for those
    # (the last, version_latest_Individual.bin), then 12 s, not a blind 90 s (the master the server
    # edits for the run's clock is on no phone: every run of every flow shows the dialog).
    manifests = lambda: s.in_client(r"I/http: GET \S*/version_latest_Individual\.bin")
    if s.poll(90, lambda: until() or manifests()) and s.poll(12, until):
        s.ok(name)
        return
    s.note("a data dialog: tapping 決定 / ダウンロード / 完了 in turn")
    if dialog_shot:
        s.shot(dialog_shot, settle=False)
    end, i = time.monotonic() + 600, 0
    while not s.poll(6, until):
        if not s.alive() or time.monotonic() > end:
            s.miss(name + " (after the data dialogs)")
            raise Abort(name)
        s.ctl("tap:" + (ui370.DATA_DECIDE, ui370.DATA_DOWNLOAD, ui370.DATA_DONE)[i % 3])
        i += 1
    s.ok(name + " (after a download)")


def popups(s, notice, bonus, home="-", bonus_wait=None):
    """The notice board (閉じる until its web view closes) and the LOGIN BONUS popup
    (soadrive/popups.py login_popups), with a screenshot of each (None: not kept). Returns the
    summary line ('ok popups closed (notice yes, login bonus x1)')."""
    sh = lambda n: s.layout.shot_path(n) if n and n != "-" else "-"
    try:
        line = _popups.login_popups(s.fifo, s.client_log, sh(notice), sh(bonus), sh(home), bonus_wait=bonus_wait,
                                    alive=s.alive)
    except Failed as e:
        s.miss("login popups (FAIL: %s)" % e)
        raise Abort("login popups")
    s.ok("login " + line[3:])  # login popups closed (notice yes, login bonus x1)
    return line


def tap_to_start(s):
    s.tap_until("TAP TO START -> Login", 120, ui370.TITLE, lambda: s.in_packets(r"> Login "))


def login_to_home(s, notice="02a-notice", bonus="02b-login-bonus", home="02-home", dialog_shot=None, done_shot=None,
                  bonus_wait=None):
    """TAP TO START -> Login -> LoginResult -> the data check -> the notice board -> the popups ->
    the home shot. Returns the popups' summary line."""
    tap_to_start(s)
    s.wait_for("Login -> LoginResult", 60, lambda: s.in_packets(r"< LoginResult"))
    data_check(s, lambda: s.in_client(r"ShowWebView\(http"), "home (the notice board)", dialog_shot, done_shot)
    line = popups(s, notice, bonus, bonus_wait=bonus_wait)
    s.ctl("wait:3000")
    if home:
        s.shot(home)
    return line


# the port's own milestone: a CPhase change (port_debug, a port native: soa only)
def phase(n):
    return r"port_debug: phase %d " % n
