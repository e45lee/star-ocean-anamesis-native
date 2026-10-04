// Layout tests for input_layout.h (port/PLAN.md task 6, types first): the recovered classes read
// against real guest objects. Each test either builds a private object with the guest's own
// constructor and methods and compares the fields read through the layout classes with the guest's
// accessors (and with what the test did), or walks the running game's input objects read-only.
// No natives here: in --selftest every t.call reaches the guest code.
#include <cstring>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/test.h"
#include "native/input/input_layout.h"

using namespace soa;
using namespace soa::native::input;

namespace {

template <typename T>
T* at_vaddr(u64 vaddr) {
    return reinterpret_cast<T*>(main_lib()->base + vaddr);
}
template <typename T>
T* instance(u64 vaddr) {
    return *at_vaddr<T*>(vaddr);
}

u64 vtable_of(TestContext& t, const char* ztv) { return t.sym(ztv) + 0x10; }
u64 call0(TestContext& t, const char* name) { return guest_call(t.sym(name), std::initializer_list<u64>{}); }
float callf(TestContext& t, const char* name, const void* self) {
    GuestArgs a;
    a.p(self);
    GuestResult r = t.call(name, a);
    float f;
    std::memcpy(&f, &r.v0, 4);
    return f;
}
// Pad::Get(id, out) / BasePeripheral::Get through the guest; returns the byte (or u16) read.
u64 pad_get(TestContext& t, const void* pad, u64 id, bool* ok) {
    u64 out = 0;
    *ok = (t.call("_ZNK4Aska3Pad3GetEmPv", {(u64)pad, id, (u64)&out}) & 0xff) != 0;
    return out;
}

}  // namespace

