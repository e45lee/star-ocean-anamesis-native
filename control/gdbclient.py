#!/usr/bin/env -S sh -c 'exec "${0%/*}/../tools/py" "$0" "$@"'
"""A small client for the runtime's GDB stub (`--gdb HOST:PORT` on soa / soa-emu / soa-viewer;
runtime/README.md "Debugging the guest with gdb"), for tests and scripts that read guest state at a
milestone without a gdb process.

Library:
    from gdbclient import GdbClient
    g = GdbClient("127.0.0.1", 1234)          # connects and stops the guest (all threads)
    base = g.lib_base()                         # load address of the game library (monitor base)
    g.set_break(base + vaddr)                   # or g.break_symbol("_ZN5CHome11GetAdjutant...")
    stop = g.cont(timeout=60)                   # {"sig": 5, "tid": ..., "swbreak": True}
    regs = g.regs()                             # {"x0": ..., "sp": ..., "pc": ..., "v0": int(128-bit), ...}
    data = g.read(regs["x0"], 0x40)
    g.step(); g.detach()                        # breakpoints removed, the client keeps running
    g.natives("Find_")                          # the guest functions now native: [{"addr", "symbol", "demangled", "native", "host"}]
A breakpoint on a native (a guest function replaced by C++) stops before the native runs, the
guest's arguments in the registers; a step runs all of it (runtime/README.md).

CLI (one shot; exits after detaching):
    control/gdbclient.py HOST:PORT [--break SYMBOL|0xADDR] [--timeout S] [--regs] [--read REG_OR_ADDR:LEN] [--monitor CMD]
e.g. control/gdbclient.py :1234 --break _ZN5CHome11GetAdjutant... --regs --read x0:0x40
     control/gdbclient.py [::1]:1234 --monitor "natives ASON"
HOST may be an IPv6 address in brackets. SYMBOL is an ELF symbol of the game library
(work/libSOA-3.7.0.so; --lib for another), resolved at the load base the stub reports.
"""
import argparse
import os
import socket
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REG_NAMES = [f"x{i}" for i in range(31)] + ["sp", "pc", "cpsr"] + [f"v{i}" for i in range(32)] + ["fpsr", "fpcr"]
REG_SIZES = [8] * 33 + [4] + [16] * 32 + [4, 4]


def checksum(data: bytes) -> int:
    return sum(data) & 0xFF


def escape(data: bytes) -> bytes:
    out = bytearray()
    for b in data:
        if b in b"$#}*":
            out += bytes([0x7D, b ^ 0x20])
        else:
            out.append(b)
    return bytes(out)


def frame(data: bytes) -> bytes:
    e = escape(data)
    return b"$" + e + b"#" + b"%02x" % checksum(e)


def unescape(data: bytes) -> bytes:
    out, i = bytearray(), 0
    while i < len(data):
        b = data[i]
        if b == 0x7D and i + 1 < len(data):
            out.append(data[i + 1] ^ 0x20)
            i += 2
        elif b == 0x2A and out and i + 1 < len(data):  # run-length: "c*n" = n - 29 more copies
            out += bytes([out[-1]]) * (data[i + 1] - 29)
            i += 2
        else:
            out.append(b)
            i += 1
    return bytes(out)


def parse_packets(buf: bytes):
    """(packets, rest): complete packets' data from a byte stream (acks skipped)."""
    pkts = []
    while True:
        buf = buf.lstrip(b"+-")
        if not buf:
            return pkts, buf
        if buf[:1] != b"$":
            j = buf.find(b"$")
            buf = b"" if j < 0 else buf[j:]
            continue
        h = buf.find(b"#")
        if h < 0 or len(buf) < h + 3:
            return pkts, buf
        raw, cs = buf[1:h], buf[h + 1:h + 3]
        buf = buf[h + 3:]
        if int(cs, 16) != checksum(raw):
            raise IOError("gdbclient: bad checksum from the stub")
        pkts.append(unescape(raw))


def le(hexstr: str) -> int:
    return int.from_bytes(bytes.fromhex(hexstr), "little")


def parse_stop(r: str):
    """'T05thread:1f2;swbreak:;' -> {'sig': 5, 'tid': 0x1f2, 'swbreak': True}."""
    if not r or r[0] not in "TS":
        raise IOError(f"gdbclient: not a stop reply: {r!r}")
    st = {"sig": int(r[1:3], 16), "tid": 0, "swbreak": False}
    for kv in r[3:].split(";"):
        k, _, v = kv.partition(":")
        if k == "thread":
            st["tid"] = int(v, 16)
        elif k == "swbreak":
            st["swbreak"] = True
    return st


