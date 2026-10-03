// Local server: gear (ギア) and weapon customisation (武器カスタム). GetGearInfo,
// ClearNewGear, AttachGear, RemoveGear, GenerateGear (ギア精製), SellGear, UpdateGearStock, the
// gear content grants (content type 15 gear item, 98 gear lottery) and the `GearInfoList` /
// per-weapon `AttachedGearInfoList` state. Rules in docs/server-rules.md "Gear";
// labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// Client structures (b, decompiled Initialize bodies and handlers; work/decomp/server-rules-gear*):
//  - GearInfoList (CParameterManager+0x8c98) = map<u64 gear uid, CGearInfo {type (u8), param1,
//    param2, player_item_id (u64), slot_index, is_new}>. Every owned gear, attached or not; the
//    gear lists (tItemData::CreateGearList) show those with player_item_id 0. type 0 = a gear item
//    (param1 = its master_item id, type 15); type != 0 = a gear made from a weapon's factor
//    (param1 = the weapon's master_item id, param2 = the factor slot; tItemData::SetGearItem(u32,
//    u32) takes slots 1..3 and shows master_global weapon_gear_item).
//  - AddGearInfoList (+0x8ce8, same map type) is merged into it; UpdateGearList (+0x8d38, u64 ids)
//    lists gear removed from it (DeleteGear / SellGear / ClearNewGear's "new" flag / RemoveGear's
//    detach), UpdateAttachedGearInfoList (+0x8d88) = map<u64 weapon uid, [CAttachedGearInfo]>.
//  - CItemInfo's child AttachedGearInfoList (+0x2e0, vector at +0x318) = the weapon's gears:
//    CAttachedGearInfo {type, param1, param2, gear_id, add_param_type1..3, value1..3}; the item's
//    stats add value_k to stat add_param_type_k (1 attack, 2 intelligence, 3 defence, 4 hit,
//    5 guard; 6 = a factor, taking two slots: tItemData::SetGearList / SetGearItem).
//
// The pure formulas of the purification are rules/gear_rules.{h,cpp}; tests: gear_tests.cpp
// (items/gear-apis, items/gear-barney-chance) and rules/gear_rules_tests.cpp.
#include <algorithm>
#include <cmath>

#include "api/items/items.h"
#include "core/log.h"
#include "soaserver/ext.h"
#include "core/errors.h"
#include "core/modules.h"
#include "master/master.h"
#include "rules/gear_rules.h"

