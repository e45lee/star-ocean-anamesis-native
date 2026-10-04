// Unit tests of the event extras (--selftest "events/"; names were server/event-* and
// server/worldboss-* before R18): exchange shops on the event calendar (api/shop/shop.cpp), the
// local event ranking (api/events/ranking.cpp), world bosses and time bonuses (api/events/world_boss.cpp),
// the favor event drop bonus (api/events/favor_drop.cpp). Events and missions are picked from the master
// data by their columns, never by name. Not differential (the server has no guest
// counterpart); scratch servers seeded from the test seed save and the 3.7.0 master.
#include <sqlite3.h>

#include <string>
#include <vector>

#include "soaserver/native_test.h"
#include "soaserver/events.h"
#include "soaserver/ext.h"

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

// An in-memory copy of master tables, as the client's master copy (ext::ClientMaster's input).
sqlite3* client_copy(Ctx& c, std::initializer_list<const char*> tables) {
    sqlite3* db = nullptr;
    sqlite3_open(":memory:", &db);
    Sql cm{db};
    cm.exec(std::string("attach '") + sqlite3_db_filename(c.m.h, "main") + "' as src");
    for (const char* t : tables) cm.exec(std::string("create table ") + t + " as select * from src." + t);
    cm.exec("detach src");
    return db;
}

u64 num(const Value* v) { return !v ? 0 : v->type == Value::Int ? (u64)v->i : v->u; }
u64 num(const Value& d, const char* a, const char* b) {
    const Value* x = d.find(a);
    return x ? num(x->find(b)) : 0;
}
// A won mission as the core hands it to the modules (ext::MissionInfo) with an evaluation value.
MissionInfo won(Ctx& c, u32 mission, int64_t value, u32 ms = 0) {
    MissionInfo mi;
    mi.mission = mission;
    mi.type = 1;
    mi.table = "master_event_mission";
    mi.area = (u32)c.m.one("select master_event_area_id from master_event_mission where id = ?", {mission});
    c.st.q("select role_id from roster order by uid limit 3", {}, [&](const Row& r) { mi.roles.push_back((u32)r.i("role_id")); });
    mi.mission_time = ms;
    mi.evaluation = [value](int) { return value; };
    mi.log_u32 = [](const char*) { return 0u; };
    return mi;
}
Value result(Ctx& c, const MissionInfo& mi) {
    Value d = Value::object();
    mission_result_extra(c, mi, d);
    return d;
}

}  // namespace

// Exchange shops on the event calendar: an event's coin shop is listed and exchangeable while the
// calendar is inside its window, and the client's master copy moves it to the clock.
NATIVE_TEST("events/exchange-shop-calendar") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        // an exchange shop with a closed, dated window (from the data, not a name)
        u32 shop = 0;
        std::string o, cl;
        c.m.q(
            "select id, opened_at, closed_at from master_exchange_shop where opened_at > '2017' and closed_at < '2022' and "
            "(select count(*) from master_exchange_shop_contents x where x.master_exchange_shop_id = master_exchange_shop.id) > 0 "
            "order by id limit 1",
            {}, [&](const Row& r) {
                shop = (u32)r.i("id");
                o = r.s("opened_at");
                cl = r.s("closed_at");
            });
        if (!shop) {
            t.fail("no dated exchange shop");
            return;
        }
        int64_t a = c.parse_time(o), b = c.parse_time(cl);
        int64_t ev = a + (b - a) / 2;
        int64_t clock = c.parse_time(events::shift_years(c.fmt_time(ev), 6));
        c.test.now = [&] { return clock; };
        c.test.event_now = [&] { return ev; };
        Value d = call(c, "ExshopExchangeList", {});
        const Value* m = d.find("ExchangeShopExCount");
        if (!m || !m->find(std::to_string(shop))) t.fail("shop %u not listed on its calendar day", shop);
        // outside the calendar window: not listed
        int64_t late = b + 400 * 86400;
        c.test.event_now = [&] { return late; };
        d = call(c, "ExshopExchangeList", {});
        m = d.find("ExchangeShopExCount");
        if (m && m->find(std::to_string(shop))) t.fail("shop %u listed after its window", shop);
        // the client's copy: moved by the whole years so the clock is inside
        sqlite3* db = client_copy(c, {"master_exchange_shop", "master_exchange_shop_contents"});
        client_master(db, ServerTime(clock), EventTime(ev));
        Sql cm{db};
        std::string no, ncl;
        cm.q("select opened_at, closed_at from master_exchange_shop where id = ?", {shop}, [&](const Row& r) {
            no = r.s("opened_at");
            ncl = r.s("closed_at");
        });
        if (!events::window_open(no, ncl, 0, ServerTime(clock)))
            t.fail("client copy %s .. %s doesn't cover the clock %s", no.c_str(), ncl.c_str(), c.fmt_time(clock).c_str());
        t.expect_eq(cm.one("select count(*) from master_exchange_shop where opened_at like '2016%' and closed_at like '2030%'", {}),
                    c.m.one("select count(*) from master_exchange_shop where opened_at like '2016%' and closed_at like '2030%'", {}),
                    "open-ended shops untouched");
        sqlite3_close(db);
        c.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

