// The home character: UpdateHome (api/player/home.h). Port code, not guest behaviour; every
// rule carries its source label (docs/server-rules.md "Home character").
#include "api/player/home.h"

#include "api/player/roster.h"  // owns_character
#include "core/log.h"
#include "core/request_args.h"
#include "core/response.h"
#include "soaserver/config.h"

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

// The home character's API (src/core/modules.cpp: the core's APIs first).
void register_home_character() { ext::add_core_api({"UpdateHome"}, update_home); }

}  // namespace soa::server
