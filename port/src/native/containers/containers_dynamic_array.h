#pragma once
// Aska::TDynamicArray<T, TAllocator<T>>::Insert_<Memory::TUninitializedFillN<T>> as a template over the
// recovered class (containers_layout.h; port/decomp/containers/arrays.c, the WorkBufferContext
// instantiation): for natives of other subsystems that insert into a guest TDynamicArray the way the
// guest's inlined / instantiated code does (ASON::Malloc's new work block). Storage comes from
// Aska::MemoryManagerAdapter::AlignedMalloc(bytes, 8) / AlignedFree, called through live::out_call (so
// a live check of the calling native records them).
#include <cstring>

#include "core/loader.h"
#include "native/common/live_call.h"
#include "native/containers/containers_family.h"
#include "native/containers/containers_layout.h"

namespace soa::native::containers {

// Inserts n slots at pos, the first `copies` of them copies of *value (Insert_'s filler {count,
// value}); returns the position of the first inserted slot (in the new storage when it grew). Grows
// to max(size + n, 2 * capacity); when the allocation fails nothing is inserted and pos is returned.
template <typename T>
T* TDynamicArray<T>::InsertFill(T* pos, u64 n, u64 copies, const T* value) {
    static const u64 aligned_malloc = main_lib()->sym("_ZN4Aska20MemoryManagerAdapter13AlignedMallocEmm");
    static const u64 aligned_free = main_lib()->sym("_ZN4Aska20MemoryManagerAdapter11AlignedFreeEPv");
    if (n == 0) return pos;
    u64 size = (u64)(m_end - m_begin), cap = (u64)(m_capEnd - m_begin);
    u64 want = size + n;
    if (cap < want) {
        u64 grown = 2 * cap;
        if (want < grown) want = grown;
        if (want >> (64 - 5)) return pos;  // (want * 0x20 overflows; T is 0x20 bytes in the instantiations used)
        T* buf = (T*)live::out_call(family(), aligned_malloc, {want * sizeof(T), 8});
        if (!buf) return pos;
        u64 before = (u64)(pos - m_begin);
        std::memcpy((void*)buf, (const void*)m_begin, before * sizeof(T));
        T* at = buf + before;
        for (u64 k = 0; k < copies; k++) std::memcpy((void*)(at + k), (const void*)value, sizeof(T));
        u64 after = (u64)(m_end - pos);
        std::memcpy((void*)(at + n), (const void*)pos, after * sizeof(T));
        live::out_call(family(), aligned_free, {(u64)m_begin});
        m_begin = buf;
        m_end = at + n + after;
        m_capEnd = buf + want;
        return at;
    }
    for (T* q = m_end; q != pos;) {  // the tail moves up by n, last element first
        --q;
        std::memcpy((void*)(q + n), (const void*)q, sizeof(T));
    }
    for (u64 k = 0; k < copies; k++) std::memcpy((void*)(pos + k), (const void*)value, sizeof(T));
    m_end += n;
    return pos;
}

}  // namespace soa::native::containers
