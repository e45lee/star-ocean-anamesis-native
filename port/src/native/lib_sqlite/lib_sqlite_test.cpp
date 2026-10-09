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

#include "soaruntime/core/log.h"
#include "core/paths.h"
#include "soaruntime/core/vfs.h"
#include "native/common/test.h"
#include "native/lib_sqlite/lib_sqlite.h"
#include "native/lib_sqlite/lib_sqlite_master.h"

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

// The master in both SQLites, and the corpus run on both; `full`: every accessor of every value.
void master_diff(TestContext& t, size_t per_template, bool full) {
    auto t0 = std::chrono::steady_clock::now();
    Side g{guest_api(), "guest"}, nat{native_api(), "native"};
    std::string host_copy, gpath = stage_master(t, &host_copy, "lib_sqlite_test_master.sqlite3");
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
