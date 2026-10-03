// soa_env_tests: the environment rule of common/include/soa/env.h (the on/off words, the number
// check, the removed variables' warnings per program) and the default data dirs (soa/paths.h). Run: build/soa_env_tests (exit 1 on a
// failure). The binaries' own warnings are checked by tests/env_removed.sh.
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include <soa/env.h>

using namespace soa::env;

int paths_tests();

namespace {
int g_failures = 0;
void check(bool ok, const std::string& what) {
    fprintf(stderr, "%s  %s\n", ok ? "ok  " : "FAIL", what.c_str());
    if (!ok) g_failures++;
}
std::vector<std::string> warnings(unsigned program, std::vector<std::string> vars) {
    std::vector<char*> envp;
    for (auto& v : vars) envp.push_back(v.data());
    envp.push_back(nullptr);
    return removed_env_warnings(program, envp.data());
}
}  // namespace

int main() {
    // the on/off rule
    for (const char* off : {"0", "false", "FALSE", "no", "No", "off", "OFF"}) check(!parse_bool(off, true), std::string("off: ") + off);
    for (const char* on : {"1", "yes", "true", "on", "2", "x"}) check(parse_bool(on, false), std::string("on: ") + on);
    check(parse_bool(nullptr, true) && !parse_bool(nullptr, false), "unset = the default");
    check(parse_bool("", true) && !parse_bool("", false), "\"\" = the default");
    setenv("SOA_ENV_TEST_B", "0", 1);
    check(!env_on("SOA_ENV_TEST_B") && !env_bool("SOA_ENV_TEST_B", true), "env_bool 0");
    check(!env_tristate("SOA_ENV_TEST_UNSET").has_value() && env_tristate("SOA_ENV_TEST_B") == false, "env_tristate");

    // numbers: range-checked, a bad value is the default (and warned about)
    setenv("SOA_ENV_TEST_N", "250", 1);
    check(env_int("SOA_ENV_TEST_N", 10, 10000, 1000) == 250, "env_int in range");
    check(env_int("SOA_ENV_TEST_N", 10, 100, 7) == 7, "env_int out of range = default");
    setenv("SOA_ENV_TEST_N", "12x", 1);
    check(env_int("SOA_ENV_TEST_N", 0, 100, 7) == 7, "env_int not a number = default");
    check(env_int("SOA_ENV_TEST_UNSET", 0, 100, 7) == 7, "env_int unset = default");
    setenv("SOA_ENV_TEST_L", "a,,b,", 1);
    check(env_list("SOA_ENV_TEST_L") == std::vector<std::string>{"a", "b"}, "env_list");

    // the removed variables: one line each, in the programs that have the flag
    auto w = warnings(kSoa, {"SOA_CLOCK=2021-05-25", "SOA_TRACE=x", "SOA_HEADLESS=", "SOA_ARENA_CHECK_EVERY=2", "HOME=/"});
    check(w == std::vector<std::string>{"SOA_HEADLESS is gone: use --headless / --windowed", "SOA_CLOCK is gone: use --clock",
                                        "SOA_ARENA_CHECK_EVERY is gone: use --live-check"},
          "soa: removed ones warned (also when empty), diagnostics not");
    check(warnings(kServer, {"SOA_CLOCK=1", "SOA_HEADLESS=1", "SOA_ARENA_CHECK=1"}) == std::vector<std::string>{"SOA_CLOCK is gone: use --clock"},
          "soa-server: only the flags it has");
    check(warnings(kEmu, {"SOA_CLOCK=1", "SOA_FONT=f"}) == std::vector<std::string>{"SOA_FONT is gone: use --font"}, "soa-emu");
    check(warnings(kRender, {"SOA_WEBVIEW_FONT=f", "SOA_WEBVIEW_DUMP_CSS=f"}) == std::vector<std::string>{"SOA_WEBVIEW_FONT is gone: use --font"},
          "soa-webview-render");
    check(warnings(kSoa, {"SOA_CLOCKS=1", "SOA_CLOCK_X=1", "XSOA_CLOCK=1", "SOA_CHECK=1"}).empty(), "names match exactly");
    for (const Removed& r : kRemoved) {
        check(r.programs != 0 && r.use[0] == '-', std::string(r.name) + ": a flag in some program");
        check(!is_live_check_var(r.name), std::string(r.name) + ": not a live-check name");
    }
    g_failures += paths_tests();  // the default data dirs (soa/paths.h; paths_tests.cpp)
    fprintf(stderr, "%s\n", g_failures ? "FAILED" : "all passed");
    return g_failures ? 1 : 0;
}
