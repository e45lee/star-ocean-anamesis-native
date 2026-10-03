// Mission NPC status from the master data (soaserver/npc_status.h). Library code; labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include "soaserver/npc_status.h"

#include <sqlite3.h>

#include <map>
#include <string>
#include <vector>

#include "soaserver/ext.h"

namespace soa::server::rules {

// A mission NPC's battle status from the master data, as the client's NPC model computes it
// (agent t1-tutorial-parity; docs/server-rules.md "Tutorial battle"). (b) The client's
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
// Test server/npc-status-master (port: compared with the client model for every row).
bool npc_status(sqlite3* master, uint32_t mission_npc_id, Value& e) {
    ext::Sql m{master};
    using ext::Row;
    using u32 = uint32_t;
    u32 level = 0, role = 0, item = 0;
    m.q("select n.level as level, b.master_role_id as role, b.master_item_id as item from master_mission_npc n "
        "join master_npc_base_parameter b on b.id = n.master_npc_id where n.id = ?",
        {mission_npc_id}, [&](const Row& r) {
            level = (u32)r.i("level");
            role = (u32)r.i("role");
            item = (u32)r.i("item");
        });
    if (!role) return false;
    const char* keys[6] = {"hp", "attack", "intelligence", "defence", "hit", "guard"};
    auto rnd = [](float x) { return (float)(u32)(int)(long)(x > 0.0f ? x + 0.5f : x - 0.5f); };
    float common[6] = {0}, rankm[6] = {100, 100, 100, 100, 100, 100}, st6[6] = {0};
    u32 rolev[6] = {0}, rank = 0;
    std::vector<u32> factors;
    bool found = false;
    m.q("select * from master_role where id = ?", {role}, [&](const Row& r) {
        found = true;
        for (int k = 0; k < 6; k++) rolev[k] = (u32)r.f(keys[k]);
        rank = (u32)r.i("rank");
        for (int k = 1; k <= 6; k++) {
            std::string c = "master_talent" + std::to_string(k) + "_id";
            if (u32 t = (u32)r.i(c.c_str())) {
                u32 f = (u32)m.one("select ifnull(master_factor_id, 0) from master_talent where id = ?", {t});
                if (f) factors.push_back(f);
            }
        }
        for (int k = 1; k <= 4; k++) {
            std::string c = "hidden_factor" + std::to_string(k) + "_id";
            if (u32 f = (u32)r.i(c.c_str())) factors.push_back(f);
        }
    });
    if (!found) return false;
    m.q("select * from master_character_common_parameter where level = ?", {level}, [&](const Row& r) {
        for (int k = 0; k < 6; k++) common[k] = (float)r.f(keys[k]);
    });
    bool rank_row = false;
    m.q("select * from master_rank where rank = ? order by limit_break != 0, id limit 1", {rank}, [&](const Row& r) {
        rank_row = true;
        for (int k = 0; k < 6; k++) rankm[k] = (float)r.f(keys[k]);
    });
    if (!rank_row)
        for (float& x : rankm) x = 0.0f;  // (b) no row: the element's zeros
    for (int k = 0; k < 6; k++) st6[k] = rnd(common[k] * ((float)rolev[k] / 100.0f));
    for (int k = 0; k < 6; k++) st6[k] = rnd((rankm[k] / 100.0f) * st6[k]);
    u32 weapon_id = 0;
    m.q("select * from master_item where id = ?", {item}, [&](const Row& w) {
        weapon_id = (u32)w.i("master_weapon_id");
        u32 up = (u32)m.one("select ifnull(status_up, 0) from master_item_compose where rarity = ?", {w.i("rarity")});
        u32 atk = (u32)w.f("attack"), itl = (u32)w.f("intelligence");
        if (atk) atk += up * 1;  // x the weapon's level, 1
        if (itl) itl += up * 1;
        st6[1] += (float)atk;
        st6[2] += (float)itl;
        st6[3] += (float)(u32)w.f("defence");
        st6[4] += (float)(u32)w.f("hit");
        st6[5] += (float)(u32)w.f("guard");
        for (int k = 1; k <= 3; k++) {
            std::string c = "factor" + std::to_string(k) + "_id", lb = "factor" + std::to_string(k) + "_limit_break";
            u32 f = (u32)w.i(c.c_str());
            if (f && w.i(lb.c_str()) <= 0) factors.push_back(f);
        }
    });
    // MasterFactorModel::GetParameter / CheckFactorSeed / GetParam (the stat parts)
    float pct[6] = {0}, fix[7] = {0};
    std::map<u32, std::map<u32, float>> exchange;  // type 53: (from, to) -> the largest %
    auto apply = [&](u32 type, float p1, float p2, float p3) {
        u32 i = p1 > 0.0f ? (u32)p1 : 0;
        if (type == 16) {
            if (i <= 5) pct[i] = p2 + pct[i];
        } else if (type == 53) {
            if (i <= 5) pct[i] = pct[i] - p3;  // the moved amount goes to the target (not read here)
        } else if (type == 70) {
            static const int slot[6] = {0, 2, 3, 4, 5, 6};
            if (i <= 5) fix[slot[i]] = p2 + fix[slot[i]];
            else if (i == 98 || i == 99) {
                if (i == 99) fix[0] = p2 + fix[0];
                for (int k = 2; k <= 6; k++) fix[k] = p2 + fix[k];
            }
        } else if (type == 77) {
            fix[1] = p1 + fix[1];
        }
    };
    for (u32 f : factors) {
        m.q("select * from master_factor where id = ?", {f}, [&](const Row& fr) {
            if (fr.i("timing") != 0) return;  // (b) only passive factors change the status
            for (int k = 1; k <= 4; k++) {
                std::string c = "master_factor_seed" + std::to_string(k) + "_id";
                u32 sid = (u32)fr.i(c.c_str());
                if (!sid) continue;
                m.q("select * from master_factor_seed where id = ?", {sid}, [&](const Row& s) {
                    u32 type = (u32)s.i("elment_type");
                    float p1 = (float)s.f("param1"), p2 = (float)s.f("param2"), p3 = (float)s.f("param3");
                    if (type != 53) {
                        apply(type, p1, p2, p3);
                        return;
                    }
                    float& mx = exchange[p1 > 0.0f ? (u32)p1 : 0][p2 > 0.0f ? (u32)p2 : 0];
                    if (mx < p3) mx = p3;
                });
            }
        });
    }
    for (auto& [from, tos] : exchange)
        for (auto& [to, v] : tos) apply(53, (float)from, (float)to, v);
    static const int fslot[6] = {0, 2, 3, 4, 5, 6};
    for (int k = 0; k < 6; k++) {
        float v = fix[fslot[k]] + rnd(st6[k] * ((pct[k] + 100.0f) / 100.0f));
        e[keys[k]] = (double)(v < 1.0f ? 1.0f : v);
    }
    // (b) the model's AP and elemental resistances: CPersonStatusInfo::Initialize's 100 and 0 for
    // every master_mission_npc row (port test server/npc-status-master compares them too)
    e["ap"] = 100.0;
    for (const char* d : {"def_fire", "def_water", "def_wind", "def_earth", "def_thunder", "def_light", "def_dark"}) e[d] = 0.0;
    e["weapon_master_item_id"] = item;
    if (weapon_id) e["weapon_id"] = weapon_id;
    // (b) MasterRoleModel::AddSkillInfo: skillN when open at the level, skillN_level 1
    m.q("select * from master_role where id = ?", {role}, [&](const Row& mr) {
        for (int k = 1; k <= 3; k++) {
            std::string id = "master_skill" + std::to_string(k) + "_id", ol = "master_skill" + std::to_string(k) + "_open_level";
            bool open = mr.i(id.c_str()) && (u32)mr.i(ol.c_str()) <= level;
            std::string sk = "skill" + std::to_string(k);
            e[sk] = open ? (u32)mr.i(id.c_str()) : 0u;
            e[sk + "_level"] = 1u;
            if (!open) e[sk + "_label"] = std::string();
        }
    });
    return true;
}

}  // namespace soa::server::rules
