"""Session `home`: the restored 3.7.0 home (the in-process local server; restore370 groups home,
common, othermenu): boot -> notice board -> LOGIN BONUS -> the home, then every home button, each
checked by the phase it switches to or the server request it sends (log lines), with a screenshot
per screen:
  main buttons   イベント (phase 5, the event list), ミッション (phase 8, episode list), スフィア211
                 (GetSphere211Info), ディープスペース探査 (phase 6, CPhase_DeepSpace);
  side buttons   ≡ menu -> お知らせ (the local notice page), フォロー (phase 13, FollowList / Blacklist;
                 player search -> error 10002), 称号 (the list, SetTitle, 外す); プレゼント (phase 14,
                 PresentList); 実績 (AchievementActiveList); オススメ! (phase 28); 情報保存; the stamina "+";
  footer         キャラクター (11), アイテム (9), ガチャ (17, GetGachaInData), ショップ (10), その他 (12,
                 the 3.7.0 other menu), ホーム (4).
When HOME_REF names a directory of reference screenshots (same file names), each shot is compared
with ImageMagick (RMSE on a small copy) and reported. A contact sheet goes to OUT/strip.png.
Exit status 1 if a destination isn't reached ("PASS: every home destination reached" /
"FAIL: N destinations missed").

Usage: port/scripts/home_session.sh <soa> <out-dir> <scratch-dir> [soa flags...]   (from any directory;
e.g. `--lang en` for the English home, PLAN-english E11: session:home-en)
Env: HOME_REF, SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc (the phase lines)."""
import glob
import os
import subprocess

from .. import popups, screens
from ..targets import Abort
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "its destinations are checked by the port's phase lines"
WRAPPER = "port/scripts/home_session.sh"


def options(ap):
    common.port_options(ap)


def main(o):
    s = common.port_run(o, common.port_config(o))

    H, G = common.HOME_MASK, common.GACHA_MASK

    def phase(name, xy, n, shot=None, mask=(), **kw):
        common.tap_to_phase(s, name, xy, n, shot, mask=mask, **kw)

    def req(name, xy, rx, shot=None, mask=(), **kw):
        common.tap_to_log(s, name, xy, rx, shot, mask=mask, **kw)

    def screen(name, xy, shot=None, mask=H, **kw):
        common.tap_to_screen(s, name, xy, shot, mask=mask, fatal=False, **kw)

    def menu():
        """≡: the menu open (after 称号 it is open already: a tap would close it)."""
        shot = common.look(s)
        if shot and popups.is_home_menu_open(shot):
            return
        screen("≡ menu", "668:200", is_screen=popups.is_home_menu_open)

    def home(name):
        phase(name + " -> home", "60:1250", 4, mask=H, secs=30, every=15, tries=2)

    def body(s):
        try:
            common.port_login(s, "01-title", "02-notice", "03-login-bonus", "04-home")
        except Abort as e:
            if "login popups" not in str(e) or not s.alive():
                raise  # (popups that didn't close are counted; the rest goes on)
        common.settle(s, mask=H)
        # ---- main buttons ----
        phase("event", "95:1085", 5, "10-event")
        home("event")
        try:
            common.episode_list(s)
        except Abort:
            if not s.alive():
                raise
        common.settle(s, "11-mission")
        home("mission")
        req("sphere211", "455:1085", r"request GetSphere211Info", "12-sphere211")
        home("sphere211")
        phase("deepspace", "635:1085", 6, "13-deepspace")
        home("deepspace")
        # ---- side buttons ----
        menu()
        s.keep_shot("20-menu", common.look(s))
        req("follow", "445:200", r"request Blacklist", "21-follow")
        screen("follow: プレイヤーIDで検索する", "364:537", mask=())
        # the ID field opens the keyboard (the game draws nothing under it: no still screen to wait for)
        req("follow: the ID field -> the keyboard", "327:610", r"StartKeyboardActivity\(", secs=30, every=8, wait_still=False)
        s.ctl("text:1234567890")
        req("follow-search", "532:610", r"SearchPlayer refused", "22-follow-search", secs=40, every=10)
        screen("follow: the search error (10002): 閉じる", "364:710", mask=())
        screen("follow: 最近遊んだプレイヤー", "364:738", "23-recent", mask=())
        screen("follow: 戻る", "100:1120", mask=())
        phase("follow-back", "100:1120", 4, mask=H, secs=30, every=15, tries=2)
        # 称号: the title list; a tap on the second one sets it (SetTitle), 外す takes it off (SetTitle 0).
        menu()
        screen("称号", "555:200", "24-titles", mask=())
        screen("称号: the other tab", "590:303", "24a-titles-other", mask=())
        req("set-title", "364:600", r"I/server: SetTitle [1-9]", "24b-title-set", secs=30, every=10, tries=2)
        screen("set-title: 閉じる", "364:800", mask=())
        req("remove-title", "515:1053", r"I/server: SetTitle 0$", "24c-title-removed", secs=30, every=10, tries=2)
        screen("remove-title: 閉じる", "364:800", mask=())
        screen("称号: 閉じる", "213:1053")
        # お知らせ: the notice board from the menu shows the local server's page (the web view draws
        # it, or the popup shows it as text when it can't).
        menu()
        req("notice", "335:200", r"webview: (local page shown|page http)", "24d-notice", secs=40, every=12)
        screen("notice: 閉じる", "364:1133")
        req("present", "668:315", r"request PresentList", "25-present")
        phase("present-back", "100:1120", 4, mask=H, secs=30, every=15, tries=2)
        req("achievements", "668:425", r"request AchievementActiveList", "26-achievements")
        screen("achievements: 閉じる", "213:1050")
        phase("recommended", "668:535", 28, "27-recommended")
        phase("recommended-back", "100:1120", 4, mask=H, secs=30, every=15, tries=2)
        screen("情報保存", "668:645", "28-datasave")
        screen("情報保存: 閉じる", "364:800")
        screen("stamina +", "303:70", "29-stamina")
        screen("stamina: 閉じる", "364:800")
        # ---- footer ----
        for name, rx, xy, shot, mask in (("character", 11, "180:1250", "30-character", ()), ("item", 9, "300:1250", "31-item", ()),
                                         ("gacha", r"request GetGachaInData", "425:1250", "32-gacha", G),
                                         ("shop", 10, "545:1250", "33-shop", ())):
            if isinstance(rx, int):
                phase(name, xy, rx, shot, mask)
            else:
                req(name, xy, rx, shot, mask)
            home(name)
        phase("other", "665:1250", 12, "34-other")
        # the other menu scrolled twice: a drag that finds the list at its end changes nothing, which
        # isn't this session's check (the phases are): each waits for the list to stop
        for shot in ("35-other-2", "36-other-3"):
            s.ctl("drag:364:900:364:500")
            common.settle(s, shot)
        home("other")
        common.settle(s, "40-home", mask=H)

    common.drive(s, body)
    shots = sorted(glob.glob(os.path.join(s.shots, "*.png")))
    if shots:
        subprocess.run(["montage"] + shots + ["-tile", "8x", "-geometry", "182x324+2+2", os.path.join(o.out, "strip.png")],
                       capture_output=True)
    ref = os.environ.get("HOME_REF")
    if ref:
        for f in shots:
            r = os.path.join(ref, os.path.basename(f))
            if os.path.isfile(r):
                print("ref  %s rmse=%.4g" % (os.path.basename(f), screens.rmse(f, r)))
    n = sum(1 for r in s.results if r.startswith("FAIL"))
    if n:
        print("FAIL: %d destinations missed" % n)
        return 1
    print("PASS: every home destination reached")
    return 0
