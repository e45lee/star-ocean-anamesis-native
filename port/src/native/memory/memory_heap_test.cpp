// Differential tests of the heap natives (memory_heap.cpp) against the 3.7.0 guest.
//
// Private heaps: a MemoryManager built by the guest's constructor over a host buffer (InitHeap(u8*,
// u64): every pointer in the heap is an address in the buffer, so two runs from the same snapshot
// are comparable byte for byte). The same operation sequence (seeded by the test's name) runs through
// the guest's functions and through the natives, each from the snapshot; their results and the whole
// manager + heap bytes must be equal. The rare paths are counted (memory_heap.h's branch counters)
// and every one must have run.
#include <algorithm>
#include <atomic>
#include <cstring>
#include <thread>
#include <vector>

#include "core/cpu.h"
#include "native/common/test.h"
#include "native/memory/memory_check.h"
#include "native/memory/memory_heap.h"

using namespace soa;
using namespace soa::native::memory;

namespace {

constexpr const char* kCtor = "_ZN4Aska13MemoryManagerC2Ev";
constexpr const char* kInitHeap = "_ZN4Aska13MemoryManager8InitHeapEPhm";
constexpr const char* kAdd = "_ZN4Aska13MemoryManager3AddEPS0_";
constexpr const char* kRet = "_ZN4Aska13MemoryManager9ClearHeapEv";  // a lone `ret` (a do-nothing callback)

// One or two managers (a ring) over host buffers, all in one storage block (snapshot = a copy of it).
struct Heaps {
    std::vector<u8> storage;
    MemoryManager* m[2] = {};
    u8* buf[2] = {};
    u64 size[2] = {};
    int count = 0;

