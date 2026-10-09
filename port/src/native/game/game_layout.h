// game_layout.h: the guest data layouts of the `game` subsystem (the game's phases (CPhase and its phase classes)).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/game/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types game` turns the structs into port/decomp/game/types.json for Ghidra.
#ifndef SOA_NATIVE_GAME_LAYOUT_H
#define SOA_NATIVE_GAME_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../kernel/kernel_layout.h"

namespace soa::native::game {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// ---- the phases: CPhase runs one CPhase::CBase at a time ---------------------------------------------

// CPhase::CBase: one phase of the game (title, home, shop, battle, ...; CPhase_* derive from it through
// CPhase_Base). The vtable slots (_ZTVN6CPhase5CBaseE; port/decomp/game/phase.c): 0 / 1 destructors,
// 2 Initialize(), 3 Release(), 4 ToRelease() (the request to leave: CPhase::RequestSwitch calls it),
// 5 Progress() (pure: the frame's step; returns the next phase id, or -1 to stay), 6 IsEnableRelease()
// (CPhase::Progress switches once it is true), 7 ToClose() (CPhase_Base's, pure).
class CBase {
public:
    static constexpr int kSlotInitialize = 2, kSlotRelease = 3, kSlotToRelease = 4, kSlotProgress = 5,
                         kSlotIsEnableRelease = 6, kSlotToClose = 7;
    const void* vtable;  // 0x00: _ZTVN6CPhase5CBaseE + 0x10 (the derived class's)
};
static_assert(sizeof(CBase) == 0x08);

// CPhase_Base: the menu phases' base (CPhase_Home, CPhase_Shop, CPhase_Gacha, ...). Layout from its
// constructor (+0x08 / +0x10 / +0x18 cleared, +0x20 = -1) and CPhase_Home's Progress (the step at +0x08
// advanced, +0x0c its wait cleared, +0x20 returned once the screen closes; +0x14 the common UI's id) and
// constructor (+0x24, its own first field, = 0; Progress stores its screen's UI id there).
class CPhase_Base {
public:
    CBase base;                // 0x00
    u32 m_step;                // 0x08: the phase's own state machine (CPhase_Home: done after 3)
    u32 m_wait;                // 0x0c: cleared at each step
    u8 unk_10[4];              // 0x10
    u32 m_commonUiId;          // 0x14: CPhase_Home: the CCommon screen's UI id
    u8 unk_18[8];              // 0x18
    u32 m_nextPhase;           // 0x20: what Progress returns once the screen has closed (-1: none yet)
    u32 m_screenUiId;          // 0x24: the derived menu phase's first field: its screen's UI id
                               //       (CPhase_Home: CHome's, from the screen's +0xb8)
};
static_assert(offsetof(CPhase_Base, m_step) == 0x08);
static_assert(offsetof(CPhase_Base, m_commonUiId) == 0x14);
static_assert(offsetof(CPhase_Base, m_nextPhase) == 0x20);
static_assert(offsetof(CPhase_Base, m_screenUiId) == 0x24);

// CPhase (TSingleton): the phase manager, a CFiberUnit (priority 0x600). Layout from the constructor (the
// phase ids, the request -1, the substance null), Switch (the present / previous ids, the substance
// deleted through slots 3 / 1 and the next one made), RequestSwitch and Progress (phase.c).
class CPhase {
public:
    // CPhase::Progress (_ZN6CPhase8ProgressEv; the port wraps it: common/port_debug.cpp).
    kernel::CFiberUnit base;   // 0x00
    u32 m_present;             // 0x38: the present phase's id (Switch)
    u32 m_previous;            // 0x3c
    u32 m_request;             // 0x40: RequestSwitch's id, -1 when none (Progress switches to it)
    u8 unk_44[4];              // 0x44
    CBase* m_pPresentSubstance;  // 0x48: the present phase's object
    // 0x50.. a u32 and a vector<u32> of phases to return to (Switch); not recovered
};
static_assert(offsetof(CPhase, m_present) == 0x38);
static_assert(offsetof(CPhase, m_previous) == 0x3c);
static_assert(offsetof(CPhase, m_request) == 0x40);
static_assert(offsetof(CPhase, m_pPresentSubstance) == 0x48);

}  // namespace soa::native::game

#endif  // SOA_NATIVE_GAME_LAYOUT_H
