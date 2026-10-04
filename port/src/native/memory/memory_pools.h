// memory_pools.h: the internals the pool natives (memory_pools.cpp) and their live check share.
#ifndef SOA_NATIVE_MEMORY_POOLS_H
#define SOA_NATIVE_MEMORY_POOLS_H

#include "native/memory/memory_layout.h"

namespace soa::native::memory {

// A pool's Framework::CMutex for a scope: the guest's IsInitialized / Initialize / Lock ... Unlock
// (sync's class; recursive: the owner may enter again). Nothing when `mutex` is null.
class PoolLock {
public:
    explicit PoolLock(void* mutex);
    ~PoolLock();
    PoolLock(const PoolLock&) = delete;
    PoolLock& operator=(const PoolLock&) = delete;

private:
    void* m_;
};

// CAssignedMemoryManagerForSTLAllocator::Allocate / Free without the live check (its fallback).
void* StlAllocateUnchecked(u64 size, const char* file, u32 line);
void StlFreeUnchecked(void* p);  // (p non-null)

// The seven TFixedLengthAllocator<N> vtables (+0x10), N = 16, 32, 64, 128, 192, 256, 512.
const u64* PoolVtables();

// Runs f on the allocator as its TFixedLengthAllocator<N> when its vtable is one of the seven and
// returns true; false (f not run) for any other class.
template <class F>
bool WithPool(const IFixedLengthAllocator* a, F&& f) {
    const u64 vt = (u64)a->vtable;
    const u64* known = PoolVtables();
    auto* p = const_cast<IFixedLengthAllocator*>(a);
    if (vt == known[0]) return f(reinterpret_cast<TFixedLengthAllocator<16>*>(p)), true;
    if (vt == known[1]) return f(reinterpret_cast<TFixedLengthAllocator<32>*>(p)), true;
    if (vt == known[2]) return f(reinterpret_cast<TFixedLengthAllocator<64>*>(p)), true;
    if (vt == known[3]) return f(reinterpret_cast<TFixedLengthAllocator<128>*>(p)), true;
    if (vt == known[4]) return f(reinterpret_cast<TFixedLengthAllocator<192>*>(p)), true;
    if (vt == known[5]) return f(reinterpret_cast<TFixedLengthAllocator<256>*>(p)), true;
    if (vt == known[6]) return f(reinterpret_cast<TFixedLengthAllocator<512>*>(p)), true;
    return false;
}

}  // namespace soa::native::memory

#endif  // SOA_NATIVE_MEMORY_POOLS_H
