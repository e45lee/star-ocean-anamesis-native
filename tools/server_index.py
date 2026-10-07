#!/usr/bin/env python3
"""Generates server/API-INDEX.md, the local server's "where is X" index (docs/history/PLAN-readability.md 2.6).

    tools/server_index.py [--server BIN] [--out server/API-INDEX.md]
    tools/server_index.py --check            exit 1 when server/API-INDEX.md isn't what it would generate

From `soa-server --list-apis` (which methods the library answers, and who registered each), the
sources (the handler and its line, the hooks that add to its response, the tests that call it) and
the docs (docs/api.md's entry, the docs/server-rules.md sections that name it). Three tables:
  1. the APIs: method, FunctionID, handler (file:line, function), hooks, rules sections, docs/api.md, tests;
  2. the hooks in their run order (`soa-server --list-hooks`: the module order of
     server/src/core/modules.cpp), per kind, with file:line;
  3. each docs/server-rules.md section and the code files that link it.
Line numbers make the index go stale with any edit above a handler: regenerate it in the same
commit (tools/check_server_docs.sh reports a stale index).
"""
import argparse
import collections
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(REPO, "server/src")
HOOK_KINDS = ["OnPlayerLoad", "OnResponse", "MissionStartExtra", "MissionResultExtra", "Grant", "ItemExtra", "ClientMaster",
              "AreaExtra"]
API_RE = re.compile(r"\badd_(?:core_)?api\(\{([^}]*)\},\s*(\[|[\w:]+)")


def read(p):
    return open(p, encoding="utf-8", errors="replace").read().split("\n")


def slug(title):
    s = title.strip().lower()
    s = re.sub(r"[^\w\- ]", "", s)
    return s.replace(" ", "-")


def rel(p):
    return os.path.relpath(p, REPO)


def sources(top):
    """the .cpp files under top (recursive), sorted by path"""
    out = []
    for d, _, fs in os.walk(top):
        out += [os.path.join(d, f) for f in fs if f.endswith(".cpp")]
    return sorted(out)


def body_of(lines, start):
    """The text of the brace block that opens on or after line index `start` (a function body)."""
    depth, out, opened = 0, [], False
    for ln in lines[start:]:
        out.append(ln)
        for ch in ln:
            if ch == "{":
                depth += 1
                opened = True
            elif ch == "}":
                depth -= 1
        if opened and depth <= 0:
            break
    return "\n".join(out)


def core_handlers():
    """Server::dispatch's if-chain is gone (docs/history/PLAN-readability.md R8): every handler, the core's
    too, is an ext::add_core_api / add_api registration (module_handlers). Kept for callers: empty."""
    return {}, []


def module_handlers():
    """method -> (file, line, function, body) from the ext::add_api registrations."""
    res = {}
    for path in sources(SRC):
        lines = read(path)
        text = "\n".join(lines)
        for i, ln in enumerate(lines):
            m = API_RE.search(ln)
            if not m:
                continue
            methods = re.findall(r'"(\w+)"', m.group(1))
            fn = m.group(2)
            if fn == "[":
                body, at, name = body_of(lines, i), i, "(lambda)"
            else:
                d = re.search(r"^(?:static )?std::vector<u8> %s\(" % re.escape(fn), text, re.M)
                at = text[:d.start()].count("\n") if d else i
                body, name = (body_of(lines, at) if d else ""), fn
            for mth in methods:
                res[mth] = (rel(path), at + 1, name, body)
    return res


def core_registered():
    """the methods registered with ext::add_core_api (the core's APIs)"""
    res = set()
    for path in sources(SRC):
        for m in re.finditer(r"\badd_core_api\(\{([^}]*)\}", "\n".join(read(path))):
            res |= set(re.findall(r'"(\w+)"', m.group(1)))
    return res


def hooks(server):
    """kind -> [(file, line, module, detail)] in run order (soa-server --list-hooks)."""
    res = collections.OrderedDict((k, []) for k in HOOK_KINDS)
    out = subprocess.run([server, "--list-hooks"], capture_output=True, text=True, check=True).stdout
    for ln in out.splitlines():
        kind, module, at, detail = ln.split("\t")
        f, line = at.rsplit(":", 1)
        res.setdefault(kind, []).append((f, int(line), module, detail if kind == "Grant" else ""))
    return res


def tests_calling():
    """method -> sorted test names whose body names it as a string ("Method")."""
    res = collections.defaultdict(set)
    files = []
    for d in ("server/src", "server/tests"):
        files += sources(os.path.join(REPO, d))
    files.append(os.path.join(REPO, "port/src/native/api/zz_server_guest_test.cpp"))
    for p in files:
        if not os.path.exists(p):
            continue
        text = open(p, encoding="utf-8", errors="replace").read()
        parts = re.split(r'NATIVE_TEST\("([^"]+)"\)', text)
        for k in range(1, len(parts), 2):
            name, body = parts[k], parts[k + 1]
            for mth in set(re.findall(r'"([A-Z]\w+)"', body)):
                res[mth].add(name)
    return res


