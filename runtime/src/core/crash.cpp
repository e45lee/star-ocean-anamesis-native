// Per-thread setup for crash reports that survive a host stack overflow (core/crash.h).
#include "core/crash.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <signal.h>
#include <sys/mman.h>
#endif
#include <unistd.h>

#include <cstdio>
#include <cstring>

#include "core/cpu.h"
#include "core/thread_record.h"

namespace soa {

namespace {

// The calling thread's record, on the heap and owned by its ThreadRecord (core/thread_record.h:
// destroyed last at the thread's end, so a fault in another per-thread destructor still reports).
struct Slot;
thread_local Slot* t_slot = nullptr;

struct Slot {
    CrashThread t;
    ~Slot() {
        if (t_slot == this) t_slot = nullptr;  // (core/thread_record.cpp: end())
#ifndef _WIN32
        if (!t.alt) return;
        long page = sysconf(_SC_PAGESIZE);
        stack_t cur{};
        // Only ours is turned off: dynarmic gives the thread that makes the first JIT its own.
        if (sigaltstack(nullptr, &cur) == 0 && cur.ss_sp == (char*)t.alt + page && !(cur.ss_flags & SS_ONSTACK)) {
            stack_t off{};
            off.ss_flags = SS_DISABLE;
            sigaltstack(&off, nullptr);
        } else if (cur.ss_sp == (char*)t.alt + page) {
            return;  // (exiting on it: keep the mapping)
        }
        munmap(t.alt, kCrashAltStack + page);
        t.alt = nullptr;
#endif
    }
};

CrashThread& this_thread() {
    if (Slot* s = t_slot) return s->t;
    auto* s = new Slot;
    thread_record_add(ThreadPhase::kCrash, s, [](void* p) { delete (Slot*)p; });
    t_slot = s;
    return s->t;
}

void set_name(CrashThread& t, const char* name) {
    if (!name) return;
    snprintf(t.name, sizeof t.name, "%s", name);
#ifndef _WIN32
    char shortname[16];  // the kernel's limit
    snprintf(shortname, sizeof shortname, "%s", name);
    pthread_setname_np(pthread_self(), shortname);
#endif
}

void setup(CrashThread& t) {
    t.active = true;
#ifdef _WIN32
    ULONG g = kCrashAltStack;
    SetThreadStackGuarantee(&g);
    ULONG_PTR lo = 0, hi = 0;
    GetCurrentThreadStackLimits(&lo, &hi);
    t.lo = lo, t.hi = hi;
#else
    pthread_attr_t a;
    if (pthread_getattr_np(pthread_self(), &a) == 0) {
        void* addr = nullptr;
        size_t size = 0;
        pthread_attr_getstack(&a, &addr, &size);
        pthread_attr_getguardsize(&a, &t.guard);
        pthread_attr_destroy(&a);
        t.lo = (uintptr_t)addr, t.hi = t.lo + size;
    }
    stack_t cur{};
    if (sigaltstack(nullptr, &cur) == 0 && !(cur.ss_flags & SS_DISABLE)) return;  // it has one already
    long page = sysconf(_SC_PAGESIZE);
    void* p = mmap(nullptr, kCrashAltStack + page, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (p == MAP_FAILED) return;
    mprotect(p, page, PROT_NONE);  // a guard page below it
    stack_t ss{};
    ss.ss_sp = (char*)p + page;
    ss.ss_size = kCrashAltStack;
    if (sigaltstack(&ss, nullptr) != 0) {
        munmap(p, kCrashAltStack + page);
        return;
    }
    t.alt = p;
#endif
}

}  // namespace

void crash_thread_begin(const char* name, uint64_t guest_entry) {
    CrashThread& t = this_thread();
    if (!t.active) setup(t);
    set_name(t, name);
    if (guest_entry) t.guest_entry = guest_entry;
}

void crash_thread_set_name(const char* name) {
    CrashThread& t = this_thread();
    if (!t.active) setup(t);
    set_name(t, name);
}

const CrashThread* crash_thread() {
    const Slot* s = t_slot;
    return s && s->t.active ? &s->t : nullptr;
}

bool crash_is_stack_overflow(const CrashThread& t, uintptr_t addr, uintptr_t sp) {
    if (!t.lo) return false;
    constexpr uintptr_t kNear = 64 << 10;  // a frame can skip past the guard page
    const uintptr_t below = t.guard + kNear;
    bool addr_hit = addr < t.lo + 4096 && addr + below >= t.lo;
    bool sp_hit = sp < t.lo + 4096 && sp + below >= t.lo;
    return addr_hit || sp_hit;
}

void crash_report_overflow(const CrashThread& t, uintptr_t sp) {
    size_t size = t.hi - t.lo, used = sp < t.hi ? t.hi - sp : 0;
    fprintf(stderr, "\n*** stack overflow on thread %s (tid %d, stack %zu KiB, used ~%zu KiB) ***\n", t.name[0] ? t.name : "?", (int)gettid(),
            size >> 10, used >> 10);
    if (t.guest_entry) fprintf(stderr, "thread entry (guest) = %s\n", describe_guest_addr(t.guest_entry).c_str());
    fflush(stderr);
}

}  // namespace soa
