// The roster as the client receives it: CPersonInfo (api/player/roster.h). Port code, not guest
// behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption (docs/server-rules.md#player-load).
#include "api/player/roster.h"

#include "api/growth/mastery.h"

#include "api/player/player_info.h"  // player_id

namespace soa::server {

using ext::Row;

// One owned character (CPersonInfo; the client keeps them at CParameterManager+0x1178, by uid).
// The keys are CPersonInfo's fields (b: port/fakeapi/fields.txt); `id` is the character's uid.
Value person_info(ext::Ctx& ctx, const Row& roster_row, PlayerId owner_player_id) {
    Value info = Value::object();
    const CharacterUid uid = roster_row.id<CharacterUid>("uid");
    const RoleId role = roster_row.id<RoleId>("role_id");
    info["id"] = uid.v;
    info["player_id"] = owner_player_id.v;
    info["master_role_id"] = role.v;
    info["level"] = (u32)roster_row.i("level");
    info["exp"] = (u32)roster_row.i("exp");
    info["limit_break_count"] = (u32)roster_row.i("limit_break");
    info["awaken_level"] = (u32)roster_row.i("awaken");
    // the equipped weapon's and accessory's item uids (EquipWeapon / EquipAccessory; 0 = none)
    info["weapon_item_id"] = or_zero(roster_row.opt<ItemUid>("weapon_uid"));
    info["accessory_item_id"] = or_zero(roster_row.opt<ItemUid>("accessory_uid"));
    // The assist pair (SetAssist, api/player/assist.cpp): whom this character has as assist
    // (roster.assist_uid; NULL: none, 0), and whom it assists (the character whose assist_uid it
    // is) (b: the CPersonInfo keys), so the pairs survive a restart and reach MissionStart's party
    // status.
    info["assist_character_id"] = or_zero(roster_row.opt<CharacterUid>("assist_uid"));
    info["assisting_character_id"] = or_zero(ctx.st.one_opt<CharacterUid>("select uid from roster where assist_uid = ?", {uid}));
    // (a) the role's three skills (master_role master_skillN_id_label) at the character's skill
    // levels, and its rush skill and gauge
    ctx.m.q("select * from master_role where id = ?", {role}, [&](const Row& role_row) {
        for (int k = 1; k <= 3; k++) {
            std::string label_column = "master_skill" + std::to_string(k) + "_id_label";
            info["skill" + std::to_string(k) + "_label"] = role_row.s(label_column.c_str());
            info["skill" + std::to_string(k) + "_level"] = (u32)roster_row.i(("skill" + std::to_string(k) + "_level").c_str());
        }
        info["rush1_label"] = role_row.s("rush_skill1_id_label");
        info["rush1_level"] = 1u;  // (d)
        info["rush_skill1_factor_id"] = (u32)role_row.i("rush_skill1_factor_id");
        info["rush_gauge_max"] = (u32)role_row.f("rush_gauge_max");
        info["rush_gauge_use"] = (u32)role_row.f("rush_gauge_use");
    });
    // (b) CPersonInfo add_hp .. add_ap: the seeds the client's status computation adds
    // (AddStatusCharacter, api/growth/growth.cpp), for a character with growth (has_growth)
    if (has_growth(roster_row))
        for (const char* k : {"add_hp", "add_attack", "add_intelligence", "add_defence", "add_hit", "add_guard", "add_ap"})
            info[k] = (u32)roster_row.i(k);
    // (b) CPersonInfo parent_master_role_id / mastery_talent_id: what a 弟子 inherited once its
    // five mastery trainings are cleared (api/growth/mastery.cpp; tCharaData::InitializeMastery
    // reads them), sent for a graduated disciple only
    MasteryInheritance inh = mastery_inheritance(ctx, uid);
    if (inh.graduated) {
        info["parent_master_role_id"] = inh.parent_master_role_id;
        info["mastery_talent_id"] = inh.mastery_talent_id;
    }
    return info;
}

bool has_growth(const Row& roster_row) {
    for (const char* k : {"add_hp", "add_attack", "add_intelligence", "add_defence", "add_hit", "add_guard", "add_ap"})
        if (roster_row.i(k)) return true;
    for (const char* k : {"equip_skill1", "equip_skill2", "equip_skill3"})
        if (!roster_row.null(k)) return true;
    return false;
}

bool owns_character(ext::Ctx& ctx, CharacterUid uid) { return uid.v && ctx.st.one("select count(*) from roster where uid = ?", {uid}) > 0; }

// Character: every owned character (CPersonInfo), by uid.
Value roster_info(ext::Ctx& ctx) {
    Value characters = Value::array();
    const PlayerId owner = player_id(ctx);
    ctx.st.q("select * from roster order by uid", {}, [&](const Row& roster_row) { characters.push(person_info(ctx, roster_row, owner)); });
    return characters;
}

}  // namespace soa::server
