// lib_crypto_layout.h: the guest data layouts of the `lib_crypto` subsystem (the bundled OpenSSL pieces: the host libcrypto at the AES_* API).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/lib_crypto/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types lib_crypto` turns the structs into port/decomp/lib_crypto/types.json for Ghidra.
#ifndef SOA_NATIVE_LIB_CRYPTO_LAYOUT_H
#define SOA_NATIVE_LIB_CRYPTO_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::lib_crypto {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// OpenSSL 1.0's AES_KEY as the guest lays it out (AES_LONG undefined: 32-bit round keys): 0xf4 bytes.
// Encrypt::CEncryptAES128::Encrypt / Decrypt (port/decomp/lib_crypto/encrypt_aes.c) keep one on their
// stack between AES_set_*_key and AES_cbc_encrypt and never read it; so the host's (OpenSSL 3, the
// same struct; its round keys may be in another format, which only the host functions see) lives in
// place.
struct AesKey {
    u32 rd_key[60];  // 0x00: 4 * (AES_MAXNR + 1)
    s32 rounds;      // 0xf0
};
static_assert(offsetof(AesKey, rounds) == 0xf0 && sizeof(AesKey) == 0xf4);

// Encrypt::CEncryptAES128 (the caller, not native here): the key and the IV, one decimal digit per
// nibble of the strings CEncryptAES128::Initialize is given (docs/notes.md "Asset encryption (ADLD)").
struct CEncryptAES128 {
    u8 key[16];  // 0x00
    u8 iv[16];   // 0x10: copied for each Encrypt / Decrypt (CBC from it)
};
static_assert(offsetof(CEncryptAES128, iv) == 0x10 && sizeof(CEncryptAES128) == 0x20);

}  // namespace soa::native::lib_crypto

#endif  // SOA_NATIVE_LIB_CRYPTO_LAYOUT_H
