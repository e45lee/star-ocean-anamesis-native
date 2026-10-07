// Unit tests of the equipment storage and the overflow box (api/storage/storage.cpp, one_time.cpp;
// docs/server-rules.md#storage), on a scratch server seeded from the test seed save with the 3.7.0
// master. Run in --selftest; not differential (the server has no guest counterpart).
#include <set>
#include <string>

#include "core/errors.h"
#include "core/request_context.h"
#include "api/storage/storage.h"
#include "soa/chash32.h"
#include "soaserver/ext.h"
#include "soaserver/native_test.h"

namespace soa::server {
namespace {
using namespace ext;

std::vector<u8> call(Ctx& c, const char* method, std::vector<u64> ints, std::vector<std::vector<u64>> vecs = {}) {
    const Handler* h = find(method);
    if (!h) return {};
    Request r;
    r.method = method;
    r.ints = std::move(ints);
    r.vecs = std::move(vecs);
    return (*h)(c, r);
}
// The answer's data (Nil when there is none).
Value data_of(const std::vector<u8>& b) {
    if (b.empty()) return Value();
    Value v = mp_decode(b);
    const Value* d = v.find("data");
    return d ? *d : Value();
}
// A weapon of the master (rarity 3, sold for FOL).
u32 a_weapon(Ctx& c) { return (u32)c.m.one("select id from master_item where type = 1 and rarity = 3 and sale_fol > 0 order by id limit 1", {}); }
// `n` new weapons in the inventory, by the core's grant (AddItem entries' uids).
std::vector<u64> grant_weapons(Ctx& c, u32 n) {
    Value items = Value::array(), stocks = Value::array(), chars = Value::array();
    c.grant(1, a_weapon(c), n, items, stocks, chars);
    std::vector<u64> uids;
    for (auto& e : items.arr) uids.push_back(e.get_u("id"));
    return uids;
}
// Fills the inventory up to item_stock with plain weapon rows.
void fill_inventory(Ctx& c) {
    u32 have = storage::inventory_count(c), cap = storage::item_stock(c);
    u64 uid = (u64)c.st.one("select ifnull(max(uid), 0) + 1 from items", {});
    for (u32 k = have; k < cap; k++, uid++)
        c.st.q("insert into items (uid, master_item_id, item_type, created_at) values (?, ?, 1, 0)", {uid, a_weapon(c)});
}
std::set<u64> ids_in(const Value* list) {
    std::set<u64> out;
    if (list)
        for (auto& e : list->arr) out.insert(e.get_u("id"));
    return out;
}

// DepositItem / GetStorageInfo / WithdrawItemFromStorage: the items move between Item and
// StorageItem (update_at_time while stored); an equipped item, a full storage, an item not in the
// inventory and a full inventory are refused with their codes; stored items can't be equipped,
// sold or composed from the inventory's APIs.
NATIVE_TEST("storage/deposit-withdraw") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        std::vector<u64> w = grant_weapons(c, 3);
        if (w.size() != 3) return t.fail("granted %zu weapons", w.size());
        // deposit two
        Value d = data_of(call(c, "DepositItem", {}, {{w[0], w[1]}}));
        t.expect_eq(code, 0u, "deposit accepted");
        const Value* upd = d.find("UpdateStorageItem");
        t.expect_eq(upd && upd->find(std::to_string(w[0])) && upd->find(std::to_string(w[1])), true, "UpdateStorageItem keyed by uid");
        t.expect_eq(upd && upd->find(std::to_string(w[0]))->find("update_at_time") != nullptr, true, "a stored entry has update_at_time");
        Value items = c.items();
        std::set<u64> inv = ids_in(&items);
        t.expect_eq(inv.count(w[0]) + inv.count(w[1]), (size_t)0, "deposited items left Item");
        t.expect_eq(inv.count(w[2]), (size_t)1, "the third stays in Item");
        Value s = data_of(call(c, "GetStorageInfo", {}));
        std::set<u64> st = ids_in(s.find("StorageItem"));
        t.expect_eq(st == std::set<u64>{w[0], w[1]}, true, "StorageItem lists the stored items");
        // refusals: stored already / unknown (10403), equipped (10203)
        code = 0;
        call(c, "DepositItem", {}, {{w[0]}});
        t.expect_eq(code, (u32)ErrorCode::kInvalidOperation, "a stored item isn't deposited again");
        u64 equipped = w[2];
        c.st.q("update roster set weapon_uid = ? where uid = (select min(uid) from roster)", {equipped});
        code = 0;
        call(c, "DepositItem", {}, {{equipped}});
        t.expect_eq(code, (u32)ErrorCode::kEquippedItem, "an equipped item is refused");
        c.st.q("update roster set weapon_uid = null where weapon_uid = ?", {equipped});
        // a stored item can't be equipped or sold from the inventory
        code = 0;
        Request eq;
        eq.method = "EquipWeapon";
        eq.ints = {(u64)c.st.one("select min(uid) from roster", {}), w[0]};
        if (const Handler* h = find("EquipWeapon")) (*h)(c, eq);
        t.expect_eq(code != 0, true, "a stored weapon can't be equipped");
        code = 0;
        call(c, "SellItemArray", {}, {{w[0]}});
        t.expect_eq(code, (u32)ErrorCode::kLockedItem, "a stored item isn't sold from the inventory");
        t.expect_eq(c.st.one("select count(*) from items where uid = ?", {w[0]}), (int64_t)1, "still owned");
        // the storage's slots: 100 without the pass
        t.expect_eq(storage::storage_stock(c), 100u, "storage_stock without the pass");
        std::vector<u64> more = grant_weapons(c, 99);
        code = 0;
        call(c, "DepositItem", {}, {more});
        t.expect_eq(code, (u32)ErrorCode::kStorageShort, "101 items don't fit 100 slots");
        t.expect_eq(c.st.one("select count(*) from items where stored_at is not null", {}), (int64_t)2, "nothing deposited");
        more.pop_back();
        code = 0;
        call(c, "DepositItem", {}, {more});
        t.expect_eq(code, 0u, "100 items fit");
        // withdraw one; a full inventory refuses the next (10202)
        code = 0;
        Value wd = data_of(call(c, "WithdrawItemFromStorage", {}, {{w[0]}}));
        t.expect_eq(code, 0u, "withdraw accepted");
        t.expect_eq(wd.find("UpdateStorageItem") && wd.find("UpdateStorageItem")->find(std::to_string(w[0])), true, "UpdateStorageItem of the item");
        items = c.items();
        t.expect_eq(ids_in(&items).count(w[0]), (size_t)1, "back in Item");
        fill_inventory(c);
        code = 0;
        call(c, "WithdrawItemFromStorage", {}, {{w[1]}});
        t.expect_eq(code, (u32)ErrorCode::kEquipSlotsShort, "no room in the inventory");
        code = 0;
        call(c, "WithdrawItemFromStorage", {}, {{w[2]}});
        t.expect_eq(code, (u32)ErrorCode::kInvalidOperation, "an item that isn't stored");
        c.st.exec("commit");
    });
    if (!ran) return;
}

