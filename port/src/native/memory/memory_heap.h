// memory_heap.h: the internals the heap natives (memory_heap.cpp), their live check
// (memory_check.cpp) and their tests share.
//
// The heap bodies (MemoryManager::*Locked, the code the guest runs between its inlined lock enter and
// leave) store into guest heap state through a Store policy:
//   - DirectStore: the natives (a plain store);
//   - LoggedStore: the live check's dry run, which logs each store's address and old bytes first so
//     the check can put the heap back and run the guest original from the same state (UndoLog).
#ifndef SOA_NATIVE_MEMORY_HEAP_H
#define SOA_NATIVE_MEMORY_HEAP_H

#include <cstring>
#include <vector>

#include "native/memory/memory_layout.h"

namespace soa::native::memory {

struct DirectStore {
    template <typename T, typename V>
    void operator()(T& field, V value) const {
        field = static_cast<T>(value);
    }
};

// The stores of one dry run, oldest first.
class UndoLog {
public:
    struct Entry {
        u8* addr;
        u8 size;
        u8 old[8];
    };
    void save(void* addr, size_t size) {
        Entry e{static_cast<u8*>(addr), static_cast<u8>(size), {}};
        std::memcpy(e.old, addr, size);
        entries_.push_back(e);
    }
    // Puts the old bytes back, newest first.
    void undo() const {
        for (auto it = entries_.rbegin(); it != entries_.rend(); ++it) std::memcpy(it->addr, it->old, it->size);
    }
    const std::vector<Entry>& entries() const { return entries_; }
    void clear() { entries_.clear(); }

private:
    std::vector<Entry> entries_;
};

struct LoggedStore {
    UndoLog* log;
    template <typename T, typename V>
    void operator()(T& field, V value) const {
        static_assert(sizeof(T) <= 8);
        log->save(&field, sizeof(T));
        field = static_cast<T>(value);
    }
};

// Branch counters: which rare paths of the heap bodies ran (the differential tests assert that every
// one did). Counted only while g_countBranches is set (a test), so the natives pay one load.
enum HeapBranch : int {
    kMallocExact,            // Malloc: the remainder under 0x50 stays with the block
    kMallocSplit,            // Malloc: the block split
    kMallocRunSplit,         // Malloc: a run's first allocation splits the run at the next superblock
    kAlignedGapToPrev,       // AlignedMalloc: the alignment gap (< 0x50) goes to the previous block
    kAlignedGapFree,         // AlignedMalloc: the alignment gap (>= 0x50) stays a free block
    kAlignedExact,           // AlignedMalloc: the tail under 0x50 stays with the block
    kAlignedRunSplit,        // AlignedMalloc: the run split
    kHighTailFree,           // AlignedMallocHigh: the tail (>= 0x50) becomes a free block
    kHighGapToPrev,          // AlignedMallocHigh: the head gap (< 0x50) goes to the previous block
    kHighRunSplitSmall,      // AlignedMallocHigh: run split, the header within 0x40 of the new run's sentinel
    kHighRunSplitSmallLast,  //   ... and the block is the run's last
    kHighRunSplitFree,       // AlignedMallocHigh: run split with a free block before the header
    kHighRunSplitFreeLast,   //   ... and the block is the run's last
    kFreeSentinelAbsorb,     // LocalFree: the block after a grown sentinel takes its extra bytes
    kFreeInsertSorted,       // LocalFree: inserted into the free list by address
    kFreeBeforeNext,         // LocalFree: inserted before the free next block
    kFreeMergePrev,          // LocalFree: merged into the free previous block
    kFreeMergeNext,          // LocalFree: merged the free next block
    kFreeRunMergePrev,       // LocalFree: an empty run merged into the empty previous run
    kFreeRunMergeNext,       // LocalFree: the empty next run merged
    kFreeNotify,             // LocalFree: the block's IMemoryNotify called
    kMallocRing,             // Malloc / AlignedMalloc*: served by another manager of the ring
    kMallocBadAlloc,         // Malloc / AlignedMalloc*: the bad-allocate notify called
    kHeapBranchCount
};
extern bool g_countBranches;
extern u32 g_branchHits[kHeapBranchCount];
extern const char* const kHeapBranchNames[kHeapBranchCount];
inline void hit(HeapBranch b) {
    if (__builtin_expect(g_countBranches, 0)) g_branchHits[b]++;
}

// The run's sentinel (its first superblock's first block) for the srbk at `index`.
inline MemoryBlock* RunHead(const MemoryManager* m, u64 index) {
    return reinterpret_cast<MemoryBlock*>(m->m_heap + index * kSrbkSize);
}

}  // namespace soa::native::memory

#endif  // SOA_NATIVE_MEMORY_HEAP_H
