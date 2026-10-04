// The live check of the resource natives: the family (resource_check.h).
#include "native/resource/resource_check.h"

namespace soa::native::resource {

live::ShadowFamily& family() {
    static live::ShadowFamily f("resource", 16);
    return f;
}
namespace {
[[maybe_unused]] live::ShadowFamily& g_family = family();  // (registered at start-up)
}  // namespace

}  // namespace soa::native::resource