// LockStorageItem / UnlockStorageItem / SellItemsFromStorage: the lock is the item's; a locked
// item isn't sold; a sale pays what SellItem pays (the same weapon sold from the inventory) and
// answers SellResult and UpdateStorageItem.
NATIVE_TEST("storage/sell-lock") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        std::vector<u64> w = grant_weapons(c, 3);
        call(c, "DepositItem", {}, {{w[0], w[1]}});
        Value l = data_of(call(c, "LockStorageItem", {}, {{w[0], w[2]}}));
        const Value* list = l.find("UpdateStorageLockList");
        t.expect_eq(list && list->arr.size() == 1 && list->arr[0].u == (w[0] & 0xffffffffu), true, "only the stored item is listed, as a u32");
        t.expect_eq(c.st.one("select locked from items where uid = ?", {w[0]}), (int64_t)1, "locked");
        t.expect_eq(c.st.one("select locked from items where uid = ?", {w[2]}), (int64_t)0, "an inventory item isn't touched");
        u32 before = ext::fol(c);
        code = 0;
        call(c, "SellItemsFromStorage", {}, {{w[0]}});
        t.expect_eq(code, (u32)ErrorCode::kLockedItem, "a locked item isn't sold");
        t.expect_eq(ext::fol(c), before, "no FOL");
        call(c, "UnlockStorageItem", {}, {{w[0]}});
        t.expect_eq(c.st.one("select locked from items where uid = ?", {w[0]}), (int64_t)0, "unlocked");
        // the inventory's price of the same weapon
        u32 f0 = ext::fol(c);
        call(c, "SellItemArray", {}, {{w[2]}});
        u32 price = ext::fol(c) - f0;
        code = 0;
        Value s = data_of(call(c, "SellItemsFromStorage", {}, {{w[0], w[1]}}));
        t.expect_eq(code, 0u, "sale accepted");
        t.expect_eq(ext::fol(c), f0 + 3 * price, "each pays the inventory's price");
        const Value* r = s.find("SellResult");
        t.expect_eq(r && r->get_u("total_fol") == 2 * price, true, "SellResult.total_fol");
        t.expect_eq(s.find("UpdateStorageItem") && s.find("UpdateStorageItem")->map.size() == 2, true, "UpdateStorageItem of the sold items");
        t.expect_eq(c.st.one("select count(*) from items where uid in (?, ?)", {w[0], w[1]}), (int64_t)0, "sold");
        c.st.exec("commit");
    });
    if (!ran) return;
}

