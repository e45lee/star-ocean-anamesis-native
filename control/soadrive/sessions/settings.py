"""Session `settings`: the options the server keeps and the story library (docs/server-rules.md#settings,
#scenario-library; docs/unimplemented-apis.md step 3.3).

Boot 1: title -> home -> その他 -> 設定 -> その他設定 (GetConfig) -> 一時保管庫設定 on (UpdateConfig
4025152546 "true") -> 閉じる -> その他設定 again (still on: 11-reopened) -> 閉じる. Between the boots the
test setup marks Episode 1's first two story chapters as cleared (campaign_clear: every master_mission
of library_EP1_main_story_00 / _01, read from the master). Boot 2 (the same phone and state: a
restart): その他設定 (still on after the restart: 21-after-restart) -> 初期設定に戻す -> 決定
(ResetConfig) -> その他設定 (off: 23-after-reset); then ミッション -> Episode 1 -> the planet select ->
シナリオライブラリ (GetScenarioLibraryInfoList: the planted missions, 30-library).

The checks read the server's log lines (UpdateConfig / ResetConfig / GetScenarioLibraryInfoList) and
its state DB (the table `config`), so they hold for both targets. Ends with PASS (exit 0) or FAIL (exit 1).

Usage: port/scripts/settings_session.sh <soa> <out-dir> <scratch-dir>   (from any directory)
Env: SOA_PHONE, SEED_RNG, WATCH=1.
Targets: port-inproc (default), port-server (the server's lines are read from its log)."""
import os
import sqlite3

from ..proc import repo_file
from . import common

TARGETS = ("port-inproc", "port-server")
WRAPPER = "port/scripts/settings_session.sh"

STORAGE = 4025152546  # master_config is_one_time_storage (CHash32 of the label)
OTHER, SETTINGS, OTHER_SETTINGS = "667:1250", "364:345", "364:913"  # footer その他, 設定, その他設定
BOX1, CLOSE = "563:350", "364:1042"  # 一時保管庫設定's box, the dialog's 閉じる
RESET, RESET_OK, RESET_CLOSE = "620:1120", "515:713", "364:713"  # 初期設定に戻す, 決定, 閉じる
LIBRARY = "373:1037"  # the planet select's シナリオライブラリ
HOME = "60:1250"  # the footer's ホーム


def options(ap):
    common.port_options(ap, extra=False)


def stored(s):
    """The option's row in the server's state: its value, or None."""
    c = sqlite3.connect(s.state_db)
    row = c.execute("select value from config where master_config_id = ?", (STORAGE,)).fetchone()
    c.close()
    return row[0] if row else None


def plant_library(db):
    """Test setup: Episode 1's first two chapters cleared (campaign_clear); their mission count."""
    m = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
    ids = [r[0] for r in m.execute("select m.id from master_mission m join master_scenario_library s on s.id = m.master_scenario_library_id "
                                   "where s.id_label in ('library_EP1_main_story_00', 'library_EP1_main_story_01')")]
    s = sqlite3.connect(db)
    s.execute("pragma foreign_keys = on")  # PLAN-schema S1: every connection that writes the state
    s.executemany("insert into campaign_clear (mission_id) values (?) on conflict do nothing", [(i,) for i in ids])
    s.commit()
    s.close()
    return len(ids)


def screen(s, name, xy, shot=None, **kw):
    return common.tap_to_screen(s, name, xy, shot, **kw)


def open_other_settings(s, shot):
    common.settle(s, mask=common.HOME_MASK)
    common.tap_to_phase(s, "その他", OTHER, 12, mask=common.HOME_MASK, fatal=True)
    screen(s, "設定", SETTINGS)
    screen(s, "その他設定", OTHER_SETTINGS, shot)


def main(o):
    s1 = common.port_run(o, common.port_config(o, limit=2400))
    seen = {}

    def boot1(s):
        common.port_login(s, notice=None, bonus=None)
        n = s.n_packets(r"GetConfig")
        open_other_settings(s, "10-other-settings")
        s.wait_for("GetConfig (その他設定)", 30, s.more_than(r"GetConfig", n))
        # the box: a toggle (made again only when no UpdateConfig came)
        common.tap_to_server(s, "UpdateConfig %d \"true\" (一時保管庫設定 on)" % STORAGE, r"UpdateConfig %d: \"true\"" % STORAGE,
                             ["tap:" + BOX1], secs=30, changes=False)
        screen(s, "閉じる", CLOSE)
        screen(s, "その他設定 again", OTHER_SETTINGS, "11-reopened")
        screen(s, "閉じる", CLOSE)
        seen["boot1"] = stored(s)

    if not common.drive(s1, boot1):
        return 1
    planted = plant_library(s1.state_db)
    s = common.port_run_again(o, common.port_config(o, limit=2400), "log-2.txt")

    def boot2(s):
        common.port_login(s, notice=None, bonus=None)
        seen["restart"] = stored(s)
        open_other_settings(s, "21-after-restart")
        screen(s, "閉じる", CLOSE)
        screen(s, "初期設定に戻す", RESET, "22-reset-dialog")
        common.tap_to_server(s, "ResetConfig (初期設定に戻す)", r"ResetConfig: every option back", ["tap:" + RESET_OK], secs=30)
        screen(s, "reset: 閉じる", RESET_CLOSE)
        screen(s, "その他設定 again", OTHER_SETTINGS, "23-after-reset")
        screen(s, "閉じる", CLOSE)
        seen["reset"] = stored(s)
        # ミッション -> the episode list -> Episode 1 (the third banner) -> the planet select -> シナリオライブラリ
        common.tap_to_phase(s, "ホーム", HOME, 4, mask=common.HOME_MASK, fatal=True)
        common.episode_list(s, "270:1085")
        common.settle(s)
        s.ctl("drag:364:850:364:400")
        common.settle(s)
        common.tap_to_phase(s, "Episode 1 -> the planet select", "364:805", 5, "29-planets", secs=120, fatal=True)
        common.tap_to_server(s, "GetScenarioLibraryInfoList (シナリオライブラリ)", r"GetScenarioLibraryInfoList [0-9]+: ", ["tap:" + LIBRARY],
                             "30-library", hold=2)
        line = s.last_line(r"GetScenarioLibraryInfoList [0-9]+: ", s.server_log) or ""
        seen["listed"] = common.state_value(line, r"GetScenarioLibraryInfoList [0-9]+: ([0-9]+) cleared")

    if not common.drive(s, boot2):
        return 1
    print("config %d: %s after the toggle, %s after the restart, %s after the reset; %d library missions planted" %
          (STORAGE, seen.get("boot1"), seen.get("restart"), seen.get("reset"), planted))
    fails = common.checks(
        (seen.get("boot1") == "true", "UpdateConfig wasn't stored"),
        (seen.get("restart") == "true", "the option didn't survive the restart"),
        (seen.get("reset") is None, "ResetConfig left the option's row"),
        (planted > 0, "no Episode 1 library missions in the master"),
        ((seen.get("listed") or 0) >= planted, "the library listed %s missions, not the %d planted" % (seen.get("listed"), planted)),
    ) + common.common_log_checks(s)
    return common.verdict(s, fails, "一時保管庫設定 stored, kept over a restart and reset; シナリオライブラリ lists %s cleared missions" % seen.get("listed"))
