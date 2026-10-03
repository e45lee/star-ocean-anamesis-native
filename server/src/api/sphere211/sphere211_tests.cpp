// Unit tests of the Sphere 211 module (api/sphere211/; --selftest "sphere211/"). Not
// differential (the server has no guest counterpart): the season pick and its client-master date
// shift, the floor / cell lottery (seeded, so repeatable), the missing-map skip (through an
// injected asset predicate, never a list of names), the sphere stamina on the server clock, and a
// dive's state transitions on a scratch server seeded from the test seed save.
#include <sqlite3.h>

#include <ctime>
#include <map>
#include <set>
#include <tuple>

#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "api/sphere211/sphere211.h"

namespace soa::server {
namespace {
using namespace ext;

Value call(Ctx& c, const char* method, std::vector<u64> ints) {
    const Handler* h = find(method);
    if (!h) return Value();
    Request r;
    r.method = method;
    r.ints = std::move(ints);
    std::vector<u8> b = (*h)(c, r);
    if (b.empty()) return Value();
    Value v = mp_decode(b);
    const Value* d = v.find("data");
    return d ? *d : Value();
}
u64 num(const Value* v) { return !v ? 0 : v->type == Value::Int ? (u64)v->i : v->u; }
u64 num(const Value& d, const char* a, const char* b) {
    const Value* x = d.find(a);
    return x ? num(x->find(b)) : 0;
}
// The cells of a response: asset id -> {mission box id, overwrite enemy level, can_play, cleared}.
struct Cell {
    u32 box = 0, ov = 0;
    bool can_play = false, cleared = false;
};
std::map<u32, Cell> cells(const Value& d) {
    std::map<u32, Cell> m;
    const Value* v = d.find("Sphere211FloorAssetInfoMap");
    if (!v) return m;
    for (auto& [k, e] : v->map) {
        Cell x;
        x.box = (u32)num(e.find("master_sphere211_mission_box_id"));
        x.ov = (u32)num(e.find("overwrite_enemy_level"));
        x.can_play = e.find("can_play") && e.find("can_play")->b;
        x.cleared = e.find("is_cleared") && e.find("is_cleared")->b;
        m[(u32)std::stoul(k)] = x;
    }
    return m;
}
// Local "YYYY-MM-DD HH:MM:SS" <-> seconds, as the module and the master data use them.
std::string fmt(int64_t t) {
    time_t tt = (time_t)t;
    struct tm tm;
    localtime_r(&tt, &tm);
    char b[32];
    strftime(b, sizeof b, "%Y-%m-%d %H:%M:%S", &tm);
    return b;
}
struct SeasonRow {
    u32 id;
    int64_t a, b;
};
std::vector<SeasonRow> seasons(Ctx& c) {
    std::vector<SeasonRow> v;
    c.m.q("select id, opened_at, closed_at from master_sphere211 order by opened_at", {},
          [&](const Row& r) { v.push_back({(u32)r.i("id"), c.parse_time(r.s("opened_at")), c.parse_time(r.s("closed_at"))}); });
    return v;
}

// The maps (BG/<label>) of a mission's stages.
std::set<std::string> maps_of(Ctx& c, u32 mission) {
    std::set<std::string> s;
    c.m.q("select master_map_id_label from master_mission_stage where master_mission_id = ?", {mission},
          [&](const Row& r) { s.insert(r.s("master_map_id_label")); });
    return s;
}

}  // namespace

// Season selection and the client-master shift.
NATIVE_TEST("sphere211/season") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        auto ss = seasons(c);
        if (ss.size() < 2) return t.fail("no seasons in master_sphere211");
        int64_t clock = c.parse_time("2026-09-29 12:00:00");
        // (a) inside a season: that season, dates moved by clock - ev
        for (auto& s : ss) {
            int64_t ev = s.a + 86400;
            auto p = sphere211::pick_season(c.m, clock, ev);
            if (p.id != s.id) t.fail("ev %s: season %u, want %u", fmt(ev).c_str(), p.id, s.id);
            if (p.shift != clock - ev) t.fail("season %u: shift %lld", s.id, (long long)p.shift);
        }
        // (d) past the last season: the last one, moved by whole periods so its window covers ev
        const SeasonRow& last = ss.back();
        int64_t period = last.b - last.a + 1;
        for (int64_t ev : {last.b + 1, last.b + period, last.b + period + 1, last.b + 7 * period + 12345, last.b + (int64_t)1000 * 86400}) {
            auto p = sphere211::pick_season(c.m, clock, ev);
            if (p.id != last.id) t.fail("past the end: season %u", p.id);
            int64_t moved = p.shift - (clock - ev);  // the whole-period part
            if (moved % period) t.fail("shift not whole periods (%lld)", (long long)moved);
            if (!(last.a + moved <= ev && ev <= last.b + moved)) t.fail("ev %s not inside the repeated window", fmt(ev).c_str());
        }
        // (d) before the first season: the season of the same date a year later (the seasons span
        // one year), so no day of the replayed calendar is without a season
        for (auto& s : ss) {
            struct tm tm;
            time_t tt = (time_t)(s.a + 86400);
            localtime_r(&tt, &tm);
            tm.tm_year -= 1;
            tm.tm_isdst = -1;
            int64_t ev = (int64_t)mktime(&tm);
            if (ev >= ss.front().a) continue;
            auto p = sphere211::pick_season(c.m, clock, ev);
            if (p.id != s.id) t.fail("a year before season %u: season %u", s.id, p.id);
            if (p.cycle) t.fail("a year before season %u: cycle %u", s.id, p.cycle);
            int64_t moved = (clock - ev) - p.shift;  // the date a year later: about one year less shift
            if (moved < 365 * 86400 - 7200 || moved > 366 * 86400 + 7200) t.fail("a year before season %u: moved %lld s", s.id, (long long)moved);
        }
        // (d) the annual gap after the last season is still the last season (cycle 0); a season
        // length past that, the repeats count cycles
        t.expect_eq(sphere211::pick_season(c.m, clock, last.b + 3600).cycle, 0u, "the day after the last season: cycle 0");
        u32 cyc = sphere211::pick_season(c.m, clock, last.b + 3 * period + 3600).cycle;
        t.expect_eq(cyc, 4u, "three season lengths past the end: cycle 4");

