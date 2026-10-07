#pragma once
// The guest functions and constants the params natives call or pass on (internal to the subsystem):
// the asserts' file names and messages, AMap::Get_(char const*) (data_formats: the guest's, or its
// native once bound), StringToNumber<T> (an istringstream: left to the guest), the game string's
// out-of-line growth helpers (libcxx) and the STL allocator (memory). Every address is the 3.7.0 lib's;
// test params/guest-constants reads the strings back.
#include <cstring>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/gen/common_addresses.h"
#include "native/params/gen/params_addresses.h"
#include "native/params/params_layout.h"

namespace soa::native::params::g {

// The constants (their vaddrs): params/addresses.txt -> gen/params_addresses.h (in this namespace), and
// common's kStrStlAllocatorH / kStrStlStringH / kStrNumElementsIsZero / kStrAllocatedMemoryIsNull.

inline u64 at(u64 vaddr) { return main_lib()->base + vaddr; }
u64 sym(const char* mangled);  // cached per call site by the callers (fatal when missing)

// Framework::gDoAssert(file, line, message): logs; the caller carries on as the guest does.
void Assert(u64 file_vaddr, int line, u64 msg_vaddr);
// Aska::ASON::AValue::AMap::Get_(char const*).
const AValue* AMapGet(const AMap* map, const char* key);
// StringToNumber<T>(char*) (T = int, unsigned, long, unsigned long, unsigned char).
s32 StringToInt(const char* s);
u32 StringToUInt(const char* s);
s64 StringToLong(const char* s);
u64 StringToULong(const char* s);
u8 StringToUTiny(const char* s);
// The game string's __grow_by / __grow_by_and_replace.
void GrowBy(String* s, u64 old_cap, u64 delta_cap, u64 old_sz, u64 n_copy, u64 n_del, u64 n_add);
void GrowByAndReplace(String* s, u64 old_cap, u64 delta_cap, u64 old_sz, u64 n_copy, u64 n_del, u64 n_add, const char* p);
// Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(n, file, line) / Free.
void* StlAllocate(u64 n, u64 file_vaddr, u32 line);
void StlFree(void* p);

}  // namespace soa::native::params::g
