# `particles`: particles: Aska's particle manager, emitters, particle objects and their rendering

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/particles/scope.txt`](../../../decomp/particles/scope.txt).
- Decompiles and the function list: [`port/decomp/particles/`](../../../decomp/particles/) (`symbols.tsv`; `tools/decomp.sh --into particles/<topic>`).
- Types: [`particles_layout.h`](particles_layout.h); for Ghidra, `tools/subsystem.py export-types particles` -> `port/decomp/particles/types.json`.
- Build settings of its own (a host library, a definition): none; a `subsystem.cmake` here would hold them (port/CMakeLists.txt includes it).

## Types (classes with their methods attached)

Every class is in [`particles_layout.h`](particles_layout.h) (namespace `soa::native::particles`); a guest
base class is the first member `base`, the guest's virtuals are members (no C++ `virtual`: the guest's
vtable is the first field). Bases from other subsystems: kernel's `TaskManager` / `Task` / `INotify` /
`MessageDispatcherBlock`, render's `HierarchicalObject` / `RenderableObject`, sync's `CriticalSection` /
`Event` / `FastCriticalSection`.

| Class (guest) | Guest size | Found from | Proven by | Status |
|---|---|---|---|---|
| `ParticleManager` (Aska) | 0x90e8 (Global::InstantiateParticleManager: operator new(0x90e8)) | ParticleManager(), Init, Add / Delete, RunLow, RunAfterRendering, DispatchEmitters, Kick, Handler | `particles/*` (the guest's functions over private managers: every field they touch) | partial: the task list, the INotify at 0xff0, the clock, m_cs, m_inFlight, the frame stamps, the two lists |
| `IParticleEmitter` (Aska) | 0x328 (the constructor writes up to 0x324; the concrete emitters are 0x400..0x510) | IParticleEmitter(), SkipThisFrame, IsEmitting, PrepareMatrices, FillMatrixContext, the manager's dispatch | `particles/*` | partial: the dispatch fields 0x198..0x215, the object / renderable / link pointers |
| `ParticleRenderableBase` (Aska) | 0xfe0 (CreateParticle allocates every ParticleRenderableObject<> as 0xfe0; assumed the base's too) | IsBufferReady, SkipThisFrame, Simulate (the active count) | `particles/getters` | partial: m_activeCount, the two buffer stamps and the buffer index |

## Natives

20 bound (`soa --list-native | grep particles:`). Live check: `soa --live-check particles[:every=N][:budget=N][:only=..][:out=FILE]`
(default every=16; [`particles_check.h`](particles_check.h): shadow checks, the guest original on a private
World built from what the native saw, its callees stubbed and answered from the native's record).

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `ParticleManager::Handler` (+ the INotify thunk `_ZThn4080_`) | `particles_manager.cpp` | `particles/handler` (400 messages: one emitter or lists, times with NaNs / infinities, locks other than 1) | shadow: the emitters as the native found them (time, last time, the lock its release saw), the clock moved on per emitter; Simulate calls (dt bits) and the emitters' state |
| `ParticleManager::RunLow` | `particles_manager.cpp` | `particles/run-low` (600 random worlds), `particles/run-low-full` (over 0x800 emitters) | shadow: the list as found under m_cs (after the Prepares), the locks as its compare-and-swaps found them; the calls (GetDt, Prepare, SkipThisFrame, IsBufferReady, the posts), the lists and the emitters where it leaves m_cs |
| `ParticleManager::RunAfterRendering` | `particles_manager.cpp` | `particles/run-after-rendering` | shadow, as RunLow's |
| `ParticleManager::DispatchEmitters` | `particles_manager.cpp` | `particles/dispatch-emitters` (counts below / at / over the live worker count) | shadow: the posts |
| `ParticleManager::DispatchEmitter` / `Kick` / `Tick` | `particles_manager.cpp` | `particles/one-emitter` | shadow: one emitter |
| `ParticleManager::Run` (+ the Task thunk `_ZThn40_`) | `particles_check.cpp` (through RunLow's / RunAfterRendering's hooks) | `particles/run` (the levels; RunLow / RunAfterRendering run) | the guest's Run with RunLow / RunAfterRendering stubbed: the one it calls |
| `ParticleManager::Add` / `Delete` | `particles_manager.cpp` | `particles/list` | shadow: the links of the nodes around the element |
| `IParticleEmitter::SkipThisFrame` / `IsEmitting` / `GetActiveNumberOfParticles`, `ParticleRenderableBase::IsBufferReady`, `ParticleManager::GetClassID` / `GetDefaultLevel` (+ Task thunks) | `particles_manager.cpp` | `particles/getters` | getter (the original on the same object, a rerun for races) |

The manager's outgoing calls go through [`particles_calls.h`](particles_calls.h) (a thread's Recorder sees
them: recorded in a live check, scripted in the tests); the shared World / guest-run helpers are in
[`particles_world.cpp`](particles_world.cpp).

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `kernel`: TaskManager (the manager's base), Task, INotify, MessageDispatcherBlock, SimpleMessageDispatcher's
  PostMessage forms (called as members), Global::m_pMessageDispatcher / m_pVSync (kernel's addresses).
- `sync`: CriticalSection (Enter / Leave as members), Event (Wait), FastCriticalSection.
- `render`: HierarchicalObject (IParticleEmitter's base), RenderableObject (ParticleRenderableBase's base).
- Upwards (callbacks): the emitters' virtual Prepare (slot 45) and Simulate (slot 51, the 74
  ParticleEmitter<FeatureList<...>> instantiations), through the guest vtable.

## RE notes

- **The dispatch protocol.** An emitter is dispatched for one Simulate by a compare-and-swap of its
  m_dispatchLock (0x1a0) from 0 to 1 that gives up when it isn't 0 (RunLow, DispatchEmitter, Kick, Tick,
  RunAfterRendering), clearing m_idle (0x19c); the worker's Handler sets m_idle and puts the lock back to 0
  only from 1. Tick takes the lock and simulates on the calling thread but never releases it (a game quirk,
  kept). m_inFlight (0x1098) counts the dispatched emitters; RunLow starts a new round only when it is <= 0.
- **Handler's dt** is `m_time - m_lastTime` clamped with FMIN to 1/30 s (`kMaxSimulateDt`): a NaN
  propagates (armf::min).
- **RunAfterRendering's frame slots**: it stores m_fillFrame at `m_frameSlots[m_frameSlots[1]]` (the second
  slot doubles as the index), takes slot 0 as m_drawnFrame and clears both (kept as the guest does it).
- **DispatchEmitters** splits RunLow's list over the dispatcher's workers: W - 1 messages 0x29a + i of n / W
  emitters (none when n < W), the rest (m_dispatchCount read again) in message 0x29a + W - 1.
- **Delete** of an element that isn't linked (null links) still decrements the count (not below 0).
