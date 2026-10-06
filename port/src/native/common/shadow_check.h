#pragma once
// Shadow checks: the live check (soa --live-check FAMILY) of natives over shared, stateful guest
// objects (locks, the peripherals' state, the resource list), where the record / replay check of
// live_check.h can't run: replaying a guest original on the real object rewinds memory other
// threads use (a released lock word, a queue another thread fills) and its callees' effects can't
// be played back (a semaphore post is a real wakeup). So a family of these checks
//   - runs the guest original (the hook's trampoline) on a private *shadow* of the object, built
//     from the state the native saw at its linearization point (the object's bytes while it held the
//     object's lock), and compares the shadow's bytes and the result with the native's; or
//   - for read-only methods (getters, list searches under the object's own lock) runs the guest
//     original on the real object right after the native and compares the results; a difference
//     that doesn't reproduce on a rerun of both is a race (another thread changed the object in
//     between), not a mismatch (check_getter).
// A family is a ShadowFamily (a live::Family, so --live-check FAMILY[:every=N][:budget=N][:only=..]
// [:out=FILE] switches and tunes it) with one ShadowFn per checked guest function. Families: sync
// (native/sync/sync_check.h), input, resource.
#include <atomic>
#include <initializer_list>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "core/cpu.h"
#include "native/common/live_check.h"

namespace soa::live {

struct ShadowFn;

// A family of shadow checks: its switch and options (live::Family), its functions and the totals.
class ShadowFamily : public Family {
public:
    ShadowFamily(const char* tag, int every);
    void add_fn(ShadowFn* f);
    void totals();       // after each check: the log line every 1000 checks, out= every 10 s
    void write_counts(); // out=FILE: the totals and per-function counts

private:
    std::vector<ShadowFn*> fns_;
    std::mutex m_;
};

// One checked guest function: its symbol, the trampoline to the original (set when installed: pass
// &fn.orig to NATIVE_FUNCTION_ORIG) and its counters.
struct ShadowFn {
    const char* sym;
    ShadowFamily& fam;
    u64 orig = 0;
    std::atomic<u64> calls{0}, checks{0}, ok{0}, bad{0}, skipped{0}, races{0};
    ShadowFn(ShadowFamily& f, const char* s);
};

// True when this call is to be checked: the family is on, the function is in only=, its budget
// isn't spent, it's the every-th call, and no check runs on this thread already (any family).
bool check_due(ShadowFn& f);
// Inside a check on this thread (also live::t_busy, so other families leave the callees alone).
struct CheckScope {
    CheckScope();
    ~CheckScope();
    CheckScope(const CheckScope&) = delete;
    CheckScope& operator=(const CheckScope&) = delete;
};
enum class Outcome { Ok, Mismatch, Skipped, Race };
// Counts one check's outcome; a mismatch (and the first few skips) is logged with `why`.
void check_result(ShadowFn& f, Outcome o, const std::string& why = {});

// "+0xNN: native XX guest YY" for the first differing byte of [from, to) outside the `skip` ranges
// ([lo, hi) pairs); empty when equal.
std::string diff_bytes(const u8* native, const u8* guest, size_t from, size_t to, std::initializer_list<std::pair<size_t, size_t>> skip = {});

// A read-only method: runs the native, then the guest original on the same arguments, and
// compares x0 (masked to the result's width); a difference a rerun of both doesn't reproduce is a
// race. `out` / `out_bytes`: an out-parameter (the register holding its pointer, its size; reg < 0:
// none) compared too (the guest writes it after the native: the native's bytes are kept aside).
void check_getter(Cpu& c, ShadowFn& f, HostFn native, u64 mask, int out_reg = -1, size_t out_bytes = 0);

// A check's per-thread scratch object (an observation, a shadow, an output buffer), made on the
// heap on the thread's first check: one per (T, Tag) and thread. Never `static thread_local T buf`
// for anything big: static TLS is carved out of every thread's stack by glibc, and guest threads
// run the JIT on 256 KiB host stacks (runtime/src/hle/libc_thread.cpp), each guest_call level
// taking ~1.7 KB. 150 KB of input's thread_local check buffers left the game thread ~90 KB and
// crashed session:tower (port/src/native/README.md "Live checks"; selftest runtime/guest-thread-host-stack).
// Destroyed at the thread's end (core/thread_record.h: thread_object).
template <typename T, typename Tag = T>
T& thread_scratch() {
    return thread_object<T, Tag>();
}

}  // namespace soa::live
