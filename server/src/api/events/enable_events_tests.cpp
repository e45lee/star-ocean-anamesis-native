// Unit tests of --enable-events (enable_events.cpp, the event module's use of it; --selftest
// "events/enable-"; names were server/enable-events-* before R18). Not differential (the server has
// no guest counterpart). The gacha list test is api/gacha/'s (gacha/enable-events), --start-coins
// api/entry/'s (entry/start-coins).
#include <sqlite3.h>

#include <ctime>
#include <set>
#include <vector>

#include "soaserver/cdn.h"
#include "soaserver/config.h"
#include "soaserver/hooks.h"
#include "soaserver/native_test.h"
#include "api/events/enable_events.h"
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

// Restores the run's options (the tests switch enable_events / event_keywords).
struct KeepOptions {
    ServerConfig saved = config();
    ~KeepOptions() {
        config().enable_events = saved.enable_events;
        config().event_keywords = saved.event_keywords;
    }
};
struct Assets {
    explicit Assets(bool all) {
        events::set_asset_check([all](const std::string&) { return all; });
    }
    ~Assets() { events::set_asset_check({}); }
};

std::set<std::string> labels(Sql& m, const char* table, const std::set<u32>& ids) {
    std::set<std::string> out;
    for (u32 id : ids) m.q(std::string("select id_label from ") + table + " where id = ?", {id}, [&](const Row& r) { out.insert(r.s("id_label")); });
    return out;
}

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

}  // namespace

// The keyword matching, and what the default list (the summer events) matches in the 3.7.0 master.
NATIVE_TEST("events/enable-keywords") {
    using enable_events::text_matches;
    t.expect_eq(text_matches("水着イベント2019前半", "水着,夏"), true, "contains one");
    t.expect_eq(text_matches("クリスマスイベント2019", "水着,夏"), false, "contains none");
    t.expect_eq(text_matches("2018年福袋限定チケットガチャ(花嫁/水着/ハロウィンのみ)", "水着,!福袋"), false, "excluded");
    t.expect_eq(text_matches("常夏キャラピックアップガチャ", " 水着 , 夏 ,,"), true, "spaces and empty items");
    t.expect_eq(text_matches("anything", ""), false, "empty list");
    t.expect_eq(text_matches("anything", "!x"), false, "exclusions alone match nothing");
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        std::set<u32> areas = enable_events::area_ids(c.m, kDefaultEventKeywords);
        std::set<std::string> al = labels(c.m, "master_event_area", areas);
        // (the user's expected summer events; the set is derived from the names, this only checks it)
        for (const char* want :
             {"event_sum_22", "event_sum_23", "event_sum_49", "event_sum_50", "event_sww2019_75", "event_sww2019_76", "event_sww2020_93"})
            if (!al.count(want)) t.fail("default keywords miss %s", want);
        std::string all;
        for (auto& l : al) all += l + " ";
        fprintf(stderr, "    %zu event areas: %s\n", al.size(), all.c_str());
        std::set<u32> gachas = enable_events::gacha_ids(c.m, kDefaultEventKeywords);
        int bad = 0, box = 0;
        for (u32 g : gachas) {
            std::string name;
            c.m.q(
                "select ifnull(t.text_value, '') as n from master_gacha g left join master_text t on t.message_id = g.name_message_id where g.id = ?",
                {g}, [&](const Row& r) { name = r.s("n"); });
            if (name.find("福袋") != std::string::npos) bad++;
            box += (int)c.m.one("select ifnull(is_box, 0) from master_gacha where id = ?", {g});
        }
        t.expect_eq(bad, 0, "no 福袋 gacha");
        if (gachas.size() < 100) t.fail("only %zu gachas matched", gachas.size());
        fprintf(stderr, "    %zu gachas (%d box gachas)\n", gachas.size(), box);
        // the 福袋 ticket gacha naming 水着 exists and is left out
        int fuku = 0;
        c.m.q(
            "select g.id as id from master_gacha g join master_text t on t.message_id = g.name_message_id where t.text_value like '%福袋%' "
            "and t.text_value like '%水着%'",
            {}, [&](const Row& r) { fuku += gachas.count((u32)r.i("id")) ? 100 : 1; });
        if (fuku == 0 || fuku >= 100) t.fail("the 福袋 exclusion (%d)", fuku);
    });
    if (!ran) t.fail("no scratch server");
}

