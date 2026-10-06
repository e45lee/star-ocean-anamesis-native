// The guest-libc helpers that differ by host (hle/format.h; port/PLAN.md 5b, W): the scanf format
// for an LLP64 host and the guest's rand(). Also run by build/runtime/soaruntime_tests.
#include <cstdio>
#include <cstdlib>
#include <string>

#include "core/selftest.h"
#include "hle/format.h"

namespace soa {
namespace {

RUNTIME_TEST("hle/libc-scanf-format-llp64") {
    t.expect_eq(host_scanf_format("%ld %lu %lx %li %lo %lX %ln", true), std::string("%lld %llu %llx %lli %llo %llX %lln"), "l -> ll");
    t.expect_eq(host_scanf_format("%lld %lf %ls %lc %d %%ld %*ld %10lu %hd %zu", true),
                std::string("%lld %lf %ls %lc %d %%ld %*lld %10llu %hd %llu"), "others kept");
    t.expect_eq(host_scanf_format("%[^,]%ld", true), std::string("%[^,]%lld"), "after a scanset");
    t.expect_eq(host_scanf_format("%zu %zd %zx %jd %ju %td %tu %zn", true), std::string("%llu %lld %llx %lld %llu %lld %llu %lln"),
                "z, j, t -> ll");
    t.expect_eq(host_scanf_format("%ld", false), std::string("%ld"), "LP64 host: unchanged");
    long long v = 0;
    unsigned long long u = 0;
    int n = sscanf("-5000000000 4000000000", host_scanf_format("%ld %lu", true).c_str(), &v, &u);
    t.expect_eq(n, 2, "converted");
    t.expect_eq(v, -5000000000LL, "64-bit %ld");
    t.expect_eq(u, 4000000000ULL, "64-bit %lu");
}

// Every 64-bit length modifier the guest's scanf may use, through this host's sscanf with the
// translated format (the guest's sscanf / vsscanf / fscanf thunks: hle/libc_stdio.cpp): all 64 bits
// written, none past them.
RUNTIME_TEST("hle/libc-scanf-64bit-lengths") {
    struct Case {
        const char* fmt;
        const char* in;
        u64 want;
    };
    const Case cases[] = {
        {"%ld", "-5000000000", (u64)-5000000000LL}, {"%li", "0x123456789a", 0x123456789aull},  {"%lu", "18446744073709551615", ~0ull},
        {"%lx", "fedcba9876543210", 0xfedcba9876543210ull}, {"%lX", "FEDCBA9876543210", 0xfedcba9876543210ull},
        {"%lo", "1777777777777777777777", ~0ull}, {"%lld", "-9000000000", (u64)-9000000000LL}, {"%llu", "12345678901234", 12345678901234ull},
        {"%zu", "8589934593", 8589934593ull}, {"%zd", "-8589934593", (u64)-8589934593LL}, {"%zx", "200000001", 0x200000001ull},
        {"%jd", "-7000000000", (u64)-7000000000LL}, {"%ju", "7000000000", 7000000000ull}, {"%td", "-6000000000", (u64)-6000000000LL},
        {"%tu", "6000000000", 6000000000ull}, {"%p", "0x7fff12345678", 0x7fff12345678ull},
    };
    for (const Case& c : cases) {
        u64 v[2] = {0x5a5a5a5a5a5a5a5aull, 0x5a5a5a5a5a5a5a5aull};
        int n = sscanf(c.in, host_scanf_format(c.fmt).c_str(), &v[0]);
        t.expect_eq(n, 1, c.fmt);
        t.expect_eq(v[0], c.want, c.fmt);
        t.expect_eq(v[1], 0x5a5a5a5a5a5a5a5aull, c.fmt);
    }
    // %ln / %zn: the count, 64 bits
    for (const char* f : {"%*s%ln", "%*s%zn", "%*s%jn", "%*s%tn"}) {
        u64 v = ~0ull;
        sscanf("abcdef", host_scanf_format(f).c_str(), &v);
        t.expect_eq(v, 6ull, f);
    }
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
