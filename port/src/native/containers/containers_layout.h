// containers_layout.h: the guest data layouts of the `containers` subsystem (the engine's containers and strings (templates)).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/containers/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types containers` turns the structs into port/decomp/containers/types.json for Ghidra.
#ifndef SOA_NATIVE_CONTAINERS_LAYOUT_H
#define SOA_NATIVE_CONTAINERS_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::containers {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// How to read this file
// ---------------------
// The engine's containers are templates (Aska::T* and Framework::T*), so most classes below are class
// templates. A template has no layout of its own: the `using` aliases at the end of each section name
// the instantiations the guest executes (or that the layout tests drive), and the static_asserts are
// on those. `tools/subsystem.py export-types containers` exports each alias's instantiation under
// clang's name for it (e.g. "TArray<unsigned int, false>").
//
// Element types that belong to other subsystems (Aska::Vector, CMetaInfo, ...) are not declared here;
// a container of them is instantiated with an opaque `Opaque<Size>` where a size is needed.
//
// Inheritance: the guest classes derive from each other (TAddressManager -> THash -> TBinaryTree ->
// TPoolLegacy -> TSmartPointer). A C++ base with data and a derived class with data is not
// standard-layout, so a derived class holds its base as the first member `base` instead; the guest's
// vtable pointer is the first field of the innermost base.
//
// Proven at runtime by port/src/native/containers/containers_layout_test.cpp ("containers/layout-*":
// the guest's own code builds and fills the objects, the host reads them through these classes).

// An element of another subsystem's type, of N bytes (only its size matters to the container).
template <u64 N>
struct Opaque {
    u8 bytes[N];
};

// ---- Strings ----------------------------------------------------------------------------------

// Framework::TStaticString<N>: a fixed char buffer, NUL-terminated, no length field (size N).
// Layout: TStaticString<16>::Set / <32>::Set copy at most N-1 chars to offset 0 and terminate;
// <256>::operator+= copies the concatenation back to offset 0 (strings.c, array_u32.c).
template <u64 N>
class TStaticString {
public:
    void Set(const char* s);                    // _ZN9Framework13TStaticStringILm16EE3SetEPKc (16, 32)
    TStaticString* OpAddAssign(const char* s);  // operator+=(char const*) _ZN9Framework13TStaticStringILm256EEpLEPKc (256; via a temporary CSTL string)

    char m_str[N];  // 0x00
};
using TStaticString16 = TStaticString<16>;
using TStaticString32 = TStaticString<32>;
using TStaticString256 = TStaticString<256>;
static_assert(sizeof(TStaticString16) == 16);
static_assert(sizeof(TStaticString32) == 32);
static_assert(sizeof(TStaticString256) == 256);

// Aska::StringUtility: static helpers only (no object).
class StringUtility {
public:
    static char* SeekStartOfNextLine(char* p);                  // _ZN4Aska13StringUtility19SeekStartOfNextLineEPc
    static const char* SeekStartOfNextLine(const char* p);      // _ZN4Aska13StringUtility19SeekStartOfNextLineEPKc
    static bool CheckForSingleLineComment(const char* p);       // _ZN4Aska13StringUtility25CheckForSingleLineCommentEPKc
    static s64 CopyLine(char* dst, s32 cap, const char* src);   // _ZN4Aska13StringUtility8CopyLineEPciPKc
    static void ConvertFullPathToDirectory(char* dst, s32 cap, const char* path);  // _ZN4Aska13StringUtility26ConvertFullPathToDirectoryEPciPKc
    static void ConvertBinaryToHexBaseAscii(const s8* src, u64 n, char* dst, u32 cap);  // _ZN4Aska13StringUtility27ConvertBinaryToHexBaseAsciiEPKamPcj
    static u64 Utf8ToMultiByte(const char* src, char* dst, u32 cap);  // _ZN4Aska13StringUtility15Utf8ToMultiByteEPKcPcj
};

// Aska::PathUtil: static helpers only (no object).
class PathUtil {
public:
    static const char* GetTailName(const char* path, u64* len);       // _ZN4Aska8PathUtil11GetTailNameEPKcPm
    static const char* GetExtentionName(const char* path, u64* len);  // _ZN4Aska8PathUtil16GetExtentionNameEPKcPm
    static s64 CatenatePathName(const char* a, const char* b, char* dst, u64 cap);  // _ZN4Aska8PathUtil16CatenatePathNameEPKcS2_Pcm
    // CatenatePathName(char const*, char const*) _ZN4Aska8PathUtil16CatenatePathNameEPKcS2_: returns a
    // string object through x8 (write its HostFn by hand).
};

// Framework::CSTLStringUtility_Base<S> (S = the CSTL basic_string, libcxx's layout): static helpers
// over S only (Replace, ReplaceSelf, Format, Split, Substr, GetExtension, IntToString, AToF, IsDigits,
// AToDoubleWithTrimming; strings.c). Most return S through x8. No object layout.

