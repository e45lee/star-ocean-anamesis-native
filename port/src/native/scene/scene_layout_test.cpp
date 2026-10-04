// Layout tests for scene_layout.h (port/PLAN.md task 6, types first): the recovered classes read against the
// running game's objects at a frame boundary (render::testutil::on_frame: the body runs on the game
// thread inside Aska::ObjectManager::OnPrePaint, before that frame's jobs are dispatched), compared with
// the guest's own getters (t.call / vcall: natives are not installed in --selftest) and with the
// invariants the decompiles show. The model tests need models on screen: at the title they skip with a
// note; port/scripts/selftest_live.sh SOA OUT TMP scene/ --at home runs them on the home screen's
// character. No natives here.
#include <cstdio>
#include <cstring>

#include "native/common/test.h"
#include "native/render/render_test_util.h"
#include "native/scene/scene_layout.h"

namespace soa::native::scene {
namespace {

using namespace render::testutil;

// The class id (the low u16 of GetClassID(0)) of the class whose GetClassID is `sym`.
u16 class_id(TestContext& t, const char* sym) { return (u16)(t.call(sym, {0, 0}) & 0xffff); }
bool is_a(TestContext& t, const void* obj, u16 id) {
    return t.call("_ZNK4Aska11IAnimatable8IsThisItEt", {(u64)obj, (u64)id}) & 1;
}

ObjectManager* object_manager() { return global_ptr<ObjectManager>(render::kVaddrGlobalObjectManager); }

// The AofObjects among this frame's painting candidates (at most `max`).
int aof_candidates(TestContext& t, AofObject** out, int max) {
    ObjectManager* om = object_manager();
    u16 aof = class_id(t, "_ZNK4Aska9AofObject10GetClassIDEi");
    int n = 0;
    for (int i = 0; i < om->m_candidateCount && n < max; i++)
        if (is_a(t, om->m_candidates[i], aof)) out[n++] = reinterpret_cast<AofObject*>(om->m_candidates[i]);
    return n;
}

}  // namespace

// ObjectManager (and the kernel TaskManager part it starts with): the objects it owns, by their vtables
// and its guest getters.
NATIVE_TEST("scene/layout-object-manager") {
    on_frame(t, [&] {
        ObjectManager* om = object_manager();
        if (!t.expect_eq(has_vtable(t, om, "_ZTVN4Aska13ObjectManagerE"), true, "ObjectManager vtable")) return;
        t.expect_eq(om->base.m_task.base.base.vtable, (const void*)(t.sym("_ZTVN4Aska13ObjectManagerE") + 0xb0),
                    "the Task base's vptr at 0x28 (vtable + 0xb0)");
        t.expect_eq(has_vtable(t, om->m_renderThread, "_ZTVN4Aska12RenderThreadE"), true, "m_renderThread");
        t.expect_eq(has_vtable(t, om->m_renderContextServer, "_ZTVN4Aska19RenderContextServerE"), true, "m_renderContextServer");
        t.expect_eq(has_vtable(t, om->m_filterTextureObject, "_ZTVN4Aska19FilterTextureObjectE"), true, "m_filterTextureObject");
        t.expect_eq(has_vtable(t, om->m_depthTextureObject, "_ZTVN4Aska18DepthTextureObjectE"), true, "m_depthTextureObject");
        t.expect_eq(has_vtable(t, om->m_msaaChanger[0], "_ZTVN4Aska17MSAAChangerObjectE"), true, "m_msaaChanger[0]");
        t.expect_eq(has_vtable(t, om->m_msaaChanger[1], "_ZTVN4Aska17MSAAChangerObjectE"), true, "m_msaaChanger[1]");
        t.expect_eq(has_vtable(t, om->m_postProcessCombiner, "_ZTVN4Aska22PostProcessCombinerTBRE"), true, "m_postProcessCombiner");
        t.expect_eq(has_vtable(t, om->m_postProcessBufferManager, "_ZTVN4Aska24PostProcessBufferManagerE"), true,
                    "m_postProcessBufferManager");
        t.expect_eq(has_vtable(t, om->m_proceduralTextureManager, "_ZTVN4Aska24ProceduralTextureManagerE"), true,
                    "m_proceduralTextureManager");
        t.expect_eq(has_vtable(t, om->m_shadowManagerRegistry, "_ZTVN4Aska21ShadowManagerRegistryE"), true,
                    "m_shadowManagerRegistry");
        t.expect_eq(has_vtable(t, om->m_freezeRenderingTask, "_ZTVN4Aska19FreezeRenderingTaskE"), true, "m_freezeRenderingTask");
        // The constructor's system objects: the filter, depth, post-process buffer manager first.
        t.expect_eq(om->m_systemObjectCount >= 3 && om->m_systemObjectCount <= 0x20, true, "m_systemObjectCount");
        t.expect_eq(om->m_systemObjects[0], om->m_filterTextureObject, "m_systemObjects[0] = the filter texture object");
        t.expect_eq(om->m_systemObjects[1], om->m_depthTextureObject, "m_systemObjects[1] = the depth texture object");
        t.expect_eq(om->m_systemObjects[2], om->m_postProcessBufferManager, "m_systemObjects[2] = the buffer manager");
        // Getters through the pointers recovered here.
        t.expect_eq(t.call("_ZNK4Aska13ObjectManager12GetNoTextureEv", {(u64)om}),
                    *reinterpret_cast<u64*>(reinterpret_cast<u8*>(om->m_renderThread) + 0x501e8), "GetNoTexture (via m_renderThread)");
        GuestResult r = guest_call(t.sym("_ZNK4Aska13ObjectManager10GetSceneEVEi"), GuestArgs().i((u64)om).i(0));
        float ev0;
        std::memcpy(&ev0, &r.v0, 4);
        float want;
        std::memcpy(&want, reinterpret_cast<u8*>(om->m_postProcessCombiner) + 0x488, 4);
        t.expect_eq(ev0, want, "GetSceneEV(0) reads m_postProcessCombiner");
        for (int i = 0; i < 0x80; i++) {
            if (!(om->m_multipassEnv[i].m_flags & 0x20)) continue;
            GuestResult ri = guest_call(t.sym("_ZNK4Aska13ObjectManager10GetSceneEVEi"), GuestArgs().i((u64)om).i((u64)(i + 1)));
            float got, exp;
            std::memcpy(&got, &ri.v0, 4);
            std::memcpy(&exp, reinterpret_cast<u8*>(om->m_multipassEnv[i].m_combiner) + 0x488, 4);
            t.expect_eq(got, exp, "GetSceneEV(i + 1) reads m_multipassEnv[i].m_combiner");
        }
        // The painting candidates (Prerender's culling filled them before OnPrePaint): all renderables.
        u16 renderable = class_id(t, "_ZNK4Aska16RenderableObject10GetClassIDEi");
        t.expect_eq(om->m_candidateCount > 0 && om->m_candidateCount <= 4096, true, "m_candidateCount (OnPrePaint runs on > 0)");
        int bad = 0;
        for (int i = 0; i < om->m_candidateCount; i++)
            if (!is_a(t, om->m_candidates[i], renderable)) bad++;
        t.expect_eq(bad, 0, "every m_candidates[i] is a RenderableObject");
        t.expect_eq(om->m_enabled, (u8)1, "m_enabled (OnPrePaint ran this far)");
        t.expect_eq(om->m_frozen, (u8)0, "m_frozen");
        t.expect_eq(om->m_resultBitsCapacity >= 0, true, "m_resultBitsCapacity");
        std::fprintf(stderr, "scene/layout-object-manager: %d candidates, %d system objects, %d passes\n",
                     om->m_candidateCount, om->m_systemObjectCount, om->m_passCount);
    });
}

// ObjectManagerJobDispatcher and its ObjectManagerWorkerThread(s), between two frames (idle).
NATIVE_TEST("scene/layout-job-dispatcher") {
    on_frame(t, [&] {
        auto* d = global_ptr<ObjectManagerJobDispatcher>(render::kVaddrGlobalObjectManagerJobDispatcher);
        if (!t.expect_eq(has_vtable(t, d, "_ZTVN4Aska26ObjectManagerJobDispatcherE"), true, "dispatcher vtable")) return;
        t.expect_eq(d->m_objectManager, object_manager(), "m_objectManager");
        t.expect_eq(d->m_workerCount, 1, "m_workerCount (Global::InstantiateObjectManagerJobDispatcher: 1)");
        t.expect_eq(*reinterpret_cast<const u64*>(reinterpret_cast<const u8*>(d->m_workers) - 8), (u64)d->m_workerCount,
                    "operator new[] count before m_workers");
        t.expect_eq(d->m_exceptIndex, -1, "m_exceptIndex");
        t.expect_eq(d->m_unkB0, 0x80, "0xb0 = 0x80 (constructor)");
        for (int i = 0; i < d->m_workerCount; i++) {
            ObjectManagerWorkerThread& w = d->m_workers[i];
            t.expect_eq(has_vtable(t, &w, "_ZTVN4Aska25ObjectManagerWorkerThreadE"), true, "worker vtable");
            t.expect_eq(w.m_dispatcher, d, "worker m_dispatcher");
            t.expect_eq(w.m_objectManager, object_manager(), "worker m_objectManager");
            t.expect_eq(w.m_running, (u8)1, "worker m_running");
            t.expect_eq(w.m_exit, (u8)0, "worker m_exit");
            t.expect_eq(w.m_mode >= 1 && w.m_mode <= 7, true, "worker m_mode is a job mode");
            t.expect_eq(w.m_nextMode == -1 || (w.m_nextMode >= 1 && w.m_nextMode <= 7), true, "worker m_nextMode");
            // Between frames the dispatcher's Sleep left the worker idle (mode 7) with no job.
            t.expect_eq(w.m_job, 0, "worker m_job (idle between frames)");
            // The lock word of its FastCriticalSection: -1 when free (the sync layout: + 0x38).
            s32 lockword;
            std::memcpy(&lockword, w.m_lock + 0x38, 4);
            t.expect_eq(lockword == -1 || lockword == 0, true, "worker m_lock's word (-1 free / 0 held)");
            t.expect_eq(w.m_resultBits, object_manager()->m_resultBits, "worker m_resultBits = the object manager's");
            // Dispatch_RenderingDecided-free check of the job parameters set last frame: they point into
            // the object manager's candidate array.
            if (w.m_prelimObjects)
                t.expect_eq(w.m_prelimObjects >= object_manager()->m_candidates &&
                                w.m_prelimObjects < object_manager()->m_candidates + 4096,
                            true, "worker m_prelimObjects points into m_candidates");
        }
    });
}

// AofObject / AofObjectRenderState / AofHandler on the frame's models (the title: the DirectAof UI, if any).
NATIVE_TEST("scene/layout-aof-object") {
    on_frame(t, [&] {
        AofObject* objs[256];
        int n = aof_candidates(t, objs, 256);
        if (n == 0) {
            std::fprintf(stderr, "scene/layout-aof-object: no AofObject among the candidates (skipped)\n");
            return;
        }
        int handlers = 0, states = 0;
        for (int k = 0; k < n; k++) {
            AofObject* o = objs[k];
            t.expect_eq(t.call("_ZNK4Aska9AofObject9ColorRateEv", {(u64)o}), (u64)&o->m_colorRate, "ColorRate()");
            t.expect_eq(t.call("_ZNK4Aska9AofObject11ColorOffsetEv", {(u64)o}), (u64)&o->m_colorOffset, "ColorOffset()");
            t.expect_eq(t.call("_ZNK4Aska9AofObject15SystemColorRateEv", {(u64)o}), (u64)&o->m_systemColorRate, "SystemColorRate()");
            t.expect_eq(t.call("_ZNK4Aska9AofObject17SystemColorOffsetEv", {(u64)o}), (u64)&o->m_systemColorOffset,
                        "SystemColorOffset()");
            t.expect_eq(t.call("_ZNK4Aska9AofObject14HasBoundingBoxEv", {(u64)o}) & 1, (u64)((o->m_flags >> 7) & 1),
                        "HasBoundingBox = m_flags bit 7");
            int q = (o->m_prebuiltVariation[0] == 2 ? 2 : 1) * (o->m_prebuiltVariation[1] == 2 ? 2 : 1) *
                    (o->m_prebuiltVariation[2] == 2 ? 2 : 1);
            t.expect_eq((s32)t.call("_ZNK4Aska9AofObject22QueryPrebuiltVariationEv", {(u64)o}), q, "QueryPrebuiltVariation");
            if (o->m_lightConfiguration != -1)
                t.expect_eq((s32)t.call("_ZNK4Aska9AofObject27GetActualLightConfigurationEv", {(u64)o}),
                            (s32)o->m_lightConfiguration, "GetActualLightConfiguration = m_lightConfiguration");
            t.expect_eq(o->m_renderStateCount <= o->m_renderStateCapacity, true, "render states: count <= capacity");
            // GetObjectRenderState(kind) finds the existing state of each kind (no append).
            AofObjectRenderState* arr = o->m_renderStates ? o->m_renderStates : o->m_inlineRenderStates;
            u16 count = o->m_renderStateCount;
            for (u16 i = 0; i < count; i++) {
                u64 got = t.call("_ZN4Aska9AofObject20GetObjectRenderStateEj", {(u64)o, arr[i].m_passKind});
                t.expect_eq(got, (u64)&arr[i], "GetObjectRenderState(kind) = the state of that kind");
                states++;
            }
            t.expect_eq(o->m_renderStateCount, count, "GetObjectRenderState appended nothing");
            if (o->m_handler) {
                handlers++;
                u64 direct = vcall(o->m_handler, 6) & 1;  // IsDirectAof
                if (has_vtable(t, o->m_handler, "_ZTVN4Aska10AofHandlerE")) {
                    u64 zt = t.sym("_ZTVN4Aska10AofHandlerE");
                    t.expect_eq(o->m_handler->vtable2, (const void*)(zt + 0x90), "AofHandler vtable2 (0x98)");
                    t.expect_eq(o->m_handler->vtable3, (const void*)(zt + 0xb8), "AofHandler vtable3 (0xa0)");
                    t.expect_eq(direct, (u64)0, "AofHandler::IsDirectAof");
                }
                t.expect_eq((u64)o->m_handler->m_materials, (u64)o->m_handler + 0xe8, "the MaterialList at 0xe8");
            }
        }
        std::fprintf(stderr, "scene/layout-aof-object: %d AofObjects, %d with handlers, %d render states checked\n", n,
                     handlers, states);
    });
}

// SkinMatricesBase / SkinMatrices / JointObject on the skinned models of the frame (none at the title:
// skipped; selftest_live.sh --at home: the home screen's character).
NATIVE_TEST("scene/layout-skinning") {
    on_frame(t, [&] {
        AofObject* objs[256];
        int n = aof_candidates(t, objs, 256);
        u16 hobj = class_id(t, "_ZNK4Aska18HierarchicalObject10GetClassIDEi");
        int skinned = 0, bones = 0, joints = 0;
        for (int k = 0; k < n; k++) {
            AofObject* o = objs[k];
            SkinMatricesBase* sm = o->m_skinMatrices;
            if (!sm) continue;
            skinned++;
            t.expect_eq(sm->m_object, o, "SkinMatricesBase::m_object = its AofObject");
            t.expect_eq(o->base.m_renderFlags & 0x200u, 0x200u, "a skinned AofObject's m_renderFlags bit 9");
            t.expect_eq(sm->m_flags & 1, 1, "SkinMatricesBase initialized (m_flags bit 0)");
            t.expect_eq(sm->m_bindPose, o->m_handler->m_bindPose, "m_bindPose = the handler's (Init)");
            if (!has_vtable(t, sm, "_ZTVN4Aska12SkinMatricesE")) continue;
            auto* s = reinterpret_cast<SkinMatrices*>(sm);
            for (u32 i = 0; i < sm->m_boneCount; i++) {
                u64 got = t.call("_ZNK4Aska12SkinMatrices13GetBoneObjectEj", {(u64)s, i});
                t.expect_eq(got, (u64)s->m_bones[i], "GetBoneObject(i) = m_bones[i]");
                HierarchicalObject* b = s->m_bones[i];
                if (!b) continue;
                bones++;
                t.expect_eq(is_a(t, b, hobj), true, "a bone is a HierarchicalObject");
                if (has_vtable(t, b, "_ZTVN4Aska11JointObjectE")) {
                    joints++;
                    auto* j = reinterpret_cast<JointObject*>(b);
                    float q[4] = {};
                    t.expect_eq(t.call("_ZNK4Aska11JointObject3GetEmPv", {(u64)j, 15, (u64)q}) & 1, (u64)1, "JointObject::Get(15)");
                    t.expect_eq(std::memcmp(q, &j->base.m_hoc.m_vec90, 16), 0, "Get(15) = the joint orientation (m_hoc 0x90)");
                    t.expect_eq(j->m_noParentScale <= 1, true, "JointObject::m_noParentScale is a bool");
                }
            }
            t.expect_eq(t.call("_ZNK4Aska12SkinMatrices13GetBoneObjectEj", {(u64)s, (u64)sm->m_boneCount + 1}), (u64)0,
                        "GetBoneObject(past m_boneCount) = null");
        }
        if (skinned == 0)
            std::fprintf(stderr, "scene/layout-skinning: no skinned AofObject on screen (skipped; selftest_live.sh --at home)\n");
        else
            std::fprintf(stderr, "scene/layout-skinning: %d skinned AofObjects, %d bones (%d JointObjects)\n", skinned, bones, joints);
    });
}

}  // namespace soa::native::scene
