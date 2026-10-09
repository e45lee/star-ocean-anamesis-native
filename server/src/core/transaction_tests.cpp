// Unit tests of the request transaction (core/server.cpp handle_request, Server::transact): a
// request whose statement fails, or whose state can't be read, is rolled back as a whole and
// refused; it never commits half its writes or answers success (docs/code-review-2026-10-06.md S1,
// S6). Run in --selftest; not differential (the server has no guest counterpart). The failures
// are forced with TEMP triggers on the scratch state's connection (invisible to the schema).
#include <string>
#include <vector>

#include "core/errors.h"
#include "soaserver/native_test.h"
#include "soaserver/fids.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

// A trigger that makes every `event` (e.g. "update on mission") on the scratch state fail.
void fail_on(ScratchServer& s, const char* name, const char* event) {
    s.sv.st.exec(std::string("create temp trigger ") + name + " before " + event + " begin select raise(abort, 'forced by the test'); end");
}

// MissionTalk inserts its mission row, then updates it: the update fails. Nothing of the request
// stays (the insert is rolled back too) and the client gets an error, not a success.
NATIVE_TEST("server/sql-failure-refuses-the-request") {
    ScratchServer s(t.rand_u64());
    if (!s.ok) return;
    u32 mission = s.id("master_mission", "mc01_030");
    if (!mission) return t.fail("no mc01_030 in the master");
    fail_on(s, "cr2_mission_update", "update on mission");
    std::vector<u8> out;
    u32 code = s.call(Request{"MissionTalk", fids::kMissionTalk, {0, mission, 0, 0}, {}, {}}, &out);
    t.expect_eq(code, (u32)ErrorCode::kItemUnusable, "refused with the generic 10208");
    t.expect_eq(s.sv.st.one("select count(*) from mission where mission_id = ?", {mission}), (int64_t)0, "the insert before it rolled back");
    t.expect_eq(out.empty(), false, "answered (the player state)");
    // The next request starts clean: the failure didn't leave a transaction open.
    s.sv.st.exec("drop trigger cr2_mission_update");
    t.expect_eq(s.call(Request{"MissionTalk", fids::kMissionTalk, {0, mission, 0, 0}, {}, {}}), 0u, "accepted once the statement works");
    t.expect_eq(s.sv.st.one("select cleared from mission where mission_id = ?", {mission}), (int64_t)1, "and committed");
}

// Server::transact (ext::with_live_server's transaction): a failed statement rolls back the rest
// and reports false; a good one commits.
NATIVE_TEST("server/transact-rolls-back") {
    ScratchServer s(t.rand_u64());
    if (!s.ok) return;
    fail_on(s, "cr2_last_insert", "insert on campaign_last");
    bool ok = s.sv.transact([](ext::Ctx& ctx) {
        ctx.st.q("insert into meta (key, value) values ('cr2_a', '1')", {});
        ctx.st.q("insert into campaign_last (id, mission_id) values (1, 0)", {});
    });
    t.expect_eq(ok, false, "a failed statement: false");
    t.expect_eq(s.sv.st.one("select count(*) from meta where key = 'cr2_a'", {}), (int64_t)0, "its earlier write rolled back");
    t.expect_eq(s.sv.st.exec("begin"), true, "no transaction left open");
    s.sv.st.exec("rollback");
    ok = s.sv.transact([](ext::Ctx& ctx) { ctx.st.q("insert into meta (key, value) values ('cr2_b', '1')", {}); });
    t.expect_eq(ok, true, "a good one: true");
    t.expect_eq(s.sv.st.one("select count(*) from meta where key = 'cr2_b'", {}), (int64_t)1, "and committed");
}

// A corrupt uid counter (meta next_item_uid not a number): the draw that needs a uid is refused,
// nothing is taken, and the server keeps running (std::stoull threw and nothing caught it).
NATIVE_TEST("server/corrupt-uid-counter-refuses") {
    ScratchServer s(t.rand_u64());
    if (!s.ok) return;
    s.set_clock("2026-10-01 12:00:00");
    u32 gacha = s.id("master_gacha", "gacha_weapon_0009");
    if (!gacha) return t.fail("no gacha_weapon_0009 in the master");
    s.sv.st.q("update player set free_coin = 100000", {});
    s.sv.st.q("update meta set value = 'not a number' where key = 'next_item_uid'", {});
    const int64_t items = s.sv.st.one("select count(*) from items", {});
    u32 code = s.call(Request{"Gacha", fids::kGacha, {gacha, 0}, {}, {}});
    t.expect_eq(code, (u32)ErrorCode::kItemUnusable, "refused with the generic 10208");
    t.expect_eq((u32)s.sv.st.one("select free_coin from player", {}), 100000u, "no coins taken");
    t.expect_eq(s.sv.st.one("select count(*) from items", {}), items, "no item added");
}

}  // namespace
}  // namespace soa::server
