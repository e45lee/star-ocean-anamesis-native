// sync_layout.h: the guest data layouts of the `sync` subsystem (mutexes, events, semaphores, threads).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/sync/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types sync` turns the structs into port/decomp/sync/types.json for Ghidra.
//
// The objects live in guest memory and guest code reads their fields (CMutex::IsLocked, the inline
// FastCriticalSection users of other subsystems), so the guest layout is the state: the natives keep
// every field where the guest keeps it and change it the way the guest does (README.md "Design").
// The host objects behind the bionic pthread / semaphore objects embedded here are the HLE layer's
// (runtime/include/soaruntime/hle/thread.h): glibc / winpthreads mutexes and condition variables in place, host
// semaphores in the HLE's side table keyed by the guest sem_t's address.
//
// Members a guest method declares `void` but whose x0 the guest leaves defined by a tail call
// (Semaphore::Wait / Signal: sem_wait's / sem_post's result) return that value here.
#ifndef SOA_NATIVE_SYNC_LAYOUT_H
#define SOA_NATIVE_SYNC_LAYOUT_H

#include <cstddef>
#include <cstdint>

namespace soa::native::sync {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// The guest classes are Aska::* and Framework::*; here they are flat in soa::native::sync (tools/subsystem.py
// matches a struct to its guest methods by the class's short name), each comment naming the guest class.

// Aska::Semaphore: guest size 0x18; layout from Semaphore::Create (port/decomp/sync/event.c):
// sem_init(&m_sem, 0, initial), then m_pSem = &m_sem; every other method works on *m_pSem.
class Semaphore {
public:
    void CtorBase();                  // Aska::Semaphore::Semaphore()          _ZN4Aska9SemaphoreC2Ev
    void Dtor();                      // Aska::Semaphore::~Semaphore()         _ZN4Aska9SemaphoreD1Ev
    void Exit();                      // Aska::Semaphore::Exit()               _ZN4Aska9Semaphore4ExitEv
    bool Create(s32 initial, s32 max);  // Aska::Semaphore::Create(int, int) (max unused)  _ZN4Aska9Semaphore6CreateEii
    s32 Wait() const;                 // Aska::Semaphore::Wait() const         _ZNK4Aska9Semaphore4WaitEv
    bool WaitNonBlocking() const;     // Aska::Semaphore::WaitNonBlocking() const
    bool IsReady() const;             // Aska::Semaphore::IsReady() const
    bool Polling() const;             // Aska::Semaphore::Polling() const      (sem_getvalue > 0)
    s32 Signal() const;               // Aska::Semaphore::Signal() const       _ZNK4Aska9Semaphore6SignalEv
    u32 Signal_Legacy() const;        // Aska::Semaphore::Signal_Legacy() const (the sem_t's first word, then sem_post)

    u64 m_pSem;   // 0x00: guest address of m_sem once Create succeeded, else 0 (Exit / the destructor clear it)
    u8 m_sem[16]; // 0x08: bionic sem_t (the HLE keeps the host semaphore aside, keyed by this address)
};
static_assert(offsetof(Semaphore, m_pSem) == 0x00);
static_assert(offsetof(Semaphore, m_sem) == 0x08);
static_assert(sizeof(Semaphore) == 0x18);

// Aska::Event: guest size 0x68 (GPUSync::WaitGPUSync's stack Event: 104 bytes); layout from
// Event::Create (port/decomp/sync/event.c): pthread_mutex_init(&m_mutex), pthread_cond_init(&m_cond),
// m_pMutex = &m_mutex, m_signaled = second argument, m_manualReset = first argument.
class Event {
public:
    void Ctor();                       // Aska::Event::Event()                  _ZN4Aska5EventC1Ev
    bool Create(bool manualReset, bool initialState);  // Aska::Event::Create(bool, bool)  _ZN4Aska5Event6CreateEbb
    bool Wait(u32 timeoutMs) const;    // Aska::Event::Wait(unsigned int) const (true only when the unlock failed)
    bool Set() const;                  // Aska::Event::Set() const
    bool Reset() const;                // Aska::Event::Reset() const
    bool IsSignal() const;             // Aska::Event::IsSignal() const
    void Exit();                       // Aska::Event::Exit() (also ~Event, a 4-byte tail call: not bound)

