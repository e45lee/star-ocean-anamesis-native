// dynamics_neon.h: FRECPE / FRSQRTE / FRECPS / FRSQRTS (single precision, FPCR = 0), from the ARM
// pseudocode (FPRecipEstimate, FPRSqrtEstimate, FPRecipStepFused, FPRSqrtStepFused, RecipEstimate,
// RecipSqrtEstimate), as dynarmic implements them for the JIT (the port's layering keeps dynarmic's
// headers out of port/, so this is the same algorithm written here). Test dynamics/neon compares
// each with the instruction itself, run by the JIT, over every exponent and many fractions.
#include "native/dynamics/dynamics_neon.h"

#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>

namespace soa::native::dynamics::neon {

namespace {

using u32 = std::uint32_t;
using u64 = std::uint64_t;

inline u32 bits(float f) {
    u32 u;
    std::memcpy(&u, &f, 4);
    return u;
}
inline float from(u32 u) {
    float x;
    std::memcpy(&x, &u, 4);
    return x;
}
inline bool is_nan(u32 b) { return (b & 0x7f800000u) == 0x7f800000u && (b & 0x7fffffu); }
inline bool is_snan(u32 b) { return is_nan(b) && !(b & 0x400000u); }
inline bool is_inf(u32 b) { return (b & 0x7fffffffu) == 0x7f800000u; }
inline bool is_zero(u32 b) { return (b & 0x7fffffffu) == 0; }
constexpr u32 kQuiet = 0x400000u, kSign = 0x80000000u, kDefaultNaN = 0x7fc00000u;

// A finite nonzero float as sign, unbiased exponent of its leading 1 bit and the 23 bits after it.
struct Unpacked {
    bool sign;
    int exp;
    u32 frac;  // the bits below the leading 1, left-aligned to 23 bits
};
Unpacked unpack(u32 b) {
    Unpacked u{(b & kSign) != 0, 0, 0};
    u32 e = (b >> 23) & 0xff, m = b & 0x7fffff;
    if (e) {
        u.exp = (int)e - 127;
        u.frac = m;
    } else {  // a denormal: normalize
        int shift = 0;
        while (!(m & 0x800000u)) m <<= 1, shift++;
        u.exp = -126 - shift;
        u.frac = m & 0x7fffff;
    }
    return u;
}

// RecipEstimate(a), a in [256, 512): the 8 fraction bits of 1 / a (u0.9 -> u1.8, the 1 implied).
u32 recip_estimate(u32 a) {
    u32 x = a * 2 + 1;
    u32 q = (1u << 19) / x;
    return ((q + 1) / 2) & 0xff;
}
// RecipSqrtEstimate(a), a in [128, 512).
u32 rsqrt_estimate(u32 a) {
    static const std::array<u32, 512> lut = [] {
        std::array<u32, 512> t{};
        for (u64 i = 128; i < 512; i++) {
            u64 x = i < 256 ? i * 2 + 1 : (i | 1) * 2;
            u64 b = 512;
            while (x * (b + 1) * (b + 1) < (1ull << 28)) b++;
            t[i] = (u32)(((b + 1) / 2) & 0xff);
        }
        return t;
    }();
    return lut[a];
}

// The float nearest to s + err (s: the double nearest to the exact value, err: the rest). (float)s
// is right unless s lies exactly halfway between two floats (a double rounding): then err decides.
float round_to_float(double s, double err) {
    float f = (float)s;
    if (err == 0 || (double)f == s || !std::isfinite(f)) return f;
    float lo = (double)f < s ? f : std::nextafter(f, -INFINITY);
    float hi = (double)f < s ? std::nextafter(f, INFINITY) : f;
    if (s != ((double)lo + (double)hi) / 2) return f;
    return err > 0 ? hi : lo;
}

// FPRecipStepFused / FPRSqrtStepFused: (c + (-a) * b) / div, rounded once (c = 2 / 3, div = 1 / 2).
float step_fused(float a, float b, double c, bool halve) {
    u32 ua = bits(a) ^ kSign, ub = bits(b);  // FPNeg(op1) first: a NaN op1 comes back negated
    if (is_snan(ua)) return from(ua | kQuiet);
    if (is_snan(ub)) return from(ub | kQuiet);
    if (is_nan(ua)) return from(ua);
    if (is_nan(ub)) return from(ub);
    bool inf1 = is_inf(ua), inf2 = is_inf(ub), zero1 = is_zero(ua), zero2 = is_zero(ub);
    if ((inf1 && zero2) || (zero1 && inf2)) return halve ? 1.5f : 2.0f;
    if (inf1 || inf2) return from((((ua ^ ub) & kSign)) | 0x7f800000u);
    double p = (double)from(ua) * (double)from(ub);  // exact (24 x 24 bits)
    double s = c + p;
    double bb = s - c;
    double err = (c - (s - bb)) + (p - bb);  // TwoSum: s + err == c + p exactly
    if (s == 0 && err == 0) return 0.0f;     // an exact zero is +0
    if (halve) s *= 0.5, err *= 0.5;         // (exact: |s| is 0 or >= 2^-46 here)
    return round_to_float(s, err);
}

}  // namespace

float frecpe(float x) {
    u32 b = bits(x);
    if (is_nan(b)) return from(is_snan(b) ? b | kQuiet : b);
    if (is_inf(b)) return from(b & kSign);
    if (is_zero(b)) return from((b & kSign) | 0x7f800000u);
    Unpacked u = unpack(b);
    if (u.exp < -128) return from((u.sign ? kSign : 0) | 0x7f800000u);  // overflows to infinity (round to nearest)
    u32 scaled = 256 | (u.frac >> 15);
    u32 estimate = recip_estimate(scaled) << 15;
    int rexp = -(u.exp + 1);
    if (rexp < -126) {
        estimate |= 1u << 23;
        if (rexp == -127) {
            estimate >>= 1;
        } else {  // -128
            estimate >>= 2;
            rexp++;
        }
    }
    u32 field = rexp < -126 ? 0 : (u32)(rexp + 127);
    return from((u.sign ? kSign : 0) | (field << 23) | (estimate & 0x7fffff));
}

float frsqrte(float x) {
    u32 b = bits(x);
    if (is_nan(b)) return from(is_snan(b) ? b | kQuiet : b);
    if (is_zero(b)) return from((b & kSign) | 0x7f800000u);
    if (b & kSign) return from(kDefaultNaN);
    if (is_inf(b)) return 0.0f;
    Unpacked u = unpack(b);
    int rexp = (-(u.exp + 1)) >> 1;
    bool odd = u.exp % 2 == 0;
    u32 mant = 0x800000u | u.frac;  // the leading 1 at bit 23
    u32 scaled = odd ? mant >> 16 : mant >> 15;
    u32 estimate = rsqrt_estimate(scaled);
    return from(((u32)(rexp + 127) << 23) | (estimate << 15));
}

float frecps(float a, float b) { return step_fused(a, b, 2.0, false); }
float frsqrts(float a, float b) { return step_fused(a, b, 3.0, true); }

}  // namespace soa::native::dynamics::neon
