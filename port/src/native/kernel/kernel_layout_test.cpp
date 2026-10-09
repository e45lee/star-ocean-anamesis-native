// Layout tests for kernel_layout.h (port/PLAN.md task 6, types first): the recovered classes read
// against real guest objects. Each test either builds a private object with the guest's own
// constructor (or the construction the guest inlines, step by step with the guest's member
// constructors) and drives it with the guest's methods, then reads the fields through the layout
// classes and compares them with the guest's accessors and with what the test did; or walks a live
// object of the running game read-only (structural fields only: the game's threads keep running).
// No natives here: in --selftest every call reaches the guest code.
#include <cstring>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/loader.h"
#include "native/common/test.h"
#include "native/kernel/kernel_layout.h"

using namespace soa;
using namespace soa::native::kernel;

namespace {

template <typename T>
T* at_vaddr(u64 vaddr) {
    return reinterpret_cast<T*>(main_lib()->base + vaddr);
}

u64 vtable_of(TestContext& t, const char* ztv) { return t.sym(ztv) + 0x10; }
u64 call0(TestContext& t, const char* name) { return guest_call(t.sym(name), std::initializer_list<u64>{}); }

constexpr const char* kZtvMessageDispatcher = "_ZTVN4Aska17MessageDispatcherE";
constexpr const char* kZtvSimpleMessageDispatcher = "_ZTVN4Aska23SimpleMessageDispatcherE";
constexpr const char* kZtvWorkerThread = "_ZTVN4Aska23SimpleMessageDispatcher13_WorkerThreadE";
constexpr const char* kZtvBlockForList = "_ZTVN4Aska29MessageDispatcherBlockForListE";
constexpr const char* kZtvBlockList = "_ZTVN4Aska5TListINS_29MessageDispatcherBlockForListEEE";
constexpr const char* kZtvBlockQueue = "_ZTVN4Aska13TDynamicQueueIPNS_29MessageDispatcherBlockForListELb0EEE";

// The dispatcher's queue from the first (highest priority) block, at most `limit` blocks.
std::vector<MessageDispatcherBlockForList*> queue_of(SimpleMessageDispatcher* d, int limit = 64) {
    std::vector<MessageDispatcherBlockForList*> out;
    auto* sentinel = &d->m_queue.m_sentinel;
    for (auto* l = reinterpret_cast<MessageDispatcherBlockForList*>(sentinel->link.m_next);
         l != sentinel && l && (int)out.size() < limit;
         l = reinterpret_cast<MessageDispatcherBlockForList*>(l->link.m_next))
        out.push_back(l);
    return out;
}

}  // namespace

// The live dispatcher (Global::m_pMessageDispatcher), read-only: vtables, the block array and free
// queue Setup built (capacity = the app's block count + 1), the worker array and each worker's owner,
// index, vtable and started flag.
NATIVE_TEST("kernel/layout-live-dispatcher") {
    auto* md = *at_vaddr<MessageDispatcher*>(kVaddrGlobalMessageDispatcher);
    if (!t.expect_eq(md != nullptr, true, "Global::m_pMessageDispatcher")) return;
    SimpleMessageDispatcher* d = &md->base;
    t.expect_eq((u64)d->vtable, vtable_of(t, kZtvMessageDispatcher), "vtable = MessageDispatcher's");
    t.expect_eq((u64)d->m_queue.vtable, vtable_of(t, kZtvBlockList), "queue: TList vtable");
    t.expect_eq((u64)d->m_queue.m_sentinel.link.vtable, vtable_of(t, kZtvBlockForList), "queue sentinel: block vtable");
    t.expect_eq((u64)d->m_freeBlocks.vtable, vtable_of(t, kZtvBlockQueue), "free queue: TDynamicQueue vtable");
    t.expect_eq(d->m_blocks != nullptr, true, "block array");
    t.expect_eq((u8*)d->m_blocks, d->m_blockStorage, "block array = its allocation");
    u64 app = *at_vaddr<u64>(kVaddrGlobalApp);
    u32 nblocks = app ? *reinterpret_cast<u32*>(app + 0x88) : 0;  // Setup(app->+0x88, 0x80)
    t.expect_eq(d->m_freeBlocks.m_capacity, nblocks + 1, "free queue capacity = blocks + 1");
    t.expect_eq((u8*)d->m_freeBlocks.m_items, (u8*)d->m_blocks + (u64)nblocks * sizeof(MessageDispatcherBlockForList),
                "free queue items after the blocks");
    int bad = 0;
    for (u32 i = 0; i < nblocks; i++)
        if ((u64)d->m_blocks[i].link.vtable != vtable_of(t, kZtvBlockForList)) bad++;
    t.expect_eq(bad, 0, "every block's vtable");
    t.expect_eq(d->m_threadPriority, 0x80, "thread priority (Setup's 0x80)");
    t.expect_eq((u8)(t.call("_ZNK4Aska23SimpleMessageDispatcher23IsWorkerThreadSuspendedEv", {(u64)d}) & 0xff),
                d->m_suspended, "IsWorkerThreadSuspended = m_suspended");
    if (!t.expect_eq(d->m_workers != nullptr, true, "workers")) return;
    t.expect_eq(d->m_workerCount >= 1 && d->m_workerCount <= 256, true, "worker count in 1..256");
    t.expect_eq(*reinterpret_cast<u64*>((u8*)d->m_workers - 8), (u64)d->m_workerCount, "new[] cookie = worker count");
    for (s32 i = 0; i < d->m_workerCount; i++) {
        WorkerThread& w = d->m_workers[i];
        t.expect_eq((u64)w.base.vtable, vtable_of(t, kZtvWorkerThread), "worker vtable");
        t.expect_eq(w.m_owner, d, "worker owner");
        t.expect_eq((s32)w.m_index, i, "worker index");
        t.expect_eq(w.m_started, (u8)1, "worker Handler started");
        t.expect_eq(w.m_exit, (u8)0, "worker not exiting");
        t.expect_eq(w.base.m_thread != 0, true, "worker pthread");
    }
}

