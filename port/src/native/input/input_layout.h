// input_layout.h: the guest data layouts of the `input` subsystem (touch, pad, mouse, keyboard).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/input/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types input` turns the structs into port/decomp/input/types.json for Ghidra.
//
// Two layers: Aska's peripherals (Aska::BasePeripheral -> Pad / PadDroid, TouchPanel, and
// BaseInputPeripheral -> Mouse / Keyboard), owned by Aska::PeripheralManager (a thread polling them
// every 8 ms), and the Framework's per-frame readers (Framework::CPad + CPad::CUnit + CPadReader,
// CTouchPanel, CMouse, CKeyboard; TSingletons) that copy the peripherals' state each frame.
// Proofs: input_layout_test.cpp (`soa --selftest input/`).
#ifndef SOA_NATIVE_INPUT_LAYOUT_H
#define SOA_NATIVE_INPUT_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../sync/sync_layout.h"

namespace soa::native::input {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// ---- Guest addresses (ELF vaddr; add main_lib()->base) of the statics the classes below use ------
// From `nm -DS work/libSOA-3.7.0.so` (sizes in the comments) and the decompiles in port/decomp/input/.
inline constexpr u64 kVaddrPeripheralManager = 0x2ccc9e0;     // Aska::Global::m_pPeripheralManager (PeripheralManager*)
inline constexpr u64 kVaddrTouchCriGlobal = 0x2c00a60;        // Aska::TouchPanel::m_criGlobal (FastCriticalSection, 0x90)
inline constexpr u64 kVaddrSystemTouchQueue = 0x2c00af0;      // Aska::TouchPanel::m_queueSystemTouchData (0x528)
inline constexpr u64 kVaddrMouseInstance = 0x2ccc6b0;         // Aska::Mouse::StaticPrivate::pMouse
inline constexpr u64 kVaddrKeyboardInstance = 0x2ccbf10;      // Aska::Keyboard::Static::pKeyboard
inline constexpr u64 kVaddrCPadInstance = 0x2c00268;          // Framework::TSingleton<CPad>::m_pInstance
inline constexpr u64 kVaddrCPadReaderInstance = 0x2c004f0;    // Framework::TSingleton<CPadReader>::m_pInstance
inline constexpr u64 kVaddrCTouchPanelInstance = 0x2bebb10;   // Framework::TSingleton<CTouchPanel>::m_pInstance
inline constexpr u64 kVaddrCMouseInstance = 0x2c00250;        // Framework::TSingleton<CMouse>::m_pInstance
inline constexpr u64 kVaddrCKeyboardInstance = 0x2bffcd0;     // Framework::TSingleton<CKeyboard>::m_pInstance

// Aska::FastCriticalSection (0x90), Aska::Thread (0x10) and Framework::CMutex (0xb0) are the `sync`
// subsystem's classes (sync_layout.h), embedded here. The input code inlines the critical section's
// enter / leave into every locked method (the lock word at +0x38, the waiters at +0x3c, the semaphore at
// +0x78): the natives call FastCriticalSection::Enter / Leave, the same algorithm on the same words.
using sync::CMutex;
using sync::FastCriticalSection;
using sync::Thread;

// The peripherals' vtable slots (byte offset = slot * 8), from _ZTVN4Aska14BasePeripheralE and the
// calls in BasePeripheral::GetStatus / Set, PeripheralManager::Handler / ResetAllPeripheral and
// Global::RegisterPeripheral. Slots 3 / 4 are Aska::IAnimatable's Clone / CreateClone (the root base).
namespace peripheral_slot {
inline constexpr int kDtor = 0, kDtorDelete = 1, kGetClassID = 2, kGet = 5, kSet = 6;
inline constexpr int kInitialize = 7;           // Initialize(u8 port): Set(1, &port) and RegisterPeripheral call it
inline constexpr int kRelease = 8;
inline constexpr int kGetStatus = 9;            // PeripheralManager::Handler polls it every 8 ms
inline constexpr int kResetStatus = 10;         // ResetAllPeripheral, Pad::Flip, CTouchPanel::Reset
inline constexpr int kGetDeviceDataNoPort = 11; // GetStatus when m_noPort
inline constexpr int kGetDeviceData = 12;       // GetStatus when m_connected
// Pad only: 13 GetRawInputData, 14 GetRawInputDataSize, 15 SetRawOutputData, 16 GetRawOutputDataSize,
// 17 SetTriggerThreshold, 18 GetTriggerThreshold. Mouse only: 13 ShowCursor, 14 SetCursorPosition.
}  // namespace peripheral_slot

// Aska::BasePeripheral: the root of every peripheral (itself an Aska::IAnimatable: vtable only).
// Layout from the base constructor inlined into Pad::Pad, TouchPanel's construction (in
// CTouchPanel::Initialize) and BaseInputPeripheral::BaseInputPeripheral, and from GetStatus,
// CheckConnection, Release, Get, Set (port/decomp/input/aska.c). Its data ends at 0xa2 and the derived
// classes put their first members in its tail padding (Itanium ABI: Pad at 0xa2, BaseInputPeripheral at
// 0xa4, TouchPanel at 0xa8), so the class is packed to its data size and embedded as the first member
// `base` of each derived class.
#pragma pack(push, 1)
class BasePeripheral {
public:
    void DtorBase();                    // Aska::BasePeripheral::~BasePeripheral() _ZN4Aska14BasePeripheralD2Ev
    void DtorDelete();                  // _ZN4Aska14BasePeripheralD0Ev (a trap: BRK, the class is abstract)
    // Virtuals in vtable order (_ZTVN4Aska14BasePeripheralE), as plain members (the vtable is the field):
    u64 GetClassID(s32 level) const;    // slot 2  _ZNK4Aska14BasePeripheral10GetClassIDEi
    bool Get(u64 id, void* out) const;  // slot 5  _ZNK4Aska14BasePeripheral3GetEmPv: id 0 m_attr98,
                                        //   1 m_port, 2 m_connected, 3 m_attr9c, 4 m_attr9d (one byte each)
    bool Set(u64 id, const void* in);   // slot 6  _ZN4Aska14BasePeripheral3SetEmPKv: 0 m_attr98, 1 Initialize(port)
    // slot 7 Initialize(u8): pure
    void Release();                     // slot 8  _ZN4Aska14BasePeripheral7ReleaseEv (resets 0x99..0xa1 under the lock)
    bool GetStatus();                   // slot 9  _ZN4Aska14BasePeripheral9GetStatusEv
    // slots 10..12 ResetStatus / GetDeviceDataNoPort / GetDeviceData: pure
    void CheckConnection();             // _ZN4Aska14BasePeripheral15CheckConnectionEv (Initialize(m_port) unless -1)

