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
    // a container: its element property's vtables (InfoBaseValueArray), the guest functions it calls
    u64 elem_vt_final = 0, elem_vt_base = 0;
    u64 fn_copy = 0, fn_destroy = 0, fn_assign = 0;
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
    // The copy constructor: InfoBase's (the class's vtable; both maps by CSTLMap's copy constructor: the
    // values as they are, so the copy's maps point at the source's properties and children: a guest
    // quirk, kept), each property's (its vtable, m_next, m_named, the name's hash, the value as wide as it
    // is; a string copy-constructed), each child's the same way.
    static void CtorCopy(const InfoClass& C, u8* obj, const u8* src);
    // The move constructor: the copy's, but a string takes the source's three words and leaves them 0
    // (InfoBase has no move: its maps are copied).
    static void Move(const InfoClass& C, u8* obj, u8* src);
    // operator=: unless obj is src, both maps by __tree::__assign_multi(src's begin, end); each property's
    // m_next, m_named, the hash, the value; a string assigned (libc++: in place when it fits, else
    // __grow_by_and_replace; nothing for itself); each child's operator=. The vtables are left alone.
    static void Assign(const InfoClass& C, u8* obj, const u8* src);
    // operator=(&&): the same, but a string is cleared, shrunk (reserve(0): a long one's storage freed)
    // and takes the source's three words, which are left 0.
    static void MoveAssign(const InfoClass& C, u8* obj, u8* src);
    // The destructor: the members from the last: a property's (a string's own vtable, its long storage
    // freed) CParameterPropertyBase<N>'s vtable (~CHash32: a RET), a child's destructor; then InfoBase's:
    // its vtable, the child map's nodes, the property map's (__tree::destroy(root); the fields stay).
    static void Dtor(const InfoClass& C, u8* obj);
};

// The state the live check and the tests compare: every property's bytes (a string by content), both
// maps' entries (key, the value's offset from the object), the children's, recursively.
std::vector<u8> info_state(const InfoClass& C, const u8* obj);
// What Initialize's steps leave (each named property's flag, hash and default; each store's bytes; the
// object's maps): for a class without a layout (CInfoManager).
std::vector<u8> info_steps_state(const InfoClass& C, const u8* obj);
// The same with every pointer as it is (maps' values, m_next): two copies of one source compared (a
// copy's maps keep the source's pointers, wherever they point).
std::vector<u8> info_state_raw(const InfoClass& C, const u8* obj);
// The same without the maps' entries (their sizes kept): a source the checks copied (the copy's maps
// point into the original) compared with the original.
std::vector<u8> info_state_no_maps(const InfoClass& C, const u8* obj);
// The bytes a destructor leaves that two runs can compare: every byte but the maps' fields (each run's
// node pointers stay) and the strings' words.
std::vector<u8> info_dtor_state(const InfoClass& C, const u8* obj);
// Frees what Initialize allocated (the maps' nodes, recursively): the tests' clean-up.
void info_free_maps(const InfoClass& C, u8* obj);

// The checked guest functions of class C (info_class_bind.cpp).
enum class InfoRole { Initialize, Ctor, CtorCopy, Dtor, Assign, Move, MoveAssign, kCount };

// TInfo<C>: the methods every info class has (each exported for some classes; gen/info_classes.h
// INFO_INITIALIZERS / INFO_CONSTRUCTORS say which). Layout: C's.
template <class C>
struct InfoTraits;

template <class C>
class TInfo {
public:
    void Initialize();  // _ZN<C>10InitializeEv (vtable slot 2)
    void Ctor();        // _ZN<C>C2Ev
    void CtorCopy(const TInfo* o);   // _ZN<C>C2ERKS_
    void Dtor();                     // _ZN<C>D2Ev
    TInfo* Assign(const TInfo* o);   // _ZN<C>aSERKS_
    void Move(TInfo* o);             // _ZN<C>C2EOS_
    TInfo* MoveAssign(TInfo* o);     // _ZN<C>aSEOS_

    C c;
};

}  // namespace soa::native::info
