// Character growth: BoostCharacter, LimitBreakCharacter(_Legacy), EvolutionCharacter,
// UpdateAwakenLevel, AddStatusCharacter, EquipWeapon / EquipAccessory, EquipSkill, EquipAuto
// (README.md).
// Port code, not guest behaviour. Rules in docs/server-rules.md#growth-rules (the evidence) and
// "Growth and economy" (what the server does with it); every rule carries its source label:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
// The pure rules are rules/growth_rules.{h,cpp}. Refusals answer the player state with a client
// error code (core/errors.h) and change nothing.
#include <algorithm>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "api/gen/reply_types.h"  // the replies' C*Info types
#include "api/growth/growth_args.h"
#include "api/growth/mastery.h"
#include "api/player/party_set.h"  // party_set_info
#include "api/player/roster.h"  // has_growth
#include "api/settings/config.h"
#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "rules/growth_rules.h"
#include "soaserver/ext.h"

namespace soa::server {

namespace {
using namespace ext;

// (a) master_item.type of the two equipment kinds.
constexpr u32 kWeaponItemType = 1;
constexpr u32 kAccessoryItemType = 3;

// The seeds' stats: AddStatusCharacter's index k is the master_item column kSeedStats[k] (the
// per-seed amount), roster_ext add_<stat> (the raised value), master_role <stat>_add_max (the cap)
// and master_global add_status_fol_<stat> (the FOL).
const char* kSeedStats[7] = {"hp", "attack", "intelligence", "defence", "hit", "guard", "ap"};

// (b) tCharaData::LimitBreakNeedItemNum: the master_item_limit_break column of each role rank
// (1 people, 2 guest, 3 party, 4 ace; 5 reads ace too).
const char* const kLimitBreakColumnOfRank[] = {"", "people", "guest", "party", "ace", "ace"};

// One owned character with the master_role fields growth needs.
struct Character {
    bool found = false;
    CharacterUid uid;
    RoleId role_id;
    u32 level = 1, exp = 0, limit_break = 0, awaken_level = 0;
    u32 rank = 0, rarity = 0, category_type = 0;
    std::string category_label;  // master_role.role_category_id_label
    int64_t limitbreak_id = 0;   // master_role.limitbreak_id
    std::string awaken_id;       // master_role.awaken_id
};

// The owned character `uid` (found = false when the player has none).
Character load_character(Ctx& ctx, CharacterUid uid) {
    Character chara;
    ctx.st.q("select * from roster where uid = ?", {uid}, [&](const Row& roster_row) {
        chara.found = true;
        chara.uid = uid;
        chara.role_id = roster_row.id<RoleId>("role_id");
        chara.level = (u32)roster_row.i("level");
        chara.exp = (u32)roster_row.i("exp");
        chara.limit_break = (u32)roster_row.i("limit_break");
        chara.awaken_level = (u32)roster_row.i("awaken");
    });
    if (!chara.found) return chara;
    ctx.m.q("select * from master_role where id = ?", {chara.role_id}, [&](const Row& role_row) {
        chara.rank = (u32)role_row.i("rank");
        chara.rarity = (u32)role_row.i("rarity");
        chara.category_type = (u32)role_row.i("category_type");
        chara.category_label = role_row.s("role_category_id_label");
        chara.limitbreak_id = role_row.i("limitbreak_id");
        chara.awaken_id = role_row.s("awaken_id");
    });
    return chara;
}

// The cost of an evolution or an awakening: a master row's use_fol and its (master_item<k>_id,
// item<k>_num) pairs.
struct ItemCost {
    bool found = false;  // the master row exists
    u32 fol = 0;
    std::vector<std::pair<u32, u32>> items;  // (master item id, count)
};

// Reads `slots` (master_item<k>_id, item<k>_num) pairs of a cost row; a pair with a 0 id or count
// isn't a cost.
void read_item_cost(const Row& cost_row, int slots, ItemCost& cost) {
    cost.found = true;
    cost.fol = (u32)cost_row.i("use_fol");
    for (int k = 1; k <= slots; k++) {
        std::string id = "master_item" + std::to_string(k) + "_id", num = "item" + std::to_string(k) + "_num";
        if (cost_row.i(id.c_str()) && cost_row.i(num.c_str())) cost.items.emplace_back((u32)cost_row.i(id.c_str()), (u32)cost_row.i(num.c_str()));
    }
}

// Takes the cost's items from the stock: the response's UseStockItem list ({master_item_id,
// use_count} each).
std::vector<infos::UseStackItemInfo> take_cost_items(Ctx& ctx, const ItemCost& cost) {
    std::vector<infos::UseStackItemInfo> use;
    for (auto& [item, n] : cost.items) {
        add_stock(ctx, item, -(int64_t)n);
        use.push_back({item, n});
    }
    return use;
}

// The character's fields as UpdateCharacter (CUpdateCharacterInfo) carries them. The equipped
// skills (skill1..3) are sent after EquipSkill (`equipped_skills`), else for a character with
// growth (has_growth: as when they lived in roster_ext, which EquipSkill always wrote). None when
// the player has no such character (the callers have checked: then `{}`).
std::optional<infos::CUpdateCharacterInfo> update_character_info(Ctx& ctx, CharacterUid uid, bool equipped_skills) {
    std::optional<infos::CUpdateCharacterInfo> found;
    ctx.st.q("select * from roster where uid = ?", {uid}, [&](const Row& roster_row) {
        infos::CUpdateCharacterInfo& info = found.emplace();
        const RoleId role = roster_row.id<RoleId>("role_id");
        info.id = uid.v;
        info.player_id = ctx.player_id().v;
        info.master_role_id = role.v;
        info.level = (u32)roster_row.i("level");
        info.exp = (u32)roster_row.i("exp");
        info.weapon_item_id = or_zero(roster_row.opt<ItemUid>("weapon_uid"));  // NULL: none
        info.skill1_level = (u32)roster_row.i("skill1_level");
        info.skill2_level = (u32)roster_row.i("skill2_level");
        info.skill3_level = (u32)roster_row.i("skill3_level");
        // the equipped skills (EquipSkill; NULL: none, 0)
        if (equipped_skills || has_growth(roster_row)) {
            info.skill1 = or_zero(roster_row.opt<SkillId>("equip_skill1"));
            info.skill2 = or_zero(roster_row.opt<SkillId>("equip_skill2"));
            info.skill3 = or_zero(roster_row.opt<SkillId>("equip_skill3"));
        }
        // (a) the role's rush skill, gauge and weapon kind (master_role)
        ctx.m.q("select * from master_role where id = ?", {role}, [&](const Row& role_row) {
            info.rush_skill = (u32)role_row.i("rush_skill1_id");
            info.rush_skill_factor_id = (u32)role_row.i("rush_skill1_factor_id");
            info.rush_gauge_max = (u32)role_row.f("rush_gauge_max");
            info.rush_gauge_use = (u32)role_row.f("rush_gauge_use");
            info.weapon_kind = (u32)role_row.i("master_weapon_kind_id");
        });
        info.rush_skill_level = 1;  // (d)
        info.is_new = 0;            // (d) not a new character
    });
    return found;
}
// UpdateCharacter's value: the info, or `{}` without the character.
Value update_character_value(Ctx& ctx, CharacterUid uid, bool equipped_skills) {
    std::optional<infos::CUpdateCharacterInfo> info = update_character_info(ctx, uid, equipped_skills);
    return info ? infos::to_value(*info) : Value::object();
}

// EquipWeaponResult / EquipAccessoryResult (Result: their info): the characters whose weapon /
// accessory is now the given item uid (0: none), keyed by their uid, and the item equipped (none: an
// empty map).
void set_equipped(infos::CEquipWeaponResultPersonInfo& entry, u64 item_uid) { entry.weapon_item_id = item_uid; }
void set_equipped(infos::CEquipAccessoryResultPersonInfo& entry, u64 item_uid) { entry.accessory_item_id = item_uid; }
template <class Result>
Value equip_result(const std::vector<std::pair<CharacterUid, u64>>& characters, std::optional<ItemUid> item) {
    Result result;
    for (const auto& [character_uid, item_uid] : characters) {
        auto& entry = result.Character[character_uid.v];
        entry.id = character_uid.v;
        set_equipped(entry, item_uid);
    }
    if (item) result.Item[item->v].id = item->v;
    return infos::to_value(result);
}
Value equip_result(bool weapon, const std::vector<std::pair<CharacterUid, u64>>& characters, std::optional<ItemUid> item) {
    return weapon ? equip_result<infos::CEquipWeaponResultInfo>(characters, item) : equip_result<infos::CEquipAccessoryResultInfo>(characters, item);
}

// BoostCharacter(u64 character_uid, u32 master_item_id, u32 count) -> BoostCharacterRes   fid e5a04db6
// API: docs/api.md#boostcharacter   Rules: docs/server-rules.md#character-exp
//
// Feeds `count` EXP items to an owned character (the strengthening screen,
// CPartyStrengthening::StrengtheningExecAPI).
//   (a) master_item.base_boosted_point per item; an item without one isn't an EXP item (10208).
//   (b) FOL = count x master_role_boosted(rank, rarity).use_fol_one (MasterRoleUseFolOne);
//       (d) the type-4 FOL campaigns (x0.5) aren't applied.
//   (a) master_global pc_boosted_up_rate (d: a percent chance of a big success),
//       pc_boosted_bonus_rate and pc_boosted_role_category_bonus_rate; the EXP rule is
//       growth_rules::boost_exp (b).
//   (b) the role's EXP curve (PersonModel::GetNextLevelExp) and level cap; (d) EXP at the cap is
//       dropped (rules::add_exp).
//   Refused: unknown character or no items, not an EXP item (10208), items short (10206), FOL
//   short (10710).
// Answers: the player state, BoostedCharacterResult {uid: {id, before/after level and exp,
// is_big_success}}, StockItem.
std::vector<u8> boost_character(Ctx& ctx, const Request& req) {
    const auto args = args::BoostCharacterArgs::from(req);
    const CharacterUid uid = args.character_uid;
    const u32 item = args.master_item_id, n = args.count;
    Character chara = load_character(ctx, uid);
    if (!chara.found || !n) return refuse(ctx, "BoostCharacter", "unknown character or no items", ErrorCode::kItemUnusable);
    u32 base = 0;
    int64_t item_category = -1;
    ctx.m.q("select base_boosted_point, role_category_type from master_item where id = ?", {item}, [&](const Row& item_row) {
        base = (u32)item_row.i("base_boosted_point");  // (a) master_item.base_boosted_point
        if (!item_row.null("role_category_type")) item_category = item_row.i("role_category_type");
    });
    if (!base) return refuse(ctx, "BoostCharacter", "not an EXP item", ErrorCode::kItemUnusable);
    if (stock_count(ctx, item) < n) return refuse(ctx, "BoostCharacter", "not enough items", ErrorCode::kItemCountError);
    // (b) FOL = count x master_role_boosted(rank, rarity).use_fol_one (MasterRoleUseFolOne);
    // (d) the type-4 FOL campaigns (x0.5) aren't applied.
    u32 fol_per_item = (u32)ctx.m.one("select use_fol_one from master_role_boosted where rank = ? and rarity = ?", {chara.rank, chara.rarity});
    u64 cost = (u64)fol_per_item * n;
    if (fol(ctx) < cost) return refuse(ctx, "BoostCharacter", "not enough FOL", ErrorCode::kFolShort);
    // (a) master_global pc_boosted_up_rate (percent chance, (d) the meaning) and
    // pc_boosted_bonus_rate / pc_boosted_role_category_bonus_rate
    double up_rate = global_f(ctx, "pc_boosted_up_rate", 11.5), big_rate = global_f(ctx, "pc_boosted_bonus_rate", 1.5);
    double category_rate = global_f(ctx, "pc_boosted_role_category_bonus_rate", 1.5);
    bool big = (double)((*ctx.rng)() % 10000) < up_rate * 100.0;  // the chance in hundredths of a percent
    u32 gain = growth_rules::boost_exp(n, base, item_category == (int64_t)chara.category_type, category_rate, big, big_rate);
    // (b) the role's EXP curve (PersonModel::GetNextLevelExp) and level cap; (d) EXP at the cap
    // is dropped (rules::add_exp)
    auto [new_level, new_exp] = rules::add_exp(chara.level, chara.exp, gain, ctx.role_next(chara.role_id), ctx.role_level_cap(chara.role_id));
    ctx.st.q("update roster set level = ?, exp = ? where uid = ?", {new_level, new_exp, uid});
    add_stock(ctx, item, -(int64_t)n);
    add_fol(ctx, -(int64_t)cost);
    count(ctx, "boost");
    Value data = ctx.base_data();
    infos::InfoMap<u64, infos::CBoostCharacterResultInfo> result;
    result[uid.v] = {
        .id = uid.v, .before_level = chara.level, .before_exp = chara.exp, .after_level = new_level, .after_exp = new_exp, .is_big_success = big};
    data["BoostedCharacterResult"] = infos::to_map(result);
    data["StockItem"] = ctx.stock();
    // read by growth_session.sh
    LOGI("server", "BoostCharacter %llx: %u x item %u -> +%u EXP%s, level %u/%u -> %u/%u, FOL -%llu", (unsigned long long)uid.v, n, item, gain,
         big ? " (big success)" : "", chara.level, chara.exp, new_level, new_exp, (unsigned long long)cost);
    return body(data);
}

// The items a limit break takes, by the request's id (limit_break_character, step 1): `item` is
// set to the master item they are; -1 when no rule gives a count.
int64_t limit_break_items(Ctx& ctx, const Character& chara, u32& item) {
    // (a) master_character_limit_break: the role's limitbreak_id and the item give item_num,
    // for limit breaks in [target_limitbreak_min, target_limitbreak_max)
    int64_t need = -1;
    // (b) the limit-break screen (CPartyCompositionLimitBreak) sends the master_character_limit_break
    // row id it offers (e.g. type_party_l), not the item id (the request seen in game in-process):
    // the row gives the item and its count
    ctx.m.q(
        "select item_id, item_num from master_character_limit_break where id = ? and limitbreak_id = ? and "
        "target_limitbreak_min <= ? and ? < target_limitbreak_max",
        {item, chara.limitbreak_id, chara.limit_break, chara.limit_break}, [&](const Row& row) {
            item = (u32)row.i("item_id");
            need = row.i("item_num");
        });
    if (need < 0)
        ctx.m.q(
            "select item_num from master_character_limit_break where limitbreak_id = ? and item_id = ? and "
            "target_limitbreak_min <= ? and ? < target_limitbreak_max",
            {chara.limitbreak_id, item, chara.limit_break, chara.limit_break}, [&](const Row& row) { need = row.i("item_num"); });
    if (need < 0) {
        // (b) tCharaData::LimitBreakNeedItemNum: master_item_limit_break by role rank 1..4
        if (chara.rank >= 1 && chara.rank <= 5)
            need = ctx.m.one(std::string("select ") + kLimitBreakColumnOfRank[chara.rank] + " from master_item_limit_break where master_item_id = ?",
                             {item}, -1);
    }
    return need;
}

// LimitBreakCharacter(u64 character_uid, u32 row_or_item_id) -> LimitBreakCharacterRes   fid 78972d03
// LimitBreakCharacter_Legacy (the same arguments) -> LimitBreakCharacterRes_Legacy         fid 1d7cbc6a
// API: docs/api.md#limitbreakcharacter   Rules: docs/server-rules.md#limit-break
//
// Raises an owned character's limit break by one (CPartyCompositionLimitBreak).
//   (b) the maximum is the master_rank rows of the role's rank - 1
//       (CParameterUtility::CalcMasterRole2LimitBreakMax); at it: 11006.
//   (a)/(b) the items: limit_break_items (the master_character_limit_break row the screen sends,
//       else the row of the role's limitbreak_id for that item, else master_item_limit_break's
//       column for the rank); none: 10208.
//   (b) FOL = master_rank(rank, limit_break + 1).use_fol (tCharaData::LimitBreakNeedFol).
//   (d) the level cap stays the rarity's.
//   Refused: unknown character, not a limit-break item (10208), at the maximum (11006), items short
//   (10206), FOL short (10710).
// Answers: the player state, LimitBreakCharacter {uid: CLimitBreakInfo}, StockItem.
std::vector<u8> limit_break_character(Ctx& ctx, const Request& req) {
    const auto args = args::LimitBreakCharacterArgs::from(req);
    const CharacterUid uid = args.character_uid;
    u32 item = args.row_or_item_id;
    Character chara = load_character(ctx, uid);
    if (!chara.found) return refuse(ctx, req.method.c_str(), "unknown character", ErrorCode::kItemUnusable);
    // (b) maximum = master_rank rows of the rank - 1 (CParameterUtility::CalcMasterRole2LimitBreakMax)
    u32 max = (u32)std::max<int64_t>(0, ctx.m.one("select count(*) from master_rank where rank = ?", {chara.rank}) - 1);
    if (chara.limit_break >= max) return refuse(ctx, req.method.c_str(), "already at the maximum", ErrorCode::kLimitReached);
    int64_t need = limit_break_items(ctx, chara, item);
    if (need <= 0) return refuse(ctx, req.method.c_str(), "not a limit-break item for this character", ErrorCode::kItemUnusable);
    if (stock_count(ctx, item) < (u32)need) return refuse(ctx, req.method.c_str(), "not enough items", ErrorCode::kItemCountError);
    // (b) FOL = master_rank(rank, limit_break + 1).use_fol (tCharaData::LimitBreakNeedFol)
    u32 cost = (u32)ctx.m.one("select use_fol from master_rank where rank = ? and limit_break = ?", {chara.rank, chara.limit_break + 1});
    if (fol(ctx) < cost) return refuse(ctx, req.method.c_str(), "not enough FOL", ErrorCode::kFolShort);
    add_stock(ctx, item, -need);
    add_fol(ctx, -(int64_t)cost);
    // (d) the level cap stays the rarity's (the client reads LevelMax from the rarity)
    ctx.st.q("update roster set limit_break = ? where uid = ?", {chara.limit_break + 1, uid});
    count(ctx, "limit_break");
    Value data = ctx.base_data();
    infos::InfoMap<u64, infos::CLimitBreakInfo> result;
    result[uid.v] = {.id = uid.v,
                     .master_role_id = chara.role_id.v,
                     .before_master_role_id = chara.role_id.v,
                     .after_master_role_id = chara.role_id.v,
                     .before_limit_break_count = chara.limit_break,
                     .after_limit_break_count = chara.limit_break + 1};
    data["LimitBreakCharacter"] = infos::to_map(result);
    data["StockItem"] = ctx.stock();
    // read by growth_session.sh
    LOGI("server", "%s %llx: limit break %u -> %u (%lld x item %u, FOL -%u)", req.method.c_str(), (unsigned long long)uid.v, chara.limit_break,
         chara.limit_break + 1, (long long)need, item, cost);
    return body(data);
}

// EvolutionCharacter(u64 character_uid) -> EvolutionCharacterRes   fid 990921b6
// API: docs/api.md#evolutioncharacter   Rules: docs/server-rules.md#evolution
//
// Evolves an owned character into the next rarity of its category (CPartyCompositionEvolution).
//   (b) only at the level cap (the screen enables the button only then); else 11002.
//   (b) the evolved role: the same role_category_id_label, the next higher rarity
//       (CUIUtility::MaxEvolution); none: 10208.
//   (a)+(b) the cost: master_role_evolution(rank, rarity, category_type), use_fol and up to four
//       items (CParameterUtility::FindRoleEvolution); (d) FOL campaigns aren't applied.
//   (b) the evolved character starts again at level 1, EXP 0 (the screen's preview and
//       uimsg_next_strongth 進化したため、レベルが1になりました).
//   Refused: unknown character, no evolution or no cost row (10208), not at the cap (11002), items
//   short (10206), FOL short (10710).
// Answers: the player state, EvolutionResult {use_fol, UseStockItem, UpdatePlayerCharacter {id,
// before/after master_role_id, level, is_rarity_7}}, StockItem.
std::vector<u8> evolution_character(Ctx& ctx, const Request& req) {
    const CharacterUid uid = args::EvolutionCharacterArgs::from(req).character_uid;
    Character chara = load_character(ctx, uid);
    if (!chara.found) return refuse(ctx, "EvolutionCharacter", "unknown character", ErrorCode::kItemUnusable);
    // (b) the level must be at the cap (CPartyCompositionEvolution enables the button only then)
    if (chara.level < ctx.role_level_cap(chara.role_id)) return refuse(ctx, "EvolutionCharacter", "not at the level cap", ErrorCode::kLevelCap);
    // (b) the evolved role: same role_category_id_label, the next higher rarity (CUIUtility::MaxEvolution)
    const RoleId next_role =
        ctx.m.one_id<RoleId>("select id from master_role where role_category_id_label = ? and rarity > ? order by rarity, id limit 1",
                             {chara.category_label, chara.rarity});
    if (!next_role.v) return refuse(ctx, "EvolutionCharacter", "no evolution", ErrorCode::kItemUnusable);
    // (a)+(b) the cost: master_role_evolution(rank, rarity, category_type)
    // (CParameterUtility::FindRoleEvolution)
    ItemCost cost;
    ctx.m.q("select * from master_role_evolution where rank = ? and rarity = ? and category_type = ?",
            {chara.rank, chara.rarity, chara.category_type}, [&](const Row& cost_row) { read_item_cost(cost_row, 4, cost); });
    if (!cost.found) return refuse(ctx, "EvolutionCharacter", "no master_role_evolution row", ErrorCode::kItemUnusable);
    for (auto& [item, n] : cost.items)
        if (stock_count(ctx, item) < n) return refuse(ctx, "EvolutionCharacter", "not enough items", ErrorCode::kItemCountError);
    if (fol(ctx) < cost.fol) return refuse(ctx, "EvolutionCharacter", "not enough FOL", ErrorCode::kFolShort);
    std::vector<infos::UseStackItemInfo> use = take_cost_items(ctx, cost);
    add_fol(ctx, -(int64_t)cost.fol);
    // (b) the evolved character starts again at level 1: CPartyCompositionEvolution's preview shows
    // the evolved form at "LV 1/<new cap>" and, after the result, the client says
    // uimsg_next_strongth 進化したため、レベルが1になりました (seen in game in-process; keeping the
    // level made the result screen show 60/70)
    ctx.st.q("update roster set role_id = ?, level = 1, exp = 0 where uid = ?", {next_role, uid});
    count(ctx, "evolution");
    u32 next_rarity = (u32)ctx.m.one("select rarity from master_role where id = ?", {next_role});
    count(ctx, "evolution_to_" + std::to_string(next_rarity));
    Value data = ctx.base_data();
    infos::CEvolutionResultInfo result{.use_fol = cost.fol,
                                       .UseStockItem = std::move(use),
                                       .UpdatePlayerCharacter = {.id = uid.v,
                                                                 .before_master_role_id = chara.role_id.v,
                                                                 .after_master_role_id = next_role.v,
                                                                 .level = 1,
                                                                 .is_rarity_7 = next_rarity >= 7 ? 1u : 0u}};
    data["EvolutionResult"] = infos::to_value(result);
    data["StockItem"] = ctx.stock();
    // read by growth_session.sh
    LOGI("server", "EvolutionCharacter %llx: role %u (rarity %u) -> %u (rarity %u), FOL -%u", (unsigned long long)uid.v, chara.role_id.v,
         chara.rarity, next_role.v, next_rarity, cost.fol);
    return body(data);
}

// UpdateAwakenLevel(u64 character_uid, u32 awaken_level) -> UpdateAwakenLevelRes   fid 2d714808
// API: docs/api.md#updateawakenlevel   Rules: docs/server-rules.md#awakening
//
// Awakens an owned character one level (CPartyAwakening::ExecAwakeningAPI).
//   (d) one level at a time: the request's level must be the current one + 1, else 10208.
//   (a) the cost: master_item_awaken(the role's awaken_id, the level), up to three items and
//       use_fol.
//   Refused: unknown character, not the next level, no cost row (10208), items short (10206), FOL
//   short (10710).
// Answers: the player state, AwakenResult {awaken_level, use_fol, UseStockItem, UpdateCharacter,
// update_child_id, update_child_mastery_talent_id (a graduated 弟子's new inherited talent:
// docs/server-rules.md#mastery)}, StockItem.
std::vector<u8> update_awaken_level(Ctx& ctx, const Request& req) {
    const auto args = args::UpdateAwakenLevelArgs::from(req);
    const CharacterUid uid = args.character_uid;
    const u32 level = args.awaken_level;
    Character chara = load_character(ctx, uid);
    if (!chara.found) return refuse(ctx, "UpdateAwakenLevel", "unknown character", ErrorCode::kItemUnusable);
    if (level != chara.awaken_level + 1)
        return refuse(ctx, "UpdateAwakenLevel", "not the next awakening level", ErrorCode::kItemUnusable);  // (d) one step at a time
    // (a) master_item_awaken (the role's awaken_id, the level): items and use_fol
    ItemCost cost;
    ctx.m.q("select * from master_item_awaken where awaken_id = ? and awaken_level = ?", {chara.awaken_id, level},
            [&](const Row& cost_row) { read_item_cost(cost_row, 3, cost); });
    if (!cost.found) return refuse(ctx, "UpdateAwakenLevel", "no master_item_awaken row", ErrorCode::kItemUnusable);
    for (auto& [item, n] : cost.items)
        if (stock_count(ctx, item) < n) return refuse(ctx, "UpdateAwakenLevel", "not enough items", ErrorCode::kItemCountError);
    if (fol(ctx) < cost.fol) return refuse(ctx, "UpdateAwakenLevel", "not enough FOL", ErrorCode::kFolShort);
    std::vector<infos::UseStackItemInfo> use = take_cost_items(ctx, cost);
    add_fol(ctx, -(int64_t)cost.fol);
    ctx.st.q("update roster set awaken = ? where uid = ?", {level, uid});
    Value data = ctx.base_data();
    infos::CAwakenResultInfo result{.awaken_level = level, .use_fol = cost.fol, .UseStockItem = std::move(use)};
    result.UpdateCharacter = update_character_info(ctx, uid, false).value_or(infos::CUpdateCharacterInfo{});  // (found: checked above)
    // (b) CAwakenResultInfo update_child_id / update_child_mastery_talent_id: the client sets
    // the CPersonInfo mastery_talent_id (+0x7a0) of the character update_child_id to the latter
    // (CApiNotify::OnUpdateAwakenLevelRes @014e2d90): a master's awakening can change the talent its
    // graduated 弟子 inherited (api/growth/mastery.cpp mastery_talent_of: the awakening's talent
    // in the master role's mastery_talent_slot); (d) reported whenever the awakened character
    // has a graduated disciple, else 0 / 0
    std::optional<CharacterUid> child = graduated_disciple_of(ctx, uid);
    result.update_child_id = child ? child->v : 0u;
    result.update_child_mastery_talent_id = child ? mastery_inheritance(ctx, *child).mastery_talent_id : 0u;
    data["AwakenResult"] = infos::to_value(result);
    data["StockItem"] = ctx.stock();
    LOGI("server", "UpdateAwakenLevel %llx: awakening %u -> %u, FOL -%u", (unsigned long long)uid.v, chara.awaken_level, level, cost.fol);
    return body(data);
}

// AddStatusCharacter(u64 character_uid, u32 master_item_id, u32 count) -> AddStatusCharacterRes   fid 74e09417
// API: docs/api.md#addstatuscharacter   Rules: docs/server-rules.md#character-exp
//
// Feeds `count` seeds (item_seed_*) to an owned character: its add_<stat> rises.
//   (a) the seed's stat is its own positive stat column of master_item (item_seed_*: 1, hp 5);
//       an item without one isn't a seed (10208).
//   (a) master_global add_status_fol_<stat>; (d) per seed used.
//   (a)+(b) the new value: growth_rules::stat_seed_gain, capped at master_role.<stat>_add_max
//       (CPartyStrengthening::GetParameterAddItemReflection).
//   Refused: unknown character or no seeds, not a seed (10208), seeds short (10206), FOL short
//   (10710).
// Answers: the player state, CharacterAddStatusResult (CPersonAddStatusResultInfo's before/after
// add_*, plus (d) use_fol and new_fol), StockItem.
std::vector<u8> add_status_character(Ctx& ctx, const Request& req) {
    const auto args = args::AddStatusCharacterArgs::from(req);
    const CharacterUid uid = args.character_uid;
    const u32 item = args.master_item_id, n = args.count;
    Character chara = load_character(ctx, uid);
    if (!chara.found || !n) return refuse(ctx, "AddStatusCharacter", "unknown character or no seeds", ErrorCode::kItemUnusable);
    // (a) the seed's own stat column of master_item (item_seed_*: 1, hp 5)
    int stat = -1;
    u32 per_seed = 0;
    ctx.m.q("select * from master_item where id = ?", {item}, [&](const Row& item_row) {
        for (int k = 0; k < 7; k++)
            if (!item_row.null(kSeedStats[k]) && item_row.f(kSeedStats[k]) > 0) {
                stat = k;
                per_seed = (u32)item_row.f(kSeedStats[k]);
            }
    });
    if (stat < 0) return refuse(ctx, "AddStatusCharacter", "not a seed", ErrorCode::kItemUnusable);
    if (stock_count(ctx, item) < n) return refuse(ctx, "AddStatusCharacter", "not enough seeds", ErrorCode::kItemCountError);
    // (a) master_global add_status_fol_<stat>; (d) per seed used
    u64 cost = (u64)ctx.global_u32(("add_status_fol_" + std::string(kSeedStats[stat])).c_str(), 0) * n;
    if (fol(ctx) < cost) return refuse(ctx, "AddStatusCharacter", "not enough FOL", ErrorCode::kFolShort);
    u32 before[7] = {0};
    ctx.st.q("select * from roster where uid = ?", {uid}, [&](const Row& roster_row) {
        for (int k = 0; k < 7; k++) before[k] = (u32)roster_row.i(("add_" + std::string(kSeedStats[k])).c_str());
    });
    u32 add_max = (u32)ctx.m.one(std::string("select ") + kSeedStats[stat] + "_add_max from master_role where id = ?", {chara.role_id});  // (a)
    u32 after[7];
    std::copy(before, before + 7, after);
    after[stat] = growth_rules::stat_seed_gain(before[stat], per_seed, n, add_max);
    ctx.st.q(std::string("update roster set add_") + kSeedStats[stat] + " = ? where uid = ?", {after[stat], uid});
    add_stock(ctx, item, -(int64_t)n);
    add_fol(ctx, -(int64_t)cost);
    count(ctx, "add_status_" + std::to_string(stat));
    Value data = ctx.base_data();
    // (the stats in kSeedStats' order)
    infos::CPersonAddStatusResultInfo result{.player_character_id = uid.v,
                                             .player_id = ctx.player_id().v,
                                             .before_add_hp = before[0],
                                             .after_add_hp = after[0],
                                             .before_add_attack = before[1],
                                             .after_add_attack = after[1],
                                             .before_add_intelligence = before[2],
                                             .after_add_intelligence = after[2],
                                             .before_add_defence = before[3],
                                             .after_add_defence = after[3],
                                             .before_add_hit = before[4],
                                             .after_add_hit = after[4],
                                             .before_add_guard = before[5],
                                             .after_add_guard = after[5],
                                             .before_add_ap = before[6],
                                             .after_add_ap = after[6],
                                             .use_fol = (u32)cost,
                                             .new_fol = (u32)fol(ctx)};
    data["CharacterAddStatusResult"] = infos::to_value(result);
    data["StockItem"] = ctx.stock();
    LOGI("server", "AddStatusCharacter %llx: %s %u -> %u (%u seeds, FOL -%llu)", (unsigned long long)uid.v, kSeedStats[stat], before[stat],
         after[stat], n, (unsigned long long)cost);
    return body(data);
}

// EquipWeapon(u64 character_uid, u64 item_uid) -> EquipWeaponRes          fid 1f3c9eca
// EquipAccessory(u64 character_uid, u64 item_uid) -> EquipAccessoryRes    fid 99750e8d
// API: docs/api.md#equipweapon   Rules: docs/server-rules.md#character-growth
//
// Equips an owned weapon / accessory on an owned character; item 0 takes it off
// (CPartyCompositionWeaponList::ReturnEquipHome).
//   (a) only an owned item of the kind (master_item.type 1 weapons, 3 accessories), else 10208.
//   (d) an item is equipped by one character at a time: it moves from its previous owner.
//   Refused: unknown character, not an owned item of the kind (10208).
// Answers: the player state, EquipWeaponResult / EquipAccessoryResult {Character: {uid: {id,
// weapon_item_id / accessory_item_id}} (the previous owner too), Item: {uid: {id}}}.
std::vector<u8> equip_item(Ctx& ctx, const Request& req) {
    const bool weapon = req.method == "EquipWeapon";
    const auto args = args::EquipItemArgs::from(req);
    const CharacterUid uid = args.character_uid;
    const std::optional<ItemUid> item = args.item_uid;  // none: take it off
    if (!owns_character(ctx, uid)) return refuse(ctx, req.method.c_str(), "unknown character", ErrorCode::kItemUnusable);
    u32 want_type = weapon ? kWeaponItemType : kAccessoryItemType;  // (a) master_item.type 1 weapons, 3 accessories
    // (b) an item in the equipment storage can't be equipped (api/items/items.h owns_item)
    if (item && ctx.st.one("select item_type from items where uid = ? and stored_at is null", {*item}) != want_type)
        return refuse(ctx, req.method.c_str(), "not an owned item of that kind", ErrorCode::kItemUnusable);
    const char* column = weapon ? "weapon_uid" : "accessory_uid";
    std::optional<CharacterUid> previous_owner;
    // (d) an item is equipped by one character at a time: it moves from its previous owner
    if (item)
        ctx.st.q(std::string("select uid from roster where ") + column + " = ? and uid != ?", {*item, uid},
                 [&](const Row& roster_row) { previous_owner = roster_row.id<CharacterUid>("uid"); });
    // (first: roster_weapon / roster_accessory, one character per item; NULL: none)
    if (previous_owner) ctx.st.q(std::string("update roster set ") + column + " = null where uid = ?", {*previous_owner});
    ctx.st.q(std::string("update roster set ") + column + " = ? where uid = ?", {item, uid});  // none: NULL
    Value data = ctx.base_data();
    std::vector<std::pair<CharacterUid, u64>> characters{{uid, or_zero(item)}};
    if (previous_owner) characters.emplace_back(*previous_owner, 0);
    data[weapon ? "EquipWeaponResult" : "EquipAccessoryResult"] = equip_result(weapon, characters, item);
    LOGI("server", "%s %llx: item %llx", req.method.c_str(), (unsigned long long)uid.v, (unsigned long long)or_zero(item));
    return body(data);
}

// EquipSkill(u64 character_uid, u32 skill1, u32 skill2, u32 skill3) -> EquipSkillRes   fid 4656d729
// API: docs/api.md#equipskill   Rules: docs/server-rules.md#character-growth
//
// Stores the three skill slots of an owned character (CPartyCompositionSkillList::ReturnButton).
//   (d) the slots are stored as sent: not checked against the role's open skills.
//   Refused: unknown character (10208).
// Answers: the player state and UpdateCharacter (the character's skill slots; docs/api.md: the
// client reads it at CParameterManager+0x4bc8).
std::vector<u8> equip_skill(Ctx& ctx, const Request& req) {
    const auto args = args::EquipSkillArgs::from(req);
    const CharacterUid uid = args.character_uid;
    if (!owns_character(ctx, uid)) return refuse(ctx, "EquipSkill", "unknown character", ErrorCode::kItemUnusable);
    // (0: an empty slot, NULL)
    ctx.st.q("update roster set equip_skill1 = nullif(?, 0), equip_skill2 = nullif(?, 0), equip_skill3 = nullif(?, 0) where uid = ?",
             {args.skill[0], args.skill[1], args.skill[2], uid});
    Value data = ctx.base_data();
    data["UpdateCharacter"] = update_character_value(ctx, uid, true);
    return body(data);
}

// ---- EquipAuto (自動設定) ---------------------------------------------------------------------

// An owned weapon or accessory as auto-equip ranks it: (d) the sum of its master_item stats at its
// level, each linear from the stat at level 1 to <stat>_max at the rarity's level_max (the compose
// table's; as gear.cpp's weapon_attack_int), over attack and intelligence for a weapon and attack,
// intelligence, defence, hit and guard for an accessory (hp and ap left out: other scales).
struct Candidate {
    ItemUid uid;
    double score = 0;
};
std::vector<Candidate> equip_candidates(Ctx& ctx, CharacterUid chara, bool weapon, u32 weapon_kind, bool take_from_others) {
    std::vector<Candidate> out;
    const char* column = weapon ? "weapon_uid" : "accessory_uid";
    ctx.st.q(std::string("select uid, master_item_id, level from items where item_type = ? and uid not in (select ") + column +
                 " from roster where " + column + " is not null and uid != ? and ?) order by uid",
             {weapon ? kWeaponItemType : kAccessoryItemType, chara, (int64_t)(take_from_others ? 0 : 1)}, [&](const Row& item_row) {
                 Candidate c{item_row.id<ItemUid>("uid")};
                 const u32 level = (u32)std::max<int64_t>(1, item_row.i("level"));
                 bool fits = true;
                 ctx.m.q(
                     "select i.*, w.master_weapon_kind_id as kind from master_item i left join master_weapon w on w.id = i.master_weapon_id "
                     "where i.id = ?",
                     {item_row.i("master_item_id")}, [&](const Row& master_row) {
                             // (a) a weapon of the role's kind (master_role / master_weapon master_weapon_kind_id)
                         if (weapon && (u32)master_row.i("kind") != weapon_kind) fits = false;
                         const u32 cap = (u32)ctx.m.one(std::string("select level_max from ") +
                                                            (weapon ? "master_item_compose" : "master_item_accessory_compose") + " where rarity = ?",
                                                        {master_row.i("rarity")}, 10);
                         const double t = cap > 1 ? std::min(1.0, (double)(level - 1) / (double)(cap - 1)) : 0.0;
                         static const char* const kWeaponStats[] = {"attack", "intelligence"};
                         static const char* const kAccessoryStats[] = {"attack", "intelligence", "defence", "hit", "guard"};
                         auto add = [&](const char* stat) {
                             const double lo = master_row.f(stat), hi = master_row.f((std::string(stat) + "_max").c_str());
                             c.score += lo + (std::max(hi, lo) - lo) * t;
                         };
                         if (weapon)
                             for (const char* stat : kWeaponStats) add(stat);
                         else
                             for (const char* stat : kAccessoryStats) add(stat);
                     });
                 if (fits) out.push_back(c);
             });
    return out;
}

// EquipAuto(u64 character_uid) -> EquipAutoRes                                   fid 7827ff6a
// API: docs/api.md#equipauto   Rules: docs/server-rules.md#equip-auto
//
// The equipment screen's 自動設定 for one character: the server picks.
//   (b) the request is the character's uid only, and CApiNotify::ApplyAutoEquipResult (@014d0444)
//       copies the answer's EquipWeaponResult / EquipAccessoryResult (the characters' weapon /
//       accessory, the items), SetAssistResultList (character_id, assist_id, old_assist_id) and
//       UpdateCharacterList (the skill slots) into the client's roster: the choice is the server's;
//   (a) the options are master_config auto_equip_steal (false: only items no other character
//       wears; uimsg_auto_equipment_config_text: with it, other characters' equipment and assists
//       are taken), auto_equip_skill (true: the skills are set) and auto_equip_assist (true); (d)
//       their defaults, the player's own settings aren't stored;
//   (d) the weapon: the owned weapon of the role's kind with the highest attack + intelligence at
//       its level (equip_candidates), the accessory likewise over its five stats; an item another
//       character wears moves (as EquipWeapon) only with auto_equip_steal; ties keep the lower uid;
//   (d) the skills (auto_equip_skill): empty slots take the role's open skills (master_role
//       master_skill1..5_id with master_skillN_open_level <= the level) not yet equipped, in that
//       order; equipped skills stay;
//   (d) the assist isn't changed (SetAssistResultList empty): which character the online server
//       chose isn't known.
//   Refused: unknown character (10208).
// Answers: the player state, EquipWeaponResult, EquipAccessoryResult (as EquipWeapon /
// EquipAccessory: the character, a previous wearer, the item), SetAssistResultList and
// UpdateCharacterList (the character's UpdateCharacter).
std::vector<u8> equip_auto(Ctx& ctx, const Request& req) {
    const CharacterUid uid = args::EquipAutoArgs::from(req).character_uid;
    Character chara = load_character(ctx, uid);
    if (!chara.found) return refuse(ctx, "EquipAuto", "unknown character", ErrorCode::kItemUnusable);
    // the player's options (api/settings/config.h): (a) master_config auto_equip_steal /
    // auto_equip_skill, the player's value (UpdateConfig) or else the master's default
    const bool steal = settings::config_on(ctx, "auto_equip_steal"), skills = settings::config_on(ctx, "auto_equip_skill");
    u32 weapon_kind = 0;
    std::vector<u32> open_skills;
    ctx.m.q("select * from master_role where id = ?", {chara.role_id}, [&](const Row& role_row) {
        weapon_kind = (u32)role_row.i("master_weapon_kind_id");
        for (int k = 1; k <= 5; k++) {
            const std::string n = std::to_string(k);
            const u32 skill = (u32)role_row.i(("master_skill" + n + "_id").c_str());
            if (skill && (u32)role_row.i(("master_skill" + n + "_open_level").c_str()) <= chara.level) open_skills.push_back(skill);
        }
    });
    Value data = ctx.base_data();
    std::string picked_log;
    for (bool weapon : {true, false}) {
        std::vector<Candidate> candidates = equip_candidates(ctx, uid, weapon, weapon_kind, steal);
        std::vector<std::pair<CharacterUid, u64>> characters;
        std::optional<ItemUid> item;
        const char* column = weapon ? "weapon_uid" : "accessory_uid";
        const Candidate* best = nullptr;
        for (const Candidate& c : candidates)
            if (!best || c.score > best->score) best = &c;
        if (best) {
            std::optional<CharacterUid> previous_owner;
            ctx.st.q(std::string("select uid from roster where ") + column + " = ? and uid != ?", {best->uid, uid},
                     [&](const Row& roster_row) { previous_owner = roster_row.id<CharacterUid>("uid"); });
            if (previous_owner) ctx.st.q(std::string("update roster set ") + column + " = null where uid = ?", {*previous_owner});
            ctx.st.q(std::string("update roster set ") + column + " = ? where uid = ?", {best->uid, uid});
            characters.emplace_back(uid, best->uid.v);
            if (previous_owner) characters.emplace_back(*previous_owner, 0);
            item = best->uid;
            picked_log += std::string(weapon ? " weapon " : " accessory ") + std::to_string(best->uid.v);
        }
        data[weapon ? "EquipWeaponResult" : "EquipAccessoryResult"] = equip_result(weapon, characters, item);
    }
    if (skills) {
        std::vector<u32> slots(3, 0);
        ctx.st.q("select equip_skill1, equip_skill2, equip_skill3 from roster where uid = ?", {uid}, [&](const Row& roster_row) {
            for (int k = 0; k < 3; k++) slots[k] = (u32)roster_row.i(("equip_skill" + std::to_string(k + 1)).c_str());
        });
        size_t next = 0;
        for (u32& slot : slots) {
            if (slot) continue;
            while (next < open_skills.size() && std::find(slots.begin(), slots.end(), open_skills[next]) != slots.end()) next++;
            if (next < open_skills.size()) slot = open_skills[next++];
        }
        ctx.st.q("update roster set equip_skill1 = nullif(?, 0), equip_skill2 = nullif(?, 0), equip_skill3 = nullif(?, 0) where uid = ?",
                 {slots[0], slots[1], slots[2], uid});
        picked_log += " skills " + std::to_string(slots[0]) + "," + std::to_string(slots[1]) + "," + std::to_string(slots[2]);
    }
    data["SetAssistResultList"] = Value::array();
    Value updated = Value::array();
    updated.push(update_character_value(ctx, uid, skills));
    data["UpdateCharacterList"] = updated;
    // read by port/scripts/equipment_session.sh
    LOGI("server", "EquipAuto %llx:%s", (unsigned long long)uid.v, picked_log.empty() ? " nothing to equip" : picked_log.c_str());
    return body(data);
}

// ChangeRole(u64 character_uid, u32 master_role_id) -> ChangeRoleRes                  fid 720e2bac
// API: docs/api.md#changerole   Rules: docs/server-rules.md#role-change
//
// Switches a role-changeable character to another of its roles (装備・技・アシスト変更 -> ロール選択,
// CRoleSelect; its request lambda @01c72678 sends the screen's character and the chosen role).
//   (a) master_role_change: the new role has a row whose person_id is the character's role's
//       master_person_id and whose rarity is the character's (b: uimsg_evolution_role_change_description
//       "このキャラクターは進化した為 ... ロールを変更できるようになります": the evolved form), inside the
//       row's opened_at / closed_at when it sets them.
//   (b) The set skills are reset (uimsg_evolution_role_change_done "セットしたスキルが初期化されます"):
//       roster equip_skill1..3 and (d) the character's skills in every party set.
//   (d) Level, EXP, skill levels, limit break, awakening and equipment are kept.
//   Refused: unknown character, a role it can't take, its own role (10208).
// Answers: the player state, UpdateCharacter (OnChangeRoleRes copies it into the character), and
// PartySet when a party set's skills were reset.
std::vector<u8> change_role(Ctx& ctx, const Request& req) {
    const auto args = args::ChangeRoleArgs::from(req);
    const CharacterUid uid = args.character_uid;
    Character chara = load_character(ctx, uid);
    if (!chara.found) return refuse(ctx, "ChangeRole", "unknown character", ErrorCode::kItemUnusable);
    if (chara.role_id == args.role_id) return refuse(ctx, "ChangeRole", "its own role", ErrorCode::kItemUnusable);
    const int64_t person = ctx.m.one("select master_person_id from master_role where id = ?", {chara.role_id});
    bool allowed = false;
    const std::string now = ctx.fmt_time(ctx.now());
    ctx.m.q("select * from master_role_change where master_role_id = ? and person_id = ? and rarity = ?", {args.role_id, person, chara.rarity},
            [&](const Row& change_row) {
                const std::string from = change_row.s("opened_at"), to = change_row.s("closed_at");
                if ((from.empty() || from <= now) && (to.empty() || now <= to)) allowed = true;
            });
    if (!allowed) return refuse(ctx, "ChangeRole", "not one of the character's roles (master_role_change)", ErrorCode::kItemUnusable);
    ctx.st.q("update roster set role_id = ?, equip_skill1 = null, equip_skill2 = null, equip_skill3 = null where uid = ?", {args.role_id, uid});
    const int64_t in_sets = ctx.st.one(
        "select count(*) from party_member where uid = ? and (skill_id1 is not null or skill_id2 is not null or skill_id3 is not null)", {uid});
    ctx.st.q("update party_member set skill_id1 = null, skill_id2 = null, skill_id3 = null where uid = ?", {uid});
    Value data = ctx.base_data();
    data["UpdateCharacter"] = update_character_value(ctx, uid, true);
    if (in_sets) data["PartySet"] = party_set_info(ctx);
    // read by mastery_session.sh
    LOGI("server", "ChangeRole %llx: role %u -> %u", (unsigned long long)uid.v, chara.role_id.v, args.role_id.v);
    return body(data);
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_growth() {
    using namespace ext;
    add_api({"BoostCharacter"}, boost_character);
    add_api({"LimitBreakCharacter", "LimitBreakCharacter_Legacy"}, limit_break_character);
    add_api({"EvolutionCharacter"}, evolution_character);
    add_api({"UpdateAwakenLevel"}, update_awaken_level);
    add_api({"AddStatusCharacter"}, add_status_character);
    add_api({"EquipWeapon", "EquipAccessory"}, equip_item);
    add_api({"EquipSkill"}, equip_skill);
    add_api({"EquipAuto"}, equip_auto);
    add_api({"ChangeRole"}, change_role);
}

}  // namespace soa::server
