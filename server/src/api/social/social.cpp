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
// Rules: docs/server-rules.md#home (Follow menu)
//
// The follow menu's blocked and recently-played lists.
//   (d) Both are empty: there are no other players. Answering with the player state (instead of
//       an empty {}) keeps data.Time / Player current.
// Answers: the player state {Time, Player, Wallet}.
std::vector<u8> empty_social_list(ext::Ctx& ctx, const Request&) { return ext::with_player_state(ctx); }

// SearchPlayer(search id) -> SearchPlayerRes                           fid 5e598152
// API: docs/api.md#searchplayer
// Rules: docs/server-rules.md#home (Follow menu)
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
    // FollowAdd(player id) / FollowRemove(player id) / BlacklistAdd(player id) /
    // BlacklistRemove(player id) / UpdateFollowMax() / NeighborList(lat, lon) /
    // NeighborRegist(lat, lon) / LocationRegist(lat, lon): stubs (ext::add_stub)
    // API: docs/api.md#followadd, docs/api.md#followremove, docs/api.md#blacklistadd,
    //      docs/api.md#blacklistremove, docs/api.md#updatefollowmax, docs/api.md#neighborlist,
    //      docs/api.md#neighborregist, docs/api.md#locationregist
    // Rules: docs/server-rules.md#social-stubs
    //
    // The social calls of a server without other players: the user's decision (2026-10-04,
    // docs/unimplemented-apis.md "Decisions": stub, and defer real friends to the multiplayer
    // server, server/PLAN-multiplayer-code.md MC7, which replaces these).
    //   (d) Answered success with {Time} only, nothing stored: the follow and block lists stay
    //       empty, follow_max and the wallet are unchanged (UpdateFollowMax spends nothing), no
    //       location is kept (also the privacy-safe choice). {Time} is what the wire answered for
    //       them before, and the in-process route an empty map; the client carried on with both
    //       (docs/unimplemented-apis.md section 1).
    // Answers: {Time}; each call logs "stub: <Method> ...".
    ext::add_stub(
        {"FollowAdd", "FollowRemove", "BlacklistAdd", "BlacklistRemove", "UpdateFollowMax", "NeighborList", "NeighborRegist", "LocationRegist"});
}

}  // namespace soa::server
