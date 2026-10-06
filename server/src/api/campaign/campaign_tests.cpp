// Unit tests of the story campaign (api/campaign/campaign.h; --selftest "campaign/"; names were
// server/campaign-unlock-chain and server/campaign-splice before R18): the unlock chain against the
// master data, and the response splice. Not differential (the server has no guest counterpart).
#include <algorithm>
#include <string>
#include <vector>

#include "api/campaign/campaign.h"
#include "core/errors.h"
#include "soaserver/config.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server::campaign {
namespace {

// Finds the Mission list of `area` in an ActiveMissionList and returns the listed mission ids.
std::vector<u32> listed_in_area(const Value& aml, u32 area) {
    std::vector<u32> out;
    const Value* missions = aml.find("Mission");
    const Value* list = missions ? missions->find(std::to_string(area)) : nullptr;
    if (list)
        for (auto& e : list->arr) out.push_back((u32)e.get_u("id"));
    return out;
}

u32 id_of(const Master& m, const char* label) {
    for (auto& [id, x] : m.missions)
        if (x.label == label) return id;
    return 0;
}

}  // namespace

NATIVE_TEST("campaign/unlock-chain") {
    const Master& m = master();
    if (m.missions.empty()) return;  // no master DB next to the port: nothing to check
    u32 area01 = 0;
    for (auto& [id, a] : m.areas)
        if (a.label == "planet01_area01") area01 = id;
    u32 mf1 = id_of(m, "mf01_001"), mc30 = id_of(m, "mc01_030"), ms2 = id_of(m, "ms01_002"), mc25 = id_of(m, "mc01_025");
    State s;
    // Seeded up to mf01_001: its chain is cleared, mf01_001 listed, mc01_030 not yet.
    for (u32 u = m.missions.at(mf1).unlock; u; u = m.missions.at(u).unlock) s.cleared.insert(u);
    t.expect_eq(s.cleared.count(mc25), (size_t)1, "chain before mf01_001 cleared");
    auto l = listed_in_area(build_active_mission_list(s), area01);
    auto has = [&](u32 id) { return std::find(l.begin(), l.end(), id) != l.end(); };
    t.expect_eq(has(mf1), true, "mf01_001 listed");
    t.expect_eq(has(mc30), false, "mc01_030 not yet listed");
    s.cleared.insert(mf1);
    l = listed_in_area(build_active_mission_list(s), area01);
    t.expect_eq(has(mc30), true, "mc01_030 listed after mf01_001");
    t.expect_eq(has(ms2), false, "ms01_002 not yet listed");
    s.cleared.insert(mc30);
    l = listed_in_area(build_active_mission_list(s), area01);
    t.expect_eq(has(ms2), true, "ms01_002 listed after mc01_030");
    // A new player sees only the first prologue mission.
    State fresh;
    size_t listed = 0;
    for (auto& [id, x] : m.missions) listed += x.area && available(m, fresh, x);
    t.expect_eq(listed, (size_t)1, "a new player has one mission (mc00_010)");
}

// The splice as on_response runs it: the body decoded, spliced, encoded again.
bool splice_bytes(std::vector<char>& body, const std::vector<std::pair<std::string, Value>>& add) {
    Value root;
    if (!decode_body(body, root) || !splice_data(root, add)) return false;
    std::vector<u8> e = mp_encode(root);
    body.assign(e.begin(), e.end());
    return true;
}
Value one_key(const char* k, Value v) {
    Value m = Value::object();
    m[k] = std::move(v);
    return m;
}

