// Differential tests of IParticleEmitter::Prepare / PrepareMatrices / PrepareMatricesTraverse / FillMatrixContext
// (particles_prepare.cpp): two private sets built alike from a seed (emitters, renderables, objects, linked objects,
// matrix buffers; their vtables the fake one), the guest original on one (its callees stubbed), the native member
// on the other (scripted); the same answers, then the calls and the bytes must match.
#include <cmath>
#include <cstring>
#include <random>
#include <string>

#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "native/particles/particles_check.h"

using namespace soa;
using namespace soa::native::particles;

namespace {

float bits_f(u32 b) {
    float f;
    std::memcpy(&f, &b, 4);
    return f;
}
float any_float(std::mt19937_64& r, float scale = 10.0f) {
    switch (r() % 14) {
    case 0: return bits_f(0x7fc00000u | (u32)(r() & 0xffff));
    case 1: return INFINITY;
    case 2: return -0.0f;
    case 3: return (float)(r() % 1000000) * 1e5f;
    default: return ((float)(r() % 200001) - 100000.0f) / 100000.0f * scale;
    }
}

constexpr int kChain = 4;
// A fake texture (its id at 0x18) the QueryTextureEx answers point at.
alignas(16) u8 g_texture[0x40];

struct Set {
    World w;
    ParticleRenderableBase* r[kChain];
    IParticleObject* o[kChain];
    u8* linked[kChain];
    u8* buffer[kChain];
    u8 anim[kChain][0x20];
    Set() {
        auto alloc = [](size_t n) {
            void* p = ::operator new(n, std::align_val_t{16});
            std::memset(p, 0, n);
            return p;
        };
        for (int i = 0; i < kChain; i++) {
            r[i] = static_cast<ParticleRenderableBase*>(alloc(sizeof(ParticleRenderableBase)));
            o[i] = static_cast<IParticleObject*>(alloc(sizeof(IParticleObject)));
            linked[i] = static_cast<u8*>(alloc(0x1a0));
            buffer[i] = static_cast<u8*>(alloc(0x140));
        }
    }
    IParticleEmitter* e(int i) const { return w.e[i]; }
    static void matrix(std::mt19937_64& g, MathMatrix& m) {
        // a rotation about z with a translation (sometimes scaled, sometimes junk)
        const float a = (float)(g() % 628) / 100.0f, s = g() % 4 ? 1.0f : (float)(g() % 300 + 1) / 100.0f;
        std::memset(&m, 0, sizeof m);
        m.m[0][0] = std::cos(a) * s, m.m[0][1] = -std::sin(a) * s, m.m[1][0] = std::sin(a) * s, m.m[1][1] = std::cos(a) * s, m.m[2][2] = s;
        m.m[0][3] = any_float(g, 100), m.m[1][3] = any_float(g, 100), m.m[2][3] = any_float(g, 100), m.m[3][3] = 1;
        if (g() % 2)  // (any 3x3: every product and sum of the inverse matters)
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++) m.m[i][j] = any_float(g, 2.0f);
        if (g() % 8 == 0) m.m[3][0] = any_float(g);
    }
    static void hoc(std::mt19937_64& g, HierarchicalObject* h) {
        matrix(g, h->m_hoc.m_world);
        for (int i = 0; i < 16; i++) (&h->m_invWorld.m[0][0])[i] = any_float(g);
        h->m_hoc.m_flags = (u8)g();
        h->m_hoc.m_flags2 = g() % 4 ? 0 : (u8)(g() % 4);
        h->m_hoc.m_position = {any_float(g), any_float(g), any_float(g), 1};
    }
    void setup(u64 seed) {
        std::mt19937_64 g(seed);
        w.reset(kChain);
        for (int i = 0; i < kChain; i++) {
            IParticleEmitter* x = e(i);
            hoc(g, &x->base);
            std::memset((void*)r[i], 0, sizeof *r[i]);
            const u64* vt = World::fake_vtable();
            std::memcpy((void*)r[i], &vt, 8);
            hoc(g, &r[i]->base.base);
            r[i]->m_textureName = g() % 2 ? 0x1234 + (g() % 2) : 0;
            r[i]->m_texture = g() % 2 ? g_texture : nullptr;
            r[i]->m_lodFlags = (u8)g();
            std::memset((void*)o[i], 0, 0x200);
            std::memcpy((void*)o[i], &vt, 8);
            for (auto& b : anim[i]) b = 0;
            const u64 name = 0x1234 + (g() % 3);
            std::memcpy(anim[i] + 0x10, &name, 8);
            o[i]->m_animData = g() % 4 ? anim[i] : nullptr;
            o[i]->m_renderLayer = (u16)g();
            o[i]->m_animFlags = (u16)g();
            o[i]->m_textureId = (u32)g();
            std::memset(linked[i], 0, 0x1a0);
            std::memcpy(linked[i], &vt, 8);
            hoc(g, reinterpret_cast<HierarchicalObject*>(linked[i]));
            for (int k = 0; k < 0x140; k++) buffer[i][k] = (u8)g();
            x->m_renderable = r[i];
            x->m_object = o[i];
            x->m_linked = g() % 2 ? reinterpret_cast<HierarchicalObject*>(linked[i]) : nullptr;
            x->m_matrixBuffer = g() % 5 ? buffer[i] : nullptr;
            x->m_child = nullptr;
            x->m_flags = (u16)g();
            x->m_resetMatrices = g() % 3 == 0;
            x->m_linkModeNext = (u8)(g() % 4);
            x->m_linkMode = (u8)(g() % 3);
            x->m_matrixMode = (u8)(g() % 3);
            x->m_simulateLock = nullptr;  // (set by the test: a FastCriticalSection of the set's)
        }
        // the chain: E0 -> E1 -> E2 through the objects (E3 alone); E1's child E3
        o[0]->m_nextEmitter = e(1), o[1]->m_nextEmitter = e(2), o[2]->m_nextEmitter = nullptr, o[3]->m_nextEmitter = nullptr;
        if (g() % 2) e(1)->m_child = e(3);
    }
    View view() const {
        View v = w.view();
        for (int i = 0; i < kChain; i++) {
            v.regions.push_back({(u64)r[i], sizeof *r[i], "R" + std::to_string(i)});
            v.regions.push_back({(u64)o[i], 0x200, "O" + std::to_string(i)});
            v.regions.push_back({(u64)linked[i], 0x1a0, "L" + std::to_string(i)});
            v.regions.push_back({(u64)buffer[i], 0x140, "B" + std::to_string(i)});
        }
        v.regions.push_back({(u64)g_texture, sizeof g_texture, "T"});
        return v;
    }
    std::string bytes() const {
        std::string s;
        auto add = [&](const void* p, size_t from, size_t n) { s.append((const char*)p + from, n); };
        for (int i = 0; i < kChain; i++) {
            add(e(i), 0x40, 0x130);  // (world, inverse, the HOC fields; not the vptrs)
            add(e(i), 0x1e8, 0x328 - 0x1e8);  // (after the pointers to the set's own objects and lock)
            add(r[i], 0x40, 0x170 - 0x40);
            add(r[i], 0x9c0, 0x18);
            add(r[i], 0xf5c, 1);
            add(o[i], 0x10c, 4);
            add(linked[i], 0x40, 0x130);
            add(buffer[i], 0, 0x140);
        }
        return s;
    }
};

