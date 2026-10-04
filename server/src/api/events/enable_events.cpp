// Enabling events by keyword (--enable-events; see enable_events.h). Port option: the
// user asked for the summer events and banners all year ("if/when possible"); the keyword list
// makes it any events. Labels: (a) master data, (b) client-side evidence, (c) outside knowledge,
// (d) assumption; docs/server-rules.md#enabling-events.
#include "api/events/enable_events.h"

#include <map>
#include <mutex>

#include "core/log.h"
#include "soaserver/config.h"
#include "soaserver/events.h"

namespace soa::server::enable_events {
using namespace ext;

const char* const kOpenedAt = "2016-01-01 00:00:00";
const char* const kClosedAt = "2037-12-31 23:59:59";

namespace {
std::mutex g_mu;
std::map<std::string, std::set<u32>>& cache() {
    static std::map<std::string, std::set<u32>> ids;
    return ids;
}

std::vector<std::string> split(const std::string& list) {
    std::vector<std::string> items;
    size_t begin = 0;
    while (begin <= list.size()) {
        size_t end = list.find(',', begin);
        if (end == std::string::npos) end = list.size();
        std::string keyword = list.substr(begin, end - begin);
        while (!keyword.empty() && (keyword.front() == ' ' || keyword.front() == '\t')) keyword.erase(0, 1);
        while (!keyword.empty() && (keyword.back() == ' ' || keyword.back() == '\t')) keyword.pop_back();
        if (!keyword.empty() && keyword != "!") items.push_back(keyword);
        begin = end + 1;
    }
    return items;
}

bool has_table(Sql& db, const char* schema, const char* table) {
    return db.one(std::string("select count(*) from ") + schema + ".sqlite_master where type = 'table' and name = ?", {table}) > 0;
}

// (a) the name of a row: master_text.text_value of its name_message_id
std::set<u32> named(Sql& master, const std::string& list, const char* schema, const char* table) {
    std::set<u32> out;
    std::string prefix = schema;
    if (!has_table(master, schema, table) || !has_table(master, schema, "master_text")) return out;
    master.q("select x.id as id, t.text_value as name from " + prefix + "." + table + " x join " + prefix +
                 ".master_text t on t.message_id = x.name_message_id",
             {}, [&](const Row& row) {
                 if (text_matches(row.s("name"), list)) out.insert((u32)row.i("id"));
             });
    return out;
}

// kind: 'a' areas, 'g' gachas, 'x' exchange shops
std::set<u32> ids_of(Sql& master, const std::string& list, char kind) {
    return kind == 'g' ? gacha_ids(master, list) : kind == 'x' ? exchange_shop_ids(master, list) : area_ids(master, list);
}
bool cached(Sql& master, u32 id, char kind) {
    if (!enabled() || !master.h) return false;
    std::string list = keywords();
    const char* file = sqlite3_db_filename(master.h, "main");
    std::string key = std::string(1, kind) + "|" + (file ? file : "") + "|" + list;
    std::lock_guard<std::mutex> l(g_mu);
    if (!file || !*file) return ids_of(master, list, kind).count(id) != 0;  // in-memory: no cache
    auto it = cache().find(key);
    if (it == cache().end()) it = cache().emplace(key, ids_of(master, list, kind)).first;
    return it->second.count(id) != 0;
}
}  // namespace

bool enabled() { return config().enable_events; }

std::string keywords() { return config().event_keywords.empty() ? std::string(kDefaultEventKeywords) : config().event_keywords; }

bool text_matches(const std::string& text, const std::string& list) {
    bool hit = false;
    for (const std::string& keyword : split(list)) {
        if (keyword[0] == '!') {
            if (text.find(keyword.substr(1)) != std::string::npos) return false;
        } else if (text.find(keyword) != std::string::npos) {
            hit = true;
        }
    }
    return hit;
}

std::set<u32> area_ids(Sql& master, const std::string& list, const char* schema) { return named(master, list, schema, "master_event_area"); }

std::set<u32> gacha_ids(Sql& master, const std::string& list, const char* schema) {
    std::set<u32> out = named(master, list, schema, "master_gacha");
    if (out.empty()) return out;
    // (a) the gachas sharing a matching gacha's banner_id are the same banner (step-up steps,
    // single / 10-draw variants), even where their own name lacks the keyword
    std::string prefix = schema;
    std::set<std::string> banners;
    for (u32 id : out)
        master.q("select banner_id from " + prefix + ".master_gacha where id = ? and ifnull(banner_id, '') != ''", {id},
                 [&](const Row& row) { banners.insert(row.s("banner_id")); });
    // (d) the keyword's exclusions still apply to such a sibling
    master.q("select g.id as id, g.banner_id as b, ifnull(t.text_value, '') as name from " + prefix + ".master_gacha g left join " + prefix +
                 ".master_text t on t.message_id = g.name_message_id",
             {}, [&](const Row& row) {
                 if (!banners.count(row.s("b"))) return;
                 std::string name = row.s("name");
                 bool excluded = false;
                 for (const std::string& keyword : split(list))
                     if (keyword[0] == '!' && name.find(keyword.substr(1)) != std::string::npos) excluded = true;
                 if (!excluded) out.insert((u32)row.i("id"));
             });
    return out;
}

std::set<u32> exchange_shop_ids(Sql& master, const std::string& list, const char* schema) {
    std::set<u32> out;
    std::string prefix = schema;
    if (!has_table(master, schema, "master_exchange_shop") || !has_table(master, schema, "master_exchange_shop_contents") ||
        !has_table(master, schema, "master_event_mission"))
        return out;
    std::set<u32> areas = area_ids(master, list, schema);
    if (areas.empty()) return out;
    // (a) the sources of every shop currency: the event area of an event mission that drops it or
    // gives it on clear, or 0 for any other source (other mission tables, common / campaign drops)
    std::string src;
    auto add = [&](const std::string& sel) { src += (src.empty() ? "" : " union all ") + sel; };
    for (const char* t : {"master_mission_drop", "master_mission_clear_present"}) {
        if (!has_table(master, schema, t)) continue;
        add("select d.content_id as item, e.master_event_area_id as area from " + prefix + "." + t + " d join " + prefix +
            ".master_event_mission e on e.id = d.master_mission_id");
        for (const char* mt : {"master_mission", "master_tower_mission", "master_world_map_mission", "master_training_mission"})
            if (has_table(master, schema, mt))
                add("select d.content_id, 0 from " + prefix + "." + t + " d where d.master_mission_id in (select id from " + prefix + "." + mt + ")");
    }
    for (const char* t : {"master_common_drop", "master_campaign_drop"})
        if (has_table(master, schema, t)) add(std::string("select content_id, 0 from ") + prefix + "." + t);
    if (src.empty()) return out;
    std::map<u32, std::set<u32>> sources;  // currency -> areas (0: not an event area)
    master.q("select distinct x.item as item, x.area as area from (" + src + ") x where x.item in (select ex_item_id from " + prefix +
                 ".master_exchange_shop_contents)",
             {}, [&](const Row& row) { sources[(u32)row.i("item")].insert((u32)row.i("area")); });
    for (auto& [item, from] : sources) {
        bool own = true;
        for (u32 begin : from) own = own && areas.count(begin);
        if (!own) continue;
        // (d) the latest of the coin's shops (reruns re-issue the shop under a new id)
        master.q("select s.id as id from " + prefix + ".master_exchange_shop s where s.id in (select master_exchange_shop_id from " + prefix +
                     ".master_exchange_shop_contents where ex_item_id = ?) order by ifnull(s.opened_at, '') desc, s.id desc limit 1",
                 {item}, [&](const Row& row) { out.insert((u32)row.i("id")); });
    }
    return out;
}

bool gacha_shown(Sql& master, u32 id, const char* schema) {
    std::string prefix = schema;
    std::string image;
    master.q("select ifnull(b.image, '') as image from " + prefix + ".master_gacha g left join " + prefix +
                 ".master_banner b on b.id_label = g.banner_id where g.id = ?",
             {id}, [&](const Row& row) { image = row.s("image"); });
    // (b)+(d) the gacha list shows master_banner.image as the banner (Image/<image>.aif); without it
    // the list row is an empty frame with only the date (seen on screen), so such a gacha isn't
    // opened. Box gachas too: they are listed on the イベントガチャ tab by their banner (seen on
    // screen: empty "ボックス 1" frames), and the event menu's ボックスガチャ button opens that tab
    return !image.empty() && events::asset_available("Image/" + image + ".aif");
}

std::set<u32> shown_gacha_ids(Sql& master, const std::string& list, const char* schema) {
    std::set<u32> out;
    for (u32 g : gacha_ids(master, list, schema))
        if (gacha_shown(master, g, schema)) out.insert(g);
    return out;
}

bool area(Sql& master, u32 id) { return cached(master, id, 'a'); }
bool gacha(Sql& master, u32 id) { return cached(master, id, 'g') && gacha_shown(master, id); }
bool exchange_shop(Sql& master, u32 id) { return cached(master, id, 'x'); }

namespace {

// What client_master changes, and how many rows.
struct ClientMasterEdit {
    Sql& db;
    int changed = 0;
    void run(const std::string& sql, std::initializer_list<Arg> args) {
        db.q(sql, args);
        changed += sqlite3_changes(db.h);
    }
};

// The enabled areas: their terms, their dated windows and missions; their banner ids into `banner_ids`.
void open_areas(ClientMasterEdit& edit, const std::set<u32>& areas, std::set<u32>& banner_ids) {
    Sql& db = edit.db;
    std::string day0 = std::string(kOpenedAt).substr(0, 10), day1 = std::string(kClosedAt).substr(0, 10);
    if (has_table(db, "main", "master_event_term"))
        for (u32 area : areas)
            // (b) GetEventAreaList builds opened_day opened_time .. closed_day closed_time
            edit.run(
                "update master_event_term set opened_day = ?, opened_time = '00:00:00', closed_day = ?, closed_time = '23:59:59' "
                "where master_event_area_id = ?",
                {day0, day1, area});
    for (u32 area : areas) {
        if (has_table(db, "main", "master_event_area")) {
            // (b) the area's own dated window, when it has one (most are empty)
            edit.run("update master_event_area set opened_at = ? where id = ? and ifnull(opened_at, '') != ''", {kOpenedAt, area});
            edit.run("update master_event_area set closed_at = ? where id = ? and ifnull(closed_at, '') != ''", {kClosedAt, area});
            db.q("select master_banner_id from master_event_area where id = ? and master_banner_id is not null", {area},
                 [&](const Row& area_row) { banner_ids.insert((u32)area_row.i("master_banner_id")); });
        }
        if (has_table(db, "main", "master_event_mission")) {
            // (b) GetEventMissionList / CTimeUtility::IsEnableTime: the missions' own windows
            edit.run("update master_event_mission set opened_at = ? where master_event_area_id = ? and ifnull(opened_at, '') != ''",
                     {kOpenedAt, area});
            edit.run("update master_event_mission set closed_at = ? where master_event_area_id = ? and ifnull(closed_at, '') != ''",
                     {kClosedAt, area});
        }
    }
}

// The enabled gachas' windows; their banner labels into `banners`.
void open_gachas(ClientMasterEdit& edit, const std::set<u32>& gachas, std::set<std::string>& banners) {
    Sql& db = edit.db;
    if (!has_table(db, "main", "master_gacha")) return;
    for (u32 gacha : gachas) {
        // (b) CGacha::IsEnableHash: the master row's opened_at / closed_at must hold the clock
        edit.run("update master_gacha set opened_at = ?, closed_at = ? where id = ?", {kOpenedAt, kClosedAt, gacha});
        db.q("select banner_id from master_gacha where id = ? and ifnull(banner_id, '') != ''", {gacha},
             [&](const Row& gacha_row) { banners.insert(gacha_row.s("banner_id")); });
    }
}

// (d) the banners of the enabled areas and gachas (master_gacha.banner_id = master_banner.id_label,
// docs/notes.md) get the same window, in case the client checks them too
void open_banners(ClientMasterEdit& edit, const std::set<std::string>& banners, const std::set<u32>& banner_ids) {
    if (!has_table(edit.db, "main", "master_banner")) return;
    for (const std::string& banner : banners)
        edit.run("update master_banner set opened_at = ?, closed_at = ? where id_label = ?", {kOpenedAt, kClosedAt, banner});
    for (u32 banner : banner_ids) edit.run("update master_banner set opened_at = ?, closed_at = ? where id = ?", {kOpenedAt, kClosedAt, banner});
}

// (b) CShop::Progress / CUIUtility::CollectMasterItemExchangeShop list the shops open by the client
// clock, and the contents by their opened_at
void open_exchange_shops(ClientMasterEdit& edit, const std::set<u32>& shops) {
    Sql& db = edit.db;
    if (!has_table(db, "main", "master_exchange_shop")) return;
    for (u32 shop : shops) {
        edit.run("update master_exchange_shop set opened_at = ?, closed_at = ? where id = ?", {kOpenedAt, kClosedAt, shop});
        if (has_table(db, "main", "master_exchange_shop_contents"))
            edit.run("update master_exchange_shop_contents set opened_at = ? where master_exchange_shop_id = ? and ifnull(opened_at, '') != ''",
                     {kOpenedAt, shop});
    }
}

}  // namespace

int client_master(Sql& db, const char* srv) {
    if (!enabled()) return 0;
    std::string list = keywords();
    std::set<u32> areas = area_ids(db, list, srv), gachas = shown_gacha_ids(db, list, srv), shops = exchange_shop_ids(db, list, srv);
    ClientMasterEdit edit{db};
    std::set<std::string> banners;  // master_banner id_labels
    std::set<u32> banner_ids;       // master_banner ids
    open_areas(edit, areas, banner_ids);
    open_gachas(edit, gachas, banners);
    open_banners(edit, banners, banner_ids);
    open_exchange_shops(edit, shops);
    LOGI("server", "enable-events (\"%s\"): %zu event areas, %zu gachas and %zu exchange shops opened in the client's master (%d rows)", list.c_str(),
         areas.size(), gachas.size(), shops.size(), edit.changed);  // read by summer_demo.sh
    return edit.changed;
}

}  // namespace soa::server::enable_events
