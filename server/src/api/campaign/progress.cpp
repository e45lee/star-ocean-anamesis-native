// The story campaign's progress (api/campaign/campaign.h): the cleared missions and the last one
// played, in the state DB's campaign_clear and campaign_last tables (PLAN-schema S12; until
// version 11 a text file, <data>/server_campaign.txt, which step 11 imports once). Read from the DB
// each time and written in the transaction of the request that cleared (no copy kept in memory: it
// went stale across a new player and across servers). Port code, not guest behaviour.
#include <atomic>
#include <cstdio>
#include <string>

#include "api/campaign/campaign.h"
#include "core/log.h"
#include "soaserver/config.h"
#include "soaserver/ext.h"

namespace soa::server::campaign {
namespace {

// The pre-version-11 file (state/schema.h kCampaignFile), for the warning when one is left over.
std::string old_file_path() { return config().data_root + "/server_campaign.txt"; }

// --campaign-seed <mission label>: every mission on the unlock chain leading to it counts as
// cleared, so play starts at that mission (port option for testing and demos). Master data and
// the option only: the same for every state.
std::set<u32> seed_chain() {
    std::set<u32> chain;
    const std::string& seed = config().campaign_seed;
    if (seed.empty()) return chain;
    const Master& m = master();
    for (auto& [id, mission] : m.missions) {
        if (mission.label != seed) continue;
        for (u32 unlock = mission.unlock; unlock && !chain.count(unlock);) {
            chain.insert(unlock);
            auto it = m.missions.find(unlock);
            unlock = it == m.missions.end() ? 0 : it->second.unlock;
        }
    }
    return chain;
}

// The first read logs what the state holds (once per process, as when the progress was loaded once).
std::atomic<bool> g_reported{false};

}  // namespace

// (d) A new player starts with nothing cleared; the 3.7.0 save doesn't record per-mission progress
// (only BAS:PlanetOpen_* flags and the last episode / world map played).
State load_state(ext::Ctx& ctx) {
    State s;
    s.now = ctx.now();
    ctx.st.q("select mission_id from campaign_clear", {}, [&](const ext::Row& r) { s.cleared.insert((u32)r.i("mission_id")); });
    s.last_play = (u32)ctx.st.one("select mission_id from campaign_last where id = 1", {});
    const bool first = !g_reported.exchange(true);
    if (first) {
        if (FILE* f = fopen(old_file_path().c_str(), "r")) {
            fclose(f);
            LOGW("server", "campaign: %s is left over from before the state DB's version 11 (its import renames it): ignored",
                 old_file_path().c_str());
        }
    }
    if (!config().campaign_seed.empty()) {
        s.seeded = true;
        for (u32 id : seed_chain()) s.cleared.insert(id);
    }
    if (first) LOGI("server", "campaign: %zu missions cleared (the state DB)", s.cleared.size());
    return s;
}

// Saves the clear (and, as the file was rewritten whole, every seeded mission with it: a seeded
// chain is saved with the first clear) and the last play, in ctx's transaction: the request's (a
// refused request keeps none of it) or the live server's own (EndMissionTalk).
void clear_mission(ext::Ctx& ctx, u32 id, const char* why) {
    const Master& m = master();
    auto it = m.missions.find(id);
    if (it == m.missions.end()) return;
    State s = load_state(ctx);
    bool first = s.cleared.insert(id).second;
    s.last_play = id;
    LOGI("server", "campaign: %s %s%s", why, it->second.label.c_str(), first ? " (first clear)" : "");
    // What the clear unlocks, for the log.
    for (auto& [next_id, next] : m.missions)
        if (first && next.unlock == id && available(m, s, next)) LOGI("server", "campaign: unlocked %s", next.label.c_str());
    for (u32 cleared : s.cleared) ctx.st.q("insert into campaign_clear (mission_id) values (?) on conflict do nothing", {cleared});
    ctx.st.q("insert into campaign_last (id, mission_id) values (1, ?) on conflict (id) do update set mission_id = excluded.mission_id",
             {s.last_play});
}

}  // namespace soa::server::campaign
