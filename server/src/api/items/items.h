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

// Whether a character wears the item (roster.weapon_uid / accessory_uid). A party set's own
// equipment (party_member) isn't looked at: PLAN-schema S5/S6.
bool item_equipped(ext::Ctx& ctx, ItemUid item_uid);

}  // namespace soa::server