// Player.storage_stock: 100, and 100 + master_global subscription_storage_stock while the Galaxy
// Pass (its master_subscription type 2) runs.
NATIVE_TEST("storage/stock-caps") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        t.expect_eq(storage::storage_stock(c), 100u, "without the pass");
        u32 plan = (u32)c.m.one("select plan_id from master_subscription where type_id = 2 order by plan_id limit 1", {});
        c.st.q("insert into subscription (plan_id, opened_at, closed_at, updated_at) values (?, ?, ?, ?)",
               {plan, c.now().v - 10, c.now().v + 86400, c.now().v});
        t.expect_eq(storage::storage_stock(c), 100u + c.global_u32("subscription_storage_stock", 0), "with the pass");
        t.expect_eq((u32)c.base_data().find("Player")->get_u("storage_stock"), storage::storage_stock(c), "Player.storage_stock");
        c.st.exec("commit");
    });
    if (!ran) return;
}

// The overflow box: with the inventory full a granted weapon goes to the box (not AddItem; the
// request's AddOneTimeStorageInfo), one row per master item with its count; GetOneTimeStorageInfo
// lists it (unique update_at_time); ClearNew clears the badge; withdrawing is refused with no room
// (10202) or more than the box holds (10206), and takes items out as new ones (AddItem,
// UpdateOneTimeStorageItem with the count left, 0 when gone); Bulk adds a repeated id's counts.
NATIVE_TEST("storage/one-time") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        u32 weapon = a_weapon(c);
        u32 other = (u32)c.m.one("select id from master_item where type = 1 and rarity = 3 and id != ? order by id limit 1", {weapon});
        t.expect_eq(storage::to_one_time_storage(c, storage::EquipSource::kOther), false, "room in the inventory");
        fill_inventory(c);
        t.expect_eq(storage::to_one_time_storage(c, storage::EquipSource::kGacha), true, "full");
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        c.grant(1, weapon, 3, items, stocks, chars);
        c.grant(1, other, 1, items, stocks, chars);
        t.expect_eq(items.arr.size(), (size_t)0, "no AddItem");
        t.expect_eq(storage::inventory_count(c), storage::item_stock(c), "the inventory stays at its slots");
        t.expect_eq(c.st.one("select num from one_time_storage where master_item_id = ?", {weapon}), (int64_t)3, "one row with the count");
        t.expect_eq(c.request->one_time_added.size(), (size_t)4, "AddOneTimeStorageInfo: one per unit");
        c.request->one_time_added.clear();
        Value g = data_of(call(c, "GetOneTimeStorageInfo", {}));
        const Value* box = g.find("OneTimeStorageItem");
        t.expect_eq(box && box->arr.size() == 2, true, "two entries");
        if (box && box->arr.size() == 2) {
            t.expect_eq(box->arr[0].get_u("update_at_time") != box->arr[1].get_u("update_at_time"), true, "unique update_at_time");
            t.expect_eq(box->arr[0].get_u("num") + box->arr[1].get_u("num"), (u64)4, "the counts");
        }
        Value cn = data_of(call(c, "ClearNewOneTimeStorageItem", {}, {{weapon, 12345}}));
        t.expect_eq(cn.find("OneTimeStorageItemClearNewList") && cn.find("OneTimeStorageItemClearNewList")->arr.size() == 1, true,
                    "the held id listed");
        t.expect_eq(c.st.one("select is_new from one_time_storage where master_item_id = ?", {weapon}), (int64_t)0, "badge cleared");
        // no room
        code = 0;
        call(c, "WithdrawItemFromOneTimeStorage", {weapon, 1});
        t.expect_eq(code, (u32)ErrorCode::kEquipSlotsShort, "the inventory is full");
        c.st.q("delete from items where uid in (select uid from items where stored_at is null order by uid desc limit 10)", {});
        code = 0;
        call(c, "WithdrawItemFromOneTimeStorage", {weapon, 4});
        t.expect_eq(code, (u32)ErrorCode::kItemCountError, "more than the box holds");
        code = 0;
        Value wd = data_of(call(c, "WithdrawItemFromOneTimeStorage", {weapon, 2}));
        t.expect_eq(code, 0u, "withdraw accepted");
        t.expect_eq(wd.find("AddItem") && wd.find("AddItem")->map.size() == 2, true, "two new items, keyed by uid");
        const Value* up = wd.find("UpdateOneTimeStorageItem");
        t.expect_eq(up && up->find(std::to_string(weapon)) && up->find(std::to_string(weapon))->get_u("num") == 1, true, "one left");
        // Bulk: the same id twice counts together; the other one taken whole
        code = 0;
        Request b;
        b.method = "BulkWithdrawItemFromOneTimeStorage";
        b.vecs = {{weapon, other, weapon}, {1, 1, 1}};
        call(c, b.method.c_str(), {}, b.vecs);
        t.expect_eq(code, (u32)ErrorCode::kItemCountError, "two of one held");
        code = 0;
        Value bw = data_of(call(c, b.method.c_str(), {}, {{weapon, other}, {1, 1}}));
        t.expect_eq(code, 0u, "bulk accepted");
        const Value* bu = bw.find("UpdateOneTimeStorageItem");
        t.expect_eq(bu && bu->map.size() == 2 && bu->find(std::to_string(other))->get_u("num") == 0, true, "taken whole: num 0");
        t.expect_eq(c.st.one("select count(*) from one_time_storage", {}), (int64_t)0, "the box empty");
        c.st.exec("commit");
    });
    if (!ran) return;
}

