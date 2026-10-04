// memory_layout.h: the guest data layouts of the `memory` subsystem (the engine heaps, allocators, handles).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/memory/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types memory` turns the structs into port/decomp/memory/types.json for Ghidra.
#ifndef SOA_NATIVE_MEMORY_LAYOUT_H
#define SOA_NATIVE_MEMORY_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../containers/containers_layout.h"  // MappedMemoryManager's hash tables (containers' classes)
#include "../sync/sync_layout.h"              // FastCriticalSection, CMutex, CriticalSection (sync's classes)

namespace soa::native::memory {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;


// ---- Guest addresses (ELF vaddr; add main_lib()->base) of the statics the classes below use ------
// From the decompiles in port/decomp/memory/ and `nm -DS` (the object sizes check the classes' sizeof).
inline constexpr u64 kVaddrGlobalMemoryManager = 0x2ccc698;       // Aska::Global::m_pMemoryManager (MemoryManager*)
inline constexpr u64 kVaddrRootMemoryManager = 0x2ccc6a0;         // the mmap'd root heap's MemoryManager* (a local
                                                                  // static of Global::InitializeMemoryManager; no symbol)
inline constexpr u64 kVaddrSystemDeleteManager = 0x2cc1d00;       // Aska::Global::m_systemDeleteManager (0x138 bytes)
inline constexpr u64 kVaddrSharedPointerCodePool = 0x2ccd4a0;     // TSharedPointerCode's counter pool (no symbol)
inline constexpr u64 kVaddrStlMemoryManager = 0x2c00528;          // CAssignedMemoryManagerForSTLAllocator::m_pMemoryManager
inline constexpr u64 kVaddrStlFixedLengthContainer = 0x2c00530;   // ...::m_pFixedLengthAllocatorContainer
inline constexpr u64 kVaddrApplicationMemoryInstance = 0x2c00260; // TSingleton<CApplicationMemory>::m_pInstance

// The locks are sync's classes (port/src/native/sync/sync_layout.h): Aska::FastCriticalSection (0x90,
// embedded: lock word +0x38, waiter count +0x3c, Semaphore +0x78), Framework::CMutex (0xb0, the pools'
// and handle managers' pointers), Aska::CriticalSection (0x28).
using sync::CMutex;
using sync::CriticalSection;
using sync::FastCriticalSection;

class MemoryManager;
class MemoryBlock;

// Aska::_MemoryBlock: the 0x40-byte header in front of every MemoryManager allocation (user pointer =
// header + 0x40). Layout from MemoryManager::Malloc / LocalFree / InitHeap / GetAllocatedManager /
// GetMemorySize (port/decomp/memory/memory_manager.c). Blocks of one superblock form a physical chain
// (next/prev by address) and the free ones a free list whose head is the superblock's first block (a
// 0x40-byte sentinel that is never free). Sizes include the header and are 16-aligned:
// Malloc(n) takes (n + 0x4f) & ~0xf; a remainder under 0x50 stays with the block.
class MemoryBlock {
public:
    u64 m_size;             // 0x00: the whole block, header included (GetMemorySize returns it)
    MemoryBlock* m_physNext;// 0x08: the next block by address (the sentinel closes the ring)
    MemoryBlock* m_physPrev;// 0x10
    MemoryBlock* m_freeNext;// 0x18: the free list (in the superblock's sentinel: its head)
    MemoryBlock* m_freePrev;// 0x20
    MemoryManager* m_owner; // 0x28: the manager it came from (GetAllocatedManager: *(p - 0x18))
    u8 m_high;              // 0x30: 1 from MallocHigh / AlignedMallocHigh (they store u16 0x101), 0 from
                            //       Malloc / AlignedMalloc (0x100) and in the run heads' sentinels
    u8 m_used;              // 0x31: 1 allocated / sentinel, 0 free (Malloc's "!= 1" tests)
    u8 unk_32[6];           // 0x32
    void* m_notify;         // 0x38: Aska::IMemoryNotify* registered on the block (LocalRegisterNotify writes
                            //       it, *(p - 8)); LocalFree calls its vtable slot 1 (notify, p) outside
                            //       the lock before freeing; 0 on allocation

