// Unit tests of the missions (api/missions/missions.h): the surprise roll, campaigns and battle
// evaluation of the drop roll; MissionStart's stamina refusal and MissionEnd's unlocks. Run in
// --selftest "missions/"; not differential (the server has no guest counterpart). Test names are
// their seeds (testing.h).
#include <unistd.h>

#include <set>
#include <string>
#include <vector>

#include "api/missions/missions.h"
#include "soaserver/config.h"
#include "soaserver/msgpack.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

using ext::Row;

NATIVE_TEST("missions/surprise-campaign-evaluation") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;  // needs the 3.7.0 master and save
    Server& sv = S.sv;
    RequestContext rc = sv.new_request();  // for the handlers called directly
    ext::Ctx ctx = sv.make_ctx(rc);
    // (a) mf01_003: a surprise enemy mission, 3 surprise lots from its is_surprise_enemy rows
    u32 m3 = S.id("master_mission", "mf01_003");
    std::set<u32> surprise_ids;
    sv.m.q("select content_id from master_mission_drop where master_mission_id = ? and is_surprise_enemy = 1", {m3},
           [&](const Row& r) { surprise_ids.insert((u32)r.i("content_id")); });
    auto R = roll_drops(ctx, m3, "master_mission", 0, 0, true, {});
    t.expect_eq(R.surprise_lots, 3u, "surprise lots");
    u32 hits = 0;
    for (auto& d : R.drops) hits += surprise_ids.count(d.id);
    if (hits < 3) t.fail("surprise drops %u < 3", hits);
    auto R0 = roll_drops(ctx, m3, "master_mission", 0, 0, false, {});
    t.expect_eq(R0.surprise_lots, 0u, "no surprise, no surprise lots");
    // the roll at MissionStart: ~10.25 % of the starts of mf01_003 meet the surprise enemy
    Request ms{"MissionStart", 0xb7c62bc2, {0, m3, 0, 0, 0, 0, 0}, {}, {}};
    int surprises = 0;
    for (int k = 0; k < 400; k++) {
        sv.st.q("update player set stamina = 200", {});
        if (S.call(ms) != 0) return t.fail("MissionStart refused");
        surprises += (int)sv.st.one("select surprise from play where id = 1", {});
    }
    if (surprises < 18 || surprises > 70) t.fail("surprise rate: %d / 400", surprises);
    // (a) Campaign_evo_blue_prism (2017-05-30 .. 2017-08-30, area event_evo_blue): +1 lot and one
    // campaign-drop lot for me99_085
    S.set_clock("2017-06-01 12:00:00");
    u32 me = S.id("master_event_mission", "me99_085");
    u32 area = (u32)sv.m.one("select master_event_area_id from master_event_mission where id = ?", {me});
    std::set<u32> camp_ids;
    sv.m.q("select content_id from master_campaign_drop where master_campaign_id_label = 'Campaign_evo_blue_prism'", {},
           [&](const Row& r) { camp_ids.insert((u32)r.i("content_id")); });
    auto C = roll_drops(ctx, me, "master_event_mission", 1, area, false, {});
    t.expect_eq(C.campaign_lots, 1u, "campaign lots");
    bool camp = false;
    for (auto& d : C.drops) camp |= camp_ids.count(d.id) > 0;
    t.expect_eq(camp, true, "a campaign drop");
    S.set_clock("2019-06-01 12:00:00");
    t.expect_eq(roll_drops(ctx, me, "master_event_mission", 1, area, false, {}).campaign_lots, 0u, "campaign over");
    // (a) evaluation: me99_MemLast_07 clear time 60000 / 120000 ms (type 6)
    u32 ml = S.id("master_event_mission", "me99_MemLast_07");
    rc.test_log_value = 59000;
    auto E = roll_drops(ctx, ml, "master_event_mission", 1, 0, false, {});
    t.expect_eq(E.evaluations.size(), (size_t)1, "evaluation reached");
    u32 want = (u32)sv.m.one(
        "select rank_1_drop_count from master_battle_evaluation where evaluation_group_id = "
        "(select evaluation_group_id from master_event_mission where id = ?) and evaluation_type = 6",
        {ml});
    t.expect_eq(E.eval_lots, want, "rank 1 lots");
    rc.test_log_value = 0;
    t.expect_eq(roll_drops(ctx, ml, "master_event_mission", 1, 0, false, {}).evaluations.size(), (size_t)0, "no time, no rank");
    // (b)+(a) type 5 (highest single damage, condition 50,000,000) is evaluated from the battle's
    // evaluation array (the tests use test_log_value)
    rc.test_log_value = 60000000;
    auto E5 = roll_drops(ctx, ml, "master_event_mission", 1, 0, false, {});
    t.expect_eq(E5.evaluations.size(), (size_t)1, "type 5 reached");
    rc.test_log_value = 0;
}

