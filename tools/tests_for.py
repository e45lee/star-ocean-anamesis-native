#!/usr/bin/env python3
"""Which tests to run for a change: the test-impact map.

    tools/tests_for.py [PATH...]                  the tests for these changed paths
    tools/tests_for.py --git-diff REV             ... for the paths changed since REV (committed and not)
    tools/tests_for.py ... --all                  every test that touches the change, not the cheapest set
    tools/tests_for.py ... --names                one test name per line (tools/gate.sh T1 reads it)
    tools/tests_for.py --regen [--observed DIR...] regenerate tests/impact.json
    tools/tests_for.py --check                    exit 1 when tests/impact.json is out of date with
                                                  soa-server --list-apis and tests/tiers.json

How a path becomes tests (the rules, in order):
  * docs only (*.md outside the code folders, docs/, LICENSE, images): nothing.
  * server/src/api/<dir>/<file>: the APIs that file answers (soa-server --list-apis) plus what its
    module hooks reach (--list-hooks: OnPlayerLoad / ClientMaster -> the login APIs, MissionStartExtra
    -> MissionStart, MissionResultExtra / AreaExtra -> MissionEnd, Grant -> every rewarding API,
    OnResponse / Schema -> the login APIs); a file answering nothing and hooking nothing: its
    folder's APIs. Then the tests whose recorded requests (tests/impact.json) include one of them:
    the replay corpora (always; seconds), and the cheapest shards and sessions that cover them
    (greedy by measured time; --all lists every one).
  * server/src/rules/<x>_rules*: the API folder <x> (growth, deepspace, gear -> items, mission -> missions).
  * the rest of server/ (core, state, master, cdn, net, app, include), tools/server_*: every corpus,
    every shard (the broad server set) and the replay against the parent build.
  * runtime/, platform370/, port/src/, emulator/src/, the root build files: the broad set: every
    shard, smoke, and the emulator / viewer gates where the user's gate scope says so.
  * tests/diff/, control/: every shard (the drivers changed), smoke, one port session and one
    emulator session (DRIVER_SESSIONS), and the slot pool's tests.
  * a test script itself (port/scripts/X.sh, emulator/scripts/X.sh, ...), or the session module
    behind a wrapper (control/soadrive/sessions/X.py, its WRAPPER line): that test.
  * a T1 check (kind `check`) whose `area` holds the path (e.g. english-report for data/english/).
Everything also runs T0 (tools/gate.sh T0) first.

tests/impact.json (generated, committed): {"apis": {API: file}, "hooks": {file: [kinds]},
"tests": {name: {"apis": [...], "source": "observed|declared"}}}. Observed APIs come from runs:
the replay corpora's requests.txt, tests/diff packet logs (`> Method`), session logs
(`request Method`, soa-server packet logs); `--observed DIR` scans a tools/gate.sh out dir (one
sub-dir per test). Tests never observed fall back to the API names their script mentions
("declared"). Regenerate after adding a test or a corpus, or when a flow changes its requests:
    tools/gate.sh T2 --out /tmp/g && tools/tests_for.py --regen --observed /tmp/g
"""
import argparse
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TIERS = os.path.join(REPO, "tests/tiers.json")
IMPACT = os.path.join(REPO, "tests/impact.json")
REPLAY = os.path.join(REPO, "server/tests/replay")

LOGIN = ["NoLoginStart", "Login", "GetPlayer", "GetServerTime"]
REWARDING = ["MissionEnd", "SaleGacha", "Gacha", "GachaOnce", "GachaTicket", "BoxGacha", "GetPresent", "GetPresentArray",
             "AchievementReceive", "AchievementReceiveList", "AchievementListReceive", "ExshopExchange", "ExItemShop",
             "DeepSpaceMissionEnd", "Sphere211MissionEnd", "ReturnSphere211"]
