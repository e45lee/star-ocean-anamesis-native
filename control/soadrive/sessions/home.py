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

from .. import screens
from ..flows import mission
from ..targets import Abort
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "its destinations are checked by the port's phase lines"
WRAPPER = "port/scripts/home_session.sh"
P = mission.phase


def options(ap):
    common.port_options(ap)


def main(o):
    s = common.port_run(o, common.port_config(o))
    c = s.ctl

    def check(name, rx, secs=60):
        s.wait_log(rx, secs, name=name, fatal=False)

    def checkt(name, rx, secs, every, tries, *cmds):
        s.tap_log(rx, secs, every, tries, *cmds, name=name, fatal=False)

    def home(name):
        checkt(name + " -> home", P(4), 30, 15, 2, "tap:60:1250")
        c("wait:5000")

    def body(s):
        try:
            common.port_login(s, "01-title", "02-notice", "03-login-bonus", "04-home")
        except Abort as e:
            if "login popups" not in str(e) or not s.alive():
                raise  # (popups that didn't close are counted; the rest goes on)
        # ---- main buttons ----
        checkt("event", P(5), 60, 20, 3, "tap:95:1085")
        c("wait:6000", s.shot_cmd("10-event"))
        home("event")
        try:
            common.episode_list(s)
        except Abort:
            if not s.alive():
                raise
        c("wait:5000", s.shot_cmd("11-mission"))
        home("mission")
        checkt("sphere211", r"request GetSphere211Info", 60, 20, 3, "tap:455:1085")
        c("wait:6000", s.shot_cmd("12-sphere211"))
        home("sphere211")
        checkt("deepspace", P(6), 60, 20, 3, "tap:635:1085")
        c("wait:8000", s.shot_cmd("13-deepspace"))
        home("deepspace")
        # ---- side buttons ----
        c("tap:668:200", "wait:2000", s.shot_cmd("20-menu"), "tap:445:200")
        check("follow", r"request Blacklist")
        c("wait:4000", s.shot_cmd("21-follow"), "tap:364:537", "wait:3000", "tap:327:610", "wait:1500", "text:1234567890", "wait:1000",
          "tap:532:610")
        check("follow-search", r"SearchPlayer refused")
        c("wait:4000", s.shot_cmd("22-follow-search"), "tap:364:710", "wait:2000", "tap:364:738", "wait:4000", s.shot_cmd("23-recent"))
        c("tap:100:1120", "wait:3000", "tap:100:1120")
        check("follow-back", P(4), 30)
        # 称号: the title list; a tap on the second one sets it (SetTitle), 外す takes it off (SetTitle 0).
        c("wait:5000", "tap:668:200", "wait:2000", "tap:555:200", "wait:4000", s.shot_cmd("24-titles"), "tap:590:303", "wait:2000",
          s.shot_cmd("24a-titles-other"))
        checkt("set-title", r"I/server: SetTitle [1-9]", 30, 10, 2, "tap:364:600")
        c("wait:3000", s.shot_cmd("24b-title-set"), "tap:364:800", "wait:2000")
        checkt("remove-title", r"I/server: SetTitle 0$", 30, 10, 2, "tap:515:1053")
        c("wait:3000", s.shot_cmd("24c-title-removed"), "tap:364:800", "wait:2000", "tap:213:1053", "wait:2000")
        # お知らせ: the notice board from the menu shows the local server's page (the web view draws
        # it, or the popup shows it as text when it can't).
        checkt("notice", r"webview: (local page shown|page http)", 40, 12, 3, "tap:668:200", "wait:2000", "tap:335:200")
        c("wait:4000", s.shot_cmd("24d-notice"), "tap:364:1133", "wait:3000")
        c("tap:668:315")
        check("present", r"request PresentList")
        c("wait:4000", s.shot_cmd("25-present"), "tap:100:1120")
        check("present-back", P(4), 30)
        c("wait:5000", "tap:668:425")
        check("achievements", r"request AchievementActiveList")
        c("wait:4000", s.shot_cmd("26-achievements"), "tap:213:1050", "wait:2000")
        c("tap:668:535")
        check("recommended", P(28))
        c("wait:4000", s.shot_cmd("27-recommended"), "tap:100:1120")
        check("recommended-back", P(4), 30)
        c("wait:5000", "tap:668:645", "wait:3000", s.shot_cmd("28-datasave"), "tap:364:800", "wait:2000")
        c("tap:303:70", "wait:3000", s.shot_cmd("29-stamina"), "tap:364:800", "wait:2000")
        # ---- footer ----
        for name, rx, xy, ms, shot in (("character", P(11), "180:1250", 6000, "30-character"), ("item", P(9), "300:1250", 5000, "31-item"),
                                       ("gacha", r"request GetGachaInData", "425:1250", 8000, "32-gacha"),
                                       ("shop", P(10), "545:1250", 5000, "33-shop")):
            checkt(name, rx, 60, 20, 3, "tap:" + xy)
            c("wait:%d" % ms, s.shot_cmd(shot))
            home(name)
        checkt("other", P(12), 60, 20, 3, "tap:665:1250")
        c("wait:5000", s.shot_cmd("34-other"), "drag:364:900:364:500", "wait:2000", s.shot_cmd("35-other-2"), "drag:364:900:364:500",
          "wait:2000", s.shot_cmd("36-other-3"))
        home("other")
        c("wait:3000", s.shot_cmd("40-home"))

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
