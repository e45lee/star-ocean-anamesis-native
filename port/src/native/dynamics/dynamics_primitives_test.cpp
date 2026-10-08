// Differential tests of the dynamics primitives' natives (dynamics_primitives.cpp) against the
// 3.7.0 guest: random shapes, points and nodes (ordinary values, then a share of special floats:
// signed zeros, NaNs with payloads, infinities, denormals), compared bit for bit.
#include <cstring>
#include <memory>

#include "native/dynamics/dynamics_layout.h"
#include "native/math/math_test_util.h"

namespace soa::native::dynamics {

using namespace math::test;

namespace {

float rf(TestContext& t, float r, int special) { return rand_float(t, r, special); }
Vector rv(TestContext& t, float r, int special) { return rand_vector(t, r, special); }

// Fills `n` bytes with random words (the fields the natives don't read keep their values).
void scramble(TestContext& t, void* p, size_t n) {
    auto* b = static_cast<u8*>(p);
    for (size_t i = 0; i < n; i++) b[i] = (u8)t.rand_int(0, 255);
}

// A segment of length 0..10 near the origin (sometimes degenerate).
Segment rand_seg(TestContext& t, int special) {
    Segment s{rv(t, 5, special), rv(t, 4, special)};
    if (t.rand_int(0, 15) == 0) s.m_direction = Vector{0, 0, 0, s.m_direction.w};
    return s;
}

DYNAMICS_CAPSULE rand_capsule(TestContext& t, int special) {
    DYNAMICS_CAPSULE c;
    scramble(t, &c, sizeof c);
    c.m_segment = rand_seg(t, special);
    c.m_otherSegment = rand_seg(t, special);
    c.m_radius = std::fabs(rf(t, 3, special));
    if (t.rand_int(0, 7) == 0) c.m_radius = rf(t, 3, special);
    return c;
}

// The point / radius a constraint test gets: near the shape, so both outcomes happen.
Vector rand_point(TestContext& t, int special) { return rv(t, 6, special); }

bool same_bytes(const void* a, const void* b, size_t n) { return std::memcmp(a, b, n) == 0; }

std::string vec(const Vector& v) { return hex(v.x) + " " + hex(v.y) + " " + hex(v.z) + " " + hex(v.w); }

}  // namespace

NATIVE_TEST("dynamics/capsule-capsule") {
    Mismatches bad{t, "DYNAMICS_CAPSULE::TestIntersection(DYNAMICS_CAPSULE*)"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 15000 ? 0 : 150;
        DYNAMICS_CAPSULE a = rand_capsule(t, special), b = rand_capsule(t, special);
        DYNAMICS_CAPSULE a2 = a, b2 = b;
        Vector gn{-7, -7, -7, -7}, nn = gn;
        float gt = -7, nt = -7, gd = -7, nd = -7;
        GuestResult g = t.call("_ZN4Aska16DYNAMICS_CAPSULE16TestIntersectionEPS0_bPNS_6VectorEPfS4_", GuestArgs().p(&a).p(&b).i(k & 1).p(&gn).p(&gt).p(&gd));
        bool n = a2.TestIntersection(&b2, k & 1, &nn, &nt, &nd);
        bad.check(k, ((g.x0 & 0xff) != 0) == n && same(gn, nn) && same(gt, nt) && same(gd, nd) && same_bytes(&a, &a2, sizeof a) && same_bytes(&b, &b2, sizeof b),
                  "guest " + std::to_string(g.x0 & 0xff) + " n " + vec(gn) + " t " + hex(gt) + " d " + hex(gd) + ", native " + std::to_string(n) + " n " + vec(nn) +
                      " t " + hex(nt) + " d " + hex(nd));
    }
}

NATIVE_TEST("dynamics/capsule-point") {
    Mismatches bad{t, "DYNAMICS_CAPSULE::TestIntersection(Vector const*)"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 15000 ? 0 : 150;
        DYNAMICS_CAPSULE a = rand_capsule(t, special), a2 = a;
        Vector p = rand_point(t, special);
        float r = rf(t, 1, special);
        Vector go{-7, -7, -7, -7}, no = go;
        bool alias = k % 7 == 0;  // out == p
        Vector gp = p, np = p;
        GuestResult g = t.call("_ZN4Aska16DYNAMICS_CAPSULE16TestIntersectionEPKNS_6VectorEfPS1_", GuestArgs().p(&a).p(&gp).f(r).p(alias ? &gp : &go));
        bool n = a2.TestIntersection(&np, r, alias ? &np : &no);
        bad.check(k, ((g.x0 & 0xff) != 0) == n && same(go, no) && same(gp, np) && same_bytes(&a, &a2, sizeof a),
                  "guest " + std::to_string(g.x0 & 0xff) + " " + vec(alias ? gp : go) + ", native " + std::to_string(n) + " " + vec(alias ? np : no));
    }
}

NATIVE_TEST("dynamics/cube-point") {
    Mismatches bad{t, "DYNAMICS_CUBE::TestIntersection(Vector const*)"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 15000 ? 0 : 150;
        auto a = std::make_unique<DYNAMICS_CUBE>();
        scramble(t, a.get(), sizeof *a);
        a->m_halfExtents = Vector{std::fabs(rf(t, 3, special)), std::fabs(rf(t, 3, special)), std::fabs(rf(t, 3, special)), 0};
        a->m_world = rand_matrix(t, special);
        a->m_invWorld = rand_matrix(t, special);
        auto a2 = std::make_unique<DYNAMICS_CUBE>(*a);
        Vector p = rand_point(t, special);
        float r = std::fabs(rf(t, 1, special));
        bool alias = k % 7 == 0;
        Vector gp = p, np = p, go{-7, -7, -7, -7}, no = go;
        GuestResult g = t.call("_ZN4Aska13DYNAMICS_CUBE16TestIntersectionEPKNS_6VectorEfPS1_", GuestArgs().p(a.get()).p(&gp).f(r).p(alias ? &gp : &go));
        bool n = a2->TestIntersection(&np, r, alias ? &np : &no);
        bad.check(k, ((g.x0 & 0xff) != 0) == n && same(go, no) && same(gp, np) && same_bytes(a.get(), a2.get(), sizeof *a),
                  "guest " + std::to_string(g.x0 & 0xff) + " " + vec(alias ? gp : go) + ", native " + std::to_string(n) + " " + vec(alias ? np : no));
    }
}

NATIVE_TEST("dynamics/sphere-capsule") {
    Mismatches bad{t, "DynamicsSphere::TestIntersection(DYNAMICS_CAPSULE*)"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 15000 ? 0 : 150;
        auto s = std::make_unique<DynamicsSphere>();
        scramble(t, s.get(), sizeof *s);
        s->m_shape.m_center = rv(t, 5, special);
        s->m_shape.m_radius = std::fabs(rf(t, 3, special));
        auto s2 = std::make_unique<DynamicsSphere>(*s);
        DYNAMICS_CAPSULE b = rand_capsule(t, special), b2 = b;
        Vector gn{-7, -7, -7, -7}, nn = gn;
        float gt = -7, nt = -7, gd = -7, nd = -7;
        GuestResult g = t.call("_ZN4Aska14DynamicsSphere16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_",
                               GuestArgs().p(s.get()).p(&b).i(k & 1).p(&gn).p(&gt).p(&gd));
        bool n = s2->TestIntersection(&b2, k & 1, &nn, &nt, &nd);
        bad.check(k, ((g.x0 & 0xff) != 0) == n && same(gn, nn) && same(gt, nt) && same(gd, nd) && same_bytes(s.get(), s2.get(), sizeof *s),
                  "guest " + std::to_string(g.x0 & 0xff) + " n " + vec(gn) + " t " + hex(gt) + " d " + hex(gd) + ", native " + std::to_string(n) + " n " + vec(nn) +
                      " t " + hex(nt) + " d " + hex(nd));
    }
}

NATIVE_TEST("dynamics/sphere-point") {
    Mismatches bad{t, "DynamicsSphere::TestIntersection(Vector const*)"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 15000 ? 0 : 150;
        auto s = std::make_unique<DynamicsSphere>();
        scramble(t, s.get(), sizeof *s);
        s->m_shape.m_center = rv(t, 5, special);
        s->m_shape.m_radius = std::fabs(rf(t, 5, special));
        auto s2 = std::make_unique<DynamicsSphere>(*s);
        Vector p = rand_point(t, special);
        float r = rf(t, 1, special);
        bool alias = k % 7 == 0;
        Vector gp = p, np = p, go{-7, -7, -7, -7}, no = go;
        GuestResult g = t.call("_ZN4Aska14DynamicsSphere16TestIntersectionEPKNS_6VectorEfPS1_", GuestArgs().p(s.get()).p(&gp).f(r).p(alias ? &gp : &go));
        bool n = s2->TestIntersection(&np, r, alias ? &np : &no);
        bad.check(k, ((g.x0 & 0xff) != 0) == n && same(go, no) && same(gp, np), "guest " + std::to_string(g.x0 & 0xff) + " " + vec(alias ? gp : go) + ", native " +
                                                                                   std::to_string(n) + " " + vec(alias ? np : no));
    }
}

NATIVE_TEST("dynamics/plane-point") {
    Mismatches bad{t, "DynamicsPlane::TestIntersection(Vector const*)"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 15000 ? 0 : 150;
        auto s = std::make_unique<DynamicsPlane>();
        scramble(t, s.get(), sizeof *s);
        s->m_shape.m_normal = rv(t, 1, special);
        s->m_shape.m_point = rv(t, 5, special);
        auto s2 = std::make_unique<DynamicsPlane>(*s);
        Vector p = rand_point(t, special);
        float r = rf(t, 1, special);
        bool alias = k % 7 == 0;
        Vector gp = p, np = p, go{-7, -7, -7, -7}, no = go;
        GuestResult g = t.call("_ZN4Aska13DynamicsPlane16TestIntersectionEPKNS_6VectorEfPS1_", GuestArgs().p(s.get()).p(&gp).f(r).p(alias ? &gp : &go));
        bool n = s2->TestIntersection(&np, r, alias ? &np : &no);
        bad.check(k, ((g.x0 & 0xff) != 0) == n && same(go, no) && same(gp, np), "guest " + std::to_string(g.x0 & 0xff) + " " + vec(alias ? gp : go) + ", native " +
                                                                                   std::to_string(n) + " " + vec(alias ? np : no));
    }
}

// Update(t, end) of every primitive: random object bytes, t and the flag.
NATIVE_TEST("dynamics/update") {
    struct Case {
        const char* sym;
        size_t size;
        void (*native)(void*, float, bool);
    };
    const Case cases[] = {
        {"_ZN4Aska14DynamicsSphere6UpdateEfb", sizeof(DynamicsSphere), [](void* p, float x, bool e) { static_cast<DynamicsSphere*>(p)->Update(x, e); }},
        {"_ZN4Aska13DynamicsPlane6UpdateEfb", sizeof(DynamicsPlane), [](void* p, float x, bool e) { static_cast<DynamicsPlane*>(p)->Update(x, e); }},
        {"_ZN4Aska12DynamicsCube6UpdateEfb", sizeof(DynamicsCube), [](void* p, float x, bool e) { static_cast<DynamicsCube*>(p)->Update(x, e); }},
        {"_ZN4Aska15DynamicsCapsule6UpdateEfb", sizeof(DynamicsCapsule), [](void* p, float x, bool e) { static_cast<DynamicsCapsule*>(p)->Update(x, e); }},
    };
    for (const Case& c : cases) {
        Mismatches bad{t, c.sym};
        for (int k = 0; k < 4000; k++) {
            int special = k < 3000 ? 0 : 150;
            alignas(16) u8 g[0x170], n[0x170];
            for (size_t i = 0; i < c.size; i += 4) {
                float v = rf(t, 10, special);
                std::memcpy(g + i, &v, 4);
            }
            std::memcpy(n, g, c.size);
            float x = rf(t, 1, special);
            bool end = k % 3 == 0;
            t.call(c.sym, GuestArgs().p(g).i(end).f(x));
            c.native(n, x, end);
            for (size_t i = 0; i < c.size; i++)
                if (g[i] != n[i]) {
                    bad.add(k, "byte +0x" + std::to_string(i) + " differs");
                    break;
                }
        }
    }
}

// Run() of every primitive over a node: a HierarchicalObject with the guest's vtable (slot 19
// WorldMatrix returns its world matrix), the matrix fresh (MakeMatrix needs a whole node: the
// live check covers it), the inverse cached or not, property 8 zero (the rigid inverse inline) or
// not (Matrix::InvertLowError). The guest and the native each run on their own copy of primitive
// and node; both copies must end the same.
NATIVE_TEST("dynamics/run") {
    struct Case {
        const char* sym;
        size_t size;
        void (*native)(void*);
    };
    const Case cases[] = {
        {"_ZN4Aska14DynamicsSphere3RunEv", sizeof(DynamicsSphere), [](void* p) { static_cast<DynamicsSphere*>(p)->Run(); }},
        {"_ZN4Aska13DynamicsPlane3RunEv", sizeof(DynamicsPlane), [](void* p) { static_cast<DynamicsPlane*>(p)->Run(); }},
        {"_ZN4Aska15DynamicsCapsule3RunEv", sizeof(DynamicsCapsule), [](void* p) { static_cast<DynamicsCapsule*>(p)->Run(); }},
        {"_ZN4Aska12DynamicsCube3RunEv", sizeof(DynamicsCube), [](void* p) { static_cast<DynamicsCube*>(p)->Run(); }},
    };
    const void* vt = reinterpret_cast<const void*>(t.sym("_ZTVN4Aska18HierarchicalObjectE") + 0x10);
    constexpr size_t kNode = 0x1a0;
    for (const Case& c : cases) {
        Mismatches bad{t, c.sym};
        for (int k = 0; k < 3000; k++) {
            int special = k < 2400 ? 0 : 150;
            alignas(16) u8 gnode[kNode], nnode[kNode], g[0x170], n[0x170];
            scramble(t, gnode, kNode);
            auto* h = reinterpret_cast<HierarchicalObject*>(gnode);
            h->base.link.vtable = vt;
            h->m_hoc.m_world = rand_matrix(t, special);
            h->m_hoc.m_flags = (u8)(t.rand_int(0, 255) & ~kHocMatrixStale);
            if (t.rand_int(0, 1)) h->m_hoc.m_flags &= ~kHocInverseValid;
            h->m_hoc.m_flags2 = (u8)(t.rand_int(0, 3) ? t.rand_int(0, 255) & ~3 : t.rand_int(0, 255));
            std::memcpy(nnode, gnode, kNode);
            for (size_t i = 0; i < c.size; i += 4) {
                float v = rf(t, 10, special);
                std::memcpy(g + i, &v, 4);
            }
            reinterpret_cast<DynamicsPrimitive*>(g)->m_handler = k % 50 == 0 ? nullptr : h;
            std::memcpy(n, g, c.size);
            if (reinterpret_cast<DynamicsPrimitive*>(n)->m_handler)
                reinterpret_cast<DynamicsPrimitive*>(n)->m_handler = reinterpret_cast<HierarchicalObject*>(nnode);
            t.call(c.sym, GuestArgs().p(g));
            c.native(n);
            reinterpret_cast<DynamicsPrimitive*>(n)->m_handler = reinterpret_cast<DynamicsPrimitive*>(g)->m_handler;
            bool ok = true;
            for (size_t i = 0; i < c.size && ok; i++)
                if (g[i] != n[i]) bad.add(k, "object byte +0x" + std::to_string(i) + " differs"), ok = false;
            for (size_t i = 0; i < kNode && ok; i++)
                if (gnode[i] != nnode[i]) bad.add(k, "node byte +0x" + std::to_string(i) + " differs"), ok = false;
        }
    }
}

}  // namespace soa::native::dynamics
