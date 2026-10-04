// The present box: PresentList and GetPresent / GetPresentArray. Port code, not guest
// behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption (docs/server-rules.md "6. Presents").
#include "api/presents/presents.h"

#include <algorithm>

#include "api/player/player_info.h"  // base_data, player_id, stack_item_info_list
#include "core/log.h"
#include "core/request_args.h"
#include "core/rewards.h"  // grant
#include "soaserver/ext.h"

namespace soa::server {

using ext::body;
using ext::Row;

namespace {

// The line the box shows for a present: (b) the box shows free_text_message_id verbatim
// (present_texts.cpp); the row's stored `text`, else built from its reason.
std::string present_line(ext::Ctx& ctx, const Row& present_row) {
    ext::Sql master{ctx.m.h};
    return ext::present_text(master, present_row.s("text"), (u32)present_row.i("reason_type"), (u32)present_row.i("reason_param"));
}

// (b) CPresentbox::CreateAllPresentList lists only presents whose deadline_at isn't past
// (an empty one parses as 0: hidden); (a) master_global present_deadline_day (30) after
// the present was created.
std::string present_deadline(ext::Ctx& ctx, int64_t created_at) {
    return format_time(created_at + (int64_t)ctx.global_u32("present_deadline_day", 30) * 86400);
}

Value present_box_info(ext::Ctx& ctx, const Row& present_row, PlayerId player) {
    Value info = Value::object();
    info["id"] = (u64)present_row.i("id");
    info["player_id"] = player.v;
    info["content_type"] = (u32)present_row.i("content_type");
    info["content_id"] = (u32)present_row.i("content_id");
    info["num"] = (u32)present_row.i("num");
    info["reason_type"] = (u32)present_row.i("reason_type");
    info["reason_param"] = (u32)present_row.i("reason_param");
    info["is_receive"] = 0u;
    info["free_text_message_id"] = present_line(ctx, present_row);
    info["deadline_at"] = present_deadline(ctx, present_row.i("created_at"));
    return info;
}

// The unreceived presents, oldest first: PresentList's PresentBox and GetPresent's "add".
Value present_box(ext::Ctx& ctx) {
    Value box = Value::array();
    const PlayerId player = player_id(ctx);
    ctx.st.q("select * from presents where received_at is null order by id", {},
             [&](const Row& present_row) { box.push(present_box_info(ctx, present_row, player)); });
    return box;
}

// What receiving presents added, as grant() lists it: AddItem, StockItem, AddCharacter.
struct Received {
    Value items = Value::array(), stocks = Value::array(), characters = Value::array();
};

// Marks one unreceived present received and grants its content as a drop is (into `added`).
// False when there is no such present.
bool receive_present(ext::Ctx& ctx, u64 present_id, Received& added) {
    bool open = false;
    Drop content{};
    ctx.st.q("select * from presents where id = ? and received_at is null", {present_id}, [&](const Row& present_row) {
        open = true;
        content = Drop{(u32)present_row.i("content_type"), (u32)present_row.i("content_id"), (u32)std::max<int64_t>(1, present_row.i("num")), 0};
    });
    if (!open) return false;
    grant(ctx, content, added.items, added.stocks, added.characters);
    ctx.st.q("update presents set received_at = ? where id = ?", {clock_now(), present_id});
    return true;
}

}  // namespace

Value present_box_info(ext::Ctx& ctx, const Row& present_row) { return present_box_info(ctx, present_row, ctx.player_id()); }

// PresentList() -> PresentListRes                                       fid fa782a45
// API: docs/api.md#presentlist   Rules: docs/server-rules.md#6-presents, docs/server-rules.md#presents-presentlist
//
// The present box (CPresentbox::Initialize sends it when the box opens).
//   (b) PresentBox is a list of CPresentBoxInfo; each line is the finished text
//       (free_text_message_id, present_texts.cpp) and a deadline_at the box doesn't hide.
// Answers: the player state with PresentBox (the unreceived presents, oldest first).
std::vector<u8> present_list(ext::Ctx& ctx, const Request&) {
    Value box = present_box(ctx);
    Value data = base_data(ctx);
    data["PresentBox"] = box;
    return body(data);
}

// GetPresentArray(vector<u64> present_ids) / GetPresent(u64 present_id, ...) -> GetPresentRes
//                                                                        fid 4072d7e1
// API: docs/api.md#getpresentarray   Rules: docs/server-rules.md#6-presents, docs/server-rules.md#presents-presentlist
//
// Receives the presents: each unreceived one's content is granted as drops are
// (core/rewards.cpp grant) and the present marked received; ids already received or unknown are
// skipped.
//   (d) GetPresent reads only its first id (its varargs aren't captured).
//   (b) CApiNotify::ApplyGetPresent refills the box from PresentGetResult.add, so "add" is the
//       whole box left.
// Answers: the player state with PresentGetResult {get: the ids received, add: the box left,
// result: {fol, free_coin} gained}, plus AddItem / StockItem / AddCharacter when they changed.
std::vector<u8> get_present(ext::Ctx& ctx, const Request& req) {
    const auto args = args::GetPresentArgs::from(req);
    u32 fol_before = (u32)ctx.st.one("select fol from player", {}), coins_before = (u32)ctx.st.one("select free_coin from player", {});
    Received added;
    Value received = Value::array();
    for (u64 present_id : args.present_ids)
        if (receive_present(ctx, present_id, added)) received.push(present_id);
    Value box = present_box(ctx);
    Value gained = Value::object();
    gained["fol"] = (u32)ctx.st.one("select fol from player", {}) - fol_before;
    gained["free_coin"] = (u32)ctx.st.one("select free_coin from player", {}) - coins_before;
    Value result = Value::object();
    result["get"] = received;
    result["add"] = box;
    result["result"] = gained;
    Value data = base_data(ctx);
    data["PresentGetResult"] = result;
    if (!added.items.arr.empty()) data["AddItem"] = added.items;
    if (!added.stocks.arr.empty()) data["StockItem"] = stack_item_info_list(ctx);
    Value add_character = Value::object();
    for (auto& character : added.characters.arr) add_character[std::to_string(character.get_u("id"))] = character;
    if (!added.characters.arr.empty()) data["AddCharacter"] = add_character;
    LOGI("server", "GetPresent: %zu received, %zu left", received.arr.size(), box.arr.size());
    return body(data);
}

// The present box's APIs (src/core/modules.cpp: the core's APIs first).
void register_presents() {
    ext::add_core_api({"PresentList"}, present_list);
    ext::add_core_api({"GetPresent", "GetPresentArray"}, get_present);
}

}  // namespace soa::server