// A private SimpleMessageDispatcher built the way Global::InstantiateMessageDispatcher does (its
// constructor is inlined there), without worker threads: Initialize, Setup(4, 0x55); the Post* forms
// write the fields read back from the queue in priority order; GetMessage(block, -1) (vtable slot 2)
// copies the first deliverable message out and returns its block to the free queue; a
// PostSyncMessageEnd message waits for its counter; Suspend / Resume; DeleteMessage; the destructor.
NATIVE_TEST("kernel/layout-message-dispatcher") {
    alignas(16) static u8 storage[sizeof(SimpleMessageDispatcher)];
    std::memset(storage, 0, sizeof storage);
    auto* d = reinterpret_cast<SimpleMessageDispatcher*>(storage);
    d->vtable = (const void*)vtable_of(t, kZtvSimpleMessageDispatcher);
    t.call("_ZN4Aska19FastCriticalSectionC1Ev", {(u64)&d->m_cs});
    d->m_queue.vtable = (const void*)vtable_of(t, kZtvBlockList);
    d->m_queue.m_sentinel.link.vtable = (const void*)vtable_of(t, kZtvBlockForList);
    d->m_queue.m_sentinel.link.m_prev = &d->m_queue.m_sentinel.link;
    d->m_queue.m_sentinel.link.m_next = &d->m_queue.m_sentinel.link;
    d->m_queue.m_count = 0;
    d->m_freeBlocks.vtable = (const void*)vtable_of(t, kZtvBlockQueue);
    d->m_freeBlocks.m_write = 1;
    t.call("_ZN4Aska5EventC1Ev", {(u64)&d->m_freeBlockEvent});
    t.expect_eq(t.call("_ZN4Aska23SimpleMessageDispatcher10InitializeEv", {(u64)d}) & 1, (u64)1, "Initialize");
    t.expect_eq(d->m_threadPriority, 0x80, "Initialize: priority 0x80");
    t.expect_eq(d->m_workers, (WorkerThread*)nullptr, "Initialize: no workers");
    const s32 kBlocks = 4;
    if (!t.expect_eq(t.call("_ZN4Aska23SimpleMessageDispatcher5SetupEii", {(u64)d, (u64)kBlocks, 0x55}) & 1, (u64)1, "Setup"))
        return;
    t.expect_eq(d->m_threadPriority, 0x55, "Setup: priority");
    t.expect_eq(d->m_full, (u8)0, "Setup: not full");
    t.expect_eq(d->m_freeBlocks.m_capacity, (u32)kBlocks + 1, "Setup: queue capacity");
    t.expect_eq(d->m_freeBlocks.m_read, 0u, "Setup: read index");
    t.expect_eq(d->m_freeBlocks.m_write, 0u, "Setup: write index wrapped");
    t.expect_eq((u8*)d->m_blocks, d->m_blockStorage, "Setup: blocks = storage");
    t.expect_eq((u8*)d->m_freeBlocks.m_items, (u8*)d->m_blocks + kBlocks * sizeof(MessageDispatcherBlockForList), "Setup: items");
    for (s32 i = 0; i < kBlocks; i++) {
        t.expect_eq(d->m_freeBlocks.m_items[i + 1], &d->m_blocks[i], "Setup: free queue holds block i");
        t.expect_eq((u64)d->m_blocks[i].link.vtable, vtable_of(t, kZtvBlockForList), "Setup: block vtable");
    }

    const u64 kNotify = 0x1111000, kA0 = 0x2222000, kA1 = 0x3333000;
    u32 serial = 0xffffffff;
    u64 ok = t.call("_ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_Pja",
                    {(u64)d, 0xc123, kNotify, kA0, kA1, (u64)&serial, 3});
    t.expect_eq(ok & 1, (u64)1, "PostMessage");
    t.expect_eq(serial, 0u, "serial 0");
    t.expect_eq(d->m_nextSerial, (u16)1, "m_nextSerial");
    t.expect_eq(d->m_queue.m_count, 1, "queue count 1");
    MessageDispatcherBlockForList* b0 = &d->m_blocks[0];
    t.expect_eq(d->m_freeBlocks.m_read, 1u, "first free block taken");
    t.expect_eq(b0->m_block.m_serial, (u16)0, "block serial");
    t.expect_eq(b0->m_block.m_message, (u16)0x0123, "block message & 0x3fff");
    t.expect_eq((u64)b0->m_block.m_notify, kNotify, "block notify");
    t.expect_eq((u64)b0->m_block.m_arg0, kA0, "block arg0");
    t.expect_eq((u64)b0->m_block.m_arg1, kA1, "block arg1");
    t.expect_eq(b0->m_block.m_counter, (s32*)nullptr, "block counter");
    t.expect_eq(b0->m_priority, (s8)3, "block priority");
    t.expect_eq(b0->link.m_next, &d->m_queue.m_sentinel.link, "block -> sentinel");
    t.expect_eq(b0->link.m_prev, &d->m_queue.m_sentinel.link, "sentinel <- block");

    // The (unsigned long, unsigned long) form, priority 5: goes in front; then another 3: after b0.
    GuestArgs ga;
    ga.p(d).i(0x45).i(kNotify + 1).i(kA0 + 1).i(kA1 + 1).i(0x77).i(0x88).p(&serial).i(5);
    t.expect_eq(t.call("_ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_mmPja", ga).x0 & 1, (u64)1, "PostMessage(keys)");
    t.expect_eq(serial, 1u, "serial 1");
    t.call("_ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_Pja",
           {(u64)d, 0x46, kNotify + 2, kA0 + 2, kA1 + 2, (u64)&serial, 3});
    auto q = queue_of(d);
    if (t.expect_eq(q.size(), (size_t)3, "queue walk: 3 blocks")) {
        t.expect_eq(q[0]->m_block.m_serial, (u16)1, "order: priority 5 first");
        t.expect_eq(q[0]->m_block.m_key0, (u64)0x77, "key0");
        t.expect_eq(q[0]->m_block.m_key1, (u64)0x88, "key1");
        t.expect_eq(q[0]->m_priority, (s8)5, "priority 5");
        t.expect_eq(q[1]->m_block.m_serial, (u16)0, "order: then the first priority 3");
        t.expect_eq(q[2]->m_block.m_serial, (u16)2, "order: then the second priority 3 (FIFO)");
        t.expect_eq(q[2]->link.m_prev, &q[1]->link, "prev link");
        t.expect_eq(d->m_queue.m_sentinel.link.m_prev, &q[2]->link, "sentinel.m_prev = last");
    }
    t.expect_eq(d->m_queue.m_count, 3, "queue count 3");

    // PostSyncMessageEnd, priority 9 (first): flagged kFlagWaitCounter, held while *counter != 0.
    alignas(8) static s32 counter;
    counter = 1;
    t.expect_eq(t.call("_ZN4Aska23SimpleMessageDispatcher18PostSyncMessageEndEtPiPNS_7INotifyEPvS4_Pja",
                       {(u64)d, 0x47, (u64)&counter, kNotify + 3, kA0 + 3, kA1 + 3, (u64)&serial, 9}) & 1,
                (u64)1, "PostSyncMessageEnd");
    q = queue_of(d);
    if (t.expect_eq(q.size(), (size_t)4, "queue walk: 4 blocks")) {
        t.expect_eq(q[0]->m_block.m_message, (u16)(0x47 | MessageDispatcherBlock::kFlagWaitCounter), "sync end: message | 0x4000");
        t.expect_eq(q[0]->m_block.m_counter, &counter, "sync end: counter");
        t.expect_eq((u64)q[0]->m_block.m_notify, kNotify + 3, "sync end: notify");
    }

    // GetMessage skips the held sync-end message and takes serial 1 (priority 5).
    alignas(16) static MessageDispatcherBlock out;
    std::memset(&out, 0, sizeof out);
    u32 write_before = d->m_freeBlocks.m_write;
    u64 got = t.call("_ZN4Aska23SimpleMessageDispatcher10GetMessageEPNS_22MessageDispatcherBlockEi", {(u64)d, (u64)&out, 0xffffffff});
    t.expect_eq(got & 1, (u64)1, "GetMessage");
    t.expect_eq(out.m_serial, (u16)1, "GetMessage: the priority 5 message (sync end held)");
    t.expect_eq((u64)out.m_notify, kNotify + 1, "GetMessage: notify copied");
    t.expect_eq(out.m_key0, (u64)0x77, "GetMessage: key0 copied");
    t.expect_eq(d->m_queue.m_count, 3, "GetMessage: count 3");
    t.expect_eq(d->m_freeBlocks.m_items[write_before] != nullptr, true, "GetMessage: block back in the free queue");
    t.expect_eq(d->m_freeBlocks.m_write, (write_before + 1) % d->m_freeBlocks.m_capacity, "GetMessage: free write index");
    // Suspended: nothing delivered.
    t.call("_ZN4Aska23SimpleMessageDispatcher19SuspendWorkerThreadEv", {(u64)d});
    t.expect_eq(d->m_suspended, (u8)1, "SuspendWorkerThread");
    t.expect_eq(t.call("_ZNK4Aska23SimpleMessageDispatcher23IsWorkerThreadSuspendedEv", {(u64)d}) & 0xff, (u64)1, "IsWorkerThreadSuspended");
    t.expect_eq(t.call("_ZN4Aska23SimpleMessageDispatcher10GetMessageEPNS_22MessageDispatcherBlockEi", {(u64)d, (u64)&out, 0xffffffff}) & 1,
                (u64)0, "GetMessage while suspended");
    t.call("_ZN4Aska23SimpleMessageDispatcher18ResumeWorkerThreadEv", {(u64)d});
    t.expect_eq(d->m_suspended, (u8)0, "ResumeWorkerThread");
    // Counter released: the sync-end message comes first; its copied counter is cleared.
    counter = 0;
    t.call("_ZN4Aska23SimpleMessageDispatcher10GetMessageEPNS_22MessageDispatcherBlockEi", {(u64)d, (u64)&out, 0xffffffff});
    t.expect_eq(out.m_message, (u16)(0x47 | MessageDispatcherBlock::kFlagWaitCounter), "GetMessage: sync end once counter is 0");
    t.expect_eq(out.m_counter, (s32*)nullptr, "GetMessage: sync end's counter cleared");
    t.expect_eq((u64)out.m_arg0, kA0 + 3, "GetMessage: arg0");
    t.expect_eq((u64)out.m_arg1, kA1 + 3, "GetMessage: arg1");
    // DeleteMessage(serial 2) unlinks it; the queue keeps serial 0.
    t.expect_eq(t.call("_ZN4Aska23SimpleMessageDispatcher13DeleteMessageEi", {(u64)d, 2}) & 1, (u64)1, "DeleteMessage(2)");
    q = queue_of(d);
    if (t.expect_eq(q.size(), (size_t)1, "after DeleteMessage: 1 block")) t.expect_eq(q[0]->m_block.m_serial, (u16)0, "serial 0 left");
    t.expect_eq(d->m_queue.m_count, 1, "after DeleteMessage: count 1");
    t.call("_ZN4Aska23SimpleMessageDispatcher13DeleteMessageEi", {(u64)d, 0xffffffff});
    t.expect_eq(d->m_queue.m_sentinel.link.m_next, &d->m_queue.m_sentinel.link, "DeleteMessage(-1): empty");

    t.call("_ZN4Aska23SimpleMessageDispatcherD2Ev", {(u64)d});
    t.expect_eq((u64)d->vtable, vtable_of(t, kZtvSimpleMessageDispatcher), "destructor: base vtable");
    t.expect_eq(d->m_freeBlocks.m_items, (MessageDispatcherBlockForList**)nullptr, "destructor: queue reset");
}