// A private Aska::Pad built by the guest's Pad(short) (the abstract base: only non-virtual methods
// and Pad's own vtable slots are used), driven through its setters, a synthetic raw input
// (UpdateKeyStatus), Flip and Release; every field read through Pad / PadKeys / PadRepeatEach and
// compared with Pad::Get, the analog getters and the decompile's arithmetic.
NATIVE_TEST("input/layout-pad") {
    alignas(16) static u8 storage[sizeof(PadDroid)];
    std::memset(storage, 0xa5, sizeof storage);
    auto* pad = reinterpret_cast<Pad*>(storage);
    const s16 kDeadZone = 0x80;
    t.call("_ZN4Aska3PadC2Es", {(u64)pad, (u64)(u16)kDeadZone});
    t.expect_eq((u64)pad->base.vtable, vtable_of(t, "_ZTVN4Aska3PadE"), "vtable");
    t.expect_eq(pad->m_deadZone, kDeadZone, "dead zone");
    t.expect_eq(pad->base.m_port, (s8)-1, "port -1");
    t.expect_eq(pad->base.m_connected, (u8)0, "not connected");
    t.expect_eq(pad->m_attra2, (u8)0xff, "0xa2");
    t.expect_eq(pad->m_rumbleSupported, (u8)0, "rumble unsupported");
    t.expect_eq(pad->m_front, (s32)0, "front 0");
    t.expect_eq(pad->m_repeatThreshold, (u8)0x10, "repeat threshold");
    t.expect_eq(pad->m_repeatInterval, (u8)0x08, "repeat interval");
    for (int i = 0; i < 16; i++) {
        t.expect_eq(pad->m_repeatEach[i].m_counter, (s16)0, "each counter");
        t.expect_eq(pad->m_repeatEach[i].m_threshold, (u8)0x10, "each threshold");
        t.expect_eq(pad->m_repeatEach[i].m_interval, (u8)0x08, "each interval");
    }
    for (int i = 0; i < 4; i++) {
        t.expect_eq(pad->m_analogMax[i], (s16)0x7fff, "analog max");
        t.expect_eq(pad->m_calibration[i], (u16)0, "calibration");
        t.expect_eq(pad->m_analogScale[i], (s16)(0x7fff - kDeadZone), "analog scale");
    }
    t.expect_eq(pad->m_analogAsDigital, (u8)0, "analog as digital");
    bool ok = false;
    // BasePeripheral::Get ids 0..4 (Pad::Get falls through to it)
    t.expect_eq((u8)pad_get(t, pad, 0, &ok), pad->base.m_attr98, "Get(0)");
    t.expect_eq((u8)pad_get(t, pad, 1, &ok), (u8)pad->base.m_port, "Get(1) port");
    t.expect_eq((u8)pad_get(t, pad, 2, &ok), pad->base.m_connected, "Get(2) connected");
    t.expect_eq((u8)pad_get(t, pad, 3, &ok), pad->base.m_attr9c, "Get(3)");
    t.expect_eq((u8)pad_get(t, pad, 4, &ok), pad->base.m_attr9d, "Get(4)");

    // The locked setters and the repeat tables.
    t.call("_ZN4Aska3Pad18SetRepeatThresholdEh", {(u64)pad, 5});
    t.call("_ZN4Aska3Pad17SetRepeatIntervalEh", {(u64)pad, 3});
    t.call("_ZN4Aska3Pad18SetAnalogAsDigitalEb", {(u64)pad, 1});
    t.call("_ZN4Aska3Pad22SetRepeatEachThresholdEth", {(u64)pad, 0x8005, 7});
    t.call("_ZN4Aska3Pad21SetRepeatEachIntervalEth", {(u64)pad, 0x0102, 2});
    t.expect_eq(pad->m_repeatThreshold, (u8)5, "SetRepeatThreshold");
    t.expect_eq(pad->m_repeatInterval, (u8)3, "SetRepeatInterval");
    t.expect_eq(pad->m_analogAsDigital, (u8)1, "SetAnalogAsDigital");
    t.expect_eq(t.call("_ZNK4Aska3Pad17IsAnalogAsDigitalEv", {(u64)pad}) & 0xff, (u64)1, "IsAnalogAsDigital");
    t.expect_eq(pad_get(t, pad, 0x10, &ok) & 0xff, (u64)pad->m_repeatThreshold, "Get(0x10)");
    t.expect_eq(pad_get(t, pad, 0x11, &ok) & 0xff, (u64)pad->m_repeatInterval, "Get(0x11)");
    for (int i = 0; i < 16; i++) {
        u8 thr = (0x8005 >> i) & 1 ? 7 : 0x10;
        u8 itv = (0x0102 >> i) & 1 ? 2 : 0x08;
        t.expect_eq(pad->m_repeatEach[i].m_threshold, thr, "SetRepeatEachThreshold");
        t.expect_eq(pad->m_repeatEach[i].m_interval, itv, "SetRepeatEachInterval");
        t.expect_eq(pad_get(t, pad, 0x12 + i, &ok) & 0xff, (u64)thr, "Get(0x12 + i)");
        t.expect_eq(pad_get(t, pad, 0x22 + i, &ok) & 0xff, (u64)itv, "Get(0x22 + i)");
    }
    // Rumble: needs m_rumbleSupported (set by the derived class; here by the test).
    pad->m_rumbleSupported = 1;
    t.call("_ZN4Aska3Pad12EnableRumbleEb", {(u64)pad, 1});
    t.call("_ZN4Aska3Pad9SetRumbleEtt", {(u64)pad, 0x1234, 0x5678});
    t.expect_eq(pad->m_rumbleEnabled, (u8)1, "EnableRumble");
    t.expect_eq(pad_get(t, pad, 5, &ok) & 0xff, (u64)1, "Get(5)");
    t.expect_eq(pad_get(t, pad, 6, &ok) & 0xff, (u64)1, "Get(6)");
    t.expect_eq(pad->m_rumble[0], (u16)0x1234, "rumble L");
    t.expect_eq(pad_get(t, pad, 7, &ok) & 0xffff, (u64)0x1234, "Get(7)");
    t.expect_eq(pad_get(t, pad, 8, &ok) & 0xffff, (u64)0x5678, "Get(8)");

    // Calibration and the analog limits.
    t.call("_ZN4Aska3Pad14SetCalibrationEsssss", {(u64)pad, 100, 200, 300, 400, (u64)(u16)kDeadZone});
    t.call("_ZN4Aska3Pad12SetAnalogMaxEssss", {(u64)pad, 0x4000, 0x4000, 0x7000, 0x7fff});
    t.expect_eq(pad->m_calibration[1], (u16)200, "SetCalibration");
    t.expect_eq(pad->m_analogMax[2], (s16)0x7000, "SetAnalogMax");
    t.expect_eq(pad->m_analogScale[2], (s16)0x7000, "analog scale = max (under 0x7fff - dead zone)");
    t.expect_eq(pad->m_analogScale[0], (s16)0x4000, "analog scale = max");
    t.expect_eq(pad->m_analogScale[3], (s16)(0x7fff - kDeadZone), "analog scale = 0x7fff - dead zone");

    // A raw input -> UpdateKeyStatus writes m_keys[m_front ^ 1].
    pad->m_rawButtons = 0x0030;
    pad->m_rawTrigger[0] = 7;
    pad->m_rawTrigger[1] = 9;
    pad->m_rawAnalog[0] = 100 + 0x3000;  // lx: +0x3000 - dead zone
    pad->m_rawAnalog[1] = 200 - 0x1000;  // ly: -0x1000 + dead zone
    pad->m_rawAnalog[2] = 300 + 0x40;    // rx: inside the dead zone -> 0
    pad->m_rawAnalog[3] = 400;           // ry: 0
    t.call("_ZN4Aska3Pad15UpdateKeyStatusEv", {(u64)pad});
    t.expect_eq(pad->base.m_updated, (u8)1, "UpdateKeyStatus sets m_updated");
    const PadKeys& k = pad->m_keys[1];
    t.expect_eq(k.m_lx, (s16)(0x3000 - kDeadZone), "lx");
    t.expect_eq(k.m_ly, (s16)(-0x1000 + kDeadZone), "ly");
    t.expect_eq(k.m_rx, (s16)0, "rx (dead zone)");
    t.expect_eq(k.m_ry, (s16)0, "ry");
    t.expect_eq(k.m_lt, (u8)7, "lt");
    t.expect_eq(k.m_rt, (u8)9, "rt");
    t.expect_eq(k.m_lxf, (float)(0x3000 - kDeadZone) / (float)0x4000, "lxf");
    // analog as digital: lx above max / 2 sets bit 3
    t.expect_eq(k.m_now, (u16)(0x0030 | 0x8), "now (raw | the analog bit)");
    t.expect_eq(k.m_before, (u16)0, "before");
    t.expect_eq(k.m_stock, k.m_now, "stock");
    t.expect_eq(k.m_single, k.m_now, "single");
    t.expect_eq(k.m_release, (u16)0, "release");
    // Flip: resets the front, swaps, carries m_now over; the getters then read the new front.
    t.call("_ZN4Aska3Pad4FlipEv", {(u64)pad});
    t.expect_eq(pad->m_front, (s32)1, "Flip swaps the front");
    t.expect_eq(pad->m_keys[0].m_now, k.m_now, "Flip carries m_now");
    t.expect_eq(pad->m_keys[0].m_stock, (u16)0, "Flip reset the old front");
    s16 a[4] = {1, 1, 1, 1};
    t.call("_ZNK4Aska3Pad17GetAnalogPositionEPsS1_S1_S1_", {(u64)pad, (u64)&a[0], (u64)&a[1], (u64)&a[2], (u64)&a[3]});
    t.expect_eq(a[0], k.m_lx, "GetAnalogPosition lx");
    t.expect_eq(a[1], k.m_ly, "GetAnalogPosition ly");
    t.expect_eq(a[2], k.m_rx, "GetAnalogPosition rx");
    float f[4] = {};
    t.call("_ZNK4Aska3Pad17GetAnalogPositionEPfS1_S1_S1_", {(u64)pad, (u64)&f[0], (u64)&f[1], (u64)&f[2], (u64)&f[3]});
    t.expect_eq(f[0], k.m_lxf, "GetAnalogPosition lxf");
    t.expect_eq(f[1], k.m_lyf, "GetAnalogPosition lyf");
    t.expect_eq(f[3], k.m_ryf, "GetAnalogPosition ryf");
    u8 lt = 0, rt = 0;
    t.call("_ZNK4Aska3Pad16GetAnalogTriggerEPhS1_", {(u64)pad, (u64)&lt, (u64)&rt});
    t.expect_eq(lt, (u8)7, "GetAnalogTrigger L");
    t.expect_eq(rt, (u8)9, "GetAnalogTrigger R");
    // ResetStatus clears the front buffer and m_updated.
    t.call("_ZN4Aska3Pad11ResetStatusEv", {(u64)pad});
    t.expect_eq(pad->m_keys[1].m_now, (u16)0, "ResetStatus clears the front");
    t.expect_eq(pad->base.m_updated, (u8)0, "ResetStatus clears m_updated");
    // Release: the keys and the base fields.
    pad->base.m_port = 0;
    pad->base.m_connected = 1;
    t.call("_ZN4Aska3Pad7ReleaseEv", {(u64)pad});
    t.expect_eq(pad->base.m_port, (s8)-1, "Release: port");
    t.expect_eq(pad->base.m_connected, (u8)0, "Release: connected");
    t.expect_eq(pad->base.m_attr9c, (u8)0xff, "Release: 0x9c");
    t.expect_eq(pad->base.m_attra0, (u8)0xff, "Release: 0xa0");
    t.expect_eq(pad->m_keys[0].m_now, (u16)0, "Release clears the keys");
    t.expect_eq(pad->m_repeatEach[0].m_counter, (s16)0, "Release clears the repeat counters");
    // The base destructor (Pad's own D0 is a trap) frees the critical section.
    t.call("_ZN4Aska14BasePeripheralD2Ev", {(u64)pad});
}

