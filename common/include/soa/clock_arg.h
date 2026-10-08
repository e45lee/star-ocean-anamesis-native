#pragma once
// A --clock value (soa, soa-server; the server library's soaserver/config.h parse_clock and
// set_clock): "YYYY-MM-DD[ HH:MM:SS]" in local time, or a plain integer (Unix seconds). The one
// parser of it, header-only so that the command-line parsers' tests (tests/cli) needn't link the
// server library.
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

#include "soa/local_time.h"

namespace soa {

// The time `s` names (Unix seconds); 0 when it is unparsable.
inline int64_t parse_clock_arg(const std::string& s) {
    struct tm tm = {};
    if (sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) >= 3) {
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        return soa::mktime_local(&tm);
    }
    char* end = nullptr;
    long long v = strtoll(s.c_str(), &end, 10);
    return end && end != s.c_str() && *end == 0 && v > 0 ? (int64_t)v : 0;
}

}  // namespace soa