    const void* vtable;                 // 0x00
    FastCriticalSection m_cs;           // 0x08: Aska::FastCriticalSection (sync); guards the derived state
    u8 m_attr98;                        // 0x98: Get / Set id 0; RegisterPeripheral clears it (0xff after construction)
    s8 m_port;                          // 0x99: Get id 1; -1 = none (Initialize stores the port)
    u8 m_connected;                     // 0x9a: Get id 2; GetStatus asks GetDeviceData only when set (TouchPanel::Initialize sets it)
    u8 m_updated;                       // 0x9b: Pad::UpdateKeyStatus sets it, Pad::ResetStatus clears it
    u8 m_attr9c;                        // 0x9c: Get id 3 (0xff after construction / Release)
    u8 m_attr9d;                        // 0x9d: Get id 4 (0xff after construction / Release)
    u16 m_attr9e;                       // 0x9e: 0 after construction / Release, meaning unknown
    u8 m_attra0;                        // 0xa0: 0xff after construction / Release, meaning unknown
    u8 m_noPort;                        // 0xa1: GetStatus calls GetDeviceDataNoPort when set
};
#pragma pack(pop)
static_assert(offsetof(BasePeripheral, m_cs) == 0x08);
static_assert(offsetof(BasePeripheral, m_attr98) == 0x98);
static_assert(offsetof(BasePeripheral, m_port) == 0x99);
static_assert(offsetof(BasePeripheral, m_connected) == 0x9a);
static_assert(offsetof(BasePeripheral, m_updated) == 0x9b);
static_assert(offsetof(BasePeripheral, m_attr9c) == 0x9c);
static_assert(offsetof(BasePeripheral, m_attr9e) == 0x9e);
static_assert(offsetof(BasePeripheral, m_noPort) == 0xa1);
static_assert(sizeof(BasePeripheral) == 0xa2);

// Aska::Pad::Keys: one frame of pad state (0x28). Layout from Pad::UpdateKeyStatus / UpdateKeyRepeat /
// GetAnalogPosition / GetAnalogTrigger and Framework::CPad::Merge / CUnit getters (the same struct is
// copied whole into CPad::CUnit by CPadReader::Run). Button masks are 16 bits (bit i = button i).
class PadKeys {
public:
    u16 m_now;          // 0x00: buttons down this frame (the raw buttons, plus the analog-as-digital bits)
    u16 m_before;       // 0x02: m_now of the previous update
    u16 m_stock;        // 0x04: every button seen down since the last ResetStatus (|= now)
    u16 m_single;       // 0x06: pressed (now & ~before), accumulated
    u16 m_release;      // 0x08: released (before & ~now), accumulated
    u16 m_repeat;       // 0x0a: key repeat over the whole mask (Pad::m_repeatThreshold / m_repeatInterval)
    u16 m_repeatEach;   // 0x0c: key repeat per button (Pad::m_repeatEach)
    s16 m_lx;           // 0x0e: analog sticks after calibration / dead zone / clamp (CalcAnalogPosition)
    s16 m_ly;           // 0x10
    s16 m_rx;           // 0x12
    s16 m_ry;           // 0x14
    u8 m_lt;            // 0x16: analog triggers (raw)
    u8 m_rt;            // 0x17
    float m_lxf;        // 0x18: m_lx / Pad::m_analogScale[0] (UpdateKeyStatus)
    float m_lyf;        // 0x1c
    float m_rxf;        // 0x20
    float m_ryf;        // 0x24
};
static_assert(offsetof(PadKeys, m_single) == 0x06);
static_assert(offsetof(PadKeys, m_repeatEach) == 0x0c);
static_assert(offsetof(PadKeys, m_lx) == 0x0e);
static_assert(offsetof(PadKeys, m_lt) == 0x16);
static_assert(offsetof(PadKeys, m_lxf) == 0x18);
static_assert(sizeof(PadKeys) == 0x28);

// Per-button repeat state of Aska::Pad (4 bytes; Pad::SetRepeatEachThreshold / Interval, UpdateKeyRepeat).
class PadRepeatEach {
public:
    s16 m_counter;      // 0x00: frames held
    u8 m_threshold;     // 0x02: first repeat after this many (Get ids 0x12..0x21)
    u8 m_interval;      // 0x03: then every this many (Get ids 0x22..0x31)
};
static_assert(sizeof(PadRepeatEach) == 4);

// Aska::Pad: a game pad (abstract: Android's is Aska::PadDroid, 0x178 bytes, the only one constructed:
// Pad::InstantiateAppropriatePad). Layout from Pad::Pad(short), Release, GetStatus, UpdateKeyStatus,
// UpdateKeyRepeat, CalcAnalogPosition, Flip, ResetStatus, the setters, Get (port/decomp/input/aska.c).
// The state is double-buffered: the peripheral thread writes m_keys[m_front ^ 1] (GetStatus ->
// UpdateKeyStatus), the game thread's Flip (CPadReader::Run) resets m_keys[m_front], swaps m_front and
// carries m_now over; readers use m_keys[m_front]. Everything under base.m_cs.
class Pad {
public:
    void CtorBase(s16 deadZone);        // Aska::Pad::Pad(short) _ZN4Aska3PadC2Es
    void DtorDelete();                  // _ZN4Aska3PadD0Ev (a trap: BRK)
    // Virtuals in vtable order (_ZTVN4Aska3PadE): slots 0, 3, 4, 7, 11..16 inherited or pure
    u64 GetClassID(s32 level) const;    // slot 2  _ZNK4Aska3Pad10GetClassIDEi
    bool Get(u64 id, void* out) const;  // slot 5  _ZNK4Aska3Pad3GetEmPv: 5 m_rumbleSupported, 6 m_rumbleEnabled,
                                        //   7 / 8 m_rumble (u16), 0x10 m_repeatThreshold, 0x11 m_repeatInterval,
                                        //   0x12.. / 0x22.. m_repeatEach[i] threshold / interval; else BasePeripheral's
    bool Set(u64 id, const void* in);   // slot 6  _ZN4Aska3Pad3SetEmPKv
    void Release();                     // slot 8  _ZN4Aska3Pad7ReleaseEv
    bool GetStatus();                   // slot 9  _ZN4Aska3Pad9GetStatusEv (BasePeripheral::GetStatus, then UpdateKeyStatus)
    void ResetStatus();                 // slot 10 _ZN4Aska3Pad11ResetStatusEv (clears m_keys[m_front] but m_now / m_before)
    void SetTriggerThreshold(u32 which, s32 value);   // slot 17 (empty)
    s32 GetTriggerThreshold(u32 which) const;         // slot 18 (0x7f)
    // Methods
    void SetAnalogAsDigital(bool on);   // _ZN4Aska3Pad18SetAnalogAsDigitalEb (locked; hot: CPad::CUnit::Progress every frame)
    bool IsAnalogAsDigital() const;     // _ZNK4Aska3Pad17IsAnalogAsDigitalEv
    void SetRepeatThreshold(u8 frames); // _ZN4Aska3Pad18SetRepeatThresholdEh (locked)
    void SetRepeatInterval(u8 frames);  // _ZN4Aska3Pad17SetRepeatIntervalEh (locked)
    void SetRepeatEachThreshold(u16 mask, u8 frames); // _ZN4Aska3Pad22SetRepeatEachThresholdEth
    void SetRepeatEachInterval(u16 mask, u8 frames);  // _ZN4Aska3Pad21SetRepeatEachIntervalEth
    void UpdateKeyStatus();             // _ZN4Aska3Pad15UpdateKeyStatusEv
    void UpdateKeyRepeat(PadKeys* keys);// _ZN4Aska3Pad15UpdateKeyRepeatEPNS0_4KeysE (Global::m_pVSync slot 1 = the frame count)
    void EmulateAnalogAsDigital(PadKeys* keys); // _ZN4Aska3Pad22EmulateAnalogAsDigitalEPNS0_4KeysE
    void CalcAnalogPosition(s16* lx, s16* ly, s16* rx, s16* ry); // _ZN4Aska3Pad18CalcAnalogPositionEPsS1_S1_S1_
    void CalcAnalogTrigger(u8* l, u8* r);                         // _ZN4Aska3Pad17CalcAnalogTriggerEPhS1_
    void Flip();                        // _ZN4Aska3Pad4FlipEv (hot)
    void EnableRumble(bool on);         // _ZN4Aska3Pad12EnableRumbleEb
    void SetRumble(u16 l, u16 r);       // _ZN4Aska3Pad9SetRumbleEtt
    void SetAnalogMax(s16 lx, s16 ly, s16 rx, s16 ry);                       // _ZN4Aska3Pad12SetAnalogMaxEssss
    void GetAnalogPosition(s16* lx, s16* ly, s16* rx, s16* ry) const;         // _ZNK4Aska3Pad17GetAnalogPositionEPsS1_S1_S1_
    void GetAnalogPosition(float* lx, float* ly, float* rx, float* ry) const; // _ZNK4Aska3Pad17GetAnalogPositionEPfS1_S1_S1_
    void CalcAnalogPositionMax();       // _ZN4Aska3Pad21CalcAnalogPositionMaxEv
    void GetAnalogTrigger(u8* l, u8* r) const;                               // _ZNK4Aska3Pad16GetAnalogTriggerEPhS1_
    void SetCalibration(s16 lx, s16 ly, s16 rx, s16 ry, s16 deadZone);       // _ZN4Aska3Pad14SetCalibrationEsssss
    static Pad* InstantiateAppropriatePad();  // _ZN4Aska3Pad25InstantiateAppropriatePadEv (new PadDroid, 0x178)
    static Pad* InstantiateDebugPad();        // (returns 0)
    static Pad* InstantiatePadCapture();      // (returns 0)

