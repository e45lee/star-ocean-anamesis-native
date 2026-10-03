#!/usr/bin/env python3
"""Inventory of the local server's state schema (DATA/server.sqlite3), generated from the code.

    tools/schema_inventory.py [--state LABEL=DB ...] [--update server/PLAN-schema.md]

What it does (server/PLAN-schema.md, section 1, is its output):
  1. Collects every C++ string literal in server/{src,net,include} (adjacent literals joined, raw
     strings included, comments skipped), splits them into SQL statements and parses each
     `create table if not exists` (table, columns, types, defaults, keys, the file:line that
     creates it). Tables created only by tests (server/tests, src/**/*_tests.cpp) are listed apart.
  2. Classifies every other statement that names a state table: a write (insert / replace /
     update / delete) or a read (select ... from / join, sub-selects included), with the columns
     it names (an `insert ... values` without a column list writes every column, `select *` reads
     every column). A column name shared by two tables of one statement counts for both, so the
     read / write sets are an over-approximation: a column listed as never read is never named.
     Statements built at run time (`"... from " + t`) are listed as dynamic.
  3. Attributes each statement to its enclosing function (the nearest preceding definition line,
     or the NATIVE_TEST it sits in: those count as tests, not as readers / writers).
  4. Lists the key-value keys (meta, sphere_meta, counters) with their writers and readers, from
     the SQL literals and the helper calls (state/state.h meta / set_meta / next_uid, api/sphere211/
     sphere_meta(ctx, ..) / set_sphere_meta(ctx, ..), ext count / counter).
  5. Greps the consumers outside the server (tools/, tests/, port/scripts, emulator/scripts,
     control/, scripts/) for the tables they name.
  6. With --state, the row counts of each table (and the meta / sphere_meta / counters rows) in
     real state DBs.

Output: markdown on stdout, or with --update FILE the text between the markers
`<!-- inventory:begin -->` and `<!-- inventory:end -->` in FILE is replaced.

    tools/schema_inventory.py --lint

The SQL hygiene gate of server/PLAN-schema.md S0 (F9): every INSERT into a state table names its
columns, and no future FK parent (LINT_UPSERT_ONLY) is written with INSERT OR REPLACE (a delete
plus an insert: with foreign keys on, it would run the children's ON DELETE actions); use
`insert ... on conflict(pk) do update set` instead. Checks server/ (the joined literals) and the
consumers' SQL (port/scripts, emulator/scripts, tools, tests: line by line). Exit 1 on a finding.
"""
import argparse
import collections
import os
import re
import sqlite3
import sys

ROOT = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
SERVER_DIRS = ["server/src", "server/net", "server/include", "server/app"]
TEST_DIRS = ["server/tests"]
CONSUMER_DIRS = ["tools", "tests", "port/scripts", "emulator/scripts", "control", "scripts"]
KV_TABLES = ("meta", "sphere_meta", "counters")
# Files whose SQL runs on another DB (not the state): their statements are not state uses.
OTHER_DB = {"server/src/master/gacha_pools.cpp": "data/gacha_pools.sqlite3 (its own meta table)"}


def rel(p):
    return os.path.relpath(p, ROOT)


def test_file(r):
    """A test source: under server/tests, or a library test beside its code (src/**/*_tests.cpp)."""
    return r.startswith("server/tests") or re.search(r"_tests?\.cpp$", r) is not None


def files(dirs, exts):
    for d in dirs:
        for base, _, fs in os.walk(os.path.join(ROOT, d)):
            for f in sorted(fs):
                if f.endswith(exts):
                    yield os.path.join(base, f)


# ---- C++ string literals -------------------------------------------------------------------
SPLICE_RE = re.compile(r'"\)?\s*\+\s*([A-Za-z_]\w*)(?:\[[^\]\n]*\])?\s*\+\s*(?:std::string\()?"')


def splice(src):
    """`"... set " + col + " = ?"` -> `"... set {col} = ?"` (same line count), so a statement
    with a run-time column name stays one statement; analyse() expands {col}. A splice may span
    a line break (`... + s +` / `".master_text ..."`, however the code is wrapped): the newlines
    it removes are put back at the end of that line, so later lines keep their numbers."""
    out, pos, owed = [], 0, 0
    for m in SPLICE_RE.finditer(src):
        chunk = src[pos:m.start()]
        if owed and "\n" in chunk:
            k = chunk.index("\n")
            chunk = chunk[:k] + "\n" * owed + chunk[k:]
            owed = 0
        out.append(chunk)
        out.append("{%s}" % m.group(1))
        owed += m.group(0).count("\n")
        pos = m.end()
    rest = src[pos:]
    if owed:
        k = rest.find("\n")
        rest = rest + "\n" * owed if k < 0 else rest[:k] + "\n" * owed + rest[k:]
    out.append(rest)
    return "".join(out)