// ---- Small values -----------------------------------------------------------------------------

// Aska::TPair<K, V> (also the THashMap value type TPair<K const, V>).
template <typename K, typename V>
struct TPair {
    K first;
    V second;
};

// Aska::TSharedPointer<T>: {object, shared counter} (Aska::TSharedPointerCode::CreateCounter /
// DeleteCounter allocate the int counter; Release() decrements it atomically and deletes both at 0).
template <typename T>
class TSharedPointer {
public:
    s32 Release();  // _ZN4Aska14TSharedPointerINS_16DecompressStream11DataContextEE7ReleaseEv (tree.c)

    T* m_ptr;          // 0x00
    s32* m_counter;    // 0x08
};
using TSharedPointerBytes = TSharedPointer<u8>;
static_assert(offsetof(TSharedPointerBytes, m_counter) == 0x08);
static_assert(sizeof(TSharedPointerBytes) == 0x10);

// Aska::TDelegate<T>: an object and an Itanium pointer-to-member-function {ptr, adj} (bit 0 of adj:
// ptr is a vtable offset). operator()(void*) (tree.c).
template <typename T>
class TDelegate {
public:
    s64 Call(void* arg);  // operator()(void*) _ZN4Aska9TDelegateINS_18AaoStreamingStreamEEclEPv

    const void* vtable;  // 0x00
    T* m_object;         // 0x08
    u64 m_fn;            // 0x10: function address, or vtable offset when m_adj & 1
    s64 m_adj;           // 0x18: (this adjustment << 1) | virtual
};
using TDelegateOpaque = TDelegate<Opaque<8>>;
static_assert(offsetof(TDelegateOpaque, m_object) == 0x08);
static_assert(offsetof(TDelegateOpaque, m_fn) == 0x10);
static_assert(offsetof(TDelegateOpaque, m_adj) == 0x18);
static_assert(sizeof(TDelegateOpaque) == 0x20);

// ---- Open-addressing hash maps (Aska::THashMap / THashSet) ------------------------------------
//
// The bucket array is an open-addressing table (Aska::detail::THashMapBucketArray<THashMapBucket<P>>):
// each bucket is {u8 state; P value} (state 0 empty, 1 used, 2 deleted). Probing is linear:
// bucket (h + i) % count for i = 0.., with h = THasher<K> (for integer keys, Thomas Wang's 64-bit
// mix, `HashInt` below). operator[] / Insert grow first: when (size + deleted + 1) / maxLoad >
// count, Rehash_(2 * that + 1). Buckets come from Aska::MemoryManagerAdapter::AlignedMalloc(n *
// sizeof(bucket), 8). Layout: THashMap<unsigned, unsigned long>::operator[], Rehash_ (whose stack
// temporary is a whole map: vtable, maxLoad at +0xc = 0.75, size +0x10, deleted +0x14, buckets
// +0x20, count +0x28) and CHandleManager_Base::Initialize's inlined constructor (hash_map.c,
// port/decomp/memory/handles.c).

// THasher<unsigned int> / THasher<unsigned long>: the bucket index base for an integer key.
inline u64 HashInt(u64 key) {
    u64 h = ~key + (key << 21);
    h = (h ^ (h >> 24)) * 265;
    h = (h ^ (h >> 14)) * 21;
    return (h ^ (h >> 28)) * 0x80000001ull;
}

template <typename P>
struct THashMapBucket {
    u8 m_state;  // 0x00: 0 empty, 1 used, 2 deleted
    P m_value;   // at P's alignment (4 for a u32 key set, 8 for TPair<u32, u64>)
};

template <typename B>
struct THashMapBucketArray {
    B* m_data;      // +0x00
    u64 m_count;    // +0x08: number of buckets
};

// The common shape of THashMap and THashSet (V = the bucket's value type: TPair<K, V> or K).
template <typename V>
class THashTable {
public:
    const void* vtable;                                 // 0x00
    u8 m_hasher;                                        // 0x08: THasher<K> (empty)
    u8 m_equal;                                         // 0x09: TEqualTo<K> (empty)
    u8 unk_0a[2];                                       // 0x0a
    float m_maxLoadFactor;                              // 0x0c: 0.75
    u32 m_size;                                         // 0x10: used buckets
    u32 m_deleted;                                      // 0x14: deleted (tombstone) buckets
    u8 m_allocator;                                     // 0x18: TAllocator (empty)
    u8 unk_19[7];                                       // 0x19
    THashMapBucketArray<THashMapBucket<V>> m_buckets;   // 0x20
};

