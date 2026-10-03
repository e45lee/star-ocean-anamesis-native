// The favor event drop bonus (好感度イベントドロップ). Port code, not guest behaviour. Rules in
// docs/server-rules.md "Favor event drop bonus"; labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
// (b) The client never computes the bonus: the party screens show a per-character drop icon
// (CParameterUtility::GetFavorDropIconImageName: favor level >= 4, not spent since the day's reset,
// RemainingEventDropBonusCountByFavor non-zero), the result screen shows drop_type 4 drops with the
// heart badge (ResultUtility::GetRewardType / GetRewardBadgeIcon), and MissionEnd's
// MissionResultCharacterFavor[same_role_id].added_event_drop_at is copied into the favor map.
#include <algorithm>
#include <set>
#include <string>
#include <vector>

#include "core/log.h"
#include "api/events/event_extras.h"
#include "api/favor/favor.h"
#include "core/modules.h"

namespace soa::server::event_extras {
using namespace ext;

namespace {
// (b) Common::MissionDropType 4: a favor event drop (the result screen's heart badge).
constexpr u32 kDropTypeFavorEvent = 4;

// (a) master_favor_level.event_drop_bonus of a level (1 at level 4, 2 at level 5)
u32 bonus_of_level(Ctx& ctx, u32 level) { return (u32)ctx.m.one("select event_drop_bonus from master_favor_level where id = ?", {level}, 0); }
}  // namespace

// MissionStartExtra hook (MissionStart, registered below; favor_start's other half is favor_result).
// Rules: docs/server-rules.md "Favor event drop bonus"
//   (a)+(d) MissionStart of an event mission (d: master_event_mission only, like the Galaxy Pass's
//       extra event drop slot, subscmsg_gpass_drop_manual): the party's own characters (slot order)
//       whose favor level gives an event_drop_bonus and whose bonus isn't spent today, up to the
//       day's remaining uses (d: the limit counts characters). A restart keeps the play's set.
// Sets: MissionParameter.is_event_drop_by_favor (b: read by nothing in the client).
void favor_start(Ctx& ctx, const MissionInfo& mission, Value& param, Value&) {
    if (mission.restart) {
        param["is_event_drop_by_favor"] = ctx.st.one("select count(*) from favor_drop_play", {}) > 0;
        return;
    }
    ctx.st.exec("delete from favor_drop_play");
    if (mission.type != kMissionTypeEvent || mission.table != "master_event_mission") return;
    int64_t now = ctx.now();
    u32 left = favor::event_drop_remaining(ctx.st.h, ctx.m.h, now);
    std::set<u32> seen;
    for (u32 role : mission.roles) {
        if (!left) break;
        u32 same_role = (u32)ctx.m.one("select same_role_id from master_role where id = ?", {role});
        if (!same_role || !seen.insert(same_role).second) continue;
        u32 lots = bonus_of_level(ctx, favor::level_of(ctx.st.h, ctx.m.h, now, same_role));
        if (!lots || favor::event_drop_used_today(ctx.st.h, ctx.m.h, now, same_role)) continue;
        ctx.st.q("insert into favor_drop_play (same_role_id, lots) values (?, ?)", {same_role, lots});
        left--;
    }
    int64_t characters = ctx.st.one("select count(*) from favor_drop_play", {});
    param["is_event_drop_by_favor"] = characters > 0;
    if (characters) LOGI("server", "MissionStart: favor event drop bonus for %lld characters", (long long)characters);
}

// favor_result: run by world_boss.cpp's MissionResultExtra hook (event_extras.h: first of the three).
// Rules: docs/server-rules.md "Favor event drop bonus"
// MissionEnd (win): (d) each character's event_drop_bonus lots from the mission's own drop rows
// (non-fixed, non-surprise, no host bonus; by rate_weigh), as drop_type 4 (b: the heart badge);
// the characters' bonus is spent (added_event_drop_at = now, sent in MissionResultCharacterFavor)
// and the day's remaining count follows.
void favor_result(Ctx& ctx, const MissionInfo& mission, Value& data) {
    std::vector<std::pair<u32, u32>> used;  // (same_role_id, lots)
    ctx.st.q("select same_role_id, lots from favor_drop_play", {},
             [&](const Row& play_row) { used.emplace_back((u32)play_row.i("same_role_id"), (u32)play_row.i("lots")); });
    ctx.st.exec("delete from favor_drop_play");
    if (used.empty()) return;
    struct DropRow {
        u32 type, id, num, weight;
    };
    std::vector<DropRow> drop_rows;
    u64 sum = 0;
    ctx.m.q(
        "select * from master_mission_drop where master_mission_id = ? and ifnull(is_surprise_enemy, 0) = 0 and ifnull(is_fix_drop, 0) = 0 "
        "and ifnull(host_bonus, 0) = 0 and rate_weigh > 0",
        {mission.mission}, [&](const Row& drop_row) {
            drop_rows.push_back({(u32)drop_row.i("content_type"), (u32)drop_row.i("content_id"), (u32)std::max<int64_t>(1, drop_row.i("num")),
                                 (u32)drop_row.i("rate_weigh")});
            sum += (u32)drop_row.i("rate_weigh");
        });
    int64_t now = ctx.now();
    u32 lots = 0;
    for (auto& [same_role, character_lots] : used) {
        for (u32 k = 0; k < character_lots && sum; k++) {
            u64 pick = (*ctx.rng)() % sum;
            for (const DropRow& drop : drop_rows) {
                if (pick < drop.weight) {
                    add_drop(ctx, data, drop.type, drop.id, drop.num, kDropTypeFavorEvent);
                    break;
                }
                pick -= drop.weight;
            }
            lots++;
        }
        std::string at = favor::mark_event_drop(ctx.st.h, same_role, now);
        // (b) the core's favor entry of the character (a character with a favor level has one);
        // (d) left alone otherwise: a partial element would reset the client's favor level
        Value& favor_map = data["MissionResultCharacterFavor"];
        for (auto& [key, entry] : favor_map.map)
            if (key == std::to_string(same_role) && entry.type == Value::Map) entry["added_event_drop_at"] = at;
    }
    data["RemainingEventDropBonusCountByFavor"] = favor::event_drop_remaining(ctx.st.h, ctx.m.h, now);
    LOGI("server", "MissionEnd mission %u: favor event drop bonus, %zu characters, %u lots", mission.mission, used.size(), lots);
}

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_favor_drop() {
    using namespace ext;
    add_mission_start_extra([](Ctx& ctx, const MissionInfo& mission, Value& param, Value& data) { favor_start(ctx, mission, param, data); });
}

}  // namespace soa::server::event_extras
