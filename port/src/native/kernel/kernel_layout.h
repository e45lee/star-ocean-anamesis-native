// kernel_layout.h: the guest data layouts of the `kernel` subsystem (tasks, fibers, the message dispatcher, the app loop).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/kernel/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types (fields use the
// fixed-width types only: `long` is 32-bit on Windows).
// `tools/subsystem.py export-types kernel` turns the structs into port/decomp/kernel/types.json for Ghidra.
//
// The guest classes are Aska::* and Framework::*; here they are flat in soa::native::kernel
// (tools/subsystem.py matches a struct to its guest methods by the class's short name), each comment
// naming the guest class. Guest classes with data-carrying bases nest the base as the first member
// (`base`), as containers_layout.h does.
#ifndef SOA_NATIVE_KERNEL_LAYOUT_H
#define SOA_NATIVE_KERNEL_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../containers/containers_layout.h"
#include "../memory/memory_layout.h"
#include "../sync/sync_layout.h"
#include "gen/kernel_addresses.h"  // kVaddr*: the guest statics (tools/gen_addresses.py)

namespace soa::native::kernel {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// ---- Guest addresses (ELF vaddr; add main_lib()->base) of the statics the classes below use: the
// generated gen/kernel_addresses.h (tools/gen_addresses.py, from addresses.txt: each found in the lib),
// included above.


// ---- The `sync` subsystem's classes (native/sync/sync_layout.h) ----------------------------------------
// Embedded everywhere here: the dispatcher's lock (+0x08) and free-block event (+0x148), the workers'
// wake-up events, the task manager's 32 barrier events and its two locks, the notifier's semaphores.
// What kernel's code shows of FastCriticalSection, inlined into every dispatcher / task manager method:
// +0x38 s32 lock word (-1 free, 0 held; LDAXR/STLXR), +0x3c s32 waiters (spinners past 0x200 tries),
// +0x78 Aska::Semaphore (signalled on unlock with > 20 waiters): sync's Enter() / Leave().
using Event = sync::Event;                              // Aska::Event (0x68)
using Semaphore = sync::Semaphore;                      // Aska::Semaphore (0x18)
using CriticalSection = sync::CriticalSection;          // Aska::CriticalSection (0x28, a recursive pthread mutex)
using FastCriticalSection = sync::FastCriticalSection;  // Aska::FastCriticalSection (0x90, spin + semaphore)
using Thread = sync::Thread;                            // Aska::Thread {vtable, the pthread}; slot 2 Handler()
static_assert(sizeof(Event) == 0x68);
static_assert(sizeof(Semaphore) == 0x18);
static_assert(sizeof(CriticalSection) == 0x28);
static_assert(sizeof(FastCriticalSection) == 0x90);
static_assert(sizeof(Thread) == 0x10);

using LinkElement = containers::LinkElement;  // Aska::LinkElement {vtable, m_prev, m_next}

class Task;
class TaskManager;
struct PostFields;  // what a Post* / Send* form writes into its block (kernel_dispatcher.cpp)
class CTimeElement;
class SimpleMessageDispatcher;

// ---- INotify --------------------------------------------------------------------------------------------
// Aska::INotify: the callback interface every system hands to the dispatcher, the notifier threads and
// the task manager's end notifications (an upward call: kernel calls scene / ui / battle / resource
// through it; only the interface is kernel's). No vtable of its own is exported; the implementers'
// (e.g. _ZTVN4Aska6Global15DeleteEndNotifyE) show the order:
//   slot 0  Handler(unsigned long arg)   the dispatcher passes the MessageDispatcherBlock*; NotifierThread
//                                        passes the INotify* itself
//   slot 1  ~INotify() (D1, no-op)       slot 2  the deleting destructor
class INotify {
public:
    static constexpr int kSlotHandler = 0;
    static constexpr int kSlotDtor = 1;
    static constexpr int kSlotDtorDelete = 2;

    const void* vtable;  // 0x00
};

// ---- The message dispatcher ---------------------------------------------------------------------------

// Aska::MessageDispatcherBlock: one message, 0x50 bytes (AddMessage memsets 0x50; GetMessage memcpy's
// 0x50 to the caller's block). Fields from the Post* / Send* writers and the worker's Handler
// (port/decomp/kernel/message_dispatcher.c).
class MessageDispatcherBlock {
public:
    static constexpr u16 kMessageMask = 0x3fff;
    static constexpr u16 kFlagWaitCounter = 0x4000;  // deliverable only once *m_counter == 0 (GetMessage)
    static constexpr u16 kFlagSignalEvent = 0x8000;  // the worker Set()s m_event after the handler

    u16 m_serial;           // 0x00: the dispatcher's m_nextSerial at posting (returned through the u32* out)
    u16 m_message;          // 0x02: the message id & kMessageMask, plus the two flags
    u8 unk_04[4];           // 0x04
    INotify* m_notify;      // 0x08: the handler: worker calls m_notify slot 0 (Handler) with this block
    Event* m_event;         // 0x10: set after the handler when kFlagSignalEvent (the Send* forms wait on it)
    TaskManager* m_barrierManager;  // 0x18: the Post*(Task*, barrier, ...) forms: AddThreadBarrier +
    u32 m_barrier;          // 0x20:   IncrementThreadBarrierCount at posting, Decrement + Delete after
    u8 unk_24[4];           // 0x24
    s32* m_counter;         // 0x28: the PostSync* forms' counter: atomically decremented after the handler
    void* m_arg0;           // 0x30: the caller's two pointers
    void* m_arg1;           // 0x38
    u64 m_key0;             // 0x40: the (unsigned long, unsigned long) forms' two words; GetMessage keeps two
    u64 m_key1;             // 0x48:   workers off messages with an equal non-zero key; 0xffffffff = exclusive
};
static_assert(offsetof(MessageDispatcherBlock, m_message) == 0x02);
static_assert(offsetof(MessageDispatcherBlock, m_notify) == 0x08);
static_assert(offsetof(MessageDispatcherBlock, m_event) == 0x10);
static_assert(offsetof(MessageDispatcherBlock, m_barrierManager) == 0x18);
static_assert(offsetof(MessageDispatcherBlock, m_barrier) == 0x20);
static_assert(offsetof(MessageDispatcherBlock, m_counter) == 0x28);
static_assert(offsetof(MessageDispatcherBlock, m_arg0) == 0x30);
static_assert(offsetof(MessageDispatcherBlock, m_key0) == 0x40);
static_assert(offsetof(MessageDispatcherBlock, m_key1) == 0x48);
static_assert(sizeof(MessageDispatcherBlock) == 0x50);

// Aska::MessageDispatcherBlockForList: a queued block, 0x70 bytes (Setup allocates n * 0x70): a
// LinkElement (vtable _ZTVN4Aska29MessageDispatcherBlockForListE: slot 0 ~LinkElement, slot 1 its
// deleting dtor), the message, its priority.
class MessageDispatcherBlockForList {
public:
    LinkElement link;              // 0x00: m_prev at +0x08, m_next at +0x10 (the queue's order)
    MessageDispatcherBlock m_block;  // 0x18
    s8 m_priority;                 // 0x68: the Post* forms' last argument; SendMessageHigh / AddMessageToFront 0x7f
    u8 unk_69[7];                  // 0x69
};
static_assert(offsetof(MessageDispatcherBlockForList, m_block) == 0x18);
static_assert(offsetof(MessageDispatcherBlockForList, m_priority) == 0x68);
static_assert(sizeof(MessageDispatcherBlockForList) == 0x70);

// Aska::TList<Aska::MessageDispatcherBlockForList>: the dispatcher's queue. Its sentinel is a whole
// MessageDispatcherBlockForList (the inline construction in Global::InstantiateMessageDispatcher sets
// the sentinel's vtable and links), so the count sits at +0x78, not at containers::TList's +0x20 (that
// layout is TList<LinkElement>'s, whose sentinel is a bare LinkElement). The queue is ordered by
// descending priority from sentinel.m_next, FIFO within a priority (AddMessage walks back from
// sentinel.m_prev and inserts after the first block with priority >= the new one).
class MessageBlockList {
public:
    const void* vtable;                      // 0x00: _ZTVN4Aska5TListINS_29MessageDispatcherBlockForListEEE + 0x10
    MessageDispatcherBlockForList m_sentinel;  // 0x08
    s32 m_count;                             // 0x78
    u8 unk_7c[4];                            // 0x7c
};
static_assert(offsetof(MessageBlockList, m_sentinel) == 0x08);
static_assert(offsetof(MessageBlockList, m_count) == 0x78);
static_assert(sizeof(MessageBlockList) == 0x80);

using BlockQueue = memory::TDynamicQueue<MessageDispatcherBlockForList*>;  // Aska::TDynamicQueue<MessageDispatcherBlockForList*, false>
static_assert(sizeof(BlockQueue) == 0x20);

// Aska::SimpleMessageDispatcher::_WorkerThread: one worker, 0xe0 bytes (AllocateWorkerThreadList:
// operator new[](n * 0xe0 + 8), the count in the 8-byte cookie before the array). An Aska::Thread
// (vtable _ZTVN4Aska23SimpleMessageDispatcher13_WorkerThreadE: slots 0 / 1 the destructors, 2 Handler).
// Handler: wait on m_wakeup, then GetMessage(&m_current) until it fails; per message call the handler,
// decrement m_counter, signal m_event, release the barrier, MessageReady().
class WorkerThread {
public:
    // Guest methods (Aska::SimpleMessageDispatcher::_WorkerThread::*)
    void Handler();                               // vtable slot 2  _ZN4Aska23SimpleMessageDispatcher13_WorkerThread7HandlerEv
    bool GetMessage(MessageDispatcherBlock* out); // _ZN4Aska23SimpleMessageDispatcher13_WorkerThread10GetMessageEPNS_22MessageDispatcherBlockE
    void MessageReady();                          // _ZN4Aska23SimpleMessageDispatcher13_WorkerThread12MessageReadyEv
    void Exit();                                  // _ZN4Aska23SimpleMessageDispatcher13_WorkerThread4ExitEv

