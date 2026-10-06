"""The 3.7.0 login's popups and the new player's name dialog, the same on every program (soa,
soa-emu, soa --server): what control/flowctl.py's login-popups and name-entry do. Raise
milestones.Failed when a popup doesn't close."""
import os
import re
import shutil
import subprocess
import sys
import time

from . import fifo, ui370
from .milestones import Failed, LogCursor


def _note(s):
    print(s, file=sys.stderr, flush=True)


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

# The favor login bonus popup (CFavorCharacterLoginBonus, フレンドリープレゼント, CPopupManager case 6:
# after the LOGIN BONUS): its 閉じる button at 364:928, as a 12x4 RGB signature of the 300x80 crop
# around it (on the home that spot is the home character, where a tap sends UpdateFavorByTap).
FAVOR_BONUS_CLOSE = bytes.fromhex(
    "183755183755183655193756153453113051123051153453193756183755183755193755031741031741061943000d3940516f6d7d9340547125"
    "385b00113c051942031741031741102d6f102d6f112e700b296d2a46814661943c588e24407d0d296d112e71102d70102d701c3b5d1b3b5d1b3a"
    "5d1d3b5d1636591131561432571936591d3b5c1c3a5b1c395a1c3a5a")


def _signature_match(shot, crop, size, ref, limit=0.06):
    r = subprocess.run(["convert", shot, "-resize", "729x1296!", "-crop", crop, "+repage", "-resize", size + "!",
                        "-depth", "8", "rgb:-"], capture_output=True)
    f = r.stdout
    if len(f) != len(ref):
        return False
    return sum(abs(a - b) for a, b in zip(f, ref)) / len(f) / 255 < limit


# The gacha result screen's title band (ガチャリザルト, the 600x60+65+250 crop scaled to 12x2 RGB): the
# same on both of its pages (the characters, the chips) and on every target, 2026-10-03.
GACHA_RESULT_TITLE = bytes.fromhex(
    "1a4d801f70c41f6fc11a6dc3417ab54e7dae537fad3876b81b6dc31f6fc11f70c51a4e82152836153044153044163044152f43142f43142f43"
    "153044163044153044153145152837")


# The 10-draw confirmation (10回ガチャで召喚しますか?): its 閉じる / 決定 row, the 520x70+100+760 crop scaled
# to 12x2 RGB, from six passing sessions (emu, port, Windows; 2026-10): they differ from the mean by
# 0.001; the gacha screen, its banner detail and a character detail by 0.15+.
GACHA_CONFIRM_BUTTONS = bytes.fromhex(
    "18304a1d3655344d671b3351112e50172733161a1b244b6c215b8d3c6487275b8820598b1130691b346e4a63901f39720d2b6217232b"
    "1920252f72b82879cf5689c2337dcb2772bf")

# A gacha banner's detail with its 1回ガチャ / 10連ガチャ buttons undimmed: the 10連ガチャ button, the
# 330x70+380+910 crop scaled to 8x2 RGB (ten detail screenshots within 0.055 of it, whichever carousel
# page shows; the confirmation (dimmed) and a character detail 0.24+).
GACHA_DETAIL_10 = bytes.fromhex(
    "99bbdab87b9aa9718f7897ac85b3bd83a5b37aa2b36e9ebca3a7c67191b15291b32a80ac4a8c9f44859d2b759b307fa7")


def is_gacha_confirm(shot):
    return _signature_match(shot, "520x70+100+760", "12x2", GACHA_CONFIRM_BUTTONS)


def is_gacha_detail(shot):
    return _signature_match(shot, "330x70+380+910", "8x2", GACHA_DETAIL_10, limit=0.1)


def is_gacha_result(shot):
    return _signature_match(shot, "600x60+65+250", "12x2", GACHA_RESULT_TITLE)


def is_login_bonus(shot):
    return _signature_match(shot, "560x170+85+120", "12x12", LOGIN_BONUS_TITLE)


def is_favor_bonus(shot):
    return _signature_match(shot, "300x80+215+890", "12x4", FAVOR_BONUS_CLOSE)


