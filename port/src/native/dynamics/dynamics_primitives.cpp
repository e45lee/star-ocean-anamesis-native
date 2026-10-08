// The dynamics primitives: the collision shapes' Run (follow the scene node), Update (interpolate
// back within a frame) and TestIntersection (dynamics_layout.h; port/decomp/dynamics/primitives.c).
// Written from the disassembly's operation order and branch conditions (dynamics_family.h).
#include <cstring>

#include "native/dynamics/dynamics_family.h"
#include "native/dynamics/gen/dynamics_addresses.h"

namespace soa::native::dynamics {

namespace {

struct V3 {
    F x, y, z;
};
inline V3 xyz(const Vector& v) { return {F(v.x), F(v.y), F(v.z)}; }
// (a.x * a.x + a.y * a.y) + a.z * a.z
inline F SquaredLength(const V3& a) { return (a.x * a.x + a.y * a.y) + a.z * a.z; }

const F kEps(math::kEpsilon);  // 0x26e519c: shorter vectors aren't normalized
const F kOne(1.0f);

// A guest .rodata / data object.
template <typename T>
const T& guest_at(u64 vaddr) {
    return *reinterpret_cast<const T*>(main_lib()->base + vaddr);
}

// The guest's math helpers (guest code): Vector::ApplyMatrix(out, m) const (out = m v, 4x4) and
// ApplyMatrixNoTransport (the 3x3 part, w = 1).
void ApplyMatrix(const Vector* v, Vector* out, const Matrix* m) {
    static const u64 fn = fn_addr("_ZNK4Aska6Vector11ApplyMatrixEPS0_PKNS_6MatrixE");
    call(fn, {(u64)v, (u64)out, (u64)m});
}
void ApplyMatrixNoTransport(const Vector* v, Vector* out, const Matrix* m) {
    static const u64 fn = fn_addr("_ZNK4Aska6Vector22ApplyMatrixNoTransportEPS0_PKNS_6MatrixE");
    call(fn, {(u64)v, (u64)out, (u64)m});
}

// v scaled to unit length in place, unless shorter than kEpsilon (b.mi: a NaN length scales).
void NormalizeInPlace(Vector* v) {
    F len = Sqrt(SquaredLength(xyz(*v)));
    if (len < kEps) return;
    F inv = kOne / len;
    v->x = f(inv * F(v->x));
    v->y = f(inv * F(v->y));
    v->z = f(inv * F(v->z));
}

// The node's stale matrix rebuilt (slot 21), as every Run starts.
void MakeMatrixIfStale(HierarchicalObject* h) {
    if (h->m_hoc.m_flags & kHocMatrixStale) vcall(h, kSlotMakeMatrix);
}
const Matrix* WorldMatrix(HierarchicalObject* h) { return reinterpret_cast<const Matrix*>(vcall(h, kSlotWorldMatrix)); }

// HierarchicalObject::m_invWorld made current (m_hoc.m_flags bit 2), inline in the primitives'
// Run: a rigid transform's inverse (the transposed rotation, -R^T t, the row (0, 0, 0, 1) from
// .rodata) when property 8 (m_flags2 bits 0-1) is 0, else Matrix::InvertLowError.
void MakeInverse(HierarchicalObject* h) {
    u8 flags = h->m_hoc.m_flags;
    if (flags & kHocInverseValid) return;
    const Matrix& m = h->m_hoc.m_world;
    Matrix& inv = h->m_invWorld;
    if (h->m_hoc.m_flags2 & 3) {
        static const u64 fn = fn_addr("_ZNK4Aska6Matrix14InvertLowErrorEPS0_");
        call(fn, {(u64)&m, (u64)&inv});
        flags = h->m_hoc.m_flags;
    } else {
        const F m00(m.m[0][0]), m01(m.m[0][1]), m02(m.m[0][2]), m03(m.m[0][3]);
        const F m10(m.m[1][0]), m11(m.m[1][1]), m12(m.m[1][2]), m13(m.m[1][3]);
        const F m20(m.m[2][0]), m21(m.m[2][1]), m22(m.m[2][2]), m23(m.m[2][3]);
        F t0 = -((m00 * m03 + m10 * m13) + m20 * m23);
        F t1 = -((m03 * m01 + m13 * m11) + m23 * m21);
        F t2 = -((m03 * m02 + m13 * m12) + m23 * m22);
        const Matrix rows{{{m.m[0][0], m.m[1][0], m.m[2][0], f(t0)},
                           {m.m[0][1], m.m[1][1], m.m[2][1], f(t1)},
                           {m.m[0][2], m.m[1][2], m.m[2][2], f(t2)},
                           {0, 0, 0, 0}}};
        std::memcpy(inv.m[0], rows.m[0], sizeof rows.m[0] * 3);
        std::memcpy(inv.m[3], &guest_at<Vector>(kRigidInverseLastRow), sizeof(Vector));
    }
    h->m_hoc.m_flags = flags | kHocInverseValid;
}

// After the new position: velocity = new - previous (w = the new w), current = new.
void Track(const Vector& pos, F px, F py, F pz, Vector* velocity, Vector* current) {
    Vector now = pos;
    *current = now;
    velocity->x = f(F(now.x) - px);
    velocity->y = f(F(now.y) - py);
    velocity->z = f(F(now.z) - pz);
    velocity->w = now.w;
}

// current - (1 - t) * velocity (xyz), the end flag taking the current position as it is.
void Interpolate(const Vector& current, const Vector& velocity, float t, Vector* out) {
    F s = kOne - F(t);
    F vx = s * F(velocity.x), vy = s * F(velocity.y), vz = s * F(velocity.z);
    out->x = f(F(current.x) - vx);
    out->y = f(F(current.y) - vy);
    out->z = f(F(current.z) - vz);
}

}  // namespace

// ---- Run ----

void DynamicsSphere::Run() {
    HierarchicalObject* h = base.m_handler;
    if (!h) return;
    const F px(m_shape.m_current.x), py(m_shape.m_current.y), pz(m_shape.m_current.z);
    MakeMatrixIfStale(h);
    ApplyMatrix(&base.m_localPosition, &m_shape.m_center, WorldMatrix(h));
    Track(m_shape.m_center, px, py, pz, &m_shape.m_velocity, &m_shape.m_current);
}

void DynamicsPlane::Run() {
    HierarchicalObject* h = base.m_handler;
    if (!h) return;
    const F px(m_shape.m_current.x), py(m_shape.m_current.y), pz(m_shape.m_current.z);
    MakeMatrixIfStale(h);
    ApplyMatrix(&base.m_localPosition, &m_shape.m_point, WorldMatrix(h));
    Track(m_shape.m_point, px, py, pz, &m_shape.m_velocity, &m_shape.m_current);
    ApplyMatrixNoTransport(&guest_at<Vector>(kVaddrUnitY), &m_shape.m_normal, WorldMatrix(h));
    NormalizeInPlace(&m_shape.m_normal);
}

void DynamicsCapsule::Run() {
    HierarchicalObject* h = base.m_handler;
    if (!h) return;
    DYNAMICS_CAPSULE& s = m_shape;
    const F px(s.m_current.x), py(s.m_current.y), pz(s.m_current.z);
    MakeMatrixIfStale(h);
    MakeInverse(h);
    ApplyMatrix(&base.m_localPosition, &s.m_segment.m_origin, WorldMatrix(h));
    Track(s.m_segment.m_origin, px, py, pz, &s.m_velocity, &s.m_current);
    // The axis through the world matrix with its columns scaled to unit length (no epsilon: a
    // zero column gives infinities), i.e. without the node's scale.
    Matrix m = *WorldMatrix(h);
    F inv[3];
    for (int c = 0; c < 3; c++) {
        F a(m.m[0][c]), b(m.m[1][c]), d(m.m[2][c]);
        inv[c] = kOne / Sqrt((a * a + b * b) + d * d);
    }
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++) m.m[r][c] = f(inv[c] * F(m.m[r][c]));
    ApplyMatrixNoTransport(&s.m_otherSegment.m_direction, &s.m_segment.m_direction, &m);
}

