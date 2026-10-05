#pragma once
// The server library's unit tests (library code): a registry with the port's NATIVE_TEST API
// (port/src/native/common/test.h: t.fail, t.expect_eq, t.rand_u64, ...), so the test files read the
// same in both places. The tests need no guest: `soa-server --selftest [filter]` runs them alone,
// and `soa --selftest` runs them after its own (port/src/native/common/test.cpp).
//
// Library test sources include "soaserver/native_test.h" for the NATIVE_TEST spelling.
#include <cstdint>
#include <random>
#include <string>
#include <vector>

namespace soa::server::testing {

class Context {
public:
    Context(const char* name, uint64_t seed) : name_(name), rng_(seed) {}

    // The test's RNG (seeded from its name) and draws from it: a u64, an int in [lo, hi], `n` bytes
    // below `alphabet`.
    std::mt19937_64& rng() { return rng_; }
    uint64_t rand_u64() { return rng_(); }
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
    // Marks the test skipped, with why (its input is absent: e.g. the 3.7.0 download in work/, which
    // is local data, not in git). The caller returns right after; a skip is neither a pass nor a
    // failure ("skip" line; counted apart in the summary).
    void skip(const char* fmt, ...) __attribute__((format(printf, 2, 3)));
    int failures() const { return failures_; }
    bool skipped() const { return skipped_; }
    // "ok  ", "FAIL" or "skip": the runners' status column.
    const char* status() const { return failures_ ? "FAIL" : skipped_ ? "skip" : "ok  "; }
    const char* name() const { return name_; }

private:
    const char* name_;
    std::mt19937_64 rng_;
    int failures_ = 0;
    bool skipped_ = false;
};

struct Test {
    const char* name;
    // The test body.
    void (*fn)(Context&);
};

// Adds a test (SOASERVER_TEST does); returns true for the static initialiser.
bool register_test(const Test& t);
// In registration (link) order.
const std::vector<Test>& tests();

// The seed a test runs with: from its name, as the port's runner does, so adding or filtering
// tests doesn't change another test's inputs.
uint64_t seed_for(const char* name);
// "skipped" for the summary line: "" or " (N skipped)".
std::string skipped_note(int skipped);
// Whether `name` matches a --selftest filter (a substring; "a|b" matches any alternative).
bool filter_match(const std::string& filter, const char* name);

// The running test's context (nullptr outside a test), for helpers that must fail it.
Context* current();
void set_current(Context* c);

// Runs one test (the context's name, seed and failures are the caller's); returns its time in ms.
double run_one(const Test& t, Context& ctx);
// Runs every test matching `filter` `repeat` times each, printing "ok   name   ms" / "FAIL ..."
// / "skip ..." lines and the summary; returns {ran, failed} (a skipped test ran, didn't fail). A non-zero `shuffle_seed` runs them in an order
// shuffled with it instead of registration order (soa-server --selftest --shuffle N: finds tests
// that depend on what an earlier test left behind; each test's own seed stays its name's).
std::pair<int, int> run_tests(const std::string& filter, int repeat = 1, bool summary = true, uint64_t shuffle_seed = 0);

}  // namespace soa::server::testing

#define SOASERVER_CONCAT2(a, b) a##b
#define SOASERVER_CONCAT(a, b) SOASERVER_CONCAT2(a, b)
#define SOASERVER_TEST(name)                                                                            \
    static void SOASERVER_CONCAT(soaserver_test_fn_, __LINE__)(::soa::server::testing::Context & t);    \
    static bool SOASERVER_CONCAT(soaserver_test_reg_, __LINE__) =                                       \
        ::soa::server::testing::register_test({name, &SOASERVER_CONCAT(soaserver_test_fn_, __LINE__)}); \
    static void SOASERVER_CONCAT(soaserver_test_fn_, __LINE__)(::soa::server::testing::Context & t)
