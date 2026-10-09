// The guest's thread imports (hle/libc_thread.cpp, the futex syscall of libc_misc.cpp /
// libc_win32.cpp), called the way the guest calls them (guest_call on the import's thunk), from
// several host threads. Also run by build/runtime/soaruntime_tests (win:runtime-tests on Windows).
//
// hle/libc-futex-wait-bitset-deadline: FUTEX_WAIT_BITSET's timeout is an absolute CLOCK_MONOTONIC
// time (the guest's clock_gettime); a wait 50 ms before it times out with ETIMEDOUT. Windows used
// the absolute time as a relative timeout (a wait of the machine's uptime) before code review CR3.
// hle/libc-futex-wake-count: FUTEX_WAKE returns how many waiters it woke (0 with none, where
// Windows always said 1; at least 1 with one waiting).
// hle/libc-pthread-once-waits: a second pthread_once caller sleeps until the first one's
// initializer has run (it spun on sched_yield, a core's worth of CPU for as long as the
// initializer took).
// hle/libc-sem-init-reused-address: guest semaphores are host objects keyed by the guest sem_t's
// address (libc_thread.cpp); sem_init over an address whose semaphore was never destroyed (a freed
// and reused sem_t) starts from the new value, not the old count.
#include <time.h>

#include <atomic>
#include <chrono>
#include <string>
#include <thread>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/hle.h"
#include "soaruntime/core/selftest.h"
#include "soaruntime/core/thread_record.h"

