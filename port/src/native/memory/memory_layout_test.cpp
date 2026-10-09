// Layout tests for memory_layout.h (port/PLAN.md task 6, types first): the recovered classes read
// against real guest objects. Each test either builds a private object with the guest's own
// constructor and methods, then compares the fields read through the layout classes with the guest's
// accessors (and with what the test did), or walks a live object of the running game read-only,
// comparing its fields with the guest's getters and with invariants the decompile shows.
// No natives here: in --selftest every t.call reaches the guest code.
#include <cstring>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/test.h"
#include "native/memory/memory_layout.h"

using namespace soa;
using namespace soa::native::memory;

namespace {

template <typename T>
T* at_vaddr(u64 vaddr) {
    return reinterpret_cast<T*>(main_lib()->base + vaddr);
}

u64 vtable_of(TestContext& t, const char* ztv) { return t.sym(ztv) + 0x10; }
// A guest function without arguments (t.call(name, {}) would be ambiguous).
u64 call0(TestContext& t, const char* name) { return guest_call(t.sym(name), std::initializer_list<u64>{}); }

// Calls vtable slot `slot` of the guest object `obj`.
u64 vcall(const void* obj, int slot, std::initializer_list<u64> rest = {}) {
    const u64* vt = *reinterpret_cast<const u64* const*>(obj);
    std::vector<u64> args{(u64)obj};
    args.insert(args.end(), rest.begin(), rest.end());
    GuestArgs ga;
    for (u64 a : args) ga.i(a);
    return guest_call(vt[slot], ga).x0;
}

// Sums the free blocks of the run starting at superblock `idx` by walking its free list from the
// sentinel (the run's first block).
u64 free_list_bytes(const MemoryManager* mm, u32 idx, int* count) {
    auto* sentinel = reinterpret_cast<MemoryBlock*>(mm->m_heap + (u64)idx * kSrbkSize);
    u64 sum = 0;
    *count = 0;
    for (MemoryBlock* b = sentinel->m_freeNext; b != sentinel && *count < 100000; b = b->m_freeNext) {
        sum += b->m_size;
        ++*count;
    }
    return sum;
}

}  // namespace