    void* Data() { return reinterpret_cast<u8*>(this) + 0x40; }
    static MemoryBlock* FromData(const void* p) {
        return reinterpret_cast<MemoryBlock*>(reinterpret_cast<u8*>(const_cast<void*>(p)) - 0x40);
    }
};
static_assert(offsetof(MemoryBlock, m_size) == 0x00);
static_assert(offsetof(MemoryBlock, m_physNext) == 0x08);
static_assert(offsetof(MemoryBlock, m_physPrev) == 0x10);
static_assert(offsetof(MemoryBlock, m_freeNext) == 0x18);
static_assert(offsetof(MemoryBlock, m_freePrev) == 0x20);
static_assert(offsetof(MemoryBlock, m_owner) == 0x28);
static_assert(offsetof(MemoryBlock, m_high) == 0x30);
static_assert(offsetof(MemoryBlock, m_used) == 0x31);
static_assert(offsetof(MemoryBlock, m_notify) == 0x38);
static_assert(sizeof(MemoryBlock) == 0x40);

// Aska::MemoryManager::_Srbk: one per 64 KiB superblock of the heap, in an array at MemoryManager::
// m_srbks (the tail of the heap buffer: InitHeap puts it after the superblocks). A run of superblocks
// that one allocation spans is linked by index (the first is in use, the others are absorbed).
// Layout from InitHeap / Malloc (port/decomp/memory/memory_manager.c).
class MemorySrbk {
public:
    u8 m_inUse;             // 0x00: 1 for the first superblock of a run
    u8 unk_01[3];           // 0x01
    u32 m_next;             // 0x04: index of the next run (0 ends the list: superblock 0 is always in use)
    u32 m_prev;             // 0x08: index of the previous run
    u8 unk_0c[4];           // 0x0c
    u64 m_allocated;        // 0x10: bytes allocated from this run (block sizes, headers included)
    u64 m_free;             // 0x18: bytes free (the free blocks' sizes)
    u64 m_largestFree;      // 0x20: the largest free block (Malloc's fast reject; recomputed after a hit)
};
static_assert(offsetof(MemorySrbk, m_inUse) == 0x00);
static_assert(offsetof(MemorySrbk, m_next) == 0x04);
static_assert(offsetof(MemorySrbk, m_prev) == 0x08);
static_assert(offsetof(MemorySrbk, m_allocated) == 0x10);
static_assert(offsetof(MemorySrbk, m_free) == 0x18);
static_assert(offsetof(MemorySrbk, m_largestFree) == 0x20);
static_assert(sizeof(MemorySrbk) == 0x28);
inline constexpr u64 kSrbkSize = 0x10000;  // bytes per superblock

// Aska::MemoryManager: the engine heap (a first-fit allocator over 64 KiB superblocks). Guest size 0xf0
// (operator new(0xf0) in MemoryManagerHelper::Init / CApplicationMemory::Set*MemoryManager); layout from
// the constructors, InitHeap, Malloc, Remove, IsCreated and ~MemoryManager. Managers are linked in a
// ring (m_ringNext / m_ringPrev; Malloc tries every manager of the ring before the bad-allocate notify).
// vtable: _ZTVN4Aska13MemoryManagerE + 0x10 (27 slots; Aska::IMemoryManager's interface).
class MemoryManager {
public:
    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)
    void CtorBase();                         // MemoryManager()  _ZN4Aska13MemoryManagerC2Ev (= C1)
    void Ctor(u64 heapSize);                 // MemoryManager(unsigned long)  _ZN4Aska13MemoryManagerC1Em
    void DtorBase();                         // ~MemoryManager()  _ZN4Aska13MemoryManagerD2Ev (= D1)
    void DtorDelete();                       // ~MemoryManager()  _ZN4Aska13MemoryManagerD0Ev (frees itself into its owner)
    // Virtuals in vtable order (_ZTVN4Aska13MemoryManagerE), as plain members
    void* VirtualMalloc(u64 size);                        // slot 0
    void* VirtualMallocHigh(u64 size);                    // slot 1
    void* VirtualAlignedMalloc(u64 size, s64 align);      // slot 2
    void* VirtualAlignedMallocHigh(u64 size, s64 align);  // slot 3
    void* VirtualRealloc(u64 size, void* p, s64 align);   // slot 4
    bool VirtualSplit(void* p, void* at);                 // slot 5
    void* VirtualMove(void* p, s64 delta, bool high);     // slot 6
    void* VirtualMoveHigh(void* p, s64 delta);            // slot 7
    void VirtualFree(void* p);                            // slot 8
    u8* VirtualGetHeapAddress() const;                    // slot 9
    bool VirtualIsPhysical() const;                       // slot 10
    // slot 11: Aska::IMemoryManager::VirtualIsMemoryHandleManager() (inherited; false)
    u64 VirtualCalcFreeSize(s64* heapBytes, s64* usedBytes) const;  // slot 12
    bool VirtualIsEmpty(bool all) const;                  // slot 13
    void* VirtualGetFastCriticalSection();                // slot 14: &m_cs
    MemorySrbk* VirtualGetSrbk(s32 index) const;          // slot 15
    u8* VirtualGetTopSrbkAddress() const;                 // slot 16
    // slot 17: Aska::IMemoryManager::VirtualGetCurrentSrbkIndex() const (inherited)
    void VirtualPrintMemoryChain();                       // slot 18
    u64 VirtualGetHeapSize() const;                       // slot 19
    MemoryManager* VirtualGetAllocatedManager(const void* p, u64* size);  // slot 20
    bool VirtualRegisterNotify(void* p, void* notify);    // slot 21 (Aska::IMemoryNotify*)
    bool VirtualRemoveNotify(void* p, void* notify);      // slot 22
    bool VirtualIsRegisteredNotify(void* p, void* notify);// slot 23
    void* VirtualGetRegisteredNotify(void* p);            // slot 24
    // slots 25, 26: ~MemoryManager() D1, D0
    // Methods
    bool InitHeap(u8* heap, u64 size);                    // InitHeap(unsigned char*, unsigned long): a caller's buffer
    bool InitHeap(u64 size);                              // InitHeap(unsigned long): operator new[](size + 0x10)
    bool InitHeap(u8* heap, u64 size, u8* srbks, u64 srbkSize);  // InitHeap(uchar*, ulong, uchar*, ulong)
    bool InitSrbk(u64 size);
    bool InitSrbk(u64 size, u8* srbks);
    void Initialize();                                    // the fields only: ring = this, no heap
    void ClearHeap();                                     // empty in 3.7.0
    void DeleteHeap();
    bool Remove(MemoryManager* other);                    // takes `other` out of this ring
    bool Add(MemoryManager* other);
    bool Add(s32 size);
    bool Add(void* heap, s32 size);
    void* Malloc(u64 size);                               // first fit from the lowest superblock (m_allocHigh: MallocHigh)
    void* MallocHigh(u64 size);                           // first fit from the top
    void* AlignedMalloc(u64 size, s64 align);
    void* AlignedMallocHigh(u64 size, s64 align);
    void* Realloc(u64 size, void* p, s64 align);
    bool Split(void* p, void* at);
    void* Move(void* p, s64 delta, bool high);
    void LocalFree(MemoryBlock* block);                   // LocalFree(Aska::_MemoryBlock*): `this` is the block's owner
    void LocalFree(void* p);                              // LocalFree(void*): block->m_owner->LocalFree(block) (`this` unused)
    bool IsCreated() const;                               // any manager of the ring has a heap
    bool IsPhysical() const;
    u64 GetMemorySize(const void* p);                     // the block's m_size
    static MemoryManager* GetAllocatedManager(const void* p, u64* size);  // the block's owner (+ m_size)
    static MemoryManager* GetAllocatedManager(const void* p);
    u64 CalcFreeSize(s64* heapBytes, s64* usedBytes) const;  // over the ring; returns the largest free block's
                                                          // usable bytes ((largest - 0x40) & ~0xf, 0 when none)
    s64 CalcFreeSize(bool onlyThis);                      // free bytes (+ 0x40 per run) of this manager or the ring
    s32 CountFreeBlocks();
    bool IsEmpty(bool all) const;
    bool SearchNextBlock(MemorySrbk** srbk, MemoryBlock** block, bool used);
    static u64 CalcSrbkSize(u64 heapSize);
    static u64 CalcFullHeapSize(u64 heapSize);
    static u64 CalcFullHeapSizeForOneBlock(u64 size, s64 align, bool high);
    bool LocalRegisterNotify(void* p, void* notify);
    bool LocalRemoveNotify(void* p, void* notify);
    bool LocalIsRegisteredNotify(void* p, void* notify);
    void* LocalGetRegisteredNotify(void* p);
    bool RegisterNotify(void* p, void* notify);
    bool RemoveNotify(void* p, void* notify);
    bool IsRegisteredNotify(void* p, void* notify);
    void* GetRegisteredNotify(void* p);
    void PrintMemoryChain();
    void PrintMemoryChain(const char* label);
    void CreateDebugMemoryMap(s32 w, s32 h, bool swap);   // empty in the release build
    void UpdateDebugMemoryMap();
    void GetDebugMemoryMap(void* text, float x, float y, u32 color, float w, float h);
    void SetSwapDebugMemoryMap(bool swap);
    // Native internals (no guest symbols; memory_heap.cpp): the bodies the guest runs between its inlined
    // lock enter and leave, storing through `st` (memory_heap.h: DirectStore, or the live check's
    // LoggedStore). Each returns nullptr when nothing in this manager fits (no store made then).
    template <class St> MemoryBlock* MallocLocked(u64 need, const St& st);
    template <class St> void* AlignedMallocLocked(u64 size, s64 align, u64 need, const St& st);
    template <class St> void* AlignedMallocHighLocked(s64 align, u64 need, const St& st);
    template <class St> void LocalFreeLocked(MemoryBlock* block, const St& st);  // after the notify part
    template <class St> void UpdateLargestFree(MemorySrbk* run, const St& st);
    // Malloc's / AlignedMalloc*'s fallback: the ring, then m_badAllocNotify (BadAllocateRequest).
    template <class TryOne> void* AllocateFromRing(u64 size, s64 align, TryOne tryOne);

