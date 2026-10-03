// Twofish-128 (alg 0x08a723ab) of the sqex library: class vtable @02a9b2e8, ctor @01235718,
// key schedule @01235770 (q-boxes @01235e1c from the spec's nibble tables @027e1f57, MDS column
// tables @01235ee8, h @012361a4, RS @01235fc0, key-dependent S-boxes @012362f4), Encrypt
// @012358f4, Decrypt @01235b98, block encrypt @01236608 / decrypt @012366f8. 16-byte key = the
// first 16 bytes of the session key; block = four little-endian words; CBC is plain byte-wise
// CBC with the IV words stored little-endian (as for AES).
// QUIRKS (the client is NOT standard Twofish; verified against the client under unicorn):
//   - The MDS table for column 2 is built wrongly (@01235ee8): (y | e<<24) + (e<<8 | f) instead
//     of f | e<<8 | y<<16 | e<<24 (y = q1 output, e = 0xEF*y, f = 0x5B*y). It feeds both the
//     round-key derivation h() and the key-dependent S-boxes, so ciphertexts differ from the
//     spec (zero key/zero block: the spec gives 9F589F5C..., the client 16E64E35...).
//   - The Encrypt/Decrypt preamble skips (n & 31) + 1 generator outputs (handled in ninja_ref.cpp).
#include <cstring>

#include "ninja_ciphers.h"

