// scene_layout.h: the guest data layouts of the `scene` subsystem (the object manager, AOF models, skinning, the framework's models).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/scene/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types scene` turns the structs into port/decomp/scene/types.json for Ghidra.
#ifndef SOA_NATIVE_SCENE_LAYOUT_H
#define SOA_NATIVE_SCENE_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../render/render_layout.h"

namespace soa::native::scene {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// The render subsystem's classes this one builds on (render_layout.h: the hierarchy's bases).
using render::MathMatrix;
using render::MathVector;
using render::RenderableObject;
using render::HierarchicalObject;
using render::HierarchicalObjectContainer;
using render::Camera;
using render::Light;
using render::LightManager;
using render::RenderContext;
using render::RENDERINFO;

// Not recovered yet (render's / anim's / resource's; pointers only here).
class RenderPass;            // Aska::RenderPass (render)
class RenderThread;          // Aska::RenderThread (render): ObjectManager::m_renderThread
class RenderContextServer;   // Aska::RenderContextServer (render)
class RenderLayer;           // Aska::RenderLayer (render): 0x110 bytes
class RenderPassManager;     // Aska::RenderPassManager (render)
class AsfHandler;            // Aska::AsfHandler (scene, not typed yet)

class ObjectManager;
class ObjectManagerJobDispatcher;
class AofObject;
class AofHandler;
class SkinMatricesBase;

// ---- The kernel's classes the object manager is built from (opaque-ish; kernel types them) -------

// Aska::TaskManager: the kernel's per-frame task list (ObjectManager and ShadowManagerRegistry derive
// from it). Data size 0xff0; layout from TaskManager::TaskManager (work/decomp, kernel's) and
// TaskManager::Add (its FastCriticalSection at 0xf60: the lock word at 0xf98). An AnimatableList (a vptr
// and a sentinel AnimatableLinkElement), then a Task (the second base, its own vptr) at 0x28: that Task is
// what the owner task manager runs (ObjectManager::OnPrePaint / OnPaint / OnPostPaint are reached through
// it, TaskManager::OwnersKickTask). Kept here, in scene, until kernel's layout header has it.
class TaskManagerBase {
public:
    const void* vtable;                    // 0x000: the AnimatableList / derived class's vtable
    render::AnimatableLinkElement m_list;  // 0x008: the task list's sentinel (links = self when empty)
    u32 m_count;                           // 0x020
    u8 unk_024[4];                         // 0x024
    render::Task m_task;                   // 0x028: the second base (vptr = the derived vtable + 0xa0 / 0xb0)
    u8 unk_050[0x80];                      // 0x050: zeroed by the constructor
    u8 unk_0d0[0x60];                      // 0x0d0
    u8 unk_130[32][0x68];                  // 0x130: 32 Aska::Event (sync's, 0x68 each)
    u8 unk_e30[0x108];                     // 0xe30: zeroed by the constructor
    u8 m_criticalSection[0x28];            // 0xf38: Aska::CriticalSection (sync)
    u8 m_fastCriticalSection[0x90];        // 0xf60: Aska::FastCriticalSection (sync; lock word at 0xf98)
};
static_assert(offsetof(TaskManagerBase, m_list) == 0x008);
static_assert(offsetof(TaskManagerBase, m_count) == 0x020);
static_assert(offsetof(TaskManagerBase, m_task) == 0x028);
static_assert(offsetof(TaskManagerBase, m_criticalSection) == 0xf38);
static_assert(offsetof(TaskManagerBase, m_fastCriticalSection) == 0xf60);
static_assert(sizeof(TaskManagerBase) == 0xff0);

// ---- The object manager's job system ---------------------------------------------------------------

// The worker modes / job ids (ObjectManagerWorkerThread::Handler's switch; a worker in mode M takes only
// job M; the dispatcher's ChangeMode switches every worker).
enum ObjectManagerJob : s32 {
    kJobNone = 0,
    kJobMakePaintingList = 1,       // Handler_MakePaintingList: ObjectManager::MakePaintingList* (kind m_paintingListKind)
    kJobPreliminarilyPrepare = 2,   // Handler_PreliminarilyPrepare (inlined in Handler): RenderableObject slot 79
    kJobPrepareForRendering = 3,    // Handler_PrepareForRendering: RenderableObject slot 80 over a batch
    kJobViewFrustumCulling = 4,     // Handler_ViewFrustumCulling: (Sub)ViewFrustumCulling / OcclusionCulling
    kJobDetectLIBL = 5,             // Handler_DetectLIBL (inlined): ObjectManager::DetectLIBL
    kJobResetSystemFlags = 6,       // Handler_ResetSystemFlags: the per-frame reset of a range of objects
    kJobIdle = 7,                   // waits on m_event; m_exit ends the thread
};

// Aska::ObjectManagerWorkerThread: one worker of the object manager's job dispatcher. Guest size 0x210
// (the dispatcher's operator new[](n * 0x210 + 8) and its inlined constructors); layout from the
// constructor, Handler, the Handler_* jobs, ChangeMode and the dispatcher's Dispatch_* / Set*Parameter
// (port/decomp/scene/object_manager.c). A job is posted by the dispatcher: it checks m_running,
// m_waiting, !m_modeChangePending, m_job == 0 and m_mode == job, stores the job's parameters, sets
// m_waiting = 0 and m_job = job, then sets m_event. The worker clears m_job when done (the dispatcher
// polls it). ChangeMode(m) takes m_lock (a FastCriticalSection: spin 0x1ff tries, then its semaphore),
// sets m_nextMode / m_modeChangePending and wakes the worker, which adopts it at its next loop.
// vtable (_ZTVN4Aska25ObjectManagerWorkerThreadE): 0 D1, 1 D0, 2 Handler (the thread body).
class ObjectManagerWorkerThread {
public:
    void CtorBase();
    void Dtor();
    void DtorDelete();
    void Handler();  // slot 2
    void Initialize(s32);
    void Handler_MakePaintingList();
    void Handler_PreliminarilyPrepare();
    void Handler_PrepareForRendering();
    void Handler_ViewFrustumCulling();
    void Handler_DetectLIBL();
    void Handler_ResetSystemFlags();
    void ChangeMode(s32);

