// The story campaign's progress (api/campaign/campaign.h): the cleared missions and the last one
// played, in the state DB's campaign_clear and campaign_last tables (PLAN-schema S12; until
// version 11 a text file, <data>/server_campaign.txt, which step 11 imports once). Port code, not
// guest behaviour.
#include <cstdio>
#include <mutex>
#include <string>

#include "api/campaign/campaign.h"
#include "core/log.h"
#include "soaserver/config.h"
#include "soaserver/ext.h"

namespace soa::server::campaign {
namespace {

std::mutex g_mu;
State g_state;

// The pre-version-11 file (state/schema.h kCampaignFile), for the warning when one is left over.
std::string old_file_path() { return config().data_root + "/server_campaign.txt"; }

// --campaign-seed <mission label>: every mission on the unlock chain leading to it counts as
// cleared, so play starts at that mission (port option for testing and demos).
void seed_progress(State& s) {
    const std::string& seed = config().campaign_seed;
    s.seeded = true;
    const Master& m = master();
    for (auto& [id, mission] : m.missions) {
        if (mission.label != seed) continue;
        for (u32 unlock = mission.unlock; unlock && !s.cleared.count(unlock);) {
            s.cleared.insert(unlock);
            auto it = m.missions.find(unlock);
            unlock = it == m.missions.end() ? 0 : it->second.unlock;
        }
    }
}

// Saves the progress (as the file was rewritten whole): every cleared mission, the seeded ones
// included (a seeded chain is saved with the first clear, as before), and the last play. The live
// server's own transaction (ext::with_live_server); callers hold the campaign's lock, never the
// server's (the campaign runs around a request, not inside a handler).
void save_state() {
    ext::with_live_server([&](ext::Ctx& ctx) {
        for (u32 id : g_state.cleared) ctx.st.q("insert into campaign_clear (mission_id) values (?) on conflict do nothing", {id});
        if (g_state.last_play)
            ctx.st.q("insert into campaign_last (id, mission_id) values (1, ?) on conflict (id) do update set mission_id = excluded.mission_id",
                     {g_state.last_play});
    });
}

}  // namespace

std::mutex& lock() { return g_mu; }

// (d) A new player starts with nothing cleared; the 3.7.0 save doesn't record per-mission progress
// (only BAS:PlanetOpen_* flags and the last episode / world map played).
State& state() {
    if (g_state.loaded) return g_state;
    g_state.loaded = true;
    ext::with_live_server([&](ext::Ctx& ctx) {
        ctx.st.q("select mission_id from campaign_clear", {}, [&](const ext::Row& r) { g_state.cleared.insert((u32)r.i("mission_id")); });
        g_state.last_play = (u32)ctx.st.one("select mission_id from campaign_last where id = 1", {});
    });
    if (FILE* f = fopen(old_file_path().c_str(), "r")) {
        fclose(f);
        LOGW("server", "campaign: %s is left over from before the state DB's version 11 (its import renames it): ignored", old_file_path().c_str());
    }
    if (!config().campaign_seed.empty()) seed_progress(g_state);
    LOGI("server", "campaign: %zu missions cleared (the state DB)", g_state.cleared.size());
    return g_state;
}

void clear_mission(State& s, u32 id, const char* why) {
    const Master& m = master();
    auto it = m.missions.find(id);
    if (it == m.missions.end()) return;
    bool first = s.cleared.insert(id).second;
    s.last_play = id;
    LOGI("server", "campaign: %s %s%s", why, it->second.label.c_str(), first ? " (first clear)" : "");
    // What the clear unlocks, for the log.
    for (auto& [next_id, next] : m.missions)
        if (first && next.unlock == id && available(m, s, next)) LOGI("server", "campaign: unlocked %s", next.label.c_str());
    save_state();
}

}  // namespace soa::server::campaign
