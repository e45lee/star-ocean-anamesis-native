#!/usr/bin/env python3
"""The evidence manifest of the local server's sources (docs/history/PLAN-readability.md section 3).

    tools/server_evidence.py [--root DIR] [--json]          print the manifest of DIR/server
    tools/server_evidence.py --against REV [--root DIR]     compare DIR's manifest with git revision REV's

The manifest counts, in the comments of every server/ C++ file (string literals excluded):
  labels       the rule source labels (a) master data, (b) client-side evidence, (c) outside
               knowledge, (d) assumption, in the forms "(x)", "(x:", "; x:" and ", x:" (per file and in total);
  addresses    client addresses "@xxxxxxxx" (7-8 hex digits) in comments and strings, net/ninja/ (cipher
               constants) apart;
  symbols      client symbols "Class::member" in comments;
  offsets      "+0x..." offsets in comments;
  tables       master tables "master_..." named in comments;
  agents       "agent <name>" history notes in code;
  links        the docs/server-rules.md / docs/api.md sections quoted in comments ("Title") or
               linked by anchor (#anchor), and whether each resolves to a heading;
  log lines    the format strings of tools/server_log_patterns.txt still present in the sources;
  rules doc    the evidence of docs/server-rules.md and its history (docs/history/server-rules-history.md,
               R20): the labels, client addresses / symbols / offsets, master tables and `code` spans
               of the text, and every table row that carries a (c) or (d) label.

--check (with no --against) exits 10 on findings of the tree itself (a broken docs link, a quoted
docs/server-rules.md link, an "agent" note) and 11 when a log line of tools/server_log_patterns.txt
is gone; tools/check_server_docs.sh decides on these exit codes, not on the printed lines.

--against REV is RG10's evidence check: it exits 1 when, compared with REV, a label count fell, an
address appeared or went (outside net/ninja), a symbol / offset / table went missing, the agent
count grew, a log-line pattern went missing, a link stopped resolving, fewer docs/server-rules.md
links were used, or the rules doc (with its history) lost a label, a client address / symbol /
offset, a master table, a `code` span or a (c) / (d) row. Moved files and sections are fine:
the sets are compared over the whole tree. A commit that deletes code may lose labels; its message
then lists them (the check still reports them); with --waivers such a loss passes when each
commit of REV..HEAD that loses evidence carries its own "Evidence removed:" line (one commit's
line no longer waives another's loss, nor uncommitted changes).
"""
import argparse
import collections
import json
import os
import re
import subprocess
import sys
import tempfile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
EXIT_FINDINGS, EXIT_LOG_LINES = 10, 11  # --check's exit codes (anything else: the tool itself failed)
EXTS = (".cpp", ".h", ".inc", ".cc", ".hpp")

LABEL_RE = re.compile(r"\(([abcd])\)|\(([abcd]):|[;,] ([abcd]):")
ADDR_RE = re.compile(r"@([0-9a-f]{7,8})\b")
SYM_RE = re.compile(r"\b([A-Z]\w+::~?\w+)")
OFF_RE = re.compile(r"\+0x[0-9a-fA-F]+\b")
TABLE_RE = re.compile(r"\bmaster_[a-z0-9_]+\b")
AGENT_RE = re.compile(r"\bagents? `?([a-z0-9][a-z0-9-]*)`?")
RULES_DOCS = ("docs/server-rules.md", "docs/history/server-rules-history.md")
CODE_SPAN_RE = re.compile(r"`([^`\n]+)`")
QUOTED_LINK_RE = re.compile(r'docs/(server-rules|api)\.md[,:]?\s*(?:section\s+)?"([^"]+)"')
ANCHOR_LINK_RE = re.compile(r"docs/(server-rules|api)\.md#([A-Za-z0-9_-]+)")


def comments(src):
    """The comment text of a C++ source (strings, chars and raw strings skipped), as (line, text)."""
    out = []
    i, n, line = 0, len(src), 1
    while i < n:
        c = src[i]
        if c == "\n":
            line += 1
            i += 1
        elif src.startswith("//", i):
            j = src.find("\n", i)
            j = n if j < 0 else j
            out.append((line, src[i + 2:j]))
            i = j
        elif src.startswith("/*", i):
            j = src.find("*/", i + 2)
            j = n if j < 0 else j
            out.append((line, src[i + 2:j]))
            line += src.count("\n", i, j)
            i = j + 2
        elif c == "R" and i + 1 < n and src[i + 1] == '"' and (i == 0 or not (src[i - 1].isalnum() or src[i - 1] == "_")):
            k = src.find("(", i + 2)
            delim = src[i + 2:k]
            j = src.find(")" + delim + '"', k)
            j = n if j < 0 else j + len(delim) + 2
            line += src.count("\n", i, j)
            i = j
        elif c in "\"'":
            j = i + 1
            while j < n and src[j] != c and src[j] != "\n":
                j += 2 if src[j] == "\\" else 1
            i = j + 1
        else:
            i += 1
    return out


