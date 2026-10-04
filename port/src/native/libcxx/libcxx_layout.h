// libcxx_layout.h: the guest data layouts of the `libcxx` subsystem (the NDK libc++ (std::__ndk1) layouts and out-of-line helpers).
//
// libc++ is not hostable (port/PLAN.md task 6, "Per library"): the game's code inlines the templates
// and embeds std::__ndk1 objects in its own classes, so natives that touch them need the guest's
// layouts byte for byte. These are the NDK r16b libc++ (_LIBCPP_VERSION 6000, ABI version 1: the
// classic string layout, not _LIBCPP_ABI_ALTERNATE_STRING_LAYOUT) layouts on AArch64 LP64, read from
// work/toolchains/android-ndk-r16b/sources/cxx-stl/llvm-libc++/include and checked against the
// decompiles in port/decomp/libcxx/ and the layout tests (libcxx_layout_test.cpp). README.md has the
// evidence for the NDK version and the table of types with their proofs.
//
// Conventions:
//   - class templates mirror libc++'s, flattened: no base classes (standard layout, so offsetof works;
//     libc++'s __compressed_pair with an empty allocator / hasher / comparator takes no bytes, so the
//     members below are exactly the stored ones); node types at namespace scope;
//   - the allocator is not a parameter: the game's allocators are empty (Framework::CSTLAllocator<T,
//     Inf> allocates through Framework::CAssignedMemoryManagerForSTLAllocator, std::allocator through
//     operator new), so every instantiation has the same layout whichever allocator it names;
//   - no C++ virtual: the control blocks' and std::function's vtable pointers are fields, with the
//     slot numbers as constants;
//   - guest out-of-line members are declared as members (bind with NATIVE_METHOD once ported); each
//     names the instantiation whose symbol was decompiled (port/decomp/libcxx/symbols.tsv);
//   - the `using X = T<...>;` aliases at the end are the instantiations exported to Ghidra
//     (tools/subsystem.py export-types).
#ifndef SOA_NATIVE_LIBCXX_LAYOUT_H
#define SOA_NATIVE_LIBCXX_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::libcxx {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// ---- pair ------------------------------------------------------------------------------------------
// std::__ndk1::pair<A, B> (also map's __value_type<K, V> and unordered_map's __hash_value_type<K, V>,
// which wrap exactly one pair<const K, V>).
template <typename A, typename B>
struct pair {
    A first;
    B second;
};

// ---- basic_string ------------------------------------------------------------------------------------
// std::__ndk1::basic_string<C, char_traits<C>, Alloc> (<string>, ABI 1, little endian): 24 bytes, a
// union of the long and the short representation; the low bit of the first byte tells them apart
// (__short_mask = 0x01, __long_mask = 0x1). Short: byte 0 = size << 1, the characters (and the NUL)
// after it, (24 - sizeof(C)) / sizeof(C) of them at most (22 + NUL for char: __min_cap = 23). Long:
// word 0 = the allocation's capacity | 1 (allocations are rounded to 16 bytes: __recommend), word 1 =
// size, word 2 = data. The game's strings are basic_string<char, char_traits<char>,
// Framework::CSTLAllocator<char, Framework::CSTLStringAllocatorInf>>; native/common/guest_std.h's
// guest::String is the same object (static_asserted in libcxx_layout_test.cpp).
template <typename C>
struct string_long_rep {
    u64 cap;   // 0x00: allocated characters (incl. the NUL) | 1
    u64 size;  // 0x08
    C* data;   // 0x10
};

template <typename C>
union string_short_head {
    u8 size;  // size << 1 (low bit clear)
    C lx;     // libc++'s __lx: gives the first character slot's size and alignment (wchar_t: 4 bytes)
};

template <typename C>
struct string_short_rep {
    string_short_head<C> head;              // 0x00
    C data[(24 - sizeof(C)) / sizeof(C)];   // sizeof(C): 1 -> 23 (22 chars + NUL)
};

