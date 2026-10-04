// memory_check.h: the live check of the memory natives (soa --live-check memory[:every=N][:budget=N]
// [:only=SUB|..][:out=FILE]).
//
// The record / replay check of live_check.h can't replay an allocator: the guest original would run
// on the real heap (its effects on memory other threads use can't be rewound), and the heap's
// FastCriticalSection isn't recursive, so the original can't even enter while the check holds it.
// So a checked call, with the real lock held for the whole check:
//   - heap (Malloc, AlignedMalloc, AlignedMallocHigh, LocalFree): the native body runs as a dry run
//     whose stores are logged (LoggedStore), its result and the bytes it wrote (and the manager's
//     whole superblock table) are recorded, then the log is undone; the guest original then runs on a
//     *shadow* of the manager (its 0xf0 bytes with a free lock word, a ring of itself, no bad-allocate
//     notify) over the same heap, and its result, the bytes at every logged address and the srbk
//     table must equal the native's. The guest's stores are the ones that stay (with the block owner
//     the guest wrote, the shadow's address, put back to the manager);
//   - fixed-length pools (pAllocate, Free; the container's and the STL allocator's dispatch to them):
//     their Framework::CMutex is recursive, so the check holds it, runs the native, records, undoes it
//     with the inverse operation (Free after pAllocate, pAllocate after Free: exact on this layout;
//     checked), then the guest original runs for real and must leave the same bytes and result;
//   - read-only functions (IsCreated, CalcFreeSize(bool), the IsMine family, NumElements): the native,
//     then the original on the same object; a difference a rerun doesn't reproduce is a race.
// Not checked (counted as skipped): a call the native served from another manager of the ring or after
// the bad-allocate notify (the shadow is alone; the rest runs natively), a LocalFree of a block with a
// registered IMemoryNotify (the guest unlocks in the middle), STL allocations served by the heap
// (checked as Malloc / LocalFree themselves).
#ifndef SOA_NATIVE_MEMORY_CHECK_H
#define SOA_NATIVE_MEMORY_CHECK_H

#include <atomic>

#include "core/cpu.h"
#include "native/memory/memory_layout.h"

namespace soa::native::memory::check {

// The checked functions.
enum Fn : int {
    kMalloc,
    kAlignedMalloc,
    kAlignedMallocHigh,
    kLocalFree,
    kIsCreated,
    kCalcFreeSize,
    kContainerAllocate,
    kContainerFree,
    kContainerIsMine,
    kNumElements,
    kStlAllocate,
    kStlFree,
    kPoolFirst,  // TFixedLengthAllocator<N>: kPoolFirst + 3 * PoolIndex(N) + {0 pAllocate, 1 Free, 2 IsMine}
    kFnCount = kPoolFirst + 3 * 7
};
constexpr int PoolIndex(u64 n) {
    return n == 16 ? 0 : n == 32 ? 1 : n == 64 ? 2 : n == 128 ? 3 : n == 192 ? 4 : n == 256 ? 5 : 6;
}
constexpr Fn PoolFn(u64 n, int op) { return static_cast<Fn>(kPoolFirst + 3 * PoolIndex(n) + op); }

// The family's switch (live::Family::on of --live-check memory): one relaxed load when off.
extern std::atomic<bool>& g_on;
bool DueSlow(Fn f);
inline bool Due(Fn f) { return __builtin_expect(g_on.load(std::memory_order_relaxed), 0) && DueSlow(f); }
// The trampoline to function f's guest original (NATIVE_FUNCTION_ORIG fills it at install).
u64& Orig(Fn f);

// Heap checks (the calls Due chose), on this manager only: nullptr when neither the native nor the
// guest found room in it (the caller then goes on through the ring natively). LocalFree returns
// false when it didn't free (the caller then runs the normal path).
void* Malloc(MemoryManager* m, u64 size);
void* AlignedMalloc(MemoryManager* m, u64 size, s64 align);
void* AlignedMallocHigh(MemoryManager* m, u64 size, s64 align);
bool LocalFree(MemoryManager* m, MemoryBlock* b);

// Pool checks.
template <u64 N>
void* PoolAllocate(TFixedLengthAllocator<N>* a, const char* file, u32 line);
template <u64 N>
void PoolFree(TFixedLengthAllocator<N>* a, void* p);
void* ContainerAllocate(CFixedLengthAllocatorContainer* c, u64 size, const char* file, u32 line);
bool ContainerFree(CFixedLengthAllocatorContainer* c, void* p);
void* StlAllocate(u64 size, const char* file, u32 line);
void StlFree(void* p);

// A read-only native's HostFn wrapped in the getter check (native, then the original, x0 compared).
void CheckGetter(Cpu& c, Fn f, HostFn native, u64 mask);
template <Fn F, HostFn Native, u64 Mask = ~u64{0}>
void Getter(Cpu& c) {
    if (Due(F)) return CheckGetter(c, F, Native, Mask);
    Native(c);
}

// For the tests (--selftest installs no natives, so the guest symbols are the originals: a test sets
// Orig(f) to them and back to 0): the family's switch, every=, and its totals.
struct Totals {
    u64 checks, ok, bad, skipped, races;
};
Totals GetTotals();
void SetForTest(bool on, int every);
const char* Symbol(Fn f);

}  // namespace soa::native::memory::check

#endif  // SOA_NATIVE_MEMORY_CHECK_H
