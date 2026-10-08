#pragma once
// Framework::CSTLStringUtility_Base<std::string>'s natives as C++ (containers_stl_string_utility.cpp),
// for other natives (native/common/native_call.h) and the tests.
#include "native/libcxx/libcxx_layout.h"

namespace soa::native::containers {

// ReplaceSelf(s, from, to, replaced): every occurrence of `from` in s replaced by `to`; returns s.
libcxx::basic_string<char>* stl_replace_self(libcxx::basic_string<char>* s, const libcxx::basic_string<char>& from,
                                             const libcxx::basic_string<char>& to, bool* replaced);
// Replace(src, from, to, replaced) into *out (the guest's x8 result): a copy of src, ReplaceSelf applied.
void stl_replace(libcxx::basic_string<char>* out, const libcxx::basic_string<char>& src, const libcxx::basic_string<char>& from,
                 const libcxx::basic_string<char>& to, bool* replaced);

}  // namespace soa::native::containers
