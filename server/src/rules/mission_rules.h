#pragma once
// The local server's mission-side rules (restore run; our code, not guest behaviour):
// pure functions over master-data values, unit-tested in mission_rules.cpp. Every rule carries its
// source label: (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption;
// see docs/server-rules.md#server-missions.
#include <cstdint>
#include <string>
#include <vector>

namespace soa::server::mission_rules {

using u32 = uint32_t;
using u64 = uint64_t;

// Common::MissionType -> the master table of its missions ("" if the server doesn't know it).
// (b) CParameterUtility::FindMissionWithId(id, type) / (a) the model types of master_campaign:
// 0 story (master_mission), 1 event (master_event_mission), 2 tower (master_tower_mission; (b)
// MasterMissionModel::GetFromMissionID), 3 world map (master_world_map_mission). Type 5 (Sphere 211)
// searches every table (b) and so has no table of its own.
const char* mission_table(u32 type);

// True when `rate_percent` (e.g. 10.25) succeeds for the uniform draw `r` in [0, 1'000'000).
bool roll_percent(double rate_percent, u64 r);

// A master_campaign row's window at the local time `t` (seconds since the epoch):
// (a) opened_day + opened_time .. closed_day + closed_time ("YYYY-MM-DD", "HH:MM:SS"), and
// (a)+(d) week_id 7 = every day (the only value in the data); 0..6 = that weekday (Sunday 0,
// as master_event_weekly).
bool campaign_active(const std::string& opened_day, const std::string& opened_time, const std::string& closed_day, const std::string& closed_time,
                     int week_id, int64_t t);

// Whether a campaign of model type `campaign_model` for area `campaign_area` applies to a mission
// of type `mission_type` in area `area`: (a) model -2 = every mission type, else it must equal
// the mission type; area 0 / none = every area of that type, else it must be the mission's area.
bool campaign_applies(int campaign_model, u32 campaign_area, u32 mission_type, u32 area);

// A stamina cost under a stamina campaign (type 1, magnification 0.5): (d) rounded up, at least 1
// (a zero cost stays 0).
u32 campaign_stamina(u32 cost, double magnification);

// The best battle-evaluation rank (1 = best .. 5) a value reaches, or 0: (a) the conditions
// rank_1..5_condition (0 = no such rank), (b) type 6 (clear time) is met by values <= the
// condition, the others by values >= (uimsg_evaluation_condition1..6), (d) best rank first.
int evaluation_rank(int type, const std::vector<u64>& conditions, u64 value);

// The battle-log property the evaluation type reads, or "" (b: CBattleLogInfo names;
// d: the mapping of types 2 and 5 has no log field and is left out).
const char* evaluation_log_field(int type);

// Character bonus: the extra lots and extra-content count for a party whose members match
// `matches` bonus rows (each giving bonus_count / extra_bonus_num), capped by (a) master_global
// max_character_bonus / max_character_extra_bonus, (d) the caps apply per party.
struct CharacterBonus {
    u32 lots = 0, extra = 0;
};
CharacterBonus character_bonus(const std::vector<std::pair<u32, u32>>& matches, u32 max_lots, u32 max_extra);

// Step-up gacha: the step a chain is at. `steps` = the chain's gacha ids in stepup_number order
// (step 1 first); `next` = the stored next_master_gacha_id (0 = not started). Returns the index
// of the current step (0 if `next` isn't in the chain).
int stepup_index(const std::vector<u32>& steps, u32 next);
// After drawing step `index`: {next index, restart increment} ((a) the last step's
// next_stepup_gacha_id points back to step 1: a loop restarts the chain).
std::pair<int, u32> stepup_advance(const std::vector<u32>& steps, int index);

// Box gacha: picks one of the remaining slots (`remaining[k]` copies of slot k) uniformly by
// copy, with `r` uniform; -1 when the box is empty. (a) rate_weigh is 1 everywhere, (c) a box
// draws without replacement.
int box_pick(const std::vector<u32>& remaining, u64 r);

}  // namespace soa::server::mission_rules
