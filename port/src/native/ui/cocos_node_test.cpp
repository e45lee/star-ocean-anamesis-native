// Differential test of cocos_node.cpp: CCocosNode::SearchByName, native vs the 3.7.0 guest, on
// private node trees (zeroed 0x230-byte nodes with only the links and the names set: all the
// search reads). In --selftest natives aren't installed: t.call reaches the guest code.
#include <cstring>
#include <string>
#include <vector>

#include "native/common/test.h"
#include "native/ui/cocos_node.h"

using namespace soa;
using namespace soa::native::ui;

namespace {

constexpr const char* kSearchByName =
    "_ZN9Framework5Cocos10CCocosNode12SearchByNameERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_"
    "22CSTLStringAllocatorInfEEEEE";

// A tree of nodes in one block; the names' long buffers come from the guest's STL allocator.
struct Tree {
    std::vector<u8> mem;
    size_t n = 0;
    explicit Tree(size_t count) : mem(count * 0x230 + 16), n(count) {}
    ~Tree() {
        for (size_t i = 0; i < n; i++) node(i)->m_name.destroy();
    }
    CCocosNode* node(size_t i) { return reinterpret_cast<CCocosNode*>(((uintptr_t)mem.data() + 15) / 16 * 16 + i * 0x230); }
    void add_child(CCocosNode* parent, CCocosNode* c) {  // appended, as THierarchy::AddChild does
        c->m_hierarchy.m_parent = parent;
        CCocosNode** link = &parent->m_hierarchy.m_firstChild;
        while (*link) link = &(*link)->m_hierarchy.m_nextSibling;
        *link = c;
    }
};

std::string name_of(TestContext& t, const std::vector<std::string>& pool) { return pool[t.rand_int(0, (int)pool.size() - 1)]; }

// Every query from every start node: the native's node equals the guest's.
void compare(TestContext& t, Tree& tree, const std::vector<std::string>& queries, const char* what, size_t starts) {
    int bad = 0;
    for (size_t s = 0; s < starts; s++) {
        CCocosNode* start = tree.node(s);
        for (const std::string& q : queries) {
            guest::String name;
            name.init(q);
            u64 want = t.call(kSearchByName, {(u64)start, (u64)&name});
            u64 got = (u64)start->SearchByName(name);
            if (got != want && bad++ < 5)
                t.fail("%s: from node %zu, '%s': native %#llx guest %#llx", what, s, q.c_str(), (unsigned long long)got,
                       (unsigned long long)want);
            name.destroy();
        }
    }
}

}  // namespace

NATIVE_TEST("ui/cocos-search-by-name") {
    // Names: short and long (libc++'s long form from 23 chars), empty, duplicates, prefixes.
    const std::vector<std::string> pool = {"", "a", "ab", "play_plate", "play_plate/0", "vanish_plate", "Button_mission",
                                           "ListView_1", "x23456789012345678901_2", "a_long_name_over_the_short_form_limit",
                                           "a_long_name_over_the_short_form_limiu", "all", "list", "banner"};
    std::vector<std::string> queries = pool;
    queries.insert(queries.end(), {"missing", "play_plate/3", "a_long_name_never_used_in_any_node_x", "pla", "a "});

    // A random tree: each node's parent is an earlier node; some nodes unnamed.
    {
        Tree tree(300);
        for (size_t i = 0; i < tree.n; i++) {
            CCocosNode* nd = tree.node(i);
            nd->m_name.init(t.rand_int(0, 9) == 0 ? std::string() : name_of(t, pool));
            if (i) tree.add_child(tree.node(t.rand_int(0, (int)i - 1)), nd);
        }
        compare(t, tree, queries, "random tree", 40);
    }
    // A long sibling list (the guest recurses once per sibling: the shape that overflowed the host
    // stack through the old wrapper), the match near the end, with children on some.
    {
        Tree tree(1500);
        tree.node(0)->m_name.init("root");
        for (size_t i = 1; i < tree.n; i++) {
            CCocosNode* nd = tree.node(i);
            nd->m_name.init(i % 7 == 0 ? std::string("item") : "item_" + std::to_string(i));
            tree.add_child(i % 5 == 0 && i > 5 ? tree.node(i - 1) : tree.node(0), nd);
        }
        std::vector<std::string> q = {"root", "item", "item_1", "item_1499", "item_1498", "item_15", "nothing", ""};
        compare(t, tree, q, "sibling list", 3);
    }
    // A deep chain of first children.
    {
        Tree tree(400);
        for (size_t i = 0; i < tree.n; i++) {
            tree.node(i)->m_name.init("lvl" + std::to_string(i % 50));
            if (i) tree.add_child(tree.node(i - 1), tree.node(i));
        }
        compare(t, tree, {"lvl0", "lvl49", "lvl25", "lvl50", ""}, "child chain", 60);
    }
}
