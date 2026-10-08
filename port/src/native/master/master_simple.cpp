// CMasterParameterBaseSqlite_Simple<E>'s methods and DeserializeMsgPack<E> (master_simple.h): one body
// for every table. The guest's instantiations differ only in the element (its size, constructor,
// copy, destructor: master_element.cpp) and the shared_ptr control blocks' vtables.
#include "native/master/master_simple.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "core/loader.h"
#include "native/common/gen/common_addresses.h"
#include "native/common/live_call.h"
#include "native/data_formats/data_formats_layout.h"
#include "native/hash/hash_layout.h"
#include "native/master/gen/master_addresses.h"
#include "native/master/master_family.h"
#include "native/master/master_guest.h"
#include "native/params/gen/params_addresses.h"
#include "native/params/params_layout.h"

namespace soa::native::master {

using data_formats::AArray;
using data_formats::AMap;
using data_formats::AValue;
using data_formats::ASON;

namespace {

u64 opt_sym(const std::string& s) { return main_lib()->sym(s.c_str()); }

u64 vslot(const void* obj, u32 slot) { return reinterpret_cast<const u64*>(*reinterpret_cast<const u64*>(obj))[slot]; }
u64 vcall(const void* obj, u32 slot, std::initializer_list<u64> rest = {}) {
    u64 a[8] = {(u64)obj};
    size_t n = 1;
    for (u64 v : rest) a[n++] = v;
    return guest_call_raw(vslot(obj, slot), a, n, nullptr, 0, 0).x0;  // (the master checks are run-both: no recording)
}
// (out_call takes an initializer_list; the overloads below keep the call sites readable)
u64 call(u64 fn, std::initializer_list<u64> args) { return live::out_call(family(), fn, args); }

const char* primary_key(const CMasterParameterBaseSqlite* self) { return (const char*)vcall(self, kMasterPrimaryKeyName); }
bool enable_search(const CMasterParameterBaseSqlite* self) { return vcall(self, kMasterEnableSearchDatabase) & 1; }

void* connector_or_assert(const CMasterParameterSimple* self, int line) {
    void* c = self->base.m_pConnector;
    if (!c) g::Assert(g::kMasterSqliteH, line, g::kConnectorIsNull);
    return c;
}

void* operator_new(u64 n) {
    static const u64 f = g::sym("_Znwm");
    return (void*)call(f, {n});
}
void* operator_new_nothrow(u64 n) {
    static const u64 f = g::sym("_ZnwmRKSt9nothrow_t");
    static const u64 tag = g::sym("_ZSt7nothrow");
    return (void*)call(f, {n, tag});
}

// A fresh __shared_ptr_emplace<E, ParameterAllocator<E>> (operator new: the counts 0, then E()).
libcxx::shared_weak_count* new_emplace(const TableInfo& T, u8** elem) {
    auto* c = (libcxx::shared_weak_count*)operator_new(sizeof(libcxx::shared_weak_count) + T.el->size);
    c->shared_weak_owners = 0;
    c->vtable = (const void*)T.emplace_vtable;
    c->shared_owners = 0;
    *elem = reinterpret_cast<u8*>(c) + sizeof(libcxx::shared_weak_count);
    ElementCode::Ctor(*T.el, *elem);
    return c;
}

U32Node* new_shared_node(u32 key, u8* ptr, libcxx::shared_weak_count* ctrl) {
    auto* nd = (U32Node*)U32Map::alloc_block(sizeof(U32Node) + sizeof(SharedPtr));
    nd->key = key;
    auto* v = reinterpret_cast<SharedPtr*>(nd->value());
    v->ptr = ptr;
    v->ctrl = ctrl;
    if (ctrl) ctrl->__add_shared();
    nd->next = nullptr;
    nd->hash = key;
    return nd;
}

void copy_out(SharedPtr* out, const U32Node* n) {
    const auto* v = reinterpret_cast<const SharedPtr*>(const_cast<U32Node*>(n)->value());
    out->ptr = v->ptr;
    out->ctrl = v->ctrl;
    if (out->ctrl) out->ctrl->__add_shared();
}

// The key of a row's map: CHash32 of a string id, else the unsigned id (0 when it isn't one).
u32 row_key(const CMasterParameterBaseSqlite* self, const AMap* row, const AValue* id) {
    if (id->m_kind == AValue::kString) return hash::CHash32::OfCString(id->m_body.str.m_cstr);
    auto r = params::CParameterParser::GetValueUInt(row, primary_key(self));
    return r.found ? r.value : 0;
}

// A row into `map` as DeserializeMsgPack inserts it: a temporary element (constructed, Initialize,
// the row deserialized), its key, then a node copy-constructed from it unless the key is there.
void insert_row(const TableInfo& T, const CMasterParameterBaseSqlite* self, const AMap* row, const AValue* id, U32Map* map,
                std::vector<u64>& tmp) {
    const ElementInfo& el = *T.el;
    u8* e = reinterpret_cast<u8*>(tmp.data());
    ElementCode::Ctor(el, e);
    ElementCode::Initialize(el, e);
    element_base(e)->Deserialize(row);
    u32 key = row_key(self, row, id);
    if (!map->find(key)) {
        auto* nd = (U32Node*)U32Map::alloc_block(sizeof(U32Node) + el.size);
        nd->key = key;
        ElementCode::CtorCopy(el, nd->value(), e);
        nd->next = nullptr;
        nd->hash = key;
        map->insert(nd);
    }
    ElementCode::Dtor(el, e);
}

}  // namespace

TableInfo resolve_table(const ElementInfo& el, const char* m) {
    TableInfo T;
    T.el = &el;
    std::string e = m;
    if (u64 a = opt_sym("_ZTVNSt6__ndk120__shared_ptr_emplaceI" + e + "18ParameterAllocatorIS1_EEE")) T.emplace_vtable = a + 16;
    if (u64 a = opt_sym("_ZTVNSt6__ndk120__shared_ptr_pointerIP" + e + "NS_14default_deleteIS1_EENS_9allocatorIS1_EEEE"))
        T.pointer_vtable = a + 16;
    T.simple_vtable = opt_sym("_ZTV33CMasterParameterBaseSqlite_SimpleI" + e + "E");
    return T;
}

void SimpleCode::release_node_shared(U32Node* n) {
    auto* v = reinterpret_cast<SharedPtr*>(n->value());
    if (v->ctrl) v->ctrl->__release_shared();
}
void SimpleCode::destroy_node_element(const ElementInfo& el, U32Node* n) { ElementCode::Dtor(el, n->value()); }

void SimpleCode::release_array(TSharedArray* a) {
    static const u64 del = g::sym("_ZdaPv");
    static const u64 del_counter = g::sym("_ZN4Aska18TSharedPointerCode13DeleteCounterEPi");
    if (a->m_counter && __atomic_sub_fetch(a->m_counter, 1, __ATOMIC_ACQ_REL) != 0) {
        a->m_data = nullptr;
        return;
    }
    if (a->m_data) call(del, {(u64)a->m_data});
    if (a->m_counter) call(del_counter, {(u64)a->m_counter});
    a->m_data = nullptr;
}

// ---- DeserializeMsgPack<E> ----

void SimpleCode::DeserializeMsgPack(const TableInfo& T, const CMasterParameterBaseSqlite* self, const TSharedArray* data,
                                    const s64* size, u8* single, U32Map* map) {
    static const u64 ctor = g::sym("_ZN4Aska4ASONC1Ev"), init = g::sym("_ZN4Aska4ASON4InitEjb"),
                     deser = g::sym("_ZN4Aska4ASON11DeserializeEPKvm"), dtor = g::sym("_ZN4Aska4ASOND1Ev");
    alignas(16) u8 ason_bytes[sizeof(ASON)];
    auto* ason = reinterpret_cast<ASON*>(ason_bytes);
    call(ctor, {(u64)ason});
    u32 work = (u32)*size << 2;
    if (work < 0x2001) work = 0x2000;
    call(init, {(u64)ason, work, 1});
    call(deser, {(u64)ason, (u64)data->m_data, (u64)*size});
    const AValue& root = ason->m_root;
    std::vector<u64> tmp((T.el->size + 7) / 8);
    if (root.m_kind == AValue::kArray) {
        const AArray& arr = root.m_body.array;
        if (map) map->rehash(fcvtpu((float)arr.m_count / map->max_load_factor));
        for (u32 i = 0; i < arr.m_count; i++) {
            const AValue* v = &arr.m_elements[i];
            if (!v) g::Assert(g::kMasterSqliteH, 0x1b0, g::kPValueIsNull);
            const AMap* row = &v->m_body.map;
            const AValue* id = const_cast<AMap*>(row)->Get_(primary_key(self));
            if (!id) break;
            if (!map) {
                if (single) {
                    vcall(single, params::CParameterElementBase::kSlotInitialize);
                    vcall(single, params::CParameterElementBase::kSlotDeserialize, {(u64)row});
                }
                break;
            }
            insert_row(T, self, row, id, map, tmp);
        }
    } else if (root.m_kind == AValue::kMap) {
        const AMap* row = &root.m_body.map;
        if (!map) {
            if (single) {
                vcall(single, params::CParameterElementBase::kSlotInitialize);
                vcall(single, params::CParameterElementBase::kSlotDeserialize, {(u64)row});
            }
        } else {
            // (the element is built and deserialized before the key is looked up)
            const ElementInfo& el = *T.el;
            u8* e = reinterpret_cast<u8*>(tmp.data());
            ElementCode::Ctor(el, e);
            ElementCode::Initialize(el, e);
            element_base(e)->Deserialize(row);
            const AValue* id = const_cast<AMap*>(row)->Get_(primary_key(self));
            if (id) {
                u32 key = row_key(self, row, id);
                if (!map->find(key)) {
                    auto* nd = (U32Node*)U32Map::alloc_block(sizeof(U32Node) + el.size);
                    nd->key = key;
                    ElementCode::CtorCopy(el, nd->value(), e);
                    nd->next = nullptr;
                    nd->hash = key;
                    map->insert(nd);
                }
            }
            ElementCode::Dtor(el, e);
        }
    } else {
        g::Assert(g::kMasterSqliteH, 0x1d7, g::kMsgpackInvalid);
    }
    call(dtor, {(u64)ason});
}

// ---- the lookups ----

void SimpleCode::pParameterFromHash(const TableInfo& T, const This* self, SharedPtr* out, u32 hash) {
    auto* me = const_cast<This*>(self);
    if (U32Node* n = me->m_cache.find(hash)) return copy_out(out, n);
    if (U32Node* n = me->m_all.find(hash)) return copy_out(out, n);
    if (!enable_search(&self->base)) {
        *out = {};
        return;
    }
    void* conn = connector_or_assert(self, 0x4d);
    vcall(conn, kConnOpen, {g::at(g::kBasMaster)});
    TSharedArray arr{};
    s64 size = 0;
    vcall(conn, kConnQueryToMsgPackId, {1, hash, (u64)&arr, (u64)&size});
    if (size < 1) {
        *out = {};
    } else {
        if (me->m_cache.size > me->m_cacheLimit) me->m_cache.clear(release_node_shared);
        U32Map tmp{};
        tmp.max_load_factor = 1.0f;
        DeserializeMsgPack(T, &self->base, &arr, &size, nullptr, &tmp);
        for (U32Node* n = tmp.first; n; n = n->next) {
            u8* e;
            libcxx::shared_weak_count* c = new_emplace(T, &e);
            ElementCode::Assign(*T.el, e, n->value());
            if (!me->m_cache.find(n->key)) me->m_cache.insert(new_shared_node(n->key, e, c));
            c->__release_shared();
        }
        if (U32Node* n = me->m_cache.find(hash)) copy_out(out, n);
        else *out = {};
        tmp.destroy([&](U32Node* n) { destroy_node_element(*T.el, n); });
    }
    release_array(&arr);
    if (!conn) g::Assert(g::kMasterSqliteH, 0x52, g::kConnectorIsNull);
    vcall(conn, kConnClose);
}

u32 SimpleCode::MakeCacheKey(const char* sql, const void* params, u32 n) {
    char buf[0x100 + 0x400] = {};  // (the guest's is 0x100: a longer key overflows its frame; here it doesn't)
    snprintf(buf, 0x100, "%s", sql);
    if (params && n) {
        static const u64 assert_fn = g::sym("_ZN9Framework9gDoAssertEPKciS1_z");
        const u8* p = reinterpret_cast<const u8*>(params);
        for (u32 i = 0; i < n; i++, p += 0x28) {
            const char* s = *reinterpret_cast<const char* const*>(p + 0x10);  // QueryParam's text (yayoi_layout.h)
            u64 a = std::strlen(buf), b = std::strlen(s);
            if (a + b > 0xff) call(assert_fn, {g::at(g::kUtilityH), 0x83, g::at(g::kStrcatSmall), a, b, 0x100});
            if (a + b < sizeof buf) std::strcat(buf, s);
        }
    }
    return hash::CHash32::OfCString(buf);
}

void SimpleCode::InsertCustomizeCache(const This* self, u32 key, const SharedPtr* p) {
    auto* me = const_cast<This*>(self);
    U32Map& m = me->m_queryCache;
    if (me->m_queryLimit <= m.size && m.size) m.clear(release_node_shared);
    if (m.find(key)) return;
    m.insert(new_shared_node(key, p->ptr, p->ctrl));
}

void SimpleCode::ParameterByQuery(const TableInfo& T, const This* self, SharedPtr* out, const char* sql, void* params, u32 n) {
    u32 key = MakeCacheKey(sql, params, n);
    if (U32Node* nd = self->m_queryCache.find(key)) return copy_out(out, nd);
    if (!enable_search(&self->base)) {
        *out = {};
        return;
    }
    void* conn = connector_or_assert(self, 0x4d);
    vcall(conn, kConnOpen, {g::at(g::kBasMaster)});
    TSharedArray arr{};
    s64 size = 0;
    vcall(conn, kConnQueryToMsgPack, {(u64)sql, (u64)&arr, (u64)&size, (u64)params, n});
    if (size < 1) {
        *out = {};
    } else {
        u8* e = (u8*)operator_new_nothrow(T.el->size);
        if (e) ElementCode::Ctor(*T.el, e);
        DeserializeMsgPack(T, &self->base, &arr, &size, e, nullptr);
        out->ptr = e;
        auto* c = (u64*)operator_new(0x20);  // __shared_ptr_pointer: vtable, counts, the pointer
        c[2] = 0;
        c[3] = (u64)e;
        out->ctrl = (libcxx::shared_weak_count*)c;
        c[0] = T.pointer_vtable;
        c[1] = 0;
        InsertCustomizeCache(self, key, out);
    }
    release_array(&arr);
    vcall(conn, kConnClose);
}

void SimpleCode::ParameterByQueryMap(const TableInfo& T, const This* self, const char* sql, U32Map* out, void* params, u32 n) {
    if (!enable_search(&self->base)) return;
    void* conn = connector_or_assert(self, 0x4d);
    vcall(conn, kConnOpen, {g::at(g::kBasMaster)});
    TSharedArray arr{};
    s64 size = 0;
    vcall(conn, kConnQueryToMsgPack, {(u64)sql, (u64)&arr, (u64)&size, (u64)params, n});
    if (size > 0) DeserializeMsgPack(T, &self->base, &arr, &size, nullptr, out);
    release_array(&arr);
    vcall(conn, kConnClose);
}

// ---- the caches ----

void SimpleCode::ClearCache(This* self) {
    self->m_cache.clear(release_node_shared);
    self->m_queryCache.clear(release_node_shared);
}

void SimpleCode::SetStoreAllCacheSize(const TableInfo& T, This* self) {
    void* conn = connector_or_assert(self, 0x4d);
    vcall(conn, kConnOpen, {g::at(g::kBasMaster)});
    TSharedArray arr{};
    s64 size = 0;
    vcall(conn, kConnQueryToMsgPackId, {0, 0, (u64)&arr, (u64)&size});
    if (size > 0) {
        U32Map tmp{};
        tmp.max_load_factor = 1.0f;
        DeserializeMsgPack(T, &self->base, &arr, &size, nullptr, &tmp);
        self->m_cacheLimit = tmp.size;
        tmp.destroy([&](U32Node* n) { destroy_node_element(*T.el, n); });
    }
    release_array(&arr);
    if (!conn) g::Assert(g::kMasterSqliteH, 0x52, g::kConnectorIsNull);
    vcall(conn, kConnClose);
}

void SimpleCode::Initialize(This* self) {
    void* c = (void*)vcall(&self->base, kMasterInstantiateSqlConnector);
    self->base.m_pConnector = c;
    if (!c) g::Assert(g::kMasterSqliteH, 0x165, g::kSqlConnectorIsNull);
}

void SimpleCode::Dtor(const TableInfo& T, This* self) {
    self->base.vtable = (const void*)(T.simple_vtable + 0x10);
    self->parameter.vtable = (const void*)(T.simple_vtable + 0x70);
    self->m_queryCache.destroy(release_node_shared);
    self->m_cache.destroy(release_node_shared);
    self->m_all.destroy(release_node_shared);
    static const u64 base_vt = g::sym("_ZTV26CMasterParameterBaseSqlite") + 0x10;
    self->base.vtable = (const void*)base_vt;
    if (void* c = self->base.m_pConnector) {
        vcall(c, kConnDtorDelete);
        self->base.m_pConnector = nullptr;
    }
}

bool SimpleCode::Deserialize(This* self, const AMap* map) {
    if (!map) g::Assert(g::kMasterSqliteH, 0x200, params::g::kApParserIsNull);
    auto* root = (const AValue*)vcall(&self->parameter, params::CParameterBase::kSlotGetRoot, {(u64)map});
    if (root) vcall(&self->base, kMasterDeserializeParameter, {(u64)&self->m_all, (u64)&root->m_body.array});
    return root != nullptr;
}

bool SimpleCode::ReleaseParameter(This* self, const char* name) {
    u32 h = hash::CHash32::OfCString(name);
    if (U32Node* n = self->m_all.find(h)) {
        self->m_all.unlink(n);
        release_node_shared(n);
        U32Map::free_block(n);
        return true;
    }
    const char* mine = (const char*)vcall(&self->parameter, params::CParameterBase::kSlotParseName);
    if (std::strcmp(name, mine) == 0) self->m_all.clear(release_node_shared);
    return true;
}

bool SimpleCode::DeserializeParameter(const TableInfo& T, This* self, U32Map* map, const AArray* array) {
    u32 count;
    if (!array) {
        g::Assert(g::kMasterSqliteH, 0x221, g::kApArrayIsNull);
        count = 0;  // (the guest reads address 8 here: a crash)
    } else {
        count = array->m_count;
    }
    for (u32 i = 0; i < count; i++) {
        const AValue* v = &array->m_elements[i];
        if (!v) g::Assert(g::kMasterSqliteH, 0x224, g::kPValueIsNull);
        const AMap* row = &v->m_body.map;
        const AValue* id = const_cast<AMap*>(row)->Get_(primary_key(&self->base));
        if (!id) continue;
        u32 kind = id->m_kind;
        const char* key_name = primary_key(&self->base);
        u32 key;
        if (kind == AValue::kString) {
            auto r = params::CParameterParser::GetValueString(row, key_name);
            if (!r.found) continue;
            key = hash::CHash32::OfCString(r.value);
        } else {
            auto r = params::CParameterParser::GetValueUInt(row, key_name);
            if (!r.found) continue;
            key = r.value;
        }
        u8* target;
        if (U32Node* n = map->find(key)) {
            target = reinterpret_cast<SharedPtr*>(n->value())->ptr;
        } else {
            u8* e;
            libcxx::shared_weak_count* c = new_emplace(T, &e);
            if (!map->find(key)) map->insert(new_shared_node(key, e, c));
            vcall(e, params::CParameterElementBase::kSlotInitialize);
            c->__release_shared();
            target = e;
        }
        vcall(target, params::CParameterElementBase::kSlotDeserialize, {(u64)row});
    }
    return true;
}

}  // namespace soa::native::master
