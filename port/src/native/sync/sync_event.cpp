// Aska::Event and Aska::CriticalSection: natives over the HLE's pthread mutexes and condition
// variables in place (port/decomp/sync/event.c; hle/thread.h: the same host objects and rules as
// the guest's pthread imports, including the window thread's sliced wait for idle presenting).
#include <sys/time.h>

#include "core/cpu.h"
#include "hle/thread.h"
#include "native/common/guest_std.h"
#include "native/common/native_method.h"
#include "native/sync/sync_check.h"
#include "native/sync/sync_layout.h"

namespace soa::native::sync {

// ---- Aska::Event ----

void Event::Ctor() { m_pMutex = 0; }

bool Event::Create(bool manualReset, bool initialState) {
    if (m_pMutex == 0) {
        hle_mutex_init((u64)m_mutex, 0);
        hle_cond_init((u64)m_cond);
        m_pMutex = (u64)m_mutex;
        m_signaled = initialState;
        m_manualReset = manualReset;
    }
    return true;
}

bool Event::Wait(u32 timeoutMs) const {
    if (m_pMutex == 0) return false;
    {
        ProfNativeWait wait;
        hle_mutex_lock(m_pMutex);
    }
    auto* self = const_cast<Event*>(this);
    if (!m_signaled) {
        ProfNativeWait wait;
        if (timeoutMs == 0) {
            hle_cond_wait((u64)m_cond, m_pMutex);
        } else {
            struct timeval tv;
            if (gettimeofday(&tv, nullptr) < 0) return false;  // (the guest returns still holding the mutex)
            // The guest's absolute time: tv_nsec = (u32)(ms * 1000000) + usec * 1000, not carried into
            // tv_sec (from about 1 s on it is >= 1e9: pthread_cond_timedwait fails with EINVAL at once).
            s64 abstime[2] = {(s64)tv.tv_sec, (s64)(u64)(u32)(timeoutMs * 1000000u) + (s64)tv.tv_usec * 1000};
            hle_cond_timedwait((u64)m_cond, m_pMutex, (u64)abstime);
        }
    } else if (t_obs) {
        t_obs->save_pre(this);
    }
    // Woken, timed out or already signaled: an auto-reset event is cleared either way.
    if (!m_manualReset) self->m_signaled = 0;
    if (t_obs && t_obs->have_pre) t_obs->save_post(this);
    return hle_mutex_unlock(m_pMutex) != 0;
}

bool Event::Set() const {
    if (m_pMutex == 0) return false;
    int r;
    {
        ProfNativeWait wait;
        r = hle_mutex_lock(m_pMutex);
    }
    if (r != 0) return false;
    if (t_obs) t_obs->save_pre(this);
    const_cast<Event*>(this)->m_signaled = 1;
    hle_cond_signal((u64)m_cond);
    if (t_obs) t_obs->save_post(this);
    return hle_mutex_unlock(m_pMutex) == 0;
}

bool Event::Reset() const {
    if (m_pMutex == 0) return false;
    int r;
    {
        ProfNativeWait wait;
        r = hle_mutex_lock(m_pMutex);
    }
    if (r != 0) return false;
    if (t_obs) t_obs->save_pre(this);
    const_cast<Event*>(this)->m_signaled = 0;
    if (t_obs) t_obs->save_post(this);
    return hle_mutex_unlock(m_pMutex) == 0;
}

bool Event::IsSignal() const { return m_pMutex != 0 && m_signaled != 0; }

void Event::Exit() {
    if (m_pMutex == 0) return;
    {
        ProfNativeWait wait;
        hle_mutex_lock(m_pMutex);
    }
    hle_cond_destroy((u64)m_cond);
    hle_mutex_unlock(m_pMutex);
    while (hle_mutex_destroy(m_pMutex) != 0) Thread::SleepU(100);
    m_pMutex = 0;
}

// ---- Aska::CriticalSection ----

void CriticalSection::CtorBase() {
    u64 attr = 1;  // a bionic pthread_mutexattr_t: PTHREAD_MUTEX_RECURSIVE (pthread_mutexattr_settype(&a, 1))
    hle_mutex_init((u64)m_mutex, (u64)&attr);
}

bool CriticalSection::TryEnter() const { return hle_mutex_trylock((u64)m_mutex) == 0; }

namespace {

// ---- live checks (sync_check.h) ----

CheckedFn g_create("_ZN4Aska5Event6CreateEbb"), g_wait("_ZNK4Aska5Event4WaitEj"), g_set("_ZNK4Aska5Event3SetEv"),
    g_reset("_ZNK4Aska5Event5ResetEv");

// A shadow event of this thread: created once by the guest's own Create (its mutex and condition
// variable are private), then given the flags the native saw.
Event* shadow_event() {
    static thread_local Event* ev = nullptr;
    if (!ev) {
        alignas(16) static thread_local u8 buf[sizeof(Event)];
        ev = (Event*)buf;
        guest_call(g_create.orig, {(u64)ev, 0, 0});
    }
    return ev;
}

// Set / Reset / a Wait that found the event signaled: the guest original on a shadow event with the
// flags the native saw while it held the mutex; the flags after and the result must match.
void check_flags(Cpu& c, CheckedFn& f, HostFn native, u64 arg1) {
    CheckScope scope;
    Observation obs;
    t_obs = &obs;
    native(c);
    t_obs = nullptr;
    bool got = c.x(0) & 1;
    if (!obs.have_pre || !obs.have_post) return check_result(f, Outcome::Skipped);  // (no event, or a Wait that waited)
    auto* pre = (const Event*)obs.pre;
    auto* post = (const Event*)obs.post;
    Event* sh = shadow_event();
    if (!sh->m_pMutex) return check_result(f, Outcome::Skipped, "no shadow event");
    sh->m_signaled = pre->m_signaled;
    sh->m_manualReset = pre->m_manualReset;
    bool want = guest_call(f.orig, {(u64)sh, arg1}) & 1;
    if (got == want && sh->m_signaled == post->m_signaled && sh->m_manualReset == post->m_manualReset)
        return check_result(f, Outcome::Ok);
    char m[128];
    snprintf(m, sizeof m, "pre signaled %u manual %u: native -> %u (%d), guest -> %u (%d)", pre->m_signaled, pre->m_manualReset, post->m_signaled, got,
             sh->m_signaled, want);
    check_result(f, Outcome::Mismatch, m);
}

void create_checked(Cpu& c) {
    if (!check_due(g_create)) return wrap_method<&Event::Create>()(c);
    CheckScope scope;
    auto* self = (Event*)c.x(0);
    u64 x1 = c.x(1), x2 = c.x(2);
    bool fresh = self->m_pMutex == 0;
    Event before;
    std::memcpy(&before, self, sizeof before);
    wrap_method<&Event::Create>()(c);
    if (!fresh) return check_result(g_create, Outcome::Skipped);  // (a no-op on an existing event)
    auto* sh = (Event*)shadow_buffer(1);
    std::memcpy(sh, &before, sizeof before);
    u64 want = guest_call(g_create.orig, {(u64)sh, x1, x2}) & 0xff;
    bool ok = (c.x(0) & 0xff) == want && sh->m_pMutex - (u64)sh == self->m_pMutex - (u64)self && sh->m_signaled == self->m_signaled &&
              sh->m_manualReset == self->m_manualReset;
    std::string why = ok ? "" : diff_bytes((const u8*)self, (const u8*)sh, 0x60, 0x62);
    guest_call(guest::sym("_ZN4Aska5Event4ExitEv"), {(u64)sh});  // (frees the shadow's mutex / condition variable)
    check_result(g_create, ok ? Outcome::Ok : Outcome::Mismatch, why);
}

void wait_checked(Cpu& c) {
    if (!check_due(g_wait)) return wrap_method<&Event::Wait>()(c);
    check_flags(c, g_wait, wrap_method<&Event::Wait>(), c.x(1));
}
void set_checked(Cpu& c) {
    if (!check_due(g_set)) return wrap_method<&Event::Set>()(c);
    check_flags(c, g_set, wrap_method<&Event::Set>(), 0);
}
void reset_checked(Cpu& c) {
    if (!check_due(g_reset)) return wrap_method<&Event::Reset>()(c);
    check_flags(c, g_reset, wrap_method<&Event::Reset>(), 0);
}
}  // namespace

NATIVE_METHOD("_ZN4Aska5EventC2Ev", &Event::Ctor, "sync: Aska::Event::Event");
NATIVE_FUNCTION_ORIG("_ZN4Aska5Event6CreateEbb", create_checked, "sync: Aska::Event::Create (HLE pthread_mutex_init / cond_init)", &g_create.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska5Event4WaitEj", wait_checked, "sync: Aska::Event::Wait (HLE cond_wait / timedwait)", &g_wait.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska5Event3SetEv", set_checked, "sync: Aska::Event::Set (HLE cond_signal)", &g_set.orig);
NATIVE_FUNCTION_ORIG("_ZNK4Aska5Event5ResetEv", reset_checked, "sync: Aska::Event::Reset", &g_reset.orig);
// (IsSignal, TryEnter: a branch in the first 8 bytes, so no trampoline to the original: not live-checked)
NATIVE_METHOD("_ZNK4Aska5Event8IsSignalEv", &Event::IsSignal, "sync: Aska::Event::IsSignal");
NATIVE_METHOD("_ZN4Aska5Event4ExitEv", &Event::Exit, "sync: Aska::Event::Exit");
NATIVE_METHOD("_ZN4Aska15CriticalSectionC2Ev", &CriticalSection::CtorBase, "sync: Aska::CriticalSection::CriticalSection (recursive HLE mutex)");
NATIVE_METHOD("_ZNK4Aska15CriticalSection8TryEnterEv", &CriticalSection::TryEnter, "sync: Aska::CriticalSection::TryEnter");

}  // namespace soa::native::sync
