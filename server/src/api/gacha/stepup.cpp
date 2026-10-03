// Step-up gacha chains (api/gacha/gacha.h). Port code, not guest behaviour.
// Every rule carries its source label, (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption (docs/server-rules.md "4. Gacha", "Step-up gacha state",
// "Step-up and box gacha lists").
#include "api/gacha/gacha.h"

#include <algorithm>
#include <set>

#include "api/player/player_info.h"  // player_id

namespace soa::server {

using ext::body;
using ext::Row;

namespace {
// (d) a guard against a malformed chain: no 3.7.0 chain has more than 10 steps (a: stepup_max).
constexpr size_t kMaxChainSteps = 64;
}  // namespace

// A step-up chain: (a) the gacha ids linked by next_stepup_gacha_id, ordered by stepup_number
// (step 1 first).
std::vector<u32> stepup_chain(ext::Ctx& ctx, u32 id) {
    std::vector<std::pair<int64_t, u32>> steps;  // (stepup_number, gacha id)
    std::set<u32> seen;
    u32 current = id;
    while (current && seen.insert(current).second && seen.size() < kMaxChainSteps) {
        u32 next = 0;
        ctx.m.q("select stepup_number, next_stepup_gacha_id from master_gacha where id = ?", {current}, [&](const Row& gacha_row) {
            steps.emplace_back(gacha_row.i("stepup_number"), current);
            next = (u32)gacha_row.i("next_stepup_gacha_id");
        });
        current = next;
    }
    std::sort(steps.begin(), steps.end());
    std::vector<u32> chain;
    for (auto& step : steps) chain.push_back(step.second);
    if (chain.empty()) chain.push_back(id);
    return chain;
}

// CStepUpGachaInfo {player_id, master_gacha_id, try_count, is_close, restart_count,
// next_master_gacha_id} (b: its Initialize). (b) CGacha::FirstCreateNormalAndStepup lists the
// master row whose id is master_gacha_id of every entry without is_close, and
// CGacha::CheckSeriesData lets it be drawn while try_count < that row's stepup_limit_count; so
// master_gacha_id = the chain's current step and try_count = the draws made on that step
// (an earlier version sent step 1 and the chain's total draws, which the client would show as
// step 1, closed after one draw). next_master_gacha_id = the step after it (a:
// next_stepup_gacha_id). is_close: (a) loop_count laps done, when the row has one (d: the
// meaning; no step-up row sets it in 3.7.0, so chains loop without end).
bool stepup_closed(ext::Ctx& ctx, u32 current, u32 restarts) {
    int64_t loops = ctx.m.one("select ifnull(loop_count, 0) from master_gacha where id = ?", {current});
    return loops > 0 && restarts >= (u64)loops;
}

namespace {

// The player's position in one chain (the state's stepup row; step 1, nothing drawn, without one).
struct ChainState {
    u32 current = 0, tries = 0, restarts = 0;
};
ChainState chain_state(ext::Ctx& ctx, u32 head) {
    ChainState state{head, 0, 0};
    ctx.st.q("select * from stepup where head = ?", {head}, [&](const Row& stepup_row) {
        state.current = (u32)stepup_row.i("next_id");
        state.tries = (u32)stepup_row.i("try_count");
        state.restarts = (u32)stepup_row.i("restart_count");
    });
    return state;
}

}  // namespace

// The shape (b): StepUpGacha / UpdateStepUpGacha are IInfoBaseMap<u64, CStepUpGachaInfo>
// (CStepUpGachaInfoList), a **map keyed by id**; an array is silently ignored
// (IInfoBaseMap::DeserializeArray does nothing, docs/ason.md), which is why no step-up was ever
// listed while it was sent as one. CApiNotify::UpdateStepUpGacha merges UpdateStepUpGacha into
// the map at CParameterManager+0x7408 by key and copies try_count, is_close, restart_count and
// next_master_gacha_id but never master_gacha_id, so a key is one step: the map holds one
// entry per step (key = master_gacha_id = that step's gacha id). The current step is open
// (is_close as above), the chain's other steps are is_close = true, so
// FirstCreateNormalAndStepup (which skips is_close == 1) lists exactly the current step.
// (b) A chain the player never drew still needs its entry: FirstCreateNormalAndStepup lists a
// step-up row only through this map. So every chain whose current step is open at the clock
// is sent, untouched chains at step 1 with try_count 0 (d: the online server's defaults).
// only_head: just that chain (the draw's UpdateStepUpGacha), whether open or not.
Value stepup_gacha_info(ext::Ctx& ctx, u32 only_head) {
    Value info = Value::object();
    const PlayerId player = player_id(ctx);
    int64_t t = clock_now();
    std::vector<u32> heads;
    if (only_head) heads.push_back(only_head);
    else  // (a) step 1 of every chain
        ctx.m.q("select id from master_gacha where is_stepup = 1 and stepup_number = 1 order by id", {},
                [&](const Row& gacha_row) { heads.push_back((u32)gacha_row.i("id")); });
    for (u32 head : heads) {
        ChainState state = chain_state(ctx, head);
        if (!only_head) {
            bool open = false;
            ctx.m.q("select * from master_gacha where id = ?", {state.current}, [&](const Row& gacha_row) { open = gacha_open(ctx, gacha_row, t); });
            if (!open) continue;
        }
        bool closed = stepup_closed(ctx, state.current, state.restarts);
        for (u32 step : stepup_chain(ctx, head)) {
            Value entry = Value::object();
            entry["player_id"] = player.v;
            entry["master_gacha_id"] = step;
            entry["try_count"] = step == state.current ? state.tries : 0u;
            entry["is_close"] = step == state.current ? closed : true;
            entry["restart_count"] = state.restarts;
            entry["next_master_gacha_id"] = (u32)ctx.m.one("select ifnull(next_stepup_gacha_id, 0) from master_gacha where id = ?", {step});
            info[std::to_string(step)] = entry;
        }
    }
    return info;
}

}  // namespace soa::server