    u8 base_thread[0x18];                    // 0x000: Aska::Thread (sync; vptr = _ZTVN4Aska25ObjectManagerWorkerThreadE + 0x10)
    u8 m_event[0x68];                        // 0x018: Aska::Event (sync): a job or a mode change was posted
    u8 m_lock[0x90];                         // 0x080: Aska::FastCriticalSection (sync): lock word at 0xb8 (-1 free), waiters 0xbc, semaphore 0xf8
    s32 m_mode;                              // 0x110: the current mode (ObjectManagerJob); 7 at construction
    s32 m_nextMode;                          // 0x114: the requested mode (-1 none pending)
    u8 m_waiting;                            // 0x118: 1 while the worker waits on m_event (a job may be posted)
    u8 m_modeChangePending;                  // 0x119: ChangeMode posted m_nextMode
    u8 m_running;                            // 0x11a: 1 at construction
    u8 m_exit;                               // 0x11b: the destructor's stop request
    s32 m_job;                               // 0x11c: the posted job (= the mode), 0 when idle / done
    u8 unk_120[8];                           // 0x120
    ObjectManagerJobDispatcher* m_dispatcher;// 0x128
    ObjectManager* m_objectManager;          // 0x130
    LightManager* m_lightManager;            // 0x138: job 2's parameter (SetPreliminarilyPrepareBasicParameter)
    u64* m_resultBits;                       // 0x140: 2 bits per object: 1 skipped, 2 prepared, 3 failed (atomic ORs)
    RenderableObject* m_resetFirst;          // 0x148: job 6: the first and last object of the range
    RenderableObject* m_resetLast;           // 0x150
    s32 m_paintingListKind;                  // 0x158: job 1: 0 normal, 1 multipass, 2 shadow, 3 post
    s32 m_paintingListIndex;                 // 0x15c: job 1's argument (-1 at construction)
    RenderableObject** m_prelimObjects;      // 0x160: job 2: the batch (objects m_prelimFirst..m_prelimLast)
    s32 m_prelimFirst;                       // 0x168
    s32 m_prelimLast;                        // 0x16c
    u8 m_renderInfo[0x20];                   // 0x170: job 3: a copy of the RENDERINFO head (SetPrepareForRenderingBasicParameter),
                                             //        0x176 / 0x178 rewritten per object (its context count / RenderContext*)
    void* unk_190;                           // 0x190: job 3: the default for an object's 0x1a0 (the Camera argument)
    s32 m_prepareKind;                       // 0x198: job 3: 0 / 1 (1 also stores the object's camera at 0x180)
    u8 unk_19c[4];                           // 0x19c
    RenderableObject** m_prepareObjects;     // 0x1a0: job 3: the batch
    s32 m_prepareFirst;                      // 0x1a8
    s32 m_prepareLast;                       // 0x1ac
    Camera* m_cullCamera;                    // 0x1b0: job 4 (SetViewFrustumCullingBasicParameter)
    s32 m_cullArg1;                          // 0x1b8
    s32 m_cullArg2;                          // 0x1bc
    RenderableObject** m_cullObjects;        // 0x1c0
    s32 m_cullKind;                          // 0x1c8: 0 view frustum, 1 sub view frustum, 2 occlusion
    s32 m_cullFirst;                         // 0x1cc
    s32 m_cullLast;                          // 0x1d0
    u8 unk_1d4[0x2c];                        // 0x1d4: Dispatch_RenderingDecided's parameters (0x1c8..0x1f8 reused)
    RenderableObject** m_liblObjects;        // 0x200: job 5 (SetDetectLIBLBasicParameter)
    s32 m_liblFirst;                         // 0x208
    s32 m_liblLast;                          // 0x20c
};
static_assert(offsetof(ObjectManagerWorkerThread, m_event) == 0x018);
static_assert(offsetof(ObjectManagerWorkerThread, m_lock) == 0x080);
static_assert(offsetof(ObjectManagerWorkerThread, m_mode) == 0x110);
static_assert(offsetof(ObjectManagerWorkerThread, m_nextMode) == 0x114);
static_assert(offsetof(ObjectManagerWorkerThread, m_waiting) == 0x118);
static_assert(offsetof(ObjectManagerWorkerThread, m_modeChangePending) == 0x119);
static_assert(offsetof(ObjectManagerWorkerThread, m_running) == 0x11a);
static_assert(offsetof(ObjectManagerWorkerThread, m_exit) == 0x11b);
static_assert(offsetof(ObjectManagerWorkerThread, m_job) == 0x11c);
static_assert(offsetof(ObjectManagerWorkerThread, m_dispatcher) == 0x128);
static_assert(offsetof(ObjectManagerWorkerThread, m_objectManager) == 0x130);
static_assert(offsetof(ObjectManagerWorkerThread, m_lightManager) == 0x138);
static_assert(offsetof(ObjectManagerWorkerThread, m_resultBits) == 0x140);
static_assert(offsetof(ObjectManagerWorkerThread, m_resetFirst) == 0x148);
static_assert(offsetof(ObjectManagerWorkerThread, m_paintingListKind) == 0x158);
static_assert(offsetof(ObjectManagerWorkerThread, m_paintingListIndex) == 0x15c);
static_assert(offsetof(ObjectManagerWorkerThread, m_prelimObjects) == 0x160);
static_assert(offsetof(ObjectManagerWorkerThread, m_prelimFirst) == 0x168);
static_assert(offsetof(ObjectManagerWorkerThread, m_renderInfo) == 0x170);
static_assert(offsetof(ObjectManagerWorkerThread, unk_190) == 0x190);
static_assert(offsetof(ObjectManagerWorkerThread, m_prepareKind) == 0x198);
static_assert(offsetof(ObjectManagerWorkerThread, m_prepareObjects) == 0x1a0);
static_assert(offsetof(ObjectManagerWorkerThread, m_prepareFirst) == 0x1a8);
static_assert(offsetof(ObjectManagerWorkerThread, m_prepareLast) == 0x1ac);
static_assert(offsetof(ObjectManagerWorkerThread, m_cullCamera) == 0x1b0);
static_assert(offsetof(ObjectManagerWorkerThread, m_cullObjects) == 0x1c0);
static_assert(offsetof(ObjectManagerWorkerThread, m_cullKind) == 0x1c8);
static_assert(offsetof(ObjectManagerWorkerThread, m_liblObjects) == 0x200);
static_assert(offsetof(ObjectManagerWorkerThread, m_liblLast) == 0x20c);
static_assert(sizeof(ObjectManagerWorkerThread) == 0x210);

// Aska::ObjectManagerJobDispatcher: the object manager's worker pool. Guest size 0xc8
// (Global::InstantiateObjectManagerJobDispatcher: operator new(200), constructed with ONE worker:
// ObjectManagerJobDispatcher(Global::m_pObjectManager, 1, &unused)); layout from the constructor, the
// destructors, WaitIdle, ChangeMode, the Dispatch_* and Set*BasicParameter (port/decomp/scene/
// object_manager.c). Dispatch_X(...) posts job X to the first idle worker in mode X and returns true;
// with none it calls ChangeMode(X) on idle workers in another mode and returns false: the caller
// (OnPrePaint, TraversePaintingList, ...) keeps polling, doing nothing else in between (see the README:
// busy-waits). m_exceptIndex >= 0 keeps one worker out (the "except render thread" variants).
// vtable (_ZTVN4Aska26ObjectManagerJobDispatcherE): 0 D1, 1 D0.
class ObjectManagerJobDispatcher {
public:
    void Ctor(ObjectManager*, s32, void*);
    void Dtor();
    void DtorDelete();
    void WaitIdle();
    void WaitAllIssued();
    void ChangeMode(s32);
    void RetryChangeMode(s32);
    void RetryChangeModeExceptRenderThread(s32);
    bool Dispatch_ResetSystemFlags(void*, void*);
    void Dispatch_MakePaintingList(s32, s32);
    bool Dispatch_PreliminarilyPrepare(void*, s32, s32);
    bool Dispatch_PrepareForRendering(s32, void*, u64);
    bool Dispatch_ViewFrustumCulling(s32, s32, s32);
    void Dispatch_RenderingDecided(void*, void*, s32, void*, void*);
    bool Dispatch_DetectLIBL(s32, s32);
    void SetPreliminarilyPrepareBasicParameter(void*, void*);
    void SetPrepareForRenderingBasicParameter(void*, void*, void*);
    void SetViewFrustumCullingBasicParameter(void*, s32, s32, void*, void*);
    void SetDetectLIBLBasicParameter(void*);
    void Sleep();

