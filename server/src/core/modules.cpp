// The one registration order of the server's modules (modules.h). Port code, not guest behaviour.
//
// The list is the order the modules registered in before step R4 of server/PLAN-readability.md
// (static initializers in link order: the sources sorted by file name), so the replies are byte for
// byte what they were. A new module goes where its hooks should run relative to the others: a
// player-load hook added at the end adds its keys after every other module's.
#include "core/modules.h"

#include <mutex>

#include "soaserver/ext.h"

namespace soa::server::modules {

namespace {

struct Module {
    const char* name;
    void (*fn)();
};

// The core's APIs first (they answered before the modules when they were Server::dispatch's
// if-chain; a module registering one of their methods is a registration error).
const Module kModules[] = {
    {"entry", register_entry},
    {"player", register_player},
    {"party", register_party},
    {"assist", register_assist},
    {"home_character", register_home_character},
    {"mission_start", register_mission_start},
    {"mission_end", register_mission_end},
    {"play_state", register_play_state},
    {"gacha", register_gacha},
    {"box_gacha", register_box_gacha},
    {"gacha_rate", register_gacha_rate},
    {"presents", register_presents},
    {"favor", register_favor},
    {"login_bonus", register_login_bonus},
    {"achievements", register_achievements},
    {"daily", register_daily},
    {"deepspace", register_deepspace},
    {"event", events::register_event},
    {"event_ranking", register_event_ranking},
    {"favor_drop", event_extras::register_favor_drop},
    {"follow", register_follow},
    {"gear", register_gear},
    {"growth", register_growth},
    {"home", register_home},
    {"social", register_social},
    {"items", register_items},
    {"new_flags", register_new_flags},
    {"notice", register_notice},
    {"shop", register_shop},
    {"sphere211", register_sphere211},
    {"subscription", register_subscription},
    {"title", register_title},
    {"tower", tower::register_tower},
    {"worldboss", register_worldboss},
    {"debug_stubs", register_debug_stubs},
    {"settings", register_settings},
    {"storage", register_storage},
    {"mastery", register_mastery},
    {"deco", register_deco},
    {"coins", register_coins},
    {"stamp", register_stamp},
};

}  // namespace

void register_all() {
    static std::once_flag once;
    std::call_once(once, [] {
        for (const Module& m : kModules) {
            ext::set_registering_module(m.name);
            m.fn();
        }
        ext::set_registering_module(nullptr);
    });
}

}  // namespace soa::server::modules
