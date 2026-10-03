// Local-time helpers (core/time.h; port code, not guest behaviour).
#include "core/time.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

namespace soa::server {

std::string format_time(int64_t t) {
    time_t tt = (time_t)t;
    struct tm tm;
    localtime_r(&tt, &tm);
    char b[32];
    strftime(b, sizeof b, "%Y-%m-%d %H:%M:%S", &tm);
    return b;
}
std::string format_time_or_empty(int64_t t) { return t <= 0 ? std::string() : format_time(t); }

int64_t parse_time(const std::string& s) {
    struct tm tm = {};
    if (sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) < 3) return 0;
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    tm.tm_isdst = -1;
    return (int64_t)mktime(&tm);
}
int64_t parse_time_strict(const std::string& s) {
    struct tm tm {};
    if (s.empty() || !strptime(s.c_str(), "%Y-%m-%d %H:%M:%S", &tm)) return 0;
    tm.tm_isdst = -1;
    return (int64_t)mktime(&tm);
}
int64_t parse_time_or_epoch(const std::string& s) {
    struct tm tm = {};
    if (sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) >= 3) return parse_time(s);
    char* end = nullptr;
    long long v = strtoll(s.c_str(), &end, 10);
    return end && end != s.c_str() && *end == 0 && v > 0 ? (int64_t)v : 0;
}
int64_t parse_day_and_time(const std::string& day, const std::string& time) {
    struct tm tm = {};
    if (sscanf(day.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday) != 3) return -1;
    sscanf(time.c_str(), "%d:%d:%d", &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    tm.tm_isdst = -1;
    return (int64_t)mktime(&tm);
}

int64_t day_start(int64_t t, int reset_hour) {
    time_t tt = (time_t)(t - (int64_t)reset_hour * 3600);
    struct tm tm;
    localtime_r(&tt, &tm);
    tm.tm_hour = reset_hour;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;
    return (int64_t)mktime(&tm);
}
int64_t add_years(int64_t t, int years) {
    time_t tt = (time_t)t;
    struct tm tm;
    localtime_r(&tt, &tm);
    tm.tm_year += years;
    tm.tm_isdst = -1;
    return (int64_t)mktime(&tm);
}
int year_of(int64_t t) {
    time_t tt = (time_t)t;
    struct tm tm;
    localtime_r(&tt, &tm);
    return tm.tm_year + 1900;
}

Window Window::of(const std::string& opened_at, const std::string& closed_at) {
    Window w;
    if (!opened_at.empty()) w.opened = parse_time(opened_at);
    if (!closed_at.empty()) w.closed = parse_time(closed_at);
    return w;
}

}  // namespace soa::server