HOOK_APIS = {
    "OnPlayerLoad": LOGIN, "ClientMaster": LOGIN, "Schema": LOGIN, "OnResponse": LOGIN, "ItemExtra": LOGIN,
    "MissionStartExtra": ["MissionStart"], "MissionResultExtra": ["MissionEnd"], "AreaExtra": ["MissionEnd", "GetMissionList"],
    "Grant": REWARDING,
}
RULES_DIR = {"growth": "growth", "deepspace": "deepspace", "gear": "items", "mission": "missions"}
BROAD_SERVER = ("server/", "tools/server_")
BROAD_CLIENT = ("runtime/", "platform370/", "port/src/", "emulator/src/", "emulator-viewer/src/", "CMakeLists.txt", "cmake/",
                "vcpkg.json", "scripts/build.sh")
DRIVERS = ("tests/diff/", "control/", "scripts/shared-phone.sh", "port/scripts/phone370.sh")
# a change to the drivers (control/soadrive, control/run.py) also runs these sessions (the port's
# session layout and the emulator's), besides every shard and smoke
DRIVER_SESSIONS = ("session:rebase-inproc", "emu:seeded")
DOC = re.compile(r"(\.md$|^docs/|^LICENSE$|\.png$|\.jpg$|\.txt$)")
CODE_TXT = ("tests/tutorial_milestones.txt", "tools/server_log_patterns.txt", "requirements.txt")


def load_tiers():
    return json.load(open(TIERS))["tests"]


def soa_server():
    return os.environ.get("SOA_SERVER", os.path.join(REPO, "build/server/soa-server"))


def list_apis():
    out = subprocess.run([soa_server(), "--list-apis"], capture_output=True, text=True, cwd=REPO).stdout
    return {f[0]: (f[2] if f[2] != "-" else None) for f in (ln.split("\t") for ln in out.splitlines()) if len(f) >= 3}


def list_hooks():
    out = subprocess.run([soa_server(), "--list-hooks"], capture_output=True, text=True, cwd=REPO).stdout
    hooks = {}
    for ln in out.splitlines():
        f = ln.split("\t")
        if len(f) >= 3:
            hooks.setdefault(f[2].split(":")[0], set()).add(f[0])
    return {k: sorted(v) for k, v in hooks.items()}


# ---- observed requests ------------------------------------------------------------------------------
REQ_RX = [re.compile(r" > (\w+) fid="), re.compile(r"request (\w+) \(fid"), re.compile(r"I/server: request (\w+)")]


def scan_dir(d, apis):
    """The API names requested in any log under d."""
    seen = set()
    for root, dirs, files in os.walk(d):
        dirs[:] = [x for x in dirs if x != "prepared"]  # a shard's prepared state: the corpus replayed, not the run
        for f in files:
            if not (f.endswith(".log") or f.endswith(".txt")) or f.startswith("state-"):
                continue
            try:
                text = open(os.path.join(root, f), errors="replace").read()
            except OSError:
                continue
            for rx in REQ_RX:
                seen.update(m for m in rx.findall(text) if m in apis)
    return seen


def corpus_apis(name, apis):
    seen = set()
    for ln in open(os.path.join(REPLAY, name, "requests.txt")):
        f = ln.split()
        if len(f) >= 4 and f[0] in ("wire", "req") and f[3] in apis:
            seen.add(f[3])
    return seen


SESSIONS = os.path.join(REPO, "control/soadrive/sessions")


def session_modules():
    """{session module path (repo-relative): the wrapper scripts it serves} from each module's WRAPPER
    line (control/run.py's sessions; a wrapper like port/scripts/x_session.sh execs control/run.py)."""
    out = {}
    if not os.path.isdir(SESSIONS):
        return out
    for f in sorted(os.listdir(SESSIONS)):
        if f.endswith(".py") and not f.startswith("_"):
            m = re.search(r'^WRAPPER = "([^" ]+)', open(os.path.join(SESSIONS, f), errors="replace").read(), re.M)
            if m:
                out["control/soadrive/sessions/" + f] = m.group(1)
    return out


def test_script(cmd):
    m = re.search(r"([\w./-]+\.(?:sh|py))", cmd)
    return m.group(1) if m else None


