// Differential tests of the table natives (master_simple.cpp) against the guest's instantiations: two
// twin tables of the same element class, one driven through the guest's CMasterParameterBaseSqlite_
// Simple<E> functions, one through TSimple<E>, over a fake connector (its vtable thunks: a table of
// generated rows served as MessagePack, every call logged) and a copy of the table's vtable whose
// InstantiateSqlConnector / pParseName are the test's. After every step the results, the call logs,
// the three caches (sizes, bucket counts, the keys in list order, each element by its bytes, its
// strings by representation; pointers into elements by whether they are set) must agree.
//   master/simple-lookups: Initialize, pParameterFromHash (hits, misses, rows the table doesn't have,
//     the cache's eviction), ParameterByQuery (both), MakeCacheKey, InsertCustomizeCache's eviction,
//     SetStoreAllCacheSize, ClearCache, the destructor;
//   master/simple-deserialize: Deserialize / DeserializeParameter (a document with the table's array,
//     twice: the second run updates), ReleaseParameter (a row, the table's name), DeserializeMsgPack
//     with a single element and with a map root.
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "native/common/guest_std.h"
#include "native/common/native_method.h"
#include "native/common/test.h"
#include "native/data_formats/data_formats_layout.h"
#include "native/hash/hash_layout.h"
#include "native/libcxx/libcxx_string.h"
#include "native/master/master_compare.h"
#include "native/master/master_simple.h"
#include "native/params/params_check.h"

namespace soa::native::master {

namespace {

// ---- MessagePack rows ----

struct Writer {
    std::vector<u8> b;
    void u8_(u8 v) { b.push_back(v); }
    void be(u64 v, int n) {
        for (int i = n - 1; i >= 0; i--) b.push_back((u8)(v >> (8 * i)));
    }
    void array(u32 n) { u8_(0xdd), be(n, 4); }
    void map(u32 n) { u8_(0xdf), be(n, 4); }
    void str(const std::string& s) { u8_(0xdb), be(s.size(), 4), b.insert(b.end(), s.begin(), s.end()); }
    void uint(u64 v) { u8_(0xcf), be(v, 8); }
    void sint(s64 v) { u8_(0xd3), be((u64)v, 8); }
    void f32(float f) {
        u32 x;
        std::memcpy(&x, &f, 4);
        u8_(0xca), be(x, 4);
    }
    void boolean(bool v) { u8_(v ? 0xc3 : 0xc2); }
};

struct Row {
    u32 id;
    std::vector<u64> values;        // per property (the value's bits)
    std::vector<std::string> strs;  // per property
};

// The fake database of one element class.
struct FakeDb {
    const ElementInfo* el = nullptr;
    bool string_ids = false;  // the "id" column a string (its key: CHash32 of it)
    std::vector<Row> rows;
    std::vector<std::string> log;
    std::string table_name = "test_table";

    std::string id_text(u32 id) const { return "ja_row" + std::to_string(id); }
    u32 key_of(const Row& r) const { return string_ids ? hash::CHash32::OfCString(id_text(r.id).c_str()) : r.id; }

