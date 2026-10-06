// The overflow box (一時保管庫): GetOneTimeStorageInfo, WithdrawItemFromOneTimeStorage,
// BulkWithdrawItemFromOneTimeStorage, ClearNewOneTimeStorageItem; filling it (to_one_time_storage,
// add_one_time) and reporting what a request put in it (AddOneTimeStorageInfo). Port code, not guest
// behaviour (api/storage/storage.h). Rules in docs/server-rules.md#storage; labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// What the client keeps (b): OneTimeStorageItem is an array of CStorageItemInfo
// (COneTimeStorageItemInfoList, CParameterManager+0x8ab8); UpdateOneTimeStorageItem a map {key:
// CStorageItemInfo} (CUpdateOneTimeStorageItemInfoList, an IInfoBaseMap<u64, CStorageItemInfo>);
// CApiNotify::DeleteOneTimeStorage (@014d4e44, run by both withdraw answers before AddItem) finds
// each entry's box entry by master_item_id (CItemInfo+0xc0) and removes it when the entry's num is
// 0, else takes its num, is_new and update_at_time. So the box holds one entry per master item, with
// a count (num). OneTimeStorageItemClearNewList (COneTimeStorageItemClearNewList) is an array of u32
// master item ids whose is_new OnClearNewOneTimeStorageItemRes (@014d5598) clears;
// AddOneTimeStorageInfo (CAddOneTimeStorageInfo, one object at CParameterManager+0x4760, also the
// present receipt's PresentGetResult.result.AddOneTimeStorageInfo) an array of u32.
// The box screen shows a box entry by update_at_time: CItemStorage::ItemInfo's constructor
// (@01f46244) puts it where the other lists keep the item's id, and the sort
// (CUISort::SortFilter_Weapon<CItemStorage::ItemInfo> @01f438ac) finds the entries by it, so (d)
// each row's time is unique (one second after the latest when two would be equal).
#include <algorithm>
#include <map>

#include "api/player/player_info.h"  // player_id
#include "api/settings/config.h"
#include "api/storage/storage.h"
#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "core/request_args.h"
#include "core/request_context.h"
#include "core/response.h"  // refusef
#include "core/rewards.h"   // new_item
#include "soaserver/ext.h"

