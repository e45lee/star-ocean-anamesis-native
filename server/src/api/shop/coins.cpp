// Paid currency (紋章石 bought with money): the coin shop's products (CoinList), the purchase flow
// (CoinDepositCreate, then CoinDepositAndroidUpdate / IOSUpdate / AmazonUpdate) and the premium
// shop's list (DirectItemShopList). Port code, not guest behaviour. The user's decision (2026-10-04,
// docs/unimplemented-apis.md "Decisions"): buying works locally and costs nothing. Rules in
// docs/server-rules.md#paid-currency; labels: (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption.
//
// The client's purchase flow (b), CPaymentManager (Progress_Purchase @015f8224):
//   1. CoinDepositCreate(1, product id, "user_id") (vtable +0x360; PurchaseInit_ @015f8fb8); the
//      answer's CoinDeposit.deposit_trans_id lands at CParameterManager+0x6e78.
//   2. The store's purchase (PaymentClient::PurchaseProduct, the platform's in-app billing; the
//      trans id as the developer payload, "%u").
//   3. VerifyReceipt_ (@015f91b0): CoinDepositAndroidUpdate(trans id, Base64(purchase data),
//      signature) (vtable +0x370); on success the store's purchase is consumed.
// The products themselves are CParameterManager+0x6e00 (CCoinInfoList, the `CoinList` key):
// CPaymentManager::Init_ (@015f87fc) registers each one's product_id with the store at login and
// fails (-0x3fd, the coin shop's error dialog) when the list is empty; CCoinShop::
// StateCoinShopCore (@019780b4) lists the store's products that have a CCoinInfo.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "api/gen/reply_types.h"  // the replies' C*Info types
#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "core/response.h"
#include "core/wallet.h"
#include "soaserver/ext.h"

