#pragma once
// Single-precision arithmetic with AArch64 NaN semantics (FPCR.DN = 0), for native code that
// must be bit-identical to the guest even when NaNs appear (e.g. inf * 0 in a layout with a
// zero scale). x86 SSE differs in two ways: an invalid operation produces the negative
// "indefinite" NaN 0xffc00000 instead of ARM's default NaN 0x7fc00000, and when both operands
// are NaNs the compiler's operand order decides which one propagates. On ARM a signalling NaN
// operand wins over a quiet one, then operand 1 over operand 2, and the result is quieted.
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstring>

namespace soa::armf {

inline uint32_t bits(float f) {
    uint32_t b;
    std::memcpy(&b, &f, 4);
    return b;
}
inline float from_bits(uint32_t b) {
    float f;
    std::memcpy(&f, &b, 4);
    return f;
}
inline bool is_snan(float f) { return std::isnan(f) && !(bits(f) & 0x00400000u); }
inline float quiet(float f) { return from_bits(bits(f) | 0x00400000u); }

// Result of a two-operand op whose raw (host) result is `r`.
inline float fix2(float a, float b, float r) {
    if (!std::isnan(r)) return r;
    if (is_snan(a)) return quiet(a);
    if (is_snan(b)) return quiet(b);
    if (std::isnan(a)) return a;
    if (std::isnan(b)) return b;
    return from_bits(0x7fc00000u);
}

inline float add(float a, float b) { return fix2(a, b, a + b); }
inline float sub(float a, float b) { return fix2(a, b, a - b); }
inline float mul(float a, float b) { return fix2(a, b, a * b); }
inline float div(float a, float b) { return fix2(a, b, a / b); }
// FMAX / FMIN: a NaN operand propagates (fix2's rules; not FMAXNM's "the number wins"), and
// +0 is larger than -0.
inline float max(float a, float b) {
    if (std::isnan(a) || std::isnan(b)) return fix2(a, b, a + b);
    if (a == b) return (bits(a) & bits(b) & 0x80000000u) ? a : from_bits(bits(a) & bits(b));  // (+0 if either is)
    return a > b ? a : b;
}
inline float min(float a, float b) {
    if (std::isnan(a) || std::isnan(b)) return fix2(a, b, a + b);
    if (a == b) return from_bits(bits(a) | bits(b));  // (-0 if either is)
    return a < b ? a : b;
}
// FCVTZS (float -> int32, toward zero): saturates out of range, NaN -> 0 (x86's cvttss2si gives
// 0x80000000 for both).
inline int32_t cvtzs(float f) {
    if (std::isnan(f)) return 0;
    if (f >= 2147483648.0f) return INT32_MAX;
    if (f <= -2147483648.0f) return INT32_MIN;
    return (int32_t)f;
}

}  // namespace soa::armf

namespace soa::armf {

// A float whose + - * / follow the AArch64 NaN rules above (unary minus flips the sign bit,
// like FNEG). Construct from float explicitly: F(x).
struct F {
    float v;
    F() = default;
    constexpr explicit F(float x) : v(x) {}
    friend F operator+(F a, F b) { return F(add(a.v, b.v)); }
    friend F operator-(F a, F b) { return F(sub(a.v, b.v)); }
    friend F operator*(F a, F b) { return F(mul(a.v, b.v)); }
    friend F operator/(F a, F b) { return F(div(a.v, b.v)); }
    F operator-() const { return F(-v); }
    F& operator+=(F b) { return *this = *this + b; }
    F& operator-=(F b) { return *this = *this - b; }
    F& operator*=(F b) { return *this = *this * b; }
    friend bool operator==(F a, F b) { return a.v == b.v; }
    // (IEEE comparisons: false when unordered, like the FCMP condition codes gt / ge / mi / ls
    // the guest branches on; write the guest's condition, e.g. !(a < b) for "b.ge not taken")
    friend bool operator<(F a, F b) { return a.v < b.v; }
    friend bool operator<=(F a, F b) { return a.v <= b.v; }
    friend bool operator>(F a, F b) { return a.v > b.v; }
    friend bool operator>=(F a, F b) { return a.v >= b.v; }
};

}  // namespace soa::armf
