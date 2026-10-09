// The live check of the TaskManager natives (kernel_task.cpp) and their hooks.
//
// The thread barriers are stateful under m_barrierCs: checked as the dispatcher's are (kernel_check.h,
// common/shadow_check.h). The native records the manager as it found it under the lock (and, for
// IncrementThreadBarrierCount, the reference count it read before taking it) and as it left it;
// the guest original then runs on this thread's shadow manager (a CriticalSection and 32 events of
// its own, the barrier arrays and the events' flags copied) and the barrier state after must match.
// GetTotalTaskNumber is a getter (common/shadow_check.h check_getter). MakeTaskList only writes
// m_taskList and m_levelEnds: the guest original runs again on the real manager after the native
// (it takes the ring's locks itself) and must produce the same list; a difference a second run of
// both doesn't reproduce is a race (a task added or removed in between).
#include <cinttypes>
#include <cstring>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "native/common/native_method.h"
#include "native/kernel/kernel_check.h"

namespace soa::native::kernel {

thread_local TaskObservation* t_tobs = nullptr;

void TaskObservation::capture_pre(const TaskManager* m) {
    std::memcpy(pre, (const void*)m, sizeof pre);
    have_pre = true;
}
void TaskObservation::capture_post(const TaskManager* m) {
    std::memcpy(post, (const void*)m, sizeof post);
    have_post = true;
}

namespace {

// The shadow manager: its own recursive mutex and events, made once per thread (on the heap:
// live::thread_scratch, not static TLS).
TaskManager* shadow_manager() {
    struct Shadow {
        alignas(16) u8 buf[sizeof(TaskManager)];
        bool made = false;
    };
    Shadow& sh = live::thread_scratch<Shadow>();
    auto* m = reinterpret_cast<TaskManager*>(sh.buf);
    if (!sh.made) {
        std::memset(sh.buf, 0, sizeof sh.buf);
        m->m_barrierCs.CtorBase();
        for (Event& e : m->m_barrierEvents) {
            e.Ctor();
            e.Create(true, false);
        }
        sh.made = true;
    }
    return m;
}

// The barrier state of a manager's bytes: the masks, refs, counts and the events' flags.
std::string barrier_state(const TaskManager* m) {
    std::string o;
    char b[64];
    snprintf(b, sizeof b, "created %#x pending %#x", m->m_barrierCreated, m->m_barrierPending);
    o += b;
    for (int k = 0; k < TaskManager::kNumLevels; k++) {
        snprintf(b, sizeof b, " %d:%d/%d/%u%u", k, m->m_barrierRefs[k], m->m_barrierCounts[k], m->m_barrierEvents[k].m_signaled,
                 m->m_barrierEvents[k].m_manualReset);
        o += b;
    }
    return o;
}

void barrier_checked(Cpu& c, CheckedFn& f, HostFn native) {
    live::CheckScope scope;
    u64 x0 = c.x(0), x1 = c.x(1);
    TaskObservation obs;
    t_tobs = &obs;
    native(c);
    t_tobs = nullptr;
    if (!obs.have_pre || !obs.have_post) return check_result(f, live::Outcome::Skipped, "no observation");
    auto* pre = reinterpret_cast<const TaskManager*>(obs.pre);
    TaskManager* sh = shadow_manager();
    sh->m_barrierCreated = pre->m_barrierCreated;
    sh->m_barrierPending = pre->m_barrierPending;
    std::memcpy(sh->m_barrierRefs, pre->m_barrierRefs, sizeof sh->m_barrierRefs);
    std::memcpy(sh->m_barrierCounts, pre->m_barrierCounts, sizeof sh->m_barrierCounts);
    if (obs.refs_read >= 0 && (u32)x1 < 32) sh->m_barrierRefs[x1] = obs.refs_read;  // (Increment: as read before the lock)
    for (int k = 0; k < TaskManager::kNumLevels; k++) {
        Event& e = sh->m_barrierEvents[k];
        if (!pre->m_barrierEvents[k].m_pMutex && e.m_pMutex) e.Exit();  // (not created yet: the guest's AddThreadBarrier creates it)
        if (pre->m_barrierEvents[k].m_pMutex && !e.m_pMutex) e.Create(true, false);
        e.m_signaled = pre->m_barrierEvents[k].m_signaled;
        e.m_manualReset = pre->m_barrierEvents[k].m_manualReset;
    }
    guest_call(f.orig, {(u64)sh, x1});
    if (obs.refs_read >= 0 && (u32)x1 < 32) sh->m_barrierRefs[x1] = reinterpret_cast<const TaskManager*>(obs.post)->m_barrierRefs[x1];
    std::string want = barrier_state(reinterpret_cast<const TaskManager*>(obs.post)), got = barrier_state(sh);
    (void)x0;
    if (want == got) return check_result(f, live::Outcome::Ok);
    check_result(f, live::Outcome::Mismatch, "barrier " + std::to_string((s32)x1) + ": native " + want + " | guest " + got);
}

CheckedFn g_add("_ZN4Aska11TaskManager16AddThreadBarrierEi"), g_del("_ZN4Aska11TaskManager19DeleteThreadBarrierEi"),
    g_inc("_ZN4Aska11TaskManager27IncrementThreadBarrierCountEi"), g_dec("_ZN4Aska11TaskManager27DecrementThreadBarrierCountEi"),
    g_total("_ZNK4Aska11TaskManager18GetTotalTaskNumberEv"), g_make("_ZN4Aska11TaskManager12MakeTaskListEv");

template <auto M, CheckedFn* F>
void barrier_hook(Cpu& c) {
    if (!live::check_due(*F)) return wrap_method<M>()(c);
    barrier_checked(c, *F, wrap_method<M>());
}

void total_hook(Cpu& c) {
    if (!live::check_due(g_total)) return wrap_method<&TaskManager::GetTotalTaskNumber>()(c);
    live::check_getter(c, g_total, wrap_method<&TaskManager::GetTotalTaskNumber>(), 0xffffffffu);
}

// The list MakeTaskList made: each level's end (as an index) and the tasks up to the last end.
std::vector<u64> task_list(const TaskManager* m) {
    std::vector<u64> v;
    if (!m->m_levelEnds || !m->m_taskList) return v;
    s64 end = 0;
    for (int k = 0; k < TaskManager::kNumLevels; k++) {
        s64 e = m->m_levelEnds[k] - m->m_taskList;
        v.push_back((u64)e);
        if (e > end) end = e;
    }
    v.push_back((u64)m->m_levelEnds[TaskManager::kNumLevels]);
    for (s64 i = 0; i < end && i < 1 << 16; i++) v.push_back((u64)m->m_taskList[i]);
    return v;
}

void make_hook(Cpu& c) {
    if (!live::check_due(g_make)) return wrap_method<&TaskManager::MakeTaskList>()(c);
    live::CheckScope scope;
    auto* m = reinterpret_cast<TaskManager*>(c.x(0));
    for (int attempt = 0; attempt < 2; attempt++) {
        wrap_method<&TaskManager::MakeTaskList>()(c);
        std::vector<u64> native = task_list(m);
        guest_call(g_make.orig, {(u64)m});
        std::vector<u64> guest = task_list(m);
        if (native == guest) return check_result(g_make, attempt ? live::Outcome::Race : live::Outcome::Ok);
        if (attempt) {
            size_t i = 0;
            while (i < native.size() && i < guest.size() && native[i] == guest[i]) i++;
            char b[128];
            snprintf(b, sizeof b, "entry %zu: native %#" PRIx64 " guest %#" PRIx64 " (sizes %zu / %zu)", i, i < native.size() ? native[i] : 0,
                     i < guest.size() ? guest[i] : 0, native.size(), guest.size());
            check_result(g_make, live::Outcome::Mismatch, b);
        }
    }
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska11TaskManager16AddThreadBarrierEi", (barrier_hook<&TaskManager::AddThreadBarrier, &g_add>),
                     "kernel: TaskManager::AddThreadBarrier", &g_add.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska11TaskManager19DeleteThreadBarrierEi", (barrier_hook<&TaskManager::DeleteThreadBarrier, &g_del>),
                     "kernel: TaskManager::DeleteThreadBarrier", &g_del.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska11TaskManager27IncrementThreadBarrierCountEi", (barrier_hook<&TaskManager::IncrementThreadBarrierCount, &g_inc>),
                     "kernel: TaskManager::IncrementThreadBarrierCount", &g_inc.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska11TaskManager27DecrementThreadBarrierCountEi", (barrier_hook<&TaskManager::DecrementThreadBarrierCount, &g_dec>),
                     "kernel: TaskManager::DecrementThreadBarrierCount", &g_dec.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska11TaskManager18GetTotalTaskNumberEv", total_hook, "kernel: TaskManager::GetTotalTaskNumber", &g_total.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska11TaskManager12MakeTaskListEv", make_hook, "kernel: TaskManager::MakeTaskList", &g_make.orig);

}  // namespace soa::native::kernel
