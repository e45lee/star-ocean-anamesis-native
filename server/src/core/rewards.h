#pragma once
// Rewards (port code, not guest behaviour): granting a content (a drop, a present, a draw) and
// adding a character (a duplicate raises the owned one's limit break); core/rewards.cpp. The
// modules grant through ext::Ctx::grant, which is grant(). What to grant is an ext::Grant (content
// type, id, count, drop type), what it added an ext::Granted (soaserver/ext.h).
#include <optional>

#include "api/storage/storage.h"  // EquipSource
#include "soaserver/ext.h"

namespace soa::server {

using ext::Grant;
using ext::Granted;

// What adding a character did (a duplicate raises the owned one's limit break).
struct Added {
    CharacterUid uid;    // the new character, or the owned one for a duplicate
    bool dup = false;
    u32 owned_role = 0;  // the owned role a duplicate counted against
    u32 lb_before = 0, lb_after = 0;
    u32 item = 0, item_num = 0;  // a duplicate beyond the maximum: limit-break material
};

// Grants a content (drop, present, gacha) and lists what it added in `granted`: items (AddItem),
// stocks (StockItem), characters (AddCharacter). Equipment the inventory has no room for goes to
// the overflow box instead (storage::to_one_time_storage, with `source` its options; not in items).
void grant(ext::Ctx& ctx, const Grant& what, Granted& granted, storage::EquipSource source = storage::EquipSource::kOther);
// Where a new item came from, for its AddItem entry (CItemInfo's content_type / drop_type).
struct ItemSource {
    ContentType content_type = ContentType::kItem;
    u32 drop_type = 0;
};
// A new owned weapon or accessory `id` in the inventory (an `items` row, whatever the inventory
// holds) and its CItemInfo entry: an AddItem entry carries the content and drop types (`source`);
// the gacha's new_items entries (AddItem of a draw) carry neither (std::nullopt).
Value new_item(ext::Ctx& ctx, MasterItemId id, std::optional<ItemSource> source);
// Grants a content as ext::Ctx::grant does (drop type 0), expanding item sets (ContentType::kItemSet:
// the master_item_set rows, recursively). `free_coins`, when given, adds up the free coins
// (ContentType::kFreeCoin) granted, sets included.
void grant_with_item_sets(ext::Ctx& ctx, const Grant& what, Granted& granted, u32* free_coins = nullptr);
// A new character, or (c) a duplicate raises the owned one's limit break by one, up to
// (a) master_character_limit_break.target_limitbreak_max (10).
Added add_character(ext::Ctx& ctx, RoleId role);

}  // namespace soa::server