    Thread base;                   // 0x00
    u8 unk_10[8];                  // 0x10
    Event m_wakeup;                // 0x18: Create(false, false) at allocation; Set by Wakeup* / Post* / Exit
    u8 m_started;                  // 0x80: Handler sets 1
    u8 m_exit;                     // 0x81: Exit / Clear set 1, then Set m_wakeup
    u8 m_signalEvent;              // 0x82: the current message's kFlagSignalEvent
    u8 m_busy;                     // 0x83: has a message (GetMessage), cleared by MessageReady
    u8 m_waiting;                  // 0x84: idle and wakeable (1 at allocation); Post* wakes the first
                                   //       m_waiting && !m_busy worker whose event isn't signalled
    u8 unk_85;                     // 0x85: 0 at allocation
    u8 m_index;                    // 0x86: its index (the GetMessage(block, int) argument)
    u8 unk_87;                     // 0x87
    SimpleMessageDispatcher* m_owner;  // 0x88
    MessageDispatcherBlock m_current;  // 0x90: the message being handled
};
static_assert(offsetof(WorkerThread, m_wakeup) == 0x18);
static_assert(offsetof(WorkerThread, m_started) == 0x80);
static_assert(offsetof(WorkerThread, m_busy) == 0x83);
static_assert(offsetof(WorkerThread, m_waiting) == 0x84);
static_assert(offsetof(WorkerThread, m_index) == 0x86);
static_assert(offsetof(WorkerThread, m_owner) == 0x88);
static_assert(offsetof(WorkerThread, m_current) == 0x90);
static_assert(offsetof(WorkerThread, m_current.m_key0) == 0xd0);
static_assert(sizeof(WorkerThread) == 0xe0);

// Aska::SimpleMessageDispatcher: the job queue the engine's worker threads ("Aska::DynamicsWorker",
// max(1, min(cores - 2, 256)) of them) drain. Guest size 0x1d0 (Global::InstantiateMessageDispatcher:
// operator new(0x1d0), the constructor inlined there: vtable, FastCriticalSection, the list's sentinel,
// the free queue, the Event; then Initialize(), Setup(app+0x88, 0x80), the vtable becomes
// MessageDispatcher's, AllocateWorkerThreadList(n, "Aska::DynamicsWorker", 0xb, 6, 0x20000)).
// Every queue operation runs under m_cs (the FastCriticalSection inlined: the spin on its lock word is
// the dispatcher's guest self time in the profile).
// vtable (_ZTVN4Aska23SimpleMessageDispatcherE; MessageDispatcher's has the same slots 2 / 3):
//   0 ~SimpleMessageDispatcher (D2)  1 deleting  2 GetMessage(MessageDispatcherBlock*, int)  3 CheckToDispatch(block)
class SimpleMessageDispatcher {
public:
    static constexpr int kSlotGetMessage = 2;
    static constexpr int kSlotCheckToDispatch = 3;

    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)
    void DtorBase();    // _ZN4Aska23SimpleMessageDispatcherD2Ev
    void DtorDelete();  // _ZN4Aska23SimpleMessageDispatcherD0Ev
    // Virtuals in vtable order, as plain members
    bool GetMessage(MessageDispatcherBlock* out, s32 workerIndex);  // slot 2  _ZN4Aska23SimpleMessageDispatcher10GetMessageEPNS_22MessageDispatcherBlockEi
    bool CheckToDispatch(MessageDispatcherBlockForList* block);     // slot 3  (returns true)
    // Methods
    bool Initialize();                                  // _ZN4Aska23SimpleMessageDispatcher10InitializeEv
    void Release();                                     // _ZN4Aska23SimpleMessageDispatcher7ReleaseEv
    bool Setup(s32 numBlocks, s32 threadPriority);      // _ZN4Aska23SimpleMessageDispatcher5SetupEii
    bool AllocateWorkerThreadList(s32 n, const char* name, s32 priority, s32 core, s32 stack);  // ...24AllocateWorkerThreadListEiPKciii
    bool AllocateWorkerThreadList(void* infos, s32 n);  // (Aska::MessageDispatherWorkerThreadInfo*, int)
    void Clear();                                       // _ZN4Aska23SimpleMessageDispatcher5ClearEv
    MessageDispatcherBlock* AddMessage(s8 priority);    // _ZN4Aska23SimpleMessageDispatcher10AddMessageEa (under m_cs)
    MessageDispatcherBlock* AddMessageToFront();        // _ZN4Aska23SimpleMessageDispatcher17AddMessageToFrontEv
    bool DeleteMessage(s32 serial);                     // _ZN4Aska23SimpleMessageDispatcher13DeleteMessageEi (< 0: all)
    bool CancelMessage(u32 serial);                     // _ZN4Aska23SimpleMessageDispatcher13CancelMessageEj
    bool WakeupWorkerThread();                          // _ZN4Aska23SimpleMessageDispatcher18WakeupWorkerThreadEv
    void WakeupAllWorkerThreads();                      // _ZN4Aska23SimpleMessageDispatcher22WakeupAllWorkerThreadsEv
    void SuspendWorkerThread();                         // _ZN4Aska23SimpleMessageDispatcher19SuspendWorkerThreadEv
    void ResumeWorkerThread();                          // _ZN4Aska23SimpleMessageDispatcher18ResumeWorkerThreadEv
    bool IsWorkerThreadSuspended() const;               // _ZNK4Aska23SimpleMessageDispatcher23IsWorkerThreadSuspendedEv
    bool PostMessage(u16 msg, INotify* notify, void* a0, void* a1, u32* serialOut, s8 priority);
        // _ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_Pja
    bool PostMessage(u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut, s8 priority);
        // _ZN4Aska23SimpleMessageDispatcher11PostMessageEtPNS_7INotifyEPvS3_mmPja
    bool PostMessage(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u32* serialOut, s8 priority);
        // _ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_Pja
    bool PostMessage(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut, s8 priority);
        // _ZN4Aska23SimpleMessageDispatcher11PostMessageEPNS_4TaskEitPNS_7INotifyEPvS5_mmPja
    bool PostSyncMessageSingle(u16 msg, s32* counter, INotify* notify, void* a0, void* a1, u32* serialOut, s8 priority);
    bool PostSyncMessageSingle(u16 msg, s32* counter, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut, s8 priority);
    bool PostSyncMessageEnd(u16 msg, s32* counter, INotify* notify, void* a0, void* a1, u32* serialOut, s8 priority);
    bool PostSyncMessageEnd(u16 msg, s32* counter, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, u32* serialOut, s8 priority);
    bool PostMultiMessages(void* args, s32 n, s8 priority);  // (Argument* / ArgumentEx*)
    bool PostSyncMessages(void* args, s32 n, s32* counter, s8 priority);
    bool SendMessage(u16 msg, INotify* notify, void* a0, void* a1, s8 priority);
    bool SendMessage(u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, s8 priority);
    bool SendMessageHigh(u16 msg, INotify* notify, void* a0, void* a1);
    bool SendMessageHigh(u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1);
    bool SendMessage(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, s8 priority);
    bool SendMessage(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1, s8 priority);
    bool SendMessageHigh(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1);
    bool SendMessageHigh(Task* task, s32 barrier, u16 msg, INotify* notify, void* a0, void* a1, u64 k0, u64 k1);

