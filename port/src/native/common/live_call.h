#pragma once
// Outgoing calls from readable natives that a live check must see (live_check.h).
//
//   u64 p = live::out_call(family(), new_array_nothrow, {size, nothrow_tag});
//
// Inside a live check (live::t_busy on this thread) the call goes through live::ACall, so the
// record / replay check records it and stubs it on the replay; otherwise it is a plain guest_call
// (which calls a replaced callee's host function directly). Outside the JIT (a --selftest body:
// no current CPU) it is a plain guest_call as well. Integer / pointer arguments only.
#include <initializer_list>

#include "soaruntime/core/cpu.h"
#include "native/common/live_check.h"

namespace soa::live {

inline u64 out_call(Family& fam, u64 target, std::initializer_list<u64> args) {
    if (__builtin_expect(!t_busy, 1) || !current_cpu()) return guest_call(target, args);
    ACall a(fam);
    for (u64 v : args) a.i(v);
    return a.call(target);
}

}  // namespace soa::live
