#!/usr/bin/env python3
"""Records a replay corpus (server/tests/replay/README.md) from a soa-server packet log.

    tools/server_replay_record.py PACKETS_DIR CORPUS_DIR --options "ARGS" [--tz ZONE] [--note TEXT]
    tools/server_replay_record.py --sweep CORPUS_DIR --options "ARGS" [--server BIN]

PACKETS_DIR is a `soa-server --log-packets DIR` directory (packets.log plus each request's plaintext
body <n>-<Api>.bin and each reply <n>-<Reply>.msgp). CORPUS_DIR gets:
  requests.txt  one request per line: `wire <n> <t> <Api> <plaintext hex>` (decoded again by the
                replay with net::decode_request), preceded by a `#` line with the logged method and
                arguments; <t> is the server clock of the request (Unix seconds): the reply's
                data.Time when it has one, else the packet log's stamp plus the clock offset seen on
                the nearest reply;
  options       the server options of the recording, one argument per line (repo-relative paths),
                which tools/server_replay_diff.py passes to soa-server --replay;
  the header of requests.txt names the time zone the recording ran in (the replay runs in it).

The bridge handshake (StartBridge, UpdateSession) is the wire layer's own and isn't recorded.
--sweep writes the generated `api-sweep` corpus instead: every method `soa-server --list-apis` says
the library answers, once, without arguments, at synthetic times that cross the 04:00 reset.

Refuses (exit 1) a packet log that contains a player id other than the sanitized LOCAL00001
(data/saves/README.md): a 10-character upper-case search id anywhere in the requests, or the
BAS:PlayerID of an untracked personal save (samples/, work/) found on this machine.
In-process logs (soa --log-packets) carry no request bodies and aren't supported (yet).
"""
import argparse
import os
import re
import shlex
import subprocess
import sys
import time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SESSION_APIS = {"StartBridge", "UpdateSession"}
ALLOWED_IDS = {"LOCAL00001", "AAAAAAAAAA"}  # the server's sanitized id; data/saves/client's placeholder
REQ_RE = re.compile(r"^(\d{4}-\d\d-\d\d \d\d:\d\d:\d\d) conn \d+ #(\d+) > (\S+) fid=([0-9a-f]{8}) (\S+) plain=\d+ method=(\S+) args: ?(.*)$")


# ---- a minimal MessagePack reader (the replies' data.Time) ------------------------------------
def mp_read(b, p=0):
    t = b[p]
    p += 1
    if t <= 0x7f:
        return t, p
    if t >= 0xe0:
        return t - 0x100, p
    if 0x80 <= t <= 0x8f or t in (0xde, 0xdf):
        n, p = (t & 0x0f, p) if t <= 0x8f else (int.from_bytes(b[p:p + (2 if t == 0xde else 4)], "big"), p + (2 if t == 0xde else 4))
        m = {}
        for _ in range(n):
            k, p = mp_read(b, p)
            v, p = mp_read(b, p)
            m[k] = v
        return m, p
    if 0x90 <= t <= 0x9f or t in (0xdc, 0xdd):
        n, p = (t & 0x0f, p) if t <= 0x9f else (int.from_bytes(b[p:p + (2 if t == 0xdc else 4)], "big"), p + (2 if t == 0xdc else 4))
        a = []
        for _ in range(n):
            v, p = mp_read(b, p)
            a.append(v)
        return a, p
    if 0xa0 <= t <= 0xbf or t in (0xd9, 0xda, 0xdb):
        if t <= 0xbf:
            n = t & 0x1f
        else:
            w = {0xd9: 1, 0xda: 2, 0xdb: 4}[t]
            n, p = int.from_bytes(b[p:p + w], "big"), p + w
        return b[p:p + n].decode("utf-8", "replace"), p + n
    if t in (0xc4, 0xc5, 0xc6):
        w = {0xc4: 1, 0xc5: 2, 0xc6: 4}[t]
        n, p = int.from_bytes(b[p:p + w], "big"), p + w
        return bytes(b[p:p + n]), p + n
    if t == 0xc0:
        return None, p
    if t in (0xc2, 0xc3):
        return t == 0xc3, p
    if t in (0xcc, 0xcd, 0xce, 0xcf):
        w = {0xcc: 1, 0xcd: 2, 0xce: 4, 0xcf: 8}[t]
        return int.from_bytes(b[p:p + w], "big"), p + w
    if t in (0xd0, 0xd1, 0xd2, 0xd3):
        w = {0xd0: 1, 0xd1: 2, 0xd2: 4, 0xd3: 8}[t]
        return int.from_bytes(b[p:p + w], "big", signed=True), p + w
    if t in (0xca, 0xcb):
        import struct
        return struct.unpack(">f" if t == 0xca else ">d", b[p:p + (4 if t == 0xca else 8)])[0], p + (4 if t == 0xca else 8)
    raise ValueError("msgpack type %02x" % t)


