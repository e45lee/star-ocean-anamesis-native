// memory_lock.cpp: the FastCriticalSection enter / leave the heap natives use (memory_lock.h).
#include "native/memory/memory_lock.h"

#include "core/cpu.h"
#include "native/common/guest_std.h"

namespace soa::native::memory {

namespace {
// The embedded Aska::Semaphore's methods and Thread::Sleep stay the guest's (sync's natives once
// installed: guest_call then calls them directly).
struct SyncCalls {
    u64 isReady = guest::sym("_ZNK4Aska9Semaphore7IsReadyEv");
    u64 wait = guest::sym("_ZNK4Aska9Semaphore4WaitEv");
    u64 signal = guest::sym("_ZNK4Aska9Semaphore6SignalEv");
    u64 sleep = guest::sym("_ZN4Aska6Thread5SleepEj");
};
const SyncCalls& calls() {
    static const SyncCalls c;
    return c;
}
bool sem_ready(u8* cs) { return guest_call(calls().isReady, {(u64)(cs + FastLock::kSemaphore)}) & 1; }

inline bool try_take(s32* w) {
    s32 expected = FastLock::kFree;
    return __atomic_load_n(w, __ATOMIC_RELAXED) == FastLock::kFree &&
           __atomic_compare_exchange_n(w, &expected, FastLock::kHeld, false, __ATOMIC_ACQUIRE, __ATOMIC_RELAXED);
}
}  // namespace

void FastLock::Enter(u8* cs) {
    s32* w = word(cs);
    // Spin: 0x200 probes (a lost store-exclusive retries without counting, as the guest's LDAXR / STLXR loop).
    for (int i = 0; i < kSpins; i++) {
        if (try_take(w)) {
            __atomic_thread_fence(__ATOMIC_SEQ_CST);  // the guest's dmb ish after the acquire
            return;
        }
    }
    // Wait: counted in the waiters while blocked.
    s32* n = waiters(cs);
    __atomic_fetch_add(n, 1, __ATOMIC_ACQ_REL);
    while (!try_take(w)) {
        do {
            if (sem_ready(cs)) {
                guest_call(calls().wait, {(u64)(cs + kSemaphore)});
            } else {
                __atomic_fetch_sub(n, 1, __ATOMIC_ACQ_REL);
                guest_call(calls().sleep, {1});
            }
            __atomic_fetch_add(n, 1, __ATOMIC_ACQ_REL);
        } while (__atomic_load_n(w, __ATOMIC_ACQUIRE) != kFree);
    }
    __atomic_fetch_sub(n, 1, __ATOMIC_ACQ_REL);
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
}

void FastLock::Leave(u8* cs) {
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    __atomic_store_n(word(cs), kFree, __ATOMIC_RELEASE);
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    s32* n = waiters(cs);
    if (__atomic_load_n(n, __ATOMIC_RELAXED) > kWaiterBias) {  // (a plain load in the guest)
        __atomic_fetch_sub(n, 1, __ATOMIC_ACQ_REL);
        if (sem_ready(cs)) guest_call(calls().signal, {(u64)(cs + kSemaphore)});
    }
}

}  // namespace soa::native::memory
