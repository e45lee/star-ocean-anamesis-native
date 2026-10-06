// Typed master-data lookups (master/master.h; port code, not guest behaviour).
#include "master/master.h"

#include <algorithm>
#include <cstdlib>

#include "rules/mission_rules.h"
#include "soaserver/ext.h"

namespace soa::server::master {

using ext::Row;
using ext::Sql;

std::string global_str(sqlite3* m, const char* key) {
    Sql db{m};
    std::string v;
    db.q("select value from master_global where key = ?", {key}, [&](const Row& r) { v = r.s("value"); });
    return v;
}
u32 global_u32(sqlite3* m, const char* key, u32 dflt) {
    Sql db{m};
    u32 v = dflt;
    db.q("select value from master_global where key = ?", {key}, [&](const Row& r) { v = (u32)strtoul(r.s("value").c_str(), nullptr, 10); });
    return v;
}
u32 global_u32_unless_empty(sqlite3* m, const char* key, u32 dflt) {
    std::string v = global_str(m, key);
    return v.empty() ? dflt : (u32)strtoul(v.c_str(), nullptr, 10);
}
double global_f(sqlite3* m, const char* key, double dflt) {
    Sql db{m};
    double v = dflt;
    db.q("select value from master_global where key = ?", {key}, [&](const Row& r) { v = strtod(r.s("value").c_str(), nullptr); });
    return v;
}

std::vector<std::pair<u32, u32>> player_level_rows(sqlite3* m, const char* column) {
    Sql db{m};
    std::vector<std::pair<u32, u32>> v;
    db.q(std::string("select level, ") + column + " as v from master_player_level order by level", {},
         [&](const Row& r) { v.emplace_back((u32)r.i("level"), (u32)r.i("v")); });
    return v;
}
u32 stamina_max(sqlite3* m, u32 level) { return rules::interpolate_level(player_level_rows(m, "stamina"), level); }
u32 player_level_max(sqlite3* m) { return std::min(999u, global_u32(m, "Player_Rank_max", 255)); }
std::vector<u32> player_next(sqlite3* m) {
    auto rows = player_level_rows(m, "next_exp");
    u32 max = player_level_max(m);
    std::vector<u32> v(max + 1, 0);
    for (u32 l = 1; l < max; l++) v[l] = rules::interpolate_level(rows, l);
    return v;
}

u32 role_level_cap(sqlite3* m, RoleId role) {
    Sql db{m};
    u32 cap = 40;
    db.q("select l.level_max from master_role r join master_role_level_max l on l.rarity = r.rarity where r.id = ?", {role},
         [&](const Row& r) { cap = (u32)r.i("level_max"); });  // NULL reads as 0 (Row::i)
    return cap;
}
std::vector<u32> role_next(sqlite3* m, RoleId role) {
    Sql db{m};
    double rate = 1.0;
    db.q("select b.exp_rate from master_role r join master_role_boosted b on b.rank = r.rank and b.rarity = r.rarity where r.id = ?", {role},
         [&](const Row& r) { rate = r.f("exp_rate"); });
    std::vector<u32> v(1, 0);
    db.q("select level, next_exp from master_character_common_parameter order by level", {}, [&](const Row& r) {
        size_t l = (size_t)r.i("level");
        if (v.size() <= l) v.resize(l + 1, 0);
        v[l] = (u32)(int)((float)rate * (float)r.i("next_exp") + 0.5f);
    });
    return v;
}

std::string text(sqlite3* m, const std::string& message_id) {
    Sql db{m};
    std::string t;
    db.q("select text_value from master_text where message_id = ? and lang = 'ja'", {message_id}, [&](const Row& r) { t = r.s("text_value"); });
    return t;
}

MissionRef find_mission(sqlite3* m, u32 type, u32 mission) {
    Sql db{m};
    MissionRef ref;
    for (const char* t :
         {mission_rules::mission_table(type), "master_mission", "master_event_mission", "master_world_map_mission", "master_tower_mission"}) {
        if (!*t || ref.found) continue;
        db.q(std::string("select * from ") + t + " where id = ?", {mission}, [&](const Row& r) {
            ref.found = true;
            ref.table = t;
            ref.type = ref.table == "master_mission"            ? 0
                       : ref.table == "master_event_mission"    ? 1
                       : ref.table == "master_tower_mission"    ? 2
                       : ref.table == "master_training_mission" ? 4
                                                                : 3;
            // (a) the area column of each table (campaigns name master_area / master_event_area ids)
            ref.area = (u32)(ref.type == 0   ? r.i("master_area_id")
                             : ref.type == 1 ? r.i("master_event_area_id")
                             : ref.type == 2 ? r.i("master_tower_area_id")
                             : ref.type == 4 ? r.i("master_training_area_id")
                                             : r.i("master_world_map_cell_id"));
        });
    }
    return ref;
}

}  // namespace soa::server::master
