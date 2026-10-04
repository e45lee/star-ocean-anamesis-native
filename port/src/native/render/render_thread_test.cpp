// Differential tests of RenderThread's request natives (render_thread.cpp) against the 3.7.0 guest: two
// private RenderThreads (host memory, their events, critical section and lock made by sync's members),
// the guest's Add* / Req* on one and the natives on the other, compared after every call.
#include <atomic>
#include <cstring>
#include <memory>
#include <new>
#include <string>
#include <thread>

#include "native/common/test.h"
#include "native/render/render_layout.h"

namespace soa::native::render {
namespace {

struct Private {
    RenderThread* rt;
    RenderableObject* obj;
    Private() {
        rt = static_cast<RenderThread*>(::operator new(sizeof(RenderThread), std::align_val_t(64)));
        std::memset(rt, 0, sizeof *rt);
        rt->m_wake.Ctor();
        rt->m_wake.Create(false, false);
        rt->m_resetDone.Ctor();
        rt->m_resetDone.Create(false, false);
        rt->m_blockCallDone.Ctor();
        rt->m_blockCallDone.Create(false, false);
        rt->m_blockCallCs.CtorBase();
        rt->m_queueLock.CtorBase();
        rt->m_queue.m_write = 1;
        obj = static_cast<RenderableObject*>(::operator new(sizeof(RenderableObject), std::align_val_t(64)));
        std::memset(obj, 0, sizeof *obj);
    }
    ~Private() {
        rt->m_wake.Exit();
        rt->m_resetDone.Exit();
        rt->m_blockCallDone.Exit();
        rt->m_queueLock.Dtor();
        ::operator delete(rt, std::align_val_t(64));
        ::operator delete(obj, std::align_val_t(64));
    }
};

constexpr u64 kAll = ~0ull, kLow = 0xffffffffull;
// The argument bits the guest defines per request type (render_thread_check.cpp's table).
void arg_mask(u8 type, u64 m[3]) {
    m[0] = m[1] = m[2] = 0;
    switch (type) {
    case 0: case 3: case 4: case 7: case 0xb: case 0xc: case 0x11: case 0x14: m[0] = m[1] = m[2] = kAll; break;
    case 2: m[0] = m[1] = kAll; break;
    case 6: case 8: case 0xe: case 0x13: m[0] = kAll; break;
    case 0x10: m[0] = m[1] = kLow; m[2] = kAll; break;
    default: break;
    }
}

std::string diff(const Private& g, const Private& n) {
    const RenderThread& a = *g.rt;
    const RenderThread& b = *n.rt;
    char m[200];
    if (a.m_queue.m_write != b.m_queue.m_write) return "m_write";
    if (a.m_queue.m_read != b.m_queue.m_read) return "m_read";
    if (a.m_status != b.m_status) return "m_status";
    if (a.m_endRenderCount != b.m_endRenderCount) return "m_endRenderCount";
    if (a.m_resetRequested != b.m_resetRequested || a.m_gpuWaitRequested != b.m_gpuWaitRequested || a.m_exitRequested != b.m_exitRequested)
        return "a request flag";
    if (a.m_wake.m_signaled != b.m_wake.m_signaled) return "m_wake signaled";
    if (a.m_resetDone.m_signaled != b.m_resetDone.m_signaled) return "m_resetDone signaled";
    if (a.m_queueLock.m_lock != b.m_queueLock.m_lock || a.m_queueLock.m_waiters != b.m_queueLock.m_waiters) return "m_queueLock";
    if (g.obj->m_renderQueued != n.obj->m_renderQueued) return "m_renderQueued";
    for (int i = 0; i < 0x2001; i++) {
        const RENDER_REQUEST& x = a.m_queue.m_entries[i];
        const RENDER_REQUEST& y = b.m_queue.m_entries[i];
        if (x.m_type != y.m_type) {
            snprintf(m, sizeof m, "entry %d type: guest %u native %u", i, x.m_type, y.m_type);
            return m;
        }
        u64 mask[3];
        arg_mask(x.m_type, mask);
        for (int k = 0; k < 3; k++) {
            u64 gx = x.m_arg[k] == (u64)g.obj ? (u64)n.obj : x.m_arg[k];
            if ((gx ^ y.m_arg[k]) & mask[k]) {
                snprintf(m, sizeof m, "entry %d (type %u) arg %d: guest %#llx native %#llx", i, x.m_type, k, (unsigned long long)x.m_arg[k],
                         (unsigned long long)y.m_arg[k]);
                return m;
            }
        }
    }
    return {};
}

}  // namespace

// Every request native on random arguments, the consumer side simulated between calls (the reader
// catching up, the status back to idle, the events reset), through a full ring (the refusals).
NATIVE_TEST("render/thread-requests") {
    Private g, n;
    int bad = 0;
    for (int k = 0; k < 20000 && bad < 3; k++) {
        const int op = t.rand_int(0, 21);
        const u64 a = t.rand_u64(), b = t.rand_u64(), c = t.rand_u64();
        const float fa = (float)t.rand_int(-1000, 1000) / 7.0f, fb = (float)t.rand_int(-1000, 1000) / 3.0f;
        u64 gr = 0, nr = 0;
        bool has = true;
        auto G = [&](const char* sym, std::initializer_list<u64> rest) {
            std::vector<u64> v{(u64)g.rt};
            v.insert(v.end(), rest.begin(), rest.end());
            GuestArgs ga;
            for (u64 x : v) ga.i(x);
            return guest_call(t.sym(sym), ga).x0 & 0xff;
        };
        switch (op) {
        case 0: gr = G("_ZN4Aska12RenderThread14AddRenderQueueEPNS_16RenderableObjectEPNS_13RenderContextEi", {(u64)g.obj, b, (u64)(u32)c});
                nr = n.rt->AddRenderQueue(n.obj, (RenderContext*)b, (s32)c); break;
        case 1: gr = G("_ZN4Aska12RenderThread21AddChangeRenderTargetEjPNS_21MULTIPASS_ENVIRONMENTE", {(u64)(u32)a, b});
                nr = n.rt->AddChangeRenderTarget((u32)a, (void*)b); break;
        case 2: gr = G("_ZN4Aska12RenderThread14AddReloadZCullEv", {}); nr = n.rt->AddReloadZCull(); break;
        case 3: gr = G("_ZN4Aska12RenderThread26AddEnableGnmOcclusionQueryEb", {a & 1}); nr = n.rt->AddEnableGnmOcclusionQuery(a & 1); break;
        case 4: {
            GuestArgs ga;
            ga.i((u64)g.rt).f(fa).f(fb);
            gr = guest_call(t.sym("_ZN4Aska12RenderThread16AddExposureScaleEff"), ga).x0 & 0xff;
            nr = n.rt->AddExposureScale(fa, fb);
            break;
        }
        case 5: gr = G("_ZN4Aska12RenderThread14AddEnableFastZEb", {a & 1}); nr = n.rt->AddEnableFastZ(a & 1); break;
        case 6: gr = G("_ZN4Aska12RenderThread21AddFinishRenderTargetEjii", {(u64)(u32)a, (u64)(u32)b, (u64)(u32)c});
                nr = n.rt->AddFinishRenderTarget((u32)a, (s32)b, (s32)c); break;
        case 7: gr = G("_ZN4Aska12RenderThread19AddTemporaryResolveEPNS_16RenderableObjectEii", {a, (u64)(u32)b, (u64)(u32)c});
                nr = n.rt->AddTemporaryResolve((RenderableObject*)a, (s32)b, (s32)c); break;
        case 8: gr = G("_ZN4Aska12RenderThread14AddBeginRenderEv", {}); nr = n.rt->AddBeginRender(); break;
        case 9: gr = G("_ZN4Aska12RenderThread12AddEndRenderEPNS_7INotifyE", {a}); nr = n.rt->AddEndRender((void*)a); break;
        case 10: gr = G("_ZN4Aska12RenderThread11AddCallBackEPFvmmEmm", {a, b, c}); nr = n.rt->AddCallBack((void (*)(u64, u64))a, b, c); break;
        case 11: gr = G("_ZN4Aska12RenderThread15AddDataTransferEPvS1_j", {a, b, (u64)(u32)c});
                 nr = n.rt->AddDataTransfer((void*)a, (void*)b, (u32)c); break;
        case 12: G("_ZN4Aska12RenderThread42ExecutePendingTileRegionOperationByAddressEPv", {a});
                 n.rt->ExecutePendingTileRegionOperationByAddress((void*)a); has = false; break;
        case 13: gr = G("_ZN4Aska12RenderThread22AddOcclusionQueryBeginEPj", {a}); nr = n.rt->AddOcclusionQueryBegin((u32*)a); break;
        case 14: gr = G("_ZN4Aska12RenderThread20AddOcclusionQueryEndEv", {}); nr = n.rt->AddOcclusionQueryEnd(); break;
        case 15: G("_ZN4Aska12RenderThread7ReqSwapEv", {}); n.rt->ReqSwap(); has = false; break;
        case 16: G("_ZN4Aska12RenderThread13ReqDeviceInitEv", {}); n.rt->ReqDeviceInit(); has = false; break;
        case 17: G("_ZN4Aska12RenderThread14ReqDeviceResetEv", {}); n.rt->ReqDeviceReset(); has = false; break;
        case 18: G("_ZN4Aska12RenderThread7ReqExitEv", {}); n.rt->ReqExit(); has = false; break;
        case 19: G("_ZN4Aska12RenderThread10ReqGpuWaitEv", {}); n.rt->ReqGpuWait(); has = false; break;
        case 20: gr = G("_ZNK4Aska12RenderThread9GetStatusEv", {}); nr = n.rt->GetStatus(); break;
        default: {
            // the consumer: the reader catches up by some entries (or all), the thread goes idle, the
            // events and flags are reset
            const int r = t.rand_int(0, 3);
            for (Private* p : {&g, &n}) {
                RenderThread& rt = *p->rt;
                if (r == 0) {
                    rt.m_queue.m_read = rt.m_queue.m_write ? rt.m_queue.m_write - 1 : 0x2000;
                    rt.m_status = 0;
                }
                rt.m_wake.m_signaled = 0;
                rt.m_resetDone.m_signaled = 1;
                if (r == 1) rt.m_resetRequested = rt.m_exitRequested = rt.m_gpuWaitRequested = 0;
            }
            has = false;
            break;
        }
        }
        // the ring full now and then: the reader parked right behind the writer
        if (k % 997 == 500)
            for (Private* p : {&g, &n}) p->rt->m_queue.m_read = (p->rt->m_queue.m_write + 3) % 0x2001;
        std::string d = diff(g, n);
        if (has && (gr & 0xff) != (nr & 0xff)) d = "result guest " + std::to_string(gr & 0xff) + " native " + std::to_string(nr & 0xff);
        if (!d.empty()) {
            t.fail("call %d (op %d): %s", k, op, d.c_str());
            bad++;
        }
    }
}

// The block calls: a host thread plays the render thread (takes m_blockCall, writes DownloadResource's
// result byte, clears the call, Sets m_blockCallDone); the call, its arguments and the result compared.
NATIVE_TEST("render/thread-block-call") {
    Private g, n;
    struct Seen {
        u64 fn = 0, a = 0, b = 0;
    };
    auto serve = [](RenderThread* rt, Seen* seen, std::atomic<bool>* stop) {
        while (!stop->load()) {
            u64 fn = __atomic_load_n(&rt->m_blockCall, __ATOMIC_ACQUIRE);
            if (fn) {
                *seen = {fn, rt->m_blockCallArg[0], rt->m_blockCallArg[1]};
                if (seen->b && seen->b > 0x10000 && seen->a == 0x1234) *reinterpret_cast<u8*>(seen->b) = 1;
                __atomic_store_n(&rt->m_blockCall, 0, __ATOMIC_RELEASE);
                rt->m_blockCallDone.Set();
            }
            std::this_thread::yield();
        }
    };
    for (int round = 0; round < 2; round++) {
        Seen sg, sn;
        u64 gr = 0, nr = 0;
        for (Private* p : {&g, &n}) {
            Seen* s = p == &g ? &sg : &sn;
            std::atomic<bool> stop{false};
            std::thread th(serve, p->rt, s, &stop);
            if (round == 0) {
                if (p == &g) t.call("_ZN4Aska12RenderThread21ReqCustomCommandBlockEPFvmmEmm", {(u64)g.rt, 0x5000, 0x77, 0x88});
                else n.rt->ReqCustomCommandBlock((void (*)(u64, u64))0x5000, 0x77, 0x88);
            } else {
                if (p == &g) gr = t.call("_ZN4Aska12RenderThread24ReqDownloadResourceBlockEPNS_11GpuResourceE", {(u64)g.rt, 0x1234}) & 0xff;
                else nr = n.rt->ReqDownloadResourceBlock((void*)0x1234);
            }
            stop = true;
            th.join();
        }
        t.expect_eq(sg.fn, sn.fn, "the block call's function");
        t.expect_eq(sg.a, sn.a, "its first argument");
        if (round == 0) t.expect_eq(sg.b, sn.b, "its second argument");
        t.expect_eq(gr, nr, "ReqDownloadResourceBlock's result");
        t.expect_eq(g.rt->m_wake.m_signaled, n.rt->m_wake.m_signaled, "m_wake");
    }
    t.expect_eq(n.rt->m_blockCall, (u64)0, "the call cleared");
}

}  // namespace soa::native::render
