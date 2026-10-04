// Layout tests for render_layout.h (port/PLAN.md task 6, types first): the recovered classes read against
// real guest objects. A test either builds a private object with the guest's own constructor and drives
// it with the guest's methods (t.call / vcall: natives are not installed in --selftest), then reads the
// fields through the layout classes, or walks the running game's objects at a frame boundary
// (testutil::on_frame) and compares their fields with the guest's getters. No natives here.
#include <cstring>
#include <memory>
#include <set>
#include <vector>

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

// The frame hook itself (testutil::on_frame, which the live layout tests of render, scene and anim use):
// the body runs on the game thread inside Aska::ObjectManager::OnPrePaint, where the globals are set.
NATIVE_TEST("render/layout-frame-hook") {
    void* om_seen = nullptr;
    bool ran = on_frame(t, [&] {
        om_seen = global_ptr<void>(kVaddrGlobalObjectManager);
        t.expect_eq(has_vtable(t, om_seen, "_ZTVN4Aska13ObjectManagerE"), true, "Global::m_pObjectManager's vtable");
        t.expect_eq(global_ptr<void>(kVaddrGlobalCameraManager) != nullptr, true, "Global::m_pCameraManager");
        t.expect_eq(global_ptr<void>(kVaddrGlobalLightManager) != nullptr, true, "Global::m_pLightManager");
        t.expect_eq(global_ptr<void>(kVaddrRenderDev) != nullptr, true, "g_pRenderDev");
    });
    t.expect_eq(ran, true, "on_frame ran");
    t.expect_eq(om_seen != nullptr, true, "an ObjectManager");
}

// ---- The device section ----------------------------------------------------------------------------

// ShaderComprssionTree: a private tree (host memory) built by the guest's constructor, filled through
// InsertNode on a window of few distinct words (many matches); after every insert m_matchLen must be the
// brute-force longest match among the positions still in the tree (with the same first word), and every
// node's parent must link back to it (m_left / m_right, or the root slot m_right[0x1001 + word]).
// Then a CompressLZwordDic -> DecompressLZwordDic round trip (the codec the tree serves).
NATIVE_TEST("render/layout-shader-compression") {
    auto mem = std::make_unique<ShaderComprssionTree>();
    ShaderComprssionTree* tr = mem.get();
    std::memset(tr, 0x5a, sizeof *tr);
    t.call("_ZN4Aska20ShaderComprssionTreeC2Ev", {(u64)tr});
    bool init_ok = true;
    for (int i = 0; i < 0x1000; i++) init_ok &= tr->m_parent[i] == ShaderComprssionTree::kNil;
    for (int w = 0; w < 0x10000; w++) init_ok &= tr->m_right[0x1001 + w] == ShaderComprssionTree::kNil;
    t.expect_eq(init_ok, true, "constructor: every parent and root NIL");
    const int kN = 600, kLen = ShaderComprssionTree::kMaxMatch;
    for (int i = 0; i < 0x1000; i++) tr->m_text[i] = (s32)(t.rand_int(0, 2));
    std::set<int> in;
    int bad_len = 0, bad_link = 0;
    for (int r = 0; r < kN; r++) {
        t.call("_ZN4Aska20ShaderComprssionTree10InsertNodeEii", {(u64)tr, (u64)r, (u64)kLen});
        int best = 0;
        for (int p : in) {
            if (tr->m_text[p & 0xfff] != tr->m_text[r & 0xfff]) continue;
            int k = 1;
            while (k < kLen && tr->m_text[(p + k) & 0xfff] == tr->m_text[(r + k) & 0xfff]) k++;
            best = std::max(best, k);
        }
        if (tr->m_matchLen != best) bad_len++;
        if (best == kLen) in.erase(tr->m_matchPos);  // a full match replaces the old node
        in.insert(r);
        for (int p : in) {
            int par = tr->m_parent[p];
            bool linked = par == ShaderComprssionTree::kNil ? false
                          : (par > 0x1000 ? tr->m_right[par] == p : (tr->m_left[par] == p || tr->m_right[par] == p));
            if (!linked) bad_link++;
        }
    }
    t.expect_eq(bad_len, 0, "InsertNode: m_matchLen = the longest match");
    t.expect_eq(bad_link, 0, "m_parent / m_left / m_right / the root slots link up");
    t.call("_ZN4Aska20ShaderComprssionTree10DeleteNodeEi", {(u64)tr, (u64)(kN - 1)});
    t.expect_eq(tr->m_parent[kN - 1], ShaderComprssionTree::kNil, "DeleteNode -> m_parent = NIL");

    std::vector<u8> dic(0x2000), src(0x1000), packed(0x4000, 0), out(0x1000 + 0x40, 0);
    for (auto& b : dic) b = (u8)t.rand_int(0, 255);
    for (size_t i = 0; i < src.size(); i++) src[i] = (u8)(i % 7 == 0 ? t.rand_int(0, 255) : "shader cache words"[i % 18]);
    s32 n = (s32)t.call("_ZN4Aska17ShaderCompression17CompressLZwordDicEPviS1_Ph", {(u64)src.data(), src.size(), (u64)packed.data(), (u64)dic.data()});
    t.expect_eq(n > 0 && n < (s32)src.size(), true, "CompressLZwordDic compresses");
    t.call("_ZN4Aska17ShaderCompression19DecompressLZwordDicEPtS1_Ph", {(u64)packed.data(), (u64)out.data(), (u64)dic.data()});
    t.expect_eq(std::memcmp(out.data(), src.data(), src.size()), 0, "DecompressLZwordDic round trip");
}

