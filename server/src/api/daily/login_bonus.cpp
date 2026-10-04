// The login bonus (ログインボーナス): a player-load hook, sent with the full-state player
// responses. Port code, not guest behaviour. The achievements are api/presents/achievements.cpp.
// Rules: docs/server-rules.md#login-bonus and docs/server-rules.md#login-bonus-modules;
// every rule carries its source label: (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption.
//
// State: table `login_bonus` (id = master_login_bonus id, day_index = the last page granted, last_at),
// and player.login_bonus_popup_pending (a day NoLoginStart granted, to report again).
#include <ctime>

#include "core/log.h"
#include "core/time.h"
#include "soaserver/ext.h"
#include "rules/growth_rules.h"
#include "core/modules.h"

namespace soa::server {

namespace {
using namespace ext;

// (b) CParameterUtility::IsTutorialClear = tutorial_status (CPlayerInfo, CParameterManager+0xdd8)
// >= CPhase_TutorialNext::LastMemId() = 9.
constexpr u32 kTutorialCleared = 9;

// Player.tutorial_status: (b) the popups (login bonus included) only open for a player past the
// tutorial (IsTutorialClear). (d) The seeded account (rank 87) has finished it: 9, unless another
// module already set the field. A player rule, kept in this hook because it is the first
// player-load hook to run (core/modules.cpp).
void default_tutorial_status(Value& data) {
    Value* player = nullptr;
    for (auto& entry : data.map)
        if (entry.first == "Player") player = &entry.second;
    if (player && player->type == Value::Map && !player->find("tutorial_status")) (*player)["tutorial_status"] = kTutorialCleared;
}

// Grants the next page of an open login bonus, if it has one: (a) is_loop and order_idx
// (growth_rules::next_login_day). Its master_login_bonus_contents rows go to the present box (c).
// Returns the page granted, 0 for none.
u32 grant_next_page(Ctx& ctx, const Row& bonus_row, u32 day) {
    u32 id = (u32)bonus_row.i("id");
    u32 last_idx = (u32)ctx.m.one("select max(order_idx) from master_login_bonus_contents where master_login_bonus_id = ?", {id});
    u32 next = growth_rules::next_login_day(day, last_idx, bonus_row.i("is_loop") != 0);
    if (!next) return 0;
    ctx.m.q("select * from master_login_bonus_contents where master_login_bonus_id = ? and order_idx = ?", {id, next}, [&](const Row& content) {
        // (a) Present_box_1 "%s %d日目": the bonus's name and the day; (d) the reason number
        // (ext.h PresentReason; present_texts.cpp)
        add_present(ctx, (u32)content.i("content_type"), (u32)content.i("content_id"), (u32)content.i("num"), kPresentLoginBonus, id,
                    format_present(text(ctx.m, "Present_box_1"), text(ctx.m, bonus_row.s("name_message_id")), next));
    });
    LOGI("server", "login bonus %s: day %u", bonus_row.s("id_label").c_str(), next);
    return next;
}

// OnPlayerLoad hook (the first player-load hook: core/modules.cpp): the login bonus.
// Rules: docs/server-rules.md#login-bonus, docs/server-rules.md#login-bonus-modules
//
// On a full-state player response (Login, SimpleLogin, CreatePlayer, GetPlayer, NoLoginStart):
// every open master_login_bonus (a) advances one day the first time after the daily reset (a)+(b)
// and puts that day's master_login_bonus_contents row in the present box (c). LoginBonus lists the
// open bonuses; is_received_now is set only in the response that granted the day (d; the popup
// condition is (b): CPopupManager::CheckStart, LoginBonusModel::GetList). The premium login bonus
// needs a purchased pass: premium_and_favor_bonus.cpp (d).
//   (b) The popup itself is the client's: 3.7.0's CPhase_Login::Progress arms the popup checks
//       (CPopupManager::AddPopup()) after a login once the tutorial is cleared, and
//       CPopupManager::CheckStart opens the login bonus from this LoginBonus list.
// Adds: LoginBonus (CLoginBonusInfo {master_login_bonus_id, current_idx, is_received_now}),
// PresentBoxCount when a day is granted or reported, and the default Player.tutorial_status.
void login_bonus(Ctx& ctx, const Request& req, Value& data) {
    default_tutorial_status(data);
    ServerTime t = ctx.now();
    // (a)+(b) the login day starts at master_global login_bonus_reset_hour (CParameterUtility::LoginBonusResetHour)
    ServerTime today = day_start(t, (int)ctx.global_u32("login_bonus_reset_hour", 4));
    Value list = Value::array();
    int granted = 0;
    // (b)+(d) The popup reads is_received_now from the last LoginBonus the client got. With the
    // 3.7.0 login the title's NoLoginStart grants the day and the Login right after it loads the
    // player again: a day granted by NoLoginStart is reported as received-now once more on that
    // Login, so the popup the login arms (CPopupManager::AddPopup) finds it.
    bool login = req.method == "Login" || req.method == "SimpleLogin";
    bool pending = login && ctx.st.one("select login_bonus_popup_pending from player", {}) != 0;
    ctx.m.q("select * from master_login_bonus order by order_id", {}, [&](const Row& bonus_row) {
        if (!open_at(bonus_row.s("opened_at"), bonus_row.s("closed_at"), t)) return;
        u32 id = (u32)bonus_row.i("id");
        u32 day = 0;
        ServerTime last_at;  // no row: 0, before every day
        ctx.st.q("select day_index, last_at from login_bonus where id = ?", {id}, [&](const Row& state_row) {
            day = (u32)state_row.i("day_index");
            last_at = state_row.time("last_at");
        });
        bool received_now = pending && last_at >= today;
        if (received_now) granted++;
        if (last_at < today) {
            if (u32 next = grant_next_page(ctx, bonus_row, day)) {
                day = next;
                received_now = true;
                granted++;
            }
            ctx.st.q("insert or replace into login_bonus (id, day_index, last_at) values (?, ?, ?)", {id, day, t});
        }
        if (!day) return;
        Value info = Value::object();
        info["master_login_bonus_id"] = id;
        info["current_idx"] = day;
        info["is_received_now"] = received_now;
        list.push(info);
    });
    data["LoginBonus"] = list;
    if (pending) ctx.st.q("update player set login_bonus_popup_pending = 0", {});
    else if (granted && req.method == "NoLoginStart") ctx.st.q("update player set login_bonus_popup_pending = 1", {});
    if (granted) data["PresentBoxCount"] = (u32)ctx.st.one("select count(*) from presents where received_at is null", {});
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_login_bonus() {
    using namespace ext;
    add_player_load(login_bonus);
}

}  // namespace soa::server
