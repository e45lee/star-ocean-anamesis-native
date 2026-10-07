// Bionic pthreads / semaphores on top of host glibc.
//
// Mutexes, condition variables and rwlocks are the same size in bionic/arm64 and glibc/x86-64,
// so glibc objects live in-place in guest memory. Bionic's static initializers for
// recursive/errorcheck mutexes are recognised and converted on first use.
#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <string.h>
#ifndef _WIN32
#include <link.h>
#include <sys/resource.h>
#endif
#include <time.h>
#include <unistd.h>

#include <atomic>
#include <mutex>
#include <unordered_map>

#include "core/crash.h"
#include "core/hle.h"
#include "core/log.h"
#include "hle/gfx.h"
#include "core/linux_errno.h"
#include "hle/thread.h"

namespace soa {
namespace {

// ---- attributes (bionic layout) ----
struct BionicAttr {
    u32 flags;
    u32 pad;
    u64 stack_base;
    u64 stack_size;
    u64 guard_size;
    s32 sched_policy;
    s32 sched_priority;
    u8 reserved[16];
};
static_assert(sizeof(BionicAttr) == 56);
constexpr u64 kDefaultStack = 1 << 20;

void th_attr_init(Cpu& c) {
    auto* a = (BionicAttr*)c.x(0);
    memset(a, 0, sizeof *a);
    a->stack_size = kDefaultStack;
    a->guard_size = 4096;
    ret(c, 0);
}
void th_attr_setdetachstate(Cpu& c) {
    auto* a = (BionicAttr*)c.x(0);
    if (c.x(1) == PTHREAD_CREATE_DETACHED) a->flags |= 1;
    else a->flags &= ~1u;
    ret(c, 0);
}
void th_attr_setstacksize(Cpu& c) {
    ((BionicAttr*)c.x(0))->stack_size = c.x(1);
    ret(c, 0);
}
void th_attr_setschedpolicy(Cpu& c) {
    ((BionicAttr*)c.x(0))->sched_policy = (s32)c.x(1);
    ret(c, 0);
}

// ---- keys ----
constexpr int kMaxKeys = 256;
std::atomic<u64> g_key_dtors[kMaxKeys];
std::atomic<bool> g_key_used[kMaxKeys];
thread_local u64 t_key_values[kMaxKeys];

void th_key_create(Cpu& c) {
    for (int i = 0; i < kMaxKeys; i++) {
        bool expected = false;
        if (g_key_used[i].compare_exchange_strong(expected, true)) {
            g_key_dtors[i] = c.x(1);
            *(s32*)c.x(0) = i;
            ret(c, 0);
            return;
        }
    }
    ret(c, EAGAIN);
}
void th_getspecific(Cpu& c) {
    u32 k = (u32)c.x(0);
    ret(c, k < kMaxKeys ? t_key_values[k] : 0);
}
u64 tls_get(u32 k) { return k < kMaxKeys ? t_key_values[k] : 0; }
void th_setspecific(Cpu& c) {
    u32 k = (u32)c.x(0);
    if (k >= kMaxKeys) {
        ret(c, EINVAL);
        return;
    }
    t_key_values[k] = c.x(1);
    ret(c, 0);
}

void run_key_destructors() {
    for (int round = 0; round < 4; round++) {
        bool any = false;
        for (int i = 0; i < kMaxKeys; i++) {
            u64 v = t_key_values[i];
            u64 d = g_key_dtors[i];
            if (v && d && g_key_used[i]) {
                t_key_values[i] = 0;
                guest_call(d, {v});
                any = true;
            }
        }
        if (!any) break;
    }
}

// ---- threads ----
struct StartInfo {
    u64 fn, arg, stack_size;
};
std::mutex g_tid_mutex;
std::unordered_map<pthread_t, pid_t> g_tids;

void* thread_body(void* p) {
    StartInfo si = *(StartInfo*)p;
    delete (StartInfo*)p;
    {
        std::lock_guard lk(g_tid_mutex);
        g_tids[pthread_self()] = gettid();
    }
    {
        char name[32];  // (renamed when the guest names it: prctl(PR_SET_NAME))
        snprintf(name, sizeof name, "guest-%d", (int)gettid());
        crash_thread_begin(name, si.fn);  // core/crash.h: overflows and faults report themselves
    }
    guest_thread_init(si.stack_size);
    u64 r = guest_call(si.fn, {si.arg});
    auto& gt = guest_thread();
    if (gt.exiting) r = gt.exit_value;
    gt.exiting = false;
    run_key_destructors();
    thread_end();  // core/thread_record.h
    {
        std::lock_guard lk(g_tid_mutex);
        g_tids.erase(pthread_self());
    }
    return (void*)r;
}

}  // namespace

size_t hle_static_tls_size() {
#ifdef _WIN32
    return 0;  // TLS isn't on the thread's stack
#else
    // The PT_TLS segments of the modules loaded at start-up (the program's own thread_locals and
    // its shared libraries'): glibc places them at the top of every new thread's stack, inside
    // the size pthread_attr_setstacksize asked for (glibc bug 11787).
    static const size_t n = [] {
        size_t sum = 0;
        dl_iterate_phdr(
            [](dl_phdr_info* info, size_t, void* p) {
                for (int i = 0; i < info->dlpi_phnum; i++) {
                    const auto& ph = info->dlpi_phdr[i];
                    if (ph.p_type != PT_TLS) continue;
                    size_t align = ph.p_align ? ph.p_align : 1;
                    *(size_t*)p += (ph.p_memsz + align - 1) / align * align;
                }
                return 0;
            },
            &sum);
        return sum;
    }();
    return n;
#endif
}

size_t hle_guest_thread_host_stack() { return kGuestThreadHostStack + hle_static_tls_size(); }

namespace {

void th_create(Cpu& c) {
    auto* out = (u64*)c.x(0);
    auto* a = (BionicAttr*)c.x(1);
    auto* si = new StartInfo{c.x(2), c.x(3), a ? a->stack_size : kDefaultStack};
    if (si->stack_size < (256 << 10)) si->stack_size = 256 << 10;
    pthread_attr_t ha;
    pthread_attr_init(&ha);
    pthread_attr_setstacksize(&ha, hle_guest_thread_host_stack());  // host side only runs the JIT + thunks
    if (a && (a->flags & 1)) pthread_attr_setdetachstate(&ha, PTHREAD_CREATE_DETACHED);
    pthread_t t;
    int r = pthread_create(&t, &ha, thread_body, si);
    pthread_attr_destroy(&ha);
    if (r == 0) *out = (u64)t;
    else delete si;
    LOGD("thread", "pthread_create(fn=%s) = %d", describe_guest_addr(c.x(2)).c_str(), r);
    ret(c, (u64)r);
}
void th_join(Cpu& c) {
    void* rv = nullptr;
    int r = pthread_join((pthread_t)c.x(0), &rv);
    if (c.x(1)) *(u64*)c.x(1) = (u64)rv;
    ret(c, (u64)r);
}
void th_exit(Cpu& c) {
    auto& gt = guest_thread();
    gt.exiting = true;
    gt.exit_value = c.x(0);
    c.halt();
}
void th_gettid_np(Cpu& c) {
    pthread_t t = (pthread_t)c.x(0);
    if (t == pthread_self()) {
        ret(c, (u64)gettid());
        return;
    }
    std::lock_guard lk(g_tid_mutex);
    auto it = g_tids.find(t);
    ret(c, it == g_tids.end() ? (u64)-1 : (u64)it->second);
}

// ---- once ----
// The guest's pthread_once_t: 0 not run, 1 running, 2 done. A caller that finds it running sleeps
// until the initializer's thread marks it done (it spun on sched_yield before code review CR3).
void th_once(Cpu& c) {
    auto* o = (std::atomic<s32>*)c.x(0);
    s32 st = o->load();
    if (st == 2) {
        ret(c, 0);
        return;
    }
    s32 expected = 0;
    if (o->compare_exchange_strong(expected, 1)) {
        guest_call(c.x(1), {});
        o->store(2);
        o->notify_all();
        ret(c, 0);
        return;
    }
    for (s32 v; (v = o->load()) != 2;) o->wait(v);
    ret(c, 0);
}

// ---- mutexes ----
#ifdef _WIN32
// A guest's zero-filled (statically initialised) mutex, cond var or rwlock is glibc's initializer
// too; winpthreads' initializers are -1 and its objects pointer-sized: a zero one becomes -1 first.
template <typename T>
T* fix_static(u64 p, T init) {
    auto* w = (std::atomic<T>*)p;
    T zero = 0;
    w->compare_exchange_strong(zero, init);
    return (T*)p;
}
#endif
constexpr u32 kBionicRecursiveInit = 0x4000, kBionicErrorcheckInit = 0x8000;
std::mutex g_init_mutex;

pthread_mutex_t* fix_mutex(u64 p) {
    auto* w = (std::atomic<u32>*)p;
    u32 v = w->load(std::memory_order_relaxed);
    if (__builtin_expect(v == kBionicRecursiveInit || v == kBionicErrorcheckInit, 0)) {
        std::lock_guard lk(g_init_mutex);
        v = w->load();
        if (v == kBionicRecursiveInit || v == kBionicErrorcheckInit) {
            pthread_mutexattr_t a;
            pthread_mutexattr_init(&a);
            pthread_mutexattr_settype(&a, v == kBionicRecursiveInit ? PTHREAD_MUTEX_RECURSIVE : PTHREAD_MUTEX_ERRORCHECK);
            pthread_mutex_init((pthread_mutex_t*)p, &a);
            pthread_mutexattr_destroy(&a);
        }
    }
#ifdef _WIN32
    if (*(u64*)p == 0) fix_static<pthread_mutex_t>(p, PTHREAD_MUTEX_INITIALIZER);
#endif
    return (pthread_mutex_t*)p;
}
void th_mutexattr_init(Cpu& c) {
    *(u64*)c.x(0) = 0;
    ret(c, 0);
}
// bionic's mutex types (a pthread_mutexattr_t's low bits): 0 normal, 1 recursive, 2 errorcheck. glibc
// numbers them the same; winpthreads has 1 errorcheck, 2 recursive.
int host_mutex_type(u64 bionic_type) {
    switch (bionic_type & 3) {
    case 1: return PTHREAD_MUTEX_RECURSIVE;
    case 2: return PTHREAD_MUTEX_ERRORCHECK;
    default: return PTHREAD_MUTEX_NORMAL;
    }
}
void th_mutexattr_settype(Cpu& c) {
    *(u64*)c.x(0) = (*(u64*)c.x(0) & ~3ull) | (c.x(1) & 3);
    ret(c, 0);
}
void th_mutexattr_destroy(Cpu& c) { ret(c, 0); }
void th_mutex_init(Cpu& c) { ret(c, (u64)hle_mutex_init(c.x(0), c.x(1))); }
void th_mutex_destroy(Cpu& c) { ret(c, (u64)hle_mutex_destroy(c.x(0))); }
void th_mutex_lock(Cpu& c) { ret(c, (u64)hle_mutex_lock(c.x(0))); }
void th_mutex_trylock(Cpu& c) { ret(c, (u64)hle_mutex_trylock(c.x(0))); }
void th_mutex_unlock(Cpu& c) { ret(c, (u64)hle_mutex_unlock(c.x(0))); }

// ---- condition variables ----
#ifdef _WIN32
pthread_cond_t* fix_cond(u64 p) { return fix_static<pthread_cond_t>(p, PTHREAD_COND_INITIALIZER); }
#else
pthread_cond_t* fix_cond(u64 p) { return (pthread_cond_t*)p; }
#endif
void th_cond_init(Cpu& c) { ret(c, (u64)hle_cond_init(c.x(0))); }
void th_cond_destroy(Cpu& c) { ret(c, (u64)hle_cond_destroy(c.x(0))); }
void th_cond_signal(Cpu& c) { ret(c, (u64)hle_cond_signal(c.x(0))); }
void th_cond_broadcast(Cpu& c) { ret(c, (u64)hle_cond_broadcast(c.x(0))); }
void th_cond_wait(Cpu& c) { ret(c, (u64)hle_cond_wait(c.x(0), c.x(1))); }
void th_cond_timedwait(Cpu& c) { ret(c, (u64)hle_cond_timedwait(c.x(0), c.x(1), c.x(2))); }

// ---- rwlock ----
void th_rwlock_init(Cpu& c) { ret(c, (u64)pthread_rwlock_init((pthread_rwlock_t*)c.x(0), nullptr)); }
void th_rwlockattr_init(Cpu& c) {
    *(u64*)c.x(0) = 0;
    ret(c, 0);
}

// ---- semaphores (bionic sem_t is 16 bytes, smaller than glibc's: keep host objects aside) ----
// A guest semaphore is a host one keyed by the guest sem_t's address. sem_init always makes a new
// one (a sem_t freed without sem_destroy and initialised again at the same address doesn't keep
// the old count: hle/libc-sem-init-reused-address); a sem_t used without sem_init (zero-filled
// memory, which bionic accepts as a semaphore at 0) gets one on first use, from its count word.
// Assumed, as the game does: memory holding a semaphore that wasn't destroyed isn't reused as a
// semaphore without sem_init (it would inherit the old host semaphore and its count), and a
// semaphore freed without sem_destroy leaks its host object (code review 2026-10-06 R3).
std::mutex g_sem_mutex;
std::unordered_map<u64, sem_t*> g_sems;
sem_t* get_sem(u64 p) {
    std::lock_guard lk(g_sem_mutex);
    auto it = g_sems.find(p);
    if (it != g_sems.end()) return it->second;
    auto* s = new sem_t;  // zero-initialised guest semaphore
    sem_init(s, 0, *(u32*)p);
    g_sems[p] = s;
    return s;
}
int sem_init_guest(u64 p, unsigned value) {
    std::lock_guard lk(g_sem_mutex);
    auto& s = g_sems[p];
    if (s) {
        sem_destroy(s);
        delete s;
    }
    s = new sem_t;
    return sem_init(s, 0, value);
}
void sem_destroy_guest(u64 p) {
    std::lock_guard lk(g_sem_mutex);
    auto it = g_sems.find(p);
    if (it != g_sems.end()) {
        sem_destroy(it->second);
        delete it->second;
        g_sems.erase(it);
    }
}
void th_sem_init(Cpu& c) { ret(c, (u64)(s64)sem_init_guest(c.x(0), (unsigned)c.x(2))); }
void th_sem_destroy(Cpu& c) {
    sem_destroy_guest(c.x(0));
    ret(c, 0);
}
void th_sem_wait(Cpu& c) { ret(c, (u64)(s64)hle_sem_wait(c.x(0))); }
void th_sem_trywait(Cpu& c) { ret(c, (u64)(s64)hle_sem_trywait(c.x(0))); }  // (-1, errno EAGAIN: 11 on both)
void th_sem_post(Cpu& c) { ret(c, (u64)(s64)hle_sem_post(c.x(0))); }
void th_sem_getvalue(Cpu& c) { ret(c, (u64)(s64)hle_sem_getvalue(c.x(0), (int*)c.x(1))); }

}  // namespace

// ---- the imports as host calls (hle/thread.h) ----
int hle_mutex_init(u64 m, u64 attr) {
    pthread_mutexattr_t a;
    pthread_mutexattr_init(&a);
    if (attr) pthread_mutexattr_settype(&a, host_mutex_type(*(u64*)attr));
    int r = pthread_mutex_init((pthread_mutex_t*)m, &a);
    pthread_mutexattr_destroy(&a);
    return linux_errno(r);
}
int hle_mutex_destroy(u64 m) { return linux_errno(pthread_mutex_destroy(fix_mutex(m))); }
int hle_mutex_lock(u64 m) { return linux_errno(pthread_mutex_lock(fix_mutex(m))); }
int hle_mutex_trylock(u64 m) { return linux_errno(pthread_mutex_trylock(fix_mutex(m))); }
int hle_mutex_unlock(u64 m) { return linux_errno(pthread_mutex_unlock(fix_mutex(m))); }
int hle_cond_init(u64 cv) { return linux_errno(pthread_cond_init((pthread_cond_t*)cv, nullptr)); }
int hle_cond_destroy(u64 cv) { return linux_errno(pthread_cond_destroy(fix_cond(cv))); }
int hle_cond_signal(u64 cv) { return linux_errno(pthread_cond_signal(fix_cond(cv))); }
int hle_cond_broadcast(u64 cv) { return linux_errno(pthread_cond_broadcast(fix_cond(cv))); }
int hle_cond_wait(u64 guest_cv, u64 guest_m) {
    auto* cv = fix_cond(guest_cv);
    pthread_mutex_t* m = fix_mutex(guest_m);
    if (!window_thread()) return linux_errno(pthread_cond_wait(cv, m));
    // Idle presenting (hle/gfx.h): the window's thread (the game's RenderThread, waiting for its next
    // frame's work) waits in slices, so that it notices idle presenting turned on while it already
    // waits, and then repaints the last frame between slices. A slice's timeout is not a wakeup.
    for (;;) {
        timespec t;
        clock_gettime(CLOCK_REALTIME, &t);
        t.tv_nsec += (idle_present_on() ? kIdlePresentMs : kIdleCheckMs) * 1000000L;
        if (t.tv_nsec >= 1000000000L) t.tv_sec++, t.tv_nsec -= 1000000000L;
        int r = pthread_cond_timedwait(cv, m, &t);
        if (r != ETIMEDOUT) return linux_errno(r);
        if (idle_present_on()) idle_present();
    }
}
int hle_cond_timedwait(u64 cv, u64 m, u64 guest_abstime) {
    // The guest's timespec is two 64-bit words. bionic (and glibc) refuse a tv_nsec outside
    // [0, 1e9) with EINVAL before waiting; winpthreads' 32-bit tv_nsec would take its low half
    // (Aska::Event::Wait builds tv_nsec >= 1e9 for timeouts of a second or more: a wait that never
    // ends on Windows when the low half is negative), so the check is made here for both.
    const s64* g = (const s64*)guest_abstime;
    if (g[1] < 0 || g[1] >= 1000000000) return linux_errno(EINVAL);
    timespec t;
    t.tv_sec = (time_t)g[0];
    t.tv_nsec = (long)g[1];
    return linux_errno(pthread_cond_timedwait(fix_cond(cv), fix_mutex(m), &t));
}
int hle_sem_wait(u64 guest_sem) {
    sem_t* s = get_sem(guest_sem);
    int r;
    while ((r = sem_wait(s)) != 0 && errno == EINTR) {}
    return r;
}
int hle_sem_trywait(u64 guest_sem) { return sem_trywait(get_sem(guest_sem)); }
int hle_sem_post(u64 guest_sem) { return sem_post(get_sem(guest_sem)); }
int hle_sem_getvalue(u64 guest_sem, int* value) { return sem_getvalue(get_sem(guest_sem), value); }

sem_t* hle_host_sem(u64 guest_sem) { return get_sem(guest_sem); }
int hle_host_sem_init(u64 guest_sem, unsigned value) { return sem_init_guest(guest_sem, value); }
void hle_host_sem_destroy(u64 guest_sem) { sem_destroy_guest(guest_sem); }

void register_libc_thread(Hle& h) {
    h.fn("pthread_attr_init", th_attr_init);
    h.fn("pthread_attr_setdetachstate", th_attr_setdetachstate);
    h.fn("pthread_attr_setstacksize", th_attr_setstacksize);
    h.fn("pthread_attr_setschedpolicy", th_attr_setschedpolicy);
    h.fn("pthread_create", th_create);
    h.fn("pthread_join", th_join);
    h.fn("pthread_exit", th_exit);
    h.fn("pthread_detach", [](Cpu& c) { ret(c, (u64)pthread_detach((pthread_t)c.x(0))); });
    h.fn("pthread_self", [](Cpu& c) { ret(c, (u64)pthread_self()); });
    h.fn("pthread_equal", [](Cpu& c) { ret(c, c.x(0) == c.x(1)); });
    h.fn("pthread_gettid_np", th_gettid_np);
    h.fn("pthread_once", th_once);
    h.fn("pthread_key_create", th_key_create);
    h.fn("pthread_getspecific", th_getspecific);
    h.fn("pthread_setspecific", th_setspecific);
    h.fn("pthread_mutexattr_init", th_mutexattr_init);
    h.fn("pthread_mutexattr_settype", th_mutexattr_settype);
    h.fn("pthread_mutexattr_destroy", th_mutexattr_destroy);
    h.fn("pthread_mutex_init", th_mutex_init);
    h.fn("pthread_mutex_destroy", th_mutex_destroy);
    h.fn("pthread_mutex_lock", th_mutex_lock);
    h.fn("pthread_mutex_trylock", th_mutex_trylock);
    h.fn("pthread_mutex_unlock", th_mutex_unlock);
    h.fn("pthread_cond_init", th_cond_init);
    h.fn("pthread_cond_destroy", th_cond_destroy);
    h.fn("pthread_cond_signal", th_cond_signal);
    h.fn("pthread_cond_broadcast", th_cond_broadcast);
    h.fn("pthread_cond_wait", th_cond_wait);
    h.fn("pthread_cond_timedwait", th_cond_timedwait);
    h.fn("pthread_rwlock_init", th_rwlock_init);
    h.fn("pthread_rwlockattr_init", th_rwlockattr_init);
    h.fn("pthread_rwlockattr_destroy", [](Cpu& c) { ret(c, 0); });
    h.fn("sem_init", th_sem_init);
    h.fn("sem_destroy", th_sem_destroy);
    h.fn("sem_wait", th_sem_wait);
    h.fn("sem_trywait", th_sem_trywait);
    h.fn("sem_post", th_sem_post);
    h.fn("sem_getvalue", th_sem_getvalue);
    HLE_WRAP(h, sched_yield);
    HLE_WRAP(h, nanosleep);
    HLE_WRAP(h, sleep);
#ifdef _WIN32  // thread priorities are left to Windows
    h.fn("getpriority", [](Cpu& c) { ret(c, 0); });
    h.fn("setpriority", [](Cpu& c) { ret(c, 0); });
#else
    h.fn("getpriority", [](Cpu& c) { ret(c, (u64)(s64)getpriority((__priority_which_t)c.x(0), (id_t)c.x(1))); });
    h.fn("setpriority", [](Cpu& c) { ret(c, (u64)(s64)setpriority((__priority_which_t)c.x(0), (id_t)c.x(1), (int)c.x(2))); });
#endif
}

// Value of a guest pthread key on the calling thread (pthread_getspecific for native code).
u64 guest_getspecific(u32 key) { return tls_get(key); }

}  // namespace soa
