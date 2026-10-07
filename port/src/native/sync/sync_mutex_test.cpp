// Differential tests of Framework::CMutex / Aska::FastCriticalSection (sync_mutex.cpp) against the
// 3.7.0 guest: the same call sequences on a guest-run and a native-run object, compared byte for
// byte after every step; guest and native threads locking one mutex together.
#include <algorithm>
#include <atomic>
#include <thread>
#include <chrono>
#include <cstring>

#include "core/loader.h"
#include "hle/thread.h"
#include "native/common/test.h"
#include "native/common/gen/common_addresses.h"
#include "native/sync/gen/sync_addresses.h"
#include "native/sync/sync_layout.h"
#include "native/sync/sync_test_util.h"

namespace soa::native::sync {
namespace {

constexpr size_t kSemPtr = offsetof(CMutex, m_substance) + offsetof(FastCriticalSection, m_sem) + offsetof(Semaphore, m_pSem);

const char* kCtor = "_ZN9Framework6CMutexC1Ev";
const char* kInit = "_ZN9Framework6CMutex10InitializeEv";
const char* kLock = "_ZN9Framework6CMutex4LockEv";
const char* kUnlock = "_ZN9Framework6CMutex6UnlockEv";
const char* kRelease = "_ZN9Framework6CMutex7ReleaseEv";
const char* kDtor = "_ZN9Framework6CMutexD1Ev";

bool same(TestContext& t, CMutex* g, CMutex* n, const char* step) {
    auto a = test::normalized(g, {kSemPtr}), b = test::normalized(n, {kSemPtr});
    for (size_t i = 0; i < a.size(); i++)
        if (a[i] != b[i]) {
            t.fail("%s: +0x%zx guest %02x native %02x", step, i, a[i], b[i]);
            return false;
        }
    return true;
}

NATIVE_TEST("sync/cmutex-sequence") {
    test::GuestObj<CMutex> g, n;
    std::memset(g.raw, 0xa5, sizeof g.raw);  // (unknown bytes: leftovers both leave alone)
    std::memset(n.raw, 0xa5, sizeof n.raw);
    t.call(kCtor, {g.addr()});
    n->Ctor();
    same(t, g.get(), n.get(), "ctor");
    t.expect_eq((u8)t.call("_ZNK9Framework6CMutex13IsInitializedEv", {g.addr()}), (u8)n->IsInitialized(), "IsInitialized (before)");
    t.call(kInit, {g.addr()});
    n->Initialize();
    same(t, g.get(), n.get(), "Initialize");
    t.expect_eq((u64)t.call("_ZN9Framework6CMutex10rSubstanceEv", {g.addr()}) - g.addr(), (u64)n->rSubstance() - n.addr(), "rSubstance");
    t.expect_eq((u64)t.call("_ZNK9Framework6CMutex11crSubstanceEv", {g.addr()}) - g.addr(), (u64)n->crSubstance() - n.addr(), "crSubstance");
    // Lock, recursive locks, the getters, unlocks down to free.
    for (int depth = 1; depth <= 3; depth++) {
        t.call(kLock, {g.addr()});
        n->Lock();
        char step[32];
        snprintf(step, sizeof step, "Lock %d", depth);
        same(t, g.get(), n.get(), step);
        t.expect_eq((u8)t.call("_ZNK9Framework6CMutex8IsLockedEv", {g.addr()}), (u8)n->IsLocked(), "IsLocked");
        t.expect_eq((s32)t.call("_ZNK9Framework6CMutex11LockCounterEv", {g.addr()}), n->LockCounter(), "LockCounter");
    }
    for (int depth = 3; depth >= 1; depth--) {
        t.call(kUnlock, {g.addr()});
        n->Unlock();
        char step[32];
        snprintf(step, sizeof step, "Unlock %d", depth);
        same(t, g.get(), n.get(), step);
    }
    t.expect_eq(n->m_owner, (u64)0, "owner after the last Unlock");
    t.expect_eq(n->m_substance.m_lock, FastCriticalSection::kFree, "lock word after the last Unlock");
    // Waiters above the bias: Unlock hands one wakeup to the semaphore.
    t.call(kLock, {g.addr()});
    n->Lock();
    g->m_substance.m_waiters = n->m_substance.m_waiters = FastCriticalSection::kWaiterBias + 2;
    t.call(kUnlock, {g.addr()});
    n->Unlock();
    same(t, g.get(), n.get(), "Unlock with waiters");
    t.expect_eq((u8)t.call("_ZNK4Aska9Semaphore7PollingEv", {g.addr() + offsetof(CMutex, m_substance) + offsetof(FastCriticalSection, m_sem)}),
                (u8)n->m_substance.m_sem.Polling(), "the wakeup posted");
    t.expect_eq((u8)n->m_substance.m_sem.Polling(), (u8)1, "a wakeup posted");
    g->m_substance.m_waiters = n->m_substance.m_waiters = FastCriticalSection::kWaiterBias;
    t.call("_ZNK4Aska9Semaphore4WaitEv", {g.addr() + offsetof(CMutex, m_substance) + offsetof(FastCriticalSection, m_sem)});  // (take them back)
    n->m_substance.m_sem.Wait();
    // Release, then the destructor of a released mutex.
    t.call(kRelease, {g.addr()});
    n->Release();
    same(t, g.get(), n.get(), "Release");
    t.call(kInit, {g.addr()});
    n->Initialize();
    t.call(kDtor, {g.addr()});
    n->DtorBase();
    same(t, g.get(), n.get(), "~CMutex");
}

NATIVE_TEST("sync/fast-critical-section-ctor") {
    test::GuestObj<FastCriticalSection> g, n;
    std::memset(g.raw, 0x5a, sizeof g.raw);
    std::memset(n.raw, 0x5a, sizeof n.raw);
    t.call("_ZN4Aska19FastCriticalSectionC1Ev", {g.addr()});
    n->CtorBase();
    constexpr size_t sem = offsetof(FastCriticalSection, m_sem) + offsetof(Semaphore, m_pSem);
    t.expect_eq(test::normalized(g.get(), {sem}) == test::normalized(n.get(), {sem}), true, "FastCriticalSection() bytes");
    t.call("_ZN4Aska19FastCriticalSectionD1Ev", {g.addr()});
    n->Dtor();
    t.expect_eq(test::normalized(g.get(), {sem}) == test::normalized(n.get(), {sem}), true, "~FastCriticalSection() bytes");
}

// Mutual exclusion across implementations: threads lock one mutex alternately through the guest's
// Lock / Unlock and the natives, recursively too, and increment a counter non-atomically inside;
// a lost update or a broken handoff shows in the count or the final state. Short critical sections
// and 8 threads on fewer free cores make the spin give up, so the waiter / semaphore path runs too.
NATIVE_TEST("sync/cmutex-contention") {
    test::GuestObj<CMutex> m;
    t.call(kCtor, {m.addr()});
    t.call(kInit, {m.addr()});
    u64 lock = t.sym(kLock), unlock = t.sym(kUnlock);
    constexpr int kThreads = 8, kIters = 3000;
    alignas(64) static volatile u64 counter;
    counter = 0;
    std::atomic<bool> done{false};
    s32 max_waiters = 0;  // (a monitor: the wait path must have run)
    std::thread monitor([&] {
        while (!done) max_waiters = std::max(max_waiters, __atomic_load_n(&m->m_substance.m_waiters, __ATOMIC_RELAXED));
    });
    test::run_guest_threads(kThreads, [&](int id) {
        for (int i = 0; i < kIters; i++) {
            bool guest_lock = (i + id) & 1, guest_unlock = (i / 2 + id) & 1, nested = i % 7 == 0;
            if (guest_lock) guest_call(lock, {m.addr()});
            else m->Lock();
            if (nested) {
                if (id & 1) guest_call(lock, {m.addr()});
                else m->Lock();
            }
            u64 v = counter;
            if (i % 64 == 0) std::this_thread::sleep_for(std::chrono::microseconds(50));  // (a long hold: others wait)
            counter = v + 1;
            if (nested) {
                if (id & 1) m->Unlock();
                else guest_call(unlock, {m.addr()});
            }
            if (guest_unlock) guest_call(unlock, {m.addr()});
            else m->Unlock();
        }
    });
    done = true;
    monitor.join();
    t.expect_eq(counter, (u64)kThreads * kIters, "counter (mutual exclusion)");
    if (max_waiters <= FastCriticalSection::kWaiterBias) t.fail("no thread ever waited (max waiters %d): the wait path didn't run", max_waiters);
    t.expect_eq(m->m_lockCount, 0, "lock count after");
    t.expect_eq(m->m_owner, (u64)0, "owner after");
    t.expect_eq(m->m_locked, (u8)0, "locked after");
    t.expect_eq(m->m_substance.m_lock, FastCriticalSection::kFree, "lock word after");
    // The waiter count at rest: the bias, less the wakeups handed out that no waiter took (a waiter
    // that got the lock word between the hand-off and its sem_wait leaves the post for a later one:
    // the guest's protocol, same in the natives). Count + pending posts = bias.
    int posts = 0;
    hle_sem_getvalue(m->m_substance.m_sem.m_pSem, &posts);
    if (m->m_substance.m_waiters + posts != FastCriticalSection::kWaiterBias)
        t.fail("waiters after: %d, pending wakeups %d (bias %d)", m->m_substance.m_waiters, posts, FastCriticalSection::kWaiterBias);

    t.call(kRelease, {m.addr()});
}

// Mutex.cpp's assert strings and the operator delete the natives call: the guest addresses they use.
NATIVE_TEST("sync/guest-addresses") {
    u64 base = main_lib()->base;
    const char* file = (const char*)(base + kMutexCpp);
    t.expect_eq(strncmp(file, "C:\\BAS_Submission", 17) == 0 && strstr(file, "Mutex.cpp") != nullptr, true, "Mutex.cpp path");
    t.expect_eq(strcmp((const char*)(base + kStrUninitializedObject), "Uninitialized object."), 0, "Uninitialized object.");
    t.expect_eq(strcmp((const char*)(base + kAlreadyInitialized), "Already initialized."), 0, "Already initialized.");
    t.expect_eq(strcmp((const char*)(base + kUnlockNotCalled), "Unlock doesn't called, yet."), 0, "Unlock doesn't called, yet.");
}

}  // namespace
}  // namespace soa::native::sync
