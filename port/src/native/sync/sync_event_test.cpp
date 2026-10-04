// Differential tests of Aska::Event / Aska::CriticalSection (sync_event.cpp) against the 3.7.0 guest:
// the same calls on a guest-run and a native-run event (flags, results, the quirky timeouts), and
// waits woken across implementations (native Wait / guest Set and the reverse).
#include <atomic>
#include <chrono>
#include <thread>

#include "native/common/test.h"
#include "native/sync/sync_layout.h"
#include "native/sync/sync_test_util.h"

namespace soa::native::sync {
namespace {

const char* kCreate = "_ZN4Aska5Event6CreateEbb";
const char* kWait = "_ZNK4Aska5Event4WaitEj";
const char* kSet = "_ZNK4Aska5Event3SetEv";
const char* kReset = "_ZNK4Aska5Event5ResetEv";
const char* kIsSignal = "_ZNK4Aska5Event8IsSignalEv";
const char* kExit = "_ZN4Aska5Event4ExitEv";

void same_flags(TestContext& t, Event* g, Event* n, const char* step) {
    if (g->m_signaled != n->m_signaled || g->m_manualReset != n->m_manualReset || (g->m_pMutex != 0) != (n->m_pMutex != 0) ||
        (g->m_pMutex && g->m_pMutex - (u64)g != n->m_pMutex - (u64)n))
        t.fail("%s: guest signaled %u manual %u mutex %d, native %u %u %d", step, g->m_signaled, g->m_manualReset, g->m_pMutex != 0, n->m_signaled,
               n->m_manualReset, n->m_pMutex != 0);
}

NATIVE_TEST("sync/event-sequence") {
    for (int manual = 0; manual < 2; manual++)
        for (int initial = 0; initial < 2; initial++) {
            test::GuestObj<Event> g, n;
            // Not created: everything is a no-op returning false.
            t.expect_eq((u8)t.call(kSet, {g.addr()}), (u8)n->Set(), "Set (no event)");
            t.expect_eq((u8)t.call(kWait, {g.addr(), 0}), (u8)n->Wait(0), "Wait (no event)");
            t.expect_eq((u8)t.call(kIsSignal, {g.addr()}), (u8)n->IsSignal(), "IsSignal (no event)");
            t.expect_eq((u8)t.call(kCreate, {g.addr(), (u64)manual, (u64)initial}), (u8)n->Create(manual, initial), "Create");
            same_flags(t, g.get(), n.get(), "Create");
            t.expect_eq((u8)t.call(kCreate, {g.addr(), (u64)!manual, (u64)!initial}), (u8)n->Create(!manual, !initial), "Create again (no-op)");
            same_flags(t, g.get(), n.get(), "Create again");
            t.expect_eq((u8)t.call(kIsSignal, {g.addr()}), (u8)n->IsSignal(), "IsSignal");
            // A wait on a signaled event returns at once (and an auto-reset one is cleared).
            if (initial) {
                t.expect_eq((u8)t.call(kWait, {g.addr(), 0}), (u8)n->Wait(0), "Wait (signaled)");
                same_flags(t, g.get(), n.get(), "Wait (signaled)");
            }
            t.expect_eq((u8)t.call(kReset, {g.addr()}), (u8)n->Reset(), "Reset");
            same_flags(t, g.get(), n.get(), "Reset");
            // Timeouts on an unsignaled event: 5 ms waits; 1000 ms builds tv_nsec >= 1e9 and fails at once.
            for (u32 ms : {5u, 1000u, 2500u}) {
                auto t0 = std::chrono::steady_clock::now();
                u8 gr = (u8)t.call(kWait, {g.addr(), ms});
                auto t1 = std::chrono::steady_clock::now();
                u8 nr = (u8)n->Wait(ms);
                auto t2 = std::chrono::steady_clock::now();
                t.expect_eq(gr, nr, "Wait(timeout) result");
                same_flags(t, g.get(), n.get(), "Wait(timeout)");
                auto gms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
                auto nms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                // From 1000 ms on tv_nsec is >= 1e9 whatever the time: both fail at once (EINVAL) instead of
                // waiting. (5 ms waits, except in the last 5 ms of a second, when it fails at once too.)
                if (ms >= 1000 && (gms >= 500 || nms >= 500)) t.fail("Wait(%u): guest took %lld ms, native %lld ms", ms, (long long)gms, (long long)nms);
            }
            t.expect_eq((u8)t.call(kSet, {g.addr()}), (u8)n->Set(), "Set");
            same_flags(t, g.get(), n.get(), "Set");
            t.expect_eq((u8)t.call(kWait, {g.addr(), 5}), (u8)n->Wait(5), "Wait(5) after Set");
            same_flags(t, g.get(), n.get(), "Wait after Set");
            t.call(kExit, {g.addr()});
            n->Exit();
            same_flags(t, g.get(), n.get(), "Exit");
            t.call(kExit, {g.addr()});  // (twice: a no-op)
            n->Exit();
        }
}

// A native Wait woken by the guest's Set, and the guest's Wait woken by the native Set.
NATIVE_TEST("sync/event-wakeup-interop") {
    for (int native_waits = 0; native_waits < 2; native_waits++) {
        test::GuestObj<Event> e;
        t.call(kCreate, {e.addr(), 0, 0});
        u64 wait = t.sym(kWait), set = t.sym(kSet);
        std::atomic<bool> woke{false};
        test::run_guest_threads(2, [&](int id) {
            if (id == 0) {
                if (native_waits) e->Wait(0);
                else guest_call(wait, {e.addr(), 0});
                woke = true;
            } else {
                // Set until the waiter woke (a Set before it waits leaves the event signaled: also fine).
                for (int i = 0; i < 2000 && !woke; i++) {
                    if (native_waits) guest_call(set, {e.addr()});
                    else e->Set();
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }
        });
        t.expect_eq(woke.load(), true, native_waits ? "native Wait woken by guest Set" : "guest Wait woken by native Set");
        t.call(kExit, {e.addr()});
    }
}

NATIVE_TEST("sync/critical-section") {
    test::GuestObj<CriticalSection> g, n;
    t.call("_ZN4Aska15CriticalSectionC1Ev", {g.addr()});
    n->CtorBase();
    const char* try_enter = "_ZNK4Aska15CriticalSection8TryEnterEv";
    const char* leave = "_ZNK4Aska15CriticalSection5LeaveEv";
    // Recursive: the owner enters again; another thread can't.
    for (int k = 0; k < 2; k++) {
        t.expect_eq((u8)t.call(try_enter, {g.addr()}), (u8)1, "guest TryEnter (owner)");
        t.expect_eq((u8)n->TryEnter(), (u8)1, "native TryEnter (owner)");
    }
    u8 other_g = 2, other_n = 2;
    u64 te = t.sym(try_enter);
    test::run_guest_threads(1, [&](int) {
        other_g = (u8)guest_call(te, {g.addr()});
        other_n = (u8)n->TryEnter();
    });
    t.expect_eq(other_g, (u8)0, "guest TryEnter from another thread");
    t.expect_eq(other_n, (u8)0, "native TryEnter from another thread");
    for (int k = 0; k < 2; k++) {
        t.call(leave, {g.addr()});
        t.call(leave, {n.addr()});
    }
    t.call("_ZN4Aska15CriticalSection6DeleteEv", {g.addr()});
    t.call("_ZN4Aska15CriticalSection6DeleteEv", {n.addr()});
}

}  // namespace
}  // namespace soa::native::sync
