// The `containers` live-check family (containers_family.h).
#include "native/containers/containers_family.h"

namespace soa::native::containers {
ContainersFamily& family() {
    static ContainersFamily f;
    return f;
}
}  // namespace soa::native::containers
