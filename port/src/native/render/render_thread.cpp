// Aska::RenderThread's request side (port/decomp/render/render_thread.c): the Add* / Req* that put
// requests in the render queue (a ring of RENDER_REQUESTs in the object) or set the thread's flags, and
// GetStatus, which the render thread polls. The thread itself (Handler, Render: the whole GL frame) stays
// guest code; the ring and every field are the guest's, in place, so guest code and these natives share
// them as the guest's own threads do (m_queueLock is sync's FastCriticalSection, the events sync's).
//
// The one change of mechanism (port/PLAN.md task 6, render): the thread's Handler loops GetStatus ->
// Render while the status is 2 ("rendering"), and Render returns at once when the ring is empty, so
// between two requests of a frame the thread spun through GetStatus (831 guest self samples, the
// FastCriticalSection's LL/SC loops) and Handler. GetStatus now waits when it would return 2 with nothing
// to do (the ring empty, no block call): until a request is published (every producer is a native here
// and wakes it) or 2 ms pass (the safety net: a guest producer that isn't, if any, delays the thread by
// at most that), then returns the status it read, exactly as before. The ring stays authoritative: the
// wait only ends early; it is re-checked under no assumption about what woke it.
//
// Live check (soa --live-check render): render_thread_check.cpp.
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>

#include "soaruntime/core/cpu.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/render/render_check.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

namespace {

inline void fence() { __atomic_thread_fence(__ATOMIC_SEQ_CST); }
inline s32 load(const s32& v) { return __atomic_load_n(&v, __ATOMIC_ACQUIRE); }
inline void store(s32& v, s32 x) { __atomic_store_n(&v, x, __ATOMIC_RELEASE); }
inline s32 next_index(s32 i) { return (u32)i + 1 < 0x2001 ? i + 1 : 0; }

// The render thread's wakeup: a sequence number every producer bumps after publishing, and a host
// condition variable for the thread waiting in GetStatus (one RenderThread exists; the state is
// global, a wakeup of another one's waiter is harmless).
struct RequestSignal {
    std::mutex m;
    std::condition_variable cv;
    std::atomic<u32> seq{0};
    std::atomic<s32> waiters{0};
};
RequestSignal& signal() {
    static RequestSignal s;
    return s;
}

void wake_render_thread() {
    RequestSignal& s = signal();
    s.seq.fetch_add(1, std::memory_order_seq_cst);
    if (s.waiters.load(std::memory_order_seq_cst) != 0) {
        std::lock_guard<std::mutex> l(s.m);
        s.cv.notify_all();
    }
}

}  // namespace

thread_local RenderThreadObservation* t_rtobs = nullptr;

// ---- the shared steps ----

bool RenderThread::QueueEmpty() const {
    return next_index(load(m_queue.m_read)) == load(m_queue.m_write);
}

// Appends a request (m_queueLock held): refused when m_write has reached m_read (the slot the reader
// holds back); else the entry, a barrier, m_write advanced, and an idle thread (status != 2) is set to
// rendering and woken through m_wake. The entry's other bytes (the guest copies a stack temporary's
// uninitialised bytes there) are zero.
bool RenderThread::PushLocked(u8 type, u64 a0, u64 a1, u64 a2) {
    const s32 read = load(m_queue.m_read);
    if (t_rtobs) t_rtobs->capture_pre(this, read);
    const s32 w = m_queue.m_write;
    bool ok = false;
    if (read != w) {
        RENDER_REQUEST& e = m_queue.m_entries[w];
        e = RENDER_REQUEST{};
        e.m_type = type;
        e.m_arg[0] = a0;
        e.m_arg[1] = a1;
        e.m_arg[2] = a2;
        fence();
        store(m_queue.m_write, next_index(w));
        if (m_status != kStatusRendering) {
            m_status = kStatusRendering;
            m_wake.Set();
            if (t_rtobs) t_rtobs->wake_set = true;
        }
        ok = true;
    }
    if (t_rtobs) t_rtobs->capture_post(this);
    return ok;
}

