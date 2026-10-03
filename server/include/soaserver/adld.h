#pragma once
// ADLD: the game's packed-file format (library code). Every packed game file (scripts, texts,
// parameters, the master database, the downloaded assets) is "ADLD", u32 flags, 8 zero bytes, then
// the payload (docs/notes.md "Asset encryption (ADLD)"):
//   flags & 1: the payload XORed with the lowercase hex of CHash32(name), repeating;
//   flags & 2: AES-128-CBC with key = the digits of "%032u" % CHash32(name) and a fixed IV, both
//              packed one decimal digit per nibble; the plaintext may start with a "DCNE" v1 header
//              {"DCNE", 1, 16 + payload length, 0} (the master DB has one).
// `name` is the asset's logical path, e.g. "sqlite/basmaster.sqlite3" or "Script/1000_010.msgp".
//
// The decrypt half is the game's own (CGame::OnInitialize's CFileLoader callback and
// Encrypt::CEncryptAES128 / DecryptAES128); the port's natives for them use these functions
// (port/src/native/engine/asset_decrypt.cpp). The encrypt half is ours: soa-server's CDN packs the
// master DB it serves with it (cdn.h); encrypt(decrypt(x)) reproduces the 3.7.0 files byte for byte.
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace soa::server::adld {

constexpr uint32_t kXor = 1;  // ADLD flags / the manifests' encType
constexpr uint32_t kAes = 2;
constexpr uint32_t kDcneMagic = 0x454e4344;  // "DCNE"

// Encrypt::CEncryptAES128 { u8 key[16]; u8 iv[16]; } over OpenSSL's AES (the game links OpenSSL's
// AES_cbc_encrypt too, so partial trailing blocks behave identically).
struct AES128 {
    unsigned char key[16], iv[16];
};
extern const char* const kDefaultIV;  // "09375711857134629684891855841614"

// CEncryptAES128::Initialize(key, iv): 0, or -101 when the key isn't a 32-character string; a null
// iv is kDefaultIV. Each character goes through atoi() of a one-character string, as in the
// original, so non-digits pack as 0.
int aes128_initialize(AES128* a, const char* key, const char* iv);
// CEncryptAES128::Decrypt / Encrypt (CBC from the stored IV; Encrypt zero-pads to 16 and returns
// the padded length).
int aes128_decrypt(const AES128* a, const void* src, uint32_t len, void* dst);
uint32_t aes128_encrypt(const AES128* a, const void* src, uint32_t len, void* dst);
// int DecryptAES128(const char* key_digits, const u8* src, u32 len, u8* dst, u32 dst_len)
int decrypt_aes128(const char* key, const void* src, uint32_t len, void* dst, uint32_t dst_len);

// The keys of `name`: "%x" (XOR) and "%032u" (AES) of CHash32(name).
std::string xor_key(const char* name);
std::string aes_key(const char* name);
// dst[i] = key[i % len] ^ src[i] for i in [0, n), forwards (so dst may be src - 16: the callback
// decrypts in place).
void xor_payload(const char* name, const unsigned char* src, unsigned char* dst, uint64_t n);
// A decrypted AES payload starting with a DCNE v1 header: true, with the real length
// (u32 at +8, minus the 16-byte header) in *real.
bool dcne_header(const unsigned char* plain, uint64_t n, uint64_t* real);

// ---- whole files (host side: soa-server, tools, tests) ------------------------------------
bool is_adld(const uint8_t* data, size_t n);
// The flags of an ADLD file (0 when it isn't one).
uint32_t flags_of(const uint8_t* data, size_t n);
// The callback's result for `file` (a copy when it isn't ADLD; the AES path reads a partial final
// block as zeros, where the game reads past its buffer).
std::vector<uint8_t> decrypt(const std::string& name, const uint8_t* file, size_t n);
inline std::vector<uint8_t> decrypt(const std::string& name, const std::vector<uint8_t>& file) { return decrypt(name, file.data(), file.size()); }
// The ADLD file of `plain` with `flags` kXor or kAes (kAes: with the DCNE header, zero-padded to
// 16 bytes, as the 3.7.0 master is packed).
std::vector<uint8_t> encrypt(const std::string& name, const uint8_t* plain, size_t n, uint32_t flags);
inline std::vector<uint8_t> encrypt(const std::string& name, const std::vector<uint8_t>& plain, uint32_t flags) {
    return encrypt(name, plain.data(), plain.size(), flags);
}

}  // namespace soa::server::adld
