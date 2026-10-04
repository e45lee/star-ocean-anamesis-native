#pragma once
// MoviePlayerActivity replacement: plays the game's MP4s, decoded with FFmpeg's libraries
// (frontend/movie_decoder.h) and drawn by the host over the game's frame (YUV to RGB in a shader).
#include <string>

namespace soa {

// Starts playback (returns false if the movie can't be opened). `is_file` selects a
// filesystem path (guest path) vs. an asset path, mirroring MoviePlayerActivity.
bool movie_start(const std::string& path, bool is_file, float volume);
void movie_stop();
bool movie_active();

// Render thread: draws the current frame over the window's framebuffer (`target_fbo`: 0, or the
// offscreen one that stands for it, hle/gfx.h GfxHooks::draw_overlay).
void movie_draw(int window_w, int window_h, unsigned target_fbo);
// Audio thread: adds movie audio (interleaved stereo float at `rate`) into out.
void movie_mix_audio(float* out, int frames, int rate);
// Test hook: while set, movie_mix_audio consumes nothing (a stalled or missing audio device).
void movie_test_stall_mixer(bool stalled);

}  // namespace soa
