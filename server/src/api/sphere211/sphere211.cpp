// Local server: Sphere 211, the extra dungeon of 3.7.0 (api/sphere211/README.md). The 13
// Sphere211* APIs over the master_sphere211* tables; the battles are master_event_mission rows
// played through the core MissionStart / MissionEnd (ext::Ctx::core_mission). This file holds the
// handlers, the player-load hook and the tables; the seasons are in season.cpp, the floors and
// cells in floors.cpp, the boxes in rewards.cpp, the ranking in ranking.cpp, the rental slot in
// rental.cpp, the state every answer carries in state.cpp (dive.h). Port code, not guest
// behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption. Rules in docs/server-rules.md "Sphere 211".
//
// Shape of a dive (c: how the mode played online; the client's screens agree, (b)):
//  - a season (master_sphere211) runs for a few weeks; a dive starts at floor 0 and warps to a
//    floor chosen from the next `lot_floor_num` floors (the "warp access", from the treasure
//    boxes gathered so far: master_sphere211_floor_transfer_level / _rate);
//  - a floor (master_sphere211_floor, by level) is a map of cells (master_sphere211_floor_asset,
//    one template lotted from the floor's asset box) from the start cell to the goal; each cell
//    is a battle lotted from its mission box (master_sphere211_mission_box, the row's `type` =
//    the cell's lottery_type) and costs sphere stamina (floor.use_stamina, own gauge:
//    master_global sphere_stamina_max / sphere_stamina_recovery_time);
//  - a won battle adds treasure boxes (floor treasure_num + boss / rare extras + the clear-streak
//    bonus), each of a rank S..D lotted by the floor's master_sphere211_treasure weights;
//  - reaching the goal clears the floor (Sphere211FloorClear: the floor's clear present, more
//    boxes) and the next floor is chosen the same way; ReturnSphere211 ends the dive and opens
//    the boxes (the rank's common drop, master_sphere211_treasure_contents).
#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

#include "api/social/rental.h"
#include "api/sphere211/dive.h"
#include "api/sphere211/sphere211_args.h"
#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "core/response.h"
#include "core/wallet.h"