    BasePeripheral base;        // 0x00
    u8 m_attra2;                // 0xa2: 0xff after construction, meaning unknown
    u8 m_attra3;                // 0xa3: 0xff after construction, meaning unknown
    u8 m_rumbleSupported;       // 0xa4: Get id 5; EnableRumble does nothing without it
    u8 m_rumbleEnabled;         // 0xa5: Get id 6
    u16 m_rawButtons;           // 0xa6: the device's buttons (written by the derived GetDeviceData)
    u8 m_rawTrigger[2];         // 0xa8: L, R
    u16 m_rawAnalog[4];         // 0xaa: lx, ly, rx, ry (unsigned, centred at m_calibration)
    u16 m_rumble[2];            // 0xb2: Get ids 7 / 8 (SetRumble; 0 unless enabled)
    u8 unk_b6[2];               // 0xb6
    PadKeys m_keys[2];          // 0xb8: double buffer, see above
    s32 m_front;                // 0x108: the buffer readers use (0 / 1)
    s16 m_repeatCounter;        // 0x10c: frames the whole mask has been held
    u8 m_repeatThreshold;       // 0x10e: Get id 0x10 (0x10 after construction; CPad sets 12)
    u8 m_repeatInterval;        // 0x10f: Get id 0x11 (8; CPad sets 6)
    PadRepeatEach m_repeatEach[16]; // 0x110: per button ({0, 0x10, 8} after construction)
    s32 m_lastFrame;            // 0x150: Global::m_pVSync's frame count at the last UpdateKeyRepeat
    s16 m_analogMax[4];         // 0x154: clamp of CalcAnalogPosition (SetAnalogMax; 0x7fff)
    u16 m_calibration[4];       // 0x15c: centres (SetCalibration; 0)
    s16 m_analogScale[4];       // 0x164: min(max, 0x7fff - dead zone): the float positions' divisor
    s16 m_deadZone;             // 0x16c: Pad(short)'s argument / SetCalibration's 5th
    u8 m_analogAsDigital;       // 0x16e: SetAnalogAsDigital: the left stick also sets buttons 0..3
    u8 unk_16f[1];              // 0x16f
};
static_assert(offsetof(Pad, m_attra2) == 0xa2);
static_assert(offsetof(Pad, m_rumbleSupported) == 0xa4);
static_assert(offsetof(Pad, m_rawButtons) == 0xa6);
static_assert(offsetof(Pad, m_rawTrigger) == 0xa8);
static_assert(offsetof(Pad, m_rawAnalog) == 0xaa);
static_assert(offsetof(Pad, m_rumble) == 0xb2);
static_assert(offsetof(Pad, m_keys) == 0xb8);
static_assert(offsetof(Pad, m_front) == 0x108);
static_assert(offsetof(Pad, m_repeatCounter) == 0x10c);
static_assert(offsetof(Pad, m_repeatThreshold) == 0x10e);
static_assert(offsetof(Pad, m_repeatEach) == 0x110);
static_assert(offsetof(Pad, m_lastFrame) == 0x150);
static_assert(offsetof(Pad, m_analogMax) == 0x154);
static_assert(offsetof(Pad, m_calibration) == 0x15c);
static_assert(offsetof(Pad, m_analogScale) == 0x164);
static_assert(offsetof(Pad, m_deadZone) == 0x16c);
static_assert(offsetof(Pad, m_analogAsDigital) == 0x16e);
static_assert(sizeof(Pad) == 0x170);

// Aska::PadDroid: Android's pad (new 0x178 in Pad::InstantiateAppropriatePad). A stub: its constructor
// is Pad(0) plus the vtable, Initialize / Release / ResetStatus / GetDeviceData* / Get / Set are empty or
// return 0 (port/decomp/input/pad_droid.c), so the live pad never gets input, its port stays -1 and
// Pad::GetStatus' UpdateKeyStatus only runs on zeros. Its own 8 bytes are never written.
class PadDroid {
public:
    Pad pad;                    // 0x00
    u8 unk_170[8];              // 0x170
};
static_assert(sizeof(PadDroid) == 0x178);

// Aska::TouchPanel::Vector2: a touch position in frame-buffer pixels (GetTap copies 4-byte elements).
class TouchVector2 {
public:
    s16 x;
    s16 y;
};
static_assert(sizeof(TouchVector2) == 4);

// Aska::TouchReport: one pointer of a TouchData (0x10). Layout from TouchPanel::GetDeviceData (which
// fills it from the system queue) and CTouchPanel's constructor.
class TouchReport {
public:
    s32 m_id;           // 0x00: the pointer id (Android's)
    u8 m_pressure;      // 0x04: pressure * a constant
    u8 unk_05[1];       // 0x05
    s16 m_x;            // 0x06: frame-buffer pixels (the window scaled to Global::m_pFrameBuffer's size)
    s16 m_y;            // 0x08
    s16 m_phase;        // 0x0a: 1 began, 2 moved, 3 ended (from the system event's action)
    u8 unk_0c[4];       // 0x0c
};
static_assert(offsetof(TouchReport, m_pressure) == 0x04);
static_assert(offsetof(TouchReport, m_x) == 0x06);
static_assert(offsetof(TouchReport, m_phase) == 0x0a);
static_assert(sizeof(TouchReport) == 0x10);

// Aska::TouchData: one input message (0x98): up to 8 pointers. Layout from TouchPanel::GetDeviceData
// / CopyMessages (memcpy n * 0x98) and CTouchPanel's constructor.
class TouchData {
public:
    u8 unk_00[8];       // 0x00
    u32 m_time;         // 0x08: Global::GetCPUTime() when the message was opened
    s32 m_numReports;   // 0x0c
    s32 m_flag10;       // 0x10: 1 once a report is added, meaning unknown
    u8 unk_14[4];       // 0x14
    TouchReport m_reports[8]; // 0x18
};
static_assert(offsetof(TouchData, m_time) == 0x08);
static_assert(offsetof(TouchData, m_numReports) == 0x0c);
static_assert(offsetof(TouchData, m_reports) == 0x18);
static_assert(sizeof(TouchData) == 0x98);

// Aska::TouchPanel::DragParam (0x18): a drag gesture; GetDrag / GetDragMulti copy it whole.
class TouchDragParam {
public:
    s32 m_state;        // 0x00: 3 = none (GetDrag fails), 2 = ended (ResetGestureParam turns it into 3)
    u8 unk_04[4];       // 0x04
    s32 m_value08;      // 0x08: cleared by ResetGestureParam every frame, meaning unknown
    u8 unk_0c[8];       // 0x0c
    s32 m_id;           // 0x14: the pointer id (-1 when reset)
};
static_assert(offsetof(TouchDragParam, m_id) == 0x14);
static_assert(sizeof(TouchDragParam) == 0x18);

// Aska::TouchPanel::PinchOutInParam (0x20; GetPinchOutIn copies it whole).
class TouchPinchParam {
public:
    s32 m_state;        // 0x00: 3 = none
    u8 unk_04[0x1c];    // 0x04
};
static_assert(sizeof(TouchPinchParam) == 0x20);

// Aska::TouchPanel::TouchAndHoldParam (8 bytes; GetTouchAndHold copies one).
class TouchHoldParam {
public:
    u8 unk_00[8];
};
static_assert(sizeof(TouchHoldParam) == 8);

// Aska::TouchOrigin: a tracked pointer of the gesture recogniser (0x24; FindOrigin / SetTap).
class TouchOrigin {
public:
    u8 unk_00[8];       // 0x00
    s16 m_x;            // 0x08: where it went down (SetTap copies x / y into the tap list)
    s16 m_y;            // 0x0a
    u8 unk_0c[4];       // 0x0c
    s32 m_value10;      // 0x10: compared by SetTap (a second touch with the same value is not a tap)
    u8 unk_14[4];       // 0x14
    s32 m_id;           // 0x18: the pointer id (FindOrigin's key)
    u8 m_active;        // 0x1c
    u8 m_tapCount;      // 0x1d
    u8 unk_1e[6];       // 0x1e
};
static_assert(offsetof(TouchOrigin, m_id) == 0x18);
static_assert(offsetof(TouchOrigin, m_active) == 0x1c);
static_assert(sizeof(TouchOrigin) == 0x24);

// Aska::TouchPanel: the touch screen (0x29d8: operator new in Framework::CTouchPanel::Initialize, which
// inlines the constructor; registered as the "ex" peripheral 0). Layout from that construction,
// Initialize, ClearGestureParam, ResetGestureParam, GetDeviceData, CopyMessages, ResetStatus, the Get*
// gesture accessors, SetTap / FindOrigin (port/decomp/input/aska.c). The peripheral thread turns the
// static system queue (m_queueSystemTouchData, filled by the Java side) into m_data under base.m_cs;
// CTouchPanel::Progress copies it out (CopyMessages, under m_criGlobal too) and runs the gestures.
class TouchPanel {
public:
    void DtorDelete();                  // _ZN4Aska10TouchPanelD0Ev
    // Virtuals (_ZTVN4Aska10TouchPanelE): slots 2, 5, 6, 8 inherited from BasePeripheral
    void Initialize(u8 port);           // slot 7  _ZN4Aska10TouchPanel10InitializeEh
    bool GetStatus();                   // slot 9  _ZN4Aska10TouchPanel9GetStatusEv (GetDeviceData, returns 1)
    void ResetStatus();                 // slot 10 _ZN4Aska10TouchPanel11ResetStatusEv (m_numData = 0 under the lock)
    void GetDeviceDataNoPort();         // slot 11 (= GetDeviceData through the vtable)
    bool GetDeviceData();               // slot 12 _ZN4Aska10TouchPanel13GetDeviceDataEv
    // Methods
    s32 CopyMessages(TouchData* out);   // _ZN4Aska10TouchPanel12CopyMessagesEPNS_9TouchDataE (hottest input function)
    void Enable(bool on);               // _ZN4Aska10TouchPanel6EnableEb
    void ClearGestureParam();           // _ZN4Aska10TouchPanel17ClearGestureParamEv
    s32 CalcDoublTapRange(s32 n);       // _ZN4Aska10TouchPanel17CalcDoublTapRangeEi (max(fb w, h) * n / a constant)
    void ResetGestureParam();           // _ZN4Aska10TouchPanel17ResetGestureParamEv
    void UpdateGesture(TouchData* data, s32 n);  // _ZN4Aska10TouchPanel13UpdateGestureEPNS_9TouchDataEi
    TouchOrigin* FindOrigin(u32 id);    // _ZN4Aska10TouchPanel10FindOriginEj
    void SetTap(TouchOrigin* origin, s32 kind);  // _ZN4Aska10TouchPanel6SetTapEPNS_11TouchOriginEi
    s32 GetTap(TouchVector2* out, s32 max);      // _ZN4Aska10TouchPanel6GetTapEPNS0_7Vector2Ei (when m_tapKind == 1)
    s32 GetDoubleTap(TouchVector2* out, s32 max);// _ZN4Aska10TouchPanel12GetDoubleTapEPNS0_7Vector2Ei (m_tapKind == 2)
    bool GetDrag(TouchDragParam* out);           // _ZN4Aska10TouchPanel7GetDragEPNS0_9DragParamE (m_drag[0])
    u32 GetDragMulti(TouchDragParam (&out)[8]);  // _ZN4Aska10TouchPanel12GetDragMultiERA8_NS0_9DragParamE
    bool GetTouchAndHold(TouchHoldParam* out);   // _ZN4Aska10TouchPanel15GetTouchAndHoldEPNS0_17TouchAndHoldParamE
    s32 GetTouchAndHoldMulti(TouchHoldParam (&out)[8]);
    bool GetPinchOutIn(TouchPinchParam* out);    // _ZN4Aska10TouchPanel13GetPinchOutInEPNS0_15PinchOutInParamE
    static bool InitializeGesture();    // _ZN4Aska10TouchPanel17InitializeGestureEv
    static void FinalizeGesture();      // _ZN4Aska10TouchPanel15FinalizeGestureEv