// A private TaskManager: the guest constructor, then Tasks (the inlined Task construction) added with
// level masks: owner, level, the per-level and total counts, the list links, GetTotalTaskNumber;
// thread barriers (created / pending masks, refs, counts); end notifications; Delete; the destructor.
NATIVE_TEST("kernel/layout-task-manager") {
    alignas(16) static u8 storage[sizeof(TaskManager)];
    std::memset(storage, 0xa5, sizeof storage);
    auto* tm = reinterpret_cast<TaskManager*>(storage);
    t.call("_ZN4Aska11TaskManagerC2Ev", {(u64)tm});
    u64 vt = t.sym("_ZTVN4Aska11TaskManagerE");
    t.expect_eq((u64)tm->vtable, vt + 0x10, "vtable");
    t.expect_eq((u64)tm->task.link.vtable, vt + 0xa0, "Task base vtable (thunks at +0xa0)");
    t.expect_eq((u64)tm->m_sentinel.vtable, vtable_of(t, "_ZTVN4Aska21AnimatableLinkElementE"), "sentinel vtable");
    t.expect_eq(tm->m_sentinel.m_prev, &tm->m_sentinel, "empty list: prev");
    t.expect_eq(tm->m_sentinel.m_next, &tm->m_sentinel, "empty list: next");
    t.expect_eq(tm->m_count, 0, "count 0");
    t.expect_eq(tm->task.m_owner, (TaskManager*)nullptr, "Task base: no owner");
    t.expect_eq(tm->task.m_level, 0x40u, "Task base: GetDefaultLevel() = 0x40");
    t.expect_eq(tm->m_ringHead, tm, "ring head = this");
    t.expect_eq(tm->m_ringPrev, tm, "ring prev = this");
    t.expect_eq(tm->m_ringNext, tm, "ring next = this");
    t.expect_eq(tm->m_broadcastIds, (u8)0x0f, "broadcast ids 0x0f");
    t.expect_eq(tm->m_totalCount, 0, "total 0");
    t.expect_eq(tm->m_barrierCreated, 0u, "no barriers");
    t.expect_eq(tm->m_taskList, (Task**)nullptr, "no task list");

    alignas(16) static Task tasks[3];
    std::memset(tasks, 0, sizeof tasks);
    for (Task& k : tasks) k.link.vtable = (const void*)vtable_of(t, "_ZTVN4Aska4TaskE");
    const u32 levels[3] = {0x5, 0x4, 0};  // 0: the task's GetDefaultLevel (0x40)
    for (int i = 0; i < 3; i++) t.call("_ZN4Aska11TaskManager3AddEPNS_4TaskEj", {(u64)tm, (u64)&tasks[i], levels[i]});
    t.expect_eq(tasks[0].m_owner, tm, "Add: owner");
    t.expect_eq(tasks[0].m_level, 0x5u, "Add: level");
    t.expect_eq(tasks[2].m_level, 0x40u, "Add(0): default level");
    t.expect_eq(tm->m_count, 3, "Add: list count");
    t.expect_eq(tm->m_levelCount[0], 1, "level 0 count");
    t.expect_eq(tm->m_levelCount[2], 2, "level 2 count");
    t.expect_eq(tm->m_levelCount[6], 1, "level 6 count");
    t.expect_eq(tm->m_totalCount, 4, "total = set bits");
    t.expect_eq((s32)t.call("_ZNK4Aska11TaskManager18GetTotalTaskNumberEv", {(u64)tm}), 4, "GetTotalTaskNumber");
    // TList::Add's links: sentinel.m_prev = the last added, m_next chains from the first.
    t.expect_eq(tm->m_sentinel.m_prev, &tasks[2].link, "list: sentinel.m_prev = last");
    t.expect_eq(tasks[0].link.m_next, &tasks[1].link, "list: next");
    t.expect_eq(tasks[2].link.m_next, &tm->m_sentinel, "list: last -> sentinel");

    t.call("_ZN4Aska11TaskManager16AddThreadBarrierEi", {(u64)tm, 3});
    t.expect_eq(tm->m_barrierCreated, 1u << 3, "AddThreadBarrier: created bit");
    t.expect_eq(tm->m_barrierPending, 1u << 3, "AddThreadBarrier: pending bit (reset)");
    t.expect_eq(tm->m_barrierRefs[3], 1, "AddThreadBarrier: refs");
    t.call("_ZN4Aska11TaskManager27IncrementThreadBarrierCountEi", {(u64)tm, 3});
    t.expect_eq(tm->m_barrierCounts[3], 1, "IncrementThreadBarrierCount");
    t.call("_ZN4Aska11TaskManager27DecrementThreadBarrierCountEi", {(u64)tm, 3});
    t.expect_eq(tm->m_barrierCounts[3], 0, "DecrementThreadBarrierCount");
    t.expect_eq(tm->m_barrierPending, 0u, "count 0: event set, pending cleared");
    t.call("_ZN4Aska11TaskManager19DeleteThreadBarrierEi", {(u64)tm, 3});
    t.expect_eq(tm->m_barrierRefs[3], 0, "DeleteThreadBarrier: refs");

    t.expect_eq(t.call("_ZN4Aska11TaskManager19CreateEndNotifyListEi", {(u64)tm, 4}) & 1, (u64)1, "CreateEndNotifyList");
    t.expect_eq(tm->m_endNotifyCount, (u16)5, "end notify count = n + 1");
    t.expect_eq(t.call("_ZN4Aska11TaskManager12AddEndNotifyEPNS_7INotifyEm", {(u64)tm, 0x5550000, 0x66}) & 1, (u64)1, "AddEndNotify");
    if (tm->m_endNotifies) {
        t.expect_eq(tm->m_endNotifies[0].m_used, (u8)1, "head used");
        t.expect_eq((u64)tm->m_endNotifies[1].m_notify, (u64)0x5550000, "entry 1 notify");
        t.expect_eq(tm->m_endNotifies[1].m_arg, (u64)0x66, "entry 1 arg");
        t.expect_eq(tm->m_endNotifies[1].m_used, (u8)1, "entry 1 used");
        t.expect_eq(tm->m_endNotifies[0].m_next, (u8)1, "head -> 1");
        t.expect_eq(tm->m_endNotifies[0].m_last, (u8)1, "head last = 1");
    }
    t.call("_ZN4Aska11TaskManager15RemoveEndNotifyEPNS_7INotifyEm", {(u64)tm, 0x5550000, 0x66});

    for (Task& k : tasks) t.call("_ZN4Aska11TaskManager6DeleteEPNS_4TaskE", {(u64)tm, (u64)&k});
    t.expect_eq(tm->m_totalCount, 0, "Delete: total 0");
    t.expect_eq(tm->m_levelCount[2], 0, "Delete: level 2 count 0");
    t.expect_eq(tm->m_count, 0, "Delete: list empty");
    t.call("_ZN4Aska11TaskManagerD2Ev", {(u64)tm});
}