NATIVE_TEST("campaign/splice") {
    // {"data": {"a": 1, "b": 2}, "status": 0} + {"b": [], "c": true} -> data {"a":1, "b": [], "c": true}
    std::vector<char> body = {(char)0x82, (char)0xa4, 'd',        'a', 't', 'a', (char)0x82, (char)0xa1, 'a', 1, (char)0xa1,
                              'b',        2,          (char)0xa6, 's', 't', 'a', 't',        'u',        's', 0};
    std::vector<std::pair<std::string, Value>> add = {{"b", Value::array()}, {"c", Value(true)}};
    t.expect_eq(splice_bytes(body, add), true, "splice ok");
    std::vector<char> want = {(char)0x82, (char)0xa4, 'd', 'a',        't',        'a', (char)0x83, (char)0xa1, 'a', 1,   (char)0xa1, 'b',
                              (char)0x90, (char)0xa1, 'c', (char)0xc3, (char)0xa6, 's', 't',        'a',        't', 'u', 's',        0};
    t.expect_eq(body == want, true, "spliced body");
    // A map value merges into an existing map: {"P": {"x": 1, "y": 2}} + {"P": {"y": 3}} -> {"x": 1, "y": 3}
    std::vector<char> pb = {(char)0x81, (char)0xa4, 'd',        'a', 't', 'a',        (char)0x81, (char)0xa1,
                            'P',        (char)0x82, (char)0xa1, 'x', 1,   (char)0xa1, 'y',        2};
    t.expect_eq(splice_bytes(pb, {{"P", one_key("y", Value(3u))}}), true, "merge splice ok");
    std::vector<char> pw = {(char)0x81, (char)0xa4, 'd',        'a', 't', 'a',        (char)0x81, (char)0xa1,
                            'P',        (char)0x82, (char)0xa1, 'x', 1,   (char)0xa1, 'y',        3};
    t.expect_eq(pb == pw, true, "merged map");
    // A replaced key moves after the kept ones; a non-map value replaces a map.
    std::vector<char> rb = {(char)0x81, (char)0xa4, 'd', 'a', 't', 'a', (char)0x82, (char)0xa1, 'P', (char)0x80, (char)0xa1, 'q', 7};
    t.expect_eq(splice_bytes(rb, {{"P", Value(5u)}}), true, "replace splice ok");
    std::vector<char> rw = {(char)0x81, (char)0xa4, 'd', 'a', 't', 'a', (char)0x82, (char)0xa1, 'q', 7, (char)0xa1, 'P', 5};
    t.expect_eq(rb == rw, true, "replaced value last");
    std::vector<char> bad = {(char)0x91, 1};
    t.expect_eq(splice_bytes(bad, add), false, "non-map body refused");
    std::vector<char> nodata = {(char)0x81, (char)0xa1, 'x', 1};
    t.expect_eq(splice_bytes(nodata, add), false, "no data map refused");
    // Not the encoder's canonical form (5 as a uint8): left alone, since the rest couldn't be
    // re-encoded unchanged; so is a truncated body.
    std::vector<char> wide = {(char)0x81, (char)0xa4, 'd', 'a', 't', 'a', (char)0x81, (char)0xa1, 'a', (char)0xcc, 5};
    t.expect_eq(splice_bytes(wide, add), false, "non-canonical body refused");
    std::vector<char> cut = {(char)0x81, (char)0xa4, 'd', 'a', 't', 'a', (char)0x82, (char)0xa1, 'a', 1};
    t.expect_eq(splice_bytes(cut, add), false, "truncated body refused");
}

// ---- the progress and the request's transaction (docs/code-review-2026-10-06.md S2) -----------

