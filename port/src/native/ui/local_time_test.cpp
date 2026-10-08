// platform370's local time (platform370/src/hle_370.cpp "3."; docs/client-changes.md "Local time:
// daylight saving"; test-only, nothing native).
//
// platform370/local-time: the client's own conversions, CTimeUtility::str2time_t (a time string ->
// time_t, tm_isdst = 0 before mktime) and CTimeUtility::TodayStart (the local midnight of a time,
// tm_isdst copied from localtime of that time), in several time zones, against the host:
//   - with the fix (the default): every wall time the host's localtime prints for an instant reads
//     back as that instant, across the year and around both changes of the year: the hour skipped
//     in spring reads as the standard reading (02:30 -> 03:30 daylight), the repeated autumn hour as
//     its first occurrence (daylight), as soa::mktime_local, which the server uses; TodayStart is
//     the local midnight on both change days;
//   - without it (--no-dst-fix, platform370::set_local_time(false)): str2time_t is the host's mktime
//     with tm_isdst 0, i.e. an hour late while daylight saving is in effect (the shipped behaviour);
//   - in a zone without daylight saving both are the same.
// The zones: America/Toronto (the host of 2026-10-08; 2026-10-07 23:20 EDT = 1791429600, 1791433200
// as shipped), the POSIX rule EST5EDT,M3.2.0,M11.1.0, JST-9 and Asia/Tokyo; on Windows (msvcrt reads
// only POSIX TZ values, with its own US rule) the host's own zone, EST5EDT and JST-9. The changes are
// found by scanning the host's localtime, so the test holds for whatever rules the libc has. TZ is set
// around each zone and restored at the end.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <vector>

#include <soa/local_time.h>

#include "native/common/test.h"
#include "platform370/platform370.h"