def replays_calling():
    res = collections.defaultdict(set)
    base = os.path.join(REPO, "server/tests/replay")
    if not os.path.isdir(base):
        return res
    for c in sorted(os.listdir(base)):
        p = os.path.join(base, c, "requests.txt")
        if not os.path.exists(p):
            continue
        for ln in open(p):
            m = re.match(r"(?:wire|req) \S+ \S+ (\w+)", ln)
            if m:
                res[m.group(1)].add("replay:" + c)
            m = re.match(r"# \S+ \S+ (\w+):", ln)
            if m:
                res[m.group(1)].add("replay:" + c)
    return res


def api_doc_entries():
    """method -> docs/api.md anchor, for its `### Method` entries."""
    res = {}
    for ln in read(os.path.join(REPO, "docs/api.md")):
        m = re.match(r"### (\w+)\s*$", ln)
        if m:
            res[m.group(1)] = slug(m.group(1))
    return res


def rules_sections():
    """[(heading, anchor, text)] of docs/server-rules.md (## to ####). The anchor is the section's
    explicit one (`<a id="..."></a>` on the line above, R20), else GitHub's slug. The generated
    register is left out (it repeats the domains' tables)."""
    secs, cur, buf, seen = [], None, [], collections.Counter()

    def anchor(t):  # GitHub's: a repeated heading gets -1, -2, ...
        a = slug(t)
        n = seen[a]
        seen[a] += 1
        return a if n == 0 else "%s-%d" % (a, n)

    in_code, prev = False, ""
    for ln in read(os.path.join(REPO, "docs/server-rules.md")):
        if ln.startswith("```"):
            in_code = not in_code
        m = None if in_code else re.match(r"(#{1,6})\s+(.*?)\s*$", ln)
        if m:
            if cur:
                secs.append((cur, cur_a, "\n".join(buf)))
            ex = re.match(r'<a id="([^"]+)"></a>\s*$', prev)
            slugged = anchor(m.group(2))
            cur, cur_a, buf = m.group(2), ex.group(1) if ex else slugged, []
        elif not re.match(r'<a id="[^"]+"></a>\s*$', ln):
            buf.append(ln)
        if ln.strip():
            prev = ln
    if cur:
        secs.append((cur, cur_a, "\n".join(buf)))
    return [x for x in secs if x[1] != "register"]