// The live system task manager and the main task, read-only: vtables, the ring, the main task's owner
// and accessors (rRootFiberKernel, rCamera, rResourceManager, FrameCounter's field), the root fiber
// kernel's chain (owner kernel, ascending priority).
NATIVE_TEST("kernel/layout-live-tasks") {
    auto* tm = *at_vaddr<TaskManager*>(kVaddrGlobalSystemTaskManager);
    if (!t.expect_eq(tm != nullptr, true, "Global::m_pSystemTaskManager")) return;
    u64 vt = t.sym("_ZTVN4Aska11TaskManagerE");
    t.expect_eq((u64)tm->vtable, vt + 0x10, "system task manager vtable");
    t.expect_eq((u64)tm->task.link.vtable, vt + 0xa0, "Task base vtable");
    t.expect_eq(tm->m_ringHead, tm, "ring head");
    t.expect_eq(tm->m_taskList != nullptr, true, "task list allocated (OwnersKickTask ran)");
    t.expect_eq(tm->m_capacity > 0, true, "task list capacity");
    t.expect_eq((u8*)tm->m_levelEnds, (u8*)(tm->m_taskList + tm->m_capacity), "level ends after the list");

    auto* mt = *at_vaddr<CMainTask*>(kVaddrMainTaskInstance);
    if (!t.expect_eq(mt != nullptr, true, "TSingleton<CMainTask>::m_pInstance")) return;
    t.expect_eq((u64)mt->task.link.vtable, vtable_of(t, "_ZTVN9Framework12CApplication9CMainTaskE"), "main task vtable");
    t.expect_eq(mt->task.m_owner, tm, "main task owner = system task manager");
    t.expect_eq(t.call("_ZN9Framework12CApplication9CMainTask16rRootFiberKernelEv", {(u64)mt}), (u64)mt->m_rootFiberKernel, "rRootFiberKernel");
    t.expect_eq(t.call("_ZNK9Framework12CApplication9CMainTask7rCameraEv", {(u64)mt}), (u64)mt->m_camera, "rCamera");
    t.expect_eq(t.call("_ZNK9Framework12CApplication9CMainTask20rSystemDefaultCameraEv", {(u64)mt}), (u64)mt->m_systemDefaultCamera, "rSystemDefaultCamera");
    t.expect_eq(t.call("_ZNK9Framework12CApplication9CMainTask6rFaderEv", {(u64)mt}), (u64)mt->m_fader, "rFader");
    t.expect_eq(t.call("_ZNK9Framework12CApplication9CMainTask13rSoundManagerEv", {(u64)mt}), (u64)mt->m_soundManager, "rSoundManager");
    t.expect_eq(t.call("_ZNK9Framework12CApplication9CMainTask16rResourceManagerEv", {(u64)mt}), (u64)mt->m_resourceManager, "rResourceManager");
    t.expect_eq(t.call("_ZN9Framework12CApplication9CMainTask22rResponderChainManagerEv", {(u64)mt}), (u64)mt->m_responderChainManager, "rResponderChainManager");
    t.expect_eq(t.call("_ZN9Framework12CApplication9CMainTask4rISOEv", {(u64)mt}), (u64)mt->m_iso, "rISO = &m_iso");
    t.expect_eq(t.call("_ZN9Framework12CApplication9CMainTask16pScreenPrintPoolEj", {(u64)mt, 1}),
                mt->m_screenPrintPools ? (u64)(mt->m_screenPrintPools + 0x40) : 0, "pScreenPrintPool(1)");
    u32 f1 = mt->m_frameCounter;
    u32 g = (u32)t.call("_ZNK9Framework12CApplication9CMainTask12FrameCounterEv", {(u64)mt});
    u32 f2 = mt->m_frameCounter;
    t.expect_eq(g >= f1 && g <= f2, true, "FrameCounter = m_frameCounter");

    CFiberKernel* k = mt->m_rootFiberKernel;
    if (!t.expect_eq(k != nullptr, true, "root fiber kernel")) return;
    t.expect_eq((u64)k->base.vtable, vtable_of(t, "_ZTVN9Framework12CFiberKernelE"), "root kernel vtable");
    t.expect_eq(k->base.m_priority, 0x600u, "root kernel priority (CFiberKernel(0x600))");
    t.expect_eq((u32)t.call("_ZNK9Framework12CFiberKernel16NumAttachedUnitsEv", {(u64)k}), k->m_numAttached, "NumAttachedUnits");
    // The chain changes on the main thread; check the links read in one pass.
    u32 n = 0, prio = 0;
    bool ok = true;
    for (CFiberUnit* u = k->m_units; u && n < 10000; u = u->m_next, n++) {
        if (u->m_kernel != k) ok = false;
        if (u->m_priority < prio) ok = false;
        prio = u->m_priority;
        if (u->m_next && u->m_next->m_prev != u) ok = false;
    }
    t.expect_eq(ok, true, "units: kernel = root, ascending priority, prev links");
    t.expect_eq(n > 0, true, "root kernel has units");
}

