#pragma once
// Event missions (api/events/event_missions.cpp). The parts other modules and the
// unit tests (api/events/event_missions_tests.cpp) reach directly. Rules and labels in docs/server-rules.md "Events":
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
//
// Two clocks meet here (server.h): the client's clock `now` (data.Time = the server clock; the
// client filters the event areas and missions by it, (b) MissionUtility::GetEventAreaList /
// GetEventMissionList) and the event calendar `ev` (event_now: the replayed service calendar).
// The dated master tables are moved by the whole years between the two (year_shift), in the
// client's master copy (ext::ClientMaster) and in every server-side window check alike, so both
// sides agree on what is open.
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "soaserver/ext.h"

namespace soa::server::events {

// ---- clocks ------------------------------------------------------------------------------
// Whole years from the event calendar to the client clock: year(now) - year(ev) (0 with --clock,
// where both are the clock). (d)
int year_shift(ServerTime now, EventTime ev);
// "YYYY-..." (a date or date-time string of the master data) with the year moved by `years`;
// other strings (empty, "HH:MM:SS") unchanged.
std::string shift_years(const std::string& s, int years);
// A local time moved by `years` (the same calendar move as shift_years).
int64_t shift_time(int64_t t, int years);
// The shift of a live request: year_shift(ctx.now(), ctx.event_now()). Other modules with dated
// content the client filters (ranking, world boss, shops) use this value, so that their own
// ext::ClientMaster changes and server-side checks agree with this module's. The tables this
// module moves in the client's copy: master_event_term, _event_area, _event_mission, _banner,
// _banner_replace, _campaign, _event_ranking_group, _world_boss, _replace_resource.
int client_years(ext::Ctx& ctx);
// A master window opened..closed (date-time strings, empty = open-ended) moved by `years`,
// compared with the local time `t`.
bool window_open(const std::string& opened, const std::string& closed, int years, ServerTime t);

// ---- assets (decided at run time, never from a list) --------------------------------------
// Whether the game can load "<dir>/<file>" (e.g. "BG/bm0012_b01a.aaf"): the port's asset lookup
// (APKs, then --download-dir), with the texture quality subdirectories. Tests install their own
// predicate; an empty function restores the default. Either call forgets cached verdicts. The
// predicate is the library's one asset override (src/core/assets.h), so it gates Sphere 211's
// missions too (sphere211::set_asset_check is the same override).
using AssetCheck = std::function<bool(const std::string& rel)>;
void set_asset_check(AssetCheck fn);
bool asset_exists(const std::string& rel);
// asset_exists through the installed predicate (tests), true when no asset source exists at all
// (unit tests without the APKs): the verdict the gating in this module uses.
bool asset_available(const std::string& rel);
// A battle mission is playable when every stage's map (BG/<map>.asf/.aaf/.acf, after the area's
// resource replacement, master_replace_resource res_type 4) and every enemy model
// (Character/<master_person.asf>.asf of the stage's enemy party) is present. A story mission
// (talk_event_id, no stages) is playable when its script (Script/<talk_event_id label>.msgp) and
// talk file (Scenario/<talk_message_file>.msgp) are (a missing one leaves the scene black). A
// mission with neither stages nor a talk event isn't.
bool mission_playable(ext::Sql& master, u32 mission);

// ---- the lists ------------------------------------------------------------------------------
struct MissionState {
    u32 id = 0;
    bool clear = false, is_new = false, last_play = false;
};
struct AreaState {
    u32 id = 0;
    std::string label;
    bool last_play = false;
    std::vector<MissionState> missions;  // the listed missions, in order_id order
};
// The event areas the client will show at `now` (the client clock) with the event calendar `ev`,
// and their missions, from the player's state (ctx.st) and the master data (ctx.m).
std::vector<AreaState> open_areas(ext::Ctx& ctx, ServerTime now, EventTime ev);
// Whether an area's term (master_event_term) or weekly slot (master_event_weekly) covers the
// client time `now` (shifted by `years`), or will start within `ahead` seconds (d: the list is
// sent ahead so an area that opens later today appears without a new request; the client hides
// it until then).
bool area_scheduled(ext::Sql& master, u32 area, int years, ServerTime now, int64_t ahead = 0);
// ActiveEventMissionList {EventArea: {area id: CAreaInfo}, EventMission: {area id: [CMissionElementInfo]}}.
Value active_event_mission_list(ext::Ctx& ctx, ServerTime now, EventTime ev);
// CampaignInfo: the master_campaign rows running at the event calendar, with their windows in the
// client's time (the client compares them with its clock, (b) CUIUtility::GetCampaignSituation*).
Value campaign_info(ext::Ctx& ctx, ServerTime now, EventTime ev);

// ---- hooks for other modules (e.g. the ranking / world boss module) ------------------------
// `events::add_area_extra(fn)` (AreaExtra, from a module's register function): adds or changes
// keys of each listed area's CAreaInfo (e.g. is_start_bighunt, false by default) when the list is built.
using AreaExtraFn = std::function<void(ext::Ctx&, u32 area, Value& info)>;
void add_area_extra(AreaExtraFn fn, const char* file = __builtin_FILE(), int line = __builtin_LINE());

// The end of an event story scene (server::end_mission_talk, core/lifecycle.cpp: after
// CEventScenario::Exit, the 3.7.0 EndMissionTalk): records the clear of a story mission of master_event_mission (first clear:
// master_mission_clear_present to the present box). False when `mission` isn't an event story
// mission. Takes the server lock itself.
bool end_mission_talk(u32 mission);
// The same on a server context (tests, and the locked path above).
bool clear_story(ext::Ctx& ctx, u32 mission);

}  // namespace soa::server::events