def declared(cmd, apis):
    """API names written in the test's script (when no run of it has been seen); for a wrapper of
    control/run.py, also in the session modules it runs."""
    script = test_script(cmd)
    if not script or not os.path.exists(os.path.join(REPO, script)):
        return set()
    text = open(os.path.join(REPO, script), errors="replace").read()
    for mod, wrapper in session_modules().items():
        if wrapper == script:
            text += open(os.path.join(REPO, mod), errors="replace").read()
    return {a for a in apis if re.search(r"\b%s\b" % re.escape(a), text)} | set(LOGIN)


def regen(observed_dirs):
    apis = list_apis()
    old = json.load(open(IMPACT))["tests"] if os.path.exists(IMPACT) else {}
    tests = {}
    for c in sorted(os.listdir(REPLAY)):
        if os.path.exists(os.path.join(REPLAY, c, "requests.txt")):
            tests["replay:" + c] = {"apis": sorted(corpus_apis(c, apis)), "source": "observed (requests.txt)"}
    for t in load_tiers():
        name = t["name"]
        seen = set()
        m = re.match(r"tests/diff/run\.sh ((?:[\w-]+ )*)--out", t["cmd"])
        flows = (m.group(1).split() or ["seeded", "tutorial", "event"]) if m else []
        for d in observed_dirs:
            # a tools/gate.sh out dir (one dir per test), or a tests/diff out dir (one per flow)
            for p in [os.path.join(d, name.replace(":", "-"))] + [os.path.join(d, f) for f in flows]:
                if os.path.isdir(p):
                    seen |= scan_dir(p, apis)
        if t.get("apis") is False:  # talks to no server (the viewer, a boot without one, selftests)
            continue
        if "Login" in seen:
            seen.add("GetPlayer")  # the server answers a Login with a GetPlayerRes too (its player builder)
        if not seen and name in old and old[name]["source"].startswith("observed"):
            seen = set(old[name].get("observed", old[name]["apis"]))  # kept from an earlier run
        if t["kind"] not in ("shard", "flow", "session", "selftest"):
            continue
        # observed plus what its script names (a run that failed early observed only part of it)
        dec = declared(t["cmd"], apis) if t["kind"] == "session" else set()
        if seen:
            tests[name] = {"apis": sorted(seen | dec), "source": "observed" + ("+declared" if dec - seen else ""),
                           "observed": sorted(seen)}
        else:
            tests[name] = {"apis": sorted(dec or declared(t["cmd"], apis)), "source": "declared"}
    data = {"about": "Generated by tools/tests_for.py --regen (do not edit; see its --help).",
            "apis": {a: f for a, f in sorted(apis.items()) if f}, "hooks": list_hooks(), "tests": tests}
    with open(IMPACT, "w") as f:
        json.dump(data, f, indent=1, ensure_ascii=False, sort_keys=False)
        f.write("\n")
    return data


def check():
    data = json.load(open(IMPACT))
    apis = {a: f for a, f in list_apis().items() if f}
    errs = []
    if apis != data["apis"]:
        errs.append("the APIs differ from soa-server --list-apis (added %s, removed %s)" %
                    (sorted(set(apis) - set(data["apis"])), sorted(set(data["apis"]) - set(apis))))
    names = {t["name"] for t in load_tiers() if t["kind"] in ("shard", "flow", "session", "selftest") and t.get("apis") is not False}
    missing = sorted(names - set(data["tests"]))
    if missing:
        errs.append("tests without an entry: %s" % missing)
    for e in errs:
        print("tests_for --check: " + e)
    print("tests_for --check: %s" % ("FAIL (tools/tests_for.py --regen)" if errs else "tests/impact.json is current"))
    return 1 if errs else 0


# ---- selection --------------------------------------------------------------------------------------
def changed_paths(rev):
    out = subprocess.run(["git", "diff", "--name-only", rev], capture_output=True, text=True, cwd=REPO).stdout.split()
    out += subprocess.run(["git", "ls-files", "--others", "--exclude-standard"], capture_output=True, text=True, cwd=REPO).stdout.split()
    return sorted(set(out))


