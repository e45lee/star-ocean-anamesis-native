// Differential tests of ParticleEmitter<...>::Simulate (particles_simulate.cpp): private emitters, objects and
// renderables built alike from one seed, the guest's Simulate of an instantiation on one set (its callees
// stubbed), the native body with that instantiation's callees on the other (scripted); the same answers
// (matrices, the features' move of the position, Random), then the calls and the bytes must match.
#include <cmath>
#include <cstring>
#include <random>
#include <string>

#include "core/thread_record.h"
#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "native/particles/particles_check.h"

using namespace soa;
using namespace soa::native::particles;

namespace {

constexpr size_t kEmitterBytes = 0x400;

float bits_f(u32 b) {
    float f;
    std::memcpy(&f, &b, 4);
    return f;
}
// Floats: ordinary, zero, negative, big, infinite, NaN.
float any_float(std::mt19937_64& r, float scale = 10.0f) {
    switch (r() % 12) {
    case 0: return bits_f(0x7fc00000u | (u32)(r() & 0xffff));
    case 1: return bits_f(0x7f800001u);
    case 2: return INFINITY;
    case 3: return -INFINITY;
    case 4: return 0.0f;
    case 5: return -0.0f;
    case 6: return (float)(r() % 1000000) * 1e5f;
    default: return ((float)(r() % 200001) - 100000.0f) / 100000.0f * scale;
    }
}

struct Set {
    u8* e;
    IParticleObject* o;
    ParticleRenderableBase* r;
    FastCriticalSection* lock;
    Set() {
        auto alloc = [](size_t n) {
            void* p = ::operator new(n, std::align_val_t{16});
            std::memset(p, 0, n);
            return p;
        };
        e = static_cast<u8*>(alloc(kEmitterBytes));
        o = static_cast<IParticleObject*>(alloc(sizeof(IParticleObject)));
        r = static_cast<ParticleRenderableBase*>(alloc(sizeof(ParticleRenderableBase)));
        lock = static_cast<FastCriticalSection*>(alloc(sizeof(FastCriticalSection)));
        guest_call(guest::sym("_ZN4Aska19FastCriticalSectionC1Ev"), {(u64)lock});
    }
    IParticleEmitter* emitter() const { return reinterpret_cast<IParticleEmitter*>(e); }
    void setup(u64 seed, u32 texture) {
        std::mt19937_64 r1(seed);
        std::memset(e, 0, kEmitterBytes);
        std::memset((void*)o, 0, 0x200);
        std::memset((void*)r, 0, sizeof *r);
        IParticleEmitter* x = emitter();
        x->m_object = r1() % 16 ? o : nullptr;
        x->m_renderable = r1() % 16 ? r : nullptr;
        x->m_flags = r1() % 8 ? 0 : IParticleEmitter::kFlagPaused;
        static const u8 modes[] = {0, 0, 1, 2, 3};
        x->m_linkMode = modes[r1() % 5];
        x->m_matrixBuffer = r1() % 4 ? (void*)0x40 : nullptr;  // (only tested for null)
        x->m_simulateLock = lock;
        x->m_timeScale = r1() % 3 ? 1.0f : any_float(r1, 2.0f);
        x->m_emitRate = any_float(r1, 300.0f);
        static const float rnd[] = {100.0f, 100.0f, 50.0f, 0.0f, 150.0f, 99.5f};
        x->m_emitRandomness = r1() % 8 ? rnd[r1() % 6] : any_float(r1, 100.0f);
        x->m_emitAccum = r1() % 4 ? (float)(r1() % 300) / 100.0f : any_float(r1, 1e3f);
        x->m_emitFlags = (u8)r1();
        x->m_firstSimulate = r1() % 2;
        x->m_lastPosition = {any_float(r1), any_float(r1), any_float(r1), 1.0f};
        x->m_unk1fc = any_float(r1);
        x->m_unk200 = any_float(r1);
        for (size_t i = 0x328; i < kEmitterBytes; i++) e[i] = (u8)r1();  // (the feature units)
        if (texture) e[texture + 0xa] = (u8)(r1() % 3);
        o->m_animation = (u32)(r1() % 3);
        o->m_animParam = (u32)r1();
        o->m_renderFlags = (u8)r1();
        o->m_animFlags = (u16)r1();
        r->m_activeCount = 7;
    }
    View view() const {
        View v;
        v.e = {emitter()};
        v.regions = {{(u64)o, 0x200, "O"}, {(u64)r, sizeof *r, "R"}, {(u64)lock, sizeof *lock, "L"}};
        return v;
    }
};

// Matrices FillMatrixContext answers with (shared by both runs): translations and scales, some with NaNs.
struct Mats {
    math::Matrix m[5];
    void fill(u64 seed) {
        std::mt19937_64 r(seed ^ 0x55);
        for (auto& x : m) {
            std::memset(&x, 0, sizeof x);
            const float s = r() % 4 ? (float)(r() % 300 + 1) / 100.0f : any_float(r);
            x.m[0][0] = s, x.m[1][1] = r() % 2 ? s : s * 2, x.m[2][2] = s, x.m[3][3] = 1;
            if (r() % 3 == 0) x.m[0][1] = any_float(r, 1.0f);
            x.m[0][3] = any_float(r, 50.0f), x.m[1][3] = any_float(r, 50.0f), x.m[2][3] = any_float(r, 50.0f);
        }
    }
};

struct Answers {
    u64 seed;
    const Mats* mats;
    void operator()(Call& c, size_t i) const {
        std::mt19937_64 r(seed * 31 + (u64)c.kind * 1000 + i);
        switch (c.kind) {
        case CallKind::FillMatrix: {
            const math::Matrix* p[5] = {&mats->m[0], &mats->m[1], &mats->m[2], &mats->m[3], r() % 2 ? &mats->m[4] : nullptr};
            std::memcpy(c.out, p, sizeof p);
            c.nout = sizeof p;
            break;
        }
        case CallKind::Affect: {
            if (r() % 3 == 0) break;  // (left as it was)
            const float v[4] = {any_float(r, 50.0f), any_float(r, 50.0f), any_float(r, 50.0f), 1.0f};
            std::memcpy(c.out, v, 16);
            c.nout = 16;
            break;
        }
        case CallKind::Random: c.ret = r() % 10000; break;
        default: break;
        }
    }
};

}  // namespace

