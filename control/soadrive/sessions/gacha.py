"""Session `gacha`: the scripted route into the gacha (729x1296 window), for coverage/profiling and as
a gacha check: title -> Login -> the data check -> home (notice board, LOGIN BONUS) -> the footer's
ガチャ (CPhase_Gacha: GetGachaInData) -> the four tabs -> おすすめガチャ's first banner -> 10連ガチャ ->
決定 (SaleGacha: 2500 free coins) -> the summon presentation -> the reveals -> the result list (次へ,
閉じる) -> ホーム (the shared gacha flow). The server state (tools/server_state.py) is dumped before
and after the draw (OUT/state-*.txt): the coins must be debited and the drawn characters added.
Ends with PASS (exit 0) or FAIL (exit 1).

The phone: the shared pre-downloaded one, linked; SOA_PHONE=DIR another, SOA_PHONE=none an empty one.
Usage: port/scripts/gacha_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SEED_RNG, WATCH=1; SOA_COVERAGE / SOA_PROFILE pass through to soa.
Targets: port-inproc (default), port-server, emu (the server's lines are read from its log)."""
import os
import re

from ..flows import gacha
from . import common

TARGETS = ("port-inproc", "port-server", "emu")
WRAPPER = "port/scripts/gacha_session.sh"


def options(ap):
    common.port_options(ap, extra=False)


def main(o):
    s = common.port_run(o, common.port_config(o))

    def body(s):
        common.port_login(s, notice=None, bonus=None)
        st1 = s.state("1-home")
        gacha.open_gacha(s, "03-gacha")
        s.wait_for("gachas open (GetGachaInData)", 30, lambda: s.in_server(r"GetGachaInData: [1-9][0-9]* gachas open"))
        for name, xy, shot in (("キャラ", "275:175", "04-tab-chara"), ("武器", "450:175", "05-tab-weapon"), ("イベント", "625:175", "06-tab-event")):
            common.tap_to_screen(s, "the tab " + name, xy, shot, mask=common.GACHA_MASK)
        gacha.ten_draw(s, st1, opened=True)
        s.state("2-drawn")
        s.ctl("profile-dump")

    if not common.drive(s, body):
        return 1
    st = lambda tag: open(os.path.join(o.out, "state-%s.txt" % tag)).read()
    c1, c2 = (common.state_value(st(t), r"coins free ([0-9]+)") for t in ("1-home", "2-drawn"))
    r1, r2 = (common.state_value(st(t), r"^roster: ([0-9]+)") for t in ("1-home", "2-drawn"))
    print("server state: free coins %s -> %s, roster %s -> %s" % (c1, c2, r1, r2))
    fails = common.checks((c1 is not None and c2 is not None and c2 < c1, "no coins were debited")) + \
        common.common_log_checks(s)
    for ln in open(s.server_log, errors="replace").read().splitlines():
        if re.search(r"I/server: (GetGachaInData|(Sale)?Gacha) ", ln):
            print("  " + ln)
    return common.verdict(s, fails, "the gacha listed, a 10-draw debited %s coins (roster %s -> %s), the presentation and "
                          "the result, back home" % ((c1 - c2) if c1 is not None and c2 is not None else "?", r1, r2))
