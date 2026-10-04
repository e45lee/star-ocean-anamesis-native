// Aska::TaskManager: the frame's task list and its thread barriers (port/decomp/kernel/task.c).
//
// The barriers are the dispatcher's (Task*, barrier) jobs of one level: posting one adds a
// reference and counts the job (Add / IncrementThreadBarrierCount, under the dispatcher's lock);
// the worker that ran it counts it off and drops the reference (Decrement / DeleteThreadBarrier,
// from the guest's _WorkerThread::Handler); OwnersKickTask waits on the level's event at the level
// boundary while jobs are left. All under m_barrierCs (a recursive pthread mutex: sync's
// CriticalSection). MakeTaskList / GetTotalTaskNumber run under the FastCriticalSection m_cs of every
// manager of the merged ring (guest code still takes those too: Add / Delete / ChangeLevel).
#include "core/cpu.h"
#include "native/common/native_method.h"
#include "native/kernel/kernel_check.h"
#include "native/kernel/kernel_layout.h"

namespace soa::native::kernel {

namespace {
inline void fence() { __atomic_thread_fence(__ATOMIC_SEQ_CST); }
inline void observe_pre(const TaskManager* m) {
    if (__builtin_expect(t_tobs != nullptr, 0)) t_tobs->capture_pre(m);
}
inline void observe_post(const TaskManager* m) {
    if (__builtin_expect(t_tobs != nullptr, 0)) t_tobs->capture_post(m);
}
}  // namespace

// ---- thread barriers ----

void TaskManager::AddThreadBarrier(s32 i) {
    m_barrierCs.Enter();
    observe_pre(this);
    const u32 bit = 1u << (i & 31);
    if (!(m_barrierCreated & bit) && m_barrierEvents[i].Create(true, false)) m_barrierCreated |= bit;
    s32 refs = m_barrierRefs[i];
    if (refs == 0) {
        // The first reference: the level's event is reset (unless it already is).
        if (!(m_barrierPending & bit)) {
            m_barrierEvents[i].Reset();
            m_barrierPending |= bit;
            refs = m_barrierRefs[i];
        } else {
            refs = 0;
        }
    }
    m_barrierRefs[i] = refs + 1;
    observe_post(this);
    m_barrierCs.Leave();
}

void TaskManager::DeleteThreadBarrier(s32 i) {
    m_barrierCs.Enter();
    observe_pre(this);
    if ((m_barrierCreated & (1u << (i & 31))) && m_barrierRefs[i] > 0) m_barrierRefs[i]--;
    observe_post(this);
    m_barrierCs.Leave();
}

// Quirk kept: the count is capped at the reference count read before taking the lock.
void TaskManager::IncrementThreadBarrierCount(s32 i) {
    const u32 bit = 1u << (i & 31);
    if (!(m_barrierCreated & bit)) {
        observe_pre(this);
        observe_post(this);
        return;
    }
    s32 refs = m_barrierRefs[i];
    if (t_tobs) t_tobs->refs_read = refs;
    m_barrierCs.Enter();
    observe_pre(this);
    s32 count = m_barrierCounts[i] < refs ? m_barrierCounts[i] + 1 : refs;
    m_barrierCounts[i] = count;
    if (count > 0 && !(m_barrierPending & bit)) {
        m_barrierEvents[i].Reset();
        m_barrierPending |= bit;
    }
    observe_post(this);
    m_barrierCs.Leave();
}

void TaskManager::DecrementThreadBarrierCount(s32 i) {
    m_barrierCs.Enter();
    observe_pre(this);
    s32 count = --m_barrierCounts[i];
    if (count == 0) {
        const u32 bit = 1u << (i & 31);
        if (m_barrierPending & bit) {
            m_barrierEvents[i].Set();
            m_barrierPending &= ~bit;
        }
    }
    observe_post(this);
    m_barrierCs.Leave();
}

// ---- the task list ----

// The number of task levels over the merged ring (each task counts once per set level bit).
s32 TaskManager::GetTotalTaskNumber() const {
    auto& cs = const_cast<FastCriticalSection&>(m_cs);
    cs.Enter();
    fence();
    s32 n = 0;
    const TaskManager* m = this;
    do {
        n += m->m_totalCount;
        m = m->m_ringNext;
    } while (m != this);
    fence();
    cs.Leave();
    return n;
}

// Every task of the merged ring into m_taskList, grouped by level (a counting sort over the ring's
// m_levelCount: a task with several level bits is listed once per level), and m_levelEnds[k] = the
// end of level k's run (m_levelEnds[32] = null). Holds every ring manager's m_cs meanwhile, taken
// from the ring head on and released from the head's successor on, the head last.
void TaskManager::MakeTaskList() {
    TaskManager* head = m_ringHead;
    head->m_cs.Enter();
    fence();
    for (TaskManager* m = head->m_ringNext; m != m_ringHead; m = m->m_ringNext) {
        m->m_cs.Enter();
        fence();
    }
    head = m_ringHead;
    s32 count[kNumLevels] = {};
    TaskManager* m = head;
    do {
        for (int k = 0; k < kNumLevels; k++) count[k] += m->m_levelCount[k];
        m = m->m_ringNext;
    } while (m != head);
    s32 start[kNumLevels];
    s32 sum = 0;
    for (int k = 0; k < kNumLevels; k++) {
        start[k] = sum;
        sum += count[k];
    }
    m = head;
    do {
        LinkElement* sentinel = &m->m_sentinel;
        for (LinkElement* l = sentinel->m_next; l != sentinel; l = l->m_next) {
            Task* t = reinterpret_cast<Task*>(l);
            u32 bits = t->m_level;
            for (int k = 0; bits; bits >>= 1, k++)
                if (bits & 1) m_taskList[start[k]++] = t;
        }
        m = m->m_ringNext;
    } while (m != m_ringHead);
    for (int k = 0; k < kNumLevels; k++) m_levelEnds[k] = m_taskList + start[k];
    m_levelEnds[kNumLevels] = nullptr;
    for (TaskManager* r = m_ringHead->m_ringNext; r != m_ringHead; r = r->m_ringNext) {
        fence();
        r->m_cs.Leave();
    }
    fence();
    m_ringHead->m_cs.Leave();
}

}  // namespace soa::native::kernel
