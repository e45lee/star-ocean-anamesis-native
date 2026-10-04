// Unit tests of the event module (api/events/event_missions.cpp; --selftest "events/"). Not differential
// (the server has no guest counterpart). Everything is derived from the master data at run time
// (no event names or ids are written here): the year shift of the client's master copy, the
// lists at a few calendar / clock pairs, the asset gating through an injected predicate, the
// clear / unlock chains of battle and story missions, CampaignInfo and the NPC helper.
#include <sqlite3.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <ctime>
#include <map>
#include <set>

#include "soaserver/native_test.h"
#include "soaserver/events.h"
#include "soaserver/ext.h"

namespace soa::server {
namespace {
using namespace ext;

int64_t T(const std::string& s) {
    struct tm tm = {};
    sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec);
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    tm.tm_isdst = -1;
    return (int64_t)mktime(&tm);
}
std::string F(int64_t t) {
    time_t tt = (time_t)t;
    struct tm tm;
    localtime_r(&tt, &tm);
    char b[32];
    strftime(b, sizeof b, "%Y-%m-%d %H:%M:%S", &tm);
    return b;
}
const events::AreaState* area_of(const std::vector<events::AreaState>& v, u32 id) {
    for (auto& a : v)
        if (a.id == id) return &a;
    return nullptr;
}
bool listed(const events::AreaState* a, u32 mission) {
    if (!a) return false;
    for (auto& m : a->missions)
        if (m.id == mission) return true;
    return false;
}
const events::MissionState* mission_of(const events::AreaState* a, u32 mission) {
    if (!a) return nullptr;
    for (auto& m : a->missions)
        if (m.id == mission) return &m;
    return nullptr;
}
// Every asset present (the tests decide playability themselves).
struct AllAssets {
    AllAssets() {
        events::set_asset_check([](const std::string&) { return true; });
    }
    ~AllAssets() { events::set_asset_check({}); }
};

// A dated event of the master: a term (opened in `year`) of an area whose missions have an
// unlock chain between two battle missions (first: no unlock; second: unlocked by it).
struct Chain {
    u32 area = 0, first = 0, second = 0;
    int64_t at = 0;  // a time inside the term
};
Chain find_chain(Ctx& c, int year) {
    Chain ch;
    c.m.q(
        "select t.master_event_area_id as area, t.opened_day as d from master_event_term t where substr(t.opened_day, 1, 4) = ? "
        "and t.closed_day > t.opened_day and substr(t.closed_day, 1, 4) = ? "
        "and t.master_event_area_id not in (select master_event_area_id from master_event_weekly) order by t.opened_day, t.id",
        {std::to_string(year), std::to_string(year)}, [&](const Row& r) {
            if (ch.area) return;
            u32 area = (u32)r.i("area");
            c.m.q(
                "select b.id as b, b.unlock_mission_id as a from master_event_mission b join master_event_mission a on a.id = b.unlock_mission_id "
                "where b.master_event_area_id = ? and a.master_event_area_id = ? and a.unlock_mission_id is null "
                "and a.visible_mission_id is null and b.visible_mission_id is null and a.opened_at is null and b.opened_at is null "
                "and exists (select 1 from master_mission_stage s where s.master_mission_id = a.id) "
                "and exists (select 1 from master_mission_stage s where s.master_mission_id = b.id) order by b.order_id limit 1",
                {area, area}, [&](const Row& m) {
                    ch.area = area;
                    ch.first = (u32)m.i("a");
                    ch.second = (u32)m.i("b");
                    ch.at = T(r.s("d") + " 12:00:00") + 86400;  // the day after it opens, noon
                });
        });
    return ch;
}

}  // namespace

