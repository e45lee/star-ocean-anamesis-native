// Player titles (称号; api/player/README.md). Port code, not guest behaviour; every rule carries its
// source label, (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
// Rules in docs/server-rules.md "Titles".
//
// What the client reads (b):
//  - `TitleList`: the owned titles. CTitleList is an InfoBaseValueArray<u32> (its vtable's
//    DeserializeArray), i.e. a plain array of master_title ids, kept in CParameterManager+0x71d8
//    (0x30-byte CParameterPropertyValue elements, the id at +0x28). CHonorMenu::SetupTitleData
//    lists exactly those ids (CMasterParameterTitle::ParameterTitleList: "SELECT * FROM
//    master_title WHERE id IN (...)"); the client adds no default titles itself.
//  - `Player.title` (CParameterManager+0xed8): the selected title. CCommon::UpdateMyStatus ->
//    CParameterUtility::SetPlayerTitle -> GetPlayerInfoTitle looks it up in master_title (plate
//    tips_resource, name name_message_id); 0 or an unknown id hides the plate.
//  - `SetTitle(u32 master_title_id)` (CHonorMenu::CallApiSetTitle, fid 4332363c) expects
//    `Player.title` back (CHonorMenu::UpdateTitleData marks the entry equal to +0xed8).
// How titles were earned (a): 355 of the 385 master_title rows are master_achievement rewards
// (content_type 13); the 30 others are the 26 `is_default` titles (title_other_0001..0026) and
// four event titles (title_bring_0010/0014/0015, title_battle_0025) no master row awards.
//
// State: the table `titles` (the owned ids) and the meta key `title` (the selected id).
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>

#include "core/log.h"
#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "core/errors.h"
#include "core/modules.h"
#include "core/request_context.h"

