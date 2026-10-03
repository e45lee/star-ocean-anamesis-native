// The guest-libc helpers that differ by host (hle/format.h; port/PLAN.md 5b, W): the scanf format
// for an LLP64 host and the guest's rand(). Also run by build/runtime/soaruntime_tests.
#include <cstdlib>
#include <string>

#include "core/selftest.h"
#include "hle/format.h"

namespace soa {
namespace {

RUNTIME_TEST("hle/libc-scanf-format-llp64") {
    t.expect_eq(host_scanf_format("%ld %lu %lx %li %lo %lX %ln", true), std::string("%lld %llu %llx %lli %llo %llX %lln"), "l -> ll");
    t.expect_eq(host_scanf_format("%lld %lf %ls %lc %d %%ld %*ld %10lu %hd %zu", true),
                std::string("%lld %lf %ls %lc %d %%ld %*lld %10llu %hd %zu"), "others kept");
    t.expect_eq(host_scanf_format("%[^,]%ld", true), std::string("%[^,]%lld"), "after a scanset");
    t.expect_eq(host_scanf_format("%ld", false), std::string("%ld"), "LP64 host: unchanged");
    long long v = 0;
    unsigned long long u = 0;
    int n = sscanf("-5000000000 4000000000", host_scanf_format("%ld %lu", true).c_str(), &v, &u);
    t.expect_eq(n, 2, "converted");
    t.expect_eq(v, -5000000000LL, "64-bit %ld");
    t.expect_eq(u, 4000000000ULL, "64-bit %lu");
}

RUNTIME_TEST("hle/libc-rand-glibc-sequence") {
    // glibc's unseeded rand(): the documented first outputs of random() seeded with 1
    glibc_random(true);
    const s32 want[] = {1804289383, 846930886, 1681692777, 1714636915, 1957747793};
    for (s32 w : want) t.expect_eq(glibc_random(), w, "glibc random() sequence");
#ifndef _WIN32
    // and the same as this host's rand() from a fresh seed 1
    srand(1);
    glibc_random(true);
    for (int i = 0; i < 1000; i++) t.expect_eq(glibc_random(), (s32)rand(), "host rand() after srand(1)");
    srand(1);
#endif
}

}  // namespace
}  // namespace soa