    void write_row(Writer& w, const Row& r) const {
        u32 n = 0;
        for (const ElementProp& d : el->props) n += d.key != nullptr;
        bool has_id = false;
        for (const ElementProp& d : el->props) has_id |= d.key && !std::strcmp(d.key, "id");
        w.map(n + !has_id);
        if (!has_id) {
            w.str("id");
            if (string_ids) w.str(id_text(r.id));
            else w.uint(r.id);
        }
        for (size_t i = 0; i < el->props.size(); i++) {
            const ElementProp& d = el->props[i];
            if (!d.key) continue;
            w.str(d.key);
            if (!std::strcmp(d.key, "id")) {
                if (string_ids) w.str(id_text(r.id));
                else w.uint(r.id);
                continue;
            }
            switch (d.kind) {
                case PropKind::kString: w.str(r.strs[i]); break;
                case PropKind::kFloat: w.f32((float)(r.values[i] % 1000) / 8.0f); break;
                case PropKind::kBool: w.boolean(r.values[i] & 1); break;
                case PropKind::kS32: w.sint((s32)r.values[i]); break;
                case PropKind::kU8: w.uint(r.values[i] & 0xff); break;
                default: w.uint((u32)r.values[i]); break;
            }
        }
    }
    std::vector<u8> select(const std::vector<const Row*>& sel, bool as_map = false) const {
        Writer w;
        if (as_map && sel.size() == 1) {
            write_row(w, *sel[0]);
            return w.b;
        }
        w.array((u32)sel.size());
        for (const Row* r : sel) write_row(w, *r);
        return w.b;
    }
};
FakeDb* g_db = nullptr;

void serve(Cpu& c, u64 arr, u64 size, const std::vector<u8>& bytes) {
    auto* a = reinterpret_cast<TSharedArray*>(arr);
    if (bytes.empty()) {
        *reinterpret_cast<s64*>(size) = 0;
        return;
    }
    a->m_data = (s8*)guest_call(guest::sym("_Znam"), {(u64)bytes.size()});
    std::memcpy(a->m_data, bytes.data(), bytes.size());
    a->m_counter = nullptr;
    *reinterpret_cast<s64*>(size) = (s64)bytes.size();
}
void conn_open(Cpu& c) { g_db->log.push_back(std::string("Open ") + (const char*)c.x(1)); }
void conn_close(Cpu& c) { g_db->log.push_back("Close"); }
void conn_dtor_delete(Cpu& c) { g_db->log.push_back("delete connector"); }
void conn_by_id(Cpu& c) {
    u32 q = (u32)c.x(1), id = (u32)c.x(2);
    g_db->log.push_back("QueryToMsgPack " + std::to_string(q) + " " + std::to_string(id));
    std::vector<const Row*> sel;
    for (const Row& r : g_db->rows)
        if (q == 0 || g_db->key_of(r) == id) sel.push_back(&r);
    serve(c, c.x(3), c.x(4), sel.empty() ? std::vector<u8>{} : g_db->select(sel));
}
void conn_by_sql(Cpu& c) {
    std::string sql = (const char*)c.x(1);
    g_db->log.push_back("QueryToMsgPack " + sql + " n=" + std::to_string((u32)c.x(5)));
    u32 h = hash::CHash32::OfCString(sql.c_str());
    std::vector<const Row*> sel;
    for (const Row& r : g_db->rows)
        if ((r.id + h) % 3 == 0) sel.push_back(&r);
    serve(c, c.x(2), c.x(3), sel.empty() ? std::vector<u8>{} : g_db->select(sel, sql.find("map") != std::string::npos));
}

// The fake connector: an object whose vtable is the test's thunks.
struct FakeConnector {
    std::vector<u64> vt;
    u64 obj[4] = {};
    FakeConnector() : vt(8) {
        static const u64 t_open = make_thunk("test:conn-open", conn_open), t_close = make_thunk("test:conn-close", conn_close),
                         t_del = make_thunk("test:conn-delete", conn_dtor_delete), t_id = make_thunk("test:conn-by-id", conn_by_id),
                         t_sql = make_thunk("test:conn-by-sql", conn_by_sql);
        vt[kConnDtor] = t_del, vt[kConnDtorDelete] = t_del, vt[kConnOpen] = t_open, vt[kConnClose] = t_close;
        vt[kConnQueryToResultObject] = t_del, vt[kConnQueryToMsgPackId] = t_id, vt[kConnQueryToMsgPack] = t_sql;
        vt[kConnQueryToResultObjectSql] = t_del;
        obj[0] = (u64)vt.data();
    }
};
FakeConnector* g_conn = nullptr;
void instantiate(Cpu& c) {
    g_db->log.push_back("InstantiateSqlConnector");
    c.set_x(0, (u64)g_conn->obj);
}
void parse_name(Cpu& c) { c.set_x(0, (u64)g_db->table_name.c_str()); }

// A table object (0xa0 bytes) with a copy of _Simple<E>'s vtables, InstantiateSqlConnector and pParseName
// the test's.
struct Table {
    std::vector<u64> vt0, vt1;
    alignas(16) u8 bytes[0x100] = {};
    CMasterParameterSimple* t() { return reinterpret_cast<CMasterParameterSimple*>(bytes); }
    explicit Table(const TableInfo& T, u64 deserialize_parameter = 0) {
        const u64* real = reinterpret_cast<const u64*>(T.simple_vtable);
        vt0.assign(real + 2, real + 2 + 10);
        vt1.assign(real + 14, real + 14 + 7);
        static const u64 t_inst = make_thunk("test:instantiate", instantiate), t_name = make_thunk("test:parse-name", parse_name);
        vt0[kMasterInstantiateSqlConnector] = t_inst;
        vt1[params::CParameterBase::kSlotParseName] = t_name;
        if (deserialize_parameter) vt0[kMasterDeserializeParameter] = deserialize_parameter;
        t()->base.vtable = vt0.data();
        t()->parameter.vtable = vt1.data();
        for (U32Map* m : {&t()->m_all, &t()->m_cache, &t()->m_queryCache}) m->max_load_factor = 1.0f;
        t()->m_cacheLimit = 3;
        t()->m_queryLimit = 2;
    }
};

// ---- comparisons ----

struct Twin {
    TestContext& t;
    const char* cls;
    const TableInfo& T;
    FakeDb db;
    FakeConnector conn;
    Table ga, na;  // the guest's table, the native's
    std::vector<std::string> glog, nlog;
    Twin(TestContext& t_, const char* c, const TableInfo& T_, u64 native_deserialize_parameter)
        : t(t_), cls(c), T(T_), ga(T_), na(T_, native_deserialize_parameter) {
        db.el = T.el;
        g_db = &db;
        g_conn = &conn;
    }
    // Runs a step on both (the guest's first), keeping their logs apart.
    template <typename G, typename N>
    void both(const char* what, G guest, N native) {
        db.log.clear();
        guest();
        glog = db.log;
        db.log.clear();
        native();
        nlog = db.log;
        if (glog != nlog) t.fail("%s %s: calls differ (%zu / %zu)", cls, what, glog.size(), nlog.size());
        check(what);
    }
    void check(const char* what) {
        auto* a = ga.t();
        auto* b = na.t();
        if ((a->base.m_pConnector != nullptr) != (b->base.m_pConnector != nullptr) || a->m_cacheLimit != b->m_cacheLimit ||
            a->m_queryLimit != b->m_queryLimit)
            t.fail("%s %s: fields", cls, what);
        std::string why;
        if (!(why = cmp_map(*T.el, a->m_all, b->m_all, true)).empty()) t.fail("%s %s: m_all %s", cls, what, why.c_str());
        if (!(why = cmp_map(*T.el, a->m_cache, b->m_cache, true)).empty()) t.fail("%s %s: m_cache %s", cls, what, why.c_str());
        if (!(why = cmp_map(*T.el, a->m_queryCache, b->m_queryCache, true)).empty())
            t.fail("%s %s: m_queryCache %s", cls, what, why.c_str());
    }
    void check_result(const char* what, const SharedPtr& a, const SharedPtr& b) {
        std::string why = cmp_element(*T.el, a.ptr, b.ptr);
        if (!why.empty() || (a.ctrl == nullptr) != (b.ctrl == nullptr)) t.fail("%s %s: result %s", cls, what, why.c_str());
    }
};

void release(SharedPtr& p) {
    if (p.ctrl) p.ctrl->__release_shared();
    p = {};
}

const char* sym_of(std::span<const ElementMethod> ms, const char* role) {
    for (const ElementMethod& m : ms)
        if (m.role && !std::strcmp(m.role, role)) return m.symbol;
    return nullptr;
}

void make_rows(TestContext& t, FakeDb& db, int n) {
    for (int i = 0; i < n; i++) {
        Row r;
        r.id = 100 + 7 * i;
        for (size_t k = 0; k < db.el->props.size(); k++) {
            r.values.push_back(t.rand_u64());
            static const int kLens[] = {0, 3, 22, 23, 40};
            int len = kLens[t.rand_int(0, 4)];
            std::string s;
            for (int j = 0; j < len; j++) s += (char)('a' + t.rand_int(0, 25));
            r.strs.push_back(s);
        }
        db.rows.push_back(r);
    }
}

// The native DeserializeParameter as a guest-callable thunk (the native twin's vtable slot 9).
template <class E>
u64 native_deserialize_parameter() {
    static const u64 a = make_thunk("test:TSimple::DeserializeParameter", wrap_method<&TSimple<E>::DeserializeParameter>());
    return a;
}

template <class E>
void lookups(TestContext& t, bool string_ids) {
    const TableInfo& T = table_info<E>();
    auto ms = ElementTraits<E>::table;
    if (!T.simple_vtable) return;
    Twin w(t, ElementTraits<E>::name, T, native_deserialize_parameter<E>());
    w.db.string_ids = string_ids;
    make_rows(t, w.db, 9);
    auto* A = w.ga.t();
    auto* B = w.na.t();
    auto G = [&](const char* role, std::initializer_list<u64> args) { return guest_call(t.sym(sym_of(ms, role)), args); };
    auto* nb = reinterpret_cast<TSimple<E>*>(B);
    if (!sym_of(ms, "Initialize") || !sym_of(ms, "Dtor") || !T.simple_vtable) return;
    w.both("Initialize", [&] { G("Initialize", {(u64)A}); }, [&] { nb->Initialize(); });
    // pParameterFromHash: rows in turn (past the cache limit), again (hits), a row the table hasn't
    std::vector<u32> ids;
    for (const Row& r : w.db.rows) ids.push_back(w.db.key_of(r));
    ids.push_back(w.db.key_of(w.db.rows[1]));
    ids.push_back(w.db.key_of(w.db.rows[8]));
    ids.push_back(12345);
    for (u32 id : ids) {
        if (!sym_of(ms, "pParameterFromHash")) break;
        SharedPtr a{}, b{};
        u64 regs[2] = {(u64)A, id};
        w.both("pParameterFromHash", [&] { guest_call_raw(t.sym(sym_of(ms, "pParameterFromHash")), regs, 2, nullptr, 0, (u64)&a); },
               [&] { nb->pParameterFromHash(&b, id); });
        w.check_result("pParameterFromHash", a, b);
        release(a), release(b);
    }
    if (const char* s = sym_of(ms, "ParameterByQuery")) {
        for (const char* sql : {"SELECT 1", "SELECT 2", "SELECT 1", "SELECT map", "SELECT 3", "SELECT 4"}) {
            SharedPtr a{}, b{};
            u64 regs[4] = {(u64)A, (u64)sql, 0, 0};
            w.both("ParameterByQuery", [&] { guest_call_raw(t.sym(s), regs, 4, nullptr, 0, (u64)&a); },
                   [&] { nb->ParameterByQuery(&b, sql, nullptr, 0); });
            w.check_result("ParameterByQuery", a, b);
            release(a), release(b);
        }
    }
    if (const char* s = sym_of(ms, "ParameterByQueryMap")) {
        for (const char* sql : {"SELECT 5", "SELECT map", "SELECT 6"}) {
            U32Map ma{}, mb{};
            ma.max_load_factor = mb.max_load_factor = 1.0f;
            w.both("ParameterByQueryMap", [&] { guest_call(t.sym(s), {(u64)A, (u64)sql, (u64)&ma, 0, 0}); },
                   [&] { nb->ParameterByQueryMap(sql, &mb, nullptr, 0); });
            std::string why = cmp_map(*T.el, ma, mb, false);
            if (!why.empty()) t.fail("%s ParameterByQueryMap: %s", w.cls, why.c_str());
            ma.destroy([&](U32Node* n) { SimpleCode::destroy_node_element(*T.el, n); });
            mb.destroy([&](U32Node* n) { SimpleCode::destroy_node_element(*T.el, n); });
        }
    }
    if (const char* s = sym_of(ms, "MakeCacheKey")) {
        alignas(8) u8 qp[3][0x28] = {};
        const char* texts[3] = {"12", "abc", ""};
        for (int i = 0; i < 3; i++) *reinterpret_cast<const char**>(qp[i] + 0x10) = texts[i];
        for (u32 n = 0; n <= 3; n++) {
            u32 a = (u32)guest_call(t.sym(s), {(u64)A, (u64)"SELECT x", (u64)qp, n});
            u32 b = nb->MakeCacheKey("SELECT x", qp, n);
            if (a != b) t.fail("%s MakeCacheKey(%u)", w.cls, n);
        }
    }
    if (const char* s = sym_of(ms, "SetStoreAllCacheSize"))
        w.both("SetStoreAllCacheSize", [&] { guest_call(t.sym(s), {(u64)A}); }, [&] { nb->SetStoreAllCacheSize(); });
    if (const char* s = sym_of(ms, "ClearCache")) w.both("ClearCache", [&] { guest_call(t.sym(s), {(u64)A}); }, [&] { nb->ClearCache(); });
    w.both("Dtor", [&] { G("Dtor", {(u64)A}); }, [&] { nb->Dtor(); });
}

// A document {name: [rows]} in a guest ASON (keeping C strings); `doc` stays alive while it's read.
struct Doc {
    alignas(16) u8 ason[sizeof(data_formats::ASON)];
    std::vector<u8> bytes;
    Doc(const FakeDb& db, const std::vector<const Row*>& sel, const std::string& name) {
        Writer w;
        w.map(1);
        w.str(name);
        Writer rows;
        auto b = db.select(sel);
        w.b.insert(w.b.end(), b.begin(), b.end());
        bytes = w.b;
        guest_call(guest::sym("_ZN4Aska4ASONC1Ev"), {(u64)ason});
        guest_call(guest::sym("_ZN4Aska4ASON4InitEjb"), {(u64)ason, 0x10000, 1});
        guest_call(guest::sym("_ZN4Aska4ASON11DeserializeEPKvm"), {(u64)ason, (u64)bytes.data(), bytes.size()});
    }
    ~Doc() { guest_call(guest::sym("_ZN4Aska4ASOND1Ev"), {(u64)ason}); }
    const data_formats::AMap* root() const { return &reinterpret_cast<const data_formats::ASON*>(ason)->m_root.m_body.map; }
};

template <class E>
void deserialize(TestContext& t, bool string_ids) {
    const TableInfo& T = table_info<E>();
    auto ms = ElementTraits<E>::table;
    if (!T.simple_vtable) return;
    Twin w(t, ElementTraits<E>::name, T, native_deserialize_parameter<E>());
    w.db.string_ids = string_ids;
    make_rows(t, w.db, 6);
    auto* A = w.ga.t();
    auto* B = w.na.t();
    auto* nb = reinterpret_cast<TSimple<E>*>(B);
    const char* deser = sym_of(ms, "Deserialize");
    if (!deser || !sym_of(ms, "Dtor") || !T.simple_vtable) return;
    std::vector<const Row*> all;
    for (const Row& r : w.db.rows) all.push_back(&r);
    for (int round = 0; round < 2; round++) {
        if (round) {
            for (Row& r : w.db.rows) r.values[0] ^= 0x55, r.strs[r.strs.size() - 1] += "x";
            all.pop_back();
        }
        Doc doc(w.db, all, w.db.table_name);
        bool a = false, b = false;
        w.both("Deserialize", [&] { a = guest_call(t.sym(deser), {(u64)A, (u64)doc.root()}) & 1; },
               [&] { b = nb->Deserialize(doc.root()); });
        if (a != b) t.fail("%s Deserialize: result", w.cls);
        Doc other(w.db, all, "another_table");
        w.both("Deserialize (no such part)", [&] { a = guest_call(t.sym(deser), {(u64)A, (u64)other.root()}) & 1; },
               [&] { b = nb->Deserialize(other.root()); });
        if (a != b) t.fail("%s Deserialize (no such part): result", w.cls);
    }
    if (const char* s = sym_of(ms, "ReleaseParameter")) {
        std::string one = string_ids ? w.db.id_text(w.db.rows[2].id) : std::to_string(w.db.rows[2].id);
        for (const std::string& name : {one, std::string("nothing"), w.db.table_name}) {
            bool a = false, b = false;
            w.both("ReleaseParameter", [&] { a = guest_call(t.sym(s), {(u64)A, (u64)name.c_str()}) & 1; },
                   [&] { b = nb->ReleaseParameter(name.c_str()); });
            if (a != b) t.fail("%s ReleaseParameter: result", w.cls);
        }
    }
    // DeserializeMsgPack with a single element and with a one-row map root
    if (const char* s = sym_of(ms, "DeserializeMsgPack")) {
        for (bool as_map : {false, true}) {
            auto bytes = w.db.select({&w.db.rows[3]}, as_map);
            TSharedArray arr{(s8*)bytes.data(), nullptr};
            s64 size = (s64)bytes.size();
            std::vector<u64> ea((T.el->size + 7) / 8), eb((T.el->size + 7) / 8);
            ElementCode::Ctor(*T.el, (u8*)ea.data());
            ElementCode::Ctor(*T.el, (u8*)eb.data());
            guest_call(t.sym(s), {(u64)A, (u64)&arr, (u64)&size, (u64)ea.data(), 0});
            nb->DeserializeMsgPack(&arr, &size, (u8*)eb.data(), nullptr);
            std::string why = cmp_element(*T.el, (u8*)ea.data(), (u8*)eb.data());
            if (!why.empty()) t.fail("%s DeserializeMsgPack(single, %s): %s", w.cls, as_map ? "map" : "array", why.c_str());
            ElementCode::Dtor(*T.el, (u8*)ea.data());
            ElementCode::Dtor(*T.el, (u8*)eb.data());
            U32Map ma{}, mb{};
            ma.max_load_factor = mb.max_load_factor = 1.0f;
            guest_call(t.sym(s), {(u64)A, (u64)&arr, (u64)&size, 0, (u64)&ma});
            nb->DeserializeMsgPack(&arr, &size, nullptr, &mb);
            why = cmp_map(*T.el, ma, mb, false);
            if (!why.empty()) t.fail("%s DeserializeMsgPack(map, %s): %s", w.cls, as_map ? "map" : "array", why.c_str());
            ma.destroy([&](U32Node* n) { SimpleCode::destroy_node_element(*T.el, n); });
            mb.destroy([&](U32Node* n) { SimpleCode::destroy_node_element(*T.el, n); });
        }
    }
    w.both("Dtor", [&] { guest_call(t.sym(sym_of(ms, "Dtor")), {(u64)A}); }, [&] { nb->Dtor(); });
}

}  // namespace

// Every table, numeric ids (and StringDB's string ids as its own case).
NATIVE_TEST("master/simple-lookups") {
#define MASTER_T(C, ZTV) \
    if (ElementTraits<C>::table[0].role) lookups<C>(t, false);
    MASTER_ELEMENTS(MASTER_T)
#undef MASTER_T
    lookups<StringDBEelement>(t, true);
}

NATIVE_TEST("master/simple-deserialize") {
#define MASTER_T(C, ZTV) \
    if (ElementTraits<C>::table[0].role) deserialize<C>(t, false);
    MASTER_ELEMENTS(MASTER_T)
#undef MASTER_T
    deserialize<StringDBEelement>(t, true);
}

}  // namespace soa::native::master