        // The client's master copy (ext::ClientMaster): the picked season's dates cover the clock.
        sqlite3* db = nullptr;
        sqlite3_open(":memory:", &db);
        Sql cm{db};
        cm.exec(std::string("attach '") + sqlite3_db_filename(c.m.h, "main") + "' as src");
        cm.exec("create table master_sphere211 as select * from src.master_sphere211");
        cm.exec("detach src");
        int64_t ev = last.b + 3 * period + 86400;
        client_master(db, clock, ev);
        std::string o, cl;
        cm.q("select opened_at, closed_at from master_sphere211 where id = ?", {last.id}, [&](const Row& r) {
            o = r.s("opened_at");
            cl = r.s("closed_at");
        });
        if (!(c.parse_time(o) <= clock && clock <= c.parse_time(cl)))
            t.fail("client master: season %u %s .. %s doesn't cover the clock %s", last.id, o.c_str(), cl.c_str(), fmt(clock).c_str());
        // the other seasons stay as they were
        t.expect_eq(
            cm.one("select count(*) from master_sphere211 m where id != ? and opened_at = (select opened_at from master_sphere211 where id = m.id)",
                   {last.id}),
            (int64_t)ss.size() - 1, "other seasons untouched");
        sqlite3_close(db);

        // Through the APIs: the player load and GetSphere211Info name the season of the calendar.
        c.st.exec("begin");
        int64_t evc = ss[1].a + 3600;
        c.test.now = [&] { return clock; };
        c.test.event_now = [&] { return evc; };
        Value d = Value::object();
        Request lr;
        lr.method = "Login";
        player_load(c, lr, d);
        t.expect_eq((u32)num(d.find("Sphere211CurrentId")), ss[1].id, "player load: Sphere211CurrentId");
        t.expect_eq(d.find("FooterMissionInfo") && d.find("FooterMissionInfo")->find("is_open_extra_dungeon") &&
                        d.find("FooterMissionInfo")->find("is_open_extra_dungeon")->b,
                    true, "extra dungeon open");
        Value info = call(c, "GetSphere211Info", {});
        t.expect_eq((u32)num(info.find("Sphere211CurrentId")), ss[1].id, "GetSphere211Info season");
        // (d) a season change ends the dive: its best floor becomes the end result, a new dive
        // begins; (b) without a battle won the player isn't ranked (rank 0, no reward)
        evc = ss[2].a + 3600;
        info = call(c, "GetSphere211Info", {});
        t.expect_eq((u32)num(info.find("Sphere211CurrentId")), ss[2].id, "next season");
        t.expect_eq((u32)num(info, "Sphere211EndResult", "previous_season_id"), ss[1].id, "end result: previous season");
        t.expect_eq((u32)num(info, "Sphere211EndResult", "floor_num"), 1u, "end result: best floor");
        t.expect_eq((u32)num(info, "Sphere211EndResult", "rank"), 0u, "end result: no battle won, not ranked");
        t.expect_eq((u32)num(info, "Sphere211FloorInfo", "floor_level"), 1u, "new dive on floor 1");
        // (d) the result goes out once
        info = call(c, "GetSphere211Info", {});
        t.expect_eq((u32)num(info, "Sphere211EndResult", "previous_season_id"), 0u, "end result sent once");
        // a battle won in the season: rank 1 and the season's rank-1 ranking reward (a), into the items
        c.st.q("insert or replace into sphere_meta values ('season_wins', 2)", {});
        u32 group = (u32)c.m.one("select coalesce(nullif(master_sphere211_ranking_reward_id, ''), 0) from master_sphere211 where id = ?", {ss[2].id});
        u32 set_id = 0, set_type = 0;
        c.m.q(
            "select content_type, content_id from master_sphere211_ranking_reward where ranking_reward_group_id = ? order by required_ranking limit 1",
            {group}, [&](const Row& r) {
                set_type = (u32)r.i("content_type");
                set_id = (u32)r.i("content_id");
            });
        std::map<u32, int64_t> want;  // stack item -> count expected after the grant
        if (set_type == 99)
            c.m.q("select content_type, content_id, num from master_item_set where item_set_id = ?", {set_id}, [&](const Row& r) {
                if (r.i("content_type") == 8 || r.i("content_type") == 9) {
                    u32 id = (u32)r.i("content_id");
                    if (!want.count(id)) want[id] = c.st.one("select ifnull(sum(count), 0) from stock where master_item_id = ?", {id});
                    want[id] += r.i("num");
                }
            });
        if (want.empty()) t.fail("season %u: no stack items in its rank-1 reward (group %u)", ss[2].id, group);
        evc = ss[3].a + 3600;
        info = call(c, "GetSphere211Info", {});
        t.expect_eq((u32)num(info, "Sphere211EndResult", "previous_season_id"), ss[2].id, "end result: season 3");
        t.expect_eq((u32)num(info, "Sphere211EndResult", "rank"), 1u, "a battle won: rank 1 (local ranking)");
        t.expect_eq(info.find("StockItem") != nullptr, true, "the reward's items are sent");
        for (auto& [id, n] : want)
            t.expect_eq(c.st.one("select ifnull(sum(count), 0) from stock where master_item_id = ?", {id}), std::min<int64_t>(n, 100000000),
                        "ranking reward item granted");
        // (d) the repeated last season: each cycle is a new season
        evc = last.b + 3 * period + 3600;
        call(c, "GetSphere211Info", {});
        c.st.q("insert or replace into sphere_meta values ('season_wins', 1)", {});
        evc += period;
        info = call(c, "GetSphere211Info", {});
        t.expect_eq((u32)num(info.find("Sphere211CurrentId")), last.id, "still the last season");
        t.expect_eq((u32)num(info, "Sphere211EndResult", "previous_season_id"), last.id, "a new cycle ends the season");
        t.expect_eq((u32)num(info, "Sphere211EndResult", "rank"), 1u, "the cycle's rank");
        c.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master (data/basmaster-3.7.0.sqlite3) and the test seed save (port/server-data/test-seed.xml)");
}

