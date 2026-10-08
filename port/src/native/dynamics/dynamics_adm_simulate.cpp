// The ADM solver loop: ArticulatedDynamicsManager::Simulate and the templates it runs per step
// (SimulateMain, PreprocessBeforeInternalForce, InterpolateRoot, CollisionSetting) for the
// ArticulatedDynamicsManager instantiation (dynamics_layout.h; port/decomp/dynamics/adm.c,
// adm_templates.c). Written from the disassembly. The parts still guest code (CollisionAndConstraint,
// StandardIK, Finalize, MatrixPreFixAndMotionBlend, the force-emitter functor, ...) are guest calls.
#include <cstring>
#include <vector>

#include "core/cpu.h"
#include "native/dynamics/dynamics_family.h"
#include "native/dynamics/dynamics_neon.h"
#include "native/dynamics/gen/dynamics_addresses.h"

namespace soa::native::dynamics {

namespace {

const F kZero(0.0f), kOne(1.0f), kHalf(0.5f), kEps(math::kEpsilon);
using neon::recip2;

template <typename T>
T& guest_var(u64 vaddr) {
    return *reinterpret_cast<T*>(main_lib()->base + vaddr);
}

// Guest functions (by symbol) and the natives called through their entry while checking.
u64 g(const char* sym) { return fn_addr(sym); }
#define GUEST_FN(name, sym)                \
    u64 name() {                           \
        static const u64 a = g(sym);       \
        return a;                          \
    }
GUEST_FN(fn_invert_low_error, "_ZNK4Aska6Matrix14InvertLowErrorEPS0_")
GUEST_FN(fn_apply_matrix_inplace, "_ZN4Aska6Vector11ApplyMatrixEPKNS_6MatrixE")
GUEST_FN(fn_matrix_calc, "_ZN4Aska14MatrixCalcFuncEPNS_6MatrixEPKNS_6VectorEPKNS_10QuaternionES7_S4_S4_PKS0_")
GUEST_FN(fn_prefix_blend, "_ZN4Aska26ArticulatedDynamicsManager26MatrixPreFixAndMotionBlendILb1EEEvPNS_13ADM_CALC_DATAEPNS_8ADMJointEjfffPNS_6VectorEb")
GUEST_FN(fn_emitter_manager, "_ZN4Aska15DynamicsManager22GetForceEmitterManagerEv")
GUEST_FN(fn_functor, "_Z39Functor_ExternalForceEmitterCalculationIN4Aska26ArticulatedDynamicsManagerENS0_20DynamicsForceEmitterEEvPT_PNS0_8ADMJointEPPT0_jfj")
GUEST_FN(fn_update_dependent, "_ZN4Aska30ArticulatedDynamicsManagerBase46UpdateDynamicsPrimitiveListWithDependencyOfADMEj")
GUEST_FN(fn_ik_false, "_ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_26ArticulatedDynamicsManagerELb0EEEvPT_ffi")
GUEST_FN(fn_ik_true, "_ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_26ArticulatedDynamicsManagerELb1EEEvPT_ffi")
GUEST_FN(fn_finalize, "_ZN4Aska30ArticulatedDynamicsManagerBase8FinalizeINS_26ArticulatedDynamicsManagerEEEvPT_ffi")
GUEST_FN(fn_collision_and_constraint,
         "_ZN4Aska30ArticulatedDynamicsManagerBase22CollisionAndConstraintINS_26ArticulatedDynamicsManagerEEEvPT_PNS_8ADMJointES6_jjf")
GUEST_FN(fn_external_force, "_ZN4Aska8ADMJoint13ExternalForceEfffPKNS_6VectorEPNS_13ADM_CALC_DATAEb")
GUEST_FN(fn_interpolate_root,
         "_ZN4Aska30ArticulatedDynamicsManagerBase15InterpolateRootINS_26ArticulatedDynamicsManagerEEEvPT_PNS_8ADMJointES6_fjj")
GUEST_FN(fn_collision_setting, "_ZN4Aska30ArticulatedDynamicsManagerBase16CollisionSettingINS_26ArticulatedDynamicsManagerEEEvPT_jj")
GUEST_FN(fn_preprocess,
         "_ZN4Aska26ArticulatedDynamicsManager29PreprocessBeforeInternalForceIS0_EEvPT_PNS_8ADMJointES5_ffjjb")
GUEST_FN(fn_simulate_main, "_ZN4Aska26ArticulatedDynamicsManager12SimulateMainIS0_EEvPT_PNS_8ADMJointES5_jiijffjf")

// m_calc.m_matrix from the joint's local transform and its parent's (MatrixCalcFunc).
void MatrixCalc(ADM_CALC_DATA* c) {
    ADM_CALC_DATA* p = c->m_parent;
    guest_call(fn_matrix_calc(), {(u64)&c->m_matrix, (u64)&c->m_position, (u64)&c->m_rotation, (u64)&c->m_orientation, (u64)&c->m_scale,
                                  p ? (u64)&p->m_scale : 0, (u64)p});
}
// The m_count - 1 first joints of a chain from `j` (sic: the guest's loop stops one short).
void MatrixCalcChain(ADMJoint* j, u32 count) {
    for (u32 k = 1 - count; k != 0; k++, j++) MatrixCalc(&j->m_calc);
}

// The force emitters' manager (DynamicsManager::GetForceEmitterManager): its active list.
struct ForceEmitterManager {
    u8 unk_00[0x50];
    void** m_active;  // 0x50
    u32 m_count;      // 0x58
};

// Calls to the natives of this file and the solver's: C++ normally, the guest entry while checking.
void solve_link(const ADMLink& l, float dt) {
    if (checking()) guest_invoke<void>(main_lib()->base + kFunSolveLink, l.m_mode, l.m_joint0, l.m_joint1, l.m_length, l.m_stiffness, dt);
    else ADMSolver::SolveLink(l.m_mode, l.m_joint0, l.m_joint1, l.m_length, l.m_stiffness, dt);
}

}  // namespace

void ArticulatedDynamicsManagerBase::CollisionSetting(ArticulatedDynamicsManagerBase* adm, u32 steps, u32 step) {
    const float t = f(F((float)(step + 1)) / F((float)steps));  // (UCVTF)
    const u32 last = steps - step == 1;
    auto update = [&](DynamicsPrimitive* p) {
        if (!p) return;
        u64 fn = static_cast<const u64*>(p->vtable)[14];  // Update(float, bool)
        guest_invoke<void>(fn, p, last, t);
    };
    if (DynamicsPrimitive** l = adm->m_collisions)
        for (u32 n = (u32)(s64)adm->m_collisionCount; n; n--) update(*l++);
    {
        DynamicsPrimitive** l = &guest_var<DynamicsPrimitive*>(kVaddrWorldCollisionList);
        for (u32 n = guest_var<u8>(kVaddrWorldCollisionCount); n; n--) update(*l++);
    }
    for (ADMExtraNode* node = adm->m_extraCollisions.m_next; node != &adm->m_extraCollisions; node = node->m_next) update(node->m_primitive);
    if (DynamicsPrimitive** l = adm->m_constraints)
        for (u32 n = (u32)(s64)adm->m_constraintCount; n; n--) update(*l++);
    DynamicsPrimitive** l = &guest_var<DynamicsPrimitive*>(kVaddrWorldConstraintList);
    for (u32 n = guest_var<u8>(kVaddrWorldConstraintCount); n; n--) update(*l++);
}

void ArticulatedDynamicsManagerBase::InterpolateRoot(ArticulatedDynamicsManagerBase* adm, ADMJoint* first, ADMJoint*, float, u32 steps, u32 step) {
    if (steps < 2) return;
    const s32 roots = adm->m_rootCount;
    if (roots < 1) return;
    if (steps - step == 1) {  // the last step: the roots where the animation puts them
        for (s32 i = 0; i < roots; i++) {
            const ADMRoot& r = adm->m_roots[i];
            ADMJoint* j = first + r.m_first;
            if (!(j->m_flags0 & 1)) continue;
            j->m_calc.m_position = j->m_rootLocal;
            if (r.m_count != 1) MatrixCalcChain(j, r.m_count);
        }
        return;
    }
    const F inv = kOne / F((float)(s32)(steps - step));
    const F rest = kOne - inv;
    for (s32 i = 0; i < roots; i++) {
        const ADMRoot& r = adm->m_roots[i];
        ADMJoint* j = first + r.m_first;
        if (!(j->m_flags0 & 1)) continue;
        u32 count = r.m_count;
        auto* c = reinterpret_cast<ADM_CALC_DATA*>((u64)adm->m_rootCalc + (u64)i * sizeof(ADM_CALC_DATA));
        float tx, ty, tz;
        if (step == 0) {
            const Matrix& m = j->m_calc.m_matrix;
            tx = m.m[0][3], ty = m.m[1][3], tz = m.m[2][3];
            j->m_rootLocal = j->m_calc.m_position;
            j->m_rootTarget = Vector{tx, ty, tz, 1.0f};
        } else {
            tx = j->m_rootTarget.x, ty = j->m_rootTarget.y, tz = j->m_rootTarget.z;
        }
        alignas(16) Vector v;
        v.x = f(inv * F(tx) + rest * F(j->m_position.x));
        v.y = f(inv * F(ty) + rest * F(j->m_position.y));
        v.z = f(inv * F(tz) + rest * F(j->m_position.z));
        v.w = j->m_position.w;
        if (c) {
            alignas(16) Matrix m;
            guest_call(fn_invert_low_error(), {(u64)c, (u64)&m});
            guest_call(fn_apply_matrix_inplace(), {(u64)&v, (u64)&m});
            j->m_calc.m_position = v;
        }
        if (count != 1) MatrixCalcChain(j, count);
    }
}

void ArticulatedDynamicsManagerBase::PreprocessBeforeInternalForce(ArticulatedDynamicsManagerBase* adm, ADMJoint* first, ADMJoint* end, float dt,
                                                                   float inv_dt, u32 steps, u32 step, bool simulating) {
    if (checking()) {
        guest_invoke<void>(fn_interpolate_root(), adm, first, end, steps, step, dt);
        guest_invoke<void>(fn_collision_setting(), adm, steps, step);
    } else {
        InterpolateRoot(adm, first, end, dt, steps, step);
        CollisionSetting(adm, steps, step);
    }
    const F blend(adm->m_blendRate);
    const float g = adm->m_gravityScale;
    const s32 roots = adm->m_rootCount;
    const ADMRoot* r = adm->m_roots;
    if (blend > kZero) {  // (b.le: a NaN rate resets)
        for (s32 i = 0; i < roots; i++) {
            auto* c = reinterpret_cast<ADM_CALC_DATA*>((u64)adm->m_rootCalc + (u64)i * sizeof(ADM_CALC_DATA));
            guest_invoke<void>(fn_prefix_blend(), c, first + r[i].m_first, r[i].m_count, &adm->m_gravityWorld, (u32)simulating, dt, inv_dt, g);
        }
    } else {
        const Vector rest = *reinterpret_cast<const Vector*>(main_lib()->base + kRigidInverseLastRow);  // (0, 0, 0, 1)
        for (s32 i = 0; i < roots; i++) {
            ADMJoint* j = first + r[i].m_first;
            for (u32 n = r[i].m_count; n; n--, j++) {
                j->m_contactNormal = rest;
                j->m_prevPosition = Vector{j->m_position.x, j->m_position.y, j->m_position.z, 1.0f};
                j->m_contactFriction = 0.0f;
                j->m_contact = 0;
                j->m_contactDamping = 0.8f;  // (0x3f4ccccd)
                j->m_calc.m_rotation = j->m_prevRotation;
                MatrixCalc(&j->m_calc);
                if (checking())
                    guest_invoke<void>(fn_external_force(), j, &adm->m_gravityWorld, &j->m_calc, (u32)simulating, dt, inv_dt, g);
                else
                    j->ExternalForce(dt, inv_dt, g, &adm->m_gravityWorld, &j->m_calc, simulating);
            }
        }
    }
    auto* m = reinterpret_cast<ForceEmitterManager*>(guest_call(fn_emitter_manager(), {}));
    if (m->m_count && adm->m_emitters) {
        u32 seed = adm->m_emitterSeed;
        guest_invoke<void>(fn_functor(), adm, first, m->m_active, m->m_count, seed, dt);
        adm->m_emitterSeed = seed + 0x56b46fd1u;
    }
}

void ArticulatedDynamicsManagerBase::SimulateMain(ArticulatedDynamicsManagerBase* adm, ADMJoint* first, ADMJoint* end, u32 iterations, s32 step0,
                                                  s32 steps, u32 ik_steps, u32 repeat, float dt, float inv_dt, float rest_speed) {
    const s64 links = adm->m_linkCount;
    s32 passes;
    bool ik;
    if (adm->m_solverMode == 2) {
        passes = adm->m_jointCount;
        ik = true;
    } else {
        passes = 1;
        ik = adm->m_ik & 1;
    }
    const bool simulating = adm->m_simulating != 0;
    s32 collisions = adm->m_collisionCount;
    if (adm->m_worldCollision) collisions += guest_var<u8>(kVaddrWorldCollisionCount);
    const u32 collision_count = adm->m_extraCollisionCount + (u32)collisions;
    u32 constraints = (adm->m_worldCollision ? guest_var<u8>(kVaddrWorldConstraintCount) : 0) + (u32)(s32)adm->m_constraintCount;
    if (adm->m_landConstraint) constraints++;
    const F rest(rest_speed);
    // (FCMP le / lt: a NaN threshold also skips the rest test)
    const bool no_rest_test = !(rest > kEps) || !(rest >= kZero);
    for (u32 pass = 0;;) {
        for (s32 i = step0; i < steps; i++) {
            if (adm->m_dependentPrimitives) guest_invoke<void>(fn_update_dependent(), adm, (u32)i);
            if (checking()) guest_invoke<void>(fn_preprocess(), adm, first, end, (u32)steps, (u32)i, (u32)simulating, dt, inv_dt);
            else PreprocessBeforeInternalForce(adm, first, end, dt, inv_dt, (u32)steps, (u32)i, simulating);
            for (s32 k = 0; k != passes; k++) {
                if (links) {
                    ADMLink* l = adm->m_linkList;
                    auto fixed_pair = [](const ADMLink& x) { return (x.m_joint0->m_flags0 & 1) && (x.m_joint1->m_flags0 & 1); };
                    if (adm->m_solverMode == 1) {
                        u32 it = 0;
                        do {
                            for (s64 n = 0; n < links; n++)
                                if (!fixed_pair(l[n])) solve_link(l[n], dt);
                            for (ADMLink* x = l + (links - 1); x >= l; x--)
                                if (!fixed_pair(*x)) solve_link(*x, dt);
                        } while (++it < iterations);
                    } else {
                        for (s64 n = 0; n < links; n++)
                            if (!fixed_pair(l[n])) solve_link(l[n], dt);
                    }
                }
                if (!ik) guest_invoke<void>(fn_ik_false(), adm, ik_steps, dt, inv_dt);
                if (checking()) guest_invoke<void>(fn_collision_and_constraint(), adm, first, end, collision_count, constraints, dt);
                else CollisionAndConstraint(adm, first, end, collision_count, constraints, dt);
            }
            if (ik) {
                if (checking()) guest_invoke<void>(fn_ik_true(), adm, ik_steps, dt, inv_dt);
                else StandardIK(adm, ik_steps, dt, inv_dt);
            }
            else guest_invoke<void>(fn_finalize(), adm, ik_steps, dt, inv_dt);
        }
        if (!no_rest_test) {
            s64 n = adm->m_jointCount;
            bool moving = false;
            if (n >= 1) {
                for (ADMJoint *j = adm->m_joints, *e = adm->m_joints + n; j < e; j++) {
                    const Vector& v = j->m_velocity;
                    if (F(std::fabs(v.x)) > rest || F(std::fabs(v.y)) > rest || F(std::fabs(v.z)) > rest) {  // (b.gt)
                        moving = true;
                        break;
                    }
                }
            }
            if (!moving) {
                adm->m_moving = 0;
                return;
            }
        }
        if (++pass >= repeat) return;
    }
}

namespace {

// A primitive's virtual by vtable slot (TestIntersection(DYNAMICS_CAPSULE*, ...) 16,
// TestIntersectionLocal 17, TestIntersection(Vector const*, float, Vector*) 19).
inline u64 slot(const void* obj, int n) { return (*static_cast<const u64* const*>(obj))[n]; }

// The 3x3 part of a matrix applied to v: (m_i0 v0 + m_i2 v2) + (m_i1 v1 + 0) per row, w = 1 (the
// NEON form the collision code uses).
Vector Rotate3(const Matrix& m, const Vector& v) {
    const F v0(v.x), v1(v.y), v2(v.z);
    auto row = [&](int i) { return (F(m.m[i][0]) * v0 + F(m.m[i][2]) * v2) + (F(m.m[i][1]) * v1 + kZero * kZero); };
    return Vector{f(row(0)), f(row(1)), f(row(2)), f(kHalf + kHalf)};
}
// A 4-lane row dot product as the code sums it: (r2 v2 + r0 v0) + (r3 v3 + r1 v1).
F Dot4(const float* r, const Vector& v) {
    return (F(r[2]) * F(v.z) + F(r[0]) * F(v.x)) + (F(r[3]) * F(v.w) + F(r[1]) * F(v.y));
}

void resolve(ADMLink* l, ADMJoint* a, ADMJoint* b, Vector* n, float t, float depth, const DYNAMICS_PRIMITIVE* d, float speed, float dt) {
    if (checking())
        guest_invoke<void>(main_lib()->base + kFunResolveContact, l, a, b, n, t, depth, d->m_response0, d->m_response1, speed, dt);
    else
        ADMSolver::ResolveContact(l, a, b, n, t, depth, d->m_response0, d->m_response1, speed, dt);
}
void mark(u8* flags, const ADMJoint* j) {
    if (j->m_index19e != 0xff) flags[j->m_index19e] = 1;
}
}  // namespace

void ArticulatedDynamicsManagerBase::CollisionAndConstraint(ArticulatedDynamicsManagerBase* adm, ADMJoint* first, ADMJoint* end, u32 collisions,
                                                            u32 constraints, float dt) {
    void* land = adm->m_landConstraint;
    bool no_land = false;
    if (!land) {
        land = guest_var<void*>(kVaddrWorldLandConstraint);
        no_land = land == nullptr;
        if ((u32)(0u - constraints) == collisions && !land) return;
    }
    // The primitives to test: the ADM's collisions, then the world's, then the extra list.
    std::vector<DynamicsPrimitive*> list;
    if ((s32)collisions >= 1) {
        const s64 own = adm->m_collisionCount;
        DynamicsPrimitive** world = &guest_var<DynamicsPrimitive*>(kVaddrWorldCollisionList);
        for (s64 i = 0; i < (s64)collisions; i++) list.push_back(i < own ? adm->m_collisions[i] : world[i - own]);
    }
    for (ADMExtraNode* node = adm->m_extraCollisions.m_next; node != &adm->m_extraCollisions; node = node->m_next) list.push_back(node->m_primitive);
    const u32 count = (u32)list.size();
    u8* const hit_flags = adm->m_hitFlags;
    DynamicsPrimitive** const own_constraints = adm->m_constraints;
    const float speed = adm->m_gravityScale;
    const u16 constraint_count = (u16)adm->m_constraintCount;
    const u32 world_constraints = adm->m_worldCollision ? guest_var<u8>(kVaddrWorldConstraintCount) : 0;
    u32 joints = (u32)(((u64)((u8*)end - (u8*)first) >> 6) * 0xb6db6db7u);  // (end - first) / 0x1c0
    ADMJoint* j = first;
    do {
        u32 links = count ? j->m_linkCount : 0;
        if (links * count != 0) {
            // The joint's frame: its matrix and the inverse (cofactors, FRECPE with two steps).
            const Matrix& m = j->m_calc.m_matrix;
            const F m00(m.m[0][0]), m01(m.m[0][1]), m02(m.m[0][2]), m03(m.m[0][3]);
            const F m10(m.m[1][0]), m11(m.m[1][1]), m12(m.m[1][2]), m13(m.m[1][3]);
            const F m20(m.m[2][0]), m21(m.m[2][1]), m22(m.m[2][2]), m23(m.m[2][3]);
            const F c01 = m00 * m11 - m01 * m10, c02 = m00 * m12 - m02 * m10, c03 = m00 * m13 - m03 * m10;
            const F c12 = m01 * m12 - m02 * m11, c13 = m01 * m13 - m03 * m11, c23 = m02 * m13 - m03 * m12;
            const F det = c12 * m20 + (c01 * m22 - c02 * m21);
            const F inv = recip2(det);
            const F A = m11 * m22 - m12 * m21, B = m02 * m21 - m01 * m22, C = m12 * m20 - m10 * m22;
            const F D = m00 * m22 - m02 * m20, E = m10 * m21 - m11 * m20, Fv = m01 * m20 - m00 * m21;
            const F G = c13 * m22 - c23 * m21, H = c23 * m20 - c03 * m22;
            alignas(16) float R[3][4] = {
                {f(inv * A), f(inv * B), f(inv * c12), f(inv * (G - c12 * m23))},
                {f(inv * C), f(inv * D), f(inv * (-c02)), f(inv * (c02 * m23 + H))},
                {f(inv * E), f(inv * Fv), f(inv * c01), f(inv * ((c03 * m21 - c13 * m20) - c01 * m23))},
            };
            ADMLink* l = j->m_links;
            for (; links; links--, l++) {
                const u8 flags = l->m_flags;
                ADMJoint* o = l->m_joint1;
                if (flags & 1) {
                    alignas(16) DYNAMICS_CAPSULE cap;
                    cap.m_radius = l->m_capsuleRadius;
                    const bool local = flags & 8;
                    for (u32 k = 0; k < count; k++) {
                        DynamicsPrimitive* p = list[k];
                        if (p->m_data->m_owner == adm && ((j->m_flags0 & 1) || (o->m_flags0 & 1))) continue;
                        alignas(16) Vector n;
                        float t, depth;
                        bool hit;
                        if (!local) {
                            Vector a = j->m_position, b = o->m_position;
                            if (flags & 4) {
                                Vector w = Rotate3(m, l->m_offset);
                                a = Vector{f(F(a.x) + F(w.x)), f(F(a.y) + F(w.y)), f(F(a.z) + F(w.z)), f(F(a.w) + F(w.w))};
                                b = Vector{f(F(b.x) + F(w.x)), f(F(b.y) + F(w.y)), f(F(b.z) + F(w.z)), f(F(b.w) + F(w.w))};
                            }
                            const F dx = F(b.x) - F(a.x), dy = F(b.y) - F(a.y), dz = F(b.z) - F(a.z);
                            F s0(0.0f), k1(0.0f);
                            if (flags & 2) {  // the swept part [m_sweepStart, m_sweepEnd] of the segment
                                s0 = F(l->m_sweepStart);
                                k1 = (F(l->m_sweepEnd) - s0) + kOne;
                                cap.m_otherSegment.m_origin = Vector{f(F(a.x) + dx * s0), f(F(a.y) + dy * s0), f(F(a.z) + dz * s0), 1.0f};
                                cap.m_otherSegment.m_direction = Vector{f(dx * k1), f(dy * k1), f(dz * k1), 1.0f};
                            } else {
                                cap.m_otherSegment.m_origin = Vector{a.x, a.y, a.z, 1.0f};
                                cap.m_otherSegment.m_direction = Vector{f(dx), f(dy), f(dz), 1.0f};
                            }
                            hit = guest_invoke<bool>(slot(p, 16), p, &cap, (u32)((flags >> 4) & 1), &n, &t, &depth);
                            if (hit && (flags & 2)) t = f(s0 + (kOne - k1) * F(t));
                        } else {
                            // In the joint's frame: the other joint through the inverse, the link from
                            // the offset (or the origin) to it.
                            alignas(16) float M[3][4];  // (the rows as the callee reads them: R0, R1, R2)
                            std::memcpy(M, R, sizeof M);
                            const Vector& op = o->m_position;
                            Vector q{f(Dot4(R[0], op)), f(Dot4(R[1], op)), f(Dot4(R[2], op)), f(kHalf + kHalf)};
                            Vector org = *reinterpret_cast<const Vector*>(main_lib()->base + kRigidInverseLastRow);
                            if (flags & 4) {
                                org = l->m_offset;
                                q = Vector{f(F(q.x) + F(org.x)), f(F(q.y) + F(org.y)), f(F(q.z) + F(org.z)), f(F(q.w) + F(org.w))};
                            }
                            if (flags & 2) {
                                const F s0(l->m_sweepStart);
                                const F k1 = (F(l->m_sweepEnd) - s0) + kOne;
                                cap.m_otherSegment.m_origin = Vector{f(F(org.x) + F(q.x) * s0), f(F(org.y) + F(q.y) * s0), f(F(org.z) + F(q.z) * s0), 1.0f};
                                cap.m_otherSegment.m_direction = Vector{f(F(q.x) * k1), f(F(q.y) * k1), f(F(q.z) * k1), 1.0f};
                            } else {
                                cap.m_otherSegment.m_origin = Vector{org.x, org.y, org.z, 1.0f};
                                cap.m_otherSegment.m_direction = Vector{q.x, q.y, q.z, 1.0f};
                            }
                            hit = guest_invoke<bool>(slot(p, 17), p, &M[0], &M[1], &M[2], &cap, (u32)((flags >> 4) & 1), &l->m_localPoint, &n, &t, &depth);
                            if (hit) n = Rotate3(m, n);
                        }
                        if (!hit) continue;
                        resolve(l, j, o, &n, t, depth, p->m_data, speed, dt);
                        mark(hit_flags, j);
                        mark(hit_flags, o);
                        if (p->m_data->m_owner == adm) {
                            j->m_contact |= 1;
                            o->m_contact |= 1;
                        }
                    }
                }
                if (j->m_contact || o->m_contact) {
                    if (o->m_parentJoint == l->m_joint0) o->m_contact |= 2;
                    if (j->m_parentJoint == l->m_joint1) j->m_contact |= 2;
                    if (checking())
                        guest_invoke<void>(main_lib()->base + kFunSolveLink, l->m_mode, j, o, l->m_length, l->m_stiffness, dt);
                    else
                        ADMSolver::SolveLink(l->m_mode, j, o, l->m_length, l->m_stiffness, dt);
                }
            }
        }
        if (!(j->m_flags0 & 1)) {
            // The constraints: the ADM's (by the joint's index list), the world's, the land.
            if (constraint_count && (j->m_flags1 & 8)) {
                for (u32 k = 0; k < j->m_constraintCount; k++) {
                    DynamicsPrimitive* p = own_constraints[j->m_constraints[k]];
                    if (!p) continue;
                    alignas(16) Vector out;
                    if (!guest_invoke<bool>(slot(p, 19), p, &j->m_position, &out, j->m_collisionRadius)) continue;
                    j->m_position = out;
                    j->m_contactFriction = f(F(j->m_contactFriction) + F(p->m_data->m_response0));
                    mark(hit_flags, j);
                    if (p->m_data->m_owner == adm) j->m_contact |= 1;
                }
            }
            DynamicsPrimitive** world = &guest_var<DynamicsPrimitive*>(kVaddrWorldConstraintList);
            for (u32 k = 0; k < world_constraints; k++) {
                DynamicsPrimitive* p = world[k];
                alignas(16) Vector out;
                if (!guest_invoke<bool>(slot(p, 19), p, &j->m_position, &out, j->m_collisionRadius)) continue;
                j->m_position = out;
                j->m_contactFriction = f(F(j->m_contactFriction) + F(p->m_data->m_response0));
                mark(hit_flags, j);
            }
            if (!no_land && (j->m_flags1 & 0x10)) {
                alignas(16) Vector v{j->m_position.x, f(F(j->m_position.y) - F(j->m_collisionRadius)), j->m_position.z, 1.0f};
                alignas(16) float height[4], friction[4];
                if (guest_invoke<bool>(slot(land, 3), land, &v, height, friction, 0ull)) {
                    j->m_position.y = f(F(height[0]) + F(j->m_collisionRadius));
                    j->m_contactFriction = f(F(j->m_contactFriction) + F(friction[0]));
                    mark(hit_flags, j);
                }
            }
        }
        j++;
    } while (--joints != 0);
}

namespace {
GUEST_FN(fn_apply_vector, "_ZNK4Aska6Matrix11ApplyVectorEPNS_6VectorEPKS1_")
// MatrixCalcFunc with an explicit parent.
void MatrixCalcWith(ADM_CALC_DATA* c, ADM_CALC_DATA* parent) {
    guest_call(fn_matrix_calc(), {(u64)&c->m_matrix, (u64)&c->m_position, (u64)&c->m_rotation, (u64)&c->m_orientation, (u64)&c->m_scale,
                                  parent ? (u64)&parent->m_scale : 0, (u64)parent});
}
// The joint's position in `space`'s frame: inverse(space) * position.
void LocalPosition(const ADM_CALC_DATA* space, const Vector* pos, Vector* out) {
    alignas(16) Matrix m;
    alignas(16) Vector v;
    guest_call(fn_invert_low_error(), {(u64)space, (u64)&m});
    guest_call(fn_apply_vector(), {(u64)&m, (u64)&v, (u64)pos});
    *out = v;
}
// A free joint's position from its calc data, then its velocity (UpdateVelocity).
void FinishJoint(ADMJoint* j, ADM_CALC_DATA* c, bool blend, float inv_dt) {
    if (!(j->m_flags0 & 1)) j->m_position = Vector{c->m_matrix.m[0][3], c->m_matrix.m[1][3], c->m_matrix.m[2][3], 1.0f};
    if (checking()) guest_invoke<void>(main_lib()->base + kFunUpdateVelocity, j, c, (u32)blend, inv_dt);
    else ADMSolver::UpdateVelocity(j, c, blend, inv_dt);
}
}  // namespace

void ArticulatedDynamicsManagerBase::StandardIK(ArticulatedDynamicsManagerBase* adm, u32 steps, float dt, float inv_dt) {
    const s32 roots = adm->m_rootCount;
    if (roots < 1) return;
    const float blend_rate = adm->m_blendRate;
    const F damp_scale(0.9f), damp_min(0.6f);  // (.rodata 0x2707bf4, 0x276c774)
    for (s32 i = 0; i < roots; i++) {
        const ADMRoot& r = adm->m_roots[i];
        ADMJoint* joints = adm->m_joints;
        const s64 first = (s32)r.m_first;
        u32 count = r.m_count;
        ADMJoint* root = joints + first;
        const bool blend = adm->m_motionBlend != 0;
        auto* rc = reinterpret_cast<ADM_CALC_DATA*>((u64)adm->m_rootCalc + (u64)i * sizeof(ADM_CALC_DATA));
        if (root->m_flags1 & 0x20) root->m_calc.m_rotation = root->m_rotation70;
        if (!root->m_lengthDirty && !(root->m_flags0 & 1)) {
            if (rc) LocalPosition(rc, &root->m_position, &root->m_calc.m_position);
            else root->m_calc.m_position = root->m_position;
        }
        MatrixCalcWith(&root->m_calc, rc);
        if (count == 1) {
            FinishJoint(root, &root->m_calc, blend, inv_dt);
            continue;
        }
        ADMJoint* prev = root;
        for (u32 k = 1 - count; k != 0; k++) {
            ADMJoint* c = prev + 1;
            ADMJoint* p = c->m_parentJoint;
            ADM_CALC_DATA* pc = &p->m_calc;
            if (c->m_contact & 2) {  // (touched last step)
                F d = F(c->m_contactDamping) * damp_scale;
                c->m_contactDamping = !(d == d) ? damp_min.v : (d > damp_min ? d.v : damp_min.v);  // (FMAXNM)
            }
            ADMJoint* turned = nullptr;
            if (!((c->m_flags0 & 1) | c->m_lengthDirty)) {
                LocalPosition(pc, &c->m_position, &c->m_calc.m_position);
            } else if (c->m_flags0 & 2) {
                MatrixCalc(pc);
                MatrixCalcWith(&c->m_calc, pc);
                if (checking())
                    guest_invoke<void>(main_lib()->base + kFunBlendRotation, p, pc, c, &c->m_calc, steps, blend_rate, dt);
                else
                    ADMSolver::BlendRotation(p, pc, c, &c->m_calc, steps, blend_rate, dt);
                MatrixCalc(pc);
                FinishJoint(p, pc, blend, inv_dt);
                turned = p;
            }
            if (c->m_flags1 & 0x20) c->m_calc.m_rotation = c->m_rotation70;
            MatrixCalcWith(&c->m_calc, pc);
            if (turned != prev) FinishJoint(prev, &prev->m_calc, blend, inv_dt);
            prev = c;
        }
        FinishJoint(prev, &prev->m_calc, blend, inv_dt);
    }
}

bool ArticulatedDynamicsManagerBase::Simulate(float dt, u32 repeat, float rest_speed) {
    if (!m_resetPending) return false;
    const F base(guest_var<float>(kVaddrBaseDt));
    s32 steps = m_steps;
    if (m_minTwoSteps) steps = steps > 2 ? steps : 2;
    if (guest_var<u8>(kVaddrDtDiv) && m_dtDiv && !m_motionBlend) {
        s32 k = steps * armf::cvtzs(f(F(dt) / base));
        steps = k > 1 ? k : 1;
    }
    const F step_dt = steps > 1 ? base : F(dt);
    const F inv = kOne / step_dt;
    s32 ik_steps;
    if (m_motionBlend) {
        ik_steps = 1;
    } else {
        F q = base <= step_dt ? step_dt / base : base / step_dt + kHalf;  // (b.ls: a NaN takes the second)
        s32 k = armf::cvtzs(f(q));
        ik_steps = k > 1 ? k : 1;
    }
    ADMJoint* first = m_joints;
    s64 n = m_jointCount;
    if (checking())
        guest_invoke<void>(fn_simulate_main(), this, first, first + n, (u32)n, 0u, (u32)steps, (u32)ik_steps, repeat, f(step_dt), f(inv), rest_speed);
    else
        SimulateMain(this, first, first + n, (u32)n, 0, steps, (u32)ik_steps, repeat, f(step_dt), f(inv), rest_speed);
    return true;
}

// ---- registration ----

namespace {

using live::kInt;
using live::kVoid;
constexpr u32 kAdmBytes = 0x1c0;

void ExtraJoint(const ADMJoint* j, live::Regions& r) {
    if (j->m_calc.m_parent && j->m_isRoot) r.add((u64)j->m_calc.m_parent, sizeof(ADM_CALC_DATA));
    s32 count = (s32)j->m_linkCount;
    if (count > 0 && j->m_links) r.add((u64)j->m_links, (u32)count * sizeof(ADMLink));
}
// The ADM's joints, their links, the roots' calc data, the ADM's link list.
void SolverRegions(const u64 x[9], live::Regions& r) {
    auto* a = reinterpret_cast<const ArticulatedDynamicsManagerBase*>(x[0]);
    if (!a) return;
    if (a->m_joints && a->m_jointCount > 0) {
        r.add((u64)a->m_joints, (u32)a->m_jointCount * sizeof(ADMJoint));
        for (s32 i = 0; i < a->m_jointCount; i++) ExtraJoint(&a->m_joints[i], r);
    }
    if (a->m_rootCalc && a->m_rootCount > 0) r.add((u64)a->m_rootCalc, (u32)a->m_rootCount * sizeof(ADM_CALC_DATA));
    if (a->m_linkList && a->m_linkCount > 0) r.add((u64)a->m_linkList, (u32)a->m_linkCount * sizeof(ADMLink));
    // (Not m_hitFlags: the ADMs of one character share it, and their workers set it concurrently;
    // the unit test compares it.)
}

#define DYN_SIM(sym, hostfn, label)                                                                               \
    static int NATIVE_CONCAT(dyn_sim_, __LINE__) = family().extra(family().add_leaf(sym, hostfn, kAdmBytes, kVoid, label, {}), \
                                                                  SolverRegions)

using Adm = ArticulatedDynamicsManagerBase;
DYN_SIM("_ZN4Aska30ArticulatedDynamicsManagerBase16CollisionSettingINS_26ArticulatedDynamicsManagerEEEvPT_jj",
        &live::leaf_function<&Adm::CollisionSetting>, "Aska::ArticulatedDynamicsManagerBase::CollisionSetting<ADM>");
DYN_SIM("_ZN4Aska30ArticulatedDynamicsManagerBase15InterpolateRootINS_26ArticulatedDynamicsManagerEEEvPT_PNS_8ADMJointES6_fjj",
        &live::leaf_function<&Adm::InterpolateRoot>, "Aska::ArticulatedDynamicsManagerBase::InterpolateRoot<ADM>");
DYN_SIM("_ZN4Aska26ArticulatedDynamicsManager29PreprocessBeforeInternalForceIS0_EEvPT_PNS_8ADMJointES5_ffjjb",
        &live::leaf_function<&Adm::PreprocessBeforeInternalForce>, "Aska::ArticulatedDynamicsManager::PreprocessBeforeInternalForce<ADM>");
DYN_SIM("_ZN4Aska30ArticulatedDynamicsManagerBase22CollisionAndConstraintINS_26ArticulatedDynamicsManagerEEEvPT_PNS_8ADMJointES6_jjf",
        &live::leaf_function<&Adm::CollisionAndConstraint>, "Aska::ArticulatedDynamicsManagerBase::CollisionAndConstraint<ADM>");
DYN_SIM("_ZN4Aska30ArticulatedDynamicsManagerBase10StandardIKINS_26ArticulatedDynamicsManagerELb1EEEvPT_ffi",
        &live::leaf_function<&Adm::StandardIK>, "Aska::ArticulatedDynamicsManagerBase::StandardIK<ADM, true>");
DYN_SIM("_ZN4Aska26ArticulatedDynamicsManager12SimulateMainIS0_EEvPT_PNS_8ADMJointES5_jiijffjf", &live::leaf_function<&Adm::SimulateMain>,
        "Aska::ArticulatedDynamicsManager::SimulateMain<ADM>");
static int dyn_sim_simulate = family().extra(family().add_leaf("_ZN4Aska26ArticulatedDynamicsManager8SimulateEfjf", &live::leaf_method<&Adm::Simulate>,
                                                               kAdmBytes, kInt, "Aska::ArticulatedDynamicsManager::Simulate", {}),
                                             SolverRegions);

}  // namespace

}  // namespace soa::native::dynamics
