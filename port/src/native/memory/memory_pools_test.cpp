// Differential tests of the pool natives (memory_pools.cpp) against the 3.7.0 guest.
//
// Private pools built by the guest's constructors (with and without their CMutex), a private
// container over guest-allocated pools: the same pAllocate / Free / IsMine sequence (seeded by the
// test's name) through the guest and through the natives, each from a snapshot of the pool objects and
// block arrays, which must end byte-identical with the same results. The STL allocator's entry points
// run on the live statics through the live check's own machinery (each call checked against the
// guest original under the pool's mutex).
#include <cstring>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/test.h"
#include "native/memory/memory_check.h"
#include "native/memory/memory_heap.h"

using namespace soa;
using namespace soa::native::memory;

namespace {

template <u64 N>
std::string Sym(const char* tail) {
    return "_ZN9Framework21TFixedLengthAllocatorILm" + std::to_string(N) + "EE" + tail;
}
template <u64 N>
std::string SymK(const char* tail) {
    return "_ZNK9Framework21TFixedLengthAllocatorILm" + std::to_string(N) + "EE" + tail;
}

// A pool's whole state: the object and its block array.
template <u64 N>
std::vector<u8> Snap(const TFixedLengthAllocator<N>* a) {
    std::vector<u8> s((const u8*)a, (const u8*)a + sizeof *a);
    const u8* b = (const u8*)a->m_blocks;
    s.insert(s.end(), b, b + a->m_maxBlock * sizeof(TFixedLengthBlock<N>));
    return s;
}
template <u64 N>
void Restore(TFixedLengthAllocator<N>* a, const std::vector<u8>& s) {
    std::memcpy((void*)a, s.data(), sizeof *a);
    std::memcpy((void*)a->m_blocks, s.data() + sizeof *a, a->m_maxBlock * sizeof(TFixedLengthBlock<N>));
}

template <u64 N>
std::vector<u64> RunPool(TestContext& t, TFixedLengthAllocator<N>* a, const std::vector<u64>& ops, bool native) {
    const std::string sAlloc = Sym<N>("9pAllocateEPKcj"), sFree = Sym<N>("4FreeEPv"), sMine = SymK<N>("6IsMineEPv");
    std::vector<u64> out, live;
    u64 foreign = 0;
    for (u64 op : ops) {
        const u64 kind = op % 10;
        u64 r = 0;
        if (kind < 5) {
            r = native ? (u64)a->pAllocate("test", 1) : t.call(sAlloc.c_str(), {(u64)a, (u64) "test", 1});
            if (r) live.push_back(r);
        } else if (kind < 8) {
            if (live.empty()) continue;
            size_t k = (op / 10) % live.size();
            u64 p = live[k];
            live.erase(live.begin() + (long)k);
            native ? a->Free((void*)p) : (void)t.call(sFree.c_str(), {(u64)a, p});
            r = p;
        } else if (kind == 8) {
            // IsMine of a live block, a block's interior, a pointer before / after the array, a foreign one
            u64 p = live.empty() ? (u64)a->m_blocks : live[(op / 10) % live.size()];
            const u64 probes[] = {p, p + 1, (u64)a->m_blocks - 0x10, (u64)a->m_blocks + a->m_maxBlock * sizeof(TFixedLengthBlock<N>), (u64)&foreign};
            for (u64 q : probes) out.push_back(native ? (u64)a->IsMine((void*)q) : t.call(sMine.c_str(), {(u64)a, q}) & 0xff);
            continue;
        } else {
            native ? a->Free(nullptr) : (void)t.call(sFree.c_str(), {(u64)a, 0});
        }
        out.push_back(r);
    }
    return out;
}

template <u64 N>
void PoolRound(TestContext& t, bool mutex, u64 maxBlock) {
    alignas(16) static u8 storage[sizeof(TFixedLengthAllocator<N>)];
    auto* a = reinterpret_cast<TFixedLengthAllocator<N>*>(storage);
    t.call(Sym<N>("C2Ecccm").c_str(), {(u64)a, 'a', 'b', (u64)('0' + N % 10), maxBlock});
    if (mutex) t.call(Sym<N>("11EnableMutexEv").c_str(), {(u64)a});
    std::vector<u64> ops;
    for (int i = 0; i < 3000; i++) ops.push_back(t.rand_u64());
    const auto snap = Snap(a);
    auto g = RunPool(t, a, ops, false);
    const auto after = Snap(a);
    Restore(a, snap);
    auto n = RunPool(t, a, ops, true);
    const auto mine = Snap(a);
    char what[64];
    snprintf(what, sizeof what, "pool<%llu> mutex %d", (unsigned long long)N, mutex);
    if (g != n) t.fail("%s: results differ", what);
    if (after != mine) t.fail("%s: state differs", what);
    t.call(Sym<N>("D2Ev").c_str(), {(u64)a});  // frees the blocks (and the mutex)
}

}  // namespace

