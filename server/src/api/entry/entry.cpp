// The entry flow: login, new player, tutorial, terms, name (api/entry/entry.h, api/entry/README.md).
// Port code, not guest behaviour; every rule carries its source label, (a) master data, (b)
// client-side evidence, (c) outside knowledge, (d) assumption. docs/server-rules.md "Entry flow"
// lists every rule with its source.
#include "api/entry/entry.h"

#include <cstdio>
#include <cstdlib>

#include "api/player/player_info.h"  // full_player_state, base_data: the player state answers
#include "core/errors.h"
#include "core/ids.h"
#include "core/log.h"
#include "core/request_args.h"
#include "core/request_context.h"
#include "core/response.h"
#include "core/server.h"  // has_player, set_meta
#include "master/master.h"
#include "soaserver/chash32.h"
#include "soaserver/config.h"

namespace soa::server {

using ext::body;
using ext::with_player_state;

namespace {

// (a) master_global Default_Character_1..3: the starter characters' master_role id_labels.
constexpr int kStarterCharacters = 3;
// (d) the starters' party: party set 1, the one a new player's party screen and MissionStart open.
constexpr u32 kStarterPartyId = 1;
// (d) a created player's search id: "LOCAL" + 5 digits of a hash (the seed's player is LOCAL00001).
constexpr const char* kSearchIdFormat = "LOCAL%05u";
constexpr u32 kSearchIdModulo = 100000;

// Login() / SimpleLogin() -> LoginRes / SimpleLoginRes              fid a01c67ef / 447fafb8
// API: docs/api.md#login, docs/api.md#simplelogin
// Rules: docs/server-rules.md "Entry flow" (Session and login), "Player load"
//
// The 3.7.0 CPhase_Login's login (states 0 and 7).
//   (b) With no account the server answers error 19001 (kNoPlayer): the 3.7.0 client's Login
//       result lambda treats exactly that code as "no player yet" and starts the new-player flow
//       (terms, name entry, CreatePlayer); any other error returns to the title.
//   (b) LoggedIn is true once a Login is answered (the client sends Login only while it is false).
// Answers: the whole player state with the CDN keys (full_player_state).
std::vector<u8> login(ext::Ctx& ctx, const Request& req) {
    if (!has_player(ctx)) {
        return ext::refuse(ctx, req.method.c_str(), "no player yet (the new-player flow)", ErrorCode::kNoPlayer);
    }
    ctx.request->logged_in = true;  // the server's logged_in() once the request is answered
    return full_player_state(ctx, req, CdnKeys::kAll);
}

// The new player's row and starter roster (create_player, step 2): returns the search id.
std::string insert_new_player(ext::Ctx& ctx, const args::CreatePlayerArgs& args, int64_t now) {
    u32 hash = chash32((args.uuid + args.name).c_str());
    char search_id[16];
    snprintf(search_id, sizeof search_id, kSearchIdFormat, hash % kSearchIdModulo);
    u32 player_id = chash32(search_id);
    ctx.st.q(
        "insert into player (id, search_id, name, level, exp, fol, stamina, stamina_at, free_coin, pay_coin, home_uid, party_id, "
        "created_at, last_login_at) values (?,?,?,?,?,?,?,?,?,?,?,?,?,?)"
        " on conflict(id) do update set search_id = excluded.search_id, name = excluded.name, "
        "level = excluded.level, exp = excluded.exp, fol = excluded.fol, stamina = excluded.stamina, "
        "stamina_at = excluded.stamina_at, free_coin = excluded.free_coin, pay_coin = excluded.pay_coin, "
        "home_uid = excluded.home_uid, party_id = excluded.party_id, created_at = excluded.created_at, "
        "last_login_at = excluded.last_login_at",
        {player_id, std::string(search_id), args.name, 1u, 0u, 0u, ctx.stamina_max(1), now, config().start_coins /* (d) free coin, --start-coins */,
         0u, 0u, 1u, now, now});
    return search_id;
}

// The starter characters, party 1 and the home character (create_player, step 3): returns their uids.
std::vector<u64> add_starters(ext::Ctx& ctx, int64_t now) {
    std::vector<u64> party;
    for (int k = 1; k <= kStarterCharacters; k++) {
        std::string role_label = master::global_str(ctx.m.h, ("Default_Character_" + std::to_string(k)).c_str());
        u32 role_id = (u32)ctx.m.one("select id from master_role where id_label = ?", {role_label});
        if (!role_id) continue;
        u64 uid = kRosterUid0 + (k - 1);
        // an upsert, not a REPLACE (server/PLAN-schema.md S0): a row of this uid takes these values and
        // every other column's default (excluded.<col>), as the REPLACE gave it
        ctx.st.q(
            "insert into roster (uid, role_id, level, exp, created_at) values (?,?,?,?,?)"
            " on conflict(uid) do update set role_id = excluded.role_id, level = excluded.level, "
            "exp = excluded.exp, limit_break = excluded.limit_break, awaken = excluded.awaken, "
            "skill1 = excluded.skill1, skill2 = excluded.skill2, skill3 = excluded.skill3, "
            "weapon_uid = excluded.weapon_uid, accessory_uid = excluded.accessory_uid, favor = excluded.favor, "
            "created_at = excluded.created_at",
            {uid, role_id, 1u, 0u, now});
        party.push_back(uid);
    }
    if (!party.empty()) ctx.st.q("update player set home_uid = ?", {party[0]});
    for (size_t slot = 0; slot < party.size(); slot++)
        ctx.st.q(
            "insert into party (party_id, slot, uid) values (?,?,?)"
            " on conflict(party_id, slot) do update set uid = excluded.uid",
            {kStarterPartyId, slot, party[slot]});
    return party;
}

}  // namespace

// CreatePlayer(name, uuid) -> CreatePlayerRes                                  fid e3e463ad
// API: docs/api.md#createplayer
// Rules: docs/server-rules.md "New player", "Player load"
//
// The new-player flow's account, after the terms and the name entry.
//   (d) level 1, EXP 0, FOL 0: the start of the rank table.
//   (a) stamina: master_player_level.stamina of level 1; (d) full.
//   (a) the starter characters: master_global Default_Character_1..3 (the 3.7.0 DB's; the offline
//       build's stand-alone flow used its own offline_Character_1..3, a data change the offline
//       build made); (c) that the server used them; level 1; (d) party 1 = those three, the home
//       character = the first.
//   (b) tutorial status 0 (not started): CTutorialManager then runs the tutorial from the start;
//       view_status / view_status2 0.
//   (d) search id "LOCAL" + 5 digits of the uuid hash; free coins --start-coins (300,000 by
//       default: the user's request); the name as sent (the online server's name checks, errors
//       10501..10503 in the client, aren't known).
//   (d) A second CreatePlayer answers the existing player unchanged.
// Answers: the whole player state with a_ver only (full_player_state): (b) CreatePlayerRes is a
// successful reply CErrorHandlerWrap::CallBackCore checks a_ver on, and a new player's client has
// had no Login reply yet to set it: without a_ver soa-emu showed the "update the app" dialog right
// after CreatePlayer. The CDN keys come with the Login the client sends next.
std::vector<u8> create_player(ext::Ctx& ctx, const Request& req) {
    const auto args = args::CreatePlayerArgs::from(req);
    if (has_player(ctx)) {
        LOGW("server", "CreatePlayer: a player exists already; answering it");
        return full_player_state(ctx, req);
    }
    int64_t now = clock_now();
    std::string search_id = insert_new_player(ctx, args, now);
    std::vector<u64> party = add_starters(ctx, now);
    ctx.st.q("insert or replace into meta (key, value) values ('next_char_uid', ?)", {std::to_string(kNewCharUid0)});
    ctx.st.q("insert or replace into meta (key, value) values ('next_item_uid', ?)", {std::to_string(kItemUid0)});
    set_meta(ctx, "tutorial_status", "0");
    set_meta(ctx, "view_status", "0");
    set_meta(ctx, "view_status2", "0");
    // read by port/scripts/tutorial_session.sh, newplayer_session.sh
    LOGI("server", "CreatePlayer: %s (%s) with %zu starter characters", search_id.c_str(), args.name.c_str(), party.size());
    return full_player_state(ctx, req, CdnKeys::kAppVersionOnly);
}

namespace {

// UpdateTutorial(u64 tutorial_status) -> UpdateTutorialRes                     fid 1cf2b3d7
// API: docs/api.md#updatetutorial
// Rules: docs/server-rules.md "Tutorial progress"
//
// The main tutorial's progress.
//   (b) The client sends the tutorial step it reached (CTutorialManager::ST_Net_Tutoflag) and
//       expects it back in Player.tutorial_status; any value is stored.
// Answers: the player state.
std::vector<u8> update_tutorial(ext::Ctx& ctx, const Request& req) {
    u64 status = args::UpdateTutorialArgs::from(req).status;
    set_meta(ctx, "tutorial_status", std::to_string((u32)status));
    LOGI("server", "UpdateTutorial: tutorial_status = %u", (u32)status);
    return with_player_state(ctx);
}

// UpdateView(ViewFlagType kind, u64 flags) -> UpdateViewRes                    fid a2eb69ba
// API: docs/api.md#updateview
// Rules: docs/server-rules.md "Tutorial progress", "UI tutorial flags"
//
// The "seen" bit sets of the UI tutorials.
//   (b) CParameterUtility::AddTutorialViewStatus: kind 0 -> view_status, else view_status2 (the
//       server stores any other kind as view_status2).
//   (d) The flags replace the stored set (the client sends its whole set).
// Answers: the player state.
std::vector<u8> update_view(ext::Ctx& ctx, const Request& req) {
    const auto args = args::UpdateViewArgs::from(req);
    set_meta(ctx, args.kind ? "view_status2" : "view_status", std::to_string(args.flags));
    return with_player_state(ctx);
}

// UpdateKiyakuVersion(version) -> UpdateKiyakuVersionRes                       fid e5af488c
// API: docs/api.md#updatekiyakuversion
// Rules: docs/server-rules.md "Terms and name"
//
// The terms (規約) the player accepted.
//   (b) Stores the version in Player.kiyaku_version.
//   (a) MasterKiyakuVersion.kiyaku_version is master_global.kiyaku_version; (b) the shape
//       (docs/api.md); update_kiyaku_string "".
// Answers: the player state and MasterKiyakuVersion.
std::vector<u8> update_kiyaku_version(ext::Ctx& ctx, const Request& req) {
    set_meta(ctx, "kiyaku_version", args::UpdateKiyakuVersionArgs::from(req).version);
    Value data = base_data(ctx);
    Value kiyaku = Value::object();
    kiyaku["kiyaku_version"] = master::global_str(ctx.m.h, "kiyaku_version");
    kiyaku["update_kiyaku_string"] = std::string();
    data["MasterKiyakuVersion"] = kiyaku;
    return body(data);
}

// UpdatePlayerName(name) -> UpdatePlayerNameRes                                fid e8e5c4da
// API: docs/api.md#updateplayername
// Rules: docs/server-rules.md "Terms and name"
//
// The player's name.
//   (d) Accepted as sent; an empty name changes nothing.
// Answers: the player state.
std::vector<u8> update_player_name(ext::Ctx& ctx, const Request& req) {
    const auto args = args::UpdatePlayerNameArgs::from(req);
    if (!args.name.empty()) ctx.st.q("update player set name = ?", {args.name});
    return with_player_state(ctx);
}

// GetServerTime() -> GetServerTimeRes                                          fid 98b03930
// API: docs/api.md#getservertime
// Rules: docs/server-rules.md "Session and login"
//
// The server clock.
//   (b) CPhase_SyncServerTime sends it when CPhase::CheckSynkServerTime asks for a resync (on
//       login, and when the 10-minute bucket changes between phase switches); it reads data.Time.
// Answers: data.Time only.
std::vector<u8> get_server_time(ext::Ctx& ctx, const Request&) { return time_only(ctx); }

}  // namespace

// soa-server's CDN (config().cdn_url, docs/online-server.md section 6): (b) the 3.7.0 client
// downloads from CInfoManager::GetDownloadURL = "<AssetPath>/<r_ver>/" + "Android/" + the file
// (CDownloadNode::StartDownload), and compares r_ver with the revision it last saw
// (CGameResourceDownloader::SetServerAssetRevision) to start the data download; (d) MasterPath
// (no 3.7.0 reader found) mirrors AssetPath's "/download" -> "/master" swap. Not sent when no
// CDN is configured (soa in-process: the response is unchanged).
void add_cdn_paths(ext::Ctx& ctx, Value& data, bool aver_only) {
    const ServerConfig& cfg = config();
    if (cfg.cdn_url.empty()) return;
    if (aver_only) return add_aver(ctx, data);
    std::string base = cfg.cdn_url;
    while (!base.empty() && base.back() == '/') base.pop_back();
    data["AssetPath"] = base + "/download";
    data["MasterPath"] = base + "/master";
    if (!cfg.cdn_revision.empty()) data["r_ver"] = cfg.cdn_revision;
    add_episode_version(ctx, data);
    add_aver(ctx, data);
}

// LatestEpisodeVersion: the number of episodes whose data packs the client offers.
// (b) CInfoManager::Initialize (3.7.0 @015135b4) registers the top-level property
// "LatestEpisodeVersion" at CInfoManager+0xb0f0 = CParameterManager+0xb6f0 (CInfoManager is
// CParameterManager+0x600); that u32 is the episode count of tEpisodeData::Initialize /
// GetEpisodeMax (Episodeデータ管理's list, the episode list's download check),
// CGameResourceDownloader::UpdateEpisodeDataMaxSize (downloader+0x278, set by
// CPhase_DataDownload::Initialize) and CParameterUtility::IsEpisodeDataStatusDownload/Delete;
// with 0 Progress_Setup never fetches version_latest_ep<n>.version / .bin and
// LoadLocalKVSEpisodeUpdateFlag returns at once. (a) the value: master_global
// latest_episode_version (3 in the 3.7.0 DB; the CDN's manifests are ep1..ep3). Sent with
// the CDN paths only: without a CDN there is no episode pack to fetch (d).
void add_episode_version(ext::Ctx& ctx, Value& data) {
    unsigned episodes = (unsigned)atoi(master::global_str(ctx.m.h, "latest_episode_version").c_str());
    if (episodes) data["LatestEpisodeVersion"] = Value(episodes);
}

void add_aver(ext::Ctx& ctx, Value& data) {
    // (b) after every successful reply but a few session ones, CErrorHandlerWrap::CallBackCore
    // (3.7.0 @01586b20) looks for BAS::GetApplicationVersion() in the client's a_ver property
    // (the list the responses' a_ver set) and otherwise opens the "update the app" dialog
    // (OpenDialogAppVer; seen with soa-emu right after Login). (a) the version accepted is
    // master_global.a_ver_android (3.7.0); the property keeps it for the later replies.
    std::string aver = master::global_str(ctx.m.h, "a_ver_android");
    if (!aver.empty()) data["a_ver"] = aver;
}

// (b) GetServerTime: data.Time only; (d) NoLoginStart / GetPlayer without a player and
// GetMissionList answer the same (docs/server-rules.md "Session and login").
std::vector<u8> time_only(ext::Ctx& ctx) {
    Value data = Value::object();
    data["Time"] = format_time(clock_now());
    return body(data);
}

// The entry flow's APIs (src/core/modules.cpp calls this first: the core's APIs register before
// the modules').
void register_entry() {
    ext::add_core_api({"Login", "SimpleLogin"}, login);
    ext::add_core_api({"CreatePlayer"}, create_player);
    ext::add_core_api({"UpdateTutorial"}, update_tutorial);
    ext::add_core_api({"UpdateView"}, update_view);
    ext::add_core_api({"UpdateKiyakuVersion"}, update_kiyaku_version);
    ext::add_core_api({"UpdatePlayerName"}, update_player_name);
    ext::add_core_api({"GetServerTime"}, get_server_time);
}

}  // namespace soa::server