    const void* vtable;                      // 0x00
    u8 m_lock[0x90];                         // 0x08: Aska::FastCriticalSection (sync)
    ObjectManagerWorkerThread* m_workers;    // 0x98: operator new[] (count at m_workers[-8 bytes])
    ObjectManager* m_objectManager;          // 0xa0
    s32 m_workerCountSeen;                   // 0xa8: ChangeMode stores m_workerCount here
    s32 m_workerCount;                       // 0xac
    s32 m_unkB0;                             // 0xb0: 0x80 at construction
    s32 m_exceptIndex;                       // 0xb4: -1, or a worker the *ExceptRenderThread paths skip
    u8 m_exceptMode;                         // 0xb8: ChangeMode(3) with m_exceptIndex >= 0 sets it (that worker -> idle)
    u8 unk_b9[0x0f];                         // 0xb9
};
static_assert(offsetof(ObjectManagerJobDispatcher, m_lock) == 0x08);
static_assert(offsetof(ObjectManagerJobDispatcher, m_workers) == 0x98);
static_assert(offsetof(ObjectManagerJobDispatcher, m_objectManager) == 0xa0);
static_assert(offsetof(ObjectManagerJobDispatcher, m_workerCountSeen) == 0xa8);
static_assert(offsetof(ObjectManagerJobDispatcher, m_workerCount) == 0xac);
static_assert(offsetof(ObjectManagerJobDispatcher, m_exceptIndex) == 0xb4);
static_assert(offsetof(ObjectManagerJobDispatcher, m_exceptMode) == 0xb8);
static_assert(sizeof(ObjectManagerJobDispatcher) == 0xc8);

// ---- The object manager ----------------------------------------------------------------------------

// ObjectManager::m_passLists[i]: one pass's painting list (MakePaintingList(i)).
struct PaintingPassList {
    RenderableObject** m_sorted;   // +0x00: must be non-null for MakePaintingList(i) to run
    RenderableObject** m_objects;  // +0x08: the pass's objects (counts: ObjectManager::m_passObjectCount[i])
};
static_assert(sizeof(PaintingPassList) == 0x10);

// ObjectManager::m_multipassEnv[i]: a multipass rendering environment (SetMultipassEnvironment); 0x80 of
// them, 0x48 bytes each (the constructor's memset 0x2400). OnPrePaint adds `m_object` to the candidates
// when m_flags bit 7 is set and the pass has objects.
struct MultipassEnvironment {
    u8 unk_00[0x28];
    RenderableObject* m_combiner;  // +0x28: its post-process combiner (GetSceneEV(i + 1) reads its 0x488)
    RenderableObject* m_object;    // +0x30: the pass's system object
    u8 unk_38[0x0a];
    s8 m_flags;                    // +0x42: bit 7: add m_object to the painting candidates; bit 5 in use (Get/SetSceneEV);
                                   //        bits 2-3 cleared by the constructor
    u8 unk_43[5];
};
static_assert(offsetof(MultipassEnvironment, m_combiner) == 0x28);
static_assert(offsetof(MultipassEnvironment, m_object) == 0x30);
static_assert(offsetof(MultipassEnvironment, m_flags) == 0x42);
static_assert(sizeof(MultipassEnvironment) == 0x48);

// Aska::ObjectManager: the scene's root: a TaskManager whose tasks are the scene's objects, the painting
// lists, the culling, the job dispatcher's client, the render thread's owner. Guest size 0x10700
// (Global::InstantiateObjectManager: operator new(0x10700)); one instance, Global::m_pObjectManager.
// Layout from ObjectManager::ObjectManager, OnPrePaint, TraversePaintingList, MakePaintingList and the
// worker's ResetSystemFlags (port/decomp/scene/object_manager.c); most of the 66 KB are fixed arrays
// (painting lists of 4096 pointers, the layer counters, the multipass environments) recovered as
// named padding where only their extent is known.
// Each frame (OnPrePaint, run by the owner TaskManager through the Task at 0x28): the system objects
// (FilterTexture, DepthTexture, the MSAA changers, the post-process buffer manager) are appended to
// m_candidates and reset; MakePaintingList jobs run per shadow layer, multipass layer and pass; the
// RenderContextServer is reset; then PreliminarilyPrepare runs on every candidate in batches of 64
// through the dispatcher; OnPostPaint traverses the lists (TraversePaintingList: PrepareForRendering
// in batches of 8, then RenderThread::AddRenderQueue per prepared object).
// vtable: _ZTVN4Aska13ObjectManagerE + 0x10 (TaskManager's interface; GetClassID slot 6, Get 16, Set 17),
// and + 0xb0 for the Task at 0x28 (this-adjusting thunks of the destructors, GetClassID, Get, Set).
class ObjectManager {
public:
    void Ctor();
    void Dtor();
    void DtorDelete();
    u64 GetClassID(s32 depth) const;  // slot 6
    bool Get(u64, void*) const;  // slot 16
    bool Set(u64, const void*);  // slot 17
    void MakeDefaultRenderLayers();
    void SetTileEnvironment(s32, s32, u32, float, s32);
    void SetTilebasedRendering(s32);
    void FlushSystemTextures();
    void OnPrePaint();
    void UpdateRenderLayerCondition();
    void UpdateMultiDraw();
    void OnPostPaint();
    void TraversePaintingListNoResolve(void*, s32, void*, s32, s32, void*, bool);
    void TraversePaintingList(void*, s32, void*, s32, s32, s32, void*, bool);
    void OnPaint();
    void MakeRenderInfoConditionList(void*, void*, void*, void*, u32);
    void MakePaintingList(s32);
    void MakePaintingListPost();
    void MakePaintingListShadow(s32);
    void MakePaintingListMultipass(s32);
    void Prerender();
    void PrepareMatrices(s32, void*);
    void MultithreadViewFrustumCulling(void*, s32, s32, void*, void*, s32);
    void MultithreadOcclusionCulling(void*, s32, s32, bool, void*, void*, s32);
    void Prerender_SortForPostProcessing(s32, void*, s32, void*, void*, void*, void*);
    void Prerender_VersatileAndMotionBlur(void*, s32, void*);
    void Prerender_TileCandidates(void*, s32, void*, s32, ObjectManagerJobDispatcher*);
    void Prerender_MultiPass(void*, s32, ObjectManagerJobDispatcher*);  // Aska::ObjectManager::Prerender_MultiPass(Aska::TLongInt<unsigned long, 2>*, int, Aska::ObjectManagerJobDispatcher*)
    void MakeDetectLIBLList(void*, void*, s32);
    void MultithreadDetectLIBL(void*, s32);
    void MultithreadSubViewFrustumCulling(void*, s32, s32, void*, void*, s32);
    void ViewFrustumCulling(void*, s32, s32, void*, s32, s32, void*);
    void DetectLIBL(void*, s32, s32);
    void SubViewFrustumCulling(void*, s32, s32, void*, s32, s32, void*);
    void OcclusionCulling(void*, s32, s32, bool, void*, s32, s32, void*);
    void AddPaintingListCandidates(void*);
    void AddMultipassPaintingListCandidates(void*, s32);
    bool IsReducedBufferLayer(s32);
    bool IsNeedZLayer(s32);
    void ClearMultipassEnvironment(s32);
    void SetMultipassEnvironment(s32, bool, s32, s32, s32, s32, s32, s32, u32, float, s32, void*, bool, bool, bool, bool);
    void SetShadowEnvironment(s32, bool, s32, s32, s32, s32, s32, s32, u32, float, s32, void*, s32, s32, bool, u8);
    void SetShadowMapResolver(s32, void*);
    void WaitForInitialize();
    void OrMultipassRenderingIDtoAllObjects(void*, bool);  // Aska::ObjectManager::OrMultipassRenderingIDtoAllObjects(Aska::TLongInt<unsigned long, 2> const*, bool)
    void AndMultipassRenderingIDtoAllObjects(void*, bool);  // Aska::ObjectManager::AndMultipassRenderingIDtoAllObjects(Aska::TLongInt<unsigned long, 2> const*, bool)
    void DeleteResources();
    void SetSceneEV(s32, float, float, float);
    void GetSceneEV(s32) const;
    void SetMeteringScale(s32, float);
    void SetPostProcessDitherRate(float);
    void GetPostProcessDitherRate() const;
    void GetPostProcessBloom();
    void SetVertexShaderGprAllocation(s32);
    void GetVertexShaderGprAllocation() const;
    void WaitBackBufferSync();
    void SwapFrame();
    void WaitGPUSync();
    void AddGPUSyncNotify(void*);
    void RemoveGPUSyncNotify(void*);
    bool QueryGPUSyncNotify(void*);
    bool IsGPUBusy();
    void GetNoTexture() const;
    void BackBufferSyncCallback(u64, u64);
    void ProfileCallBack(u64, u64);
    void GetPassFormat(s32) const;