// A private MemoryManager: constructor, InitHeap, Malloc / LocalFree through the guest, the fields
// through MemoryManager / MemorySrbk / MemoryBlock against the guest's getters and the free lists.
NATIVE_TEST("memory/layout-memory-manager") {
    alignas(16) static u8 storage[sizeof(MemoryManager)];
    std::memset(storage, 0xa5, sizeof storage);
    auto* mm = reinterpret_cast<MemoryManager*>(storage);
    t.call("_ZN4Aska13MemoryManagerC2Ev", {(u64)mm});
    t.expect_eq((u64)mm->vtable, vtable_of(t, "_ZTVN4Aska13MemoryManagerE"), "vtable");
    t.expect_eq(mm->m_ringHead, mm, "ring head = this");
    t.expect_eq(mm->m_ringNext, mm, "ring next = this");
    t.expect_eq(mm->m_ringPrev, mm, "ring prev = this");
    t.expect_eq(mm->m_parent, (MemoryManager*)nullptr, "parent");
    t.expect_eq(mm->m_heap, (u8*)nullptr, "no heap yet");
    t.expect_eq(mm->m_allocHigh, (u8)0, "allocHigh");
    t.expect_eq(t.call("_ZN4Aska13MemoryManager29VirtualGetFastCriticalSectionEv", {(u64)mm}), (u64)&mm->m_cs,
                "GetFastCriticalSection = &m_cs");

    const u64 kHeap = 0x40000;
    if (!t.expect_eq(t.call("_ZN4Aska13MemoryManager8InitHeapEm", {(u64)mm, kHeap}) & 0xff, (u64)1, "InitHeap"))
        return;
    t.expect_eq(mm->m_ownsHeap, (u8)1, "ownsHeap");
    t.expect_eq(mm->m_srbkCount, (u32)((kHeap + 0xffbe) / 0x10028), "srbkCount (InitHeap's formula)");
    t.expect_eq(t.call("_ZNK4Aska13MemoryManager21VirtualGetHeapAddressEv", {(u64)mm}), (u64)mm->m_heap, "GetHeapAddress = m_heap");
    t.expect_eq(t.call("_ZNK4Aska13MemoryManager18VirtualGetHeapSizeEv", {(u64)mm}), mm->m_heapSize, "GetHeapSize = m_heapSize");
    t.expect_eq(t.call("_ZNK4Aska13MemoryManager24VirtualGetTopSrbkAddressEv", {(u64)mm}), (u64)mm->m_srbks, "GetTopSrbkAddress = m_srbks");
    t.expect_eq((u64)mm->m_srbks, (u64)(mm->m_heap + mm->m_heapSize), "srbk table after the superblocks");
    for (u32 i = 0; i < mm->m_srbkCount; i++)
        t.expect_eq(t.call("_ZNK4Aska13MemoryManager14VirtualGetSrbkEi", {(u64)mm, i}), (u64)&mm->m_srbks[i], "GetSrbk(i) = &m_srbks[i]");
    MemorySrbk& s0 = mm->m_srbks[0];
    t.expect_eq(s0.m_inUse, (u8)1, "srbk0 in use");
    t.expect_eq(s0.m_allocated, (u64)0, "srbk0 nothing allocated");
    t.expect_eq(s0.m_free, mm->m_heapSize - 0x40, "srbk0 free = heap - sentinel");
    t.expect_eq(s0.m_largestFree, s0.m_free, "srbk0 largest = free");
    int n = 0;
    t.expect_eq(free_list_bytes(mm, 0, &n), s0.m_free, "free list bytes = srbk0 free");
    t.expect_eq(n, 1, "one free block");
    auto* sentinel = reinterpret_cast<MemoryBlock*>(mm->m_heap);
    t.expect_eq(sentinel->m_size, (u64)0x40, "sentinel size");
    t.expect_eq(sentinel->m_used, (u8)1, "sentinel marked used");

    const u64 kAsk = 100;
    u64 p = t.call("_ZN4Aska13MemoryManager6MallocEm", {(u64)mm, kAsk});
    if (!t.expect_eq(p != 0, true, "Malloc")) return;
    MemoryBlock* b = MemoryBlock::FromData((void*)p);
    t.expect_eq(b, reinterpret_cast<MemoryBlock*>(mm->m_heap + 0x40), "first block right after the sentinel");
    t.expect_eq(b->m_size, (kAsk + 0x4f) & ~u64{0xf}, "block size = (n + 0x4f) & ~0xf");
    t.expect_eq(b->m_owner, mm, "block owner");
    t.expect_eq(b->m_used, (u8)1, "block used");
    t.expect_eq(b->m_physPrev, sentinel, "physPrev = sentinel");
    t.expect_eq(b->m_physNext->m_physPrev, b, "physNext->physPrev = block");
    u64 size_out = 0;
    t.expect_eq(t.call("_ZN4Aska13MemoryManager19GetAllocatedManagerEPKvPm", {p, (u64)&size_out}), (u64)mm, "GetAllocatedManager = m_owner");
    t.expect_eq(size_out, b->m_size, "GetAllocatedManager size = m_size");
    t.expect_eq(t.call("_ZN4Aska13MemoryManager13GetMemorySizeEPKv", {(u64)mm, p}), b->m_size, "GetMemorySize = m_size");
    t.expect_eq(t.call("_ZN4Aska13MemoryManager26VirtualGetAllocatedManagerEPKvPm", {(u64)mm, p, 0}), (u64)mm, "VirtualGetAllocatedManager");
    // Each run: its free list holds what its srbk says; the allocated bytes are the block's.
    u64 allocated = 0;
    u32 idx = 0;
    for (int guard = 0; guard < 64; guard++) {
        MemorySrbk& s = mm->m_srbks[idx];
        t.expect_eq(s.m_inUse, (u8)1, "run head in use");
        t.expect_eq(free_list_bytes(mm, idx, &n), s.m_free, "run free list = srbk free");
        allocated += s.m_allocated;
        if (s.m_next != 0) t.expect_eq(mm->m_srbks[s.m_next].m_prev, idx, "srbk next->prev");
        idx = s.m_next;
        if (idx == 0) break;
    }
    t.expect_eq(allocated, b->m_size, "allocated bytes = the block");

    t.call("_ZN4Aska13MemoryManager9LocalFreeEPv", {(u64)mm, p});
    t.expect_eq(mm->m_srbks[0].m_allocated, (u64)0, "srbk0 allocated after free");
    t.call("_ZN4Aska13MemoryManagerD2Ev", {(u64)mm});
    t.expect_eq(mm->m_heap, (u8*)nullptr, "DeleteHeap cleared m_heap");
}

