#include "frontend/movie.h"

#include <GLES3/gl3.h>
#include <fcntl.h>
#include <signal.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <cstring>
#include <deque>
#include <fstream>
#include <mutex>
#include <thread>
#include <vector>

#include "android/ndk.h"
#include "android/platform.h"
#include "core/log.h"
#include "core/vfs.h"

extern char** environ;

namespace soa {

namespace {

struct Proc {
    pid_t pid = -1;
    int fd = -1;
};

// Runs argv with stdout on a pipe.
Proc spawn_reader(const std::vector<std::string>& args) {
    int p[2];
    if (pipe2(p, O_CLOEXEC) != 0) return {};
    posix_spawn_file_actions_t fa;
    posix_spawn_file_actions_init(&fa);
    posix_spawn_file_actions_adddup2(&fa, p[1], 1);
    // Don't leak the game's (or the other decoder's) descriptors into the child.
    posix_spawn_file_actions_addclosefrom_np(&fa, 3);
    std::vector<char*> argv;
    for (auto& a : args) argv.push_back((char*)a.c_str());
    argv.push_back(nullptr);
    pid_t pid;
    int r = posix_spawnp(&pid, argv[0], &fa, nullptr, argv.data(), environ);
    posix_spawn_file_actions_destroy(&fa);
    close(p[1]);
    if (r != 0) {
        close(p[0]);
        return {};
    }
    return {pid, p[0]};
}

void kill_proc(Proc& p) {
    if (p.fd >= 0) close(p.fd);
    if (p.pid > 0) {
        kill(p.pid, SIGKILL);
        waitpid(p.pid, nullptr, 0);
    }
    p = {};
}

std::string run_capture(const std::vector<std::string>& args) {
    Proc p = spawn_reader(args);
    if (p.fd < 0) return {};
    std::string out;
    char buf[4096];
    ssize_t n;
    while ((n = read(p.fd, buf, sizeof buf)) > 0) out.append(buf, n);
    close(p.fd);
    waitpid(p.pid, nullptr, 0);
    return out;
}

bool read_full(int fd, void* dst, size_t n) {
    auto* d = (char*)dst;
    while (n) {
        ssize_t r = read(fd, d, n);
        if (r <= 0) return false;
        d += r;
        n -= r;
    }
    return true;
}

struct Movie {
    std::string input;
    int w = 0, h = 0;
    double fps = 30;
    float volume = 1;
    Proc video, audio;
    std::thread video_thread, audio_thread;
    std::atomic<bool> stop{false}, video_done{false}, audio_done{false};

    std::mutex frame_m;
    std::vector<unsigned char> frame;  // latest decoded frame (RGBA)
    bool frame_dirty = false;

