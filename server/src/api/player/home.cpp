// The home character: UpdateHome (api/player/home.h). Port code, not guest behaviour; every
// rule carries its source label (docs/server-rules.md#home-character).
#include "api/player/home.h"

#include "api/player/roster.h"  // owns_character
#include "core/errors.h"
#include "core/log.h"
#include "core/request_args.h"
#include "core/response.h"
#include "soaserver/config.h"

namespace soa::server {

using ext::with_player_state;

// UpdateHome(u64 character_uid) -> UpdateHomeRes                               fid 46e0807c
// API: docs/api.md#updatehome
// Rules: docs/server-rules.md#home-character
//
// The home (お気に入り) character, from 3.7.0's CAdjutantSelect.
//   (b) The request carries the owned character's id (tCharaData::CharaId), a uid.
//   (d) It must be owned: an unowned or 0 uid changes nothing and is not answered (an empty
//       body: "not handled", the host's fallback), not refused with an error code.
//   (b) Player.home_pc_id = the uid, which the client's home shows, also after a restart; the
//       next boot's save sync writes its role as player_home_pc_roleid (which 3.7.0's
//       Load_PlayerInfo doesn't read).
// Answers: the player state.
std::vector<u8> update_home(ext::Ctx& ctx, const Request& req) {
    const CharacterUid uid = args::UpdateHomeArgs::from(req).character_uid;
    if (!owns_character(ctx, uid)) {
        LOGW("server", "UpdateHome %llu refused (not owned)", (unsigned long long)uid.v);
        return {};
    }
    ctx.st.q("update player set home_uid = ?", {uid});
    LOGI("server", "UpdateHome: %llu", (unsigned long long)uid.v);  // read by port/scripts/party_session.sh
    return with_player_state(ctx);
}

// --home3d-all (d: a debug option, off by default; docs/home3d.md). The client reads
// master_person.home3d_disable (b: CHome::GetAdjutant @01aebe38 reports !person+0x9a8 as "3D
// allowed"; CHome::Update then forces the 2D home and darkens the 2D/3D switch); 16
// persons have it set in 3.7.0 (a), the collab characters among them. Cleared here in the client's
// copy only; the server's own master is untouched.
int enable_home3d(ext::Sql& client_master) {
    int n = (int)client_master.one("select count(*) from master_person where coalesce(home3d_disable, 0) != 0", {});
    client_master.exec("update master_person set home3d_disable = 0 where coalesce(home3d_disable, 0) != 0");
    return n;
}

void client_home3d_all(ext::Sql& client_master, ServerTime, EventTime) {
    if (!config().home3d_all) return;
    int n = enable_home3d(client_master);
    LOGI("server", "--home3d-all: home3d_disable cleared for %d persons in the client's master", n);
}

// Home3DAnd2DSwitching(u8 is_3d) -> Home3DAnd2DSwitchingRes                       fid a092292c
// API: docs/api.md#home3dand2dswitching
// Rules: docs/server-rules.md#home-2d-3d, docs/home3d.md
//
// The home's 2D / 3D mode, the player's choice (b):
//   - CHome::GetAdjutant (@01aebe38) reports whether the home character may be shown in 3D
//     (!master_person.home3d_disable); CHome::Update then forces the 2D home for one that may
//     not, and CHome::Progress sends Home3DAnd2DSwitching(0). Its answer's lambda continues the
//     home (state 3) with the mode set from Player.is_3d_home (CParameterManager+0xd38); with no
//     answer the home stays empty (no model, no illustration).
//   - The 会話モード footer's 2D/3D変更 button sends the other mode the same way.
//   (d) Stored as sent (any non-zero: 3D) in player.is_3d_home, the choice of the online game's
//   setting; it holds for every home character, as the client's one flag does.
// Answers: the player state (Player.is_3d_home).
std::vector<u8> home3d_and_2d_switching(ext::Ctx& ctx, const Request& req) {
    const bool is_3d = args::Home3DAnd2DSwitchingArgs::from(req).is_3d;
    ctx.st.q("update player set is_3d_home = ?", {(int64_t)(is_3d ? 1 : 0)});
    LOGI("server", "Home3DAnd2DSwitching: %s", is_3d ? "3D" : "2D");
    return with_player_state(ctx);
}

// ChangeMascot(u32 master_person_id) -> ChangeMascotRes                           fid d1bcebee
// API: docs/api.md#changemascot   Rules: docs/server-rules.md#home-mascot
//
// The home's mascot (マスコット変更 in お気に入り変更, CAdjutantSelect -> CMascotSelectDialog).
//   (b) The mascots are master_home_message rows of type 3 the player's story progress opens
//       (CHome builds the list; CAdjutantSelect shows Button_mascot_change for two or more), each a
//       master_person; the dialog names them from master_person and the request lambda (@01913cc8)
//       sends the chosen one's id.
//   (a) The id must be a master_person id (10208 otherwise); (d) the server doesn't re-check the
//       story progress (the list is the client's).
//   (d) Stored in player.mascot_id and sent as Player.mascot_id from then on (the client keeps
//       its own copy too, the KVS HomeMascotID: CUIUtility::SetMascot).
// Answers: the player state (Player.mascot_id).
std::vector<u8> change_mascot(ext::Ctx& ctx, const Request& req) {
    const u32 person = args::ChangeMascotArgs::from(req).master_person_id;
    if (!ctx.m.one("select count(*) from master_person where id = ?", {person}))
        return ext::refuse(ctx, "ChangeMascot", "not a master_person id", (u32)ErrorCode::kItemUnusable);
    ctx.st.q("update player set mascot_id = ?", {person});
    LOGI("server", "ChangeMascot: %u", person);
    return with_player_state(ctx);
}

// The home character's APIs (src/core/modules.cpp: the core's APIs first).
void register_home_character() {
    ext::add_core_api({"UpdateHome"}, update_home);
    ext::add_core_api({"Home3DAnd2DSwitching"}, home3d_and_2d_switching);
    ext::add_core_api({"ChangeMascot"}, change_mascot);
}

}  // namespace soa::server