def comment_blocks(src):
    """The comments of consecutive lines joined into one text each (whitespace collapsed)."""
    blocks, last = [], None
    for line, text in comments(src):
        if last is not None and line <= last + 1 and blocks:
            blocks[-1] += " " + text
        else:
            blocks.append(text)
        last = line + text.count("\n")
    return [re.sub(r"\s+", " ", b) for b in blocks]


def code_without_comments(src):
    """The source with comments removed (strings kept): where log format strings live."""
    res, i, n = [], 0, len(src)
    while i < n:
        if src.startswith("//", i):
            j = src.find("\n", i)
            i = n if j < 0 else j
        elif src.startswith("/*", i):
            j = src.find("*/", i + 2)
            i = n if j < 0 else j + 2
        elif src[i] in "\"'":
            q, j = src[i], i + 1
            while j < n and src[j] != q and src[j] != "\n":
                j += 2 if src[j] == "\\" else 1
            res.append(src[i:j + 1])
            i = j + 1
        else:
            res.append(src[i])
            i += 1
    return "".join(res)


def slug(title):
    """GitHub's heading anchor."""
    s = title.strip().lower()
    s = re.sub(r"[^\w\- ]", "", s)
    return s.replace(" ", "-")


def headings(root, doc):
    p = os.path.join(root, "docs", doc + ".md")
    hs = set()
    if not os.path.exists(p):
        return hs, set()
    anchors, explicit = set(), set()
    in_code = False
    for ln in open(p, encoding="utf-8"):
        if ln.startswith("```"):
            in_code = not in_code
        if in_code:
            continue
        m = re.match(r"#+\s+(.*?)\s*#*\s*$", ln)
        if m:
            hs.add(m.group(1).strip())
            anchors.add(slug(m.group(1)))
        for a in re.findall(r'<a (?:id|name)="([^"]+)"', ln):
            explicit.add(a)
    # a doc with explicit anchors (docs/server-rules.md since R20) is linked by those only
    return hs, explicit or anchors


def link_ok(kind, target, heads):
    """Whether a quoted section title names a heading of the doc: the start of a heading, with or
    without its section number ("Clock" for "#### Clocks", "Entry flow" for "Entry flow: login,
    ..."); backticks ignored. Anchor links (#titles) must name a heading's anchor exactly."""
    hs, _ = heads[kind]
    t = target.strip().replace("`", "")
    for h in hs:
        h = h.replace("`", "")
        if h.startswith(t) or re.sub(r"^[\d.]+\s+", "", h).startswith(t):
            return True
    return False


def rules_doc(root):
    """The evidence of the rules doc and its history (R20): what a re-heading must keep. Fenced code
    blocks count too; a table row counts when it carries a (c) or (d) label (whitespace-normalized)."""
    d = {"labels": collections.Counter(), "addresses": set(), "symbols": set(), "offsets": collections.Counter(),
         "tables": set(), "spans": set(), "cd_rows": set()}
    for rel in RULES_DOCS:
        p = os.path.join(root, rel)
        if not os.path.exists(p):
            continue
        for ln in open(p, encoding="utf-8"):
            for g in LABEL_RE.findall(ln):
                d["labels"][next(x for x in g if x)] += 1
            d["addresses"].update(ADDR_RE.findall(ln))
            d["symbols"].update(SYM_RE.findall(ln))
            d["offsets"].update(OFF_RE.findall(ln))
            d["tables"].update(TABLE_RE.findall(ln))
            d["spans"].update(CODE_SPAN_RE.findall(ln))
            row = ln.strip()
            if row.startswith("|") and re.search(r"\([cd]\)", row):
                d["cd_rows"].add(re.sub(r"\s+", " ", row))
    return d


