// Aska::detail::SpookyHashV2: Bob Jenkins' SpookyHash V2 (public domain, http://burtleburtle.net/bob/hash/spooky.html),
// the reference implementation attached to the recovered class (hash_layout.h; the guest's copy is
// port/decomp/hash/spooky.c, built with unaligned reads allowed: AArch64). Bit-exact with the
// guest (tests hash/spooky-*).
#include <cstring>

#include "native/hash/hash_family.h"
#include "native/hash/hash_layout.h"

namespace soa::native::hash {

namespace {

inline u64 Rot64(u64 x, int k) { return (x << k) | (x >> (64 - k)); }
inline u64 Load64(const u8* p) {
    u64 v;
    std::memcpy(&v, p, 8);
    return v;
}
inline u32 Load32(const u8* p) {
    u32 v;
    std::memcpy(&v, p, 4);
    return v;
}

inline void EndPartial(u64& h0, u64& h1, u64& h2, u64& h3, u64& h4, u64& h5, u64& h6, u64& h7, u64& h8, u64& h9, u64& h10, u64& h11) {
    h11 += h1, h2 ^= h11, h1 = Rot64(h1, 44);
    h0 += h2, h3 ^= h0, h2 = Rot64(h2, 15);
    h1 += h3, h4 ^= h1, h3 = Rot64(h3, 34);
    h2 += h4, h5 ^= h2, h4 = Rot64(h4, 21);
    h3 += h5, h6 ^= h3, h5 = Rot64(h5, 38);
    h4 += h6, h7 ^= h4, h6 = Rot64(h6, 33);
    h5 += h7, h8 ^= h5, h7 = Rot64(h7, 10);
    h6 += h8, h9 ^= h6, h8 = Rot64(h8, 13);
    h7 += h9, h10 ^= h7, h9 = Rot64(h9, 38);
    h8 += h10, h11 ^= h8, h10 = Rot64(h10, 53);
    h9 += h11, h0 ^= h9, h11 = Rot64(h11, 42);
    h10 += h0, h1 ^= h10, h0 = Rot64(h0, 54);
}

inline void End(const u64* data, u64& h0, u64& h1, u64& h2, u64& h3, u64& h4, u64& h5, u64& h6, u64& h7, u64& h8, u64& h9, u64& h10, u64& h11) {
    h0 += data[0], h1 += data[1], h2 += data[2], h3 += data[3], h4 += data[4], h5 += data[5];
    h6 += data[6], h7 += data[7], h8 += data[8], h9 += data[9], h10 += data[10], h11 += data[11];
    EndPartial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    EndPartial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    EndPartial(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
}

inline void ShortMix(u64& h0, u64& h1, u64& h2, u64& h3) {
    h2 = Rot64(h2, 50), h2 += h3, h0 ^= h2;
    h3 = Rot64(h3, 52), h3 += h0, h1 ^= h3;
    h0 = Rot64(h0, 30), h0 += h1, h2 ^= h0;
    h1 = Rot64(h1, 41), h1 += h2, h3 ^= h1;
    h2 = Rot64(h2, 54), h2 += h3, h0 ^= h2;
    h3 = Rot64(h3, 48), h3 += h0, h1 ^= h3;
    h0 = Rot64(h0, 38), h0 += h1, h2 ^= h0;
    h1 = Rot64(h1, 37), h1 += h2, h3 ^= h1;
    h2 = Rot64(h2, 62), h2 += h3, h0 ^= h2;
    h3 = Rot64(h3, 34), h3 += h0, h1 ^= h3;
    h0 = Rot64(h0, 5), h0 += h1, h2 ^= h0;
    h1 = Rot64(h1, 36), h1 += h2, h3 ^= h1;
}

inline void ShortEnd(u64& h0, u64& h1, u64& h2, u64& h3) {
    h3 ^= h2, h2 = Rot64(h2, 15), h3 += h2;
    h0 ^= h3, h3 = Rot64(h3, 52), h0 += h3;
    h1 ^= h0, h0 = Rot64(h0, 26), h1 += h0;
    h2 ^= h1, h1 = Rot64(h1, 51), h2 += h1;
    h3 ^= h2, h2 = Rot64(h2, 28), h3 += h2;
    h0 ^= h3, h3 = Rot64(h3, 9), h0 += h3;
    h1 ^= h0, h0 = Rot64(h0, 47), h1 += h0;
    h2 ^= h1, h1 = Rot64(h1, 54), h2 += h1;
    h3 ^= h2, h2 = Rot64(h2, 32), h3 += h2;
    h0 ^= h3, h3 = Rot64(h3, 25), h0 += h3;
    h1 ^= h0, h0 = Rot64(h0, 63), h1 += h0;
}

}  // namespace

void SpookyHashV2::Mix(const u64* data, u64& s0, u64& s1, u64& s2, u64& s3, u64& s4, u64& s5, u64& s6, u64& s7, u64& s8, u64& s9, u64& s10,
                       u64& s11) {
    // (the guest reads the 96-byte block unaligned: through memcpy here)
    const u8* p = reinterpret_cast<const u8*>(data);
    s0 += Load64(p + 0), s2 ^= s10, s11 ^= s0, s0 = Rot64(s0, 11), s11 += s1;
    s1 += Load64(p + 8), s3 ^= s11, s0 ^= s1, s1 = Rot64(s1, 32), s0 += s2;
    s2 += Load64(p + 16), s4 ^= s0, s1 ^= s2, s2 = Rot64(s2, 43), s1 += s3;
    s3 += Load64(p + 24), s5 ^= s1, s2 ^= s3, s3 = Rot64(s3, 31), s2 += s4;
    s4 += Load64(p + 32), s6 ^= s2, s3 ^= s4, s4 = Rot64(s4, 17), s3 += s5;
    s5 += Load64(p + 40), s7 ^= s3, s4 ^= s5, s5 = Rot64(s5, 28), s4 += s6;
    s6 += Load64(p + 48), s8 ^= s4, s5 ^= s6, s6 = Rot64(s6, 39), s5 += s7;
    s7 += Load64(p + 56), s9 ^= s5, s6 ^= s7, s7 = Rot64(s7, 57), s6 += s8;
    s8 += Load64(p + 64), s10 ^= s6, s7 ^= s8, s8 = Rot64(s8, 55), s7 += s9;
    s9 += Load64(p + 72), s11 ^= s7, s8 ^= s9, s9 = Rot64(s9, 54), s8 += s10;
    s10 += Load64(p + 80), s0 ^= s8, s9 ^= s10, s10 = Rot64(s10, 22), s9 += s11;
    s11 += Load64(p + 88), s1 ^= s9, s10 ^= s11, s11 = Rot64(s11, 46), s10 += s0;
}

void SpookyHashV2::Short(const void* message, u64 length, u64* hash1, u64* hash2) {
    const u8* p = static_cast<const u8*>(message);
    u64 remainder = length % 32;
    u64 a = *hash1, b = *hash2, c = kConst, d = kConst;
    if (length > 15) {
        const u8* end = p + (length / 32) * 32;
        for (; p < end; p += 32) {
            c += Load64(p), d += Load64(p + 8);
            ShortMix(a, b, c, d);
            a += Load64(p + 16), b += Load64(p + 24);
        }
        if (remainder >= 16) {
            c += Load64(p), d += Load64(p + 8);
            ShortMix(a, b, c, d);
            p += 16;
            remainder -= 16;
        }
    }
    d += length << 56;
    switch (remainder) {
    case 15: d += (u64)p[14] << 48; [[fallthrough]];
    case 14: d += (u64)p[13] << 40; [[fallthrough]];
    case 13: d += (u64)p[12] << 32; [[fallthrough]];
    case 12: d += Load32(p + 8), c += Load64(p); break;
    case 11: d += (u64)p[10] << 16; [[fallthrough]];
    case 10: d += (u64)p[9] << 8; [[fallthrough]];
    case 9: d += (u64)p[8]; [[fallthrough]];
    case 8: c += Load64(p); break;
    case 7: c += (u64)p[6] << 48; [[fallthrough]];
    case 6: c += (u64)p[5] << 40; [[fallthrough]];
    case 5: c += (u64)p[4] << 32; [[fallthrough]];
    case 4: c += Load32(p); break;
    case 3: c += (u64)p[2] << 16; [[fallthrough]];
    case 2: c += (u64)p[1] << 8; [[fallthrough]];
    case 1: c += (u64)p[0]; break;
    case 0: c += kConst, d += kConst;
    }
    ShortEnd(a, b, c, d);
    *hash1 = a;
    *hash2 = b;
}

void SpookyHashV2::Hash128(const void* message, u64 length, u64* hash1, u64* hash2) {
    if (length < kBufSize) return Short(message, length, hash1, hash2);
    u64 h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11;
    h0 = h3 = h6 = h9 = *hash1;
    h1 = h4 = h7 = h10 = *hash2;
    h2 = h5 = h8 = h11 = kConst;
    const u8* p = static_cast<const u8*>(message);
    const u8* end = p + (length / kBlockSize) * kBlockSize;
    for (; p < end; p += kBlockSize) Mix(reinterpret_cast<const u64*>(p), h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    u64 remainder = length - (u64)(end - static_cast<const u8*>(message));
    u64 buf[kNumVars];
    std::memcpy(buf, end, remainder);
    std::memset(reinterpret_cast<u8*>(buf) + remainder, 0, kBlockSize - remainder);
    reinterpret_cast<u8*>(buf)[kBlockSize - 1] = (u8)remainder;
    End(buf, h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    *hash1 = h0;
    *hash2 = h1;
}

void SpookyHashV2::Init(u64 seed1, u64 seed2) {
    m_length = 0;
    m_remainder = 0;
    m_state[0] = seed1;
    m_state[1] = seed2;
}

void SpookyHashV2::Update(const void* message, u64 length) {
    u64 h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11;
    u64 newLength = length + m_remainder;
    if (newLength < kBufSize) {
        std::memcpy(reinterpret_cast<u8*>(m_data) + m_remainder, message, length);
        m_length = length + m_length;
        m_remainder = (u8)newLength;
        return;
    }
    if (m_length < kBufSize) {
        h0 = h3 = h6 = h9 = m_state[0];
        h1 = h4 = h7 = h10 = m_state[1];
        h2 = h5 = h8 = h11 = kConst;
    } else {
        h0 = m_state[0], h1 = m_state[1], h2 = m_state[2], h3 = m_state[3], h4 = m_state[4], h5 = m_state[5];
        h6 = m_state[6], h7 = m_state[7], h8 = m_state[8], h9 = m_state[9], h10 = m_state[10], h11 = m_state[11];
    }
    m_length = length + m_length;
    const u8* p = static_cast<const u8*>(message);
    if (m_remainder) {
        u8 prefix = (u8)(kBufSize - m_remainder);
        std::memcpy(reinterpret_cast<u8*>(m_data) + m_remainder, message, prefix);
        Mix(m_data, h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
        Mix(&m_data[kNumVars], h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
        p += prefix;
        length -= prefix;
    }
    const u8* end = p + (length / kBlockSize) * kBlockSize;
    u8 remainder = (u8)(length - (u64)(end - p));
    for (; p < end; p += kBlockSize) Mix(reinterpret_cast<const u64*>(p), h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    m_remainder = remainder;
    std::memcpy(m_data, end, remainder);
    m_state[0] = h0, m_state[1] = h1, m_state[2] = h2, m_state[3] = h3, m_state[4] = h4, m_state[5] = h5;
    m_state[6] = h6, m_state[7] = h7, m_state[8] = h8, m_state[9] = h9, m_state[10] = h10, m_state[11] = h11;
}

void SpookyHashV2::Final(u64* hash1, u64* hash2) {
    if (m_length < kBufSize) {
        *hash1 = m_state[0];
        *hash2 = m_state[1];
        Short(m_data, m_length, hash1, hash2);
        return;
    }
    u64* data = m_data;
    u8 remainder = m_remainder;
    u64 h0 = m_state[0], h1 = m_state[1], h2 = m_state[2], h3 = m_state[3], h4 = m_state[4], h5 = m_state[5];
    u64 h6 = m_state[6], h7 = m_state[7], h8 = m_state[8], h9 = m_state[9], h10 = m_state[10], h11 = m_state[11];
    if (remainder >= kBlockSize) {
        Mix(data, h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
        data += kNumVars;
        remainder -= kBlockSize;
    }
    // (into m_data: the guest's Final leaves the padding there)
    std::memset(reinterpret_cast<u8*>(data) + remainder, 0, kBlockSize - remainder);
    reinterpret_cast<u8*>(data)[kBlockSize - 1] = remainder;
    End(data, h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
    *hash1 = h0;
    *hash2 = h1;
}

// ---- natives (Mix is only called by Hash128 / Update / Final, natives too: left unbound) ----

using S = SpookyHashV2;
using live::kVoid;
using live::out;
using live::out_len;

LEAF_FUNCTION(family(), "_ZN4Aska6detail12SpookyHashV25ShortEPKvmPmS4_", &S::Short, kVoid, "Aska::detail::SpookyHashV2::Short", {out(2, 8), out(3, 8)});
LEAF_FUNCTION(family(), "_ZN4Aska6detail12SpookyHashV27Hash128EPKvmPmS4_", &S::Hash128, kVoid, "Aska::detail::SpookyHashV2::Hash128", {out(2, 8), out(3, 8)});
LEAF_METHOD(family(), "_ZN4Aska6detail12SpookyHashV24InitEmm", &S::Init, sizeof(S), kVoid, "Aska::detail::SpookyHashV2::Init", {});
LEAF_METHOD(family(), "_ZN4Aska6detail12SpookyHashV26UpdateEPKvm", &S::Update, sizeof(S), kVoid, "Aska::detail::SpookyHashV2::Update", {});
LEAF_METHOD(family(), "_ZN4Aska6detail12SpookyHashV25FinalEPmS2_", &S::Final, sizeof(S), kVoid, "Aska::detail::SpookyHashV2::Final", {out(1, 8), out(2, 8)});

}  // namespace soa::native::hash