def generate(server):
    out = subprocess.run([server, "--list-apis"], capture_output=True, text=True, check=True).stdout
    apis = []
    for ln in out.splitlines():
        m, fid, by = ln.split("\t")
        apis.append((m, fid, by))
    mods = module_handlers()
    hk = hooks(server)
    tests = tests_calling()
    for k, v in replays_calling().items():
        tests[k] |= v
    docs = api_doc_entries()
    secs = rules_sections()
    o = []
    o.append("<!-- Generated by tools/server_index.py from soa-server --list-apis, the sources and the docs. Do not edit;")
    o.append("     regenerate: tools/server_index.py (tools/check_server_docs.sh reports a stale index). -->")
    o.append("# Local server: where is X")
    o.append("")
    o.append("Every API the 3.7.0 client can send, what answers it, and where its rules are written down. "
             "The layout and the request flow are in [ARCHITECTURE.md](ARCHITECTURE.md); the rules and their source labels in "
             "[docs/server-rules.md](../docs/server-rules.md); the client side of each API in [docs/api.md](../docs/api.md).")
    o.append("")
    o.append("## 1. APIs")
    o.append("")
    o.append("**Answered by**: the file whose `ext::add_core_api` (the core's APIs, registered first; marked *core*) or "
             "`ext::add_api` (a module's) registers it; **Handler** is the handler's definition. "
             "**Hooks** are the extension points that add to its response besides the two `OnResponse` hooks every answered "
             "response goes through (section 2). **Rules** are the `docs/server-rules.md` sections that name the method "
             "(at most four). **Tests** are the server tests that send it (by name in their body) and the replay corpora "
             "(`server/tests/replay/`).")
    o.append("")
    answered = [a for a in apis if a[2] != "-"]
    core_apis = core_registered()
    o.append("%d methods answered (%d by the core, %d by modules); %d more the wire knows with no handler (soa-server answers "
             "them `data.Time`)." % (len(answered), sum(1 for a in answered if a[0] in core_apis),
                                    sum(1 for a in answered if a[0] not in core_apis), len(apis) - len(answered)))
    o.append("")
    o.append("| Method | fid | Answered by | Handler | Hooks | Rules | docs/api.md | Tests |")
    o.append("|---|---|---|---|---|---|---|---|")
    load_hooks = "OnPlayerLoad (%d)" % len(hk["OnPlayerLoad"])
    for m, fid, by in answered:
        f, line, fn, body = mods.get(m, (by, 0, "?", ""))
        handler = "[%s:%d](%s#L%d) `%s`" % (os.path.basename(f), line, os.path.relpath(f, "server"), line, fn)
        h = []
        if "full_player_state(" in body or "api_player(" in body or "player_load(" in body:
            h.append(load_hooks)
        if "mission_start_extra" in body or (fn == "mission_start" and f.endswith("missions/mission_start.cpp")):
            h.append("MissionStartExtra (%d)" % len(hk["MissionStartExtra"]))
        if "mission_result_extra" in body or (fn == "mission_end" and f.endswith("missions/mission_end.cpp")):
            h.append("MissionResultExtra (%d)" % len(hk["MissionResultExtra"]))
        if "grant(" in body:
            h.append("Grant")
        if "item_info_list(" in body:
            h.append("ItemExtra")
        word = re.compile(r"`%s(?:\(|`)" % re.escape(m))
        rs = [(t, a) for t, a, txt in secs if word.search(txt) or word.search("`" + t)][:4]
        rules = "; ".join("[%s](../docs/server-rules.md#%s)" % (t.replace("|", "\\|").replace("`", ""), a) for t, a in rs) or "-"
        doc = "[%s](../docs/api.md#%s)" % (m, docs[m]) if m in docs else "-"
        ts = sorted(tests.get(m, ()))
        tcol = ", ".join("`%s`" % t for t in ts[:6]) + (" +%d" % (len(ts) - 6) if len(ts) > 6 else "") if ts else "-"
        by_col = os.path.basename(by) + (" *core*" if m in core_apis else "")
        o.append("| `%s` | `%s` | %s | %s | %s | %s | %s | %s |" % (m, fid, by_col,
                                                                  handler, ", ".join(h) or "-", rules, doc, tcol))
    o.append("")
    unanswered = [a for a in apis if a[2] == "-"]
    o.append("Not answered (%d): %s." % (len(unanswered), ", ".join("`%s`" % a[0] for a in unanswered)))
    o.append("")
    o.append("## 2. Hooks in run order")
    o.append("")
    o.append("Each module registers from its `register_<module>()` function, and `server/src/core/modules.cpp` calls those in "
             "one explicit list, so each kind runs in that list's order (`soa-server --list-hooks`; the test "
             "`server/module-order` pins it). `OnPlayerLoad` and `OnResponse` add keys to one response map, and maps keep "
             "insertion order on the wire, so this order is visible in the reply bytes (docs/history/PLAN-readability.md 1.3). "
             "The links are the registration lines.")
    o.append("")
    for kind, regs in hk.items():
        if not regs:
            continue
        o.append("- **%s** (%d): %s" % (kind, len(regs), "; ".join(
            "[%s:%d](%s#L%d)%s" % (os.path.basename(f), line, os.path.relpath(f, "server"), line, " (%s)" % d if d else "")
            for f, line, _, d in regs)))
    o.append("")
    o.append("## 3. Rules sections and the code that links them")
    o.append("")
    o.append("`docs/server-rules.md` sections linked (`docs/server-rules.md#anchor`) in `server/` comments.")
    o.append("")
    links = collections.defaultdict(set)
    for d, _, fs in os.walk(os.path.join(REPO, "server")):
        for f in fs:
            if not f.endswith((".cpp", ".h")):
                continue
            p = os.path.join(d, f)
            text = re.sub(r"\s*\n\s*//\s*", " ", open(p, encoding="utf-8", errors="replace").read())
            for t in re.findall(r'docs/server-rules\.md[,:]?\s*(?:section\s+)?"([^"]+)"', text):
                links[t].add(rel(p))
            for a in re.findall(r"docs/server-rules\.md#([A-Za-z0-9_-]+)", text):
                links["#" + a].add(rel(p))
    o.append("| Section | Linked from |")
    o.append("|---|---|")
    for t in sorted(links):
        o.append("| %s | %s |" % (t.replace("|", "\\|"), ", ".join("`%s`" % x for x in sorted(links[t]))))
    o.append("")
    return "\n".join(o)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--server", default=os.path.join(REPO, "build/server/soa-server"))
    ap.add_argument("--out", default=os.path.join(REPO, "server/API-INDEX.md"))
    ap.add_argument("--check", action="store_true")
    a = ap.parse_args()
    text = generate(a.server)
    if a.check:
        cur = open(a.out, encoding="utf-8").read() if os.path.exists(a.out) else ""
        if cur != text:
            print("server/API-INDEX.md is stale: run tools/server_index.py")
            return 1
        print("server/API-INDEX.md is fresh")
        return 0
    with open(a.out, "w", encoding="utf-8") as f:
        f.write(text)
    print("wrote %s" % rel(a.out))
    return 0


if __name__ == "__main__":
    sys.exit(main())
