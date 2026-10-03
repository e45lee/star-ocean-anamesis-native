#pragma once
// Self-tests of the runtime itself (host-side behaviour of the HLE, the frontend, ...), run by the
// host program's test runner: `soa --selftest` runs them first, in registration (link) order,
// before the port's NATIVE_TESTs (port/src/native/common/test.cpp). A runtime test needs no
// game code; a test that needs the guest library or port code is a NATIVE_TEST in the port.
//
//   RUNTIME_TEST("audio/opensl-queue-drains") { ...; if (bad) t.fail("..."); }
#include <vector>

namespace soa {

// What a runtime test reports to: the host's runner implements report_failure().
class RuntimeTestContext {
public:
    virtual ~RuntimeTestContext() = default;
    // Records a failure (the test continues so all mismatches get reported).
    void fail(const char* fmt, ...) __attribute__((format(printf, 2, 3)));
    template <typename A, typename B>
    bool expect_eq(const A& a, const B& b, const char* what) {
        if (a == b) return true;
        fail("%s mismatch", what);
        return false;
    }
    int failures() const { return failures_; }

protected:
    virtual void report_failure(const char* msg) = 0;

private:
    int failures_ = 0;
};

struct RuntimeTest {
    const char* name;
    void (*fn)(RuntimeTestContext&);
};

bool register_runtime_test(const RuntimeTest& t);
// Every registered runtime test, in registration order.
const std::vector<RuntimeTest>& runtime_tests();

}  // namespace soa

#define RUNTIME_CONCAT_(a, b) a##b
#define RUNTIME_CONCAT(a, b) RUNTIME_CONCAT_(a, b)
#define RUNTIME_TEST(name)                                                                             \
    static void RUNTIME_CONCAT(runtime_test_fn_, __LINE__)(::soa::RuntimeTestContext & t);              \
    static bool RUNTIME_CONCAT(runtime_test_reg_, __LINE__) =                                          \
        ::soa::register_runtime_test({name, &RUNTIME_CONCAT(runtime_test_fn_, __LINE__)});             \
    static void RUNTIME_CONCAT(runtime_test_fn_, __LINE__)(::soa::RuntimeTestContext & t)
