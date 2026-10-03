#pragma once
// Deep space (api/deepspace/README.md): what the module's files share. Internal to the module
// (the handlers in deepspace.cpp, the offers and answers in state.cpp, the party bonuses in
// bonuses.cpp, the rewards in rewards.cpp) and its tests; the APIs themselves are reached through
// ext::find("DeepSpace..."). Labels: (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption.
#include <string>
#include <utility>
#include <vector>

#include "soaserver/ext.h"

namespace soa::server::deepspace {

using ext::Ctx;
using ext::Row;

// ---- clocks (state.cpp) --------------------------------------------------------------------
// Expedition timers (a ship's started_at / closed_at, a rare offer's limit, the quick-return price
// and its daily count) run on the server clock ctx.now() (clock_now: --clock / the tests
// fast-forward them). Dated master rows use the event calendar ctx.event_now() when only the
// server reads them (bonus sets, drop items, bonus items): calendar(). Rows the client also filters
// by its own clock (data.Time = the server clock): areas and missions (b: CDeepSpace::
// GetDeepSpaceAreaList / GetDeepSpaceMissionList drop those outside opened_at..closed_at) must be
// open by both, or the server would offer what the client hides: open_by_both_clocks(). The ship
// count reads the server clock only (b: CUIUtility::GetMaxShipCount).
int64_t calendar(Ctx& ctx);
bool open_by_both_clocks(Ctx& ctx, const std::string& opened_at, const std::string& closed_at);

// ---- areas and offers (state.cpp) ------------------------------------------------------------
// A master_deep_space_area row (a).
struct Area {
    u32 id = 0;
    std::string label, resource;
    u32 max_exp = 0;
    bool required = false;
    std::vector<std::pair<u32, double>> requirements;  // (required area, exploration rate %)
    std::string opened_at, closed_at;
};
std::vector<Area> areas(Ctx& ctx);
u32 area_exp(Ctx& ctx, u32 area_id);
// Opens the areas the clock and the exploration rates allow, offers their normal missions and
// drops the offers that ran out (rules in state.cpp).
void refresh_offers(Ctx& ctx, int64_t t);
// (a) a master_deep_space_bonus_set row of `set_type` open by the calendar, picked by rate_weigh;
// 0 when none.
u32 roll_bonus_set(Ctx& ctx, u32 set_type);
// The start of t's play-limit day (the daily reset).
int64_t limit_day(Ctx& ctx, int64_t t);
// Whether an offer (a ds_offer row) has used up its plays for the period.
bool at_limit(Ctx& ctx, const Row& offer_row);

// ---- ships (state.cpp) -----------------------------------------------------------------------
u32 subscription_ships(Ctx& ctx, int64_t t);
u32 max_ships(Ctx& ctx, int64_t t);
// The uids of a ds_ship row's `uids` text ("uid,uid,...").
std::vector<u64> parse_uids(const std::string& uids);
// The quick returns used today (resets the count on a new day).
u32 time_saving_count(Ctx& ctx, int64_t t);

// ---- the answers' values (state.cpp; the client's info classes, b) ---------------------------
Value area_info(Ctx& ctx, const Area& area, int64_t t);  // CDeepSpaceAreaInfo
void put_area_info(Ctx& ctx, Value& data, u32 area_id, int64_t t);  // data.DeepSpaceArea: the area's, when it exists
Value area_list(Ctx& ctx, int64_t t);                    // DeepSpaceAreaList
Value ship_info(Ctx& ctx, const Row& ship_row);          // CDeepSpaceShipInfo
Value ship_list(Ctx& ctx, int64_t t, bool ended);        // DeepSpaceActiveShipInfoList / DeepSpaceEndShipInfoList
Value ship_info_of(Ctx& ctx, u32 ship_id);               // DeepSpaceShip
Value character_map(Ctx& ctx);                           // characters {uid: CDeepSpaceCharacterInfo}
Value bonus_apply_list(Ctx& ctx, int64_t only_ship = -1);  // DeepSpaceBonusAllApplyInfoList
Value deep_mission_player(Ctx& ctx, int64_t t, bool level_up);  // DeepMissionPlayer

// ---- the party and its bonuses (bonuses.cpp) ---------------------------------------------------
constexpr size_t kMaxMembers = 8;  // (b) uimsg_deep_space_select_num "%d / ８"
// What the bonus conditions read of a character.
struct Member {
    u64 uid = 0;
    u32 role_id = 0, level = 0, limit_break = 0, awaken = 0, category = 0;
    std::string weapon_kind;
    float battle_power = 0;
};
Member member(Ctx& ctx, u64 uid);
// Whether a master_deep_space_bonus row applies to a member.
bool applies(const Row& bonus_row, const Member& m);
// Whether a master_deep_space_bonus row sums battle power (condition2 5) rather than members.
bool sums_battle_power(const Row& bonus_row);
// The bonuses of a bonus set for a party, valued by the client's rule.
std::vector<std::pair<u32, float>> party_bonuses(Ctx& ctx, u32 set_id, const std::vector<Member>& party);
// Every character not out on a ship (roster order).
std::vector<u64> free_characters(Ctx& ctx);

// ---- MissionEnd's rewards (rewards.cpp) --------------------------------------------------------
// One drop lot.
struct Lot {
    u32 type, id, num;
    int category = 0;  // CDropContentInfo.bonus_category (BonusCategory)
    bool rare = false, add = false, hit = false;
};
struct Rewards {
    std::vector<Lot> lots;
    double rare_mission_mul = 1.0;  // the rare-point bonuses' factor on the rare-mission rate
};
Rewards roll_rewards(Ctx& ctx, u32 mission_id, u32 ship_id);
// The next uniform [0, 1) of the server's RNG.
double uniform(Ctx& ctx);

}  // namespace soa::server::deepspace
