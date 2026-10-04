// The stubs (ext::add_stub, core/stub.cpp; --selftest "server/stubs"): every stub of
// docs/unimplemented-apis.md part 3 step 8 (the social calls, the Debug* APIs) is a registered
// handler that answers success with data.Time and changes nothing in the state.
#include <string>
#include <vector>

#include "soaserver/ext.h"
#include "soaserver/msgpack.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

const char* const kStubs[] = {
    "FollowAdd",
    "FollowRemove",
    "BlacklistAdd",
    "BlacklistRemove",
    "UpdateFollowMax",
    "NeighborList",
    "NeighborRegist",
    "LocationRegist",
    "DebugBarneyChance",
    "DebugCharacterBoost",
    "DebugCreatePlayer",
    "DebugDeepBonus",
    "DebugDeepBonusRareMission",
    "DebugDeepMissionDrop",
    "DebugDeletePlayer",
    "DebugFavorLoginBonus",
    "DebugGacha",
    "DebugGachaMutation",
    "DebugGear",
    "DebugGearDrop",
    "DebugGetCharacter",
    "DebugGetCoin",
    "DebugGetFol",
    "DebugGetItem",
    "DebugGradeUpCharacter",
    "DebugItemBoost",
    "DebugLotDeity",
    "DebugMissionDrop",
    "DebugOpenMission",
    "DebugSphere211LotAsset",
    "DebugSphere211LotEnemyLevel",
    "DebugSphere211LotFloorNum",
    "DebugSphere211LotMission",
    "DebugSphere211TreasureBox",
    "DebugTowerMax",
};

// Every row of every table, as text: the state's whole content.
std::string state_dump(ext::Sql& st) {
    std::vector<std::string> tables;
    st.q("select name from sqlite_master where type = 'table' order by name", {}, [&](const ext::Row& r) { tables.push_back(r.s("name")); });
    std::string out;
    for (const std::string& name : tables) {
        out += "## " + name + "\n";
        st.q("select * from \"" + name + "\" order by rowid", {}, [&](const ext::Row& r) {
            for (const auto& kv : r.v) out += kv.first + "=" + r.s(kv.first.c_str()) + " ";
            out += "\n";
        });
    }
    return out;
}

NATIVE_TEST("server/stubs") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    RequestContext request = sv.new_request();
    ext::Ctx ctx = sv.make_ctx(request);
    const std::string before = state_dump(sv.st);
    for (const char* m : kStubs) {
        const ext::Handler* h = ext::find(m);
        if (!h) {
            t.fail("%s: no handler registered", m);
            continue;
        }
        Request r;
        r.method = m;
        r.fid = 0x1234;
        r.ints = {7, 9};
        r.strs = {"x"};
        r.vecs = {{1, 2, 3, 4, 5, 6}};
        std::vector<u8> b = (*h)(ctx, r);
        if (b.empty()) {
            t.fail("%s: not handled", m);
            continue;
        }
        Value v = mp_decode(b);
        const Value* d = v.find("data");
        const Value* st = v.find("status");
        t.expect_eq(d && d->find("Time") != nullptr, true, (std::string(m) + ": data.Time").c_str());
        t.expect_eq(st && st->u == 0, true, (std::string(m) + ": status 0 (success)").c_str());
    }
    t.expect_eq(state_dump(sv.st) == before, true, "the state is unchanged");
}

}  // namespace
}  // namespace soa::server
