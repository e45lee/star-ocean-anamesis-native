// Differential tests of Aska::Thread's bound members (sync_thread.cpp) against the 3.7.0 guest.
#include <chrono>

#include "native/common/test.h"
#include "native/sync/sync_layout.h"
#include "native/sync/sync_test_util.h"

namespace soa::native::sync {
namespace {

NATIVE_TEST("sync/thread-members") {
    test::GuestObj<Thread> g, n;
    t.call("_ZN4Aska6ThreadC1Ev", {g.addr()});
    n->Ctor();
    t.expect_eq(std::memcmp(g.raw, n.raw, sizeof g.raw), 0, "Thread() bytes");
    t.expect_eq((s32)t.call("_ZN4Aska6Thread7WaitEndEv", {g.addr()}), n->WaitEnd(), "WaitEnd (no thread)");
    g->m_thread = n->m_thread = 0x1234;
    t.call("_ZN4Aska6Thread6DeleteEv", {g.addr()});
    n->Delete();
    t.expect_eq(std::memcmp(g.raw, n.raw, sizeof g.raw), 0, "Delete");
    t.call("_ZN4Aska6ThreadD1Ev", {g.addr()});
    n->DtorBase();
    t.expect_eq(std::memcmp(g.raw, n.raw, sizeof g.raw), 0, "~Thread() bytes");
    t.expect_eq(t.call("_ZN4Aska6Thread12GetCurrentIDEv", {}), Thread::GetCurrentID(), "GetCurrentID");
}

// Both sides end in the host's nanosleep (the HLE's thunk; the native's sleep_for), so the test
// checks the argument conversion (ms / us to a timespec): equal results, and each side sleeps about
// the requested time. "About" is the host's timer: Linux never wakes early; Windows (winpthreads:
// whole milliseconds, a wait on the system tick) can wake up to a tick (15.6 ms without
// timeBeginPeriod) plus the truncated millisecond early (a 3 ms Sleep once took 2356 us there), so
// the 50 ms cases carry the meaning on Windows: a ms / us mix-up (1000x) stays outside the bounds.
// The upper bound leaves 2 s for a loaded host.
NATIVE_TEST("sync/thread-sleep") {
    struct Case {
        const char* sym;
        s32 (*native)(u32);
        u32 arg;
        s64 want_us;
    };
#ifdef _WIN32
    constexpr s64 kEarlyUs = 16000 + 1000;
#else
    constexpr s64 kEarlyUs = 0;
#endif
    for (const Case& k : {Case{"_ZN4Aska6Thread5SleepEj", &Thread::Sleep, 3, 3000}, Case{"_ZN4Aska6Thread5SleepEj", &Thread::Sleep, 50, 50000},
                          Case{"_ZN4Aska6Thread6SleepUEj", &Thread::SleepU, 1500, 1500}, Case{"_ZN4Aska6Thread6SleepUEj", &Thread::SleepU, 50000, 50000},
                          Case{"_ZN4Aska6Thread6SleepUEj", &Thread::SleepU, 0, 0}}) {
        auto t0 = std::chrono::steady_clock::now();
        s32 gr = (s32)t.call(k.sym, {k.arg});
        auto t1 = std::chrono::steady_clock::now();
        s32 nr = k.native(k.arg);
        auto t2 = std::chrono::steady_clock::now();
        t.expect_eq(gr, nr, k.sym);
        s64 gus = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        s64 nus = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        s64 lo = k.want_us - kEarlyUs - k.want_us / 20, hi = k.want_us + 2000000;  // (5%: the clocks' granularity)
        if (gus < lo || nus < lo || gus > hi || nus > hi)
            t.fail("%s(%u): guest slept %lld us, native %lld us (expected %lld..%lld)", k.sym, k.arg, (long long)gus, (long long)nus, (long long)lo,
                   (long long)hi);
    }
}

// The destructor joins the thread: a guest-created Aska::Thread's handle (pthread_create through the
// HLE) joined by the native destructor.
NATIVE_TEST("sync/thread-join") {
    test::GuestObj<Thread> th;
    t.call("_ZN4Aska6ThreadC1Ev", {th.addr()});
    // Create(bool, priority, stack size, bool): runs Main -> vtable Handler (the base's: returns at once).
    u8 ok = (u8)t.call("_ZN4Aska6Thread6CreateEbiib", {th.addr(), 1, 50, 0x10000, 1});
    t.expect_eq(ok, (u8)1, "Thread::Create");
    if (ok) {
        t.expect_eq(th->m_thread != 0, true, "handle");
        th->DtorBase();
        t.expect_eq(th->m_thread, (u64)0, "joined and cleared");
    }
}

}  // namespace
}  // namespace soa::native::sync
