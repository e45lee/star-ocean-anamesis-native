# `sync`: mutexes, events, semaphores, threads

A subsystem of the native rebuild (port/PLAN.md task 6). The workflow (decompile, types, natives,
tests, Ghidra types): port/src/native/README.md "Per-subsystem workflow".

- Scope: the demangled-name patterns in [`port/decomp/sync/scope.txt`](../../../decomp/sync/scope.txt):
  `Framework::CMutex`, `Framework::CThread`, `Aska::{Event, Semaphore, Thread, Mutex, CriticalSection,
  FastCriticalSection}`. Not here: `Aska::GPUSync` (a `NotifierThread`: kernel's) and
  `Aska::StateCacheThreadSafe` (render's GL state cache), which the queue's first proposal had in sync.
- Decompiles and the function list: [`port/decomp/sync/`](../../../decomp/sync/) (`mutex.c`, `event.c`,
  `thread.c`, `symbols.tsv`).
- Types: [`sync_layout.h`](sync_layout.h); for Ghidra, `tools/subsystem.py export-types sync` ->
  `port/decomp/sync/types.json`.
- The public contract for later waves: `sync_layout.h`'s classes and their members. `memory`'s
  `TFixedLengthAllocator<N>::pAllocate / Free` and `CFixedLengthAllocatorContainer::Free` are where
  most `CMutex::Lock / Unlock` calls come from; their natives call `CMutex::Lock()` / `Unlock()`
  directly, and code that inlines a `FastCriticalSection` uses its `Enter()` / `Leave()`.

## Design

The objects live in guest memory and guest code reads them, so **the guest layout is the state**:
the natives keep every field where the guest keeps it and change it the way the guest does. No
second mechanism:

- `Framework::CMutex` / `Aska::FastCriticalSection`: the guest's own algorithm on the guest's words
  (lock word -1 free / 0 held, the waiter count biased by 20, the recursion count, the owner), with
  host atomics instead of LL/SC loops. The JIT's exclusive store is a host compare-and-swap on the
  word (`runtime/src/core/cpu.cpp` `MemoryWriteExclusive*`, `fastmem_exclusive_access`), so guest code
  that still enters the same `FastCriticalSection` inline (other subsystems) and these natives
  exclude each other correctly (`sync/cmutex-contention` mixes them on one mutex).
- `Aska::Event`, `Aska::CriticalSection`: the bionic pthread mutex / condition variable embedded in
  the object, through the HLE layer's host calls (`runtime/src/hle/thread.h` `hle_mutex_*`,
  `hle_cond_*`): the same host objects in place and the same rules as the guest's pthread imports
  (bionic's static initializers, winpthreads' zero objects, the window thread's sliced wait for
  idle presenting).
- `Aska::Semaphore`: the HLE's side table of host semaphores keyed by the guest `sem_t`'s address
  (`hle_host_sem_init / destroy`, `hle_sem_*`), the one the guest's `sem_*` imports reach.
- Blocking calls are wrapped in `ProfNativeWait`, so the profiler counts them as waiting.

## Types (classes with their methods attached)

| Class | Guest size | Found from (ctor, decompile) | Status |
|---|---|---|---|
| `Semaphore` (Aska) | 0x18 | `Create`: `sem_init(&m_sem)`, `m_pSem = &m_sem` (`event.c`) | typed, native |
| `Event` (Aska) | 0x68 | `Create`: mutex @8, cond @0x30, flags @0x60 / 0x61; GPUSync's 104-byte stack Event (`event.c`) | typed, native |
| `CriticalSection` (Aska) | 0x28 | its ctor: a recursive pthread mutex in place | typed, native |
| `Mutex` (Aska) | 0x20 | its ctor: `Semaphore` @8, `Create(1, 1)` | typed, native |
| `FastCriticalSection` (Aska) | 0x90 | its ctor (`m_lock` @0x38, `m_waiters` @0x3c, `m_sem` @0x78) and CMutex's inlined enter / leave (`mutex.c`) | typed, native |
| `Thread` (Aska) | 0x10 | its ctor and `Create` (`m_thread` @8) (`thread.c`) | typed, native (part) |
| `CMutex` (Framework) | 0xb0 | `Initialize` / `Lock` / `Unlock` (`mutex.c`) | typed, native |
| `CSubstance` (Framework::CThread) | 0x20 | its ctor and `Handler` (`thread.c`) | typed |
| `CThread` (Framework) | 0x40 | its ctor, `Create`, `Resume`, `TerminateCallback` (`thread.c`) | typed |

## Natives

45 bound (`soa --list-native | grep sync:`). Live check: `soa --live-check sync[:every=N][:out=FILE]`
(default every=16; `sync_check.h`).

| Class::Method | File | Differential tests | Live check |
|---|---|---|---|
| `CMutex::Lock` / `Unlock` | `sync_mutex.cpp` | `sync/cmutex-sequence`, `sync/cmutex-contention` | shadow replay (bytes, waiter hand-off, wakeup) |
| `CMutex::Initialize` | `sync_mutex.cpp` | `sync/cmutex-sequence` | shadow replay (bytes) |
| `CMutex::IsLocked` / `IsInitialized` / `LockCounter` | `sync_mutex.cpp` | `sync/cmutex-sequence` | getter (guest on the real object) |
| `CMutex` ctor / `~CMutex` (D2, D0) / `Release` / `rSubstance` / `crSubstance` | `sync_mutex.cpp` | `sync/cmutex-sequence` | - |
| `FastCriticalSection` ctor / dtor | `sync_mutex.cpp` | `sync/fast-critical-section-ctor` | (inside CMutex::Initialize's) |
| `Event::Create` | `sync_event.cpp` | `sync/event-sequence` | shadow replay |
| `Event::Wait` / `Set` / `Reset` | `sync_event.cpp` | `sync/event-sequence`, `sync/event-wakeup-interop` | shadow replay (Wait: when signaled; a Wait that waits is skipped) |
| `Event::IsSignal` / ctor / `Exit` | `sync_event.cpp` | `sync/event-sequence` | - (IsSignal: no trampoline, a branch in its first 8 bytes) |
| `CriticalSection` ctor / `TryEnter` | `sync_event.cpp` | `sync/critical-section` | - (TryEnter: no trampoline) |
| `Semaphore::Create` | `sync_semaphore.cpp` | `sync/semaphore-sequence` | shadow replay |
| `Semaphore::IsReady` | `sync_semaphore.cpp` | `sync/semaphore-sequence` | getter |
| `Semaphore` ctor / dtor / `Exit` / `Wait` / `WaitNonBlocking` / `Polling` / `Signal` / `Signal_Legacy` | `sync_semaphore.cpp` | `sync/semaphore-sequence`, `sync/semaphore-wakeup-interop` | - (no guest-visible state; Polling: no trampoline) |
| `Mutex` ctor / dtor / `Lock` / `TryLock` / `Unlock` | `sync_semaphore.cpp` | `sync/mutex-binary-semaphore` | - |
| `Thread` ctor / dtor (D2, D0) / `WaitEnd` / `Delete` / `Sleep` / `SleepU` | `sync_thread.cpp` | `sync/thread-members`, `sync/thread-sleep`, `sync/thread-join` | - |

Not bound:
- 4-byte tail calls (the patch is 8 bytes): `CriticalSection::~CriticalSection / Delete / Enter /
  Leave`, `Event::~Event`, `Thread::GetCurrentID / Switch / Handler / CreateThreadKey /
  DeleteSignalHandler`, `CThread::~CThread` (D0, a trap).
- `Thread::Create` and the priority functions (`ConvertTo*Priority`, `Get/SetPriority`,
  `PosixInitThreadPriority`): 7 samples in four flows; they need an HLE thread-create export,
  `getrlimit(RLIMIT_NICE)` (stubbed on Windows) and a float constant (0x28014f8) not recovered.
- `Thread::Main` (every Aska thread's entry: a native would add a JIT level per thread and break the
  profiler's thread naming), `Thread::Exit` (`pthread_exit` halts the guest CPU in the HLE),
  `Thread::InitializeThreadSystem` (once).
- `Framework::CThread` / `CSubstance`: none of it runs in the profiled flows; types only.

The live check: `sync_check.h` (why the record / replay check of `live_check.h` can't run sync
primitives, and the shadow replay that does).

## Measurements

The login and battle flows (REBUILD-QUEUE.md's scripts, `SOA_PROFILE` at 1000 Hz), main's binary
(before) and this branch (after) run side by side on the same machine load, 2026-10-04:

| Flow | Busy samples before -> after | sync guest self before -> after | Guest JIT | Native | HLE working |
|---|---|---|---|---|---|
| login | 48,605 -> 40,832 (-16.0%) | 4,851 (10.0%) -> 32 (0.08%) | 39,262 -> 32,303 | 659 -> 3,829 | 8,681 -> 4,694 |
| battle | 115,771 -> 108,888 (-5.9%) | 7,629 (6.6%) -> 43 (0.04%) | 94,290 -> 87,053 | 900 -> 9,427 | 20,566 -> 12,396 |

`CMutex::Lock / Unlock` (79% of sync's guest time, mostly the memory subsystem's fixed-length
allocators) cost 42 + 42 native samples in the battle run instead of ~6,000 guest ones. The native
column grows because the host calls the guest made through HLE thunks now run inside the natives:
`Event::Set`'s `pthread_cond_signal` (a futex wake, ~6,700 samples: the guest's
`[hle]pthread_cond_signal` was 6,011) and `Semaphore::Signal`'s `sem_post`. What's left of sync's
guest time: `GPUSync` (kernel's) and the getters without a trampoline. Frame rate: no measurable change
(both runs at the 60 fps cap in steady state; the 10-second `I/perf` samples in loading and on a
shared machine are too noisy to show more).

## Dependencies

None below it (level 1). Calls up: `Framework::gDoAssert` (Mutex.cpp's asserts, guest code) and
`operator delete` (`_ZdlPv`, guest code) by the deleting destructors.

## RE notes

- `FastCriticalSection`'s waiter count starts at 20 (`kWaiterBias`); `Leave` hands a wakeup to the
  semaphore when it is above 20 (`cmp w9, #0x15; b.lt`), taking one off; the woken waiter adds it
  back. A waiter that gets the lock word between that hand-off and its `sem_wait` leaves the post for
  a later waiter, so at rest `m_waiters + pending posts == 20`, not always `m_waiters == 20`
  (`sync/cmutex-contention` checks the sum).
- `CMutex::Lock` reads `m_owner` before acquiring (an unlocked read: only the owner can make it
  equal to itself) and calls `Aska::Thread::GetCurrentID` (pthread_self) twice.
- `Event::Wait(ms)` returns `pthread_mutex_unlock(...) != 0`: false on success, timeout or not. The
  timed path builds `tv_nsec = (u32)(ms * 1000000) + usec * 1000` without carrying into `tv_sec`: from
  about 1 s on (and in the last `ms` of any second) it is >= 1e9, and `pthread_cond_timedwait` fails
  with EINVAL at once instead of waiting (bionic's and glibc's check). It doesn't loop on spurious wakeups, and an auto-reset
  event is cleared after a timeout too. Kept as is (`sync/event-sequence`).
- `Event::Create(manualReset, initialState)`: the first bool is +0x61, the second +0x60.
- `Semaphore::Create(initial, max)` ignores `max`; `Signal_Legacy` returns the guest `sem_t`'s first
  word, which the HLE never writes (its semaphores are host objects aside).
- `Thread::Sleep(ms)` multiplies `ms * 1000` in 32 bits (wraps from 4294968 ms on).
- **Windows (fixed in the HLE, `hle_mutex_init`):** bionic numbers the mutex types 0 normal,
  1 recursive, 2 errorcheck (glibc the same); winpthreads has 1 errorcheck, 2 recursive. The HLE
  passed bionic's number through, so on Windows every guest recursive mutex
  (`Aska::CriticalSection`, ...) was an errorcheck one (a recursive enter failed with EDEADLK without
  locking) and errorcheck ones were recursive. `host_mutex_type` maps them now.
- **Windows (fixed in the HLE, `hle_cond_timedwait`):** the guest's timespec has a 64-bit `tv_nsec`;
  winpthreads read its low 32 bits, so `Event::Wait(1000..2147)` waited (carried into seconds) where
  bionic returns EINVAL, and from about 2148 ms on the low half is negative and the wait never ended
  (found by `sync/event-sequence` on Windows). The HLE now refuses a `tv_nsec` outside [0, 1e9) with
  EINVAL on both platforms, as bionic does, and passes a host timespec.
