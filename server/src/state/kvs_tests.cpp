// Unit tests of the Game.xml codec (state/kvs.h). Run in --selftest; not differential (the server has no guest counterpart). Test names are
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

NATIVE_TEST("server/kvs-roundtrip") {
    // write_kvs / read_kvs_ordered: the game's LocalKVS file format (as soa_save/kvs.py)
    std::string p = "/tmp/soa-server-kvs-test.xml";
    std::vector<std::pair<std::string, std::string>> kv = {
        {"player_level", std::string("\x57\0\0\0", 4)}, {"player_name", std::string("Fayt\0", 5)}, {"abc", std::string(100, 'z')}};
    if (!write_kvs(p, kv)) return t.fail("write");
    auto back = read_kvs_ordered(p);
    t.expect_eq(back, kv, "roundtrip");
    auto m = read_kvs(p);
    t.expect_eq(kv_u32(m, "player_level"), 87u, "u32");
    t.expect_eq(kv_str(m, "player_name"), std::string("Fayt"), "str");
    unlink(p.c_str());
    // the committed synthetic test seed: the sanitized local id, never a real account's
    if (std::string s = find_repo_file("port/server-data/test-seed.xml"); !s.empty()) {
        auto g = read_kvs(s);
        t.expect_eq(kv_str(g, "BAS:PlayerID"), std::string(kLocalPlayerId), "test seed player id");
        if (kv_u32(g, "player_level") < 1) t.fail("test seed: no player_level");
    } else t.fail("port/server-data/test-seed.xml is missing");
    // the real 3.7.0 save (the runtime seed), when present: readable
    if (std::string s = real_seed_save(); !s.empty()) {
        auto g = read_kvs(s);
        if (kv_str(g, "BAS:PlayerID").size() != 10) t.fail("3.7.0 player id: not 10 characters");  // never copied: kLocalPlayerId
        if (kv_u32(g, "player_level") < 1) t.fail("3.7.0 save: no player_level");
    }
}

}  // namespace
}  // namespace soa::server
