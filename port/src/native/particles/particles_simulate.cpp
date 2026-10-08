// ParticleEmitter<FeatureList<...>>::Simulate(float), the emitters' per-frame step (IParticleEmitter vtable slot
// 51), for all 74 instantiations (gen/particles_instantiations.inc: tools/gen_particles_instantiations.py checks
// that each one's code is one of the two shapes this body is: with a Texture unit or without), and its live check.
//
// From the decompile in port/decomp/particles/emitter_hot.c, checked against the disassembly. Floating point
// follows the guest instruction for instruction (armf::F: AArch64 NaN rules; no fused multiply-add, the lib has
// none); branches on FCMP take the guest's condition codes (b.ge / b.mi / b.lt: an unordered compare as the
// guest takes it). The emitter's m_simulateLock is a FastCriticalSection the guest inlines: sync's Enter / Leave
// are the same code.
#include <cmath>
#include <cstring>
#include <mutex>

#include "core/loader.h"
#include "native/common/arm_float.h"
#include "core/thread_record.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "native/particles/particles_check.h"

namespace soa::native::particles {

using armf::F;

namespace {

template <typename T>
T value(u64 vaddr) {
    T v;
    std::memcpy(&v, reinterpret_cast<const void*>(main_lib()->base + vaddr), sizeof v);
    return v;
}

}  // namespace

// ---- the real callees (particles_calls.h) ----

namespace calls {
void fill_matrix(IParticleEmitter* e, MatrixContext* m) { guest_call(sym_fill_matrix(), {(u64)e, (u64)m}); }
void affect(u64 fn, IParticleEmitter* e, MathVector* pos, MatrixContext* m, float dt) { guest_invoke<void>(fn, (u64)e, (u64)pos, (u64)m, dt); }
u32 random(u32 n) { return guest_invoke<u32>(sym_random(), n); }
void emit(u64 fn, IParticleEmitter* e, s32 n, EmitContext* ctx, const MatrixContext* m) {
    guest_invoke<void>(fn, (u64)e, (u64)(u32)n, (u64)ctx, (u64)m);
}
void set_animation(IParticleObject* o, s32 index) { guest_call(sym_set_animation(), {(u64)o, (u64)(u32)index}); }
void render(u64 fn, ParticleRenderableBase* r, float dt, MatrixContext* m, bool b) { guest_invoke<void>(fn, (u64)r, (u64)m, (u64)b, dt); }
}  // namespace calls

// The emitter's step: dt scaled by m_timeScale; under m_simulateLock (made by the first Simulate): the
// matrices, the emitter's position (its world translation, moved by the features: EmitterAffectToParticle), the
// particles due (m_emitRate, varied by m_emitRandomness percent), the stop-when-still test, the scale, the
// whole particles emitted (Emit), the texture unit's animation to the object, and the renderable's step.
void IParticleEmitter::Simulate(float dt, const Instantiation& k) {
    if (!m_object || !m_renderable || (m_flags & kFlagPaused)) return;
    if ((u8)(m_linkMode - 1) <= 1 && !m_matrixBuffer) return;
    ParticleRenderableBase* rb = m_renderable;
    rb->m_activeCount = 0;
    const F t = F(m_timeScale) * F(dt);
    FastCriticalSection* lock = SimulateLock();
    if (lock) lock->Enter();
    note(Recorder::kLocked, this, 0);

    MatrixContext mc;
    calls::FillMatrix(this, &mc);
    MathVector pos{mc.world->m[0][3], mc.world->m[1][3], mc.world->m[2][3], 1.0f};
    calls::Affect(k.affect, this, &pos, &mc, t.v);

    const F full(value<float>(kEmitFullRandomness));
    F add;
    if (F(m_emitRandomness) >= full) {
        add = t * F(m_emitRate);
    } else {
        const F pct(value<float>(kPercent));
        const F spread = (full - F(m_emitRandomness)) * pct;
        const F base = t * F(m_emitRate);
        const u32 r = calls::Random(10000);
        const F x = spread * F((float)r) * F(value<float>(kRandomScale));
        add = base * (F(m_emitRandomness) * pct + x);
    }
    m_emitAccum = (add + F(m_emitAccum)).v;

    EmitContext ctx;
    std::memset(&ctx, 0, sizeof ctx);
    if (m_emitFlags & kEmitStopWhenStill) {
        if (m_firstSimulate) {
            m_firstSimulate = 0;
            m_lastPosition = pos;
        } else {
            const F dx = F(m_lastPosition.x) - F(pos.x), dy = F(m_lastPosition.y) - F(pos.y), dz = F(m_lastPosition.z) - F(pos.z);
            const F sum = dx * dx + dy * dy + dz * dz;
            const float d = ::sqrtf(sum.v);  // (FSQRT, and libm's sqrtf when that is a NaN: the host's sqrtf either way)
            if (d < value<float>(kStillDistance) || m_emitRandomness == 0.0f) m_stopped = 1;
        }
    }
    if (m_emitFlags & kEmitScaleFromMatrix) {
        mc.world->PutPRS(nullptr, nullptr, &ctx.m_scale);
        m_scale = ctx.m_scale;
    }
    const F acc(m_emitAccum);
    if (acc >= F(1.0f)) {
        const s32 n = armf::cvtzs(acc.v);
        m_emitAccum = (acc - F((float)n)).v;
        ctx.m_flags = 0;
        ctx.m_dt = t.v;
        calls::Emit(k.emit, this, n, &ctx, &mc);
    }
    if (k.textureOffset) {
        const auto* tex = reinterpret_cast<const TextureUnit*>(reinterpret_cast<const u8*>(this) + k.textureOffset);
        if (m_object->m_animation != tex->m_animation) calls::SetAnimation(m_object, tex->m_animation);
        m_object->m_animParam = tex->m_animParam;
        m_object->m_renderFlags = (u8)((m_object->m_renderFlags & ~1u) | ((tex->m_flags >> 2) & 1u));
    }
    rb->m_emitterPosition = pos;
    calls::Render(k.render, rb, t.v, &mc, m_unk200 < m_unk1fc);
    note(Recorder::kUnlocking, this, 0);
    if (lock) lock->Leave();
}

// ---- the instantiations, bound ----

namespace {

struct Row {
    const char *simulate, *affect, *emit, *render;
    u32 texture;
};
#define PARTICLES_ROW(SIM, AFF, EMIT, REND, TEX) Row{SIM, AFF, EMIT, REND, TEX},
#include "native/particles/gen/particles_instantiations.inc"
constexpr Row kRows[] = {PARTICLES_SIMULATES(PARTICLES_ROW)};
constexpr size_t kNumRows = sizeof kRows / sizeof kRows[0];

const IParticleEmitter::Instantiation& instantiation(size_t i) {
    static IParticleEmitter::Instantiation table[kNumRows];
    static std::once_flag once;
    std::call_once(once, [] {
        for (size_t r = 0; r < kNumRows; r++)
            table[r] = {guest::sym(kRows[r].affect), guest::sym(kRows[r].emit), guest::sym(kRows[r].render), kRows[r].texture};
    });
    return table[i];
}

struct Fn : live::ShadowFn {
    explicit Fn(const char* s) : live::ShadowFn(family(), s) {}
};
template <size_t I>
Fn& fn() {
    static Fn f(kRows[I].simulate);
    return f;
}

// The shadow (this thread's): an emitter (0x400 bytes: the smallest concrete emitter), an object, a
// renderable and a FastCriticalSection of its own (the guest's constructor).
constexpr size_t kEmitterBytes = 0x400, kObjectBytes = 0x200;
struct SimShadow {
    u8* e;
    u8* o;
    ParticleRenderableBase* r;
    FastCriticalSection* lock;
    SimShadow() {
        auto alloc = [](size_t n) {
            void* p = ::operator new(n, std::align_val_t{16});
            std::memset(p, 0, n);
            return p;
        };
        e = static_cast<u8*>(alloc(kEmitterBytes));
        o = static_cast<u8*>(alloc(sizeof(IParticleObject)));
        r = static_cast<ParticleRenderableBase*>(alloc(sizeof(ParticleRenderableBase)));
        lock = static_cast<FastCriticalSection*>(alloc(sizeof(FastCriticalSection)));
        guest_call(guest::sym("_ZN4Aska19FastCriticalSectionC1Ev"), {(u64)lock});
    }
    IParticleEmitter* emitter() const { return reinterpret_cast<IParticleEmitter*>(e); }
};

// The emitter's and the object's bytes (what a callee may have changed).
std::vector<u8> snapshot(const IParticleEmitter* e) {
    std::vector<u8> v(kEmitterBytes + kObjectBytes);
    std::memcpy(v.data(), e, kEmitterBytes);
    if (e->m_object) std::memcpy(v.data() + kEmitterBytes, e->m_object, kObjectBytes);
    return v;
}

void check_simulate(Cpu& c, Fn& f, size_t row) {
    using live::Outcome;
    live::CheckScope scope;
    auto* e = reinterpret_cast<IParticleEmitter*>(c.x(0));
    const float dt = c.s(0);
    const IParticleEmitter::Instantiation& k = instantiation(row);
    if (!e->m_simulateLock) {  // (its first: the lock's allocation isn't replayed)
        e->Simulate(dt, k);
        return live::check_result(f, Outcome::Skipped, "the first Simulate");
    }
    IParticleObject* const realO = e->m_object;
    ParticleRenderableBase* const realR = e->m_renderable;
    std::vector<u8> pre = snapshot(e), post;
    bool unlocked = false;
    Recorder rec;
    rec.on_note = [&](Recorder::Point p, const void* o, s64) {
        if (o != e) return;
        if (p == Recorder::kLocked) pre = snapshot(e);
        if (p == Recorder::kUnlocking) post = snapshot(e), unlocked = true;
    };
    std::vector<u8> before;
    rec.before = [&](Recorder&, const Call&) { before = snapshot(e); };
    rec.after = [&](Recorder&, Call& k2) {  // what the callee changed: the before and after bytes, concatenated
        k2.after = before;
        std::vector<u8> a = snapshot(e);
        k2.after.insert(k2.after.end(), a.begin(), a.end());
    };
    t_rec = &rec;
    e->Simulate(dt, k);
    t_rec = nullptr;

    SimShadow& sh = thread_object<SimShadow>();
    IParticleEmitter* s = sh.emitter();
    auto load = [&](const std::vector<u8>& v) {  // the emitter / object bytes into the shadow, its pointers its own
        std::memcpy(sh.e, v.data(), kEmitterBytes);
        if (realO) std::memcpy(sh.o, v.data() + kEmitterBytes, kObjectBytes);
        s->m_object = realO ? reinterpret_cast<IParticleObject*>(sh.o) : nullptr;
        s->m_renderable = realR ? sh.r : nullptr;
        s->m_simulateLock = sh.lock;
    };
    load(pre);
    auto apply = [&](const std::vector<u8>& ba) {  // the bytes a callee changed in the native run
        const size_t n = ba.size() / 2;
        for (size_t i = 0; i < n; i++) {
            if (ba[i] == ba[n + i]) continue;
            if (i < kEmitterBytes) sh.e[i] = ba[n + i];
            else if (realO) sh.o[i - kEmitterBytes] = ba[n + i];
        }
        s->m_object = realO ? reinterpret_cast<IParticleObject*>(sh.o) : nullptr;
        s->m_renderable = realR ? sh.r : nullptr;
        s->m_simulateLock = sh.lock;
    };
    GuestRun g;
    g.script = &rec.calls;
    g.extra = {{sym_fill_matrix(), CallKind::FillMatrix}, {k.affect, CallKind::Affect}, {sym_random(), CallKind::Random},
               {k.emit, CallKind::Emit},          {sym_set_animation(), CallKind::SetAnimation}, {k.render, CallKind::Render}};
    g.after = [&](size_t i, Call&) {
        if (i < rec.calls.size() && !rec.calls[i].after.empty()) apply(rec.calls[i].after);
    };
    g.run(f.orig, {(u64)s}, &dt);

    View nv, gv;
    nv.e = {e};
    gv.e = {s};
    nv.regions = {{(u64)realO, kObjectBytes, "O"}, {(u64)realR, sizeof(ParticleRenderableBase), "R"}};
    gv.regions = {{(u64)sh.o, kObjectBytes, "O"}, {(u64)sh.r, sizeof(ParticleRenderableBase), "R"}};
    if (!g.error.empty()) return live::check_result(f, Outcome::Mismatch, g.error);
    std::string d = first_diff(nv.texts(rec.calls), gv.texts(g.log));
    if (!d.empty()) return live::check_result(f, Outcome::Mismatch, "calls: " + d);
    if (unlocked) {
        // the emitter (but its pointers to the object / renderable / lock) and the object as the native left them
        std::vector<u8> got = snapshot(s);
        for (size_t off : {offsetof(IParticleEmitter, m_object), offsetof(IParticleEmitter, m_renderable), offsetof(IParticleEmitter, m_simulateLock)})
            std::memcpy(got.data() + off, post.data() + off, 8);
        // (from 0x198: Simulate writes none of its HierarchicalObject base, which the game thread updates
        // meanwhile; a byte the real emitter changed again since the native left it is a race)
        const std::vector<u8> now = snapshot(e);
        for (size_t i = offsetof(IParticleEmitter, m_id); i < got.size(); i++)
            if (got[i] != post[i]) {
                if (now[i] != post[i]) return live::check_result(f, Outcome::Race);
                char m[96];
                snprintf(m, sizeof m, "%s +%#zx: native %02x guest %02x", i < kEmitterBytes ? "emitter" : "object",
                         i < kEmitterBytes ? i : i - kEmitterBytes, post[i], got[i]);
                return live::check_result(f, Outcome::Mismatch, m);
            }
    }
    live::check_result(f, Outcome::Ok);
}

template <size_t I>
void simulate_hook(Cpu& c) {
    if (!live::check_due(fn<I>())) return reinterpret_cast<IParticleEmitter*>(c.x(0))->Simulate(c.s(0), instantiation(I));
    check_simulate(c, fn<I>(), I);
}

template <size_t... I>
bool bind_all(std::index_sequence<I...>) {
    (::soa::register_native_function({kRows[I].simulate, &simulate_hook<I>, "particles: ParticleEmitter<...>::Simulate", nullptr, &fn<I>().orig, nullptr,
                               "simulate_hook"}),
     ...);
    return true;
}
[[maybe_unused]] const bool g_bound = bind_all(std::make_index_sequence<kNumRows>());

}  // namespace

// For the tests: the rows (Simulate symbol, texture offset) and their instantiations.
size_t simulate_rows() { return kNumRows; }
const char* simulate_row_symbol(size_t i) { return kRows[i].simulate; }
const IParticleEmitter::Instantiation& simulate_row(size_t i) { return instantiation(i); }

}  // namespace soa::native::particles