def resolve(src, var, upto):
    """The string literals a variable can hold: its last assignment / initializer before
    offset `upto` (`const char* col = weapon ? "weapon_uid" : "accessory_uid";`,
    `kStats[7] = {"hp", ...}`)."""
    best = None
    for m in re.finditer(r"\b%s\b(?:\[\d*\])?\s*=\s*([^;]*);" % re.escape(var), src[:upto] if upto else src):
        best = m
    if not best:
        for m in re.finditer(r"\b%s\b(?:\[\d*\])?\s*=\s*([^;]*);" % re.escape(var), src):
            best = m
            break
    return re.findall(r'"(\w+)"', best.group(1)) if best else []


def literal_groups(src):
    """[(line, text, dynamic)]: runs of adjacent string literals (only whitespace / comments
    between them) joined; `dynamic` when the run is followed or preceded by `+` (built at run
    time)."""
    out = []
    i, n, line = 0, len(src), 1
    cur, cur_line, last_end = None, 0, 0

    def flush(end_pos):
        nonlocal cur
        if cur is not None:
            before = src[max(0, cur_start - 3):cur_start].strip()
            after = src[end_pos:end_pos + 3].strip()
            dyn = before.endswith("+") or after.startswith("+")
            out.append((cur_line, "".join(cur), dyn))
        cur = None

    cur_start = 0
    while i < n:
        c = src[i]
        if c == "\n":
            line += 1
            i += 1
            continue
        if src.startswith("//", i):
            j = src.find("\n", i)
            i = n if j < 0 else j
            continue
        if src.startswith("/*", i):
            j = src.find("*/", i + 2)
            j = n if j < 0 else j + 2
            line += src.count("\n", i, j)
            i = j
            continue
        if c == "'":  # char literal
            j = i + 1
            while j < n and src[j] != "'":
                j += 2 if src[j] == "\\" else 1
            i = j + 1
            continue
        if c == "R" and src.startswith('R"', i) and (i == 0 or not (src[i - 1].isalnum() or src[i - 1] == "_")):
            k = src.find("(", i + 2)
            delim = src[i + 2:k]
            endm = ")" + delim + '"'
            j = src.find(endm, k + 1)
            text = src[k + 1:j]
            if cur is None:
                cur, cur_line, cur_start = [], line, i
            cur.append(text)
            line += text.count("\n")
            i = j + len(endm)
            last_end = i
            continue
        if c == '"':
            j = i + 1
            buf = []
            while j < n and src[j] != '"':
                if src[j] == "\\":
                    buf.append({"n": " ", "t": " ", '"': '"', "\\": "\\"}.get(src[j + 1], src[j + 1]))
                    j += 2
                else:
                    buf.append(src[j])
                    j += 1
            if cur is None:
                cur, cur_line, cur_start = [], line, i
            cur.append("".join(buf))
            i = j + 1
            last_end = i
            continue
        if not c.isspace() and cur is not None:
            flush(last_end)
        i += 1
    flush(last_end)
    return out


DEF_RE = re.compile(r"^(\s{0,4})(?!(if|for|while|switch|return|else|do|case)\b)[A-Za-z_][\w:<>,\s\*&~\[\]]*\([^;]*\)\s*(const\s*)?(override\s*)?\{\s*$")
ONELINE_RE = re.compile(r"^\s{0,4}(?!(if|for|while|switch|return|else|do|case)\b)(static\s+)?[A-Za-z_][\w:<>,\*&~]*(\s+[\w:<>,\*&~]+)*\s+[\w:~]+\([^;{]*\)\s*(const\s*)?\{.*\}\s*$")
TEST_RE = re.compile(r'^NATIVE_TEST\("([^"]+)"\)|^SOASERVER_TEST\("([^"]+)"\)|^\s*TEST\("([^"]+)"')
REG_RE = re.compile(r'^\s*(?:ext::)?(Api|OnPlayerLoad|OnResponse|Grant|ItemExtra|MissionStartExtra|MissionResultExtra|ClientMaster)\s+(\w+)\s*\((.*)')


def function_index(lines):
    """For each line number (1-based): (context name, is_test)."""
    ctx = [("(file scope)", False)] * (len(lines) + 2)
    cur = ("(file scope)", False)
    for k, l in enumerate(lines, 1):
        m = TEST_RE.match(l)
        if m:
            cur = ("test " + next(g for g in m.groups() if g), True)
        else:
            m = REG_RE.match(l)
            if m:
                meth = re.findall(r'"(\w+)"', m.group(3))
                cur = ("%s %s%s" % (m.group(1), m.group(2), (" " + "/".join(meth)) if meth else ""), False)
            elif DEF_RE.match(l) and "=" not in l.split("(")[0]:
                name = re.findall(r"([\w:~]+)\s*\(", l)
                if name:
                    cur = (name[0], False)
            elif ONELINE_RE.match(l) and "=" not in l.split("(")[0]:
                # a one-line definition: its own context for this line only
                ctx[k] = (re.findall(r"([\w:~]+)\s*\(", l)[0], cur[1])
                continue
        ctx[k] = cur
    return ctx


# ---- SQL -----------------------------------------------------------------------------------
CREATE_RE = re.compile(r"create\s+table\s+if\s+not\s+exists\s+(\w+)\s*\(", re.I)


