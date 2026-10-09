// master_layout.h: the guest data layouts of the `master` subsystem (master data: the SQLite connectors, the master parameter tables, StringDB, CMasterManager / CMasterCache).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/master/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types master` turns the structs into port/decomp/master/types.json for Ghidra.
#ifndef SOA_NATIVE_MASTER_LAYOUT_H
#define SOA_NATIVE_MASTER_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../params/params_layout.h"
#include "gen/master_elements.h"

namespace soa::native::master {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// ---- the elements ----------------------------------------------------------------------------------------
//
// The rows of the master tables as the client keeps them: one class per table (the T of
// CMasterParameterBaseSqlite_Simple<T> / _Category<T>), a CParameterElementBase followed by its
// properties (params_layout.h). The 160 classes are generated (gen/master_elements.h,
// tools/gen_master_elements.py: the inlined default constructor, the destructor and Initialize read
// from the lib); their code is the same for every class but for the property list, so the natives are
// one template over the generated class.

// The N- and T-independent views of a property: CParameterPropertyBase<N>'s layout (vtable, m_next,
// m_named, m_name) is the same for every N, a value's m_value is at +0x28 whatever its T, a string's
// String at +0x28 (params_layout.h).
using AnyProperty = params::CParameterPropertyBase<0>;
using AnyValueProperty = params::CParameterPropertyValue<u64, 0>;
using AnyStringProperty = params::CParameterPropertyString<0>;
static_assert(sizeof(AnyProperty) == 0x28 && offsetof(AnyValueProperty, m_value) == 0x28 && offsetof(AnyStringProperty, m_value) == 0x28);
static_assert(sizeof(AnyValueProperty) == 0x30 && sizeof(AnyStringProperty) == 0x40);

// TElement<E>: the methods every element class has (each exported for most classes; the generated
// kEMethods list says which). Layout: E's.
template <class E>
class TElement {
public:
    // E::E(): CParameterElementBase(), the element's vtable; each property: its final vtable, m_next = 0,
    // m_named = 0, CHash32() (vtable, hash 0); a string's three words 0. Values are left as they were.
    void Ctor();  // _ZN<E>C2Ev (inlined into the templates for every class)
    // E::E(E const&): vtables as Ctor; m_first, each m_next, m_named, hash and value copied as they are
    // (the copy's list still runs through the source's properties: a guest quirk, kept); strings copied
    // (a long one into new storage from the STL allocator).
    void CtorCopy(const TElement* o);  // _ZN<E>C2ERKS_
    // E::operator=(E const&): m_first, each m_next, m_named, hash, value; strings assigned (libc++
    // assign: in place when it fits, else __grow_by_and_replace). Vtables untouched.
    TElement* Assign(const TElement* o);  // _ZN<E>aSERKS_
    // ~E() (D2): the element's vtable back; each property from the last: a string's
    // CParameterPropertyString<N> vtable, its long storage freed, then CParameterPropertyBase<N>'s
    // vtable; ~CHash32 (a RET).
    void Dtor();        // _ZN<E>D2Ev
    void DtorDelete();  // _ZN<E>D0Ev: ~E(), operator delete
    // E::Initialize() (vtable slot 0): each named property in the AddProperty order: m_name = CHash32(key)
    // (a key of 23 bytes or more goes through a long std::string: allocated and freed around it),
    // m_named = 1, a value property's default, AddProperty.
    void Initialize();  // _ZN<E>10InitializeEv

