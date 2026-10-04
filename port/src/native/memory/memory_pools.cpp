// memory_pools.cpp: the STL allocator's fixed-length pools as natives: Framework::TFixedLengthAllocator<N>
// (pAllocate, Free, IsMine for the seven N), CFixedLengthAllocatorContainer (pAllocate, Free, IsMine),
// and CAssignedMemoryManagerForSTLAllocator::
// Allocate / Free, on the guest's own pool objects.
//
// Readable C++ from the Ghidra decompile (port/decomp/memory/stl_allocator.c; the asserts' arguments
// from the disassembly). Each pool's lock is its Framework::CMutex (m_mutex: sync's class, its members
// called directly). The container's calls through the
// allocators' vtables go straight to these members when the vtable is a TFixedLengthAllocator<N>'s,
// else to the guest's slot. Not native (cold): the constructors, NumAllocated, IsFree, the reports,
// EnableMutex / DisableMutex, BlockSize (8 bytes: reached through the vtable only).
#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/guest_std.h"
#include "native/common/native_method.h"
#include "native/memory/memory_check.h"
#include "native/memory/memory_heap.h"
#include "native/memory/memory_pools.h"

namespace soa::native::memory {

namespace {
// Guest string addresses (vaddr) the asserts pass, and their lines.
constexpr u64 kStrFixedLengthH = 0x26db199;   // ".../Framework/TFixedLengthAllocator.h"
constexpr u64 kStrOutOfRange = 0x26db1f8;     // "The argument has gotten numeric out of range.(%d/%d)"
constexpr u64 kStrNotFree = 0x26db22d;        // "Not free."
constexpr u64 kStrIllegalAddress = 0x26db237; // "Illegal address.(%08x)\n"
constexpr u64 kStrDoubleFree = 0x26db24f;     // "Double free."
constexpr u64 kStrObjectContainerH = 0x2865e66;  // ".../Framework/TObjectContainer.h"
constexpr u64 kStrElementsNull = 0x26ee29f;      // "m_pElements is null."
constexpr u64 kStrFixedLengthCpp = 0x28663d3;    // "...\\Framework\\TFixedLengthAllocator.cpp"
constexpr u64 kStrAllocatorsNull = 0x2866463;    // "m_Allocators.IsInitialized() is null."

u64 Str(u64 vaddr) { return main_lib()->base + vaddr; }

struct Calls {
    u64 assert_ = guest::sym("_ZN9Framework9gDoAssertEPKciS1_z");
    u64 newArrayNothrow = guest::sym("_ZnamRKSt9nothrow_t");
    u64 nothrow = guest::sym("_ZSt7nothrow");
    u64 deleteArray = guest::sym("_ZdaPv");
    u64 objectContainerVtable = guest::sym("_ZTVN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEEE") + 0x10;
    u64 poolVtable[7] = {
        guest::sym("_ZTVN9Framework21TFixedLengthAllocatorILm16EEE") + 0x10,
        guest::sym("_ZTVN9Framework21TFixedLengthAllocatorILm32EEE") + 0x10,
        guest::sym("_ZTVN9Framework21TFixedLengthAllocatorILm64EEE") + 0x10,
        guest::sym("_ZTVN9Framework21TFixedLengthAllocatorILm128EEE") + 0x10,
        guest::sym("_ZTVN9Framework21TFixedLengthAllocatorILm192EEE") + 0x10,
        guest::sym("_ZTVN9Framework21TFixedLengthAllocatorILm256EEE") + 0x10,
        guest::sym("_ZTVN9Framework21TFixedLengthAllocatorILm512EEE") + 0x10,
    };
};
const Calls& calls() {
    static const Calls c;
    return c;
}
}  // namespace

const u64* PoolVtables() { return calls().poolVtable; }

PoolLock::PoolLock(CMutex* mutex) : m_(mutex) {
    if (!m_) return;
    if (!m_->IsInitialized()) m_->Initialize();
    m_->Lock();
}
PoolLock::~PoolLock() {
    if (m_) m_->Unlock();
}

namespace {

// Framework::gDoAssert(file, line, format, ...): the guest's (it logs; the asserts never fire in a
// healthy run).
void Assert(u64 file, u32 line, u64 format, u64 a = 0, u64 b = 0) {
    guest_call(calls().assert_, {Str(file), line, Str(format), a, b});
}

u64 Slot(const void* obj, int slot) { return (*static_cast<const u64* const*>(obj))[slot]; }

u64* StlMemoryManagerSlot() { return reinterpret_cast<u64*>(main_lib()->base + kVaddrStlMemoryManager); }
u64* StlContainerSlot() { return reinterpret_cast<u64*>(main_lib()->base + kVaddrStlFixedLengthContainer); }
}  // namespace

// ---- IFixedLengthAllocator: the vtable calls ----

u64 IFixedLengthAllocator::BlockSize() const {
    u64 n = 0;
    if (WithPool(this, [&](auto* p) { n = p->BlockSize(); })) return n;
    return guest_call(Slot(this, 2), {(u64)this});
}
void* IFixedLengthAllocator::pAllocate(const char* file, u32 line) {
    void* r = nullptr;
    if (WithPool(this, [&](auto* p) { r = p->pAllocate(file, line); })) return r;
    return (void*)guest_call(Slot(this, 4), {(u64)this, (u64)file, line});
}
void IFixedLengthAllocator::Free(void* q) {
    if (WithPool(this, [&](auto* p) { p->Free(q); })) return;
    guest_call(Slot(this, 5), {(u64)this, (u64)q});
}
bool IFixedLengthAllocator::IsMine(void* q) const {
    bool r = false;
    if (WithPool(this, [&](auto* p) { r = p->IsMine(q); })) return r;
    return guest_call(Slot(this, 6), {(u64)this, (u64)q}) & 1;
}

// ---- TFixedLengthAllocator<N> ----

template <u64 N>
u64 TFixedLengthAllocator<N>::BlockSize() const {
    return N;
}

template <u64 N>
void* TFixedLengthAllocator<N>::AllocateLocked() {
    if ((u64)m_numAllocated >= m_maxBlock) return nullptr;
    const u32 i = m_freeHead;
    if (m_maxBlock <= i) Assert(kStrFixedLengthH, 0xf9, kStrOutOfRange, i, m_maxBlock);
    TFixedLengthBlock<N>* blocks = m_blocks;
    m_freeHead = blocks[i].m_header.m_next;
    if (blocks[i].m_header.m_free != 1) {
        Assert(kStrFixedLengthH, 0xfc, kStrNotFree);
        blocks = m_blocks;
    }
    m_numAllocated++;
    blocks[i].m_header.m_free = 0;
    return m_blocks[i].m_data;
}

template <u64 N>
void TFixedLengthAllocator<N>::FreeLocked(void* p) {
    if (!p) return;
    // (the guest asks through its vtable; for this class that is IsMine below)
    if (!reinterpret_cast<IFixedLengthAllocator*>(this)->IsMine(p)) Assert(kStrFixedLengthH, 0x10f, kStrIllegalAddress, (u64)p);
    auto* h = reinterpret_cast<FixedLengthBlockHeader*>(static_cast<u8*>(p) - sizeof(FixedLengthBlockHeader));
    if (h->m_free != 0) Assert(kStrFixedLengthH, 0x111, kStrDoubleFree);
    h->m_free = 1;
    h->m_next = m_freeHead;
    m_freeHead = h->m_index;
    m_numAllocated--;
}

template <u64 N>
void* TFixedLengthAllocator<N>::pAllocate(const char* file, u32 line) {
    if (check::Due(check::PoolFn(N, 0))) return check::PoolAllocate(this, file, line);
    PoolLock lock(m_mutex);
    return AllocateLocked();
}

template <u64 N>
void TFixedLengthAllocator<N>::Free(void* p) {
    if (check::Due(check::PoolFn(N, 1))) return check::PoolFree(this, p);
    PoolLock lock(m_mutex);
    FreeLocked(p);
}

template <u64 N>
bool TFixedLengthAllocator<N>::IsMine(void* p) const {
    const u64 a = (u64)p, lo = (u64)m_blocks;
    if (a < lo) return false;
    if (lo + m_maxBlock * sizeof(TFixedLengthBlock<N>) <= a) return false;
    if (m_tag[0] == 0) return false;
    const auto* h = reinterpret_cast<const FixedLengthBlockHeader*>(static_cast<u8*>(p) - sizeof(FixedLengthBlockHeader));
    return (char)h->m_tag[0] == m_tag[0] && (char)h->m_tag[1] == m_tag[1] && (char)h->m_tag[2] == m_tag[2];
}

template class TFixedLengthAllocator<16>;
template class TFixedLengthAllocator<32>;
template class TFixedLengthAllocator<64>;
template class TFixedLengthAllocator<128>;
template class TFixedLengthAllocator<192>;
template class TFixedLengthAllocator<256>;
template class TFixedLengthAllocator<512>;

// ---- the container's element access (TObjectContainer's accessors, inlined in the guest's loops) ----
// Framework::TObjectContainer belongs to `containers` (its NumElements / rElement / crElement natives);
// the pool loops inline them, so the same reads and asserts are written out here.
namespace {
using AllocatorList = TObjectContainer<IFixedLengthAllocator*>;

// NumElements (the container's vtable slot 4): the guest's own function unless it is the known one.
u64 Count(const AllocatorList* c) {
    if ((u64)c->vtable != calls().objectContainerVtable) return guest_call(Slot(c, 4), {(u64)c});
    if (!c->m_elements) Assert(kStrObjectContainerH, 0x3e, kStrElementsNull);
    return c->m_count;
}
// rElement (lines 0x44 / 0x45) or crElement (0x4b / 0x4c).
IFixedLengthAllocator* ElementAt(const AllocatorList* c, u64 i, bool constAccess) {
    if (!c->m_elements) Assert(kStrObjectContainerH, constAccess ? 0x4b : 0x44, kStrElementsNull);
    if (Count(c) <= i) Assert(kStrObjectContainerH, constAccess ? 0x4c : 0x45, kStrOutOfRange, i, Count(c));
    return c->m_elements[i];
}
}  // namespace

// ---- CFixedLengthAllocatorContainer ----

// The guest's loops (pAllocate, Free, IsMine): `if (!elements) assert` once, then per index: an
// inlined NumElements' "m_pElements is null" assert, the count check, the element (rElement /
// crElement's asserts), the test. (Only the asserts' order is approximated: they never fire.)
IFixedLengthAllocator* CFixedLengthAllocatorContainer::AllocatorFor(u64 size) {
    TObjectContainer<IFixedLengthAllocator*>& c = m_allocators;
    if (!c.m_elements) Assert(kStrFixedLengthCpp, 0x83, kStrAllocatorsNull);
    for (u64 i = 0;; i++) {
        if (!c.m_elements) Assert(kStrObjectContainerH, 0x3e, kStrElementsNull);
        if (c.m_count <= i) return nullptr;
        IFixedLengthAllocator* a = ElementAt(&c, i, false);
        if (size <= a->BlockSize()) return a;
    }
}

IFixedLengthAllocator* CFixedLengthAllocatorContainer::AllocatorOwning(void* p) const {
    const TObjectContainer<IFixedLengthAllocator*>& c = m_allocators;
    if (!c.m_elements) Assert(kStrFixedLengthCpp, 0xae, kStrAllocatorsNull);
    for (u64 i = 0;; i++) {
        if (!c.m_elements) Assert(kStrObjectContainerH, 0x3e, kStrElementsNull);
        if (c.m_count <= i) return nullptr;
        IFixedLengthAllocator* a = ElementAt(&c, i, true);
        if (a->IsMine(p)) return a;
    }
}

void* CFixedLengthAllocatorContainer::pAllocate(u64 size, const char* file, u32 line) {
    if (check::Due(check::kContainerAllocate)) return check::ContainerAllocate(this, size, file, line);
    IFixedLengthAllocator* a = AllocatorFor(size);
    return a ? a->pAllocate(file, line) : nullptr;
}

bool CFixedLengthAllocatorContainer::Free(void* p) {
    if (check::Due(check::kContainerFree)) return check::ContainerFree(this, p);
    // (Free's loop asserts with rElement's lines and 0x9d; the same checks as IsMine's)
    TObjectContainer<IFixedLengthAllocator*>& c = m_allocators;
    if (!c.m_elements) Assert(kStrFixedLengthCpp, 0x9d, kStrAllocatorsNull);
    for (u64 i = 0;; i++) {
        if (!c.m_elements) Assert(kStrObjectContainerH, 0x3e, kStrElementsNull);
        if (c.m_count <= i) return false;
        IFixedLengthAllocator* a = ElementAt(&c, i, false);
        if (a->IsMine(p)) {
            a->Free(p);
            return true;
        }
    }
}

bool CFixedLengthAllocatorContainer::IsMine(void* p) const { return AllocatorOwning(p) != nullptr; }

// ---- CAssignedMemoryManagerForSTLAllocator ----

void* CAssignedMemoryManagerForSTLAllocator::Allocate(u64 size, const char* file, u32 line) {
    if (check::Due(check::kStlAllocate)) return check::StlAllocate(size, file, line);
    return StlAllocateUnchecked(size, file, line);
}

void* StlAllocateUnchecked(u64 size, const char* file, u32 line) {
    if (auto* c = reinterpret_cast<CFixedLengthAllocatorContainer*>(*StlContainerSlot())) {
        if (void* p = c->pAllocate(size, file, line)) return p;
    }
    if (auto* m = reinterpret_cast<MemoryManager*>(*StlMemoryManagerSlot())) return m->Malloc(size);
    return (void*)guest_call(calls().newArrayNothrow, {size, calls().nothrow});
}

void CAssignedMemoryManagerForSTLAllocator::Free(void* p) {
    if (!p) return;
    if (check::Due(check::kStlFree)) return check::StlFree(p);
    StlFreeUnchecked(p);
}

void StlFreeUnchecked(void* p) {
    auto* c = reinterpret_cast<CFixedLengthAllocatorContainer*>(*StlContainerSlot());
    if (c && c->Free(p)) return;
    if (auto* m = reinterpret_cast<MemoryManager*>(*StlMemoryManagerSlot())) return m->LocalFree(p);
    guest_call(calls().deleteArray, {(u64)p});
}

// ---- bindings ----

// (one registration per __COUNTER__: NATIVE_FUNCTION_ORIG's __LINE__ names collide inside a macro)
#define MEMORY_REG(sym, fn, note, orig) \
    static bool NATIVE_CONCAT(memory_pool_reg_, __COUNTER__) = ::soa::register_native_function({sym, fn, note, nullptr, orig})
#define MEMORY_POOL_NATIVES(N)                                                                                           \
    MEMORY_REG("_ZN9Framework21TFixedLengthAllocatorILm" #N "EE9pAllocateEPKcj", wrap_method<&TFixedLengthAllocator<N>::pAllocate>(), \
               "memory: TFixedLengthAllocator<" #N ">::pAllocate", &check::Orig(check::PoolFn(N, 0)));                  \
    MEMORY_REG("_ZN9Framework21TFixedLengthAllocatorILm" #N "EE4FreeEPv", wrap_method<&TFixedLengthAllocator<N>::Free>(), \
               "memory: TFixedLengthAllocator<" #N ">::Free", &check::Orig(check::PoolFn(N, 1)));                       \
    MEMORY_REG("_ZNK9Framework21TFixedLengthAllocatorILm" #N "EE6IsMineEPv",                                             \
               (check::Getter<check::PoolFn(N, 2), wrap_method<&TFixedLengthAllocator<N>::IsMine>(), 0xff>),           \
               "memory: TFixedLengthAllocator<" #N ">::IsMine", &check::Orig(check::PoolFn(N, 2)))
MEMORY_POOL_NATIVES(16);
MEMORY_POOL_NATIVES(32);
MEMORY_POOL_NATIVES(64);
MEMORY_POOL_NATIVES(128);
MEMORY_POOL_NATIVES(192);
MEMORY_POOL_NATIVES(256);
MEMORY_POOL_NATIVES(512);
#undef MEMORY_POOL_NATIVES
#undef MEMORY_REG

NATIVE_FUNCTION_ORIG("_ZN9Framework30CFixedLengthAllocatorContainer9pAllocateEmPKcj", wrap_method<&CFixedLengthAllocatorContainer::pAllocate>(),
                     "memory: CFixedLengthAllocatorContainer::pAllocate", &check::Orig(check::kContainerAllocate));
NATIVE_FUNCTION_ORIG("_ZN9Framework30CFixedLengthAllocatorContainer4FreeEPv", wrap_method<&CFixedLengthAllocatorContainer::Free>(),
                     "memory: CFixedLengthAllocatorContainer::Free", &check::Orig(check::kContainerFree));
NATIVE_FUNCTION_ORIG("_ZNK9Framework30CFixedLengthAllocatorContainer6IsMineEPv",
                     (check::Getter<check::kContainerIsMine, wrap_method<&CFixedLengthAllocatorContainer::IsMine>(), 0xff>),
                     "memory: CFixedLengthAllocatorContainer::IsMine", &check::Orig(check::kContainerIsMine));
NATIVE_FUNCTION_ORIG("_ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj",
                     wrap<&CAssignedMemoryManagerForSTLAllocator::Allocate>(), "memory: CAssignedMemoryManagerForSTLAllocator::Allocate",
                     &check::Orig(check::kStlAllocate));
NATIVE_FUNCTION_ORIG("_ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv", wrap<&CAssignedMemoryManagerForSTLAllocator::Free>(),
                     "memory: CAssignedMemoryManagerForSTLAllocator::Free", &check::Orig(check::kStlFree));

}  // namespace soa::native::memory