bool RenderThread::Push(u8 type, u64 a0, u64 a1, u64 a2) {
    m_queueLock.Enter();
    bool ok = PushLocked(type, a0, a1, a2);
    m_queueLock.Leave();
    if (ok) wake_render_thread();
    return ok;
}

// ReqDeviceReset / ReqExit / ReqGpuWait: the flag and m_wake under the lock (the thread reads the
// flags on its idle path).
void RenderThread::RequestFlag(u8 RenderThread::*flag) {
    m_queueLock.Enter();
    if (t_rtobs) t_rtobs->capture_pre(this, load(m_queue.m_read));
    this->*flag = 1;
    m_wake.Set();
    if (t_rtobs) t_rtobs->wake_set = true;
    if (flag == &RenderThread::m_resetRequested) {
        m_resetDone.Reset();
        if (t_rtobs) t_rtobs->reset_done_reset = true;
    }
    if (t_rtobs) t_rtobs->capture_post(this);
    m_queueLock.Leave();
    wake_render_thread();
}

// GetStatus's wait (the render thread, status 2): while the ring is empty and no block call is pending,
// until a producer's wakeup or 2 ms.
void RenderThread::WaitForRequest() const {
    RequestSignal& s = signal();
    s.waiters.fetch_add(1, std::memory_order_seq_cst);
    const u32 seq = s.seq.load(std::memory_order_seq_cst);
    if (QueueEmpty() && __atomic_load_n(&m_blockCall, __ATOMIC_ACQUIRE) == 0) {
        ProfNativeWait wait;
        std::unique_lock<std::mutex> l(s.m);
        s.cv.wait_for(l, std::chrono::milliseconds(2), [&] { return s.seq.load(std::memory_order_seq_cst) != seq; });
    }
    s.waiters.fetch_sub(1, std::memory_order_seq_cst);
}

// ---- the guest members ----

u8 RenderThread::GetStatus() const {
    auto& lock = const_cast<sync::FastCriticalSection&>(m_queueLock);
    lock.Enter();
    const u8 status = m_status;
    lock.Leave();
    return status;
}

// Lock-free (the guest's: one producer, the painting traversal): the object's queued count first, even
// when the ring is full; m_write advanced only if the reader hasn't caught up meanwhile (it can't: the
// reader stops one short of m_write).
bool RenderThread::AddRenderQueue(RenderableObject* obj, RenderContext* ctx, s32 pass) {
    const s32 queued = __atomic_fetch_add(&obj->m_renderQueued, 1, __ATOMIC_SEQ_CST);
    const s32 read = load(m_queue.m_read);
    if (t_rtobs) {
        t_rtobs->capture_pre(this, read);
        t_rtobs->queued_before = queued;
    }
    const s32 w = m_queue.m_write;
    if (read == w) {
        if (t_rtobs) t_rtobs->capture_post(this);
        return false;
    }
    RENDER_REQUEST& e = m_queue.m_entries[w];
    e.m_type = kReqRenderQueue;
    e.m_arg[0] = (u64)obj;
    e.m_arg[1] = (u64)ctx;
    e.m_arg[2] = (u64)(s64)pass;
    fence();
    if (load(m_queue.m_read) != m_queue.m_write) store(m_queue.m_write, next_index(m_queue.m_write));
    fence();
    if (t_rtobs) t_rtobs->capture_post(this);
    wake_render_thread();
    return true;
}

