#pragma once
// The outgoing calls of the particle manager's natives (particles_manager.cpp), through one place so a
// check can see them.
//
// Every call the manager natives make out of the subsystem (the dispatcher's PostMessage forms, the
// dispatcher's free-block Event::Wait, VSync::GetDt, the emitters' virtual Prepare / Simulate) and the two
// emitter predicates RunLow branches on (SkipThisFrame, IsBufferReady) go through these wrappers. With no
// recorder on the thread (the normal run) they are the plain calls. With one (t_rec):
//   - Recorder::kRecord (a live check's native run): the call is made and recorded with its result;
//   - Recorder::kScript (a differential test's native run): the call isn't made; it is recorded and
//     answered from the recorder's script, as the guest run's stubs answer the guest's calls.
// The guest original's calls are logged into the same Call form by the stubs of particles_check.h, so
// the two runs compare call by call.
#include <cstring>
#include <functional>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "native/particles/particles_layout.h"

namespace soa::native::particles {

enum class CallKind : u8 {
    PostTask,   // SimpleMessageDispatcher::PostMessage(Task*, int, u16, INotify*, void*, void*, u64, u64, u32*, s8)
    Post,       // SimpleMessageDispatcher::PostMessage(u16, INotify*, void*, void*, u64, u64, u32*, s8)
    Wait,       // Event::Wait(unsigned int) const (the dispatcher's free-block event)
    GetDt,      // VSync::GetDt(int) const, through the VSync's vtable (slot 0)
    Prepare,    // IParticleEmitter vtable slot 45
    Simulate,   // IParticleEmitter vtable slot 51 (float dt)
    Skip,       // IParticleEmitter::SkipThisFrame() const
    Ready,      // ParticleRenderableBase::IsBufferReady() const
    // Simulate's (particles_simulate.cpp):
    FillMatrix,    // IParticleEmitter::FillMatrixContext(MatrixContext*): out = the five pointers
    Affect,        // ParticleEmitter<...>::EmitterAffectToParticle(Vector*, MatrixContext*, float): out = the vector after
    Random,        // Aska::Random(unsigned int)
    Emit,          // ParticleEmitter<...>::Emit(int, EmitContext*, MatrixContext const*)
    SetAnimation,  // IParticleObject::SetAnimation(int)
    Render,        // ParticleRenderableObject<...>::RenderProcedure(float, MatrixContext*, bool)
    kCount
};
const char* kind_name(CallKind k);

// One outgoing call: its arguments as the callee sees them and its answer.
struct Call {
    CallKind kind{};
    u64 x[10] = {};     // the integer / pointer arguments in order (stack ones included)
    int n = 0;          // how many of x
    u32 f0 = 0;         // the float argument's bits (Simulate's dt)
    // The answer: x0 (a bool / int result), s0 (GetDt), the serial a PostMessage wrote to its out-pointer.
    u64 ret = 0;
    u32 fret = 0;
    u32 serial = 0;
    // What the callee wrote to its out-buffer (FillMatrix, Affect): replayed into the caller's buffer.
    u8 out[48] = {};
    u32 nout = 0;
    // A check's snapshot of the objects after the call (record mode), for the shadow's replay.
    std::vector<u8> after;
};

struct Recorder;
// The thread's recorder (a check's or a test's native run), or none.
extern thread_local Recorder* t_rec;

struct Recorder {
    enum Mode { kRecord, kScript };
    Mode mode = kRecord;
    std::vector<Call> calls;   // in order
    std::vector<Call> script;  // kScript: the answers, in order (kind checked)
    size_t next = 0;
    // kScript, instead of `script`: fills a call's answer from its kind and its index among the calls of
    // that kind (a test's random answers, the same for both runs).
    std::function<void(Call&, size_t)> answer;
    size_t perKind[(int)CallKind::kCount] = {};
    std::string error;         // kScript: the first call the script didn't expect
    // Called before / after each recorded call (both modes), e.g. a check noting what the native saw.
    std::function<void(Recorder&, const Call&)> before;
    std::function<void(Recorder&, Call&)> after;
    // The moments the natives report (note() below), for what a check must see then: kLocked / kUnlocking
    // (m_cs just taken / about to be released: obj the manager), kTaken / kReleased (an emitter's
    // m_dispatchLock compare-and-swap: v the value it found), kTimeRead (Handler: v = the bits of m_time
    // << 32 | the emitter's m_lastTime it read), kInFlight (RunLow: v = the m_inFlight it compared),
    // kFrameRead (RunAfterRendering: v = the m_fillFrame it read).
    enum Point : u8 { kLocked, kUnlocking, kTaken, kReleased, kTimeRead, kInFlight, kFrameRead };
    std::function<void(Point, const void* obj, s64 v)> on_note;