template <typename C>
union string_rep {
    string_long_rep<C> l;
    string_short_rep<C> s;
    u64 words[3];
};

template <typename C>
class basic_string {
public:
    // Guest out-of-line members (the game's string: _ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE...;
    // port/decomp/libcxx/string.c):
    void reserve(u64 n);                                                         // ...7reserveEm
    void __grow_by(u64 old_cap, u64 delta_cap, u64 old_sz, u64 n_copy, u64 n_del, u64 n_add);  // ...9__grow_byEmmmmmm
    void __grow_by_and_replace(u64 old_cap, u64 delta_cap, u64 old_sz, u64 n_copy, u64 n_del, u64 n_add,
                               const C* s);                                      // ...21__grow_by_and_replaceEmmmmmmPKc
    basic_string* replace(u64 pos, u64 n1, const C* s, u64 n2);                  // ...7replaceEmmPKcm
    basic_string* insert(u64 pos, const C* s);                                   // ...6insertEmPKc
    void Dtor();                                                                 // ...D2Ev

    // Host-side readers of the representation (what the guest inlines).
    static constexpr u64 kMinCap = (24 - sizeof(C)) / sizeof(C);  // __min_cap (incl. the NUL)
    bool is_long() const { return r.s.head.size & 1; }
    u64 size() const { return is_long() ? r.l.size : r.s.head.size >> 1; }
    u64 capacity() const { return is_long() ? (r.l.cap & ~u64(1)) - 1 : kMinCap - 1; }
    const C* data() const { return is_long() ? r.l.data : r.s.data; }

    string_rep<C> r;  // 0x00
};
static_assert(sizeof(basic_string<char>) == 0x18);
static_assert(offsetof(string_long_rep<char>, size) == 0x08 && offsetof(string_long_rep<char>, data) == 0x10);
static_assert(offsetof(string_short_rep<char>, data) == 0x01 && sizeof(string_short_rep<char>) == 0x18);
static_assert(offsetof(string_short_rep<wchar_t>, data) == 0x04 && sizeof(string_short_rep<wchar_t>) == 0x18);

// ---- vector --------------------------------------------------------------------------------------------
// std::__ndk1::vector<T, Alloc> (__vector_base: __begin_, __end_, __end_cap_ = __compressed_pair<T*, Alloc>).
// Growth (__recommend): max(2 * capacity, size + 1), capped at max_size.
template <typename T>
class vector {
public:
    // e.g. vector<basic_string<char, ...CSTLAllocator...>, CSTLAllocator<...CSTLVectorAllocatorInf>>::
    // __push_back_slow_path<basic_string&&> (0x11a929c), reserve (0x13a534c).
    void __push_back_slow_path(T* x);
    void reserve(u64 n);

    u64 size() const { return u64(end_ - begin_); }
    u64 capacity() const { return u64(end_cap_ - begin_); }

    T* begin_;    // 0x00
    T* end_;      // 0x08
    T* end_cap_;  // 0x10
};
static_assert(sizeof(vector<u32>) == 0x18);
static_assert(offsetof(vector<u32>, end_) == 0x08 && offsetof(vector<u32>, end_cap_) == 0x10);

// ---- list ----------------------------------------------------------------------------------------------
// std::__ndk1::list<T, Alloc> (__list_imp: __end_ = the sentinel __list_node_base {__prev_, __next_},
// then __size_alloc_ = __compressed_pair<size_type, Alloc>). Circular: the sentinel is the list
// object itself (an empty list's prev / next point at it). Nodes: {__prev_, __next_, __value_}.
// native/common/guest_std.h's guest::StringList is list<basic_string<char>>.
template <typename T>
struct list_node {
    list_node* prev;  // 0x00
    list_node* next;  // 0x08
    T value;          // 0x10 (for alignof(T) <= 8)
};

template <typename T>
class list {
public:
    // e.g. list<basic_string<char, ...>, CSTLAllocator<..., CSTLListAllocatorInf>>::emplace_back<char const*&>,
    // ::remove(basic_string const&), ::push_back(basic_string const&).
    void push_back(const T* x);
    void remove(const T* x);