def manifest(root):
    server = os.path.join(root, "server")
    files = []
    for d, _, fs in os.walk(server):
        for f in fs:
            if f.endswith(EXTS):
                files.append(os.path.join(d, f))
    files.sort()
    heads = {doc: headings(root, doc) for doc in ("server-rules", "api")}
    m = {"files": {}, "labels": collections.Counter(), "addresses": collections.Counter(), "cipher_addresses": 0,
         "symbols": collections.Counter(), "offsets": collections.Counter(), "tables": collections.Counter(),
         "agents": 0, "links": {}, "log_lines": {}}
    all_code = []
    for p in files:
        rel = os.path.relpath(p, root)
        src = open(p, encoding="utf-8", errors="replace").read()
        cipher = "/net/ninja" in p or os.path.basename(p).startswith("ninja_")
        fm = {"labels": collections.Counter(), "addresses": 0, "symbols": 0, "offsets": 0, "agents": 0, "links": 0}
        for a in ADDR_RE.findall(src):
            if cipher:
                m["cipher_addresses"] += 1
            else:
                m["addresses"][a] += 1
                fm["addresses"] += 1
        for line, text in comments(src):
            for g in LABEL_RE.findall(text):
                lab = next(x for x in g if x)
                fm["labels"][lab] += 1
            for s in SYM_RE.findall(text):
                m["symbols"][s] += 1
                fm["symbols"] += 1
            for o in OFF_RE.findall(text):
                m["offsets"][o] += 1
                fm["offsets"] += 1
            for t in TABLE_RE.findall(text):
                m["tables"][t] += 1
        # an agent mention may wrap onto the next comment line: search each run of comments on
        # consecutive lines as one text
        for block in comment_blocks(src):
            fm["agents"] += len(AGENT_RE.findall(block))
        # links may span a comment line break: search the file's joined comment text
        joined = re.sub(r"\s+", " ", " ".join(t for _, t in comments(src)))
        for kind, title in QUOTED_LINK_RE.findall(joined):
            key = "docs/%s.md \"%s\"" % (kind, title)
            m["links"].setdefault(key, {"ok": link_ok(kind if kind == "api" else "server-rules", title, heads), "uses": []})
            m["links"][key]["uses"].append(rel)
            fm["links"] += 1
        for kind, anchor in ANCHOR_LINK_RE.findall(joined):
            key = "docs/%s.md#%s" % (kind, anchor)
            ok = anchor in heads[kind][1]
            m["links"].setdefault(key, {"ok": ok, "uses": []})
            m["links"][key]["uses"].append(rel)
            fm["links"] += 1
        m["labels"].update(fm["labels"])
        m["agents"] += fm["agents"]
        m["files"][rel] = {**fm, "labels": dict(fm["labels"])}
        all_code.append(code_without_comments(src))
    code = "\n".join(all_code)
    pats = os.path.join(root, "tools/server_log_patterns.txt")
    if not os.path.exists(pats):
        pats = os.path.join(REPO, "tools/server_log_patterns.txt")
    for ln in open(pats, encoding="utf-8"):
        if ln.startswith("#") or "\t" not in ln:
            continue
        frag = ln.split("\t", 1)[0]
        m["log_lines"][frag] = frag in code
    m["rules_doc"] = rules_doc(root)
    return m


def summary(m):
    lab = m["labels"]
    rd = m["rules_doc"]
    broken = [k for k, v in m["links"].items() if not v["ok"]]
    return [
        "files %d" % len(m["files"]),
        "labels (a) %d (b) %d (c) %d (d) %d" % (lab["a"], lab["b"], lab["c"], lab["d"]),
        "client addresses %d (%d distinct), plus %d cipher constants in net/ninja*" % (sum(m["addresses"].values()), len(m["addresses"]),
                                                                                          m["cipher_addresses"]),
        "client symbols %d (%d distinct)" % (sum(m["symbols"].values()), len(m["symbols"])),
        "+0x offsets %d" % sum(m["offsets"].values()),
        "master tables %d (%d distinct)" % (sum(m["tables"].values()), len(m["tables"])),
        "agent mentions %d" % m["agents"],
        "doc links %d uses, %d distinct, %d broken%s" % (sum(len(v["uses"]) for v in m["links"].values()), len(m["links"]), len(broken),
                                                        (": " + "; ".join(broken)) if broken else ""),
        "server-rules links quoted %d (anchors only since R20: docs/server-rules.md#anchor)" % sum(
            len(v["uses"]) for k, v in m["links"].items() if k.startswith('docs/server-rules.md "')),
        "rules doc labels (a) %d (b) %d (c) %d (d) %d; %d symbols, %d addresses, %d offsets, %d tables, %d code spans, %d (c)/(d) rows" % (
            rd["labels"]["a"], rd["labels"]["b"], rd["labels"]["c"], rd["labels"]["d"], len(rd["symbols"]), len(rd["addresses"]),
            sum(rd["offsets"].values()), len(rd["tables"]), len(rd["spans"]), len(rd["cd_rows"])),
        "log lines %d/%d present%s" % (sum(m["log_lines"].values()), len(m["log_lines"]),
                                       "" if all(m["log_lines"].values()) else " (missing: %s)" % "; ".join(k for k, v in m["log_lines"].items() if not v)),
    ]


