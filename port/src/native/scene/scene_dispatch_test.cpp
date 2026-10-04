// Differential tests of the job dispatcher's natives (scene_dispatch.cpp) against the 3.7.0 guest, on a
// private dispatcher with private (never started) workers built by the guest's own constructor.
//
// For each job the guest reference is the guest's whole path: its Dispatch_X posts the job to a worker that
// idles in mode X (the parameter stores, m_job, the Event::Set), then the worker's own Handler_X loop runs
// one iteration on this thread (m_modeChangePending set so it returns after the job). The native runs
// Dispatch_X with the job inline. Both see the same fake objects (vtables of recording fake functions) and
// stubbed guest callees (MakePaintingList*, the culling, DetectLIBL); the call sequences with their
// arguments (and the RENDERINFO bytes each PrepareForRendering call sees), the result bits, the worker's
// parameter bytes and, for ResetSystemFlags, the objects' bytes must be equal.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <cstring>
#include <string>
#include <vector>

#include "native/common/guest_stub.h"
#include "native/common/test.h"
#include "native/scene/scene_dispatch.h"
#include "native/scene/scene_layout.h"

namespace soa::native::scene {
namespace {

constexpr u32 kObjBytes = 0x310;  // a RenderableObject
constexpr int kObjects = 40;

void* zalloc(size_t n) {
    void* p = std::aligned_alloc(16, (n + 15) & ~size_t(15));
    std::memset(p, 0, n);
    return p;
}

std::string hex(const void* p, size_t n) {
    std::string s;
    char b[4];
    for (size_t i = 0; i < n; i++) {
        snprintf(b, sizeof b, "%02x", ((const u8*)p)[i]);
        s += b;
    }
    return s;
}

// What the fake functions and the stubbed callees saw, in order.
std::vector<std::string>* g_log = nullptr;
void note(const std::string& s) {
    if (g_log) g_log->push_back(s);
}

// A private dispatcher with `n` workers made by the guest's constructor (Event created, never started),
// and kObjects fake RenderableObjects whose vtable slots 51 / 62 / 79 / 80 / 83 are recording fakes.
struct Rig {
    TestContext& t;
    int n;
    ObjectManagerJobDispatcher* d;
    u8* block;  // operator new[]'s layout: the count, then the workers
    u8* objs;
    u8* objsInit;
    RenderableObject* obj[kObjects];
    u64* vtable;
    u64 bits[8];
    u8 fakeOm[0x20];