namespace ninja::detail {
namespace {

const uint8_t kQt[2][4][16] = {
    {{0x8, 0x1, 0x7, 0xd, 0x6, 0xf, 0x3, 0x2, 0x0, 0xb, 0x5, 0x9, 0xe, 0xc, 0xa, 0x4},
     {0xe, 0xc, 0xb, 0x8, 0x1, 0x2, 0x3, 0x5, 0xf, 0x4, 0xa, 0x6, 0x7, 0x0, 0x9, 0xd},
     {0xb, 0xa, 0x5, 0xe, 0x6, 0xd, 0x9, 0x0, 0xc, 0x8, 0xf, 0x3, 0x2, 0x4, 0x7, 0x1},
     {0xd, 0x7, 0xf, 0x4, 0x1, 0x2, 0x6, 0xe, 0x9, 0xb, 0x3, 0x0, 0x8, 0x5, 0xc, 0xa}},
    {{0x2, 0x8, 0xb, 0xd, 0xf, 0x7, 0x6, 0xe, 0x3, 0x1, 0x9, 0x4, 0x0, 0xa, 0xc, 0x5},
     {0x1, 0xe, 0x2, 0xb, 0x4, 0xc, 0x3, 0x7, 0x6, 0xd, 0xa, 0x5, 0xf, 0x9, 0x0, 0x8},
     {0x4, 0xc, 0x7, 0x5, 0x1, 0x6, 0x9, 0xa, 0x0, 0xe, 0xd, 0x8, 0x2, 0xb, 0x3, 0xf},
     {0xb, 0x9, 0x5, 0x1, 0xc, 0x3, 0xd, 0xe, 0x6, 0x4, 0x7, 0xf, 0x2, 0x0, 0x8, 0xa}}};

uint8_t gf_mul(uint8_t a, uint8_t b, unsigned poly) {
    unsigned r = 0, x = a;
    for (; b; b >>= 1, x <<= 1)
        if (b & 1) r ^= x;
    for (int i = 15; i >= 8; i--)
        if (r & (1u << i)) r ^= poly << (i - 8);
    return (uint8_t)r;
}

struct Tables {
    uint8_t q[2][256];
    // MDS column i applied to its final q-box output (@01235ee8, Ghidra-addr object +0x10c).
    uint32_t col[4][256];
    Tables() {
        for (int t = 0; t < 2; t++)
            for (int x = 0; x < 256; x++) {
                uint8_t a0 = x >> 4, b0 = x & 15;
                uint8_t a1 = a0 ^ b0, b1 = (a0 ^ ((b0 >> 1) | (b0 << 3)) ^ (8 * a0)) & 15;
                uint8_t a2 = kQt[t][0][a1], b2 = kQt[t][1][b1];
                uint8_t a3 = a2 ^ b2, b3 = (a2 ^ ((b2 >> 1) | (b2 << 3)) ^ (8 * a2)) & 15;
                uint8_t a4 = kQt[t][2][a3], b4 = kQt[t][3][b3];
                q[t][x] = (uint8_t)(b4 << 4 | a4);
            }
        for (int x = 0; x < 256; x++) {
            for (int c = 0; c < 4; c++) {
                uint32_t y = q[(c & 1) ? 0 : 1][x];  // columns 0, 2: q1; 1, 3: q0
                uint32_t f = gf_mul((uint8_t)y, 0x5b, 0x169), e = gf_mul((uint8_t)y, 0xef, 0x169);
                switch (c) {
                case 0: col[0][x] = y | f << 8 | e << 16 | e << 24; break;  // standard
                case 1: col[1][x] = e | e << 8 | f << 16 | y << 24; break;  // standard
                // QUIRK (client bug): standard is f | e << 8 | y << 16 | e << 24; the client
                // builds (y | e << 24) + (e << 8 | f), so y lands in byte 0 (added, with carry).
                case 2: col[2][x] = (y | e << 24) + (e << 8 | f); break;
                case 3: col[3][x] = f | y << 8 | e << 16 | f << 24; break;  // standard
                }
            }
        }
    }
};
const Tables& tables() {
    static const Tables t;
    return t;
}

// h() for a 128-bit key (k = 2): L = {L0, L1}.
uint32_t h(uint32_t x, const uint32_t* L) {
    const auto& q = tables().q;
    uint8_t y[4];
    for (int i = 0; i < 4; i++) y[i] = (uint8_t)(x >> (8 * i));
    y[0] = q[0][q[0][y[0]] ^ (uint8_t)L[1]] ^ (uint8_t)L[0];
    y[1] = q[0][q[1][y[1]] ^ (uint8_t)(L[1] >> 8)] ^ (uint8_t)(L[0] >> 8);
    y[2] = q[1][q[0][y[2]] ^ (uint8_t)(L[1] >> 16)] ^ (uint8_t)(L[0] >> 16);
    y[3] = q[1][q[1][y[3]] ^ (uint8_t)(L[1] >> 24)] ^ (uint8_t)(L[0] >> 24);
    const auto& c = tables().col;
    return c[0][y[0]] ^ c[1][y[1]] ^ c[2][y[2]] ^ c[3][y[3]];
}

struct Twofish : Cipher {
    uint32_t K[40];
    uint32_t S[4][256];  // key-dependent S-boxes combined with the MDS columns