void DynamicsCube::Run() {
    HierarchicalObject* h = base.m_handler;
    if (!h) return;
    DYNAMICS_CUBE& s = m_shape;
    const F px(s.m_current.x), py(s.m_current.y), pz(s.m_current.z);
    MakeMatrixIfStale(h);
    s.m_world = *WorldMatrix(h);
    ApplyMatrix(&base.m_localPosition, &s.m_center, &s.m_world);
    Track(s.m_center, px, py, pz, &s.m_velocity, &s.m_current);
    ApplyMatrixNoTransport(&guest_at<Vector>(kVaddrUnitX), &s.m_axis[0], &s.m_world);
    ApplyMatrixNoTransport(&guest_at<Vector>(kVaddrUnitY), &s.m_axis[1], &s.m_world);
    ApplyMatrixNoTransport(&guest_at<Vector>(kVaddrUnitZ), &s.m_axis[2], &s.m_world);
    for (Vector& a : s.m_axis) NormalizeInPlace(&a);
    MakeInverse(h);
    s.m_invWorld = h->m_invWorld;
}

// ---- Update ----

void DynamicsSphere::Update(float t, bool end) {
    DYNAMICS_SPHERE& s = m_shape;
    if (end) {
        s.m_center.x = s.m_current.x;
        s.m_center.y = s.m_current.y;
        s.m_center.z = s.m_current.z;
    } else {
        Interpolate(s.m_current, s.m_velocity, t, &s.m_center);
    }
    s.m_center.w = s.m_current.w;
}

