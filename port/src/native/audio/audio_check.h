#pragma once
// The live checks of the audio natives:
//   soa --live-check audio[:every=N][:budget=N][:only=..][:out=FILE]       (shadow checks, below)
//   soa --live-check audio_leaf[:every=N][:budget=N][:only=..][:out=FILE]  (record / replay leaves)
//
// `audio` is a shadow family (native/common/shadow_check.h): the signal path's voice lists are shared
// by the sound manager thread (Add / Delete), the dispatcher's worker running the notifies (Handler)
// and AudioSignal's task (GetSignalCount). The getter runs the guest original on the real object right
// after the native; the mutators and Handler run the guest original, under the notify's own lock, on a
// shadow notify built from the slots the native saw (audio_signal.cpp).
// `audio_leaf` is a record / replay family (native/common/live_leaf.h) for the pure leaves (the ADPCM
// decoder): the object, the input and the output buffers snapshotted and compared.
#include "native/common/live_leaf.h"
#include "native/common/shadow_check.h"

namespace soa::native::audio {

live::ShadowFamily& family();
live::LeafFamily& leaf_family();
struct CheckedFn : live::ShadowFn {
    explicit CheckedFn(const char* s) : ShadowFn(family(), s) {}
};

}  // namespace soa::native::audio
