// Differential tests of the host SQLite against the guest's SQLite 3.13.0, through the bound API in the
// guest ABI on both sides (lib_sqlite.h: guest_api() = the guest's own code, native_api() = thunks to the
// natives). The game's own procedure on the 3.7.0 master (data/basmaster-3.7.0.sqlite3): an in-memory
// database, ATTACH of the decrypted file by its Android path, `create table X as select * from newdb.X`
// for every table, DETACH; then every query the game's code holds (the "SELECT * FROM ..." strings of
// libSOA-3.7.0.so, the connectors' __TABLE_NAME__ templates for every table), instantiated with values of
// the master, binds as text (as Aska::Yayoi::SQLiteDriver binds). Results compare row by row, in order:
// column names, value types and the values as the game reads them.
#include <sqlite3.h>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iterator>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

#include "core/log.h"
#include "core/paths.h"
#include "core/vfs.h"
#include "native/common/test.h"
#include "native/lib_sqlite/lib_sqlite.h"

namespace soa::native::lib_sqlite {
namespace {

// ---- one side (guest or native), driven through guest calls ----

struct Side {
    Api a;
    const char* name;

    u64 open(const char* path, int* rc) {
        u64* out = (u64*)calloc(1, 8);
        *rc = guest_invoke<int>(a.open, path, out);
        u64 db = *out;
        free(out);
        return db;
    }
    int exec(u64 db, const char* sql) { return guest_invoke<int>(a.exec, db, sql, 0, 0, 0); }
    u64 prepare(u64 db, const std::string& sql, int* rc, long* tail_off) {
        u64* out = (u64*)calloc(2, 8);
        *rc = guest_invoke<int>(a.prepare_v2, db, sql.c_str(), (int)-1, out, out + 1);
        u64 st = out[0];
        *tail_off = out[1] ? (long)(out[1] - (u64)(uintptr_t)sql.c_str()) : -1;
        free(out);
        return st;
    }
    const char* errmsg(u64 db) { return guest_invoke<const char*>(a.errmsg, db); }
    int step(u64 st) { return guest_invoke<int>(a.step, st); }
    int reset(u64 st) { return guest_invoke<int>(a.reset, st); }
    int finalize(u64 st) { return guest_invoke<int>(a.finalize, st); }
    int close(u64 db) { return guest_invoke<int>(a.close, db); }
};

std::string hex64(u64 v) {
    char b[24];
    snprintf(b, sizeof b, "%016llx", (unsigned long long)v);
    return b;
}
std::string str_or_null(const char* s) { return s ? "'" + std::string(s) + "'" : "NULL"; }

// One column of the current row as the game reads it (Aska::Yayoi::SQLiteDriver::EntityObject:
// sqlite3_value_type, then the typed getter), or every accessor (`full`: the conversions too, in a fixed
// order, the same on both sides).
std::string read_value(Side& s, u64 st, int i, bool full) {
    u64 v = guest_invoke<u64>(s.a.column_value, st, i);
    if (!v) return "<no value>";
    int t = guest_invoke<int>(s.a.value_type, v);
    std::string r = std::to_string(t) + ":";
    auto vi = [&] { return std::to_string(guest_invoke<int>(s.a.value_int, v)); };
    auto vi64 = [&] { return std::to_string(guest_invoke<s64>(s.a.value_int64, v)); };
    auto vd = [&] {
        double d = guest_invoke<double>(s.a.value_double, v);
        u64 b;
        memcpy(&b, &d, 8);
        return hex64(b);
    };
    auto vt = [&] { return str_or_null(guest_invoke<const char*>(s.a.value_text, v)); };
    auto vb = [&] { return std::to_string(guest_invoke<int>(s.a.value_bytes, v)); };
    auto vblob = [&] {
        const u8* p = guest_invoke<const u8*>(s.a.value_blob, v);
        int n = guest_invoke<int>(s.a.value_bytes, v);
        std::string h = std::to_string(n) + (p ? "#" : "#null");
        for (int k = 0; p && k < n; k++) h += hex64(p[k]).substr(14);
        return h;
    };
    switch (t) {
    case SQLITE_INTEGER: r += full ? vi() + "," + vi64() + "," + vd() + "," + vt() + "," + vb() : vi(); break;
    case SQLITE_FLOAT: r += full ? vd() + "," + vi() + "," + vi64() + "," + vt() + "," + vb() : vd(); break;
    case SQLITE_TEXT: r += full ? vt() + "," + vb() + "," + vi() + "," + vi64() + "," + vd() : vt(); break;
    case SQLITE_BLOB: r += vblob(); break;
    default: r += full ? vt() + "," + vb() + "," + vi() : ""; break;
    }
    return r;
}

struct Result {
    int prepare_rc = 0, last_rc = 0, finalize_rc = 0, param_count = 0;
    long tail = -1;
    std::string errmsg;
    std::vector<std::string> names, rows, bind_rcs;
};

// Runs one statement the way SQLiteDriver::_Execute / Find / EntityObject do: prepare_v2,
// bind_parameter_count, bind_text of each parameter (SQLITE_STATIC), step until done reading every
// column, reset, finalize.
Result run(Side& s, u64 db, const std::string& sql, const std::vector<std::string>& params, bool full) {
    Result r;
    u64 st = s.prepare(db, sql, &r.prepare_rc, &r.tail);
    if (!st) {
        r.errmsg = s.errmsg(db);
        return r;
    }
    r.param_count = guest_invoke<int>(s.a.bind_parameter_count, st);
    for (size_t k = 0; k < params.size(); k++)
        r.bind_rcs.push_back(std::to_string(guest_invoke<int>(s.a.bind_text, st, (int)(k + 1), params[k].c_str(), (int)params[k].size(), (u64)0)));
    int n = guest_invoke<int>(s.a.column_count, st);
    for (int i = 0; i < n; i++) r.names.push_back(str_or_null(guest_invoke<const char*>(s.a.column_name, st, i)));
    for (;;) {
        r.last_rc = s.step(st);
        if (r.last_rc != SQLITE_ROW) break;
        std::string row;
        for (int i = 0; i < n; i++) row += (i ? "|" : "") + read_value(s, st, i, full);
        r.rows.push_back(std::move(row));
    }
    s.reset(st);
    r.finalize_rc = s.finalize(st);
    return r;
}

// Compares two results; false (and a failure) on the first difference.
bool same(TestContext& t, const std::string& sql, const Result& g, const Result& n) {
    auto bad = [&](const char* what, const std::string& gv, const std::string& nv) {
        t.fail("%s: %s: guest %.300s / native %.300s", sql.substr(0, 160).c_str(), what, gv.c_str(), nv.c_str());
        return false;
    };
    if (g.prepare_rc != n.prepare_rc) return bad("prepare rc", std::to_string(g.prepare_rc), std::to_string(n.prepare_rc));
    if (g.tail != n.tail) return bad("tail", std::to_string(g.tail), std::to_string(n.tail));
    // (sqlite3_errmsg's text: not compared. Its one caller, SQLiteDriver::_Prepare, drops it; the texts
    // differ between versions, e.g. "SELECT * FROM ": 3.13.0 'near " ": syntax error', 3.45.1 "incomplete
    // input". That both have one is.)
    if (g.errmsg.empty() != n.errmsg.empty()) return bad("errmsg", g.errmsg, n.errmsg);
    if (g.param_count != n.param_count) return bad("parameter count", std::to_string(g.param_count), std::to_string(n.param_count));
    if (g.bind_rcs != n.bind_rcs) return bad("bind rc", "", "");
    if (g.names != n.names) return bad("column names", g.names.empty() ? "" : g.names[0], n.names.empty() ? "" : n.names[0]);
    if (g.last_rc != n.last_rc) return bad("step rc", std::to_string(g.last_rc), std::to_string(n.last_rc));
    if (g.finalize_rc != n.finalize_rc) return bad("finalize rc", std::to_string(g.finalize_rc), std::to_string(n.finalize_rc));
    if (g.rows.size() != n.rows.size()) return bad("row count", std::to_string(g.rows.size()), std::to_string(n.rows.size()));
    for (size_t k = 0; k < g.rows.size(); k++)
        if (g.rows[k] != n.rows[k]) return bad(("row " + std::to_string(k)).c_str(), g.rows[k], n.rows[k]);
    return true;
}

// ---- the master, loaded the way CStaticTransaction does ----

// The 3.7.0 master copied to a guest path (the game ATTACHes its decrypted copy by its Android path).
std::string stage_master(TestContext& t, std::string* host_copy) {
    std::string src = find_repo_file("data/basmaster-3.7.0.sqlite3");
    if (src.empty()) {
        t.fail("data/basmaster-3.7.0.sqlite3 not found");
        return "";
    }
    std::string guest = guest_internal_dir() + "/lib_sqlite_test_master.sqlite3";
    *host_copy = host_path(guest.c_str());
    std::ifstream in(src, std::ios::binary);
    std::ofstream out(*host_copy, std::ios::binary | std::ios::trunc);
    out << in.rdbuf();
    if (!out) t.fail("can't copy the master to %s", host_copy->c_str());
    return guest;
}

// The game's load (CStaticTransaction): ":memory:", ATTACH, a copy of every table, DETACH. The table
// names (the game's query) go to *tables; the statements' results are compared through `cmp`.
u64 load_master(TestContext& t, Side& s, const std::string& guest_path, std::vector<std::string>* tables, std::vector<Result>* log) {
    int rc = 0;
    u64 db = s.open(":memory:", &rc);
    if (rc != SQLITE_OK || !db) {
        t.fail("%s: open(:memory:) = %d", s.name, rc);
        return 0;
    }
    auto exec = [&](const std::string& sql) {
        log->push_back(run(s, db, sql, {}, true));
        return log->back();
    };
    char buf[512];
    snprintf(buf, sizeof buf, "ATTACH DATABASE '%s' AS %s", guest_path.c_str(), "newdb");
    exec(buf);
    snprintf(buf, sizeof buf, "SELECT name FROM %s.sqlite_master WHERE type='table' and name NOT IN ('sqlite_stat1', 'sqlite_sequence')", "newdb");
    log->push_back(run(s, db, buf, {}, false));
    Result names = log->back();
    for (auto& row : names.rows) {
        // (row = "3:'name'")
        size_t q = row.find('\'');
        if (q != std::string::npos && row.size() > q + 1) tables->push_back(row.substr(q + 1, row.size() - q - 2));
    }
    for (auto& tb : *tables) {
        snprintf(buf, sizeof buf, "create table %s as select * from %s.%s", tb.c_str(), "newdb", tb.c_str());
        exec(buf);
    }
    snprintf(buf, sizeof buf, "DETACH DATABASE %s", "newdb");
    exec(buf);
    return db;
}

// ---- the query corpus ----

struct Query {
    std::string sql;
    std::vector<std::string> params;
};

// The game's query strings: every NUL-terminated "SELECT * FROM ..." in the 3.7.0 lib.
std::vector<std::string> lib_queries(TestContext& t) {
    std::string path = find_repo_file("work/libSOA-3.7.0.so");
    std::ifstream f(path, std::ios::binary);
    if (!f) {
        t.fail("work/libSOA-3.7.0.so not found");
        return {};
    }
    std::string bytes((std::istreambuf_iterator<char>(f)), {});
    std::set<std::string> out;
    const std::string key = "SELECT * FROM ";
    for (size_t p = bytes.find(key); p != std::string::npos; p = bytes.find(key, p + 1)) {
        if (p > 0 && bytes[p - 1] != '\0') continue;
        size_t e = bytes.find('\0', p);
        out.insert(bytes.substr(p, e - p));
    }
    return {out.begin(), out.end()};
}

// Helper database (the host SQLite on the master file directly): the tables' columns and values to
// instantiate the templates with.
struct Master {
    sqlite3* db = nullptr;
    std::map<std::string, std::set<std::string>> columns;
    ~Master() {
        if (db) sqlite3_close(db);
    }
    bool open(const std::string& path) {
        if (sqlite3_open_v2(path.c_str(), &db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) return false;
        for (auto& tb : strings("SELECT name FROM sqlite_master WHERE type='table'"))
            for (auto& c : strings("SELECT name FROM pragma_table_info('" + tb + "')")) columns[tb].insert(c);
        return true;
    }
    std::vector<std::string> strings(const std::string& sql) {
        std::vector<std::string> v;
        sqlite3_stmt* st = nullptr;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &st, nullptr) != SQLITE_OK) return v;
        while (sqlite3_step(st) == SQLITE_ROW) {
            const unsigned char* s = sqlite3_column_text(st, 0);
            v.push_back(s ? (const char*)s : "");
        }
        sqlite3_finalize(st);
        return v;
    }
    // Rows of the given columns: up to n, spread over the table (plus the value tuples' SQL literals).
    std::vector<std::vector<std::string>> samples(const std::string& tb, const std::vector<std::string>& cols, size_t n, bool literal) {
        std::string list;
        for (auto& c : cols) list += (list.empty() ? "" : ", ") + std::string(literal ? "quote(" : "") + "`" + c + "`" + (literal ? ")" : "");
        std::string where;
        for (auto& c : cols) where += (where.empty() ? " WHERE " : " AND ") + std::string("`") + c + "` IS NOT NULL";
        std::vector<std::vector<std::string>> all;
        sqlite3_stmt* st = nullptr;
        std::string sql = "SELECT DISTINCT " + list + " FROM `" + tb + "`" + where;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &st, nullptr) != SQLITE_OK) return all;
        while (sqlite3_step(st) == SQLITE_ROW) {
            std::vector<std::string> r;
            for (size_t k = 0; k < cols.size(); k++) {
                const unsigned char* s = sqlite3_column_text(st, (int)k);
                r.push_back(s ? (const char*)s : "");
            }
            all.push_back(std::move(r));
        }
        sqlite3_finalize(st);
        if (all.size() <= n) return all;
        std::vector<std::vector<std::string>> out;
        for (size_t k = 0; k < n; k++) out.push_back(all[k * all.size() / n]);
        return out;
    }
};