// A private Framework::CPad::CUnit: its constructor, then m_keys / the lock bytes written through
// the layout and read back with the guest's virtual getters.
NATIVE_TEST("input/layout-cpad-unit") {
    alignas(16) static u8 storage[sizeof(CUnit)];
    std::memset(storage, 0, sizeof storage);
    auto* u = reinterpret_cast<CUnit*>(storage);
    t.call("_ZN9Framework4CPad5CUnitC2Ev", {(u64)u});
    t.expect_eq((u64)u->vtable, vtable_of(t, "_ZTVN9Framework4CPad5CUnitE"), "vtable");
    t.expect_eq(u->m_port, (s32)-1, "port -1");
    PadKeys& k = u->m_keys;
    k.m_now = 0x1111; k.m_before = 0x2222; k.m_stock = 0x3333; k.m_single = 0x4444;
    k.m_release = 0x5555; k.m_repeat = 0x6666; k.m_repeatEach = 0x7777;
    k.m_lx = -100; k.m_ly = 200; k.m_rx = -300; k.m_ry = 400; k.m_lt = 11; k.m_rt = 22;
    k.m_lxf = 0.25f; k.m_lyf = -0.5f; k.m_rxf = 0.75f; k.m_ryf = -1.0f;
    const u64 p = (u64)u;
    t.expect_eq(t.call("_ZNK9Framework4CPad5CUnit4KeysEv", {p}), (u64)&u->m_keys, "Keys() = &m_keys");
    t.expect_eq((u16)t.call("_ZNK9Framework4CPad5CUnit6GetNowEv", {p}), k.m_now, "GetNow");
    t.expect_eq((u16)t.call("_ZNK9Framework4CPad5CUnit9GetBeforeEv", {p}), k.m_before, "GetBefore");
    t.expect_eq((u16)t.call("_ZNK9Framework4CPad5CUnit8GetStockEv", {p}), k.m_stock, "GetStock");
    t.expect_eq((u16)t.call("_ZNK9Framework4CPad5CUnit9GetSingleEv", {p}), k.m_single, "GetSingle");
    t.expect_eq((u16)t.call("_ZNK9Framework4CPad5CUnit10GetReleaseEv", {p}), k.m_release, "GetRelease");
    t.expect_eq((u16)t.call("_ZNK9Framework4CPad5CUnit9GetRepeatEv", {p}), k.m_repeat, "GetRepeat");
    t.expect_eq((u16)t.call("_ZNK9Framework4CPad5CUnit13GetRepeatEachEv", {p}), k.m_repeatEach, "GetRepeatEach");
    t.expect_eq((s16)t.call("_ZNK9Framework4CPad5CUnit11GetAnalogLXEv", {p}), k.m_lx, "GetAnalogLX");
    t.expect_eq((s16)t.call("_ZNK9Framework4CPad5CUnit11GetAnalogLYEv", {p}), k.m_ly, "GetAnalogLY");
    t.expect_eq((s16)t.call("_ZNK9Framework4CPad5CUnit11GetAnalogRXEv", {p}), k.m_rx, "GetAnalogRX");
    t.expect_eq((s16)t.call("_ZNK9Framework4CPad5CUnit11GetAnalogRYEv", {p}), k.m_ry, "GetAnalogRY");
    t.expect_eq((u8)t.call("_ZNK9Framework4CPad5CUnit11GetAnalogLTEv", {p}), k.m_lt, "GetAnalogLT");
    t.expect_eq((u8)t.call("_ZNK9Framework4CPad5CUnit11GetAnalogRTEv", {p}), k.m_rt, "GetAnalogRT");
    t.expect_eq(callf(t, "_ZNK9Framework4CPad5CUnit12GetAnalogLXFEv", u), k.m_lxf, "GetAnalogLXF");
    t.expect_eq(callf(t, "_ZNK9Framework4CPad5CUnit12GetAnalogLYFEv", u), k.m_lyf, "GetAnalogLYF");
    t.expect_eq(callf(t, "_ZNK9Framework4CPad5CUnit12GetAnalogRXFEv", u), k.m_rxf, "GetAnalogRXF");
    t.expect_eq(callf(t, "_ZNK9Framework4CPad5CUnit12GetAnalogRYFEv", u), k.m_ryf, "GetAnalogRYF");
    // The lock bytes: each silences its getters.
    u->m_lockButtons = 1;
    t.expect_eq((u16)t.call("_ZNK9Framework4CPad5CUnit6GetNowEv", {p}), (u16)0, "m_lockButtons");
    u->m_lockTriggerL = 1;
    t.expect_eq(callf(t, "_ZNK9Framework4CPad5CUnit12GetAnalogLTFEv", u), 0.0f, "m_lockTriggerL");
    t.call("_ZN9Framework4CPad5CUnit9UnlockAllEv", {p});
    t.expect_eq(u->m_lockButtons, (u8)0, "UnlockAll clears 0x5c");
    t.expect_eq(u->m_lockTriggerL, (u8)0, "UnlockAll clears 0x5f");
    t.expect_eq(u->m_lockTriggerR, (u8)0, "UnlockAll clears 0x60");
    // CUnit::Copy is the m_stock -> m_keys copy (CPadReader's side writes m_stock); with port -1 it
    // asserts, so it is not run here; the live test checks m_stock / m_keys on the game's unit.
}

