// Unit tests of seeding (state/seed.h). Run in --selftest; not differential (the server has no guest counterpart). Test names are
// their seeds (testing.h): they keep the names they had in core/server.cpp.
#include <unistd.h>

#include <set>
#include <string>
#include <vector>

#include "state/kvs.h"
#include "state/seed.h"
#include "soaserver/config.h"
#include "soaserver/master_source.h"
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

// Which save a new state is seeded from (docs/server-rules.md#seed): with no seed save (a packaged
// build ships none) and no --new-player, a new state has no player, so the client runs its own
// new-player flow; the client's own Game.xml (--game-xml) counts only when it holds a player (the
// client writes a settings-only one at its first start); --seed FILE seeds from FILE; --new-player
// never seeds. The checkout's data/saves/seed/Game.xml is hidden by pointing the repo roots at a
// directory without it.
NATIVE_TEST("server/seed-source-rule") {
    const std::string master = master_source::resolve();
    const std::string test_seed = find_repo_file("server/tests/fixtures/test-seed.xml");
    if (master.empty() || test_seed.empty()) return t.fail("needs the 3.7.0 master and server/tests/fixtures/test-seed.xml");
    ServerConfig& c = config();
    const ServerConfig saved = c;
    const std::string tag = "/tmp/soa-server-seedrule-" + std::to_string(getpid());
    const std::string settings = tag + "-client-Game.xml";
    // the client's first-start Game.xml: its settings, no player (BAS:PlayerName 0)
    write_kvs(settings, {{"BAS:EffectAlpha", std::string("\x64\0\0\0", 4)},
                         {"BAS:VoiceLanguage", std::string("\0\x01\0\0", 4)},
                         {"BAS:PlayerName", std::string("\0", 1)}});
    c.repo_roots = {tag + "-no-checkout"};  // non-empty: no fallback to the working directory
    c.seed.clear();
    c.game_xml.clear();
    c.new_player = false;
    int n = 0;
    // a fresh state DB opened as Server::init opens one; its player count
    auto players = [&](const std::string& seed_save) -> long long {
        Server sv;
        sv.live = false;
        std::string db = tag + "-" + std::to_string(n++) + ".sqlite3";
        for (const char* suffix : {"", "-wal", "-shm"}) unlink((db + suffix).c_str());
        long long r = -1;
        if (sv.m.open(master, true) && sv.open_state(db, t.rand_u64(), seed_save)) r = sv.st.one("select count(*) from player", {});
        sv.st.close();
        sv.m.close();
        for (const char* suffix : {"", "-wal", "-shm"}) unlink((db + suffix).c_str());
        return r;
    };
    t.expect_eq(real_seed_save(), std::string(), "no checkout seed save");
    t.expect_eq(seed_source(), std::string(), "no seed: none");
    t.expect_eq(players(""), 0LL, "no seed: a new state has no player (the client's new-player flow)");
    c.game_xml = settings;
    t.expect_eq(save_holds_player(settings), false, "the client's settings-only Game.xml holds no player");
    t.expect_eq(seed_source(), std::string(), "a settings-only --game-xml: no seed");
    t.expect_eq(players(""), 0LL, "a settings-only --game-xml: no player");
    c.game_xml = test_seed;
    t.expect_eq(seed_source(), test_seed, "a --game-xml holding a player seeds");
    c.game_xml = settings;
    c.seed = test_seed;
    t.expect_eq(seed_source(), test_seed, "--seed FILE");
    t.expect_eq(players(""), 1LL, "--seed FILE: seeded");
    t.expect_eq(players(test_seed), 1LL, "an explicit seed save: seeded");
    c.new_player = true;
    t.expect_eq(players(""), 0LL, "--new-player with --seed: no player");
    c = saved;
    unlink(settings.c_str());
}

}  // namespace
}  // namespace soa::server
