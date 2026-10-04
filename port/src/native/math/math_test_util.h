#pragma once
// Inputs for the `math` differential tests (math_*_test.cpp): random floats that hit the edges
// (zeros of both signs, NaNs with payloads, infinities, denormals, huge and tiny values) as well as
// ordinary ones, and bit-exact comparison of float results.
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>

#include "native/common/test.h"
#include "native/math/math_layout.h"

namespace soa::native::math::test {

inline u32 bits(float f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return b;
}
inline float from_bits(u32 b) {
    float f;
    std::memcpy(&f, &b, 4);
    return f;
}

// A float: mostly ordinary values in [-r, r]; with probability `special` (in 1/1000) an edge value.
inline float rand_float(TestContext& t, float r = 10.0f, int special = 30) {
    int k = t.rand_int(0, 999);
    if (k < special) {
        switch (t.rand_int(0, 11)) {
        case 0: return 0.0f;
        case 1: return -0.0f;
        case 2: return from_bits(0x7fc00000u | (u32)t.rand_int(0, 0x3fffff));    // quiet NaN, payload
        case 3: return from_bits(0xffc00000u | (u32)t.rand_int(0, 0x3fffff));    // negative quiet NaN
        case 4: return from_bits(0x7f800001u | (u32)t.rand_int(0, 0x3ffffe));    // signalling NaN
        case 5: return INFINITY;
        case 6: return -INFINITY;
        case 7: return from_bits((u32)t.rand_int(1, 0x7fffff) | (t.rand_int(0, 1) ? 0x80000000u : 0));  // denormal
        case 8: return (t.rand_int(0, 1) ? 1.0f : -1.0f) * std::ldexp(1.0f, t.rand_int(60, 127));        // huge
        case 9: return (t.rand_int(0, 1) ? 1.0f : -1.0f) * std::ldexp(1.0f, -t.rand_int(20, 126));       // tiny
        case 10: return 1.0f;
        default: return -1.0f;
        }
    }
    if (k < special + 100) return (float)t.rand_int(-4, 4);  // small integers: exact ties, zeros
    return std::uniform_real_distribution<float>(-r, r)(t.rng());
}
inline Vector rand_vector(TestContext& t, float r = 10.0f, int special = 30) {
    return Vector{rand_float(t, r, special), rand_float(t, r, special), rand_float(t, r, special), rand_float(t, r, special)};
}
// A unit quaternion (or, with probability special/1000, an arbitrary one).
inline Quaternion rand_quaternion(TestContext& t, int special = 30) {
    Quaternion q{rand_float(t, 1, special), rand_float(t, 1, special), rand_float(t, 1, special), rand_float(t, 1, special)};
    if (t.rand_int(0, 999) < special) return q;
    float n = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    if (n > 1e-3f && std::isfinite(n)) q = {q.x / n, q.y / n, q.z / n, q.w / n};
    return q;
}

// A rotation matrix (from a random unit quaternion), sometimes scaled or with a random
// translation row, or (with probability special/1000) arbitrary.
inline Matrix rand_matrix(TestContext& t, int special) {
    Matrix m{};
    if (t.rand_int(0, 999) < special) {
        for (auto& row : m.m)
            for (float& v : row) v = rand_float(t, 3, special);
        return m;
    }
    Quaternion q = rand_quaternion(t, 0);
    float x = q.x, y = q.y, z = q.z, w = q.w;
    float r[3][3] = {{1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w)},
                     {2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)},
                     {2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y)}};
    float s = t.rand_int(0, 3) ? 1.0f : rand_float(t, 3, 0);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) m.m[i][j] = r[i][j] * s;
        m.m[i][3] = rand_float(t, 50, 0);
    }
    m.m[3][3] = 1.0f;
    return m;
}

// Bytes equal (floats compared by their bits: NaN payloads and signed zeros count).
template <typename T>
bool same(const T& a, const T& b) {
    return std::memcmp(&a, &b, sizeof(T)) == 0;
}

// Counts a mismatch, reporting the first few with `what` and the case number.
struct Mismatches {
    TestContext& t;
    const char* name;
    int n = 0;
    void add(int k, const std::string& what) {
        if (n++ < 5) t.fail("%s case %d: %s", name, k, what.c_str());
    }
    void check(int k, bool ok, const std::string& what) {
        if (!ok) add(k, what);
    }
    ~Mismatches() {
        if (n) t.fail("%s: %d mismatches", name, n);
    }
};

inline std::string hex(float f) {
    char b[48];
    std::snprintf(b, sizeof b, "%08x (%g)", (unsigned)bits(f), (double)f);
    return b;
}

}  // namespace soa::native::math::test
