// Differential tests of the particle manager's natives (particles_manager.cpp): two private Worlds built
// alike from one seed (particles_check.h), the guest original run on one (its callees stubbed), the native
// member on the other (its callees through a scripted Recorder); both get the same answers (by call kind
// and index), and the calls and the states must match.
#include <cmath>
#include <cstring>
#include <random>
#include <string>

#include "core/loader.h"
#include "native/common/test.h"
#include "native/particles/particles_check.h"

using namespace soa;
using namespace soa::native::particles;

namespace {

u64 mix(u64 a, u64 b, u64 c) {
    u64 h = a ^ (b * 0x9e3779b97f4a7c15ull) ^ (c * 0xc2b2ae3d27d4eb4full);
    h ^= h >> 31;
    h *= 0xbf58476d1ce4e5b9ull;
    h ^= h >> 29;
    return h;
}

float from_bits(u32 b) {
    float f;
    std::memcpy(&f, &b, 4);
    return f;
}
// Times / dts: ordinary, zero, negative, huge, infinite, quiet and signalling NaNs.
float pick_float(u64 h) {
    static const u32 special[] = {0x00000000, 0x80000000, 0x7f800000, 0xff800000, 0x7fc00000, 0x7fc00123, 0x7f800001, 0xff812345, 0x7f7fffff};
    switch (h % 8) {
    case 0: return from_bits(special[(h >> 8) % (sizeof special / 4)]);
    case 1: return -(float)((h >> 8) % 1000) / 7.0f;
    case 2: return (float)((h >> 8) % 100000) * 1000.0f;
    default: return (float)((h >> 8) % 100000) / 977.0f;
    }
}

// The answers both runs get.
struct Answers {
    u64 seed;
    void operator()(Call& c, size_t i) const {
        const u64 h = mix(seed, (u64)c.kind + 1, i);
        switch (c.kind) {
        case CallKind::PostTask:
        case CallKind::Post:
            c.ret = (h % 5) != 0;  // a full queue now and then: Event::Wait and another try
            c.serial = (u32)(h >> 16);
            break;
        case CallKind::GetDt: {
            const float f = i % 3 ? 1.0f / 60 : pick_float(h >> 4);
            std::memcpy(&c.fret, &f, 4);
            break;
        }
        case CallKind::Skip: c.ret = (h % 4) == 0; break;
        case CallKind::Ready: c.ret = (h % 3) != 0; break;
        default: c.ret = 0; break;
        }
    }
};

// A world from `seed`: n emitters with random dispatch state.
void setup(World& w, u64 seed, int n) {
    std::mt19937_64 r(seed);
    w.reset(n);
    ParticleManager* m = w.m;
    m->m_time = pick_float(r());
    static const s32 inflight[] = {-2, -1, 0, 0, 0, 0, 1, 3};
    m->m_inFlight = inflight[r() % 8];
    m->m_buffersPending = r() % 2;
    m->m_fillFrame = (u32)r() % 50;
    m->m_drawnFrame = (u32)r() % 50;
    m->m_frameSlots[0] = (u32)r() % 50;
    m->m_frameSlots[1] = (u32)(r() % 2);  // (the index: 0 or 1)
    for (int i = 0; i < n; i++) {
        IParticleEmitter* e = w.e[i];
        e->m_flags = (u16)r() & 0x1ff;
        if (r() % 4) e->m_flags |= IParticleEmitter::kFlagEnabled;
        e->m_waitBuffer = r() % 3 == 0;
        static const u8 modes[] = {0, 0, 0, 1, 2};
        e->m_linkMode = modes[r() % 5];
        e->m_matrixMode = modes[r() % 5] == 1;
        static const s32 locks[] = {0, 0, 0, 1, 1, 2, -1};
        e->m_dispatchLock = locks[r() % 7];
        e->m_idle = r() % 2;
        e->m_serial = (u32)r();
        e->m_lastTime = pick_float(r());
        e->m_dispatchKey = r() % 4 ? (u64)r() : 0;
        e->m_renderable = reinterpret_cast<ParticleRenderableBase*>(0x10 * (u64)(i + 1));  // (never read: IsBufferReady is stubbed)
    }
}

// Everything the natives may change, pointers named.
std::string state(const World& w) {
    View v = w.view();
    std::string o = MState::of(w.m, v).text() + " fill " + std::to_string(w.m->m_fillFrame) + " inflight " + std::to_string(w.m->m_inFlight) +
                    " count " + std::to_string(w.m->base.m_count) + "\n";
    auto link = [&](const soa::native::containers::LinkElement* p) { return p == &w.m->base.m_sentinel ? std::string("S") : v.name((u64)p); };
    o += "S " + link(w.m->base.m_sentinel.m_prev) + " " + link(w.m->base.m_sentinel.m_next) + "\n";
    for (int i = 0; i < w.n; i++) {
        const IParticleEmitter* e = w.e[i];
        o += "E" + std::to_string(i) + " " + EState::of(e).text() + " links " + link(e->base.base.link.m_prev) + " " + link(e->base.base.link.m_next) + "\n";
    }
    return o;
}

// Runs the native (`nat`, on N, its calls scripted) and the guest `sym` (on G, stubbed) and compares.
template <typename Nat>
bool compare(TestContext& t, const char* what, u64 seed, World& G, World& N, Nat nat, const char* sym, std::initializer_list<u64> gx,
             const float* s0 = nullptr, u64* nativeRet = nullptr, u64* guestRet = nullptr) {
    Answers ans{seed};
    Recorder rec;
    rec.mode = Recorder::kScript;
    rec.answer = ans;
    t_rec = &rec;
    const u64 r = nat();
    t_rec = nullptr;
    GuestRun g;
    g.answer = ans;
    g.run(t.sym(sym), gx, s0);
    if (nativeRet) *nativeRet = r;
    if (guestRet) *guestRet = g.result.x0;
    if (!rec.error.empty()) return t.fail("%s seed %llu: native: %s", what, (unsigned long long)seed, rec.error.c_str()), false;
    if (!g.error.empty()) return t.fail("%s seed %llu: guest: %s", what, (unsigned long long)seed, g.error.c_str()), false;
    std::string d = first_diff(N.view().texts(rec.calls), G.view().texts(g.log));
    if (!d.empty()) return t.fail("%s seed %llu: calls: %s", what, (unsigned long long)seed, d.c_str()), false;
    d = first_diff(state(N), state(G));
    if (!d.empty()) return t.fail("%s seed %llu: state: %s", what, (unsigned long long)seed, d.c_str()), false;
    return true;
}

World& world_g() {
    static World w;
    return w;
}
World& world_n() {
    static World w;
    return w;
}

}  // namespace