    static u8* Align(u8* p, u64 a) { return reinterpret_cast<u8*>(((u64)p + a - 1) & ~(a - 1)); }
    void Build(TestContext& t, u64 size0, u64 size1 = 0) {
        count = size1 ? 2 : 1;
        storage.assign(0x400 + size0 + size1 + 0x100, 0);
        u8* p = Align(storage.data(), 0x40);
        for (int i = 0; i < count; i++) {
            m[i] = reinterpret_cast<MemoryManager*>(p);
            p += 0x100;
        }
        size[0] = size0, size[1] = size1;
        for (int i = 0; i < count; i++) {
            buf[i] = Align(p, 0x10);
            p = buf[i] + size[i] + 0x10;
            t.call(kCtor, {(u64)m[i]});
            t.expect_eq(t.call(kInitHeap, {(u64)m[i], (u64)buf[i], size[i]}) & 0xff, (u64)1, "InitHeap");
        }
        if (count == 2) t.call(kAdd, {(u64)m[0], (u64)m[1]});
    }
};

// A fake guest object whose every vtable slot is a lone `ret` (an IMemoryNotify, a bad-allocate
// notify that frees nothing).
struct NopObject {
    u64 vtable[4];
    u64* self;
    void Init(TestContext& t) {
        for (u64& v : vtable) v = t.sym(kRet);
        self = vtable;
    }
    void* Ptr() { return &self; }
};

enum OpKind { kOpMalloc, kOpAligned, kOpAlignedHigh, kOpFree, kOpFreeBlock, kOpCalcFree, kOpCalcFreeAll, kOpCalcFree2, kOpIsCreated, kOpNotify };
struct Op {
    OpKind kind;
    u64 a, b;
};

u64 RandSize(TestContext& t) {
    switch (t.rand_int(0, 9)) {
    case 0: return (u64)t.rand_int(1, 16);
    case 1:
    case 2:
    case 3: return (u64)t.rand_int(1, 512);
    case 4:
    case 5: return (u64)t.rand_int(512, 8192);
    case 6: return (u64)t.rand_int(8192, 0x18000);
    case 7: return 0xffc0 - 0x50 + (u64)t.rand_int(-0x60, 0x60);  // near a superblock
    case 8: return (u64)t.rand_int(0x10000, 0x30000);
    default: return (u64)t.rand_int(0x30, 0x90);
    }
}
s64 RandAlign(TestContext& t) {
    static const s64 kAligns[] = {0, 4, 8, 16, 32, 64, 128, 256, 4096, 0x8000, 0x10000};
    return kAligns[t.rand_int(0, 10)];
}

std::vector<Op> MakeOps(TestContext& t, int n, bool notify) {
    std::vector<Op> ops;
    for (int i = 0; i < n; i++) {
        int r = t.rand_int(0, 99);
        Op op{};
        if (r < 30) op = {kOpMalloc, RandSize(t), 0};
        else if (r < 38) op = {kOpAligned, RandSize(t), (u64)RandAlign(t)};
        else if (r < 46) op = {kOpAlignedHigh, RandSize(t), (u64)RandAlign(t)};
        else if (r < 80) op = {kOpFree, t.rand_u64(), 0};
        else if (r < 88) op = {kOpFreeBlock, t.rand_u64(), 0};
        else if (r < 91) op = {kOpCalcFree, 0, 0};
        else if (r < 93) op = {kOpCalcFreeAll, 0, 0};
        else if (r < 95) op = {kOpCalcFree2, 0, 0};
        else if (r < 97) op = {kOpIsCreated, 0, 0};
        else op = {notify ? kOpNotify : kOpFree, t.rand_u64(), 0};
        ops.push_back(op);
    }
    // Free everything at the end (runs empty and merge).
    for (int i = 0; i < 400; i++) ops.push_back({kOpFree, 0, 0});
    return ops;
}

// Runs the ops on h through the guest (native = false) or the natives; the results (pointers as
// offsets in the storage).
std::vector<u64> Run(TestContext& t, Heaps& h, const std::vector<Op>& ops, bool native, NopObject* notify) {
    std::vector<u64> out;
    std::vector<u64> live;
    MemoryManager* m = h.m[0];
    const u64 base = (u64)h.storage.data();
    auto rel = [&](u64 p) { return p ? p - base : ~u64{0}; };
    for (const Op& op : ops) {
        u64 r = 0;
        switch (op.kind) {
        case kOpMalloc:
            r = native ? (u64)m->Malloc(op.a) : t.call("_ZN4Aska13MemoryManager6MallocEm", {(u64)m, op.a});
            if (r) live.push_back(r);
            r = rel(r);
            break;
        case kOpAligned:
            r = native ? (u64)m->AlignedMalloc(op.a, (s64)op.b) : t.call("_ZN4Aska13MemoryManager13AlignedMallocEml", {(u64)m, op.a, op.b});
            if (r) live.push_back(r);
            r = rel(r);
            break;
        case kOpAlignedHigh:
            r = native ? (u64)m->AlignedMallocHigh(op.a, (s64)op.b) : t.call("_ZN4Aska13MemoryManager17AlignedMallocHighEml", {(u64)m, op.a, op.b});
            if (r) live.push_back(r);
            r = rel(r);
            break;
        case kOpFree:
        case kOpFreeBlock:
        case kOpNotify: {
            if (live.empty()) break;
            size_t k = op.a % live.size();
            u64 p = live[k];
            live.erase(live.begin() + (long)k);
            MemoryBlock* b = MemoryBlock::FromData((void*)p);
            if (op.kind == kOpNotify) b->m_notify = notify->Ptr();  // (as LocalRegisterNotify would)
            if (op.kind == kOpFreeBlock) {
                if (native) b->m_owner->LocalFree(b);
                else t.call("_ZN4Aska13MemoryManager9LocalFreeEPNS_12_MemoryBlockE", {(u64)b->m_owner, (u64)b});
            } else {
                if (native) m->LocalFree((void*)p);
                else t.call("_ZN4Aska13MemoryManager9LocalFreeEPv", {(u64)m, p});
            }
            r = rel(p);
            break;
        }
        case kOpCalcFree:
            r = native ? (u64)m->CalcFreeSize(true) : t.call("_ZN4Aska13MemoryManager12CalcFreeSizeEb", {(u64)m, 1});
            break;
        case kOpCalcFreeAll:
            r = native ? (u64)m->CalcFreeSize(false) : t.call("_ZN4Aska13MemoryManager12CalcFreeSizeEb", {(u64)m, 0});
            break;
        case kOpCalcFree2: {
            s64 a = -1, b = -1;
            r = native ? m->CalcFreeSize(&a, &b) : t.call("_ZNK4Aska13MemoryManager12CalcFreeSizeEPlS1_", {(u64)m, (u64)&a, (u64)&b});
            out.push_back((u64)a);
            out.push_back((u64)b);
            break;
        }
        case kOpIsCreated:
            r = native ? (u64)m->IsCreated() : t.call("_ZNK4Aska13MemoryManager9IsCreatedEv", {(u64)m}) & 0xff;
            break;
        }
        out.push_back(r);
    }
    return out;
}

// The first differing byte of two snapshots, as "+off: native xx guest yy" ("" when equal).
std::string FirstDiff(const std::vector<u8>& nat, const std::vector<u8>& gst) {
    for (size_t i = 0; i < nat.size(); i++)
        if (nat[i] != gst[i]) {
            char m[96];
            snprintf(m, sizeof m, "storage+%#zx: native %02x guest %02x", i, nat[i], gst[i]);
            return m;
        }
    return {};
}

// One differential round: the ops from the snapshot through the guest, then through the natives.
bool Round(TestContext& t, Heaps& h, const std::vector<Op>& ops, NopObject* notify, const char* what) {
    const std::vector<u8> snap = h.storage;
    std::vector<u64> g = Run(t, h, ops, false, notify);
    const std::vector<u8> after = h.storage;
    h.storage = snap;
    g_countBranches = true;
    std::vector<u64> n = Run(t, h, ops, true, notify);
    g_countBranches = false;
    bool ok = true;
    if (g != n) {
        size_t i = 0;
        while (i < g.size() && i < n.size() && g[i] == n[i]) i++;
        t.fail("%s: result %zu: native %#llx guest %#llx", what, i, i < n.size() ? (unsigned long long)n[i] : 0ull,
               i < g.size() ? (unsigned long long)g[i] : 0ull);
        ok = false;
    }
    std::string d = FirstDiff(h.storage, after);
    if (!d.empty()) {
        t.fail("%s: %s", what, d.c_str());
        ok = false;
    }
    return ok;
}

}  // namespace