    list_node<T>* sentinel() { return reinterpret_cast<list_node<T>*>(this); }

    list_node<T>* prev;  // 0x00: the last node (or the sentinel)
    list_node<T>* next;  // 0x08: the first node (or the sentinel)
    u64 size;            // 0x10
};
static_assert(sizeof(list<u32>) == 0x18 && offsetof(list<u32>, size) == 0x10);
static_assert(offsetof(list_node<u64>, value) == 0x10);

// ---- __tree (map, set, multimap, multiset) ---------------------------------------------------------
// std::__ndk1::__tree<V, Compare, Alloc> (<__tree>): __begin_node_ (the leftmost node, or the end node
// when empty), __pair1_ = __compressed_pair<__tree_end_node, node allocator> (the end node: its __left_
// is the root), __pair3_ = __compressed_pair<size_type, value_compare>. The root's __parent_ is the end
// node. Nodes: __tree_end_node {__left_} <- __tree_node_base {__right_, __parent_, bool __is_black_}
// <- __tree_node {__value_}. map<K, V> = __tree<__value_type<K, V>> = __tree<pair<const K, V>>.
struct tree_node_base {
    tree_node_base* left;    // 0x00 (__tree_end_node::__left_)
    tree_node_base* right;   // 0x08
    tree_node_base* parent;  // 0x10 (an __end_node_pointer: the end node for the root)
    bool is_black;           // 0x18
    u8 pad_19[7];
};
static_assert(sizeof(tree_node_base) == 0x20);
static_assert(offsetof(tree_node_base, right) == 0x08 && offsetof(tree_node_base, parent) == 0x10 &&
              offsetof(tree_node_base, is_black) == 0x18);

// void std::__ndk1::__tree_balance_after_insert<__tree_node_base<void*>*>(root, x)  (0x116045c,
// port/decomp/libcxx/tree.c): a free function template.
void __tree_balance_after_insert(tree_node_base* root, tree_node_base* x);

template <typename V>
struct tree_node {
    tree_node* left;    // 0x00
    tree_node* right;   // 0x08
    tree_node_base* parent;  // 0x10
    bool is_black;      // 0x18
    u8 pad_19[7];
    V value;            // 0x20 (for alignof(V) <= 8 ... 16)
};
using TreeNodeCheck_ = tree_node<pair<u32, u64>>;  // (offsetof is a macro: no commas in its type)
static_assert(offsetof(TreeNodeCheck_, value) == 0x20 && sizeof(TreeNodeCheck_) == 0x30);

template <typename V>
class tree {
public:
    // e.g. __tree<__value_type<unsigned, IParameterProperty*>, ..., CSTLAllocator<..., CSTLMapAllocatorInf>>::
    // __emplace_unique_key_args<unsigned, unsigned, IParameterProperty*&> (0x1160314; returns pair<iterator,
    // bool> in x0 / x1) and ::destroy(node) (0x1161438), port/decomp/libcxx/tree.c.
    void destroy(tree_node<V>* nd);

    tree_node_base* end_node() { return reinterpret_cast<tree_node_base*>(&root); }
    tree_node<V>* begin() { return begin_node; }

    tree_node<V>* begin_node;  // 0x00: leftmost node (== end_node() when empty)
    tree_node<V>* root;        // 0x08: __pair1_.first().__left_ (the end node is this field's address)
    u64 size;                  // 0x10
};
static_assert(sizeof(tree<u32>) == 0x18 && offsetof(tree<u32>, root) == 0x08 && offsetof(tree<u32>, size) == 0x10);

template <typename K, typename V> using map = tree<pair<K, V>>;
template <typename K> using set = tree<K>;

