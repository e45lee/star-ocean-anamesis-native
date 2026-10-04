// The player's options (設定 > その他設定 / バトル設定; api/settings/README.md). Port code, not guest
// behaviour; every rule carries its source label, (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption. Rules in docs/server-rules.md#settings.
//
// What the client reads (b):
//  - `ConfigInfoList`: CConfigInfoList, an InfoBaseArray<CConfigInfo> ({master_config_id, value,
//    type}: CConfigInfo::Initialize), kept in CParameterManager+0x9480 (0xd8-byte elements). The
//    whole list is replaced by a response that carries it.
//  - CUIUtility::IsConfigListCheck (@01eea65c) finds an option there by CHash32(id_label) and
//    reads it as on when its value is "true"; an option not in the list is the caller's default
//    (false for the one-time storage ones). Its readers aren't only the settings screen
//    (CSystemSettingMenu::SetupOtherSetting): CItemNumWarning, CPresentbox::IsNumWarning,
//    CMissionMenu::StateCheckPlayStart, CTradeMenu, MissionUtility::GetItemNumWarningType (the
//    one-time storage options), CUIUtility::IsAutoEquipSkill / IsAutoEquipSteal(Party) and
//    IsGalaxyPassIconShow. Only the settings screen's CSystemSettingMenu::StartOtherSetting sends
//    GetConfig, so the player load carries the list too (load_config below).
//  - `ConfigInfo` (UpdateConfig's answer): CApiNotify::OnUpdateConfigRes (@014d89a0) puts the
//    answered ConfigInfo (CParameterManager+0x9498) into the list, replacing the entry with its
//    master_config_id or appending it, whatever the body holds: the answer must carry it.
//
// State: the table `config` (schema version 13): the options the player changed, by
// master_config id; an option without a row is the master's default.
#include "api/settings/config.h"

#include <cstdio>
#include <string>
#include <vector>

#include "api/settings/settings.h"
#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "soaserver/chash32.h"