EVIDENCE_PATHS = ("server", "docs/server-rules.md", "docs/api.md", "docs/history/server-rules-history.md",
                  "tools/server_log_patterns.txt")


def at_rev(rev, git=REPO):
    d = tempfile.mkdtemp(prefix="server-evidence.")
    paths = [p for p in EVIDENCE_PATHS
             if subprocess.run(["git", "cat-file", "-e", "%s:%s" % (rev, p)], cwd=git, capture_output=True).returncode == 0]
    a = subprocess.run(["git", "archive", rev] + paths, cwd=git, capture_output=True, check=True)
    subprocess.run(["tar", "-x", "-C", d], input=a.stdout, check=True)
    return d


def manifest_at(rev, git=REPO):
    d = at_rev(rev, git)
    try:
        return manifest(d)
    finally:
        subprocess.run(["rm", "-rf", d])


def git_out(git, *args):
    return subprocess.run(["git"] + list(args), cwd=git, capture_output=True, text=True, check=True).stdout


WAIVER = re.compile(r"^Evidence removed:", re.M)


def unwaived(rev, current, git=REPO):
    """For a loss against REV: each commit of REV..HEAD (merges aside: their parents' commits are in
    the range) that loses evidence against its parent must say so itself (an "Evidence removed:"
    line in its message); so must uncommitted changes, which have no message. Returns the
    problems no commit's own message covers ([] = every loss waived by the commit that made it),
    and the waivers that counted, as lines."""
    commits = git_out(git, "rev-list", "--no-merges", "--reverse", "%s..HEAD" % rev, "--", *EVIDENCE_PATHS).split()
    bad, waived, cache = [], [], {}

    def man(r):
        if r not in cache:
            cache[r] = manifest_at(r, git)
        return cache[r]
    for c in commits:
        parents = git_out(git, "rev-list", "--parents", "-n", "1", c).split()[1:]
        if not parents:
            continue  # a root commit loses nothing
        probs = against(man(parents[0]), man(c))
        if not probs:
            continue
        msg = git_out(git, "log", "-1", "--format=%B", c)
        subject = "%s %s" % (c[:10], msg.splitlines()[0] if msg else "")
        if WAIVER.search(msg):
            waived.append(subject + ": " + "; ".join(probs))
            waived += ["    " + ln for ln in msg.splitlines() if WAIVER.match(ln)]
        else:
            bad += ["%s (its message has no \"Evidence removed:\" line): %s" % (subject, p) for p in probs]
    probs = against(man(git_out(git, "rev-parse", "HEAD").strip()), current)
    bad += ["uncommitted changes (commit them with an \"Evidence removed:\" line): %s" % p for p in probs]
    if not bad and not waived:
        bad.append("lost across the range though no single commit loses it (a merge's resolution?)")
    return bad, waived


def check(m):
    """--check: the problems of this tree on its own (not against a revision), as (findings, hard):
    findings are broken docs links, quoted docs/server-rules.md links and "agent" history notes;
    hard is a log line scripts wait on that is gone from the sources."""
    findings = []
    broken = [k for k, v in m["links"].items() if not v["ok"]]
    if broken:
        findings.append("doc links broken: %s" % "; ".join(broken))
    quoted = sum(len(v["uses"]) for k, v in m["links"].items() if k.startswith('docs/server-rules.md "'))
    if quoted:
        findings.append("server-rules links quoted: %d (use anchors: docs/server-rules.md#anchor)" % quoted)
    if m["agents"]:
        findings.append("agent mentions: %d (%s)" % (m["agents"], ", ".join(f for f, fm in m["files"].items() if fm["agents"])))
    hard = ["log line gone: %s" % k for k, v in m["log_lines"].items() if not v]
    return findings, hard


