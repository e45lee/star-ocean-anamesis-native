// The `libcxx` live-check family (libcxx_family.h).
#include "native/libcxx/libcxx_family.h"

namespace soa::native::libcxx {
live::LeafFamily& family() {
    static live::LeafFamily f("libcxx", 8);
    return f;
}
}  // namespace soa::native::libcxx