def reply_time(path):
    try:
        v, _ = mp_read(open(path, "rb").read())
        s = v.get("data", {}).get("Time") if isinstance(v, dict) else None
        return int(time.mktime(time.strptime(s, "%Y-%m-%d %H:%M:%S"))) if isinstance(s, str) else None
    except (ValueError, IndexError, KeyError, AttributeError, OSError):
        return None


# ---- the sanitize rule ---------------------------------------------------------------------------
def personal_ids():
    """The BAS:PlayerID of untracked personal saves on this machine (never printed)."""
    ids = set()
    sys.path.insert(0, REPO)
    try:
        from soa_save.kvs import KVSFile  # noqa: E402
    except Exception:
        # soa_save needs pycryptodome: ask the repo's .venv (the ids stay in this pipe)
        py = os.path.join(REPO, ".venv/bin/python")
        if os.path.exists(py) and os.path.realpath(sys.prefix) != os.path.realpath(os.path.join(REPO, ".venv")):
            r = subprocess.run([py, os.path.abspath(__file__), "--personal-ids"], capture_output=True, text=True)
            return set(r.stdout.split()) if r.returncode == 0 else ids
        return ids
    roots = {REPO}
    work = os.path.join(REPO, "work")
    if os.path.islink(work):  # a worktree: its work/ links into the main checkout
        roots.add(os.path.dirname(os.path.realpath(work)))
    for root in roots:
        for rel in ("samples/Game.xml", "samples/Game_all_characters.xml", "work/Game-3.7.0.xml"):
            p = os.path.join(root, rel)
            if not os.path.exists(p):
                continue
            try:
                for k, v in KVSFile.load(p).entries.items():
                    if "PlayerID" in k:
                        s = v.rstrip(b"\0").decode("utf-8", "ignore").strip()
                        if s and s not in ALLOWED_IDS:
                            ids.add(s)
            except Exception:
                pass
    return ids


def check_sanitized(blobs):
    """blobs: (where, bytes). Exits 1 naming the file (not the id) when one holds a real player id."""
    personal = personal_ids()
    bad = []
    for where, b in blobs:
        text = b.decode("latin-1")
        for m in re.finditer(r"(?<![A-Za-z0-9])[A-Z0-9]{10}(?![A-Za-z0-9])", text):
            tok = m.group(0)
            if tok not in ALLOWED_IDS and re.search(r"[A-Z]", tok) and re.search(r"[0-9]", tok):
                bad.append(where)
        for pid in personal:
            if pid in text:
                bad.append(where)
    if bad:
        sys.exit("server_replay_record: refused: %s holds a player id other than LOCAL00001 "
                 "(the sanitize rule, data/saves/README.md)" % ", ".join(sorted(set(bad))))


