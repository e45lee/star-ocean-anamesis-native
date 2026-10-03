// The roster as the client receives it: CPersonInfo (api/player/roster.h). Port code, not guest
// behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption (docs/server-rules.md "Player load").
#include "api/player/roster.h"

#include "api/player/player_info.h"  // player_id

namespace soa::server {

using ext::Row;

// One owned character (CPersonInfo; the client keeps them at CParameterManager+0x1178, by uid).
// The keys are CPersonInfo's fields (b: port/fakeapi/fields.txt); `id` is the character's uid.
Value person_info(ext::Ctx& ctx, const Row& roster_row, u32 owner_player_id) {
    Value info = Value::object();
    u32 role = (u32)roster_row.i("role_id");
    info["id"] = (u64)roster_row.i("uid");
    info["player_id"] = owner_player_id;
    info["master_role_id"] = role;
    info["level"] = (u32)roster_row.i("level");
    info["exp"] = (u32)roster_row.i("exp");
    info["limit_break_count"] = (u32)roster_row.i("limit_break");
    info["awaken_level"] = (u32)roster_row.i("awaken");
    // the equipped weapon's and accessory's item uids (EquipWeapon / EquipAccessory; 0 = none)
    info["weapon_item_id"] = (u64)roster_row.i("weapon_uid");
    info["accessory_item_id"] = (u64)roster_row.i("accessory_uid");
    // The assist pair (SetAssist, api/player/assist.cpp): whom this character has as assist, and
    // whom it assists (b: the CPersonInfo keys), so the pairs survive a restart and reach
    // MissionStart's party status.
    info["assist_character_id"] = (u64)ctx.st.one("select assist_uid from assist where uid = ?", {roster_row.i("uid")}, 0);
    info["assisting_character_id"] = (u64)ctx.st.one("select uid from assist where assist_uid = ?", {roster_row.i("uid")}, 0);
    // (a) the role's three skills (master_role master_skillN_id_label) at the character's skill
    // levels, and its rush skill and gauge
    ctx.m.q("select * from master_role where id = ?", {role}, [&](const Row& role_row) {
        for (int k = 1; k <= 3; k++) {
            std::string label_column = "master_skill" + std::to_string(k) + "_id_label";
            info["skill" + std::to_string(k) + "_label"] = role_row.s(label_column.c_str());
            info["skill" + std::to_string(k) + "_level"] = (u32)roster_row.i(("skill" + std::to_string(k)).c_str());
        }
        info["rush1_label"] = role_row.s("rush_skill1_id_label");
        info["rush1_level"] = 1u;  // (d)
        info["rush_skill1_factor_id"] = (u32)role_row.i("rush_skill1_factor_id");
        info["rush_gauge_max"] = (u32)role_row.f("rush_gauge_max");
        info["rush_gauge_use"] = (u32)role_row.f("rush_gauge_use");
    });
    // (b) CPersonInfo add_hp .. add_ap: the seeds the client's status computation adds
    // (AddStatusCharacter; the table is api/growth/growth.cpp's)
    if (ctx.st.one("select count(*) from sqlite_master where name = 'roster_ext'", {}))
        ctx.st.q("select * from roster_ext where uid = ?", {roster_row.i("uid")}, [&](const Row& ext_row) {
            for (const char* k : {"add_hp", "add_attack", "add_intelligence", "add_defence", "add_hit", "add_guard", "add_ap"})
                info[k] = (u32)ext_row.i(k);
        });
    return info;
}

// Character: every owned character (CPersonInfo), by uid.
Value roster_info(ext::Ctx& ctx) {
    Value characters = Value::array();
    u32 owner = player_id(ctx);
    ctx.st.q("select * from roster order by uid", {}, [&](const Row& roster_row) { characters.push(person_info(ctx, roster_row, owner)); });
    return characters;
}

}  // namespace soa::server
