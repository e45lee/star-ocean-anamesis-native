// Unit tests of paid currency (api/shop/coins.cpp; run in --selftest; not differential: the server
// has no guest counterpart), on a scratch server seeded from the test seed save, against the 3.7.0
// master data. docs/server-rules.md#paid-currency.
#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "soaserver/msgpack.h"
#include "testing/module_test.h"

namespace soa::server {
namespace {
using namespace ext;

std::vector<u8> call_s(Ctx& ctx, const char* method, std::vector<u64> ints, std::vector<std::string> strs) {
    const Handler* handler = find(method);
    if (!handler) return {};
    Request req;
    req.method = method;
    req.ints = std::move(ints);
    req.strs = std::move(strs);
    return (*handler)(ctx, req);
}
const Value* data_of(const Value& v) { return v.find("data"); }

NATIVE_TEST("shop/coins") {
    with_scratch_server(t.rand_u64(), [&](Ctx& ctx) {
        ctx.st.exec("begin");
        u32 refused = 0;
        ctx.test.on_refuse = [&](u32 code) { refused = code; };
        // ---- the products: the 2019-10-01 regular sets of master_text (001..007 in 3.7.0) ----------
        Value load = module_test::player_load_data(ctx);
        const Value* list = load.find("CoinList");
        if (!list) return t.fail("no CoinList on the player load");
        t.expect_eq((u32)list->map.size(), 7u, "seven products (coin_name_001..007)");
        const Value* s_set = list->find("1");
        if (!s_set) return t.fail("no product 1");
        t.expect_eq(s_set->find("coin") ? (u32)s_set->find("coin")->u : 0u, 120u, "S set: 120 paid");
        t.expect_eq(s_set->find("free_coin") ? (u32)s_set->find("free_coin")->u : 1u, 0u, "S set: no bonus");
        const Value* tera = list->find("7");
        if (!tera) return t.fail("no product 7");
        t.expect_eq((u32)tera->find("coin")->u, 10000u, "テラ set: 10,000 paid (coin_description__20191001_007)");
        t.expect_eq((u32)tera->find("free_coin")->u, 6550u, "テラ set: 6,550 bonus");
        t.expect_eq((u32)tera->find("yen")->u, 10000u, "the price shown is the paid count");
        t.expect_eq(tera->find("product_id")->s, std::string("soa.local.coin_007"), "the store's product id");
        t.expect_eq(tera->find("title_label")->s, std::string("coin_title_20191001_007"), "the 2019-10-01 title");
        t.expect_eq(list->find("8") == nullptr, true, "the limited sets aren't sold");

        // ---- a purchase: create (pending), then the Android update credits paid + free ------------------
        ctx.st.q("update player set free_coin = 5, pay_coin = 0", {});
        Value created = mp_decode(call_s(ctx, "CoinDepositCreate", {1, 7}, {"user_id"}));
        const Value* dep = data_of(created) ? data_of(created)->find("CoinDeposit") : nullptr;
        u32 trans = dep && dep->find("deposit_trans_id") ? (u32)dep->find("deposit_trans_id")->u : 0;
        t.expect_eq(trans != 0, true, "a deposit trans id");
        t.expect_eq(ctx.st.one("select count(*) from coin_deposit where trans_id = ? and completed_at is null", {trans}), (int64_t)1, "pending");
        t.expect_eq(ctx.st.one("select pay_coin from player", {}), (int64_t)0, "nothing credited before the update");
        Value done = mp_decode(call_s(ctx, "CoinDepositAndroidUpdate", {trans}, {"cmVjZWlwdA==", ""}));
        t.expect_eq(ctx.st.one("select pay_coin from player", {}), (int64_t)10000, "10,000 paid stones");
        t.expect_eq(ctx.st.one("select free_coin from player", {}), (int64_t)6555, "6,550 free stones on top of 5");
        t.expect_eq(
            ctx.st.one("select count(*) from coin_deposit where trans_id = ? and completed_at is not null and paid = 10000 and free = 6550", {trans}),
            (int64_t)1, "the purchase record");
        const Value* d = data_of(done);
        const Value* wallet = d ? d->find("Wallet") : nullptr;
        t.expect_eq(wallet && wallet->find("pay_coin") ? (u32)wallet->find("pay_coin")->u : 0u, 10000u, "Wallet.pay_coin answered");
        const Value* purchased = d ? d->find("PurchasedItemInfo") : nullptr;
        t.expect_eq(purchased && purchased->find("name_label") ? purchased->find("name_label")->s : std::string(), std::string("coin_name_007"),
                    "PurchasedItemInfo.name_label");

        // ---- the store retries: no second credit; an unknown deposit and product are refused -------------
        call_s(ctx, "CoinDepositAndroidUpdate", {trans}, {"cmVjZWlwdA==", ""});
        t.expect_eq(ctx.st.one("select pay_coin from player", {}), (int64_t)10000, "a completed deposit isn't credited twice");
        call_s(ctx, "CoinDepositIOSUpdate", {trans + 100}, {"", ""});
        t.expect_eq(refused, 10208u, "an unknown deposit: 10208");
        refused = 0;
        call_s(ctx, "CoinDepositCreate", {1, 8}, {"user_id"});
        t.expect_eq(refused, 10208u, "a product not sold: 10208");
        t.expect_eq(ctx.st.one("select count(*) from coin_deposit", {}), (int64_t)1, "no deposit for it");

        // ---- the iOS / Amazon updates complete a purchase the same way ---------------------------------
        Value c2 = mp_decode(call_s(ctx, "CoinDepositCreate", {1, 1}, {"user_id"}));
        u32 trans2 = (u32)data_of(c2)->find("CoinDeposit")->find("deposit_trans_id")->u;
        call_s(ctx, "CoinDepositAmazonUpdate", {trans2}, {"", ""});
        t.expect_eq(ctx.st.one("select pay_coin from player", {}), (int64_t)10120, "the S set's 120 via the Amazon update");

        // ---- the list methods ------------------------------------------------------------------------
        Value cl = mp_decode(call_s(ctx, "CoinList", {}, {}));
        t.expect_eq(data_of(cl) && data_of(cl)->find("CoinList") ? (u32)data_of(cl)->find("CoinList")->map.size() : 0u, 7u,
                    "CoinList answers the list");
        Value dl = mp_decode(call_s(ctx, "DirectItemShopList", {}, {}));
        const Value* direct = data_of(dl) ? data_of(dl)->find("DirectItemShopInfoList") : nullptr;
        t.expect_eq(direct && direct->arr.empty(), true, "DirectItemShopList: an empty list");
        ctx.st.exec("commit");
    });
}

}  // namespace
}  // namespace soa::server