// Event areas: with the option, the matching areas are listed at a clock and calendar outside
// their terms (assets permitting); without it, none is. The client's master copy gets their
// terms, missions and gachas widened.
NATIVE_TEST("events/enable-areas") {
    KeepOptions keep;
    ServerConfig& opt = config();
    opt.event_keywords.clear();
    // 2026-01-15 on the client's clock, the calendar in 2021-01: no summer term runs
    ServerTime now(T("2026-01-15 12:00:00"));
    EventTime ev(T("2021-01-15 12:00:00"));
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        std::set<u32> want = enable_events::area_ids(c.m, kDefaultEventKeywords);
        auto listed = [&]() {
            std::set<u32> ids;
            for (auto& a : events::open_areas(c, now, ev))
                if (want.count(a.id)) ids.insert(a.id);
            return ids;
        };
        Assets all(true);
        opt.enable_events = false;
        t.expect_eq(listed().size(), (size_t)0, "without the option: no matching area");
        opt.enable_events = true;
        std::set<u32> on = listed();
        size_t with_missions = 0;
        for (u32 a : want) with_missions += c.m.one("select count(*) from master_event_mission where master_event_area_id = ?", {a}) > 0;
        t.expect_eq(on.size(), with_missions, "with the option: every matching area with missions");
        events::set_asset_check([](const std::string&) { return false; });
        t.expect_eq(listed().size(), (size_t)0, "no assets: none (the runtime gating still applies)");
        events::set_asset_check({});
        fprintf(stderr, "    with this run's assets: %zu of the %zu matching areas playable\n", listed().size(), want.size());
        events::set_asset_check([](const std::string&) { return true; });
        // the ActiveEventMissionList carries them
        Value v = events::active_event_mission_list(c, now, ev);
        const Value* ea = v.find("EventArea");
        size_t n = 0;
        if (ea)
            for (auto& kv : ea->map) n += want.count((u32)std::stoul(kv.first));
        if (n != on.size())
            t.fail("ActiveEventMissionList.EventArea: %zu matching areas, want %zu (%zu keys)", n, on.size(), ea ? ea->map.size() : (size_t)0);

        // the client's master copy, through the event module's ClientMaster (after its year shift)
        sqlite3* db = nullptr;
        sqlite3_open(":memory:", &db);
        Sql cm{db};
        cm.exec(std::string("attach '") + sqlite3_db_filename(c.m.h, "main") + "' as src");
        for (const char* tb : {"master_event_term", "master_event_area", "master_event_mission", "master_banner", "master_gacha", "master_text",
                               "master_event_weekly", "master_campaign"})
            cm.exec(std::string("create table ") + tb + " as select * from src." + tb);
        cm.exec("detach src");
        client_master(db, now, ev);
        std::string today = "2026-01-15";
        int open_terms = 0;
        for (u32 a : want)
            open_terms += cm.one("select count(*) from master_event_term where master_event_area_id = ? and opened_day <= ? and closed_day >= ?",
                                 {a, today, today}) > 0;
        t.expect_eq(open_terms, (int)want.size(), "every matching area's term covers the client clock");
        std::set<u32> gachas = enable_events::shown_gacha_ids(c.m, kDefaultEventKeywords);  // (every asset present here)
        int open_g = 0;
        for (u32 g : gachas)
            open_g += cm.one("select count(*) from master_gacha where id = ? and opened_at <= ? and closed_at >= ?", {g, today, today}) > 0;
        t.expect_eq(open_g, (int)gachas.size(), "every matching gacha's window covers the client clock");
        // the other areas keep the year shift only (a non-matching term moved 5 years)
        int64_t other = cm.one(
            "select count(*) from master_event_term where master_event_area_id not in (select id from master_event_area where "
            "name_message_id in (select message_id from master_text where text_value like '%水着%')) and closed_day > '2030'",
            {});
        int64_t other_src = c.m.one("select count(*) from master_event_term where closed_day > '2025'", {});
        t.expect_eq(other, other_src, "other terms: the year shift only");
        sqlite3_close(db);
        opt.enable_events = false;
        sqlite3_open(":memory:", &db);
        Sql cm2{db};
        cm2.exec(std::string("attach '") + sqlite3_db_filename(c.m.h, "main") + "' as src");
        cm2.exec("create table master_gacha as select * from src.master_gacha");
        cm2.exec("detach src");
        t.expect_eq(enable_events::client_master(cm2), 0, "off: the client's master untouched");
        sqlite3_close(db);
    });
    if (!ran) t.fail("no scratch server");
}

