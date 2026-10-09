// Aska::SimpleMessageDispatcher and its _WorkerThread (port/decomp/kernel/message_dispatcher.c).
//
// The guest's queue on the guest's fields: every operation runs under the dispatcher's own
// FastCriticalSection (m_cs), entered and left through sync's members, so these natives, the forms
// still left to the guest (PostMultiMessages, PostSyncMessages, Setup, Clear, ...) and the guest's
// _WorkerThread::Handler exclude each other on the same lock word (sync/README.md "Design"). What
// changes is the cost: in the guest every one of these spun on that word through the JIT's
// exclusive monitor (0x200 LL/SC probes before parking) while the holder ran its critical section
// as JIT code; here the critical sections are a few host instructions and the spin is host atomics.
//
// Upward calls go through the guest vtables: the worker asks its owner's slot 2 (GetMessage) and
// GetMessage asks slot 3 (CheckToDispatch) for each candidate; both are called as members when
// the slot holds the guest function these natives replace, else through guest_call.
// The observation hooks (t_dobs) only run inside a live check (kernel_check.h).
#include <cstring>

#include "soaruntime/core/cpu.h"
#include "native/common/guest_std.h"
#include "native/common/native_method.h"
#include "native/kernel/kernel_check.h"
#include "native/kernel/kernel_layout.h"

