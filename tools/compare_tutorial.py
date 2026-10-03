#!/usr/bin/env python3
"""Tutorial parity: the new-player tutorial flow of the port (soa, a fresh data dir) and
of the 3.7.0 emulator (soa-emu + soa-server), checked against one milestone list and compared.

    tools/compare_tutorial.py check port PORT_OUT [--name Claire]
    tools/compare_tutorial.py check emu EMU_OUT [--name Claire]
    tools/compare_tutorial.py compare PORT_OUT EMU_OUT [--name Claire] [--montage DIR]

PORT_OUT is port/scripts/tutorial_session.sh's out dir (fresh.log, fresh/*.png, server.sqlite3);
EMU_OUT is emulator/scripts/emulator_session.sh --new-player's (packets/packets.log, emu.log,
*.png, server/server.sqlite3). The milestones are tests/tutorial_milestones.txt.

check: prints PASS / FAIL per milestone (the requests in order, the battle party's stats) and
exits non-zero on a FAIL. compare: the parity report: the request sequences (every difference
classified: transport, or a behavioural difference), the battle (party, enemies, damage), the
screenshots (RMSE per milestone pair, montages, the tutorial frames aligned) and the two server
states (every table, times masked). emulator/README.md "Tutorial parity".

Needs ImageMagick (compare, convert, montage) for the screenshots and python3-msgpack for the
emulator's battle log.
"""
import argparse
import difflib
import glob
import math
import os
import re
import sqlite3
import statistics
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SPEC = os.path.join(REPO, "tests", "tutorial_milestones.txt")
ONDAMAGE = "_ZN16CCharacterObject8OnDamageERKN24IAttackCollisionCallback23CallbackArgument_DamageEfb"

# Requests that only one side sends, and why. None of them changes the server's state.
TRANSPORT = {
    "StartBridge": "the emulator's bridge handshake (soa's server is in-process: no bridge)",
    "UpdateSession": "the emulator's bridge session (no bridge in soa)",
    "GetServerTime": "CPhase_SyncServerTime: sent when the 10-minute bucket changed between phase switches (timing)",
    "GetMissionList": "read-only: the emulator's mission menu asks for the list, soa's route doesn't; in-process the same "
                      "ActiveMissionList comes with every response (docs/server-rules.md 'The story campaign on the wire')",
}


# ---- the spec ---------------------------------------------------------------------------------
def load_spec(name):
    reqs, party, shots = [], [], []
    for line in open(SPEC, encoding="utf-8"):
        line = line.rstrip("\n")
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        kind, _, rest = line.partition(" ")
        if kind == "req":
            reqs.append(rest.replace("$NAME", name).strip())
        elif kind == "party":
            party.append(tuple(float(x) for x in rest.split()))
        elif kind == "shot":
            f = rest.split(" ", 4)
            shots.append((f[0], f[1], f[2], float(f[3]), f[4] if len(f) > 4 else ""))
    return reqs, party, shots


# ---- the requests, normalized -------------------------------------------------------------------
# Each entry: (method, normalized args). Arguments one client sends that the other's transport
# can't carry are dropped:
#   NoLoginStart(version): the app version string (it differed while the port ran the offline build)
#   Login(uuid, ..): soa's FakeApiCaller route captures no Login arguments
#   CreatePlayer(uuid, name, device, ..): the name only (soa captures the strings it needs)
#   EndMissionTalk(type, mission, flag, u32): the mission only: soa delivers it from
#     CEventScenario::Exit with the mission id (docs/client-changes.md); the server reads only it
#   MissionEnd(mission, battle_log, flag): soa reads the battle log from the client in-process
def port_requests(log):
    out = []
    last_end = -10
    for i, line in enumerate(open(log, errors="replace")):
        m = re.search(r"I/server: request (\w+) \(fid [0-9a-f]+\):\s?(.*)$", line)
        if m:
            meth, args = m.group(1), m.group(2).strip()
            if meth == "GetPlayMission" and i - last_end <= 6:
                continue  # the EndMissionTalk answer's delivery (restore_campaign.cpp)
            out.append(normalize(meth, args))
            continue
        m = re.search(r"I/restore: CEventScenario::Exit: EndMissionTalk\((\d+)\)", line)
        if m:
            out.append(("EndMissionTalk", m.group(1)))
            last_end = i
    return out


