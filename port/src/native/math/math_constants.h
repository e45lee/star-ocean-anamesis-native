#pragma once
// The .rodata constants the math natives use: each with the vaddr the guest loads it from. Test
// math/constants compares every one with the lib's bytes (kConstants below lists them).
#include <cstdint>

namespace soa::native::math {

inline constexpr float kEpsilon = 1e-6f;          // 0x26e519c: lengths below it aren't normalized
inline constexpr float kInvPi = 0.318309873f;      // 0x26ebdf4
inline constexpr float kMinusPi = -3.14159274f;    // 0x26edb30
inline constexpr float kPi = 3.14159274f;          // 0x26e3fd0
inline constexpr float kHalfPi = 1.57079637f;      // 0x26f7284
inline constexpr float kSlerpMinAngle = 0.01f;     // 0x26e6ae4: below it Slerp is linear
// sin(r) = r * (1 + r^2 * S(r^2)) and cos(r) = 1 + r^2 * C(r^2) on [-pi/2, pi/2]: Horner
// coefficients, highest first (0x2864928.., 0x2864910..; 0x2870cc0 is -kSin[0]).
inline constexpr float kSin[7] = {-6.57978446e-13f, 1.58846755e-10f, -2.50368490e-08f, 2.75565571e-06f, -1.98412483e-04f, 8.33333284e-03f, -1.66666672e-01f};
inline constexpr float kSinLead = 6.57978446e-13f;  // 0x2870cc0
inline constexpr float kCos[6] = {-9.77353094e-12f, 2.06202722e-09f, -2.75369331e-07f, 2.48006872e-05f, -1.38888671e-03f, 4.16666642e-02f};
// acos(c) = pi/2 + c * (c^2 * A(c^2) + kAcos[7]) for c in [0, 1] (0x287158c..0x28715a8).
inline constexpr float kAcos[8] = {-44.9103203f, 147.367905f, -192.855698f, 127.678413f, -44.9730835f, 7.95500851f, -0.791238725f, -0.986177981f};
// Matrix::CalcEuler's asin (its default order): a rational approximation, one for |x| < 0.94
// and one in d = |x| - 0.94 (0x2870cd8.., 0x2870ce0.., 0x2870cf8..).
inline constexpr float kAsinSplit = 0.94f;       // 0x2870cd8
inline constexpr float kAsinSplitNeg = -0.94f;   // 0x2870cdc
inline constexpr float kAsinHigh[6] = {-7139.48047f, 522.452209f, -55.2367783f, -16.7203407f, 1.22263026f, 16.2329006f};
inline constexpr float kAsinLow[5] = {-0.174860716f, 0.255844921f, -0.961087108f, 1.00763714f, 0.912481189f};

// Matrix::Invert's smallest pivot (0x26fac84, 0x2864944).
inline constexpr float kInvertMinPivot = 1e-5f;
inline constexpr float kInvertMinPivotNeg = -1e-5f;

// Every constant with its vaddr (and, for arrays, consecutive ones), for math/constants.
struct RodataConstant {
    uint64_t vaddr;
    const float* values;
    int count;
};
inline constexpr RodataConstant kConstants[] = {
    {0x26ebdf4, &kInvPi, 1},  {0x26edb30, &kMinusPi, 1}, {0x26e3fd0, &kPi, 1},      {0x26f7284, &kHalfPi, 1},
    {0x26e6ae4, &kSlerpMinAngle, 1}, {0x2864928, kSin, 7}, {0x2870cc0, &kSinLead, 1}, {0x2864910, kCos, 6},
    {0x287158c, kAcos, 8},     {0x26e519c, &kEpsilon, 1}, {0x2870cd8, &kAsinSplit, 1}, {0x2870cdc, &kAsinSplitNeg, 1},
    {0x2870ce0, kAsinHigh, 6}, {0x2870cf8, kAsinLow, 5},
    {0x26fac84, &kInvertMinPivot, 1}, {0x2864944, &kInvertMinPivotNeg, 1},
};

}  // namespace soa::native::math