namespace soa::native::kernel {

namespace {

inline void fence() { __atomic_thread_fence(__ATOMIC_SEQ_CST); }

const u64* vtable_of(const void* vt) { return static_cast<const u64*>(vt); }

u64 fn_get_message() {
    static const u64 a = guest::sym("_ZN4Aska23SimpleMessageDispatcher10GetMessageEPNS_22MessageDispatcherBlockEi");
    return a;
}
u64 fn_check_to_dispatch() {
    static const u64 a = guest::sym("_ZN4Aska23SimpleMessageDispatcher15CheckToDispatchEPNS_29MessageDispatcherBlockForListE");
    return a;
}

// Aska::Global::m_pEventPool's Scoop / Sink: the Send* forms' fallback when their stack event can't
// be created (sync's Event::Create always succeeds, so never in practice).
u64 event_pool() {
    static const u64 a = guest::sym("_ZN4Aska6Global12m_pEventPoolE");
    return *reinterpret_cast<const u64*>(a);
}
Event* event_pool_scoop() {
    static const u64 fn = guest::sym("_ZN4Aska9EventPool5ScoopEv");
    return reinterpret_cast<Event*>(guest_call(fn, {event_pool()}));
}
void event_pool_sink(Event* e) {
    static const u64 fn = guest::sym("_ZN4Aska9EventPool4SinkEPNS_5EventE");
    guest_call(fn, {event_pool(), (u64)e});
}

inline void observe_pre(const SimpleMessageDispatcher* d) {
    if (__builtin_expect(t_dobs != nullptr, 0)) t_dobs->capture_pre(d);
}
inline void observe_post(const SimpleMessageDispatcher* d) {
    if (__builtin_expect(t_dobs != nullptr, 0)) t_dobs->capture_post(d);
}

}  // namespace

// What one Post* / Send* form writes into its block besides the serial (the rest stays as the
// memset left it).
struct PostFields {
    u16 message = 0;        // the id & 0x3fff, with the form's flag (0x4000 sync end, 0x8000 send)
    INotify* notify = nullptr;
    void* a0 = nullptr;
    void* a1 = nullptr;
    u64 k0 = 0, k1 = 0;
    s32* counter = nullptr;  // the PostSync* forms
    bool hasTask = false;    // the (Task*, barrier) forms
    Task* task = nullptr;
    s32 barrier = 0;
};

// ---- the queue (callers hold m_cs) ----

MessageDispatcherBlockForList* SimpleMessageDispatcher::LinkFreeBlock(s8 priority, bool atFront) {
    // Pop the free queue: the slot after m_read; empty when that is m_write.
    u32 next = m_freeBlocks.m_read + 1 < m_freeBlocks.m_capacity ? m_freeBlocks.m_read + 1 : 0;
    if (next == m_freeBlocks.m_write) {
        m_full = 1;
        m_freeBlockEvent.Reset();
        return nullptr;
    }
    m_freeBlocks.m_read = next;
    MessageDispatcherBlockForList* b = m_freeBlocks.m_items[next];
    LinkElement* sentinel = &m_queue.m_sentinel.link;
    LinkElement* after = sentinel;  // insert after it: the front unless a block of >= priority is found
    if (!atFront) {
        // Back from the last block: after the last one whose priority is >= the new one (FIFO within one).
        for (LinkElement* l = sentinel->m_prev; l != sentinel; l = l->m_prev) {
            if (priority <= reinterpret_cast<MessageDispatcherBlockForList*>(l)->m_priority) {
                after = l;
                break;
            }
        }
    }
    LinkElement* before = after->m_next;
    b->link.m_prev = after;
    b->link.m_next = before;
    before->m_prev = &b->link;
    after->m_next = &b->link;
    m_queue.m_count++;
    b->m_priority = atFront ? (s8)0x7f : priority;
    std::memset(&b->m_block, 0, sizeof b->m_block);
    return b;
}

MessageDispatcherBlock* SimpleMessageDispatcher::AddMessage(s8 priority) {
    observe_pre(this);
    MessageDispatcherBlockForList* b = LinkFreeBlock(priority, false);
    observe_post(this);
    return b ? &b->m_block : nullptr;
}

MessageDispatcherBlock* SimpleMessageDispatcher::AddMessageToFront() {
    observe_pre(this);
    MessageDispatcherBlockForList* b = LinkFreeBlock(0x7f, true);
    observe_post(this);
    return b ? &b->m_block : nullptr;
}

// Unlinks the block with this serial (the newest first; < 0: every block). Quirk kept: the block
// doesn't go back to the free queue (it leaks until Setup runs again), and "every block" empties
// the list without touching the count. The serial is compared as a u32 with the u16 field.
bool SimpleMessageDispatcher::DeleteMessage(s32 serial) {
    observe_pre(this);
    LinkElement* sentinel = &m_queue.m_sentinel.link;
    bool found = true;
    if (serial < 0) {
        sentinel->m_prev = sentinel;
        sentinel->m_next = sentinel;
    } else {
        LinkElement* l = sentinel->m_prev;
        while (l != sentinel && (u32)reinterpret_cast<MessageDispatcherBlockForList*>(l)->m_block.m_serial != (u32)serial) l = l->m_prev;
        if (l == sentinel) {
            found = false;
        } else {
            LinkElement *prev = l->m_prev, *next = l->m_next;
            if (prev) prev->m_next = next;
            if (next) next->m_prev = prev;
            if (m_queue.m_count > 0) m_queue.m_count--;
            l->m_prev = nullptr;
            l->m_next = nullptr;
        }
    }
    observe_post(this);
    return found;
}

bool SimpleMessageDispatcher::CancelMessage(u32 serial) {
    m_cs.Enter();
    fence();
    bool r = DeleteMessage((s32)serial);
    fence();
    m_cs.Leave();
    return r;
}

// ---- waking the workers (no lock of the dispatcher's own: the guest reads the flags as they are) ----

s32 SimpleMessageDispatcher::WakeIdleWorker() {
    for (s32 i = 0; i < m_workerCount; i++) {
        WorkerThread& w = m_workers[i];
        u8 flags = (w.m_waiting ? DispatchObservation::kWaiting : 0) | (w.m_busy ? DispatchObservation::kBusy : 0);
        if (w.m_waiting && !w.m_busy) {
            if (!w.m_wakeup.IsSignal()) {
                if (t_dobs) t_dobs->note_worker(i, flags), t_dobs->note_set(i);
                w.m_wakeup.Set();
                return i;
            }
            flags |= DispatchObservation::kSignaled;
        }
        if (t_dobs) t_dobs->note_worker(i, flags);
    }
    return -1;
}

void SimpleMessageDispatcher::WakeWaitingWorkers() {
    for (s32 i = 0; i < m_workerCount; i++) {
        WorkerThread& w = m_workers[i];
        if (t_dobs) t_dobs->note_worker(i, w.m_waiting ? DispatchObservation::kWaiting : 0);
        if (w.m_waiting) {
            if (t_dobs) t_dobs->note_set(i);
            w.m_wakeup.Set();
        }
    }
}

bool SimpleMessageDispatcher::WakeupWorkerThread() { return WakeIdleWorker() >= 0; }

void SimpleMessageDispatcher::WakeupAllWorkerThreads() { WakeWaitingWorkers(); }

void SimpleMessageDispatcher::SuspendWorkerThread() {
    m_cs.Enter();
    fence();
    observe_pre(this);
    m_suspended = 1;
    observe_post(this);
    fence();
    m_cs.Leave();
}

void SimpleMessageDispatcher::ResumeWorkerThread() {
    m_cs.Enter();
    fence();
    observe_pre(this);
    m_suspended = 0;
    if (m_queue.m_sentinel.link.m_next != &m_queue.m_sentinel.link) WakeWaitingWorkers();
    observe_post(this);
    fence();
    m_cs.Leave();
}

bool SimpleMessageDispatcher::IsWorkerThreadSuspended() const { return m_suspended; }

bool SimpleMessageDispatcher::CheckToDispatch(MessageDispatcherBlockForList*) { return true; }

// ---- posting ----

namespace {
void fill_block(MessageDispatcherBlock& m, const PostFields& f, u16 serial, Event* event, TaskManager* owner) {
    m.m_serial = serial;
    m.m_message = f.message;
    m.m_notify = f.notify;
    m.m_event = event;
    m.m_counter = f.counter;
    m.m_arg0 = f.a0;
    m.m_arg1 = f.a1;
    m.m_key0 = f.k0;
    m.m_key1 = f.k1;
    if (f.hasTask) {
        m.m_barrierManager = owner;
        m.m_barrier = (u32)f.barrier;
    }
}
TaskManager* owner_of(const PostFields& f) { return f.hasTask && f.task ? f.task->m_owner : nullptr; }
}  // namespace

// The Post* forms: a block at its priority, filled; the (Task*, barrier) forms register the message
// with the task's manager's barrier while still holding the lock; then the serial out, the lock
// released, and one idle worker woken.
bool SimpleMessageDispatcher::Post(const PostFields& f, u32* serialOut, s8 priority) {
    m_cs.Enter();
    fence();
    observe_pre(this);
    MessageDispatcherBlockForList* b = LinkFreeBlock(priority, false);
    if (!b) {
        observe_post(this);
        fence();
        m_cs.Leave();
        return false;
    }
    TaskManager* owner = owner_of(f);
    u16 serial = m_nextSerial++;
    fill_block(b->m_block, f, serial, nullptr, owner);
    if (f.hasTask && (u32)f.barrier < 0x20 && owner) {
        owner->AddThreadBarrier(f.barrier);
        owner->IncrementThreadBarrierCount(f.barrier);
    }
    if (serialOut) *serialOut = serial;
    observe_post(this);
    fence();
    m_cs.Leave();
    WakeIdleWorker();
    return true;
}

// The Send* forms: as Post, with kFlagSignalEvent and an event of the caller's (on its stack; the
// event pool's when that can't be created), which the worker sets after the handler; the caller
// waits on it outside the lock. SendMessageHigh puts the message first with priority 0x7f. Quirk
// kept: when neither event is had, the block stays queued, zeroed, and the form returns false.
bool SimpleMessageDispatcher::Send(const PostFields& f, s8 priority, bool high) {
    m_cs.Enter();
    fence();
    observe_pre(this);
    MessageDispatcherBlockForList* b = LinkFreeBlock(priority, high);
    if (!b) {
        observe_post(this);
        fence();
        m_cs.Leave();
        return false;
    }
    TaskManager* owner = owner_of(f);
    alignas(16) Event stackEvent;
    stackEvent.Ctor();
    Event* event = &stackEvent;
    bool pooled = false;
    if (!stackEvent.Create(true, false)) {
        event = event_pool_scoop();
        pooled = true;
        if (!event) {
            stackEvent.Exit();
            observe_post(this);
            fence();
            m_cs.Leave();
            return false;
        }
    }
    u16 serial = m_nextSerial++;
    PostFields g = f;
    g.message = (u16)(f.message | MessageDispatcherBlock::kFlagSignalEvent);
    fill_block(b->m_block, g, serial, event, owner);
    if (f.hasTask && (u32)f.barrier < 0x20 && owner) {
        owner->AddThreadBarrier(f.barrier);
        owner->IncrementThreadBarrierCount(f.barrier);
    }
    observe_post(this);
    fence();
    m_cs.Leave();
    WakeIdleWorker();
    event->Wait(0);
    if (pooled) event_pool_sink(event);
    stackEvent.Exit();
    return true;
}

bool SimpleMessageDispatcher::PostMessage(u16 msg, INotify* notify, void* a0, void* a1, u32* serialOut, s8 priority) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1;
    return Post(f, serialOut, priority);
}
bool SimpleMessageDispatcher::PostMessage(u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut, s8 priority) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1, f.k0 = k0, f.k1 = k1;
    return Post(f, serialOut, priority);
}
bool SimpleMessageDispatcher::PostMessage(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u32* serialOut, s8 priority) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1;
    f.hasTask = true, f.task = task, f.barrier = barrier;
    return Post(f, serialOut, priority);
}
bool SimpleMessageDispatcher::PostMessage(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut,
                                          s8 priority) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1, f.k0 = k0, f.k1 = k1;
    f.hasTask = true, f.task = task, f.barrier = barrier;
    return Post(f, serialOut, priority);
}
// PostSyncMessageSingle: the job counts against *counter (the caller incremented it); the worker
// decrements it after the handler. PostSyncMessageEnd: held back (kFlagWaitCounter) until *counter is 0.
bool SimpleMessageDispatcher::PostSyncMessageSingle(u16 msg, s32* counter, INotify* notify, void* a0, void* a1, u32* serialOut, s8 priority) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.counter = counter, f.notify = notify, f.a0 = a0, f.a1 = a1;
    return Post(f, serialOut, priority);
}
bool SimpleMessageDispatcher::PostSyncMessageSingle(u16 msg, s32* counter, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut,
                                                    s8 priority) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.counter = counter, f.notify = notify, f.a0 = a0, f.a1 = a1, f.k0 = k0, f.k1 = k1;
    return Post(f, serialOut, priority);
}
bool SimpleMessageDispatcher::PostSyncMessageEnd(u16 msg, s32* counter, INotify* notify, void* a0, void* a1, u32* serialOut, s8 priority) {
    PostFields f;
    f.message = (u16)((msg & MessageDispatcherBlock::kMessageMask) | MessageDispatcherBlock::kFlagWaitCounter);
    f.counter = counter, f.notify = notify, f.a0 = a0, f.a1 = a1;
    return Post(f, serialOut, priority);
}
bool SimpleMessageDispatcher::PostSyncMessageEnd(u16 msg, s32* counter, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut,
                                                 s8 priority) {
    PostFields f;
    f.message = (u16)((msg & MessageDispatcherBlock::kMessageMask) | MessageDispatcherBlock::kFlagWaitCounter);
    f.counter = counter, f.notify = notify, f.a0 = a0, f.a1 = a1, f.k0 = k0, f.k1 = k1;
    return Post(f, serialOut, priority);
}

