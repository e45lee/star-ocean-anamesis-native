// IInfoBaseMap<K, T>::DeserializeChild (one body for the maps of gen/info_classes.h INFO_MAP_DESERIALIZERS;
// the decompiles of the CPersonInfo, CSkillInfoArray and CAchievementInfo instantiations): the map is
// emptied (__tree::destroy), then each pair of the document's map gives a key (the container's KeyFromParser,
// vtable slot 4: the key's text through an istringstream) and, when the key is new, a node: a T built by
// its default constructor on the stack (zeroed first, as the guest's memset), moved into a node from the
// STL allocator (Allocate(0x28 + sizeof(T), "...STL_Map.h", 0x21): __construct_node), linked where
// __find_equal puts it and balanced (__tree_balance_after_insert), the temporary destroyed, the node's
// T initialized (slot 2). Then the pair's value, an array or a map, goes to the T's DeserializeArray /
// DeserializeChild (slots 0 / 1). The temporary is never initialized (its maps are empty), so nothing in
// the node points at it (unlike InfoBaseArray<T>::DeserializeArray's: README "Next"). Some instantiations
// call __emplace_unique_key_args, others inline it around __construct_node: the same steps.
//
// Live check (family `info`, run-both): the native, then the original on the same object and document (it
// empties the map and builds it again): the keys and every node's T (info_state) must be what the native
// left.
#include <cstring>
#include <string>
#include <vector>

#include "soaruntime/core/log.h"
#include "native/common/native.h"
#include "native/data_formats/data_formats_layout.h"
#include "native/info/gen/info_addresses.h"
#include "native/info/info_class.h"
#include "native/info/info_guest.h"

