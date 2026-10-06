// The server library's test registry and runner (soaserver/testing.h; library code).
#include "soaserver/testing.h"

#include <algorithm>
#include <chrono>
#include <cstdarg>
#include <cstdio>

namespace soa::server::testing {

namespace {
std::vector<Test>& registry() {
    static std::vector<Test> t;
    return t;
}
Context* g_current = nullptr;
}  // namespace

bool register_test(const Test& t) {
    registry().push_back(t);
    return true;
}
const std::vector<Test>& tests() { return registry(); }

std::vector<uint8_t> Context::rand_bytes(size_t n, int alphabet) {
    std::vector<uint8_t> v(n);
    for (auto& b : v) b = (uint8_t)(rng_() % alphabet);
    return v;
}

void Context::fail(const char* fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    fprintf(stderr, "    FAIL [%s]: %s\n", name_, buf);
    failures_++;
}

void Context::skip(const char* fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    fprintf(stderr, "    skip [%s]: %s\n", name_, buf);
    skipped_ = true;
}

std::string skipped_note(int skipped) { return skipped ? " (" + std::to_string(skipped) + " skipped)" : ""; }

uint64_t seed_for(const char* name) {
    uint64_t seed = 0x5eed0000;
    for (const char* c = name; *c; c++) seed = seed * 131 + (uint8_t)*c;
    return seed;
}

bool filter_match(const std::string& filter, const char* name) {
    if (filter.empty()) return true;
    for (size_t pos = 0;;) {
        size_t bar = filter.find('|', pos);
        std::string alt = filter.substr(pos, bar == std::string::npos ? std::string::npos : bar - pos);
        if (!alt.empty() && std::string(name).find(alt) != std::string::npos) return true;
        if (bar == std::string::npos) return false;
        pos = bar + 1;
    }
}

Context* current() { return g_current; }
void set_current(Context* c) { g_current = c; }

double run_one(const Test& t, Context& ctx) {
    auto t0 = std::chrono::steady_clock::now();
    set_current(&ctx);
    t.fn(ctx);
    set_current(nullptr);
    return std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count();
}

std::pair<int, int> run_tests(const std::string& filter, int repeat, bool summary, uint64_t shuffle_seed) {
    int failed = 0, ran = 0, skipped = 0;
    std::vector<const Test*> order;
    for (const Test& t : tests()) order.push_back(&t);
    if (shuffle_seed) {
        std::mt19937_64 rng(shuffle_seed);
        std::shuffle(order.begin(), order.end(), rng);
        fprintf(stderr, "(tests in a shuffled order, seed %llu)\n", (unsigned long long)shuffle_seed);
    }
    for (const Test* tp : order) {
        const Test& t = *tp;
        if (!filter_match(filter, t.name)) continue;
        for (int rep = 0; rep < repeat; rep++) {
            Context ctx(t.name, seed_for(t.name));
            double ms = run_one(t, ctx);
            ran++;
            if (ctx.failures()) failed++;
            else if (ctx.skipped()) skipped++;
            fprintf(stderr, "%s  %-50s %8.1f ms\n", ctx.status(), t.name, ms);
        }
    }
    if (summary) fprintf(stderr, "%d/%d server tests passed%s\n", ran - failed - skipped, ran, skipped_note(skipped).c_str());
    return {ran, failed};
}

}  // namespace soa::server::testing