// The running game's input objects, read-only: PeripheralManager and its two peripherals (the PadDroid
// and the TouchPanel), the Framework singletons (CPad + its unit, CTouchPanel, CKeyboard, CMouse) and
// Aska's Mouse / Keyboard statics, compared with the guest's getters and with each other.
NATIVE_TEST("input/layout-live") {
    auto* pm = instance<PeripheralManager>(kVaddrPeripheralManager);
    if (!t.expect_eq(pm != nullptr, true, "Global::m_pPeripheralManager")) return;
    t.expect_eq((u64)pm->vtable, vtable_of(t, "_ZTVN4Aska17PeripheralManagerE"), "PeripheralManager vtable");
    t.expect_eq((u64)*reinterpret_cast<const void* const*>(pm->m_thread), vtable_of(t, "_ZTVN4Aska17PeripheralManagerE") + 0x50,
                "PeripheralManager's Thread vtable (+0x60)");
    t.expect_eq((u64)pm->m_pad, t.call("_ZN4Aska6Global13GetPeripheralEi", {0}), "m_pad = GetPeripheral(0)");
    t.expect_eq((u64)pm->m_pad, call0(t, "_ZN4Aska6Global12GetActivePadEv"), "m_pad = GetActivePad");
    t.expect_eq((u64)pm->m_ex, t.call("_ZN4Aska6Global15GetExPeripheralEi", {0}), "m_ex = GetExPeripheral(0)");
    t.expect_eq(pm->m_quit, (u8)0, "m_quit");
    t.expect_eq(pm->m_started, (u8)1, "m_started (the polling thread runs)");

    // The pad (a PadDroid), its stable fields through Pad::Get.
    auto* pad = reinterpret_cast<Pad*>(pm->m_pad);
    if (t.expect_eq(pad != nullptr, true, "pad")) {
        t.expect_eq((u64)pad->base.vtable, vtable_of(t, "_ZTVN4Aska8PadDroidE"), "pad is a PadDroid");
        // PadDroid::Initialize (slot 7, what RegisterPeripheral calls with 0) is an empty stub: the port stays -1.
        t.expect_eq(pad->base.m_port, (s8)-1, "pad port (PadDroid::Initialize is empty)");
        t.expect_eq(pad->base.m_attr98, (u8)0, "RegisterPeripheral cleared 0x98");
        bool ok = false;
        t.expect_eq((u8)pad_get(t, pad, 1, &ok), (u8)pad->base.m_port, "pad Get(1)");
        t.expect_eq((u8)pad_get(t, pad, 2, &ok), pad->base.m_connected, "pad Get(2)");
        t.expect_eq(pad_get(t, pad, 5, &ok) & 0xff, (u64)pad->m_rumbleSupported, "pad Get(5)");
        t.expect_eq(pad_get(t, pad, 0x10, &ok) & 0xff, (u64)pad->m_repeatThreshold, "pad Get(0x10)");
        t.expect_eq(pad_get(t, pad, 0x11, &ok) & 0xff, (u64)pad->m_repeatInterval, "pad Get(0x11)");
        t.expect_eq(pad_get(t, pad, 0x13, &ok) & 0xff, (u64)pad->m_repeatEach[1].m_threshold, "pad Get(0x13)");
        t.expect_eq(t.call("_ZNK4Aska3Pad17IsAnalogAsDigitalEv", {(u64)pad}) & 0xff, (u64)pad->m_analogAsDigital,
                    "pad IsAnalogAsDigital");
        t.expect_eq(pad->m_front == 0 || pad->m_front == 1, true, "pad m_front 0 / 1");
        t.expect_eq(pad->m_analogScale[0] <= pad->m_analogMax[0], true, "pad analog scale <= max");
    }

    // The touch panel.
    auto* tp = reinterpret_cast<TouchPanel*>(pm->m_ex);
    if (t.expect_eq(tp != nullptr, true, "touch panel")) {
        t.expect_eq((u64)tp->base.vtable, vtable_of(t, "_ZTVN4Aska10TouchPanelE"), "TouchPanel vtable");
        t.expect_eq(tp->base.m_port, (s8)0, "touch port 0");
        t.expect_eq(tp->base.m_connected, (u8)1, "touch connected (Initialize)");
        t.expect_eq(tp->m_enabled, (u8)1, "touch enabled");
        t.expect_eq(tp->m_holdTime, (s32)0xfa, "touch-and-hold time 0xfa");
        t.expect_eq((s32)t.call("_ZN4Aska10TouchPanel17CalcDoublTapRangeEi", {(u64)tp, 0x50}), tp->m_doubleTapRange,
                    "m_doubleTapRange = CalcDoublTapRange(0x50)");
        t.expect_eq(tp->m_numData >= 0 && tp->m_numData <= 64, true, "m_numData in 0..64");
        // The gesture accessors against the fields (idle: no touch; read twice to tolerate a frame).
        TouchDragParam d{};
        bool got = (t.call("_ZN4Aska10TouchPanel7GetDragEPNS0_9DragParamE", {(u64)tp, (u64)&d}) & 0xff) != 0;
        t.expect_eq(got, tp->m_drag[0].m_state != 3, "GetDrag = m_drag[0].m_state != 3");
        if (got) t.expect_eq(d.m_id, tp->m_drag[0].m_id, "GetDrag copies m_drag[0]");
        TouchPinchParam pp{};
        got = (t.call("_ZN4Aska10TouchPanel13GetPinchOutInEPNS0_15PinchOutInParamE", {(u64)tp, (u64)&pp}) & 0xff) != 0;
        t.expect_eq(got, tp->m_pinch.m_state != 3, "GetPinchOutIn = m_pinch.m_state != 3");
        TouchHoldParam hp{};
        got = (t.call("_ZN4Aska10TouchPanel15GetTouchAndHoldEPNS0_17TouchAndHoldParamE", {(u64)tp, (u64)&hp}) & 0xff) != 0;
        t.expect_eq(got, tp->m_numHolds != 0, "GetTouchAndHold = m_numHolds != 0");
        TouchVector2 taps[8];
        s32 n = (s32)t.call("_ZN4Aska10TouchPanel6GetTapEPNS0_7Vector2Ei", {(u64)tp, (u64)taps, 8});
        t.expect_eq(n, tp->m_tapKind == 1 ? (tp->m_tapCount < 8 ? tp->m_tapCount : 8) : 0, "GetTap count");
        for (s32 i = 0; i < n && i < 8; i++) t.expect_eq(taps[i].x, tp->m_taps[i].x, "GetTap x = m_taps[i]");
        for (const TouchDragParam& dp : tp->m_drag)
            t.expect_eq(dp.m_state >= 0 && dp.m_state <= 3, true, "drag state in 0..3");
    }

    // Framework::CTouchPanel.
    auto* ctp = instance<CTouchPanel>(kVaddrCTouchPanelInstance);
    if (t.expect_eq(ctp != nullptr, true, "CTouchPanel")) {
        const u64 p = (u64)ctp;
        t.expect_eq((u64)ctp->vtable, vtable_of(t, "_ZTVN9Framework11CTouchPanelE"), "CTouchPanel vtable");
        t.expect_eq((u64)ctp->m_panel, (u64)pm->m_ex, "CTouchPanel m_panel = the ex peripheral");
        t.expect_eq((u8)t.call("_ZNK9Framework11CTouchPanel11IsConnectedEv", {p}), tp ? tp->m_attached : (u8)0, "IsConnected = m_attached");
        t.expect_eq((s32)t.call("_ZNK9Framework11CTouchPanel12NumTouchDataEv", {p}), ctp->m_numData, "NumTouchData");
        t.expect_eq(t.call("_ZNK9Framework11CTouchPanel16rTouchDataBufferEv", {p}), (u64)ctp->m_data, "rTouchDataBuffer");
        t.expect_eq(t.call("_ZNK9Framework11CTouchPanel14rAnalogVirtualEv", {p}), (u64)ctp->m_analogVirtual, "rAnalogVirtual");
        t.expect_eq(t.call("_ZNK9Framework11CTouchPanel9rTapParamEj", {p, 1}), (u64)&ctp->m_tap[1], "rTapParam(1)");
        t.expect_eq((u8)t.call("_ZNK9Framework11CTouchPanel10IsTapParamEv", {p}), ctp->m_isTap, "IsTapParam");
        t.expect_eq(t.call("_ZNK9Framework11CTouchPanel15rDoubleTapParamEv", {p}), (u64)&ctp->m_doubleTap, "rDoubleTapParam");
        t.expect_eq((u8)t.call("_ZNK9Framework11CTouchPanel16IsDoubleTapParamEv", {p}), ctp->m_isDoubleTap, "IsDoubleTapParam");
        t.expect_eq(t.call("_ZNK9Framework11CTouchPanel10rDragParamEv", {p}), (u64)&ctp->m_drag, "rDragParam");
        t.expect_eq((u8)t.call("_ZNK9Framework11CTouchPanel11IsDragParamEv", {p}), ctp->m_isDrag, "IsDragParam");
        t.expect_eq(t.call("_ZNK9Framework11CTouchPanel18rTouchAndHoldParamEv", {p}), (u64)&ctp->m_hold, "rTouchAndHoldParam");
        t.expect_eq((u8)t.call("_ZNK9Framework11CTouchPanel19IsTouchAndHoldParamEv", {p}), ctp->m_isHold, "IsTouchAndHoldParam");
        t.expect_eq(t.call("_ZNK9Framework11CTouchPanel16rPinchOutInParamEv", {p}), (u64)&ctp->m_pinch, "rPinchOutInParam");
        t.expect_eq((u8)t.call("_ZNK9Framework11CTouchPanel17IsPinchOutInParamEv", {p}), ctp->m_isPinch, "IsPinchOutInParam");
        t.expect_eq(callf(t, "_ZNK9Framework11CTouchPanel20PinchOutInDeltaScaleEv", ctp), ctp->m_pinchDeltaScale, "PinchOutInDeltaScale");
        t.expect_eq(callf(t, "_ZNK9Framework11CTouchPanel24AnalogVirtualMaxDistanceEv", ctp), ctp->m_analogVirtualMaxDistance,
                    "AnalogVirtualMaxDistance");
        t.expect_eq(callf(t, "_ZNK9Framework11CTouchPanel22AnalogVirtualThresholdEv", ctp), ctp->m_analogVirtualThreshold,
                    "AnalogVirtualThreshold");
    }

    // Framework::CPad and its unit.
    auto* cpad = instance<CPad>(kVaddrCPadInstance);
    if (t.expect_eq(cpad != nullptr, true, "CPad")) {
        const u64 p = (u64)cpad;
        t.expect_eq((u64)cpad->vtable, vtable_of(t, "_ZTVN9Framework4CPadE"), "CPad vtable");
        t.expect_eq((u32)t.call("_ZNK9Framework4CPad8NumUnitsEv", {p}), cpad->m_numUnits, "NumUnits");
        t.expect_eq(cpad->m_numUnits, (u32)1, "one unit");
        t.expect_eq((u32)t.call("_ZNK9Framework4CPad4ModeEv", {p}), cpad->m_mode, "Mode()");
        t.expect_eq(t.call("_ZNK9Framework4CPad4UnitEj", {p, 0}), (u64)cpad->m_units, "Unit(0) = m_units");
        t.expect_eq(*reinterpret_cast<const u64*>(reinterpret_cast<const u8*>(cpad->m_units) - 8), (u64)1, "new[] cookie = 1");
        const CUnit* u = cpad->m_units;
        t.expect_eq((u64)u->vtable, vtable_of(t, "_ZTVN9Framework4CPad5CUnitE"), "CUnit vtable");
        t.expect_eq(u->m_port, (s32)0, "unit port 0");
        t.expect_eq((u16)t.call("_ZNK9Framework4CPad5CUnit8GetStockEv", {(u64)u}), u->m_lockButtons ? (u16)0 : u->m_keys.m_stock,
                    "unit GetStock");
        t.expect_eq((s16)t.call("_ZNK9Framework4CPad5CUnit11GetAnalogLXEv", {(u64)u}), u->m_lockLeverL ? (s16)0 : u->m_keys.m_lx,
                    "unit GetAnalogLX");
        auto* reader = instance<CPadReader>(kVaddrCPadReaderInstance);
        if (t.expect_eq(reader != nullptr, true, "CPadReader"))
            t.expect_eq((u64)reader->vtable, vtable_of(t, "_ZTVN9Framework10CPadReaderE"), "CPadReader vtable");
    }

    // Framework::CKeyboard: Now / Repeat per key against the bit array and the key records.
    auto* kb = instance<CKeyboard>(kVaddrCKeyboardInstance);
    if (t.expect_eq(kb != nullptr, true, "CKeyboard")) {
        for (int key = 0; key < 256; key++) {
            bool now = (kb->m_down[key >> 3] >> (key & 7)) & 1;
            t.expect_eq((t.call("_ZNK9Framework9CKeyboard3NowEi", {(u64)kb, (u64)key}) & 0xff) != 0, now, "CKeyboard::Now = m_down bit");
            t.expect_eq(t.call("_ZNK9Framework9CKeyboard6RepeatEi", {(u64)kb, (u64)key}) & 0xff, (u64)(kb->m_keys[key].m_flags & 1),
                        "CKeyboard::Repeat = m_keys[k] bit 0");
        }
    }
    t.expect_eq(instance<CMouse>(kVaddrCMouseInstance) != nullptr, true, "CMouse");

    // Aska's Mouse / Keyboard statics (constructed by CMouse / CKeyboard::Progress through GetInstance).
    auto* mouse = instance<Mouse>(kVaddrMouseInstance);
    t.expect_eq((u64)mouse, call0(t, "_ZN4Aska5Mouse19GetInstanceNoCreateEv"), "Mouse::GetInstanceNoCreate");
    if (mouse) t.expect_eq((u64)mouse->input.base.vtable, vtable_of(t, "_ZTVN4Aska5MouseE"), "Mouse vtable");
    auto* keyboard = instance<Keyboard>(kVaddrKeyboardInstance);
    t.expect_eq((u64)keyboard, call0(t, "_ZN4Aska8Keyboard19GetInstanceNoCreateEv"), "Keyboard::GetInstanceNoCreate");
    if (keyboard) {
        t.expect_eq((u64)keyboard->input.base.vtable, vtable_of(t, "_ZTVN4Aska8KeyboardE"), "Keyboard vtable");
        t.expect_eq(keyboard->input.m_count >= 0 && keyboard->input.m_count <= 64, true, "Keyboard message count");
    }
}