namespace soa::server {

namespace args {
// CoinDepositCreate(u8 platform, s32 product, s8 const* user): (b) Progress_Purchase sends
// platform 1, the CCoinInfo id the player chose and the literal "user_id".
struct CoinDepositCreateArgs {
    u32 platform = 0, product = 0;
    static CoinDepositCreateArgs from(const Request& req) {
        return {req.ints.size() > 0 ? (u32)req.ints[0] : 0, req.ints.size() > 1 ? (u32)req.ints[1] : 0};
    }
};
// CoinDeposit{Android,IOS,Amazon}Update(u32 trans id, s8 const* receipt, s8 const* signature).
struct CoinDepositUpdateArgs {
    u32 trans_id = 0;
    std::string receipt, signature;
    static CoinDepositUpdateArgs from(const Request& req) {
        CoinDepositUpdateArgs a;
        a.trans_id = req.ints.size() > 0 ? (u32)req.ints[0] : 0;
        if (req.strs.size() > 0) a.receipt = req.strs[0];
        if (req.strs.size() > 1) a.signature = req.strs[1];
        return a;
    }
};
}  // namespace args

using ext::body;
using ext::Ctx;
using ext::Row;

namespace {

// One product of the coin shop (a CCoinInfo).
struct Product {
    u32 id = 0;      // CCoinInfo.id: the number of its master_text labels
    u32 paid = 0;    // CCoinInfo.coin: the stones bought (paid stones)
    u32 bonus = 0;   // CCoinInfo.free_coin: the bonus (free stones)
    std::string name_label, title_label, description_label;
};

// "※2,080個＋おまけ370個" -> 2080 and 370; false when the text isn't that shape.
bool parse_counts(const std::string& text, u32& paid, u32& bonus) {
    auto number_before = [&](size_t from, size_t& end, u32& out) {
        size_t i = from;
        while (i < text.size() && !(text[i] >= '0' && text[i] <= '9')) i++;
        if (i >= text.size()) return false;
        u64 v = 0;
        while (i < text.size() && ((text[i] >= '0' && text[i] <= '9') || text[i] == ',')) {
            if (text[i] != ',') v = v * 10 + (u64)(text[i] - '0');
            i++;
        }
        if (text.compare(i, 3, "個") != 0 || v > 0xffffffffu) return false;
        out = (u32)v;
        end = i + 3;
        return true;
    };
    size_t at = text.find("※");
    size_t bonus_at = text.find("おまけ");
    if (at == std::string::npos || bonus_at == std::string::npos) return false;
    size_t end = 0;
    if (!number_before(at, end, paid) || end > bonus_at) return false;
    return number_before(bonus_at, end, bonus);
}

// The coin shop's products, from the master text (docs/server-rules.md#paid-currency):
//   (a) master_text coin_name_NNN / coin_title_NNN / coin_description_NNN are the products' labels
//       (the client shows them through CCoinInfo name_label / title_label / description_label,
//       CCoinShop::tInfo::Initialize @0197874c: GetSystemMessage of each); the 2019-10-01 set
//       (coin_title_20191001_NNN, coin_description__20191001_NNN) is the one sold last.
//   (a)+(d) a product's stones are read from its description, "※<paid>個＋おまけ<bonus>個"
//       (the purchase history's text: おまけ is free, master_text uimsg_buy_history_explan).
//   (d) Sold: the NNN with the three 2019-10-01 labels whose name has neither "限定" nor "＋":
//       the limited and bonus sets' 2019-10-01 descriptions don't describe their names (008's name
//       is an S set, its description 3,060 + 3,060), so which they were is unknown. 001..007 in
//       the 3.7.0 master.
std::vector<Product> products(Ctx& ctx) {
    // one scan of the coin labels (master_text has no index on message_id)
    std::map<std::string, std::string> texts;
    ctx.m.q("select message_id, text_value from master_text where message_id like 'coin\\_%' escape '\\'", {},
            [&](const Row& r) { texts.emplace(r.s("message_id"), r.s("text_value")); });
    auto text_of = [&](const std::string& id) {
        auto it = texts.find(id);
        return it == texts.end() ? std::string() : it->second;
    };
    std::vector<Product> out;
    for (const auto& [name_id, name] : texts) {
        if (name_id.rfind("coin_name_", 0) != 0) continue;
        std::string number = name_id.substr(strlen("coin_name_"));
        if (number.empty() || number.find_first_not_of("0123456789") != std::string::npos) continue;
        if (name.find("限定") != std::string::npos || name.find("＋") != std::string::npos) continue;
        Product p;
        p.id = (u32)strtoul(number.c_str(), nullptr, 10);
        p.name_label = name_id;
        p.title_label = "coin_title_20191001_" + number;
        p.description_label = "coin_description__20191001_" + number;
        if (text_of(p.title_label).empty() || !parse_counts(text_of(p.description_label), p.paid, p.bonus) || !p.paid) continue;
        out.push_back(p);
    }
    return out;
}

const Product* find_product(const std::vector<Product>& list, u32 id) {
    for (const Product& p : list)
        if (p.id == id) return &p;
    return nullptr;
}

// The store's product id of a product (CCoinInfo.product_id; the platform's in-app billing knows
// it by this): (d) made up, the real SKUs aren't recorded; under the store's 64 bytes
// (CPaymentManager::Init_ copies it into a 0x40 buffer).
std::string store_product_id(u32 id) {
    char b[48];
    snprintf(b, sizeof b, "soa.local.coin_%03u", id);
    return b;
}

// CCoinInfo (b: the keys CCoinInfo::Initialize @01659284 registers, the 3.7.0 schema dump):
//   id, product_id (the store's), coin / free_coin (the stones, paid / bonus), yen (the price
//   tInfo::Price @0197b024 shows), order_id, icon_id (tInfo::Icon @0197ad5c: itm_th_001NN, 1..3),
//   name_label / title_label / description_label, opened_at / closed_at ("" = no window:
//   CUIUtility::IsTimeOverCoinSale @01ef76c8 checks a non-empty one), bought_at (non-empty with
//   interval_day 0 = sold out: IsSoldOutCoinSale @01ef77e8), limit_count / limit_num / interval_day
//   (StateCoinShopCore lists a product while limit_count is 0 or limit_num isn't), bonus_type
//   (only 0 is listed in the coin shop), is_once, sale_type, starter_limit_day, is_view_closed_at.
//   (d) yen = the paid stones (the descriptions' paid counts are the Japanese store's price points,
//   120 .. 10,000); (d) icon 1 for the two smallest sets, 2 for the next two, 3 above; (d) no
//   product has a limit, a window or a bonus.
infos::CCoinInfo coin_info(const Product& p) {
    infos::CCoinInfo info;  // (the rest "", 0, false: no window, limit or bonus)
    info.id = p.id;
    info.product_id = store_product_id(p.id);
    info.coin = p.paid;
    info.free_coin = p.bonus;
    info.yen = p.paid;
    info.order_id = p.id;
    info.icon_id = p.id <= 2 ? 1u : p.id <= 4 ? 2u : 3u;
    info.name_label = p.name_label;
    info.title_label = p.title_label;
    info.description_label = p.description_label;
    return info;
}

// CoinList: {id: CCoinInfo} (a number map, InfoBaseNumberMap<CCoinInfo>; a map key is the id).
Value coin_list(Ctx& ctx) {
    infos::InfoMap<u64, infos::CCoinInfo> list;
    for (const Product& p : products(ctx)) list[p.id] = coin_info(p);
    return infos::to_map(list);
}

// CoinList() -> CoinListRes                                                fid d859bb89
// API: docs/api.md#coinlist   Rules: docs/server-rules.md#paid-currency
//
// The coin shop's products. (b) No 3.7.0 caller sends it (docs/api.md): the client gets them with
// the player load (load_coin_list below); answered for a client that asks.
// Answers: the player state with CoinList.
std::vector<u8> coin_list_api(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["CoinList"] = coin_list(ctx);
    return body(data);
}

// CoinDepositCreate(u8 platform, s32 product, s8 const* user) -> CoinDepositCreateRes   fid 3850fb96
// API: docs/api.md#coindepositcreate   Rules: docs/server-rules.md#paid-currency
//
// Starts a purchase: a pending coin_deposit row (the product, the platform, the time).
//   (b) Progress_Purchase sends it before the store's purchase and passes the answer's
//       CoinDeposit.deposit_trans_id (CParameterManager+0x6e78) to the store as the payload and
//       back in CoinDepositAndroidUpdate.
//   (d) The trans id is the row's (1, 2, ...). A product that isn't sold (products()) is refused
//       with 10208, the server's generic refusal; nothing is charged anywhere (Decisions).
// Answers: the player state with CoinDeposit {deposit_trans_id}.
std::vector<u8> coin_deposit_create(Ctx& ctx, const Request& req) {
    auto a = args::CoinDepositCreateArgs::from(req);
    std::vector<Product> list = products(ctx);
    if (!find_product(list, a.product)) return ext::refusef(ctx, "CoinDepositCreate", ErrorCode::kItemUnusable, "no product %u", a.product);
    ctx.st.q("insert into coin_deposit (product_id, platform, created_at) values (?, ?, ?)", {a.product, a.platform, ctx.now()});
    u32 trans = (u32)ctx.st.one("select max(trans_id) from coin_deposit", {});
    LOGI("server", "CoinDepositCreate: product %u (platform %u): deposit %u pending", a.product, a.platform, trans);
    Value data = ctx.base_data();
    data["CoinDeposit"] = infos::to_value(infos::CCoinDepositInfo{trans});
    return body(data);
}

// CoinDepositAndroidUpdate / CoinDepositIOSUpdate / CoinDepositAmazonUpdate
//   (u32 trans id, s8 const* receipt, s8 const* signature) -> ...UpdateRes   fid 089ac659 / c5193b15 / 0bc7f736
// API: docs/api.md#coindepositandroidupdate   Rules: docs/server-rules.md#paid-currency
//
// Completes a purchase: the product's stones are credited, the deposit row records it.
//   (b) VerifyReceipt_ sends it with the store's receipt; OnCoinDepositAndroidUpdateRes applies the
//       answer (Wallet; PurchasedItemInfo for the coin shop's result: CPurchasedItemInfo bonus_type,
//       name_label, title_label).
//   (a)+(d) the product's paid stones go to the paid coins (player.pay_coin; the wallet keeps free
//       and paid apart, core/wallet.h), its bonus (おまけ) to the free coins (a: uimsg_buy_history_explan,
//       "おまけ分は無償入手分").
//   (d) No receipt validation (Decisions): the receipt and signature are logged, not checked.
//   (d) A deposit already completed answers the same without crediting again (the store retries a
//       purchase whose answer it lost: Progress_Reverify); an unknown trans id is refused with
//       10208. The iOS and Amazon updates do the same as the Android one (the port is an Android
//       client).
// Answers: the player state with PurchasedItemInfo and CoinList.
std::vector<u8> coin_deposit_update(Ctx& ctx, const Request& req) {
    auto a = args::CoinDepositUpdateArgs::from(req);
    const char* method = req.method.c_str();
    u32 product_id = 0;
    bool done = false, known = false;
    ctx.st.q("select product_id, completed_at from coin_deposit where trans_id = ?", {a.trans_id}, [&](const Row& r) {
        known = true;
        product_id = (u32)r.i("product_id");
        done = !r.null("completed_at");
    });
    std::vector<Product> list = products(ctx);
    const Product* p = known ? find_product(list, product_id) : nullptr;
    if (!p) return ext::refusef(ctx, method, ErrorCode::kItemUnusable, "no pending deposit %u", a.trans_id);
    LOGI("server", "%s: deposit %u, receipt %zu bytes, signature %zu bytes (not validated)", method, a.trans_id, a.receipt.size(),
         a.signature.size());
    if (!done) {
        wallet::add_paid_coins(ctx.st.h, p->paid);
        wallet::add_free_coins(ctx.st.h, p->bonus);
        ctx.st.q("update coin_deposit set completed_at = ?, paid = ?, free = ? where trans_id = ?", {ctx.now(), p->paid, p->bonus, a.trans_id});
        LOGI("server", "%s: deposit %u completed: product %u, %u paid + %u free stones", method, a.trans_id, p->id, p->paid, p->bonus);
    } else {
        LOGI("server", "%s: deposit %u was completed already; nothing credited", method, a.trans_id);
    }
    Value data = ctx.base_data();
    data["PurchasedItemInfo"] =
        infos::to_value(infos::CPurchasedItemInfo{.bonus_type = 0, .name_label = p->name_label, .title_label = p->title_label});
    data["CoinList"] = coin_list(ctx);
    return body(data);
}

// DirectItemShopList() -> DirectItemShopListRes                           fid c367268b
// API: docs/api.md#directitemshoplist   Rules: docs/server-rules.md#paid-currency
//
// The premium shop (プレミアムショップ: item sets bought with money; CShop::ProgressDirectItemShop).
//   (b) CDirectItemShop buys a row through CPaymentManager::Purchase(int), i.e. a store product of
//       the CoinList, and the 3.7.0 shop menu has no premium-shop entry (CShop::Setup lists
//       item_shop .. stamina_heal); the 購入情報 screen shows its passes as 販売終了.
//   (d) Answered with an empty list: master_direct_item_shop names the sets but no store product
//       or price for them, so nothing can be sold.
// Answers: the player state with an empty DirectItemShopInfoList.
std::vector<u8> direct_item_shop_list(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["DirectItemShopInfoList"] = Value::array();
    return body(data);
}

// OnPlayerLoad hook (Login, GetPlayer, NoLoginStart's full player state).
// Rules: docs/server-rules.md#paid-currency
//   (b) CoinList has no caller in 3.7.0 while CPaymentManager::Init_ needs the products at the
//       end of the login (CPhase_Login::Progress state 0xe calls CPaymentManager::Initialize);
//       (d) so every full player load carries them.
// Adds: CoinList.
void load_coin_list(Ctx& ctx, const Request&, Value& data) { data["CoinList"] = coin_list(ctx); }

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this).
void register_coins() {
    using namespace ext;
    add_api({"CoinList"}, coin_list_api);
    add_api({"CoinDepositCreate"}, coin_deposit_create);
    add_api({"CoinDepositAndroidUpdate", "CoinDepositIOSUpdate", "CoinDepositAmazonUpdate"}, coin_deposit_update);
    add_api({"DirectItemShopList"}, direct_item_shop_list);
    add_player_load(load_coin_list);
}

}  // namespace soa::server
