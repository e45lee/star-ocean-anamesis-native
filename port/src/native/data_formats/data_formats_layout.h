// data_formats_layout.h: the guest data layouts of the `data_formats` subsystem (ASON, ACSV, msgpack).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/data_formats/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types data_formats` turns the structs into port/decomp/data_formats/types.json for Ghidra.
#ifndef SOA_NATIVE_DATA_FORMATS_LAYOUT_H
#define SOA_NATIVE_DATA_FORMATS_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::data_formats {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// The form (replace with the first recovered class; `tools/subsystem.py skeleton data_formats` writes the
// member declarations from port/decomp/data_formats/symbols.tsv):
//
// // CExample: guest size 0x18; layout from CExample::CExample (port/decomp/data_formats/example.c).
// class CExample {
// public:
//     // Guest methods as members (bound with NATIVE_METHOD, native/common/native_method.h):
//     void Ctor();                    // CExample::CExample()  _ZN8CExampleC2Ev (a C++ constructor can't be bound)
//     void Dtor();                    // CExample::~CExample() _ZN8CExampleD2Ev
//     u32 GetId() const;              // CExample::GetId() const
//     static CExample* Instance();    // a static member: bound with NATIVE_FUNCTION(sym, wrap<&CExample::Instance>(), ...)
//     // Virtuals in vtable order, as plain members: the object lives in guest memory with the guest's
//     // vtable, so no C++ `virtual` (a host vptr would change the layout); vtable is a field.
//     void Update(float dt);          // vtable slot 2  CExample::Update(float)
//
//     const void* vtable;  // 0x00: _ZTV8CExample + 0x10
//     u32 m_id;            // 0x08
//     u8 unk_0c[4];        // 0x0c: written by CExample::Reset, meaning unknown
//     u64 m_value;         // 0x10
// };
// static_assert(offsetof(CExample, m_id) == 0x08);
// static_assert(offsetof(CExample, m_value) == 0x10);
// static_assert(sizeof(CExample) == 0x18);

}  // namespace soa::native::data_formats

#endif  // SOA_NATIVE_DATA_FORMATS_LAYOUT_H
