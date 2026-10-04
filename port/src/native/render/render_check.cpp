// The live check of the render natives: the family (render_check.h).
#include "native/render/render_check.h"

namespace soa::native::render {

live::RunBothFamily& fam() {
    static live::RunBothFamily f("render", 1);
    return f;
}

}  // namespace soa::native::render