    // Host helpers (not guest symbols): the pieces every Post* / Send* form inlines.
    MessageDispatcherBlockForList* LinkFreeBlock(s8 priority, bool atFront);  // under m_cs; nullptr when full
    bool Post(const PostFields& f, u32* serialOut, s8 priority);
    bool Send(const PostFields& f, s8 priority, bool high);
    s32 WakeIdleWorker();  // the Post* forms' wake pass (WakeupWorkerThread's loop): the index woken, or -1
    void WakeWaitingWorkers();  // Set every m_waiting worker's event (WakeupAllWorkerThreads' loop)

    const void* vtable;              // 0x00
    FastCriticalSection m_cs;        // 0x08: guards everything below
    MessageBlockList m_queue;        // 0x98: the queued messages (sentinel at 0xa0, count at 0x110)
    BlockQueue m_freeBlocks;         // 0x118: free blocks (Setup pushes all n; capacity n + 1)
    MessageDispatcherBlockForList* m_blocks;  // 0x138: the block array (Setup: operator new[](n * 0x70 + (n + 1) * 8))
    u8* m_blockStorage;              // 0x140: the same allocation (delete[]d by the destructor)
    Event m_freeBlockEvent;          // 0x148: Create(true, false) in Setup; Reset when the queue is full, Set when
                                     //        GetMessage frees a block while m_full
    u8 m_full;                       // 0x1b0
    u8 unk_1b1[3];                   // 0x1b1
    s32 m_threadPriority;            // 0x1b4: Setup's 2nd argument (0x80 by Initialize); the workers' priority
    s32 m_workerCount;               // 0x1b8
    u8 unk_1bc[4];                   // 0x1bc
    WorkerThread* m_workers;         // 0x1c0: new[] array (count cookie at m_workers - 8)
    u8 m_suspended;                  // 0x1c8: SuspendWorkerThread / ResumeWorkerThread; GetMessage returns 0 while set
    u8 unk_1c9;                      // 0x1c9
    u16 m_nextSerial;                // 0x1ca
    u8 unk_1cc[4];                   // 0x1cc
};
static_assert(offsetof(SimpleMessageDispatcher, m_cs) == 0x08);
static_assert(offsetof(SimpleMessageDispatcher, m_queue) == 0x98);
static_assert(offsetof(SimpleMessageDispatcher, m_queue.m_sentinel) == 0xa0);
static_assert(offsetof(SimpleMessageDispatcher, m_queue.m_sentinel.link.m_prev) == 0xa8);
static_assert(offsetof(SimpleMessageDispatcher, m_queue.m_sentinel.link.m_next) == 0xb0);
static_assert(offsetof(SimpleMessageDispatcher, m_queue.m_count) == 0x110);
static_assert(offsetof(SimpleMessageDispatcher, m_freeBlocks) == 0x118);
static_assert(offsetof(SimpleMessageDispatcher, m_freeBlocks.m_write) == 0x120);
static_assert(offsetof(SimpleMessageDispatcher, m_freeBlocks.m_read) == 0x124);
static_assert(offsetof(SimpleMessageDispatcher, m_freeBlocks.m_capacity) == 0x128);
static_assert(offsetof(SimpleMessageDispatcher, m_freeBlocks.m_items) == 0x130);
static_assert(offsetof(SimpleMessageDispatcher, m_blocks) == 0x138);
static_assert(offsetof(SimpleMessageDispatcher, m_blockStorage) == 0x140);
static_assert(offsetof(SimpleMessageDispatcher, m_freeBlockEvent) == 0x148);
static_assert(offsetof(SimpleMessageDispatcher, m_full) == 0x1b0);
static_assert(offsetof(SimpleMessageDispatcher, m_threadPriority) == 0x1b4);
static_assert(offsetof(SimpleMessageDispatcher, m_workerCount) == 0x1b8);
static_assert(offsetof(SimpleMessageDispatcher, m_workers) == 0x1c0);
static_assert(offsetof(SimpleMessageDispatcher, m_suspended) == 0x1c8);
static_assert(offsetof(SimpleMessageDispatcher, m_nextSerial) == 0x1ca);
static_assert(sizeof(SimpleMessageDispatcher) == 0x1d0);

// Aska::MessageDispatcher: the class Global::m_pMessageDispatcher holds; SimpleMessageDispatcher plus
// nothing (same 0x1d0 allocation; Initialize / Release are empty, vtable slots 2 / 3 inherited).
class MessageDispatcher {
public:
    bool Initialize();  // _ZN4Aska17MessageDispatcher10InitializeEv (returns)
    void Release();     // _ZN4Aska17MessageDispatcher7ReleaseEv

    SimpleMessageDispatcher base;  // 0x00
};
static_assert(sizeof(MessageDispatcher) == 0x1d0);

// ---- Tasks ----------------------------------------------------------------------------------------------

// Aska::Task: a unit of per-frame work in a TaskManager (an Aska::AnimatableLinkElement: IAnimatable's
// vtable + the list links). Guest size 0x28: the constructor is inlined everywhere (WaitVSync::
// Instantiate, CMainTask::CMainTask, TaskManager::TaskManager's Task base): vtable, links 0, owner 0,
// +0x24 u16 0, +0x26 u8 0, m_level = GetDefaultLevel() (vtable slot 11).
// vtable (_ZTVN4Aska4TaskE): 0 / 1 dtors, 2 GetClassID(int), 3 Clone, 4 CreateClone, 5 Get, 6 Set
// (AnimatableLinkElement), 7 DeleteThis(DeleteManager*), 8 DeleteThisNextFrame, 9 DeleteThisAfterTwoFrames,
// 10 DeleteThisImmediately, 11 GetDefaultLevel, 12 MessageHandler(u32, int, void*, void*), 13 Run(int),
// 14 IsMulti, 15 OnDeleteFromTaskManager, 16 OnAddToTaskManager, 17 OnAddTopToTaskManager,
// 18 OnInsertToTaskManager. Run (slot 13) is the upward call into every system's task (scene, ui, battle).
class Task {
public:
    static constexpr int kSlotGetDefaultLevel = 11;
    static constexpr int kSlotMessageHandler = 12;
    static constexpr int kSlotRun = 13;
    static constexpr int kSlotOnAddToTaskManager = 16;
    static constexpr u8 kFlagNoRun = 0x02;  // m_flags bit 1: OwnersKickTask skips the task's Run

