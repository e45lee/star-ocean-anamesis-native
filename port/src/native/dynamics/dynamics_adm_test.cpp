// Differential tests of the ADM bracket's natives (dynamics_adm.cpp) against the 3.7.0 guest: a
// joint set built in an arena of buffers (random floats and flags, real pointers between them, the
// scene nodes' guest vtable), run by the guest, the arena's bytes saved, put back, run by the
// native, compared byte for byte. The nodes (HierarchicalObjectContainer::
// m_flags bit 0, render_layout.h's "matrix fixed", is the stale mark: UpdateHierarchically sets it
// on the subtree, MakeMatrix clears it): a fake node has no children, MakeMatrix is a no-op.
#include <cstring>
#include <memory>
#include <vector>

#include "core/loader.h"
#include "native/dynamics/dynamics_layout.h"
#include "native/dynamics/gen/dynamics_addresses.h"
#include "native/math/math_test_util.h"

namespace soa::native::dynamics {

using namespace math::test;

namespace {

// Buffers whose bytes a test saves, restores and compares.
class Arena {
public:
    template <typename T>
    T* alloc(TestContext& t, size_t bytes = sizeof(T), int special = 0) {
        bufs_.emplace_back(new (std::align_val_t(16)) u8[bytes], bytes);
        u8* p = bufs_.back().p;
        for (size_t i = 0; i + 4 <= bytes; i += 4) {
            float v = rand_float(t, 4, special);
            std::memcpy(p + i, &v, 4);
        }
        return reinterpret_cast<T*>(p);
    }
    std::vector<std::vector<u8>> save() const {
        std::vector<std::vector<u8>> s;
        for (auto& b : bufs_) s.emplace_back(b.p, b.p + b.n);
        return s;
    }
    void restore(const std::vector<std::vector<u8>>& s) {
        for (size_t i = 0; i < bufs_.size(); i++) std::memcpy(bufs_[i].p, s[i].data(), bufs_[i].n);
    }
    // "" or where the first difference is.
    std::string diff(const std::vector<std::vector<u8>>& a, const std::vector<std::vector<u8>>& b) const {
        for (size_t i = 0; i < a.size(); i++)
            for (size_t k = 0; k < a[i].size(); k++)
                if (a[i][k] != b[i][k]) return "buffer " + std::to_string(i) + " +0x" + std::to_string(k);
        return "";
    }
    ~Arena() {
        for (auto& b : bufs_) operator delete[](b.p, std::align_val_t(16));
    }

private:
    struct Buf {
        u8* p;
        size_t n;
        Buf(u8* p_, size_t n_) : p(p_), n(n_) {}
    };
    std::vector<Buf> bufs_;
};

// A scene node: the container inside a HierarchicalObject whose vtable is a copy of the guest's
// with slot 21 (MakeMatrix) a no-op guest function (Aska::Dynamics::Run: RET), so a stale matrix
// costs nothing; no children or referrers, so UpdateHierarchically only marks it.
HierarchicalObject* make_owner(TestContext& t, Arena& a, int special) {
    auto* h = a.alloc<HierarchicalObject>(t, 0x1a0, special);
    auto* vt = a.alloc<u64>(t, 64 * 8);
    std::memcpy(vt, reinterpret_cast<const void*>(t.sym("_ZTVN4Aska18HierarchicalObjectE") + 0x10), 64 * 8);
    vt[kSlotMakeMatrix] = t.sym("_ZN4Aska8Dynamics3RunEv");
    h->base.link.vtable = vt;
    h->m_hoc.m_flags = (u8)t.rand_int(0, 255);
    h->m_hoc.m_world = rand_matrix(t, special);
    h->m_hoc.m_parent = nullptr;
    h->m_hoc.m_firstChild = nullptr;
    h->m_hoc.m_referrers = nullptr;
    h->m_hoc.m_prevSibling = h->m_hoc.m_nextSibling = &h->m_hoc;
    h->m_hoc.m_owner = h;
    return h;
}

// A joint set: n joints over nodes, some roots with node parents and a parent buffer, the others
// chained to the previous joint's calc data, links between neighbours.
struct JointSet {
    std::vector<ADMJoint*> joints;
    ADMJoint* array = nullptr;
};
JointSet make_joints(TestContext& t, Arena& a, int n, int special) {
    JointSet s;
    s.array = a.alloc<ADMJoint>(t, sizeof(ADMJoint) * n, special);
    for (int i = 0; i < n; i++) {
        ADMJoint& j = s.array[i];
        s.joints.push_back(&j);
        HierarchicalObject* owner = make_owner(t, a, special);
        j.m_node = &owner->m_hoc;
        j.m_node->m_parent = t.rand_int(0, 2) ? &make_owner(t, a, special)->m_hoc : nullptr;
        j.m_isRoot = (u8)(i == 0 || t.rand_int(0, 4) == 0);
        if (j.m_isRoot)
            j.m_calc.m_parent = t.rand_int(0, 4) ? a.alloc<ADM_CALC_DATA>(t, sizeof(ADM_CALC_DATA), special) : nullptr;
        else
            j.m_calc.m_parent = &s.array[i - 1].m_calc;
        j.m_hasPivot = (u8)t.rand_int(0, 1);
        j.m_writesPosture = (u8)t.rand_int(0, 1);
        j.m_flags0 = (u8)t.rand_int(0, 255);
        j.m_flags1 = (u8)t.rand_int(0, 255);
        j.m_dampDownwards = (u8)t.rand_int(0, 1);
        j.m_linkCount = 0;
        j.m_links = nullptr;
    }
    for (int i = 0; i < n; i++) {
        ADMJoint& j = s.array[i];
        int links = t.rand_int(0, 3);
        if (!links) continue;
        j.m_links = a.alloc<ADMLink>(t, sizeof(ADMLink) * links, special);
        j.m_linkCount = (u32)links;
        for (int k = 0; k < links; k++) {
            j.m_links[k].m_flags = (u8)t.rand_int(0, 255);
            j.m_links[k].m_joint0 = &j;
            j.m_links[k].m_joint1 = &s.array[t.rand_int(0, n - 1)];
        }
    }
    return s;
}

}  // namespace

NATIVE_TEST("dynamics/joint-external-force") {
    Mismatches bad{t, "ADMJoint::ExternalForce"};
    for (int k = 0; k < 20000; k++) {
        int special = k < 15000 ? 0 : 150;
        Arena a;
        auto* j = a.alloc<ADMJoint>(t, sizeof(ADMJoint), special);
        j->m_flags0 = (u8)(t.rand_int(0, 7) ? 0 : 1);
        j->m_flags1 = (u8)t.rand_int(0, 255);
        j->m_dampDownwards = (u8)t.rand_int(0, 1);
        if (t.rand_int(0, 3)) j->m_mass = std::fabs(j->m_mass);
        auto* ext = a.alloc<Vector>(t, sizeof(Vector), special);
        auto* calc = a.alloc<ADM_CALC_DATA>(t, sizeof(ADM_CALC_DATA), special);
        float dt = rand_float(t, 0.1f, special), mx = rand_float(t, 2, special), g = rand_float(t, 10, special);
        bool full = k % 5 == 0;
        auto before = a.save();
        t.call("_ZN4Aska8ADMJoint13ExternalForceEfffPKNS_6VectorEPNS_13ADM_CALC_DATAEb", GuestArgs().p(j).p(ext).p(calc).i(full).f(dt).f(mx).f(g));
        auto guest = a.save();
        a.restore(before);
        j->ExternalForce(dt, mx, g, ext, calc, full);
        std::string d = a.diff(guest, a.save());
        bad.check(k, d.empty(), d);
    }
}

NATIVE_TEST("dynamics/joint-prepare-flush") {
    Mismatches prep{t, "ADMJoint::PrepareCalc"}, flush{t, "ADMJoint::Flush"};
    for (int k = 0; k < 3000; k++) {
        int special = k < 2400 ? 0 : 150;
        Arena a;
        JointSet s = make_joints(t, a, t.rand_int(1, 6), special);
        ADMJoint* j = s.joints[t.rand_int(0, (int)s.joints.size() - 1)];
        if (k % 40 == 0) j->m_node = nullptr;
        auto before = a.save();
        t.call("_ZN4Aska8ADMJoint11PrepareCalcEv", GuestArgs().p(j));
        auto guest = a.save();
        a.restore(before);
        j->PrepareCalc();
        std::string d = a.diff(guest, a.save());
        prep.check(k, d.empty(), d);
        if (!j->m_node) continue;
        a.restore(before);
        t.call("_ZN4Aska8ADMJoint5FlushEv", GuestArgs().p(j));
        guest = a.save();
        a.restore(before);
        j->Flush();
        d = a.diff(guest, a.save());
        flush.check(k, d.empty(), d);
    }
}

// ArticulatedDynamicsManagerBase::PrepareCalc / Flush over a joint set: every branch (disabled,
// motion blend, velocities from the motion, the pose reset, its early returns).
NATIVE_TEST("dynamics/adm-prepare-flush") {
    Mismatches prep{t, "ArticulatedDynamicsManagerBase::PrepareCalc"}, flush{t, "ArticulatedDynamicsManagerBase::Flush"};
    for (int k = 0; k < 3000; k++) {
        int special = k < 2400 ? 0 : 150;
        Arena a;
        int n = t.rand_int(0, 6);
        auto* m = a.alloc<ArticulatedDynamicsManagerBase>(t, 0x1c0, special);
        JointSet s = n ? make_joints(t, a, n, special) : JointSet{};
        m->m_joints = s.array;
        m->m_jointCount = (s16)n;
        m->m_enabled = (u8)(k % 20 != 0);
        m->m_skipFlush = (u8)t.rand_int(0, 1);
        m->m_resetVelocity = (u8)(t.rand_int(0, 3) == 0);
        m->m_motionBlend = (u8)t.rand_int(0, 1);
        m->m_flushed = (u8)t.rand_int(0, 1);
        m->m_resetPending = (u8)t.rand_int(0, 1);
        m->m_resetRequest = (u8)t.rand_int(0, 1);
        if (t.rand_int(0, 1)) m->m_blendRate = 0.99999f;
        m->m_model = nullptr;
        if (t.rand_int(0, 2) == 0) {
            auto* model = a.alloc<render::RenderableObject>(t, sizeof(render::RenderableObject), special);
            model->m_renderFlags = (u32)t.rand_int(0, 0xffff);
            m->m_model = model;
        }
        m->m_gravityNode = t.rand_int(0, 1) ? make_owner(t, a, special) : nullptr;
        // the pose reset compares rotations: make some equal
        for (ADMJoint* j : s.joints)
            if (t.rand_int(0, 1)) j->m_prevRotation = j->m_calc.m_rotation;
        float dt = rand_float(t, 0.1f, special);
        auto before = a.save();
        t.call("_ZN4Aska30ArticulatedDynamicsManagerBase11PrepareCalcEf", GuestArgs().p(m).f(dt));
        auto guest = a.save();
        a.restore(before);
        m->PrepareCalc(dt);
        std::string d = a.diff(guest, a.save());
        prep.check(k, d.empty(), d);
        a.restore(before);
        t.call("_ZN4Aska30ArticulatedDynamicsManagerBase5FlushEv", GuestArgs().p(m));
        guest = a.save();
        a.restore(before);
        m->Flush();
        d = a.diff(guest, a.save());
        flush.check(k, d.empty(), d);
    }
}

}  // namespace soa::native::dynamics