def affected(paths, data, tiers):
    """(apis, broad_server, broad_client, drivers, direct tests, reasons)."""
    apis_of_file = {}
    for a, f in data["apis"].items():
        apis_of_file.setdefault(f, set()).add(a)
    apis, reasons, direct = set(), [], set()
    broad_server = broad_client = drivers = False
    scripts = {}
    for t in tiers:
        m = re.search(r"([\w./-]+\.(?:sh|py))", t["cmd"])
        if m:
            scripts.setdefault(m.group(1), []).append(t["name"])
    sessions = session_modules()
    for p in paths:
        if p in sessions and sessions[p] in scripts:
            direct.update(scripts[sessions[p]])
            reasons.append("%s: the session behind %s" % (p, sessions[p]))
            continue
        if p in scripts and (p.startswith(("port/scripts/", "emulator/scripts/", "emulator-viewer/scripts/"))):
            direct.update(scripts[p])
            reasons.append("%s: the test script itself" % p)
            if p in ("port/scripts/phone370.sh",):
                drivers = True
            continue
        if p.startswith("server/tests/replay/"):
            reasons.append("%s: a replay corpus (T0's replay; replay-parent)" % p)
            continue
        if DOC.search(p) and p not in CODE_TXT and not p.startswith(("server/src/", "runtime/", "port/src/")):
            reasons.append("%s: documentation (no test)" % p)
            continue
        m = re.match(r"server/src/api/([^/]+)/([^/]+)$", p)
        r = re.match(r"server/src/rules/([a-z0-9]+)_rules", p)
        if m or r:
            if r:
                d = RULES_DIR.get(r.group(1))
                if not d:
                    broad_server = True
                    reasons.append("%s: shared rules -> the broad server set" % p)
                    continue
                files = [f for f in apis_of_file if f.startswith("server/src/api/%s/" % d)]
                hooks_files = [f for f in data["hooks"] if f.startswith("server/src/api/%s/" % d)]
            else:
                d = m.group(1)
                files = [p] if p in apis_of_file else []
                hooks_files = [p] if p in data["hooks"] else []
                if not files and not hooks_files:  # a helper: the folder's
                    files = [f for f in apis_of_file if f.startswith("server/src/api/%s/" % d)]
                    hooks_files = [f for f in data["hooks"] if f.startswith("server/src/api/%s/" % d)]
            got = set()
            for f in files:
                got |= apis_of_file[f]
            for f in hooks_files:
                for k in data["hooks"][f]:
                    got |= set(HOOK_APIS.get(k, LOGIN))
            if not got:
                broad_server = True
                reasons.append("%s: no API or hook of its own -> the broad server set" % p)
            else:
                apis |= got
                reasons.append("%s: %s" % (p, " ".join(sorted(got))))
            continue
        if p.startswith(BROAD_SERVER):
            broad_server = True
            reasons.append("%s: server core -> every corpus, every shard" % p)
            continue
        if p.startswith(BROAD_CLIENT) or p in BROAD_CLIENT:
            broad_client = True
            reasons.append("%s: client / runtime / build -> the broad set" % p)
            continue
        if p.startswith(DRIVERS):
            drivers = True
            reasons.append("%s: the test drivers -> every shard" % p)
            continue
        if p.startswith("tools/") or p.startswith("tests/"):
            reasons.append("%s: tooling (T0 only)" % p)
            continue
        reasons.append("%s: no rule (T0 only)" % p)
    return apis, broad_server, broad_client, drivers, direct, reasons