    const void* vtable;          // 0x00: _ZTVN4Aska13MemoryManagerE + 0x10
    u8 m_allocHigh;              // 0x08: 1: Malloc allocates from the top (MallocHigh)
    u8 unk_09[7];                // 0x09
    MemorySrbk* m_srbks;         // 0x10: the superblock table (m_srbkCount entries)
    u32 m_srbkCount;             // 0x18: superblocks in the heap ((size + 0xffbe) / 0x10028 per InitHeap(size))
    u8 unk_1c[4];                // 0x1c
    u8* m_heap;                  // 0x20: superblock 0 (nullptr: no heap)
    u64 m_heapSize;              // 0x28: the bytes before the superblock table (m_srbks = m_heap + m_heapSize):
                                 //       (size + 0x10 - count * 0x28) & ~0xf, or count * 0x10000 when that
                                 //       leaves under 0x80 in the last superblock
    void* m_badAllocNotify;      // 0x30: called when no manager of the ring can satisfy Malloc (vtable slot 0,
                                 //       e.g. Framework::CBadAllocateNotifyRetry from CApplicationMemory)
    u8 m_ownsHeap;               // 0x38: InitHeap(size) allocated m_heap (freed by DeleteHeap)
    u8 unk_39[7];                // 0x39
    MemoryManager* m_ringHead;   // 0x40: the ring's first manager (this when alone)
    MemoryManager* m_ringNext;   // 0x48: the next manager of the ring (Malloc's fallback order)
    MemoryManager* m_ringPrev;   // 0x50
    MemoryManager* m_parent;     // 0x58: a manager whose heap holds this one (~MemoryManager deletes the children)
    FastCriticalSection m_cs;    // 0x60: every heap method's lock (its word at 0x98)
};
static_assert(offsetof(MemoryManager, vtable) == 0x00);
static_assert(offsetof(MemoryManager, m_allocHigh) == 0x08);
static_assert(offsetof(MemoryManager, m_srbks) == 0x10);
static_assert(offsetof(MemoryManager, m_srbkCount) == 0x18);
static_assert(offsetof(MemoryManager, m_heap) == 0x20);
static_assert(offsetof(MemoryManager, m_heapSize) == 0x28);
static_assert(offsetof(MemoryManager, m_badAllocNotify) == 0x30);
static_assert(offsetof(MemoryManager, m_ownsHeap) == 0x38);
static_assert(offsetof(MemoryManager, m_ringHead) == 0x40);
static_assert(offsetof(MemoryManager, m_ringNext) == 0x48);
static_assert(offsetof(MemoryManager, m_ringPrev) == 0x50);
static_assert(offsetof(MemoryManager, m_parent) == 0x58);
static_assert(offsetof(MemoryManager, m_cs) == 0x60);
static_assert(sizeof(MemoryManager) == 0xf0);

// The request MemoryManager::Malloc / MallocHigh / AlignedMalloc / AlignedMallocHigh pass to
// m_badAllocNotify's vtable slot 0 when no manager of the ring can satisfy them (built on the caller's
// stack; the handler, e.g. Framework::CBadAllocateNotifyRetry, frees memory and may allocate into
// m_result). Layout from the four callers (memory_manager.c).
class BadAllocateRequest {
public:
    MemoryManager* m_manager;  // 0x00: the manager Malloc was called on
    u64 m_size;                // 0x08: the size asked for
    s64 m_align;               // 0x10: 4 for Malloc / MallocHigh, the alignment (at least 4) for AlignedMalloc*
    u32 m_zero18;              // 0x18: 0 (meaning unknown)
    u8 unk_1c[4];              // 0x1c: not written (the guest leaves stack garbage)
    s32* m_retries;            // 0x20: the caller's handler-call count (1 during the call; a second failure returns 0)
    void* m_result;            // 0x28: 0; the handler's allocation, returned when non-null
};
static_assert(offsetof(BadAllocateRequest, m_size) == 0x08);
static_assert(offsetof(BadAllocateRequest, m_align) == 0x10);
static_assert(offsetof(BadAllocateRequest, m_zero18) == 0x18);
static_assert(offsetof(BadAllocateRequest, m_retries) == 0x20);
static_assert(offsetof(BadAllocateRequest, m_result) == 0x28);
static_assert(sizeof(BadAllocateRequest) == 0x30);

// Aska::MemoryManagerAdapter: static entry points over Aska::Global's manager (no fields).
class MemoryManagerAdapter {
public:
    static void* Malloc(u64 size);
    static void Free(void* p);
    static void* AlignedMalloc(u64 size, u64 align);
    static void AlignedFree(void* p);
};

