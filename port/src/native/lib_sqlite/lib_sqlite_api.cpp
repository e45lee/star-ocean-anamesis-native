// The game's SQLite 3.13.0 replaced by the host SQLite at the API boundary (README.md): the sqlite3_*
// functions the game's own code calls (Aska::Yayoi::SQLiteDriver only), plus sqlite3_free.
//
// What crosses the boundary:
//   - handles (sqlite3*, sqlite3_stmt*, sqlite3_value*) are opaque to the game: host objects;
//   - strings and blobs SQLite returns are host memory, readable by guest code (identity-mapped);
//   - file names are the guest's Android paths: the guest-path VFS (lib_sqlite_vfs.cpp) maps them;
//   - callbacks are guest functions: sqlite3_exec's row callback and sqlite3_bind_text's destructor run
//     through guest_call (the destructor when SQLite releases the text, as 3.13.0 does);
//   - memory SQLite hands out (sqlite3_exec's error message) is the host SQLite's: sqlite3_free is bound
//     too, so the game frees it there.
//
// The live check (soa --live-check lib_sqlite): a shadow run. Every database the game opens is opened in
// the guest's own SQLite too, and every call is repeated there on the shadow handles (the original code,
// through the hooks' trampolines); the results must match: return codes, strings and blobs byte for byte,
// doubles bit for bit, rows in the same order. The guest SQLite's own internal calls to exported sqlite3_*
// functions land on these hooks too: inside a shadow call (t_guest) a hook runs the original.
#include <cinttypes>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/cpu.h"
#include "core/log.h"
#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/common/native.h"
#include "native/lib_sqlite/lib_sqlite.h"

