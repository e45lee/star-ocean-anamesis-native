#pragma once
// Extension modules of the local server (our code, not guest behaviour).
// server.cpp owns the state and the dispatcher; the modules in server/src/api/<domain>/ answer
// further API methods through this interface, so they live in their own files. Each module has
// one `register_<module>()` function (declared in src/core/modules.h) that registers its handlers and
// hooks; src/core/modules.cpp calls them in one explicit order (register_all), so the order every hook
// kind runs in is that list's, whatever the source files are named:
//  - `ext::add_api({"Method", ...}, fn)` registers a handler by method name; server.cpp's
//    dispatcher asks `ext::find(method)` for methods it doesn't answer itself;
//  - `ext::add_player_load(fn)` adds keys to the full-state player response (Login,
//    NoLoginStart, GetPlayer ...), e.g. the day's login bonus;
// A module's state tables are not its own registration: every table is created when the state
// DB opens (src/state/schema.cpp, PLAN-schema S1); a module that needs a new one adds a step there.
// The add_* functions are called only from a register_<module>() (their `file` / `line` record
// the caller, for soa-server --list-apis / --list-hooks).
// Every game rule a module applies carries its source label in a comment, as in server.cpp:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
#include <sqlite3.h>

#include <functional>
#include <initializer_list>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "soaserver/ids.h"
#include "soaserver/server.h"
#include "soaserver/sql.h"

namespace soa::server {
struct RequestContext;  // src/core/request_context.h
namespace gacha_pools {
class Pools;  // src/master/gacha_pools.h
}
}  // namespace soa::server

namespace soa::server::ext {

// ---- SQLite on a borrowed handle (the state or master DB the server opened) ----------------
// The one wrapper, soaserver/sql.h; its names here are the ones every handler uses.
using Row = sql::Row;
using Arg = sql::Arg;
using Sql = sql::Sql;
using sql::one_null_as_zero;

// A module's changes to the core mission flow (api/sphere211/sphere211.cpp: Sphere 211 battles are event
// missions played through the core MissionStart / MissionEnd). Port code; the rules are the
// module's, labelled there.
struct MissionOverride {
    std::vector<u64> party;          // the battle party (owned uids), instead of the current party
    u64 helper = 0;                  // an owned character as the 4th member (the core's own-helper path)
    bool free_stamina = false;       // no AP stamina, ticket or vanish item taken
    u32 overwrite_enemy_level = 0;   // MissionParameter.overwrite_enemy_level
    u32 add_enemy_level = 0;         // MissionParameter.add_enemy_level
};

// What every handler, core or module, gets for one request: the two DBs, the RNG, the request's
// own state and the server's services. The services are plain member functions (defined in
// src/core/context.cpp), so a module reports state exactly as the core does, and "go to
// definition" lands on the code. Port code, not guest behaviour.
struct Ctx {
    Sql st, m;                  // state DB (inside the request's transaction), master DB
    std::mt19937_64* rng = nullptr;
    RequestContext* request = nullptr;    // this request's state (src/core/request_context.h)
    gacha_pools::Pools* pools = nullptr;  // the reconstructed gacha pools (src/master/gacha_pools.h)

    // A live server (soa or soa-server): the client's data (the request's battle log, the asset
    // index) is there; false in the unit tests' scratch servers.
    bool live() const;
    int64_t now();                                  // the server clock (--clock aware)
    // The event calendar (server.h event_now): dated content (event terms, deep-space missions,
    // Sphere 211 seasons) uses it; wallet, stamina and other real-time rules use now().
    int64_t event_now();
    std::string fmt_time(int64_t t);               // "YYYY-MM-DD HH:MM:SS", local time
    int64_t parse_time(const std::string& s);
    Value base_data();                             // {Time, Player, Wallet}
    Value roster();                                // Character (CPersonInfo list)
    Value stock();                                 // StockItem (CStackItemInfo list)
    Value items();                                 // Item (CItemInfo list)
    PlayerId player_id();
    std::vector<u32> role_next(RoleId role);          // per-level next EXP of a role
    u32 role_level_cap(RoleId role);
    u32 stamina_max(u32 level);
    void tick_stamina();
    u32 global_u32(const char* key, u32 dflt);
    std::vector<u32> player_next();                // per-level next EXP of the player rank
    u32 player_level_max();                        // the player rank cap
    // Grants one content (the core's grant(): items, characters, FOL, coins, stack items).
    void grant(u32 type, u32 id, u32 num, Value& items, Value& stocks, Value& chars);
    // Runs the core MissionStart / MissionEnd / MissionFailed (by r.method) with `ov` applied and
    // returns its response's data (Nil when the core refused it or doesn't know the mission).
    Value core_mission(const Request& r, const MissionOverride* ov);
    // Refuses the request with a client error code (the core's error path: request->refusal).
    void set_error(u32 code);