// Aska::MemoryManagerHelper: owns a MemoryManager (and the buffers of a MemoryHandleManager setup).
// Guest size 0x28 (the constructor clears 0x08..0x20); layout from the constructor, Init,
// InitMemoryHandleManager, Cleanup, ~MemoryManagerHelper (port/decomp/memory/helpers.c).
class MemoryManagerHelper {
public:
    void Ctor();       // MemoryManagerHelper()  _ZN4Aska19MemoryManagerHelperC1Ev
    void DtorBase();   // ~MemoryManagerHelper(): deletes m_manager, restores Global::m_pMemoryManager = m_savedGlobal
    // Virtuals in vtable order (_ZTVN4Aska19MemoryManagerHelperE)
    bool Init(u64 size, u32 unused);      // slot 0: new MemoryManager + InitHeap; becomes Global::m_pMemoryManager
    void Cleanup();                       // slot 1
    // Methods
    bool InitMemoryManager(u64 size);     // new MemoryManager + InitHeap (Global untouched)
    void CleanupMemoryManaer();           // (sic) deletes m_manager
    bool InitMemoryHandleManager(u64 size, u32 blocks);
    void CleanupMemoryHandleManager();

    const void* vtable;           // 0x00: _ZTVN4Aska19MemoryManagerHelperE + 0x10
    MemoryManager* m_manager;     // 0x08
    MemoryManager* m_savedGlobal; // 0x10: Global::m_pMemoryManager before Init
    u8* m_heap;                   // 0x18: InitMemoryHandleManager's heap (operator new[])
    u8* m_srbks;                  // 0x20: InitMemoryHandleManager's superblock / block tables
};
static_assert(offsetof(MemoryManagerHelper, m_manager) == 0x08);
static_assert(offsetof(MemoryManagerHelper, m_savedGlobal) == 0x10);
static_assert(offsetof(MemoryManagerHelper, m_heap) == 0x18);
static_assert(offsetof(MemoryManagerHelper, m_srbks) == 0x20);
static_assert(sizeof(MemoryManagerHelper) == 0x28);

// Framework::CApplicationMemory (TSingleton): the client's heaps. Guest size 0x28 (the constructor
// clears five words); layout from the r*MemoryManager getters and Set*MemoryManager (helpers.c).
class CApplicationMemory {
public:
    void Ctor();                            // CApplicationMemory(): registers the TSingleton instance
    void SetPrimaryMemoryManager();         // = Global::GetAvailableMemoryManager(); then the STL heap (0x1c00000)
    void SetParticleMemoryManager();        // new MemoryManager -> ParticleManager::gpMemHeap
    void SetSoundMemoryManager();           // new MemoryManager -> SoundMemory::m_pMemHeap
    void SetNetworkMemoryManager();
    void gReportMemory();
    MemoryManager* rPrimaryMemoryManager();
    MemoryManager* rSecondaryMemoryManager();
    MemoryManager* rParticleMemoryManager();
    MemoryManager* rSoundMemoryManager();
    MemoryManager* rNetworkMemoryManager();
    void* rDefaultBadAllocateNotify();      // a static Framework::CBadAllocateNotify
    void* rDefaultBadAllocateNotifyRetry(); // a static Framework::CBadAllocateNotifyRetry

    MemoryManager* m_primary;    // 0x00
    MemoryManager* m_secondary;  // 0x08
    MemoryManager* m_particle;   // 0x10
    MemoryManager* m_sound;      // 0x18
    MemoryManager* m_network;    // 0x20
};
static_assert(offsetof(CApplicationMemory, m_primary) == 0x00);
static_assert(offsetof(CApplicationMemory, m_secondary) == 0x08);
static_assert(offsetof(CApplicationMemory, m_particle) == 0x10);
static_assert(offsetof(CApplicationMemory, m_sound) == 0x18);
static_assert(offsetof(CApplicationMemory, m_network) == 0x20);
static_assert(sizeof(CApplicationMemory) == 0x28);

class CFixedLengthAllocatorContainer;

// Framework::CAssignedMemoryManagerForSTLAllocator: static state only (the kVaddrStl* statics above).
// Allocate tries the fixed-length allocators, then the STL MemoryManager (CApplicationMemory's
// 0x1c00000-byte heap), then operator new[](nothrow); Free in the same order (stl_allocator.c).
class CAssignedMemoryManagerForSTLAllocator {
public:
    static void Attach(MemoryManager* m);
    static MemoryManager* CreateAndAttach(u64 heapSize);
    static void AttachFixedLengthAllocator(CFixedLengthAllocatorContainer* c);
    static CFixedLengthAllocatorContainer* pAttachFixedLengthAllocator();
    static MemoryManager* pAttachedMemoryManager();
    static void* Allocate(u64 size, const char* file, u32 line);
    static void Free(void* p);
    static void ReportC();
    static void ReportS();
    static bool IsEnableReportByEachAccess(bool enable);  // returns the previous value
};

// Framework::IFixedLengthAllocator: the interface of TFixedLengthAllocator<N> (vtable only). Slots
// (from TFixedLengthAllocator<32>'s vtable and the calls in CFixedLengthAllocatorContainer):
// 0 D1, 1 D0, 2 BlockSize, 3 MaxBlock, 4 pAllocate, 5 Free, 6 IsMine, 7 NumAllocated, 8 IsFree,
// 9 ActivityRatio, 10 TotalMemoryAmount, 11 UsedMemoryAmount, 12 EnableMutex, 13 DisableMutex.
class IFixedLengthAllocator {
public:
    // Calls through the vtable (memory_pools.cpp): a TFixedLengthAllocator<N> natively when the vtable
    // is one of the seven instantiations', else the guest's slot.
    u64 BlockSize() const;                        // slot 2
    void* pAllocate(const char* file, u32 line);  // slot 4
    void Free(void* p);                           // slot 5
    bool IsMine(void* p) const;                   // slot 6

    const void* vtable;  // 0x00
};
static_assert(sizeof(IFixedLengthAllocator) == 0x08);

// The 0x10-byte header in front of each TFixedLengthAllocator<N> block (stride N + 0x10); written by
// the constructor, pAllocate, Free and checked by IsMine (stl_allocator.c).
class FixedLengthBlockHeader {
public:
    u8 m_tag[3];   // 0x00: the allocator's three tag characters (IsMine compares them)
    u8 m_free;     // 0x03: 1 free, 0 allocated (pAllocate asserts "Not free." unless 1)
    u32 m_index;   // 0x04: this block's index
    u32 m_next;    // 0x08: the next free block's index (0xffffffff ends the list)
    u8 unk_0c[4];  // 0x0c: 0xcc fill
};
static_assert(offsetof(FixedLengthBlockHeader, m_free) == 0x03);
static_assert(offsetof(FixedLengthBlockHeader, m_index) == 0x04);
static_assert(offsetof(FixedLengthBlockHeader, m_next) == 0x08);
static_assert(sizeof(FixedLengthBlockHeader) == 0x10);

