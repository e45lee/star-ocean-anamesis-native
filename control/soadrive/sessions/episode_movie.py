"""Session `episode-movie`: the Episode 2 / 3 opening stories (the in-process local server): title ->
home -> Mission -> the episode list -> Episode 2 (or 3) -> world map STORY point -> 1-01 ->
ストーリー開始 -> オート -> the scene plays its opening movie (m2011_010.mp4 / m6011_010.mp4) -> the
movie must report its end (MovieFinished) -> the scene ends (EndMissionTalk).

The episode's own data (the pack EP<n>) is on the shared phone, but the run's client save decides
whether the client counts it as downloaded; the client gets it from the in-process CDN through its
own flow. SOA_EPISODE_PACKS picks how:
  0 (default)    the "ask" flow: the client's books have no episode (BAS:DownloadEpisodeFlag 0): the
                 episode list's tap asks for the download, はい goes back to the title, TAP TO START
                 -> the data phase downloads version_latest_ep<n> and its bundles (ダウンロード, 完了)
                 -> home again;
  1              the "save" flow: the committed save as it is (Episodes 1-3): the first data phase
                 after Login downloads all three packs (on a phone that has them: only their
                 manifests' .version checked).
Either way the run checks the GET of version_latest_ep<n>, the GETs of Android/EP<n>/ (except in
the save flow on a phone with the pack), that data/files/download/EP<n> exists, and shows その他 ->
Episodeデータ管理 (screenshot 05-episode-data). Ends with PASS (exit 0) or FAIL (exit 1).

Usage: port/scripts/episode_movie_session.sh <soa> <out-dir> <scratch-dir> [2|3]   (from any directory)
Env: CAMPAIGN_SEED (default mf01_001: a returning player), HOME_MISSION_X, SOA_EPISODE_PACKS,
SOA_PHONE (scripts/shared-phone.sh), WATCH=1.
Targets: port-inproc (the phase lines, the in-process CDN's GET lines)."""
import os
import time

from ..flows import launch, mission
from . import common

TARGETS = ("port-inproc",)
TARGETS_WHY = "it waits on the port's phase lines and the in-process server's lines"
WRAPPER = "port/scripts/episode_movie_session.sh"
P = mission.phase


def options(ap):
    common.port_options(ap, extra=False)
    ap.add_argument("episode", nargs="?", default="2", choices=("2", "3"))