    void DtorBase();                         // _ZN4Aska4TaskD2Ev (asks m_owner to Delete it, slot 8)
    void DtorDelete();                       // _ZN4Aska4TaskD0Ev
    void Run(s32 level);                     // slot 13  _ZN4Aska4Task3RunEi
    void ChangeLevel(u32 level);             // _ZN4Aska4Task11ChangeLevelEj
    void Remove();                           // _ZN4Aska4Task6RemoveEv
    void ForceDelete();                      // _ZN4Aska4Task11ForceDeleteEv
    void DeleteThis(void* deleteManager);    // slot 7  _ZN4Aska4Task10DeleteThisEPNS_13DeleteManagerE

    LinkElement link;       // 0x00: vtable, m_prev, m_next (the owner's list: TList<AnimatableLinkElement>)
    TaskManager* m_owner;   // 0x18: set by TaskManager::Add / AddTop / Insert
    u32 m_level;            // 0x20: a bit mask of levels (TaskManager counts each set bit)
    u8 m_flags;             // 0x24: kFlagNoRun
    u8 unk_25;              // 0x25: 0 at construction (u16 with m_flags)
    u8 unk_26;              // 0x26: 0 at construction
    u8 unk_27;              // 0x27
};
static_assert(offsetof(Task, m_owner) == 0x18);
static_assert(offsetof(Task, m_level) == 0x20);
static_assert(offsetof(Task, m_flags) == 0x24);
static_assert(sizeof(Task) == 0x28);

// Aska::TaskManager's end notifications (CreateEndNotifyList(n): n + 1 entries of 0x18; entry 0 is the
// list head: m_used 1, m_last = the last added): OwnersKickTask calls each m_notify slot 0 with m_arg.
struct TaskEndNotify {
    INotify* m_notify;  // 0x00
    u64 m_arg;          // 0x08
    u8 m_used;          // 0x10
    u8 m_next;          // 0x11: index of the next entry (0 ends)
    u8 m_last;          // 0x12: entry 0 only: the last entry's index
    u8 unk_13[5];       // 0x13
};
static_assert(sizeof(TaskEndNotify) == 0x18);

// Aska::TaskManager: the frame's task list, itself a Task (second base at +0x28; vtable at +0x28 is
// _ZTVN4Aska11TaskManagerE + 0xa0: the non-virtual thunks). Guest size 0xff0 (Global's
// InstantiateSystemTaskManager: operator new(0xff0)); layout from TaskManager::TaskManager,
// ~TaskManager, Add, OwnersKickTask, MakeTaskList, the barrier functions (port/decomp/kernel/task.c).
// Primary vtable (_ZTVN4Aska11TaskManagerE): 0 / 1 dtors, 2 Add / 3 AddTop / 4 Insert / 5 Delete
// (TList<AnimatableLinkElement>'s), 6 GetClassID, 7 GetThisType, 8 Delete(Task*), 9 PreAllocateTaskList,
// 10 DeletePreAllocateTaskList, 11 MergeManager, 12 ReleaseMergedManager, 13 Broadcast, 14 OwnersKickTask,
// 15 Delete(LinkElement*).
// OwnersKickTask (once per frame on the system task manager from CMainTask / AskaMainThread):
// MakeTaskList sorts every task of the merged ring into m_taskList by level (m_levelEnds[level] marks
// each level's end), then runs them in order (Task slot 13 with the level), waiting on
// m_barrierEvents[level + 1] at each level boundary while that barrier's count is > 0.
class TaskManager {
public:
    static constexpr int kSlotDeleteTask = 8;
    static constexpr int kSlotPreAllocateTaskList = 9;
    static constexpr int kSlotOwnersKickTask = 14;
    static constexpr int kNumLevels = 32;

    void Ctor();                              // _ZN4Aska11TaskManagerC2Ev
    void DtorBase();                          // _ZN4Aska11TaskManagerD2Ev
    void DtorDelete();                        // _ZN4Aska11TaskManagerD0Ev
    void Add(Task* t);                        // _ZN4Aska11TaskManager3AddEPNS_4TaskE
    void Add(Task* t, u32 level);             // _ZN4Aska11TaskManager3AddEPNS_4TaskEj (0: the task's default level)
    void AddTop(Task* t, u32 level);          // _ZN4Aska11TaskManager6AddTopEPNS_4TaskEj
    void Insert(Task* t, Task* at, u32 level);  // _ZN4Aska11TaskManager6InsertEPNS_4TaskES2_j
    void Delete(Task* t);                     // slot 8  _ZN4Aska11TaskManager6DeleteEPNS_4TaskE
    void ChangeLevel(Task* t, u32 level);     // _ZN4Aska11TaskManager11ChangeLevelEPNS_4TaskEj
    void IncrementTaskLevelCount(u32 level);  // _ZN4Aska11TaskManager23IncrementTaskLevelCountEj
    void DecrementTaskLevelCount(u32 level);  // _ZN4Aska11TaskManager23DecrementTaskLevelCountEj
    s32 GetTotalTaskNumber() const;           // _ZNK4Aska11TaskManager18GetTotalTaskNumberEv (sum of m_totalCount over the ring, under m_cs)
    void PreAllocateTaskList(s32 n);          // slot 9
    void DeletePreAllocateTaskList();         // slot 10
    void MergeManager(TaskManager* other);    // slot 11
    void ReleaseMergedManager();              // slot 12
    void OwnersKickTask();                    // slot 14  _ZN4Aska11TaskManager14OwnersKickTaskEv
    void MakeTaskList();                      // _ZN4Aska11TaskManager12MakeTaskListEv
    bool IsCalled(Task* t);                   // _ZN4Aska11TaskManager8IsCalledEPNS_4TaskE
    void AddThreadBarrier(s32 i);             // _ZN4Aska11TaskManager16AddThreadBarrierEi
    void DeleteThreadBarrier(s32 i);          // _ZN4Aska11TaskManager19DeleteThreadBarrierEi
    void IncrementThreadBarrierCount(s32 i);  // _ZN4Aska11TaskManager27IncrementThreadBarrierCountEi
    void DecrementThreadBarrierCount(s32 i);  // _ZN4Aska11TaskManager27DecrementThreadBarrierCountEi
    bool CreateEndNotifyList(s32 n);          // _ZN4Aska11TaskManager19CreateEndNotifyListEi
    bool AddEndNotify(INotify* n, u64 arg);   // _ZN4Aska11TaskManager12AddEndNotifyEPNS_7INotifyEm
    bool RemoveEndNotify(INotify* n, u64 arg);  // _ZN4Aska11TaskManager15RemoveEndNotifyEPNS_7INotifyEm
    void SetupMessageQueue(void* queue);      // _ZN4Aska11TaskManager17SetupMessageQueueEPNS_12MessageQueueE
    u8 AllocateBroadcast();                   // _ZN4Aska11TaskManager17AllocateBroadcastEv
    void Broadcast(u8 id);                    // slot 13