// Aska::THashMap<K, V, THasher<K>, TEqualTo<K>, TAllocator<TPair<K const, V>>>.
template <typename K, typename V>
class THashMap {
public:
    void Dtor();                    // ~THashMap() D2: frees the buckets (AlignedFree), size = 0
    void DtorDelete();              // ~THashMap() D0
    V* OpIndex(const K* key);       // operator[](K const&): inserts a default V when missing
    void Rehash_(u64 count);        // Rehash_(unsigned long)
    // template Insert<THashMapIterator<...>>(first, last): range insert (Rehash_ uses it)

    THashTable<TPair<K, V>> table;  // 0x00
};
using THashMapU32U64 = THashMap<u32, u64>;          // CHandleManager_Base's map (memory)
using THashMapU32U32 = THashMap<u32, u32>;
using THashMapU32Bool = THashMap<u32, bool>;
using THashMapU32Str256 = THashMap<u32, TStaticString<256>>;
static_assert(offsetof(THashMapU32U64, table.m_maxLoadFactor) == 0x0c);
static_assert(offsetof(THashMapU32U64, table.m_size) == 0x10);
static_assert(offsetof(THashMapU32U64, table.m_deleted) == 0x14);
static_assert(offsetof(THashMapU32U64, table.m_buckets.m_data) == 0x20);
static_assert(offsetof(THashMapU32U64, table.m_buckets.m_count) == 0x28);
static_assert(sizeof(THashMapU32U64) == 0x30);
using THashMapBucketU32U64 = THashMapBucket<TPair<u32, u64>>;
static_assert(sizeof(THashMapBucketU32U64) == 0x18);                     // bucket stride (operator[])
static_assert(offsetof(THashMapBucketU32U64, m_value.first) == 0x08);
static_assert(offsetof(THashMapBucketU32U64, m_value.second) == 0x10);  // operator[]'s result

// Aska::THashSet<K, THasher<K>, TEqualTo<K>, TAllocator<K>>: the same table, buckets {state, K}.
template <typename K>
class THashSet {
public:
    void Dtor();               // ~THashSet() D2
    void DtorDelete();         // ~THashSet() D0
    void Rehash_(u64 count);   // Rehash_(unsigned long)
    // template Insert<THashMapIterator<...>>(first, last)

    THashTable<K> table;       // 0x00
};
using THashSetU32 = THashSet<u32>;
static_assert(sizeof(THashSetU32) == 0x30);
using THashMapBucketU32 = THashMapBucket<u32>;
static_assert(sizeof(THashMapBucketU32) == 8);                 // THashSet<unsigned>::Insert: stride 8
static_assert(offsetof(THashMapBucketU32, m_value) == 4);      // key at +4

// ---- The legacy pool / tree / hash family ------------------------------------------------------
//
// Aska::TPoolLegacy<T, false> (a fixed pool of T with a used-bit array) <- TBinaryTree<T> (nodes from
// the pool, else operator new; a bucket table of binary search trees; a doubly linked list of all
// nodes) <- THash<T> (bucket = CalcHashValue(key) % m_tableSize) <- TAddressManager<T> /
// TCategorizeHash<T>. Layout: MappedMemoryManager::MappedMemoryManager's inlined construction of its
// TAddressManager<AddressNode> (vtable TPoolLegacy, SecurePool(n * 4), vtable TBinaryTree, the table:
// new T*[n] or the one inline slot, vtable TAddressManager), TBinaryTree<AddressNode>::AllocNode /
// FreeNode / FreeTable / ~TBinaryTree, TPoolLegacy::SecurePool, THash::Regist,
// TCategorizeHash::Search / GetNext (legacy_tree.c, tree.c, pool.c, hash.c).

// Aska::TBitArray<W, false>.
template <typename W>
class TBitArray {
public:
    bool Alloc(u32 bits, const W* storage);  // _ZN4Aska9TBitArrayIjLb0EE5AllocEjPKj
    void Dtor();                              // ~TBitArray()

    const void* vtable;  // 0x00
    u8 unk_08[8];        // 0x08: never written by the code read
    W* m_bits;           // 0x10
    u32 m_numWords;      // 0x18
    u32 m_numBits;       // 0x1c
    u8 m_ownsBits;       // 0x20: m_bits from new[] (freed by SecurePool / the destructor)
    u8 unk_21[7];        // 0x21
};
using TBitArrayU32 = TBitArray<u32>;
using TBitArrayU64 = TBitArray<u64>;
static_assert(offsetof(TBitArrayU32, m_bits) == 0x10);
static_assert(offsetof(TBitArrayU32, m_numWords) == 0x18);
static_assert(offsetof(TBitArrayU32, m_numBits) == 0x1c);
static_assert(offsetof(TBitArrayU32, m_ownsBits) == 0x20);
static_assert(sizeof(TBitArrayU32) == 0x28);

// Aska::TPoolLegacy<T, false>: T objects in m_pool, bit i of m_used set = slot i taken. A slot is
// taken by a linear scan from m_cursor (wrapping); a full pool falls back to operator new.
template <typename T>
class TPoolLegacy {
public:
    bool SecurePool(u32 count, bool clear, const void* storage, const u32* bits);  // SecurePool(unsigned, bool, void const*, unsigned const*)
    void Dtor();  // ~TPoolLegacy()