NATIVE_TEST("missions/unlock-refusal") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    RequestContext rc = sv.new_request();  // for the handlers called directly
    ext::Ctx ctx = sv.make_ctx(rc);
    u32 m1 = S.id("master_mission", "mf01_001");
    Request ms{"MissionStart", 0xb7c62bc2, {0, m1, 0, 0, 0, 0, 0}, {}, {}};
    Request me{"MissionEnd", 0x8312a64c, {m1, 0}, {}, {}};
    // stamina short: refused with 10004, nothing changes (stamina, play record, play count)
    sv.st.q("update player set stamina = 1, stamina_at = ?", {clock_now()});
    std::vector<u8> out;
    t.expect_eq(S.call(ms, &out), 10004u, "error code");
    t.expect_eq((u32)sv.st.one("select stamina from player", {}), 1u, "stamina kept");
    t.expect_eq((u32)sv.st.one("select count(*) from play", {}), 0u, "no play record");
    t.expect_eq((u32)sv.st.one("select ifnull(sum(play_count), 0) from mission", {}), 0u, "no play count");
    if (out.empty()) t.fail("a refusal still answers a body");
    // enough stamina: accepted, error code back to 0
    sv.st.q("update player set stamina = 100", {});
    t.expect_eq(S.call(ms), 0u, "accepted");
    // the first clear of mf01_001 opens the missions it unlocks (mc01_030)
    t.expect_eq(S.call(me), 0u, "MissionEnd");
    u32 mc = S.id("master_mission", "mc01_030");
    t.expect_eq((u32)sv.st.one("select count(*) from unlocks where mission_id = ? and by_mission = ?", {mc, m1}), 1u, "mc01_030 unlocked");
    t.expect_eq(S.call(ms), 0u, "again");
    t.expect_eq(S.call(me), 0u, "second clear");
    t.expect_eq((u32)sv.st.one("select count(*) from unlocks", {}),
                (u32)sv.m.one("select count(*) from master_mission where unlock_mission_id = ?", {m1}), "unlocks recorded once");
    // --fail isn't given in the tests: the forced-error option is off
    t.expect_eq(sv.forced_error("MissionStart"), 0u, "no forced error");
}

// MissionEnd of no mission (no argument and no play, or an id in no mission table) isn't answered
// and records nothing (it used to record mission 0 as cleared); a known mission still ends.
NATIVE_TEST("missions/end-unknown-mission") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    const u32 kNotHandled = 0xffffffffu;
    auto recorded = [&] { return (u32)sv.st.one("select count(*) from mission", {}); };
    u32 before = recorded();
    t.expect_eq(S.call({"MissionEnd", 0x8312a64c, {}, {}, {}}), kNotHandled, "no argument, no play: not answered");
    t.expect_eq((u32)sv.st.one("select count(*) from mission where mission_id = 0", {}), 0u, "mission 0 not recorded");
    t.expect_eq(S.call({"MissionEnd", 0x8312a64c, {12345, 0}, {}, {}}), kNotHandled, "an unknown id: not answered");
    t.expect_eq(recorded(), before, "nothing recorded");
    // a known mission ends as before, also when its start was refused (no play: the request's id)
    u32 m1 = S.id("master_mission", "mf01_001");
    t.expect_eq(S.call({"MissionEnd", 0x8312a64c, {m1, 0}, {}, {}}), 0u, "a known mission without a play: answered");
    t.expect_eq((u32)sv.st.one("select clear_count from mission where mission_id = ?", {m1}), 1u, "cleared");
    // with a play, no argument ends the play's mission
    sv.st.q("update player set stamina = 100", {});
    t.expect_eq(S.call({"MissionStart", 0xb7c62bc2, {0, m1, 0, 0, 0, 0, 0}, {}, {}}), 0u, "start");
    t.expect_eq(S.call({"MissionEnd", 0x8312a64c, {}, {}, {}}), 0u, "no argument: the play's mission");
    t.expect_eq((u32)sv.st.one("select clear_count from mission where mission_id = ?", {m1}), 2u, "the play's mission cleared");
}

