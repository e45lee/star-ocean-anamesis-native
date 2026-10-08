// The ADM solver's local helpers (no symbols; bound by address: addresses.txt): the link (distance)
// constraint (dynamics_layout.h ADMSolver; port/decomp/dynamics/adm_local.c). Written from the
// disassembly: the NEON lanes as scalars in the guest's operation order, its estimate
// instructions through dynamics_neon.h.
#include <cinttypes>
#include <cstdio>
#include <cstdlib>

#include "native/dynamics/dynamics_family.h"
#include "native/dynamics/dynamics_neon.h"
#include "native/dynamics/gen/dynamics_addresses.h"

namespace soa::native::dynamics {

namespace {
const F kZero(0.0f), kOne(1.0f), kHalf(0.5f), kEps(math::kEpsilon);
// ResolveContact's limits on t and the factor beyond them (.rodata 0.01f, 0.99f, 100.0f: exact
// literals; the tests put t on both sides of each).
constexpr float kNearStart = 0.01f, kNearEnd = 0.99f, kFar = 100.0f;
F frecpe(F x) { return F(neon::frecpe(x.v)); }
F frsqrte(F x) { return F(neon::frsqrte(x.v)); }
F frecps(F a, F b) { return F(neon::frecps(a.v, b.v)); }
F frsqrts(F a, F b) { return F(neon::frsqrts(a.v, b.v)); }
}  // namespace

void ADMSolver::SolveLink(u8 mode, ADMJoint* a, ADMJoint* b, float rest, float k1, float k2) {
    const Vector pa = a->m_position, pb = b->m_position;
    const F wa(a->m_mass), wb(b->m_mass);
    const bool fixed_a = a->m_flags0 & 1, fixed_b = b->m_flags0 & 1;
    // Each joint's weight (the share the *other* one moves): a fixed joint 1 and the other 0.
    F w_a, w_b;
    if (fixed_a) w_a = kOne, w_b = kZero;
    else if (fixed_b) w_a = kZero, w_b = kOne;
    else w_a = wa, w_b = wb;

    if (mode == 1) {
        F dx = F(pb.x) - F(pa.x), dy = F(pb.y) - F(pa.y), dz = F(pb.z) - F(pa.z);
        F s = (dx * dx + dy * dy) + dz * dz;
        F len = Sqrt(s);
        F n = Sqrt(s);
        if (!(n < kEps)) {
            F inv = kOne / n;
            dx = dx * inv;
            dy = dy * inv;
            dz = dz * inv;
        }
        F force = (F(k1) * F(k2)) * (len - F(rest));
        F ka, kb;
        if (w_b == kZero && w_a == kZero) {  // (FCMP ... b.ne: a NaN weight takes the shares)
            ka = kb = force * kHalf;
        } else {
            F sum = w_b + w_a;
            ka = force * (w_b / sum);
            kb = force * (w_a / sum);
        }
        a->m_position = Vector{f(F(pa.x) + ka * dx), f(F(pa.y) + ka * dy), f(F(pa.z) + ka * dz), pa.w};
        b->m_position = Vector{f(F(pb.x) - kb * dx), f(F(pb.y) - kb * dy), f(F(pb.z) - kb * dz), pb.w};
        return;
    }
    if (mode != 0) {  // (the positions are stored back unchanged)
        a->m_position = pa;
        b->m_position = pb;
        return;
    }
    // Mode 0, the NEON form: every lane carries the same length and shares; only the direction
    // differs per lane (lane 3, w, ends as 1).
    const F d[3] = {F(pb.x) - F(pa.x), F(pb.y) - F(pa.y), F(pb.z) - F(pa.z)};
    const F s = (d[0] * d[0] + d[2] * d[2]) + (d[1] * d[1] + kZero);
    const F r = frsqrte(s);
    const F st = frsqrts(r * r, s);
    const F len = s * (r * st);
    const F diff = len - F(rest);
    const F k(a->m_stiffness);
    const F half = (diff * k) * kHalf;
    const F sum = w_b + w_a;
    const F e = frecpe(sum);
    const F c = diff * ((e * frecps(e, sum)) * k);
    F move_b = w_a * c, move_a = w_b * c;  // b moves by w_a's share, a by w_b's
    if (move_b == kZero && move_a == kZero) move_b = move_a = half;  // (FCMP / FCCMP eq per lane)
    const F rsq = r * st;
    float na[3], nb[3];
    const float* pa3 = &pa.x;
    const float* pb3 = &pb.x;
    for (int i = 0; i < 3; i++) {
        F n = d[i] * rsq;
        nb[i] = f(F(pb3[i]) - n * move_b);
        na[i] = f(F(pa3[i]) + n * move_a);
    }
    a->m_position = Vector{na[0], na[1], na[2], 1.0f};
    b->m_position = Vector{nb[0], nb[1], nb[2], 1.0f};
}

void ADMSolver::ResolveContact(ADMLink* link, ADMJoint* a, ADMJoint* b, const Vector* n, float t, float depth, float response0,
                               float response1, float speed, float dt) {
    const F dt2 = F(dt) * F(dt);
    F reach = dt2 * F(speed);
    reach = reach + reach;
    F d(depth);
    bool fast = reach < d;  // (b.mi)
    if (!fast) {
        const Vector& v = a->m_velocity;
        F v2 = (F(v.x) * F(v.x) + F(v.y) * F(v.y)) + F(v.z) * F(v.z);
        fast = dt2 * v2 > reach * reach;  // (b.le: a NaN isn't fast)
    }
    if (fast) d = (F(link->m_bounce) * F(response1) + kOne) * d;
    const F nx(n->x), ny(n->y), nz(n->z);
    F ux = nx, uy = ny, uz = nz;
    F len = Sqrt((nx * nx + ny * ny) + nz * nz);
    if (!(len < kEps)) {
        F inv = kOne / len;
        ux = inv * nx;
        uy = inv * ny;
        uz = inv * nz;
    }
    for (ADMJoint* j : {a, b}) {
        Vector& c = j->m_contactNormal;
        c.x = f(F(c.x) + ux);
        c.y = f(F(c.y) + uy);
        c.z = f(F(c.z) + uz);
    }
    F mx = d * nx;  // (the unnormalized normal)
    const F fr = F(link->m_friction) * F(response0);
    a->m_contactFriction = f(F(a->m_contactFriction) + fr);
    b->m_contactFriction = f(fr + F(b->m_contactFriction));
    F my = d * ny, mz = d * nz;
    const bool fixed_b = b->m_flags0 & 1, fixed_a = a->m_flags0 & 1;
    if (fixed_a || fixed_b) {
        ADMJoint* j;
        if (fixed_a) {
            if (fixed_b) return;
            if (F(t) < F(kNearStart)) {  // (b.pl: a NaN takes 1 / t)
                mx = mx * F(kFar), my = my * F(kFar), mz = mz * F(kFar);
            } else {
                F inv = kOne / F(t);
                mx = inv * mx, my = inv * my, mz = inv * mz;
            }
            j = b;
        } else {
            if (F(t) > F(kNearEnd)) {  // (b.le: a NaN takes 1 / (1 - t))
                mx = mx * F(kFar), my = my * F(kFar), mz = mz * F(kFar);
            } else {
                F inv = kOne / (kOne - F(t));
                mx = inv * mx, my = inv * my, mz = inv * mz;
            }
            j = a;
        }
        Vector& p = j->m_position;
        p.x = f(mx + F(p.x));
        p.y = f(my + F(p.y));
        p.z = f(mz + F(p.z));
        return;
    }
    const F wa(a->m_mass), wb(b->m_mass);
    const F sum = wa + wb;
    F r = wa / sum;
    if (!(sum > kZero)) r = kHalf;  // (fcsel gt)
    const F rt = r - F(t);
    const F ka = r * rt, kb = (r + F(-1.0f)) * rt;
    Vector& pa = a->m_position;
    Vector& pb = b->m_position;
    F ax = mx + mx * ka, bx = mx + mx * kb;
    F ay = my + my * ka, by = my + my * kb;
    F az = mz + mz * ka, bz = mz + mz * kb;
    pa.x = f(F(pa.x) + ax);
    pa.y = f(F(pa.y) + ay);
    pa.z = f(F(pa.z) + az);
    pb.x = f(bx + F(pb.x));
    pb.y = f(by + F(pb.y));
    pb.z = f(bz + F(pb.z));
}

void ADMSolver::UpdateVelocity(ADMJoint* j, ADM_CALC_DATA* calc, bool rest, float inv_dt) {
    if (rest) {
        j->m_velocity = *reinterpret_cast<const Vector*>(main_lib()->base + kRigidInverseLastRow);  // (0, 0, 0, 1)
    } else {
        const F inv(inv_dt);
        F vx = (F(j->m_position.x) - F(j->m_prevPosition.x)) * inv;
        F vy = (F(j->m_position.y) - F(j->m_prevPosition.y)) * inv;
        F vz = (F(j->m_position.z) - F(j->m_prevPosition.z)) * inv;
        const F fr(j->m_contactFriction);
        if (fr > kZero) {  // (b.le: a NaN friction does nothing)
            const F keep = kOne - (fr < kOne ? fr : kOne);  // (FMINNM of two numbers)
            Vector& c = j->m_contactNormal;
            F len = Sqrt((F(c.x) * F(c.x) + F(c.y) * F(c.y)) + F(c.z) * F(c.z));
            F nx(c.x), ny(c.y), nz(c.z);
            if (!(len < kEps)) {
                F il = kOne / len;
                nx = il * nx, ny = il * ny, nz = il * nz;
                c.x = f(nx), c.y = f(ny), c.z = f(nz);
            }
            F dot = (vx * nx + vy * ny) + vz * nz;
            F px = nx * dot, py = ny * dot, pz = nz * dot;
            vx = px + keep * (vx - px);
            vy = py + keep * (vy - py);
            vz = pz + keep * (vz - pz);
        }
        j->m_velocity = Vector{f(vx), f(vy), f(vz), 1.0f};
        if (j->m_contact) {
            const F k(j->m_contactDamping);
            j->m_velocity.x = f(k * vx);
            j->m_velocity.y = f(k * vy);
            j->m_velocity.z = f(k * vz);
        }
    }
    j->m_prevRotation = calc->m_rotation;
}

// ---- registration ----

namespace {

// "@0x..." (a library-relative address) for a local function's registration.
const char* at_symbol(u64 vaddr) {
    char* s = static_cast<char*>(std::malloc(24));
    std::snprintf(s, 24, "@0x%" PRIx64, vaddr);
    return s;
}

// The two joints (x1, x2) a link / contact function moves.
void LinkRegions(const u64 x[9], live::Regions& r) {
    if (x[1]) r.add(x[1], sizeof(ADMJoint));
    if (x[2] && x[2] != x[1]) r.add(x[2], sizeof(ADMJoint));
}

static int reg_link = family().extra(family().add_leaf(at_symbol(kFunSolveLink), &live::leaf_function<&ADMSolver::SolveLink>, 0, live::kVoid,
                                                       "Aska ADM link constraint (FUN_02429994)", {}),
                                     LinkRegions);

static int reg_contact = family().extra(
    family().add_leaf(at_symbol(kFunResolveContact), &live::leaf_function<&ADMSolver::ResolveContact>, 0, live::kVoid,
                      "Aska ADM contact response (FUN_0242a9f4)", {}),
    LinkRegions);
static int reg_velocity = family().add_leaf(at_symbol(kFunUpdateVelocity), &live::leaf_function<&ADMSolver::UpdateVelocity>, sizeof(ADMJoint),
                                            live::kVoid, "Aska ADM velocity update (FUN_0242ac84)", {});

}  // namespace

}  // namespace soa::native::dynamics
