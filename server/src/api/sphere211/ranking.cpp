// Sphere 211: the season ranking, its reward groups and its reward (api/sphere211/README.md;
// declared in dive.h). Port code, not guest behaviour; every rule carries its source label,
// (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption. Rules in
// docs/server-rules.md "Sphere 211".
#include <algorithm>
#include <string>
#include <vector>

#include "api/sphere211/dive.h"
#include "core/log.h"

namespace soa::server::sphere211 {

// A season's ranking reward group: its master_sphere211_ranking_reward_id (a); (d) the last season
// (13) has none (the service ended with it), and as it repeats past the end it gets the group of
// the latest season before it that has one. The client's master copy gets the same group (a data
// override: CSphereRankingResult shows the reward of Sphere211EndResult.previous_season_id's
// group, b), so the season-end dialog shows what was granted.
u32 ranking_group_of(ext::Sql& master, u32 season_id) {
    u32 group = 0;
    std::string opened_at;
    master.q("select coalesce(nullif(master_sphere211_ranking_reward_id, ''), 0) g, opened_at from master_sphere211 where id = ?", {season_id},
             [&](const Row& season_row) {
                 group = (u32)season_row.i("g");
                 opened_at = season_row.s("opened_at");
             });
    if (!group && !opened_at.empty())
        group = (u32)master.one(
            "select coalesce(nullif(master_sphere211_ranking_reward_id, ''), 0) from master_sphere211 where opened_at < ? and "
            "coalesce(nullif(master_sphere211_ranking_reward_id, ''), 0) != 0 order by opened_at desc limit 1",
            {opened_at});
    return group;
}
void client_ranking_groups(ext::Sql& db, int64_t, int64_t) {
    std::vector<u32> without_group;
    db.q("select id from master_sphere211 where coalesce(nullif(master_sphere211_ranking_reward_id, ''), 0) = 0", {},
         [&](const Row& season_row) { without_group.push_back((u32)season_row.i("id")); });
    for (u32 season_id : without_group)
        if (u32 group = ranking_group_of(db, season_id))
            db.q("update master_sphere211 set master_sphere211_ranking_reward_id = ? where id = ?", {group, season_id});
}

// The season's ranking reward for `rank` (master_sphere211_ranking_reward of its group, a): the
// row with the smallest required_ranking at or above the rank (b: CSphereRankingResult::Initialize
// shows the row whose range, the previous row's required_ranking + 1 .. its own, holds the rank).
// (b) granted straight into the items: uimsg_sphere211_ranking_result "ランキング報酬が所持アイテムに
// 追加されました" (the dialog has no present-box step).
void ranking_reward(Ctx& ctx, u32 season_id, u32 rank) {
    u32 group = ranking_group_of(ctx.m, season_id);
    Value items = Value::array(), stocks = Value::array(), characters = Value::array();
    ctx.m.q(
        "select content_type, content_id, num, id_label from master_sphere211_ranking_reward where ranking_reward_group_id = ? and "
        "required_ranking >= ? order by required_ranking limit 1",
        {group, rank}, [&](const Row& reward_row) {
            grant_content(ctx, (u32)reward_row.i("content_type"), (u32)reward_row.i("content_id"), (u32)std::max<int64_t>(1, reward_row.i("num")),
                          items, stocks, characters);
            LOGI("server", "Sphere211: season %u ranking reward for rank %u: %s", season_id, rank, reward_row.s("id_label").c_str());
        });
}

// (d) a local ranking of one player: the best floor of the season (Sphere211RankingInfoMap
// {player id: {player_id, floor_level, entered_at, rank}}), rank 1.
Value ranking_info_map(Ctx& ctx, const Season& season) {
    Value map = Value::object();
    u32 player_id = ctx.player_id();
    ctx.st.q("select * from sphere_rank where season_id = ?", {season.id}, [&](const Row& rank_row) {
        Value info = Value::object();
        info["player_id"] = player_id;
        info["floor_level"] = (u32)rank_row.i("floor_level");
        info["entered_at"] = ctx.fmt_time(rank_row.i("entered_at"));
        info["rank"] = 1u;
        map[std::to_string(player_id)] = info;
    });
    return map;
}

}  // namespace soa::server::sphere211