namespace soa::native::dynamics {

// The link constraint (ADMSolver::SolveLink, FUN_02429994) in its three modes, fixed ends, zero /
// special weights: the guest at its address, the native; both joints' bytes compared.
NATIVE_TEST("dynamics/solve-link") {
    using math::test::rand_float;
    Mismatches bad{t, "ADMSolver::SolveLink"};
    const u64 fn = main_lib()->base + kFunSolveLink;
    for (int k = 0; k < 30000; k++) {
        int special = k < 22000 ? 0 : 150;
        Arena a;
        auto* j0 = a.alloc<ADMJoint>(t, sizeof(ADMJoint), special);
        auto* j1 = a.alloc<ADMJoint>(t, sizeof(ADMJoint), special);
        for (ADMJoint* j : {j0, j1}) {
            j->m_flags0 = (u8)(t.rand_int(0, 5) ? 0 : t.rand_int(0, 255));
            if (t.rand_int(0, 4) == 0) j->m_mass = 0.0f;
            else if (t.rand_int(0, 2)) j->m_mass = std::fabs(j->m_mass);
        }
        u8 mode = (u8)(k % 7 == 0 ? t.rand_int(0, 255) : t.rand_int(0, 1));
        float rest = std::fabs(rand_float(t, 3, special)), k1 = rand_float(t, 1, special), k2 = rand_float(t, 1, special);
        auto before = a.save();
        guest_call(fn, GuestArgs().i(mode).p(j0).p(j1).f(rest).f(k1).f(k2));
        auto guest = a.save();
        a.restore(before);
        ADMSolver::SolveLink(mode, j0, j1, rest, k1, k2);
        std::string d = a.diff(guest, a.save());
        bad.check(k, d.empty(), "mode " + std::to_string(mode) + ": " + d);
    }
}

}  // namespace soa::native::dynamics

