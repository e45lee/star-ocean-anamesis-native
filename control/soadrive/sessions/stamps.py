"""Session `stamps`: キャラクター > スタンプ編成 (the chat stamps' palette) against the local server
(docs/server-rules.md#stamps). Boot 1: the screen lists the 12 default stamps and the default palette
(pages 1-3 filled in order_id order, page 4 empty) -> page 1's first slot gets HELP (stamp_05: it
swaps with よろしく, which goes to page 2) -> page 4's first slot gets RUSH (stamp_09: it leaves page
3) -> 戻る (SetStampSlot: the whole palette, checked slot by slot). Boot 2, the same phone (the
re-login check): page 3's first slot gets RUSH back from page 4 -> 戻る (SetStampSlot): the palette
the client sends is boot 1's with that one move, so the client had the kept palette. The milestones
are the server's log lines (both targets); the end state the server's state DB. Screenshots go to
OUT/shots (the re-login's r*).
Prints "PASS: ..." (exit 0) or the failed checks and "FAIL: ..." (exit 1).

Usage: port/scripts/stamps_session.sh [--target port-inproc|port-server] <soa> <out-dir> <scratch-dir>
Env: SEED_RNG, SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc (default), port-server."""
import re
import sqlite3

from .. import milestones
from ..proc import repo_file
from . import common

TARGETS = ("port-inproc", "port-server")
WRAPPER = "port/scripts/stamps_session.sh"

CHARA_MENU = "tap:180:1245"
STAMP_MENU = "tap:364:785"  # スタンプ編成, the character menu scrolled to its end
SLOT1, NEXT_PAGE, PREV_PAGE, BACK = "165:300", "690:310", "40:310", "100:1120"
HELP, RUSH = "95:740", "95:885"  # the stamp list: the second row's first (stamp_05), the third row's first (stamp_09)


def options(ap):
    common.port_options(ap, extra=False)


def defaults():
    """The type-1 stamps in order_id order (the server's default palette, pages 1-3)."""
    m = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
    return [r[0] for r in m.execute("select id from master_stamp where type = 1 order by order_id, id")]


def server_step(s, rx, name, secs=40):
    """Waits for the next server-log line matching rx (counted from the step's start)."""
    before = milestones.count(s.server_log, rx)
    return lambda: s.wait_for(name, secs, lambda: milestones.count(s.server_log, rx) > before)


def open_stamps(s, shot):
    # scrolled to the end (one drag scrolls a varying distance)
    s.ctl(CHARA_MENU, "wait:5000", "drag:364:1000:364:300", "wait:1500", "drag:364:1000:364:300", "wait:1500", "drag:364:1000:364:300",
          "wait:2500", s.shot_cmd(shot + "-menu"), STAMP_MENU, "wait:5000", s.shot_cmd(shot))


def sent_palette(s):
    """The last SetStampSlot's palette from the server log."""
    m = None
    for ln in open(s.server_log, errors="replace").read().splitlines():
        m = re.search(r"SetStampSlot: [0-9]+ slots \[([0-9,]*)\]", ln) or m
    return [int(x) for x in m.group(1).split(",")] if m and m.group(1) else []


def boot1(s):
    c = s.ctl
    common.port_login(s, notice=None, bonus=None)
    open_stamps(s, "03-stamps")
    c("tap:" + SLOT1, "wait:1500", "tap:" + HELP, "wait:2000", s.shot_cmd("04-help-on-page1"))
    c("tap:" + NEXT_PAGE, "wait:1200", "tap:" + NEXT_PAGE, "wait:1200", "tap:" + NEXT_PAGE, "wait:1500", s.shot_cmd("05-page4"))
    c("tap:" + SLOT1, "wait:1500", "tap:" + RUSH, "wait:2000", s.shot_cmd("06-rush-on-page4"))
    done = server_step(s, r"SetStampSlot: 16 slots", "戻る: SetStampSlot sent")
    c("tap:" + BACK)
    done()
    c("wait:3000", s.shot_cmd("07-back"))


def boot2(s):
    c = s.ctl
    common.port_login(s, notice=None, bonus=None)
    open_stamps(s, "r03-stamps")
    c("tap:" + NEXT_PAGE, "wait:1200", "tap:" + NEXT_PAGE, "wait:1200", "tap:" + NEXT_PAGE, "wait:1500", s.shot_cmd("r04-page4-kept"))
    c("tap:" + PREV_PAGE, "wait:1500", "tap:" + SLOT1, "wait:1500", "tap:" + RUSH, "wait:2000", s.shot_cmd("r05-rush-on-page3"))
    done = server_step(s, r"SetStampSlot: 16 slots", "after a re-login: 戻る sends SetStampSlot")
    c("tap:" + BACK)
    done()
    c("wait:3000", s.shot_cmd("r06-back"))


def main(o):
    d = defaults()
    if len(d) != 12:
        print("FAIL: the master has %d type-1 stamps, not 12" % len(d))
        return 1
    # boot 1: HELP (d[4]) and よろしく (d[0]) swap, RUSH (d[8]) moves from page 3 to page 4
    want1 = [d[4], d[1], d[2], d[3], d[0], d[5], d[6], d[7], 0, d[9], d[10], d[11], d[8], 0, 0, 0]
    # boot 2: RUSH back to page 3's first slot
    want2 = [d[4], d[1], d[2], d[3], d[0], d[5], d[6], d[7], d[8], d[9], d[10], d[11], 0, 0, 0, 0]
    s = common.port_run(o, common.port_config(o, limit=1800))
    if not common.drive(s, boot1):
        return 1
    got1 = sent_palette(s)
    s2 = common.port_run_again(o, common.port_config(o, limit=1800), "log-relogin.txt")
    ok2 = common.drive(s2, boot2)
    got2 = sent_palette(s2)
    st = sqlite3.connect("file:%s?mode=ro" % s2.state_db, uri=True)
    stored = [r[0] or 0 for r in st.execute("select stamp_id from stamp_slots order by slot")]
    owned = st.execute("select count(*) from stamps").fetchone()[0]
    print("boot 1 sent %s\nboot 2 sent %s\nend state: %d stamps owned, palette %s" % (got1, got2, owned, stored))
    fails = [] if ok2 else ["the re-login boot didn't finish"]
    fails += common.checks((got1 == want1, "boot 1's palette isn't the expected swap and move (want %s)" % want1),
                           (got2 == want2, "after the re-login the client didn't start from the kept palette (want %s)" % want2),
                           (stored == want2, "the state DB's palette isn't the last one sent"), (owned == 12, "%d stamps owned, not 12" % owned))
    for run in (s, s2):
        if milestones.count(run.server_log, r"refused with error"):
            fails.append("a request was refused (%s)" % run.server_log)
        if milestones.count(run.client_log, r"Unhandled SIG|\*\*\* host signal"):
            fails.append("soa crashed (%s)" % run.client_log)
    return common.verdict(s2, fails, "スタンプ編成 lists the default stamps and palette, a change is sent (SetStampSlot), kept, and the "
                          "client starts from it after a re-login")
