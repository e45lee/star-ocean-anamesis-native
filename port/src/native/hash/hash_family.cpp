// The `hash` live-check family (hash_family.h).
#include "native/hash/hash_family.h"

namespace soa::native::hash {
live::LeafFamily& family() {
    static live::LeafFamily f("hash", 8);
    return f;
}
}  // namespace soa::native::hash