    BasePeripheral base;            // 0x00
    u8 unk_a2[6];                   // 0xa2
    TouchData m_data[64];           // 0xa8: this poll's messages
    s32 m_numData;                  // 0x26a8
    u8 unk_26ac[4];                 // 0x26ac
    u64 m_value26b0;                // 0x26b0: 0 after construction, meaning unknown
    s32 m_doubleTapRange;           // 0x26b8: CalcDoublTapRange(0x50) (Initialize, ClearGestureParam)
    s32 m_value26bc;                // 0x26bc: 0 after ClearGestureParam
    s16 m_lastX;                    // 0x26c0: the last primary pointer's position (GetDeviceData)
    s16 m_lastY;                    // 0x26c2
    u8 m_attached;                  // 0x26c4: CTouchPanel::IsConnected
    u8 m_enabled;                   // 0x26c5: Enable(); Initialize sets 1
    TouchVector2 m_taps[8];         // 0x26c6: the last tap / double tap's positions (GetTap)
    TouchVector2 m_tapWork[8];      // 0x26e6: being collected (SetTap)
    u8 unk_2706[2];                 // 0x2706
    s32 m_tapWorkCount;             // 0x2708
    u8 unk_270c[4];                 // 0x270c
    u8 unk_2710[0x10];              // 0x2710: cleared with the origins (memset 0x2710, 0x130)
    TouchOrigin m_origins[8];       // 0x2720
    u8 unk_2840[0x40];              // 0x2840
    s32 m_tapCount;                 // 0x2880: valid entries of m_taps
    s32 m_lastTapCount;             // 0x2884: m_tapCount before ResetGestureParam
    s32 m_tapKind;                  // 0x2888: 1 tap, 2 double tap
    s32 m_lastTapKind;              // 0x288c
    u8 unk_2890[4];                 // 0x2890
    TouchHoldParam m_holds[8];      // 0x2894
    s32 m_numHolds;                 // 0x28d4
    TouchPinchParam m_pinch;        // 0x28d8
    u8 unk_28f8[4];                 // 0x28f8
    s32 m_holdTime;                 // 0x28fc: 0xfa (250) after Initialize / ClearGestureParam (a touch-and-hold time?)
    u8 unk_2900[4];                 // 0x2900
    s32 m_value2904;                // 0x2904: 0 after ClearGestureParam and SetTap
    u8 unk_2908[4];                 // 0x2908
    TouchDragParam m_drag[8];       // 0x290c
    u8 unk_29cc[0xc];               // 0x29cc
};
static_assert(offsetof(TouchPanel, m_data) == 0xa8);
static_assert(offsetof(TouchPanel, m_numData) == 0x26a8);
static_assert(offsetof(TouchPanel, m_doubleTapRange) == 0x26b8);
static_assert(offsetof(TouchPanel, m_lastX) == 0x26c0);
static_assert(offsetof(TouchPanel, m_attached) == 0x26c4);
static_assert(offsetof(TouchPanel, m_enabled) == 0x26c5);
static_assert(offsetof(TouchPanel, m_taps) == 0x26c6);
static_assert(offsetof(TouchPanel, m_tapWork) == 0x26e6);
static_assert(offsetof(TouchPanel, m_tapWorkCount) == 0x2708);
static_assert(offsetof(TouchPanel, m_origins) == 0x2720);
static_assert(offsetof(TouchPanel, m_tapCount) == 0x2880);
static_assert(offsetof(TouchPanel, m_tapKind) == 0x2888);
static_assert(offsetof(TouchPanel, m_holds) == 0x2894);
static_assert(offsetof(TouchPanel, m_numHolds) == 0x28d4);
static_assert(offsetof(TouchPanel, m_pinch) == 0x28d8);
static_assert(offsetof(TouchPanel, m_holdTime) == 0x28fc);
static_assert(offsetof(TouchPanel, m_value2904) == 0x2904);
static_assert(offsetof(TouchPanel, m_drag) == 0x290c);
static_assert(sizeof(TouchPanel) == 0x29d8);

// One event of Aska::TouchPanel::m_queueSystemTouchData (0x14; read by GetDeviceData).
class SystemTouchEvent {
public:
    u32 m_action;       // 0x00: low byte the Android action (0..6), high bits: not the primary pointer
    s32 m_id;           // 0x04
    float m_x;          // 0x08: window pixels
    float m_y;          // 0x0c
    float m_pressure;   // 0x10
};
static_assert(sizeof(SystemTouchEvent) == 0x14);

// Aska::TouchPanel::m_queueSystemTouchData (0x528, nm -S): a ring of 65 events (the indices wrap at
// 0x41), written by the Java side's touch callback, read by GetDeviceData.
class SystemTouchQueue {
public:
    u8 unk_00[8];       // 0x00
    s32 m_written;      // 0x08: the producer's last slot: GetDeviceData stops when its next slot reaches it
    s32 m_consumed;     // 0x0c: GetDeviceData's last slot (it reads events[(m_consumed + 1) % 65], then stores that)
    SystemTouchEvent m_events[65]; // 0x10
    u8 unk_524[4];      // 0x524
};
static_assert(offsetof(SystemTouchQueue, m_events) == 0x10);
static_assert(sizeof(SystemTouchQueue) == 0x528);

// Aska::BaseInputPeripheral: the message-queue peripheral Mouse and Keyboard derive from. Layout from
// its constructor (memset 0xa4, 0x208), CopyMessages, AddMessage, ClearMessages (port/decomp/input/base_input.c).
class BaseInputPeripheral {
public:
    void CtorBase();                    // _ZN4Aska19BaseInputPeripheralC2Ev
    void DtorBase();                    // _ZN4Aska19BaseInputPeripheralD2Ev
    void DtorDelete();                  // _ZN4Aska19BaseInputPeripheralD0Ev
    void Initialize(u8 port);           // slot 7 (empty)
    void Release();                     // slot 8 (BasePeripheral::Release)
    bool GetStatus();                   // slot 9 (0)
    void ResetStatus();                 // slot 10 (empty)
    void GetDeviceDataNoPort();         // slot 11 (empty)
    bool GetDeviceData();               // slot 12 (0)
    void CopyMessages(u64* out) const;  // _ZNK4Aska19BaseInputPeripheral12CopyMessagesEPNS0_7MessageE
    void ClearMessages();               // _ZN4Aska19BaseInputPeripheral13ClearMessagesEv
    void AddMessage(const u64* msg);    // _ZN4Aska19BaseInputPeripheral10AddMessageEPKNS0_7MessageE

