#pragma once
// The element natives' generic code (master_element.cpp) and TElement<E>'s members over it: one
// element class is its generated property list (gen/master_elements.h) plus the guest addresses that
// list names (ElementInfo, resolved on first use).
#include <cstddef>
#include <span>
#include <vector>

#include "native/master/master_family.h"
#include "native/master/master_layout.h"

namespace soa::native::master {

using String = params::String;

// One element class's guest addresses.
struct ElementInfo {
    const char* cls = nullptr;
    std::span<const ElementProp> props;
    u32 size = 0;
    u64 vtable = 0;                   // _ZTV<E> + 16
    u64 hash_vtable = 0;              // Framework::CHash32's
    std::vector<u64> vt_final;        // per property: its class's vtable (+16)
    std::vector<u64> vt_base;         // per property: CParameterPropertyBase<N>'s (+16)
    std::vector<u16> linked;          // the named properties' indices in AddProperty order
};
ElementInfo resolve_element(const char* cls, const char* ztv, std::span<const ElementProp> props, u32 size);
u32 value_width(PropKind k);  // sizeof(T) of a value property
void g_operator_delete(void* p);  // master_guest.h g::OperatorDelete (for the templates below)

// E -> its generated tables (specialized for every class of MASTER_ELEMENTS in master_element_bind.cpp
// and the tests).
template <class E>
struct ElementTraits;

#define MASTER_ELEMENT_TRAITS(C, ZTV)                                         \
    template <>                                                               \
    struct ElementTraits<C> {                                                 \
        static constexpr const char* name = #C;                               \
        static constexpr const char* ztv = ZTV;                               \
        static constexpr const char* mangled = ZTV + 4;                       \
        static constexpr std::span<const ElementMethod> table{k##C##Table};   \
        static constexpr std::span<const ElementProp> props{k##C##Props};     \
        static constexpr std::span<const ElementMethod> methods{k##C##Methods}; \
    };
MASTER_ELEMENTS(MASTER_ELEMENT_TRAITS)
#undef MASTER_ELEMENT_TRAITS

template <class E>
const ElementInfo& element_info() {
    static const ElementInfo I = resolve_element(ElementTraits<E>::name, ElementTraits<E>::ztv, ElementTraits<E>::props, sizeof(E));
    return I;
}

// The code every element class shares, on an element's bytes.
struct ElementCode {
    static void Ctor(const ElementInfo& I, u8* obj);
    static void CtorCopy(const ElementInfo& I, u8* obj, const u8* src);
    static void Assign(const ElementInfo& I, u8* obj, const u8* src);
    static void Dtor(const ElementInfo& I, u8* obj);
    static void Initialize(const ElementInfo& I, u8* obj);
    static void AssignString(String* dst, const String* src);
};

// The N- and T-independent views of a property (params_layout.h: the layouts don't depend on them),
// at the offset its generated row gives (static_asserted against the generated class).
inline params::CParameterElementBase* element_base(u8* obj) { return reinterpret_cast<params::CParameterElementBase*>(obj); }
inline const params::CParameterElementBase* element_base(const u8* obj) {
    return reinterpret_cast<const params::CParameterElementBase*>(obj);
}
inline AnyProperty* property(u8* obj, const ElementProp& d) { return reinterpret_cast<AnyProperty*>(obj + d.offset); }
inline const AnyProperty* property(const u8* obj, const ElementProp& d) {
    return reinterpret_cast<const AnyProperty*>(obj + d.offset);
}
inline AnyStringProperty* string_property(u8* obj, const ElementProp& d) { return reinterpret_cast<AnyStringProperty*>(obj + d.offset); }
inline const AnyStringProperty* string_property(const u8* obj, const ElementProp& d) {
    return reinterpret_cast<const AnyStringProperty*>(obj + d.offset);
}
inline u8* value_bytes(u8* obj, const ElementProp& d) { return obj + d.offset + offsetof(AnyValueProperty, m_value); }
inline const u8* value_bytes(const u8* obj, const ElementProp& d) { return obj + d.offset + offsetof(AnyValueProperty, m_value); }

// ---- the live check (master_element_check.cpp): run-both on a private copy ----

enum class ElementRole { Initialize, Ctor, CtorCopy, Assign, Dtor, DtorDelete, kCount };
// The checked guest functions of class E, by role (the first symbol bound for it; master_element_bind.cpp).
template <class E>
struct ElementFns {
    static inline Fn* fn[(int)ElementRole::kCount] = {};
};
template <class E>
Fn* element_fn(ElementRole r) {
    Fn* f = ElementFns<E>::fn[(int)r];
    return f && fam().due(*f) ? f : nullptr;
}
struct ElementCheck {
    static void Ctor(const ElementInfo& I, Fn& f, u8* obj);
    static void CtorCopy(const ElementInfo& I, Fn& f, u8* obj, const u8* src);
    static void Assign(const ElementInfo& I, Fn& f, u8* obj, const u8* src);
    static void Dtor(const ElementInfo& I, Fn& f, u8* obj);
    static void Initialize(const ElementInfo& I, Fn& f, u8* obj);
};

// ---- TElement<E>'s members (master_layout.h) ----

template <class E>
u8* bytes_of(TElement<E>* t) {
    return reinterpret_cast<u8*>(t);
}
template <class E>
const u8* bytes_of(const TElement<E>* t) {
    return reinterpret_cast<const u8*>(t);
}

template <class E>
void TElement<E>::Ctor() {
    if (Fn* f = element_fn<E>(ElementRole::Ctor)) return ElementCheck::Ctor(element_info<E>(), *f, bytes_of(this));
    ElementCode::Ctor(element_info<E>(), bytes_of(this));
}
template <class E>
void TElement<E>::CtorCopy(const TElement* o) {
    if (Fn* f = element_fn<E>(ElementRole::CtorCopy)) return ElementCheck::CtorCopy(element_info<E>(), *f, bytes_of(this), bytes_of(o));
    ElementCode::CtorCopy(element_info<E>(), bytes_of(this), bytes_of(o));
}
template <class E>
TElement<E>* TElement<E>::Assign(const TElement* o) {
    if (Fn* f = element_fn<E>(ElementRole::Assign)) ElementCheck::Assign(element_info<E>(), *f, bytes_of(this), bytes_of(o));
    else ElementCode::Assign(element_info<E>(), bytes_of(this), bytes_of(o));
    return this;
}
template <class E>
void TElement<E>::Dtor() {
    if (Fn* f = element_fn<E>(ElementRole::Dtor)) return ElementCheck::Dtor(element_info<E>(), *f, bytes_of(this));
    ElementCode::Dtor(element_info<E>(), bytes_of(this));
}
template <class E>
void TElement<E>::DtorDelete() {
    ElementCode::Dtor(element_info<E>(), bytes_of(this));  // (not checked: the guest's would delete its copy)
    g_operator_delete(this);
}
template <class E>
void TElement<E>::Initialize() {
    if (Fn* f = element_fn<E>(ElementRole::Initialize)) return ElementCheck::Initialize(element_info<E>(), *f, bytes_of(this));
    ElementCode::Initialize(element_info<E>(), bytes_of(this));
}

}  // namespace soa::native::master
