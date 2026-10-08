// The master natives' live-check family (master_family.h).
#include "native/master/master_family.h"

namespace soa::native::master {

live::RunBothFamily& fam() {
    static live::RunBothFamily f("master", 8);
    return f;
}

live::Family& family() { return fam().family(); }

}  // namespace soa::native::master
