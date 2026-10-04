// Unit tests of the player state and the home character (api/player/player_info.h, home.h). Run in --selftest;
// not differential (the server has no guest counterpart). Test names are their seeds (testing.h); they are
// named player/... after their domain.
#include <sqlite3.h>
#include <unistd.h>

#include <set>
#include <string>
#include <vector>

#include "api/player/home.h"
#include "api/player/player_info.h"
#include "soaserver/native_test.h"
#include "testing/scratch.h"

namespace soa::server {
namespace {

using ext::Row;

// Player.home_pc_id is the home character's uid (docs/server-rules.md#home-character): 3.7.0's
// CHome::GetAdjutant finds it among the owned characters by CPersonInfo uid and otherwise shows
// party 1's first member, so a role id would show the party leader after a restart. UpdateHome
// to a character outside party 1 answers it, and the next player load (a restart's Login) too.
NATIVE_TEST("player/home-pc-id") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    RequestContext request = sv.new_request();  // for the handlers called directly
    ext::Ctx ctx = sv.make_ctx(request);
    auto sent = [&](const std::vector<u8>& b) -> u64 {
        if (b.empty()) return 0;
        Value v = mp_decode(b);
        const Value* d = v.find("data");
        const Value* p = d ? d->find("Player") : nullptr;
        const Value* h = p ? p->find("home_pc_id") : nullptr;
        return h ? h->u : 0;
    };
    auto loaded = [&] { return (u64)player_info(ctx).get_u("home_pc_id"); };
    u64 home = (u64)sv.st.one("select home_uid from player", {});
    t.expect_eq(loaded(), home, "seeded: the home character's uid");
    t.expect_eq((u64)sv.st.one("select uid from party_member where party_id = 1 and slot = 0", {}), home, "seeded: party 1's first member");
    t.expect_eq(sv.st.one("select count(*) from roster where uid = ?", {loaded()}), (int64_t)1, "an owned uid, not a role id");
    u64 other = (u64)sv.st.one(
        "select uid from roster where uid not in (select uid from party_member where party_id = 1 and uid is not null) order by uid desc limit 1",
        {});
    if (!other) return t.fail("no character outside party 1");
    t.expect_eq(sent(update_home(ctx, Request{"UpdateHome", 0, {other}, {}, {}})), other, "UpdateHome answers the new uid");
    t.expect_eq(loaded(), other, "the next player load sends it");
    t.expect_eq(update_home(ctx, Request{"UpdateHome", 0, {1}, {}, {}}).empty(), true, "an unowned id: refused");
    t.expect_eq(loaded(), other, "refused: unchanged");
}

// view_status / view_status2 are u64 bit sets (CPlayerInfo) the state keeps as their int64 bits
// (player columns since PLAN-schema S3; section 5's risk: a signed read would send -1). All ones in,
// all ones out: the seeded state's (every UI tutorial seen), and UpdateView's word with the top
// bit set, in its reply (the msgpack uint 64) and in the next player load.
NATIVE_TEST("player/view-status-bits") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    RequestContext request = sv.new_request();
    ext::Ctx ctx = sv.make_ctx(request);
    auto word = [](const Value& player, const char* key) {
        const Value* v = player.find(key);
        return v && v->type == Value::UInt ? v->u : 0;
    };
    t.expect_eq(sv.st.one("select view_status from player", {}), (int64_t)-1, "seeded: stored as the int64 bits");
    t.expect_eq(word(player_info(ctx), "view_status"), ~0ull, "seeded: view_status all ones");
    t.expect_eq(word(player_info(ctx), "view_status2"), ~0ull, "seeded: view_status2 all ones");
    const ext::Handler* update_view = ext::find("UpdateView");
    if (!update_view) return t.fail("no UpdateView handler");
    const u64 top_bit = 0x8000000000000005ull;
    Value reply = mp_decode((*update_view)(ctx, Request{"UpdateView", 0, {0, top_bit}, {}, {}}));
    const Value* data = reply.find("data");
    const Value* player = data ? data->find("Player") : nullptr;
    t.expect_eq(player ? word(*player, "view_status") : 0, top_bit, "UpdateView(0): the reply's word, unsigned");
    t.expect_eq(word(player_info(ctx), "view_status"), top_bit, "the next load");
    (*update_view)(ctx, Request{"UpdateView", 0, {1, 0}, {}, {}});
    t.expect_eq(word(player_info(ctx), "view_status2"), 0ull, "UpdateView(1): view_status2");
    t.expect_eq(word(player_info(ctx), "view_status"), top_bit, "view_status unchanged");
}

}  // namespace
// --home3d-all (docs/home3d.md): the client's master copy loses every home3d_disable flag; the
// other master_person columns and rows stay as they were.
NATIVE_TEST("player/home3d-all") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    RequestContext request = S.sv.new_request();
    ext::Ctx ctx = S.sv.make_ctx(request);
    sqlite3* db = nullptr;
    sqlite3_open(":memory:", &db);
    ext::Sql cm{db};
    cm.exec("attach '" + std::string(sqlite3_db_filename(ctx.m.h, "main")) + "' as src");
    cm.exec("create table master_person as select * from src.master_person");
    cm.exec("detach src");
    int64_t rows = cm.one("select count(*) from master_person", {});
    int64_t off = cm.one("select count(*) from master_person where coalesce(home3d_disable, 0) != 0", {});
    int64_t file_sum = cm.one("select count(*) from master_person where home3d_file is not null and home3d_file != ''", {});
    t.expect_eq(off > 0, true, "3.7.0 has 2D-only persons (2B, 9S, A2, ...)");
    t.expect_eq((int64_t)enable_home3d(cm), off, "the changed persons counted");
    t.expect_eq(cm.one("select count(*) from master_person where coalesce(home3d_disable, 0) != 0", {}), (int64_t)0, "none left");
    t.expect_eq(cm.one("select count(*) from master_person", {}), rows, "no row added or removed");
    t.expect_eq(cm.one("select count(*) from master_person where home3d_file is not null and home3d_file != ''", {}), file_sum,
                "home3d_file untouched");
    sqlite3_close(db);
}