// Handler and its INotify thunk: one emitter (m_arg1 0) or a list; times with NaNs / infinities (FSUB,
// FMIN against 1/30), locks other than 1 left alone.
NATIVE_TEST("particles/handler") {
    World &G = world_g(), &N = world_n();
    int ok = 0;
    for (u64 seed = 1; seed <= 400; seed++) {
        const int n = seed % 5 == 0 ? 0 : (int)(seed % 23);
        setup(G, seed, n ? n : 1);
        setup(N, seed, n ? n : 1);
        for (World* w : {&G, &N}) {
            if (n) {
                for (int i = 0; i < n; i++) w->m->m_dispatchStorage[i] = w->e[(i * 7) % n];  // (an order of its own)
                w->block->m_arg0 = w->m->m_dispatchStorage;
            } else {
                w->block->m_arg0 = w->e[0];
            }
            w->block->m_arg1 = (void*)(u64)n;
        }
        const bool thunk = seed % 2;
        if (!compare(
                t, "Handler", seed, G, N, [&] { return N.m->Handler(N.block), (u64)0; },
                thunk ? "_ZThn4080_N4Aska15ParticleManager7HandlerEm" : "_ZN4Aska15ParticleManager7HandlerEm",
                {(u64)G.m + (thunk ? 0xff0 : 0), (u64)G.block}))
            break;
        ok++;
    }
    t.expect_eq(ok, 400, "Handler runs");
}

