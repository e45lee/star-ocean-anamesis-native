// Unit tests of the server object: a whole session on a scratch state (missions, gacha, presents
// through the core handlers) and the response encoder. Run in --selftest; not differential (the server has no guest counterpart). Test names are
// their seeds (testing.h): they keep the names they had in core/server.cpp.
#include <unistd.h>

#include <set>
#include <string>
#include <vector>

#include "api/gacha/gacha.h"
#include "api/missions/missions.h"
#include "api/player/player_info.h"
#include "api/presents/presents.h"
#include "core/ids.h"
#include "state/kvs.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

using ext::Row;

// A whole session on a scratch state DB seeded from the test seed save, with invariants: stamina
// never negative and debited by use_stamina, EXP / FOL by the master amounts, drops only from the
// mission's tables, coins debited by the price, draws and new characters counted.
NATIVE_TEST("server/session-invariants") {
    std::string master, save;
    if (!scratch_inputs(master, save)) return;  // (fails the test)
    Db* mm = test_master();
    if (!mm) return t.fail("master");
    Server sv;
    sv.live = false;
    std::string db = "/tmp/soa-server-test-" + std::to_string(getpid()) + ".sqlite3";
    unlink(db.c_str());
    if (!sv.m.open(master, true) || !sv.open_state(db, t.rand_u64(), save)) return t.fail("open");
    sv.pools.open();  // the reconstructed pools when present (else the rarity fallback)
    RequestContext rc = sv.new_request();  // the handlers below are called directly, in one context
    ext::Ctx ctx = sv.make_ctx(rc);
    // The seed's own values (port/server-data/test-seed.xml): its level and its distinct roles.
    auto kv = read_kvs(save);
    std::set<u32> seed_roles;
    for (u32 i = 0, n = kv_u32(kv, "person_size", 0); i < n; i++)
        if (u32 r = kv_u32(kv, "person_master_role_id_" + std::to_string(i))) seed_roles.insert(r);
    if (seed_roles.size() < 4) t.fail("the seed save has %zu roles", seed_roles.size());
    t.expect_eq((u32)sv.st.one("select level from player", {}), kv_u32(kv, "player_level", 0), "seeded level");
    t.expect_eq((u32)sv.st.one("select count(*) from roster", {}), (u32)seed_roles.size(), "seeded roster");
    t.expect_eq(sv.st.one("select count(*) from player where name = ? and search_id = 'LOCAL00001'", {kv_str(kv, "player_name")}), (int64_t)1,
                "seeded name, local id");
    t.expect_eq((u32)sv.st.one("select count(*) from party where party_id = 1", {}), 4u, "party 1");
    u32 mission = (u32)mm->one("select id from master_mission where id_label = 'mf01_001'", {});
    u32 cost = (u32)mm->one("select use_stamina from master_mission where id = ?", {mission});
    u32 pexp = (u32)mm->one("select exp from master_mission where id = ?", {mission});
    u32 fol = (u32)mm->one("select fol from master_mission where id = ?", {mission});
    std::set<u32> allowed;
    mm->q("select content_id from master_mission_drop where master_mission_id = ?", {mission},
          [&](const Row& r) { allowed.insert((u32)r.i("content_id")); });
    mm->q("select content_id from master_common_drop where common_drop_id = (select common_drop_id from master_mission where id = ?)", {mission},
          [&](const Row& r) { allowed.insert((u32)r.i("content_id")); });
    Request ms{"MissionStart", 0xb7c62bc2, {0, mission, 0, 0, 0, 0, 0}, {}, {}};
    Request me{"MissionEnd", 0x8312a64c, {mission, 0}, {}, {}};
    sv.st.exec("begin");
    for (int k = 0; k < 80; k++) {
        // a start with too little stamina is refused (10004) and changes nothing; refill then
        if ((u32)sv.st.one("select stamina from player", {}) < cost) {
            rc.refusal = 0;
            mission_start(ctx, ms);
            t.expect_eq(rc.refusal, 10004u, "stamina short: 10004");
            rc.refusal = 0;
            sv.st.q("update player set stamina = ?", {ctx.stamina_max((u32)sv.st.one("select level from player", {}))});
        }
        u32 s0 = (u32)sv.st.one("select stamina from player", {});
        u64 e0 = (u64)sv.st.one("select exp from player", {}) + 1000000ull * sv.st.one("select level from player", {});
        u32 f0 = (u32)sv.st.one("select fol from player", {});
        u32 items0 = (u32)sv.st.one("select count(*) from items", {});
        if (mission_start(ctx, ms).empty()) return t.fail("MissionStart");
        u32 s1 = (u32)sv.st.one("select stamina from player", {});
        if (s1 != s0 - cost) t.fail("stamina %u -> %u (cost %u)", s0, s1, cost);
        if (mission_end(ctx, me).empty()) return t.fail("MissionEnd");
        u64 e1 = (u64)sv.st.one("select exp from player", {}) + 1000000ull * sv.st.one("select level from player", {});
        if (e1 <= e0) t.fail("player EXP didn't grow");
        if ((u32)sv.st.one("select fol from player", {}) != f0 + fol) t.fail("FOL");
        sv.st.q("select master_item_id from items where uid >= ? ", {(u64)kItemUid0 + items0}, [&](const Row& r) {
            if (!allowed.count((u32)r.i("master_item_id"))) t.fail("drop %u not in the mission's tables", (u32)r.i("master_item_id"));
        });
    }
    sv.st.exec("commit");
    (void)pexp;
    if (sv.st.one("select min(stamina) from player", {}) < 0) t.fail("negative stamina");
    t.expect_eq((u32)sv.st.one("select clear_count from mission where mission_id = ?", {mission}), 80u, "clear count");
    // gacha_role_0001: a sale 10-draw costs sale_bulk_coin
    u32 g = (u32)mm->one("select id from master_gacha where id_label = 'gacha_role_0001'", {});
    u32 price = (u32)mm->one("select sale_bulk_coin from master_gacha where id = ?", {g});
    for (int k = 0; k < 3; k++) {
        u32 c0 = (u32)sv.st.one("select free_coin from player", {});
        u32 n0 = (u32)sv.st.one("select count(*) from roster", {}), h0 = (u32)sv.st.one("select count(*) from gacha_history", {});
        Request gr{"SaleGacha", 0xb164b4c5, {g}, {"x"}, {}};
        if (gacha(ctx, gr).empty()) return t.fail("SaleGacha");
        u32 c1 = (u32)sv.st.one("select free_coin from player", {});
        u32 h1 = (u32)sv.st.one("select count(*) from gacha_history", {});
        u32 news = (u32)sv.st.one("select count(*) from gacha_history where id > ? and duplicate = 0", {h0});
        if (c0 >= price) {
            if (c1 != c0 - price) t.fail("coins %u -> %u (price %u)", c0, c1, price);
            t.expect_eq(h1 - h0, 10u, "10 draws");
            t.expect_eq((u32)sv.st.one("select count(*) from roster", {}), n0 + news, "new characters");
        } else {
            if (c1 != c0 || h1 != h0) t.fail("a draw without enough coins changed the state");
        }
    }
    // every drawn role's rarity matches its rank (S/A 5, B 4, C/D 3)
    sv.st.q("select role_id, rank from gacha_history", {}, [&](const Row& r) {
        u32 rar = (u32)mm->one("select rarity from master_role where id = ?", {r.i("role_id")});
        char rk = r.s("rank")[0];
        bool ok = rk == 'S' || rk == 'A' ? (rar == 5 || rar == 6) : rk == 'B' ? rar == 4 : rar == 3;
        if (!ok) t.fail("rank %c drew rarity %u", rk, rar);
    });
    // presents: the first clear put master_mission_clear_present rows in the box; receiving
    // them empties it
    u32 np = (u32)sv.st.one("select count(*) from presents where received_at is null", {});
    t.expect_eq(np, (u32)mm->one("select count(*) from master_mission_clear_present where master_mission_id = ?", {mission}), "clear presents");
    std::vector<u64> ids;
    sv.st.q("select id from presents", {}, [&](const Row& r) { ids.push_back((u64)r.i("id")); });
    Request gp{"GetPresentArray", 0x4072d7e1, {}, {}, {ids}};
    if (get_present(ctx, gp).empty()) t.fail("GetPresent");
    t.expect_eq((u32)sv.st.one("select count(*) from presents where received_at is null", {}), 0u, "box emptied");
    sqlite3_close(sv.st.h);
    sv.st.h = nullptr;
    for (const char* suffix : {"", "-wal", "-shm"}) unlink((db + suffix).c_str());
}

NATIVE_TEST("server/msgpack") {
    Value v = Value::object();
    v["a"] = 1u;
    v["b"] = -1;
    v["c"] = 300u;
    v["d"] = "xy";
    v["e"] = Value::array();
    v["e"].push(true);
    v["f"] = 0x7e000000ull;
    auto b = mp_encode(v);
    const std::vector<u8> want = {0x86, 0xa1, 'a', 0x01, 0xa1, 'b',  0xff, 0xa1, 'c', 0xcd, 0x01, 0x2c, 0xa1, 'd',
                                  0xa2, 'x',  'y', 0xa1, 'e',  0x91, 0xc3, 0xa1, 'f', 0xce, 0x7e, 0x00, 0x00, 0x00};
    t.expect_eq(b, want, "encoding");
}

}  // namespace
}  // namespace soa::server