// Aska::BaseInputPeripheral's message ring on a private object (its constructor, AddMessage,
// CopyMessages, ClearMessages, the base destructor).
NATIVE_TEST("input/layout-base-input") {
    alignas(16) static u8 storage[sizeof(BaseInputPeripheral) + 8];
    std::memset(storage, 0xa5, sizeof storage);
    auto* bp = reinterpret_cast<BaseInputPeripheral*>(storage);
    t.call("_ZN4Aska19BaseInputPeripheralC2Ev", {(u64)bp});
    t.expect_eq((u64)bp->base.vtable, vtable_of(t, "_ZTVN4Aska19BaseInputPeripheralE"), "vtable");
    t.expect_eq(bp->base.m_port, (s8)-1, "port");
    t.expect_eq(bp->m_count, (s32)0, "count");
    t.expect_eq(bp->m_readIndex, (s32)0, "read index");
    for (u64 i = 0; i < 70; i++) {
        u64 msg = 0x1000000000ull * (i + 1) + i;
        t.call("_ZN4Aska19BaseInputPeripheral10AddMessageEPKNS0_7MessageE", {(u64)bp, (u64)&msg});
    }
    t.expect_eq(bp->m_count, (s32)64, "AddMessage stops at 64");
    for (u32 i = 0; i < 64; i++) {
        u64 v;
        std::memcpy(&v, bp->m_messages[i], 8);
        t.expect_eq(v, 0x1000000000ull * (i + 1) + i, "m_messages[i]");
    }
    std::vector<u64> out(64, 0);
    t.call("_ZNK4Aska19BaseInputPeripheral12CopyMessagesEPNS0_7MessageE", {(u64)bp, (u64)out.data()});
    t.expect_eq(out[63], 0x1000000000ull * 64 + 63, "CopyMessages");
    t.call("_ZN4Aska19BaseInputPeripheral13ClearMessagesEv", {(u64)bp});
    t.expect_eq(bp->m_count, (s32)0, "ClearMessages: count");
    t.expect_eq(bp->m_readIndex, (s32)0, "ClearMessages: read index");
    t.expect_eq(storage[sizeof(BaseInputPeripheral)], (u8)0xa5, "nothing written past 0x2ac");
    t.call("_ZN4Aska19BaseInputPeripheralD2Ev", {(u64)bp});
}
