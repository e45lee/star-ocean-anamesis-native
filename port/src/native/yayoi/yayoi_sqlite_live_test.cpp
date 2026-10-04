// The SQLite driver family's live check itself (yayoi_sqlite_live.cpp), in --selftest: the trampolines
// are pointed at the guest symbols (natives aren't installed here, so those are the originals), the
// check is switched on, and a session through the natives' thunks is shadowed: checks, no mismatch.
// Then the native's database is changed behind the driver's back (a row only it has): caught.
#include <sqlite3.h>

#include "native/yayoi/yayoi_sqlite_live.h"
#include "native/yayoi/yayoi_sqlite_test_util.h"

namespace soa::native::yayoi {
namespace {

using namespace test;

struct LiveOn {
    LiveOn() {
        for (int k = 0; k < live::kFnCount; k++) live::g_orig[k] = guest::sym(live::info((live::Fn)k).sym);
        driver_live_switch(true);
    }
    ~LiveOn() {
        driver_live_switch(false);
        for (int k = 0; k < live::kFnCount; k++) live::g_orig[k] = 0;
    }
};

}  // namespace

NATIVE_TEST("yayoi/live-check") {
    static DBAddress addr{":memory:"};
    Side n{"native", true, {}};
    u64 c0, b0, s0, c1, b1, s1;
    driver_live_counts(&c0, &b0, &s0);
    u64 d, e;
    {
        LiveOn on;
        d = n.new_driver();
        n.status(DRV "6DoOpenENS0_6Entity4ModeEPKcPKNS0_9DBAddressE", {d, 1, 0, (u64)&addr});
        const char* exec = DRV "7ExecuteEPKcPKNS0_10QueryParamEm";
        n.status(exec, {d, (u64)"CREATE TABLE t(id INTEGER, name TEXT, v REAL)", 0, 0});
        n.status(exec, {d, (u64)"INSERT INTO t VALUES(1, 'one', 1.5), (2, 'two', NULL), (3, '', -2)", 0, 0});
        e = n.new_entity();
        n.status(DRV "4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE", {d, (u64)"SELECT * FROM t ORDER BY id", 0, 0, e});
        serialize_text(n, e, nullptr);
        n.delete_entity(e);
        // (Serialize leaves the statement after its last row: a new Find for the walk)
        e = n.new_entity();
        n.status(DRV "4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE", {d, (u64)"SELECT * FROM t ORDER BY id", 0, 0, e});
        while (n.status(ENT "5FetchEv", {e}) == 0) {
            read_column(n, e, 0);
            read_column(n, e, 1);
            s32 v;
            n.status(ENT "10GetIntegerEPKcPim", {e, (u64)"id", (u64)&v, 0});
        }
        driver_live_counts(&c1, &b1, &s1);
        if (c1 - c0 < 20) t.fail("only %llu checks", (unsigned long long)(c1 - c0));
        t.expect_eq(b1 - b0, (u64)0, "no mismatch");
        t.expect_eq(s1 - s0, (u64)0, "nothing skipped");
        n.delete_entity(e);

        // a row only the native's connection has: the next Serialize and Fetch walk differ
        sqlite3_exec((sqlite3*)((SQLiteDriver*)d)->m_db, "INSERT INTO t VALUES(4, 'native only', 0)", nullptr, nullptr, nullptr);
        e = n.new_entity();
        n.status(DRV "4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE", {d, (u64)"SELECT * FROM t ORDER BY id", 0, 0, e});
        serialize_text(n, e, nullptr);
        n.delete_entity(e);
        driver_live_counts(&c0, &b0, &s0);
        t.expect_eq(b0 - b1 >= 1, true, "the divergence is caught");
        n.delete_driver(d);
    }
}

}  // namespace soa::native::yayoi
