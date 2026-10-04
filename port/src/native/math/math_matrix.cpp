// Aska::Matrix: product, look-at, decomposition and Euler angles (math_layout.h;
// port/decomp/math/matrix.c). Written from the disassembly's operation order and branch
// conditions (math_family.h). libm calls (asinf, acosf, cosf, atan2f) are the host's, as the
// guest's HLE thunks are.
#include <cmath>

#include "native/math/math_constants.h"
#include "native/math/math_family.h"
#include "native/math/math_layout.h"

namespace soa::native::math {

namespace {

struct V3 {
    F x, y, z;
};

inline F Asin(F v) { return F(::asinf(v.v)); }
inline F Acos(F v) { return F(::acosf(v.v)); }
inline F Cos(F v) { return F(::cosf(v.v)); }
inline F Atan2(F y, F x) { return F(::atan2f(y.v, x.v)); }

// A row's xyz, scaled to unit length unless shorter than kEpsilon.
V3 UnitRow(const float* r) {
    V3 v{F(r[0]), F(r[1]), F(r[2])};
    F len = Sqrt(v.z * v.z + (v.x * v.x + v.y * v.y));
    if (len < F(kEpsilon)) return v;
    F inv = F(1.0f) / len;
    return {v.x * inv, v.y * inv, v.z * inv};
}

// clamp(v, -1, 1); a NaN stays.
F Clamp1(F v) {
    if (v > F(1.0f)) return F(1.0f);
    if (v < F(-1.0f)) return F(-1.0f);
    return v;
}

// |v| < kEpsilon and |v - 1| < kEpsilon, as the guest tests them.
bool NearZero(F v) { return v < F(kEpsilon) && v > F(-kEpsilon); }
bool NearOne(F v) { return NearZero(v + F(-1.0f)); }

// CalcEuler's own asin for its default order: a rational approximation (|x| > 1: 0, without the
// sign), the sign of x OR-ed into the result's bits.
F GuestAsin(F x) {
    F ax = !(x >= F(0.0f)) ? -x : x;
    if (ax > F(1.0f)) return F(0.0f);
    F num, den;
    if (ax < F(kAsinSplit)) {
        num = ax * (ax * (ax * (ax * F(kAsinLow[0]) + F(kAsinLow[1])) + F(kAsinLow[2])) + F(kAsinLow[3]));
        den = ax * F(kAsinLow[4]);
    } else {
        F d = ax + F(kAsinSplitNeg);
        num = d * (d * (d * (d * F(kAsinHigh[0]) + F(kAsinHigh[1])) + F(kAsinHigh[2])) + F(kAsinHigh[3])) + F(kAsinHigh[4]);
        den = d * F(kAsinHigh[5]);
    }
    F r = num / (F(1.0f) - den);
    return F(armf::from_bits((armf::bits(x.v) & 0x80000000u) | armf::bits(r.v)));
}

}  // namespace

void Matrix::Mul(const Matrix* a, const Matrix* b) {
    Matrix r;  // (a or b may be this)
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            r.m[i][j] = f(((F(a->m[i][0]) * F(b->m[0][j]) + F(a->m[i][1]) * F(b->m[1][j])) + F(a->m[i][2]) * F(b->m[2][j])) + F(a->m[i][3]) * F(b->m[3][j]));
    *this = r;
}

void Matrix::Invert() {
    // Gauss-Jordan in place, without pivoting; a pivot within 1e-5 of 0 is replaced by +-1e-5.
    Matrix a = *this;
    for (int k = 0; k < 4; k++) {
        F p(a.m[k][k]);
        if (p >= F(0.0f) && p < F(kInvertMinPivot)) p = F(kInvertMinPivot);
        else if (p > F(kInvertMinPivotNeg) && p < F(0.0f)) p = F(kInvertMinPivotNeg);
        F inv = F(1.0f) / p;
        for (int j = 0; j < 4; j++) a.m[k][j] = f(inv * F(a.m[k][j]));
        a.m[k][k] = f(inv);
        for (int i = 0; i < 4; i++) {
            if (i == k) continue;
            F g(a.m[i][k]);
            for (int j = 0; j < 4; j++)
                if (j != k) a.m[i][j] = f(F(a.m[i][j]) - g * F(a.m[k][j]));
            // -(inv * g): as -0.0 - x for some (i, k) and FNEG x for the others (the compiler's
            // unrolling; they differ only in a NaN's sign)
            static constexpr bool kSubtract[4][4] = {{false, true, true, true}, {false, false, true, false}, {false, false, false, true}, {false, false, false, false}};
            a.m[i][k] = f(kSubtract[i][k] ? F(-0.0f) - inv * g : -(inv * g));
        }
    }
    *this = a;
}

void Matrix::ApplyVector(Vector* out, const Vector* v) const {
    if (out != v) {
        // row by row, reading v again after each store (as the guest: out may overlap v otherwise)
        for (int i = 0; i < 4; i++) {
            float r = f(((F(m[i][0]) * F(v->x) + F(m[i][1]) * F(v->y)) + F(m[i][2]) * F(v->z)) + F(m[i][3]) * F(v->w));
            (&out->x)[i] = r;
        }
        return;
    }
    // out == v: row 0 as above, the others with the operands the other way round
    F x(v->x), y(v->y), z(v->z), w(v->w);
    F r0 = ((F(m[0][0]) * x + F(m[0][1]) * y) + F(m[0][2]) * z) + F(m[0][3]) * w;
    F r[3];
    for (int i = 1; i < 4; i++) r[i - 1] = ((x * F(m[i][0]) + y * F(m[i][1])) + z * F(m[i][2])) + w * F(m[i][3]);
    *out = Vector{f(r0), f(r[0]), f(r[1]), f(r[2])};
}

void Matrix::SetLookAtMatrixZPUp(const Vector* eye, const Vector* dir, const Vector* up, float roll) {
    static constexpr Matrix kIdentity = {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};  // 0x26dbb00
    if (F(dir->x) == F(0.0f) && F(dir->y) == F(0.0f) && F(dir->z) == F(0.0f)) {
        *this = kIdentity;  // (no translation either)
        return;
    }
    const F one(1.0f), eps(kEpsilon);
    // The forward axis: dir, unit unless shorter than kEpsilon.
    V3 f0{F(dir->x), F(dir->y), F(dir->z)};
    V3 fw = f0;
    F len = Sqrt((fw.x * fw.x + fw.y * fw.y) + fw.z * fw.z);
    if (!(len < eps)) {
        F inv = one / len;
        fw = {inv * fw.x, inv * fw.y, inv * fw.z};
    }
    // right = up x dir (the unnormalized dir), unit; then the true up = forward x right, unit.
    F ux(up->x), uy(up->y), uz(up->z);
    V3 r{uy * f0.z - uz * f0.y, uz * f0.x - f0.z * ux, f0.y * ux - uy * f0.x};
    len = Sqrt(r.z * r.z + (r.x * r.x + r.y * r.y));
    if (!(len < eps)) {
        F inv = one / len;
        r = {r.x * inv, inv * r.y, inv * r.z};
    }
    V3 u{r.z * fw.y - r.y * fw.z, r.x * fw.z - r.z * fw.x, r.y * fw.x - r.x * fw.y};
    len = Sqrt(u.z * u.z + (u.x * u.x + u.y * u.y));
    if (!(len < eps)) {
        F inv = one / len;
        u = {inv * u.x, inv * u.y, u.z * inv};
    }
    // The roll: sin and cos by the guest's polynomials (as Quaternion::Create).
    int32_t n = armf::cvtzs(f(F(roll) * F(kInvPi)));
    F rr = F(roll) + F((float)n) * F(kMinusPi);
    bool odd = n & 1;
    F signed_r = odd ? -rr : rr;
    F r2 = rr * rr;
    F s = r2 * F(kSin[0]);
    for (int i = 1; i < 6; i++) s = r2 * (s + F(kSin[i]));
    s = r2 * (s + F(kSin[6])) + one;
    F c = r2 * F(kCos[0]);
    for (int i = 1; i < 6; i++) c = r2 * (c + F(kCos[i]));
    c = r2 * (c + F(-0.5f));
    F cos_roll = odd ? F(-1.0f) - c : c + one;
    F sin_roll = signed_r * s;
    // this = [right, up, forward] (as columns) * rotation about Z by the roll.
    Matrix axes = kIdentity, rot = kIdentity;
    axes.m[0][0] = f(r.x), axes.m[0][1] = f(u.x), axes.m[0][2] = f(fw.x);
    axes.m[1][0] = f(r.y), axes.m[1][1] = f(u.y), axes.m[1][2] = f(fw.y);
    axes.m[2][0] = f(r.z), axes.m[2][1] = f(u.z), axes.m[2][2] = f(fw.z);
    rot.m[0][0] = f(cos_roll), rot.m[0][1] = f(sin_roll);
    rot.m[1][0] = f(-(signed_r * s)), rot.m[1][1] = f(cos_roll);  // (FNMUL)
    Mul(&axes, &rot);
    m[0][3] = eye->x;  // (read after the product: as the guest)
    m[1][3] = eye->y;
    m[3][3] = 1.0f;
    m[2][3] = eye->z;
}

void Matrix::PutPRS(Vector* pos, Quaternion* rot, Vector* scale) const {
    const F eps(kEpsilon), one(1.0f);
    // The columns' xyz.
    V3 c0{F(m[0][0]), F(m[1][0]), F(m[2][0])}, c1{F(m[0][1]), F(m[1][1]), F(m[2][1])}, c2{F(m[0][2]), F(m[1][2]), F(m[2][2])};
    auto length = [](const V3& v) { return Sqrt((v.x * v.x + v.y * v.y) + v.z * v.z); };
    if (scale) {
        // The column lengths, snapped to 1 within kEpsilon.
        F sx = length(c0), sy = length(c1), sz = length(c2);
        auto snap = [&](F s) { return Abs(s + F(-1.0f)) < eps ? one : s; };
        scale->x = f(snap(sx));
        scale->y = f(snap(sy));
        scale->z = f(snap(sz));
        scale->w = 1.0f;
    }
    if (rot) {
        auto unit = [&](V3 v) {
            F len = length(v);
            if (len < eps) return v;
            F inv = one / len;
            return V3{inv * v.x, inv * v.y, inv * v.z};
        };
        V3 u0 = unit(c0), u1 = unit(c1), u2 = unit(c2);
        Matrix r = {{{f(u0.x), f(u1.x), f(u2.x), 0}, {f(u0.y), f(u1.y), f(u2.y), 0}, {f(u0.z), f(u1.z), f(u2.z), 0}, {0, 0, 0, 1}}};
        rot->Create(&r);
    }
    if (pos) *pos = Vector{m[0][3], m[1][3], m[2][3], 1.0f};
}

void Matrix::CalcEuler(Vector* out, EnumRotateType order) const {
    const F zero(0.0f);
    const V3 a = UnitRow(m[0]), b = UnitRow(m[1]), c = UnitRow(m[2]);
    F ex = zero, ey = zero, ez = zero;
    if (NearOne(a.x) && NearZero(a.y) && NearZero(a.z)) {
        ex = Atan2(c.y, c.z);  // a rotation about X only
    } else if (NearOne(b.y) && NearZero(b.x) && NearZero(b.z)) {
        ey = Atan2(a.z, a.x);  // about Y only
    } else if (NearOne(c.z) && NearZero(c.x) && NearZero(c.y)) {
        ez = Atan2(b.x, b.y);  // about Z only
    } else {
        // The middle angle by asin, its cosine, then the other two by acos with the signs from
        // the matrix (each order's elements; a zero cosine: gimbal lock, the others 0).
        switch (order) {
        case 1: {
            ez = Asin(b.x);
            F cs = Cos(ez);
            if (cs == zero) break;
            F s = Acos(Clamp1(a.x / cs));
            ey = cs * c.x > zero ? -s : s;
            s = Acos(Clamp1(b.y / cs));
            ex = cs * b.z > zero ? -s : s;
            break;
        }
        case 2: {
            F t = Asin(a.y);
            ez = -t;
            F cs = Cos(t);
            if (cs == zero) break;
            F s = Acos(Clamp1(a.x / cs));
            ey = cs * a.z < zero ? -s : s;
            s = Acos(Clamp1(b.y / cs));
            ex = cs * c.y < zero ? -s : s;
            break;
        }
        case 3: {
            ex = Asin(c.y);
            F cs = Cos(ex);
            if (cs == zero) break;
            F s = Acos(Clamp1(b.y / cs));
            ez = cs * a.y > zero ? -s : s;
            s = Acos(Clamp1(c.z / cs));
            ey = cs * c.x > zero ? -s : s;
            break;
        }
        case 4: {
            F t = Asin(b.z);
            ex = -t;
            F cs = Cos(t);
            if (cs == zero) break;
            F s = Acos(Clamp1(b.y / cs));
            ez = cs * b.x < zero ? -s : s;
            s = Acos(Clamp1(c.z / cs));
            ey = cs * a.z < zero ? -s : s;
            break;
        }
        case 5: {
            ey = Asin(a.z);
            F cs = Cos(ey);
            if (cs == zero) break;
            F s = Acos(Clamp1(a.x / cs));
            ez = cs * a.y > zero ? -s : s;
            s = Acos(Clamp1(c.z / cs));
            ex = cs * b.z > zero ? -s : s;
            break;
        }
        default: {  // 0 and anything else: its own asin
            F t = GuestAsin(c.x);
            ey = -t;
            F cs = Cos(t);
            if (!(Abs(cs) > F(kEpsilon))) {
                ex = Atan2(a.y, a.z);
                break;
            }
            F s = Acos(Clamp1(a.x / cs));
            ez = cs * b.x < zero ? -s : s;
            s = Acos(Clamp1(c.z / cs));
            ex = cs * c.y < zero ? -s : s;
            break;
        }
        }
    }
    out->x = f(ex);
    out->y = f(ey);
    out->z = f(ez);
}

// ---- natives ----
// (the const members snapshot no `this`: math_segment.cpp)

using live::kVoid;
using live::out;
constexpr u32 kObj = sizeof(Matrix);

LEAF_METHOD(family(), "_ZN4Aska6Matrix3MulEPKS0_S2_", &Matrix::Mul, kObj, kVoid, "Aska::Matrix::Mul(Matrix const*, Matrix const*)", {});
LEAF_METHOD(family(), "_ZN4Aska6Matrix19SetLookAtMatrixZPUpEPKNS_6VectorES3_S3_f", &Matrix::SetLookAtMatrixZPUp, kObj, kVoid, "Aska::Matrix::SetLookAtMatrixZPUp", {});
LEAF_METHOD(family(), "_ZNK4Aska6Matrix6PutPRSEPNS_6VectorEPNS_10QuaternionES2_", &Matrix::PutPRS, 0, kVoid, "Aska::Matrix::PutPRS",
            {out(1, sizeof(Vector)), out(2, sizeof(Quaternion)), out(3, sizeof(Vector))});
LEAF_METHOD(family(), "_ZN4Aska6Matrix6InvertEv", &Matrix::Invert, kObj, kVoid, "Aska::Matrix::Invert", {});
LEAF_METHOD(family(), "_ZNK4Aska6Matrix11ApplyVectorEPNS_6VectorEPKS1_", &Matrix::ApplyVector, 0, kVoid, "Aska::Matrix::ApplyVector", {out(1, sizeof(Vector))});
LEAF_METHOD(family(), "_ZNK4Aska6Matrix9CalcEulerEPNS_6VectorE14EnumRotateType", &Matrix::CalcEuler, 0, kVoid, "Aska::Matrix::CalcEuler", {out(1, 12)});

}  // namespace soa::native::math
