#pragma once
// The state of the one request being answered (port code, not guest behaviour). Every handler,
// core or module, reaches it through its ext::Ctx (`ctx.request`); nothing of a request lives on
// the long-lived server object or in a global. core/server.cpp's handle() makes one per request
// (and the scratch / live-server helpers one for their run), so a request starts from a clean
// slate: no refusal, the request's own battle log, no titles granted yet.
#include <memory>
#include <vector>

#include "soaserver/battle_log.h"
#include "soaserver/ids.h"
#include "soaserver/server.h"

namespace soa::server {

struct RequestContext {
    // The client error code the request is refused with (master_text error_message_text_<code>),
    // 0 = not refused. A handler sets it through ext::refuse (or Ctx::set_error); handle_request
    // then rolls the request back and answers the player state only (ARCHITECTURE.md
    // "Transactions, refusals and errors").
    u32 refusal = 0;
    // The battle log the request carries (MissionEnd & co.; soaserver/battle_log.h), nullptr = none.
    std::shared_ptr<const BattleLog> battle_log;
    // A live server (soa or soa-server; was `in_game`): battle values come from the request's
    // battle log, and deep space asks the asset index whether an area's images exist. False in the
    // unit tests' scratch servers: battle values are `test_log_value`, every area counts as present.
    bool live = true;
    u64 test_log_value = 0;  // the battle-log value the unit tests use (live = false)
    // Set by Login when it answered the player: the server's logged_in() (FakeApiCaller::LoggedIn).
    bool logged_in = false;
    // The titles this request granted (api/player/titles.cpp: a Grant adds them, its OnResponse hook
    // reports them as AddTitleList).
    std::vector<TitleId> titles_added;
    // The equipment this request sent to the overflow box (一時保管庫), one master item id per unit
    // (api/storage/one_time.cpp: add_one_time adds them, its OnResponse hook reports them as
    // AddOneTimeStorageInfo).
    std::vector<MasterItemId> one_time_added;

    // The request's battle log, or an empty one (every value its default).
    const BattleLog& log() const {
        static const BattleLog none;
        return battle_log ? *battle_log : none;
    }
};

}  // namespace soa::server
