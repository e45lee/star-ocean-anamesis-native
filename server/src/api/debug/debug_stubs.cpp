// The debug APIs (docs/unimplemented-apis.md 2.4): stubs. Port code, not guest behaviour; every rule
// carries its source label, (a) master data, (b) client-side evidence, (c) outside knowledge, (d)
// assumption.
//
// The 3.7.0 client's API table has none of them (they were the developers' tools); only a test or a
// modified client can send one, over the wire.
#include "core/modules.h"
#include "soaserver/ext.h"

namespace soa::server {

// The module's registrations (src/core/modules.cpp calls this; server/ARCHITECTURE.md "The module
// registry and its order").
void register_debug_stubs() {
    // Debug*(...): stubs (ext::add_stub), 27 methods
    // API: docs/api.md (the Debug* sections)
    // Rules: docs/server-rules.md#social-stubs
    //
    // The user's decision (2026-10-04, docs/unimplemented-apis.md "Decisions": stub).
    //   (d) Answered success with {Time} only and nothing changed, even by the ones whose names
    //       promise items or currency (DebugGetCoin, DebugGetItem): a local game has the save
    //       editor for that, and a stub that grants nothing can't corrupt a state.
    // Answers: {Time}; each call logs "stub: <Method> ...".
    ext::add_stub({"DebugBarneyChance",
                   "DebugCharacterBoost",
                   "DebugCreatePlayer",
                   "DebugDeepBonus",
                   "DebugDeepBonusRareMission",
                   "DebugDeepMissionDrop",
                   "DebugDeletePlayer",
                   "DebugFavorLoginBonus",
                   "DebugGacha",
                   "DebugGachaMutation",
                   "DebugGear",
                   "DebugGearDrop",
                   "DebugGetCharacter",
                   "DebugGetCoin",
                   "DebugGetFol",
                   "DebugGetItem",
                   "DebugGradeUpCharacter",
                   "DebugItemBoost",
                   "DebugLotDeity",
                   "DebugMissionDrop",
                   "DebugOpenMission",
                   "DebugSphere211LotAsset",
                   "DebugSphere211LotEnemyLevel",
                   "DebugSphere211LotFloorNum",
                   "DebugSphere211LotMission",
                   "DebugSphere211TreasureBox",
                   "DebugTowerMax"});
}

}  // namespace soa::server
