#pragma once
// The game string's members as other subsystems' natives call them (libcxx_string.cpp): the
// out-of-line replace, and the copy constructor / destructor the guest inlines (storage from the
// CSTL allocator, through live::out_call).
#include "native/libcxx/libcxx_layout.h"

namespace soa::native::libcxx {

// basic_string::replace(pos, n1, s, n2) (the native's body).
basic_string<char>* string_replace(basic_string<char>* self, u64 pos, u64 n1, const char* s, u64 n2);
// basic_string(basic_string const&) as the guest inlines it: a short source is copied whole; a long
// one gets (size + 16) & ~15 bytes (short when it fits in 22).
void string_copy_construct(basic_string<char>* self, const basic_string<char>& src);
// ~basic_string(): frees a long string's storage.
void string_destroy(basic_string<char>* self);

}  // namespace soa::native::libcxx
