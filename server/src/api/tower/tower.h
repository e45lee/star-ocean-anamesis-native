// The tower (試練の遺跡) module of the local server (api/tower/tower.cpp; --restore-tower),
// exposed for its unit tests (tower_tests.cpp). docs/server-rules.md#tower.
#pragma once
#include <string>

#include "soaserver/ext.h"

namespace soa::server::tower {
// The stand-in banner image for a tower area (id_label "tower_NN") whose master_banner row is
// gone: the first of banner_TrialSpace_NNN, _NNN_002, _NNN_001 the port can load; "" if none.
std::string standin_banner_image(const std::string& area_label);
// Whether the client will show the area (a master_tower_area row): its banner row exists, or a
// stand-in can be made.
bool area_banner_ok(ext::Sql& master, const ext::Row& area_row);
// Adds the stand-in banner rows to a master DB (the client's copy); returns how many.
int client_banners(ext::Sql& client_master);
// Puts ActiveTowerMissionList, TowerSchedule and Player.tower_try_count into `data` (a response's
// data map).
void lists(ext::Ctx& ctx, Value& data);
}  // namespace soa::server::tower