namespace soa::native::dynamics {

// The contact response (FUN_0242a9f4): fixed ends, t on both sides of 0.01 / 0.99, slow and fast
// contacts, zero / special weights.
NATIVE_TEST("dynamics/resolve-contact") {
    using math::test::rand_float;
    Mismatches bad{t, "ADMSolver::ResolveContact"};
    const u64 fn = main_lib()->base + kFunResolveContact;
    for (int k = 0; k < 30000; k++) {
        int special = k < 22000 ? 0 : 150;
        Arena a;
        auto* j0 = a.alloc<ADMJoint>(t, sizeof(ADMJoint), special);
        auto* j1 = a.alloc<ADMJoint>(t, sizeof(ADMJoint), special);
        auto* link = a.alloc<ADMLink>(t, sizeof(ADMLink), special);
        auto* n = a.alloc<Vector>(t, sizeof(Vector), special);
        for (ADMJoint* j : {j0, j1}) {
            j->m_flags0 = (u8)(t.rand_int(0, 3) ? 0 : t.rand_int(0, 255));
            if (t.rand_int(0, 4) == 0) j->m_mass = 0.0f;
            else if (t.rand_int(0, 2)) j->m_mass = std::fabs(j->m_mass);
        }
        float tt;
        switch (t.rand_int(0, 4)) {
        case 0: tt = 0.01f + rand_float(t, 0.002f, 0); break;
        case 1: tt = 0.99f + rand_float(t, 0.002f, 0); break;
        case 2: tt = (float)t.rand_int(0, 1); break;
        default: tt = rand_float(t, 1.2f, special);
        }
        if (t.rand_int(0, 20) == 0) tt = from_bits(0x3c23d70au + (u32)t.rand_int(-1, 1));  // 0.01 and its neighbours
        if (t.rand_int(0, 20) == 0) tt = from_bits(0x3f7d70a4u + (u32)t.rand_int(-1, 1));  // 0.99 and its neighbours
        float depth = rand_float(t, 0.5f, special), r0 = rand_float(t, 1, special), r1 = rand_float(t, 1, special);
        float speed = rand_float(t, 5, special), dt = rand_float(t, 0.1f, special);
        auto before = a.save();
        guest_call(fn, GuestArgs().p(link).p(j0).p(j1).p(n).f(tt).f(depth).f(r0).f(r1).f(speed).f(dt));
        auto guest = a.save();
        a.restore(before);
        ADMSolver::ResolveContact(link, j0, j1, n, tt, depth, r0, r1, speed, dt);
        std::string d = a.diff(guest, a.save());
        if (!d.empty() && bad.n < 3) {
            auto nat = a.save();
            const float* gp = reinterpret_cast<const float*>(guest[0].data() + 0x10);
            const float* np = reinterpret_cast<const float*>(nat[0].data() + 0x10);
            t.fail("t %08x depth %08x r0 %08x r1 %08x speed %08x dt %08x flags %d %d mass %08x %08x guest %08x %08x %08x native %08x %08x %08x",
                   bits(tt), bits(depth), bits(r0), bits(r1), bits(speed), bits(dt), j0->m_flags0 & 1, j1->m_flags0 & 1, bits(j0->m_mass),
                   bits(j1->m_mass), bits(gp[0]), bits(gp[1]), bits(gp[2]), bits(np[0]), bits(np[1]), bits(np[2]));
        }
        bad.check(k, d.empty(), d);
    }
}

// The velocity update (FUN_0242ac84): rest or not, friction above / below 1, zero / NaN, touched.
NATIVE_TEST("dynamics/update-velocity") {
    using math::test::rand_float;
    Mismatches bad{t, "ADMSolver::UpdateVelocity"};
    const u64 fn = main_lib()->base + kFunUpdateVelocity;
    for (int k = 0; k < 30000; k++) {
        int special = k < 22000 ? 0 : 150;
        Arena a;
        auto* j = a.alloc<ADMJoint>(t, sizeof(ADMJoint), special);
        auto* c = a.alloc<ADM_CALC_DATA>(t, sizeof(ADM_CALC_DATA), special);
        j->m_contact = (u8)(t.rand_int(0, 1) ? 0 : t.rand_int(0, 255));
        if (t.rand_int(0, 3) == 0) j->m_contactFriction = 0.0f;
        if (t.rand_int(0, 5) == 0) j->m_contactNormal = Vector{0, 0, 0, 1};
        bool rest = k % 9 == 0;
        float inv = rand_float(t, 60, special);
        auto before = a.save();
        guest_call(fn, GuestArgs().p(j).p(c).i(rest).f(inv));
        auto guest = a.save();
        a.restore(before);
        ADMSolver::UpdateVelocity(j, c, rest, inv);
        std::string d = a.diff(guest, a.save());
        bad.check(k, d.empty(), d);
    }
}

}  // namespace soa::native::dynamics