// ---- __hash_table (unordered_map, unordered_set) ---------------------------------------------------
// std::__ndk1::__hash_table<V, Hash, Equal, Alloc> (<__hash_table>): __bucket_list_ = unique_ptr<
// __next_pointer[], __bucket_list_deallocator {bucket count}> (the array, then its size), __p1_ =
// __compressed_pair<__first_node, node allocator> (the before-begin anchor: its __next_ is the first
// node), __p2_ = __compressed_pair<size_type, hasher>, __p3_ = __compressed_pair<float, key_equal>.
// One singly linked list through every node; bucket[i] points at the node BEFORE bucket i's first
// node (the anchor &first for the list head's bucket). Bucket of a hash (__constrain_hash): h & (n-1)
// when n is a power of two, else h % n (h < n: h). std::hash<unsigned>: the value; std::hash<string>:
// __murmur2_or_cityhash<unsigned long, 64> (0x1352ff8). Growth: rehash(max(2n + !pow2(n) (n > 2),
// ceil((size + 1) / max_load_factor))); __next_prime (0x265aba8) for non-power-of-two sizes.
template <typename V>
struct hash_node {
    hash_node* next;  // 0x00
    u64 hash;         // 0x08
    V value;          // 0x10 (for alignof(V) <= 8)
};
using HashNodeCheck_ = hash_node<pair<u32, bool>>;
static_assert(offsetof(HashNodeCheck_, value) == 0x10 && sizeof(HashNodeCheck_) == 0x18);

template <typename V>
class hash_table {
public:
    // e.g. unordered_map<unsigned, bool, ..., CSTLAllocator<..., CSTLUnorderedMapAllocatorInf>>::operator[](unsigned&&)
    // (0x17e59a4) and its __hash_table::__rehash(unsigned long) (0x17f6818), port/decomp/libcxx/hash.c.
    void __rehash(u64 n);

    static u64 constrain_hash(u64 h, u64 n) { return (n & (n - 1)) == 0 ? h & (n - 1) : (h < n ? h : h % n); }

    hash_node<V>** buckets;  // 0x00: each the node before the bucket's first (or &first), or null
    u64 bucket_count;        // 0x08
    hash_node<V>* first;     // 0x10: __p1_.first().__next_ (the anchor is this field's address)
    u64 size;                // 0x18
    float max_load_factor;   // 0x20 (1.0f by default)
    u8 pad_24[4];
};
static_assert(sizeof(hash_table<u32>) == 0x28);
static_assert(offsetof(hash_table<u32>, bucket_count) == 0x08 && offsetof(hash_table<u32>, first) == 0x10 &&
              offsetof(hash_table<u32>, size) == 0x18 && offsetof(hash_table<u32>, max_load_factor) == 0x20);

template <typename K, typename V> using unordered_map = hash_table<pair<K, V>>;
template <typename K> using unordered_set = hash_table<K>;

// ---- shared_ptr / weak_ptr and their control blocks ------------------------------------------------
// std::__ndk1::__shared_count {vtable, long __shared_owners_} <- __shared_weak_count {+ long
// __shared_weak_owners_} (<memory>). The counts are "owners - 1": a fresh block holds 0 / 0 (one
// shared owner, the implicit weak reference); __release_shared runs __on_zero_shared when the count
// goes from 0 to -1, then __release_weak (port/decomp/libcxx/shared_ptr.c: slots +0x10 and +0x20).
// Vtable slots (_ZTV + 0x10): 0 ~D1, 1 ~D0 (deleting), 2 __on_zero_shared, 3 __get_deleter (weak count
// only), 4 __on_zero_shared_weak.
enum SharedCountSlot : u32 {
    kSharedSlotDtor = 0,
    kSharedSlotDeletingDtor = 1,
    kSharedSlotOnZeroShared = 2,
    kSharedSlotGetDeleter = 3,
    kSharedSlotOnZeroSharedWeak = 4,
};

class shared_count {
public:
    void __add_shared();      // _ZNSt6__ndk114__shared_count12__add_sharedEv (0x269537c)
    bool __release_shared();  // _ZNSt6__ndk114__shared_count16__release_sharedEv (0x2695394)

    const void* vtable;   // 0x00
    s64 shared_owners;    // 0x08: owners - 1
};
static_assert(sizeof(shared_count) == 0x10 && offsetof(shared_count, shared_owners) == 0x08);

