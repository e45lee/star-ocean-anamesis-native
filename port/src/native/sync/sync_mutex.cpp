// Aska::FastCriticalSection and Framework::CMutex (port/decomp/sync/mutex.c).
//
// The guest's algorithm on the guest's words, with host atomics: the lock word, the waiter count and
// the recursion count are changed by LL/SC loops in the guest (ldaxr / stlxr) and by atomic RMWs
// here. Both are the same host operation: the JIT's exclusive store is a host compare-and-swap on
// the word (runtime/src/core/cpu.cpp, MemoryWriteExclusive*: fastmem_exclusive_access), so guest
// code still entering the same FastCriticalSection inline (other subsystems) and these natives
// exclude each other correctly. What changes is the cost: an uncontended Lock / Unlock was ~20
// JIT'd instructions, two HLE calls (pthread_self) and four exclusive pairs through dynarmic's
// global monitor; the spin of a contended Lock ran 512 LL/SC probes.
#include <atomic>

#ifndef _WIN32
#include <sched.h>
#endif
#include <pthread.h>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/loader.h"
#include "soaruntime/hle/thread.h"
#include "native/common/guest_std.h"
#include "native/common/native_method.h"
#include "native/sync/sync_check.h"
#include "native/sync/sync_layout.h"
#include "native/common/gen/common_addresses.h"
#include "native/sync/gen/sync_addresses.h"

