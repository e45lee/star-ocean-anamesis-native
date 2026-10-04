#pragma once
// The `hash` subsystem's live-check family (--live-check hash): every native of the subsystem is
// registered through it (native/common/live_leaf.h), so a normal run can compare each one with
// the guest original. A function-local static: the natives in every hash_*.cpp share it whatever
// the static-initialization order.
#include "native/common/live_leaf.h"

namespace soa::native::hash {
live::LeafFamily& family();
}  // namespace soa::native::hash
