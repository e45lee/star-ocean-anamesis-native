// RenderThread's natives bound, and their live check (render_check.h): a checked request native runs
// for real with t_rtobs set, then the guest original runs on this thread's shadow RenderThread (a private
// 0x50298-byte object with events, a lock and a semaphore of its own) loaded with the state the native
// saw, and the shadow must end in the state the native left. GetStatus is a getter: the original runs on
// the real object right after the native.
//
// Not checked live: ReqCustomCommandBlock / ReqDownloadResourceBlock (a replay would run the block call
// on the render thread a second time; render/thread-block-call compares them with the guest's).
#include <cstring>
#include <memory>
#include <new>
#include <string>

#include "soaruntime/core/cpu.h"
#include "soaruntime/hle/thread.h"
#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/render/render_check.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

void RenderThreadObservation::capture_pre(const RenderThread* rt, s32 read) {
    if (have_pre) return;  // (AddEndRender: PushLocked's)
    have_pre = true;
    pre.status = rt->m_status;
    pre.resetRequested = rt->m_resetRequested;
    pre.gpuWaitRequested = rt->m_gpuWaitRequested;
    pre.exitRequested = rt->m_exitRequested;
    pre.endRenderCount = rt->m_endRenderCount;
    pre.write = rt->m_queue.m_write;
    pre.read = read;
    pre.entry = rt->m_queue.m_entries[pre.write];
}

void RenderThreadObservation::capture_post(const RenderThread* rt) {
    post.status = rt->m_status;
    post.resetRequested = rt->m_resetRequested;
    post.gpuWaitRequested = rt->m_gpuWaitRequested;
    post.exitRequested = rt->m_exitRequested;
    post.endRenderCount = rt->m_endRenderCount;
    post.write = rt->m_queue.m_write;
    post.read = pre.read;
    post.entry = rt->m_queue.m_entries[pre.write];
}