    explicit Twofish(const uint8_t* key) {
        block = 16;
        uint32_t Me[2] = {load_le32(key), load_le32(key + 8)}, Mo[2] = {load_le32(key + 4), load_le32(key + 12)};
        for (int i = 0; i < 20; i++) {
            uint32_t a = h(0x02020202u * (uint32_t)i, Me);
            uint32_t b = rotl32(h(0x02020202u * (uint32_t)i + 0x01010101u, Mo), 8);
            K[2 * i] = a + b;
            K[2 * i + 1] = rotl32(a + 2 * b, 9);
        }
        // S vector (RS code, GF(2^8) mod 0x14d), reversed order
        static const uint8_t RS[4][8] = {{0x01, 0xa4, 0x55, 0x87, 0x5a, 0x58, 0xdb, 0x9e},
                                         {0xa4, 0x56, 0x82, 0xf3, 0x1e, 0xc6, 0x68, 0xe5},
                                         {0x02, 0xa1, 0xfc, 0xc1, 0x47, 0xae, 0x3d, 0x19},
                                         {0xa4, 0x55, 0x87, 0x5a, 0x58, 0xdb, 0x9e, 0x03}};
        uint32_t Sv[2];
        for (int k = 0; k < 2; k++) {
            uint32_t v = 0;
            for (int i = 0; i < 4; i++) {
                uint8_t s = 0;
                for (int j = 0; j < 8; j++) s ^= gf_mul(RS[i][j], key[8 * k + j], 0x14d);
                v |= (uint32_t)s << (8 * i);
            }
            Sv[1 - k] = v;
        }
        // Key-dependent S-boxes (@012362f4): the same chains as h() with L = S vector.
        const auto& q = tables().q;
        const auto& c = tables().col;
        for (int x = 0; x < 256; x++) {
            uint8_t y = (uint8_t)x;
            S[0][x] = c[0][q[0][q[0][y] ^ (uint8_t)Sv[1]] ^ (uint8_t)Sv[0]];
            S[1][x] = c[1][q[0][q[1][y] ^ (uint8_t)(Sv[1] >> 8)] ^ (uint8_t)(Sv[0] >> 8)];
            S[2][x] = c[2][q[1][q[0][y] ^ (uint8_t)(Sv[1] >> 16)] ^ (uint8_t)(Sv[0] >> 16)];
            S[3][x] = c[3][q[1][q[1][y] ^ (uint8_t)(Sv[1] >> 24)] ^ (uint8_t)(Sv[0] >> 24)];
        }
    }

    uint32_t g0(uint32_t x) const { return S[0][x & 255] ^ S[1][(x >> 8) & 255] ^ S[2][(x >> 16) & 255] ^ S[3][x >> 24]; }
    uint32_t g1(uint32_t x) const { return g0(rotl32(x, 8)); }

    void enc(uint8_t* b) const {
        uint32_t r0 = load_le32(b) ^ K[0], r1 = load_le32(b + 4) ^ K[1], r2 = load_le32(b + 8) ^ K[2],
                 r3 = load_le32(b + 12) ^ K[3];
        for (int r = 0; r < 16; r += 2) {
            uint32_t t0 = g0(r0), t1 = g1(r1);
            r2 = rotr32(r2 ^ (t0 + t1 + K[2 * r + 8]), 1);
            r3 = rotl32(r3, 1) ^ (t0 + 2 * t1 + K[2 * r + 9]);
            t0 = g0(r2), t1 = g1(r3);
            r0 = rotr32(r0 ^ (t0 + t1 + K[2 * r + 10]), 1);
            r1 = rotl32(r1, 1) ^ (t0 + 2 * t1 + K[2 * r + 11]);
        }
        store_le32(b, r2 ^ K[4]), store_le32(b + 4, r3 ^ K[5]), store_le32(b + 8, r0 ^ K[6]),
            store_le32(b + 12, r1 ^ K[7]);
    }
    void dec(uint8_t* b) const {
        uint32_t r2 = load_le32(b) ^ K[4], r3 = load_le32(b + 4) ^ K[5], r0 = load_le32(b + 8) ^ K[6],
                 r1 = load_le32(b + 12) ^ K[7];
        for (int r = 14; r >= 0; r -= 2) {
            uint32_t t0 = g0(r2), t1 = g1(r3);
            r0 = rotl32(r0, 1) ^ (t0 + t1 + K[2 * r + 10]);
            r1 = rotr32(r1 ^ (t0 + 2 * t1 + K[2 * r + 11]), 1);
            t0 = g0(r0), t1 = g1(r1);
            r2 = rotl32(r2, 1) ^ (t0 + t1 + K[2 * r + 8]);
            r3 = rotr32(r3 ^ (t0 + 2 * t1 + K[2 * r + 9]), 1);
        }
        store_le32(b, r0 ^ K[0]), store_le32(b + 4, r1 ^ K[1]), store_le32(b + 8, r2 ^ K[2]),
            store_le32(b + 12, r3 ^ K[3]);
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

std::unique_ptr<Cipher> make_twofish(const uint8_t* key) { return std::make_unique<Twofish>(key); }

}  // namespace ninja::detail
