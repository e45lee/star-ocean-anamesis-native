// Layout tests for libcxx_layout.h: the guest's own out-of-line libc++ members (3.7.0 lib, natives
// not installed in --selftest) run on objects laid out with the recovered structs, and the results
// are read back through the structs' fields. A wrong offset shows up as a wrong size / link / value,
// or as the guest following a garbage pointer.
//
// Objects live in host memory (identity-mapped for the guest); everything the guest allocates comes
// from the game's STL allocator and is given back through the guest's own members (remove, destroy,
// ~basic_string, destroy_deallocate) or guest::stl_free, the allocator they used
// (Framework::CAssignedMemoryManagerForSTLAllocator: port/decomp/libcxx/*.c).
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "native/libcxx/libcxx_layout.h"

namespace soa {
namespace {

namespace lx = soa::native::libcxx;
using U32Bool = lx::pair<u32, bool>;

static_assert(sizeof(guest::String) == sizeof(lx::String), "guest_std.h's String is basic_string<char>");
static_assert(sizeof(guest::StringList) == sizeof(lx::ListString), "guest_std.h's StringList is list<String>");
static_assert(sizeof(guest::StringList::Node) == sizeof(lx::ListStringNode));

// The game's string: basic_string<char, char_traits<char>, Framework::CSTLAllocator<char, CSTLStringAllocatorInf>>.
constexpr const char* kStrReserve = "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE7reserveEm";
constexpr const char* kStrInsert = "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE6insertEmPKc";
constexpr const char* kStrReplace = "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEE7replaceEmmPKcm";
constexpr const char* kStrDtor = "_ZNSt6__ndk112basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS3_22CSTLStringAllocatorInfEEEED2Ev";

std::string view(const lx::String& s) { return std::string(s.data(), s.size()); }

// The string's invariants, through the struct: the NUL after the characters; a long string's
// capacity word is odd, its allocation a multiple of 16 and larger than the size; a short one's size
// fits the 22 inline characters.
void check_string(TestContext& t, const lx::String& s, const std::string& want, const char* what) {
    if (view(s) != want) t.fail("%s: \"%s\" read through the struct, want \"%s\"", what, view(s).c_str(), want.c_str());
    if (s.data()[s.size()] != 0) t.fail("%s: no NUL after the characters", what);
    if (s.is_long()) {
        u64 alloc = s.r.l.cap & ~u64(1);
        if (alloc % 16 || alloc <= s.r.l.size) t.fail("%s: long capacity word %#llx, size %llu", what, (unsigned long long)s.r.l.cap, (unsigned long long)s.r.l.size);
    } else if (s.r.s.head.size >> 1 > 22) {
        t.fail("%s: short size %u", what, s.r.s.head.size >> 1);
    }
    // the same object as guest_std.h reads it
    const auto* g = reinterpret_cast<const guest::String*>(&s);
    if (g->view() != want) t.fail("%s: guest::String reads \"%s\"", what, g->str().c_str());
}

NATIVE_TEST("libcxx/layout-string") {
    alignas(8) lx::String s{};
    std::memset(&s, 0, sizeof s);
    check_string(t, s, "", "empty");
    t.call(kStrInsert, {(u64)&s, 0, (u64)"hello"});
    t.expect_eq(s.is_long(), false, "short after insert");
    t.expect_eq((u32)s.r.s.head.size, 10u, "short size byte = size << 1");
    check_string(t, s, "hello", "insert short");
    std::string longer = "hello, a string longer than the 22 characters a short one holds";
    t.call(kStrInsert, {(u64)&s, 5, (u64)(longer.c_str() + 5)});
    t.expect_eq(s.is_long(), true, "long after insert");
    check_string(t, s, longer, "insert long");
    t.call(kStrReplace, {(u64)&s, 0, 5, (u64)"HELLO", 5});
    check_string(t, s, "HELLO" + longer.substr(5), "replace");
    t.call(kStrReserve, {(u64)&s, 300});
    if (s.capacity() < 300) t.fail("reserve(300): capacity %llu", (unsigned long long)s.capacity());
    check_string(t, s, "HELLO" + longer.substr(5), "reserve keeps the characters");
    t.call(kStrDtor, {(u64)&s});  // frees the long buffer through the game's allocator

    // reserve on an empty short string goes long with size 0
    std::memset(&s, 0, sizeof s);
    t.call(kStrReserve, {(u64)&s, 100});
    t.expect_eq(s.is_long(), true, "reserve(100) is long");
    t.expect_eq(s.size(), (u64)0, "reserve(100) size");
    if (s.capacity() < 100) t.fail("reserve(100): capacity %llu", (unsigned long long)s.capacity());
    check_string(t, s, "", "reserve empty");
    t.call(kStrDtor, {(u64)&s});
}

// vector<String, CSTLAllocator<..., CSTLVectorAllocatorInf>>::__push_back_slow_path<String>(String&&):
// reallocates to max(2 * capacity, size + 1) and moves the elements.
NATIVE_TEST("libcxx/layout-vector") {
    const char* slow = "_ZNSt6__ndk16vectorINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS5_IS8_NS4_22CSTLVectorAllocatorInfEEEE21__push_back_slow_pathIS8_EEvOT_";
    lx::VectorString v{};
    std::vector<std::string> want;
    u64 cap = 0;
    for (int i = 0; i < 9; i++) {
        std::string text = (i & 1) ? "element " + std::to_string(i) + " which is long enough for the heap" : "e" + std::to_string(i);
        guest::String g;
        g.init(text);
        t.call(slow, {(u64)&v, (u64)&g});
        want.push_back(text);
        cap = std::max(2 * cap, (u64)want.size());
        t.expect_eq(v.size(), (u64)want.size(), "vector size");
        t.expect_eq(v.capacity(), cap, "vector capacity (2x growth)");
        // (the guest copies the source instead of moving it: the decompile allocates a new character
        // buffer for a long source, port/decomp/libcxx/vector_list_function.c; Framework::CSTLAllocator's
        // construct takes a const T&, most likely. So the source keeps its characters and is freed here.)
        if (g.view() != text) t.fail("element %d: the source string changed", i);
        g.destroy();
    }
    for (size_t i = 0; i < want.size(); i++) check_string(t, v.begin_[i], want[i], "vector element");
    for (size_t i = 0; i < want.size(); i++) reinterpret_cast<guest::String*>(&v.begin_[i])->destroy();
    guest::stl_free(v.begin_);
}

// list<String, CSTLAllocator<..., CSTLListAllocatorInf>>::emplace_back<char const*&> / remove(String const&).
NATIVE_TEST("libcxx/layout-list") {
    const char* emplace = "_ZNSt6__ndk14listINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS5_IS8_NS4_20CSTLListAllocatorInfEEEE12emplace_backIJRPKcEEEvDpOT_";
    const char* remove = "_ZNSt6__ndk14listINS_12basic_stringIcNS_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEENS5_IS8_NS4_20CSTLListAllocatorInfEEEE6removeERKS8_";
    lx::ListString l;
    l.prev = l.next = l.sentinel();
    l.size = 0;
    std::vector<std::string> want = {"alpha", "a node value long enough to be a long string", "gamma", "delta"};
    for (auto& w : want) {
        const char* p = w.c_str();
        t.call(emplace, {(u64)&l, (u64)&p});
    }
    t.expect_eq(l.size, (u64)want.size(), "list size");
    size_t i = 0;
    for (auto* n = l.next; n != l.sentinel() && i < 16; n = n->next, i++) {
        if (i < want.size()) check_string(t, n->value, want[i], "list node value");
        if (n->next->prev != n) t.fail("list node %zu: next->prev isn't the node", i);
    }
    t.expect_eq(i, want.size(), "nodes from next to the sentinel");
    t.expect_eq((u64)l.prev->next, (u64)l.sentinel(), "the last node's next is the sentinel");
    // the same list through guest_std.h
    std::vector<std::string> seen;
    reinterpret_cast<guest::StringList*>(&l)->for_each([&](const guest::String& s) { seen.push_back(s.str()); });
    t.expect_eq(seen == want, true, "guest::StringList walk");
    for (auto& w : want) {
        guest::String key;
        key.init(w);
        t.call(remove, {(u64)&l, (u64)&key});
        key.destroy();
    }
    t.expect_eq(l.size, (u64)0, "list empty after remove");
    t.expect_eq((u64)l.next, (u64)l.sentinel(), "empty list's next is the sentinel");
    t.expect_eq((u64)l.prev, (u64)l.sentinel(), "empty list's prev is the sentinel");
}

// Red-black invariants of a tree read through tree_node: the black height, or -1 on a violation.
int black_height(TestContext& t, const lx::MapU32U64Node* n, const lx::tree_node_base* parent, int depth) {
    if (!n) return 1;
    if (depth > 64) { t.fail("tree deeper than 64"); return -1; }
    if (n->parent != parent) { t.fail("node %u: parent link", n->value.first); return -1; }
    if (!n->is_black && ((n->left && !n->left->is_black) || (n->right && !n->right->is_black))) {
        t.fail("node %u: a red node with a red child", n->value.first);
        return -1;
    }
    if (n->left && !(n->left->value.first < n->value.first)) t.fail("node %u: left child not smaller", n->value.first);
    if (n->right && !(n->value.first < n->right->value.first)) t.fail("node %u: right child not larger", n->value.first);
    auto* self = reinterpret_cast<const lx::tree_node_base*>(n);
    int l = black_height(t, n->left, self, depth + 1), r = black_height(t, n->right, self, depth + 1);
    if (l < 0 || r < 0) return -1;
    if (l != r) { t.fail("node %u: black heights %d / %d", n->value.first, l, r); return -1; }
    return l + (n->is_black ? 1 : 0);
}

void inorder(const lx::MapU32U64Node* n, std::vector<std::pair<u32, u64>>& out) {
    if (!n) return;
    inorder(n->left, out);
    out.push_back({n->value.first, n->value.second});
    inorder(n->right, out);
}

// map<unsigned, IParameterProperty*, less, CSTLAllocator<..., CSTLMapAllocatorInf>>: __tree::
// __emplace_unique_key_args<unsigned, unsigned, IParameterProperty*&> (which runs
// __tree_balance_after_insert) and __tree::destroy(node).
NATIVE_TEST("libcxx/layout-tree") {
    const char* emplace = "_ZNSt6__ndk16__treeINS_12__value_typeIjP18IParameterPropertyEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE25__emplace_unique_key_argsIjJjRS3_EEENS_4pairINS_15__tree_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbEERKT_DpOT0_";
    const char* destroy = "_ZNSt6__ndk16__treeINS_12__value_typeIjP18IParameterPropertyEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE7destroyEPNS_11__tree_nodeIS4_PvEE";
    lx::MapU32U64 m;
    m.root = nullptr;
    m.begin_node = reinterpret_cast<lx::MapU32U64Node*>(m.end_node());
    m.size = 0;
    std::map<u32, u64> want;
    for (int i = 0; i < 300; i++) {
        u32 key = (u32)t.rand_int(0, 999);
        u32 key2 = key;
        u64 value = t.rand_u64();
        bool fresh = !want.count(key);
        if (fresh) want[key] = value;
        GuestResult r = t.call(emplace, GuestArgs().p(&m).p(&key).p(&key2).p(&value));
        auto* node = reinterpret_cast<lx::MapU32U64Node*>(r.x0);
        if ((r.x1 & 1) != (u64)fresh) t.fail("key %u: inserted flag %llu", key, (unsigned long long)(r.x1 & 1));
        if (!node || node->value.first != key) t.fail("key %u: returned node", key);
    }
    t.expect_eq(m.size, (u64)want.size(), "tree size");
    std::vector<std::pair<u32, u64>> got;
    inorder(m.root, got);
    t.expect_eq(got == std::vector<std::pair<u32, u64>>(want.begin(), want.end()), true, "in-order keys and values");
    if (!m.root || !m.root->is_black) t.fail("root missing or red");
    if (m.root && m.root->parent != m.end_node()) t.fail("the root's parent isn't the end node");
    const lx::MapU32U64Node* leftmost = m.root;
    while (leftmost && leftmost->left) leftmost = leftmost->left;
    t.expect_eq((u64)m.begin_node, (u64)leftmost, "begin_node is the leftmost node");
    black_height(t, m.root, m.end_node(), 0);
    t.call(destroy, {(u64)&m, (u64)m.root});
}

// unordered_map<unsigned, bool, ..., CSTLAllocator<..., CSTLUnorderedMapAllocatorInf>>::operator[](unsigned&&)
// (which rehashes through __hash_table::__rehash).
NATIVE_TEST("libcxx/layout-hash") {
    const char* index = "_ZNSt6__ndk113unordered_mapIjbNS_4hashIjEENS_8equal_toIjEEN9Framework13CSTLAllocatorINS_4pairIKjbEENS5_28CSTLUnorderedMapAllocatorInfEEEEixEOj";
    lx::UMapU32Bool h{};
    h.max_load_factor = 1.0f;
    std::map<u32, bool> want;
    for (int i = 0; i < 400; i++) {
        u32 key = (u32)t.rand_int(0, 1999);
        u32 arg = key;
        bool* slot = (bool*)t.call(index, {(u64)&h, (u64)&arg});
        if (!want.count(key)) {
            if (*slot) t.fail("key %u: a new value isn't value-initialised", key);
            *slot = key & 1;
            want[key] = key & 1;
        }
        // the returned reference is the node's mapped value
        auto* node = reinterpret_cast<lx::UMapU32BoolNode*>((u8*)slot - offsetof(lx::UMapU32BoolNode, value) -
                                                            offsetof(U32Bool, second));
        if (node->value.first != key || node->hash != key) t.fail("key %u: node key %u hash %llu", key, node->value.first, (unsigned long long)node->hash);
    }
    t.expect_eq(h.size, (u64)want.size(), "hash size");
    if (h.bucket_count == 0 || (float)h.size > h.max_load_factor * (float)h.bucket_count) t.fail("load factor: %llu in %llu buckets", (unsigned long long)h.size, (unsigned long long)h.bucket_count);
    // one list through every node; bucket[b] is the node before b's first node (the anchor for the head)
    std::map<u32, bool> got;
    auto* anchor = reinterpret_cast<lx::UMapU32BoolNode*>(&h.first);
    lx::UMapU32BoolNode* prev = anchor;
    std::set<u64> started;
    for (auto* n = h.first; n && got.size() <= want.size(); prev = n, n = n->next) {
        got[n->value.first] = n->value.second;
        u64 b = h.constrain_hash(n->hash, h.bucket_count);
        bool first_in_bucket = prev == anchor || h.constrain_hash(prev->hash, h.bucket_count) != b;
        if (first_in_bucket) {
            if (started.count(b)) t.fail("bucket %llu's nodes aren't contiguous", (unsigned long long)b);
            started.insert(b);
            if (h.buckets[b] != prev) t.fail("bucket %llu doesn't point at the node before its first", (unsigned long long)b);
        }
    }
    t.expect_eq(got == want, true, "nodes from first: keys and values");
    for (u64 b = 0; b < h.bucket_count; b++)
        if (!started.count(b) && h.buckets[b]) t.fail("empty bucket %llu isn't null", (unsigned long long)b);
    for (auto* n = h.first; n;) {
        auto* next = n->next;
        guest::stl_free(n);
        n = next;
    }
    guest::stl_free(h.buckets);
}

// __shared_count / __shared_weak_count's out-of-line counters on a control block, and the
// __shared_ptr_emplace vtable's slot order.
NATIVE_TEST("libcxx/layout-shared-ptr") {
    static const u64 fake_vtable[8] = {};  // never called: the counts never reach -1 below
    lx::shared_weak_count c{fake_vtable, 0, 0};
    t.call("_ZNSt6__ndk119__shared_weak_count12__add_sharedEv", {(u64)&c});
    t.expect_eq(c.shared_owners, (s64)1, "__add_shared -> shared_owners");
    t.call("_ZNSt6__ndk119__shared_weak_count10__add_weakEv", {(u64)&c});
    t.expect_eq(c.shared_weak_owners, (s64)1, "__add_weak -> shared_weak_owners");
    t.expect_eq(t.call("_ZNSt6__ndk119__shared_weak_count4lockEv", {(u64)&c}), (u64)&c, "lock() on a live block");
    t.expect_eq(c.shared_owners, (s64)2, "lock -> shared_owners");
    t.call("_ZNSt6__ndk119__shared_weak_count16__release_sharedEv", {(u64)&c});
    t.call("_ZNSt6__ndk119__shared_weak_count16__release_sharedEv", {(u64)&c});
    t.expect_eq(c.shared_owners, (s64)0, "__release_shared x2");
    t.call("_ZNSt6__ndk119__shared_weak_count14__release_weakEv", {(u64)&c});
    t.expect_eq(c.shared_weak_owners, (s64)0, "__release_weak");
    c.shared_owners = -1;  // expired
    t.expect_eq(t.call("_ZNSt6__ndk119__shared_weak_count4lockEv", {(u64)&c}), (u64)0, "lock() on an expired block");
    lx::shared_count sc{fake_vtable, 0};
    t.call("_ZNSt6__ndk114__shared_count12__add_sharedEv", {(u64)&sc});
    t.expect_eq((u32)(t.call("_ZNSt6__ndk114__shared_count16__release_sharedEv", {(u64)&sc}) & 0xff), 0u, "__release_shared 1 -> 0 returns false");
    t.expect_eq(sc.shared_owners, (s64)0, "shared_count owners");

#define EMPL "_ZNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EE"
    auto* vt = (const u64*)(t.sym("_ZTVNSt6__ndk120__shared_ptr_emplaceI16StringDBEelement16BAS_STLAllocatorIS1_EEE") + 0x10);
    t.expect_eq(vt[lx::kSharedSlotDtor], t.sym(EMPL "D2Ev"), "slot 0: ~__shared_ptr_emplace");
    t.expect_eq(vt[lx::kSharedSlotDeletingDtor], t.sym(EMPL "D0Ev"), "slot 1: deleting dtor");
    t.expect_eq(vt[lx::kSharedSlotOnZeroShared], t.sym(EMPL "16__on_zero_sharedEv"), "slot 2: __on_zero_shared");
    t.expect_eq(vt[lx::kSharedSlotOnZeroSharedWeak], t.sym(EMPL "21__on_zero_shared_weakEv"), "slot 4: __on_zero_shared_weak");
#undef EMPL
}

// __function::__func<function<void(bool, long)>, allocator, void(bool, unsigned long)>: the vtable's
// slot order, and __clone(__base*) on a __func whose wrapped function holds a heap __func (so the
// clone follows the wrapped function's __f_ at func + 0x10 + 0x20 and calls its slot 2, __clone()).
NATIVE_TEST("libcxx/layout-function") {
#define FUNC "St6__ndk110__function6__funcINS_8functionIFvblEEENS_9allocatorIS4_EEFvbmEE"
    auto* vt = (const void* const*)(t.sym("_ZTVN" FUNC "E") + 0x10);
    struct { lx::FunctionSlot slot; const char* sym; } slots[] = {
        {lx::kFuncSlotDtor, "_ZN" FUNC "D2Ev"},
        {lx::kFuncSlotDeletingDtor, "_ZN" FUNC "D0Ev"},
        {lx::kFuncSlotClone, "_ZNK" FUNC "7__cloneEv"},
        {lx::kFuncSlotCloneInto, "_ZNK" FUNC "7__cloneEPNS0_6__baseIS7_EE"},
        {lx::kFuncSlotDestroy, "_ZN" FUNC "7destroyEv"},
        {lx::kFuncSlotDestroyDeallocate, "_ZN" FUNC "18destroy_deallocateEv"},
        {lx::kFuncSlotCall, "_ZN" FUNC "clEObOm"},
        {lx::kFuncSlotTarget, "_ZNK" FUNC "6targetERKSt9type_info"},
        {lx::kFuncSlotTargetType, "_ZNK" FUNC "11target_typeEv"},
    };
    for (auto& s : slots)
        if ((u64)vt[s.slot] != t.sym(s.sym)) t.fail("vtable slot %u isn't %s", (unsigned)s.slot, s.sym);

    // inner: a __func wrapping an empty function; outer: one wrapping a function whose __f_ is inner (heap form)
    alignas(16) lx::FuncFunction inner{}, outer{}, copy{};
    inner.vtable = (const void* const*)vt;
    inner.f.f = nullptr;
    outer.vtable = (const void* const*)vt;
    outer.f.f = reinterpret_cast<lx::function_base*>(&inner);
    std::memset(&copy, 0xcd, sizeof copy);
    t.call("_ZNK" FUNC "7__cloneEPNS0_6__baseIS7_EE", {(u64)&outer, (u64)&copy});
    t.expect_eq((u64)copy.vtable, (u64)vt, "clone's vtable");
    auto* made = reinterpret_cast<lx::FuncFunction*>(copy.f.f);
    if (!made || made == &inner || copy.f.is_inline()) {
        t.fail("clone's wrapped function: __f_ %p isn't a new heap __func", (void*)made);
        return;
    }
    t.expect_eq((u64)made->vtable, (u64)vt, "the heap copy's vtable");
    t.expect_eq((u64)made->f.f, (u64)0, "the heap copy wraps an empty function");
    // empty: __f_ null in the copy
    alignas(16) lx::FuncFunction copy2{};
    std::memset(&copy2, 0xcd, sizeof copy2);
    t.call("_ZNK" FUNC "7__cloneEPNS0_6__baseIS7_EE", {(u64)&inner, (u64)&copy2});
    t.expect_eq((u64)copy2.f.f, (u64)0, "clone of an empty wrapped function");
    // free the heap copy through its own slot 5 (destroy_deallocate: ~function, then operator delete)
    t.call("_ZN" FUNC "18destroy_deallocateEv", {(u64)made});
#undef FUNC
}

}  // namespace
}  // namespace soa