NATIVE_TEST("events/shift") {
    t.expect_eq(events::shift_years("2020-09-10", 6), std::string("2026-09-10"), "date");
    t.expect_eq(events::shift_years("2019-12-31 23:59:59", 1), std::string("2020-12-31 23:59:59"), "date-time");
    t.expect_eq(events::shift_years("14:30:00", 6), std::string("14:30:00"), "a time stays");
    t.expect_eq(events::shift_years("", 6), std::string(""), "empty stays");
    t.expect_eq(events::shift_years("2020-02-29", 0), std::string("2020-02-29"), "no shift");
    t.expect_eq(events::year_shift(ServerTime(T("2026-09-29 21:00:00")), EventTime(T("2020-09-29 21:00:00"))), 6, "whole years");
    t.expect_eq(events::year_shift(ServerTime(T("2019-05-01 10:00:00")), EventTime(T("2019-05-01 10:00:00"))), 0, "--clock: none");
    t.expect_eq(events::window_open("2020-09-10 14:30:00", "2020-09-30 13:59:59", 6, ServerTime(T("2026-09-29 21:00:00"))), true, "inside, shifted");
    t.expect_eq(events::window_open("2020-09-10 14:30:00", "2020-09-30 13:59:59", 0, ServerTime(T("2026-09-29 21:00:00"))), false,
                "outside, unshifted");
    t.expect_eq(events::window_open("", "", 6, ServerTime(0)), true, "open-ended");
    t.expect_eq(events::shift_time(T("2020-09-29 21:00:00"), 6), T("2026-09-29 21:00:00"), "time");

    // The client's master copy (ext::ClientMaster): every dated event table moves by the years.
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        sqlite3* db = nullptr;
        sqlite3_open(":memory:", &db);
        Sql cm{db};
        cm.exec(std::string("attach '") + sqlite3_db_filename(c.m.h, "main") + "' as src");
        for (const char* tb : {"master_event_term", "master_event_area", "master_event_mission", "master_banner", "master_campaign",
                               "master_event_ranking_group", "master_world_boss", "master_event_weekly"})
            cm.exec(std::string("create table ") + tb + " as select * from src." + tb);
        cm.exec("detach src");
        std::map<u32, std::string> before;
        cm.q("select id, opened_day from master_event_term", {}, [&](const Row& r) { before[(u32)r.i("id")] = r.s("opened_day"); });
        ServerTime now(T("2026-09-29 21:00:00"));
        EventTime ev(T("2020-09-29 21:00:00"));
        client_master(db, now, ev);
        int bad = 0, n = 0;
        cm.q("select id, opened_day from master_event_term", {}, [&](const Row& r) {
            n++;
            if (r.s("opened_day") != events::shift_years(before[(u32)r.i("id")], 6)) bad++;
        });
        t.expect_eq(bad, 0, "every term moved 6 years");
        if (!n) t.fail("no terms");
        // a weekly slot has no dates: unchanged
        t.expect_eq(cm.one("select count(*) from master_event_weekly where opened_time glob '[0-9][0-9][0-9][0-9]-*'", {}), (int64_t)0,
                    "weekly untouched");
        // the ranking group's dates too (the extras module's windows follow the same shift)
        cm.q("select id, closed_at from master_event_ranking_group where closed_at is not null and closed_at != '' limit 1", {}, [&](const Row& r) {
            std::string orig = (std::string) "";
            c.m.q("select closed_at from master_event_ranking_group where id = ?", {r.i("id")}, [&](const Row& o) { orig = o.s("closed_at"); });
            t.expect_eq(r.s("closed_at"), events::shift_years(orig, 6), "ranking group moved");
        });
        sqlite3_close(db);
    });
    if (!ran) fprintf(stderr, "    (no scratch server; client-master part skipped)\n");
}

// The lists at a calendar date, with and without the client being years ahead.
NATIVE_TEST("events/lists") {
    AllAssets all;
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        Chain ch = find_chain(c, 2020);
        if (!ch.area) return t.fail("no 2020 event with a two-mission unlock chain in the master");
        for (int years : {0, 6}) {
            int64_t ev = ch.at, now = events::shift_time(ch.at, years);
            auto v = events::open_areas(c, ServerTime(now), EventTime(ev));
            const events::AreaState* a = area_of(v, ch.area);
            if (!a) {
                t.fail("area %u not open at %s (+%d years)", ch.area, F(ev).c_str(), years);
                continue;
            }
            t.expect_eq(listed(a, ch.first), true, "the chain's first mission listed");
            t.expect_eq(listed(a, ch.second), false, "the second not yet");
            // Before the service (no term of any year) the area isn't there.
            int64_t before = T("2015-06-01 12:00:00");
            t.expect_eq(area_of(events::open_areas(c, ServerTime(events::shift_time(before, years)), EventTime(before)), ch.area) == nullptr, true,
                        "closed before any term");
        }
        // The list value: EventArea / EventMission keyed by the area id as a string.
        Value l = events::active_event_mission_list(c, ServerTime(ch.at), EventTime(ch.at));
        const Value* ea = l.find("EventArea");
        const Value* em = l.find("EventMission");
        if (!ea || !em) return t.fail("no EventArea / EventMission");
        const Value* info = ea->find(std::to_string(ch.area));
        if (!info) return t.fail("area missing from EventArea");
        t.expect_eq(info->find("mission_ct") != nullptr && info->find("is_start_bighunt") != nullptr, true, "CAreaInfo keys");
        const Value* ms = em->find(std::to_string(ch.area));
        t.expect_eq(ms && ms->type == Value::Arr && !ms->arr.empty(), true, "missions listed");
        if (ms && !ms->arr.empty()) t.expect_eq(ms->arr[0].find("is_clear") != nullptr, true, "CMissionElementInfo keys");
    });
    if (!ran) fprintf(stderr, "    (no scratch server; skipped)\n");
}

