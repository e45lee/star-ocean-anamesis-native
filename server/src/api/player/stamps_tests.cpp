// Tests of the chat stamps (api/player/stamps.cpp; docs/server-rules.md#stamps).
#include <string>
#include <vector>

#include <algorithm>

#include "soaserver/ext.h"
#include "soaserver/msgpack.h"
#include "soaserver/native_test.h"
#include "testing/module_test.h"

namespace soa::server {
namespace {

std::vector<u32> u32s(const Value* list) {
    std::vector<u32> out;
    if (list && list->type == Value::Arr)
        for (const Value& v : list->arr) out.push_back((u32)v.u);
    return out;
}

Value load(ext::Ctx& ctx) { return module_test::player_load_data(ctx, "Login"); }

// SetStampSlot(stamps): its answer's data (Nil without one) and the refusal code (0: none).
struct Answer {
    Value data;
    u32 code = 0;
};
Answer set_slots(ext::Ctx& ctx, std::vector<u64> stamps) {
    Answer a;
    ctx.test.on_refuse = [&](u32 code) { a.code = code; };
    std::vector<u8> b = module_test::call(ctx, "SetStampSlot", {}, {std::move(stamps)});
    ctx.test.on_refuse = nullptr;
    const Value all = b.empty() ? Value() : mp_decode(b);  // kept: find() points into it
    if (const Value* d = all.find("data")) a.data = *d;
    return a;
}

// The player load: (a)+(d) the type-1 stamps owned, (a)+(b) a palette of stamp_page_max * 4 slots,
// (d) the default one: the type-1 stamps in order_id order, the rest empty.
NATIVE_TEST("player/stamps-load") {
    bool ran = ext::with_scratch_server(t.rand_u64(), [&](ext::Ctx& ctx) {
        ctx.st.exec("begin");
        Value data = load(ctx);
        std::vector<u32> list = u32s(data.find("StampList")), slots = u32s(data.find("StampSlot"));
        t.expect_eq((int64_t)list.size(), ctx.m.one("select count(*) from master_stamp where type = 1", {}), "the type-1 stamps are owned");
        const int64_t pages = ctx.m.one("select cast(value as integer) from master_global where key = 'stamp_page_max'", {});
        t.expect_eq((int64_t)slots.size(), pages * 4, "stamp_page_max pages of four slots");
        std::vector<u32> want;
        ctx.m.q("select id from master_stamp where type = 1 order by order_id, id", {}, [&](const ext::Row& r) { want.push_back((u32)r.i("id")); });
        want.resize(slots.size(), 0);
        t.expect_eq(slots, want, "the default palette: the type-1 stamps by order_id, then empty slots");
        ctx.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master (data/basmaster-3.7.0.sqlite3) and the test seed");
}

// SetStampSlot: (d) stored slot by slot and answered (StampSlot), kept for the next load; an unowned
// stamp or too many entries refused (10208) without a change; fewer entries pad with empty slots.
NATIVE_TEST("player/stamps-set-slot") {
    bool ran = ext::with_scratch_server(t.rand_u64(), [&](ext::Ctx& ctx) {
        ctx.st.exec("begin");
        if (!ext::find("SetStampSlot")) return t.fail("no SetStampSlot handler");
        Value data = load(ctx);
        std::vector<u32> owned = u32s(data.find("StampList"));
        const size_t n = u32s(data.find("StampSlot")).size();
        if (owned.size() < 3 || n < 4) return t.fail("too few default stamps or slots");
        std::vector<u64> sent(n, 0);
        sent[0] = owned[2];
        sent[1] = owned[0];
        sent[n - 1] = owned[1];
        Answer r = set_slots(ctx, sent);
        t.expect_eq(r.code, 0u, "accepted");
        std::vector<u32> want(sent.begin(), sent.end());
        t.expect_eq(u32s(r.data.find("StampSlot")), want, "answered as sent");
        t.expect_eq(u32s(load(ctx).find("StampSlot")), want, "the next load sends it");
        t.expect_eq(ctx.st.one("select count(*) from stamp_slots where stamp_id is null", {}), (int64_t)(n - 3), "empty slots are NULL");

        // an unowned (type-2) stamp: refused, the palette unchanged
        const u32 unowned = (u32)ctx.m.one("select id from master_stamp where type = 2 order by id limit 1", {});
        t.expect_eq(set_slots(ctx, {unowned}).code, 10208u, "an unowned stamp refused");
        t.expect_eq(u32s(load(ctx).find("StampSlot")), want, "unchanged after the refusal");
        t.expect_eq(set_slots(ctx, std::vector<u64>(n + 1, 0)).code, 10208u, "more entries than slots refused");

        // fewer entries: the rest empty; all empty stays empty (not the default palette again)
        t.expect_eq(set_slots(ctx, {owned[1]}).code, 0u, "a short palette accepted");
        std::vector<u32> short_want(n, 0);
        short_want[0] = owned[1];
        t.expect_eq(u32s(load(ctx).find("StampSlot")), short_want, "padded with empty slots");
        t.expect_eq(set_slots(ctx, {}).code, 0u, "an empty palette accepted");
        t.expect_eq(u32s(load(ctx).find("StampSlot")), std::vector<u32>(n, 0), "every slot empty");
        ctx.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master (data/basmaster-3.7.0.sqlite3) and the test seed");
}

// Grant (content type 12): (a) a master_stamp id joins StampList once; the response reports
// StampList, AddStampList and PresentGetResult.result.Stamp; then it can go in the palette.
NATIVE_TEST("player/stamps-grant") {
    bool ran = ext::with_scratch_server(t.rand_u64(), [&](ext::Ctx& ctx) {
        ctx.st.exec("begin");
        load(ctx);
        const ext::GrantFn* grant = ext::find_grant(12);
        if (!grant) return t.fail("content type 12 has no grant");
        const u32 reward = (u32)ctx.m.one("select content_id from master_achievement where content_type = 12 order by id limit 1", {});
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        (*grant)(ctx, reward, 1, items, stocks, chars);
        (*grant)(ctx, reward, 1, items, stocks, chars);  // twice: owned once
        (*grant)(ctx, 12345, 1, items, stocks, chars);   // not a master_stamp id: skipped
        t.expect_eq(ctx.st.one("select count(*) from stamps where id = ?", {reward}), (int64_t)1, "stamp owned");
        t.expect_eq(ctx.st.one("select count(*) from stamps where id = 12345", {}), (int64_t)0, "an unknown id skipped");
        Request present_req;
        present_req.method = "GetPresent";
        Value present_data = Value::object();
        present_data["PresentGetResult"] = Value::object();
        ext::on_response(ctx, present_req, present_data);
        t.expect_eq(u32s(present_data.find("AddStampList")), std::vector<u32>{reward}, "AddStampList once");
        std::vector<u32> list = u32s(present_data.find("StampList"));
        t.expect_eq(std::find(list.begin(), list.end(), reward) != list.end(), true, "StampList has it");
        const Value* result = present_data.find("PresentGetResult")->find("result");
        const Value* stamps = result ? result->find("Stamp") : nullptr;
        t.expect_eq(stamps && stamps->arr.size() == 1 ? (u32)stamps->arr[0].get_u("master_stamp_id") : 0u, reward, "result.Stamp");
        present_data = Value::object();
        ext::on_response(ctx, present_req, present_data);
        t.expect_eq(present_data.find("AddStampList") != nullptr, false, "no AddStampList without a grant");

        Answer r = set_slots(ctx, {reward});
        t.expect_eq(r.code, 0u, "the granted stamp accepted in the palette");
        std::vector<u32> got = u32s(r.data.find("StampSlot"));
        t.expect_eq(got.empty() ? 0u : got[0], reward, "the granted stamp goes in the palette");
        ctx.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master (data/basmaster-3.7.0.sqlite3) and the test seed");
}

}  // namespace
}  // namespace soa::server