    u64 m_pMutex;        // 0x00: guest address of m_mutex once created, else 0 (the methods lock *m_pMutex)
    u8 m_mutex[40];      // 0x08: bionic pthread_mutex_t (a glibc / winpthreads mutex in place: HLE)
    u8 m_cond[48];       // 0x30: bionic pthread_cond_t (in place: HLE)
    u8 m_signaled;       // 0x60
    u8 m_manualReset;    // 0x61: a successful Wait leaves m_signaled set (else it clears it)
    u8 unk_62[6];        // 0x62: (alignment)
};
static_assert(offsetof(Event, m_pMutex) == 0x00);
static_assert(offsetof(Event, m_mutex) == 0x08);
static_assert(offsetof(Event, m_cond) == 0x30);
static_assert(offsetof(Event, m_signaled) == 0x60);
static_assert(offsetof(Event, m_manualReset) == 0x61);
static_assert(sizeof(Event) == 0x68);

// Aska::CriticalSection: a recursive pthread mutex in place; layout from its constructor
// (pthread_mutexattr_settype(PTHREAD_MUTEX_RECURSIVE), pthread_mutex_init(this)). Enter / Leave /
// Delete / the destructor are 4-byte tail calls into the pthread imports (not bindable: the patch is
// 8 bytes); TryEnter is bound.
class CriticalSection {
public:
    void CtorBase();       // Aska::CriticalSection::CriticalSection()  _ZN4Aska15CriticalSectionC2Ev
    bool TryEnter() const; // Aska::CriticalSection::TryEnter() const   _ZNK4Aska15CriticalSection8TryEnterEv
    void Enter() const;    // Aska::CriticalSection::Enter() const      (pthread_mutex_lock: a 4-byte tail call, not bound)
    void Leave() const;    // Aska::CriticalSection::Leave() const      (pthread_mutex_unlock: likewise)

    u8 m_mutex[40];  // 0x00: bionic pthread_mutex_t (recursive)
};
static_assert(offsetof(CriticalSection, m_mutex) == 0x00);
static_assert(sizeof(CriticalSection) == 0x28);

// Aska::Mutex: a binary semaphore; layout from its constructor (Semaphore at +8, Create(1, 1)).
// The first 8 bytes are never written by its methods.
class Mutex {
public:
    void CtorBase();  // Aska::Mutex::Mutex()    _ZN4Aska5MutexC2Ev
    void DtorBase();  // Aska::Mutex::~Mutex()   _ZN4Aska5MutexD2Ev
    s32 Lock();       // Aska::Mutex::Lock()     (Semaphore::Wait)
    bool TryLock();   // Aska::Mutex::TryLock()  (Semaphore::WaitNonBlocking)
    s32 Unlock();     // Aska::Mutex::Unlock()   (Semaphore::Signal)

    u8 unk_00[8];         // 0x00
    Semaphore m_sem;      // 0x08
};
static_assert(offsetof(Mutex, m_sem) == 0x08);
static_assert(sizeof(Mutex) == 0x20);

// Aska::FastCriticalSection: guest size 0x90 (Framework::CMutex holds one at +0x10, its next field is
// at +0xa0); layout from its constructor (port/decomp/sync/mutex.c: m_lock = -1, m_waiters = 20,
// m_sem.Create(0, 0x7fffffff)) and CMutex::Lock / Unlock, where the enter / leave code is inlined.
// The lock word is -1 when free and 0 when held; m_waiters counts from kWaiterBias: a thread that
// gave up spinning adds one while it waits (on m_sem, or in Sleep(1) when m_sem isn't ready) and the
// leaving thread hands one wakeup to m_sem when the count is above the bias. Enter / Leave aren't
// guest symbols (inlined in CMutex and in other subsystems' code: MemoryManager, ...); they are this
// class's members here so CMutex's natives and later subsystems share one implementation.
class FastCriticalSection {
public:
    static constexpr s32 kFree = -1, kHeld = 0, kWaiterBias = 20, kSpins = 0x200;
    void CtorBase();  // Aska::FastCriticalSection::FastCriticalSection()   _ZN4Aska19FastCriticalSectionC2Ev
    void Dtor();      // Aska::FastCriticalSection::~FastCriticalSection()  _ZN4Aska19FastCriticalSectionD1Ev
    void Enter();     // (inlined in the guest: CMutex::Lock's acquire)
    void Leave();     // (inlined in the guest: CMutex::Unlock's release)

    u8 unk_00[0x38];  // 0x00: never touched by the code read so far
    s32 m_lock;       // 0x38: -1 free, 0 held (guest LL/SC: the JIT's exclusive stores are host CAS)
    s32 m_waiters;    // 0x3c: kWaiterBias + the threads waiting
    u8 unk_40[0x38];  // 0x40
    Semaphore m_sem;  // 0x78: the waiters' wakeups
};
static_assert(offsetof(FastCriticalSection, m_lock) == 0x38);
static_assert(offsetof(FastCriticalSection, m_waiters) == 0x3c);
static_assert(offsetof(FastCriticalSection, m_sem) == 0x78);
static_assert(sizeof(FastCriticalSection) == 0x90);

// Aska::Thread: guest size 0x10; layout from its constructor (vtable, m_thread = 0) and Create
// (m_thread = pthread_create's handle). The thread runs Thread::Main(this), which calls the
// vtable's Handler (slot 2). Create / the priority functions / Main / Exit stay guest code (README).
class Thread {
public:
    void Ctor();           // Aska::Thread::Thread()          _ZN4Aska6ThreadC1Ev
    void DtorBase();       // Aska::Thread::~Thread()         _ZN4Aska6ThreadD2Ev   (joins the thread)
    void DtorDelete();     // Aska::Thread::~Thread()         _ZN4Aska6ThreadD0Ev   (joins, operator delete)
    // vtable: slot 0 / 1 the destructors, slot 2 Handler() (an empty `ret` in the base: not bound)
    s32 WaitEnd();         // Aska::Thread::WaitEnd()         (pthread_join; x0 its result)
    void Delete();         // Aska::Thread::Delete()          (forgets the handle)
    static s32 Sleep(u32 ms);     // Aska::Thread::Sleep(unsigned int)   (nanosleep; x0 its result)
    static s32 SleepU(u32 usec);  // Aska::Thread::SleepU(unsigned int)
    static u64 GetCurrentID();    // Aska::Thread::GetCurrentID(): pthread_self (a 4-byte tail call: not bound)

