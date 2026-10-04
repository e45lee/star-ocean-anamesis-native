// Differential tests of Aska::Segment's natives (math_segment.cpp) against the 3.7.0 guest.
#include "native/math/math_layout.h"
#include "native/math/math_test_util.h"

namespace soa::native::math {

using namespace test;

namespace {

// A segment: random, or (with the case number's help) degenerate, or parallel / anti-parallel /
// collinear to `other` so every branch of the search runs.
Segment rand_segment(TestContext& t, const Segment* other, int special) {
    Segment s{rand_vector(t, 10, special), rand_vector(t, 5, special)};
    int kind = t.rand_int(0, 19);
    if (kind == 0) s.m_direction = Vector{0, 0, 0, s.m_direction.w};
    else if (kind == 1) s.m_direction.x = s.m_direction.y = 0;
    else if (other && kind <= 6) {
        float k = kind <= 3 ? rand_float(t, 3, 0) : (kind == 4 ? 1.0f : -1.0f);
        const Vector& d = other->m_direction;
        s.m_direction = Vector{d.x * k, d.y * k, d.z * k, s.m_direction.w};
        if (kind == 5) s.m_direction.x += 1e-4f;  // nearly parallel
        if (kind == 6) s.m_origin = Vector{other->m_origin.x + d.x * 0.5f, other->m_origin.y + d.y * 0.5f, other->m_origin.z + d.z * 0.5f, 1};  // collinear
    } else if (kind == 7) {
        s.m_origin = Vector{(float)t.rand_int(-2, 2), (float)t.rand_int(-2, 2), (float)t.rand_int(-2, 2), 1};
        s.m_direction = Vector{(float)t.rand_int(-2, 2), (float)t.rand_int(-2, 2), (float)t.rand_int(-2, 2), 0};
    }
    return s;
}

}  // namespace

NATIVE_TEST("math/segment-point") {
    Mismatches bad{t, "Segment::SquaredDistance(Vector)"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 15000 ? 0 : 150;
        Segment s = rand_segment(t, nullptr, special);
        Vector p = rand_vector(t, 12, special);
        float gt = -7, nt = -7;
        bool with_t = k % 5 != 0;
        GuestResult g = t.call("_ZNK4Aska7Segment15SquaredDistanceEPKNS_6VectorEPf", GuestArgs().p(&s).p(&p).p(with_t ? &gt : nullptr));
        float n = s.SquaredDistance(&p, with_t ? &nt : nullptr);
        float gr = from_bits((u32)g.v0.lo);
        bad.check(k, same(gr, n) && same(gt, nt), "guest " + hex(gr) + " t " + hex(gt) + ", native " + hex(n) + " t " + hex(nt));
    }
}

NATIVE_TEST("math/segment-segment") {
    Mismatches bad{t, "Segment::SquaredDistance(Segment)"};
    for (int k = 0; k < 40000; k++) {
        int special = k < 30000 ? 0 : 150;
        Segment a = rand_segment(t, nullptr, special);
        Segment b = rand_segment(t, &a, special);
        if (k % 2) std::swap(a, b);
        float g0 = -7, g1 = -7, n0 = -7, n1 = -7;
        int outs = k % 4;  // which out-parameters are passed
        float* gp0 = outs & 1 ? nullptr : &g0;
        float* gp1 = outs & 2 ? nullptr : &g1;
        float* np0 = outs & 1 ? nullptr : &n0;
        float* np1 = outs & 2 ? nullptr : &n1;
        GuestResult g = t.call("_ZNK4Aska7Segment15SquaredDistanceEPKS0_PfS3_", GuestArgs().p(&a).p(&b).p(gp0).p(gp1));
        float n = a.SquaredDistance(&b, np0, np1);
        float gr = from_bits((u32)g.v0.lo);
        bad.check(k, same(gr, n) && same(g0, n0) && same(g1, n1),
                  "guest " + hex(gr) + " t " + hex(g0) + " " + hex(g1) + ", native " + hex(n) + " t " + hex(n0) + " " + hex(n1));
    }
}

}  // namespace soa::native::math