def emu_requests(plog):
    out = []
    for line in open(plog, errors="replace"):
        m = re.search(r" > (\w+) fid=\S+ .*? args: ?(.*)$", line)
        if m:
            out.append(normalize(m.group(1), m.group(2).strip()))
    return out


def normalize(meth, args):
    a = args
    if meth in ("NoLoginStart", "Login", "SimpleLogin"):
        a = ""
    elif meth == "CreatePlayer":
        q = re.findall(r'"([^"]*)"', args)
        names = [s for s in q if not re.fullmatch(r"[0-9a-f-]{36}", s) and s]
        a = '"%s"' % (names[0] if names else "")
    elif meth == "EndMissionTalk":
        p = args.split()
        a = p[1] if len(p) >= 2 else args
    elif meth == "MissionEnd":
        a = " ".join(x for x in args.split() if not x.startswith("battle_log["))
    return (meth, a)


def fmt(r):
    return (r[0] + " " + r[1]).strip()


def behavioural(reqs):
    return [r for r in reqs if r[0] not in TRANSPORT]


def check_order(reqs, want):
    """[(milestone, ok)]: each wanted request found after the previous one."""
    res, pos = [], 0
    have = [fmt(r) for r in reqs]
    for w in want:
        try:
            k = have.index(w, pos)
            res.append((w, True))
            pos = k + 1
        except ValueError:
            res.append((w, False))
    return res


# ---- the battle -------------------------------------------------------------------------------------
def port_party(log):
    """The party's stats: the battle natives' damage log (SOA_BATTLE_DAMAGE_LOG, before the
    rebase's revision 2), else the stats the client battled with: its MissionEnd battle log's
    PlayerCharacter list, which the in-process server logs (as the emulator's packet log keeps
    it), else what the server sent in MissionStart (its NPC model's log line)."""
    s, fought, sent = set(), set(), set()
    for line in open(log, errors="replace"):
        m = re.search(r"battle_dmg: atk kind 1 \[hp (\S+) atk (\S+) int (\S+) def (\S+) hit (\S+) grd (\S+)\]", line)
        if m:
            s.add(tuple(float(x) for x in m.groups()))
        m = re.search(r"MissionStart NPC \d+: master-data model applied .*\[hp (\S+) atk (\S+) int (\S+) def (\S+) hit (\S+) grd (\S+)\]", line)
        if m:
            sent.add(tuple(float(x) for x in m.groups()))
        m = re.search(r"MissionEnd mission 3645708271 battle log PlayerCharacter \d+: \[hp (\S+) atk (\S+) int (\S+) def (\S+) hit (\S+) grd (\S+)\]", line)
        if m:
            fought.add(tuple(float(x) for x in m.groups()))
    return s or fought or sent


def port_enemies(log):
    s = set()
    for line in open(log, errors="replace"):
        m = re.search(r"-> def kind 2 \[hp (\S+) atk (\S+) int (\S+) def (\S+) hit (\S+) grd (\S+)\]", line)
        if m:
            s.add(tuple(float(x) for x in m.groups()))
    return s


def port_bases(log):
    """The port's hits as (final / cancel) and the cancel levels seen (SOA_BATTLE_DAMAGE_LOG)."""
    bases, cancels = set(), set()
    for line in open(log, errors="replace"):
        m = re.search(r"battle_dmg: .* cancel (\S+) -> base \S+, final (\S+)", line)
        if m and float(m.group(1)) > 0 and float(m.group(2)) > 0:
            cancels.add(float(m.group(1)))
            bases.add(float(m.group(2)) / float(m.group(1)))
    return bases, cancels


def emu_battle_log(out):
    logs = sorted(glob.glob(os.path.join(out, "packets", "*-MissionEnd-battle_log.msgp")),
                  key=lambda p: int(os.path.basename(p).split("-")[0]))
    if not logs:
        return None
    import msgpack
    return msgpack.unpackb(open(logs[0], "rb").read(), raw=False, strict_map_key=False)


def emu_party(out):
    bl = emu_battle_log(out)
    if not bl:
        return set()
    keys = ("hp", "attack", "intelligence", "defence", "hit", "guard")
    return {tuple(float(p.get(k, 0)) for k in keys) for p in bl.get("PlayerCharacter", [])}