    const void* vtable;  // 0x00: _ZTVN4Aska6ThreadE + 0x10 (or a derived class's)
    u64 m_thread;        // 0x08: the guest pthread_t (the HLE's host pthread_t), 0 when none
};
static_assert(offsetof(Thread, m_thread) == 0x08);
static_assert(sizeof(Thread) == 0x10);

// Framework::CMutex: guest size 0xb0; layout from CMutex::Initialize / Lock / Unlock
// (port/decomp/sync/mutex.c). A recursive mutex over Aska::FastCriticalSection: the owner and the
// recursion count are kept beside it. Its asserts call Framework::gDoAssert (Mutex.cpp's lines).
class CMutex {
public:
    void Ctor();              // Framework::CMutex::CMutex()        _ZN9Framework6CMutexC1Ev
    void DtorBase();          // Framework::CMutex::~CMutex()       _ZN9Framework6CMutexD2Ev
    void DtorDelete();        // Framework::CMutex::~CMutex()       _ZN9Framework6CMutexD0Ev (+ operator delete)
    // vtable: slot 0 / 1 the destructors, slot 2 IsLocked
    bool IsLocked() const;    // Framework::CMutex::IsLocked() const
    void Release();           // Framework::CMutex::Release()
    void Initialize();        // Framework::CMutex::Initialize()
    bool IsInitialized() const;           // Framework::CMutex::IsInitialized() const
    s32 LockCounter() const;              // Framework::CMutex::LockCounter() const
    FastCriticalSection* rSubstance();               // Framework::CMutex::rSubstance()
    const FastCriticalSection* crSubstance() const;  // Framework::CMutex::crSubstance() const
    void Lock();              // Framework::CMutex::Lock()
    void Unlock();            // Framework::CMutex::Unlock()

    const void* vtable;                     // 0x00: _ZTVN9Framework6CMutexE + 0x10
    u8 unk_08[8];                           // 0x08
    FastCriticalSection m_substance;  // 0x10
    u8 m_initialized;                       // 0xa0: Initialize .. Release
    u8 m_locked;                            // 0xa1: set by Lock, cleared by the last Unlock
    u8 unk_a2[2];                           // 0xa2
    s32 m_lockCount;                        // 0xa4: the owner's recursion depth (LL/SC in the guest)
    u64 m_owner;                            // 0xa8: Aska::Thread::GetCurrentID() of the owner, 0 when free
};
static_assert(offsetof(CMutex, m_substance) == 0x10);
static_assert(offsetof(CMutex, m_initialized) == 0xa0);
static_assert(offsetof(CMutex, m_locked) == 0xa1);
static_assert(offsetof(CMutex, m_lockCount) == 0xa4);
static_assert(offsetof(CMutex, m_owner) == 0xa8);
static_assert(sizeof(CMutex) == 0xb0);

// Framework::CThread::CSubstance: an Aska::Thread whose Handler runs the owning CThread's work;
// guest size 0x20; layout from its constructor and Handler (port/decomp/sync/thread.c). Not bound
// (none of it runs in the profiled flows); recovered for the kernel subsystem.
class CSubstance {
public:
    Thread base;     // 0x00: vtable _ZTVN9Framework7CThread10CSubstanceE + 0x10
    u8 unk_10[8];          // 0x10
    u64 m_pInstance;       // 0x18: the CThread (set by CreateAskaThread / CThread::Create)
};
static_assert(offsetof(CSubstance, m_pInstance) == 0x18);
static_assert(sizeof(CSubstance) == 0x20);

// Framework::CThread: guest size 0x40; layout from its constructor, Create, Resume and
// TerminateCallback (port/decomp/sync/thread.c). Abstract (vtable slot 2 is pure: the work). Not bound.
class CThread {
public:
    const void* vtable;              // 0x00: _ZTVN9Framework7CThreadE + 0x10
    CSubstance m_substance;    // 0x08
    u8 m_isExecuting;                // 0x28: Resume sets it, ToTerminate clears it
    u8 unk_29[7];                    // 0x29
    u64 m_pTerminateCallback;        // 0x30: a Framework::ICallback*, called with (m_terminateArg, this)
    u32 m_terminateArg;              // 0x38
    u8 unk_3c[4];                    // 0x3c
};
static_assert(offsetof(CThread, m_substance) == 0x08);
static_assert(offsetof(CThread, m_isExecuting) == 0x28);
static_assert(offsetof(CThread, m_pTerminateCallback) == 0x30);
static_assert(offsetof(CThread, m_terminateArg) == 0x38);
static_assert(sizeof(CThread) == 0x40);

}  // namespace soa::native::sync

#endif  // SOA_NATIVE_SYNC_LAYOUT_H
