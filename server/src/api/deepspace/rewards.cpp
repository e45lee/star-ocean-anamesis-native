// Deep space: the drops of an expedition and the bonuses that change them (api/deepspace/README.md;
// declared in deepspace.h). Port code, not guest behaviour; every rule carries its source label,
// (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption. Rules in
// docs/server-rules.md#deepspace.
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

#include "api/deepspace/deepspace.h"
#include "core/time.h"

namespace soa::server::deepspace {

namespace {

// (a) master_deep_space_bonus.bonus_effect_id; (c)+(d) the effects from their names in master_text
// name_ds_bonus_* (roll_rewards).
enum class BonusEffect : int { kRareMissionRate = 1, kRareDropRate = 2, kExtraLots = 3, kHitTable = 4 };
// (d) CDropContentInfo.bonus_category: the result screen's bonus marks.
enum class BonusCategory : int { kNone = 0, kHit = 1, kAdd = 2, kRare = 3 };

// One lot from a master_deep_space_drop_item table: (a) the rows of `where` (drop_type_id or
// drop_type_id_label = key) open by the calendar, picked by rate_weigh.
bool draw(Ctx& ctx, const std::string& where, ext::Arg key, Lot& out) {
    std::vector<Lot> rows;
    std::vector<u32> weights;
    ctx.m.q("select * from master_deep_space_drop_item where " + where + " order by order_id, id", {key}, [&](const Row& drop_row) {
        if (!open_at(drop_row.s("opened_at"), drop_row.s("closed_at"), calendar(ctx)) || drop_row.i("rate_weigh") <= 0) return;
        rows.push_back(Lot{(u32)drop_row.i("content_type"), (u32)drop_row.i("content_id"), (u32)std::max<int64_t>(1, drop_row.i("num"))});
        weights.push_back((u32)drop_row.i("rate_weigh"));
    });
    u64 sum = 0;
    for (u32 w : weights) sum += w;
    if (!sum) return false;
    out = rows[rules::weighted_pick(weights, (*ctx.rng)() % sum)];
    return true;
}

// A bonus that adds lots: effect 3 (`add`: `lots` more lots of the mission's tables) or 4 (one lot
// of the table `table`), each with `percent` %.
struct ExtraLots {
    std::string table;
    double percent;
    u32 lots;
    bool add;
};

}  // namespace

double uniform(Ctx& ctx) { return (double)((*ctx.rng)() >> 11) / 9007199254740992.0; }

// (a) drop_count lots from drop_type_id; (a)+(d) each lot comes from rare_drop_type_id instead
// with rare_drop_rate percent (x the rare-drop bonuses). Bonuses of the ship ((a) bonus_effect_id,
// (c)+(d) the effects from their names in master_text name_ds_bonus_*):
//   1 "レア探査ポイント発見率アップ" multiplies the rare-mission rate by the bonus value;
//   2 "レアアイテム発見率アップ" multiplies the rare-drop rate by the bonus value;
//   3 "+N追加アイテム発見率" adds bonus_effect_param1 lots with bonus_effect_param2 percent x value;
//   4 "X発見率アップ" draws one lot from the drop table named bonus_effect_param1 (drop_type_id_label)
//     with bonus_effect_param3 percent x value.
Rewards roll_rewards(Ctx& ctx, u32 mission_id, u32 ship_id) {
    Rewards rewards;
    double rare_drop_mul = 1.0;
    std::vector<ExtraLots> extras;
    ctx.st.q("select bonus_id, value from ds_bonus where ship_id = ?", {ship_id}, [&](const Row& ship_bonus_row) {
        double value = ship_bonus_row.f("value");
        ctx.m.q("select * from master_deep_space_bonus where id = ?", {ship_bonus_row.i("bonus_id")}, [&](const Row& bonus_row) {
            auto effect = (BonusEffect)bonus_row.i("bonus_effect_id");
            if (effect == BonusEffect::kRareMissionRate) rewards.rare_mission_mul *= value;
            else if (effect == BonusEffect::kRareDropRate) rare_drop_mul *= value;
            else if (effect == BonusEffect::kExtraLots)
                extras.push_back(
                    {"", atof(bonus_row.s("bonus_effect_param2").c_str()) * value, (u32)atoi(bonus_row.s("bonus_effect_param1").c_str()), true});
            else if (effect == BonusEffect::kHitTable)
                extras.push_back({bonus_row.s("bonus_effect_param1"), atof(bonus_row.s("bonus_effect_param3").c_str()) * value, 1, false});
        });
    });
    u32 drop_count = 0, drop_type = 0, rare_type = 0;
    double rare_rate = 0;
    ctx.m.q("select * from master_deep_space_mission where id = ?", {mission_id}, [&](const Row& mission_row) {
        drop_count = (u32)mission_row.i("drop_count");
        drop_type = (u32)mission_row.i("drop_type_id");
        rare_type = (u32)mission_row.i("rare_drop_type_id");
        rare_rate = mission_row.f("rare_drop_rate");
    });
    auto draw_lot = [&](bool add) {
        Lot lot;
        bool rare = rare_type && uniform(ctx) * 100.0 < rare_rate * rare_drop_mul;
        if (rare ? draw(ctx, "drop_type_id = ?", rare_type, lot) : draw(ctx, "drop_type_id = ?", drop_type, lot)) {
            lot.rare = rare;
            lot.add = add;
            BonusCategory category = rare ? BonusCategory::kRare : add ? BonusCategory::kAdd : BonusCategory::kNone;
            lot.category = (int)category;  // (d) the result screen's bonus marks
            rewards.lots.push_back(lot);
        }
    };
    for (u32 k = 0; k < drop_count; k++) draw_lot(false);
    for (auto& extra : extras) {
        if (uniform(ctx) * 100.0 >= extra.percent) continue;
        if (extra.add) {
            for (u32 k = 0; k < extra.lots; k++) draw_lot(true);
        } else {
            Lot lot;
            if (draw(ctx, "drop_type_id_label = ?", extra.table, lot)) {
                lot.hit = true;
                lot.category = (int)BonusCategory::kHit;
                rewards.lots.push_back(lot);
            }
        }
    }
    return rewards;
}

}  // namespace soa::server::deepspace
