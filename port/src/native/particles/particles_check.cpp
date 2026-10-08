// The live checks of the particle manager's natives (particles_check.h) and their bindings.
#include "native/particles/particles_check.h"

#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <map>
#include <memory>

#include "core/thread_record.h"
#include "native/common/guest_std.h"
#include "native/common/native_method.h"

namespace soa::native::particles {

live::ShadowFamily& family() {
    static live::ShadowFamily f("particles", 16);
    return f;
}

namespace {

using live::check_due;
using live::check_result;
using live::CheckScope;
using live::Outcome;

struct Fn : live::ShadowFn {
    explicit Fn(const char* s) : live::ShadowFn(family(), s) {}
};

World& world() { return thread_object<World>(); }  // this thread's (core/thread_record.h)

// A this-adjusting thunk of member M: `this` is x0 - off.
template <auto M, u64 Off>
void thunk(Cpu& c) {
    c.set_x(0, c.x(0) - Off);
    wrap_method<M>()(c);
}

// The emitters of the manager's list, in order.
std::vector<IParticleEmitter*> list_of(const ParticleManager* m) {
    std::vector<IParticleEmitter*> v;
    for (IParticleEmitter* e = m->FirstEmitter(); e && v.size() < (size_t)World::kMaxEmitters + 1; e = m->NextEmitter(e)) v.push_back(e);
    return v;
}
View view_of(const ParticleManager* m, const std::vector<IParticleEmitter*>& es) {
    View v;
    v.m = m;
    for (auto* e : es) v.e.push_back(e);
    return v;
}
int index_of(const std::vector<IParticleEmitter*>& es, const void* e) {
    for (size_t i = 0; i < es.size(); i++)
        if (es[i] == e) return (int)i;
    return -1;
}

// The comparison all checks end with: the call lists, then the states (texts, one line each).
void finish(Fn& f, const Recorder& rec, const View& nv, GuestRun& g, const View& gv, const std::string& nativeState,
            const std::string& guestState, const std::string& extra = {}) {
    if (!g.error.empty()) return check_result(f, Outcome::Mismatch, g.error);
    std::string d = first_diff(nv.texts(rec.calls), gv.texts(g.log));
    if (!d.empty()) return check_result(f, Outcome::Mismatch, "calls: " + d);
    d = first_diff(nativeState, guestState);
    if (!d.empty()) return check_result(f, Outcome::Mismatch, "state: " + d);
    if (!extra.empty()) return check_result(f, Outcome::Mismatch, extra);
    check_result(f, Outcome::Ok);
}

// ---- Handler (and its INotify thunk) ----

Fn g_handler("_ZN4Aska15ParticleManager7HandlerEm"), g_handler_thunk("_ZThn4080_N4Aska15ParticleManager7HandlerEm");

void check_handler(Cpu& c, Fn& f, u64 off) {
    CheckScope scope;
    auto* m = reinterpret_cast<ParticleManager*>(c.x(0) - off);
    auto* b = reinterpret_cast<MessageDispatcherBlock*>(c.x(1));
    const u64 n = (u64)b->m_arg1;
    std::vector<IParticleEmitter*> es;
    if (n == 0) es.push_back(static_cast<IParticleEmitter*>(b->m_arg0));
    else
        for (u64 i = 0; i < n && i <= (u64)World::kMaxEmitters; i++) es.push_back(static_cast<IParticleEmitter* const*>(b->m_arg0)[i]);
    if (es.size() > (size_t)World::kMaxEmitters) {
        wrap_method<&ParticleManager::Handler>()(c);
        return check_result(f, Outcome::Skipped, "too many emitters");
    }
    // What the native saw per emitter: the times, the lock its release found; and what it left (after the
    // emitter's Simulate: serial, last time; at its release: idle).
    struct Seen {
        u32 now = 0, last = 0;
        s32 lockSeen = 0;
        EState after;
        u8 idle = 0;
    };
    std::vector<Seen> seen(es.size());
    size_t cur = 0;
    Recorder rec;
    rec.on_note = [&](Recorder::Point p, const void* o, s64 v) {
        if (cur >= es.size() || o != es[cur]) return;
        if (p == Recorder::kTimeRead) seen[cur].now = (u32)((u64)v >> 32), seen[cur].last = (u32)v;
        if (p == Recorder::kReleased) {
            seen[cur].lockSeen = (s32)v;
            seen[cur].idle = es[cur]->m_idle;
            cur++;
        }
    };
    rec.after = [&](Recorder&, Call& k) {
        if (k.kind == CallKind::Simulate && cur < es.size()) seen[cur].after = EState::of(es[cur]);
    };
    c.set_x(0, (u64)m);
    t_rec = &rec;
    wrap_method<&ParticleManager::Handler>()(c);
    t_rec = nullptr;
    if (cur != es.size()) return check_result(f, Outcome::Mismatch, "the native simulated " + std::to_string(cur) + " of " + std::to_string(es.size()));

    // The shadow: the emitters as the native found them, the manager's time moved on per emitter.
    World& w = world();
    w.reset((int)es.size());
    for (size_t i = 0; i < es.size(); i++) {
        IParticleEmitter* s = w.e[i];
        std::memcpy(&s->m_lastTime, &seen[i].last, 4);
        s->m_dispatchLock = seen[i].lockSeen;
    }
    std::memcpy(&w.m->m_time, &seen[0].now, 4);
    w.m->m_inFlight = 0;
    if (n == 0) w.block->m_arg0 = w.e[0];
    else {
        for (size_t i = 0; i < es.size(); i++) w.m->m_dispatchStorage[i] = w.e[i];
        w.block->m_arg0 = w.m->m_dispatchStorage;
    }
    w.block->m_arg1 = (void*)n;
    GuestRun g;
    g.script = &rec.calls;
    g.after = [&](size_t i, Call&) {
        if (i + 1 < es.size()) std::memcpy(&w.m->m_time, &seen[i + 1].now, 4);
    };
    g.run(f.orig, {(u64)w.m + off, (u64)w.block});

    std::string ns, gs;
    for (size_t i = 0; i < es.size(); i++) {
        EState want = seen[i].after;
        want.idle = seen[i].idle;
        want.lock = seen[i].lockSeen == 1 ? 0 : seen[i].lockSeen;
        want.waitBuffer = 0;
        EState got = EState::of(w.e[i]);
        got.waitBuffer = 0;
        ns += want.text() + "\n";
        gs += got.text() + "\n";
    }
    ns += "in flight " + std::to_string(-(s64)es.size());
    gs += "in flight " + std::to_string(w.m->m_inFlight);
    finish(f, rec, view_of(m, es), g, w.view(), ns, gs);
}

void handler_hook(Cpu& c) {
    if (!check_due(g_handler)) return wrap_method<&ParticleManager::Handler>()(c);
    check_handler(c, g_handler, 0);
}
void handler_thunk_hook(Cpu& c) {
    if (!check_due(g_handler_thunk)) return thunk<&ParticleManager::Handler, 0xff0>(c);
    check_handler(c, g_handler_thunk, 0xff0);
}

// ---- Tick / DispatchEmitter / Kick: one emitter ----

Fn g_tick("_ZN4Aska15ParticleManager4TickEPNS_16IParticleEmitterEf"), g_dispatch1("_ZN4Aska15ParticleManager15DispatchEmitterEPNS_16IParticleEmitterEb"),
    g_kick("_ZN4Aska15ParticleManager4KickEPNS_16IParticleEmitterE");

// The emitter as the native found it (after its Prepare, for Kick), the lock values its compare-and-swaps
// saw, and the serial its post got.
struct OneEmitter {
    IParticleEmitter* e;
    EState pre, afterPrepare;
    s32 takeSeen = -1, releaseSeen = -1;
    bool posted = false, prepared = false, released = false;
    u32 serial = 0;
    explicit OneEmitter(IParticleEmitter* x) : e(x), pre(EState::of(x)) {}
    void hook(Recorder& rec) {
        rec.on_note = [this](Recorder::Point p, const void* o, s64 v) {
            if (o != e) return;
            if (p == Recorder::kTaken) takeSeen = (s32)v;
            if (p == Recorder::kReleased) releaseSeen = (s32)v, released = true;
        };
        rec.after = [this](Recorder&, Call& k) {
            if (k.kind == CallKind::Post && (k.ret & 1)) posted = true, serial = k.serial;
            if (k.kind == CallKind::Prepare) afterPrepare = EState::of(e), prepared = true;
        };
    }
    const EState& start() const { return prepared ? afterPrepare : pre; }
    // What the native's writes made of it.
    EState want() const {
        EState w = start();
        if (takeSeen != 0) {  // not taken: left alone
            w.lock = takeSeen;
            return w;
        }
        w.idle = 0;
        w.lock = 1;
        if (posted) w.serial = serial;
        if (released) w.idle = 1, w.lock = releaseSeen == 1 ? 0 : releaseSeen;
        return w;
    }
};

void check_one(Cpu& c, Fn& f, HostFn native, bool kick) {
    CheckScope scope;
    auto* m = reinterpret_cast<ParticleManager*>(c.x(0));
    auto* e = reinterpret_cast<IParticleEmitter*>(c.x(1));
    const u64 x2 = c.x(2);
    const float s0 = c.s(0);
    OneEmitter one(e);
    Recorder rec;
    one.hook(rec);
    t_rec = &rec;
    native(c);
    t_rec = nullptr;
    const u64 nativeRet = c.x(0);
    if (one.takeSeen < 0) return check_result(f, Outcome::Mismatch, "the native didn't try the lock");

    World& w = world();
    w.reset(1);
    IParticleEmitter* s = w.e[0];
    one.start().apply(s);
    s->m_dispatchLock = one.takeSeen;
    GuestRun g;
    g.script = &rec.calls;
    g.after = [&](size_t i, Call& k) {
        // the lock as the native's release found it (DispatchEmitter giving up after its failed post)
        if (one.released && k.kind == CallKind::Post && i + 1 == rec.calls.size()) s->m_dispatchLock = one.releaseSeen;
    };
    g.run(f.orig, {(u64)w.m, (u64)s, x2}, &s0);
    std::string ns = one.want().text(), gs = EState::of(s).text();
    if (kick) {
        const s32 delta = one.takeSeen == 0 ? 1 : 0;
        ns += " in flight " + std::to_string(delta);
        gs += " in flight " + std::to_string(w.m->m_inFlight);
    }
    std::string extra;
    if (&f == &g_dispatch1 && (nativeRet & 0xff) != (g.result.x0 & 0xff)) extra = "result: native " + std::to_string(nativeRet & 0xff) + " guest " + std::to_string(g.result.x0 & 0xff);
    View nv = view_of(m, {e}), gv = w.view();
    finish(f, rec, nv, g, gv, ns, gs, extra);
}

void tick_hook(Cpu& c) {
    if (!check_due(g_tick)) return wrap_method<&ParticleManager::Tick>()(c);
    check_one(c, g_tick, wrap_method<&ParticleManager::Tick>(), false);
}
void dispatch1_hook(Cpu& c) {
    if (!check_due(g_dispatch1)) return wrap_method<&ParticleManager::DispatchEmitter>()(c);
    check_one(c, g_dispatch1, wrap_method<&ParticleManager::DispatchEmitter>(), false);
}
void kick_hook(Cpu& c) {
    if (!check_due(g_kick)) return wrap_method<&ParticleManager::Kick>()(c);
    check_one(c, g_kick, wrap_method<&ParticleManager::Kick>(), true);
}

// ---- DispatchEmitters ----

Fn g_dispatch("_ZN4Aska15ParticleManager16DispatchEmittersEv");

void check_dispatch(Cpu& c) {
    CheckScope scope;
    auto* m = reinterpret_cast<ParticleManager*>(c.x(0));
    const u64 n = m->m_dispatchCount;
    if (n > ParticleManager::kListCapacity) {
        wrap_method<&ParticleManager::DispatchEmitters>()(c);
        return check_result(g_dispatch, Outcome::Skipped, "count over the capacity");
    }
    Recorder rec;
    t_rec = &rec;
    wrap_method<&ParticleManager::DispatchEmitters>()(c);
    t_rec = nullptr;
    const u64 nativeRet = c.x(0);
    World& w = world();
    w.reset(0);
    w.m->m_dispatchCount = n;
    GuestRun g;
    g.script = &rec.calls;
    g.run(g_dispatch.orig, {(u64)w.m});
    std::string extra;
    if ((nativeRet & 0xff) != (g.result.x0 & 0xff)) extra = "result differs";
    finish(g_dispatch, rec, view_of(m, {}), g, w.view(), "", "", extra);
}
void dispatch_hook(Cpu& c) {
    if (!check_due(g_dispatch)) return wrap_method<&ParticleManager::DispatchEmitters>()(c);
    check_dispatch(c);
}

// ---- RunLow / RunAfterRendering: the whole list ----

Fn g_runlow("_ZN4Aska15ParticleManager6RunLowEv"), g_runafter("_ZN4Aska15ParticleManager17RunAfterRenderingEv");

void check_list(Cpu& c, Fn& f, HostFn native, bool low) {
    CheckScope scope;
    auto* m = reinterpret_cast<ParticleManager*>(c.x(0));
    const float time0 = m->m_time;  // (only this thread writes the clock and the frame fields)
    const u32 drawn0 = m->m_drawnFrame, slots0[2] = {m->m_frameSlots[0], m->m_frameSlots[1]};
    std::vector<IParticleEmitter*> es;
    std::vector<EState> atLock, want;
    std::map<const void*, s32> takeSeen;
    MState mUnlocking;
    s32 inFlightRead = 0, taken = 0;
    u32 fillRead = 0;
    u8 pendingAtLock = 0;
    bool locked = false, unlocked = false, tooMany = false;
    Recorder rec;
    rec.on_note = [&](Recorder::Point p, const void* o, s64 v) {
        switch (p) {
        case Recorder::kLocked:
            if (o != m) break;
            es = list_of(m);
            tooMany = es.size() > (size_t)World::kMaxEmitters;
            if (tooMany) es.resize(World::kMaxEmitters);
            for (auto* e : es) atLock.push_back(EState::of(e));
            want = atLock;
            pendingAtLock = m->m_buffersPending;
            locked = true;
            break;
        case Recorder::kUnlocking:
            if (o != m) break;
            mUnlocking = MState::of(m, view_of(m, es));
            if (low)
                for (size_t i = 0; i < es.size(); i++) want[i] = EState::of(es[i]);  // (nothing posted yet)
            unlocked = true;
            break;
        case Recorder::kTaken: {
            takeSeen[o] = (s32)v;
            if (v == 0) taken++;
            const int i = index_of(es, o);
            if (!low && i >= 0) {  // RunAfterRendering: what it did to the emitter
                want[i].waitBuffer = 0;
                if (v != 0) want[i].lock = (s32)v;
                else want[i].idle = 0, want[i].lock = 1;
            }
            break;
        }
        case Recorder::kInFlight: inFlightRead = (s32)v; break;
        case Recorder::kFrameRead: fillRead = (u32)v; break;
        default: break;
        }
    };
    rec.after = [&](Recorder&, Call& k) {
        if (low || k.kind != CallKind::Post || !(k.ret & 1)) return;
        const int i = index_of(es, (const void*)k.x[3]);
        if (i >= 0) want[i].serial = k.serial;
    };
    t_rec = &rec;
    native(c);
    t_rec = nullptr;
    if (tooMany) return check_result(f, Outcome::Skipped, "too many emitters");
    if (locked != unlocked) return check_result(f, Outcome::Mismatch, "the native's lock notes don't pair");

    // The shadow: the list as the native found it under the lock (each lock as its compare-and-swap found it).
    World& w = world();
    w.reset((int)es.size());
    for (size_t i = 0; i < es.size(); i++) {
        atLock[i].apply(w.e[i]);
        auto it = takeSeen.find(es[i]);
        if (it != takeSeen.end()) w.e[i]->m_dispatchLock = it->second;
    }
    ParticleManager* s = w.m;
    s->m_time = time0;
    s->m_inFlight = low ? inFlightRead : 0;
    s->m_drawnFrame = drawn0;
    s->m_frameSlots[0] = slots0[0];
    s->m_frameSlots[1] = slots0[1];
    s->m_fillFrame = fillRead;
    s->m_buffersPending = pendingAtLock;
    GuestRun g;
    g.script = &rec.calls;
    g.run(f.orig, {(u64)s});

    // Compare: the native's state where it left the lock (the real objects change after) and the guest's.
    View nv = view_of(m, es), gv = w.view();
    auto bits = [](float x) {
        u32 b;
        std::memcpy(&b, &x, 4);
        return std::to_string(b);
    };
    std::string ns, gs;
    if (low) {
        ns = "time " + bits(m->m_time);
        gs = "time " + bits(s->m_time);
    } else {
        ns = "drawn " + std::to_string(m->m_drawnFrame) + " slots " + std::to_string(m->m_frameSlots[0]) + " " + std::to_string(m->m_frameSlots[1]);
        gs = "drawn " + std::to_string(s->m_drawnFrame) + " slots " + std::to_string(s->m_frameSlots[0]) + " " + std::to_string(s->m_frameSlots[1]);
    }
    if (locked) {
        const MState gm = MState::of(s, gv);
        ns += " pending " + std::to_string(mUnlocking.buffersPending) + "\n";
        gs += " pending " + std::to_string(gm.buffersPending) + "\n";
        if (low) {
            MState nm = mUnlocking;
            nm.time = gm.time;  // (compared above)
            nm.fillFrame = gm.fillFrame, nm.drawnFrame = gm.drawnFrame, nm.frameSlots[0] = gm.frameSlots[0], nm.frameSlots[1] = gm.frameSlots[1];
            ns += nm.text() + "\n";
            gs += gm.text() + "\n";
        }
        for (size_t i = 0; i < es.size(); i++) {
            ns += "E" + std::to_string(i) + " " + want[i].text() + "\n";
            gs += "E" + std::to_string(i) + " " + EState::of(w.e[i]).text() + "\n";
        }
        ns += "in flight +" + std::to_string(taken);
        gs += "in flight +" + std::to_string(s->m_inFlight - (low ? inFlightRead : 0));
    }
    finish(f, rec, nv, g, gv, ns, gs);
}

void runlow_hook(Cpu& c) {
    if (!check_due(g_runlow)) return wrap_method<&ParticleManager::RunLow>()(c);
    check_list(c, g_runlow, wrap_method<&ParticleManager::RunLow>(), true);
}
void runafter_hook(Cpu& c) {
    if (!check_due(g_runafter)) return wrap_method<&ParticleManager::RunAfterRendering>()(c);
    check_list(c, g_runafter, wrap_method<&ParticleManager::RunAfterRendering>(), false);
}

// ---- Run (and its Task thunk): RunLow / RunAfterRendering through their hooks (so they are checked) ----

Fn g_run("_ZN4Aska15ParticleManager3RunEi"), g_run_thunk("_ZThn40_N4Aska15ParticleManager3RunEi");

// Which one the native ran (-1 none, 0 RunLow, 1 RunAfterRendering).
int run_native(Cpu& c, u64 off) {
    const s32 level = (s32)c.x(1);
    c.set_x(0, c.x(0) - off);
    if (level == ParticleManager::kRunAfterRenderingLevel) return runafter_hook(c), 1;
    if (level == ParticleManager::kRunLowLevel) return runlow_hook(c), 0;
    return -1;
}

// The guest's Run with RunLow / RunAfterRendering stubbed: which one it calls, and with which `this`.
void check_run(Cpu& c, Fn& f, u64 off) {
    const u64 x0 = c.x(0), x1 = c.x(1);
    const int nat = run_native(c, off);
    CheckScope scope;
    const u64 low = guest::sym("_ZN4Aska15ParticleManager6RunLowEv"), after = guest::sym("_ZN4Aska15ParticleManager17RunAfterRenderingEv");
    const char* nl = live::ensure_stub(low);
    const char* na = live::ensure_stub(after);
    if (!nl || !na) return check_result(f, Outcome::Skipped, "can't stub RunLow / RunAfterRendering");
    live::drop_stale_code(low);
    live::drop_stale_code(after);
    int got = -1;
    u64 self = 0;
    {
        live::ReplaySession rs;
        rs.answer(nl, [&](Cpu& cc) { got = 0, self = cc.x(0); });
        rs.answer(na, [&](Cpu& cc) { got = 1, self = cc.x(0); });
        guest_call(f.orig, {x0, x1});
    }
    if (got != nat) return check_result(f, Outcome::Mismatch, "level " + std::to_string((s32)x1) + ": native " + std::to_string(nat) + " guest " + std::to_string(got));
    if (got >= 0 && self != x0 - off) return check_result(f, Outcome::Mismatch, "this differs");
    check_result(f, Outcome::Ok);
}
void run_hook(Cpu& c) {
    if (!check_due(g_run)) return (void)run_native(c, 0);
    check_run(c, g_run, 0);
}
void run_thunk_hook(Cpu& c) {
    if (!check_due(g_run_thunk)) return (void)run_native(c, 0x28);
    check_run(c, g_run_thunk, 0x28);
}

// ---- Add / Delete: the links around the element ----

Fn g_add("_ZN4Aska15ParticleManager3AddEPNS_21AnimatableLinkElementE"), g_delete("_ZN4Aska15ParticleManager6DeleteEPNS_21AnimatableLinkElementE");

using Link = containers::LinkElement;

// The nodes a list operation touches, their links named by node (or hex).
struct Nodes {
    std::vector<Link*> n;  // n[0] the sentinel, n[1] the element
    void add(Link* p) {
        if (!p) return;
        for (Link* q : n)
            if (q == p) return;
        n.push_back(p);
    }
    std::string name(const Link* p) const {
        for (size_t i = 0; i < n.size(); i++)
            if (n[i] == p) return "N" + std::to_string(i);
        char b[24];
        snprintf(b, sizeof b, "%#" PRIx64, (u64)p);
        return b;
    }
    std::string text(const std::vector<std::pair<Link*, Link*>>& links, s32 count) const {
        std::string o = "count " + std::to_string(count);
        for (size_t i = 0; i < links.size(); i++) o += " N" + std::to_string(i) + "(" + name(links[i].first) + "," + name(links[i].second) + ")";
        return o;
    }
};

void check_link(Cpu& c, Fn& f, HostFn native) {
    CheckScope scope;
    auto* m = reinterpret_cast<ParticleManager*>(c.x(0));
    auto* e = reinterpret_cast<Link*>(c.x(1));
    Nodes nodes;
    std::vector<std::pair<Link*, Link*>> pre, post;
    s32 countPre = 0, countPost = 0;
    Recorder rec;
    rec.on_note = [&](Recorder::Point p, const void* o, s64) {
        if (o != m) return;
        if (p == Recorder::kLocked) {
            nodes.add(&m->base.m_sentinel);
            nodes.add(e);
            nodes.add(m->base.m_sentinel.m_prev);
            if (e) nodes.add(e->m_prev), nodes.add(e->m_next);
            for (Link* q : nodes.n) pre.push_back({q->m_prev, q->m_next});
            countPre = m->base.m_count;
        } else if (p == Recorder::kUnlocking) {
            for (Link* q : nodes.n) post.push_back({q->m_prev, q->m_next});
            countPost = m->base.m_count;
        }
    };
    t_rec = &rec;
    native(c);
    t_rec = nullptr;
    if (pre.empty() || post.size() != pre.size()) return check_result(f, Outcome::Mismatch, "the native's lock notes don't pair");

    // The shadow: the nodes as copies (the sentinel the shadow manager's), links among them relocated.
    World& w = world();
    w.reset(0);
    const size_t k = nodes.n.size();
    std::vector<Link> copies(k);
    std::vector<Link*> shadow(k);
    shadow[0] = &w.m->base.m_sentinel;
    for (size_t i = 1; i < k; i++) shadow[i] = &copies[i];
    auto reloc = [&](Link* p) -> Link* {
        for (size_t i = 0; i < k; i++)
            if (nodes.n[i] == p) return shadow[i];
        return p;
    };
    for (size_t i = 0; i < k; i++) shadow[i]->m_prev = reloc(pre[i].first), shadow[i]->m_next = reloc(pre[i].second);
    w.m->base.m_count = countPre;
    GuestRun g;
    g.run(f.orig, {(u64)w.m, e ? (u64)shadow[1] : 0});
    Nodes sn;
    sn.n = shadow;
    std::vector<std::pair<Link*, Link*>> got;
    for (Link* q : shadow) got.push_back({q->m_prev, q->m_next});
    if (!g.error.empty()) return check_result(f, Outcome::Mismatch, g.error);
    std::string d = first_diff(nodes.text(post, countPost), sn.text(got, w.m->base.m_count));
    // (hex values are the outside links: the same on both sides)
    check_result(f, d.empty() ? Outcome::Ok : Outcome::Mismatch, d);
}
void add_hook(Cpu& c) {
    if (!check_due(g_add)) return wrap_method<&ParticleManager::Add>()(c);
    check_link(c, g_add, wrap_method<&ParticleManager::Add>());
}
void delete_hook(Cpu& c) {
    if (!check_due(g_delete)) return wrap_method<&ParticleManager::Delete>()(c);
    check_link(c, g_delete, wrap_method<&ParticleManager::Delete>());
}

// ---- getters ----

Fn g_skip("_ZNK4Aska16IParticleEmitter13SkipThisFrameEv"), g_emitting("_ZNK4Aska16IParticleEmitter10IsEmittingEv"),
    g_active("_ZNK4Aska16IParticleEmitter26GetActiveNumberOfParticlesEv"), g_ready("_ZNK4Aska22ParticleRenderableBase13IsBufferReadyEv"),
    g_classid("_ZNK4Aska15ParticleManager10GetClassIDEi"), g_classid_thunk("_ZThn40_NK4Aska15ParticleManager10GetClassIDEi"),
    g_level("_ZNK4Aska15ParticleManager15GetDefaultLevelEv"), g_level_thunk("_ZThn40_NK4Aska15ParticleManager15GetDefaultLevelEv");

template <Fn* F, HostFn N, u64 Mask>
void getter_hook(Cpu& c) {
    if (!check_due(*F)) return N(c);
    live::check_getter(c, *F, N, Mask);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska15ParticleManager7HandlerEm", handler_hook, "particles: ParticleManager::Handler", &g_handler.orig);
NATIVE_FUNCTION_ORIG("_ZThn4080_N4Aska15ParticleManager7HandlerEm", handler_thunk_hook, "particles: ParticleManager::Handler (INotify thunk)",
                     &g_handler_thunk.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska15ParticleManager4TickEPNS_16IParticleEmitterEf", tick_hook, "particles: ParticleManager::Tick", &g_tick.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska15ParticleManager15DispatchEmitterEPNS_16IParticleEmitterEb", dispatch1_hook, "particles: ParticleManager::DispatchEmitter",
                     &g_dispatch1.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska15ParticleManager4KickEPNS_16IParticleEmitterE", kick_hook, "particles: ParticleManager::Kick", &g_kick.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska15ParticleManager16DispatchEmittersEv", dispatch_hook, "particles: ParticleManager::DispatchEmitters", &g_dispatch.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska15ParticleManager6RunLowEv", runlow_hook, "particles: ParticleManager::RunLow", &g_runlow.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska15ParticleManager17RunAfterRenderingEv", runafter_hook, "particles: ParticleManager::RunAfterRendering", &g_runafter.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska15ParticleManager3RunEi", run_hook, "particles: ParticleManager::Run", &g_run.orig);
NATIVE_FUNCTION_ORIG("_ZThn40_N4Aska15ParticleManager3RunEi", run_thunk_hook, "particles: ParticleManager::Run (Task thunk)", &g_run_thunk.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska15ParticleManager3AddEPNS_21AnimatableLinkElementE", add_hook, "particles: ParticleManager::Add", &g_add.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska15ParticleManager6DeleteEPNS_21AnimatableLinkElementE", delete_hook, "particles: ParticleManager::Delete", &g_delete.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska16IParticleEmitter13SkipThisFrameEv", (getter_hook<&g_skip, wrap_method<&IParticleEmitter::SkipThisFrame>(), 0xff>),
                     "particles: IParticleEmitter::SkipThisFrame", &g_skip.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska16IParticleEmitter10IsEmittingEv", (getter_hook<&g_emitting, wrap_method<&IParticleEmitter::IsEmitting>(), 0xff>),
                     "particles: IParticleEmitter::IsEmitting", &g_emitting.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska16IParticleEmitter26GetActiveNumberOfParticlesEv",
                     (getter_hook<&g_active, wrap_method<&IParticleEmitter::GetActiveNumberOfParticles>(), 0xffffffff>),
                     "particles: IParticleEmitter::GetActiveNumberOfParticles", &g_active.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska22ParticleRenderableBase13IsBufferReadyEv",
                     (getter_hook<&g_ready, wrap_method<&ParticleRenderableBase::IsBufferReady>(), 0xff>),
                     "particles: ParticleRenderableBase::IsBufferReady", &g_ready.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska15ParticleManager10GetClassIDEi", (getter_hook<&g_classid, wrap_method<&ParticleManager::GetClassID>(), ~0ull>),
                     "particles: ParticleManager::GetClassID", &g_classid.orig);
NATIVE_FUNCTION_ORIG("_ZThn40_NK4Aska15ParticleManager10GetClassIDEi", (getter_hook<&g_classid_thunk, thunk<&ParticleManager::GetClassID, 0x28>, ~0ull>),
                     "particles: ParticleManager::GetClassID (Task thunk)", &g_classid_thunk.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska15ParticleManager15GetDefaultLevelEv", (getter_hook<&g_level, wrap_method<&ParticleManager::GetDefaultLevel>(), 0xffffffff>),
                     "particles: ParticleManager::GetDefaultLevel", &g_level.orig);
NATIVE_FUNCTION_ORIG("_ZThn40_NK4Aska15ParticleManager15GetDefaultLevelEv",
                     (getter_hook<&g_level_thunk, thunk<&ParticleManager::GetDefaultLevel, 0x28>, 0xffffffff>),
                     "particles: ParticleManager::GetDefaultLevel (Task thunk)", &g_level_thunk.orig);

}  // namespace soa::native::particles