    Rig(TestContext& tc, int workers) : t(tc), n(workers) {
        d = (ObjectManagerJobDispatcher*)zalloc(sizeof(ObjectManagerJobDispatcher));
        block = (u8*)zalloc(16 + n * sizeof(ObjectManagerWorkerThread));
        *(u64*)(block + 8) = (u64)n;
        d->m_workers = (ObjectManagerWorkerThread*)(block + 16);
        d->m_workerCount = n;
        d->m_exceptIndex = -1;
        d->m_objectManager = (ObjectManager*)fakeOm;
        for (int i = 0; i < n; i++) {
            ObjectManagerWorkerThread* w = &d->m_workers[i];
            t.call("_ZN4Aska25ObjectManagerWorkerThreadC1Ev", {(u64)w});
            t.call("_ZN4Aska5Event6CreateEbb", {(u64)&w->m_event, 0, 0});
            w->m_dispatcher = d;
            w->m_objectManager = (ObjectManager*)fakeOm;
        }
        static const u64 fPrelim = fake_function("scene.t.prelim", 2), fPrepare = fake_function("scene.t.prepare", 2),
                         fReset = fake_function("scene.t.rdsm", 1), fCheck = fake_function("scene.t.crc", 1),
                         fRoutine = fake_function("scene.t.routine", 1);
        vtable = (u64*)zalloc(8 * 96);
        vtable[kSlotPreliminarilyPrepare] = fPrelim;
        vtable[kSlotPrepareForRendering] = fPrepare;
        vtable[kSlotResetDynamicShaderModifier] = fReset;
        vtable[kSlotCheckRenderContexts] = fCheck;
        vtable[kSlotRoutineProcedure] = fRoutine;
        objs = (u8*)zalloc(kObjBytes * kObjects);
        objsInit = (u8*)zalloc(kObjBytes * kObjects);
        static RenderContext* ctxBase = (RenderContext*)zalloc(0x230 * 4);
        for (int i = 0; i < kObjects; i++) {
            RenderableObject* o = obj[i] = (RenderableObject*)(objs + i * kObjBytes);
            u8 raw[kObjBytes];
            for (u32 k = 0; k < kObjBytes; k++) raw[k] = (u8)t.rand_int(0, 255);
            std::memcpy(o, raw, kObjBytes);
            *(u64**)o = vtable;
            o->m_shadowFlags[0] = (u8)t.rand_int(0, 255);
            o->m_shadowFlags[1] = (u8)t.rand_int(0, 255);
            static const s32 divisors[] = {0, 1, 2, 3, -1, -7, 5};
            o->m_contextDivisor = divisors[t.rand_int(0, 6)];
            o->m_contextsWanted = t.rand_int(0, 9) == 0 ? (s32)0x80000000 : t.rand_int(-100000, 100000);
            o->m_contextsUsed = t.rand_int(-3, 70000);
            o->m_contexts = ctxBase + t.rand_int(0, 3);
            o->m_camera = t.rand_int(0, 1) ? nullptr : (render::Camera*)(0x1000 + 16 * i);
            o->m_renderFlags = (u32)t.rand_u64();
            o->base.base.link.m_next = (containers::LinkElement*)(i + 1 < kObjects ? objs + (i + 1) * kObjBytes : nullptr);
        }
        std::memcpy(objsInit, objs, kObjBytes * kObjects);
    }
    ~Rig() {
        for (int i = 0; i < n; i++) {
            ObjectManagerWorkerThread* w = &d->m_workers[i];
            t.call("_ZN4Aska5Event4ExitEv", {(u64)&w->m_event});
            t.call("_ZN4Aska19FastCriticalSectionD1Ev", {(u64)&w->m_lock});
        }
        std::free(d);
        std::free(block);
        std::free(objs);
        std::free(objsInit);
        std::free(vtable);
    }
    ObjectManagerWorkerThread& w(int i = 0) { return d->m_workers[i]; }
    int index_of(u64 p) const {
        for (int i = 0; i < kObjects; i++)
            if ((u64)obj[i] == p) return i;
        return -1;
    }
    // Back to the state of construction: objects, result bits, the workers idle in `mode` with no job.
    void reset(int mode) {
        std::memcpy(objs, objsInit, kObjBytes * kObjects);
        for (int i = 0; i < 8; i++) bits[i] = (i * 0x9e3779b97f4a7c15ull) & 0x1111111111111111ull;  // (other objects' bits)
        for (int i = 0; i < n; i++) {
            ObjectManagerWorkerThread& x = w(i);
            x.m_mode = mode;
            x.m_nextMode = -1;
            x.m_waiting = 1;
            x.m_modeChangePending = 0;
            x.m_running = 1;
            x.m_job = 0;
            x.m_resultBits = bits;
        }
    }
};

// A session answering the fakes and the stubbed callees, logging into `log`.
struct Session {
    StubSession s;
    std::vector<std::string> log;
    Rig& rig;
    explicit Session(Rig& r) : rig(r) {
        g_log = &log;
        auto obj_call = [this](const char* what, u64 ret_bit) {
            return [this, what, ret_bit](Cpu& c) {
                int i = rig.index_of(c.x(0));
                note(std::string(what) + "(obj" + std::to_string(i) + ")");
                // results with bit 0 set or clear (and other bits set: the callers test bit 0 only)
                c.set_x(0, ((i * 7) % 3 == 0 ? 0 : ret_bit) | 0x100);
            };
        };
        answer("scene.t.prelim", [this](Cpu& c) {
            int i = rig.index_of(c.x(0));
            note("prelim(obj" + std::to_string(i) + ", lm=" + std::to_string(c.x(1)) + ")");
            c.set_x(0, ((i * 5) % 4 == 1 ? 0 : 1) | 0xfe00);
        });
        answer("scene.t.prepare", [this](Cpu& c) {
            int i = rig.index_of(c.x(0));
            note("prepare(obj" + std::to_string(i) + ", info@" + std::to_string(c.x(1) - (u64)&rig.w()) + "=" +
                 hex((const void*)c.x(1), sizeof(RENDERINFO)) + ")");
            c.set_x(0, ((i * 3) % 5 == 2 ? 2 : 1));
        });
        answer("scene.t.rdsm", obj_call("rdsm", 1));
        answer("scene.t.crc", obj_call("crc", 1));
        answer("scene.t.routine", obj_call("routine", 1));
        auto callee = [](const char* what, int nregs, bool stack9) {
            return [what, nregs, stack9](Cpu& c) {
                std::string e = std::string(what) + "(";
                for (int i = 0; i < nregs; i++) e += (i ? "," : "") + std::to_string(c.x(i));
                if (stack9) e += ",[sp]=" + std::to_string(*(const u64*)c.sp());
                note(e + ")");
                c.set_x(0, 0);
            };
        };
        answer("scene.t.mpl", callee("MakePaintingList", 2, false));
        answer("scene.t.mplm", callee("MakePaintingListMultipass", 2, false));
        answer("scene.t.mpls", callee("MakePaintingListShadow", 2, false));
        answer("scene.t.mplp", callee("MakePaintingListPost", 1, false));
        answer("scene.t.vfc", callee("ViewFrustumCulling", 8, false));
        answer("scene.t.svfc", callee("SubViewFrustumCulling", 8, false));
        answer("scene.t.occ", callee("OcclusionCulling", 8, true));
        answer("scene.t.libl", callee("DetectLIBL", 4, false));
    }
    ~Session() { g_log = nullptr; }
    void answer(const char* name, StubSession::Behaviour b) {
        s.behave[name] = std::move(b);
        s.only.insert(name);
    }
};

void stub_callees() {
    static bool once = [] {
        stub("_ZN4Aska13ObjectManager16MakePaintingListEi", "scene.t.mpl", 2);
        stub("_ZN4Aska13ObjectManager25MakePaintingListMultipassEi", "scene.t.mplm", 2);
        stub("_ZN4Aska13ObjectManager22MakePaintingListShadowEi", "scene.t.mpls", 2);
        stub("_ZN4Aska13ObjectManager20MakePaintingListPostEv", "scene.t.mplp", 1);
        stub("_ZN4Aska13ObjectManager18ViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectEiiPm", "scene.t.vfc", 8);
        stub("_ZN4Aska13ObjectManager21SubViewFrustumCullingEPNS_6CameraEiiPPNS_16RenderableObjectEiiPm", "scene.t.svfc", 8);
        stub("_ZN4Aska13ObjectManager16OcclusionCullingEPNS_6CameraEiibPPNS_16RenderableObjectEiiPm", "scene.t.occ", 8);
        stub("_ZN4Aska13ObjectManager10DetectLIBLEPPNS_16RenderableObjectEii", "scene.t.libl", 4);
        return true;
    }();
    (void)once;
}

// One run's observable outcome.
struct Outcome {
    u64 ret = 0;
    std::vector<std::string> log;
    std::vector<u8> params;  // the worker's bytes from m_lightManager (0x138) on
    u64 bits[8];
    std::vector<u8> objects;
};

Outcome capture(Rig& r, u64 ret, Session& s) {
    Outcome o;
    o.ret = ret;
    o.log = s.log;
    const u8* w = (const u8*)&r.w();
    o.params.assign(w + offsetof(ObjectManagerWorkerThread, m_lightManager), w + sizeof(ObjectManagerWorkerThread));
    std::memcpy(o.bits, r.bits, sizeof o.bits);
    o.objects.assign(r.objs, r.objs + kObjBytes * kObjects);
    return o;
}

void compare(TestContext& t, const char* what, const Outcome& g, const Outcome& n) {
    char m[160];
    snprintf(m, sizeof m, "%s: result", what);
    t.expect_eq(n.ret & 1, g.ret & 1, m);
    snprintf(m, sizeof m, "%s: calls", what);
    if (!t.expect_eq(n.log, g.log, m)) {
        for (size_t i = 0; i < std::max(n.log.size(), g.log.size()); i++)
            fprintf(stderr, "  %3zu guest %-60s native %s\n", i, i < g.log.size() ? g.log[i].c_str() : "-",
                    i < n.log.size() ? n.log[i].c_str() : "-");
    }
    snprintf(m, sizeof m, "%s: result bits", what);
    t.expect_eq(std::memcmp(n.bits, g.bits, sizeof g.bits), 0, m);
    snprintf(m, sizeof m, "%s: worker parameters", what);
    if (!t.expect_eq(n.params, g.params, m)) {
        for (size_t i = 0; i < g.params.size(); i++)
            if (n.params[i] != g.params[i]) {
                fprintf(stderr, "  worker +0x%zx: guest %02x native %02x\n", i + offsetof(ObjectManagerWorkerThread, m_lightManager), g.params[i],
                        n.params[i]);
                break;
            }
    }
    snprintf(m, sizeof m, "%s: objects", what);
    if (!t.expect_eq(n.objects, g.objects, m)) {
        for (size_t i = 0; i < g.objects.size(); i++)
            if (n.objects[i] != g.objects[i]) {
                fprintf(stderr, "  object %zu +0x%zx: guest %02x native %02x\n", i / kObjBytes, i % kObjBytes, g.objects[i], n.objects[i]);
                break;
            }
    }
}

// The guest: Dispatch_X (from `post`) to the worker idling in mode `job`, then its Handler_X for one job.
Outcome run_guest(Rig& r, int job, const char* handler, const std::function<u64()>& post) {
    r.reset(job);
    Session s(r);
    u64 ret = post();
    r.w().m_modeChangePending = 1;  // (Handler_X returns after this job)
    if (ret & 1) r.t.call(handler, {(u64)&r.w()});
    r.w().m_modeChangePending = 0;
    // The guest's own end state: the worker waits again, no job (the native leaves them as it found them).
    return capture(r, ret, s);
}

Outcome run_native(Rig& r, const std::function<u64()>& post) {
    r.reset(7);
    Session s(r);
    u64 ret = post();
    return capture(r, ret, s);
}

}  // namespace

NATIVE_TEST("scene/dispatch-prepare-for-rendering") {
    Rig r(t, 1);
    RENDERINFO info;
    std::vector<u8> raw = t.rand_bytes(sizeof info);
    std::memcpy(&info, raw.data(), sizeof info);
    for (int kind = 0; kind <= 2; kind++) {
        for (int first : {0, 3, 30}) {
            int last = first + 7 < kObjects ? first + 7 : kObjects - 1;
            auto args = [&] { return (u64)(u32)first | (u64)(u32)last << 32; };
            const char* disp = "_ZN4Aska26ObjectManagerJobDispatcher28Dispatch_PrepareForRenderingEiPPNS_16RenderableObjectEm";
            const char* set = "_ZN4Aska26ObjectManagerJobDispatcher36SetPrepareForRenderingBasicParameterEPNS_10RENDERINFOEPmPNS_6CameraE";
            Outcome g = run_guest(r, 3, "_ZN4Aska25ObjectManagerWorkerThread27Handler_PrepareForRenderingEv", [&] {
                t.call(set, {(u64)r.d, (u64)&info, (u64)r.bits, 0x7770});
                return t.call(disp, {(u64)r.d, (u64)kind, (u64)(r.obj + first), args()});
            });
            Outcome n = run_native(r, [&] {
                r.d->SetPrepareForRenderingBasicParameter(&info, r.bits, (render::Camera*)0x7770);
                return (u64)r.d->Dispatch_PrepareForRendering(kind, r.obj + first, args());
            });
            char what[64];
            snprintf(what, sizeof what, "prepare kind %d [%d, %d]", kind, first, last);
            compare(t, what, g, n);
        }
    }
}

NATIVE_TEST("scene/dispatch-preliminarily-prepare") {
    Rig r(t, 1);
    for (int first : {0, 5, 33}) {
        int last = std::min(first + 9, kObjects - 1);
        const char* disp = "_ZN4Aska26ObjectManagerJobDispatcher29Dispatch_PreliminarilyPrepareEPPNS_16RenderableObjectEii";
        const char* set = "_ZN4Aska26ObjectManagerJobDispatcher37SetPreliminarilyPrepareBasicParameterEPNS_12LightManagerEPm";
        // (Handler inlines this job; Handler_PreliminarilyPrepare is the same loop as a function of its own)
        Outcome g = run_guest(r, 2, "_ZN4Aska25ObjectManagerWorkerThread28Handler_PreliminarilyPrepareEv", [&] {
            t.call(set, {(u64)r.d, 0x4440, (u64)r.bits});
            return t.call(disp, {(u64)r.d, (u64)(r.obj + first), (u64)first, (u64)last});
        });
        Outcome n = run_native(r, [&] {
            r.d->SetPreliminarilyPrepareBasicParameter((LightManager*)0x4440, r.bits);
            return (u64)r.d->Dispatch_PreliminarilyPrepare(r.obj + first, first, last);
        });
        char what[64];
        snprintf(what, sizeof what, "prelim [%d, %d]", first, last);
        compare(t, what, g, n);
    }
}

NATIVE_TEST("scene/dispatch-make-painting-list") {
    stub_callees();
    Rig r(t, 1);
    for (int kind = -1; kind <= 4; kind++) {
        int index = t.rand_int(0, 127);
        const char* disp = "_ZN4Aska26ObjectManagerJobDispatcher25Dispatch_MakePaintingListEii";
        Outcome g = run_guest(r, 1, "_ZN4Aska25ObjectManagerWorkerThread24Handler_MakePaintingListEv", [&] {
            t.call(disp, {(u64)r.d, (u64)(u32)kind, (u64)(u32)index});
            return (u64)1;  // (void: it loops until it posts)
        });
        Outcome n = run_native(r, [&] {
            r.d->Dispatch_MakePaintingList(kind, index);
            return (u64)1;
        });
        char what[64];
        snprintf(what, sizeof what, "make painting list kind %d", kind);
        compare(t, what, g, n);
    }
}

NATIVE_TEST("scene/dispatch-view-frustum-culling") {
    stub_callees();
    Rig r(t, 1);
    for (int kind = 0; kind <= 3; kind++) {
        const char* disp = "_ZN4Aska26ObjectManagerJobDispatcher27Dispatch_ViewFrustumCullingEiii";
        const char* set = "_ZN4Aska26ObjectManagerJobDispatcher35SetViewFrustumCullingBasicParameterEPNS_6CameraEiiPPNS_16RenderableObjectEPm";
        int first = t.rand_int(0, 20), last = first + t.rand_int(0, 19);
        Outcome g = run_guest(r, 4, "_ZN4Aska25ObjectManagerWorkerThread26Handler_ViewFrustumCullingEv", [&] {
            t.call(set, {(u64)r.d, 0x5550, 0, 0xffffffff, (u64)r.obj, (u64)r.bits});
            return t.call(disp, {(u64)r.d, (u64)kind, (u64)first, (u64)last});
        });
        Outcome n = run_native(r, [&] {
            r.d->SetViewFrustumCullingBasicParameter((render::Camera*)0x5550, 0, -1, r.obj, r.bits);
            return (u64)r.d->Dispatch_ViewFrustumCulling(kind, first, last);
        });
        char what[64];
        snprintf(what, sizeof what, "culling kind %d", kind);
        compare(t, what, g, n);
    }
}

NATIVE_TEST("scene/dispatch-detect-libl") {
    stub_callees();
    Rig r(t, 1);
    const char* disp = "_ZN4Aska26ObjectManagerJobDispatcher19Dispatch_DetectLIBLEii";
    const char* set = "_ZN4Aska26ObjectManagerJobDispatcher27SetDetectLIBLBasicParameterEPPNS_16RenderableObjectE";
    Outcome g = run_guest(r, 5, "_ZN4Aska25ObjectManagerWorkerThread18Handler_DetectLIBLEv", [&] {
        t.call(set, {(u64)r.d, (u64)r.obj});
        return t.call(disp, {(u64)r.d, 8, 23});
    });
    Outcome n = run_native(r, [&] {
        r.d->SetDetectLIBLBasicParameter(r.obj);
        return (u64)r.d->Dispatch_DetectLIBL(8, 23);
    });
    compare(t, "detect LIBL", g, n);
}

NATIVE_TEST("scene/dispatch-reset-system-flags") {
    Rig r(t, 1);
    const char* disp = "_ZN4Aska26ObjectManagerJobDispatcher25Dispatch_ResetSystemFlagsEPNS_16RenderableObjectES2_";
    // A range ending at its last object, a single object, and a range cut short by the object manager's
    // list head (Global::m_pObjectManager + 8) as a link.
    const u64 head = *(const u64*)guest_fns().globalObjectManager + 8;
    for (int k = 0; k < 3; k++) {
        int first = k == 1 ? 12 : 2, last = k == 1 ? 12 : 17;
        if (k == 2) r.obj[9]->base.base.link.m_next = (containers::LinkElement*)head;
        if (k == 2) std::memcpy(r.objsInit, r.objs, kObjBytes * kObjects);
        Outcome g = run_guest(r, 6, "_ZN4Aska25ObjectManagerWorkerThread24Handler_ResetSystemFlagsEv",
                              [&] { return t.call(disp, {(u64)r.d, (u64)r.obj[first], (u64)r.obj[last]}); });
        Outcome n = run_native(r, [&] { return (u64)r.d->Dispatch_ResetSystemFlags(r.obj[first], r.obj[last]); });
        char what[64];
        snprintf(what, sizeof what, "reset system flags %d", k);
        compare(t, what, g, n);
    }
}

// ChangeMode / RetryChangeMode* / WaitIdle / WaitAllIssued / Sleep and the Set*BasicParameter forms on two
// idle workers: the dispatcher's bytes (and the workers' parameters) as the guest leaves them.
NATIVE_TEST("scene/dispatch-modes-and-parameters") {
    Rig r(t, 2);
    auto dispatcher_bytes = [&] { return std::vector<u8>((const u8*)r.d + 0x98, (const u8*)r.d + sizeof(ObjectManagerJobDispatcher)); };
    auto worker_params = [&] {
        std::vector<u8> v;
        for (int i = 0; i < 2; i++) {
            const u8* w = (const u8*)&r.w(i);
            v.insert(v.end(), w + offsetof(ObjectManagerWorkerThread, m_lightManager), w + sizeof(ObjectManagerWorkerThread));
        }
        return v;
    };
    struct Op {
        const char* sym;
        std::function<void(int)> native;
    };
    const Op ops[] = {
        {"_ZN4Aska26ObjectManagerJobDispatcher10ChangeModeEi", [&](int m) { r.d->ChangeMode(m); }},
        {"_ZN4Aska26ObjectManagerJobDispatcher15RetryChangeModeEi", [&](int m) { r.d->RetryChangeMode(m); }},
        {"_ZN4Aska26ObjectManagerJobDispatcher33RetryChangeModeExceptRenderThreadEi", [&](int m) { r.d->RetryChangeModeExceptRenderThread(m); }},
        {"_ZN4Aska26ObjectManagerJobDispatcher8WaitIdleEv", [&](int) { r.d->WaitIdle(); }},
        {"_ZN4Aska26ObjectManagerJobDispatcher13WaitAllIssuedEv", [&](int) { r.d->WaitAllIssued(); }},
        {"_ZN4Aska26ObjectManagerJobDispatcher5SleepEv", [&](int) { r.d->Sleep(); }},
    };
    for (const Op& op : ops) {
        for (int except : {-1, 1}) {
            for (int mode = 1; mode <= 7; mode++) {
                for (u8 exceptMode : {0, 1}) {
                    r.reset(mode == 7 ? 1 : 7);  // (workers in another mode: the Retry forms switch them)
                    r.d->m_exceptIndex = except;
                    r.d->m_exceptMode = exceptMode;
                    r.d->m_workerCountSeen = 0;
                    t.call(op.sym, {(u64)r.d, (u64)mode});
                    std::vector<u8> g = dispatcher_bytes();
                    r.reset(mode == 7 ? 1 : 7);
                    r.d->m_exceptIndex = except;
                    r.d->m_exceptMode = exceptMode;
                    r.d->m_workerCountSeen = 0;
                    op.native(mode);
                    char what[160];
                    snprintf(what, sizeof what, "%s(%d), except %d, except mode %d: dispatcher bytes", op.sym, mode, except, exceptMode);
                    t.expect_eq(dispatcher_bytes(), g, what);
                }
            }
        }
    }
    r.d->m_exceptIndex = -1;
    // The Set*BasicParameter forms store into every worker.
    RENDERINFO info;
    std::vector<u8> raw = t.rand_bytes(sizeof info);
    std::memcpy(&info, raw.data(), sizeof info);
    r.reset(7);
    t.call("_ZN4Aska26ObjectManagerJobDispatcher37SetPreliminarilyPrepareBasicParameterEPNS_12LightManagerEPm", {(u64)r.d, 0x1230, 0x4560});
    t.call("_ZN4Aska26ObjectManagerJobDispatcher36SetPrepareForRenderingBasicParameterEPNS_10RENDERINFOEPmPNS_6CameraE",
           {(u64)r.d, (u64)&info, 0x7890, 0xabc0});
    t.call("_ZN4Aska26ObjectManagerJobDispatcher35SetViewFrustumCullingBasicParameterEPNS_6CameraEiiPPNS_16RenderableObjectEPm",
           {(u64)r.d, 0xdef0, 3, 0xfffffffe, 0x1110, 0x2220});
    t.call("_ZN4Aska26ObjectManagerJobDispatcher27SetDetectLIBLBasicParameterEPPNS_16RenderableObjectE", {(u64)r.d, 0x3330});
    std::vector<u8> g = worker_params();
    r.reset(7);
    r.d->SetPreliminarilyPrepareBasicParameter((LightManager*)0x1230, (u64*)0x4560);
    r.d->SetPrepareForRenderingBasicParameter(&info, (u64*)0x7890, (render::Camera*)0xabc0);
    r.d->SetViewFrustumCullingBasicParameter((render::Camera*)0xdef0, 3, -2, (RenderableObject**)0x1110, (u64*)0x2220);
    r.d->SetDetectLIBLBasicParameter((RenderableObject**)0x3330);
    t.expect_eq(worker_params(), g, "Set*BasicParameter: the workers' parameters");
}

}  // namespace soa::native::scene
