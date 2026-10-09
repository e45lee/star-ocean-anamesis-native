// The connectors' query methods (master_layout.h CSimpleSqliteConnector; port/decomp/master/connector_text.c
// and the disassembly): one body for the 165 connectors of gen/master_connectors.inc, which differ only in
// their CLocalEntity's statics, their BuildQuery<CLocalEntity> (yayoi's, called) and the query count; the
// connector's row is found by its vtable. The driver, the mutex, the EntityObject and its Serialize are
// yayoi's / sync's (called through their symbols: natives where they are).
// Live check (family `master`): QueryToMsgPack (both) runs the original after the native into a second
// array, and the two MessagePack documents must be byte for byte equal (QueryToResultObject runs inside
// them, through the vtable: checked that way).
#include <cstdio>
#include <cstring>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "core/loader.h"
#include "native/common/native.h"
#include "native/common/native_call.h"
#include "native/master/master_family.h"
#include "native/master/master_guest.h"
#include "native/master/master_layout.h"
#include "native/master/master_simple.h"
#include "native/sync/sync_layout.h"
#include "native/yayoi/yayoi_layout.h"

namespace soa::native::master {

namespace {

struct ConnectorSyms {
    const char *vtable, *msgpack_id, *msgpack_sql, *result_id, *result_sql, *queries, *keies, *build_query;
    u32 count;
};
#define MASTER_CONNECTOR_ROW(VT, MI, MS, RI, RS, Q, K, BQ, N) {VT, MI, MS, RI, RS, Q, K, BQ, N},
const ConnectorSyms kConnectors[] = {
#include "native/master/gen/master_connectors.inc"
    MASTER_CONNECTORS(MASTER_CONNECTOR_ROW)
};
#undef MASTER_CONNECTOR_ROW

constexpr size_t kCount = sizeof kConnectors / sizeof kConnectors[0];
Fn* g_fns[kCount][2];  // per connector: QueryToMsgPack(q, id)'s and (sql)'s live-check slots

struct ConnectorInfo {
    u64 queries = 0, keies = 0, build_query = 0;
    u32 count = 0;
    Fn* fn_id = nullptr;
    Fn* fn_sql = nullptr;
};

// vtable (+0x10) -> the connector's addresses (built once).
const ConnectorInfo* info_of(const CSimpleSqliteConnector* c) {
    static std::unordered_map<u64, ConnectorInfo>* table = [] {
        auto* t = new std::unordered_map<u64, ConnectorInfo>();
        for (size_t i = 0; i < kCount; i++) {
            const ConnectorSyms& s = kConnectors[i];
            ConnectorInfo I;
            I.fn_id = g_fns[i][0];
            I.fn_sql = g_fns[i][1];
            I.queries = g::sym(s.queries);
            I.keies = g::sym(s.keies);
            I.build_query = g::sym(s.build_query);
            I.count = s.count;
            (*t)[g::sym(s.vtable) + 0x10] = I;
        }
        return t;
    }();
    auto it = table->find((u64)c->vtable);
    return it == table->end() ? nullptr : &it->second;
}

u64 call(u64 fn, std::initializer_list<u64> args) { return guest_call(fn, args); }
u64 call_x8(u64 fn, std::initializer_list<u64> args, void* x8) {
    u64 a[8];
    size_t n = 0;
    for (u64 v : args) a[n++] = v;
    return guest_call_raw(fn, a, n, nullptr, 0, (u64)x8).x0;
}
u64 vslot(const void* obj, u32 slot) { return reinterpret_cast<const u64*>(*reinterpret_cast<const u64*>(obj))[slot]; }

// sync's and yayoi's natives, called as C++ when installed (native_call.h).
NativeCallee kLock{"sync", "_ZN9Framework6CMutex4LockEv"};
NativeCallee kUnlock{"sync", "_ZN9Framework6CMutex6UnlockEv"};
NativeCallee kEntityCtor{"yayoi", "_ZN4Aska5Yayoi12SQLiteDriver12EntityObjectC1Ev"};
NativeCallee kEntityDtor{"yayoi", "_ZN4Aska5Yayoi12SQLiteDriver12EntityObjectD1Ev"};
NativeCallee kSerialize{"yayoi", "_ZN4Aska5Yayoi12SQLiteDriver12EntityObject9SerializeEPl"};
NativeCallee kDoOpen{"yayoi", "_ZN4Aska5Yayoi12SQLiteDriver6DoOpenENS0_6Entity4ModeEPKcPKNS0_9DBAddressE"};
NativeCallee kFind{"yayoi", "_ZN4Aska5Yayoi12SQLiteDriver4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE"};
static_assert(sizeof(TSharedArray) == sizeof(yayoi::SharedBytes));

auto* as_mutex(u64 p) { return reinterpret_cast<sync::CMutex*>(p); }
auto* as_entity(void* p) { return static_cast<yayoi::EntityObject*>(p); }
auto* as_driver(u64 p) { return reinterpret_cast<yayoi::SQLiteDriver*>(p); }
s64 driver_find(u64 driver, u64 sql, void* params, u32 n, void* entity) {
    if (kFind.direct()) return as_driver(driver)->Find((const char*)sql, static_cast<const yayoi::QueryParam*>(params), n, as_entity(entity));
    s64 st = 0;
    call_x8(kFind.addr(), {driver, sql, (u64)params, n, (u64)entity}, &st);
    return st;
}

// CStaticTransaction's transaction object (instance + 0x40: a CSqliteTransaction).
u64 transaction() {
    static const u64 inst = g::sym("_ZN9Framework10TSingletonI18CStaticTransactionE11m_pInstanceE");
    return *reinterpret_cast<const u64*>(inst) + 0x40;
}
struct Locked {
    u64 mutex;
    Locked() {
        static const u64 rmutex = g::sym("_ZN18CSqliteTransaction6rMutexEv");
        mutex = call(rmutex, {transaction()});
        if (kLock.direct()) as_mutex(mutex)->Lock();
        else call(kLock.addr(), {mutex});
    }
    ~Locked() {
        static const u64 rmutex = g::sym("_ZN18CSqliteTransaction6rMutexEv");
        u64 m = call(rmutex, {transaction()});
        if (kUnlock.direct()) as_mutex(m)->Unlock();
        else call(kUnlock.addr(), {m});
    }
};

// The EntityObject (0x60) and the EntityCache after it, as QueryToMsgPack keeps them on its stack.
struct Entity {
    alignas(16) u8 bytes[0x80] = {};
    Entity() {
        static const u64 ec = g::sym("_ZN4Aska5Yayoi11EntityCacheC1Ev");
        if (kEntityCtor.direct()) as_entity(bytes)->Ctor();
        else call(kEntityCtor.addr(), {(u64)bytes});
        call(ec, {(u64)bytes + 0x60});
        bytes[0x78] = 0;
    }
    ~Entity() {
        static const u64 ec = g::sym("_ZN4Aska5Yayoi11EntityCacheD1Ev");
        call(ec, {(u64)bytes + 0x60});
        if (kEntityDtor.direct()) as_entity(bytes)->Dtor();
        else call(kEntityDtor.addr(), {(u64)bytes});
    }
};

// data = the serialized rows (TSharedArray's assignment, then the temporary released).
void serialize_into(Entity& e, TSharedArray* data, s64* size) {
    TSharedArray res{};
    if (kSerialize.direct()) {
        yayoi::SharedBytes r = as_entity(e.bytes)->Serialize(size);
        std::memcpy(&res, &r, sizeof res);
    } else {
        call_x8(kSerialize.addr(), {(u64)e.bytes, (u64)size}, &res);
    }
    if (res.m_data != data->m_data) {
        TSharedArray old = *data;
        bool last = !old.m_counter || __atomic_sub_fetch(old.m_counter, 1, __ATOMIC_ACQ_REL) == 0;
        if (last) {
            static const u64 del = g::sym("_ZdaPv"), del_counter = g::sym("_ZN4Aska18TSharedPointerCode13DeleteCounterEPi");
            if (old.m_data) call(del, {(u64)old.m_data});
            if (old.m_counter) call(del_counter, {(u64)old.m_counter});
        }
        *data = res;
        if (res.m_counter) __atomic_add_fetch(res.m_counter, 1, __ATOMIC_ACQ_REL);
    }
    SimpleCode::release_array(&res);
}

}  // namespace

void CSimpleSqliteConnector::QueryToResultObject(u32 query, void* params, u32 n, void* entity) {
    const ConnectorInfo* I = info_of(this);
    u64 t = transaction();
    u64 driver = call(vslot((void*)t, kTransactionPSubstance), {t});
    if ((s32)query > (s32)I->count - 1) return;
    u64 q = I->queries + (u64)(s64)(s32)query * 0x20;
    u64 addr = call(vslot((void*)t, kTransactionGetDefaultServer), {t, 0, 0});
    s64 st = 0;
    if (kDoOpen.direct()) st = as_driver(driver)->DoOpen(0, nullptr, reinterpret_cast<const yayoi::DBAddress*>(addr));
    else call_x8(kDoOpen.addr(), {driver, 0, 0, addr}, &st);
    if (st < 0) return;
    u64 sql = call(I->build_query, {driver, q, (u64)&m_entity, 0});
    if (!sql) return;
    driver_find(driver, sql, params, n, entity);
}

void CSimpleSqliteConnector::QueryToResultObjectSql(const char* sql, void* params, u32 n, void* entity) {
    u64 t = transaction();
    u64 driver = call(vslot((void*)t, kTransactionPSubstance), {t});
    driver_find(driver, (u64)sql, params, n, entity);
}

void CSimpleSqliteConnector::QueryToMsgPack(u32 query, u32 id, TSharedArray* data, s64* size) {
    const ConnectorInfo* I = info_of(this);
    Locked lock;
    Entity e;
    u64 key = 0;
    u32 bound = 0;
    if (query == 1 || query == 2) {
        snprintf(m_idText, sizeof m_idText, "%u", id);
        key = query == 2;
        bound = 1;
    }
    alignas(8) u8 param[0x28] = {};  // QueryParam: the key's name, type 7, the text, its length, 0, 0
    u64 name = *reinterpret_cast<const u64*>(I->keies + key * 0x10);
    u64 seven = 7, text = (u64)m_idText, len = std::strlen(m_idText);
    std::memcpy(param, &name, 8);
    std::memcpy(param + 8, &seven, 8);
    std::memcpy(param + 0x10, &text, 8);
    std::memcpy(param + 0x18, &len, 8);
    call(vslot(this, kConnQueryToResultObject), {(u64)this, query, (u64)param, bound, (u64)e.bytes});
    serialize_into(e, data, size);
}

void CSimpleSqliteConnector::QueryToMsgPackSql(const char* sql, TSharedArray* data, s64* size, void* params, u32 n) {
    Locked lock;
    Entity e;
    call(vslot(this, kConnQueryToResultObjectSql), {(u64)this, (u64)sql, (u64)params, n, (u64)e.bytes});
    serialize_into(e, data, size);
}

namespace {

std::string cmp_arrays(const TSharedArray& a, s64 na, const TSharedArray& b, s64 nb) {
    if (na != nb) return "size " + std::to_string(na) + " / " + std::to_string(nb);
    if (na > 0 && (!a.m_data || !b.m_data || std::memcmp(a.m_data, b.m_data, (size_t)na))) return "bytes";
    return {};
}

void h_msgpack_id(Cpu& c) {
    auto* self = reinterpret_cast<CSimpleSqliteConnector*>(c.x(0));
    auto* data = reinterpret_cast<TSharedArray*>(c.x(3));
    auto* size = reinterpret_cast<s64*>(c.x(4));
    u32 q = (u32)c.x(1), id = (u32)c.x(2);
    Fn* f = info_of(self)->fn_id;
    if (!f || !fam().due(*f)) return self->QueryToMsgPack(q, id, data, size);
    live::RunBothFamily::Scope scope;
    self->QueryToMsgPack(q, id, data, size);
    TSharedArray g{};
    s64 gs = 0;
    guest_call(f->orig, {(u64)self, q, id, (u64)&g, (u64)&gs});
    std::string why = cmp_arrays(*data, *size, g, gs);
    SimpleCode::release_array(&g);
    fam().result(*f, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
}

void h_msgpack_sql(Cpu& c) {
    auto* self = reinterpret_cast<CSimpleSqliteConnector*>(c.x(0));
    const char* sql = reinterpret_cast<const char*>(c.x(1));
    auto* data = reinterpret_cast<TSharedArray*>(c.x(2));
    auto* size = reinterpret_cast<s64*>(c.x(3));
    void* params = reinterpret_cast<void*>(c.x(4));
    u32 n = (u32)c.x(5);
    Fn* f = info_of(self)->fn_sql;
    if (!f || !fam().due(*f)) return self->QueryToMsgPackSql(sql, data, size, params, n);
    live::RunBothFamily::Scope scope;
    self->QueryToMsgPackSql(sql, data, size, params, n);
    TSharedArray g{};
    s64 gs = 0;
    guest_call(f->orig, {(u64)self, (u64)sql, (u64)&g, (u64)&gs, (u64)params, n});
    std::string why = cmp_arrays(*data, *size, g, gs);
    SimpleCode::release_array(&g);
    fam().result(*f, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
}

void h_result_id(Cpu& c) {
    reinterpret_cast<CSimpleSqliteConnector*>(c.x(0))->QueryToResultObject((u32)c.x(1), (void*)c.x(2), (u32)c.x(3), (void*)c.x(4));
}
void h_result_sql(Cpu& c) {
    reinterpret_cast<CSimpleSqliteConnector*>(c.x(0))->QueryToResultObjectSql((const char*)c.x(1), (void*)c.x(2), (u32)c.x(3),
                                                                              (void*)c.x(4));
}

// A live-check slot per connector and method (its trampoline is that connector's code: the check finds
// it through the connector's vtable).
bool bind() {
    for (size_t i = 0; i < kCount; i++) {
        const ConnectorSyms& s = kConnectors[i];
        Fn* fi = g_fns[i][0] = new Fn(fam(), s.msgpack_id);
        Fn* fs = g_fns[i][1] = new Fn(fam(), s.msgpack_sql);
        register_native_function({s.msgpack_id, &h_msgpack_id, "master: CSimpleSqliteConnector::QueryToMsgPack(q, id)", nullptr, &fi->orig,
                                  nullptr, "CSimpleSqliteConnector::QueryToMsgPack"});
        register_native_function({s.msgpack_sql, &h_msgpack_sql, "master: CSimpleSqliteConnector::QueryToMsgPack(sql)", nullptr,
                                  &fs->orig, nullptr, "CSimpleSqliteConnector::QueryToMsgPackSql"});
        register_native_function({s.result_id, &h_result_id, "master: CSimpleSqliteConnector::QueryToResultObject(q)", nullptr, nullptr,
                                  nullptr, "CSimpleSqliteConnector::QueryToResultObject"});
        register_native_function({s.result_sql, &h_result_sql, "master: CSimpleSqliteConnector::QueryToResultObject(sql)", nullptr,
                                  nullptr, nullptr, "CSimpleSqliteConnector::QueryToResultObjectSql"});
    }
    return true;
}
[[maybe_unused]] const bool g_bound = bind();

}  // namespace

}  // namespace soa::native::master