// The local event ranking: the best score of the ranking's mission while its group runs (lower is
// better for clear time), the ranking screen's rows, then the result and its reward tier once.
NATIVE_TEST("events/ranking") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        // a group with a higher-is-better ranking (type 1..5) and its mission
        u32 group = 0, ranking = 0, mission = 0, type = 0;
        std::string o, cl, rc, res;
        c.m.q(
            "select r.id, r.ranking_type, r.master_event_mission_id, g.* from master_event_ranking r join master_event_ranking_group g "
            "on g.id = r.ranking_group_id where r.ranking_type between 1 and 5 order by g.opened_at limit 1",
            {}, [&](const Row& r) {
                group = (u32)r.i("id");
                ranking = (u32)c.m.one("select id from master_event_ranking where ranking_group_id = ? and ranking_type = ? limit 1",
                                       {r.i("id"), r.i("ranking_type")});
                mission = (u32)r.i("master_event_mission_id");
                type = (u32)r.i("ranking_type");
                o = r.s("opened_at"), cl = r.s("closed_at"), rc = r.s("ranking_closed_at"), res = r.s("result_closed_at");
            });
        if (!group) {
            t.fail("no ranking group");
            return;
        }
        // (both clocks the same: no year move; the move itself is the event module's, tested in events/shift)
        int64_t ev = c.parse_time(o) + 3600;
        c.test.now = [&] { return ev; };
        c.test.event_now = [&] { return ev; };
        Value d = result(c, won(c, mission, 5000));
        const Value* up = d.find("UpdatedEventRankingIdList");
        if (!up || up->arr.empty()) t.fail("no UpdatedEventRankingIdList after a scored win");
        result(c, won(c, mission, 3000));  // worse: kept 5000
        result(c, won(c, mission, 7000));  // better
        d = call(c, "GetEventRankingInfo", {group});
        const Value* lists = d.find("GetEventRankingResultInfo") ? d.find("GetEventRankingResultInfo")->find("EventRankingInfoListMap") : nullptr;
        const Value* rows = lists ? lists->find(std::to_string(ranking)) : nullptr;
        if (!rows || rows->arr.size() != 1) t.fail("ranking %u: not one row", ranking);
        else {
            t.expect_eq(num(rows->arr[0].find("score")), (u64)7000, "best score kept (higher is better)");
            t.expect_eq(num(rows->arr[0].find("rank_ui")), (u64)1, "rank 1");
            t.expect_eq(num(rows->arr[0].find("party_player_id1")), (u64)c.player_id().v, "own row");
        }
        // a win outside the group's window scores nothing
        int64_t late = c.parse_time(cl) + 60;
        c.test.now = [&] { return late; };
        c.test.event_now = [&] { return late; };
        result(c, won(c, mission, 9000));
        t.expect_eq(c.st.one("select score from event_rank_score where ranking_id = ?", {ranking}), (int64_t)7000, "closed group");
        // nothing due before ranking_closed_at, the group after it
        t.expect_eq(num(call(c, "CheckEventRankingResult", {}), "CheckEventRankingResultInfo", "master_event_ranking_group_id"), (u64)0,
                    "not due while counting");
        int64_t due = c.parse_time(rc) + 60;
        c.test.now = [&] { return due; };
        c.test.event_now = [&] { return due; };
        t.expect_eq(num(call(c, "CheckEventRankingResult", {}), "CheckEventRankingResultInfo", "master_event_ranking_group_id"), (u64)group, "due");
        // the reward: the tier of rank 1 (smallest required_ranking >= 1)
        u32 rtype = 0;
        c.m.q("select content_type from master_event_ranking_reward where ranking_reward_group_id = ? order by required_ranking limit 1", {ranking},
              [&](const Row& r) { rtype = (u32)r.i("content_type"); });
        int64_t presents_items = c.st.one("select count(*) from items", {}) + c.st.one("select ifnull(sum(count), 0) from stock", {});
        d = call(c, "ReceiveEventRankingResult", {});
        t.expect_eq(num(d, "CheckEventRankingResultInfo", "master_event_ranking_group_id"), (u64)group, "received group");
        if (rtype && c.st.one("select count(*) from items", {}) + c.st.one("select ifnull(sum(count), 0) from stock", {}) <= presents_items)
            t.fail("no reward granted (content type %u)", rtype);
        t.expect_eq(num(call(c, "CheckEventRankingResult", {}), "CheckEventRankingResultInfo", "master_event_ranking_group_id"), (u64)0,
                    "received once");
        d = call(c, "ClearNewEventRanking", {});
        if (!d.find("UpdatedEventRankingIdList") || !d.find("UpdatedEventRankingIdList")->arr.empty()) t.fail("ClearNew: empty list");
        (void)type;
        // clear time (type 6): lower is better, 0 is no time
        u32 r6 = 0, m6 = 0, g6 = 0;
        std::string o6;
        c.m.q(
            "select r.id, r.master_event_mission_id, g.id as gid, g.opened_at from master_event_ranking r join master_event_ranking_group g "
            "on g.id = r.ranking_group_id where r.ranking_type = 6 limit 1",
            {}, [&](const Row& r) { r6 = (u32)r.i("id"), m6 = (u32)r.i("master_event_mission_id"), g6 = (u32)r.i("gid"), o6 = r.s("opened_at"); });
        if (r6) {
            int64_t e6 = c.parse_time(o6) + 60;
            c.test.now = [&] { return e6; };
            c.test.event_now = [&] { return e6; };
            result(c, won(c, m6, 0));
            t.expect_eq(c.st.one("select count(*) from event_rank_score where ranking_id = ?", {r6}), (int64_t)0, "no time, no score");
            result(c, won(c, m6, 90000));
            result(c, won(c, m6, 120000));
            result(c, won(c, m6, 80000));
            t.expect_eq(c.st.one("select score from event_rank_score where ranking_id = ?", {r6}), (int64_t)80000, "fastest kept");
            (void)g6;
        }
        c.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

