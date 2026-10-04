#pragma once
// Sphere 211 (api/sphere211/README.md): the parts other modules (the achievements,
// api/presents/achievements.cpp) and its unit tests (sphere211_tests.cpp) reach directly. The APIs
// themselves are reached through ext::find("Sphere211..."); what the module's own files share is
// in dive.h.
#include <cstdint>
#include <functional>
#include <string>

#include "soaserver/ext.h"

namespace soa::server::sphere211 {

// The season of the event calendar `ev` and how many seconds its master dates move to be current
// on the client's clock `clock` (rules in api/sphere211/season.cpp, docs/server-rules.md "Sphere 211").
// `cycle` counts the repetitions of the last season past the service's end (0 otherwise): a new
// cycle is a new season (its dive and ranking start over).
struct SeasonPick {
    u32 id = 0;
    int64_t shift = 0;
    u32 cycle = 0;
};
SeasonPick pick_season(ext::Sql& master, ServerTime clock, EventTime ev);

// Whether the game can load an asset ("BG/<map>.aaf"): by default the port's asset lookup (APKs +
// download dir). Tests install their own predicate; an empty function restores the default. Either
// call forgets the cached mission verdicts. It is the library's one asset override (core/assets.h),
// the same as events::set_asset_check.
using AssetCheck = std::function<bool(const std::string& rel)>;
void set_asset_check(AssetCheck fn);
// A mission whose battle maps (BG/<map>.asf/.aaf/.acf of each stage) are all present.
bool mission_playable(ext::Ctx& c, u32 mission);

// ---- Sphere 211 achievements (master_achievement types 61 / 62; api/presents/achievements.cpp asks) --------
// (a) type 61 "スフィア211の N F以上に到達する" (the floor reached), type 62 "スフィア211のミッションを
// N回クリアする" (the weekly challenge スフィア週間チャレンジ and campaign rows). Their windows are
// service dates, moved like the season by the current season's shift (pick_season).
bool is_achievement_type(int type);
// Whether a row's window (opened_at / closed_at, "" = open-ended), moved by the shift, covers the
// server clock; *limit_at = the moved closed_at ("" when open-ended).
bool achievement_open(ext::Ctx& c, const std::string& opened_at, const std::string& closed_at, std::string* limit_at);
// The progress of a type 61 / 62 row: the highest floor entered / the Sphere 211 battles won while
// the moved window was running.
int64_t achievement_progress(ext::Ctx& c, int type, const std::string& opened_at, const std::string& closed_at);

}  // namespace soa::server::sphere211