    TaskManagerBase base;                          // 0x00000
    u8 unk_0ff0[8];                                // 0x00ff0
    u8 m_unkFF8;                                   // 0x00ff8: 1 at construction
    u8 unk_0ff9[7];                                // 0x00ff9
    RenderContextServer* m_renderContextServer;    // 0x01000: operator new(0x58)
    RenderableObject** m_list1008;                 // 0x01008: 0x8000-byte arrays (4096 objects)
    RenderableObject** m_list1010;                 // 0x01010
    RenderableObject** m_list1018;                 // 0x01018
    PaintingPassList m_passLists[8];               // 0x01020: pass 0's arrays allocated by the constructor
    u8 unk_10a0[0x800];                            // 0x010a0: zeroed by the constructor
    RenderableObject** m_list18a0;                 // 0x018a0: 0x8000 bytes
    u8 unk_18a8[0x208];                            // 0x018a8
    RenderableObject** m_list1ab0;                 // 0x01ab0: 0x8000 bytes
    RenderableObject** m_list1ab8;                 // 0x01ab8: 0x8000 bytes
    void* m_list1ac0;                              // 0x01ac0: 0x4000 bytes
    RenderableObject** m_candidates;               // 0x01ac8: this frame's painting candidates (m_candidateCount)
    RenderableObject** m_list1ad0;                 // 0x01ad0: 0x8000 bytes
    RenderableObject** m_list1ad8;                 // 0x01ad8: 0x8000 bytes
    RenderableObject** m_multiDrawObjects;         // 0x01ae0: 0x100 bytes; OnPrePaint bumps their 0x1ac (m_multiDrawObjectCount)
    void* m_list1ae8;                              // 0x01ae8: 0x200 bytes
    RenderableObject** m_list1af0;                 // 0x01af0: 0x8000 bytes
    u8 unk_1af8[8];                                // 0x01af8
    u64 unk_1b00;                                  // 0x01b00: 0 at construction
    s32 m_multiDrawObjectCount;                    // 0x01b08
    u8 unk_1b0c[4];                                // 0x01b0c
    u8 m_lock[0x90];                               // 0x01b10: Aska::FastCriticalSection (sync)
    u64* m_resultBits;                             // 0x01ba0: 2 bits per candidate, the workers' results (operator new[])
    s32 m_resultBitsCapacity;                      // 0x01ba8: objects m_resultBits holds
    u8 unk_1bac[0x18];                             // 0x01bac
    s32 m_postProcessCount;                        // 0x01bc4: != 0: MakePaintingList job kind 3 (post)
    s32 m_passObjectCount[8];                      // 0x01bc8: objects of m_passLists[i]
    s32 m_passCount1be8[8];                        // 0x01be8: MakePaintingList's per-pass counter
    s32 m_layerObjectCount[0x80];                  // 0x01c08: per multipass layer (OnPrePaint: != 0 -> MakePaintingList kind 1)
    u16 m_shadowLayerCount[0x40];                  // 0x01e08: per shadow layer (!= 0 -> MakePaintingList kind 2)
    u8 unk_1e88[0x2068];                           // 0x01e88
    u16 m_unk3ef0;                                 // 0x03ef0: OnPrePaint's RenderContext index base
    u8 unk_3ef2[2];                                // 0x03ef2
    s32 m_candidateCount;                          // 0x03ef4
    u8 unk_3ef8[0x14];                             // 0x03ef8
    u8 m_enabled;                                  // 0x03f0c: 0: OnPrePaint does nothing (1 at construction)
    u8 unk_3f0d;                                   // 0x03f0d
    u8 m_frozen;                                   // 0x03f0e: != 0: OnPrePaint does nothing
    u8 unk_3f0f[5];                                // 0x03f0f
    u8 m_renderThreadBusySeen;                     // 0x03f14: set when the render thread's 0x501d1 flag skipped a frame
    u8 unk_3f15[7];                                // 0x03f15
    u8 m_layerLimit;                               // 0x03f1c: from the RenderLayer's 0x21 (capped by 0x1e when m_capLayers)
    u8 m_capLayers;                                // 0x03f1d: 1 at construction
    u8 unk_3f1e[2];                                // 0x03f1e
    s32 m_passCount;                               // 0x03f20: passes MakePaintingList(0..n-1) runs (at least 1)
    float m_unk3f24;                               // 0x03f24: 0.25 at construction
    u8 unk_3f28[0x530];                            // 0x03f28
    u64 unk_4458;                                  // 0x04458: 0 at construction
    void* m_freezeRenderingTask;                   // 0x04460: Aska::FreezeRenderingTask (a Task, operator new(0x28)), on the system task manager
    u8 unk_4468[0x10];                             // 0x04468
    RenderLayer* m_renderLayer;                    // 0x04478: operator new(0x110): u32 count, u16* entries (+8), the layer -> bucket map (+0x10)
    RenderThread* m_renderThread;                  // 0x04480: operator new(0x50298)
    u64 unk_4488;                                  // 0x04488: 0 at construction
    u64 unk_4490;                                  // 0x04490: 0 at construction
    RenderableObject* m_systemObjects[0x20];       // 0x04498: the objects ObjectManager owns (m_systemObjectCount)
    s32 m_systemObjectCount;                       // 0x04598
    u8 unk_459c[0x14];                             // 0x0459c
    RenderableObject* m_filterTextureObject;       // 0x045b0: Aska::FilterTextureObject (0x2480 bytes)
    RenderableObject* m_depthTextureObject;        // 0x045b8: Aska::DepthTextureObject (0x2220 bytes)
    RenderableObject* m_msaaChanger[2];            // 0x045c0: Aska::MSAAChangerObject (RenderableObject + u16 at 0x308)
    s32 m_multiDrawLayerCount;                     // 0x045d0: layers whose entry has bit 11 set (AofObject reads it)
    u8 unk_45d4[4];                                // 0x045d4
    void* m_postProcessMaster;                     // 0x045d8: Aska::PostProcessMaster (0x7a0 bytes, aligned 16)
    RenderableObject* m_proceduralTextureManager;  // 0x045e0: Aska::ProceduralTextureManager (0x1920 bytes)
    float m_unk45e8;                               // 0x045e8: 0.1 at construction
    u8 unk_45ec[4];                                // 0x045ec
    MultipassEnvironment m_multipassEnv[0x80];     // 0x045f0
    u8 unk_69f0[0x4a28];                           // 0x069f0
    RenderableObject* m_postProcessCombiner;       // 0x0b418: Aska::PostProcessCombinerTBR (0x1ee0 bytes)
    RenderableObject* m_postProcessBufferManager;  // 0x0b420: Aska::PostProcessBufferManager (0x4a0 bytes)
    u8 unk_b428[0x50c8];                           // 0x0b428
    void* m_shadowManagerRegistry;                 // 0x104f0: Aska::ShadowManagerRegistry (a TaskManager, 0x13f0 bytes)
    RenderableObject* m_contextObjects[0x40];      // 0x104f8: OnPrePaint gives each a RenderContext (m_contextObjectCount)
    s32 m_contextObjectCount;                      // 0x106f8
    u8 unk_106fc[4];                               // 0x106fc
};
static_assert(offsetof(ObjectManager, m_unkFF8) == 0x00ff8);
static_assert(offsetof(ObjectManager, m_renderContextServer) == 0x01000);
static_assert(offsetof(ObjectManager, m_passLists) == 0x01020);
static_assert(offsetof(ObjectManager, m_list18a0) == 0x018a0);
static_assert(offsetof(ObjectManager, m_list1ab0) == 0x01ab0);
static_assert(offsetof(ObjectManager, m_candidates) == 0x01ac8);
static_assert(offsetof(ObjectManager, m_multiDrawObjects) == 0x01ae0);
static_assert(offsetof(ObjectManager, m_multiDrawObjectCount) == 0x01b08);
static_assert(offsetof(ObjectManager, m_lock) == 0x01b10);
static_assert(offsetof(ObjectManager, m_resultBits) == 0x01ba0);
static_assert(offsetof(ObjectManager, m_resultBitsCapacity) == 0x01ba8);
static_assert(offsetof(ObjectManager, m_postProcessCount) == 0x01bc4);
static_assert(offsetof(ObjectManager, m_passObjectCount) == 0x01bc8);
static_assert(offsetof(ObjectManager, m_passCount1be8) == 0x01be8);
static_assert(offsetof(ObjectManager, m_layerObjectCount) == 0x01c08);
static_assert(offsetof(ObjectManager, m_shadowLayerCount) == 0x01e08);
static_assert(offsetof(ObjectManager, m_unk3ef0) == 0x03ef0);
static_assert(offsetof(ObjectManager, m_candidateCount) == 0x03ef4);
static_assert(offsetof(ObjectManager, m_enabled) == 0x03f0c);
static_assert(offsetof(ObjectManager, m_frozen) == 0x03f0e);
static_assert(offsetof(ObjectManager, m_renderThreadBusySeen) == 0x03f14);
static_assert(offsetof(ObjectManager, m_layerLimit) == 0x03f1c);
static_assert(offsetof(ObjectManager, m_passCount) == 0x03f20);
static_assert(offsetof(ObjectManager, m_unk3f24) == 0x03f24);
static_assert(offsetof(ObjectManager, unk_4458) == 0x04458);
static_assert(offsetof(ObjectManager, m_freezeRenderingTask) == 0x04460);
static_assert(offsetof(ObjectManager, m_renderLayer) == 0x04478);
static_assert(offsetof(ObjectManager, m_renderThread) == 0x04480);
static_assert(offsetof(ObjectManager, m_systemObjects) == 0x04498);
static_assert(offsetof(ObjectManager, m_systemObjectCount) == 0x04598);
static_assert(offsetof(ObjectManager, m_filterTextureObject) == 0x045b0);
static_assert(offsetof(ObjectManager, m_depthTextureObject) == 0x045b8);
static_assert(offsetof(ObjectManager, m_msaaChanger) == 0x045c0);
static_assert(offsetof(ObjectManager, m_multiDrawLayerCount) == 0x045d0);
static_assert(offsetof(ObjectManager, m_postProcessMaster) == 0x045d8);
static_assert(offsetof(ObjectManager, m_proceduralTextureManager) == 0x045e0);
static_assert(offsetof(ObjectManager, m_multipassEnv) == 0x045f0);
static_assert(offsetof(ObjectManager, m_postProcessCombiner) == 0x0b418);
static_assert(offsetof(ObjectManager, m_postProcessBufferManager) == 0x0b420);
static_assert(offsetof(ObjectManager, m_shadowManagerRegistry) == 0x104f0);
static_assert(offsetof(ObjectManager, m_contextObjects) == 0x104f8);
static_assert(offsetof(ObjectManager, m_contextObjectCount) == 0x106f8);
static_assert(sizeof(ObjectManager) == 0x10700);

// ---- AOF models -----------------------------------------------------------------------------------

// Aska::AofObjectRenderState: an AofObject's cached render state for one pass kind (GetObjectRenderState
// finds or appends it: 4 inline in AofObject, then a heap array). 0x20 bytes.
struct AofObjectRenderState {
    u8 unk_00[0x18];
    u16 m_passKind;   // +0x18: RENDERINFO's pass kind (byte 3 & 7)
    u8 m_valid;       // +0x1a: 0 = rebuild (MakeObjectRenderState<...>)
    u8 unk_1b[5];
};
static_assert(offsetof(AofObjectRenderState, m_passKind) == 0x18);
static_assert(offsetof(AofObjectRenderState, m_valid) == 0x1a);
static_assert(sizeof(AofObjectRenderState) == 0x20);

// Aska::AofObject: a model instance (an .aof mesh set drawn with its AofHandler's materials): the
// drawable the home screen's characters, the battle's models and the UI's DirectAof sprites are. Guest
// size 0x6b0 (AofObject::CreateClone: operator new(0x6b0)); layout from AofObject::AofObject,
// PrepareForRendering, GetObjectRenderState, SetProgrammableTransparency (port/decomp/scene/aof_object.c,
// port/decomp/render/renderable_object.c). The draw path (a worker thread, job 3): PrepareForRendering
// (slot 80) -> GetObjectRenderState(pass kind) -> GetColorPass / the RenderPassManager's passes ->
// MakeObjectRenderState<flags> -> RenderPass::PrepareRenderState -> PrepareColorShader -> per
// RenderContext (0x230 bytes each) m_handler's vtable slot 7 (MakeRenderContext).
// vtable (_ZTVN4Aska9AofObjectE, 92 slots): RenderableObject's 89 (overrides as declared), then 89
// IsIntersectable, 90 SetAofHandler, 91 Clone(AofObject const*, int).
class AofObject {
public:
    void CtorBase();
    void Dtor();
    void DtorDelete();
    u64 GetClassID(s32 depth) const;  // slot 2
    bool Clone(const render::IAnimatable* src);  // slot 3
    AofObject* CreateClone(const render::IAnimatable* src);  // slot 4
    bool Get(u64, void*) const;  // slot 5
    bool Set(u64, const void*);  // slot 6
    void DeleteThis(void*);  // slot 7
    void Run(s32);  // slot 13
    void InitializeConditions();  // slot 22
    void CheckSleepAvailability();  // slot 23
    void GetBoundingBox(bool);  // slot 42
    void SetRenderLayerID(u8);  // slot 44
    void UpdateMultiDrawVars();  // slot 45
    void SetShadowManagerIndex(s32, u64);  // slot 46
    void GetShadowManagerIndex(s32);  // slot 47
    void GetShaderAdapterCache(s32);  // slot 48
    void GetShaderAdapterCacheSize() const;  // slot 49
    void SetShaderAdapterCacheCount(s32, s32);  // slot 50
    void ResetDynamicShaderModifier();  // slot 51
    void EnableCastShadow(bool);  // slot 52
    void PrepareLightContext(void*);  // slot 55
    bool IsAffectingLight(void*);  // slot 56
    bool QueryPrebuiltVariation() const;  // slot 59
    void SetPrebuiltVariation(s32);  // slot 60
    void GetCurrentPrebuiltVariation() const;  // slot 61
    void CheckRenderContexts();  // slot 62
    void SetSystemColorRate(void*);  // slot 64
    void SystemColorRate() const;  // slot 65
    void SetColorRate(void*);  // slot 66
    void ColorRate() const;  // slot 67
    void SetSystemColorOffset(void*);  // slot 68
    void SystemColorOffset() const;  // slot 69
    void SetColorOffset(void*);  // slot 70
    void ColorOffset() const;  // slot 71
    void SetProgrammableTransparency(u64);  // slot 73
    void SetIBLAcceptanceNumber(u32);  // slot 74
    void ComputeBoundingSphere(bool);  // slot 75
    void GetBoundingBoxDirect(void*);  // slot 76
    bool HasBoundingBox() const;  // slot 77
    void RenderingDecided();  // slot 78
    bool PreliminarilyPrepare(LightManager* lm);  // slot 79
    bool PrepareForRendering(const RENDERINFO* info);  // slot 80
    void Render(RenderContext* ctx, s32 pass);  // slot 81
    void ReleaseShaderCache();  // slot 85
    void EnableObjectMotionBlur(bool);  // slot 86
    bool IsIntersectable();  // slot 89
    void SetAofHandler(AofHandler*, bool);  // slot 90
    bool Clone(const AofObject*, s32);  // slot 91
    void RemoveStandingShaderAdapter(void*);
    void InvalidateObjectRenderState();
    void SetProgrammableForceOpaque(bool);
    void UpdateBoundingVolumes(AofHandler*);
    void AddStandingShaderAdapter(void*);
    void FlushRenderPassManager_unsafe();
    void FlushRenderPassManager();
    bool MakeObjectRenderStateShadow(void*, void*, bool);
    bool MakeObjectRenderState_1010(AofObjectRenderState* state, RenderPass* pass);  // MakeObjectRenderState<1010u>
    bool MakeObjectRenderState_496(AofObjectRenderState* state, RenderPass* pass);  // MakeObjectRenderState<496u>
    bool MakeObjectRenderStateOMB(void*, void*, bool);
    bool MakeObjectRenderState_2027(AofObjectRenderState* state, RenderPass* pass);  // MakeObjectRenderState<2027u>
    bool MakeObjectRenderState_1514(AofObjectRenderState* state, RenderPass* pass);  // MakeObjectRenderState<1514u>
    bool MakeObjectRenderStateMultiDraw(void*, void*);
    bool MakeObjectRenderState_2543(AofObjectRenderState* state, RenderPass* pass);  // MakeObjectRenderState<2543u>
    bool MakePassRenderStateMultiDraw(u32, void*);
    bool MakeObjectRenderState(void*, void*, bool);
    bool MakeObjectRenderState_7151(AofObjectRenderState* state, RenderPass* pass);  // MakeObjectRenderState<7151u>
    bool MakeObjectRenderState_3055(AofObjectRenderState* state, RenderPass* pass);  // MakeObjectRenderState<3055u>
    void InitializeRendering();
    void CalcBoundingExtent(bool);
    void ResetDynamicShaderModifierCache();
    void PrepareLightContextPost(void*);
    void PrepareIBLContext(void*, void*);
    bool IsPBAmbientBRDFEnabled() const;
    RenderPass* GetColorPass(const RENDERINFO* info);
    RenderPass* GetMultiDrawPass(u32 index, const RENDERINFO* info);
    bool PrepareForRendering_Preliminary();
    AofObjectRenderState* GetObjectRenderState(u32 passKind);
    void PrepareObjectScreenUVMatrix(void*, void*);
    bool PrepareColorShader(void*, void*);
    bool PrepareShader(void*, void*, bool);
    void GetActualLightConfiguration() const;
    void RenderProfileBegin(void*);
    void RenderContextValidation(void*);
    void RenderProfileEnd();
    void SetPerPixelLightCount(s32);
    void EnableBoundingObjectDebug(bool);
    void SetNormalDebug(s32);
    void SetBinormalDebug(s32);
    void GetPackedIndexByAttrType(const char*, const char*) const;
    void GetPackedIndexByTextureType(const char*, u64) const;
    void SearchTextureID(const char*, u64) const;
    void ChangeTextureID(u64, const char*, u64);
    void GetRandomVertexPosAndNormal(void*, void*) const;
    void GetVertexPosition(s32, void*) const;
    void GetVertexPosAndNormal(s32, void*, void*) const;
    void StopModifiers();
    void StartModifiers();
    void GetRenderNodeIndex(const char*);
    void GetRenderNode(s32);
    void AllocateMeshArray(u32);
    void SetStateDirtyToAllObjects();
    bool MakeObjectRenderState_1015(AofObjectRenderState* state, RenderPass* pass);  // MakeObjectRenderState<1015u>
    bool MakeObjectRenderState_497(AofObjectRenderState* state, RenderPass* pass);  // MakeObjectRenderState<497u>
    void CheckLightMaskMixerLight(void*) const;

