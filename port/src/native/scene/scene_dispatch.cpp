// The object manager's job dispatcher (Aska::ObjectManagerJobDispatcher) and the job bodies of its worker
// (Aska::ObjectManagerWorkerThread), native: every posted job runs at once on the posting thread.
//
// The guest (port/decomp/scene/object_manager.c) has one worker thread in 3.7.0. Dispatch_X posts job X
// to it when it idles in mode X and returns false otherwise; the callers (OnPrePaint, OnPostPaint's
// TraversePaintingList*, Prerender's Multithread*Culling, PrepareMatrices) call it again and again
// while they scan the worker's 2-bit results, and the dispatcher's ChangeMode / Sleep move the worker
// between modes through its FastCriticalSection: about half of scene's guest time was this polling
// (README "The job dispatcher"). Here Dispatch_X stores the job's parameters in the worker as the guest
// does and runs the job's body (the Run* members: one iteration of the worker's Handler_X loop) right
// away, so it always returns true with every result in place. That is one of the guest's own schedules
// (a worker that finishes before the poster looks again): the callers scan the results in index order,
// so the render queue's order doesn't depend on the schedule, and the callers of jobs 4 to 6 already run
// those bodies themselves on the posting thread when the worker is busy. The worker thread stays parked
// in mode 7 (its construction state, an Event wait) because ChangeMode / Sleep no longer wake it; the
// destructor (guest code) still stops it.
#include <cstring>

#include "core/cpu.h"
#include "native/common/guest_std.h"
#include "native/scene/scene_check.h"
#include "native/scene/scene_dispatch.h"
#include "native/scene/scene_layout.h"