namespace soa::server {

namespace sphere211 {
namespace {

using ext::refuse;

// The core MissionStart / MissionEnd / MissionFailed requests a Sphere 211 battle runs through
// (their fids: docs/api.md).
constexpr u32 kFidMissionStart = 0xb7c62bc2, kFidMissionEnd = 0x8312a64c, kFidMissionFailed = 0x479604f6;
constexpr u32 kMissionTypeEvent = 1;  // (b) MissionStart's mission type of a master_event_mission
constexpr u32 kAutoMembers = 4;       // (b) the party screen's four slots

// (b) Sphere211TreasureDropInfo.type (ResultUtility::GetRewardType(Common::Sphere211DropType),
// CSphereFloorClear): the badges of the mission result and the floor-clear boxes; (d) the battle's
// own boxes as type 0 (no badge).
enum class DropType : u32 { kBattle = 0, kStreak = 1, kBoss = 2, kRare = 3, kFloorClear = 4 };

// ---- GetSphere211Info -------------------------------------------------------------------------

// GetSphere211Info() -> GetSphere211InfoRes                                   fid 1e03058b
// API: docs/api.md#getsphere211info
// Rules: docs/server-rules.md "Sphere 211"
//
// The board, when it opens (phase 5).
//   (d) loads the dive (a season change ends the old one: season.cpp load_dive); a dive at floor 0
//       starts on floor 1 (floors.cpp start_dive_if_idle).
//   (d) the season-end result goes out once: end_pending is cleared after this answer.
// Answers: the dive state (state.cpp put_state).
std::vector<u8> get_sphere211_info(Ctx& ctx, const Request&) {
    Season season = load_dive(ctx);
    start_dive_if_idle(ctx, season);
    Value data = dive_state(ctx, season);
    set_sphere_meta(ctx, "end_pending", 0);
    LOGI("server", "GetSphere211Info: season %u (index %u), floor %u", season.id, season.index,
         (u32)ctx.st.one("select floor_level from sphere where id = 1", {}));
    return ext::body(data);
}

// ---- Sphere211SelectedFloor ---------------------------------------------------------------------

// Sphere211SelectedFloor(u32 offset) -> Sphere211SelectedFloorRes             fid f8371209
// API: docs/api.md#sphere211selectedfloor
// Rules: docs/server-rules.md "Sphere 211"
//
// The floor chosen in the next-floor select.
//   (b) the list is MissionUtility::Sphere211FloorData(floor, lot_floor_num): the next
//       lot_floor_num floors; the request carried 1 when 2F was chosen on 1F, so the value is the
//       offset from the current floor, i.e. the 1-based entry of that list.
//   (d) clamped into 1 .. lot_floor_num; the new floor is lotted (floors.cpp enter_floor).
// Answers: the dive state.
std::vector<u8> sphere211_selected_floor(Ctx& ctx, const Request& req) {
    const auto args = args::Sphere211SelectedFloorArgs::from(req);
    Season season = load_dive(ctx);
    u32 floor = 0, lot = 0;
    ctx.st.q("select floor_level, lot_floor_num from sphere where id = 1", {}, [&](const Row& sphere_row) {
        floor = (u32)sphere_row.i("floor_level");
        lot = (u32)sphere_row.i("lot_floor_num");
    });
    lot = std::max<u32>(1, lot);
    u32 level = floor + std::min(std::max<u32>(1, args.offset), lot);
    enter_floor(ctx, season, level);
    LOGI("server", "Sphere211SelectedFloor(%u): floor %u -> %u (lot %u)", args.offset, floor, level, lot);
    return ext::body(dive_state(ctx, season));
}

// ---- Sphere211MissionStart ----------------------------------------------------------------------

// The battle's party (b): slots 1-3 are party members, slot 4 (GetParty(3), with its owner's user
// id) the rental slot, which the menu also fills from the player's own characters: played as the
// core's own helper (d: no other players, so an own character only). Members not in the roster are
// left out.
void own_party(Ctx& ctx, const args::Sphere211MissionStartArgs& args, ext::MissionOverride& override_) {
    for (u64 uid : args.party_slots)
        if (uid && ctx.st.one("select count(*) from roster where uid = ?", {uid})) override_.party.push_back(uid);
    if (args.slot4 && ctx.st.one("select count(*) from roster where uid = ?", {args.slot4})) override_.helper = args.slot4;
}

// EX characters (master_role.rank 5; b: CParameterUtility::IsRoleDeity @01820c3c is rank == 5).
// (b) CSphereMissionDetail::NextPhase (@01c1989c) checks the four slots, the own characters only
// (tCharaData::Type() 0; a rental is never checked), and with an EX character among them opens
// CDialogManager::OpenSphere211SallyDialogWithDeity with master_global max_revive_count (3, a) minus
// CParameterManager+0xf48 (CPlayerInfo+0x910, Player.sphere211_revive_count) as "使用可能回数 残り
// %d 回" (uimsg_sphere211_mission_start_with_deity).
constexpr u32 kRankDeity = 5;
std::vector<u64> ex_members(Ctx& ctx, const ext::MissionOverride& override_, bool rented_helper) {
    std::vector<u64> members = override_.party;
    if (override_.helper && !rented_helper) members.push_back(override_.helper);
    std::vector<u64> ex;
    for (u64 uid : members)
        if (ctx.m.one("select rank from master_role where id = ?", {ctx.st.one("select role_id from roster where uid = ?", {uid})}) == kRankDeity)
            ex.push_back(uid);
    return ex;
}

// The cell's enemy level: (a) overwrite_enemy_level of the cell, else base_enemy_level + the cell's
// add_enemy_level (d: their sum).
// Port test hook (not a game rule): sphere_meta 'test_enemy_level', when a session script sets
// it in the state DB, overrides the enemy level, so port/scripts/sphere211_session.sh can lose
// a battle on purpose (continue / retire). Never set by the server itself.
u32 enemy_level(Ctx& ctx, const Floor& floor, u32 asset_id) {
    u32 add = 0;
    ctx.m.q("select add_enemy_level from master_sphere211_floor_asset where id = ?", {asset_id},
            [&](const Row& asset_row) { add = (u32)asset_row.i("add_enemy_level"); });
    u32 overwrite = (u32)ctx.st.one("select overwrite_enemy_level from sphere_cell where asset_id = ?", {asset_id});
    u32 level = overwrite ? overwrite : floor.base_enemy_level + add;
    if (int64_t test_level = sphere_meta(ctx, "test_enemy_level")) level = (u32)test_level;
    return level;
}

// Sphere211MissionStart(u32, u32 cell, u64 uid x3, u64 slot4, u32 owner) -> Sphere211MissionStartRes   fid 04ec9513
// API: docs/api.md#sphere211missionstart
// Rules: docs/server-rules.md "Sphere 211"
//
// A cell's battle (b: CStageManager::CallMissionStart type 5; the arguments: sphere211_args.h).
//   (d) an unknown cell (or one without a battle) is refused with 10208 (kItemUnusable).
//   (a) floor.use_stamina from the sphere gauge; 10004 (kStaminaShort) when short, as AP (d).
//   (b)+(d) the party and slot 4 (own_party); a rental in slot 4 (rental.cpp rental_available)
//       plays as the core's rental helper (b: the core plays a rental id in the 4th slot as the
//       clone of its roster character); a rental not available is refused with 10208 (d).
//   (a)+(d) the enemy level (enemy_level).
//   The battle is the core event mission start (ext::Ctx::core_mission, no AP); its refusal is
//   refused with 10208 (d).
//   (b) the cell is marked playing, the party as departed (a character sorties once per dive,
//       until 帰還: uimsg_sphere211_return_dialog "帰還をすることで全てのキャラが再度出撃できるように
//       なり"; the departed stay across floors); (d) a rented character doesn't depart.
//   EX characters (ex_members): a sortie with one uses one of master_global max_revive_count (3)
//       uses until 帰還 (sphere.revive_count, sent as Player.sphere211_revive_count; b: the sally
//       dialog shows max minus it, and UpdateMissionStartPlayerInfo takes the Player answered
//       here); (a) uimsg_sphere211_mission_start_with_deity: the characters sortieing with an EX
//       character don't become 出撃済み, the EX character does. (d) Departing happens at the start,
//       as for every sortie (the text says "on a clear"), and one use per sortie however many EX
//       characters it has; with no uses left the start is refused with 10208 (kItemUnusable) (d:
//       the code; the client's dialog then says 残り 0 回 and doesn't stop the start itself).
//   (d) the gauge's regeneration starts when it leaves full.
// Answers: the core MissionStart's keys (MissionParameter with the enemy level, PlayMission,
// BattleParameter) and the dive state.
std::vector<u8> sphere211_mission_start(Ctx& ctx, const Request& req) {
    const auto args = args::Sphere211MissionStartArgs::from(req);
    const char* method = "Sphere211MissionStart";
    Season season = load_dive(ctx);
    // 1. the cell and the cost
    u32 asset_id = 0, mission_id = 0;
    if (!find_cell(ctx, req, asset_id, mission_id) || !mission_id) return refuse(ctx, method, "no such cell", ErrorCode::kItemUnusable);
    u32 level = (u32)ctx.st.one("select floor_level from sphere where id = 1", {});
    Floor floor = floor_row(ctx, season, level);
    u32 stamina = (u32)ctx.st.one("select stamina from sphere where id = 1", {});
    if (stamina < floor.use_stamina) return refuse(ctx, method, "sphere stamina short", ErrorCode::kStaminaShort);
    // 2. the party, slot 4, the enemy level
    ext::MissionOverride override_;
    override_.free_stamina = true;
    own_party(ctx, args, override_);
    u32 lender = 0;
    if (args.has_owner && args.slot4 && rental::source_uid(args.slot4)) {
        lender = args.owner;
        if (!rental_available(ctx, lender, args.slot4)) return refuse(ctx, method, "rental not available", ErrorCode::kItemUnusable);  // (d) the code
        override_.helper = args.slot4;
    }
    override_.overwrite_enemy_level = enemy_level(ctx, floor, asset_id);
    override_.add_enemy_level = 0;
    const std::vector<u64> ex = ex_members(ctx, override_, lender != 0);
    u32 revive_count = (u32)ctx.st.one("select revive_count from sphere where id = 1", {});
    u32 revive_max = ctx.global_u32("max_revive_count", 3);
    if (!ex.empty() && revive_count >= revive_max)
        return ext::refusef(ctx, method, ErrorCode::kItemUnusable, "EX sorties used up (%u of %u)", revive_count, revive_max);
    // 3. the core battle
    Request core{"MissionStart", kFidMissionStart, {kMissionTypeEvent, mission_id, 0, 0, 0, 0, 0}, {}, {}};
    Value data = ctx.core_mission(core, &override_);
    if (data.type != Value::Map) return refuse(ctx, method, "core MissionStart refused", ErrorCode::kItemUnusable);
    // 4. the dive
    int64_t t = ctx.now();
    if (stamina >= stamina_max(ctx)) ctx.st.q("update sphere set stamina_at = ?", {t});  // (d) regen starts when leaving full
    ctx.st.q("update sphere set stamina = stamina - ?", {floor.use_stamina});
    ctx.st.q("update sphere_cell set playing = case when asset_id = ? then 1 else 0 end, updated_at = ?", {asset_id, t});
    if (ex.empty()) {
        for (u64 uid : override_.party) ctx.st.q("insert or ignore into sphere_departed (uid) values (?)", {uid});
        if (override_.helper && !lender) ctx.st.q("insert or ignore into sphere_departed (uid) values (?)", {override_.helper});
    } else {  // an EX sortie: only the EX characters depart; one use
        for (u64 uid : ex) ctx.st.q("insert or ignore into sphere_departed (uid) values (?)", {uid});
        ctx.st.q("update sphere set revive_count = revive_count + 1 where id = 1", {});
        LOGI("server", "Sphere211MissionStart: %zu EX character(s), the others stay; EX sorties %u -> %u of %u", ex.size(), revive_count,
             revive_count + 1, revive_max);
    }
    if (lender) record_rental(ctx, season, lender, t);
    put_state(ctx, season, data);
    LOGI("server", "Sphere211MissionStart: floor %u cell %u mission %u, %zu members, enemy level %u, sphere stamina %u -> %u", level, asset_id,
         mission_id, override_.party.size(), override_.overwrite_enemy_level, stamina, stamina - floor.use_stamina);
    return ext::body(data);
}

// ---- Sphere211MissionEnd ------------------------------------------------------------------------

// Sphere211MissionEnd(u32, u32 cell) -> Sphere211MissionEndRes                fid 03f169b2
// API: docs/api.md#sphere211missionend
// Rules: docs/server-rules.md "Sphere 211"
//
// A won battle.
//   (a) the core MissionEnd of the event mission (EXP, FOL, drops, first-clear presents).
//   The cell is cleared, the clear streak grows; (d) a win is logged for the achievements (type 62)
//   and the season's ranking.
//   The battle's treasure boxes: (a) floor.treasure_num, + boss_add_treasure_num for a boss cell
//   (lottery_type 2, d), + rare_add_treasure_num for a rare cell (lottery_type 4 / 6, d), + the
//   streak bonus (a: master_sphere211_treasure_streak_bonus, the highest row whose id (streak) is
//   reached, b: MissionUtility::Sphere211DropBonusCount).
//   Sphere211TreasureDropInfoList [{type, num}] (b: Sphere211TreasureDropInfo::Initialize registers
//   "type" and "num"; the mission result lists each entry with num > 0, and
//   ResultUtility::GetRewardType(Common::Sphere211DropType) badges type 1 badge_clear.png (the
//   連続クリア streak bonus), 2 badge_boss.png, 3 badge_rareenemy.png; CSphereFloorClear reads type 4
//   as the floor-clear boxes). (d) the battle's own boxes as type 0 (no badge).
// Answers: the core MissionEnd's result keys, Sphere211TreasureDropInfoList and the dive state.
std::vector<u8> sphere211_mission_end(Ctx& ctx, const Request& req) {
    Season season = load_dive(ctx);
    u32 asset_id = 0, mission_id = 0;
    find_cell(ctx, req, asset_id, mission_id);
    Request core{"MissionEnd", kFidMissionEnd, {mission_id, 0}, {}, {}};
    Value data = ctx.core_mission(core, nullptr);
    if (data.type != Value::Map) data = ctx.base_data();
    u32 level = (u32)ctx.st.one("select floor_level from sphere where id = 1", {});
    Floor floor = floor_row(ctx, season, level);
    u32 type = (u32)LotteryType::kNormal;
    ctx.m.q("select lottery_type from master_sphere211_floor_asset where id = ?", {asset_id},
            [&](const Row& asset_row) { type = (u32)asset_row.i("lottery_type"); });
    bool boss = type == (u32)LotteryType::kBoss, rare = type == (u32)LotteryType::kRare || type == (u32)LotteryType::kRareAlt;
    ctx.st.q("update sphere set streak = streak + 1", {});
    log_event(ctx, LogKind::kWin, 1);  // the achievements (type 62) and the season's ranking entry
    set_sphere_meta(ctx, "season_wins", sphere_meta(ctx, "season_wins") + 1);
    u32 streak = (u32)ctx.st.one("select streak from sphere where id = 1", {});
    u32 streak_bonus = (u32)ctx.m.one(
        "select ifnull((select add_treasure from master_sphere211_treasure_streak_bonus where id <= ? order by id desc limit 1), 0)", {streak});
    u32 boxes = floor.treasure_num + (boss ? floor.boss_add : 0) + (rare ? floor.rare_add : 0) + streak_bonus;
    add_boxes(ctx, floor, boxes);
    ctx.st.q("update sphere_cell set cleared = case when asset_id = ? then 1 else cleared end, playing = 0, updated_at = ?", {asset_id, ctx.now()});
    Value drops = Value::array();
    auto put_drop = [&](DropType drop_type, u32 num) {
        if (!num) return;
        Value info = Value::object();
        info["type"] = (u32)drop_type;
        info["num"] = num;
        drops.push(info);
    };
    put_drop(DropType::kBattle, floor.treasure_num);
    put_drop(DropType::kStreak, streak_bonus);
    put_drop(DropType::kBoss, boss ? floor.boss_add : 0);
    put_drop(DropType::kRare, rare ? floor.rare_add : 0);
    data["Sphere211TreasureDropInfoList"] = drops;
    put_state(ctx, season, data);
    // read by port/scripts/sphere211_session.sh ("streak 4")
    LOGI("server", "Sphere211MissionEnd: floor %u cell %u mission %u cleared, streak %u, %u boxes", level, asset_id, mission_id, streak, boxes);
    return ext::body(data);
}

// ---- Sphere211MissionFailed / Sphere211MissionContinue ------------------------------------------

// Sphere211MissionFailed(u32, u32 cell) -> Sphere211MissionFailedRes          fid 172f3b5f
// API: docs/api.md#sphere211missionfailed
// Rules: docs/server-rules.md "Sphere 211"
//
// A lost or retired battle (the defeat dialog's いいえ, the pause menu's ミッションリタイア).
//   (c)+(d) the cell stays uncleared (and playable), the clear streak resets and the stamina stays
//   spent; the core MissionFailed ends the play record.
// Answers: the dive state.
std::vector<u8> sphere211_mission_failed(Ctx& ctx, const Request&) {
    Season season = load_dive(ctx);
    Request core{"MissionFailed", kFidMissionFailed, {kMissionTypeEvent, 0}, {}, {}};
    ctx.core_mission(core, nullptr);
    ctx.st.q("update sphere set streak = 0", {});
    ctx.st.q("update sphere_cell set playing = 0", {});
    // read by port/scripts/sphere211_session.sh, sphere211_continue_session.sh
    LOGI("server", "Sphere211MissionFailed: streak reset");
    return ext::body(dive_state(ctx, season));
}

// Sphere211MissionContinue(u32 +0x68, u32 +0x6c, bool) -> Sphere211MissionContinueRes   fid 5ac657b3
// API: docs/api.md#sphere211missioncontinue
// Rules: docs/server-rules.md "Sphere 211"
//
// Continue after a defeat (b: the battle's defeat dialog "紋章石100個を使用することで全員が復活
// できます" with the wallet before -> after, seen in game; the request carries the cell and 1).
//   (a) master_global continue_use_coin (100) coins, free coins first (a: core/wallet.h);
//   20000 (kCoinsShort) when short (d, the coin-short code); the battle goes on.
// Answers: the dive state and is_mission_continue.
std::vector<u8> sphere211_mission_continue(Ctx& ctx, const Request&) {
    Season season = load_dive(ctx);
    u32 cost = ctx.global_u32("continue_use_coin", 100);
    if (!wallet::spend_coins(ctx.st.h, cost)) return refuse(ctx, "Sphere211MissionContinue", "coins short", ErrorCode::kCoinsShort);
    Value data = dive_state(ctx, season);
    data["is_mission_continue"] = true;
    // read by port/scripts/sphere211_continue_session.sh ("100 coins")
    LOGI("server", "Sphere211MissionContinue: %u coins, the battle goes on", cost);
    return ext::body(data);
}

// ---- Sphere211FloorClear --------------------------------------------------------------------------

// Sphere211FloorClear(u32 goal asset id) -> Sphere211FloorClearRes            fid 5187adb1
// API: docs/api.md#sphere211floorclear
// Rules: docs/server-rules.md "Sphere 211"
//
// The goal reached (目標地点 -> 次のフロアへ -> 決定).
//   (a) the floor's clear present (master_sphere211_floor_clear_present of the season's group at
//       this level, d: the highest level row at or below it), floor_clear_treasure_num more boxes
//       (drop type 4, b: CSphereFloorClear::Setup), and the next-floor select (lot_floor_num from
//       the warp access, floors.cpp).
//   (d) the goal counts as reached when any cell next to it is cleared (the client only offers it
//       then); a missing argument names the floor's is_goal cell.
// Answers: the player state, Sphere211FloorClearResultInfo, Sphere211TreasureDropInfoList,
// StockItem (when stack items were granted) and the dive state.
std::vector<u8> sphere211_floor_clear(Ctx& ctx, const Request& req) {
    const auto args = args::Sphere211FloorClearArgs::from(req);
    Season season = load_dive(ctx);
    u32 level = (u32)ctx.st.one("select floor_level from sphere where id = 1", {});
    Floor floor = floor_row(ctx, season, level);
    Value data = ctx.base_data();
    Value items = Value::array(), stocks = Value::array(), characters = Value::array();
    Value result = Value::object();
    ctx.m.q("select * from master_sphere211_floor_clear_present where clear_present_group_id = ? and level <= ? order by level desc limit 1",
            {season.clear_present_group, level}, [&](const Row& present_row) {
                u32 type = (u32)present_row.i("content_type"), id = (u32)present_row.i("content_id"), num = (u32)present_row.i("num");
                ctx.grant(type, id, num, items, stocks, characters);
                result["clear_present_id"] = id;
                result["clear_present_content_type"] = type;
                result["clear_present_num"] = num;
            });
    data["Sphere211FloorClearResultInfo"] = result;
    add_boxes(ctx, floor, floor.floor_clear_treasure_num);
    Value drops = Value::array();
    if (floor.floor_clear_treasure_num) {
        Value info = Value::object();
        info["type"] = (u32)DropType::kFloorClear;
        info["num"] = floor.floor_clear_treasure_num;
        drops.push(info);
    }
    data["Sphere211TreasureDropInfoList"] = drops;
    u32 total = (u32)ctx.st.one("select treasure_total from sphere where id = 1", {});
    u32 goal = args.goal_asset_id;
    if (!goal)
        goal = (u32)ctx.m.one("select id from master_sphere211_floor_asset where floor_group_id = ? and is_goal = 1",
                              {ctx.st.one("select asset_group from sphere where id = 1", {})});
    ctx.st.q("update sphere set clear_asset = ?, lot_floor_num = ?", {goal ? goal : 1u, lot_floor_num(ctx, total)});
    ctx.st.q("update sphere set best_floor = max(best_floor, ?)", {level});
    if (!stocks.arr.empty()) data["StockItem"] = ctx.stock();
    put_state(ctx, season, data);
    LOGI("server", "Sphere211FloorClear(%u): floor %u cleared, %u boxes, next-floor lot %u", goal, level, floor.floor_clear_treasure_num,
         (u32)ctx.st.one("select lot_floor_num from sphere where id = 1", {}));
    return ext::body(data);
}

// ---- Sphere211UseRerollItem / Sphere211StaminaHeal -----------------------------------------------

// Sphere211UseRerollItem() -> Sphere211UseRerollItemRes                       fid 19e61236
// API: docs/api.md#sphere211usererollitem
// Rules: docs/server-rules.md "Sphere 211"
//
// The floor select's 再設定.
//   (a) the season's reroll item x reroll_item_num re-lots the next-floor count; 10206
//   (kItemCountError) when short (d).
// Answers: the dive state and StockItem.
std::vector<u8> sphere211_use_reroll_item(Ctx& ctx, const Request&) {
    Season season = load_dive(ctx);
    if (ext::stock_count(ctx, season.reroll_item) < season.reroll_num)
        return refuse(ctx, "Sphere211UseRerollItem", "no reroll item", ErrorCode::kItemCountError);
    ext::add_stock(ctx, season.reroll_item, -(int64_t)season.reroll_num);
    u32 total = (u32)ctx.st.one("select treasure_total from sphere where id = 1", {});
    u32 before = (u32)ctx.st.one("select lot_floor_num from sphere where id = 1", {});
    ctx.st.q("update sphere set lot_floor_num = ?, reroll_count = reroll_count + 1", {lot_floor_num(ctx, total)});
    Value data = dive_state(ctx, season);
    data["StockItem"] = ctx.stock();
    LOGI("server", "Sphere211UseRerollItem: next-floor lot %u -> %u", before, (u32)ctx.st.one("select lot_floor_num from sphere where id = 1", {}));
    return ext::body(data);
}

// Sphere211StaminaHeal() -> Sphere211StaminaHealRes                           fid 3a3ab3ed
// API: docs/api.md#sphere211staminaheal
// Rules: docs/server-rules.md "Sphere 211"
//
// The S stamina ＋ -> the season's ticket -> 決定.
//   (a) one of the season's heal_item_id adds its master_item heal_point (1 for every season's
//       "Sスタミナチケット", "スフィア・スタミナを1回復できるチケット"; b: the heal dialog shows 現在の
//       スタミナ 8 / 9 -> 回復後のスタミナ 9 / 9 and offers only the season's item);
//   (d) capped at the maximum (the client refuses to heal a full gauge: "スタミナは既に全回復して
//       います"); 10206 (kItemCountError) when the item is short (d). Regeneration restarts from
//       now when the gauge is full.
// Answers: the dive state and StockItem.
std::vector<u8> sphere211_stamina_heal(Ctx& ctx, const Request&) {
    Season season = load_dive(ctx);
    if (ext::stock_count(ctx, season.heal_item) < 1) return refuse(ctx, "Sphere211StaminaHeal", "no heal item", ErrorCode::kItemCountError);
    ext::add_stock(ctx, season.heal_item, -1);
    u32 point = (u32)std::max<int64_t>(1, ctx.m.one("select ifnull(heal_point, 1) from master_item where id = ?", {season.heal_item}, 1));
    u32 before = (u32)ctx.st.one("select stamina from sphere where id = 1", {}), max = stamina_max(ctx);
    u32 after = std::min(max, std::max(before, before + point));
    ctx.st.q("update sphere set stamina = ?", {after});
    if (after >= max) ctx.st.q("update sphere set stamina_at = ?", {ctx.now()});
    Value data = dive_state(ctx, season);
    data["StockItem"] = ctx.stock();
    // read by port/scripts/sphere211_continue_session.sh ("8 -> 9")
    LOGI("server", "Sphere211StaminaHeal: sphere stamina %u -> %u (item %u)", before, after, season.heal_item);
    return ext::body(data);
}

// ---- ReturnSphere211 ------------------------------------------------------------------------------

// ReturnSphere211() -> ReturnSphere211Res                                     fid 83390f3f
// API: docs/api.md#returnsphere211
// Rules: docs/server-rules.md "Sphere 211"
//
// 帰還 -> 帰還.
//   (b) every character that sortied comes back and can sortie again (master_text
//       uimsg_sphere211_return_finished; OnReturnSphere211Res clears the client's Sphere211
//       character map) and the gathered treasure data is analysed: the boxes' ranks are lotted and
//       the boxes open (rewards.cpp).
//   (b) the dialog: returning resets the clear streak bonus; (a)+(b) the EX sorties' uses come back
//       (revive_count 0).
//   (d) the dive stays on its floor; nothing is charged.
//   (b) Sphere211TreasureResultLotInfoMap {key: {lot_num}}: the box counts
//       CSphereBoxResult::Initialize reads for keys 0..4; the screen shows key 4 as S and 3 as A
//       (seen in game), so key = 4 - our rank (0 = S .. 4 = D).
// Answers: the player state, Sphere211TreasureResultLotInfoMap, Sphere211TreasureResultInfoMap,
// StockItem, Item / Character (when granted) and the dive state.
std::vector<u8> return_sphere211(Ctx& ctx, const Request&) {
    Season season = load_dive(ctx);
    Value data = ctx.base_data();
    Value items = Value::array(), stocks = Value::array(), characters = Value::array(), result = Value::object();
    u32 floor = (u32)ctx.st.one("select floor_level from sphere where id = 1", {});
    lot_ranks(ctx, season);
    Value lots = Value::object();
    for (u32 key = 0; key < 5; key++) {
        Value info = Value::object();
        info["lot_num"] = (u32)ctx.st.one("select count(*) from sphere_box where rank = ?", {4 - key});
        lots[std::to_string(key)] = info;
    }
    data["Sphere211TreasureResultLotInfoMap"] = lots;
    open_boxes(ctx, season, &items, &stocks, &characters, &result);
    u32 back = (u32)ctx.st.one("select count(*) from sphere_departed", {});
    ctx.st.exec("delete from sphere_departed");
    // (a) "※使用可能回数は帰還することで回復します" (uimsg_sphere211_mission_start_with_deity); (b)
    // CApiNotify::OnReturnSphere211Res (@014e343c) zeroes CParameterManager+0xf48 itself
    ctx.st.q("update sphere set streak = 0, revive_count = 0", {});
    data["Sphere211TreasureResultInfoMap"] = result;
    data["StockItem"] = ctx.stock();
    if (!items.arr.empty()) data["Item"] = ctx.items();
    if (!characters.arr.empty()) data["Character"] = ctx.roster();
    put_state(ctx, season, data);
    LOGI("server", "ReturnSphere211: %u characters back, floor %u", back, floor);
    return ext::body(data);
}

// ---- GetSphere211RankingInfo ---------------------------------------------------------------------

// GetSphere211RankingInfo(bool) -> GetSphere211RankingInfoRes                 fid 5943ae5c
// API: docs/api.md#getsphere211rankinginfo
// Rules: docs/server-rules.md "Sphere 211"
//
// (d) a local ranking of one player: the season's best floor, rank 1 (ranking.cpp).
// Answers: the dive state, Sphere211RankingInfoMap and Sphere211RankingTopInfoMap (the same map).
std::vector<u8> get_sphere211_ranking_info(Ctx& ctx, const Request&) {
    Season season = load_dive(ctx);
    Value data = dive_state(ctx, season);
    Value ranking = ranking_info_map(ctx, season);
    data["Sphere211RankingInfoMap"] = ranking;
    data["Sphere211RankingTopInfoMap"] = ranking;
    return ext::body(data);
}

// ---- Sphere211AutoMemberSelect / Sphere211EquipAuto ----------------------------------------------

// Sphere211AutoMemberSelect(u32, u32 cell, u32) -> Sphere211AutoMemberSelectRes   fid 2d0a3ab3
// API: docs/api.md#sphere211automemberselect
// Rules: docs/server-rules.md "Sphere 211"
//
// 自動編成 on the party screen ((b) the request as the client sends it is (1, the cell's asset id,
// 0); the response key Sphere211AutoMemberSelectResultInfo is an InfoBaseValueArray<u64> (its
// typeinfo sits with that template's, like DeepSpace's AutoSelectedResult): the proposed party's
// uids).
//   (d) the 4 strongest characters that haven't sortied in this dive: by level, then rarity
//   (master_role.rarity), limit break, uid; slot 4 is the rental slot, which the menu fills from the
//   player's own characters too (b, Sphere211MissionStart).
// Answers: the dive state and Sphere211AutoMemberSelectResultInfo.
std::vector<u8> sphere211_auto_member_select(Ctx& ctx, const Request&) {
    Season season = load_dive(ctx);
    Value data = dive_state(ctx, season);
    std::vector<std::tuple<int64_t, int64_t, int64_t, u64>> ranked;  // -level, -rarity, -limit break, uid
    ctx.st.q("select uid, role_id, level, limit_break from roster where uid not in (select uid from sphere_departed)", {},
             [&](const Row& roster_row) {
                 int64_t rarity = ctx.m.one("select rarity from master_role where id = ?", {roster_row.i("role_id")});
                 ranked.emplace_back(-roster_row.i("level"), -rarity, -roster_row.i("limit_break"), (u64)roster_row.i("uid"));
             });
    std::sort(ranked.begin(), ranked.end());
    Value selected = Value::array();
    for (size_t k = 0; k < ranked.size() && k < kAutoMembers; k++) selected.push(std::get<3>(ranked[k]));
    LOGI("server", "Sphere211AutoMemberSelect: %zu members proposed", selected.arr.size());
    data["Sphere211AutoMemberSelectResultInfo"] = selected;
    return ext::body(data);
}

// Sphere211EquipAuto(u32, u32, vector<u64>) -> Sphere211EquipAutoRes          fid 9ce7e42e
// API: docs/api.md#sphere211equipauto
// Rules: docs/server-rules.md "Sphere 211"
//
// 自動設定: (d) answered with the state; the client keeps its own equipment.
// Answers: the dive state.
std::vector<u8> sphere211_equip_auto(Ctx& ctx, const Request&) {
    Season season = load_dive(ctx);
    return ext::body(dive_state(ctx, season));
}

// ---- the player load ------------------------------------------------------------------------------

// OnPlayerLoad: FooterMissionInfo.is_open_extra_dungeon, Sphere211CurrentId, the rental bonus
//                                                          on Login, SimpleLogin, CreatePlayer, GetPlayer, NoLoginStart
// Rules: docs/server-rules.md "Sphere 211"
//
//   (b) every full player load opens the extra dungeon: FooterMissionInfo.is_open_extra_dungeon
//       sets CParameterManager+0x1a38 (CParameterUtility::IsOpenExtraDungeon; the Sphere 211 menu
//       also needs no "sphere211" entry in the maintenance map), (c) open in 3.7.0.
//   (b) the extra-dungeon menu (MissionUtility::tPartInfo for type 5) shows Sphere 211 as out of
//       its period until Sphere211CurrentId (CParameterManager+0xaff0) names the running season:
//       sent with the player too.
//   (a)+(b)+(d) the Sphere 211 rental bonus of the earlier days (rental.cpp rental_bonus).
// Adds: FooterMissionInfo.is_open_extra_dungeon, Sphere211CurrentId; Sphere211RentalBonus,
// Sphere211RentalCount and PresentBoxCount on the day a bonus is paid.
void load_sphere211(Ctx& ctx, const Request&, Value& data) {
    data["FooterMissionInfo"]["is_open_extra_dungeon"] = true;
    data["Sphere211CurrentId"] = current_season(ctx).id;
    rental_bonus(ctx, data);
}

// ---- state ----------------------------------------------------------------------------------------
// (d) our layout: one dive per player; the cells of the current floor; the characters that
// sortied on this floor; the boxes gathered in this dive; the local ranking's best floors.
const char* const kSchemaSphere = R"(
create table if not exists sphere (id integer primary key check (id = 1), season_id integer, floor_level integer default 0,
  asset_group integer default 0, streak integer default 0, treasure_total integer default 0, stamina integer, stamina_at integer,
  revive_count integer default 0, best_floor integer default 0, entered_at integer, clear_asset integer default 0,
  lot_floor_num integer default 0, reroll_count integer default 0, prev_season integer default 0, prev_floor integer default 0,
  prev_treasure integer default 0, prev_rank integer default 0);
create table if not exists sphere_cell (asset_id integer primary key, floor_level integer, mission_box_id integer, mission_id integer,
  overwrite_enemy_level integer default 0, cleared integer default 0, playing integer default 0, created_at integer, updated_at integer);
create table if not exists sphere_departed (uid integer primary key);
create table if not exists sphere_box (id integer primary key autoincrement, floor_level integer, rank integer);
create table if not exists sphere_rank (season_id integer primary key, floor_level integer, entered_at integer);
)";
// (d) For the rental slot, the Sphere 211 rental bonus, the achievements and the season end: small
// keyed values (sphere_meta: the season's cycle, its battles won, whether the season-end result is
// still to be shown); the rental slot's lenders of the current floor and whether each was rented;
// the Sphere 211 rentals per rental day; a log of battles won (kind 1) and floors entered (kind 2,
// value = the floor) on the server clock, for the achievements.
const char* const kSchemaSphereExtra = R"(
create table if not exists sphere_meta (key text primary key, value integer);
create table if not exists sphere_rental (follow_player_id integer primary key, used integer default 0, updated_at integer);
create table if not exists sphere_rental_day (day integer primary key, season_id integer, count integer default 0, paid integer default 0);
create table if not exists sphere_log (id integer primary key autoincrement, kind integer, value integer, at integer);
)";

}  // namespace
}  // namespace sphere211

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_sphere211() {
    using namespace sphere211;
    ext::add_schema(kSchemaSphere);
    ext::add_schema(kSchemaSphereExtra);
    ext::add_client_master(client_seasons);
    ext::add_client_master(client_ranking_groups);
    ext::add_api({"GetSphere211Info"}, get_sphere211_info);
    ext::add_api({"Sphere211SelectedFloor"}, sphere211_selected_floor);
    ext::add_api({"Sphere211MissionStart"}, sphere211_mission_start);
    ext::add_api({"Sphere211MissionEnd"}, sphere211_mission_end);
    ext::add_api({"Sphere211MissionFailed"}, sphere211_mission_failed);
    ext::add_api({"Sphere211MissionContinue"}, sphere211_mission_continue);
    ext::add_api({"Sphere211FloorClear"}, sphere211_floor_clear);
    ext::add_api({"Sphere211UseRerollItem"}, sphere211_use_reroll_item);
    ext::add_api({"Sphere211StaminaHeal"}, sphere211_stamina_heal);
    ext::add_api({"ReturnSphere211"}, return_sphere211);
    ext::add_api({"GetSphere211RankingInfo"}, get_sphere211_ranking_info);
    ext::add_api({"Sphere211AutoMemberSelect"}, sphere211_auto_member_select);
    ext::add_api({"Sphere211EquipAuto"}, sphere211_equip_auto);
    ext::add_player_load(load_sphere211);
}

}  // namespace soa::server