// Private fiber units under a private kernel: the constructors (handle, priority), Create (Attach by
// priority, status Activating), the accessors and status transitions, pSearchByHandle, Destroy.
NATIVE_TEST("kernel/layout-fiber") {
    alignas(16) static CFiberKernel kernel;
    alignas(16) static CFiberUnit units[3];
    std::memset(&kernel, 0xa5, sizeof kernel);
    std::memset(units, 0xa5, sizeof units);
    t.call("_ZN9Framework12CFiberKernelC2Ej", {(u64)&kernel, 0x700});
    t.expect_eq((u64)kernel.base.vtable, vtable_of(t, "_ZTVN9Framework12CFiberKernelE"), "kernel vtable");
    t.expect_eq(kernel.base.m_priority, 0x700u, "kernel priority");
    t.expect_eq(kernel.m_units, (CFiberUnit*)nullptr, "kernel: no units");
    t.expect_eq(kernel.m_numAttached, 0xa5a5a5a5u, "the constructor leaves the counts alone");
    t.call("_ZN9Framework12CFiberKernel10InitializeEv", {(u64)&kernel});
    t.expect_eq(kernel.m_numAttached, 0u, "Initialize: 0 attached");
    t.expect_eq(kernel.m_numActive, 0u, "Initialize: 0 active");
    t.expect_eq(kernel.m_unk48, (u64)0, "kernel +0x48 = 0");
    const u32 prios[3] = {30, 10, 20};
    for (int i = 0; i < 3; i++) {
        t.call("_ZN9Framework10CFiberUnitC2Ej", {(u64)&units[i], prios[i]});
        t.expect_eq((u64)units[i].vtable, vtable_of(t, "_ZTVN9Framework10CFiberUnitE"), "unit vtable");
        t.expect_eq(units[i].m_priority, prios[i], "unit priority");
        t.expect_eq((u32)t.call("_ZNK9Framework10CFiberUnit8PriorityEv", {(u64)&units[i]}), prios[i], "Priority()");
        t.expect_eq(units[i].m_status, CFiberUnit::kStatusNone, "unit status 0");
        t.expect_eq(units[i].m_kernel, (void*)nullptr, "unit no kernel");
    }
    t.expect_eq(units[1].m_handle, units[0].m_handle + 1, "handles consecutive");
    for (CFiberUnit& u : units) t.call("_ZN9Framework12CFiberKernel6CreateEPNS_10CFiberUnitE", {(u64)&kernel, (u64)&u});
    t.expect_eq(kernel.m_numAttached, 3u, "Create: attached");
    t.expect_eq((u32)t.call("_ZNK9Framework12CFiberKernel16NumAttachedUnitsEv", {(u64)&kernel}), 3u, "NumAttachedUnits");
    t.expect_eq(kernel.m_units, &units[1], "chain head: priority 10");
    t.expect_eq(units[1].m_next, &units[2], "then 20");
    t.expect_eq(units[2].m_next, &units[0], "then 30");
    t.expect_eq(units[0].m_prev, &units[2], "prev link");
    for (CFiberUnit& u : units) {
        t.expect_eq(u.m_kernel, (void*)&kernel, "Create: kernel");
        t.expect_eq(t.call("_ZNK9Framework10CFiberUnit7pKernelEv", {(u64)&u}), (u64)&kernel, "pKernel()");
        t.expect_eq(u.m_status, CFiberUnit::kStatusActivating, "Create: Activating");
        t.expect_eq((s32)t.call("_ZNK9Framework10CFiberUnit6StatusEv", {(u64)&u}), u.m_status, "Status()");
        t.expect_eq(t.call("_ZNK9Framework12CFiberKernel15pSearchByHandleEj", {(u64)&kernel, u.m_handle}), (u64)&u, "pSearchByHandle");
    }
    t.call("_ZN9Framework10CFiberUnit5GroupEj", {(u64)&units[0], 0x1234});
    t.expect_eq(units[0].m_group, 0x1234u, "Group(g)");
    t.expect_eq((u32)t.call("_ZNK9Framework10CFiberUnit5GroupEv", {(u64)&units[0]}), 0x1234u, "Group()");
    t.call("_ZN9Framework10CFiberUnit22ActivateFromActivatingEv", {(u64)&units[0]});
    t.expect_eq(units[0].m_status, CFiberUnit::kStatusActive, "ActivateFromActivating");
    t.expect_eq(t.call("_ZNK9Framework10CFiberUnit8IsActiveEv", {(u64)&units[0]}) & 0xff, (u64)1, "IsActive");
    t.call("_ZN9Framework10CFiberUnit4WaitEv", {(u64)&units[0]});
    t.expect_eq(units[0].m_status, CFiberUnit::kStatusWaiting, "Wait");
    t.call("_ZN9Framework10CFiberUnit8ActivateEv", {(u64)&units[0]});
    t.expect_eq(units[0].m_status, CFiberUnit::kStatusActivating, "Activate from Waiting");
    t.call("_ZN9Framework10CFiberUnit7DestroyEb", {(u64)&units[2], 1});
    t.expect_eq(units[2].m_status, CFiberUnit::kStatusDestroyRequested, "Destroy(true): requested");
    for (CFiberUnit& u : units) t.call("_ZN9Framework10CFiberUnit7DestroyEb", {(u64)&u, 0});
    t.expect_eq(kernel.m_numAttached, 0u, "Destroy: detached");
    t.expect_eq(kernel.m_units, (CFiberUnit*)nullptr, "Destroy: chain empty");
    t.expect_eq(units[0].m_kernel, (void*)nullptr, "Destroy: kernel cleared");
    t.expect_eq(t.call("_ZNK9Framework10CFiberUnit11IsDestroyedEv", {(u64)&units[0]}) & 0xff, (u64)1, "IsDestroyed");
    for (CFiberUnit& u : units) t.call("_ZN9Framework10CFiberUnitD2Ev", {(u64)&u});
    t.call("_ZN9Framework12CFiberKernelD2Ev", {(u64)&kernel});
}

