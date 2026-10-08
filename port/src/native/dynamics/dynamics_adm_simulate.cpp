// The ADM solver loop: ArticulatedDynamicsManager::Simulate and the templates it runs per step
// (SimulateMain, PreprocessBeforeInternalForce, InterpolateRoot, CollisionSetting) for the
// ArticulatedDynamicsManager instantiation (dynamics_layout.h; port/decomp/dynamics/adm.c,
// adm_templates.c). Written from the disassembly. The parts still guest code (CollisionAndConstraint,
// StandardIK, Finalize, MatrixPreFixAndMotionBlend, the force-emitter functor, ...) are guest calls.
#include "core/cpu.h"
#include "native/dynamics/dynamics_family.h"
#include "native/dynamics/gen/dynamics_addresses.h"

namespace soa::native::dynamics {

namespace {

const F kZero(0.0f), kOne(1.0f), kHalf(0.5f), kEps(math::kEpsilon);

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
                guest_invoke<void>(fn_collision_and_constraint(), adm, first, end, collision_count, constraints, dt);
            }
            if (ik) guest_invoke<void>(fn_ik_true(), adm, ik_steps, dt, inv_dt);
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
DYN_SIM("_ZN4Aska26ArticulatedDynamicsManager12SimulateMainIS0_EEvPT_PNS_8ADMJointES5_jiijffjf", &live::leaf_function<&Adm::SimulateMain>,
        "Aska::ArticulatedDynamicsManager::SimulateMain<ADM>");
static int dyn_sim_simulate = family().extra(family().add_leaf("_ZN4Aska26ArticulatedDynamicsManager8SimulateEfjf", &live::leaf_method<&Adm::Simulate>,
                                                               kAdmBytes, kInt, "Aska::ArticulatedDynamicsManager::Simulate", {}),
                                             SolverRegions);

}  // namespace

}  // namespace soa::native::dynamics
