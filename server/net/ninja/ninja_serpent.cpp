// Serpent (128-bit key) of the sqex library: class vtable @02a95ab8, ctor @01232f68, key
// schedule @01232fc0, Encrypt @012343e4 / Decrypt @01234680, block @01234980 / @01236288
// (Ghidra addresses, libSOA.so 3.7.0).
// Standard Serpent (the AES-finalist / NESSIE convention: little-endian words, key padded
// with a 1 bit after the 128 key bits). The class runs plain CBC over the bytes; the chaining
// state starts as the four IV words stored little-endian (like the AES class).
#include <cstring>

#include "ninja_ciphers.h"

namespace ninja::detail {
namespace {

const uint8_t kS[8][16] = {
    {3, 8, 15, 1, 10, 6, 5, 11, 14, 13, 4, 2, 7, 0, 9, 12},
    {15, 12, 2, 7, 9, 0, 5, 10, 1, 11, 14, 8, 6, 13, 3, 4},
    {8, 6, 7, 9, 3, 12, 10, 15, 13, 1, 14, 4, 0, 11, 5, 2},
    {0, 15, 11, 8, 12, 9, 6, 3, 13, 1, 2, 4, 10, 7, 5, 14},
    {1, 15, 8, 3, 12, 0, 11, 6, 2, 5, 4, 10, 9, 14, 7, 13},
    {15, 5, 2, 11, 4, 10, 9, 12, 0, 3, 14, 8, 13, 6, 7, 1},
    {7, 2, 12, 5, 8, 4, 6, 11, 14, 9, 1, 15, 13, 3, 10, 0},
    {1, 13, 15, 0, 14, 8, 2, 11, 7, 4, 12, 10, 9, 3, 5, 6},
};

// Applies a 4-bit S-box bitwise across the four words (bitslice form).
void sbox(const uint8_t* s, uint32_t* x) {
    uint32_t y[4] = {};
    for (int j = 0; j < 32; j++) {
        unsigned v = (x[0] >> j & 1) | (x[1] >> j & 1) << 1 | (x[2] >> j & 1) << 2 | (x[3] >> j & 1) << 3;
        v = s[v];
        for (int k = 0; k < 4; k++) y[k] |= (uint32_t)(v >> k & 1) << j;
    }
    memcpy(x, y, sizeof y);
}

struct Serpent : Cipher {
    uint32_t k[33][4];
    uint8_t inv[8][16];
    explicit Serpent(const uint8_t* key) {
        block = 16;
        uint32_t w[140] = {};
        for (int i = 0; i < 4; i++) w[i] = load_le32(key + 4 * i);
        w[4] = 1;
        for (int i = 0; i < 132; i++)
            w[i + 8] = rotl32(w[i] ^ w[i + 3] ^ w[i + 5] ^ w[i + 7] ^ 0x9e3779b9u ^ (uint32_t)i, 11);
        for (int i = 0; i < 33; i++) {
            memcpy(k[i], &w[8 + 4 * i], 16);
            sbox(kS[(3 - i + 32) % 8], k[i]);
        }
        for (int s = 0; s < 8; s++)
            for (int v = 0; v < 16; v++) inv[s][kS[s][v]] = (uint8_t)v;
    }
    void enc(uint8_t* b) const {
        uint32_t x[4];
        for (int i = 0; i < 4; i++) x[i] = load_le32(b + 4 * i);
        for (int r = 0; r < 32; r++) {
            for (int i = 0; i < 4; i++) x[i] ^= k[r][i];
            sbox(kS[r % 8], x);
            if (r == 31) {
                for (int i = 0; i < 4; i++) x[i] ^= k[32][i];
            } else {
                x[0] = rotl32(x[0], 13), x[2] = rotl32(x[2], 3);
                x[1] ^= x[0] ^ x[2], x[3] ^= x[2] ^ x[0] << 3;
                x[1] = rotl32(x[1], 1), x[3] = rotl32(x[3], 7);
                x[0] ^= x[1] ^ x[3], x[2] ^= x[3] ^ x[1] << 7;
                x[0] = rotl32(x[0], 5), x[2] = rotl32(x[2], 22);
            }
        }
        for (int i = 0; i < 4; i++) store_le32(b + 4 * i, x[i]);
    }
    void dec(uint8_t* b) const {
        uint32_t x[4];
        for (int i = 0; i < 4; i++) x[i] = load_le32(b + 4 * i);
        for (int r = 31; r >= 0; r--) {
            if (r == 31) {
                for (int i = 0; i < 4; i++) x[i] ^= k[32][i];
            } else {
                x[2] = rotr32(x[2], 22), x[0] = rotr32(x[0], 5);
                x[2] ^= x[3] ^ x[1] << 7, x[0] ^= x[1] ^ x[3];
                x[3] = rotr32(x[3], 7), x[1] = rotr32(x[1], 1);
                x[3] ^= x[2] ^ x[0] << 3, x[1] ^= x[0] ^ x[2];
                x[2] = rotr32(x[2], 3), x[0] = rotr32(x[0], 13);
            }
            sbox(inv[r % 8], x);
            for (int i = 0; i < 4; i++) x[i] ^= k[r][i];
        }
        for (int i = 0; i < 4; i++) store_le32(b + 4 * i, x[i]);
    }
    void encrypt_cbc(const uint32_t* iv, uint8_t* d, size_t n) const override {
        uint8_t c[16];
        for (int i = 0; i < 4; i++) store_le32(c + 4 * i, iv[i]);
        for (size_t o = 0; o < n; o += 16) {
            for (int i = 0; i < 16; i++) d[o + i] ^= c[i];
            enc(d + o);
            memcpy(c, d + o, 16);
        }
    }
    void decrypt_cbc(const uint32_t* iv, uint8_t* d, size_t n) const override {
        uint8_t c[16], nc[16];
        for (int i = 0; i < 4; i++) store_le32(c + 4 * i, iv[i]);
        for (size_t o = 0; o < n; o += 16) {
            memcpy(nc, d + o, 16);
            dec(d + o);
            for (int i = 0; i < 16; i++) d[o + i] ^= c[i];
            memcpy(c, nc, 16);
        }
    }
};

}  // namespace

std::unique_ptr<Cipher> make_serpent(const uint8_t* key) { return std::make_unique<Serpent>(key); }

}  // namespace ninja::detail