    RenderableObject base;                    // 0x000: vtable _ZTVN4Aska9AofObjectE + 0x10
    u8 unk_310[0x60];                         // 0x310
    u64 unk_370;                              // 0x370: 0 at construction
    u32 m_flags;                              // 0x378: bit 4 needs light context, bit 13 / 19 pass selectors (PrepareForRendering), bit 16 no-transparency
    u16 m_flags2;                             // 0x37c: bit 5: run PrepareForRendering_Preliminary first
    u8 unk_37e;                               // 0x37e: 0 at construction
    s8 m_forcedLayer;                         // 0x37f: -1 = from RENDERINFO (bits 3-4 of byte 3); 0xffff written with 0x380
    u8 unk_380;                               // 0x380
    s8 m_lightConfiguration;                  // 0x381: -1 = ObjectManager::m_LightConfiguration (GetActualLightConfiguration)
    u16 unk_382;                              // 0x382: 0 at construction
    u8 m_unk384;                              // 0x384: compared with the color pass's 0x1c0 (shader invalidation)
    u8 unk_385;                               // 0x385
    u8 m_savedTransparency;                   // 0x386: SetProgrammableTransparency's saved mode (0xff none)
    u8 unk_387;                               // 0x387
    u8 unk_388;                               // 0x388
    u8 unk_389;                               // 0x389: 1 at construction
    u8 unk_38a;                               // 0x38a: 3 at construction
    u8 unk_38b;                               // 0x38b
    u8 unk_38c;                               // 0x38c: 3 at construction
    u8 unk_38d;                               // 0x38d
    u8 m_unk38e;                              // 0x38e: compared with m_vertexPassNum
    u8 m_vertexPassNum;                       // 0x38f: RenderPass::GetVertexPassNum (pass kind 3)
    u16 m_shaderFlags;                        // 0x390: & 0x4001 -> the pass's 0x20 before AofHandler::InitializeShader
    u8 unk_392[6];                            // 0x392
    RenderPassManager* m_renderPassManager;   // 0x398: its base pass at +0x18
    SkinMatricesBase* m_skinMatrices;         // 0x3a0: m_handler's CreateSkinMatrices (slot 13) result; base 0x198 |= 0x200 then
    u64 unk_3a8;                              // 0x3a8
    u32 unk_3b0;                              // 0x3b0
    u32 unk_3b4;                              // 0x3b4
    u32 unk_3b8;                              // 0x3b8
    u32 unk_3bc;                              // 0x3bc
    void* m_buffer3c0;                        // 0x3c0: operator new[](0x3520, align 16) (SetAofHandler)
    u64 unk_3c8[2];                           // 0x3c8
    AofHandler* m_handler;                    // 0x3d8: the model data (materials at m_handler->m_materials)
    u8 unk_3e0[0x30];                         // 0x3e0
    u8 m_textureModifiers[0x20];              // 0x410: Aska::TextureModifierManager (vptr + a LinkElement list sentinel at 0x418)
    u32 unk_430;                              // 0x430
    u8 unk_434[4];                            // 0x434
    u64 unk_438[4];                           // 0x438
    AofObjectRenderState* m_renderStates;     // 0x458: the heap array (null: m_inlineRenderStates)
    u16 m_renderStateCapacity;                // 0x460: 4 at construction
    u16 m_renderStateCount;                   // 0x462
    u8 unk_464[4];                            // 0x464
    void* m_renderStateAllocator;             // 0x468: Aska::MemoryManager* (null: operator new[])
    AofObjectRenderState m_inlineRenderStates[4];  // 0x470
    float unk_4f0;                            // 0x4f0: 1.0 at construction
    u8 unk_4f4[4];                            // 0x4f4
    AofObject* m_ring[2];                     // 0x4f8: self at construction (a ring of clones?)
    u8 unk_508[0x18];                         // 0x508
    MathVector m_colorRate;                   // 0x520: ColorRate() (AofObject keeps its own; (1, 1, 1, 1) at construction)
    MathVector m_colorOffset;                 // 0x530: ColorOffset()
    MathVector m_systemColorRate;             // 0x540: SystemColorRate() ((1, 1, 1, 1) at construction)
    MathVector m_systemColorOffset;           // 0x550: SystemColorOffset()
    u8 unk_560[0x40];                         // 0x560
    u8 unk_5a0[0x80];                         // 0x5a0: zeroed by the constructor
    MathVector m_vec620;                      // 0x620
    float m_unk630[5];                        // 0x630: 100, 100, 0.5, 0.1, 100 at construction
    u8 unk_644[0x0c];                         // 0x644
    u64 unk_650;                              // 0x650
    u32 unk_658;                              // 0x658: 2 at construction
    u8 unk_65c[4];                            // 0x65c
    u64 unk_660;                              // 0x660
    u8 unk_668[0x10];                         // 0x668
    u64 unk_678[2];                           // 0x678
    u8 unk_688[8];                            // 0x688
    void* m_multiDrawData;                    // 0x690: null: no multi-draw pass (pass kind 5)
    u8 m_prebuiltVariation[3];                // 0x698: 1, 2, 0 at construction; 2 = a variation axis (QueryPrebuiltVariation);
                                              //        [2] = the IBL acceptance number (SetIBLAcceptanceNumber)
    u8 unk_69b[2];                            // 0x69b
    u8 unk_69d[3];                            // 0x69d
    u64 unk_6a0;                              // 0x6a0
    s16 m_lastRenderInfoId;                   // 0x6a8: PrepareForRendering stores RENDERINFO's first s16
    u8 unk_6aa[6];                            // 0x6aa
};
static_assert(offsetof(AofObject, m_flags) == 0x378);
static_assert(offsetof(AofObject, m_flags2) == 0x37c);
static_assert(offsetof(AofObject, m_forcedLayer) == 0x37f);
static_assert(offsetof(AofObject, m_unk384) == 0x384);
static_assert(offsetof(AofObject, m_savedTransparency) == 0x386);
static_assert(offsetof(AofObject, m_vertexPassNum) == 0x38f);
static_assert(offsetof(AofObject, m_shaderFlags) == 0x390);
static_assert(offsetof(AofObject, m_renderPassManager) == 0x398);
static_assert(offsetof(AofObject, m_skinMatrices) == 0x3a0);
static_assert(offsetof(AofObject, m_buffer3c0) == 0x3c0);
static_assert(offsetof(AofObject, m_handler) == 0x3d8);
static_assert(offsetof(AofObject, m_textureModifiers) == 0x410);
static_assert(offsetof(AofObject, m_renderStates) == 0x458);
static_assert(offsetof(AofObject, m_renderStateCapacity) == 0x460);
static_assert(offsetof(AofObject, m_renderStateCount) == 0x462);
static_assert(offsetof(AofObject, m_renderStateAllocator) == 0x468);
static_assert(offsetof(AofObject, m_inlineRenderStates) == 0x470);
static_assert(offsetof(AofObject, unk_4f0) == 0x4f0);
static_assert(offsetof(AofObject, m_ring) == 0x4f8);
static_assert(offsetof(AofObject, m_colorRate) == 0x520);
static_assert(offsetof(AofObject, m_colorOffset) == 0x530);
static_assert(offsetof(AofObject, m_systemColorRate) == 0x540);
static_assert(offsetof(AofObject, m_systemColorOffset) == 0x550);
static_assert(offsetof(AofObject, unk_5a0) == 0x5a0);
static_assert(offsetof(AofObject, m_vec620) == 0x620);
static_assert(offsetof(AofObject, m_unk630) == 0x630);
static_assert(offsetof(AofObject, unk_658) == 0x658);
static_assert(offsetof(AofObject, m_multiDrawData) == 0x690);
static_assert(offsetof(AofObject, m_prebuiltVariation) == 0x698);
static_assert(offsetof(AofObject, m_lightConfiguration) == 0x381);
static_assert(offsetof(AofObject, m_lastRenderInfoId) == 0x6a8);
static_assert(sizeof(AofObject) == 0x6b0);

// Aska::AofHandler: a model's data, shared by its AofObjects (an ITextureHandler: textures are attached
// through it). Guest size 0x330 (AofObject::Clone: operator new(0x330)); layout from
// AofHandler::AofHandler, SetShaderContextFlag, SkinMatricesBase::Init and AofObject's uses
// (port/decomp/scene/aof_handler.c). Its MaterialList (render's Aska::MaterialList: MaterialList::Activate
// uploads the material constants; docs/render/hair-shader.md) is embedded at 0xe8.
// vtable (_ZTVN4Aska10AofHandlerE + 0x10; secondary vptrs at 0x98 (+0x90) and 0xa0 (+0xb8)): the members
// declared with slots.
class AofHandler {
public:
    void CtorBase();
    void Dtor();
    void DtorDelete();
    void NotifyTexture();  // slot 2
    bool Attach(const void*, bool, s32, s32);  // slot 3
    void Detach();  // slot 4
    bool Clone(const AofHandler*, bool);  // slot 5
    bool IsDirectAof() const;  // slot 6
    bool MakeRenderContext(void*, AofObject*, void*, void*, void*);  // slot 7
    void NotifyMapping();  // slot 8
    void OnSkinMatricesCreated(AofObject*);  // slot 9
    void GetShaderContextFlag() const;  // slot 10
    void DeleteCallback(s32, void*);  // slot 11
    void CancelCallback(s32, void*);  // slot 12
    SkinMatricesBase* CreateSkinMatrices() const;  // slot 13
    void AttachTextures(void*, void*, bool, s32, s32);
    void DetachTextures(void*, void*, bool);
    void Attach_IndexList(void*, void*, u32);
    void Attach_VertexList(void*, void*, u32, bool);
    void Attach_AdditionalBuffers(void*, void*);
    void Attach_CalcPrimitiveInfo(void*, void*);
    void HookMeshset(s32, void*);
    void UnhookMeshset(s32);
    bool InitializeShaderKey(void*, s32, bool);
    bool InitializeShader(void*, s32, bool, bool);
    void CheckShaderKeyIsInAHSLPrebuiltDatabase(void*);
    void UpdateForProceduralTexture();
    bool UsesTexturePaletteBySkinning() const;
    void InitializeSkinPaletteConstant(SkinMatricesBase*);
    void SetShaderContextFlag();