void DynamicsPlane::Update(float t, bool end) {
    DYNAMICS_PLANE& s = m_shape;
    if (end) {
        s.m_point.x = s.m_current.x;
        s.m_point.y = s.m_current.y;
        s.m_point.z = s.m_current.z;
    } else {
        Interpolate(s.m_current, s.m_velocity, t, &s.m_point);
    }
    s.m_point.w = s.m_current.w;
}

void DynamicsCube::Update(float t, bool end) {
    DYNAMICS_CUBE& s = m_shape;
    if (end) {
        s.m_center.x = s.m_current.x;
        s.m_center.y = s.m_current.y;
        s.m_center.z = s.m_current.z;
    } else {
        Interpolate(s.m_current, s.m_velocity, t, &s.m_center);
    }
    s.m_center.w = s.m_current.w;
}

void DynamicsCapsule::Update(float t, bool end) {
    DYNAMICS_CAPSULE& s = m_shape;
    Vector& o = s.m_segment.m_origin;
    if (end) {  // (w = 1 here, the current w otherwise)
        o = Vector{s.m_current.x, s.m_current.y, s.m_current.z, 1.0f};
        return;
    }
    Interpolate(s.m_current, s.m_velocity, t, &o);
    o.w = s.m_current.w;
}

// ---- TestIntersection ----

bool DYNAMICS_CAPSULE::TestIntersection(DYNAMICS_CAPSULE* other, bool, Vector* normal, float* t, float* depth) {
    float t_this, t_other;
    F d2(m_segment.SquaredDistance(&other->m_otherSegment, &t_this, &t_other));
    F reach = F(m_radius) + F(other->m_radius);
    if (!(d2 <= reach * reach)) return false;  // (b.ls: a NaN distance misses)
    const Segment& a = m_segment;
    const Segment& b = other->m_otherSegment;
    const F ta(t_this), tb(t_other);
    // The closest points: origin + t * direction (x: t first; y, z: direction first).
    F ax = F(a.m_origin.x) + ta * F(a.m_direction.x);
    F ay = F(a.m_origin.y) + F(a.m_direction.y) * ta;
    F az = F(a.m_origin.z) + F(a.m_direction.z) * ta;
    F bx = F(b.m_origin.x) + tb * F(b.m_direction.x);
    F by = F(b.m_origin.y) + F(b.m_direction.y) * tb;
    F bz = F(b.m_origin.z) + F(b.m_direction.z) * tb;
    normal->x = f(bx - ax);
    normal->y = f(by - ay);
    normal->z = f(bz - az);
    F len = Sqrt(SquaredLength(xyz(*normal)));
    normal->w = 1.0f;
    if (!(len < kEps)) {
        F inv = kOne / len;
        normal->x = f(inv * F(normal->x));
        normal->y = f(inv * F(normal->y));
        normal->z = f(inv * F(normal->z));
    }
    *t = t_other;
    *depth = f(reach - Sqrt(d2));
    return true;
}

bool DYNAMICS_CAPSULE::TestIntersection(const Vector* p, float r, Vector* out) {
    float t;
    F d = Sqrt(F(m_segment.SquaredDistance(p, &t)));
    F over = d - (F(m_radius) - F(r));
    if (!(over >= F(0.0f))) return false;  // (b.ge: a NaN stays)
    const Segment& s = m_segment;
    const F tt(t);
    // From p to its closest point on the axis.
    F dx = (tt * F(s.m_direction.x) + F(s.m_origin.x)) - F(p->x);
    F dy = (F(s.m_direction.y) * tt + F(s.m_origin.y)) - F(p->y);
    F dz = (F(s.m_direction.z) * tt + F(s.m_origin.z)) - F(p->z);
    F len = Sqrt((dx * dx + dy * dy) + dz * dz);
    if (!(len < kEps)) {
        F inv = kOne / len;
        dx = dx * inv;
        dy = dy * inv;
        dz = dz * inv;
    }
    out->x = f(F(p->x) + over * dx);
    out->y = f(over * dy + F(p->y));
    out->w = 1.0f;
    out->z = f(over * dz + F(p->z));
    return true;
}

