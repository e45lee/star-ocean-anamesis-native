// The master tables' element classes (master_layout.h TElement<E>; the 160 classes of
// gen/master_elements.h): their constructors, copy constructor, operator=, destructors and Initialize,
// one template over the generated class (the guest's code differs per class only in the property list).
// port/decomp/master/element_signal.c and stringdb.c are the decompiles read; README.md "Elements".
#include <cstring>
#include <span>
#include <string>
#include <vector>

#include "soaruntime/core/loader.h"
#include "soaruntime/core/log.h"
#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/hash/hash_layout.h"
#include "native/libcxx/libcxx_string.h"
#include "native/master/master_element.h"
#include "native/master/master_family.h"
#include "native/master/master_guest.h"
#include "native/params/params_check.h"

namespace soa::native::master {

namespace {

constexpr u64 kShortKey = 23;  // a key this long or longer is a long std::string (allocated)

std::string value_vtable_symbol(const ElementProp& p) {
    char t = 'j';
    switch (p.kind) {
        case PropKind::kU32: t = 'j'; break;
        case PropKind::kS32: t = 'i'; break;
        case PropKind::kFloat: t = 'f'; break;
        case PropKind::kBool: t = 'b'; break;
        case PropKind::kU8: t = 'h'; break;
        case PropKind::kU64: t = 'm'; break;
        case PropKind::kString: break;
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

}  // namespace

u32 value_width(PropKind k) {
    switch (k) {
        case PropKind::kBool:
        case PropKind::kU8: return 1;
        case PropKind::kU64: return 8;
        case PropKind::kString: return 0;
        default: return 4;
    }
}

ElementInfo resolve_element(const char* cls, const char* ztv, std::span<const ElementProp> props, u32 size) {
    ElementInfo I;
    I.cls = cls;
    I.props = props;
    I.size = size;
    I.vtable = g::sym(ztv) + 16;
    I.hash_vtable = g::sym("_ZTVN9Framework7CHash32E") + 16;
    std::vector<int> by_link(props.size(), -1);
    for (size_t i = 0; i < props.size(); i++) {
        const ElementProp& p = props[i];
        I.vt_final.push_back(g::sym((p.kind == PropKind::kString ? string_vtable_symbol(p.n) : value_vtable_symbol(p)).c_str()) + 16);
        I.vt_base.push_back(g::sym(base_vtable_symbol(p.n).c_str()) + 16);
        if (p.link >= 0) by_link[p.link] = (int)i;
    }
    for (int i : by_link)
        if (i >= 0) I.linked.push_back((u16)i);
    return I;
}

// ---- the generic code: one element class's ElementInfo and its bytes ----

void ElementCode::Ctor(const ElementInfo& I, u8* obj) {
    auto* base = element_base(obj);
    base->vtable = (const void*)I.vtable;
    base->m_first = nullptr;
    for (size_t i = 0; i < I.props.size(); i++) {
        AnyProperty* p = property(obj, I.props[i]);
        p->base.vtable = (const void*)I.vt_final[i];
        p->base.m_next = nullptr;
        p->m_named = false;
        p->m_name.vtable = I.hash_vtable;
        p->m_name.m_hash = 0;
        if (I.props[i].kind == PropKind::kString) std::memset(&string_property(obj, I.props[i])->m_value, 0, sizeof(String));
    }
}

void ElementCode::CtorCopy(const ElementInfo& I, u8* obj, const u8* src) {
    auto* base = element_base(obj);
    base->vtable = (const void*)I.vtable;
    base->m_first = element_base(src)->m_first;  // the source's list (sic)
    for (size_t i = 0; i < I.props.size(); i++) {
        const ElementProp& d = I.props[i];
        AnyProperty* p = property(obj, d);
        const AnyProperty* s = property(src, d);
        p->base.vtable = (const void*)I.vt_final[i];
        p->base.m_next = s->base.m_next;
        p->m_named = s->m_named;
        p->m_name.vtable = I.hash_vtable;
        p->m_name.m_hash = s->m_name.m_hash;
        if (d.kind == PropKind::kString) libcxx::string_copy_construct(&string_property(obj, d)->m_value, string_property(src, d)->m_value);
        else std::memcpy(value_bytes(obj, d), value_bytes(src, d), value_width(d.kind));
    }
}

// basic_string::operator=(basic_string const&) as the copy assignment inlines it: nothing for itself;
// in place when the source fits the capacity, else __grow_by_and_replace.
void ElementCode::AssignString(String* dst, const String* src) {
    if (dst == src) return;
    u64 n = src->size();
    const char* s = src->data();
    u64 cap = dst->capacity();
    if (n > cap) {
        u64 sz = dst->size();
        dst->__grow_by_and_replace(cap, n - cap, sz, 0, sz, n, s);
        return;
    }
    char* to = dst->is_long() ? dst->r.l.data : (char*)&dst->r.s.data[0];
    if (n) std::memmove(to, s, n);
    to[n] = 0;
    if (dst->is_long()) dst->r.l.size = n;
    else dst->r.s.head.size = (u8)(n << 1);
}

void ElementCode::Assign(const ElementInfo& I, u8* obj, const u8* src) {
    element_base(obj)->m_first = element_base(src)->m_first;
    for (const ElementProp& d : I.props) {
        AnyProperty* p = property(obj, d);
        const AnyProperty* s = property(src, d);
        p->base.m_next = s->base.m_next;
        p->m_named = s->m_named;
        p->m_name.m_hash = s->m_name.m_hash;
        if (d.kind == PropKind::kString) AssignString(&string_property(obj, d)->m_value, &string_property(src, d)->m_value);
        else std::memcpy(value_bytes(obj, d), value_bytes(src, d), value_width(d.kind));
    }
}

void ElementCode::Dtor(const ElementInfo& I, u8* obj) {
    element_base(obj)->vtable = (const void*)I.vtable;
    for (size_t i = I.props.size(); i-- > 0;) {
        const ElementProp& d = I.props[i];
        AnyProperty* p = property(obj, d);
        if (d.kind == PropKind::kString) {
            p->base.vtable = (const void*)I.vt_final[i];
            String& s = string_property(obj, d)->m_value;
            if (s.is_long()) g::StlFree(s.r.l.data);
        }
        p->base.vtable = (const void*)I.vt_base[i];
        // ~CHash32(): a RET
    }
}

void ElementCode::Initialize(const ElementInfo& I, u8* obj) {
    auto* base = element_base(obj);
    for (u16 i : I.linked) {
        const ElementProp& d = I.props[i];
        AnyProperty* p = property(obj, d);
        u64 len = std::strlen(d.key);
        // the key is a std::string temporary: a long one has storage of its own for the call
        char* tmp = nullptr;
        if (len >= kShortKey) {
            tmp = (char*)g::StringAllocate((len + 16) & ~u64(15));
            std::memcpy(tmp, d.key, len + 1);
        }
        p->m_name.Assign(tmp ? tmp : d.key);
        p->m_named = true;
        if (d.kind != PropKind::kString) std::memcpy(value_bytes(obj, d), &d.def, value_width(d.kind));
        if (tmp) g::StlFree(tmp);
        base->AddProperty(&p->base);
    }
}

}  // namespace soa::native::master
