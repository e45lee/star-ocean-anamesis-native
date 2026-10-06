"""Flow `event`: the summer event mission (the server's --enable-events): イベント -> the 水着イベント2020
board (星の海と夢の渚, event_sww2020_93) -> its first story mc99_565 (skipped: EndMissionTalk), which
unlocks the battle me99_1054 -> single play, no rental, party 1 -> the battle -> the result pages
-> back on the board -> home. emulator/scripts/summer_demo.sh's event part, on every target."""
import re
import sqlite3

from .. import proc, screens, ui370
from ..targets import Abort
from . import launch, mission

NAME = "event"
EST = 330
# summer_demo.sh's calendar (the event list's rows depend on it), a few seconds past the hour.
CLOCK = "2026-10-01 12:00:05"


def config(Config):
    return Config(["--enable-events"], CLOCK)


# home: the still parts at the still limit, the character masked (screens.HOME_CHARACTER)
HOME = (0.08, (screens.HOME_CHARACTER,))
SCREENS = {
    "01-title": 0.08,
    "02b-login-bonus": 0.08,
    "02-home": HOME,
    "03-event-list": 0.08,
    "04-event-board": 0.10,
    "05-story-detail": 0.10,
    "06-story-skip": None,
    "07-board-story-cleared": 0.10,
    "08-mission-detail": 0.08,
    "09-party": 0.08,
    "10-start-confirm": 0.08,
    "11-battle": None,
    "12-result-rewards": None,
    "13-result-drops": None,
    "14-result-exp": None,
    "15-board-after-clear": 0.10,
    "16-home-after-event": HOME,
}


def mid(table, label):
    db = proc.repo_file("data/basmaster-3.7.0.sqlite3")
    r = sqlite3.connect("file:%s?mode=ro" % db, uri=True).execute("select id from %s where id_label = ?" % table, (label,)).fetchone()
    return r[0] if r else None


def beach(path):
    """The 星の海と夢の渚 board: sand below the sea (warm in the lower middle); the other boards and
    the event list are space (blue)."""
    v = screens.fx(path, "mean.r - mean.b", "600x250+60+850")
    return v is not None and v > 0.08


def story_popup(path):
    m = screens.mean(path, "729x200+0+560")
    w = screens.fx(path, "mean.r - mean.b", "600x120+60+880")
    return m is not None and w is not None and m < 0.32 and w > 0.05


def run(s):
    story, battle = mid("master_event_mission", "mc99_565"), mid("master_event_mission", "me99_1054")
    launch.title(s)
    launch.login_to_home(s)
    s.state("1-home")

    n = s.n_packets(r"> CheckEventRankingResult")
    s.tap_until("イベント -> the event menu (CheckEventRankingResult)", 60, ui370.HOME_EVENT, s.more_than(r"> CheckEventRankingResult", n))
    s.ctl("wait:6000")
    s.shot("03-event-list")
    # The rows in turn until one opens the beach board whose first story (232:840) opens a story
    # popup (summer_demo.sh: the list is never scrolled).
    board, pop = s.scratch("board.png"), s.scratch("story.png")
    found = None
    for y in (525, 680, 830, 985):
        s.send(["tap:364:%d" % y, "wait:7000", "shot:" + board])
        if beach(board):
            s.send(["tap:232:840", "wait:3000", "shot:" + pop])
            if story_popup(pop):
                found = y
                break
            s.note("the row at y=%d opens a beach board without the story at 232:840" % y)
        else:
            s.note("the row at y=%d is not the beach board" % y)
        s.send(["tap:" + ui370.BACK, "wait:5000", "shot:" + s.scratch("back.png")])
    if not s.check("the summer event board (水着イベント2020)%s" % (" at the row y=%d" % found if found else ""), found is not None):
        raise Abort("no event board")
    s.keep_shot("04-event-board", board)
    s.keep_shot("05-story-detail", pop)
    s.tap_until("story mc99_565 -> MissionTalk", 60, ui370.STORY_START, lambda: s.in_packets(r"> MissionTalk .* %d " % story))
    s.ctl("wait:10000", "tap:" + ui370.STORY_SKIP, "wait:2000")
    s.shot("06-story-skip", settle=False)
    n = s.n_packets(r"> CheckEventRankingResult")
    s.tap_until("story skipped (はい) -> EndMissionTalk", 60, ui370.STORY_SKIP_YES, lambda: s.in_packets(r"> EndMissionTalk .* %d 1" % story))
    s.wait_for("back on the board (CheckEventRankingResult)", 60, s.more_than(r"> CheckEventRankingResult", n))
    s.ctl("wait:6000")
    s.shot("07-board-story-cleared")
    # The battle the story unlocked, me99_1054 (right of the cleared story).
    s.ctl("tap:685:655", "wait:4000")
    s.shot("08-mission-detail")
    s.ctl("tap:" + ui370.SINGLE_PLAY, "wait:5000", "tap:" + ui370.RENTAL_NONE, "wait:5000")
    s.shot("09-party")
    mission.open_mission_confirm(s)
    s.shot("10-start-confirm")
    mission.start_mission(s, "me99_1054 -> MissionStart -> MissionStartRes", lambda: s.in_packets(r"< MissionStartRes"), opened=True)
    s.check("MissionStart names me99_1054 (%d)" % battle, s.in_packets(r"> MissionStart .* %d " % battle))
    s.ctl("wait:15000")
    s.shot("11-battle", settle=False)
    s.wait_for("the battle: MissionEnd (battle log) -> MissionEndRes", 600, lambda: s.in_packets(r"< MissionEndRes"))
    s.check("server: me99_1054's first clear", s.in_server(r"MissionEnd mission %d: .*first clear" % battle))
    # (counted before the result pages: their last OK can already lead back to the board)
    n = s.n_packets(r"> CheckEventRankingResult")
    s.ctl("wait:7000")
    for p in ("12-result-rewards", "13-result-drops", "14-result-exp"):
        if s.n_packets(r"> CheckEventRankingResult") > n:
            break
        s.ctl("tap:" + ui370.RESULT_OK, "wait:4000")
        s.shot(p, settle=False)
    s.tap_until("the result pages -> back on the board (CheckEventRankingResult)", 90, ui370.RESULT_OK,
                s.more_than(r"> CheckEventRankingResult", n))
    s.ctl("wait:6000")
    s.shot("15-board-after-clear")
    st1 = open(s.scratch("state-1-home.txt")).read()
    st = s.state("2-after-battle")
    s.check("state: story mc99_565 cleared", re.search(r"^  mission %d: cleared" % story, st, re.M) is not None)
    s.check("state: battle me99_1054 cleared", re.search(r"^  mission %d: cleared" % battle, st, re.M) is not None)
    s.check("state: mc99_566 unlocked by me99_1054", "unlocked mc99_566 (by me99_1054)" in st)
    coin = lambda t: int((re.search(r"^  stock item_coin_291 x(\d+)", t, re.M) or [0, 0])[1])
    s.check("state: event drops (item_coin_291 %d -> %d)" % (coin(st1), coin(st)), coin(st) > coin(st1))
    s.ctl("tap:" + ui370.FOOTER_HOME, "wait:8000")
    s.shot("16-home-after-event")
    s.check("no ProtocolError in the packet log", not s.in_packets(r"< ProtocolError"))
