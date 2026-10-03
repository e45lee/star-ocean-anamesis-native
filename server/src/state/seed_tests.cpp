// Unit tests of seeding (state/seed.h). Run in --selftest; not differential (the server has no guest counterpart). Test names are
// their seeds (testing.h): they keep the names they had in core/server.cpp.
#include <unistd.h>

#include <set>
#include <string>
#include <vector>

#include "state/kvs.h"
#include "state/seed.h"
#include "soaserver/config.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

using ext::Row;

// Seeding from an offline-build save (the offline game's Game.xml, with its BAS:StandAlone* keys):
// soa-server --seed / soa --seed take it like a 3.7.0 one. The committed sanitized offline save is
// data/saves/client/Game.xml (rank 87 "Fayt", 276 characters, placeholder BAS:PlayerID).
NATIVE_TEST("server/seed-from-380-save") {
    std::string master = find_repo_file("data/basmaster-3.7.0.sqlite3");
    std::string save = find_repo_file("data/saves/client/Game.xml");
    if (master.empty() || save.empty()) return t.fail("needs data/basmaster-3.7.0.sqlite3 and data/saves/client/Game.xml");
    auto kv = read_kvs(save);
    if (kv.find("BAS:StandAloneNewPlayer") == kv.end()) t.fail("data/saves/client/Game.xml isn't an offline-build save (no BAS:StandAloneNewPlayer)");
    Server sv;
    sv.live = false;
    std::string db = "/tmp/soa-server-seed380-" + std::to_string(getpid()) + ".sqlite3";
    for (const char* suffix : {"", "-wal", "-shm"}) unlink((db + suffix).c_str());
    if (!sv.m.open(master, true) || !sv.open_state(db, t.rand_u64(), save)) return t.fail("open");
    t.expect_eq((u32)sv.st.one("select level from player", {}), kv_u32(kv, "player_level"), "player level");
    t.expect_eq((u32)sv.st.one("select fol from player", {}), kv_u32(kv, "player_fol"), "FOL");
    t.expect_eq((u32)sv.st.one("select count(*) from roster", {}), kv_u32(kv, "person_size"), "roster size");
    std::string name;
    sv.st.q("select name from player", {}, [&](const Row& r) { name = r.s("name"); });
    t.expect_eq(name, kv_str(kv, "player_name"), "name");
    // never the save's own BAS:PlayerID: the server's sanitized local id
    std::string search;
    sv.st.q("select search_id from player", {}, [&](const Row& r) { search = r.s("search_id"); });
    t.expect_eq(search, std::string(kLocalPlayerId), "player id");
    if (sv.st.h) sqlite3_close(sv.st.h);
    sv.st.h = nullptr;
    for (const char* suffix : {"", "-wal", "-shm"}) unlink((db + suffix).c_str());
}

}  // namespace
}  // namespace soa::server
