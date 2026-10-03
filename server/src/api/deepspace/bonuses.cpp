// Deep space: the party's bonus conditions and values (api/deepspace/README.md; declared in
// deepspace.h). Port code, not guest behaviour; every rule carries its source label, (a) master
// data, (b) client-side evidence, (c) outside knowledge, (d) assumption. Rules in
// docs/server-rules.md "Deep space".
#include <cstdlib>
#include <set>
#include <string>
#include <vector>

#include "api/deepspace/deepspace.h"
#include "rules/deepspace_rules.h"

namespace soa::server::deepspace {

namespace {
// (b) CDeepSpace::tBonusInfo::IsApplyCharacter: master_deep_space_bonus.bonus_condition1_id
// (who) and bonus_condition2_id (what they need).
enum class Who : int { kRole = 1, kWeaponKind = 2, kAnyone = 3 };
enum class Needs : int { kLevel = 1, kAllAtMaximum = 2, kLimitBreak = 3, kAwaken = 4, kBattlePower = 5 };
}  // namespace

Member member(Ctx& ctx, u64 uid) {
    Member m;
    m.uid = uid;
    ctx.st.q("select * from roster where uid = ?", {uid}, [&](const Row& roster_row) {
        m.role_id = roster_row.id<RoleId>("role_id");
        m.level = (u32)roster_row.i("level");
        m.limit_break = (u32)roster_row.i("limit_break");
        m.awaken = (u32)roster_row.i("awaken");
    });
    ctx.m.q("select category_type, master_weapon_kind_id_label from master_role where id = ?", {m.role_id}, [&](const Row& role_row) {
        m.category = (u32)role_row.i("category_type");  // (b)+(d) tCharaData::Role(): the role's category_type (1..5)
        m.weapon_kind = role_row.s("master_weapon_kind_id_label");  // (b) tCharaData::WeaponType(): e.g. "W07Bw"
    });
    // (d) battle power: the client's CalcBP sums each of the six stats as a percentage of a
    // reference character (the level-1 / level-70 common parameters); the server has no stat
    // model, so it scales with the level (and limit break), fitted to the client's own sum on
    // screen for the seed save (8 characters of levels 50..60 without weapons: 1701).
    m.battle_power = 3.86f * (float)m.level * (1.0f + 0.03f * (float)m.limit_break);
    return m;
}

// (b) CDeepSpace::tBonusInfo::IsApplyCharacter: condition1 1 = the role (category_type) equals
// param1, 2 = the weapon kind equals param1, 3 = anyone; condition2 1 = level >= param2,
// 2 = all parameters at their maximum (d: taken as level >= param2 too), 3 = limit break >=
// param2, 4 = awaken level >= param2, others (5 = battle power) = anyone.
bool applies(const Row& bonus_row, const Member& m) {
    int who = bonus_row.null("bonus_condition1_id") ? 0 : (int)bonus_row.i("bonus_condition1_id");
    int needs = bonus_row.null("bonus_condition2_id") ? 0 : (int)bonus_row.i("bonus_condition2_id");
    std::string who_param = bonus_row.s("bonus_condition1_param"), needs_param = bonus_row.s("bonus_condition2_param");
    if (who == (int)Who::kRole && (u32)atoi(who_param.c_str()) != m.category) return false;
    if (who == (int)Who::kWeaponKind && who_param != m.weapon_kind) return false;
    u32 need = (u32)atoi(needs_param.c_str());
    switch ((Needs)needs) {
        case Needs::kLevel:
        case Needs::kAllAtMaximum:
            return m.level >= need;
        case Needs::kLimitBreak:
            return m.limit_break >= need;
        case Needs::kAwaken:
            return m.awaken >= need;
        default:
            return true;
    }
}
bool sums_battle_power(const Row& bonus_row) {
    return !bonus_row.null("bonus_condition2_id") && bonus_row.i("bonus_condition2_id") == (int64_t)Needs::kBattlePower;
}

// The bonuses of a bonus set for a party: (a) bonus1_id..bonus6_id, (b) valued by the client's
// rule (rules::deepspace::bonus_value).
std::vector<std::pair<u32, float>> party_bonuses(Ctx& ctx, u32 set_id, const std::vector<Member>& party) {
    std::vector<std::pair<u32, float>> values;
    std::vector<u32> bonus_ids;
    ctx.m.q("select * from master_deep_space_bonus_set where id = ?", {set_id}, [&](const Row& set_row) {
        for (int k = 1; k <= 6; k++) {
            std::string col = "bonus" + std::to_string(k) + "_id";
            if (!set_row.null(col.c_str()) && set_row.i(col.c_str())) bonus_ids.push_back((u32)set_row.i(col.c_str()));
        }
    });
    for (u32 bonus_id : bonus_ids)
        ctx.m.q("select * from master_deep_space_bonus where id = ?", {bonus_id}, [&](const Row& bonus_row) {
            bool battle_power = sums_battle_power(bonus_row);
            float count = 0;
            for (auto& m : party)
                if (applies(bonus_row, m)) count += battle_power ? (float)(int)m.battle_power : 1.0f;
            values.emplace_back(
                bonus_id, rules::deepspace::bonus_value((u32)count, (float)bonus_row.f("bonus_condition_param_min"),
                                                        (float)bonus_row.f("bonus_condition_param_max"), (float)bonus_row.f("bonus_effect_param_min"),
                                                        (float)bonus_row.f("bonus_effect_param_max"), battle_power));
        });
    return values;
}

std::vector<u64> free_characters(Ctx& ctx) {
    std::set<u64> busy;
    ctx.st.q("select uid from ds_ship_member", {}, [&](const Row& member_row) { busy.insert((u64)member_row.i("uid")); });
    std::vector<u64> free;
    ctx.st.q("select uid from roster order by uid", {}, [&](const Row& roster_row) {
        if (!busy.count((u64)roster_row.i("uid"))) free.push_back((u64)roster_row.i("uid"));
    });
    return free;
}

}  // namespace soa::server::deepspace
