// The pure rules of soaserver/server.h `rules::` (port code, not guest behaviour): weighted picks,
// EXP and levels, level interpolation, stamina. Unit-tested in src/core/server.cpp's tests (the
// rules' own tests move beside them with step R8.10 of server/PLAN-readability.md).
#include <algorithm>
#include <cmath>

#include "soaserver/server.h"

namespace soa::server {

namespace rules {

int weighted_pick(const std::vector<u32>& weights, u64 r) {
    for (size_t i = 0; i < weights.size(); i++) {
        if (r < weights[i]) return (int)i;
        r -= weights[i];
    }
    return weights.empty() ? -1 : (int)weights.size() - 1;
}

std::pair<u32, u32> add_exp(u32 level, u32 exp, u64 gain, const std::vector<u32>& next, u32 cap) {
    u64 e = (u64)exp + gain;
    while (level < cap && level < next.size() && next[level] != 0 && e >= next[level]) {
        e -= next[level];
        level++;
    }
    if (level >= cap) e = 0;  // (d) EXP doesn't accumulate at the cap
    return {level, (u32)std::min<u64>(e, 0xffffffffu)};
}

double round_half_away(double v) { return v < 0 ? -std::floor(-v + 0.5) : std::floor(v + 0.5); }

u32 interpolate_level(const std::vector<std::pair<u32, u32>>& rows, u32 level) {
    const std::pair<u32, u32>* lo = nullptr;
    const std::pair<u32, u32>* hi = nullptr;
    for (auto& r : rows) {
        if (r.first == level) return r.second;
        if (r.first < level && (!lo || r.first > lo->first)) lo = &r;
        if (r.first > level && (!hi || r.first < hi->first)) hi = &r;
    }
    if (!lo) return hi ? hi->second : 0;
    if (!hi) return lo->second;
    double step = ((double)hi->second - (double)lo->second) / (double)(hi->first - lo->first);
    return (u32)((double)lo->second + round_half_away(step * (double)(level - lo->first)));
}

std::pair<u32, u64> regen_stamina(u32 stamina, u32 max, u64 elapsed, u32 period) {
    if (stamina >= max || period == 0) return {stamina, 0};
    u64 gained = elapsed / period;
    if (stamina + gained >= max) return {max, 0};
    return {stamina + (u32)gained, elapsed % period};
}

}  // namespace rules

}  // namespace soa::server
