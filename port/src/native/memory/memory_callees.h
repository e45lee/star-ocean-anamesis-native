#pragma once
// memory's natives that other subsystems' natives call (native/common/native_call.h): the STL
// allocator's Allocate / Free and MemoryManager::CalcFreeSize(bool). A caller tests direct() and calls
// the member, else makes its own guest call (guest_call, or live::out_call in a record / replay family)
// to addr().
#include "native/common/native_call.h"
#include "native/memory/memory_layout.h"

namespace soa::native::memory {

extern NativeCallee kStlAllocateCallee;   // CAssignedMemoryManagerForSTLAllocator::Allocate(size, file, line)
extern NativeCallee kStlFreeCallee;       // CAssignedMemoryManagerForSTLAllocator::Free(p)
extern NativeCallee kCalcFreeSizeCallee;  // MemoryManager::CalcFreeSize(bool)

}  // namespace soa::native::memory
