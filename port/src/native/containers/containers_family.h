#pragma once
// The `containers` subsystem's live-check family (--live-check containers): every native of the subsystem is
// registered through it (native/common/live_leaf.h), so a normal run can compare each one with the
// guest original. A function-local static: the natives in every containers_*.cpp share it whatever the
// static-initialization order.
#include "native/common/live_leaf.h"

namespace soa::native::containers {
live::LeafFamily& family();
}  // namespace soa::native::containers