def split_top(s):
    parts, depth, cur = [], 0, []
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        parts.append("".join(cur).strip())
    return parts


def parse_creates(text):
    out = []
    for m in CREATE_RE.finditer(text):
        depth, j = 1, m.end()
        while j < len(text) and depth:
            depth += {"(": 1, ")": -1}.get(text[j], 0)
            j += 1
        body = text[m.end():j - 1]
        cols, cons = [], []
        for p in split_top(body):
            w = p.split()
            if w[0].lower() in ("primary", "unique", "foreign", "check", "constraint"):
                cons.append(" ".join(w))
            else:
                cols.append((w[0], " ".join(w[1:])))
        out.append((m.group(1), cols, cons, m.start()))
    return out


WRITE_RE = re.compile(r"\b(insert(?:\s+or\s+\w+)?\s+into|replace\s+into|update|delete\s+from)\s+(\w+)", re.I)
READ_RE = re.compile(r"\b(from|join)\s+(\w+)", re.I)
IDENT_RE = re.compile(r"[A-Za-z_]\w*")


def statements(text):
    for s in text.split(";"):
        s = " ".join(s.split())
        if re.search(r"\b(select|insert|update|delete|replace|create)\b", s, re.I):
            yield s


def star_columns(src):
    """Names a `select *` row callback can read in this file: every string literal (Row
    accessors r.i("col")), plus prefixes concatenated at run time ("skill" + k, "add_" + k)."""
    lits = set(re.findall(r'"(\w+)"', src))
    prefixes = set(re.findall(r'"(\w+)"\)?\s*\+', src))
    return lambda col: col in lits or any(col.startswith(p) and len(p) >= 3 for p in prefixes)


def analyse(stmt, tables, star=lambda col: True):
    """[(table, 'w'|'r', written cols, read cols)] for the state tables the statement names."""
    res = []
    low = stmt.lower()
    if low.startswith("create"):
        return res
    names = set()
    writes = {}
    for m in WRITE_RE.finditer(stmt):
        t = m.group(2)
        if t in tables:
            writes[t] = m
            names.add(t)
    reads = set()
    for m in READ_RE.finditer(stmt):
        t = m.group(2)
        if t in tables:
            # "delete from t" is a write, not a read
            if t in writes and writes[t].group(1).lower().startswith("delete") and writes[t].start() <= m.start() <= writes[t].end():
                continue
            reads.add(t)
            names.add(t)
    idents = set(IDENT_RE.findall(stmt))
    for t in sorted(names):
        cols = [c for c, _ in tables[t]["cols"]]
        wcols, rcols = set(), set()
        if t in writes:
            kind = writes[t].group(1).lower()
            after = stmt[writes[t].end():]
            if kind.startswith(("insert", "replace")):
                m = re.match(r"\s*\(([^)]*)\)", after)
                if m and not re.match(r"\s*\(\s*select", after, re.I):
                    wcols = {c.strip() for c in m.group(1).split(",")} & set(cols)
                else:
                    wcols = set(cols)
                m2 = re.search(r"\bdo\s+update\s+set\s+(.*?)(\bwhere\b|$)", after, re.I)
                if m2:
                    wcols |= {a.split("=")[0].strip() for a in split_top(m2.group(1))} & set(cols)
            elif kind == "update":
                m = re.search(r"\bset\s+(.*?)(\bwhere\b|$)", after, re.I)
                if m:
                    wcols = {a.split("=")[0].strip() for a in split_top(m.group(1))} & set(cols)
            elif kind.startswith("delete"):
                wcols = set(cols)  # the row goes
        if t in reads or (t in writes and not writes[t].group(1).lower().startswith(("insert", "replace"))):
            if re.search(r"select\s+\*", stmt, re.I) and t in reads:
                rcols |= {c for c in cols if star(c)}
            rcols |= (idents & set(cols)) - (wcols if t not in reads else set())
        if t in reads and t not in writes:
            rcols |= idents & set(cols)
        res.append((t, "w" if t in writes else "r", wcols, rcols, t in reads))
    return res


