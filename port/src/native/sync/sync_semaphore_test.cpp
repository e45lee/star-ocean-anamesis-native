// Differential tests of Aska::Semaphore / Aska::Mutex (sync_semaphore.cpp) against the 3.7.0 guest,
// and waits woken across implementations.
#include <atomic>
#include <chrono>
#include <thread>

#include "native/common/test.h"
#include "native/sync/sync_layout.h"
#include "native/sync/sync_test_util.h"

namespace soa::native::sync {
namespace {

NATIVE_TEST("sync/semaphore-sequence") {
    test::GuestObj<Semaphore> g, n;
    auto same = [&](const char* step) {
        if (test::normalized(g.get(), {0}) != test::normalized(n.get(), {0})) t.fail("%s: bytes differ", step);
    };
    t.call("_ZN4Aska9SemaphoreC1Ev", {g.addr()});
    n->CtorBase();
    same("ctor");
    // Not created.
    t.expect_eq((u8)t.call("_ZNK4Aska9Semaphore7IsReadyEv", {g.addr()}), (u8)n->IsReady(), "IsReady (none)");
    t.expect_eq((u8)t.call("_ZNK4Aska9Semaphore15WaitNonBlockingEv", {g.addr()}), (u8)n->WaitNonBlocking(), "WaitNonBlocking (none)");
    t.expect_eq((u8)t.call("_ZNK4Aska9Semaphore7PollingEv", {g.addr()}), (u8)n->Polling(), "Polling (none)");
    t.expect_eq((u32)t.call("_ZNK4Aska9Semaphore13Signal_LegacyEv", {g.addr()}), n->Signal_Legacy(), "Signal_Legacy (none)");
    t.expect_eq((s32)t.call("_ZNK4Aska9Semaphore6SignalEv", {g.addr()}), n->Signal(), "Signal (none)");
    t.expect_eq((s32)t.call("_ZNK4Aska9Semaphore4WaitEv", {g.addr()}), n->Wait(), "Wait (none)");
    t.expect_eq((u8)t.call("_ZN4Aska9Semaphore6CreateEii", {g.addr(), 3, 10}), (u8)n->Create(3, 10), "Create(3, 10)");
    same("Create");
    t.expect_eq((u8)t.call("_ZNK4Aska9Semaphore7IsReadyEv", {g.addr()}), (u8)n->IsReady(), "IsReady");
    for (int k = 0; k < 4; k++) {
        t.expect_eq((u8)t.call("_ZNK4Aska9Semaphore7PollingEv", {g.addr()}), (u8)n->Polling(), "Polling");
        t.expect_eq((u8)t.call("_ZNK4Aska9Semaphore15WaitNonBlockingEv", {g.addr()}), (u8)n->WaitNonBlocking(), "WaitNonBlocking");
    }
    t.expect_eq((s32)t.call("_ZNK4Aska9Semaphore6SignalEv", {g.addr()}), n->Signal(), "Signal");
    t.expect_eq((u32)t.call("_ZNK4Aska9Semaphore13Signal_LegacyEv", {g.addr()}), n->Signal_Legacy(), "Signal_Legacy");
    t.expect_eq((s32)t.call("_ZNK4Aska9Semaphore4WaitEv", {g.addr()}), n->Wait(), "Wait");
    t.expect_eq((s32)t.call("_ZNK4Aska9Semaphore4WaitEv", {g.addr()}), n->Wait(), "Wait");
    t.expect_eq((u8)t.call("_ZNK4Aska9Semaphore7PollingEv", {g.addr()}), (u8)n->Polling(), "Polling (empty)");
    t.call("_ZN4Aska9Semaphore4ExitEv", {g.addr()});
    n->Exit();
    same("Exit");
    t.call("_ZN4Aska9SemaphoreD1Ev", {g.addr()});
    n->Dtor();
    same("dtor");
}

NATIVE_TEST("sync/mutex-binary-semaphore") {
    test::GuestObj<Mutex> g, n;
    t.call("_ZN4Aska5MutexC1Ev", {g.addr()});
    n->CtorBase();
    constexpr size_t sem = offsetof(Mutex, m_sem);
    t.expect_eq(test::normalized(g.get(), {sem}) == test::normalized(n.get(), {sem}), true, "Mutex() bytes");
    t.expect_eq((u8)t.call("_ZN4Aska5Mutex7TryLockEv", {g.addr()}), (u8)n->TryLock(), "TryLock (free)");
    t.expect_eq((u8)t.call("_ZN4Aska5Mutex7TryLockEv", {g.addr()}), (u8)n->TryLock(), "TryLock (held)");
    t.expect_eq((s32)t.call("_ZN4Aska5Mutex6UnlockEv", {g.addr()}), n->Unlock(), "Unlock");
    t.expect_eq((s32)t.call("_ZN4Aska5Mutex4LockEv", {g.addr()}), n->Lock(), "Lock");
    t.expect_eq((s32)t.call("_ZN4Aska5Mutex6UnlockEv", {g.addr()}), n->Unlock(), "Unlock");
    t.call("_ZN4Aska5MutexD1Ev", {g.addr()});
    n->DtorBase();
    t.expect_eq(test::normalized(g.get(), {sem}) == test::normalized(n.get(), {sem}), true, "~Mutex() bytes");
}

// One host semaphore behind both: a native Wait woken by the guest's Signal and the reverse.
NATIVE_TEST("sync/semaphore-wakeup-interop") {
    for (int native_waits = 0; native_waits < 2; native_waits++) {
        test::GuestObj<Semaphore> s;
        t.call("_ZN4Aska9SemaphoreC1Ev", {s.addr()});
        t.call("_ZN4Aska9Semaphore6CreateEii", {s.addr(), 0, 100});
        u64 wait = t.sym("_ZNK4Aska9Semaphore4WaitEv"), signal = t.sym("_ZNK4Aska9Semaphore6SignalEv");
        std::atomic<int> woke{0};
        test::run_guest_threads(3, [&](int id) {
            if (id < 2) {
                if (native_waits) s->Wait();
                else guest_call(wait, {s.addr()});
                woke++;
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
                for (int k = 0; k < 2; k++) {
                    if (native_waits) guest_call(signal, {s.addr()});
                    else s->Signal();
                }
            }
        });
        t.expect_eq(woke.load(), 2, native_waits ? "native Waits woken by guest Signals" : "guest Waits woken by native Signals");
        t.call("_ZN4Aska9Semaphore4ExitEv", {s.addr()});
    }
}

}  // namespace
}  // namespace soa::native::sync
