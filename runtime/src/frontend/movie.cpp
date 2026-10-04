#include "frontend/movie.h"

#include <GLES3/gl3.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstring>
#include <deque>
#include <iterator>
#include <mutex>
#include <thread>
#include <vector>

#include "android/ndk.h"
#include "android/platform.h"
#include "core/log.h"
#include "core/vfs.h"
#include "frontend/movie_decoder.h"

namespace soa {

namespace {

struct Movie {
    MovieSource source;
    int w = 0, h = 0;  // the picture as shown (after the rotation below)
    int src_w = 0, src_h = 0;  // as decoded
    bool rotate = false;
    double fps = 30;
    float volume = 1;
    MovieStream video, audio;
    bool has_audio = false;
    std::thread video_thread, audio_thread;
    std::atomic<bool> stop{false}, video_done{false}, audio_done{false};

    std::mutex frame_m;
    MovieFrame frame;  // latest decoded picture (yuv420p planes)
    bool frame_dirty = false;

    std::mutex audio_m;
    std::deque<float> samples;  // interleaved stereo at 48 kHz
    u64 consumed = 0;           // stereo frames taken out of `samples` (played or dropped)
    std::chrono::steady_clock::time_point start;
};

constexpr int kMovieRate = MovieStream::kAudioRate;
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

// Frame k is shown at start + k / fps (the stream's r_frame_rate), as when the frames came from
// the ffmpeg program's constant-rate output.
void video_loop(Movie* m) {
    MovieFrame buf;
    std::string err;
    for (u64 k = 0; !m->stop; k++) {
        if (!m->video.next_video(buf, &err)) {
            if (!err.empty() && !m->stop) LOGE("movie", "video: %s", err.c_str());
            break;
        }
        auto due = m->start + std::chrono::microseconds((u64)(k * 1e6 / m->fps));
        while (!m->stop && std::chrono::steady_clock::now() < due) std::this_thread::sleep_for(std::chrono::milliseconds(2));
        std::lock_guard lk(m->frame_m);
        std::swap(m->frame, buf);
        m->frame_dirty = true;
    }
    m->video_done = true;
}

void audio_loop(Movie* m) {
    std::vector<float> buf;
    std::string err;
    while (!m->stop) {
        if (!m->audio.next_audio(buf, &err)) {
            if (!err.empty() && !m->stop) LOGE("movie", "audio: %s", err.c_str());
            break;
        }
        // Don't run far ahead of playback.
        for (;;) {
            {
                std::lock_guard lk(m->audio_m);
                drop_late_audio(m);
                if (m->samples.size() < kMovieRate * 2) {
                    m->samples.insert(m->samples.end(), buf.begin(), buf.end());
                    break;
                }
            }
            if (m->stop) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
    m->audio_done = true;
}

// Where an asset's bytes are: the APK's entry (stored: in place in the APK's mapping), or with
// --download the download tree's file (a folder's file, or the data zip's stored entry in place).
// A compressed entry is inflated into memory.
bool asset_source(const std::string& path, MovieSource& out) {
    AssetManager::Found f;
    AssetManager::Download dl;
    if (asset_manager().find_download(path, dl) && (asset_manager().download_prefer() || !asset_manager().find(path, f))) {
        const ZipArchive* zip = dl.tree->zip();
        if (!zip) {
            out = MovieSource::file(dl.loc.file);
            return true;
        }
        const ZipArchive::Entry* e = zip->find(dl.tree->prefix() + dl.rel);
        if (const uint8_t* p = e ? zip->stored_data(*e) : nullptr) {
            out = MovieSource::memory(p, e->size, dl.tree);  // the tree keeps the zip mapped
            return true;
        }
        std::vector<uint8_t> data;
        if (!dl.tree->read(dl.rel, data)) return false;
        out = MovieSource::owned(std::move(data));
        return true;
    }
    if (!asset_manager().find(path, f)) return false;
    if (const uint8_t* p = f.zip->stored_data(*f.entry)) {
        out = MovieSource::memory(p, f.entry->size);  // the asset manager's APKs stay open
        return true;
    }
    std::vector<uint8_t> data;
    if (!f.zip->extract(*f.entry, data)) return false;
    out = MovieSource::owned(std::move(data));
    return true;
}

// ---------------------------------------------------------------------------
// GL (render thread only): the planes go to three R8 textures; a shader converts them to RGBA
// (BT.601, limited range: what the ffmpeg program's swscale used for these movies, which don't
// tag their colour space) and turns the picture upright into g_tex, which is blitted to the window.

const char* kVs = R"(#version 300 es
void main() {  // one triangle over the whole viewport
    gl_Position = vec4(float((gl_VertexID & 1) << 2) - 1.0, float((gl_VertexID & 2) << 1) - 1.0, 0.0, 1.0);
}
)";
// Row 0 of g_tex is the picture's top (as the decoded rows; the blit flips). Rotated: output
// (x, y) is source (src_w - y, x), ffmpeg's transpose=2 (90 degrees counter-clockwise). Chroma is
// taken from the 2x2 block's sample (no interpolation), as swscale's unscaled yuv420p -> rgba.
const char* kFs = R"(#version 300 es
precision highp float;
precision highp int;
uniform highp sampler2D u_y, u_u, u_v;
uniform ivec2 u_src;
uniform int u_rotate;
out vec4 o;
void main() {
    ivec2 d = ivec2(gl_FragCoord.xy);
    ivec2 s = u_rotate != 0 ? ivec2(u_src.x - 1 - d.y, d.x) : d;
    float y = 1.1643836 * (texelFetch(u_y, s, 0).r - 0.0627451);
    float u = texelFetch(u_u, s / 2, 0).r - 0.5019608;
    float v = texelFetch(u_v, s / 2, 0).r - 0.5019608;
    o = vec4(clamp(vec3(y + 1.5960268 * v, y - 0.3917623 * u - 0.8129676 * v, y + 2.0172321 * u), 0.0, 1.0), 1.0);
}
)";

struct Gl {
    bool failed = false;
    GLuint prog = 0, vao = 0;
    GLint u_src = -1, u_rotate = -1;
    GLuint planes[3] = {};  // Y, U, V
    GLuint tex = 0, fbo = 0;
    int tex_w = 0, tex_h = 0, plane_w = 0, plane_h = 0;
};
Gl g_gl;

GLuint compile(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512] = {};
        glGetShaderInfoLog(s, sizeof log, nullptr, log);
        LOGE("movie", "shader: %s", log);
        glDeleteShader(s);
        return 0;
    }
    return s;
}

