// Layout tests for render_layout.h (port/PLAN.md task 6, types first): the recovered classes read against
// real guest objects. A test either builds a private object with the guest's own constructor and drives
// it with the guest's methods (t.call / vcall: natives are not installed in --selftest), then reads the
// fields through the layout classes, or walks the running game's objects at a frame boundary
// (testutil::on_frame) and compares their fields with the guest's getters. No natives here.
#include <cstring>

#include "native/common/test.h"
#include "native/render/render_layout.h"
#include "native/render/render_test_util.h"

namespace soa::native::render {
namespace {

using namespace testutil;

// A RenderableObject in host memory, built by the guest's constructor and destroyed by its destructor.
struct PrivateRenderable {
    alignas(16) u8 storage[sizeof(RenderableObject)];
    TestContext& t;
    explicit PrivateRenderable(TestContext& tc) : t(tc) {
        std::memset(storage, 0xa5, sizeof storage);
        t.call("_ZN4Aska16RenderableObjectC2Ev", {(u64)storage});
    }
    ~PrivateRenderable() { t.call("_ZN4Aska16RenderableObjectD1Ev", {(u64)storage}); }
    RenderableObject* operator->() { return reinterpret_cast<RenderableObject*>(storage); }
    RenderableObject* get() { return reinterpret_cast<RenderableObject*>(storage); }
};

bool vec_eq(const MathVector& a, const float (&b)[4]) { return std::memcmp(a.f, b, sizeof b) == 0; }

}  // namespace

// IAnimatable / Task / HierarchicalObjectContainer / HierarchicalObject / RenderableObject: a private
// RenderableObject (its constructor inlines every base's), its setters and getters through the guest,
// the scene-graph links through AttachChild / DetachFromParent / ChildObject.
NATIVE_TEST("render/layout-renderable-object") {
    PrivateRenderable a(t), b(t);
    RenderableObject* o = a.get();
    HierarchicalObject& ho = o->base;
    HierarchicalObjectContainer& hoc = ho.m_hoc;

    // The bases, as the constructor leaves them.
    t.expect_eq(ho.base.base.base.vtable, vtable_of(t, "_ZTVN4Aska16RenderableObjectE"), "vtable");
    t.expect_eq(hoc.vtable, vtable_of(t, "_ZTVN4Aska27HierarchicalObjectContainerE"), "the HOC base's vtable at 0x30");
    t.expect_eq(ho.base.m_manager, (TaskManager*)nullptr, "Task::m_manager");
    t.expect_eq(ho.base.base.m_next, (AnimatableLinkElement*)nullptr, "link next");
    // The constructor stores Task::GetDefaultLevel() (the Task part runs with Task's vtable), not the
    // derived class's slot 11.
    t.expect_eq((u64)ho.base.m_level, t.call("_ZNK4Aska4Task15GetDefaultLevelEv", {(u64)o}) & 0xffffffff, "m_level = Task::GetDefaultLevel()");
    t.expect_eq(vcall(o, 11) & 0xffffffff, (u64)0x4000, "slot 11 = RenderableObject::GetDefaultLevel");
    t.expect_eq(hoc.m_owner, (void*)o, "HOC owner");
    t.expect_eq(hoc.m_pWorld, &hoc.m_world, "HOC m_pWorld = &m_world");
    t.expect_eq(hoc.m_prevSibling, &hoc, "ring prev = self");
    t.expect_eq(hoc.m_nextSibling, &hoc, "ring next = self");
    t.expect_eq(hoc.m_parent, (HierarchicalObjectContainer*)nullptr, "no parent");
    t.expect_eq(hoc.m_firstChild, (HierarchicalObjectContainer*)nullptr, "no child");
    t.expect_eq(ho.m_onDestroy, (void (*)(HierarchicalObject*))nullptr, "m_onDestroy");
    t.expect_eq(ho.m_simpleDynamics, (void*)nullptr, "m_simpleDynamics");
    t.expect_eq(ho.m_active, (u8)1, "m_active");
    t.expect_eq((u32)o->m_shadowFlags[0] & 0xfd, (u32)0x40, "shadow flags at construction (0x40, bit 1 kept)");
    t.expect_eq(o->unk_1b7, (u8)3, "0x1b7 = 3");
    const float ident[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    t.expect_eq(vec_eq(hoc.m_scale, ident), true, "scale (1, 1, 1, 1)");
    t.expect_eq(o->m_angle2f8, 0.785398185f, "0x2f8 = pi/4");

    // The class id chain (GetClassID through the vtable) and IsThisIt.
    u64 id0 = vcall(o, 2, {0});
    t.expect_eq(t.call("_ZNK4Aska11IAnimatable8IsThisItEt", {(u64)o, id0 & 0xffff}) & 0xff, (u64)1, "IsThisIt(own id)");

    // HierarchicalObject getters / setters.
    t.expect_eq(t.call("_ZNK4Aska18HierarchicalObject11WorldMatrixEv", {(u64)o}), (u64)&hoc.m_world, "WorldMatrix() = &m_hoc.m_world");
    t.expect_eq(vcall(o, 19), (u64)&hoc.m_world, "slot 19 = WorldMatrix");
    const float pos[4] = {1.5f, -2.0f, 3.25f, 1.0f};
    t.call("_ZN4Aska18HierarchicalObject11SetPositionEPKNS_6VectorE", {(u64)o, (u64)pos});
    t.expect_eq(vec_eq(hoc.m_position, pos), true, "SetPosition -> m_hoc.m_position");
    alignas(16) float got[16] = {};
    t.expect_eq(t.call("_ZNK4Aska18HierarchicalObject3GetEmPv", {(u64)o, 5, (u64)got}) & 0xff, (u64)1, "Get(5)");
    t.expect_eq(std::memcmp(got, pos, sizeof pos), 0, "Get(5) = position");
    const float q[4] = {0.0f, 0.70710677f, 0.0f, 0.70710677f};
    t.call("_ZN4Aska18HierarchicalObject10SetPostureEPKNS_10QuaternionE", {(u64)o, (u64)q});
    t.expect_eq(vec_eq(*reinterpret_cast<MathVector*>(&hoc.m_posture), q), true, "SetPosture(Quaternion) -> m_posture");
    const float sc[4] = {2.0f, 3.0f, 4.0f, 1.0f};
    t.call("_ZN4Aska18HierarchicalObject8SetScaleEPKNS_6VectorE", {(u64)o, (u64)sc});
    t.expect_eq(vec_eq(hoc.m_scale, sc), true, "SetScale -> m_scale");
    const float p10[4] = {5.0f, 6.0f, 7.0f, 8.0f}, p11[4] = {9.0f, 10.0f, 11.0f, 12.0f};
    t.call("_ZN4Aska18HierarchicalObject3SetEmPKv", {(u64)o, 10, (u64)p10});
    t.call("_ZN4Aska18HierarchicalObject3SetEmPKv", {(u64)o, 11, (u64)p11});
    t.expect_eq(vec_eq(hoc.m_param10, p10), true, "Set(10) -> m_param10");
    t.expect_eq(vec_eq(hoc.m_param11, p11), true, "Set(11) -> m_param11");
    u8 active = 0xee;
    t.call("_ZNK4Aska18HierarchicalObject3GetEmPv", {(u64)o, 13, (u64)&active});
    t.expect_eq(active, ho.m_active, "Get(13) = m_active");
    u8 order = 0xee;
    t.call("_ZNK4Aska18HierarchicalObject3GetEmPv", {(u64)o, 8, (u64)&order});
    t.expect_eq((u32)order, (u32)(hoc.m_flags2 & 3), "Get(8) = m_hoc.m_flags2 & 3");

    // RenderableObject's own fields.
    const float cr[4] = {0.25f, 0.5f, 0.75f, 1.0f}, co[4] = {0.1f, 0.2f, 0.3f, 0.0f};
    t.call("_ZN4Aska16RenderableObject12SetColorRateEPKNS_6VectorE", {(u64)o, (u64)cr});
    t.call("_ZN4Aska16RenderableObject14SetColorOffsetEPKNS_6VectorE", {(u64)o, (u64)co});
    t.expect_eq(vec_eq(o->m_colorRate, cr), true, "SetColorRate -> m_colorRate");
    t.expect_eq(vec_eq(o->m_colorOffset, co), true, "SetColorOffset -> m_colorOffset");
    t.expect_eq(t.call("_ZNK4Aska16RenderableObject9ColorRateEv", {(u64)o}), (u64)&o->m_colorRate, "ColorRate()");
    t.expect_eq(t.call("_ZNK4Aska16RenderableObject17SystemColorOffsetEv", {(u64)o}), (u64)&o->m_colorOffset, "SystemColorOffset()");
    t.call("_ZN4Aska16RenderableObject16EnableCastShadowEb", {(u64)o, 1});
    t.expect_eq(o->m_shadowFlags[0] & 0x10, 0x10, "EnableCastShadow -> bit 4");
    t.call("_ZN4Aska16RenderableObject19EnableReceiveShadowEb", {(u64)o, 1});
    t.expect_eq(o->m_shadowFlags[0] & 0x20, 0x20, "EnableReceiveShadow -> bit 5");
    t.call("_ZN4Aska16RenderableObject22EnableReceiveProjectorEb", {(u64)o, 1});
    t.expect_eq(o->m_shadowFlags[0] & 0x80, 0x80, "EnableReceiveProjector -> bit 7");
    t.call("_ZN4Aska16RenderableObject8OnActiveEb", {(u64)o, 0});
    t.expect_eq(o->m_renderFlags & 0x2000u, 0x2000u, "OnActive(false) -> m_renderFlags bit 13");
    t.call("_ZN4Aska16RenderableObject8OnActiveEb", {(u64)o, 1});
    t.expect_eq(o->m_renderFlags & 0x2000u, 0u, "OnActive(true)");
    t.call("_ZN4Aska16RenderableObject22EnableObjectMotionBlurEb", {(u64)o, 1});
    t.expect_eq(o->m_renderFlags & 0x4000000u, 0x4000000u, "EnableObjectMotionBlur -> bit 26");
    t.call("_ZN4Aska16RenderableObject27SetProgrammableTransparencyENS0_9ProgTransE", {(u64)o, 2});
    t.expect_eq(o->m_progTrans, (u8)2, "SetProgrammableTransparency -> m_progTrans");
    t.call("_ZN4Aska16RenderableObject22SetIBLAcceptanceNumberEj", {(u64)o, 7});
    t.expect_eq(o->m_iblAcceptance, (u8)7, "SetIBLAcceptanceNumber");
    const u64 ids[2] = {0x1122334455667788ull, 0x99aabbccddeeff00ull};
    t.call("_ZN4Aska16RenderableObject23SetMultipassRenderingIDEPKmi", {(u64)o, (u64)ids, 2});
    t.call("_ZN4Aska16RenderableObject30SetMultipassRequestRenderingIDEPKmi", {(u64)o, (u64)ids, 1});
    t.expect_eq(o->m_multipassRenderingID[1], ids[1], "SetMultipassRenderingID");
    t.expect_eq(o->m_multipassRequestRenderingID[0], ids[0], "SetMultipassRequestRenderingID");
    o->m_multiDraw = 5;
    t.call("_ZN4Aska16RenderableObject19UpdateMultiDrawVarsEv", {(u64)o});
    t.expect_eq(o->m_multiDraw, (u32)0, "UpdateMultiDrawVars -> m_multiDraw = 0");
    t.expect_eq(vcall(o, 41), (u64)&o->m_boundingSphere, "VirtualBoundingSphere = &m_boundingSphere");
    const float* def = at_vaddr<float>(kVaddrDefaultSphere);
    t.expect_eq(std::memcmp(o->m_boundingSphere.f, def, 16), 0, "bounding sphere = m_vDefaultSphere (ComputeBoundingSphere)");

    // The scene graph: b under a, then detached.
    HierarchicalObjectContainer& bh = b->base.m_hoc;
    t.call("_ZN4Aska27HierarchicalObjectContainer11AttachChildEPS0_", {(u64)&hoc, (u64)&bh});
    t.expect_eq(bh.m_parent, &hoc, "AttachChild: child's m_parent");
    t.expect_eq(hoc.m_firstChild, &bh, "AttachChild: parent's m_firstChild");
    t.expect_eq((s32)t.call("_ZNK4Aska27HierarchicalObjectContainer19GetChildObjectCountEv", {(u64)&hoc}), 1, "GetChildObjectCount");
    t.expect_eq(t.call("_ZNK4Aska27HierarchicalObjectContainer11ChildObjectEi", {(u64)&hoc, 0}), (u64)&bh, "ChildObject(0)");
    t.call("_ZN4Aska27HierarchicalObjectContainer16DetachFromParentEv", {(u64)&bh});
    t.expect_eq(bh.m_parent, (HierarchicalObjectContainer*)nullptr, "DetachFromParent: m_parent");
    t.expect_eq(hoc.m_firstChild, (HierarchicalObjectContainer*)nullptr, "DetachFromParent: parent's m_firstChild");
    t.expect_eq(bh.m_nextSibling, &bh, "DetachFromParent: ring = self");
}

}  // namespace soa::native::render
