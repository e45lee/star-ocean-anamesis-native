"""The server's state as data: every table of a state DB, with what legitimately differs between
two runs masked (PLAN-consolidate D9; generalized from tools/compare_tutorial.py's state_rows)."""
import re
import sqlite3

# Columns that hold a time (the server clock runs on in real time from --clock, so two runs differ
# by seconds): masked.
# PLAN-schema S9: a day start is `*_day` and a counter `day_index` (compared: login_bonus.day_index,
# premium_pass.day_index; they were `day`, masked by `^day`), a boolean `is_*` (ds_area.is_last_play,
# was last_play, masked by `^last_`); `_secs$` keeps wboss.last_clear_secs (a battle's duration in
# real seconds) masked, which `^last_` covered.
TIME_COL = re.compile(r"(_at$|^at$|^time$|_time$|_day$|^date|stamina_at|_secs$|_until$|^expire)")
# Columns that hold a run's identity: masked.
ID_COLS = {
    # a new player's id and search id: CHash32 of the device UUID + name, and a fresh KVS makes a
    # new UUID every run (the seeded player's come from the seed save: equal anyway)
    ("player", "id"),
    ("player", "search_id"),
}
# Tables only one route has, or whose rows are about the transport; not compared.
SKIP_TABLES = {
    "wire_device": "soa-server's record of the bridge's device UUIDs (no bridge in-process)",
    "meta": "the state DB's own bookkeeping (schema version, the seed's start time)",
}


def rows(db, mask_cols=()):
    """{table: (columns, sorted rows)}, times and ids masked."""
    c = sqlite3.connect("file:%s?mode=ro" % db, uri=True)
    out = {}
    for (name,) in c.execute("select name from sqlite_master where type = 'table' order by name"):
        if name in SKIP_TABLES or name.startswith("sqlite_"):
            continue
        cur = c.execute('select * from "%s"' % name)
        cols = [d[0] for d in cur.description]
        rs = []
        for r in cur.fetchall():
            rs.append(tuple("<time>" if TIME_COL.search(col) else "<id>" if (name, col) in ID_COLS or (name, col) in mask_cols else v
                            for col, v in zip(cols, r)))
        out[name] = (cols, sorted(rs, key=repr))
    c.close()
    return out


def diff(a_db, b_db, la="A", lb="B", mask_cols=()):
    """Lines describing every difference (empty: equal)."""
    a, b = rows(a_db, mask_cols), rows(b_db, mask_cols)
    out = []
    for t in sorted(set(a) | set(b)):
        if t not in a or t not in b:
            out.append("%s: only in %s" % (t, la if t in a else lb))
            continue
        if a[t] == b[t]:
            continue
        cols = a[t][0]
        ra, rb = a[t][1], b[t][1]
        sa, sb = set(ra), set(rb)
        only_a = [r for r in ra if r not in sb]
        only_b = [r for r in rb if r not in sa]
        out.append("%s (%s): %d rows only in %s, %d only in %s" % (t, ",".join(cols), len(only_a), la, len(only_b), lb))
        for r in only_a[:6]:
            out.append("    %s: %s" % (la, r))
        for r in only_b[:6]:
            out.append("    %s: %s" % (lb, r))
    return out
