"""tools/compare_tutorial.py masks the server state's times with soadrive.state's list (code review
T5: its copy lacked `_until$|^expire`, so expiry columns came out as differences)."""
import sqlite3

import compare_tutorial


def db(path, until, expire, gold):
    c = sqlite3.connect(path)
    c.execute("create table buff (id integer, effect_until integer, expire_at integer, expire integer, gold integer)")
    c.execute("insert into buff values (1, ?, ?, ?, ?)", (until, expire, expire, gold))
    c.commit()
    c.close()
    return str(path)


def test_expiry_columns_are_masked(tmp_path):
    a = compare_tutorial.state_rows(db(tmp_path / "a.sqlite3", 100, 200, 5))
    b = compare_tutorial.state_rows(db(tmp_path / "b.sqlite3", 160, 260, 5))
    assert a == b
    c = compare_tutorial.state_rows(db(tmp_path / "c.sqlite3", 100, 200, 6))
    assert a != c  # a real column still counts