    const void* vtable;              // 0x000: ITextureHandler's place (vtable + 0x10)
    u32 unk_008;                     // 0x008
    u8 unk_00c[4];                   // 0x00c
    u8 m_barrier[0x78];              // 0x010: Aska::TBarrierSlim<true> (vptr, u32 lock at 0x18, u32 at 0x1c, Aska::Event at 0x20)
    u32 unk_088;                     // 0x088
    u8 unk_08c[4];                   // 0x08c
    u32 unk_090;                     // 0x090: atomic
    u8 unk_094;                      // 0x094
    u8 unk_095[3];                   // 0x095
    const void* vtable2;             // 0x098: _ZTVN4Aska10AofHandlerE + 0x90 (the INotify-like base: NotifyMapping)
    const void* vtable3;             // 0x0a0: _ZTVN4Aska10AofHandlerE + 0xb8 (DeleteCallback / CancelCallback)
    u8 m_flagsA8;                    // 0x0a8: bits 0-4 cleared by the constructor
    u8 unk_0a9;                      // 0x0a9
    u8 unk_0aa[6];                   // 0x0aa
    void* m_model;                   // 0x0b0: the attached model header (+0x70 u16 meshset count, +0x76 u16 bone count, +0x78 u16 palette size)
    u8 unk_0b8;                      // 0x0b8
    u8 unk_0b9[3];                   // 0x0b9
    float unk_0bc[2];                // 0x0bc: 1, 1 at construction
    u8 unk_0c4[0x0c];                // 0x0c4: zeroed by the constructor
    void** m_meshsets;               // 0x0d0: per meshset: +8 -> its info (+0x19 u8 skin matrix count), [0] -> +0x1a s8 shared-palette index
    u8 unk_0d8[8];                   // 0x0d8
    void* m_bindPose;                // 0x0e0: SkinMatricesBase::Init copies it (the bones' inverse bind matrices)
    u8 m_materials[0x230];           // 0x0e8: Aska::MaterialList (render): u16 flags at +0x20 (0x108), u8 material count +0x22 (0x10a),
                                     //        the materials (0x2a0 bytes each) at *(+0x18) (0x100) + 0x10
    u64 unk_318;                     // 0x318: 0 at construction
    u64 unk_320;                     // 0x320
    u64 unk_328;                     // 0x328
};
static_assert(offsetof(AofHandler, m_barrier) == 0x010);
static_assert(offsetof(AofHandler, vtable2) == 0x098);
static_assert(offsetof(AofHandler, vtable3) == 0x0a0);
static_assert(offsetof(AofHandler, m_flagsA8) == 0x0a8);
static_assert(offsetof(AofHandler, m_model) == 0x0b0);
static_assert(offsetof(AofHandler, m_meshsets) == 0x0d0);
static_assert(offsetof(AofHandler, m_bindPose) == 0x0e0);
static_assert(offsetof(AofHandler, m_materials) == 0x0e8);
static_assert(offsetof(AofHandler, unk_318) == 0x318);
static_assert(sizeof(AofHandler) == 0x330);

// ---- Skinning --------------------------------------------------------------------------------------

// Aska::SkinMatricesBase: an AofObject's bone palette. Guest size 0x78 (the constructor's memset
// 0x10..0x78; SkinMatrices adds 0x78..0x98); layout from SkinMatricesBase::SkinMatricesBase, Init,
// GetSkinMatrixCount (port/decomp/scene/skinning.c). Created by AofHandler::CreateSkinMatrices (slot 13:
// operator new(0x98) SkinMatrices).
// vtable (_ZTVN4Aska16SkinMatricesBaseE): 0 D1, 1 D0, 2 MakeSkinMatrices (pure here), 3 UpdateSimpleDynamics,
// 4 GetTexturePaletteMatrices, 5 GetBoneObject, 6 InitPalette_(AofObject*, AsfHandler*), 7 InitPalette_(
// AofObject*, DirectAofPrimitiveBase*), 8 InitPaletteEx_, 9 GetAllocSize, 10 Assign.
class SkinMatricesBase {
public:
    void CtorBase();
    void DtorBase();
    void DtorDelete();
    void UpdateSimpleDynamics(void*);  // slot 3
    void GetTexturePaletteMatrices() const;  // slot 4
    render::HierarchicalObject* GetBoneObject(u32 index) const;  // slot 5
    bool InitPalette_(AofObject*, AsfHandler*);  // slot 6
    bool InitPalette_(AofObject*, void*);  // slot 7
    bool InitPaletteEx_(AofObject*, AsfHandler*);  // slot 8
    void GetAllocSize(u64, u64, u64) const;  // slot 9
    void Assign(u64, u64, u64);  // slot 10
    bool InitPalette(AofObject*, AsfHandler*);
    bool InitPalette(AofObject*, void*);
    bool InitPaletteEx(AofObject*, AsfHandler*);
    bool Init(AofObject*);
    void InitTexturePalette_();
    void Init3rdTexturePalette();
    void AllocPaletteTexture_(s32);
    void AllocUnmanagedPaletteTexture();
    u8 GetSkinMatrixCount(s32 meshset) const;
    void GetVelocityArray(s32) const;
    void GetVelocityArrayBack(s32) const;
    void KickPalette(void*);

