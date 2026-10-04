// memory_check.cpp: the live check of the memory natives (memory_check.h has the design).
#include "native/memory/memory_check.h"

#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <mutex>
#include <string>
#include <vector>

#include "core/loader.h"
#include "core/log.h"
#include "native/common/live_check.h"
#include "native/memory/memory_heap.h"
#include "native/memory/memory_lock.h"
#include "native/memory/memory_pools.h"

namespace soa::native::memory::check {

namespace {
// --live-check memory: every= (default 64), budget=, only= (substrings of the symbols below), out=.
live::Family g_family("memory", 64, false);

const char* const kSyms[kFnCount] = {
    "_ZN4Aska13MemoryManager6MallocEm",
    "_ZN4Aska13MemoryManager13AlignedMallocEml",
    "_ZN4Aska13MemoryManager17AlignedMallocHighEml",
    "_ZN4Aska13MemoryManager9LocalFreeEPNS_12_MemoryBlockE",
    "_ZNK4Aska13MemoryManager9IsCreatedEv",
    "_ZN4Aska13MemoryManager12CalcFreeSizeEb",
    "_ZN9Framework30CFixedLengthAllocatorContainer9pAllocateEmPKcj",
    "_ZN9Framework30CFixedLengthAllocatorContainer4FreeEPv",
    "_ZNK9Framework30CFixedLengthAllocatorContainer6IsMineEPv",
    "_ZNK9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE11NumElementsEv",
    "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj",
    "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv",
#define POOL(N)                                                         \
    "_ZN9Framework21TFixedLengthAllocatorILm" #N "EE9pAllocateEPKcj", \
        "_ZN9Framework21TFixedLengthAllocatorILm" #N "EE4FreeEPv",    \
        "_ZNK9Framework21TFixedLengthAllocatorILm" #N "EE6IsMineEPv"
    POOL(16), POOL(32), POOL(64), POOL(128), POOL(192), POOL(256), POOL(512),
#undef POOL
};

struct Counts {
    u64 orig = 0;
    std::atomic<u64> calls{0}, checks{0}, ok{0}, bad{0}, skipped{0}, races{0};
};
Counts g_counts[kFnCount];
std::mutex g_file_m;
thread_local bool t_in_check = false;

void SummaryFile() {
    if (g_family.out_path.empty()) return;
    std::lock_guard lk(g_file_m);
    FILE* f = fopen(g_family.out_path.c_str(), "w");
    if (!f) return;
    auto& s = g_family.stats;
    fprintf(f, "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races\n", (unsigned long long)s.checks.load(),
            (unsigned long long)s.ok.load(), (unsigned long long)s.bad.load(), (unsigned long long)s.skipped.load(),
            (unsigned long long)s.races.load());
    for (int i = 0; i < kFnCount; i++) {
        const Counts& c = g_counts[i];
        if (!c.checks) continue;
        fprintf(f, "%-72.72s checks %7llu ok %7llu bad %llu skipped %llu races %llu\n", kSyms[i], (unsigned long long)c.checks.load(),
                (unsigned long long)c.ok.load(), (unsigned long long)c.bad.load(), (unsigned long long)c.skipped.load(),
                (unsigned long long)c.races.load());
    }
    fclose(f);
}

void LogTotals() {
    auto& s = g_family.stats;
    const u64 n = s.checks;
    if (n % 1000) {
        // (the counts file also every 10 s: a session ends with a kill)
        static std::atomic<s64> last{0};
        s64 now = (s64)time(nullptr), l = last.load(std::memory_order_relaxed);
        if (now - l < 10 || !last.compare_exchange_strong(l, now)) return;
        SummaryFile();
        return;
    }
    SummaryFile();
    LOGI(g_family.log_tag.c_str(), "%llu checks: %llu ok, %llu mismatches, %llu skipped, %llu races", (unsigned long long)n,
         (unsigned long long)s.ok.load(), (unsigned long long)s.bad.load(), (unsigned long long)s.skipped.load(),
         (unsigned long long)s.races.load());
}

enum class Outcome { Ok, Mismatch, Skipped, Race };
void Result(Fn f, Outcome o, const std::string& why = {}) {
    Counts& c = g_counts[f];
    auto& s = g_family.stats;
    c.checks++, s.checks++;
    switch (o) {
    case Outcome::Ok: c.ok++, s.ok++; break;
    case Outcome::Mismatch:
        c.bad++, s.bad++;
        if (c.bad <= 5) LOGE(g_family.log_tag.c_str(), "MISMATCH %s: %s", kSyms[f], why.c_str());
        break;
    case Outcome::Skipped:
        c.skipped++, s.skipped++;
        if (c.skipped <= 2 && !why.empty()) LOGI(g_family.log_tag.c_str(), "skipped %s: %s", kSyms[f], why.c_str());
        break;
    case Outcome::Race: c.races++, s.races++; break;
    }
    LogTotals();
}

struct Scope {
    Scope() { t_in_check = live::t_busy = true; }
    ~Scope() { t_in_check = live::t_busy = false; }
};

std::string Hex(const char* what, u64 a, u64 b) {
    char m[160];
    snprintf(m, sizeof m, "%s: native %#" PRIx64 " guest %#" PRIx64, what, a, b);
    return m;
}

// ---- heap ----

// The manager's shadow: its bytes, with a free lock (no waiters), a ring of itself and no
// bad-allocate notify; the heap pointers are the real manager's.
MemoryManager* Shadow(const MemoryManager* m) {
    alignas(16) static thread_local u8 buf[sizeof(MemoryManager)];
    auto* s = reinterpret_cast<MemoryManager*>(buf);
    std::memcpy(buf, (const void*)m, sizeof buf);
    s32 freeWord = FastLock::kFree, bias = FastLock::kWaiterBias;
    std::memcpy(s->m_cs + FastLock::kLockWord, &freeWord, 4);
    std::memcpy(s->m_cs + FastLock::kWaiters, &bias, 4);
    s->m_ringHead = s->m_ringNext = s->m_ringPrev = s;
    s->m_badAllocNotify = nullptr;
    return s;
}

// What a native dry run left: the final bytes at each logged store and the srbk table.
struct DryRun {
    UndoLog log;
    std::vector<u8> post;   // the entries' bytes after the run, in log order
    std::vector<u8> table;  // the manager's srbk table after the run
    void record(const MemoryManager* m) {
        post.clear();
        for (const auto& e : log.entries()) post.insert(post.end(), e.addr, e.addr + e.size);
        const u8* t = reinterpret_cast<const u8*>(m->m_srbks);
        table.assign(t, t + (size_t)m->m_srbkCount * sizeof(MemorySrbk));
    }
    // "" when the memory now holds what the dry run left.
    std::string compare(const MemoryManager* m) const {
        size_t at = 0;
        for (const auto& e : log.entries()) {
            if (std::memcmp(e.addr, post.data() + at, e.size) != 0) {
                u64 now = 0, then = 0;
                std::memcpy(&now, e.addr, e.size);
                std::memcpy(&then, post.data() + at, e.size);
                char what[96];
                snprintf(what, sizeof what, "store at heap+%#" PRIx64 " (%u bytes)", (u64)(e.addr - m->m_heap), e.size);
                return Hex(what, then, now);
            }
            at += e.size;
        }
        const u8* t = reinterpret_cast<const u8*>(m->m_srbks);
        for (size_t i = 0; i < table.size(); i++) {
            if (t[i] != table[i]) {
                char what[96];
                snprintf(what, sizeof what, "srbk %zu +%#zx", i / sizeof(MemorySrbk), i % sizeof(MemorySrbk));
                return Hex(what, table[i], t[i]);
            }
        }
        return {};
    }
};

// One checked allocation on manager m: `native(st)` is the lock-held body (the data pointer or null),
// `guest(shadow)` the original on the shadow.
template <class Native, class Guest>
void* CheckAlloc(Fn f, MemoryManager* m, Native native, Guest guest) {
    Scope scope;
    FastLock::Enter(m->m_cs);
    DryRun dry;
    void* n = native(LoggedStore{&dry.log});
    dry.record(m);
    dry.log.undo();
    MemoryManager* sh = Shadow(m);
    void* g = (void*)guest(sh);
    if (g) {
        MemoryBlock* b = MemoryBlock::FromData(g);
        if (b->m_owner == sh) b->m_owner = m;
    }
    std::string why = n != g ? Hex("result", (u64)n, (u64)g) : dry.compare(m);
    FastLock::Leave(m->m_cs);
    Result(f, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
    return g;  // the guest's allocation (and stores) stand
}

// ---- pools ----

// A pool's state a pAllocate / Free touches: the object and one block header.
template <u64 N>
struct PoolState {
    u8 obj[sizeof(TFixedLengthAllocator<N>)] = {};
    u8 hdr[sizeof(FixedLengthBlockHeader)] = {};
    FixedLengthBlockHeader* at = nullptr;
    void save(const TFixedLengthAllocator<N>* a, FixedLengthBlockHeader* h) {
        std::memcpy(obj, (const void*)a, sizeof obj);
        at = h;
        if (h) std::memcpy(hdr, h, sizeof hdr);
    }
    void restore(TFixedLengthAllocator<N>* a) const {
        std::memcpy((void*)a, obj, sizeof obj);
        if (at) std::memcpy(at, hdr, sizeof hdr);
    }
    std::string compare(const TFixedLengthAllocator<N>* a) const {
        const u8* now = reinterpret_cast<const u8*>(a);
        for (size_t i = 0; i < sizeof obj; i++)
            if (now[i] != obj[i]) return Hex("pool object byte", i, 0) + Hex(" value", obj[i], now[i]);
        if (at)
            for (size_t i = 0; i < sizeof hdr; i++)
                if (reinterpret_cast<const u8*>(at)[i] != hdr[i]) return Hex("block header byte", i, 0) + Hex(" value", hdr[i], reinterpret_cast<const u8*>(at)[i]);
        return {};
    }
};

template <u64 N>
FixedLengthBlockHeader* NextHeader(TFixedLengthAllocator<N>* a) {
    if ((u64)a->m_numAllocated >= a->m_maxBlock || a->m_freeHead >= a->m_maxBlock) return nullptr;
    return &a->m_blocks[a->m_freeHead].m_header;
}
inline FixedLengthBlockHeader* HeaderOf(void* p) {
    return reinterpret_cast<FixedLengthBlockHeader*>(static_cast<u8*>(p) - sizeof(FixedLengthBlockHeader));
}

// pAllocate on pool `a` checked against `guest()` (the original of pAllocate, or of a dispatcher that
// ends in it), with a's mutex held across both (recursive: the original enters it again).
template <u64 N, class Guest>
void* CheckPoolAllocate(Fn f, TFixedLengthAllocator<N>* a, Guest guest) {
    PoolLock lock(a->m_mutex);
    PoolState<N> pre, post;
    pre.save(a, NextHeader(a));
    void* n = a->AllocateLocked();
    post.save(a, pre.at);
    pre.restore(a);
    void* g = (void*)guest();
    std::string why = n != g ? Hex("result", (u64)n, (u64)g) : post.compare(a);
    Result(f, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
    return g;
}

template <u64 N, class Guest>
void CheckPoolFree(Fn f, TFixedLengthAllocator<N>* a, void* p, Guest guest) {
    PoolLock lock(a->m_mutex);
    PoolState<N> pre, post;
    pre.save(a, p ? HeaderOf(p) : nullptr);
    a->FreeLocked(p);
    post.save(a, pre.at);
    pre.restore(a);
    guest();
    std::string why = post.compare(a);
    Result(f, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
}

CFixedLengthAllocatorContainer* StlContainer() {
    return *reinterpret_cast<CFixedLengthAllocatorContainer**>(main_lib()->base + kVaddrStlFixedLengthContainer);
}
}  // namespace

std::atomic<bool>& g_on = g_family.on;  // (a reference: constant-initialized)

u64& Orig(Fn f) { return g_counts[f].orig; }

bool DueSlow(Fn f) {
    Counts& c = g_counts[f];
    if (t_in_check || live::t_busy || !c.orig || !g_family.only.match(kSyms[f])) return false;
    if (g_family.budget && c.checks >= (u64)g_family.budget) return false;
    return c.calls.fetch_add(1, std::memory_order_relaxed) % (u64)g_family.every == 0;
}

void* Malloc(MemoryManager* m, u64 size) {
    const u64 need = (size + 0x4f) & ~u64{0xf};
    return CheckAlloc(kMalloc, m, [&](const LoggedStore& st) -> void* {
        MemoryBlock* b = m->MallocLocked(need, st);
        return b ? b->Data() : nullptr;
    }, [&](MemoryManager* sh) { return guest_call(Orig(kMalloc), {(u64)sh, size}); });
}

void* AlignedMalloc(MemoryManager* m, u64 size, s64 align) {
    const u64 need = (size + 0x4f) & ~u64{0xf};
    return CheckAlloc(kAlignedMalloc, m, [&](const LoggedStore& st) { return m->AlignedMallocLocked(size, align, need, st); },
                      [&](MemoryManager* sh) { return guest_call(Orig(kAlignedMalloc), {(u64)sh, size, (u64)align}); });
}

void* AlignedMallocHigh(MemoryManager* m, u64 size, s64 align) {
    const u64 need = (size + 0x4f) & ~u64{0xf};
    return CheckAlloc(kAlignedMallocHigh, m, [&](const LoggedStore& st) { return m->AlignedMallocHighLocked(align, need, st); },
                      [&](MemoryManager* sh) { return guest_call(Orig(kAlignedMallocHigh), {(u64)sh, size, (u64)align}); });
}

bool LocalFree(MemoryManager* m, MemoryBlock* b) {
    if (b->m_notify) {
        Result(kLocalFree, Outcome::Skipped, "a registered IMemoryNotify (the guest unlocks mid-call)");
        return false;
    }
    Scope scope;
    FastLock::Enter(m->m_cs);
    if (b->m_used != 1 || b->m_notify) {  // changed meanwhile: the normal path decides
        FastLock::Leave(m->m_cs);
        return false;
    }
    DryRun dry;
    m->LocalFreeLocked(b, LoggedStore{&dry.log});
    dry.record(m);
    dry.log.undo();
    guest_call(Orig(kLocalFree), {(u64)Shadow(m), (u64)b});
    std::string why = dry.compare(m);
    FastLock::Leave(m->m_cs);
    Result(kLocalFree, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
    return true;
}

template <u64 N>
void* PoolAllocate(TFixedLengthAllocator<N>* a, const char* file, u32 line) {
    Scope scope;
    const Fn f = PoolFn(N, 0);
    return CheckPoolAllocate(f, a, [&] { return guest_call(Orig(f), {(u64)a, (u64)file, line}); });
}

template <u64 N>
void PoolFree(TFixedLengthAllocator<N>* a, void* p) {
    Scope scope;
    const Fn f = PoolFn(N, 1);
    CheckPoolFree(f, a, p, [&] { guest_call(Orig(f), {(u64)a, (u64)p}); });
}

#define POOL(N)                                                                          \
    template void* PoolAllocate<N>(TFixedLengthAllocator<N>*, const char*, u32); \
    template void PoolFree<N>(TFixedLengthAllocator<N>*, void*);
POOL(16)
POOL(32)
POOL(64)
POOL(128)
POOL(192)
POOL(256)
POOL(512)
#undef POOL

// The dispatchers: the pool the native picks, checked with the dispatcher's original as the guest run.
void* ContainerAllocate(CFixedLengthAllocatorContainer* c, u64 size, const char* file, u32 line) {
    Scope scope;
    IFixedLengthAllocator* a = c->AllocatorFor(size);
    auto guest = [&] { return guest_call(Orig(kContainerAllocate), {(u64)c, size, (u64)file, line}); };
    void* r = nullptr;
    if (!a) {
        r = (void*)guest();
        Result(kContainerAllocate, r ? Outcome::Mismatch : Outcome::Ok, r ? Hex("result", 0, (u64)r) : "");
        return r;
    }
    if (!WithPool(a, [&](auto* pool) { r = CheckPoolAllocate(kContainerAllocate, pool, guest); })) {
        Result(kContainerAllocate, Outcome::Skipped, "not a TFixedLengthAllocator");
        r = a->pAllocate(file, line);
    }
    return r;
}

bool ContainerFree(CFixedLengthAllocatorContainer* c, void* p) {
    Scope scope;
    IFixedLengthAllocator* a = c->AllocatorOwning(p);
    auto guest = [&] { return guest_call(Orig(kContainerFree), {(u64)c, (u64)p}) & 1; };
    if (!a) {
        const bool g = guest();
        Result(kContainerFree, g ? Outcome::Mismatch : Outcome::Ok, g ? "the guest found an owner" : "");
        return g;
    }
    if (!WithPool(a, [&](auto* pool) { CheckPoolFree(kContainerFree, pool, p, guest); })) {
        Result(kContainerFree, Outcome::Skipped, "not a TFixedLengthAllocator");
        a->Free(p);
    }
    return true;
}

void* StlAllocate(u64 size, const char* file, u32 line) {
    Scope scope;
    CFixedLengthAllocatorContainer* c = StlContainer();
    IFixedLengthAllocator* a = c ? c->AllocatorFor(size) : nullptr;
    void* r = nullptr;
    bool pooled = false;
    if (a) {
        WithPool(a, [&](auto* pool) {
            if (NextHeader(pool) == nullptr) return;  // full: the heap serves it (unchecked here)
            r = CheckPoolAllocate(kStlAllocate, pool, [&] { return guest_call(Orig(kStlAllocate), {size, (u64)file, line}); });
            pooled = true;
        });
    }
    if (pooled) return r;
    Result(kStlAllocate, Outcome::Skipped);  // (served by the heap: Malloc's own checks cover it)
    return StlAllocateUnchecked(size, file, line);
}

void StlFree(void* p) {
    Scope scope;
    CFixedLengthAllocatorContainer* c = StlContainer();
    IFixedLengthAllocator* a = c ? c->AllocatorOwning(p) : nullptr;
    if (a && WithPool(a, [&](auto* pool) { CheckPoolFree(kStlFree, pool, p, [&] { guest_call(Orig(kStlFree), {(u64)p}); }); })) return;
    Result(kStlFree, Outcome::Skipped);
    StlFreeUnchecked(p);
}

Totals GetTotals() {
    auto& s = g_family.stats;
    return {s.checks.load(), s.ok.load(), s.bad.load(), s.skipped.load(), s.races.load()};
}
void SetForTest(bool on, int every) {
    g_family.every = every;
    g_family.on = on;
}
const char* Symbol(Fn f) { return kSyms[f]; }

void CheckGetter(Cpu& c, Fn f, HostFn native, u64 mask) {
    Scope scope;
    u64 x[8];
    for (int i = 0; i < 8; i++) x[i] = c.x(i);
    native(c);
    const u64 got = c.x(0) & mask;
    const u64 want = guest_call(Orig(f), {x[0], x[1], x[2], x[3]}) & mask;
    if (got == want) return Result(f, Outcome::Ok);
    // Rerun both: a value another thread changed in between doesn't reproduce.
    for (int i = 0; i < 8; i++) c.set_x(i, x[i]);
    native(c);
    const u64 got2 = c.x(0) & mask;
    const u64 want2 = guest_call(Orig(f), {x[0], x[1], x[2], x[3]}) & mask;
    if (got2 == want2) return Result(f, Outcome::Race);
    Result(f, Outcome::Mismatch, Hex("x0", got2, want2));
}

}  // namespace soa::native::memory::check