// The live managers: Global::m_pMemoryManager's ring, CApplicationMemory's getters, the STL allocator's
// statics and its six fixed-length pools.
NATIVE_TEST("memory/layout-live-managers") {
    const u64 mm_vt = vtable_of(t, "_ZTVN4Aska13MemoryManagerE");
    // GetAvailableMemoryManager: Global::m_pMemoryManager, else the mmap'd root heap's manager (the
    // 3.7.0 boot leaves the former null).
    MemoryManager* g = *at_vaddr<MemoryManager*>(kVaddrGlobalMemoryManager);
    if (!g) g = *at_vaddr<MemoryManager*>(kVaddrRootMemoryManager);
    if (!t.expect_eq(g != nullptr, true, "a memory manager")) return;
    t.expect_eq((u64)g, call0(t, "_ZN4Aska6Global25GetAvailableMemoryManagerEv"), "GetAvailableMemoryManager");
    MemoryManager* cur = g;
    for (int i = 0; i < 64; i++) {
        t.expect_eq((u64)cur->vtable, mm_vt, "ring member vtable");
        t.expect_eq(cur->m_ringNext->m_ringPrev, cur, "ring next->prev");
        t.expect_eq(vcall(cur, 9), (u64)cur->m_heap, "ring member GetHeapAddress");
        t.expect_eq(vcall(cur, 19), cur->m_heapSize, "ring member GetHeapSize");
        t.expect_eq(vcall(cur, 16), (u64)cur->m_srbks, "ring member GetTopSrbkAddress");
        cur = cur->m_ringNext;
        if (cur == g) break;
    }
    MemoryManager* root = *at_vaddr<MemoryManager*>(kVaddrRootMemoryManager);
    if (root) t.expect_eq((u64)root->vtable, mm_vt, "root heap's manager vtable");

    auto* am = *at_vaddr<CApplicationMemory*>(kVaddrApplicationMemoryInstance);
    if (t.expect_eq(am != nullptr, true, "TSingleton<CApplicationMemory>")) {
        t.expect_eq(t.call("_ZN9Framework18CApplicationMemory21rPrimaryMemoryManagerEv", {(u64)am}), (u64)am->m_primary, "rPrimary");
        if (am->m_secondary)
            t.expect_eq(t.call("_ZN9Framework18CApplicationMemory23rSecondaryMemoryManagerEv", {(u64)am}), (u64)am->m_secondary, "rSecondary");
        t.expect_eq(t.call("_ZN9Framework18CApplicationMemory22rParticleMemoryManagerEv", {(u64)am}), (u64)am->m_particle, "rParticle");
        t.expect_eq(t.call("_ZN9Framework18CApplicationMemory19rSoundMemoryManagerEv", {(u64)am}), (u64)am->m_sound, "rSound");
        t.expect_eq(t.call("_ZN9Framework18CApplicationMemory21rNetworkMemoryManagerEv", {(u64)am}), (u64)am->m_network, "rNetwork");
        for (MemoryManager* m : {am->m_primary, am->m_particle, am->m_sound, am->m_network})
            if (m) t.expect_eq((u64)m->vtable, mm_vt, "CApplicationMemory manager vtable");
    }

    MemoryManager* stl = *at_vaddr<MemoryManager*>(kVaddrStlMemoryManager);
    t.expect_eq(call0(t, "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator22pAttachedMemoryManagerEv"), (u64)stl, "pAttachedMemoryManager");
    if (stl) {
        t.expect_eq((u64)stl->vtable, mm_vt, "STL manager vtable");
        t.expect_eq((u64)stl->m_badAllocNotify, t.call("_ZN9Framework18CApplicationMemory30rDefaultBadAllocateNotifyRetryEv", {(u64)am}),
                    "STL manager's bad-allocate notify (CreateAndAttach)");
    }
    auto* flc = *at_vaddr<CFixedLengthAllocatorContainer*>(kVaddrStlFixedLengthContainer);
    t.expect_eq(call0(t, "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator27pAttachFixedLengthAllocatorEv"), (u64)flc, "pAttachFixedLengthAllocator");
    if (!t.expect_eq(flc != nullptr, true, "fixed-length container")) return;
    t.expect_eq((u64)flc->m_allocators.vtable, vtable_of(t, "_ZTVN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEEE"), "container vtable");
    t.expect_eq(t.call("_ZNK9Framework30CFixedLengthAllocatorContainer13IsInitializedEv", {(u64)flc}) & 0xff, (u64)1, "IsInitialized");
    t.expect_eq(vcall(flc, 4), flc->m_allocators.m_count, "NumElements (vtable slot 4) = m_count");
    if (!t.expect_eq(flc->m_allocators.m_count, (u64)6, "six pools")) return;
    const u64 sizes[6] = {16, 32, 64, 128, 256, 512};
    for (int i = 0; i < 6; i++) {
        auto* a = reinterpret_cast<TFixedLengthAllocator32*>(flc->m_allocators.m_elements[i]);  // same layout for every N
        t.expect_eq(vcall(a, 2), sizes[i], "BlockSize (slot 2)");
        t.expect_eq(vcall(a, 3), a->m_maxBlock, "MaxBlock (slot 3) = m_maxBlock");
        t.expect_eq(vcall(a, 10), a->m_maxBlock * (sizes[i] + 0x10), "TotalMemoryAmount (slot 10)");
        t.expect_eq(a->m_tag[0], 'm', "tag 0");
        t.expect_eq(a->m_ownsBlocks, (u8)1, "ownsBlocks");
        t.expect_eq(a->m_mutex != nullptr, true, "mutex");
        // Block 0's header: its index and the pool's tags; IsMine(its data) through the guest.
        auto* h = reinterpret_cast<FixedLengthBlockHeader*>(a->m_blocks);
        t.expect_eq(h->m_index, (u32)0, "block 0 index");
        t.expect_eq(std::memcmp(h->m_tag, a->m_tag, 3), 0, "block 0 tags");
        t.expect_eq(vcall(a, 6, {(u64)(h + 1)}) & 0xff, (u64)1, "IsMine(block 0)");
        u64 stride = sizes[i] + 0x10;
        auto* last = reinterpret_cast<FixedLengthBlockHeader*>((u8*)a->m_blocks + (a->m_maxBlock - 1) * stride);
        t.expect_eq(last->m_index, (u32)(a->m_maxBlock - 1), "last block index (stride N + 0x10)");
    }
}