namespace soa::native::lib_sqlite {
namespace {

enum Fn {
#define SOA_SQLITE_ENUM(n) k_##n,
    SOA_SQLITE_API(SOA_SQLITE_ENUM)
#undef SOA_SQLITE_ENUM
        kCount
};
const char* const kSym[kCount] = {
#define SOA_SQLITE_SYM(n) "sqlite3_" #n,
    SOA_SQLITE_API(SOA_SQLITE_SYM)
#undef SOA_SQLITE_SYM
};

// Trampolines to the guest originals (set when the natives are installed).
u64 g_orig[kCount];

// ---- the live check: the shadow run in the guest's SQLite ----

live::Family g_fam("lib_sqlite", 1, false);

// > 0 while this thread runs guest SQLite code for the shadow: the hooks run the originals.
thread_local int t_guest = 0;

struct Shadow {
    std::mutex m;
    std::unordered_map<u64, u64> db, stmt;  // host handle -> guest handle
    struct Val {
        u64 guest, stmt;
    };
    std::unordered_map<u64, Val> val;  // host sqlite3_value* -> the guest's, and the host statement
    std::atomic<u64> checks{0}, bad{0}, skipped{0};
    u64 per_checks[kCount] = {}, per_bad[kCount] = {};
    int logged = 0;
};
Shadow& shadow() {
    static Shadow* s = new Shadow;  // (never destroyed: hooks may run during exit)
    return *s;
}
bool checking() { return g_fam.on.load(std::memory_order_relaxed) && t_guest == 0; }

u64 guest_target(Fn k) {
    static u64 sym[kCount];
    if (g_orig[k]) return g_orig[k];
    if (!sym[k]) sym[k] = guest::sym(kSym[k]);
    return sym[k];
}

template <typename R, typename... A>
R gcall(Fn k, A... a) {
    ++t_guest;
    R r = guest_invoke<R>(guest_target(k), a...);
    --t_guest;
    return r;
}

u64 map_get(std::unordered_map<u64, u64>& m, const void* h) {
    std::lock_guard lk(shadow().m);
    auto it = m.find((u64)(uintptr_t)h);
    return it == m.end() ? 0 : it->second;
}

void write_summary() {
    Shadow& s = shadow();
    if (g_fam.out_path.empty()) return;
    FILE* f = fopen(g_fam.out_path.c_str(), "w");
    if (!f) return;
    fprintf(f, "lib_sqlite live check: %" PRIu64 " checks, %" PRIu64 " mismatches, %" PRIu64 " skipped\n", s.checks.load(),
            s.bad.load(), s.skipped.load());
    std::lock_guard lk(s.m);
    for (int k = 0; k < kCount; k++) fprintf(f, "%-36s %10" PRIu64 " checks %6" PRIu64 " mismatches\n", kSym[k], s.per_checks[k], s.per_bad[k]);
    fclose(f);
}

// One comparison. `what` describes the mismatch; `ctx` is the statement (its SQL goes to the log).
void result(Fn k, bool ok, sqlite3_stmt* ctx, const char* fmt, ...) __attribute__((format(printf, 4, 5)));
void result(Fn k, bool ok, sqlite3_stmt* ctx, const char* fmt, ...) {
    Shadow& s = shadow();
    u64 n = ++s.checks;
    bool log_it = false;
    {
        std::lock_guard lk(s.m);
        s.per_checks[k]++;
        if (!ok) {
            s.per_bad[k]++;
            log_it = s.logged++ < 50;
        }
    }
    if (!ok) {
        s.bad++;
        if (log_it) {
            char buf[512];
            va_list ap;
            va_start(ap, fmt);
            vsnprintf(buf, sizeof buf, fmt, ap);
            va_end(ap);
            const char* sql = ctx ? sqlite3_sql(ctx) : nullptr;
            LOGE("lib_sqlite_check", "MISMATCH %s: %s%s%s", kSym[k], buf, sql ? " | sql: " : "", sql ? sql : "");
        }
        write_summary();
    } else if (n % 20000 == 0) {
        write_summary();
        if (n % 1000000 == 0)
            LOGI("lib_sqlite_check", "%" PRIu64 " checks, %" PRIu64 " mismatches, %" PRIu64 " skipped", n, s.bad.load(), s.skipped.load());
    }
}
void skipped() { shadow().skipped++; }

bool same_str(const char* a, const char* b) { return (!a && !b) || (a && b && strcmp(a, b) == 0); }
const char* show(const char* s) { return s ? s : "(null)"; }

// ---- the natives ----

int n_open(const char* name, sqlite3** pp) {
    register_guest_vfs();
    // (3.13.0's sqlite3_open: READWRITE | CREATE on the default VFS; here the guest-path one)
    int rc = sqlite3_open_v2(name, pp, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, guest_vfs_name());
    if (checking()) {
        u64* out = (u64*)calloc(1, 8);
        int grc = gcall<int>(k_open, name, out);
        result(k_open, rc == grc, nullptr, "rc %d vs %d (%s)", rc, grc, show(name));
        if (*pp && *out) {
            std::lock_guard lk(shadow().m);
            shadow().db[(u64)(uintptr_t)*pp] = *out;
        }
        free(out);
    }
    return rc;
}

int n_close(sqlite3* db) {
    u64 g = checking() ? map_get(shadow().db, db) : 0;
    int rc = sqlite3_close(db);
    if (g) {
        int grc = gcall<int>(k_close, g);
        result(k_close, rc == grc, nullptr, "rc %d vs %d", rc, grc);
        if (rc == SQLITE_OK) {
            std::lock_guard lk(shadow().m);
            shadow().db.erase((u64)(uintptr_t)db);
        }
        write_summary();
    } else if (checking() && db) {
        skipped();
    }
    return rc;
}

// The row callback: a guest function, called through guest_call. With the live check on, each row the
// host passes it is recorded with the callback's answer, and the shadow's exec gets a host callback that
// compares its rows with them and gives the same answers (so an abort happens at the same row).
using Row = std::vector<std::string>;
std::string row_text(int n, char** values, char** names) {
    std::string r;
    for (int k = 0; k < n; k++) r += std::string(names[k] ? names[k] : "(null)") + "=" + (values[k] ? values[k] : "NULL") + "\x1f";
    return r;
}
struct ExecCallback {
    u64 fn, arg;
    bool record;
    std::vector<std::pair<std::string, int>> rows;  // (row, answer)
    size_t replayed = 0;
    bool same = true;
};
int exec_row(void* p, int n, char** values, char** names) {
    auto* cb = (ExecCallback*)p;
    int rc = guest_invoke<int>(cb->fn, cb->arg, (u64)n, values, names);
    if (cb->record) cb->rows.push_back({row_text(n, values, names), rc});
    return rc;
}
int shadow_exec_row(u64 p, int n, char** values, char** names) {
    auto* cb = (ExecCallback*)(uintptr_t)p;
    if (cb->replayed >= cb->rows.size()) {
        cb->same = false;
        return 1;
    }
    auto& [row, rc] = cb->rows[cb->replayed++];
    if (row != row_text(n, values, names)) cb->same = false;
    return rc;
}
// The error message: host memory, freed by the bound sqlite3_free.
int n_exec(sqlite3* db, const char* sql, u64 callback, u64 arg, char** errmsg) {
    u64 g = checking() ? map_get(shadow().db, db) : 0;
    ExecCallback cb{callback, arg, g != 0};
    int rc = sqlite3_exec(db, sql, callback ? exec_row : nullptr, &cb, errmsg);
    if (g) {
        static const u64 replay = make_thunk("lib_sqlite:shadow_exec_row", wrap<&shadow_exec_row>());
        int grc = gcall<int>(k_exec, g, sql, callback ? replay : 0, &cb, 0);
        bool ok = rc == grc && cb.same && cb.replayed == cb.rows.size();
        result(k_exec, ok, nullptr, "rc %d vs %d, rows %zu vs %zu%s (%s)", rc, grc, cb.rows.size(), cb.replayed, cb.same ? "" : " differ", show(sql));
    } else if (checking()) {
        skipped();
    }
    return rc;
}

int n_prepare_v2(sqlite3* db, const char* sql, int bytes, sqlite3_stmt** pp, const char** tail) {
    int rc = sqlite3_prepare_v2(db, sql, bytes, pp, tail);
    if (u64 g = checking() ? map_get(shadow().db, db) : 0) {
        u64* out = (u64*)calloc(2, 8);
        int grc = gcall<int>(k_prepare_v2, g, sql, bytes, out, out + 1);
        bool ok = rc == grc && (*pp != nullptr) == (out[0] != 0);
        if (ok && tail) ok = (u64)(uintptr_t)*tail == out[1];
        result(k_prepare_v2, ok, nullptr, "rc %d vs %d, stmt %d vs %d (%s)", rc, grc, *pp != nullptr, out[0] != 0, show(sql));
        if (*pp && out[0]) {
            std::lock_guard lk(shadow().m);
            shadow().stmt[(u64)(uintptr_t)*pp] = out[0];
        }
        free(out);
    } else if (checking()) {
        skipped();
    }
    return rc;
}

const char* n_errmsg(sqlite3* db) {
    const char* m = sqlite3_errmsg(db);
    if (u64 g = checking() ? map_get(shadow().db, db) : 0) {
        // The text isn't compared, only that both have one: its one caller (SQLiteDriver::_Prepare)
        // drops it, and the texts differ between versions (3.13.0 'near " ": syntax error', 3.45.1
        // "incomplete input"). A different text is logged.
        const char* gm = gcall<const char*>(k_errmsg, g);
        result(k_errmsg, (m != nullptr) == (gm != nullptr), nullptr, "%s vs %s", show(m), show(gm));
        if (m && gm && strcmp(m, gm) != 0) LOGW("lib_sqlite_check", "sqlite3_errmsg: \"%s\" (host) vs \"%s\" (guest)", m, gm);
    }
    return m;
}

int n_bind_parameter_count(sqlite3_stmt* st) {
    int n = sqlite3_bind_parameter_count(st);
    if (u64 g = checking() ? map_get(shadow().stmt, st) : 0) {
        int gn = gcall<int>(k_bind_parameter_count, g);
        result(k_bind_parameter_count, n == gn, st, "%d vs %d", n, gn);
    }
    return n;
}

// The destructor: SQLITE_STATIC (0) and SQLITE_TRANSIENT (-1) pass through. A guest function: the host
// SQLite gets release_text, which calls it (guest_call) when SQLite releases the text, as 3.13.0 would
// (a failed bind at once, a NULL text that binds never: bindText is the same in both versions).
std::mutex g_dtor_m;
std::unordered_multimap<const void*, u64> g_dtors;  // text -> its guest destructor
void release_text(void* p) {
    u64 fn = 0;
    {
        std::lock_guard lk(g_dtor_m);
        auto it = g_dtors.find(p);
        if (it == g_dtors.end()) return;
        fn = it->second;
        g_dtors.erase(it);
    }
    guest_invoke<void>(fn, p);
}
int n_bind_text(sqlite3_stmt* st, int i, const char* text, int bytes, u64 destructor) {
    bool guest_fn = destructor != 0 && destructor != (u64)-1;
    if (guest_fn) {
        std::lock_guard lk(g_dtor_m);
        g_dtors.insert({text, destructor});
    }
    int rc = sqlite3_bind_text(st, i, text, bytes, destructor == 0 ? SQLITE_STATIC : guest_fn ? release_text : SQLITE_TRANSIENT);
    if (guest_fn && rc == SQLITE_OK && !text) {  // (never released)
        std::lock_guard lk(g_dtor_m);
        auto it = g_dtors.find(text);
        if (it != g_dtors.end()) g_dtors.erase(it);
    }
    if (u64 g = checking() ? map_get(shadow().stmt, st) : 0) {
        // (the shadow binds a copy: the guest's text may be released before the shadow lets it go)
        int grc = gcall<int>(k_bind_text, g, i, text, bytes, destructor == 0 ? (u64)0 : (u64)-1);
        result(k_bind_text, rc == grc, st, "rc %d vs %d (?%d)", rc, grc, i);
    }
    return rc;
}

int n_step(sqlite3_stmt* st) {
    int rc = sqlite3_step(st);
    if (u64 g = checking() ? map_get(shadow().stmt, st) : 0) {
        int grc = gcall<int>(k_step, g);
        result(k_step, rc == grc, st, "rc %d vs %d", rc, grc);
    } else if (checking() && st) {
        skipped();
    }
    return rc;
}

int n_reset(sqlite3_stmt* st) {
    int rc = sqlite3_reset(st);
    if (u64 g = checking() ? map_get(shadow().stmt, st) : 0) {
        int grc = gcall<int>(k_reset, g);
        result(k_reset, rc == grc, st, "rc %d vs %d", rc, grc);
    }
    return rc;
}

int n_finalize(sqlite3_stmt* st) {
    u64 g = checking() ? map_get(shadow().stmt, st) : 0;
    std::string sql = g && sqlite3_sql(st) ? sqlite3_sql(st) : "";
    int rc = sqlite3_finalize(st);
    if (g) {
        int grc = gcall<int>(k_finalize, g);
        result(k_finalize, rc == grc, nullptr, "rc %d vs %d (%s)", rc, grc, sql.c_str());
        Shadow& s = shadow();
        std::lock_guard lk(s.m);
        s.stmt.erase((u64)(uintptr_t)st);
        for (auto it = s.val.begin(); it != s.val.end();) it = it->second.stmt == (u64)(uintptr_t)st ? s.val.erase(it) : std::next(it);
    }
    return rc;
}

int n_column_count(sqlite3_stmt* st) {
    int n = sqlite3_column_count(st);
    if (u64 g = checking() ? map_get(shadow().stmt, st) : 0) {
        int gn = gcall<int>(k_column_count, g);
        result(k_column_count, n == gn, st, "%d vs %d", n, gn);
    }
    return n;
}

const char* n_column_name(sqlite3_stmt* st, int i) {
    const char* s = sqlite3_column_name(st, i);
    if (u64 g = checking() ? map_get(shadow().stmt, st) : 0) {
        const char* gs = gcall<const char*>(k_column_name, g, i);
        result(k_column_name, same_str(s, gs), st, "column %d: \"%s\" vs \"%s\"", i, show(s), show(gs));
    }
    return s;
}

sqlite3_value* n_column_value(sqlite3_stmt* st, int i) {
    sqlite3_value* v = sqlite3_column_value(st, i);
    if (u64 g = checking() ? map_get(shadow().stmt, st) : 0) {
        u64 gv = gcall<u64>(k_column_value, g, i);
        result(k_column_value, (v != nullptr) == (gv != 0), st, "column %d: value %d vs %d", i, v != nullptr, gv != 0);
        if (v && gv) {
            std::lock_guard lk(shadow().m);
            shadow().val[(u64)(uintptr_t)v] = {gv, (u64)(uintptr_t)st};
        }
    }
    return v;
}

// A host value's shadow (0: none) and its statement (for the log).
u64 value_shadow(const sqlite3_value* v, sqlite3_stmt** st) {
    std::lock_guard lk(shadow().m);
    auto it = shadow().val.find((u64)(uintptr_t)v);
    if (it == shadow().val.end()) return 0;
    *st = (sqlite3_stmt*)(uintptr_t)it->second.stmt;
    return it->second.guest;
}

int n_value_type(sqlite3_value* v) {
    int t = sqlite3_value_type(v);
    sqlite3_stmt* st = nullptr;
    if (u64 g = checking() ? value_shadow(v, &st) : 0) {
        int gt = gcall<int>(k_value_type, g);
        result(k_value_type, t == gt, st, "%d vs %d", t, gt);
    }
    return t;
}

int n_value_int(sqlite3_value* v) {
    int r = sqlite3_value_int(v);
    sqlite3_stmt* st = nullptr;
    if (u64 g = checking() ? value_shadow(v, &st) : 0) {
        int gr = gcall<int>(k_value_int, g);
        result(k_value_int, r == gr, st, "%d vs %d", r, gr);
    }
    return r;
}

s64 n_value_int64(sqlite3_value* v) {
    s64 r = sqlite3_value_int64(v);
    sqlite3_stmt* st = nullptr;
    if (u64 g = checking() ? value_shadow(v, &st) : 0) {
        s64 gr = gcall<s64>(k_value_int64, g);
        result(k_value_int64, r == gr, st, "%" PRId64 " vs %" PRId64, r, gr);
    }
    return r;
}

double n_value_double(sqlite3_value* v) {
    double r = sqlite3_value_double(v);
    sqlite3_stmt* st = nullptr;
    if (u64 g = checking() ? value_shadow(v, &st) : 0) {
        double gr = gcall<double>(k_value_double, g);
        result(k_value_double, memcmp(&r, &gr, 8) == 0, st, "%.17g vs %.17g", r, gr);
    }
    return r;
}

const unsigned char* n_value_text(sqlite3_value* v) {
    const unsigned char* r = sqlite3_value_text(v);
    sqlite3_stmt* st = nullptr;
    if (u64 g = checking() ? value_shadow(v, &st) : 0) {
        auto* gr = gcall<const char*>(k_value_text, g);
        result(k_value_text, same_str((const char*)r, gr), st, "\"%.100s\" vs \"%.100s\"", show((const char*)r), show(gr));
    }
    return r;
}

const void* n_value_blob(sqlite3_value* v) {
    const void* r = sqlite3_value_blob(v);
    sqlite3_stmt* st = nullptr;
    if (u64 g = checking() ? value_shadow(v, &st) : 0) {
        const void* gr = gcall<const void*>(k_value_blob, g);
        // (the sizes after the blob, as the game reads them: sqlite3_value_bytes doesn't convert a blob)
        int n = sqlite3_value_bytes(v), gn = gcall<int>(k_value_bytes, g);
        bool ok = n == gn && (r != nullptr) == (gr != nullptr) && (!r || n <= 0 || memcmp(r, gr, (size_t)n) == 0);
        result(k_value_blob, ok, st, "%d bytes vs %d", n, gn);
    }
    return r;
}

int n_value_bytes(sqlite3_value* v) {
    int r = sqlite3_value_bytes(v);
    sqlite3_stmt* st = nullptr;
    if (u64 g = checking() ? value_shadow(v, &st) : 0) {
        int gr = gcall<int>(k_value_bytes, g);
        result(k_value_bytes, r == gr, st, "%d vs %d", r, gr);
    }
    return r;
}

// (memory the host SQLite handed out: sqlite3_exec's error message)
void n_free(void* p) { sqlite3_free(p); }

// ---- the hooks ----

// Inside a shadow call the guest SQLite's own calls to its exported functions run the originals.
void run_original(Cpu& c, u64 orig) {
    GuestArgs a;
    for (int k = 0; k < 8; k++) a.i(c.x(k));
    for (int k = 0; k < 8; k++) a.vecs.push_back(c.v(k));
    a.x8 = c.x(8);
    GuestResult g = guest_call(orig, a);
    c.set_x(0, g.x0);
    c.set_x(1, g.x1);
    c.set_v(0, g.v0);
    c.set_v(1, g.v1);
}

template <auto F, Fn K>
void hook(Cpu& c) {
    if (t_guest > 0 && g_orig[K]) return run_original(c, g_orig[K]);
    wrap<F>()(c);
}

#define SOA_SQLITE_REGISTER(n)                                                                                       \
    static bool reg_##n = register_native_function(                                                                  \
        {"sqlite3_" #n, &hook<&n_##n, k_##n>, "lib_sqlite: host SQLite (sqlite3_" #n ")", nullptr, &g_orig[k_##n]});
SOA_SQLITE_API(SOA_SQLITE_REGISTER)
#undef SOA_SQLITE_REGISTER

}  // namespace

Api guest_api() {
    Api a;
#define SOA_SQLITE_GUEST(n) a.n = guest::sym("sqlite3_" #n);
    SOA_SQLITE_API(SOA_SQLITE_GUEST)
#undef SOA_SQLITE_GUEST
    return a;
}

Api native_api() {
    static const Api a = [] {
        Api r;
#define SOA_SQLITE_THUNK(n) r.n = make_thunk("lib_sqlite:sqlite3_" #n, &hook<&n_##n, k_##n>);
        SOA_SQLITE_API(SOA_SQLITE_THUNK)
#undef SOA_SQLITE_THUNK
        return r;
    }();
    return a;
}

// The live check's counters (the tests of the check itself).
void live_counts(u64* checks, u64* bad, u64* skip) {
    *checks = shadow().checks, *bad = shadow().bad, *skip = shadow().skipped;
}
void live_switch(bool on) { g_fam.on = on; }

}  // namespace soa::native::lib_sqlite
