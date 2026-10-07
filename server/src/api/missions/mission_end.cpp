// MissionEnd: EXP, favor, drops, first-clear presents and unlocks (api/missions/missions.h). Port
// code, not guest behaviour.
// Every rule carries its source label, (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption (docs/server-rules.md#server-missions).
#include "api/missions/missions.h"

#include <algorithm>
#include <tuple>

#include "api/favor/favor.h"
#include "api/player/player_info.h"  // base_data, stack_item_info_list
#include "core/log.h"
#include "core/request_args.h"

namespace soa::server {

using ext::body;
using ext::Row;

namespace {

// The content types a first-clear present can be (master_mission_clear_present.content_type; a:
// docs/api.md "Content types").
constexpr u32 kContentItem = 1, kContentCharacter = 2, kContentFol = 3, kContentFreeCoin = 4;

// A MissionEnd in progress: the play it ends and what each step granted, in the order the steps
// run (mission_end below).
struct MissionEnd {
    u32 mission = 0;
    std::vector<PlayMember> party;  // the play's party (play_member)
    u32 play_stamina_cost = 0;
    bool surprise = false;
    MissionRef mission_ref;
    double favor_rate = 1.0;
    u32 player_exp = 0, character_exp = 0, fol = 0;  // the mission's player EXP, EXP per member, FOL
    u32 level_before = 0, level_after = 0;           // the player's
    Value result_characters, result_favor;           // MissionResultCharacter, MissionResultCharacterFavor
    Value added_items, added_stocks, added_characters;  // what the drops added (AddItem, StockItem, AddCharacter)
    Rolled rolled;
    bool first_clear = false;
    std::vector<std::string> unlocked;  // the id_labels of the missions it unlocked
    Value present_items, present_characters, present_stocks;  // ClearPresentList
    u32 present_free_coins = 0;
    u32 mission_time = 0;  // the battle log's mission_time
};

// 1. The play this ends: the mission, its party, its stamina and surprise roll. False when the
// request names no mission the master knows (below): MissionEnd isn't answered.
bool read_play(ext::Ctx& ctx, const Request& req, MissionEnd& end) {
    // MissionEnd(u32 mission (+0x54), u32 (+0x5c)); the party and mission come from the
    // MissionStart this ends.
    end.mission = args::MissionEndArgs::from(req).mission;
    // (d) without a play in progress (none started, or MissionFailed ended it) the mission type is
    // 0 (find_mission tries every table), no surprise enemy, no party: until PLAN-schema S7 the
    // last start's type and surprise roll were read (MissionFailed left them behind).
    u32 played = 0, played_type = 0;
    ctx.st.q("select mission_id, mission_type, stamina_cost, surprise from play where id = 1", {}, [&](const Row& play_row) {
        played = (u32)play_row.i("mission_id");
        played_type = (u32)play_row.i("mission_type");
        end.play_stamina_cost = (u32)play_row.i("stamina_cost");
        end.surprise = play_row.i("surprise") != 0;
    });
    end.party = play_members(ctx);
    if (!end.mission) end.mission = played;
    end.mission_ref = find_mission(ctx, played_type, end.mission);
    // An id that is 0 (no argument and no play) or in none of the mission tables isn't a mission
    // to end: (d) not answered, nothing granted or recorded, as MissionStart doesn't answer an
    // unknown mission. Until 2026-10-03 it was recorded as cleared (mission 0 from the api-sweep
    // replay corpus, found by S0). Why not a refusal: (b) the client has no MissionEnd row in its
    // error-kind table (CErrorHandlerWrap::ErrKind, Ghidra 0x2cc5b70), and its handling table
    // (ELF 0x2714360, read by CErrorHandlerWrap::HndlType) gives MissionEnd type 0 where
    // MissionStart has 2 (back to the title) and the other APIs 1 (give up); (d) type 0 is read as
    // the resend, which a refusal would repeat. What the online server answered isn't known.
    if (!end.mission || !end.mission_ref.found) {
        LOGW("server", "MissionEnd: unknown mission %u (type %u), not answered", end.mission, played_type);
        return false;
    }
    return true;
}

// 2. The mission's rewards: player EXP, EXP per member, FOL, the favor campaigns.
void mission_rewards(ext::Ctx& ctx, MissionEnd& end) {
    // (a)+(b) type-8 campaigns (友好, labels *_yuukou_*, magnification 1.5, one event area each):
    // MissionUtility::UpdateEventAreaListCampaign shows them on the event area only while favor
    // battles are open (IsOpenFavorabilityBattle) and the client multiplies nothing itself, so
    // they multiply the battle favor the server grants (d: favor is what "友好" multiplies, the
    // client shows no other effect)
    if (end.mission_ref.found)
        for (const Campaign& campaign : campaigns_for(ctx, end.mission_ref))
            if (campaign.type == CampaignType::kFavor && campaign.magnification > 0) end.favor_rate *= campaign.magnification;
    ctx.m.q("select exp, pc_exp, fol from " + end.mission_ref.table + " where id = ?", {end.mission}, [&](const Row& mission_row) {
        end.player_exp = (u32)mission_row.i("exp");        // (a) master_mission.exp: player EXP
        end.character_exp = (u32)mission_row.i("pc_exp");  // (a) master_mission.pc_exp: EXP per party member
        end.fol = (u32)mission_row.i("fol");               // (a) master_mission.fol
    });
}

// 3. The player's EXP, level-up and FOL.
void player_exp(ext::Ctx& ctx, MissionEnd& end) {
    // Player EXP and level-up; (d) stamina refills to the new maximum on a level-up.
    u32 exp_before = 0;
    ctx.st.q("select level, exp from player", {}, [&](const Row& player_row) {
        end.level_before = (u32)player_row.i("level");
        exp_before = (u32)player_row.i("exp");
    });
    auto next_exp = ctx.player_next();
    u32 exp_after = 0;
    std::tie(end.level_after, exp_after) = rules::add_exp(end.level_before, exp_before, end.player_exp, next_exp, ctx.player_level_max());
    ctx.st.q("update player set level = ?, exp = ?, fol = min(fol + ?, ?) where 1",
             {end.level_after, exp_after, end.fol, ctx.global_u32("item_fol_max_num", 4200000000u)});
    if (end.level_after > end.level_before) {  // (c) a rank-up adds the new maximum to the current stamina (スタミナが加算されます)
        tick_stamina(ctx);
        ctx.st.q("update player set stamina = stamina + ?, stamina_at = ?", {ctx.stamina_max(end.level_after), ctx.now()});
    }
}

// 4. The party's EXP and battle favor.
void characters_exp_and_favor(ext::Ctx& ctx, MissionEnd& end) {
    end.result_characters = Value::object();
    end.result_favor = Value::object();
    for (const PlayMember& member : end.party) {
        if (!member.uid) continue;  // a mission NPC (or a character gone): no EXP, no favor
        const CharacterUid uid = *member.uid;
        ctx.st.q("select * from roster where uid = ?", {uid}, [&](const Row& roster_row) {
            const RoleId role = roster_row.id<RoleId>("role_id");
            u32 level_before = (u32)roster_row.i("level"), exp_before = (u32)roster_row.i("exp");
            auto next_exp = ctx.role_next(role);
            auto [level_after, exp_after] = rules::add_exp(level_before, exp_before, end.character_exp, next_exp, ctx.role_level_cap(role));
            ctx.st.q("update roster set level = ?, exp = ? where uid = ?", {level_after, exp_after, uid});
            Value result = Value::object();
            result["id"] = uid.v;
            result["before_level"] = level_before;
            result["before_exp"] = exp_before;
            result["after_level"] = level_after;
            result["after_exp"] = exp_after;
            end.result_characters[std::to_string(uid.v)] = result;
            // Favor per same_role_id: server/src/api/favor/favor.cpp (master_favor_battle_effect).
            const SameRoleId same_role_id = ctx.m.one_id<SameRoleId>("select same_role_id from master_role where id = ?", {role});
            if (!end.result_favor.find(std::to_string(same_role_id.v))) {
                Value favor = favor::mission_gain(ctx.st.h, ctx.m.h, ctx.now(), same_role_id, end.play_stamina_cost, end.favor_rate);
                if (favor.type == Value::Map) end.result_favor[std::to_string(same_role_id.v)] = favor;
            }
        });
    }
}

// 5. The drop roll, granted.
void roll_and_grant_drops(ext::Ctx& ctx, MissionEnd& end) {
    end.added_items = Value::array();
    end.added_stocks = Value::array();
    end.added_characters = Value::array();
    // the party's roles, in roster order (the character bonus counts them, not their order)
    std::vector<u32> roles;
    ctx.st.q("select r.role_id from roster r where r.uid in (select uid from play_member) order by r.uid", {},
             [&](const Row& roster_row) { roles.push_back((u32)roster_row.i("role_id")); });
    const MissionRef& ref = end.mission_ref;
    end.rolled = roll_drops(ctx, end.mission, ref.table, ref.type, ref.area, end.surprise, roles);
    for (const Drop& drop : end.rolled.drops) grant(ctx, drop, end.added_items, end.added_stocks, end.added_characters);
}

// 6. The first clear and the missions it unlocks.
void unlocks(ext::Ctx& ctx, MissionEnd& end) {
    end.first_clear = ctx.st.one("select cleared from mission where mission_id = ?", {end.mission}) == 0;
    // Unlocks (a): on the first clear, the missions of the same table whose unlock_mission_id
    // is this one open (the menus list them through ActiveMissionList, which the story campaign,
    // api/campaign/, builds from the same rule); recorded in the unlocks table.
    if (!end.first_clear) return;
    ctx.m.q("select id, id_label from " + end.mission_ref.table + " where unlock_mission_id = ? order by id", {end.mission},
            [&](const Row& unlocked_row) {
                ctx.st.q("insert or ignore into unlocks (mission_id, mission_type, by_mission, at) values (?,?,?,?)",
                         {unlocked_row.i("id"), end.mission_ref.type, end.mission, ctx.now()});
                end.unlocked.push_back(unlocked_row.s("id_label"));
            });
}

// 7. The first clear's presents.
void clear_presents(ext::Ctx& ctx, MissionEnd& end) {
    // (a) master_mission_clear_present rows go to the present box on the first clear (d: first
    // clear only), and (b) are listed in ClearPresentList, which the result screen shows as
    // "first clear" rewards when an entry matches a clear-present row of the mission
    // (ResultUtility::GetRewardItemList: free_coin as content 4; item / character /
    // stock_item entries by their first property, the content id).
    end.present_items = Value::array();
    end.present_characters = Value::array();
    end.present_stocks = Value::array();
    if (!end.first_clear) return;
    ctx.m.q("select * from master_mission_clear_present where master_mission_id = ? order by order_id", {end.mission}, [&](const Row& present_row) {
        ctx.st.q("insert into presents (content_type, content_id, num, reason_type, reason_param, created_at) values (?,?,?,?,?,?)",
                 {present_row.i("content_type"), ext::present_content_id((u32)present_row.i("content_type"), (u32)present_row.i("content_id")),
                  present_row.i("num"), (int)ext::kPresentMissionClear /* (d) the reason */, end.mission, ctx.now()});
        u32 content_type = (u32)present_row.i("content_type"), content_id = (u32)present_row.i("content_id"), num = (u32)present_row.i("num");
        Value entry = Value::object();
        entry["id"] = content_id;
        entry["content_type"] = content_type;
        entry["drop_type"] = 0u;
        if (content_type == kContentFreeCoin) end.present_free_coins += num;
        else if (content_type == kContentItem) end.present_items.push(entry);
        else if (content_type == kContentCharacter) end.present_characters.push(entry);
        else if (content_type != kContentFol) {
            entry["use_count"] = num;
            entry["num"] = num;
            end.present_stocks.push(entry);
        }
    });
}

// 8. The clear record; the play ends.
void record_clear(ext::Ctx& ctx, MissionEnd& end) {
    ctx.st.q("insert into mission (mission_id) values (?) on conflict(mission_id) do nothing", {end.mission});
    ctx.st.q("update mission set cleared = 1, clear_count = clear_count + 1, first_clear_at = ifnull(first_clear_at, ?) where mission_id = ?",
             {ctx.now(), end.mission});
    ctx.st.q("delete from play", {});  // and its members (ON DELETE CASCADE)
}

// (b) BattleEvaluationResultInfoList: one CBattleEvaluationResultInfo {master_battle_evaluation_id}
// per evaluation reached.
Value evaluation_result_list(const Rolled& rolled) {
    Value list = Value::array();
    for (u32 id : rolled.evaluations) {
        Value entry = Value::object();
        entry["master_battle_evaluation_id"] = id;
        list.push(entry);
    }
    return list;
}

// DropList (CMissionResultDropInfo): the FOL and the drops.
Value drop_list_info(const MissionEnd& end) {
    Value drop_list = Value::object();
    drop_list["fol"] = end.fol;
    drop_list["free_coin"] = 0u;
    drop_list["up_fol_rate"] = 0u;
    // (b) ResultUtility::PushToItemList<CMissionResultDropInfo> shows each drop by the
    // element's first property (`id`) as the content id (master item / role), its
    // content_type and drop_type; the owned uids go in AddItem / AddCharacter instead.
    Value shown_items = Value::array(), shown_characters = Value::array();
    for (const Value& item : end.added_items.arr) {
        Value shown = item;
        shown["id"] = item.get_u("master_item_id");
        shown_items.push(shown);
    }
    for (const Value& character : end.added_characters.arr) {
        Value shown = character;
        shown["id"] = character.get_u("master_role_id");
        shown["content_type"] = kContentCharacter;
        shown_characters.push(shown);
    }
    drop_list["item"] = shown_items;
    drop_list["character"] = shown_characters;
    drop_list["stock_item"] = end.added_stocks;
    return drop_list;
}

// ClearPresentList (CMissionResultDropInfo): the first clear's presents.
Value clear_present_list_info(const MissionEnd& end) {
    Value present_list = Value::object();
    present_list["fol"] = 0u;
    present_list["free_coin"] = end.present_free_coins;
    present_list["up_fol_rate"] = 0u;
    present_list["item"] = end.present_items;
    present_list["character"] = end.present_characters;
    present_list["stock_item"] = end.present_stocks;
    return present_list;
}

// 9. The answer's data: the player state, evaluations, MissionEndResult, Achievement, DropList,
// ClearPresentList, the added items and characters, the EXP and favor results.
Value mission_end_data(ext::Ctx& ctx, MissionEnd& end) {
    Value data = base_data(ctx);
    if (!end.rolled.evaluations.empty()) data["BattleEvaluationResultInfoList"] = evaluation_result_list(end.rolled);
    Value end_result = Value::object();
    // (b) the battle log's mission_time (ms: the result screen prints it as %d:%02d.%02d)
    end.mission_time = ctx.live() ? battle_log_u32(ctx, "mission_time", 0) : 0;
    end_result["mission_time"] = end.mission_time;
    data["MissionEndResult"] = end_result;
    // (b) the favor achievements follow the battle favor (ext::achievement_state)
    data["Achievement"] = ext::achievement_state(ctx);
    data["DropList"] = drop_list_info(end);
    if (end.first_clear) data["ClearPresentList"] = clear_present_list_info(end);
    ext::add_items(data, end.added_items);
    if (!end.added_stocks.arr.empty()) data["StockItem"] = stack_item_info_list(ctx);
    if (!end.added_characters.arr.empty()) {
        Value add_character = Value::object();
        for (auto& character : end.added_characters.arr) add_character[std::to_string(character.get_u("id"))] = character;
        data["AddCharacter"] = add_character;
    }
    data["MissionResultCharacter"] = end.result_characters;
    data["MissionResultCharacterFavor"] = end.result_favor;
    data["PresentBoxCount"] = (u32)ctx.st.one("select count(*) from presents where received_at is null", {});
    return data;
}

// 10. The log lines (read by the session scripts) and the battle log's party stats.
void log_mission_end(ext::Ctx& ctx, const MissionEnd& end) {
    const u32 mission = end.mission;
    const Rolled& rolled = end.rolled;
    // read by battle_session.sh, rental_session.sh
    LOGI("server", "MissionEnd mission %u: player exp +%u (level %u -> %u), fol +%u, %zu items, %zu stack drops%s, time %u ms, favor for %zu",
         mission, end.player_exp, end.level_before, end.level_after, end.fol, end.added_items.arr.size(), end.added_stocks.arr.size(),
         end.first_clear ? ", first clear" : "", end.mission_time, end.result_favor.map.size());
    // read by restore_missions.sh
    LOGI(
        "server",
        "MissionEnd mission %u drops: surprise %s (%u lots), campaign +%u lots, character bonus +%u lots +%u extra, evaluation %zu reached (%u lots)",
        mission, end.surprise ? "yes" : "no", rolled.surprise_lots, rolled.campaign_lots, rolled.bonus_lots, rolled.bonus_extra,
        rolled.evaluations.size(), rolled.eval_lots);
    for (auto& label : end.unlocked) LOGI("server", "MissionEnd mission %u: unlocked %s", mission, label.c_str());  // read by restore_missions.sh
    // (b) the stats the client battled with: its battle log's PlayerCharacter list (the
    // CPersonStatusInfo of each party member; docs/ason.md "Battle log"). Logged only, for the
    // session checks (tools/compare_tutorial.py port_party) to compare with what MissionStart sent.
    if (const Value* logged = current_log(ctx).root().find("PlayerCharacter"); logged && logged->type == Value::Arr) {
        auto num = [](const Value& member, const char* key) {
            const Value* v = member.find(key);
            return !v ? 0.0 : v->type == Value::Float ? v->f : v->type == Value::Int ? (double)v->i : v->type == Value::UInt ? (double)v->u : 0.0;
        };
        for (size_t k = 0; k < logged->arr.size(); k++) {
            const Value& member = logged->arr[k];
            if (member.type != Value::Map) continue;
            LOGI("server", "MissionEnd mission %u battle log PlayerCharacter %zu: [hp %g atk %g int %g def %g hit %g grd %g]", mission, k,
                 num(member, "hp"), num(member, "attack"), num(member, "intelligence"), num(member, "defence"), num(member, "hit"),
                 num(member, "guard"));
        }
    }
}

// 11. The modules' additions (ext::MissionResultExtra).
void mission_result_extras(ext::Ctx& ctx, const MissionEnd& end, Value& data) {
    ext::MissionInfo info = mission_info(ctx, end.mission_ref, end.mission, battle_uids(end.party));
    info.mission_time = end.mission_time;
    info.log_u32 = [&ctx](const char* name) { return ctx.live() ? battle_log_u32(ctx, name, 0) : (u32)ctx.request->test_log_value; };
    info.evaluation = [&ctx](int type) -> int64_t { return ctx.live() ? battle_evaluation_value(ctx, type) : (int64_t)ctx.request->test_log_value; };
    ext::mission_result_extra(ctx, info, data);
}

}  // namespace

// MissionEnd(u32 mission_id, u32) + the battle log -> MissionEndRes                     fid 8312a64c
// API: docs/api.md#missionend   Rules: docs/server-rules.md#mission-end, docs/server-rules.md#mission-end-drops, docs/server-rules.md#type-8-campaigns
//
// Ends a won battle (a loss sends MissionFailed): grants its rewards and ends the play record.
//   (a) the mission's exp, pc_exp (each party member) and fol (capped at master_global
//       item_fol_max_num); (c) a rank-up adds the new stamina maximum;
//   (a) the battle favor per same_role_id (master_favor_battle_effect by the play's stamina),
//       x a running type-8 campaign (d: favor is what it multiplies);
//   (a)+(d) the drop roll (drops.cpp: lots, surprise, campaigns, character bonus, evaluation);
//   (a) the first clear's master_mission_clear_present rows to the present box (d: first clear
//       only) and the missions whose unlock_mission_id is this one, recorded in `unlocks`;
//   (b) the mission is the request's, else the play's; the party is the play's.
//   (d) a mission id that is 0 or in no mission table isn't answered (read_play).
// Answers: the player state with MissionEndResult (the battle log's mission_time), Achievement,
// DropList, ClearPresentList (first clear), BattleEvaluationResultInfoList (evaluations reached),
// AddItem / StockItem / AddCharacter, MissionResultCharacter(Favor), PresentBoxCount, and the
// modules' MissionResultExtra additions.
std::vector<u8> mission_end(ext::Ctx& ctx, const Request& req) {
    MissionEnd end;
    if (!read_play(ctx, req, end)) return {};
    mission_rewards(ctx, end);
    player_exp(ctx, end);
    characters_exp_and_favor(ctx, end);
    roll_and_grant_drops(ctx, end);
    unlocks(ctx, end);
    clear_presents(ctx, end);
    record_clear(ctx, end);
    Value data = mission_end_data(ctx, end);
    log_mission_end(ctx, end);
    mission_result_extras(ctx, end, data);
    return body(data);
}

// MissionEnd (src/core/modules.cpp: the core's APIs first).
void register_mission_end() { ext::add_core_api({"MissionEnd"}, mission_end); }

}  // namespace soa::server