def ondamage(log):
    v = []
    for line in open(log, errors="replace"):
        if "I/trace: " + ONDAMAGE in line:
            m = re.search(r" s0=([-0-9.e+]+)", line)
            if m:
                v.append(float(m.group(1)))
    return v


def mission_time(log):
    m = re.findall(r"MissionEnd mission 3645708271: .* time (\d+) ms", open(log, errors="replace").read())
    return int(m[0]) if m else None


# ---- screenshots -------------------------------------------------------------------------------
def rmse(a, b):
    p = subprocess.run(["compare", "-metric", "RMSE", a, b, "null:"], capture_output=True, text=True)
    m = re.search(r"\(([0-9.e+-]+)\)", p.stderr)
    return float(m.group(1)) if m else None


def tiny(f):
    return subprocess.run(["convert", f, "-resize", "45x80!", "-colorspace", "gray", "-depth", "8", "gray:-"],
                          capture_output=True).stdout


def tiny_rmse(a, b):
    n = min(len(a), len(b))
    return math.sqrt(sum((a[i] - b[i]) ** 2 for i in range(n)) / max(n, 1)) / 255.0


# ---- server state -------------------------------------------------------------------------------
TIME_COL = re.compile(r"(_at$|^at$|^time$|_time$|^day|_day$|^date|stamina_at)")
ID_COLS = {("player", "id"), ("player", "search_id")}


def state_rows(db):
    c = sqlite3.connect("file:%s?mode=ro" % db, uri=True)
    t = {}
    for (name,) in c.execute("select name from sqlite_master where type = 'table' order by name"):
        cur = c.execute('select * from "%s"' % name)
        cols = [d[0] for d in cur.description]
        rows = []
        for r in cur.fetchall():
            rows.append(tuple("<time>" if TIME_COL.search(col) else "<id>" if (name, col) in ID_COLS else v
                              for col, v in zip(cols, r)))
        t[name] = (cols, sorted(rows, key=repr))
    return t


# ---- runs ------------------------------------------------------------------------------------------
class Run:
    def __init__(self, kind, out):
        self.kind, self.out = kind, out
        if kind == "port":
            self.log = os.path.join(out, "fresh.log")
            self.shots = os.path.join(out, "fresh")
            self.db = os.path.join(out, "server.sqlite3")
            self.reqs = port_requests(self.log) if os.path.exists(self.log) else []
        else:
            self.log = os.path.join(out, "emu.log")
            self.shots = out
            self.db = os.path.join(out, "server", "server.sqlite3")
            plog = os.path.join(out, "packets", "packets.log")
            self.reqs = emu_requests(plog) if os.path.exists(plog) else []

    def party(self):
        return port_party(self.log) if self.kind == "port" else emu_party(self.out)

    def damage(self):
        return ondamage(self.log)

    def time(self):
        return mission_time(self.log if self.kind == "port" else os.path.join(self.out, "server.log"))

    def tutorial_frames(self):
        pat = "l[0-9][0-9][0-9].png" if self.kind == "port" else "tutorial-[0-9][0-9][0-9].png"
        return sorted(glob.glob(os.path.join(self.shots, pat)))


def check(kind, out, name):
    reqs, party, _ = load_spec(name)
    run = Run(kind, out)
    failed = 0
    for w, ok in check_order(run.reqs, reqs):
        print("%s  milestone: %s" % ("PASS" if ok else "FAIL", w))
        failed |= not ok
    got = run.party()
    for p in party:
        ok = p in got
        print("%s  battle party member %s" % ("PASS" if ok else "FAIL", " ".join("%g" % x for x in p)))
        failed |= not ok
    extra = got - set(party)
    if extra:
        print("FAIL  battle party: unexpected members %s" % sorted(extra))
        failed = 1
    print("FAIL tutorial milestones" if failed else "PASS tutorial milestones (%s)" % SPEC)
    return 1 if failed else 0