template <u64 N>
class TFixedLengthBlock {
public:
    FixedLengthBlockHeader m_header;  // 0x00
    u8 m_data[N];                     // 0x10: what pAllocate returns
};

// Framework::TFixedLengthAllocator<N>: a pool of m_maxBlock blocks of N bytes. Guest size 0x48
// (operator new(0x48) for each in CGame::OnInitialize, which builds the six the STL allocator uses:
// <16> 'm16' x0x2000, <32> 'm32' x0x8000, <64> 'm64' x0x18000, <128> 'm12' x0x800, <256> 'm25' x0x800,
// <512> 'm51' x0x800; <192> exists too). Layout from the constructor, pAllocate, Free, IsMine and the
// accessors (stl_allocator.c).
template <u64 N>
class TFixedLengthAllocator {
public:
    void Ctor(char tag0, char tag1, char tag2, u64 maxBlock);  // C2: _ZN9Framework21TFixedLengthAllocatorILm<N>EEC2Ecccm
    void DtorBase();                    // D2
    void DtorDelete();                  // D0
    // Virtuals in vtable order (IFixedLengthAllocator)
    u64 BlockSize() const;              // slot 2: N
    u64 MaxBlock() const;               // slot 3: m_maxBlock
    void* pAllocate(const char* file, u32 line);  // slot 4: the free list's head; nullptr when full
    void Free(void* p);                 // slot 5
    bool IsMine(void* p) const;         // slot 6: in the block array and the header's tags match
    u32 NumAllocated() const;           // slot 7
    bool IsFree() const;                // slot 8: NumAllocated < MaxBlock
    float ActivityRatio() const;        // slot 9
    u64 TotalMemoryAmount() const;      // slot 10: m_maxBlock * (N + 0x10)
    u64 UsedMemoryAmount() const;       // slot 11: m_numAllocated * (N + 0x10)
    void EnableMutex();                 // slot 12: new Framework::CMutex (0xb0 bytes)
    void DisableMutex();                // slot 13
    // Native internals (memory_pools.cpp): pAllocate's / Free's bodies under m_mutex.
    void* AllocateLocked();
    void FreeLocked(void* p);

    const void* vtable;                 // 0x00: _ZTVN9Framework21TFixedLengthAllocatorILm<N>EEE + 0x10
    u8 unk_08[0x10];                    // 0x08: not written by the constructor; meaning unknown
    char m_tag[3];                      // 0x18: the tags copied into each block header
    u8 m_tagPad;                        // 0x1b: 0
    u8 unk_1c[4];                       // 0x1c
    u64 m_maxBlock;                     // 0x20
    TFixedLengthBlock<N>* m_blocks;     // 0x28: operator new[](m_maxBlock * (N + 0x10)), 0xcc-filled
    u8 m_ownsBlocks;                    // 0x30: 1 (the destructor deletes m_blocks)
    u8 unk_31[3];                       // 0x31
    u32 m_numAllocated;                 // 0x34
    u32 m_freeHead;                     // 0x38: index of the first free block
    u8 unk_3c[4];                       // 0x3c
    CMutex* m_mutex;                    // 0x40: EnableMutex's, or nullptr (DisableMutex)
};
using TFixedLengthAllocator16 = TFixedLengthAllocator<16>;
using TFixedLengthAllocator32 = TFixedLengthAllocator<32>;
using TFixedLengthAllocator64 = TFixedLengthAllocator<64>;
using TFixedLengthAllocator128 = TFixedLengthAllocator<128>;
using TFixedLengthAllocator192 = TFixedLengthAllocator<192>;
using TFixedLengthAllocator256 = TFixedLengthAllocator<256>;
using TFixedLengthAllocator512 = TFixedLengthAllocator<512>;
static_assert(sizeof(TFixedLengthBlock<32>) == 0x30);
static_assert(offsetof(TFixedLengthAllocator32, m_tag) == 0x18);
static_assert(offsetof(TFixedLengthAllocator32, m_maxBlock) == 0x20);
static_assert(offsetof(TFixedLengthAllocator32, m_blocks) == 0x28);
static_assert(offsetof(TFixedLengthAllocator32, m_ownsBlocks) == 0x30);
static_assert(offsetof(TFixedLengthAllocator32, m_numAllocated) == 0x34);
static_assert(offsetof(TFixedLengthAllocator32, m_freeHead) == 0x38);
static_assert(offsetof(TFixedLengthAllocator32, m_mutex) == 0x40);
static_assert(sizeof(TFixedLengthAllocator16) == 0x48 && sizeof(TFixedLengthAllocator32) == 0x48 &&
              sizeof(TFixedLengthAllocator64) == 0x48 && sizeof(TFixedLengthAllocator128) == 0x48 &&
              sizeof(TFixedLengthAllocator192) == 0x48 && sizeof(TFixedLengthAllocator256) == 0x48 &&
              sizeof(TFixedLengthAllocator512) == 0x48);

// Framework::TObjectContainer<T>: a fixed array (vtable, count, elements). Guest size 0x18; layout from
// TObjectContainer<IFixedLengthAllocator*>::Initialize / NumElements / rElement (stl_allocator.c).
// vtable slot 4 (+0x20) is NumElements.
template <typename T>
class TObjectContainer {
public:
    void DtorBase();                    // ~TObjectContainer(): operator delete[](m_elements)
    void Initialize(u64 count);         // operator new[](count * sizeof(T), nothrow)
    u64 NumElements() const;            // vtable slot 4
    T* rElement(u64 i);                 // asserts i < NumElements()
    const T* crElement(u64 i) const;
    void Reset();

    const void* vtable;  // 0x00: _ZTVN9Framework16TObjectContainerI...EE + 0x10
    u64 m_count;         // 0x08
    T* m_elements;       // 0x10
};
using TObjectContainerFixedLengthAllocatorPtr = TObjectContainer<IFixedLengthAllocator*>;
static_assert(offsetof(TObjectContainerFixedLengthAllocatorPtr, m_count) == 0x08);
static_assert(offsetof(TObjectContainerFixedLengthAllocatorPtr, m_elements) == 0x10);
static_assert(sizeof(TObjectContainerFixedLengthAllocatorPtr) == 0x18);

