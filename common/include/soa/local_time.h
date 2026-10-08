#pragma once
// Local wall time -> Unix seconds, daylight saving included and deterministic (docs/server-rules.md
// "Two clocks"). The one rule the server (core/time.cpp, core/clock.cpp, the rules), the --clock
// parser (clock_arg.h), the device clock and the client's mktime (platform370/src/hle_370.cpp, so
// CTimeUtility::str2time_t and the guest's other conversions) share, so that both sides read every
// time string as the same instant.
//
// mktime with tm_isdst = -1 decides daylight saving itself, but glibc resolves the repeated hour of
// the autumn change (e.g. 2026-11-01 01:30 in America/Toronto, once EDT and once EST) by a hint left
// from its previous call: the answer depends on what was converted before. So the hour is resolved
// here, from the two readings mktime gives with tm_isdst = 0 (standard time) and 1 (daylight time):
//   - exactly one reading is self-consistent (the instant it gives has that tm_isdst): that one;
//   - both are (the repeated hour): the earlier, the first occurrence (daylight time; (d), a choice);
//   - neither is (the hour skipped in spring, e.g. 2026-03-08 02:30): the standard-time reading,
//     the offset in force before the change (02:30 -> 03:30 EDT), as glibc's tm_isdst = -1 does;
//   - mktime fails for both (-1): -1.
// In a zone without daylight saving (Asia/Tokyo, the original service's) only the standard reading
// is consistent: the same as mktime with tm_isdst 0 or -1.
#include <cstdint>
#include <ctime>

namespace soa {

// Which of the two readings to take (0: standard, 1: daylight): t0 / t1 are mktime's results with
// tm_isdst 0 / 1, isdst0 / isdst1 the tm_isdst it wrote back with them.
inline int pick_local_reading(int64_t t0, int isdst0, int64_t t1, int isdst1) {
    bool v0 = t0 != -1 && isdst0 == 0, v1 = t1 != -1 && isdst1 > 0;
    if (v0 && v1) return t1 < t0 ? 1 : 0;
    if (v1) return 1;
    if (v0 || t0 != -1) return 0;
    return t1 != -1 ? 1 : 0;
}

// mktime for a local wall time, whatever tm->tm_isdst says (see above). Normalises *tm as mktime does.
inline int64_t mktime_local(struct tm* tm) {
    struct tm a = *tm, b = *tm;
    a.tm_isdst = 0;
    b.tm_isdst = 1;
    int64_t t0 = (int64_t)mktime(&a), t1 = (int64_t)mktime(&b);
    if (pick_local_reading(t0, a.tm_isdst, t1, b.tm_isdst)) {
        *tm = b;
        return t1;
    }
    *tm = a;
    return t0;
}

}  // namespace soa