bool SimpleMessageDispatcher::SendMessage(u16 msg, INotify* notify, void* a0, void* a1, s8 priority) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1;
    return Send(f, priority, false);
}
bool SimpleMessageDispatcher::SendMessage(u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, s8 priority) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1, f.k0 = k0, f.k1 = k1;
    return Send(f, priority, false);
}
bool SimpleMessageDispatcher::SendMessageHigh(u16 msg, INotify* notify, void* a0, void* a1) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1;
    return Send(f, 0x7f, true);
}
bool SimpleMessageDispatcher::SendMessageHigh(u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1, f.k0 = k0, f.k1 = k1;
    return Send(f, 0x7f, true);
}
bool SimpleMessageDispatcher::SendMessage(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, s8 priority) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1;
    f.hasTask = true, f.task = task, f.barrier = barrier;
    return Send(f, priority, false);
}
bool SimpleMessageDispatcher::SendMessage(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, s8 priority) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1, f.k0 = k0, f.k1 = k1;
    f.hasTask = true, f.task = task, f.barrier = barrier;
    return Send(f, priority, false);
}
bool SimpleMessageDispatcher::SendMessageHigh(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1;
    f.hasTask = true, f.task = task, f.barrier = barrier;
    return Send(f, 0x7f, true);
}
bool SimpleMessageDispatcher::SendMessageHigh(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1) {
    PostFields f;
    f.message = msg & MessageDispatcherBlock::kMessageMask, f.notify = notify, f.a0 = a0, f.a1 = a1, f.k0 = k0, f.k1 = k1;
    f.hasTask = true, f.task = task, f.barrier = barrier;
    return Send(f, 0x7f, true);
}