namespace soa::native::scene {

namespace {

// AArch64's SDIV: x / 0 = 0 and INT_MIN / -1 = INT_MIN (C++ traps or is undefined there).
s32 arm_sdiv(s32 n, s32 d) {
    if (d == 0) return 0;
    if (d == -1) return (s32)(0u - (u32)n);
    return n / d;
}

u16 shadow_flags(const RenderableObject* o) {
    u16 v;
    std::memcpy(&v, o->m_shadowFlags, 2);
    return v;
}
void set_shadow_flags(RenderableObject* o, u16 v) { std::memcpy(o->m_shadowFlags, &v, 2); }

}  // namespace

// ---- guest calls ---------------------------------------------------------------------------------

u64 vcall(const void* obj, int slot, std::initializer_list<u64> rest) {
    const u64* vt = *reinterpret_cast<const u64* const*>(obj);  // (the guest vptr: the object's first word)
    u64 a[8] = {(u64)obj};
    size_t n = 1;
    for (u64 v : rest) a[n++] = v;
    return job_call(vt[slot], a, n);
}

const GuestFns& guest_fns() {
    static const GuestFns f = {
        guest::sym("_ZN4Aska13ObjectManager16MakePaintingListEi"),
        guest::sym("_ZN4Aska13ObjectManager25MakePaintingListMultipassEi"),
        guest::sym("_ZN4Aska13ObjectManager22MakePaintingListShadowEi"),
        guest::sym("_ZN4Aska13ObjectManager20MakePaintingListPostEv"),
        guest::sym("_ZN4Aska13ObjectManager18ViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectEiiPm"),
        guest::sym("_ZN4Aska13ObjectManager21SubViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectEiiPm"),
        guest::sym("_ZN4Aska13ObjectManager16OcclusionCullingEPNS_6CameraEiibPPNS_16RenderableObjectEiiPm"),
        guest::sym("_ZN4Aska13ObjectManager10DetectLIBLEPPNS_16RenderableObjectEii"),
        guest::sym("_ZN4Aska6Global16m_pObjectManagerE"),
    };
    return f;
}

// ---- the worker's job bodies ---------------------------------------------------------------------

void ObjectManagerWorkerThread::SetResult(s32 index, u64 result) {
    u64* word = m_resultBits + (index >> 5);  // (re-read per object, as the guest does)
    __atomic_fetch_or(word, result << ((index & 31) * 2), __ATOMIC_SEQ_CST);
}

// Handler_MakePaintingList: the painting list of one pass (kind 0), multipass layer (1), shadow layer (2)
// or the post-process list (3); the index goes in w1 for all four (MakePaintingListPost takes none).
void ObjectManagerWorkerThread::RunMakePaintingList() {
    const GuestFns& g = guest_fns();
    u64 fn;
    switch ((u32)m_paintingListKind) {
    case 0: fn = g.makePaintingList; break;
    case 1: fn = g.makePaintingListMultipass; break;
    case 2: fn = g.makePaintingListShadow; break;
    case 3: fn = g.makePaintingListPost; break;
    default: return;
    }
    const u64 a[] = {(u64)m_objectManager, (u64)(u32)m_paintingListIndex};
    job_call(fn, a, 2);
}

// Handler's case 2 (= Handler_PreliminarilyPrepare): PreliminarilyPrepare (slot 79) on the batch's objects
// not yet marked prepared this frame (m_shadowFlags bit 0 clear): result 2 when it returns true, else 3;
// the others are 1 (skipped).
void ObjectManagerWorkerThread::RunPreliminarilyPrepare() {
    const s32 first = m_prelimFirst, last = m_prelimLast;
    RenderableObject** objects = m_prelimObjects;
    for (s64 i = first; i <= last; i++) {
        RenderableObject* o = objects[i - first];
        if ((o->m_shadowFlags[0] & 1) == 0) {
            bool ok = vcall(o, kSlotPreliminarilyPrepare, {(u64)m_lightManager}) & 1;
            SetResult((s32)i, ok ? 2 : 3);
        } else {
            SetResult((s32)i, 1);
        }
    }
}

// Handler_PrepareForRendering: PrepareForRendering (slot 80) with the worker's RENDERINFO copy on the
// batch's objects that PreliminarilyPrepare marked (m_shadowFlags bit 0 set); before each call the copy
// gets the object's context count (m_contextsWanted / m_contextDivisor, SDIV, truncated to 16 bits) and
// its next RenderContext, and with kind 1 its camera (the worker's default when it has none).
void ObjectManagerWorkerThread::RunPrepareForRendering() {
    const s32 first = m_prepareFirst, last = m_prepareLast, kind = m_prepareKind;
    RenderableObject** objects = m_prepareObjects;
    if (kind != 0 && kind != 1) return;
    for (s64 i = first; i <= last; i++) {
        RenderableObject* o = objects[i - first];
        if ((o->m_shadowFlags[0] & 1) == 0) {
            SetResult((s32)i, 1);
            continue;
        }
        if (kind == 1) m_renderInfo.m_camera = o->m_camera ? o->m_camera : m_defaultCamera;
        __atomic_thread_fence(__ATOMIC_SEQ_CST);  // (DMB ISH)
        m_renderInfo.m_contextCount = (u16)arm_sdiv(o->m_contextsWanted, o->m_contextDivisor);
        m_renderInfo.m_contexts = o->m_contexts + o->m_contextsUsed;
        bool ok = vcall(o, kSlotPrepareForRendering, {(u64)&m_renderInfo}) & 1;
        SetResult((s32)i, ok ? 2 : 3);
    }
}

// Handler_ViewFrustumCulling: the culling of objects m_cullFirst..m_cullLast into the result bits, by kind.
void ObjectManagerWorkerThread::RunViewFrustumCulling() {
    const GuestFns& g = guest_fns();
    switch (m_cullKind) {
    case 0:
    case 1: {
        const u64 a[] = {(u64)m_objectManager, (u64)m_cullCamera, (u64)(u32)m_cullArg1, (u64)(u32)m_cullArg2,
                         (u64)m_cullObjects,   (u64)(u32)m_cullFirst, (u64)(u32)m_cullLast, (u64)m_resultBits};
        job_call(m_cullKind == 0 ? g.viewFrustumCulling : g.subViewFrustumCulling, a, 8);
        break;
    }
    case 2: {  // (bool false in w4; the result bits are the ninth argument, on the stack)
        const u64 a[] = {(u64)m_objectManager, (u64)m_cullCamera, (u64)(u32)m_cullArg1, (u64)(u32)m_cullArg2, 0,
                         (u64)m_cullObjects,   (u64)(u32)m_cullFirst, (u64)(u32)m_cullLast, (u64)m_resultBits};
        job_call(g.occlusionCulling, a, 9);
        break;
    }
    default: break;  // (3: Dispatch_RenderingDecided's kind, which no handler case takes)
    }
}

// Handler's case 5 (= Handler_DetectLIBL).
void ObjectManagerWorkerThread::RunDetectLIBL() {
    const u64 a[] = {(u64)m_objectManager, (u64)m_liblObjects, (u64)(u32)m_liblFirst, (u64)(u32)m_liblLast};
    job_call(guest_fns().detectLIBL, a, 4);
}

// One object's per-frame reset (Handler_ResetSystemFlags' loop body; PrepareMatrices runs the same when
// the dispatcher refuses the job).
void ResetObjectSystemFlags(RenderableObject* o) {
    o->m_renderFlags &= 0xdfffffbfu;
    set_shadow_flags(o, shadow_flags(o) & 0xfefe);
    o->m_contextDivisor = 0;
    o->m_contexts = nullptr;
    o->m_contextsUsed = 0;
    vcall(o, kSlotResetDynamicShaderModifier);
    o->m_frameScratch230[0] = o->m_frameScratch230[1] = 0;
    o->unk_1f8 = o->unk_200 = 0;
    o->m_frameScratch1e8[0] = o->m_frameScratch1e8[1] = 0;
    set_shadow_flags(o, shadow_flags(o) & 0xfff9);
    const u32 flags = o->m_renderFlags;
    o->m_renderFlags = flags | 0x124;
    if (flags & 0x6081) {
        if (flags & (1u << 25)) vcall(o, kSlotCheckRenderContexts);
        if (flags & (1u << 21)) vcall(o, kSlotRoutineProcedure);
    }
}

// Handler_ResetSystemFlags: m_resetFirst .. m_resetLast along the task links (HierarchicalObject's
// next at +0x10), stopping early at the object manager's own list head (Global::m_pObjectManager + 8).
void ObjectManagerWorkerThread::RunResetSystemFlags() {
    const u64 head = *reinterpret_cast<const u64*>(guest_fns().globalObjectManager) + 8;
    RenderableObject* o = m_resetFirst;
    RenderableObject* const last = m_resetLast;
    for (;;) {
        ResetObjectSystemFlags(o);
        if (o == last) break;
        o = next_task(o);
        if (reinterpret_cast<u64>(o) == head) break;
    }
}

// ---- the dispatcher ------------------------------------------------------------------------------

ObjectManagerWorkerThread* ObjectManagerJobDispatcher::InlineWorker(bool exceptRenderThread) {
    for (s32 i = 0; i < m_workerCount; i++)
        if (!exceptRenderThread || i != m_exceptIndex) return &m_workers[i];
    return nullptr;
}

bool ObjectManagerJobDispatcher::WantsModeChange(const ObjectManagerWorkerThread& w, s32 mode) {
    return w.m_running && w.m_waiting && !w.m_modeChangePending && w.m_job == 0 && w.m_nextMode < 0 && w.m_mode != mode;
}

// ChangeMode(m): the guest waits until no worker has a job (none ever has one here), notes the worker
// count, keeps the "except" worker idle for mode 3 when there is one (never: m_exceptIndex is -1), and
// asks each worker to switch. The workers stay parked: every job runs on the posting thread.
void ObjectManagerJobDispatcher::ChangeMode(s32 mode) {
    m_workerCountSeen = m_workerCount;
    if (mode == 3 && m_exceptIndex >= 0) m_exceptMode = 1;
    else if (m_exceptMode) m_exceptMode = 0;
}

void ObjectManagerJobDispatcher::RetryChangeMode(s32 mode) {
    for (s32 i = 0; i < m_workerCount; i++)
        if (WantsModeChange(m_workers[i], mode)) ChangeMode(mode);
}

void ObjectManagerJobDispatcher::RetryChangeModeExceptRenderThread(s32 mode) {
    for (s32 i = 0; i < m_workerCount; i++)
        if (i != m_exceptIndex && WantsModeChange(m_workers[i], mode)) ChangeMode(mode);
}

// WaitIdle / WaitAllIssued: the guest spins (Thread::Switch) until no worker has a job: none has one.
void ObjectManagerJobDispatcher::WaitIdle() {}
void ObjectManagerJobDispatcher::WaitAllIssued() {}
// Sleep: WaitIdle, then every worker to mode 7: they are there.
void ObjectManagerJobDispatcher::Sleep() {}

void ObjectManagerJobDispatcher::SetPreliminarilyPrepareBasicParameter(LightManager* lm, u64* resultBits) {
    for (s32 i = 0; i < m_workerCount; i++) {
        m_workers[i].m_lightManager = lm;
        m_workers[i].m_resultBits = resultBits;
    }
}

void ObjectManagerJobDispatcher::SetPrepareForRenderingBasicParameter(const RENDERINFO* info, u64* resultBits, Camera* camera) {
    for (s32 i = 0; i < m_workerCount; i++) {
        m_workers[i].m_renderInfo = *info;
        m_workers[i].m_defaultCamera = camera;
        m_workers[i].m_resultBits = resultBits;
    }
}

void ObjectManagerJobDispatcher::SetViewFrustumCullingBasicParameter(Camera* camera, s32 a1, s32 a2, RenderableObject** objects, u64* resultBits) {
    for (s32 i = 0; i < m_workerCount; i++) {
        ObjectManagerWorkerThread& w = m_workers[i];
        w.m_cullCamera = camera;
        w.m_cullArg1 = a1;
        w.m_cullArg2 = a2;
        w.m_cullObjects = objects;
        w.m_resultBits = resultBits;
    }
}

void ObjectManagerJobDispatcher::SetDetectLIBLBasicParameter(RenderableObject** objects) {
    for (s32 i = 0; i < m_workerCount; i++) m_workers[i].m_liblObjects = objects;
}

// The Dispatch_* forms: the guest's parameter stores, then the job's body. Without a worker the guest's
// Dispatch_MakePaintingList spins for ever and the others return false; here they return false (3.7.0
// always has one).
void ObjectManagerJobDispatcher::Dispatch_MakePaintingList(s32 kind, s32 index) {
    ObjectManagerWorkerThread* w = InlineWorker(false);
    if (!w) return;
    w->m_paintingListKind = kind;
    w->m_paintingListIndex = index;
    w->RunMakePaintingList();
}

bool ObjectManagerJobDispatcher::Dispatch_PreliminarilyPrepare(RenderableObject** objects, s32 first, s32 last) {
    ObjectManagerWorkerThread* w = InlineWorker(false);
    if (!w) return false;
    w->m_prelimObjects = objects;
    w->m_prelimFirst = first;
    w->m_prelimLast = last;
    w->RunPreliminarilyPrepare();
    return true;
}

bool ObjectManagerJobDispatcher::Dispatch_PrepareForRendering(s32 kind, RenderableObject** objects, u64 firstLast) {
    ObjectManagerWorkerThread* w = InlineWorker(m_exceptIndex >= 0);
    if (!w) return false;
    w->m_prepareKind = kind;
    w->m_prepareObjects = objects;
    w->m_prepareFirst = (s32)firstLast;
    w->m_prepareLast = (s32)(firstLast >> 32);
    w->RunPrepareForRendering();
    return true;
}

bool ObjectManagerJobDispatcher::Dispatch_ViewFrustumCulling(s32 kind, s32 first, s32 last) {
    ObjectManagerWorkerThread* w = InlineWorker(false);
    if (!w) return false;
    w->m_cullKind = kind;
    w->m_cullFirst = first;
    w->m_cullLast = last;
    w->RunViewFrustumCulling();
    return true;
}

bool ObjectManagerJobDispatcher::Dispatch_DetectLIBL(s32 first, s32 last) {
    ObjectManagerWorkerThread* w = InlineWorker(false);
    if (!w) return false;
    w->m_liblFirst = first;
    w->m_liblLast = last;
    w->RunDetectLIBL();
    return true;
}

bool ObjectManagerJobDispatcher::Dispatch_ResetSystemFlags(RenderableObject* first, RenderableObject* last) {
    ObjectManagerWorkerThread* w = InlineWorker(false);
    if (!w) return false;
    w->m_resetFirst = first;
    w->m_resetLast = last;
    w->RunResetSystemFlags();
    return true;
}

}  // namespace soa::native::scene