def select(paths, all_tests=False):
    data = json.load(open(IMPACT))
    tiers = load_tiers()
    by_name = {t["name"]: t for t in tiers}
    apis, bs, bc, drv, direct, reasons = affected(paths, data, tiers)
    chosen, why = [], {}

    def add(name, w):
        if name not in why:
            chosen.append(name)
            why[name] = w

    corpora = sorted(n for n, v in data["tests"].items() if n.startswith("replay:") and (bs or set(v["apis"]) & apis))
    shards = [t for t in tiers if t["kind"] == "shard"]
    if bs or bc or drv:
        for t in shards:
            add(t["name"], "broad")
        if bs:
            add("replay-parent", "server core")
        if bc or drv:
            add("smoke", "client / drivers")
        if drv:
            # the session runner and the shared flows: one port session and one emulator session
            for n in DRIVER_SESSIONS:
                add(n, "drivers")
        if bc:
            for t in tiers:
                if t["tier"] == "T2" and t.get("area") and t["kind"] == "session" and any(
                        any(p.startswith(a) or p == a for a in t["area"]) for p in paths):
                    add(t["name"], "gate scope")
    if apis:
        add("replay-parent", "server APIs")
        cands = [t for t in tiers if t["kind"] in ("shard", "session") and t["name"] in data["tests"]
                 and t["tier"] in ("T1", "T2")]
        if all_tests:
            for t in cands:
                hit = set(data["tests"][t["name"]]["apis"]) & apis
                if hit:
                    add(t["name"], " ".join(sorted(hit)))
        else:
            # greedy weighted set cover: shards first (they compare 3 targets), then sessions
            left = set(apis)
            covered_any = set().union(*(set(data["tests"][t["name"]]["apis"]) for t in cands)) if cands else set()
            left &= covered_any
            while left:
                best = min(cands, key=lambda t: (t["secs"] * (1 if t["kind"] == "shard" else 1.5)) /
                           max(1e-9, len(set(data["tests"][t["name"]]["apis"]) & left)))
                hit = set(data["tests"][best["name"]]["apis"]) & left
                if not hit:
                    break
                add(best["name"], " ".join(sorted(hit)))
                left -= hit
            for a in sorted(apis - covered_any):
                reasons.append("note: %s is in no shard or session (only corpora%s)" % (a, "" if any(a in data["tests"][c]["apis"] for c in corpora) else ": add one"))
    for n in sorted(direct):
        add(n, "its script changed")
    # a T1 check with an `area` (e.g. english-report: data/english/, tools/english_*): when a path is in it
    for t in tiers:
        if t["tier"] == "T1" and t["kind"] == "check" and t.get("area") and any(
                any(p.startswith(a) or p == a for a in t["area"]) for p in paths):
            add(t["name"], "its area")
    return [by_name[n] for n in chosen if n in by_name], why, corpora, apis, reasons


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("paths", nargs="*")
    ap.add_argument("--git-diff", metavar="REV")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--names", action="store_true")
    ap.add_argument("--regen", action="store_true")
    ap.add_argument("--observed", nargs="*", default=[])
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    if a.regen:
        d = regen([os.path.abspath(x) for x in a.observed])
        print("wrote tests/impact.json: %d APIs, %d tests (%d observed)" %
              (len(d["apis"]), len(d["tests"]), sum(1 for v in d["tests"].values() if v["source"].startswith("observed"))))
        return 0
    if a.check:
        return check()
    paths = list(a.paths)
    if a.git_diff:
        paths += changed_paths(a.git_diff)
    paths = [os.path.relpath(os.path.abspath(p), REPO) if os.path.exists(p) else p for p in paths]
    tests, why, corpora, apis, reasons = select(paths, a.all)
    if a.names:
        print("\n".join(t["name"] for t in tests))
        return 0
    print("changed: %d paths" % len(paths))
    for r in reasons:
        print("  " + r)
    if apis:
        print("APIs: " + " ".join(sorted(apis)))
    print("\nT0 always: tools/gate.sh T0")
    if corpora:
        print("replay corpora (in T0's replay; vs the parent build: replay-parent): " + " ".join(c[7:] for c in corpora))
    if not tests:
        print("T1: nothing beyond T0")
        return 0
    total = 0
    print("T1 (%s):" % ("every test touching it" if a.all else "the cheapest set covering it"))
    for t in tests:
        print("  %-28s %5ds  %s  [%s]" % (t["name"], t["secs"], t["cmd"], why[t["name"]]))
        total += t["secs"]
    shards = [t["name"].split(":", 1)[1] for t in tests if t["kind"] == "shard"]
    if shards:
        print("\nthe shards in one run (parallel): tests/diff/run.sh %s" % " ".join(shards))
    print("run them: tools/gate.sh T1 --for %s" % (("--git-diff " + a.git_diff) if a.git_diff else " ".join(a.paths)))
    print("(sum of the tests' times %ds; in parallel about the longest)" % total)
    return 0


if __name__ == "__main__":
    sys.exit(main())
