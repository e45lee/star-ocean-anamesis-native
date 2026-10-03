// Unit tests of the entry flow (api/entry/entry.h). Run in --selftest; not differential (the server has no
// guest counterpart). Test names are their seeds (testing.h); they are named entry/... after their domain.
#include <unistd.h>

#include <set>
#include <string>
#include <vector>

#include "api/entry/entry.h"
#include "soaserver/config.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

using ext::Row;

// --start-coins: a seeded player and a created one start with that many free coins (300,000
// by default, the user's request).
NATIVE_TEST("entry/start-coins") {
    ServerConfig& opt = config();
    ServerConfig saved = opt;
    t.expect_eq(ServerConfig().start_coins, 300000u, "default 300,000");
    opt.start_coins = 300000;
    {
        ScratchServer S(t.rand_u64());
        if (!S.ok) return;
        t.expect_eq((u32)S.sv.st.one("select free_coin from player", {}), 300000u, "seeded player");
    }
    opt.start_coins = 4321;
    {
        ScratchServer S(t.rand_u64() ^ 1);
        if (!S.ok) return;
        Server& sv = S.sv;
        RequestContext request = sv.new_request();  // for the handlers called directly
        ext::Ctx ctx = sv.make_ctx(request);
        t.expect_eq((u32)sv.st.one("select free_coin from player", {}), 4321u, "seeded player, --start-coins 4321");
        sv.st.exec("delete from player");
        create_player(ctx, Request{"CreatePlayer", 0, {}, {"Tester", "uuid-test"}, {}});
        t.expect_eq((u32)sv.st.one("select count(*) from player", {}), 1u, "created");
        t.expect_eq((u32)sv.st.one("select free_coin from player", {}), 4321u, "created player, --start-coins 4321");
    }
    opt.start_coins = saved.start_coins;
}

// CreatePlayer in its request's transaction (PLAN-schema S4): the player row before the starters
// (home_uid deferred, NULL until they exist), the party sets 1..party_set_max (player.party_id's
// parents), the starters as the home character and party 1: the commit's deferred foreign keys
// hold, and nothing dangles.
NATIVE_TEST("entry/create-player-references") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    sv.st.exec("delete from player; delete from party_set; delete from party; delete from titles");
    t.expect_eq(S.call(Request{"CreatePlayer", 0xe3e463ad, {}, {"Tester", "uuid-test"}, {}}), 0u, "CreatePlayer");
    t.expect_eq((u32)sv.st.one("select count(*) from player", {}), 1u, "created (the transaction committed)");
    t.expect_eq((u32)sv.st.one("select count(*) from party_set", {}), 10u, "the party sets 1..party_set_max (10)");
    t.expect_eq((u32)sv.st.one("select count(*) from player p join roster r on r.uid = p.home_uid", {}), 1u, "the home character");
    t.expect_eq((u32)sv.st.one("select count(*) from player p join titles x on x.id = p.title_id", {}), 1u, "the worn title is owned");
    int fk_rows = 0;
    sv.st.q("pragma foreign_key_check", {}, [&](const Row&) { fk_rows++; });
    t.expect_eq(fk_rows, 0, "foreign_key_check");
}

}  // namespace
}  // namespace soa::server