// The floor and cell lottery: repeatable for a seed, cells as the map template lists them, each
// battle from the cell's box group with the cell's lottery type; maps missing -> mission skipped.
NATIVE_TEST("sphere211/lottery") {
    u64 seed = t.rand_u64();
    using Snapshot = std::vector<std::tuple<u32, u32, u32, u32>>;  // asset, box, mission, enemy level
    auto run = [&](std::vector<Snapshot>& out) {
        return with_scratch_server(seed, [&](Ctx& c) {
            c.st.exec("begin");
            std::mt19937_64 rng(seed);
            c.rng = &rng;
            int64_t ev = c.parse_time("2020-07-01 12:00:00");
            c.test.now = [&] { return ev; };
            c.test.event_now = [&] { return ev; };
            sphere211::set_asset_check([](const std::string&) { return true; });
            for (int k = 0; k < 6; k++) {
                c.st.exec("delete from sphere");  // a fresh dive each time: floor 1 lotted again
                call(c, "GetSphere211Info", {});
                Snapshot s;
                c.st.q(
                    "select asset_id, mission_box_id, mission_id, overwrite_enemy_level from sphere_cell order by asset_id", {}, [&](const Row& r) {
                        s.emplace_back((u32)r.i("asset_id"), (u32)r.i("mission_box_id"), (u32)r.i("mission_id"), (u32)r.i("overwrite_enemy_level"));
                    });
                out.push_back(s);
            }
            sphere211::set_asset_check({});
            c.st.exec("rollback");
        });
    };
    std::vector<Snapshot> a, b;
    if (!run(a)) return t.fail("needs the 3.7.0 master and a seed save");
    run(b);
    t.expect_eq(a == b, true, "same seed, same floors");
    std::set<Snapshot> distinct(a.begin(), a.end());
    if (distinct.size() < 2) t.fail("6 lots of floor 1 were all the same map and battles");

    with_scratch_server(seed, [&](Ctx& c) {
        c.st.exec("begin");
        std::mt19937_64 rng(seed ^ 0x5eed);
        c.rng = &rng;
        int64_t ev = c.parse_time("2020-07-01 12:00:00");
        c.test.now = [&] { return ev; };
        c.test.event_now = [&] { return ev; };
        // (a) every cell of the lotted template; its battle from its box group, type = lottery_type
        u32 floor_group =
            (u32)c.m.one("select master_sphere211_floor_group_id from master_sphere211 where ? between opened_at and closed_at", {fmt(ev)});
        u32 box_group = (u32)c.m.one("select asset_box_group_id from master_sphere211_floor where floor_group_id = ? and level = 1", {floor_group});
        std::set<u32> templates;
        c.m.q("select asset_id from master_sphere211_floor_asset_box where asset_group_id = ?", {box_group},
              [&](const Row& r) { templates.insert((u32)r.i("asset_id")); });
        sphere211::set_asset_check([](const std::string&) { return true; });
        for (auto& snap : a) {
            if (snap.empty()) {
                t.fail("empty floor");
                continue;
            }
            u32 tmpl = (u32)c.m.one("select floor_group_id from master_sphere211_floor_asset where id = ?", {std::get<0>(snap[0])});
            if (!templates.count(tmpl)) t.fail("template %u not in the floor's asset box", tmpl);
            t.expect_eq((u32)snap.size(), (u32)c.m.one("select count(*) from master_sphere211_floor_asset where floor_group_id = ?", {tmpl}),
                        "cells = template rows");
            for (auto& [asset, box, mission, lv] : snap) {
                u32 mb = (u32)c.m.one("select ifnull(mission_box_group_id, 0) from master_sphere211_floor_asset where id = ?", {asset});
                if (!mb) {
                    if (mission) t.fail("cell %u without a box has mission %u", asset, mission);
                    continue;
                }
                u32 type = (u32)c.m.one("select lottery_type from master_sphere211_floor_asset where id = ?", {asset});
                t.expect_eq((u32)c.m.one("select mission_box_group_id from master_sphere211_mission_box where id = ?", {box}), mb, "box group");
                t.expect_eq((u32)c.m.one("select type from master_sphere211_mission_box where id = ?", {box}), type, "box type = lottery type");
                t.expect_eq((u32)c.m.one("select master_mission_id from master_sphere211_mission_box where id = ?", {box}), mission, "box mission");
            }
        }
        // Missing maps: every mission using the maps of the first lotted battle is skipped.
        u32 victim = 0;
        for (auto& e : a[0])
            if (std::get<2>(e)) {
                victim = std::get<2>(e);
                break;
            }
        std::set<std::string> gone;
        for (auto& m : maps_of(c, victim)) gone.insert("BG/" + m + ".aaf");
        if (gone.empty()) return t.fail("mission %u has no maps", victim);
        sphere211::set_asset_check([&](const std::string& rel) { return !gone.count(rel); });
        t.expect_eq(sphere211::mission_playable(c, victim), false, "a mission with a missing map isn't playable");
        int lotted = 0;
        for (int k = 0; k < 8; k++) {
            c.st.exec("delete from sphere");
            call(c, "GetSphere211Info", {});
            c.st.q("select asset_id, mission_id from sphere_cell where mission_box_id != 0", {}, [&](const Row& r) {
                lotted++;
                for (auto& m : maps_of(c, (u32)r.i("mission_id")))
                    if (gone.count("BG/" + m + ".aaf"))
                        t.fail("cell %u: mission %u uses a missing map", (u32)r.i("asset_id"), (u32)r.i("mission_id"));
            });
        }
        if (!lotted) t.fail("no battles lotted with one map missing");
        // (d) nothing playable at all: the unfiltered lot, so the floor still has its battles
        sphere211::set_asset_check([](const std::string&) { return false; });
        c.st.exec("delete from sphere");
        call(c, "GetSphere211Info", {});
        t.expect_eq(c.st.one("select count(*) from sphere_cell where mission_box_id != 0 and mission_id = 0", {}), (int64_t)0,
                    "no assets: every battle cell still has a mission");
        sphere211::set_asset_check({});
        c.st.exec("rollback");
    });
}

