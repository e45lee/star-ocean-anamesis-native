// yayoi_sqlite_test_util.h: shared by the SQLite driver family's differential tests (yayoi_sqlite_*_test.cpp):
// one side of a test (the guest's functions or thunks of the natives, called through the guest ABI) and
// the objects' states as text, so the two sides' logs compare line by line.
#pragma once

#include <sqlite3.h>

#include <algorithm>
#include <cinttypes>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "native/yayoi/yayoi_guest.h"
#include "native/yayoi/yayoi_layout.h"
#include "native/yayoi/yayoi_sqlite.h"

namespace soa::native::yayoi::test {

#define DRV "_ZN4Aska5Yayoi12SQLiteDriver"
#define ENT "_ZN4Aska5Yayoi12SQLiteDriver12EntityObject"
#define MAP "_ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE"

inline std::string fmt(const char* f, ...) __attribute__((format(printf, 1, 2)));
inline std::string fmt(const char* f, ...) {
    char b[1024];
    va_list ap;
    va_start(ap, f);
    vsnprintf(b, sizeof b, f, ap);
    va_end(ap);
    return b;
}


// ---- one side: its functions (guest or native) and its objects ----

struct Side {
    const char* name;
    bool native;
    std::vector<std::string> log;

    u64 fn(const char* sym) const { return native ? driver_native_thunk(sym) : guest::sym(sym); }
    u64 call(const char* sym, std::initializer_list<u64> args) const { return guest_call(fn(sym), args); }
    s64 status(const char* sym, std::initializer_list<u64> args) const {
        s64 st = 0x5a5a5a5a;
        GuestArgs a;
        for (u64 v : args) a.i(v);
        a.sret(&st);
        guest_call(fn(sym), a);
        return st;
    }
    SharedBytes serialize(u64 e, s64* size) const {
        SharedBytes r{(s8*)0x5a5a, (s32*)0x5a5a};
        GuestArgs a;
        a.i(e).p(size).sret(&r);
        guest_call(fn(ENT "9SerializeEPl"), a);
        return r;
    }
    void add(std::string s) {
        // (SOA_YAYOI_TEST_TRACE=1: every line to stderr as it is made)
        static const bool trace = getenv("SOA_YAYOI_TEST_TRACE") != nullptr;
        if (trace) fprintf(stderr, "[%s] %.300s\n", name, s.c_str());
        log.push_back(std::move(s));
    }