    std::mutex audio_m;
    std::deque<float> samples;  // interleaved stereo at 48 kHz
    u64 consumed = 0;           // stereo frames taken out of `samples` (played or dropped)
    std::chrono::steady_clock::time_point start;
};

constexpr int kMovieRate = 48000;
// How far audio may lag the wall clock before it is dropped (device latency allowance).
constexpr double kAudioSlack = 0.5;

// Audio is paced by the wall clock, not only by the audio device: samples the device hasn't
// taken by the time they are kAudioSlack late are dropped. Without this a missing, failed or
// stalled audio device (no SDL callback: headless runs, WSLg audio hiccups) kept the decoder
// blocked on a full buffer, so audio_done / movie_active() never changed and the game's
// MovieFinished() polling never saw the end. Call with audio_m held.
void drop_late_audio(Movie* m) {
    double t = std::chrono::duration<double>(std::chrono::steady_clock::now() - m->start).count() - kAudioSlack;
    if (t <= 0) return;
    u64 due = (u64)(t * kMovieRate);
    if (m->consumed >= due) return;
    size_t n = std::min<size_t>(m->samples.size(), (size_t)(due - m->consumed) * 2);
    m->samples.erase(m->samples.begin(), m->samples.begin() + n);
    m->consumed += n / 2;
}

std::mutex g_m;
std::unique_ptr<Movie> g_movie;
std::atomic<bool> g_active{false};
std::atomic<bool> g_mixer_stalled{false};  // test hook: movie_mix_audio takes nothing
std::string g_tmp_file;

// GL objects (render thread only)
GLuint g_tex = 0, g_fbo = 0;
int g_tex_w = 0, g_tex_h = 0;

void video_loop(Movie* m) {
    size_t sz = (size_t)m->w * m->h * 4;
    std::vector<unsigned char> buf(sz);
    for (u64 k = 0; !m->stop; k++) {
        if (!read_full(m->video.fd, buf.data(), sz)) break;
        auto due = m->start + std::chrono::microseconds((u64)(k * 1e6 / m->fps));
        while (!m->stop && std::chrono::steady_clock::now() < due) std::this_thread::sleep_for(std::chrono::milliseconds(2));
        std::lock_guard lk(m->frame_m);
        m->frame.swap(buf);
        buf.resize(sz);
        m->frame_dirty = true;
    }
    m->video_done = true;
}

void audio_loop(Movie* m) {
    std::vector<float> buf(4096);
    while (!m->stop) {
        ssize_t n = read(m->audio.fd, buf.data(), buf.size() * sizeof(float));
        if (n <= 0) break;
        // Don't run far ahead of playback.
        for (;;) {
            {
                std::lock_guard lk(m->audio_m);
                drop_late_audio(m);
                if (m->samples.size() < kMovieRate * 2) {
                    m->samples.insert(m->samples.end(), buf.begin(), buf.begin() + n / sizeof(float));
                    break;
                }
            }
            if (m->stop) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
    m->audio_done = true;
}

}  // namespace

bool movie_start(const std::string& path, bool is_file, float volume) {
    movie_stop();
    auto m = std::make_unique<Movie>();
    m->volume = volume;
    if (is_file) {
        m->input = host_path(path.c_str());
    } else {
        AssetManager::Found f;
        std::string dl;
        if (asset_manager().find_download(path, dl) && (asset_manager().download_prefer() || !asset_manager().find(path, f))) {
            m->input = dl;  // --download-dir: builtin_data/<rel> served from the download tree
        } else if (!asset_manager().find(path, f)) {
            LOGE("movie", "asset %s not found", path.c_str());
            return false;
        } else {
            // ffmpeg's subfile protocol reads the (uncompressed) entry in place inside the APK.
            u64 start = f.zip->data_offset_of(*f.entry);
            if (f.entry->method == 0) {
                m->input = "subfile,,start," + std::to_string(start) + ",end," + std::to_string(start + f.entry->size) + ",,:" + f.zip->path();
            } else {
                std::vector<uint8_t> data;
                f.zip->extract(*f.entry, data);
                g_tmp_file = vfs_config().root + "/movie.tmp.mp4";
                std::ofstream(g_tmp_file, std::ios::binary).write((const char*)data.data(), data.size());
                m->input = g_tmp_file;
            }
        }
    }
    std::string probe = run_capture({"ffprobe", "-v", "error", "-select_streams", "v:0", "-show_entries", "stream=width,height,r_frame_rate", "-of", "csv=p=0", m->input});
    int num = 30, den = 1;
    if (sscanf(probe.c_str(), "%d,%d,%d/%d", &m->w, &m->h, &num, &den) < 2 || m->w <= 0 || m->h <= 0) {
        LOGE("movie", "ffprobe failed for %s (is ffmpeg installed?): %s", m->input.c_str(), probe.c_str());
        return false;
    }
    m->fps = den ? (double)num / den : 30.0;
    if (m->fps <= 1 || m->fps > 240) m->fps = 30;
    // The game's movies are stored portrait with the picture rotated; Android shows them in a
    // portrait-locked activity while the phone is held landscape. Rotate them upright.
    std::vector<std::string> vargs = {"ffmpeg", "-v", "error", "-nostdin", "-i", m->input};
    if (m->h > m->w) {
        vargs.insert(vargs.end(), {"-vf", "transpose=2"});
        std::swap(m->w, m->h);
    }
    vargs.insert(vargs.end(), {"-f", "rawvideo", "-pix_fmt", "rgba", "-"});
    m->video = spawn_reader(vargs);
    m->audio = spawn_reader({"ffmpeg", "-v", "error", "-nostdin", "-i", m->input, "-vn", "-f", "f32le", "-ac", "2", "-ar", "48000", "-"});
    if (m->video.fd < 0) {
        LOGE("movie", "couldn't run ffmpeg");
        kill_proc(m->audio);
        return false;
    }
    LOGI("movie", "playing %s (%dx%d @ %.2f fps)", path.c_str(), m->w, m->h, m->fps);
    m->start = std::chrono::steady_clock::now();
    Movie* raw = m.get();
    m->video_thread = std::thread(video_loop, raw);
    if (m->audio.fd >= 0) m->audio_thread = std::thread(audio_loop, raw);
    else m->audio_done = true;
    std::lock_guard lk(g_m);
    g_movie = std::move(m);
    g_active = true;
    return true;
}

void movie_stop() {
    std::unique_ptr<Movie> m;
    {
        std::lock_guard lk(g_m);
        m = std::move(g_movie);
        g_active = false;
    }
    if (!m) return;
    m->stop = true;
    kill_proc(m->video);
    kill_proc(m->audio);
    if (m->video_thread.joinable()) m->video_thread.join();
    if (m->audio_thread.joinable()) m->audio_thread.join();
    if (!g_tmp_file.empty()) unlink(g_tmp_file.c_str()), g_tmp_file.clear();
    LOGI("movie", "stopped");
}

bool movie_active() {
    if (!g_active) return false;
    std::lock_guard lk(g_m);
    if (!g_movie) return false;
    if (g_movie->video_done && g_movie->audio_done) {
        std::lock_guard lk2(g_movie->audio_m);
        drop_late_audio(g_movie.get());
        if (g_movie->samples.empty()) return false;
    }
    return true;
}

void movie_draw(int ww, int wh, unsigned target_fbo) {
    std::lock_guard lk(g_m);
    Movie* m = g_movie.get();
    if (!m) return;
    if (!g_tex) {
        glGenTextures(1, &g_tex);
        glGenFramebuffers(1, &g_fbo);
    }
    GLint prev_tex, prev_unpack, prev_align, prev_read;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &prev_tex);
    glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &prev_unpack);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &prev_align);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &prev_read);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glBindTexture(GL_TEXTURE_2D, g_tex);
    if (g_tex_w != m->w || g_tex_h != m->h) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m->w, m->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        g_tex_w = m->w, g_tex_h = m->h;
        std::vector<unsigned char> black((size_t)m->w * m->h * 4, 0);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m->w, m->h, GL_RGBA, GL_UNSIGNED_BYTE, black.data());
    }
    {
        std::lock_guard fl(m->frame_m);
        if (m->frame_dirty) {
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m->w, m->h, GL_RGBA, GL_UNSIGNED_BYTE, m->frame.data());
            m->frame_dirty = false;
        }
    }
    glBindFramebuffer(GL_READ_FRAMEBUFFER, g_fbo);
    glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_tex, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target_fbo);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    double sa = (double)m->w / m->h, da = (double)ww / std::max(1, wh);
    int dw = ww, dh = wh;
    if (da > sa) dw = (int)(wh * sa + 0.5);
    else dh = (int)(ww / sa + 0.5);
    int dx = (ww - dw) / 2, dy = (wh - dh) / 2;
    // Decoded rows are top-down; flip while blitting.
    glBlitFramebuffer(0, 0, m->w, m->h, dx, dy + dh, dx + dw, dy, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, prev_read);
    glBindTexture(GL_TEXTURE_2D, prev_tex);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, prev_unpack);
    glPixelStorei(GL_UNPACK_ALIGNMENT, prev_align);
}

void movie_test_stall_mixer(bool stalled) { g_mixer_stalled = stalled; }

void movie_mix_audio(float* out, int frames, int rate) {
    if (!g_active || g_mixer_stalled) return;
    std::lock_guard lk(g_m);
    Movie* m = g_movie.get();
    if (!m) return;
    std::lock_guard al(m->audio_m);
    size_t n = std::min<size_t>(m->samples.size(), (size_t)frames * 2);
    for (size_t i = 0; i < n; i++) out[i] += m->samples[i] * m->volume;
    m->samples.erase(m->samples.begin(), m->samples.begin() + n);
    m->consumed += n / 2;
}

}  // namespace soa