namespace soa::server {

namespace args {
// SetTitle(u32 master_title_id): 0 takes the title off (also when the argument is missing). The
// module's own args struct (core/request_args.h holds the core handlers').
struct SetTitleArgs {
    u32 title_id = 0;
    static SetTitleArgs from(const Request& req) { return {req.ints.empty() ? 0 : (u32)req.ints[0]}; }
};
}  // namespace args

namespace {

using ext::Row;

// (a) docs/api.md "Content types": master_achievement.content_type 13 is a master_title id.
constexpr u32 kContentTypeTitle = 13;

bool is_title(ext::Ctx& ctx, int64_t title_id) { return title_id && ctx.m.one("select count(*) from master_title where id = ?", {title_id}) > 0; }

bool owns_title(ext::Ctx& ctx, u32 title_id) { return ctx.st.one("select count(*) from titles where id = ?", {title_id}) > 0; }

// (a) is_default = 1 titles are every player's; (d) the server lists them as owned (the client
// lists only TitleList ids, so without them a new player's list would be empty).
void ensure_default_titles(ext::Ctx& ctx) {
    ctx.m.q("select id from master_title where is_default = 1", {},
            [&](const Row& title_row) { ctx.st.q("insert or ignore into titles (id, got_at) values (?, 0)", {title_row.i("id")}); });
}

// TitleList: the owned master_title ids, the default ones included.
Value title_list(ext::Ctx& ctx) {
    ensure_default_titles(ctx);
    Value list = Value::array();
    ctx.st.q("select id from titles order by id", {}, [&](const Row& title_row) { list.push((u32)title_row.i("id")); });
    return list;
}

// The selected title (meta "title"). (d) A player who never chose one wears the first default
// title (lowest order_id, title_other_0001): 3.7.0's choice for a new player isn't known, and
// with 0 the status bar's plate stays hidden. That default is stored on the first read.
u32 selected_title(ext::Ctx& ctx) {
    int64_t stored = -1;
    ctx.st.q("select value from meta where key = 'title'", {}, [&](const Row& meta_row) { stored = std::stoll(meta_row.s("value")); });
    if (stored >= 0) return (u32)stored;
    u32 first_default = (u32)ctx.m.one("select id from master_title where is_default = 1 order by order_id, id limit 1", {});
    ctx.st.q("insert or replace into meta (key, value) values ('title', ?)", {std::to_string(first_default)});
    return first_default;
}

void select_title(ext::Ctx& ctx, u32 title_id) {
    ctx.st.q("insert or replace into meta (key, value) values ('title', ?)", {std::to_string(title_id)});
}

void set_player_title(Value& data, u32 title_id) {
    if (Value* player = data.find_mut("Player"); player && player->type == Value::Map) (*player)["title"] = title_id;
}

// Grant (content type 13): a title                        from the present box (achievement rewards)
// Rules: docs/server-rules.md "Titles" (Grant)
//
//   (a) Content type 13 is a master_title id (docs/api.md "Content types",
//       master_achievement.content_type 13 -> master_title ids); an id not in master_title is
//       logged and skipped.
//   (d) The title joins the owned list; a title owned already changes nothing.
// Adds: the id to the request's titles_added, which report_added_titles answers.
void grant_title(ext::Ctx& ctx, u32 title_id, u32, Value&, Value&, Value&) {
    if (!is_title(ctx, title_id)) {
        LOGW("server", "title %u: not in master_title", title_id);
        return;
    }
    if (owns_title(ctx, title_id)) return;
    ctx.st.q("insert into titles (id, got_at) values (?, ?)", {title_id, ctx.now()});
    ctx.request->titles_added.push_back(title_id);  // for AddTitleList / PresentGetResult.result.Title (OnResponse)
    LOGI("server", "title %u granted", title_id);
}

// OnPlayerLoad: TitleList, Player.title                   on Login, SimpleLogin, CreatePlayer, GetPlayer, NoLoginStart
// Rules: docs/server-rules.md "Titles"
//
//   (b) TitleList and Player.title are what CHonorMenu and the status bar read (above).
//   (d) Nothing without a player (the new-player flow's NoLoginStart).
// Adds: data.TitleList (the owned titles, the defaults included) and Player.title (the selected one).
void load_titles(ext::Ctx& ctx, const Request&, Value& data) {
    if (!ctx.st.one("select count(*) from player", {})) return;  // no player yet (new-player flow)
    data["TitleList"] = title_list(ctx);
    set_player_title(data, selected_title(ctx));
}

// SetTitle(u32 master_title_id) -> SetTitleRes                                 fid 4332363c
// API: docs/api.md#settitle
// Rules: docs/server-rules.md "Titles"
//
// Selects the title the status bar's plate shows.
//   (b) CHonorMenu::CallApiSetTitle sends it; CHonorMenu::UpdateTitleData expects Player.title back.
//   (d) An id the player doesn't own is refused with kItemUnusable (10208, the generic refusal).
//   (b) 0 takes the title off (the 外す button, the client's "称号を外しました" dialog); (d)
//       CHonorMenu's remove button (ChangeRemoveButtonActive) is the only way the client could
//       send 0.
// Answers: the player state with Player.title, and TitleList.
std::vector<u8> set_title(ext::Ctx& ctx, const Request& req) {
    const auto args = args::SetTitleArgs::from(req);
    ensure_default_titles(ctx);
    if (args.title_id && !owns_title(ctx, args.title_id)) return ext::refuse(ctx, req.method.c_str(), "title not owned", ErrorCode::kItemUnusable);
    select_title(ctx, args.title_id);
    Value data = ctx.base_data();
    set_player_title(data, args.title_id);
    data["TitleList"] = title_list(ctx);
    LOGI("server", "SetTitle %u", args.title_id);  // read by port/scripts/home_session.sh
    return ext::body(data);
}

// OnResponse: the titles this request granted             on every answered response
// Rules: docs/server-rules.md "Titles" (Grant)
//
//   (b) The keys (docs/api.md; CPresentBoxReceiveTitleInfo): a response that granted titles
//       carries the new list TitleList (state), AddTitleList (the per-response result) and, for a
//       present receive, PresentGetResult.result.Title ({master_title_id}). Player.title is in
//       every Player the core sends (api/player/player_info.cpp player_info, meta "title").
// Adds: those keys when grant_title added a title during the request; nothing otherwise.
bool report_added_titles(ext::Ctx& ctx, const Request&, Value& data) {
    std::vector<u32> added;
    added.swap(ctx.request->titles_added);
    if (added.empty()) return false;
    data["TitleList"] = title_list(ctx);
    Value added_list = Value::array();
    for (u32 title_id : added) added_list.push(title_id);
    data["AddTitleList"] = added_list;
    if (Value* present_result = data.find_mut("PresentGetResult"); present_result && present_result->type == Value::Map) {
        Value& result = (*present_result)["result"];
        if (result.type != Value::Map) result = Value::object();
        Value titles = Value::array();
        for (u32 title_id : added) {
            Value entry = Value::object();
            entry["master_title_id"] = title_id;
            titles.push(entry);
        }
        result["Title"] = titles;
    }
    return true;
}

// ---- tests ------------------------------------------------------------------------------
u32 player_title(const Value& data) {
    const Value* player = data.find("Player");
    const Value* title = player ? player->find("title") : nullptr;
    return title ? (u32)title->u : 0;
}

NATIVE_TEST("player/titles") {
    bool ran = ext::with_scratch_server(t.rand_u64(), [&](ext::Ctx& ctx) {
        ctx.st.exec("begin");
        Request login_req;
        login_req.method = "Login";
        Value data = Value::object();
        data["Player"] = Value::object();
        ext::player_load(ctx, login_req, data);
        const Value* list = data.find("TitleList");
        int64_t defaults = ctx.m.one("select count(*) from master_title where is_default = 1", {});
        if (!list || list->type != Value::Arr) {
            t.fail("no TitleList in the player load");
            return;
        }
        t.expect_eq((int64_t)list->arr.size(), defaults, "the default titles are owned");
        u32 first = (u32)ctx.m.one("select id from master_title where is_default = 1 order by order_id, id limit 1", {});
        t.expect_eq(player_title(data), first, "a new selection wears the first default title");

        // An achievement title: not owned -> SetTitle refused; granted through the present box.
        u32 ach_title = (u32)ctx.m.one("select content_id from master_achievement where content_type = 13 order by id limit 1", {});
        const ext::Handler* handler = ext::find("SetTitle");
        if (!handler || !ach_title) {
            t.fail("no SetTitle handler or no title achievement");
            return;
        }
        Request set_req;
        set_req.method = "SetTitle";
        set_req.ints = {ach_title};
        (*handler)(ctx, set_req);
        t.expect_eq((u32)ctx.st.one("select value from meta where key = 'title'", {}), first, "unowned title refused");
        const ext::GrantFn* grant = ext::find_grant(kContentTypeTitle);
        if (!grant) {
            t.fail("content type 13 has no grant");
            return;
        }
        Value items = Value::array(), stocks = Value::array(), chars = Value::array();
        (*grant)(ctx, ach_title, 1, items, stocks, chars);
        (*grant)(ctx, ach_title, 1, items, stocks, chars);  // twice: owned once
        t.expect_eq(ctx.st.one("select count(*) from titles where id = ?", {ach_title}), (int64_t)1, "title owned");
        Request present_req;
        present_req.method = "GetPresent";
        Value present_data = Value::object();
        present_data["PresentGetResult"] = Value::object();
        ext::on_response(ctx, present_req, present_data);
        const Value* added = present_data.find("AddTitleList");
        t.expect_eq(added && added->type == Value::Arr ? added->arr.size() : (size_t)0, (size_t)1, "AddTitleList once");
        const Value* result = present_data.find("PresentGetResult")->find("result");
        const Value* result_titles = result ? result->find("Title") : nullptr;
        t.expect_eq(result_titles && result_titles->arr.size() == 1 ? (u32)result_titles->arr[0].get_u("master_title_id") : 0u, ach_title,
                    "result.Title");
        present_data = Value::object();
        ext::on_response(ctx, present_req, present_data);
        t.expect_eq(present_data.find("AddTitleList") != nullptr, false, "no AddTitleList without a grant");

        (*handler)(ctx, set_req);
        t.expect_eq((u32)ctx.st.one("select value from meta where key = 'title'", {}), ach_title, "owned title set");
        data = Value::object();
        data["Player"] = Value::object();
        ext::player_load(ctx, login_req, data);
        t.expect_eq(player_title(data), ach_title, "the load reports the set title");
        set_req.ints = {0};
        (*handler)(ctx, set_req);
        t.expect_eq((u32)ctx.st.one("select value from meta where key = 'title'", {}), 0u, "SetTitle(0) takes it off");
        ctx.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master (data/basmaster-3.7.0.sqlite3) and the seed save (data/saves/seed/Game.xml)");
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_title() {
    ext::add_grant(kContentTypeTitle, grant_title);
    ext::add_player_load(load_titles);
    ext::add_api({"SetTitle"}, set_title);
    ext::add_response_hook(report_added_titles);
}

}  // namespace soa::server