# ---- recording -----------------------------------------------------------------------------------
def record(pkts, corpus, options, tz, note):
    log = os.path.join(pkts, "packets.log")
    lines = open(log, encoding="utf-8", errors="replace").read().splitlines()
    reqs = []
    for ln in lines:
        m = REQ_RE.match(ln)
        if not m:
            continue
        stamp, seq, api, fid, alg, method, args = m.groups()
        if api in SESSION_APIS:
            continue
        if alg == "inproc":
            sys.exit("server_replay_record: %s is an in-process log (soa --log-packets): it has no request bodies" % log)
        binp = os.path.join(pkts, "%s-%s.bin" % (seq, api))
        if not os.path.exists(binp):
            continue  # undecodable (logged, refused by the wire layer)
        rt = None
        for f in sorted(os.listdir(pkts)):
            if f.startswith(seq + "-") and f.endswith(".msgp") and "battle_log" not in f and not f.endswith("-sent.msgp"):
                rt = reply_time(os.path.join(pkts, f))
                if rt:
                    break
        st = int(time.mktime(time.strptime(stamp, "%Y-%m-%d %H:%M:%S")))
        reqs.append(dict(seq=seq, api=api, method=method, args=args, stamp=stamp, wall=st, t=rt, body=open(binp, "rb").read()))
    if not reqs:
        sys.exit("server_replay_record: no requests in %s" % log)
    check_sanitized([("%s-%s.bin" % (r["seq"], r["api"]), r["body"]) for r in reqs] + [("packets.log", "\n".join(r["args"] for r in reqs).encode())])
    # requests without a reply time: the packet log's stamp + the offset of the nearest reply
    timed = [i for i, r in enumerate(reqs) if r["t"] is not None]
    if not timed:
        sys.exit("server_replay_record: no reply carries data.Time; can't place the requests on the server clock")
    for i, r in enumerate(reqs):
        if r["t"] is None:
            j = min(timed, key=lambda k: (abs(k - i), k))
            r["t"] = r["wall"] + (reqs[j]["t"] - reqs[j]["wall"])
    os.makedirs(corpus, exist_ok=True)
    with open(os.path.join(corpus, "requests.txt"), "w") as f:
        f.write("# soa-server replay corpus (server/tests/replay/README.md), recorded by tools/server_replay_record.py\n")
        if note:
            f.write("# %s\n" % note)
        f.write("# tz: %s\n" % tz)
        for r in reqs:
            f.write("# %s %s: %s\n" % (r["stamp"], r["method"], r["args"]))
            f.write("wire %s %d %s %s\n" % (r["seq"], r["t"], r["api"], r["body"].hex()))
    write_options(corpus, options)
    print("%s: %d requests" % (corpus, len(reqs)))


def write_options(corpus, options):
    with open(os.path.join(corpus, "options"), "w") as f:
        for a in shlex.split(options):
            f.write(a + "\n")


def sweep(corpus, options, server, tz):
    out = subprocess.run([server, "--list-apis"], capture_output=True, text=True, check=True).stdout
    methods = []
    for ln in out.splitlines():
        m, fid, by = ln.split("\t")
        if by != "-":
            methods.append((m, fid))
    # Login first (the player's day starts), then every method in name order; 03:58:00 + 5 s per
    # request crosses the 04:00 reset (docs/server-rules.md "Clock") about a third of the way in.
    order = [x for x in methods if x[0] == "Login"] + [x for x in methods if x[0] != "Login"]
    t0 = int(time.mktime(time.strptime("2026-10-01 03:58:00", "%Y-%m-%d %H:%M:%S")))
    os.makedirs(corpus, exist_ok=True)
    with open(os.path.join(corpus, "requests.txt"), "w") as f:
        f.write("# soa-server replay corpus (server/tests/replay/README.md): api-sweep, generated by\n")
        f.write("# tools/server_replay_record.py --sweep: every method the library answers, once, no arguments.\n")
        f.write("# tz: %s\n" % tz)
        for i, (m, fid) in enumerate(order):
            fid = fid if fid != "-" else "%08x" % (0xf0000000 + i)  # no wire FunctionID: a synthetic one
            f.write("req %d %d %s %s - - - -\n" % (i + 1, t0 + 5 * i, m, fid))
    write_options(corpus, options)
    print("%s: %d requests" % (corpus, len(order)))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("packets", nargs="?")
    ap.add_argument("corpus")
    ap.add_argument("--options", required=True, help="the recording's server options (one shell-quoted string)")
    ap.add_argument("--tz", default=os.environ.get("TZ") or "America/Toronto", help="the recording's time zone")
    ap.add_argument("--note", default="", help="a line for the header (where the recording came from)")
    ap.add_argument("--sweep", action="store_true")
    ap.add_argument("--server", default=os.path.join(REPO, "build/server/soa-server"))
    if sys.argv[1:] == ["--personal-ids"]:  # (internal: personal_ids() through the .venv)
        sys.stdout.write("\n".join(personal_ids()))
        return
    a = ap.parse_args()
    os.environ["TZ"] = a.tz
    time.tzset()
    if a.sweep:
        sweep(a.corpus if a.packets is None else a.packets, a.options, a.server, a.tz)
    else:
        if not a.packets:
            ap.error("PACKETS_DIR missing")
        record(a.packets, a.corpus, a.options, a.tz, a.note)


if __name__ == "__main__":
    main()
