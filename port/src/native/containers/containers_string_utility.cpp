// Aska::StringUtility (containers_layout.h; port/decomp/containers/strings.c).
#include <cstring>

#include "native/containers/containers_family.h"
#include "native/containers/containers_layout.h"

namespace soa::native::containers {

// On Android the "multibyte" encoding is UTF-8 itself: a counted copy. The size query (dst null,
// cap 0) and the copy both count the terminator; a copy is cut at cap (then unterminated). A null
// dst with a cap, or a dst without one, is a bad argument (Aska::Status -0x3bd, as a u32).
u64 StringUtility::Utf8ToMultiByte(const char* src, char* dst, u32 cap) {
    if ((dst == nullptr) != (cap == 0)) return 0xfffffc43u;
    u64 n = std::strlen(src) + 1;
    if (!dst) return (u32)n;
    u64 c = n < cap ? n : cap;
    std::strncpy(dst, src, c);
    return (u32)c;
}

// ---- natives ----

LEAF_FUNCTION(family(), "_ZN4Aska13StringUtility15Utf8ToMultiByteEPKcPcj", &StringUtility::Utf8ToMultiByte, live::kInt,
              "Aska::StringUtility::Utf8ToMultiByte", {live::out_len(1, 2)});

}  // namespace soa::native::containers
