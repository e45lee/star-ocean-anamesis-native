// The equipment storage (装備倉庫): GetStorageInfo, DepositItem, WithdrawItemFromStorage,
// SellItemsFromStorage, LockStorageItem / UnlockStorageItem (api/storage/storage.h). Port code, not
// guest behaviour. Rules in docs/server-rules.md#storage; labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// What the client keeps (b): StorageItem is an array of CStorageItemInfo (CItemInfo's keys plus
// update_at_time; CStorageItemInfo::Initialize @014ff30c) at CParameterManager+0x8a68;
// UpdateStorageItem a map {uid: CStorageItemInfo} (CUpdateStorageItemInfoList,
// IInfoBaseMap<u64, CStorageItemInfo>: an array isn't read, DeserializeArray @0166be20 returns 0; the
// key a number or a numeric string, InfoBaseNumberMap::ConvertParserValueToKey @0166c054).
// OnDepositItemRes applies it with CApiNotify::AddStorage (@014d437c: each entry joins the storage
// list and leaves the item list, by id); OnWithdrawItemFromStorageRes with DeleteStorage(false)
// (@014d4864: each entry goes back to the item list and leaves the storage); OnSellItemsFromStorageRes
// with DeleteStorage(true) (it leaves the storage only). UpdateStorageLockList is an array of u32 uids
// (CUpdateStorageLockList; OnLockStorageItemRes @014d58d0 sets is_lock on the storage entries whose
// id equals one, OnUnlockStorageItemRes @014d5c0c clears it).
//
// The state (schema version 15): a stored item keeps its `items` row with stored_at set (the time it
// was deposited), so its gear, its lock and the references to it stay as they are.
#include "api/storage/storage.h"

#include <set>

#include "api/items/items.h"            // item_equipped, stored_item_sale_fol
#include "api/player/player_info.h"     // item_info_list
#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "core/request_args.h"
#include "core/response.h"  // refusef
#include "soaserver/ext.h"

