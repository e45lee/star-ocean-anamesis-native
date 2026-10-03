// Sphere 211: the treasure boxes ("T data") a dive gathers, their ranks and what they open into
// (api/sphere211/README.md; declared in dive.h). Port code, not guest behaviour; every rule carries
// its source label, (a) master data, (b) client-side evidence, (c) outside knowledge,
// (d) assumption. Rules in docs/server-rules.md "Sphere 211".
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "api/sphere211/dive.h"
#include "core/log.h"

namespace soa::server::sphere211 {

namespace {
constexpr u32 kContentItemSet = 99;  // (a) docs/api.md "Content types": a master_item_set
// A box's rank, 0 = S .. 4 = D (the s..d columns of master_sphere211_treasure /
// master_sphere211_treasure_contents); the client keys them the other way round (b).
constexpr u32 kRankD = 4;
}  // namespace

void grant_content(Ctx& ctx, u32 type, u32 id, u32 num, Value& items, Value& stocks, Value& characters) {
    if (type == kContentItemSet) {
        ctx.m.q("select content_type, content_id, num from master_item_set where item_set_id = ? order by order_id", {id}, [&](const Row& set_row) {
            grant_content(ctx, (u32)set_row.i("content_type"), (u32)set_row.i("content_id"), (u32)set_row.i("num") * num, items, stocks, characters);
        });
        return;
    }
    ctx.grant(type, id, num, items, stocks, characters);
}

// Treasure boxes ("T data"): `count` more boxes gathered on `floor`, unopened. Their ranks are
// lotted when they are analysed (ReturnSphere211).
void add_boxes(Ctx& ctx, const Floor& floor, u32 count) {
    for (u32 k = 0; k < count; k++) ctx.st.q("insert into sphere_box (floor_level, rank) values (?, -1)", {floor.level});
    ctx.st.q("update sphere set treasure_total = treasure_total + ?", {count});
}

// Lots the rank (0 = S .. 4 = D) of every unopened box with the current floor's
// master_sphere211_treasure s..d weights (a; b: the return dialog shows these rates for the
// floor the player is on, MissionUtility::Sphere211BoxRate).
void lot_ranks(Ctx& ctx, const Season& season) {
    u32 level = (u32)ctx.st.one("select floor_level from sphere where id = 1", {});
    Floor floor = floor_row(ctx, season, std::max<u32>(1, level));
    std::vector<std::pair<u32, u32>> weights;
    ctx.m.q("select * from master_sphere211_treasure where id = ?", {floor.treasure_id}, [&](const Row& treasure_row) {
        const char* cols[] = {"s_weight", "a_weight", "b_weight", "c_weight", "d_weight"};
        for (u32 rank = 0; rank <= kRankD; rank++) weights.push_back({(u32)treasure_row.i(cols[rank]), rank});
    });
    std::vector<int64_t> box_ids;
    ctx.st.q("select id from sphere_box where rank < 0 order by id", {}, [&](const Row& box_row) { box_ids.push_back(box_row.i("id")); });
    for (int64_t box_id : box_ids) {
        int k = weighted_index(ctx, weights);
        ctx.st.q("update sphere_box set rank = ? where id = ?", {k < 0 ? kRankD : weights[k].second, box_id});
    }
}

// Opens the dive's boxes: each box one row of its rank's common drop group
// (master_sphere211_treasure_contents <rank>_common_drop_id, a) lotted by rate_weigh (a), granted
// to the player (d: directly, as the box result screen shows them obtained).
void open_boxes(Ctx& ctx, const Season& season, Value* items, Value* stocks, Value* characters, Value* result) {
    lot_ranks(ctx, season);
    u32 drop_groups[kRankD + 1] = {};
    ctx.m.q("select * from master_sphere211_treasure_contents where id = ?", {season.treasure_contents}, [&](const Row& contents_row) {
        const char* cols[] = {"s_common_drop_id", "a_common_drop_id", "b_common_drop_id", "c_common_drop_id", "d_common_drop_id"};
        for (u32 rank = 0; rank <= kRankD; rank++) drop_groups[rank] = (u32)contents_row.i(cols[rank]);
    });
    Value no_items = Value::array(), no_stocks = Value::array(), no_characters = Value::array();
    std::vector<std::pair<int64_t, u32>> boxes;
    ctx.st.q("select id, rank from sphere_box order by id", {},
             [&](const Row& box_row) { boxes.push_back({box_row.i("id"), (u32)box_row.i("rank")}); });
    for (auto [box_id, rank] : boxes) {
        struct Content {
            u32 type, id, num;
        };
        std::vector<std::pair<u32, Content>> drops;
        ctx.m.q("select rate_weigh, content_type, content_id, num from master_common_drop where common_drop_id = ?",
                {drop_groups[std::min<u32>(rank, kRankD)]}, [&](const Row& drop_row) {
                    drops.push_back({(u32)drop_row.i("rate_weigh"),
                                     {(u32)drop_row.i("content_type"), (u32)drop_row.i("content_id"), (u32)std::max<int64_t>(1, drop_row.i("num"))}});
                });
        int k = weighted_index(ctx, drops);
        if (k < 0) continue;
        Content content = drops[k].second;
        ctx.grant(content.type, content.id, content.num, items ? *items : no_items, stocks ? *stocks : no_stocks,
                  characters ? *characters : no_characters);
        if (result) {
            // (b) Sphere211TreasureResultInfoMap {rank: [Sphere211TreasureResultInfo {content_id,
            // num}]} (the list class has no key of its own; CSphereBoxResult::GetRewardItemList),
            // (d) content_type added for completeness.
            Value info = Value::object();
            info["content_id"] = content.id;
            info["content_type"] = content.type;
            info["num"] = content.num;
            Value& list = (*result)[std::to_string(kRankD - std::min<u32>(rank, kRankD))];  // client keys: 0 D .. 4 S (b)
            if (list.type != Value::Arr) list = Value::array();
            list.push(info);
        }
    }
    ctx.st.exec("delete from sphere_box");
    LOGI("server", "Sphere211: %zu boxes opened", boxes.size());
}

}  // namespace soa::server::sphere211
