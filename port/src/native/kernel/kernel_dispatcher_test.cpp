// Differential tests of the dispatcher natives (kernel_dispatcher.cpp): two private dispatchers
// built the same way (the construction Global::InstantiateMessageDispatcher inlines, the guest's
// Initialize and Setup), each with a worker array of its own whose threads never run (the events
// made by the guest's Create), and a private TaskManager each for the (Task*, barrier) forms. A
// random sequence of operations (every bound form, GetMessage with other workers busy on keys,
// sync-end messages and their counters, full queues, suspend / resume, delete / cancel, the wake
// passes) runs on one through the guest functions (natives aren't installed in --selftest) and on
// the other through the native members; after each step the two states, normalized (pointers as
// "block 3" / "sentinel" / "manager"), the results, the serials, the out blocks and the task
// managers' barrier state must be equal. The Send* forms wait on their event: the guest's
// Event::Wait is stubbed for its run, the native's returns at once (sync::t_replay_no_wait).
#include <cstring>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "native/common/guest_stub.h"
#include "native/common/test.h"
#include "native/kernel/kernel_layout.h"
#include "native/sync/sync_check.h"

using namespace soa;
using namespace soa::native;
using namespace soa::native::kernel;

namespace {

u64 vtable_of(TestContext& t, const char* ztv) { return t.sym(ztv) + 0x10; }

constexpr s32 kBlocks = 16, kWorkers = 3;

// One side: a dispatcher, its fake workers, a task manager and a task it owns.
struct Side {
    alignas(16) u8 storage[sizeof(SimpleMessageDispatcher)];
    alignas(16) u8 workers[8 + kWorkers * sizeof(WorkerThread)];
    alignas(16) u8 tm_storage[sizeof(TaskManager)];
    alignas(16) Task task;
    SimpleMessageDispatcher* d = nullptr;
    TaskManager* tm = nullptr;

