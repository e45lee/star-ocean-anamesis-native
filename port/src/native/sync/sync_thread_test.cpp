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

NATIVE_TEST("sync/thread-sleep") {
    struct Case {
        const char* sym;
        s32 (*native)(u32);
        u32 arg;
        int min_us;
    };
    for (const Case& k : {Case{"_ZN4Aska6Thread5SleepEj", &Thread::Sleep, 3, 2500}, Case{"_ZN4Aska6Thread6SleepUEj", &Thread::SleepU, 1500, 1200},
                          Case{"_ZN4Aska6Thread6SleepUEj", &Thread::SleepU, 0, 0}}) {
        auto t0 = std::chrono::steady_clock::now();
        s32 gr = (s32)t.call(k.sym, {k.arg});
        auto t1 = std::chrono::steady_clock::now();
        s32 nr = k.native(k.arg);
        auto t2 = std::chrono::steady_clock::now();
        t.expect_eq(gr, nr, k.sym);
        auto gus = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        auto nus = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        if (gus < k.min_us || nus < k.min_us) t.fail("%s(%u): guest slept %lld us, native %lld us", k.sym, k.arg, (long long)gus, (long long)nus);
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