// Private time elements: the constructor, AddChild (links), Rate / Suspend / Interpose setters, Add's
// scaled dt down the tree, the accessors.
NATIVE_TEST("kernel/layout-time-element") {
    alignas(16) static CTimeElement e[3];
    std::memset(e, 0xa5, sizeof e);
    for (CTimeElement& x : e) t.call("_ZN9Framework12CTimeElementC2Ev", {(u64)&x});
    t.expect_eq((u64)e[0].base.vtable, vtable_of(t, "_ZTVN9Framework12CTimeElementE"), "vtable");
    t.expect_eq(e[0].m_rate, 1.0f, "rate 1");
    t.expect_eq(e[0].base.m_parent, (CTimeElement*)nullptr, "no parent");
    t.expect_eq(guest_invoke<float>(t.sym("_ZNK9Framework12CTimeElement4RateEv"), (u64)&e[0]), e[0].m_rate, "Rate()");
    // e[0] is the root; e[1], e[2] its children (vtable slot 2 AddChild).
    t.call("_ZN9Framework12CTimeElement8AddChildEPS0_", {(u64)&e[0], (u64)&e[1]});
    t.call("_ZN9Framework12CTimeElement8AddChildEPS0_", {(u64)&e[0], (u64)&e[2]});
    t.expect_eq(e[0].base.m_firstChild, &e[1], "first child");
    t.expect_eq(e[1].base.m_nextSibling, &e[2], "next sibling");
    t.expect_eq(e[1].base.m_parent, &e[0], "parent");
    t.expect_eq(e[2].base.m_parent, &e[0], "parent 2");
    guest_invoke<void>(t.sym("_ZN9Framework12CTimeElement4RateEf"), (u64)&e[1], 0.5f);
    t.expect_eq(e[1].m_rate, 0.5f, "Rate(0.5)");
    guest_invoke<void>(t.sym("_ZN9Framework12CTimeElement4RateEf"), (u64)&e[2], 2.0f);
    guest_invoke<void>(t.sym("_ZN9Framework12CTimeElement3AddEf"), (u64)&e[0], 0.25f);
    t.expect_eq(e[0].m_dt, 0.25f, "root dt");
    t.expect_eq(e[1].m_dt, 0.125f, "child dt = parent's * 0.5");
    t.expect_eq(e[2].m_dt, 0.5f, "child dt = parent's * 2");
    t.expect_eq(e[1].m_time, 0.125f, "child time");
    t.expect_eq(guest_invoke<float>(t.sym("_ZNK9Framework12CTimeElement2DTEv"), (u64)&e[1]), e[1].m_dt, "DT()");
    guest_invoke<void>(t.sym("_ZN9Framework12CTimeElement7SuspendEf"), (u64)&e[2], 1.0f);
    t.expect_eq(e[2].m_suspend, 1.0f, "Suspend(1)");
    t.expect_eq(guest_invoke<float>(t.sym("_ZNK9Framework12CTimeElement7SuspendEv"), (u64)&e[2]), 1.0f, "Suspend()");
    guest_invoke<void>(t.sym("_ZN9Framework12CTimeElement9InterposeEff"), (u64)&e[1], 2.0f, 0.25f);
    t.expect_eq(e[1].m_interposeTime, 0.5f, "Interpose: time = t * rate");
    t.expect_eq(e[1].m_interposeRate, 0.25f, "Interpose: rate");
    t.expect_eq(guest_invoke<float>(t.sym("_ZNK9Framework12CTimeElement13InterposeRateEv"), (u64)&e[1]), 0.25f, "InterposeRate()");
    t.expect_eq(guest_invoke<float>(t.sym("_ZNK9Framework12CTimeElement10DetailRateEv"), (u64)&e[1]), 0.25f, "DetailRate() while interposing");
    t.call("_ZN9Framework12CTimeElement16DetachFromParentEv", {(u64)&e[2]});
    t.expect_eq(e[1].base.m_nextSibling, (CTimeElement*)nullptr, "DetachFromParent: unlinked");
    t.expect_eq(e[2].base.m_parent, (CTimeElement*)nullptr, "DetachFromParent: no parent");
    t.call("_ZN9Framework12CTimeElement16DetachFromParentEv", {(u64)&e[1]});
    for (CTimeElement& x : e) t.call("_ZN9Framework12CTimeElementD2Ev", {(u64)&x});
}

