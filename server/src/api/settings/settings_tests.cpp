// Unit tests of the settings module (api/settings/; run in --selftest; not differential: the server
// has no guest counterpart), on a scratch server seeded from the test seed save, against the 3.7.0
// master data. Test names are their seeds (testing.h): settings/...
#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "api/settings/config.h"
#include "soa/chash32.h"
#include "soaserver/ext.h"
#include "soaserver/native_test.h"
#include "testing/module_test.h"

namespace soa::server {
namespace {
using namespace ext;
using module_test::player_load_data;

// Calls `method`'s registered handler with these arguments (module_test::call has no strings).
Value call_data(Ctx& ctx, const char* method, std::vector<u64> ints, std::vector<std::string> strs = {}, std::vector<std::vector<u64>> vecs = {}) {
    const Handler* handler = find(method);
    if (!handler) return Value();
    Request req;
    req.method = method;
    req.ints = std::move(ints);
    req.strs = std::move(strs);
    req.vecs = std::move(vecs);
    std::vector<u8> b = (*handler)(ctx, req);
    if (b.empty()) return Value();
    Value v = mp_decode(b);
    const Value* d = v.find("data");
    return d ? *d : Value();
}

// ConfigInfoList as {master_config_id: value}.
std::map<u32, std::string> config_values(const Value& data) {
    std::map<u32, std::string> out;
    const Value* list = data.find("ConfigInfoList");
    if (!list) return out;
    for (const Value& info : list->arr) {
        const Value* id = info.find("master_config_id");
        const Value* value = info.find("value");
        if (id && value) out[(u32)id->u] = value->s;
    }
    return out;
}

// The options (docs/server-rules.md#settings): GetConfig lists every master_config row with the
// master's defaults; UpdateConfig stores one (answered as ConfigInfo) and every later GetConfig and
// player load (Login, GetPlayer) carries it; config_on reads it as the client does ("true"); an
// unknown id is refused; ResetConfig brings back the defaults.
NATIVE_TEST("settings/config") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& ctx) {
        ctx.st.exec("begin");
        u32 code = 0;
        ctx.test.on_refuse = [&](u32 e) { code = e; };
        const u32 storage = chash32(settings::kOneTimeStorage);
        t.expect_eq(storage, (u32)ctx.m.one("select id from master_config where id_label = 'is_one_time_storage'", {}),
                    "the label's CHash32 is its id");
        std::map<u32, std::string> defaults;
        ctx.m.q("select id, value from master_config", {}, [&](const Row& r) { defaults[(u32)r.i("id")] = r.s("value"); });
        t.expect_eq(defaults.size() > 0, true, "master_config has rows");
        t.expect_eq(config_values(call_data(ctx, "GetConfig", {})) == defaults, true, "GetConfig: the master's defaults");
        t.expect_eq(config_values(player_load_data(ctx, "Login")) == defaults, true, "the player load: the defaults");
        t.expect_eq(settings::config_on(ctx, settings::kOneTimeStorage), defaults[storage] == "true", "config_on: the default");

        Value updated = call_data(ctx, "UpdateConfig", {storage, 4}, {"true"});
        const Value* info = updated.find("ConfigInfo");
        if (!info) return t.fail("UpdateConfig answers no ConfigInfo");
        t.expect_eq((u32)info->get_u("master_config_id"), storage, "ConfigInfo.master_config_id");
        t.expect_eq(info->find("value") ? info->find("value")->s : std::string(), std::string("true"), "ConfigInfo.value");
        t.expect_eq((u32)info->get_u("type"), 4u, "ConfigInfo.type");
        t.expect_eq(ctx.st.one("select count(*) from config", {}), (int64_t)1, "stored");
        t.expect_eq(config_values(call_data(ctx, "GetConfig", {}))[storage], std::string("true"), "GetConfig: the player's value");
        t.expect_eq(config_values(player_load_data(ctx, "GetPlayer"))[storage], std::string("true"), "the player load: the player's value");
        t.expect_eq(settings::config_on(ctx, settings::kOneTimeStorage), true, "config_on: on");
        t.expect_eq(settings::config_on(ctx, storage), true, "config_on by id: on");
        call_data(ctx, "UpdateConfig", {storage, 4}, {"false"});
        t.expect_eq(settings::config_on(ctx, settings::kOneTimeStorage), false, "config_on: off again");
        t.expect_eq(ctx.st.one("select count(*) from config", {}), (int64_t)1, "one row per option");

        code = 0;
        call_data(ctx, "UpdateConfig", {12345, 4}, {"true"});
        t.expect_eq(code, 10403u, "an unknown id is refused");
        t.expect_eq(settings::config_on(ctx, 12345u), false, "an unknown option is off");

        call_data(ctx, "UpdateConfig", {storage, 4}, {"true"});
        t.expect_eq(config_values(call_data(ctx, "ResetConfig", {})) == defaults, true, "ResetConfig: the defaults");
        t.expect_eq(ctx.st.one("select count(*) from config", {}), (int64_t)0, "ResetConfig deletes the rows");
        t.expect_eq(settings::config_on(ctx, settings::kOneTimeStorage), defaults[storage] == "true", "config_on: the default again");
    });
    if (!ran) t.fail("no scratch server");
}

