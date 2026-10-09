// Unit tests of the missions (api/missions/missions.h): the surprise roll, campaigns and battle
// evaluation of the drop roll; MissionStart's stamina refusal and MissionEnd's unlocks. Run in
// --selftest "missions/"; not differential (the server has no guest counterpart). Test names are
// their seeds (testing.h).
#include <unistd.h>

#include <set>
#include <string>
#include <vector>

#include "api/missions/missions.h"
#include "api/social/rental.h"
#include "core/errors.h"
#include "soaserver/config.h"
#include "soaserver/fids.h"
#include "soaserver/msgpack.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

using ext::Row;

// The text of a one-column query's first row ("" when none).
std::string text_of(ext::Sql& db, const std::string& sql, std::initializer_list<ext::Arg> args = {}) {
    std::string v;
    db.q("select (" + sql + ") as v", args, [&](const Row& r) { v = r.s("v"); });
    return v;
}

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
    Request ms{"MissionStart", fids::kMissionStart, {0, m3, 0, 0, 0, 0, 0}, {}, {}};
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
    Request ms{"MissionStart", fids::kMissionStart, {0, m1, 0, 0, 0, 0, 0}, {}, {}};
    Request me{"MissionEnd", fids::kMissionEnd, {m1, 0}, {}, {}};
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
    t.expect_eq(S.call({"MissionEnd", fids::kMissionEnd, {}, {}, {}}), kNotHandled, "no argument, no play: not answered");
    t.expect_eq((u32)sv.st.one("select count(*) from mission where mission_id = 0", {}), 0u, "mission 0 not recorded");
    t.expect_eq(S.call({"MissionEnd", fids::kMissionEnd, {12345, 0}, {}, {}}), kNotHandled, "an unknown id: not answered");
    t.expect_eq(recorded(), before, "nothing recorded");
    // a known mission ends as before, also when its start was refused (no play: the request's id)
    u32 m1 = S.id("master_mission", "mf01_001");
    t.expect_eq(S.call({"MissionEnd", fids::kMissionEnd, {m1, 0}, {}, {}}), 0u, "a known mission without a play: answered");
    t.expect_eq((u32)sv.st.one("select clear_count from mission where mission_id = ?", {m1}), 1u, "cleared");
    // with a play, no argument ends the play's mission
    sv.st.q("update player set stamina = 100", {});
    t.expect_eq(S.call({"MissionStart", fids::kMissionStart, {0, m1, 0, 0, 0, 0, 0}, {}, {}}), 0u, "start");
    t.expect_eq(S.call({"MissionEnd", fids::kMissionEnd, {}, {}, {}}), 0u, "no argument: the play's mission");
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
    t.expect_eq(S.call({"MissionStart", fids::kMissionStart, {0, m3, 0, 0, 0, 0, 0}, {}, {}}), 0u, "start");
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
    t.expect_eq(S.call({"MissionFailed", fids::kMissionFailed, {0, m3}, {}, {}}), 0u, "MissionFailed");
    t.expect_eq((u32)sv.st.one("select count(*) from play", {}), 0u, "the play ended");
    t.expect_eq((u32)sv.st.one("select count(*) from play_member", {}), 0u, "its members with it");
    // a MissionEnd naming the mission, with no play: no party gets EXP, nothing stale is read
    std::vector<u8> out;
    t.expect_eq(S.call({"MissionEnd", fids::kMissionEnd, {m3, 0}, {}, {}}, &out), 0u, "MissionEnd without a play");
    Value d = out.empty() ? Value() : mp_decode(out);
    const Value* data = d.find("data");
    const Value* result = data ? data->find("MissionResultCharacter") : nullptr;
    t.expect_eq(result && result->type == Value::Map ? result->map.size() : (size_t)99, (size_t)0, "no party: no character EXP");
    // the tutorial battle's NPC party: npc_uid, no roster reference
    u32 tutorial = S.id("master_mission", "ms00_001");
    t.expect_eq(S.call({"MissionStart", fids::kMissionStart, {0, tutorial, 0, 0, 0, 0, 0}, {}, {}}), 0u, "the tutorial battle");
    const u32 npcs = (u32)sv.m.one("select count(*) from master_mission_npc where master_mission_id = ?", {tutorial});
    t.expect_eq((u32)sv.st.one("select count(*) from play_member where uid is null and npc_uid between 2130706433 and 2130706687", {}), npcs,
                "the mission NPCs as npc_uid");
    t.expect_eq((u32)sv.st.one("select min(npc_uid) from play_member", {}), 0x7f000001u, "kNpcPartyUid0 + 1 first");
}