    const void* vtable;        // 0x00
    u8 unk_08[8];              // 0x08: zeroed by the inlined constructors (u32 at +8)
    TBitArray<u32> m_used;     // 0x10: m_used.m_numBits = the pool's capacity
    u32 m_cursor;              // 0x38: next slot to try
    u32 m_count;               // 0x3c: slots taken
    T* m_pool;                 // 0x40
    u8 m_ownsPool;             // 0x48: m_pool from new[] (else the caller's storage)
    u8 unk_49[7];              // 0x49
};

// Aska::TBinaryNode<N>: the node of TBinaryTree / THash; N bytes of key at +0x28 (GetKey). Virtuals
// (the node's vtable): +0x10 Init, +0x18 Term, +0x20 Compare(key), +0x28 SetKey(key), +0x30 GetKey.
template <u32 N>
class TBinaryNode {
public:
    void Init();                  // _ZN4Aska11TBinaryNodeILj8EE4InitEv (empty for 8, 16, 24, 32)
    void Term();
    void Dtor();
    const void* GetKey() const;   // returns this + 0x28
    s32 Compare(const void* key);  // TBinaryNode<8>::Compare: strcmp(key, GetKey()) (overridden: AddressNode compares u64s)

    const void* vtable;           // 0x00
    TBinaryNode* m_prev;          // 0x08: the tree's list of all nodes
    TBinaryNode* m_next;          // 0x10
    TBinaryNode* m_left;          // 0x18: Compare(key) < 0 goes here
    TBinaryNode* m_right;         // 0x20: Compare(key) > 0 goes here
    u8 m_key[N];                  // 0x28
};
using TBinaryNode8 = TBinaryNode<8>;
using TBinaryNode16 = TBinaryNode<16>;
using TBinaryNode24 = TBinaryNode<24>;
using TBinaryNode32 = TBinaryNode<32>;
static_assert(offsetof(TBinaryNode8, m_prev) == 0x08);
static_assert(offsetof(TBinaryNode8, m_next) == 0x10);
static_assert(offsetof(TBinaryNode8, m_left) == 0x18);
static_assert(offsetof(TBinaryNode8, m_right) == 0x20);
static_assert(offsetof(TBinaryNode8, m_key) == 0x28);
static_assert(sizeof(TBinaryNode8) == 0x30);  // AddressNode's pool stride

// Aska::AddressNode: TBinaryNode<8> keyed by an address (SetKey copies the u64; Compare: -1 / 0 / 1).
class AddressNode {
public:
    void SetKey(const void* key);   // _ZN4Aska11AddressNode6SetKeyEPKv
    s32 Compare(const void* key);   // _ZN4Aska11AddressNode7CompareEPKv
    void DtorDelete();              // _ZN4Aska11AddressNodeD0Ev

    TBinaryNode<8> base;            // 0x00 (key: the u64 at 0x28)
};
static_assert(sizeof(AddressNode) == 0x30);

// Aska::TBinaryTree<T>: the virtuals used through its vtable: +0x10 AllocNode(key), +0x18
// FreeNode(T**), +0x60 CalcHashValue(key) (THash), +0x68 Regist(key, hash) (THash).
template <typename T>
class TBinaryTree {
public:
    T* AllocNode(const void* key);  // AllocNode(void const*): a pool slot or operator new, appended to the list
    void FreeNode(T** node);        // FreeNode(T**): unlinks, frees its subtrees, returns the slot
    void FreeTable();               // FreeTable()
    T* Regist(const void* key);     // Regist(void const*)
    T* RegistEx(const void* key);
    T* Register(const void* key);
    bool IsRegisted(const void* key);
    bool IsRegistered(const void* key);
    T* Search(const void* key);
    void Remove(const void* key);
    void Remove(T** node);
    void Dtor();                    // ~TBinaryTree()

    TPoolLegacy<T> base;            // 0x00
    T** m_table;                    // 0x50: bucket roots (THash); m_inlineTable when m_tableSize is 1
    u32 m_tableSize;                // 0x58
    u8 unk_5c[4];                   // 0x5c
    T** m_lastSlot;                 // 0x60: the slot the last Regist / Register walked to
    T* m_inlineTable[1];            // 0x68
    T* m_head;                      // 0x70: first node allocated (list by TBinaryNode::m_next)
    T* m_tail;                      // 0x78: last node allocated
    T* m_cursor;                    // 0x80: iteration
    u8 m_iterationDone;             // 0x88
    u8 unk_89[3];                   // 0x89
    u32 m_nodeCount;                // 0x8c
};

