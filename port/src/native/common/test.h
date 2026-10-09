#pragma once
// Differential tests for native replacements: each test runs the original guest (ARM64)
// function and the native C++ one on the same inputs and compares the results.
//
// Run with `soa --selftest [substring]`. The library is loaded *without* native replacements
// so guest symbols still point at the original code.
#include <cstdint>
#include <functional>
#include <random>
#include <string>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/loader.h"
#include "native/common/native.h"

namespace soa {

class TestContext {
public:
    explicit TestContext(LoadedLib& lib, u64 seed) : lib_(lib), rng_(seed) {}

    // Guest function address by mangled symbol (fails the test if missing).
    u64 sym(const char* name);
    u64 call(const char* name, std::initializer_list<u64> args) { return guest_call(sym(name), args); }

    GuestResult call(const char* name, const GuestArgs& args) { return guest_call(sym(name), args); }

    std::mt19937_64& rng() { return rng_; }
    u64 rand_u64() { return rng_(); }
    int rand_int(int lo, int hi) { return std::uniform_int_distribution<int>(lo, hi)(rng_); }
    std::vector<uint8_t> rand_bytes(size_t n, int alphabet = 256);

    // Records a failure (the test continues so all mismatches get reported).
    void fail(const char* fmt, ...) __attribute__((format(printf, 2, 3)));
    template <typename A, typename B>
    bool expect_eq(const A& a, const B& b, const char* what) {
        if (a == b) return true;
        fail("%s mismatch", what);
        return false;
    }
    int failures() const { return failures_; }

private:
    LoadedLib& lib_;
    std::mt19937_64 rng_;
    int failures_ = 0;
};

struct NativeTest {
    const char* name;
    void (*fn)(TestContext&);
};

bool register_native_test(const NativeTest& t);

// A hook that --selftest installs before the game starts (natives are not installed then), for
// tests that must run on a game thread at a known point, e.g. between two UI frames. `fn`
// replaces the guest function; *original receives a trampoline that runs the original code.
struct TestHook {
    const char* symbol;
    HostFn fn;
    u64* original;
    bool optional = false;  // skip (with a warning) instead of failing when it can't be installed
};
bool register_test_hook(const TestHook& h);
void install_test_hooks(LoadedLib& lib);
// Runs all tests whose name contains `filter`; returns the number of failing tests.
int run_native_tests(LoadedLib& lib, const std::string& filter);
// The running test's context (nullptr outside run_native_tests), for helpers that can't take a
// TestContext& but must fail the test, e.g. on missing test data.
TestContext* current_test_context();

}  // namespace soa

#define NATIVE_TEST_HOOK(sym, fn, original) \
    static bool NATIVE_CONCAT(native_test_hook_, __LINE__) = ::soa::register_test_hook({sym, fn, original})

#define NATIVE_TEST(name)                                                                              \
    static void NATIVE_CONCAT(native_test_fn_, __LINE__)(::soa::TestContext & t);                      \
    static bool NATIVE_CONCAT(native_test_reg_, __LINE__) =                                            \
        ::soa::register_native_test({name, &NATIVE_CONCAT(native_test_fn_, __LINE__)});                \
    static void NATIVE_CONCAT(native_test_fn_, __LINE__)(::soa::TestContext & t)
