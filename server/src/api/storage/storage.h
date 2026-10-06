#pragma once
// The equipment storage (装備倉庫) and the overflow box (一時保管庫): what the rest of the server
// asks of them (api/storage/storage.cpp, api/storage/one_time.cpp; port code, not guest
// behaviour). Rules in docs/server-rules.md#storage; labels: (a) master data, (b) client-side
// evidence, (c) outside knowledge, (d) assumption.
#include "soaserver/ext.h"

namespace soa::server::storage {

// Where a new piece of equipment (a weapon or an accessory) comes from, for the overflow box's
// options: a gacha draw, or anything else (presents, mission drops, the shops, the exchange).
enum class EquipSource { kGacha, kOther };

// Player.item_stock: the inventory's equipment slots (装備所持枠). (a) master_global item_stock_max.
u32 item_stock(ext::Ctx& ctx);
// Player.storage_stock: the equipment storage's slots (倉庫装備所持).
//   (b) CItemStorage::GetMaxStorageItemCount (@01f45f50) reads it (CParameterManager+0x948, CPlayerInfo
//   storage_stock); the client counts the first GetStartStorageItemCount (@01f4623c) = 100 as the
//   base and shows the rest as an extension (GetExtendStorageItemCount @01f437c4).
//   (a) the Galaxy Pass's type 2 (master_subscription "subscmsg_gpass_warehouse_title":
//   倉庫装備所持数＋４００個) adds master_global subscription_storage_stock (400) while it runs.
u32 storage_stock(ext::Ctx& ctx);
// The equipment in the inventory (owned weapons and accessories not in the equipment storage):
// (b) CUIUtility::GetEquipItemCount (@01edfd44), the client's item list.
u32 inventory_count(ext::Ctx& ctx);

// Whether one more piece of equipment from `source` goes to the overflow box instead of the
// inventory: (b) when the inventory is full, CItemNumWarning::IsWarningDraw (@01b42884): the
// equipment count + 1 > item_stock (a: master_text cp0003_tutorial_160 and the uimsg_*_itemmax
// texts: equipment beyond the slots goes to the box). The player's 一時保管庫設定 options
// (master_config is_one_time_storage for gacha draws, is_one_time_storage_except_gacha for the
// rest; CUIUtility::IsOneTimeStorageEnable @01eea5f8 / IsOneTimeStorageExceptGachaEnable
// @01eea8e0) send every piece to the box while on; they are GetConfig / UpdateConfig's and plug in
// here (see one_time.cpp).
bool to_one_time_storage(ext::Ctx& ctx, EquipSource source);
// Puts `num` of the master item `id` in the overflow box (its row's count; new, and changed now)
// and lists each unit in the request's AddOneTimeStorageInfo (RequestContext::one_time_added).
void add_one_time(ext::Ctx& ctx, MasterItemId id, u32 num);

}  // namespace soa::server::storage
