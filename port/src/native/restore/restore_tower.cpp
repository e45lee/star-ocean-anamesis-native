// --restore-tower (opt-in): the tower (試練の遺跡) opened. 3.7.0 had it closed:
// CParameterUtility::IsOpenTowerMission returns 0; with the opt-in the hook below returns 1.
// docs/client-changes.md "Tower", docs/notes.md "Tower layout".
//
// The tower menu (CTowerMissionMenu) draws on three scenes it shares with the event menu:
// mission_menu_common, eventmission_top (the floor list) and mission_list2 (a floor's missions).
// The only copies left, the 3.7.0 download's, were re-authored after the tower closed, and two
// things the tower code expects are gone. No other copy exists (every .csf of the download and
// both APKs was searched; the manifests list no other version). Two client changes make the menu
// work; both are port-specific stand-ins, as the layout is client data (no server route):
//
// 1. The challenge-count plates. CTowerMissionMenu::Setup looks up "play_plate/0".."play_plate/3"
//    in mission_list2 (one visible per remaining try: StaminaUtility::NowStamina(1) == n, the 4th
//    for 3 or more) and writes their visible flag unchecked; mission_list2 has no play_plate (only
//    the event menu's vanish_plate), so the guest dereferences null. While Setup runs, a search
//    for exactly those four names that finds nothing returns a detached, empty CCocosNode (one per
//    name, never shown): CCocosNode::SearchByName / SearchByTreeName are wrapped (with the opt-in
//    only) and run the guest search first. Every other missing name keeps the guest's null: its callers check it
//    (btn_restart_old), or probe with it until it's missing (the
//    "Button_mission_%d/new/icon_vanish_1" loop in SetupEventMissionSelect would never end).
//    The remaining tries still show on the extra-dungeon menu's tower banner ("3/3").
// 2. The mission buttons. The list items are cloned from the common-resource scene's
//    "Button_mission" (CUIUtility::SetupCommonResource_ButtonMission, which the tower's item
//    callback calls), but CTowerMissionMenu::Initialize never adds that scene; the event menu's
//    Initialize calls CUIObject::AddCommonResourceScene() after its three scenes. Without it the
//    list shows empty plates (mission_list2's own ListView_1 child) that ignore taps. After the
//    guest's Initialize, the wrapper calls AddCommonResourceScene() on the menu, as the event
//    menu does.
#include <cstring>
#include <map>
#include <string>

#include "core/cpu.h"
#include "core/log.h"
#include "core/options.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"

namespace soa::native::restore_tower {
namespace {

bool on() { return options().server.enabled && options().server.restore_tower; }

int g_depth = 0;  // inside CTowerMissionMenu::Setup (game thread only)

bool standin_name(std::string_view name) {
    return name.size() == 12 && name.substr(0, 11) == "play_plate/" && name[11] >= '0' && name[11] <= '3';
}
u64 stand_in(u64 /*node*/, std::string_view name) {
    if (g_depth <= 0 || !standin_name(name)) return 0;
    static std::map<std::string, u64> made;
    std::string key(name);
    auto it = made.find(key);
    if (it != made.end()) return it->second;
    static const u64 ctor = guest::sym("_ZN9Framework5Cocos10CCocosNodeC1Ev");
    u64 n = (u64)guest::new_array_nothrow(0x400);
    memset((void*)n, 0, 0x400);
    guest_call(ctor, {n});
    made[key] = n;
    LOGI("restore_tower", "tower menu: layout node '%s' missing (3.7.0 mission_list2); a hidden stand-in", key.c_str());
    return n;
}

GuestArgs same_args(Cpu& c) {
    GuestArgs a;
    for (int k = 0; k < 8; k++) a.i(c.x(k));
    a.f(c.s(0));
    a.x8 = c.x(8);
    return a;
}

// CCocosNode::SearchByName / SearchByTreeName(const std::string&): x0 this, x1 the name. The
// guest search first; a miss inside Setup may get a stand-in.
#define COCOS_STR "ERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE"
u64 g_orig_search_name = 0, g_orig_search_tree = 0;
template <u64* Orig>
void h_search(Cpu& c) {
    u64 node = c.x(0), name = c.x(1);
    u64 r = guest_call(*Orig, {node, name});
    if (!r && g_depth > 0) r = stand_in(node, ((const guest::String*)name)->view());
    c.set_x(0, r);
}
NATIVE_FUNCTION_ORIG_IF("_ZN9Framework5Cocos10CCocosNode12SearchByName" COCOS_STR, h_search<&g_orig_search_name>,
                        "restore: tower menu, stand-ins for the lost play_plate nodes (--restore-tower)", on, &g_orig_search_name);
NATIVE_FUNCTION_ORIG_IF("_ZN9Framework5Cocos10CCocosNode16SearchByTreeName" COCOS_STR, h_search<&g_orig_search_tree>,
                        "restore: tower menu, stand-ins for the lost play_plate nodes (--restore-tower)", on, &g_orig_search_tree);

u64 g_orig_setup = 0;
void h_setup(Cpu& c) {
    g_depth++;
    u64 r = guest_call(g_orig_setup, same_args(c)).x0;
    g_depth--;
    c.set_x(0, r);
}
NATIVE_FUNCTION_ORIG_IF("_ZN17CTowerMissionMenu5SetupEv", h_setup,
                        "restore: tower menu, stand-ins for the lost play_plate nodes (--restore-tower)", on, &g_orig_setup);

// bool CParameterUtility::IsOpenTowerMission(): 0 in 3.7.0 (the tower was closed); 1 with the
// opt-in. Client change (docs/client-changes.md "Tower").
void h_is_open_tower(Cpu& c) { c.set_x(0, 1); }
NATIVE_FUNCTION_IF("_ZN17CParameterUtility18IsOpenTowerMissionEv", h_is_open_tower, "restore: the tower is open (--restore-tower)", on);

// CTowerMissionMenu::Initialize(float, const std::function<void(int)>&): x0 this, s0, x1.
u64 g_orig_init = 0;
void h_init(Cpu& c) {
    u64 self = c.x(0);
    u64 r = guest_call(g_orig_init, same_args(c)).x0;
    static const u64 add = guest::sym("_ZN9CUIObject22AddCommonResourceSceneEv");
    guest_call(add, {self});
    c.set_x(0, r);
}
NATIVE_FUNCTION_ORIG_IF("_ZN17CTowerMissionMenu10InitializeEfRKNSt6__ndk18functionIFviEEE", h_init,
                        "restore: tower menu adds the common-resource scene, as the event menu does (--restore-tower)", on,
                        &g_orig_init);

}  // namespace
}  // namespace soa::native::restore_tower
