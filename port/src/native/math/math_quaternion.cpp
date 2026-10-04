// Aska::Quaternion: construction from an axis-angle, a matrix and Euler angles, and Slerp
// (math_layout.h; port/decomp/math/quaternion.c). Written from the disassembly: the guest's own
// polynomial sin / cos / acos (not libm) with its .rodata coefficients, its operation order and
// its branch conditions (math_family.h).
#include "native/math/math_constants.h"
#include "native/math/math_family.h"
#include "native/math/math_layout.h"

namespace soa::native::math {

namespace {

// The quaternion product a * b, in the guest's operand order (both products of CreateFromEuler).
Quaternion Mul(const Quaternion& qa, const Quaternion& qb) {
    F ax(qa.x), ay(qa.y), az(qa.z), aw(qa.w), bx(qb.x), by(qb.y), bz(qb.z), bw(qb.w);
    F x = ((aw * bx + ax * bw) + ay * bz) - az * by;
    F y = bx * az + (bw * ay + (aw * by - ax * bz));
    F z = bw * az + ((aw * bz + ax * by) - bx * ay);
    F w = ((aw * bw - bx * ax) - ay * by) - bz * az;
    return {f(x), f(y), f(z), f(w)};
}

}  // namespace

void Quaternion::Create(const Vector* axis_angle) {
    const Vector& v = *axis_angle;
    F len = Sqrt((F(v.x) * F(v.x) + F(v.y) * F(v.y)) + F(v.z) * F(v.z));
    // The axis: normalized when not shorter than kEpsilon (by division, not by a reciprocal).
    F axis[3] = {F(v.x), F(v.y), F(v.z)};
    if (len >= F(kEpsilon)) axis[0] = axis[0] / len, axis[1] = axis[1] / len, axis[2] = axis[2] / len;
    // half = angle / 2 reduced to r in [-pi/2, pi/2]: half = r + n * pi.
    F half = F(v.w) * F(0.5f);
    int32_t n = armf::cvtzs(f(half * F(kInvPi)));
    F r = half + F((float)n) * F(kMinusPi);
    bool odd = n & 1;
    F signed_r = odd ? -r : r;
    F r2 = r * r;
    F s = r2 * F(kSin[0]);
    for (int i = 1; i < 6; i++) s = r2 * (s + F(kSin[i]));
    s = r2 * (s + F(kSin[6])) + F(1.0f);  // (the loop's last step written out: + kSin[6], * r2, + 1)
    F sin_half = signed_r * s;
    F c = r2 * F(kCos[0]);
    for (int i = 1; i < 6; i++) c = r2 * (c + F(kCos[i]));
    c = r2 * (c + F(-0.5f));
    F cos_half = odd ? F(-1.0f) - c : c + F(1.0f);
    x = f(axis[0] * sin_half);
    y = f(axis[1] * sin_half);
    z = f(axis[2] * sin_half);
    w = f(cos_half);
}

void Quaternion::Create(const Matrix* mat) {
    const auto& m = mat->m;
    F trace = ((F(m[0][0]) + F(m[1][1])) + F(m[2][2])) + F(m[3][3]);
    float* q = &x;  // x, y, z, w by index
    if (trace >= F(1.0f)) {
        F s = Sqrt(trace);
        w = f(s * F(0.5f));
        F inv = F(0.5f) / s;
        x = f(inv * (F(m[2][1]) - F(m[1][2])));
        y = f(inv * (F(m[0][2]) - F(m[2][0])));
        z = f(inv * (F(m[1][0]) - F(m[0][1])));
        return;
    }
    // The largest diagonal element i (ties and NaNs: the guest's `le` / `gt`), then j, k after it.
    static constexpr int kNext[3] = {1, 2, 0};  // 0x28715cc
    int i = !(F(m[0][0]) > F(m[1][1])) ? 1 : 0;
    if (F(m[2][2]) > F(m[i][i])) i = 2;
    int j = kNext[i], k = kNext[j];
    F s = Sqrt(((F(m[i][i]) - F(m[j][j])) - F(m[k][k])) + F(1.0f));
    q[i] = f(s * F(0.5f));
    if (s == F(0.0f)) {
        x = y = z = 0.0f, w = 1.0f;  // (0x26dbb30: the identity)
        return;
    }
    F inv = F(0.5f) / s;
    q[j] = f(inv * (F(m[i][j]) + F(m[j][i])));
    q[k] = f(inv * (F(m[i][k]) + F(m[k][i])));
    w = f(-(inv * (F(m[j][k]) - F(m[k][j]))));  // (FNMUL)
}

void Quaternion::CreateFromEuler(float ax, float ay, float az, EnumRotateType order) {
    Vector vx{1, 0, 0, ax}, vy{0, 1, 0, ay}, vz{0, 0, 1, az};
    Quaternion qx, qy, qz;
    qx.Create(&vx);
    qy.Create(&vy);
    qz.Create(&vz);
    Quaternion q;
    switch (order) {
    case 1: q = Mul(Mul(qy, qz), qx); break;
    case 2: q = Mul(Mul(qx, qz), qy); break;
    case 3: q = Mul(Mul(qz, qx), qy); break;
    case 4: q = Mul(Mul(qy, qx), qz); break;
    case 5: q = Mul(Mul(qx, qy), qz); break;
    default: q = Mul(Mul(qz, qy), qx); break;  // 0 and anything else: X, then Y, then Z
    }
    F len = Sqrt(((F(q.x) * F(q.x) + F(q.y) * F(q.y)) + F(q.z) * F(q.z)) + F(q.w) * F(q.w));
    F inv = F(1.0f) / len;
    x = f(F(q.x) * inv);
    y = f(inv * F(q.y));
    z = f(inv * F(q.z));
    w = f(inv * F(q.w));
}

void Quaternion::Slerp(const Quaternion* q1, const Quaternion* q2, float t_) {
    const F t(t_), one(1.0f);
    const F x1(q1->x), y1(q1->y), z1(q1->z), w1(q1->w), x2(q2->x), y2(q2->y), z2(q2->z), w2(q2->w);
    F dot = ((x1 * x2 + y1 * y2) + z1 * z2) + w1 * w2;
    F c = !(dot >= F(0.0f)) ? -dot : dot;  // |dot| (a NaN dot: negated)
    bool spherical = false;
    F rx, ry, rz, rw;
    if (!(c > one) && !(c < F(-1.0f))) {
        F c2 = c * c;
        F p = c2 * F(kAcos[0]);
        for (int i = 1; i < 6; i++) p = c2 * (p + F(kAcos[i]));
        F theta = c * (c2 * (p + F(kAcos[6])) + F(kAcos[7])) + F(kHalfPi);  // acos(c)
        if (theta > F(kSlerpMinAngle)) {
            spherical = true;
            // sin((1 - t) theta), sin(t theta) and sin(theta), each reduced by multiples of pi.
            auto sin_ = [&](F a) {
                int32_t n = armf::cvtzs(f(a * F(kInvPi)));
                F r = a - F((float)n) * F(kPi);
                F r2 = r * r;
                F s = r2 * (F(kSin[1]) - r2 * F(kSinLead));
                for (int i = 2; i < 7; i++) s = r2 * (s + F(kSin[i]));
                s = s + one;
                return ((n & 1) ? -r : r) * s;
            };
            F sa = sin_((one - t) * theta), sb = sin_(theta * t), st = sin_(theta);
            F wa = !(dot >= F(0.0f)) ? -sa : sa;
            F inv = one / st;
            rx = inv * (wa * x1 + sb * x2);
            ry = inv * (wa * y1 + sb * y2);
            rz = inv * (wa * z1 + sb * z2);
            rw = inv * (wa * w1 + sb * w2);
        }
    }
    if (!spherical) {
        F wa = one - t, wb = !(dot >= F(0.0f)) ? -t : t;
        rx = wa * x1 + wb * x2;
        ry = wa * y1 + wb * y2;
        rz = wa * z1 + wb * z2;
        rw = wa * w1 + wb * w2;
    }
    F len = Sqrt(rw * rw + ((rx * rx + ry * ry) + rz * rz));
    F inv = one / len;
    x = f(rx * inv);
    y = f(inv * ry);
    z = f(inv * rz);
    w = f(inv * rw);
}

// ---- natives ----

using live::kVoid;
constexpr u32 kObj = sizeof(Quaternion);

LEAF_METHOD(family(), "_ZN4Aska10Quaternion6CreateEPKNS_6VectorE", static_cast<void (Quaternion::*)(const Vector*)>(&Quaternion::Create), kObj, kVoid,
            "Aska::Quaternion::Create(Vector const*)", {});
LEAF_METHOD(family(), "_ZN4Aska10Quaternion6CreateEPKNS_6MatrixE", static_cast<void (Quaternion::*)(const Matrix*)>(&Quaternion::Create), kObj, kVoid,
            "Aska::Quaternion::Create(Matrix const*)", {});
LEAF_METHOD(family(), "_ZN4Aska10Quaternion15CreateFromEulerEfff14EnumRotateType", &Quaternion::CreateFromEuler, kObj, kVoid, "Aska::Quaternion::CreateFromEuler", {});
LEAF_METHOD(family(), "_ZN4Aska10Quaternion5SlerpEPKS0_S2_f", &Quaternion::Slerp, kObj, kVoid, "Aska::Quaternion::Slerp", {});

}  // namespace soa::native::math
