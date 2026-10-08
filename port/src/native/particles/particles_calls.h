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
    size_t perKind[8] = {};
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

}  // namespace calls

}  // namespace soa::native::particles