// Framework::CFixedLengthAllocatorContainer: the STL allocator's pools, tried in order (the first
// whose BlockSize() >= n). Guest size 0x18 (operator new(0x18) in CGame::OnInitialize): only the
// TObjectContainer base, whose vtable it keeps (no vtable of its own).
class CFixedLengthAllocatorContainer {
public:
    void Ctor();                         // C1
    void DtorBase();                     // D2: Release, then the base's destructor
    void Release();                      // deletes every allocator (vtable slot 1)
    void Initialize(IFixedLengthAllocator** allocators, u32 count);
    bool IsInitialized() const;          // m_allocators.m_elements != nullptr
    void* pAllocate(u64 size, const char* file, u32 line);
    bool Free(void* p);                  // false: not from these pools
    bool IsMine(void* p) const;
    void EnableMutex();
    void DisableMutex();
    void ReportS();
    void ReportC();
    void ReportL();
    // Native internals (memory_pools.cpp): the pool pAllocate / Free / IsMine pick, with the guest's
    // asserts on the way (nullptr: none).
    IFixedLengthAllocator* AllocatorFor(u64 size);
    IFixedLengthAllocator* AllocatorOwning(void* p) const;

    TObjectContainer<IFixedLengthAllocator*> m_allocators;  // 0x00
};
static_assert(offsetof(CFixedLengthAllocatorContainer, m_allocators) == 0x00);
static_assert(sizeof(CFixedLengthAllocatorContainer) == 0x18);

// Framework::CHandleManager_Base: handles (instance id << 32 | serial) -> u64 values in an
// Aska::THashMap<u32, u64> (containers). Layout from the constructor, Initialize, Register, Refer,
// Unregister, IsIssuedHandle, ~CHandleManager_Base (handles.c). Size: the last field ends at 0x34; no
// allocation site was found (the derived CHandleManager<T> templates embed it), so 0x38 is the
// alignment's rounding.
class CHandleManager_Base {
public:
    void Ctor();                          // C1
    void DtorBase();                      // D2: deletes m_mutex and m_elements (their vtable slot 1)
    void DtorDelete();                    // D0
    void Initialize(u32 capacity, u32 reservedStart, u32 reservedEnd);
    bool IsInitialized() const;           // m_elements != nullptr
    void EnableMutex();
    void* rElementContainer();            // m_elements
    u64 Register(u64 value);              // 0: full
    bool Unregister(u64 handle);
    u64 Refer(u64 handle) const;          // 0: not issued / not found
    bool IsIssuedHandle(u64 handle) const;// m_instanceId == handle >> 32
    void MountAdditionalInformation(u32 a, u32 b);
    void UnmountAdditionalInformation(u64 handle);

    const void* vtable;      // 0x00: _ZTVN9Framework19CHandleManager_BaseE + 0x10
    u32 m_instanceId;        // 0x08: from gInstanceUniqueNumber (handles' high word)
    u8 unk_0c[4];            // 0x0c
    void* m_elements;        // 0x10: Aska::THashMap<u32, u64>* (0x30 bytes, operator new; containers' type)
    CMutex* m_mutex;         // 0x18: EnableMutex's
    u32 m_nextSerial;        // 0x20: the next serial (skips 0 and [m_reservedStart, m_reservedEnd])
    u32 m_capacity;          // 0x24
    u32 m_count;             // 0x28
    u32 m_reservedStart;     // 0x2c
    u32 m_reservedEnd;       // 0x30
    u8 unk_34[4];            // 0x34
};
static_assert(offsetof(CHandleManager_Base, m_instanceId) == 0x08);
static_assert(offsetof(CHandleManager_Base, m_elements) == 0x10);
static_assert(offsetof(CHandleManager_Base, m_mutex) == 0x18);
static_assert(offsetof(CHandleManager_Base, m_nextSerial) == 0x20);
static_assert(offsetof(CHandleManager_Base, m_capacity) == 0x24);
static_assert(offsetof(CHandleManager_Base, m_count) == 0x28);
static_assert(offsetof(CHandleManager_Base, m_reservedStart) == 0x2c);
static_assert(offsetof(CHandleManager_Base, m_reservedEnd) == 0x30);
static_assert(sizeof(CHandleManager_Base) == 0x38);

// Aska::TDynamicQueue<T, false>: a ring buffer of T over a caller's array (capacity = items + 1).
// Guest size 0x20; layout from DeleteManager's Initialize / Clear / AddMain / IsEmpty and its
// destructor (which re-runs the queues' inline constructors: vtable, head = 1, the rest 0).
template <typename T>
class TDynamicQueue {
public:
    const void* vtable;  // 0x00: _ZTVN4Aska13TDynamicQueueI...Lb0EEE + 0x10
    u32 m_write;         // 0x08: the next slot written (push)
    u32 m_read;          // 0x0c: the last slot read (empty when m_write == m_read + 1 mod m_capacity)
    u32 m_capacity;      // 0x10
    u8 unk_14[4];        // 0x14
    T* m_items;          // 0x18
};

class DeletePointerInfo;
using TDynamicQueueDeletePointerInfoPtr = TDynamicQueue<DeletePointerInfo*>;
static_assert(offsetof(TDynamicQueueDeletePointerInfoPtr, m_write) == 0x08);
static_assert(offsetof(TDynamicQueueDeletePointerInfoPtr, m_read) == 0x0c);
static_assert(offsetof(TDynamicQueueDeletePointerInfoPtr, m_capacity) == 0x10);
static_assert(offsetof(TDynamicQueueDeletePointerInfoPtr, m_items) == 0x18);
static_assert(sizeof(TDynamicQueueDeletePointerInfoPtr) == 0x20);

// Aska::DeleteManager::_DeletePointerInfo: one deferred delete (0x18 bytes: Initialize allocates
// queueSize * 0x18 for them; AddMain fills one).
class DeletePointerInfo {
public:
    void DeletePointer();     // _ZN4Aska13DeleteManager18_DeletePointerInfo13DeletePointerEv

    void* m_pointer;          // 0x00
    void* m_handler;          // 0x08: Aska::IDeleteHandler* (nullptr: plain delete)
    u8 m_deferred;            // 0x10: AddMain's 4th argument: 0 -> m_queued, else -> *m_pending
    u8 m_kind;                // 0x11: AddMain's 3rd argument
    u8 unk_12[6];             // 0x12
};
static_assert(offsetof(DeletePointerInfo, m_handler) == 0x08);
static_assert(offsetof(DeletePointerInfo, m_deferred) == 0x10);
static_assert(offsetof(DeletePointerInfo, m_kind) == 0x11);
static_assert(sizeof(DeletePointerInfo) == 0x18);

