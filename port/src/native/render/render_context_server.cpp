// Aska::RenderContextServer's atomic bump allocators (port/decomp/render/render_thread.c): the
// ObjectManager worker threads take render batches, batch lites and light contexts from the per-frame
// pools while they prepare objects (GetRenderBatch 1,376 + GetLightContext 494 guest self samples: the
// guest's LDXR/STXR loops, which the JIT runs as host compare-and-swaps, contended). Natively a host
// fetch-add on the same counter word: guest code still adding to it (ResetServer's plain stores, the
// other getters) and these natives mix as two guest threads would.
//
// Live check (soa --live-check render): the counter the native's fetch-add saw is put into a private copy
// of the object, the guest original runs on the copy with the same n, and its result and the copy's
// counter must equal the native's.
#include <cstring>
#include <string>

#include "core/cpu.h"
#include "native/common/native.h"
#include "native/render/render_check.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

namespace {
inline u32 fetch_add(u32& word, s32 n) { return __atomic_fetch_add(&word, (u32)n, __ATOMIC_SEQ_CST); }
}  // namespace

// The pools are taken past their end without a check (the guest's add is unconditional): a request
// that doesn't fit returns null and leaves the counter beyond the count until ResetServer.
RenderContextBatch* RenderContextServer::GetRenderBatch(s32 n) {
    const u32 first = fetch_add(m_batchUsed, n);
    return first + (u32)n < m_batchCount ? &m_batches[first] : nullptr;
}

u32* RenderContextServer::GetRenderBatchLite(s32 n) {
    const u32 first = fetch_add(m_batchLiteUsed, n);
    return first + (u32)n < m_batchLiteCount ? &m_batchLites[first] : nullptr;
}

LightContext* RenderContextServer::GetLightContext(s32 n) {
    const u32 first = fetch_add(m_lightContextUsed, n);
    return first + (u32)n < m_lightContextCount ? &m_lightContexts[m_bufferIndex][first] : nullptr;
}

namespace {

live::RunBothFamily::Fn fBatch(fam(), "_ZN4Aska19RenderContextServer14GetRenderBatchEi");
live::RunBothFamily::Fn fBatchLite(fam(), "_ZN4Aska19RenderContextServer18GetRenderBatchLiteEi");
live::RunBothFamily::Fn fLight(fam(), "_ZN4Aska19RenderContextServer15GetLightContextEi");

// The checked call: a copy of the object before the native, the native on the real object, the original
// on the copy with the same n; the results (as offsets into the pool, which the copy shares) and the
// counters compared. When the real counter moved by more than n, another worker took entries between the
// copy and the native's add: a race, not checked.
template <typename T>
void checked(Cpu& c, live::RunBothFamily::Fn& f, T* (RenderContextServer::*get)(s32), u32 RenderContextServer::*used) {
    auto* self = reinterpret_cast<RenderContextServer*>(c.x(0));
    const s32 n = (s32)c.x(1);
    if (__builtin_expect(!fam().due(f), 1)) {
        c.set_x(0, (u64)(self->*get)(n));
        return;
    }
    live::RunBothFamily::Scope scope;
    alignas(16) RenderContextServer shadow;
    std::memcpy(&shadow, self, sizeof shadow);
    T* r = (self->*get)(n);
    const u32 after = __atomic_load_n(&(self->*used), __ATOMIC_SEQ_CST);
    c.set_x(0, (u64)r);
    if (after != shadow.*used + (u32)n) {
        fam().result(f, live::RunBothFamily::Outcome::Race, "the counter moved by more than n");
        return;
    }
    T* g = (T*)guest_call(f.orig, {(u64)&shadow, (u64)(u32)n});
    std::string why;
    if (g != r) why = "result: native " + std::to_string((u64)r) + ", guest " + std::to_string((u64)g) + " (n " + std::to_string(n) + ")";
    else if (shadow.*used != after) why = "counter: native " + std::to_string(after) + ", guest " + std::to_string(shadow.*used);
    fam().result(f, why.empty() ? live::RunBothFamily::Outcome::Ok : live::RunBothFamily::Outcome::Mismatch, why);
}

void HostGetRenderBatch(Cpu& c) { checked(c, fBatch, &RenderContextServer::GetRenderBatch, &RenderContextServer::m_batchUsed); }
void HostGetRenderBatchLite(Cpu& c) { checked(c, fBatchLite, &RenderContextServer::GetRenderBatchLite, &RenderContextServer::m_batchLiteUsed); }
void HostGetLightContext(Cpu& c) { checked(c, fLight, &RenderContextServer::GetLightContext, &RenderContextServer::m_lightContextUsed); }

}  // namespace

NATIVE_FUNCTION_ORIG(fBatch.sym, HostGetRenderBatch, "render: RenderContextServer::GetRenderBatch", &fBatch.orig);
NATIVE_FUNCTION_ORIG(fBatchLite.sym, HostGetRenderBatchLite, "render: RenderContextServer::GetRenderBatchLite", &fBatchLite.orig);
NATIVE_FUNCTION_ORIG(fLight.sym, HostGetLightContext, "render: RenderContextServer::GetLightContext", &fLight.orig);

}  // namespace soa::native::render