std::string table_of(const std::string& sql) {
    static const std::regex re("FROM `?(\\w+)`?");
    std::smatch m;
    return std::regex_search(sql, m, re) ? m[1].str() : "";
}

// The column a placeholder at `pos` compares with: "col = ?", "`col` <= ?", "col IN (" ...; or, for
// "'%s' >= `col`", the one after it.
std::string column_at(const std::string& sql, size_t pos) {
    static const std::regex before("`?(\\w+)`?\\s*(?:NOT\\s+)?(=|<=|>=|<|>|IN\\s*\\(|IN|IS NOT|IS)\\s*'?$");
    static const std::regex after("^'?\\s*(>=|<=|<|>|=)\\s*`?(\\w+)`?");
    std::smatch m;
    std::string pre = sql.substr(0, std::min(pos, sql.size())), post = pos + 2 < sql.size() ? sql.substr(pos + 2) : "";
    if (std::regex_search(pre, m, before)) return m[1].str();
    if (std::regex_search(post, m, after)) return m[2].str();
    return "";
}

// One template -> the queries to run: placeholders ('?' bound as text; %s / %u / %d formatted in; a
// trailing "IN (" / "= " / "<= " completed as the game's code completes it) filled from the master's
// rows, up to `n` tuples, plus a tuple that matches nothing.
std::vector<Query> instantiate(Master& m, const std::string& tmpl, size_t n) {
    std::vector<Query> out;
    // %s as a table name ("SELECT * FROM %s WHERE col ..."): every table with the columns used.
    if (tmpl.rfind("SELECT * FROM %s", 0) == 0) {
        static const std::regex col("(\\w+) (IN|=)");
        std::vector<std::string> need;
        for (auto it = std::sregex_iterator(tmpl.begin(), tmpl.end(), col); it != std::sregex_iterator(); ++it) need.push_back((*it)[1]);
        for (auto& [tb, cols] : m.columns) {
            bool ok = !need.empty();
            for (auto& c : need) ok = ok && cols.count(c);
            if (!ok) continue;
            std::string s = tmpl;
            s.replace(14, 2, tb);
            for (auto& q : instantiate(m, s, n)) out.push_back(q);
        }
        return out;
    }
    if (tmpl.find("__TABLE_NAME__") != std::string::npos) {
        for (auto& [tb, cols] : m.columns) {
            std::string s = std::regex_replace(tmpl, std::regex("__TABLE_NAME__"), tb);
            std::string c = column_at(s, s.find('?') == std::string::npos ? s.size() : s.find('?'));
            if (s.find('?') != std::string::npos && !cols.count(c)) continue;
            for (auto& q : instantiate(m, s, n)) out.push_back(q);
        }
        return out;
    }
    std::string tb = table_of(tmpl);
    // the placeholders, in order: (position, kind, column)
    struct Ph {
        size_t pos;
        char kind;  // '?', 's', 'u' (number), 'E' (trailing: a value), 'I' (trailing IN list)
        std::string col;
    };
    std::vector<Ph> ph;
    for (size_t k = 0; k < tmpl.size(); k++) {
        if (tmpl[k] == '?') ph.push_back({k, '?', column_at(tmpl, k)});
        else if (tmpl[k] == '%' && k + 1 < tmpl.size() && strchr("sud", tmpl[k + 1])) ph.push_back({k, tmpl[k + 1] == 's' ? 's' : 'u', column_at(tmpl, k)});
    }
    static const std::regex in_end("IN\\s*\\($"), eq_end("(=|<=|>=|<|>)\\s*$");
    char trailing = std::regex_search(tmpl, in_end) ? 'I' : std::regex_search(tmpl, eq_end) ? 'E' : 0;
    if (trailing) ph.push_back({tmpl.size(), trailing, column_at(tmpl + "''", tmpl.size())});
    if (ph.empty()) return {{tmpl, {}}};
    std::vector<std::string> cols;
    for (auto& p : ph) {
        if (p.col.empty() || !m.columns[tb].count(p.col)) return {{"-- no column for a placeholder: " + tmpl, {}}};
        cols.push_back(p.col);
    }
    auto raw = m.samples(tb, cols, n, false), lit = m.samples(tb, cols, n, true);
    if (raw.size() != lit.size()) return {};
    raw.push_back(std::vector<std::string>(cols.size(), "-12345"));
    lit.push_back(std::vector<std::string>(cols.size(), "-12345"));
    std::vector<std::string> in_list;  // a trailing IN list: up to 10 of the column's values
    if (trailing == 'I')
        for (auto& r : m.samples(tb, {ph.back().col}, 10, true)) in_list.push_back(r[0]);
    for (size_t r = 0; r < raw.size(); r++) {
        Query q;
        size_t last = 0;
        for (size_t k = 0; k < ph.size(); k++) {
            q.sql += tmpl.substr(last, ph[k].pos - last);
            last = ph[k].pos + (ph[k].kind == '?' ? 1 : ph[k].kind == 'E' || ph[k].kind == 'I' ? 0 : 2);
            switch (ph[k].kind) {
            case '?': q.sql += "?", q.params.push_back(raw[r][k]); break;
            case 's': q.sql += raw[r][k]; break;  // (inside the template's quotes)
            case 'u': q.sql += lit[r][k]; break;
            case 'E': q.sql += lit[r][k]; break;
            case 'I': {
                std::string l = lit[r][k];
                for (auto& v : in_list) l += "," + v;
                q.sql += l + ")";
                break;
            }
            }
        }
        q.sql += tmpl.substr(std::min(last, tmpl.size()));
        out.push_back(std::move(q));
    }
    return out;
}

