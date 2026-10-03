// MissionStart: the cost, the surprise roll, the stages and the battle party (api/missions/missions.h).
// Port code, not guest behaviour.
// Every rule carries its source label, (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption (docs/server-rules.md "Server missions").
#include "api/missions/missions.h"

#include <algorithm>

#include "api/player/party_set.h"      // party_member_uids
#include "api/player/person_status.h"  // person_status_info
#include "api/player/player_info.h"    // base_data, stack_item_info_list
#include "api/social/rental.h"       // rental helper ids
#include "core/errors.h"
#include "core/log.h"
#include "core/request_args.h"
#include "core/response.h"
#include "core/time.h"  // day_start
#include "core/server.h"  // one_null_as_zero
#include "rules/mission_rules.h"
#include "soaserver/chash32.h"
#include "soaserver/config.h"
#include "soaserver/npc_status.h"

namespace soa::server {

using ext::body;
using ext::Row;

namespace {

// (d) the uids the mission NPCs fight under while a temp table shadows `roster`: kNpcPartyUid0 + 1
// + their order (the tutorial's NPC party), kNpcPartyUid0 + 1 for an event mission's NPC helper.
constexpr u64 kNpcPartyUid0 = 0x7f000000;

// A mission NPC (master_mission_npc row): its role and level, and its two ids.
struct MissionNpc {
    u32 role_id, level;
    u32 mission_npc_id, npc_id;  // master_mission_npc id, master_npc id (= master_npc_base_parameter id)
};

// A MissionStart in progress: its arguments and what each step decided, in the order the steps
// run (start_mission below).
struct MissionStart {
    const ext::MissionOverride* module_override = nullptr;  // a module's changes (ext::Ctx::core_mission)
    bool restarting = false;                                // MissionRestart: no stamina, no new play count
    args::MissionStartArgs args;                            // with a module's own helper applied
    MissionRef mission_ref;
    Value mission_parameter;  // MissionParameter
    // 2. the cost
    u32 stamina_cost = 0;
    u32 ticket_item_id = 0, ticket_num = 0, vanish_item_id = 0, vanish_num = 0;
    bool surprise_possible = false;
    double surprise_rate = 0;
    u32 campaign_lots = 0;
    // 3-6. the checks, the roll, the payment
    u32 stamina_before = 0;
    bool surprise = false;
    u32 stamina_paid = 0;
    // 7-10. the battle party
    u32 party_id = 0;
    std::vector<u64> party_uids;
    Value player_characters;          // BattleParameter.PlayerCharacter
    std::string play_uids;            // the party as the play record keeps it ("uid,uid,")
    std::vector<MissionNpc> npcs;     // the mission's NPCs that fight (the tutorial's NPC party)
    std::vector<MissionNpc> all_npcs;  // every master_mission_npc row of the mission, in order
    u32 event_npc = 0;                // the picked NPC helper: its index + 1 in all_npcs (0: none)
    Value event_npc_status;
    u64 helper_uid = 0;
    HelperKind helper_kind = HelperKind::kNone;
};

// A mission NPC's battle status from the master data, as the client's NPC model computes it
// (soaserver/npc_status.h).
bool npc_master_status(ext::Ctx& ctx, u32 mission_npc_id, Value& status) { return rules::npc_status(ctx.m.h, mission_npc_id, status); }

// 1. The arguments and the mission's master row (false: an unknown mission, not answered).
bool resolve_mission(ext::Ctx& ctx, const Request& req, MissionStart& start) {
    // MissionStart(u32 type, u32 mission, u32 helper index + 1, u64 own helper uid, u32 NPC
    // helper id, u64 rental uid, u32) (b: CStageManager::CallMissionStart; docs/api.md)
    start.args = args::MissionStartArgs::from(req);
    if (start.module_override && start.module_override->helper) {  // a module's 4th member: the own-helper path
        start.args.helper_index_plus_1 = 1;
        start.args.own_helper_uid = start.module_override->helper;
    }
    start.mission_ref = find_mission(ctx, start.args.type, start.args.mission);
    if (!start.mission_ref.found) {
        LOGW("server", "MissionStart: unknown mission %u (type %u)", start.args.mission, start.args.type);
        return false;
    }
    return true;
}

// 2. The cost: stamina, ticket and vanish item from the master row, the campaigns, a module's
// changes.
void read_cost(ext::Ctx& ctx, MissionStart& start) {
    const u32 mission = start.args.mission;
    Value& parameter = start.mission_parameter;
    parameter = Value::object();
    ctx.m.q("select * from " + start.mission_ref.table + " where id = ?", {mission}, [&](const Row& mission_row) {
        start.stamina_cost = (u32)mission_row.i("use_stamina");  // (a) use_stamina
        start.ticket_item_id = (u32)mission_row.i("ticket_item_id");  // (a) ticket_item_id x ticket_num
        start.ticket_num = (u32)std::max<int64_t>(1, mission_row.i("ticket_num"));
        start.vanish_item_id = (u32)mission_row.i("vanish_item_id");  // (a) vanish_item_id x vanish_num; (d) consumed at start
        start.vanish_num = (u32)std::max<int64_t>(1, mission_row.i("vanish_num"));
        start.surprise_possible = mission_row.i("is_surprise_enemy") != 0;  // (a)
        // (a) surprise_rate; (d) master_global surprise_rate when the row has none
        start.surprise_rate = mission_row.null("surprise_rate") ? (double)ctx.global_u32("surprise_rate", 10) : mission_row.f("surprise_rate");
        parameter["master_mission_id"] = mission;
        parameter["master_mission_id_label"] = mission_row.s("id_label");
        parameter["multi_player_count"] = 1u;
        parameter["is_event_drop_by_favor"] = false;
        parameter["overwrite_enemy_level"] = 0u;
        parameter["add_enemy_level"] = 0u;
    });
    // (a)+(b) stamina campaigns (type 1, magnification 0.5) for the mission's type and area
    // (CUIUtility::IsDecConsumeStamina); (a) type 0 campaigns add lot_drop_count_add lots.
    for (const Campaign& campaign : campaigns_for(ctx, start.mission_ref)) {
        if (campaign.type == CampaignType::kStamina) start.stamina_cost = mission_rules::campaign_stamina(start.stamina_cost, campaign.magnification);
        if (campaign.type == CampaignType::kDropLots) start.campaign_lots += campaign.extra_lots;
    }
    // Extension modules (ext::MissionOverride, e.g. Sphere 211's own stamina): no AP cost,
    // ticket or vanish item; the module's enemy level.
    if (const ext::MissionOverride* module = start.module_override) {
        if (module->free_stamina) start.stamina_cost = start.ticket_item_id = start.vanish_item_id = 0;
        parameter["overwrite_enemy_level"] = module->overwrite_enemy_level;
        parameter["add_enemy_level"] = module->add_enemy_level;
    }
    parameter["stamina_cost"] = start.stamina_cost;
}

// 3. The checks: a refusal's answer, or empty when the start can go on.
std::vector<u8> check_cost(ext::Ctx& ctx, const Request& req, MissionStart& start) {
    // Checks (a: master_text error_message_text_<code>): stamina short -> 10004
    // (スタミナが不足しています); ticket or vanish item short -> 10206 (アイテムの所持数エラー, d: the code).
    tick_stamina(ctx);
    start.stamina_before = (u32)ctx.st.one("select stamina from player", {});
    if (start.restarting) return {};
    if (start.stamina_before < start.stamina_cost) {
        return ext::refusef(ctx, req.method.c_str(), ErrorCode::kStaminaShort, "stamina %u < cost %u", start.stamina_before, start.stamina_cost);
    }
    if ((start.ticket_item_id && stock_count(ctx, start.ticket_item_id) < start.ticket_num) ||
        (start.vanish_item_id && stock_count(ctx, start.vanish_item_id) < start.vanish_num)) {
        return ext::refuse(ctx, req.method.c_str(), "ticket / vanish item short", ErrorCode::kItemCountError);
    }
    return {};
}

// 4. The surprise enemy roll.
void roll_surprise(ext::Ctx& ctx, MissionStart& start) {
    // (d) a restart (MissionRestart) replays the stored surprise roll
    if (start.restarting) start.surprise = ctx.st.one("select surprise from play_ext where id = 1", {}) != 0;
    else if (start.surprise_possible) start.surprise = mission_rules::roll_percent(start.surprise_rate, (*ctx.rng)());
    // SOA_SERVER_SURPRISE=1 (port test option): a mission with a surprise enemy always meets it
    if (!start.restarting && start.surprise_possible && config().surprise) start.surprise = true;
    start.mission_parameter["is_surprise"] = start.surprise;
}

// 5. The stages (CMissionStageInfo list) of the mission.
Value stage_list(ext::Ctx& ctx, u32 mission) {
    Value stages = Value::array();
    ctx.m.q("select * from master_mission_stage where master_mission_id = ? order by order_id", {mission}, [&](const Row& stage_row) {
        Value stage = Value::object();
        stage["id"] = (u32)stage_row.i("id");
        stage["id_label"] = stage_row.s("id_label");
        stage["order_id"] = (u32)stage_row.i("order_id");
        stage["is_boss"] = stage_row.i("is_boss") != 0;
        stage["serial_number"] = (u32)stage_row.i("serial_number");
        stage["master_mission_id"] = (u32)stage_row.i("master_mission_id");
        stage["master_mission_id_label"] = stage_row.s("master_mission_id_label");
        stage["master_stage_layout_id"] = (u32)stage_row.i("master_stage_layout_id");
        stage["master_stage_layout_id_label"] = stage_row.s("master_stage_layout_id_label");
        stage["master_enemy_party_id"] = (u32)stage_row.i("master_enemy_party_id");
        stage["master_map_id"] = (u32)stage_row.i("master_map_id");
        stage["master_map_id_label"] = stage_row.s("master_map_id_label");
        // (b) a uint in CMissionStageInfo: the CHash32 of the stage_bgm name
        stage["stage_bgm"] = stage_row.s("stage_bgm").empty() ? 0u : chash32(stage_row.s("stage_bgm").c_str());
        stage["is_surprise_enemy_stage"] = stage_row.i("is_surprise_enemy_stage") != 0;
        stages.push(stage);
    });
    return stages;
}

// 6. Pays the stamina, ticket and vanish item.
void pay(ext::Ctx& ctx, MissionStart& start) {
    start.stamina_paid = start.restarting ? 0 : start.stamina_cost;
    ctx.st.q("update player set stamina = ?, stamina_at = case when stamina >= ? then ? else stamina_at end",
             {start.stamina_before - start.stamina_paid, ctx.stamina_max((u32)ctx.st.one("select level from player", {})), clock_now()});
    if (start.restarting) return;
    if (start.ticket_item_id) ext::add_stock(ctx, start.ticket_item_id, -(int64_t)start.ticket_num);  // checked in step 3: never below 0
    if (start.vanish_item_id) ext::add_stock(ctx, start.vanish_item_id, -(int64_t)start.vanish_num);
}

// 7. The player's party (or a module's).
void own_party(ext::Ctx& ctx, MissionStart& start) {
    // The party: (b) the third argument is the helper index + 1 (CParameterUI+0x1b0), not a
    // party; the party is server state: the player's current party_id (set by UpdateParty),
    // else party 1 (d). (A NULL party_id reads as 0 here, which has no members, so party 1: the
    // same party a NULL-as-default read would give.)
    start.party_id = (u32)one_null_as_zero(ctx.st, "select party_id from player", {}, 1);
    start.party_uids = party_member_uids(ctx, start.party_id);
    if (start.party_uids.empty()) {
        start.party_id = 1;
        start.party_uids = party_member_uids(ctx, 1);
    }
    if (start.module_override && !start.module_override->party.empty()) start.party_uids = start.module_override->party;  // the module's party
}

// 8a. The mission's master_mission_npc rows (the tutorial's NPC party, or an event mission's NPC
// helper candidates).
void load_mission_npcs(ext::Ctx& ctx, MissionStart& start) {
    // A mission with master_mission_npc rows (the tutorial battle ms00_001:
    // tutorial_npc_role0001..3 at level 60) is fought by those NPCs, not the player's party.
    // (a) the rows (role through master_npc_base_parameter, level); (c) the tutorial battle used
    // preset characters; (d) that they're sent as the party (BattleParameter.PlayerCharacter, uids
    // 0x7f000000 + order: kNpcPartyUid0) with the stats rules of a roster character and no limit
    // break. A temp table shadows `roster` while they're built.
    // (b) In the game their stats and weapon then come from the client's NPC model
    // (client_npc_status: MasterMissionNpcModel::CalculateParameter, which adds the NPC's weapon
    // master_npc_base_parameter.master_item_id and the role's talents), and so do their skills
    // and skill levels (MasterRoleModel::AddSkillInfo).
    ctx.m.q(
        "select b.master_role_id as role, n.level as level, n.id as id, n.master_npc_id as npc from master_mission_npc n "
        "join master_npc_base_parameter b on b.id = n.master_npc_id where n.master_mission_id = ? order by n.order_id",
        {start.args.mission}, [&](const Row& npc_row) {
            start.all_npcs.push_back({(u32)npc_row.i("role"), (u32)npc_row.i("level"), (u32)npc_row.i("id"), (u32)npc_row.i("npc")});
        });
    start.npcs = start.all_npcs;
    if (start.module_override && !start.module_override->party.empty()) start.npcs.clear();  // a module's party wins (Sphere 211)
}

// 8b. An event mission's NPCs are helper candidates: the one the player picked joins.
void pick_event_npc_helper(MissionStart& start) {
    // Event missions: (b) CParameterUtility::CreateRentalListAuto(type, mission) makes a
    // mission's master_mission_npc rows the helper list of the mission menu (instead of the
    // rental list), so they are helper candidates, not the party: the player's party fights, and
    // the NPC the player picked (MissionStart's NPC helper argument) joins as the 4th member.
    // Only the tutorial (CPhase_TutorialNext builds its preset party from the same rows) keeps
    // the NPC party.
    if (MissionType(start.mission_ref.type) != MissionType::kEvent || start.npcs.empty()) return;
    const u32 helper_index_plus_1 = start.args.helper_index_plus_1, npc_helper_id = start.args.npc_helper_id;
    for (size_t k = 0; k < start.all_npcs.size(); k++)
        if (helper_index_plus_1 && npc_helper_id && (start.all_npcs[k].mission_npc_id == npc_helper_id || start.all_npcs[k].npc_id == npc_helper_id))
            start.event_npc = (u32)k + 1;
    if (helper_index_plus_1 && npc_helper_id && !start.event_npc)
        LOGW("server", "MissionStart: NPC helper %u isn't one of mission %u's NPCs; none joins", npc_helper_id, start.args.mission);
    if (start.event_npc) start.npcs = {start.npcs[start.event_npc - 1]};
    else start.npcs.clear();
}

// 8c. The picked NPC helper's battle status.
void event_npc_status(ext::Ctx& ctx, MissionStart& start) {
    if (!start.event_npc) return;
    // (d) as the tutorial's NPCs: the stats rules of a roster character, no limit break
    ctx.st.exec("create temp table roster as select * from main.roster where 0");
    ctx.st.q("insert into temp.roster values (?,?,?,0,0,0,1,1,1,0,0,0,?)",
             {kNpcPartyUid0 + 1, start.npcs[0].role_id, start.npcs[0].level, clock_now()});
    start.event_npc_status = person_status_info(ctx, kNpcPartyUid0 + 1);
    ctx.st.exec("drop table temp.roster");
    // (b) as the tutorial's NPCs: in the game the stats, the weapon
    // (master_npc_base_parameter.master_item_id) and the skills come from the client's own NPC
    // model, MasterMissionNpcModel::CalculateParameter(master_mission_npc id), the function
    // tCharaData::CalcStatus runs for the NPC helper list's tCharaData
    // (tCharaData::InitializeNPC). Without it the helper fought without its weapon.
    // (b) the same model from the master data (soaserver/npc_status.h)
    npc_master_status(ctx, start.all_npcs[start.event_npc - 1].mission_npc_id, start.event_npc_status);
    start.npcs.clear();
}

// 8d. The tutorial's NPC party: the NPCs replace the party, in a temp `roster` (dropped by
// drop_npc_party after the party's statuses are built).
void npc_party(ext::Ctx& ctx, MissionStart& start) {
    if (start.npcs.empty()) return;
    ctx.st.exec("create temp table roster as select * from main.roster where 0");
    for (size_t k = 0; k < start.npcs.size(); k++)
        ctx.st.q("insert into temp.roster values (?,?,?,0,0,0,1,1,1,0,0,0,?)",
                 {kNpcPartyUid0 + k + 1, start.npcs[k].role_id, start.npcs[k].level, clock_now()});
    start.party_uids.clear();
    for (size_t k = 0; k < start.npcs.size(); k++) start.party_uids.push_back(kNpcPartyUid0 + k + 1);
}

// 9. The battle status of each party member.
void party_members(ext::Ctx& ctx, MissionStart& start) {
    Value& members = start.player_characters;
    for (u64 uid : start.party_uids) {
        LOGI("server", "MissionStart party member %zu: uid %llu", (size_t)(members.arr.size()),
             (unsigned long long)uid);  // read by tools/compare_tutorial.py
        members.push(person_status_info(ctx, uid));
        size_t k = members.arr.size() - 1;
        // (b) the NPC model from the master data (npc_master_status, soaserver/npc_status.h)
        if (!start.npcs.empty() && k < start.all_npcs.size()) {
            bool applied = npc_master_status(ctx, start.all_npcs[k].mission_npc_id, members.arr[k]);
            auto npc_stat = [&](const char* key) {
                const Value* v = members.arr[k].find(key);
                return v ? v->f : -1.0;
            };
            // (the six stats: tools/compare_tutorial.py reads the party of a soa run from here)
            LOGI("server", "MissionStart NPC %u: master-data model %s (attack %g) [hp %g atk %g int %g def %g hit %g grd %g]",
                 start.all_npcs[k].mission_npc_id, applied ? "applied" : "declined", npc_stat("attack"), npc_stat("hp"), npc_stat("attack"),
                 npc_stat("intelligence"), npc_stat("defence"), npc_stat("hit"), npc_stat("guard"));
        }
        start.play_uids += std::to_string(uid) + ",";
    }
}

// 10a. A rental clone (api/social/rental.h) in either u64 argument fights as the party's fourth
// member. False when neither argument names one of the player's characters.
bool rental_helper(ext::Ctx& ctx, MissionStart& start) {
    // Rental helpers (api/social/rental.cpp): a synthetic rental character (a roster clone,
    // rental.h, d) in either u64 argument fights as the party's fourth member: (b) the mission
    // menu's party data keeps the chosen helper in slot 3 (tPartyData +0x8798 = 8 + 3 x 0x2d30)
    // and CPartyManager::InitializePlayer builds exactly four slots.
    const u64 own_helper_uid = start.args.own_helper_uid, rental_uid = start.args.rental_uid;
    u64 rental_id = rental::source_uid(own_helper_uid) ? own_helper_uid : rental::source_uid(rental_uid) ? rental_uid : 0;
    u64 rental_source = rental_id ? rental::source_uid(rental_id) : 0;
    if (rental_source && !ctx.st.one("select count(*) from roster where uid = ?", {rental_source})) rental_source = 0;
    if (!(start.args.helper_index_plus_1 && rental_source && start.npcs.empty())) return false;
    Value helper_status = person_status_info(ctx, rental_source);
    helper_status["id"] = rental_id;
    Value& members = start.player_characters;
    if (members.arr.size() >= 4) members.arr[3] = helper_status;
    else members.push(helper_status);
    start.helper_uid = rental_id;
    start.helper_kind = HelperKind::kRental;
    // (d) counted per rental day for the rental bonus (api/social/rental.cpp)
    ext::ensure_schema(ctx.st);
    ctx.st.q("insert into follow_rental (day, count) values (?, 1) on conflict(day) do update set count = count + 1",
             {day_start(clock_now(), (int)ctx.global_u32("login_bonus_reset_hour", 4))});
    LOGI("server", "MissionStart: rental helper %llu (a clone of roster uid %llu) as member 4",
         (unsigned long long)rental_id,  // read by rental_session.sh
         (unsigned long long)rental_source);
    return true;
}

// 10b. An own character as the helper, or a helper only recorded.
void own_or_recorded_helper(ext::Ctx& ctx, MissionStart& start) {
    // Helpers (d: the argument meanings are inferred, docs/api.md MissionStart): an own
    // character (kind 0, u64) not in the party joins the battle status list and is named in
    // rental_sub_character_id; an NPC helper (u32 master_npc id) and a rental character (u64)
    // are recorded (the NPC's status and a friend's roster aren't server state here).
    const u64 own_helper_uid = start.args.own_helper_uid;
    if (own_helper_uid && ctx.st.one("select count(*) from roster where uid = ?", {own_helper_uid}) &&
        std::find(start.party_uids.begin(), start.party_uids.end(), own_helper_uid) == start.party_uids.end()) {
        start.helper_uid = own_helper_uid;
        start.helper_kind = HelperKind::kOwn;
        start.player_characters.push(person_status_info(ctx, own_helper_uid));
    } else if (start.args.rental_uid) {
        start.helper_uid = start.args.rental_uid;
        start.helper_kind = HelperKind::kRental;
    } else if (start.args.npc_helper_id) {
        start.helper_kind = HelperKind::kNpc;
    }
}

// 10c. The event mission's NPC helper as the 4th member.
void event_npc_member(MissionStart& start) {
    if (!start.event_npc || start.event_npc_status.type != Value::Map) return;
    Value& members = start.player_characters;
    if (members.arr.size() > 3) members.arr.resize(3);
    members.push(start.event_npc_status);
    start.helper_kind = HelperKind::kNpc;
    LOGI("server", "MissionStart: event NPC helper %u (role %llu, level %llu) as member %zu", start.args.npc_helper_id,
         (unsigned long long)start.event_npc_status.get_u("master_role_id"), (unsigned long long)start.event_npc_status.get_u("level"),
         members.arr.size());
}

// 10. The 4th member: a rental helper, an own helper, or the event mission's NPC helper.
void helper_member(ext::Ctx& ctx, MissionStart& start) {
    if (!rental_helper(ctx, start) && start.args.helper_index_plus_1) own_or_recorded_helper(ctx, start);
    event_npc_member(start);
}

// 10d. The tutorial's NPC party is built: the temp `roster` goes.
void drop_npc_party(ext::Ctx& ctx, MissionStart& start) {
    if (start.npcs.empty()) return;
    ctx.st.exec("drop table temp.roster");
    LOGI("server", "MissionStart: %zu mission NPCs as the party (master_mission_npc)", start.npcs.size());
}

// 11. The play record and the mission's play count.
void record_play(ext::Ctx& ctx, MissionStart& start) {
    const u32 mission = start.args.mission;
    ctx.st.q("insert or replace into play values (1,?,?,?,?,?)", {mission, start.party_id, clock_now(), start.stamina_cost, start.play_uids});
    if (!start.restarting)
        ctx.st.q("insert or replace into play_ext values (1,?,?,?,?,?,?)", {start.mission_ref.type, start.surprise ? 1 : 0, start.helper_uid,
                                                                            (u32)start.helper_kind, start.args.npc_helper_id, start.campaign_lots});
    ctx.st.q("insert into mission (mission_id) values (?) on conflict(mission_id) do nothing", {mission});
    if (!start.restarting) ctx.st.q("update mission set play_count = play_count + 1 where mission_id = ?", {mission});
}

// 12. The answer: the player state, MissionParameter, PlayMission, BattleParameter; the modules'
// MissionStartExtra.
std::vector<u8> mission_start_response(ext::Ctx& ctx, MissionStart& start) {
    const u32 mission = start.args.mission;
    Value data = base_data(ctx);
    data["MissionParameter"] = start.mission_parameter;
    Value play_mission = Value::object();
    play_mission["mission_id"] = mission;
    play_mission["is_play"] = 1u;
    play_mission["is_expired"] = false;
    play_mission["is_maintenance"] = false;
    data["PlayMission"] = play_mission;
    Value battle_parameter = Value::object();
    battle_parameter["rental_sub_character_id"] = start.helper_kind == HelperKind::kOwn ? start.helper_uid : 0;
    battle_parameter["PlayerCharacter"] = start.player_characters;
    data["BattleParameter"] = battle_parameter;
    if (!start.restarting && (start.ticket_item_id || start.vanish_item_id)) data["StockItem"] = stack_item_info_list(ctx);
    {  // extension modules' additions (ext::MissionStartExtra)
        ext::MissionInfo info = mission_info(ctx, start.mission_ref, mission, start.party_uids);
        info.restart = start.restarting;
        ext::mission_start_extra(ctx, info, data["MissionParameter"], data);
    }
    LOGI("server", "MissionStart mission %u (%s) party %u (helper arg %u kind %u): %zu members, stamina %u -> %u%s%s", mission,
         start.mission_ref.table.c_str(), start.party_id, start.args.helper_index_plus_1, (u32)start.helper_kind, start.party_uids.size(),
         start.stamina_before, start.stamina_before - start.stamina_paid, start.surprise ? ", surprise enemy" : "",
         start.campaign_lots ? ", campaign lots" : "");  // read by battle_session.sh
    return body(data);
}

}  // namespace

// MissionStart, and the same start for a module (ext::Ctx::core_mission: `module_override`, the
// module's changes) or a MissionRestart (`restarting`: no stamina, no new play count).
std::vector<u8> start_mission(ext::Ctx& ctx, const Request& req, const ext::MissionOverride* module_override, bool restarting) {
    MissionStart start;
    start.module_override = module_override;
    start.restarting = restarting;
    if (!resolve_mission(ctx, req, start)) return {};
    read_cost(ctx, start);
    if (std::vector<u8> refused = check_cost(ctx, req, start); !refused.empty()) return refused;
    roll_surprise(ctx, start);
    start.mission_parameter["mission_stage"] = stage_list(ctx, start.args.mission);
    // (d) no pre-rolled drops: MissionEnd rolls them (docs/server-rules.md "Server missions")
    start.mission_parameter["mission_drop"] = Value::array();
    start.mission_parameter["mission_drop_rare"] = Value::array();
    start.mission_parameter["common_drop"] = Value::array();
    start.mission_parameter["battle_evaluation_drop"] = Value::array();
    pay(ctx, start);
    own_party(ctx, start);
    start.player_characters = Value::array();
    load_mission_npcs(ctx, start);
    pick_event_npc_helper(start);
    event_npc_status(ctx, start);
    npc_party(ctx, start);
    party_members(ctx, start);
    helper_member(ctx, start);
    drop_npc_party(ctx, start);
    record_play(ctx, start);
    return mission_start_response(ctx, start);
}

// What a mission played, for the extension modules (ext::MissionInfo).
ext::MissionInfo mission_info(ext::Ctx& ctx, const MissionRef& ref, u32 mission, const std::vector<u64>& uids) {
    ext::MissionInfo info;
    info.mission = mission;
    info.type = ref.type;
    info.area = ref.area;
    info.table = ref.table;
    info.uids = uids;
    for (u64 uid : uids) {
        int64_t role = ctx.st.one("select role_id from roster where uid = ?", {uid}, 0);
        if (role) info.roles.push_back((u32)role);
    }
    return info;
}

// MissionStart(u32 mission_type, u32 mission_id, u32 helper_index_plus_1, u64 own_helper_uid,
//              u32 npc_helper_id, u64 rental_uid, u32) -> MissionStartRes          fid b7c62bc2
// API: docs/api.md#missionstart   Rules: docs/server-rules.md "2.2 MissionStart", "Server missions", "Rental helpers"
//
// Starts a battle: pays its cost and sends the stages and the battle party's statuses.
//   (a) the mission row of the type's table (master_mission, master_event_mission,
//       master_tower_mission, master_world_map_mission; an unknown id isn't answered);
//   (a) use_stamina, x a running stamina campaign; ticket_item_id x ticket_num and
//       vanish_item_id x vanish_num, taken at the start (d); stamina short -> 10004, items short
//       -> 10206 (d: the code); a locked mission isn't refused (d);
//   (a) the surprise roll at surprise_rate (d: master_global surprise_rate when the row has none);
//   (d) the party is the player's current party (Player.party_id), else party 1; (b) the third
//       argument is the helper index + 1, not a party;
//   the tutorial's master_mission_npc rows fight as the party; an event mission's are helper
//       candidates (b); a rental clone, an own character or the picked NPC joins as member 4 (d).
// Answers: the player state with MissionParameter, PlayMission, BattleParameter, StockItem when
// a ticket or vanish item was taken, and the modules' MissionStartExtra additions.
std::vector<u8> mission_start(ext::Ctx& ctx, const Request& req) { return start_mission(ctx, req, nullptr, false); }

// MissionStart (src/core/modules.cpp: the core's APIs first).
void register_mission_start() { ext::add_core_api({"MissionStart"}, mission_start); }

}  // namespace soa::server