// The live PerformanceCounter (scale, GetMark) and a private one (constructor, Mark / Set / GetMark).
NATIVE_TEST("kernel/layout-performance-counter") {
    auto* live = *at_vaddr<PerformanceCounter*>(kVaddrGlobalPerformanceCounter);
    if (t.expect_eq(live != nullptr, true, "Global::m_pPerformanceCounter")) {
        t.expect_eq((u64)live->vtable, vtable_of(t, "_ZTVN4Aska18PerformanceCounterE"), "live vtable");
        t.expect_eq(live->m_scale, 0.001, "live scale");
        t.expect_eq(live->m_baseTime > 0, true, "live base time");
    }
    alignas(16) static PerformanceCounter pc;
    std::memset(&pc, 0xa5, sizeof pc);
    t.call("_ZN4Aska18PerformanceCounterC2Ev", {(u64)&pc});
    t.expect_eq((u64)pc.vtable, vtable_of(t, "_ZTVN4Aska18PerformanceCounterE"), "vtable");
    t.expect_eq(pc.m_scale, 0.001, "scale 0.001");
    t.expect_eq(pc.m_marks[47], (s64)0, "marks cleared");
    t.expect_eq(pc.m_values[47], 0, "values cleared");
    t.expect_eq(pc.m_baseTime > 0, true, "base time = now");
    t.call("_ZN4Aska18PerformanceCounter4MarkEi", {(u64)&pc, 5});
    t.expect_eq(pc.m_marks[5] >= pc.m_baseTime, true, "Mark(5) = now");
    t.expect_eq((s64)t.call("_ZNK4Aska18PerformanceCounter7GetMarkEi", {(u64)&pc, 5}), pc.m_marks[5], "GetMark(5)");
    pc.m_marks[6] = pc.m_marks[5] - 3000000;  // 3 ms earlier
    t.call("_ZN4Aska18PerformanceCounter3SetEi", {(u64)&pc, 6});
    t.expect_eq(pc.m_values[6] >= 3000, true, "Set(6) = elapsed us");
    t.expect_eq(pc.m_values[5], 0, "Set(6) wrote only value 6");
}

