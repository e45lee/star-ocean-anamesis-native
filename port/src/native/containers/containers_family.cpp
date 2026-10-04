// The `containers` live-check family (containers_family.h).
#include "native/containers/containers_family.h"

namespace soa::native::containers {
live::LeafFamily& family() {
    static live::LeafFamily f("containers", 8);
    return f;
}
}  // namespace soa::native::containers