// Random sequences on one heap, several sizes (the superblock count decides how runs split and merge).
static bool RandomRounds(TestContext& t) {
    NopObject notify;
    notify.Init(t);
    const u64 kSizes[] = {0x30000, 0x80000, 0x200000};
    int round = 0;
    for (u64 size : kSizes) {
        for (int rep = 0; rep < 6; rep++, round++) {
            Heaps h;
            h.Build(t, size);
            auto ops = MakeOps(t, 600, true);
            char what[64];
            snprintf(what, sizeof what, "heap %#llx round %d", (unsigned long long)size, rep);
            if (!Round(t, h, ops, &notify, what)) return false;
        }
    }
    return true;
}

// A ring of two managers (the first one small: allocations spill into the second) and the bad-allocate
// notify (a do-nothing handler: the second ring pass fails too).
static bool RingRounds(TestContext& t) {
    NopObject handler;
    handler.Init(t);
    for (int rep = 0; rep < 6; rep++) {
        Heaps h;
        h.Build(t, 0x20000, 0x60000);
        h.m[0]->m_badAllocNotify = handler.Ptr();
        auto ops = MakeOps(t, 300, false);
        char what[64];
        snprintf(what, sizeof what, "ring round %d", rep);
        if (!Round(t, h, ops, nullptr, what)) return false;
    }
    return true;
}

// Fresh heaps, one AlignedMallocHigh each, over sizes and alignments that put the block's header at
// every distance from a superblock start (the run-split shapes), then more allocations and frees.
static bool HighRunSplitRounds(TestContext& t) {
    for (u64 size : {u64{0x8000}, u64{0x10000}, u64{0x1ff00}, u64{0x2ff80}}) {
        for (s64 align : {s64{16}, s64{64}, s64{4096}}) {
            for (int k = 0; k < 8; k++) {
                Heaps h;
                h.Build(t, 0x80000);
                std::vector<Op> ops{{kOpAlignedHigh, size + (u64)k * 0x18, (u64)align}, {kOpMalloc, 100, 0}, {kOpAlignedHigh, 0x200, 64},
                                    {kOpAligned, 0x300, 256}, {kOpFree, 1, 0}, {kOpFree, 0, 0}, {kOpFree, 0, 0}, {kOpFree, 0, 0}};
                char what[96];
                snprintf(what, sizeof what, "high size %#llx align %lld k %d", (unsigned long long)size, (long long)align, k);
                if (!Round(t, h, ops, nullptr, what)) return false;
            }
        }
    }
    return true;
}