// MissionContinue (docs/server-rules.md#failure-continue-restart): 1 revives for
// continue_use_coin coins (free first) and keeps the play; 0 changes nothing; a continue campaign
// halves the price (model 99 for every type; an event mission's own area); a mission with
// is_continue 0, nothing in progress or the coins short are refused. MissionLose ends the play.
NATIVE_TEST("missions/continue") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    auto coins = [&] { return (u32)sv.st.one("select free_coin from player", {}); };
    auto continued = [&](const std::vector<u8>& out) {
        Value d = out.empty() ? Value() : mp_decode(out);
        const Value* data = d.find("data");
        const Value* c = data ? data->find("is_mission_continue") : nullptr;
        return c && c->type == Value::Bool ? (int)c->b : -1;
    };
    const u32 price = (u32)std::stoul("0" + text_of(sv.m, "select value from master_global where key = 'continue_use_coin'"));
    t.expect_eq(price, 100u, "(a) continue_use_coin");
    std::vector<u8> out;
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {1}, {}, {}}), (u32)ErrorCode::kInvalidOperation, "nothing in progress: refused");
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {0}, {}, {}}, &out), 0u, "a decline without a play: answered");
    t.expect_eq(continued(out), 0, "declined");
    // a story mission (is_continue 1)
    u32 m3 = S.id("master_mission", "mf01_003");
    t.expect_eq((u32)sv.m.one("select is_continue from master_mission where id = ?", {m3}), 1u, "(a) mf01_003 continues");
    sv.st.q("update player set stamina = 200, free_coin = 1000, pay_coin = 0", {});
    t.expect_eq(S.call({"MissionStart", fids::kMissionStart, {0, m3, 0, 0, 0, 0, 0}, {}, {}}), 0u, "start");
    const std::string play_before = text_of(sv.st, "select mission_id || ',' || party_id || ',' || stamina_cost || ',' || surprise from play");
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {0}, {}, {}}, &out), 0u, "いいえ");
    t.expect_eq(continued(out), 0, "not continued");
    t.expect_eq(coins(), 1000u, "a decline costs nothing");
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {1}, {}, {}}, &out), 0u, "はい");
    t.expect_eq(continued(out), 1, "continued");
    t.expect_eq(coins(), 900u, "continue_use_coin taken");
    t.expect_eq(text_of(sv.st, "select mission_id || ',' || party_id || ',' || stamina_cost || ',' || surprise from play"), play_before,
                "the play stays open, unchanged");
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {5}, {}, {}}), 0u, "any non-zero continues");
    t.expect_eq(coins(), 800u, "and pays again");
    sv.st.q("update player set free_coin = 99", {});
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {1}, {}, {}}), (u32)ErrorCode::kCoinsShort, "coins short: refused");
    t.expect_eq(coins(), 99u, "nothing taken");
    sv.st.q("update player set free_coin = 60, pay_coin = 40", {});
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {1}, {}, {}}), 0u, "free and paid together");
    t.expect_eq(sv.st.one("select free_coin + pay_coin from player", {}), (int64_t)0, "free first, then paid");
    // (a)+(b) Campaign2021_spring_Continue (model 99, 2021-03-25 .. 04-15, x0.5): every type
    S.set_clock("2021-04-01 12:00:00");
    sv.st.q("update player set free_coin = 1000, pay_coin = 0", {});
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {1}, {}, {}}), 0u, "during the spring campaign");
    t.expect_eq(coins(), 950u, "half price");
    // an event mission in event_2020_max_04 during Campaign2020_2021_newyear_Continue_007 (its
    // area only), and one in another area
    S.set_clock("2021-01-02 12:00:00");
    const u32 area = S.id("master_event_area", "event_2020_max_04");
    const u32 in_area =
        (u32)sv.m.one("select id from master_event_mission where master_event_area_id = ? and is_continue = 1 order by id limit 1", {area});
    const u32 other = (u32)sv.m.one(
        "select id from master_event_mission where is_continue = 1 and master_event_area_id not in (select master_area_id from master_campaign "
        "where type_id = 9) order by id limit 1",
        {});
    if (!in_area || !other) return t.fail("no event missions for the area test");
    sv.st.q("update play set mission_id = ?, mission_type = 1", {in_area});
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {1}, {}, {}}), 0u, "an event mission in the campaign's area");
    t.expect_eq(coins(), 900u, "half price");
    sv.st.q("update play set mission_id = ?, mission_type = 1", {other});
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {1}, {}, {}}), 0u, "another area");
    // (Campaign2020_2021_newyear_Continue_001 is the story missions' (model 0), not the events')
    t.expect_eq(coins(), 800u, "full price");
    // (a) a tower mission: is_continue 0
    const u32 tower = (u32)sv.m.one("select id from master_tower_mission order by id limit 1", {});
    sv.st.q("update play set mission_id = ?, mission_type = 2", {tower});
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {1}, {}, {}}), (u32)ErrorCode::kInvalidOperation, "is_continue 0: refused");
    t.expect_eq(coins(), 800u, "nothing taken");
    // MissionLose (no 3.7.0 caller): ends the play as MissionFailed
    t.expect_eq(S.call({"MissionLose", fids::kMissionLose, {}, {}, {}}), 0u, "MissionLose");
    t.expect_eq((u32)sv.st.one("select count(*) from play", {}), 0u, "the play ended");
}