    // Records `c`; in kRecord mode runs `real` (which fills c's answer), in kScript mode answers from
    // the script. Returns the call (its answer).
    template <typename F>
    Call& run(Call c, F&& real) {
        if (before) before(*this, c);
        if (mode == kRecord) {
            t_rec = nullptr;  // (what the callee runs isn't the checked native's)
            real(c);
            t_rec = this;
        } else if (answer) {
            answer(c, perKind[(int)c.kind]++);
        } else if (next < script.size() && script[next].kind == c.kind) {
            const Call& s = script[next++];
            c.ret = s.ret;
            c.fret = s.fret;
            c.serial = s.serial;
            std::memcpy(c.out, s.out, sizeof c.out);
            c.nout = s.nout;
        } else if (error.empty()) {
            error = std::string("call ") + std::to_string(calls.size()) + " (" + kind_name(c.kind) + "): not in the script";
        }
        calls.push_back(c);
        if (after) after(*this, calls.back());
        return calls.back();
    }
};
inline void note(Recorder::Point p, const void* obj, s64 v) {
    Recorder* r = t_rec;
    if (__builtin_expect(r != nullptr, 0) && r->on_note) r->on_note(p, obj, v);
}

namespace calls {

// The real calls.
bool post_task(SimpleMessageDispatcher* d, Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1,
               u32* serialOut, s8 prio);
bool post(SimpleMessageDispatcher* d, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut, s8 prio);
void wait(const Event* e, u32 ms);
float get_dt(const void* vsync, s32 clock);
void prepare(IParticleEmitter* e);
void simulate(IParticleEmitter* e, float dt);
void fill_matrix(IParticleEmitter* e, MatrixContext* m);
void affect(u64 fn, IParticleEmitter* e, MathVector* pos, MatrixContext* m, float dt);
u32 random(u32 n);
void emit(u64 fn, IParticleEmitter* e, s32 n, EmitContext* ctx, const MatrixContext* m);
void set_animation(IParticleObject* o, s32 index);
void render(u64 fn, ParticleRenderableBase* r, float dt, MatrixContext* m, bool b);

// Through the recorder when there is one.
inline bool PostTask(SimpleMessageDispatcher* d, Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1,
                     u32* serialOut, s8 prio) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return post_task(d, task, barrier, msg, notify, a0, a1, k0, k1, serialOut, prio);
    Call c;
    c.kind = CallKind::PostTask;
    u64 a[10] = {(u64)d, (u64)task, (u64)(u32)barrier, msg, (u64)notify, (u64)a0, (u64)a1, k0, k1, (u64)serialOut};
    std::memcpy(c.x, a, sizeof a);
    c.n = 10;
    Call& k = r->run(c, [&](Call& c2) {
        c2.ret = post_task(d, task, barrier, msg, notify, a0, a1, k0, k1, serialOut, prio);
        if (serialOut) c2.serial = *serialOut;
    });
    if (r->mode == Recorder::kScript && serialOut) *serialOut = k.serial;
    return k.ret & 1;
}
inline bool Post(SimpleMessageDispatcher* d, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut, s8 prio) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return post(d, msg, notify, a0, a1, k0, k1, serialOut, prio);
    Call c;
    c.kind = CallKind::Post;
    u64 a[8] = {(u64)d, msg, (u64)notify, (u64)a0, (u64)a1, k0, k1, (u64)serialOut};
    std::memcpy(c.x, a, sizeof a);
    c.n = 8;
    Call& k = r->run(c, [&](Call& c2) {
        c2.ret = post(d, msg, notify, a0, a1, k0, k1, serialOut, prio);
        if (serialOut) c2.serial = *serialOut;
    });
    if (r->mode == Recorder::kScript && serialOut) *serialOut = k.serial;
    return k.ret & 1;
}
inline void Wait(const Event* e, u32 ms) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return wait(e, ms);
    Call c;
    c.kind = CallKind::Wait;
    c.x[0] = (u64)e;
    c.x[1] = ms;
    c.n = 2;
    r->run(c, [&](Call&) { wait(e, ms); });
}
inline float GetDt(const void* vsync, s32 clock) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return get_dt(vsync, clock);
    Call c;
    c.kind = CallKind::GetDt;
    c.x[0] = (u64)vsync;
    c.x[1] = (u64)(u32)clock;
    c.n = 2;
    Call& k = r->run(c, [&](Call& c2) {
        float f = get_dt(vsync, clock);
        std::memcpy(&c2.fret, &f, 4);
    });
    float f;
    std::memcpy(&f, &k.fret, 4);
    return f;
}
inline void Prepare(IParticleEmitter* e) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return prepare(e);
    Call c;
    c.kind = CallKind::Prepare;
    c.x[0] = (u64)e;
    c.n = 1;
    r->run(c, [&](Call&) { prepare(e); });
}
inline void Simulate(IParticleEmitter* e, float dt) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return simulate(e, dt);
    Call c;
    c.kind = CallKind::Simulate;
    c.x[0] = (u64)e;
    c.n = 1;
    std::memcpy(&c.f0, &dt, 4);
    r->run(c, [&](Call&) { simulate(e, dt); });
}
inline bool Skip(const IParticleEmitter* e) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return e->SkipThisFrame();
    Call c;
    c.kind = CallKind::Skip;
    c.x[0] = (u64)e;
    c.n = 1;
    return r->run(c, [&](Call& c2) { c2.ret = e->SkipThisFrame(); }).ret & 1;
}
inline bool Ready(const ParticleRenderableBase* rb) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return rb->IsBufferReady();
    Call c;
    c.kind = CallKind::Ready;
    c.x[0] = (u64)rb;
    c.n = 1;
    return r->run(c, [&](Call& c2) { c2.ret = rb->IsBufferReady(); }).ret & 1;
}

