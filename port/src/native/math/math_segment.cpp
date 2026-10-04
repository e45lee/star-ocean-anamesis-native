// Aska::Segment: squared distances to a point and to another segment (math_layout.h;
// port/decomp/math/primitives.c). Written from the disassembly's operation order (no FMA anywhere:
// math_family.h) and its branch conditions, which Ghidra's C gets wrong for NaN inputs; the
// segment-segment case also ends in an FMAX(d, 0) Ghidra's output lacks.
#include "native/math/math_family.h"
#include "native/math/math_layout.h"

namespace soa::native::math {

namespace {

struct V3 {
    F x, y, z;
};
inline V3 xyz(const Vector& v) { return {F(v.x), F(v.y), F(v.z)}; }
inline F SquaredLength(const V3& v) { return (v.x * v.x + v.y * v.y) + v.z * v.z; }

// The squared distance from the point `origin + diff` (diff: relative to the segment's origin
// `seg_origin`... as the caller computed it) to the segment with direction `dir`; *t its parameter.
// Shared by Segment::SquaredDistance(Vector) and the degenerate cases of the segment-segment one.
F PointToSegment(V3 diff, V3 dir, F* t) {
    F dot = (diff.x * dir.x + diff.y * dir.y) + diff.z * dir.z;
    *t = F(0.0f);
    if (!(dot <= F(0.0f))) {  // (b.ls: a NaN dot projects)
        F len2 = SquaredLength(dir);
        if (dot >= len2) {
            diff = {diff.x - dir.x, diff.y - dir.y, diff.z - dir.z};
            *t = F(1.0f);
        } else {
            *t = dot / len2;
            diff = {diff.x - dir.x * *t, diff.y - dir.y * *t, diff.z - dir.z * *t};
        }
    }
    return SquaredLength(diff);
}

// The result of the segment-segment search: the squared distance accumulated from |diff|^2, and
// the two parameters.
struct Closest {
    F dist2, t0, t1;
};

}  // namespace

float Segment::SquaredDistance(const Vector* p, float* t) const {
    V3 diff = {F(p->x) - F(m_origin.x), F(p->y) - F(m_origin.y), F(p->z) - F(m_origin.z)};
    F param;
    F d = PointToSegment(diff, xyz(m_direction), &param);
    if (t) *t = f(param);
    return f(d);
}

float Segment::SquaredDistance(const Segment* o, float* t_this, float* t_other) const {
    const F kZero(0.0f), kOne(1.0f), kMinus2(-2.0f), kEps(kEpsilon);
    const V3 d0 = xyz(m_direction), d1 = xyz(o->m_direction);
    const F a = SquaredLength(d0), c = SquaredLength(d1);  // the squared lengths
    const F len0 = Sqrt(a), len1 = Sqrt(c);

    // A zero-length segment: the distance from its origin to the other segment.
    if (a == kZero) {
        if (t_this) *t_this = 0.0f;
        V3 diff = {F(m_origin.x) - F(o->m_origin.x), F(m_origin.y) - F(o->m_origin.y), F(m_origin.z) - F(o->m_origin.z)};
        F t;
        F d = PointToSegment(diff, d1, &t);
        if (t_other) *t_other = f(t);
        return f(d);
    }
    if (c == kZero) {
        if (t_other) *t_other = 0.0f;
        V3 diff = {F(o->m_origin.x) - F(m_origin.x), F(o->m_origin.y) - F(m_origin.y), F(o->m_origin.z) - F(m_origin.z)};
        F t;
        F d = PointToSegment(diff, d0, &t);
        if (t_this) *t_this = f(t);
        return f(d);
    }

    // Unit directions (left as they are when shorter than kEpsilon).
    auto unit = [&](const V3& v) {
        F n = Sqrt(SquaredLength(v));
        if (n < kEps) return v;
        F inv = kOne / n;
        return V3{inv * v.x, inv * v.y, inv * v.z};
    };
    const V3 u0 = unit(d0), u1 = unit(d1);
    const V3 diff = {F(o->m_origin.x) - F(m_origin.x), F(o->m_origin.y) - F(m_origin.y), F(o->m_origin.z) - F(m_origin.z)};
    const F f0 = SquaredLength(diff);  // the squared distance of the origins: the search adds to it
    const F dist = Sqrt(f0);
    V3 n = diff;  // the unit direction between the origins
    if (!(dist < kEps)) {
        F inv = kOne / dist;
        n = {diff.x * inv, diff.y * inv, diff.z * inv};
    }
    const F dotU = u0.z * u1.z + (u0.y * u1.y + u0.x * u1.x);
    const F det = (a * c) * (dotU * dotU + F(-1.0f));
    const F b = (d0.x * d1.x + d0.y * d1.y) + d0.z * d1.z;
    const F d = (diff.x * d0.x + diff.y * d0.y) + diff.z * d0.z;
    const F e = (diff.x * d1.x + diff.y * d1.y) + diff.z * d1.z;
    const F sign = det < kZero ? F(-1.0f) : kOne;
    const F absdet = Abs(det);

    // The ends of the search: (squared distance, t0, t1), each with the guest's association.
    auto zero = [&] { return Closest{f0, kZero, kZero}; };
    auto end0 = [&] { return Closest{(f0 + a) + d * kMinus2, kOne, kZero}; };  // this's end, other's origin
    auto inner0 = [&] {  // other's origin projected on this
        F t0 = d / a;
        return Closest{f0 - d * t0, t0, kZero};
    };
    auto end1 = [&] { return Closest{(f0 + c) + (e + e), kZero, kOne}; };  // this's origin, other's end
    auto inner1_from_origin0 = [&] {  // this's origin projected on other
        if (e >= kZero) return zero();
        if (c <= -e) return end1();
        F t1 = -e / c;
        return Closest{f0 + e * t1, kZero, t1};
    };
    auto inner1_from_end0 = [&](F bme, bool add_d_first) {  // this's end projected on other
        F t1 = bme / c;
        if (add_d_first) return Closest{((f0 + a) + d * kMinus2) - bme * t1, kOne, t1};
        return Closest{((f0 + a) - bme * t1) + d * kMinus2, kOne, t1};
    };
    auto ends_ab060 = [&](F bme) { return Closest{(f0 + (a + c)) + (d + bme) * kMinus2, kOne, kOne}; };
    auto ends_ab120 = [&](F dpb) { return Closest{(a + (f0 + c)) + ((e - dpb) + (e - dpb)), kOne, kOne}; };
    auto ends_aaf74 = [&](F dpb) { return Closest{(f0 + (a + c)) + ((e - dpb) + (e - dpb)), kOne, kOne}; };
    auto inner0_to_end1 = [&](F dpb) {  // other's end projected on this (ab08c)
        F t0 = dpb / a;
        return Closest{(e + e) + ((f0 + c) - dpb * t0), t0, kOne};
    };
    auto inner0_to_end1_b = [&](F dpb) {  // the same, associated differently (aaeb8)
        F t0 = dpb / a;
        return Closest{((f0 + c) + (e + e)) - dpb * t0, t0, kOne};
    };
    auto end1_c_first = [&] { return Closest{c + (f0 + (e + e)), kZero, kOne}; };

    Closest r;
    if (!(absdet >= kEps)) {
        // (Nearly) parallel.
        if (b < kZero) {
            if (d <= kZero) r = zero();
            else if (d <= a) r = inner0();
            else {
                F bme = b - e;
                if (bme >= c) r = Closest{(f0 + (a + c)) + ((e - bme) + (e - bme)), kOne, kOne};
                else r = inner1_from_end0(bme, false);
            }
        } else {
            if (a <= d) r = end0();
            else if (d >= kZero) r = inner0();
            else if (b <= -d) r = end1();
            else {
                F t1 = -d / b;
                r = Closest{f0 + t1 * ((e + e) + c * t1), kZero, t1};
            }
        }
    } else {
        const F nu0 = n.z * u0.z + (n.y * u0.y + n.x * u0.x);
        const F nu1 = n.z * u1.z + (n.y * u1.y + n.x * u1.x);
        const F S = sign * ((c * (len0 * dist)) * (dotU * nu1 - nu0));  // t0 * |det|
        const F T = sign * (((a * len1) * dist) * (nu1 - dotU * nu0));  // t1 * |det|
        auto beyond_end0 = [&] {  // this's end against other (aae28)
            F bme = b - e;
            if (bme <= kZero) return end0();
            if (bme >= c) return ends_ab060(bme);
            return inner1_from_end0(bme, false);
        };
        if (S >= kZero) {
            if (absdet >= S) {
                if (!(T >= kZero)) {
                    if (d <= kZero) r = zero();
                    else if (d >= a) r = end0();
                    else r = inner0();
                } else if (absdet >= T) {
                    // Interior: both parameters inside.
                    F inv = kOne / absdet;
                    F t0 = inv * S, t1 = inv * T;
                    F s = t0 * (a * t0 + d * kMinus2) + t1 * (c * t1 + (e + e));
                    r = Closest{f0 + (s - b * (t1 * (t0 + t0))), t0, t1};
                } else {
                    F dpb = d + b;
                    if (dpb <= kZero) r = end1_c_first();
                    else if (a <= dpb) r = ends_ab120(dpb);
                    else r = inner0_to_end1_b(dpb);
                }
            } else if (!(T >= kZero)) {
                if (!(d < a)) {
                    F bme = b - e;
                    if (bme <= kZero) r = end0();
                    else if (c <= bme) r = ends_ab060(bme);
                    else r = inner1_from_end0(bme, true);
                } else if (!(d <= kZero)) r = inner0();
                else r = zero();
            } else if (absdet >= T) {
                r = beyond_end0();
            } else {
                F dpb = d + b;
                if (a >= dpb) r = dpb <= kZero ? end1() : inner0_to_end1(dpb);
                else r = beyond_end0();
            }
        } else if (T >= kZero) {
            if (absdet >= T) r = inner1_from_origin0();
            else {
                F dpb = d + b;
                if (dpb >= kZero) r = !(a <= dpb) ? inner0_to_end1(dpb) : ends_aaf74(dpb);
                else r = inner1_from_origin0();
            }
        } else {
            if (!(d >= kZero)) r = inner1_from_origin0();
            else if (a <= d) r = end0();
            else r = inner0();
        }
    }
    if (t_this) *t_this = f(r.t0);
    if (t_other) *t_other = f(r.t1);
    return f(Max(r.dist2, kZero));
}

// ---- natives ----
// (const members: `this` is input only, so it isn't snapshotted: restoring it for the replay would
// rewind another thread's write to it, and a difference there could only be such a write)

using live::kFloat;
using live::out;

LEAF_METHOD(family(), "_ZNK4Aska7Segment15SquaredDistanceEPKNS_6VectorEPf", static_cast<float (Segment::*)(const Vector*, float*) const>(&Segment::SquaredDistance),
            0, kFloat, "Aska::Segment::SquaredDistance(Vector const*, float*)", {out(2, 4)});
LEAF_METHOD(family(), "_ZNK4Aska7Segment15SquaredDistanceEPKS0_PfS3_", static_cast<float (Segment::*)(const Segment*, float*, float*) const>(&Segment::SquaredDistance),
            0, kFloat, "Aska::Segment::SquaredDistance(Segment const*, float*, float*)", {out(2, 4), out(3, 4)});

}  // namespace soa::native::math
