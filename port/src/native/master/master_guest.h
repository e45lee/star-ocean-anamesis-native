#pragma once
// The guest functions and constants the master natives call or pass on (internal to the subsystem):
// the STL allocator (memory), operator delete, the assert. Calls go through live::out_call (a live
// check records them); every address is the 3.7.0 lib's.
#include "core/cpu.h"
#include "core/loader.h"
#include "native/master/master_layout.h"

namespace soa::native::master::g {

inline u64 at(u64 vaddr) { return main_lib()->base + vaddr; }
u64 sym(const char* mangled);  // fatal when missing; callers cache it

// Framework::CAssignedMemoryManagerForSTLAllocator::Allocate(n, "...STL_String.h", 0x1c) (a string's
// storage) / Free.
void* StringAllocate(u64 n);
void StlFree(void* p);
// operator delete(void*) (a deleting destructor's).
void OperatorDelete(void* p);

}  // namespace soa::native::master::g
