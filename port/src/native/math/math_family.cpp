// The `math` live-check family (math_family.h).
#include "native/math/math_family.h"

namespace soa::native::math {
live::LeafFamily& family() {
    static live::LeafFamily f("math", 1);
    return f;
}
}  // namespace soa::native::math
