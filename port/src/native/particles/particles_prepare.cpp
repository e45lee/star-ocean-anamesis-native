// IParticleEmitter's per-frame preparation (Prepare, vtable slot 45: RunLow / Kick call it on the game thread) and
// its matrices (PrepareMatrices, PrepareMatricesTraverse, FillMatrixContext: what Simulate works with), and their
// live checks.
//
// From the decompiles in port/decomp/particles/emitter.c, checked against the disassembly. The inverse of a world
// matrix without scale / shear (m_hoc.m_flags2 & 3 clear) is inlined in the guest as the transpose with
// -(R^T t) in column 3: here make_inverse, product for product in the guest's operand order (armf::F); with it
// set, Matrix::InvertLowError (guest code). Prepare takes the emitter's m_simulateLock (the one Simulate takes).
#include <cstring>

#include "soaruntime/core/loader.h"
#include "soaruntime/core/thread_record.h"
#include "native/common/arm_float.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "native/common/native_call.h"
#include "native/particles/particles_check.h"

namespace soa::native::particles {

using armf::F;
using Link = containers::LinkElement;

namespace {

u64 slot_of(const void* obj, int k) { return reinterpret_cast<const u64*>(*reinterpret_cast<const u64*>(obj))[k]; }

// The cached inverse world matrix (m_invWorld, valid with m_hoc.m_flags bit 2).
void make_inverse(HierarchicalObject* h) {
    u8 flags = h->m_hoc.m_flags;
    if (flags & 4) return;
    if (h->m_hoc.m_flags2 & 3) {
        static const u64 invert = guest::sym("_ZNK4Aska6Matrix14InvertLowErrorEPS0_");
        guest_call(invert, {(u64)&h->m_hoc.m_world, (u64)&h->m_invWorld});
        flags = h->m_hoc.m_flags;
    } else {
        const float(&m)[4][4] = h->m_hoc.m_world.m;
        float(&o)[4][4] = h->m_invWorld.m;
        const F m00(m[0][0]), m01(m[0][1]), m02(m[0][2]), m03(m[0][3]), m10(m[1][0]), m11(m[1][1]), m12(m[1][2]), m13(m[1][3]),
            m20(m[2][0]), m21(m[2][1]), m22(m[2][2]), m23(m[2][3]);
        const F w0 = -((m00 * m03 + m10 * m13) + m20 * m23);
        const F w1 = -((m03 * m01 + m13 * m11) + m23 * m21);
        const F w2 = -((m03 * m02 + m13 * m12) + m23 * m22);
        const float r0[4] = {m[0][0], m[1][0], m[2][0], m[3][0]}, r1[4] = {m[0][1], m[1][1], m[2][1], m[3][1]},
                    r2[4] = {m[0][2], m[1][2], m[2][2], m[3][2]};
        std::memcpy(o[0], r0, 16);
        std::memcpy(o[1], r1, 16);
        std::memcpy(o[2], r2, 16);
        o[0][3] = w0.v, o[1][3] = w1.v, o[2][3] = w2.v;
        o[3][0] = 0, o[3][1] = 0, o[3][2] = 0, o[3][3] = 1;
    }
    h->m_hoc.m_flags = flags | 4;
}

HierarchicalObject* ho(ParticleRenderableBase* r) { return &r->base.base; }

}  // namespace

// ---- the real callees (particles_calls.h) ----

namespace calls {
// (slot 19 still HierarchicalObject::WorldMatrix, `add x0, x0, #0x40; ret`: its result without a guest call)
u64 vcall(const void* obj, int slot, u64 a1) {
    static const u64 worldMatrix = guest::sym("_ZNK4Aska18HierarchicalObject11WorldMatrixEv");
    const u64 fn = slot_of(obj, slot);
    if (slot == IParticleEmitter::kSlotWorldMatrix && fn == worldMatrix)
        return (u64)&static_cast<const HierarchicalObject*>(obj)->m_hoc.m_world;
    return guest_call(fn, {(u64)obj, a1});
}
// The natives as C++ (native_call.h); through their guest entries (the hooks) with a live check on, so the
// check sees (and stubs) these calls.
NativeCallee kTraverse{"particles", "_ZN4Aska16IParticleEmitter23PrepareMatricesTraverseEv"};
NativeCallee kMatrices{"particles", "_ZN4Aska16IParticleEmitter15PrepareMatricesEv"};
void traverse(IParticleEmitter* e) {
    if (kTraverse.direct()) return e->PrepareMatricesTraverse();
    guest_call(kTraverse.addr(), {(u64)e});
}
void matrices(IParticleEmitter* e) {
    if (kMatrices.direct()) return e->PrepareMatrices();
    guest_call(kMatrices.addr(), {(u64)e});
}
u64 malloc_(u64 n) {
    static const u64 f = guest::sym("_ZN4Aska15ParticleManager6MallocEm");
    return guest_call(f, {n});
}
u64 placement_new(u64 n, u64 p, u64 align) {
    static const u64 f = guest::sym("_ZnwmPvm");
    return guest_call(f, {n, p, align});
}
u64 query_texture(void* tm, u64 name, bool b) {
    static const u64 f = guest::sym("_ZN4Aska14TextureManager14QueryTextureExEmb");
    return guest_call(f, {(u64)tm, name, (u64)b});
}
void set_render_layer(ParticleRenderableBase* r, u32 layer, bool b) {
    static const u64 f = guest::sym("_ZN4Aska22ParticleRenderableBase14SetRenderLayerEjb");
    guest_call(f, {(u64)r, layer, (u64)b});
}
}  // namespace calls

// ---- the members ----

// m_simulateLock, made on first use (operator new(nothrow) + the constructor); null when the allocation fails.
FastCriticalSection* IParticleEmitter::SimulateLock() {
    FastCriticalSection* lock = m_simulateLock;
    if (!lock) {
        static const u64 newNothrow = guest::sym("_ZnwmRKSt9nothrow_t"), nothrow = guest::sym("_ZSt7nothrow");
        lock = reinterpret_cast<FastCriticalSection*>(guest_call(newNothrow, {sizeof(FastCriticalSection), nothrow}));
        if (lock) lock->CtorBase();
        m_simulateLock = lock;
    }
    return lock;
}

// The emitter's world matrix made (when invalid) and inverted, the renderable's (or the emitter's handed to it with
// kFlagMatrixLink), the linked object's made; m_resetMatrices: both remembered positions at the translation.
void IParticleEmitter::PrepareMatrices() {
    if (base.m_hoc.m_flags & 1) calls::VCall(this, kSlotMakeMatrix);
    make_inverse(&base);
    ParticleRenderableBase* rb = m_renderable;
    if (m_flags & kFlagMatrixLink) {
        calls::VCall(rb, kSlotSetPosition, (u64)&base.m_hoc.m_position);
        calls::VCall(m_renderable, kSlotSetPosture, (u64)&base.m_hoc.m_posture);
        calls::VCall(m_renderable, kSlotSetScale, (u64)&base.m_hoc.m_scale);
        rb = m_renderable;
        const u64 wm = calls::VCall(this, kSlotWorldMatrix);
        calls::VCall(rb, kSlotSetWorldMatrix, wm);
    } else if (ho(rb)->m_hoc.m_flags & 1) {
        calls::VCall(rb, kSlotMakeMatrix);
    }
    make_inverse(ho(m_renderable));
    if (m_linked && (m_linked->m_hoc.m_flags & 1)) calls::VCall(m_linked, kSlotMakeMatrix);
    if (m_resetMatrices) {
        const float(&m)[4][4] = base.m_hoc.m_world.m;
        m_lastPosition = {m[0][3], m[1][3], m[2][3], 1.0f};
        m_prevPosition = {m[0][3], m[1][3], m[2][3], 1.0f};
        m_resetMatrices = 0;
    }
}

// This emitter's matrices, its child chain's (m_child) and those of the emitters after it on its object's chain.
void IParticleEmitter::PrepareMatricesTraverse() {
    IParticleEmitter* e = this;
    do {
        calls::Matrices(e);
        if (e->m_child) calls::Traverse(e->m_child);
        e = e->m_object->m_nextEmitter;
    } while (e);
}

// The five matrices: from the matrix buffer (m_linkMode set, not m_matrixMode 1), else the live ones (made first
// with m_matrixMode 1 and m_linkMode set).
void IParticleEmitter::FillMatrixContext(MatrixContext* mc) {
    if (m_matrixMode == 1) {
        if (m_linkMode) calls::Matrices(this);
    } else if (m_linkMode) {
        const auto* b = static_cast<const MathMatrix*>(m_matrixBuffer);
        mc->world = b, mc->invWorld = b + 1, mc->renderWorld = b + 2, mc->renderInvWorld = b + 3, mc->linkedWorld = b + 4;
        return;
    }
    mc->world = reinterpret_cast<const MathMatrix*>(calls::VCall(this, kSlotWorldMatrix));
    mc->invWorld = &base.m_invWorld;
    mc->renderWorld = reinterpret_cast<const MathMatrix*>(calls::VCall(m_renderable, kSlotWorldMatrix));
    mc->renderInvWorld = &ho(m_renderable)->m_invWorld;
    mc->linkedWorld = m_linked ? reinterpret_cast<const MathMatrix*>(calls::VCall(m_linked, kSlotWorldMatrix)) : nullptr;
}

// Under m_simulateLock: m_linkMode from m_linkModeNext and, for modes 1 / 2, the matrix buffer (made on first use:
// ParticleManager::Malloc + placement new) filled with the five matrices (mode 1 makes them first). Then the
// object's texture (looked up once per name in the TextureManager, under its lock), the object's Prepare and the
// renderable's layer.
void IParticleEmitter::Prepare() {
    FastCriticalSection* lock = SimulateLock();
    if (lock) lock->Enter();
    note(Recorder::kLocked, this, 0);
    const u8 mode = m_linkModeNext;
    m_linkMode = mode;
    if (mode == 1 || mode == 2) {
        if (mode == 1) calls::Traverse(this);
        u8* buf = static_cast<u8*>(m_matrixBuffer);
        if (!buf) {
            const u64 p = calls::Malloc(0x140);
            buf = reinterpret_cast<u8*>(calls::PlacementNew(0x140, p, 4));
            if (buf) std::memset(buf, 0, 0x140);
            m_matrixBuffer = buf;
        }
        if (buf) {
            std::memcpy(buf, reinterpret_cast<const void*>(calls::VCall(this, kSlotWorldMatrix)), 0x40);
            std::memcpy(static_cast<u8*>(m_matrixBuffer) + 0x40, &base.m_invWorld, 0x40);
            std::memcpy(static_cast<u8*>(m_matrixBuffer) + 0x80, reinterpret_cast<const void*>(calls::VCall(m_renderable, kSlotWorldMatrix)), 0x40);
            std::memcpy(static_cast<u8*>(m_matrixBuffer) + 0xc0, &ho(m_renderable)->m_invWorld, 0x40);
            u8* last = static_cast<u8*>(m_matrixBuffer) + 0x100;
            if (m_linked) {
                std::memcpy(last, reinterpret_cast<const void*>(calls::VCall(m_linked, kSlotWorldMatrix)), 0x40);
            } else {
                static const float identity[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
                std::memcpy(last, identity, 0x40);
            }
        }
    }
    note(Recorder::kUnlocking, this, 0);
    if (lock) lock->Leave();
    if (!m_object) return;
    if (ParticleRenderableBase* rb = m_renderable) {
        const u8* anim = m_object->m_animData;
        u64 name = 0;
        if (anim) std::memcpy(&name, anim + 0x10, 8);
        if (rb->m_textureName != name) {
            rb->m_textureName = name;
            rb->m_texture = nullptr;
            rb = m_renderable;
            name = rb->m_textureName;
        }
        if (name) {
            const void* t = rb->m_texture;
            if (!t) {
                u8* tm = *reinterpret_cast<u8* const*>(main_lib()->base + render::kVaddrGlobalTextureManager);
                const auto* cs = reinterpret_cast<const CriticalSection*>(tm + 0xb0);  // (TextureManager's lock)
                cs->Enter();
                t = reinterpret_cast<const void*>(calls::QueryTexture(tm, name, true));
                cs->Leave();
                rb->m_texture = t;
            }
            if (t) std::memcpy(&m_object->m_textureId, static_cast<const u8*>(t) + 0x18, 4);
        }
        rb = m_renderable;
        if (rb->m_lodFlags & 0x40) ho(rb)->m_hoc.m_flags &= 0xef;
    }
    calls::VCall(m_object, IParticleObject::kSlotPrepare);
    if (ParticleRenderableBase* rb = m_renderable) calls::SetRenderLayer(rb, m_object->m_renderLayer, (m_object->m_animFlags >> 1) & 1);
}

// ---- the live checks: the guest original on shadows (the emitter, its renderable, object, linked object, the
// emitters of the chain, the matrix buffer), every callee stubbed and answered from the native's record with the
// bytes it changed ----

namespace {

using live::Outcome;

struct Fn : live::ShadowFn {
    explicit Fn(const char* s) : live::ShadowFn(family(), s) {}
};

// Real objects and their private copies.
struct Shadows {
    struct R {
        u8* real;
        u8* shadow;
        size_t size;
        std::string name;
    };
    std::vector<R> r;
    std::vector<u8*> owned;
    ~Shadows() {
        for (u8* p : owned) ::operator delete(p, std::align_val_t{16});
    }
    u8* add(const void* real, size_t size, const std::string& name) {
        auto* p = static_cast<u8*>(::operator new(size, std::align_val_t{16}));
        std::memset(p, 0, size);
        owned.push_back(p);
        r.push_back({(u8*)real, p, size, name});
        return p;
    }
    std::vector<u8> capture() const {
        std::vector<u8> v;
        for (const R& x : r) v.insert(v.end(), x.real, x.real + x.size);
        return v;
    }
    void load(const std::vector<u8>& v) {
        size_t o = 0;
        for (const R& x : r) std::memcpy(x.shadow, v.data() + o, x.size), o += x.size;
    }
    void apply(const std::vector<u8>& before, const std::vector<u8>& after) {
        size_t o = 0;
        for (const R& x : r) {
            for (size_t i = 0; i < x.size; i++)
                if (before[o + i] != after[o + i]) x.shadow[i] = after[o + i];
            o += x.size;
        }
    }
    u64 to_shadow(u64 v) const {
        for (const R& x : r)
            if (v >= (u64)x.real && v < (u64)x.real + x.size) return (u64)x.shadow + (v - (u64)x.real);
        return v;
    }
    View view(bool shadow) const {
        View v;
        for (const R& x : r) v.regions.push_back({(u64)(shadow ? x.shadow : x.real), x.size, x.name});
        return v;
    }
    // Pointers among the copies pointing at reals: to the copies (at the given offsets of each copy).
    void relink(const std::vector<std::pair<size_t, size_t>>& fields) {  // (region index, offset)
        for (auto [i, off] : fields) {
            u64 v;
            std::memcpy(&v, r[i].shadow + off, 8);
            v = to_shadow(v);
            std::memcpy(r[i].shadow + off, &v, 8);
        }
    }
    void vtables() {  // every copy's vtable the fake one
        const u64* vt = World::fake_vtable();
        for (const R& x : r)
            if (x.name[0] == 'E' || x.name[0] == 'R' || x.name[0] == 'O' || x.name[0] == 'L') std::memcpy(x.shadow, &vt, 8);
    }
};

constexpr size_t kEmitterBytes = 0x328, kRenderableBytes = sizeof(ParticleRenderableBase), kObjectBytes = 0x200, kLinkedBytes = 0x1a0;

// The emitter-side objects of one emitter as shadow regions: E (emitter), R, O, L (linked), B (matrix buffer).
void add_emitter(Shadows& s, IParticleEmitter* e, const std::string& tag) {
    s.add(e, kEmitterBytes, "E" + tag);
    if (e->m_renderable) s.add(e->m_renderable, kRenderableBytes, "R" + tag);
    if (e->m_object) s.add(e->m_object, kObjectBytes, "O" + tag);
    if (e->m_linked) s.add(e->m_linked, kLinkedBytes, "L" + tag);
    if (e->m_matrixBuffer) s.add(e->m_matrixBuffer, 0x140, "B" + tag);
}
// The emitter copies' pointers to the other copies.
void relink_emitters(Shadows& s) {
    std::vector<std::pair<size_t, size_t>> f;
    for (size_t i = 0; i < s.r.size(); i++) {
        if (s.r[i].name[0] == 'E')
            for (size_t off : {offsetof(IParticleEmitter, m_object), offsetof(IParticleEmitter, m_renderable), offsetof(IParticleEmitter, m_linked),
                               offsetof(IParticleEmitter, m_matrixBuffer), offsetof(IParticleEmitter, m_child)})
                f.push_back({i, off});
        if (s.r[i].name[0] == 'O') f.push_back({i, offsetof(IParticleObject, m_nextEmitter)});
    }
    s.relink(f);
}

struct Lock {
    FastCriticalSection* p;
    Lock() {
        p = static_cast<FastCriticalSection*>(::operator new(sizeof(FastCriticalSection), std::align_val_t{16}));
        std::memset((void*)p, 0, sizeof *p);
        guest_call(guest::sym("_ZN4Aska19FastCriticalSectionC1Ev"), {(u64)p});
    }
};

// One check: the native run recorded (`run`), the shadows loaded from `pre` (or from the moment noted kLocked),
// the guest original on them, then the calls and the shadows' bytes against the native's at kUnlocking (or after).
void check(Fn& f, Shadows& s, const std::function<void()>& run, const std::function<void(GuestRun&)>& guest,
           const std::vector<std::pair<u64, CallKind>>& extra, bool (*writes)(char region, size_t off), const void* noteObj,
           const std::function<std::string()>& more = {}) {
    std::vector<u8> pre = s.capture(), post, before;
    Recorder rec;
    rec.on_note = [&](Recorder::Point p, const void* o, s64) {
        if (o != noteObj) return;
        if (p == Recorder::kLocked) pre = s.capture();
    };
    rec.before = [&](Recorder&, const Call&) { before = s.capture(); };
    rec.after = [&](Recorder&, Call& k) {
        k.after = before;
        std::vector<u8> a = s.capture();
        k.after.insert(k.after.end(), a.begin(), a.end());
    };
    t_rec = &rec;
    run();
    t_rec = nullptr;
    post = s.capture();  // (Prepare writes the texture fields after releasing its lock: the state at its end)

    s.load(pre);
    s.vtables();
    relink_emitters(s);
    GuestRun g;
    g.script = &rec.calls;
    g.extra = extra;
    g.relocate = [&](u64 v) { return s.to_shadow(v); };
    g.after = [&](size_t i, Call&) {
        if (i >= rec.calls.size() || rec.calls[i].after.empty()) return;
        const std::vector<u8>& ba = rec.calls[i].after;
        const size_t n = ba.size() / 2;
        s.apply(std::vector<u8>(ba.begin(), ba.begin() + n), std::vector<u8>(ba.begin() + n, ba.end()));
        s.vtables();
        relink_emitters(s);
    };
    guest(g);
    if (!g.error.empty()) return live::check_result(f, Outcome::Mismatch, g.error);
    const std::string d = first_diff(s.view(false).texts(rec.calls), s.view(true).texts(g.log));
    if (!d.empty()) return live::check_result(f, Outcome::Mismatch, "calls: " + d);
    // The bytes the function writes itself (its callees' writes were replayed), the copies against the native's.
    // (Only those: the render thread and the workers change the renderable and the object meanwhile.)
    const std::vector<u8> now = s.capture();
    size_t o = 0;
    for (size_t i = 0; i < s.r.size(); o += s.r[i].size, i++) {
        const Shadows::R& x = s.r[i];
        for (size_t b = 0; b < x.size; b++) {
            if (!writes || !writes(x.name[0], b) || x.shadow[b] == post[o + b]) continue;
            if (now[o + b] != post[o + b]) return live::check_result(f, Outcome::Race);
            char m[96];
            snprintf(m, sizeof m, "%s +%#zx: native %02x guest %02x", x.name.c_str(), b, post[o + b], x.shadow[b]);
            return live::check_result(f, Outcome::Mismatch, m);
        }
    }
    if (more) {
        const std::string e = more();
        if (!e.empty()) return live::check_result(f, Outcome::Mismatch, e);
    }
    live::check_result(f, Outcome::Ok);
}

bool in(size_t b, size_t from, size_t to) { return b >= from && b < to; }
// What each function writes itself.
bool prepare_writes(char r, size_t b) {
    switch (r) {
    case 'E': return in(b, 0x210, 0x211);
    case 'B': return true;
    case 'R': return in(b, 0x9c0, 0x9c8) || in(b, 0x9d0, 0x9d8) || in(b, 0x128, 0x129);
    case 'O': return in(b, 0x10c, 0x110);
    default: return false;
    }
}
bool matrices_writes(char r, size_t b) {
    switch (r) {
    case 'E': return in(b, 0x128, 0x129) || in(b, 0x130, 0x170) || in(b, 0x2e0, 0x302);
    case 'R': return in(b, 0x128, 0x129) || in(b, 0x130, 0x170);
    default: return false;
    }
}

Fn g_prepare("_ZN4Aska16IParticleEmitter7PrepareEv"), g_matrices("_ZN4Aska16IParticleEmitter15PrepareMatricesEv"),
    g_traverse("_ZN4Aska16IParticleEmitter23PrepareMatricesTraverseEv"), g_fill("_ZN4Aska16IParticleEmitter17FillMatrixContextEPNS0_13MatrixContextE");

u64 sym_(const char* s) { return guest::sym(s); }

void prepare_hook(Cpu& c) {
    auto* e = reinterpret_cast<IParticleEmitter*>(c.x(0));
    if (!live::check_due(g_prepare)) return e->Prepare();
    live::CheckScope scope;
    // (its first: the lock's or the buffer's allocation isn't replayed; nor an object / renderable missing)
    if (!e->m_simulateLock || !e->m_object || !e->m_renderable || (!e->m_matrixBuffer && (u8)(e->m_linkModeNext - 1) <= 1)) {
        e->Prepare();
        return live::check_result(g_prepare, Outcome::Skipped, "an allocation or a missing object");
    }
    Shadows s;
    add_emitter(s, e, "");
    Lock& lock = thread_object<Lock>();
    check(
        g_prepare, s, [&] { e->Prepare(); },
        [&](GuestRun& g) {
            auto* se = reinterpret_cast<IParticleEmitter*>(s.r[0].shadow);
            se->m_simulateLock = lock.p;
            g.run(g_prepare.orig, {(u64)se});
        },
        {{sym_("_ZN4Aska16IParticleEmitter23PrepareMatricesTraverseEv"), CallKind::Traverse}, {sym_("_ZN4Aska15ParticleManager6MallocEm"), CallKind::Malloc},
         {sym_("_ZnwmPvm"), CallKind::PlacementNew}, {sym_("_ZN4Aska14TextureManager14QueryTextureExEmb"), CallKind::QueryTexture},
         {sym_("_ZN4Aska22ParticleRenderableBase14SetRenderLayerEjb"), CallKind::SetRenderLayer}},
        prepare_writes, e);
}

void matrices_hook(Cpu& c) {
    auto* e = reinterpret_cast<IParticleEmitter*>(c.x(0));
    if (!live::check_due(g_matrices)) return e->PrepareMatrices();
    live::CheckScope scope;
    if (!e->m_renderable) {
        e->PrepareMatrices();
        return live::check_result(g_matrices, Outcome::Skipped, "no renderable");
    }
    Shadows s;
    add_emitter(s, e, "");
    check(
        g_matrices, s, [&] { e->PrepareMatrices(); }, [&](GuestRun& g) { g.run(g_matrices.orig, {(u64)s.r[0].shadow}); }, {}, matrices_writes, e);
}

void fill_hook(Cpu& c) {
    auto* e = reinterpret_cast<IParticleEmitter*>(c.x(0));
    auto* mc = reinterpret_cast<MatrixContext*>(c.x(1));
    if (!live::check_due(g_fill)) return e->FillMatrixContext(mc);
    live::CheckScope scope;
    if (!e->m_renderable) {
        e->FillMatrixContext(mc);
        return live::check_result(g_fill, Outcome::Skipped, "no renderable");
    }
    Shadows s;
    add_emitter(s, e, "");
    MatrixContext* out = reinterpret_cast<MatrixContext*>(s.add(mc, sizeof *mc, "C"));
    check(
        g_fill, s, [&] { e->FillMatrixContext(mc); },
        [&](GuestRun& g) { g.run(g_fill.orig, {(u64)s.r[0].shadow, (u64)out}); },
        {{sym_("_ZN4Aska16IParticleEmitter15PrepareMatricesEv"), CallKind::Matrices}}, nullptr, e, [&] {
            // the context: its pointers, named
            View nv = s.view(false), gv = s.view(true);
            std::string a, b;
            for (int i = 0; i < 5; i++) a += nv.name((u64)(&mc->world)[i]) + " ", b += gv.name((u64)(&out->world)[i]) + " ";
            return a == b ? std::string() : "context: native " + a + "| guest " + b;
        });
}

void traverse_hook(Cpu& c) {
    auto* e = reinterpret_cast<IParticleEmitter*>(c.x(0));
    if (!live::check_due(g_traverse)) return e->PrepareMatricesTraverse();
    live::CheckScope scope;
    // The chain: this emitter and the ones after it on its objects' chain (at most 8).
    Shadows s;
    int n = 0;
    for (IParticleEmitter* x = e; x; x = x->m_object ? x->m_object->m_nextEmitter : nullptr) {
        if (++n > 8 || !x->m_object) {
            e->PrepareMatricesTraverse();
            return live::check_result(g_traverse, Outcome::Skipped, "a long chain or no object");
        }
        s.add(x, kEmitterBytes, "E" + std::to_string(n - 1));
        s.add(x->m_object, kObjectBytes, "O" + std::to_string(n - 1));
    }
    check(
        g_traverse, s, [&] { e->PrepareMatricesTraverse(); }, [&](GuestRun& g) { g.run(g_traverse.orig, {(u64)s.r[0].shadow}); },
        {{sym_("_ZN4Aska16IParticleEmitter15PrepareMatricesEv"), CallKind::Matrices},
         {sym_("_ZN4Aska16IParticleEmitter23PrepareMatricesTraverseEv"), CallKind::Traverse}},
        nullptr, e);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska16IParticleEmitter7PrepareEv", prepare_hook, "particles: IParticleEmitter::Prepare", &g_prepare.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska16IParticleEmitter15PrepareMatricesEv", matrices_hook, "particles: IParticleEmitter::PrepareMatrices", &g_matrices.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska16IParticleEmitter23PrepareMatricesTraverseEv", traverse_hook, "particles: IParticleEmitter::PrepareMatricesTraverse",
                     &g_traverse.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska16IParticleEmitter17FillMatrixContextEPNS0_13MatrixContextE", fill_hook, "particles: IParticleEmitter::FillMatrixContext",
                     &g_fill.orig);

}  // namespace soa::native::particles