NATIVE_TEST("memory/pools-differential") {
    for (bool mutex : {false, true}) {
        PoolRound<16>(t, mutex, 64);
        PoolRound<32>(t, mutex, 200);
        PoolRound<64>(t, mutex, 7);
        PoolRound<128>(t, mutex, 33);
        PoolRound<192>(t, mutex, 1);
        PoolRound<256>(t, mutex, 50);
        PoolRound<512>(t, mutex, 16);
    }
}

// A private container over guest-made pools: pAllocate by size (the first pool that fits), Free / IsMine
// of its blocks, of a heap pointer and of null.
NATIVE_TEST("memory/pools-container-differential") {
    const u64 kSizes[] = {16, 32, 64, 128, 256, 512};
    const u64 kMax[] = {40, 30, 20, 10, 8, 4};
    IFixedLengthAllocator* pools[6];
    for (int i = 0; i < 6; i++) {
        u64 p = t.call("_Znwm", {0x48});
        const u64 n = kSizes[i];
        std::string c2 = "_ZN9Framework21TFixedLengthAllocatorILm" + std::to_string(n) + "EEC2Ecccm";
        t.call(c2.c_str(), {p, 'q', (u64)('0' + i), 'z', kMax[i]});
        pools[i] = (IFixedLengthAllocator*)p;
    }
    alignas(16) static u8 cstorage[sizeof(CFixedLengthAllocatorContainer)];
    auto* c = reinterpret_cast<CFixedLengthAllocatorContainer*>(cstorage);
    t.call("_ZN9Framework30CFixedLengthAllocatorContainerC1Ev", {(u64)c});
    t.call("_ZN9Framework30CFixedLengthAllocatorContainer10InitializeEPPNS_21IFixedLengthAllocatorEj", {(u64)c, (u64)pools, 6});
    u64 heapPtr = t.call("_Znwm", {64});

    auto snapAll = [&] {
        std::vector<u8> s;
        for (int i = 0; i < 6; i++) {
            const u8* o = (const u8*)pools[i];
            s.insert(s.end(), o, o + 0x48);
            const u8* b = *(u8* const*)(o + 0x28);
            s.insert(s.end(), b, b + kMax[i] * (kSizes[i] + 0x10));
        }
        return s;
    };
    auto restoreAll = [&](const std::vector<u8>& s) {
        size_t at = 0;
        for (int i = 0; i < 6; i++) {
            u8* o = (u8*)pools[i];
            std::memcpy(o, s.data() + at, 0x48);
            at += 0x48;
            u8* b = *(u8**)(o + 0x28);
            const size_t len = kMax[i] * (kSizes[i] + 0x10);
            std::memcpy(b, s.data() + at, len);
            at += len;
        }
    };
    std::vector<u64> ops;
    for (int i = 0; i < 4000; i++) ops.push_back(t.rand_u64());
    auto run = [&](bool native) {
        std::vector<u64> out, live;
        for (u64 op : ops) {
            const u64 kind = op % 8;
            if (kind < 4) {
                const u64 size = (op >> 8) % 640;  // (over 512: no pool)
                u64 r = native ? (u64)c->pAllocate(size, "t", 2)
                               : t.call("_ZN9Framework30CFixedLengthAllocatorContainer9pAllocateEmPKcj", {(u64)c, size, (u64) "t", 2});
                if (r) live.push_back(r);
                out.push_back(r);
            } else if (kind < 7) {
                u64 p = heapPtr;
                if (!live.empty() && kind != 6) {
                    size_t k = (op >> 8) % live.size();
                    p = live[k];
                    live.erase(live.begin() + (long)k);
                }
                out.push_back(native ? (u64)c->Free((void*)p) : t.call("_ZN9Framework30CFixedLengthAllocatorContainer4FreeEPv", {(u64)c, p}) & 0xff);
            } else {
                u64 p = live.empty() ? heapPtr : live[(op >> 8) % live.size()];
                out.push_back(native ? (u64)c->IsMine((void*)p) : t.call("_ZNK9Framework30CFixedLengthAllocatorContainer6IsMineEPv", {(u64)c, p}) & 0xff);
            }
        }
        return out;
    };
    const auto snap = snapAll();
    auto g = run(false);
    const auto after = snapAll();
    restoreAll(snap);
    auto n = run(true);
    t.expect_eq(g == n, true, "results");
    t.expect_eq(snapAll() == after, true, "pool state");
    t.expect_eq(c->m_allocators.m_count, (u64)6, "6 pools");
    t.call("_ZdlPv", {heapPtr});
    t.call("_ZN9Framework30CFixedLengthAllocatorContainerD1Ev", {(u64)c});  // deletes the pools
}

