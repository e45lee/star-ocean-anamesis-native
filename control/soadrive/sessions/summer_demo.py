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
CDN from work/SOA-3.7.0-canonical-data.zip, --enable-events, --seed-rng 1, --log-packets; soa-emu pointed at it:
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

from .. import popups as _popups, proc, screens, ui370, waits
from ..flows import event, launch, mission
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

    def settle(self, what, **kw):
        """The screen settled (waits.settle), kept as the next shot."""
        self.keep(what, waits.settle(self.s, **kw) or waits.look(self.s))

    def tap(self, what, xy, **kw):
        """A tap to the next screen (waits.tap_to_screen, a note when it doesn't come), kept as the next shot."""
        self.keep(what, waits.tap_to_screen(self.s, what, xy, fatal=None, **kw) or waits.look(self.s))

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
    args = []
    for k, title in SECTIONS:
        if shots.by[k]:
            args += ["@" + title] + shots.by[k]
    r = subprocess.run([sys.executable, os.path.join(REPO, "tools/contact_sheet.py"), "--cols", "6", "--tile", "360", "--title",
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
    # a fixed wait: a picture of the boot at 4 s
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
        # a fixed wait: a picture of the download prompt (the download then waits for itself)
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
    sh.settle("event-list", mask=waits.EVENT_MASK, hold=2)
    # Each row in turn until one opens the beach board whose first story (232:840) opens a story
    # popup (the list is never scrolled: a fling leaves it somewhere else).
    story, battle = event.mid("master_event_mission", "mc99_565"), event.mid("master_event_mission", "me99_1054")
    board, pop = os.path.join(scratch, "board.png"), os.path.join(scratch, "story.png")
    found = None
    for y in (525, 680, 830, 985):
        shutil.copyfile(waits.tap_to_screen(s, "the row at y=%d" % y, "364:%d" % y, mask=waits.EVENT_MASK, fatal=None) or waits.look(s), board)
        if event.beach(board):
            shutil.copyfile(waits.tap_to_screen(s, "the board's first story", "232:840", mask=waits.EVENT_MASK, fatal=None) or waits.look(s), pop)
            if event.story_popup(pop):
                found = y
                break
            s.note("the row at y=%d opens a beach board without the story at 232:840; 戻る" % y)
        else:
            s.note("the row at y=%d is not a beach board; 戻る" % y)
        waits.tap_to_screen(s, "戻る", ui370.BACK, mask=waits.EVENT_MASK, fatal=None)
    if found is None:
        s.fail("no row opened the 水着イベント2020 board")
    s.ok("the summer event board (水着イベント2020, 星の海と夢の渚; row at y=%d)" % found)
    sh.keep("summer-event-board", board)
    sh.keep("story-detail", pop)
    s.tap_until("story 星海に現れし渚 (mc99_565) -> MissionTalk", 60, ui370.STORY_START, lambda: s.in_packets(r"> MissionTalk .* %d " % story),
                every=5)
    sh.settle("story-scene", hold=2)
    sh.tap("story-skip", ui370.STORY_SKIP)
    n = s.n_packets(r"> CheckEventRankingResult")
    s.tap_until("story skipped (はい) -> EndMissionTalk", 60, ui370.STORY_SKIP_YES, lambda: s.in_packets(r"> EndMissionTalk .* %d 1" % story),
                every=5)
    s.wait_for("back on the board (CheckEventRankingResult)", 60, s.more_than(r"> CheckEventRankingResult", n))
    sh.settle("board-story-cleared", mask=waits.EVENT_MASK, hold=2)
    # The battle it unlocked, me99_1054 (New, right of the cleared story).
    sh.tap("mission-detail", "685:655", mask=waits.EVENT_MASK)
    sh.tap("rental", ui370.SINGLE_PLAY)
    sh.tap("party", ui370.RENTAL_NONE, is_screen=_popups.is_party_start)
    mission.open_mission_confirm(s)  # ミッション開始, retried until the confirmation is up (a lost tap)
    sh.shot("start-confirm")
    mission.start_mission(s, "ビーチスポーツ？【初級】 (me99_1054) -> MissionStart -> MissionStartRes",
                          lambda: s.in_packets(r"< MissionStartRes"), opened=True)
    s.check("MissionStart names me99_1054 (%d)" % battle, s.in_packets(r"> MissionStart .* %d " % battle))
    # fixed waits: pictures of the battle's moments (its loading, the fight, the win), nothing to wait for
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
    # (counted before the result pages: the last one's OK leads back to the board; how many pages
    # a tap passes depends on when it lands, as flows/event.py says)
    n = s.n_packets(r"> CheckEventRankingResult")
    for p in ("rewards", "drops", "exp"):
        if s.n_packets(r"> CheckEventRankingResult") > n:
            break
        sh.tap("result-" + p, ui370.RESULT_OK, tries=1)
    s.tap_until("results -> back on the board (CheckEventRankingResult)", 90, ui370.RESULT_OK, s.more_than(r"> CheckEventRankingResult", n),
                every=5)
    sh.settle("board-after-clear", mask=waits.EVENT_MASK, hold=2)
    s.state("2-after-battle")
    sh.tap("home-after-event", ui370.FOOTER_HOME, mask=waits.HOME_MASK)

    # ---- 3. the summer gacha ----
    sh.section = "gacha"
    s.tap_until("ガチャ -> GetGachaInData", 60, ui370.FOOTER_GACHA, lambda: s.in_packets(r"< GetGachaInDataRes"), every=5)
    sh.settle("gacha-menu", mask=waits.GACHA_MASK, hold=2)
    sh.tap("summer-banner", ui370.GACHA_FIRST_BANNER, mask=waits.GACHA_MASK)  # the first banner of おすすめガチャ: 復刻水着2020①
    s.ctl("tap:" + ui370.GACHA_10)  # 10連ガチャ (2,500 coins)
    gacha_flow.open_confirm(s)  # a lost tap or a pick-up page's character detail: retried / closed
    sh.shot("draw-confirm")
    s.tap_until("10-draw: 決定 -> Gacha -> GachaRes", 60, ui370.GACHA_DECIDE, lambda: s.in_packets(r"< GachaRes"), every=5)
    gline = next((ln for ln in open(s.server_log, errors="replace").read().splitlines()
                  if re.match(r"^I/server: Gacha [0-9]* \(.*draws for", ln)), "")
    m = re.match(r"^I/server: Gacha ([0-9]*) ", gline)
    gname = gacha_name(int(m.group(1))) if m else ""
    s.check("a summer gacha: %s (%s)" % (gname or "?", re.sub(r"^I/server: ", "", gline)), re.search(r"水着|夏|サマー", gname))
    # fixed waits: pictures of the summon's moments (the presentation is timed, nothing marks them)
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
    # ALL SKIP until the results (gacha.summon)
    sh.keep("gacha-results", gacha_flow.summon(s) or waits.look(s))
    sh.tap("gacha-results-chips", ui370.GACHA_RESULT_NEXT)  # 次へ
    sh.tap("banner-after-draw", ui370.GACHA_RESULT_NEXT, mask=waits.GACHA_MASK)  # 閉じる
    sh.tap("home-end", ui370.FOOTER_HOME, mask=waits.HOME_MASK)
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
            print("FAIL: %s not built (scripts/build.sh --target %s)" % (b, what))
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