    E e;
};

// ---- the tables ------------------------------------------------------------------------------------------

// Aska::TSharedArray<signed char>: a counted buffer (a connector's MessagePack): the data (operator
// new[]) and its counter (Aska::TSharedPointerCode; freed with DeleteCounter when it drops to 0).
struct TSharedArray {
    s8* m_data;      // 0x00
    s32* m_counter;  // 0x08
};
static_assert(sizeof(TSharedArray) == 0x10);

// std::shared_ptr<E> as the maps and the x8 results hold it.
struct SharedPtr {
    u8* ptr;                          // 0x00: the element
    libcxx::shared_weak_count* ctrl;  // 0x08: its control block (or null)
};
static_assert(sizeof(SharedPtr) == 0x10);

// CSqliteTransaction (CStaticTransaction + 0x40, the master DB's): the vtable slots the connector calls.
// _ZTV18CSqliteTransaction: 0 / 1 destructors, 2 Open(char const*), 3 Close(), 4 pSubstance() (the
// Aska::Yayoi::SQLiteDriver), 5 GetDefaultServer(Entity::Mode, char const*) const (the DBAddress).
enum TransactionSlot : u32 {
    kTransactionPSubstance = 4,
    kTransactionGetDefaultServer = 5,
};

// The connector interface the tables call (CSimpleSqliteConnector<...>'s vtable): slot numbers.
// Layout of the connector itself below (CSimpleSqliteConnector).
enum ConnectorSlot : u32 {
    kConnDtor = 0,
    kConnDtorDelete = 1,
    kConnOpen = 2,                // Open(char const* file): a RET in the 3.7.0 connectors
    kConnClose = 3,               // Close(): a RET
    kConnQueryToResultObject = 4, // (unsigned query, QueryParam*, unsigned n, TEntityObject&)
    kConnQueryToMsgPackId = 5,    // (unsigned query, unsigned id, TSharedArray&, long& size)
    kConnQueryToMsgPack = 6,      // (char const* sql, TSharedArray&, long& size, QueryParam*, unsigned n)
    kConnQueryToResultObjectSql = 7,
};

// CSimpleSqliteConnector<Table, Entity>: one table's SQL, guest size 0x118 (operator new(0x118, nothrow)
// in the concrete tables' InstantiateSqlConnector: the vtable, the CLocalEntity<Table> sub-object's vtable
// twice). Layout from QueryToMsgPack (the id printed with "%u" at +0x18, 0x100 bytes) and
// QueryToResultObject (the CLocalEntity at +0x10 is BuildQuery's entity). port/decomp/master/connector_text.c.
// Every connector's four query methods have the same code but for the CLocalEntity's statics (its
// queries: a QueryObject of 0x20 each, as many as the count; its primary keys: 0x10 each) and the
// BuildQuery<CLocalEntity> instantiation (gen/master_connectors.inc, checked by the generator).
class CSimpleSqliteConnector {
public:
    // vtable slots 2-7 (ConnectorSlot), the four bound:
    // QueryToMsgPack(q, id, data, size): under CStaticTransaction's mutex: q 1 / 2: the id as "%u" into
    // m_idText and the q-1st primary key as a QueryParam's name (type 7, the text, its length);
    // else no parameter (the key the first, the text whatever m_idText holds); QueryToResultObject(q) through
    // the vtable into an EntityObject, its rows serialized (EntityObject::Serialize) into data / size.
    void QueryToMsgPack(u32 query, u32 id, TSharedArray* data, s64* size);
    void QueryToMsgPackSql(const char* sql, TSharedArray* data, s64* size, void* params, u32 n);
    // QueryToResultObject(q): the driver (CStaticTransaction + 0x40, slot 4); q below the count: DoOpen(0, 0,
    // slot 5's address), then BuildQuery(the q-th query, the CLocalEntity) and Find.
    void QueryToResultObject(u32 query, void* params, u32 n, void* entity);
    void QueryToResultObjectSql(const char* sql, void* params, u32 n, void* entity);