inline void FillMatrix(IParticleEmitter* e, MatrixContext* m) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return fill_matrix(e, m);
    Call c;
    c.kind = CallKind::FillMatrix;
    c.x[0] = (u64)e;
    c.x[1] = (u64)m;
    c.n = 2;
    Call& k = r->run(c, [&](Call& c2) {
        fill_matrix(e, m);
        std::memcpy(c2.out, m, sizeof *m);
        c2.nout = sizeof *m;
    });
    if (r->mode == Recorder::kScript) std::memcpy(m, k.out, sizeof *m);
}
inline void Affect(u64 fn, IParticleEmitter* e, MathVector* pos, MatrixContext* m, float dt) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return affect(fn, e, pos, m, dt);
    Call c;
    c.kind = CallKind::Affect;
    c.x[0] = (u64)e;
    c.x[1] = (u64)pos;
    c.x[2] = (u64)m;
    std::memcpy(&c.x[3], pos, 16);  // (the vector it got: x[3], x[4])
    c.n = 5;
    std::memcpy(&c.f0, &dt, 4);
    Call& k = r->run(c, [&](Call& c2) {
        affect(fn, e, pos, m, dt);
        std::memcpy(c2.out, pos, 16);
        c2.nout = 16;
    });
    if (r->mode == Recorder::kScript && k.nout) std::memcpy(pos, k.out, 16);
}
inline u32 Random(u32 n) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return random(n);
    Call c;
    c.kind = CallKind::Random;
    c.x[0] = n;
    c.n = 1;
    return (u32)r->run(c, [&](Call& c2) { c2.ret = random(n); }).ret;
}
inline void Emit(u64 fn, IParticleEmitter* e, s32 n, EmitContext* ctx, const MatrixContext* m) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return emit(fn, e, n, ctx, m);
    Call c;
    c.kind = CallKind::Emit;
    c.x[0] = (u64)e;
    c.x[1] = (u64)(u32)n;
    c.x[2] = (u64)ctx;
    c.x[3] = (u64)m;
    u32 dt;
    std::memcpy(&dt, &ctx->m_dt, 4);
    c.x[4] = dt | (u64)ctx->m_flags << 32;  // (what Emit reads of the context with flags 0)
    c.n = 5;
    r->run(c, [&](Call&) { emit(fn, e, n, ctx, m); });
}
inline void SetAnimation(IParticleObject* o, s32 index) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return set_animation(o, index);
    Call c;
    c.kind = CallKind::SetAnimation;
    c.x[0] = (u64)o;
    c.x[1] = (u64)(u32)index;
    c.n = 2;
    r->run(c, [&](Call&) { set_animation(o, index); });
}
inline void Render(u64 fn, ParticleRenderableBase* rb, float dt, MatrixContext* m, bool b) {
    Recorder* r = t_rec;
    if (__builtin_expect(!r, 1)) return render(fn, rb, dt, m, b);
    Call c;
    c.kind = CallKind::Render;
    c.x[0] = (u64)rb;
    c.x[1] = (u64)m;
    c.x[2] = b;
    std::memcpy(&c.x[3], &rb->m_emitterPosition, 16);  // (what Simulate left in the renderable: x[3], x[4], x[5])
    c.x[5] = (u32)rb->m_activeCount;
    c.n = 6;
    std::memcpy(&c.f0, &dt, 4);
    r->run(c, [&](Call&) { render(fn, rb, dt, m, b); });
}

}  // namespace calls

}  // namespace soa::native::particles
