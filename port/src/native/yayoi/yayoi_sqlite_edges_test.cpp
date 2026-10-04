// Differential tests of the SQLite driver family on a private database (yayoi_sqlite_test_util.h: the
// guest's functions vs thunks of the natives, each side on its own objects, logs compared):
//   yayoi/sqlite-driver-edges: the statuses and quirks: a fresh entity, the cache buffer, Open /
//     DoOpen through an IDriverSetting, the transaction flags, parameter counts, null params, a
//     failing prepare (closes the database), Execute without an entity (one step), every getter by
//     index and by name on INTEGER / REAL / TEXT / BLOB / NULL values (32-bit truncation, text
//     truncation, an exact fit), a duplicate column name, Serialize on texts > 256 bytes and > 64 KB,
//     blobs, NULLs, > 64 columns and an empty result.
//   yayoi/column-map: THashMap<char const*, int>'s members on maps each side built: Emplace_ into a
//     full table, Insert_, deleted buckets, Rehash_ (also to 0 buckets and with odd load factors), the
//     range Insert and the destructors.
#include "native/yayoi/yayoi_sqlite_test_util.h"

namespace soa::native::yayoi {
namespace {

using namespace test;

// An IDriverSetting<SQLiteDriver>: vtable slot 0 (this, mode) -> the DBAddress (":memory:").
DBAddress g_setting_addr{":memory:"};
u32 g_setting_mode = 0xffffffff;
void setting_address(Cpu& c) {
    g_setting_mode = (u32)c.x(1);
    c.set_x(0, (u64)&g_setting_addr);
}
struct Setting {
    const u64* vtable;
};
Setting* setting() {
    static u64 vt[4] = {make_thunk("yayoi_test:IDriverSetting::address", &setting_address), 0, 0, 0};
    static Setting s{vt};
    return &s;
}

s64 exec(Side& s, u64 d, const char* sql, const std::vector<std::string>& params = {}, u64 n = ~0ull) {
    std::vector<QueryParam> p = params_of(params);
    s64 st = s.status(DRV "7ExecuteEPKcPKNS0_10QueryParamEm", {d, (u64)sql, params.empty() ? 0 : (u64)p.data(), n == ~0ull ? p.size() : n});
    s.add(fmt("exec %" PRId64 " %.60s ", st, sql) + driver_state(d, p.data()));
    return st;
}

// Every getter on column c (by index; `name` too when given).
std::string all_getters(Side& s, u64 e, int c, const char* name) {
    std::string r;
    auto by = [&](const char* isym, const char* nsym, auto* out, auto show) {
        using T = std::remove_pointer_t<decltype(out)>;
        *out = (T)0x5a;
        s64 st = s.status(isym, {e, (u64)(u32)c, (u64)out, 0});
        r += fmt("%" PRId64 "/", st) + show(*out) + " ";
        if (name) {
            *out = (T)0x5a;
            st = s.status(nsym, {e, (u64)name, (u64)out, 0});
            r += fmt("n%" PRId64 "/", st) + show(*out) + " ";
        }
    };
    s8 i8;
    s16 i16;
    s32 i32;
    s64 i64;
    float f;
    double d;
    by(ENT "10GetTinyIntEiPam", ENT "10GetTinyIntEPKcPam", &i8, [](s8 v) { return fmt("%d", v); });
    by(ENT "8GetShortEiPsm", ENT "8GetShortEPKcPsm", &i16, [](s16 v) { return fmt("%d", v); });
    by(ENT "10GetIntegerEiPim", ENT "10GetIntegerEPKcPim", &i32, [](s32 v) { return fmt("%d", v); });
    by(ENT "7GetLongEiPlm", ENT "7GetLongEPKcPlm", &i64, [](s64 v) { return fmt("%" PRId64, v); });
    by(ENT "8GetFloatEiPfm", ENT "8GetFloatEPKcPfm", &f, [](float v) { return dbl(v); });
    by(ENT "9GetDoubleEiPdm", ENT "9GetDoubleEPKcPdm", &d, [](double v) { return dbl(v); });
    r += fmt("type %d ", (s32)s.call(ENT "7GetTypeEim", {e, (u64)(u32)c, 0}));
    if (name) r += fmt("ntype %d ", (s32)s.call(ENT "7GetTypeEPKcm", {e, (u64)name, 0}));
    r += fmt("flen %d ", (s32)s.call(ENT "14GetFieldLengthEii", {e, (u64)(u32)c, 0}));
    u64 len = 0x5a;
    s64 st = s.status(ENT "15GetStringLengthEiPmm", {e, (u64)(u32)c, (u64)&len, 0});
    r += fmt("slen %" PRId64 "/%" PRIu64 " ", st, len);
    // GetString into buffers of several sizes (truncation; the exact fit returns the size)
    for (u64 cap : {(u64)0x10000, (u64)4, (u64)len + 1, (u64)len, (u64)1}) {
        std::vector<char> buf(std::max<u64>(cap, 1) + 8, 0x5a);
        u64 size = cap;
        st = s.status(ENT "9GetStringEiPcPmm", {e, (u64)(u32)c, (u64)buf.data(), (u64)&size, 0});
        r += fmt("str[%" PRIu64 "] %" PRId64 "/%" PRId64 "/", cap, st, (s64)size) + std::string(buf.data(), std::min<size_t>(buf.size(), 40)) + " ";
        if (name && cap == 0x10000) {
            size = cap;
            st = s.status(ENT "9GetStringEPKcPcPmm", {e, (u64)name, (u64)buf.data(), (u64)&size, 0});
            r += fmt("nstr %" PRId64 "/%" PRId64 " ", st, (s64)size);
        }
    }
    std::vector<char> data(0x20000, 0x5a);
    u64 size = data.size();
    st = s.status(ENT "7GetDataEiPcPmm", {e, (u64)(u32)c, (u64)data.data(), (u64)&size, 0});
    r += fmt("data %" PRId64 "/%" PRId64 "/", st, (s64)size);
    for (u64 k = 0; st == 0 && k < size && k < 16; k++) r += fmt("%02x", (u8)data[k]);
    if (name) {
        size = data.size();
        st = s.status(ENT "7GetDataEPKcPcPmm", {e, (u64)name, (u64)data.data(), (u64)&size, 0});
        r += fmt(" ndata %" PRId64 "/%" PRId64, st, (s64)size);
    }
    char tb[32];
    u64 tsize = sizeof tb;
    r += fmt(" time %" PRId64 " %" PRId64, s.status(ENT "7GetTimeEiPcPmm", {e, (u64)(u32)c, (u64)tb, (u64)&tsize, 0}),
             s.status(ENT "7GetTimeEiPcPmm", {e, (u64)(u32)c, 0, (u64)&tsize, 0}));
    if (name)
        r += fmt(" ntime %" PRId64 " %" PRId64, s.status(ENT "7GetTimeEPKcPcPmm", {e, (u64)name, (u64)tb, (u64)&tsize, 0}),
                 s.status(ENT "7GetTimeEPKcPcPmm", {e, (u64)name, 0, (u64)&tsize, 0}));
    return r;
}

std::string find(Side& s, u64 d, u64 e, const char* sql, const std::vector<std::string>& params = {}) {
    std::vector<QueryParam> p = params_of(params);
    s64 st = s.status(DRV "4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE", {d, (u64)sql, params.empty() ? 0 : (u64)p.data(), p.size(), e});
    return fmt("find %" PRId64 " %.60s ", st, sql) + driver_state(d, p.data()) + " " + entity_state(e);
}

// Every row of `sql` through every getter, by index and (every column's name) by name.
void walk_all(Side& s, u64 d, const char* sql, const std::vector<const char*>& names) {
    u64 e = s.new_entity();
    s.add(find(s, d, e, sql));
    for (int r = 0;; r++) {
        s64 st = s.status(ENT "5FetchEv", {e});
        s.add(fmt("fetch %" PRId64, st));
        if (st != 0) break;
        for (int c = 0; c < ((const EntityObject*)e)->m_numColumns; c++)
            s.add(fmt("r%d c%d ", r, c) + all_getters(s, e, c, c < (int)names.size() ? names[c] : nullptr));
        s.add(entity_state(e));
    }
    s.add(fmt("fetch past %" PRId64, s.status(ENT "5FetchEv", {e})));
    s.delete_entity(e);
}

void serialize(Side& s, u64 d, const char* sql) {
    u64 e = s.new_entity();
    s.add(find(s, d, e, sql));
    std::vector<u8> bytes;
    s.add(serialize_text(s, e, &bytes));
    std::string h;
    for (size_t k = 0; k < bytes.size(); k++) h += fmt("%02x", bytes[k]);
    // (long texts: the digest of the bytes, the head and the tail)
    u64 sum = 1469598103934665603ull;
    for (u8 b : bytes) sum = (sum ^ b) * 1099511628211ull;
    s.add(fmt("msgpack %zu %016" PRIx64 " ", bytes.size(), sum) + h.substr(0, 400) + " .. " + (h.size() > 400 ? h.substr(h.size() - 200) : ""));
    s.add(serialize_text(s, e, nullptr));  // (again: the statement is reset and stepped from the start)
    s.delete_entity(e);
}

void edges(Side& s) {
    // a fresh entity: no statement
    u64 e = s.new_entity();
    s.add(entity_state(e));
    s.add(fmt("fetch %" PRId64, s.status(ENT "5FetchEv", {e})));
    s.add("fresh " + all_getters(s, e, 0, "x"));
    s32 v = 0;
    s.add(fmt("null outs %" PRId64 " %" PRId64 " %" PRId64, s.status(ENT "10GetIntegerEiPim", {e, 0, 0, 0}),
              s.status(ENT "9GetStringEiPcPmm", {e, 0, 0, 0, 0}), s.status(ENT "15GetStringLengthEiPmm", {e, 0, 0, 0})));
    s.add(fmt("name missing %" PRId64 " %d", s.status(ENT "10GetIntegerEPKcPim", {e, (u64)"x", (u64)&v, 0}), (s32)s.call(ENT "7GetTypeEPKcm", {e, (u64)"x", 0})));
    s.add(fmt("serialize-cache %" PRIu64, s.call(ENT "14SerializeCacheEPm", {e, 0})));
    {
        SharedBytes r = s.serialize(e, nullptr);
        s.add(fmt("serialize(null) %d %d", r.m_ptr != nullptr, r.m_counter != nullptr));
    }
    s.add(serialize_text(s, e, nullptr));
    // the cache buffer
    u64 size = 0;
    s.add(fmt("cache %" PRId64, s.status(ENT "17CreateCacheBufferEm", {e, 16})) + " " + entity_state(e));
    u64 p = s.call(ENT "14GetCacheBufferEPm", {e, (u64)&size});
    s.add(fmt("get %d %" PRIu64, p != 0, size));
    s.add(fmt("cache %" PRId64 " %" PRId64, s.status(ENT "17CreateCacheBufferEm", {e, 8}), s.status(ENT "17CreateCacheBufferEm", {e, 0x1000})) + " " +
          entity_state(e));
    s.call(ENT "7ReleaseEv", {e});
    s.add("release " + entity_state(e));
    s.add(fmt("cache %" PRId64, s.status(ENT "17CreateCacheBufferEm", {e, 32})));
    s.call(ENT "10ClearCacheEv", {e});
    s.add("clear " + entity_state(e));
    s.delete_entity(e);

    // Open / DoOpen through the setting
    u64 d = s.new_driver();
    s.add(driver_state(d));
    s.add(fmt("open(null) %" PRId64 " open %" PRId64, s.status(DRV "4OpenEPNS0_14IDriverSettingIS1_EE", {d, 0}),
              s.status(DRV "4OpenEPNS0_14IDriverSettingIS1_EE", {d, (u64)setting()})));
    const char* kDoOpen = DRV "6DoOpenENS0_6Entity4ModeEPKcPKNS0_9DBAddressE";
    g_setting_mode = 0xffffffff;
    s.add(fmt("doopen %" PRId64 " mode %u ", s.status(kDoOpen, {d, 0, 0, 0}), g_setting_mode) + driver_state(d));
    g_setting_mode = 0xffffffff;
    s.add(fmt("doopen again %" PRId64 " mode %u ", s.status(kDoOpen, {d, 3, 0, 0}), g_setting_mode) + driver_state(d));
    // the transaction flags
    s.add(fmt("begin %" PRId64 " %" PRId64 " ", s.status(DRV "16BeginTransactionEv", {d}), s.status(DRV "16BeginTransactionEv", {d})) + driver_state(d));
    s.add(fmt("_begin %" PRId64 " ", s.status(DRV "17_BeginTransactionEv", {d})) + driver_state(d));
    s.add(fmt("_begin %" PRId64 " begin %" PRId64 " ", s.status(DRV "17_BeginTransactionEv", {d}), s.status(DRV "16BeginTransactionEv", {d})) + driver_state(d));
    s.add(fmt("commit %" PRId64 " %" PRId64 " rollback %" PRId64 " ", s.status(DRV "6CommitEv", {d}), s.status(DRV "6CommitEv", {d}),
              s.status(DRV "8RollbackEv", {d})) +
          driver_state(d));
    g_setting_mode = 0xffffffff;
    s.add(fmt("begin %" PRId64 " doopen(0) %" PRId64 " mode %u ", s.status(DRV "16BeginTransactionEv", {d}), s.status(kDoOpen, {d, 0, 0, 0}), g_setting_mode) +
          driver_state(d));
    static DBAddress other{":memory:"};
    static DBAddress bad_path{"/nonexistent-dir/sub/yayoi-test.sqlite3"};
    s.add(fmt("begin %" PRId64 " doopen(other) %" PRId64 " ", s.status(DRV "16BeginTransactionEv", {d}), s.status(kDoOpen, {d, 1, 0, (u64)&other})) +
          driver_state(d));
    s.add(fmt("rollback %" PRId64 " %" PRId64 " ", s.status(DRV "8RollbackEv", {d}), s.status(DRV "8RollbackEv", {d})) + driver_state(d));

    // the table
    exec(s, d, "CREATE TABLE t(i INTEGER, r REAL, s TEXT, b BLOB, n)");
    std::string long300(300, 'x'), long70k(70000, 'y');
    long300[150] = 'Z';
    const std::vector<std::vector<std::string>> rows = {
        {"1", "1.5", "abc", "b1", "n"},
        {"4294967297", "1e300", "", "", "7"},
        {"-5", "-0.0", long300, "x", "8.25"},
        {"9007199254740993", "3.14159", "\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e", "y", "text"},
        {"-2147483649", "2.5e-310", long70k, "z", "-1"},
        {"127", "0.1", "abc\x01" "def", "w", "300"},
        {"x12", "nan", "1e3", "v", ""},
    };
    for (auto& r : rows) exec(s, d, "INSERT INTO t VALUES(?, ?, ?, ?, ?)", r);
    exec(s, d, "INSERT INTO t VALUES(NULL, NULL, NULL, NULL, NULL)");
    exec(s, d, "INSERT INTO t VALUES(65536, 1, X'00ff10', X'', X'4142')");
    exec(s, d, "INSERT INTO t VALUES(?, ?, ?, ?, ?)", rows[0], 4);           // the parameter count
    exec(s, d, "INSERT INTO t VALUES(?, ?, ?, ?, ?)", {}, 5);                // no params: the binds are skipped
    exec(s, d, "SELECT * FROM t ORDER BY rowid");                            // no entity: one step
    exec(s, d, "UPDATE t SET n = 1 WHERE i = -999");
    walk_all(s, d, "SELECT i, r, s, b, n FROM t ORDER BY rowid", {"i", "r", "s", "b", "n"});
    walk_all(s, d, "SELECT i, s AS i, r FROM t ORDER BY rowid LIMIT 3", {"i", "missing", "r"});  // a duplicate name
    serialize(s, d, "SELECT i, r, s, b, n FROM t ORDER BY rowid");
    serialize(s, d, "SELECT * FROM t WHERE i = -999");
    serialize(s, d, "SELECT s FROM t WHERE length(s) > 1000");

    // > 64 columns (the guest takes its name table from the network allocator)
    std::string cols, vals;
    for (int k = 0; k < 70; k++) {
        cols += fmt("%sc%d", k ? ", " : "", k);
        vals += fmt("%s%d", k ? ", " : "", k * 3 - 50);
    }
    exec(s, d, ("CREATE TABLE w(" + cols + ")").c_str());
    exec(s, d, ("INSERT INTO w VALUES(" + vals + ")").c_str());
    exec(s, d, ("INSERT INTO w VALUES(" + vals + ")").c_str());
    serialize(s, d, "SELECT * FROM w");

    // a failing prepare closes the database; the next DoOpen opens it again
    s.add(fmt("begin %" PRId64 " _begin %" PRId64, s.status(DRV "16BeginTransactionEv", {d}), s.status(DRV "17_BeginTransactionEv", {d})));
    exec(s, d, "SELEC nope");
    exec(s, d, "SELECT 1");
    u64 e2 = s.new_entity();
    s.add(find(s, d, e2, "SELECT 1"));
    s.delete_entity(e2);
    s.add(fmt("doopen %" PRId64 " ", s.status(kDoOpen, {d, 1, 0, (u64)&other})) + driver_state(d));
    exec(s, d, "SELECT * FROM t");  // (a new database: no such table)
    s.add(fmt("doopen(bad path) %" PRId64 " ", s.status(kDoOpen, {d, 1, 0, (u64)&bad_path})) + driver_state(d));
    s.call(DRV "5CloseEv", {d});
    s.add("close " + driver_state(d));
    s.call(DRV "5CloseEv", {d});
    s.delete_driver(d);
}

}  // namespace

NATIVE_TEST("yayoi/sqlite-driver-edges") {
    Side g{"guest", false, {}}, n{"native", true, {}};
    edges(g);
    edges(n);
    same_logs(t, g, n, "edges");
    t.expect_eq(g.log.size() > 100, true, "the script ran");
}

}  // namespace soa::native::yayoi