namespace {

constexpr u32 kFidMissionStart = 0xb7c62bc2, kFidMissionEnd = 0x8312a64c, kFidMissionTalk = 0x816dc8b4;
Request start_req(u32 mission) { return Request{"MissionStart", kFidMissionStart, {0, mission, 0, 0, 0, 0, 0}, {}, {}}; }
Request end_req(u32 mission) { return Request{"MissionEnd", kFidMissionEnd, {mission, 0}, {}, {}}; }

// A scratch server as the live one (server::answer, ext::with_live_server), with the server
// switched on, for the length of a test; restores both.
struct AsLiveServer {
    Server* previous;
    bool was_enabled;
    std::string was_fail;
    explicit AsLiveServer(ScratchServer& s) : previous(set_live_server_for_test(&s.sv)), was_enabled(config().enabled), was_fail(config().fail) {
        config().enabled = true;
    }
    ~AsLiveServer() {
        set_live_server_for_test(previous);
        config().enabled = was_enabled;
        config().fail = was_fail;
    }
};

// Whether mission `id` is listed as cleared in an ActiveMissionList (msgpack).
bool listed_clear(const std::vector<uint8_t>& aml, u32 id) {
    Value v = mp_decode(aml);
    const Value* missions = v.find("Mission");
    if (!missions) return false;
    for (auto& [area, list] : missions->map)
        for (auto& e : list.arr)
            if (e.get_u("id") == id) return e.find("is_clear") && e.find("is_clear")->b;
    return false;
}

}  // namespace

// An accepted MissionEnd / MissionTalk records the campaign's clear in the request's own
// transaction (through the server's handle(), as both hosts' requests go).
NATIVE_TEST("campaign/clear-in-the-request") {
    ScratchServer s(t.rand_u64());
    if (!s.ok) return;
    u32 battle = s.id("master_mission", "mf01_001"), talk = s.id("master_mission", "mc01_030");
    t.expect_eq(s.call(start_req(battle)), 0u, "MissionStart");
    t.expect_eq(s.call(end_req(battle)), 0u, "MissionEnd");
    t.expect_eq(s.sv.st.one("select count(*) from campaign_clear where mission_id = ?", {battle}), (int64_t)1, "the battle's clear recorded");
    t.expect_eq(s.sv.st.one("select mission_id from campaign_last where id = 1", {}), (int64_t)battle, "as the last play");
    t.expect_eq(s.call(Request{"MissionTalk", kFidMissionTalk, {0, talk, 0, 0}, {}, {}}), 0u, "MissionTalk");
    t.expect_eq(s.sv.st.one("select count(*) from campaign_clear where mission_id = ?", {talk}), (int64_t)1, "the scene's clear recorded");
}

// A refused MissionEnd (here --fail MissionEnd:10208) records no clear: the campaign's write is
// rolled back with the rest of the request. Through server::answer, the hosts' lifecycle.
NATIVE_TEST("campaign/refused-mission-end-records-no-clear") {
    ScratchServer s(t.rand_u64());
    if (!s.ok) return;
    AsLiveServer live(s);
    // mc00_010: the one mission a new player has listed
    u32 battle = s.id("master_mission", "mc00_010");
    t.expect_eq(answer(start_req(battle), {}).error_code, 0u, "MissionStart");
    config().fail = "MissionEnd:10208";
    Reply r = answer(end_req(battle), {});
    t.expect_eq(r.error_code, (u32)ErrorCode::kItemUnusable, "MissionEnd refused");
    t.expect_eq(s.sv.st.one("select count(*) from campaign_clear where mission_id = ?", {battle}), (int64_t)0, "no clear recorded");
    t.expect_eq(listed_clear(active_mission_list_msgpack(), battle), false, "nor listed as cleared");
}

// The progress is the state DB's: a second server (another state) doesn't see the first one's
// clears (the campaign kept a copy loaded once per process).
NATIVE_TEST("campaign/progress-follows-the-state-db") {
    u32 battle = 0;
    {
        ScratchServer a(t.rand_u64());
        if (!a.ok) return;
        AsLiveServer live(a);
        battle = a.id("master_mission", "mc00_010");  // listed for a new player
        answer(start_req(battle), {});
        t.expect_eq(answer(end_req(battle), {}).error_code, 0u, "MissionEnd on the first state");
        t.expect_eq(listed_clear(active_mission_list_msgpack(), battle), true, "listed as cleared there");
    }
    ScratchServer b(t.rand_u64());
    if (!b.ok) return;
    AsLiveServer live(b);
    t.expect_eq(listed_clear(active_mission_list_msgpack(), battle), false, "not cleared on a fresh state");
}

}  // namespace soa::server::campaign
