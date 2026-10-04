"""tools/server_replay_record.py's reply reader (msgpack): data.Time of a reply, and the replies it skips."""
import os
import sys
import time

import msgpack

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "tools"))
import server_replay_record as rr  # noqa: E402

STAMP = "2026-10-01 03:58:00"


def write(tmp_path, data):
    p = tmp_path / "1-Reply.msgp"
    p.write_bytes(data)
    return str(p)


def test_reply_time_reads_data_time(tmp_path):
    body = msgpack.packb({"data": {"Time": STAMP, "Player": {"id": 1, "name": "Tessa"}}, "status": 0})
    assert rr.reply_time(write(tmp_path, body)) == int(time.mktime(time.strptime(STAMP, "%Y-%m-%d %H:%M:%S")))


def test_the_reply_is_the_first_object(tmp_path):
    body = msgpack.packb({"data": {"Time": STAMP}, "status": 0}) + msgpack.packb([1, 2])
    assert rr.read_reply(body) == {"data": {"Time": STAMP}, "status": 0}
    assert rr.reply_time(write(tmp_path, body)) is not None


def test_integer_keys_bin_and_bad_utf8_decode():
    body = b"\x83" + msgpack.packb(7) + msgpack.packb(b"\x00\xff", use_bin_type=True) \
        + msgpack.packb("k") + b"\xa2\xc3\x28" + msgpack.packb("f") + msgpack.packb(1.5)
    assert rr.read_reply(body) == {7: b"\x00\xff", "k": "�(", "f": 1.5}


def test_replies_without_a_time(tmp_path):
    assert rr.reply_time(write(tmp_path, msgpack.packb({"data": {}, "status": 0}))) is None
    assert rr.reply_time(write(tmp_path, msgpack.packb([1, 2, 3]))) is None
    assert rr.reply_time(write(tmp_path, msgpack.packb({"data": {"Time": STAMP}})[:-4])) is None  # truncated
    assert rr.reply_time(write(tmp_path, b"\xc1")) is None  # never used
    assert rr.reply_time(str(tmp_path / "missing.msgp")) is None