// World boss: GetWorldBossInfo by event area, the gauges filled by target-item drops, a wave clear
// (present, next wave, big hunt, clear list once, cut-in once), the calendar gate.
NATIVE_TEST("events/worldboss-waves") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 area = 0, boss = 0, mission = 0;
        std::string o;
        c.m.q(
            "select a.id as area, b.id as boss, b.opened_at from master_event_area a join master_world_boss b on b.id = a.event_id "
            "where a.event_type = 1 and (select count(*) from master_world_boss_wave w where w.world_boss_event_id = b.id) > 1 order by a.id limit 1",
            {}, [&](const Row& r) { area = (u32)r.i("area"), boss = (u32)r.i("boss"), o = r.s("opened_at"); });
        if (!area) {
            t.fail("no world-boss event area");
            return;
        }
        mission = (u32)c.m.one("select id from master_event_mission where master_event_area_id = ? and ifnull(is_bighunt, 0) = 0 limit 1", {area});
        // the calendar six years back: the boss's window moved onto the clock (events::client_years)
        int64_t ev = c.parse_time(o) + 86400;
        int64_t clock = c.parse_time(events::shift_years(c.fmt_time(ev), 6));
        c.test.now = [&] { return clock; };
        c.test.event_now = [&] { return ev; };
        Value d = call(c, "GetWorldBossInfo", {area});
        t.expect_eq((u32)num(d, "CWorldBossInfo", "world_boss_id"), boss, "boss of the area");
        t.expect_eq((u32)num(d, "CWorldBossInfo", "wave"), 1u, "wave 1");
        u64 need = num(d, "CT_WorldBossInfo", "next_required_num");
        if (!need) t.fail("no requirement");
        t.expect_eq(num(d.find("start_bigHunt_area_id")), (u64)0, "no hunt yet");
        if (const Value* l = d.find("CWorldBossPlayerInfoList"); !l || !l->map.empty()) t.fail("empty clear list");
        // target items in a result's drops fill the gauges
        u32 items[3];
        c.m.q("select * from master_world_boss where id = ?", {boss}, [&](const Row& r) {
            items[0] = (u32)r.i("target_item1_id"), items[1] = (u32)r.i("target_item2_id"), items[2] = (u32)r.i("target_item3_id");
        });
        auto drops = [&](u64 n0, u64 n1, u64 n2) {
            MissionInfo mi = won(c, mission, 0);
            Value dd = Value::object();
            Value dl = Value::object();
            Value st = Value::array();
            u64 n[3] = {n0, n1, n2};
            for (int k = 0; k < 3; k++) {
                Value e = Value::object();
                e["id"] = items[k];
                e["num"] = n[k];
                st.push(e);
            }
            dl["stock_item"] = st;
            dd["DropList"] = dl;
            mission_result_extra(c, mi, dd);
            return dd;
        };
        d = drops(need, need, need / 2);
        t.expect_eq((u32)num(d, "CWorldBossInfo", "wave"), 1u, "one gauge short: still wave 1");
        t.expect_eq(num(d, "CWorldBossInfo", "num1"), need, "gauge 1");
        int64_t presents = c.st.one("select count(*) from presents", {});
        d = drops(0, 0, need);
        t.expect_eq((u32)num(d, "CWorldBossInfo", "wave"), 2u, "wave cleared");
        t.expect_eq(num(d, "CWorldBossInfo", "num1"), (u64)0, "fresh gauges");
        t.expect_eq(c.st.one("select count(*) from presents", {}), presents + 1, "wave reward in the present box");
        t.expect_eq((u32)num(d.find("start_bigHunt_area_id")), area, "big hunt in the area");
        d = call(c, "GetWorldBossInfo", {area});
        const Value* l = d.find("CWorldBossPlayerInfoList");
        t.expect_eq(l ? l->map.size() : 0, (size_t)1, "one clear listed");
        if (!d.find("CWorldBossPlayerInfo") || !d.find("CWorldBossPlayerInfo")->find("is_new_open") ||
            !d.find("CWorldBossPlayerInfo")->find("is_new_open")->b)
            t.fail("cut-in on the first open");
        if (d.find("CT_WorldBossInfo")->find("bighunt_closed_at")->s.empty()) t.fail("hunt end time");
        d = call(c, "GetWorldBossInfo", {area});
        l = d.find("CWorldBossPlayerInfoList");
        t.expect_eq(l ? l->map.size() : 1, (size_t)0, "the clear listed once");
        if (d.find("CWorldBossPlayerInfo")->find("is_new_open")->b) t.fail("cut-in once");
        // after the hunt: no hunt area; outside the boss's window: no boss
        int64_t after = clock + 400 * 86400;
        c.test.now = [&] { return after; };
        c.test.event_now = [&] { return after; };
        d = call(c, "GetWorldBossInfo", {area});
        t.expect_eq(num(d, "CWorldBossInfo", "world_boss_id"), (u64)0, "boss window over");
        t.expect_eq(num(d.find("start_bigHunt_area_id")), (u64)0, "hunt over");
        c.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

