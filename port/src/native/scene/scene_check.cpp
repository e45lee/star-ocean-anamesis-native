// The live check of the job dispatcher's natives (scene_check.h) and their bindings.
#include "native/scene/scene_check.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <utility>

#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/common/native_method.h"
#include "native/scene/scene_dispatch.h"

namespace soa::native::scene {

live::ShadowFamily& family() {
    static live::ShadowFamily f("scene", 16);
    return f;
}

thread_local JobRecorder* t_rec = nullptr;

u64 job_call(u64 fn, const u64* a, size_t n) {
    JobRecorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return guest_call_raw(fn, a, n, nullptr, 0, 0).x0;
    // Where the call lands (a lone B followed); a lone RET has no effect to replay and isn't recorded.
    const u64 lands = live::callee(fn);
    if (live::is_ret_only(lands)) return guest_call_raw(fn, a, n, nullptr, 0, 0).x0;
    JobCall c;
    c.target = lands;
    c.n = (int)n;
    std::memcpy(c.x, a, n * 8);
    for (size_t i = 0; i < r->objs.size(); i++)
        if ((u64)r->objs[i] == a[0]) {
            c.obj = (int)i;
            break;
        }
    if (n >= 2 && a[1] == (u64)&r->worker->m_renderInfo) {
        const u8* p = (const u8*)&r->worker->m_renderInfo;
        c.info.assign(p, p + sizeof(RENDERINFO));
    }
    t_rec = nullptr;  // (what the callee calls isn't the body's)
    c.ret = guest_call_raw(fn, a, n, nullptr, 0, 0).x0;
    t_rec = r;
    if (c.obj >= 0) {
        const u8* p = (const u8*)r->objs[c.obj];
        c.objAfter.assign(p, p + kObjSnap);
    }
    if (r->bits) c.bitsAfter.assign((const u8*)r->bits, (const u8*)(r->bits + r->bitsWords));
    r->calls.push_back(std::move(c));
    return r->calls.back().ret;
}

namespace {

using live::check_due;
using live::check_result;
using live::CheckScope;
using live::Outcome;
using live::ShadowFn;

using D = ObjectManagerJobDispatcher;
using W = ObjectManagerWorkerThread;

constexpr size_t kMaxObjects = 512;
constexpr u32 kCopyStride = 0x250;   // one object copy (kObjSnap bytes, 16-aligned)
constexpr size_t kParamsFrom = offsetof(W, m_lightManager);
constexpr size_t kStateFrom = offsetof(W, m_mode), kStateTo = offsetof(W, unk_120);

void* zalloc(size_t n) {
    void* p = std::aligned_alloc(16, (n + 15) & ~size_t(15));
    std::memset(p, 0, n);
    return p;
}

// This thread's shadow: a dispatcher with one worker built by the guest's constructor (its Event created,
// never started), reused by every check on the thread.
struct Shadow {
    D* d = nullptr;
    W* w = nullptr;
    Shadow() {
        d = (D*)zalloc(sizeof(D));
        u8* block = (u8*)zalloc(16 + sizeof(W));
        *(u64*)(block + 8) = 1;  // (operator new[]'s count)
        w = (W*)(block + 16);
        guest_call(guest::sym("_ZN4Aska25ObjectManagerWorkerThreadC1Ev"), {(u64)w});
        guest_call(guest::sym("_ZN4Aska5Event6CreateEbb"), {(u64)&w->m_event, 0, 0});
    }
    // The real dispatcher's fields, its worker's (from `workerFields`, the bytes from m_mode on as the
    // native found them), the worker idle in `mode` with no job and its event clear.
    void set(const D* real, const u8* workerFields, s32 mode) {
        const void* vt = real->vtable;
        std::memset((void*)d, 0, sizeof(D));
        d->vtable = vt;
        d->m_workers = w;
        d->m_objectManager = real->m_objectManager;
        d->m_workerCountSeen = real->m_workerCountSeen;
        d->m_workerCount = 1;
        d->m_unkB0 = real->m_unkB0;
        d->m_exceptIndex = real->m_exceptIndex;
        d->m_exceptMode = real->m_exceptMode;
        std::memcpy((u8*)w + kStateFrom, workerFields, sizeof(W) - kStateFrom);
        w->m_mode = mode;
        w->m_nextMode = -1;
        w->m_waiting = 1;
        w->m_modeChangePending = 0;
        w->m_running = 1;
        w->m_exit = 0;
        w->m_job = 0;
        w->m_dispatcher = d;
        guest_call(guest::sym("_ZNK4Aska5Event5ResetEv"), {(u64)&w->m_event});
    }
};
Shadow& shadow() {
    static thread_local Shadow s;
    return s;
}

std::string hexdiff(const u8* a, const u8* b, size_t n, size_t base) {
    for (size_t i = 0; i < n; i++)
        if (a[i] != b[i]) {
            char m[96];
            snprintf(m, sizeof m, "+0x%zx: native %02x guest %02x", base + i, a[i], b[i]);
            return m;
        }
    return {};
}

// ---- the Dispatch_* checks -------------------------------------------------------------------------

struct JobFn : ShadowFn {
    s32 job;
    const char* handler;
    JobFn(const char* sym, s32 j, const char* h) : ShadowFn(family(), sym), job(j), handler(h) {}
};

JobFn g_mpl("_ZN4Aska26ObjectManagerJobDispatcher25Dispatch_MakePaintingListEii", 1,
            "_ZN4Aska25ObjectManagerWorkerThread24Handler_MakePaintingListEv");
JobFn g_prelim("_ZN4Aska26ObjectManagerJobDispatcher29Dispatch_PreliminarilyPrepareEPPNS_16RenderableObjectEii", 2,
               "_ZN4Aska25ObjectManagerWorkerThread28Handler_PreliminarilyPrepareEv");
JobFn g_prepare("_ZN4Aska26ObjectManagerJobDispatcher28Dispatch_PrepareForRenderingEiPPNS_16RenderableObjectEm", 3,
                "_ZN4Aska25ObjectManagerWorkerThread27Handler_PrepareForRenderingEv");
JobFn g_vfc("_ZN4Aska26ObjectManagerJobDispatcher27Dispatch_ViewFrustumCullingEiii", 4,
            "_ZN4Aska25ObjectManagerWorkerThread26Handler_ViewFrustumCullingEv");
JobFn g_libl("_ZN4Aska26ObjectManagerJobDispatcher19Dispatch_DetectLIBLEii", 5, "_ZN4Aska25ObjectManagerWorkerThread18Handler_DetectLIBLEv");
JobFn g_reset("_ZN4Aska26ObjectManagerJobDispatcher25Dispatch_ResetSystemFlagsEPNS_16RenderableObjectES2_", 6,
              "_ZN4Aska25ObjectManagerWorkerThread24Handler_ResetSystemFlagsEv");

// One checked Dispatch_X: the native (recorded), then the guest's Dispatch_X + Handler_X on the shadow.
void check_job(Cpu& c, JobFn& f, HostFn native) {
    CheckScope scope;
    D* realD = (D*)c.x(0);
    if (realD->m_workerCount != 1 || !realD->InlineWorker(f.job == 3 && realD->m_exceptIndex >= 0)) {
        native(c);
        return check_result(f, Outcome::Skipped, "not one worker");
    }
    W* realW = realD->InlineWorker(f.job == 3 && realD->m_exceptIndex >= 0);
    const u64 x[4] = {c.x(0), c.x(1), c.x(2), c.x(3)};

    // The batch the job works on.
    JobRecorder rec;
    rec.worker = realW;
    RenderableObject** array = nullptr;  // jobs 2 / 3: the argument array (indexed from `first`)
    s32 first = 0, last = -1;
    const u64 head = *reinterpret_cast<const u64*>(guest_fns().globalObjectManager) + 8;
    if (f.job == 2) array = (RenderableObject**)x[1], first = (s32)x[2], last = (s32)x[3];
    if (f.job == 3) array = (RenderableObject**)x[2], first = (s32)x[3], last = (s32)(x[3] >> 32);
    if (array) {
        if (last - first + 1 > (s32)kMaxObjects) {
            native(c);
            return check_result(f, Outcome::Skipped, "batch too large");
        }
        for (s32 i = first; i <= last; i++) rec.objs.push_back(array[i - first]);
    }
    if (f.job == 6) {  // the chain the job walks
        RenderableObject* o = (RenderableObject*)x[1];
        for (;;) {
            rec.objs.push_back(o);
            if (o == (RenderableObject*)x[2] || rec.objs.size() > kMaxObjects) break;
            o = next_task(o);
            if ((u64)o == head) break;
        }
        if (rec.objs.size() > kMaxObjects) {
            native(c);
            return check_result(f, Outcome::Skipped, "chain too long");
        }
    }
    size_t words = 0;  // the result words the job writes
    if (f.job == 2 || f.job == 3) words = last >= 0 ? (size_t)(last >> 5) + 1 : 0;
    if (f.job == 4) words = (size_t)((s32)x[3] >> 5) + 1;
    u64* realBits = realW->m_resultBits;
    if (f.job == 4) rec.bits = realBits, rec.bitsWords = words;

    // As the native found them: the worker's fields, the result words, the objects.
    std::vector<u8> fieldsPre((const u8*)realW + kStateFrom, (const u8*)realW + sizeof(W));
    std::vector<u64> bitsPre(realBits && words ? realBits : nullptr, realBits && words ? realBits + words : nullptr);
    const size_t n = rec.objs.size();
    std::vector<u8> objsPre(n * kObjSnap);
    for (size_t i = 0; i < n; i++) std::memcpy(&objsPre[i * kObjSnap], rec.objs[i], kObjSnap);

    t_rec = &rec;
    native(c);
    t_rec = nullptr;
    const u64 nativeRet = c.x(0);

    // The shadow, as the native found things.
    Shadow& sh = shadow();
    sh.set(realD, fieldsPre.data(), f.job);
    u8* copies = (u8*)zalloc(n * kCopyStride + 16);
    std::vector<u64> shadowArray(n);
    for (size_t i = 0; i < n; i++) {
        std::memcpy(copies + i * kCopyStride, &objsPre[i * kObjSnap], kObjSnap);
        shadowArray[i] = (u64)(copies + i * kCopyStride);
    }
    auto copy_of = [&](size_t i) { return (RenderableObject*)(copies + i * kCopyStride); };
    auto relink = [&](size_t i) {  // a chain copy's link to the next copy
        if (f.job == 6 && i + 1 < n && next_task(rec.objs[i]) == rec.objs[i + 1])
            copy_of(i)->base.base.link.m_next = (containers::LinkElement*)copy_of(i + 1);
    };
    for (size_t i = 0; i < n; i++) relink(i);
    std::vector<u64> shadowBits(bitsPre);
    if (realBits && words) sh.w->m_resultBits = shadowBits.data();
    // real -> shadow, for the arguments
    auto to_shadow = [&](u64 v) -> u64 {
        for (size_t i = 0; i < n; i++)
            if (v == (u64)rec.objs[i]) return shadowArray[i];
        if (v == (u64)&realW->m_renderInfo) return (u64)&sh.w->m_renderInfo;
        if (realBits && words && v == (u64)realBits) return (u64)shadowBits.data();
        return v;
    };

    // The replay: every recorded callee answered from the record.
    live::ReplaySession rs;
    size_t cursor = 0;
    std::string err;
    for (const JobCall& k : rec.calls) {
        const char* name = live::ensure_stub(k.target);
        if (!name) {
            std::free(copies);
            return check_result(f, Outcome::Skipped, "a callee can't be stubbed");
        }
        live::drop_stale_code(k.target);
        const u64 target = k.target;
        rs.answer(name, [&, target](Cpu& cc) {
            if (cursor >= rec.calls.size()) {
                if (err.empty()) err = "the guest made more calls than the native";
                cc.set_x(0, 0);
                return;
            }
            const JobCall& r = rec.calls[cursor++];
            char m[160];
            if (r.target != target && err.empty()) {
                snprintf(m, sizeof m, "call %zu: guest called %#llx, native %#llx", cursor - 1, (unsigned long long)target,
                         (unsigned long long)r.target);
                err = m;
            }
            for (int i = 0; i < r.n && err.empty(); i++) {
                u64 got = i < 8 ? cc.x(i) : *(const u64*)(cc.sp() + 8 * (i - 8));
                u64 want = to_shadow(r.x[i]);
                if (got != want) {
                    snprintf(m, sizeof m, "call %zu (%#llx): argument %d: guest %#llx, native %#llx", cursor - 1, (unsigned long long)target, i,
                             (unsigned long long)got, (unsigned long long)want);
                    err = m;
                }
            }
            if (!r.info.empty() && err.empty()) {
                std::string d = hexdiff(r.info.data(), (const u8*)cc.x(1), r.info.size(), 0);
                if (!d.empty()) err = "call " + std::to_string(cursor - 1) + ": RENDERINFO " + d;
            }
            if (r.obj >= 0) {
                std::memcpy(copy_of(r.obj), r.objAfter.data(), kObjSnap);
                relink(r.obj);
            }
            if (!r.bitsAfter.empty()) std::memcpy(shadowBits.data(), r.bitsAfter.data(), r.bitsAfter.size());
            cc.set_x(0, r.ret);
        });
    }
    u64 a[4] = {(u64)sh.d, x[1], x[2], x[3]};
    if (f.job == 2) a[1] = (u64)shadowArray.data();
    if (f.job == 3) a[2] = (u64)shadowArray.data();
    if (f.job == 6) a[1] = to_shadow(x[1]), a[2] = to_shadow(x[2]);
    const u64 guestRet = guest_call_raw(f.orig, a, 4, nullptr, 0, 0).x0;
    sh.w->m_modeChangePending = 1;  // (Handler_X returns after this job)
    if (f.job == 1 || (guestRet & 1)) guest_call(guest::sym(f.handler), {(u64)sh.w});
    sh.w->m_modeChangePending = 0;

    // Compare.
    if (err.empty() && cursor != rec.calls.size()) err = "the guest made " + std::to_string(cursor) + " of the native's " + std::to_string(rec.calls.size()) + " calls";
    if (err.empty() && f.job != 1 && (guestRet & 1) != (nativeRet & 1)) err = "result: native " + std::to_string(nativeRet & 1) + ", guest " + std::to_string(guestRet & 1);
    if (err.empty() && realBits && words && std::memcmp(realBits, shadowBits.data(), words * 8) != 0)
        err = "result words " + hexdiff((const u8*)realBits, (const u8*)shadowBits.data(), words * 8, 0);
    if (err.empty()) {
        // the shadow's own pointers count as the real ones
        if (sh.w->m_resultBits == shadowBits.data()) sh.w->m_resultBits = realBits;
        if (sh.w->m_prelimObjects == (RenderableObject**)shadowArray.data()) sh.w->m_prelimObjects = array;
        if (sh.w->m_prepareObjects == (RenderableObject**)shadowArray.data()) sh.w->m_prepareObjects = array;
        if (f.job == 6) sh.w->m_resetFirst = (RenderableObject*)x[1], sh.w->m_resetLast = (RenderableObject*)x[2];
        std::string d = hexdiff((const u8*)realW + kParamsFrom, (const u8*)sh.w + kParamsFrom, sizeof(W) - kParamsFrom, kParamsFrom);
        if (!d.empty()) err = "worker " + d;
    }
    for (size_t i = 0; i < n && err.empty(); i++) {
        constexpr size_t from = offsetof(RenderableObject, m_renderFlags);
        std::string d = hexdiff((const u8*)rec.objs[i] + from, (const u8*)copy_of(i) + from, kObjSnap - from, from);
        if (!d.empty()) err = "object " + std::to_string(i) + " " + d;
    }
    std::free(copies);
    check_result(f, err.empty() ? Outcome::Ok : Outcome::Mismatch, err);
}

template <auto M>
void checked_job(Cpu& c, JobFn& f) {
    if (!check_due(f)) return wrap_method<M>()(c);
    check_job(c, f, wrap_method<M>());
}

void mpl_hook(Cpu& c) { checked_job<&D::Dispatch_MakePaintingList>(c, g_mpl); }
void prelim_hook(Cpu& c) { checked_job<&D::Dispatch_PreliminarilyPrepare>(c, g_prelim); }
void prepare_hook(Cpu& c) { checked_job<&D::Dispatch_PrepareForRendering>(c, g_prepare); }
void vfc_hook(Cpu& c) { checked_job<&D::Dispatch_ViewFrustumCulling>(c, g_vfc); }
void libl_hook(Cpu& c) { checked_job<&D::Dispatch_DetectLIBL>(c, g_libl); }
void reset_hook(Cpu& c) { checked_job<&D::Dispatch_ResetSystemFlags>(c, g_reset); }

// ---- the mode changes and the parameter stores ----------------------------------------------------

// The guest original on the shadow (its worker idle in another mode than the argument's), then the
// dispatcher's bytes from m_workerCountSeen on and the worker's parameters against the native's.
struct PlainFn : ShadowFn {
    explicit PlainFn(const char* sym) : ShadowFn(family(), sym) {}
};
void check_plain(Cpu& c, PlainFn& f, HostFn native) {
    CheckScope scope;
    D* realD = (D*)c.x(0);
    if (realD->m_workerCount != 1) {
        native(c);
        return check_result(f, Outcome::Skipped, "not one worker");
    }
    W* realW = &realD->m_workers[0];
    std::vector<u8> fieldsPre((const u8*)realW + kStateFrom, (const u8*)realW + sizeof(W));
    const u64 a1 = c.x(1);
    u64 a[6] = {0, c.x(1), c.x(2), c.x(3), c.x(4), c.x(5)};
    Shadow& sh = shadow();
    sh.set(realD, fieldsPre.data(), (s32)a1 == 7 ? 1 : 7);
    native(c);
    a[0] = (u64)sh.d;
    guest_call_raw(f.orig, a, 6, nullptr, 0, 0);
    constexpr size_t from = offsetof(D, m_workerCountSeen);
    std::string err = hexdiff((const u8*)realD + from, (const u8*)sh.d + from, sizeof(D) - from, from);
    if (err.empty()) {
        std::string d = hexdiff((const u8*)realW + kParamsFrom, (const u8*)sh.w + kParamsFrom, sizeof(W) - kParamsFrom, kParamsFrom);
        if (!d.empty()) err = "worker " + d;
    }
    sh.w->m_modeChangePending = 0;
    check_result(f, err.empty() ? Outcome::Ok : Outcome::Mismatch, err);
}

template <auto M>
void checked_plain(Cpu& c, PlainFn& f) {
    if (!check_due(f)) return wrap_method<M>()(c);
    check_plain(c, f, wrap_method<M>());
}

PlainFn g_change("_ZN4Aska26ObjectManagerJobDispatcher10ChangeModeEi");
PlainFn g_retry("_ZN4Aska26ObjectManagerJobDispatcher15RetryChangeModeEi");
PlainFn g_retry_ex("_ZN4Aska26ObjectManagerJobDispatcher33RetryChangeModeExceptRenderThreadEi");
PlainFn g_wait_idle("_ZN4Aska26ObjectManagerJobDispatcher8WaitIdleEv");
PlainFn g_wait_issued("_ZN4Aska26ObjectManagerJobDispatcher13WaitAllIssuedEv");
PlainFn g_sleep("_ZN4Aska26ObjectManagerJobDispatcher5SleepEv");
PlainFn g_set_prelim("_ZN4Aska26ObjectManagerJobDispatcher37SetPreliminarilyPrepareBasicParameterEPNS_12LightManagerEPm");
PlainFn g_set_prepare("_ZN4Aska26ObjectManagerJobDispatcher36SetPrepareForRenderingBasicParameterEPNS_10RENDERINFOEPmPNS_6CameraE");
PlainFn g_set_vfc("_ZN4Aska26ObjectManagerJobDispatcher35SetViewFrustumCullingBasicParameterEPNS_6CameraEiiPPNS_16RenderableObjectEPm");
PlainFn g_set_libl("_ZN4Aska26ObjectManagerJobDispatcher27SetDetectLIBLBasicParameterEPPNS_16RenderableObjectE");

void change_hook(Cpu& c) { checked_plain<&D::ChangeMode>(c, g_change); }
void retry_hook(Cpu& c) { checked_plain<&D::RetryChangeMode>(c, g_retry); }
void retry_ex_hook(Cpu& c) { checked_plain<&D::RetryChangeModeExceptRenderThread>(c, g_retry_ex); }
void wait_idle_hook(Cpu& c) { checked_plain<&D::WaitIdle>(c, g_wait_idle); }
void wait_issued_hook(Cpu& c) { checked_plain<&D::WaitAllIssued>(c, g_wait_issued); }
void sleep_hook(Cpu& c) { checked_plain<&D::Sleep>(c, g_sleep); }
void set_prelim_hook(Cpu& c) { checked_plain<&D::SetPreliminarilyPrepareBasicParameter>(c, g_set_prelim); }
void set_prepare_hook(Cpu& c) { checked_plain<&D::SetPrepareForRenderingBasicParameter>(c, g_set_prepare); }
void set_vfc_hook(Cpu& c) { checked_plain<&D::SetViewFrustumCullingBasicParameter>(c, g_set_vfc); }
void set_libl_hook(Cpu& c) { checked_plain<&D::SetDetectLIBLBasicParameter>(c, g_set_libl); }

}  // namespace

// ---- bindings ------------------------------------------------------------------------------------

#define SCENE_NATIVE(fn, hook, what) \
    NATIVE_FUNCTION_ORIG(fn.sym, hook, "scene: Aska::ObjectManagerJobDispatcher::" what " (jobs inline)", &fn.orig)
SCENE_NATIVE(g_mpl, mpl_hook, "Dispatch_MakePaintingList");
SCENE_NATIVE(g_prelim, prelim_hook, "Dispatch_PreliminarilyPrepare");
SCENE_NATIVE(g_prepare, prepare_hook, "Dispatch_PrepareForRendering");
SCENE_NATIVE(g_vfc, vfc_hook, "Dispatch_ViewFrustumCulling");
SCENE_NATIVE(g_libl, libl_hook, "Dispatch_DetectLIBL");
SCENE_NATIVE(g_reset, reset_hook, "Dispatch_ResetSystemFlags");
SCENE_NATIVE(g_change, change_hook, "ChangeMode");
SCENE_NATIVE(g_retry, retry_hook, "RetryChangeMode");
SCENE_NATIVE(g_retry_ex, retry_ex_hook, "RetryChangeModeExceptRenderThread");
SCENE_NATIVE(g_wait_idle, wait_idle_hook, "WaitIdle");
SCENE_NATIVE(g_wait_issued, wait_issued_hook, "WaitAllIssued");
SCENE_NATIVE(g_sleep, sleep_hook, "Sleep");
SCENE_NATIVE(g_set_prelim, set_prelim_hook, "SetPreliminarilyPrepareBasicParameter");
SCENE_NATIVE(g_set_prepare, set_prepare_hook, "SetPrepareForRenderingBasicParameter");
SCENE_NATIVE(g_set_vfc, set_vfc_hook, "SetViewFrustumCullingBasicParameter");
SCENE_NATIVE(g_set_libl, set_libl_hook, "SetDetectLIBLBasicParameter");

}  // namespace soa::native::scene
