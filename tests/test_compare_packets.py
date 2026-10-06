"""tools/compare_packets.py, the packet comparison behind every tests/diff verdict (pytest): equal
logs PASS, a difference FAILs, and logs with nothing in them never PASS."""
import os
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOOL = os.path.join(REPO, "tools", "compare_packets.py")

# soa-server --log-packets lines (the format compare_packets.packets() reads), made up
WIRE = """\
2026-01-01 00:00:00 conn 1 open
2026-01-01 00:00:00 conn 1 #1 > NoLoginStart fid=95804837 clear plain=36 method=NoLoginStart args: "3.7.0" dev=2
2026-01-01 00:00:01   < NoLoginStartRes fid=a8dad4e4 clear plain=10 packet=20 data{Time,Player}
2026-01-01 00:00:02 conn 2 #2 > StartBridge fid=d4053e85 clear plain=16 method=StartBridge args:
2026-01-01 00:00:02   < ResultStart fid=850735d4 clear plain=1160 packet=1204 token=02de2c6b97e8a129b0f25c4dbc964acd3a361e4218156e37
2026-01-01 00:00:02 bridge: UUID=aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa deviceType=2 token=x -> session b9399f23fd8ee751be0ef9bc9c8386e3
2026-01-01 00:00:03 conn 2 #4 > Login fid=a01c67ef MARS plain=97 method=Login args: "aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa" "" 0
2026-01-01 00:00:03   < LoginResult fid=2acff1ed AES128 plain=10 packet=20 data{Time,Player,Wallet} status=0
2026-01-01 00:00:04 conn 2 #5 > GetServerTime fid=11111111 MARS plain=8 method=GetServerTime args:
2026-01-01 00:00:04   < GetServerTimeRes fid=22222222 MARS plain=8 packet=16 data{Time}
"""


def run(tmp_path, a, b, *opts):
    pa, pb = tmp_path / "a.log", tmp_path / "b.log"
    pa.write_text(a)
    pb.write_text(b)
    r = subprocess.run([sys.executable, TOOL, str(pa), str(pb)] + list(opts), capture_output=True, text=True)
    return r.returncode, r.stdout


def test_equal_logs_pass(tmp_path):
    # times, cipher, sizes and the UUID differ by nature between two runs: masked
    b = WIRE.replace("2026-01-01", "2026-02-02").replace("plain=97", "plain=98").replace("aaaaaaaa-aaaa", "bbbbbbbb-bbbb")
    rc, out = run(tmp_path, WIRE, b)
    assert rc == 0 and "PASS packets equal" in out


def test_a_different_request_fails(tmp_path):
    rc, out = run(tmp_path, WIRE, WIRE.replace('args: "3.7.0"', 'args: "3.6.0"'))
    assert rc == 1 and "FAIL packets differ" in out
    rc, _ = run(tmp_path, WIRE, WIRE.replace("data{Time,Player,Wallet}", "data{Time,Player}"))  # a reply's keys
    assert rc == 1
    rc, _ = run(tmp_path, WIRE, WIRE.replace("status=0", "status=3"))
    assert rc == 1


def test_empty_logs_never_pass(tmp_path):
    """The negative control: two empty logs are 'equal' but compared nothing."""
    rc, out = run(tmp_path, "", "")
    assert rc == 1 and "FAIL packets differ" in out and "0 requests" in out
    rc, _ = run(tmp_path, "garbage\nnot a packet line\n", "garbage\nnot a packet line\n")  # unreadable logs
    assert rc == 1
    rc, _ = run(tmp_path, WIRE, WIRE, "--min-requests", "10")
    assert rc == 1
    rc, _ = run(tmp_path, WIRE, WIRE, "--min-requests", "3")
    assert rc == 0


def test_transport_neutral_drops_the_wire_only_parts(tmp_path):
    """--transport-neutral: the in-process route's log (no bridge, Login without arguments, dev=?)
    equals the wire's."""
    inproc = "\n".join(ln for ln in WIRE.splitlines() if "Bridge" not in ln and "ResultStart" not in ln and "bridge:" not in ln)
    inproc = inproc.replace('args: "aaaaaaaa-aaaa-aaaa-aaaa-aaaaaaaaaaaa" "" 0', "args: ").replace("dev=2", "dev=?") + "\n"
    assert run(tmp_path, WIRE, inproc)[0] == 1
    assert run(tmp_path, WIRE, inproc, "--transport-neutral")[0] == 0


def test_float_time_sync_compares_the_count(tmp_path):
    lines = WIRE.splitlines()
    moved = lines[:1] + lines[-2:] + lines[1:-2]  # the GetServerTime exchange earlier
    assert run(tmp_path, WIRE, "\n".join(moved) + "\n")[0] == 1
    assert run(tmp_path, WIRE, "\n".join(moved) + "\n", "--float-time-sync")[0] == 0
    assert run(tmp_path, WIRE, "\n".join(lines[:-2]) + "\n", "--float-time-sync")[0] == 1  # one fewer