// A weekly slot follows the weekday of the client's clock.
NATIVE_TEST("events/weekly") {
    AllAssets all;
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        u32 area = 0;
        int week = -1;
        c.m.q(
            "select master_event_area_id as a, week_id as w from master_event_weekly where opened_time = '00:00:00' and closed_time = '23:59:59' "
            "and master_event_area_id not in (select master_event_area_id from master_event_term) order by id limit 1",
            {}, [&](const Row& r) { area = (u32)r.i("a"), week = (int)r.i("w"); });
        if (!area) return;  // no all-day weekly slot in this master
        std::set<int> days;
        c.m.q("select week_id from master_event_weekly where master_event_area_id = ?", {area},
              [&](const Row& r) { days.insert((int)r.i("week_id")); });
        // a date of that weekday, and one of a weekday the area has no slot on
        int64_t d = T("2026-09-27 12:00:00");  // a Sunday
        int64_t on = d + 86400 * week, off = 0;
        for (int k = 0; k < 7; k++)
            if (!days.count(k)) off = d + 86400 * k;
        auto v = events::open_areas(c, ServerTime(on), EventTime(events::shift_time(on, -6)));
        t.expect_eq(area_of(v, area) != nullptr, true, "open on its weekday");
        if (off) {
            // (the list is sent a day ahead: the day before a slot the area is listed too)
            bool next_day_slot = days.count((int)(((off - d) / 86400 + 1) % 7)) != 0;
            auto v2 = events::open_areas(c, ServerTime(off), EventTime(events::shift_time(off, -6)));
            t.expect_eq(area_of(v2, area) != nullptr, next_day_slot, "not open on another weekday");
        }
        t.expect_eq(events::area_scheduled(c.m, area, 0, ServerTime(on)), true, "scheduled");
    });
    if (!ran) fprintf(stderr, "    (no scratch server; skipped)\n");
}

