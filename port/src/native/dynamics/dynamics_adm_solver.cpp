// The ADM solver's local helpers (no symbols; bound by address: addresses.txt): the link (distance)
// constraint (dynamics_layout.h ADMSolver; port/decomp/dynamics/adm_local.c). Written from the
// disassembly: the NEON lanes as scalars in the guest's operation order, its estimate
// instructions through dynamics_neon.h.
#include <cinttypes>
#include <cmath>
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

namespace {

// The NEON idioms of the ADM solver (each lane alike): 1 / sqrt(s) by FRSQRTE and two Newton
// steps, 1 / x by FRECPE and two, the 3-lane sum (x0 + x1) + (x2 + 0).
F rsqrt2(F s) {
    F r = frsqrte(s);
    r = r * frsqrts(r * r, s);
    return r * frsqrts(r * r, s);
}
F recip2(F x) {
    F e = frecpe(x);
    e = e * frecps(e, x);
    return e * frecps(e, x);
}
F sum3(F a, F b, F c) { return (a + b) + (c + kZero); }
F bitsf(u32 b) { return F(armf::from_bits(b)); }

// The vectorized acos's rational part: z * P(z) / Q(z) (the coefficients as the code's immediates).
struct AcosPQ {
    F p, q;
};
AcosPQ acos_pq(F z) {
    F p = z * bitsf(0x3811ef08) + bitsf(0x3a4f7f04);
    F q = z * bitsf(0x3d9dc62e) + bitsf(0xbf303361);
    p = z * p + bitsf(0xbd241146);
    q = z * q + bitsf(0x4001572d);
    p = z * p + bitsf(0x3e4e0aa8);
    q = z * q + bitsf(0xc019d139);
    p = z * p + bitsf(0xbea6b090);
    q = z * q + kOne;
    p = z * p + bitsf(0x3e2aaaab);
    return {p, q};
}
// acos(c) for |c| in [0.5, 1): 2 * asin(sqrt(z)), z = (1 -+ c) / 2, sqrt by 1 / rsqrt.
F acos_half(F z) {
    F rs = rsqrt2(z);
    AcosPQ pq = acos_pq(z);
    F sq = recip2(rs);
    F t = (z * pq.p) * recip2(pq.q);
    t = sq * t;
    t = sq + t;
    return t + t;
}

const F kPi = bitsf(0x40490fdb), kHalfPi = bitsf(0x3fc90fdb);

}  // namespace

