// Item sets (core/rewards.cpp grant_with_item_sets): the 3.7.0 master's nested sets are expanded,
// and a set containing itself stops at the depth guard instead of recursing for ever.
// --selftest "rewards/item-sets".
#include <sqlite3.h>

#include "core/rewards.h"
#include "soaserver/ext.h"
#include "soaserver/native_test.h"

namespace soa::server {
namespace {
using namespace ext;

NATIVE_TEST("rewards/item-sets") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        // a stack-item set of the master: every row granted, num x the set's count
        u32 set = (u32)c.m.one(
            "select item_set_id from master_item_set group by item_set_id "
            "having min(content_type) between 5 and 10 and max(content_type) between 5 and 10 order by item_set_id limit 1",
            {});
        if (!set) return t.fail("no stack-item set in master_item_set");
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        grant_with_item_sets(c, kContentTypeItemSet, set, 2, items, stocks, chars);
        t.expect_eq((u32)stocks.arr.size(), (u32)c.m.one("select count(*) from master_item_set where item_set_id = ?", {set}),
                    "one StockItem per row");
        // the nested sets (a set in a set in a set) end in grants
        u32 coins = 0;
        Value i2 = Value::array(), s2 = Value::array(), c2 = Value::array();
        grant_with_item_sets(c, kContentTypeItemSet, 184028475u, 1, i2, s2, c2, &coins);
        t.expect_eq(i2.arr.size() + s2.arr.size() + c2.arr.size() + coins > 0, true, "the nested set grants something");
        // a set containing itself (shadowing the master's table with a temp copy plus that row)
        c.m.exec("create temp table master_item_set as select * from main.master_item_set");
        c.m.exec("insert into temp.master_item_set (id, item_set_id, order_id, content_id, content_type, num) values (1, 7, 1, 7, 99, 1)");
        Value i3 = Value::array(), s3 = Value::array(), c3 = Value::array();
        grant_with_item_sets(c, kContentTypeItemSet, 7, 1, i3, s3, c3);  // returns: the depth guard
        t.expect_eq(i3.arr.size() + s3.arr.size() + c3.arr.size(), (size_t)0, "a self-containing set grants nothing");
        c.m.exec("drop table temp.master_item_set");
        c.st.exec("rollback");
    });
    if (!ran) return;  // no 3.7.0 master or save
}

}  // namespace
}  // namespace soa::server