    BasePeripheral base;        // 0x00
    u8 unk_a2[2];               // 0xa2
    u32 m_messages[64][2];      // 0xa4: BaseInputPeripheral::Message (8 bytes each, 4-aligned), a ring
    s32 m_readIndex;            // 0x2a4
    s32 m_count;                // 0x2a8: AddMessage stops at 64
};
static_assert(offsetof(BaseInputPeripheral, m_messages) == 0xa4);
static_assert(offsetof(BaseInputPeripheral, m_readIndex) == 0x2a4);
static_assert(offsetof(BaseInputPeripheral, m_count) == 0x2a8);
static_assert(sizeof(BaseInputPeripheral) == 0x2ac);

// Aska::Mouse: a function-local static (0x2dcc6b8, guard after it: 0x310 bytes at most); Mouse::GetInstance
// constructs it. Only GetInstance executes in the profiled flows; CMouse::Progress reads 0x2c0..0x300.
class Mouse {
public:
    void CtorBase();                    // _ZN4Aska5MouseC2Ev
    static Mouse* GetInstance();        // _ZN4Aska5Mouse11GetInstanceEv
    static Mouse* GetInstanceNoCreate();// _ZN4Aska5Mouse19GetInstanceNoCreateEv

    BaseInputPeripheral input;  // 0x00
    u8 unk_2ac[0x14];           // 0x2ac: cleared by the constructor
    u32 m_buttonL;              // 0x2c0: bit 0 = down (CMouse::Progress)
    u32 m_buttonR;              // 0x2c4
    u32 m_buttonM;              // 0x2c8
    u8 unk_2cc[0x30];           // 0x2cc
    s32 m_x;                    // 0x2fc
    s32 m_y;                    // 0x300
    u8 unk_304[0xc];            // 0x304: the constructor clears up to 0x30e
};
static_assert(offsetof(Mouse, m_buttonL) == 0x2c0);
static_assert(offsetof(Mouse, m_x) == 0x2fc);
static_assert(sizeof(Mouse) == 0x310);

// Aska::Keyboard: a function-local static (GetInstance); 0x402 bytes cleared from 0x2ac. CKeyboard::Progress
// reads s32 m_keyDown[256] at 0x2ac.
class Keyboard {
public:
    void CtorBase();                    // _ZN4Aska8KeyboardC2Ev
    static Keyboard* GetInstance();     // _ZN4Aska8Keyboard11GetInstanceEv
    static Keyboard* GetInstanceNoCreate();

