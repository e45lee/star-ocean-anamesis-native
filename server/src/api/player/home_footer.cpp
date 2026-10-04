// The 3.7.0 home's footer flags (api/player/README.md). Port code, not guest behaviour; every rule
// carries its source label, (a) master data, (b) client-side evidence, (c) outside knowledge, (d)
// assumption. Rules in docs/server-rules.md#home.
//
// FooterMissionInfo {ep1_new_area_count, is_open_extra_dungeon, is_open_event_mission,
// is_open_evolution, is_open_multiplay} (port/fakeapi/fields.txt) is the object the client keeps
// in CParameterManager (b): the CParameterUtility gates read its fields,
//   IsOpenExtraDungeon  = CParameterManager+0x1a38  (the home's main_button3, Sphere 211)
//   IsOpenEventMission  = CParameterManager+0x1a68  (main_button1, event missions)
//   IsOpenEvolution     = CParameterManager+0x1a98
//   IsOpenMulti(bool)   = CParameterManager+0x1ac8  (multiplayer)
// (0x30 apart: one CParameterProperty per field, in the order the schema lists them). The
// 3.7.0 home shows a locked button with the game's own "clear more
// missions to open this" dialog while a flag is 0. IsOpenDeepSpace is not a footer flag: it is
// open unless the feature-status map (CParameterManager+0x74a8) closes "deep_space" (b), so the
// server sends nothing for it.
//
// The follow menu's lists (Blacklist, GetRecentlyPlayedList, SearchPlayer) are api/social/social.cpp's.
#include <cstdio>

#include "core/log.h"
#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "core/modules.h"

namespace soa::server {
namespace {

// FooterMissionInfo: the home footer's feature flags (the client's CParameterUtility::IsOpen* gates above).
Value footer_mission_info() {
    Value footer = Value::object();
    // (d) no new-area marker on the footer's mission button: the campaign's own "New" marks are
    // in ActiveMissionList (api/campaign/campaign.cpp).
    footer["ep1_new_area_count"] = 0u;
    // (d) Sphere 211 (the extra dungeon) open. No master row says when 3.7.0 opened it (the
    // lock dialog only says "clear missions"); the seeded 3.7.0 account (rank 87, all planets
    // open) had it. The Sphere 211 APIs are api/sphere211/'s.
    footer["is_open_extra_dungeon"] = true;
    // (d) Event missions open (api/events/event_missions.cpp sends ActiveEventMissionList with the same player
    // loads): the 3.7.0 account this restores had them; with 0 the button shows the lock dialog.
    footer["is_open_event_mission"] = true;
    // (d) Evolution open, as for any player past the tutorial in 3.7.0 (c: evolution existed
    // from launch); the growth module answers EvolutionCharacter (api/growth/growth.cpp).
    footer["is_open_evolution"] = true;
    // (d) Multiplayer closed: there is no other player to match with.
    footer["is_open_multiplay"] = false;
    return footer;
}

// OnPlayerLoad: FooterMissionInfo                         on Login, SimpleLogin, CreatePlayer, GetPlayer, NoLoginStart
// Rules: docs/server-rules.md#home
//
// Every full-state player response carries the footer flags (footer_mission_info above).
//   (d) The 3.7.0 server's exact choice of responses isn't known; the login responses are the
//       ones the home is built after.
// Adds: data.FooterMissionInfo.
void load_footer(ext::Ctx&, const Request&, Value& data) { data["FooterMissionInfo"] = footer_mission_info(); }

// The player load carries FooterMissionInfo with the flags above (the client applies it to
// CParameterManager+0x1a38.. ; checked on screen by port/scripts/home_session.sh).
NATIVE_TEST("player/home-footer") {
    bool ran = ext::with_scratch_server(t.rand_u64(), [&](ext::Ctx& ctx) {
        Request req;
        req.method = "GetPlayer";
        Value data = Value::object();
        ext::player_load(ctx, req, data);
        const Value* footer = data.find("FooterMissionInfo");
        if (!footer || footer->type != Value::Map) {
            t.fail("no FooterMissionInfo in the player load");
            return;
        }
        auto flag = [&](const char* k) {
            const Value* v = footer->find(k);
            return v && v->type == Value::Bool && v->b;
        };
        t.expect_eq(flag("is_open_extra_dungeon"), true, "Sphere 211 open");
        t.expect_eq(flag("is_open_event_mission"), true, "events open");
        t.expect_eq(flag("is_open_multiplay"), false, "multiplayer closed");
        t.expect_eq(flag("is_open_evolution"), true, "evolution open");
    });
    if (!ran) fprintf(stderr, "    (no scratch server: the test seed save or the 3.7.0 master DB is missing; skipped)\n");
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_home() { ext::add_player_load(load_footer); }

}  // namespace soa::server