def main(o):
    ep = o.episode
    seed = os.environ.get("CAMPAIGN_SEED") or "mf01_001"
    flow = "save" if os.environ.get("SOA_EPISODE_PACKS", "0") == "1" else "ask"
    x = os.environ.get("HOME_MISSION_X") or "270"
    s = common.port_run(o, common.port_config(o, ["--campaign-seed", seed], limit=2400, seed_rng=None))
    y = "470" if ep == "3" else "730"
    info = {}

    def episode_list(shot):
        common.episode_list(s, "%s:1085" % x)
        s.ctl("wait:6000", s.shot_cmd(shot))

    def body(s):
        # A phone that carries the pack: no manifest .bin GET, and in the save flow no bundle GET either.
        had = os.path.isdir(os.path.join(s.phone, "data/files/download/EP" + ep))
        fetch = not (flow == "save" and had)
        epget = r"version_latest_ep%s\.(bin|version)" % ep if had else r"version_latest_ep%s\.bin" % ep
        common.port_login(s, notice=None, bonus=None)
        if flow == "ask":
            # The episode's data isn't there: its tap asks to go back to the title for the download.
            episode_list("03-episodes-before")
            if s.in_client(r"GET .*Android/EP%s/" % ep):
                s.fail("Episode %s's data was fetched before it was asked for" % ep)
            s.ctl("tap:364:" + y, "wait:3000", s.shot_cmd("03-download-needed"))
            s.tap_log(P(1), 60, 10, 3, "tap:515:800", name="はい -> the title")
            # the title's dialog (閉じる 364:713), TAP TO START (no Login: the client is logged in), the
            # data phase: the episode's download dialog (ダウンロード), its bundles, 完了, home.
            s.ctl("wait:4000", s.shot_cmd("03-title-dialog"), "tap:364:713", "wait:3000")
            s.tap_log(r"GET .*" + epget, 90, 10, 6, "tap:364:1000", name="TAP TO START -> version_latest_ep%s" % ep)
            s.tap_log(r"GET .*/Android/EP%s/" % ep, 60, 10, 6, "wait:3000", "tap:515:800", name="Episode %s's download started" % ep)
        # The pack's download: its manifest and bundles; done when no GET is logged for 20 s.
        if fetch:
            s.wait_for("an Episode %s bundle fetched" % ep, 120, lambda: s.in_client(r"GET .*/Android/EP%s/" % ep))
        gets = {"n": -1, "t": time.monotonic()}

        def quiet():
            n = s.count(s.client_log, r"I/http: GET")
            if n != gets["n"]:
                gets["n"], gets["t"] = n, time.monotonic()
            return time.monotonic() - gets["t"] >= 20

        s.wait_for("the downloads stopped", 1200, quiet)
        if not s.in_client(r"GET .*" + epget):
            s.fail("no version_latest_ep%s (%s)" % (ep, epget))
        info["bundles"] = s.count(s.client_log, r"GET .*/Android/EP%s/" % ep)
        print("episode %s: %d bundles of Android/EP%s/ fetched (%s flow)" % (ep, info["bundles"], ep, flow))
        if not os.path.isdir(os.path.join(s.phone, "data/files/download/EP" + ep)):
            s.fail("no data/files/download/EP%s after the download" % ep)
        if flow == "ask":
            s.ctl(s.shot_cmd("04-download-done"))
            s.tap_log(P(4), 180, 10, 15, "tap:364:790", name="完了 -> home")
            launch.popups(s, None, None)
        # その他 -> scroll -> Episodeデータ管理: the episodes and their state; 閉じる.
        s.ctl("tap:665:1250", "wait:5000", "drag:364:900:364:300:800", "wait:2000", "drag:364:900:364:300:800", "wait:2000",
              "tap:364:595", "wait:3000", s.shot_cmd("05-episode-data"), "tap:215:1043", "wait:2000")
        s.tap_log(P(4), 60, 15, 4, "tap:60:1240", name="ホーム -> home")
        s.ctl("wait:3000")
        episode_list("06-episodes")
        s.ctl("tap:364:" + y)
        s.wait_log(r"campaign: GetWorldMapInfoList", 120, name="the world map (GetWorldMapInfoList)")
        s.ctl("wait:8000", s.shot_cmd("07-worldmap"))
        # The STORY point (Episode 2 in the middle of the map, Episode 3 left of it) -> 1-01 -> story start.
        s.ctl("tap:240:650" if ep == "3" else "tap:360:640")
        s.ctl("wait:4000", "tap:364:410", "wait:4000", s.shot_cmd("08-mission"), "tap:515:714")
        s.wait_log(P(3), 120, name="the scene (phase 3)")
        # Auto mode, then fast-forward; no taps from here on (a tap while the movie plays skips it).
        s.ctl("wait:20000", s.shot_cmd("09-scene"), "tap:614:1240", "wait:1000", "tap:115:45")
        if not s.poll(750, lambda: s.in_client(r"PlayMovie\(")):
            s.fail("no movie")
        s.wait_log(r"movie: playing", 30, name="the movie started")
        s.ctl("wait:5000", s.shot_cmd("10-movie"))
        # The movie (124 s / 89 s) must end by itself, then the scene continues to its end.
        s.wait_log(r"movie: ended", 300, name="the movie ended")
        s.ctl("wait:3000", s.shot_cmd("11-after-movie"))
        s.wait_log(r"EndMissionTalk", 300, name="the scene ended (EndMissionTalk)")
        s.wait_log(r"story scene played", 30, name="story scene played")
        s.ctl("wait:8000", s.shot_cmd("12-worldmap"))

    if not common.drive(s, body):
        return 1
    fails = common.checks((s.in_client(r"request EndMissionTalk"), "no EndMissionTalk"))
    return common.verdict(s, fails, "episode %s: the opening movie played to its end, the scene done (EndMissionTalk)" % ep)
