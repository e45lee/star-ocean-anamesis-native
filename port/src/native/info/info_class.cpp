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
#include "native/libcxx/libcxx_string.h"

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
    if (C.kind == InfoKind::kValueArray) {
        R.elem_vt_final = g::sym(value_vtable_symbol(C.elem_prop).c_str()) + 16;
        R.elem_vt_base = g::sym(base_vtable_symbol(C.elem_prop.n).c_str()) + 16;
    }
    if (C.fn_copy) R.fn_copy = g::sym(C.fn_copy);
    if (C.fn_destroy) R.fn_destroy = g::sym(C.fn_destroy);
    if (C.fn_assign) R.fn_assign = g::sym(C.fn_assign);
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

// ---- copies, assignments, moves, the destructor (infos without a container inside) ----

namespace {

AnyStringProperty* string_property(u8* obj, const InfoProp& d) { return reinterpret_cast<AnyStringProperty*>(obj + d.offset); }
u8* value_bytes(u8* obj, const InfoProp& d) { return obj + d.offset + offsetof(AnyValueProperty, m_value); }
const u8* value_bytes(const u8* obj, const InfoProp& d) { return obj + d.offset + offsetof(AnyValueProperty, m_value); }

// basic_string::operator=(basic_string const&) as the copy assignment inlines it: nothing for itself; in
// place when the source fits the capacity, else __grow_by_and_replace.
void assign_string(params::String* dst, const params::String* src) {
    if (dst == src) return;
    u64 n = src->size();
    const char* s = src->data();
    u64 cap = dst->capacity();
    if (n > cap) {
        u64 sz = dst->size();
        dst->__grow_by_and_replace(cap, n - cap, sz, 0, sz, n, s);
        return;
    }
    char* to = dst->is_long() ? dst->r.l.data : reinterpret_cast<char*>(&dst->r.s.data[0]);
    if (n) std::memmove(to, s, n);
    to[n] = 0;
    if (dst->is_long()) dst->r.l.size = n;
    else dst->r.s.head.size = static_cast<u8>(n << 1);
}

// The source's three words taken, the source's left 0.
void steal_string(params::String* dst, params::String* src) {
    std::memcpy(dst, src, sizeof *dst);
    std::memset(src, 0, sizeof *src);
}

enum class Copy { kCopy, kMove };

void copy_into(const InfoClass& C, u8* obj, u8* src, Copy how);
void destroy(const InfoClass& C, u8* obj);

using Tree = libcxx::tree<u8>;  // (a container's map: the node's key at +0x20, the element at +0x28)
Tree& tree_of(u8* obj) { return *reinterpret_cast<Tree*>(&reinterpret_cast<InfoContainer*>(obj)->m_body); }

// One property of an InfoBaseValueArray's vector (CParameterPropertyValue<T, N>): its copy constructor.
void copy_value_property(const InfoClass& C, const InfoResolved& R, u8* to, const u8* from) {
    static const u64 hash_vtable = g::sym("_ZTVN9Framework7CHash32E") + 16;
    auto* p = reinterpret_cast<AnyProperty*>(to);
    auto* q = reinterpret_cast<const AnyProperty*>(from);
    p->base.vtable = reinterpret_cast<const void*>(R.elem_vt_final);
    p->base.m_next = q->base.m_next;
    p->m_named = q->m_named;
    p->m_name.vtable = hash_vtable;
    p->m_name.m_hash = q->m_name.m_hash;
    std::memcpy(to + 0x28, from + 0x28, value_width(C.elem_prop.kind));
}

// A container's body. The vector (InfoBaseArray, InfoBaseValueArray): copied (storage of the source's size
// from Allocate(bytes, "STL_Vector.h", 0x20), each element copy-constructed in order) or, by the move
// constructor, taken (the source's three words, left 0). The map (IInfoBaseMap): copied either way (CSTLMap
// declares a copy constructor: no move): empty, then each source element in order by the guest's
// __emplace_hint_unique_key_args(end(), key, the element's pair).
void copy_container(const InfoClass& C, const InfoResolved& R, u8* obj, u8* src, Copy how) {
    auto* c = reinterpret_cast<InfoContainer*>(obj);
    auto* sc = reinterpret_cast<InfoContainer*>(src);
    if (C.kind == InfoKind::kMap) {
        Tree& t = tree_of(obj);
        t.root = nullptr;
        t.size = 0;
        t.begin_node = reinterpret_cast<libcxx::tree_node<u8>*>(t.end_node());
        each_node(*reinterpret_cast<const PropertyMap*>(&sc->m_body), [&](const PropertyNode* n) {
            const u8* pair = reinterpret_cast<const u8*>(n) + 0x20;
            g::call(R.fn_copy, {reinterpret_cast<u64>(&t), reinterpret_cast<u64>(t.end_node()), reinterpret_cast<u64>(pair),
                                reinterpret_cast<u64>(pair)});
        });
        return;
    }
    if (how == Copy::kMove) {
        std::memcpy(c->m_body, sc->m_body, sizeof c->m_body);
        std::memset(sc->m_body, 0, sizeof sc->m_body);
        return;
    }
    c->m_body[0] = c->m_body[1] = c->m_body[2] = 0;
    u64 bytes = sc->m_body[1] - sc->m_body[0];
    if (!bytes) return;
    u64 p = reinterpret_cast<u64>(g::VectorAllocate(bytes));
    c->m_body[0] = c->m_body[1] = p;
    c->m_body[2] = p + bytes;
    u64 stride = C.kind == InfoKind::kValueArray ? 0x30 : C.elem->size;
    for (u64 e = sc->m_body[0]; e != sc->m_body[1]; e += stride) {
        if (C.kind == InfoKind::kValueArray) copy_value_property(C, R, reinterpret_cast<u8*>(c->m_body[1]), reinterpret_cast<const u8*>(e));
        else copy_into(*C.elem, reinterpret_cast<u8*>(c->m_body[1]), reinterpret_cast<u8*>(e), Copy::kCopy);
        c->m_body[1] += stride;
    }
}

// A container's body destroyed: the vector's elements from the last (an info's destructor; a value
// property's: CParameterPropertyBase<N>'s vtable), the end back at the beginning, the storage freed; the
// map's nodes by the guest's __tree::destroy(root).
void destroy_container(const InfoClass& C, const InfoResolved& R, u8* obj) {
    auto* c = reinterpret_cast<InfoContainer*>(obj);
    if (C.kind == InfoKind::kMap) {
        Tree& t = tree_of(obj);
        g::call(R.fn_destroy, {reinterpret_cast<u64>(&t), reinterpret_cast<u64>(t.root)});
        return;
    }
    if (!c->m_body[0]) return;
    u64 stride = C.kind == InfoKind::kValueArray ? 0x30 : C.elem->size;
    for (u64 e = c->m_body[1]; e != c->m_body[0];) {
        e -= stride;
        if (C.kind == InfoKind::kValueArray) *reinterpret_cast<u64*>(e) = R.elem_vt_base;
        else destroy(*C.elem, reinterpret_cast<u8*>(e));
    }
    c->m_body[1] = c->m_body[0];
    g::StlFree(reinterpret_cast<void*>(c->m_body[0]));
}

void copy_into(const InfoClass& C, u8* obj, u8* src, Copy how) {
    const InfoResolved& R = resolve(C);
    static const u64 hash_vtable = g::sym("_ZTVN9Framework7CHash32E") + 16;
    auto* base = reinterpret_cast<InfoBase*>(obj);
    auto* sb = reinterpret_cast<const InfoBase*>(src);
    base->vtable = reinterpret_cast<const void*>(R.vtable);
    g::CopyPropertyMap(&base->m_properties, &sb->m_properties);
    g::CopyChildMap(&base->m_children, &sb->m_children);
    if (C.kind != InfoKind::kInfo) return copy_container(C, R, obj, src, how);
    for (size_t i = 0; i < C.props.size(); i++) {
        const InfoProp& d = C.props[i];
        AnyProperty* p = property(obj, d);
        const AnyProperty* q = property(src, d);
        p->base.vtable = reinterpret_cast<const void*>(R.vt_final[i]);
        p->base.m_next = q->base.m_next;
        p->m_named = q->m_named;
        p->m_name.vtable = hash_vtable;
        p->m_name.m_hash = q->m_name.m_hash;
        if (d.kind != InfoPropKind::kString) std::memcpy(value_bytes(obj, d), value_bytes(src, d), value_width(d.kind));
        else if (how == Copy::kMove) steal_string(&string_property(obj, d)->m_value, &string_property(src, d)->m_value);
        else libcxx::string_copy_construct(&string_property(obj, d)->m_value, string_property(src, d)->m_value);
    }
    for (const InfoChild& ch : C.children) copy_into(*ch.cls, obj + ch.offset, src + ch.offset, how);
    if (C.tail) std::memcpy(obj + C.size - C.tail, src + C.size - C.tail, C.tail);
}

void assign_from(const InfoClass& C, u8* obj, u8* src, Copy how) {
    auto* base = reinterpret_cast<InfoBase*>(obj);
    auto* sb = reinterpret_cast<const InfoBase*>(src);
    if (obj != src) {
        g::AssignPropertyMap(&base->m_properties, &sb->m_properties);
        g::AssignChildMap(&base->m_children, &sb->m_children);
    }
    if (C.kind != InfoKind::kInfo) {
        // the body (a move assignment too: the containers' copy assignment): the guest's vector::assign(first,
        // last) / __tree::__assign_multi(first, last), unless it's itself
        if (obj == src) return;
        const InfoResolved& R = resolve(C);
        auto* sc = reinterpret_cast<const InfoContainer*>(src);
        u64 first = sc->m_body[0], last = sc->m_body[1];
        if (C.kind == InfoKind::kMap) last = reinterpret_cast<u64>(&sc->m_body[1]);  // (end(): the end node)
        g::call(R.fn_assign, {reinterpret_cast<u64>(&reinterpret_cast<InfoContainer*>(obj)->m_body), first, last});
        return;
    }
    for (const InfoProp& d : C.props) {
        AnyProperty* p = property(obj, d);
        const AnyProperty* q = property(src, d);
        p->base.m_next = q->base.m_next;
        p->m_named = q->m_named;
        p->m_name.m_hash = q->m_name.m_hash;
        if (d.kind != InfoPropKind::kString) {
            std::memmove(value_bytes(obj, d), value_bytes(src, d), value_width(d.kind));
        } else if (how == Copy::kCopy) {
            assign_string(&string_property(obj, d)->m_value, &string_property(src, d)->m_value);
        } else {
            // clear(), reserve(0) (a long string shrinks: its storage freed), then the source's words
            params::String& v = string_property(obj, d)->m_value;
            if (v.is_long()) g::StlFree(v.r.l.data);
            std::memset(&v, 0, sizeof v);
            steal_string(&v, &string_property(src, d)->m_value);
        }
    }
    for (const InfoChild& ch : C.children) assign_from(*ch.cls, obj + ch.offset, src + ch.offset, how);
    if (C.tail) std::memmove(obj + C.size - C.tail, src + C.size - C.tail, C.tail);
}

}  // namespace