// The sphere stamina: max and regeneration from master_global, on the server clock (--clock).
NATIVE_TEST("sphere211/stamina") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 mx = c.global_u32("sphere_stamina_max", 0), period = c.global_u32("sphere_stamina_recovery_time", 0);
        t.expect_eq(mx, 9u, "master_global sphere_stamina_max");
        t.expect_eq(period, 17280u, "master_global sphere_stamina_recovery_time");
        int64_t base = c.parse_time("2020-07-01 12:00:00");
        set_server_clock(base);  // c.now is the server's clock_now
        auto stamina = [&] {
            Value d = call(c, "GetSphere211Info", {});
            return (u32)num(d, "Sphere211StaminaInfo", "stamina");
        };
        t.expect_eq(stamina(), mx, "starts full");
        c.st.q("update sphere set stamina = 2, stamina_at = ?", {base});
        set_server_clock(base + 3 * (int64_t)period + 100);
        t.expect_eq(stamina(), 5u, "+1 a period");
        set_server_clock(base + 3 * (int64_t)period + 100 + (int64_t)period - 200);
        t.expect_eq(stamina(), 5u, "not yet the next point");
        set_server_clock(base + 40 * (int64_t)period);
        t.expect_eq(stamina(), mx, "capped at the maximum");
        set_server_clock(0);
        c.st.exec("rollback");
    });
    set_server_clock(0);
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