// The three kinds of rounds; then every rare path of the heap bodies must have run.
NATIVE_TEST("memory/heap-differential") {
    std::memset(g_branchHits, 0, sizeof g_branchHits);
    if (!RandomRounds(t) || !RingRounds(t) || !HighRunSplitRounds(t)) return;
    for (int b = 0; b < kHeapBranchCount; b++)
        if (g_branchHits[b] == 0) t.fail("heap branch %s never ran", kHeapBranchNames[b]);
}

// Native and guest code on one heap at once (4 threads each), then the heap's consistency: the lock
// protocol must exclude them from each other.
NATIVE_TEST("memory/heap-mixed-threads") {
    Heaps h;
    h.Build(t, 0x400000);
    MemoryManager* m = h.m[0];
    const u64 gMalloc = t.sym("_ZN4Aska13MemoryManager6MallocEm"), gFree = t.sym("_ZN4Aska13MemoryManager9LocalFreeEPv");
    std::vector<std::thread> th;
    std::atomic<int> failures{0};
    for (int i = 0; i < 8; i++) {
        th.emplace_back([&, i] {
            const bool native = i % 2 == 0;
            std::vector<std::pair<u64, u64>> live;  // (pointer, size)
            u64 seed = 0x9e3779b97f4a7c15ull * (u64)(i + 1);
            for (int k = 0; k < 4000; k++) {
                seed ^= seed << 13, seed ^= seed >> 7, seed ^= seed << 17;
                if (live.size() < 40 && (seed & 3) != 0) {
                    u64 n = 16 + seed % 3000;
                    u64 p = native ? (u64)m->Malloc(n) : guest_call(gMalloc, {(u64)m, n});
                    if (!p) {
                        failures++;
                        continue;
                    }
                    std::memset((void*)p, i, n);  // (a block another thread also got would be overwritten)
                    live.emplace_back(p, n);
                } else if (!live.empty()) {
                    const size_t at = seed % live.size();
                    const auto [p, n] = live[at];
                    live.erase(live.begin() + (long)at);
                    for (u64 j = 0; j < n; j++)
                        if (((u8*)p)[j] != (u8)i) {
                            failures++;
                            break;
                        }
                    if (native) m->LocalFree((void*)p);
                    else guest_call(gFree, {(u64)m, p});
                }
            }
            for (const auto& [p, n] : live) {
                if (native) m->LocalFree((void*)p);
                else guest_call(gFree, {(u64)m, p});
            }
        });
    }
    for (auto& x : th) x.join();
    t.expect_eq(failures.load(), 0, "no failed allocation, no block shared");
    // Everything freed: one run, nothing allocated, one free block holding all of it.
    const MemorySrbk& s0 = m->m_srbks[0];
    t.expect_eq(s0.m_next, 0u, "one run left");
    t.expect_eq(s0.m_allocated, (u64)0, "nothing allocated");
    MemoryBlock* head = RunHead(m, 0);
    t.expect_eq(head->m_freeNext->m_freeNext, head, "one free block");
    t.expect_eq(head->m_freeNext->m_size, s0.m_free, "it holds the run's free bytes");
    t.expect_eq(m->m_cs.m_lock, FastCriticalSection::kFree, "lock free");
}

// The live check's own machinery on private heaps (the originals are the guest symbols here): every
// checked call must come out ok.
NATIVE_TEST("memory/heap-live-check") {
    using namespace check;
    const Fn fns[] = {kMalloc, kAlignedMalloc, kAlignedMallocHigh, kLocalFree, kIsCreated, kCalcFreeSize};
    for (Fn f : fns) Orig(f) = t.sym(Symbol(f));
    const Totals before = GetTotals();
    SetForTest(true, 1);
    NopObject notify;
    notify.Init(t);
    for (int rep = 0; rep < 4; rep++) {
        Heaps h;
        h.Build(t, rep < 2 ? 0x80000 : 0x200000);
        auto ops = MakeOps(t, 500, true);
        Run(t, h, ops, true, &notify);
    }
    SetForTest(false, 64);
    for (Fn f : fns) Orig(f) = 0;
    const Totals after = GetTotals();
    t.expect_eq(after.bad - before.bad, (u64)0, "no mismatch");
    t.expect_eq(after.ok - before.ok > 1000, true, "checks ran");
}
