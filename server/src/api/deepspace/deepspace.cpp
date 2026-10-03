// Local server: deep space expeditions ("ディープスペース探査", CPhase_DeepSpace = phase 6;
// api/deepspace/README.md). Five APIs: DeepSpaceActiveList, DeepSpaceAutoMemberSelect,
// DeepSpaceMissionStart, DeepSpaceMissionEnd, DeepSpaceMissionEndNow. The client code is the same
// in 3.7.0 and the offline build (CDeepSpace*, the dialogs and the three guest CApiNotify
// handlers); this module gives it the server data it expects. This file holds the handlers; the
// offers, ships and answer values are in state.cpp, the party bonuses in bonuses.cpp, the drops in
// rewards.cpp (deepspace.h), the pure rules in rules/deepspace_rules. Port code, not guest
// behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption. Rules in docs/server-rules.md "Deep space".
//
// Request and response shapes (b) of the handlers' own keys:
//   AutoSelectedResult     [uid, ...] (InfoBaseValueArray<u64>)
//   CContentInfoMap        {n: CDropContentInfo} content_id, content_type, num, is_new,
//                          master_item_id, bonus_category, is_rare_bonus, is_add_bonus,
//                          is_hit_bonus, is_rare_hit_bonus
//   add_characters_exp     {uid: character_id, add_exp, before_level, before_exp, after_level,
//                          after_exp, order_id}
// (the area, ship, character and bonus maps and DeepMissionPlayer: state.cpp).
#include <algorithm>
#include <set>
#include <string>
#include <vector>

#include "api/deepspace/deepspace.h"
#include "api/deepspace/deepspace_args.h"
#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "core/time.h"
#include "core/wallet.h"
#include "master/master.h"
#include "rules/deepspace_rules.h"

