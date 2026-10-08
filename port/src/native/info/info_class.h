#pragma once
// The info classes' generic code (info_class.cpp) and TInfo<C>'s members over it: an info class is its
// generated InfoClass (gen/info_classes.h: properties, children, Initialize's steps) plus the guest
// addresses those name (resolved on first use).
#include <cstddef>
#include <string>
#include <vector>

#include "native/info/gen/info_classes.h"
#include "native/info/info_family.h"
#include "native/info/info_layout.h"

namespace soa::native::info {

// The N- and T-independent views of a property (params_layout.h: the layouts don't depend on them).
using AnyProperty = params::CParameterPropertyBase<0>;
using AnyValueProperty = params::CParameterPropertyValue<u64, 0>;
using AnyStringProperty = params::CParameterPropertyString<0>;
static_assert(sizeof(AnyProperty) == 0x28 && offsetof(AnyValueProperty, m_value) == 0x28 && offsetof(AnyStringProperty, m_value) == 0x28);

u32 value_width(InfoPropKind k);  // sizeof(T) of a value property

// One class's guest addresses (resolved once per class).
struct InfoResolved {
    u64 vtable = 0;                // ZTV + 16
    std::vector<u64> vt_final;     // per property: its class's vtable (+16)
    std::vector<u64> vt_base;      // per property: CParameterPropertyBase<N>'s (+16)
};
const InfoResolved& resolve(const InfoClass& C);

// The code every info class shares, on an object's bytes.
struct InfoCode {
    // The default constructor (inlined almost everywhere; exported for some): InfoBase (the class's
    // vtable, both maps empty), each property as CParameterPropertyX<N>() leaves it (its vtable, m_next 0,
    // m_named 0, CHash32(): vtable, 0; a string's three words 0; a value untouched), each child the same
    // way (a container: its vtable, empty maps, its vector / map empty).
    static void Ctor(const InfoClass& C, u8* obj);
    // Initialize: the steps in order. A property: m_name = CHash32(key) (a key of 23 bytes or more goes
    // through a long std::string: allocated and freed around it), m_named = 1, the default stored (as
    // wide as the value; none for a string), then the property map's __emplace_unique_key_args(its
    // NameHash() = m_name's hash, the property). A child: its pParseName() (vtable slot 3) as a CHash32,
    // the child map's __emplace_unique_impl(that, the child), the child's Initialize (slot 2).
    static void Initialize(const InfoClass& C, u8* obj);
};

// The state the live check and the tests compare: every property's bytes (a string by content), both
// maps' entries (key, the value's offset from the object), the children's, recursively.
std::vector<u8> info_state(const InfoClass& C, const u8* obj);
// Frees what Initialize allocated (the maps' nodes, recursively): the tests' clean-up.
void info_free_maps(const InfoClass& C, u8* obj);

// The checked guest functions of class C (info_class_bind.cpp).
enum class InfoRole { Initialize, Ctor, kCount };

// TInfo<C>: the methods every info class has (each exported for some classes; gen/info_classes.h
// INFO_INITIALIZERS / INFO_CONSTRUCTORS say which). Layout: C's.
template <class C>
struct InfoTraits;

template <class C>
class TInfo {
public:
    void Initialize();  // _ZN<C>10InitializeEv (vtable slot 2)
    void Ctor();        // _ZN<C>C2Ev

    C c;
};

}  // namespace soa::native::info