bool gl_setup(Gl& g) {
    if (g.prog || g.failed) return !g.failed;
    GLuint vs = compile(GL_VERTEX_SHADER, kVs), fs = compile(GL_FRAGMENT_SHADER, kFs);
    if (vs && fs) {
        g.prog = glCreateProgram();
        glAttachShader(g.prog, vs);
        glAttachShader(g.prog, fs);
        glLinkProgram(g.prog);
        GLint ok = 0;
        glGetProgramiv(g.prog, GL_LINK_STATUS, &ok);
        if (!ok) glDeleteProgram(g.prog), g.prog = 0;
    }
    if (vs) glDeleteShader(vs);
    if (fs) glDeleteShader(fs);
    if (!g.prog) {
        LOGE("movie", "the movie's GL program failed; movies show black");
        g.failed = true;
        return false;
    }
    g.u_src = glGetUniformLocation(g.prog, "u_src");
    g.u_rotate = glGetUniformLocation(g.prog, "u_rotate");
    GLint prev_prog;
    glGetIntegerv(GL_CURRENT_PROGRAM, &prev_prog);
    glUseProgram(g.prog);
    glUniform1i(glGetUniformLocation(g.prog, "u_y"), 0);
    glUniform1i(glGetUniformLocation(g.prog, "u_u"), 1);
    glUniform1i(glGetUniformLocation(g.prog, "u_v"), 2);
    glUseProgram(prev_prog);
    glGenVertexArrays(1, &g.vao);
    glGenTextures(3, g.planes);
    glGenTextures(1, &g.tex);
    glGenFramebuffers(1, &g.fbo);
    return true;
}

// Converts `f` into g.tex (m's shown size), saving and restoring the GL state it changes.
void gl_convert(Gl& g, const Movie* m, const MovieFrame& f) {
    GLint prog, vao, active, draw_fb, unpack_buf, ua, url, usr, usp, vp[4], tex[3], sampler[3];
    GLboolean mask[4];
    glGetIntegerv(GL_CURRENT_PROGRAM, &prog);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vao);
    glGetIntegerv(GL_ACTIVE_TEXTURE, &active);
    for (int i = 0; i < 3; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &tex[i]);
        glGetIntegerv(GL_SAMPLER_BINDING, &sampler[i]);
    }
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &draw_fb);
    glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &unpack_buf);
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &ua);
    glGetIntegerv(GL_UNPACK_ROW_LENGTH, &url);
    glGetIntegerv(GL_UNPACK_SKIP_ROWS, &usr);
    glGetIntegerv(GL_UNPACK_SKIP_PIXELS, &usp);
    glGetIntegerv(GL_VIEWPORT, vp);
    glGetBooleanv(GL_COLOR_WRITEMASK, mask);
    const GLenum caps[] = {GL_BLEND, GL_DEPTH_TEST, GL_STENCIL_TEST, GL_CULL_FACE, GL_SAMPLE_ALPHA_TO_COVERAGE, GL_SAMPLE_COVERAGE, GL_SCISSOR_TEST, GL_RASTERIZER_DISCARD};
    GLboolean was[std::size(caps)];
    for (size_t i = 0; i < std::size(caps); i++) was[i] = glIsEnabled(caps[i]);

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    bool resize = g.plane_w != f.w || g.plane_h != f.h;
    const uint8_t* p = f.planes.data();
    for (int i = 0; i < 3; i++) {
        int pw = i ? f.chroma_w() : f.w, ph = i ? f.chroma_h() : f.h;
        glActiveTexture(GL_TEXTURE0 + i);
        glBindSampler(i, 0);
        glBindTexture(GL_TEXTURE_2D, g.planes[i]);
        if (resize) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, pw, ph, 0, GL_RED, GL_UNSIGNED_BYTE, p);
        } else {
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, pw, ph, GL_RED, GL_UNSIGNED_BYTE, p);
        }
        p += (size_t)pw * ph;
    }
    g.plane_w = f.w, g.plane_h = f.h;
    // A picture of an unexpected size (none of the game's) is drawn into the top-left corner.
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g.fbo);
    glViewport(0, 0, std::min(g.tex_w, m->rotate ? f.h : f.w), std::min(g.tex_h, m->rotate ? f.w : f.h));
    for (GLenum c : caps) glDisable(c);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glUseProgram(g.prog);
    glUniform2i(g.u_src, f.w, f.h);
    glUniform1i(g.u_rotate, m->rotate ? 1 : 0);
    glBindVertexArray(g.vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(vao);
    glUseProgram(prog);
    for (size_t i = 0; i < std::size(caps); i++) (was[i] ? glEnable : glDisable)(caps[i]);
    glColorMask(mask[0], mask[1], mask[2], mask[3]);
    glViewport(vp[0], vp[1], vp[2], vp[3]);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_fb);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ua);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, url);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, usr);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, usp);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, unpack_buf);
    for (int i = 2; i >= 0; i--) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, tex[i]);
        glBindSampler(i, sampler[i]);
    }
    glActiveTexture(active);
}

}  // namespace