// Aska::THash<T>: TBinaryTree with a hashed bucket table. CalcHashValue(key): FNV-1a 32-bit over the
// NUL-terminated key, % m_tableSize (THash<AddressNode>; overridden by TAddressManager).
template <typename T>
class THash {
public:
    T* Regist(const void* key);                 // Regist(void const*) = Regist(key, CalcHashValue(key))
    T* Regist(const void* key, u32 hash);       // Regist(void const*, unsigned)
    T* RegistEx(const void* key);
    bool IsRegisted(const void* key);
    bool IsRegisted(const void* key, u32 hash);
    T* Search(const void* key);
    T* Search(const void* key, u32 hash);
    void Remove(const void* key);
    void Remove(const void* key, u32 hash);
    void Remove(T** node);
    u32 CalcHashValue(const void* key) const;
    void Dtor();                                // ~THash()

    TBinaryTree<T> base;                        // 0x00
};

// Aska::TAddressManager<T>: THash keyed by an address; CalcHashValue folds the 8 key bytes:
// h = ((h % size) * 8 + byte) for each byte, then % size.
template <typename T>
class TAddressManager {
public:
    T* Register(const void* key);               // _ZN4Aska15TAddressManagerINS_11AddressNodeEE8RegisterEPKv
    bool IsRegistered(const void* key);         // _ZN4Aska15TAddressManagerINS_11AddressNodeEE12IsRegisteredEPKv
    u32 CalcHashValue(const void* key) const;   // _ZNK4Aska15TAddressManagerINS_11AddressNodeEE13CalcHashValueEPKv
    void DtorDelete();                          // _ZN4Aska15TAddressManagerINS_11AddressNodeEED0Ev

    THash<T> base;                              // 0x00
};
using TPoolLegacyAddressNode = TPoolLegacy<AddressNode>;
using TBinaryTreeAddressNode = TBinaryTree<AddressNode>;
using THashAddressNode = THash<AddressNode>;
using TAddressManagerAddressNode = TAddressManager<AddressNode>;
static_assert(offsetof(TPoolLegacyAddressNode, m_used) == 0x10);
static_assert(offsetof(TPoolLegacyAddressNode, m_used.m_bits) == 0x20);
static_assert(offsetof(TPoolLegacyAddressNode, m_used.m_numBits) == 0x2c);
static_assert(offsetof(TPoolLegacyAddressNode, m_used.m_ownsBits) == 0x30);
static_assert(offsetof(TPoolLegacyAddressNode, m_cursor) == 0x38);
static_assert(offsetof(TPoolLegacyAddressNode, m_count) == 0x3c);
static_assert(offsetof(TPoolLegacyAddressNode, m_pool) == 0x40);
static_assert(offsetof(TPoolLegacyAddressNode, m_ownsPool) == 0x48);
static_assert(sizeof(TPoolLegacyAddressNode) == 0x50);
static_assert(offsetof(TBinaryTreeAddressNode, m_table) == 0x50);
static_assert(offsetof(TBinaryTreeAddressNode, m_tableSize) == 0x58);
static_assert(offsetof(TBinaryTreeAddressNode, m_lastSlot) == 0x60);
static_assert(offsetof(TBinaryTreeAddressNode, m_inlineTable) == 0x68);
static_assert(offsetof(TBinaryTreeAddressNode, m_head) == 0x70);
static_assert(offsetof(TBinaryTreeAddressNode, m_tail) == 0x78);
static_assert(offsetof(TBinaryTreeAddressNode, m_cursor) == 0x80);
static_assert(offsetof(TBinaryTreeAddressNode, m_iterationDone) == 0x88);
static_assert(offsetof(TBinaryTreeAddressNode, m_nodeCount) == 0x8c);
static_assert(sizeof(TBinaryTreeAddressNode) == 0x90);
static_assert(sizeof(THashAddressNode) == 0x90);
static_assert(sizeof(TAddressManagerAddressNode) == 0x90);  // MappedMemoryManager: next member at +0x90

// Aska::TCategorizeHash<T>: THash whose equal keys chain through the nodes' "category" links (node
// +0x38 previous, +0x40 next: Regist inserts by the node's virtual +0x38 compare; Search walks
// them), plus an iteration state for GetNext.
template <typename T>
class TCategorizeHash {
public:
    T* Regist(const void* key);
    T* Regist(const void* key, u32 hash);
    T* Search(const void* key, u32 hash);
    void Remove(const void* key, u32 hash);
    void Remove(T** node);
    void FreeNode(T** node);
    T* GetNext() const;            // GetNext() const: next node over all buckets; sets m_iterationDone at the end

    THash<T> base;                 // 0x00 (base.base.m_iterationDone at 0x88: iteration finished)
    T* m_iterNode;                 // 0x90
    u32 m_iterBucket;              // 0x98
    u8 unk_9c[4];                  // 0x9c: size not confirmed (no constructor read)
};
using TCategorizeHashOpaque = TCategorizeHash<Opaque<0x48>>;
static_assert(offsetof(TCategorizeHashOpaque, m_iterNode) == 0x90);
static_assert(offsetof(TCategorizeHashOpaque, m_iterBucket) == 0x98);