bool RenderThread::AddChangeRenderTarget(u32 id, void* env) { return Push(kReqChangeRenderTarget, id, (u64)env, 0); }
bool RenderThread::AddReloadZCull() { return Push(kReqReloadZCull, 0, 0, 0); }
bool RenderThread::AddEnableGnmOcclusionQuery(bool on) { return Push(kReqGnmOcclusionQuery, on, 0, 0); }
bool RenderThread::AddExposureScale(float a, float b) {
    u32 ba, bb;
    std::memcpy(&ba, &a, 4);
    std::memcpy(&bb, &b, 4);
    return Push(kReqExposureScale, ba, bb, 0);
}
bool RenderThread::AddEnableFastZ(bool on) { return Push(kReqEnableFastZ, on, 0, 0); }
bool RenderThread::AddFinishRenderTarget(u32 id, s32 a, s32 b) { return Push(kReqFinishRenderTarget, id, (u64)(s64)a, (u64)(s64)b); }
bool RenderThread::AddTemporaryResolve(RenderableObject* obj, s32 a, s32 b) {
    return Push(kReqTemporaryResolve, (u64)obj, (u64)(s64)a, (u64)(s64)b);
}
bool RenderThread::AddBeginRender() { return Push(kReqBeginRender, 0, 0, 0); }

// The end of a frame's requests: m_endRenderCount counts it even when the ring is full.
bool RenderThread::AddEndRender(void* notify) {
    m_queueLock.Enter();
    bool ok = PushLocked(kReqEndRender, (u64)notify, 0, 0);
    m_endRenderCount++;
    if (t_rtobs) t_rtobs->capture_post(this);
    m_queueLock.Leave();
    if (ok) wake_render_thread();
    return ok;
}

bool RenderThread::AddCallBack(void (*fn)(u64, u64), u64 a, u64 b) { return Push(kReqCallBack, (u64)fn, a, b); }
bool RenderThread::AddDataTransfer(void* dst, void* src, u32 size) { return Push(kReqDataTransfer, (u64)dst, (u64)src, size); }
void RenderThread::ExecutePendingTileRegionOperationByAddress(void* p) { Push(kReqTileRegion, (u64)p, 0, 0); }
bool RenderThread::AddOcclusionQueryBegin(u32* result) { return Push(kReqOcclusionQueryBegin, (u64)result, 0, 0); }
bool RenderThread::AddOcclusionQueryEnd() { return Push(kReqOcclusionQueryEnd, 0, 0, 0); }
void RenderThread::ReqSwap() { Push(kReqSwap, 0, 0, 0); }
void RenderThread::ReqDeviceInit() { Push(kReqDeviceInit, 0, 0, 0); }
void RenderThread::ReqDeviceReset() { RequestFlag(&RenderThread::m_resetRequested); }
void RenderThread::ReqExit() { RequestFlag(&RenderThread::m_exitRequested); }
void RenderThread::ReqGpuWait() { RequestFlag(&RenderThread::m_gpuWaitRequested); }

// A function run on the render thread while the caller waits (one caller at a time: m_blockCallCs).
void RenderThread::ReqCustomCommandBlock(void (*fn)(u64, u64), u64 a, u64 b) {
    m_blockCallCs.Enter();
    m_blockCallDone.Reset();
    m_blockCallArg[0] = a;
    m_blockCallArg[1] = b;
    __atomic_store_n(&m_blockCall, (u64)fn, __ATOMIC_RELEASE);
    m_wake.Set();
    wake_render_thread();
    m_blockCallDone.Wait(0);
    m_blockCallCs.Leave();
}

// DownloadResource(resource, &result) on the render thread; its result byte.
bool RenderThread::ReqDownloadResourceBlock(void* resource) {
    static const u64 download = guest::sym("_Z16DownloadResourcemm");
    alignas(8) u8 result[8] = {};
    m_blockCallCs.Enter();
    m_blockCallDone.Reset();
    m_blockCallArg[0] = (u64)resource;
    m_blockCallArg[1] = (u64)result;
    __atomic_store_n(&m_blockCall, download, __ATOMIC_RELEASE);
    m_wake.Set();
    wake_render_thread();
    m_blockCallDone.Wait(0);
    m_blockCallCs.Leave();
    return result[0] != 0;
}

}  // namespace soa::native::render
