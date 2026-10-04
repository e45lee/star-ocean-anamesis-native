// yayoi_guest.h: the guest functions the SQLite driver's natives still call (other subsystems' code
// that isn't native yet: memory's allocators, TSharedPointerCode's counters, data_formats' ASON), as
// guest calls with their symbols looked up once. Pointers handed to them are host pointers (guest
// memory is identity-mapped), host stack objects included.
#pragma once

#include "core/cpu.h"
#include "native/common/guest_std.h"
#include "native/yayoi/yayoi_layout.h"

namespace soa::native::yayoi::gfn {

// Aska::MemoryManagerAdapter::AlignedMalloc / AlignedFree (the column map's buckets).
inline void* aligned_malloc(u64 size, u64 align) {
    static const u64 fn = guest::sym("_ZN4Aska20MemoryManagerAdapter13AlignedMallocEmm");
    return (void*)guest_call(fn, {size, align});
}
inline void aligned_free(void* p) {
    static const u64 fn = guest::sym("_ZN4Aska20MemoryManagerAdapter11AlignedFreeEPv");
    guest_call(fn, {(u64)p});
}
// operator delete(void*) (the map's deleting destructor).
inline void operator_delete(void* p) {
    static const u64 fn = guest::sym("_ZdlPv");
    guest_call(fn, {(u64)p});
}
// Aska::TSharedPointerCode::CreateCounter(int) / DeleteCounter(int*).
inline s32* create_counter(s32 initial) {
    static const u64 fn = guest::sym("_ZN4Aska18TSharedPointerCode13CreateCounterEi");
    return (s32*)guest_call(fn, {(u64)(u32)initial});
}
inline void delete_counter(s32* p) {
    static const u64 fn = guest::sym("_ZN4Aska18TSharedPointerCode13DeleteCounterEPi");
    guest_call(fn, {(u64)p});
}
// Aska::ASON (data_formats; the object is the caller's, 0x90 bytes).
void ason_ctor(void* ason);
void ason_dtor(void* ason);
s64 ason_init(void* ason, u32 work_size, bool keep_cstrings);        // Init(unsigned int, bool)
s64 ason_make_array(void* ason, void* value, u32 n);                 // MakeAValue_Array (Status)
s64 ason_make_map(void* ason, void* value, u32 n);                   // MakeAValue_Map (Status)
void* ason_malloc(void* ason, u64 n);                                // Malloc
s64 ason_calc_serialized_size(const void* ason);                     // CalcSerializedSize
s64 ason_serialize(const void* ason, void* out, u64 size);           // Serialize(void*, unsigned long)

}  // namespace soa::native::yayoi::gfn