bool DYNAMICS_CUBE::TestIntersection(const Vector* p, float r, Vector* out) {
    static const u64 apply = fn_addr("_ZNK4Aska6Vector11ApplyMatrixEPS0_PKNS_6MatrixE");
    alignas(16) Vector local;
    call(apply, {(u64)p, (u64)&local, (u64)&m_invWorld});
    *out = local;
    const F rr(r);
    const F c[3] = {F(local.x), F(local.y), F(local.z)};
    const float* half = &m_halfExtents.x;
    float* o = &out->x;
    bool hit = false;
    for (int i = 0; i < 3; i++) {
        F h(half[i]);
        if (c[i] - rr < -h) {  // (b.pl: a NaN takes the upper test)
            o[i] = f(rr - h);
            hit = true;
        } else if (c[i] + rr > h) {  // (b.le: a NaN is inside)
            o[i] = f(h - rr);
            hit = true;
        }
    }
    if (!hit) return false;
    call(apply, {(u64)out, (u64)out, (u64)&m_world});
    return true;
}

bool DynamicsSphere::TestIntersection(DYNAMICS_CAPSULE* other, bool, Vector* normal, float* t, float* depth) {
    const DYNAMICS_SPHERE& s = m_shape;
    float tp;
    F d2(other->m_otherSegment.SquaredDistance(&s.m_center, &tp));
    F reach = F(s.m_radius) + F(other->m_radius);
    if (!(d2 <= reach * reach)) return false;  // (b.ls)
    const Segment& b = other->m_otherSegment;
    const F tt(tp);
    F nx = (tt * F(b.m_direction.x) + F(b.m_origin.x)) - F(s.m_center.x);
    F ny = (F(b.m_direction.y) * tt + F(b.m_origin.y)) - F(s.m_center.y);
    F nz = (F(b.m_direction.z) * tt + F(b.m_origin.z)) - F(s.m_center.z);
    float w = b.m_direction.w;
    F len = Sqrt((nx * nx + ny * ny) + nz * nz);
    if (!(len < kEps)) {
        F inv = kOne / len;
        nx = nx * inv;
        ny = ny * inv;
        nz = nz * inv;
    }
    normal->x = f(nx);
    normal->y = f(ny);
    normal->z = f(nz);
    normal->w = w;
    *t = tp;
    *depth = f(reach - Sqrt(d2));
    return true;
}

bool DynamicsSphere::TestIntersection(const Vector* p, float r, Vector* out) {
    const DYNAMICS_SPHERE& s = m_shape;
    F dx = F(p->x) - F(s.m_center.x), dy = F(p->y) - F(s.m_center.y), dz = F(p->z) - F(s.m_center.z);
    F d2 = (dx * dx + dy * dy) + dz * dz;
    F over = Sqrt(d2) - (F(s.m_radius) - F(r));
    if (!(over >= F(0.0f))) return false;  // (b.ge)
    F len = Sqrt(d2);
    if (!(len < kEps)) {
        F inv = kOne / len;
        dx = dx * inv;
        dy = dy * inv;
        dz = dz * inv;
    }
    out->x = f(F(p->x) - over * dx);
    out->y = f(F(p->y) - over * dy);
    out->z = f(F(p->z) - over * dz);
    out->w = p->w;
    return true;
}

bool DynamicsPlane::TestIntersection(const Vector* p, float r, Vector* out) {
    const DYNAMICS_PLANE& s = m_shape;
    const F nx(s.m_normal.x), ny(s.m_normal.y), nz(s.m_normal.z);
    const F x(p->x), y(p->y), z(p->z);
    F dist = ((x - F(s.m_point.x)) * nx + (y - F(s.m_point.y)) * ny) + (z - F(s.m_point.z)) * nz;
    const F rr(r);
    if (!(dist <= rr)) return false;  // (b.ls: a NaN distance misses)
    float w = p->w;
    F k = dist - rr;
    out->x = f(x - nx * k);
    out->y = f(y - ny * k);
    out->z = f(z - nz * k);
    out->w = w;
    return true;
}

// ---- registration ----