// Missions whose files are missing are hidden; an area with none left isn't listed; a hidden
// mission doesn't block what it unlocks.
NATIVE_TEST("events/asset-gating") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        Chain ch = find_chain(c, 2020);
        if (!ch.area) return t.fail("no chain");
        std::set<std::string> first_maps;
        c.m.q("select master_map_id_label from master_mission_stage where master_mission_id = ?", {ch.first},
              [&](const Row& r) { first_maps.insert("BG/" + r.s("master_map_id_label") + ".aaf"); });
        std::set<std::string> second_maps;
        c.m.q("select master_map_id_label from master_mission_stage where master_mission_id = ?", {ch.second},
              [&](const Row& r) { second_maps.insert("BG/" + r.s("master_map_id_label") + ".aaf"); });
        bool shared = false;
        for (auto& m : first_maps) shared |= second_maps.count(m) != 0;
        events::set_asset_check([&](const std::string& rel) { return !first_maps.count(rel); });
        auto v = events::open_areas(c, ServerTime(ch.at), EventTime(ch.at));
        const events::AreaState* a = area_of(v, ch.area);
        t.expect_eq(listed(a, ch.first), false, "a mission with a missing map is hidden");
        if (!shared) t.expect_eq(listed(a, ch.second), true, "what it unlocks is reachable");
        t.expect_eq(events::mission_playable(c.m, ch.first), false, "not playable");
        // Nothing present: the area disappears (its story missions aside).
        events::set_asset_check([](const std::string&) { return false; });
        v = events::open_areas(c, ServerTime(ch.at), EventTime(ch.at));
        a = area_of(v, ch.area);
        bool only_story = true;
        if (a)
            for (auto& m : a->missions) only_story &= c.m.one("select count(*) from master_mission_stage where master_mission_id = ?", {m.id}) == 0;
        t.expect_eq(only_story, true, "no battle mission without its files");
        // A missing enemy model counts like a missing map.
        std::string model;
        c.m.q(
            "select p.asf as asf from master_mission_stage s join master_enemy_party ep on ep.id = s.master_enemy_party_id "
            "join master_enemy_base_parameter b on b.id = ep.member1_id join master_person p on p.id = b.master_person_id "
            "where s.master_mission_id = ? limit 1",
            {ch.first}, [&](const Row& r) { model = "Character/" + r.s("asf") + ".asf"; });
        if (!model.empty()) {
            events::set_asset_check([&](const std::string& rel) { return rel != model; });
            t.expect_eq(events::mission_playable(c.m, ch.first), false, "missing enemy model");
        }
        events::set_asset_check([](const std::string&) { return true; });
        t.expect_eq(events::mission_playable(c.m, ch.first), true, "all present");
        // A story mission needs its script and talk file.
        u32 story = 0;
        std::string script;
        c.m.q("select id, talk_event_id_label as l from master_event_mission where talk_event_id is not null order by id limit 1", {},
              [&](const Row& r) { story = (u32)r.i("id"), script = "Script/" + r.s("l") + ".msgp"; });
        if (story) {
            t.expect_eq(events::mission_playable(c.m, story), true, "story with its script");
            events::set_asset_check([&](const std::string& rel) { return rel != script; });
            t.expect_eq(events::mission_playable(c.m, story), false, "story without its script");
        }
    });
    events::set_asset_check({});
    if (!ran) fprintf(stderr, "    (no scratch server; skipped)\n");
}

// Clears: a won battle (the core MissionEnd) unlocks the next mission; a story scene's end
// (end_mission_talk's clear_story) clears a story mission and unlocks what follows it.
NATIVE_TEST("events/clear-chain") {
    AllAssets all;
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        Chain ch = find_chain(c, 2020);
        if (!ch.area) return t.fail("no chain");
        c.st.q("update player set stamina = 999", {});
        Request s;
        s.method = "MissionStart";
        s.ints = {1, ch.first, 1, 0, 0, 0, 0};
        Value d = c.core_mission(s, nullptr);
        t.expect_eq(d.type == Value::Map && d.find("MissionParameter") != nullptr, true, "event mission started");
        Request e;
        e.method = "MissionEnd";
        e.ints = {ch.first, 0};
        c.core_mission(e, nullptr);
        auto v = events::open_areas(c, ServerTime(ch.at), EventTime(ch.at));
        const events::AreaState* a = area_of(v, ch.area);
        const events::MissionState* m1 = mission_of(a, ch.first);
        t.expect_eq(m1 && m1->clear && !m1->is_new, true, "first mission CLEAR");
        t.expect_eq(listed(a, ch.second), true, "the second unlocked");

        // A story chain: a story mission with no unlock, and one it unlocks.
        u32 st1 = 0, st2 = 0, sarea = 0;
        c.m.q(
            "select b.id as b, a.id as a, a.master_event_area_id as area from master_event_mission b join master_event_mission a on a.id = b.unlock_mission_id "
            "where a.talk_event_id is not null and b.talk_event_id is not null and a.unlock_mission_id is null order by a.id limit 1",
            {}, [&](const Row& r) { st1 = (u32)r.i("a"), st2 = (u32)r.i("b"), sarea = (u32)r.i("area"); });
        if (!st1) return t.fail("no story chain");
        t.expect_eq(events::clear_story(c, st1), true, "story cleared");
        t.expect_eq(c.st.one("select cleared from mission where mission_id = ?", {st1}), (int64_t)1, "recorded");
        t.expect_eq(events::clear_story(c, ch.first), false, "a battle mission isn't a story");
        // Its area at a date of one of its terms: the next story is listed.
        std::string day;
        c.m.q("select opened_day from master_event_term where master_event_area_id = ? order by opened_day limit 1", {sarea},
              [&](const Row& r) { day = r.s("opened_day"); });
        if (day.empty()) return;  // a weekly-only area
        int64_t at = T(day + " 12:00:00") + 86400;
        auto sv = events::open_areas(c, ServerTime(at), EventTime(at));
        a = area_of(sv, sarea);
        t.expect_eq(listed(a, st2), true, "the next story unlocked");
        t.expect_eq(mission_of(a, st1) && mission_of(a, st1)->clear, true, "story CLEAR");
    });
    if (!ran) fprintf(stderr, "    (no scratch server; skipped)\n");
}