// ---- delivering ----

// The first deliverable message, copied to `out` (vtable slot 2; the caller holds m_cs). Nothing
// while suspended. While other workers are busy, a message sharing a non-zero key with one of their
// current messages is skipped, and an exclusive message (a key 0xffffffff) stops the search, as
// does any other worker on an exclusive one; a kFlagWaitCounter message waits for its counter.
// The block goes back to the free queue (unless that is full) and a full queue's waiters are told.
bool SimpleMessageDispatcher::GetMessage(MessageDispatcherBlock* out, s32 workerIndex) {
    LinkElement* sentinel = &m_queue.m_sentinel.link;
    LinkElement* l = sentinel->m_next;
    if (l == sentinel) return false;
    if (m_suspended) return false;
    const u64* vt = vtable_of(vtable);
    auto check_to_dispatch = [&](MessageDispatcherBlockForList* b) {
        u64 fn = vt[kSlotCheckToDispatch];
        if (fn == fn_check_to_dispatch()) return true;
        return (guest_call(fn, {(u64)this, (u64)b}) & 1) != 0;
    };
    auto counter_ready = [](const MessageDispatcherBlock& m) { return m.m_counter == nullptr || *m.m_counter == 0; };
    const u32 self = (u32)workerIndex;
    s32 n = m_workerCount;
    u32 busy = 0;
    for (s32 i = 0; i < n; i++) {
        if ((u32)i == self) continue;
        u8 b = m_workers[i].m_busy;
        if (t_dobs && i < kMaxWorkers) t_dobs->busy[i] = (u8)(DispatchObservation::kRead | (b ? DispatchObservation::kBusy : 0));
        if (b) busy |= 1u << (i & 31);
    }
    MessageDispatcherBlockForList* b = nullptr;
    if (n > 0 && busy) {
        for (; l != sentinel; l = l->m_next) {
            auto* c = reinterpret_cast<MessageDispatcherBlockForList*>(l);
            const u64 k0 = c->m_block.m_key0, k1 = c->m_block.m_key1;
            if (k0 == 0xffffffff || k1 == 0xffffffff) return false;
            if (!(c->m_block.m_message & MessageDispatcherBlock::kFlagWaitCounter)) {
                s32 j = 0;
                for (; j < n; j++) {
                    if ((u32)j == self || !(busy & (1u << (j & 31)))) continue;
                    const MessageDispatcherBlock& cur = m_workers[j].m_current;
                    if ((k0 != 0 && (cur.m_key0 == k0 || cur.m_key1 == k0)) || (k1 != 0 && (cur.m_key0 == k1 || cur.m_key1 == k1)) ||
                        cur.m_key0 == 0xffffffff || cur.m_key1 == 0xffffffff)
                        break;
                }
                if (j == n && check_to_dispatch(c)) {
                    b = c;
                    break;
                }
            } else if (counter_ready(c->m_block)) {
                b = c;
                break;
            }
        }
    } else {
        for (; l != sentinel; l = l->m_next) {
            auto* c = reinterpret_cast<MessageDispatcherBlockForList*>(l);
            if (!(c->m_block.m_message & MessageDispatcherBlock::kFlagWaitCounter)) {
                if (check_to_dispatch(c)) {
                    b = c;
                    break;
                }
            } else if (counter_ready(c->m_block)) {
                b = c;
                break;
            }
        }
    }
    if (!b) return false;
    if (b->m_block.m_message & MessageDispatcherBlock::kFlagWaitCounter) b->m_block.m_counter = nullptr;
    std::memcpy(out, &b->m_block, sizeof *out);
    LinkElement *prev = b->link.m_prev, *next = b->link.m_next;
    if (prev) prev->m_next = next;
    if (next) next->m_prev = prev;
    if (m_queue.m_count > 0) m_queue.m_count--;
    b->link.m_prev = nullptr;
    b->link.m_next = nullptr;
    if (m_freeBlocks.m_read != m_freeBlocks.m_write) {
        m_freeBlocks.m_items[m_freeBlocks.m_write] = b;
        m_freeBlocks.m_write = m_freeBlocks.m_write + 1 < m_freeBlocks.m_capacity ? m_freeBlocks.m_write + 1 : 0;
    }
    if (m_full) {
        m_freeBlockEvent.Set();
        m_full = 0;
    }
    return true;
}

