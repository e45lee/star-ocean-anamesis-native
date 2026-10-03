"""Prepared server states: a shard starts from the state a full flow reaches at some point, instead of
playing up to it. The state is made by the server itself (soa-server --replay of a recorded corpus
of server/tests/replay/, cut after one of its requests), so it is exactly what the server's own
rules produce for those requests; every target then starts from a copy of it (soa-server --data,
or soa --db for the in-process route), with the server's side files next to it (side_files: e.g.
--campaign-seed's server_campaign.txt), which the targets copy into the server's data dir.
No client state is prepared: the phone is the shared one, as
in every flow, and the client learns where it is from the server (Login / GetPlayer).
"""
import os
import shutil
import shlex
import sqlite3
import subprocess
import threading

from .proc import REPO

_lock = threading.Lock()


def corpus_lines(corpus):
    with open(os.path.join(REPO, "server/tests/replay", corpus, "requests.txt")) as f:
        return f.read().splitlines()


def cut_after(corpus, method, nth=1, arg=None):
    """The index of the request line after which to cut: the nth `method` request (with the packet
    log's comment line `arg` in its arguments, e.g. UpdateTutorial's '4')."""
    lines, seen, comment = corpus_lines(corpus), 0, ""
    for i, line in enumerate(lines):
        if line.startswith("# 20"):
            comment = line
            continue
        f = line.split()
        if len(f) >= 4 and f[0] in ("wire", "req") and f[3] == method:
            if arg is None or comment.rstrip().endswith(": " + arg):
                seen += 1
                if seen == nth:
                    return i
    raise ValueError("%s: no request %s #%d%s" % (corpus, method, nth, " (%s)" % arg if arg else ""))


def side_files(db):
    """The server's side files of a prepared state (OUT_DIR/side/*: every file of the replay's data
    dir but the state DB), for the target to copy into its server's data dir."""
    d = os.path.join(os.path.dirname(db), "side")
    return [os.path.join(d, f) for f in sorted(os.listdir(d))] if os.path.isdir(d) else []


def state(corpus, upto, out_dir, server_bin):
    """OUT_DIR/server.sqlite3: the server state after the corpus's request lines [0, upto] (a
    line index: cut_after), replayed with the corpus's own options. Made once per out dir."""
    db = os.path.join(out_dir, "server.sqlite3")
    with _lock:
        if os.path.exists(db):
            return db
        os.makedirs(out_dir, exist_ok=True)
        cdir = os.path.join(out_dir, "corpus")
        os.makedirs(cdir, exist_ok=True)
        src = os.path.join(REPO, "server/tests/replay", corpus)
        with open(os.path.join(cdir, "requests.txt"), "w") as f:
            f.write("\n".join(corpus_lines(corpus)[:upto + 1]) + "\n")
        # the corpus's options (paths relative to the repo root) and time zone (its header)
        opts = [a for a in open(os.path.join(src, "options")).read().splitlines() if a.strip()]
        tz = next((ln.split(":", 1)[1].strip() for ln in corpus_lines(corpus) if ln.startswith("# tz:")), "UTC")
        rout = os.path.join(out_dir, "replay")
        r = subprocess.run([server_bin] + opts + ["--replay", cdir, "--out", rout], cwd=REPO, capture_output=True, text=True,
                           env=dict(os.environ, TZ=tz))
        with open(os.path.join(out_dir, "replay.log"), "w") as f:
            f.write("$ %s\n%s%s" % (" ".join(shlex.quote(x) for x in [server_bin] + opts + ["--replay", cdir, "--out", rout]),
                                    r.stdout, r.stderr))
        live = os.path.join(rout, "data", "server.sqlite3")
        if r.returncode != 0 or not os.path.exists(live):
            raise RuntimeError("preparing the state from %s failed (see %s/replay.log)" % (corpus, out_dir))
        # one self-contained file (the replay's DB is in WAL mode)
        a, b = sqlite3.connect(live), sqlite3.connect(db + ".tmp")
        a.backup(b)
        a.close()
        b.close()
        # the side files (the campaign's server_campaign.txt, ...): everything else in the data dir
        side = os.path.join(out_dir, "side")
        os.makedirs(side, exist_ok=True)
        for f in os.listdir(os.path.dirname(live)):
            p = os.path.join(os.path.dirname(live), f)
            if os.path.isfile(p) and not f.startswith("server.sqlite3"):
                shutil.copyfile(p, os.path.join(side, f))
        os.rename(db + ".tmp", db)
        return db