namespace soa::server {
namespace {
using namespace ext;

// (d) gear uids: their own range, like the core's item uids (0x7d000000..)
constexpr u64 kGearUid0 = 0x7c000000;

// CGearInfo.type (b: the client structures above): 0 a gear item, != 0 a gear made from a
// weapon's factor; the server makes type 1 (d).
constexpr u32 kGearItem = 0;
constexpr u32 kFactorGear = 1;
// The content types this module grants (a: docs/api.md "Content types"; 98 is master_gear_lottery's
// category_id as a content).
constexpr u32 kContentGearItem = 15;
constexpr u32 kContentGearLottery = 98;
// CAttachedGearInfo.add_param_type of a weapon factor (b: tItemData::SetGearList / SetGearItem).
constexpr u32 kBonusFactor = 6;
// A weapon's factor slots, master_item factor1..3 (a), and the gear bonuses add_param1..3 (a).
constexpr int kFactorSlots = 3;
constexpr u32 kMaxGearBonuses = 3;
// GenerateGear (b: CCustomGear): up to five materials (item_image1..5); gear rarities 1..5
// (a: master_gear_probability rank1..5_rate).
constexpr size_t kMaxGenerateMaterials = 5;
constexpr int kMaxGearRarity = 5;

// One owned gear (a gear_items row).
struct Gear {
    bool ok = false;
    u64 uid = 0, item_uid = 0;  // item_uid: the weapon it is attached to, 0 when free
    u32 type = 0, id = 0, param2 = 0, slot = 0;  // id: param1 (the gear item, or the factor's weapon)
    bool is_new = false;
};
Gear find_gear(Sql& state, u64 uid) {
    Gear gear;
    state.q("select * from gear_items where uid = ?", {uid}, [&](const Row& gear_row) {
        gear.ok = true;
        gear.uid = uid;
        gear.type = (u32)gear_row.i("type");
        gear.id = (u32)gear_row.i("master_item_id");
        gear.param2 = (u32)gear_row.i("param2");
        gear.item_uid = (u64)gear_row.i("item_uid");
        gear.slot = (u32)gear_row.i("slot");
        gear.is_new = gear_row.i("is_new") != 0;
    });
    return gear;
}

// CGearInfo, one entry of GearInfoList / AddGearInfoList.
Value gear_info(const Gear& gear) {  // (b) CGearInfo's fields
    Value info = Value::object();
    info["type"] = gear.type;
    info["param1"] = gear.id;
    info["param2"] = gear.param2;
    info["player_item_id"] = gear.item_uid;
    info["slot_index"] = gear.slot;
    info["is_new"] = gear.is_new;
    return info;
}
// GearInfoList: every owned gear by uid.
Value gear_info_list(Sql& state) {
    // (d) gear attached to a weapon that is gone (sold, used as material) goes with it
    state.exec("delete from gear_items where item_uid != 0 and item_uid not in (select uid from items)");
    Value list = Value::object();
    state.q("select uid from gear_items order by uid", {}, [&](const Row& gear_row) {
        u64 uid = (u64)gear_row.i("uid");
        list[std::to_string(uid)] = gear_info(find_gear(state, uid));
    });
    return list;
}

// (b) CAttachedGearInfo of one attached gear. A gear item's bonuses are its master_gear row's
// add_param_type1..3 / add_param1..3 (a: master_item.master_gear_id). A weapon-factor gear carries
// the weapon's factor of its slot as bonus type 6 (d: type 6 is the client's two-slot factor kind).
Value attached_gear_info(Sql& master, const Gear& gear) {
    Value info = Value::object();
    info["type"] = gear.type;
    info["param1"] = gear.id;
    info["param2"] = gear.param2;
    info["gear_id"] = gear.uid;
    for (u32 k = 1; k <= kMaxGearBonuses; k++) {
        info["add_param_type" + std::to_string(k)] = 0u;
        info["value" + std::to_string(k)] = 0u;
    }
    if (gear.type == kGearItem) {
        master.q("select g.* from master_gear g join master_item i on i.master_gear_id = g.id where i.id = ?", {gear.id}, [&](const Row& gear_row) {
            for (u32 k = 1; k <= kMaxGearBonuses; k++) {
                std::string type_col = "add_param_type" + std::to_string(k), value_col = "add_param" + std::to_string(k);
                info[type_col] = (u32)gear_row.i(type_col.c_str());
                info["value" + std::to_string(k)] = (u32)gear_row.i(value_col.c_str());
            }
        });
    } else if (gear.param2 >= 1 && gear.param2 <= (u32)kFactorSlots) {
        std::string factor_col = "factor" + std::to_string(gear.param2) + "_id";
        u32 factor = (u32)master.one("select " + factor_col + " from master_item where id = ?", {gear.id});
        if (factor) {
            info["add_param_type1"] = kBonusFactor;
            info["value1"] = factor;
        }
    }
    return info;
}
// A weapon's AttachedGearInfoList, by slot.
Value attached_gear_info_list(Sql& state, Sql& master, u64 item_uid) {
    Value list = Value::array();
    state.q("select uid from gear_items where item_uid = ? order by slot", {item_uid},
            [&](const Row& gear_row) { list.push(attached_gear_info(master, find_gear(state, (u64)gear_row.i("uid")))); });
    return list;
}

// Hook (ext::add_item_extra): every owned weapon with gear lists it in its CItemInfo.
//   (b) CItemInfo's child AttachedGearInfoList (+0x2e0); sent only when the weapon has gear.
void attached_gear_extra(Sql& state, Sql& master, u64 uid, Value& item) {
    if (state.one("select count(*) from gear_items where item_uid = ?", {uid}) == 0) return;
    item["AttachedGearInfoList"] = attached_gear_info_list(state, master, uid);
}

u64 new_gear(Ctx& ctx, u32 type, u32 master_item, u32 param2) {
    u64 uid = (u64)ctx.st.one("select ifnull(max(uid), ?) + 1 from gear_items", {kGearUid0});
    ctx.st.q("insert into gear_items (uid, type, master_item_id, param2, created_at) values (?,?,?,?,?)",
             {uid, type, master_item, param2, ctx.now()});
    return uid;
}

// A gear lottery (a: master_gear_lottery rows of a category, open at the clock, by rate_weigh;
// `kind` != 0 keeps the rows of that weapon kind). 0 when nothing matches.
u32 lottery(Ctx& ctx, const std::string& category, u32 kind) {
    std::vector<std::pair<u32, u32>> rows;  // (item, weight)
    // dated content: the event calendar (server.h event_now)
    std::string now = ctx.fmt_time(ctx.event_now());
    ctx.m.q(
        "select master_item_id, rate_weigh, master_weapon_kind_id from master_gear_lottery where category_id_label = ? "
        "and (opened_at is null or opened_at = '' or opened_at <= ?) and (closed_at is null or closed_at = '' or closed_at > ?)",
        {category, now, now}, [&](const Row& lottery_row) {
            if (kind && (u32)lottery_row.i("master_weapon_kind_id") != kind) return;
            if (lottery_row.i("rate_weigh") > 0) rows.push_back({(u32)lottery_row.i("master_item_id"), (u32)lottery_row.i("rate_weigh")});
        });
    if (rows.empty()) return 0;
    u64 sum = 0;
    for (auto& row : rows) sum += row.second;
    u64 x = (*ctx.rng)() % sum;
    for (auto& row : rows) {
        if (x < row.second) return row.first;
        x -= row.second;
    }
    return rows.back().first;
}

void add_to(Value& list, u64 uid, const Gear& gear) { list[std::to_string(uid)] = gear_info(gear); }

// ---- content grants: 15 gear item, 98 gear lottery ----------------------------------------
// (a) content type 15 = a master_item of type 15 with its master_gear row; 98 = a lottery of
// master_gear_lottery by category_id (gear_drop_1..5), docs/api.md "Content types". (d) the gear
// stock cap isn't checked for grants.
void grant_gear(Ctx& ctx, u32 item, u32 num, Value& added) {
    for (u32 k = 0; k < std::max(1u, num); k++) {
        u64 uid = new_gear(ctx, kGearItem, item, 0);
        add_to(added, uid, find_gear(ctx.st, uid));
    }
}
// Hook (ext::add_grant 15): grants `num` gears of the gear item `id` (at least one).
//   The client refetches the gear (GetGearInfo) when it opens the gear screens (b: CCustomGear::
//   Setup, CItemPossessionList::Setup), so a grant only changes the state.
void grant_gear_content(Ctx& ctx, u32 id, u32 num, Value&, Value&, Value&) {
    Value unused = Value::object();
    grant_gear(ctx, id, num, unused);
}
// Hook (ext::add_grant 98): `num` draws (at least one) of the gear lottery category `id`
//   (a: master_gear_lottery.category_id); a category with nothing open logs and grants nothing.
void grant_gear_lottery(Ctx& ctx, u32 id, u32 num, Value&, Value&, Value&) {
    std::string category;
    ctx.m.q("select category_id_label from master_gear_lottery where category_id = ? limit 1", {id},
            [&](const Row& lottery_row) { category = lottery_row.s("category_id_label"); });
    Value unused = Value::object();
    for (u32 k = 0; k < std::max(1u, num); k++)
        if (u32 item = lottery(ctx, category, 0)) grant_gear(ctx, item, 1, unused);
        else LOGW("server", "gear lottery %u (%s): nothing open", id, category.c_str());
}

// ---- barney chance (バーニィチャンス) --------------------------------------------------------
// master_gear_barney_chance (a): groups of three rows, one per barney_chance_type 1..3, each with
// a mood_rate and a mutation_rate. In every group the three mood_rates sum to 100 (default
// 70/25/5; event groups e.g. 0/0/100) and the mutation_rates rise with the type (10/30/60).
// The client (b):
//  - shows the current chance as the purification menu's icon: CCustomGear::
//    UpdatePurificationMenu sets Image_chance1 to icon_chance1..3.png by CParameterManager+0x91c0
//    (= GearBarneyChanceInfo.barney_chance_type: the info's type value at +0x90, the info at
//    +0x9130), plus one step when a selected material has the flag at tItemData+0x22d;
//  - after GenerateGear, when GearGenerationInfoResult.is_barney_chance (CParameterManager+0x8ef0:
//    the result at +0x8da0, whose AddGearInfoList map is the +0x8e10 the same code walks) is set
//    and the first new gear has a rarity, starts the CCustomGearCutIn with that rarity - 1: the
//    cut-in shows one star less and plays its rank-up (the `stars < rarity` branch of
//    CCustomGearCutIn::Progress). So is_barney_chance means "this gear was raised a rarity".
// Rules (d, the readings of the columns): the open group is the dated group whose
// opened_at..closed_at holds the event clock, else the undated `default` group. The chance type
// ("Barney's mood") is drawn from the open group by mood_rate, kept until the next GenerateGear
// (or until another group opens), and sent as GearBarneyChanceInfo {barney_chance_group_id,
// barney_chance_type} with the gear state. A generation raises the drawn gear's rarity by one
// (a new draw from gear_purification_<rarity + 1>, when there is one) with mutation_rate percent
// of the current type, reports it as is_barney_chance, and draws the next mood.
struct Barney {
    u32 group = 0, type = 0, mood = 0, mutation = 0;
};
std::vector<Barney> barney_group(Ctx& ctx) {
    std::string now = ctx.fmt_time(ctx.event_now());  // dated content: the event calendar
    std::vector<Barney> rows;
    auto add = [&](const Row& chance_row) {
        rows.push_back({(u32)chance_row.i("barney_chance_group_id"), (u32)chance_row.i("barney_chance_type"), (u32)chance_row.i("mood_rate"),
                        (u32)chance_row.i("mutation_rate")});
    };
    u32 group = (u32)ctx.m.one(
        "select barney_chance_group_id from master_gear_barney_chance where opened_at is not null and opened_at != '' "
        "and opened_at <= ? and closed_at > ? order by opened_at desc limit 1",
        {now, now}, 0);
    if (group) ctx.m.q("select * from master_gear_barney_chance where barney_chance_group_id = ? order by barney_chance_type", {group}, add);
    else
        ctx.m.q(
            "select * from master_gear_barney_chance where opened_at is null or opened_at = '' order by barney_chance_group_id, "
            "barney_chance_type",
            {}, add);
    if (!rows.empty()) {
        u32 first = rows.front().group;  // (d) one undated group: the first
        rows.erase(std::remove_if(rows.begin(), rows.end(), [first](const Barney& b) { return b.group != first; }), rows.end());
    }
    return rows;
}
Barney barney_draw(Ctx& ctx, const std::vector<Barney>& group) {
    u32 sum = 0;
    for (auto& b : group) sum += b.mood;
    if (!sum) return group.empty() ? Barney{} : group.front();
    u32 x = (u32)((*ctx.rng)() % sum);
    for (auto& b : group) {
        if (x < b.mood) return b;
        x -= b.mood;
    }
    return group.back();
}
// The current chance: the stored draw while its group is open, else a new draw (stored).
Barney barney_current(Ctx& ctx, bool redraw = false) {
    std::vector<Barney> open_group = barney_group(ctx);
    if (open_group.empty()) return {};
    u32 group = 0, type = 0;
    ctx.st.q("select group_id, type from gear_barney where id = 1", {},
             [&](const Row& barney_row) { group = (u32)barney_row.i("group_id"), type = (u32)barney_row.i("type"); });
    if (!redraw && group == open_group.front().group)
        for (auto& b : open_group)
            if (b.type == type) return b;
    Barney b = barney_draw(ctx, open_group);
    ctx.st.q("insert or replace into gear_barney (id, group_id, type) values (1, ?, ?)", {b.group, b.type});
    return b;
}
Value barney_chance_info(const Barney& b) {  // (b) CGearBarneyChanceInfo's fields
    Value info = Value::object();
    info["barney_chance_group_id"] = b.group;
    info["barney_chance_type"] = b.type;
    return info;
}

// Hook (ext::add_player_load): full-state responses carry the gear and the barney chance.
//   (b) GearInfoList is state (docs/api.md "Player state"); (d) the current barney chance is
//   sent with the gear state.
void load_gear_state(Ctx& ctx, const Request&, Value& data) {
    data["GearInfoList"] = gear_info_list(ctx.st);
    data["GearBarneyChanceInfo"] = barney_chance_info(barney_current(ctx));
}

// GetGearInfo() -> GetGearInfoRes                                         fid 388092cc
// API: docs/api.md#getgearinfo   Rules: docs/server-rules.md "Gear"
//
// The gear screens' refetch of the whole gear state.
//   (b) CCustomGear::Setup and CItemPossessionList::Setup send it when they open.
// Answers: the player state, GearInfoList (every owned gear) and GearBarneyChanceInfo.
std::vector<u8> get_gear_info(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["GearInfoList"] = gear_info_list(ctx.st);
    data["GearBarneyChanceInfo"] = barney_chance_info(barney_current(ctx));
    return body(data);
}

// ClearNewGear(vector<u64> gear uids) -> ClearNewGearRes                  fid b0092669
// API: docs/api.md#clearnewgear   Rules: docs/server-rules.md "Gear"
//
// Clears the "new" mark of the gears.
//   (b) OnClearNewGearRes clears is_new of the gears UpdateGearList names.
//   (d) Uids that aren't owned gears are named back anyway (nothing changes for them).
// Answers: the player state and UpdateGearList (the uids sent).
std::vector<u8> clear_new_gear(Ctx& ctx, const Request& req) {
    Value data = ctx.base_data(), ids = Value::array();
    for (u64 uid : uid_list(req)) {
        ctx.st.q("update gear_items set is_new = 0 where uid = ?", {uid});
        ids.push(uid);
    }
    data["UpdateGearList"] = ids;
    return body(data);
}

// An owned weapon (an `items` row) and its master_item / master_weapon fields.
struct Weapon {
    bool ok = false;
    u32 id = 0, level = 1, lb = 0, rarity = 0, slots = 0, kind = 0, type = 0;  // lb: limit break; slots: max_gear_slot_num
    bool locked = false, equipped = false;
};
Weapon find_weapon(Ctx& ctx, u64 uid) {
    Weapon weapon;
    ctx.st.q("select * from items where uid = ?", {uid}, [&](const Row& item_row) {
        weapon.ok = true;
        weapon.id = (u32)item_row.i("master_item_id");
        weapon.level = (u32)std::max<int64_t>(1, item_row.i("level"));
        weapon.lb = (u32)item_row.i("limit_break");
        weapon.locked = item_row.i("locked") != 0;
    });
    if (!weapon.ok) return weapon;
    ctx.m.q(
        "select i.type, i.rarity, i.max_gear_slot_num, w.master_weapon_kind_id from master_item i left join master_weapon w on "
        "w.id = i.master_weapon_id where i.id = ?",
        {weapon.id}, [&](const Row& item_row) {
            weapon.type = (u32)item_row.i("type");
            weapon.rarity = (u32)item_row.i("rarity");
            weapon.slots = (u32)item_row.i("max_gear_slot_num");
            weapon.kind = (u32)item_row.i("master_weapon_kind_id");
        });
    weapon.equipped = item_equipped(ctx, uid);
    return weapon;
}
// The weapon kind a gear fits: a gear item's master_gear kind (a), a factor gear's weapon's (d).
u32 gear_kind(Ctx& ctx, const Gear& gear) {
    if (gear.type != kGearItem)  // a weapon-factor gear: the weapon's kind (d)
        return (u32)ctx.m.one("select w.master_weapon_kind_id from master_item i join master_weapon w on w.id = i.master_weapon_id where i.id = ?",
                              {gear.id});
    return (u32)ctx.m.one("select g.master_weapon_kind_id from master_item i join master_gear g on g.id = i.master_gear_id where i.id = ?",
                          {gear.id});
}

// AttachGear's arguments: (u64 weapon uid, u64 gear uid, u32 slot); all three or none.
struct AttachGearArgs {
    bool complete = false;
    u64 weapon_uid = 0, gear_uid = 0;
    u32 slot = 0;
    static AttachGearArgs from(const Request& req) {
        AttachGearArgs args;
        args.complete = req.ints.size() >= 3;
        if (!args.complete) return args;
        args.weapon_uid = req.ints[0];
        args.gear_uid = req.ints[1];
        args.slot = (u32)req.ints[2];
        return args;
    }
};

// AttachGear(u64 weapon uid, u64 gear uid, u32 slot) -> AttachGearRes      fid bce2e7f2
// API: docs/api.md#attachgear   Rules: docs/server-rules.md "Gear", "Fixes found on the growth screens"
//
// Sets a free gear into a weapon's slot (the weapon custom screen, CCustomGear).
//   (b) uimsg_gear_set_*: only a weapon with slots (master_item.max_gear_slot_num, a) and a gear
//   of the same weapon kind (tutorial cp0003_tutorial_180); a gear already in the slot is destroyed
//   (uimsg_gear_set_dialog2 / cp0003_tutorial_181). Cost: master_global attach_gear_coin (a) in FOL
//   (d: the key says "coin", but the gear screens' only currency shortage text is
//   uimsg_gear_fol_shortage). Slot: 0-based below max_gear_slot_num (d).
//   (a)+(b) the gear's master_gear.limit_break_conditions is the weapon limit break it needs, and
//   the gear needs as many slots as it has bonuses (below).
//   (d) Refusals: kItemUnusable (10208) for the arguments, weapon, slot, kind and conditions;
//   kFolShort (10710) for the FOL.
// Answers: the player state, AddGearInfoList (the gear, now attached), UpdateGearList (the
// destroyed gear), UpdateAttachedGearInfoList (the weapon's gears) and Item.
std::vector<u8> attach_gear(Ctx& ctx, const Request& req) {
    const auto args = AttachGearArgs::from(req);
    if (!args.complete) return refuse(ctx, "AttachGear", "arguments", ErrorCode::kItemUnusable);
    u64 weapon_uid = args.weapon_uid, gear_uid = args.gear_uid;
    u32 slot = args.slot;
    Weapon weapon = find_weapon(ctx, weapon_uid);
    Gear gear = find_gear(ctx.st, gear_uid);
    if (!weapon.ok || !gear.ok || gear.item_uid) return refuse(ctx, "AttachGear", "weapon or free gear not owned", ErrorCode::kItemUnusable);
    if (slot >= weapon.slots) return refuse(ctx, "AttachGear", "no such slot", ErrorCode::kItemUnusable);
    if (gear_kind(ctx, gear) != weapon.kind) return refuse(ctx, "AttachGear", "weapon kind mismatch", ErrorCode::kItemUnusable);
    // (a)+(b) the gear's master_gear.limit_break_conditions is the weapon limit break it needs
    // (the gear list shows it as セット条件; CCustomGear refuses with 武器の上限解放が必要です, seen in
    // game) and the gear needs as many slots as it has bonuses (tItemData::GearSlotCount: a gear's
    // non-zero add_param_type count, a weapon's max_gear_slot_num capped at 3)
    if (gear.type == kGearItem) {
        int64_t limit_break_needed = ctx.m.one(
            "select ifnull(g.limit_break_conditions, 0) from master_item i join master_gear g on g.id = i.master_gear_id "
            "where i.id = ?",
            {gear.id});
        if ((int64_t)weapon.lb < limit_break_needed)
            return refuse(ctx, "AttachGear", "weapon limit break below the gear's condition", ErrorCode::kItemUnusable);
        u32 slots_needed = (u32)ctx.m.one(
            "select (ifnull(g.add_param_type1, 0) != 0) + (ifnull(g.add_param_type2, 0) != 0) + (ifnull(g.add_param_type3, 0) != 0) "
            "from master_item i join master_gear g on g.id = i.master_gear_id where i.id = ?",
            {gear.id});
        if (slots_needed > std::min(weapon.slots, kMaxGearBonuses)) return refuse(ctx, "AttachGear", "not enough slots", ErrorCode::kItemUnusable);
    }
    u32 cost = ctx.global_u32("attach_gear_coin", 10000);
    if (fol(ctx) < cost) return refuse(ctx, "AttachGear", "FOL", ErrorCode::kFolShort);
    add_fol(ctx, -(int64_t)cost);
    Value destroyed = Value::array(), added = Value::object(), attached = Value::object();
    ctx.st.q("select uid from gear_items where item_uid = ? and slot = ?", {weapon_uid, slot},
             [&](const Row& gear_row) { destroyed.push((u64)gear_row.i("uid")); });
    for (auto& old : destroyed.arr) ctx.st.q("delete from gear_items where uid = ?", {old.u});
    ctx.st.q("update gear_items set item_uid = ?, slot = ?, is_new = 0 where uid = ?", {weapon_uid, slot, gear_uid});
    add_to(added, gear_uid, find_gear(ctx.st, gear_uid));
    attached[std::to_string(weapon_uid)] = attached_gear_info_list(ctx.st, ctx.m, weapon_uid);
    count(ctx, "gear_attach");
    Value data = ctx.base_data();
    data["AddGearInfoList"] = added;
    data["UpdateGearList"] = destroyed;  // (b) erased from GearInfoList: the destroyed gear
    data["UpdateAttachedGearInfoList"] = attached;
    data["Item"] = ctx.items();
    LOGI("server", "AttachGear: gear %llu -> weapon %llu slot %u (%zu replaced)", (unsigned long long)gear_uid, (unsigned long long)weapon_uid, slot,
         destroyed.arr.size());  // read by growth_session.sh
    return body(data);
}

// RemoveGear's argument: (u64 weapon uid), or a gear uid (d).
struct RemoveGearArgs {
    bool sent = false;
    u64 uid = 0;
    static RemoveGearArgs from(const Request& req) {
        RemoveGearArgs args;
        args.sent = !req.ints.empty();
        if (args.sent) args.uid = req.ints[0];
        return args;
    }
};

// RemoveGear(u64 weapon uid) -> RemoveGearRes                              fid 33da88ce
// API: docs/api.md#removegear   Rules: docs/server-rules.md "Gear"
//
// Takes the gear off a weapon (CCustomGear's ギア解除).
//   (b) the argument is the weapon's uid (the request seen in game from CCustomGear's ギア解除, which
//   takes every gear off: OnRemoveGearRes clears the weapon's whole AttachedGearInfoList and zeroes
//   player_item_id / slot_index of the gears UpdateGearList names); a gear uid is accepted too (d).
//   (a) master_global gear_remove_gear_item (item_grease) x1 per request (b: the dialog's 必要数 1);
//   the gears return to the free list (b: uimsg_gear_slot_remove_success ギアを入手しました).
//   (d) Refusals: kItemUnusable (10208) without an attached gear, kItemCountError (10206) without
//   the grease.
// Answers: the player state, UpdateGearList (the gears taken off), UpdateAttachedGearInfoList,
// UpdateStockItem (the grease left), StockItem and Item.
std::vector<u8> remove_gear(Ctx& ctx, const Request& req) {
    const auto args = RemoveGearArgs::from(req);
    if (!args.sent) return refuse(ctx, "RemoveGear", "arguments", ErrorCode::kItemUnusable);
    u64 weapon_uid = args.uid;
    Gear gear = find_gear(ctx.st, weapon_uid);
    if (gear.ok) weapon_uid = gear.item_uid;
    std::vector<u64> gears;
    ctx.st.q("select uid from gear_items where item_uid = ? and item_uid != 0 order by slot", {weapon_uid},
             [&](const Row& gear_row) { gears.push_back((u64)gear_row.i("uid")); });
    if (gear.ok) gears = {gear.uid};
    if (gears.empty() || !weapon_uid) return refuse(ctx, "RemoveGear", "no gear attached", ErrorCode::kItemUnusable);
    std::string label = master::global_str(ctx.m.h, "gear_remove_gear_item");
    u32 grease = (u32)ctx.m.one("select id from master_item where id_label = ?", {label.empty() ? std::string("item_grease") : label});
    if (stock_count(ctx, grease) < 1) return refuse(ctx, "RemoveGear", "no grease", ErrorCode::kItemCountError);
    add_stock(ctx, grease, -1);
    // (the player state is built again below, after the changes; this first build ticks the
    // stamina before them, as it always did)
    Value data = ctx.base_data(), ids = Value::array(), attached = Value::object(), stock_update = Value::array();
    for (u64 uid : gears) {
        ctx.st.q("update gear_items set item_uid = 0, slot = 0 where uid = ?", {uid});
        ids.push(uid);
    }
    attached[std::to_string(weapon_uid)] = attached_gear_info_list(ctx.st, ctx.m, weapon_uid);
    Value grease_left = Value::object();
    grease_left["id"] = grease;
    grease_left["master_item_id"] = grease;
    grease_left["num"] = stock_count(ctx, grease);
    stock_update.push(grease_left);
    data = ctx.base_data();
    data["UpdateGearList"] = ids;
    data["UpdateAttachedGearInfoList"] = attached;
    data["UpdateStockItem"] = stock_update;
    data["StockItem"] = ctx.stock();
    data["Item"] = ctx.items();
    LOGI("server", "RemoveGear: %zu gear(s) off weapon %llu", gears.size(), (unsigned long long)weapon_uid);  // read by growth_session.sh
    return body(data);
}

// SellGear(vector<u64> gear uids) -> SellGearRes                           fid 1700186d
// API: docs/api.md#sellgear   Rules: docs/server-rules.md "Gear"
//
// Sells free gears for FOL.
//   (a) master_item.sale_fol of the gear item (type 15; the weapon_gear_item's for weapon-factor
//   gears); attached gear can't be sold (d). (b) the native OnSellGearRes erases UpdateGearList.
//   (d) Refusals: kItemUnusable (10208) for an empty list, kLockedItem (10204) for a gear not
//   owned or attached.
// Answers: the player state, SellResult {total_fol, item_ids (empty), UpdateGearList} and
// UpdateGearList.
std::vector<u8> sell_gear(Ctx& ctx, const Request& req) {
    std::vector<u64> uids = uid_list(req);
    if (uids.empty()) return refuse(ctx, "SellGear", "nothing", ErrorCode::kItemUnusable);
    u32 total = 0;
    Value ids = Value::array();
    for (u64 uid : uids) {
        Gear gear = find_gear(ctx.st, uid);
        if (!gear.ok || gear.item_uid) return refuse(ctx, "SellGear", "gear not owned or attached", ErrorCode::kLockedItem);
        u32 item = gear.id;
        if (gear.type != kGearItem) {
            std::string label = master::global_str(ctx.m.h, "weapon_gear_item");
            item = (u32)ctx.m.one("select id from master_item where id_label = ?", {label});
        }
        total += (u32)ctx.m.one("select ifnull(sale_fol, 0) from master_item where id = ?", {item});
        ctx.st.q("delete from gear_items where uid = ?", {uid});
        ids.push(uid);
    }
    add_fol(ctx, total);
    Value data = ctx.base_data(), result = Value::object();
    result["total_fol"] = total;
    result["item_ids"] = Value::array();
    result["UpdateGearList"] = ids;
    data["SellResult"] = result;
    data["UpdateGearList"] = ids;
    return body(data);
}

// UpdateGearStock() -> UpdateGearStockRes                                  fid d10e6806
// API: docs/api.md#updategearstock   Rules: docs/server-rules.md "Gear"
//
// Buys more gear slots; always refused.
//   (a) gear_stock_up_num 5 more slots for gear_stock_use_coin 100 coins (b: uimsg_gear_extension_
//   confimation 紋章石１００個); (b) the maximum is master_global gear_stock_max
//   (CParameterUtility::MaxGearFrame, default 300). The core sends Player.gear_stock = gear_stock_max
//   (d: the starting capacity is unknown), so this refuses (the client's own IsMaxGearFrame check
//   normally stops it first).
// Answers: the refusal kLimitReached (11006, (d) the code) with the player state.
std::vector<u8> update_gear_stock(Ctx& ctx, const Request&) {
    return refuse(ctx, "UpdateGearStock", "gear stock already at gear_stock_max", ErrorCode::kLimitReached);
}

// ---- GenerateGear (ギア精製) ------------------------------------------------------------------

// A weapon's attack + intelligence at its level (d: master_item attack..attack_max linear over
// levels 1..the rarity's level_max; the client's ItemModel::GetDetail wasn't read).
u32 weapon_attack_int(Ctx& ctx, const Weapon& weapon) {
    u32 cap = (u32)ctx.m.one("select level_max from master_item_compose where rarity = ?", {weapon.rarity}, 10);
    double t = cap > 1 ? std::min(1.0, (double)(weapon.level - 1) / (double)(cap - 1)) : 0.0;
    double v = 0;
    ctx.m.q("select * from master_item where id = ?", {weapon.id}, [&](const Row& item_row) {
        for (const char* k : {"attack", "intelligence"}) {
            double lo = item_row.f(k), hi = item_row.f((std::string(k) + "_max").c_str());
            v += lo + (std::max(hi, lo) - lo) * t;
        }
    });
    return (u32)v;
}

// GenerateGear's arguments: (u64 base weapon uid, u32 carrot master item, vector<u64> materials);
// the first two or none.
struct GenerateGearArgs {
    bool complete = false;
    u64 base_uid = 0;
    u32 carrot_item = 0;
    std::vector<u64> material_uids;
    static GenerateGearArgs from(const Request& req) {
        GenerateGearArgs args;
        args.complete = req.ints.size() >= 2;
        if (!args.complete) return args;
        args.base_uid = req.ints[0];
        args.carrot_item = (u32)req.ints[1];
        args.material_uids = uid_list(req);
        return args;
    }
};

// One GenerateGear request's working state, filled step by step.
struct Generation {
    GenerateGearArgs args;
    Weapon base;                        // the base weapon (ok = false without one)
    u32 rarity_sum = 0, first_kind = 0;  // the materials' rarities; the first material's weapon kind
    std::vector<u64> used_items, used_gears;  // the materials, by table
    u32 carrot_slot = 0;                // the factor slot the carrot picks (1..3), 0 without one
    u32 rank_value = 0, rarity = 1;     // the rank value and the drawn rarity
    u32 item = 0;                       // the purified gear's master item (0: nothing open)
    Barney chance, next;                // the mood used and the next one
    bool mutated = false;               // the barney chance raised the rarity
    Value added = Value::object(), gone = Value::array(), deleted = Value::array();
};

// 1. The base weapon and the materials (false: refused, `refusal`).
//   (b) CCustomGear: up to five materials (item_image1..5); at least one gear or weapon selected
//   (tutorial cp0003_tutorial_186); materials: free gears or unlocked, unequipped weapons
//   (b: tutorial; d: the lock / equip rule).
bool check_base_and_materials(Ctx& ctx, Generation& gen, std::vector<u8>& refusal) {
    const auto& args = gen.args;
    if (args.material_uids.size() > kMaxGenerateMaterials || (args.material_uids.empty() && !args.base_uid)) {
        refusal = refuse(ctx, "GenerateGear", "materials", ErrorCode::kItemUnusable);
        return false;
    }
    if (args.base_uid) {
        gen.base = find_weapon(ctx, args.base_uid);
        if (!gen.base.ok || gen.base.type != item_type::kWeapon) {
            refusal = refuse(ctx, "GenerateGear", "base is not an owned weapon", ErrorCode::kItemUnusable);
            return false;
        }
        if (gen.base.locked || gen.base.equipped) {
            refusal = refuse(ctx, "GenerateGear", "base locked or equipped", ErrorCode::kLockedItem);  // (b) uimsg_gear_weapon_lock
            return false;
        }
    }
    for (u64 uid : args.material_uids) {
        if (uid == args.base_uid) {
            refusal = refuse(ctx, "GenerateGear", "base used as material", ErrorCode::kItemUnusable);
            return false;
        }
        Gear gear = find_gear(ctx.st, uid);
        if (gear.ok) {
            if (gear.item_uid) {
                refusal = refuse(ctx, "GenerateGear", "attached gear", ErrorCode::kLockedItem);
                return false;
            }
            gen.rarity_sum += (u32)ctx.m.one("select rarity from master_item where id = ?", {gear.id});
            if (!gen.first_kind) gen.first_kind = gear_kind(ctx, gear);
            gen.used_gears.push_back(uid);
            continue;
        }
        Weapon weapon = find_weapon(ctx, uid);
        if (!weapon.ok || weapon.type != item_type::kWeapon) {
            refusal = refuse(ctx, "GenerateGear", "material not owned", ErrorCode::kItemUnusable);
            return false;
        }
        if (weapon.locked || weapon.equipped) {
            refusal = refuse(ctx, "GenerateGear", "material locked or equipped", ErrorCode::kLockedItem);
            return false;
        }
        gen.rarity_sum += weapon.rarity;  // (b) tItemData+0x1e8 = the master item's rarity
        if (!gen.first_kind) gen.first_kind = weapon.kind;
        gen.used_items.push_back(uid);
    }
    return true;
}

// 2. The carrot (a: master_global gear_extract_factor1..3_item = item_carrot1..3; b:
// uimsg_gear_create_item 追加アイテムを1種類選択します, optional) (false: refused, `refusal`).
bool check_carrot(Ctx& ctx, Generation& gen, std::vector<u8>& refusal) {
    u32 carrot = gen.args.carrot_item;
    if (!carrot) return true;
    for (int k = 1; k <= kFactorSlots; k++) {
        std::string key = "gear_extract_factor" + std::to_string(k) + "_item", label = master::global_str(ctx.m.h, key.c_str());
        if ((u32)ctx.m.one("select id from master_item where id_label = ?", {label}) == carrot) gen.carrot_slot = (u32)k;
    }
    if (!gen.carrot_slot) {
        refusal = refuse(ctx, "GenerateGear", "not a carrot", ErrorCode::kItemUnusable);
        return false;
    }
    if (stock_count(ctx, carrot) < 1) {
        refusal = refuse(ctx, "GenerateGear", "no carrot", ErrorCode::kItemCountError);
        return false;
    }
    return true;
}

// 3. Pays (false: refused, `refusal`).
//   (a) master_global coin_for_generate_gears, (b) compared with the FOL (CCustomGear::
//   UpdatePurificationMenu: NowFol >= the cost enables Button_start); (d) the same for every
//   generation
bool pay(Ctx& ctx, Generation& gen, std::vector<u8>& refusal) {
    u32 cost = ctx.global_u32("coin_for_generate_gears", 10000);
    if (fol(ctx) < cost) {
        refusal = refuse(ctx, "GenerateGear", "FOL", ErrorCode::kFolShort);
        return false;
    }
    add_fol(ctx, -(int64_t)cost);
    if (gen.args.carrot_item) add_stock(ctx, gen.args.carrot_item, -1);
    return true;
}

// 4. The rarity: rank -> rarity (b: the rank value; a: master_gear_probability rank1..5_rate in
// percent).
void roll_rarity(Ctx& ctx, Generation& gen) {
    u32 attack_int = gen.base.ok ? weapon_attack_int(ctx, gen.base) : 0;
    gen.rank_value = gear_rules::rank_value(gen.rarity_sum, attack_int, ctx.global_u32("rare_factor_for_normal_gear", 30));
    u32 rates[kMaxGearRarity + 1] = {0};
    bool found = false;
    auto take = [&](const Row& probability_row) {
        found = true;
        for (int k = 1; k <= kMaxGearRarity; k++) rates[k] = (u32)probability_row.i(("rank" + std::to_string(k) + "_rate").c_str());
    };
    ctx.m.q("select * from master_gear_probability where rank_threshold < ? order by rank_threshold desc limit 1", {gen.rank_value}, take);
    if (!found) ctx.m.q("select * from master_gear_probability order by rank_threshold limit 1", {}, take);  // (d) below every threshold
    u32 sum = 0;
    for (int k = 1; k <= kMaxGearRarity; k++) sum += rates[k];
    gen.rarity = 1;
    if (sum) {
        u64 x = (*ctx.rng)() % sum;
        for (int k = 1; k <= kMaxGearRarity; k++) {
            if (x < rates[k]) {
                gen.rarity = (u32)k;
                break;
            }
            x -= rates[k];
        }
    }
}

// 5. The gear (a: master_gear_lottery gear_purification_<rarity> of the weapon kind by
// rate_weigh) and the barney chance (see "barney chance" above; a: the columns, b: what the
// client shows, d: the rules): the current mood's mutation_rate percent raises the gear a
// rarity; then a new mood.
void draw_gear(Ctx& ctx, Generation& gen) {
    u32 kind = gen.base.ok ? gen.base.kind : gen.first_kind;  // (d) without a base: the first material's kind
    auto draw = [&](u32 rarity) {
        u32 item = lottery(ctx, "gear_purification_" + std::to_string(rarity), kind);
        return item ? item : lottery(ctx, "gear_purification_" + std::to_string(rarity), 0);
    };
    gen.item = draw(gen.rarity);
    gen.chance = barney_current(ctx);
    if (gen.item && gen.chance.mutation && gen.rarity < (u32)kMaxGearRarity && (u32)((*ctx.rng)() % 100) < gen.chance.mutation) {
        if (u32 raised = draw(gen.rarity + 1)) {
            gen.item = raised;
            gen.rarity++;
            gen.mutated = true;
        }
    }
    gen.next = barney_current(ctx, true);
    if (gen.item) {
        u64 uid = new_gear(ctx, kGearItem, gen.item, 0);
        add_to(gen.added, uid, find_gear(ctx.st, uid));
    }
}

// 6. The factor extraction from the base weapon, which is used up (b: the chance formula of
// gear_rules::extract_chance; a: master_item factorN_id / factorN_limit_break / factorN_lock (b:
// uimsg_gear_create_item_warning: a factor not released or locked can't be extracted); d: p =
// master_global extraction_facter_<n> for the n-th extractable factor, the carrot picks the slot,
// else a uniform one, and the factor gear comes in addition to the gear)
void extract_factor(Ctx& ctx, Generation& gen) {
    if (!gen.base.ok) return;
    const Weapon& base = gen.base;
    std::vector<u32> slots;
    ctx.m.q("select * from master_item where id = ?", {base.id}, [&](const Row& item_row) {
        for (u32 k = 1; k <= (u32)kFactorSlots; k++) {
            std::string factor = "factor" + std::to_string(k);
            if (item_row.i((factor + "_id").c_str()) && (u32)item_row.i((factor + "_limit_break").c_str()) <= base.lb &&
                !item_row.i((factor + "_lock").c_str()))
                slots.push_back(k);
        }
    });
    if (!slots.empty()) {
        u32 slot = gen.carrot_slot && std::find(slots.begin(), slots.end(), gen.carrot_slot) != slots.end() ? gen.carrot_slot
                                                                                                            : slots[(*ctx.rng)() % slots.size()];
        u32 p = ctx.global_u32(("extraction_facter_" + std::to_string(std::min<u32>(base.lb, 2) + 1)).c_str(), 0);
        float chance = gear_rules::extract_chance(p, gen.rarity_sum);
        if ((float)((*ctx.rng)() % 10000) < chance * 100.0f) {
            u64 uid = new_gear(ctx, kFactorGear, base.id, slot);
            add_to(gen.added, uid, find_gear(ctx.st, uid));
        }
    }
    ctx.st.q("delete from items where uid = ?", {gen.args.base_uid});  // (d) the base weapon is used up too
    gen.deleted.push(gen.args.base_uid);
}

// 7. The materials are used up (b: uimsg_gear_create_warning 素材にした武器やギアは失われます).
void use_materials(Ctx& ctx, Generation& gen) {
    for (u64 uid : gen.used_items) {
        ctx.st.q("delete from items where uid = ?", {uid});
        gen.deleted.push(uid);
    }
    for (u64 uid : gen.used_gears) {
        ctx.st.q("delete from gear_items where uid = ?", {uid});
        gen.gone.push(uid);
    }
}

// 8. The answer.
std::vector<u8> generate_gear_response(Ctx& ctx, Generation& gen) {
    Value data = ctx.base_data(), result = Value::object();
    result["is_barney_chance"] = gen.mutated;
    result["use_master_item_id"] = gen.args.carrot_item;
    result["barney_chance_type"] = gen.chance.type;
    result["AddGearInfoList"] = gen.added;
    result["CDeleteItemList"] = gen.deleted;
    result["UpdateGearList"] = gen.gone;
    data["GearGenerationInfoResult"] = result;
    data["AddGearInfoList"] = gen.added;
    data["UpdateGearList"] = gen.gone;
    data["Item"] = ctx.items();
    data["StockItem"] = ctx.stock();
    data["GearBarneyChanceInfo"] = barney_chance_info(gen.next);
    LOGI("server", "GenerateGear: rank value %u -> rarity %u, %zu gear(s); barney chance type %u (mutation %u%%)%s, next type %u", gen.rank_value,
         gen.rarity, gen.added.map.size(), gen.chance.type, gen.chance.mutation, gen.mutated ? ": raised a rarity" : "",
         gen.next.type);  // read by growth_session.sh
    return body(data);
}

// GenerateGear(u64 base weapon uid, u32 carrot item, vector<u64> materials) -> GenerateGearRes
//                                                                          fid af1c5d33
// API: docs/api.md#generategear   Rules: docs/server-rules.md "Gear"
//
// The gear purification (ギア精製): materials (gears or weapons) and an optional base weapon
// become a new gear of a drawn rarity, plus maybe a factor gear of the base.
//   (b) the rank value and the extraction chance are the client's own formulas
//   (rules/gear_rules.h); (a) the rates, lotteries and costs are master data; (d) the base is used
//   up too, the factor gear comes in addition, the barney chance's reading (steps 1-7).
//   (d) Refusals: kItemUnusable (10208) for the arguments, base, materials and carrot,
//   kLockedItem (10204) for a locked / equipped / attached one, kItemCountError (10206) without
//   the carrot, kFolShort (10710) for the FOL.
// Answers: the player state, GearGenerationInfoResult {is_barney_chance, use_master_item_id,
// barney_chance_type, AddGearInfoList, CDeleteItemList, UpdateGearList}, AddGearInfoList,
// UpdateGearList, Item, StockItem and the next GearBarneyChanceInfo.
std::vector<u8> generate_gear(Ctx& ctx, const Request& req) {
    Generation gen;
    gen.args = GenerateGearArgs::from(req);
    if (!gen.args.complete) return refuse(ctx, "GenerateGear", "arguments", ErrorCode::kItemUnusable);
    std::vector<u8> refusal;
    if (!check_base_and_materials(ctx, gen, refusal)) return refusal;
    if (!check_carrot(ctx, gen, refusal)) return refusal;
    if (!pay(ctx, gen, refusal)) return refusal;
    roll_rarity(ctx, gen);
    draw_gear(ctx, gen);
    extract_factor(ctx, gen);
    use_materials(ctx, gen);
    count(ctx, "gear_generate");
    return generate_gear_response(ctx, gen);
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_gear() {
    using namespace ext;
    add_item_extra(attached_gear_extra);
    add_grant(kContentGearItem, grant_gear_content);
    add_grant(kContentGearLottery, grant_gear_lottery);
    add_player_load(load_gear_state);
    add_api({"GetGearInfo"}, get_gear_info);
    add_api({"ClearNewGear"}, clear_new_gear);
    add_api({"AttachGear"}, attach_gear);
    add_api({"RemoveGear"}, remove_gear);
    add_api({"SellGear"}, sell_gear);
    add_api({"UpdateGearStock"}, update_gear_stock);
    add_api({"GenerateGear"}, generate_gear);
}

}  // namespace soa::server