namespace {

constexpr u64 kAll = ~0ull, kLow = 0xffffffffull;

// The argument bits of a request entry the guest defines, by type (the rest is a stack temporary's
// uninitialised bytes in the guest's entry: not compared).
struct ArgMask {
    u64 m[3];
};
ArgMask arg_mask(u8 type) {
    switch (type) {
    case RenderThread::kReqRenderQueue: case RenderThread::kReqFinishRenderTarget: case RenderThread::kReqTemporaryResolve:
    case RenderThread::kReqCallBack: case RenderThread::kReqReloadZCull: case RenderThread::kReqDataTransfer:
    case RenderThread::kReqEnableFastZ: case RenderThread::kReqGnmOcclusionQuery:
        return {{kAll, kAll, kAll}};
    case RenderThread::kReqChangeRenderTarget: return {{kAll, kAll, 0}};
    case RenderThread::kReqEndRender: case RenderThread::kReqOcclusionQueryBegin: case RenderThread::kReqTileRegion:
    case RenderThread::kReqDeviceInit:
        return {{kAll, 0, 0}};
    case RenderThread::kReqExposureScale: return {{kLow, kLow, kAll}};  // the floats' upper words: garbage
    default: return {{0, 0, 0}};  // begin render, occlusion query end, swap
    }
}

// This thread's shadow RenderThread (and a RenderableObject for AddRenderQueue's count).
struct Shadow {
    RenderThread* rt = nullptr;
    RenderableObject* obj = nullptr;
    Shadow() {
        rt = static_cast<RenderThread*>(::operator new(sizeof(RenderThread), std::align_val_t(64)));
        std::memset(rt, 0, sizeof *rt);
        rt->m_wake.Ctor();
        rt->m_wake.Create(false, false);
        rt->m_resetDone.Ctor();
        rt->m_resetDone.Create(false, false);
        hle_host_sem_init((u64)rt->m_queueLock.m_sem.m_sem, 0);
        rt->m_queueLock.m_sem.m_pSem = (u64)rt->m_queueLock.m_sem.m_sem;
        obj = static_cast<RenderableObject*>(::operator new(sizeof(RenderableObject), std::align_val_t(64)));
        std::memset(obj, 0, sizeof *obj);
    }
    // (kept for the thread's life: the semaphore's host object stays registered)
    void load(const RenderThread* real, const RenderThreadObservation::State& s) {
        rt->base.vtable = real->base.vtable;
        rt->m_status = s.status;
        rt->m_resetRequested = s.resetRequested;
        rt->m_gpuWaitRequested = s.gpuWaitRequested;
        rt->m_exitRequested = s.exitRequested;
        rt->m_endRenderCount = s.endRenderCount;
        rt->m_queue.m_write = s.write;
        rt->m_queue.m_read = s.read;
        rt->m_queue.m_entries[s.write] = s.entry;
        rt->m_wake.m_signaled = 0;
        rt->m_wake.m_manualReset = real->m_wake.m_manualReset;
        rt->m_resetDone.m_signaled = 1;
        rt->m_queueLock.m_lock = sync::FastCriticalSection::kFree;
        rt->m_queueLock.m_waiters = sync::FastCriticalSection::kWaiterBias;
    }
};
Shadow& shadow() { return thread_object<Shadow>(); }  // (core/thread_record.h)

std::string compare(const RenderThreadObservation& o, const RenderThread* sh, const RenderableObject* real_obj, const RenderableObject* sh_obj) {
    const auto& p = o.post;
    char m[200];
    auto field = [&](const char* name, long long native, long long guest) {
        snprintf(m, sizeof m, "%s: native %lld, guest %lld", name, native, guest);
        return std::string(m);
    };
    if (sh->m_queue.m_write != p.write) return field("m_write", p.write, sh->m_queue.m_write);
    if (sh->m_status != p.status) return field("m_status", p.status, sh->m_status);
    if (sh->m_endRenderCount != p.endRenderCount) return field("m_endRenderCount", p.endRenderCount, sh->m_endRenderCount);
    if (sh->m_resetRequested != p.resetRequested) return field("m_resetRequested", p.resetRequested, sh->m_resetRequested);
    if (sh->m_gpuWaitRequested != p.gpuWaitRequested) return field("m_gpuWaitRequested", p.gpuWaitRequested, sh->m_gpuWaitRequested);
    if (sh->m_exitRequested != p.exitRequested) return field("m_exitRequested", p.exitRequested, sh->m_exitRequested);
    if ((sh->m_wake.m_signaled != 0) != o.wake_set) return field("m_wake set", o.wake_set, sh->m_wake.m_signaled);
    if ((sh->m_resetDone.m_signaled == 0) != o.reset_done_reset) return field("m_resetDone reset", o.reset_done_reset, sh->m_resetDone.m_signaled == 0);
    const RENDER_REQUEST& ge = sh->m_queue.m_entries[o.pre.write];
    if (ge.m_type != p.entry.m_type) return field("entry type", p.entry.m_type, ge.m_type);
    const ArgMask mask = arg_mask(ge.m_type);
    for (int k = 0; k < 3; k++) {
        u64 n = p.entry.m_arg[k], g = ge.m_arg[k];
        if (k == 0 && ge.m_type == RenderThread::kReqRenderQueue && g == (u64)sh_obj) g = (u64)real_obj;  // the shadow's object
        if ((n ^ g) & mask.m[k]) {
            snprintf(m, sizeof m, "entry (type %u) arg %d: native %#llx, guest %#llx", ge.m_type, k, (unsigned long long)n, (unsigned long long)g);
            return m;
        }
    }
    return {};
}

// A request native, live-checked: `fn` is the member's HostFn (wrap_method), `has_result` whether the
// guest returns a bool.
void checked_request(Cpu& c, live::RunBothFamily::Fn& f, HostFn fn, bool has_result, bool render_queue) {
    if (__builtin_expect(!fam().due(f), 1)) return fn(c);
    live::RunBothFamily::Scope scope;
    const u64 x[4] = {c.x(0), c.x(1), c.x(2), c.x(3)};
    const float s0 = c.s(0), s1 = c.s(1);
    auto* rt = reinterpret_cast<RenderThread*>(x[0]);
    auto* real_obj = render_queue ? reinterpret_cast<RenderableObject*>(x[1]) : nullptr;
    RenderThreadObservation obs;
    t_rtobs = &obs;
    fn(c);
    t_rtobs = nullptr;
    const u64 result = c.x(0);
    if (!obs.have_pre) {
        fam().result(f, live::RunBothFamily::Outcome::Skipped, "no observation");
        return;
    }
    Shadow& sh = shadow();
    sh.load(rt, obs.pre);
    sh.obj->m_renderQueued = obs.queued_before;
    GuestArgs a;
    a.i((u64)sh.rt).i(render_queue ? (u64)sh.obj : x[1]).i(x[2]).i(x[3]).f(s0).f(s1);
    const u64 g = guest_call(f.orig, a).x0;
    std::string why = compare(obs, sh.rt, real_obj, sh.obj);
    if (why.empty() && has_result && (g & 0xff) != (result & 0xff))
        why = "result: native " + std::to_string(result & 0xff) + ", guest " + std::to_string(g & 0xff);
    if (why.empty() && render_queue && sh.obj->m_renderQueued != obs.queued_before + 1)
        why = "m_renderQueued: guest " + std::to_string(sh.obj->m_renderQueued) + ", expected " + std::to_string(obs.queued_before + 1);
    fam().result(f, why.empty() ? live::RunBothFamily::Outcome::Ok : live::RunBothFamily::Outcome::Mismatch, why);
}

#define RT_SYM(name) "_ZN4Aska12RenderThread" name
// One bound request native: its Fn (counters, trampoline) and HostFn.
#define RT_REQUEST(id, sym, member, has_result, queue)                                                      \
    live::RunBothFamily::Fn f##id(fam(), sym);                                                              \
    void Host##id(Cpu& c) { checked_request(c, f##id, wrap_method<member>(), has_result, queue); }          \
    NATIVE_FUNCTION_ORIG(sym, Host##id, "render: RenderThread::" #id, &f##id.orig)

RT_REQUEST(AddRenderQueue, RT_SYM("14AddRenderQueueEPNS_16RenderableObjectEPNS_13RenderContextEi"), &RenderThread::AddRenderQueue, true, true);
RT_REQUEST(AddChangeRenderTarget, RT_SYM("21AddChangeRenderTargetEjPNS_21MULTIPASS_ENVIRONMENTE"), &RenderThread::AddChangeRenderTarget, true, false);
RT_REQUEST(AddReloadZCull, RT_SYM("14AddReloadZCullEv"), &RenderThread::AddReloadZCull, true, false);
RT_REQUEST(AddEnableGnmOcclusionQuery, RT_SYM("26AddEnableGnmOcclusionQueryEb"), &RenderThread::AddEnableGnmOcclusionQuery, true, false);
RT_REQUEST(AddExposureScale, RT_SYM("16AddExposureScaleEff"), &RenderThread::AddExposureScale, true, false);
RT_REQUEST(AddEnableFastZ, RT_SYM("14AddEnableFastZEb"), &RenderThread::AddEnableFastZ, true, false);
RT_REQUEST(AddFinishRenderTarget, RT_SYM("21AddFinishRenderTargetEjii"), &RenderThread::AddFinishRenderTarget, true, false);
RT_REQUEST(AddTemporaryResolve, RT_SYM("19AddTemporaryResolveEPNS_16RenderableObjectEii"), &RenderThread::AddTemporaryResolve, true, false);
RT_REQUEST(AddBeginRender, RT_SYM("14AddBeginRenderEv"), &RenderThread::AddBeginRender, true, false);
RT_REQUEST(AddEndRender, RT_SYM("12AddEndRenderEPNS_7INotifyE"), &RenderThread::AddEndRender, true, false);
RT_REQUEST(AddCallBack, RT_SYM("11AddCallBackEPFvmmEmm"), &RenderThread::AddCallBack, true, false);
RT_REQUEST(AddDataTransfer, RT_SYM("15AddDataTransferEPvS1_j"), &RenderThread::AddDataTransfer, true, false);
RT_REQUEST(ExecutePendingTileRegionOperationByAddress, RT_SYM("42ExecutePendingTileRegionOperationByAddressEPv"),
           &RenderThread::ExecutePendingTileRegionOperationByAddress, false, false);
RT_REQUEST(AddOcclusionQueryBegin, RT_SYM("22AddOcclusionQueryBeginEPj"), &RenderThread::AddOcclusionQueryBegin, true, false);
RT_REQUEST(AddOcclusionQueryEnd, RT_SYM("20AddOcclusionQueryEndEv"), &RenderThread::AddOcclusionQueryEnd, true, false);
RT_REQUEST(ReqSwap, RT_SYM("7ReqSwapEv"), &RenderThread::ReqSwap, false, false);
RT_REQUEST(ReqDeviceInit, RT_SYM("13ReqDeviceInitEv"), &RenderThread::ReqDeviceInit, false, false);
RT_REQUEST(ReqDeviceReset, RT_SYM("14ReqDeviceResetEv"), &RenderThread::ReqDeviceReset, false, false);
RT_REQUEST(ReqExit, RT_SYM("7ReqExitEv"), &RenderThread::ReqExit, false, false);
RT_REQUEST(ReqGpuWait, RT_SYM("10ReqGpuWaitEv"), &RenderThread::ReqGpuWait, false, false);

// GetStatus: the status under the lock, then (status 2, nothing queued) the wait for the next request
// (render_thread.cpp). Checked as a getter before the wait.
live::RunBothFamily::Fn fGetStatus(fam(), "_ZNK4Aska12RenderThread9GetStatusEv");
void HostGetStatus(Cpu& c) {
    const auto* rt = reinterpret_cast<const RenderThread*>(c.x(0));
    u8 st = rt->GetStatus();
    if (__builtin_expect(fam().due(fGetStatus), 0)) {
        live::RunBothFamily::Scope scope;
        u8 g = (u8)guest_call(fGetStatus.orig, {(u64)rt});
        if (g == st) {
            fam().result(fGetStatus, live::RunBothFamily::Outcome::Ok);
        } else {
            u8 st2 = rt->GetStatus(), g2 = (u8)guest_call(fGetStatus.orig, {(u64)rt});
            fam().result(fGetStatus, st2 == g2 ? live::RunBothFamily::Outcome::Race : live::RunBothFamily::Outcome::Mismatch,
                         "native " + std::to_string(st) + ", guest " + std::to_string(g));
        }
    }
    if (st == RenderThread::kStatusRendering) rt->WaitForRequest();
    c.set_x(0, st);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZNK4Aska12RenderThread9GetStatusEv", HostGetStatus, "render: RenderThread::GetStatus (+ the wait for a request)", &fGetStatus.orig);
NATIVE_METHOD("_ZN4Aska12RenderThread21ReqCustomCommandBlockEPFvmmEmm", &RenderThread::ReqCustomCommandBlock, "render: RenderThread::ReqCustomCommandBlock");
NATIVE_METHOD("_ZN4Aska12RenderThread24ReqDownloadResourceBlockEPNS_11GpuResourceE", &RenderThread::ReqDownloadResourceBlock,
              "render: RenderThread::ReqDownloadResourceBlock");

}  // namespace soa::native::render
