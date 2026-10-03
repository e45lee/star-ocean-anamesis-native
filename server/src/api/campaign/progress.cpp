// The story campaign's progress (api/campaign/campaign.h): the cleared missions and the last one
// played, kept as text in <data>/server_campaign.txt ("clear <mission id>" and "last <mission id>"
// lines), outside the state DB (PLAN-readability section 6: folding it into the state DB is
// PLAN-schema's S12). Port code, not guest behaviour.
#include <cstdio>
#include <cstring>
#include <mutex>
#include <string>

#include "api/campaign/campaign.h"
#include "core/log.h"
#include "soaserver/config.h"

namespace soa::server::campaign {
namespace {

std::mutex g_mu;
State g_state;

std::string state_path() { return config().data_root + "/server_campaign.txt"; }

// SOA_CAMPAIGN_SEED=<mission label>: every mission on the unlock chain leading to it counts as
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

void save_state() {
    std::string tmp = state_path() + ".tmp";
    FILE* f = fopen(tmp.c_str(), "w");
    if (!f) return;
    for (u32 id : g_state.cleared) fprintf(f, "clear %u\n", id);
    if (g_state.last_play) fprintf(f, "last %u\n", g_state.last_play);
    fclose(f);
    rename(tmp.c_str(), state_path().c_str());
}

}  // namespace

std::mutex& lock() { return g_mu; }

// (d) A new player starts with nothing cleared; the 3.7.0 save doesn't record per-mission progress
// (only BAS:PlanetOpen_* flags and the last episode / world map played).
State& state() {
    if (g_state.loaded) return g_state;
    g_state.loaded = true;
    if (FILE* f = fopen(state_path().c_str(), "r")) {
        char word[32];
        unsigned long value;
        while (fscanf(f, "%31s %lu", word, &value) == 2) {
            if (!strcmp(word, "clear")) g_state.cleared.insert((u32)value);
            else if (!strcmp(word, "last")) g_state.last_play = (u32)value;
        }
        fclose(f);
    }
    if (!config().campaign_seed.empty()) seed_progress(g_state);
    LOGI("server", "campaign: %zu missions cleared (%s)", g_state.cleared.size(), state_path().c_str());
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