class shared_weak_count {
public:
    void __add_shared();             // _ZNSt6__ndk119__shared_weak_count12__add_sharedEv (0x26953d8)
    void __add_weak();               // _ZNSt6__ndk119__shared_weak_count10__add_weakEv (0x26953f0)
    void __release_shared();         // _ZNSt6__ndk119__shared_weak_count16__release_sharedEv (0x2695408)
    void __release_weak();           // _ZNSt6__ndk119__shared_weak_count14__release_weakEv (0x269547c)
    shared_weak_count* lock();       // _ZNSt6__ndk119__shared_weak_count4lockEv (0x26954a4): null if expired

    const void* vtable;        // 0x00
    s64 shared_owners;         // 0x08: owners - 1 (-1: expired)
    s64 shared_weak_owners;    // 0x10: weak owners - 1 (+ the shared owners' one)
};
static_assert(sizeof(shared_weak_count) == 0x18);
static_assert(offsetof(shared_weak_count, shared_owners) == 0x08 && offsetof(shared_weak_count, shared_weak_owners) == 0x10);

// make_shared / allocate_shared's block: __shared_ptr_emplace<T, Alloc> {__shared_weak_count,
// __compressed_pair<Alloc, T> __data_} (empty allocator: T right after the counts).
template <typename T>
struct shared_ptr_emplace {
    const void* vtable;      // 0x00
    s64 shared_owners;       // 0x08
    s64 shared_weak_owners;  // 0x10
    T value;                 // 0x18 (for alignof(T) <= 8)
};
static_assert(offsetof(shared_ptr_emplace<u64>, value) == 0x18);

// shared_ptr<T>(T*) / (T*, D)'s block: __shared_ptr_pointer<P, D, A> {__shared_weak_count,
// __compressed_pair<__compressed_pair<P, D>, A> __data_} (empty deleter and allocator: just the pointer).
template <typename P>
struct shared_ptr_pointer {
    const void* vtable;      // 0x00
    s64 shared_owners;       // 0x08
    s64 shared_weak_owners;  // 0x10
    P ptr;                   // 0x18
};
static_assert(sizeof(shared_ptr_pointer<void*>) == 0x20);

template <typename T>
struct shared_ptr {
    T* ptr;                     // 0x00 (__ptr_)
    shared_weak_count* cntrl;   // 0x08 (__cntrl_)
};
template <typename T>
struct weak_ptr {
    T* ptr;                     // 0x00
    shared_weak_count* cntrl;   // 0x08
};
static_assert(sizeof(shared_ptr<void>) == 0x10 && offsetof(shared_ptr<void>, cntrl) == 0x08);

// std::__ndk1::unique_ptr<T, D> with an empty deleter: the pointer.
template <typename T>
struct unique_ptr {
    T* ptr;  // 0x00
};

// ---- function ------------------------------------------------------------------------------------------
// std::__ndk1::function<R(Args...)> (<functional>, libc++ 6: no __value_func yet): aligned_storage<3 *
// sizeof(void*)>::type __buf_, then __base* __f_. aligned_storage<24>'s default alignment is the
// strictest fundamental one, 16 on AArch64 (long double), which rounds the buffer up to 32 bytes: __f_
// is at 0x20 and sizeof is 0x30 (the decompiled __func<function<void(bool, long)>, ...>::__clone reads
// the wrapped function's __f_ at +0x30 = 0x10 + 0x20 and allocates 0x40 for the __func).
// __f_: null when empty, == &__buf_ when the callable is stored inline (it fits in 32 bytes and is
// nothrow-copyable), else a heap __func.
// __function::__base<R(Args...)> vtable slots (_ZTV + 0x10): 0 ~D1, 1 ~D0, 2 __clone() const (new
// copy), 3 __clone(__base*) const (copy into a buffer), 4 destroy(), 5 destroy_deallocate(),
// 6 operator()(Args&&...) (byte offset 0x30), 7 target(type_info const&), 8 target_type().
enum FunctionSlot : u32 {
    kFuncSlotDtor = 0,
    kFuncSlotDeletingDtor = 1,
    kFuncSlotClone = 2,
    kFuncSlotCloneInto = 3,
    kFuncSlotDestroy = 4,
    kFuncSlotDestroyDeallocate = 5,
    kFuncSlotCall = 6,
    kFuncSlotTarget = 7,
    kFuncSlotTargetType = 8,
};