// A private TFixedLengthAllocator<32>: the constructor's block headers, pAllocate / Free through the
// guest, NumAllocated / IsMine against the fields.
NATIVE_TEST("memory/layout-fixed-length-allocator") {
    alignas(16) static u8 storage[sizeof(TFixedLengthAllocator32)];
    std::memset(storage, 0, sizeof storage);
    auto* a = reinterpret_cast<TFixedLengthAllocator32*>(storage);
    const u64 kMax = 8;
    t.call("_ZN9Framework21TFixedLengthAllocatorILm32EEC2Ecccm", {(u64)a, 'x', 'y', 'z', kMax});
    t.expect_eq((u64)a->vtable, vtable_of(t, "_ZTVN9Framework21TFixedLengthAllocatorILm32EEE"), "vtable");
    t.expect_eq(std::memcmp(a->m_tag, "xyz", 3), 0, "tags");
    t.expect_eq(a->m_maxBlock, kMax, "maxBlock");
    t.expect_eq(t.call("_ZNK9Framework21TFixedLengthAllocatorILm32EE8MaxBlockEv", {(u64)a}), a->m_maxBlock, "MaxBlock()");
    t.expect_eq(a->m_numAllocated, (u32)0, "numAllocated");
    t.expect_eq(a->m_freeHead, (u32)0, "freeHead");
    t.expect_eq(a->m_ownsBlocks, (u8)1, "ownsBlocks");
    for (u32 i = 0; i < kMax; i++) {
        const FixedLengthBlockHeader& h = a->m_blocks[i].m_header;
        t.expect_eq(h.m_index, i, "header index");
        t.expect_eq(h.m_next, i + 1 < kMax ? i + 1 : 0xffffffffu, "header next");
        t.expect_eq(h.m_free, (u8)1, "header free");
        t.expect_eq(std::memcmp(h.m_tag, "xyz", 3), 0, "header tags");
    }
    u64 p = t.call("_ZN9Framework21TFixedLengthAllocatorILm32EE9pAllocateEPKcj", {(u64)a, (u64)"layout", 1});
    t.expect_eq(p, (u64)a->m_blocks[0].m_data, "pAllocate = block 0's data");
    t.expect_eq(a->m_numAllocated, (u32)1, "numAllocated after pAllocate");
    t.expect_eq(t.call("_ZNK9Framework21TFixedLengthAllocatorILm32EE12NumAllocatedEv", {(u64)a}) & 0xffffffff, (u64)a->m_numAllocated, "NumAllocated()");
    t.expect_eq(a->m_freeHead, (u32)1, "freeHead after pAllocate");
    t.expect_eq(a->m_blocks[0].m_header.m_free, (u8)0, "block 0 taken");
    t.expect_eq(t.call("_ZNK9Framework21TFixedLengthAllocatorILm32EE6IsMineEPv", {(u64)a, p}) & 0xff, (u64)1, "IsMine");
    t.expect_eq(t.call("_ZNK9Framework21TFixedLengthAllocatorILm32EE16UsedMemoryAmountEv", {(u64)a}), (u64)0x30, "UsedMemoryAmount");
    t.call("_ZN9Framework21TFixedLengthAllocatorILm32EE4FreeEPv", {(u64)a, p});
    t.expect_eq(a->m_numAllocated, (u32)0, "numAllocated after Free");
    t.expect_eq(a->m_freeHead, (u32)0, "freeHead after Free");
    t.expect_eq(a->m_blocks[0].m_header.m_next, (u32)1, "freed block links the old head");
    t.expect_eq(a->m_blocks[0].m_header.m_free, (u8)1, "block 0 free again");
    t.call("_ZN9Framework21TFixedLengthAllocatorILm32EED2Ev", {(u64)a});
    t.expect_eq(a->m_mutex, (void*)nullptr, "DisableMutex via the destructor");
}

