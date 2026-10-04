#pragma once
// The live check of the sync natives (soa --live-check sync[:every=N][:budget=N][:only=..][:out=FILE]).
//
// The record / replay check of live_check.h can't run sync primitives: replaying a guest Lock or
// Set on the real object rewinds memory other threads use (a released lock word, a cleared event)
// and its callees' effects can't be played back (a cond_signal is a real wakeup). So a sync check
// replays the guest original on a private *shadow* of the object instead:
//   - the native records what it saw at its linearization point (an Observation: the object's bytes
//     at the moment it held the lock, the waiter count it read, whether it posted the semaphore),
//     through the thread's t_obs, which only a check sets;
//   - the check builds a shadow with exactly that state (an embedded semaphore re-pointed at the
//     shadow's own, so a guest Signal / sem_destroy touches nothing real), runs the guest original
//     (the hook's trampoline) on it, and compares the shadow's bytes and result with the native's;
//   - read-only methods (IsLocked, IsSignal, IsReady, ...) run the guest original on the real object
//     right after the native; a difference that doesn't reproduce on a rerun is a race (another
//     thread changed the object in between), not a mismatch.
// Blocking paths (a Wait that had to wait, a contended Lock's wait itself) are checked from the
// point they acquire: the guest runs from the state the native saw once it got the lock.
#include <atomic>
#include <cstring>
#include <string>

#include "core/cpu.h"
#include "native/common/shadow_check.h"
#include "native/sync/sync_layout.h"

namespace soa::native::sync {

// The family (--live-check sync; native/common/shadow_check.h has the switch, the counters, the
// byte comparison and the getter check).
live::ShadowFamily& family();
// One checked guest function of the family.
struct CheckedFn : live::ShadowFn {
    explicit CheckedFn(const char* s) : ShadowFn(family(), s) {}
};
using live::check_due;
using live::check_getter;
using live::check_result;
using live::CheckScope;
using live::diff_bytes;
using live::Outcome;

// What a mutator saw at its linearization point (filled by the native when t_obs is set).
struct Observation {
    u8 pre[sizeof(CMutex)];   // the object's bytes at the moment it held the lock (before writing)
    u8 post[sizeof(CMutex)];  // ... after its own writes (CMutex::Unlock: before the release)
    bool have_pre = false, have_post = false;
    bool fresh = false;       // CMutex::Lock: acquired the lock word (not a recursive enter)
    s32 waiters_read = 0;     // CMutex::Unlock: the waiter count it decided on
    bool posted = false;      // ... whether it handed a wakeup to the semaphore
    template <typename T>
    void save_pre(const T* o) {
        std::memcpy(pre, (const void*)o, sizeof(T));
        have_pre = true;
    }
    template <typename T>
    void save_post(const T* o) {
        std::memcpy(post, (const void*)o, sizeof(T));
        have_post = true;
    }
};
// Set by a check around its native run; the natives note their observations here.
extern thread_local Observation* t_obs;

// Set by another family's shadow check around a guest replay of a blocking caller (kernel's
// SendMessage: it waits on an event only a worker would set): Event::Wait on this thread then
// returns at once, as if the event were signaled.
extern thread_local bool t_replay_no_wait;

// A zeroed, 16-aligned, per-thread scratch buffer for shadows (guest-visible host memory: guest
// memory is identity-mapped). `slot` keeps two shadows apart.
u8* shadow_buffer(int slot);
// A FastCriticalSection of a shadow object made ready for a guest original to run on it: `waiters`
// waiters and the semaphore the shadow's own (a guest Signal / sem_destroy on it reaches nothing
// real; the HLE's host semaphore for it is created here when the original had one); the lock word is
// the caller's. release_shadow_lock destroys that host semaphore again.
void make_shadow_lock(FastCriticalSection& cs, s32 waiters = FastCriticalSection::kWaiterBias);
void release_shadow_lock(FastCriticalSection& cs);

}  // namespace soa::native::sync
