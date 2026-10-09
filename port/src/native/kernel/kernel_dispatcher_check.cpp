// The live check of the dispatcher natives (kernel_check.h) and their hooks.
//
// A checked call runs the native for real with t_dobs set: it records the dispatcher, its worker
// array and its block storage as it found them once it held m_cs ("pre") and as it left them
// before releasing m_cs ("post"), the counters its queued sync-end messages wait on, and what its
// wake passes read and Set. The check then loads "pre" into this thread's shadow arena (a private
// copy at other addresses: every pointer into the three regions relocated, the queued blocks'
// counters moved to arena slots holding the recorded values, a lock word that is free, a semaphore
// and events of its own whose flags are copied) and runs the guest original on it (the hook's
// trampoline, with the caller's stack arguments in place): the shadow after it, mapped back to the
// real addresses, must equal "post", the results must match, and the guest's wake pass (on shadow
// workers given the flags the native read) must Set the same workers.
//
// Not compared: the lock and semaphore (the shadow's own), the events' pthread objects (their
// flags are compared), the Send* forms' m_event (each run's own stack event), and the (Task*,
// barrier) forms' m_barrierManager: the replay gets a copy of the task whose owner is null, so the
// guest doesn't register the barrier a second time on the real task manager (the natives' barrier
// calls are covered by the differential tests, kernel/dispatcher-*). Workers other than the
// caller's are compared only where the call writes them.
#include <cinttypes>
#include <cstdlib>
#include <cstring>
#include <new>

#include "soaruntime/core/cpu.h"
#include "soaruntime/hle/thread.h"
#include "native/common/guest_std.h"
#include "native/common/native_method.h"
#include "native/kernel/kernel_check.h"
#include "native/sync/sync_check.h"

namespace soa::native::kernel {

live::ShadowFamily& family() {
    static live::ShadowFamily f("kernel", 16);
    return f;
}
thread_local DispatchObservation* t_dobs = nullptr;
u64 g_get_message_orig = 0;  // the trampoline to the guest's GetMessage(block, int) (installed natives only)

namespace {

[[maybe_unused]] live::ShadowFamily& g_registered = family();

constexpr size_t kDispatcherBytes = sizeof(SimpleMessageDispatcher);
constexpr size_t kEventHeader = offsetof(Event, m_signaled);  // m_pMutex, the mutex and the cond: the shadow's own

// The three regions of a dispatcher's state.
struct Shape {
    u64 d = 0;
    u64 w = 0;  // the worker array's new[] cookie (m_workers - 8), 0 without workers
    u64 s = 0;  // the block storage
    u32 wbytes = 0, sbytes = 0;
    s32 nworkers = 0;
    u32 nblocks = 0;
    size_t total() const { return kDispatcherBytes + wbytes + sbytes; }
    static Shape of(const SimpleMessageDispatcher* d) {
        Shape sh;
        sh.d = (u64)d;
        sh.nworkers = d->m_workers ? d->m_workerCount : 0;
        if (sh.nworkers < 0 || sh.nworkers > kMaxWorkers) sh.nworkers = 0;
        if (sh.nworkers) {
            sh.w = (u64)d->m_workers - 8;
            sh.wbytes = 8 + (u32)sh.nworkers * sizeof(WorkerThread);
        }
        sh.s = (u64)d->m_blockStorage;
        sh.nblocks = d->m_freeBlocks.m_capacity ? d->m_freeBlocks.m_capacity - 1 : 0;
        if (sh.s) sh.sbytes = sh.nblocks * (u32)sizeof(MessageDispatcherBlockForList) + (sh.nblocks + 1) * 8;
        return sh;
    }
    bool same(const Shape& o) const { return d == o.d && w == o.w && s == o.s && wbytes == o.wbytes && sbytes == o.sbytes; }
};

void capture(const SimpleMessageDispatcher* d, std::vector<u8>& out) {
    Shape sh = Shape::of(d);
    out.resize(sh.total());
    std::memcpy(out.data(), (const void*)sh.d, kDispatcherBytes);
    if (sh.wbytes) std::memcpy(out.data() + kDispatcherBytes, (const void*)sh.w, sh.wbytes);
    if (sh.sbytes) std::memcpy(out.data() + kDispatcherBytes + sh.wbytes, (const void*)sh.s, sh.sbytes);
}

}  // namespace

void DispatchObservation::capture_pre(const SimpleMessageDispatcher* d) {
    if (have_pre) return;  // (the outermost lock: CancelMessage's DeleteMessage)
    capture(d, pre);
    have_pre = true;
    // The queued sync-end messages' counters, as GetMessage will read them.
    const LinkElement* sentinel = &d->m_queue.m_sentinel.link;
    u32 limit = Shape::of(d).nblocks + 1;
    for (const LinkElement* l = sentinel->m_next; l && l != sentinel && limit--; l = l->m_next) {
        auto* b = reinterpret_cast<const MessageDispatcherBlockForList*>(l);
        if ((b->m_block.m_message & MessageDispatcherBlock::kFlagWaitCounter) && b->m_block.m_counter)
            counters.push_back({(u64)b->m_block.m_counter, __atomic_load_n(b->m_block.m_counter, __ATOMIC_SEQ_CST)});
    }
}

void DispatchObservation::capture_post(const SimpleMessageDispatcher* d) {
    capture(d, post);
    have_post = true;
}

namespace {

// ---- the shadow arena (one per thread, rebuilt when the dispatcher's shape changes) ----

constexpr size_t kVtableSlots = 8, kCounterSlots = 256;

struct Arena {
    Shape shape;
    u8* mem = nullptr;
    size_t od = 0, ovt = 0, ow = 0, os = 0, oc = 0, otask = 0, size = 0;
    u64 vt_real = 0;
    std::vector<std::pair<u64, u64>> counter_map;  // (real counter, arena slot)

