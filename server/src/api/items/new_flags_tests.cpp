// The NEW badges (api/items/new_flags.cpp; --selftest "items/new-badges"): what the seed holds is
// not new; a weapon, a character and a stack item granted later are, in the player state lists;
// ClearNewItem / ClearNewCharacter / ClearNewStackItem clear them and list what they cleared.
#include <string>
#include <vector>

#include "soaserver/ext.h"
#include "soaserver/msgpack.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

// The is_new of the entry with `key` == v in a list (-1: no such entry or no flag).
int flag_in(const Value& list, const char* key, u64 v) {
    for (const Value& e : list.arr) {
        const Value* k = e.find(key);
        if (k && k->u == v) {
            const Value* f = e.find("is_new");
            return f ? (int)f->u : -1;
        }
    }
    return -1;
}

std::vector<u8> call(ext::Ctx& ctx, const char* method, std::vector<u64> ids) {
    const ext::Handler* h = ext::find(method);
    if (!h) return {};
    Request r;
    r.method = method;
    r.vecs = {ids};
    return (*h)(ctx, r);
}

const Value* data_key(const Value& root, const char* k) {
    const Value* d = root.find("data");
    return d ? d->find(k) : nullptr;
}

NATIVE_TEST("items/new-badges") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    RequestContext request = sv.new_request();
    ext::Ctx ctx = sv.make_ctx(request);
    t.expect_eq(sv.st.one("select count(*) from roster where is_new = 1", {}), (int64_t)0, "the seeded characters are not new");
    // a weapon, a character the seed lacks, a stack item
    const u32 weapon = (u32)sv.m.one("select id from master_item where type = 1 order by id limit 1", {});
    // a role whose category the player owns none of (else the grant is a duplicate)
    std::string owned_categories = "0";
    sv.st.q("select role_id from roster", {}, [&](const ext::Row& row) {
        owned_categories += "," + std::to_string(sv.m.one("select role_category_id from master_role where id = ?", {row.i("role_id")}));
    });
    const u32 role = (u32)sv.m.one("select id from master_role where role_category_id not in (" + owned_categories + ") order by id limit 1", {});
    t.expect_eq(role != 0, true, "a role the player lacks");
    const u32 stack = (u32)sv.m.one("select id from master_item where type = 5 order by id limit 1", {});
    Value items = Value::array(), stocks = Value::array(), chars = Value::array();
    ctx.grant(1, weapon, 1, items, stocks, chars);
    ctx.grant(2, role, 1, items, stocks, chars);
    sv.st.q("delete from stock where master_item_id = ?", {stack});
    ctx.grant(5, stack, 3, items, stocks, chars);
    const u64 item_uid = (u64)sv.st.one("select max(uid) from items", {});
    const u64 char_uid = (u64)sv.st.one("select uid from roster where role_id = ?", {role});
    t.expect_eq(chars.arr.size() == 1 && chars.arr[0].find("is_new") && chars.arr[0].find("is_new")->u == 1, true,
                "the granted character's entry is new");
    t.expect_eq(flag_in(ctx.items(), "id", item_uid), 1, "Item: the granted weapon is new");
    t.expect_eq(flag_in(ctx.roster(), "id", char_uid), 1, "Character: the granted character is new");
    t.expect_eq(flag_in(ctx.stock(), "master_item_id", stack), 1, "StockItem: the first stack of an item is new");
    const u64 seeded = (u64)sv.st.one("select min(uid) from roster", {});
    t.expect_eq(flag_in(ctx.roster(), "id", seeded), 0, "Character: a seeded character is not new");

    Value r = mp_decode(call(ctx, "ClearNewItem", {item_uid, 12345}));
    const Value* l = data_key(r, "ItemClearNewList");
    t.expect_eq(l && l->arr.size() == 1 && l->arr[0].u == item_uid, true, "ItemClearNewList: the owned item only");
    t.expect_eq(flag_in(ctx.items(), "id", item_uid), 0, "the item is no longer new");

    r = mp_decode(call(ctx, "ClearNewCharacter", {char_uid, 777}));
    l = data_key(r, "UpdateCharacterList");
    t.expect_eq(l && l->arr.size() == 1 && flag_in(*l, "id", char_uid) == 0, true, "UpdateCharacterList: {id, is_new 0} of the owned one");
    t.expect_eq(flag_in(ctx.roster(), "id", char_uid), 0, "the character is no longer new");

    r = mp_decode(call(ctx, "ClearNewStackItem", {stack, 4242424}));
    l = data_key(r, "StackItemClearNewList");
    t.expect_eq(l && l->arr.size() == 1 && l->arr[0].u == stack, true, "StackItemClearNewList: the held item only");
    t.expect_eq(flag_in(ctx.stock(), "master_item_id", stack), 0, "the stack item is no longer new");
    ctx.grant(5, stack, 1, items, stocks, chars);
    t.expect_eq(flag_in(ctx.stock(), "master_item_id", stack), 0, "more of a held stack item: not new again");
}

}  // namespace
}  // namespace soa::server
