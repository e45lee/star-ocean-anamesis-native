"""soadrive.proc.free_ports, the one free-port helper (Linux and a Windows program from WSL), and
the bind race it leaves: soa-server's "port taken" line is what Run.start retries on, on both
platforms (proc.addr_in_use)."""
import socket
import subprocess

import pytest

from soadrive import proc


@pytest.mark.parametrize("win", [False, True])
def test_free_ports_are_distinct(win):
    ports = proc.free_ports(5, win)
    assert len(set(ports)) == 5 and all(0 < p < 65536 for p in ports)
    if win:
        assert all(30000 <= p <= 44000 for p in ports)


def test_addr_in_use_reads_both_platforms_messages(tmp_path):
    log = tmp_path / "server.log"
    assert not proc.addr_in_use(str(tmp_path / "missing.log"))
    log.write_text("soa-server: ready\n")
    assert not proc.addr_in_use(str(log))
    for line in ("soa-server: 127.0.0.1:4000: Address already in use",
                 "soa-server: 127.0.0.1:4000: Only one usage of each socket address (protocol/network address/port) is normally permitted."):
        log.write_text(line + "\n")
        assert proc.addr_in_use(str(log))


def test_soa_server_on_a_taken_port_is_recognized(repo, tmp_path):
    server = repo / "build" / "server" / "soa-server"
    if not server.exists():
        pytest.skip("soa-server not built")
    with socket.socket() as s:
        s.bind(("127.0.0.1", 0))
        s.listen()
        port = s.getsockname()[1]
        log = tmp_path / "server.log"
        with open(log, "w") as f:
            r = subprocess.run(["timeout", "-k", "5", "60", str(server), "--listen", "127.0.0.1:%d" % port, "--http", "127.0.0.1:0",
                                "--data", str(tmp_path / "data")], stdout=f, stderr=subprocess.STDOUT)
    assert r.returncode != 0
    assert proc.addr_in_use(str(log)), log.read_text()[-400:]
