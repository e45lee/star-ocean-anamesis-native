#pragma once
// The guest functions and constants the params natives call or pass on (internal to the subsystem):
// the asserts' file names and messages, AMap::Get_(char const*) (data_formats: the guest's, or its
// native once bound), StringToNumber<T> (an istringstream: left to the guest), the game string's
// out-of-line growth helpers (libcxx) and the STL allocator (memory). Every address is the 3.7.0 lib's;
// test params/guest-constants reads the strings back.
#include <cstring>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/params/params_layout.h"

namespace soa::native::params::g {

// vaddrs of the constants (Ghidra address - 0x100000).
constexpr u64 kParameterParserCpp = 0x275e860;  // "C:\BAS_Submission\...\Parameter\ParameterParser.cpp"
constexpr u64 kParameterParserH = 0x275e8e7;    // "...\Source\Game/Parameter/ParameterParser.h"
constexpr u64 kParameterBaseCpp = 0x275e3b2;    // "...\Parameter\ParameterBase.cpp"
constexpr u64 kApObjectIsNull = 0x275e8ae;      // "apObject is null."
constexpr u64 kApParserIsNull = 0x26dc58a;      // "apParser is null."
constexpr u64 kApValueIsNull = 0x275e8d6;       // "apValue is null."
constexpr u64 kNotFound = 0x275e8c0;            // "not found " (the by-key getters' dropped message)
constexpr u64 kNotMatch = 0x275e8cb;            // "not match "
constexpr u64 kEmptyString = 0x28d2011;         // "" (GetValueString's value when not found)
constexpr u64 kStlAllocatorH = 0x26db0be;       // "...\Framework/STL_Allocator.h"
constexpr u64 kNumElementsIsZero = 0x26db115;   // "aNumElements is zero."
constexpr u64 kAllocatedIsNull = 0x26db12b;     // "pAllocatedMemory is null."
constexpr u64 kStlStringH = 0x26db145;          // "...\Framework/STL_String.h"

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
