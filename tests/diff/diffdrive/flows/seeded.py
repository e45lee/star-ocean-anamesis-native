"""Flow `seeded`: the seeded player (LOCAL00001, data/saves/seed/Game.xml) logs in, the popups, the
campaign's 1-05 (mf01_001: soa-server --campaign-seed mf01_001) through the mission map and its
battle, a 10-draw of the first recommended banner, home. emulator/scripts/emulator_session.sh's
seeded run, on every target. Its parts are the shards `login`, `battle` and `gacha`."""
from . import gacha, launch, mission

NAME = "seeded"
EST = 400  # seconds (3 targets in parallel; the order difftest starts flows in)
CLOCK = "2026-10-01 12:00:05"


def config(Config):
    return Config(["--campaign-seed", "mf01_001"], CLOCK)


# The screens compared between the targets: the RMSE limit against the emulator's (None: shown in
# the report, not gated); home with its character masked (screens.HOME_CHARACTER).
SCREENS = dict(launch.SCREENS, **mission.SCREENS, **gacha.SCREENS)


def run(s):
    launch.title(s)
    launch.login_to_home(s)
    s.state("1-home")
    st = mission.campaign_105(s)
    gacha.ten_draw(s, st)
    s.check("no ProtocolError in the packet log", not s.in_packets(r"< ProtocolError"))