    const void* vtable;           // 0x00: _ZTVN4Aska11TaskManagerE + 0x10
    LinkElement m_sentinel;       // 0x08: the task list (TList<AnimatableLinkElement>; vtable AnimatableLinkElement's)
    s32 m_count;                  // 0x20: tasks in the list
    u8 unk_24[4];                 // 0x24
    Task task;                    // 0x28: the Task base (vtable _ZTVN4Aska11TaskManagerE + 0xa0)
    s32 m_levelCount[kNumLevels]; // 0x50: tasks per level bit
    s32 m_totalCount;             // 0xd0: one per set level bit of each task
    s32 m_runLevel;               // 0xd4: OwnersKickTask: the level being run
    s32 m_runIndex;               // 0xd8: OwnersKickTask: the index in m_taskList being run
    s32 m_runCount;               // 0xdc: OwnersKickTask: GetTotalTaskNumber at the start
    void* m_messageQueue;         // 0xe0: Aska::MessageQueue* (SetupMessageQueue; shared by the ring)
    Task** m_taskList;            // 0xe8: PreAllocateTaskList(n): new[](n + 0x21) pointers
    u8 unk_f0[8];                 // 0xf0
    Task*** m_levelEnds;          // 0xf8: = m_taskList + n: per level, the end of its run in m_taskList
    s32 m_capacity;               // 0x100: n
    u8 unk_104[4];                // 0x104
    TaskManager* m_ringHead;      // 0x108: the merged ring's first manager (this when alone)
    TaskManager* m_ringPrev;      // 0x110: this when alone
    TaskManager* m_ringNext;      // 0x118: this when alone (GetTotalTaskNumber walks it)
    u8 m_broadcastIds;            // 0x120: allocated broadcast ids (bits; 0x0f at construction)
    u8 unk_121;                   // 0x121
    u16 m_endNotifyCount;         // 0x122: CreateEndNotifyList(n): n + 1
    u8 unk_124[4];                // 0x124
    TaskEndNotify* m_endNotifies; // 0x128
    Event m_barrierEvents[kNumLevels];  // 0x130: barrier i's event (Created by AddThreadBarrier)
    u32 m_barrierCreated;         // 0xe30: bit i: m_barrierEvents[i] created
    u32 m_barrierPending;         // 0xe34: bit i: the event is Reset (count > 0)
    s32 m_barrierRefs[kNumLevels];    // 0xe38: AddThreadBarrier / DeleteThreadBarrier
    s32 m_barrierCounts[kNumLevels];  // 0xeb8: Increment / DecrementThreadBarrierCount (the posted messages)
    CriticalSection m_barrierCs;  // 0xf38
    FastCriticalSection m_cs;     // 0xf60: Add / Delete / GetTotalTaskNumber / MakeTaskList
};
static_assert(offsetof(TaskManager, m_sentinel) == 0x08);
static_assert(offsetof(TaskManager, m_count) == 0x20);
static_assert(offsetof(TaskManager, task) == 0x28);
static_assert(offsetof(TaskManager, task.m_owner) == 0x40);
static_assert(offsetof(TaskManager, task.m_level) == 0x48);
static_assert(offsetof(TaskManager, m_levelCount) == 0x50);
static_assert(offsetof(TaskManager, m_totalCount) == 0xd0);
static_assert(offsetof(TaskManager, m_runIndex) == 0xd8);
static_assert(offsetof(TaskManager, m_runCount) == 0xdc);
static_assert(offsetof(TaskManager, m_messageQueue) == 0xe0);
static_assert(offsetof(TaskManager, m_taskList) == 0xe8);
static_assert(offsetof(TaskManager, m_levelEnds) == 0xf8);
static_assert(offsetof(TaskManager, m_capacity) == 0x100);
static_assert(offsetof(TaskManager, m_ringHead) == 0x108);
static_assert(offsetof(TaskManager, m_ringNext) == 0x118);
static_assert(offsetof(TaskManager, m_broadcastIds) == 0x120);
static_assert(offsetof(TaskManager, m_endNotifyCount) == 0x122);
static_assert(offsetof(TaskManager, m_endNotifies) == 0x128);
static_assert(offsetof(TaskManager, m_barrierEvents) == 0x130);
static_assert(offsetof(TaskManager, m_barrierCreated) == 0xe30);
static_assert(offsetof(TaskManager, m_barrierPending) == 0xe34);
static_assert(offsetof(TaskManager, m_barrierRefs) == 0xe38);
static_assert(offsetof(TaskManager, m_barrierCounts) == 0xeb8);
static_assert(offsetof(TaskManager, m_barrierCs) == 0xf38);
static_assert(offsetof(TaskManager, m_cs) == 0xf60);
static_assert(sizeof(TaskManager) == 0xff0);

// ---- Fibers ---------------------------------------------------------------------------------------------

// Framework::CFiberUnit: a cooperative unit of the client's main loop (scenes, phases, menus derive from
// it). Guest size 0x38; layout from CFiberUnit::CFiberUnit(unsigned int), the accessors, CFiberKernel::
// Attach / Detach / Progress (port/decomp/kernel/fiber.c). A Framework::TChain<CFiberUnit> (prev / next).
// vtable (_ZTVN9Framework10CFiberUnitE): 0 / 1 dtors, 2 Attach(CFiberUnit*), 3 pTop, 4 pBottom,
// 5 Progress (pure: the derived class's per-frame body: the upward call into the game), 6 OnCreated,
// 7 OnDestroyed, 8 IsDestroyed, 9 CreateSubFiber(CFiberUnit*).
class CFiberUnit {
public:
    static constexpr int kSlotAttach = 2;
    static constexpr int kSlotProgress = 5;
    static constexpr int kSlotOnCreated = 6;
    // m_status values (Activate / Wait / ActivateFromActivating / CFiberKernel::Progress)
    // 0: not created / destroyed (IsDestroyed), 4: Destroy(true) requested (Progress destroys and deletes it)
    static constexpr s32 kStatusNone = 0, kStatusActivating = 1, kStatusActive = 2, kStatusWaiting = 3,
                         kStatusDestroyRequested = 4;

    void CtorBase(u32 priority);   // _ZN9Framework10CFiberUnitC2Ej
    void DtorBase();               // _ZN9Framework10CFiberUnitD2Ev
    void DtorDelete();             // _ZN9Framework10CFiberUnitD0Ev
    void Attach(CFiberUnit* u);    // slot 2
    CFiberUnit* pTop();            // slot 3
    CFiberUnit* pBottom();         // slot 4
    void OnCreated();              // slot 6 (empty)
    void OnDestroyed();            // slot 7 (empty)
    bool IsDestroyed() const;      // slot 8
    void CreateSubFiber(CFiberUnit* u);  // slot 9
    s32 Status() const;            // _ZNK9Framework10CFiberUnit6StatusEv
    u32 Priority() const;          // _ZNK9Framework10CFiberUnit8PriorityEv
    void* pKernel() const;         // _ZNK9Framework10CFiberUnit7pKernelEv (CFiberKernel*)
    u32 Group() const;             // _ZNK9Framework10CFiberUnit5GroupEv
    void Group(u32 g);             // _ZN9Framework10CFiberUnit5GroupEj
    void Activate();               // _ZN9Framework10CFiberUnit8ActivateEv (from Waiting / None)
    void ActivateFromActivating(); // _ZN9Framework10CFiberUnit22ActivateFromActivatingEv
    void Wait();                   // _ZN9Framework10CFiberUnit4WaitEv
    void Destroy(bool b);          // _ZN9Framework10CFiberUnit7DestroyEb
    bool IsCreated() const;        // _ZNK9Framework10CFiberUnit9IsCreatedEv
    bool IsActive() const;         // _ZNK9Framework10CFiberUnit8IsActiveEv

    const void* vtable;     // 0x00
    CFiberUnit* m_prev;     // 0x08: TChain
    CFiberUnit* m_next;     // 0x10: TChain (the kernel's list: ascending m_priority)
    u64 m_unk18;            // 0x18: 0 at construction and at Create (meaning unknown)
    u32 m_handle;           // 0x20: TSimpleHandle<CFiberUnitHandle>::m_MasterHandle + 1 (skips -1 -> 0)
    u32 m_priority;         // 0x24: the constructor's argument
    void* m_kernel;         // 0x28: CFiberKernel* (Create / CreateSubFiber)
    s32 m_status;           // 0x30: kStatus*
    u32 m_group;            // 0x34
};
static_assert(offsetof(CFiberUnit, m_prev) == 0x08);
static_assert(offsetof(CFiberUnit, m_next) == 0x10);
static_assert(offsetof(CFiberUnit, m_handle) == 0x20);
static_assert(offsetof(CFiberUnit, m_priority) == 0x24);
static_assert(offsetof(CFiberUnit, m_kernel) == 0x28);
static_assert(offsetof(CFiberUnit, m_status) == 0x30);
static_assert(offsetof(CFiberUnit, m_group) == 0x34);
static_assert(sizeof(CFiberUnit) == 0x38);

