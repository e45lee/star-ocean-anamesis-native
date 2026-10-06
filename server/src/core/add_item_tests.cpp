// AddItem's shape (ext::add_items, core/ext.cpp): (b) CAddItemList is an IInfoBaseMap<u64,
// CItemInfo> whose DeserializeArray (@0163d574) returns 0, so every response sends its new items
// as a map {uid (a string): CItemInfo}. --selftest "server/add-item-map".
#include <string>

#include "soaserver/ext.h"
#include "soaserver/native_test.h"

namespace soa::server {
namespace {

NATIVE_TEST("server/add-item-map") {
    // the helper: keyed by the uid as a string, merged across calls, nothing for no items
    Value data = Value::object();
    ext::add_items(data, Value::array());
    t.expect_eq(data.find("AddItem") != nullptr, false, "no AddItem for no items");
    Value items = Value::array();
    for (u64 uid : {0x7d000001ull, 0x7d000002ull}) {
        Value e = Value::object();
        e["id"] = uid;
        e["master_item_id"] = 1u;
        items.push(e);
    }
    ext::add_items(data, items);
    Value more = Value::array();
    Value e = Value::object();
    e["id"] = 0x7d000003ull;
    more.push(e);
    ext::add_items(data, more);
    const Value* add = data.find("AddItem");
    t.expect_eq(add && add->type == Value::Map, true, "AddItem is a map");
    if (!add || add->type != Value::Map) return;
    t.expect_eq(add->map.size(), (size_t)3, "three entries");
    const Value* first = add->find(std::to_string(0x7d000001ull));
    t.expect_eq(first ? (u64)first->get_u("id") : 0ull, 0x7d000001ull, "keyed by the uid");

    // a MissionEnd extra's drop (ext::add_drop) of two weapons: two AddItem entries under their uids
    bool ran = ext::with_scratch_server(t.rand_u64(), [&](ext::Ctx& ctx) {
        ctx.st.exec("begin");
        const u32 weapon = (u32)ctx.m.one("select id from master_item where type = 1 order by id limit 1", {});
        Value d = Value::object();
        ext::add_drop(ctx, d, 1, weapon, 2, 0);
        const Value* a = d.find("AddItem");
        t.expect_eq(a && a->type == Value::Map ? a->map.size() : (size_t)0, (size_t)2, "two weapons in the AddItem map");
        if (a && a->type == Value::Map)
            for (const auto& [key, item] : a->map) {
                t.expect_eq(key, std::to_string(item.get_u("id")), "the key is the item's uid");
                t.expect_eq(ctx.st.one("select count(*) from items where uid = ?", {(int64_t)item.get_u("id")}), (int64_t)1, "an owned item");
            }
        ctx.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master (data/basmaster-3.7.0.sqlite3) and the test seed");
}

}  // namespace
}  // namespace soa::server
