#pragma once
// A native calling a guest function that is itself a native (of its own subsystem or another one)
// as C++, not through guest_call (port/src/native/README.md "Calls between natives").
//
//   namespace { NativeCallee kAsonMalloc{"data_formats", "_ZN4Aska4ASON6MallocEm"}; }  // namespace scope
//   void* ason_malloc(void* ason, u64 n) {
//       if (kAsonMalloc.direct()) return static_cast<data_formats::ASON*>(ason)->Malloc(n);
//       return (void*)guest_call(kAsonMalloc.addr(), {(u64)ason, n});
//   }
//
// direct() is decided once, when the natives are installed (install_native_functions): true when the
// callee's native was installed there (not with --natives route / none, --natives-skip of its
// subsystem, a false NATIVE_FUNCTION_IF predicate, nor in --selftest, which installs none), no
// --live-check family is on, the GDB stub isn't listening (breakpoints on natives) and SOA_DIRECT_CALLS
// isn't 0. Otherwise the call site takes its guest_call, exactly as before: a run with any live check
// (callees recorded, stubbed, marked or checked as nested callees), a --selftest run and an A/B with a
// subsystem left to the guest all execute what they did before natives called each other as C++.
//
// The C++ a site calls must be what the callee's registered HostFn runs when its family's check is
// off (the member a NATIVE_METHOD / wrap<> binds, a leaf family's `run`); `expect`, when given, is
// that HostFn, and test native/direct-callees checks the registration has it. Every callee's symbol
// must be registered as a native by `subsystem` (the same test).
#include <atomic>
#include <set>
#include <string>
#include <vector>

#include "soaruntime/core/cpu.h"

namespace soa::native {

class NativeCallee {
public:
    NativeCallee(const char* subsystem, const char* sym, HostFn expect = nullptr);
    NativeCallee(const NativeCallee&) = delete;
    NativeCallee& operator=(const NativeCallee&) = delete;

    // Call the native as C++ (see above).
    bool direct() const { return direct_; }
    // The callee's guest entry (looked up on first use), for the guest_call path.
    u64 addr() const {
        u64 a = addr_.load(std::memory_order_relaxed);
        return a ? a : resolve();
    }

    const char* subsystem() const { return subsystem_; }
    const char* sym() const { return sym_; }
    HostFn expect() const { return expect_; }

    // Every NativeCallee constructed (namespace-scope objects: all of them before main).
    static const std::vector<NativeCallee*>& all();
    // Called by install_native_functions with the symbols it installed and whether direct calls are
    // allowed at all (no live check, no GDB stub, SOA_DIRECT_CALLS).
    static void resolve_all(const std::set<std::string>& installed, bool allowed);
    // Tests: switches one callee (to compare both paths in --selftest).
    void set_direct_for_test(bool on) { direct_ = on; }

private:
    u64 resolve() const;

    const char* subsystem_;
    const char* sym_;
    HostFn expect_;
    bool direct_ = false;
    mutable std::atomic<u64> addr_{0};
};

}  // namespace soa::native