// Framework::CFiberKernel: a CFiberUnit that runs a chain of units. Guest size 0x50 (CApplication:
// operator new(0x50) + CFiberKernel(0x600) for the root kernel; the constructor leaves m_numAttached /
// m_numActive alone: Initialize() clears them). Progress (slot 5): units Activating become Active,
// every Active unit's Progress (slot 5) runs in chain order, units with Destroy requested are
// destroyed and deleted (slot 1), m_numActive = the Active count. vtable as CFiberUnit's with slot 2
// Attach (insert by ascending priority), 5 Progress, 9 CreateSubFiber.
class CFiberKernel {
public:
    void CtorBase(u32 priority);             // _ZN9Framework12CFiberKernelC2Ej
    void DtorBase();                         // _ZN9Framework12CFiberKernelD2Ev
    void DtorDelete();                       // _ZN9Framework12CFiberKernelD0Ev
    void Attach(CFiberUnit* u);              // slot 2  _ZN9Framework12CFiberKernel6AttachEPNS_10CFiberUnitE
    void Progress();                         // slot 5  _ZN9Framework12CFiberKernel8ProgressEv
    void CreateSubFiber(CFiberUnit* u);      // slot 9
    void Initialize();                       // _ZN9Framework12CFiberKernel10InitializeEv
    void Release();                          // _ZN9Framework12CFiberKernel7ReleaseEv
    u32 NumAttachedUnits() const;            // _ZNK9Framework12CFiberKernel16NumAttachedUnitsEv
    u32 NumActiveUnits() const;              // _ZNK9Framework12CFiberKernel14NumActiveUnitsEv
    CFiberUnit* pSearchByHandle(u32 h) const;  // _ZNK9Framework12CFiberKernel15pSearchByHandleEj
    void Detach(CFiberUnit* u);              // _ZN9Framework12CFiberKernel6DetachEPNS_10CFiberUnitE
    void Create(CFiberUnit* u);              // _ZN9Framework12CFiberKernel6CreateEPNS_10CFiberUnitE
    void Destroy(CFiberUnit* u);             // _ZN9Framework12CFiberKernel7DestroyEPNS_10CFiberUnitE

    CFiberUnit base;        // 0x00
    u32 m_numAttached;      // 0x38
    u32 m_numActive;        // 0x3c: Progress's count of Active units
    CFiberUnit* m_units;    // 0x40: the chain's head (lowest priority value first)
    u64 m_unk48;            // 0x48: 0 at construction and Initialize (meaning unknown)
};
static_assert(offsetof(CFiberKernel, m_numAttached) == 0x38);
static_assert(offsetof(CFiberKernel, m_numActive) == 0x3c);
static_assert(offsetof(CFiberKernel, m_units) == 0x40);
static_assert(sizeof(CFiberKernel) == 0x50);

// ---- The application loop -------------------------------------------------------------------------------

// Framework::CApplication::CMainTask: the client's main task (the TSingleton), added to the system task
// manager by CApplication::InitializeMainTask; Run(int) (Task slot 13) is the frame: input, the root
// fiber kernel's Progress, cameras, faders, sound. Guest size 0xf8 (InitializeMainTask: operator
// new(0xf8)); layout from the constructor and the r* accessors (port/decomp/kernel/application.c).
// Fields whose meaning the read code doesn't show are padding.
class CMainTask {
public:
    void Ctor();                            // _ZN9Framework12CApplication9CMainTaskC2Ev
    void Run(s32 level);                    // Task slot 13  _ZN9Framework12CApplication9CMainTask3RunEi
    u32 FrameCounter() const;               // _ZNK9Framework12CApplication9CMainTask12FrameCounterEv
    CFiberKernel* rRootFiberKernel();       // _ZN9Framework12CApplication9CMainTask16rRootFiberKernelEv
    void* rCamera() const;                  // _ZNK9Framework12CApplication9CMainTask7rCameraEv
    void* rSystemDefaultCamera() const;     // _ZNK9Framework12CApplication9CMainTask20rSystemDefaultCameraEv
    void* rFader() const;                   // _ZNK9Framework12CApplication9CMainTask6rFaderEv
    void* rFaderView_Color() const;         // _ZNK9Framework12CApplication9CMainTask16rFaderView_ColorEv
    void* rSoundManager() const;            // _ZNK9Framework12CApplication9CMainTask13rSoundManagerEv
    void* rResourceManager() const;         // _ZNK9Framework12CApplication9CMainTask16rResourceManagerEv
    void* rDebugPrimitiveManager();         // _ZN9Framework12CApplication9CMainTask22rDebugPrimitiveManagerEv
    void* rResponderChainManager();         // _ZN9Framework12CApplication9CMainTask22rResponderChainManagerEv
    void* rISO();                           // _ZN9Framework12CApplication9CMainTask4rISOEv (= &m_iso)
    void* pScreenPrintPool(u32 i);          // _ZN9Framework12CApplication9CMainTask16pScreenPrintPoolEj (m_screenPrintPools + i * 0x40)

    Task task;                      // 0x00: vtable _ZTVN9Framework12CApplication9CMainTaskE + 0x10
    u8 unk_28[4];                   // 0x28
    u32 m_frameCounter;             // 0x2c
    void* m_camera;                 // 0x30: Aska::Camera* (rCamera / crCamera)
    void* m_systemDefaultCamera;    // 0x38
    u8 m_iso[8];                    // 0x40: Framework::CISO (constructed in place; rISO; size from the next field)
    void* m_fader;                  // 0x48: Framework::CFader*
    void* m_faderViewColor;         // 0x50
    void* m_soundManager;           // 0x58
    void* m_resourceManager;        // 0x60: Framework::CResourceManager* (the resource subsystem's)
    u8 unk_68[0x28];                // 0x68: (+0x6f, +0x70 bytes written by the ctor / dtor)
    CFiberKernel* m_rootFiberKernel;  // 0x90
    u8* m_screenPrintPools;         // 0x98: 2 pools of 0x40
    u8 unk_a0[0x38];                // 0xa0
    void* m_debugPrimitiveManager;  // 0xd8
    void* m_responderChainManager;  // 0xe0: Framework::ResponderChain::CManager*
    u8 unk_e8[0x10];                // 0xe8: (+0xec u8, +0xf0 cleared by the ctor)
};
static_assert(offsetof(CMainTask, m_frameCounter) == 0x2c);
static_assert(offsetof(CMainTask, m_camera) == 0x30);
static_assert(offsetof(CMainTask, m_systemDefaultCamera) == 0x38);
static_assert(offsetof(CMainTask, m_iso) == 0x40);
static_assert(offsetof(CMainTask, m_fader) == 0x48);
static_assert(offsetof(CMainTask, m_faderViewColor) == 0x50);
static_assert(offsetof(CMainTask, m_soundManager) == 0x58);
static_assert(offsetof(CMainTask, m_resourceManager) == 0x60);
static_assert(offsetof(CMainTask, m_rootFiberKernel) == 0x90);
static_assert(offsetof(CMainTask, m_screenPrintPools) == 0x98);
static_assert(offsetof(CMainTask, m_debugPrimitiveManager) == 0xd8);
static_assert(offsetof(CMainTask, m_responderChainManager) == 0xe0);
static_assert(sizeof(CMainTask) == 0xf8);