    // Tests only (the scratch servers' callers): fixed clocks instead of the server's, and an
    // observer of refusals. Unset in a live server.
    struct TestHooks {
        std::function<int64_t()> now, event_now;
        std::function<void(u32 code)> on_refuse;
    } test;
};

using Handler = std::function<std::vector<u8>(Ctx&, const Request&)>;
// Registers `h` for `methods`. A method registered twice (the core's APIs register first) is a
// registration error (registration_errors; the first registration stays).
// `file` is the registering source file (soa-server --list-apis); the caller's by default.
void add_api(std::initializer_list<const char*> methods, Handler h, const char* file = __builtin_FILE(), int line = __builtin_LINE());
// The core's APIs (src/api/entry, api/player, ...; registered before the modules): add_api under
// the name the API index (tools/server_index.py) marks as the core's. (Before PLAN-schema S1 the
// modules' tables weren't created before a core API; every table now exists once the state is
// open.)
void add_core_api(std::initializer_list<const char*> methods, Handler h, const char* file = __builtin_FILE(), int line = __builtin_LINE());
using PlayerLoadFn = std::function<void(Ctx&, const Request&, Value& data)>;
void add_player_load(PlayerLoadFn fn, const char* file = __builtin_FILE(), int line = __builtin_LINE());
// `ext::add_response_hook(fn)`: sees (and may add keys to) the data of every response the server
// answers through its dispatcher (core and module APIs alike; not refused ones), inside the
// request's transaction, after the handler ran. `r.method` names the API. E.g. the event module
// (api/events/event_missions.cpp) adds ActiveEventMissionList to the mission responses. fn returns true when it
// changed `data` (only then is the response re-encoded).
using ResponseFn = std::function<bool(Ctx&, const Request&, Value& data)>;
void add_response_hook(ResponseFn fn, const char* file = __builtin_FILE(), int line = __builtin_LINE());
// `ext::add_grant(type, fn)`: grants a content type the core's grant() doesn't handle itself
// (e.g. gear 15, gear lottery 98); fn adds what it granted to the response lists it is given.
// One module per content type (a second one is a registration error).
using GrantFn = std::function<void(Ctx&, u32 id, u32 num, Value& items, Value& stocks, Value& chars)>;
void add_grant(u32 content_type, GrantFn fn, const char* file = __builtin_FILE(), int line = __builtin_LINE());
// `ext::add_item_extra(fn)`: adds keys to each owned item (CItemInfo) the core lists in `Item`
// (e.g. its attached gear); st / m are the state and master DBs.
using ItemExtraFn = std::function<void(Sql& st, Sql& m, ItemUid uid, Value& item)>;
void add_item_extra(ItemExtraFn fn, const char* file = __builtin_FILE(), int line = __builtin_LINE());

// What the core MissionStart / MissionEnd played (agent events-extras), for modules that add to
// their responses: event drops, time bonuses, world-boss damage, ranking scores.
struct MissionInfo {
    u32 mission = 0;         // the master mission id
    u32 type = 0;            // Common::MissionType of its table: 0 story, 1 event, 2 tower, 3 world map
    u32 area = 0;            // its area (master_event_area id for event missions)
    std::string table;       // "master_event_mission" ...
    std::vector<u64> uids;   // the party (owned uids; NPC / rental members as the core sent them)
    std::vector<u32> roles;  // their master_role ids (owned characters only)
    bool restart = false;    // MissionStart: a MissionRestart (the same play again, nothing paid)
    u32 mission_time = 0;    // MissionEnd: the battle log's mission_time (ms; 0 outside the game)
    // MissionEnd: a battle log property (CBattleLogInfo, e.g. "damage_total"); the unit tests'
    // value outside the game.
    std::function<u32(const char* name)> log_u32;
    // MissionEnd: the battle's evaluation value of `type` 1..6 (b: CBattleEvaluationInfo, the
    // ranking_type / evaluation_type numbering), -1 when none; the unit tests' value outside the game.
    std::function<int64_t(int type)> evaluation;
};
// `ext::add_mission_start_extra(fn)` (MissionStartExtra): after the core MissionStart built its
// response; fn may change `param` (MissionParameter) and add keys to `data`. Not called for refused starts.
using MissionStartFn = std::function<void(Ctx&, const MissionInfo&, Value& param, Value& data)>;
void add_mission_start_extra(MissionStartFn fn, const char* file = __builtin_FILE(), int line = __builtin_LINE());
// `ext::add_mission_result_extra(fn)` (MissionResultExtra): after the core MissionEnd granted its rewards and built its
// response (DropList, StockItem, AddItem ...); fn grants more (Ctx::grant) and adds what it granted
// to `data` (add_drops below keeps DropList / StockItem / AddItem consistent).
using MissionResultFn = std::function<void(Ctx&, const MissionInfo&, Value& data)>;
void add_mission_result_extra(MissionResultFn fn, const char* file = __builtin_FILE(), int line = __builtin_LINE());
// Grants `type` / `id` x `num` as a MissionEnd drop of `drop_type` (Common::MissionDropType, see
// src/api/missions/drops.cpp roll_drops) and lists it in data's DropList, AddItem / AddCharacter and StockItem.
void add_drop(Ctx& c, Value& data, u32 type, u32 id, u32 num, u32 drop_type);
void mission_start_extra(Ctx& c, const MissionInfo& mi, Value& param, Value& data);
void mission_result_extra(Ctx& c, const MissionInfo& mi, Value& data);

// Changes to the client's own copy of the master data (the game copies each master table into
// its in-memory DB at boot; the master both server modes' CDNs serve is prepared with these:
// server.cpp apply_client_master). `now` is the server clock, `event_now` the event calendar (server.h). Data-level overrides only (docs/server-rules.md).
// `ext::add_client_master(fn)` (ClientMaster).
using ClientMasterFn = std::function<void(Sql& client_db, int64_t now, int64_t event_now)>;
void add_client_master(ClientMasterFn fn, const char* file = __builtin_FILE(), int line = __builtin_LINE());

// The registrations in their order (soa-server --list-hooks, the test server/module-order): every
// hook (`kind` OnPlayerLoad, OnResponse, MissionStartExtra, MissionResultExtra, Grant, ItemExtra,
// ClientMaster, AreaExtra; not Api) with the module that registered it, the registering file and
// line, and a detail (Grant: the content type).
struct HookInfo {
    std::string kind, module, file, detail;
    int line = 0;
};
std::vector<HookInfo> hook_order();
// Duplicate registrations found by register_all (empty when there are none); each is also logged.
std::vector<std::string> registration_errors();
// Records a hook (called by the add_* functions, and events::add_area_extra).
void record_hook(const char* kind, const char* file, int line, std::string detail = "");

// The handler of `method` (core/server.cpp's dispatcher), nullptr when none is registered.
const Handler* find(const std::string& method);
// soa-server --list-apis: every registered method with the file that registered it.
std::map<std::string, std::string> api_sources();
void player_load(Ctx& c, const Request& r, Value& data);
bool has_response_hooks();
bool on_response(Ctx& c, const Request& r, Value& data);  // true: data changed
const GrantFn* find_grant(u32 content_type);
void item_extra(Sql& st, Sql& m, ItemUid uid, Value& item);
void client_master(sqlite3* db, int64_t now, int64_t event_now);

// The file of the master DB the live server reads (the 3.7.0 master), "" without a server.
std::string server_master_path();
// Runs fn on the live server (under its lock, in one transaction). False without a server.
bool with_live_server(const std::function<void(Ctx&)>& fn);

// Tests: runs fn on a scratch server seeded from port/server-data/test-seed.xml (synthetic) with the 3.7.0 master
// (implemented in server.cpp). False when either file is missing; the running test then fails
// with a message naming the missing file.
bool with_scratch_server(u64 seed, const std::function<void(Ctx&)>& fn);

// The response envelope {"data": ..., "status": 0}.
std::vector<u8> body(Value data, u32 status = 0);

// master_global value as a double (e.g. "11.5"), (a).
double global_f(Ctx& c, const char* key, double dflt);

// ---- small state helpers shared by the modules -------------------------------------------
u32 stock_count(Ctx& c, u32 item);  // owned stack items of a master item
void add_stock(Ctx& c, u32 item, int64_t delta);  // (a) capped at item_stock_max_num
u32 fol(Ctx& c);
void add_fol(Ctx& c, int64_t delta);  // (a) capped at item_fol_max_num
// Event counters for achievements (ext table `counters`): e.g. "boost", "limit_break".
void count(Ctx& c, const std::string& key, int64_t n = 1);
int64_t counter(Ctx& c, const std::string& key);
// The active achievements as the `Achievement` state key sends them (api/presents/achievements.cpp). (b) The
// client's favor-achievement reward popup and home badge (CParameterUtility::
// GetNotReceiveGoaledFavorabilityAchievement, CHome::UpdateBadge) read this state and never
// request it, so responses that change favor carry it (agent server-rules).
Value achievement_state(Ctx& c);
// Passes (api/shop/subscription.cpp): whether a master_subscription type (e.g. 3 = the deep space
// ships) is on at t, and the `Subscription` state key {type: {master_subscription_type_id,
// opened_at, closed_at}} the client reads (CParameterUtility::EnableSubscriptionType).
bool subscription_active(Ctx& c, u32 type, int64_t t);
Value subscription_state(Ctx& c);
// A present in the box (the core's presents table). `text` is the line the box shows for it
// (sent as free_text_message_id; empty = built from the reason, see present_text), stored in the
// present's `text` column (NULL when empty).
void add_present(Ctx& c, u32 type, u32 id, u32 num, u32 reason_type, u32 reason_param, const std::string& text = "");
// A present's content_id as stored: NULL for a wallet type's 0 (3 FOL, 4 free coins: no content),
// else the id. Every writer of `presents` binds it (add_present, MissionEnd's clear presents).
Arg present_content_id(u32 type, u32 id);
// ---- present texts (present_texts.cpp) ----------------------------------------------------
// (b) The present box shows each present's free_text_message_id string verbatim as its line
// (CPresentbox::CreateAllPresentList copies it into PresentParameter+0x68, the cell sets it as
// the label text); reason_type / reason_param are never read. So the server formats the line,
// from the master_text Present_box_* templates (a). The reason types are the server's own (d):
enum PresentReason : u32 {
    kPresentLoginBonus = 1,  // reason_param = master_login_bonus id; Present_box_1 "%s %d日目"
    kPresentMissionClear = 2,  // reason_param = master mission id; Present_box_2 "%sより"
    kPresentAchievement = 3,  // reason_param = master_achievement id; Present_box_3 "%s"
    kPresentPremiumLogin = 6,  // reason_param = master_premium_login_bonus id; Present_box_6 "%s %d日目"
    kPresentFavorBonus = 7,  // reason_param = master_role id; Present_favor_1 "%sのフレンドリープレゼント"
};
// master_text (lang ja) of a message id; "" when missing.
std::string text(Sql& m, const std::string& message_id);
// "%s" / "%d" in a Present_box template replaced in order.
std::string format_present(const std::string& tmpl, const std::string& s, int64_t d = -1);
// A present's line: its stored text (the row's `text`), else one built from reason_type /
// reason_param.
std::string present_text(Sql& m, const std::string& stored, u32 reason_type, u32 reason_param);
// A request refused (not enough materials, FOL, ...): nothing changes; the core's error path
// (agent server-missions) rolls the request back, answers the player state only and the client
// shows its own error dialog, master_text error_message_text_<code>. Codes (b: the texts):
// 10206 items short, 10204 locked items, 10710 / 11001 FOL short (d: which of the three FOL
// codes), 20000 coins short, 11006 limit reached, 11002 level cap, 17001 exchange period over,
// 10208 anything else (d). Inside the library they are named: src/core/errors.h `ErrorCode`
// (generated from the client's texts), with a refuse(..., ErrorCode) overload.
std::vector<u8> refuse(Ctx& c, const char* method, const char* why, u32 code);

}  // namespace soa::server::ext
