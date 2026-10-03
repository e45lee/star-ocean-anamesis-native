#pragma once
// Enabling events by keyword (--enable-events; port option, off by default). Besides the
// replayed event calendar (server::event_now), every event area and every gacha whose name
// (master_text of its name_message_id) matches the keyword list (--event-keywords; the default
// kDefaultEventKeywords is the summer events and banners) is open all year: the server lists it
// (events::open_areas, GetGachaInData) and the client's master copy gets an open window for it
// (client_master below), so the client's own clock filters let it through. Missions are still
// gated on their assets (events::mission_playable). Rules and labels in docs/server-rules.md
// "Enabling events by keyword":
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include <set>
#include <string>

#include "soaserver/ext.h"

namespace soa::server::enable_events {

// The window an enabled area / gacha gets in the client's master copy (and in GetGachaInData):
// (d) wide enough to cover any clock the port runs at, ending before 2038 (a 32-bit time_t or a
// remaining-seconds int stays in range).
extern const char* const kOpenedAt;  // "2016-01-01 00:00:00"
extern const char* const kClosedAt;  // "2037-12-31 23:59:59"

// Whether the option is on (config().enable_events). Tests switch it via config().
bool enabled();
// The keyword list in force: config().event_keywords, or kDefaultEventKeywords when empty.
std::string keywords();
// Whether `text` matches the comma list `list`: it contains at least one plain keyword and none of
// the "!"-prefixed ones (empty items are ignored).
bool text_matches(const std::string& text, const std::string& list);

// The matching ids in the master `master` (tables of schema `schema`, "main" by default), by name:
// master_event_area / master_gacha rows whose name_message_id text matches `list`. A gacha also
// counts when it shares its banner_id with a matching gacha (a: the steps of a step-up and the
// single / 10-draw variants of one banner share it).
std::set<u32> area_ids(ext::Sql& master, const std::string& list, const char* schema = "main");
std::set<u32> gacha_ids(ext::Sql& master, const std::string& list, const char* schema = "main");

// Whether the client can show this gacha (box gachas included): one whose list
// banner (master_banner.image of its banner_id, Image/<image>.aif) is present (events::asset_available).
bool gacha_shown(ext::Sql& master, u32 id, const char* schema = "main");
// gacha_ids without the gachas the client can't show.
std::set<u32> shown_gacha_ids(ext::Sql& master, const std::string& list, const char* schema = "main");

// The exchange shops (アイテム交換所, master_exchange_shop) of the matching areas. (a) A shop is
// linked to an event through its currency: the ex_item_id of its contents is an event coin, i.e.
// an item that the missions of the matching areas drop or give as clear presents
// (master_mission_drop / master_mission_clear_present of master_event_mission rows) and that no
// other source gives (the missions of other event areas, story, tower and world-map missions,
// master_common_drop, master_campaign_drop; a shared currency such as the revival coins 復刻コイン
// drops in ~90 areas and is excluded). (d) A coin's shop was re-issued with each rerun under a
// new id; the one with the latest opened_at (the last run's line-up) is opened.
std::set<u32> exchange_shop_ids(ext::Sql& master, const std::string& list, const char* schema = "main");

// With the option on: whether this area / gacha / exchange shop is enabled (a gacha: and shown; the name match is
// cached per master file and list).
// False with the option off.
bool area(ext::Sql& master, u32 id);
bool gacha(ext::Sql& master, u32 id);
bool exchange_shop(ext::Sql& master, u32 id);

// The client's master copy (called by the event module's ext::ClientMaster after its year shift):
// the enabled areas' master_event_term rows, their dated master_event_area / master_event_mission
// windows and banners, and the enabled gachas' master_gacha windows and banners, get the open
// window kOpenedAt..kClosedAt, and so do the enabled exchange shops (master_exchange_shop and
// their contents' dated opened_at). The ids come from `srv_schema` (the server's master attached to
// `db`) or `db` itself. Returns the number of changed rows. Does nothing with the option off.
int client_master(ext::Sql& db, const char* srv_schema = "main");

}  // namespace soa::server::enable_events