namespace soa {
namespace {

constexpr s64 kFutex = 98;
constexpr u64 kFutexWaitBitsetPrivate = 9 | 128, kFutexWakePrivate = 1 | 128, kBitsetAny = 0xffffffff;

u64 import(RuntimeTestContext& t, const char* name) {
    u64 a = Hle::get().lookup(name);
    if (!a) t.fail("no import %s", name);
    return a;
}

double thread_cpu_seconds() {
    timespec ts{};
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

RUNTIME_TEST("hle/libc-futex-wait-bitset-deadline") {
    const u64 sys = import(t, "syscall"), clk = import(t, "clock_gettime"), errno_fn = import(t, "__errno");
    if (!sys || !clk || !errno_fn) return;
    alignas(4) static std::atomic<u32> word{0};
    word = 0;
    std::atomic<bool> done{false};
    s64 result = 0;
    int err = 0;
    double took = -1;
    std::thread th([&] {
        ThreadScope scope("futex-test");
        guest_thread_init(256 << 10);
        s64 deadline[2];
        guest_call(clk, {1 /* CLOCK_MONOTONIC */, (u64)deadline});
        deadline[1] += 50000000;
        if (deadline[1] >= 1000000000) deadline[0]++, deadline[1] -= 1000000000;
        auto t0 = std::chrono::steady_clock::now();
        result = (s64)guest_call(sys, {kFutex, (u64)&word, kFutexWaitBitsetPrivate, 0, (u64)deadline, 0, kBitsetAny});
        err = *(int*)guest_call(errno_fn, {});
        took = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
        done = true;
    });
    auto t0 = std::chrono::steady_clock::now();
    while (!done && std::chrono::steady_clock::now() - t0 < std::chrono::seconds(2)) std::this_thread::sleep_for(std::chrono::milliseconds(5));
    if (!done) {
        t.fail("FUTEX_WAIT_BITSET with a deadline 50 ms away still waits after 2 s");
        word = 1;  // let it go
        while (!done) {
            guest_call(sys, {kFutex, (u64)&word, kFutexWakePrivate, 1});
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    th.join();
    if (result != -1 || err != 110) t.fail("FUTEX_WAIT_BITSET past its deadline returned %lld, errno %d (want -1, ETIMEDOUT 110)", (long long)result, err);
    if (took >= 0 && took < 0.03) t.fail("FUTEX_WAIT_BITSET returned after %.3f s, before its deadline 50 ms away", took);
}

RUNTIME_TEST("hle/libc-futex-wake-count") {
    const u64 sys = import(t, "syscall");
    if (!sys) return;
    alignas(4) static std::atomic<u32> word{0};
    word = 0;
    t.expect_eq((s64)guest_call(sys, {kFutex, (u64)&word, kFutexWakePrivate, 1}), (s64)0, "FUTEX_WAKE with no waiter");
    // One waiter (no timeout); wake it until it has gone (it may not be waiting yet at the first wake).
    std::atomic<bool> done{false};
    std::thread th([&] {
        ThreadScope scope("futex-test");
        guest_thread_init(256 << 10);
        guest_call(sys, {kFutex, (u64)&word, kFutexWaitBitsetPrivate, 0, 0, 0, kBitsetAny});
        done = true;
    });
    s64 woken = 0;
    for (int i = 0; i < 400 && !done; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        woken += (s64)guest_call(sys, {kFutex, (u64)&word, kFutexWakePrivate, 0x7fffffff});
    }
    if (!done) {
        t.fail("the waiter didn't wake in 2 s");
        word = 1;
        while (!done) {
            guest_call(sys, {kFutex, (u64)&word, kFutexWakePrivate, 1});
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    th.join();
    // (at least 1: on Windows a wake between the waiter being counted and it waiting counts it
    // without waking it; the next wake does)
    if (woken < 1) t.fail("FUTEX_WAKE reported no waiter woken, with one waiting");
}

std::atomic<int> g_once_runs{0};
std::atomic<bool> g_once_entered{false};
void once_init(Cpu&) {
    g_once_entered = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    g_once_runs++;
}

RUNTIME_TEST("hle/libc-pthread-once-waits") {
    const u64 once = import(t, "pthread_once");
    if (!once) return;
    static const u64 init = make_thunk("selftest_once_init", once_init);
    alignas(4) static std::atomic<s32> control{0};
    control = 0;
    g_once_runs = 0;
    g_once_entered = false;
    std::thread first([&] {
        ThreadScope scope("once-test");
        guest_thread_init(256 << 10);
        guest_call(once, {(u64)&control, init});
    });
    while (!g_once_entered) std::this_thread::yield();
    int runs_seen = -1;
    double cpu = 0;
    std::thread second([&] {
        ThreadScope scope("once-test");
        guest_thread_init(256 << 10);
        double c0 = thread_cpu_seconds();
        guest_call(once, {(u64)&control, init});
        cpu = thread_cpu_seconds() - c0;
        runs_seen = g_once_runs;
    });
    first.join();
    second.join();
    t.expect_eq(runs_seen, 1, "initializer runs seen by the second caller when its pthread_once returned");
    t.expect_eq(g_once_runs.load(), 1, "initializer runs");
    if (cpu > 0.1) t.fail("the second pthread_once caller used %.3f s of CPU while the initializer slept 0.3 s", cpu);
}

RUNTIME_TEST("hle/libc-sem-init-reused-address") {
    const u64 init = import(t, "sem_init"), post = import(t, "sem_post"), getvalue = import(t, "sem_getvalue"),
              destroy = import(t, "sem_destroy");
    if (!init || !post || !getvalue || !destroy) return;
    alignas(8) u8 sem[16] = {};  // bionic's sem_t (LP64): 16 bytes
    int v = -1;
    guest_call(init, {(u64)sem, 0, 0});
    for (int i = 0; i < 3; i++) guest_call(post, {(u64)sem});
    guest_call(getvalue, {(u64)sem, (u64)&v});
    t.expect_eq(v, 3, "value after 3 posts");
    // The same memory as a new semaphore, the old one never destroyed.
    guest_call(init, {(u64)sem, 0, 1});
    guest_call(getvalue, {(u64)sem, (u64)&v});
    t.expect_eq(v, 1, "value after sem_init over a semaphore that wasn't destroyed");
    guest_call(destroy, {(u64)sem});
}

}  // namespace
}  // namespace soa