// ---- Fast pool -------------------------------------------------------------------------------

// Aska::TPoolFast<T, B>: a pool of T with a 64-bit-word used bitmap; Scoop(n) takes n contiguous
// slots (from m_cursor, wrapping), Sink returns them. Layout: SecurePool, Scoop, ~TPoolFast (the
// D2 resets +0x08 to TSmartPointer<false>'s vtable: the bit array is a second base there).
template <typename T>
class TPoolFast {
public:
    bool SecurePool(u32 count, T* storage);   // SecurePool(unsigned int, T*)
    T* Scoop(s32 n);                          // Scoop(int)
    T* Scoop();                               // Scoop()
    void Sink(T* p);                          // Sink(T*)
    void Sink(T* p, s32 n);                   // Sink(T*, int)
    void ReleasePool();
    void Dtor();                              // ~TPoolFast()

    const void* vtable;        // 0x00
    TBitArray<u64> m_used;     // 0x08: m_used.m_numBits = capacity
    T* m_pool;                 // 0x30
    u32 m_cursor;              // 0x38
    u32 m_count;               // 0x3c
    u8 unk_40;                 // 0x40
    u8 m_ownsPool;             // 0x41
    u8 unk_42[6];              // 0x42
};
using TPoolFastVector = TPoolFast<Opaque<16>>;  // TPoolFast<Aska::Vector, false> (math's Vector: 16 bytes)
static_assert(offsetof(TPoolFastVector, m_used.m_bits) == 0x18);
static_assert(offsetof(TPoolFastVector, m_used.m_numWords) == 0x20);
static_assert(offsetof(TPoolFastVector, m_used.m_numBits) == 0x24);
static_assert(offsetof(TPoolFastVector, m_used.m_ownsBits) == 0x28);
static_assert(offsetof(TPoolFastVector, m_pool) == 0x30);
static_assert(offsetof(TPoolFastVector, m_cursor) == 0x38);
static_assert(offsetof(TPoolFastVector, m_count) == 0x3c);
static_assert(offsetof(TPoolFastVector, m_ownsPool) == 0x41);
static_assert(sizeof(TPoolFastVector) == 0x48);

// Aska::TPoolHandler<T>: CreateNode / DeleteNode / AttachPool(TPoolLegacy<T>*) / DetachPool (pool.c);
// layout not recovered.

// ---- Arrays ---------------------------------------------------------------------------------

// Aska::TArray<T, B>: a growable array (new[] storage). Resize(n): grows to 2n when n > capacity
// (the first allocation max(n, m_minCapacity)), shrinks to 2n when n < capacity / 4 and shrinkable;
// Push is Resize(size + 1) then m_data[size] = v. Layout: Resize, the dtors, and the inlined
// constructor in MasterNpcBaseParameterModel::GetParameter (vtable, 0, 0, 0, 0, m_minCapacity = 8, 0;
// size 0x38).
template <typename T, bool B>
class TArray {
public:
    void Resize(s64 n, bool keep);                                // Resize(long, bool)
    void SetAt(s64 i, const T* v);                                // SetAt(long, T const&)
    void Clear();
    // ForceRealloc(long, long, T const*, StBoolean<false>)
    void Dtor();                                                  // ~TArray() D2
    void DtorDelete();                                            // ~TArray() D0

    const void* vtable;    // 0x00
    T* m_data;             // 0x08
    s64 m_capacity;        // 0x10
    s64 m_size;            // 0x18
    s64 unk_20;            // 0x20: zeroed with m_size by Resize(0)
    s64 m_minCapacity;     // 0x28: the first allocation's minimum (8)
    u16 m_flags;           // 0x30: bit 0 = the last allocation failed
    u16 m_flags2;          // 0x32: bit 0 = may shrink / free on Resize(0)
    u8 unk_34[4];          // 0x34
};
using TArrayU32 = TArray<u32, false>;
using TArrayU32B = TArray<u32, true>;
static_assert(offsetof(TArrayU32, m_data) == 0x08);
static_assert(offsetof(TArrayU32, m_capacity) == 0x10);
static_assert(offsetof(TArrayU32, m_size) == 0x18);
static_assert(offsetof(TArrayU32, m_minCapacity) == 0x28);
static_assert(offsetof(TArrayU32, m_flags) == 0x30);
static_assert(offsetof(TArrayU32, m_flags2) == 0x32);
static_assert(sizeof(TArrayU32) == 0x38);

