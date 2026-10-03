"""Shard `gacha`: login, then the `seeded` flow's 10-draw straight from home (no battle before it:
the coins and the draws are the seeded player's from the start). Per-change gate for the gacha
APIs (GetGachaInData, SaleGacha) and the wallet."""
from . import gacha, launch, seeded

NAME = "gacha"
EST = 255
config = seeded.config
SCREENS = dict(launch.SCREENS, **gacha.SCREENS)


def run(s):
    launch.title(s)
    launch.login_to_home(s)
    st = s.state("1-home")
    gacha.ten_draw(s, st)
    s.check("no ProtocolError in the packet log", not s.in_packets(r"< ProtocolError"))
