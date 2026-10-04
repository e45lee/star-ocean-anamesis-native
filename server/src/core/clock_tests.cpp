// Unit tests of the server's event calendar (--selftest "server/"; not differential: server code
// with no guest counterpart). The run-option tests are the port's
// (port/src/native/api/zz_server_guest_test.cpp).
#include <sqlite3.h>

#include <ctime>
#include <string>

#include "core/log.h"
#include "soaserver/config.h"
#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "soaserver/server.h"

namespace soa::server {
namespace {

int64_t local(int y, int mo, int d, int h = 12, int mi = 0, int s = 0) {
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

// (d) the replayed calendar over the 3.7.0 master: day-level coverage by master_event_term.
NATIVE_TEST("server/event-now") {
    sqlite3* m = nullptr;
    if (std::string p = find_repo_file("data/basmaster-3.7.0.sqlite3"); !p.empty())
        if (sqlite3_open_v2(p.c_str(), &m, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK) {
            sqlite3_close(m);
            m = nullptr;
        }
    if (!m) {
        LOGW("selftest", "server/event-now: the 3.7.0 master DB isn't there; skipped");
        return;
    }
    // Expected years from the 3.7.0 DB's terms (the newest year with a term open that month-day).
    t.expect_eq(event_year(m, 1, 3), 2021, "Jan 3 -> 2021 (New Year events)");
    t.expect_eq(event_year(m, 6, 25), 2020, "Jun 25 -> 2020 (2021's last terms closed on the 21st-24th)");
    t.expect_eq(event_year(m, 10, 1), 2019, "Oct 1 -> 2019");
    t.expect_eq(event_year(m, 12, 25), 2020, "Dec 25 -> 2020");
    t.expect_eq(event_year(m, 2, 29), 2020, "Feb 29 -> the leap year 2020");
    // The mapped time keeps month, day and time of day.
    int64_t e = event_time(m, ServerTime(local(2026, 10, 1, 9, 30, 15))).v;
    t.expect_eq(e, local(2019, 10, 1, 9, 30, 15), "2026-10-01 09:30:15 -> 2019-10-01 09:30:15");
    t.expect_eq(event_time(m, ServerTime(local(2026, 10, 1, 23, 59, 59))).v, local(2019, 10, 1, 23, 59, 59), "same day, cached");
    t.expect_eq(event_time(m, ServerTime(local(2027, 1, 3, 0, 0, 0))).v, local(2021, 1, 3, 0, 0, 0), "next day re-queried");
    // Every day of a leap year maps into a year where a (closing) term is open that day.
    for (int64_t d = local(2024, 1, 1); d < local(2025, 1, 1); d += 86400) {
        int64_t x = event_time(m, ServerTime(d)).v;
        char day[16];
        time_t tt = (time_t)x;
        strftime(day, sizeof day, "%Y-%m-%d", localtime(&tt));
        sqlite3_stmt* st = nullptr;
        sqlite3_prepare_v2(m, "select count(*) from master_event_term where opened_day <= ?1 and ?1 <= closed_day and closed_day < '2022'", -1, &st,
                           nullptr);
        sqlite3_bind_text(st, 1, day, -1, SQLITE_TRANSIENT);
        int n = sqlite3_step(st) == SQLITE_ROW ? sqlite3_column_int(st, 0) : 0;
        sqlite3_finalize(st);
        if (!n) t.fail("%s: no term open on the mapped day", day);
    }
    sqlite3_close(m);

    // Through a server: without a clock the calendar is replayed; with one (--clock) it is the clock.
    ext::with_scratch_server(t.rand_u64(), [&](ext::Ctx& c) {
        set_server_clock(0);
        int64_t real = c.now().v, ev = c.event_now().v;
        time_t a = (time_t)real, b = (time_t)ev;
        struct tm ta, tb;
        localtime_r(&a, &ta);
        localtime_r(&b, &tb);
        if (tb.tm_year + 1900 > 2021 || tb.tm_mon != ta.tm_mon || tb.tm_mday != ta.tm_mday) t.fail("event_now: not today in a service year");
        set_server_clock(local(2019, 10, 1, 4));
        int64_t now1 = c.now().v, ev1 = c.event_now().v;
        if (ev1 < now1 || ev1 > now1 + 2) t.fail("event_now under --clock isn't the clock");
        if (now1 < local(2019, 10, 1, 4) || now1 > local(2019, 10, 1, 4) + 5) t.fail("set_server_clock");
        set_server_clock(0);
    });
}

}  // namespace
}  // namespace soa::server
