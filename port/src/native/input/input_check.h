#pragma once
// The live check of the input natives (soa --live-check input[:every=N][:budget=N][:only=..][:out=FILE]).
//
// A shadow check (native/common/shadow_check.h): the peripherals are shared with the
// PeripheralManager thread (it writes the pad's back buffer and the touch panel's messages every 8 ms
// under the peripheral's FastCriticalSection), so a guest original can't be replayed on the real
// object. A locked native notes the object's bytes while it holds the lock (t_obs: before and after
// its own writes); the check runs the guest original on a private shadow built from the "before"
// bytes (the lock word free, sync's make_shadow_lock: no waiters, the semaphore the shadow's own) and
// compares the shadow with the "after" bytes and the results. The lock word, the waiter count and the
// semaphore pointer are left out of the comparison: the enter / leave are sync's
// FastCriticalSection::Enter / Leave, whose hand-offs sync's own check covers (CMutex::Lock / Unlock).
#include <cstring>

#include "native/common/native_method.h"
#include "native/common/shadow_check.h"
#include "native/input/input_layout.h"
#include "native/sync/sync_check.h"

namespace soa::native::input {

live::ShadowFamily& family();
struct CheckedFn : live::ShadowFn {
    explicit CheckedFn(const char* s) : ShadowFn(family(), s) {}
};

// What a locked native saw while it held its object's lock (filled when t_obs is set, by a check).
struct Observation {
    static constexpr size_t kMax = sizeof(TouchPanel);
    alignas(16) u8 pre[kMax];   // the object's bytes once the lock was held, before the native's writes
    alignas(16) u8 post[kMax];  // ... after them, before the release
    bool have_pre = false, have_post = false;
    template <typename T>
    void save_pre(const T* o) {
        static_assert(sizeof(T) <= kMax);
        std::memcpy(pre, (const void*)o, sizeof(T));
        have_pre = true;
    }
    template <typename T>
    void save_post(const T* o) {
        static_assert(sizeof(T) <= kMax);
        std::memcpy(post, (const void*)o, sizeof(T));
        have_post = true;
    }
};
extern thread_local Observation* t_obs;

// The byte ranges of a peripheral's lock a shadow comparison leaves out: the lock word, the waiters,
// the semaphore pointer (BasePeripheral::m_cs at +0x08).
inline constexpr size_t kLockWordOff = offsetof(BasePeripheral, m_cs) + offsetof(FastCriticalSection, m_lock);
inline constexpr size_t kSemPtrOff = offsetof(BasePeripheral, m_cs) + offsetof(FastCriticalSection, m_sem);

// A per-thread, 16-aligned shadow of a peripheral (zeroed).
u8* shadow_object();

// The check of a locked mutator: native member M of peripheral class T (its first member `base`, a
// BasePeripheral), then the guest original on a shadow of the "before" state with the same
// arguments; the shadow must equal the "after" state outside the lock's words.
template <typename T, auto M>
void locked_checked(Cpu& c, CheckedFn& f) {
    if (!live::check_due(f)) return wrap_method<M>()(c);
    live::CheckScope scope;
    static thread_local Observation obs;
    obs.have_pre = obs.have_post = false;
    u64 x[4] = {c.x(0), c.x(1), c.x(2), c.x(3)};
    t_obs = &obs;
    wrap_method<M>()(c);
    t_obs = nullptr;
    if (!obs.have_pre || !obs.have_post) return live::check_result(f, live::Outcome::Skipped, "no observation");
    auto* sh = (T*)shadow_object();
    std::memcpy((void*)sh, obs.pre, sizeof(T));
    sh->base.m_cs.m_lock = FastCriticalSection::kFree;
    sync::make_shadow_lock(sh->base.m_cs);
    guest_call(f.orig, {(u64)sh, x[1], x[2], x[3]});
    std::string why = live::diff_bytes(obs.post, (const u8*)sh, 0, sizeof(T), {{kLockWordOff, kLockWordOff + 8}, {kSemPtrOff, kSemPtrOff + 8}});
    sync::release_shadow_lock(sh->base.m_cs);
    live::check_result(f, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}

}  // namespace soa::native::input