namespace soa::server {

namespace storage {

bool to_one_time_storage(ext::Ctx& ctx, EquipSource source) {
    // The player's options (その他設定, api/settings/config.h): (b) with master_config
    // is_one_time_storage on (CUIUtility::IsOneTimeStorageEnable, 一時保管庫設定) every gacha draw's
    // equipment goes to the box, with is_one_time_storage_except_gacha on
    // (IsOneTimeStorageExceptGachaEnable) every other source's (the screen's texts).
    if (settings::config_on(ctx, source == EquipSource::kGacha ? settings::kOneTimeStorage : settings::kOneTimeStorageExceptGacha)) return true;
    // (b) the inventory is full: the equipment count + 1 > item_stock (CItemNumWarning::IsWarningDraw)
    return inventory_count(ctx) >= item_stock(ctx);
}

void add_one_time(ext::Ctx& ctx, MasterItemId id, u32 num) {
    if (!num) return;
    // (d) a time no other row has (the box screen tells its entries apart by it; above)
    int64_t stamp = std::max<int64_t>(ctx.now().v, ctx.st.one("select ifnull(max(updated_at), 0) + 1 from one_time_storage", {}));
    ctx.st.q(
        "insert into one_time_storage (master_item_id, num, is_new, updated_at) values (?, ?, 1, ?) "
        "on conflict(master_item_id) do update set num = num + excluded.num, is_new = 1, updated_at = excluded.updated_at",
        {id, num, stamp});
    for (u32 k = 0; k < num; k++) ctx.request->one_time_added.push_back(id);
    LOGI("server", "overflow box: +%u of item %u (the inventory holds %u of %u)", num, id.v, inventory_count(ctx), item_stock(ctx));
}

}  // namespace storage

namespace {
using namespace ext;

// A box row as a CStorageItemInfo: CItemInfo's keys as the item lists send them, for a new piece of
// equipment (level 1, nothing boosted, unlocked, not equipped), its count (num), the "new" badge and
// update_at_time. (d) id is the master item id: the box's entries have no uid (the client matches
// them by master_item_id).
Value one_time_entry(Ctx& ctx, MasterItemId id, u32 num, bool is_new, int64_t updated_at) {
    Value info = Value::object();
    info["id"] = (u64)id.v;
    info["player_id"] = player_id(ctx).v;
    info["master_item_id"] = id.v;
    info["item_type"] = (u32)ctx.m.one("select type from master_item where id = ?", {id});
    info["boosted_point"] = 0u;
    info["limit_break_count"] = 0u;
    info["level"] = 1u;
    info["is_lock"] = false;
    info["is_equip"] = false;
    info["num"] = num;
    info["is_new"] = is_new;
    info["update_at_time"] = (u64)updated_at;
    return info;
}

// OneTimeStorageItem: every box row, by master item id.
Value one_time_list(Ctx& ctx) {
    Value list = Value::array();
    ctx.st.q("select * from one_time_storage order by master_item_id", {}, [&](const Row& row) {
        list.push(one_time_entry(ctx, row.id<MasterItemId>("master_item_id"), (u32)row.i("num"), row.i("is_new") != 0, row.i("updated_at")));
    });
    return list;
}

// GetOneTimeStorageInfo() -> GetOneTimeStorageInfoRes                       fid 074df139
// API: docs/api.md#getonetimestorageinfo   Rules: docs/server-rules.md#storage
//
// The overflow box's contents, which CItemStorage::Setup asks for when 一時保管庫から取り出す opens.
//   (b) OnGetOneTimeStorageInfoRes is a plain apply: OneTimeStorageItem replaces the client's list.
// Answers: the player state and OneTimeStorageItem (one entry per master item, with its count).
std::vector<u8> get_one_time_storage_info(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["OneTimeStorageItem"] = one_time_list(ctx);
    LOGI("server", "GetOneTimeStorageInfo: %zu entries in the overflow box", data["OneTimeStorageItem"].arr.size());
    return body(data);
}

// WithdrawItemFromOneTimeStorage(u32 id, u32 count) -> ...Res                fid aa6a1d11
// BulkWithdrawItemFromOneTimeStorage(vector<u32> ids, vector<u32> counts) -> ...Res  fid 59f02ddd
// API: docs/api.md#withdrawitemfromonetimestorage, docs/api.md#bulkwithdrawitemfromonetimestorage
// Rules: docs/server-rules.md#storage
//
// Takes equipment out of the overflow box into the inventory (取り出す): each unit becomes a new
// owned item.
//   (b) the ids are master item ids (the box's entries; DeleteOneTimeStorage matches them so).
//   (d) an id the box doesn't hold, a count of 0 or more than it holds: kItemCountError (10206
//   アイテムの所持数エラー); an id sent twice counts its counts together.
//   (b)+(a) the inventory holds item_stock items (uimsg_equipstorage_out_itemmax_error): more is
//   refused with kEquipSlotsShort (10202 装備アイテム所持枠が不足しています).
// Answers: the player state, UpdateOneTimeStorageItem {master id: CStorageItemInfo with the count
// left, 0 when none} and AddItem {uid: CItemInfo} (the new items).
std::vector<u8> withdraw_from_one_time_storage(Ctx& ctx, const Request& req) {
    std::map<u32, u64> want;  // master item id -> count
    std::vector<MasterItemId> order;
    for (const auto& [id, count] : args::OneTimeWithdrawArgs::from(req).takes) {
        if (!want.count(id.v)) order.push_back(id);
        want[id.v] += count;
    }
    u64 total = 0;
    for (MasterItemId id : order) {
        u64 held = (u64)ctx.st.one("select ifnull(sum(num), 0) from one_time_storage where master_item_id = ?", {id});
        if (!want[id.v] || want[id.v] > held)
            return refusef(ctx, req.method.c_str(), ErrorCode::kItemCountError, "item %u: %llu wanted, the box holds %llu", id.v,
                           (unsigned long long)want[id.v], (unsigned long long)held);
        total += want[id.v];
    }
    const u32 cap = storage::item_stock(ctx), have = storage::inventory_count(ctx);
    if (have + total > cap)
        return refusef(ctx, req.method.c_str(), ErrorCode::kEquipSlotsShort, "the inventory holds %u of %u; %llu more don't fit", have, cap,
                       (unsigned long long)total);
    // (b) AddItem is a map {uid: CItemInfo} (ext::add_items: CAddItemList, an IInfoBaseMap<u64,
    // CItemInfo>, whose DeserializeArray @0163d574 returns 0, an array isn't read);
    // CApiNotify::AddItem (@014c207c) adds each to the item list
    Value updated = Value::object(), added = Value::array();
    for (MasterItemId id : order) {
        u32 take = (u32)want[id.v];
        bool is_new = false;
        int64_t updated_at = 0;
        u32 left = 0;
        ctx.st.q("select * from one_time_storage where master_item_id = ?", {id}, [&](const Row& row) {
            left = (u32)row.i("num") - take;
            is_new = row.i("is_new") != 0;
            updated_at = row.i("updated_at");
        });
        if (left) ctx.st.q("update one_time_storage set num = ? where master_item_id = ?", {left, id});
        else ctx.st.q("delete from one_time_storage where master_item_id = ?", {id});
        updated[std::to_string(id.v)] = one_time_entry(ctx, id, left, is_new, updated_at);
        // (d) the new items' content type is a unique item's (1) and their drop type 0, as a present's
        for (u32 k = 0; k < take; k++) {
            added.push(new_item(ctx, id, 1, 0));
        }
    }
    Value data = ctx.base_data();
    data["UpdateOneTimeStorageItem"] = updated;
    ext::add_items(data, added);
    LOGI("server", "%s: %llu items from the overflow box", req.method.c_str(), (unsigned long long)total);
    return body(data);
}

// ClearNewOneTimeStorageItem(vector<u32> ids) -> ClearNewOneTimeStorageItemRes  fid d4f178a3
// API: docs/api.md#clearnewonetimestorageitem   Rules: docs/server-rules.md#storage
//
// Clears the box entries' "new" badge (CItemStorage::Progress sends the new entries when the box
// screen closes).
//   (b) the ids are master item ids; (d) ids the box doesn't hold change nothing and aren't listed.
// Answers: the player state and OneTimeStorageItemClearNewList [master id] of the entries cleared.
std::vector<u8> clear_new_one_time_storage_item(Ctx& ctx, const Request& req) {
    Value cleared = Value::array();
    for (MasterItemId id : args::OneTimeClearNewArgs::from(req).ids) {
        if (!ctx.st.one("select count(*) from one_time_storage where master_item_id = ?", {id})) continue;
        ctx.st.q("update one_time_storage set is_new = 0 where master_item_id = ?", {id});
        cleared.push(id.v);
    }
    Value data = ctx.base_data();
    data["OneTimeStorageItemClearNewList"] = cleared;
    LOGI("server", "ClearNewOneTimeStorageItem: %zu entries no longer new", cleared.arr.size());
    return body(data);
}

// OnResponse: AddOneTimeStorageInfo                    on any response that filled the overflow box
// Rules: docs/server-rules.md#storage
//
//   (b) AddOneTimeStorageInfo (CAddOneTimeStorageInfo) is an array of u32; (d) the master item id of
//   each unit the request put in the box (storage::add_one_time), at the top of the answer (the
//   client keeps one object for it, which PresentGetResult.result's key fills too; there as well).
// Adds: AddOneTimeStorageInfo (and PresentGetResult.result's) when the request filled the box.
bool report_one_time_added(Ctx& ctx, const Request&, Value& data) {
    std::vector<MasterItemId> added;
    added.swap(ctx.request->one_time_added);
    if (added.empty()) return false;
    Value list = Value::array();
    for (MasterItemId id : added) list.push(id.v);
    data["AddOneTimeStorageInfo"] = list;
    // and in a present receipt's result, where the client's schema lists it too (as AddTitleList's
    // titles, api/player/titles.cpp)
    if (Value* present_result = data.find_mut("PresentGetResult"); present_result && present_result->type == Value::Map) {
        Value& result = (*present_result)["result"];
        if (result.type != Value::Map) result = Value::object();
        result["AddOneTimeStorageInfo"] = list;
    }
    return true;
}

}  // namespace

// The overflow box's registrations (register_storage, api/storage/storage.cpp, calls this).
void register_one_time_storage() {
    ext::add_api({"GetOneTimeStorageInfo"}, get_one_time_storage_info);
    ext::add_api({"WithdrawItemFromOneTimeStorage", "BulkWithdrawItemFromOneTimeStorage"}, withdraw_from_one_time_storage);
    ext::add_api({"ClearNewOneTimeStorageItem"}, clear_new_one_time_storage_item);
    ext::add_response_hook(report_one_time_added);
}

}  // namespace soa::server