// Home3DAnd2DSwitching (docs/server-rules.md#home-2d-3d): a new player's home is 3D; the
// request stores the mode sent (0: 2D, any non-zero: 3D) and answers it as Player.is_3d_home, as
// every later player load does.
NATIVE_TEST("player/home3d-switching") {
    ScratchServer S(t.rand_u64());
    if (!S.ok) return;
    Server& sv = S.sv;
    RequestContext request = sv.new_request();
    ext::Ctx ctx = sv.make_ctx(request);
    auto sent = [&](const std::vector<u8>& b) -> int {
        if (b.empty()) return -1;
        Value v = mp_decode(b);
        const Value* d = v.find("data");
        const Value* p = d ? d->find("Player") : nullptr;
        const Value* h = p ? p->find("is_3d_home") : nullptr;
        return h ? (h->type == Value::Bool ? (int)h->b : (int)h->u) : -1;
    };
    auto loaded = [&] {
        const Value* h = player_info(ctx).find("is_3d_home");
        return h ? (h->type == Value::Bool ? (int)h->b : (int)h->u) : -1;
    };
    t.expect_eq(loaded(), 1, "a new player: 3D");
    Request r;
    r.method = "Home3DAnd2DSwitching";
    r.ints = {0};
    t.expect_eq(sent(home3d_and_2d_switching(ctx, r)), 0, "switched to 2D: answered");
    t.expect_eq(loaded(), 0, "2D on the next load");
    t.expect_eq(sv.st.one("select is_3d_home from player", {}), (int64_t)0, "stored");
    r.ints = {5};
    t.expect_eq(sent(home3d_and_2d_switching(ctx, r)), 1, "any non-zero: 3D");
    t.expect_eq(loaded(), 1, "3D on the next load");
}

}  // namespace soa::server