// Time bonus: the master_time_bonus rows whose time the win is within, granted and listed.
NATIVE_TEST("events/worldboss-time-bonus") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        u32 mission = 0;
        int64_t type = 0;
        c.m.q(
            "select id, time_bonus_type_id from master_event_mission where time_bonus_type_id is not null and time_bonus_type_id != 0 "
            "order by id limit 1",
            {}, [&](const Row& r) { mission = (u32)r.i("id"), type = r.i("time_bonus_type_id"); });
        if (!mission) {
            t.fail("no time-bonus mission");
            return;
        }
        int64_t rows = c.m.one("select count(*) from master_time_bonus where type_id = ?", {type});
        int64_t min_t = c.m.one("select min(time) from master_time_bonus where type_id = ?", {type});
        int64_t max_t = c.m.one("select max(time) from master_time_bonus where type_id = ?", {type});
        Value d = result(c, won(c, mission, 0, 1000));
        const Value* l = d.find("WorldBossMissionTimeBonusDropItemInfoList");
        t.expect_eq(l ? (int64_t)l->arr.size() : 0, rows, "fast: every row");
        if (!d.find("StockItem")) t.fail("granted stock items listed");
        d = result(c, won(c, mission, 0, (u32)(max_t * 1000 + 1)));
        t.expect_eq(d.find("WorldBossMissionTimeBonusDropItemInfoList") == nullptr, true, "too slow: none");
        if (max_t > min_t) {
            d = result(c, won(c, mission, 0, (u32)(max_t * 1000)));
            l = d.find("WorldBossMissionTimeBonusDropItemInfoList");
            t.expect_eq(l ? (int64_t)l->arr.size() : 0,
                        c.m.one("select count(*) from master_time_bonus where type_id = ? and time >= ?", {type, max_t}),
                        "at the slowest row's time");
        }
        d = result(c, won(c, mission, 0, 0));
        t.expect_eq(d.find("WorldBossMissionTimeBonusDropItemInfoList") == nullptr, true, "no time: none");
        c.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

