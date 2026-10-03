// The story campaign's master data (api/campaign/campaign.h): the mission, area, planet, stage and
// world-map tables, read once from the server's master DB. Port code, not guest behaviour. Its own
// SQLite reads (not ext::Sql): the campaign opens the master itself, outside the server object.
#include <sqlite3.h>

#include <cstdio>
#include <string>
#include <vector>

#include "api/campaign/campaign.h"
#include "core/log.h"
#include "soaserver/config.h"

namespace soa::server::campaign {
namespace {

std::string col_s(sqlite3_stmt* st, int i) {
    const unsigned char* t = sqlite3_column_text(st, i);
    return t ? (const char*)t : "";
}
u32 col_u(sqlite3_stmt* st, int i) { return (u32)sqlite3_column_int64(st, i); }

template <typename F>
void query(sqlite3* db, const char* sql, F&& f) {
    sqlite3_stmt* st = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        LOGW("server", "campaign: %s: %s", sql, sqlite3_errmsg(db));
        return;
    }
    while (sqlite3_step(st) == SQLITE_ROW) f(st);
    sqlite3_finalize(st);
}

// (d) a file below this size isn't a master DB (an un-fetched git-lfs pointer, say).
constexpr long kMinMasterBytes = 1000000;

// The master DB the server reads: SOA_MASTER_DB, else the decrypted 3.7.0 DB, else the offline
// build's (the campaign tables are identical in both; a last resort when the 3.7.0 DB is missing).
sqlite3* open_master() {
    std::vector<std::string> paths;
    if (!config().campaign_master_db.empty()) paths.push_back(config().campaign_master_db);
    for (const char* p : {"data/basmaster-3.7.0.sqlite3", "data/basmaster-3.8.0.sqlite3"})  // 380-ok: fallback
        if (std::string f = find_repo_file(p); !f.empty()) paths.push_back(f);
    for (auto& path : paths) {
        FILE* f = fopen(path.c_str(), "rb");
        if (!f) continue;
        fseek(f, 0, SEEK_END);
        long n = ftell(f);
        fclose(f);
        sqlite3* db = nullptr;
        if (n > kMinMasterBytes && sqlite3_open_v2(path.c_str(), &db, SQLITE_OPEN_READONLY, nullptr) == SQLITE_OK) {
            LOGI("server", "campaign: master data from %s", path.c_str());
            return db;
        }
        if (db) sqlite3_close(db);
    }
    LOGW("server", "campaign: no master DB found (set SOA_MASTER_DB)");
    return nullptr;
}

// (a) master_mission: the Episode 1 missions.
void load_missions(sqlite3* db, Master& m) {
    query(db,
          "select id, id_label, master_area_id, order_id, unlock_mission_id, visible_mission_id, use_stamina, "
          "opened_at, closed_at, talk_event_id from master_mission",
          [&](sqlite3_stmt* st) {
              Mission x;
              x.id = col_u(st, 0), x.label = col_s(st, 1), x.area = col_u(st, 2), x.order = col_u(st, 3);
              x.unlock = col_u(st, 4), x.visible = col_u(st, 5), x.stamina = col_u(st, 6);
              x.opened = col_s(st, 7), x.closed = col_s(st, 8), x.talk = sqlite3_column_type(st, 9) != SQLITE_NULL;
              m.missions[x.id] = x;
          });
}

// (a) master_area and master_planet.
void load_areas_and_planets(sqlite3* db, Master& m) {
    query(db, "select id, id_label, master_planet_id, order_id, opened_at, closed_at from master_area", [&](sqlite3_stmt* st) {
        Area a;
        a.id = col_u(st, 0), a.label = col_s(st, 1), a.planet = col_u(st, 2), a.order = col_u(st, 3);
        a.opened = col_s(st, 4), a.closed = col_s(st, 5);
        m.areas[a.id] = a;
    });
    query(db, "select id, id_label, order_id from master_planet", [&](sqlite3_stmt* st) {
        Planet p;
        p.id = col_u(st, 0), p.label = col_s(st, 1), p.order = col_u(st, 2);
        m.planets[p.id] = p;
    });
}

// (a) master_mission_stage, by mission in order_id order.
void load_stages(sqlite3* db, Master& m) {
    query(db,
          "select id, id_label, serial_number, master_mission_id, order_id, master_stage_layout_id, "
          "master_stage_layout_id_label, is_boss, master_enemy_party_id, master_map_id, master_map_id_label, stage_bgm, "
          "is_surprise_enemy_stage from master_mission_stage order by order_id",
          [&](sqlite3_stmt* st) {
              Stage s;
              s.id = col_u(st, 0), s.label = col_s(st, 1), s.serial = col_u(st, 2);
              u32 mission = col_u(st, 3);
              s.order = col_u(st, 4), s.layout = col_u(st, 5), s.layout_label = col_s(st, 6), s.boss = col_u(st, 7) != 0;
              s.enemy_party = col_u(st, 8), s.map = col_u(st, 9), s.map_label = col_s(st, 10), s.bgm = col_s(st, 11);
              s.surprise = col_u(st, 12) != 0;
              m.stages[mission].push_back(s);
          });
}

// (a) the world map (Episodes 2 and 3): master_world_map_mission, master_world_map,
// master_world_map_cell, the story groups' progress (master_world_map_group_mission) and
// master_world_map_progress.
void load_world_map(sqlite3* db, Master& m) {
    query(db,
          "select id, id_label, master_world_map_group_mission_id, master_world_map_cell_id, difficulty, mission_type, "
          "master_scenario_library_id, order_id, use_stamina, unlock_mission_id, visible_mission_id, talk_event_id, "
          "opened_at, closed_at from master_world_map_mission",
          [&](sqlite3_stmt* st) {
              Mission x;
              x.id = col_u(st, 0), x.label = col_s(st, 1), x.group = col_u(st, 2), x.cell = col_u(st, 3);
              x.difficulty = col_u(st, 4), x.type = col_u(st, 5), x.library = col_u(st, 6), x.order = col_u(st, 7);
              x.stamina = col_u(st, 8), x.unlock = col_u(st, 9), x.visible = col_u(st, 10);
              x.talk = sqlite3_column_type(st, 11) != SQLITE_NULL, x.opened = col_s(st, 12), x.closed = col_s(st, 13);
              m.missions[x.id] = x;
          });
    query(db, "select id, id_label, episode_type_id, episode_type_id_label, order_id, opened_at, closed_at from master_world_map",
          [&](sqlite3_stmt* st) {
              WorldMap w;
              w.id = col_u(st, 0), w.label = col_s(st, 1), w.episode = col_u(st, 2), w.episode_label = col_s(st, 3);
              w.order = col_u(st, 4), w.opened = col_s(st, 5), w.closed = col_s(st, 6);
              m.world_maps[w.id] = w;
          });
    query(db, "select id, id_label, master_world_map_id, opened_at, closed_at from master_world_map_cell", [&](sqlite3_stmt* st) {
        Cell c;
        c.id = col_u(st, 0), c.label = col_s(st, 1), c.map = col_u(st, 2), c.opened = col_s(st, 3), c.closed = col_s(st, 4);
        m.cells[c.id] = c;
    });
    query(db, "select id, progress from master_world_map_group_mission where progress is not null",
          [&](sqlite3_stmt* st) { m.group_progress[col_u(st, 0)] = col_u(st, 1); });
    query(db, "select episode_type_id, progress, unlock_condition_mission_id, unlock_mission_group_id from master_world_map_progress",
          [&](sqlite3_stmt* st) { m.progress.push_back({col_u(st, 0), col_u(st, 1), col_u(st, 2), col_u(st, 3)}); });
}

}  // namespace

const Master& master() {
    static Master m;
    if (m.loaded) return m;
    m.loaded = true;
    sqlite3* db = open_master();
    if (!db) return m;
    load_missions(db, m);
    load_areas_and_planets(db, m);
    load_stages(db, m);
    load_world_map(db, m);
    sqlite3_close(db);
    LOGI("server", "campaign: %zu world maps, %zu cells, %zu progress rows", m.world_maps.size(), m.cells.size(), m.progress.size());
    LOGI("server", "campaign: %zu missions, %zu areas, %zu planets", m.missions.size(), m.areas.size(), m.planets.size());
    return m;
}

}  // namespace soa::server::campaign
