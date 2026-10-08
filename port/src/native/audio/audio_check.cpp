// The audio live-check families (audio_check.h).
#include "native/audio/audio_check.h"

namespace soa::native::audio {

live::ShadowFamily& family() {
    static live::ShadowFamily f("audio", 16);
    return f;
}
live::LeafFamily& leaf_family() {
    static live::LeafFamily f("audio_leaf", 16);
    return f;
}
namespace {
[[maybe_unused]] live::ShadowFamily& g_family = family();         // (registered at start-up)
[[maybe_unused]] live::LeafFamily& g_leaf_family = leaf_family();
}  // namespace

}  // namespace soa::native::audio
