# `kernel`: tasks, fibers, the message dispatcher, the app loop

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/kernel/scope.txt`](../../../decomp/kernel/scope.txt).
- Decompiles and the function list: [`port/decomp/kernel/`](../../../decomp/kernel/) (`symbols.tsv`; `tools/decomp.sh --into kernel/<topic>`).
- Types: [`kernel_layout.h`](kernel_layout.h); for Ghidra, `tools/subsystem.py export-types kernel` -> `port/decomp/kernel/types.json`.
- Build settings of its own (a host library, a definition): [`subsystem.cmake`](subsystem.cmake).

## Types (classes with their methods attached)

Type recovery a wave ahead of the code (port/REBUILD-QUEUE.md: kernel is wave 4). Layouts are proven
by the layout tests in [`kernel_layout_test.cpp`](kernel_layout_test.cpp) (`soa --selftest kernel/`,
all 9 pass): private objects built with the guest's own constructors (or the construction the guest
inlines, step by step with the guest's member constructors) and driven by the guest's methods, or the
running game's objects walked read-only (structural fields only), their fields read through these
classes and compared with the guest's accessors and with what the test did.

| Class (guest) | Guest size | Found from | Proven by (kernel/layout-...) | Status |
|---|---|---|---|---|
| `SimpleMessageDispatcher` (Aska) | 0x1d0 (operator new in Global::InstantiateMessageDispatcher) | the inlined ctor there, Initialize, Setup, AllocateWorkerThreadList, Clear, AddMessage, Post* / Send*, GetMessage, Suspend / Resume, DeleteMessage, dtor | `-message-dispatcher` (private, no workers: Setup's blocks and free queue, 4 Post forms' fields and priority order, GetMessage's copy and the free-queue return, the sync-end hold, Suspend, DeleteMessage, dtor), `-live-dispatcher` | typed |
| `MessageDispatcher` (Aska) | 0x1d0 | Instantiate (the vtable swap), its 4-byte Initialize / Release | `-live-dispatcher` (vtable) | typed (adds no fields) |
| `MessageDispatcherBlock` (Aska) | 0x50 | Post* writers, worker Handler, GetMessage's memcpy | `-message-dispatcher` | typed; +0x04, +0x24 unknown |
| `MessageDispatcherBlockForList` (Aska) | 0x70 | Setup (n * 0x70), AddMessage | `-message-dispatcher`, `-live-dispatcher` (every block's vtable) | typed |
| `MessageBlockList` (Aska::TList<MessageDispatcherBlockForList>) | 0x80 | the inlined ctor, AddMessage, GetMessage, DeleteMessage | `-message-dispatcher` (walk, count at +0x78) | typed |
| `WorkerThread` (Aska::SimpleMessageDispatcher::_WorkerThread) | 0xe0 (new[] n * 0xe0 + 8) | AllocateWorkerThreadList, Handler, GetMessage, MessageReady, Exit | `-live-dispatcher` (vtable, owner, index, started, pthread, new[] cookie) | typed; +0x10, +0x85 unknown |
| `INotify` (Aska) | vtable only | DeleteEndNotify's vtable, the worker's call | (interface) | slot constants |
| `Task` (Aska) | 0x28 | the inlined ctor (WaitVSync::Instantiate, CMainTask, TaskManager), ~Task, ChangeLevel, TaskManager::Add | `-task-manager` (Add: owner, level, links) | typed; +0x25..0x27 unknown |
| `TaskManager` (Aska) | 0xff0 (operator new in Global) | ctor, dtor, Add, Delete, GetTotalTaskNumber, OwnersKickTask, MakeTaskList, barriers, end notifies, MergeManager, SetupMessageQueue | `-task-manager` (private: ctor fields, Add counts / links, barriers, end notifies, Delete, dtor), `-live-tasks` (vtables, ring, task list) | typed; +0xf0, +0x104 unknown |
| `TaskEndNotify` | 0x18 | CreateEndNotifyList, AddEndNotify | `-task-manager` | typed |
| `CFiberUnit` (Framework) | 0x38 | ctor, accessors, Attach / Detach / Destroy, Progress | `-fiber` (private: handles, priority, Create, the chain order, status transitions, Group, pSearchByHandle, Destroy), `-live-tasks` (the root kernel's chain) | typed; +0x18 unknown |
| `CFiberKernel` (Framework) | 0x50 (operator new in CApplication) | ctor, Initialize, Attach, Detach, Progress, Create / Destroy | `-fiber`, `-live-tasks` | typed; +0x48 unknown |
| `CMainTask` (Framework::CApplication) | 0xf8 (InitializeMainTask) | ctor, the r* accessors | `-live-tasks` (every accessor vs its field, owner = system task manager) | partial: 0x28, 0x68..0x8f, 0xa0..0xd7, 0xe8..0xf7 unknown |
| `PerformanceCounter` (Aska) | 0x260 (Instantiate) | ctor, Mark, Set | `-performance-counter` (private + live) | typed |
| `CTimeElement` (Framework) | 0x48 | ctor, Initialize, Add, AddChild, DetachFromParent, setters | `-time-element` (tree links, Add's scaled dt down the tree, Suspend, Interpose, DetailRate) | typed; base = containers' THierarchy |
| `NotifierThread` (Aska) + `NotifyElement` | 0xb8 / 0x28 | ctor, AddNotify, Notify, RemoveNotify, QueryNotify | `-notifier-thread` (private), `-live-vsync` (VSync's) | typed |
| `EventNotify` (Aska) | 0x10 | GPUSync::WaitGPUSync's stack object | `kernel/gpu-sync` | typed |
| `GPUSync` (Aska) | 0xd8 | WaitGPUSync, Notify, the destructors (`gpu_sync.c`) | `kernel/gpu-sync` | typed, native |
| `VSync` (Aska) | >= 0x160 | ctor, Initialize, UpdateDt / CalcDtAndDFrame, GetDt | `-live-vsync` (vtables, frame rate, GetDt, the counter) | partial: size not confirmed |
| `Global` (Aska) | statics | `nm -DCS`, Instantiate* | (addresses used by the live tests) | `kVaddrGlobal*` constants |
| not recovered | | | | `CMessageManager`, `ResponderChain::CManager`, `LifeCycleManager`, `AskaMainThread`, `TaskThread` / `TaskThreadManager` (multi-threaded task managers), `WaitVSync` / `WaitDraw` (Tasks: 0x40 with a bool at +0x38), `CApplication::CAskaAppWithoutAPE`, `AndroidUtil`, `Platform::Android` |

## Natives

43 bound (`soa --list-native | grep kernel:`). Live check: `soa --live-check kernel[:every=N][:out=FILE]`
(default every=16; `kernel_check.h`: shadow replays as sync's, `common/shadow_check.h`).

| Class::Method (guest symbol) | File | Differential tests | Live check |
|---|---|---|---|
| `SimpleMessageDispatcher::PostMessage` (4 forms), `PostSyncMessageSingle` / `End` (2 each) | `kernel_dispatcher.cpp` | `kernel/dispatcher-sequence` | shadow replay (dispatcher, workers, blocks; the wake pass) |
| `SimpleMessageDispatcher::SendMessage` / `SendMessageHigh` (4 each) | `kernel_dispatcher.cpp` | `kernel/dispatcher-sequence` (the guest's Event::Wait stubbed) | shadow replay (the replay's Event::Wait doesn't block: `sync::t_replay_no_wait`) |
| `SimpleMessageDispatcher::GetMessage(block, int)` | `kernel_dispatcher.cpp` | `kernel/dispatcher-sequence` | inside the worker's (the shadow's vtable slot 2 = the guest original) |
| `_WorkerThread::GetMessage`, `_WorkerThread::MessageReady` | `kernel_dispatcher.cpp` | `kernel/dispatcher-sequence` | shadow replay |
| `AddMessage`, `AddMessageToFront`, `DeleteMessage`, `CancelMessage` | `kernel_dispatcher.cpp` | `kernel/dispatcher-sequence` | shadow replay |
| `SuspendWorkerThread`, `ResumeWorkerThread`, `WakeupWorkerThread`, `WakeupAllWorkerThreads` | `kernel_dispatcher.cpp` | `kernel/dispatcher-sequence` | shadow replay (wake passes) |
| `IsWorkerThreadSuspended` | `kernel_dispatcher_check.cpp` | `kernel/dispatcher-sequence` | - (8 bytes, no trampoline) |
| `TaskManager::Add` / `DeleteThreadBarrier`, `Increment` / `DecrementThreadBarrierCount` | `kernel_task.cpp` | `kernel/task-barriers` | shadow replay (barrier state) |
| `TaskManager::MakeTaskList`, `GetTotalTaskNumber` | `kernel_task.cpp` | `kernel/task-list` (a merged ring of 3) | run-both on the real manager / getter |
| `PerformanceCounter::Mark` / `Set` (2) / `AddSet`, `Global::GetCPUTime` | `kernel_timing.cpp` | `kernel/clock-readers` | bracketed by the guest before and after |
| `VSync::GetDt` | `kernel_timing.cpp` | `kernel/vsync-getdt` | getter (s0) |
| `CTimeElement::Add` | `kernel_timing.cpp` | `kernel/time-element-add` (random trees, NaNs) | run-both on the tree |
| `GPUSync::WaitGPUSync`, `GPUSync::Notify` | `kernel_gpu_sync.cpp` | `kernel/gpu-sync` | none (runs handlers / blocks on another thread: not replayable) |

Live coverage (story, battle-gacha, battle-gacha on software GL; 226,759 checks, 0 mismatches, 45 races):
the Post / PostSync / SendMessage forms the flows use, worker GetMessage (with GetMessage(block, int)
inside it), MessageReady, Suspend / Resume, Delete / DecrementThreadBarrier, MakeTaskList,
GetTotalTaskNumber, PerformanceCounter Mark / Set, GetCPUTime, GetDt, CTimeElement::Add. Not reached
live in these flows (covered by the differential tests only): AddMessage / ToFront, Delete / Cancel
Message, the Wakeup* passes, Set(int, long), AddSet, the Send / SendHigh variants other than
SendMessage(msg, notify, a0, a1, prio), Add / IncrementThreadBarrierCount (the native Post* call them
as members; only guest callers reach their hooks). CTimeElement::Add's live replay recurses into
siblings through the patched entry (natively): the live check proves a node and its first-child chain,
`kernel/time-element-add` the sibling branches.

Not bound (left to the guest, mixed locking on the same lock word is safe): `PostMultiMessages` (4),
`PostSyncMessages` (2) (not executed in the four flows), `Setup`, `Clear`, `AllocateWorkerThreadList` (2),
`Initialize`, the destructors, `CheckToDispatch` (8 bytes; GetMessage skips the call when the slot is
it), `_WorkerThread::Handler` (the worker's main loop: its exit is `Thread::Exit` -> `pthread_exit`,
which halts the guest CPU at its JIT level; it never touches the lock), `TaskManager::OwnersKickTask`
and the rest of TaskManager / CFiberKernel / NotifierThread.

## Dependencies

Subsystems whose types or functions this one uses (port/REBUILD-QUEUE.md has the measured call edges):
- `sync` (11,870 samples): Aska::Event (0x68), Semaphore (0x18), CriticalSection (0x28),
  FastCriticalSection (0x90), Thread (0x10) are embedded everywhere (the dispatcher's lock at +0x08 and
  event at +0x148, the workers' wake-up events, the task manager's 32 barrier events, its two locks,
  the notifier's semaphores): `kernel_layout.h` uses sync's classes (`using Event = sync::Event;` ...),
  and the natives call their members (`FastCriticalSection::Enter` / `Leave`, `Event::Set`, ...).
- `memory` (1,384): `memory::TDynamicQueue<T>` (the dispatcher's free-block queue); DeleteManager
  (Task::DeleteThis*); blocks / task lists come from `operator new[]`.
- `containers`: `LinkElement` (dispatcher blocks, tasks, notify elements), `TList<LinkElement>`
  (NotifierThread's list), `TPoolFast<T>` (the notifier's pool), `THierarchy<T>` (CTimeElement's base).
  Note for containers: `TList<T>` embeds a whole `T` as its sentinel; containers_layout.h's `TList<T>`
  (sentinel `LinkElement`, count at +0x20) is right for `TList<LinkElement>` only: the dispatcher's
  `TList<MessageDispatcherBlockForList>` has its count at +0x78 (`MessageBlockList` here).
- `math` (376): none of its types embedded here.
- Co-developed, same level: `resource` (kernel -> resource 18,512 samples: CMainTask holds
  `Framework::CResourceManager*` at +0x60; the dispatcher runs resource's decode / read jobs through
  INotify), `input` (5,510: Aska::Global::GetPeripheral / GetActivePad / RegisterPeripheral return the
  peripherals: `Aska::BasePeripheral*`, input's). Those subsystems hold kernel's types as pointers:
  `Aska::INotify` (vtable slot 0 Handler(u64)), `Aska::Task` (0x28), `Aska::TaskManager` (0xff0),
  `Aska::MessageDispatcherBlock` (0x50: what a dispatcher job's Handler receives).
- Upwards (callbacks, interfaces only): `Task` slot 13 Run(int level) (every system's per-frame task:
  scene 65,870 samples, info, ui, battle), `INotify` slot 0 Handler(u64) (the dispatcher's jobs: scene's
  object-manager jobs, dynamics, resource), `CFiberUnit` slot 5 Progress (the client's phases / scenes),
  TaskManager end notifications (INotify slot 0 with the registered arg).

## RE notes

- **The dispatcher.** One Aska::MessageDispatcher (Global::m_pMessageDispatcher), built in
  Global::InstantiateMessageDispatcher: Setup(app+0x88 blocks, priority 0x80), then
  max(1, min(cores - 2, 256)) workers "Aska::DynamicsWorker" (priority 0xb, core 6, stack 0x20000).
  The queue is a list of 0x70-byte blocks ordered by descending priority (FIFO within one); free blocks
  live in a TDynamicQueue ring of capacity n + 1; when it is empty, Post* sets m_full, Resets
  m_freeBlockEvent and fails. Every operation takes the FastCriticalSection at +0x08 (spin up to 0x200
  times on the lock word, then the semaphore): **this spin is most of the dispatcher's 6.7% guest self
  time** (`_WorkerThread::GetMessage` 7,540 samples, `MessageReady` 4,118, `SuspendWorkerThread` 1,254,
  the Post* forms ~1,100 each: all workers contend on one lock). A host native over a host mutex /
  condition variable is the win here, but it must cover the whole family (every Post* / Send* /
  GetMessage / MessageReady / Suspend / Resume / Delete / Cancel and the worker's Handler) because
  they share the lock and the queue.
- **Workers.** Handler: Event::Wait(m_wakeup); while GetMessage(&m_current): m_notify->Handler(block)
  (INotify slot 0), atomic --*m_counter, Set(*m_event) if the message had 0x8000, release the task
  barrier (TaskManager::DecrementThreadBarrierCount + DeleteThreadBarrier) if m_barrierManager, then
  MessageReady (clears m_busy and the worker's keys; wakes other waiting workers when the finished
  message was exclusive). GetMessage(block, index) (vtable slot 2) skips messages whose non-zero
  m_key0 / m_key1 equals a key another busy worker holds, or 0xffffffff while any worker is busy
  (exclusive jobs), and kFlagWaitCounter (0x4000) messages until *m_counter is 0 (PostSyncMessageEnd:
  "after all the PostSyncMessageSingle jobs of this counter"); otherwise asks CheckToDispatch (slot 3,
  always true here).
- **Send\*** waits: it takes an Event from Global::m_pEventPool (or a stack one), posts with 0x8000 and
  m_event, then waits; SendMessageHigh / AddMessageToFront use priority 0x7f.
- **Tasks.** TaskManager::OwnersKickTask (the system manager, once per frame from CMainTask / the main
  thread): refresh barriers, MakeTaskList (gathers every task of the merged ring into m_taskList sorted
  by level bit: counting sort over m_levelCount), then for each task in order call Run(level) (slot 13)
  unless m_flags bit 1, waiting on barrier event level + 1 at each level boundary while its count > 0
  (the dispatcher's Post*(Task*, barrier, ...) jobs of that level), then the end notifications. A task's
  m_level is a bit mask; Add counts one per set bit (m_totalCount = GetTotalTaskNumber).
- **Fibers.** The root CFiberKernel (priority 0x600) is CMainTask::m_rootFiberKernel; units are kept in
  ascending priority; Progress runs every Active unit's slot 5 and deletes units whose Destroy(true)
  was requested. The constructor doesn't clear m_numAttached / m_numActive (Initialize does).
- **Quirks.** SimpleMessageDispatcher::DeleteMessage unlinks the block but doesn't return it to the free
  queue (the block leaks until Setup runs again); DeleteMessage(-1) empties the list without touching
  the count; the serial is compared as a u32 with the u16 field. A Send* form whose stack event can't be
  created and whose event pool is empty returns false with its zeroed block left queued.
  TaskManager::IncrementThreadBarrierCount caps the count at the reference count it read before taking
  m_barrierCs. CFiberKernel::Detach decrements m_numAttached even when the unit isn't in its chain.
  CTimeElement::Add: a suspended node counts its suspension down by dt times its *interpose time* when
  one is set (not the rate); an interposition that ends is cleared down the first-child chain only.
- **Global::GetCPUTime** is CLOCK_BOOTTIME (bionic id 7) in milliseconds, not a CPU time.
- **GPUSync** (from sync's list): a NotifierThread (0xb8) + a pending flag (+0xb8) + a binary semaphore
  (+0xc0). WaitGPUSync registers a stack EventNotify (vtable + Event*), releases the semaphore, waits,
  removes it; without an event it polls the flag with Sleep(1). Notify clears the flag, stamps
  performance counter 2 and runs NotifierThread::Notify under the semaphore.

## For the code agent (hot functions, guest self samples over login + battle + gacha + story = 293,654 busy)

Kernel's self time is 27,602 samples (9.4%), 19,767 of them in SimpleMessageDispatcher (lock spinning):

| Function | Self | Inclusive |
|---|---|---|
| `SimpleMessageDispatcher::_WorkerThread::GetMessage(MessageDispatcherBlock*)` | 7,540 | 8,328 |
| `SimpleMessageDispatcher::_WorkerThread::MessageReady()` | 4,118 | 5,196 |
| `TaskManager::MakeTaskList()` | 1,442 | 1,445 |
| `SimpleMessageDispatcher::SuspendWorkerThread()` | 1,254 | 1,254 |
| `SimpleMessageDispatcher::PostMessage(u16, INotify*, void*, void*, u64, u64, u32*, s8)` | 1,173 | 2,380 |
| `SimpleMessageDispatcher::PostMessage(u16, INotify*, void*, void*, u32*, s8)` | 1,108 | 3,203 |
| `SimpleMessageDispatcher::_WorkerThread::Handler()` | 998 | 36,221 |
| `SimpleMessageDispatcher::PostSyncMessageSingle(u16, int*, INotify*, void*, void*, u32*, s8)` | 995 | 1,806 |
| `SimpleMessageDispatcher::ResumeWorkerThread()` | 995 | 1,039 |
| `SimpleMessageDispatcher::GetMessage(MessageDispatcherBlock*, int)` | 722 | 763 |
| `TaskManager::GetTotalTaskNumber() const` | 591 | 591 |
| `TaskManager::OwnersKickTask()` | 560 | 140,341 |
| `SimpleMessageDispatcher::SendMessage(u16, INotify*, void*, void*, u64, u64, s8)` | 361 | 1,460 |
| `SimpleMessageDispatcher::PostSyncMessageEnd(...u64, u64...)` | 316 | 413 |
| `Framework::CFiberKernel::Progress()` | 297 | 83,166 |
| `Aska::Global::GetCPUTime()` | 269 | 357 |
| `Framework::CApplication::CMainTask::Run(int)` | 253 | 97,573 |
| `VSync::UpdateVSyncEvents`, `PerformanceCounter::Set` / `Mark`, `CTimeElement::Add(float)`, `VSync::GetDt` | 197 / 155 / 105 / 135 / 125 | |

Suggested order: (1) the dispatcher family as one unit (all of SimpleMessageDispatcher + _WorkerThread,
on a host lock; they share the queue and the FastCriticalSection, which is sync's: coordinate with
n-sync's FastCriticalSection native), (2) TaskManager's MakeTaskList / GetTotalTaskNumber / the
barriers (with Add / Delete / ChangeLevel: one lock), (3) the small pure leaves (PerformanceCounter
Mark / Set, CTimeElement::Add, VSync::GetDt / UpdateDt, Global::GetCPUTime) with differential tests.

## Unknowns

- MessageDispatcherBlock +0x04 / +0x24, _WorkerThread +0x10 / +0x85, Task +0x25..+0x27, TaskManager +0xf0 /
  +0x104, CFiberUnit +0x18 (cleared by Create), CFiberKernel +0x48, CMainTask's middle (0x68..0x8f,
  0xa0..0xd7), VSync's size and +0x13c..+0x143 / +0x15c.
- Not recovered: CMessageManager (Deliver 39 samples), ResponderChain::CManager / CResponder,
  LifeCycleManager, AskaMainThread, TaskThread / TaskThreadManager (decompiled in task.c, not typed),
  CApplication::CAskaAppWithoutAPE, Aska::App (Global::m_pApp: +0x88 = the dispatcher's block count).