    // objects in host memory (guest-visible), filled with a pattern before their constructors
    u64 new_driver() const {
        void* p = std::malloc(sizeof(SQLiteDriver));
        std::memset(p, 0xa5, sizeof(SQLiteDriver));
        call(DRV "C1Ev", {(u64)p});
        return (u64)p;
    }
    void delete_driver(u64 d) const {
        call(DRV "D1Ev", {d});
        std::free((void*)d);
    }
    u64 new_entity() const {
        void* p = std::malloc(sizeof(EntityObject));
        std::memset(p, 0xa5, sizeof(EntityObject));
        call(ENT "C1Ev", {(u64)p});
        return (u64)p;
    }
    void delete_entity(u64 e) const {
        call(ENT "D1Ev", {e});
        std::free((void*)e);
    }
};

// The objects' states as text (pointers as present / absent; the map's buckets with their keys).
// (m_lastParams: 0 none, 1 the params passed last (`params`), 2 others)
inline std::string driver_state(u64 d, const void* params = nullptr) {
    auto* p = (const SQLiteDriver*)d;
    int lp = !p->m_lastParams ? 0 : p->m_lastParams == params ? 1 : 2;
    return fmt("drv[set=%" PRIx64 " v08=%" PRIx64 " params=%d db=%d stmt=%d tx=%d begin=%d addr=%" PRIx64 " v48=%" PRIx64 " prep=%d buf=%d/%" PRIu64 "]",
               (u64)p->m_setting, p->m_value08, lp, p->m_db != nullptr, p->m_stmt != nullptr, p->m_inTransaction,
               p->m_beginRequested, (u64)p->m_address, p->m_value48, p->m_prepared, p->m_queryBuffer != nullptr, p->m_queryBufferSize);
}
inline std::string map_state(const ColumnMap& m) {
    const auto& t = m.table;
    u32 load;
    std::memcpy(&load, &t.m_maxLoadFactor, 4);
    std::string s = fmt("map[vt=%d load=%08x size=%u del=%u count=%" PRIu64 ":", t.vtable == column_map_vtable(), load, t.m_size, t.m_deleted,
                        t.m_buckets.m_count);
    for (u64 i = 0; t.m_buckets.m_data && i < t.m_buckets.m_count; i++) {
        const ColumnBucket& b = t.m_buckets.m_data[i];
        if (b.m_state == 1) s += fmt(" %" PRIu64 "=%s:%d", i, b.m_value.first ? b.m_value.first : "null", b.m_value.second);
        else if (b.m_state) s += fmt(" %" PRIu64 "#%u", i, b.m_state);
    }
    return s + "]";
}
inline std::string entity_state(u64 e) {
    auto* p = (const EntityObject*)e;
    return fmt("ent[v00=%" PRIx64 " cols=%d cache=%d/%" PRIu64 " stmt=%d db=%d ", p->m_value00, p->m_numColumns, p->m_cache != nullptr, p->m_cacheSize,
               p->m_stmt != nullptr, p->m_db != nullptr) +
           map_state(p->m_columns) + "]";
}
inline std::string dbl(double d) {
    u64 b;
    std::memcpy(&b, &d, 8);
    return fmt("%.17g(%016" PRIx64 ")", d, b);
}

// QueryParams for a query's values (bound as text), owned by the caller.
inline std::vector<QueryParam> params_of(const std::vector<std::string>& v) {
    std::vector<QueryParam> p(v.size());
    std::memset(p.data(), 0, p.size() * sizeof(QueryParam));
    for (size_t k = 0; k < v.size(); k++) {
        p[k].m_text = v[k].c_str();
        p[k].m_length = (s32)v[k].size();
    }
    return p;
}

// Serialize's result as text plus the bytes' digest (and the buffer freed).
inline std::string serialize_text(Side& s, u64 e, std::vector<u8>* bytes) {
    s64 size = 0x77;
    SharedBytes r = s.serialize(e, &size);
    std::string t = fmt("serialize size=%" PRId64 " buf=%d counter=%d", size, r.m_ptr != nullptr, r.m_counter ? *r.m_counter : -999);
    if (bytes) bytes->clear();
    if (r.m_ptr && size > 0 && bytes) bytes->assign((const u8*)r.m_ptr, (const u8*)r.m_ptr + size);
    if (r.m_ptr) guest::delete_array(r.m_ptr);
    if (r.m_counter) gfn::delete_counter(r.m_counter);
    return t;
}

// One column of the current row through the getters the game uses (by index): the type, then the
// typed getter for it (and GetString for every type).
inline std::string read_column(Side& s, u64 e, int c) {
    s32 type = (s32)s.call(ENT "7GetTypeEim", {e, (u64)(u32)c, 0});
    std::string r = fmt("%d:", type);
    s64 st;
    switch (type) {
    case SQLITE_INTEGER: {
        s32 v = 0x5a5a;
        st = s.status(ENT "10GetIntegerEiPim", {e, (u64)(u32)c, (u64)&v, 0});
        s64 l = 0x5a5a;
        s64 st2 = s.status(ENT "7GetLongEiPlm", {e, (u64)(u32)c, (u64)&l, 0});
        r += fmt("%" PRId64 "/%d %" PRId64 "/%" PRId64, st, v, st2, l);
        break;
    }
    case SQLITE_FLOAT: {
        double d = 0;
        float f = 0;
        st = s.status(ENT "9GetDoubleEiPdm", {e, (u64)(u32)c, (u64)&d, 0});
        s64 st2 = s.status(ENT "8GetFloatEiPfm", {e, (u64)(u32)c, (u64)&f, 0});
        r += fmt("%" PRId64 "/%s %" PRId64 "/%s", st, dbl(d).c_str(), st2, dbl(f).c_str());
        break;
    }
    default: break;
    }
    char buf[256];
    std::memset(buf, 0x5a, sizeof buf);
    u64 size = sizeof buf;
    st = s.status(ENT "9GetStringEiPcPmm", {e, (u64)(u32)c, (u64)buf, (u64)&size, 0});
    buf[sizeof buf - 1] = 0;
    r += fmt(" str %" PRId64 "/%" PRId64 "/'%s'", st, (s64)size, st == 0 ? buf : "");
    return r;
}

// Every column of every row of the entity's statement; every `name_every`-th row also by name.
inline void walk_rows(Side& s, u64 e, size_t name_every, size_t* rows) {
    auto* p = (const EntityObject*)e;
    std::vector<std::string> names;
    for (u64 i = 0; p->m_columns.table.m_buckets.m_data && i < p->m_columns.table.m_buckets.m_count; i++)
        if (p->m_columns.table.m_buckets.m_data[i].m_state == 1) names.push_back(p->m_columns.table.m_buckets.m_data[i].m_value.first);
    for (size_t r = 0;; r++) {
        s64 st = s.status(ENT "5FetchEv", {e});
        if (st != 0) {
            s.add(fmt("fetch %" PRId64, st));
            break;
        }
        ++*rows;
        std::string row;
        for (int c = 0; c < p->m_numColumns; c++) row += read_column(s, e, c) + "|";
        if (name_every && r % name_every == 0) {
            for (auto& n : names) {
                s32 type = (s32)s.call(ENT "7GetTypeEPKcm", {e, (u64)n.c_str(), 0});
                s32 v = 0x5a5a;
                s64 st1 = s.status(ENT "10GetIntegerEPKcPim", {e, (u64)n.c_str(), (u64)&v, 0});
                double d = 0;
                s64 st2 = s.status(ENT "9GetDoubleEPKcPdm", {e, (u64)n.c_str(), (u64)&d, 0});
                char buf[128];
                u64 size = sizeof buf;
                s64 st3 = s.status(ENT "9GetStringEPKcPcPmm", {e, (u64)n.c_str(), (u64)buf, (u64)&size, 0});
                row += fmt("%s=%d,%" PRId64 "/%d,%" PRId64 "/%s,%" PRId64 "/%" PRId64 "/%s;", n.c_str(), type, st1, v, st2, dbl(d).c_str(), st3,
                           (s64)size, st3 == 0 ? std::string(buf, std::min<u64>(size, sizeof buf - 1)).c_str() : "");
            }
            row += " " + entity_state(e);
        }
        s.add(row);
    }
}

// Compares the two sides' logs (the first differences fail the test).
inline bool same_logs(TestContext& t, const Side& g, const Side& n, const char* what) {
    int bad = 0;
    if (g.log.size() != n.log.size()) t.fail("%s: %zu log lines vs %zu", what, g.log.size(), n.log.size());
    for (size_t k = 0; k < g.log.size() && k < n.log.size(); k++)
        if (g.log[k] != n.log[k]) {
            t.fail("%s: line %zu:\n  guest  %.700s\n  native %.700s", what, k, g.log[k].c_str(), n.log[k].c_str());
            if (++bad >= 5) break;
        }
    return bad == 0 && g.log.size() == n.log.size();
}

}  // namespace soa::native::yayoi::test