void ADMSolver::AimRotation(Quaternion* out, ADM_CALC_DATA* calc, ADMJoint* child, ADM_CALC_DATA* child_calc, float factor) {
    const Quaternion q = calc->m_rotation;
    *out = q;
    if (child->m_flags0 & 4) return;
    const Matrix& m = calc->m_matrix;
    const F e = kEps / F(factor);
    const F near = kOne - e;
    const F px(m.m[0][3]), py(m.m[1][3]), pz(m.m[2][3]);
    const Matrix& cm = child_calc->m_matrix;
    // The unit directions to the child's animated (u) and simulated (w) positions.
    F d1x = F(cm.m[0][3]) - px, d1y = F(cm.m[1][3]) - py, d1z = F(cm.m[2][3]) - pz;
    F d2x = F(child->m_position.x) - px, d2y = F(child->m_position.y) - py, d2z = F(child->m_position.z) - pz;
    F r1 = rsqrt2(sum3(d1x * d1x, d1y * d1y, d1z * d1z));
    F r2 = rsqrt2(sum3(d2x * d2x, d2y * d2y, d2z * d2z));
    const F u0 = d1x * r1, u1 = d1y * r1, u2 = d1z * r1;
    const F w0 = d2x * r2, w1 = d2y * r2, w2 = d2z * r2;
    const F c = sum3(u0 * w0, u1 * w1, u2 * w2);
    if (!(near > c)) return;  // (FCMGT: a NaN doesn't turn)
    const F n0 = (u1 * w2 - u2 * w1) * kOne;
    const F n1 = (u0 * w2 - u2 * w0) * F(-1.0f);
    const F n2 = (u0 * w1 - u1 * w0) * kOne;
    if (sum3(n0 * n0, n1 * n1, n2 * n2) == kZero) return;
    // The axis in calc's space: through the inverse of its 3x3 part (cofactors / determinant).
    const F m00(m.m[0][0]), m01(m.m[0][1]), m02(m.m[0][2]);
    const F m10(m.m[1][0]), m11(m.m[1][1]), m12(m.m[1][2]);
    const F m20(m.m[2][0]), m21(m.m[2][1]), m22(m.m[2][2]);
    const F c01 = m00 * m11 - m01 * m10, c02 = m00 * m12 - m02 * m10, c12 = m01 * m12 - m02 * m11;
    const F inv = recip2(c12 * m20 + (c01 * m22 - c02 * m21));
    const F r0[3] = {(m11 * m22 - m12 * m21) * inv, (m02 * m21 - m01 * m22) * inv, c12 * inv};
    const F r1_[3] = {(m12 * m20 - m10 * m22) * inv, (m00 * m22 - m02 * m20) * inv, (-c02) * inv};
    const F r2_[3] = {(m10 * m21 - m11 * m20) * inv, (m01 * m20 - m00 * m21) * inv, c01 * inv};
    auto local = [&](const F* r) { return (r[0] * n0 + r[2] * n2) + (r[1] * n1 + kZero * kZero); };
    const F a0 = local(r0), a1 = local(r1_), a2 = local(r2_);
    const F ra = rsqrt2(sum3(a0 * a0, a1 * a1, a2 * a2));
    const F s0n = a0 * ra, s1n = a1 * ra, s2n = a2 * ra;
    // The angle: acos(max(c, -1)).
    const F cl = F(-1.0f) > c ? F(-1.0f) : c;
    const F ac(std::fabs(cl.v));
    F angle;
    if (ac >= kOne) {
        angle = cl > kZero ? F(0.0f) : kPi;
    } else if (kHalf > ac) {
        if (bitsf(0x34000000) >= ac) {
            angle = kHalfPi;
        } else {
            F z = cl * cl;
            AcosPQ pq = acos_pq(z);
            F t = ((z * pq.p) * recip2(pq.q) + kOne);
            angle = kHalfPi - cl * t;
        }
    } else if (cl < kZero) {
        angle = kPi - acos_half(cl * kHalf + kHalf);
    } else {
        angle = acos_half((kOne - cl) * kHalf);
    }
    // sin / cos of the half angle (polynomials), the turn's quaternion r = (axis sin, cos), q * r.
    const F h = angle * kHalf;
    const F z = h * h;
    F sp = z * bitsf(0xab393458) + bitsf(0x2f2ea763);
    F cp = z * bitsf(0xad2bf012) + bitsf(0x310db391);
    sp = z * sp + bitsf(0xb2d7109d);
    cp = z * cp + bitsf(0xb493d679);
    sp = z * sp + bitsf(0x3638edce);
    cp = z * cp + bitsf(0x37d00b12);
    sp = z * sp + bitsf(0xb9500cf2);
    cp = z * cp + bitsf(0xbab60b4e);
    sp = z * sp + bitsf(0x3c088888);
    cp = z * cp + bitsf(0x3d2aaaaa);
    sp = z * sp + bitsf(0xbe2aaaab);
    cp = z * cp + F(-0.5f);
    const F sn = h + (h * z) * sp;
    const F cs = z * cp + kOne;
    const F s0 = s0n * sn, s1 = s1n * sn, s2 = s2n * sn;
    const F qx(q.x), qy(q.y), qz(q.z), qw(q.w);
    const F nqx = kZero - qx, nqy = kZero - qy;
    out->x = f((qy * s2 - qz * s1) + (s0 * qw + cs * qx));
    out->y = f((qz * s0 - qx * s2) + (s1 * qw + cs * qy));
    out->z = f((qx * s1 - qy * s0) + (s2 * qw + cs * qz));
    out->w = f((nqy * s1 - qz * s2) + (cs * qw + nqx * s0));
}

