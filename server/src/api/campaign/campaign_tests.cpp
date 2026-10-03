// Unit tests of the story campaign (api/campaign/campaign.h; --selftest "campaign/"; names were
// server/campaign-unlock-chain and server/campaign-splice before R18): the unlock chain against the
// master data, and the response splice. Not differential (the server has no guest counterpart).
#include <algorithm>
#include <string>
#include <vector>

#include "api/campaign/campaign.h"
#include "soaserver/native_test.h"

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
    s.loaded = true;
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
    fresh.loaded = true;
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

}  // namespace soa::server::campaign
