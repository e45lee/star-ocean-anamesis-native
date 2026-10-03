// Box gacha: BoxGacha, ResetBoxGacha, GetBoxGacha and the box lists (api/gacha/gacha.h). Port
// code, not guest behaviour.
// Every rule carries its source label, (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption (docs/server-rules.md "4. Gacha", "Gacha: step-up and box",
// "Step-up and box gacha lists").
#include "api/gacha/gacha.h"

#include <algorithm>
#include <map>
#include <set>

#include "api/events/enable_events.h"  // gacha_shown: a series without its banner isn't listed
#include "api/player/player_info.h"    // base_data, player_id, stack_item_info_list
#include "core/errors.h"
#include "core/log.h"
#include "core/request_args.h"
#include "core/response.h"
#include "core/rewards.h"  // grant
#include "rules/mission_rules.h"

namespace soa::server {

using ext::body;
using ext::Row;

namespace {

// (d) a guard against a malformed series: no 3.7.0 series has more than 6 boxes (a: box_gacha_index).
constexpr size_t kMaxSeriesBoxes = 32;

// (a) a master_gacha row with is_box is one box; its slots are the master_box_gacha rows of
// that gacha, box_count copies each; (c) drawing without replacement.
struct BoxSlot {
    u32 id, content_type, content_id, num, copies, drawn;
    u32 left() const { return copies - std::min(copies, drawn); }
};

std::vector<BoxSlot> box_slots(ext::Ctx& ctx, u32 gacha) {
    std::vector<BoxSlot> slots;
    ctx.m.q("select * from master_box_gacha where master_gacha_id = ? order by order_id, id", {gacha}, [&](const Row& slot_row) {
        slots.push_back({(u32)slot_row.i("id"), (u32)slot_row.i("content_type"), (u32)slot_row.i("content_id"),
                         (u32)std::max<int64_t>(1, slot_row.i("num")), (u32)std::max<int64_t>(1, slot_row.i("box_count")), 0});
    });
    for (auto& slot : slots) slot.drawn = (u32)ctx.st.one("select drawn from box_slots where gacha_id = ? and slot_id = ?", {gacha, slot.id});
    return slots;
}

}  // namespace

// BoxGacha / UpdateBoxGacha: IInfoBaseMap<u64, CBoxGachaInfo>, a map keyed by id (b: an array
// is ignored). CBoxGachaInfo {player_id, master_gacha_id, master_box_gacha_id, max_box_count,
// box_num, order_id, content_id, content_type, num, is_maintenance} (b: its Initialize).
// CApiNotify::UpdateBoxGacha merges by key and copies only box_num, so box_num is the copies
// left and the key one slot (key = master_box_gacha_id). CGachaBoxDetail lists the entries whose
// master_gacha_id is the box, with order_id, content_type, box_num and num ("×%u") (b).
Value box_gacha_info(ext::Ctx& ctx, u32 gacha, Value* into) {
    Value info = Value::object();
    u32 player = player_id(ctx);
    std::map<u32, u32> order, num;
    ctx.m.q("select id, order_id, num from master_box_gacha where master_gacha_id = ?", {gacha}, [&](const Row& slot_row) {
        order[(u32)slot_row.i("id")] = (u32)slot_row.i("order_id");
        num[(u32)slot_row.i("id")] = (u32)slot_row.i("num");
    });
    for (auto& slot : box_slots(ctx, gacha)) {
        Value entry = Value::object();
        entry["player_id"] = player;
        entry["master_gacha_id"] = gacha;
        entry["master_box_gacha_id"] = slot.id;
        entry["max_box_count"] = slot.copies;
        entry["box_num"] = slot.left();  // (b) the copies left
        entry["order_id"] = order[slot.id];
        entry["content_id"] = slot.content_id;
        entry["content_type"] = slot.content_type;
        entry["num"] = num[slot.id];  // (a) master_box_gacha.num as it is
        entry["is_maintenance"] = false;
        (into ? *into : info)[std::to_string(slot.id)] = entry;
    }
    return info;
}

namespace {

u32 box_left(ext::Ctx& ctx, u32 gacha) {
    u32 left = 0;
    for (auto& slot : box_slots(ctx, gacha)) left += slot.left();
    return left;
}

// A box series (a): the box with default_release = 1 first, then next_box_gacha_id (the last
// box points to itself). The current box is the first one with copies left, or the last.
std::vector<u32> box_series(ext::Ctx& ctx, u32 head) {
    std::vector<u32> series;
    std::set<u32> seen;
    u32 box = head;
    while (box && seen.insert(box).second && series.size() < kMaxSeriesBoxes) {
        u32 next = 0;
        ctx.m.q("select next_box_gacha_id from master_gacha where id = ? and is_box = 1", {box}, [&](const Row& gacha_row) {
            series.push_back(box);
            next = gacha_row.null("next_box_gacha_id") ? 0 : (u32)gacha_row.i("next_box_gacha_id");
        });
        box = next;
    }
    return series;
}

u32 box_series_head(ext::Ctx& ctx, u32 box) {  // (a) the default_release box whose series holds this box
    u32 head = 0;
    ctx.m.q("select id from master_gacha where is_box = 1 and default_release = 1 order by id", {}, [&](const Row& gacha_row) {
        if (head) return;
        for (u32 member : box_series(ctx, (u32)gacha_row.i("id")))
            if (member == box) head = (u32)gacha_row.i("id");
    });
    return head ? head : box;
}

// The series to list: the one holding `only`, else every open series whose banner is shown.
std::vector<u32> listed_series_heads(ext::Ctx& ctx, u32 only, int64_t t) {
    std::vector<u32> heads;
    if (only) {
        heads.push_back(box_series_head(ctx, only));
        return heads;
    }
    // (b)+(d) a series whose list banner image isn't present isn't listed: its row would be
    // an empty frame (seen on screen), as for --enable-events (enable_events::gacha_shown)
    ext::Sql master{ctx.m.h};
    ctx.m.q("select * from master_gacha where is_box = 1 and default_release = 1 order by id", {}, [&](const Row& gacha_row) {
        if (gacha_open(ctx, gacha_row, t) && enable_events::gacha_shown(master, (u32)gacha_row.i("id"))) heads.push_back((u32)gacha_row.i("id"));
    });
    return heads;
}

}  // namespace

// BoxGachaList / UpdateBoxGachaList: IInfoBaseMap<u64, CBoxGachaListInfo> (b), a map keyed by
// id. CBoxGachaListInfo {player_id, master_gacha_id, box_num, total_count, reset_count,
// is_close, is_reset, next_master_gacha_id, is_maintenance} (b: its Initialize).
// CApiNotify::UpdateBoxGacha merges UpdateBoxGachaList by key without copying master_gacha_id,
// so a key is one box (key = master_gacha_id). CGacha::AddListBoxSeries lists (イベントガチャ
// tab) the box of every entry with is_close == 0 and box_num != 0; RemoveInactiveBox drops a
// listed box whose entry has is_close or box_num == 0; CreateBoxData keeps box_num
// (CGacha+0xad8), which CGachaBoxDetail shows as ボックス残数 (box remaining count) (b). So:
// every box of an open series up to the current one, the earlier ones is_close; box_num = the
// copies left in the box (b: the label; seen on screen: a full 20-copy box showed 1 when box_num
// was the box's index); is_reset = is_manual_reset (d).
// only: just the series of that box (the draw's update), whether open or not.
Value box_gacha_list_info(ext::Ctx& ctx, u32 only, Value* slots) {
    Value info = Value::object();
    u32 player = player_id(ctx);
    int64_t t = clock_now();
    for (u32 head : listed_series_heads(ctx, only, t)) {
        auto series = box_series(ctx, head);
        if (series.empty()) continue;
        size_t current = 0;
        while (current + 1 < series.size() && !box_left(ctx, series[current])) current++;
        for (size_t k = 0; k <= current; k++) {
            u32 id = series[k];
            Value entry = Value::object();
            entry["player_id"] = player;
            entry["master_gacha_id"] = id;
            entry["box_num"] = box_left(ctx, id);  // (b) the copies left (the detail's ボックス残数)
            entry["total_count"] = (u32)ctx.st.one("select total_count from box_state where gacha_id = ?", {id});
            entry["reset_count"] = (u32)ctx.st.one("select reset_count from box_state where gacha_id = ?", {id});
            entry["is_close"] = k < current;
            entry["is_reset"] = ctx.m.one("select ifnull(is_manual_reset, 0) from master_gacha where id = ?", {id}) != 0;
            // (a) an empty box moves on to next_box_gacha_id (the last box points to itself)
            entry["next_master_gacha_id"] = k + 1 < series.size() && !box_left(ctx, id) ? series[k + 1] : id;
            entry["is_maintenance"] = false;
            info[std::to_string(id)] = entry;
            if (slots && k == current) box_gacha_info(ctx, id, slots);
        }
    }
    return info;
}

namespace {

// A box's ticket: (a) ticket_item_id x ticket_num per draw (event coins).
struct BoxTicket {
    bool is_box = false;
    u32 item = 0, per_draw = 0;
};
BoxTicket box_ticket(ext::Ctx& ctx, u32 gacha) {
    BoxTicket ticket;
    ctx.m.q("select * from master_gacha where id = ?", {gacha}, [&](const Row& gacha_row) {
        ticket.is_box = gacha_row.i("is_box") != 0;
        ticket.item = (u32)gacha_row.i("ticket_item_id");
        ticket.per_draw = (u32)std::max<int64_t>(1, gacha_row.i("ticket_num"));
    });
    return ticket;
}

// What the draws granted: grant()'s lists and BoxGachaItems.
struct BoxDraws {
    Value results = Value::array(), items = Value::array(), stocks = Value::array(), characters = Value::array();
};

// `count` draws without replacement (rules box_pick over the copies left), each slot's content
// granted as a drop is (core/rewards.cpp grant).
BoxDraws draw_slots(ext::Ctx& ctx, u32 gacha, std::vector<BoxSlot>& slots, std::vector<u32>& left, u32 count) {
    BoxDraws draws;
    for (u32 k = 0; k < count; k++) {
        int i = mission_rules::box_pick(left, (*ctx.rng)());
        if (i < 0) break;
        left[i]--;
        BoxSlot& slot = slots[i];
        ctx.st.q("insert into box_slots values (?,?,1) on conflict(gacha_id, slot_id) do update set drawn = drawn + 1", {gacha, slot.id});
        grant(ctx, Drop{slot.content_type, slot.content_id, slot.num, 0}, draws.items, draws.stocks, draws.characters);
        // (b) CBoxGachaResultInfo {id, master_box_gacha_id, content_id, content_type, num,
        // duplication} (its Initialize; the result list shows "×num"); id = the draw's index (d)
        Value result = Value::object();
        result["id"] = k + 1;
        result["master_box_gacha_id"] = slot.id;
        result["content_id"] = slot.content_id;
        result["content_type"] = slot.content_type;
        result["num"] = slot.num;
        result["duplication"] = 0u;
        draws.results.push(result);
    }
    return draws;
}

// (b)+(d) the series' last box ("∞", next_box_gacha_id = itself or none) refills once
// emptied: the box banners say "∞ボックスは繰り返し召喚できます" (the ∞ box can be drawn
// again and again), and an emptied box has box_num 0, which the client drops from the list
// (CGacha::RemoveInactiveBox), so it couldn't be reset any more. Counted as a reset.
void refill_last_box(ext::Ctx& ctx, u32 gacha) {
    if (box_left(ctx, gacha)) return;
    int64_t next = ctx.m.one("select ifnull(next_box_gacha_id, 0) from master_gacha where id = ?", {gacha});
    if (next && (u32)next != gacha) return;
    ctx.st.q("delete from box_slots where gacha_id = ?", {gacha});
    ctx.st.q("insert into box_state (gacha_id, reset_count) values (?, 1) on conflict(gacha_id) do update set reset_count = reset_count + 1",
             {gacha});
}

}  // namespace

// BoxGacha(u32 gacha_id, u32 count) -> BoxGachaRes                      fid 5be25d4b
// API: docs/api.md#boxgacha   Rules: docs/server-rules.md#44-step-up-and-box-gacha, docs/server-rules.md#gacha-step-up-and-box
//
// Draws `count` copies from a box (b: CGacha::RequestGacha sends it; docs/api.md Callers).
//   (a) ticket_item_id x ticket_num per draw (event coins).
//   (d) count is capped by the copies left; an empty box is refused with kInvalidOperation (10403),
//       tickets short with kItemCountError (10206) (d: the codes).
//   (c) each draw takes a uniformly random remaining copy (without replacement).
//   (b)+(d) the series' last box refills once emptied (refill_last_box).
// Answers: the player state with BoxGachaItems, UpdateBoxGachaList (this series),
// UpdateBoxGacha (the slots of this box and of the next once it moved on), StockItem, and
// AddItem / AddCharacter when drawn. Not a box: not handled (no body).
std::vector<u8> box_gacha(ext::Ctx& ctx, const Request& req) {
    const auto args = args::BoxGachaArgs::from(req);
    u32 id = args.gacha_id, count = args.count;
    BoxTicket ticket = box_ticket(ctx, id);
    if (!ticket.is_box) return {};
    auto slots = box_slots(ctx, id);
    std::vector<u32> left;
    u32 total_left = 0;
    for (auto& slot : slots) {
        left.push_back(slot.left());
        total_left += left.back();
    }
    count = std::min(count, total_left);
    if (!count) return ext::refusef(ctx, req.method.c_str(), ErrorCode::kInvalidOperation, "box %u is empty", id);
    if (ticket.item && stock_count(ctx, ticket.item) < ticket.per_draw * count)
        return ext::refusef(ctx, req.method.c_str(), ErrorCode::kItemCountError, "box %u: tickets short (%u needed)", id, ticket.per_draw * count);
    if (ticket.item) ext::add_stock(ctx, ticket.item, -(int64_t)(ticket.per_draw * count));  // checked above: never below 0
    BoxDraws draws = draw_slots(ctx, id, slots, left, count);
    ctx.st.q(
        "insert into box_state (gacha_id, total_count) values (?, ?) on conflict(gacha_id) do update set total_count = total_count + excluded.total_count",
        {id, count});
    refill_last_box(ctx, id);
    Value data = base_data(ctx);
    data["BoxGachaItems"] = draws.results;
    Value slots_info = box_gacha_info(ctx, id);  // this box's slots, and the next box's once it moved on
    data["UpdateBoxGachaList"] = box_gacha_list_info(ctx, id, &slots_info);
    data["UpdateBoxGacha"] = slots_info;
    if (!draws.items.arr.empty()) data["AddItem"] = draws.items;
    data["StockItem"] = stack_item_info_list(ctx);
    if (!draws.characters.arr.empty()) {
        Value add_character = Value::object();
        for (auto& character : draws.characters.arr) add_character[std::to_string(character.get_u("id"))] = character;
        data["AddCharacter"] = add_character;
    }
    LOGI("server", "BoxGacha %u: %u draws, %u tickets, %u left", id, count, ticket.per_draw * count, total_left - count);
    return body(data);
}

// ResetBoxGacha(u32 gacha_id) -> ResetBoxGachaRes                        fid c292cf48
// API: docs/api.md#resetboxgacha   Rules: docs/server-rules.md#44-step-up-and-box-gacha
//
// Refills a box (b: CGacha::ProgressBoxDetail sends it; docs/api.md Callers).
//   (a) only a box with is_manual_reset (the last of a series) resets; (d) at any time, not only
//       when empty: its slots refill and reset_count counts up.
//   (d) another box is refused with kInvalidOperation (10403, d: the code).
// Answers: the player state with UpdateBoxGachaList (this series) and UpdateBoxGacha (its slots).
// Not a box: not handled (no body).
std::vector<u8> reset_box_gacha(ext::Ctx& ctx, const Request& req) {
    u32 id = args::GachaIdArgs::from(req).gacha_id;
    if (!ctx.m.one("select count(*) from master_gacha where id = ? and is_box = 1", {id})) return {};
    if (!ctx.m.one("select ifnull(is_manual_reset, 0) from master_gacha where id = ?", {id}))
        return ext::refusef(ctx, req.method.c_str(), ErrorCode::kInvalidOperation, "box %u has no manual reset", id);
    ctx.st.q("delete from box_slots where gacha_id = ?", {id});
    ctx.st.q("insert into box_state (gacha_id, reset_count) values (?, 1) on conflict(gacha_id) do update set reset_count = reset_count + 1", {id});
    Value data = base_data(ctx);
    Value slots = box_gacha_info(ctx, id);
    data["UpdateBoxGachaList"] = box_gacha_list_info(ctx, id, &slots);
    data["UpdateBoxGacha"] = slots;
    LOGI("server", "ResetBoxGacha %u", id);
    return body(data);
}

// GetBoxGacha() -> GetBoxGachaRes                                        fid af250236
// API: docs/api.md#getboxgacha   Rules: docs/server-rules.md#gacha-step-up-and-box
//
// The box series and their current boxes (b: code near CGachaRatio sends it; docs/api.md Callers).
//   (b) BoxGachaList and BoxGacha are maps keyed by id ("Step-up and box gacha lists").
// Answers: the player state with BoxGachaList (every open series) and BoxGacha (the slots of
// each series' current box).
std::vector<u8> get_box_gacha(ext::Ctx& ctx, const Request&) {
    Value data = base_data(ctx);
    Value boxes = Value::object();
    Value list = box_gacha_list_info(ctx, 0, &boxes);  // the current box of every open series and its slots
    data["BoxGachaList"] = list;
    data["BoxGacha"] = boxes;
    return body(data);
}

// The box gacha's APIs (src/core/modules.cpp: the core's APIs first).
void register_box_gacha() {
    ext::add_core_api({"BoxGacha"}, box_gacha);
    ext::add_core_api({"ResetBoxGacha"}, reset_box_gacha);
    ext::add_core_api({"GetBoxGacha"}, get_box_gacha);
}

}  // namespace soa::server
