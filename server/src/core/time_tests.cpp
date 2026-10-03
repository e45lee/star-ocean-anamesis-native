// Unit tests of core/time (--selftest "server/"; not differential: server code with no guest
// counterpart). They pin how the variants differ, since each replaced copies that differed.
#include <ctime>
#include <string>

#include "core/time.h"
#include "soaserver/native_test.h"

namespace soa::server {
namespace {

int64_t local(int y, int mo, int d, int h, int mi, int s) {
    struct tm tm = {};
    tm.tm_year = y - 1900;
    tm.tm_mon = mo - 1;
    tm.tm_mday = d;
    tm.tm_hour = h;
    tm.tm_min = mi;
    tm.tm_sec = s;
    tm.tm_isdst = -1;
    return (int64_t)mktime(&tm);
}

NATIVE_TEST("server/time-variants") {
    int64_t at = local(2020, 6, 1, 12, 34, 56);
    t.expect_eq(format_time(at), std::string("2020-06-01 12:34:56"), "format_time");
    t.expect_eq(parse_time("2020-06-01 12:34:56"), at, "parse_time round trip");
    t.expect_eq(format_time_or_empty(0), std::string(), "or_empty: 0 is unset");
    t.expect_eq(format_time_or_empty(at), format_time(at), "or_empty: else format_time");
    // lenient vs strict: a date alone
    t.expect_eq(parse_time("2020-06-01"), local(2020, 6, 1, 0, 0, 0), "parse_time: the date alone is midnight");
    t.expect_eq(parse_time_strict("2020-06-01"), (int64_t)0, "parse_time_strict: the date alone is 0");
    t.expect_eq(parse_time_strict(""), (int64_t)0, "parse_time_strict: empty");
    t.expect_eq(parse_time("x"), (int64_t)0, "parse_time: garbage");
    // --clock: a time or epoch seconds
    t.expect_eq(parse_time_or_epoch("2020-06-01 12:34:56"), at, "or_epoch: a time");
    t.expect_eq(parse_time_or_epoch("1600000000"), (int64_t)1600000000, "or_epoch: seconds");
    t.expect_eq(parse_time_or_epoch("-5"), (int64_t)0, "or_epoch: not positive");
    // day + time columns
    t.expect_eq(parse_day_and_time("2020-06-01", "12:34:56"), at, "day and time");
    t.expect_eq(parse_day_and_time("2020-06-01", ""), local(2020, 6, 1, 0, 0, 0), "day and no time");
    t.expect_eq(parse_day_and_time("2020-06", "12:00:00"), (int64_t)-1, "a day needs three fields");
    // reset day
    t.expect_eq(day_start(local(2020, 6, 1, 4, 0, 0), 4), local(2020, 6, 1, 4, 0, 0), "04:00 starts a day");
    t.expect_eq(day_start(local(2020, 6, 1, 3, 59, 59), 4), local(2020, 5, 31, 4, 0, 0), "03:59 is the day before");
    t.expect_eq(add_years(local(2020, 2, 29, 12, 0, 0), 1), local(2021, 3, 1, 12, 0, 0), "Feb 29 + 1 year");
    t.expect_eq(year_of(at), 2020, "year_of");
    // windows: inclusive ends, empty = open-ended
    t.expect_eq(open_at("2020-06-01 12:34:56", "2020-06-01 12:34:56", at), true, "both ends inclusive");
    t.expect_eq(!open_at("2020-06-01 12:34:57", "", at), true, "not yet open");
    t.expect_eq(!open_at("", "2020-06-01 12:34:55", at), true, "closed");
    t.expect_eq(open_at("", "", at), true, "open-ended");
}

}  // namespace
}  // namespace soa::server