// Exchange shops (A2): the matching events' coin shops, linked through their currency (a coin the
// matching areas' missions drop and nothing else gives), are listed and exchange outside their
// dated window with the option, and not without it; the client's master copy gets their window.
NATIVE_TEST("events/enable-exchange-shops") {
    KeepOptions keep;
    ServerConfig& opt = config();
    opt.event_keywords.clear();
    ServerTime now(T("2026-01-15 12:00:00"));
    EventTime ev(T("2021-01-15 12:00:00"));
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        c.test.now = [&] { return now.v; };
        c.test.event_now = [&] { return ev.v; };
        std::set<u32> shops = enable_events::exchange_shop_ids(c.m, kDefaultEventKeywords);
        std::set<std::string> sl = labels(c.m, "master_exchange_shop", shops);
        std::string all;
        for (auto& l : sl) all += l + " ";
        fprintf(stderr, "    %zu exchange shops: %s\n", sl.size(), all.c_str());
        if (shops.size() < 5) t.fail("only %zu summer exchange shops", shops.size());
        // one shop per currency, and no currency that other areas' missions drop (the revival coins)
        std::set<u32> areas = enable_events::area_ids(c.m, kDefaultEventKeywords);
        std::set<u32> coins;
        for (u32 x : shops)
            c.m.q("select distinct ex_item_id as i from master_exchange_shop_contents where master_exchange_shop_id = ?", {x},
                  [&](const Row& r) { coins.insert((u32)r.i("i")); });
        if (coins.size() < shops.size()) t.fail("%zu shops share %zu currencies", shops.size(), coins.size());
        for (u32 i : coins)
            c.m.q(
                "select distinct e.master_event_area_id as a from master_mission_drop d join master_event_mission e on e.id = d.master_mission_id "
                "where d.content_id = ?",
                {i}, [&](const Row& r) {
                    if (!areas.count((u32)r.i("a"))) t.fail("currency %u also drops in area %lld", i, (long long)r.i("a"));
                });
        u32 shop = 0, row = 0, coin = 0, price = 0;
        for (u32 x : shops) {
            c.m.q(
                "select id, ex_item_id, ex_num from master_exchange_shop_contents where master_exchange_shop_id = ? and ex_num > 0 order by order_id, id limit 1",
                {x}, [&](const Row& r) {
                    row = (u32)r.i("id");
                    coin = (u32)r.i("ex_item_id");
                    price = (u32)r.i("ex_num");
                });
            if (row) {
                shop = x;
                break;
            }
        }
        if (!shop) {
            t.fail("no enabled shop with a contents row");
            c.st.exec("rollback");
            return;
        }
        auto listed = [&]() {
            Value d = call(c, "ExshopExchangeList", {});
            const Value* m = d.find("ExchangeShopExCount");
            return m && m->find(std::to_string(shop)) != nullptr;
        };
        add_stock(c, coin, price);
        opt.enable_events = false;
        t.expect_eq(listed(), false, "off: the shop keeps its dated window");
        t.expect_eq(call(c, "ExshopExchange", {row, 1}).find("ExchangeResult") != nullptr, false, "off: no exchange");
        opt.enable_events = true;
        t.expect_eq(listed(), true, "on: listed");
        u32 before = stock_count(c, coin);
        Value d = call(c, "ExshopExchange", {row, 1});
        t.expect_eq(d.find("ExchangeResult") != nullptr, true, "on: exchanged");
        t.expect_eq(stock_count(c, coin), before - price, "paid in the event coin");

        // the client's master copy
        sqlite3* db = nullptr;
        sqlite3_open(":memory:", &db);
        Sql cm{db};
        cm.exec(std::string("attach '") + sqlite3_db_filename(c.m.h, "main") + "' as srv");
        for (const char* tb : {"master_exchange_shop", "master_exchange_shop_contents"})
            cm.exec(std::string("create table main.") + tb + " as select * from srv." + tb);
        enable_events::client_master(cm, "srv");
        int open = 0;
        for (u32 x : shops)
            open += (int)cm.one("select count(*) from master_exchange_shop where id = ? and opened_at = ? and closed_at = ?",
                                {x, enable_events::kOpenedAt, enable_events::kClosedAt});
        t.expect_eq(open, (int)shops.size(), "every enabled shop's window opened in the client's copy");
        t.expect_eq(cm.one("select count(*) from master_exchange_shop where closed_at = ?", {enable_events::kClosedAt}), (int64_t)shops.size(),
                    "no other shop");
        cm.exec("detach srv");
        sqlite3_close(db);
        c.st.exec("rollback");
    });
    if (!ran) t.fail("no scratch server");
}