// RunLow: the clock, the early return while emitters are in flight, the two lists (skips, buffers not
// ready, taken locks), the make-matrix message or DispatchEmitters (one message per worker).
NATIVE_TEST("particles/run-low") {
    World &G = world_g(), &N = world_n();
    int ok = 0;
    for (u64 seed = 1; seed <= 600; seed++) {
        const int n = (int)(seed % 41);
        setup(G, seed, n);
        setup(N, seed, n);
        if (!compare(
                t, "RunLow", seed, G, N, [&] { return N.m->RunLow(), (u64)0; }, "_ZN4Aska15ParticleManager6RunLowEv", {(u64)G.m}))
            break;
        ok++;
    }
    t.expect_eq(ok, 600, "RunLow runs");
}

// The capacity: more than 0x800 emitters (both lists stop at 0x800).
NATIVE_TEST("particles/run-low-full") {
    World &G = world_g(), &N = world_n();
    for (u64 seed = 1; seed <= 3; seed++) {
        const int n = 0x800 + 5 + (int)seed;
        setup(G, seed, n);
        setup(N, seed, n);
        for (World* w : {&G, &N}) {
            w->m->m_inFlight = 0;
            for (int i = 0; i < n; i++) {
                IParticleEmitter* e = w->e[i];
                e->m_flags = IParticleEmitter::kFlagEnabled;
                e->m_waitBuffer = 0;
                e->m_linkMode = seed == 2;
                e->m_matrixMode = 0;
                e->m_dispatchLock = 0;
            }
        }
        if (!compare(
                t, "RunLow (full)", seed, G, N, [&] { return N.m->RunLow(), (u64)0; }, "_ZN4Aska15ParticleManager6RunLowEv", {(u64)G.m}))
            break;
    }
}

// RunAfterRendering: the frame slots (index 0 / 1), the waiting emitters dispatched (taken or not).
NATIVE_TEST("particles/run-after-rendering") {
    World &G = world_g(), &N = world_n();
    int ok = 0;
    for (u64 seed = 1; seed <= 400; seed++) {
        const int n = (int)(seed % 29);
        setup(G, seed, n);
        setup(N, seed, n);
        if (!compare(
                t, "RunAfterRendering", seed, G, N, [&] { return N.m->RunAfterRendering(), (u64)0; },
                "_ZN4Aska15ParticleManager17RunAfterRenderingEv", {(u64)G.m}))
            break;
        ok++;
    }
    t.expect_eq(ok, 400, "RunAfterRendering runs");
}

// DispatchEmitters over the live dispatcher's worker count: counts below, at and above it.
NATIVE_TEST("particles/dispatch-emitters") {
    World &G = world_g(), &N = world_n();
    for (u64 seed = 1; seed <= 300; seed++) {
        setup(G, seed, 0);
        setup(N, seed, 0);
        const u64 n = seed % 7 == 0 ? 0x800 : seed % 3 == 0 ? seed % 5 : seed;
        G.m->m_dispatchCount = N.m->m_dispatchCount = n;
        u64 rn = 0, rg = 0;
        if (!compare(
                t, "DispatchEmitters", seed, G, N, [&] { return (u64)N.m->DispatchEmitters(); }, "_ZN4Aska15ParticleManager16DispatchEmittersEv",
                {(u64)G.m}, nullptr, &rn, &rg))
            break;
        if (!t.expect_eq(rn & 0xff, rg & 0xff, "DispatchEmitters result")) break;
    }
}

// Run (and its Task thunk): RunLow at level 0xe, RunAfterRendering at 0x1c, nothing else.
NATIVE_TEST("particles/run") {
    World &G = world_g(), &N = world_n();
    const s32 levels[] = {0xe, 0x1c, 0, 0xd, 0xf, 0x1b, 0x1d, -1};
    for (u64 seed = 1; seed <= 64; seed++) {
        setup(G, seed, (int)(seed % 9));
        setup(N, seed, (int)(seed % 9));
        const s32 level = levels[seed % 8];
        const bool thunk = (seed / 8) % 2;
        if (!compare(
                t, "Run", seed, G, N, [&] { return N.m->Run(level), (u64)0; },
                thunk ? "_ZThn40_N4Aska15ParticleManager3RunEi" : "_ZN4Aska15ParticleManager3RunEi", {(u64)G.m + (thunk ? 0x28 : 0), (u64)(u32)level}))
            break;
    }
}