    BaseInputPeripheral input;  // 0x00
    s32 m_keyDown[256];         // 0x2ac: > 0 = down
    u8 unk_6ac[2];              // 0x6ac: (the constructor's memset ends at 0x6ae)
    u8 unk_6ae[2];              // 0x6ae
};
static_assert(offsetof(Keyboard, m_keyDown) == 0x2ac);
static_assert(sizeof(Keyboard) == 0x6b0);

// Aska::PeripheralManager (0x38: operator new in Global::InstantiatePeripheralManager): IAnimatable at
// 0 and an Aska::Thread at 8 (vtable at +0x60 of _ZTVN4Aska17PeripheralManagerE, its Handler a thunk).
// Handler polls m_pad and m_ex (vtable slot 9, GetStatus) every 8 ms until m_quit.
class PeripheralManager {
public:
    void Ctor();                        // _ZN4Aska17PeripheralManagerC1Ev
    void DtorBase();                    // _ZN4Aska17PeripheralManagerD2Ev
    void DtorDelete();                  // _ZN4Aska17PeripheralManagerD0Ev
    bool Get(u64 id, void* out) const;  // slot 5 (0)
    bool Set(u64 id, const void* in);   // slot 6 (0)
    void Handler();                     // slot 7  _ZN4Aska17PeripheralManager7HandlerEv
    void ResetAllPeripheral();          // _ZN4Aska17PeripheralManager18ResetAllPeripheralEv (slot 10 of both)

    const void* vtable;         // 0x00: _ZTVN4Aska17PeripheralManagerE + 0x10
    Thread m_thread;            // 0x08: Aska::Thread (sync); its vtable = _ZTV... + 0x60
    u8 unk_18[8];               // 0x18: not written by the constructor (Aska::Thread's?)
    BasePeripheral* m_pad;      // 0x20: Global::GetPeripheral(0) / GetActivePad / RegisterPeripheral(0)
    BasePeripheral* m_ex;       // 0x28: Global::GetExPeripheral(0): the TouchPanel
    u8 m_quit;                  // 0x30: the destructor sets it, Handler loops until it
    u8 m_started;               // 0x31: InitializePeripheralManager (thread created)
    u8 unk_32[6];               // 0x32
};
static_assert(offsetof(PeripheralManager, m_thread) == 0x08);
static_assert(offsetof(PeripheralManager, m_pad) == 0x20);
static_assert(offsetof(PeripheralManager, m_ex) == 0x28);
static_assert(offsetof(PeripheralManager, m_quit) == 0x30);
static_assert(sizeof(PeripheralManager) == 0x38);

// ---- Framework ---------------------------------------------------------------------------------

// Framework::CPad::CUnit (0x68): one pad port. Layout from CUnit::Initialize / Copy / UnlockAll / the
// getters and CPad::Merge / CPadReader::Run (port/decomp/input/framework.c). CPadReader::Run (an
// Aska::Task) copies the Aska pad's front keys into m_stock under CPad's mutex; CUnit::Copy (the game
// thread, CPad::Progress) then copies m_stock to m_keys, which the getters read.
class CUnit {
public:
    void CtorBase();                    // _ZN9Framework4CPad5CUnitC2Ev
    void DtorBase();                    // _ZN9Framework4CPad5CUnitD2Ev
    // Virtuals in vtable order (_ZTVN9Framework4CPad5CUnitE): the getters, slot 0 GetNow .. 18 GetAnalogRYF,
    // 19.. IsNow / IsBefore / IsSingle / IsRelease / IsRepeat / IsRepeatEach (reading m_keys)
    u16 GetNow() const;                 // slot 0
    u16 GetBefore() const;              // slot 1
    u16 GetStock() const;               // slot 2
    u16 GetSingle() const;              // slot 3
    u16 GetRelease() const;             // slot 4
    u16 GetRepeat() const;              // slot 5
    u16 GetRepeatEach() const;          // slot 6
    s16 GetAnalogLX() const;            // slot 7
    s16 GetAnalogLY() const;            // slot 8
    s16 GetAnalogRX() const;            // slot 9
    s16 GetAnalogRY() const;            // slot 10
    u8 GetAnalogLT() const;             // slot 11
    u8 GetAnalogRT() const;             // slot 12
    float GetAnalogLTF() const;         // slot 13
    float GetAnalogRTF() const;         // slot 14
    float GetAnalogLXF() const;         // slot 15
    float GetAnalogLYF() const;         // slot 16
    float GetAnalogRXF() const;         // slot 17
    float GetAnalogRYF() const;         // slot 18
    // Methods
    void Initialize(u32 port);          // _ZN9Framework4CPad5CUnit10InitializeEj (instantiates and registers the Aska pad)
    void Release();
    void Clear();
    void Progress(float dt);            // _ZN9Framework4CPad5CUnit8ProgressEf (the Aska pad's repeat timing by dt)
    void Copy();                        // _ZN9Framework4CPad5CUnit4CopyEv
    const PadKeys* Keys() const;        // _ZNK9Framework4CPad5CUnit4KeysEv (&m_keys)
    PadKeys* rKeys();                   // _ZN9Framework4CPad5CUnit5rKeysEv
    void LockAll();                     // _ZN9Framework4CPad5CUnit7LockAllEv
    void LockButtons();
    void LockAnalogLeverL();
    void LockAnalogLeverR();
    void LockAnalogTriggerL();
    void LockAnalogTriggerR();
    void UnlockAll();                   // _ZN9Framework4CPad5CUnit9UnlockAllEv

