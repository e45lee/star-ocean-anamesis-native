// Differential tests of what the bridge carries across the boundary (lib_sqlite_api.cpp): guest callbacks
// (sqlite3_exec's row callback, sqlite3_bind_text's destructor), the host-allocated error message and
// sqlite3_free, binds (static, transient, lengths), statement tails; each run on the guest's SQLite and on
// the natives through the same guest calls. And the live check itself: a shadowed run matches, a diverged
// one is caught.
#include <sqlite3.h>

#include <cstring>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/lib_sqlite/lib_sqlite.h"

namespace soa::native::lib_sqlite {
namespace {

// The guest callbacks: thunks to host functions recording what they're called with.
std::vector<std::string> g_rows;
int exec_cb(u64 arg, int n, char** values, char** names) {
    std::string r = std::to_string(arg) + ":";
    for (int k = 0; k < n; k++) r += std::string(names[k]) + "=" + (values[k] ? values[k] : "NULL") + ";";
    g_rows.push_back(r);
    return arg == 7 && g_rows.size() >= 2 ? 1 : 0;  // (arg 7: abort after two rows)
}
std::vector<std::string> g_freed;
void destructor(const char* p) { g_freed.push_back(p ? p : "(null)"); }

struct Trace {
    std::vector<std::string> v;
    void add(const std::string& what, long long x) { v.push_back(what + "=" + std::to_string(x)); }
    void str(const std::string& what, const char* s) { v.push_back(what + "=" + (s ? s : "(null)")); }
};

// One scripted session on one side; everything observable goes to the trace.
Trace session(const Api& a) {
    static const u64 cb = make_thunk("test:lib_sqlite:exec_cb", wrap<&exec_cb>());
    static const u64 dtor = make_thunk("test:lib_sqlite:destructor", wrap<&destructor>());
    Trace t;
    g_rows.clear();
    g_freed.clear();
    u64* out = (u64*)calloc(4, 8);
    t.add("open", guest_invoke<int>(a.open, ":memory:", out));
    u64 db = out[0];
    const char* setup = "create table t(a integer, b text, c real, d blob); insert into t values(1,'one',1.5,x'00ff');"
                        "insert into t values(2,NULL,-0.25,NULL); insert into t values(3,'three',1e300,x'');";
    t.add("exec setup", guest_invoke<int>(a.exec, db, setup, 0, 0, 0));
    // the row callback (a guest function), its argument, and its abort (non-zero -> SQLITE_ABORT)
    t.add("exec cb", guest_invoke<int>(a.exec, db, "select * from t order by a", cb, (u64)5, 0));
    t.add("exec cb abort", guest_invoke<int>(a.exec, db, "select a, b from t order by a", cb, (u64)7, 0));
    for (auto& r : g_rows) t.str("row", r.c_str());
    // the error message: allocated by that side's SQLite, freed by its sqlite3_free
    out[1] = 0;
    t.add("exec bad", guest_invoke<int>(a.exec, db, "select * from nosuch", 0, 0, out + 1));
    t.add("errmsg set", out[1] != 0);
    if (out[1]) {
        t.str("errmsg", (const char*)out[1]);  // ("no such table: nosuch" in both versions)
        guest_invoke<void>(a.free, out[1]);
    }
    // binds: a guest destructor, SQLITE_TRANSIENT with the buffer changed after the bind, explicit lengths
    t.add("prepare", guest_invoke<int>(a.prepare_v2, db, "select ?1, ?2, ?3, length(?3); select 2", -1, out + 2, out + 3));
    u64 st = out[2];
    t.add("tail", (long long)(out[3] - (u64)0));
    char* owned = strdup("owned by the guest");
    char buf[16] = "transient";
    t.add("params", guest_invoke<int>(a.bind_parameter_count, st));
    t.add("bind 1", guest_invoke<int>(a.bind_text, st, 1, owned, -1, dtor));
    t.add("bind 2 null", guest_invoke<int>(a.bind_text, st, 2, (const char*)nullptr, -1, dtor));  // (no destructor call)
    t.add("bind 2", guest_invoke<int>(a.bind_text, st, 2, buf, -1, (u64)-1));
    strcpy(buf, "changed");
    t.add("bind 3", guest_invoke<int>(a.bind_text, st, 3, "abcdef", 3, (u64)0));
    t.add("bind 9", guest_invoke<int>(a.bind_text, st, 9, "range", -1, (u64)0));  // SQLITE_RANGE
    t.add("bind 9 dtor", guest_invoke<int>(a.bind_text, st, 9, "failed bind", -1, dtor));  // (destructor at once)
    t.add("destructor calls after a failed bind", (long long)g_freed.size());
    t.add("step", guest_invoke<int>(a.step, st));
    for (int i = 0; i < 4; i++) {
        u64 v = guest_invoke<u64>(a.column_value, st, i);
        t.str("value", guest_invoke<const char*>(a.value_text, v));
        t.add("bytes", guest_invoke<int>(a.value_bytes, v));
    }
    t.add("step 2", guest_invoke<int>(a.step, st));
    t.add("reset", guest_invoke<int>(a.reset, st));
    t.add("finalize", guest_invoke<int>(a.finalize, st));
    t.add("destructor calls", (long long)g_freed.size());
    for (auto& f : g_freed) t.str("destroyed", f.c_str());
    free(owned);
    // blobs and types, read the game's way
    t.add("prepare 2", guest_invoke<int>(a.prepare_v2, db, "select * from t order by a", -1, out + 2, 0));
    st = out[2];
    t.add("columns", guest_invoke<int>(a.column_count, st));
    for (int i = 0; i < 4; i++) t.str("name", guest_invoke<const char*>(a.column_name, st, i));
    while (guest_invoke<int>(a.step, st) == SQLITE_ROW) {
        for (int i = 0; i < 4; i++) {
            u64 v = guest_invoke<u64>(a.column_value, st, i);
            int type = guest_invoke<int>(a.value_type, v);
            t.add("type", type);
            if (type == SQLITE_INTEGER) t.add("int", guest_invoke<int>(a.value_int, v)), t.add("int64", guest_invoke<s64>(a.value_int64, v));
            if (type == SQLITE_FLOAT) {
                double d = guest_invoke<double>(a.value_double, v);
                long long bits;
                memcpy(&bits, &d, 8);
                t.add("double bits", bits);
            }
            if (type == SQLITE_BLOB) {
                const u8* p = guest_invoke<const u8*>(a.value_blob, v);
                int n = guest_invoke<int>(a.value_bytes, v);
                t.add("blob bytes", n);
                for (int k = 0; k < n; k++) t.add("blob", p[k]);
            }
            if (type == SQLITE_TEXT) t.str("text", guest_invoke<const char*>(a.value_text, v));
        }
    }
    t.add("finalize 2", guest_invoke<int>(a.finalize, st));
    t.add("finalize null", guest_invoke<int>(a.finalize, 0));
    t.add("close", guest_invoke<int>(a.close, db));
    free(out);
    return t;
}

NATIVE_TEST("lib_sqlite/bridge") {
    Trace g = session(guest_api()), n = session(native_api());
    t.expect_eq(g.v.size(), n.v.size(), "trace length");
    for (size_t k = 0; k < g.v.size() && k < n.v.size(); k++)
        if (g.v[k] != n.v[k]) t.fail("step %zu: guest %s / native %s", k, g.v[k].c_str(), n.v[k].c_str());
}

// The live check: the natives with the shadow on; a session matches (checks, no mismatches); a shadow
// that diverged (a row inserted behind the check's back, on the host database only) is caught.
NATIVE_TEST("lib_sqlite/live-check") {
    u64 c0, b0, s0, c1, b1, s1, c2, b2, s2;
    live_counts(&c0, &b0, &s0);
    live_switch(true);
    session(native_api());
    live_counts(&c1, &b1, &s1);
    t.expect_eq(b1 - b0, (u64)0, "no mismatches over the session");
    if (c1 - c0 < 60) t.fail("only %llu checks", (unsigned long long)(c1 - c0));
    Api a = native_api();
    u64* out = (u64*)calloc(2, 8);
    guest_invoke<int>(a.open, ":memory:", out);
    u64 db = out[0];
    guest_invoke<int>(a.exec, db, "create table t(a); insert into t values(1)", 0, 0, 0);
    sqlite3_exec((sqlite3*)(uintptr_t)db, "insert into t values(2)", nullptr, nullptr, nullptr);  // (the host only)
    guest_invoke<int>(a.prepare_v2, db, "select a from t", -1, out + 1, 0);
    while (guest_invoke<int>(a.step, out[1]) == SQLITE_ROW) guest_invoke<u64>(a.column_value, out[1], 0);
    guest_invoke<int>(a.finalize, out[1]);
    guest_invoke<int>(a.close, db);
    free(out);
    live_switch(false);
    live_counts(&c2, &b2, &s2);
    if (b2 - b1 < 1) t.fail("the diverged shadow wasn't caught");
}

}  // namespace
}  // namespace soa::native::lib_sqlite