// The whole corpus: the lib's templates, plus every table's "SELECT * FROM t" and "... WHERE id=?".
std::vector<Query> corpus(TestContext& t, Master& m, size_t n) {
    std::vector<Query> qs;
    std::vector<std::string> tmpls = lib_queries(t);
    for (auto& [tb, cols] : m.columns) {
        tmpls.push_back("SELECT * FROM " + tb);
        if (cols.count("id")) tmpls.push_back("SELECT * FROM " + tb + " WHERE id=?");
    }
    for (auto& s : tmpls)
        if (s == "SELECT * FROM ") qs.push_back({s, {}});  // (a prefix the code completes: run as is, an error in both)
        else for (auto& q : instantiate(m, s, n)) qs.push_back(std::move(q));
    return qs;
}

// The master in both SQLites, and the corpus run on both; `full`: every accessor of every value.
void master_diff(TestContext& t, size_t per_template, bool full) {
    auto t0 = std::chrono::steady_clock::now();
    Side g{guest_api(), "guest"}, nat{native_api(), "native"};
    std::string host_copy, gpath = stage_master(t, &host_copy);
    if (gpath.empty()) return;
    std::vector<std::string> gt, nt;
    std::vector<Result> glog, nlog;
    u64 gdb = load_master(t, g, gpath, &gt, &glog), ndb = load_master(t, nat, gpath, &nt, &nlog);
    if (!gdb || !ndb) return;
    t.expect_eq(gt, nt, "the master's table list");
    t.expect_eq(gt.size(), (size_t)176, "176 tables");
    for (size_t k = 0; k < glog.size() && k < nlog.size(); k++) same(t, "(load step " + std::to_string(k) + ")", glog[k], nlog[k]);
    for (auto& r : nlog)
        if (r.prepare_rc != SQLITE_OK || (r.last_rc != SQLITE_DONE)) t.fail("load: native rc %d / %d (%s)", r.prepare_rc, r.last_rc, r.errmsg.c_str());

    Master m;
    if (!m.open(host_copy)) return t.fail("can't open %s", host_copy.c_str());
    std::vector<Query> qs = corpus(t, m, per_template);
    size_t rows = 0, bad = 0, unfilled = 0;
    for (auto& q : qs) {
        if (q.sql.rfind("--", 0) == 0) {
            unfilled++;
            LOGW("lib_sqlite_test", "%s", q.sql.c_str());
            continue;
        }
        Result a = run(g, gdb, q.sql, q.params, full), b = run(nat, ndb, q.sql, q.params, full);
        rows += a.rows.size();
        if (!same(t, q.sql, a, b) && ++bad > 20) {
            t.fail("(stopping after 20 differing queries)");
            break;
        }
        if (a.prepare_rc != SQLITE_OK) LOGW("lib_sqlite_test", "query fails in both: %s (%s)", q.sql.c_str(), a.errmsg.c_str());
    }
    t.expect_eq(g.close(gdb), SQLITE_OK, "guest close");
    t.expect_eq(nat.close(ndb), SQLITE_OK, "native close");
    remove(host_copy.c_str());
    double secs = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    LOGI("lib_sqlite_test", "%zu queries (%zu templates without a fill), %zu rows, %zu differing, %s accessors, %.1f s", qs.size(), unfilled,
         rows, bad, full ? "every" : "the game's", secs);
}

}  // namespace

// The master loaded as the game loads it, then the game's queries: every table in full and up to 6
// instantiations of each template, values read as the game reads them.
NATIVE_TEST("lib_sqlite/master-queries") { master_diff(t, 6, false); }

// Every accessor (the conversions: int / int64 / double / text / bytes of every value), up to 3
// instantiations per template.
NATIVE_TEST("lib_sqlite/master-accessors") { master_diff(t, 3, true); }

}  // namespace soa::native::lib_sqlite
