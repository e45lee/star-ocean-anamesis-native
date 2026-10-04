# `input`: touch, pad, mouse, keyboard

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/input/scope.txt`](../../../decomp/input/scope.txt).
- Decompiles and the function list: [`port/decomp/input/`](../../../decomp/input/) (`symbols.tsv`; `tools/decomp.sh --into input/<topic>`).
- Types: [`input_layout.h`](input_layout.h); for Ghidra, `tools/subsystem.py export-types input` -> `port/decomp/input/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Type recovery a wave ahead of the code (port/REBUILD-QUEUE.md: input is wave 4). Layouts are proven by
[`input_layout_test.cpp`](input_layout_test.cpp) (`soa --selftest input/`, 4 tests, all pass): private
objects built and driven by the guest's own constructors and methods, or the running game's input
objects walked read-only, their fields read through these classes and compared with the guest's
accessors and with the decompile's arithmetic.

| Class (guest) | Guest size | Found from | Proven by (input/layout-...) | Status |
|---|---|---|---|---|
| `BasePeripheral` (Aska) | 0xa2 data (packed: derived members start in its tail padding) | the inlined base ctors, GetStatus, CheckConnection, Release, Get, Set | `-pad` (Get ids 0..4, Release), `-live` | typed; 0x98, 0x9c..0xa0 meaning unknown |
| `Pad` (Aska) + `PadKeys` (Pad::Keys) + `PadRepeatEach` | 0x170 / 0x28 / 4 | Pad(short), UpdateKeyStatus / KeyRepeat, CalcAnalogPosition, Flip, ResetStatus, setters, Get | `-pad` (private: every setter vs field and Get id, a synthetic raw input through UpdateKeyStatus + Flip vs GetAnalogPosition (both), GetAnalogTrigger, ResetStatus, Release), `-live` | typed; 0xa2 / 0xa3 unknown |
| `PadDroid` (Aska) | 0x178 (operator new) | ctor, the stubs | `-live` (the live pad's vtable) | typed (stub class) |
| `TouchPanel` (Aska) + `TouchData`, `TouchReport`, `TouchVector2`, `TouchDragParam`, `TouchPinchParam`, `TouchHoldParam`, `TouchOrigin` | 0x29d8 (operator new) / 0x98 / 0x10 / 4 / 0x18 / 0x20 / 8 / 0x24 | CTouchPanel::Initialize (inlined ctor), Initialize, Clear/ResetGestureParam, GetDeviceData, CopyMessages, SetTap, FindOrigin, the Get* gesture accessors | `-live` (vtable, port, flags, CalcDoublTapRange(0x50) = m_doubleTapRange, GetDrag / GetPinchOutIn / GetTouchAndHold / GetTap vs fields) | partly: the gesture params' inner fields and several 4-byte words unknown |
| `SystemTouchEvent` / `SystemTouchQueue` (TouchPanel::m_queueSystemTouchData) | 0x14 / 0x528 (nm -S) | GetDeviceData | size only | typed |
| `BaseInputPeripheral` (Aska) | 0x2ac | ctor, CopyMessages, AddMessage, ClearMessages | `-base-input` (private: 70 AddMessage, the 64-cap, the ring, CopyMessages, ClearMessages, nothing past 0x2ac) | typed |
| `Mouse` / `Keyboard` (Aska) | 0x310 / 0x6b0 (function-local statics) | ctors, GetInstance, CMouse / CKeyboard::Progress | `-live` (GetInstanceNoCreate = the static, vtables) | partly (only what CMouse / CKeyboard read) |
| `PeripheralManager` (Aska) | 0x38 (operator new) | ctor (Global::InstantiatePeripheralManager), Handler, ResetAllPeripheral, Global::Get/Register*Peripheral | `-live` (vtables, m_pad = GetPeripheral(0) = GetActivePad, m_ex = GetExPeripheral(0), m_started) | typed; 0x18 unknown |
| `CPad` (Framework) + `CPadMerged` (CPad::tMerged) | 0x110 (last field ends 0x10c) / 0x38 | ctor, Initialize, Release, Mode, rUnit, Progress, Merge, tMerged::Reset | `-live` (NumUnits, Mode, Unit(0), the new[] cookie) | typed |
| `CUnit` (Framework::CPad::CUnit) | 0x68 (new[] in CPad::Initialize) | Initialize, Copy, the getters, Lock* / UnlockAll | `-cpad-unit` (private: all 18 getters incl. float vs m_keys, the lock bytes, UnlockAll), `-live` | typed |
| `CPadReader` (Framework; an Aska::Task) | 0x28 (operator new) | CPad::Initialize's inlined ctor, Run | `-live` (vtable) | typed; the task base is kernel's |
| `CTouchPanel` (Framework) | 0x26b0 (last field ends 0x26ac) | ctor, Initialize, Release, Reset, Progress, the accessors | `-live` (all 16 accessors vs fields, IsConnected) | partly: 0x18..0x27, 0x3c..0x45 unknown |
| `CKeyboard` (Framework) + `CKeyboardKey` | 0x900 | Initialize, Progress, Now, Repeat, Press | `-live` (Now / Repeat for all 256 keys vs m_down / m_keys) | typed |
| `CMouse` (Framework) | 0x1c | Initialize, Reset, Progress, InputFromPanel | `-live` (singleton only) | typed from the decompile |

## Natives

7 bound (`soa --list-native | grep input:`), the hottest input functions: the locked methods the game
thread calls every frame and CPad::Merge. Their critical section is sync's
`FastCriticalSection::Enter` / `Leave` on the guest's own words, so the guest code that still takes the
same locks (the PeripheralManager thread's `GetStatus` / `GetDeviceData` / `UpdateKeyStatus`, `Release`)
and these natives exclude each other. Live check: `soa --live-check input[:every=N][:out=FILE]` (default
every=16; `input_check.h`: the guest original on a shadow of the object as the native saw it under the
lock).

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `Aska::Pad::SetAnalogAsDigital` / `SetRepeatThreshold` / `SetRepeatInterval` | `input_pad.cpp` | `input/pad-setters` (private pads from the guest's `Pad(short)`, edge and random values) | shadow (the pad's bytes) |
| `Aska::Pad::Flip` (vtable slot 10 `ResetStatus` first, then the swap under the lock) | `input_pad.cpp` | `input/pad-flip` (random double-buffered keys, the guest's `Pad::ResetStatus`) | shadow |
| `Framework::CPad::Merge` | `input_pad.cpp` | `input/pad-merge` (a test hook on Merge: on the game thread, the singleton's units and the active pad poked with random / edge masks, analog values, NaN / ±0 / inf floats, triggers) | the guest on a copy of `this` with m_merged poisoned |
| `Aska::TouchPanel::CopyMessages` (m_criGlobal, then the panel's lock) | `input_touch.cpp` | `input/touch-copy-messages` (private panels, 0..64 random messages) | shadow + the copied messages |
| `Aska::TouchPanel::ResetStatus` | `input_touch.cpp` | `input/touch-copy-messages` | shadow |

Not bound: `TouchPanel::GetDeviceData` (83 samples; the system queue -> TouchReport conversion on the
peripheral thread, with the frame-buffer scale: kernel's / render's Global state), `CPadReader::Run`
(53; an Aska::Task: kernel's), `Pad::GetStatus` / `UpdateKeyStatus` / `UpdateKeyRepeat` (36; the pad is a
stub on Android: zeros), the gesture recogniser (`UpdateGesture`, `ResetGestureParam`, the Get*
accessors: small, and their inner parameter fields aren't typed yet), `CPad::CUnit::Progress` (14; it
calls the three setters, now native). `Global::GetActivePad` / `GetPeripheral` and the TSingletons are
read directly (`PeripheralManager::Instance`, `CPad::Instance`, `CKeyboard::Instance`).

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `sync` (1,688 samples): sync_layout.h's classes embedded: Aska::FastCriticalSection (0x90) at
  BasePeripheral + 0x08 guards every peripheral's state, Aska::Thread (0x10) at PeripheralManager + 0x08,
  Framework::CMutex (0xb0) at CPad + 0x10. Most of the input "self" time was that critical section
  inlined (the LDAXR / STLXR spin in Pad::SetAnalogAsDigital / SetRepeat*, TouchPanel::CopyMessages,
  ResetStatus); the natives call `FastCriticalSection::Enter` / `Leave`.
- `kernel` (401 samples, same level): CPadReader is an Aska::Task (0x28, its fields opaque here);
  Aska::Global::Get/Register*Peripheral, GetActivePad, m_pVSync (UpdateKeyRepeat's frame count),
  m_pFrameBuffer (TouchPanel's pixel scale), GetCPUTime: kernel's Aska::Global.
- `render`: Aska::RenderDeviceGL::GetDefaultWindowWidth / Height (TouchPanel::GetDeviceData's scale).
Upwards: the game reads CPad / CTouchPanel / CMouse / CKeyboard (TSingletons); `cocos`'s CCocosTouch
consumes the TouchPanel gesture params (Framework::Cocos::CCocosTouch::SetPinchInfo takes a
PinchOutInParam: cocos' row, left out of this scope).

## RE notes

- **Threads.** Aska::PeripheralManager runs its own thread (Global::InitializePeripheralManager: priority
  0x80, stack 0x400) that calls GetStatus (slot 9) on the pad and the touch panel every 8 ms. The game
  thread's Framework::CPad::Progress runs the CPadReader task (Pad::Flip + copy the front keys into
  each CUnit's m_stock), then CUnit::Copy (m_stock -> m_keys) and Merge; CTouchPanel::Progress copies
  the touch messages out with CopyMessages (under TouchPanel::m_criGlobal and the panel's own lock).
- **The pad is a stub on Android.** Pad::InstantiateAppropriatePad makes an Aska::PadDroid whose
  Initialize / GetDeviceData / ResetStatus are empty: the port stays -1, m_connected 0, and the keys
  stay zero. The ~1,500 samples of Pad::SetAnalogAsDigital / SetRepeatThreshold / SetRepeatInterval /
  Flip are CPad::CUnit::Progress setting them every frame through the lock.
- **Pad state.** Double-buffered PadKeys (m_keys[2], m_front); UpdateKeyStatus (peripheral thread)
  writes m_keys[m_front ^ 1]: before = now, now = raw buttons (+ the left stick as buttons 0..3 with
  m_analogAsDigital, threshold m_analogMax / 2), stock |= now, single |= now & ~before, release |=
  before & ~now, then UpdateKeyRepeat (whole-mask and per-button repeat, frame-based on
  Global::m_pVSync's counter). Analog: (raw - m_calibration) outside the dead zone, minus the dead zone,
  clamped to m_analogMax; float = that / m_analogScale (min(max, 0x7fff - dead zone)).
- **Touch.** The Java side fills TouchPanel::m_queueSystemTouchData (65 x 0x14); the peripheral thread
  (GetDeviceData) converts each event into a TouchReport (window -> frame-buffer pixels, phase 1 began /
  2 moved / 3 ended) in the current TouchData (up to 8 pointers per message, 64 messages). Gestures
  (taps, double taps, drags, touch-and-hold, pinch) are recognised in UpdateGesture on the game thread.
- **Tail padding.** BasePeripheral's data ends at 0xa2 and Pad continues at 0xa2, BaseInputPeripheral
  at 0xa4, TouchPanel at 0xa8 (Itanium ABI reuses a non-POD base's tail padding), hence the packed base.

## Unknowns

BasePeripheral 0x98 / 0x9c / 0x9d / 0x9e / 0xa0 (Get / Set ids, no reader seen); Pad 0xa2 / 0xa3;
PadDroid 0x170; TouchData 0x00..0x07, 0x14; TouchReport 0x05, 0x0c; the inner fields of DragParam /
PinchOutInParam / TouchAndHoldParam and most of TouchOrigin (UpdateGesture, 2,428 bytes, not mapped);
TouchPanel 0x26b0, 0x26bc, 0x2710..0x271f, 0x2840..0x287f, 0x2890, 0x28f8, 0x2900, 0x2904, 0x2908, 0x29cc..;
CTouchPanel 0x18..0x27 (Progress' work), 0x3c..0x45; Mouse / Keyboard beyond what the Framework reads;
PeripheralManager 0x18.

## For the code agent

Hot (self samples over the four profiled flows, port/REBUILD-QUEUE.md's run): TouchPanel::CopyMessages
635, Pad::Flip 408, Pad::SetAnalogAsDigital 362, Pad::SetRepeatInterval 325, TouchPanel::ResetStatus
318, Pad::SetRepeatThreshold 306, CPad::Merge 196, TouchPanel::GetDeviceData 189, CPadReader::Run 71,
PeripheralManager::Handler 71, Pad::GetStatus 69, CTouchPanel::Progress 61, ResetGestureParam 61,
CPad::Progress 57, TouchPanel::GetStatus 56, UpdateGesture 51, BasePeripheral::GetStatus 46.
Nearly all of it is the FastCriticalSection spin inlined in these methods, so they move with `sync`'s
FastCriticalSection natives (Lock / Unlock on `base.m_cs`) as one family: every method that takes the
peripheral's lock (the Pad setters, Flip, GetStatus, Release, ResetStatus, CopyMessages, GetDeviceData)
must go native together, or a native's lock and the guest's inlined lock must be the same algorithm on
the same words (+0x38 lock, +0x3c spinners, +0x78 semaphore).
