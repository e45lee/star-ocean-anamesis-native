// The local server's mission-side rules; see mission_rules.h and docs/server-rules.md#server-missions.
// Labels: (a) master data, (b) client-side evidence, (c) outside knowledge,
// (d) assumption.
#include "rules/mission_rules.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>

#include "core/time.h"

namespace soa::server::mission_rules {

const char* mission_table(u32 type) {
    switch (type) {
        case 0:
            return "master_mission";
        case 1:
            return "master_event_mission";
        case 2:
            return "master_tower_mission";  // (b) MasterMissionModel::GetFromMissionID type 2
        case 3:
            return "master_world_map_mission";
        case 4:
            return "master_training_mission";  // (b) CStageManager::CallMissionStart: type 4 sends TrainingMissionStart
        default:
            return "";
    }
}

bool roll_percent(double rate_percent, u64 r) {
    if (rate_percent <= 0) return false;
    return (double)(r % 1000000) < rate_percent * 10000.0;
}

bool campaign_active(const std::string& opened_day, const std::string& opened_time, const std::string& closed_day, const std::string& closed_time,
                     int week_id, int64_t t) {
    int64_t o = parse_day_and_time(opened_day, opened_time), c = parse_day_and_time(closed_day, closed_time);
    if (o < 0 || c < 0 || t < o || t > c) return false;
    if (week_id >= 0 && week_id <= 6) {
        time_t tt = (time_t)t;
        struct tm tm;
        localtime_r(&tt, &tm);
        return tm.tm_wday == week_id;
    }
    return true;
}

bool campaign_applies(int campaign_model, u32 campaign_area, u32 mission_type, u32 area) {
    if (campaign_model != -2 && campaign_model != (int)mission_type) return false;
    return campaign_area == 0 || campaign_area == area;
}

bool continue_campaign_applies(int campaign_model, u32 campaign_area, bool every_type_pass, u32 mission_type, u32 area) {
    if (every_type_pass) return campaign_model == kEveryMissionModel;
    if (campaign_model != (int)mission_type) return false;
    return mission_type != 1 || campaign_area == 0 || campaign_area == area;
}

u32 continue_price(u32 price, double magnification) { return (u32)((float)magnification * (float)price); }

u32 campaign_stamina(u32 cost, double magnification) {
    if (cost == 0) return 0;
    double v = std::ceil((double)cost * magnification - 1e-9);
    return (u32)std::max(1.0, v);
}

int evaluation_rank(int type, const std::vector<u64>& conditions, u64 value) {
    for (size_t k = 0; k < conditions.size(); k++) {
        u64 c = conditions[k];
        if (c == 0) continue;
        bool met = type == 6 ? (value > 0 && value <= c) : value >= c;
        if (met) return (int)k + 1;
    }
    return 0;
}

const char* evaluation_log_field(int type) {
    switch (type) {
        case 1:
            return "damage_total";    // (b) uimsg_evaluation_condition1: total damage
        case 3:
            return "rush_cooperate";  // (b) rush-combo total damage
        case 4:
            return "hit_max";         // (b) highest hit count
        case 6:
            return "mission_time";    // (b) clear time in ms
        default:
            return "";               // (b) 2 (enemies defeated), 5 (highest single damage): no CBattleLogInfo field;
                                      // api/missions/ reads them from the evaluation array (battle_evaluation_value)
    }
}

CharacterBonus character_bonus(const std::vector<std::pair<u32, u32>>& matches, u32 max_lots, u32 max_extra) {
    CharacterBonus b;
    for (auto& [lots, extra] : matches) {
        b.lots += lots;
        b.extra += extra;
    }
    b.lots = std::min(b.lots, max_lots);
    b.extra = std::min(b.extra, max_extra);
    return b;
}

int stepup_index(const std::vector<u32>& steps, u32 next) {
    for (size_t k = 0; k < steps.size(); k++)
        if (steps[k] == next) return (int)k;
    return 0;
}

std::pair<int, u32> stepup_advance(const std::vector<u32>& steps, int index) {
    if (steps.empty()) return {0, 0};
    int n = index + 1;
    if (n >= (int)steps.size()) return {0, 1};
    return {n, 0};
}

int box_pick(const std::vector<u32>& remaining, u64 r) {
    u64 sum = 0;
    for (u32 x : remaining) sum += x;
    if (!sum) return -1;
    r %= sum;
    for (size_t k = 0; k < remaining.size(); k++) {
        if (r < remaining[k]) return (int)k;
        r -= remaining[k];
    }
    return -1;
}

}  // namespace soa::server::mission_rules