namespace {
TEST_PROBE(g_probeAddRenderQueue, "_ZN4Aska12RenderThread14AddRenderQueueEPNS_16RenderableObjectEPNS_13RenderContextEi");
TEST_PROBE(g_probeGetRenderBatch, "_ZN4Aska19RenderContextServer14GetRenderBatchEi");
}  // namespace

// RenderThread and its queue: two consecutive AddRenderQueue calls (on the painting thread); the entry
// the first one wrote (at the m_write it saw) must hold its arguments (type 0, object, context, pass)
// when the second comes, and m_write must have moved on. The sync members and helper threads by vtable.
NATIVE_TEST("render/layout-render-thread") {
    struct Seen { RenderThread* rt = nullptr; s32 write = -1; u64 obj = 0, ctx = 0, pass = 0; } first;
    int calls = 0;
    probe_call(t, g_probeAddRenderQueue, [&](Cpu& c) {
        auto* rt = reinterpret_cast<RenderThread*>(c.x(0));
        if (calls++ == 0) {
            first = {rt, rt->m_queue.m_write, c.x(1), c.x(2), (u64)(s64)(s32)c.x(3)};
            return false;  // stay armed for the next call
        }
        t.expect_eq(rt, first.rt, "one RenderThread");
        t.expect_eq(rt->vtable, vtable_of(t, "_ZTVN4Aska12RenderThreadE"), "RenderThread vtable");
        t.expect_eq(vslot(rt, 2), t.sym("_ZN4Aska12RenderThread7HandlerEv"), "slot 2 = Handler");
        t.expect_eq(rt->m_queue.vtable, vtable_of(t, "_ZTVN4Aska6TQueueINS_14RENDER_REQUESTELi8192EEE"), "m_queue's vtable (0x198)");
        t.expect_eq(has_vtable(t, rt->m_finishCallbackThread, "_ZTVN4Aska26RenderFinishCallbackThreadE"), true, "m_finishCallbackThread");
        t.expect_eq(has_vtable(t, rt->m_callbackThread, "_ZTVN4Aska26RenderThreadCallBackThreadE"), true, "m_callbackThread");
        t.expect_eq(rt->m_blankTexture != nullptr, true, "m_blankTexture");
        t.expect_eq(rt->m_initialized, (u8)1, "m_initialized (Handler_Init ran)");
        t.expect_eq(first.write >= 0 && first.write <= 0x2000, true, "m_write in the ring");
        const RENDER_REQUEST& e = rt->m_queue.m_entries[first.write];
        t.expect_eq(e.m_type, (u8)0, "the first call's entry: type 0");
        t.expect_eq(e.m_arg[0], first.obj, "entry: the object");
        t.expect_eq(e.m_arg[1], first.ctx, "entry: the RenderContext");
        t.expect_eq(e.m_arg[2], first.pass, "entry: the pass (sign-extended)");
        t.expect_eq(rt->m_queue.m_write, first.write == 0x2000 ? 0 : first.write + 1, "m_write advanced by one");
        u8 st = (u8)t.call("_ZNK4Aska12RenderThread9GetStatusEv", {(u64)rt});
        t.expect_eq(st <= 3, true, "GetStatus (m_status under m_queueLock)");
        return true;
    }, 20000, "RenderThread::AddRenderQueue");
}

// RenderContextServer: on a GetRenderBatch call (a worker preparing an object). The arrays are new[]s
// with the element count in the cookie at -8 (RenderContext, RenderContextBatch); the light contexts
// are one new[] split in two buffers.
NATIVE_TEST("render/layout-render-context-server") {
    probe_call(t, g_probeGetRenderBatch, [&](Cpu& c) {
        auto* sv = reinterpret_cast<RenderContextServer*>(c.x(0));
        t.expect_eq(sv->vtable, vtable_of(t, "_ZTVN4Aska19RenderContextServerE"), "vtable");
        t.expect_eq(sv->m_contexts != nullptr && sv->m_contextCount > 0, true, "m_contexts");
        t.expect_eq(reinterpret_cast<const u64*>(sv->m_contexts)[-1], (u64)sv->m_contextCount, "RenderContext new[] cookie = m_contextCount");
        t.expect_eq(reinterpret_cast<const u64*>(sv->m_batches)[-1], (u64)sv->m_batchCount, "RenderContextBatch new[] cookie = m_batchCount");
        t.expect_eq((u64)sv->m_lightContexts[1] - (u64)sv->m_lightContexts[0], (u64)sv->m_lightContextCount * kLightContextSize,
                    "m_lightContexts[1] = [0] + count");
        t.expect_eq(sv->m_bufferIndex <= 1, true, "m_bufferIndex");
        t.expect_eq((u64)sv->m_contextUsed <= (u64)sv->m_contextCount, true, "m_contextUsed <= m_contextCount");
        return true;
    }, 20000, "RenderContextServer::GetRenderBatch");
}
}  // namespace soa::native::render
