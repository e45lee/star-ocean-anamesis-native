#pragma once
// Shadow-replay live checks (soa --live-check FAMILY): the family-agnostic part of the check that
// sync introduced (native/sync/sync_check.h) and kernel's dispatcher uses too.
//
// Stateful primitives can't be checked by live_check.h's record / replay: replaying a guest Lock or
// Post on the real object rewinds memory other threads use. A shadow check instead has the native
// record what it saw at its linearization point (holding the lock), builds a private *shadow* of the
// object with exactly that state, runs the guest original (the hook's trampoline) on the shadow and
// compares. This header has the switch, the counters and the comparison helpers; each family builds
// its own shadows.
#include <atomic>
#include <cstdio>
#include <initializer_list>
#include <string>
#include <utility>

#include "core/cpu.h"
#include "native/common/live_check.h"

namespace soa::live {

// A family checked by shadow replays: --live-check <tag> switches it on and sets every= / budget= /
// only= / out=. Its record / replay machinery isn't used; its stats are the totals.
struct ShadowFamily {
    ShadowFamily(const char* tag, int every);
    Family fam;
    void summary_file();  // the per-function counts to out=
};

// One checked guest function: its symbol, the trampoline to the original (set when installed) and
// its counters.
struct CheckedFn {
    ShadowFamily* family;
    const char* sym;
    u64 orig = 0;
    std::atomic<u64> calls{0}, checks{0}, ok{0}, bad{0}, skipped{0}, races{0};
    CheckedFn(ShadowFamily& f, const char* s);
};

// True when this call is to be checked: the family is on, the function is in only=, its budget isn't
// spent, it's the every-th call, and no check (of any family) runs on this thread already.
bool check_due(CheckedFn& f);
// Inside a check on this thread (also live::t_busy, so other families leave the callees alone).
struct CheckScope {
    CheckScope();
    ~CheckScope();
};
bool in_shadow_check();  // this thread is inside a CheckScope
enum class Outcome { Ok, Mismatch, Skipped, Race };
// Counts one check's outcome; a mismatch (and the first few skips) is logged with `why`.
void check_result(CheckedFn& f, Outcome o, const std::string& why = {});

// "+0xNN: native XX guest YY" for the first differing byte of [from, to) outside `skip` ranges.
std::string diff_bytes(const u8* native, const u8* guest, size_t from, size_t to, std::initializer_list<std::pair<size_t, size_t>> skip = {});

// A read-only method: runs the native, then the guest original on the same object, and compares
// x0 (masked to the result's width); a difference that a rerun of both doesn't reproduce is a race.
void check_getter(Cpu& c, CheckedFn& f, HostFn native, u64 mask);

}  // namespace soa::live
