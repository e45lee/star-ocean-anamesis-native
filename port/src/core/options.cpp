// Run options (see options.h): filled from the command line only (main.cpp).
#include "core/options.h"

#include <cstdlib>
#include <cstring>
#include <ctime>

namespace soa {

namespace {
RunOptions g_options;
}  // namespace

const char* const kDefaultEventKeywords = "水着,夏,サマー,!福袋";

const RunOptions& options() { return g_options; }
RunOptions& mutable_options() { return g_options; }

int64_t parse_clock(const std::string& s) {
    struct tm tm = {};
    if (sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) >= 3) {
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        tm.tm_isdst = -1;
        return (int64_t)mktime(&tm);
    }
    // Unix seconds.
    char* end = nullptr;
    long long v = strtoll(s.c_str(), &end, 10);
    return end && end != s.c_str() && *end == 0 && v > 0 ? (int64_t)v : 0;
}

bool set_clock(ServerOptions& o, const std::string& s) {
    int64_t t = parse_clock(s);
    if (!t) return false;
    o.has_clock = true;
    o.clock = t;
    o.clock_offset = t - (int64_t)time(nullptr);
    return true;
}


}  // namespace soa
