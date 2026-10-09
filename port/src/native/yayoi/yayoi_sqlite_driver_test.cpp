// Differential tests of the SQLite driver family (yayoi_sqlite_hooks.cpp) against the 3.7.0 guest: the
// same calls on both sides, through the guest ABI (the guest's own functions, which use the guest's
// SQLite 3.13.0 in --selftest, vs thunks of the natives' HostFns, which use the host SQLite), each side
// on its own driver and entity objects. Results are compared as logs of every status, value and
// object state, and Serialize's MessagePack byte for byte.
//   yayoi/sqlite-driver-master: the master loaded the game's way through the driver (DoOpen :memory:,
//     ATTACH, CStaticTransaction::Progress's table walk, create table ... as select, DETACH); then every
//     table and the game's query corpus (lib_sqlite_master.h): Find + Serialize, and a row walk with
//     the typed getters (by index, and by name every few rows).
//   yayoi/sqlite-driver-edges: statuses and quirks on a private database (transactions, failing
//     prepares, parameter counts, NULLs, truncations, > 64 columns, long texts, blobs, the cache buffer).
//   yayoi/column-map: the THashMap<char const*, int> members on maps built by each side.
#include <sqlite3.h>

#include <chrono>
#include <cinttypes>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "soaruntime/core/log.h"
#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "native/lib_sqlite/lib_sqlite_master.h"
#include "native/yayoi/yayoi_guest.h"
#include "native/yayoi/yayoi_layout.h"
#include "native/yayoi/yayoi_sqlite.h"
#include "native/yayoi/yayoi_sqlite_test_util.h"