// A dive: start -> end -> neighbours open -> failed / continue -> floor clear -> next floor ->
// 帰還 (boxes analysed, characters back) on a scratch server.
NATIVE_TEST("sphere211/dive") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        std::mt19937_64 rng(t.rand_u64());
        c.rng = &rng;
        int64_t clock = c.parse_time("2020-07-01 12:00:00");
        c.test.now = [&] { return clock; };
        c.test.event_now = [&] { return clock; };
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        sphere211::set_asset_check([](const std::string&) { return true; });
        Value d = call(c, "GetSphere211Info", {});
        auto cs = cells(d);
        if (cs.empty()) return t.fail("no cells");
        // (c)+(d) only the start cell (no neighbours listed) is playable at first
        u32 start = 0, nplay = 0;
        for (auto& [a, x] : cs)
            if (x.can_play) {
                nplay++;
                start = a;
            }
        t.expect_eq(nplay, 1u, "one playable cell");
        t.expect_eq((u32)c.m.one("select count(*) from master_sphere211_floor_asset where id = ? and parent_cell_1_id is null and "
                                 "parent_cell_2_id is null and parent_cell_3_id is null and parent_cell_4_id is null",
                                 {start}),
                    1u, "it has no neighbours listed");
        std::vector<u64> party;
        c.st.q("select uid from roster order by uid limit 3", {}, [&](const Row& r) { party.push_back((u64)r.i("uid")); });
        u32 st0 = (u32)num(d, "Sphere211StaminaInfo", "stamina");
        u32 ap0 = (u32)c.st.one("select stamina from player", {});
        u32 floor_use = (u32)c.m.one(
            "select use_stamina from master_sphere211_floor where floor_group_id = (select master_sphere211_floor_group_id "
            "from master_sphere211 where id = ?) and level = 1",
            {num(d.find("Sphere211CurrentId"))});
        // stamina short: refused, nothing spent
        c.st.q("update sphere set stamina = 0", {});
        code = 0;
        call(c, "Sphere211MissionStart", {start, 0, party[0], party[1], party[2], 0, 0});
        t.expect_eq(code, 10004u, "stamina short: 10004");
        t.expect_eq(c.st.one("select count(*) from sphere_departed", {}), (int64_t)0, "nobody departed");
        c.st.q("update sphere set stamina = ?", {st0});
        // start: the sphere gauge pays, not AP; the party departs
        code = 0;
        d = call(c, "Sphere211MissionStart", {start, 0, party[0], party[1], party[2], 0, 0});
        t.expect_eq(code, 0u, "start accepted");
        t.expect_eq((u32)num(d, "Sphere211StaminaInfo", "stamina"), st0 - floor_use, "sphere stamina spent");
        t.expect_eq((u32)c.st.one("select stamina from player", {}), ap0, "AP untouched");
        t.expect_eq(c.st.one("select playing from sphere_cell where asset_id = ?", {start}), (int64_t)1, "cell playing");
        t.expect_eq(c.st.one("select count(*) from sphere_departed", {}), (int64_t)3, "3 departed");
        const Value* bp = d.find("BattleParameter");
        t.expect_eq(bp && bp->find("PlayerCharacter") ? (u32)bp->find("PlayerCharacter")->arr.size() : 0u, 3u, "the chosen party fights");
        // end: cleared, streak 1, the battle's boxes; the start's neighbours open
        u32 boxes0 = (u32)c.st.one("select count(*) from sphere_box", {});
        d = call(c, "Sphere211MissionEnd", {start, 0});
        t.expect_eq((u32)num(d, "Sphere211FloorInfo", "mission_clear_streak"), 1u, "streak 1");
        cs = cells(d);
        t.expect_eq(cs[start].cleared, true, "start cleared");
        u32 treasure_num = (u32)c.m.one(
            "select treasure_num from master_sphere211_floor where floor_group_id = (select master_sphere211_floor_group_id "
            "from master_sphere211 where id = ?) and level = 1",
            {num(d.find("Sphere211CurrentId"))});
        u32 type = (u32)c.m.one("select lottery_type from master_sphere211_floor_asset where id = ?", {start});
        if (type == 1) t.expect_eq((u32)c.st.one("select count(*) from sphere_box", {}) - boxes0, treasure_num, "boxes: treasure_num");
        std::set<u32> want_open;
        c.m.q("select id from master_sphere211_floor_asset where ? in (parent_cell_1_id, parent_cell_2_id, parent_cell_3_id, parent_cell_4_id)",
              {start}, [&](const Row& r) { want_open.insert((u32)r.i("id")); });
        std::set<u32> open;
        for (auto& [a, x] : cs)
            if (x.can_play) open.insert(a);
        t.expect_eq(open == want_open && !open.empty(), true, "the start's neighbours open");
        // a lost battle: the streak resets, the cell stays open, the stamina stays spent
        u32 next = *open.begin();
        u32 st1 = (u32)c.st.one("select stamina from sphere", {});
        call(c, "Sphere211MissionStart", {next, 0, party[0], party[1], party[2], 0, 0});
        u32 coins = (u32)c.st.one("select free_coin from player", {});
        d = call(c, "Sphere211MissionContinue", {next, 0, 1});
        t.expect_eq(d.find("is_mission_continue") && d.find("is_mission_continue")->b, true, "continue answered");
        t.expect_eq((u32)c.st.one("select free_coin from player", {}), coins - c.global_u32("continue_use_coin", 100),
                    "(a) continue costs continue_use_coin");
        t.expect_eq(d.find("Wallet") != nullptr, true, "the wallet is sent");
        d = call(c, "Sphere211MissionFailed", {next, 0});
        t.expect_eq((u32)num(d, "Sphere211FloorInfo", "mission_clear_streak"), 0u, "retire resets the streak");
        t.expect_eq(cells(d)[next].cleared, false, "retired cell not cleared");
        t.expect_eq(cells(d)[next].can_play, true, "retired cell still playable");
        t.expect_eq((u32)c.st.one("select stamina from sphere", {}), st1 - floor_use, "stamina stays spent");
        // the goal: floor clear, present + boxes, the next-floor lot
        u32 group = (u32)c.st.one("select asset_group from sphere", {});
        u32 goal = (u32)c.m.one("select id from master_sphere211_floor_asset where floor_group_id = ? and is_goal = 1", {group});
        u32 fct = (u32)c.m.one(
            "select floor_clear_treasure_num from master_sphere211_floor where floor_group_id = (select "
            "master_sphere211_floor_group_id from master_sphere211 where id = ?) and level = 1",
            {num(d.find("Sphere211CurrentId"))});
        u32 boxes1 = (u32)c.st.one("select count(*) from sphere_box", {});
        d = call(c, "Sphere211FloorClear", {goal});
        t.expect_eq((u32)c.st.one("select count(*) from sphere_box", {}) - boxes1, fct, "floor_clear_treasure_num boxes");
        t.expect_eq((u32)num(d, "Sphere211FloorClearInfo", "master_sphere211_asset_id"), goal, "clear info: goal");
        u32 lot = (u32)num(d, "Sphere211FloorClearInfo", "lot_floor_num");
        if (lot < 1) t.fail("lot_floor_num %u", lot);
        t.expect_eq(d.find("Sphere211FloorClearResultInfo") && d.find("Sphere211FloorClearResultInfo")->find("clear_present_id") != nullptr, true,
                    "clear present");
        // the next floor: the first offered one
        d = call(c, "Sphere211SelectedFloor", {1});
        t.expect_eq((u32)num(d, "Sphere211FloorInfo", "floor_level"), 2u, "floor 2");
        t.expect_eq((u32)num(d, "Sphere211FloorClearInfo", "master_sphere211_asset_id"), 0u, "clear info reset");
        t.expect_eq(c.st.one("select count(*) from sphere_departed", {}), (int64_t)3, "(b) the departed stay out until 帰還");
        // 帰還: the boxes are analysed and opened, everyone comes back, the dive stays on its floor
        u32 nbox = (u32)c.st.one("select count(*) from sphere_box", {});
        d = call(c, "ReturnSphere211", {});
        const Value* lots = d.find("Sphere211TreasureResultLotInfoMap");
        u32 sum = 0;
        if (lots)
            for (auto& [k, e] : lots->map) sum += (u32)num(e.find("lot_num"));
        t.expect_eq(sum, nbox, "every box analysed");
        const Value* res = d.find("Sphere211TreasureResultInfoMap");
        u32 got = 0;
        if (res)
            for (auto& [k, l] : res->map) {
                if (std::stoul(k) > 4) t.fail("rank key %s", k.c_str());
                got += (u32)l.arr.size();
            }
        if (nbox && !got) t.fail("no rewards from %u boxes", nbox);
        t.expect_eq(c.st.one("select count(*) from sphere_box", {}), (int64_t)0, "boxes opened");
        t.expect_eq(c.st.one("select count(*) from sphere_departed", {}), (int64_t)0, "everyone back");
        t.expect_eq((u32)num(d, "Sphere211FloorInfo", "floor_level"), 2u, "(d) the dive stays on floor 2");
        t.expect_eq((u32)num(d, "Sphere211FloorInfo", "mission_clear_streak"), 0u, "streak reset");
        // the local ranking: best floor 2, rank 1
        d = call(c, "GetSphere211RankingInfo", {0});
        const Value* rk = d.find("Sphere211RankingInfoMap");
        t.expect_eq(rk && rk->map.size() == 1 ? (u32)num(rk->map[0].second.find("floor_level")) : 0u, 2u, "ranking: best floor");
        sphere211::set_asset_check({});
        c.st.exec("rollback");
    });
    sphere211::set_asset_check({});
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

