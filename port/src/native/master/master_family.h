#pragma once
// The live check of the master natives (soa --live-check master[:every=N][:budget=N][:only=..][:out=FILE]):
// a run-both family (native/common/live_run_both.h). Each native runs first, for real; then the guest
// original (its hook's trampoline) runs on a private copy of what the call changes, and the two are
// compared (master_element.cpp: an element's bytes, its strings by representation, its property list
// relative to the element). Nested natives run unchecked inside a check (live::t_busy).
#include "native/common/live_run_both.h"

namespace soa::native::master {

live::RunBothFamily& fam();
// The family as a live::Family (live::out_call's recorder; the run-both checks don't record).
live::Family& family();
using Fn = live::RunBothFamily::Fn;
using Outcome = live::RunBothFamily::Outcome;

}  // namespace soa::native::master
