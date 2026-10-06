"""Session `summer-demo`: the unmodified 3.7.0 client in the emulator (soa-emu) against soa-server
with the summer events enabled, from boot to a summer event battle and a summer gacha 10-draw,
with numbered screenshots and a contact sheet (emulator/README.md "Summer demonstration").

Usage: emulator/scripts/summer_demo.sh [options] [OUT]
  OUT               where the screenshots, logs and state dumps go (default
                    work/test/summer-demonstration); its old *.png, *.log and state-*.txt are
                    deleted first, other files (README.md) are kept
  --watch           show the emulator's window (default: headless)
  --clock C         the date both the server and the phone start at, "YYYY-MM-DD HH:MM:SS"
                    (default "2026-10-01 12:00:00": a fixed calendar, so the event list's rows and
                    the seeded draws are the same every run); "host" runs on the real date
  --emu FILE        soa-emu (default build/emulator/soa-emu)
  --server FILE     soa-server (default build/server/soa-server)
Env:
  SOA_PHONE         the phone's game data (scripts/shared-phone.sh): unset -> linked from the shared
                    pre-downloaded phone; "none" -> an empty phone: the client downloads its 3 GB
                    (three more screenshots: download-prompt, download-dialog, download-done)
  EMU_DATA=DIR      run on DIR as the phone itself; never deleted
  KEEP_SCRATCH=1    keep the scratch dir (the phone, the server state, the packet bodies)

What it does: soa-server with a fresh state seeded from data/saves/seed/Game.xml (LOCAL00001), the
CDN from work/download-3.7.0, --enable-events, --seed-rng 1, --log-packets; soa-emu pointed at it:
  1. launch: boot, title (NoLoginStart), TAP TO START (StartBridge, Login), the data, the notice
     board and LOGIN BONUS, home;
  2. summer event: イベント (CheckEventRankingResult) -> the 水着イベント2020 board (星の海と夢の渚,
     event_sww2020_93; found by its beach) -> its first story mc99_565 (skipped: EndMissionTalk),
     which unlocks the battle me99_1054 -> single play, no rental, party 1 -> MissionStart -> the
     battle -> MissionEnd -> the result pages -> back on the board; then home;
  3. summer gacha: ガチャ (GetGachaInData) -> the first banner, 復刻水着2020① (checked against the
     master's gacha name) -> 10連ガチャ -> 決定 (Gacha) -> the summon, the results, home.
Then the server's state before / after: the story and battle cleared, the event coins dropped, the
stamina spent, 2,500 coins debited, ten draws recorded; and a contact sheet of all screenshots
(tools/contact_sheet.py, OUT/summer-demonstration-grid.png). Prints PASS / FAIL per milestone and a
final PASS (exit 0) or FAIL (exit 1); OUT/milestones.txt. Kills only the processes it started.
Targets: emu (default), port-server, port-inproc."""
import os
import re
import shutil
import sqlite3
import subprocess
import sys
import tempfile
import time

from .. import popups as _popups, proc, screens, ui370
from ..flows import event, launch
from ..flows import gacha as gacha_flow
from ..milestones import Failed
from ..proc import REPO
from ..targets import Config, Layout, Run
from . import common

TARGETS = ("emu", "port-server", "port-inproc")
WRAPPER = "emulator/scripts/summer_demo.sh"
SECTIONS = (("launch", "1. Launch: boot, title, login, popups, home"),
            ("event", "2. Summer event: 水着イベント2020 (event_sww2020_93), story mc99_565 + battle me99_1054"),
            ("gacha", "3. Summer gacha: 復刻水着2020① 10-draw"))


def options(ap):
    ap.add_argument("out", nargs="?", default=os.path.join(REPO, "work/test/summer-demonstration"))
    ap.add_argument("--watch", action="store_true", help="show the window")
    ap.add_argument("--clock", default="2026-10-01 12:00:00", help='"YYYY-MM-DD HH:MM:SS", or host')
    ap.add_argument("--emu", default=os.path.join(REPO, "build/emulator/soa-emu"))
    ap.add_argument("--server", default=os.path.join(REPO, "build/server/soa-server"))