# ---- relationships ---------------------------------------------------------------------------
# (child table, child column, parent, parent column, none sentinel, proposed ON DELETE, note).
# parent "m:<table>" is in the read-only master DB (not enforceable by SQLite across files);
# several "m:" tables separated by "|" = the id is one of them (a union of id spaces). A column
# holding "a,b,c" lists is checked element-wise with a "list:" prefix on the column.
RELS = [
    ("player", "home_uid", "roster", "uid", 0, "SET NULL", "home character (the client falls back to party 1's leader)"),
    ("player", "party_id", "party_set", "party_id", 0, "NO ACTION, deferred", "current party set (party has no unique party_id)"),
    ("roster", "role_id", "m:master_role", "id", None, "-", ""),
    ("roster", "weapon_uid", "items", "uid", 0, "SET NULL", "equipped weapon"),
    ("roster", "accessory_uid", "items", "uid", 0, "SET NULL", "equipped accessory"),
    ("roster_ext", "uid", "roster", "uid", None, "merged (S4)", "1:1 extension"),
    ("items", "master_item_id", "m:master_item", "id", None, "-", ""),
    ("stock", "master_item_id", "m:master_item", "id", None, "-", ""),
    ("gear_items", "item_uid", "items", "uid", 0, "CASCADE", "gear attached to a weapon (0: in the gear box)"),
    ("gear_items", "master_item_id", "m:master_item", "id", None, "-", "gear kind (api/items/gear.cpp reads master_item for it)"),
    ("party", "uid", "roster", "uid", 0, "SET NULL (as party_member.uid, S6)", "member"),
    ("party_member", "party_id", "party_set", "party_id", None, "CASCADE", "slot details of a set"),
    ("party_member", "weapon_uid", "items", "uid", 0, "SET NULL", ""),
    ("party_member", "accessory_uid", "items", "uid", 0, "SET NULL", ""),
    ("party_member", "assist_uid", "roster", "uid", 0, "SET NULL", ""),
    ("assist", "uid", "roster", "uid", None, "merged (S4): roster.assist_uid", ""),
    ("assist", "assist_uid", "roster", "uid", None, "SET NULL (roster.assist_uid)", ""),
    ("mission", "mission_id", "m:master_mission|master_event_mission|master_world_map_mission|master_tower_mission", "id", None, "-",
     "four disjoint id spaces (the tower's floors too: S0 found them in the tower replay)"),
    ("unlocks", "mission_id", "m:master_mission|master_event_mission|master_world_map_mission|master_tower_mission", "id", None, "-", ""),
    ("unlocks", "by_mission", "m:master_mission|master_event_mission|master_world_map_mission|master_tower_mission", "id", 0, "-", ""),
    ("unlocks", "by_mission", "mission", "mission_id", 0, "NO ACTION, deferred", "the mission whose clear opened it"),
    ("play", "mission_id", "m:master_mission|master_event_mission|master_world_map_mission|master_tower_mission|master_deep_space_mission", "id", 0, "-", ""),
    ("play_ext", "id", "play", "id", None, "merged (S7)", "1:1 extension"),
    ("play", "list:uids", "roster", "uid", 0, "SET NULL (play_member.uid, S7)", "party of the battle (0x7f0000xx: NPCs)"),
    ("gacha_history", "gacha_id", "m:master_gacha", "id", None, "-", ""),
    ("gacha_history", "role_id", "m:master_role", "id", 0, "-", ""),
    ("gacha_history", "uid", "roster|items", "uid", 0, "SET NULL (split: character_uid / item_uid, S10)", "a character uid, or an item uid for a weapon draw (role_id 0)"),
    ("stepup", "head", "m:master_gacha", "id", None, "-", ""),
    ("box_state", "gacha_id", "m:master_gacha", "id", None, "-", ""),
    ("box_slots", "gacha_id", "box_state", "gacha_id", None, "CASCADE", ""),
    ("present_texts", "id", "presents", "id", None, "merged (S8)", ""),
    ("login_bonus", "id", "m:master_login_bonus", "id", None, "-", ""),
    ("achievements", "id", "m:master_achievement", "id", None, "-", ""),
    ("titles", "id", "m:master_title", "id", None, "-", ""),
    ("premium_pass", "id", "m:master_premium_login_bonus", "id", None, "-", ""),
    ("subscription", "plan_id", "m:master_subscription_plan", "id", None, "-", ""),
    ("favor", "same_role_id", "m:master_role", "same_role_id", None, "-", "favor per same role"),
    ("favor_drop_play", "same_role_id", "m:master_role", "same_role_id", None, "-", ""),
    ("favor_bonus_state", "lot_uid", "roster", "uid", 0, "SET NULL", "the favor bonus character"),
    ("shop_counts", "id", "m:master_item_shop", "id", None, "-", ""),
    ("exchange_counts", "shop_id", "m:master_exchange_shop", "id", None, "-", ""),
    ("ds_area", "area_id", "m:master_deep_space_area", "id", None, "-", ""),
    ("ds_offer", "mission_id", "m:master_deep_space_mission", "id", None, "-", ""),
    ("ds_offer", "area_id", "ds_area", "area_id", None, "CASCADE", ""),
    ("ds_offer", "ship_id", "ds_ship", "ship_id", 0, "SET NULL", ""),
    ("ds_ship", "area_id", "ds_area", "area_id", None, "CASCADE", ""),
    ("ds_ship", "list:uids", "roster", "uid", 0, "NO ACTION (ds_ship_member.uid, S7)", "the ship's crew"),
    ("ds_bonus", "ship_id", "ds_ship", "ship_id", None, "CASCADE", ""),
    ("sphere_departed", "uid", "roster", "uid", None, "CASCADE", ""),
    ("sphere_cell", "asset_id", "m:master_sphere211_floor_asset", "id", None, "-", ""),
    ("sphere", "season_id", "m:master_sphere211", "id", 0, "-", ""),
    ("wboss", "boss_id", "m:master_world_boss", "id", None, "-", ""),
    ("wboss_clear", "boss_id", "wboss", "boss_id", None, "CASCADE", ""),
    ("event_rank_score", "ranking_id", "m:master_event_ranking", "id", None, "-", ""),
    ("event_rank_received", "group_id", "m:master_event_ranking_group", "id", None, "-", ""),
    ("wire_device", "player_id", "player", "id", 0, "SET NULL", ""),
    ("meta", "kv:support_uid", "roster", "uid", 0, "SET NULL (player.support_uid, S3)", "Player.support_pc_id"),
    ("meta", "kv:title", "titles", "id", 0, "SET NULL (player.title_id, S3)", "Player.title"),
]


