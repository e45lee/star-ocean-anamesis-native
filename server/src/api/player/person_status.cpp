// A battle member's status: CPersonStatusInfo (api/player/person_status.h).
// Port code, not guest behaviour; every rule carries its source label, (a) master data, (b)
// client-side evidence, (c) outside knowledge, (d) assumption (docs/server-rules.md#battle-status).
#include "api/player/person_status.h"

#include <algorithm>

#include "api/favor/favor.h"  // favor levels
#include "api/growth/mastery.h"  // mastery_inheritance
#include "api/player/player_info.h"  // player_id
#include "api/player/roster.h"  // person_info

namespace soa::server {

using ext::Row;

namespace {

// The six battle stats (CPersonStatusInfo and the master tables name them alike).
const char* const kStatKeys[6] = {"hp", "attack", "intelligence", "defence", "hit", "guard"};
// The two equipment slots: roster <slot>_uid, CPersonStatusInfo <slot>_master_item_id, ...
const char* const kEquipmentSlots[2] = {"weapon", "accessory"};

// The role's stats at `level`, its rank and its skills (person_status_info, step 1).
void base_stats(ext::Ctx& ctx, const Row& roster_row, RoleId role, u32 level, Value& status) {
    // (b) stats as the client's status screen computes them (PersonModel::
    // CalculateParameter -> tCharaData::CalcStatus, docs/server-rules.md#battle-status):
    // round_half_away(master_role.<stat> x master_character_common_parameter[level].<stat>
    // / 100), times the master_rank row of (role rank, limit break) / 100 (rounded again:
    // (d)), at least 1. The next steps add the equipment, favor, awakening and seeds; factors
    // (talents) aren't added (d).
    double base[6] = {0}, rank_percent[6] = {100, 100, 100, 100, 100, 100};
    const auto& keys = kStatKeys;
    u32 rush_level = 1;
    ctx.m.q("select * from master_character_common_parameter where level = ?", {level}, [&](const Row& level_row) {
        for (int k = 0; k < 6; k++) base[k] = (double)level_row.i(keys[k]);
    });
    ctx.m.q("select k.* from master_rank k join master_role r on r.rank = k.rank where r.id = ? and k.limit_break = ?",
            {role, roster_row.i("limit_break")}, [&](const Row& rank_row) {
                for (int k = 0; k < 6; k++) rank_percent[k] = (double)rank_row.i(keys[k]);
                rush_level = (u32)std::max<int64_t>(1, rank_row.i("rush_level"));  // (a) master_rank.rush_level
            });
    status["rush1_level"] = rush_level;
    ctx.m.q("select * from master_role where id = ?", {role}, [&](const Row& role_row) {
        for (int k = 0; k < 6; k++) {
            double v = rules::round_half_away(role_row.f(keys[k]) * base[k] / 100.0);
            v = rules::round_half_away(v * rank_percent[k] / 100.0);
            status[keys[k]] = std::max(1.0, v);
        }
        status["ap"] = 100.0;  // (d) the generator's AP; no master column
        // (d) no elemental resistances
        for (const char* d : {"def_fire", "def_water", "def_wind", "def_earth", "def_thunder", "def_light", "def_dark"}) status[d] = 0.0;
        // (d) the role's first weapon of its kind when nothing is equipped
        u32 kind = (u32)role_row.i("master_weapon_kind_id");
        ctx.m.q("select * from master_weapon where master_weapon_kind_id = ? order by serial_number limit 1", {kind}, [&](const Row& weapon_row) {
            status["weapon_id"] = (u32)weapon_row.i("id");
            status["master_weapon_kind_id"] = (u32)weapon_row.i("master_weapon_kind_id");
            status["weapon_kind_id_label"] = weapon_row.s("master_weapon_kind_id_label");
        });
        for (int k = 1; k <= 3; k++) {  // (a) skills open at master_skillN_open_level
            std::string id = "master_skill" + std::to_string(k) + "_id", open_level = "master_skill" + std::to_string(k) + "_open_level";
            bool open = role_row.i(id.c_str()) && (u32)role_row.i(open_level.c_str()) <= level;
            status["skill" + std::to_string(k)] = open ? (u32)role_row.i(id.c_str()) : 0u;
            if (!open) status["skill" + std::to_string(k) + "_level"] = 0u;
        }
        status["rush1"] = (u32)role_row.i("rush_skill1_id");
    });
}

// The equipped weapon's and accessory's stats (step 2).
void equipment_stats(ext::Ctx& ctx, const Row& roster_row, Value& status) {
    status["weapon_master_item_id"] = 0u;
    status["weapon_limit_break_count"] = 0u;
    status["weapon_level"] = 1u;
    status["accessory_master_item_id"] = 0u;
    status["accessory_limit_break_count"] = 0u;
    status["accessory_level"] = 0u;
    const auto& keys = kStatKeys;
    // Equipment (b: tCharaData::CalcStatus adds the equipped weapon's and accessory's
    // master_item stats): (a) master_item hp / attack .. guard / ap; (d) at their base
    // values (the compose-level growth toward *_max isn't applied yet); (a) weapon_id =
    // the weapon's master_weapon_id.
    for (int k = 0; k < 2; k++) {
        const std::string slot = kEquipmentSlots[k];
        u64 item_uid = (u64)roster_row.i((slot + "_uid").c_str());
        if (!item_uid) continue;
        ctx.st.q("select * from items where uid = ?", {item_uid}, [&](const Row& item_row) {
            u32 master_item_id = (u32)item_row.i("master_item_id");
            status[slot + "_master_item_id"] = master_item_id;
            status[slot + "_limit_break_count"] = (u32)item_row.i("limit_break");
            status[slot + "_level"] = (u32)std::max<int64_t>(1, item_row.i("level"));
            ctx.m.q("select * from master_item where id = ?", {master_item_id}, [&](const Row& master_item_row) {
                for (int j = 0; j < 6; j++) status[keys[j]] = status[keys[j]].f + (double)master_item_row.i(keys[j]);
                status["ap"] = status["ap"].f + (double)master_item_row.i("ap");
                if (k == 0 && master_item_row.i("master_weapon_id")) status["weapon_id"] = (u32)master_item_row.i("master_weapon_id");
            });
        });
    }
}

// The favor level's AP bonus and the awakening's rush skill (step 3).
void favor_and_awakening(ext::Ctx& ctx, const Row& roster_row, RoleId role, Value& status) {
    // (a) master_favor_level.ap_bonus of the character's favor level (b: GetFavorApBonus);
    // (d) added to the base AP 100
    u32 favor_level =
        favor::level_of(ctx.st.h, ctx.m.h, ctx.now(), ctx.m.one_id<SameRoleId>("select same_role_id from master_role where id = ?", {role}));
    status["ap"] = status["ap"].f + (double)ctx.m.one("select ifnull(ap_bonus, 0) from master_favor_level where id = ?", {favor_level});
    // (a) awakening: the master_awaken row of the role's category at its awaken_level replaces
    // the rush skill and gauge (docs/server-rules.md#battle-status); its talents (factors) aren't added (d)
    if (roster_row.i("awaken") > 0)
        ctx.m.q("select a.* from master_awaken a join master_role r on r.role_category_id = a.role_category_id where r.id = ? and a.awaken_level = ?",
                {role, roster_row.i("awaken")}, [&](const Row& awaken_row) {
                    if (!awaken_row.i("rush_skill1_id")) return;
                    status["rush1"] = (u32)awaken_row.i("rush_skill1_id");
                    status["rush1_label"] = awaken_row.s("rush_skill1_id_label");
                    status["rush1_level"] = (u32)std::max<int64_t>(1, awaken_row.i("rush_skill1_level"));
                    status["rush_skill1_factor_id"] = (u32)awaken_row.i("rush_skill1_factor_id");
                    status["rush_gauge_max"] = (u32)awaken_row.f("rush_gauge_max");
                    status["rush_gauge_use"] = (u32)awaken_row.f("rush_gauge_use");
                });
    status["favor_level"] = favor_level;
}

// The seeds (roster add_*) (step 4).
void seed_stats(const Row& roster_row, Value& status) {
    // (b) the seeds (roster add_*, raised by AddStatusCharacter) are added to the stats
    // (PersonModel::CalculateParameter adds CPersonInfo add_*) and reported in add_*, for a
    // character with growth (has_growth, as person_info sends them)
    if (!has_growth(roster_row)) return;
    for (const char* k : {"hp", "attack", "intelligence", "defence", "hit", "guard", "ap"}) {
        std::string add_column = std::string("add_") + k;
        status[add_column] = (u32)roster_row.i(add_column.c_str());
        status[k] = status[k].f + (double)roster_row.i(add_column.c_str());
    }
}

}  // namespace

// The battle status of one party member (CPersonStatusInfo: MissionStart's BattleParameter.PlayerCharacter
// entries, which the client's battle uses as they are), as the server computed it: the
// character's CPersonInfo (api/player/roster.cpp) plus the player's name and level and the
// computed stats. Its four steps are above.
Value person_status_info(ext::Ctx& ctx, u64 uid) {
    Value status = Value::object();
    const PlayerId owner = player_id(ctx);
    std::string player_name;
    u32 player_level = 1;
    ctx.st.q("select name, level from player", {}, [&](const Row& player_row) {
        player_name = player_row.s("name");
        player_level = (u32)player_row.i("level");
    });
    ctx.st.q("select * from roster where uid = ?", {uid}, [&](const Row& roster_row) {
        const RoleId role = roster_row.id<RoleId>("role_id");
        u32 level = (u32)roster_row.i("level");
        status = person_info(ctx, roster_row, owner);
        status["player_level"] = player_level;
        status["player_name"] = player_name;
        auto next = ctx.role_next(role);
        status["next_exp"] = level < next.size() ? next[level] : 0u;  // (b) the role's EXP curve
        base_stats(ctx, roster_row, role, level, status);
        equipment_stats(ctx, roster_row, status);
        favor_and_awakening(ctx, roster_row, role, status);
        // (d) none of these apply to the server's characters
        status["is_rookie"] = false;
        status["is_subscription"] = false;
        status["is_multi_main_character"] = false;
        // (b) the inherited mastery talent and its master's role (api/growth/mastery.cpp; 0 for
        // a character that isn't a graduated 弟子); the talent only while the disciple's role type
        // is the master's (uimsg_evolution_role_change_confirm: another role makes it 無効)
        MasteryInheritance inh = mastery_inheritance(ctx, CharacterUid(uid));
        status["parent_master_role_id"] = inh.parent_master_role_id;
        status["mastery_talent_id"] = inh.active ? inh.mastery_talent_id : 0u;
        seed_stats(roster_row, status);
    });
    return status;
}

}  // namespace soa::server