class Shots:
    """OUT/NN-name.png, numbered in order, per section (the contact sheet's rows); a flat frame (a
    black or white transition) is taken again, up to 5 times, 1.5 s apart."""

    def __init__(self, s):
        self.s, self.n, self.section, self.by = s, 0, "launch", {k: [] for k, _ in SECTIONS}

    def name(self, what):
        self.n += 1
        return "%02d-%s" % (self.n, what)

    def add(self, path):
        if os.path.exists(path) and os.path.getsize(path) > 0:
            self.by[self.section].append(path)

    def shot(self, what):
        nm = self.name(what)
        path = self.s.layout.shot_path(nm)
        for _ in range(5):
            self.s.send(["shot:" + path])
            if os.path.exists(path) and os.path.getsize(path) > 0 and not screens.flat(path):
                break
            time.sleep(1.5)
        if not os.path.exists(path):
            self.s.miss("screenshot %s not taken" % what)
            return
        self.add(path)

    def keep(self, what, src):
        path = self.s.layout.shot_path(self.name(what))
        if os.path.exists(src):
            shutil.copyfile(src, path)
            self.add(path)
        else:
            self.s.miss("screenshot %s not kept" % what)


def sheet(s, shots, scratch):
    if not shots.by["launch"]:
        return
    py = os.path.join(REPO, ".venv/bin/python")
    if not os.path.exists(py):
        py = sys.executable
    args = []
    for k, title in SECTIONS:
        if shots.by[k]:
            args += ["@" + title] + shots.by[k]
    r = subprocess.run([py, os.path.join(REPO, "tools/contact_sheet.py"), "--cols", "6", "--tile", "360", "--title",
                        "Summer demo: 3.7.0 client in %s + soa-server --enable-events, %s" % (
                            "soa-emu" if s.target == "emu" else "soa", time.strftime("%F"))] + args +
                       ["-o", os.path.join(s.layout.shots, "summer-demonstration-grid.png")], capture_output=True, text=True)
    out = (r.stdout + r.stderr).strip().splitlines()
    s.check("contact sheet (%s)" % (out[-1] if out else ""), r.returncode == 0)


def gacha_name(gid):
    db = proc.repo_file("data/basmaster-3.7.0.sqlite3")
    r = sqlite3.connect("file:%s?mode=ro" % db, uri=True).execute(
        "select (select text_value from master_text t where t.message_id = g.name_message_id limit 1) from master_gacha g where id = ?",
        (gid,)).fetchone()
    return r[0] if r and r[0] else ""