def fk_report(st_path, master_path):
    c = sqlite3.connect("file:%s?mode=ro" % st_path, uri=True)
    if master_path and os.path.exists(master_path):
        c.execute("attach database ? as m", ("file:%s?mode=ro" % master_path,))
    have = {n for (n,) in c.execute("select name from sqlite_master where type = 'table'")}
    mhave = {n for (n,) in c.execute("select name from m.sqlite_master where type = 'table'")} if master_path else set()
    out = []
    for ch, col, par, pcol, none, act, note in RELS:
        if ch not in have:
            out.append((ch, col, par, pcol, none, act, "table absent", "", "", ""))
            continue
        if par.startswith("m:"):
            parents = [p for p in par[2:].split("|") if p in mhave]
            if not parents:
                out.append((ch, col, par, pcol, none, act, "master absent", "", "", ""))
                continue
            pset = set()
            for p in parents:
                pset |= {r[0] for r in c.execute('select "%s" from m."%s"' % (pcol, p))}
        else:
            parents = [p for p in par.split("|") if p in have]
            if not parents:
                out.append((ch, col, par, pcol, none, act, "parent absent", "", "", ""))
                continue
            pset = set()
            for p in parents:
                pset |= {r[0] for r in c.execute('select "%s" from "%s"' % (pcol, p))}
        if col.startswith("kv:"):
            vals = [int(v) for (v,) in c.execute("select value from meta where key = ?", (col[3:],)) if str(v).lstrip("-").isdigit()]
        elif col.startswith("list:"):
            vals = []
            for (v,) in c.execute('select "%s" from "%s"' % (col[5:], ch)):
                vals += [int(x) for x in str(v or "").replace(";", ",").split(",") if x.strip().lstrip("-").isdigit()]
        else:
            vals = [r[0] for r in c.execute('select "%s" from "%s"' % (col, ch))]
        n = len(vals)
        nnull = sum(1 for v in vals if v is None)
        nzero = sum(1 for v in vals if none is not None and v == none)
        bad = sorted({v for v in vals if v is not None and not (none is not None and v == none) and v not in pset})
        if col == "list:uids":
            npc = [v for v in bad if 0x7f000000 <= v < 0x7f100000]
            bad = [v for v in bad if v not in npc]
            note = (note + "; %d NPC uids" % len(npc)) if npc else note
        out.append((ch, col, par, pcol, none, act, n, nnull, nzero, bad))
    return out


# Tables written only by upsert (S0): the parents of the target schema's foreign keys (section 3.2:
# player, roster, items, titles, party_set, mission, box_state, presents, ds_area, ds_ship, wboss)
# and the other tables of F9's REPLACE list (party, party_member, favor, stock, subscription,
# present_texts).
LINT_UPSERT_ONLY = ("player", "roster", "items", "titles", "party_set", "mission", "box_state", "presents", "ds_area", "ds_ship",
                    "wboss", "party", "party_member", "favor", "stock", "subscription", "present_texts")
# Consumers whose SQL runs on another DB: the pools DB's builder (its own meta table).
LINT_OTHER_DB = ("tools/build_gacha_pools.py",)
POSITIONAL_RE = re.compile(r"\b(?:insert(?:\s+or\s+\w+)?|replace)\s+into\s+(\w+)\s+values\b", re.I)
REPLACE_RE = re.compile(r"\b(?:insert\s+or\s+replace|replace)\s+into\s+(\w+)\b", re.I)


def lint():
    """The S0 gate (module docstring): a list of "file:line: finding" strings."""
    state = set()
    for path in list(files(SERVER_DIRS, (".cpp", ".h"))) + list(files(TEST_DIRS, (".cpp", ".h"))):
        if rel(path) in OTHER_DB:
            continue
        for line, text, dyn in literal_groups(open(path, encoding="utf-8", errors="replace").read()):
            state |= {name for name, _, _, _ in parse_creates(text)}
    found = []

    def check(where, stmt):
        for m in POSITIONAL_RE.finditer(stmt):
            if m.group(1) in state:
                found.append("%s: insert into %s without a column list" % (where, m.group(1)))
        for m in REPLACE_RE.finditer(stmt):
            if m.group(1) in LINT_UPSERT_ONLY:
                found.append("%s: insert or replace into %s (a future FK parent: upsert)" % (where, m.group(1)))

    for path in list(files(SERVER_DIRS, (".cpp", ".h"))) + list(files(TEST_DIRS, (".cpp", ".h"))):
        if rel(path) in OTHER_DB:
            continue
        for line, text, dyn in literal_groups(open(path, encoding="utf-8", errors="replace").read()):
            for st in statements(text):
                check("%s:%d" % (rel(path), line), st)
    for path in files(CONSUMER_DIRS, (".sh", ".py")):
        if rel(path) in LINT_OTHER_DB or rel(path) == "tools/schema_inventory.py":
            continue
        for k, l in enumerate(open(path, encoding="utf-8", errors="replace"), 1):
            check("%s:%d" % (rel(path), k), l)
    return found