// A private CHandleManager_Base: Initialize, Register / Refer / Unregister through the guest.
NATIVE_TEST("memory/layout-handle-manager") {
    alignas(16) static u8 storage[sizeof(CHandleManager_Base)];
    std::memset(storage, 0, sizeof storage);
    auto* h = reinterpret_cast<CHandleManager_Base*>(storage);
    t.call("_ZN9Framework19CHandleManager_BaseC1Ev", {(u64)h});
    t.expect_eq((u64)h->vtable, vtable_of(t, "_ZTVN9Framework19CHandleManager_BaseE"), "vtable");
    t.call("_ZN9Framework19CHandleManager_Base10InitializeEjjj", {(u64)h, 16, 5, 7});
    t.expect_eq(h->m_elements != nullptr, true, "elements map");
    t.expect_eq(t.call("_ZN9Framework19CHandleManager_Base17rElementContainerEv", {(u64)h}), (u64)h->m_elements, "rElementContainer");
    t.expect_eq(h->m_capacity, (u32)16, "capacity");
    t.expect_eq(h->m_reservedStart, (u32)5, "reservedStart");
    t.expect_eq(h->m_reservedEnd, (u32)7, "reservedEnd");
    t.expect_eq(h->m_nextSerial, (u32)1, "first serial");
    t.expect_eq(h->m_count, (u32)0, "count");
    std::vector<u64> handles;
    for (u64 v = 0x1000; v < 0x1006; v++) handles.push_back(t.call("_ZN9Framework19CHandleManager_Base8RegisterEm", {(u64)h, v}));
    t.expect_eq(h->m_count, (u32)6, "count after Register");
    for (size_t i = 0; i < handles.size(); i++) {
        t.expect_eq((u32)(handles[i] >> 32), h->m_instanceId, "handle's high word = instance id");
        u32 serial = (u32)handles[i];
        t.expect_eq(serial >= 5 && serial <= 7, false, "reserved serials skipped");
        t.expect_eq(t.call("_ZNK9Framework19CHandleManager_Base5ReferEm", {(u64)h, handles[i]}), (u64)(0x1000 + i), "Refer");
    }
    t.expect_eq(h->m_nextSerial, (u32)handles.back() + 1, "nextSerial");
    t.call("_ZN9Framework19CHandleManager_Base10UnregisterEm", {(u64)h, handles[0]});
    t.expect_eq(h->m_count, (u32)5, "count after Unregister");
    t.call("_ZN9Framework19CHandleManager_BaseD1Ev", {(u64)h});
    t.expect_eq(h->m_elements, (void*)nullptr, "destructor deleted the map");
}

// The live system DeleteManager: the queues Initialize carved out of one block.
NATIVE_TEST("memory/layout-delete-manager") {
    auto* d = at_vaddr<DeleteManager>(kVaddrSystemDeleteManager);
    t.expect_eq((u64)d->vtable, vtable_of(t, "_ZTVN4Aska13DeleteManagerE"), "vtable");
    if (!t.expect_eq(d->m_infoStorage != nullptr, true, "initialized")) return;
    t.expect_eq(d->m_infos, d->m_infoStorage, "infos = storage");
    t.expect_eq(d->m_pending, &d->m_pendingQueue, "m_pending = &m_pendingQueue");
    const u32 cap = (u32)d->m_queueSize + 1;
    const u64 qvt = vtable_of(t, "_ZTVN4Aska13TDynamicQueueIPNS_13DeleteManager18_DeletePointerInfoELb0EEE");
    auto* items = reinterpret_cast<DeletePointerInfo**>((u8*)d->m_infoStorage + (u64)d->m_queueSize * sizeof(DeletePointerInfo));
    const TDynamicQueue<DeletePointerInfo*>* qs[4] = {&d->m_free, &d->m_queued, &d->m_pendingQueue, &d->m_flushing};
    for (int i = 0; i < 4; i++) {
        t.expect_eq((u64)qs[i]->vtable, qvt, "queue vtable");
        t.expect_eq(qs[i]->m_capacity, cap, "queue capacity = size + 1");
        t.expect_eq(qs[i]->m_items, items + (u64)i * cap, "queue items carved in order");
    }
    // Every info the free queue's array points at lies in the info array.
    for (u32 i = 0; i < cap; i++) {
        DeletePointerInfo* p = d->m_free.m_items[i];
        if (!p) continue;
        bool in = p >= d->m_infos && p < d->m_infos + d->m_queueSize && ((u8*)p - (u8*)d->m_infos) % sizeof(DeletePointerInfo) == 0;
        t.expect_eq(in, true, "free item inside the info array");
    }
}

