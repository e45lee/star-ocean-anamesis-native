#pragma once
// What the item and gear modules share (api/items/items.cpp, api/items/gear.cpp; port code, not
// guest behaviour): the master_item types they test, the uid-list argument and the "equipped"
// check. Labels: (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

// master_item.type values the item APIs test (a: the master data; docs/api.md "Content types",
// where the same numbers name the content types).
namespace item_type {
constexpr u32 kWeapon = 1;      // a weapon (owned as an `items` row with a uid)
constexpr u32 kAccessory = 3;   // an accessory (an `items` row too)
constexpr u32 kHealItem = 10;   // a stamina heal item (heal_type / heal_point)
}  // namespace item_type

// The uid list of SellItem(Array), LockItem(Array), UnlockItem(Array), ClearNewGear, SellGear and
// GenerateGear's materials: the request's first vector, empty when none was sent.
inline std::vector<u64> uid_list(const Request& req) { return req.vecs.empty() ? std::vector<u64>{} : req.vecs[0]; }
// uid_list as item uids (SellItem(Array), LockItem(Array), UnlockItem(Array), ItemCompose /
// ItemGradeUp's materials); gear.cpp has its gear uid list (ClearNewGear, SellGear).
inline std::vector<ItemUid> item_uid_list(const Request& req) {
    std::vector<ItemUid> uids;
    for (u64 uid : uid_list(req)) uids.push_back(ItemUid(uid));
    return uids;
}

// Whether a character wears the item: its own equipment (roster.weapon_uid / accessory_uid) or a
// party set's for a member (party_member.weapon_uid / accessory_uid; PLAN-schema S6, d: the set's
// equipment is the member's, so the item is in use). Both references are ON DELETE SET NULL.
bool item_equipped(ext::Ctx& ctx, ItemUid item_uid);
// Whether the player owns the weapon or accessory in the inventory (an `items` row not in the
// equipment storage).
bool owns_item(ext::Ctx& ctx, ItemUid item_uid);
// What selling the item `item_uid` of the equipment storage pays: the inventory's sale rule
// (SellItem: (b) round(sale_fol x master_item_sale_rate[level].sale_rate) for a weapon, sale_fol for
// the rest); 0 when it isn't there.
u32 stored_item_sale_fol(ext::Ctx& ctx, ItemUid item_uid);

}  // namespace soa::server
