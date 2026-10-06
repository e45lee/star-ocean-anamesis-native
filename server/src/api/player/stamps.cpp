// Chat stamps (スタンプ; api/player/README.md): the stamps the player owns and the スタンプ編成
// palette. Port code, not guest behaviour; every rule carries its source label, (a) master data,
// (b) client-side evidence, (c) outside knowledge, (d) assumption. Rules in
// docs/server-rules.md#stamps.
//
// What the client reads (b):
//  - `StampList`: the owned stamps. CStampList is an InfoBaseValueArray<u32> (its vtable's
//    DeserializeArray), a plain array of master_stamp ids, kept in CParameterManager+0x70b0.
//    CStampSelect::Setup (@01e63150) lists exactly those ids
//    (CMasterParameterStamp::ParameterList @01e64414: "SELECT * FROM master_stamp WHERE id IN
//    (...)"); the client adds no default stamps itself.
//  - `StampSlot`: the palette. CStampSlotInfo is an InfoBaseValueArray<u32> too
//    (CParameterManager+0x7138); CStampSelect::Setup copies it into the screen's slots, four per
//    page ("Node_2/plate%d/chara3/stamp_1..4"; CStampSelect::UpdateSelectStamp @01e65010 reads
//    slot page * 4 + i, and 0 is the empty tile stp_th_stp0; IsSelectStamp @01e6560c walks it
//    in fours). The page count is master_global stamp_page_max (CStampSelect::Initialize
//    @01e62e20; 3 when the key is missing). A palette shorter than the pages is read past its end.
//  - `SetStampSlot(vector<u32>)` (CStampSelect::StampUpdate @01e658a4, fid 58123949): sent when
//    the palette differs from the one the screen opened with; the request lambda (@01e69270)
//    sends the screen's whole palette (+0x330). The answer goes through
//    CApiNotify::OnSetStampSlotRes (DeserializeToInfo: the keys above replace the client's lists).
// How stamps were earned (a): master_stamp has 12 type-1 rows (order_id 1..12; master_global
// stamp_kind is 12) and 278 type-2 rows. 271 of the type-2 stamps are rewards (content type 12:
// master_achievement, master_login_bonus_contents, master_exchange_shop_contents); no type-1 stamp
// is a reward anywhere, and 7 type-2 ones are no master row's reward.
//
// State: the tables `stamps` (the owned ids) and `stamp_slots` (the palette; schema version 19).
#include <optional>
#include <string>
#include <vector>

#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "core/request_context.h"
#include "soaserver/ext.h"

