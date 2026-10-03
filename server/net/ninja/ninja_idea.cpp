// IDEA class of the sqex library (alg 0x0951fad3; Ghidra addresses in libSOA.so 3.7.0: ctor
// @0122da24, vtable @02a95978, Encrypt @0122dd18, Decrypt @0122df48, block encrypt @0122e184 /
// decrypt @0122e3cc, key schedule @0122da7c). Standard IDEA (16-bit words big-endian) with the
// first 16 bytes of the session key. The class's CBC loop is plain CBC over bytes; the chaining
// value starts as the two generator words stored little-endian.
#include <cstring>

#include "ninja_ciphers.h"

namespace ninja::detail {
namespace {

uint16_t mul(uint16_t a, uint16_t b) {
    if (!a) return (uint16_t)(1 - b);
    if (!b) return (uint16_t)(1 - a);
    uint32_t p = (uint32_t)a * b;
    uint16_t lo = (uint16_t)p, hi = (uint16_t)(p >> 16);
    return (uint16_t)(lo - hi + (lo < hi));
}
uint16_t inv(uint16_t x) {  // multiplicative inverse mod 65537 (0 stands for 65536; inv(0)=0, inv(1)=1)
    if (x <= 1) return x;
    int64_t t0 = 0, t1 = 1, r0 = 0x10001, r1 = x;
    while (r1) {
        int64_t q = r0 / r1, t;
        t = r0 - q * r1, r0 = r1, r1 = t;
        t = t0 - q * t1, t0 = t1, t1 = t;
    }
    return (uint16_t)(t0 < 0 ? t0 + 0x10001 : t0);
}

struct Idea : Cipher {
    uint16_t ek[52], dk[52];
    explicit Idea(const uint8_t* key) {
        block = 8;
        for (int i = 0; i < 8; i++) ek[i] = (uint16_t)(key[2 * i] << 8 | key[2 * i + 1]);
        for (int i = 8; i < 52; i++) {
            int j = i & ~7, k = i & 7;  // rotate the 128-bit key left by 25 bits per group of 8
            ek[i] = (uint16_t)(ek[j - 8 + ((k + 1) & 7)] << 9 | ek[j - 8 + ((k + 2) & 7)] >> 7);
        }
        // decryption subkeys
        int p = 0;
        for (int r = 8; r >= 0; r--) {
            const uint16_t* k = ek + 6 * r;
            dk[p++] = inv(k[0]);
            if (r == 8 || r == 0) {
                dk[p++] = (uint16_t)-k[1];
                dk[p++] = (uint16_t)-k[2];
            } else {
                dk[p++] = (uint16_t)-k[2];
                dk[p++] = (uint16_t)-k[1];
            }
            dk[p++] = inv(k[3]);
            if (r > 0) {
                dk[p++] = ek[6 * (r - 1) + 4];
                dk[p++] = ek[6 * (r - 1) + 5];
            }
        }
    }
    static void crypt(const uint16_t* k, uint8_t* b) {
        uint16_t x1 = (uint16_t)(b[0] << 8 | b[1]), x2 = (uint16_t)(b[2] << 8 | b[3]);
        uint16_t x3 = (uint16_t)(b[4] << 8 | b[5]), x4 = (uint16_t)(b[6] << 8 | b[7]);
        for (int r = 0; r < 8; r++, k += 6) {
            x1 = mul(x1, k[0]);
            x2 = (uint16_t)(x2 + k[1]);
            x3 = (uint16_t)(x3 + k[2]);
            x4 = mul(x4, k[3]);
            uint16_t t0 = mul((uint16_t)(x1 ^ x3), k[4]);
            uint16_t t1 = mul((uint16_t)(t0 + (x2 ^ x4)), k[5]);
            t0 = (uint16_t)(t0 + t1);
            x1 ^= t1, x4 ^= t0;
            uint16_t t = (uint16_t)(x2 ^ t0);
            x2 = (uint16_t)(x3 ^ t1), x3 = t;
        }
        uint16_t y1 = mul(x1, k[0]), y2 = (uint16_t)(x3 + k[1]), y3 = (uint16_t)(x2 + k[2]), y4 = mul(x4, k[3]);
        b[0] = (uint8_t)(y1 >> 8), b[1] = (uint8_t)y1, b[2] = (uint8_t)(y2 >> 8), b[3] = (uint8_t)y2;
        b[4] = (uint8_t)(y3 >> 8), b[5] = (uint8_t)y3, b[6] = (uint8_t)(y4 >> 8), b[7] = (uint8_t)y4;
    }
    void encrypt_cbc(const uint32_t* iv, uint8_t* d, size_t n) const override {
        uint8_t c[8];
        store_le32(c, iv[0]), store_le32(c + 4, iv[1]);
        for (size_t o = 0; o < n; o += 8) {
            for (int i = 0; i < 8; i++) d[o + i] ^= c[i];
            crypt(ek, d + o);
            memcpy(c, d + o, 8);
        }
    }
    void decrypt_cbc(const uint32_t* iv, uint8_t* d, size_t n) const override {
        uint8_t c[8], nc[8];
        store_le32(c, iv[0]), store_le32(c + 4, iv[1]);
        for (size_t o = 0; o < n; o += 8) {
            memcpy(nc, d + o, 8);
            crypt(dk, d + o);
            for (int i = 0; i < 8; i++) d[o + i] ^= c[i];
            memcpy(c, nc, 8);
        }
    }
};

}  // namespace

std::unique_ptr<Cipher> make_idea(const uint8_t* key) { return std::make_unique<Idea>(key); }

}  // namespace ninja::detail
