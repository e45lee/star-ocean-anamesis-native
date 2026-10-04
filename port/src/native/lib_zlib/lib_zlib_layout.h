// lib_zlib_layout.h: the guest data layouts of the `lib_zlib` subsystem (zlib 1.2.5: the host library at the inflate / deflate API).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/lib_zlib/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types lib_zlib` turns the structs into port/decomp/lib_zlib/types.json for Ghidra.
#ifndef SOA_NATIVE_LIB_ZLIB_LAYOUT_H
#define SOA_NATIVE_LIB_ZLIB_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::lib_zlib {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// z_stream as the guest (AArch64 LP64, zlib 1.2.5) lays it out: 0x70 bytes, the size the game passes
// to inflateInit2_ (port/decomp/lib_zlib/aska_compress.c: AskaUncompress*, on their stack). The host's
// z_stream is the same on Linux, but on Windows uLong is 32-bit (88 bytes, other offsets), so the
// natives never hand this struct to the host library: each stream has a host twin (a host z_stream),
// and the fields are copied across around every call (lib_zlib_api.cpp).
struct ZStream {
    const u8* next_in;  // 0x00
    u32 avail_in;       // 0x08
    u8 pad_0c[4];       // 0x0c
    u64 total_in;       // 0x10
    u8* next_out;       // 0x18
    u32 avail_out;      // 0x20
    u8 pad_24[4];       // 0x24
    u64 total_out;      // 0x28: read by AskaUncompress* (the decompressed size)
    const char* msg;    // 0x30
    void* state;        // 0x38: the library's private state; here the host twin
    u64 zalloc;         // 0x40: guest function pointers (the game passes 0: the library's default)
    u64 zfree;          // 0x48
    u64 opaque;         // 0x50
    s32 data_type;      // 0x58
    u8 pad_5c[4];       // 0x5c
    u64 adler;          // 0x60
    u64 reserved;       // 0x68
};
static_assert(offsetof(ZStream, avail_in) == 0x08 && offsetof(ZStream, total_in) == 0x10 && offsetof(ZStream, next_out) == 0x18);
static_assert(offsetof(ZStream, avail_out) == 0x20 && offsetof(ZStream, total_out) == 0x28 && offsetof(ZStream, msg) == 0x30);
static_assert(offsetof(ZStream, state) == 0x38 && offsetof(ZStream, zalloc) == 0x40 && offsetof(ZStream, data_type) == 0x58);
static_assert(offsetof(ZStream, adler) == 0x60 && sizeof(ZStream) == 0x70);

}  // namespace soa::native::lib_zlib

#endif  // SOA_NATIVE_LIB_ZLIB_LAYOUT_H
