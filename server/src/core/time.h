#pragma once
// Local-time helpers of the local server (port code, not guest behaviour): the one copy of each
// format / parse variant, the start of a reset day and the opened_at..closed_at window. Every time
// the server sends or reads is local time "YYYY-MM-DD HH:MM:SS" (the client parses data.Time and
// the master's *_at the same way). Where earlier copies differed, the variants are separate
// functions whose names say how (server/PLAN-readability.md 2.3); behaviour is unchanged.
// format_time itself is public (soaserver/server.h).
#include <cstdint>
#include <string>

#include "soaserver/server.h"

namespace soa::server {

// format_time(t) (server.h), except that t <= 0 formats as "" (an unset time; api/favor/).
std::string format_time_or_empty(int64_t t);

// "YYYY-MM-DD HH:MM:SS" (local time) -> seconds. Lenient: "%d-%d-%d %d:%d:%d" with at least the
// date (missing time fields are 0); 0 when not even the date parses.
int64_t parse_time(const std::string& s);
// The same, strict: the whole "%Y-%m-%d %H:%M:%S" form (strptime) or 0, "" included (api/favor/).
int64_t parse_time_strict(const std::string& s);
// parse_time, or else a plain positive number of seconds since the epoch; 0 when neither
// (--clock: config.h parse_clock).
int64_t parse_time_or_epoch(const std::string& s);
// A day "YYYY-MM-DD" (all three fields, else -1) and a time "HH:MM:SS" (missing fields 0) as one
// local time (the master's *_day + *_time column pairs, e.g. master_campaign).
int64_t parse_day_and_time(const std::string& day, const std::string& time);

// The start of the reset day `t` falls in: the latest local `reset_hour`:00:00 at or before t
// (the daily counters, login bonus days, rental days; the hour is master_global
// login_bonus_reset_hour, read by the caller).
int64_t day_start(int64_t t, int reset_hour);
// `t` moved by `years` calendar years (same month, day and time; Feb 29 normalises to Mar 1).
int64_t add_years(int64_t t, int years);
// The local calendar year of `t`.
int year_of(int64_t t);

// A master row's opened_at..closed_at window, both ends inclusive; an empty end is open-ended.
// The ends are parsed with parse_time (so an unparsable one reads as 0).
struct Window {
    int64_t opened = INT64_MIN, closed = INT64_MAX;
    static Window of(const std::string& opened_at, const std::string& closed_at);
    bool contains(int64_t t) const { return opened <= t && t <= closed; }
};
// Window::of(opened_at, closed_at).contains(t): whether a dated master row is open at t.
inline bool open_at(const std::string& opened_at, const std::string& closed_at, int64_t t) { return Window::of(opened_at, closed_at).contains(t); }

}  // namespace soa::server
