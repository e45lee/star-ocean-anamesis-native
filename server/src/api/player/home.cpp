// The home character: UpdateHome (api/player/home.h). Port code, not guest behaviour; every
// rule carries its source label (docs/server-rules.md "Home character").
#include "api/player/home.h"

#include "core/log.h"
#include "core/request_args.h"
#include "core/response.h"

namespace soa::server {

using ext::with_player_state;

// UpdateHome(u64 character_uid) -> UpdateHomeRes                               fid 46e0807c
// API: docs/api.md#updatehome
// Rules: docs/server-rules.md "Home character"
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
    u64 uid = args::UpdateHomeArgs::from(req).character_uid;
    if (!uid || !ctx.st.one("select count(*) from roster where uid = ?", {uid})) {
        LOGW("server", "UpdateHome %llu refused (not owned)", (unsigned long long)uid);
        return {};
    }
    ctx.st.q("update player set home_uid = ?", {uid});
    LOGI("server", "UpdateHome: %llu", (unsigned long long)uid);  // read by port/scripts/party_session.sh
    return with_player_state(ctx);
}

// The home character's API (src/core/modules.cpp: the core's APIs first).
void register_home_character() { ext::add_core_api({"UpdateHome"}, update_home); }

}  // namespace soa::server
