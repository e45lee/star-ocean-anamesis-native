// --selftest: a movie must report its end even when no audio device drains its sound (headless
// runs, a failed SDL_OpenAudioDevice, a stalled WSLg sink). Before the wall-clock audio pacing the
// decoder blocked on a full 1 s buffer and movie_active() stayed true forever, so the game's
// MovieFinished() polling never saw the end (Episode 2/3 opening movies).
#include <sys/stat.h>
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <string>
#include <thread>

#include "core/vfs.h"
#include "frontend/movie.h"
#include "core/selftest.h"

namespace soa {
namespace {

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
    if (system("ffmpeg -version >/dev/null 2>&1") != 0) return;  // no ffmpeg: movies can't play at all
    // A 2 s clip with a sine track, written where the guest path /tmp/... maps (rootfs).
    const std::string guest = "/tmp/soa_movie_selftest.mp4";
    std::string host = host_path(guest.c_str());
    make_dirs(host.substr(0, host.rfind('/')));
    std::string cmd = "ffmpeg -v error -y -f lavfi -i testsrc=size=64x36:rate=30:duration=2 -f lavfi -i sine=frequency=440:duration=2 "
                      "-c:v libx264 -pix_fmt yuv420p -c:a aac -shortest '" + host + "' </dev/null";
    if (system(cmd.c_str()) != 0) {
        cmd = "ffmpeg -v error -y -f lavfi -i testsrc=size=64x36:rate=30:duration=2 -f lavfi -i sine=frequency=440:duration=2 -shortest '" + host + "' </dev/null";
        if (system(cmd.c_str()) != 0) { t.fail("couldn't make the test clip"); return; }
    }
    double took = play_until_end(guest, 10);
    unlink(host.c_str());
    if (took < 0) t.fail("the 2 s movie didn't report its end within 10 s with no audio drain");
    else if (took < 1.5) t.fail("the 2 s movie ended early (%.2f s)", took);
}

}  // namespace
}  // namespace soa