// The favor event drop bonus through the core MissionStart / MissionEnd of an event mission: party
// characters at a bonus favor level flag the start, the win adds drop_type 4 drops, spends their
// bonus for the day and lowers the remaining count; a story mission gets none.
NATIVE_TEST("events/favor-drop") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        // an event mission with non-fixed drops
        u32 mission = (u32)c.m.one(
            "select m.id from master_event_mission m where (select count(*) from master_mission_drop d where d.master_mission_id = m.id and "
            "ifnull(d.is_fix_drop, 0) = 0 and ifnull(d.is_surprise_enemy, 0) = 0 and d.rate_weigh > 0) > 0 and "
            "(select count(*) from master_mission_stage s where s.master_mission_id = m.id) > 0 and "
            "(select count(*) from master_mission_npc n where n.master_mission_id = m.id) = 0 order by m.id limit 1",
            {});
        if (!mission) {
            t.fail("no event mission with drops");
            return;
        }
        // every character's favor at the top of level 4 (a: master_favor_level next_favor_point)
        int64_t pts = c.m.one("select next_favor_point from master_favor_level where id = 4", {}, 90000);
        c.st.exec("delete from favor");
        c.st.q("insert into favor (same_role_id, point) select distinct same_role_id, ? from (select 0 as same_role_id) where 0", {pts});
        std::vector<u32> sames;
        c.st.q("select distinct role_id from roster", {},
               [&](const Row& r) { sames.push_back((u32)c.m.one("select same_role_id from master_role where id = ?", {r.i("role_id")})); });
        for (u32 s : sames)
            c.st.q(
                "insert into favor (same_role_id, point) values (?, ?)"
                " on conflict(same_role_id) do update set point = excluded.point, tap_count = excluded.tap_count, "
                "tapped_at = excluded.tapped_at, event_drop_at = excluded.event_drop_at",
                {s, pts});
        Request rs;
        rs.method = "MissionStart";
        rs.ints = {1, mission, 0, 0, 0, 0, 0};
        c.st.q("update player set stamina = 999", {});
        Value d = c.core_mission(rs, nullptr);
        const Value* mp = d.find("MissionParameter");
        if (!mp || !mp->find("is_event_drop_by_favor") || !mp->find("is_event_drop_by_favor")->b) {
            t.fail("is_event_drop_by_favor not set for a level-4 party");
            c.st.exec("rollback");
            return;
        }
        int64_t used = c.st.one("select count(*) from favor_drop_play", {});
        Request re;
        re.method = "MissionEnd";
        re.ints = {mission, 0};
        d = c.core_mission(re, nullptr);
        int hearts = 0;
        if (const Value* dl = d.find("DropList"))
            for (const char* k : {"item", "character", "stock_item"})
                if (const Value* l = dl->find(k))
                    for (const Value& e : l->arr)
                        if (num(e.find("drop_type")) == 4) hearts++;
        if (!hearts) t.fail("no favor (drop_type 4) drops");
        u32 limit = c.global_u32("favor_event_drop_bonus_limit", 3);
        t.expect_eq(num(d.find("RemainingEventDropBonusCountByFavor")), (u64)(limit - used), "remaining count");
        t.expect_eq(c.st.one("select count(*) from favor where event_drop_at is not null", {}), used, "bonus spent");
        // again the same day: the spent characters give no bonus
        d = c.core_mission(rs, nullptr);
        t.expect_eq(
            c.st.one(
                "select count(*) from favor_drop_play f where f.same_role_id in (select same_role_id from favor where event_drop_at is not null)",
                {}),
            (int64_t)0, "spent characters skipped");
        c.core_mission(re, nullptr);
        c.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

