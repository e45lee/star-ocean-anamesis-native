// memory_heap.cpp: Aska::MemoryManager's allocator natives (Malloc, AlignedMalloc, AlignedMallocHigh,
// LocalFree, CalcFreeSize, IsCreated) on the guest's own heap structures.
//
// Readable C++ from the Ghidra decompile (port/decomp/memory/memory_manager.c; the LocalFree notify
// path checked against the disassembly, where Ghidra merged the Signal call into a return). The guest
// layout stays the state: guest code (Realloc, Split, Move, IsEmpty, the MappedMemoryManager, every
// header reader) still walks and edits the same blocks, so every store here is the guest's, in the
// guest's order, including the stale links an allocated block keeps. The lock is the guest's
// FastCriticalSection at m_cs (sync's Enter / Leave: the guest's inlined protocol on the guest's
// words; the JIT's exclusive stores are host CAS), so native and guest heap code exclude each other.
//
// Not native (they share the lock and the layout, so mixing is safe): MallocHigh (never runs in
// 3.7.0's flows; Malloc calls the guest's when m_allocHigh is set), Realloc, Split, Move, IsEmpty,
// CountFreeBlocks, InitHeap / the ring setup, and the 8-to-20-byte leaves (GetMemorySize,
// GetAllocatedManager: a native would cost more than the guest's two instructions).
#include "native/memory/memory_heap.h"

#include "core/cpu.h"
#include "native/common/guest_std.h"
#include "native/common/native_method.h"
#include "native/memory/memory_check.h"