namespace soa::native::yayoi {
namespace {

using namespace test;


// ---- the master ----

// CStaticTransaction's load through the driver: :memory:, ATTACH, the table list (Find, Fetch,
// GetType, GetString as CStaticTransaction::Progress walks it), create table ... as select, DETACH.
std::vector<std::string> load_master(Side& s, u64 d, const std::string& gpath, const DBAddress* addr) {
    std::vector<std::string> tables;
    s.add(fmt("open %" PRId64, s.status(DRV "6DoOpenENS0_6Entity4ModeEPKcPKNS0_9DBAddressE", {d, 1, 0, (u64)addr})));
    std::string sql = "ATTACH DATABASE '" + gpath + "' AS newdb";
    s.add(fmt("attach %" PRId64 " ", s.status(DRV "7ExecuteEPKcPKNS0_10QueryParamEm", {d, (u64)sql.c_str(), 0, 0})) + driver_state(d));
    u64 e = s.new_entity();
    const char* names = "SELECT name FROM newdb.sqlite_master WHERE type='table' and name NOT IN ('sqlite_stat1', 'sqlite_sequence')";
    s.add(fmt("find %" PRId64 " ", s.status(DRV "4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE", {d, (u64)names, 0, 0, e})) + entity_state(e));
    for (;;) {
        s64 st = s.status(ENT "5FetchEv", {e});
        if (st != 0) {
            s.add(fmt("fetch %" PRId64, st));
            break;
        }
        s32 type = (s32)s.call(ENT "7GetTypeEim", {e, 0, 0});
        char buf[256];
        u64 size = sizeof buf;
        s64 st2 = s.status(ENT "9GetStringEiPcPmm", {e, 0, (u64)buf, (u64)&size, 0});
        s.add(fmt("table %d %" PRId64 " %" PRId64 " %s", type, st2, (s64)size, buf));
        tables.push_back(buf);
    }
    s.delete_entity(e);
    for (auto& tb : tables) {
        std::string c = "create table " + tb + " as select * from newdb." + tb;
        s.add(fmt("copy %s %" PRId64, tb.c_str(), s.status(DRV "7ExecuteEPKcPKNS0_10QueryParamEm", {d, (u64)c.c_str(), 0, 0})));
    }
    s.add(fmt("detach %" PRId64, s.status(DRV "7ExecuteEPKcPKNS0_10QueryParamEm", {d, (u64)"DETACH DATABASE newdb", 0, 0})));
    return tables;
}

// One query on one side: Find + Serialize, then Find again and the row walk.
void run_query(Side& s, u64 d, const lib_sqlite::Query& q, std::vector<u8>* msgpack, size_t name_every, size_t* rows) {
    std::vector<QueryParam> p = params_of(q.params);
    u64 e = s.new_entity();
    s64 st = s.status(DRV "4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE", {d, (u64)q.sql.c_str(), (u64)p.data(), p.size(), e});
    s.add(fmt("find %" PRId64 " ", st) + driver_state(d, p.data()) + " " + entity_state(e));
    s.add(serialize_text(s, e, msgpack));
    s.delete_entity(e);
    if (st == 0) {
        // (a new entity, as the game makes one per query: Store keeps the map when the new statement
        // has the old one's address, and the old names are gone with the old statement)
        e = s.new_entity();
        st = s.status(DRV "4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE", {d, (u64)q.sql.c_str(), (u64)p.data(), p.size(), e});
        s.add(fmt("find %" PRId64, st));
        walk_rows(s, e, name_every, rows);
        s.delete_entity(e);
    }
}

void master_test(TestContext& t, size_t per_template) {
    auto t0 = std::chrono::steady_clock::now();
    std::string host_copy, gpath = lib_sqlite::stage_master(t, &host_copy, "yayoi_driver_test_master.sqlite3");
    if (gpath.empty()) return;
    static DBAddress addr{":memory:"};
    Side g{"guest", false, {}}, n{"native", true, {}};
    u64 gd = g.new_driver(), nd = n.new_driver();
    std::vector<std::string> gt = load_master(g, gd, gpath, &addr), nt = load_master(n, nd, gpath, &addr);
    t.expect_eq(gt.size(), (size_t)176, "176 tables");
    if (!same_logs(t, g, n, "load")) return;

    lib_sqlite::Master m;
    if (!m.open(host_copy)) return t.fail("can't open %s", host_copy.c_str());
    std::vector<lib_sqlite::Query> qs;
    for (auto& tb : gt) qs.push_back({"SELECT * FROM " + tb, {}});  // every table, whole
    // (a query that doesn't prepare would close the driver's database, on both sides: the edges test
    // has that case; here such queries are left out)
    size_t failing = 0;
    for (auto& q : lib_sqlite::corpus(t, m, per_template)) {
        if (q.sql.rfind("--", 0) == 0) continue;
        sqlite3_stmt* st = nullptr;
        bool ok = sqlite3_prepare_v2(m.db, q.sql.c_str(), -1, &st, nullptr) == SQLITE_OK;
        sqlite3_finalize(st);
        if (ok) qs.push_back(q);
        else failing++;
    }
    size_t rows = 0, bytes = 0, bad = 0, serialized = 0;
    for (size_t k = 0; k < qs.size(); k++) {
        g.log.clear();
        n.log.clear();
        std::vector<u8> gm, nm;
        size_t grows = 0, nrows = 0;
        // (every table whole: by name every 97th row; the corpus: every 7th)
        size_t every = k < gt.size() ? 97 : 7;
        run_query(g, gd, qs[k], &gm, every, &grows);
        run_query(n, nd, qs[k], &nm, every, &nrows);
        rows += grows;
        bytes += gm.size();
        serialized += !gm.empty();
        bool ok = same_logs(t, g, n, qs[k].sql.substr(0, 200).c_str());
        if (gm != nm) {
            size_t i = 0;
            while (i < gm.size() && i < nm.size() && gm[i] == nm[i]) i++;
            t.fail("%.200s: MessagePack differs at byte %zu (%zu vs %zu bytes)", qs[k].sql.c_str(), i, gm.size(), nm.size());
            ok = false;
        }
        if (!((const SQLiteDriver*)gd)->m_db || !((const SQLiteDriver*)nd)->m_db) {
            t.fail("%.200s: the database was closed", qs[k].sql.c_str());
            break;
        }
        if (!ok && ++bad >= 10) {
            t.fail("(stopping after 10 differing queries)");
            break;
        }
    }
    t.expect_eq(serialized > 1000, true, "most queries serialize rows");
    t.expect_eq(failing < 5, true, "few corpus queries fail to prepare");
    g.delete_driver(gd);
    n.delete_driver(nd);
    remove(host_copy.c_str());
    double secs = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
    LOGI("yayoi_test", "driver: %zu queries (%zu tables whole; %zu not preparing left out), %zu rows walked, %zu serialized (%zu MessagePack bytes), %zu differing, %.1f s",
         qs.size(), gt.size(), failing, rows, serialized, bytes, bad, secs);
}

}  // namespace

// The master through both drivers: every table whole and the game's query corpus (up to 3 fills per
// template), Serialize's bytes and every value as the getters read it.
NATIVE_TEST("yayoi/sqlite-driver-master") { master_test(t, 3); }

}  // namespace soa::native::yayoi
