#pragma once
// The live check of the info natives (soa --live-check info[:every=N][:budget=N][:only=..][:out=FILE]): a
// run-both family (native/common/live_run_both.h): each checked call runs the native, then the guest
// original (its hook's trampoline) on the same arguments (the checked natives only read), and the
// results are compared.
#include "native/common/live_run_both.h"

namespace soa::native::info {

live::RunBothFamily& fam();
using Fn = live::RunBothFamily::Fn;
using Outcome = live::RunBothFamily::Outcome;

}  // namespace soa::native::info