namespace {
// BlendRotation's rate for `steps` sub-steps: r -> 1 - (1 - r)^(2^(steps-1)) when dt >= the base,
// else 1 - (1 - r)^(1/steps) (repeated square roots for even counts, a polynomial for 3, powf).
// Returns false when the 3-step polynomial is negative (the second blend skips its slerp).
struct Rate {
    F r;
    bool negative;
    bool above;  // the 3-step polynomial above 1
};
Rate step_rate(F r, u32 steps, F dt, F base) {
    if (dt >= base) {  // (b.ge)
        if ((s32)steps < 2) return {r, false, false};
        F x = kOne - r;
        for (s32 k = (s32)steps + 1; ; ) {
            k--;
            x = x * x;
            if (!(k > 2)) break;
        }
        return {kOne - x, false, false};
    }
    if (!(steps & 1)) {
        F x = kOne - r;
        if ((s32)steps < 1) return {kOne - x, false, false};
        F y;
        s32 k = 0;
        do {
            y = Sqrt(x);
            k += 2;
            x = y;
        } while (k < (s32)steps);
        return {kOne - y, false, false};
    }
    F x = kOne - r;
    if (steps == 3) {
        F sq = Sqrt(x);
        F v = ((x * (x * bitsf(0x3e74aba4)) + sq * bitsf(0x3fc93997)) + x * bitsf(0xbf59d2e1)) + bitsf(0x3d415139);
        F y = kOne - v;
        if (y < kZero) return {kZero, true, false};
        if (y <= kOne || !(y == y)) return {y, false, false};  // (b.le: a NaN stays)
        return {kOne, false, true};
    }
    F p(::powf(x.v, (kOne / F((float)(s32)steps)).v));
    return {kOne - p, false, false};
}
void slerp(Quaternion* q, const Quaternion* to, F t) {
    alignas(16) Quaternion r;
    r.Slerp(q, to, f(t));
    *q = r;
}
}  // namespace

void ADMSolver::BlendRotation(ADMJoint* j, ADM_CALC_DATA* calc, ADMJoint* child, ADM_CALC_DATA* child_calc, u32 steps, float blend, float dt) {
    const F base = bitsf(0x3c83126f);  // 0.016: the reference step (.rodata 0x28e2c84)
    const F tdt(dt);
    F factor = (base / tdt) * kHalf;
    factor = !(factor == factor) ? kOne : (factor > kOne ? factor : kOne);  // (FMAXNM(x, 1): the number wins over a NaN)
    alignas(16) Quaternion q;
    if (checking()) guest_invoke<void>(main_lib()->base + kFunAimRotation, &q, calc, child, child_calc, f(factor));
    else AimRotation(&q, calc, child, child_calc, f(factor));
    if (j->m_flags1 & 4) {
        F r(armf::min(j->m_param170, 1.0f));  // (FMIN: a NaN propagates)
        if (steps != 1) {
            Rate rt = step_rate(r, steps, tdt, base);
            r = rt.r;
        }
        slerp(&q, &j->m_rotation70, r);
    }
    F b(blend);
    if (b > kEps) {  // (b.le: a NaN doesn't blend)
        F t = F(j->m_blendWeight) * b;
        bool go;
        if (steps == 1) {
            go = t > kEps;
        } else {
            Rate rt = step_rate(t, steps, tdt, base);
            if (rt.negative) go = false;
            else if (rt.above) t = kOne, go = true;  // (straight to the slerp with min(1, 1))
            else t = rt.r, go = t > kEps;
        }
        if (go) slerp(&q, &j->m_rotation80, F(armf::min(t.v, 1.0f)));
    }
    calc->m_rotation = q;
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

static int reg_aim = family().extra(family().add_leaf(at_symbol(kFunAimRotation), &live::leaf_function<&ADMSolver::AimRotation>, 0, live::kVoid,
                                                      "Aska ADM aim rotation (FUN_0242a08c)", {live::out(0, 16)}),
                                    nullptr);
static int reg_blend = family().add_leaf(at_symbol(kFunBlendRotation), &live::leaf_function<&ADMSolver::BlendRotation>, 0, live::kVoid,
                                         "Aska ADM rotation blend (FUN_02429d78)", {live::out(1, sizeof(ADM_CALC_DATA))});
static int reg_velocity = family().add_leaf(at_symbol(kFunUpdateVelocity), &live::leaf_function<&ADMSolver::UpdateVelocity>, sizeof(ADMJoint),
                                            live::kVoid, "Aska ADM velocity update (FUN_0242ac84)", {});

}  // namespace

}  // namespace soa::native::dynamics