    const void* vtable;              // 0x00
    u16 m_boneCount;                 // 0x08: the model's bone count (AofHandler::m_model +0x76)
    u8 m_flags;                      // 0x0a: bit 0 initialized, bit 1 texture palette, bit 2 simple dynamics
    u8 unk_0b;                       // 0x0b
    u8 unk_0c[4];                    // 0x0c
    u8 unk_10[0x30];                 // 0x10
    u16* m_meshsetPaletteBase;       // 0x40: per meshset, its first palette entry (Init)
    void* m_bindPose;                // 0x48: = the handler's m_bindPose
    void* m_paletteTexture[3];       // 0x50: AllocPaletteTexture_ (texture palettes; 0x60 the third)
    u32 m_paletteSize;               // 0x68: the model's palette size (+0x78)
    u32 m_paletteStride;             // 0x6c: 5 (vec4s per entry)
    AofObject* m_object;             // 0x70: the AofObject skinned
};
static_assert(offsetof(SkinMatricesBase, m_boneCount) == 0x08);
static_assert(offsetof(SkinMatricesBase, m_flags) == 0x0a);
static_assert(offsetof(SkinMatricesBase, m_meshsetPaletteBase) == 0x40);
static_assert(offsetof(SkinMatricesBase, m_bindPose) == 0x48);
static_assert(offsetof(SkinMatricesBase, m_paletteTexture) == 0x50);
static_assert(offsetof(SkinMatricesBase, m_paletteSize) == 0x68);
static_assert(offsetof(SkinMatricesBase, m_object) == 0x70);
static_assert(sizeof(SkinMatricesBase) == 0x78);

// Aska::SkinMatrices: the CPU skinning palette: MakeSkinMatrices (slot 2) computes, per bone,
// palette[i] = inverse(object world) * bone world * bind[i] as a Matrix34 (0x30 bytes) and hands the
// palette to KickPalette. Guest size 0x98 (AofHandler::CreateSkinMatrices: operator new(0x98)); layout
// from SkinMatrices::SkinMatrices, GetBoneObject, MakeSkinMatrices (port/decomp/scene/skinning.c). The
// object's inverse world matrix is cached in HierarchicalObject 0x130 (render's m_invWorld; its
// validity is m_hoc.m_flags bit 2).
class SkinMatrices {
public:
    void Ctor();
    void DtorBase();
    void DtorDelete();
    bool MakeSkinMatrices();  // slot 2
    void UpdateSimpleDynamics(void*);  // slot 3
    void GetTexturePaletteMatrices() const;  // slot 4
    render::HierarchicalObject* GetBoneObject(u32 index) const;  // slot 5
    bool InitPalette_(AofObject*, AsfHandler*);  // slot 6
    bool InitPaletteEx_(AofObject*, AsfHandler*);  // slot 8
    void GetAllocSize(u64, u64, u64) const;  // slot 9
    void Assign(u64, u64, u64);  // slot 10

    SkinMatricesBase base;                 // 0x00: vtable _ZTVN4Aska12SkinMatricesE + 0x10
    void* m_skeleton;                      // 0x78: its 0xb0 s32 must be >= 2 for MakeSkinMatrices to run
    HierarchicalObject** m_bones;          // 0x80: m_boneCount entries (GetBoneObject: null past m_boneCount)
    float (*m_bindMatrices)[12];           // 0x88: Matrix34 per bone (the inverse bind pose)
    float (*m_palette)[12];                // 0x90: Matrix34 per bone, the output (128-byte aligned run zeroed first)
};
static_assert(offsetof(SkinMatrices, m_skeleton) == 0x78);
static_assert(offsetof(SkinMatrices, m_bones) == 0x80);
static_assert(offsetof(SkinMatrices, m_bindMatrices) == 0x88);
static_assert(offsetof(SkinMatrices, m_palette) == 0x90);
static_assert(sizeof(SkinMatrices) == 0x98);

// Aska::SkinMatricesSimple: the DirectAofPrimitive variant. Guest data 0x8c (constructor: 0x78, 0x80 u64,
// 0x88 u32); allocation not found.
class SkinMatricesSimple {
public:
    void Ctor();
    void DtorBase();
    void DtorDelete();
    bool MakeSkinMatrices();  // slot 2
    bool InitPalette_(AofObject*, void*);  // slot 7
    void GetAllocSize(u64, u64, u64) const;  // slot 9
    void Assign(u64, u64, u64);  // slot 10

    SkinMatricesBase base;  // 0x00: vtable _ZTVN4Aska18SkinMatricesSimpleE + 0x10
    u64 unk_78;             // 0x78
    u64 unk_80;             // 0x80
    u32 unk_88;             // 0x88
    u8 unk_8c[4];           // 0x8c
};
static_assert(offsetof(SkinMatricesSimple, unk_88) == 0x88);
static_assert(sizeof(SkinMatricesSimple) == 0x90);

// Aska::JointObject: a bone (a HierarchicalObject whose matrix also applies a joint orientation).
// MakeMatrix (slot 21): MatrixCalcFunc(world, position, posture, joint orientation (m_hoc.m_jointOrientation:
// property 15), scale, parent scale (only when the parent's owner has 0x195 bit 0 and m_noParentScale is
// 0), parent world). No constructor or allocation in the lib's exports: data size 0x199 (the bool at 0x198,
// in HierarchicalObject's tail padding), allocation presumably 0x1a0 (unverified).
// vtable (_ZTVN4Aska11JointObjectE, 46 slots = HierarchicalObject's).
class JointObject {
public:
    void DtorDelete();
    u64 GetClassID(s32 depth) const;  // slot 2
    bool Get(u64, void*) const;  // slot 5
    bool Set(u64, const void*);  // slot 6
    void MakeMatrix();  // slot 21