// The live VSync, read-only: vtables (IVSync at 0, NotifierThread at 8), GetBasicFrameRate,
// GetDt(i) = m_dt[i] * m_dtScale, the notifier's pool.
NATIVE_TEST("kernel/layout-live-vsync") {
    auto* v = *at_vaddr<VSync*>(kVaddrGlobalVSync);
    if (!t.expect_eq(v != nullptr, true, "Global::m_pVSync")) return;
    u64 vt = t.sym("_ZTVN4Aska5VSyncE");
    t.expect_eq((u64)v->vtable, vt + 0x10, "vtable");
    t.expect_eq((u64)v->m_notifier.base.vtable, vt + 0x50, "NotifierThread vtable (+0x50)");
    t.expect_eq((u32)t.call("_ZNK4Aska5VSync17GetBasicFrameRateEv", {(u64)v}), v->m_basicFrameRate, "GetBasicFrameRate");
    t.expect_eq(v->m_basicFrameRate, 60u, "60 fps");
    t.expect_eq(v->m_dtScale, 1.0f, "dt scale 1");
    u32 c0 = *at_vaddr<volatile u32>(kVaddrVSyncCounter);
    u32 cg = (u32)t.call("_ZNK4Aska5VSync15GetVSyncCounterEv", {(u64)v});
    u32 c1 = *at_vaddr<volatile u32>(kVaddrVSyncCounter);
    t.expect_eq(cg - c0 <= c1 - c0, true, "GetVSyncCounter = VSync::m_nVSyncCounter");
    bool dt_ok = false;  // the render thread updates m_dt; retry until a read pair agrees
    for (int i = 0; i < 50 && !dt_ok; i++) {
        float a = v->m_dt[0] * v->m_dtScale;
        float g = guest_invoke<float>(t.sym("_ZNK4Aska5VSync5GetDtEi"), (u64)v, 0);
        float b = v->m_dt[0] * v->m_dtScale;
        dt_ok = (g == a || g == b);
    }
    t.expect_eq(dt_ok, true, "GetDt(0) = m_dt[0] * m_dtScale");
    t.expect_eq(guest_invoke<float>(t.sym("_ZNK4Aska5VSync5GetDtEi"), (u64)v, 6), 0.0f, "GetDt(6) = 0 (6 clocks)");
    NotifierThread& n = v->m_notifier;
    t.expect_eq((u64)n.m_list.vtable, vtable_of(t, "_ZTVN4Aska4ListE"), "notifier list vtable");
    t.expect_eq((u64)n.m_pool.vtable, vtable_of(t, "_ZTVN4Aska9TPoolFastINS_14NotifierThread13NotifyElementELb0EEE"), "notifier pool vtable");
    t.expect_eq(n.m_pool.m_pool != nullptr, true, "notifier pool storage");
    t.expect_eq(n.m_pool.m_count <= n.m_pool.m_used.m_numBits, true, "pool count <= capacity");
}

// A private NotifierThread (no thread started): the constructor, AddNotify's pooled element in the
// list, QueryNotify, RemoveNotify.
NATIVE_TEST("kernel/layout-notifier-thread") {
    alignas(16) static NotifierThread n;
    std::memset(&n, 0, sizeof n);
    t.call("_ZN4Aska14NotifierThreadC2Ei", {(u64)&n, 8});
    t.expect_eq((u64)n.base.vtable, vtable_of(t, "_ZTVN4Aska14NotifierThreadE"), "vtable");
    t.expect_eq(n.m_list.m_sentinel.m_next, &n.m_list.m_sentinel, "empty list");
    t.expect_eq(n.m_list.m_count, 0, "list count 0");
    t.expect_eq(n.m_pool.m_used.m_numBits, 8u, "pool capacity 8");
    t.expect_eq(n.m_pool.m_count, 0u, "pool count 0");
    t.call("_ZN4Aska14NotifierThread9AddNotifyEPNS_7INotifyEj", {(u64)&n, 0x7770000, 3});
    t.expect_eq(n.m_list.m_count, 1, "AddNotify: list count");
    t.expect_eq(n.m_pool.m_count, 1u, "AddNotify: pool count");
    auto* el = reinterpret_cast<NotifyElement*>(n.m_list.m_sentinel.m_prev);
    t.expect_eq(el, &n.m_pool.m_pool[0], "AddNotify: element = pool slot 0");
    t.expect_eq((u64)el->m_notify, (u64)0x7770000, "element notify");
    t.expect_eq(el->m_count, 3u, "element count");
    t.expect_eq(el->link.m_next, &n.m_list.m_sentinel, "element -> sentinel");
    t.expect_eq(t.call("_ZN4Aska14NotifierThread11QueryNotifyEPNS_7INotifyE", {(u64)&n, 0x7770000}) & 0xff, (u64)1, "QueryNotify");
    t.call("_ZN4Aska14NotifierThread12RemoveNotifyEPNS_7INotifyE", {(u64)&n, 0x7770000});
    t.expect_eq(n.m_list.m_count, 0, "RemoveNotify: list count");
    // No destructor: ~NotifierThread posts an ExitNotify and Thread::WaitEnd()s a thread this test never
    // started. The two semaphores and the pool's storage stay allocated (once per run).
}
