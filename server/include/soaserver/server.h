#pragma once
// The local server emulator (libsoaserver; our code, not guest behaviour). soa runs it in-process
// (--server inproc, the default), through the FakeApiCaller route (port/src/native/api/fakeapi.cpp);
// soa-server runs it standalone (server/README.md). It answers the game's API requests with
// responses built from a persistent player state (SQLite, <data>/server.sqlite3) and the 3.7.0
// master data. Its configuration is soaserver/config.h, its view of the client soaserver/hooks.h. See docs/server-rules.md for every
// rule it applies and its source label:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "soaserver/msgpack.h"
#include "soaserver/times.h"

struct sqlite3;

namespace soa::server {

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s32 = int32_t;
using s64 = int64_t;

class BattleLog;  // soaserver/battle_log.h

// The arguments of one request method (FakeApiCaller's in soa: port/src/native/api/
// server_adapters.cpp capture_from_guest; the wire decoder's in soa-server).
struct Request {
    std::string method;          // e.g. "MissionStart"
    u32 fid = 0;                 // GameProtocol FunctionID
    std::vector<u64> ints;       // integer arguments in order (strings and vectors excluded)
    std::vector<std::string> strs;          // s8 const* arguments in order
    std::vector<std::vector<u64>> vecs;     // CSTLVector<u64/u32> const& arguments in order
    // MissionEnd & co.: the battle log the request carries (soaserver/battle_log.h; soa-server:
    // the wire's blob, soa: the client's serializer on the FakeApiCaller route); nullptr = none.
    std::shared_ptr<const BattleLog> battle_log;
};

// The server answers (config().enabled; soa: --server inproc, the default).
bool enabled();

// A web page the local server hosts (api/player/notice.cpp: the notice board's page): true when `url`
// is one, with its text in *text. The port shows it in the game's web-view popup
// (native/ui/webview_local.cpp), since the desktop has no web view.
bool web_page(const std::string& url, std::string* text);
// The same page as an HTML document (*content_type "text/html; charset=utf-8"), for a real web view
// (docs/webview.md: the litehtml renderer, webview/; the port's --webview prototype).
bool web_document(const std::string& url, std::string* content_type, std::string* body);

// ---- clocks ------------------------------------------------------------------------------
// clock_now(): the server clock: the real time, or --clock "YYYY-MM-DD HH:MM:SS" and
// running on from there. Wallet, stamina, login and other real-time rules use it.
ServerTime clock_now();
// A time as the server sends it: local "YYYY-MM-DD HH:MM:SS" (src/core/time.h has the parsers and
// the other variants).
std::string format_time(int64_t t);
// The same for either clock's time (soaserver/times.h): the wire's text, formatted at the boundary.
inline std::string format_time(ServerTime t) { return format_time(t.v); }
inline std::string format_time(EventTime t) { return format_time(t.v); }
// Tests: sets the clock to `t` (running on from there), as --clock does; 0 = the real time.
void set_server_clock(int64_t t);
// Test seam (soa-server --replay): the wall clock the server clock runs on, `time(nullptr)` by
// default. clock_now() = source() + the --clock offset, so a replay sets the source to each
// recorded request's time minus config().clock_offset and the server clock reads as recorded;
// the event calendar's choice (--clock or not) is unchanged. nullptr restores time(nullptr).
using ClockSource = int64_t (*)();
void set_clock_source(ClockSource source);
// event_now(): the event calendar, for dated content (event terms, deep-space missions, the
// Sphere 211 season). With --clock it is the clock. Without, (d): today's month, day and time
// mapped onto the most recent year in which some master_event_term covers that month-day (the
// years the table's terms open in, 2016-2021 in the 3.7.0 DB; open-ended terms that close after
// the last of those years don't count), so the service's calendar replays year after year.
// docs/server-rules.md#conventions.
EventTime event_now();
// The mapping itself for the real time `t` over the master DB `master` (core/clock.cpp; t
// itself when no year qualifies or the table is missing). Cached per local day.
EventTime event_time(sqlite3* master, ServerTime t);
// The event calendar when it is the server clock itself (--clock; no master to replay): the one
// place a ServerTime becomes an EventTime unmapped (soaserver/times.h).
inline EventTime clock_as_calendar(ServerTime t) { return EventTime(t.v); }
// The year event_time picks for the month-day m-d (0: none), uncached (tests).
int event_year(sqlite3* master, int m, int d);

// A request arrived: the server keeps it as the pending request of r.fid (handle() answers it).
// Logs it. Nothing when the server is off.
void submit(const Request& r);

// Entry flow. --new-player: the server starts without a
// player (the client runs the 3.7.0 new-player flow; its Login is refused with 19001, see
// error_code). logged_in(): FakeApiCaller::LoggedIn (false until a Login was answered).
bool new_player_mode();
bool logged_in();

// The server's master-data overrides on a master DB `db` outside the client, with the clocks and
// the server's master file given: drops master_global.service_stop_day and runs the modules'
// ext::ClientMaster hooks (date shifts, texts, tower banners, shop, Sphere 211). Both server modes'
// CDNs prepare the master they serve with it (no live server needed). Nothing when `db` has no
// master_global table. `server_master` stands in for the live server's master file wherever a module reads it.
void apply_client_master(sqlite3* db, ServerTime now, EventTime event_now, const std::string& server_master);

// Builds the response body for the pending request of FunctionID `fid` (submit), in one
// transaction. False if no handler answers it. Both hosts reach it through answer().
bool handle(u32 fid, std::vector<u8>& out);
// The former signature (its `file`, the FakeApiCaller's canned file name, is read by nothing);
// kept for one merge wave (server/PLAN-readability.md R9).
bool handle(u32 fid, const std::string& file, std::vector<u8>& out);

// The error code the server refused the last request of `fid` with (0 = accepted), as the
// online server's ErrorCode(fid) would report it (master_text error_message_text_<code>). Port
// plumbing (not guest behaviour): the FakeApiCaller route always reports success, so
// port/src/native/api/fakeapi.cpp asks this for IsSuccess / IsFailure / ErrorCode. A refused
// request changes no state; its body carries only the player state (data.Time, Player, Wallet).
u32 error_code(u32 fid);

// ---- the request lifecycle (core/lifecycle.cpp): one for both hosts -------------------------
// The answer to one request.
struct Reply {
    std::vector<u8> body;  // the response MessagePack ({data, status}), the story campaign's data added
    u32 error_code = 0;    // the code it was refused with (0 accepted; error_code(fid))
    bool handled = false;  // false: no handler answered, `body` is the host's fallback (+ the campaign's data)
};
// A host's answer to a request no handler answers: soa-server's {data: {Time}}, soa's file of its
// fake-server directory (or {}).
using Fallback = std::function<std::vector<u8>()>;
// One request through the server, as both hosts (soa's FakeApiCaller route, soa-server's wire)
// deliver it: EndMissionTalk ends the story scene and is answered with GetPlayMission's answer;
// any other request is submitted, seen by the story campaign (campaign::on_request), handled, and
// its accepted or unhandled answer gets the campaign's data (campaign::on_response). A refused
// answer is the player state with `error_code`, without the campaign's data.
Reply answer(const Request& r, const Fallback& fallback);
// EndMissionTalk(mission): the end of a story mission's scene: an event module's story mission
// (events::end_mission_talk), else the story campaign's (campaign::end_mission_talk).
void end_mission_talk(u32 mission);

// ---- rules (pure functions over master data; unit-tested) ---------------------------------
namespace rules {
// Picks an index from `weights` (sum > 0) with the uniform value r in [0, sum).
int weighted_pick(const std::vector<u32>& weights, u64 r);
// Applies `gain` EXP to (level, exp) with the per-level next_exp table `next` (next[L] = EXP
// needed from L to L+1, 0 = cap) and the level cap. Returns the new {level, exp}.
std::pair<u32, u32> add_exp(u32 level, u32 exp, u64 gain, const std::vector<u32>& next, u32 cap);
// Rounds half away from zero (the client's rounding in its level interpolation and stats).
double round_half_away(double v);
// A per-level value from a sparse table of (level, value) rows: exact rows win; other levels
// are interpolated linearly between the nearest rows below and above, rounded half away from
// zero (MasterPlayerLevelModel::GetByCalculatedLevel); outside the table, the nearest row.
u32 interpolate_level(const std::vector<std::pair<u32, u32>>& rows, u32 level);
// Stamina after `elapsed` seconds from `stamina` (one point per `period` s up to `max`; a
// stamina above max (e.g. after a level-up) doesn't regenerate but isn't cut either).
// Returns {stamina, seconds carried over into the next point}.
std::pair<u32, u64> regen_stamina(u32 stamina, u32 max, u64 elapsed, u32 period);
}  // namespace rules

}  // namespace soa::server