def main():
    if sys.argv[1:] == ["--lint"]:
        found = lint()
        for f in found:
            print(f)
        print("schema_inventory --lint: %s" % ("%d finding(s)" % len(found) if found else "clean"))
        sys.exit(1 if found else 0)
    ap = argparse.ArgumentParser()
    ap.add_argument("--state", action="append", default=[], help="LABEL=PATH of a state DB for row counts")
    ap.add_argument("--master", default=os.path.join(ROOT, "data", "basmaster-3.7.0.sqlite3"))
    ap.add_argument("--update", help="replace the inventory between the markers in this file")
    a = ap.parse_args()

    tables = collections.OrderedDict()
    test_tables = collections.OrderedDict()
    uses = []  # (table, file, line, ctx, is_test, kind, wcols, rcols, stmt)
    dynamic = []
    src_cache = {}
    for path in list(files(SERVER_DIRS, (".cpp", ".h"))) + list(files(TEST_DIRS, (".cpp", ".h"))):
        src = open(path, encoding="utf-8", errors="replace").read()
        src_cache[path] = src
        is_test_file = test_file(rel(path))
        for line, text, dyn in literal_groups(src):
            for name, cols, cons, off in parse_creates(text):
                ln = line + text.count("\n", 0, off)
                tgt = test_tables if is_test_file else tables
                if name in tgt:
                    tgt[name]["also"].append("%s:%d" % (rel(path), ln))
                    continue
                tgt[name] = {"cols": cols, "cons": cons, "where": "%s:%d" % (rel(path), ln), "also": []}
    for path, src in src_cache.items():
        if rel(path) in OTHER_DB:
            continue
        lines = src.split("\n")
        ctx = function_index(lines)
        is_test_file = test_file(rel(path))
        offs = [0]
        for l_ in lines:
            offs.append(offs[-1] + len(l_) + 1)
        star = star_columns(src)
        for line, text, dyn in literal_groups(splice(src)):
            for st0 in statements(text):
                variants = [st0]
                for var in re.findall(r"\{(\w+)\}", st0):
                    vals = resolve(src, var, offs[min(line, len(offs) - 1)])
                    if vals:
                        variants = [v.replace("{%s}" % var, x) for v in variants for x in vals]
                for st in variants:
                  for t, kind, wc, rc, rd in analyse(st, tables, star):
                    name, is_test = ctx[min(line, len(ctx) - 1)]
                    uses.append((t, rel(path), line, name, is_test or is_test_file, kind, wc, rc, rd, st))
                st = st0
                if dyn and re.search(r"\b(from|into|update|join)\s*$", st, re.I):
                    dynamic.append((rel(path), line, st))

    # ---- key-value keys --------------------------------------------------------------------
    kv = {t: collections.defaultdict(lambda: {"w": set(), "r": set()}) for t in KV_TABLES}
    for path, src in src_cache.items():
        lines = src.split("\n")
        ctx = function_index(lines)
        r = rel(path)
        if r in OTHER_DB:
            continue
        is_test_file = test_file(r)
        for k, l in enumerate(lines, 1):
            code = l.split("//")[0]
            name, is_test = ctx[k]
            where = "%s:%d %s%s" % (r, k, name, " (test)" if is_test or is_test_file else "")
            for m in re.finditer(r"into (meta|sphere_meta|counters) (?:\(key, value\) )?values \('(\w+)'", code):
                kv[m.group(1)][m.group(2)]["w"].add(where)
            for m in re.finditer(r"from (meta|sphere_meta|counters) where key = '(\w+)'", code):
                kv[m.group(1)][m.group(2)]["r"].add(where)
            if "api/sphere211/" in r:
                for m in re.finditer(r"\b(set_sphere_meta|sphere_meta)\((?:c|ctx), \"(\w+)\"", code):
                    kv["sphere_meta"][m.group(2)]["w" if m.group(1) == "set_sphere_meta" else "r"].add(where)
                continue
            # the state module's meta helpers (state/state.h): the files that include it, directly or
            # through core/server.h
            if r.endswith("state/state.cpp") or '#include "state/state.h"' in src or '#include "core/server.h"' in src:
                for m in re.finditer(r"\b(set_meta|meta|next_uid)\(([^;]*)", code):
                    first = m.group(2).split(",")[0] if m.group(1) != "set_meta" else m.group(2).rsplit(",", 1)[0]
                    for key in re.findall(r'"(\w+)"', first):
                        if m.group(1) == "next_uid":
                            kv["meta"][key]["r"].add(where)
                            kv["meta"][key]["w"].add(where)
                        else:
                            kv["meta"][key]["w" if m.group(1) == "set_meta" else "r"].add(where)
            # count(c, "key") / counter(ctx, "prefix_" + ...); a key chosen by `cond ? "a" : "b"` counts both
            for m in re.finditer(r"\b(count|counter)\((?:c|ctx), (\"[\w]+\"(?: \+ [^,)]+(?:\([^)]*\))?)?)", code):
                key = m.group(2).replace('"', "")
                key = re.sub(r" \+ .*", "*", key)
                kv["counters"][key]["w" if m.group(1) == "count" else "r"].add(where)
            for m in re.finditer(r"\b(count|counter)\((?:c|ctx), [^,()?]+\? \"(\w+)\" : \"(\w+)\"", code):
                for key in m.group(2, 3):
                    kv["counters"][key]["w" if m.group(1) == "count" else "r"].add(where)

    # ---- consumers outside the server ------------------------------------------------------
    consumers = collections.defaultdict(set)
    tre = re.compile(r"\b(from|join|into|update|table)\s+[\"']?(\w+)", re.I)
    for path in files(CONSUMER_DIRS, (".py", ".sh")):
        try:
            text = open(path, encoding="utf-8", errors="replace").read()
        except OSError:
            continue
        for k, l in enumerate(text.split("\n"), 1):
            for m in tre.finditer(l):
                if m.group(2) in tables:
                    consumers[m.group(2)].add(rel(path))
            if "server_state.py" in l and not rel(path).endswith("server_state.py"):
                consumers["(tools/server_state.py)"].add(rel(path))

    # ---- row counts ------------------------------------------------------------------------
    states = []
    for s in a.state:
        label, _, p = s.partition("=")
        c = sqlite3.connect("file:%s?mode=ro" % p, uri=True)
        counts = {n: c.execute('select count(*) from "%s"' % n).fetchone()[0]
                  for (n,) in c.execute("select name from sqlite_master where type = 'table' and name not like 'sqlite_%'")}
        cols = {n: [r[1] for r in c.execute('pragma table_info("%s")' % n)] for n in counts}
        kvrows = {}
        for t in KV_TABLES:
            if t in counts:
                kvrows[t] = dict(c.execute('select key, value from "%s"' % t).fetchall())
        uv = c.execute("pragma user_version").fetchone()[0]
        states.append((label, counts, cols, kvrows, uv))

    # ---- report ----------------------------------------------------------------------------
    o = []
    w = o.append
    w("Generated by `tools/schema_inventory.py%s` (do not edit by hand).\n" %
      "".join(" --state %s" % s.split("=")[0] + "=…" for s in a.state))
    w("### 1.1 Tables (%d created by the server; %d `create table` sites)\n" %
      (len(tables), len(tables) + sum(len(t["also"]) for t in tables.values())))
    hdr = "| table | created at | cols | keys / constraints | writers (non-test) | readers (non-test) |" + "".join(" rows: %s |" % s[0] for s in states)
    w(hdr)
    w("|" + "---|" * (6 + len(states)))
    for t, d in tables.items():
        ws = sorted({"%s %s" % (u[1].split("/")[-1], u[3]) for u in uses if u[0] == t and u[5] == "w" and not u[4]})
        rs = sorted({"%s %s" % (u[1].split("/")[-1], u[3]) for u in uses if u[0] == t and u[8] and not u[4]})
        keys = [c for c, ty in d["cols"] if "primary key" in ty] + d["cons"]
        row = "| `%s` | %s | %d | %s | %s | %s |" % (t, d["where"] + ("; also " + ", ".join(d["also"]) if d["also"] else ""),
                                               len(d["cols"]), "; ".join(keys) or "**none**",
                                               "<br>".join(ws) or "**none**", "<br>".join(rs) or "**none**")
        for _, counts, _, _, _ in states:
            row += " %s |" % (counts.get(t, "absent"))
        w(row)
    w("")
    if test_tables:
        w("Created only by tests (scratch DBs, not the state schema): " + ", ".join("`%s` (%s)" % (t, d["where"]) for t, d in test_tables.items()) + "\n")
    for label, counts, _, _, uv in states:
        extra = sorted(set(counts) - set(tables))
        w("State `%s`: `pragma user_version` = %d; tables in the DB not created by the code: %s.\n" % (label, uv, ", ".join(extra) or "none"))

    w("### 1.2 Columns: who writes and who reads them\n")
    w("`W` = written by non-test code, `R` = read (named in a select / where / join) by non-test code, `T` = touched only by tests. "
      "File and function per column; `*` after a column = never written by non-test code, `!` = never read by non-test code.\n")
    for t, d in tables.items():
        w("#### `%s` (%s)\n" % (t, d["where"]))
        w("| column | type | W | R | written in | read in |")
        w("|---|---|---|---|---|---|")
        for col, ty in d["cols"]:
            wu = [u for u in uses if u[0] == t and col in u[6]]
            ru = [u for u in uses if u[0] == t and col in u[7]]
            wn = [u for u in wu if not u[4]]
            rn = [u for u in ru if not u[4]]
            flag = ("" if wn else "*") + ("" if rn else "!")

            def fmt(us):
                seen = collections.OrderedDict()
                for u in us:
                    seen.setdefault("%s:%d %s" % (u[1].split("/")[-1], u[2], u[3]), u[4])
                items = ["%s%s" % (k, " (test)" if v else "") for k, v in seen.items()]
                return "<br>".join(items[:8]) + ("<br>… %d more" % (len(items) - 8) if len(items) > 8 else "")

            w("| `%s`%s | %s | %s | %s | %s | %s |" % (col, flag, ty, "W" if wn else ("T" if wu else "-"),
                                               "R" if rn else ("T" if ru else "-"), fmt(wu) or "-", fmt(ru) or "-"))
        w("")

    w("### 1.3 Key-value keys (meta, sphere_meta, counters)\n")
    w("| table | key | writers | readers |" + "".join(" value in %s |" % s[0] for s in states))
    w("|---|---|---|---|" + "---|" * len(states))
    for t in KV_TABLES:
        for key in sorted(kv[t]):
            d = kv[t][key]
            row = "| `%s` | `%s` | %s | %s |" % (t, key, "<br>".join(sorted(d["w"])) or "**none**", "<br>".join(sorted(d["r"])) or "**none**")
            for _, _, _, kvrows, _ in states:
                vals = kvrows.get(t, {})
                if key.endswith("*"):
                    hits = {k: v for k, v in vals.items() if k.startswith(key[:-1])}
                    row += " %s |" % (", ".join("%s=%s" % kv_ for kv_ in sorted(hits.items())) or "-")
                else:
                    v = vals.get(key)
                    row += " %s |" % ("-" if v is None else "`%s`" % (str(v)[:40] + ("…" if len(str(v)) > 40 else "")))
            w(row)
    for label, _, _, kvrows, _ in states:
        for t in KV_TABLES:
            known = {k for k in kv[t] if not k.endswith("*")}
            pref = [k[:-1] for k in kv[t] if k.endswith("*")]
            unk = [k for k in kvrows.get(t, {}) if k not in known and not any(k.startswith(p) for p in pref)]
            if unk:
                w("\nKeys in `%s`.%s with no literal in the code: %s" % (label, t, ", ".join("`%s`" % k for k in sorted(unk))))
    w("")

    w("### 1.4 Statements built at run time\n")
    for f, l, s in dynamic:
        w("- %s:%d `%s …`" % (f, l, s[:100]))
    w("")
    w("### 1.5 Consumers outside the server (scripts and tools that query the state DB)\n")
    w("| table | files |")
    w("|---|---|")
    for t in list(tables) + ["(tools/server_state.py)"]:
        if consumers.get(t):
            w("| `%s` | %s |" % (t, ", ".join(sorted(consumers[t]))))
    w("\n`tests/diff/diffdrive/state.py` reads **every** table generically (`select *`, masked by column-name patterns; skips `meta`, `wire_device`).\n")

    w("### 1.6 Relationships and today's violations\n")
    w("Every reference between tables (`m:` = the read-only master DB, not enforceable by SQLite). Per state: "
      "rows checked / NULL / the 0 'none' sentinel / dangling values (orphans: no parent row). "
      "`ON DELETE` is the action declared in section 3.2 (`merged (Sn)`: the table goes away in step Sn). "
      "%d relationships: %d between state tables, %d into the master.\n" % (len(RELS), sum(1 for r in RELS if not r[2].startswith("m:")),
                                                                         sum(1 for r in RELS if r[2].startswith("m:"))))
    hdr = "| child.column | parent | sentinel | ON DELETE |" + "".join(" %s: n / null / 0 / dangling |" % s_[0] for s_ in states)
    w(hdr)
    w("|---|---|---|---|" + "---|" * len(states))
    reps = [fk_report(sp.partition("=")[2], a.master) for sp in a.state]
    for i, rel_ in enumerate(RELS):
        ch, col, par, pcol, none, act, note = rel_
        row = "| `%s.%s` | `%s.%s`%s | %s | %s |" % (ch, col, par, pcol, (" (%s)" % note) if note else "", "-" if none is None else none, act)
        for rp in reps:
            r_ = rp[i]
            if isinstance(r_[6], str):
                row += " %s |" % r_[6]
            else:
                bad = r_[9]
                row += " %d / %d / %d / %s |" % (r_[6], r_[7], r_[8], ("**%d** (%s)" % (len(bad), ", ".join(hex(b) if b > 0xffffff else str(b) for b in bad[:4]))) if bad else "0")
        if reps and any(not isinstance(rp[i][6], str) and rp[i][-1] for rp in reps):
            pass
        w(row)
    w("")
    text = "\n".join(o)
    if a.update:
        doc = open(a.update, encoding="utf-8").read()
        b, e = "<!-- inventory:begin -->", "<!-- inventory:end -->"
        i, j = doc.index(b) + len(b), doc.index(e)
        open(a.update, "w", encoding="utf-8").write(doc[:i] + "\n" + text + "\n" + doc[j:])
    else:
        sys.stdout.write(text + "\n")


if __name__ == "__main__":
    main()
