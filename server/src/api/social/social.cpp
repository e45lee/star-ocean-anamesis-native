// The follow (フォロー) menu's lists on a local server, which has no other players (api/social/README.md).
// Port code, not guest behaviour; every rule carries its source label, (a) master data, (b)
// client-side evidence, (c) outside knowledge, (d) assumption.
//
// The 3.7.0 home's side menu opens the follow menu (phase 13, CFriendMenu). There are no other
// players on a local server, so the social lists are empty (d) and a player search finds nobody.
// FollowList (also the mission helper list) is the rental helpers' (api/social/rental.cpp).
#include "core/errors.h"
#include "core/modules.h"
#include "core/response.h"
#include "soaserver/ext.h"

namespace soa::server {
namespace {

// Blacklist() -> BlacklistRes                                          fid 36ed89b2
// GetRecentlyPlayedList() -> GetRecentlyPlayedListRes                  fid c5316c8e
// API: docs/api.md#blacklist, docs/api.md#getrecentlyplayedlist
// Rules: docs/server-rules.md "12. Home" (Follow menu)
//
// The follow menu's blocked and recently-played lists.
//   (d) Both are empty: there are no other players. Answering with the player state (instead of
//       the FakeApiCaller's empty canned body) keeps data.Time / Player current.
// Answers: the player state {Time, Player, Wallet}.
std::vector<u8> empty_social_list(ext::Ctx& ctx, const Request&) { return ext::with_player_state(ctx); }

// SearchPlayer(search id) -> SearchPlayerRes                           fid 5e598152
// API: docs/api.md#searchplayer
// Rules: docs/server-rules.md "12. Home" (Follow menu)
//
// The follow menu's player search.
//   (d) Nobody is found: there are no other players.
//   (b) The refusal is error 10002, kPlayerNotFound: the game's own "player data not found" dialog
//       (master_text error_message_text_10002).
// Answers: the refusal (the player state and the error code).
std::vector<u8> search_player(ext::Ctx& ctx, const Request& req) {
    return ext::refuse(ctx, req.method.c_str(), "no other players on the local server", ErrorCode::kPlayerNotFound);
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_social() {
    ext::add_api({"Blacklist", "GetRecentlyPlayedList"}, empty_social_list);
    ext::add_api({"SearchPlayer"}, search_player);
}

}  // namespace soa::server