// The worker's next message (Handler's loop): asks its owner (vtable slot 2) under the owner's
// lock; a message makes the worker busy and remembers its kFlagSignalEvent (cleared from the
// message id kept in m_current). A worker that isn't waiting first hands the wake-up to an idle one.
bool WorkerThread::GetMessage(MessageDispatcherBlock* out) {
    SimpleMessageDispatcher* d = m_owner;
    if (!m_waiting) {
        if (d->WakeIdleWorker() >= 0) return false;
        m_waiting = 1;
        m_wakeup.Set();
    }
    d->m_cs.Enter();
    fence();
    observe_pre(d);
    u64 fn = vtable_of(d->vtable)[SimpleMessageDispatcher::kSlotGetMessage];
    bool got = fn == fn_get_message() ? d->GetMessage(out, m_index) : (guest_call(fn, {(u64)d, (u64)out, (u64)m_index}) & 1) != 0;
    if (got) {
        m_busy = 1;
        m_signalEvent = (u8)(m_current.m_message >> 15);
        m_current.m_message &= MessageDispatcherBlock::kMessageMask;
    }
    observe_post(d);
    fence();
    d->m_cs.Leave();
    return got;
}

// After a message (Handler): not busy; if it was exclusive, every waiting worker is woken (outside
// the lock, as the guest does); its keys are cleared under the lock.
void WorkerThread::MessageReady() {
    m_busy = 0;
    SimpleMessageDispatcher* d = m_owner;
    if (m_current.m_key0 == 0xffffffff || m_current.m_key1 == 0xffffffff) d->WakeWaitingWorkers();
    d->m_cs.Enter();
    fence();
    observe_pre(d);
    m_current.m_key0 = 0;
    m_current.m_key1 = 0;
    observe_post(d);
    fence();
    d->m_cs.Leave();
}

}  // namespace soa::native::kernel