    HierarchicalObject base;   // 0x000
    u8 m_noParentScale;        // 0x198: MakeMatrix: 0 = apply the parent's scale (segment scale compensation off)
    u8 unk_199[7];             // 0x199
};
static_assert(offsetof(JointObject, m_noParentScale) == 0x198);
static_assert(sizeof(JointObject) == 0x1a0);
// ---- The DirectAof drawables (the UI's sprites and text: Framework::Cocos draws through them) -------

// Aska::DirectAofHandler: an AofHandler whose meshes are built at run time (BeginMesh / AddVertex /
// EndMesh, Open / Close, the shape helpers). Guest size 0x380 (CCocosScene::AddSceneRenderer: operator
// new(0x380)); layout from DirectAofHandler::DirectAofHandler, Create (port/decomp/scene/direct_aof.c).
// IsDirectAof (slot 6) returns 1.
class DirectAofHandler {
public:
    void CtorBase();                       // DirectAofHandler()  _ZN4Aska16DirectAofHandlerC2Ev
    bool IsDirectAof() const;              // slot 6
    bool Create(s32 meshsets, bool flag, const char* name);  // operator new(0xd0) model header (name at +0xb0, 31 chars)
    void Open();
    void OnOpen();
    void Close(const MathVector* v, bool b);
    void OnClose(const MathVector* v, bool b);
    void UpdatePrim();
    bool BeginMesh(void* material, s32 a, s32 b);  // Aska::DirectMaterial*
    bool BeginMesh(void* material);
    bool AddMeshset(s32 index, const void* material, s32 a, s32 b);
    void Sync(void* prim, u32 a, u32 b);   // Aska::RenderablePrimitive*
    void EndMesh();
    void SetPrimCount(s32 a, s32 b, s32 c);
    void AddVertex(const MathVector* pos, const MathVector* color, u32 c);
    void* GetIndexBuffer(s32 index, s32* count);
    void* GetVertexBuffer(s32 index, s32* count);
    void FlipBuffer(s32 index);
    void OnAddMeshset(s32 index);
    bool MakeRenderContext(RenderContext* ctx, AofObject* obj, const RENDERINFO* info, RenderPass* pass, void* arg);  // slot 7

    AofHandler base;          // 0x000: vtable _ZTVN4Aska16DirectAofHandlerE + 0x10 (+0xb8 at 0x98, +0xe0 at 0xa0)
    u8 unk_330[0x20];         // 0x330
    u8 m_flags;               // 0x350: bit 0 Create's flag; bits 0-4 = 8 at construction
    u8 unk_351;               // 0x351: 1 at construction
    u8 unk_352;               // 0x352: (a u32 zeroed at construction; Create clears the byte)
    u8 unk_353[5];            // 0x353
    u64 unk_358[4];           // 0x358: 0 at construction
    u32 unk_378;              // 0x378: 1 at construction
    u8 unk_37c[4];            // 0x37c
};
static_assert(offsetof(DirectAofHandler, m_flags) == 0x350);
static_assert(offsetof(DirectAofHandler, unk_358) == 0x358);
static_assert(offsetof(DirectAofHandler, unk_378) == 0x378);
static_assert(sizeof(DirectAofHandler) == 0x380);

// Framework::CDirectAofPrimitiveRenderer: an AofObject that draws a batch of sprites / quads put during the
// frame (Put; the Cocos UI's images, the faders). Guest size 0x7b0 (CCocosScene::AddSceneRenderer:
// operator new(0x7b0)); layout from its constructor, Reset, Reserve, PutCounter (port/decomp/scene/
// direct_aof.c).
class CDirectAofPrimitiveRenderer {
public:
    void CtorBase();                       // _ZN9Framework27CDirectAofPrimitiveRendererC2Ev
    void Initialize(s32 type, u32 count, bool flag);
    void Reserve(u32 count);               // creates m_primitive (operator new(0x410): a DirectAofPrimitiveEx)
    bool IsInitialized() const;
    void Release();
    void Reset();                          // m_putCount = 0, m_dirty = 0 (asserts IsInitialized)
    u32 PutCounter() const;
    bool PreliminarilyPrepare(LightManager* lm);       // slot 79
    bool PrepareForRendering(const RENDERINFO* info);  // slot 80
    void Render(RenderContext* ctx, s32 pass);          // slot 81

    AofObject base;                        // 0x000
    u8 m_material[0xb0];                   // 0x6b0: Aska::DirectMaterial (zeroed with what follows: 0xdc bytes)
    void* m_primitive;                     // 0x760: Framework::DirectAofPrimitiveEx (a DirectAofPrimitive) ("m_pDirectAofHandler")
    u8 unk_768[0x20];                      // 0x768
    u32 m_reserved;                        // 0x788: Reserve's high-water mark
    u32 m_putCount;                        // 0x78c: Put calls this frame (Reset zeroes it)
    u32 unk_790;                           // 0x790
    u32 unk_794;                           // 0x794
    u32 unk_798;                           // 0x798
    s32 m_type;                            // 0x79c: 2 = quads (Reserve: BeginQuadMesh)
    u8 unk_7a0;                            // 0x7a0
    u8 m_flag7a1;                          // 0x7a1: DirectAofHandler::Create's flag
    u8 m_dirty;                            // 0x7a2: Reset clears it
    u8 unk_7a3[0x0d];                      // 0x7a3
};
static_assert(offsetof(CDirectAofPrimitiveRenderer, m_material) == 0x6b0);
static_assert(offsetof(CDirectAofPrimitiveRenderer, m_primitive) == 0x760);
static_assert(offsetof(CDirectAofPrimitiveRenderer, m_reserved) == 0x788);
static_assert(offsetof(CDirectAofPrimitiveRenderer, m_putCount) == 0x78c);
static_assert(offsetof(CDirectAofPrimitiveRenderer, m_type) == 0x79c);
static_assert(offsetof(CDirectAofPrimitiveRenderer, m_dirty) == 0x7a2);
static_assert(sizeof(CDirectAofPrimitiveRenderer) == 0x7b0);

// Framework::CDirectAofTextRenderer: an AofObject that draws the text put during the frame (CCocosLabel::
// DrawSelf -> Put; a font and a UTF-8 text compositor). Guest size 0x830 (CCocosScene::AddSceneRenderer:
// operator new(0x830)); layout from its constructor, Reset, PutCounter (port/decomp/scene/direct_aof.c).
// The put pool is double-buffered: m_putPools[m_putPoolIndex] is the current one.
struct DirectAofTextPutPool {
    void* m_strings;          // +0x00: operator new[](200): 4 entries of 0x30 (a count word before them)
    u32 m_capacity;           // +0x08: 4 at construction (the constructor stores 4 as a u64 over +0x08..+0x0f)
    u32 m_putCount;           // +0x0c: Put calls (PutCounter); Reset zeroes +0x0c..+0x13
    u32 unk_10;               // +0x10
    u32 unk_14;               // +0x14
    u32 unk_18;               // +0x18
    u32 unk_1c;               // +0x1c
};
static_assert(offsetof(DirectAofTextPutPool, m_putCount) == 0x0c);
static_assert(sizeof(DirectAofTextPutPool) == 0x20);

class CDirectAofTextRenderer {
public:
    void CtorBase();                       // _ZN9Framework22CDirectAofTextRendererC2Ev
    bool Initialize(s32 a, void* font, const void* list);  // (int, Aska::FontHandle, CSTLVector<unsigned long> const&)
    void Reserve(u32 count);
    void Release();
    void Reset();                          // the other put pool becomes current, its count zeroed
    u32 PutCounter() const;                // m_putPools[m_putPoolIndex].m_putCount
    u32 CharCount() const;
    bool PreliminarilyPrepare(LightManager* lm);  // slot 79 (builds the glyph meshes: 357 self samples)

    AofObject base;                        // 0x000
    u8 m_font[0x10];                       // 0x6b0: Aska::FontHandle
    const void* m_compositorVtable;        // 0x6c0: Aska::TTextCompositor<Aska::Utf8> (vptr; the compositor runs to 0x7d5)
    u8 m_compositorFont[0x10];             // 0x6c8: Aska::FontHandle
    u8 unk_6d8[0x100];                     // 0x6d8: the compositor's state (zeroed)
    u32 m_pendingPuts;                     // 0x7d8: atomic; Reset swaps the pools when != 0
    u8 unk_7dc[4];                         // 0x7dc
    DirectAofTextPutPool m_putPools[2];    // 0x7e0
    u32 m_putPoolIndex;                    // 0x820
    u8 unk_824[0x0c];                      // 0x824
};
static_assert(offsetof(CDirectAofTextRenderer, m_font) == 0x6b0);
static_assert(offsetof(CDirectAofTextRenderer, m_compositorVtable) == 0x6c0);
static_assert(offsetof(CDirectAofTextRenderer, m_pendingPuts) == 0x7d8);
static_assert(offsetof(CDirectAofTextRenderer, m_putPools) == 0x7e0);
static_assert(offsetof(CDirectAofTextRenderer, m_putPoolIndex) == 0x820);
static_assert(sizeof(CDirectAofTextRenderer) == 0x830);

}  // namespace soa::native::scene

#endif  // SOA_NATIVE_SCENE_LAYOUT_H
