// game_layout.h's vtable slots, against the guest's own vtables (VIRTUALS.md 1.5).
#include "native/common/test.h"
#include "native/game/game_layout.h"

using namespace soa;
using namespace soa::native::game;

NATIVE_TEST("game/phase-slots") {
    auto* vt = (const u64*)(t.sym("_ZTV11CPhase_Home") + 0x10);
    t.expect_eq(vt[CBase::kSlotToRelease], t.sym("_ZN6CPhase5CBase9ToReleaseEv"), "slot 4: ToRelease");
    t.expect_eq(vt[CBase::kSlotProgress], t.sym("_ZN11CPhase_Home8ProgressEv"), "slot 5: Progress");
    t.expect_eq(vt[CBase::kSlotIsEnableRelease], t.sym("_ZN11CPhase_Home15IsEnableReleaseEv"), "slot 6: IsEnableRelease");
    t.expect_eq(vt[CBase::kSlotToClose], t.sym("_ZN11CPhase_Home7ToCloseEv"), "slot 7: ToClose");
}
