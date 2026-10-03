// Unit tests of the shops and passes (api/shop/; run in --selftest; not differential: the server has
// no guest counterpart), on a scratch server seeded from the test seed save, against the 3.7.0
// master data. Test names are their seeds (testing.h): shop/... since R18 (shop/item-shop-and-exchange
// was server/economy-apis in api/growth/growth_tests.cpp, shop/subscription was server/subscription in
// subscription.cpp).
#include "api/shop/subscription.h"
#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "testing/module_test.h"

namespace soa::server {
namespace {
using namespace ext;
using module_test::call;

NATIVE_TEST("shop/item-shop-and-exchange") {
    with_scratch_server(t.rand_u64(), [&](Ctx& ctx) {
        ctx.st.exec("begin");
        // ---- item shop: an open monthly row with limit_count 1; bought once per period
        int64_t now = ctx.now();
        std::string now_text = ctx.fmt_time(now);
        u32 row = (u32)ctx.m.one(
            "select id from master_item_shop where reset_type = 2 and limit_count = 1 and opened_at <= ? and closed_at >= ? "
            "order by id limit 1",
            {now_text, now_text});
        if (row) {
            u32 price = (u32)ctx.m.one("select price from master_item_shop where id = ?", {row});
            ctx.st.q("update player set free_coin = ?", {price * 3});
            int64_t stock0 = ctx.st.one("select ifnull(sum(count),0) from stock", {}) + ctx.st.one("select count(*) from items", {});
            call(ctx, "ExItemShop", {row});
            t.expect_eq((u32)ctx.st.one("select free_coin from player", {}), price * 2, "shop price");
            int64_t stock1 = ctx.st.one("select ifnull(sum(count),0) from stock", {}) + ctx.st.one("select count(*) from items", {});
            if (stock1 <= stock0) t.fail("nothing granted by the shop row");
            call(ctx, "ExItemShop", {row});
            t.expect_eq((u32)ctx.st.one("select free_coin from player", {}), price * 2, "sold out after limit_count");
            // a new month resets it
            ctx.st.q("update shop_counts set period = period - 1 where id = ?", {row});
            call(ctx, "ExItemShop", {row});
            t.expect_eq((u32)ctx.st.one("select free_coin from player", {}), price, "new period");
        } else {
            t.fail("no open monthly shop row at %s", now_text.c_str());
        }
        // ---- exchange: any row whose shop is open now (skipped when none)
        u32 exchange_row = (u32)ctx.m.one(
            "select x.id from master_exchange_shop_contents x join master_exchange_shop s on s.id = x.master_exchange_shop_id "
            "where (s.opened_at is null or s.opened_at <= ?) and (s.closed_at is null or s.closed_at >= ?) and "
            "(x.opened_at is null or x.opened_at <= ?) and x.content_type in (5, 7, 8, 9, 10) order by x.id limit 1",
            {now_text, now_text, now_text});
        if (exchange_row) {
            u32 coin = (u32)ctx.m.one("select ex_item_id from master_exchange_shop_contents where id = ?", {exchange_row});
            u32 price = (u32)ctx.m.one("select ex_num from master_exchange_shop_contents where id = ?", {exchange_row});
            u32 content = (u32)ctx.m.one("select content_id from master_exchange_shop_contents where id = ?", {exchange_row});
            u32 num = (u32)ctx.m.one("select num from master_exchange_shop_contents where id = ?", {exchange_row});
            add_stock(ctx, coin, price);
            u32 before = stock_count(ctx, content);
            call(ctx, "ExshopExchange", {exchange_row, 1});
            t.expect_eq(stock_count(ctx, coin), 0u, "exchange paid");
            t.expect_eq(stock_count(ctx, content), before + num, "exchange granted");
            t.expect_eq((u32)ctx.st.one("select num from exchange_counts where id = ?", {exchange_row}), 1u, "exchange counted");
        }
        ctx.st.exec("commit");
    });
}

NATIVE_TEST("shop/subscription") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& ctx) {
        ctx.st.exec("begin");
        int64_t clock = ctx.parse_time("2020-06-01 12:00:00");
        ctx.test.now = [&] { return clock; };
        u32 plan = (u32)ctx.m.one("select id from master_subscription_plan where id_label = 'pshop_galaxypass_001'", {});
        if (!plan) return t.fail("no pshop_galaxypass_001 plan");
        t.expect_eq(subscription_active(ctx, 3, clock), false, "no pass at first");
        subscription::grant_plan(ctx, plan, 30, clock);
        t.expect_eq(subscription_active(ctx, 3, clock), true, "type 3 (deep space ships) on");
        t.expect_eq(subscription_active(ctx, 4, clock), false, "type 4 isn't in the Galaxy Pass");
        t.expect_eq(subscription_active(ctx, 3, clock + 30 * 86400 - 1), true, "on for 30 days");
        t.expect_eq(subscription_active(ctx, 3, clock + 30 * 86400), false, "off after 30 days");
        // a second grant while it runs extends it
        subscription::grant_plan(ctx, plan, 30, clock + 86400);
        t.expect_eq(subscription_active(ctx, 3, clock + 59 * 86400), true, "extended");
        Value types = subscription::subscription_info(ctx);
        const Value* type3 = types.find("3");
        if (!type3) return t.fail("no type 3 entry");
        const Value* closed_at = type3->find("closed_at");
        t.expect_eq(closed_at ? closed_at->s : std::string("?"), ctx.fmt_time(clock + 60 * 86400), "closed_at sent");
        // the Galaxy Pass has the types 1, 2, 3, 5 (a)
        t.expect_eq(types.map.size(), (size_t)ctx.m.one("select count(*) from master_subscription where plan_id = ?", {plan}),
                    "every type of the plan");
        // --galaxy-pass: granted when missing or expired, not while running
        clock += 61 * 86400;
        subscription::keep_galaxy_pass(ctx, clock);
        t.expect_eq(subscription_active(ctx, 3, clock), true, "renewed by the option");
        int64_t until = ctx.st.one("select closed_at from subscription where plan_id = ?", {plan});
        subscription::keep_galaxy_pass(ctx, clock + 10);
        t.expect_eq(ctx.st.one("select closed_at from subscription where plan_id = ?", {plan}), until, "not extended while running");
    });
    if (!ran) return;
}

}  // namespace
}  // namespace soa::server
