// The gacha: GetGachaInData and the draws (Gacha, GachaOnce, SaleGacha, SaleGachaOnce, GachaTicket;
// api/gacha/gacha.h). Port code, not guest behaviour.
// Every rule carries its source label, (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption (docs/server-rules.md#gacha-rules).
#include "api/gacha/gacha.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <optional>

#include "api/events/enable_events.h"  // --enable-events
#include "api/player/player_info.h"    // base_data, player_id, stack_item_info_list
#include "core/errors.h"
#include "core/log.h"
#include "core/request_args.h"
#include "core/response.h"
#include "core/rewards.h"  // add_character
#include "core/server.h"   // next_uid
#include "core/time.h"     // open_at
#include "core/wallet.h"
#include "master/gacha_pools.h"
#include "rules/mission_rules.h"

namespace soa::server {

using ext::body;
using ext::Row;

namespace {

// (a) master content type 1: an item (a weapon, when a gacha draws it: gacha_pools::Unit).
constexpr u32 kContentTypeItem = 1;
// gacha_history.rank: the draw's rank as a letter, S (index 0) .. D (4) (d: our column).
constexpr const char* kRankLetters = "SABCD";
// (d) GetGachaInData's window for a master row without one: open since the service start / for good.
constexpr const char* kOpenedForever = "2016-01-01 00:00:00";
constexpr const char* kClosedNever = "2099-12-31 23:59:59";

// (d) --enable-events: a gacha whose name matches the keywords is open all year (and its
// client-side window is widened to match, enable_events::client_master)
bool gacha_enabled(ext::Ctx& ctx, const Row& gacha_row) {
    ext::Sql master{ctx.m.h};
    return enable_events::gacha(master, (u32)gacha_row.i("id"));
}

}  // namespace

bool gacha_open(ext::Ctx& ctx, const Row& gacha_row, ServerTime t) {  // (a) master_gacha.opened_at / closed_at
    if (gacha_enabled(ctx, gacha_row)) return true;
    return open_at(gacha_row.s("opened_at"), gacha_row.s("closed_at"), t);
}

namespace {

// One GachaHashMap entry: {GachaHashList: [{master_gacha_id, hash, opened_at, closed_at}]} (b:
// CGacha::IsEnableHash needs the entry's window to hold the clock).
Value gacha_hash_entry(ext::Ctx& ctx, const Row& gacha_row) {
    Value hash_info = Value::object();
    hash_info["master_gacha_id"] = (u32)gacha_row.i("id");
    char hash[16];
    snprintf(hash, sizeof hash, "%08x", (u32)gacha_row.i("id"));  // (d) any string: the client only echoes it
    hash_info["hash"] = hash;
    if (gacha_enabled(ctx, gacha_row)) {  // (d) the window the client's master copy got
        hash_info["opened_at"] = enable_events::kOpenedAt;
        hash_info["closed_at"] = enable_events::kClosedAt;
    } else {
        hash_info["opened_at"] = gacha_row.s("opened_at").empty() ? kOpenedForever : gacha_row.s("opened_at");
        hash_info["closed_at"] = gacha_row.s("closed_at").empty() ? kClosedNever : gacha_row.s("closed_at");
    }
    Value entry = Value::object();
    entry["GachaHashList"] = Value::array();
    entry["GachaHashList"].push(hash_info);
    return entry;
}

}  // namespace

// GetGachaInData() -> GetGachaInDataRes                                fid 8e4a88d7
// API: docs/api.md#getgachaindata   Rules: docs/server-rules.md#gacha-open, docs/server-rules.md#gacha-step-up-box-rules
//
// The gacha screen's banners (b: CGacha::Initialize sends it; docs/api.md Callers).
//   (a) every master_gacha row open at the server clock (gacha_open; --enable-events adds the
//       matching ones, d) gets a GachaHashMap entry keyed by its id.
//   (a)+(b) StepUpGacha: the step-up chains open at the clock (stepup.cpp).
//   (b) BoxGachaList: the box series open at the clock, the イベントガチャ tab
//       (CGacha::AddListBoxSeries; box.cpp).
// Answers: the player state with GachaHashMap, StepUpGacha and BoxGachaList.
std::vector<u8> get_gacha_in_data(ext::Ctx& ctx, const Request&) {
    Value hash_map = Value::object();
    ServerTime t = clock_now();
    int open = 0;
    ctx.m.q("select * from master_gacha order by id", {}, [&](const Row& gacha_row) {
        if (!gacha_open(ctx, gacha_row, t)) return;
        hash_map[std::to_string((u32)gacha_row.i("id"))] = gacha_hash_entry(ctx, gacha_row);
        open++;
    });
    Value data = base_data(ctx);
    data["GachaHashMap"] = hash_map;
    data["StepUpGacha"] = stepup_gacha_info(ctx);  // (a)+(b) the step-up chains open at the clock
    // (b) the box series open at the clock: the イベントガチャ tab (CGacha::AddListBoxSeries)
    data["BoxGachaList"] = box_gacha_list_info(ctx);
    LOGI("server", "GetGachaInData: %d gachas open at %s", open, format_time(t).c_str());  // read by gacha_session.sh, nier_demo.sh
    return body(data);
}

namespace {
// Pools (d, the method): master_gacha's table_name tables aren't in either master DB, so
// the pool is rebuilt from master_role (docs/server-rules.md#gacha-rates): S and A = ★5 and up
// (rarity 5 and 6, role ranks 3..5), S from the banner's master_gacha_pickup group when it
// has one; B = rarity 4; C and D = rarity 3 ((a)+(c): the rates and banner texts, e.g.
// gacha_role_0001's bonus rates C 0 / B 84 and "10連で★4以上のキャラが1体確定!"). Only roles
// released (opened_at) by the server's clock (d). Characters only, no weapons (d).
// The fallback when the reconstructed pools (master/gacha_pools.h) aren't there.
u32 draw_role(ext::Ctx& ctx, const Row& gacha_row, int rank) {
    std::vector<u32> pool;
    // (d) roles already released at the server's clock (a banner's own opened_at is too early
    // for the permanent banners: gacha_role_0001 opened 2016-01-01)
    std::string opened = format_time(clock_now());
    if (rank == 0 && !gacha_row.null("gacha_pickup_group_id"))
        ctx.m.q("select master_role_id from master_gacha_pickup where pickup_group_id = ?", {gacha_row.i("gacha_pickup_group_id")},
                [&](const Row& pickup_row) { pool.push_back((u32)pickup_row.i("master_role_id")); });
    if (pool.empty()) {
        std::string sql = rank <= 1 ? "rarity in (5, 6) and rank between 3 and 5" : rank == 2 ? "rarity = 4" : "rarity = 3";
        ctx.m.q("select id from master_role where id_label like 'role_c%' and " + sql +
                    " and (opened_at is null or opened_at = '' or opened_at <= ?) order by id",
                {opened}, [&](const Row& role_row) { pool.push_back((u32)role_row.i("id")); });
        if (pool.empty())  // (d) no dated role fits: the whole rarity
            ctx.m.q("select id from master_role where id_label like 'role_c%' and " + sql + " order by id", {},
                    [&](const Row& role_row) { pool.push_back((u32)role_row.i("id")); });
    }
    return pool.empty() ? 0 : pool[(*ctx.rng)() % pool.size()];
}

// A draw in progress (gacha() below): its count and price, the step-up chain, the coins it
// takes and what it drew.
struct GachaDraw {
    u32 id = 0;
    bool once = false;
    u32 count = 0, price = 0;
    u32 ticket = 0, tickets = 0;
    std::vector<u32> chain;  // the step-up chain (empty: not a step-up)
    int step = 0;
    u32 use_free = 0, use_pay = 0;
    // What it drew: GachaItems, AddCharacter, LimitBreakCharacter, LimitBreakItem, AddItem,
    // CharacterChipInfoList.
    Value items, added_characters, limit_breaks, limit_break_items, new_items, chips;
};

// 1. The count and price: once or bulk, sale, or tickets.
void count_and_price(const Request& req, const args::GachaArgs& args, const Row& gacha_row, GachaDraw& draw) {
    // (a) count and price from master_gacha: once = coin (sale_once_coin on sale),
    // bulk = bulk_count for bulk_coin (sale_bulk_coin on sale).
    bool sale = req.method.rfind("Sale", 0) == 0;
    // (b) Gacha(id, hash, n): CGacha::RequestGacha sends n = 1 when the selected button is the
    // single draw (CGacha+0x2d4 == 1; 1回ガチャ, as SaleGachaOnce there) and n = 0 for the
    // bulk draw (as SaleGacha); GachaOnce / SaleGachaOnce are single draws by name
    draw.once = req.method.find("Once") != std::string::npos || (req.method == "Gacha" && args.n == 1);
    draw.count = draw.once ? 1 : std::max<u32>(1, (u32)gacha_row.i("bulk_count"));
    draw.price = draw.once ? (u32)(sale && !gacha_row.null("sale_once_coin") ? gacha_row.i("sale_once_coin") : gacha_row.i("coin"))
                           : (u32)(sale && !gacha_row.null("sale_bulk_coin") ? gacha_row.i("sale_bulk_coin") : gacha_row.i("bulk_coin"));
    if (req.method == "GachaTicket") {
        draw.count = args.n ? (u32)args.n : 1;  // (d) arg 2 = draws
        draw.ticket = (u32)gacha_row.i("ticket_item_id");
        draw.tickets = (u32)std::max<int64_t>(1, gacha_row.i("ticket_num")) * draw.count;
        draw.price = 0;
    }
}

// 2. A step-up gacha: only the chain's current step can be drawn (false: refused, `refusal`).
bool check_stepup(ext::Ctx& ctx, const Request& req, const Row& gacha_row, GachaDraw& draw, std::vector<u8>& refusal) {
    // Currency: (a) free coins first, then paid (core/wallet.h); (a) is_pay_coin = paid coins only.
    // Step-up (a): is_stepup rows chain through next_stepup_gacha_id; only the chain's
    // current step can be drawn ((d) another step is refused with 10403 不正なデータ処理).
    if (gacha_row.i("is_stepup")) {
        draw.chain = stepup_chain(ctx, draw.id);
        // No stepup row = the chain's head. (next_id is never NULL: advance_stepup always writes a
        // chain id, so the NULL-as-0 read and plain one() agree; kept by name, PLAN-readability 1.5.)
        draw.step = mission_rules::stepup_index(
            draw.chain, (u32)one_null_as_zero(ctx.st, "select next_id from stepup where head = ?", {draw.chain[0]}, draw.chain[0]));
        if (draw.chain[draw.step] != draw.id ||
            stepup_closed(ctx, draw.id, (u32)ctx.st.one("select restart_count from stepup where head = ?", {draw.chain[0]}))) {
            refusal = ext::refusef(ctx, req.method.c_str(), ErrorCode::kInvalidOperation, "gacha %u: step-up chain %u is at step %d, not this one",
                                   draw.id, draw.chain[0], draw.step + 1);
            return false;
        }
    }
    return true;
}

// 3. Pays the coins (free first) or the tickets (false: refused, `refusal`).
bool pay_draw(ext::Ctx& ctx, const Request& req, const Row& gacha_row, GachaDraw& draw, std::vector<u8>& refusal) {
    wallet::Coins have = wallet::coins(ctx.st.h);
    u32 free_coins = have.free, paid_coins = have.paid;
    wallet::CoinSplit pay = wallet::split(have, draw.price, gacha_row.i("is_pay_coin") != 0);  // (a) is_pay_coin: paid coins only
    draw.use_free = pay.free, draw.use_pay = pay.paid;
    if (!wallet::covers(have, draw.price, gacha_row.i("is_pay_coin") != 0) ||
        (draw.ticket && ctx.st.one("select ifnull(sum(count),0) from stock where master_item_id = ?", {draw.ticket}) < draw.tickets)) {
        // (a) master_text error_message_text_20000 紋章石が不足しています ((d) of 20000 / 20003);
        // a ticket short: (d) 10206 アイテムの所持数エラー
        refusal = ext::refusef(ctx, req.method.c_str(), draw.use_pay > paid_coins ? ErrorCode::kCoinsShort : ErrorCode::kItemCountError,
                               "gacha %u: not enough currency (price %u, free %u, paid %u)", draw.id, draw.price, free_coins, paid_coins);
        return false;
    }
    wallet::take(ctx.st.h, pay);
    if (draw.ticket) ext::add_stock(ctx, draw.ticket, -(int64_t)draw.tickets);  // checked above: never below 0
    return true;
}

// The gacha_history row of one unit: a character (its role and uid) or a weapon (its item uid;
// no role); the coins of the whole draw on its first unit (k == 0).
struct Drawn {
    std::optional<RoleId> role;
    std::optional<CharacterUid> character;
    std::optional<ItemUid> item;
};
void record_history(ext::Ctx& ctx, const GachaDraw& draw, const Drawn& drawn, int rank, bool duplicate, u32 k) {
    ctx.st.q(
        "insert into gacha_history (gacha_id, at, role_id, character_uid, item_uid, rank, duplicate, cost_free, cost_pay) "
        "values (?,?,?,?,?,?,?,?,?)",
        {draw.id, clock_now(), drawn.role, drawn.character, drawn.item, std::string(1, kRankLetters[rank]), duplicate ? 1 : 0,
         k == 0 ? draw.use_free : 0u, k == 0 ? draw.use_pay : 0u});
}

// 4a. A drawn weapon: a new unique item (AddItem) and the history row; with no room in the
// inventory it goes to the overflow box (storage::to_one_time_storage; AddOneTimeStorageInfo):
// (d) then the GachaItems entry has no item (player_item_id 0) and the history row no uid.
void draw_weapon(ext::Ctx& ctx, GachaDraw& draw, const gacha_pools::Unit& unit, int rank, u32 k) {
    std::optional<ItemUid> drawn;
    if (storage::to_one_time_storage(ctx, storage::EquipSource::kGacha)) {
        storage::add_one_time(ctx, MasterItemId(unit.content_id), 1);
    } else {
        const ItemUid item_uid = next_item_uid(ctx);
        drawn = item_uid;
        u32 item_type = (u32)ctx.m.one("select type from master_item where id = ?", {unit.content_id});
        ctx.st.q("insert into items (uid, master_item_id, item_type, created_at) values (?,?,?,?)",
                 {item_uid, unit.content_id, item_type, clock_now()});
        Value item = Value::object();  // CItemInfo
        item["id"] = item_uid.v;
        item["player_id"] = player_id(ctx).v;
        item["master_item_id"] = unit.content_id;
        item["item_type"] = item_type;
        item["boosted_point"] = 0u;
        item["limit_break_count"] = 0u;
        draw.new_items.push(item);
    }
    Value result = Value::object();  // the GachaItems entry
    result["master_item_id"] = unit.content_id;
    result["player_item_id"] = drawn ? drawn->v : (u64)0;
    result["master_role_id"] = 0u;
    result["player_character_id"] = 0u;
    result["duplication"] = 0u;
    result["is_mutation"] = false;
    draw.items.push(result);
    record_history(ctx, draw, Drawn{std::nullopt, std::nullopt, drawn}, rank, false, k);
}

// (b) LimitBreakCharacter: map uid -> CLimitBreakInfo; the result screen assigns the steps to the
// duplicates in draw order, AddLimitBreak syncs it.
void add_limit_break(GachaDraw& draw, const Added& added) {
    Value& limit_break = draw.limit_breaks[std::to_string(added.uid.v)];
    if (limit_break.type != Value::Map) {
        limit_break = Value::object();
        limit_break["id"] = added.uid.v;
        limit_break["master_role_id"] = added.owned_role;
        limit_break["before_master_role_id"] = added.owned_role;
        limit_break["after_master_role_id"] = added.owned_role;
        limit_break["before_limit_break_count"] = added.lb_before;
    }
    limit_break["after_limit_break_count"] = added.lb_after;
}

// Character chips for a duplicate (4.3): (a) the role's universe_chip_item_id on a gacha with
// universe_chip_flg; (d) chip x chip_rate / 100 of the master_universe_chip_gacha_exchange row of
// the role's rank per duplicate. Sent as CharacterChipInfoList {uid: {id, master_role_id,
// master_item_id, num}} (b: the element is a CLimitBreakItemInfo {id, master_role_id,
// master_item_id, num}; CLimitOverCharacter::CountCharaChip splits num over the duplicates of
// that character) and added to the stack items.
void add_chips(ext::Ctx& ctx, GachaDraw& draw, u32 role, CharacterUid uid) {
    u32 chip_item = (u32)ctx.m.one("select ifnull(universe_chip_item_id, 0) from master_role where id = ?", {role});
    u32 chips = (u32)ctx.m.one(
        "select cast(chip * chip_rate / 100 as integer) from master_universe_chip_gacha_exchange where rank = "
        "(select rank from master_role where id = ?)",
        {role});
    if (!chip_item || !chips) return;
    ext::add_stock(ctx, chip_item, chips);  // (a) capped at master_global item_stock_max_num
    Value& chip_info = draw.chips[std::to_string(uid.v)];
    if (chip_info.type != Value::Map) {
        chip_info = Value::object();
        chip_info["id"] = uid.v;
        chip_info["master_role_id"] = role;
        chip_info["master_item_id"] = chip_item;
        chip_info["num"] = 0u;
    }
    chip_info["num"] = chip_info["num"].u + chips;
}

// 4b. A drawn character: new, or a duplicate (limit break, its material, character chips); the
// result entry and the history row.
void add_drawn_role(ext::Ctx& ctx, GachaDraw& draw, u32 role, int rank, u32 k, bool chip_gacha) {
    Added added = add_character(ctx, RoleId(role));
    bool duplicate = added.dup;
    const CharacterUid uid = added.uid;
    if (duplicate && added.lb_after > added.lb_before) {
        add_limit_break(draw, added);
    } else if (duplicate && added.item) {
        Value limit_break_item = Value::object();  // (b) CLimitBreakItemInfo
        limit_break_item["master_role_id"] = role;
        limit_break_item["master_item_id"] = added.item;
        draw.limit_break_items.push(limit_break_item);
    }
    if (duplicate && chip_gacha) add_chips(ctx, draw, role, uid);
    Value result = Value::object();  // the GachaItems entry
    result["master_item_id"] = 0u;
    result["player_item_id"] = 0u;
    result["master_role_id"] = role;
    result["player_character_id"] = uid.v;
    result["duplication"] = duplicate ? 1u : 0u;
    result["is_mutation"] = false;
    draw.items.push(result);
    if (!duplicate) {
        Value character = Value::object();  // the AddCharacter entry
        character["id"] = uid.v;
        character["master_role_id"] = role;
        character["level"] = 1u;
        character["exp"] = 0u;
        character["limit_break_count"] = 0u;
        character["awaken_level"] = 0u;
        draw.added_characters[std::to_string(uid.v)] = character;
    }
    record_history(ctx, draw, Drawn{RoleId(role), uid, std::nullopt}, rank, duplicate, k);
}

// 4. The draws: a rank by the rates, a unit from the pools (or by rarity), duplicates, limit
// breaks, character chips, the history.
void draw_units(ext::Ctx& ctx, const Row& gacha_row, GachaDraw& draw) {
    // (a) rank rates s..d_rank_rate (percent); (d) is_bulk_bonus's bonus rates are used
    // for the last draw of a bulk draw.
    const char* rate_columns[5] = {"s_rank_rate", "a_rank_rate", "b_rank_rate", "c_rank_rate", "d_rank_rate"};
    const char* bonus_columns[4] = {"bonus_s_rank_rate", "bonus_a_rank_rate", "bonus_b_rank_rate", "bonus_c_rank_rate"};
    draw.items = Value::array(), draw.added_characters = Value::object(), draw.limit_breaks = Value::object();
    draw.limit_break_items = Value::array(), draw.new_items = Value::array(), draw.chips = Value::object();
    bool chip_gacha = !gacha_row.null("universe_chip_flg") && gacha_row.i("universe_chip_flg");  // (a) master_gacha.universe_chip_flg
    for (u32 k = 0; k < draw.count; k++) {
        std::vector<u32> weights;
        bool bonus = !draw.once && gacha_row.i("is_bulk_bonus") && k + 1 == draw.count;
        for (int j = 0; j < 5; j++)
            weights.push_back((u32)std::lround(100.0 * (bonus && j < 4 ? gacha_row.f(bonus_columns[j]) : gacha_row.f(rate_columns[j]))));
        u64 sum = 0;
        for (u32 w : weights) sum += w;
        int rank = sum ? rules::weighted_pick(weights, (*ctx.rng)() % sum) : 3;
        // The reconstructed pools (docs/server-rules.md#gacha-pools) when present: the rank by the
        // banner's rates over ranks with a released unit, then a unit of that rank.
        // Without them, draw_role's rarity pools.
        gacha_pools::Unit unit;
        int pool_rank = rank;
        u32 role = 0;
        if (ctx.pools->is_open() && ctx.pools->draw(draw.id, bonus, format_time(clock_now()), (*ctx.rng)(), (*ctx.rng)(), pool_rank, unit)) {
            rank = pool_rank;
            if (unit.content_type == kContentTypeItem) {  // a weapon: a new unique item (AddItem)
                draw_weapon(ctx, draw, unit, rank, k);
                continue;
            }
            role = unit.content_id;
        } else {
            role = draw_role(ctx, gacha_row, rank);
        }
        add_drawn_role(ctx, draw, role, rank, k, chip_gacha);
    }
}

// 5a. A step-up draw moves its chain on: (a) StepUpGacha {player_id, master_gacha_id (d: the
// chain's step 1), try_count, restart_count, next_master_gacha_id}; a draw of the last step loops
// to step 1. (a)+(b) a step is drawn stepup_limit_count times (1 in every 3.7.0 row) before the
// chain moves on; try_count counts the draws on the current step.
void advance_stepup(ext::Ctx& ctx, const Request& req, GachaDraw& draw, Value& data) {
    u32 tries = (u32)ctx.st.one("select try_count from stepup where head = ? and next_id = ?", {draw.chain[0], draw.id}) + 1;
    u32 limit = (u32)std::max<int64_t>(1, ctx.m.one("select ifnull(stepup_limit_count, 1) from master_gacha where id = ?", {draw.id}));
    auto [next, restarted] = tries >= limit ? mission_rules::stepup_advance(draw.chain, draw.step) : std::pair<int, u32>{draw.step, 0};
    ctx.st.q(
        "insert into stepup (head, try_count, restart_count, next_id) values (?, ?, ?, ?) "
        "on conflict(head) do update set try_count = excluded.try_count, "
        "restart_count = restart_count + excluded.restart_count, next_id = excluded.next_id",
        {draw.chain[0], tries >= limit ? 0u : tries, restarted, draw.chain[next]});
    data["UpdateStepUpGacha"] = stepup_gacha_info(ctx, draw.chain[0]);  // (b) merged by key: this chain's steps
    data["StepUpGacha"] = stepup_gacha_info(ctx);
    LOGI("server", "%s %u: step-up chain %u step %d -> %d%s", req.method.c_str(), draw.id, draw.chain[0], draw.step + 1, next + 1,
         restarted ? " (restart)" : "");  // read by restore_missions.sh
}

// 5. The step-up advance and the answer's data.
Value gacha_data(ext::Ctx& ctx, const Request& req, const Row& gacha_row, GachaDraw& draw) {
    Value data = base_data(ctx);
    if (!draw.chain.empty()) advance_stepup(ctx, req, draw, data);
    data["GachaItems"] = draw.items;
    data["AddCharacter"] = draw.added_characters;
    if (!draw.new_items.arr.empty()) data["AddItem"] = draw.new_items;
    if (!draw.limit_breaks.map.empty()) data["LimitBreakCharacter"] = draw.limit_breaks;
    if (!draw.limit_break_items.arr.empty()) data["LimitBreakItem"] = draw.limit_break_items;
    if (!draw.chips.map.empty()) data["CharacterChipInfoList"] = draw.chips;
    if (!draw.limit_break_items.arr.empty() || !draw.chips.map.empty()) data["StockItem"] = stack_item_info_list(ctx);
    LOGI("server", "%s %u (%s): %u draws for %u free + %u paid coins, %u tickets", req.method.c_str(), draw.id, gacha_row.s("id_label").c_str(),
         draw.count, draw.use_free, draw.use_pay, draw.tickets);  // read by gacha_session.sh, nier_demo.sh, summer_demo.sh
    return data;
}

}  // namespace

// Gacha(u32 master_gacha_id, s8 const* hash, u32 once) / GachaOnce(u32 gacha, hash) /
// SaleGacha(u32 gacha, hash) / SaleGachaOnce(u32 gacha, hash) /
// GachaTicket(u32 gacha, u32 ticket_count, hash) -> <Method>Res
//                                       fids a0a1940b, 992ccbe5, b164b4c5, 2d230806, ee11c3d3
// API: docs/api.md#gacha   Rules: docs/server-rules.md#gacha-rules, docs/server-rules.md#gacha-step-up-box
//
// A draw: GachaOnce one unit for `coin`, Gacha the bulk draw (or the single one, once = 1),
// SaleGacha / SaleGachaOnce at the sale prices, GachaTicket ticket_item_id x ticket_num per draw.
//   (a) the count, price and currency from master_gacha (count_and_price); free coins first,
//       is_pay_coin = paid coins only (core/wallet.h).
//   (d) a step-up step that isn't the chain's current one is refused with kInvalidOperation (10403).
//   (a) coins short: kCoinsShort (20000); (d) tickets short: kItemCountError (10206).
//   (a)+(d) each unit: a rank by the rates, then a unit from the reconstructed pools (4.5) or by
//       rarity (draw_role); duplicates raise the limit break or give its item, chips (4.3).
// Answers: the player state with GachaItems, AddCharacter, and when they changed AddItem,
// LimitBreakCharacter, LimitBreakItem, CharacterChipInfoList, StockItem; a step-up draw also
// UpdateStepUpGacha and StepUpGacha. An unknown gacha isn't handled (no body).
std::vector<u8> gacha(ext::Ctx& ctx, const Request& req) {
    const auto args = args::GachaArgs::from(req);
    GachaDraw draw;
    draw.id = args.gacha_id;
    Value data;
    bool found = false;
    std::vector<u8> refusal;  // the answer of a refused draw
    ctx.m.q("select * from master_gacha where id = ?", {draw.id}, [&](const Row& gacha_row) {
        found = true;
        count_and_price(req, args, gacha_row, draw);
        if (!check_stepup(ctx, req, gacha_row, draw, refusal)) return;
        if (!pay_draw(ctx, req, gacha_row, draw, refusal)) return;
        draw_units(ctx, gacha_row, draw);
        data = gacha_data(ctx, req, gacha_row, draw);
    });
    if (!found) {
        LOGW("server", "%s: unknown gacha %u", req.method.c_str(), draw.id);
        return {};
    }
    if (!refusal.empty()) return refusal;
    return body(data);
}

// The gacha's APIs (src/core/modules.cpp: the core's APIs first).
void register_gacha() {
    ext::add_core_api({"GetGachaInData"}, get_gacha_in_data);
    ext::add_core_api({"Gacha", "GachaOnce", "SaleGacha", "SaleGachaOnce", "GachaTicket"}, gacha);
}

}  // namespace soa::server
