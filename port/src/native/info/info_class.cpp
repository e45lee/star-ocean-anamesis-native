// The info classes (info_layout.h InfoClass; the 187 classes of gen/info_classes.h): their default
// constructors and Initialize, one generic code over the generated class (the guest's code differs per
// class only in the property and child lists). port/decomp/info/person_status.c is the decompile read
// (CPersonStatusInfo's constructor, Initialize, destructor); README.md "Info classes".
#include "native/info/info_class.h"

#include <algorithm>
#include <cstring>
#include <map>
#include <mutex>
#include <string>

#include "native/common/gen/common_addresses.h"
#include "native/common/guest_std.h"
#include "native/hash/hash_layout.h"
#include "native/info/info_guest.h"

namespace soa::native::info {

namespace {

constexpr u64 kShortKey = 23;  // a key this long or longer is a long std::string (allocated)

std::string value_vtable_symbol(const InfoProp& p) {
    char t = 'j';
    switch (p.kind) {
        case InfoPropKind::kU32: t = 'j'; break;
        case InfoPropKind::kS32: t = 'i'; break;
        case InfoPropKind::kFloat: t = 'f'; break;
        case InfoPropKind::kBool: t = 'b'; break;
        case InfoPropKind::kU8: t = 'h'; break;
        case InfoPropKind::kU64: t = 'm'; break;
        case InfoPropKind::kString: break;
    }
    char b[160];
    snprintf(b, sizeof b, "_ZTV23CParameterPropertyValueI%cLj%uE%sE", t, p.n,
             p.radian ? "24CPropertyConverterRadian" : "18CPropertyConverter");
    return b;
}
std::string string_vtable_symbol(u32 n) {
    return "_ZTV24CParameterPropertyStringINSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS4_"
           "22CSTLStringAllocatorInfEEEEELj" +
           std::to_string(n) + "EE";
}
std::string base_vtable_symbol(u32 n) { return "_ZTV22CParameterPropertyBaseILj" + std::to_string(n) + "EE"; }

AnyProperty* property(u8* obj, const InfoProp& d) { return reinterpret_cast<AnyProperty*>(obj + d.offset); }
const AnyProperty* property(const u8* obj, const InfoProp& d) { return reinterpret_cast<const AnyProperty*>(obj + d.offset); }
const params::String& string_value(const u8* obj, const InfoProp& d) {
    return reinterpret_cast<const AnyStringProperty*>(obj + d.offset)->m_value;
}

}  // namespace

u32 value_width(InfoPropKind k) {
    switch (k) {
        case InfoPropKind::kBool:
        case InfoPropKind::kU8: return 1;
        case InfoPropKind::kU64: return 8;
        case InfoPropKind::kString: return 0;
        default: return 4;
    }
}

const InfoResolved& resolve(const InfoClass& C) {
    static std::mutex m;
    static std::map<const InfoClass*, InfoResolved>* cache = new std::map<const InfoClass*, InfoResolved>();
    std::lock_guard<std::mutex> lock(m);
    auto it = cache->find(&C);
    if (it != cache->end()) return it->second;
    InfoResolved R;
    R.vtable = g::sym(C.ztv) + 16;
    for (const InfoProp& p : C.props) {
        R.vt_final.push_back(g::sym((p.kind == InfoPropKind::kString ? string_vtable_symbol(p.n) : value_vtable_symbol(p)).c_str()) + 16);
        R.vt_base.push_back(g::sym(base_vtable_symbol(p.n).c_str()) + 16);
    }
    return cache->emplace(&C, std::move(R)).first->second;
}

// ---- the default constructor ----

namespace {

void empty_maps(InfoBase* b) {
    for (PropertyMap* m : {&b->m_properties, &b->m_children}) {
        m->root = nullptr;
        m->size = 0;
        m->begin_node = reinterpret_cast<PropertyNode*>(m->end_node());
    }
}

}  // namespace

void InfoCode::Ctor(const InfoClass& C, u8* obj) {
    const InfoResolved& R = resolve(C);
    static const u64 hash_vtable = g::sym("_ZTVN9Framework7CHash32E") + 16;
    auto* base = reinterpret_cast<InfoBase*>(obj);
    base->vtable = reinterpret_cast<const void*>(R.vtable);
    empty_maps(base);
    if (C.kind != InfoKind::kInfo) {
        auto* c = reinterpret_cast<InfoContainer*>(obj);
        if (C.kind == InfoKind::kMap) {  // CSTLMap: begin node = the end node (&root), root 0, size 0
            c->m_body[0] = reinterpret_cast<u64>(&c->m_body[1]);
            c->m_body[1] = 0;
            c->m_body[2] = 0;
        } else {  // CSTLVector: begin, end, capacity 0
            c->m_body[0] = c->m_body[1] = c->m_body[2] = 0;
        }
        return;
    }
    for (size_t i = 0; i < C.props.size(); i++) {
        const InfoProp& d = C.props[i];
        AnyProperty* p = property(obj, d);
        p->base.vtable = reinterpret_cast<const void*>(R.vt_final[i]);
        p->base.m_next = nullptr;
        p->m_named = false;
        p->m_name.vtable = hash_vtable;
        p->m_name.m_hash = 0;
        if (d.kind == InfoPropKind::kString) std::memset(&reinterpret_cast<AnyStringProperty*>(p)->m_value, 0, sizeof(params::String));
    }
    for (const InfoChild& ch : C.children) Ctor(*ch.cls, obj + ch.offset);
}

// ---- Initialize ----

void InfoCode::Initialize(const InfoClass& C, u8* obj) {
    auto* self = reinterpret_cast<InfoBase*>(obj);
    for (const InfoStep& s : C.init) {
        if (s.kind == InfoStep::kProperty) {
            auto* p = reinterpret_cast<AnyProperty*>(obj + s.offset);
            u64 len = std::strlen(s.key);
            // the key is a std::string temporary: a long one has storage of its own for the call
            char* tmp = nullptr;
            if (len >= kShortKey) {
                tmp = static_cast<char*>(g::StringAllocate((len + 16) & ~u64(15)));
                std::memcpy(tmp, s.key, len + 1);
            }
            p->m_name.Assign(tmp ? tmp : s.key);
            p->m_named = true;
            if (s.width) std::memcpy(&reinterpret_cast<AnyValueProperty*>(p)->m_value, &s.def, s.width);
            if (tmp) g::StlFree(tmp);
            // NameHash() (CParameterPropertyBase<N>'s: m_name's hash; checked by the generator)
            g::EmplaceProperty(&self->m_properties, p->m_name.m_hash, p);
        } else {
            void* child = obj + s.offset;
            const char* key = reinterpret_cast<const char*>(g::vcall(child, InfoBase::kSlotParseName, {}));
            hash::CHash32 h;
            h.Ctor(key);
            g::EmplaceChild(&self->m_children, &h, child);
            // (~CHash32: a RET)
            g::vcall(child, InfoBase::kSlotInitialize, {});
        }
    }
}

// ---- the state the checks compare, the tests' clean-up ----

namespace {

template <class F>
void each_node(const PropertyMap& m, F f) {
    auto* end = reinterpret_cast<const libcxx::tree_node_base*>(&m.root);
    for (auto* n = reinterpret_cast<const libcxx::tree_node_base*>(m.begin_node); n != end;) {
        f(reinterpret_cast<const PropertyNode*>(n));
        if (n->right) {
            n = n->right;
            while (n->left) n = n->left;
        } else {
            while (n->parent->left != n) n = n->parent;
            n = n->parent;
        }
    }
}

void put(std::vector<u8>& out, const void* p, size_t n) {
    out.insert(out.end(), static_cast<const u8*>(p), static_cast<const u8*>(p) + n);
}

struct Span;
void prop_state(std::vector<u8>& out, const InfoProp& d, const u8* obj, Span top);

// A pointer as the comparison sees it: into the top object, relative to it; else relative to `other`
// (a copy's maps and m_next still point into the object it was copied from, a dead temporary: the
// copy quirk; where that was differs between two runs, its layout doesn't), flagged; null as null.
struct Span {
    u64 lo, hi;
};
u64 relative(const void* p, Span top, u64 other) {
    u64 v = reinterpret_cast<u64>(p);
    if (!v) return 0;
    if (v >= top.lo && v < top.hi) return v - top.lo;
    return (v - other) | (u64(1) << 63);
}

void map_state(std::vector<u8>& out, const PropertyMap& m, Span top) {
    put(out, &m.size, 8);
    u64 lo = ~u64(0);
    each_node(m, [&](const PropertyNode* n) { lo = std::min(lo, reinterpret_cast<u64>(n->value.second)); });
    each_node(m, [&](const PropertyNode* n) {
        put(out, &n->value.first, 4);
        u64 rel = relative(n->value.second, top, lo);
        put(out, &rel, 8);
    });
}

void state(std::vector<u8>& out, const InfoClass& C, const u8* obj, Span top) {
    auto* b = reinterpret_cast<const InfoBase*>(obj);
    put(out, &b->vtable, 8);
    map_state(out, b->m_properties, top);
    map_state(out, b->m_children, top);
    if (C.kind != InfoKind::kInfo) {
        // the elements, each relative to itself (their storage is each run's own)
        auto* c = reinterpret_cast<const InfoContainer*>(obj);
        if (C.kind == InfoKind::kMap) {
            auto& tree = *reinterpret_cast<const PropertyMap*>(&c->m_body);
            put(out, &tree.size, 8);
            each_node(tree, [&](const PropertyNode* n) {
                auto* node = reinterpret_cast<const u8*>(n);
                put(out, node + 0x20, C.key_size);
                if (C.elem) state(out, *C.elem, node + 0x28, Span{reinterpret_cast<u64>(node) + 0x28, reinterpret_cast<u64>(node) + 0x28 + C.elem->size});
            });
            return;
        }
        u64 stride = C.kind == InfoKind::kValueArray ? 0x30 : C.elem ? C.elem->size : 0;
        u64 n = stride ? (c->m_body[1] - c->m_body[0]) / stride : 0;
        put(out, &n, 8);
        for (u64 i = 0; i < n; i++) {
            auto* e = reinterpret_cast<const u8*>(c->m_body[0] + i * stride);
            Span self{reinterpret_cast<u64>(e), reinterpret_cast<u64>(e) + stride};
            if (C.kind == InfoKind::kValueArray) prop_state(out, C.elem_prop, e, self);
            else state(out, *C.elem, e, self);
        }
        return;
    }
    for (const InfoProp& d : C.props) prop_state(out, d, obj, top);
    for (const InfoChild& ch : C.children) state(out, *ch.cls, obj + ch.offset, top);
}

void prop_state(std::vector<u8>& out, const InfoProp& d, const u8* obj, Span top) {
    const AnyProperty* p = property(obj, d);
    put(out, &p->base.vtable, 8);
    u64 next = relative(p->base.m_next, top, reinterpret_cast<u64>(p->base.m_next));  // (outside: only "set")
    put(out, &next, 8);
    put(out, &p->m_named, 1);
    put(out, &p->m_name.vtable, 8);
    put(out, &p->m_name.m_hash, 4);  // (not its padding)
    if (d.kind == InfoPropKind::kString) {
        const params::String& s = string_value(obj, d);
        put(out, s.data(), s.size());
        out.push_back(0xff);
    } else {
        put(out, &reinterpret_cast<const AnyValueProperty*>(p)->m_value, value_width(d.kind));
    }
}

}  // namespace

std::vector<u8> info_state(const InfoClass& C, const u8* obj) {
    std::vector<u8> out;
    state(out, C, obj, Span{reinterpret_cast<u64>(obj), reinterpret_cast<u64>(obj) + C.size});
    return out;
}

void info_free_maps(const InfoClass& C, u8* obj) {
    auto* b = reinterpret_cast<InfoBase*>(obj);
    g::DestroyPropertyTree(&b->m_properties);
    g::DestroyChildTree(&b->m_children);
    empty_maps(b);
    if (C.kind == InfoKind::kInfo)
        for (const InfoChild& ch : C.children) info_free_maps(*ch.cls, obj + ch.offset);
}

}  // namespace soa::native::info