def body(s, sh, scratch):
    # ---- 1. launch ----
    s.ctl("wait:4000")
    sh.shot("boot")
    launch.title(s, None, retry=False)
    sh.shot("title")
    if s.target == "port-inproc":
        launch.tap_to_start(s)
    else:
        s.tap_until("TAP TO START -> StartBridge -> ResultStart", 120, ui370.TITLE, lambda: s.in_packets(r"< ResultStart"), every=5)
    s.wait_for("Login -> LoginResult", 60, lambda: s.in_packets(r"< LoginResult"))
    if s.target != "port-inproc":
        s.wait_for("Login's GetPlayerRes (seeded player)", 30, lambda: s.in_packets(r"< GetPlayerRes .*ends the login request"))
    home = lambda: s.in_client(r"ShowWebView\(http")
    if s.predownloaded:
        s.note("the game data is on the phone (SOA_PHONE / EMU_DATA); no full download")
        launch.data_check(s, home, "home (notice board)")
    else:
        s.ctl("wait:8000")
        sh.shot("download-prompt")
        dl = [sh.name("download-dialog"), sh.name("download-done")]
        launch.download(s, ui370.DATA_DECIDE, *dl)
        for nm in dl:
            sh.add(s.layout.shot_path(nm))
        s.tap_until("完了 -> home (notice board)", 120, ui370.DATA_DONE, home)
    names = [sh.name(x) for x in ("notice-board", "login-bonus", "home")]
    paths = [s.layout.shot_path(x) for x in names]
    try:
        line = _popups.login_popups(s.fifo, s.client_log, *paths, alive=s.alive)
    except Failed as e:
        s.fail("login popups (FAIL: %s)" % e)
    s.ok("login " + line[3:])
    for p in paths:
        sh.add(p)
    if not os.path.exists(paths[1]):
        s.note("no LOGIN BONUS popup this time")
    s.state("1-home")

    # ---- 2. the summer event ----
    sh.section = "event"
    n = s.n_packets(r"> CheckEventRankingResult")
    s.tap_until("イベント -> the event menu (CheckEventRankingResult)", 60, ui370.HOME_EVENT, s.more_than(r"> CheckEventRankingResult", n),
                every=5)
    s.ctl("wait:6000")
    sh.shot("event-list")
    # Each row in turn until one opens the beach board whose first story (232:840) opens a story
    # popup (the list is never scrolled: a fling leaves it somewhere else).
    story, battle = event.mid("master_event_mission", "mc99_565"), event.mid("master_event_mission", "me99_1054")
    board, pop = os.path.join(scratch, "board.png"), os.path.join(scratch, "story.png")
    found = None
    for y in (525, 680, 830, 985):
        s.send(["tap:364:%d" % y, "wait:7000", "shot:" + board])
        if event.beach(board):
            s.send(["tap:232:840", "wait:3000", "shot:" + pop])
            if event.story_popup(pop):
                found = y
                break
            s.note("the row at y=%d opens a beach board without the story at 232:840; 戻る" % y)
        else:
            s.note("the row at y=%d is not a beach board; 戻る" % y)
        s.ctl("tap:" + ui370.BACK, "wait:5000")
    if found is None:
        s.fail("no row opened the 水着イベント2020 board")
    s.ok("the summer event board (水着イベント2020, 星の海と夢の渚; row at y=%d)" % found)
    sh.keep("summer-event-board", board)
    sh.keep("story-detail", pop)
    s.tap_until("story 星海に現れし渚 (mc99_565) -> MissionTalk", 60, ui370.STORY_START, lambda: s.in_packets(r"> MissionTalk .* %d " % story),
                every=5)
    s.ctl("wait:10000")
    sh.shot("story-scene")
    s.ctl("tap:" + ui370.STORY_SKIP, "wait:2000")
    sh.shot("story-skip")
    n = s.n_packets(r"> CheckEventRankingResult")
    s.tap_until("story skipped (はい) -> EndMissionTalk", 60, ui370.STORY_SKIP_YES, lambda: s.in_packets(r"> EndMissionTalk .* %d 1" % story),
                every=5)
    s.wait_for("back on the board (CheckEventRankingResult)", 60, s.more_than(r"> CheckEventRankingResult", n))
    s.ctl("wait:6000")
    sh.shot("board-story-cleared")
    # The battle it unlocked, me99_1054 (New, right of the cleared story).
    s.ctl("tap:685:655", "wait:4000")
    sh.shot("mission-detail")
    s.ctl("tap:" + ui370.SINGLE_PLAY, "wait:5000")
    sh.shot("rental")
    s.ctl("tap:" + ui370.RENTAL_NONE, "wait:5000")
    sh.shot("party")
    s.ctl("tap:" + ui370.PARTY_START, "wait:3000")
    sh.shot("start-confirm")
    s.tap_until("ビーチスポーツ？【初級】 (me99_1054) -> MissionStart -> MissionStartRes", 60, ui370.CONFIRM_OK,
                lambda: s.in_packets(r"< MissionStartRes"), every=5)
    s.check("MissionStart names me99_1054 (%d)" % battle, s.in_packets(r"> MissionStart .* %d " % battle))
    s.ctl("wait:6000")
    sh.shot("battle-loading")
    for i in range(1, 5):
        if s.poll(8, lambda: s.in_packets(r"< MissionEndRes")):
            break
        sh.shot("battle-%d" % i)
    s.wait_for("the battle won: MissionEnd (battle log) -> MissionEndRes", 600, lambda: s.in_packets(r"< MissionEndRes"))
    for rx, what in ((r"MissionEnd mission %d: .*first clear" % battle, "no first clear of me99_1054"),
                     (r"MissionEnd mission %d: unlocked" % battle, "nothing unlocked")):
        ln = s.last_line(rx, s.server_log)
        if ln:
            s.ok("server: " + re.sub(r"^I/server: ", "", ln))
        else:
            s.miss("server: " + what)
    s.ctl("wait:2000")
    sh.shot("battle-won")
    s.ctl("wait:5000")
    sh.shot("victory")
    for p in ("rewards", "drops", "exp"):
        s.ctl("tap:" + ui370.RESULT_OK, "wait:4000")
        sh.shot("result-" + p)
    n = s.n_packets(r"> CheckEventRankingResult")
    s.tap_until("results -> back on the board (CheckEventRankingResult)", 90, ui370.RESULT_OK, s.more_than(r"> CheckEventRankingResult", n),
                every=5)
    s.ctl("wait:6000")
    sh.shot("board-after-clear")
    s.state("2-after-battle")
    s.ctl("tap:" + ui370.FOOTER_HOME, "wait:8000")
    sh.shot("home-after-event")

    # ---- 3. the summer gacha ----
    sh.section = "gacha"
    s.tap_until("ガチャ -> GetGachaInData", 60, ui370.FOOTER_GACHA, lambda: s.in_packets(r"< GetGachaInDataRes"), every=5)
    s.ctl("wait:8000")
    sh.shot("gacha-menu")
    s.ctl("tap:" + ui370.GACHA_FIRST_BANNER, "wait:5000")  # the first banner of おすすめガチャ: 復刻水着2020①
    sh.shot("summer-banner")
    s.ctl("tap:" + ui370.GACHA_10, "wait:2500")  # 10連ガチャ (2,500 coins)
    gacha_flow.open_confirm(s)  # a lost tap or a pick-up page's character detail: retried / closed
    sh.shot("draw-confirm")
    s.tap_until("10-draw: 決定 -> Gacha -> GachaRes", 60, ui370.GACHA_DECIDE, lambda: s.in_packets(r"< GachaRes"), every=5)
    gline = next((ln for ln in open(s.server_log, errors="replace").read().splitlines()
                  if re.match(r"^I/server: Gacha [0-9]* \(.*draws for", ln)), "")
    m = re.match(r"^I/server: Gacha ([0-9]*) ", gline)
    gname = gacha_name(int(m.group(1))) if m else ""
    s.check("a summer gacha: %s (%s)" % (gname or "?", re.sub(r"^I/server: ", "", gline)), re.search(r"水着|夏|サマー", gname))
    s.ctl("wait:4000")
    sh.shot("summon-start")
    s.ctl("tap:" + ui370.SUMMON_START, "wait:3000")
    sh.shot("summon-1")
    s.ctl("wait:3000")
    sh.shot("summon-2")
    s.ctl("wait:6000")
    sh.shot("summon-reveal")
    s.ctl("tap:" + ui370.SUMMON_REVEAL, "wait:4000")
    sh.shot("summon-card")
    s.ctl("tap:" + ui370.SUMMON_ALL_SKIP, "wait:5000")
    sh.shot("gacha-results")
    s.ctl("tap:" + ui370.GACHA_RESULT_NEXT, "wait:4000")  # 次へ
    sh.shot("gacha-results-chips")
    s.ctl("tap:" + ui370.GACHA_RESULT_NEXT, "wait:4000")  # 閉じる
    sh.shot("banner-after-draw")
    s.ctl("tap:" + ui370.FOOTER_HOME, "wait:8000")
    sh.shot("home-end")
    s.state("3-after-gacha")

    # ---- server-side evidence ----
    st = lambda tag: open(os.path.join(s.layout.state_dir, "state-%s.txt" % tag), errors="replace").read()
    st1, st2, st3 = st("1-home"), st("2-after-battle"), st("3-after-gacha")
    s.check("state: story mc99_565 (%d) cleared" % story, re.search(r"^  mission %d: cleared" % story, st2, re.M))
    s.check("state: battle me99_1054 (%d) cleared" % battle, re.search(r"^  mission %d: cleared" % battle, st2, re.M))
    s.check("state: mc99_566 unlocked by me99_1054", "unlocked mc99_566 (by me99_1054)" in st2)
    coin = lambda t: common.state_value(t, r"^  stock item_coin_291 x([0-9]+)") or 0
    s.check("state: event drops: item_coin_291 %d -> %d" % (coin(st1), coin(st2)), coin(st2) > coin(st1))
    s1, s2 = (common.state_value(t, r" stamina ([0-9]+) ") for t in (st1, st2))
    s.check("state: stamina spent (%s -> %s)" % (s1, s2), s1 is not None and s2 is not None and s2 < s1)
    c2, c3 = (common.state_value(t, r" coins free ([0-9]+) ") for t in (st2, st3))
    s.check("state: 2,500 coins debited (%s -> %s)" % (c2, c3), c2 is not None and c3 is not None and c2 - c3 == 2500)
    d = len(re.findall(r"^  gacha .*: ", st3, re.M))
    s.check("state: %d draws recorded (%d duplicates)" % (d, len(re.findall(r"^  gacha .*\(duplicate\)", st3, re.M))), d == 10)
    r2, r3 = (common.state_value(t, r"^roster: ([0-9]+) ") for t in (st2, st3))
    s.note("roster %s -> %s characters" % (r2, r3))
    if s.in_packets(r"< ProtocolError"):
        s.miss("a ProtocolError in the packet log")


