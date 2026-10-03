// Event missions (soaserver/events.h). Port code, not guest behaviour. The event menu of the unchanged
// client (home -> イベント, CEventMissionMenu) lists what the server's ActiveEventMissionList names
// and its own master copy allows at the client's clock; the battles are master_event_mission rows
// played through the core MissionStart / MissionEnd (api/missions/), the story scenes end through the
// client's EndMissionTalk (CEventScenario::Exit -> events::end_mission_talk). Rules in
// docs/server-rules.md "Events"; labels:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// Client facts this module builds on ((b), docs/notes.md "Events"):
//  - the home's event button needs FooterMissionInfo.is_open_event_mission (api/player/home_footer.cpp) and
//    goes to CPhase_Mission with mission type 1, which sends no request for it: CEventMissionMenu
//    reads the ActiveEventMissionList the client already holds (CParameterManager+0x1d40
//    EventArea = InfoBaseNumberMap<CAreaInfo>, +0x1d90 EventMission = InfoBaseNumberMap<
//    CMissionInfoList>), so every response that can change it carries it;
//  - MissionUtility::GetEventAreaList keeps only the listed areas whose master_event_term /
//    master_event_weekly row covers the client's clock (CTimeUtility::NowTime = data.Time plus
//    the device's elapsed time), and GetEventMissionList the missions whose opened_at..closed_at
//    does; so the dated tables are moved into the client's years (ext::ClientMaster below);
//  - CUIUtility::GetCampaignSituation* read CampaignInfo (CParameterManager+0x74f8,
//    InfoBaseArray<CCampaignInfo>) and compare its opened_at / closed_at with the client clock.
#include "soaserver/events.h"

#include <cstdio>
#include <cstring>
#include <ctime>
#include <map>
#include <mutex>
#include <set>

#include "soaserver/hooks.h"
#include "core/log.h"
#include "core/time.h"
#include "core/assets.h"
#include "api/events/enable_events.h"
#include "core/modules.h"
#include "soaserver/ext.h"

