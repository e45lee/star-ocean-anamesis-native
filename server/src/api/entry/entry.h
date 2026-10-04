#pragma once
// The entry flow (port code, not guest behaviour): Login / SimpleLogin, CreatePlayer, the
// tutorial, the UI tutorials seen, the terms version, the player's name, the server time
// (api/entry/entry.cpp, api/entry/README.md; docs/server-rules.md#entry).
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

// CreatePlayer(name, uuid): the new player (its doc block is in entry.cpp). Public for the tests.
std::vector<u8> create_player(ext::Ctx& ctx, const Request& req);

// soa-server's CDN keys of a Login answer: AssetPath, MasterPath, r_ver, LatestEpisodeVersion and
// a_ver; nothing without a CDN. `aver_only`: a_ver only (CreatePlayer's answer).
void add_cdn_paths(ext::Ctx& ctx, Value& data, bool aver_only = false);
// data.LatestEpisodeVersion: the number of episodes whose data packs the client offers (master_global).
void add_episode_version(ext::Ctx& ctx, Value& data);
// data.a_ver: the app version the client accepts (master_global a_ver_android).
void add_aver(ext::Ctx& ctx, Value& data);

// The answer of GetServerTime, GetMissionList, and NoLoginStart / GetPlayer without a player:
// data.Time only.
std::vector<u8> time_only(ext::Ctx& ctx);

}  // namespace soa::server
