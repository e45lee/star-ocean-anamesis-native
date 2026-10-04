// memory_lock.h: Aska::FastCriticalSection's enter / leave as the heap code inlines them, over the
// guest's own lock words, for the memory natives.
//
// MemoryManager::Malloc / LocalFree / CalcFreeSize / IsCreated (and Realloc, Split, DeleteManager, which
// stay guest code) inline the same enter / leave on the FastCriticalSection at MemoryManager::m_cs
// (port/decomp/memory/memory_manager.c). The guest layout is the state: lock word +0x38 (-1 free, 0
// held), waiter count +0x3c (biased by 20), Aska::Semaphore +0x78. The JIT's exclusive store is a host
// compare-and-swap on the word (runtime/src/core/cpu.cpp, fastmem_exclusive_access), so these host
// atomics and guest code entering the same section exclude each other.
//
// `sync` owns the class (port/src/native/sync, n-sync: sync::FastCriticalSection::Enter / Leave, the
// same algorithm); this file is the memory subsystem's stand-in until both are on main, then the
// heap natives call sync's members and this file goes.
#ifndef SOA_NATIVE_MEMORY_LOCK_H
#define SOA_NATIVE_MEMORY_LOCK_H

#include "native/memory/memory_layout.h"

namespace soa::native::memory {

class FastLock {
public:
    static constexpr u64 kLockWord = 0x38, kWaiters = 0x3c, kSemaphore = 0x78;
    static constexpr s32 kFree = -1, kHeld = 0, kWaiterBias = 20, kSpins = 0x200;

    // The guest's inlined enter: 0x200 probes of the lock word, then counted in the waiters while
    // blocked on the semaphore (or sleeping 1 ms when it isn't ready), retrying when woken.
    static void Enter(u8* cs);
    // The guest's inlined leave: the word to -1, then one wakeup handed to the semaphore when more
    // than the bias are waiting.
    static void Leave(u8* cs);
    // True when the word reads held (the live check's sanity test; racy by nature).
    static bool IsHeld(const u8* cs) { return __atomic_load_n(word(const_cast<u8*>(cs)), __ATOMIC_ACQUIRE) != kFree; }

private:
    static s32* word(u8* cs) { return reinterpret_cast<s32*>(cs + kLockWord); }
    static s32* waiters(u8* cs) { return reinterpret_cast<s32*>(cs + kWaiters); }
};

// Holds a FastCriticalSection for a scope.
class FastLockGuard {
public:
    explicit FastLockGuard(u8* cs) : cs_(cs) { FastLock::Enter(cs_); }
    ~FastLockGuard() { FastLock::Leave(cs_); }
    FastLockGuard(const FastLockGuard&) = delete;
    FastLockGuard& operator=(const FastLockGuard&) = delete;

private:
    u8* cs_;
};

}  // namespace soa::native::memory

#endif  // SOA_NATIVE_MEMORY_LOCK_H
