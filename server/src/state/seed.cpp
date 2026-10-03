// Seeding a new state DB from a save (state/seed.h). Port code, not guest behaviour; every rule
// is labelled here and in docs/server-rules.md "Seed".
#include "state/seed.h"

#include <algorithm>
#include <set>

#include "core/ids.h"
#include "core/log.h"
#include "core/server.h"  // first_existing, set_meta
#include "soaserver/chash32.h"
#include "soaserver/config.h"
#include "state/kvs.h"

namespace soa::server {

// The runtime seed save (soa's and soa-server's default): the committed, sanitized 3.7.0
// save data/saves/seed/Game.xml (a real end-of-service player, BAS:PlayerID = LOCAL00001;
// data/saves/README.md); --seed overrides it. "" when it's missing.
std::string real_seed_save() { return find_repo_file("data/saves/seed/Game.xml"); }

// (d) seed defaults, labelled in docs/server-rules.md "Seed".
void seed(ext::Ctx& ctx, const std::string& explicit_seed) {
    std::string seedp = first_existing({explicit_seed, config().seed, real_seed_save(), config().game_xml});
    auto kv = read_kvs(seedp);
    LOGI("server", "seeding from %s (%zu keys)", seedp.empty() ? "(nothing)" : seedp.c_str(), kv.size());
    // (d) The local player's search id is always the sanitized kLocalPlayerId, never the save's
    // BAS:PlayerID: that is a real account's id, and it would leak into responses, the synced
    // Game.xml, logs and docs.
    std::string search = kLocalPlayerId;
    std::string name = kv_str(kv, "player_name");
    if (name.empty()) name = "Player";                           // (d)
    u32 level = std::max(1u, kv_u32(kv, "player_level", 1));     // seed (save)
    u32 exp = kv_u32(kv, "player_exp", 0);                       // seed (save)
    u32 fol = kv_u32(kv, "player_fol", 0);                       // seed (save)
    u32 pid = chash32(search.c_str());                           // (d) numeric player id = CHash32(search id)
    u32 smax = ctx.stamina_max(level);
    int64_t t = clock_now();
    ctx.st.q(
        "insert into player (id, search_id, name, level, exp, fol, stamina, stamina_at, free_coin, pay_coin, home_uid, party_id, "
        "created_at, last_login_at) values (?,?,?,?,?,?,?,?,?,?,?,?,?,?)"
        " on conflict(id) do update set search_id = excluded.search_id, name = excluded.name, "
        "level = excluded.level, exp = excluded.exp, fol = excluded.fol, stamina = excluded.stamina, "
        "stamina_at = excluded.stamina_at, free_coin = excluded.free_coin, pay_coin = excluded.pay_coin, "
        "home_uid = excluded.home_uid, party_id = excluded.party_id, created_at = excluded.created_at, "
        "last_login_at = excluded.last_login_at",
        {pid, search, name, level, exp, fol, smax /* (d) full stamina */, t, config().start_coins /* (d) free coin, --start-coins */, 0, 0, 1, t, t});
    // Roster: person_master_role_id_N (master_role ids), deduplicated (the client cache
    // lists some roles twice).
    std::vector<u32> roles;
    std::set<u32> seen;
    u32 n = kv_u32(kv, "person_size", 0);
    for (u32 i = 0; i < n; i++) {
        u32 r = kv_u32(kv, "person_master_role_id_" + std::to_string(i));
        if (r && seen.insert(r).second && ctx.m.one("select count(*) from master_role where id = ?", {r})) roles.push_back(r);
    }
    u32 home_role = kv_u32(kv, "player_home_pc_roleid");
    u64 home_uid = 0;
    for (size_t i = 0; i < roles.size(); i++) {
        u64 uid = kRosterUid0 + i;
        u32 cap = ctx.role_level_cap(roles[i]);
        // an upsert, not a REPLACE (server/PLAN-schema.md S0): a row of this uid takes these values and
        // every other column's default (excluded.<col>), as the REPLACE gave it
        ctx.st.q(
            "insert into roster (uid, role_id, level, exp, created_at) values (?,?,?,?,?)"
            " on conflict(uid) do update set role_id = excluded.role_id, level = excluded.level, "
            "exp = excluded.exp, limit_break = excluded.limit_break, awaken = excluded.awaken, "
            "skill1 = excluded.skill1, skill2 = excluded.skill2, skill3 = excluded.skill3, "
            "weapon_uid = excluded.weapon_uid, accessory_uid = excluded.accessory_uid, "
            "created_at = excluded.created_at",
            {uid, roles[i], cap > 10 ? cap - 10 : 1u /* (d) seed level: 10 below the cap */, 0, t});
        if (roles[i] == home_role) home_uid = uid;
    }
    if (!home_uid && !roles.empty()) home_uid = kRosterUid0;
    ctx.st.q("update player set home_uid = ?", {home_uid});
    // (d) party 1 = the home character + the three highest-rarity other roster members
    // (first in roster order among equals); parties 2..10 empty
    std::vector<u64> party = {home_uid};
    std::vector<std::pair<int, size_t>> by_rarity;
    for (size_t i = 0; i < roles.size(); i++) by_rarity.emplace_back(-(int)ctx.m.one("select rarity from master_role where id = ?", {roles[i]}), i);
    std::stable_sort(by_rarity.begin(), by_rarity.end(), [](auto& a, auto& b) { return a.first < b.first; });
    for (auto& [r, i] : by_rarity)
        if (party.size() < 4 && kRosterUid0 + i != home_uid) party.push_back(kRosterUid0 + i);
    for (size_t s = 0; s < party.size(); s++)
        ctx.st.q(
            "insert into party (party_id, slot, uid) values (1,?,?)"
            " on conflict(party_id, slot) do update set uid = excluded.uid",
            {s, party[s]});
    ctx.st.q("insert or replace into meta (key, value) values ('next_char_uid', ?)", {std::to_string(kNewCharUid0)});
    ctx.st.q("insert or replace into meta (key, value) values ('next_item_uid', ?)", {std::to_string(kItemUid0)});
    ctx.st.q("insert or replace into meta (key, value) values ('seed', ?)", {seedp});
    // (b) the seeded (3.7.0) player finished the tutorial: tutorial_status = 9, the client's
    // last tutorial step (CPhase_TutorialNext::LastMemId; CParameterUtility::IsTutorialClear
    // is status >= it). (d) every UI tutorial seen (view_status / view_status2 all ones):
    // the save doesn't record them, and a veteran player has seen them all.
    set_meta(ctx, "tutorial_status", "9");
    set_meta(ctx, "view_status", "18446744073709551615");
    set_meta(ctx, "view_status2", "18446744073709551615");
    LOGI("server", "seeded player %s (%s, level %u) with %zu characters", search.c_str(), name.c_str(), level, roles.size());
}

}  // namespace soa::server
