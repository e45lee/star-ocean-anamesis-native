#pragma once
// The guest functions and constants the master natives call or pass on (internal to the subsystem):
// the STL allocator (memory), operator delete, the assert. Calls go through live::out_call (a live
// check records them); every address is the 3.7.0 lib's.
#include "soaruntime/core/cpu.h"
#include "soaruntime/core/loader.h"
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
// Framework::gDoAssert(file, line, message) (vaddrs; logs, and the caller carries on as the guest does).
void Assert(u64 file_vaddr, int line, u64 msg_vaddr);

}  // namespace soa::native::master::g
