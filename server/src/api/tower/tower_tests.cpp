// Unit tests of the tower module (api/tower/tower.cpp, --restore-tower; --selftest
// "tower/"). Not differential (the server has no guest counterpart): the stand-in banner
// rule (through an injected asset predicate, never a list of names), the client-master rows, and
// the lists on a scratch server seeded from the test seed save.
#include <sqlite3.h>

#include <set>
#include <string>

#include "soaserver/native_test.h"
#include "soaserver/events.h"
#include "soaserver/ext.h"
#include "api/tower/tower.h"

namespace soa::server {
namespace {
using namespace ext;

// Only the images named in `have` exist.
void only_images(std::set<std::string> have) {
    events::set_asset_check([have](const std::string& rel) { return rel.rfind("Image/", 0) != 0 || have.count(rel) != 0; });
}
u64 num(const Value* v) { return !v ? 0 : v->type == Value::Int ? (u64)v->i : v->u; }

}  // namespace

NATIVE_TEST("tower/banner") {
    only_images({"Image/banner_TrialSpace_003.aif", "Image/banner_TrialSpace_004_002.aif", "Image/banner_TrialSpace_004_001.aif",
                 "Image/banner_TrialSpace_005_001.aif"});
    t.expect_eq(tower::standin_banner_image("tower_03"), std::string("banner_TrialSpace_003"), "plain name first");
    t.expect_eq(tower::standin_banner_image("tower_04"), std::string("banner_TrialSpace_004_002"), "_002 before _001");
    t.expect_eq(tower::standin_banner_image("tower_05"), std::string("banner_TrialSpace_005_001"), "_001 last");
    t.expect_eq(tower::standin_banner_image("tower_01"), std::string(""), "no image, no stand-in");
    t.expect_eq(tower::standin_banner_image("tower"), std::string(""), "no number");
    t.expect_eq(tower::standin_banner_image("tower_x"), std::string(""), "not a number");
    events::set_asset_check({});
}

// The client's master copy: a row for each tower area whose banner row is missing and whose
// image exists; existing rows untouched.
NATIVE_TEST("tower/client-master") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        sqlite3* db = nullptr;
        sqlite3_open(":memory:", &db);
        Sql cm{db};
        cm.exec(std::string("attach '") + sqlite3_db_filename(c.m.h, "main") + "' as src");
        for (const char* tb : {"master_tower_area", "master_banner"}) cm.exec(std::string("create table ") + tb + " as select * from src." + tb);
        cm.exec("detach src");
        int64_t banners0 = cm.one("select count(*) from master_banner", {});
        // the areas whose banner row is missing, and the number of those with a derivable image
        int64_t missing = cm.one(
            "select count(*) from master_tower_area a where coalesce(a.master_banner_id, 0) != 0 and "
            "not exists (select 1 from master_banner b where b.id = a.master_banner_id)",
            {});
        events::set_asset_check([](const std::string&) { return true; });
        int added = tower::client_banners(cm);
        t.expect_eq((int64_t)added, missing, "a row per missing banner (every image present)");
        t.expect_eq(cm.one("select count(*) from master_banner", {}), banners0 + added, "rows added");
        t.expect_eq(cm.one("select count(*) from master_tower_area a where coalesce(a.master_banner_id, 0) != 0 and "
                           "not exists (select 1 from master_banner b where b.id = a.master_banner_id)",
                           {}),
                    (int64_t)0, "every banner id resolves");
        t.expect_eq(tower::client_banners(cm), 0, "idempotent");
        // each added row's image follows its area's number
        int bad = 0;
        cm.q("select a.id_label, b.image from master_tower_area a join master_banner b on b.id = a.master_banner_id where b.url = ''", {},
             [&](const Row& r) {
                 std::string want = tower::standin_banner_image(r.s("id_label"));
                 if (r.s("image") != want) bad++;
             });
        t.expect_eq(bad, 0, "images from the area numbers");
        sqlite3_close(db);