    SimpleMessageDispatcher* d() const { return reinterpret_cast<SimpleMessageDispatcher*>(mem + od); }
    WorkerThread* worker(s32 i) const { return reinterpret_cast<WorkerThread*>(mem + ow + 8 + (size_t)i * sizeof(WorkerThread)); }

    void release() {
        if (!mem) return;
        d()->m_freeBlockEvent.Exit();
        for (s32 i = 0; i < shape.nworkers; i++) worker(i)->m_wakeup.Exit();
        hle_host_sem_destroy((u64)d()->m_cs.m_sem.m_sem);
        ::operator delete(mem, std::align_val_t(64));
        mem = nullptr;
    }
    void build(const Shape& sh) {
        release();
        shape = sh;
        auto up = [](size_t v) { return (v + 63) & ~size_t(63); };
        od = 0;
        ovt = up(kDispatcherBytes);
        ow = up(ovt + kVtableSlots * 8);
        os = up(ow + sh.wbytes);
        oc = up(os + sh.sbytes);
        otask = up(oc + kCounterSlots * 8);
        size = up(otask + sizeof(Task));
        mem = static_cast<u8*>(::operator new(size, std::align_val_t(64)));
        std::memset(mem, 0, size);
        // Events and the semaphore of its own (in place, as the guest's Create makes them).
        d()->m_freeBlockEvent.Ctor();
        d()->m_freeBlockEvent.Create(true, false);
        for (s32 i = 0; i < sh.nworkers; i++) {
            worker(i)->m_wakeup.Ctor();
            worker(i)->m_wakeup.Create(false, false);
        }
        hle_host_sem_init((u64)d()->m_cs.m_sem.m_sem, 0);
    }

    // Real -> arena for a pointer into one of the regions (or a moved counter); else unchanged.
    u64 map(u64 v) const {
        if (v >= shape.d && v < shape.d + kDispatcherBytes) return (u64)mem + od + (v - shape.d);
        if (shape.wbytes && v >= shape.w && v < shape.w + shape.wbytes) return (u64)mem + ow + (v - shape.w);
        if (shape.sbytes && v >= shape.s && v < shape.s + shape.sbytes) return (u64)mem + os + (v - shape.s);
        return v;
    }
    u64 unmap(u64 v) const {
        u64 base = (u64)mem;
        if (v >= base + od && v < base + od + kDispatcherBytes) return shape.d + (v - base - od);
        if (shape.wbytes && v >= base + ow && v < base + ow + shape.wbytes) return shape.w + (v - base - ow);
        if (shape.sbytes && v >= base + os && v < base + os + shape.sbytes) return shape.s + (v - base - os);
        if (v >= base + ovt && v < base + ovt + kVtableSlots * 8) return vt_real + (v - base - ovt);
        for (auto& [real, slot] : counter_map)
            if (v == slot) return real;
        return v;
    }
    template <typename F>
    void each_word(F f) {
        auto run = [&](size_t off, size_t n) {
            for (size_t k = 0; k + 8 <= n; k += 8) f(*reinterpret_cast<u64*>(mem + off + k));
        };
        run(od, kDispatcherBytes);
        run(ow, shape.wbytes);
        run(os, shape.sbytes);
    }
    std::vector<size_t> event_offsets() const {
        std::vector<size_t> v{od + offsetof(SimpleMessageDispatcher, m_freeBlockEvent)};
        for (s32 i = 0; i < shape.nworkers; i++) v.push_back((size_t)((u8*)&worker(i)->m_wakeup - mem));
        return v;
    }