// TSharedPointerCode's static pool: a counter from CreateCounter is a pool slot holding the value, with
// its used bit set; DeleteCounter clears the bit.
NATIVE_TEST("memory/layout-shared-pointer-code") {
    auto* pool = at_vaddr<TSharedPointerCodePool>(kVaddrSharedPointerCodePool);
    const s32 kValue = 0x5a5a;
    auto* c = (s32*)t.call("_ZN4Aska18TSharedPointerCode13CreateCounterEi", {(u64)kValue});
    if (!t.expect_eq(c != nullptr, true, "CreateCounter")) return;
    t.expect_eq(*c, kValue, "counter value");
    if (c >= pool->m_counters && c < pool->m_counters + 256) {
        size_t i = c - pool->m_counters;
        t.expect_eq((pool->m_used[i / 32] >> (i % 32)) & 1, 1u, "used bit set");
        t.expect_eq(t.call("_ZN4Aska18TSharedPointerCode13DeleteCounterEPi", {(u64)c}) & 0xff, (u64)1, "DeleteCounter");
        t.expect_eq((pool->m_used[i / 32] >> (i % 32)) & 1, 0u, "used bit cleared");
    } else {
        // The pool was full (256 live counters): CreateCounter fell back to operator new(4).
        t.call("_ZN4Aska18TSharedPointerCode13DeleteCounterEPi", {(u64)c});
    }
}

// MemoryManagerHelper / MemoryHandleManager: the constructors' fields; InitMemoryManager's manager.
NATIVE_TEST("memory/layout-helpers") {
    alignas(16) static u8 hs[sizeof(MemoryManagerHelper)];
    std::memset(hs, 0xa5, sizeof hs);
    auto* h = reinterpret_cast<MemoryManagerHelper*>(hs);
    t.call("_ZN4Aska19MemoryManagerHelperC1Ev", {(u64)h});
    t.expect_eq((u64)h->vtable, vtable_of(t, "_ZTVN4Aska19MemoryManagerHelperE"), "helper vtable");
    t.expect_eq(h->m_manager, (MemoryManager*)nullptr, "helper manager");
    t.expect_eq(h->m_srbks, (u8*)nullptr, "helper srbks");
    t.expect_eq(t.call("_ZN4Aska19MemoryManagerHelper17InitMemoryManagerEm", {(u64)h, 0x20000}) & 0xff, (u64)1, "InitMemoryManager");
    if (t.expect_eq(h->m_manager != nullptr, true, "helper's manager")) {
        t.expect_eq((u64)h->m_manager->vtable, vtable_of(t, "_ZTVN4Aska13MemoryManagerE"), "helper's manager vtable");
        t.expect_eq(h->m_manager->m_ownsHeap, (u8)1, "helper's manager owns its heap");
    }
    t.call("_ZN4Aska19MemoryManagerHelper19CleanupMemoryManaerEv", {(u64)h});
    t.expect_eq(h->m_manager, (MemoryManager*)nullptr, "CleanupMemoryManaer");
    // (No destructor: it would set Global::m_pMemoryManager to m_savedGlobal.)

    alignas(16) static u8 ms[sizeof(MemoryHandleManager)];
    std::memset(ms, 0xa5, sizeof ms);
    auto* m = reinterpret_cast<MemoryHandleManager*>(ms);
    t.call("_ZN4Aska19MemoryHandleManagerC1Ev", {(u64)m});
    t.expect_eq((u64)m->vtable, vtable_of(t, "_ZTVN4Aska19MemoryHandleManagerE"), "handle manager vtable");
    t.expect_eq(m->m_ringHead, m, "ring head");
    t.expect_eq(m->m_ringNext, m, "ring next");
    t.expect_eq(m->m_ringPrev, m, "ring prev");
    t.expect_eq(m->m_parent, (MemoryHandleManager*)nullptr, "parent");
    t.expect_eq(m->m_blockChunks, (void*)nullptr, "block chunks");
    t.expect_eq(m->m_heap, (u8*)nullptr, "heap");
    t.call("_ZN4Aska19MemoryHandleManagerD1Ev", {(u64)m});
}