    void build(TestContext& t) {
        std::memset(storage, 0, sizeof storage);
        d = reinterpret_cast<SimpleMessageDispatcher*>(storage);
        d->vtable = (const void*)vtable_of(t, "_ZTVN4Aska23SimpleMessageDispatcherE");
        t.call("_ZN4Aska19FastCriticalSectionC1Ev", {(u64)&d->m_cs});
        d->m_queue.vtable = (const void*)vtable_of(t, "_ZTVN4Aska5TListINS_29MessageDispatcherBlockForListEEE");
        d->m_queue.m_sentinel.link.vtable = (const void*)vtable_of(t, "_ZTVN4Aska29MessageDispatcherBlockForListE");
        d->m_queue.m_sentinel.link.m_prev = &d->m_queue.m_sentinel.link;
        d->m_queue.m_sentinel.link.m_next = &d->m_queue.m_sentinel.link;
        d->m_freeBlocks.vtable = (const void*)vtable_of(t, "_ZTVN4Aska13TDynamicQueueIPNS_29MessageDispatcherBlockForListELb0EEE");
        d->m_freeBlocks.m_write = 1;
        t.call("_ZN4Aska5EventC1Ev", {(u64)&d->m_freeBlockEvent});
        t.call("_ZN4Aska23SimpleMessageDispatcher10InitializeEv", {(u64)d});
        t.call("_ZN4Aska23SimpleMessageDispatcher5SetupEii", {(u64)d, (u64)kBlocks, 0x55});
        std::memset(workers, 0, sizeof workers);
        *reinterpret_cast<u64*>(workers) = kWorkers;
        auto* w = reinterpret_cast<WorkerThread*>(workers + 8);
        for (s32 i = 0; i < kWorkers; i++) {
            w[i].base.vtable = (const void*)vtable_of(t, "_ZTVN4Aska23SimpleMessageDispatcher13_WorkerThreadE");
            t.call("_ZN4Aska5EventC1Ev", {(u64)&w[i].m_wakeup});
            t.call("_ZN4Aska5Event6CreateEbb", {(u64)&w[i].m_wakeup, 0, 0});
            w[i].m_waiting = 1;
            w[i].m_owner = d;
            w[i].m_index = (u8)i;
            w[i].m_started = 1;
        }
        d->m_workers = w;
        d->m_workerCount = kWorkers;
        std::memset(tm_storage, 0, sizeof tm_storage);
        tm = reinterpret_cast<TaskManager*>(tm_storage);
        t.call("_ZN4Aska11TaskManagerC2Ev", {(u64)tm});
        std::memset(&task, 0, sizeof task);
        task.link.vtable = (const void*)vtable_of(t, "_ZTVN4Aska4TaskE");
        task.m_owner = tm;
    }
    void destroy(TestContext& t) {
        for (s32 i = 0; i < kWorkers; i++) t.call("_ZN4Aska5Event4ExitEv", {(u64)&d->m_workers[i].m_wakeup});
        d->m_workers = nullptr;
        d->m_workerCount = 0;
        t.call("_ZN4Aska23SimpleMessageDispatcherD2Ev", {(u64)d});
        t.call("_ZN4Aska11TaskManagerD2Ev", {(u64)tm});
    }
    WorkerThread& worker(s32 i) { return d->m_workers[i]; }
};

// The state with pointers normalized.
struct Describer {
    const Side& s;
    std::string name(const void* p) const {
        if (!p) return "0";
        const SimpleMessageDispatcher* d = s.d;
        if (p == &d->m_queue.m_sentinel.link || p == &d->m_queue.m_sentinel) return "S";
        if (p >= (const void*)d->m_blocks && p < (const void*)(d->m_blocks + kBlocks)) {
            size_t off = (const u8*)p - (const u8*)d->m_blocks;
            return "B" + std::to_string(off / sizeof(MessageDispatcherBlockForList)) +
                   (off % sizeof(MessageDispatcherBlockForList) ? "+" + std::to_string(off % sizeof(MessageDispatcherBlockForList)) : "");
        }
        if (p == s.tm) return "TM";
        char b[32];
        snprintf(b, sizeof b, "%#llx", (unsigned long long)(u64)p);
        return b;
    }
    std::string block(const MessageDispatcherBlock& m) const {
        char b[256];
        snprintf(b, sizeof b, "{#%u msg %#x notify %s ev %s mgr %s bar %u ctr %s a %s,%s k %#llx,%#llx}", m.m_serial, m.m_message, name(m.m_notify).c_str(),
                 m.m_event ? "E" : "0", name(m.m_barrierManager).c_str(), m.m_barrier, name(m.m_counter).c_str(), name(m.m_arg0).c_str(),
                 name(m.m_arg1).c_str(), (unsigned long long)m.m_key0, (unsigned long long)m.m_key1);
        return b;
    }
    std::string all() const {
        const SimpleMessageDispatcher* d = s.d;
        std::string o;
        char b[256];
        snprintf(b, sizeof b, "S<%s,%s> count %d free r%u w%u cap %u full %u ev %u susp %u next %u\n", name(d->m_queue.m_sentinel.link.m_prev).c_str(),
                 name(d->m_queue.m_sentinel.link.m_next).c_str(), d->m_queue.m_count, d->m_freeBlocks.m_read, d->m_freeBlocks.m_write,
                 d->m_freeBlocks.m_capacity, d->m_full, d->m_freeBlockEvent.m_signaled, d->m_suspended, d->m_nextSerial);
        o += b;
        for (u32 i = 0; i < d->m_freeBlocks.m_capacity; i++) o += name(d->m_freeBlocks.m_items[i]) + " ";
        o += "\n";
        for (s32 i = 0; i < kBlocks; i++) {
            const MessageDispatcherBlockForList& l = d->m_blocks[i];
            o += "B" + std::to_string(i) + "<" + name(l.link.m_prev) + "," + name(l.link.m_next) + "> p" + std::to_string(l.m_priority) + " " + block(l.m_block) + "\n";
        }
        for (s32 i = 0; i < kWorkers; i++) {
            const WorkerThread& w = d->m_workers[i];
            snprintf(b, sizeof b, "W%d wait %u busy %u sig %u ev %u ", i, w.m_waiting, w.m_busy, w.m_signalEvent, w.m_wakeup.m_signaled);
            o += b + block(w.m_current) + "\n";
        }
        const TaskManager* tm = s.tm;
        snprintf(b, sizeof b, "TM created %#x pending %#x", tm->m_barrierCreated, tm->m_barrierPending);
        o += b;
        for (int k = 0; k < TaskManager::kNumLevels; k++)
            if (tm->m_barrierRefs[k] || tm->m_barrierCounts[k] || (tm->m_barrierCreated >> k & 1))
                o += " [" + std::to_string(k) + ": " + std::to_string(tm->m_barrierRefs[k]) + "/" + std::to_string(tm->m_barrierCounts[k]) + " ev " +
                     std::to_string(tm->m_barrierEvents[k].m_signaled) + "]";
        return o + "\n";
    }
};

std::string first_diff(const std::string& a, const std::string& b) {
    size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) i++;
    size_t ls = a.rfind('\n', i == 0 ? 0 : i - 1);
    ls = ls == std::string::npos ? 0 : ls + 1;
    size_t ea = a.find('\n', i), eb = b.find('\n', i);
    return "guest: " + a.substr(ls, ea - ls) + " | native: " + b.substr(ls, eb - ls);
}

}  // namespace