    // The state `snap` (a capture of the real dispatcher) at the arena's addresses.
    void load(const std::vector<u8>& snap, const std::vector<std::pair<u64, s32>>& counters, u64 getMessageOrig) {
        std::vector<size_t> evs = event_offsets();
        std::vector<u8> headers(evs.size() * kEventHeader);
        for (size_t k = 0; k < evs.size(); k++) std::memcpy(&headers[k * kEventHeader], mem + evs[k], kEventHeader);
        std::memcpy(mem + od, snap.data(), kDispatcherBytes);
        if (shape.wbytes) std::memcpy(mem + ow, snap.data() + kDispatcherBytes, shape.wbytes);
        if (shape.sbytes) std::memcpy(mem + os, snap.data() + kDispatcherBytes + shape.wbytes, shape.sbytes);
        each_word([&](u64& w) { w = map(w); });
        for (size_t k = 0; k < evs.size(); k++) std::memcpy(mem + evs[k], &headers[k * kEventHeader], kEventHeader);
        SimpleMessageDispatcher* sd = d();
        sd->m_cs.m_lock = FastCriticalSection::kFree;
        sd->m_cs.m_waiters = FastCriticalSection::kWaiterBias;
        sd->m_cs.m_sem.m_pSem = (u64)sd->m_cs.m_sem.m_sem;
        // The vtable: the real one's slots, GetMessage's the guest original (the worker's replay asks it).
        vt_real = (u64)sd->vtable;
        auto* vt = reinterpret_cast<u64*>(mem + ovt);
        std::memcpy(vt, (const void*)vt_real, kVtableSlots * 8);
        if (getMessageOrig) vt[SimpleMessageDispatcher::kSlotGetMessage] = getMessageOrig;
        sd->vtable = vt;
        // The queued blocks' counters: arena slots with the values recorded under the lock.
        counter_map.clear();
        auto* slots = reinterpret_cast<s32*>(mem + oc);
        for (auto& [real, value] : counters) {
            if (counter_map.size() >= kCounterSlots / 2) break;
            u64 slot = (u64)&slots[counter_map.size() * 2];
            *reinterpret_cast<s32*>(slot) = value;
            counter_map.push_back({real, slot});
        }
        auto* blocks = reinterpret_cast<MessageDispatcherBlockForList*>(mem + os);
        for (u32 i = 0; shape.sbytes && i < shape.nblocks; i++)
            for (auto& [real, slot] : counter_map)
                if ((u64)blocks[i].m_block.m_counter == real) blocks[i].m_block.m_counter = reinterpret_cast<s32*>(slot);
    }