// One emitter: Tick (dt passed through), DispatchEmitter (waiting or giving up on a full queue), Kick
// (Prepare, the make-matrix message unless m_linkMode, in flight +1 / -1).
NATIVE_TEST("particles/one-emitter") {
    World &G = world_g(), &N = world_n();
    int ok = 0;
    for (u64 seed = 1; seed <= 900; seed++) {
        setup(G, seed, 1);
        setup(N, seed, 1);
        const float dt = pick_float(mix(seed, 7, 7));
        bool good;
        u64 rn = 0, rg = 0;
        switch (seed % 3) {
        case 0:
            good = compare(
                t, "Tick", seed, G, N, [&] { return N.m->Tick(N.e[0], dt), (u64)0; }, "_ZN4Aska15ParticleManager4TickEPNS_16IParticleEmitterEf",
                {(u64)G.m, (u64)G.e[0]}, &dt);
            break;
        case 1: {
            const bool wait = (seed / 3) % 2;
            good = compare(
                t, "DispatchEmitter", seed, G, N, [&] { return (u64)N.m->DispatchEmitter(N.e[0], wait); },
                "_ZN4Aska15ParticleManager15DispatchEmitterEPNS_16IParticleEmitterEb", {(u64)G.m, (u64)G.e[0], (u64)wait}, nullptr, &rn, &rg);
            good = good && t.expect_eq(rn & 0xff, rg & 0xff, "DispatchEmitter result");
            break;
        }
        default:
            good = compare(
                t, "Kick", seed, G, N, [&] { return N.m->Kick(N.e[0]), (u64)0; }, "_ZN4Aska15ParticleManager4KickEPNS_16IParticleEmitterE",
                {(u64)G.m, (u64)G.e[0]});
            break;
        }
        if (!good) break;
        ok++;
    }
    t.expect_eq(ok, 900, "one-emitter runs");
}

// Add / Delete: random appends and unlinks (the sentinel, null, an unlinked element with null links:
// the count still goes down, not below 0).
NATIVE_TEST("particles/list") {
    World &G = world_g(), &N = world_n();
    for (u64 seed = 1; seed <= 40; seed++) {
        const int n = 12;
        setup(G, seed, n);
        setup(N, seed, n);
        std::mt19937_64 r(seed);
        std::vector<bool> linked(n, true);
        for (int step = 0; step < 60; step++) {
            const int i = (int)(r() % n);
            const int op = (int)(r() % 8);
            bool good;
            if (op == 0) {  // the sentinel or null
                const bool sentinel = r() % 2;
                good = compare(
                    t, "Delete (sentinel / null)", seed, G, N,
                    [&] { return N.m->Delete(sentinel ? &N.m->base.m_sentinel : nullptr), (u64)0; },
                    "_ZN4Aska15ParticleManager6DeleteEPNS_21AnimatableLinkElementE", {(u64)G.m, sentinel ? (u64)&G.m->base.m_sentinel : 0});
            } else if (linked[i] || op == 1) {
                good = compare(
                    t, "Delete", seed, G, N, [&] { return N.m->Delete(&N.e[i]->base.base.link), (u64)0; },
                    "_ZN4Aska15ParticleManager6DeleteEPNS_21AnimatableLinkElementE", {(u64)G.m, (u64)G.e[i]});
                linked[i] = false;
            } else {
                good = compare(
                    t, "Add", seed, G, N, [&] { return N.m->Add(&N.e[i]->base.base.link), (u64)0; },
                    "_ZN4Aska15ParticleManager3AddEPNS_21AnimatableLinkElementE", {(u64)G.m, (u64)G.e[i]});
                linked[i] = true;
            }
            if (!good) return;
        }
    }
}

