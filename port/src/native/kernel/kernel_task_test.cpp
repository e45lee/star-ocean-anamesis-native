// Differential tests of the TaskManager natives (kernel_task.cpp): private managers built by the
// guest's constructor, one set driven by the guest functions (natives aren't installed in
// --selftest), the other by the native members, compared after every step.
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "native/common/test.h"
#include "native/kernel/kernel_layout.h"

using namespace soa;
using namespace soa::native::kernel;

namespace {

std::string barriers(const TaskManager* m) {
    std::string o;
    char b[64];
    snprintf(b, sizeof b, "created %#x pending %#x", m->m_barrierCreated, m->m_barrierPending);
    o += b;
    for (int k = 0; k < TaskManager::kNumLevels; k++) {
        snprintf(b, sizeof b, " %d:%d/%d/%u", k, m->m_barrierRefs[k], m->m_barrierCounts[k], m->m_barrierEvents[k].m_signaled);
        o += b;
    }
    return o;
}

struct Managers {
    static constexpr int kManagers = 3, kTasks = 24;
    alignas(16) u8 storage[kManagers][sizeof(TaskManager)];
    alignas(16) Task tasks[kTasks];
    TaskManager* m(int i) { return reinterpret_cast<TaskManager*>(storage[i]); }
    void build(TestContext& t) {
        for (int i = 0; i < kManagers; i++) {
            std::memset(storage[i], 0, sizeof storage[i]);
            t.call("_ZN4Aska11TaskManagerC2Ev", {(u64)m(i)});
        }
        std::memset(tasks, 0, sizeof tasks);
        for (Task& k : tasks) k.link.vtable = (const void*)(t.sym("_ZTVN4Aska4TaskE") + 0x10);
    }
    void destroy(TestContext& t) {
        for (int i = 0; i < kManagers; i++) t.call("_ZN4Aska11TaskManagerD2Ev", {(u64)m(i)});
    }
    std::string list(TaskManager* x) {  // MakeTaskList's output, tasks as indices
        std::string o;
        for (int k = 0; k <= TaskManager::kNumLevels; k++) {
            Task** e = x->m_levelEnds[k];
            o += e ? std::to_string(e - x->m_taskList) + " " : "null ";
        }
        Task** end = x->m_taskList;
        for (int k = 0; k < TaskManager::kNumLevels; k++)
            if (x->m_levelEnds[k] > end) end = x->m_levelEnds[k];
        o += "|";
        for (Task** p = x->m_taskList; p < end; p++) o += " " + std::to_string(*p - tasks);
        return o;
    }
};

}  // namespace

// The thread barriers: random Add / Delete / Increment / Decrement on 4 levels (counts going below
// zero and refs capping the count included).
NATIVE_TEST("kernel/task-barriers") {
    static Managers g, n;
    g.build(t);
    n.build(t);
    int steps = 0;
    for (; steps < 2000; steps++) {
        int op = t.rand_int(0, 3), i = t.rand_int(0, 3) * 7;
        const char* names[4] = {"_ZN4Aska11TaskManager16AddThreadBarrierEi", "_ZN4Aska11TaskManager19DeleteThreadBarrierEi",
                                "_ZN4Aska11TaskManager27IncrementThreadBarrierCountEi", "_ZN4Aska11TaskManager27DecrementThreadBarrierCountEi"};
        t.call(names[op], {(u64)g.m(0), (u64)i});
        switch (op) {
        case 0: n.m(0)->AddThreadBarrier(i); break;
        case 1: n.m(0)->DeleteThreadBarrier(i); break;
        case 2: n.m(0)->IncrementThreadBarrierCount(i); break;
        default: n.m(0)->DecrementThreadBarrierCount(i); break;
        }
        if (!t.expect_eq(barriers(g.m(0)), barriers(n.m(0)), names[op])) break;
    }
    t.expect_eq(steps, 2000, "steps run");
    g.destroy(t);
    n.destroy(t);
}

// MakeTaskList / GetTotalTaskNumber over a merged ring of three managers: tasks with random level
// masks added (the guest's Add on both sides), some deleted, the list made by the guest on one side
// and natively on the other, for every manager of the ring (each makes the ring's whole list).
NATIVE_TEST("kernel/task-list") {
    static Managers g, n;
    g.build(t);
    n.build(t);
    for (Managers* s : {&g, &n}) {
        t.call("_ZN4Aska11TaskManager12MergeManagerEPS0_", {(u64)s->m(0), (u64)s->m(1)});
        t.call("_ZN4Aska11TaskManager12MergeManagerEPS0_", {(u64)s->m(0), (u64)s->m(2)});
    }
    t.expect_eq(g.m(1)->m_ringHead, g.m(0), "merged: ring head");
    std::vector<int> owner(Managers::kTasks, -1);
    int longest = 0;
    for (int round = 0; round < 40; round++) {
        int k = t.rand_int(0, Managers::kTasks - 1);
        if (owner[k] < 0) {
            int mi = t.rand_int(0, 2);
            u32 level = t.rand_int(0, 3) ? (u32)(t.rand_u64() & (t.rand_int(0, 1) ? 0x7u : 0x80000013u)) : 0;
            for (Managers* s : {&g, &n}) t.call("_ZN4Aska11TaskManager3AddEPNS_4TaskEj", {(u64)s->m(mi), (u64)&s->tasks[k], level});
            owner[k] = mi;
        } else if (t.rand_int(0, 2) == 0) {
            for (Managers* s : {&g, &n}) t.call("_ZN4Aska11TaskManager6DeleteEPNS_4TaskE", {(u64)s->m(owner[k]), (u64)&s->tasks[k]});
            owner[k] = -1;
        }
        int mi = t.rand_int(0, 2);
        s32 tg = (s32)t.call("_ZNK4Aska11TaskManager18GetTotalTaskNumberEv", {(u64)g.m(mi)});
        s32 tn = n.m(mi)->GetTotalTaskNumber();
        if (!t.expect_eq(tg, tn, "GetTotalTaskNumber")) break;
        for (Managers* s : {&g, &n})
            if (s->m(mi)->m_capacity < tg) t.call("_ZN4Aska11TaskManager19PreAllocateTaskListEi", {(u64)s->m(mi), (u64)(tg + 4)});
        if (!g.m(mi)->m_taskList) continue;
        t.call("_ZN4Aska11TaskManager12MakeTaskListEv", {(u64)g.m(mi)});
        n.m(mi)->MakeTaskList();
        if (!t.expect_eq(g.list(g.m(mi)), n.list(n.m(mi)), "MakeTaskList")) break;
        longest = std::max(longest, (int)tg);
        // every lock of the ring released
        for (int i = 0; i < 3; i++) t.expect_eq(n.m(i)->m_cs.m_lock, FastCriticalSection::kFree, "ring lock released");
    }
    t.expect_eq(longest > 10, true, "lists of some length made");
    for (Managers* s : {&g, &n})
        for (int k = 0; k < Managers::kTasks; k++)
            if (owner[k] >= 0) t.call("_ZN4Aska11TaskManager6DeleteEPNS_4TaskE", {(u64)s->m(owner[k]), (u64)&s->tasks[k]});
    g.destroy(t);
    n.destroy(t);
}
