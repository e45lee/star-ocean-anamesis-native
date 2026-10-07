// The local server's event calendar (server.h event_now / event_time; port code, not guest
// behaviour). Rule (d), docs/server-rules.md#conventions: with no --clock, dated content replays the
// service's calendar: today's month, day and time are mapped onto the most recent year in which
// some master_event_term covers that month-day. Nothing about which events exist is hard-coded;
// the candidate years are the years the table's terms open in.
#include <sqlite3.h>

#include <cstdio>
#include <ctime>
#include <mutex>
#include <string>
#include <vector>

#include "core/server.h"  // set_clock_offset, event_clock_of
#include "soaserver/config.h"
#include "soaserver/server.h"

namespace soa::server {

// ---- the server clock (server.h clock_now) ----------------------------------------------------
// --clock "YYYY-MM-DD HH:MM:SS": the server's clock starts at that time and
// runs on from there, so past banners and events can be replayed.
namespace {
int64_t g_clock_offset = 0;
ClockSource g_clock_source = nullptr;  // set_clock_source (server.h): nullptr = time(nullptr)
}  // namespace

ServerTime clock_now() { return ServerTime((g_clock_source ? g_clock_source() : (int64_t)time(nullptr)) + g_clock_offset); }
void set_server_clock(int64_t t) { g_clock_offset = t ? t - (int64_t)time(nullptr) : 0; }
void set_clock_offset(int64_t offset) { g_clock_offset = offset; }
void set_clock_source(ClockSource source) { g_clock_source = source; }
EventTime event_clock_at(sqlite3* m, ServerTime t) { return g_clock_offset ? clock_as_calendar(t) : event_time(m, t); }
EventTime event_clock_of(sqlite3* m) { return event_clock_at(m, clock_now()); }
void use_configured_clock() {
    if (config().has_clock) set_clock_offset(config().clock_offset);  // --clock
}

namespace {

bool valid_date(int y, int m, int d) {
    struct tm tm = {};
    tm.tm_year = y - 1900;
    tm.tm_mon = m - 1;
    tm.tm_mday = d;
    tm.tm_hour = 12;
    tm.tm_isdst = -1;
    mktime(&tm);  // normalises e.g. Feb 29 of a common year to Mar 1
    return tm.tm_year == y - 1900 && tm.tm_mon == m - 1 && tm.tm_mday == d;
}

// The candidate years, newest first: every year some term opens in; open-ended terms (closing
// after the newest of those years, e.g. the 2030-12-31 "never closes" rows) are left out.
std::vector<int> candidate_years(sqlite3* db, int* last) {
    std::vector<int> years;
    *last = 0;
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db,
                           "select distinct cast(substr(opened_day, 1, 4) as integer) y from master_event_term "
                           "where opened_day is not null and opened_day != '' order by y desc",
                           -1, &st, nullptr) != SQLITE_OK)
        return years;
    while (sqlite3_step(st) == SQLITE_ROW)
        if (int y = sqlite3_column_int(st, 0); y > 0) years.push_back(y);
    sqlite3_finalize(st);
    if (!years.empty()) *last = years.front();
    return years;
}

}  // namespace

int event_year(sqlite3* master, int m, int d) {
    if (!master) return 0;
    int last = 0;
    std::vector<int> years = candidate_years(master, &last);
    if (years.empty()) return 0;
    sqlite3_stmt* st = nullptr;
    // (a) master_event_term.opened_day / closed_day ("YYYY-MM-DD", compared as text), day-level
    // so the year doesn't change during the day.
    if (sqlite3_prepare_v2(master,
                           "select 1 from master_event_term where opened_day <= ?1 and ?1 <= closed_day "
                           "and cast(substr(closed_day, 1, 4) as integer) <= ?2 limit 1",
                           -1, &st, nullptr) != SQLITE_OK)
        return 0;
    int found = 0;
    for (int cand : years) {
        if (!valid_date(cand, m, d)) continue;  // Feb 29 only in leap years
        char day[48];
        snprintf(day, sizeof day, "%04d-%02d-%02d", cand, m, d);
        sqlite3_reset(st);
        sqlite3_bind_text(st, 1, day, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(st, 2, last);
        if (sqlite3_step(st) == SQLITE_ROW) {
            found = cand;
            break;
        }
    }
    sqlite3_finalize(st);
    return found;
}

EventTime event_time(sqlite3* master, ServerTime t) {
    time_t tt = (time_t)t.v;
    struct tm tm;
    localtime_r(&tt, &tm);
    int y = tm.tm_year + 1900, m = tm.tm_mon + 1, d = tm.tm_mday;
    // Cached per (master, local date): one query a day.
    static std::mutex mu;
    static sqlite3* c_db = nullptr;
    static int c_key = -1, c_year = 0;
    int key = y * 10000 + m * 100 + d, year;
    {
        std::lock_guard<std::mutex> l(mu);
        if (c_db != master || c_key != key) {
            c_db = master;
            c_key = key;
            c_year = event_year(master, m, d);
        }
        year = c_year;
    }
    if (!year) return clock_as_calendar(t);  // (d) no term covers this month-day in any year: the real time
    struct tm e = tm;
    e.tm_year = year - 1900;
    e.tm_isdst = -1;
    return EventTime((int64_t)mktime(&e));
}

}  // namespace soa::server