namespace soa::server {

namespace args {
// UpdateConfig(u32 master_config_id, s8 const* value, u32 type) (b: CSystemSettingMenu's
// AutoEquipSettingSend and tNotifyData send it; the wire's u32 · char[191] · u32).
struct UpdateConfigArgs {
    u32 master_config_id = 0;
    std::string value;
    u32 type = 0;
    static UpdateConfigArgs from(const Request& r) {
        return {r.ints.size() > 0 ? (u32)r.ints[0] : 0u, r.strs.empty() ? std::string() : r.strs[0], r.ints.size() > 1 ? (u32)r.ints[1] : 0u};
    }
};
}  // namespace args

namespace settings {

namespace {

using ext::Row;

// One CConfigInfo.
Value config_info(u32 master_config_id, const std::string& value, u32 type) {
    Value info = Value::object();
    info["master_config_id"] = master_config_id;
    info["value"] = value;
    info["type"] = type;
    return info;
}

// ConfigInfoList: every master_config row (a), with the player's value and type where the player
// changed it (the table `config`), else the master's default (a: master_config.value / type).
Value config_info_list(ext::Ctx& ctx) {
    Value list = Value::array();
    ctx.m.q("select id, value, type from master_config order by id", {}, [&](const Row& master_row) {
        const u32 id = (u32)master_row.i("id");
        std::string value = master_row.s("value");
        u32 type = (u32)master_row.i("type");
        ctx.st.q("select value, type from config where master_config_id = ?", {id}, [&](const Row& own) {
            value = own.s("value");
            type = (u32)own.i("type");
        });
        list.push(config_info(id, value, type));
    });
    return list;
}

bool is_config(ext::Ctx& ctx, u32 master_config_id) { return ctx.m.one("select count(*) from master_config where id = ?", {master_config_id}) > 0; }

// OnPlayerLoad: ConfigInfoList                           on Login, SimpleLogin, CreatePlayer, GetPlayer, NoLoginStart
// Rules: docs/server-rules.md#settings
//
//   (b) The options' readers outside the settings screen (above) see only what a response put in
//       CParameterManager+0x9480, and only the settings screen asks for it: without the list in
//       the player load, a changed option (一時保管庫設定) would be off again after a restart until
//       the settings screen is opened, and the master's "true" defaults (auto_equip_skill, ...)
//       would read as off.
//   (d) Nothing without a player (the new-player flow's NoLoginStart).
// Adds: data.ConfigInfoList (every option: the player's value, else the master's default).
void load_config(ext::Ctx& ctx, const Request&, Value& data) {
    if (!ctx.st.one("select count(*) from player", {})) return;  // no player yet (new-player flow)
    data["ConfigInfoList"] = config_info_list(ctx);
}

// GetConfig() -> GetConfigRes                                                   fid 8fcedcac
// API: docs/api.md#getconfig
// Rules: docs/server-rules.md#settings
//
// The options the settings screen shows (CSystemSettingMenu::StartOtherSetting sends it, then
// SetupOtherSetting reads the list).
//   (a) Every master_config row, the player's value where changed, else master_config.value.
//   (d) `Option` (COptionInfo: frame rate, volumes, ...) isn't sent: the client keeps those
//       settings itself, and a response without the key leaves the client's copy as it was.
// Answers: the player state and ConfigInfoList.
std::vector<u8> get_config(ext::Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["ConfigInfoList"] = config_info_list(ctx);
    return ext::body(data);
}

// UpdateConfig(u32 master_config_id, s8 const* value, u32 type) -> UpdateConfigRes  fid f82ca7ca
// API: docs/api.md#updateconfig
// Rules: docs/server-rules.md#settings
//
// One option the player changed (e.g. その他設定 > 一時保管庫設定: UpdateConfig(4025152546, "true", 4)).
//   (b) The value string and its type are stored as sent (the client's own "true" / "false"; the
//       option's readers compare the string).
//   (d) An id master_config doesn't have is refused with kInvalidOperation (10403): the client
//       only sends master ids.
// Answers: the player state and ConfigInfo (the stored option; OnUpdateConfigRes puts it in the list).
std::vector<u8> update_config(ext::Ctx& ctx, const Request& req) {
    const auto a = args::UpdateConfigArgs::from(req);
    if (!is_config(ctx, a.master_config_id)) return ext::refuse(ctx, req.method.c_str(), "not a master_config id", ErrorCode::kInvalidOperation);
    ctx.st.q(
        "insert into config (master_config_id, value, type) values (?, ?, ?) "
        "on conflict (master_config_id) do update set value = excluded.value, type = excluded.type",
        {a.master_config_id, a.value, a.type});
    LOGI("server", "UpdateConfig %u: \"%s\" (type %u)", a.master_config_id, a.value.c_str(), a.type);
    Value data = ctx.base_data();
    data["ConfigInfo"] = config_info(a.master_config_id, a.value, a.type);
    return ext::body(data);
}

// ResetConfig() -> ResetConfigRes                                               fid 685d66f3
// API: docs/api.md#resetconfig
// Rules: docs/server-rules.md#settings
//
// 初期設定に戻す (CSystemSettingMenu::ProgressResetApi).
//   (a) Every option back to the master's default (master_config.value): the player's rows are
//       deleted.
// Answers: the player state and ConfigInfoList (the defaults).
std::vector<u8> reset_config(ext::Ctx& ctx, const Request&) {
    ctx.st.q("delete from config", {});
    LOGI("server", "ResetConfig: every option back to master_config's default");
    Value data = ctx.base_data();
    data["ConfigInfoList"] = config_info_list(ctx);
    return ext::body(data);
}

}  // namespace

std::string config_value(ext::Ctx& ctx, u32 master_config_id) {
    std::string value;
    bool own = false;
    ctx.st.q("select value from config where master_config_id = ?", {master_config_id}, [&](const Row& r) {
        value = r.s("value");
        own = true;
    });
    if (!own) ctx.m.q("select value from master_config where id = ?", {master_config_id}, [&](const Row& r) { value = r.s("value"); });
    return value;
}

bool config_on(ext::Ctx& ctx, u32 master_config_id) { return config_value(ctx, master_config_id) == "true"; }

bool config_on(ext::Ctx& ctx, const char* id_label) { return config_on(ctx, chash32(id_label)); }

void register_config() {
    ext::add_api({"GetConfig"}, get_config);
    ext::add_api({"UpdateConfig"}, update_config);
    ext::add_api({"ResetConfig"}, reset_config);
    ext::add_player_load(load_config);
}

}  // namespace settings

}  // namespace soa::server
