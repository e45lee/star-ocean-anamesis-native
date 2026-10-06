// The shops: the item shop (ItemShopList, ExItemShop; master_item_shop) and the exchange shops
// (ExshopExchangeList, ExshopExchange; master_exchange_shop*). Port code, not guest behaviour.
// Rules in docs/server-rules.md#shops, docs/server-rules.md#shops-modules and docs/server-rules.md#event-exchange-shops;
// labels: (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include <ctime>
#include <tuple>

#include "core/log.h"
#include "core/time.h"
#include "api/events/enable_events.h"
#include "soaserver/events.h"
#include "soaserver/ext.h"
#include "core/errors.h"
#include "core/rewards.h"  // grant_with_item_sets
#include "core/wallet.h"
#include "rules/growth_rules.h"
#include "core/modules.h"

namespace soa::server {

namespace args {
// ExItemShop(u32 master_item_shop_id). The module's own args structs (core/request_args.h holds
// the core handlers').
struct ExItemShopArgs {
    u32 shop_row_id = 0;
    static ExItemShopArgs from(const Request& req) { return {req.ints.size() > 0 ? (u32)req.ints[0] : 0}; }
};
// ExshopExchange(u32 contents id: a master_exchange_shop_contents row, u32 num): (d) a missing or 0
// count is 1.
struct ExshopExchangeArgs {
    u32 contents_id = 0, count = 1;
    static ExshopExchangeArgs from(const Request& req) {
        return {req.ints.size() > 0 ? (u32)req.ints[0] : 0, req.ints.size() > 1 && req.ints[1] ? (u32)req.ints[1] : 1};
    }
};
}  // namespace args

namespace {
using namespace ext;

// Exchange shops on the event calendar (docs/server-rules.md#event-exchange-shops):
// (a) master_exchange_shop opened_at / closed_at; (d) a shop is open when the clock is inside its
// window, or inside it moved by the calendar's whole years (events::client_years, the shift the
// event module applies to the event tables): the event shops (e.g. an event's coin exchange) open
// with their event. The client's master copy moves those rows the same way (client_master_shops
// below), so the client's own filter (b: CShop::Progress lists the master shops open by the client
// clock) agrees. Unlike the event tables, only the rows the move opens are moved (an open-ended row
// moved forward would open late).
bool opened_by_year_shift(const std::string& opened_at, const std::string& closed_at, int years, ServerTime now) {
    return years > 0 && events::window_open(opened_at, closed_at, years, now) && !events::window_open(opened_at, closed_at, 0, now);
}
bool exchange_window_open(Ctx& ctx, const std::string& opened_at, const std::string& closed_at) {
    ServerTime now = ctx.now();
    return events::window_open(opened_at, closed_at, 0, now) || events::window_open(opened_at, closed_at, events::client_years(ctx), now);
}
// "hh:mm:ss" -> seconds since midnight (master_item_shop.reset_time).
int seconds_of_day(const std::string& hms) {
    int h = 0, m = 0, s = 0;
    sscanf(hms.c_str(), "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

// The start of an item-shop row's current period (growth_rules::shop_period_start: (a) reset_type 2
// monthly on day reset_param at reset_time; 0 = the row never resets).
ServerTime shop_period(const Row& shop_row, ServerTime t) {
    return ServerTime(growth_rules::shop_period_start(t.v, (int)shop_row.i("reset_type"), (int)shop_row.i("reset_param"),
                                                      seconds_of_day(shop_row.s("reset_time"))));
}

// The player's count for one item-shop row in the current period.
u32 shop_bought(Ctx& ctx, const Row& shop_row, ServerTime t) {
    ServerTime period = shop_period(shop_row, t);
    u32 bought = 0;
    ctx.st.q("select num, period from shop_counts where id = ?", {shop_row.i("id")}, [&](const Row& count_row) {
        if (count_row.time("period") == period) bought = (u32)count_row.i("num");  // (a) a new period starts from 0
    });
    return bought;
}
// CItemShopInfo, (b) from CItemShop::CreateItemSetList: the shop lists the master rows whose ids
// are in the owned ItemShopInfoList (a row missing from it counts as sold out); it takes the
// info's `limit_count` (+0x90) as the count still available this period (bought = master
// limit_count - it; ItemShopUtility::ItemSetInfo::GetRemain / IsEnable), and reset_at, parsed
// with str2time_t, is the time shown as 交換可能期限 (the next reset). num_total: (d) the number
// bought ever.
Value item_shop_info(Ctx& ctx, const Row& shop_row, ServerTime t) {
    Value info = Value::object();
    int reset_type = (int)shop_row.i("reset_type"), reset_param = (int)shop_row.i("reset_param");
    int reset_seconds = seconds_of_day(shop_row.s("reset_time"));
    info["id"] = (u32)shop_row.i("id");
    u32 limit = (u32)shop_row.i("limit_count"), bought = shop_bought(ctx, shop_row, t);
    info["limit_count"] = limit > bought ? limit - bought : 0u;
    info["num_total"] = (u32)ctx.st.one("select total from shop_counts where id = ?", {shop_row.i("id")});
    info["loop_count"] = (u32)shop_row.i("loop_count");
    info["is_new"] = false;
    int64_t period = growth_rules::shop_period_start(t.v, reset_type, reset_param, reset_seconds);  // 0: never resets
    // (d) the next reset: the period start a month (32 days) on, normalised to its day
    info["reset_at"] =
        period ? ctx.fmt_time(growth_rules::shop_period_start(period + 32 * 86400, reset_type, reset_param, reset_seconds)) : std::string("");
    return info;
}
// ItemShopInfoList: every master_item_shop row open at the clock, in order_id order.
Value item_shop_list(Ctx& ctx) {
    Value list = Value::array();
    ServerTime t = ctx.now();
    ctx.m.q("select * from master_item_shop order by order_id", {}, [&](const Row& shop_row) {
        if (open_at(shop_row.s("opened_at"), shop_row.s("closed_at"), t)) list.push(item_shop_info(ctx, shop_row, t));  // (a)+(b) the open window
    });
    return list;
}

// ItemShopList() -> ItemShopListRes                                     fid b04c111c
// API: docs/api.md#itemshoplist   Rules: docs/server-rules.md#shops, docs/server-rules.md#shops-modules
//
// The item shop's rows and the player's counts (b: CShop::ProgressItemShop sends it; docs/api.md Callers).
//   (b) CItemShop::CreateItemSetList lists only the rows in ItemShopInfoList; (a) every row open
//       at the clock is sent (item_shop_info: what is left this period, the next reset).
// Answers: the player state with ItemShopInfoList.
std::vector<u8> item_shop_list_api(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["ItemShopInfoList"] = item_shop_list(ctx);
    return body(data);
}

// Why a purchase or an exchange is refused (why == nullptr: it isn't).
struct Refusal {
    const char* why = nullptr;
    ErrorCode code{};
};

// Pays for one item-shop row and counts it, unless refused.
Refusal buy_item_shop_row(Ctx& ctx, const Row& shop_row, ServerTime t) {
    u32 id = (u32)shop_row.i("id");
    if (!open_at(shop_row.s("opened_at"), shop_row.s("closed_at"), t)) return {"closed", ErrorCode::kExchangeExpired};
    u32 limit = (u32)shop_row.i("limit_count"), bought = shop_bought(ctx, shop_row, t);
    // (b) ItemShopUtility::IsEnable; (d) limit 0 = unlimited
    if (limit && bought >= limit) return {"sold out", ErrorCode::kLimitReached};
    // (a) price; (b) in coins (紋章石: the screen's 必要紋章石); (a) free coins first (core/wallet.h);
    // (b) short: 20003, which the exchange's answer lambda (@01b5eea4) answers with the coin shop
    // (CDialogManager::OpenCoinShopDialog for the coins missing; docs/server-rules.md#paid-currency)
    u32 price = (u32)shop_row.i("price");
    if (!wallet::spend_coins(ctx.st.h, price)) return {"not enough coins", ErrorCode::kCoinsShortShop};
    ctx.st.q(
        "insert into shop_counts (id, num, period, total) values (?, ?, ?, 1) "
        "on conflict(id) do update set num = excluded.num, period = excluded.period, "
        "total = total + 1",
        {id, bought + 1, shop_period(shop_row, t)});
    return {};
}

// ExItemShop(u32 master_item_shop_id) -> ExItemShopRes                  fid 33d09fb7
// API: docs/api.md#exitemshop   Rules: docs/server-rules.md#shops, docs/server-rules.md#shops-modules
//
// Buys one item-shop row (b: code near CItemShop sends it; docs/api.md Callers).
//   (a) the row open at the clock, else kExchangeExpired (17001); (b)+(d) limit_count per period
//       (0 = unlimited), else kLimitReached (11006); (a) price in coins, free coins first, else
//       kCoinsShort (20000); an unknown row: kItemUnusable (10208, the generic refusal).
//   (a) content x num, item sets expanded; (d) straight into the inventory, not the present box.
// Answers: the player state with ItemShopInfo (this row), ItemShopInfoList, StockItem, and
// AddItem when items were granted.
std::vector<u8> ex_item_shop(Ctx& ctx, const Request& req) {
    const auto args = args::ExItemShopArgs::from(req);
    ServerTime t = ctx.now();
    std::vector<u8> out;
    bool found = false;
    ctx.m.q("select * from master_item_shop where id = ?", {args.shop_row_id}, [&](const Row& shop_row) {
        found = true;
        Refusal refusal = buy_item_shop_row(ctx, shop_row, t);
        if (refusal.why) {
            out = refuse(ctx, "ExItemShop", refusal.why, refusal.code);
            return;
        }
        Value items = Value::array(), stocks = Value::array(), characters = Value::array();
        u32 free_coins = 0;
        grant_with_item_sets(ctx, (u32)shop_row.i("content_type"), (u32)shop_row.i("content_id"), (u32)std::max<int64_t>(1, shop_row.i("num")), items,
                             stocks, characters, &free_coins);
        Value data = ctx.base_data();
        data["ItemShopInfo"] = item_shop_info(ctx, shop_row, t);
        data["ItemShopInfoList"] = item_shop_list(ctx);
        if (!items.arr.empty()) data["AddItem"] = items;
        data["StockItem"] = ctx.stock();
        LOGI("server", "ExItemShop %u (%s): %u coins, %zu items, %zu stack grants", args.shop_row_id, shop_row.s("id_label").c_str(),
             (u32)shop_row.i("price"), items.arr.size(), stocks.arr.size());
        out = body(data);
    });
    if (!found) return refuse(ctx, "ExItemShop", "unknown shop row", ErrorCode::kItemUnusable);
    return out;
}

// ExchangeShopExCount (CExchangeShopExCountInfoCategoryMap, CParameterManager+0x60d0): (b) CShop
// lists only the master exchange shops open by the clock whose id is a key of this map
// (CShop::Progress after CUIUtility::CollectMasterItemExchangeShop), so every open shop is sent.
// Inside a shop: (d) contents id -> {ex_count} (the element's one field, ex_count, is (b): its
// Initialize), the number exchanged so far.
Value exchange_counts(Ctx& ctx) {
    Value shops = Value::object();
    ctx.m.q("select id, opened_at, closed_at from master_exchange_shop order by id", {}, [&](const Row& shop_row) {
        // (a)+(d) --enable-events: the enabled events' shops are open all year (enable_events.h)
        if (!exchange_window_open(ctx, shop_row.s("opened_at"), shop_row.s("closed_at")) &&
            !enable_events::exchange_shop(ctx.m, (u32)shop_row.i("id")))
            return;
        Value contents = Value::object();
        ctx.m.q("select id from master_exchange_shop_contents where master_exchange_shop_id = ? order by id", {shop_row.i("id")},
                [&](const Row& contents_row) {
                    Value count = Value::object();
                    count["ex_count"] = (u32)ctx.st.one("select num from exchange_counts where id = ?", {contents_row.i("id")});
                    contents[std::to_string(contents_row.i("id"))] = count;
                });
        shops[std::to_string(shop_row.i("id"))] = contents;
    });
    return shops;
}

// ExshopExchangeList() -> ExshopExchangeListRes                         fid 7329eff2
// API: docs/api.md#exshopexchangelist   Rules: docs/server-rules.md#shops, docs/server-rules.md#shops-modules
//
// The exchange shops open and the player's counts (b: CShop::Progress sends it; docs/api.md Callers).
//   (b) CShop lists only the shops keyed in ExchangeShopExCount (exchange_counts).
// Answers: the player state with ExchangeShopExCount.
std::vector<u8> exshop_exchange_list(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["ExchangeShopExCount"] = exchange_counts(ctx);
    return body(data);
}

// The checks of one exchange.
Refusal exchange_refusal(Ctx& ctx, const Row& contents_row, u32 count) {
    // (a) the shop's window and the row's opened_at; (d) --enable-events: an enabled event's shop
    // and its rows are open all year
    bool enabled = enable_events::exchange_shop(ctx.m, (u32)contents_row.i("master_exchange_shop_id"));
    if (!enabled && (!exchange_window_open(ctx, contents_row.s("shop_opened"), contents_row.s("shop_closed")) ||
                     !exchange_window_open(ctx, contents_row.s("opened_at"), "")))
        return {"closed", ErrorCode::kExchangeExpired};
    // (a) exchange_item_max per request
    if (count > ctx.global_u32("exchange_item_max", 50)) return {"too many at once", ErrorCode::kLimitReached};
    u32 done = (u32)ctx.st.one("select num from exchange_counts where id = ?", {contents_row.i("id")});
    u32 limit = (u32)contents_row.i("ex_limit");  // (a) ex_limit caps the total; 0 = unlimited
    if (limit && done + count > limit) return {"over the limit", ErrorCode::kLimitReached};
    // (a) ex_num of ex_item_id per exchange
    if (stock_count(ctx, (u32)contents_row.i("ex_item_id")) < (u64)contents_row.i("ex_num") * count)
        return {"not enough exchange items", ErrorCode::kItemCountError};
    return {};
}

// The answer of an exchange: ExchangeResult, the counts, what was granted.
Value exchange_data(Ctx& ctx, const Row& contents_row, u32 count, u32 free_coins, const Value& items, const Value& characters) {
    Value data = ctx.base_data();
    Value result = Value::object();
    result["master_exchange_shop_id"] = (u32)contents_row.i("master_exchange_shop_id");
    result["ex_item_id"] = (u32)contents_row.i("ex_item_id");
    result["num"] = count;
    result["AddFreeCoin"] = free_coins;
    data["ExchangeResult"] = result;
    data["ExchangeShopExCount"] = exchange_counts(ctx);
    if (!items.arr.empty()) data["AddItem"] = items;
    if (!characters.arr.empty()) {
        Value add_character = Value::object();
        for (auto& character : characters.arr) add_character[std::to_string(character.get_u("id"))] = character;
        data["AddCharacter"] = add_character;
    }
    data["StockItem"] = ctx.stock();
    return data;
}

// ExshopExchange(u32 master_exchange_shop_contents_id, u32 num) -> ExshopExchangeRes
//                                                                       fid 70d0f3ce
// API: docs/api.md#exshopexchange   Rules: docs/server-rules.md#shops, docs/server-rules.md#shops-modules
//
// Exchanges `num` times one row of an exchange shop.
//   (a) the shop's window and the row's opened_at (or the event calendar's, d), else
//       kExchangeExpired (17001); (a) num <= master_global exchange_item_max (50) and ex_limit
//       (0 = unlimited), else kLimitReached (11006); (a) ex_num x num of ex_item_id, else
//       kItemCountError (10206); an unknown row: kItemUnusable (10208).
//   (a) content x num granted, item sets expanded; the exchange counted (achievements).
// Answers: the player state with ExchangeResult {master_exchange_shop_id, ex_item_id, num,
// AddFreeCoin}, ExchangeShopExCount, StockItem, and AddItem / AddCharacter when granted.
std::vector<u8> exshop_exchange(Ctx& ctx, const Request& req) {
    const auto args = args::ExshopExchangeArgs::from(req);
    u32 id = args.contents_id, count = args.count;
    std::vector<u8> out;
    bool found = false;
    ctx.m.q(
        "select x.*, s.opened_at as shop_opened, s.closed_at as shop_closed from master_exchange_shop_contents x "
        "join master_exchange_shop s on s.id = x.master_exchange_shop_id where x.id = ?",
        {id}, [&](const Row& contents_row) {
            found = true;
            Refusal refusal = exchange_refusal(ctx, contents_row, count);
            if (refusal.why) {
                out = refuse(ctx, "ExshopExchange", refusal.why, refusal.code);
                return;
            }
            u32 ex_item = (u32)contents_row.i("ex_item_id");
            u64 pay = (u64)contents_row.i("ex_num") * count;
            add_stock(ctx, ex_item, -(int64_t)pay);
            ctx.st.q("insert into exchange_counts (id, num) values (?, ?) on conflict(id) do update set num = num + excluded.num", {id, count});
            Value items = Value::array(), stocks = Value::array(), characters = Value::array();
            u32 free_coins = 0;
            grant_with_item_sets(ctx, (u32)contents_row.i("content_type"), (u32)contents_row.i("content_id"),
                                 (u32)std::max<int64_t>(1, contents_row.i("num")) * count, items, stocks, characters, &free_coins);
            ext::count(ctx, "exchange", count);
            Value data = exchange_data(ctx, contents_row, count, free_coins, items, characters);
            LOGI("server", "ExshopExchange %u (%s) x%u: -%llu of item %u", id, contents_row.s("id_label").c_str(), count, (unsigned long long)pay,
                 ex_item);
            out = body(data);
        });
    if (!found) return refuse(ctx, "ExshopExchange", "unknown exchange row", ErrorCode::kItemUnusable);
    return out;
}

// ClientMaster hook (the served master's override). The client's master copy: the exchange shops
// the event calendar has open but the clock hasn't move by the calendar's whole years
// (events::year_shift), with their contents' opened_at (d).
void client_master_shops(Sql& db, ServerTime now, EventTime ev) {
    int years = events::year_shift(now, ev);
    if (years <= 0) return;
    std::vector<std::tuple<int64_t, std::string, std::string>> shops;
    db.q("select id, opened_at, closed_at from master_exchange_shop", {}, [&](const Row& shop_row) {
        if (opened_by_year_shift(shop_row.s("opened_at"), shop_row.s("closed_at"), years, now))
            shops.emplace_back(shop_row.i("id"), shop_row.s("opened_at"), shop_row.s("closed_at"));
    });
    for (auto& [id, opened_at, closed_at] : shops) {
        db.q("update master_exchange_shop set opened_at = ?, closed_at = ? where id = ?",
             {events::shift_years(opened_at, years), events::shift_years(closed_at, years), id});
        std::vector<std::pair<int64_t, std::string>> rows;
        db.q("select id, opened_at from master_exchange_shop_contents where master_exchange_shop_id = ?", {id},
             [&](const Row& contents_row) { rows.emplace_back(contents_row.i("id"), contents_row.s("opened_at")); });
        for (auto& [contents_id, contents_opened] : rows)
            if (!contents_opened.empty())
                db.q("update master_exchange_shop_contents set opened_at = ? where id = ?",
                     {events::shift_years(contents_opened, years), contents_id});
    }
    LOGI("server", "exchange shops: %zu moved %d years in the client's master (event calendar)", shops.size(), years);
}

// OnPlayerLoad hook (Login, GetPlayer, NoLoginStart's full player state).
// Rules: docs/server-rules.md#shops-modules
//   (b) ItemShopInfoList and ExchangeShopExCount are owned state the client keeps; the full-state
//       responses carry them (d: which responses).
// Adds: ItemShopInfoList, ExchangeShopExCount.
void load_shops(Ctx& ctx, const Request&, Value& data) {
    data["ItemShopInfoList"] = item_shop_list(ctx);
    data["ExchangeShopExCount"] = exchange_counts(ctx);
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_shop() {
    using namespace ext;
    add_api({"ItemShopList"}, item_shop_list_api);
    add_api({"ExItemShop"}, ex_item_shop);
    add_api({"ExshopExchangeList"}, exshop_exchange_list);
    add_api({"ExshopExchange"}, exshop_exchange);
    add_client_master(client_master_shops);
    add_player_load(load_shops);
}

}  // namespace soa::server