// Aska::DeleteManager: deletes objects at a safe point of the frame (FlushMain). Guest size 0x138
// (nm -S Aska::Global::m_systemDeleteManager); layout from Initialize / Clear / AddMain / IsEmpty and
// the destructor (delete_manager.c). Initialize: one operator new[] holds the info array and the
// item arrays of the free, queued and pending queues (capacity = queueSize + 1 each).
class DeleteManager {
public:
    void DtorBase();                          // D2
    void DtorDelete();                        // D0
    bool Initialize();                        // queue size from AppProjectDependentProxy
    void Clear();
    bool IsEmpty();
    bool AddMain(void* p, u8 kind, u8 deferred, void* handler);  // Aska::IDeleteHandler*
    bool Cancel(void* p);
    void PreFlushMain();
    void FlushMain();
    void PostFlushMain();

    const void* vtable;                       // 0x00: _ZTVN4Aska13DeleteManagerE + 0x10
    FastCriticalSection m_cs;                 // 0x08: (its lock word at 0x40)
    DeletePointerInfo* m_infoStorage;         // 0x98: the operator new[] block (also the infos)
    DeletePointerInfo* m_infos;               // 0xa0
    TDynamicQueue<DeletePointerInfo*> m_free;     // 0xa8: unused infos (Clear refills it)
    TDynamicQueue<DeletePointerInfo*> m_queued;   // 0xc8: AddMain(deferred = 0)
    TDynamicQueue<DeletePointerInfo*> m_pendingQueue; // 0xe8: AddMain(deferred != 0), via m_pending
    TDynamicQueue<DeletePointerInfo*> m_flushing; // 0x108: being flushed (PreFlushMain / FlushMain)
    TDynamicQueue<DeletePointerInfo*>* m_pending; // 0x128: &m_pendingQueue after Initialize
    s32 m_queueSize;                          // 0x130
    u8 unk_134[4];                            // 0x134
};
static_assert(offsetof(DeleteManager, m_cs) == 0x08);
static_assert(offsetof(DeleteManager, m_infoStorage) == 0x98);
static_assert(offsetof(DeleteManager, m_infos) == 0xa0);
static_assert(offsetof(DeleteManager, m_free) == 0xa8);
static_assert(offsetof(DeleteManager, m_queued) == 0xc8);
static_assert(offsetof(DeleteManager, m_pendingQueue) == 0xe8);
static_assert(offsetof(DeleteManager, m_flushing) == 0x108);
static_assert(offsetof(DeleteManager, m_pending) == 0x128);
static_assert(offsetof(DeleteManager, m_queueSize) == 0x130);
static_assert(sizeof(DeleteManager) == 0x138);

// Aska::TSharedPointerCode: TSharedPointer's reference counters, from a static pool of 256 (a spin
// lock, a count, the counters, a used bitmap, a search hint; no symbol: the addresses in CreateCounter
// / DeleteCounter, delete_manager.c), else operator new(4).
class TSharedPointerCode {
public:
    static s32* CreateCounter(s32 initial);
    static bool DeleteCounter(s32* counter);  // false: a pool slot that wasn't in use
};
class TSharedPointerCodePool {
public:
    s32 m_lock;            // 0x000: 0 free, 1 held (spins; Thread::SleepU(0) every 512 tries)
    s32 m_count;           // 0x004: pool counters in use
    s32 m_counters[256];   // 0x008
    u32 m_used[8];         // 0x408: bit i: m_counters[i] in use
    u32 m_hint;            // 0x428: where the next search starts
};
static_assert(offsetof(TSharedPointerCodePool, m_counters) == 0x008);
static_assert(offsetof(TSharedPointerCodePool, m_used) == 0x408);
static_assert(offsetof(TSharedPointerCodePool, m_hint) == 0x428);
static_assert(sizeof(TSharedPointerCodePool) == 0x42c);

// Aska::MemoryHandleManager: a compacting heap of movable blocks (Aska::_MemoryHandleBlock, 0x48
// bytes) addressed by u32 handles. Not used by the 3.7.0 flows beyond IsAllocated /
// GetAllocatedManager lookups. Guest size: the second FastCriticalSection ends at 0x390 (the constructor;
// no allocation site found). Partial layout from the constructor, InitSrbk, GetBlock, IsAllocated (handles.c).
class MemoryHandleManager {
public:
    void Ctor();                              // C1
    void* GetBlock(u32 handle) const;         // Aska::_MemoryHandleBlock*
    bool IsAllocated(u32 handle, u64* size) const;
    static bool IsAllocated(const void* p, u64* size);
    static MemoryHandleManager* GetAllocatedManager(const void* p, u64* size);
    static u64 CalcSrbkSize(u64 heapSize);    // ((heapSize + 0xff7f) >> 16) * 0x30
    static u64 CalcBlocksSize(s32 blocks);    // blocks * 0x48 + 0x18

    const void* vtable;           // 0x000: _ZTVN4Aska19MemoryHandleManagerE + 0x10
    u8 m_allocHigh;               // 0x008
    u8 unk_009[0x1df];            // 0x009: the constructor zeroes 0x10..0x1e7
    u8* m_srbks;                  // 0x1e8: superblock table (0x30-byte entries; set by InitHeap, not the constructor)
    u32 m_srbkCount;              // 0x1f0
    u8 unk_1f4[4];                // 0x1f4
    void* m_blockChunks;          // 0x1f8: list of {blocks, next, count, first handle} chunks (GetBlock)
    u8 unk_200[0x18];             // 0x200
    u8* m_heap;                   // 0x218
    u64 m_heapSize;               // 0x220
    u8 unk_228[8];                // 0x228
    u8 m_growBlocks;              // 0x230: allocate more block chunks when out
    u8 unk_231[0x7];              // 0x231
    MemoryHandleManager* m_ringHead;  // 0x238
    MemoryHandleManager* m_ringNext;  // 0x240
    MemoryHandleManager* m_ringPrev;  // 0x248
    MemoryHandleManager* m_parent;    // 0x250
    u8 unk_258[0x18];             // 0x258
    FastCriticalSection m_cs;                // 0x270: (IsAllocated)
    FastCriticalSection m_blockCs;           // 0x300: (GetBlock)
};
static_assert(offsetof(MemoryHandleManager, m_srbks) == 0x1e8);
static_assert(offsetof(MemoryHandleManager, m_srbkCount) == 0x1f0);
static_assert(offsetof(MemoryHandleManager, m_blockChunks) == 0x1f8);
static_assert(offsetof(MemoryHandleManager, m_heap) == 0x218);
static_assert(offsetof(MemoryHandleManager, m_heapSize) == 0x220);
static_assert(offsetof(MemoryHandleManager, m_growBlocks) == 0x230);
static_assert(offsetof(MemoryHandleManager, m_ringHead) == 0x238);
static_assert(offsetof(MemoryHandleManager, m_cs) == 0x270);
static_assert(offsetof(MemoryHandleManager, m_blockCs) == 0x300);
static_assert(sizeof(MemoryHandleManager) == 0x390);

