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
#include "native/sync/sync_layout.h"

namespace soa::native::sync {

// One checked guest function: its symbol, the trampoline to the original (set when installed) and
// its counters.
struct CheckedFn {
    const char* sym;
    u64 orig = 0;
    std::atomic<u64> calls{0}, checks{0}, ok{0}, bad{0}, skipped{0}, races{0};
    explicit CheckedFn(const char* s);
};

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

// True when this call is to be checked: the family is on (--live-check sync), the function is in
// only=, its budget isn't spent, it's the every-th call, and no check runs on this thread already.
bool check_due(CheckedFn& f);
// Inside a check on this thread (also live::t_busy, so other families leave the callees alone).
struct CheckScope {
    CheckScope();
    ~CheckScope();
};
enum class Outcome { Ok, Mismatch, Skipped, Race };
// Counts one check's outcome; a mismatch (and the first few skips) is logged with `why`.
void check_result(CheckedFn& f, Outcome o, const std::string& why = {});

// A zeroed, 16-aligned, per-thread scratch buffer for shadows (guest-visible host memory: guest
// memory is identity-mapped). `slot` keeps two shadows apart.
u8* shadow_buffer(int slot);
// "+0xNN: native XX guest YY" for the first differing byte of [from, to) outside `skip` ranges.
std::string diff_bytes(const u8* native, const u8* guest, size_t from, size_t to, std::initializer_list<std::pair<size_t, size_t>> skip = {});

// A read-only method: runs the native, then the guest original on the same object, and compares
// x0 (masked to the result's width); a difference that a rerun of both doesn't reproduce is a race.
void check_getter(Cpu& c, CheckedFn& f, HostFn native, u64 mask);

}  // namespace soa::native::sync