// Aska::TDynamicArray<T, A>: begin / end / capacity-end (std::vector's shape) behind a vtable;
// storage from A (TAllocator: AlignedMalloc; AudioAllocator; TSmallHeapAllocator). Insert_<...>
// (an iterator, n, a filler), Reserve(n), the dtors (AlignedFree when capEnd != begin).
template <typename T>
class TDynamicArray {
public:
    void Reserve(u64 n);   // Reserve(unsigned long)
    // TArrayIterator<...> Insert_<Memory::TUninitializedFillN<T>>(TArrayIterator<...>, unsigned long, ...)
    void Dtor();           // ~TDynamicArray() D2
    void DtorDelete();     // ~TDynamicArray() D0

    const void* vtable;    // 0x00
    T* m_begin;            // 0x08
    T* m_end;              // 0x10
    T* m_capEnd;           // 0x18
};
using TDynamicArrayU32 = TDynamicArray<u32>;
static_assert(offsetof(TDynamicArrayU32, m_begin) == 0x08);
static_assert(offsetof(TDynamicArrayU32, m_end) == 0x10);
static_assert(offsetof(TDynamicArrayU32, m_capEnd) == 0x18);
static_assert(sizeof(TDynamicArrayU32) == 0x20);

// Aska::TStack<T, N>: N elements inline, m_data -> them (or new[] storage when grown); the D2 resets
// m_data to the inline storage and the {capacity, top} pair to {N, -1}.
template <typename T, u32 N>
class TStack {
public:
    bool Push(const T* v);                     // Push(T const&) (TStack<StackItem, 32>)
    bool CopyElement(const T* src, T* dst);    // CopyElement(T const*, T*): *dst = *src, true
    void Dtor();                               // ~TStack() D2
    void DtorDelete();                         // ~TStack() D0

    const void* vtable;   // 0x00
    T m_inline[N];        // 0x08
    T* m_data;
    u32 m_capacity;       // N while inline
    s32 m_top;            // -1 when empty
};
using TStackU32x10 = TStack<u32, 10>;
static_assert(offsetof(TStackU32x10, m_inline) == 0x08);
static_assert(offsetof(TStackU32x10, m_data) == 0x30);
static_assert(offsetof(TStackU32x10, m_capacity) == 0x38);
static_assert(offsetof(TStackU32x10, m_top) == 0x3c);
static_assert(sizeof(TStackU32x10) == 0x40);

// Aska::TList<T> (T derives from Aska::LinkElement {vtable, prev, next}): an intrusive circular list
// whose sentinel is a LinkElement at +0x08. Add appends before the sentinel (Add, Delete, AddTop,
// Insert; arrays.c).
struct LinkElement {
    const void* vtable;     // 0x00
    LinkElement* m_prev;    // 0x08
    LinkElement* m_next;    // 0x10
};
template <typename T>
class TList {
public:
    void Add(T* e);             // Add(T*)
    void AddTop(T* e);          // AddTop(T*)
    void Insert(T* e, T* at);   // Insert(T*, T*)
    void Delete(T* e);          // Delete(T*)

    const void* vtable;         // 0x00
    LinkElement m_sentinel;     // 0x08: m_sentinel.m_prev = last, m_next = first
    s32 m_count;                // 0x20
    u8 unk_24[4];               // 0x24: size not confirmed
};
using TListLink = TList<LinkElement>;
static_assert(offsetof(TListLink, m_sentinel) == 0x08);
static_assert(offsetof(TListLink, m_sentinel.m_prev) == 0x10);
static_assert(offsetof(TListLink, m_count) == 0x20);

// Aska::RingBuffer: a byte FIFO in a circular buffer: PushFront writes at m_front, PopBack reads at
// m_back (both move up, mod m_size; PushBack / PopFront move them down); m_used is updated atomically. Open(size) allocates the buffer as a
// TSharedPointer<u8>; Open(buffer, size) uses the caller's. Layout: Open, Reset, Close, PushFront,
// PopBack, PrivatePeepPushFront / PushBack (ring_buffer.c).
class RingBuffer {
public:
    bool Open(const void* buffer, u64 size);           // _ZN4Aska10RingBuffer4OpenEPKvm
    bool Open(u64 size);                               // _ZN4Aska10RingBuffer4OpenEm
    void Reset();                                      // _ZN4Aska10RingBuffer5ResetEv
    void Close();                                      // _ZN4Aska10RingBuffer5CloseEv
    u64 PushFront(const void* src, u64 n);             // _ZN4Aska10RingBuffer9PushFrontEPKvm
    u64 PopFront(void* dst, u64 n);                    // _ZN4Aska10RingBuffer8PopFrontEPvm
    u64 PushBack(const void* src, u64 n);              // _ZN4Aska10RingBuffer8PushBackEPKvm
    u64 PopBack(void* dst, u64 n);                     // _ZN4Aska10RingBuffer7PopBackEPvm
    u64 PushFront(void** where, u64 n);                // _ZN4Aska10RingBuffer9PushFrontEPPvm (reserve in place)
    u64 PopFront(void** where, u64 n);                 // _ZN4Aska10RingBuffer8PopFrontEPPvm
    u64 PushBack(void** where, u64 n);                 // _ZN4Aska10RingBuffer8PushBackEPPvm
    u64 PopBack(void** where, u64 n);                  // _ZN4Aska10RingBuffer7PopBackEPPvm
    u64 PrivatePeepPushFront(void** where, u64 n) const;  // _ZNK4Aska10RingBuffer20PrivatePeepPushFrontEPPvm
    u64 PrivatePeepPopFront(void** where, u64 n) const;   // _ZNK4Aska10RingBuffer19PrivatePeepPopFrontEPPvm
    u64 PrivatePeepPushBack(void** where, u64 n) const;   // _ZNK4Aska10RingBuffer19PrivatePeepPushBackEPPvm
    u64 PrivatePeepPopBack(void** where, u64 n) const;    // _ZNK4Aska10RingBuffer18PrivatePeepPopBackEPPvm