// The rental slot: the lenders (the synthetic rental players), once per floor each, three a floor;
// the Sphere 211 rental bonus paid the next day on the player load.
NATIVE_TEST("sphere211/rental") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        std::mt19937_64 rng(t.rand_u64());
        c.rng = &rng;
        int64_t clock = c.parse_time("2020-07-01 12:00:00");
        c.test.now = [&] { return clock; };
        c.test.event_now = [&] { return clock; };
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        sphere211::set_asset_check([](const std::string&) { return true; });
        Value d = call(c, "GetSphere211Info", {});
        const Value* info = d.find("Sphere211RentalCharacterInfoMap");
        const Value* detail = d.find("Sphere211RentalCharacterDetailInfoMap");
        const Value* fid = d.find("FollowID");
        if (!info || !detail || !fid) return t.fail("rental keys missing");
        if (info->map.size() < 4) return t.fail("only %zu lenders", info->map.size());
        t.expect_eq(detail->map.size(), info->map.size(), "a detail entry per lender");
        t.expect_eq(fid->arr.size(), info->map.size(), "(b) every lender followed (FollowID)");
        std::vector<std::pair<u32, u64>> lenders;  // player id, rental character id
        for (auto& [k, e] : info->map) {
            u32 lp = (u32)num(e.find("follow_player_id"));
            t.expect_eq(std::to_string(lp), k, "keyed by the lender");
            t.expect_eq(e.find("is_used") && !e.find("is_used")->b, true, "not used yet");
            const Value* de = detail->find(k);
            const Value* pc = de ? de->find("pc") : nullptr;
            t.expect_eq(pc ? (u32)num(pc->find("player_id")) : 0u, lp, "(b) detail pc.player_id = the lender");
            lenders.push_back({lp, pc ? num(pc->find("id")) : 0});
        }
        auto used = [&](const Value& v, u32 lp) {
            const Value* m = v.find("Sphere211RentalCharacterInfoMap");
            const Value* e = m ? m->find(std::to_string(lp)) : nullptr;
            return e && e->find("is_used") && e->find("is_used")->b;
        };
        u32 start = 0;
        for (auto& [a, x] : cells(d))
            if (x.can_play) start = a;
        std::vector<u64> party;
        c.st.q("select uid from roster order by uid limit 3", {}, [&](const Row& r) { party.push_back((u64)r.i("uid")); });
        // a rental in the 4th slot
        code = 0;
        d = call(c, "Sphere211MissionStart", {start, 0, party[0], party[1], party[2], lenders[0].second, lenders[0].first});
        t.expect_eq(code, 0u, "rental start accepted");
        t.expect_eq(used(d, lenders[0].first), true, "the lender is used");
        t.expect_eq(c.st.one("select count(*) from sphere_departed", {}), (int64_t)3, "(d) the rental doesn't depart");
        const Value* bp = d.find("BattleParameter");
        t.expect_eq(bp && bp->find("PlayerCharacter") ? (u32)bp->find("PlayerCharacter")->arr.size() : 0u, 4u, "the rental fights as member 4");
        d = call(c, "Sphere211MissionEnd", {start, 0});
        // the same lender again on this floor: refused
        u32 next = 0;
        for (auto& [a, x] : cells(d))
            if (x.can_play) next = a;
        std::vector<u64> party2;
        c.st.q("select uid from roster where uid not in (select uid from sphere_departed) order by uid limit 3", {},
               [&](const Row& r) { party2.push_back((u64)r.i("uid")); });
        code = 0;
        call(c, "Sphere211MissionStart", {next, 0, party2[0], party2[1], party2[2], lenders[0].second, lenders[0].first});
        t.expect_eq(code, 10208u, "(d) a lender lends once per floor");
        // (a) three rentals a floor: then every lender counts as used
        c.st.q("insert into sphere_rental values (?, 1, ?), (?, 1, ?)", {lenders[1].first, clock, lenders[2].first, clock});
        d = call(c, "GetSphere211Info", {});
        t.expect_eq(used(d, lenders[3].first), true, "three rentals: the floor's rentals are used up");
        code = 0;
        call(c, "Sphere211MissionStart", {next, 0, party2[0], party2[1], party2[2], lenders[3].second, lenders[3].first});
        t.expect_eq(code, 10208u, "a fourth rental refused");
        // a new floor lends again
        u32 group = (u32)c.st.one("select asset_group from sphere", {});
        u32 goal = (u32)c.m.one("select id from master_sphere211_floor_asset where floor_group_id = ? and is_goal = 1", {group});
        call(c, "Sphere211FloorClear", {goal});
        d = call(c, "Sphere211SelectedFloor", {1});
        t.expect_eq(used(d, lenders[0].first) || used(d, lenders[3].first), false, "a new floor: every lender again");
        // the Sphere 211 rental bonus: 5 rentals on a day (a: rental_count 5) pay the next day
        u32 season = (u32)num(d.find("Sphere211CurrentId"));
        t.expect_eq(c.st.one("select ifnull(sum(count), 0) from sphere_rental_day", {}), (int64_t)1, "one rental counted");
        c.st.q("update sphere_rental_day set count = 5", {});
        u32 row = 0, item = 0;
        c.m.q("select id, content_id from master_sphere211_rental_bonus where master_sphere211_id = ? order by rental_count limit 1", {season},
              [&](const Row& r) {
                  row = (u32)r.i("id");
                  item = (u32)r.i("content_id");
              });
        if (!row) return t.fail("season %u has no rental bonus row", season);
        auto presents_of = [&] { return c.st.one("select count(*) from presents where content_id = ?", {item}); };
        int64_t presents = presents_of();
        Value pd = Value::object();
        Request lr;
        lr.method = "Login";
        player_load(c, lr, pd);
        t.expect_eq(pd.find("Sphere211RentalBonus") == nullptr, true, "not paid the same day");
        clock += 86400;
        pd = Value::object();
        player_load(c, lr, pd);
        t.expect_eq((u32)num(pd.find("Sphere211RentalBonus")), row, "(b) Sphere211RentalBonus = the row id");
        t.expect_eq((u32)num(pd.find("Sphere211RentalCount")), 5u, "Sphere211RentalCount");
        t.expect_eq(presents_of() - presents, (int64_t)1, "one present of the season's reroll item");
        pd = Value::object();
        player_load(c, lr, pd);
        t.expect_eq(pd.find("Sphere211RentalBonus") == nullptr, true, "paid once");
        sphere211::set_asset_check({});
        c.st.exec("rollback");
    });
    sphere211::set_asset_check({});
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

