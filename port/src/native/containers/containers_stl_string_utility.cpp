// Framework::CSTLStringUtility_Base<std::string>::ReplaceSelf / Replace: replace every occurrence of
// a string (port/decomp/containers/strings.c). The string is the game's CSTL basic_string (libcxx's
// layout); replace is basic_string::replace (libcxx_string.cpp), whose storage comes from the guest's
// STL allocator.
#include <string_view>

#include "native/common/live_leaf.h"
#include "native/containers/containers_family.h"
#include "native/containers/containers_string_utility.h"
#include "native/libcxx/libcxx_layout.h"
#include "native/libcxx/libcxx_string.h"

namespace soa::native::containers {

using String = libcxx::basic_string<char>;

// Framework::CSTLStringUtility_Base<S> for the game's string: static helpers only (no object).
class CSTLStringUtility {
public:
    // Replaces each occurrence of `from` in s (searching on after each replacement) by `to`;
    // *replaced (when given) tells whether any was. Returns s. (An empty `from` matches at every
    // position: with an empty `to` the guest loops for ever, and so does this.)
    static String* ReplaceSelf(String* s, const String& from, const String& to, bool* replaced);
    // A copy of src with ReplaceSelf applied (an x8 result).
    static void Replace(String* out, const String& src, const String& from, const String& to, bool* replaced);
};

String* CSTLStringUtility::ReplaceSelf(String* s, const String& from, const String& to, bool* replaced) {
    if (replaced) *replaced = false;
    for (u64 pos = 0;;) {
        std::string_view hay(s->data(), s->size()), needle(from.data(), from.size());
        if (pos > hay.size() || hay.size() - pos < needle.size()) return s;
        u64 at = needle.empty() ? pos : hay.find(needle, pos);
        if (at == std::string_view::npos) return s;
        libcxx::string_replace(s, at, needle.size(), to.data(), to.size());
        if (replaced) *replaced = true;
        pos = at + to.size();
    }
}

void CSTLStringUtility::Replace(String* out, const String& src, const String& from, const String& to, bool* replaced) {
    String tmp;
    libcxx::string_copy_construct(&tmp, src);
    ReplaceSelf(&tmp, from, to, replaced);
    libcxx::string_copy_construct(out, tmp);
    libcxx::string_destroy(&tmp);
}

// ---- natives ----

namespace {
void ReplaceSelf_(Cpu& c) {
    c.set_x(0, (u64)CSTLStringUtility::ReplaceSelf(reinterpret_cast<String*>(c.x(0)), *reinterpret_cast<const String*>(c.x(1)),
                                                   *reinterpret_cast<const String*>(c.x(2)), reinterpret_cast<bool*>(c.x(3))));
}
void Replace_(Cpu& c) {
    CSTLStringUtility::Replace(reinterpret_cast<String*>(c.x(8)), *reinterpret_cast<const String*>(c.x(0)), *reinterpret_cast<const String*>(c.x(1)),
                               *reinterpret_cast<const String*>(c.x(2)), reinterpret_cast<bool*>(c.x(3)));
}
}  // namespace

#define UTIL_SYM(m) \
    "_ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE" m
LEAF_HOSTFN(family(), UTIL_SYM("11ReplaceSelfERS8_RKS8_SC_Pb"), &ReplaceSelf_, sizeof(String), live::kInt,
            "Framework::CSTLStringUtility_Base<std::string>::ReplaceSelf", {live::out(3, 1)});
LEAF_HOSTFN(family(), UTIL_SYM("7ReplaceERKS8_SB_SB_Pb"), &Replace_, 0, live::kVoid, "Framework::CSTLStringUtility_Base<std::string>::Replace",
            {live::out(8, sizeof(String)), live::out(3, 1)});
#undef UTIL_SYM

// (containers_string_utility.h)
String* stl_replace_self(String* s, const String& from, const String& to, bool* replaced) { return CSTLStringUtility::ReplaceSelf(s, from, to, replaced); }
void stl_replace(String* out, const String& src, const String& from, const String& to, bool* replaced) {
    CSTLStringUtility::Replace(out, src, from, to, replaced);
}

}  // namespace soa::native::containers
