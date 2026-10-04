// lib_sqlite_layout.h: the guest data layouts of the `lib_sqlite` subsystem (SQLite 3.13.0 (the game's bundled copy) replaced by the host SQLite).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/lib_sqlite/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types lib_sqlite` turns the structs into port/decomp/lib_sqlite/types.json for Ghidra.
#ifndef SOA_NATIVE_LIB_SQLITE_LAYOUT_H
#define SOA_NATIVE_LIB_SQLITE_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::lib_sqlite {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// No guest layouts: the boundary is SQLite's C API, whose handles (sqlite3*, sqlite3_stmt*,
// sqlite3_value*) the game's code only passes back to SQLite (Aska::Yayoi::SQLiteDriver keeps them at
// +0x18 / +0x20 and in its EntityObject; port/src/native/lib_sqlite/README.md). They are host SQLite
// objects now; nothing of 3.13.0's internal structs is read by guest code.

}  // namespace soa::native::lib_sqlite

#endif  // SOA_NATIVE_LIB_SQLITE_LAYOUT_H