namespace soa::native::sync {

namespace {

// seq_cst read-modify-writes and stores: the guest's acquire / release exclusives and its dmb ish.
inline s32 atomic_load(const s32& v) { return __atomic_load_n(&v, __ATOMIC_SEQ_CST); }
inline void atomic_store(s32& v, s32 x) { __atomic_store_n(&v, x, __ATOMIC_SEQ_CST); }
inline void atomic_add(s32& v, s32 d) { __atomic_fetch_add(&v, d, __ATOMIC_SEQ_CST); }
inline bool atomic_cas(s32& v, s32 expected, s32 desired) {
    return __atomic_compare_exchange_n(&v, &expected, desired, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}
inline void fence() { __atomic_thread_fence(__ATOMIC_SEQ_CST); }
inline void cpu_relax() {
#if defined(__x86_64__) || defined(__i386__)
    __builtin_ia32_pause();
#elif defined(__aarch64__)
    asm volatile("yield");
#endif
}

// Framework::gDoAssert(file, line, message) with Mutex.cpp's own strings (sync/addresses.txt, common's
// kStrUninitializedObject).
void mutex_assert(int line, u64 message) {
    static const u64 fn = guest::sym("_ZN9Framework9gDoAssertEPKciS1_z");
    u64 base = main_lib()->base;
    guest_call(fn, {base + kMutexCpp, (u64)line, base + message});
}

}  // namespace

// ---- Aska::FastCriticalSection ----

void FastCriticalSection::CtorBase() {
    m_lock = kFree;
    m_waiters = kWaiterBias;
    m_sem.CtorBase();
    m_sem.Create(0, 0x7fffffff);
}

void FastCriticalSection::Dtor() {
    m_sem.Exit();
    m_sem.Dtor();
}

void FastCriticalSection::Enter() {
    // Spin: 0x200 probes of the lock word.
    for (int i = 0;; i++) {
        if (atomic_load(m_lock) == kFree && atomic_cas(m_lock, kFree, kHeld)) {
            fence();
            return;
        }
        if (i >= kSpins - 1) break;
        cpu_relax();
    }
    // Wait: counted in m_waiters while blocked on m_sem (or sleeping 1 ms when it isn't there).
    atomic_add(m_waiters, 1);
    while (!(atomic_load(m_lock) == kFree && atomic_cas(m_lock, kFree, kHeld))) {
        do {
            if (m_sem.IsReady()) {
                m_sem.Wait();
            } else {
                atomic_add(m_waiters, -1);
                Thread::Sleep(1);
            }
            atomic_add(m_waiters, 1);
        } while (atomic_load(m_lock) != kFree);
    }
    atomic_add(m_waiters, -1);
    fence();
}

void FastCriticalSection::Leave() {
    fence();
    atomic_store(m_lock, kFree);
    fence();
    s32 waiters = m_waiters;  // (a plain load in the guest)
    if (t_obs) t_obs->waiters_read = waiters;
    if (waiters > kWaiterBias) {
        atomic_add(m_waiters, -1);
        if (m_sem.IsReady()) {
            m_sem.Signal();
            if (t_obs) t_obs->posted = true;
        }
    }
}

// ---- Framework::CMutex ----

static const void* cmutex_vtable() {
    static const u64 vt = guest::sym("_ZTVN9Framework6CMutexE") + 0x10;
    return (const void*)vt;
}

void CMutex::Ctor() {
    vtable = cmutex_vtable();
    m_initialized = 0;
    m_locked = 0;
}

void CMutex::Release() {
    if (m_locked) mutex_assert(0x36, kUnlockNotCalled);
    if (m_initialized) {
        fence();
        if (m_lockCount != 0) mutex_assert(0x3a, kUnlockNotCalled);
        if (!m_initialized) mutex_assert(0x44, kStrUninitializedObject);
        m_substance.Dtor();
    }
    m_initialized = 0;
    m_locked = 0;
}

void CMutex::DtorBase() {
    vtable = cmutex_vtable();
    Release();
}

void CMutex::DtorDelete() {
    DtorBase();
    static const u64 op_delete = guest::sym("_ZdlPv");
    guest_call(op_delete, {(u64)this});
}

void CMutex::Initialize() {
    if (m_initialized) mutex_assert(0x1a, kAlreadyInitialized);
    m_substance.CtorBase();
    m_initialized = 1;
    m_locked = 0;
    m_lockCount = 0;
    m_owner = 0;
}

bool CMutex::IsInitialized() const { return m_initialized; }

s32 CMutex::LockCounter() const {
    if (!m_initialized) mutex_assert(0xa6, kStrUninitializedObject);
    fence();
    return m_lockCount;
}

FastCriticalSection* CMutex::rSubstance() {
    if (!m_initialized) mutex_assert(0x44, kStrUninitializedObject);
    return &m_substance;
}

const FastCriticalSection* CMutex::crSubstance() const {
    if (!m_initialized) mutex_assert(0x4a, kStrUninitializedObject);
    return &m_substance;
}

void CMutex::Lock() {
    if (!m_initialized) mutex_assert(0x61, kStrUninitializedObject);
    u64 self = Thread::GetCurrentID();
    if (__atomic_load_n(&m_owner, __ATOMIC_RELAXED) != self) {  // (a plain read: only the owner itself can make it equal)
        if (!m_initialized) mutex_assert(0x44, kStrUninitializedObject);
        m_substance.Enter();
        if (t_obs) {
            t_obs->save_pre(this);
            t_obs->fresh = true;
        }
    } else if (t_obs) {
        t_obs->save_pre(this);
    }
    m_owner = self;
    m_locked = 1;
    atomic_add(m_lockCount, 1);
    if (t_obs) t_obs->save_post(this);
}

void CMutex::Unlock() {
    if (!m_initialized) mutex_assert(0x7d, kStrUninitializedObject);
    if (t_obs) t_obs->save_pre(this);
    if (m_lockCount != 1) {
        atomic_add(m_lockCount, -1);
        if (t_obs) t_obs->save_post(this);
        return;
    }
    m_locked = 0;
    m_owner = 0;
    atomic_add(m_lockCount, -1);
    if (!m_initialized) mutex_assert(0x44, kStrUninitializedObject);
    if (t_obs) t_obs->save_post(this);
    m_substance.Leave();
}

bool CMutex::IsLocked() const { return m_locked; }

namespace {

// ---- live checks (sync_check.h) ----

CheckedFn g_lock("_ZN9Framework6CMutex4LockEv"), g_unlock("_ZN9Framework6CMutex6UnlockEv"), g_init("_ZN9Framework6CMutex10InitializeEv"),
    g_is_locked("_ZNK9Framework6CMutex8IsLockedEv"), g_is_init("_ZNK9Framework6CMutex13IsInitializedEv"),
    g_lock_counter("_ZNK9Framework6CMutex11LockCounterEv");

constexpr size_t kLockOff = offsetof(CMutex, m_substance) + offsetof(FastCriticalSection, m_lock);
constexpr size_t kWaitersOff = offsetof(CMutex, m_substance) + offsetof(FastCriticalSection, m_waiters);
constexpr size_t kSemOff = offsetof(CMutex, m_substance) + offsetof(FastCriticalSection, m_sem);

// A shadow CMutex with `state`'s bytes whose semaphore is the shadow's own (a guest Signal or
// sem_destroy on it reaches nothing real; the HLE's host semaphore for it is created on first use
// and destroyed by release_shadow).
CMutex* make_shadow(const u8* state, s32 waiters) {
    auto* sh = (CMutex*)shadow_buffer(0);
    std::memcpy(sh, state, sizeof(CMutex));
    make_shadow_lock(sh->m_substance, waiters);
    return sh;
}
void release_shadow(CMutex* sh) { release_shadow_lock(sh->m_substance); }
int shadow_sem_value(CMutex* sh) {
    int v = 0;
    if (u64 p = sh->m_substance.m_sem.m_pSem) hle_sem_getvalue(p, &v);
    return v;
}

// Lock: the guest from the state the native saw once it held the lock word (the lock word free
// again for a fresh acquire); the bytes after must equal the native's, except the waiter count
// (other threads' waits) and the semaphore pointer (the shadow's own).
void lock_checked(Cpu& c) {
    if (!check_due(g_lock)) return wrap_method<&CMutex::Lock>()(c);
    CheckScope scope;
    Observation obs;
    t_obs = &obs;
    wrap_method<&CMutex::Lock>()(c);
    t_obs = nullptr;
    if (!obs.have_pre || !obs.have_post) return check_result(g_lock, Outcome::Skipped, "no observation");
    if (obs.fresh) {
        s32 free_ = FastCriticalSection::kFree;
        std::memcpy(obs.pre + kLockOff, &free_, 4);
    }
    CMutex* sh = make_shadow(obs.pre, FastCriticalSection::kWaiterBias);
    guest_call(g_lock.orig, {(u64)sh});
    s32 sh_waiters = sh->m_substance.m_waiters;
    std::string why = diff_bytes(obs.post, (const u8*)sh, 0, sizeof(CMutex), {{kWaitersOff, kWaitersOff + 4}, {kSemOff, kSemOff + 8}});
    if (why.empty() && sh_waiters != FastCriticalSection::kWaiterBias) why = "guest waited on the shadow";
    release_shadow(sh);
    check_result(g_lock, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
}

// Unlock: the guest from the state at entry (the caller holds the lock) with the waiter count the
// native read; the bytes it wrote before the release, the released lock word, the waiter count after
// and whether a wakeup was posted must match.
void unlock_checked(Cpu& c) {
    if (!check_due(g_unlock)) return wrap_method<&CMutex::Unlock>()(c);
    CheckScope scope;
    Observation obs;
    t_obs = &obs;
    wrap_method<&CMutex::Unlock>()(c);
    t_obs = nullptr;
    if (!obs.have_pre || !obs.have_post) return check_result(g_unlock, Outcome::Skipped, "no observation");
    auto* pre = (const CMutex*)obs.pre;
    bool released = pre->m_lockCount == 1;
    s32 waiters = released ? obs.waiters_read : pre->m_substance.m_waiters;
    CMutex* sh = make_shadow(obs.pre, waiters);
    guest_call(g_unlock.orig, {(u64)sh});
    // The native's state after: its writes before the release, then the release and the handoff.
    u8 native_after[sizeof(CMutex)];
    std::memcpy(native_after, obs.post, sizeof native_after);
    s32 native_waiters = waiters;
    if (released) {
        s32 free_ = FastCriticalSection::kFree;
        std::memcpy(native_after + kLockOff, &free_, 4);
        if (waiters > FastCriticalSection::kWaiterBias) native_waiters--;
    }
    std::string why = diff_bytes(native_after, (const u8*)sh, 0, sizeof(CMutex), {{kWaitersOff, kWaitersOff + 4}, {kSemOff, kSemOff + 8}});
    if (why.empty() && sh->m_substance.m_waiters != native_waiters)
        why = "waiters " + std::to_string(waiters) + ": native -> " + std::to_string(native_waiters) + ", guest -> " + std::to_string(sh->m_substance.m_waiters);
    if (why.empty() && (shadow_sem_value(sh) > 0) != obs.posted) why = obs.posted ? "native posted a wakeup, guest didn't" : "guest posted a wakeup, native didn't";
    release_shadow(sh);
    check_result(g_unlock, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
}

// Initialize: the guest on a copy of the object as it was before; equal bytes after (the semaphore
// pointer relative to the object). The shadow's semaphore is destroyed again.
void init_checked(Cpu& c) {
    if (!check_due(g_init)) return wrap_method<&CMutex::Initialize>()(c);
    CheckScope scope;
    auto* self = (CMutex*)c.x(0);
    u8 before[sizeof(CMutex)];
    std::memcpy(before, self, sizeof before);
    wrap_method<&CMutex::Initialize>()(c);
    auto* sh = (CMutex*)shadow_buffer(0);
    std::memcpy(sh, before, sizeof before);
    guest_call(g_init.orig, {(u64)sh});
    u64 rel_native = self->m_substance.m_sem.m_pSem ? self->m_substance.m_sem.m_pSem - (u64)self : 0;
    u64 rel_guest = sh->m_substance.m_sem.m_pSem ? sh->m_substance.m_sem.m_pSem - (u64)sh : 0;
    std::string why = diff_bytes((const u8*)self, (const u8*)sh, 0, sizeof(CMutex), {{kSemOff, kSemOff + 8}});
    if (why.empty() && rel_native != rel_guest) why = "m_sem.m_pSem differs";
    release_shadow(sh);
    check_result(g_init, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
}

void is_locked_checked(Cpu& c) {
    if (!check_due(g_is_locked)) return wrap_method<&CMutex::IsLocked>()(c);
    check_getter(c, g_is_locked, wrap_method<&CMutex::IsLocked>(), 0xff);
}
void is_init_checked(Cpu& c) {
    if (!check_due(g_is_init)) return wrap_method<&CMutex::IsInitialized>()(c);
    check_getter(c, g_is_init, wrap_method<&CMutex::IsInitialized>(), 0xff);
}
void lock_counter_checked(Cpu& c) {
    if (!check_due(g_lock_counter)) return wrap_method<&CMutex::LockCounter>()(c);
    check_getter(c, g_lock_counter, wrap_method<&CMutex::LockCounter>(), 0xffffffffu);
}

}  // namespace

NATIVE_METHOD("_ZN4Aska19FastCriticalSectionC2Ev", &FastCriticalSection::CtorBase, "sync: Aska::FastCriticalSection::FastCriticalSection");
NATIVE_METHOD("_ZN4Aska19FastCriticalSectionD2Ev", &FastCriticalSection::Dtor, "sync: Aska::FastCriticalSection::~FastCriticalSection");

NATIVE_METHOD("_ZN9Framework6CMutexC2Ev", &CMutex::Ctor, "sync: Framework::CMutex::CMutex");
NATIVE_METHOD("_ZN9Framework6CMutexD2Ev", &CMutex::DtorBase, "sync: Framework::CMutex::~CMutex");
NATIVE_METHOD("_ZN9Framework6CMutexD0Ev", &CMutex::DtorDelete, "sync: Framework::CMutex::~CMutex (deleting)");
NATIVE_METHOD("_ZN9Framework6CMutex7ReleaseEv", &CMutex::Release, "sync: Framework::CMutex::Release");
NATIVE_FUNCTION_ORIG("_ZN9Framework6CMutex10InitializeEv", init_checked, "sync: Framework::CMutex::Initialize", &g_init.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework6CMutex13IsInitializedEv", is_init_checked, "sync: Framework::CMutex::IsInitialized", &g_is_init.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework6CMutex11LockCounterEv", lock_counter_checked, "sync: Framework::CMutex::LockCounter", &g_lock_counter.orig);
NATIVE_METHOD("_ZN9Framework6CMutex10rSubstanceEv", &CMutex::rSubstance, "sync: Framework::CMutex::rSubstance");
NATIVE_METHOD("_ZNK9Framework6CMutex11crSubstanceEv", &CMutex::crSubstance, "sync: Framework::CMutex::crSubstance");
NATIVE_FUNCTION_ORIG("_ZN9Framework6CMutex4LockEv", lock_checked, "sync: Framework::CMutex::Lock (FastCriticalSection, host atomics)", &g_lock.orig);
NATIVE_FUNCTION_ORIG("_ZN9Framework6CMutex6UnlockEv", unlock_checked, "sync: Framework::CMutex::Unlock", &g_unlock.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework6CMutex8IsLockedEv", is_locked_checked, "sync: Framework::CMutex::IsLocked", &g_is_locked.orig);

}  // namespace soa::native::sync
