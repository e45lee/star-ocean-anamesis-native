// Mission NPC status from the master data (soaserver/npc_status.h). Library code; labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include "soaserver/npc_status.h"

#include <sqlite3.h>

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "soaserver/ext.h"

namespace soa::server::rules {

namespace {
using ext::Row;
using ext::Sql;
using u32 = uint32_t;

// The six stats, in the order of the master columns and CPersonStatusInfo's keys.
constexpr int kStats = 6;
constexpr const char* kStatKeys[kStats] = {"hp", "attack", "intelligence", "defence", "hit", "guard"};
enum Stat { kHp = 0, kAttack = 1, kIntelligence = 2, kDefence = 3, kHit = 4, kGuard = 5 };

// The guest's rounding: +-0.5, truncated towards zero through int.
float round_stat(float x) { return (float)(u32)(int)(int64_t)(x > 0.0f ? x + 0.5f : x - 0.5f); }

// (a) master_factor_seed.elment_type: the passive stat effects MasterFactorModel::GetParam folds (b).
enum class FactorElement : u32 {
    kChangeParameter = 16,     // + param2 % to stat param1
    kExchangeParameter = 53,   // param3 % moved from stat param1 to stat param2 (the largest per pair)
    kChangeParameterFix = 70,  // + param2 to stat param1 (98 / 99: to every stat but HP / and HP)
    kAp = 77,                  // + param1 AP
};

// The mission NPC's row: master_mission_npc (level) joined to master_npc_base_parameter (role, weapon).
struct MissionNpc {
    u32 level = 0, role = 0, weapon_item = 0;
};
MissionNpc mission_npc(Sql& master, u32 mission_npc_id) {
    MissionNpc npc;
    master.q(
        "select n.level as level, b.master_role_id as role, b.master_item_id as item from master_mission_npc n "
        "join master_npc_base_parameter b on b.id = n.master_npc_id where n.id = ?",
        {mission_npc_id}, [&](const Row& npc_row) {
            npc.level = (u32)npc_row.i("level");
            npc.role = (u32)npc_row.i("role");
            npc.weapon_item = (u32)npc_row.i("item");
        });
    return npc;
}

// The role's part: master_role's stats (as u32 percentages) and rank, and its factors: the
// talents 1-6 (master_talent.master_factor_id), then the hidden factors 1-4.
struct RoleBase {
    u32 stat[kStats] = {0};
    u32 rank = 0;
};
std::optional<RoleBase> role_base(Sql& master, u32 role, std::vector<u32>& factors) {
    std::optional<RoleBase> base;
    master.q("select * from master_role where id = ?", {role}, [&](const Row& role_row) {
        base.emplace();
        for (int k = 0; k < kStats; k++) base->stat[k] = (u32)role_row.f(kStatKeys[k]);
        base->rank = (u32)role_row.i("rank");
        for (int k = 1; k <= 6; k++) {
            std::string column = "master_talent" + std::to_string(k) + "_id";
            if (u32 talent = (u32)role_row.i(column.c_str())) {
                u32 factor = (u32)master.one("select ifnull(master_factor_id, 0) from master_talent where id = ?", {talent});
                if (factor) factors.push_back(factor);
            }
        }
        for (int k = 1; k <= 4; k++) {
            std::string column = "hidden_factor" + std::to_string(k) + "_id";
            if (u32 factor = (u32)role_row.i(column.c_str())) factors.push_back(factor);
        }
    });
    return base;
}

// base = rnd(common[level].stat x (role stat / 100)), then rnd(base x rank stat / 100) with the
// rank's limit-break-0 row of master_rank.
void base_status(Sql& master, u32 level, const RoleBase& role, float status[kStats]) {
    float common[kStats] = {0}, rank_rate[kStats] = {100, 100, 100, 100, 100, 100};
    master.q("select * from master_character_common_parameter where level = ?", {level}, [&](const Row& common_row) {
        for (int k = 0; k < kStats; k++) common[k] = (float)common_row.f(kStatKeys[k]);
    });
    bool rank_found = false;
    master.q("select * from master_rank where rank = ? order by limit_break != 0, id limit 1", {role.rank}, [&](const Row& rank_row) {
        rank_found = true;
        for (int k = 0; k < kStats; k++) rank_rate[k] = (float)rank_row.f(kStatKeys[k]);
    });
    if (!rank_found)
        for (float& x : rank_rate) x = 0.0f;  // (b) no row: the element's zeros
    for (int k = 0; k < kStats; k++) status[k] = round_stat(common[k] * ((float)role.stat[k] / 100.0f));
    for (int k = 0; k < kStats; k++) status[k] = round_stat((rank_rate[k] / 100.0f) * status[k]);
}

// The NPC's weapon at level 1, limit break 0: attack / intelligence + master_item_compose[rarity]
// .status_up x 1 when non-zero, defence, hit, guard as they are (no HP); its factor1 (if
// factor1_limit_break = 0) and factor2 / factor3 (if their limit break <= 0). Returns the item's
// master_weapon_id (0: none).
u32 add_weapon(Sql& master, u32 item, float status[kStats], std::vector<u32>& factors) {
    u32 weapon_id = 0;
    master.q("select * from master_item where id = ?", {item}, [&](const Row& item_row) {
        weapon_id = (u32)item_row.i("master_weapon_id");
        u32 up = (u32)master.one("select ifnull(status_up, 0) from master_item_compose where rarity = ?", {item_row.i("rarity")});
        u32 attack = (u32)item_row.f("attack"), intelligence = (u32)item_row.f("intelligence");
        if (attack) attack += up * 1;  // x the weapon's level, 1
        if (intelligence) intelligence += up * 1;
        status[kAttack] += (float)attack;
        status[kIntelligence] += (float)intelligence;
        status[kDefence] += (float)(u32)item_row.f("defence");
        status[kHit] += (float)(u32)item_row.f("hit");
        status[kGuard] += (float)(u32)item_row.f("guard");
        for (int k = 1; k <= 3; k++) {
            std::string column = "factor" + std::to_string(k) + "_id", limit_break = "factor" + std::to_string(k) + "_limit_break";
            u32 factor = (u32)item_row.i(column.c_str());
            if (factor && item_row.i(limit_break.c_str()) <= 0) factors.push_back(factor);
        }
    });
    return weapon_id;
}

// MasterFactorModel::GetParameter / CheckFactorSeed / GetParam (the stat parts): the percentages
// per stat and the fixed additions (fix[0] HP, fix[1] AP, fix[2..6] the other stats).
struct FactorSums {
    float percent[kStats] = {0}, fix[7] = {0};
    void apply(u32 element, float p1, float p2, float p3) {
        static const int kFixSlot[kStats] = {0, 2, 3, 4, 5, 6};
        u32 stat = p1 > 0.0f ? (u32)p1 : 0;
        if (element == (u32)FactorElement::kChangeParameter) {
            if (stat <= 5) percent[stat] = p2 + percent[stat];
        } else if (element == (u32)FactorElement::kExchangeParameter) {
            if (stat <= 5) percent[stat] = percent[stat] - p3;  // the moved amount goes to the target (not read here)
        } else if (element == (u32)FactorElement::kChangeParameterFix) {
            if (stat <= 5) fix[kFixSlot[stat]] = p2 + fix[kFixSlot[stat]];
            else if (stat == 98 || stat == 99) {
                if (stat == 99) fix[0] = p2 + fix[0];
                for (int k = 2; k <= 6; k++) fix[k] = p2 + fix[k];
            }
        } else if (element == (u32)FactorElement::kAp) {
            fix[1] = p1 + fix[1];
        }
    }
};

// Folds the passive factors' (timing 0, b) seeds 1-4 in order; the exchanges (53) are applied
// after the others, the largest % per (from, to) pair.
FactorSums fold_factors(Sql& master, const std::vector<u32>& factors) {
    FactorSums sums;
    std::map<u32, std::map<u32, float>> exchange;  // (from, to) -> the largest %
    for (u32 factor : factors) {
        master.q("select * from master_factor where id = ?", {factor}, [&](const Row& factor_row) {
            if (factor_row.i("timing") != 0) return;  // (b) only passive factors change the status
            for (int k = 1; k <= 4; k++) {
                std::string column = "master_factor_seed" + std::to_string(k) + "_id";
                u32 seed = (u32)factor_row.i(column.c_str());
                if (!seed) continue;
                master.q("select * from master_factor_seed where id = ?", {seed}, [&](const Row& seed_row) {
                    u32 element = (u32)seed_row.i("elment_type");
                    float p1 = (float)seed_row.f("param1"), p2 = (float)seed_row.f("param2"), p3 = (float)seed_row.f("param3");
                    if (element != (u32)FactorElement::kExchangeParameter) {
                        sums.apply(element, p1, p2, p3);
                        return;
                    }
                    float& largest = exchange[p1 > 0.0f ? (u32)p1 : 0][p2 > 0.0f ? (u32)p2 : 0];
                    if (largest < p3) largest = p3;
                });
            }
        });
    }
    for (auto& [from, tos] : exchange)
        for (auto& [to, percent] : tos) sums.apply((u32)FactorElement::kExchangeParameter, (float)from, (float)to, percent);
    return sums;
}

// (b) MasterRoleModel::AddSkillInfo: skillN when open at the level, skillN_level 1.
void add_skills(Sql& master, u32 role, u32 level, Value& e) {
    master.q("select * from master_role where id = ?", {role}, [&](const Row& role_row) {
        for (int k = 1; k <= 3; k++) {
            std::string id = "master_skill" + std::to_string(k) + "_id", open_level = "master_skill" + std::to_string(k) + "_open_level";
            bool open = role_row.i(id.c_str()) && (u32)role_row.i(open_level.c_str()) <= level;
            std::string skill = "skill" + std::to_string(k);
            e[skill] = open ? (u32)role_row.i(id.c_str()) : 0u;
            e[skill + "_level"] = 1u;
            if (!open) e[skill + "_label"] = std::string();
        }
    });
}

}  // namespace

// A mission NPC's battle status from the master data, as the client's NPC model computes it
// (docs/server-rules.md#tutorial-battle). (b) The client's
// MasterMissionNpcModel::CalculateParameter -> MasterNpcBaseParameterModel::GetCharacterParameter
// / GetParameter (3.7.0 decompiles work/decomp/tutorial-dmg-e.resolved.c,
// server-rules-factor.resolved.c), in the guest's single-precision steps:
//  - base = rnd(common[level].stat x (u32 master_role.stat / 100)), then rnd(base x
//    master_rank[role rank, limit break 0].stat / 100); rnd = +-0.5, truncated;
//  - + the NPC's weapon (master_npc_base_parameter.master_item_id) at level 1, limit break 0:
//    attack / intelligence + master_item_compose[rarity].status_up x 1 when non-zero, defence,
//    hit, guard as they are (no HP);
//  - the factors: the role's talents 1-6 (master_talent.master_factor_id), its hidden factors
//    1-4, the weapon's factor1 (if factor1_limit_break = 0) and factor2 / factor3 (if their
//    limit break <= 0); of these, the passive ones (timing 0) give their seeds 1-4, folded by
//    MasterFactorModel::GetParam (types 16 ChangeParameter %, 53 ExchangeParameter, the max of
//    each (from, to), 70 ChangeParameterFix, 77 AP);
//  - stat = rnd(stat x (100 + %) / 100) + fix, at least 1.
// Tests server/npc-status-tutorial and server/npc-status-409829631 (library); the port test
// server/npc-status-master compared every row with the client's model until it was removed with the
// StatusProvider (docs/server-rules.md#battle-status).
bool npc_status(sqlite3* master_db, uint32_t mission_npc_id, Value& e) {
    Sql master{master_db};
    const MissionNpc npc = mission_npc(master, mission_npc_id);
    if (!npc.role) return false;
    std::vector<u32> factors;
    const std::optional<RoleBase> role = role_base(master, npc.role, factors);
    if (!role) return false;
    float status[kStats] = {0};
    base_status(master, npc.level, *role, status);
    const u32 weapon_id = add_weapon(master, npc.weapon_item, status, factors);
    const FactorSums sums = fold_factors(master, factors);
    static const int kFixSlot[kStats] = {0, 2, 3, 4, 5, 6};
    for (int k = 0; k < kStats; k++) {
        float v = sums.fix[kFixSlot[k]] + round_stat(status[k] * ((sums.percent[k] + 100.0f) / 100.0f));
        e[kStatKeys[k]] = (double)(v < 1.0f ? 1.0f : v);
    }
    // (b) the model's AP and elemental resistances: CPersonStatusInfo::Initialize's 100 and 0 for
    // every master_mission_npc row (the removed port test server/npc-status-master compared them too)
    e["ap"] = 100.0;
    for (const char* d : {"def_fire", "def_water", "def_wind", "def_earth", "def_thunder", "def_light", "def_dark"}) e[d] = 0.0;
    e["weapon_master_item_id"] = npc.weapon_item;
    if (weapon_id) e["weapon_id"] = weapon_id;
    add_skills(master, npc.role, npc.level, e);
    return true;
}

}  // namespace soa::server::rules
