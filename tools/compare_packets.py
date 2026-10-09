#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Compare two soa-server packet logs (soa-server --log-packets DIR -> DIR/packets.log): the
requests two clients sent for the same scripted flow, e.g. soa --server (the port on the 3.7.0
client) and soa-emu (the unmodified 3.7.0 client), each against a fresh soa-server with the same
seed (--seed-rng 1). port/scripts/rebase_server_diff.sh runs both and calls this.

    tools/compare_packets.py A/packets.log B/packets.log [--client-logs A.log B.log] [-v]

Compared, in order:
  * every request: method, FunctionID, arguments;
  * every reply: its name, the top-level keys of its data map, its status;
  * the bridge handshake (deviceType).
Masked (they differ by nature between two runs): times and connection / request numbers, the
cipher and the packet sizes (the client picks a cipher per request), device UUIDs (a fresh KVS
makes a new one), session keys and bridge tokens. With --client-logs the clients' HTTP GETs
(I/http: GET <url>, platform370's log line) are compared too, as a multiset (the downloader's
threads may reorder them).
Exits 0 and prints "PASS packets equal" when everything compared is equal and each log has at
least --min-requests requests (default 1); otherwise prints the differences (unified diff of the
normalized sequences) and exits 1. tests/test_compare_packets.py has its cases.

    --mask-battle-log    MissionEnd & co.'s battle_log[N]: the length masked (it grows with the
                         battle's length, which the party's AI and the frame timing decide; the
                         battle's effect is compared in the server state instead)
    --transport-neutral  for a log of the port's in-process route (soa --log-packets: the
                         FakeApiCaller route, no wire) against a wire log: only what both routes
                         carry. Dropped: the bridge handshake (StartBridge / ResultStart, the bridge
                         POST, UpdateSession / ResultUpdateSession, session lines), the GetPlayerRes
                         soa-server sends after a LoginResult to end the login request (the
                         in-process route applies the Login answer through OnGetPlayerRes itself),
                         Login / SimpleLogin's arguments (the wire's UUID, push token and advertising
                         id; IApiCaller::Login takes none) and CreatePlayer's but the name (the
                         route captures the name only). Masked: the DeviceType (dev=N; the
                         FakeApiCaller methods don't take it: dev=?). tests/diff/README.md.
    --collapse-title-repeat
                         a NoLoginStart sent again right after the first one was answered (the
                         same arguments, nothing in between) counts once: the title sometimes
                         sends it twice within a second (seen on soa-emu in 1 run of 2;
                         tests/diff/README.md); the first exchange is kept
    --float-time-sync    GetServerTime exchanges are compared by count, not by position: the client
                         asks for the time when a timer and a screen change meet, so under load a
                         slower client sends it a request earlier or later (seen in the tutorial's
                         mission menu on soa-emu at 20 clients, 2026-10-03); it changes no state
"""
import argparse
import collections
import difflib
import re
import sys

UUID = re.compile(r"\b[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}\b")
HEX48 = re.compile(r"\b[0-9a-f]{48}\b")
HEX32 = re.compile(r"\b[0-9a-f]{32}\b")


def mask(s):
    s = UUID.sub("<uuid>", s)
    s = HEX48.sub("<token>", s)
    s = HEX32.sub("<session>", s)
    return s


def packets(path):
    out = []
    for line in open(path, errors="replace"):
        line = line.rstrip("\n")
        m = re.search(r" > (\w+) fid=(\w+) \S+ plain=\d+ method=(\w+) args: ?(.*)$", line)
        if m:
            out.append("> %s fid=%s args: %s" % (m.group(1), m.group(2), mask(m.group(4).strip())))
            continue
        m = re.search(r" > (\w+) fid=(\w+)", line)
        if m:  # a request whose body didn't decode
            out.append("> %s fid=%s (undecoded)" % (m.group(1), m.group(2)))
            continue
        m = re.search(r"^\S+ \S+ +< (\w+) fid=(\w+)(.*)$", line)
        if m:
            rest = m.group(3)
            keys = re.search(r"data\{([^}]*)\}", rest)
            status = re.search(r"status=(-?\d+)", rest)
            out.append("< %s%s%s" % (m.group(1), " data{%s}" % keys.group(1) if keys else "",
                                     " status=%s" % status.group(1) if status else ""))
            continue
        m = re.search(r"bridge: UUID=\S+ deviceType=(\d+)", line)
        if m:
            out.append("bridge deviceType=%s" % m.group(1))
            continue
        m = re.search(r" > session\b", line)
        if m:
            out.append("> session")
    return out


WIRE_ONLY = re.compile(r"^(bridge deviceType=|> session$|> (StartBridge|UpdateSession) |< (ResultStart|ResultUpdateSession)\b)")


def neutral(seq):
    out = []
    for x in seq:
        if WIRE_ONLY.search(x):
            continue
        if x.startswith("< GetPlayerRes") and out and out[-1].startswith("< LoginResult"):
            continue  # soa-server's second reply to a Login
        m = re.match(r"> (Login|SimpleLogin) (fid=\S+) args: ", x)
        if m:
            x = "> %s %s args: <wire only>" % (m.group(1), m.group(2))
        m = re.match(r"> CreatePlayer (fid=\S+) args: (.*)$", x)
        if m:  # the name only: the UUID, DeviceType and the last field are the wire's
            names = [q for q in re.findall(r'"([^"]*)"', m.group(2)) if q and q != "<uuid>"]
            x = "> CreatePlayer %s args: %s <wire only>" % (m.group(1), " ".join('"%s"' % q for q in names))
        out.append(re.sub(r"\bdev=(\d+|\?)", "dev=<dev>", x))
    return out


def collapse_title_repeat(seq):
    out = []
    i = 0
    while i < len(seq):
        x = seq[i]
        if (x.startswith("> NoLoginStart ") and len(out) >= 2 and out[-2] == x and out[-1].startswith("< ")):
            i += 1
            if i < len(seq) and seq[i].startswith("< NoLoginStartRes"):
                i += 1
            continue
        out.append(x)
        i += 1
    return out


def float_time_sync(seq):
    """(the sequence without GetServerTime requests and their replies, how many there were)"""
    out, n, skip = [], 0, False
    for x in seq:
        if x.startswith("> GetServerTime "):
            n, skip = n + 1, True
            continue
        if skip and x.startswith("< GetServerTimeRes"):
            skip = False
            continue
        skip = False
        out.append(x)
    return out, n


def mask_battle_log(seq):
    return [re.sub(r"\bbattle_log\[\d+\]", "battle_log[<n>]", x) for x in seq]


def http_gets(path):
    c = collections.Counter()
    for line in open(path, errors="replace"):
        m = re.search(r"I/http: GET (\S+)", line)
        if m:
            c[m.group(1)] += 1
    return c


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("a")
    ap.add_argument("b")
    ap.add_argument("--client-logs", nargs=2, metavar=("A_LOG", "B_LOG"))
    ap.add_argument("--labels", nargs=2, default=("A", "B"))
    ap.add_argument("-v", action="store_true", help="print the normalized sequences")
    ap.add_argument("--transport-neutral", action="store_true", help="compare only what the in-process route and the wire both carry")
    ap.add_argument("--mask-battle-log", action="store_true", help="mask the battle log's length")
    ap.add_argument("--collapse-title-repeat", action="store_true", help="a repeated NoLoginStart counts once")
    ap.add_argument("--float-time-sync", action="store_true", help="GetServerTime compared by count, not position")
    ap.add_argument("--min-requests", type=int, default=1, metavar="N",
                    help="FAIL when either log has fewer than N requests (default 1: two empty logs compare nothing)")
    o = ap.parse_args()
    la, lb = o.labels
    pa, pb = packets(o.a), packets(o.b)
    if o.transport_neutral:
        pa, pb = neutral(pa), neutral(pb)
    if o.mask_battle_log:
        pa, pb = mask_battle_log(pa), mask_battle_log(pb)
    if o.collapse_title_repeat:
        pa, pb = collapse_title_repeat(pa), collapse_title_repeat(pb)
    ok = True
    if o.float_time_sync:
        (pa, ta), (pb, tb) = float_time_sync(pa), float_time_sync(pb)
        if ta != tb:
            ok = False
            print("FAIL  GetServerTime count differs (%s: %d, %s: %d)" % (la, ta, lb, tb))
        else:
            print("ok    %d GetServerTime exchanges on each side (compared by count)" % ta)
    if o.v:
        for x in pa:
            print("%s  %s" % (la, x))
        for x in pb:
            print("%s  %s" % (lb, x))
    nreq = sum(1 for x in pa if x.startswith("> "))
    for lab, path, seq in ((la, o.a, pa), (lb, o.b, pb)):
        n = sum(1 for x in seq if x.startswith("> "))
        if n < o.min_requests:
            # two empty (or truncated, or unparsable) logs are "equal": that compares nothing
            ok = False
            print("FAIL  %s: %d requests in %s (at least %d expected: a run that sent nothing, or a log this "
                  "tool can't read)" % (lab, n, path, o.min_requests))
    if pa != pb:
        ok = False
        print("FAIL  packet sequences differ (%s: %d entries, %s: %d)" % (la, len(pa), lb, len(pb)))
        sys.stdout.writelines(x + "\n" for x in difflib.unified_diff(pa, pb, la, lb, lineterm="", n=2))
    else:
        print("ok    %d entries equal (%d requests): %s" % (len(pa), nreq, " ".join(x.split()[1] for x in pa if x.startswith("> "))))
    if o.client_logs:
        ga, gb = http_gets(o.client_logs[0]), http_gets(o.client_logs[1])
        if ga != gb:
            ok = False
            print("FAIL  HTTP GETs differ (%s: %d, %s: %d)" % (la, sum(ga.values()), lb, sum(gb.values())))
            for u in sorted(set(ga) | set(gb)):
                if ga[u] != gb[u]:
                    print("      %s: %s %d, %s %d" % (u, la, ga[u], lb, gb[u]))
        else:
            print("ok    %d HTTP GETs equal (%d distinct URLs)" % (sum(ga.values()), len(ga)))
    print("PASS packets equal" if ok else "FAIL packets differ")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