namespace {

using live::kInt;
using live::kVoid;
using live::out;

// Run also writes the node's flags and cached inverse (MakeInverse; Matrix::InvertLowError).
void NodeRegion(const u64 x[9], live::Regions& r) {
    auto* p = reinterpret_cast<const DynamicsPrimitive*>(x[0]);
    if (p && p->m_handler) r.add((u64)&p->m_handler->m_hoc.m_flags, offsetof(HierarchicalObject, unk_170) - offsetof(HierarchicalObject, m_hoc.m_flags));
}

#define DYN_RUN(sym, cls)                                                                                                        \
    static int NATIVE_CONCAT(dyn_run_, __LINE__) =                                                                               \
        family().extra(family().add_leaf(sym, &live::leaf_method<&cls::Run>, sizeof(cls), kVoid, "Aska::" #cls "::Run", {}), NodeRegion)

DYN_RUN("_ZN4Aska14DynamicsSphere3RunEv", DynamicsSphere);
DYN_RUN("_ZN4Aska13DynamicsPlane3RunEv", DynamicsPlane);
DYN_RUN("_ZN4Aska15DynamicsCapsule3RunEv", DynamicsCapsule);
DYN_RUN("_ZN4Aska12DynamicsCube3RunEv", DynamicsCube);

LEAF_METHOD(family(), "_ZN4Aska14DynamicsSphere6UpdateEfb", &DynamicsSphere::Update, sizeof(DynamicsSphere), kVoid, "Aska::DynamicsSphere::Update", {});
LEAF_METHOD(family(), "_ZN4Aska13DynamicsPlane6UpdateEfb", &DynamicsPlane::Update, sizeof(DynamicsPlane), kVoid, "Aska::DynamicsPlane::Update", {});
LEAF_METHOD(family(), "_ZN4Aska12DynamicsCube6UpdateEfb", &DynamicsCube::Update, sizeof(DynamicsCube), kVoid, "Aska::DynamicsCube::Update", {});
LEAF_METHOD(family(), "_ZN4Aska15DynamicsCapsule6UpdateEfb", &DynamicsCapsule::Update, sizeof(DynamicsCapsule), kVoid, "Aska::DynamicsCapsule::Update", {});

LEAF_METHOD(family(), "_ZN4Aska16DYNAMICS_CAPSULE16TestIntersectionEPS0_bPNS_6VectorEPfS4_",
            static_cast<bool (DYNAMICS_CAPSULE::*)(DYNAMICS_CAPSULE*, bool, Vector*, float*, float*)>(&DYNAMICS_CAPSULE::TestIntersection),
            sizeof(DYNAMICS_CAPSULE), kInt, "Aska::DYNAMICS_CAPSULE::TestIntersection(DYNAMICS_CAPSULE*)", {out(3, 16), out(4, 4), out(5, 4)});
LEAF_METHOD(family(), "_ZN4Aska16DYNAMICS_CAPSULE16TestIntersectionEPKNS_6VectorEfPS1_",
            static_cast<bool (DYNAMICS_CAPSULE::*)(const Vector*, float, Vector*)>(&DYNAMICS_CAPSULE::TestIntersection), sizeof(DYNAMICS_CAPSULE), kInt,
            "Aska::DYNAMICS_CAPSULE::TestIntersection(Vector const*)", {out(2, 16)});
LEAF_METHOD(family(), "_ZN4Aska13DYNAMICS_CUBE16TestIntersectionEPKNS_6VectorEfPS1_", &DYNAMICS_CUBE::TestIntersection, sizeof(DYNAMICS_CUBE), kInt,
            "Aska::DYNAMICS_CUBE::TestIntersection(Vector const*)", {out(2, 16)});
LEAF_METHOD(family(), "_ZN4Aska14DynamicsSphere16TestIntersectionEPNS_16DYNAMICS_CAPSULEEbPNS_6VectorEPfS5_",
            static_cast<bool (DynamicsSphere::*)(DYNAMICS_CAPSULE*, bool, Vector*, float*, float*)>(&DynamicsSphere::TestIntersection), sizeof(DynamicsSphere),
            kInt, "Aska::DynamicsSphere::TestIntersection(DYNAMICS_CAPSULE*)", {out(3, 16), out(4, 4), out(5, 4)});
LEAF_METHOD(family(), "_ZN4Aska14DynamicsSphere16TestIntersectionEPKNS_6VectorEfPS1_",
            static_cast<bool (DynamicsSphere::*)(const Vector*, float, Vector*)>(&DynamicsSphere::TestIntersection), sizeof(DynamicsSphere), kInt,
            "Aska::DynamicsSphere::TestIntersection(Vector const*)", {out(2, 16)});
LEAF_METHOD(family(), "_ZN4Aska13DynamicsPlane16TestIntersectionEPKNS_6VectorEfPS1_", &DynamicsPlane::TestIntersection, sizeof(DynamicsPlane), kInt,
            "Aska::DynamicsPlane::TestIntersection(Vector const*)", {out(2, 16)});

}  // namespace

}  // namespace soa::native::dynamics