// The birth month (docs/server-rules.md#account): GetBirthYearMonth is refused with 10009 until
// UpdateBirthYearMonth stores one ("YYYY-MM", the client's ranges; anything else refused), then
// answers it as Birth.
NATIVE_TEST("settings/birth-year-month") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& ctx) {
        ctx.st.exec("begin");
        u32 code = 0;
        ctx.test.on_refuse = [&](u32 e) { code = e; };
        call_data(ctx, "GetBirthYearMonth", {});
        t.expect_eq(code, 10009u, "never entered: 10009");
        for (const char* bad : {"1899-12", "2101-01", "1990-00", "1990-13", "199005", ""}) {
            code = 0;
            call_data(ctx, "UpdateBirthYearMonth", {}, {bad});
            t.expect_eq(code, 10403u, bad);
        }
        t.expect_eq(ctx.st.one("select count(*) from player where birth_year is not null", {}), (int64_t)0, "nothing stored");
        code = 0;
        Value updated = call_data(ctx, "UpdateBirthYearMonth", {}, {"1990-05"});
        t.expect_eq(code, 0u, "accepted");
        const Value* birth = updated.find("Birth");
        t.expect_eq(birth ? (u32)birth->get_u("year") : 0u, 1990u, "Birth.year");
        t.expect_eq(birth ? (u32)birth->get_u("month") : 0u, 5u, "Birth.month");
        Value got = call_data(ctx, "GetBirthYearMonth", {});
        t.expect_eq(code, 0u, "known now");
        birth = got.find("Birth");
        t.expect_eq(birth ? (u32)birth->get_u("year") * 100 + (u32)birth->get_u("month") : 0u, 199005u, "GetBirthYearMonth answers it");
        call_data(ctx, "UpdateBirthYearMonth", {}, {"2001-11"});
        t.expect_eq(ctx.st.one("select birth_year * 100 + birth_month from player", {}), (int64_t)200111, "entered again: replaced");
    });
    if (!ran) t.fail("no scratch server");
}

// ReadExpirationInfo and SendGuideInformation (docs/server-rules.md#account): accepted, nothing
// stored; the guide list answered is empty.
NATIVE_TEST("settings/read-marks") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& ctx) {
        ctx.st.exec("begin");
        u32 code = 0;
        ctx.test.on_refuse = [&](u32 e) { code = e; };
        const u64 expiration = (u64)ctx.m.one("select id from master_expiration_information order by id limit 1", {});
        Value read = call_data(ctx, "ReadExpirationInfo", {}, {}, {{expiration, 7}});
        t.expect_eq(code, 0u, "ReadExpirationInfo accepted");
        t.expect_eq(read.find("Time") != nullptr, true, "ReadExpirationInfo answered");
        t.expect_eq(read.find("ExpirationInfoList") == nullptr, true, "no ExpirationInfoList");
        const u32 guide = (u32)ctx.m.one("select id from master_guide_information order by id limit 1", {});
        Value sent = call_data(ctx, "SendGuideInformation", {guide});
        t.expect_eq(code, 0u, "SendGuideInformation accepted");
        const Value* list = sent.find("GuideInformationInfoList");
        t.expect_eq(list && list->type == Value::Arr && list->arr.empty(), true, "an empty guide list");
    });
    if (!ran) t.fail("no scratch server");
}