    const void* vtable;        // 0x00
    const void* m_entity0;     // 0x08: CLocalEntity<Table>'s vtable
    const void* m_entity;      // 0x10: the CLocalEntity<Table> (its vtable): BuildQuery's entity
    char m_idText[0x100];      // 0x18: the id QueryToMsgPack(q, id) binds, "%u"
};
static_assert(offsetof(CSimpleSqliteConnector, m_entity) == 0x10);
static_assert(offsetof(CSimpleSqliteConnector, m_idText) == 0x18);
static_assert(sizeof(CSimpleSqliteConnector) == 0x118);

// CMasterParameterBaseSqlite: the tables' base, guest size 0x10 (vtable, the connector). Layout from
// _Simple<T>'s destructor (the connector's deleting destructor, slot 1) and Initialize (the
// connector from slot 6). Vtable (_ZTV26CMasterParameterBaseSqlite, then each _Simple<T>'s):
enum MasterSlot : u32 {
    kMasterDtor = 0,
    kMasterDtorDelete = 1,            // a trap in _Simple<T> (never deleted through this base)
    kMasterInitialize = 2,            // _Simple<T>::Initialize
    kMasterPrimaryKeyName = 3,        // pPrimaryKeyName(): "id" unless the class overrides it
    kMasterGetQueryIndex = 4,
    kMasterEnableSearchDatabase = 5,  // false: the table isn't queried (lookups miss)
    kMasterInstantiateSqlConnector = 6,  // the concrete class's: a new CSimpleSqliteConnector<...>
    kMasterDeserialize = 7,           // _Simple<T>::Deserialize(AMap const*)
    kMasterReleaseParameter = 8,
    kMasterDeserializeParameter = 9,  // (map&, AArray const*)
};
class CMasterParameterBaseSqlite {
public:
    const void* vtable;  // 0x00
    void* m_pConnector;  // 0x08: CSimpleSqliteConnector<...>* (from InstantiateSqlConnector)
};
static_assert(sizeof(CMasterParameterBaseSqlite) == 0x10);

// Framework::CSTLUnorderedMap<unsigned int, V> (libc++'s unordered_map with std::hash<unsigned> and
// the STL allocator; libcxx_layout.h hash_table), whatever V is (master_hash.cpp: libc++ 6.0's
// algorithms as the game's instantiations compile them, port/decomp/libcxx/hash.c, port/decomp/master/
// stringdb.c: rehash, __rehash, the inlined find / __node_insert_unique / erase / clear; storage from
// the STL allocator, "STL_UnorderedMap.h", 0x1c).
// A node's fixed part; the value follows at +0x18.
struct U32Node {
    U32Node* next;  // 0x00
    u64 hash;       // 0x08: the key (std::hash<unsigned>)
    u32 key;        // 0x10
    u32 pad_14;     // 0x14: (padding; a pair<u32, bool> would keep its bool here)
    u8* value() { return reinterpret_cast<u8*>(this) + 0x18; }
};
static_assert(sizeof(U32Node) == 0x18);

// The table (libcxx::hash_table's layout, 0x28 bytes) with the operations the master code inlines.
class U32Map {
public:
    static u64 constrain(u64 h, u64 n) { return (n & (n - 1)) == 0 ? h & (n - 1) : (h < n ? h : h % n); }

    U32Node* find(u32 key) const;
    // libc++'s rehash(n): n rounded to a prime (2 for 1), then __rehash when it grows, or when it
    // shrinks below what the size needs.
    void rehash(u64 n);
    void rehash_exact(u64 n);  // __rehash(n)
    // __node_insert_unique of a node the caller made (its key and hash set; the key not present):
    // grows first when the load would pass max_load_factor.
    void insert(U32Node* nd);
    // erase(node) (the node unlinked, size - 1; the caller frees it).
    void unlink(U32Node* nd);
    // clear(): when not empty, every node destroyed (destroy(node), then freed), the buckets zeroed.
    template <typename F>
    void clear(F destroy) {
        if (!size) return;
        free_nodes(destroy);
        first = nullptr;
        for (u64 i = 0; i < bucket_count; i++) buckets[i] = nullptr;
        size = 0;
    }
    // ~unordered_map: every node destroyed and freed, then the bucket array.
    template <typename F>
    void destroy(F destroy) {
        free_nodes(destroy);
        U32Node** b = buckets;
        buckets = nullptr;
        if (b) free_block(b);
    }

    U32Node** buckets;      // 0x00
    u64 bucket_count;       // 0x08
    U32Node* first;         // 0x10 (the anchor: buckets point at the node before theirs, or here)
    u64 size;               // 0x18
    float max_load_factor;  // 0x20
    u8 pad_24[4];

