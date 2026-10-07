#pragma once
// Time value types (docs/history/PLAN-readability.md 2.3, step R17; port code, not guest behaviour). The
// server reads two clocks (soaserver/server.h, docs/server-rules.md#conventions):
//   - ServerTime: the server clock (clock_now(), ext::Ctx::now(): the real time, or --clock and
//     running on from there). The wire's data.Time is this clock, so the client filters what it
//     shows by it. Every time the state stores is a ServerTime: since PLAN-schema S9 an INTEGER of
//     unix seconds, NULL = never (std::optional<ServerTime>, sql::Row::opt), except the four 0
//     sentinels S10 maps (ds_offer.closed_at / updated_at, wboss.hunt_until,
//     favor_bonus_state.healed_at), read as a ServerTime whose .v is tested. Reset-day starts
//     (day_start, the `*_day` columns) are ServerTimes too.
//   - EventTime: the event calendar (event_now(), ext::Ctx::event_now(): today's date replayed onto
//     the service's calendar, the clock itself under --clock). Dated master content the server
//     alone decides (event terms, deep space's bonus sets and drops, the tower, Sphere 211's
//     season) is tested against it. It is never stored: sql::Arg has no EventTime overload.
// The master data's own dates ("YYYY-MM-DD HH:MM:SS" text, parsed by core/time.h parse_time) are
// neither: raw seconds (int64_t) that a window test (core/time.h Window::contains) compares with a
// ServerTime or an EventTime, the overload naming the clock.
//
// Each clock is its own type: comparing or subtracting a ServerTime and an EventTime doesn't
// compile, and neither converts to or from a number except explicitly (`ServerTime(n)`, `.v`). A
// time moves by a duration in seconds (`t + 60`); two times of one clock subtract to a duration
// (int64_t seconds). The wire's text is formatted at the boundary (format_time / ext::Ctx::fmt_time).
#include <compare>
#include <cstdint>
#include <optional>

namespace soa::server {

template <class Tag>
struct Time {
    using rep = int64_t;
    int64_t v = 0;  // unix seconds
    constexpr Time() = default;
    constexpr explicit Time(int64_t seconds) : v(seconds) {}
    friend constexpr auto operator<=>(const Time&, const Time&) = default;
    // Moved by a duration (seconds).
    friend constexpr Time operator+(Time t, int64_t seconds) { return Time(t.v + seconds); }
    friend constexpr Time operator-(Time t, int64_t seconds) { return Time(t.v - seconds); }
    constexpr Time& operator+=(int64_t seconds) {
        v += seconds;
        return *this;
    }
    // The duration from b to a (seconds).
    friend constexpr int64_t operator-(Time a, Time b) { return a.v - b.v; }
};

// The server clock (unix seconds): every stored time, the wire's data.Time.
using ServerTime = Time<struct ServerClockTag>;
// The event calendar (unix seconds): dated master content the server decides. Never stored.
using EventTime = Time<struct EventCalendarTag>;

}  // namespace soa::server
