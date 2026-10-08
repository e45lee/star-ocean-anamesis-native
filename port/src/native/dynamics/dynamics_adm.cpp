// The articulated dynamics' per-frame bracket: ArticulatedDynamicsManagerBase::PrepareCalc (the
// joints from their scene nodes) and Flush (back into them), with ADMJoint's PrepareCalc, Flush and
// ExternalForce (dynamics_layout.h; port/decomp/dynamics/adm.c, adm_templates.c). Written from the
// disassembly's operation order and branch conditions (dynamics_family.h).
#include "native/dynamics/dynamics_family.h"
#include "native/dynamics/gen/dynamics_addresses.h"

namespace soa::native::dynamics {

namespace {

const F kZero(0.0f), kOne(1.0f);

template <typename T>
const T& guest_at(u64 vaddr) {
    return *reinterpret_cast<const T*>(main_lib()->base + vaddr);
}

// Guest helpers (guest code): Vector::ApplyQuaternion(out, q) const, ApplyMatrixNoTransport, the
// node container's UpdateHierarchically, MatrixCalcFunc.
void ApplyQuaternion(const Vector* v, Vector* out, const Quaternion* q) {
    static const u64 fn = fn_addr("_ZNK4Aska6Vector15ApplyQuaternionEPS0_PKNS_10QuaternionE");
    call(fn, {(u64)v, (u64)out, (u64)q});
}
void ApplyMatrixNoTransport(const Vector* v, Vector* out, const Matrix* m) {
    static const u64 fn = fn_addr("_ZNK4Aska6Vector22ApplyMatrixNoTransportEPS0_PKNS_6MatrixE");
    call(fn, {(u64)v, (u64)out, (u64)m});
}
// The node's matrices made current before it is written (unless its matrix is fixed: m_flags bit 0).
void UpdateHierarchicallyUnlessFixed(HierarchicalObjectContainer* n) {
    static const u64 fn = fn_addr("_ZN4Aska27HierarchicalObjectContainer20UpdateHierarchicallyEv");
    if (!(n->m_flags & 1)) call(fn, {(u64)n});
}
// m_calc.m_matrix from the joint's local transform and its parent's.
void MatrixCalc(ADM_CALC_DATA* c) {
    static const u64 fn = fn_addr("_ZN4Aska14MatrixCalcFuncEPNS_6MatrixEPKNS_6VectorEPKNS_10QuaternionES7_S4_S4_PKS0_");
    ADM_CALC_DATA* p = c->m_parent;
    call(fn, {(u64)&c->m_matrix, (u64)&c->m_position, (u64)&c->m_rotation, (u64)&c->m_orientation, (u64)&c->m_scale,
              p ? (u64)&p->m_scale : 0, (u64)p});
}
HierarchicalObject* owner_of(HierarchicalObjectContainer* n) { return static_cast<HierarchicalObject*>(n->m_owner); }

// ArticulatedDynamicsManagerBase::PrepareCalc's motion blend: below it the ADM blends with the
// animation (.rodata 0x28c49e4).
const F& blend_full() {
    static const F v(guest_at<float>(kBlendFull));
    return v;
}

}  // namespace

// ---- ADMJoint ----

void ADMJoint::PrepareCalc() {
    HierarchicalObjectContainer* n = m_node;
    if (!n) return;
    HierarchicalObject* owner = owner_of(n);
    if (owner->m_hoc.m_flags & kHocMatrixStale) vcall(owner, kSlotMakeMatrix);
    if (m_isRoot && n->m_parent && m_calc.m_parent) m_calc.m_parent->m_matrix = n->m_parent->m_world;
    if (m_hasPivot) {
        alignas(16) Vector r;
        ApplyQuaternion(&m_pivot, &r, &n->m_posture);
        F x = (F(n->m_param9.x) + F(n->m_position.x)) + F(r.x);
        F y = (F(n->m_param9.y) + F(n->m_position.y)) + F(r.y);
        F z = (F(n->m_param9.z) + F(n->m_position.z)) + F(r.z);
        m_calc.m_position = Vector{f(x), f(y), f(z), 1.0f};
    } else {
        m_calc.m_position = n->m_position;
    }
    m_calc.m_rotation = n->m_posture;
    m_calc.m_scale = n->m_scale;
    s32 count = (s32)m_linkCount;
    for (s32 i = 0; i < count; i++) {
        ADMLink& l = m_links[i];
        if (!(l.m_flags & 0x10)) continue;
        const Vector& o = l.m_joint1->m_position;
        F dx = F(m_position.x) - F(o.x), dy = F(m_position.y) - F(o.y), dz = F(m_position.z) - F(o.z);
        l.m_length = f(Sqrt((dx * dx + dy * dy) + dz * dz));
        l.m_joint1->m_lengthDirty = 1;
    }
}

void ADMJoint::Flush() {
    HierarchicalObjectContainer* n = m_node;
    if (m_hasPivot) {
        alignas(16) Vector r;
        ApplyQuaternion(&m_pivot, &r, &m_calc.m_rotation);
        F x = (F(m_calc.m_position.x) - F(r.x)) - F(n->m_param9.x);
        F y = (F(m_calc.m_position.y) - F(r.y)) - F(n->m_param9.y);
        F z = (F(m_calc.m_position.z) - F(r.z)) - F(n->m_param9.z);
        float w = m_calc.m_position.w;
        UpdateHierarchicallyUnlessFixed(n);
        n->m_position = Vector{f(x), f(y), f(z), w};
    } else {
        UpdateHierarchicallyUnlessFixed(n);
        n->m_position = m_calc.m_position;
    }
    if (m_writesPosture) {
        UpdateHierarchicallyUnlessFixed(n);
        n->m_posture = m_calc.m_rotation;
    }
    UpdateHierarchicallyUnlessFixed(n);
    n->m_scale = m_calc.m_scale;
}

void ADMJoint::ExternalForce(float dt, float max_rate, float g, const Vector* ext, ADM_CALC_DATA* calc, bool full) {
    if (m_flags0 & 1) {  // fixed: where the animation puts it
        m_position.x = calc->m_matrix.m[0][3];
        m_position.y = calc->m_matrix.m[1][3];
        m_position.z = calc->m_matrix.m[2][3];
        m_position.w = 1.0f;
        return;
    }
    const u8 flags = m_flags1;
    const F px(m_position.x), py(m_position.y), pz(m_position.z), t(dt);
    F ax = kZero, az = kZero;
    F ay = (flags & 1) ? kZero - F(g) : kZero;
    F mass(m_mass);
    if (((flags & 2) || full) && mass > kZero) {  // (b.le: a NaN mass doesn't damp)
        F rate;
        if (full) rate = kOne;
        else if (m_dampDownwards && F(m_velocity.y) < kZero) rate = F(m_dampingDown);  // (b.pl: a NaN velocity takes m_damping)
        else rate = F(m_damping);
        rate = rate / mass;
        F k = rate < F(max_rate) ? rate : F(max_rate);  // (fcsel mi)
        ax = kZero - F(m_velocity.x) * k;
        ay = ay - F(m_velocity.y) * k;
        az = kZero - k * F(m_velocity.z);
    }
    F vx = ax * t + F(m_velocity.x);
    F vy = ay * t + F(m_velocity.y);
    m_velocity.x = f(vx);
    m_velocity.y = f(vy);
    F vz = az * t + F(m_velocity.z);
    m_velocity.z = f(vz);
    F x = px + vx * t, y = py + vy * t, z = pz + vz * t;
    if (flags & 0x40) {
        x = x + F(ext->x) * t;
        y = y + F(ext->y) * t;
        z = z + F(ext->z) * t;
    }
    m_position.x = f(x);
    m_position.y = f(y);
    m_position.z = f(z);
    m_position.w = 1.0f;
}

// ---- ArticulatedDynamicsManagerBase ----

void ArticulatedDynamicsManagerBase::PrepareCalc(float dt) {
    if (!m_enabled) {
        m_flushed = m_resetPending = 0;
        return;
    }
    ADMJoint* const first = m_joints;
    const s64 n = m_jointCount;
    ADMJoint* const end = first + n;
    ADMJoint* j = first;
    if (m_motionBlend) {
        const F rate(m_blendRate);
        if (rate < blend_full() && n != 0) {  // (b.pl: a NaN rate doesn't blend)
            for (s64 i = 0; i < n; i++) {
                ADMJoint& a = first[i];
                F w = rate * F(a.m_blendWeight);
                HierarchicalObjectContainer* node = a.m_node;
                if (a.m_isRoot) {
                    UpdateHierarchicallyUnlessFixed(node);
                    node->m_position = a.m_calc.m_position;
                }
                if (w < F(0.5f) && a.m_writesPosture) {  // (b.pl)
                    UpdateHierarchicallyUnlessFixed(node);
                    node->m_posture = a.m_calc.m_rotation;
                }
            }
            j = m_joints;
        }
    }
    if (checking()) {
        static const u64 fn = fn_addr("_ZN4Aska8ADMJoint11PrepareCalcEv");
        for (; j != end; j++) call(fn, {(u64)j});
    } else {
        for (; j != end; j++) j->PrepareCalc();
    }
    for (ADMJoint* k = m_joints; k != end; k++) MatrixCalc(&k->m_calc);

    if (!m_skipFlush && m_gravityNode) {
        if (m_gravityNode->m_hoc.m_flags & kHocMatrixStale) vcall(m_gravityNode, kSlotMakeMatrix);
        HierarchicalObject* g = m_gravityNode;
        ApplyMatrixNoTransport(&m_gravity, &m_gravityWorld, reinterpret_cast<const Matrix*>(vcall(g, kSlotWorldMatrix)));
    }

    ADMJoint* joints = m_joints;
    bool from_motion = m_resetVelocity != 0;
    if (!from_motion) {
        bool moving = m_model && (m_model->m_renderFlags & 0x2101);  // (a u16 load: bits 0, 8, 13)
        from_motion = moving || F(m_blendRate) >= blend_full();  // (b.ge: a NaN rate resets)
    }
    if (from_motion) {
        if ((s32)n != 0) {
            const F inv = kOne / F(dt);
            for (s64 i = 0; i < n; i++) {
                ADMJoint& a = joints[i];
                const Matrix& m = a.m_calc.m_matrix;
                const float tx = m.m[0][3], ty = m.m[1][3], tz = m.m[2][3];
                a.m_prevRotation = a.m_calc.m_rotation;
                F vx = inv * (F(tx) - F(a.m_prevPosition.x));
                F vy = inv * (F(ty) - F(a.m_prevPosition.y));
                F vz = inv * (F(tz) - F(a.m_prevPosition.z));
                a.m_position = Vector{tx, ty, tz, 1.0f};
                a.m_velocity.x = f(vx);
                a.m_velocity.y = f(vy);
                a.m_velocity.z = f(vz);
            }
        }
        if (!m_skipFlush) m_skipFlush = 1;
        m_flushed = m_resetPending = 0;
        return;
    }
    // At rest: the pose reset (the joints where the animation puts them, no velocity), when
    // pending; this path leaves m_flushed / m_resetPending as they are.
    if (!m_resetPending) return;
    if (!m_skipFlush && !m_motionBlend && !m_resetRequest) return;
    m_skipFlush = 0;
    m_resetRequest = 0;
    if ((s32)n == 0) return;
    const Vector& rest = guest_at<Vector>(kRigidInverseLastRow);  // (0, 0, 0, 1)
    for (s64 i = 0; i < n; i++) {
        ADMJoint& a = joints[i];
        const Quaternion r = a.m_calc.m_rotation;
        const Matrix& m = a.m_calc.m_matrix;
        a.m_position = Vector{m.m[0][3], m.m[1][3], m.m[2][3], 1.0f};
        const Quaternion& p = a.m_prevRotation;
        bool same = F(r.w) == F(p.w) && F(r.y) == F(p.y) && F(r.z) == F(p.z) && F(r.x) == F(p.x);
        if (!same) a.m_rotation80 = r;
        a.m_prevRotation = r;
        a.m_velocity = rest;
    }
}

void ArticulatedDynamicsManagerBase::Flush() {
    if (m_flushed && !m_skipFlush) {
        s64 n = m_jointCount;
        static const u64 fn = fn_addr("_ZN4Aska8ADMJoint5FlushEv");
        for (s64 i = 0; i < n; i++)
            if (checking()) call(fn, {(u64)&m_joints[i]});
            else m_joints[i].Flush();
    }
    m_flushed = m_resetPending = 1;
}

// ---- registration ----

namespace {

using live::kVoid;
constexpr u32 kAdmBytes = 0x1c0;  // ArticulatedDynamicsManager (the instantiation that runs)

// A joint's memory besides itself: a root's parent buffer, its links and the joints they reach
// (PrepareCalc), its node's transform (Flush, the blend write-back).
void JointExtra(const ADMJoint* j, live::Regions& r) {
    if (j->m_calc.m_parent && j->m_isRoot) r.add((u64)j->m_calc.m_parent, sizeof(Matrix));
    s32 count = (s32)j->m_linkCount;
    if (count > 0 && j->m_links) {
        r.add((u64)j->m_links, (u32)count * sizeof(ADMLink));
        for (s32 i = 0; i < count; i++)
            if (const ADMJoint* o = j->m_links[i].m_joint1) r.add((u64)&o->m_lengthDirty, 1);
    }
    if (HierarchicalObjectContainer* n = j->m_node) {
        r.add((u64)&n->m_position, offsetof(HierarchicalObjectContainer, m_param9) - offsetof(HierarchicalObjectContainer, m_position));
        if (auto* o = static_cast<HierarchicalObject*>(n->m_owner)) r.add((u64)&o->m_hoc.m_flags, 1);
    }
}
void JointRegions(const u64 x[9], live::Regions& r) {
    if (auto* j = reinterpret_cast<const ADMJoint*>(x[0])) JointExtra(j, r);
}
void AdmRegions(const u64 x[9], live::Regions& r) {
    auto* a = reinterpret_cast<const ArticulatedDynamicsManagerBase*>(x[0]);
    if (!a || !a->m_joints || a->m_jointCount <= 0) return;
    r.add((u64)a->m_joints, (u32)a->m_jointCount * sizeof(ADMJoint));
    for (s32 i = 0; i < a->m_jointCount; i++) JointExtra(&a->m_joints[i], r);
}

#define DYN_ADM(sym, method, bytes, label, extra_fn)                                                             \
    static int NATIVE_CONCAT(dyn_adm_, __LINE__) = family().extra(                                               \
        family().add_leaf(sym, &live::leaf_method<method>, bytes, kVoid, label, {}), extra_fn)

DYN_ADM("_ZN4Aska8ADMJoint11PrepareCalcEv", &ADMJoint::PrepareCalc, sizeof(ADMJoint), "Aska::ADMJoint::PrepareCalc", JointRegions);
DYN_ADM("_ZN4Aska8ADMJoint5FlushEv", &ADMJoint::Flush, sizeof(ADMJoint), "Aska::ADMJoint::Flush", JointRegions);
DYN_ADM("_ZN4Aska8ADMJoint13ExternalForceEfffPKNS_6VectorEPNS_13ADM_CALC_DATAEb", &ADMJoint::ExternalForce, sizeof(ADMJoint),
        "Aska::ADMJoint::ExternalForce", nullptr);
DYN_ADM("_ZN4Aska30ArticulatedDynamicsManagerBase11PrepareCalcEf", &ArticulatedDynamicsManagerBase::PrepareCalc, kAdmBytes,
        "Aska::ArticulatedDynamicsManagerBase::PrepareCalc", AdmRegions);
DYN_ADM("_ZN4Aska30ArticulatedDynamicsManagerBase5FlushEv", &ArticulatedDynamicsManagerBase::Flush, kAdmBytes,
        "Aska::ArticulatedDynamicsManagerBase::Flush", AdmRegions);

}  // namespace

}  // namespace soa::native::dynamics
