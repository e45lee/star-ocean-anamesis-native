#pragma once
// CMasterParameterBaseSqlite_Simple<E> and CMasterParameterBaseSqlite::DeserializeMsgPack<E> (the
// tables' caches and lookups, master_layout.h CMasterParameterSimple): the code every table shares,
// over the element class's ElementInfo and the table's own guest addresses (TableInfo), and
// TSimple<E>, whose members are the natives (master_simple_bind.cpp binds every instantiation the
// generator lists). port/decomp/master/simple_item.c and stringdb.c are the decompiles read.
#include <span>

#include "native/master/master_element.h"
#include "native/master/master_hash.h"

namespace soa::native::master {

// One table's guest addresses besides its element's (resolved on first use; 0 when the lib has no
// such symbol: only the instantiations a method needs exist).
struct TableInfo {
    const ElementInfo* el = nullptr;
    u64 emplace_vtable = 0;   // __shared_ptr_emplace<E, ParameterAllocator<E>> (+16)
    u64 pointer_vtable = 0;   // __shared_ptr_pointer<E*, default_delete<E>, allocator<E>> (+16)
    u64 simple_vtable = 0;    // _ZTV33CMasterParameterBaseSqlite_SimpleI<E>E (the symbol; +0x10 / +0x70 its two tables)
};
TableInfo resolve_table(const ElementInfo& el, const char* mangled_element);

// The code over a table's bytes.
struct SimpleCode {
    using This = CMasterParameterSimple;
    static void pParameterFromHash(const TableInfo& T, const This* self, SharedPtr* out, u32 hash);
    static void ParameterByQuery(const TableInfo& T, const This* self, SharedPtr* out, const char* sql, void* params, u32 n);
    static void ParameterByQueryMap(const TableInfo& T, const This* self, const char* sql, U32Map* out, void* params, u32 n);
    static u32 MakeCacheKey(const char* sql, const void* params, u32 n);
    static void InsertCustomizeCache(const This* self, u32 key, const SharedPtr* p);
    static void ClearCache(This* self);
    static void SetStoreAllCacheSize(const TableInfo& T, This* self);
    static void Initialize(This* self);
    static void Dtor(const TableInfo& T, This* self);
    static bool Deserialize(This* self, const data_formats::AMap* map);
    static bool ReleaseParameter(This* self, const char* name);
    static bool DeserializeParameter(const TableInfo& T, This* self, U32Map* map, const data_formats::AArray* array);
    // CMasterParameterBaseSqlite::DeserializeMsgPack<E>(data, size, single, map) const
    static void DeserializeMsgPack(const TableInfo& T, const CMasterParameterBaseSqlite* self, const TSharedArray* data,
                                   const s64* size, u8* single, U32Map* map);

