#pragma once
// Run-both live checks (live_check.h's second kind): a family whose checks run the native, then the
// guest original (the hook's trampoline) on the same inputs (or on a private copy of the object the
// call changes), and compare. For natives the record / replay check can't replay (a property list
// walked through vtables, strings re-allocated by guest helpers, sync primitives) or that don't need
// it (pure readers). The family owns the switches (--live-check TAG[:every=N][:budget=N][:only=..]
// [:out=FILE]), the per-function counters, the guard against nested checks (live::t_busy, shared
// with every family) and the counts file; how a function is checked is its native's business.
//
//   live::RunBothFamily& fam();                       // a function-local static (natives in several files)
//   static live::RunBothFamily::Fn f(fam(), "_ZN...");  // one per checked guest function
//   NATIVE_FUNCTION_ORIG(f.sym, host, "note", &f.orig);  // the trampoline the check runs
//   if (fam().due(f)) { live::RunBothFamily::Scope s; ...native...; ...guest_call(f.orig, ...)...;
//                       fam().result(f, outcome, why); }
//
// (native/sync/sync_check.h is the same pattern with sync's own shadow objects; it predates this.)
#include <atomic>
#include <mutex>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "native/common/live_check.h"

namespace soa::live {

class RunBothFamily {
public:
    // One checked guest function: its symbol, the trampoline to the original (set when installed)
    // and its counters.
    struct Fn {
        const char* sym;
        u64 orig = 0;
        std::atomic<u64> calls{0}, checks{0}, ok{0}, bad{0}, skipped{0}, races{0};
        Fn(RunBothFamily& fam, const char* s);
    };
    enum class Outcome { Ok, Mismatch, Skipped, Race };

    RunBothFamily(const char* tag, int every);

    // True when this call is to be checked: the family is on, the function is in only=, its budget
    // isn't spent, it's the every-th call, its original is installed and no check runs on this
    // thread already (live::t_busy, any family).
    bool due(Fn& f) {
        if (__builtin_expect(!fam_.on.load(std::memory_order_relaxed), 1)) return false;
        return due_slow(f);
    }
    bool on() const { return fam_.on.load(std::memory_order_relaxed); }
    // Inside a check on this thread (live::t_busy: nested natives run unchecked).
    struct Scope {
        Scope() { t_busy = true; }
        ~Scope() { t_busy = false; }
        Scope(const Scope&) = delete;
        Scope& operator=(const Scope&) = delete;
    };
    // Counts one check's outcome; a mismatch (and the first few skips) is logged with `why`.
    void result(Fn& f, Outcome o, const std::string& why = {});
    // "+0xNN: native XX guest YY" for the first differing byte of [0, n), or "".
    static std::string diff_bytes(const void* native, const void* guest, size_t n);

    Family& family() { return fam_; }

private:
    bool due_slow(Fn& f);
    void totals();
    void summary_file();

    Family fam_;
    std::mutex m_, file_m_;
    std::vector<Fn*> fns_;
    std::atomic<s64> last_file_{0};  // when the counts file was last written (time())
};

}  // namespace soa::live
