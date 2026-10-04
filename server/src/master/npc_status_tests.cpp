// Mission NPC status from the master data (soaserver/npc_status.h): the
// tutorial battle's three NPCs against the values the client's NPC model gives
// (MasterMissionNpcModel::CalculateParameter; docs/notes.md "Tutorial battle damage"). The port's
// server/npc-status-master compares every master_mission_npc row with the live client model.
#include "soaserver/ext.h"
#include "soaserver/msgpack.h"
#include "soaserver/native_test.h"
#include "soaserver/npc_status.h"

#include <sqlite3.h>

namespace soa::server {
namespace {
using namespace ext;

NATIVE_TEST("server/npc-status-tutorial") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        struct Want {
            const char* npc;
            double hp, attack, intelligence, defence, hit, guard;
            const char* item;
        };
        // (b) the client model's numbers (port: client NPC status of master_mission_npc ...)
        const Want want[] = {
            {"ms00_001_npc01", 7781, 1281, 755, 960, 551, 397, "item_W01Sw_21"},
            {"ms00_001_npc02", 6859, 1208, 898, 832, 616, 451, "item_W03Gu_11"},
            {"ms00_001_npc03", 5989, 749, 2045, 653, 516, 407, "item_W02Ro_19"},
        };
        for (const Want& w : want) {
            u32 id = (u32)c.m.one("select id from master_mission_npc where id_label = ?", {w.npc});
            if (!id) return t.fail("no master_mission_npc %s", w.npc);
            Value e = Value::object();
            if (!rules::npc_status(c.m.h, id, e)) return t.fail("npc_status(%s) failed", w.npc);
            const char* keys[6] = {"hp", "attack", "intelligence", "defence", "hit", "guard"};
            const double v[6] = {w.hp, w.attack, w.intelligence, w.defence, w.hit, w.guard};
            for (int k = 0; k < 6; k++)
                if (e[keys[k]].f != v[k]) t.fail("%s %s: %g, want %g", w.npc, keys[k], e[keys[k]].f, v[k]);
            u32 item = (u32)c.m.one("select id from master_item where id_label = ?", {w.item});
            t.expect_eq((u32)e["weapon_master_item_id"].u, item, "weapon item");
            t.expect_eq((u32)e["weapon_id"].u, (u32)c.m.one("select master_weapon_id from master_item where id = ?", {item}), "weapon id");
            for (const char* k : {"skill1_level", "skill2_level", "skill3_level"}) t.expect_eq((u32)e[k].u, 1u, k);
        }
        Value e = Value::object();
        e["attack"] = 1.0;
        t.expect_eq(rules::npc_status(c.m.h, 1, e), false, "no such row");
        t.expect_eq(e["attack"].f, 1.0, "unchanged");
    });
    if (!ran) return;
}

// The tutorial battle's MissionStart (ms00_001): BattleParameter.PlayerCharacter carries the NPC
// model's status (the 3.7.0 client battles with what the server sends; emulator_session.sh
// --new-player checks the same numbers in its MissionEnd battle log).
NATIVE_TEST("server/npc-status-tutorial-missionstart") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.q("update player set stamina = 999", {});
        Request s;
        s.method = "MissionStart";
        s.ints = {0, 3645708271u, 1, 0, 0, 0, 0};
        Value d = c.core_mission(s, nullptr);
        const Value* bp = d.type == Value::Map ? d.find("BattleParameter") : nullptr;
        const Value* pc = bp ? bp->find("PlayerCharacter") : nullptr;
        if (!pc || pc->arr.size() != 3) return t.fail("no 3-NPC party");
        const double want[3][6] = {{7781, 1281, 755, 960, 551, 397}, {6859, 1208, 898, 832, 616, 451}, {5989, 749, 2045, 653, 516, 407}};
        const char* keys[6] = {"hp", "attack", "intelligence", "defence", "hit", "guard"};
        for (int i = 0; i < 3; i++)
            for (int k = 0; k < 6; k++) {
                const Value* v = pc->arr[i].find(keys[k]);
                if (!v || v->f != want[i][k]) t.fail("member %d %s: %g, want %g", i, keys[k], v ? v->f : -1.0, want[i][k]);
            }
    });
    if (!ran) return;
}

// master_mission_npc 409829631 (me99_1028_npc02, kimono_npc_role0002: role_cp0306_b04a_5131 at
// level 37, an NPC helper of the event mission me99_1028). The port's old client-model comparison
// (server/npc-status-master, removed with the StatusProvider) reported HP 5158 (server) vs 4728
// (client) here. Not a formula difference but a data one: that selftest's client read the 3.7.0
// APK's built-in master, where the role's talents are factor_oni_101/103/105/107 (passive
// factor_oni_107: attack +10 %, HP +10 %); the downloaded 3.7.0 master, the one the server uses and
// its CDN serves to the client, has factor_wadoramu10_501/oni_103/wadoramu10_505/503 (passive
// wadoramu10_505: attack +15 %, HP +20 %, AP +30). base HP = rnd(3256 x 1.32) = 4298: x 1.2 = 5158,
// x 1.1 = 4728. The test checks both: the served master's numbers, and the APK master's (the
// role's talents swapped back on a copy) equal to the client model's 4728.
NATIVE_TEST("server/npc-status-409829631") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        const u32 id = 409829631;
        Value e = Value::object();
        if (!rules::npc_status(c.m.h, id, e)) return t.fail("npc_status(%u) failed", id);
        t.expect_eq(e["hp"].f, 5158.0, "hp (downloaded master)");
        t.expect_eq(e["attack"].f, 1425.0, "attack (downloaded master): rnd((767 + 453 + 19) x 1.15)");
        t.expect_eq(e["ap"].f, 100.0, "ap");
        // the APK built-in master's talents on a copy of the master
        sqlite3* copy = nullptr;
        if (sqlite3_open(":memory:", &copy) != SQLITE_OK) return t.fail("open :memory:");
        sqlite3_backup* b = sqlite3_backup_init(copy, "main", c.m.h, "main");
        if (b) sqlite3_backup_step(b, -1), sqlite3_backup_finish(b);
        Sql m2{copy};
        m2.q(
            "update master_role set master_talent1_id = 3116377880, master_talent2_id = 1473136180, master_talent3_id = 3199066881, "
            "master_talent4_id = 1352892973 where id = 1402721066",
            {});
        Value a = Value::object();
        bool ok = rules::npc_status(copy, id, a);
        sqlite3_close(copy);
        if (!ok) return t.fail("npc_status(%u) on the copy failed", id);
        t.expect_eq(a["hp"].f, 4728.0, "hp (the APK master's talents) = the old client-model number");
        t.expect_eq(a["attack"].f, 1363.0, "attack (the APK master's talents): rnd(1239 x 1.10)");
    });
    if (!ran) return;
}

}  // namespace
}  // namespace soa::server