// TrainingMissionStart (docs/server-rules.md#battle-simulator): the simulator's mission and stage
// from master_training_mission, the current party, no stamina, no play record or play count (so
// the next GetPlayMission offers no resume).
NATIVE_TEST("missions/training-start") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    const u32 sim = S.id("master_training_mission", "simulator_mission01");
    t.expect_eq(text_of(sv.m, "select value from master_global where key = 'training_mission_id_label'"), std::string("simulator_mission01"),
                "(a) the training mission");
    sv.st.q("update player set stamina = 7", {});
    const u32 party = (u32)sv.st.one("select ifnull(party_id, 1) from player", {});
    std::vector<u8> out;
    t.expect_eq(S.call({"TrainingMissionStart", fids::kTrainingMissionStart, {sim, 1, 0}, {}, {}}, &out), 0u, "started");
    Value d = out.empty() ? Value() : mp_decode(out);
    const Value* data = d.find("data");
    const Value* mp = data ? data->find("MissionParameter") : nullptr;
    t.expect_eq(mp ? mp->get_u("master_mission_id") : 0, (u64)sim, "the simulator's mission");
    const Value* stages = mp ? mp->find("mission_stage") : nullptr;
    t.expect_eq(stages ? stages->arr.size() : 0, (size_t)sv.m.one("select count(*) from master_mission_stage where master_mission_id = ?", {sim}),
                "its stages");
    if (stages && !stages->arr.empty())
        t.expect_eq(stages->arr[0].find("id_label") ? stages->arr[0].find("id_label")->s : std::string(), std::string("simulator_mission01_Stage01"),
                    "the simulator's stage");
    const Value* bp = data ? data->find("BattleParameter") : nullptr;
    const Value* pc = bp ? bp->find("PlayerCharacter") : nullptr;
    std::vector<u64> want;
    sv.st.q("select uid from party_member where party_id = ? and uid is not null order by slot", {party},
            [&](const ext::Row& r) { want.push_back((u64)r.i("uid")); });
    std::vector<u64> got;
    if (pc)
        for (const Value& m : pc->arr) got.push_back(m.get_u("id"));
    t.expect_eq(got == want, true, "the current party");
    t.expect_eq((u32)sv.st.one("select stamina from player", {}), 7u, "(a) no stamina");
    t.expect_eq((u32)sv.st.one("select count(*) from play", {}), 0u, "no play record");
    t.expect_eq((u32)sv.st.one("select count(*) from mission where mission_id = ?", {sim}), 0u, "no play count");
    std::vector<u8> pm;
    t.expect_eq(S.call({"GetPlayMission", fids::kGetPlayMission, {}, {}, {}}, &pm), 0u, "GetPlayMission");
    Value p = pm.empty() ? Value() : mp_decode(pm);
    const Value* pdata = p.find("data");
    const Value* play = pdata ? pdata->find("PlayMission") : nullptr;
    t.expect_eq(play ? play->get_u("is_play") : 9, (u64)0, "nothing to resume");
    // a lost simulator battle: OpenContinue declines by itself (is_continue 0): answered
    t.expect_eq(S.call({"MissionContinue", fids::kMissionContinue, {0}, {}, {}}), 0u, "the automatic decline");
    t.expect_eq(S.call({"TrainingMissionStart", fids::kTrainingMissionStart, {12345, 1, 0}, {}, {}}) != 0, true, "an unknown mission isn't answered");
}