// CampaignInfo: the campaigns running at the event calendar, their windows in the client's years.
NATIVE_TEST("events/campaign-info") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        u32 id = 0;
        std::string od, ot, cd;
        c.m.q(
            "select id, opened_day, opened_time, closed_day from master_campaign where substr(opened_day, 1, 4) = '2020' and closed_day > opened_day "
            "and week_id = 7 order by id limit 1",
            {}, [&](const Row& r) { id = (u32)r.i("id"), od = r.s("opened_day"), ot = r.s("opened_time"), cd = r.s("closed_day"); });
        if (!id) return;
        int64_t ev = T(od + " " + ot) + 3600, now = events::shift_time(ev, 6);
        Value l = events::campaign_info(c, ServerTime(now), EventTime(ev));
        const Value* e = nullptr;
        for (auto& x : l.arr)
            if (x.find("id") && x.get_u("id") == id) e = &x;
        if (!e) return t.fail("campaign %u not running", id);
        t.expect_eq(e->find("opened_at")->s, events::shift_years(od, 6) + " " + ot, "opened_at in the client's years");
        t.expect_eq(e->find("type_id") != nullptr && e->find("master_mission_model_type") != nullptr, true, "CCampaignInfo keys");
        // a year later nothing of it
        Value l2 = events::campaign_info(c, ServerTime(now + 366 * 86400), EventTime(ev + 366 * 86400));
        bool still = false;
        for (auto& x : l2.arr) still |= x.get_u("id") == id;
        t.expect_eq(still, false, "over later");
    });
    if (!ran) fprintf(stderr, "    (no scratch server; skipped)\n");
}

// An event mission's master_mission_npc rows are helper candidates: the player's party fights and
// the picked NPC joins as the 4th member; without a pick, no NPC (b: CreateRentalListAuto).
NATIVE_TEST("events/npc-helper") {
    AllAssets all;
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        u32 mission = 0, npc_row = 0, role = 0;
        c.m.q(
            "select n.master_mission_id as m, n.id as id, b.master_role_id as role from master_mission_npc n join master_event_mission e on e.id = n.master_mission_id "
            "join master_npc_base_parameter b on b.id = n.master_npc_id where e.ticket_item_id is null and e.vanish_item_id is null order by n.id limit 1",
            {}, [&](const Row& r) { mission = (u32)r.i("m"), npc_row = (u32)r.i("id"), role = (u32)r.i("role"); });
        if (!mission) return;
        c.st.q("update player set stamina = 999", {});
        auto members = [&](const Value& d) -> std::vector<u32> {
            std::vector<u32> v;
            const Value* bp = d.find("BattleParameter");
            const Value* pc = bp ? bp->find("PlayerCharacter") : nullptr;
            if (pc)
                for (auto& p : pc->arr) v.push_back((u32)p.get_u("master_role_id"));
            return v;
        };
        Request s;
        s.method = "MissionStart";
        s.ints = {1, mission, 0, 0, 0, 0, 0};
        auto own = members(c.core_mission(s, nullptr));
        if (own.empty()) return t.fail("no party");
        t.expect_eq(std::find(own.begin(), own.end(), role) == own.end() || own.size() > 1, true, "no NPC party without a pick");
        Request f;
        f.method = "MissionFailed";
        f.ints = {1, mission};
        c.core_mission(f, nullptr);
        s.ints = {1, mission, 1, 0, npc_row, 0, 0};
        auto with = members(c.core_mission(s, nullptr));
        t.expect_eq(with.size(), std::min<size_t>(own.size(), 3) + 1, "party + the NPC");
        if (!with.empty()) t.expect_eq(with.back(), role, "the picked NPC is the 4th member");
    });
    if (!ran) fprintf(stderr, "    (no scratch server; skipped)\n");
}

}  // namespace soa::server
