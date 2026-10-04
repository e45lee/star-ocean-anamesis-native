#pragma once
// The bundled OpenSSL pieces (1.0.x's AES): replaced by the host's libcrypto (vcpkg's OpenSSL) at the
// AES API the game calls (only Encrypt::CEncryptAES128::Encrypt / Decrypt do; port/decomp/lib_crypto/).
// AES_set_encrypt_key / AES_set_decrypt_key are 4-byte branches (through the PLT) to
// private_AES_set_*_key, which are the natives. These functions, with the guest's signatures, are
// the natives; the differential tests call them directly. README.md has the rules.
#include "native/common/lockstep.h"
#include "native/lib_crypto/lib_crypto_layout.h"

namespace soa::native::lib_crypto {

s32 set_encrypt_key(const u8* user_key, s32 bits, AesKey* key);
s32 set_decrypt_key(const u8* user_key, s32 bits, AesKey* key);
void cbc_encrypt(const u8* in, u8* out, u64 length, const AesKey* key, u8* ivec, s32 enc);

// The live check (--live-check lib_crypto) and, for its test, its originals (as lib_vorbis_api.h).
live::Lockstep& lockstep();
void use_originals(u64 (*sym)(const char*));

}  // namespace soa::native::lib_crypto
