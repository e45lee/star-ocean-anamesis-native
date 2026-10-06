// Local server: items and stamina. ItemCompose(Array), ItemGradeUp(Array), InheritAccessory,
// MaterialCompose, SellItem(Array) / SellStackItem, LockItem(Array) / UnlockItem(Array),
// UseHealItem, StaminaHeal, UpdateItemStock (SellGear: gear.cpp). Rules in docs/server-rules.md#player-rank-stamina,
// docs/server-rules.md#weapons-and-accessories, docs/server-rules.md#growth-and-economy, docs/server-rules.md#items-and-stamina; labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include <cmath>

#include "api/items/items.h"
#include "core/log.h"
#include "soaserver/ext.h"
#include "core/errors.h"
#include "core/wallet.h"
#include "rules/growth_rules.h"
#include "core/modules.h"

namespace soa::server {

bool item_equipped(ext::Ctx& ctx, ItemUid item_uid) {
    return ctx.st.one(
               "select exists (select 1 from roster where weapon_uid = ?1 or accessory_uid = ?1)"
               " or exists (select 1 from party_member where weapon_uid = ?1 or accessory_uid = ?1)",
               {item_uid}) > 0;
}

// (b) an item in the equipment storage isn't in the inventory: the client removes it from its item
// list (CApiNotify::AddStorage @014d437c) and can't equip or strengthen it (a: master_text
// cp0003_tutorial_151 "装備倉庫の中に入っている武器やアクセサリーの装備や強化はできない").
bool owns_item(ext::Ctx& ctx, ItemUid item_uid) {
    return ctx.st.one("select count(*) from items where uid = ? and stored_at is null", {item_uid}) > 0;
}

namespace {
using namespace ext;

// The content type MaterialCompose grants when its recipe names none: a stack item (a: docs/api.md
// "Content types" 5).
constexpr u32 kContentStackItem = 5;
// master_material_compose's ingredient columns master_item1..5_id / item1..5_num (a).
constexpr int kRecipeIngredients = 5;

// One owned weapon or accessory (an `items` row) with its master_item fields.
struct Item {
    bool ok = false;
    ItemUid uid;
    MasterItemId id;
    u32 type = 0, points = 0, lb = 0, rarity = 0, sale_fol = 0;  // points: boosted points (`exp`); lb: limit break
    bool locked = false, equipped = false;
};
// The item `uid` of the inventory (not ok when it is in the equipment storage, owns_item), or with
// `stored` one of the equipment storage.
Item find_item(Ctx& ctx, ItemUid uid, bool stored = false) {
    Item item;
    ctx.st.q(std::string("select * from items where uid = ? and stored_at is ") + (stored ? "not null" : "null"), {uid}, [&](const Row& item_row) {
        item.ok = true;
        item.uid = uid;
        item.id = item_row.id<MasterItemId>("master_item_id");
        item.type = (u32)item_row.i("item_type");
        item.points = (u32)item_row.i("exp");
        item.lb = (u32)item_row.i("limit_break");
        item.locked = item_row.i("locked") != 0;
    });
    if (!item.ok) return item;
    ctx.m.q("select rarity, sale_fol from master_item where id = ?", {item.id}, [&](const Row& master_row) {
        item.rarity = (u32)master_row.i("rarity");
        item.sale_fol = (u32)master_row.i("sale_fol");
    });
    item.equipped = item_equipped(ctx, uid);
    return item;
}
// The compose table of an item type: accessories have their own (a).
const char* compose_table(u32 type) { return type == item_type::kAccessory ? "master_item_accessory_compose" : "master_item_compose"; }
// (a) the level cap: level_max of the rarity, or master_item_limit_break_level_max for a limit
// break > 0 (type 1 weapons, 3 accessories)
u32 item_cap(Ctx& ctx, const Item& item) {
    if (item.lb) {
        u32 cap = (u32)ctx.m.one("select level_max from master_item_limit_break_level_max where type = ? and limit_break = ?", {item.type, item.lb});
        if (cap) return cap;
    }
    return (u32)ctx.m.one(std::string("select level_max from ") + compose_table(item.type) + " where rarity = ?", {item.rarity}, 10);
}
u32 item_level_of(Ctx& ctx, const Item& item) {
    u32 next = (u32)ctx.m.one(std::string("select next_level_boosted_point from ") + compose_table(item.type) + " where rarity = ?", {item.rarity});
    return growth_rules::item_level(item.points, next, item_cap(ctx, item));
}
// What selling an item pays: (b) weapons round(sale_fol x master_item_sale_rate[level].sale_rate),
// others sale_fol (CParameterUtility::tItemData::SellingPrice).
u32 sale_fol(Ctx& ctx, const Item& item) {
    double rate = 1.0;
    if (item.type == item_type::kWeapon) {
        u32 level = item_level_of(ctx, item);
        ctx.m.q("select sale_rate from master_item_sale_rate where id = ?", {level}, [&](const Row& rate_row) { rate = rate_row.f("sale_rate"); });
    }
    return growth_rules::sell_price(item.sale_fol, rate);
}

// What a material is to a compose's limit break, beyond a copy of the base: a limit-break item
// ("hammer", …ハンマー：上限解放素材 / マジカルスレッド) that fits the base, one that doesn't, or
// neither (an ordinary material).
enum class LimitBreakItem { kNone, kFits, kOtherBase };
// (b) the client's rule:
//   A limit-break item is a strengthening material (CParameterUtility::IsStrengMaterialWithMaster
//   @0180a2d0: the item's master_weapon kind, CMasterCache::IsStrengMaterial @01692f9c: the kind
//   label contains "W99St") listed by item_id in master_weapon_limit_break (weapons:
//   CItemStrengtheningPotal::IsLimitBrealItem @01b8975c) or master_accessory_limit_break
//   (accessories: IsAccessoryLimitBrealItem @01b897bc); (a) all 185 rows are W99St items.
//   It fits a weapon (CItemStrengtheningList::IsAvailableLimitBreak @01b746fc) when its row has a
//   weapon_type_id and that is the base's master_weapon_kind_id or the row's weapon_type_id_label
//   is "ALL" (the generic hammers: by kind, whatever the base's family), or, without a
//   weapon_type_id, when the row's limitbreak_type_id is the base's master_item.limitbreak_type_id
//   (the family hammers). It fits an accessory (IsAvailableAccessoryLimitBreak @01b75a4c) when
//   its row's limitbreak_type_id is set and accessory_type_id_label is "ALL" or that type is the
//   base's (a: the one row, マジカルスレッド, is ALL).
LimitBreakItem limit_break_item(Ctx& ctx, const Item& base, const Item& material) {
    bool strengthening_material = ctx.m.one(
                                      "select count(*) from master_item i join master_weapon w on w.id = i.master_weapon_id "
                                      "join master_weapon_kind k on k.id = w.master_weapon_kind_id where i.id = ? and instr(k.id_label, 'W99St') > 0",
                                      {material.id}) > 0;
    if (!strengthening_material) return LimitBreakItem::kNone;
    int64_t base_family = ctx.m.one("select ifnull(limitbreak_type_id, 0) from master_item where id = ?", {base.id});
    bool listed = false, fits = false;
    if (base.type == item_type::kAccessory) {
        ctx.m.q(
            "select ifnull(limitbreak_type_id, 0) as family, ifnull(accessory_type_id_label, '') as label from master_accessory_limit_break "
            "where item_id = ? order by id limit 1",
            {material.id}, [&](const Row& row) {
                listed = true;
                fits = row.i("family") != 0 && (row.s("label") == "ALL" || row.i("family") == base_family);
            });
    } else {
        int64_t base_kind = ctx.m.one(
            "select w.master_weapon_kind_id from master_item i join master_weapon w on w.id = i.master_weapon_id where i.id = ?", {base.id});
        ctx.m.q(
            "select ifnull(weapon_type_id, 0) as kind, ifnull(weapon_type_id_label, '') as label, ifnull(limitbreak_type_id, 0) as family "
            "from master_weapon_limit_break where item_id = ? order by id limit 1",
            {material.id}, [&](const Row& row) {
                listed = true;
                fits = row.i("kind") ? (row.i("kind") == base_kind || row.s("label") == "ALL") : row.i("family") == base_family;
            });
    }
    if (!listed) return LimitBreakItem::kNone;
    return fits ? LimitBreakItem::kFits : LimitBreakItem::kOtherBase;
}

// The arguments of ItemCompose(Array) and ItemGradeUp(Array): (u64 base uid, vector<u64> materials).
struct BaseAndMaterialsArgs {
    ItemUid base_uid;
    std::vector<ItemUid> material_uids;
    static BaseAndMaterialsArgs from(const Request& req) { return {ItemUid(req.ints.size() > 0 ? req.ints[0] : 0), item_uid_list(req)}; }
};

// What one ItemCompose changes, for its answer.
struct Composed {
    Item base, after;
    u32 level_before = 0, level_after = 0;
    u64 cost = 0;
    bool big = false;
    Value lost = Value::array();
};
// ComposeResult (CItemComposeResultInfo's fields, b), with the player state and Item (and
// InheritAccessory's InheritResultInfo).
std::vector<u8> compose_response(Ctx& ctx, const Composed& composed, const Value* inherited = nullptr) {
    Value data = ctx.base_data();
    if (inherited) data["InheritResultInfo"] = *inherited;  // InheritAccessory's
    Value result = Value::object();
    result["id"] = composed.base.uid.v;
    result["before_level"] = composed.level_before;
    result["before_boosted_point"] = composed.base.points;
    result["before_limit_break_count"] = composed.base.lb;
    result["after_level"] = composed.level_after;
    result["after_boosted_point"] = composed.after.points;
    result["after_limit_break_count"] = composed.after.lb;
    result["is_big_success"] = composed.big;
    result["use_fol"] = (u32)composed.cost;
    result["lost_item_ids"] = composed.lost;
    result["UpdateGearList"] = Value::array();
    data["ComposeResult"] = result;
    data["Item"] = ctx.items();
    return body(data);
}

std::vector<u8> compose(Ctx& ctx, const char* method, ItemUid base_uid, const std::vector<ItemUid>& materials, Composed& composed);

// ItemCompose(u64 base uid, vector<u64> material uids) -> ItemComposeRes   fid 02a5cd1d
//   (also ItemComposeArray, the same request)
// API: docs/api.md#itemcomposearray   Rules: docs/server-rules.md#items-and-stamina, docs/server-rules.md#weapons-and-accessories
//
// Feeds weapons / accessories to a base item: boosted points, levels and limit breaks.
//   (b) each material adds growth_rules::compose_points (CItemStrengtheningPotal::GetAddBoostedPoint).
//   (a) a copy of the base's own item raises its limit break (master_item_limit_break_level_max);
//   (b) so does a limit-break item that fits the base (limit_break_item: master_weapon_limit_break /
//   master_accessory_limit_break); one raise per copy or item, up to the cap, counted as
//   `weapon_limit_break` / `accessory_limit_break` (achievement type 6); every compose counts
//   `weapon_boost` / `accessory_boost` (types 5 / 38).
//   (a) use_fol_one per material, (b) at the material's rarity (the screen's 必要FOL); (d) the
//   type-2 FOL campaigns the screen applies aren't; weapon_compose_up_rate / weapon_compose_bonus_rate.
//   (d) locked or equipped materials and the base itself can't be fed; points stop at the cap
//   level's threshold.
//   (d) Refusals: kItemUnusable (10208) without a base weapon / accessory or materials, or for a
//   limit-break item that doesn't fit the base (b: the client never offers one), kLockedItem
//   (10204) for a material, kFolShortGrowth (11001) for the FOL.
// Answers: the player state, ComposeResult and Item.
std::vector<u8> item_compose(Ctx& ctx, const Request& req) {
    const auto args = BaseAndMaterialsArgs::from(req);
    Composed composed;
    if (std::vector<u8> refused = compose(ctx, "ItemCompose", args.base_uid, args.material_uids, composed); !refused.empty()) return refused;
    return compose_response(ctx, composed);
}

// The compose itself (ItemCompose's rules above; also InheritAccessory's): the base grows, the
// materials go, the FOL is paid, the counters count. A refusal's answer, or empty when composed.
std::vector<u8> compose(Ctx& ctx, const char* method, ItemUid base_uid, const std::vector<ItemUid>& materials, Composed& composed) {
    Item& base = composed.base;
    base = find_item(ctx, base_uid);
    if (!base.ok || (base.type != item_type::kWeapon && base.type != item_type::kAccessory) || materials.empty())
        return refuse(ctx, method, "no base item or no materials", ErrorCode::kItemUnusable);
    const char* table = compose_table(base.type);
    u32 next = (u32)ctx.m.one(std::string("select next_level_boosted_point from ") + table + " where rarity = ?", {base.rarity});
    u32 lb_max = (u32)ctx.m.one("select max(limit_break) from master_item_limit_break_level_max where type = ?", {base.type}, 5);
    u64 gain = 0;
    u32 lb = base.lb;
    for (ItemUid material_uid : materials) {
        Item material = find_item(ctx, material_uid);
        // (d) locked or equipped items and the base itself can't be fed
        if (!material.ok || material.locked || material.equipped || material_uid == base_uid)
            return refuse(ctx, method, "a material is locked, equipped or missing", ErrorCode::kLockedItem);
        // (a) a copy of the same item raises the limit break (master_item_limit_break_level_max);
        // (b) so does a limit-break item that fits the base, one raise each
        // (CItemStrengtheningPotal::GetAddLimitReleaseWeaponNum @01b899d8 /
        // GetAddLimitReleaseAccessoryNum @01b89b70: a copy first, else a limit-break item)
        bool raises = material.id == base.id;
        if (!raises) {
            LimitBreakItem hammer = limit_break_item(ctx, base, material);
            // (b) the material list never offers one that doesn't fit (CItemStrengtheningList::
            // CreateWeaponList / CreateAccessoryList skip it); (d) refused, with kItemUnusable
            if (hammer == LimitBreakItem::kOtherBase)
                return refuse(ctx, method, "a limit-break item that doesn't fit the base", ErrorCode::kItemUnusable);
            raises = hammer == LimitBreakItem::kFits;
        }
        if (raises && lb < lb_max) lb++;
        u32 boosted_point = (u32)ctx.m.one(std::string("select boosted_point from ") + table + " where rarity = ?", {material.rarity});
        gain += growth_rules::compose_points(material.points, boosted_point);
        // (a) use_fol_one per material, (b) of the material's rarity: the strengthening screen's
        // 必要FOL (CItemStrengtheningPotal::InitializePotal @01b856ac, the loop ending at 01b86cdc)
        // sums,
        // for each material, the tItemComposeParam's use_fol_one (master +0x198) whose rarity
        // (+0xa8) is the material's master rarity (+0x118), the match GetAddBoostedPoint
        // (@01b891c8) makes for the points; the table is the base's (CreateItemComposeList
        // @01b83aa0: weapons master_item_compose, accessories _accessory_compose)
        composed.cost += (u64)ctx.m.one(std::string("select use_fol_one from ") + table + " where rarity = ?", {material.rarity});
    }
    if (fol(ctx) < composed.cost) return refuse(ctx, method, "not enough FOL", ErrorCode::kFolShortGrowth);
    // (a) weapon_compose_up_rate (percent, (d) the meaning) / weapon_compose_bonus_rate
    composed.big = (double)((*ctx.rng)() % 10000) < global_f(ctx, "weapon_compose_up_rate", 11.5) * 100.0;
    if (composed.big) gain = (u64)std::floor((double)gain * global_f(ctx, "weapon_compose_bonus_rate", 1.5));
    Item& after = composed.after;
    after = base;
    after.lb = lb;
    u32 cap = item_cap(ctx, after);
    // (d) points stop at the cap level's threshold
    u64 points = std::min<u64>((u64)base.points + gain, next ? (u64)(cap - 1) * next : 0);
    after.points = (u32)points;
    composed.level_before = item_level_of(ctx, base), composed.level_after = item_level_of(ctx, after);
    ctx.st.q("update items set exp = ?, limit_break = ?, level = ? where uid = ?", {after.points, lb, composed.level_after, base_uid});
    for (ItemUid material_uid : materials) {
        ctx.st.q("delete from items where uid = ?", {material_uid});  // its gear goes with it (ON DELETE CASCADE)
        composed.lost.push(material_uid.v);
    }
    add_fol(ctx, -(int64_t)composed.cost);
    count(ctx, base.type == item_type::kAccessory ? "accessory_boost" : "weapon_boost");
    // The limit-break raises of this compose, one per raise (achievement type 6, 武器を N回上限解放する:
    // api/presents/achievements.cpp). (b) A compose raises the limit break once per qualifying
    // material: CItemStrengtheningPotal::GetAddLimitReleaseWeaponNum (@01b899d8) adds 1 for each
    // material of the base's item id or a limit-break item, and WarningLimitbreak (@01b8a810)
    // warns when the current limit break plus that sum reaches 6; (a) the cap is
    // master_item_limit_break_level_max's highest limit_break (5). The raises counted are the ones
    // applied above (lb - base.lb), so nothing is counted past the cap.
    if (lb > base.lb) count(ctx, base.type == item_type::kAccessory ? "accessory_limit_break" : "weapon_limit_break", (int64_t)(lb - base.lb));
    LOGI("server", "%s %llx: +%llu points%s, level %u -> %u, limit break %u -> %u, FOL -%llu", method, (unsigned long long)base_uid.v,
         (unsigned long long)gain, composed.big ? " (big success)" : "", composed.level_before, composed.level_after, base.lb, lb,
         (unsigned long long)composed.cost);
    return {};
}

// ItemGradeUp(u64 base uid, vector<u64> material uids) -> ItemGradeUpRes   fid 8952aa02
//   (also ItemGradeUpArray, the same request)
// API: docs/api.md#itemgradeuparray   Rules: docs/server-rules.md#items-and-stamina, docs/server-rules.md#weapons-and-accessories
//
// Turns a weapon and its materials into a weapon of the next grade.
//   (a) master_item_grade_up by rarity: grade_up_num materials, use_fol; the new weapon from
//   master_item_grade_up_list (the base's rarity and weapon kind) by rate_weigh.
//   (d) rows opened by the server clock; the base becomes the new weapon at level 1; locked or
//   equipped materials can't be used.
//   (d) Refusals: kItemUnusable (10208) without a base weapon, a wrong count or no candidate,
//   kLockedItem (10204) for a material, kFolShortGrowth (11001) for the FOL.
// Answers: the player state, GradeUpResult and Item.
std::vector<u8> item_grade_up(Ctx& ctx, const Request& req) {
    const auto args = BaseAndMaterialsArgs::from(req);
    const ItemUid base_uid = args.base_uid;
    const auto& materials = args.material_uids;
    Item base = find_item(ctx, base_uid);
    if (!base.ok || base.type != item_type::kWeapon) return refuse(ctx, "ItemGradeUp", "no base weapon", ErrorCode::kItemUnusable);
    // (a) master_item_grade_up by rarity: grade_up_num materials, use_fol
    u32 need = 0, cost = 0;
    ctx.m.q("select * from master_item_grade_up where id = ?", {base.rarity}, [&](const Row& grade_up_row) {
        need = (u32)grade_up_row.i("grade_up_num");
        cost = (u32)grade_up_row.i("use_fol");
    });
    if (!need || materials.size() != need) return refuse(ctx, "ItemGradeUp", "wrong number of materials", ErrorCode::kItemUnusable);
    for (ItemUid material_uid : materials) {
        Item material = find_item(ctx, material_uid);
        if (!material.ok || material.locked || material.equipped || material_uid == base_uid)
            return refuse(ctx, "ItemGradeUp", "a material is locked, equipped or missing", ErrorCode::kLockedItem);
    }
    if (fol(ctx) < cost) return refuse(ctx, "ItemGradeUp", "not enough FOL", ErrorCode::kFolShortGrowth);
    // (a) the new weapon from master_item_grade_up_list rows of the base's rarity and weapon kind
    // by rate_weigh; (d) rows opened by the server clock
    u32 kind = (u32)ctx.m.one("select w.master_weapon_kind_id from master_item i join master_weapon w on w.id = i.master_weapon_id where i.id = ?",
                              {base.id});
    std::vector<u32> ids, weights;
    std::string now = ctx.fmt_time(ctx.now());
    ctx.m.q(
        "select master_item_id, rate_weigh from master_item_grade_up_list where rarity = ? and master_weapon_kind_id = ? and "
        "(opened_at is null or opened_at <= ?) and (closed_at is null or closed_at >= ?)",
        {base.rarity, kind, now, now}, [&](const Row& candidate_row) {
            ids.push_back((u32)candidate_row.i("master_item_id"));
            weights.push_back((u32)std::max<int64_t>(0, candidate_row.i("rate_weigh")));
        });
    u64 sum = 0;
    for (u32 weight : weights) sum += weight;
    if (!sum) return refuse(ctx, "ItemGradeUp", "no grade-up candidates", ErrorCode::kItemUnusable);
    u32 got = ids[rules::weighted_pick(weights, (*ctx.rng)() % sum)];
    // (d) the base becomes the new weapon, fresh (level 1, no limit break); materials are lost
    ctx.st.q("update items set master_item_id = ?, item_type = (select 1), exp = 0, limit_break = 0, level = 1 where uid = ?", {got, base_uid});
    Value lost = Value::array();
    for (ItemUid material_uid : materials) {
        ctx.st.q("delete from items where uid = ?", {material_uid});  // its gear goes with it (ON DELETE CASCADE)
        lost.push(material_uid.v);
    }
    add_fol(ctx, -(int64_t)cost);
    count(ctx, "weapon_grade_up");
    Value data = ctx.base_data();
    Value result = Value::object();
    result["grade_up_m_item_id"] = got;
    result["base_item_id"] = base_uid.v;
    result["use_fol"] = cost;
    result["lost_item_ids"] = lost;
    result["UpdateGearList"] = Value::array();
    data["GradeUpResult"] = result;
    data["Item"] = ctx.items();
    LOGI("server", "ItemGradeUp %llx: item %u -> %u, FOL -%u", (unsigned long long)base_uid.v, base.id.v, got, cost);
    return body(data);
}

// MaterialCompose's arguments: (u32 master_material_compose id, u32 times); 0 or missing times = 1.
struct MaterialComposeArgs {
    u32 recipe_id = 0, times = 1;
    static MaterialComposeArgs from(const Request& req) {
        return {req.ints.size() > 0 ? (u32)req.ints[0] : 0, req.ints.size() > 1 && req.ints[1] ? (u32)req.ints[1] : 1};
    }
};

// MaterialCompose(u32 recipe id, u32 times) -> MaterialComposeRes          fid f9a4ba8c
// API: docs/api.md#materialcompose   Rules: docs/server-rules.md#items-and-stamina
//
// Makes stack items from stack items.
//   (a) master_material_compose: up to five (item, num), use_fol -> result item x num, per time;
//   the result's content type (d: a stack item when the row names none).
//   (d) Refusals: kItemUnusable (10208) for an unknown recipe, kItemCountError (10206) for the
//   materials, kFolShortGrowth (11001) for the FOL.
// Answers: the player state, AddItem (when the result is a unique item) and StockItem.
std::vector<u8> material_compose(Ctx& ctx, const Request& req) {
    const auto args = MaterialComposeArgs::from(req);
    u32 id = args.recipe_id, times = args.times;
    bool found = false;
    u32 cost = 0, result_type = 0, result_id = 0, result_num = 0;
    std::vector<std::pair<u32, u32>> need;
    // (a) master_material_compose: up to five (item, num), use_fol -> result item x num
    ctx.m.q("select * from master_material_compose where id = ?", {id}, [&](const Row& recipe_row) {
        found = true;
        cost = (u32)recipe_row.i("use_fol");
        result_type = (u32)recipe_row.i("result_content_type");
        result_id = (u32)recipe_row.i("result_item_id");
        result_num = (u32)recipe_row.i("result_item_num");
        for (int k = 1; k <= kRecipeIngredients; k++) {
            std::string item_col = "master_item" + std::to_string(k) + "_id", num_col = "item" + std::to_string(k) + "_num";
            if (recipe_row.i(item_col.c_str()) && recipe_row.i(num_col.c_str()))
                need.emplace_back((u32)recipe_row.i(item_col.c_str()), (u32)recipe_row.i(num_col.c_str()));
        }
    });
    if (!found) return refuse(ctx, "MaterialCompose", "unknown recipe", ErrorCode::kItemUnusable);
    for (auto& [item, num] : need)
        if (stock_count(ctx, item) < (u64)num * times) return refuse(ctx, "MaterialCompose", "not enough materials", ErrorCode::kItemCountError);
    if (fol(ctx) < (u64)cost * times) return refuse(ctx, "MaterialCompose", "not enough FOL", ErrorCode::kFolShortGrowth);
    for (auto& [item, num] : need) add_stock(ctx, item, -(int64_t)num * times);
    add_fol(ctx, -(int64_t)cost * times);
    Value added_items = Value::array(), stocks = Value::array(), chars = Value::array();
    ctx.grant(result_type ? result_type : kContentStackItem, result_id, result_num * times, added_items, stocks, chars);
    Value data = ctx.base_data();
    ext::add_items(data, added_items);
    data["StockItem"] = ctx.stock();
    LOGI("server", "MaterialCompose %u x%u: item %u x%u, FOL -%u", id, times, result_id, result_num * times, cost * times);
    return body(data);
}

// SellStackItem's arguments: (u32 master item id, u32 count).
struct SellStackItemArgs {
    u32 item = 0, count = 0;
    static SellStackItemArgs from(const Request& req) {
        return {req.ints.size() > 0 ? (u32)req.ints[0] : 0, req.ints.size() > 1 ? (u32)req.ints[1] : 0};
    }
};

// SellItem(vector<u64> item uids) -> SellItemRes                           fid 00ee45f7
//   (also SellItemArray, the same request; SellStackItem(u32 item, u32 count), fid 445ab956)
// API: docs/api.md#sellitemarray, docs/api.md#sellstackitem   Rules: docs/server-rules.md#items-and-stamina, docs/server-rules.md#weapons-and-accessories
//
// Sells weapons / accessories, or a count of one stack item, for FOL.
//   (b) weapons: round(sale_fol x master_item_sale_rate[level].sale_rate); others sale_fol
//   (CParameterUtility::tItemData::SellingPrice). (a) stack items: sale_fol x count.
//   (d) locked or equipped items can't be sold.
//   (d) Refusals: kItemCountError (10206) for a stack item short, kLockedItem (10204) for a
//   locked, equipped or missing item.
// Answers: the player state, SellResult {total_fol, master_item_id, num, item_ids, StockItem,
// UpdateGearList} and StockItem (SellStackItem) or Item.
std::vector<u8> sell_item(Ctx& ctx, const Request& req) {
    u64 total = 0;
    Value ids = Value::array(), stock_map = Value::object();
    u32 sold_item = 0, sold_num = 0;
    if (req.method == "SellStackItem") {
        const auto args = SellStackItemArgs::from(req);
        sold_item = args.item;
        sold_num = args.count;
        if (!sold_num || stock_count(ctx, sold_item) < sold_num) return refuse(ctx, "SellStackItem", "not enough items", ErrorCode::kItemCountError);
        // (a) stack items: sale_fol x count
        total = (u64)ctx.m.one("select sale_fol from master_item where id = ?", {sold_item}) * sold_num;
        add_stock(ctx, sold_item, -(int64_t)sold_num);
        Value entry = Value::object();
        entry["master_item_id"] = sold_item;
        entry["use_count"] = stock_count(ctx, sold_item);
        stock_map[std::to_string(sold_item)] = entry;
    } else {
        for (ItemUid uid : item_uid_list(req)) {
            Item item = find_item(ctx, uid);
            if (!item.ok || item.locked || item.equipped)
                return refuse(ctx, req.method.c_str(), "an item is locked, equipped or missing", ErrorCode::kLockedItem);
        }
        for (ItemUid uid : item_uid_list(req)) {
            total += sale_fol(ctx, find_item(ctx, uid));
            ctx.st.q("delete from items where uid = ?", {uid});  // its gear goes with it (ON DELETE CASCADE)
            ids.push(uid.v);
        }
    }
    add_fol(ctx, (int64_t)total);
    Value data = ctx.base_data();
    Value result = Value::object();
    result["total_fol"] = (u32)total;
    result["master_item_id"] = sold_item;
    result["num"] = sold_num;
    result["item_ids"] = ids;
    result["StockItem"] = stock_map;
    result["UpdateGearList"] = Value::array();
    data["SellResult"] = result;
    if (req.method == "SellStackItem") data["StockItem"] = ctx.stock();
    else data["Item"] = ctx.items();
    LOGI("server", "%s: +%llu FOL (%zu items%s)", req.method.c_str(), (unsigned long long)total, ids.arr.size(), sold_item ? ", stack item" : "");
    return body(data);
}

// LockItem(vector<u64> item uids) -> LockItemRes                           fid 88f29383
//   (also LockItemArray; UnlockItem(Array), fid 2f9569e5: the same with the lock off)
// API: docs/api.md#lockitemarray, docs/api.md#unlockitemarray   Rules: docs/server-rules.md#items-and-stamina
//
// Sets or clears the items' lock flag (sent as Item.is_lock, b: CItemInfo's fields).
//   (d) Uids that aren't owned items change nothing; no refusal.
// Answers: the player state and Item.
std::vector<u8> lock_item(Ctx& ctx, const Request& req) {
    bool on = req.method.rfind("Lock", 0) == 0;
    const std::vector<ItemUid> uids = item_uid_list(req);
    for (ItemUid uid : uids) ctx.st.q("update items set locked = ? where uid = ?", {on ? 1 : 0, uid});
    LOGI("server", "%s: %zu items %s", req.method.c_str(), uids.size(), on ? "locked" : "unlocked");
    Value data = ctx.base_data();
    data["Item"] = ctx.items();
    return body(data);
}

// Adds healed stamina: (d) on top of the current stamina, overflow allowed; the regeneration
// clock restarts when it reaches the maximum.
void heal(Ctx& ctx, u32 points) {
    ctx.tick_stamina();
    ctx.st.q("update player set stamina = stamina + ?", {points});
    u32 level = (u32)ctx.st.one("select level from player", {});
    if ((u32)ctx.st.one("select stamina from player", {}) >= ctx.stamina_max(level)) ctx.st.q("update player set stamina_at = ?", {ctx.now()});
}

// UseHealItem's arguments: (u32 master item id, u32 count); 0 or missing count = 1.
struct UseHealItemArgs {
    u32 item = 0, count = 1;
    static UseHealItemArgs from(const Request& req) {
        return {req.ints.size() > 0 ? (u32)req.ints[0] : 0, req.ints.size() > 1 && req.ints[1] ? (u32)req.ints[1] : 1};
    }
};

// UseHealItem(u32 master item id, u32 count) -> UseHealItemRes             fid baeea1ba
// API: docs/api.md#usehealitem   Rules: docs/server-rules.md#items-and-stamina, docs/server-rules.md#stamina
//
// Uses stamina heal items.
//   (a) master_item type 10, heal_type / heal_point; (b) the points are
//   StaminaUtility::StaminaHealPoint (growth_rules::heal_points) x count; (d) added on top of
//   the current stamina (heal).
//   (d) Refusals: kItemUnusable (10208) for an item that isn't a heal item, kItemCountError
//   (10206) for the count.
// Answers: the player state, UseStockItem {master_item_id, use_count} and StockItem.
std::vector<u8> use_heal_item(Ctx& ctx, const Request& req) {
    const auto args = UseHealItemArgs::from(req);
    u32 item = args.item, n = args.count;
    int type = -1;
    u32 point = 0;
    ctx.m.q("select heal_type, heal_point from master_item where id = ? and type = ?", {item, item_type::kHealItem}, [&](const Row& item_row) {
        type = (int)item_row.i("heal_type");  // (a) master_item type 10, heal_type / heal_point
        point = (u32)item_row.i("heal_point");
    });
    if (type < 0) return refuse(ctx, "UseHealItem", "not a heal item", ErrorCode::kItemUnusable);
    if (stock_count(ctx, item) < n) return refuse(ctx, "UseHealItem", "not enough items", ErrorCode::kItemCountError);
    u32 level = (u32)ctx.st.one("select level from player", {});
    u32 points = growth_rules::heal_points(type, point, ctx.stamina_max(level)) * n;
    add_stock(ctx, item, -(int64_t)n);
    heal(ctx, points);
    Value data = ctx.base_data();
    Value use = Value::object();
    use["master_item_id"] = item;
    use["use_count"] = n;
    data["UseStockItem"] = use;
    data["StockItem"] = ctx.stock();
    LOGI("server", "UseHealItem %u x%u: +%u stamina", item, n, points);
    return body(data);
}

// StaminaHeal() -> StaminaHealRes                                          fid 737fac92
// API: docs/api.md#staminaheal   Rules: docs/server-rules.md#items-and-stamina, docs/server-rules.md#stamina
//
// Refills the stamina for coins.
//   (a)+(b) master_global stamina_use_coin (StaminaUtility::StaminaUseCoin); heals the maximum
//   (StaminaUtility::StaminaHealPoint(type, nullptr)); (a) free coins first (wallet::spend_coins; core/wallet.h);
//   (d) added on top of the current stamina (heal).
//   (d) Refusal: kCoinsShort (20000) when the coins don't cover it.
// Answers: the player state.
std::vector<u8> stamina_heal(Ctx& ctx, const Request&) {
    // (a)+(b) master_global stamina_use_coin (StaminaUtility::StaminaUseCoin); heals the maximum
    // (StaminaUtility::StaminaHealPoint(type, nullptr))
    u32 price = ctx.global_u32("stamina_use_coin", 100);
    // (a) free coins first (core/wallet.h: master_text uimsg_buy_history_explan)
    if (!wallet::spend_coins(ctx.st.h, price)) return refuse(ctx, "StaminaHeal", "not enough coins", ErrorCode::kCoinsShort);
    u32 level = (u32)ctx.st.one("select level from player", {});
    u32 points = std::max(1u, ctx.stamina_max(level));
    heal(ctx, points);
    Value data = ctx.base_data();
    LOGI("server", "StaminaHeal: %u coins, +%u stamina", price, points);
    return body(data);
}

// InheritAccessory's arguments: (u64 base accessory uid, u64 lost accessory uid) (b:
// CItemStrengtheningPotal::SetStrengtheningExec's request lambda @01b8dc5c sends the base +0x210
// and the first material +0x218).
struct InheritAccessoryArgs {
    ItemUid base_uid, lost_uid;
    static InheritAccessoryArgs from(const Request& req) {
        return {ItemUid(req.ints.size() > 0 ? req.ints[0] : 0), ItemUid(req.ints.size() > 1 ? req.ints[1] : 0)};
    }
};

// InheritAccessory(u64 base uid, u64 lost uid) -> InheritAccessoryRes               fid d9feb3e8
// API: docs/api.md#inheritaccessory   Rules: docs/server-rules.md#accessory-inheritance
//
// ファクター継承: a strengthening (強化合成) of an inheritance accessory (＜INHERIT＞), which also
// takes in its material's factor, once.
//   (b) the strengthening screen sends it instead of ItemCompose when the base can inherit
//       (CItemStrengtheningPotal::SetStrengtheningExec @01b89d08: CUIUtility::CheckInheriteType
//       @01ed0bec is 1 when the base's master_item.max_inheritance_num isn't 0 and it has no
//       inherited item yet, 2 once it has one); the base and the first material;
//   (a) max_inheritance_num (21 accessories, all 2; b: the client tests it for non-zero only, and
//       its dialog says 一度合成するとファクターを変更できません: one inheritance per accessory);
//   (b) the material list greys out the other inheritance accessories (seen on screen), so the lost
//       one is another, ordinary accessory;
//   (b) the screen previews it as a compose (強化ポイント, 必要FOL) and its dialog says the factor is
//       inherited 強化合成時に: the compose's rules apply (compose above: points, FOL, big success,
//       limit break, `accessory_boost`);
//   (b) the answer's InheritResultInfo {base_player_item_id, lost_master_item_id,
//       lost_player_item_id, lost_item_limit_break_count} is applied by
//       CApiNotify::OnInheritAccessoryRes (@014cb410): the base's InheritItemInfo
//       {inherited_master_item_id, inherited_master_item_limit_break_count} (CItemInfo+0x248) takes
//       the lost item's master id and limit break, the lost item leaves the list; ComposeResult's
//       after_level / after_boosted_point / after_limit_break_count are copied to the base;
//   counted as `accessory_inherit` (achievement type 58, アクセサリーにファクターを N回継承させる);
//   (d) Refusals: kItemUnusable (10208) for a base that can't inherit or a lost item that isn't
//       another owned ordinary accessory; the compose's for the rest (10204 locked or equipped,
//       11001 FOL).
// Answers: the player state, InheritResultInfo, ComposeResult and Item (the base's InheritItemInfo).
std::vector<u8> inherit_accessory(Ctx& ctx, const Request& req) {
    const auto args = InheritAccessoryArgs::from(req);
    Item base = find_item(ctx, args.base_uid), lost = find_item(ctx, args.lost_uid);
    if (!base.ok || base.type != item_type::kAccessory) return refuse(ctx, "InheritAccessory", "no base accessory", ErrorCode::kItemUnusable);
    auto can_inherit = [&](const Item& item) {
        return ctx.m.one("select ifnull(max_inheritance_num, 0) from master_item where id = ?", {item.id}) != 0;
    };
    // (a)+(b) the base can inherit: max_inheritance_num, and nothing inherited yet
    if (!can_inherit(base) || ctx.st.one("select inherited_master_item_id is not null from items where uid = ?", {args.base_uid}) != 0)
        return refuse(ctx, "InheritAccessory", "the base can't inherit (max_inheritance_num 0, or inherited already)", ErrorCode::kItemUnusable);
    // (b) another accessory, not an inheritance one (greyed out in the material list)
    if (!lost.ok || lost.type != item_type::kAccessory || args.lost_uid == args.base_uid || can_inherit(lost))
        return refuse(ctx, "InheritAccessory", "the lost item isn't another ordinary owned accessory", ErrorCode::kItemUnusable);
    Composed composed;
    if (std::vector<u8> refused = compose(ctx, "InheritAccessory", args.base_uid, {args.lost_uid}, composed); !refused.empty()) return refused;
    ctx.st.q("update items set inherited_master_item_id = ?, inherited_limit_break = ? where uid = ?", {lost.id, lost.lb, args.base_uid});
    count(ctx, "accessory_inherit");
    Value inherited = Value::object();
    inherited["base_player_item_id"] = args.base_uid.v;
    inherited["lost_master_item_id"] = lost.id.v;
    inherited["lost_player_item_id"] = args.lost_uid.v;
    inherited["lost_item_limit_break_count"] = lost.lb;
    std::vector<u8> answer = compose_response(ctx, composed, &inherited);
    // read by port/scripts/equipment_session.sh
    LOGI("server", "InheritAccessory %llx: inherited item %u (limit break %u) from %llx", (unsigned long long)args.base_uid.v, lost.id.v, lost.lb,
         (unsigned long long)args.lost_uid.v);
    return answer;
}

// UpdateItemStock() -> UpdateItemStockRes                                  fid cf39cc5c
// API: docs/api.md#updateitemstock   Rules: docs/server-rules.md#stocks-and-wallet
//
// Buys more weapon / accessory slots; always refused, as UpdateGearStock.
//   (a) item_stock_up_num 5 more slots for item_stock_use_coin 100 coins; (b) the maximum is
//   master_global item_stock_max (CParameterUtility::ItemStockMax @0181b990, 300 without the row),
//   and CItemFrame::Progress (@01b2d454) hides the expansion button once
//   CParameterUtility::NowItemStockMax reaches it. The server sends Player.item_stock =
//   item_stock_max (d: the starting capacity isn't in the master), so there is nothing to buy.
// Answers: the refusal kLimitReached (11006, (d) the code) with the player state.
std::vector<u8> update_item_stock(Ctx& ctx, const Request&) {
    return refuse(ctx, "UpdateItemStock", "item stock already at item_stock_max", ErrorCode::kLimitReached);
}

}  // namespace

u32 stored_item_sale_fol(ext::Ctx& ctx, ItemUid item_uid) { return sale_fol(ctx, find_item(ctx, item_uid, true)); }

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_items() {
    using namespace ext;
    add_api({"ItemCompose", "ItemComposeArray"}, item_compose);
    add_api({"ItemGradeUp", "ItemGradeUpArray"}, item_grade_up);
    add_api({"MaterialCompose"}, material_compose);
    add_api({"SellItem", "SellItemArray", "SellStackItem"}, sell_item);  // SellGear: api/items/gear.cpp
    add_api({"LockItem", "LockItemArray", "UnlockItem", "UnlockItemArray"}, lock_item);
    add_api({"UseHealItem"}, use_heal_item);
    add_api({"StaminaHeal"}, stamina_heal);
    add_api({"InheritAccessory"}, inherit_accessory);
    add_api({"UpdateItemStock"}, update_item_stock);
}

}  // namespace soa::server
