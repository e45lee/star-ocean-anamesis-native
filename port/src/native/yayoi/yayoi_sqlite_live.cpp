// The SQLite driver family's live check: a shadow run (yayoi_sqlite_live.h). soa --live-check
// yayoi_sqlite[:out=FILE].
#include "native/yayoi/yayoi_sqlite_live.h"

#include <algorithm>
#include <atomic>
#include <cinttypes>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/log.h"
#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/yayoi/yayoi_guest.h"
#include "native/yayoi/yayoi_layout.h"
#include "native/yayoi/yayoi_sqlite.h"

namespace soa::native::yayoi::live {

u64 g_orig[kFnCount];

namespace {

soa::live::Family g_fam("yayoi_sqlite", 1);

// > 0 while this thread runs a shadow call: the hooks run the originals.
thread_local int t_shadow = 0;

struct State {
    std::mutex m;
    std::unordered_map<u64, u64> drivers, entities;  // the game's object -> its shadow
    std::atomic<u64> checks{0}, bad{0}, skipped{0};
    u64 per_checks[kFnCount] = {}, per_bad[kFnCount] = {}, per_skip[kFnCount] = {};
    int logged = 0;
};
State& state() {
    static State* s = new State;  // (never destroyed: hooks may run during exit)
    return *s;
}

void write_summary() {
    State& s = state();
    if (g_fam.out_path.empty()) return;
    FILE* f = fopen(g_fam.out_path.c_str(), "w");
    if (!f) return;
    fprintf(f, "yayoi_sqlite live check: %" PRIu64 " checks, %" PRIu64 " mismatches, %" PRIu64 " skipped\n", s.checks.load(),
            s.bad.load(), s.skipped.load());
    std::lock_guard lk(s.m);
    for (int k = 0; k < kFnCount; k++)
        fprintf(f, "%-52s %10" PRIu64 " checks %6" PRIu64 " mismatches %6" PRIu64 " skipped\n", info((Fn)k).label + 7, s.per_checks[k],
                s.per_bad[k], s.per_skip[k]);
    fclose(f);
}

void skip(Fn k) {
    State& s = state();
    s.skipped++;
    std::lock_guard lk(s.m);
    s.per_skip[k]++;
}

// One check of a call: `diff` empty when the shadow agreed.
void result(Fn k, const std::string& diff) {
    State& s = state();
    u64 n = ++s.checks;
    bool log_it = false;
    {
        std::lock_guard lk(s.m);
        s.per_checks[k]++;
        if (!diff.empty()) {
            s.per_bad[k]++;
            log_it = s.logged++ < 50;
        }
    }
    if (!diff.empty()) {
        s.bad++;
        if (log_it) LOGE("yayoi_sqlite_check", "MISMATCH %s: %s", info(k).label + 7, diff.c_str());
        write_summary();
    } else if (n % 1000 == 0) {
        write_summary();
        if (n % 1000000 == 0)
            LOGI("yayoi_sqlite_check", "%" PRIu64 " checks, %" PRIu64 " mismatches, %" PRIu64 " skipped", n, s.bad.load(), s.skipped.load());
    }
}

std::string fmt(const char* f, ...) __attribute__((format(printf, 1, 2)));
std::string fmt(const char* f, ...) {
    char b[512];
    va_list ap;
    va_start(ap, f);
    vsnprintf(b, sizeof b, f, ap);
    va_end(ap);
    return b;
}

u64 lookup(std::unordered_map<u64, u64>& m, u64 key) {
    std::lock_guard lk(state().m);
    auto it = m.find(key);
    return it == m.end() ? 0 : it->second;
}

// ---- the objects' states ----

std::string diff_driver(const SQLiteDriver& a, const SQLiteDriver& s) {
    std::string d;
    auto f = [&](const char* name, u64 x, u64 y) {
        if (x != y) d += fmt("%s %" PRIx64 " vs %" PRIx64 "; ", name, x, y);
    };
    f("m_setting", (u64)a.m_setting, (u64)s.m_setting);
    f("m_value08", a.m_value08, s.m_value08);
    f("m_lastParams", (u64)a.m_lastParams, (u64)s.m_lastParams);
    f("m_db?", a.m_db != nullptr, s.m_db != nullptr);
    f("m_stmt?", a.m_stmt != nullptr, s.m_stmt != nullptr);
    f("m_inTransaction", a.m_inTransaction, s.m_inTransaction);
    f("m_beginRequested", a.m_beginRequested, s.m_beginRequested);
    f("m_address", (u64)a.m_address, (u64)s.m_address);
    f("m_value48", a.m_value48, s.m_value48);
    f("m_prepared", a.m_prepared, s.m_prepared);
    // (m_queryBuffer / m_buffer50: the master side's BuildQuery writes the game's driver only)
    return d;
}

std::string diff_entity(const EntityObject& a, const EntityObject& s) {
    std::string d;
    auto f = [&](const char* name, u64 x, u64 y) {
        if (x != y) d += fmt("%s %" PRIx64 " vs %" PRIx64 "; ", name, x, y);
    };
    f("m_value00", a.m_value00, s.m_value00);
    f("m_numColumns", (u32)a.m_numColumns, (u32)s.m_numColumns);
    f("m_cache?", a.m_cache != nullptr, s.m_cache != nullptr);
    f("m_cacheSize", a.m_cacheSize, s.m_cacheSize);
    f("m_stmt?", a.m_stmt != nullptr, s.m_stmt != nullptr);
    f("m_db?", a.m_db != nullptr, s.m_db != nullptr);
    const auto& x = a.m_columns.table;
    const auto& y = s.m_columns.table;
    u32 lx, ly;
    std::memcpy(&lx, &x.m_maxLoadFactor, 4);
    std::memcpy(&ly, &y.m_maxLoadFactor, 4);
    f("map vtable", (u64)x.vtable, (u64)y.vtable);
    f("map maxLoad", lx, ly);
    f("map size", x.m_size, y.m_size);
    f("map deleted", x.m_deleted, y.m_deleted);
    f("map buckets?", x.m_buckets.m_data != nullptr, y.m_buckets.m_data != nullptr);
    f("map count", x.m_buckets.m_count, y.m_buckets.m_count);
    if (!d.empty() || !x.m_buckets.m_data || !y.m_buckets.m_data) return d;
    for (u64 i = 0; i < x.m_buckets.m_count; i++) {
        const ColumnBucket& p = x.m_buckets.m_data[i];
        const ColumnBucket& q = y.m_buckets.m_data[i];
        if (p.m_state != q.m_state) return d + fmt("bucket %" PRIu64 " state %u vs %u", i, p.m_state, q.m_state);
        if (p.m_state != 1) continue;
        bool same_key = p.m_value.first && q.m_value.first ? std::strcmp(p.m_value.first, q.m_value.first) == 0 : p.m_value.first == q.m_value.first;
        if (!same_key || p.m_value.second != q.m_value.second)
            return d + fmt("bucket %" PRIu64 " (%s, %d) vs (%s, %d)", i, p.m_value.first ? p.m_value.first : "null", p.m_value.second,
                           q.m_value.first ? q.m_value.first : "null", q.m_value.second);
    }
    return d;
}

std::string diff_bytes(const char* what, const void* a, const void* b, u64 n) {
    if (n == 0 || std::memcmp(a, b, n) == 0) return "";
    const u8* p = (const u8*)a;
    const u8* q = (const u8*)b;
    u64 i = 0;
    while (p[i] == q[i]) i++;
    return fmt("%s differ at byte %" PRIu64 " of %" PRIu64 " (%02x vs %02x); ", what, i, n, p[i], q[i]);
}

GuestResult run_shadow(Fn k, const u64 x[8], u64 x8) {
    GuestArgs a;
    for (int i = 0; i < 8; i++) a.i(x[i]);
    a.x8 = x8;
    ++t_shadow;
    GuestResult g = guest_call(g_orig[k], a);
    --t_shadow;
    return g;
}

}  // namespace

bool on() { return g_fam.on.load(std::memory_order_relaxed) && t_shadow == 0; }

bool forward(Cpu& c, Fn k) {
    if (t_shadow == 0 || !g_orig[k]) return false;
    GuestArgs a;
    for (int i = 0; i < 8; i++) a.i(c.x(i));
    for (int i = 0; i < 8; i++) a.vecs.push_back(c.v(i));
    a.x8 = c.x(8);
    GuestResult g = guest_call(g_orig[k], a);
    c.set_x(0, g.x0);
    c.set_x(1, g.x1);
    c.set_v(0, g.v0);
    return true;
}

void before(Cpu& c, Fn k, Call* call) {
    call->k = k;
    for (int i = 0; i < 8; i++) call->x[i] = c.x(i);
    call->x8 = c.x(8);
    const FnInfo& fi = info(k);
    auto snap = [&](u64 p, u64 n) {
        if (p) call->out_before.assign((const u8*)p, (const u8*)p + n);
    };
    switch (fi.out) {
    case Out::None: break;
    case Out::Value: snap(call->x[2], fi.bytes); break;
    case Out::U64At1: snap(call->x[1], 8); break;
    case Out::U64At2: snap(call->x[2], 8); break;
    case Out::I32At2: snap(call->x[2], 4); break;
    case Out::SizeAt1: snap(call->x[1], 8); break;
    case Out::Text:
    case Out::Data:
        if (call->x[3]) call->size_before = *(const u64*)call->x[3];
        if (fi.out == Out::Text && call->x[2] && call->x[3]) snap(call->x[2], std::min<u64>(call->size_before, 1u << 20));
        break;
    }
}

void after(Cpu& c, Call& call) {
    const Fn k = call.k;
    const FnInfo& fi = info(k);
    State& s = state();
    u64 shadow = 0;
    bool ctor = k == kDriverCtor || k == kEntityCtor;
    bool dtor = k == kDriverDtor || k == kEntityDtor;
    if (k == kStore || k == kMapInsertRange || k == kMapDtor || k == kMapDtorDelete) {
        // (only the family's own code calls these on the game's objects; the shadow can't be given the
        // game's statement or iterators into the game's buckets, nor destroy part of a shadow object)
        return skip(k);
    }
    if (ctor) {
        u64 size = k == kDriverCtor ? sizeof(SQLiteDriver) : sizeof(EntityObject);
        shadow = (u64)std::calloc(1, size);
    } else if (fi.obj == Obj::Driver) {
        shadow = lookup(s.drivers, call.x[0]);
    } else if (fi.obj == Obj::Entity) {
        shadow = lookup(s.entities, call.x[0]);
    } else {
        u64 e = lookup(s.entities, call.x[0] - offsetof(EntityObject, m_columns));
        shadow = e ? e + offsetof(EntityObject, m_columns) : 0;
    }
    if (!shadow) return skip(k);

    u64 x[8];
    std::memcpy(x, call.x, sizeof x);
    x[0] = shadow;
    u64 shadow_entity = 0;
    if (k == kFind || k == k_Execute) {
        if (x[4]) {
            shadow_entity = lookup(s.entities, x[4]);
            if (!shadow_entity) return skip(k);
            x[4] = shadow_entity;
        }
    }
    // the out-parameters: the shadow's copies, as they were before the native wrote them
    std::vector<u8> out(call.out_before);
    u64 shadow_size = call.size_before;
    switch (fi.out) {
    case Out::None: break;
    case Out::Value:
    case Out::I32At2:
    case Out::U64At2:
        if (x[2]) x[2] = (u64)out.data();
        break;
    case Out::U64At1:
    case Out::SizeAt1:
        if (x[1]) x[1] = (u64)out.data();
        break;
    case Out::Text:
        if (x[3]) x[3] = (u64)&shadow_size;
        if (x[2]) {
            out.resize(std::max<u64>(out.size(), 1));
            x[2] = (u64)out.data();
        }
        break;
    case Out::Data:
        if (x[3]) x[3] = (u64)&shadow_size;
        if (x[2]) {
            u64 written = call.x[3] ? *(const u64*)call.x[3] : 0;
            out.assign(std::max<u64>(written, call.size_before) * 2 + 4096, 0);
            x[2] = (u64)out.data();
        }
        break;
    }
    alignas(16) u8 ret[32] = {};
    GuestResult g = run_shadow(k, x, (u64)ret);

    std::string d;
    switch (fi.ret) {
    case Ret::Status: {
        s64 a = *(const s64*)call.x8, b;
        std::memcpy(&b, ret, 8);
        if (a != b) d += fmt("status %" PRId64 " vs %" PRId64 "; ", a, b);
        break;
    }
    case Ret::Int:
        if ((u32)c.x(0) != (u32)g.x0) d += fmt("result %d vs %d; ", (s32)c.x(0), (s32)g.x0);
        break;
    case Ret::Ptr:
        if ((c.x(0) != 0) != (g.x0 != 0)) d += fmt("pointer %d vs %d; ", c.x(0) != 0, g.x0 != 0);
        break;
    case Ret::U64:
        if (c.x(0) != g.x0) d += fmt("result %" PRIx64 " vs %" PRIx64 "; ", c.x(0), g.x0);
        break;
    case Ret::Void: break;
    case Ret::Shared: {
        const SharedBytes& a = *(const SharedBytes*)call.x8;
        SharedBytes b;
        std::memcpy(&b, ret, sizeof b);
        s64 na = call.x[1] ? *(const s64*)call.x[1] : 0, nb = 0;
        if (x[1]) std::memcpy(&nb, out.data(), 8);
        if (na != nb) d += fmt("size %" PRId64 " vs %" PRId64 "; ", na, nb);
        if ((a.m_ptr != nullptr) != (b.m_ptr != nullptr) || (a.m_counter != nullptr) != (b.m_counter != nullptr))
            d += fmt("buffer %d/%d vs %d/%d; ", a.m_ptr != nullptr, a.m_counter != nullptr, b.m_ptr != nullptr, b.m_counter != nullptr);
        else if (a.m_counter && *a.m_counter != *b.m_counter)
            d += fmt("counter %d vs %d; ", *a.m_counter, *b.m_counter);
        if (d.empty() && a.m_ptr && na > 0) d += diff_bytes("MessagePack", a.m_ptr, b.m_ptr, (u64)na);
        if (b.m_ptr) guest::delete_array(b.m_ptr);
        if (b.m_counter) gfn::delete_counter(b.m_counter);
        break;
    }
    case Ret::InsertResult: {
        const ColumnMapInsertResult& a = *(const ColumnMapInsertResult*)call.x8;
        ColumnMapInsertResult b;
        std::memcpy(&b, ret, sizeof b);
        if (a.m_inserted != b.m_inserted || a.m_it.m_bucket - a.m_it.m_begin != b.m_it.m_bucket - b.m_it.m_begin ||
            a.m_it.m_end - a.m_it.m_begin != b.m_it.m_end - b.m_it.m_begin)
            d += fmt("iterator %td/%td %d vs %td/%td %d; ", a.m_it.m_bucket - a.m_it.m_begin, a.m_it.m_end - a.m_it.m_begin, a.m_inserted,
                     b.m_it.m_bucket - b.m_it.m_begin, b.m_it.m_end - b.m_it.m_begin, b.m_inserted);
        break;
    }
    }
    switch (fi.out) {
    case Out::None:
    case Out::SizeAt1: break;
    case Out::Value:
    case Out::I32At2:
    case Out::U64At2:
        if (call.x[2]) d += diff_bytes("out", (const void*)call.x[2], out.data(), out.size());
        break;
    case Out::U64At1:
        if (call.x[1]) d += diff_bytes("out", (const void*)call.x[1], out.data(), out.size());
        break;
    case Out::Text:
    case Out::Data: {
        u64 na = call.x[3] ? *(const u64*)call.x[3] : 0;
        if (call.x[3] && na != shadow_size) d += fmt("*size %" PRId64 " vs %" PRId64 "; ", (s64)na, (s64)shadow_size);
        if (call.x[2] && d.empty()) {
            u64 n = fi.out == Out::Text ? std::min<u64>(call.size_before, 1u << 20) : std::min<u64>(na, out.size());
            d += diff_bytes("buffer", (const void*)call.x[2], out.data(), n);
        }
        break;
    }
    }
    if (fi.obj == Obj::Driver) d += diff_driver(*(const SQLiteDriver*)call.x[0], *(const SQLiteDriver*)shadow);
    else if (fi.obj == Obj::Entity) d += diff_entity(*(const EntityObject*)call.x[0], *(const EntityObject*)shadow);
    else d += diff_entity(*(const EntityObject*)(call.x[0] - offsetof(EntityObject, m_columns)),
                          *(const EntityObject*)(shadow - offsetof(EntityObject, m_columns)));
    if (shadow_entity) {
        std::string e = diff_entity(*(const EntityObject*)call.x[4], *(const EntityObject*)shadow_entity);
        if (!e.empty()) d += "entity: " + e;
    }
    if (!d.empty() && fi.obj == Obj::Driver && call.x[1] && (k == kFind || k == k_Execute || k == kExecute || k == k_Prepare))
        d += fmt(" (sql: %.200s)", (const char*)call.x[1]);
    result(k, d);

    if (ctor) {
        std::lock_guard lk(s.m);
        auto& m = k == kDriverCtor ? s.drivers : s.entities;
        m[call.x[0]] = shadow;  // (a constructor over a live object replaces its shadow; the old one leaks)
    } else if (dtor) {
        {
            std::lock_guard lk(s.m);
            (k == kDriverDtor ? s.drivers : s.entities).erase(call.x[0]);
        }
        std::free((void*)shadow);
        if (k == kDriverDtor) write_summary();
    }
    if (k == kDoOpen && call.x[3]) {
        const DBAddress* a = (const DBAddress*)call.x[3];
        LOGI("yayoi_sqlite_check", "DoOpen %s (driver %" PRIx64 ", shadow %" PRIx64 ")", a->m_path ? a->m_path : "(null)", call.x[0], shadow);
        write_summary();
    }
}

}  // namespace soa::native::yayoi::live

namespace soa::native::yayoi {

void driver_live_counts(u64* checks, u64* mismatches, u64* skipped) {
    auto& s = live::state();
    *checks = s.checks, *mismatches = s.bad, *skipped = s.skipped;
}
void driver_live_switch(bool on) { live::g_fam.on = on; }

}  // namespace soa::native::yayoi