    static void* alloc_block(u64 n);  // Allocate(n, "STL_UnorderedMap.h", 0x1c), with the allocator's assert
    static void free_block(void* p);

private:
    template <typename F>
    void free_nodes(F destroy) {
        for (U32Node* n = first; n;) {
            U32Node* next = n->next;
            destroy(n);
            free_block(n);
            n = next;
        }
    }
    U32Node* anchor() { return reinterpret_cast<U32Node*>(&first); }  // (next at +0: the before-begin node)
};
static_assert(sizeof(U32Map) == 0x28);
static_assert(offsetof(U32Map, first) == offsetof(libcxx::hash_table<u32>, first));
static_assert(offsetof(U32Map, max_load_factor) == offsetof(libcxx::hash_table<u32>, max_load_factor));


// CMasterParameterBaseSqlite_Simple<T>: a table's caches and lookups, guest size 0xa0 (what the
// _Simple<T> methods touch; a concrete class (CMasterParameterItem, StringDB, ...) may add fields).
// Layout from the destructor (three maps, then the base), ClearCache, pParameterFromHash (m_cache
// first, then m_all; the eviction past m_cacheLimit), ParameterByQuery / InsertCustomizeCache
// (m_queryCache, m_queryLimit), SetStoreAllCacheSize (m_cacheLimit = the table's row count),
// ReleaseParameter (m_all). port/decomp/master/simple_item.c, stringdb.c. The concrete classes
// are constructed inline by their users (no exported constructor).
class CMasterParameterSimple {
public:
    CMasterParameterBaseSqlite base;  // 0x00
    params::CParameterBase parameter; // 0x10: the second base (CParameterBase's vtable: pParseName, pGetRoot)
    U32Map m_all;             // 0x18: by id, every row (StoreAllCache / DeserializeParameter)
    U32Map m_cache;           // 0x40: by id, the rows looked up (pParameterFromHash)
    u64 m_cacheLimit;                 // 0x68: m_cache is cleared when a miss finds it larger
    U32Map m_queryCache;      // 0x70: by MakeCacheKey(query, params), ParameterByQuery's rows
    u64 m_queryLimit;                 // 0x98: m_queryCache is cleared when an insert finds it this full
};
static_assert(offsetof(CMasterParameterSimple, parameter) == 0x10);
static_assert(offsetof(CMasterParameterSimple, m_all) == 0x18);
static_assert(offsetof(CMasterParameterSimple, m_cache) == 0x40);
static_assert(offsetof(CMasterParameterSimple, m_cacheLimit) == 0x68);
static_assert(offsetof(CMasterParameterSimple, m_queryCache) == 0x70);
static_assert(offsetof(CMasterParameterSimple, m_queryLimit) == 0x98);
static_assert(sizeof(CMasterParameterSimple) == 0xa0);

// StringDB: the client's texts (master_text), a CMasterParameterBaseSqlite_Simple<StringDBEelement>
// (the table's size and what follows it not recovered: StringDB::SetAddLoadFileName's string). The
// element's text_value is the CParameterPropertyString<32> at +0x80 (its string at +0xa8).
class StringDB {
public:
    // GetNativeString(id, &found) (the string through x8): the element of CHash32(Format("%s_%s", "ja", id))
    // (the language hard-coded: the English mode serves English in the ja_ rows of its own master),
    // text_value decrypted (CParameterPropertyBase<32>::CryptString); not found: the id itself.
    void GetNativeString(params::String* out, const char* id, bool* found);  // _ZN8StringDB15GetNativeStringEPKcPb
    // Get(id, &found): GetNativeString, then every "\\n" (backslash, n) replaced by a newline
    // (CSTLStringUtility_Base::Replace), the result's storage released (clear, reserve(0)) and the
    // replaced string moved in.
    void Get(params::String* out, const char* id, bool* found);  // _ZN8StringDB3GetEPKcPb

    CMasterParameterSimple table;  // 0x00
};

}  // namespace soa::native::master

#endif  // SOA_NATIVE_MASTER_LAYOUT_H