namespace soa {
namespace {

constexpr const char* kStr2Time = "_ZN12CTimeUtility10str2time_tEPKclbb";
constexpr const char* kTodayStart = "_ZN12CTimeUtility10TodayStartEl";

void set_tz(const char* tz) {
    if (tz) setenv("TZ", tz, 1);
    else unsetenv("TZ");
    tzset();
}

struct tm local(int64_t t) {
    time_t tt = (time_t)t;
    struct tm tm {};
    localtime_r(&tt, &tm);
    return tm;
}

std::string fmt(const struct tm& tm) {
    char b[64];
    std::snprintf(b, sizeof b, "%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min,
                  tm.tm_sec);
    return b;
}

int64_t str2time(TestContext& t, const std::string& s) {
    char buf[64] = {};
    std::strncpy(buf, s.c_str(), sizeof buf - 1);
    return (int64_t)t.call(kStr2Time, {(u64)buf, 0, 0, 1});  // as GetEventAreaList etc. call it
}

// The host's mktime of the fields of `s` with tm_isdst 0: what the shipped str2time_t returns.
int64_t standard_reading(const struct tm& fields) {
    struct tm tm = fields;
    tm.tm_isdst = 0;
    return (int64_t)mktime(&tm);
}

// The instants in 2026 at which the zone's tm_isdst changes (0 -> 1 and 1 -> 0); 0 when none.
void changes(int64_t* spring, int64_t* autumn) {
    *spring = *autumn = 0;
    struct tm jan {};
    jan.tm_year = 126, jan.tm_mon = 0, jan.tm_mday = 1, jan.tm_isdst = -1;
    int64_t t0 = (int64_t)mktime(&jan);
    int prev = local(t0).tm_isdst;
    for (int64_t t = t0 + 3600; t < t0 + 366 * 86400; t += 3600) {
        int d = local(t).tm_isdst;
        if (d == prev) continue;
        int64_t lo = t - 3600, hi = t;  // the first second with the new value
        while (hi - lo > 1) {
            int64_t mid = lo + (hi - lo) / 2;
            (local(mid).tm_isdst == prev ? lo : hi) = mid;
        }
        (d > 0 ? *spring : *autumn) = hi;
        prev = d;
    }
}

void check_zone(TestContext& t, const char* tz) {
    const char* name = tz ? tz : "(the host's zone)";
    int64_t spring, autumn;
    changes(&spring, &autumn);
    {
        struct tm sp = local(spring), au = local(autumn);
        fprintf(stderr, "  platform370/local-time: %s: daylight saving %s %s .. %s\n", name, spring || autumn ? "from" : "none",
                spring ? fmt(sp).c_str() : "-", autumn ? fmt(au).c_str() : "-");
    }
    std::vector<int64_t> probes;
    // every day of 2026 at 23:20 local (the EXP mission's last hour) and at 12:00
    struct tm jan {};
    jan.tm_year = 126, jan.tm_mon = 0, jan.tm_mday = 1, jan.tm_hour = 23, jan.tm_min = 20;
    for (int d = 0; d < 365; d += 3) {
        struct tm a = jan;
        a.tm_mday += d;
        int64_t x = mktime_local(&a);
        probes.push_back(x);
        probes.push_back(x - 11 * 3600 - 1200);
    }
    // around the changes: every 15 minutes from 3 hours before to 3 hours after
    for (int64_t c : {spring, autumn})
        if (c)
            for (int64_t d = -3 * 3600; d <= 3 * 3600; d += 900) probes.push_back(c + d);

    for (bool fix : {true, false}) {
        platform370::set_local_time(fix);
        int bad = 0;
        for (int64_t x : probes) {
            struct tm tm = local(x);
            std::string s = fmt(tm);
            int64_t got = str2time(t, s);
            struct tm f = tm;
            int64_t want = fix ? mktime_local(&f) : standard_reading(tm);
            // with the fix, the instant itself, except the repeated hour's second occurrence
            bool repeated = autumn && x >= autumn && x < autumn + 3600;
            if (fix && !repeated && want != x) t.fail("%s: mktime_local(%s) = %lld, not the instant %lld", name, s.c_str(), (long long)want, (long long)x);
            if (fix && repeated && want != x - 3600)
                t.fail("%s: the repeated %s reads as %lld, want its first occurrence %lld", name, s.c_str(), (long long)want, (long long)(x - 3600));
            if (got != want && bad++ < 5)
                t.fail("%s, %s: str2time_t(\"%s\") = %lld, want %lld (instant %lld, isdst %d)", name, fix ? "fixed" : "--no-dst-fix", s.c_str(),
                       (long long)got, (long long)want, (long long)x, tm.tm_isdst);
        }
        if (bad > 5) t.fail("%s: %d more mismatches", name, bad - 5);
    }
    platform370::set_local_time(true);

    if (spring) {
        // the skipped hour: one hour into the standard reading of the change's wall time
        struct tm before = local(spring - 1);  // e.g. 01:59:59 standard
        struct tm gap = before;
        gap.tm_sec += 1 + 1800;  // 02:30:00, not normalised
        if (gap.tm_sec >= 60) gap.tm_min += gap.tm_sec / 60, gap.tm_sec %= 60;
        if (gap.tm_min >= 60) gap.tm_hour += gap.tm_min / 60, gap.tm_min %= 60;
        std::string s = fmt(gap);
        int64_t got = str2time(t, s);
        if (got != spring + 1800) t.fail("%s: the skipped %s reads as %lld, want %lld (the standard reading)", name, s.c_str(), (long long)got, (long long)(spring + 1800));
    }
    // TodayStart on the change days (an afternoon) and an ordinary day: the local midnight
    for (int64_t x : {spring + 10 * 3600, autumn + 10 * 3600, (int64_t)1791429600}) {
        if (x < 86400) continue;
        struct tm m = local(x);
        m.tm_hour = m.tm_min = m.tm_sec = 0;
        int64_t want = mktime_local(&m);
        int64_t got = (int64_t)t.call(kTodayStart, {(u64)x});
        if (got != want) t.fail("%s: TodayStart(%lld) = %lld, want the local midnight %lld", name, (long long)x, (long long)got, (long long)want);
    }
}

NATIVE_TEST("platform370/local-time") {
    if (!platform370::local_time()) {
        t.fail("platform370::local_time() is off: run without --no-dst-fix");
        return;
    }
    const char* old = std::getenv("TZ");
    std::string saved = old ? old : "";
#ifdef _WIN32
    const char* zones[] = {nullptr, "EST5EDT", "JST-9"};
#else
    const char* zones[] = {"America/Toronto", "EST5EDT,M3.2.0,M11.1.0", "JST-9", "Asia/Tokyo"};
#endif
    for (const char* z : zones) {
        if (z) set_tz(z);
        check_zone(t, z);
#ifndef _WIN32
        if (!std::strcmp(z, "America/Toronto")) {
            // the events-fix case: 2026-10-07 23:20 EDT
            int64_t got = str2time(t, "2026-10-07 23:20:00");
            if (got != 1791429600) t.fail("America/Toronto: str2time_t(2026-10-07 23:20:00) = %lld, want 1791429600", (long long)got);
            platform370::set_local_time(false);
            got = str2time(t, "2026-10-07 23:20:00");
            platform370::set_local_time(true);
            if (got != 1791433200) t.fail("America/Toronto, --no-dst-fix: %lld, want 1791433200 (an hour late)", (long long)got);
        }
        if (!std::strcmp(z, "JST-9") || !std::strcmp(z, "Asia/Tokyo")) {
            int64_t a = str2time(t, "2026-10-07 23:20:00");
            if (a != 1791382800) t.fail("%s: str2time_t(2026-10-07 23:20:00) = %lld, want 1791382800", z, (long long)a);
        }
#endif
    }
    set_tz(old ? saved.c_str() : nullptr);
}

}  // namespace
}  // namespace soa