namespace soa::native::memory {

bool g_countBranches = false;
u32 g_branchHits[kHeapBranchCount];
const char* const kHeapBranchNames[kHeapBranchCount] = {
    "MallocExact",       "MallocSplit",      "MallocRunSplit",     "AlignedGapToPrev",       "AlignedGapFree",
    "AlignedExact",      "AlignedRunSplit",  "HighTailFree",       "HighGapToPrev",          "HighRunSplitSmall",
    "HighRunSplitSmallLast", "HighRunSplitFree", "HighRunSplitFreeLast", "FreeSentinelAbsorb", "FreeInsertSorted",
    "FreeBeforeNext",    "FreeMergePrev",    "FreeMergeNext",      "FreeRunMergePrev",       "FreeRunMergeNext",
    "FreeNotify",        "MallocRing",       "MallocBadAlloc",
};

namespace {
constexpr u64 kHeader = sizeof(MemoryBlock);  // 0x40
constexpr u64 kMinSplit = 0x50;              // a remainder under this stays with the block

MemoryBlock* At(void* p, s64 off = 0) { return reinterpret_cast<MemoryBlock*>(static_cast<u8*>(p) + off); }
u8* Bytes(const void* p) { return static_cast<u8*>(const_cast<void*>(p)); }

// The u16 the allocators store at +0x30: m_high, m_used.
template <class St>
void MarkUsed(MemoryBlock* b, bool high, const St& st) {
    st(b->m_high, high ? 1 : 0);
    st(b->m_used, 1);
}

// A run head's sentinel and its one free block after it (the run split's fresh superblock):
// sentinel 0x40 bytes, used; the free block `freeSize` bytes; both rings of two.
template <class St>
void InitRunHead(MemoryBlock* head, u64 freeSize, const St& st) {
    MemoryBlock* f = head + 1;
    st(head->m_high, 0), st(head->m_used, 1);
    st(head->m_notify, nullptr);
    st(f->m_size, freeSize);
    st(f->m_high, 0), st(f->m_used, 0);
    st(f->m_freeNext, head);
    st(f->m_freePrev, head);
    st(f->m_physNext, head);
    st(f->m_physPrev, head);
    st(head->m_freeNext, f);
    st(head->m_freePrev, f);
    st(head->m_size, kHeader);
    st(head->m_physNext, f);
    st(head->m_physPrev, f);
}

const u64& MallocHighFn() {
    static const u64 a = guest::sym("_ZN4Aska13MemoryManager10MallocHighEm");
    return a;
}
}  // namespace

// ---- the lock-held bodies ----

// The largest free block of a run (walking its free list from the sentinel while the links go up).
template <class St>
void MemoryManager::UpdateLargestFree(MemorySrbk* run, const St& st) {
    MemoryBlock* head = RunHead(this, (u64)(run - m_srbks));
    u64 best = 0;
    for (MemoryBlock* b = head->m_freeNext; head < b; b = b->m_freeNext)
        if (b->m_used != 1 && b->m_size > best) best = b->m_size;
    st(run->m_largestFree, best);
}

template <class St>
MemoryBlock* MemoryManager::MallocLocked(u64 need, const St& st) {
    MemorySrbk* srbks = m_srbks;
    u32 idx = 0;
    do {
        MemorySrbk* run = &srbks[idx];
        if (need <= run->m_largestFree) {
            MemoryBlock* head = RunHead(this, idx);
            for (MemoryBlock* b = head->m_freeNext; b != head; b = b->m_freeNext) {
                if (b->m_size < need) continue;
                const u64 rest = b->m_size - need;
                if (rest < kMinSplit) {
                    hit(kMallocExact);
                    st(b->m_freePrev->m_freeNext, b->m_freeNext);
                    st(b->m_freeNext->m_freePrev, b->m_freePrev);
                    need = b->m_size;
                } else {
                    hit(kMallocSplit);
                    MemoryBlock* r = At(b, need);
                    st(r->m_size, rest);
                    st(r->m_used, 0);
                    st(r->m_freePrev, b->m_freePrev);
                    st(r->m_freeNext, b->m_freeNext);
                    st(b->m_freePrev->m_freeNext, r);
                    st(b->m_freeNext->m_freePrev, r);
                    st(b->m_physNext->m_physPrev, r);
                    st(r->m_physNext, b->m_physNext);
                    st(b->m_physNext, r);
                    st(r->m_physPrev, b);
                    st(b->m_size, need);
                }
                st(b->m_owner, this);
                st(b->m_notify, nullptr);
                MarkUsed(b, false, st);
                const u64 before = run->m_allocated;
                st(run->m_allocated, before + need);
                st(run->m_free, run->m_free - need);
                if (before == 0) {
                    // The run's first allocation: the superblocks past the block's end become a run of
                    // their own (when the next superblock is not in use already).
                    u64 end = (u64)(Bytes(b) + b->m_size - Bytes(head));
                    if (head->m_physPrev->m_used != 1) end += kHeader;
                    const u64 span = end < 0xffc1 ? 1 : (end + 0xffff) >> 16;
                    const u64 nidx = span + idx;
                    if (nidx < m_srbkCount && srbks[nidx].m_inUse == 0) {
                        hit(kMallocRunSplit);
                        MemorySrbk* nrun = &srbks[nidx];
                        st(nrun->m_inUse, 1);
                        st(nrun->m_next, run->m_next);
                        st(srbks[run->m_next].m_prev, (u32)nidx);
                        st(run->m_next, (u32)nidx);
                        st(nrun->m_prev, idx);
                        st(nrun->m_allocated, 0);
                        const u64 kept = span * kSrbkSize - run->m_allocated - kHeader;
                        const u64 moved = run->m_free - kept - kHeader;
                        st(nrun->m_free, moved);
                        st(nrun->m_largestFree, moved);
                        MemoryBlock* nhead = RunHead(this, nidx);
                        InitRunHead(nhead, moved, st);
                        st(run->m_free, kept);
                        // The old run's free block that crossed the boundary now ends there.
                        for (MemoryBlock* f = head->m_freeNext; f != head; f = f->m_freeNext) {
                            if (Bytes(nhead) < Bytes(f) + f->m_size) {
                                st(f->m_size, (u64)(Bytes(nhead) - Bytes(f)));
                                break;
                            }
                        }
                    }
                }
                UpdateLargestFree(run, st);
                return b;
            }
        }
        idx = run->m_next;
    } while (idx != 0);
    return nullptr;
}

template <class St>
void* MemoryManager::AlignedMallocLocked(u64 size, s64 align, u64 need, const St& st) {
    MemorySrbk* srbks = m_srbks;
    u32 idx = 0;
    do {
        MemorySrbk* run = &srbks[idx];
        if (need <= run->m_largestFree) {
            MemoryBlock* head = RunHead(this, idx);
            for (MemoryBlock* f = head->m_freeNext; f != head; f = f->m_freeNext) {
                if (f->m_size < need) continue;
                // The lowest aligned data address past f's header that leaves room for `size`.
                const u64 data = ((u64)align + 0x3f + (u64)f) & (u64)-align;
                const u64 fend = f->m_size + (u64)f;
                if (fend < ((size + 0xf + data) & ~u64{0xf})) continue;
                MemoryBlock* b = At((void*)(data - kHeader));
                const u64 gap = (u64)(Bytes(b) - Bytes(f));
                u64 prevTaken = 0;  // gap bytes counted as allocated (given to a used previous block)
                if (gap != 0) {
                    MemoryBlock* physNext = f->m_physNext;
                    MemoryBlock* physPrev = f->m_physPrev;
                    MemoryBlock* freeNext = f->m_freeNext;
                    MemoryBlock* freePrev = f->m_freePrev;
                    st(b->m_used, 0);
                    st(b->m_size, fend - (u64)b);
                    st(b->m_physNext, physNext);
                    st(b->m_freeNext, freeNext);
                    st(physNext->m_physPrev, b);
                    if (gap < kMinSplit) {
                        hit(kAlignedGapToPrev);
                        if (physPrev->m_used != 0) prevTaken = gap;
                        st(physPrev->m_size, physPrev->m_size + gap);
                        st(b->m_physPrev, physPrev);
                        st(b->m_freePrev, freePrev);
                        st(physPrev->m_physNext, b);
                    } else {
                        hit(kAlignedGapFree);
                        st(f->m_size, gap);
                        st(f->m_physNext, b);
                        st(f->m_freeNext, b);
                        st(b->m_physPrev, f);
                        st(b->m_freePrev, f);
                    }
                }
                if (b->m_size - need < kMinSplit) {
                    hit(kAlignedExact);
                    st(b->m_freePrev->m_freeNext, b->m_freeNext);
                    st(b->m_freeNext->m_freePrev, b->m_freePrev);
                    need = b->m_size;
                } else {
                    MemoryBlock* r = At(b, need);
                    st(r->m_size, b->m_size - need);
                    st(r->m_used, 0);
                    st(r->m_freePrev, b->m_freePrev);
                    st(r->m_freeNext, b->m_freeNext);
                    st(b->m_freePrev->m_freeNext, r);
                    st(b->m_freeNext->m_freePrev, r);
                    st(b->m_physNext->m_physPrev, r);
                    st(r->m_physNext, b->m_physNext);
                    st(b->m_physNext, r);
                    st(r->m_physPrev, b);
                    st(b->m_size, need);
                }
                st(b->m_owner, this);
                st(b->m_notify, nullptr);
                MarkUsed(b, false, st);
                const u64 before = run->m_allocated;
                st(run->m_allocated, before + need + prevTaken);
                st(run->m_free, run->m_free - (need + prevTaken));
                if (before == 0) {
                    u64 end = (u64)(Bytes(b) + b->m_size - Bytes(head));
                    if (head->m_physPrev->m_used != 1) end += kHeader;
                    const u64 span = (end >> 6) < 0x3ff ? 1 : (end + 0xffff) >> 16;
                    const u64 nidx = span + idx;
                    if (nidx < m_srbkCount && srbks[nidx].m_inUse == 0) {
                        hit(kAlignedRunSplit);
                        MemorySrbk* nrun = &srbks[nidx];
                        st(nrun->m_inUse, 1);
                        st(nrun->m_next, run->m_next);
                        st(srbks[run->m_next].m_prev, (u32)nidx);
                        st(run->m_next, (u32)nidx);
                        st(nrun->m_prev, idx);
                        st(nrun->m_allocated, 0);
                        const u64 kept = span * kSrbkSize - run->m_allocated - kHeader;
                        const u64 moved = run->m_free - kept - kHeader;
                        st(nrun->m_free, moved);
                        st(nrun->m_largestFree, moved);
                        MemoryBlock* nhead = RunHead(this, nidx);
                        InitRunHead(nhead, moved, st);
                        st(run->m_free, kept);
                        for (MemoryBlock* x = head->m_freeNext; x != head; x = x->m_freeNext) {
                            if (Bytes(nhead) < Bytes(x) + x->m_size) {
                                st(x->m_size, (u64)(Bytes(nhead) - Bytes(x)));
                                break;
                            }
                        }
                    }
                }
                UpdateLargestFree(run, st);
                return (void*)data;
            }
        }
        idx = run->m_next;
    } while (idx != 0);
    return nullptr;
}

template <class St>
void* MemoryManager::AlignedMallocHighLocked(s64 align, u64 need, const St& st) {
    MemorySrbk* srbks = m_srbks;
    u32 idx = srbks[0].m_prev;  // the last run first, backwards through the runs
    do {
        MemorySrbk* run = &srbks[idx];
        if (need <= run->m_largestFree) {
            MemoryBlock* head = RunHead(this, idx);
            for (MemoryBlock* f = head->m_freePrev; f != head; f = f->m_freePrev) {
                const u64 fsize = f->m_size;
                if (fsize < need) continue;
                const u64 data = ((u64)f + (fsize - need)) & (u64)-align;
                if (data < (u64)f + kHeader) continue;
                MemoryBlock* b = At((void*)(data - kHeader));
                MemoryBlock* end = At(b, need);
                const u64 tail = (u64)f + (fsize - (u64)end);
                if (tail < kMinSplit) {
                    need += tail;
                } else {
                    hit(kHighTailFree);
                    st(end->m_size, tail);
                    st(end->m_used, 0);
                    st(end->m_freePrev, f);
                    st(end->m_freeNext, f->m_freeNext);
                    st(f->m_freeNext->m_freePrev, end);
                    st(f->m_freeNext, end);
                    st(f->m_physNext->m_physPrev, end);
                    st(end->m_physNext, f->m_physNext);
                    st(f->m_physNext, end);
                    st(end->m_physPrev, f);
                    st(f->m_size, (u64)(Bytes(end) - Bytes(f)));
                }
                MemoryBlock* physNext = f->m_physNext;
                MemoryBlock* freeNext = f->m_freeNext;
                const u64 gap = (u64)(Bytes(b) - Bytes(f));
                u64 prevTaken = 0;
                MemoryBlock* freePrev;
                if (gap < kMinSplit) {
                    hit(kHighGapToPrev);
                    MemoryBlock* physPrev = f->m_physPrev;
                    freePrev = f->m_freePrev;
                    if (physPrev->m_used != 0) prevTaken = gap;
                    st(physPrev->m_size, physPrev->m_size + gap);
                    st(b->m_physNext, physNext);
                    st(b->m_physPrev, physPrev);
                    st(b->m_freeNext, freeNext);
                    st(b->m_freePrev, freePrev);
                    st(physPrev->m_physNext, b);
                    st(physNext->m_physPrev, b);
                    st(freePrev->m_freeNext, freeNext);
                    // (then freeNext->m_freePrev = freePrev below: the block leaves the free list)
                } else {
                    st(b->m_used, 0);
                    st(b->m_physNext, physNext);
                    st(b->m_freeNext, freeNext);
                    st(physNext->m_physPrev, b);
                    st(f->m_size, gap);
                    st(f->m_physNext, b);
                    st(b->m_physPrev, f);
                    freeNext = b;  // the guest's `puVar24 = puVar27`: b->m_freePrev = f below
                    freePrev = f;
                }
                st(freeNext->m_freePrev, freePrev);
                st(b->m_size, need);
                st(b->m_owner, this);
                st(b->m_notify, nullptr);
                MarkUsed(b, true, st);
                const u64 before = run->m_allocated;
                const u64 taken = prevTaken + need;
                st(run->m_allocated, before + taken);
                st(run->m_free, run->m_free - taken);
                MemorySrbk* target = run;  // the run whose largest free block is recomputed
                if (before == 0 && (gap >> 16) != 0) {
                    // The run's first allocation sits superblocks above its start: those superblocks
                    // (from the one holding the header) become a run of their own; the old run keeps
                    // its sentinel and one free block up to there.
                    const u64 nidx = (gap >> 16) + idx;
                    MemorySrbk* nrun = &srbks[nidx];
                    st(nrun->m_next, run->m_next);
                    const u64 kept = (gap & ~u64{0xffff}) - kHeader;
                    MemoryBlock* nhead = RunHead(this, nidx);
                    st(srbks[run->m_next].m_prev, (u32)nidx);
                    st(run->m_next, (u32)nidx);
                    st(nrun->m_prev, idx);
                    const u64 oldFree = run->m_free;
                    st(run->m_allocated, 0);
                    st(run->m_free, kept);
                    st(run->m_largestFree, kept);
                    MemoryBlock* hf = head + 1;
                    st(head->m_high, 0), st(head->m_used, 1);
                    st(head->m_notify, nullptr);
                    st(hf->m_size, kept);
                    st(hf->m_high, 0), st(hf->m_used, 0);
                    st(hf->m_freeNext, head);
                    st(hf->m_freePrev, head);
                    st(hf->m_physNext, head);
                    st(hf->m_physPrev, head);
                    st(head->m_freeNext, hf);
                    st(head->m_freePrev, hf);
                    st(head->m_size, kHeader);
                    st(head->m_physNext, hf);
                    st(head->m_physPrev, hf);
                    st(nrun->m_inUse, 1);
                    st(nrun->m_allocated, taken);
                    st(nrun->m_free, (oldFree - kHeader) - run->m_free);
                    MemoryBlock* next = b->m_physNext;
                    MemoryBlock* nf = nhead + 1;
                    const u64 lead = (u64)(Bytes(b) - Bytes(nf));
                    MemoryBlock** fix;      // the guest's puVar15: the link finally set to `link`
                    MemoryBlock* link;
                    if (lead < kHeader) {
                        // No room for a free block before the header: the sentinel takes the bytes.
                        st(nhead->m_high, 0), st(nhead->m_used, 1);
                        st(nhead->m_notify, nullptr);
                        st(nhead->m_size, lead + kHeader);
                        st(nrun->m_allocated, nrun->m_allocated + lead);
                        st(nrun->m_free, nrun->m_free - lead);
                        st(nhead->m_physNext, b);
                        if (nhead < next) {
                            hit(kHighRunSplitSmall);
                            st(nhead->m_physPrev, next);
                            st(nhead->m_freeNext, next);
                            st(nhead->m_freePrev, next);
                            st(b->m_physPrev, nhead);
                            st(next->m_physNext, nhead);
                            st(next->m_freeNext, nhead);
                            fix = &next->m_freePrev;
                        } else {
                            hit(kHighRunSplitSmallLast);
                            fix = &b->m_physPrev;
                            st(nhead->m_physPrev, b);
                            st(nhead->m_freeNext, nhead);
                            st(nhead->m_freePrev, nhead);
                            st(b->m_physNext, nhead);
                        }
                        link = nhead;
                    } else {
                        // A sentinel, then a free block up to the header.
                        st(nhead->m_high, 0), st(nhead->m_used, 1);
                        st(nhead->m_freeNext, nf);
                        st(nhead->m_freePrev, nf);
                        st(nhead->m_physNext, nf);
                        st(nhead->m_physPrev, nf);
                        st(nhead->m_notify, nullptr);
                        st(nf->m_size, lead);
                        st(nf->m_high, 0), st(nf->m_used, 0);
                        st(nf->m_physNext, nhead);
                        st(nf->m_physPrev, nhead);
                        st(nf->m_freeNext, nhead);
                        st(nf->m_freePrev, nhead);
                        st(nhead->m_size, kHeader);
                        if (nf < next) {
                            hit(kHighRunSplitFree);
                            st(nhead->m_physPrev, next);
                            st(nhead->m_freeNext, nf);
                            st(nhead->m_freePrev, next);
                            st(nf->m_physNext, b);
                            st(nf->m_physPrev, nhead);
                            st(nf->m_freeNext, next);
                            st(nf->m_freePrev, nhead);
                            st(b->m_physPrev, nf);
                            st(next->m_physNext, nhead);
                            st(next->m_freeNext, nhead);
                            fix = &next->m_freePrev;
                        } else {
                            hit(kHighRunSplitFreeLast);
                            st(nhead->m_physPrev, b);
                            st(nhead->m_freeNext, nf);
                            st(nhead->m_freePrev, nf);
                            st(nf->m_physNext, b);
                            st(nf->m_physPrev, nhead);
                            st(nf->m_freeNext, nhead);
                            st(nf->m_freePrev, nhead);
                            st(b->m_physNext, nhead);
                            fix = &b->m_physPrev;
                        }
                        link = nf;
                    }
                    st(*fix, link);
                    target = nrun;
                }
                UpdateLargestFree(target, st);
                return (void*)data;
            }
        }
        idx = run->m_prev;
    } while (srbks[0].m_prev != idx);
    return nullptr;
}

template <class St>
void MemoryManager::LocalFreeLocked(MemoryBlock* b, const St& st) {
    u64 size = b->m_size;
    // The block's run: the nearest superblock at or below it that starts a run.
    u64 idx = (u64)(Bytes(b) - m_heap) >> 16;
    MemorySrbk* run = nullptr;
    for (s64 i = (s64)idx; i >= 0; i--) {
        run = &m_srbks[i];
        if (run->m_inUse) {
            idx = (u64)i;
            break;
        }
    }
    MemoryBlock* merged;
    MemoryBlock* prev = b->m_physPrev;
    if (prev->m_used == 1) {
        MemoryBlock* head = RunHead(this, idx);
        if (prev == head && head->m_size > kHeader) {
            // The sentinel grew (AlignedMalloc gave it a gap): the block moves down to right after the
            // sentinel and takes those bytes.
            hit(kFreeSentinelAbsorb);
            const u64 extra = head->m_size;
            st(head->m_size, kHeader);
            st(b->m_used, 0);
            const MemoryBlock copy = *b;
            size = size + extra - kHeader;
            MemoryBlock* nb = head + 1;
            st(head->m_physNext, nb);
            st(nb->m_physNext, copy.m_physNext);
            st(nb->m_size, copy.m_size);
            st(nb->m_freeNext, copy.m_freeNext);
            st(nb->m_physPrev, copy.m_physPrev);
            st(nb->m_owner, copy.m_owner);
            st(nb->m_freePrev, copy.m_freePrev);
            st(nb->m_notify, copy.m_notify);
            st(nb->m_high, copy.m_high);
            st(nb->m_used, copy.m_used);
            for (int i = 0; i < 6; i++) st(nb->unk_32[i], copy.unk_32[i]);
            st(nb->m_size, size);
            st(nb->m_freeNext, head->m_freeNext);
            st(head->m_freeNext->m_freePrev, nb);
            st(nb->m_freePrev, head);
            st(head->m_freeNext, nb);
            st(nb->m_physNext->m_physPrev, nb);
            merged = nb;
        } else {
            MemoryBlock* next = b->m_physNext;
            MemoryBlock* before;
            if (next->m_used == 1) {
                // Both neighbours used: into the free list by address.
                hit(kFreeInsertSorted);
                MemoryBlock* at = head;
                do {
                    next = at->m_freeNext;
                    if (b <= next) break;
                    at = next;
                } while (next != head);
                before = next->m_freePrev;
                st(b->m_freeNext, next);
            } else {
                hit(kFreeBeforeNext);
                st(b->m_freeNext, next);
                before = next->m_freePrev;
            }
            st(b->m_freePrev, before);
            st(next->m_freePrev, b);
            st(b->m_freePrev->m_freeNext, b);
            merged = b;
        }
    } else {
        hit(kFreeMergePrev);
        st(prev->m_physNext, b->m_physNext);
        st(b->m_physNext->m_physPrev, prev);
        st(prev->m_size, prev->m_size + size);
        st(b->m_used, 0);
        merged = prev;
    }
    MemoryBlock* nx = merged->m_physNext;
    if (nx->m_used != 1) {
        hit(kFreeMergeNext);
        st(merged->m_size, merged->m_size + nx->m_size);
        st(merged->m_physNext, nx->m_physNext);
        st(merged->m_freeNext, nx->m_freeNext);
        st(merged->m_freePrev->m_freeNext, merged);
        st(nx->m_freeNext->m_freePrev, merged);
        st(nx->m_physNext->m_physPrev, merged);
    }
    st(merged->m_used, 0);

    const u64 allocated = run->m_allocated;
    const u64 freeBytes = run->m_free;
    st(run->m_allocated, allocated - size);
    st(run->m_free, freeBytes + size);
    MemorySrbk* r = run;
    if (allocated - size == 0) {
        // An empty run joins an empty neighbour run (the previous one, then the next one).
        if (run != m_srbks) {
            const u32 pi = run->m_prev;
            if (m_srbks[pi].m_allocated == 0) {
                hit(kFreeRunMergePrev);
                st(run->m_inUse, 0);
                r = &m_srbks[pi];
                const u64 total = freeBytes + size + r->m_free + kHeader;
                st(r->m_free, total);
                st(RunHead(this, pi)->m_freeNext->m_size, total);
                st(r->m_next, run->m_next);
                st(m_srbks[run->m_next].m_prev, pi);
            }
        }
        const u32 ni = r->m_next;
        if (ni != 0 && m_srbks[ni].m_allocated == 0) {
            hit(kFreeRunMergeNext);
            MemorySrbk* n = &m_srbks[ni];
            st(n->m_inUse, 0);
            st(r->m_next, n->m_next);
            st(m_srbks[n->m_next].m_prev, n->m_prev);
            const u64 total = n->m_free + r->m_free + kHeader;
            st(r->m_free, total);
            st(RunHead(this, n->m_prev)->m_freeNext->m_size, total);
        }
    }
    UpdateLargestFree(r, st);
}

template MemoryBlock* MemoryManager::MallocLocked<DirectStore>(u64, const DirectStore&);
template MemoryBlock* MemoryManager::MallocLocked<LoggedStore>(u64, const LoggedStore&);
template void* MemoryManager::AlignedMallocLocked<DirectStore>(u64, s64, u64, const DirectStore&);
template void* MemoryManager::AlignedMallocLocked<LoggedStore>(u64, s64, u64, const LoggedStore&);
template void* MemoryManager::AlignedMallocHighLocked<DirectStore>(s64, u64, const DirectStore&);
template void* MemoryManager::AlignedMallocHighLocked<LoggedStore>(s64, u64, const LoggedStore&);
template void MemoryManager::LocalFreeLocked<DirectStore>(MemoryBlock*, const DirectStore&);
template void MemoryManager::LocalFreeLocked<LoggedStore>(MemoryBlock*, const LoggedStore&);

// ---- the entry points ----

// Malloc / AlignedMalloc*: this manager, then the others of the ring, each under its own lock; when
// none fits, the bad-allocate notify once (it may free memory, or allocate itself), then the ring again.
template <class TryOne>
void* MemoryManager::AllocateFromRing(u64 size, s64 align, TryOne tryOne) {
    s32 retries = 0;
    MemoryManager* m = this;
    for (;;) {
        m->m_cs.Enter();
        void* p = tryOne(m);
        m->m_cs.Leave();
        if (p) {
            if (m != this) hit(kMallocRing);
            return p;
        }
        m = m->m_ringNext;
        if (m != this) continue;
        if (retries > 0 || !m_badAllocNotify) return nullptr;
        hit(kMallocBadAlloc);
        retries++;
        BadAllocateRequest rq{};
        rq.m_manager = this;
        rq.m_size = size;
        rq.m_align = align;
        rq.m_zero18 = 0;
        rq.m_retries = &retries;
        rq.m_result = nullptr;
        const u64* vt = *static_cast<const u64* const*>(m_badAllocNotify);
        guest_call(vt[kBadAllocNotifySlotHandler], {(u64)m_badAllocNotify, (u64)&rq});
        if (rq.m_result) return rq.m_result;
    }
}

void* MemoryManager::Malloc(u64 size) {
    if (size == 0) return nullptr;
    if (m_allocHigh == 1) return (void*)guest_call(MallocHighFn(), {(u64)this, size});
    if (check::Due(check::kMalloc)) {
        if (void* p = check::Malloc(this, size)) return p;  // (nothing in this manager: the ring below)
    }
    const u64 need = (size + 0x4f) & ~u64{0xf};
    return AllocateFromRing(size, 4, [need](MemoryManager* m) -> void* {
        MemoryBlock* b = m->MallocLocked(need, DirectStore{});
        return b ? b->Data() : nullptr;
    });
}

void* MemoryManager::AlignedMalloc(u64 size, s64 align) {
    if (size == 0) return nullptr;
    if (m_allocHigh == 1) return AlignedMallocHigh(size, align);
    if (align < 5) align = 4;
    if (check::Due(check::kAlignedMalloc)) {
        if (void* p = check::AlignedMalloc(this, size, align)) return p;
    }
    const u64 need = (size + 0x4f) & ~u64{0xf};
    return AllocateFromRing(size, align, [=](MemoryManager* m) { return m->AlignedMallocLocked(size, align, need, DirectStore{}); });
}

void* MemoryManager::AlignedMallocHigh(u64 size, s64 align) {
    if (size == 0) return nullptr;
    if (align < 5) align = 4;
    if (check::Due(check::kAlignedMallocHigh)) {
        if (void* p = check::AlignedMallocHigh(this, size, align)) return p;
    }
    const u64 need = (size + 0x4f) & ~u64{0xf};
    return AllocateFromRing(size, align, [=](MemoryManager* m) { return m->AlignedMallocHighLocked(align, need, DirectStore{}); });
}

void MemoryManager::LocalFree(MemoryBlock* b) {
    if (check::Due(check::kLocalFree) && check::LocalFree(this, b)) return;
    m_cs.Enter();
    if (b->m_used != 1) {  // not allocated (a double free): nothing
        m_cs.Leave();
        return;
    }
    if (b->m_notify) {
        // The registered IMemoryNotify hears of it first, outside the lock (it may free other blocks,
        // even this one).
        hit(kFreeNotify);
        m_cs.Leave();
        void* notify = b->m_notify;
        const u64* vt = *static_cast<const u64* const*>(notify);
        guest_call(vt[kMemoryNotifySlotFreeing], {(u64)notify, (u64)b->Data()});
        m_cs.Enter();
        const u8 used = b->m_used;
        b->m_notify = nullptr;
        if (used == 0) {
            m_cs.Leave();
            return;
        }
    }
    LocalFreeLocked(b, DirectStore{});
    m_cs.Leave();
}

void MemoryManager::LocalFree(void* p) {
    MemoryBlock* b = MemoryBlock::FromData(p);
    b->m_owner->LocalFree(b);
}

bool MemoryManager::IsCreated() const {
    FastCriticalSection& cs = const_cast<FastCriticalSection&>(m_cs);
    cs.Enter();
    bool created = false;
    const MemoryManager* m = this;
    do {
        if (m->m_heap) {
            created = true;
            break;
        }
        m = m->m_ringNext;
    } while (m != this);
    cs.Leave();
    return created;
}

s64 MemoryManager::CalcFreeSize(bool onlyThis) {
    if (!IsCreated()) return 0;
    s64 total = 0;
    MemoryManager* m = this;
    do {
        m->m_cs.Enter();
        u32 idx = 0;
        do {
            const MemorySrbk& run = m->m_srbks[idx];
            idx = run.m_next;
            total += (s64)run.m_free + (s64)kHeader;
        } while (idx != 0);
        m->m_cs.Leave();
        m = m->m_ringNext;
    } while (!onlyThis && m != this);
    return total;
}

u64 MemoryManager::CalcFreeSize(s64* heapBytes, s64* usedBytes) const {
    if (!IsCreated()) {
        *heapBytes = 0;
        *usedBytes = 0;
        return 0;
    }
    s64 heap = 0, freeTotal = 0, largest = 0;
    const MemoryManager* m = this;
    do {
        FastCriticalSection& cs = const_cast<FastCriticalSection&>(m->m_cs);
        cs.Enter();
        u32 idx = 0;
        do {
            const MemorySrbk& run = m->m_srbks[idx];
            idx = run.m_next;
            if ((s64)run.m_largestFree > largest) largest = (s64)run.m_largestFree;
            freeTotal += (s64)run.m_free + (s64)kHeader;
        } while (idx != 0);
        cs.Leave();
        heap += (s64)(reinterpret_cast<u8*>(m->m_srbks) - m->m_heap);
        m = m->m_ringNext;
    } while (m != this);
    if (heapBytes) *heapBytes = heap;
    if (usedBytes) *usedBytes = heap - freeTotal;
    const s64 usable = largest - (s64)kHeader;
    return usable < 0 ? 0 : (u64)usable & ~u64{0xf};
}

NATIVE_FUNCTION_ORIG("_ZN4Aska13MemoryManager6MallocEm", wrap_method<&MemoryManager::Malloc>(), "memory: MemoryManager::Malloc",
                     &check::Orig(check::kMalloc));
NATIVE_FUNCTION_ORIG("_ZN4Aska13MemoryManager13AlignedMallocEml", wrap_method<&MemoryManager::AlignedMalloc>(),
                     "memory: MemoryManager::AlignedMalloc", &check::Orig(check::kAlignedMalloc));
NATIVE_FUNCTION_ORIG("_ZN4Aska13MemoryManager17AlignedMallocHighEml", wrap_method<&MemoryManager::AlignedMallocHigh>(),
                     "memory: MemoryManager::AlignedMallocHigh", &check::Orig(check::kAlignedMallocHigh));
NATIVE_FUNCTION_ORIG("_ZN4Aska13MemoryManager9LocalFreeEPNS_12_MemoryBlockE",
                     wrap_method<static_cast<void (MemoryManager::*)(MemoryBlock*)>(&MemoryManager::LocalFree)>(),
                     "memory: MemoryManager::LocalFree(_MemoryBlock*)", &check::Orig(check::kLocalFree));
NATIVE_METHOD("_ZN4Aska13MemoryManager9LocalFreeEPv", static_cast<void (MemoryManager::*)(void*)>(&MemoryManager::LocalFree),
              "memory: MemoryManager::LocalFree(void*)");
NATIVE_FUNCTION_ORIG("_ZNK4Aska13MemoryManager9IsCreatedEv", (check::Getter<check::kIsCreated, wrap_method<&MemoryManager::IsCreated>(), 0xff>),
                     "memory: MemoryManager::IsCreated", &check::Orig(check::kIsCreated));
NATIVE_FUNCTION_ORIG("_ZN4Aska13MemoryManager12CalcFreeSizeEb",
                     (check::Getter<check::kCalcFreeSize, wrap_method<static_cast<s64 (MemoryManager::*)(bool)>(&MemoryManager::CalcFreeSize)>()>),
                     "memory: MemoryManager::CalcFreeSize(bool)", &check::Orig(check::kCalcFreeSize));
NATIVE_METHOD("_ZNK4Aska13MemoryManager12CalcFreeSizeEPlS1_",
              static_cast<u64 (MemoryManager::*)(s64*, s64*) const>(&MemoryManager::CalcFreeSize),
              "memory: MemoryManager::CalcFreeSize(long*, long*)");

}  // namespace soa::native::memory
