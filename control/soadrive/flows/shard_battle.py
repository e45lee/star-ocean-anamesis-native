"""Shard `battle`: login, then the `seeded` flow's campaign battle (1-05, mf01_001: the mission map,
the battle, the result pages, home). Per-change gate for the mission APIs (GetMissionList,
MissionStart, MissionEnd and its rewards) without the gacha."""
from . import launch, mission, seeded

NAME = "battle"
EST = 280
config = seeded.config
SCREENS = dict(launch.SCREENS, **mission.SCREENS)


def run(s):
    launch.title(s)
    launch.login_to_home(s)
    s.state("1-home")
    mission.campaign_105(s)
    s.check("no ProtocolError in the packet log", not s.in_packets(r"< ProtocolError"))