def login_popups(fifo_path, log, notice_shot, bonus_shot, home_shot, notice_wait=None, bonus_wait=None, alive=None):
    """After the 3.7.0 login reaches home: close the notice board (閉じる at 364:1133, retried until
    the client logs its web view closing), then the LOGIN BONUS popup (閉じる at 364:1063, tapped
    while a screenshot shows the popup's title: it can have a second page, and it can appear late),
    then the favor login bonus popup (閉じる at 364:928, tapped while a screenshot shows its button;
    waited for when the log has the in-process server's "favor login bonus" line), with a
    screenshot of each and of the home after them. A shot path of '-' isn't kept. Returns the
    summary line ('ok popups closed (...)'); raises Failed when a popup doesn't close."""
    def send(*cmds):
        # a client that died (alive(): its process, its log) ends the popups at once
        if alive is not None and not alive():
            raise Failed("the client is gone")
        return fifo.send(fifo_path, list(cmds), timeout=400, alive=alive)

    lg = LogCursor(log)
    scratch = os.path.join(os.path.dirname(os.path.abspath(log)), ".flowctl-popup.png")
    keep = lambda p: p if p != "-" else scratch
    if notice_wait is None:
        notice_wait = float(os.environ.get("FLOW_NOTICE_WAIT", "120"))
    if bonus_wait is None:
        bonus_wait = float(os.environ.get("FLOW_BONUS_WAIT", "40"))
    # 1. the notice board: the client opens its web view (ShowWebView(http...)), 閉じる closes it
    # (SetRootURI("") + ShowWebView()).
    opened = lg.wait(re.compile(r"ShowWebView\(http"), notice_wait, alive=alive)
    if opened is None:
        _note("note: no notice board opened")
    else:
        # closed: the runtime's "ShowWebView() not supported" (the text-label fallback, soa-emu) or the
        # port's web view ("webview: closed")
        closed = re.compile(r"ShowWebView\(\) not supported|I/webview: closed")
        cmds = ["wait:8000", "shot:" + keep(notice_shot), "tap:" + ui370.NOTICE_CLOSE]
        for n in range(10):
            send(*cmds)
            if lg.wait(closed, 8, alive=alive) is not None:
                break
            _note("retry %d: the notice board is still open" % (n + 2))
            cmds = ["tap:" + ui370.NOTICE_CLOSE]
        else:
            raise Failed("the notice board didn't close")
    # 2. the LOGIN BONUS popup (after the notice board; each page's 閉じる at 364:1063, which on
    # the home is the gap between the ミッション and スフィア211 buttons).
    deadline = time.monotonic() + bonus_wait
    seen, taps, cmds = False, 0, ["wait:4000", "shot:" + keep(home_shot)]
    while True:
        send(*cmds)
        if is_login_bonus(keep(home_shot)):
            if not seen and bonus_shot != "-":
                shutil.copyfile(keep(home_shot), bonus_shot)
            seen, taps = True, taps + 1
            if taps > 8:
                raise Failed("the LOGIN BONUS popup didn't close")
            cmds = ["tap:" + ui370.LOGIN_BONUS_CLOSE, "wait:3000", "shot:" + keep(home_shot)]
        elif seen:
            break
        elif time.monotonic() > deadline:
            _note("note: no LOGIN BONUS popup")
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
        send(*cmds)
        if is_favor_bonus(keep(home_shot)):
            favor += 1
            if favor > 6:
                raise Failed("the favor login bonus popup didn't close")
            cmds = ["tap:" + ui370.FAVOR_BONUS_CLOSE, "wait:3000", "shot:" + keep(home_shot)]
        elif favor or time.monotonic() > deadline:
            break
        else:
            cmds = ["wait:2000", "shot:" + keep(home_shot)]
    if os.path.exists(scratch):
        os.remove(scratch)
    return ("ok popups closed (notice %s, login bonus %s%s)" %
            ("yes" if opened else "no", "x%d" % taps if seen else "no", ", favor bonus x%d" % favor if favor else ""))


def name_entry(fifo_path, log, name, typed_shot, alive=None):
    """The new-player name dialog (after the terms' 同意する): tap the name field until the client
    opens its keyboard (StartKeyboardActivity; a tap during the dialog's fade-in is dropped), only
    then type NAME (text:, which a keyboard opened later would clear), screenshot, then 決定 until
    the client sends CreatePlayer (the in-process server's 'request CreatePlayer' line). Returns
    'ok CreatePlayer "NAME"'; raises Failed unless CreatePlayer carries NAME."""
    def send(*cmds):
        # a client that died (alive(): its process, its log) ends the popups at once
        if alive is not None and not alive():
            raise Failed("the client is gone")
        return fifo.send(fifo_path, list(cmds), timeout=400, alive=alive)

    lg = LogCursor(log)
    kb = re.compile(r"StartKeyboardActivity\(")
    for n in range(12):
        send("wait:1500", "tap:" + ui370.NAME_FIELD)
        if lg.wait(kb, 4, alive=alive) is not None:
            break
        _note("retry %d: no keyboard yet" % (n + 2))
        if n % 3 == 2:  # the terms' 同意する may have been dropped: tap it again
            send("tap:" + ui370.TERMS_AGREE, "wait:2500")
    else:
        raise Failed("the name field never opened the keyboard (StartKeyboardActivity)")
    # The game renders no frames while its keyboard is open (the host repaints the last one with its
    # text box, so a shot: then shows the box); text: finishes the entry at once.
    send("wait:500", "text:" + name, "wait:1500", "shot:" + typed_shot)
    cp = re.compile(r"request CreatePlayer \(fid [0-9a-f]+\): (.*)$")
    line = None
    for n in range(5):
        send("tap:" + ui370.NAME_DECIDE)
        line = lg.wait(cp, 10, alive=alive)
        if line is not None:
            break
        _note("retry %d: no CreatePlayer yet" % (n + 2))
    if line is None:
        raise Failed("決定 never sent CreatePlayer")
    sent = cp.search(line).group(1).strip()
    if sent != '"%s"' % name:
        raise Failed('CreatePlayer sent the name %s, not "%s"' % (sent, name))
    return 'ok CreatePlayer "%s"' % name