// The scenario library (docs/server-rules.md#scenario-library): the cleared missions (the core's
// `mission` clears and campaign_clear) of the episode type asked for that belong to a chapter, in
// id order; others' and uncleared ones aren't listed.
NATIVE_TEST("settings/scenario-library") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& ctx) {
        ctx.st.exec("begin");
        ctx.st.q("delete from campaign_last", {});
        ctx.st.q("delete from campaign_clear", {});
        ctx.st.q("update mission set cleared = 0", {});
        auto listed = [&](u32 episode) {
            std::vector<u32> out;
            Value d = call_data(ctx, "GetScenarioLibraryInfoList", {episode});
            if (const Value* list = d.find("WorldMapScenarioLibraryInfoList"))
                for (const Value& v : list->arr) out.push_back((u32)v.u);
            return out;
        };
        // a world map story mission of one chapter, another of another episode, Episode 1's
        auto pick = [&](const char* table, const char* label_like) {
            return (u32)ctx.m.one(std::string("select w.id from ") + table +
                                      " w join master_scenario_library s on s.id = w.master_scenario_library_id "
                                      "where s.id_label like ? order by w.id limit 1",
                                  {label_like});
        };
        const u32 ep_main = (u32)ctx.m.one("select episode_type_id from master_scenario_library where id_label = 'library_main_story_01'", {});
        const u32 ep3 = (u32)ctx.m.one("select episode_type_id from master_scenario_library where id_label = 'library_EP3_main_story_01'", {});
        const u32 ep1 = (u32)ctx.m.one("select episode_type_id from master_scenario_library where id_label = 'library_EP1_main_story_01'", {});
        const u32 main01 = pick("master_world_map_mission", "library_main_story_01");
        const u32 main02 = pick("master_world_map_mission", "library_main_story_02");
        const u32 ep3_01 = pick("master_world_map_mission", "library_EP3_main_story_01");
        const u32 ep1_01 = pick("master_mission", "library_EP1_main_story_01");
        if (!main01 || !main02 || !ep3_01 || !ep1_01 || !ep_main || !ep3 || !ep1) return t.fail("the master's library missions");
        const u32 no_chapter = (u32)ctx.m.one(
            "select id from master_world_map_mission where master_scenario_library_id is null or master_scenario_library_id = 0 order by id limit 1",
            {});
        t.expect_eq(listed(ep_main).empty(), true, "nothing cleared: empty");
        ctx.st.q("insert into campaign_clear (mission_id) values (?)", {main02});
        ctx.st.q("insert into campaign_clear (mission_id) values (?)", {ep3_01});
        ctx.st.q("insert into campaign_clear (mission_id) values (?)", {ep1_01});
        if (no_chapter) ctx.st.q("insert into campaign_clear (mission_id) values (?)", {no_chapter});
        ctx.st.q(
            "insert into mission (mission_id, cleared, play_count, clear_count) values (?, 1, 1, 1) "
            "on conflict (mission_id) do update set cleared = 1",
            {main01});
        t.expect_eq(listed(ep_main) == std::vector<u32>{std::min(main01, main02), std::max(main01, main02)}, true, "the main story's two");
        t.expect_eq(listed(ep3) == std::vector<u32>{ep3_01}, true, "Episode 3's");
        t.expect_eq(listed(ep1) == std::vector<u32>{ep1_01}, true, "Episode 1's (master_mission)");
        t.expect_eq(listed(12345).empty(), true, "another episode type: empty");
    });
    if (!ran) t.fail("no scratch server");
}

}  // namespace
}  // namespace soa::server
