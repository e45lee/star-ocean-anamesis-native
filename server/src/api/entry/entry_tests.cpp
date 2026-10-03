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

}  // namespace
}  // namespace soa::server