    // helpers shared with the checks and tests
    static void release_node_shared(U32Node* n);    // a shared_ptr<E> node's value released
    static void destroy_node_element(const ElementInfo& el, U32Node* n);  // an E node's ~E()
    static void release_array(TSharedArray* a);     // ~TSharedArray
};

// E -> its table (master_simple_bind.cpp specializes it for every element of MASTER_ELEMENTS).
template <class E>
const TableInfo& table_info() {
    static const TableInfo T = resolve_table(element_info<E>(), ElementTraits<E>::mangled);
    return T;
}

// ---- the live check (master_simple_check.cpp): run-both on a copy of the table ----

enum class SimpleRole {
    pParameterFromHash, ParameterByQuery, ParameterByQueryMap, MakeCacheKey, InsertCustomizeCache, ClearCache,
    SetStoreAllCacheSize, Initialize, Dtor, Deserialize, ReleaseParameter, DeserializeParameter, DeserializeMsgPack, kCount
};
SimpleRole simple_role(const char* name);  // kCount when unknown
template <class E>
struct SimpleFns {
    static inline Fn* fn[(int)SimpleRole::kCount] = {};
};
template <class E>
Fn* simple_fn(SimpleRole r) {
    Fn* f = SimpleFns<E>::fn[(int)r];
    return f && fam().due(*f) ? f : nullptr;
}
// Each runs the native on the table, the original (f.orig) on a copy of the table as it was (its maps
// copied, the elements shared), and compares results and caches.
struct SimpleCheck {
    using This = CMasterParameterSimple;
    static void pParameterFromHash(const TableInfo& T, Fn& f, This* self, SharedPtr* out, u32 hash);
    static void ParameterByQuery(const TableInfo& T, Fn& f, This* self, SharedPtr* out, const char* sql, void* params, u32 n);
    static void ParameterByQueryMap(const TableInfo& T, Fn& f, This* self, const char* sql, U32Map* out, void* params, u32 n);
    static u32 MakeCacheKey(Fn& f, This* self, const char* sql, void* params, u32 n);
    static void InsertCustomizeCache(const TableInfo& T, Fn& f, This* self, u32 key, const SharedPtr* p);
    static void Plain(const TableInfo& T, Fn& f, This* self, SimpleRole r);  // ClearCache, SetStoreAllCacheSize, Initialize, Dtor
    static bool Deserialize(const TableInfo& T, Fn& f, This* self, const data_formats::AMap* map);
    static bool ReleaseParameter(const TableInfo& T, Fn& f, This* self, const char* name);
    static bool DeserializeParameter(const TableInfo& T, Fn& f, This* self, U32Map* map, const data_formats::AArray* array);
    static void DeserializeMsgPack(const TableInfo& T, Fn& f, This* self, const TSharedArray* data, const s64* size, u8* single,
                                   U32Map* map);
};

// The natives: TSimple<E>'s layout is CMasterParameterSimple's.
template <class E>
class TSimple {
public:
    using R = SimpleRole;
    void pParameterFromHash(SharedPtr* out, u32 hash) const {
        if (Fn* f = simple_fn<E>(R::pParameterFromHash)) return SimpleCheck::pParameterFromHash(table_info<E>(), *f, me(), out, hash);
        SimpleCode::pParameterFromHash(table_info<E>(), &s, out, hash);
    }
    void ParameterByQuery(SharedPtr* out, const char* sql, void* params, u32 n) const {
        if (Fn* f = simple_fn<E>(R::ParameterByQuery)) return SimpleCheck::ParameterByQuery(table_info<E>(), *f, me(), out, sql, params, n);
        SimpleCode::ParameterByQuery(table_info<E>(), &s, out, sql, params, n);
    }
    void ParameterByQueryMap(const char* sql, U32Map* out, void* params, u32 n) const {
        if (Fn* f = simple_fn<E>(R::ParameterByQueryMap))
            return SimpleCheck::ParameterByQueryMap(table_info<E>(), *f, me(), sql, out, params, n);
        SimpleCode::ParameterByQueryMap(table_info<E>(), &s, sql, out, params, n);
    }
    u32 MakeCacheKey(const char* sql, void* params, u32 n) const {
        if (Fn* f = simple_fn<E>(R::MakeCacheKey)) return SimpleCheck::MakeCacheKey(*f, me(), sql, params, n);
        return SimpleCode::MakeCacheKey(sql, params, n);
    }
    void InsertCustomizeCache(u32 key, const SharedPtr* p) const {
        if (Fn* f = simple_fn<E>(R::InsertCustomizeCache)) return SimpleCheck::InsertCustomizeCache(table_info<E>(), *f, me(), key, p);
        SimpleCode::InsertCustomizeCache(&s, key, p);
    }
    void ClearCache() {
        if (Fn* f = simple_fn<E>(R::ClearCache)) return SimpleCheck::Plain(table_info<E>(), *f, &s, R::ClearCache);
        SimpleCode::ClearCache(&s);
    }
    void SetStoreAllCacheSize() {
        if (Fn* f = simple_fn<E>(R::SetStoreAllCacheSize)) return SimpleCheck::Plain(table_info<E>(), *f, &s, R::SetStoreAllCacheSize);
        SimpleCode::SetStoreAllCacheSize(table_info<E>(), &s);
    }
    void Initialize() {
        if (Fn* f = simple_fn<E>(R::Initialize)) return SimpleCheck::Plain(table_info<E>(), *f, &s, R::Initialize);
        SimpleCode::Initialize(&s);
    }
    void Dtor() {
        if (Fn* f = simple_fn<E>(R::Dtor)) return SimpleCheck::Plain(table_info<E>(), *f, &s, R::Dtor);
        SimpleCode::Dtor(table_info<E>(), &s);
    }
    bool Deserialize(const data_formats::AMap* map) {
        if (Fn* f = simple_fn<E>(R::Deserialize)) return SimpleCheck::Deserialize(table_info<E>(), *f, &s, map);
        return SimpleCode::Deserialize(&s, map);
    }
    bool ReleaseParameter(const char* name) {
        if (Fn* f = simple_fn<E>(R::ReleaseParameter)) return SimpleCheck::ReleaseParameter(table_info<E>(), *f, &s, name);
        return SimpleCode::ReleaseParameter(&s, name);
    }
    bool DeserializeParameter(U32Map* map, const data_formats::AArray* array) {
        if (Fn* f = simple_fn<E>(R::DeserializeParameter)) return SimpleCheck::DeserializeParameter(table_info<E>(), *f, &s, map, array);
        return SimpleCode::DeserializeParameter(table_info<E>(), &s, map, array);
    }
    // CMasterParameterBaseSqlite::DeserializeMsgPack<E> (this: the base; a concrete table)
    void DeserializeMsgPack(const TSharedArray* data, const s64* size, u8* single, U32Map* map) const {
        if (Fn* f = simple_fn<E>(R::DeserializeMsgPack))
            return SimpleCheck::DeserializeMsgPack(table_info<E>(), *f, me(), data, size, single, map);
        SimpleCode::DeserializeMsgPack(table_info<E>(), &s.base, data, size, single, map);
    }

    CMasterParameterSimple s;

private:
    CMasterParameterSimple* me() const { return const_cast<CMasterParameterSimple*>(&s); }
};

}  // namespace soa::native::master
