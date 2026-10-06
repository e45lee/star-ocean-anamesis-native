// The state's references into the master DB (state/check.h; server/PLAN-schema.md S0). Port code.
#include "state/check.h"

#include <set>
#include <sstream>

#include "soaserver/ext.h"

namespace soa::server::state {

using ext::Row;
using ext::Sql;

const std::vector<MasterRef>& master_refs() {
    // PLAN-schema 1.6's "m:" rows, in its order (tools/schema_inventory.py RELS).
    static const std::vector<MasterRef> refs = {
        {"roster", "role_id", "master_role", "id", false},
        {"items", "master_item_id", "master_item", "id", false},
        {"stock", "master_item_id", "master_item", "id", false},
        {"gear_items", "master_item_id", "master_item", "id", false},
        // the mission id spaces are disjoint (PLAN-schema F6); MissionEnd records the tower's floors too
        {"mission", "mission_id", "master_mission|master_event_mission|master_world_map_mission|master_tower_mission", "id", false},
        {"unlocks", "mission_id", "master_mission|master_event_mission|master_world_map_mission|master_tower_mission", "id", false},
        {"unlocks", "by_mission", "master_mission|master_event_mission|master_world_map_mission|master_tower_mission", "id", true},
        {"play", "mission_id", "master_mission|master_event_mission|master_world_map_mission|master_tower_mission|master_deep_space_mission", "id",
         true},
        {"gacha_history", "gacha_id", "master_gacha", "id", false},
        // NULL: a weapon draw (0 before PLAN-schema S10, which the migration tests check on the older versions)
        {"gacha_history", "role_id", "master_role", "id", true},
        {"stepup", "head", "master_gacha", "id", false},
        {"box_state", "gacha_id", "master_gacha", "id", false},
        {"login_bonus", "id", "master_login_bonus", "id", false},
        {"achievements", "id", "master_achievement", "id", false},
        {"titles", "id", "master_title", "id", false},
        {"premium_pass", "id", "master_premium_login_bonus", "id", false},
        {"subscription", "plan_id", "master_subscription_plan", "id", false},
        {"favor", "same_role_id", "master_role", "same_role_id", false},
        {"favor_drop_play", "same_role_id", "master_role", "same_role_id", false},
        {"shop_counts", "id", "master_item_shop", "id", false},
        {"ds_area", "area_id", "master_deep_space_area", "id", false},
        {"ds_offer", "mission_id", "master_deep_space_mission", "id", false},
        {"sphere_cell", "asset_id", "master_sphere211_floor_asset", "id", false},
        {"sphere", "season_id", "master_sphere211", "id", true},
        {"wboss", "boss_id", "master_world_boss", "id", false},
        {"event_rank_score", "ranking_id", "master_event_ranking", "id", false},
        {"event_rank_received", "group_id", "master_event_ranking_group", "id", false},
        // the story campaign's clears (PLAN-schema S12): Episode 1's missions and the world map's
        {"campaign_clear", "mission_id", "master_mission|master_world_map_mission", "id", false},
        // the 師弟 pairs' mastery type (schema version 13)
        {"mastery", "type_id", "master_mastery_step", "type_id", false},
        // the home's mascot (schema version 13; NULL: never chosen)
        {"player", "mascot_id", "master_person", "id", false},
        // the decorations (schema version 13): an object or a hair colour; a character's hair (0: none)
        {"deco_owned", "master_deco_id", "master_deco_object|master_deco_hair", "id", false},
        {"character_deco", "hair_id", "master_deco_hair", "id", true},
    };
    return refs;
}

namespace {

bool has_table(Sql& db, const std::string& name) {
    return db.one("select count(*) from sqlite_master where type = 'table' and name = ?", {name}) > 0;
}

std::vector<std::string> split_tables(const std::string& tables) {
    std::vector<std::string> out;
    std::stringstream ss(tables);
    for (std::string t; std::getline(ss, t, '|');) out.push_back(t);
    return out;
}

}  // namespace

std::vector<Dangling> check(sqlite3* st_handle, sqlite3* master_handle) {
    Sql st{st_handle}, m{master_handle};
    std::vector<Dangling> out;
    for (const MasterRef& ref : master_refs()) {
        std::vector<std::string> parents;
        for (const std::string& t : split_tables(ref.master_tables))
            if (has_table(m, t)) parents.push_back(t);
        std::set<int64_t> dangling;
        st.q(std::string("select distinct ") + ref.column + " as v from " + ref.table + " where " + ref.column + " is not null", {},
             [&](const Row& r) {
                 int64_t id = r.i("v");
                 if (ref.zero_is_none && id == 0) return;
                 for (const std::string& t : parents)
                     if (m.one("select count(*) from " + t + " where " + ref.master_column + " = ?", {id}) > 0) return;
                 dangling.insert(id);
             });
        if (!dangling.empty()) out.push_back({ref, std::vector<int64_t>(dangling.begin(), dangling.end())});
    }
    return out;
}

std::string describe(const Dangling& d) {
    std::string s = std::string(d.ref.table) + "." + d.ref.column + " -> " + d.ref.master_tables + "." + d.ref.master_column + ": " +
                    std::to_string(d.ids.size()) + " dangling (";
    for (size_t i = 0; i < d.ids.size(); i++) s += (i ? ", " : "") + std::to_string(d.ids[i]);
    return s + ")";
}

}  // namespace soa::server::state
