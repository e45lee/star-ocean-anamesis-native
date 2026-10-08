// The `dynamics` live-check family (dynamics_family.h).
#include "native/dynamics/dynamics_family.h"

namespace soa::native::dynamics {
DynamicsFamily& family() {
    static DynamicsFamily f;
    return f;
}
}  // namespace soa::native::dynamics
