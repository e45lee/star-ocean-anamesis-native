// Aska::Hash: SHA-1 and the CRCs over a caller's buffers (hash_layout.h; port/decomp/hash/aska_hash.c).
// SHA-1 is FIPS 180-4's, written from the standard; the buffer protocol (size checks, the padded
// message left in `work`) is the guest's. MD5, the HMACs, RSA_SHA1 and the IStream variants don't
// run in the profiled flows and stay guest code (port/decomp/hash/symbols.tsv: skip).
#include <cstring>

#include "native/hash/hash_family.h"
#include "native/hash/hash_layout.h"

namespace soa::native::hash {

namespace {

template <typename T, T kPoly>
struct ReflectedCrcTable {
    T t[256];
    constexpr ReflectedCrcTable() : t{} {
        for (u32 i = 0; i < 256; i++) {
            T c = (T)i;
            for (int k = 0; k < 8; k++) c = (c & 1) ? (T)((c >> 1) ^ kPoly) : (T)(c >> 1);
            t[i] = c;
        }
    }
};
// The guest's tables: CRC-16 at vaddr 0x2872808, CRC-32 at 0x2872a08 (test hash/crc-tables).
constexpr ReflectedCrcTable<u16, 0x8408> kCrc16;
constexpr ReflectedCrcTable<u32, 0xEDB88320u> kCrc32;

inline u32 rol(u32 x, int k) { return (x << k) | (x >> (32 - k)); }

// One 64-byte block of SHA-1 (FIPS 180-4, 6.1.2).
void sha1_block(u32 h[5], const u8* p) {
    u32 w[80];
    for (int t = 0; t < 16; t++) w[t] = (u32)p[4 * t] << 24 | (u32)p[4 * t + 1] << 16 | (u32)p[4 * t + 2] << 8 | p[4 * t + 3];
    for (int t = 16; t < 80; t++) w[t] = rol(w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16], 1);
    u32 a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];
    for (int t = 0; t < 80; t++) {
        u32 f, k;
        if (t < 20) f = (b & c) | (~b & d), k = 0x5a827999;
        else if (t < 40) f = b ^ c ^ d, k = 0x6ed9eba1;
        else if (t < 60) f = (b & c) | (b & d) | (c & d), k = 0x8f1bbcdc;
        else f = b ^ c ^ d, k = 0xca62c1d6;
        u32 tmp = rol(a, 5) + f + e + k + w[t];
        e = d, d = c, c = rol(b, 30), b = a, a = tmp;
    }
    h[0] += a, h[1] += b, h[2] += c, h[3] += d, h[4] += e;
}

}  // namespace

const u16* crc16_table() { return kCrc16.t; }
const u32* crc32_table() { return kCrc32.t; }

u64 Hash::SHA1(const char* data, u64 len, char* out, u64 outlen, char* work, u64 worklen) {
    u64 total = (len + 0x41) & ~(u64)0x3f;  // the padded length: a 0x80 byte and the 8-byte length fit
    if (outlen < 20 || worklen < total + 0x40) return 0;
    s64 zeros = (s64)(total - len) - 8;     // (the 0x80 byte and the zero fill before the length)
    if (zeros < 1) {
        total += 0x40;
        zeros = (s64)(total - len) - 8;
    }
    u8* w = reinterpret_cast<u8*>(work);
    std::memcpy(w, data, len);
    std::memset(w + len, 0, (u64)zeros);
    w[len] = 0x80;
    u64 bits = len << 3;
    for (int i = 0; i < 8; i++) w[len + zeros + i] = (u8)(bits >> (56 - 8 * i));
    u32 h[5] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0};
    for (u64 off = 0; off < total; off += 64) sha1_block(h, w + off);
    u8* o = reinterpret_cast<u8*>(out);
    for (int i = 0; i < 5; i++) o[4 * i] = (u8)(h[i] >> 24), o[4 * i + 1] = (u8)(h[i] >> 16), o[4 * i + 2] = (u8)(h[i] >> 8), o[4 * i + 3] = (u8)h[i];
    return 20;
}

u64 Hash::CRC(const u8* data, u64 len, u16* out) {
    u16 crc = 0;
    if (len && data) {
        u32 c = 0xffff;
        for (u64 i = 0; i < len; i++) c = (c >> 8) ^ kCrc16.t[(c ^ data[i]) & 0xff];
        crc = (u16)~c;
    }
    *out = crc;
    return 2;
}

u64 Hash::CRC(const u8* data, u64 len, u32* out) {
    u32 crc = 0;
    if (len && data) {
        u32 c = 0xffffffff;
        for (u64 i = 0; i < len; i++) c = kCrc32.t[(c ^ data[i]) & 0xff] ^ (c >> 8);
        crc = ~c;
    }
    *out = crc;
    return 4;
}

// ---- natives ----

using live::kInt;
using live::out;
using live::out_len;

// (SHA1's `work` region: the padded length plus one block, at most what the caller passed)
LEAF_FUNCTION(family(), "_ZN4Aska4Hash4SHA1EPKcmPcmS3_m", &Hash::SHA1, kInt, "Aska::Hash::SHA1(char const*, unsigned long, char*, unsigned long, char*, unsigned long)",
              {out(2, 20), out_len(4, 1, 1, 0x48, 0x10000)});
LEAF_FUNCTION(family(), "_ZN4Aska4Hash3CRCEPKhmPt", static_cast<u64 (*)(const u8*, u64, u16*)>(&Hash::CRC), kInt, "Aska::Hash::CRC(unsigned char const*, unsigned long, unsigned short*)",
              {out(2, 2)});
LEAF_FUNCTION(family(), "_ZN4Aska4Hash3CRCEPKhmPj", static_cast<u64 (*)(const u8*, u64, u32*)>(&Hash::CRC), kInt, "Aska::Hash::CRC(unsigned char const*, unsigned long, unsigned int*)",
              {out(2, 4)});

}  // namespace soa::native::hash