namespace soa::server {

namespace deepspace {
namespace {

namespace dr = rules::deepspace;
using ext::refuse;

// (a) master_deep_space_bonus_item.type: 1 adds the bonus param1_id at the item's value, 2
// multiplies every bonus by it.
enum class BonusItemType : int { kAddBonus = 1, kMultiplyAll = 2 };

// ---- DeepSpaceActiveList ---------------------------------------------------------------------

// DeepSpaceActiveList() -> DeepSpaceActiveListRes                              fid a7a82ef5
// API: docs/api.md#deepspaceactivelist
// Rules: docs/server-rules.md "Deep space"
//
// The expedition screen's lists (CDeepSpace::Progress sends it when the screen opens).
//   (a)+(d) the areas the clocks, the exploration rates and the area images open, each with its
//       offers (state.cpp refresh_offers, area_list); (d) quick returns counted per day.
//   (b) the ships out (Active) and back (End), the members on them and the ships' bonus values;
//       (b) the pass's ships read `Subscription`, also sent here so a pass that ran out since the
//       last player load is seen as the server counts it (d).
//   (d) is_new is shown once: the areas' and offers' flags are cleared after this answer.
// Answers: the player state, DeepSpaceAreaList, DeepSpaceActiveShipInfoList,
// DeepSpaceEndShipInfoList, DeepSpaceBonusAllApplyInfoList, characters, Subscription.
std::vector<u8> deep_space_active_list(Ctx& ctx, const Request&) {
    int64_t t = ctx.now();
    time_saving_count(ctx, t);
    refresh_offers(ctx, t);
    Value data = ctx.base_data();
    data["DeepSpaceAreaList"] = area_list(ctx, t);
    data["DeepSpaceActiveShipInfoList"] = ship_list(ctx, t, false);
    data["DeepSpaceEndShipInfoList"] = ship_list(ctx, t, true);
    data["DeepSpaceBonusAllApplyInfoList"] = bonus_apply_list(ctx);
    data["characters"] = character_map(ctx);
    data["Subscription"] = ext::subscription_state(ctx);
    ctx.st.q("update ds_area set is_new = 0", {});
    ctx.st.q("update ds_offer set is_new = 0", {});
    // read by port/scripts/deepspace_session.sh ("(2 by the pass)")
    LOGI("server", "DeepSpaceActiveList: %zu areas, %zu ships out, %zu back, %u ships (%u by the pass)", data["DeepSpaceAreaList"].map.size(),
         data["DeepSpaceActiveShipInfoList"].map.size(), data["DeepSpaceEndShipInfoList"].map.size(), max_ships(ctx, t), subscription_ships(ctx, t));
    return ext::body(data);
}

// ---- DeepSpaceAutoMemberSelect -----------------------------------------------------------------

// DeepSpaceAutoMemberSelect(u32 bonus_set_id, u32 bonus_id) -> DeepSpaceAutoMemberSelectRes   fid ed9aae28
// API: docs/api.md#deepspaceautomemberselect
// Rules: docs/server-rules.md "Deep space"
//
// The party screen's 自動選択 (b: the arguments are the captured request's; the screen's hint
// "ボーナスを一つ選択すると、そのボーナスを強化する特性キャラクターを優先的に自動選択します").
//   (d) the free characters meeting the tapped bonus's conditions come first (by battle power for
//       a battle-power bonus, else by level), then the others by level;
//   (b) up to 8 members (uimsg_deep_space_select_num "%d / ８").
// Answers: the player state and AutoSelectedResult (the uids).
std::vector<u8> deep_space_auto_member_select(Ctx& ctx, const Request& req) {
    const auto args = args::DeepSpaceAutoMemberSelectArgs::from(req);
    std::vector<std::pair<std::pair<int, float>, u64>> scored;  // ((meets the bonus, battle power or level), uid)
    for (u64 uid : free_characters(ctx)) {
        Member m = member(ctx, uid);
        int hit = 0;
        bool battle_power = false;
        ctx.m.q("select * from master_deep_space_bonus where id = ?", {args.bonus_id}, [&](const Row& bonus_row) {
            battle_power = sums_battle_power(bonus_row);
            hit = applies(bonus_row, m) ? 1 : 0;
        });
        scored.push_back({{hit, battle_power ? m.battle_power : (float)m.level}, uid});
    }
    std::stable_sort(scored.begin(), scored.end(), [](auto& a, auto& b) { return a.first > b.first; });
    Value selected = Value::array();
    for (size_t k = 0; k < scored.size() && k < kMaxMembers; k++) selected.push(scored[k].second);
    Value data = ctx.base_data();
    data["AutoSelectedResult"] = selected;
    LOGI("server", "DeepSpaceAutoMemberSelect bonus %u: %zu members", args.bonus_id, selected.arr.size());
    return ext::body(data);
}

// ---- DeepSpaceMissionStart ---------------------------------------------------------------------

// The offer of a mission: whether it can depart now (on offer, not on a ship, not past its
// closed_at) and its bonus set.
struct Offer {
    bool open = false;
    u32 bonus_set_id = 0;
};
Offer find_offer(Ctx& ctx, u32 mission_id, int64_t t) {
    Offer offer;
    ctx.st.q("select * from ds_offer where mission_id = ?", {mission_id}, [&](const Row& offer_row) {
        offer.open = offer_row.i("ship_id") == 0 && !(offer_row.i("closed_at") && offer_row.i("closed_at") < t);
        offer.bonus_set_id = (u32)offer_row.i("bonus_set_id");
    });
    return offer;
}

// The refusal of a departure, "" when the party may go: (b) 1..8 owned characters (the "%d / ８"
// counter), none out on a ship, none twice.
const char* party_refusal(Ctx& ctx, const std::vector<u64>& uids) {
    std::set<u64> busy, seen;
    ctx.st.q("select uid from ds_ship_member", {}, [&](const Row& member_row) { busy.insert((u64)member_row.i("uid")); });
    if (uids.empty() || uids.size() > kMaxMembers) return "party size";
    for (u64 uid : uids)
        if (!seen.insert(uid).second || busy.count(uid) || !ctx.st.one("select count(*) from roster where uid = ?", {uid}))
            return "a member is busy, unknown or twice";
    return "";
}

// The lowest free ship number of 1..max_ships (state.cpp); 0 when every ship is out.
u32 free_ship(Ctx& ctx, u32 ships_max) {
    u32 ship_id = 0;
    for (u32 k = 1; k <= ships_max && !ship_id; k++)
        if (!ctx.st.one("select count(*) from ds_ship where ship_id = ?", {k})) ship_id = k;
    return ship_id;
}

// The bonus item: (a) a master_deep_space_bonus_item row of that master item open by the
// calendar; (d) one is used up per expedition; 10206 (items short) when none is owned. Returns the
// refusal (nullptr when the item was taken) and its code.
const char* take_bonus_item(Ctx& ctx, u32 item_id, ErrorCode& code) {
    bool bonus_item = false;
    ctx.m.q("select opened_at, closed_at from master_deep_space_bonus_item where master_item_id = ?", {item_id},
            [&](const Row& item_row) { bonus_item = bonus_item || open_at(item_row.s("opened_at"), item_row.s("closed_at"), calendar(ctx)); });
    code = ErrorCode::kItemUnusable;
    if (!bonus_item) return "not a bonus item";
    code = ErrorCode::kItemCountError;
    if (ext::stock_count(ctx, item_id) < 1) return "bonus item not owned";
    ext::add_stock(ctx, item_id, -1);
    return nullptr;
}

// The ship's bonus values (ds_bonus): the party's bonuses of the offer's set (bonuses.cpp), with
// (b) the bonus item (UpdateDeepSpaceMissionBonusList's multiplier): (a) type 2 multiplies every
// bonus by its value; (a) type 1 adds the bonus param1_id, (d) at the item's value.
void set_ship_bonuses(Ctx& ctx, u32 ship_id, u32 set_id, u32 item_id, const std::vector<u64>& uids) {
    std::vector<Member> party;
    for (u64 uid : uids) party.push_back(member(ctx, uid));
    ctx.st.q("delete from ds_bonus where ship_id = ?", {ship_id});
    double all_mul = 1.0;
    u32 item_bonus = 0;
    double item_value = 1.0;
    if (item_id)
        ctx.m.q("select * from master_deep_space_bonus_item where master_item_id = ?", {item_id}, [&](const Row& item_row) {
            if (!open_at(item_row.s("opened_at"), item_row.s("closed_at"), calendar(ctx))) return;
            if (item_row.i("type") == (int64_t)BonusItemType::kMultiplyAll) all_mul = item_row.f("value");
            else if (item_row.i("type") == (int64_t)BonusItemType::kAddBonus) {
                item_bonus = (u32)item_row.i("param1_id");
                item_value = item_row.f("value");
            }
        });
    for (auto& [bonus_id, value] : party_bonuses(ctx, set_id, party))
        ctx.st.q("insert into ds_bonus (ship_id, bonus_id, value) values (?,?,?)", {ship_id, bonus_id, (double)value * all_mul});
    if (item_bonus) ctx.st.q("insert or replace into ds_bonus (ship_id, bonus_id, value) values (?,?,?)", {ship_id, item_bonus, item_value});
}

// DeepSpaceMissionStart(u32 mission_id, u32 item_id, vector<u64> uids) -> DeepSpaceMissionStartRes   fid 63c9927a
// API: docs/api.md#deepspacemissionstart
// Rules: docs/server-rules.md "Deep space"
//
// Sends a party on an expedition (the arguments: deepspace_args.h). The area is the mission's.
//   (d) refused with 10208 (kItemUnusable, the generic refusal, as the other modules) for a
//       mission not on offer or at its play limit, a bad party ((b) 1..8 owned characters, none out
//       on a ship, none twice) or no free ship; a bonus item: 10208 when it isn't one (open by the
//       calendar, a), 10206 (kItemCountError) when none is owned; (d) one is used up.
//   (a) the expedition lasts master_deep_space_mission.time, (c)+(d) in minutes (30..480: the
//       client shows it as 0.5H..8H, uimsg_deep_space_exploration_time3 "%.1fH").
//   (d) a departure is a play for the daily / weekly limits.
//   (a) achievement type 45 "ディープスペース探査を N回行う" / "派遣する" counts expeditions;
//       (d) a departure counts, at its time (ds_log; api/presents/achievements.cpp).
//   (d) the area becomes the last played; the ship's bonus values are the party's (set_ship_bonuses).
// Answers: the player state, DeepSpaceShip, DeepSpaceActiveShipInfoList, DeepSpaceArea,
// DeepSpaceAreaList, UpdateDeepSpaceBonusAllApplyInfoList (this ship's),
// DeepSpaceBonusAllApplyInfoList, characters.
std::vector<u8> deep_space_mission_start(Ctx& ctx, const Request& req) {
    const auto args = args::DeepSpaceMissionStartArgs::from(req);
    const char* method = "DeepSpaceMissionStart";
    u32 area_id = (u32)ctx.m.one("select master_deep_area_id from master_deep_space_mission where id = ?", {args.mission_id});
    int64_t t = ctx.now();
    refresh_offers(ctx, t);
    // 1. the offer, the party, the ship, the bonus item
    Offer offer = find_offer(ctx, args.mission_id, t);
    if (!offer.open) return refuse(ctx, method, "mission not on offer", ErrorCode::kItemUnusable);
    bool limited = false;
    ctx.st.q("select * from ds_offer where mission_id = ?", {args.mission_id}, [&](const Row& offer_row) { limited = at_limit(ctx, offer_row); });
    if (limited) return refuse(ctx, method, "the mission's play limit is reached", ErrorCode::kItemUnusable);  // (d) code
    if (const char* why = party_refusal(ctx, args.uids); *why) return refuse(ctx, method, why, ErrorCode::kItemUnusable);
    u32 ships_max = max_ships(ctx, t);
    u32 ship_id = free_ship(ctx, ships_max);
    if (!ship_id) return refuse(ctx, method, "no free ship", ErrorCode::kItemUnusable);
    if (args.item_id) {
        ErrorCode code;
        if (const char* why = take_bonus_item(ctx, args.item_id, code)) return refuse(ctx, method, why, code);
    }
    // 2. the ship departs
    int64_t minutes = ctx.m.one("select time from master_deep_space_mission where id = ?", {args.mission_id});
    ctx.st.q("insert into ds_ship (ship_id, area_id, mission_id, bonus_set_id, item_id, started_at, closed_at) values (?,?,?,?,?,?,?)",
             {ship_id, area_id, args.mission_id, offer.bonus_set_id, args.item_id, t, t + minutes * 60});
    // the crew, slot 1..8 in the order sent (b: the ship_slot the client looks up; owned, checked above)
    for (size_t k = 0; k < args.uids.size(); k++)
        ctx.st.q("insert into ds_ship_member (ship_id, slot, uid) values (?,?,?)", {ship_id, (u32)k + 1, CharacterUid(args.uids[k])});
    ctx.st.q(
        "update ds_offer set ship_id = ?, updated_at = ?, play_count_daily = play_count_daily + 1, "
        "play_count_weekly = play_count_weekly + 1 where mission_id = ?",
        {ship_id, t, args.mission_id});
    ctx.st.q("insert into ds_log (mission_id, started_at) values (?, ?)", {args.mission_id, t});
    ctx.st.q("update ds_area set is_last_play = (area_id = ?)", {area_id});
    set_ship_bonuses(ctx, ship_id, offer.bonus_set_id, args.item_id, args.uids);
    // 3. the answer
    Value data = ctx.base_data();
    data["DeepSpaceShip"] = ship_info_of(ctx, ship_id);
    data["DeepSpaceActiveShipInfoList"] = ship_list(ctx, t, false);
    put_area_info(ctx, data, area_id, t);
    data["DeepSpaceAreaList"] = area_list(ctx, t);
    data["UpdateDeepSpaceBonusAllApplyInfoList"] = bonus_apply_list(ctx, ship_id);
    data["DeepSpaceBonusAllApplyInfoList"] = bonus_apply_list(ctx);
    data["characters"] = character_map(ctx);
    LOGI("server", "DeepSpaceMissionStart area %u mission %u: ship %u/%u, %zu members, back in %lld min", area_id, args.mission_id, ship_id,
         ships_max, args.uids.size(), (long long)minutes);
    return ext::body(data);
}

// ---- DeepSpaceMissionEnd / DeepSpaceMissionEndNow ----------------------------------------------

// A ship out or back (a ds_ship row).
struct Ship {
    bool found = false;
    u32 ship_id = 0, area_id = 0, mission_id = 0;
    int64_t closed_at = 0;
    std::vector<CharacterUid> members;  // the crew (ds_ship_member), by slot
    Value info;                         // CDeepSpaceShipInfo as it was found
};
Ship load_ship(Ctx& ctx, u32 ship_id) {
    Ship ship;
    ship.ship_id = ship_id;
    ctx.st.q("select * from ds_ship where ship_id = ?", {ship_id}, [&](const Row& ship_row) {
        ship.found = true;
        ship.area_id = (u32)ship_row.i("area_id");
        ship.mission_id = (u32)ship_row.i("mission_id");
        ship.closed_at = ship_row.i("closed_at");
        ship.members = ship_members(ctx, ship_id);
        ship.info = ship_info(ctx, ship_row);
    });
    return ship;
}

// The quick-return price paid: items and coins.
struct QuickReturnPaid {
    u32 items = 0, coins = 0;
};
// (b) the quick-return price (rules::deepspace::quick_return_cost) with (a) master_global
// deep_space_quick_return_item and (a) master_deep_space_time_saving.rate of the day's use number
// (+1, capped at the last row); paid with the items owned, the rest in coins, (a) free coins first
// (core/wallet.h). False when the coins are short.
bool pay_quick_return(Ctx& ctx, const Ship& ship, int64_t t, QuickReturnPaid& paid) {
    u32 used_today = time_saving_count(ctx, t);
    u32 last_row = (u32)ctx.m.one("select max(id) from master_deep_space_time_saving", {});
    double rate = 0;
    ctx.m.q("select rate from master_deep_space_time_saving where id = ?", {std::min(used_today + 1, last_row)},
            [&](const Row& time_saving_row) { rate = time_saving_row.f("rate"); });
    std::string label = master::global_str(ctx.m.h, "deep_space_quick_return_item");
    u32 item_id = (u32)ctx.m.one("select id from master_item where id_label = ?", {label});
    auto cost = dr::quick_return_cost(ship.closed_at - t, (float)rate, item_id ? ext::stock_count(ctx, item_id) : 0);
    wallet::Coins have = wallet::coins(ctx.st.h);
    if (!wallet::covers(have, cost.coins)) return false;
    if (cost.items) ext::add_stock(ctx, item_id, -(int64_t)cost.items);
    wallet::take(ctx.st.h, wallet::split(have, cost.coins));  // (a) free coins first (core/wallet.h)
    ctx.st.q("update player set time_saving_count = ?", {used_today + 1});
    paid.items = cost.items;
    paid.coins = cost.coins;
    return true;
}

// DeepSpaceMissionEndNow(u32 ship_id) -> DeepSpaceMissionEndNowRes            fid 2df0328c
// API: docs/api.md#deepspacemissionendnow
// Rules: docs/server-rules.md "Deep space"
//
// Quick return (今すぐ帰還, CDeepSpaceQuickReturnDialog).
//   (d) an unknown ship is refused with 10208 (kItemUnusable); a ship out costs the quick-return
//       price (pay_quick_return), 20000 (kCoinsShort) when the coins are short; one already back
//       costs nothing.
//   (b) it brings the ship home, nothing more: CApiNotify::OnDeepSpaceMissionEndNowRes moves
//       DeepSpaceShip into the End map (the client then shows the mission as 帰還済 and collects it
//       with MissionEnd, which gives the rewards).
// Answers: the player state, DeepMissionPlayer, DeepSpaceShip, DeepSpaceActiveShipInfoList,
// DeepSpaceEndShipInfoList, DeepSpaceArea, StockItem.
std::vector<u8> deep_space_mission_end_now(Ctx& ctx, const Request& req) {
    const auto args = args::DeepSpaceMissionEndArgs::from(req);
    const char* method = "DeepSpaceMissionEndNow";
    int64_t t = ctx.now();
    Ship ship = load_ship(ctx, args.ship_id);
    if (!ship.found) return refuse(ctx, method, "no such ship", ErrorCode::kItemUnusable);
    QuickReturnPaid paid;
    if (ship.closed_at > t && !pay_quick_return(ctx, ship, t, paid)) return refuse(ctx, method, "not enough coins", ErrorCode::kCoinsShort);
    ctx.st.q("update ds_ship set closed_at = ? where ship_id = ?", {std::min(ship.closed_at, t), ship.ship_id});
    Value data = ctx.base_data();
    data["DeepMissionPlayer"] = deep_mission_player(ctx, t, false);
    data["DeepSpaceShip"] = ship_info_of(ctx, ship.ship_id);
    data["DeepSpaceActiveShipInfoList"] = ship_list(ctx, t, false);
    data["DeepSpaceEndShipInfoList"] = ship_list(ctx, t, true);
    put_area_info(ctx, data, ship.area_id, t);
    data["StockItem"] = ctx.stock();
    LOGI("server", "%s ship %u (area %u mission %u): back now for %u items and %u coins", method, ship.ship_id, ship.area_id, ship.mission_id,
         paid.items, paid.coins);
    return ext::body(data);
}

// What MissionEnd's rewards did, for its answer and log line.
struct Expedition {
    u32 player_exp = 0, character_exp = 0, fol = 0, area_exp = 0;
    double rare_mission_rate = 0;
    u32 rare_mission_type = 0;
    u32 level_before = 0, level_after = 0;
    Value characters_exp = Value::object();  // add_characters_exp
    Value content_map = Value::object();     // CContentInfoMap
    Value added_items = Value::array();      // AddItem
    size_t lots = 0;
    std::string rare_label;  // the id_label of a rare mission offered, "" when none
};

// Player: (a) player_exp, (a) fol; the level-up adds the new maximum stamina (as MissionEnd).
void grant_player(Ctx& ctx, const Ship& ship, Expedition& done) {
    ctx.m.q("select * from master_deep_space_mission where id = ?", {ship.mission_id}, [&](const Row& mission_row) {
        done.player_exp = (u32)mission_row.i("player_exp");
        done.character_exp = (u32)mission_row.i("character_exp");
        done.fol = (u32)mission_row.i("fol");
        done.area_exp = (u32)mission_row.i("exp");
        done.rare_mission_rate = mission_row.f("rare_mission_rate");
        done.rare_mission_type = (u32)mission_row.i("rare_mission_type_id");
    });
    u32 exp_before = 0;
    ctx.st.q("select level, exp from player", {}, [&](const Row& player_row) {
        done.level_before = (u32)player_row.i("level");
        exp_before = (u32)player_row.i("exp");
    });
    auto [level_after, exp_after] = rules::add_exp(done.level_before, exp_before, done.player_exp, ctx.player_next(), ctx.player_level_max());
    done.level_after = level_after;
    ctx.st.q("update player set level = ?, exp = ?", {level_after, exp_after});
    ext::add_fol(ctx, done.fol);
    if (level_after > done.level_before) {
        ctx.tick_stamina();
        ctx.st.q("update player set stamina = stamina + ?, stamina_at = ?", {ctx.stamina_max(level_after), ctx.now()});
    }
}

// Characters: (a) character_exp each.
// (b) CAddCharacterExpInfo {character_id, add_exp, before_level, before_exp, after_level,
// after_exp, order_id}: CDeepSpaceResult::Setup shows the members by order_id 0..7 and
// animates before_level / before_exp + add_exp; the handler stores after_level / after_exp.
void grant_character_exp(Ctx& ctx, const Ship& ship, Expedition& done) {
    u32 order = 0;
    for (const CharacterUid uid : ship.members)
        ctx.st.q("select * from roster where uid = ?", {uid}, [&](const Row& roster_row) {
            const RoleId role_id = roster_row.id<RoleId>("role_id");
            u32 level_before = (u32)roster_row.i("level"), exp_before = (u32)roster_row.i("exp");
            auto [level_after, exp_after] =
                rules::add_exp(level_before, exp_before, done.character_exp, ctx.role_next(role_id), ctx.role_level_cap(role_id));
            ctx.st.q("update roster set level = ?, exp = ? where uid = ?", {level_after, exp_after, uid});
            Value info = Value::object();
            info["character_id"] = uid.v;
            info["add_exp"] = done.character_exp;
            info["order_id"] = order++;
            info["before_level"] = level_before;
            info["before_exp"] = exp_before;
            info["after_level"] = level_after;
            info["after_exp"] = exp_after;
            done.characters_exp[std::to_string(uid.v)] = info;
        });
}

// The drops (rewards.cpp roll_rewards), granted, and their CDropContentInfo entries.
void grant_drops(Ctx& ctx, const Ship& ship, Expedition& done, double& rare_mission_mul) {
    Rewards rewards = roll_rewards(ctx, ship.mission_id, ship.ship_id);
    Value stocks = Value::array(), characters = Value::array();
    u32 n = 0;
    for (auto& lot : rewards.lots) {
        ctx.grant(lot.type, lot.id, lot.num, done.added_items, stocks, characters);
        Value info = Value::object();
        info["content_id"] = lot.id;
        info["content_type"] = lot.type;
        info["num"] = lot.num;
        info["is_new"] = false;                                 // (d)
        info["master_item_id"] = lot.type == 2 ? 0u : lot.id;  // (d) none for a character (content type 2)
        info["bonus_category"] = (u32)lot.category;
        info["is_rare_bonus"] = lot.rare;
        info["is_add_bonus"] = lot.add;
        info["is_hit_bonus"] = lot.hit;
        info["is_rare_hit_bonus"] = false;  // (d)
        done.content_map[std::to_string(++n)] = info;
    }
    done.lots = rewards.lots.size();
    rare_mission_mul = rewards.rare_mission_mul;
}

// The offer: back on the list with a new bonus set (d); a rare offer is used up (d).
void renew_offer(Ctx& ctx, const Ship& ship, int64_t t) {
    bool rare_offer = ctx.st.one("select closed_at from ds_offer where mission_id = ?", {ship.mission_id}) != 0;
    if (rare_offer) {
        ctx.st.q("delete from ds_offer where mission_id = ?", {ship.mission_id});
    } else {
        u32 set_type = (u32)ctx.m.one("select bonus_set_type_id from master_deep_space_mission where id = ?", {ship.mission_id});
        ctx.st.q("update ds_offer set ship_id = 0, bonus_set_id = ?, play_count = play_count + 1, updated_at = ? where mission_id = ?",
                 {roll_bonus_set(ctx, set_type), t, ship.mission_id});
    }
}

// A rare mission: (a) rare_mission_rate percent (x the rare-point bonuses) to offer one of the
// missions whose rare_type_id is this mission's rare_mission_type_id (open by the clock,
// by rate_weigh) in the same area, (a) for rare_limit_time minutes. (d) one rare offer of a
// mission at a time.
void roll_rare_offer(Ctx& ctx, const Ship& ship, int64_t t, double rare_mission_mul, Expedition& done) {
    if (!done.rare_mission_type || !(uniform(ctx) * 100.0 < done.rare_mission_rate * rare_mission_mul)) return;
    std::vector<u32> ids, weights, limit_minutes, set_types;
    ctx.m.q("select * from master_deep_space_mission where rare_type_id = ? and master_deep_area_id = ?", {done.rare_mission_type, ship.area_id},
            [&](const Row& mission_row) {
                if (!open_by_both_clocks(ctx, mission_row.s("opened_at"), mission_row.s("closed_at")) || mission_row.i("rate_weigh") <= 0) return;
                if (ctx.st.one("select count(*) from ds_offer where mission_id = ?", {mission_row.i("id")})) return;
                ids.push_back((u32)mission_row.i("id"));
                weights.push_back((u32)mission_row.i("rate_weigh"));
                limit_minutes.push_back((u32)mission_row.i("rare_limit_time"));
                set_types.push_back((u32)mission_row.i("bonus_set_type_id"));
            });
    u64 sum = 0;
    for (u32 w : weights) sum += w;
    if (!sum) return;
    int k = rules::weighted_pick(weights, (*ctx.rng)() % sum);
    ctx.st.q("insert into ds_offer (mission_id, area_id, bonus_set_id, closed_at, is_new, updated_at) values (?,?,?,?,1,?)",
             {ids[k], ship.area_id, roll_bonus_set(ctx, set_types[k]), t + (int64_t)limit_minutes[k] * 60, t});
    ctx.m.q("select id_label from master_deep_space_mission where id = ?", {ids[k]},
            [&](const Row& mission_row) { done.rare_label = mission_row.s("id_label"); });
}

// DeepSpaceMissionEnd(u32 ship_id) -> DeepSpaceMissionEndRes                  fid 140e365b
// API: docs/api.md#deepspacemissionend
// Rules: docs/server-rules.md "Deep space"
//
// Collects a ship that is back (CDeepSpace::SetupPartySelect sends it for a 帰還済 mission).
//   (d) an unknown ship, or one not back yet, is refused with 10208 (kItemUnusable).
//   (a) the mission's player_exp (a level-up adds the new maximum stamina, as MissionEnd), fol,
//       character_exp to each member (grant_character_exp) and exp to the area's exploration, up
//       to its max_exp.
//   (a)+(c)+(d) the drops and the ship's bonus effects (rewards.cpp roll_rewards).
//   (d) the offer goes back on the list with a new bonus set; a rare offer is used up; (a)+(d) a
//       rare mission may be offered (roll_rare_offer); areas the new exploration rate opens open.
// Answers: the player state, DeepMissionPlayer, DeepSpaceShip ((b) the handler takes this ship out
// of both ship maps), the ship lists, DeepSpaceBonusAllApplyInfoList, characters, DeepSpaceArea,
// DeepSpaceAreaList, add_characters_exp, CContentInfoMap, AddItem (when items were granted),
// StockItem.
std::vector<u8> deep_space_mission_end(Ctx& ctx, const Request& req) {
    const auto args = args::DeepSpaceMissionEndArgs::from(req);
    const char* method = "DeepSpaceMissionEnd";
    int64_t t = ctx.now();
    Ship ship = load_ship(ctx, args.ship_id);
    if (!ship.found) return refuse(ctx, method, "no such ship", ErrorCode::kItemUnusable);
    if (ship.closed_at > t) return refuse(ctx, method, "the ship isn't back yet", ErrorCode::kItemUnusable);
    // 1. the rewards
    Expedition done;
    grant_player(ctx, ship, done);
    grant_character_exp(ctx, ship, done);
    u32 max_exp = (u32)ctx.m.one("select max_exp from master_deep_space_area where id = ?", {ship.area_id});
    ctx.st.q("update ds_area set exp = min(exp + ?, ?) where area_id = ?", {done.area_exp, max_exp, ship.area_id});
    double rare_mission_mul = 1.0;
    grant_drops(ctx, ship, done, rare_mission_mul);
    // 2. the offers and the ship
    renew_offer(ctx, ship, t);
    roll_rare_offer(ctx, ship, t, rare_mission_mul, done);
    ctx.st.q("delete from ds_ship where ship_id = ?", {ship.ship_id});  // and its crew (ON DELETE CASCADE)
    ctx.st.q("delete from ds_bonus where ship_id = ?", {ship.ship_id});
    refresh_offers(ctx, t);  // areas the new exploration rate opens
    // 3. the answer
    Value data = ctx.base_data();
    data["DeepMissionPlayer"] = deep_mission_player(ctx, t, done.level_after > done.level_before);
    data["DeepSpaceShip"] = ship.info;
    data["DeepSpaceActiveShipInfoList"] = ship_list(ctx, t, false);
    data["DeepSpaceEndShipInfoList"] = ship_list(ctx, t, true);
    data["DeepSpaceBonusAllApplyInfoList"] = bonus_apply_list(ctx);
    data["characters"] = character_map(ctx);
    put_area_info(ctx, data, ship.area_id, t);
    data["DeepSpaceAreaList"] = area_list(ctx, t);
    data["add_characters_exp"] = done.characters_exp;
    data["CContentInfoMap"] = done.content_map;
    if (!done.added_items.arr.empty()) data["AddItem"] = done.added_items;
    data["StockItem"] = ctx.stock();
    LOGI("server",
         "%s ship %u (area %u mission %u): player exp +%u (level %u -> %u), fol +%u, characters +%u exp x%zu, area exp +%u, "
         "%zu lots, quick return %u items %u coins%s%s",
         method, ship.ship_id, ship.area_id, ship.mission_id, done.player_exp, done.level_before, done.level_after, done.fol, done.character_exp,
         done.characters_exp.map.size(), done.area_exp, done.lots, 0u, 0u, done.rare_label.empty() ? "" : ", rare mission ", done.rare_label.c_str());
    return ext::body(data);
}

}  // namespace
}  // namespace deepspace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_deepspace() {
    using namespace deepspace;
    ext::add_api({"DeepSpaceActiveList"}, deep_space_active_list);
    ext::add_api({"DeepSpaceAutoMemberSelect"}, deep_space_auto_member_select);
    ext::add_api({"DeepSpaceMissionStart"}, deep_space_mission_start);
    ext::add_api({"DeepSpaceMissionEnd"}, deep_space_mission_end);
    ext::add_api({"DeepSpaceMissionEndNow"}, deep_space_mission_end_now);
}

}  // namespace soa::server