// ---- Timing ---------------------------------------------------------------------------------------------

// Aska::PerformanceCounter: frame-phase timers. Guest size 0x260 (Global::InstantiatePerformanceCounter:
// operator new(0x260)); layout from the constructor, Mark, Set, GetMark (port/decomp/kernel/timing.c).
// Mark(i) stores CLOCK_MONOTONIC ns in m_marks[i]; Set(i) stores (now - m_marks[i]) * m_scale in m_values[i].
class PerformanceCounter {
public:
    static constexpr int kNumCounters = 48;

    void Ctor();                    // _ZN4Aska18PerformanceCounterC2Ev
    void Mark(s32 i);               // _ZN4Aska18PerformanceCounter4MarkEi
    void Set(s32 i);                // _ZN4Aska18PerformanceCounter3SetEi
    void Set(s32 i, s64 value);     // _ZN4Aska18PerformanceCounter3SetEil
    void AddSet(s32 i);             // _ZN4Aska18PerformanceCounter6AddSetEi
    s64 GetMark(s32 i) const;       // _ZNK4Aska18PerformanceCounter7GetMarkEi

    const void* vtable;             // 0x00
    double m_scale;                 // 0x08: 0.001 (ns -> us)
    s64 m_marks[kNumCounters];      // 0x10
    s32 m_values[kNumCounters];     // 0x190
    s64 m_baseTime;                 // 0x250: CLOCK_MONOTONIC ns at construction
    u8 unk_258[8];                  // 0x258: 0 at construction
};
static_assert(offsetof(PerformanceCounter, m_scale) == 0x08);
static_assert(offsetof(PerformanceCounter, m_marks) == 0x10);
static_assert(offsetof(PerformanceCounter, m_values) == 0x190);
static_assert(offsetof(PerformanceCounter, m_baseTime) == 0x250);
static_assert(sizeof(PerformanceCounter) == 0x260);

// Framework::CTimeElement: a node of the client's time tree (scaled dt per subtree). Guest size 0x48
// (the constructor writes up to 0x44); layout from CTimeElement::CTimeElement, Initialize, Add(float),
// AddChild, DetachFromParent, the accessors (port/decomp/kernel/timing.c). A Framework::THierarchy
// (containers'). Add(dt) per node: dt *= the effective rate (m_interposeRate while interposing, else
// m_rate; 0 while suspended, which counts m_suspend down), m_time += dt, m_dt = dt; the scaled dt
// flows down the tree (a child's dt is its parent's scaled dt times its own rate).
// vtable: 0 / 1 dtors, 2 AddChild, 3 DetachFromParent, 4 DetachSelf.
class CTimeElement {
public:
    void Ctor();                        // _ZN9Framework12CTimeElementC2Ev
    void Initialize();                  // _ZN9Framework12CTimeElement10InitializeEv
    void AddChild(CTimeElement* c);     // slot 2
    void DetachFromParent();            // slot 3
    void DetachSelf();                  // slot 4
    void Add(float dt);                 // _ZN9Framework12CTimeElement3AddEf
    float Rate() const;                 // _ZNK9Framework12CTimeElement4RateEv
    void Rate(float r);                 // _ZN9Framework12CTimeElement4RateEf
    float DetailRate() const;           // _ZNK9Framework12CTimeElement10DetailRateEv
    float DT() const;                   // _ZNK9Framework12CTimeElement2DTEv
    void DT(float dt);                  // _ZN9Framework12CTimeElement2DTEf
    float Suspend() const;              // _ZNK9Framework12CTimeElement7SuspendEv
    void Suspend(float t);              // _ZN9Framework12CTimeElement7SuspendEf
    void AddSuspend(float t);           // _ZN9Framework12CTimeElement10AddSuspendEf
    void Interpose(float time, float rate);  // _ZN9Framework12CTimeElement9InterposeEff
    bool IsInterpose() const;           // _ZNK9Framework12CTimeElement11IsInterposeEv
    float InterposeRate() const;        // _ZNK9Framework12CTimeElement13InterposeRateEv
    float InterposeTime() const;        // _ZNK9Framework12CTimeElement13InterposeTimeEv
    void UpdateDTForce();               // _ZN9Framework12CTimeElement13UpdateDTForceEv

    containers::THierarchy<CTimeElement> base;  // 0x00: vtable, m_parent, m_nextSibling (+0x10), m_firstChild (+0x18), +0x20
    float m_time;                // 0x28: accumulated (scaled) time
    float m_rate;                // 0x2c: 1.0 at construction
    float m_dt;                  // 0x30: the last Add's scaled dt (DT())
    float m_suspend;             // 0x34: remaining suspend time
    u8 m_interposeStarted;       // 0x38
    u8 unk_39[3];                // 0x39
    float m_interposeTime;       // 0x3c: remaining interpose time
    float m_interposeRate;       // 0x40
    u8 m_lock;                   // 0x44: IsLockTimeElement (Rate() asserts on it)
    u8 unk_45[3];                // 0x45
};
static_assert(offsetof(CTimeElement, base.m_parent) == 0x08);
static_assert(offsetof(CTimeElement, base.m_nextSibling) == 0x10);
static_assert(offsetof(CTimeElement, base.m_firstChild) == 0x18);
static_assert(offsetof(CTimeElement, m_time) == 0x28);
static_assert(offsetof(CTimeElement, m_rate) == 0x2c);
static_assert(offsetof(CTimeElement, m_dt) == 0x30);
static_assert(offsetof(CTimeElement, m_suspend) == 0x34);
static_assert(offsetof(CTimeElement, m_interposeStarted) == 0x38);
static_assert(offsetof(CTimeElement, m_interposeTime) == 0x3c);
static_assert(offsetof(CTimeElement, m_interposeRate) == 0x40);
static_assert(offsetof(CTimeElement, m_lock) == 0x44);
static_assert(sizeof(CTimeElement) == 0x48);

// Aska::NotifierThread::NotifyElement: a pooled registration (0x28: the pool's element size in AddNotify).
class NotifyElement {
public:
    LinkElement link;    // 0x00: in NotifierThread::m_list
    INotify* m_notify;   // 0x18
    u32 m_count;         // 0x20: notifications left (0: forever); Notify unlinks the element when it reaches 0
    u8 unk_24[4];        // 0x24
};
static_assert(offsetof(NotifyElement, m_notify) == 0x18);
static_assert(offsetof(NotifyElement, m_count) == 0x20);
static_assert(sizeof(NotifyElement) == 0x28);

// Aska::NotifierThread: a thread that calls registered INotify handlers (slot 0) each time it is
// signalled (VSync is one). Guest size 0xb8 (VSync embeds it at +0x08 and its own fields start at
// +0xc0); layout from NotifierThread::NotifierThread(int), AddNotify, Notify, Handler.
// vtable: 0 / 1 dtors, 2 Handler (wait m_signal, slot 5), 3 GetThreadPriority, 4 GetThreadName, 5 Notify.
class NotifierThread {
public:
    void Ctor(s32 capacity);                // _ZN4Aska14NotifierThreadC2Ei
    void DtorBase();                        // _ZN4Aska14NotifierThreadD2Ev
    void Init();                            // _ZN4Aska14NotifierThread4InitEv
    void Handler();                         // slot 2
    void Notify();                          // slot 5  _ZN4Aska14NotifierThread6NotifyEv
    void AddNotify(INotify* n, u32 count);  // _ZN4Aska14NotifierThread9AddNotifyEPNS_7INotifyEj
    void AddPriorityNotify(INotify* n, u32 count);  // _ZN4Aska14NotifierThread17AddPriorityNotifyEPNS_7INotifyEj
    void RemoveNotify(INotify* n);          // _ZN4Aska14NotifierThread12RemoveNotifyEPNS_7INotifyE
    bool QueryNotify(INotify* n);           // _ZN4Aska14NotifierThread11QueryNotifyEPNS_7INotifyE