        // No image anywhere: nothing added.
        sqlite3_open(":memory:", &db);
        Sql cm2{db};
        cm2.exec(std::string("attach '") + sqlite3_db_filename(c.m.h, "main") + "' as src");
        for (const char* tb : {"master_tower_area", "master_banner"}) cm2.exec(std::string("create table ") + tb + " as select * from src." + tb);
        cm2.exec("detach src");
        only_images({});
        t.expect_eq(tower::client_banners(cm2), 0, "no images, no rows");
        sqlite3_close(db);
        events::set_asset_check({});
    });
    if (!ran) fprintf(stderr, "    (no scratch server; skipped)\n");
}

// The lists: the open areas the client can show, the first floor of each, the next floor after a
// clear, the try count.
NATIVE_TEST("tower/lists") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        events::set_asset_check([](const std::string&) { return true; });
        c.st.exec("delete from mission");
        Value d = Value::object();
        d["Player"] = Value::object();
        tower::lists(c, d);
        const Value* at = d.find("ActiveTowerMissionList");
        const Value* areas = at ? at->find("TowerArea") : nullptr;
        const Value* missions = at ? at->find("TowerMission") : nullptr;
        if (!areas || !missions) {
            t.fail("no ActiveTowerMissionList");
            return;
        }
        // (a) the open areas: opened_at <= calendar <= closed_at
        int64_t now = c.event_now().v;
        std::set<std::string> open;
        c.m.q("select id, opened_at, closed_at, master_banner_id from master_tower_area", {}, [&](const Row& r) {
            if (!r.i("master_banner_id")) return;
            std::string o = r.s("opened_at"), cl = r.s("closed_at");
            if ((!o.empty() && c.parse_time(o) > now) || (!cl.empty() && c.parse_time(cl) < now)) return;
            open.insert(std::to_string(r.i("id")));
        });
        t.expect_eq(areas->map.size(), open.size(), "every open area with a banner listed");
        if (open.empty()) t.fail("no open tower area in the master data");
        int multi = 0;
        for (auto& [k, v] : missions->map) {
            if (!open.count(k)) t.fail("a closed area listed");
            if (v.arr.size() != 1) multi++;
        }
        t.expect_eq(multi, 0, "one floor per area before any clear");
        t.expect_eq(num(d.find("Player")->find("tower_try_count")), (u64)c.global_u32("Tower_Challenge_Count", 3), "try count");

        // clear the first floor of one area: the floor it unlocks is listed, the first is is_clear
        std::string area = missions->map.front().first;
        u32 first = (u32)num(missions->map.front().second.arr[0].find("id"));
        u32 next =
            (u32)c.m.one("select id from master_tower_mission where unlock_mission_id = ? and master_tower_area_id = ?", {first, std::stoll(area)});
        c.st.q(
            "insert into mission (mission_id, cleared) values (?, 1)"
            " on conflict(mission_id) do update set cleared = excluded.cleared, "
            "play_count = excluded.play_count, clear_count = excluded.clear_count, "
            "first_clear_at = excluded.first_clear_at",
            {first});
        Value d2 = Value::object();
        tower::lists(c, d2);
        const Value* l = d2.find("ActiveTowerMissionList")->find("TowerMission")->find(area);
        if (!l) {
            t.fail("area gone after a clear");
            return;
        }
        if (next) {
            t.expect_eq(l->arr.size(), (size_t)2, "the next floor unlocked");
            bool clear = false;
            for (auto& e : l->arr)
                if (num(e.find("id")) == first) clear = e.find("is_clear") && e.find("is_clear")->b;
            t.expect_eq(clear, true, "the first floor is_clear");
        }

        // no banner images: the areas without a banner row aren't listed
        only_images({});
        Value d3 = Value::object();
        tower::lists(c, d3);
        size_t with_row = 0;
        c.m.q("select id, master_banner_id from master_tower_area", {}, [&](const Row& r) {
            if (open.count(std::to_string(r.i("id"))) && c.m.one("select count(*) from master_banner where id = ?", {r.i("master_banner_id")}))
                with_row++;
        });
        t.expect_eq(d3.find("ActiveTowerMissionList")->find("TowerArea")->map.size(), with_row, "only areas with a banner row");
        c.st.exec("delete from mission");
        events::set_asset_check({});
    });
    if (!ran) fprintf(stderr, "    (no scratch server; skipped)\n");
}

}  // namespace soa::server