// The getters: SkipThisFrame, IsEmitting, GetActiveNumberOfParticles on emitters with private renderables,
// IsBufferReady against the live manager's frame counters, GetClassID / GetDefaultLevel (and their thunks).
NATIVE_TEST("particles/getters") {
    constexpr int kN = 64;
    static IParticleEmitter es[kN];
    static ParticleRenderableBase rs[kN];
    std::mt19937_64 r(5);
    for (int round = 0; round < 20; round++) {
        for (int i = 0; i < kN; i++) {
            IParticleEmitter& e = es[i];
            ParticleRenderableBase& rb = rs[i];
            e.m_flags = (u16)r();
            e.m_renderable = r() % 5 ? &rb : nullptr;
            rb.base.m_renderFlags = (u32)r() & (r() % 2 ? 0x2101u : 0xffffffffu) & (r() % 3 ? ~0u : 0u);
            rb.m_activeCount = r() % 3 ? (s32)(r() % 7) - 2 : 0;
            const u64 h = (u64)&e;
            t.expect_eq(t.call("_ZNK4Aska16IParticleEmitter13SkipThisFrameEv", {h}) & 0xff, (u64)e.SkipThisFrame(), "SkipThisFrame");
            t.expect_eq(t.call("_ZNK4Aska16IParticleEmitter10IsEmittingEv", {h}) & 0xff, (u64)e.IsEmitting(), "IsEmitting");
            t.expect_eq((s32)t.call("_ZNK4Aska16IParticleEmitter26GetActiveNumberOfParticlesEv", {h}), e.GetActiveNumberOfParticles(),
                        "GetActiveNumberOfParticles");
        }
    }
    // IsBufferReady: stamps around the live counters (read again when a comparison fails: they move).
    auto* gm = *reinterpret_cast<ParticleManager* const*>(main_lib()->base + kVaddrGlobalParticleManager);
    if (gm) {
        int checked = 0;
        for (int round = 0; round < 400; round++) {
            const u32 fill = gm->m_fillFrame, drawn = gm->m_drawnFrame;
            const u32 cand[] = {0, 1, fill - 1, fill, fill + 1, drawn - 1, drawn, drawn + 1, 0xffffffffu, (u32)r()};
            ParticleRenderableBase& rb = rs[round % kN];
            rb.m_buffer = (u32)(r() % 2);
            rb.m_stamp[0] = cand[r() % 10];
            rb.m_stamp[1] = cand[r() % 10];
            const u64 g = t.call("_ZNK4Aska22ParticleRenderableBase13IsBufferReadyEv", {(u64)&rb}) & 0xff;
            const u64 n = rb.IsBufferReady();
            if (gm->m_fillFrame != fill || gm->m_drawnFrame != drawn) continue;  // (moved meanwhile)
            t.expect_eq(g, n, "IsBufferReady");
            checked++;
        }
        t.expect_eq(checked > 100, true, "IsBufferReady compared");
    }
    alignas(16) static u8 dummy[sizeof(ParticleManager)];
    auto* pm = reinterpret_cast<ParticleManager*>(dummy);
    for (s32 depth = -1; depth < 6; depth++) {
        t.expect_eq(t.call("_ZNK4Aska15ParticleManager10GetClassIDEi", {(u64)pm, (u64)(u32)depth}), pm->GetClassID(depth), "GetClassID");
        t.expect_eq(t.call("_ZThn40_NK4Aska15ParticleManager10GetClassIDEi", {(u64)pm + 0x28, (u64)(u32)depth}), pm->GetClassID(depth),
                    "GetClassID (thunk)");
    }
    t.expect_eq((u32)t.call("_ZNK4Aska15ParticleManager15GetDefaultLevelEv", {(u64)pm}), pm->GetDefaultLevel(), "GetDefaultLevel");
    t.expect_eq((u32)t.call("_ZThn40_NK4Aska15ParticleManager15GetDefaultLevelEv", {(u64)pm + 0x28}), pm->GetDefaultLevel(),
                "GetDefaultLevel (thunk)");
}