// GetPlayerDetailInfo: SearchResult {player id: CFollowInfo {order, player, pc}}, the player (the
// one entrant) with a character of the roster, as the detail dialog reads it
// (CParameterUtility::CreateSearchFriendData -> tCharaData::InitializeFollow).
NATIVE_TEST("events/player-detail") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        u32 pid = c.player_id().v;
        Value d = call(c, "GetPlayerDetailInfo", {pid});
        const Value* sr = d.find("SearchResult");
        if (!sr || sr->type != Value::Map || sr->map.size() != 1) {
            t.fail("no single-entry SearchResult map");
            return;
        }
        const Value* e = sr->find(std::to_string(pid));
        if (!e) {
            t.fail("SearchResult isn't keyed by the player id");
            return;
        }
        const Value* pl = e->find("player");
        const Value* pc = e->find("pc");
        if (!pl || !pc || !e->find("order")) {
            t.fail("entry incomplete");
            return;
        }
        t.expect_eq(num(pl->find("id")), (u64)pid, "player.id");
        std::string name;
        c.st.q("select name from player", {}, [&](const Row& r) { name = r.s("name"); });
        t.expect_eq(pl->find("name") ? pl->find("name")->s : std::string("?"), name, "player.name");
        t.expect_eq(num(pc->find("player_id")), (u64)pid, "pc.player_id");
        u64 uid = num(pc->find("id"));
        u32 role = (u32)num(pc->find("master_role_id"));
        t.expect_eq((u32)c.st.one("select role_id from roster where uid = ?", {uid}), role, "pc is a roster character");
        if (!role) t.fail("pc without a role");
        // another id (a ranking row's entrant) is answered the same way
        Value d2 = call(c, "GetPlayerDetailInfo", {12345});
        t.expect_eq(d2.find("SearchResult") != nullptr, true, "any id answered");
    });
    if (!ran) t.fail("needs the 3.7.0 master and a seed save");
}

}  // namespace soa::server