def compare(port_out, emu_out, name, montage_dir):
    reqs, party, shots = load_spec(name)
    p, e = Run("port", port_out), Run("emu", emu_out)
    unexplained = 0
    print("# Tutorial parity report")
    print("port: %s\nemulator: %s\n" % (port_out, emu_out))

    print("## Milestones (%s)" % os.path.relpath(SPEC, REPO))
    for run in (p, e):
        res = check_order(run.reqs, reqs)
        bad = [w for w, ok in res if not ok]
        print("- %s: %d/%d milestones%s" % (run.kind, len(res) - len(bad), len(res), (", missing: " + "; ".join(bad)) if bad else ""))
        unexplained += len(bad)

    print("\n## Requests")
    for run in (p, e):
        only = {}
        for r in run.reqs:
            if r[0] in TRANSPORT:
                only[r[0]] = only.get(r[0], 0) + 1
        print("- %s: %d requests, %d behavioural; transport-only: %s" % (
            run.kind, len(run.reqs), len(behavioural(run.reqs)), ", ".join("%s x%d" % kv for kv in sorted(only.items())) or "none"))
    for k, why in TRANSPORT.items():
        print("  - %s: %s" % (k, why))
    pb, eb = [fmt(r) for r in behavioural(p.reqs)], [fmt(r) for r in behavioural(e.reqs)]
    if pb == eb:
        print("- behavioural sequence: identical (%d requests)" % len(pb))
    else:
        print("- behavioural sequence: DIFFERENT")
        for l in difflib.unified_diff(eb, pb, "emulator", "port", lineterm="", n=1):
            print("    " + l)
        unexplained += 1

    print("\n## Tutorial battle (ms00_001)")
    pp, ep = p.party(), e.party()
    for name_, s in (("port", pp), ("emulator", ep)):
        print("- %s party: %s" % (name_, "; ".join(" ".join("%g" % x for x in m) for m in sorted(s)) or "none logged"))
    if pp == ep == set(party):
        print("- party stats: identical, and as the milestones expect (hp atk int def hit guard)")
    else:
        print("- party stats: DIFFERENT (expected %s)" % sorted(set(party)))
        unexplained += 1
    bl = emu_battle_log(emu_out)
    if bl:
        print("- emulator enemies (battle log StageEnemyInfo / DefeatedEnemyInfo): %s / %s" % (
            bl.get("StageEnemyInfo"), bl.get("DefeatedEnemyInfo")))
    pe = port_enemies(p.log)
    if pe:
        print("- port enemies (SOA_BATTLE_DAMAGE_LOG defenders): %s" % "; ".join(" ".join("%g" % x for x in m) for m in sorted(pe)))
    print("- mission time (MissionEnd): port %s ms, emulator %s ms (the scripted taps, not the same frames)" % (p.time(), e.time()))
    pd, ed = p.damage(), e.damage()
    for name_, d in (("port", pd), ("emulator", ed)):
        if d:
            q = sorted(d)
            print("- %s OnDamage: %d hits, min %.0f, median %.0f, p90 %.0f, max %.0f, total %.0f" % (
                name_, len(d), q[0], statistics.median(q), q[int(0.9 * (len(q) - 1))], q[-1], sum(q)))
        else:
            print("- %s OnDamage: not traced (SOA_TRACE=%s)" % (name_, ONDAMAGE))
    if pd and ed:
        # The hits differ with the taps' timing (which attacks, which combo step: the cancel bonus
        # x1 / x1.5 / x2), so the medians needn't agree. Compared: the strongest hit (the scripted
        # special attack, the same in every run) and how many of the emulator's hits are one of the
        # port's logged hits (final / cancel) at one of the port's cancel levels, within 3 %.
        # Informational beyond the max: the decisive inputs are the party stats above, the enemy
        # master rows and the damage code (the same 3.7.0 battle-calc code in both programs).
        mx = max(pd) / max(max(ed), 1e-9)
        ok = 0.95 < mx < 1.05
        print("- strongest hit: port %.0f, emulator %.0f (%s)" % (max(pd), max(ed), "the same" if ok else "DIFFERENT"))
        unexplained += not ok
        bases, cancels = port_bases(p.log)
        if bases:
            n = sum(1 for x in ed if any(abs(x - b * c) <= 0.03 * x for b in bases for c in cancels))
            print("- emulator hits that are a port hit's base x a cancel level %s (3 %%): %d of %d" % (sorted(cancels), n, len(ed)))

    print("\n## Screens")
    if montage_dir:
        os.makedirs(montage_dir, exist_ok=True)
    for nm, pf, ef, mx, why in shots:
        a, b = os.path.join(p.shots, pf), os.path.join(e.shots, ef)
        if not (os.path.exists(a) and os.path.exists(b)):
            print("- %s: missing (%s%s)" % (nm, "" if os.path.exists(a) else pf + " ", "" if os.path.exists(b) else ef))
            unexplained += 1
            continue
        v = rmse(a, b)
        ok = v is not None and v <= mx
        note = "" if ok else (" (expected: " + why + ")" if why else " DIFFERENT")
        print("- %s: RMSE %.3f (limit %.2f)%s" % (nm, v if v is not None else -1, mx, note))
        if not ok and not why:
            unexplained += 1
        if montage_dir:
            subprocess.run(["montage", a, b, "-tile", "2x1", "-geometry", "364x648+4+4", os.path.join(montage_dir, nm + ".png")])
    pf, ef = p.tutorial_frames(), e.tutorial_frames()
    if pf and ef:
        es = [tiny(f) for f in ef]
        worst, last, back = 0.0, -1, 0
        rows = []
        for f in pf:
            s = tiny(f)
            j = min(range(len(es)), key=lambda k: tiny_rmse(s, es[k]))
            d = tiny_rmse(s, es[j])
            back += j < last
            last = max(last, j)
            worst = max(worst, d)
            rows.append("%s~%s %.3f" % (os.path.basename(f), os.path.basename(ef[j]), d))
        close = sum(1 for r in rows if float(r.split()[-1]) <= 0.05)
        print("- tutorial frames (one every round): %d port frames, %d emulator frames; %d of the port's have an "
              "emulator frame within RMSE 0.05 (45x80 grey), %d out of order (the battle: taps and AI timing)" % (
                  len(pf), len(ef), close, back))
        print("  " + ", ".join(rows))

    print("\n## Server state (every table, times masked)")
    if os.path.exists(p.db) and os.path.exists(e.db):
        a, b = state_rows(p.db), state_rows(e.db)
        diffs = []
        for t in sorted(set(a) | set(b)):
            if t not in a or t not in b:
                diffs.append("%s: only in the %s" % (t, "emulator's" if t in b else "port's"))
            elif a[t] != b[t]:
                ra, rb = set(a[t][1]), set(b[t][1])
                diffs.append("%s: port-only rows %s; emulator-only rows %s" % (t, sorted(ra - rb, key=repr)[:4], sorted(rb - ra, key=repr)[:4]))
        expected = {"wire_device": "soa-server records the bridge's device UUID (docs/server-rules.md 'Device -> player')",
                    "meta": "meta.seed / the start time"}
        for d in diffs:
            t = d.split(":")[0]
            print("- %s%s" % (d, ("  (expected: " + expected[t] + ")") if t in expected else ""))
            if t not in expected:
                unexplained += 1
        if not diffs:
            print("- identical")
        print("- masked: player id / search_id (CHash32 of the device UUID + name), *_at / day columns")
    else:
        print("- missing: %s" % ", ".join(x for x in (p.db, e.db) if not os.path.exists(x)))

    print("\nunexplained differences: %d" % unexplained)
    print("PASS parity" if unexplained == 0 else "FAIL parity")
    return 0 if unexplained == 0 else 1


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sp = ap.add_subparsers(dest="cmd", required=True)
    c = sp.add_parser("check")
    c.add_argument("kind", choices=["port", "emu"])
    c.add_argument("out")
    c.add_argument("--name", default=os.environ.get("NEWPLAYER_NAME", "Claire"))
    m = sp.add_parser("compare")
    m.add_argument("port_out")
    m.add_argument("emu_out")
    m.add_argument("--name", default=os.environ.get("NEWPLAYER_NAME", "Claire"))
    m.add_argument("--montage", help="write a side-by-side montage per screenshot pair here")
    a = ap.parse_args()
    if a.cmd == "check":
        sys.exit(check(a.kind, a.out, a.name))
    sys.exit(compare(a.port_out, a.emu_out, a.name, a.montage))


if __name__ == "__main__":
    main()