// soa-server's asset index (cdn::asset_index_from_config, server/app/main.cpp) holds the stand-ins
// the CDN serves, so the banner gate opens gacha_pickup_role_0054 / _0056, whose list banners only
// standin-assets has (docs/server-rules.md#enabling-events); --standin-assets off leaves them shut.
NATIVE_TEST("events/enable-standin-banners") {
    KeepOptions keep;
    ServerConfig& opt = config();
    struct KeepCdn {
        ServerConfig saved = config();
        std::shared_ptr<const AssetIndex> index;
        ~KeepCdn() {
            config().download_dir = saved.download_dir;
            config().cdn_standins = saved.cdn_standins;
            config().standin_dir = saved.standin_dir;
            set_asset_index(index);
        }
    } keep_cdn;
    std::string download = find_repo_file("work/download-3.7.0"), standins = find_repo_file("standin-assets");
    if (download.empty() || standins.empty()) return t.skip("work/download-3.7.0 or standin-assets not found (the 3.7.0 download: local data)");
    events::set_asset_check({});
    keep_cdn.index = set_asset_index(nullptr);  // put back by ~KeepCdn (soa: its AssetManager)
    opt.download_dir = download;
    opt.standin_dir.clear();
    opt.event_keywords.clear();
    opt.enable_events = true;
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        std::vector<u32> ids;
        for (const char* g : {"gacha_pickup_role_0054", "gacha_pickup_role_0056"}) {
            u32 id = (u32)c.m.one("select id from master_gacha where id_label = ?", {std::string(g)});
            if (!id) t.fail("%s not in the master", g);
            else ids.push_back(id);
        }
        const char* banner = "builtin_data/Image/etc2/banner_gacha_pickup_role_0054.aif";
        for (bool on : {true, false}) {
            opt.cdn_standins = on;
            set_asset_index(cdn::asset_index_from_config());
            t.expect_eq(cdn::standin_dir_from_config().empty(), !on, on ? "stand-ins on: their dir" : "off: no dir");
            t.expect_eq(asset_index().exists(banner), on, on ? "stand-ins on: the 0054 banner indexed" : "off: not indexed");
            for (u32 id : ids) {
                t.expect_eq(enable_events::gacha_shown(c.m, id), on, on ? "stand-ins on: the gacha's banner found" : "off: no banner");
                t.expect_eq(enable_events::gacha(c.m, id), on, on ? "stand-ins on: opened" : "off: not opened");
            }
        }
    });
    if (!ran) t.fail("no scratch server");
}

}  // namespace soa::server