namespace soa::server {

namespace storage {

// (b) CItemStorage::GetStartStorageItemCount (@01f4623c): the storage's own slots.
constexpr u32 kStartStorageStock = 100;
// (a) master_subscription type_id 2: the Galaxy Pass's storage (subscmsg_gpass_warehouse_title).
constexpr u32 kSubscriptionTypeStorage = 2;

u32 item_stock(ext::Ctx& ctx) { return ctx.global_u32("item_stock_max", 500); }  // (a) master_global item_stock_max

u32 storage_stock(ext::Ctx& ctx) {
    // (b) the base 100; (a) + master_global subscription_storage_stock (400) while the pass's type 2 runs
    u32 extra = ext::subscription_active(ctx, kSubscriptionTypeStorage, ctx.now()) ? ctx.global_u32("subscription_storage_stock", 400) : 0;
    return kStartStorageStock + extra;
}

u32 inventory_count(ext::Ctx& ctx) { return (u32)ctx.st.one("select count(*) from items where stored_at is null", {}); }

}  // namespace storage

namespace {
using namespace ext;
using args::StorageItemsArgs;

u32 stored_count(Ctx& ctx) { return (u32)ctx.st.one("select count(*) from items where stored_at is not null", {}); }
bool is_stored(Ctx& ctx, ItemUid uid) { return ctx.st.one("select count(*) from items where uid = ? and stored_at is not null", {uid}) > 0; }

// The request's uids, each once (d: a uid sent twice counts once), in their order.
std::vector<ItemUid> distinct(const std::vector<ItemUid>& uids) {
    std::vector<ItemUid> out;
    std::set<u64> seen;
    for (ItemUid uid : uids)
        if (seen.insert(uid.v).second) out.push_back(uid);
    return out;
}

// StorageItem: the items of the equipment storage (CStorageItemInfo: CItemInfo's keys and
// update_at_time, player_info.cpp item_info_list).
Value storage_item_list(Ctx& ctx) { return item_info_list(ctx, "where stored_at is not null"); }

// One item as an UpdateStorageItem entry: its CItemInfo keys as the item lists send them (and
// update_at_time while it is stored).
Value storage_entry(Ctx& ctx, ItemUid uid) {
    Value list = item_info_list(ctx, "where uid = " + std::to_string(uid.v));
    return list.arr.empty() ? Value::object() : list.arr[0];
}

// GetStorageInfo() -> GetStorageInfoRes                                     fid 06669069
// API: docs/api.md#getstorageinfo   Rules: docs/server-rules.md#storage
//
// The equipment storage's contents, which CItemStorage::Setup asks for when the storage screens
// open (装備倉庫にしまう / 取り出す / 売却).
//   (b) OnGetStorageInfoRes is a plain apply: StorageItem replaces the client's storage list.
// Answers: the player state and StorageItem (every stored item).
std::vector<u8> get_storage_info(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["StorageItem"] = storage_item_list(ctx);
    LOGI("server", "GetStorageInfo: %zu items in the storage", data["StorageItem"].arr.size());
    return body(data);
}

// DepositItem(vector<u64> uids) -> DepositItemRes                           fid c4cd3b1a
// API: docs/api.md#deposititem   Rules: docs/server-rules.md#storage
//
// Moves items from the inventory into the equipment storage (倉庫にしまう).
//   (b) the deposit list leaves out equipped items (CItemStorage::GetAllItemList @01f409a4: an item
//   with is_equip, or one a party set holds): (b)+(a) an equipped one is refused with
//   kEquippedItem (10203 装備中のアイテムが含まれています).
//   (b) a locked item may be deposited and keeps its lock (AddStorage copies the whole CItemInfo).
//   (b)+(a) the storage holds storage_stock items (the client's own check, uimsg_equipstorage_itemmax_error
//   倉庫装備所持数の上限を超えて...): more is refused with kStorageShort (10211 倉庫枠が不足しています).
//   (d) an item that isn't in the inventory (unknown, or stored already) is refused with
//   kInvalidOperation (10403 不正なデータ処理です).
// Answers: the player state and UpdateStorageItem {uid: CStorageItemInfo} of the deposited items.
std::vector<u8> deposit_item(Ctx& ctx, const Request& req) {
    const std::vector<ItemUid> uids = distinct(StorageItemsArgs::from(req).uids);
    for (ItemUid uid : uids) {
        if (!owns_item(ctx, uid))
            return refusef(ctx, "DepositItem", ErrorCode::kInvalidOperation, "item %llu isn't in the inventory", (unsigned long long)uid.v);
        if (item_equipped(ctx, uid)) return refusef(ctx, "DepositItem", ErrorCode::kEquippedItem, "item %llu is equipped", (unsigned long long)uid.v);
    }
    const u32 cap = storage::storage_stock(ctx), held = stored_count(ctx);
    if (held + uids.size() > cap)
        return refusef(ctx, "DepositItem", ErrorCode::kStorageShort, "the storage holds %u of %u; %zu more don't fit", held, cap, uids.size());
    Value updated = Value::object();
    for (ItemUid uid : uids) {
        ctx.st.q("update items set stored_at = ? where uid = ?", {ctx.now(), uid});
        updated[std::to_string(uid.v)] = storage_entry(ctx, uid);
    }
    Value data = ctx.base_data();
    data["UpdateStorageItem"] = updated;
    LOGI("server", "DepositItem: %zu items into the storage (%zu of %u)", uids.size(), held + uids.size(), cap);
    return body(data);
}

// WithdrawItemFromStorage(vector<u64> uids) -> WithdrawItemFromStorageRes   fid de86bab0
// API: docs/api.md#withdrawitemfromstorage   Rules: docs/server-rules.md#storage
//
// Moves items from the equipment storage back into the inventory (倉庫から取り出す).
//   (b)+(a) the inventory holds item_stock items (the client's own check,
//   uimsg_equipstorage_out_itemmax_error 装備所持数の上限を超えて...): more is refused with
//   kEquipSlotsShort (10202 装備アイテム所持枠が不足しています).
//   (a) a storage over its slots (a pass that ended) still lets items out
//   (subscmsg_gpass_warehouse_manual: 取り出すことと売却することは可能).
//   (d) an item that isn't stored is refused with kInvalidOperation (10403).
// Answers: the player state and UpdateStorageItem {uid: CItemInfo} of the withdrawn items.
std::vector<u8> withdraw_item_from_storage(Ctx& ctx, const Request& req) {
    const std::vector<ItemUid> uids = distinct(StorageItemsArgs::from(req).uids);
    for (ItemUid uid : uids)
        if (!is_stored(ctx, uid))
            return refusef(ctx, "WithdrawItemFromStorage", ErrorCode::kInvalidOperation, "item %llu isn't in the storage", (unsigned long long)uid.v);
    const u32 cap = storage::item_stock(ctx), held = storage::inventory_count(ctx);
    if (held + uids.size() > cap)
        return refusef(ctx, "WithdrawItemFromStorage", ErrorCode::kEquipSlotsShort, "the inventory holds %u of %u; %zu more don't fit", held, cap,
                       uids.size());
    Value updated = Value::object();
    for (ItemUid uid : uids) {
        ctx.st.q("update items set stored_at = null where uid = ?", {uid});
        updated[std::to_string(uid.v)] = storage_entry(ctx, uid);
    }
    Value data = ctx.base_data();
    data["UpdateStorageItem"] = updated;
    LOGI("server", "WithdrawItemFromStorage: %zu items back to the inventory", uids.size());
    return body(data);
}

// SellItemsFromStorage(vector<u64> uids) -> SellItemsFromStorageRes        fid 81416fa8
// API: docs/api.md#sellitemsfromstorage   Rules: docs/server-rules.md#storage
//
// Sells stored items for FOL (倉庫から売却).
//   (b) each pays what SellItem pays for it (api/items/items.h stored_item_sale_fol:
//   CParameterUtility::tItemData::SellingPrice); (a) the FOL is capped at master_global
//   item_fol_max_num (core/wallet.h).
//   (d) a locked item can't be sold, as in the inventory: kLockedItem (10204); one that isn't
//   stored: kInvalidOperation (10403).
// Answers: the player state, UpdateStorageItem {uid: CStorageItemInfo} of the sold items (the
// client drops them: DeleteStorage(true)) and SellResult {total_fol, master_item_id, num, item_ids,
// StockItem, UpdateGearList} as SellItem's.
std::vector<u8> sell_items_from_storage(Ctx& ctx, const Request& req) {
    const std::vector<ItemUid> uids = distinct(StorageItemsArgs::from(req).uids);
    for (ItemUid uid : uids) {
        if (!is_stored(ctx, uid))
            return refusef(ctx, "SellItemsFromStorage", ErrorCode::kInvalidOperation, "item %llu isn't in the storage", (unsigned long long)uid.v);
        if (ctx.st.one("select locked from items where uid = ?", {uid}))
            return refusef(ctx, "SellItemsFromStorage", ErrorCode::kLockedItem, "item %llu is locked", (unsigned long long)uid.v);
    }
    u64 total = 0;
    Value updated = Value::object(), ids = Value::array();
    for (ItemUid uid : uids) {
        updated[std::to_string(uid.v)] = storage_entry(ctx, uid);
        total += stored_item_sale_fol(ctx, uid);
        ctx.st.q("delete from items where uid = ?", {uid});  // its gear goes with it (ON DELETE CASCADE)
        ids.push(uid.v);
    }
    add_fol(ctx, (int64_t)total);
    Value data = ctx.base_data();
    data["UpdateStorageItem"] = updated;
    Value result = Value::object();  // CSellResultInfo, as SellItem's
    result["total_fol"] = (u32)total;
    result["master_item_id"] = 0u;
    result["num"] = 0u;
    result["item_ids"] = ids;
    result["StockItem"] = Value::object();
    result["UpdateGearList"] = Value::array();
    data["SellResult"] = result;
    LOGI("server", "SellItemsFromStorage: +%llu FOL (%zu items)", (unsigned long long)total, uids.size());
    return body(data);
}

// LockStorageItem(vector<u64> uids) -> LockStorageItemRes                   fid b398671e
//   (UnlockStorageItem, fid b28403c2: the same with the lock off)
// API: docs/api.md#lockstorageitem, docs/api.md#unlockstorageitem   Rules: docs/server-rules.md#storage
//
// Sets or clears the lock of stored items (the item's own lock, items.locked).
//   (b) UpdateStorageLockList is read as u32s compared with the u64 uid (OnLockStorageItemRes
//   @014d58d0): the uids (the local uids fit in 32 bits, core/ids.h kItemUid0).
//   (d) uids that aren't stored change nothing and aren't listed; no refusal (as LockItem).
// Answers: the player state and UpdateStorageLockList [uid] of the stored items it changed.
std::vector<u8> lock_storage_item(Ctx& ctx, const Request& req) {
    const bool on = req.method == "LockStorageItem";
    Value changed = Value::array();
    for (ItemUid uid : distinct(StorageItemsArgs::from(req).uids)) {
        if (!is_stored(ctx, uid)) continue;
        ctx.st.q("update items set locked = ? where uid = ?", {on ? 1 : 0, uid});
        changed.push((u32)uid.v);
    }
    Value data = ctx.base_data();
    data["UpdateStorageLockList"] = changed;
    LOGI("server", "%s: %zu stored items", req.method.c_str(), changed.arr.size());
    return body(data);
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order"). The overflow box's: api/storage/one_time.cpp.
void register_storage() {
    ext::add_api({"GetStorageInfo"}, get_storage_info);
    ext::add_api({"DepositItem"}, deposit_item);
    ext::add_api({"WithdrawItemFromStorage"}, withdraw_item_from_storage);
    ext::add_api({"SellItemsFromStorage"}, sell_items_from_storage);
    ext::add_api({"LockStorageItem", "UnlockStorageItem"}, lock_storage_item);
    register_one_time_storage();
}

}  // namespace soa::server