    TSharedPointer<u8> m_owned;   // 0x00: the buffer Open(size) allocated
    u8* m_buffer;                 // 0x10: 0 = closed
    u64 m_size;                   // 0x18
    u64 m_front;                  // 0x20: write position (PushFront)
    u64 m_back;                   // 0x28: read position (PopBack)
    s32 m_used;                   // 0x30: bytes in the buffer (atomic)
    u8 unk_34[4];                 // 0x34: size not confirmed
};
static_assert(offsetof(RingBuffer, m_buffer) == 0x10);
static_assert(offsetof(RingBuffer, m_size) == 0x18);
static_assert(offsetof(RingBuffer, m_front) == 0x20);
static_assert(offsetof(RingBuffer, m_back) == 0x28);
static_assert(offsetof(RingBuffer, m_used) == 0x30);
static_assert(sizeof(RingBuffer) == 0x38);

// ---- Trees and hierarchies -------------------------------------------------------------------

// Framework::CSTLMap<K, V>: std::__ndk1::map<K, V, less<K>, CSTLAllocator<...>> (libcxx's __tree:
// begin node, the end node's left = root, size; nodes from Framework::CSTLAllocator). Only the copy
// constructor is out of line (tree.c). The node layout is libcxx's.
template <typename K, typename V>
class CSTLMap {
public:
    void CopyCtor(const CSTLMap* other);  // CSTLMap(CSTLMap const&)

    void* m_beginNode;   // 0x00
    void* m_root;        // 0x08: the end node (this + 8) is {left = root}
    u64 m_size;          // 0x10
};
using CSTLMapU32Ptr = CSTLMap<u32, void*>;
static_assert(offsetof(CSTLMapU32Ptr, m_root) == 0x08);
static_assert(offsetof(CSTLMapU32Ptr, m_size) == 0x10);
static_assert(sizeof(CSTLMapU32Ptr) == 0x18);

// Framework::THierarchy<T>: the parent / sibling / child links T derives from (T = CTimeElement,
// Cocos::CCocosNode). DetachSelf(T*) unlinks a node and hands its children to its parent; AddChild
// appends to the parent's child list (tree.c).
template <typename T>
class THierarchy {
public:
    void DetachSelf(T* self);              // DetachSelf(T*)
    void AddChild(T* parent, T* child);    // AddChild(T*, T*)

    const void* vtable;     // 0x00 (T's)
    T* m_parent;            // 0x08
    T* m_nextSibling;       // 0x10
    T* m_firstChild;        // 0x18
    u64 unk_20;             // 0x20: zeroed by DetachSelf
};
using THierarchyOpaque = THierarchy<Opaque<8>>;
static_assert(offsetof(THierarchyOpaque, m_parent) == 0x08);
static_assert(offsetof(THierarchyOpaque, m_nextSibling) == 0x10);
static_assert(offsetof(THierarchyOpaque, m_firstChild) == 0x18);
static_assert(offsetof(THierarchyOpaque, unk_20) == 0x20);

// ---- Not recovered (executed, listed for the code agent) --------------------------------------
// Aska::TPriorityQueue<T, true>: CreateElement / Acquire (arrays.c): an Aska::CriticalSection at
//   +0x08 (sync), a pool of TEventElement<T> (0x58 bytes) whose used bits are at +0xb8 (bit count
//   +0xc4), cursor +0xd0, count +0xd4, the pool +0xd8, "may allocate" flag +0xe9.
// Aska::TMultipleBuffer<true>: CreateBuffer / DeleteBuffer over GpuResources (render).
// TOMQuickSort<RenderableObject, float, 64, 10> / Aska::TArrayQuickSort<Occluder, float, 64, 10>:
//   static Ascend / Descend sorts over T** (no object; scene / render callers).
// Aska::TPoolAtomic<T, N>, TPoolAtomicDynamic<T>, TBarrierSlim, TAddressList: one executed function
//   each (pool.c, "other").

}  // namespace soa::native::containers

#endif  // SOA_NATIVE_CONTAINERS_LAYOUT_H
