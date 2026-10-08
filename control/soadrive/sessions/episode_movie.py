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
        common.settle(s, mask=common.HOME_MASK)
        common.episode_list(s, "%s:1085" % x)
        common.settle(s, shot, hold=2)

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
            common.tap_to_screen(s, "the episode -> its download question", "364:" + y, "03-download-needed")
            s.tap_log(P(1), 60, 10, 3, "tap:515:800", name="はい -> the title")
            # the title's dialog (閉じる 364:713), TAP TO START (no Login: the client is logged in), the
            # data phase: the episode's download dialog (ダウンロード), its bundles, 完了, home.
            common.settle(s, "03-title-dialog", hold=2)
            common.tap_to_screen(s, "the title's dialog: 閉じる", "364:713")
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
        common.settle(s, mask=common.HOME_MASK)
        common.tap_to_phase(s, "その他", "665:1250", 12, mask=common.HOME_MASK, fatal=True)
        for _ in range(2):
            s.ctl("drag:364:900:364:300:800")
            common.settle(s)
        common.tap_to_screen(s, "Episodeデータ管理", "364:595", "05-episode-data")
        common.tap_to_screen(s, "Episodeデータ管理: 閉じる", "215:1043")
        common.tap_to_phase(s, "ホーム -> home", "60:1240", 4, every=15, tries=4, mask=common.HOME_MASK, fatal=True)
        episode_list("06-episodes")
        s.ctl("tap:364:" + y)
        s.wait_log(r"campaign: GetWorldMapInfoList", 120, name="the world map (GetWorldMapInfoList)")
        common.settle(s, "07-worldmap", hold=2)
        # The STORY point (Episode 2 in the middle of the map, Episode 3 left of it) -> 1-01 -> story start.
        common.tap_to_screen(s, "the STORY point", "240:650" if ep == "3" else "360:640")
        common.tap_to_screen(s, "1-01", "364:410", "08-mission")
        common.tap_to_log(s, "the scene (phase 3)", "515:714", P(3), secs=120, tries=1, fatal=True, wait_still=False)
        # Auto mode, then fast-forward; no taps from here on (a tap while the movie plays skips it).
        # A fixed wait: the scene's buttons appear after its intro and nothing marks that (as the
        # tutorial's opening, flows/tutorial.py).
        s.ctl("wait:20000", s.shot_cmd("09-scene"), "tap:614:1240", "wait:1000", "tap:115:45")
        if not s.poll(750, lambda: s.in_client(r"PlayMovie\(")):
            s.fail("no movie")
        s.wait_log(r"movie: playing", 30, name="the movie started")
        # a fixed wait: a picture of the movie at 5 s (a movie never holds still)
        s.ctl("wait:5000", s.shot_cmd("10-movie"))
        # The movie (124 s / 89 s) must end by itself, then the scene continues to its end.
        s.wait_log(r"movie: ended", 300, name="the movie ended")
        common.settle(s, "11-after-movie", secs=15)
        s.wait_log(r"EndMissionTalk", 300, name="the scene ended (EndMissionTalk)")
        s.wait_log(r"story scene played", 30, name="story scene played")
        common.settle(s, "12-worldmap", hold=2)

    if not common.drive(s, body):
        return 1
    fails = common.checks((s.in_client(r"request EndMissionTalk"), "no EndMissionTalk"))
    return common.verdict(s, fails, "episode %s: the opening movie played to its end, the scene done (EndMissionTalk)" % ep)
