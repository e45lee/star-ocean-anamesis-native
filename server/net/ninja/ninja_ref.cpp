// Reference implementation of the Ninja / sqex message envelope (see ninja_ref.h and
// docs/online-server.md §3 "Encryption (Ninja)"). Addresses below are Ghidra addresses (ELF vaddr + 0x100000)
// in the offline build's libSOA.so, where this was first read (380-ok); the code is identical in
// 3.7.0 (tools/genlib.py local_name / local map an unnamed function between builds; the cipher
// classes sit 0x24dc higher in 3.7.0).
#define OPENSSL_SUPPRESS_DEPRECATED
#include "ninja_ref.h"

#include <openssl/sha.h>

#include <cstring>
#include <random>

#include "ninja_ciphers.h"

namespace ninja {
using namespace detail;

const uint32_t kAllAlgs[10] = {kSEED, kAES128, kBlowfish, kCAST128, kCamellia128,
                               kSerpent, kTwofish, kIDEA, kMARS, kMISTY1};

const char* alg_name(uint32_t alg) {
    switch (alg) {
    case kSEED: return "SEED";
    case kAES128: return "AES128";
    case kBlowfish: return "Blowfish";
    case kCAST128: return "CAST128";
    case kCamellia128: return "Camellia128";
    case kSerpent: return "Serpent";
    case kTwofish: return "Twofish";
    case kIDEA: return "IDEA";
    case kMARS: return "MARS";
    case kMISTY1: return "MISTY1";
    }
    return nullptr;
}

namespace {

uint32_t bswap32(uint32_t v) { return __builtin_bswap32(v); }

// The per-algorithm IV generator (SqexEncryptionAlgorithm+0x20, created by @0123add0 from the
// table @027e3060 indexed by (r2 + alg) & 1): 0 -> XorShift128, 1 -> MT19937. Reseeded with r2
// at the start of every Encrypt/Decrypt (vtable +0x20).
struct Rng {
    bool mt = false;
    std::mt19937 m;          // MT19937 seed @0123b0e4 = init_genrand; next @0123b26c (standard)
    uint32_t x, y, z, w;     // XorShift128 seed @0123b430, next @0123b4cc
    Rng(uint32_t alg, uint32_t r2) : mt(((r2 + alg) & 1) != 0) {
        if (mt) {
            m.seed(r2);
        } else {
            auto f = [](uint32_t s) { return (s ^ s >> 30) * 0x6c078965u; };
            x = f(r2);
            y = f(x) + 1;
            z = f(y) + 2;
            w = f(z) + 3;
        }
    }
    uint32_t next() {
        if (mt) return (uint32_t)m();
        uint32_t t = x ^ x << 11;
        t = t ^ t >> 8 ^ w ^ w >> 19;
        x = y, y = z, z = w, w = t;
        return t;
    }
};

std::unique_ptr<Cipher> make_cipher(uint32_t alg, const uint8_t* key) {
    switch (alg) {
    case kSEED: return make_seed(key);
    case kAES128: return make_aes128(key);
    case kBlowfish: return make_blowfish(key);
    case kCAST128: return make_cast128(key);
    case kCamellia128: return make_camellia128(key);
    case kSerpent: return make_serpent(key);
    case kTwofish: return make_twofish(key);
    case kIDEA: return make_idea(key);
    case kMARS: return make_mars(key);
    case kMISTY1: return make_misty1(key);
    }
    return nullptr;
}

// Common start of every class's Encrypt / Decrypt (e.g. AES @01227e24 / @012280a0):
// seed(r2); n = next(); skip (n & k) + 1 outputs; IV = next() x block/4; length mask = next().
// k is 0x3f for Serpent (@01231f08), 0x1f for MARS (@0122c5e8) and Twofish (@012358f4), 0xf
// for the other classes.
struct Stream {
    uint32_t iv[4] = {};
    uint32_t mask = 0;
    Stream(uint32_t alg, uint32_t r2, size_t block) {
        Rng g(alg, r2);
        uint32_t n = g.next();
        uint32_t k = alg == kSerpent ? 0x3f : (alg == kMARS || alg == kTwofish) ? 0x1f : 0xf;
        for (uint32_t i = 0; i < (n & k) + 1; i++) g.next();
        for (size_t i = 0; i < block / 4; i++) iv[i] = g.next();
        mask = g.next();
    }
};

// Keyed digest of the trailer (@01227238): two SHA-256 passes with the 32-byte key XOR 0x5c,
// then XOR 0x36, each prepended as a 32-byte block (an HMAC-like construction with the pads
// swapped and a 32-byte block; a missing key counts as 32 zero bytes).
void keyed_digest(const uint8_t key[kKeySize], const uint8_t* msg, size_t n, uint8_t out[32]) {
    std::vector<uint8_t> b(32 + n);
    for (int i = 0; i < 32; i++) b[i] = key[i] ^ 0x5c;
    memcpy(b.data() + 32, msg, n);
    uint8_t h1[32];
    SHA256(b.data(), b.size(), h1);
    uint8_t c[64];
    for (int i = 0; i < 32; i++) c[i] = key[i] ^ 0x36;
    memcpy(c + 32, h1, 32);
    SHA256(c, 64, out);
}

// Trailer words (@01227014 write / @01227a40 check): BE32 digest word, rotated by the salt
// (right when salt bit 0 is clear, left otherwise), stored BE32.
void make_trailer(const uint8_t key[kKeySize], const uint8_t* env, size_t body_end, uint32_t salt, uint8_t out[32]) {
    uint8_t d[32];
    keyed_digest(key, env, body_end, d);
    for (int i = 0; i < 8; i++) {
        uint32_t v = load_be32(d + 4 * i);
        v = (salt & 1) ? rotl32(v, salt) : rotr32(v, salt);
        store_be32(out + 4 * i, v);
    }
}

// Header (@01226ec4). The fields are scattered over the 24 bytes; S = salt,
// M' = bswap(first MT19937(r2) output), A' = bswap(alg), R' = bswap(r2):
//   S          -> bytes 0, 6, 12, 18 (little-endian order)
//   rotr(0xbaabbaab ^ S, S)  -> 5, 11, 17, 23   (signature: bswap(S ^ rotl(x, S)) == 0xabbaabba)
//   rotl(0x11010000 ^ S, S)  -> 1, 7, 13, 19    (version: bswap(S ^ rotr(x, S)) == 0x111)
//   M' ^ A'    -> 3, 9, 15, 21
//   ~M' bytes 0..3 -> 8, 14, 2, 20
//   R' bytes 0..3 XOR M' bytes 3, 2, 1, 0 -> 4, 10, 16, 22
void write_header(uint8_t* h, uint32_t alg, uint32_t r2, uint32_t salt) {
    std::mt19937 mt(r2);  // SqexEncryptionAlgorithm ctor @0123bed8: MT19937(r2) first output
    uint32_t m = bswap32((uint32_t)mt());
    uint32_t a = bswap32(alg), r = bswap32(r2), s = salt;
    uint32_t sig = rotr32(0xbaabbaabu ^ s, s);
    uint32_t ver = rotl32(0x11010000u ^ s, s);
    uint32_t p = m ^ a;
    auto B = [](uint32_t v, int i) { return (uint8_t)(v >> (8 * i)); };
    const int sp[4] = {0, 6, 12, 18}, gp[4] = {5, 11, 17, 23}, vp[4] = {1, 7, 13, 19}, pp[4] = {3, 9, 15, 21};
    for (int i = 0; i < 4; i++) {
        h[sp[i]] = B(s, i);
        h[gp[i]] = B(sig, i);
        h[vp[i]] = B(ver, i);
        h[pp[i]] = B(p, i);
    }
    h[8] = (uint8_t)~B(m, 0), h[14] = (uint8_t)~B(m, 1), h[2] = (uint8_t)~B(m, 2), h[20] = (uint8_t)~B(m, 3);
    h[4] = B(m, 3) ^ B(r, 0), h[10] = B(m, 2) ^ B(r, 1), h[16] = B(m, 1) ^ B(r, 2), h[22] = B(m, 0) ^ B(r, 3);
}

uint32_t gather(const uint8_t* h, int a, int b, int c, int d) {
    return (uint32_t)h[a] | (uint32_t)h[b] << 8 | (uint32_t)h[c] << 16 | (uint32_t)h[d] << 24;
}

}  // namespace

bool parse_header(const uint8_t* e, size_t n, Header* h) {
    if (n < kHeaderSize) return false;
    h->salt = gather(e, 0, 6, 12, 18);
    h->signature = bswap32(h->salt ^ rotl32(gather(e, 5, 11, 17, 23), h->salt));  // @01227950
    h->version = bswap32(h->salt ^ rotr32(gather(e, 1, 7, 13, 19), h->salt));     // @012279cc
    auto nx = [&](int a, int b) { return (uint32_t)(uint8_t)~(e[a] ^ e[b]); };
    h->alg = bswap32(nx(3, 8) | nx(9, 14) << 8 | nx(15, 2) << 16 | nx(21, 20) << 24);  // @0122786c
    h->r2 = bswap32(nx(4, 20) | nx(10, 2) << 8 | nx(16, 14) << 16 | nx(22, 8) << 24);  // @012278f8
    h->mt = bswap32((uint32_t)(uint8_t)~e[8] | (uint32_t)(uint8_t)~e[14] << 8 | (uint32_t)(uint8_t)~e[2] << 16 |
                    (uint32_t)(uint8_t)~e[20] << 24);
    return true;
}

std::vector<uint8_t> encrypt(const uint8_t key[kKeySize], uint32_t alg, uint32_t r2, uint32_t salt,
                             const uint8_t* plain, size_t n) {
    auto c = make_cipher(alg, key);
    if (!c || n == 0) return {};
    size_t padded = (n + c->block - 1) & ~(c->block - 1);
    std::vector<uint8_t> env(kHeaderSize + 4 + padded + kTrailerSize);
    uint8_t* body = env.data() + kHeaderSize;
    Stream st(alg, r2, c->block);
    store_be32(body, (uint32_t)n ^ st.mask);
    memcpy(body + 4, plain, n);
    memset(body + 4 + n, 0xff, padded - n);  // padding @0123c268
    c->encrypt_cbc(st.iv, body + 4, padded);
    write_header(env.data(), alg, r2, salt);
    make_trailer(key, env.data(), env.size() - kTrailerSize, salt, env.data() + env.size() - kTrailerSize);
    return env;
}

int decrypt(const uint8_t key[kKeySize], const uint8_t* env, size_t n, std::vector<uint8_t>* plain,
            uint32_t* alg_out) {
    Header h;
    if (n < kHeaderSize + kTrailerSize || !parse_header(env, n, &h)) return kErrBadEnvelope;
    if (alg_out) *alg_out = h.alg;
    auto c = make_cipher(h.alg, key);
    if (!c || h.signature != 0xabbaabbau) return kErrBadEnvelope;
    uint8_t t[32];
    make_trailer(key, env, n - kTrailerSize, h.salt, t);
    if (memcmp(t, env + n - kTrailerSize, 32) != 0) return kErrMac;
    if (h.version != 0x111) return kErrBadEnvelope;
    size_t body = n - kHeaderSize - kTrailerSize;
    // AES (@012280a0): body >= 20 and (body - 4) % 16 == 0; the 8-byte-block classes likewise.
    if (body < 4 + c->block || (body - 4) % c->block) return kErrLength;
    Stream st(h.alg, h.r2, c->block);
    std::vector<uint8_t> d(env + kHeaderSize + 4, env + kHeaderSize + body);
    c->decrypt_cbc(st.iv, d.data(), d.size());
    uint32_t len = load_be32(env + kHeaderSize) ^ st.mask;
    if (len > d.size()) return kErrLength;  // the client does not check this (it trusts the length)
    d.resize(len);
    if (plain) *plain = std::move(d);
    return kOk;
}

}  // namespace ninja
