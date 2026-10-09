#pragma once
// std::function's copy constructor and destructor as the guest inlines them (libc++ 6's <functional>,
// libcxx_layout.h `function`), for natives that hold the game's std::function objects. The callable
// stays the guest's: both go through its __base vtable (kFuncSlot*), so they are guest calls.
#include "native/libcxx/libcxx_layout.h"

namespace soa::native::libcxx {

// function(function const& src) into uninitialised storage at dst: empty stays empty; an inline callable
// is cloned into dst's buffer (__clone(__base*), slot 3, after dst's __f_ points at it); a heap one is
// cloned onto the heap (__clone(), slot 2).
void function_copy_construct(function* dst, const function& src);
// ~function(): an inline callable's destroy() (slot 4), a heap one's destroy_deallocate() (slot 5).
void function_destroy(function* f);
// The guest address in slot `s` of the callable's __base vtable (f must not be empty).
u64 function_slot(const function& f, FunctionSlot s);

}  // namespace soa::native::libcxx
