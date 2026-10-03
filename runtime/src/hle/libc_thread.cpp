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
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

#include <atomic>
#include <mutex>
#include <unordered_map>

#include "core/hle.h"
#include "core/log.h"
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
    guest_thread_init(si.stack_size);
    u64 r = guest_call(si.fn, {si.arg});
    auto& gt = guest_thread();
    if (gt.exiting) r = gt.exit_value;
    gt.exiting = false;
    run_key_destructors();
    guest_thread_release();
    {
        std::lock_guard lk(g_tid_mutex);
        g_tids.erase(pthread_self());
    }
    return (void*)r;
}

void th_create(Cpu& c) {
    auto* out = (u64*)c.x(0);
    auto* a = (BionicAttr*)c.x(1);
    auto* si = new StartInfo{c.x(2), c.x(3), a ? a->stack_size : kDefaultStack};
    if (si->stack_size < (256 << 10)) si->stack_size = 256 << 10;
    pthread_attr_t ha;
    pthread_attr_init(&ha);
    pthread_attr_setstacksize(&ha, 256 << 10);  // host side only runs the JIT + thunks
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
        ret(c, 0);
        return;
    }
    while (o->load() != 2) sched_yield();
    ret(c, 0);
}

// ---- mutexes ----
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
    return (pthread_mutex_t*)p;
}
void th_mutexattr_init(Cpu& c) {
    *(u64*)c.x(0) = 0;
    ret(c, 0);
}
void th_mutexattr_settype(Cpu& c) {
    *(u64*)c.x(0) = (*(u64*)c.x(0) & ~3ull) | (c.x(1) & 3);
    ret(c, 0);
}
void th_mutexattr_destroy(Cpu& c) { ret(c, 0); }
void th_mutex_init(Cpu& c) {
    pthread_mutexattr_t a;
    pthread_mutexattr_init(&a);
    if (c.x(1)) pthread_mutexattr_settype(&a, (int)(*(u64*)c.x(1) & 3));
    int r = pthread_mutex_init((pthread_mutex_t*)c.x(0), &a);
    pthread_mutexattr_destroy(&a);
    ret(c, (u64)r);
}
void th_mutex_destroy(Cpu& c) { ret(c, (u64)pthread_mutex_destroy(fix_mutex(c.x(0)))); }
void th_mutex_lock(Cpu& c) { ret(c, (u64)pthread_mutex_lock(fix_mutex(c.x(0)))); }
void th_mutex_trylock(Cpu& c) { ret(c, (u64)pthread_mutex_trylock(fix_mutex(c.x(0)))); }
void th_mutex_unlock(Cpu& c) { ret(c, (u64)pthread_mutex_unlock(fix_mutex(c.x(0)))); }

// ---- condition variables ----
void th_cond_init(Cpu& c) { ret(c, (u64)pthread_cond_init((pthread_cond_t*)c.x(0), nullptr)); }
void th_cond_destroy(Cpu& c) { ret(c, (u64)pthread_cond_destroy((pthread_cond_t*)c.x(0))); }
void th_cond_signal(Cpu& c) { ret(c, (u64)pthread_cond_signal((pthread_cond_t*)c.x(0))); }
void th_cond_broadcast(Cpu& c) { ret(c, (u64)pthread_cond_broadcast((pthread_cond_t*)c.x(0))); }
void th_cond_wait(Cpu& c) { ret(c, (u64)pthread_cond_wait((pthread_cond_t*)c.x(0), fix_mutex(c.x(1)))); }
void th_cond_timedwait(Cpu& c) {
    ret(c, (u64)pthread_cond_timedwait((pthread_cond_t*)c.x(0), fix_mutex(c.x(1)), (const timespec*)c.x(2)));
}

// ---- rwlock ----
void th_rwlock_init(Cpu& c) { ret(c, (u64)pthread_rwlock_init((pthread_rwlock_t*)c.x(0), nullptr)); }
void th_rwlockattr_init(Cpu& c) {
    *(u64*)c.x(0) = 0;
    ret(c, 0);
}

// ---- semaphores (bionic sem_t is 16 bytes, smaller than glibc's: keep host objects aside) ----
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
void th_sem_wait(Cpu& c) {
    sem_t* s = get_sem(c.x(0));
    int r;
    while ((r = sem_wait(s)) != 0 && errno == EINTR) {}
    ret(c, (u64)(s64)r);
}
void th_sem_trywait(Cpu& c) { ret(c, (u64)(s64)sem_trywait(get_sem(c.x(0)))); }
void th_sem_post(Cpu& c) { ret(c, (u64)(s64)sem_post(get_sem(c.x(0)))); }
void th_sem_getvalue(Cpu& c) { ret(c, (u64)(s64)sem_getvalue(get_sem(c.x(0)), (int*)c.x(1))); }

}  // namespace

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
    h.fn("getpriority", [](Cpu& c) { ret(c, (u64)(s64)getpriority((__priority_which_t)c.x(0), (id_t)c.x(1))); });
    h.fn("setpriority", [](Cpu& c) { ret(c, (u64)(s64)setpriority((__priority_which_t)c.x(0), (id_t)c.x(1), (int)c.x(2))); });
}

// Value of a guest pthread key on the calling thread (pthread_getspecific for native code).
u64 guest_getspecific(u32 key) { return tls_get(key); }

}  // namespace soa
