// lib_zstd_layout.h: the guest data layouts of the `lib_zstd` subsystem (zstd: the host library at the ZSTD_* API).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/lib_zstd/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types lib_zstd` turns the structs into port/decomp/lib_zstd/types.json for Ghidra.
#ifndef SOA_NATIVE_LIB_ZSTD_LAYOUT_H
#define SOA_NATIVE_LIB_ZSTD_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::lib_zstd {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// Aska::ZSTDInBuffer / Aska::ZSTDOutBuffer: the game's names for zstd's ZSTD_inBuffer / ZSTD_outBuffer
// (Aska::DecompressStreamZSTD(void**, ZSTDOutBuffer*, ZSTDInBuffer*) passes them straight to
// ZSTD_decompressStream; port/decomp/lib_zstd/aska_zstd.c, decode_main.c). Plain C structs, the same on
// every host (size_t is 64-bit on Windows too): the host's ZSTD_inBuffer / ZSTD_outBuffer.
struct ZSTDInBuffer {
    const void* src;  // 0x00
    u64 size;         // 0x08
    u64 pos;          // 0x10
};
struct ZSTDOutBuffer {
    void* dst;  // 0x00
    u64 size;   // 0x08
    u64 pos;    // 0x10
};
static_assert(offsetof(ZSTDInBuffer, size) == 0x08 && offsetof(ZSTDInBuffer, pos) == 0x10 && sizeof(ZSTDInBuffer) == 0x18);
static_assert(offsetof(ZSTDOutBuffer, size) == 0x08 && offsetof(ZSTDOutBuffer, pos) == 0x10 && sizeof(ZSTDOutBuffer) == 0x18);

}  // namespace soa::native::lib_zstd

#endif  // SOA_NATIVE_LIB_ZSTD_LAYOUT_H