namespace soa::native::master {
namespace {

// StringDB::GetNativeString / Get on twin tables of texts (string ids "ja_rowN"; texts with "\n"
// escapes, long and short, encrypted as the element keeps them: the fake rows go through
// Deserialize, which encrypts).
void stringdb(TestContext& t) {
    const TableInfo& T = table_info<StringDBEelement>();
    Twin w(t, "StringDB", T, native_deserialize_parameter<StringDBEelement>());
    w.db.string_ids = true;
    make_rows(t, w.db, 6);
    int text = -1;
    for (size_t i = 0; i < T.el->props.size(); i++)
        if (T.el->props[i].key && !std::strcmp(T.el->props[i].key, "text_value")) text = (int)i;
    if (text < 0) return t.fail("StringDBEelement has no text_value");
    const char* texts[] = {"plain", "line\\nbreak", "\\n", "a long text with\\nseveral\\nescapes in it", "", "x\\"};
    for (int i = 0; i < 6; i++) w.db.rows[i].strs[text] = texts[i];
    auto* A = w.ga.t();
    auto* B = w.na.t();
    guest_call(t.sym("_ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementE10InitializeEv"), {(u64)A});
    reinterpret_cast<TSimple<StringDBEelement>*>(B)->Initialize();
    for (const char* sym : {"_ZN8StringDB15GetNativeStringEPKcPb", "_ZN8StringDB3GetEPKcPb"}) {
        bool get = std::strstr(sym, "3Get") != nullptr;
        for (int i = 0; i < 8; i++) {
            std::string id = i < 6 ? "row" + std::to_string(w.db.rows[i].id) : (i == 6 ? "no_such_row" : "a_missing_id_longer_than_22");
            params::String a{}, b{};
            bool fa = false, fb = false;
            u64 regs[3] = {(u64)A, (u64)id.c_str(), (u64)&fa};
            guest_call_raw(t.sym(sym), regs, 3, nullptr, 0, (u64)&a);
            auto* db = reinterpret_cast<StringDB*>(B);
            if (get) db->Get(&b, id.c_str(), &fb);
            else db->GetNativeString(&b, id.c_str(), &fb);
            std::string why = fa != fb ? "found" : params::diff_strings(a, b);
            if (why.empty() && a.size() && std::memcmp(a.data(), b.data(), a.size())) why = "bytes";
            if (!why.empty()) t.fail("%s(%s): %s", get ? "Get" : "GetNativeString", id.c_str(), why.c_str());
            libcxx::string_destroy(&a);
            libcxx::string_destroy(&b);
        }
    }
    w.check("StringDB");
    guest_call(t.sym("_ZN33CMasterParameterBaseSqlite_SimpleI16StringDBEelementED2Ev"), {(u64)A});
    reinterpret_cast<TSimple<StringDBEelement>*>(B)->Dtor();
}

}  // namespace

NATIVE_TEST("master/stringdb") { stringdb(t); }

}  // namespace soa::native::master