bool movie_start(const std::string& path, bool is_file, float volume) {
    movie_stop();
    auto m = std::make_unique<Movie>();
    m->volume = volume;
    if (is_file) {
        m->source = MovieSource::file(host_path(path.c_str()));
    } else if (!asset_source(path, m->source)) {
        LOGE("movie", "asset %s not found", path.c_str());
        return false;
    }
    Movie* raw = m.get();
    auto stopping = [raw] { return raw->stop.load(); };
    std::string err;
    if (!m->video.open(m->source, MovieStream::Kind::video, &err, stopping)) {
        LOGE("movie", "can't play %s: %s", path.c_str(), err.c_str());
        return false;
    }
    m->src_w = m->video.width(), m->src_h = m->video.height();
    if (m->src_w <= 0 || m->src_h <= 0) {
        LOGE("movie", "can't play %s: no picture size", path.c_str());
        return false;
    }
    m->fps = m->video.frame_rate();
    if (m->fps <= 1 || m->fps > 240) m->fps = 30;
    // The game's movies are stored portrait with the picture rotated; Android shows them in a
    // portrait-locked activity while the phone is held landscape. Rotate them upright.
    m->rotate = m->src_h > m->src_w;
    m->w = m->rotate ? m->src_h : m->src_w;
    m->h = m->rotate ? m->src_w : m->src_h;
    m->has_audio = m->audio.open(m->source, MovieStream::Kind::audio, &err, stopping);
    LOGI("movie", "playing %s (%dx%d @ %.2f fps%s)", path.c_str(), m->w, m->h, m->fps, m->has_audio ? "" : ", no audio");
    m->start = std::chrono::steady_clock::now();
    m->video_thread = std::thread(video_loop, raw);
    if (m->has_audio) m->audio_thread = std::thread(audio_loop, raw);
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
    if (m->video_thread.joinable()) m->video_thread.join();
    if (m->audio_thread.joinable()) m->audio_thread.join();
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
    Gl& g = g_gl;
    if (!gl_setup(g)) return;
    GLint prev_tex, prev_read, prev_active;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &prev_active);
    glActiveTexture(GL_TEXTURE0);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &prev_tex);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &prev_read);
    if (g.tex_w != m->w || g.tex_h != m->h) {
        glBindTexture(GL_TEXTURE_2D, g.tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m->w, m->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, prev_tex);
        g.tex_w = m->w, g.tex_h = m->h;
        // black until the first picture
        GLint prev_draw;
        glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &prev_draw);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g.fbo);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g.tex, 0);
        GLboolean scissor = glIsEnabled(GL_SCISSOR_TEST);
        glDisable(GL_SCISSOR_TEST);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        if (scissor) glEnable(GL_SCISSOR_TEST);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, prev_draw);
    }
    {
        std::lock_guard fl(m->frame_m);
        if (m->frame_dirty) {
            gl_convert(g, m, m->frame);
            m->frame_dirty = false;
        }
    }
    glBindFramebuffer(GL_READ_FRAMEBUFFER, g.fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target_fbo);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    double sa = (double)m->w / m->h, da = (double)ww / std::max(1, wh);
    int dw = ww, dh = wh;
    if (da > sa) dw = (int)(wh * sa + 0.5);
    else dh = (int)(ww / sa + 0.5);
    int dx = (ww - dw) / 2, dy = (wh - dh) / 2;
    // The picture's rows are top-down; flip while blitting.
    glBlitFramebuffer(0, 0, m->w, m->h, dx, dy + dh, dx + dw, dy, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, prev_read);
    glActiveTexture(prev_active);
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
