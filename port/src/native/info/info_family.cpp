// The info natives' live-check family (info_family.h).
#include "native/info/info_family.h"

namespace soa::native::info {

live::RunBothFamily& fam() {
    static live::RunBothFamily f("info", 8);
    return f;
}

}  // namespace soa::native::info