// The Sphere 211 achievements (types 61 / 62): open on the season's moved dates, counted from the
// dive's log.
NATIVE_TEST("sphere211/achievements") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        std::mt19937_64 rng(t.rand_u64());
        c.rng = &rng;
        u32 weekly = 0, floor_row = 0;
        std::string wo, wc;
        c.m.q(
            "select id, opened_at, closed_at from master_achievement where type = 62 and id_label like 'Event_sphere_mission_%' and "
            "default_release = 1 order by opened_at, goal_count limit 1",
            {}, [&](const Row& r) {
                weekly = (u32)r.i("id");
                wo = r.s("opened_at");
                wc = r.s("closed_at");
            });
        if (!weekly) return t.fail("no weekly challenge rows");
        int64_t evc = c.parse_time(wo) + 86400, clock = evc;
        floor_row = (u32)c.m.one(
            "select id from master_achievement where type = 61 and default_release = 1 and opened_at <= ? and closed_at >= ? "
            "order by goal_count limit 1",
            {fmt(evc), fmt(evc)});
        if (!floor_row) return t.fail("no floor achievement open at %s", fmt(evc).c_str());
        c.test.now = [&] { return clock; };
        c.test.event_now = [&] { return evc; };
        sphere211::set_asset_check([](const std::string&) { return true; });
        auto entry = [&](const Value& list, u32 id) -> const Value* {
            for (auto& e : list.arr)  // the list (before agent a6-deepspace) or
                if ((u32)num(e.find("master_achievement_id")) == id) return &e;
            for (auto& [k, e] : list.map)  // the id-keyed map
                if ((u32)num(e.find("master_achievement_id")) == id) return &e;
            return nullptr;
        };
        Value d = call(c, "GetSphere211Info", {});
        const Value* ach = d.find("Achievement");
        if (!ach) return t.fail("no Achievement state with the Sphere 211 answers");
        const Value* e = entry(*ach, weekly);
        if (!e) return t.fail("weekly challenge %u not active at %s", weekly, fmt(clock).c_str());
        t.expect_eq((u32)num(e->find("count")), 0u, "nothing won yet");
        t.expect_eq(e->find("limit_at") ? e->find("limit_at")->s : std::string(), wc, "limit_at = closed_at (no shift)");
        e = entry(*ach, floor_row);
        t.expect_eq(e ? (u32)num(e->find("count")) : 99u, 1u, "type 61: floor 1 entered");
        // a battle won counts
        u32 start = 0;
        for (auto& [a, x] : cells(d))
            if (x.can_play) start = a;
        std::vector<u64> party;
        c.st.q("select uid from roster order by uid limit 3", {}, [&](const Row& r) { party.push_back((u64)r.i("uid")); });
        call(c, "Sphere211MissionStart", {start, 0, party[0], party[1], party[2], 0, 0});
        d = call(c, "Sphere211MissionEnd", {start, 0});
        e = d.find("Achievement") ? entry(*d.find("Achievement"), weekly) : nullptr;
        t.expect_eq(e ? (u32)num(e->find("count")) : 0u, 1u, "type 62: one battle won");
        // a win outside the window doesn't count
        c.st.q("insert into sphere_log (kind, value, at) values (1, 1, ?)", {c.parse_time(wo) - 60});
        Value st = achievement_state(c);
        e = entry(st, weekly);
        t.expect_eq(e ? (u32)num(e->find("count")) : 0u, 1u, "a win before the window doesn't count");
        // replayed six years later: the window moves with the season, the old wins are outside it
        clock = evc + 6 * 365 * 86400;
        st = achievement_state(c);
        e = entry(st, weekly);
        if (!e) return t.fail("weekly challenge not active on the moved dates");
        {
            std::string got = e->find("limit_at") ? e->find("limit_at")->s : std::string(), want = fmt(c.parse_time(wc) + (clock - evc));
            if (got != want) t.fail("limit_at %s, want %s (closed_at %s)", got.c_str(), want.c_str(), wc.c_str());
        }
        t.expect_eq((u32)num(e->find("count")), 0u, "the moved week starts at 0");
        // after the moved window: gone
        clock = c.parse_time(wc) + (clock - evc) + 60;
        evc = c.parse_time(wc) + 60;
        t.expect_eq(entry(achievement_state(c), weekly) == nullptr, true, "closed after its week");
        sphere211::set_asset_check({});
        c.st.exec("rollback");
    });
    sphere211::set_asset_check({});
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

