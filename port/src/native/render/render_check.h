#pragma once
// The live check of the render natives (soa --live-check render[:every=N][:budget=N][:only=..][:out=FILE]):
// a run-both family (native/common/live_run_both.h). Each checked native runs first, for real; then the
// guest original (its hook's trampoline) runs on the same inputs, on private memory, and the results are
// compared:
//   - ShaderCompression::CompressLZwordDic: the original into a scratch buffer; the size and every byte;
//   - RenderContextServer::GetRenderBatch / GetRenderBatchLite / GetLightContext: the original on a copy
//     of the object taken before the native; the result and the counter (a race when another worker
//     moved the counter in between);
//   - RenderThread's Add* / Req*: the native records the request state it saw once it held m_queueLock
//     ("pre": the ring's indices, the status, the flags, the slot it writes) and what it left ("post");
//     the original runs on a private RenderThread loaded with "pre" (its own events and lock) and must
//     leave "post" (the written slot compared on the bytes the guest defines; RenderThreadObservation);
//   - RenderThread::GetStatus: the original on the real object right after the native (a getter; a
//     difference that a rerun doesn't reproduce is a race).
// Nested natives run unchecked inside a check (live::t_busy).
#include "native/common/live_run_both.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

live::RunBothFamily& fam();

// What a RenderThread request native saw and did (render_thread.cpp records it while t_rtobs is set;
// render_thread_check.cpp replays the original from `pre` and compares with `post`).
struct RenderThreadObservation {
    struct State {
        u8 status = 0, resetRequested = 0, gpuWaitRequested = 0, exitRequested = 0;
        u16 endRenderCount = 0;
        s32 write = 0, read = 0;
        RENDER_REQUEST entry{};  // the slot at pre's m_write
    };
    State pre, post;
    bool have_pre = false;
    bool wake_set = false;          // m_wake.Set() called
    bool reset_done_reset = false;  // m_resetDone.Reset() called
    s32 queued_before = 0;          // AddRenderQueue: the object's m_renderQueued before its add

    void capture_pre(const RenderThread* rt, s32 read);
    void capture_post(const RenderThread* rt);
};
extern thread_local RenderThreadObservation* t_rtobs;

}  // namespace soa::native::render
