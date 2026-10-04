// Aska::Semaphore and Aska::Mutex (a binary semaphore): natives over the HLE's semaphores
// (port/decomp/sync/event.c). The guest's sem_t holds nothing the host uses: the HLE keeps the host
// semaphore in a side table keyed by the sem_t's guest address (hle/thread.h), the same one the
// guest's sem_* imports reach, so native and guest calls on one semaphore interoperate.
#include "core/cpu.h"
#include "hle/thread.h"
#include "native/common/native_method.h"
#include "native/sync/sync_check.h"
#include "native/sync/sync_layout.h"

namespace soa::native::sync {

// ---- Aska::Semaphore ----

void Semaphore::CtorBase() { m_pSem = 0; }

void Semaphore::Dtor() { Exit(); }

void Semaphore::Exit() {
    if (m_pSem) {
        hle_host_sem_destroy(m_pSem);  // the guest's sem_destroy (the HLE's returns 0)
        m_pSem = 0;
    }
}

bool Semaphore::Create(s32 initial, s32 /*max: unused*/) {
    u64 sem = (u64)m_sem;
    if (hle_host_sem_init(sem, (unsigned)initial) != 0) return false;
    m_pSem = sem;
    return true;
}

s32 Semaphore::Wait() const {
    if (!m_pSem) return 0;
    ProfNativeWait wait;
    return hle_sem_wait(m_pSem);
}

bool Semaphore::WaitNonBlocking() const { return m_pSem && hle_sem_trywait(m_pSem) == 0; }

bool Semaphore::IsReady() const { return m_pSem != 0; }

bool Semaphore::Polling() const {
    if (!m_pSem) return false;
    int value;  // (the guest's stack slot: read even when sem_getvalue failed; the HLE's never does)
    int r = hle_sem_getvalue(m_pSem, &value);
    return r == 0 && value > 0;
}

s32 Semaphore::Signal() const { return m_pSem ? hle_sem_post(m_pSem) : 0; }

u32 Semaphore::Signal_Legacy() const {
    if (!m_pSem) return 0;
    u32 first = *(const u32*)m_pSem;  // the guest sem_t's first word (the HLE never writes it)
    hle_sem_post(m_pSem);
    return first;
}

// ---- Aska::Mutex ----

void Mutex::CtorBase() {
    m_sem.CtorBase();
    m_sem.Create(1, 1);
}
void Mutex::DtorBase() {
    m_sem.Exit();
    m_sem.Dtor();
}
s32 Mutex::Lock() { return m_sem.Wait(); }
bool Mutex::TryLock() { return m_sem.WaitNonBlocking(); }
s32 Mutex::Unlock() { return m_sem.Signal(); }

namespace {

// ---- live checks (sync_check.h) ----

CheckedFn g_create("_ZN4Aska9Semaphore6CreateEii"), g_ready("_ZNK4Aska9Semaphore7IsReadyEv");

// Create on a zeroed shadow: the result and m_pSem (relative to the object) must match; the
// shadow's host semaphore is destroyed again.
void create_checked(Cpu& c) {
    if (!check_due(g_create)) return wrap_method<&Semaphore::Create>()(c);
    CheckScope scope;
    u64 x1 = c.x(1), x2 = c.x(2);
    auto* self = (Semaphore*)c.x(0);
    wrap_method<&Semaphore::Create>()(c);
    u32 got = (u32)c.x(0) & 0xff;
    auto* sh = (Semaphore*)shadow_buffer(0);
    u32 want = (u32)guest_call(g_create.orig, {(u64)sh, x1, x2}) & 0xff;
    bool same_ptr = (self->m_pSem ? self->m_pSem - (u64)self : 0) == (sh->m_pSem ? sh->m_pSem - (u64)sh : 0);
    if (sh->m_pSem) hle_host_sem_destroy(sh->m_pSem);
    if (got == want && same_ptr) return check_result(g_create, Outcome::Ok);
    check_result(g_create, Outcome::Mismatch, "result " + std::to_string(got) + " vs " + std::to_string(want) + (same_ptr ? "" : ", m_pSem differs"));
}

void ready_checked(Cpu& c) {
    if (!check_due(g_ready)) return wrap_method<&Semaphore::IsReady>()(c);
    check_getter(c, g_ready, wrap_method<&Semaphore::IsReady>(), 0xff);
}
}  // namespace

// The C1 / D1 aliases share the C2 / D2 addresses: one symbol each.
NATIVE_METHOD("_ZN4Aska9SemaphoreC2Ev", &Semaphore::CtorBase, "sync: Aska::Semaphore::Semaphore");
NATIVE_METHOD("_ZN4Aska9SemaphoreD2Ev", &Semaphore::Dtor, "sync: Aska::Semaphore::~Semaphore");
NATIVE_METHOD("_ZN4Aska9Semaphore4ExitEv", &Semaphore::Exit, "sync: Aska::Semaphore::Exit");
NATIVE_FUNCTION_ORIG("_ZN4Aska9Semaphore6CreateEii", create_checked, "sync: Aska::Semaphore::Create", &g_create.orig);
NATIVE_METHOD("_ZNK4Aska9Semaphore4WaitEv", &Semaphore::Wait, "sync: Aska::Semaphore::Wait (HLE sem_wait)");
NATIVE_METHOD("_ZNK4Aska9Semaphore15WaitNonBlockingEv", &Semaphore::WaitNonBlocking, "sync: Aska::Semaphore::WaitNonBlocking");
NATIVE_FUNCTION_ORIG("_ZNK4Aska9Semaphore7IsReadyEv", ready_checked, "sync: Aska::Semaphore::IsReady", &g_ready.orig);
// (Polling: a branch in the first 8 bytes, so no trampoline to the original: not live-checked)
NATIVE_METHOD("_ZNK4Aska9Semaphore7PollingEv", &Semaphore::Polling, "sync: Aska::Semaphore::Polling");
NATIVE_METHOD("_ZNK4Aska9Semaphore6SignalEv", &Semaphore::Signal, "sync: Aska::Semaphore::Signal (HLE sem_post)");
NATIVE_METHOD("_ZNK4Aska9Semaphore13Signal_LegacyEv", &Semaphore::Signal_Legacy, "sync: Aska::Semaphore::Signal_Legacy");

NATIVE_METHOD("_ZN4Aska5MutexC2Ev", &Mutex::CtorBase, "sync: Aska::Mutex::Mutex");
NATIVE_METHOD("_ZN4Aska5MutexD2Ev", &Mutex::DtorBase, "sync: Aska::Mutex::~Mutex");
NATIVE_METHOD("_ZN4Aska5Mutex4LockEv", &Mutex::Lock, "sync: Aska::Mutex::Lock");
NATIVE_METHOD("_ZN4Aska5Mutex7TryLockEv", &Mutex::TryLock, "sync: Aska::Mutex::TryLock");
NATIVE_METHOD("_ZN4Aska5Mutex6UnlockEv", &Mutex::Unlock, "sync: Aska::Mutex::Unlock");

}  // namespace soa::native::sync
