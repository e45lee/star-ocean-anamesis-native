// Comparing two runs' elements and maps; copies of maps (master_compare.h).
#include "native/master/master_compare.h"

#include <cstring>
#include <unordered_map>

#include "native/params/params_check.h"

namespace soa::native::master {

// Field by field (the padding is whatever the allocator left: not compared): the element's vtable and
// list head, each property's vtable, m_next, m_named, hash and value (sizeof(T)) or string.
std::string cmp_element(const ElementInfo& I, const u8* a, const u8* b) {
    if (!a || !b) return (!a && !b) ? "" : "one element missing";
    auto same = [&](u32 at, u32 n) { return std::memcmp(a + at, b + at, n) == 0; };
    auto both_set = [&](u32 at) {
        u64 x, y;
        std::memcpy(&x, a + at, 8), std::memcpy(&y, b + at, 8);
        return (x != 0) == (y != 0);
    };
    if (!same(0, 8) || !both_set(8)) return "element head";
    for (const ElementProp& d : I.props) {
        u32 o = d.offset;
        std::string at = " of +" + std::to_string(o);
        if (!same(o, 8)) return "vtable" + at;
        if (!both_set(o + 8)) return "m_next" + at;
        if (!same(o + 0x10, 1)) return "m_named" + at;
        if (!same(o + 0x18, 8) || !same(o + 0x20, 4)) return "m_name" + at;
        if (d.kind == PropKind::kString) {
            std::string why = params::diff_strings(string_property(a, d)->m_value, string_property(b, d)->m_value);
            if (!why.empty()) return "string" + at + ": " + why;
        } else if (d.link >= 0 && !same(o + 0x28, value_width(d.kind))) {  // (an unnamed one is never written)
            return "value" + at;
        }
    }
    return {};
}

std::string cmp_map(const ElementInfo& I, U32Map& a, U32Map& b, bool shared) {
    char m[160];
    if ((a.buckets == nullptr) != (b.buckets == nullptr) || a.size != b.size || a.bucket_count != b.bucket_count || a.max_load_factor != b.max_load_factor) {
        snprintf(m, sizeof m, "size %llu/%llu buckets %llu/%llu", (unsigned long long)a.size, (unsigned long long)b.size,
                 (unsigned long long)a.bucket_count, (unsigned long long)b.bucket_count);
        return m;
    }
    for (u64 i = 0; a.buckets && b.buckets && i < a.bucket_count; i++)
        if ((a.buckets[i] != nullptr) != (b.buckets[i] != nullptr)) return "bucket " + std::to_string(i);
    U32Node *x = a.first, *y = b.first;
    for (; x && y; x = x->next, y = y->next) {
        if (x->key != y->key || x->hash != y->hash) return "key order";
        const u8* ex = shared ? reinterpret_cast<SharedPtr*>(x->value())->ptr : x->value();
        const u8* ey = shared ? reinterpret_cast<SharedPtr*>(y->value())->ptr : y->value();
        std::string why = cmp_element(I, ex, ey);
        if (!why.empty()) return "key " + std::to_string(x->key) + ": " + why;
        if (shared) {
            auto* cx = reinterpret_cast<SharedPtr*>(x->value())->ctrl;
            auto* cy = reinterpret_cast<SharedPtr*>(y->value())->ctrl;
            if ((cx == nullptr) != (cy == nullptr) || (cx && (cx->shared_owners != cy->shared_owners || cx->vtable != cy->vtable)))
                return "control block of " + std::to_string(x->key);
        }
    }
    return (x || y) ? "list length" : "";
}

void clone_map(const ElementInfo& I, U32Map& to, const U32Map& from, bool shared) {
    to = {};
    to.max_load_factor = from.max_load_factor;
    to.size = from.size;
    to.bucket_count = from.bucket_count;
    if (from.buckets) {
        to.buckets = (U32Node**)U32Map::alloc_block(from.bucket_count * 8);
        for (u64 i = 0; i < from.bucket_count; i++) to.buckets[i] = nullptr;
    }
    std::unordered_map<const U32Node*, U32Node*> map;
    map[reinterpret_cast<const U32Node*>(&from.first)] = reinterpret_cast<U32Node*>(&to.first);
    U32Node* prev = reinterpret_cast<U32Node*>(&to.first);
    for (const U32Node* n = from.first; n; n = n->next) {
        auto* c = (U32Node*)U32Map::alloc_block(sizeof(U32Node) + (shared ? sizeof(SharedPtr) : I.size));
        c->next = nullptr;
        c->hash = n->hash;
        c->key = n->key;
        if (shared) {
            auto* v = reinterpret_cast<SharedPtr*>(c->value());
            *v = *reinterpret_cast<const SharedPtr*>(const_cast<U32Node*>(n)->value());
            if (v->ctrl) v->ctrl->__add_shared();
        } else {
            ElementCode::CtorCopy(I, c->value(), const_cast<U32Node*>(n)->value());
        }
        prev->next = c;
        prev = c;
        map[n] = c;
    }
    for (u64 i = 0; from.buckets && i < from.bucket_count; i++)
        if (from.buckets[i]) to.buckets[i] = map.count(from.buckets[i]) ? map[from.buckets[i]] : nullptr;
}

void free_map(const ElementInfo& I, U32Map& m, bool shared) {
    if (shared) m.destroy(SimpleCode::release_node_shared);
    else m.destroy([&](U32Node* n) { SimpleCode::destroy_node_element(I, n); });
}

}  // namespace soa::native::master