// The season's items: the heal ticket adds its heal_point (a), the reroll item re-lots the
// next-floor count; both refused (10206) without the item.
NATIVE_TEST("sphere211/items") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        std::mt19937_64 rng(t.rand_u64());
        c.rng = &rng;
        int64_t clock = c.parse_time("2020-07-01 12:00:00");
        c.test.now = [&] { return clock; };
        c.test.event_now = [&] { return clock; };
        u32 code = 0;
        c.test.on_refuse = [&](u32 e) { code = e; };
        sphere211::set_asset_check([](const std::string&) { return true; });
        Value d = call(c, "GetSphere211Info", {});
        u32 season = (u32)num(d.find("Sphere211CurrentId"));
        u32 heal = (u32)c.m.one("select heal_item_id from master_sphere211 where id = ?", {season});
        u32 reroll = (u32)c.m.one("select reroll_item_id from master_sphere211 where id = ?", {season});
        u32 point = (u32)c.m.one("select heal_point from master_item where id = ?", {heal});
        t.expect_eq(point, 1u, "(a) the ticket heals 1");
        // no item: refused
        c.st.q("update sphere set stamina = 3", {});
        code = 0;
        call(c, "Sphere211StaminaHeal", {});
        t.expect_eq(code, 10206u, "no heal item: 10206");
        c.st.q("insert or replace into stock values (?, 10, 2)", {heal});
        code = 0;
        d = call(c, "Sphere211StaminaHeal", {});
        t.expect_eq(code, 0u, "heal accepted");
        t.expect_eq((u32)num(d, "Sphere211StaminaInfo", "stamina"), 3u + point, "+heal_point");
        t.expect_eq(c.st.one("select count from stock where master_item_id = ?", {heal}), (int64_t)1, "one ticket used");
        c.st.q("update sphere set stamina = 9", {});
        d = call(c, "Sphere211StaminaHeal", {});
        t.expect_eq((u32)num(d, "Sphere211StaminaInfo", "stamina"), 9u, "(d) capped at the maximum");
        // reroll: needs the item, re-lots lot_floor_num (at least 1)
        c.st.q("update sphere set lot_floor_num = 1, clear_asset = 1", {});
        code = 0;
        call(c, "Sphere211UseRerollItem", {});
        t.expect_eq(code, 10206u, "no reroll item: 10206");
        c.st.q("insert or replace into stock values (?, 10, 1)", {reroll});
        code = 0;
        d = call(c, "Sphere211UseRerollItem", {});
        t.expect_eq(code, 0u, "reroll accepted");
        t.expect_eq(c.st.one("select count from stock where master_item_id = ?", {reroll}), (int64_t)0, "the reroll item used");
        if (num(d, "Sphere211FloorClearInfo", "lot_floor_num") < 1) t.fail("lot_floor_num < 1 after the reroll");
        t.expect_eq(c.st.one("select reroll_count from sphere", {}), (int64_t)1, "reroll counted");
        sphere211::set_asset_check({});
        c.st.exec("rollback");
    });
    sphere211::set_asset_check({});
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

}  // namespace soa::server
