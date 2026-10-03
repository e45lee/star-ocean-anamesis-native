#pragma once
// Rewards (port code, not guest behaviour): granting a content (a drop, a present, a draw) and
// adding a character (a duplicate raises the owned one's limit break); core/rewards.cpp. The
// modules grant through ext::Ctx::grant, which is grant() with drop type 0.
#include "soaserver/ext.h"

namespace soa::server {

// (a) docs/api.md "Content types": 4 free coins (紋章石), 99 an item set (master_item_set).
constexpr u32 kContentTypeFreeCoin = 4;
constexpr u32 kContentTypeItemSet = 99;

// One content to grant: content type, master id, count, Common::MissionDropType.
struct Drop {
    u32 type, id, num, drop_type;
};

// What adding a character did (a duplicate raises the owned one's limit break).
struct Added {
    CharacterUid uid;    // the new character, or the owned one for a duplicate
    bool dup = false;
    u32 owned_role = 0;  // the owned role a duplicate counted against
    u32 lb_before = 0, lb_after = 0;
    u32 item = 0, item_num = 0;  // a duplicate beyond the maximum: limit-break material
};

// Grants a content (drop, present, gacha) and lists what it added in `items` (AddItem),
// `stocks` (StockItem) and `chars` (AddCharacter).
void grant(ext::Ctx& ctx, const Drop& d, Value& items, Value& stocks, Value& chars);
// Grants a content as ext::Ctx::grant does (drop type 0), expanding item sets (content type 99:
// the master_item_set rows, recursively). `free_coins`, when given, adds up the free coins
// (content type 4) granted, sets included.
void grant_with_item_sets(ext::Ctx& ctx, u32 type, u32 id, u32 num, Value& items, Value& stocks, Value& chars, u32* free_coins = nullptr);
// A new character, or (c) a duplicate raises the owned one's limit break by one, up to
// (a) master_character_limit_break.target_limitbreak_max (10).
Added add_character(ext::Ctx& ctx, u32 role);

}  // namespace soa::server