def against(old, new):
    """The problems of new compared with old (section 3's table)."""
    probs = []
    for lab in "abcd":
        if new["labels"][lab] < old["labels"][lab]:
            probs.append("labels (%s): %d -> %d" % (lab, old["labels"][lab], new["labels"][lab]))
    # (addresses added are new evidence, not a loss: only the gone ones count, as for the symbols)
    gone = sorted(set(old["addresses"]) - set(new["addresses"]))
    if gone:
        added = sorted(set(new["addresses"]) - set(old["addresses"]))
        probs.append("client addresses changed: gone %s, new %s" % (gone, added))
    gone = sorted(set(old["symbols"]) - set(new["symbols"]))
    if gone:
        probs.append("client symbols gone: %s" % ", ".join(gone))
    lost = old["offsets"] - new["offsets"]
    if lost:
        probs.append("+0x offsets gone: %s" % ", ".join("%s x%d" % kv for kv in sorted(lost.items())))
    gone = sorted(set(old["tables"]) - set(new["tables"]))
    if gone:
        probs.append("master tables gone from comments: %s" % ", ".join(gone))
    if new["agents"] > old["agents"]:
        probs.append("agent mentions: %d -> %d" % (old["agents"], new["agents"]))
    for k, v in new["log_lines"].items():
        if not v and old["log_lines"].get(k, False):
            probs.append("log line gone: %s" % k)
    for k, v in new["links"].items():
        if not v["ok"] and old["links"].get(k, {}).get("ok", False):
            probs.append("link broken: %s" % k)
    uses = lambda m: sum(len(v["uses"]) for k, v in m["links"].items() if k.startswith("docs/server-rules.md"))
    if uses(new) < uses(old):
        probs.append("docs/server-rules.md links used: %d -> %d" % (uses(old), uses(new)))
    o, n = old["rules_doc"], new["rules_doc"]
    for lab in "abcd":
        if n["labels"][lab] < o["labels"][lab]:
            probs.append("rules doc labels (%s): %d -> %d" % (lab, o["labels"][lab], n["labels"][lab]))
    for key, what in (("addresses", "client addresses"), ("symbols", "client symbols"), ("tables", "master tables"),
                      ("spans", "code spans"), ("cd_rows", "(c)/(d) rows")):
        gone = sorted(o[key] - n[key])
        if gone:
            probs.append("rules doc %s gone: %s" % (what, "; ".join(gone)))
    lost = o["offsets"] - n["offsets"]
    if lost:
        probs.append("rules doc +0x offsets gone: %s" % ", ".join("%s x%d" % kv for kv in sorted(lost.items())))
    return probs


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--root", default=REPO, help="the checkout (default this one)")
    ap.add_argument("--against", metavar="REV", help="compare with git revision REV")
    ap.add_argument("--json", action="store_true", help="print the whole manifest as JSON")
    ap.add_argument("--files", action="store_true", help="print the per-file counts")
    ap.add_argument("--check", action="store_true",
                    help="exit %d on broken / quoted docs links or agent mentions, %d on a missing log line "
                         "(tools/check_server_docs.sh)" % (EXIT_FINDINGS, EXIT_LOG_LINES))
    ap.add_argument("--waivers", action="store_true",
                    help="with --against: a loss passes when every commit of REV..HEAD that makes one says "
                         "\"Evidence removed:\" in its own message (tools/check_server_docs.sh)")
    a = ap.parse_args()
    root = os.path.abspath(a.root)
    m = manifest(root)
    if a.json:
        print(json.dumps(m, indent=1, sort_keys=True, default=lambda x: sorted(x) if isinstance(x, set) else dict(x)))
        return 0
    if not a.against:
        for ln in summary(m):
            print(ln)
        if a.check:
            findings, hard = check(m)
            for p in findings + hard:
                print("CHECK: " + p)
            return EXIT_LOG_LINES if hard else EXIT_FINDINGS if findings else 0
        if a.files:
            for f, fm in m["files"].items():
                lab = fm["labels"]
                print("%-48s a %3d b %3d c %3d d %3d  addr %3d sym %3d off %3d agent %2d links %2d" % (
                    f, lab.get("a", 0), lab.get("b", 0), lab.get("c", 0), lab.get("d", 0), fm["addresses"], fm["symbols"], fm["offsets"],
                    fm["agents"], fm["links"]))
        return 0
    old = manifest_at(a.against, root)
    probs = against(old, m)
    print("evidence vs %s:" % a.against)
    for o, n in zip(summary(old), summary(m)):
        print("  %s\n  -> %s" % (o, n) if o != n else "  %s (same)" % n)
    if probs:
        print("LOST:")
        for p in probs:
            print("  " + p)
        if a.waivers:
            bad, waived = unwaived(a.against, m, root)
            if waived:
                print("waived by the commits that lost it:")
                for ln in waived:
                    print("  " + ln)
            if bad:
                print("NOT WAIVED:")
                for p in bad:
                    print("  " + p)
                return 1
            print("every loss is waived by its own commit's \"Evidence removed:\" line")
            return 0
        return 1
    print("nothing lost")
    return 0


if __name__ == "__main__":
    sys.exit(main())
