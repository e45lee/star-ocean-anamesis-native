// Sphere 211: the rental slot (the party's 4th) and the Sphere 211 rental bonus
// (api/sphere211/README.md; declared in dive.h). Port code, not guest behaviour; every rule carries
// its source label, (a) master data, (b) client-side evidence, (c) outside knowledge,
// (d) assumption. Rules in docs/server-rules.md#sphere211.
#include <charconv>
#include <string>
#include <system_error>
#include <tuple>
#include <vector>

#include "api/player/roster.h"  // owns_character
#include "api/social/rental.h"
#include "api/sphere211/dive.h"
#include "core/log.h"
#include "core/time.h"

namespace soa::server::sphere211 {

// ---- the rental slot --------------------------------------------------------------------------
// (b) The party's 4th slot lends a followed player's character: CParameterUtility::
// CreateSphere211RentalList walks Sphere211RentalCharacterInfoMap (CParameterManager+0xa008; per
// entry player_id, follow_player_id, is_used, updated_at; entries with is_used are skipped when the
// party asks, the list is sorted by updated_at), keeps the follow_player_ids that are in FollowID
// and not in BlacklistID, and builds each from the Sphere211RentalCharacterDetailInfoMap entry
// (+0xa058) whose pc.player_id is that id: a CFollowInfo {order, player, pc}, the shape of
// BattleRental (tCharaData::InitializeRental). The board shows them as the followee icons
// (CSphereMissionMenu::UpdateBadgeAndFollowee). (a) master_text cp0003_tutorial_sphere211_007:
// followed players on the same floor lend "１フロアにつき合計３回まで".
// (d) There are no other players: the lenders are the synthetic rental players of api/social/rental.cpp
// (rental.h follow_map: clones of the player's own characters), all of them followed (FollowID,
// sent with the Sphere 211 responses) and on the player's floor (Sphere211FollowFloorInfoList);
// each lends once per floor, and after three rentals on a floor every lender counts as used.
namespace {
constexpr u32 kFollowStatusFollowed = 1;  // (d) Sphere211FollowFloorInfo.follow_status of a followed lender
bool floor_rentals_used_up(Ctx& ctx) { return ctx.st.one("select count(*) from sphere_rental where used = 1", {}) >= kRentalsPerFloor; }
}  // namespace

void put_rental(Ctx& ctx, u32 floor, Value& data) {
    Value lenders = rental::follow_map(ctx);
    u32 player_id = ctx.player_id().v;  // the wire's number
    bool full = floor_rentals_used_up(ctx);
    Value info_map = Value::object(), follow_ids = Value::array(), floors = Value::array();
    ServerTime t = ctx.now();
    for (auto& [key, entry] : lenders.map) {
        u32 lender = 0;
        if (auto [end, ec] = std::from_chars(key.data(), key.data() + key.size(), lender); ec != std::errc() || end != key.data() + key.size()) {
            LOGW("server", "Sphere211 rental: lender \"%s\" isn't a player id: skipped", key.c_str());
            continue;
        }
        bool used = false;
        ServerTime updated_at = t;
        ctx.st.q("select used, updated_at from sphere_rental where follow_player_id = ?", {lender}, [&](const Row& rental_row) {
            used = rental_row.i("used") != 0;
            updated_at = rental_row.time("updated_at");
        });
        Value info = Value::object();
        info["player_id"] = player_id;
        info["follow_player_id"] = lender;
        info["is_used"] = used || full;
        info["updated_at"] = ctx.fmt_time(updated_at);
        info_map[key] = info;
        follow_ids.push(lender);
        Value floor_info = Value::object();
        floor_info["player_id"] = lender;
        floor_info["floor_level"] = floor;
        floor_info["follow_status"] = kFollowStatusFollowed;
        floors.push(floor_info);
        if (Value* player = entry.type == Value::Map && entry.find("player") ? &entry["player"] : nullptr) (*player)["sphere211_floor_level"] = floor;
    }
    data["Sphere211RentalCharacterInfoMap"] = info_map;
    data["Sphere211RentalCharacterDetailInfoMap"] = lenders;
    data["Sphere211FollowFloorInfoList"] = floors;
    data["FollowID"] = follow_ids;
}

// A rental id (rental.h) lent by one of the floor's lenders that hasn't lent on this floor, while
// the floor has rentals left, whose roster character exists.
bool rental_available(Ctx& ctx, u32 lender, u64 rental_id) {
    bool listed = rental::follow_map(ctx).find(std::to_string(lender)) != nullptr;
    bool used = ctx.st.one("select count(*) from sphere_rental where follow_player_id = ? and used = 1", {lender}) > 0;
    bool full = floor_rentals_used_up(ctx);
    std::optional<CharacterUid> source = rental::source_uid(rental_id);
    return listed && !used && !full && source && owns_character(ctx, *source);
}

// The Sphere 211 rental bonus (a: master_sphere211_rental_bonus, one row per season: rental_count
// 5 -> the season's reroll item x1, present_message_id sphere_rental_bonus_1 "スフィア211レンタル
// ボーナス"). (b) The home popup of CPopupManager::CheckStart case 5 opens when Sphere211RentalBonus
// (the row id: CSphereRentalBonus::Setup looks the row up by id) and Sphere211RentalCount are both
// non-zero, and says uimsg_sphere211_getting_rental_bonus "前日、%u人のユーザーがあなたをレンタルしました
// ... あなたのフォロワーから%sが%u個届いています" with the row's content; the 3.7.0 login's
// CPopupManager::AddPopup() arms it (mask 0x7b). MissionUtility::Sphere211RentalBonusItem(count)
// picks the season's row with the highest rental_count at or below the count (b).
// (d) Nobody else rents on a local server: the rentals counted are the player's own Sphere 211
// rentals (MissionStart, per rental day from master_global login_bonus_reset_hour, the daily reset;
// the season they were made in). Each earlier unpaid day pays once, on the next full player load,
// into the present box ("届いています"), like the rental bonus of api/social/rental.cpp.
namespace {
ServerTime rental_day(Ctx& ctx, ServerTime t) {
    return day_start(t, (int)ctx.global_u32("login_bonus_reset_hour", 4));  // (a)
}
}  // namespace

// (d) a rented character doesn't depart; its lender has lent on this floor; the day's rentals count.
void record_rental(Ctx& ctx, const Season& season, u32 lender, ServerTime t) {
    ctx.st.q("insert or replace into sphere_rental (follow_player_id, used, updated_at) values (?, 1, ?)", {lender, t});
    ctx.st.q("insert into sphere_rental_day (rental_day, season_id, count) values (?, ?, 1) on conflict(rental_day) do update set count = count + 1",
             {rental_day(ctx, t), season.id});
}

void rental_bonus(Ctx& ctx, Value& data) {
    ServerTime today = rental_day(ctx, ctx.now());
    std::vector<std::tuple<ServerTime, u32, u32>> due;  // day, season, count
    ctx.st.q("select rental_day, season_id, count from sphere_rental_day where paid = 0 and rental_day < ? order by rental_day", {today},
             [&](const Row& day_row) { due.emplace_back(day_row.time("rental_day"), (u32)day_row.i("season_id"), (u32)day_row.i("count")); });
    u32 last_id = 0, last_count = 0;
    for (auto& [day, season_id, count] : due) {
        ctx.m.q("select * from master_sphere211_rental_bonus where master_sphere211_id = ? and rental_count <= ? order by rental_count desc limit 1",
                {season_id, count}, [&](const Row& bonus_row) {
                    std::string line = ext::display_text(ctx.m, bonus_row.s("present_message_id"));
                    ext::add_present(ctx, (u32)bonus_row.i("content_type"), (u32)bonus_row.i("content_id"), (u32)bonus_row.i("num"),
                                     ext::kPresentAchievement, (u32)bonus_row.i("id"), line);
                    last_id = (u32)bonus_row.i("id");
                    last_count = count;
                    // read by port/scripts/sphere211_session.sh, sphere211_continue_session.sh ("5 rentals")
                    LOGI("server", "Sphere211 rental bonus: %u rentals on day %lld -> %s: %u x %s", count, (long long)day.v,
                         bonus_row.s("id_label").c_str(), (u32)bonus_row.i("num"), bonus_row.s("content_id_label").c_str());
                });
        ctx.st.q("update sphere_rental_day set paid = 1 where rental_day = ?", {day});
    }
    if (!last_id) return;
    data["Sphere211RentalBonus"] = last_id;
    data["Sphere211RentalCount"] = last_count;
    data["PresentBoxCount"] = (u32)ctx.st.one("select count(*) from presents where received_at is null", {});
}

}  // namespace soa::server::sphere211
