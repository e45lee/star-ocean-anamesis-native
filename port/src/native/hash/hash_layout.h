// hash_layout.h: the guest data layouts of the `hash` subsystem (Hashes: CHash32, SpookyHash V2, SHA-1 / MD5 / HMAC, CRC, UTF-8).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/hash/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types hash` turns the structs into port/decomp/hash/types.json for Ghidra.
//
// What other subsystems can rely on: CHash32 is the game's 32-bit name hash (ids of resources,
// parameters, master rows are these values): Framework::CHash32 is a 16-byte object {vptr, m_hash}
// and CHash32::Of(s, n) the value. Aska::Hash / Aska::Utf8 are free functions (namespaces here:
// the mangled names can't tell a namespace from a class of statics, and nothing has a `this`).
#ifndef SOA_NATIVE_HASH_LAYOUT_H
#define SOA_NATIVE_HASH_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "native/libcxx/libcxx_layout.h"

namespace soa::native::hash {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// The guest's std::string (basic_string<char, ..., Framework::CSTLAllocator<char, ...>>): the libcxx
// subsystem's layout.
using GuestString = libcxx::String;

// Framework::CHash32: guest size 0x10; layout from its constructors (port/decomp/hash/chash32.c:
// the vtable at +0, the hash at +8). The hash is a table CRC-32 (reflected 0xEDB88320, the
// table at vaddr 0x2863e48) seeded with the length, no final xor; 0 for an empty or null string.
// The guest's C1 / C2 constructors are one function at one address (bound once). The 4-byte
// destructors (D2: ret; D0: b operator delete) are too small to hook and stay guest code.
class CHash32 {
public:
    // The hash of n bytes (the loop every constructor and operator inlines).
    static u32 Of(const char* s, u64 n);
    static u32 OfCString(const char* s);  // strlen, then Of; 0 for null

    // Constructors (bound as Ctor: a C++ constructor can't be bound)
    void Ctor();                          // CHash32()  _ZN9Framework7CHash32C2Ev
    void Ctor(const char* s);             // CHash32(char const*)  _ZN9Framework7CHash32C2EPKc
    void Ctor(const char* s, u64 n);      // CHash32(char const*, unsigned long)  _ZN9Framework7CHash32C1EPKcm
    void Ctor(const GuestString& s);      // CHash32(std::string const&)
    void Ctor(u32 v);                     // CHash32(unsigned int): the hash of "%u"
    void Ctor(s32 v);                     // CHash32(int): also "%u" (the guest's format)
    // vtable slots 0 / 1: ~CHash32() (D2 / D0: guest code)
    u32 Get() const;                       // Get() const
    u32 ToU32() const;                     // operator unsigned int() const
    bool Eq(const CHash32& o) const;       // operator==(CHash32 const&) const
    bool Eq(const u32& v) const;           // operator==(unsigned int const&) const
    bool Ne(const CHash32& o) const;       // operator!=(CHash32 const&) const
    bool Ne(const u32& v) const;           // operator!=(unsigned int const&) const
    bool Lt(const CHash32& o) const;       // operator<(CHash32 const&) const
    bool Gt(const CHash32& o) const;       // operator>(CHash32 const&) const
    bool Lt(const char* s) const;          // operator<(char const*) const
    bool Gt(const char* s) const;          // operator>(char const*) const
    bool Lt(const u32& v) const;           // operator<(unsigned int const&) const: v < hash (sic)
    bool Gt(const u32& v) const;           // operator>(unsigned int const&) const: hash < v (sic)
    CHash32* Assign(const char* s);        // operator=(char const*): asserts on null
    void Assign(const GuestString& s);     // operator=(std::string const&) (returns nothing)

    u64 vtable;  // 0x00: _ZTVN9Framework7CHash32E + 0x10
    u32 m_hash;  // 0x08
    u8 pad_0c[4];  // 0x0c: alignment
};
static_assert(offsetof(CHash32, vtable) == 0x00);
static_assert(offsetof(CHash32, m_hash) == 0x08);
static_assert(sizeof(CHash32) == 0x10);

// Aska::detail::SpookyHashV2: guest size 0x130; Bob Jenkins' SpookyHash V2 (public domain), the
// reference class's layout (Init / Update / Final in port/decomp/hash/spooky.c use these offsets).
class SpookyHashV2 {
public:
    static constexpr int kNumVars = 12;
    static constexpr u64 kBlockSize = kNumVars * 8;  // 96
    static constexpr u64 kBufSize = 2 * kBlockSize;   // 192
    static constexpr u64 kConst = 0xdeadbeefdeadbeefull;

    // Static members (no `this`)
    static void Short(const void* message, u64 length, u64* hash1, u64* hash2);
    static void Hash128(const void* message, u64 length, u64* hash1, u64* hash2);
    static void Mix(const u64* data, u64& s0, u64& s1, u64& s2, u64& s3, u64& s4, u64& s5, u64& s6, u64& s7, u64& s8, u64& s9,
                    u64& s10, u64& s11);
    // Members
    void Init(u64 seed1, u64 seed2);
    void Update(const void* message, u64 length);
    void Final(u64* hash1, u64* hash2);

    u64 m_data[2 * kNumVars];  // 0x000: unhashed data, for partial messages
    u64 m_state[kNumVars];     // 0x0c0: internal state of the hash
    u64 m_length;              // 0x120: total length of the input so far
    u8 m_remainder;            // 0x128: length of unhashed data stashed in m_data
    u8 pad_129[7];             // 0x129
};
static_assert(offsetof(SpookyHashV2, m_state) == 0xc0);
static_assert(offsetof(SpookyHashV2, m_length) == 0x120);
static_assert(offsetof(SpookyHashV2, m_remainder) == 0x128);
static_assert(sizeof(SpookyHashV2) == 0x130);

// Aska::Hash: digests over a caller's buffers (port/decomp/hash/aska_hash.c).
namespace Hash {
// SHA-1 of data[0..len) (FIPS 180-4). The message is padded in `work` (at least
// ((len + 0x41) & ~0x3f) + 0x40 bytes, else 0 is returned; the padded message stays there), the
// 20-byte digest goes to `out` (outlen >= 20, else 0). Returns 20.
u64 SHA1(const char* data, u64 len, char* out, u64 outlen, char* work, u64 worklen);
// CRC-16/X-25 (reflected 0x8408, init 0xffff, final xor 0xffff) / CRC-32 (zlib's) of
// data[0..len); 0 for empty or null data. Returns the CRC's size in bytes (2 / 4).
u64 CRC(const u8* data, u64 len, u16* out);
u64 CRC(const u8* data, u64 len, u32* out);
}  // namespace Hash

// Aska::Utf8 (port/decomp/hash/utf8.c).
namespace Utf8 {
u64 GetByteSizeAt_(u8 lead);  // 1-4 by the lead byte; 0 for an invalid one
// UTF-8 to UCS-4 / UCS-2, at most n code units, stopping at a NUL; the count written.
u64 ToUcs4(char32_t* dst, const char* src, u64 n);
u64 ToUcs2(char16_t* dst, const char* src, u64 n);
}  // namespace Utf8

}  // namespace soa::native::hash

#endif  // SOA_NATIVE_HASH_LAYOUT_H
