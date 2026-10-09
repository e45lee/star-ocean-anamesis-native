#pragma once
// Test helper: stubbing guest callees for differential tests of code with side effects.
//
// A differential test runs the original guest function and its native replacement on the same
// state. When that function calls into subsystems that can't run in the self-test (UI, sound,
// scene graph), `stub()` redirects the callee: while a `StubSession` is active on the calling
// thread, calls to it are logged (name + normalised arguments) and answered by a host
// behaviour; on every other thread, or with no session, the original code still runs (through
// a relocated-prologue trampoline). Both sides of the test reach the callee at the same guest
// address, so the guest and native runs produce comparable call logs.
//
// `fake_function()` makes a guest-callable address for fake vtables that behaves the same way.
//
// Hooks stay installed for the rest of the process; they are only meant for --selftest.
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "soaruntime/core/cpu.h"

namespace soa::native {

struct StubSession {
    // Called for a stubbed function when a session is active; returns the result registers
    // (defaults: log the call, return 0 in x0 and s0).
    using Behaviour = std::function<void(Cpu& c)>;

    StubSession();
    ~StubSession();
    StubSession(const StubSession&) = delete;

    std::vector<std::string> log;
    // Renders a pointer-sized argument for the log (so that the two sides' logs compare
    // equal); default: hex.
    std::function<std::string(u64)> fmt_ptr;
    // Per-function behaviour by stub name.
    std::map<std::string, Behaviour> behave;
    // How many integer / float argument registers each stub logs (by name); default 4 / 0.
    std::map<std::string, std::pair<int, int>> arity;
    // If non-empty, only these stubs are answered by the session; calls to any other stubbed
    // function (hooks stay installed for the whole process, so earlier tests' stubs are still
    // there) run the original code, as they would with no session.
    std::set<std::string> only;

    static StubSession* current();
    void record(const char* name, Cpu& c);
};

// Hooks the guest function `mangled` (once) so calls from a thread with an active StubSession
// go to that session. `name` is how the call is logged. Returns false if the function's
// prologue can't be relocated (then it's left alone).
bool stub(const char* mangled, const char* name, int n_int = 4, int n_float = 0);
bool stub_at(u64 addr, const char* name, int n_int = 4, int n_float = 0);
// The trampoline running the original code of a function hooked by stub()/stub_at() (0 if it
// isn't stubbed): lets a test call the unstubbed original, e.g. as the guest reference.
u64 stub_original(u64 addr);
// The name the stub at `addr` currently answers to ("" if not stubbed): the latest stub() call
// for a function names it, so a test that stubs a function another test file stubbed too
// should look the name up after its stub() call.
std::string stub_name(u64 addr);
// Marks the stub at `addr` exclusive: sessions without `only` no longer answer it (they run the
// original), so a test stubbing a widely used function (gDoAssert, operator delete, ...) doesn't
// change later tests whose sessions answer every stub. Stubbing the function again clears it.
void stub_set_exclusive(u64 addr, bool on);

// Like stub(), but only sessions whose `only` set names it answer it; sessions without `only`
// (and other threads) run the original. For callees many other tests reach (asserts, frees), so
// that installing the hook doesn't change their logs. A later ordinary stub() of the same
// function turns it into an ordinary stub (with that name); a function another test already
// stubbed is left as it is (its name must then match the one in `only`).
bool stub_isolated(const char* mangled, const char* name, int n_int = 4, int n_float = 0);
bool stub_isolated_at(u64 addr, const char* name, int n_int = 4, int n_float = 0);

// Like stub(), but a session that has no behaviour for `name` runs the original code (unlogged),
// e.g. for allocators that only some tests replace.
bool stub_passthrough(const char* mangled, const char* name, int n_int = 4);
// The name `addr` was first stubbed under ("" if it isn't stubbed): stubs are process-wide, so a
// test stubbing a function another test already stubbed must use that name in its sessions.
std::string stub_name(u64 addr);

// A guest-callable fake function (for fake vtables) that logs as `name`.
u64 fake_function(const char* name, int n_int = 1, int n_float = 0);

}  // namespace soa::native