namespace soa::native::info {

namespace {

using data_formats::AMap;
using data_formats::AValue;
using Node = libcxx::tree_node_base;

constexpr u32 kSlotKeyFromParser = 4;  // K (const ASON_Pair*): the container's key of a document pair
constexpr u32 kNodeValue = 0x28;       // a node's T (the key at +0x20)

u64 node_key(const Node* n, u32 key_size) {
    auto* p = reinterpret_cast<const u8*>(n) + 0x20;
    if (key_size == 4) {
        u32 k;
        std::memcpy(&k, p, 4);
        return k;
    }
    u64 k;
    std::memcpy(&k, p, 8);
    return k;
}

}  // namespace

// The map's tree (InfoContainer::m_body: begin node, root, size; the end node is the root field).
struct InfoMapTree {
    Node* begin;
    Node* root;
    u64 size;
    Node* end() { return reinterpret_cast<Node*>(&root); }
};

struct InfoMapCode {
    static bool DeserializeChild(const InfoClass& M, InfoContainer* self, const AMap* map);
};

bool InfoMapCode::DeserializeChild(const InfoClass& M, InfoContainer* self, const AMap* map) {
    static const u64 allocate = g::sym("_ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj");
    static const u64 balance = g::sym("_ZNSt6__ndk127__tree_balance_after_insertIPNS_16__tree_node_baseIPvEEEEvT_S5_");
    const InfoClass& T = *M.elem;
    const u32 ks = M.key_size;
    auto* tree = reinterpret_cast<InfoMapTree*>(self->m_body);
    g::call(g::sym(M.fn_destroy), {reinterpret_cast<u64>(tree), reinterpret_cast<u64>(tree->root)});
    tree->begin = tree->end();
    tree->root = nullptr;
    tree->size = 0;
    if (map->m_count == 0) return true;
    std::vector<u8> tmp(T.size + 16);
    u8* temp = reinterpret_cast<u8*>((reinterpret_cast<uintptr_t>(tmp.data()) + 15) & ~uintptr_t(15));
    u32 i = 0;
    do {
        const data_formats::ASON_Pair& pair = map->m_pairs[i];
        u64 key = g::vcall(self, kSlotKeyFromParser, {reinterpret_cast<u64>(&pair)});
        if (ks == 4) key = (u32)key;
        // lower_bound(key), then: equal, or the slot __find_equal gives a new key
        Node* end = tree->end();
        Node* found = end;
        for (Node* n = tree->root; n;) {
            if (node_key(n, ks) < key) {
                n = n->right;
            } else {
                found = n;
                n = n->left;
            }
        }
        u8* value;
        if (found != end && !(key < node_key(found, ks))) {
            value = reinterpret_cast<u8*>(found) + kNodeValue;
        } else {
            std::memset(temp, 0, T.size);
            InfoCode::Ctor(T, temp);
            Node* parent = end;
            Node** slot = &end->left;
            for (Node* n = tree->root; n;) {
                parent = n;
                if (key < node_key(n, ks)) {
                    slot = &n->left;
                    n = n->left;
                } else {  // (greater: a key equal to it was found above)
                    slot = &n->right;
                    n = n->right;
                }
            }
            auto* nd = reinterpret_cast<Node*>(g::call(allocate, {(u64)kNodeValue + T.size, g::at(g::kStlMapH), 0x21}));
            if (!nd) fatal("info: IInfoBaseMap node allocation failed (%s)", M.name);  // (the guest asserts and writes through null)
            std::memcpy(reinterpret_cast<u8*>(nd) + 0x20, &key, ks);
            InfoCode::Move(T, reinterpret_cast<u8*>(nd) + kNodeValue, temp);
            nd->left = nullptr;
            nd->right = nullptr;
            nd->parent = parent;
            *slot = nd;
            if (tree->begin->left) tree->begin = tree->begin->left;
            guest_call(balance, {reinterpret_cast<u64>(tree->root), reinterpret_cast<u64>(*slot)});
            tree->size++;
            InfoCode::Dtor(T, temp);
            value = reinterpret_cast<u8*>(nd) + kNodeValue;
            g::vcall(value, InfoBase::kSlotInitialize, {});
        }
        u32 kind = pair.value.m_kind;
        if (kind == AValue::kArray) g::vcall(value, InfoBase::kSlotDeserializeArray, {reinterpret_cast<u64>(&pair.value.m_body)});
        else if (kind == AValue::kMap) g::vcall(value, InfoBase::kSlotDeserializeChild, {reinterpret_cast<u64>(&pair.value.m_body)});
        i++;
    } while (i < map->m_count);
    return true;
}

namespace {

// The keys and each node's T, in order.
std::vector<u8> map_state(const InfoClass& M, const InfoContainer* self) {
    std::vector<u8> out;
    auto* tree = reinterpret_cast<const InfoMapTree*>(self->m_body);
    const Node* end = reinterpret_cast<const Node*>(&tree->root);
    u64 n = 0;
    for (const Node* nd = tree->begin; nd != end && n <= tree->size; n++) {
        u64 k = node_key(nd, M.key_size);
        out.insert(out.end(), reinterpret_cast<const u8*>(&k), reinterpret_cast<const u8*>(&k) + 8);
        std::vector<u8> s = info_state(*M.elem, reinterpret_cast<const u8*>(nd) + kNodeValue);
        out.insert(out.end(), s.begin(), s.end());
        if (nd->right) {
            nd = nd->right;
            while (nd->left) nd = nd->left;
        } else {
            while (nd->parent->left != nd) nd = nd->parent;
            nd = nd->parent;
        }
    }
    out.insert(out.end(), reinterpret_cast<const u8*>(&tree->size), reinterpret_cast<const u8*>(&tree->size) + 8);
    return out;
}

template <const InfoClass* M>
struct MapFn {
    static inline Fn* fn = nullptr;
    static void host(Cpu& c) {
        auto* self = reinterpret_cast<InfoContainer*>(c.x(0));
        auto* map = reinterpret_cast<const AMap*>(c.x(1));
        if (!map) {  // (the guest asserts, then reads address 8)
            c.set_x(0, guest_call(fn->orig, {c.x(0), 0}));
            return;
        }
        bool r = InfoMapCode::DeserializeChild(*M, self, map);
        if (fam().due(*fn)) {
            live::RunBothFamily::Scope scope;
            std::vector<u8> n = map_state(*M, self);
            bool g = guest_call(fn->orig, {c.x(0), c.x(1)}) & 1;
            std::vector<u8> after = map_state(*M, self);
            bool ok = g == r && n == after;
            fam().result(*fn, ok ? Outcome::Ok : Outcome::Mismatch,
                         ok ? "" : std::string(M->name) + ": the map differs after the original's run (" + std::to_string(n.size()) + " / " +
                                       std::to_string(after.size()) + " bytes)");
        }
        c.set_x(0, r);
    }
    static bool bind(const char* sym) {
        fn = new Fn(fam(), sym);  // (lives as long as the process: the registry keeps &fn->orig)
        static const std::string note = std::string("info: IInfoBaseMap DeserializeChild (") + M->name + ")";
        register_native_function({sym, &host, note.c_str(), nullptr, &fn->orig, nullptr, "InfoMapCode::DeserializeChild"});
        return true;
    }
};

#define INFO_BIND_MAP(C, SYM) [[maybe_unused]] const bool NATIVE_CONCAT(info_map_, C) = MapFn<&kInfo_##C>::bind(SYM);
INFO_MAP_DESERIALIZERS(INFO_BIND_MAP)
#undef INFO_BIND_MAP

}  // namespace

// For the differential test (info_map_test.cpp).
bool info_map_deserialize_child(const InfoClass& M, void* self, const void* map) {
    return InfoMapCode::DeserializeChild(M, reinterpret_cast<InfoContainer*>(self), reinterpret_cast<const AMap*>(map));
}
std::vector<u8> info_map_state(const InfoClass& M, const void* self) { return map_state(M, reinterpret_cast<const InfoContainer*>(self)); }

}  // namespace soa::native::info