    // The arena's state mapped back to the real addresses, in a capture's shape.
    std::vector<u8> unload() {
        std::vector<u8> out(shape.total());
        SimpleMessageDispatcher* sd = d();
        std::memcpy(out.data(), mem + od, kDispatcherBytes);
        if (shape.wbytes) std::memcpy(out.data() + kDispatcherBytes, mem + ow, shape.wbytes);
        if (shape.sbytes) std::memcpy(out.data() + kDispatcherBytes + shape.wbytes, mem + os, shape.sbytes);
        for (size_t k = 0; k + 8 <= out.size(); k += 8) {
            u64 w;
            std::memcpy(&w, &out[k], 8);
            w = unmap(w);
            std::memcpy(&out[k], &w, 8);
        }
        (void)sd;
        return out;
    }
};

Arena& arena_for(const Shape& sh) {
    Arena& a = thread_object<Arena>();  // (core/thread_record.h)
    if (!a.mem || !a.shape.same(sh)) a.build(sh);
    return a;
}

// ---- comparing ----

enum Kind : u8 {
    kPost,           // the Post* / PostSync* forms
    kSend,           // the Send* forms (blocking)
    kAddMessage,     // AddMessage / AddMessageToFront (the caller holds m_cs)
    kDelete,         // DeleteMessage (the caller holds m_cs) / CancelMessage
    kSuspend,        // Suspend / ResumeWorkerThread
    kWorkerGet,      // _WorkerThread::GetMessage
    kMessageReady,   // _WorkerThread::MessageReady
    kWakeup,         // WakeupWorkerThread / WakeupAllWorkerThreads (no lock, no state of the dispatcher's)
};

struct Spec {
    Kind kind;
    bool task = false;  // the (Task*, barrier) forms: x1 is the task
    int serial = -1;    // the u32* serial out's argument index (x0 = 0; >= 8: the stack)
    bool returns = true;
};

// Byte ranges of a capture not compared: the lock, the events' pthread objects and padding, the
// worker array (handled per kind).
bool skipped(size_t k, const Shape& sh, Kind kind, s32 self, bool skipEventField, bool skipBarrierField) {
    if (k < kDispatcherBytes) {
        if (k >= offsetof(SimpleMessageDispatcher, m_cs) && k < offsetof(SimpleMessageDispatcher, m_queue)) return true;
        size_t e = offsetof(SimpleMessageDispatcher, m_freeBlockEvent);
        if (k >= e && k < e + sizeof(Event) && (k - e < kEventHeader || k - e >= kEventHeader + 2)) return true;
        return false;
    }
    k -= kDispatcherBytes;
    if (k < sh.wbytes) {
        if (k < 8) return false;  // the cookie
        size_t i = (k - 8) / sizeof(WorkerThread), o = (k - 8) % sizeof(WorkerThread);
        if (o >= offsetof(WorkerThread, m_wakeup) && o < offsetof(WorkerThread, m_wakeup) + sizeof(Event)) return true;
        if (kind == kWorkerGet || kind == kMessageReady) return (s32)i != self;
        return true;  // (the other kinds don't write workers; their flags are compared via the wake pass)
    }
    k -= sh.wbytes;
    if (k < (size_t)sh.nblocks * sizeof(MessageDispatcherBlockForList)) {
        size_t o = k % sizeof(MessageDispatcherBlockForList);
        size_t base = offsetof(MessageDispatcherBlockForList, m_block);
        if (skipEventField && o >= base + offsetof(MessageDispatcherBlock, m_event) && o < base + offsetof(MessageDispatcherBlock, m_event) + 8) return true;
        if (skipBarrierField && o >= base + offsetof(MessageDispatcherBlock, m_barrierManager) &&
            o < base + offsetof(MessageDispatcherBlock, m_barrierManager) + 8)
            return true;
    }
    return false;
}

std::string where(size_t k, const Shape& sh) {
    char m[96];
    if (k < kDispatcherBytes) {
        snprintf(m, sizeof m, "dispatcher+0x%zx", k);
    } else if ((k -= kDispatcherBytes) < sh.wbytes) {
        snprintf(m, sizeof m, "worker %lld +0x%zx", k < 8 ? (long long)-1 : (long long)((k - 8) / sizeof(WorkerThread)), k < 8 ? k : (k - 8) % sizeof(WorkerThread));
    } else {
        k -= sh.wbytes;
        snprintf(m, sizeof m, "block %zu +0x%zx", k / sizeof(MessageDispatcherBlockForList), k % sizeof(MessageDispatcherBlockForList));
    }
    return m;
}

// Sets the arena workers' flags to what the native's wake pass read (the decisions the guest's
// replay of that pass makes depend on them), and their events' flags to unsignaled except where
// the native read them signaled (so a Set shows as a flag turned on).
void load_wake(Arena& a, const DispatchObservation& obs, bool flags) {
    for (s32 i = 0; i < a.shape.nworkers; i++) {
        WorkerThread* w = a.worker(i);
        u8 r = obs.wake[i];
        if (flags && (r & DispatchObservation::kRead)) {  // (workers the pass didn't read keep their state under the lock)
            w->m_waiting = (r & DispatchObservation::kWaiting) ? 1 : 0;
            w->m_busy = (r & DispatchObservation::kBusy) ? 1 : 0;
        }
        w->m_wakeup.m_signaled = (r & DispatchObservation::kSignaled) ? 1 : 0;
    }
}
std::string compare_wake(Arena& a, const DispatchObservation& obs) {
    for (s32 i = 0; i < a.shape.nworkers; i++) {
        bool native_set = obs.wake[i] & DispatchObservation::kSet;
        bool was = obs.wake[i] & DispatchObservation::kSignaled;
        bool guest_set = !was && a.worker(i)->m_wakeup.m_signaled;
        if (native_set != guest_set) {
            char m[96];
            snprintf(m, sizeof m, "wake: worker %d: native %s, guest %s", i, native_set ? "Set" : "-", guest_set ? "Set" : "-");
            return m;
        }
    }
    return {};
}

u64* arg_slot(u64* x, u64 sp, int idx) { return idx < 8 ? &x[idx] : reinterpret_cast<u64*>(sp + 8 * (idx - 8)); }

void run_checked(Cpu& c, CheckedFn& f, HostFn native, const Spec& spec) {
    live::CheckScope scope;
    u64 x[8];
    for (int i = 0; i < 8; i++) x[i] = c.x(i);
    V128 v[8];
    for (int i = 0; i < 8; i++) v[i] = c.v(i);
    const u64 sp = c.sp(), x8 = c.x(8);
    // The dispatcher (and the worker, for its methods).
    const bool on_worker = spec.kind == kWorkerGet || spec.kind == kMessageReady;
    auto* worker = on_worker ? reinterpret_cast<WorkerThread*>(x[0]) : nullptr;
    auto* d = on_worker ? worker->m_owner : reinterpret_cast<SimpleMessageDispatcher*>(x[0]);
    if (!d) {
        native(c);
        return check_result(f, live::Outcome::Skipped, "no dispatcher");
    }
    if (on_worker && !worker->m_waiting) {  // (the hand-off branch: never in the game)
        native(c);
        return check_result(f, live::Outcome::Skipped, "worker not waiting");
    }
    DispatchObservation obs;
    if (spec.kind == kWakeup) obs.capture_pre(d);
    t_dobs = &obs;
    native(c);
    t_dobs = nullptr;
    const u64 native_x0 = c.x(0);
    if (spec.kind == kWakeup) obs.post = obs.pre, obs.have_post = true;
    if (!obs.have_pre || !obs.have_post) return check_result(f, live::Outcome::Skipped, "no observation");
    Shape sh = Shape::of(d);
    if (sh.total() != obs.pre.size() || obs.pre.size() != obs.post.size()) return check_result(f, live::Outcome::Skipped, "dispatcher reshaped");
    u32 native_serial = 0;
    u64* serial_slot = nullptr;
    u64 serial_ptr = 0;
    if (spec.serial >= 0) {
        serial_slot = arg_slot(x, sp, spec.serial);
        serial_ptr = *serial_slot;
        if (serial_ptr) native_serial = *reinterpret_cast<u32*>(serial_ptr);
    }
    // The replay.
    Arena& a = arena_for(sh);
    a.load(obs.pre, obs.counters, g_get_message_orig);
    load_wake(a, obs, spec.kind != kWorkerGet);
    // The other workers' m_busy as the native's GetMessage read it.
    for (s32 i = 0; i < a.shape.nworkers && i < kMaxWorkers; i++)
        if (obs.busy[i] & DispatchObservation::kRead) a.worker(i)->m_busy = (obs.busy[i] & DispatchObservation::kBusy) ? 1 : 0;
    u64 gx[8];
    std::memcpy(gx, x, sizeof gx);
    s32 self = -1;
    if (on_worker) {
        self = (s32)(((u64)worker - (sh.w + 8)) / sizeof(WorkerThread));
        gx[0] = a.map(x[0]);
        if (spec.kind == kWorkerGet) gx[1] = a.map(x[1]);
    } else {
        gx[0] = a.map(x[0]);
    }
    alignas(16) u8 task_copy[sizeof(Task)];
    if (spec.task && x[1]) {
        std::memcpy(task_copy, (const void*)x[1], sizeof(Task));
        reinterpret_cast<Task*>(task_copy)->m_owner = nullptr;
        gx[1] = (u64)task_copy;
    }
    // A worker's out block outside the regions: the guest writes the caller's buffer; the native's bytes are put back.
    u8 native_out[sizeof(MessageDispatcherBlock)];
    bool out_real = spec.kind == kWorkerGet && x[1] && gx[1] == x[1];
    if (out_real) std::memcpy(native_out, (const void*)x[1], sizeof native_out);
    sync::t_replay_no_wait = spec.kind == kSend;
    GuestResult gr = live::guest_call_at_sp(f.orig, gx, v, x8, sp);
    sync::t_replay_no_wait = false;
    std::string why;
    // Results.
    u64 mask = spec.kind == kAddMessage ? ~0ull : 0xff;
    u64 gx0 = spec.kind == kAddMessage ? a.unmap(gr.x0) : gr.x0;
    if (spec.returns && (native_x0 & mask) != (gx0 & mask)) {
        char m[96];
        snprintf(m, sizeof m, "x0: native %#" PRIx64 " guest %#" PRIx64, native_x0 & mask, gx0 & mask);
        why = m;
    }
    if (why.empty() && serial_ptr && (native_x0 & 0xff)) {
        u32 guest_serial = *reinterpret_cast<u32*>(serial_ptr);
        if (guest_serial != native_serial) why = "serial out: native " + std::to_string(native_serial) + " guest " + std::to_string(guest_serial);
        *reinterpret_cast<u32*>(serial_ptr) = native_serial;
    }
    if (out_real) {
        if (why.empty() && (native_x0 & 1) && std::memcmp(native_out, (const void*)x[1], sizeof native_out)) why = "out block";
        std::memcpy((void*)x[1], native_out, sizeof native_out);
    }
    // The state.
    if (why.empty()) {
        std::vector<u8> g = a.unload();
        const bool skipEvent = spec.kind == kSend, skipBarrier = spec.task;
        // (the shadow's own lock must be free again)
        if (a.d()->m_cs.m_lock != FastCriticalSection::kFree) why = "guest left the shadow's lock held";
        for (size_t k = 0; why.empty() && k < g.size(); k++) {
            if (g[k] == obs.post[k] || skipped(k, sh, spec.kind, self, skipEvent, skipBarrier)) continue;
            char m[160];
            snprintf(m, sizeof m, "%s: native %02x guest %02x (pre %02x)", where(k, sh).c_str(), obs.post[k], g[k], obs.pre[k]);
            why = m;
        }
    }
    if (why.empty()) why = compare_wake(a, obs);
    if (why.empty()) return check_result(f, live::Outcome::Ok);
    // A counter another thread changed since the native read it, or a worker's flags MessageReady
    // cleared meanwhile, makes the replay see a different state: a race, not a mismatch.
    for (auto& [real, value] : obs.counters)
        if (__atomic_load_n(reinterpret_cast<s32*>(real), __ATOMIC_SEQ_CST) != value) return check_result(f, live::Outcome::Race);
    check_result(f, live::Outcome::Mismatch, why);
}

// ---- the hooks ----

template <auto M>
struct Hook {
    static CheckedFn* fn;
    static Spec spec;
    static void run(Cpu& c) {
        if (!live::check_due(*fn)) return wrap_method<M>()(c);
        run_checked(c, *fn, wrap_method<M>(), spec);
    }
};
template <auto M>
CheckedFn* Hook<M>::fn = nullptr;
template <auto M>
Spec Hook<M>::spec{};

template <auto M>
bool bind(const char* sym, const char* note, Spec spec) {
    Hook<M>::fn = new CheckedFn(sym);
    Hook<M>::spec = spec;
    register_native_function({sym, &Hook<M>::run, note, nullptr, &Hook<M>::fn->orig});
    return true;
}

using D = SimpleMessageDispatcher;
using W = WorkerThread;

// Overloads by their signatures.
using PostPlain = bool (D::*)(u16, INotify*, void*, void*, u32*, s8);
using PostKeys = bool (D::*)(u16, INotify*, void*, void*, u64, u64, u32*, s8);
using PostTask = bool (D::*)(Task*, s32, u16, INotify*, void*, void*, u32*, s8);
using PostTaskKeys = bool (D::*)(Task*, s32, u16, INotify*, void*, void*, u64, u64, u32*, s8);
using PostSync = bool (D::*)(u16, s32*, INotify*, void*, void*, u32*, s8);
using PostSyncKeys = bool (D::*)(u16, s32*, INotify*, void*, void*, u64, u64, u32*, s8);
using SendPlain = bool (D::*)(u16, INotify*, void*, void*, s8);
using SendKeys = bool (D::*)(u16, INotify*, void*, void*, u64, u64, s8);
using SendHigh = bool (D::*)(u16, INotify*, void*, void*);
using SendHighKeys = bool (D::*)(u16, INotify*, void*, void*, u64, u64);
using SendTask = bool (D::*)(Task*, s32, u16, INotify*, void*, void*, s8);
using SendTaskKeys = bool (D::*)(Task*, s32, u16, INotify*, void*, void*, u64, u64, s8);
using SendHighTask = bool (D::*)(Task*, s32, u16, INotify*, void*, void*);
using SendHighTaskKeys = bool (D::*)(Task*, s32, u16, INotify*, void*, void*, u64, u64);

[[maybe_unused]] const bool g_bound[] = {
    bind<static_cast<PostPlain>(&D::PostMessage)>("_ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_Pja",
                                                  "kernel: SimpleMessageDispatcher::PostMessage", {kPost, false, 5}),
    bind<static_cast<PostKeys>(&D::PostMessage)>("_ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_mmPja",
                                                 "kernel: SimpleMessageDispatcher::PostMessage (keys)", {kPost, false, 7}),
    bind<static_cast<PostTask>(&D::PostMessage)>("_ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_Pja",
                                                 "kernel: SimpleMessageDispatcher::PostMessage (task barrier)", {kPost, true, 7}),
    bind<static_cast<PostTaskKeys>(&D::PostMessage)>("_ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_mmPja",
                                                     "kernel: SimpleMessageDispatcher::PostMessage (task barrier, keys)", {kPost, true, 9}),
    bind<static_cast<PostSync>(&D::PostSyncMessageSingle)>("_ZN4Aska23SimpleMessageDispatcher21PostSyncMessageSingleEtPiPNS_7INotifyEPvS4_Pja",
                                                           "kernel: SimpleMessageDispatcher::PostSyncMessageSingle", {kPost, false, 6}),
    bind<static_cast<PostSyncKeys>(&D::PostSyncMessageSingle)>("_ZN4Aska23SimpleMessageDispatcher21PostSyncMessageSingleEtPiPNS_7INotifyEPvS4_mmPja",
                                                               "kernel: SimpleMessageDispatcher::PostSyncMessageSingle (keys)", {kPost, false, 8}),
    bind<static_cast<PostSync>(&D::PostSyncMessageEnd)>("_ZN4Aska23SimpleMessageDispatcher18PostSyncMessageEndEtPiPNS_7INotifyEPvS4_Pja",
                                                        "kernel: SimpleMessageDispatcher::PostSyncMessageEnd", {kPost, false, 6}),
    bind<static_cast<PostSyncKeys>(&D::PostSyncMessageEnd)>("_ZN4Aska23SimpleMessageDispatcher18PostSyncMessageEndEtPiPNS_7INotifyEPvS4_mmPja",
                                                            "kernel: SimpleMessageDispatcher::PostSyncMessageEnd (keys)", {kPost, false, 8}),
    bind<static_cast<SendPlain>(&D::SendMessage)>("_ZN4Aska23SimpleMessageDispatcher11SendMessageEtPNS_7INotifyEPvS3_a",
                                                  "kernel: SimpleMessageDispatcher::SendMessage", {kSend}),
    bind<static_cast<SendKeys>(&D::SendMessage)>("_ZN4Aska23SimpleMessageDispatcher11SendMessageEtPNS_7INotifyEPvS3_mma",
                                                 "kernel: SimpleMessageDispatcher::SendMessage (keys)", {kSend}),
    bind<static_cast<SendHigh>(&D::SendMessageHigh)>("_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEtPNS_7INotifyEPvS3_",
                                                     "kernel: SimpleMessageDispatcher::SendMessageHigh", {kSend}),
    bind<static_cast<SendHighKeys>(&D::SendMessageHigh)>("_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEtPNS_7INotifyEPvS3_mm",
                                                         "kernel: SimpleMessageDispatcher::SendMessageHigh (keys)", {kSend}),
    bind<static_cast<SendTask>(&D::SendMessage)>("_ZN4Aska23SimpleMessageDispatcher11SendMessageEPNS_4TaskEitPNS_7INotifyEPvS5_a",
                                                 "kernel: SimpleMessageDispatcher::SendMessage (task barrier)", {kSend, true}),
    bind<static_cast<SendTaskKeys>(&D::SendMessage)>("_ZN4Aska23SimpleMessageDispatcher11SendMessageEPNS_4TaskEitPNS_7INotifyEPvS5_mma",
                                                     "kernel: SimpleMessageDispatcher::SendMessage (task barrier, keys)", {kSend, true}),
    bind<static_cast<SendHighTask>(&D::SendMessageHigh)>("_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEPNS_4TaskEitPNS_7INotifyEPvS5_",
                                                         "kernel: SimpleMessageDispatcher::SendMessageHigh (task barrier)", {kSend, true}),
    bind<static_cast<SendHighTaskKeys>(&D::SendMessageHigh)>("_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEPNS_4TaskEitPNS_7INotifyEPvS5_mm",
                                                             "kernel: SimpleMessageDispatcher::SendMessageHigh (task barrier, keys)", {kSend, true}),
    bind<&D::AddMessage>("_ZN4Aska23SimpleMessageDispatcher10AddMessageEa", "kernel: SimpleMessageDispatcher::AddMessage", {kAddMessage}),
    bind<&D::AddMessageToFront>("_ZN4Aska23SimpleMessageDispatcher17AddMessageToFrontEv", "kernel: SimpleMessageDispatcher::AddMessageToFront",
                                {kAddMessage}),
    bind<&D::DeleteMessage>("_ZN4Aska23SimpleMessageDispatcher13DeleteMessageEi", "kernel: SimpleMessageDispatcher::DeleteMessage (never frees)",
                            {kDelete}),
    bind<&D::CancelMessage>("_ZN4Aska23SimpleMessageDispatcher13CancelMessageEj", "kernel: SimpleMessageDispatcher::CancelMessage", {kDelete}),
    bind<&D::SuspendWorkerThread>("_ZN4Aska23SimpleMessageDispatcher19SuspendWorkerThreadEv", "kernel: SimpleMessageDispatcher::SuspendWorkerThread",
                                  {kSuspend, false, -1, false}),
    bind<&D::ResumeWorkerThread>("_ZN4Aska23SimpleMessageDispatcher18ResumeWorkerThreadEv", "kernel: SimpleMessageDispatcher::ResumeWorkerThread",
                                 {kSuspend, false, -1, false}),
    bind<&D::WakeupWorkerThread>("_ZN4Aska23SimpleMessageDispatcher18WakeupWorkerThreadEv", "kernel: SimpleMessageDispatcher::WakeupWorkerThread",
                                 {kWakeup}),
    bind<&D::WakeupAllWorkerThreads>("_ZN4Aska23SimpleMessageDispatcher22WakeupAllWorkerThreadsEv",
                                     "kernel: SimpleMessageDispatcher::WakeupAllWorkerThreads", {kWakeup, false, -1, false}),
    bind<&W::GetMessage>("_ZN4Aska23SimpleMessageDispatcher13_WorkerThread10GetMessageEPNS_22MessageDispatcherBlockE",
                         "kernel: SimpleMessageDispatcher::_WorkerThread::GetMessage (+ GetMessage(block, int))", {kWorkerGet}),
    bind<&W::MessageReady>("_ZN4Aska23SimpleMessageDispatcher13_WorkerThread12MessageReadyEv", "kernel: SimpleMessageDispatcher::_WorkerThread::MessageReady",
                           {kMessageReady, false, -1, false}),
};

}  // namespace

// GetMessage(block, int): reached through the vtable from the worker's GetMessage (the native calls
// the member directly when the slot is this function); checked inside the worker's check, whose
// replay asks the guest original through the shadow's vtable.
NATIVE_FUNCTION_ORIG("_ZN4Aska23SimpleMessageDispatcher10GetMessageEPNS_22MessageDispatcherBlockEi",
                     ::soa::wrap_method<&SimpleMessageDispatcher::GetMessage>(), "kernel: SimpleMessageDispatcher::GetMessage(block, int)",
                     &g_get_message_orig);
NATIVE_METHOD("_ZNK4Aska23SimpleMessageDispatcher23IsWorkerThreadSuspendedEv", &SimpleMessageDispatcher::IsWorkerThreadSuspended,
              "kernel: SimpleMessageDispatcher::IsWorkerThreadSuspended");

}  // namespace soa::native::kernel
