#include "native/common/test.h"

#include <cstdlib>
#include <string>

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <cstdarg>

#include "core/log.h"
#include "core/selftest.h"
#include "native/common/native.h"
#include "soaserver/testing.h"  // the server library's tests (top-level server/)

namespace soa {

static std::vector<NativeTest>& tests() {
    static std::vector<NativeTest> t;
    return t;
}

bool register_native_test(const NativeTest& t) {
    tests().push_back(t);
    return true;
}

u64 TestContext::sym(const char* name) {
    u64 a = lib_.sym(name);
    if (!a) fail("guest symbol %s not found", name);
    return a;
}

std::vector<uint8_t> TestContext::rand_bytes(size_t n, int alphabet) {
    std::vector<uint8_t> v(n);
    for (auto& b : v) b = (uint8_t)(rng_() % alphabet);
    return v;
}

static std::vector<TestHook>& test_hooks() {
    static std::vector<TestHook> h;
    return h;
}

bool register_test_hook(const TestHook& h) {
    test_hooks().push_back(h);
    return true;
}

void install_test_hooks(LoadedLib& lib) {
    // SOA_TEST_HOOKS_SKIP=sym1,sym2 (or "all"): leave these test hooks out (their tests then fail);
    // for finding a hook that breaks the boot of a new guest build (the 3.7.0 rebase).
    const char* skip_env = getenv("SOA_TEST_HOOKS_SKIP");
    std::string skip = skip_env ? std::string(",") + skip_env + "," : "";
    // The 3.7.0 rebase (P1, natives off): hooks that run a native (a2c transcription with the old lib's
    // constants) in the game's own frame from boot on crash the 3.7.0 guest before any test runs
    // (found by bisecting the boot). Left out until P2 regenerates their family; their tests fail.
    static const char* const kRebaseSkippedHooks[] = {
        // cocos/gui-reader-in-frame (cocos_guireader.cpp): CreateTree, Play and GetHandle load / run
        // the transcription into the game's scenes.
        "_ZN9Framework5Cocos15CCocosGuiReader10CreateTreeERKNS_20CResourceElement_CsfERNS0_10CCocosNodeERNS0_19CCocosObjectFactoryE",
        "_ZN9Framework5Cocos23CCocosTimelineAnimation4PlayERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEjjbNS2_8functionIFvvEEE",
        "_ZNK9Framework5Cocos23CCocosTimelineAnimation9GetHandleERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE",
    };
    if (!getenv("SOA_TEST_HOOKS_ALL"))  // SOA_TEST_HOOKS_ALL=1: install them anyway (P2)
        for (const char* h : kRebaseSkippedHooks) skip += std::string(",") + h + ",";
    for (auto& h : test_hooks()) {
        if (!skip.empty() && (skip == ",all," || skip.find(std::string(",") + h.symbol + ",") != std::string::npos)) {
            fprintf(stderr, "test hook: %s skipped (SOA_TEST_HOOKS_SKIP)\n", h.symbol);
            continue;
        }
        u64 addr = lib.sym(h.symbol);
        if (!addr) fatal("test hook: guest symbol %s not found", h.symbol);
        *h.original = make_original_trampoline(addr);
        if (!*h.original && h.optional) {
            fprintf(stderr, "test hook: can't relocate the prologue of %s (skipped)\n", h.symbol);
            continue;
        }
        // The 3.7.0 rebase (P1): a guest function whose 3.7.0 prologue isn't relocatable (e.g.
        // CTutorialManager::IsExistMenuVoiceMask, a 4-byte stub in the offline build, starts with a
        // tbnz in 3.7.0) can't carry its hook; the run goes on without it and the tests that need it fail
        // (docs/history/REBASE-370.md "Selftest on 3.7.0"). Was fatal.
        if (!*h.original) {
            fprintf(stderr, "test hook: can't relocate the prologue of %s (skipped: its tests are expected to fail)\n", h.symbol);
            continue;
        }
        hook_guest_function(addr, h.symbol, h.fn);
    }
}

static const char* g_current_test = "";
static TestContext* g_current_ctx = nullptr;

TestContext* current_test_context() { return g_current_ctx; }

void TestContext::fail(const char* fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    fprintf(stderr, "    FAIL [%s]: %s\n", g_current_test, buf);
    failures_++;
}

namespace {
// A runtime test (core/selftest.h: RUNTIME_TEST) reports through the running TestContext.
struct RuntimeTestAdapter final : RuntimeTestContext {
    TestContext& ctx;
    explicit RuntimeTestAdapter(TestContext& c) : ctx(c) {}
    void report_failure(const char* msg) override { ctx.fail("%s", msg); }
};
struct TestEntry {
    const char* name;
    void (*native)(TestContext&);
    void (*runtime)(RuntimeTestContext&);
};
}  // namespace

int run_native_tests(LoadedLib& lib, const std::string& filter) {
    int failed = 0, ran = 0;
    // The runtime's own tests first (they used to be linked first, so they registered first),
    // then the port's NATIVE_TESTs.
    std::vector<TestEntry> all;
    for (auto& r : runtime_tests()) all.push_back({r.name, nullptr, r.fn});
    for (auto& n : tests()) all.push_back({n.name, n.fn, nullptr});
    for (auto& t : all) {
        // The filter is a substring; "a|b" runs the tests matching any of the alternatives.
        if (!filter.empty()) {
            bool match = false;
            for (size_t pos = 0; !match;) {
                size_t bar = filter.find('|', pos);
                std::string alt = filter.substr(pos, bar == std::string::npos ? std::string::npos : bar - pos);
                match = !alt.empty() && std::string(t.name).find(alt) != std::string::npos;
                if (bar == std::string::npos) break;
                pos = bar + 1;
            }
            if (!match) continue;
        }
        // SOA_SELFTEST_SKIP=name1,name2: tests left out by exact name (e.g. ones that crash the
        // process on a new guest build; the 3.7.0 rebase).
        static const std::string skip_tests = getenv("SOA_SELFTEST_SKIP") ? std::string(",") + getenv("SOA_SELFTEST_SKIP") + "," : "";
        if (!skip_tests.empty() && skip_tests.find(std::string(",") + t.name + ",") != std::string::npos) {
            fprintf(stderr, "skip  %s (SOA_SELFTEST_SKIP)\n", t.name);
            continue;
        }
        // One line before each test, so a crash names the test it happened in.
        fprintf(stderr, "run   %s\n", t.name);
        g_current_test = t.name;
        // SOA_SELFTEST_REPEAT=N runs each matching test N times (same seed), to shake out
        // flakiness (races with the game threads).
        static const int repeat = getenv("SOA_SELFTEST_REPEAT") ? std::max(1, atoi(getenv("SOA_SELFTEST_REPEAT"))) : 1;
        for (int rep = 0; rep < repeat; rep++) {
            // Seeded by name, so adding or filtering tests doesn't change another test's inputs.
            u64 seed = 0x5eed0000;
            for (const char* c = t.name; *c; c++) seed = seed * 131 + (u8)*c;
            TestContext ctx(lib, seed);
            auto t0 = std::chrono::steady_clock::now();
            g_current_ctx = &ctx;
            if (t.native) t.native(ctx);
            else {
                RuntimeTestAdapter rt(ctx);
                t.runtime(rt);
            }
            g_current_ctx = nullptr;
            double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
            ran++;
            if (ctx.failures()) failed++;
            fprintf(stderr, "%s  %-50s %8.1f ms\n", ctx.failures() ? "FAIL" : "ok  ", t.name, ms);
        }
    }
    // The server library's tests (top-level server/; they ran last when it was port/src/server):
    // same filter, seeds, repeat and output.
    for (const server::testing::Test& t : server::testing::tests()) {
        if (!server::testing::filter_match(filter, t.name)) continue;
        g_current_test = t.name;
        static const int repeat = getenv("SOA_SELFTEST_REPEAT") ? std::max(1, atoi(getenv("SOA_SELFTEST_REPEAT"))) : 1;
        for (int rep = 0; rep < repeat; rep++) {
            server::testing::Context ctx(t.name, server::testing::seed_for(t.name));
            double ms = server::testing::run_one(t, ctx);
            ran++;
            if (ctx.failures()) failed++;
            fprintf(stderr, "%s  %-50s %8.1f ms\n", ctx.failures() ? "FAIL" : "ok  ", t.name, ms);
        }
    }
    fprintf(stderr, "%d/%d native tests passed\n", ran - failed, ran);
    return failed;
}

}  // namespace soa