struct Answers {
    u64 seed;
    void operator()(Call& c, size_t i) const {
        std::mt19937_64 g(seed * 131 + (u64)c.kind * 7 + i);
        switch (c.kind) {
        case CallKind::VCall:
            if (c.x[1] == IParticleEmitter::kSlotWorldMatrix) c.ret = c.x[0] + offsetof(HierarchicalObject, m_hoc) + offsetof(soa::native::render::HierarchicalObjectContainer, m_world);
            break;
        case CallKind::Malloc: c.ret = 0; break;
        case CallKind::PlacementNew: c.ret = c.x[1]; break;
        case CallKind::QueryTexture: c.ret = g() % 3 ? (u64)g_texture : 0; break;
        default: break;
        }
    }
};

Set& set_g() {
    static Set s;
    return s;
}
Set& set_n() {
    static Set s;
    return s;
}

// fn: 0 Prepare, 1 PrepareMatrices, 2 PrepareMatricesTraverse, 3 FillMatrixContext
bool run_one(TestContext& t, int fn, u64 seed) {
    static const char* names[] = {"_ZN4Aska16IParticleEmitter7PrepareEv", "_ZN4Aska16IParticleEmitter15PrepareMatricesEv",
                                  "_ZN4Aska16IParticleEmitter23PrepareMatricesTraverseEv",
                                  "_ZN4Aska16IParticleEmitter17FillMatrixContextEPNS0_13MatrixContextE"};
    static FastCriticalSection* locks[2] = {};
    for (int k = 0; k < 2; k++)
        if (!locks[k]) {
            locks[k] = static_cast<FastCriticalSection*>(::operator new(sizeof(FastCriticalSection), std::align_val_t{16}));
            std::memset((void*)locks[k], 0, sizeof(FastCriticalSection));
            t.call("_ZN4Aska19FastCriticalSectionC1Ev", {(u64)locks[k]});
        }
    Set &G = set_g(), &N = set_n();
    G.setup(seed);
    N.setup(seed);
    for (int i = 0; i < kChain; i++) G.e(i)->m_simulateLock = locks[0], N.e(i)->m_simulateLock = locks[1];
    MatrixContext gm{}, nm{};
    Answers ans{seed};
    Recorder rec;
    rec.mode = Recorder::kScript;
    rec.answer = ans;
    t_rec = &rec;
    switch (fn) {
    case 0: N.e(0)->Prepare(); break;
    case 1: N.e(0)->PrepareMatrices(); break;
    case 2: N.e(0)->PrepareMatricesTraverse(); break;
    default: N.e(0)->FillMatrixContext(&nm); break;
    }
    t_rec = nullptr;
    GuestRun g;
    g.answer = ans;
    g.extra = {{t.sym(names[2]), CallKind::Traverse},
               {t.sym(names[1]), CallKind::Matrices},
               {t.sym("_ZN4Aska15ParticleManager6MallocEm"), CallKind::Malloc},
               {t.sym("_ZnwmPvm"), CallKind::PlacementNew},
               {t.sym("_ZN4Aska14TextureManager14QueryTextureExEmb"), CallKind::QueryTexture},
               {t.sym("_ZN4Aska22ParticleRenderableBase14SetRenderLayerEjb"), CallKind::SetRenderLayer}};
    if (fn == 3) g.run(t.sym(names[3]), {(u64)G.e(0), (u64)&gm});
    else g.run(t.sym(names[fn]), {(u64)G.e(0)});  // (stubbed itself: GuestRun runs its original)
    const std::string what = std::string(names[fn]) + " seed " + std::to_string(seed);
    if (!rec.error.empty()) return t.fail("%s: native: %s", what.c_str(), rec.error.c_str()), false;
    if (!g.error.empty()) return t.fail("%s: guest: %s", what.c_str(), g.error.c_str()), false;
    View nv = N.view(), gv = G.view();
    std::string d = first_diff(nv.texts(rec.calls), gv.texts(g.log));
    if (!d.empty()) return t.fail("%s: calls: %s", what.c_str(), d.c_str()), false;
    if (N.bytes() != G.bytes()) {
        const std::string a = N.bytes(), b = G.bytes();
        size_t i = 0;
        while (i < a.size() && a[i] == b[i]) i++;
        return t.fail("%s: bytes differ at %zu of the state", what.c_str(), i), false;
    }
    if (fn == 3)
        for (int i = 0; i < 5; i++)
            if (nv.name((u64)(&nm.world)[i]) != gv.name((u64)(&gm.world)[i])) return t.fail("%s: context %d", what.c_str(), i), false;
    return true;
}

}  // namespace

NATIVE_TEST("particles/prepare") {
    for (u64 seed = 1; seed <= 600; seed++)
        if (!run_one(t, 0, seed)) return;
}
NATIVE_TEST("particles/prepare-matrices") {
    for (u64 seed = 1; seed <= 600; seed++)
        if (!run_one(t, 1, seed)) return;
}
NATIVE_TEST("particles/prepare-matrices-traverse") {
    for (u64 seed = 1; seed <= 200; seed++)
        if (!run_one(t, 2, seed)) return;
}
NATIVE_TEST("particles/fill-matrix-context") {
    for (u64 seed = 1; seed <= 400; seed++)
        if (!run_one(t, 3, seed)) return;
}
