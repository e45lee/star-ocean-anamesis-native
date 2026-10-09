// --selftest: the movie player on FFmpeg's libraries (frontend/movie_decoder.h), with a clip built into
// the program (movie_test_clip.inc: H.264 + AAC, the game's codecs), so no ffmpeg program is needed.
//
// frontend/movie-ends-without-audio-device: a movie must report its end even when no audio device
// drains its sound (headless runs, a failed SDL_OpenAudioDevice, a stalled WSLg sink). Before the
// wall-clock audio pacing the decoder blocked on a full 1 s buffer and movie_active() stayed true
// forever, so the game's MovieFinished() polling never saw the end (Episode 2/3 opening movies).
#include <unistd.h>

#include <chrono>
#include <fstream>
#include <string>
#include <thread>

#include "soaruntime/core/selftest.h"
#include "soaruntime/core/vfs.h"
#include "frontend/movie.h"
#include "soaruntime/frontend/movie_decoder.h"

namespace soa {
namespace {

const unsigned char kClip[] = {
#include "frontend/movie_test_clip.inc"
};

// Writes the clip where the guest path /tmp/... maps (rootfs); the guest path, or "" on failure.
std::string write_clip(const char* name) {
    std::string guest = std::string("/tmp/") + name;
    std::string host = host_path(guest.c_str());
    make_dirs(host.substr(0, host.rfind('/')));
    std::ofstream f(host, std::ios::binary);
    f.write((const char*)kClip, sizeof kClip);
    return f.good() ? guest : std::string();
}

// Plays `guest_path` (a file path) with the mixer stalled; returns the seconds until
// movie_active() went false, or -1 after `limit` seconds.
double play_until_end(const std::string& guest_path, double limit) {
    movie_test_stall_mixer(true);
    auto t0 = std::chrono::steady_clock::now();
    double took = -1;
    if (movie_start(guest_path, true, 0.0f)) {
        for (;;) {
            double e = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();
            if (!movie_active()) { took = e; break; }
            if (e > limit) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
    movie_stop();
    movie_test_stall_mixer(false);
    return took;
}

RUNTIME_TEST("frontend/movie-ends-without-audio-device") {
    std::string guest = write_clip("soa_movie_selftest.mp4");
    if (guest.empty()) { t.fail("couldn't write the test clip"); return; }
    double took = play_until_end(guest, 10);
    unlink(host_path(guest.c_str()).c_str());
    if (took < 0) t.fail("the 2 s movie didn't report its end within 10 s with no audio drain");
    else if (took < 1.5) t.fail("the 2 s movie ended early (%.2f s)", took);
}

// The decoder on the clip, from memory (the in-place zip entry path) and from a file: every picture
// (B-frames: the delayed ones after the end too) and all the sound, the same both ways.
RUNTIME_TEST("frontend/movie-decodes-clip") {
    auto decode = [&](const MovieSource& src, int& frames, size_t& samples, uint64_t& sum) {
        frames = 0, samples = 0, sum = 0;
        std::string err;
        MovieStream v, a;
        if (!v.open(src, MovieStream::Kind::video, &err)) { t.fail("video: %s", err.c_str()); return; }
        t.expect_eq(v.width(), 36, "width");
        t.expect_eq(v.height(), 64, "height");
        t.expect_eq((int)(v.frame_rate() + 0.5), 30, "frame rate");
        MovieFrame f;
        while (v.next_video(f, &err)) {
            frames++;
            for (uint8_t b : f.planes) sum = sum * 31 + b;
        }
        if (!err.empty()) t.fail("video: %s", err.c_str());
        if (!a.open(src, MovieStream::Kind::audio, &err)) { t.fail("audio: %s", err.c_str()); return; }
        std::vector<float> s;
        while (a.next_audio(s, &err)) samples += s.size() / 2;
        if (!err.empty()) t.fail("audio: %s", err.c_str());
    };
    int frames_m, frames_f;
    size_t samples_m, samples_f;
    uint64_t sum_m, sum_f;
    decode(MovieSource::memory(kClip, sizeof kClip), frames_m, samples_m, sum_m);
    t.expect_eq(frames_m, 60, "pictures");
    // 2 s at 48 kHz, give or take the encoder's last frame (1024 samples)
    if (samples_m < 95000 || samples_m > 97000) t.fail("%zu sound samples, not about 96000", samples_m);
    std::string guest = write_clip("soa_movie_decode.mp4");
    if (guest.empty()) { t.fail("couldn't write the test clip"); return; }
    decode(MovieSource::file(host_path(guest.c_str())), frames_f, samples_f, sum_f);
    unlink(host_path(guest.c_str()).c_str());
    t.expect_eq(frames_f, frames_m, "pictures from a file");
    t.expect_eq((uint64_t)samples_f, (uint64_t)samples_m, "samples from a file");
    t.expect_eq(sum_f, sum_m, "pictures from a file = from memory");
}

}  // namespace
}  // namespace soa
