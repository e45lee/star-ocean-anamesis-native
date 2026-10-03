#!/usr/bin/env python3
"""Writes port/server-data/test-seed.xml: a synthetic seed save for the local server's tests.

The runtime seed (soa's and soa-server's default) is the committed, sanitized real 3.7.0 save data/saves/seed/Game.xml,
which is gitignored because it holds a real account (player id, device id, name). The server's
scratch tests (--selftest "server/") seed from this file instead, so they run in a fresh checkout.
It holds NO real account data: the sanitized player id LOCAL00001, a made-up name and a roster
picked mechanically from the 3.7.0 master data (the first roles of each rarity by id).

The file is an Aska::LocalKVS Game.xml (soa_save/kvs.py) with only the keys the server's seed
reads (server/src/state/seed.cpp seed): player_name / _level / _exp / _fol, person_size +
person_master_role_id_N, player_home_pc_roleid, BAS:PlanetOpen_planetNN, plus BAS:PlayerID.
The tests read their expectations from the constants below (server.cpp "test seed").

usage: .venv/bin/python tools/make_test_seed.py [--master data/basmaster-3.7.0.sqlite3] [--out PATH]
"""
import argparse
import os
import sqlite3
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
from soa_save.kvs import KVSFile  # noqa: E402

NAME = "Tessa"          # made up
LEVEL = 60
EXP = 0
FOL = 250000
PLAYER_ID = "LOCAL00001"  # the sanitized local id (docs/server-rules.md "Seed")
PER_RARITY = {3: 12, 4: 10, 5: 12, 6: 4}  # roles taken per rarity (lowest ids first): 38
PLANETS = 10


def main():
    root = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..")
    ap = argparse.ArgumentParser()
    ap.add_argument("--master", default=os.path.join(root, "data/basmaster-3.7.0.sqlite3"))
    ap.add_argument("--out", default=os.path.join(root, "port/server-data/test-seed.xml"))
    a = ap.parse_args()
    db = sqlite3.connect(f"file:{a.master}?mode=ro", uri=True)
    roles = []
    for rarity, n in sorted(PER_RARITY.items()):
        roles += [r for (r,) in db.execute("select id from master_role where rarity = ? order by id limit ?", (rarity, n))]
    home = roles[PER_RARITY[3] + PER_RARITY[4]]  # the first ★5
    k = KVSFile()
    k.set_str("BAS:PlayerID", PLAYER_ID)
    k.set_str("player_name", NAME)
    k.set_u32("player_level", LEVEL)
    k.set_u32("player_exp", EXP)
    k.set_u32("player_fol", FOL)
    k.set_u32("player_home_pc_roleid", home)
    k.set_u32("person_size", len(roles))
    for i, r in enumerate(roles):
        k.set_u32(f"person_master_role_id_{i}", r)
    for p in range(1, PLANETS + 1):
        k.set_u8(f"BAS:PlanetOpen_planet{p:02d}", 1)
    k.save(a.out)
    print(f"{a.out}: {NAME}, level {LEVEL}, {len(roles)} roles, home {home}")


if __name__ == "__main__":
    main()
