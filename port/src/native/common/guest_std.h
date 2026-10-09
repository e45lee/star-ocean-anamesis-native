#pragma once
// Access to the game's C++ runtime objects from native code.
//
// The game is built against the NDK's libc++ (std::__ndk1) with Framework::CSTLAllocator,
// whose storage comes from Framework::CAssignedMemoryManagerForSTLAllocator. Native
// replacements that read or build those objects must keep that exact layout and allocator,
// because guest code elsewhere still uses them. These helpers do that.
#include <cstring>
#include <string>
#include <string_view>

#include "native/libcxx/libcxx_layout.h"
#include "soaruntime/core/cpu.h"

namespace soa::guest {

// Framework::CAssignedMemoryManagerForSTLAllocator::Allocate / Free
void* stl_alloc(size_t n);
void stl_free(void* p);
// operator new[](size_t, std::nothrow_t const&) / operator delete[](void*)
void* new_array_nothrow(size_t n);
void delete_array(void* p);
// Guest address of an exported symbol (fatal if missing).
u64 sym(const char* mangled);

// std::__ndk1::basic_string<char, ..., Framework::CSTLAllocator<char, ...>> (24 bytes): libcxx_layout.h's
// basic_string<char>, whose host-side helpers (init / assign / destroy, view / str) allocate through
// stl_alloc / stl_free.
using String = native::libcxx::basic_string<char>;

}  // namespace soa::guest