def main(o):
    out = os.path.abspath(o.out)
    for b, what in ((o.emu, "soa-emu"), (o.server, "soa-server")):
        if o.target != "port-inproc" and not os.access(b, os.X_OK):
            print("FAIL: %s not built (cmake -S . -B build && cmake --build build --target %s)" % (b, what))
            return 1
    if not shutil.which("convert"):
        print("FAIL: ImageMagick's convert is needed (screen checks)")
        return 1
    os.makedirs(out, exist_ok=True)
    for f in os.listdir(out):
        if f.endswith((".png", ".log", ".log.pos")) or (f.startswith("state-") and f.endswith(".txt")) or f == "milestones.txt":
            os.remove(os.path.join(out, f))
    scratch = tempfile.mkdtemp(prefix="summer-demo.", dir=os.environ.get("TMPDIR", "/tmp"))
    phone = os.environ.get("EMU_DATA") or None
    lay = Layout("emu-session", scratch, os.path.join(scratch, "fifo"), os.path.join(scratch, "emu.log"),
                 os.path.join(scratch, "emu.log") if o.target == "port-inproc" else os.path.join(scratch, "server.log"),
                 os.path.join(scratch, "packets", "packets.log"), os.path.join(scratch, "server", "server.sqlite3"), out,
                 phone or os.path.join(scratch, "phone"), out, os.path.join(scratch, "steps.txt"), flat_shots=True)
    clock = None if o.clock == "host" else o.clock
    cfg = Config(["--enable-events"], clock, seed=os.path.join(REPO, "data/saves/seed/Game.xml"), seed_rng=1, windowed=o.watch,
                 fresh_kvs=False, phone=phone, state_master=False,
                 binary=o.emu if o.target == "emu" else None, server_binary=o.server)
    s = Run(o.target, lay, cfg, slot=o.slot)
    print("summer_demo: OUT %s; clock %s; client %s; soa-server %s" % (out, o.clock, os.path.realpath(o.emu), os.path.realpath(o.server)))
    sh = Shots(s)

    def run(s):
        if phone:
            s.predownloaded = os.path.isdir(os.path.join(phone, "data/files/download/UI"))
        if s.target != "port-inproc" and not s.in_server(r"enable-events"):
            s.fail("soa-server didn't enable the summer events")
        body(s, sh, scratch)

    try:
        common.drive(s, run)
    finally:
        sheet(s, sh, scratch)
        for src, dst in ((lay.client_log, "emu.log"), (lay.server_log, "server.log"), (lay.packets, "packets.log")):
            if os.path.exists(src):
                shutil.copyfile(src, os.path.join(out, dst))
        if common.env_on("KEEP_SCRATCH"):
            print("scratch kept: %s (phone: %s)" % (scratch, s.phone))
        else:
            shutil.rmtree(scratch, ignore_errors=True)
    print("---")
    lines = s.results + ["FAIL" if s.failed else "PASS"]
    print("\n".join(s.results))
    with open(os.path.join(out, "milestones.txt"), "w") as f:
        f.write("\n".join(lines) + "\n")
    print("screenshots, logs and state dumps in %s" % out)
    print(lines[-1])
    return 1 if s.failed else 0