namespace soa::server {

namespace args {
// SetStampSlot(vector<u32> stamps): the palette, slot by slot (page * 4 + position), 0 for an
// empty slot (b: CStampSelect::StampUpdate's request lambda @01e69270). The module's own args struct.
struct SetStampSlotArgs {
    std::vector<u64> stamps;
    static SetStampSlotArgs from(const Request& r) { return {r.vecs.empty() ? std::vector<u64>() : r.vecs[0]}; }
};
}  // namespace args

namespace {

using ext::Row;

// (a) docs/api.md "Content types": content type 12 is a master_stamp id (master_achievement,
// master_login_bonus_contents, master_exchange_shop_contents).
constexpr u32 kContentTypeStamp = 12;
// (b) four stamps per palette page (CStampSelect::Setup / UpdateSelectStamp @01e65010).
constexpr u32 kSlotsPerPage = 4;

bool is_stamp(ext::Ctx& ctx, StampId stamp) { return stamp.v && ctx.m.one("select count(*) from master_stamp where id = ?", {stamp}) > 0; }

bool owns_stamp(ext::Ctx& ctx, StampId stamp) { return ctx.st.one("select count(*) from stamps where id = ?", {stamp}) > 0; }

// The palette's size: (a) master_global stamp_page_max pages (4 in 3.7.0) of (b) four slots;
// (b) 3 pages without the key, as CStampSelect::Initialize.
u32 slot_count(ext::Ctx& ctx) {
    const double pages = ext::global_f(ctx, "stamp_page_max", 3);
    return (pages > 0 ? (u32)pages : 0) * kSlotsPerPage;
}

// (a)+(d) The type-1 stamps are every player's: no master row awards one (above), so the server
// lists them as owned (the client lists only StampList ids; without them a new player has none).
void ensure_default_stamps(ext::Ctx& ctx) {
    ctx.m.q("select id from master_stamp where type = 1", {},
            [&](const Row& stamp_row) { ctx.st.q("insert or ignore into stamps (id, got_at) values (?, null)", {stamp_row.i("id")}); });
}

// StampList: the owned master_stamp ids, the default ones included.
Value stamp_list(ext::Ctx& ctx) {
    ensure_default_stamps(ctx);
    Value list = Value::array();
    ctx.st.q("select id from stamps order by id", {}, [&](const Row& stamp_row) { list.push((u32)stamp_row.i("id")); });
    return list;
}

// The palette, slot_count() entries, 0 for an empty slot. A player who never set it (no
// stamp_slots row): (d) the default stamps in master_stamp order_id order from the first slot,
// the rest empty (3.7.0's first palette isn't known; an empty one would leave the multiplayer
// chat's stamp buttons blank until the player arranges them).
std::vector<u32> palette(ext::Ctx& ctx) {
    std::vector<u32> slots(slot_count(ctx), 0);
    if (ctx.st.one("select count(*) from stamp_slots", {}) == 0) {
        ensure_default_stamps(ctx);
        size_t k = 0;
        ctx.m.q("select id from master_stamp where type = 1 order by order_id, id", {}, [&](const Row& stamp_row) {
            if (k < slots.size()) slots[k++] = (u32)stamp_row.i("id");
        });
        return slots;
    }
    // (d) a slot past the palette's size (a smaller stamp_page_max than when it was set) is dropped
    ctx.st.q("select slot, stamp_id from stamp_slots where stamp_id is not null order by slot", {}, [&](const Row& slot_row) {
        const int64_t slot = slot_row.i("slot");
        if (slot >= 0 && (size_t)slot < slots.size()) slots[(size_t)slot] = (u32)slot_row.i("stamp_id");
    });
    return slots;
}

Value stamp_slot_info(ext::Ctx& ctx) {
    Value list = Value::array();
    for (u32 stamp : palette(ctx)) list.push(stamp);
    return list;
}

// Grant (content type 12): a stamp                        from the present box, an exchange shop
// Rules: docs/server-rules.md#stamps (Grant)
//
//   (a) Content type 12 is a master_stamp id (docs/api.md "Content types"); an id not in
//       master_stamp is logged and skipped.
//   (d) The stamp joins the owned list; a stamp owned already changes nothing.
// Adds: the id to the request's stamps_added, which report_added_stamps answers.
void grant_stamp(ext::Ctx& ctx, u32 content_id, u32, Value&, Value&, Value&) {
    const StampId stamp(content_id);
    if (!is_stamp(ctx, stamp)) {
        LOGW("server", "stamp %u: not in master_stamp", stamp.v);
        return;
    }
    ensure_default_stamps(ctx);
    if (owns_stamp(ctx, stamp)) return;
    ctx.st.q("insert into stamps (id, got_at) values (?, ?)", {stamp, ctx.now()});
    ctx.request->stamps_added.push_back(stamp);  // for AddStampList / PresentGetResult.result.Stamp (OnResponse)
    LOGI("server", "stamp %u granted", stamp.v);
}

// OnPlayerLoad: StampList, StampSlot                      on Login, SimpleLogin, CreatePlayer, GetPlayer, NoLoginStart
// Rules: docs/server-rules.md#stamps
//
//   (b) StampList and StampSlot are what CStampSelect (キャラクター > スタンプ編成) reads (above).
//   (d) Nothing without a player (the new-player flow's NoLoginStart).
// Adds: data.StampList (the owned stamps, the defaults included) and data.StampSlot (the palette).
void load_stamps(ext::Ctx& ctx, const Request&, Value& data) {
    if (!ctx.st.one("select count(*) from player", {})) return;  // no player yet (new-player flow)
    data["StampList"] = stamp_list(ctx);
    data["StampSlot"] = stamp_slot_info(ctx);
}

// SetStampSlot(vector<u32> stamps) -> SetStampSlotRes                           fid 58123949
// API: docs/api.md#setstampslot
// Rules: docs/server-rules.md#stamps
//
// Stores the スタンプ編成 palette (the multiplayer chat's stamps).
//   (b) CStampSelect::StampUpdate sends the screen's whole palette, slot page * 4 + position, 0 for
//       an empty slot; the answer's StampSlot replaces the client's (CStampSlotInfo).
//   (d) A stamp the player doesn't own, or more entries than the palette has, is refused with
//       kItemUnusable (10208, the generic refusal); fewer entries leave the remaining slots empty.
//   (d) Otherwise stored as sent, slot by slot (stamp_slots; NULL for an empty slot).
// Answers: the player state with StampSlot and StampList.
std::vector<u8> set_stamp_slot(ext::Ctx& ctx, const Request& req) {
    const auto args = args::SetStampSlotArgs::from(req);
    ensure_default_stamps(ctx);
    const u32 slots = slot_count(ctx);
    if (args.stamps.size() > slots) return ext::refuse(ctx, req.method.c_str(), "more stamps than the palette's slots", ErrorCode::kItemUnusable);
    for (u64 stamp : args.stamps)
        if (stamp && (stamp > 0xffffffffull || !owns_stamp(ctx, StampId((u32)stamp))))
            return ext::refuse(ctx, req.method.c_str(), "stamp not owned", ErrorCode::kItemUnusable);
    ctx.st.q("delete from stamp_slots", {});
    for (u32 slot = 0; slot < slots; slot++) {
        const u64 stamp = slot < args.stamps.size() ? args.stamps[slot] : 0;
        ctx.st.q("insert into stamp_slots (slot, stamp_id) values (?, ?)",
                 {(int64_t)slot, stamp ? std::optional<StampId>(StampId((u32)stamp)) : std::nullopt});
    }
    Value data = ctx.base_data();
    data["StampSlot"] = stamp_slot_info(ctx);
    data["StampList"] = stamp_list(ctx);
    std::string shown;
    for (u64 stamp : args.stamps) shown += (shown.empty() ? "" : ",") + std::to_string(stamp);
    LOGI("server", "SetStampSlot: %zu slots [%s]", args.stamps.size(), shown.c_str());  // read by the stamps session
    return ext::body(data);
}

// OnResponse: the stamps this request granted             on every answered response
// Rules: docs/server-rules.md#stamps (Grant)
//
//   (b) The keys (port/fakeapi/schema.txt; CAddStampList, an InfoBaseValueArray<u32>;
//       CPresentBoxReceiveStampInfo): a response that granted stamps carries the new list
//       StampList (state), AddStampList (the per-response result) and, for a present receive,
//       PresentGetResult.result.Stamp ({master_stamp_id}).
// Adds: those keys when grant_stamp added a stamp during the request; nothing otherwise.
bool report_added_stamps(ext::Ctx& ctx, const Request&, Value& data) {
    std::vector<StampId> added;
    added.swap(ctx.request->stamps_added);
    if (added.empty()) return false;
    data["StampList"] = stamp_list(ctx);
    Value added_list = Value::array();
    for (StampId stamp : added) added_list.push(stamp.v);
    data["AddStampList"] = added_list;
    if (Value* present_result = data.find_mut("PresentGetResult"); present_result && present_result->type == Value::Map) {
        Value& result = (*present_result)["result"];
        if (result.type != Value::Map) result = Value::object();
        Value stamps = Value::array();
        for (StampId stamp : added) {
            Value entry = Value::object();
            entry["master_stamp_id"] = stamp.v;
            stamps.push(entry);
        }
        result["Stamp"] = stamps;
    }
    return true;
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_stamp() {
    ext::add_grant(kContentTypeStamp, grant_stamp);
    ext::add_player_load(load_stamps);
    ext::add_api({"SetStampSlot"}, set_stamp_slot);
    ext::add_response_hook(report_added_stamps);
}

}  // namespace soa::server