    Thread base;                // 0x00
    u8 unk_10[8];               // 0x10
    containers::TListLink m_list;  // 0x18: Aska::List (vtable, sentinel LinkElement, count at +0x38)
    Semaphore m_lock;           // 0x40: Create(1, 1): the list's mutex
    Semaphore m_signal;         // 0x58: Create(0, 0x100): Handler waits on it
    containers::TPoolFast<NotifyElement> m_pool;  // 0x70: SecurePool(capacity)
};
static_assert(offsetof(NotifierThread, m_list) == 0x18);
static_assert(offsetof(NotifierThread, m_list.m_sentinel) == 0x20);
static_assert(offsetof(NotifierThread, m_list.m_count) == 0x38);
static_assert(offsetof(NotifierThread, m_lock) == 0x40);
static_assert(offsetof(NotifierThread, m_signal) == 0x58);
static_assert(offsetof(NotifierThread, m_pool) == 0x70);
static_assert(offsetof(NotifierThread, m_pool.m_used.m_bits) == 0x88);
static_assert(offsetof(NotifierThread, m_pool.m_pool) == 0xa0);
static_assert(offsetof(NotifierThread, m_pool.m_count) == 0xac);
static_assert(sizeof(NotifierThread) == 0xb8);

// Aska::EventNotify: an INotify whose Handler sets an event (a stack object in GPUSync::WaitGPUSync).
class EventNotify {
public:
    const void* vtable;  // 0x00: _ZTVN4Aska11EventNotifyE + 0x10 (slot 0 Handler: m_event->Set())
    Event* m_event;      // 0x08
};
static_assert(sizeof(EventNotify) == 0x10);

// Aska::GPUSync: a NotifierThread the render thread signals when the GPU has finished a frame
// (RenderThread::m_pGPUSync). Layout from WaitGPUSync / Notify / the destructors
// (port/decomp/kernel/gpu_sync.c): the notifier, a "frame pending" flag, a binary semaphore guarding both.
class GPUSync {
public:
    void WaitGPUSync();  // _ZN4Aska7GPUSync11WaitGPUSyncEv
    void Notify();       // _ZN4Aska7GPUSync6NotifyEv (NotifierThread vtable slot 5)

    NotifierThread base;  // 0x00: vtable _ZTVN4Aska7GPUSyncE + 0x10
    u8 m_pending;         // 0xb8: set by the render thread when a frame is queued; Notify clears it
    u8 unk_b9[7];         // 0xb9
    Semaphore m_lock;     // 0xc0: guards m_pending and the notify list (Wait / Signal)
};
static_assert(offsetof(GPUSync, m_pending) == 0xb8);
static_assert(offsetof(GPUSync, m_lock) == 0xc0);
static_assert(sizeof(GPUSync) == 0xd8);

// Aska::VSync: the frame clock. An IVSync (vtable at +0) and a NotifierThread (+0x08: VSync's vtable
// + 0x50, the thunks). Layout from VSync::VSync(int), Initialize, CalcDtAndDFrame / UpdateDt, GetDt,
// GetBasicFrameRate (port/decomp/kernel/timing.c); size not confirmed (no allocation site read).
// Per clock i (6): UpdateDt(i) takes the vsync counter delta (capped at 60 / m_divisor) as the frame
// count m_dFrame[i], m_invDFrame[i] = 1 / it, m_dt[i] = frames / the video manager's refresh rate (or
// m_fixedDt[i] when m_useFixedDt); GetDt(i) = m_dt[i] * m_dtScale.
// vtable: 0 GetDt(int), 1 GetVSyncCounter, 2 GetBasicFrameRate, 3 Notify, 4 / 5 dtors.
class VSync {
public:
    static constexpr int kNumClocks = 6;

    float GetDt(s32 clock) const;           // slot 0  _ZNK4Aska5VSync5GetDtEi
    u32 GetVSyncCounter() const;            // slot 1  (the static m_nVSyncCounter)
    u32 GetBasicFrameRate() const;          // slot 2  _ZNK4Aska5VSync17GetBasicFrameRateEv
    void Notify();                          // slot 3
    bool Initialize();                      // _ZN4Aska5VSync10InitializeEv
    void UpdateDt(s32 clock);               // _ZN4Aska5VSync8UpdateDtEi
    void CalcDtAndDFrame(s32 clock, u32 counter);  // _ZN4Aska5VSync15CalcDtAndDFrameEij
    void UpdateVSyncEvents(u32 a, u32 b, s32 c, bool d);  // _ZN4Aska5VSync17UpdateVSyncEventsEjjib
    void WaitVSync(s32 a, s32 b);           // _ZN4Aska5VSync9WaitVSyncEii

    const void* vtable;                 // 0x00: _ZTVN4Aska5VSyncE + 0x10
    NotifierThread m_notifier;          // 0x08: vtable _ZTVN4Aska5VSyncE + 0x50
    s32 m_lastCounter[kNumClocks];      // 0xc0: Initialize clears 0xc0..0x12b
    s32 m_prevCounter[kNumClocks];      // 0xd8
    s16 m_dFrame[kNumClocks];           // 0xf0
    float m_invDFrame[kNumClocks];      // 0xfc
    float m_dt[kNumClocks];             // 0x114
    float m_dtScale;                    // 0x12c: 1.0 by Initialize
    u32 m_basicFrameRate;               // 0x130: 60 (the constructor; CApplication writes 60 / 1 at 0x130 / 0x134)
    u32 m_divisor;                      // 0x134: 15 by the constructor, 1 after CApplication's init
    u8 m_useFixedDt;                    // 0x138
    u8 unk_139[3];                      // 0x139
    u8 unk_13c[8];                      // 0x13c: 0 by Initialize
    float m_fixedDt[kNumClocks];        // 0x144: (Initialize clears 0x144..0x15b)
    u32 unk_15c;                        // 0x15c: 0 by Initialize
};
static_assert(offsetof(VSync, m_notifier) == 0x08);
static_assert(offsetof(VSync, m_lastCounter) == 0xc0);
static_assert(offsetof(VSync, m_prevCounter) == 0xd8);
static_assert(offsetof(VSync, m_dFrame) == 0xf0);
static_assert(offsetof(VSync, m_invDFrame) == 0xfc);
static_assert(offsetof(VSync, m_dt) == 0x114);
static_assert(offsetof(VSync, m_dtScale) == 0x12c);
static_assert(offsetof(VSync, m_basicFrameRate) == 0x130);
static_assert(offsetof(VSync, m_divisor) == 0x134);
static_assert(offsetof(VSync, m_useFixedDt) == 0x138);
static_assert(offsetof(VSync, m_fixedDt) == 0x144);
static_assert(sizeof(VSync) == 0x160);  // at least: the last field read; no allocation site read

// Aska::Global: statics only (the addresses above). Its functions (GetCPUTime, GetPeripheral,
// GetActivePad, the Instantiate* family, InitAll, DeleteEndNotify::Handler) are kernel's.
class Global {
public:
    static s64 GetCPUTime();              // _ZN4Aska6Global10GetCPUTimeEv (CLOCK_BOOTTIME in ms)
    static void* GetPeripheral(s32 i);    // _ZN4Aska6Global13GetPeripheralEi
    static void* GetActivePad();          // _ZN4Aska6Global12GetActivePadEv
    static bool InstantiateMessageDispatcher();   // _ZN4Aska6Global28InstantiateMessageDispatcherEv
    static bool InstantiatePerformanceCounter();  // _ZN4Aska6Global29InstantiatePerformanceCounterEv
    static bool InitAll();                // _ZN4Aska6Global7InitAllEv
};

}  // namespace soa::native::kernel

#endif  // SOA_NATIVE_KERNEL_LAYOUT_H