// The play record (PLAN-schema S7): MissionStart writes one `play` row and the party as
// `play_member` rows in battle order (owned characters, or the tutorial's mission NPCs as
// npc_uid); MissionFailed ends all of it, so a MissionEnd with no play in progress reads no mission
// type, surprise roll or party (before S7, MissionFailed left play_ext's type and surprise behind).
NATIVE_TEST("missions/play-record") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    u32 m3 = S.id("master_mission", "mf01_003");
    sv.st.q("update player set stamina = 200", {});
    t.expect_eq(S.call({"MissionStart", 0xb7c62bc2, {0, m3, 0, 0, 0, 0, 0}, {}, {}}), 0u, "start");
    t.expect_eq((u32)sv.st.one("select count(*) from play", {}), 1u, "one play");
    t.expect_eq((u32)sv.st.one("select mission_id from play", {}), m3, "its mission");
    const u32 members = (u32)sv.st.one("select count(*) from play_member", {});
    t.expect_eq(members > 0, true, "the party recorded");
    t.expect_eq((u32)sv.st.one("select count(*) from play_member m join roster r on r.uid = m.uid where m.npc_uid is null", {}), members,
                "owned characters");
    t.expect_eq(
        (u32)sv.st.one("select count(*) from play_member where slot != (select count(*) from play_member p where p.slot < play_member.slot)", {}), 0u,
        "slots 0..n-1");
    // a surprise roll, then the battle is lost
    sv.st.q("update play set surprise = 1", {});
    t.expect_eq(S.call({"MissionFailed", 0x479604f6, {0, m3}, {}, {}}), 0u, "MissionFailed");
    t.expect_eq((u32)sv.st.one("select count(*) from play", {}), 0u, "the play ended");
    t.expect_eq((u32)sv.st.one("select count(*) from play_member", {}), 0u, "its members with it");
    // a MissionEnd naming the mission, with no play: no party gets EXP, nothing stale is read
    std::vector<u8> out;
    t.expect_eq(S.call({"MissionEnd", 0x8312a64c, {m3, 0}, {}, {}}, &out), 0u, "MissionEnd without a play");
    Value d = out.empty() ? Value() : mp_decode(out);
    const Value* data = d.find("data");
    const Value* result = data ? data->find("MissionResultCharacter") : nullptr;
    t.expect_eq(result && result->type == Value::Map ? result->map.size() : (size_t)99, (size_t)0, "no party: no character EXP");
    // the tutorial battle's NPC party: npc_uid, no roster reference
    u32 tutorial = S.id("master_mission", "ms00_001");
    t.expect_eq(S.call({"MissionStart", 0xb7c62bc2, {0, tutorial, 0, 0, 0, 0, 0}, {}, {}}), 0u, "the tutorial battle");
    const u32 npcs = (u32)sv.m.one("select count(*) from master_mission_npc where master_mission_id = ?", {tutorial});
    t.expect_eq((u32)sv.st.one("select count(*) from play_member where uid is null and npc_uid between 2130706433 and 2130706687", {}), npcs,
                "the mission NPCs as npc_uid");
    t.expect_eq((u32)sv.st.one("select min(npc_uid) from play_member", {}), 0x7f000001u, "kNpcPartyUid0 + 1 first");
}

}  // namespace
}  // namespace soa::server
