// The particle manager's dispatch (Aska::ParticleManager) and the emitter / renderable predicates it uses,
// as members of the recovered classes (particles_layout.h). Bound with their live checks in
// particles_check.cpp; differential tests in particles_manager_test.cpp.
//
// From the decompiles in port/decomp/particles/manager.c, emitter.c and renderable.c, checked against the
// disassembly. The guest's lock-free updates are LDAXR / STLXR loops; here they are the host atomics on the
// same words (the JIT's exclusive stores are host compare-and-swaps, so the two mix): taking an emitter is a
// compare-and-swap 0 -> 1 of m_dispatchLock that gives up when it isn't 0; Handler / DispatchEmitter put it
// back with 1 -> 0 only (a lock another thread changed meanwhile is left alone); m_inFlight is an atomic add.
#include <cstring>

#include "soaruntime/core/loader.h"
#include "native/common/arm_float.h"
#include "native/particles/particles_calls.h"

namespace soa::native::particles {

thread_local Recorder* t_rec = nullptr;

namespace {

bool take(IParticleEmitter* e) {  // m_dispatchLock 0 -> 1, or false when it wasn't 0
    s32 seen = 0;
    const bool ok = __atomic_compare_exchange_n(&e->m_dispatchLock, &seen, 1, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    note(Recorder::kTaken, e, seen);
    return ok;
}
void release(IParticleEmitter* e) {  // m_dispatchLock 1 -> 0, or nothing when it isn't 1
    s32 seen = 1;
    __atomic_compare_exchange_n(&e->m_dispatchLock, &seen, 0, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
    note(Recorder::kReleased, e, seen);
}
void add(s32& v, s32 d) { __atomic_fetch_add(&v, d, __ATOMIC_SEQ_CST); }

template <typename T>
T* global(u64 vaddr) {
    return *reinterpret_cast<T* const*>(main_lib()->base + vaddr);
}
template <typename T>
T value(u64 vaddr) {
    T v;
    std::memcpy(&v, reinterpret_cast<const void*>(main_lib()->base + vaddr), sizeof v);
    return v;
}
SimpleMessageDispatcher* dispatcher() { return &global<kernel::MessageDispatcher>(kernel::kVaddrGlobalMessageDispatcher)->base; }
u64 slot(const void* obj, int k) { return reinterpret_cast<const u64*>(*reinterpret_cast<const u64*>(obj))[k]; }

}  // namespace

const char* kind_name(CallKind k) {
    switch (k) {
    case CallKind::PostTask: return "PostMessage(Task*)";
    case CallKind::Post: return "PostMessage";
    case CallKind::Wait: return "Event::Wait";
    case CallKind::GetDt: return "VSync::GetDt";
    case CallKind::Prepare: return "Prepare";
    case CallKind::Simulate: return "Simulate";
    case CallKind::Skip: return "SkipThisFrame";
    case CallKind::Ready: return "IsBufferReady";
    case CallKind::FillMatrix: return "FillMatrixContext";
    case CallKind::Affect: return "EmitterAffectToParticle";
    case CallKind::Random: return "Random";
    case CallKind::Emit: return "Emit";
    case CallKind::SetAnimation: return "SetAnimation";
    case CallKind::Render: return "RenderProcedure";
    case CallKind::VCall: return "vcall";
    case CallKind::Traverse: return "PrepareMatricesTraverse";
    case CallKind::Matrices: return "PrepareMatrices";
    case CallKind::Malloc: return "ParticleManager::Malloc";
    case CallKind::PlacementNew: return "operator new(placement)";
    case CallKind::QueryTexture: return "QueryTextureEx";
    case CallKind::SetRenderLayer: return "SetRenderLayer";
    case CallKind::kCount: break;
    }
    return "?";
}

// ---- the plain outgoing calls (particles_calls.h) ----

namespace calls {
bool post_task(SimpleMessageDispatcher* d, Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1,
               u32* serialOut, s8 prio) {
    return d->PostMessage(task, barrier, msg, notify, a0, a1, k0, k1, serialOut, prio);
}
bool post(SimpleMessageDispatcher* d, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut, s8 prio) {
    return d->PostMessage(msg, notify, a0, a1, k0, k1, serialOut, prio);
}
void wait(const Event* e, u32 ms) { e->Wait(ms); }
float get_dt(const void* vsync, s32 clock) { return guest_invoke<float>(slot(vsync, 0), (u64)vsync, clock); }
void prepare(IParticleEmitter* e) { guest_call(slot(e, IParticleEmitter::kSlotPrepare), {(u64)e}); }
void simulate(IParticleEmitter* e, float dt) { guest_invoke<void>(slot(e, IParticleEmitter::kSlotSimulate), (u64)e, dt); }
}  // namespace calls

// ---- IParticleEmitter / ParticleRenderableBase ----

bool IParticleEmitter::SkipThisFrame() const {
    if (!(m_flags & kFlagSkippable)) return false;
    return m_renderable && (m_renderable->base.m_renderFlags & 0x2101) != 0;
}
bool IParticleEmitter::IsEmitting() const { return m_renderable && m_renderable->m_activeCount != 0; }
s32 IParticleEmitter::GetActiveNumberOfParticles() const { return m_renderable ? m_renderable->m_activeCount : 0; }
void IParticleEmitter::CallPrepare() { calls::Prepare(this); }
void IParticleEmitter::CallSimulate(float dt) { calls::Simulate(this, dt); }

// A half filled in frame `stamp` (0: never filled) is ready once the manager has drawn that frame:
// m_drawnFrame >= stamp, unless the counters wrapped in between (the comparisons are unsigned).
bool ParticleRenderableBase::IsBufferReady() const {
    const ParticleManager* m = global<ParticleManager>(kVaddrGlobalParticleManager);
    const u32 stamp = m_stamp[m_buffer];
    if (stamp == 0) return true;
    const u32 fill = m->m_fillFrame, drawn = m->m_drawnFrame;
    const bool wrapped = fill >= stamp ? drawn > fill : drawn < fill;
    return drawn >= stamp && !wrapped;
}

// ---- ParticleManager ----

u64 ParticleManager::GetClassID(s32 depth) const {
    switch (depth) {
    case 0: return 0xf01b;
    case 1: return 0xf000f001f002;
    case 2: return 0xf000f001;
    default: return 0xf000;
    }
}
u32 ParticleManager::GetDefaultLevel() const { return 0x10004000; }

IParticleEmitter* ParticleManager::FirstEmitter() const {
    const containers::LinkElement* e = base.m_sentinel.m_next;
    return e == &base.m_sentinel ? nullptr : reinterpret_cast<IParticleEmitter*>(const_cast<containers::LinkElement*>(e));
}
IParticleEmitter* ParticleManager::NextEmitter(const IParticleEmitter* e) const {
    const containers::LinkElement* n = e->base.base.link.m_next;
    return n == &base.m_sentinel ? nullptr : reinterpret_cast<IParticleEmitter*>(const_cast<containers::LinkElement*>(n));
}

// Appended at the list's end, under m_cs.
void ParticleManager::Add(containers::LinkElement* e) {
    m_cs.Enter();
    note(Recorder::kLocked, this, 0);
    containers::LinkElement* tail = base.m_sentinel.m_prev;
    e->m_prev = tail;
    e->m_next = &base.m_sentinel;
    base.m_sentinel.m_prev = e;
    tail->m_next = e;
    base.m_count++;
    note(Recorder::kUnlocking, this, 0);
    m_cs.Leave();
}

// Unlinked under m_cs (not the sentinel, not null); the count doesn't go below 0.
void ParticleManager::Delete(containers::LinkElement* e) {
    m_cs.Enter();
    note(Recorder::kLocked, this, 0);
    if (e != &base.m_sentinel && e) {
        containers::LinkElement* prev = e->m_prev;
        containers::LinkElement* next = e->m_next;
        if (prev) prev->m_next = next;
        if (next) next->m_prev = prev;
        if (base.m_count > 0) base.m_count--;
        e->m_prev = nullptr;
        e->m_next = nullptr;
    }
    note(Recorder::kUnlocking, this, 0);
    m_cs.Leave();
}

void ParticleManager::Run(s32 level) {
    if (level == kRunAfterRenderingLevel) return RunAfterRendering();
    if (level == kRunLowLevel) return RunLow();
}

// One emitter of a Simulate message: dt = the time since its last Simulate, at most kMaxSimulateDt
// (FMIN: a NaN propagates); then it's idle and undispatched again.
void ParticleManager::SimulateOne(IParticleEmitter* e, float maxDt) {
    e->m_serial = 0xffffffff;
    const float now = m_time;
    const float last = e->m_lastTime;
    e->m_lastTime = now;
    if (__builtin_expect(t_rec != nullptr, 0)) {
        u32 a, b;
        std::memcpy(&a, &now, 4);
        std::memcpy(&b, &last, 4);
        note(Recorder::kTimeRead, e, (s64)((u64)a << 32 | b));
    }
    e->CallSimulate(armf::min(armf::sub(now, last), maxDt));
    e->m_idle = 1;
    release(e);
    add(m_inFlight, -1);
}

// The workers' Simulate messages: m_arg0 the emitter list, m_arg1 its length (0: m_arg0 is one emitter).
void ParticleManager::Handler(MessageDispatcherBlock* b) {
    const u64 n = (u64)b->m_arg1;
    const float maxDt = value<float>(kMaxSimulateDt);
    if (n == 0) return SimulateOne(static_cast<IParticleEmitter*>(b->m_arg0), maxDt);
    IParticleEmitter* const* list = static_cast<IParticleEmitter* const*>(b->m_arg0);
    for (u64 i = 0; i < n; i++) SimulateOne(list[i], maxDt);
}

// The 0x29a message for one emitter (its key k0 keeps it on one worker), retried after each wait for a
// free block; the serial goes to m_serial.
bool ParticleManager::PostSimulate(IParticleEmitter* e, bool wait) {
    SimpleMessageDispatcher* d = dispatcher();
    u32 serial = 0;
    if (!calls::Post(d, kMsgSimulate, &m_notify, e, nullptr, e->m_dispatchKey, 0, &serial, 0)) {
        if (!wait) return false;
        do calls::Wait(&d->m_freeBlockEvent, 0);
        while (!calls::Post(d, kMsgSimulate, &m_notify, e, nullptr, e->m_dispatchKey, 0, &serial, 0));
    }
    e->m_serial = serial;
    return true;
}

// Dispatches one emitter for a Simulate unless it is dispatched already. With `wait` false a full queue
// gives up (the emitter idle and undispatched again).
bool ParticleManager::DispatchEmitter(IParticleEmitter* e, bool wait) {
    if (!take(e)) return false;
    e->m_idle = 0;
    if (PostSimulate(e, wait)) return true;
    e->m_idle = 1;
    release(e);
    return false;
}

// Simulate on this thread (no dispatch) unless the emitter is dispatched already; it stays taken (the
// guest's Tick never releases it).
void ParticleManager::Tick(IParticleEmitter* e, float dt) {
    if (!take(e)) return;
    e->m_idle = 0;
    e->CallSimulate(dt);
}

// The make-matrix message (Task form: the task's barrier), retried after each wait for a free block.
void ParticleManager::PostMakeMatrix(u32 barrier, void* a0, void* a1, u64 k0) {
    SimpleMessageDispatcher* d = dispatcher();
    while (!calls::PostTask(d, &base.task, (s32)barrier, kMsgMakeMatrix, &m_makeMatrix, a0, a1, k0, 0, nullptr, 0))
        calls::Wait(&d->m_freeBlockEvent, 0);
}

// Starts one emitter now: Prepare, its matrices (unless m_linkMode), then its Simulate (waiting for a free
// block). Counted in m_inFlight first; uncounted when it is dispatched already.
void ParticleManager::Kick(IParticleEmitter* e) {
    e->CallPrepare();
    add(m_inFlight, 1);
    if (!e->m_linkMode) {
        SimpleMessageDispatcher* d = dispatcher();
        const s32* level = reinterpret_cast<const s32*>(main_lib()->base + kVaddrTaskLevelForMakeMatrix);
        while (!calls::PostTask(d, &base.task, *level, kMsgMakeMatrix, &m_makeMatrix, e, nullptr, e->m_dispatchKey, 0, nullptr, 0))
            calls::Wait(&d->m_freeBlockEvent, 0);
    }
    if (!take(e)) {
        add(m_inFlight, -1);
        return;
    }
    e->m_idle = 0;
    PostSimulate(e, true);
}

// A Simulate message for n emitters, retried after each wait for a free block.
void ParticleManager::PostSimulateList(u16 msg, IParticleEmitter** list, u64 n) {
    SimpleMessageDispatcher* d = dispatcher();
    while (!calls::Post(d, msg, &m_notify, list, (void*)n, 0, 0, nullptr, 0)) calls::Wait(&d->m_freeBlockEvent, 0);
}

// RunLow's list, one message per worker: with W > 1 workers, W - 1 messages (0x29a + i) of n / W emitters
// each (none when n < W) and the rest in message 0x29a + W - 1 (m_dispatchCount read again after the
// first ones).
bool ParticleManager::DispatchEmitters() {
    u64 n = m_dispatchCount;
    if (!n) return true;
    IParticleEmitter** list = m_dispatchList;
    const s32 workers = dispatcher()->m_workerCount;
    if (workers <= 1) {
        PostSimulateList(kMsgSimulate, list, n);
        return true;
    }
    const u64 chunk = n / (u64)(s64)workers;
    u64 done = 0;
    if (chunk) {
        for (s32 i = 0; i < workers - 1; i++) {
            PostSimulateList((u16)(kMsgSimulate + i), list, chunk);
            list += chunk;
            done += chunk;
        }
        n = m_dispatchCount;
    }
    if (n - done) PostSimulateList((u16)(kMsgSimulate + workers - 1), list, n - done);
    return true;
}

// The frame's start (level 0xe): the clock advanced by VSync's dt; then, unless emitters of the last
// round are still in flight, under m_cs: every enabled emitter prepared, the ones to make matrices for
// listed, the ones to simulate taken and listed (an emitter whose buffer isn't drawn yet waits for
// RunAfterRendering instead), and the lists sent: the make-matrix list as one message (its handler
// dispatches), else the Simulate list (DispatchEmitters).
void ParticleManager::RunLow() {
    const void* vsync = global<void>(kernel::kVaddrGlobalVSync);
    const float dt = calls::GetDt(vsync, 0);
    m_time = armf::add(dt, m_time);
    const s32 inFlight = m_inFlight;
    note(Recorder::kInFlight, this, inFlight);
    if (inFlight > 0) return;
    m_cs.Enter();
    for (IParticleEmitter* e = FirstEmitter(); e; e = NextEmitter(e))
        if (e->m_flags & IParticleEmitter::kFlagEnabled) e->CallPrepare();
    note(Recorder::kLocked, this, 0);
    m_matrixCount = 0;
    m_dispatchCount = 0;
    if (base.m_count != 0) {
        for (IParticleEmitter* e = FirstEmitter(); e; e = NextEmitter(e)) {
            if (!(e->m_flags & IParticleEmitter::kFlagEnabled) || calls::Skip(e) || e->m_waitBuffer || e->m_linkMode) continue;
            if (m_matrixCount >= kListCapacity) break;
            m_matrixList[m_matrixCount] = e;
            m_matrixCount++;
        }
        for (IParticleEmitter* e = FirstEmitter(); e; e = NextEmitter(e)) {
            if (!(e->m_flags & IParticleEmitter::kFlagEnabled) || calls::Skip(e) || e->m_waitBuffer || e->m_matrixMode) continue;
            if (m_dispatchCount >= kListCapacity) break;
            if (!calls::Ready(e->m_renderable)) {
                e->m_waitBuffer = 1;
                m_buffersPending = 1;
                continue;
            }
            if (!take(e)) continue;
            e->m_idle = 0;
            m_dispatchList[m_dispatchCount] = e;
            m_dispatchCount++;
            e->m_waitBuffer = 0;
            add(m_inFlight, 1);
        }
    }
    note(Recorder::kUnlocking, this, 0);
    m_cs.Leave();
    if (const u64 n = m_matrixCount) {
        PostMakeMatrix(0x10, m_matrixList, (void*)n, 0);
        return;
    }
    if (m_dispatchCount) DispatchEmitters();
}

// After the frame's rendering (level 0x1c): the frame stamps advanced, and every emitter RunLow left
// waiting for its buffer counted in flight and dispatched (uncounted when it is dispatched already).
void ParticleManager::RunAfterRendering() {
    const u32 fill = m_fillFrame;
    note(Recorder::kFrameRead, this, fill);
    m_frameSlots[m_frameSlots[1]] = fill;  // (the index is the second slot itself)
    const u32 drawn = m_frameSlots[0];
    m_frameSlots[0] = 0;
    m_frameSlots[1] = 0;
    m_drawnFrame = drawn;
    m_cs.Enter();
    note(Recorder::kLocked, this, 0);
    if (m_buffersPending) {
        for (IParticleEmitter* e = FirstEmitter(); e; e = NextEmitter(e)) {
            if (!e->m_waitBuffer) continue;
            e->m_waitBuffer = 0;
            add(m_inFlight, 1);
            if (!take(e)) {
                add(m_inFlight, -1);
                continue;
            }
            e->m_idle = 0;
            PostSimulate(e, true);
        }
        m_buffersPending = 0;
    }
    note(Recorder::kUnlocking, this, 0);
    m_cs.Leave();
}

}  // namespace soa::native::particles