namespace soa::server::events {
namespace {
using namespace ext;

// (d) our state: the last event mission started (is_last_play). Clears are the core's `mission`
// table (MissionEnd / MissionTalk / end_mission_talk).
const char* const kSchema = "create table if not exists event_last (id integer primary key check (id = 1), mission_id integer, area_id integer)";

// ---- assets ------------------------------------------------------------------------------
// The one asset gate (core/assets.h): the tests' override, else everything when there is no asset
// source at all (outside the game: nothing is gated rather than everything), else the index.
bool have(const std::string& rel) { return assets::available(rel); }
// The mission verdicts, valid for one asset override (assets::generation).
std::mutex g_cache_mu;
std::map<u32, bool>& playable_cache() {
    static std::map<u32, bool> verdicts;
    static uint64_t generation = 0;
    if (generation != assets::generation()) {
        verdicts.clear();
        generation = assets::generation();
    }
    return verdicts;
}

std::vector<std::function<void(Ctx&, u32, Value&)>>& area_extras() {
    static std::vector<std::function<void(Ctx&, u32, Value&)>> v;
    return v;
}

}  // namespace

// ---- clocks ------------------------------------------------------------------------------
int year_shift(int64_t now, int64_t ev) { return year_of(now) - year_of(ev); }

std::string shift_years(const std::string& s, int years) {
    if (!years || s.size() < 5 || s[4] != '-') return s;
    for (int k = 0; k < 4; k++)
        if (s[k] < '0' || s[k] > '9') return s;
    char y[8];
    snprintf(y, sizeof y, "%04d", atoi(s.substr(0, 4).c_str()) + years);
    return y + s.substr(4);
}

int64_t shift_time(int64_t t, int years) { return years ? parse_time(shift_years(format_time(t), years)) : t; }
int client_years(Ctx& ctx) { return year_shift(ctx.now(), ctx.event_now()); }

bool window_open(const std::string& opened, const std::string& closed, int years, int64_t t) {
    // (a) the master's local date-times; shifted as the client's copy is (the client parses them
    // with CTimeUtility::str2time_t, so Feb 29 of a common year normalises the same way).
    if (!opened.empty() && parse_time(shift_years(opened, years)) > t) return false;
    if (!closed.empty() && parse_time(shift_years(closed, years)) < t) return false;
    return true;
}

// ---- assets --------------------------------------------------------------------------------
// The one asset gate's override and lookup (core/assets.h).
void set_asset_check(AssetCheck fn) { assets::set_override(std::move(fn)); }
bool asset_exists(const std::string& rel) { return assets::found(rel); }

bool asset_available(const std::string& rel) { return have(rel); }

namespace {

// (a) the area's map replacements (master_event_area.resource_replace_group_id ->
// master_replace_resource rows of res_type 4: original map -> replacement)
std::map<std::string, std::string> map_replacements(Sql& master, u32 mission) {
    std::map<std::string, std::string> replacements;
    master.q(
        "select r.original_res, r.replace_res from master_event_mission e join master_event_area a on a.id = e.master_event_area_id "
        "join master_replace_resource r on r.replace_group_id = a.resource_replace_group_id and r.res_type = 4 where e.id = ?",
        {mission}, [&](const Row& replace_row) { replacements[replace_row.s("original_res")] = replace_row.s("replace_res"); });
    return replacements;
}

// The files a battle mission's stages load: each stage's map (after the replacements) and its
// enemies' models. `stages` counts the stages (0: not a battle mission).
std::set<std::string> battle_files(Sql& master, u32 mission, int& stages) {
    std::map<std::string, std::string> replacements = map_replacements(master, mission);
    std::set<std::string> files;
    master.q("select master_map_id_label, master_enemy_party_id from master_mission_stage where master_mission_id = ?", {mission},
             [&](const Row& stage_row) {
                 stages++;
                 std::string map = stage_row.s("master_map_id_label");
                 if (auto replaced = replacements.find(map); replaced != replacements.end()) map = replaced->second;
                 if (!map.empty())
                     for (const char* ext : {"asf", "aaf", "acf"}) files.insert("BG/" + map + "." + ext);
                 // (a) master_enemy_party member1..8_id -> master_enemy_base_parameter.master_person_id
                 // -> master_person.asf: the enemy's model (Character/<asf>.asf)
                 master.q(
                     "select p.asf as asf from master_enemy_party ep join master_enemy_base_parameter b on b.id in (ep.member1_id, "
                     "ep.member2_id, ep.member3_id, ep.member4_id, ep.member5_id, ep.member6_id, ep.member7_id, ep.member8_id) "
                     "join master_person p on p.id = b.master_person_id where ep.id = ?",
                     {stage_row.i("master_enemy_party_id")}, [&](const Row& person_row) {
                         if (!person_row.s("asf").empty()) files.insert("Character/" + person_row.s("asf") + ".asf");
                     });
             });
    return files;
}

// (a) a story mission: a talk_event_id and no stages. (b) on screen: a scene whose script
// (Script/<talk_event_id label>.msgp) or talk file (Scenario/<talk_message_file>.msgp) is
// missing never starts (CPhase_Event stays black), so (d) such a story isn't offered.
bool story_playable(Sql& master, u32 mission) {
    bool ok = false;
    master.q("select talk_event_id_label as l, talk_message_file as f from master_event_mission where id = ? and talk_event_id is not null",
             {mission}, [&](const Row& story_row) {
                 ok = !story_row.s("l").empty() && have("Script/" + story_row.s("l") + ".msgp") &&
                      (story_row.s("f").empty() || have("Scenario/" + story_row.s("f") + ".msgp"));
                 if (!ok)
                     LOGD("server", "events: story mission %u not playable: Script/%s or Scenario/%s missing", mission, story_row.s("l").c_str(),
                          story_row.s("f").c_str());
             });
    return ok;
}

}  // namespace

bool mission_playable(Sql& master, u32 mission) {
    {
        std::lock_guard<std::mutex> l(g_cache_mu);
        auto it = playable_cache().find(mission);
        if (it != playable_cache().end()) return it->second;
    }
    bool ok = true;
    int stages = 0;
    std::set<std::string> files = battle_files(master, mission, stages);
    if (stages) {
        for (const std::string& rel : files)
            if (!have(rel)) {
                LOGD("server", "events: mission %u not playable: %s missing", mission, rel.c_str());
                ok = false;
                break;
            }
    } else {
        ok = story_playable(master, mission);
    }
    std::lock_guard<std::mutex> l(g_cache_mu);
    playable_cache()[mission] = ok;
    return ok;
}

// ---- schedule ----------------------------------------------------------------------------
namespace {

// (a)+(b) master_event_term: opened_day opened_time .. closed_day closed_time (the client's
// GetEventAreaList builds the same two date-times), moved by `years`.
bool term_covers(Sql& master, u32 area, int years, int64_t now, int64_t ahead) {
    bool open = false;
    master.q("select opened_day, closed_day, opened_time, closed_time from master_event_term where master_event_area_id = ?", {area},
             [&](const Row& term_row) {
                 if (open) return;
                 std::string opened_day = term_row.s("opened_day"), closed_day = term_row.s("closed_day");
                 if (opened_day.empty() || closed_day.empty()) return;
                 int64_t opened =
                     parse_time(shift_years(opened_day, years) + " " + (term_row.s("opened_time").empty() ? "00:00:00" : term_row.s("opened_time")));
                 int64_t closed =
                     parse_time(shift_years(closed_day, years) + " " + (term_row.s("closed_time").empty() ? "23:59:59" : term_row.s("closed_time")));
                 if (opened <= now + ahead && now <= closed) open = true;
             });
    return open;
}

// (a)+(b) master_event_weekly: week_id = the weekday of the client's clock (0 Sunday, as the
// labels sunday_* / monday_* say), opened_time..closed_time that day. The weekday is the real
// one of the client's date, not the replayed year's (the client computes it; documented).
bool weekly_covers(Sql& master, u32 area, int64_t now, int64_t ahead) {
    bool open = false;
    for (int64_t t : {now, now + ahead}) {
        time_t tt = (time_t)t;
        struct tm tm;
        localtime_r(&tt, &tm);
        char day[16];
        strftime(day, sizeof day, "%Y-%m-%d", &tm);
        master.q("select opened_time, closed_time from master_event_weekly where master_event_area_id = ? and week_id = ?", {area, tm.tm_wday},
                 [&](const Row& weekly_row) {
                     int64_t opened = parse_time(std::string(day) + " " + weekly_row.s("opened_time"));
                     int64_t closed = parse_time(std::string(day) + " " + weekly_row.s("closed_time"));
                     if (t == now ? (opened <= now && now <= closed) : (now <= closed && opened <= now + ahead)) open = true;
                 });
        if (!ahead) break;
    }
    return open;
}

}  // namespace

bool area_scheduled(Sql& master, u32 area, int years, int64_t now, int64_t ahead) {
    if (term_covers(master, area, years, now, ahead)) return true;
    return weekly_covers(master, area, now, ahead);
}

// ---- the lists ---------------------------------------------------------------------------
namespace {

// (d) the list is sent a day ahead (area_scheduled), so an area opening later today is known.
constexpr int64_t kListAheadSeconds = 86400;

// What the lists read of the player's state: the cleared missions (the core's `mission` table)
// and the event mission (and its area) played last.
struct EventProgress {
    std::set<u32> cleared;
    u32 last_mission = 0, last_area = 0;
};
EventProgress event_progress(Ctx& ctx) {
    EventProgress progress;
    ctx.st.q("select mission_id from mission where cleared = 1", {},
             [&](const Row& mission_row) { progress.cleared.insert((u32)mission_row.i("mission_id")); });
    ctx.st.q("select mission_id, area_id from event_last where id = 1", {}, [&](const Row& last_row) {
        progress.last_mission = (u32)last_row.i("mission_id");
        progress.last_area = (u32)last_row.i("area_id");
    });
    return progress;
}

// The listed missions of one area, in order_id order (into area.missions).
void list_area_missions(Ctx& ctx, const EventProgress& progress, bool enabled, int years, int64_t now, AreaState& area) {
    ctx.m.q(
        "select id, unlock_mission_id, visible_mission_id, opened_at, closed_at from master_event_mission "
        "where master_event_area_id = ? order by order_id, id",
        {area.id}, [&](const Row& mission_row) {
            u32 id = (u32)mission_row.i("id");
            // (a)+(b) the mission's own window (CTimeUtility::IsEnableTime on the client)
            if (!enabled && (!window_open(mission_row.s("opened_at"), "", years, now + kListAheadSeconds) ||
                             !window_open("", mission_row.s("closed_at"), years, now)))
                return;
            // (a) unlock_mission_id / visible_mission_id must be cleared; (d) a mission this
            // port can't play (missing assets) doesn't block what it unlocks, so the rest of
            // the event stays reachable.
            for (const char* column : {"unlock_mission_id", "visible_mission_id"}) {
                u32 required = (u32)mission_row.i(column);
                if (required && !progress.cleared.count(required) && mission_playable(ctx.m, required)) return;
            }
            // (d) missions whose battle maps / enemy models are missing are not offered
            if (!mission_playable(ctx.m, id)) return;
            MissionState mission;
            mission.id = id;
            mission.clear = progress.cleared.count(id) != 0;
            mission.is_new = !mission.clear;  // (d) new until cleared
            mission.last_play = id == progress.last_mission;
            area.missions.push_back(mission);
        });
}

}  // namespace

std::vector<AreaState> open_areas(Ctx& ctx, int64_t now, int64_t ev) {
    int years = year_shift(now, ev);
    EventProgress progress = event_progress(ctx);
    std::vector<AreaState> out;
    ctx.m.q("select id, id_label, opened_at, closed_at from master_event_area order by order_id, id", {}, [&](const Row& area_row) {
        u32 id = (u32)area_row.i("id");
        // (d) --enable-events: an area whose name matches the keywords is open all year, besides
        // the calendar (its client-side term is widened to match, enable_events::client_master)
        bool enabled = enable_events::area(ctx.m, id);
        if (!enabled) {
            if (!window_open(area_row.s("opened_at"), "", years, now + kListAheadSeconds) || !window_open("", area_row.s("closed_at"), years, now))
                return;
            if (!area_scheduled(ctx.m, id, years, now, kListAheadSeconds)) return;
        }
        AreaState area;
        area.id = id;
        area.label = area_row.s("id_label");
        area.last_play = id == progress.last_area;
        list_area_missions(ctx, progress, enabled, years, now, area);
        // (d) an area with no playable mission isn't listed
        if (!area.missions.empty()) out.push_back(std::move(area));
    });
    return out;
}

namespace {

// One CAreaInfo {mission_ct, is_new, is_last_play, is_start_bighunt} (b), then the AreaExtra hooks.
Value area_info(Ctx& ctx, const AreaState& area) {
    Value info = Value::object();
    bool any_new = false;
    for (auto& mission : area.missions) any_new |= mission.is_new;
    info["mission_ct"] = (u32)area.missions.size();  // (d) the number of listed missions
    info["is_new"] = any_new;                         // (d) an uncleared mission is listed
    info["is_last_play"] = area.last_play;
    info["is_start_bighunt"] = false;  // (d) no big hunt unless a module says so (AreaExtra)
    modules::register_all();
    for (auto& extra : area_extras()) extra(ctx, area.id, info);
    return info;
}

// An area's [CMissionElementInfo {id, is_new, is_clear, is_last_play}] (b).
Value mission_list(const AreaState& area) {
    Value list = Value::array();
    for (auto& mission : area.missions) {
        Value element = Value::object();
        element["id"] = mission.id;
        element["is_new"] = mission.is_new;
        element["is_clear"] = mission.clear;
        element["is_last_play"] = mission.last_play;
        list.push(element);
    }
    return list;
}

}  // namespace

Value active_event_mission_list(Ctx& ctx, int64_t now, int64_t ev) {
    Value areas = Value::object(), missions = Value::object();
    for (const AreaState& area : open_areas(ctx, now, ev)) {
        areas[std::to_string(area.id)] = area_info(ctx, area);
        missions[std::to_string(area.id)] = mission_list(area);
    }
    Value list = Value::object();
    list["EventArea"] = areas;
    list["EventMission"] = missions;
    return list;
}

Value campaign_info(Ctx& ctx, int64_t now, int64_t ev) {
    int years = year_shift(now, ev);
    Value list = Value::array();
    ctx.m.q("select * from master_campaign order by id", {}, [&](const Row& campaign_row) {
        std::string opened_text = shift_years(campaign_row.s("opened_day"), years) + " " + campaign_row.s("opened_time");
        std::string closed_text = shift_years(campaign_row.s("closed_day"), years) + " " + campaign_row.s("closed_time");
        int64_t opened = parse_time(opened_text), closed = parse_time(closed_text);
        if (!opened || !closed || now < opened || now > closed) return;
        // (a) week_id 7 = every day (the only value in the data), 0..6 a weekday of the client clock
        int week = (int)campaign_row.i("week_id");
        if (week >= 0 && week <= 6) {
            time_t tt = (time_t)now;
            struct tm tm;
            localtime_r(&tt, &tm);
            if (tm.tm_wday != week) return;
        }
        Value info = Value::object();  // CCampaignInfo (b: its keys)
        info["id"] = (u32)campaign_row.i("id");
        info["type_id"] = (u32)campaign_row.i("type_id");
        info["week_id"] = (u32)week;
        info["opened_at"] = format_time(opened);
        info["closed_at"] = format_time(closed);
        info["magnification"] = campaign_row.f("magnification");
        info["lot_drop_count_add"] = (u32)campaign_row.i("lot_drop_count_add");
        info["master_area_id"] = (u32)campaign_row.i("master_area_id");
        info["master_area_id_label"] = campaign_row.s("master_area_id_label");
        // (a) master_mission_model_type: -2 every type, else the mission type
        info["master_mission_model_type"] = (int64_t)campaign_row.i("master_mission_model_type");
        list.push(info);
    });
    return list;
}

void add_area_extra(AreaExtraFn fn, const char* file, int line) {
    area_extras().push_back(std::move(fn));
    ext::record_hook("AreaExtra", file, line);
}

bool clear_story(Ctx& ctx, u32 mission) {
    bool story = ctx.m.one("select count(*) from master_event_mission where id = ? and talk_event_id is not null", {mission}) > 0;
    if (!story) return false;
    bool first = ctx.st.one("select cleared from mission where mission_id = ?", {mission}) == 0;
    ctx.st.q("insert into mission (mission_id) values (?) on conflict(mission_id) do nothing", {mission});
    ctx.st.q(
        "update mission set cleared = 1, play_count = play_count + 1, clear_count = clear_count + 1, "
        "first_clear_at = ifnull(first_clear_at, ?) where mission_id = ?",
        {ctx.now(), mission});
    u32 area = (u32)ctx.m.one("select master_event_area_id from master_event_mission where id = ?", {mission});
    ctx.st.q("insert or replace into event_last values (1, ?, ?)", {mission, area});
    // (a) master_mission_clear_present rows of the mission go to the present box on the first
    // clear, as the core does for a battle (d: first clear only)
    int presents = 0;
    if (first)
        ctx.m.q("select content_type, content_id, num from master_mission_clear_present where master_mission_id = ? order by order_id", {mission},
                [&](const Row& present_row) {
                    add_present(ctx, (u32)present_row.i("content_type"), (u32)present_row.i("content_id"), (u32)present_row.i("num"),
                                kPresentMissionClear, mission);
                    presents++;
                });
    LOGI("server", "events: story mission %u played%s (%d clear presents)", mission, first ? ", first clear" : "", presents);
    return true;
}

namespace {

// ---- delivery ----------------------------------------------------------------------------
// (d) The responses that carry the list: the full-state player loads (below) and the mission
// flow's answers (the 3.7.0 server's exact choice isn't known; these are the ones after which
// the event menu can be opened or changes).
const std::set<std::string>& list_methods() {
    static const std::set<std::string> methods = {"MissionStart",   "MissionEnd",     "MissionFailed", "MissionTalk",
                                                  "MissionRestart", "GetPlayMission", "UpdateHome",    "GetMissionList"};
    return methods;
}

// OnPlayerLoad hook (Login, GetPlayer, NoLoginStart's full player state).
// Rules: docs/server-rules.md "What is listed", "Other data"
//   (b) the event menu sends no request: it reads the ActiveEventMissionList the client holds;
//       (b) CampaignInfo feeds the campaign badges (CUIUtility::GetCampaignSituation*).
//   (d) no event is under maintenance (CEventMaintenanceInfoMap {area: {master_event_area_id, status}}).
// Adds: ActiveEventMissionList (at the client clock and the event calendar), CampaignInfo,
// EventMaintenanceInfoMap ({}).
void load_events(Ctx& ctx, const Request&, Value& data) {
    int64_t now = ctx.now(), event_now = ctx.event_now();
    data["ActiveEventMissionList"] = active_event_mission_list(ctx, now, event_now);
    data["CampaignInfo"] = campaign_info(ctx, now, event_now);
    data["EventMaintenanceInfoMap"] = Value::object();
    const Value* areas = data.find("ActiveEventMissionList")->find("EventArea");
    LOGI("server", "events: %zu event areas open (client clock %s, event calendar %s, %+d years)", areas ? areas->map.size() : 0,
         format_time(now).c_str(), format_time(event_now).c_str(), year_shift(now, event_now));  // read by events_session.sh
}

// OnResponse hook (every response).
// Rules: docs/server-rules.md "What is listed"
//   (d) is_last_play: a MissionStart of an event mission records it (and its area) as the last.
//   (b)+(d) the mission flow's answers (list_methods) carry the new ActiveEventMissionList, and
//       GetMissionList's CampaignInfo.
// Adds: ActiveEventMissionList (list_methods), CampaignInfo (GetMissionList). True when it changed
// the response.
bool event_response_keys(Ctx& ctx, const Request& req, Value& data) {
    if (req.method == "MissionStart" && req.ints.size() > 1) {
        u32 mission = (u32)req.ints[1];  // MissionStart(type, mission, ...): core/request_args.h MissionStartArgs
        u32 area = (u32)ctx.m.one("select master_event_area_id from master_event_mission where id = ?", {mission});
        if (area) ctx.st.q("insert or replace into event_last values (1, ?, ?)", {mission, area});
    }
    if (!list_methods().count(req.method)) return false;
    int64_t now = ctx.now(), event_now = ctx.event_now();
    data["ActiveEventMissionList"] = active_event_mission_list(ctx, now, event_now);
    if (req.method == "GetMissionList") data["CampaignInfo"] = campaign_info(ctx, now, event_now);
    return true;
}

// ---- the client's master copy ----------------------------------------------------------
// (d) The dated event tables move by the whole years between the event calendar and the client
// clock, so the client's own filters (GetEventAreaList, IsEnableTime, the banners and campaign
// windows) see the replayed calendar at its real date. Month, day and time stay; a weekly slot
// keeps its weekday (master_event_weekly has no dates). With --clock the shift is 0.
void shift_client_master(Sql& db, int64_t now, int64_t event_now) {
    int years = year_shift(now, event_now);
    if (!years) return;
    struct DatedTable {
        const char* table;
        const char* columns[4];  // nullptr-terminated
    };
    static const DatedTable kDatedTables[] = {
        {"master_event_term", {"opened_day", "closed_day", nullptr}},
        {"master_event_area", {"opened_at", "closed_at", nullptr}},
        {"master_event_mission", {"opened_at", "closed_at", nullptr}},
        {"master_banner", {"opened_at", "closed_at", nullptr}},
        {"master_banner_replace", {"opened_at", "closed_at", nullptr}},
        {"master_campaign", {"opened_day", "closed_day", nullptr}},
        {"master_event_ranking_group", {"opened_at", "closed_at", "ranking_closed_at", "result_closed_at"}},
        {"master_world_boss", {"opened_at", "closed_at", nullptr}},
        {"master_replace_resource", {"opened_at", "closed_at", nullptr}},
    };
    int changed = 0;
    for (const DatedTable& dated : kDatedTables)
        for (const char* column : dated.columns) {
            if (!column) break;
            if (sqlite3_table_column_metadata(db.h, "main", dated.table, column, nullptr, nullptr, nullptr, nullptr, nullptr) != SQLITE_OK) continue;
            db.q(std::string("update ") + dated.table + " set " + column + " = printf('%04d', cast(substr(" + column +
                     ", 1, 4) as integer) + ?) || substr(" + column + ", 5) where " + column + " glob '[0-9][0-9][0-9][0-9]-*'",
                 {years});
            changed += sqlite3_changes(db.h);
        }
    LOGI("server", "events: the client's dated event tables moved %+d years (%d values; event calendar %s, clock %s)", years, changed,
         format_time(event_now).c_str(), format_time(now).c_str());
}
// (d) --enable-events: after the shift, the enabled areas and gachas get their open window (the
// ids from the server's master, whose texts the client's copy may lack).
void enable_client_master(Sql& db) {
    if (!enable_events::enabled()) return;
    std::string server_master = server_master_path();
    if (server_master.empty()) {
        enable_events::client_master(db, "main");
        return;
    }
    db.q("attach database ? as srv", {server_master});
    enable_events::client_master(db, "srv");
    db.exec("detach database srv");
}

// ClientMaster hook (the master copy the client is served, before it is sent).
// Rules: docs/server-rules.md "Two clocks", "Enabling events by keyword"
//   (d) the dated event tables moved by the year shift (shift_client_master), then (d) the
//       --enable-events windows (enable_client_master); docs/client-changes.md lists both.
void client_master_events(Sql& db, int64_t now, int64_t event_now) {
    shift_client_master(db, now, event_now);
    enable_client_master(db);
}

}  // namespace

bool end_mission_talk(u32 mission) {
    bool cleared = false;
    ext::with_live_server([&](Ctx& ctx) { cleared = clear_story(ctx, mission); });
    return cleared;
}

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_event() {
    using namespace ext;
    add_schema(kSchema);
    add_player_load(load_events);
    add_response_hook(event_response_keys);
    add_client_master(client_master_events);
}

}  // namespace soa::server::events