// The STL allocator's Allocate / Free on the live statics, each call checked by the live check
// (memory_check.cpp: the pool's mutex held, the native, the state put back, the guest original).
NATIVE_TEST("memory/pools-stl-live-check") {
    using namespace check;
    std::vector<Fn> fns{kStlAllocate, kStlFree, kContainerAllocate, kContainerFree, kContainerIsMine};
    for (u64 n : {16, 32, 64, 128, 192, 256, 512})
        for (int op = 0; op < 3; op++) fns.push_back(PoolFn(n, op));
    for (Fn f : fns) Orig(f) = t.sym(Symbol(f));
    // Allocate's prologue has an ADRP: its original runs through a relocated trampoline when installed;
    // use one here too (runtime's make_original_trampoline relocates the ADRP).
    Orig(kStlAllocate) = make_original_trampoline(t.sym(Symbol(kStlAllocate)));
    t.expect_eq(Orig(kStlAllocate) != 0, true, "Allocate's trampoline");
    // Are the live pools locked by mutexes? (else other threads race with any check)
    auto* c = *reinterpret_cast<CFixedLengthAllocatorContainer**>(main_lib()->base + kVaddrStlFixedLengthContainer);
    if (!t.expect_eq(c != nullptr, true, "STL container")) return;
    for (u64 i = 0; i < c->m_allocators.m_count; i++) {
        auto* a = reinterpret_cast<TFixedLengthAllocator<16>*>(c->m_allocators.m_elements[i]);  // (the mutex field's offset is N-independent)
        t.expect_eq(a->m_mutex != nullptr, true, "live pool has a CMutex");
    }
    const Totals before = GetTotals();
    SetForTest(true, 1);
    std::vector<void*> live;
    for (int i = 0; i < 2000; i++) {
        const u64 size = 1 + (u64)t.rand_int(0, 700);
        if (void* p = CAssignedMemoryManagerForSTLAllocator::Allocate(size, "t", 3)) live.push_back(p);
        if (live.size() > 50 || (i & 3) == 0) {
            size_t k = (size_t)t.rand_int(0, (int)live.size() - 1);
            CAssignedMemoryManagerForSTLAllocator::Free(live[k]);
            live.erase(live.begin() + (long)k);
        }
        if (i % 7 == 0 && !live.empty()) {
            c->IsMine(live.back());
        }
    }
    for (void* p : live) CAssignedMemoryManagerForSTLAllocator::Free(p);
    SetForTest(false, 64);
    for (Fn f : fns) Orig(f) = 0;
    const Totals after = GetTotals();
    t.expect_eq(after.bad - before.bad, (u64)0, "no mismatch");
    t.expect_eq(after.ok - before.ok > 1000, true, "checks ran");
}