// Aska::MappedMemoryManager: the AFF mapping tables (which loaded asset buffers are mapped, relocated
// and by whom). Guest size 0x468 (operator new(0x468, nothrow) in Global::InstantiateMappedMemoryManager,
// which passes the eight AppProjectDependentProxy::GetMappedMemoryManager* sizes). Layout from its
// constructor, which inlines the construction of every member (each a containers class: TPoolLegacy,
// then the TBinaryTree table, then the final vtable), ~MappedMemoryManager, and RemoveHandlerEx
// (port/decomp/memory/mapped.c). The node types are other code's (only pointers to them here).
class MappedMemoryPointer;     // Aska::MappedMemoryPointer (PointerManager's nodes)
class MappedMemoryRelation;    // Aska::MappedMemoryRelation
class MappedMemoryLocation;    // Aska::MappedMemoryLocation
class MappedMemoryIdentifier;  // Aska::MappedMemoryIdentifier
class AUIDNode;                // Aska::AUIDNode
using TCategorizeHashMappedMemoryPointer = containers::TCategorizeHash<MappedMemoryPointer>;
using TCategorizeHashMappedMemoryLocation = containers::TCategorizeHash<MappedMemoryLocation>;
using TCategorizeHashMappedMemoryIdentifier = containers::TCategorizeHash<MappedMemoryIdentifier>;
using THashMappedMemoryRelation = containers::THash<MappedMemoryRelation>;
using THashAUIDNode = containers::THash<AUIDNode>;
static_assert(sizeof(TCategorizeHashMappedMemoryPointer) == 0xa0);  // the next member follows at +0xa0
static_assert(sizeof(THashMappedMemoryRelation) == 0x90);
class MappedMemoryManager {
public:
    // MappedMemoryManager(registerTable, registerPool, mappingTable, mappingPool, handlerTable,
    // handlerPool, returnTable, returnPool): the hash tables' bucket counts and the node pools' sizes
    void Ctor(u32 registerTable, u32 registerPool, u32 mappingTable, u32 mappingPool, u32 handlerTable,
              u32 handlerPool, u32 returnTable, u32 returnPool);  // _ZN4Aska19MappedMemoryManagerC1Ejjjjjjjj
    void DtorBase();     // ~MappedMemoryManager() D1: drops the AUIDElem pool's reference, frees every table
    void DtorDelete();   // D0
    // Methods (none native; the names the decompiles use)
    bool ShouldBeMappedEx(const void* askaFile);
    bool RegisterMappingEx(void* p, void* askaFile, const void** out);
    bool AttachMappingEx(void* p, void* askaFile, const void** out);
    bool DetachMappingEx(void* p, const void* auid, bool flag);
    bool RemoveMappingEx(void* p, bool flag);
    bool MoveMappingEx(void* from, void* to);
    void RemoveHandlerEx(const void* handler);  // Aska::IMappingHandler const*
    void FlushMappingEx();

    const void* vtable;          // 0x000: _ZTVN4Aska19MappedMemoryManagerE + 0x10 (slot 3, +0x18: the deleting
                                 //        destructor Global::DeleteMappedMemoryManager calls)
    CriticalSection m_cs;        // 0x008: (a bionic pthread mutex inside)
    void* m_auidElemPool;        // 0x030: TPoolLegacy<Aska::AUIDElem>* (operator new(0x50), SecurePool(mappingPool));
                                 //        its +0x08 u32 counts references (the destructor deletes it at 0)
    TCategorizeHashMappedMemoryPointer m_pointers;          // 0x038: PointerManager (registerTable / registerPool)
    THashMappedMemoryRelation m_relations;                  // 0x0d8: RelationManager (registerTable / registerPool)
    TCategorizeHashMappedMemoryLocation m_locations;        // 0x168: LocationManager (mappingTable / mappingPool)
    TCategorizeHashMappedMemoryPointer m_handlers;          // 0x208: PointerManager keyed by IMappingHandler*
                                                            //        (RemoveHandlerEx) (handlerTable / handlerPool)
    TCategorizeHashMappedMemoryIdentifier m_identifiers;    // 0x2a8: IdentifierManager: a handler's identifiers
                                                            //        (handlerTable / handlerPool)
    THashAUIDNode m_auids;                                  // 0x348: Aska::AUIDHash (returnTable / returnPool)
    containers::TAddressManagerAddressNode m_addresses;     // 0x3d8: TAddressManager<AddressNode>
                                                            //        (returnTable / returnPool * 4)
};
static_assert(offsetof(MappedMemoryManager, m_cs) == 0x008);
static_assert(offsetof(MappedMemoryManager, m_auidElemPool) == 0x030);
static_assert(offsetof(MappedMemoryManager, m_pointers) == 0x038);
static_assert(offsetof(MappedMemoryManager, m_relations) == 0x0d8);
static_assert(offsetof(MappedMemoryManager, m_locations) == 0x168);
static_assert(offsetof(MappedMemoryManager, m_handlers) == 0x208);
static_assert(offsetof(MappedMemoryManager, m_identifiers) == 0x2a8);
static_assert(offsetof(MappedMemoryManager, m_auids) == 0x348);
static_assert(offsetof(MappedMemoryManager, m_addresses) == 0x3d8);
static_assert(sizeof(MappedMemoryManager) == 0x468);
inline constexpr u64 kVaddrMappedMemoryManager = 0x2ccc5e0;  // Aska::Global::m_pMappedMemoryManager

}  // namespace soa::native::memory

#endif  // SOA_NATIVE_MEMORY_LAYOUT_H
