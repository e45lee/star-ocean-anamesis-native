#pragma once
// Shared by the ASON natives (data_formats_ason_*.cpp): the guest allocator calls they make (through
// live::out_call, so a live check records them), msgpack's big-endian loads / stores, and the live-check
// regions of an ASON's bump allocator.
#include <cstring>

#include "core/loader.h"
#include "native/common/live_call.h"
#include "native/data_formats/data_formats_family.h"
#include "native/data_formats/data_formats_layout.h"

namespace soa::native::data_formats::ason {

// operator new[](n, std::nothrow) / operator delete[] of the game (the ASON's blocks and temporaries).
inline void* new_array_nothrow(u64 n) {
    static const u64 fn = main_lib()->sym("_ZnamRKSt9nothrow_t");
    static const u64 nothrow = main_lib()->sym("_ZSt7nothrow");
    return (void*)live::out_call(family(), fn, {n, nothrow});
}
inline void delete_array(void* p) {
    static const u64 fn = main_lib()->sym("_ZdaPv");
    live::out_call(family(), fn, {(u64)p});
}

inline u16 load_be16(const u8* p) { return (u16)(p[0] << 8 | p[1]); }
inline u32 load_be32(const u8* p) { return (u32)p[0] << 24 | (u32)p[1] << 16 | (u32)p[2] << 8 | p[3]; }
inline u64 load_be64(const u8* p) { return (u64)load_be32(p) << 32 | load_be32(p + 4); }
inline void store_be16(u8* p, u16 v) { p[0] = (u8)(v >> 8), p[1] = (u8)v; }
inline void store_be32(u8* p, u32 v) { store_be16(p, (u16)(v >> 16)), store_be16(p + 2, (u16)v); }
inline void store_be64(u8* p, u64 v) { store_be32(p, (u32)(v >> 32)), store_be32(p + 4, (u32)v); }

// The live-check regions of an ASON's allocator: the block Malloc bumps (its unused tail, where a
// call's new values go), its WorkBufferContext, and TemporaryMalloc's scratch.
inline void add_allocator_regions(u64 ason, live::Regions& r) {
    if (!ason) return;
    const ASON* a = reinterpret_cast<const ASON*>(ason);
    if (const ASON_WorkBufferContext* w = a->m_currentWork) {
        add_region(r, (u64)w, sizeof *w);
        if (w->m_buffer && w->m_used < w->m_size) add_region(r, (u64)(w->m_buffer + w->m_used), w->m_size - w->m_used);
    }
    add_region(r, (u64)a->m_temp, a->m_tempSize);
}

// An x8-result HostFn's Status out.
inline void set_status(Cpu& c, Status s) { *reinterpret_cast<Status*>(c.x(8)) = s; }

}  // namespace soa::native::data_formats::ason
