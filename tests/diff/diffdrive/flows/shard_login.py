"""Shard `login`: the `seeded` flow's start only: the title, Login, the data check, the notice board
and the LOGIN BONUS, home (the seeded player, the seeded flow's options). Per-change gate for the
entry APIs (NoLoginStart, Login, GetPlayer, the login bonus, the notices) and the boot."""
from . import launch, seeded

NAME = "login"
EST = 135
config = seeded.config
SCREENS = dict(launch.SCREENS)


def run(s):
    launch.title(s)
    launch.login_to_home(s)
    s.state("1-home")
    s.check("no ProtocolError in the packet log", not s.in_packets(r"< ProtocolError"))
