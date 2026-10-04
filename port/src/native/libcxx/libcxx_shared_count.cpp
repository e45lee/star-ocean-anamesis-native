// std::__ndk1::__shared_count / __shared_weak_count: the out-of-line reference counts of every
// shared_ptr / weak_ptr the game holds (libcxx_layout.h; port/decomp/libcxx/shared_ptr.c).
//
// The counts are "owners - 1" and are changed with LDXR / STXR loops in the guest. The JIT's
// exclusive store is a compare-and-swap on the guest word (runtime/src/core/cpu.cpp,
// MemoryWriteExclusive*), so a host atomic read-modify-write on the same word interleaves
// correctly with guest code still running the inlined increments.
//
// When a count drops from 0 to -1 the block's virtual __on_zero_shared (slot 2) /
// __on_zero_shared_weak (slot 4) runs; those are called through the family (live::ACall), so the
// live check records and replays them (live::out_call).
#include "native/common/live_call.h"
#include "native/libcxx/libcxx_family.h"
#include "native/libcxx/libcxx_layout.h"

namespace soa::native::libcxx {

namespace {

// Slot `slot` of the block's guest vtable, called with the block as `this`.
void call_slot(const void* self, const void* vtable, u32 slot) {
    u64 fn = reinterpret_cast<const u64*>(vtable)[slot];
    live::out_call(family(), fn, {(u64)self});
}

// libc++'s __libcpp_atomic_refcount_increment (relaxed) / _decrement (acq_rel): the old value.
s64 increment(s64& v) { return __atomic_fetch_add(&v, 1, __ATOMIC_RELAXED); }
s64 decrement(s64& v) { return __atomic_fetch_sub(&v, 1, __ATOMIC_ACQ_REL); }

}  // namespace

void shared_count::__add_shared() { increment(shared_owners); }

bool shared_count::__release_shared() {
    if (decrement(shared_owners) != 0) return false;
    call_slot(this, vtable, kSharedSlotOnZeroShared);
    return true;
}

void shared_weak_count::__add_shared() { increment(shared_owners); }
void shared_weak_count::__add_weak() { increment(shared_weak_owners); }

void shared_weak_count::__release_shared() {
    if (decrement(shared_owners) != 0) return;
    call_slot(this, vtable, kSharedSlotOnZeroShared);
    __release_weak();  // (inlined in the guest)
}

void shared_weak_count::__release_weak() {
    if (decrement(shared_weak_owners) != 0) return;
    call_slot(this, vtable, kSharedSlotOnZeroSharedWeak);  // (a tail call in the guest)
}

shared_weak_count* shared_weak_count::lock() {
    s64 n = __atomic_load_n(&shared_owners, __ATOMIC_RELAXED);
    while (n != -1)
        if (__atomic_compare_exchange_n(&shared_owners, &n, n + 1, true, __ATOMIC_RELAXED, __ATOMIC_RELAXED)) return this;
    return nullptr;
}

// ---- natives ----

using live::kInt;
using live::kVoid;

LEAF_METHOD(family(), "_ZNSt6__ndk114__shared_count12__add_sharedEv", &shared_count::__add_shared, sizeof(shared_count), kVoid,
            "std::__shared_count::__add_shared", {});
LEAF_METHOD(family(), "_ZNSt6__ndk114__shared_count16__release_sharedEv", &shared_count::__release_shared, sizeof(shared_count), kInt,
            "std::__shared_count::__release_shared", {});
LEAF_METHOD(family(), "_ZNSt6__ndk119__shared_weak_count12__add_sharedEv", &shared_weak_count::__add_shared, sizeof(shared_weak_count), kVoid,
            "std::__shared_weak_count::__add_shared", {});
LEAF_METHOD(family(), "_ZNSt6__ndk119__shared_weak_count10__add_weakEv", &shared_weak_count::__add_weak, sizeof(shared_weak_count), kVoid,
            "std::__shared_weak_count::__add_weak", {});
LEAF_METHOD(family(), "_ZNSt6__ndk119__shared_weak_count16__release_sharedEv", &shared_weak_count::__release_shared, sizeof(shared_weak_count), kVoid,
            "std::__shared_weak_count::__release_shared", {});
LEAF_METHOD(family(), "_ZNSt6__ndk119__shared_weak_count14__release_weakEv", &shared_weak_count::__release_weak, sizeof(shared_weak_count), kVoid,
            "std::__shared_weak_count::__release_weak", {});
LEAF_METHOD(family(), "_ZNSt6__ndk119__shared_weak_count4lockEv", &shared_weak_count::lock, sizeof(shared_weak_count), kInt,
            "std::__shared_weak_count::lock", {});

}  // namespace soa::native::libcxx