// The player's options (その他設定, api/settings/config.h) send equipment to the overflow box with
// room in the inventory: is_one_time_storage the gacha's, is_one_time_storage_except_gacha the rest.
NATIVE_TEST("storage/one-time-options") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        auto set = [&](const char* label, const char* v) {
            const Handler* h = find("UpdateConfig");
            Request r;
            r.method = "UpdateConfig";
            r.ints = {(u64)chash32(label), 4};
            r.strs = {v};
            if (h) (*h)(c, r);
        };
        using storage::EquipSource;
        t.expect_eq(storage::to_one_time_storage(c, EquipSource::kGacha), false, "the defaults: the inventory");
        set("is_one_time_storage", "true");
        t.expect_eq(storage::to_one_time_storage(c, EquipSource::kGacha), true, "一時保管庫設定 on: the gacha's to the box");
        t.expect_eq(storage::to_one_time_storage(c, EquipSource::kOther), false, "the rest still to the inventory");
        set("is_one_time_storage_except_gacha", "true");
        t.expect_eq(storage::to_one_time_storage(c, EquipSource::kOther), true, "the other option on: the rest to the box");
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        c.grant(1, a_weapon(c), 1, items, stocks, chars);
        t.expect_eq(items.arr.size(), (size_t)0, "a granted weapon went to the box");
        t.expect_eq(c.st.one("select ifnull(sum(num), 0) from one_time_storage", {}), (int64_t)1, "in the box");
        c.st.exec("rollback");
    });
    if (!ran) t.fail("no scratch server");
}

}  // namespace
}  // namespace soa::server