// Every instantiation, 40 random emitters each (both shapes, the texture unit at its offsets).
NATIVE_TEST("particles/simulate") {
    static Set G, N;
    static Mats mats;
    const size_t rows = simulate_rows();
    t.expect_eq(rows, (size_t)74, "instantiations");
    int ran = 0, emitted = 0, animated = 0;
    for (size_t row = 0; row < rows; row++) {
        const IParticleEmitter::Instantiation& k = simulate_row(row);
        for (u64 j = 0; j < 40; j++) {
            const u64 seed = row * 1000 + j + 1;
            G.setup(seed, k.textureOffset);
            N.setup(seed, k.textureOffset);
            mats.fill(seed);
            std::mt19937_64 r(seed);
            const float dt = r() % 4 ? 1.0f / 60 : any_float(r, 0.1f);
            Answers ans{seed, &mats};
            Recorder rec;
            rec.mode = Recorder::kScript;
            rec.answer = ans;
            t_rec = &rec;
            N.emitter()->Simulate(dt, k);
            t_rec = nullptr;
            GuestRun g;
            g.answer = ans;
            g.extra = {{sym_fill_matrix(), CallKind::FillMatrix}, {k.affect, CallKind::Affect}, {sym_random(), CallKind::Random},
                       {k.emit, CallKind::Emit},          {sym_set_animation(), CallKind::SetAnimation}, {k.render, CallKind::Render}};
            g.run(t.sym(simulate_row_symbol(row)), {(u64)G.emitter()}, &dt);
            auto where = [&] { return std::string(simulate_row_symbol(row)).substr(0, 120) + " seed " + std::to_string(seed); };
            if (!rec.error.empty()) return t.fail("%s: native: %s", where().c_str(), rec.error.c_str());
            if (!g.error.empty()) return t.fail("%s: guest: %s", where().c_str(), g.error.c_str());
            std::string d = first_diff(N.view().texts(rec.calls), G.view().texts(g.log));
            if (!d.empty()) return t.fail("%s: calls: %s", where().c_str(), d.c_str());
            for (size_t i = 0x198; i < kEmitterBytes; i++)
                if (N.e[i] != G.e[i] && !(i >= 0x1b8 && i < 0x1c8))
                    return t.fail("%s: emitter +%#zx: native %02x guest %02x", where().c_str(), i, N.e[i], G.e[i]);
            if (std::memcmp(N.o, G.o, 0x200) || N.r->m_activeCount != G.r->m_activeCount ||
                std::memcmp(&N.r->m_emitterPosition, &G.r->m_emitterPosition, 16))
                return t.fail("%s: object / renderable differ", where().c_str());
            for (const Call& c : rec.calls) {
                emitted += c.kind == CallKind::Emit;
                animated += c.kind == CallKind::SetAnimation;
            }
            ran++;
        }
    }
    t.expect_eq(ran, (int)rows * 40, "Simulate runs");
    t.expect_eq(emitted > 100 && animated > 50, true, "Emit / SetAnimation reached");
}