// Aska::MappedMemoryManager: a private one built by the guest's constructor with small, distinct sizes
// (each member's table size and pool capacity read back through the containers' classes), the
// PointerManager / TAddressManager members used through the guest's own Register / IsRegistered, then
// the guest's destructor; and the live one (Global::m_pMappedMemoryManager) against the sizes
// AppProjectDependentProxy hands InstantiateMappedMemoryManager.
NATIVE_TEST("memory/layout-mapped-memory-manager") {
    namespace containers = soa::native::containers;
    using containers::TPoolLegacy;
    alignas(16) static u8 storage[sizeof(MappedMemoryManager)];
    std::memset(storage, 0xa5, sizeof storage);
    auto* m = reinterpret_cast<MappedMemoryManager*>(storage);
    // registerTable, registerPool, mappingTable, mappingPool, handlerTable, handlerPool, returnTable, returnPool
    const u32 sz[8] = {3, 5, 7, 9, 11, 13, 17, 19};
    GuestArgs ga;
    ga.i((u64)m);
    for (u32 v : sz) ga.i(v);
    t.call("_ZN4Aska19MappedMemoryManagerC1Ejjjjjjjj", ga);
    t.expect_eq((u64)m->vtable, vtable_of(t, "_ZTVN4Aska19MappedMemoryManagerE"), "vtable");
    auto vt = [](const void* member) { return (u64) * reinterpret_cast<const void* const*>(member); };
    t.expect_eq(vt(&m->m_pointers), vtable_of(t, "_ZTVN4Aska19MappedMemoryManager14PointerManagerE"), "0x038 PointerManager");
    t.expect_eq(vt(&m->m_relations), vtable_of(t, "_ZTVN4Aska19MappedMemoryManager15RelationManagerE"), "0x0d8 RelationManager");
    t.expect_eq(vt(&m->m_locations), vtable_of(t, "_ZTVN4Aska19MappedMemoryManager15LocationManagerE"), "0x168 LocationManager");
    t.expect_eq(vt(&m->m_handlers), vtable_of(t, "_ZTVN4Aska19MappedMemoryManager14PointerManagerE"), "0x208 PointerManager");
    t.expect_eq(vt(&m->m_identifiers), vtable_of(t, "_ZTVN4Aska19MappedMemoryManager17IdentifierManagerE"), "0x2a8 IdentifierManager");
    t.expect_eq(vt(&m->m_auids), vtable_of(t, "_ZTVN4Aska8AUIDHashE"), "0x348 AUIDHash");
    t.expect_eq(vt(&m->m_addresses), vtable_of(t, "_ZTVN4Aska15TAddressManagerINS_11AddressNodeEEE"), "0x3d8 TAddressManager");
    // Bucket counts and pool capacities (the ctor's argument -> member mapping).
    t.expect_eq(m->m_pointers.base.base.m_tableSize, sz[0], "pointers table = registerTable");
    t.expect_eq(m->m_pointers.base.base.base.m_used.m_numBits, sz[1], "pointers pool = registerPool");
    t.expect_eq(m->m_relations.base.m_tableSize, sz[0], "relations table = registerTable");
    t.expect_eq(m->m_relations.base.base.m_used.m_numBits, sz[1], "relations pool = registerPool");
    t.expect_eq(m->m_locations.base.base.m_tableSize, sz[2], "locations table = mappingTable");
    t.expect_eq(m->m_locations.base.base.base.m_used.m_numBits, sz[3], "locations pool = mappingPool");
    t.expect_eq(m->m_handlers.base.base.m_tableSize, sz[4], "handlers table = handlerTable");
    t.expect_eq(m->m_handlers.base.base.base.m_used.m_numBits, sz[5], "handlers pool = handlerPool");
    t.expect_eq(m->m_identifiers.base.base.m_tableSize, sz[4], "identifiers table = handlerTable");
    t.expect_eq(m->m_identifiers.base.base.base.m_used.m_numBits, sz[5], "identifiers pool = handlerPool");
    t.expect_eq(m->m_auids.base.m_tableSize, sz[6], "auids table = returnTable");
    t.expect_eq(m->m_auids.base.base.m_used.m_numBits, sz[7], "auids pool = returnPool");
    t.expect_eq(m->m_addresses.base.base.m_tableSize, sz[6], "addresses table = returnTable");
    t.expect_eq(m->m_addresses.base.base.base.m_used.m_numBits, sz[7] * 4, "addresses pool = returnPool * 4");
    if (t.expect_eq(m->m_auidElemPool != nullptr, true, "AUIDElem pool")) {
        auto* pool = reinterpret_cast<TPoolLegacy<containers::Opaque<8>>*>(m->m_auidElemPool);
        t.expect_eq(pool->m_used.m_numBits, sz[3], "AUIDElem pool = mappingPool");
        t.expect_eq(*reinterpret_cast<u32*>(pool->unk_08), 1u, "AUIDElem pool: one reference");
    }
    // The members work as the classes say: PointerManager::Register adds a node to m_pointers' list,
    // TAddressManager::Register one to m_addresses'.
    static u64 key = 0x1234;
    t.call("_ZN4Aska19MappedMemoryManager14PointerManager8RegisterEPKv", {(u64)&m->m_pointers, (u64)&key});
    t.expect_eq(t.call("_ZN4Aska19MappedMemoryManager14PointerManager12IsRegisteredEPKv", {(u64)&m->m_pointers, (u64)&key}) & 0xff, (u64)1,
                "PointerManager IsRegistered");
    t.expect_eq(m->m_pointers.base.base.m_nodeCount, 1u, "m_pointers: one node");
    t.expect_eq(m->m_handlers.base.base.m_nodeCount, 0u, "m_handlers untouched");
    t.call("_ZN4Aska15TAddressManagerINS_11AddressNodeEE8RegisterEPKv", {(u64)&m->m_addresses, (u64)&key});
    t.expect_eq(m->m_addresses.base.base.m_nodeCount, 1u, "m_addresses: one node");
    t.call("_ZN4Aska19MappedMemoryManagerD1Ev", {(u64)m});

    // The live one: the proxy's sizes.
    auto* live = *at_vaddr<MappedMemoryManager*>(kVaddrMappedMemoryManager);
    if (!live) return;  // not instantiated in this build's boot
    t.expect_eq((u64)live->vtable, vtable_of(t, "_ZTVN4Aska19MappedMemoryManagerE"), "live vtable");
    alignas(16) u8 proxy[64] = {};
    t.call("_ZN4Aska24AppProjectDependentProxyC1Ev", {(u64)proxy});
    auto get = [&](const char* s) { return (u32)t.call(s, {(u64)proxy}); };
    u32 regTable = get("_ZNK4Aska24AppProjectDependentProxy35GetMappedMemoryManagerRegisterTableEv");
    u32 mapTable = get("_ZNK4Aska24AppProjectDependentProxy34GetMappedMemoryManagerMappingTableEv");
    u32 hTable = get("_ZNK4Aska24AppProjectDependentProxy34GetMappedMemoryManagerHandlerTableEv");
    u32 retTable = get("_ZNK4Aska24AppProjectDependentProxy33GetMappedMemoryManagerReturnTableEv");
    u32 retPool = get("_ZNK4Aska24AppProjectDependentProxy32GetMappedMemoryManagerReturnPoolEv");
    t.call("_ZN4Aska24AppProjectDependentProxyD1Ev", {(u64)proxy});
    auto bucket = [](u32 want) { return want < 2 ? 1u : want; };  // the ctor's single inline slot
    t.expect_eq(live->m_pointers.base.base.m_tableSize, bucket(regTable), "live pointers table");
    t.expect_eq(live->m_locations.base.base.m_tableSize, bucket(mapTable), "live locations table");
    t.expect_eq(live->m_handlers.base.base.m_tableSize, bucket(hTable), "live handlers table");
    t.expect_eq(live->m_auids.base.m_tableSize, bucket(retTable), "live auids table");
    t.expect_eq(live->m_addresses.base.base.base.m_used.m_numBits, retPool * 4, "live addresses pool");
}

// The heap's callback slots (memory_layout.h kBadAllocNotifySlotHandler / kMemoryNotifySlotFreeing): the
// bad-allocation handler's vtable as CApplicationMemory's (Framework::CBadAllocateNotifyRetry) has it.
NATIVE_TEST("memory/notify-slots") {
    auto* vt = (const u64*)(t.sym("_ZTVN9Framework23CBadAllocateNotifyRetryE") + 0x10);
    t.expect_eq(vt[kBadAllocNotifySlotHandler], t.sym("_ZN9Framework23CBadAllocateNotifyRetry7HandlerEm"),
                "slot 0: CBadAllocateNotifyRetry::Handler(unsigned long)");
}
