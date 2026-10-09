// The shared pieces of the particle manager's checks and tests (particles_check.h): pointer naming, the
// state texts, the private World and the stubbed guest run.
#include <cinttypes>
#include <cstdio>
#include <cstring>

#include "soaruntime/core/loader.h"
#include "native/common/guest_std.h"
#include "native/common/guest_stub.h"
#include "native/common/live_check.h"
#include "native/particles/particles_check.h"

namespace soa::native::particles {

namespace {

std::string hex(u64 v) {
    char b[24];
    snprintf(b, sizeof b, "%#" PRIx64, v);
    return b;
}
std::string fbits(float f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return hex(b);
}
const SimpleMessageDispatcher* real_dispatcher() {
    return &(*reinterpret_cast<kernel::MessageDispatcher* const*>(main_lib()->base + kernel::kVaddrGlobalMessageDispatcher))->base;
}
void* zalloc16(size_t n) {
    void* p = ::operator new(n ? n : 1, std::align_val_t{16});
    std::memset(p, 0, n);
    return p;
}
void zfree16(void* p) { ::operator delete(p, std::align_val_t{16}); }

}  // namespace

// ---- naming ----

std::string View::name(u64 v) const {
    char b[48];
    const u64 mb = (u64)m;
    if (m && v >= mb && v < mb + sizeof(ParticleManager)) {
        snprintf(b, sizeof b, "M+%#" PRIx64, v - mb);
        return b;
    }
    for (size_t i = 0; i < e.size(); i++) {
        const u64 eb = (u64)e[i];
        if (v >= eb && v < eb + sizeof(IParticleEmitter)) {
            if (v == eb) snprintf(b, sizeof b, "E%zu", i);
            else snprintf(b, sizeof b, "E%zu+%#" PRIx64, i, v - eb);
            return b;
        }
    }
    for (const Region& r : regions)
        if (v >= r.base && v < r.base + r.size) {
            if (v == r.base) return r.name;
            snprintf(b, sizeof b, "%s+%#" PRIx64, r.name.c_str(), v - r.base);
            return b;
        }
    const u64 d = (u64)real_dispatcher();
    if (v >= d && v < d + sizeof(kernel::MessageDispatcher)) {
        snprintf(b, sizeof b, "D+%#" PRIx64, v - d);
        return b;
    }
    return hex(v);
}

std::string View::text(const Call& c) const {
    std::string o = kind_name(c.kind);
    o += "(";
    // the out-pointer of the PostMessage forms: the caller's stack, named by being there
    u32 stack = 0;  // the arguments that point into the caller's frame (bits)
    switch (c.kind) {
    case CallKind::PostTask: stack = 1u << 9; break;
    case CallKind::Post: stack = 1u << 7; break;
    case CallKind::FillMatrix: stack = 1u << 1; break;
    case CallKind::Affect: stack = 3u << 1; break;
    case CallKind::Emit: stack = 3u << 2; break;
    case CallKind::Render: stack = 1u << 1; break;
    default: break;
    }
    // the values (not pointers) among the arguments
    u32 values = 0;
    switch (c.kind) {
    case CallKind::Affect: values = 3u << 3; break;
    case CallKind::Emit: values = 1u << 1 | 1u << 4; break;
    case CallKind::Random: values = 1; break;
    case CallKind::SetAnimation: values = 1u << 1; break;
    case CallKind::Render: values = 0xfu << 2; break;
    case CallKind::VCall: values = 1u << 1; break;
    case CallKind::Malloc: values = 1; break;
    case CallKind::PlacementNew: values = 5; break;
    case CallKind::QueryTexture: values = 6; break;
    case CallKind::SetRenderLayer: values = 6; break;
    default: break;
    }
    for (int i = 0; i < c.n; i++) {
        if (i) o += ", ";
        if (stack >> i & 1) o += c.x[i] ? "S" : "0";
        else if (values >> i & 1) o += hex(c.x[i]);
        else o += name(c.x[i]);
    }
    if (c.kind == CallKind::Simulate || c.kind == CallKind::Affect || c.kind == CallKind::Render) o += ", dt " + hex(c.f0);
    o += ") -> " + (c.kind == CallKind::VCall ? name(c.ret) : hex(c.ret));
    if (c.kind == CallKind::GetDt) o += " " + hex(c.fret);
    return o;
}

std::string View::texts(const std::vector<Call>& calls) const {
    std::string o;
    for (const Call& c : calls) o += text(c) + "\n";
    return o;
}

// ---- states ----

EState EState::of(const IParticleEmitter* e) {
    EState s;
    s.idle = __atomic_load_n(&e->m_idle, __ATOMIC_RELAXED);
    s.waitBuffer = e->m_waitBuffer;
    s.linkMode = e->m_linkMode;
    s.matrixMode = e->m_matrixMode;
    s.flags = e->m_flags;
    s.lock = __atomic_load_n(&e->m_dispatchLock, __ATOMIC_SEQ_CST);
    s.serial = e->m_serial;
    s.lastTime = e->m_lastTime;
    s.key = e->m_dispatchKey;
    s.renderable = e->m_renderable;
    return s;
}
void EState::apply(IParticleEmitter* e) const {
    e->m_idle = idle;
    e->m_waitBuffer = waitBuffer;
    e->m_linkMode = linkMode;
    e->m_matrixMode = matrixMode;
    e->m_flags = flags;
    e->m_dispatchLock = lock;
    e->m_serial = serial;
    e->m_lastTime = lastTime;
    e->m_dispatchKey = key;
    e->m_renderable = renderable;
}
std::string EState::text() const {
    char b[96];
    u32 t;
    std::memcpy(&t, &lastTime, 4);
    snprintf(b, sizeof b, "idle %u wait %u lock %d serial %#x last %#x", idle, waitBuffer, lock, serial, t);
    return b;
}

MState MState::of(const ParticleManager* m, const View& v) {
    MState s;
    std::memcpy(&s.time, &m->m_time, 4);
    s.matrixCount = m->m_matrixCount;
    s.dispatchCount = m->m_dispatchCount;
    for (u64 i = 0; i < s.matrixCount && i < ParticleManager::kListCapacity; i++) s.matrixList.push_back(v.name((u64)m->m_matrixList[i]));
    for (u64 i = 0; i < s.dispatchCount && i < ParticleManager::kListCapacity; i++) s.dispatchList.push_back(v.name((u64)m->m_dispatchList[i]));
    s.buffersPending = m->m_buffersPending;
    s.fillFrame = m->m_fillFrame;
    s.drawnFrame = m->m_drawnFrame;
    s.frameSlots[0] = m->m_frameSlots[0];
    s.frameSlots[1] = m->m_frameSlots[1];
    return s;
}
std::string MState::text() const {
    char b[160];
    snprintf(b, sizeof b, "time %#x pending %u drawn %u slots %u %u lists %" PRIu64 " / %" PRIu64 ":", time, buffersPending, drawnFrame,
             frameSlots[0], frameSlots[1], matrixCount, dispatchCount);
    std::string o = b;
    for (const std::string& s : matrixList) o += " " + s;
    o += " |";
    for (const std::string& s : dispatchList) o += " " + s;
    return o;
}

std::string first_diff(const std::string& native, const std::string& guest) {
    if (native == guest) return {};
    size_t i = 0;
    while (i < native.size() && i < guest.size() && native[i] == guest[i]) i++;
    size_t from = native.rfind('\n', i);
    from = from == std::string::npos ? 0 : from + 1;
    auto line = [&](const std::string& s) {
        size_t to = s.find('\n', from);
        std::string l = s.substr(from, to == std::string::npos ? std::string::npos : to - from);
        if (l.size() > 200) l = l.substr(0, 200) + "...";
        return l.empty() ? std::string("(end)") : l;
    };
    return "native \"" + line(native) + "\" | guest \"" + line(guest) + "\"";
}

// ---- the World ----

const char* fake_slot_name(int k) {
    switch (k) {
    case 3: return "particles:v3";
    case 19: return "particles:v19";
    case 20: return "particles:v20";
    case 21: return "particles:v21";
    case 26: return "particles:v26";
    case 29: return "particles:v29";
    default: return "particles:v32";
    }
}

const u64* World::fake_vtable() {
    static const u64* vt = [] {
        auto* t = static_cast<u64*>(zalloc16(64 * 8));
        const u64 trap = fake_function("particles:trap", 1, 0);
        for (int k = 0; k < 64; k++) t[k] = trap;
        for (int k : kFakeSlots) t[k] = fake_function(fake_slot_name(k), 2, 0);
        t[IParticleEmitter::kSlotPrepare] = fake_function("particles:prepare", 1, 0);
        t[IParticleEmitter::kSlotSimulate] = fake_function("particles:simulate", 1, 1);
        return t;
    }();
    return vt;
}

World::World() {
    m = static_cast<ParticleManager*>(zalloc16(sizeof(ParticleManager)));
    guest_call(guest::sym("_ZN4Aska15CriticalSectionC2Ev"), {(u64)&m->m_cs});
    block = static_cast<MessageDispatcherBlock*>(zalloc16(sizeof(MessageDispatcherBlock)));
}
World::~World() {
    for (IParticleEmitter* p : e) zfree16(p);
    zfree16(block);
    // (m_cs's mutex is left: a pthread mutex no thread holds needs no destruction)
    zfree16(m);
}

void World::reset(int count) {
    u8 cs[sizeof(CriticalSection)];
    std::memcpy(cs, &m->m_cs, sizeof cs);
    std::memset((void*)m, 0, sizeof(ParticleManager));
    std::memcpy(&m->m_cs, cs, sizeof cs);
    m->base.m_sentinel.m_prev = m->base.m_sentinel.m_next = &m->base.m_sentinel;
    m->m_matrixList = m->m_matrixStorage;
    m->m_dispatchList = m->m_dispatchStorage;
    if (count > kMaxEmitters) count = kMaxEmitters;
    while ((int)e.size() < count) e.push_back(static_cast<IParticleEmitter*>(zalloc16(sizeof(IParticleEmitter))));
    n = count;
    containers::LinkElement* s = &m->base.m_sentinel;
    for (int i = 0; i < n; i++) {
        std::memset((void*)e[i], 0, sizeof(IParticleEmitter));
        auto& link = e[i]->base.base.link;
        link.vtable = fake_vtable();
        link.m_prev = s->m_prev;
        link.m_next = s;
        s->m_prev->m_next = &link;
        s->m_prev = &link;
    }
    m->base.m_count = n;
    std::memset((void*)block, 0, sizeof(MessageDispatcherBlock));
}

View World::view() const {
    View v;
    v.m = m;
    for (int i = 0; i < n; i++) v.e.push_back(e[i]);
    return v;
}

// ---- the stubbed guest run ----

namespace {

struct Targets {
    u64 postTask, post, wait, getDt, skip, ready;
};
const Targets& targets() {
    static const Targets t = [] {
        Targets t;
        t.postTask = guest::sym("_ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_mmPja");
        t.post = guest::sym("_ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_mmPja");
        t.wait = guest::sym("_ZNK4Aska5Event4WaitEj");
        t.getDt = guest::sym("_ZNK4Aska5VSync5GetDtEi");
        t.skip = guest::sym("_ZNK4Aska16IParticleEmitter13SkipThisFrameEv");
        t.ready = guest::sym("_ZNK4Aska22ParticleRenderableBase13IsBufferReadyEv");
        World::fake_vtable();  // (the fake functions)
        return t;
    }();
    return t;
}

}  // namespace

void GuestRun::run(u64 fn, std::initializer_list<u64> x, const float* s0) {
    const Targets& t = targets();
    live::ReplaySession rs;
    auto respond = [this](CallKind k, Cpu& c, int slot) {
        Call call;
        call.kind = k;
        if (k == CallKind::VCall) {
            const bool arg = slot == 20 || slot == 26 || slot == 29 || slot == 32;
            call.x[0] = c.x(0), call.x[1] = (u64)slot, call.x[2] = arg ? c.x(1) : 0, call.n = 3;
        }
        switch (k) {
        case CallKind::PostTask: {
            const u64* stack = reinterpret_cast<const u64*>(c.sp());
            u64 a[10] = {c.x(0), c.x(1), (u64)(u32)c.x(2), (u64)(u16)c.x(3), c.x(4), c.x(5), c.x(6), c.x(7), stack[0], stack[1]};
            std::memcpy(call.x, a, sizeof a);
            call.n = 10;
            break;
        }
        case CallKind::Post: {
            u64 a[8] = {c.x(0), (u64)(u16)c.x(1), c.x(2), c.x(3), c.x(4), c.x(5), c.x(6), c.x(7)};
            std::memcpy(call.x, a, sizeof a);
            call.n = 8;
            break;
        }
        case CallKind::Wait:
        case CallKind::GetDt:
            call.x[0] = c.x(0);
            call.x[1] = (u32)c.x(1);
            call.n = 2;
            break;
        case CallKind::FillMatrix:
            call.x[0] = c.x(0);
            call.x[1] = c.x(1);
            call.n = 2;
            break;
        case CallKind::Affect:
            call.x[0] = c.x(0);
            call.x[1] = c.x(1);
            call.x[2] = c.x(2);
            std::memcpy(&call.x[3], (const void*)c.x(1), 16);
            call.n = 5;
            call.f0 = (u32)c.v(0).lo;
            break;
        case CallKind::Random:
            call.x[0] = (u32)c.x(0);
            call.n = 1;
            break;
        case CallKind::Emit: {
            call.x[0] = c.x(0);
            call.x[1] = (u32)c.x(1);
            call.x[2] = c.x(2);
            call.x[3] = c.x(3);
            const auto* ctx = reinterpret_cast<const EmitContext*>(c.x(2));
            u32 dt;
            std::memcpy(&dt, &ctx->m_dt, 4);
            call.x[4] = dt | (u64)ctx->m_flags << 32;
            call.n = 5;
            break;
        }
        case CallKind::SetAnimation:
            call.x[0] = c.x(0);
            call.x[1] = (u32)c.x(1);
            call.n = 2;
            break;
        case CallKind::Render: {
            const auto* rb = reinterpret_cast<const ParticleRenderableBase*>(c.x(0));
            call.x[0] = c.x(0);
            call.x[1] = c.x(1);
            call.x[2] = c.x(2) & 0xff;
            std::memcpy(&call.x[3], &rb->m_emitterPosition, 16);
            call.x[5] = (u32)rb->m_activeCount;
            call.n = 6;
            call.f0 = (u32)c.v(0).lo;
            break;
        }
        case CallKind::VCall: break;  // (filled by the slot's answer below)
        case CallKind::PlacementNew:
            call.x[0] = c.x(0), call.x[1] = c.x(1), call.x[2] = c.x(2), call.n = 3;
            break;
        case CallKind::QueryTexture:
            call.x[0] = c.x(0), call.x[1] = c.x(1), call.x[2] = c.x(2) & 0xff, call.n = 3;
            break;
        case CallKind::SetRenderLayer:
            call.x[0] = c.x(0), call.x[1] = (u32)c.x(1), call.x[2] = c.x(2) & 0xff, call.n = 3;
            break;
        case CallKind::Simulate: call.f0 = (u32)c.v(0).lo; [[fallthrough]];
        default:
            call.x[0] = c.x(0);
            call.n = 1;
            break;
        }
        const Call* s = script && next < script->size() ? &(*script)[next] : nullptr;
        bool answered = true;
        if (answer) {
            answer(call, perKind[(int)k]++);
        } else if (s && s->kind == k) {
            next++;
            call.ret = s->ret;
            call.fret = s->fret;
            call.serial = s->serial;
            std::memcpy(call.out, s->out, sizeof call.out);
            call.nout = s->nout;
        } else {
            answered = false;
            if (error.empty()) error = "guest call " + std::to_string(log.size()) + " (" + kind_name(k) + "): not in the native's";
        }
        const int out = k == CallKind::PostTask ? 9 : k == CallKind::Post ? 7 : -1;
        if (out >= 0 && call.x[out] && answered) *reinterpret_cast<u32*>(call.x[out]) = call.serial;
        if (answered && call.nout && (k == CallKind::FillMatrix || k == CallKind::Affect))
            std::memcpy(reinterpret_cast<void*>(call.x[1]), call.out, call.nout);
        if (k == CallKind::VCall && relocate) call.ret = relocate(call.ret);
        c.set_x(0, call.ret);
        if (k == CallKind::GetDt) {
            float f;
            std::memcpy(&f, &call.fret, 4);
            c.set_s(0, f);
        }
        log.push_back(call);
        if (after) after(log.size() - 1, log.back());
        if (log.size() > (script ? script->size() : (size_t)1 << 20) + live::kRunaway) live::stop_runaway(c);
    };
    struct Stubbed {
        u64 addr;
        CallKind kind;
    };
    const Stubbed stubs[] = {{t.postTask, CallKind::PostTask}, {t.post, CallKind::Post},  {t.wait, CallKind::Wait},
                             {t.getDt, CallKind::GetDt},       {t.skip, CallKind::Skip},  {t.ready, CallKind::Ready}};
    for (const Stubbed& s : stubs) {
        const char* name = live::ensure_stub(s.addr);
        if (!name) {
            error = std::string("can't stub ") + kind_name(s.kind);
            return;
        }
        live::drop_stale_code(s.addr);
        const CallKind k = s.kind;
        rs.answer(name, [respond, k](Cpu& c) { respond(k, c, 0); });
    }
    for (const auto& [addr, k] : extra) {
        const char* name = live::ensure_stub(addr);
        if (!name) {
            error = std::string("can't stub ") + kind_name(k);
            return;
        }
        live::drop_stale_code(addr);
        const CallKind kk = k;
        rs.answer(name, [respond, kk](Cpu& c) { respond(kk, c, 0); });
    }
    rs.answer("particles:prepare", [respond](Cpu& c) { respond(CallKind::Prepare, c, 0); });
    rs.answer("particles:simulate", [respond](Cpu& c) { respond(CallKind::Simulate, c, 0); });
    for (int k : kFakeSlots) rs.answer(fake_slot_name(k), [respond, k](Cpu& c) { respond(CallKind::VCall, c, k); });
    rs.answer("particles:trap", [this](Cpu& c) {
        if (error.empty()) error = "the guest called an emitter virtual other than Prepare / Simulate";
        c.set_x(0, 0);
    });
    if (const u64 o = stub_original(fn)) fn = o;  // (fn itself stubbed, for its recursion: its original code)
    GuestArgs a;
    for (u64 v : x) a.i(v);
    if (s0) a.f(*s0);
    result = guest_call(fn, a);
}

u64 sym_fill_matrix() {
    static const u64 a = guest::sym("_ZN4Aska16IParticleEmitter17FillMatrixContextEPNS0_13MatrixContextE");
    return a;
}
u64 sym_random() {
    static const u64 a = guest::sym("_ZN4Aska6RandomEj");
    return a;
}
u64 sym_set_animation() {
    static const u64 a = guest::sym("_ZN4Aska15IParticleObject12SetAnimationEi");
    return a;
}

}  // namespace soa::native::particles
