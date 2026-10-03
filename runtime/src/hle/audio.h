#pragma once

namespace soa {

// Mixes all OpenSL ES players into `out` (interleaved stereo float, overwritten) and runs
// the guest's buffer-queue callbacks for buffers that finished. Called by the frontend.
void audio_mix(float* out, int frames, int rate);

// Starts the audio device/mixer thread: calls the host's HostHooks::start_audio (android/platform.h),
// which must be idempotent.
void audio_start_mixer();

}  // namespace soa