NATIVE_TEST("kernel/dispatcher-sequence") {
    static Side g, n;
    g.build(t);
    n.build(t);
    const u64 wait_fn = t.sym("_ZNK4Aska5Event4WaitEj");
    stub_isolated_at(wait_fn, "kernel_send_wait", 2);
    const std::string wait_name = stub_name(wait_fn);
    alignas(8) static s32 counters[2];
    counters[0] = counters[1] = 1;
    const u64 keys[4] = {0, 7, 9, 0xffffffff};
    std::string last = "build";
    int steps = 0;
    int full = 0, delivered = 0, sync_end = 0, sends = 0, worker_got = 0, barriers = 0;
    for (; steps < 1500; steps++) {
        // op weights: posting, delivering and finishing balanced so the queue neither stays full nor
        // empty (DeleteMessage leaks its block: kept rare)
        int r = t.rand_int(0, 99), op;
        if (r < 30) op = r % 8;
        else if (r < 36) op = 8;
        else if (r < 56) op = 9;
        else if (r < 66) op = 11;
        else if (r < 78) op = 13;
        else if (r < 81) op = 14;
        else if (r < 83) op = 15;
        else if (r < 86) op = 16;
        else if (r < 89) op = 17;
        else if (r < 92) op = 18;
        else if (r < 94) op = 19;
        else if (r < 97) op = 20;
        else if (r < 99) op = 21;
        else op = 22;
        u16 msg = (u16)t.rand_u64();
        u64 notify = 0x10000 + (t.rand_u64() & 0xff0), a0 = t.rand_u64(), a1 = t.rand_u64();
        u64 k0 = keys[t.rand_int(0, 9) ? t.rand_int(0, 2) : 3], k1 = keys[t.rand_int(0, 9) ? t.rand_int(0, 2) : 3];
        s8 prio = (s8)t.rand_int(-2, 4);
        s32 barrier = t.rand_int(-1, 33);
        s32 widx = t.rand_int(0, kWorkers - 1);
        s32* ctr = &counters[t.rand_int(0, 1)];
        u32 sg = 0xdead, sn = 0xdead;
        u64 rg = 0, rn = 0;
        alignas(16) MessageDispatcherBlock og{}, on{};
        bool cmp_out = false;
        char what[96];
        snprintf(what, sizeof what, "step %d op %d", steps, op);
        GuestArgs ga;
        auto P = [&](Side& s) { return (u64)s.d; };
        switch (op) {
        case 0:
            rg = t.call("_ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_Pja", {P(g), msg, notify, a0, a1, (u64)&sg, (u64)prio});
            rn = n.d->PostMessage(msg, (INotify*)notify, (void*)a0, (void*)a1, &sn, prio);
            break;
        case 1:
            ga.p(g.d).i(msg).i(notify).i(a0).i(a1).i(k0).i(k1).p(&sg).i((u64)prio);
            rg = t.call("_ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_mmPja", ga).x0;
            rn = n.d->PostMessage(msg, (INotify*)notify, (void*)a0, (void*)a1, k0, k1, &sn, prio);
            break;
        case 2:
            ga.p(g.d).p(&g.task).i((u64)barrier).i(msg).i(notify).i(a0).i(a1).p(&sg).i((u64)prio);
            rg = t.call("_ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_Pja", ga).x0;
            rn = n.d->PostMessage(&n.task, barrier, msg, (INotify*)notify, (void*)a0, (void*)a1, &sn, prio);
            break;
        case 3:
            ga.p(g.d).p(&g.task).i((u64)barrier).i(msg).i(notify).i(a0).i(a1).i(k0).i(k1).p(&sg).i((u64)prio);
            rg = t.call("_ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_mmPja", ga).x0;
            rn = n.d->PostMessage(&n.task, barrier, msg, (INotify*)notify, (void*)a0, (void*)a1, k0, k1, &sn, prio);
            break;
        case 4:
            rg = t.call("_ZN4Aska23SimpleMessageDispatcher21PostSyncMessageSingleEtPiPNS_7INotifyEPvS4_Pja",
                        {P(g), msg, (u64)ctr, notify, a0, a1, (u64)&sg, (u64)prio});
            rn = n.d->PostSyncMessageSingle(msg, ctr, (INotify*)notify, (void*)a0, (void*)a1, &sn, prio);
            break;
        case 5:
            ga.p(g.d).i(msg).p(ctr).i(notify).i(a0).i(a1).i(k0).i(k1).p(&sg).i((u64)prio);
            rg = t.call("_ZN4Aska23SimpleMessageDispatcher21PostSyncMessageSingleEtPiPNS_7INotifyEPvS4_mmPja", ga).x0;
            rn = n.d->PostSyncMessageSingle(msg, ctr, (INotify*)notify, (void*)a0, (void*)a1, k0, k1, &sn, prio);
            break;
        case 6:
            rg = t.call("_ZN4Aska23SimpleMessageDispatcher18PostSyncMessageEndEtPiPNS_7INotifyEPvS4_Pja",
                        {P(g), msg, (u64)ctr, notify, a0, a1, (u64)&sg, (u64)prio});
            rn = n.d->PostSyncMessageEnd(msg, ctr, (INotify*)notify, (void*)a0, (void*)a1, &sn, prio);
            break;
        case 7:
            ga.p(g.d).i(msg).p(ctr).i(notify).i(a0).i(a1).i(k0).i(k1).p(&sg).i((u64)prio);
            rg = t.call("_ZN4Aska23SimpleMessageDispatcher18PostSyncMessageEndEtPiPNS_7INotifyEPvS4_mmPja", ga).x0;
            rn = n.d->PostSyncMessageEnd(msg, ctr, (INotify*)notify, (void*)a0, (void*)a1, k0, k1, &sn, prio);
            break;
        case 8: {  // the Send* forms
            int form = t.rand_int(0, 7);
            {
                StubSession ss;
                ss.only = {wait_name};
                switch (form) {
                case 0: rg = t.call("_ZN4Aska23SimpleMessageDispatcher11SendMessageEtPNS_7INotifyEPvS3_a", {P(g), msg, notify, a0, a1, (u64)prio}); break;
                case 1:
                    ga.p(g.d).i(msg).i(notify).i(a0).i(a1).i(k0).i(k1).i((u64)prio);
                    rg = t.call("_ZN4Aska23SimpleMessageDispatcher11SendMessageEtPNS_7INotifyEPvS3_mma", ga).x0;
                    break;
                case 2: rg = t.call("_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEtPNS_7INotifyEPvS3_", {P(g), msg, notify, a0, a1}); break;
                case 3: rg = t.call("_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEtPNS_7INotifyEPvS3_mm", {P(g), msg, notify, a0, a1, k0, k1}); break;
                case 4:
                    ga.p(g.d).p(&g.task).i((u64)barrier).i(msg).i(notify).i(a0).i(a1).i((u64)prio);
                    rg = t.call("_ZN4Aska23SimpleMessageDispatcher11SendMessageEPNS_4TaskEitPNS_7INotifyEPvS5_a", ga).x0;
                    break;
                case 5:
                    ga.p(g.d).p(&g.task).i((u64)barrier).i(msg).i(notify).i(a0).i(a1).i(k0).i(k1).i((u64)prio);
                    rg = t.call("_ZN4Aska23SimpleMessageDispatcher11SendMessageEPNS_4TaskEitPNS_7INotifyEPvS5_mma", ga).x0;
                    break;
                case 6:
                    rg = t.call("_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEPNS_4TaskEitPNS_7INotifyEPvS5_",
                                {P(g), (u64)&g.task, (u64)barrier, msg, notify, a0, a1});
                    break;
                default:
                    ga.p(g.d).p(&g.task).i((u64)barrier).i(msg).i(notify).i(a0).i(a1).i(k0).i(k1);
                    rg = t.call("_ZN4Aska23SimpleMessageDispatcher15SendMessageHighEPNS_4TaskEitPNS_7INotifyEPvS5_mm", ga).x0;
                    break;
                }
            }
            sync::t_replay_no_wait = true;
            switch (form) {
            case 0: rn = n.d->SendMessage(msg, (INotify*)notify, (void*)a0, (void*)a1, prio); break;
            case 1: rn = n.d->SendMessage(msg, (INotify*)notify, (void*)a0, (void*)a1, k0, k1, prio); break;
            case 2: rn = n.d->SendMessageHigh(msg, (INotify*)notify, (void*)a0, (void*)a1); break;
            case 3: rn = n.d->SendMessageHigh(msg, (INotify*)notify, (void*)a0, (void*)a1, k0, k1); break;
            case 4: rn = n.d->SendMessage(&n.task, barrier, msg, (INotify*)notify, (void*)a0, (void*)a1, prio); break;
            case 5: rn = n.d->SendMessage(&n.task, barrier, msg, (INotify*)notify, (void*)a0, (void*)a1, k0, k1, prio); break;
            case 6: rn = n.d->SendMessageHigh(&n.task, barrier, msg, (INotify*)notify, (void*)a0, (void*)a1); break;
            default: rn = n.d->SendMessageHigh(&n.task, barrier, msg, (INotify*)notify, (void*)a0, (void*)a1, k0, k1); break;
            }
            sync::t_replay_no_wait = false;
            snprintf(what, sizeof what, "step %d send form %d", steps, form);
            break;
        }
        case 9:
        case 10: {  // GetMessage(block, index): the caller's index, maybe none (-1)
            s32 idx = t.rand_int(-1, kWorkers - 1);
            rg = t.call("_ZN4Aska23SimpleMessageDispatcher10GetMessageEPNS_22MessageDispatcherBlockEi", {P(g), (u64)&og, (u64)(u32)idx});
            rn = n.d->GetMessage(&on, idx);
            cmp_out = (rg & 1) != 0;
            break;
        }
        case 11:
        case 12:
            rg = t.call("_ZN4Aska23SimpleMessageDispatcher13_WorkerThread10GetMessageEPNS_22MessageDispatcherBlockE",
                        {(u64)&g.worker(widx), (u64)&g.worker(widx).m_current});
            rn = n.worker(widx).GetMessage(&n.worker(widx).m_current);
            break;
        case 13:
            t.call("_ZN4Aska23SimpleMessageDispatcher13_WorkerThread12MessageReadyEv", {(u64)&g.worker(widx)});
            n.worker(widx).MessageReady();
            break;
        case 14:
            if (t.rand_int(0, 1)) {
                t.call("_ZN4Aska23SimpleMessageDispatcher19SuspendWorkerThreadEv", {P(g)});
                n.d->SuspendWorkerThread();
            } else {
                t.call("_ZN4Aska23SimpleMessageDispatcher18ResumeWorkerThreadEv", {P(g)});
                n.d->ResumeWorkerThread();
            }
            break;
        case 15: {
            s32 serial = t.rand_int(0, 9) ? (s32)(g.d->m_nextSerial - 1 - t.rand_int(0, 6)) : (t.rand_int(0, 3) ? 0x10003 : -1);
            if (t.rand_int(0, 1)) {
                rg = t.call("_ZN4Aska23SimpleMessageDispatcher13DeleteMessageEi", {P(g), (u64)(u32)serial});
                rn = n.d->DeleteMessage(serial);
            } else {
                rg = t.call("_ZN4Aska23SimpleMessageDispatcher13CancelMessageEj", {P(g), (u64)(u32)serial});
                rn = n.d->CancelMessage((u32)serial);
            }
            break;
        }
        case 16: {
            bool front = t.rand_int(0, 1);
            u64 pg = front ? t.call("_ZN4Aska23SimpleMessageDispatcher17AddMessageToFrontEv", {P(g)})
                           : t.call("_ZN4Aska23SimpleMessageDispatcher10AddMessageEa", {P(g), (u64)prio});
            MessageDispatcherBlock* pn = front ? n.d->AddMessageToFront() : n.d->AddMessage(prio);
            Describer dg{g}, dn{n};
            t.expect_eq(dg.name((void*)pg), dn.name(pn), "AddMessage result");
            break;
        }
        case 17:
            if (t.rand_int(0, 1)) {
                rg = t.call("_ZN4Aska23SimpleMessageDispatcher18WakeupWorkerThreadEv", {P(g)});
                rn = n.d->WakeupWorkerThread();
            } else {
                t.call("_ZN4Aska23SimpleMessageDispatcher22WakeupAllWorkerThreadsEv", {P(g)});
                n.d->WakeupAllWorkerThreads();
            }
            break;
        case 18:  // the workers' events consumed (as a worker's Wait does)
            for (s32 i = 0; i < kWorkers; i++)
                if (t.rand_int(0, 1)) g.worker(i).m_wakeup.m_signaled = n.worker(i).m_wakeup.m_signaled = 0;
            break;
        case 19:  // a worker on another message: busy with keys (GetMessage's exclusion)
            for (Side* s : {&g, &n}) {
                s->worker(widx).m_busy = 1;
                s->worker(widx).m_current.m_key0 = k0;
                s->worker(widx).m_current.m_key1 = k1;
            }
            break;
        case 20:  // the counters
            counters[t.rand_int(0, 1)] = t.rand_int(0, 1);
            break;
        case 21:  // a job's barrier done (the guest's Handler)
            if ((u32)barrier < 0x20) {
                t.call("_ZN4Aska11TaskManager27DecrementThreadBarrierCountEi", {(u64)g.tm, (u64)barrier});
                t.call("_ZN4Aska11TaskManager19DeleteThreadBarrierEi", {(u64)g.tm, (u64)barrier});
                n.tm->DecrementThreadBarrierCount(barrier);
                n.tm->DeleteThreadBarrier(barrier);
            }
            break;
        default:  // IsWorkerThreadSuspended
            rg = t.call("_ZNK4Aska23SimpleMessageDispatcher23IsWorkerThreadSuspendedEv", {P(g)});
            rn = n.d->IsWorkerThreadSuspended();
            break;
        }
        if (op <= 8 && !(rg & 1)) full++;
        if (op == 8 && (rg & 1)) sends++;
        if ((op == 9 || op == 10) && (rg & 1)) delivered++, sync_end += (og.m_message & MessageDispatcherBlock::kFlagWaitCounter) != 0;
        if ((op == 11 || op == 12) && (rg & 1)) worker_got++;
        if ((op == 2 || op == 3) && (rg & 1) && (u32)barrier < 0x20) barriers++;
        bool ok = t.expect_eq(rg & 0xff, rn & 0xff, what) && t.expect_eq(sg, sn, "serial out");
        if (cmp_out) {
            Describer dg{g}, dn{n};
            ok = t.expect_eq(dg.block(og), dn.block(on), "out block") && ok;
        }
        std::string sgd = Describer{g}.all(), snd = Describer{n}.all();
        if (sgd != snd) {
            t.fail("%s (after %s): %s", what, last.c_str(), first_diff(sgd, snd).c_str());
            ok = false;
        }
        if (!ok) break;
        last = what;
    }
    t.expect_eq(steps, 1500, "steps run");
    // (the sequence reached every path that matters)
    t.expect_eq(full > 10 && delivered > 10 && sync_end > 0 && sends > 10 && worker_got > 10 && barriers > 5, true, "coverage");
    fprintf(stderr, "  dispatcher-sequence: %d full, %d delivered (%d sync end), %d sends, %d worker gets, %d barrier posts\n", full, delivered,
                                       sync_end, sends, worker_got, barriers);
    g.destroy(t);
    n.destroy(t);
}