    const void* vtable;         // 0x00: _ZTVN9Framework4CPad5CUnitE + 0x10
    s32 m_port;                 // 0x08: -1 until Initialize
    PadKeys m_keys;             // 0x0c: what the getters read
    PadKeys m_stock;            // 0x34: CPadReader::Run's copy of the Aska pad's front keys
    u8 m_lockButtons;           // 0x5c: LockButtons: the mask getters return 0
    u8 m_lockLeverL;            // 0x5d: LockAnalogLeverL: GetAnalogLX / LY (and F) return 0
    u8 m_lockLeverR;            // 0x5e: LockAnalogLeverR
    u8 m_lockTriggerL;          // 0x5f: LockAnalogTriggerL
    u8 m_lockTriggerR;          // 0x60: LockAnalogTriggerR (LockAll sets all five, UnlockAll clears them)
    u8 unk_61[7];               // 0x61
};
static_assert(offsetof(CUnit, m_port) == 0x08);
static_assert(offsetof(CUnit, m_keys) == 0x0c);
static_assert(offsetof(CUnit, m_stock) == 0x34);
static_assert(offsetof(CUnit, m_lockButtons) == 0x5c);
static_assert(offsetof(CUnit, m_lockTriggerR) == 0x60);
static_assert(sizeof(CUnit) == 0x68);

// Framework::CPad::tMerged (0x38): every unit's keys and the active Aska pad's, OR'ed (masks) or
// largest-magnitude (analog), rebuilt by CPad::Merge each frame. Layout from Merge and tMerged::Reset.
class CPadMerged {
public:
    void Reset();                       // _ZN9Framework4CPad7tMerged5ResetEv

    u16 m_now;          // 0x00
    u16 m_before;       // 0x02
    u16 m_stock;        // 0x04
    u16 m_single;       // 0x06
    u16 m_release;      // 0x08
    u16 m_repeat;       // 0x0a
    u16 m_repeatEach;   // 0x0c
    u8 unk_0e[2];       // 0x0e
    u32 m_lt;           // 0x10
    u32 m_rt;           // 0x14
    s32 m_lx;           // 0x18
    s32 m_ly;           // 0x1c
    s32 m_rx;           // 0x20
    s32 m_ry;           // 0x24
    float m_lxf;        // 0x28
    float m_lyf;        // 0x2c
    float m_rxf;        // 0x30
    float m_ryf;        // 0x34
};
static_assert(offsetof(CPadMerged, m_lt) == 0x10);
static_assert(offsetof(CPadMerged, m_lx) == 0x18);
static_assert(offsetof(CPadMerged, m_lxf) == 0x28);
static_assert(sizeof(CPadMerged) == 0x38);

// Framework::CPad (TSingleton): the game's pad reader. Layout from CPad::CPad, Initialize, Release,
// Mode, rUnit, NumUnits, Progress, Merge (port/decomp/input/framework.c). Size: the last field ends
// at 0x10c (no allocation site read).
class CPad {
public:
    void Ctor();                        // _ZN9Framework4CPadC1Ev
    void DtorBase();                    // _ZN9Framework4CPadD2Ev
    void DtorDelete();                  // _ZN9Framework4CPadD0Ev
    void Initialize();                  // _ZN9Framework4CPad10InitializeEv (1 unit; creates the CPadReader task)
    void Release();                     // _ZN9Framework4CPad7ReleaseEv
    void Mode(u32 mode);                // _ZN9Framework4CPad4ModeEj
    u32 Mode() const;                   // _ZNK9Framework4CPad4ModeEv
    CUnit* rUnit(u32 i);                // _ZN9Framework4CPad5rUnitEj
    const CUnit* Unit(u32 i) const;     // _ZNK9Framework4CPad4UnitEj
    u32 NumUnits() const;               // _ZNK9Framework4CPad8NumUnitsEv
    void Clear();                       // _ZN9Framework4CPad5ClearEv
    void Progress(float dt);            // _ZN9Framework4CPad8ProgressEf (hot: the frame's pad update)
    void Merge();                       // _ZN9Framework4CPad5MergeEv (hot)
    u16 NowWithEveryMode() const;       // _ZNK9Framework4CPad16NowWithEveryModeEv
    u16 SingleWithEveryMode() const;
    u16 RepeatWithEveryMode() const;
    // GetNow(int) .. GetAnalogRYF(int): the merged value when mode matches (see the decompile)

    const void* vtable;         // 0x00: _ZTVN9Framework4CPadE + 0x10
    u8 unk_08[8];               // 0x08
    CMutex m_mutex;             // 0x10: Framework::CMutex (sync)
    u32 m_numUnits;             // 0xc0: 1 (Initialize)
    u8 unk_c4[4];               // 0xc4
    CUnit* m_units;             // 0xc8: new[] (count cookie at -8)
    u32 m_mode;                 // 0xd0: Mode(u32) (only 0 is valid); Progress skips the units otherwise
    CPadMerged m_merged;        // 0xd4
    u8 unk_10c[4];              // 0x10c
};
static_assert(offsetof(CPad, m_mutex) == 0x10);
static_assert(offsetof(CPad, m_numUnits) == 0xc0);
static_assert(offsetof(CPad, m_units) == 0xc8);
static_assert(offsetof(CPad, m_mode) == 0xd0);
static_assert(offsetof(CPad, m_merged) == 0xd4);
static_assert(sizeof(CPad) == 0x110);

// Framework::CPadReader (TSingleton; an Aska::Task, 0x28: operator new in CPad::Initialize). The task
// base (vtable, 0x08..0x26) is the kernel subsystem's Aska::Task: opaque here.
class CPadReader {
public:
    void DtorBase();                    // _ZN9Framework10CPadReaderD2Ev
    void DtorDelete();                  // _ZN9Framework10CPadReaderD0Ev
    u64 GetClassID(s32 level) const;    // _ZNK9Framework10CPadReader10GetClassIDEi
    s32 GetDefaultLevel() const;        // _ZNK9Framework10CPadReader15GetDefaultLevelEv (4)
    void Run(s32 arg);                  // _ZN9Framework10CPadReader3RunEi (Flip + copy into each unit's m_stock)

