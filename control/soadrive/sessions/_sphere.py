"""What the two Sphere 211 sessions share: the test setup in the state DB, the state dump, a battle
from a cell's detail, the login with the rental bonus popup, the board."""
import os
import re
import sqlite3
import time

from ..flows import launch, mission
from ..proc import repo_file
from . import common

# the map the cell taps are for (the server lots it with --seed-rng 605)
MAP = "2554458071"


def sql(s, *queries):
    c = sqlite3.connect(s.state_db, timeout=60)
    c.execute("pragma foreign_keys = on")  # PLAN-schema S1: every connection that writes the state
    for q in queries:
        c.execute(q)
    c.commit()
    c.close()


def state(s, tag):
    c = sqlite3.connect(s.state_db)
    r = c.execute("select season_id, floor_level, streak, treasure_total, stamina, clear_asset, lot_floor_num from sphere").fetchone()
    out = ["sphere season %s floor %s streak %s treasure_total %s stamina %s clear_asset %s lot %s" % r,
           "cells %s cleared %s" % (c.execute("select count(*) from sphere_cell").fetchone()[0],
                                    c.execute("select count(*) from sphere_cell where cleared = 1").fetchone()[0]),
           "boxes %s" % c.execute("select count(*) from sphere_box").fetchone()[0],
           "departed %s" % c.execute("select count(*) from sphere_departed").fetchone()[0]]
    out += ["rank season %s best floor %s" % x for x in c.execute("select season_id, floor_level from sphere_rank")]
    c.close()
    text = "\n".join(out) + "\n"
    with open(os.path.join(s.layout.state_dir, "state-%s.txt" % tag), "w") as f:
        f.write(text)
    print(text, end="", flush=True)
    return text


def setup(s):
    """The season's heal and reroll tickets, and 5 Sphere 211 rentals two days ago, unpaid (the
    season named in the log's client-master line)."""
    m = re.search(r"Sphere211: season ([0-9]+)", open(s.client_log, errors="replace").read())
    if not m:
        s.fail("no Sphere211 season in the log")
    c = sqlite3.connect(s.state_db, timeout=60)
    c.execute("pragma foreign_keys = on")
    master = sqlite3.connect("file:%s?mode=ro" % repo_file("data/basmaster-3.7.0.sqlite3"), uri=True)
    for i, t in master.execute("select id, type from master_item where id_label like 'item_sphere_stamina_%' or id_label like 'item_sphere_re_%'"):
        c.execute("insert into stock (master_item_id, item_type, count) values (?, ?, 2) on conflict(master_item_id) do update set count = 2", (i, t))
    c.execute("create table if not exists sphere_rental_day (day integer primary key, season_id integer, count integer default 0, paid integer default 0)")
    c.execute("insert or replace into sphere_rental_day (day, season_id, count, paid) values (?, ?, 5, 0)",
              (int(time.time()) - 2 * 86400, int(m.group(1))))
    c.commit()
    c.close()


def login_to_board(s):
    """The title, the test setup, Login -> home, the popups, the rental bonus popup, the home's
    スフィア211 -> the board (floor 1 on MAP); state-1-floor1."""
    launch.title(s, "01-title")
    setup(s)
    launch.login_to_home(s, "02-notice", "03-login-bonus", "04-home")
    if not s.in_client(r"Sphere211 rental bonus: 5 rentals"):
        s.fail("the Sphere 211 rental bonus wasn't paid")
    s.ctl("wait:3000", s.shot_cmd("04b-rental-bonus"), "tap:364:800", "wait:3000", s.shot_cmd("04c-home"))
    s.tap_log(r"GetSphere211Info: season", 60, 20, 3, "tap:455:1085", name="スフィア211 -> the board")
    s.ctl("wait:6000", s.shot_cmd("05-board"))
    if not s.in_client(r"Sphere211: floor 1 \(floor row [0-9]*\), map %s " % MAP):
        s.fail("floor 1 isn't the map this session's taps are for (--seed-rng 605 lots map %s): %s"
               % (MAP, s.last_line(r"Sphere211: floor 1")))
    return state(s, "1-floor1")


def battle(s, tag, rent=False, retry_start=True):
    """The cell's detail is open: single play -> the rental list (the first lender with rent, else
    選択しない) -> auto party -> start -> the battle -> the result pages until the board (phase 5)."""
    s.ctl("wait:4000", s.shot_cmd(tag + "-detail"), "tap:364:905", "wait:5000", s.shot_cmd(tag + "-rental"))
    s.ctl("tap:364:383" if rent else "tap:628:1120")
    s.ctl("wait:4000", "tap:364:898")
    s.wait_log(r"Sphere211AutoMemberSelect: 4 members proposed", 30, name=tag + ": auto member select")
    s.ctl("wait:4000", s.shot_cmd(tag + "-party"))
    # ミッション開始 -> 決定, resent until the server logs the start (a tap can be dropped under load)
    if retry_start:
        s.tap_log(r"Sphere211MissionStart: floor", 60, 15, 3, "tap:140:898", "wait:3000", "tap:515:713", name=tag + ": Sphere211MissionStart")
    else:
        s.ctl("tap:140:898", "wait:3000", "tap:515:713")
        s.wait_log(r"Sphere211MissionStart: floor", 60, name=tag + ": Sphere211MissionStart")
    s.ctl("wait:15000", s.shot_cmd(tag + "-battle"))
    line = s.wait_log(r"Sphere211MissionEnd: |Sphere211MissionFailed", 500, name=tag + ": the battle ended", fatal=False)
    if line is None:
        s.ctl(s.shot_cmd(tag + "-stuck"))
        s.fail(tag + ": the battle didn't end")
    if "Sphere211MissionFailed" in line:
        s.fail(tag + ": the battle was lost")
    s.ctl("wait:10000", s.shot_cmd(tag + "-result"))
    i = 0
    while s.cursor.wait(mission.phase(5), 4, alive=s.alive) is None:
        s.ctl("tap:364:1050")
        i += 1
        if i >= 12:
            s.fail(tag + ": the result pages didn't end")
    s.ctl("wait:6000")


def port_config(o):
    return common.port_config(o, limit=2400, seed_rng=int(os.environ.get("SEED_RNG") or 605))
