// master_layout.h: the guest data layouts of the `master` subsystem (master data: the SQLite connectors, the master parameter tables, StringDB, CMasterManager / CMasterCache).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/master/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types master` turns the structs into port/decomp/master/types.json for Ghidra.
#ifndef SOA_NATIVE_MASTER_LAYOUT_H
#define SOA_NATIVE_MASTER_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../params/params_layout.h"
#include "gen/master_elements.h"

namespace soa::native::master {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// ---- the elements ----------------------------------------------------------------------------------------
//
// The rows of the master tables as the client keeps them: one class per table (the T of
// CMasterParameterBaseSqlite_Simple<T> / _Category<T>), a CParameterElementBase followed by its
// properties (params_layout.h). The 160 classes are generated (gen/master_elements.h,
// tools/gen_master_elements.py: the inlined default constructor, the destructor and Initialize read
// from the lib); their code is the same for every class but for the property list, so the natives are
// one template over the generated class.

// The N- and T-independent views of a property: CParameterPropertyBase<N>'s layout (vtable, m_next,
// m_named, m_name) is the same for every N, a value's m_value is at +0x28 whatever its T, a string's
// String at +0x28 (params_layout.h).
using AnyProperty = params::CParameterPropertyBase<0>;
using AnyValueProperty = params::CParameterPropertyValue<u64, 0>;
using AnyStringProperty = params::CParameterPropertyString<0>;
static_assert(sizeof(AnyProperty) == 0x28 && offsetof(AnyValueProperty, m_value) == 0x28 && offsetof(AnyStringProperty, m_value) == 0x28);
static_assert(sizeof(AnyValueProperty) == 0x30 && sizeof(AnyStringProperty) == 0x40);

// TElement<E>: the methods every element class has (each exported for most classes; the generated
// kEMethods list says which). Layout: E's.
template <class E>
class TElement {
public:
    // E::E(): CParameterElementBase(), the element's vtable; each property: its final vtable, m_next = 0,
    // m_named = 0, CHash32() (vtable, hash 0); a string's three words 0. Values are left as they were.
    void Ctor();  // _ZN<E>C2Ev (inlined into the templates for every class)
    // E::E(E const&): vtables as Ctor; m_first, each m_next, m_named, hash and value copied as they are
    // (the copy's list still runs through the source's properties: a guest quirk, kept); strings copied
    // (a long one into new storage from the STL allocator).
    void CtorCopy(const TElement* o);  // _ZN<E>C2ERKS_
    // E::operator=(E const&): m_first, each m_next, m_named, hash, value; strings assigned (libc++
    // assign: in place when it fits, else __grow_by_and_replace). Vtables untouched.
    TElement* Assign(const TElement* o);  // _ZN<E>aSERKS_
    // ~E() (D2): the element's vtable back; each property from the last: a string's
    // CParameterPropertyString<N> vtable, its long storage freed, then CParameterPropertyBase<N>'s
    // vtable; ~CHash32 (a RET).
    void Dtor();        // _ZN<E>D2Ev
    void DtorDelete();  // _ZN<E>D0Ev: ~E(), operator delete
    // E::Initialize() (vtable slot 0): each named property in the AddProperty order: m_name = CHash32(key)
    // (a key of 23 bytes or more goes through a long std::string: allocated and freed around it),
    // m_named = 1, a value property's default, AddProperty.
    void Initialize();  // _ZN<E>10InitializeEv

    E e;
};

}  // namespace soa::native::master

#endif  // SOA_NATIVE_MASTER_LAYOUT_H