void InfoCode::CtorCopy(const InfoClass& C, u8* obj, const u8* src) { copy_into(C, obj, const_cast<u8*>(src), Copy::kCopy); }
void InfoCode::Move(const InfoClass& C, u8* obj, u8* src) { copy_into(C, obj, src, Copy::kMove); }
void InfoCode::Assign(const InfoClass& C, u8* obj, const u8* src) { assign_from(C, obj, const_cast<u8*>(src), Copy::kCopy); }
void InfoCode::MoveAssign(const InfoClass& C, u8* obj, u8* src) { assign_from(C, obj, src, Copy::kMove); }

void InfoCode::Dtor(const InfoClass& C, u8* obj) { destroy(C, obj); }

namespace {

void destroy(const InfoClass& C, u8* obj) {
    const InfoResolved& R = resolve(C);
    static const u64 infobase_vtable = g::sym("_ZTV8InfoBase") + 16;
    auto* base = reinterpret_cast<InfoBase*>(obj);
    base->vtable = reinterpret_cast<const void*>(R.vtable);
    if (C.kind != InfoKind::kInfo) destroy_container(C, R, obj);
    // the members from the last (properties and children interleave by offset)
    size_t pi = C.props.size(), ci = C.children.size();
    while (pi || ci) {
        bool child = ci && (!pi || C.children[ci - 1].offset > C.props[pi - 1].offset);
        if (child) {
            const InfoChild& ch = C.children[--ci];
            destroy(*ch.cls, obj + ch.offset);
            continue;
        }
        const InfoProp& d = C.props[--pi];
        AnyProperty* p = property(obj, d);
        if (d.kind == InfoPropKind::kString) {
            p->base.vtable = reinterpret_cast<const void*>(R.vt_final[pi]);
            params::String& v = string_property(obj, d)->m_value;
            if (v.is_long()) g::StlFree(v.r.l.data);
        }
        p->base.vtable = reinterpret_cast<const void*>(R.vt_base[pi]);
    }
    base->vtable = reinterpret_cast<const void*>(infobase_vtable);
    g::DestroyChildTree(&base->m_children);
    g::DestroyPropertyTree(&base->m_properties);
}

}  // namespace