// MissionRestart replays the recorded helper (PLAN-schema S7; before, it sent the play's party id
// as the helper index and no helper ids, so the restarted battle lost its helper): an own
// character stays rental_sub_character_id and a member; a rental clone stays member 4 and its
// rental day isn't counted again; the play's party set fights again.
NATIVE_TEST("missions/restart-helper") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    u32 m1 = S.id("master_mission", "mf01_001");
    sv.st.q("update player set stamina = 200", {});
    auto battle = [&](const std::vector<u8>& out) {
        Value d = out.empty() ? Value() : mp_decode(out);
        const Value* data = d.find("data");
        const Value* bp = data ? data->find("BattleParameter") : nullptr;
        return bp ? *bp : Value();
    };
    auto members = [&](const Value& bp) {
        std::vector<u64> ids;
        if (const Value* pc = bp.find("PlayerCharacter"); pc && pc->type == Value::Arr)
            for (const Value& member : pc->arr) ids.push_back(member.get_u("id"));
        return ids;
    };
    const Request restart{"MissionRestart", fids::kMissionRestart, {}, {}, {}};
    // an own character outside the party as the helper
    const u64 own = (u64)sv.st.one(
        "select uid from roster where uid not in (select uid from party_member where uid is not null and party_id = (select party_id from player)) "
        "order by uid limit 1",
        {});
    std::vector<u8> out;
    t.expect_eq(S.call({"MissionStart", fids::kMissionStart, {0, m1, 1, own, 0, 0, 0}, {}, {}}, &out), 0u, "start with an own helper");
    Value started = battle(out);
    t.expect_eq(started.get_u("rental_sub_character_id"), own, "the own helper");
    t.expect_eq((u32)sv.st.one("select helper_kind from play", {}), (u32)HelperKind::kOwn, "recorded: kind own");
    out.clear();
    t.expect_eq(S.call(restart, &out), 0u, "MissionRestart");
    Value restarted = battle(out);
    t.expect_eq(restarted.get_u("rental_sub_character_id"), own, "the restart keeps the own helper");
    t.expect_eq(members(restarted), members(started), "the same members");
    t.expect_eq(S.call({"MissionEnd", fids::kMissionEnd, {m1, 0}, {}, {}}), 0u, "MissionEnd");
    // a rental clone as member 4
    const u64 rental = rental::id_of(CharacterUid(own));
    const int64_t rentals = sv.st.one("select ifnull(sum(count), 0) from follow_rental", {});
    out.clear();
    t.expect_eq(S.call({"MissionStart", fids::kMissionStart, {0, m1, 1, 0, 0, rental, 0}, {}, {}}, &out), 0u, "start with a rental clone");
    started = battle(out);
    t.expect_eq(members(started).size(), (size_t)4, "four members");
    t.expect_eq(members(started).back(), rental, "the clone is member 4");
    t.expect_eq(sv.st.one("select ifnull(sum(count), 0) from follow_rental", {}), rentals + 1, "a rental counted");
    out.clear();
    t.expect_eq(S.call(restart, &out), 0u, "MissionRestart");
    restarted = battle(out);
    t.expect_eq(members(restarted), members(started), "the restart keeps the clone as member 4");
    t.expect_eq(sv.st.one("select ifnull(sum(count), 0) from follow_rental", {}), rentals + 1, "the restart isn't another rental");
    t.expect_eq((u32)sv.st.one("select helper_kind from play", {}), (u32)HelperKind::kRental, "still kind rental");
    // the play's party set fights again, also when the current set changed since
    const u32 set = (u32)sv.st.one("select party_id from play", {});
    sv.st.q("update player set party_id = ?", {set == 1 ? 2u : 1u});
    t.expect_eq(S.call(restart), 0u, "MissionRestart after the current set changed");
    t.expect_eq((u32)sv.st.one("select party_id from play", {}), set, "the play's set");
    t.expect_eq(S.call({"MissionFailed", fids::kMissionFailed, {}, {}, {}}), 0u, "MissionFailed");
    t.expect_eq(S.call(restart), 0xffffffffu, "nothing in progress: not handled");
}

}  // namespace
}  // namespace soa::server