def split_addr(addr):
    """'HOST:PORT', '[V6]:PORT' or ':PORT' -> (host, port); the host defaults to 127.0.0.1."""
    host, _, port = addr.rpartition(":")
    if host.startswith("[") and host.endswith("]"):
        host = host[1:-1]
    return host or "127.0.0.1", int(port)


class GdbClient:
    def __init__(self, host="127.0.0.1", port=1234, timeout=30.0, stop=True):
        host = (host or "127.0.0.1").strip("[]")  # an IPv6 address with or without its brackets
        self.sock = socket.create_connection((host, port), timeout=timeout)
        self.sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        self.buf = b""
        self.noack = False
        self.breaks = set()
        self.stop_info = None
        self.cmd("qSupported:swbreak+;vContSupported+")
        if self.cmd("QStartNoAckMode") == "OK":
            self.noack = True
        if stop:
            self.stop_info = parse_stop(self.cmd("?"))

    # ---- transport
    def _send(self, data: bytes):
        self.sock.sendall(frame(data))

    def _recv(self, timeout=None):
        if timeout is not None:
            self.sock.settimeout(timeout)
        while True:
            pkts, self.buf = parse_packets(self.buf)
            if pkts:
                p = pkts[0]
                # keep any later packet (rare) for the next call
                self.buf = b"".join(frame(q) for q in pkts[1:]) + self.buf
                if not self.noack:
                    self.sock.sendall(b"+")
                return p.decode("latin-1")
            chunk = self.sock.recv(65536)
            if not chunk:
                raise IOError("gdbclient: the stub closed the connection")
            self.buf += chunk

    def cmd(self, packet, timeout=None):
        self._send(packet.encode("latin-1") if isinstance(packet, str) else packet)
        r = self._recv(timeout)
        while r.startswith("O") and r != "OK" and not r.startswith("OK"):  # console output (monitor)
            r = self._recv(timeout)
        return r

    # ---- state
    def threads(self):
        r = self.cmd("qfThreadInfo")
        return [int(t, 16) for t in r[1:].split(",") if t] if r.startswith("m") else []

    def select(self, tid):
        if tid:
            self.cmd("Hg%x" % tid)

    def regs(self, tid=None):
        self.select(tid or (self.stop_info or {}).get("tid"))
        r = self.cmd("g")
        if r.startswith("E"):
            raise IOError(f"gdbclient: g -> {r}")
        out, off = {}, 0
        for name, size in zip(REG_NAMES, REG_SIZES):
            out[name] = le(r[off:off + 2 * size])
            off += 2 * size
        return out

    def reg(self, name, tid=None):
        self.select(tid or (self.stop_info or {}).get("tid"))
        r = self.cmd("p%x" % REG_NAMES.index(name))
        if r.startswith("E"):
            raise IOError(f"gdbclient: p {name} -> {r}")
        return le(r)

    def set_reg(self, name, value, tid=None):
        self.select(tid or (self.stop_info or {}).get("tid"))
        n = REG_NAMES.index(name)
        r = self.cmd("P%x=%s" % (n, value.to_bytes(REG_SIZES[n], "little").hex()))
        if r != "OK":
            raise IOError(f"gdbclient: P {name} -> {r}")

    def read(self, addr, n):
        out = b""
        while len(out) < n:
            k = min(0x800, n - len(out))
            r = self.cmd("m%x,%x" % (addr + len(out), k))
            if r.startswith("E"):
                raise IOError(f"gdbclient: can't read {addr + len(out):#x}: {r}")
            out += bytes.fromhex(r)
        return out

    def read_u64(self, addr):
        return int.from_bytes(self.read(addr, 8), "little")

    def write(self, addr, data: bytes):
        r = self.cmd(b"X%x,%x:" % (addr, len(data)) + data)
        if r != "OK":
            raise IOError(f"gdbclient: can't write {addr:#x}: {r}")

    def monitor(self, command):
        self._send(("qRcmd," + command.encode().hex()).encode())
        text = ""
        while True:
            r = self._recv()
            if r.startswith("O") and r != "OK":
                text += bytes.fromhex(r[1:]).decode("utf-8", "replace")
            else:
                return text

    def libs(self):
        """[(base, path)] of the loaded images."""
        out = []
        for line in self.monitor("base").splitlines():
            a, _, p = line.partition(" ")
            if a.startswith("0x"):
                out.append((int(a, 16), p))
        return out

    def natives(self, text=""):
        """The guest functions now native (`monitor natives [TEXT]`): [{"addr", "symbol", "demangled",
        "native" (the C++), "host" (its host address)}]."""
        out = []
        for line in self.monitor(("natives " + text).strip()).splitlines():
            f = line.split("\t")
            if len(f) == 5 and f[0].startswith("0x"):
                out.append({"addr": int(f[0], 16), "symbol": f[1], "demangled": f[2], "native": f[3], "host": int(f[4], 16)})
        return out

    def lib_base(self, name="libSOA"):
        for base, path in self.libs():
            if name in os.path.basename(path):
                return base
        raise IOError(f"gdbclient: no loaded image named like {name!r}")

    # ---- breakpoints and execution
    def set_break(self, addr):
        r = self.cmd("Z0,%x,4" % addr)
        if r != "OK":
            raise IOError(f"gdbclient: can't set a breakpoint at {addr:#x}: {r}")
        self.breaks.add(addr)

    def del_break(self, addr):
        self.cmd("z0,%x,4" % addr)
        self.breaks.discard(addr)

    def break_symbol(self, symbol, lib=None):
        addr = self.lib_base() + symbol_vaddr(symbol, lib)
        self.set_break(addr)
        return addr

    def step(self, tid=None):
        tid = tid or self.stop_info["tid"]
        self.stop_info = parse_stop(self.cmd("vCont;s:%x" % tid))
        return self.stop_info

    def cont(self, timeout=None):
        """Resume every thread until the next stop (stepping over a breakpoint at the current pc first)."""
        if self.stop_info and self.breaks:
            pc = self.reg("pc", self.stop_info["tid"])
            if pc in self.breaks:
                self.del_break(pc)
                self.step()
                self.set_break(pc)
        self._send(b"vCont;c")
        try:
            r = self._recv(timeout)
        except socket.timeout:
            self.interrupt()
            raise TimeoutError("gdbclient: no stop within the timeout (interrupted)")
        self.stop_info = parse_stop(r)
        return self.stop_info

    def interrupt(self):
        self.sock.sendall(b"\x03")
        self.stop_info = parse_stop(self._recv(30))
        return self.stop_info

    def detach(self):
        try:
            self.cmd("D", timeout=10)
        finally:
            self.sock.close()


