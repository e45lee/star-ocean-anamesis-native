#pragma once
// The server's modules and their one registration order (modules.cpp). Port code, not guest behaviour.
//
// Each module registers its API handlers and hooks (ext.h: add_api, add_player_load, ...) from one
// function, `register_<module>()`, defined at the end of its source file. register_all() calls them
// in the order of modules.cpp's list, once, before the registry is first read. The order matters:
// each hook kind runs in registration order, and OnPlayerLoad / OnResponse hooks add keys to one
// response map, whose insertion order is on the wire. So the order is this explicit list, not the
// file names (static-initializer order, before step R4 of server/PLAN-readability.md), and a source
// file can be renamed or moved without changing a reply byte. The test server/module-order pins it.

namespace soa::server {
void register_entry();         // api/entry/entry.cpp: Login, CreatePlayer, the tutorial, terms, name, server time
void register_player();        // api/player/player_info.cpp: GetPlayer, NoLoginStart (the player load)
void register_party();         // api/player/party.cpp: UpdateParty, UpdatePartySet
void register_assist();        // api/player/assist.cpp: SetAssist
void register_home_character();  // api/player/home.cpp: UpdateHome
void register_mission_start();   // api/missions/mission_start.cpp: MissionStart
void register_mission_end();     // api/missions/mission_end.cpp: MissionEnd
void register_gacha();          // api/gacha/gacha.cpp: GetGachaInData, Gacha, GachaOnce, SaleGacha, SaleGachaOnce, GachaTicket
void register_box_gacha();      // api/gacha/box.cpp: BoxGacha, ResetBoxGacha, GetBoxGacha
void register_gacha_rate();     // api/gacha/rates.cpp: GetGachaRate
void register_presents();       // api/presents/presents.cpp: PresentList, GetPresent, GetPresentArray
void register_favor();          // api/favor/favor_api.cpp: UpdateFavorByTap, UseFavorItem
void register_play_state();      // api/missions/play_state.cpp: GetPlayMission, MissionFailed / Talk / Restart, GetMissionList
void register_login_bonus();   // api/daily/login_bonus.cpp: the login bonus
void register_achievements();  // api/presents/achievements.cpp: the achievements
void register_daily();         // api/daily/premium_and_favor_bonus.cpp: premium login bonus, favor login bonus, StaminaHealByFavor
void register_deepspace();     // api/deepspace/deepspace.cpp
void register_event_ranking(); // api/events/ranking.cpp
void register_follow();        // api/social/rental.cpp: follow lists, rental helpers (UpdateSupport)
void register_gear();          // api/items/gear.cpp
void register_growth();        // api/growth/growth.cpp
void register_home();          // api/player/home_footer.cpp: the home footer flags
void register_social();        // api/social/social.cpp: the follow menu's lists (Blacklist, GetRecentlyPlayedList, SearchPlayer)
void register_items();         // api/items/items.cpp
void register_notice();        // api/player/notice.cpp
void register_shop();          // api/shop/shop.cpp
void register_sphere211();     // api/sphere211/sphere211.cpp
void register_subscription();  // api/shop/subscription.cpp
void register_title();         // api/player/titles.cpp
void register_worldboss();     // api/events/world_boss.cpp
void register_mastery();       // api/growth/mastery.cpp: GetMasteryInfo, TrainMastery, ResetMastery
void register_deco();          // api/player/deco.cpp: the character decorations (キャラデコ)
}  // namespace soa::server
namespace soa::server::events {
void register_event();  // api/events/event_missions.cpp: event missions, campaigns (master_campaign)
}
namespace soa::server::event_extras {
void register_favor_drop();  // api/events/favor_drop.cpp
}
namespace soa::server::tower {
void register_tower();  // api/tower/tower.cpp
}
namespace soa::server::ext {
// The module register_all is running (recorded with each hook, ext::hook_order); nullptr after.
void set_registering_module(const char* name);
}  // namespace soa::server::ext

namespace soa::server::modules {
// Registers every module, in the list's order; only the first call does anything (thread-safe).
// Called by the registry's readers (ext::find, ext::player_load, ext::client_master, ...), so
// neither host calls it.
void register_all();
}  // namespace soa::server::modules