    const void* vtable;         // 0x00: _ZTVN9Framework10CPadReaderE + 0x10
    u8 m_task[0x20];            // 0x08: Aska::Task's fields (kernel): 0x08..0x18 0, 0x20 u32 = vtable slot 11's
                                // result (the default level), 0x24 u16, 0x26 u8 (CPad::Initialize's inlined ctor)
};
static_assert(sizeof(CPadReader) == 0x28);

// Framework::CTouchPanel (TSingleton): the game's touch reader. Layout from CTouchPanel::CTouchPanel,
// Initialize, Release, Reset, Progress and the accessors (port/decomp/input/framework.c). Size: the last
// field ends at 0x26ac (no allocation site read).
class CTouchPanel {
public:
    void Ctor();                        // _ZN9Framework11CTouchPanelC1Ev
    void DtorBase();                    // _ZN9Framework11CTouchPanelD2Ev
    void DtorDelete();                  // _ZN9Framework11CTouchPanelD0Ev
    void Initialize();                  // _ZN9Framework11CTouchPanel10InitializeEv (new Aska::TouchPanel, RegisterExPeripheral(0))
    void Release();
    void Reset();                       // the Aska panel's ResetStatus
    void Progress(float dt);            // _ZN9Framework11CTouchPanel8ProgressEf (hot: CopyMessages + gestures)
    void InputFromMouse();              // (empty)
    bool IsConnected() const;           // _ZNK9Framework11CTouchPanel11IsConnectedEv (GetExPeripheral(0)->m_attached)
    const void* rAnalogVirtual() const; // &m_analogVirtual
    const TouchData* rTouchDataBuffer() const; // &m_data[0]
    s32 NumTouchData() const;           // m_numData
    const TouchVector2* rTapParam(u32 i) const;   // &m_tap[i] (i < 2)
    bool IsTapParam() const;
    const TouchVector2* rDoubleTapParam() const;
    bool IsDoubleTapParam() const;
    const TouchDragParam* rDragParam() const;
    bool IsDragParam() const;
    const TouchHoldParam* rTouchAndHoldParam() const;
    bool IsTouchAndHoldParam() const;
    const TouchPinchParam* rPinchOutInParam() const;
    bool IsPinchOutInParam() const;
    float PinchOutInDeltaScale() const;
    float AnalogVirtualMaxDistance() const;
    void AnalogVirtualMaxDistance(float v);
    float AnalogVirtualThreshold() const;
    void AnalogVirtualThreshold(float v);

    const void* vtable;             // 0x00: _ZTVN9Framework11CTouchPanelE + 0x10
    TouchPanel* m_panel;            // 0x08: the Aska panel (Initialize)
    s32 m_x;                        // 0x10: the primary pointer (CMouse::InputFromPanel reads x / y / m_touching)
    s32 m_y;                        // 0x14
    u8 unk_18[0x10];                // 0x18: Progress's work, meaning unknown
    float m_analogVirtualMaxDistance; // 0x28: a constant pair after construction
    float m_analogVirtualThreshold;   // 0x2c
    u8 m_analogVirtual[8];          // 0x30: rAnalogVirtual (0 after Initialize)
    u8 m_touching;                  // 0x38
    u8 unk_39[3];                   // 0x39
    u8 unk_3c[0xa];                 // 0x3c: cleared by the constructor
    u8 m_flag46;                    // 0x46: cleared by Initialize
    u8 unk_47[1];                   // 0x47
    TouchData m_data[64];           // 0x48: CopyMessages' copy
    s32 m_numData;                  // 0x2648
    TouchVector2 m_tap[2];          // 0x264c
    u8 m_isTap;                     // 0x2654
    u8 unk_2655[1];                 // 0x2655
    TouchVector2 m_doubleTap;       // 0x2656
    u8 m_isDoubleTap;               // 0x265a
    u8 unk_265b[1];                 // 0x265b
    TouchDragParam m_drag;          // 0x265c
    u8 m_isDrag;                    // 0x2674
    u8 unk_2675[3];                 // 0x2675
    TouchHoldParam m_hold;          // 0x2678
    u8 m_isHold;                    // 0x2680
    u8 unk_2681[3];                 // 0x2681
    TouchPinchParam m_pinch;        // 0x2684
    u8 m_isPinch;                   // 0x26a4
    u8 unk_26a5[3];                 // 0x26a5
    float m_pinchDeltaScale;        // 0x26a8
    u8 unk_26ac[4];                 // 0x26ac
};
static_assert(offsetof(CTouchPanel, m_panel) == 0x08);
static_assert(offsetof(CTouchPanel, m_x) == 0x10);
static_assert(offsetof(CTouchPanel, m_analogVirtualMaxDistance) == 0x28);
static_assert(offsetof(CTouchPanel, m_analogVirtual) == 0x30);
static_assert(offsetof(CTouchPanel, m_touching) == 0x38);
static_assert(offsetof(CTouchPanel, m_flag46) == 0x46);
static_assert(offsetof(CTouchPanel, m_data) == 0x48);
static_assert(offsetof(CTouchPanel, m_numData) == 0x2648);
static_assert(offsetof(CTouchPanel, m_tap) == 0x264c);
static_assert(offsetof(CTouchPanel, m_isTap) == 0x2654);
static_assert(offsetof(CTouchPanel, m_doubleTap) == 0x2656);
static_assert(offsetof(CTouchPanel, m_drag) == 0x265c);
static_assert(offsetof(CTouchPanel, m_isDrag) == 0x2674);
static_assert(offsetof(CTouchPanel, m_hold) == 0x2678);
static_assert(offsetof(CTouchPanel, m_pinch) == 0x2684);
static_assert(offsetof(CTouchPanel, m_isPinch) == 0x26a4);
static_assert(offsetof(CTouchPanel, m_pinchDeltaScale) == 0x26a8);
static_assert(sizeof(CTouchPanel) == 0x26b0);

// One key of Framework::CKeyboard (8 bytes): bit 0 repeat now, bit 1 past the first delay; a timer.
class CKeyboardKey {
public:
    u8 m_flags;         // 0x00
    u8 unk_01[3];       // 0x01
    float m_timer;      // 0x04: counts down by dt; reloaded with 12 then 6
};
static_assert(sizeof(CKeyboardKey) == 8);

// Framework::CKeyboard (TSingleton; no vtable). Layout from Initialize, Progress, Now, Repeat, Press.
class CKeyboard {
public:
    void Initialize();                  // _ZN9Framework9CKeyboard10InitializeEv
    void Release();
    void Progress(float dt);            // _ZN9Framework9CKeyboard8ProgressEf (Aska::Keyboard::m_keyDown -> m_down)
    bool Now(s32 key) const;            // _ZNK9Framework9CKeyboard3NowEi
    bool Repeat(s32 key) const;         // _ZNK9Framework9CKeyboard6RepeatEi
    s32 Press() const;                  // _ZNK9Framework9CKeyboard5PressEv
    static bool IsDrawableCharacter(u32 c);

    u8 m_down[32];              // 0x00: one bit per key
    u8 unk_20[0xe0];            // 0x20: cleared by Initialize (memset 0x100)
    CKeyboardKey m_keys[256];   // 0x100
};
static_assert(offsetof(CKeyboard, m_keys) == 0x100);
static_assert(sizeof(CKeyboard) == 0x900);

// Framework::CMouse (TSingleton; no vtable). Layout from Initialize, Reset, Progress, InputFromPanel.
// The button bytes: bit 0 down, 1 down (copy), 2 pressed, 3 released; the high nibble is kept.
class CMouse {
public:
    void Initialize();                  // _ZN9Framework6CMouse10InitializeEv
    void Reset();
    void Progress(float dt);            // _ZN9Framework6CMouse8ProgressEf
    void InputFromPanel();              // _ZN9Framework6CMouse14InputFromPanelEv (CTouchPanel's m_x / m_y / m_touching)

    s32 m_x;            // 0x00
    s32 m_y;            // 0x04
    u32 m_button[5];    // 0x08: L, R, M, and two more (flags in the low byte)
};
static_assert(offsetof(CMouse, m_button) == 0x08);
static_assert(sizeof(CMouse) == 0x1c);

}  // namespace soa::native::input

#endif  // SOA_NATIVE_INPUT_LAYOUT_H