def symbol_vaddr(symbol, lib=None):
    """The ELF vaddr of a symbol (mangled name) of the game library."""
    from elftools.elf.elffile import ELFFile
    path = lib or os.path.join(REPO, "work", "libSOA-3.7.0.so")
    with open(path, "rb") as f:
        elf = ELFFile(f)
        for sec in (".dynsym", ".symtab"):
            s = elf.get_section_by_name(sec)
            if s:
                for sym in s.get_symbol_by_name(symbol) or []:
                    if sym["st_value"]:
                        return sym["st_value"]
    raise KeyError(f"{symbol} not in {path}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("addr", help="HOST:PORT, [IPV6]:PORT or :PORT of --gdb")
    ap.add_argument("--break", dest="brk", help="a symbol (mangled) or 0xADDR (absolute) to run to")
    ap.add_argument("--lib", help="the ELF file for --break symbols (default work/libSOA-3.7.0.so)")
    ap.add_argument("--timeout", type=float, default=120)
    ap.add_argument("--regs", action="store_true")
    ap.add_argument("--read", action="append", default=[], help="REG_OR_ADDR:LEN, hex dump")
    ap.add_argument("--monitor")
    a = ap.parse_args()
    g = GdbClient(*split_addr(a.addr))
    try:
        print(f"stopped: {g.stop_info}")
        if a.monitor:
            print(g.monitor(a.monitor), end="")
        if a.brk:
            addr = int(a.brk, 16) if a.brk.startswith("0x") else g.break_symbol(a.brk, a.lib)
            if a.brk.startswith("0x"):
                g.set_break(addr)
            st = g.cont(timeout=a.timeout)
            print(f"hit {addr:#x}: {st}")
        regs = g.regs() if a.regs or a.read else {}
        if a.regs:
            for k in REG_NAMES[:34]:
                print(f"{k:5} {regs[k]:#018x}")
        for spec in a.read:
            what, _, n = spec.partition(":")
            addr = regs[what] if what in regs else int(what, 16)
            data = g.read(addr, int(n, 0))
            for off in range(0, len(data), 16):
                print(f"{addr + off:#x}: {data[off:off + 16].hex(' ')}")
    finally:
        g.detach()
        print("detached")


if __name__ == "__main__":
    sys.exit(main())
