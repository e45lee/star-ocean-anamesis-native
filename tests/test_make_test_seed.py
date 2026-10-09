"""tools/make_test_seed.py: the default output is the committed test seed; --extra-roles / --home."""
import pathlib
import sqlite3

import pytest

import make_test_seed as mts
from soa_save.kvs import KVSFile

ROOT = pathlib.Path(__file__).resolve().parent.parent


MASTER = ROOT / "data/basmaster-3.7.0.sqlite3"
pytestmark = pytest.mark.skipif(not MASTER.is_file(), reason="needs the 3.7.0 master")


def db():
    return sqlite3.connect(f"file:{MASTER}?mode=ro", uri=True)


def roster(k):
    return [k.get_u32(f"person_master_role_id_{i}") for i in range(k.get_u32("person_size"))]


def test_default_is_the_committed_seed(tmp_path):
    out = tmp_path / "seed.xml"
    mts.main(["--master", str(MASTER), "--out", str(out)])
    assert out.read_bytes() == (ROOT / "server/tests/fixtures/test-seed.xml").read_bytes()


def test_extra_roles_and_home(tmp_path):
    base, base_roles, _ = mts.build(db())
    c = db()
    nier = [c.execute("select id from master_role where id_label = ?", (lab,)).fetchone()[0]
            for lab in ("role_cc0015_b01a_6551", "role_cc0016_b01a_6563")]
    out = tmp_path / "seed.xml"
    mts.main(["--master", str(MASTER), "--out", str(out), "--extra-roles", f"role_cc0015_b01a_6551,{nier[1]},{base_roles[0]}",
              "--home", "role_cc0017_b01a_6572"])
    k = KVSFile.load(out)
    a2 = c.execute("select id from master_role where id_label = 'role_cc0017_b01a_6572'").fetchone()[0]
    assert roster(k) == base_roles + nier + [a2]  # duplicates dropped; the home added last
    assert k.get_u32("player_home_pc_roleid") == a2
    assert k.get_str("BAS:PlayerID") == "LOCAL00001"


def test_unknown_role_refused():
    with pytest.raises(SystemExit):
        mts.build(db(), ["role_does_not_exist"])
