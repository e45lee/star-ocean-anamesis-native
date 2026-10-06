// The guest-libc helpers that differ by host (hle/format.h; port/PLAN.md 5b, W): the scanf format
// for an LLP64 host and the guest's rand(). Also run by build/runtime/soaruntime_tests.
#include <time.h>

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

RUNTIME_TEST("hle/libc-strftime-c89") {
    // the format msvcrt gets for bionic's conversions: fixed cases on every host
    struct tm tmv{};
    time_t s = 1700000000;  // 2023-11-14 22:13:20 UTC, a Tuesday
#ifdef _WIN32
    gmtime_s(&tmv, &s);
#else
    gmtime_r(&s, &tmv);
#endif
    t.expect_eq(strftime_c89_format("%F %T", tmv, 0), std::string("%Y-%m-%d %H:%M:%S"), "%F %T");
    t.expect_eq(strftime_c89_format("%D %R %h", tmv, 0), std::string("%m/%d/%y %H:%M %b"), "%D %R %h");
    t.expect_eq(strftime_c89_format("%e|%k|%l|%C|%u|%P", tmv, 0), std::string("14|22|10|20|2|pm"), "%e %k %l %C %u %P");
    t.expect_eq(strftime_c89_format("%G-W%V %g", tmv, 0), std::string("2023-W46 23"), "ISO week");
    t.expect_eq(strftime_c89_format("%z", tmv, 9 * 3600), std::string("+0900"), "%z east");
    t.expect_eq(strftime_c89_format("%z", tmv, -(4 * 3600 + 30 * 60)), std::string("-0430"), "%z west");
    t.expect_eq(strftime_c89_format("%s", tmv, 0), std::string("1700000000"), "%s");
    t.expect_eq(strftime_c89_format("%-d.%-m %_H %Ey %Od", tmv, 0), std::string("14.11 22 %y %d"), "flags and E/O");
    t.expect_eq(strftime_c89_format("100%% %n%t", tmv, 0), std::string("100%% \n\t"), "literals");
    char out[64];
    std::string f = strftime_c89_format("%F %T %e", tmv, 0);
    t.expect_eq(std::string(out, strftime(out, sizeof out, f.c_str(), &tmv)), std::string("2023-11-14 22:13:20 14"), "through the host's strftime");
#ifndef _WIN32
    // on glibc (which has them all) the written-out format gives what the original does, over
    // dates that cross ISO week-year boundaries
    const time_t days[] = {1609459200 /* 2021-01-01, week 53 of 2020 */, 1735516800 /* 2024-12-30, week 1 of 2025 */,
                           1798675200 /* 2026-12-31 */, 1104537600 /* 2005-01-01 */, 951782400 /* 2000-02-29 */, 0};
    const char* fmts[] = {"%F %T", "%D %R %r", "%e %k %l %C %u", "%G %g %V", "%h %n %t %P", "%-d %_m %0e %-H",
                          "%Ey %OH %EY", "%z", "%a %A %b %B %p %U %W %w %j %y %Y %%"};
    for (time_t d : days)
        for (int h = 0; h < 24; h += 7) {
            time_t at = d + h * 3600 + 59;
            struct tm u;
            gmtime_r(&at, &u);
            for (const char* fm : fmts) {
                char a[128], b[128];
                size_t na = strftime(a, sizeof a, fm, &u);
                size_t nb = strftime(b, sizeof b, strftime_c89_format(fm, u, 0).c_str(), &u);
                t.expect_eq(std::string(b, nb), std::string(a, na), fm);
            }
        }
#endif
}

}  // namespace
}  // namespace soa