// ---- the state the checks compare, the tests' clean-up ----

namespace {


void put(std::vector<u8>& out, const void* p, size_t n) {
    out.insert(out.end(), static_cast<const u8*>(p), static_cast<const u8*>(p) + n);
}

struct Span;
void prop_state(std::vector<u8>& out, const InfoProp& d, const u8* obj, Span top);

// A pointer as the comparison sees it: into the top object, relative to it; else relative to `other`
// (a copy's maps and m_next still point into the object it was copied from, a dead temporary: the
// copy quirk; where that was differs between two runs, its layout doesn't), flagged; null as null.
thread_local bool t_maps = true;  // (info_state_no_maps: the map sizes only)
thread_local bool t_raw = false;  // (info_state_raw: pointers as they are)

struct Span {
    u64 lo, hi;
};
u64 relative(const void* p, Span top, u64 other) {
    u64 v = reinterpret_cast<u64>(p);
    if (!v || t_raw) return v;
    if (v >= top.lo && v < top.hi) return v - top.lo;
    return (v - other) | (u64(1) << 63);
}


void map_state(std::vector<u8>& out, const PropertyMap& m, Span top) {
    put(out, &m.size, 8);
    if (!t_maps) return;
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
    put(out, obj + C.size - C.tail, C.tail);
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

std::vector<u8> info_state_raw(const InfoClass& C, const u8* obj) {
    t_raw = true;
    std::vector<u8> out = info_state(C, obj);
    t_raw = false;
    return out;
}

std::vector<u8> info_state_no_maps(const InfoClass& C, const u8* obj) {
    t_maps = false;
    std::vector<u8> out = info_state(C, obj);
    t_maps = true;
    return out;
}

std::vector<u8> info_dtor_state(const InfoClass& K, const u8* obj) {
    std::vector<u8> mask(K.size, 1);
    auto clear = [&](size_t off, size_t n) { std::fill(mask.begin() + off, mask.begin() + off + n, 0); };
    std::vector<std::pair<const InfoClass*, size_t>> todo{{&K, 0}};
    while (!todo.empty()) {
        auto [c, at] = todo.back();
        todo.pop_back();
        clear(at + offsetof(InfoBase, m_properties), 0x30);
        if (c->kind != InfoKind::kInfo) {
            clear(at + 0x38, 0x18);
            continue;
        }
        for (const InfoProp& d : c->props)
            if (d.kind == InfoPropKind::kString) clear(at + d.offset + 0x28, 0x18);
        for (const InfoChild& ch : c->children) todo.push_back({ch.cls, at + ch.offset});
    }
    std::vector<u8> out;
    for (size_t i = 0; i < K.size; i++)
        if (mask[i]) out.push_back(obj[i]);
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
