// The drop roll of a won mission (api/missions/missions.h). Port code, not guest behaviour.
// Every rule carries its source label, (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption (docs/server-rules.md "Server missions").
#include "api/missions/missions.h"

#include <algorithm>

#include "core/server.h"  // one_null_as_zero
#include "rules/mission_rules.h"

namespace soa::server {

using ext::Arg;
using ext::body;
using ext::Row;

// (a) master_mission_drop / master_common_drop / master_campaign_drop rows; (d) lot
// semantics: each lot picks one row by rate_weigh; rows with is_fix_drop always drop;
// (a)+(d) host_bonus rows only drop for a multiplayer host, so never here.
void lottery(ext::Ctx& ctx, const std::string& sql, Arg key, int64_t lots, DropType drop_type, std::vector<Drop>& out, bool fixed) {
    std::vector<Drop> rows;
    std::vector<u32> weights;
    ctx.m.q(sql, {key}, [&](const Row& drop_row) {
        if (!drop_row.null("host_bonus") && drop_row.i("host_bonus")) return;
        Drop drop{(u32)drop_row.i("content_type"), (u32)drop_row.i("content_id"), (u32)std::max<int64_t>(1, drop_row.i("num")), (u32)drop_type};
        if (!drop_row.null("is_fix_drop") && drop_row.i("is_fix_drop")) {
            if (fixed) out.push_back(drop);
        } else if (drop_row.i("rate_weigh") > 0) {
            rows.push_back(drop);
            weights.push_back((u32)drop_row.i("rate_weigh"));
        }
    });
    u64 sum = 0;
    for (u32 weight : weights) sum += weight;
    for (int64_t k = 0; k < lots && sum; k++) out.push_back(rows[rules::weighted_pick(weights, (*ctx.rng)() % sum)]);
}

namespace {

// The lot counts of a mission row (a).
struct LotCounts {
    int64_t lots = 0;           // lot_drop_count
    int64_t surprise_lots = 0;  // lot_surprise_drop_count
    int64_t common_lots = 0;    // lot_common_drop_count
    int64_t common_drop_id = 0;
    int64_t evaluation_group_id = 0;  // (a) event missions only
};

LotCounts lot_counts(ext::Ctx& ctx, const std::string& table, u32 mission) {
    LotCounts counts;
    ctx.m.q("select * from " + table + " where id = ?", {mission}, [&](const Row& mission_row) {
        counts.lots = mission_row.i("lot_drop_count");
        counts.surprise_lots = mission_row.i("lot_surprise_drop_count");
        counts.common_lots = mission_row.i("lot_common_drop_count");
        counts.common_drop_id = mission_row.i("common_drop_id");
        counts.evaluation_group_id = mission_row.i("evaluation_group_id");
    });
    return counts;
}

// (a) campaigns of type 0 (Campaign_evo_*_prism) running for this mission: lot_drop_count_add
// more lots, and (d) one lot from the campaign's master_campaign_drop rows.
std::vector<Campaign> drop_campaigns(ext::Ctx& ctx, const std::string& table, u32 type, u32 area) {
    MissionRef ref;
    ref.table = table, ref.type = type, ref.area = area, ref.found = true;
    std::vector<Campaign> running;
    for (const Campaign& campaign : campaigns_for(ctx, ref))
        if (campaign.type == CampaignType::kDropLots) running.push_back(campaign);
    return running;
}

// (a) master_mission_character_bonus rows of the mission (or its area) inside their window,
// one match per party member of that role category: bonus_count more lots and
// extra_bonus_num x the extra content, (a) capped by master_global max_character_bonus /
// max_character_extra_bonus ((d) per party). Sets rolled.bonus_lots / bonus_extra; returns the
// extra content.
Drop character_bonus(ext::Ctx& ctx, u32 mission, u32 area, const std::vector<u32>& party_roles, Rolled& rolled) {
    std::vector<std::pair<u32, u32>> matches;  // bonus_count, extra_bonus_num
    Drop extra{0, 0, 0, 0};
    std::string now = format_time(clock_now());
    for (u32 role : party_roles) {
        // (master_role has no NULL role_category_id in 3.7.0, so the NULL-as-0 read and the default agree)
        int64_t category = one_null_as_zero(ctx.m, "select role_category_id from master_role where id = ?", {role}, -1);
        ctx.m.q(
            "select * from master_mission_character_bonus where master_role_category_id = ? and "
            "(master_mission_id = ? or (master_mission_id is null and master_area_id = ?)) and "
            "(opened_at is null or opened_at <= ?) and (closed_at is null or closed_at >= ?) limit 1",
            {category, mission, area, now, now}, [&](const Row& bonus_row) {
                matches.emplace_back((u32)bonus_row.i("bonus_count"), (u32)bonus_row.i("extra_bonus_num"));
                if (bonus_row.i("extra_bonus_content_id"))
                    extra = Drop{(u32)bonus_row.i("extra_bonus_content_type"), (u32)bonus_row.i("extra_bonus_content_id"), 0, 0};
            });
    }
    auto capped = mission_rules::character_bonus(matches, ctx.global_u32("max_character_bonus", 2), ctx.global_u32("max_character_extra_bonus", 2));
    rolled.bonus_lots = capped.lots;
    rolled.bonus_extra = extra.id ? capped.extra : 0;
    return extra;
}

// (a) battle evaluation (event missions with an evaluation_group_id): per evaluation, the best
// rank the battle log reaches pays rank_N_drop_count lots from its drop set (the
// master_mission_drop rows labelled master_mission_drop_id_label); (b) the log values.
void evaluation_drops(ext::Ctx& ctx, int64_t evaluation_group_id, Rolled& rolled) {
    ctx.m.q("select * from master_battle_evaluation where evaluation_group_id = ? order by order_id", {evaluation_group_id},
            [&](const Row& evaluation_row) {
                int type = (int)evaluation_row.i("evaluation_type");
                // (b) the battle's evaluation array (battle_evaluation_value), else the battle log
                // property of the type (types 2 and 5 have none)
                const char* field = mission_rules::evaluation_log_field(type);
                int64_t value_of_type = ctx.live() ? battle_evaluation_value(ctx, type) : -1;
                if (value_of_type < 0 && !*field && ctx.live()) return;
                u64 value = value_of_type >= 0 ? (u64)value_of_type : ctx.live() ? battle_log_u32(ctx, field, 0) : ctx.request->test_log_value;
                std::vector<u64> conditions;
                for (int k = 1; k <= 5; k++) conditions.push_back((u64)evaluation_row.i(("rank_" + std::to_string(k) + "_condition").c_str()));
                int rank = mission_rules::evaluation_rank(type, conditions, value);
                if (!rank) return;
                u32 lots = (u32)evaluation_row.i(("rank_" + std::to_string(rank) + "_drop_count").c_str());
                rolled.evaluations.push_back((u32)evaluation_row.i("id"));
                rolled.eval_lots += lots;
                lottery(ctx, "select * from master_mission_drop where master_mission_id_label = ?", evaluation_row.s("master_mission_drop_id_label"),
                        lots, DropType::kPlain, rolled.drops, false);
            });
}

}  // namespace

// The whole drop roll of a won mission (docs/server-rules.md 2.4, "Server missions"). The lots are
// drawn in a fixed order (the RNG's): normal, campaign, character bonus, campaign drops, the
// bonus extra, surprise, common, evaluation.
Rolled roll_drops(ext::Ctx& ctx, u32 mission, const std::string& table, u32 type, u32 area, bool surprise, const std::vector<u32>& party_roles) {
    Rolled rolled;
    std::vector<Drop>& out = rolled.drops;
    const LotCounts counts = lot_counts(ctx, table, mission);
    const std::vector<Campaign> campaigns = drop_campaigns(ctx, table, type, area);
    for (const Campaign& campaign : campaigns) rolled.campaign_lots += campaign.extra_lots;
    const Drop extra = character_bonus(ctx, mission, area, party_roles, rolled);
    const std::string normal = "select * from master_mission_drop where master_mission_id = ? and ifnull(is_surprise_enemy, 0) = 0";
    lottery(ctx, normal, mission, counts.lots, DropType::kPlain, out);
    // (a) extra lots (campaign, character bonus) draw from the same rows; (d) without fixed rows
    // again. drop_type (Common::MissionDropType, DropType): (b) character-bonus drops are 5.
    if (rolled.campaign_lots) lottery(ctx, normal, mission, rolled.campaign_lots, DropType::kPlain, out, false);
    if (rolled.bonus_lots) lottery(ctx, normal, mission, rolled.bonus_lots, DropType::kCharacterBonus, out, false);
    for (const Campaign& campaign : campaigns)
        lottery(ctx, "select * from master_campaign_drop where master_campaign_id = ?", campaign.id, 1, DropType::kPlain, out);
    if (rolled.bonus_extra) out.push_back(Drop{extra.type, extra.id, rolled.bonus_extra, (u32)DropType::kCharacterBonus});
    // (a) the surprise enemy's lot_surprise_drop_count lots from its is_surprise_enemy rows
    if (surprise) {
        rolled.surprise_lots = (u32)counts.surprise_lots;
        lottery(ctx, "select * from master_mission_drop where master_mission_id = ? and is_surprise_enemy = 1", mission, counts.surprise_lots,
                DropType::kPlain, out);
    }
    // (b) drop_type 0 for common drops too: 2 is the beginner badge (初心者), which the first server
    // core sent
    if (counts.common_drop_id)
        lottery(ctx, "select *, 0 as is_fix_drop from master_common_drop where common_drop_id = ?", counts.common_drop_id, counts.common_lots,
                DropType::kPlain, out);
    if (counts.evaluation_group_id) evaluation_drops(ctx, counts.evaluation_group_id, rolled);
    return rolled;
}

}  // namespace soa::server
