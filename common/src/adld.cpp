// ADLD packing (soa/adld.h; moved to common/ from soa-server's cdn/adld.cpp). The decrypt half is
// the game's own; the encrypt half is ours.
#include "soa/adld.h"

// The low-level AES API on purpose: the game links OpenSSL's AES_cbc_encrypt, whose partial-block
// behaviour the port reproduces (deprecated since OpenSSL 3.0, still provided).
#define OPENSSL_SUPPRESS_DEPRECATED
#include <openssl/aes.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "soa/chash32.h"

namespace soa::adld {

const char* const kDefaultIV = "09375711857134629684891855841614";

namespace {
// Packs a 32-digit decimal string one digit per nibble. Each character goes through atoi() of a
// one-character string, as in the original, so non-digits become 0.
void pack_digits(const char* s, unsigned char out[16]) {
    std::memset(out, 0, 16);
    for (int i = 0; i < 32; i++) {
        char one[2] = {s[i], 0};
        auto v = (unsigned char)atoi(one);
        out[i / 2] |= (i & 1) ? v : (unsigned char)(v << 4);
    }
}
}  // namespace

int aes128_initialize(AES128* a, const char* key, const char* iv) {
    if (!iv) iv = kDefaultIV;
    if (!key || strlen(key) != 32) return -101;
    pack_digits(key, a->key);
    pack_digits(iv, a->iv);
    return 0;
}

int aes128_decrypt(const AES128* a, const void* src, uint32_t len, void* dst) {
    AES_KEY k;
    int r = AES_set_decrypt_key(a->key, 128, &k);
    unsigned char iv[16];
    std::memcpy(iv, a->iv, 16);
    AES_cbc_encrypt((const unsigned char*)src, (unsigned char*)dst, len, &k, iv, AES_DECRYPT);
    return r;
}

uint32_t aes128_encrypt(const AES128* a, const void* src, uint32_t len, void* dst) {
    AES_KEY k;
    AES_set_encrypt_key(a->key, 128, &k);
    unsigned char iv[16];
    std::memcpy(iv, a->iv, 16);
    uint32_t padded = (len + 15) & ~15u;
    if (padded == len) {
        AES_cbc_encrypt((const unsigned char*)src, (unsigned char*)dst, padded, &k, iv, AES_ENCRYPT);
    } else {
        std::vector<unsigned char> tmp(padded, 0);
        std::memcpy(tmp.data(), src, len);
        AES_cbc_encrypt(tmp.data(), (unsigned char*)dst, padded, &k, iv, AES_ENCRYPT);
    }
    return padded;
}

int decrypt_aes128(const char* key, const void* src, uint32_t len, void* dst, uint32_t dst_len) {
    if (dst_len < len) return -1;
    AES128 a{};
    aes128_initialize(&a, key, nullptr);
    return aes128_decrypt(&a, src, len, dst);
}

std::string xor_key(const char* name) {
    char key[16];
    snprintf(key, sizeof key, "%x", chash32(name));
    return key;
}
std::string aes_key(const char* name) {
    char key[64];
    snprintf(key, sizeof key, "%032u", chash32(name));
    return key;
}

void xor_payload(const char* name, const unsigned char* src, unsigned char* dst, uint64_t n) {
    std::string key = xor_key(name);
    size_t klen = key.size();
    for (uint64_t i = 0, j = 0; i < n; i++) {
        dst[i] = (unsigned char)key[j] ^ src[i];
        j = klen ? (j + 1) % klen : 0;
    }
}

bool dcne_header(const unsigned char* plain, uint64_t n, uint64_t* real) {
    if (n < 12) return false;
    uint32_t hdr[3];
    std::memcpy(hdr, plain, 12);
    if (hdr[0] != kDcneMagic || hdr[1] != 1) return false;
    *real = (uint64_t)hdr[2] - 16;
    return true;
}

bool is_adld(const uint8_t* data, size_t n) { return data && n >= 16 && memcmp(data, "ADLD", 4) == 0; }
uint32_t flags_of(const uint8_t* data, size_t n) {
    if (!is_adld(data, n)) return 0;
    uint32_t f;
    std::memcpy(&f, data + 4, 4);
    return f;
}

std::vector<uint8_t> decrypt(const std::string& name, const uint8_t* file, size_t n) {
    if (!is_adld(file, n)) return std::vector<uint8_t>(file, file + n);
    uint32_t flags = flags_of(file, n);
    uint64_t size = n - 16;
    std::vector<uint8_t> out(size);
    if (flags & kXor) {
        xor_payload(name.c_str(), file + 16, out.data(), size);
        return out;
    }
    if (!(flags & kAes)) {  // (neither flag: the game only drops the header size, keeping the bytes)
        std::memcpy(out.data(), file, size);
        return out;
    }
    // The game decrypts in place from a buffer with slack after it; a partial final block reads
    // zeros here.
    std::vector<uint8_t> src(file + 16, file + n);
    src.resize(size + 16, 0);
    out.resize(size + 16);
    decrypt_aes128(aes_key(name.c_str()).c_str(), src.data(), (uint32_t)size, out.data(), (uint32_t)size);
    out.resize(size);
    uint64_t real;
    if (dcne_header(out.data(), out.size(), &real) && real <= out.size() - 16)
        return std::vector<uint8_t>(out.begin() + 16, out.begin() + 16 + (ptrdiff_t)real);
    return out;
}

std::vector<uint8_t> encrypt(const std::string& name, const uint8_t* plain, size_t n, uint32_t flags) {
    std::vector<uint8_t> out(16, 0);
    std::memcpy(out.data(), "ADLD", 4);
    std::memcpy(out.data() + 4, &flags, 4);
    if (flags & kXor) {
        out.resize(16 + n);
        xor_payload(name.c_str(), plain, out.data() + 16, n);
        return out;
    }
    if (!(flags & kAes)) {
        out.insert(out.end(), plain, plain + n);
        return out;
    }
    // {"DCNE", 1, 16 + n, 0} + the plaintext, zero-padded to the AES block.
    std::vector<uint8_t> body(16 + n);
    uint32_t hdr[4] = {kDcneMagic, 1, (uint32_t)(16 + n), 0};
    std::memcpy(body.data(), hdr, 16);
    if (n) std::memcpy(body.data() + 16, plain, n);
    AES128 a{};
    aes128_initialize(&a, aes_key(name.c_str()).c_str(), nullptr);
    out.resize(16 + ((body.size() + 15) & ~(size_t)15));
    aes128_encrypt(&a, body.data(), (uint32_t)body.size(), out.data() + 16);
    return out;
}

}  // namespace soa::adld