struct function_base {
    const void* const* vtable;  // 0x00: _ZTVNSt6__ndk110__function6__funcI...EE + 0x10
};

// __function::__func<F, Alloc, R(Args...)>: {vtable, __compressed_pair<F, Alloc> __f_} (empty
// allocator: the callable right after the vtable, at its alignment).
template <typename F>
struct func {
    const void* const* vtable;  // 0x00
    F f;                        // 0x08 (alignof(F) <= 8; 0x10 for a wrapped std::function)
};

struct function {
    alignas(16) u8 buf[32];  // 0x00: __buf_ (an inline __func; aligned_storage<24, 16>)
    function_base* f;        // 0x20: __f_
    bool is_inline() const { return f == reinterpret_cast<const function_base*>(buf); }
};
static_assert(sizeof(function) == 0x30 && alignof(function) == 16 && offsetof(function, f) == 0x20);
static_assert(sizeof(func<function>) == 0x40 && offsetof(func<function>, f) == 0x10);  // F aligned 16

// ---- deque (from the NDK header; no guest object checked) ------------------------------------------
// std::__ndk1::deque<T, Alloc> (__deque_base): __map_ = __split_buffer<T*> {__first_, __begin_, __end_,
// __end_cap_}, __start_ (index of the first element), __size_. Blocks of __block_size = sizeof(T) < 256 ?
// 4096 / sizeof(T) : 16 elements.
template <typename T>
struct deque {
    T** map_first;      // 0x00
    T** map_begin;      // 0x08
    T** map_end;        // 0x10
    T** map_end_cap;    // 0x18
    u64 start;          // 0x20
    u64 size;           // 0x28
};
static_assert(sizeof(deque<u32>) == 0x30);

// ---- the instantiations exported to Ghidra -----------------------------------------------------------
using String = basic_string<char>;  // the game's std::string (CSTLAllocator) and std::string alike
using StringRep = string_rep<char>;
using StringLongRep = string_long_rep<char>;
using StringShortRep = string_short_rep<char>;
using VectorU32 = vector<u32>;
using VectorPtr = vector<void*>;
using VectorString = vector<String>;
using ListString = list<String>;
using ListStringNode = list_node<String>;
using MapU32U64 = tree<pair<u32, u64>>;        // also map<unsigned, T*>
using MapU32U64Node = tree_node<pair<u32, u64>>;
using MapStringString = tree<pair<String, String>>;
using MapStringStringNode = tree_node<pair<String, String>>;
using UMapU32U64 = hash_table<pair<u32, u64>>;  // also unordered_map<unsigned, T*>
using UMapU32U64Node = hash_node<pair<u32, u64>>;
using UMapU32Bool = hash_table<pair<u32, bool>>;
using UMapU32BoolNode = hash_node<pair<u32, bool>>;
using UMapStringPtr = hash_table<pair<String, void*>>;
using UMapStringPtrNode = hash_node<pair<String, void*>>;
using SharedPtrVoid = shared_ptr<void>;
using WeakPtrVoid = weak_ptr<void>;
using SharedPtrEmplaceU64 = shared_ptr_emplace<u64>;
using SharedPtrPointerVoid = shared_ptr_pointer<void*>;
using UniquePtrVoid = unique_ptr<void>;
using DequePtr = deque<void*>;
using FuncFunction = func<function>;  // __func<function<...>, allocator, ...>: a function wrapping a function

}  // namespace soa::native::libcxx

#endif  // SOA_NATIVE_LIBCXX_LAYOUT_H
