// OpenGL ES: the guest's GL calls go to the host's GLES (Mesa), in the contexts the frontend creates
// for the guest's EGL (egl.cpp, gfx.h), with a few translations; plus the default-framebuffer
// emulation that renders the guest's EGL surfaces into framebuffer objects and presents the window's.
//
// The entry points come from libEGL's eglGetProcAddress at hle_init, before any window or context
// exists (SDL_GL_GetProcAddress isn't available then, and the runtime doesn't link SDL). They are
// libglvnd's dispatch stubs, which call into the vendor of the context current on the calling thread:
// the frontend's SDL contexts are EGL contexts from the same libEGL.so.1 (SDL loads it; app/host.cpp
// makes SDL's X11 backend use EGL rather than GLX, and its Wayland backend only has EGL), so the
// stubs reach the same Mesa driver SDL's context runs on. app/host.cpp checks this once at start-up
// (SDL_GL_GetProcAddress vs these pointers).
#include <soa/env.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl32.h>

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "soaruntime/android/ndk.h"
#include "soaruntime/core/hle.h"
#include "soaruntime/core/log.h"
#include "soaruntime/core/thread_record.h"
#include "hle/egl_state.h"
#include "hle/etc2.h"
#include "hle/gfx.h"
#include "soaruntime/hle/gl_host.h"

namespace soa {

// ===========================================================================
// GLES: every entry point goes through a function pointer from eglGetProcAddress.

#define GL_ENTRY(name) static decltype(&::name) s_##name = nullptr;
#include "soaruntime/hle/gl_functions.inc"
#undef GL_ENTRY

// Entry points for native code (hle/gl_host.h): the same functions the guest thunks call.
namespace glh {
#define GL_ENTRY(name) decltype(&::name) name = nullptr;
#include "soaruntime/hle/gl_functions.inc"
#undef GL_ENTRY
thread_local Recorder* t_rec = nullptr;
thread_local bool t_map_overwrites = false;
}  // namespace glh

void missing_slot_call(Cpu& c) {
    const char* n = thunk_name_at(c.pc() - 4);
    LOGE("gl", "call to unavailable GL function %s", n ? n : "?");
    c.set_x(0, 0);
}

namespace {

// Filtered extension string: hide extensions whose entry points we can't pass through.
const GLubyte* host_glGetString(GLenum name) {
    const GLubyte* s = s_glGetString(name);
    if (name == GL_EXTENSIONS && s) {
        struct ExtTag;
        std::string& ext = thread_object<std::string, ExtTag>();  // (core/thread_record.h)
        ext.clear();
        std::string all = (const char*)s;
        size_t p = 0;
        while (p < all.size()) {
            size_t e = all.find(' ', p);
            if (e == std::string::npos) e = all.size();
            std::string x = all.substr(p, e - p);
            p = e + 1;
            if (x.empty() || x == "GL_KHR_debug") continue;
            ext += x + " ";
        }
        return (const GLubyte*)ext.c_str();
    }
    return s;
}
void th_glGetString(Cpu& c) {
    GLenum n = (GLenum)c.x(0);
    const GLubyte* r = host_glGetString(n);
    static std::atomic<int> logged{0};
    if (logged.fetch_add(1) < 4 && r) {
        if (n == GL_EXTENSIONS) LOGD("gl", "GL_EXTENSIONS = %s", (const char*)r);
        else LOGI("gl", "glGetString(%#x) = %s", n, (const char*)r);
    }
    ret_ptr(c, r);
}

// sRGB ETC2 textures are decoded by the port (hle/etc2.h) and uploaded as GL_SRGB8_ALPHA8.
//
// The host driver (Mesa d3d12 on WSL) has no ETC2 and decodes on the CPU at upload; for the sRGB
// variants its decode is about 70x slower than for the linear ones (a 1024x1024
// GL_COMPRESSED_SRGB8_ETC2 upload takes ~650 ms, the RGB8 one ~9 ms). The game uploads ~550
// sRGB ETC2 levels per restore session, and they were 90% of all glCompressedTexImage2D time
// (~14 s of ~16 s in restore_session.sh; ~24% of busy samples). Decoding them here and
// uploading the RGBA8 result stores the same texels (checked texel for texel against the
// driver's own decode: selftest hle/etc2-vs-host) at ~10 ns per pixel plus a plain upload.
// Port enhancement, default on; SOA_GL_HOST_SRGB_ETC2=1 passes the compressed data to the host
// driver as before. glTexStorage2D and glCompressedTexSubImage2D with these formats follow, so
// such a texture is SRGB8_ALPHA8 in every path. (Not translated: the 3D/array variants, which the
// game doesn't use, and querying the texture's internal format back, which it doesn't do.)
bool host_srgb_etc2() {
    static const bool on = [] {
        return env::env_on("SOA_GL_HOST_SRGB_ETC2");
    }();
    return on;
}
bool srgb_etc2_format(GLenum fmt, etc2::Format* f) {
    switch (fmt) {
    case GL_COMPRESSED_SRGB8_ETC2: *f = etc2::Format::RGB8; return true;
    case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2: *f = etc2::Format::RGB8A1; return true;
    case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC: *f = etc2::Format::RGBA8; return true;
    default: return false;
    }
}
// Decodes an sRGB ETC2 upload to RGBA8 in a per-thread buffer, or returns null when the call
// must go to the driver unchanged: the translation is off, or the call is one the driver
// rejects or reads differently (bad size, border, a pixel unpack buffer bound: data is then
// an offset), so its error behaviour stays the driver's.
const u8* decode_srgb_etc2(GLenum fmt, GLsizei w, GLsizei h, GLint border, GLsizei size, const void* data) {
    etc2::Format f;
    if (!srgb_etc2_format(fmt, &f) || host_srgb_etc2()) return nullptr;
    if (w <= 0 || h <= 0 || border != 0 || !data || (size_t)size != etc2::image_bytes(f, w, h)) return nullptr;
    GLint pbo = 0;
    s_glGetIntegerv(GL_PIXEL_UNPACK_BUFFER_BINDING, &pbo);
    if (pbo) return nullptr;
    struct Etc2Tag;
    std::vector<u8>& buf = thread_object<std::vector<u8>, Etc2Tag>();  // (core/thread_record.h)
    buf.resize((size_t)w * h * 4);
    etc2::decode(f, (const u8*)data, w, h, buf.data());
    return buf.data();
}
// Uploads tightly packed RGBA8 rows whatever the guest's unpack state (which compressed
// uploads ignore): the row-layout parameters are set to their defaults around the call.
template <typename F>
void with_default_unpack(F&& upload) {
    static constexpr GLenum kParams[] = {GL_UNPACK_ALIGNMENT, GL_UNPACK_ROW_LENGTH, GL_UNPACK_SKIP_ROWS, GL_UNPACK_SKIP_PIXELS};
    static constexpr GLint kDefault[] = {4, 0, 0, 0};
    GLint saved[4];
    for (int i = 0; i < 4; i++) {
        s_glGetIntegerv(kParams[i], &saved[i]);
        if (saved[i] != kDefault[i]) s_glPixelStorei(kParams[i], kDefault[i]);
    }
    upload();
    for (int i = 0; i < 4; i++)
        if (saved[i] != kDefault[i]) s_glPixelStorei(kParams[i], saved[i]);
}

// ETC1 isn't exposed on GLES3 contexts by every driver, but ETC1 data is valid ETC2 RGB8.
void host_glCompressedTexImage2D(GLenum target, GLint level, GLenum fmt, GLsizei w, GLsizei h, GLint border, GLsizei size, const void* data) {
    if (fmt == GL_ETC1_RGB8_OES) fmt = GL_COMPRESSED_RGB8_ETC2;
    if (const u8* rgba = decode_srgb_etc2(fmt, w, h, border, size, data)) {
        with_default_unpack([&] { s_glTexImage2D(target, level, GL_SRGB8_ALPHA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba); });
        return;
    }
    s_glCompressedTexImage2D(target, level, fmt, w, h, border, size, data);
}
void host_glCompressedTexSubImage2D(GLenum target, GLint level, GLint x, GLint y, GLsizei w, GLsizei h, GLenum fmt, GLsizei size, const void* data) {
    if (const u8* rgba = decode_srgb_etc2(fmt, w, h, 0, size, data)) {
        with_default_unpack([&] { s_glTexSubImage2D(target, level, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, rgba); });
        return;
    }
    s_glCompressedTexSubImage2D(target, level, x, y, w, h, fmt, size, data);
}
// A write-only map whose caller overwrites the whole range (glh::t_map_overwrites, gl_host.h)
// may discard the range's old contents: GL_MAP_INVALIDATE_RANGE_BIT changes nothing the caller
// can observe, and spares the driver keeping them. Without it, Mesa d3d12 waits for the GPU to
// finish with the buffer (it was just filled by glBufferData and drawn from): ~1.6 ms per map, 3%
// of busy samples in restore_session.sh, for the engine's vertex/index buffer updates.
// Port enhancement, default on; SOA_GL_MAP_INVALIDATE=0 maps with the caller's flags only.
bool map_invalidate_on() {
    static const bool on = [] {
        return env::env_bool("SOA_GL_MAP_INVALIDATE", true);
    }();
    return on;
}
// SOA_GL_BUFFER_DUMP=<dir> (diagnostic): the bytes of every buffer upload, to compare with a decoder
// (tools/asf2gltf --check-gl-dump: a model's vertex and index blocks against what the game uploads).
// Each distinct content goes once to <dir>/<fnv1a64>.bin; <dir>/index.tsv gets one line per upload:
// sequence, call (data = glBufferData, sub = glBufferSubData, map = a write map at its glUnmapBuffer),
// target, buffer name, offset, size, hash. Off (no cost but one test) when unset.
struct BufferDump {
    std::mutex mu;
    FILE* index = nullptr;
    std::string dir;
    std::set<uint64_t> seen;
    uint64_t seq = 0;
    struct Map { GLenum target; GLintptr off; GLsizeiptr len; void* ptr; };
    std::unordered_map<GLuint, Map> maps;  // by buffer name: the open write maps
};
BufferDump* buffer_dump() {
    static BufferDump* d = [] () -> BufferDump* {
        const char* dir = env::env_str("SOA_GL_BUFFER_DUMP");
        if (!dir || !*dir) return nullptr;
        auto* b = new BufferDump;
        b->dir = dir;
        b->index = fopen((b->dir + "/index.tsv").c_str(), "w");
        if (!b->index) { LOGW("gl", "SOA_GL_BUFFER_DUMP: cannot create %s/index.tsv", dir); delete b; return nullptr; }
        return b;
    }();
    return d;
}
GLuint bound_buffer(GLenum target) {
    GLenum q = 0;
    switch (target) {
    case GL_ARRAY_BUFFER: q = GL_ARRAY_BUFFER_BINDING; break;
    case GL_ELEMENT_ARRAY_BUFFER: q = GL_ELEMENT_ARRAY_BUFFER_BINDING; break;
    case GL_UNIFORM_BUFFER: q = GL_UNIFORM_BUFFER_BINDING; break;
    case GL_COPY_WRITE_BUFFER: q = GL_COPY_WRITE_BUFFER_BINDING; break;
    case GL_PIXEL_UNPACK_BUFFER: q = GL_PIXEL_UNPACK_BUFFER_BINDING; break;
    default: return 0;
    }
    GLint b = 0;
    s_glGetIntegerv(q, &b);
    return (GLuint)b;
}
void dump_buffer(const char* call, GLenum target, GLuint buf, GLintptr off, GLsizeiptr len, const void* data) {
    BufferDump* d = buffer_dump();
    if (!d || !data || len <= 0) return;
    uint64_t h = 0xcbf29ce484222325ull;
    for (GLsizeiptr i = 0; i < len; i++) h = (h ^ ((const uint8_t*)data)[i]) * 0x100000001b3ull;
    std::lock_guard lk(d->mu);
    if (d->seen.insert(h).second) {
        char name[32];
        snprintf(name, sizeof name, "/%016llx.bin", (unsigned long long)h);
        if (FILE* f = fopen((d->dir + name).c_str(), "wb")) {
            fwrite(data, 1, (size_t)len, f);
            fclose(f);
        }
    }
    fprintf(d->index, "%llu\t%s\t0x%x\t%u\t%lld\t%lld\t%016llx\n", (unsigned long long)d->seq++, call, target, buf,
            (long long)off, (long long)len, (unsigned long long)h);
    fflush(d->index);
}
void host_glBufferData(GLenum target, GLsizeiptr len, const void* data, GLenum usage) {
    if (buffer_dump()) dump_buffer("data", target, bound_buffer(target), 0, len, data);
    s_glBufferData(target, len, data, usage);
}
void host_glBufferSubData(GLenum target, GLintptr off, GLsizeiptr len, const void* data) {
    if (buffer_dump()) dump_buffer("sub", target, bound_buffer(target), off, len, data);
    s_glBufferSubData(target, off, len, data);
}
GLboolean host_glUnmapBuffer(GLenum target) {
    if (BufferDump* d = buffer_dump()) {
        GLuint buf = bound_buffer(target);
        BufferDump::Map m{};
        bool have = false;
        {
            std::lock_guard lk(d->mu);
            auto it = d->maps.find(buf);
            if (it != d->maps.end()) { m = it->second; have = true; d->maps.erase(it); }
        }
        if (have) dump_buffer("map", m.target, buf, m.off, m.len, m.ptr);
    }
    return s_glUnmapBuffer(target);
}
void* host_glMapBufferRange(GLenum target, GLintptr off, GLsizeiptr len, GLbitfield acc) {
    if (glh::t_map_overwrites && acc == GL_MAP_WRITE_BIT && map_invalidate_on()) acc |= GL_MAP_INVALIDATE_RANGE_BIT;
    void* p = s_glMapBufferRange(target, off, len, acc);
    if (BufferDump* d = buffer_dump(); d && p && (acc & GL_MAP_WRITE_BIT)) {
        GLuint buf = bound_buffer(target);
        std::lock_guard lk(d->mu);
        d->maps[buf] = {target, off, len, p};
    }
    return p;
}
void host_glTexStorage2D(GLenum target, GLsizei levels, GLenum fmt, GLsizei w, GLsizei h) {
    etc2::Format f;
    if (srgb_etc2_format(fmt, &f) && !host_srgb_etc2()) fmt = GL_SRGB8_ALPHA8;
    s_glTexStorage2D(target, levels, fmt, w, h);
}

// ===========================================================================
// Default-framebuffer emulation (ANativeWindow_setBuffersGeometry, and the surfaces of the emulated
// EGL: egl.cpp).
//
// Android scales the window's buffers to the screen; here each context renders into an FBO of the
// requested size whenever the game binds framebuffer 0 on the window surface, and eglSwapBuffers
// blits it (letterboxed) to the real window. A context bound to a pbuffer (the frontend binds it
// on a hidden surface of its own) gets an FBO of the pbuffer's size as its framebuffer 0 the same way, so
// framebuffer 0 is always complete, as on a real pbuffer. Each context has one stand-in per surface
// kind: the game binds its main context to the 1x1 pbuffer at times (RenderDeviceGL::
// SetCurrentContext), which must not discard the window's.

struct StandIn {
    GLuint fbo = 0, color = 0, depth = 0;
    int w = 0, h = 0;
};
struct CtxFbos {
    StandIn surface[2];  // by egl_emu::Surface::Kind
    StandIn present;     // the window's own framebuffer when presenting offscreen (GfxHooks::offscreen_present)
};
std::mutex g_fbo_mutex;
std::unordered_map<void*, CtxFbos> g_fbos;

bool scaling_active() {
    auto& w = native_window();
    return w.buffer_width > 0 && w.buffer_height > 0;
}
// Size of the emulated default framebuffer: the buffer geometry if set, else the Android window size.
int fb_width() { return scaling_active() ? native_window().buffer_width : native_window().width; }
int fb_height() { return scaling_active() ? native_window().buffer_height : native_window().height; }

// (Re)allocates f at w x h: RGBA8 colour, and D24S8 depth/stencil if `depth`; cleared to opaque black.
// Keeps the caller's framebuffer and renderbuffer bindings.
void alloc_stand_in(StandIn& f, int w, int h, bool depth, const char* what) {
    GLint prev_rb = 0;
    s_glGetIntegerv(GL_RENDERBUFFER_BINDING, &prev_rb);
    if (!f.fbo) {
        s_glGenFramebuffers(1, &f.fbo);
        s_glGenRenderbuffers(1, &f.color);
        if (depth) s_glGenRenderbuffers(1, &f.depth);
    }
    f.w = w;
    f.h = h;
    s_glBindRenderbuffer(GL_RENDERBUFFER, f.color);
    s_glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, f.w, f.h);
    if (depth) {
        s_glBindRenderbuffer(GL_RENDERBUFFER, f.depth);
        s_glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, f.w, f.h);
    }
    s_glBindRenderbuffer(GL_RENDERBUFFER, prev_rb);
    GLint prev_fb = 0;
    s_glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prev_fb);
    s_glBindFramebuffer(GL_FRAMEBUFFER, f.fbo);
    s_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, f.color);
    if (depth) {
        s_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, f.depth);
        s_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, f.depth);
    }
    GLenum st = s_glCheckFramebufferStatus(GL_FRAMEBUFFER);
    s_glClearColor(0, 0, 0, 1);
    s_glClear(GL_COLOR_BUFFER_BIT | (depth ? GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT : 0));
    s_glBindFramebuffer(GL_FRAMEBUFFER, prev_fb);
    LOGI("gl", "%s emulated at %dx%d (fbo %u, status %#x)", what, f.w, f.h, f.fbo, st);
}

// FBO standing in for framebuffer 0 on this thread's current context and draw surface, or 0.
GLuint default_fbo() {
    egl_emu::Surface* s = egl_emu::current_draw();
    if (!s) return 0;
    bool window = s->kind == egl_emu::Surface::Window;
    int w = window ? fb_width() : s->width, h = window ? fb_height() : s->height;
    std::lock_guard lk(g_fbo_mutex);
    StandIn& f = g_fbos[egl_emu::current_context()].surface[s->kind];
    if (f.fbo && f.w == w && f.h == h) return f.fbo;
    alloc_stand_in(f, w, h, true, window ? "default framebuffer" : "pbuffer");
    return f.fbo;
}
// Debug (SOA_TRACE_RT=1): log distinct render-target allocations and viewports.
bool trace_rt() {
    static bool on = env::env_on("SOA_TRACE_RT");
    return on;
}
void host_glRenderbufferStorage(GLenum target, GLenum fmt, GLsizei w, GLsizei h) {
    if (trace_rt()) LOGI("rt", "glRenderbufferStorage(fmt %#x, %dx%d)", (unsigned)fmt, (int)w, (int)h);
    s_glRenderbufferStorage(target, fmt, w, h);
}
void host_glViewport(GLint x, GLint y, GLsizei w, GLsizei h) {
    if (trace_rt()) {
        static std::mutex m;
        static std::set<std::pair<int, int>> seen;
        std::lock_guard lk(m);
        if (seen.insert({(int)w, (int)h}).second) LOGI("rt", "glViewport(%d,%d,%d,%d)", (int)x, (int)y, (int)w, (int)h);
    }
    s_glViewport(x, y, w, h);
}
void host_glFramebufferTexture2D(GLenum target, GLenum att, GLenum textarget, GLuint tex, GLint level) {
    if (trace_rt()) {
        GLint w = 0, h = 0, prev = 0;
        s_glGetIntegerv(GL_TEXTURE_BINDING_2D, &prev);
        s_glBindTexture(GL_TEXTURE_2D, tex);
        s_glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
        s_glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
        s_glBindTexture(GL_TEXTURE_2D, prev);
        LOGI("rt", "glFramebufferTexture2D(att %#x, tex %u: %dx%d)", (unsigned)att, (unsigned)tex, w, h);
    }
    s_glFramebufferTexture2D(target, att, textarget, tex, level);
}

void host_glBindFramebuffer(GLenum target, GLuint fb) {
    if (fb == 0) fb = default_fbo();
    s_glBindFramebuffer(target, fb);
}

void host_glGetIntegerv(GLenum pname, GLint* out) {
    s_glGetIntegerv(pname, out);
    if ((pname == GL_FRAMEBUFFER_BINDING || pname == GL_READ_FRAMEBUFFER_BINDING) && *out != 0 && (GLuint)*out == default_fbo()) *out = 0;
}

// Attachment names for the default framebuffer (GL_COLOR/GL_DEPTH/GL_STENCIL) aren't valid on an FBO.
std::vector<GLenum> fix_attachments(GLenum target, GLsizei n, const GLenum* att) {
    std::vector<GLenum> v(att, att + n);
    GLint bound = 0;
    s_glGetIntegerv(target == GL_READ_FRAMEBUFFER ? GL_READ_FRAMEBUFFER_BINDING : GL_FRAMEBUFFER_BINDING, &bound);
    if (bound != 0 && (GLuint)bound == default_fbo()) {
        for (auto& a : v) {
            if (a == GL_COLOR) a = GL_COLOR_ATTACHMENT0;
            else if (a == GL_DEPTH) a = GL_DEPTH_ATTACHMENT;
            else if (a == GL_STENCIL) a = GL_STENCIL_ATTACHMENT;
        }
    }
    return v;
}
void host_glInvalidateFramebuffer(GLenum target, GLsizei n, const GLenum* att) {
    auto v = fix_attachments(target, n, att);
    s_glInvalidateFramebuffer(target, (GLsizei)v.size(), v.data());
}
void host_glDiscardFramebufferEXT(GLenum target, GLsizei n, const GLenum* att) {
    auto v = fix_attachments(target, n, att);
    if (s_glDiscardFramebufferEXT) s_glDiscardFramebufferEXT(target, (GLsizei)v.size(), v.data());
    else s_glInvalidateFramebuffer(target, (GLsizei)v.size(), v.data());
}

// GL thunk for guest code: runs Impl, or records the call when a glh::Recorder is installed
// on this thread (see hle/gl_host.h).
template <auto* Slot, HostFn Impl = &wrapped_slot<Slot>>
void gl_thunk(Cpu& c) {
    if (glh::t_rec) [[unlikely]] {
        using Tr = FnTraits<std::remove_pointer_t<decltype(Slot)>>;
        ArgReader rd(c);
        auto args = std::apply([&](auto... d) { return std::tuple<decltype(d)...>{rd.next<decltype(d)>()...}; }, typename Tr::Args{});
        const char* n = thunk_name_at(c.pc() - 4);
        glh::t_rec->calls.push_back(glh::format_call(n ? n : "?", args));
        glh::zero_outs(args, glh::t_rec->result);
        using R = typename Tr::Ret;
        if constexpr (std::is_integral_v<R>) set_result(c, (R)glh::t_rec->result);
        else c.set_x(0, 0);
        return;
    }
    Impl(c);
}

// glReleaseShaderCompiler is only a hint (GLES 3.0 section 7.1: "resources allocated by the
// shader compiler may be released", with no effect on any GL state or later compile results).
// The guest calls it after EVERY successful glCompileShader (RenderDeviceData::CreateShader). On
// a phone driver that is cheap; on Mesa it drops the GLSL built-in function library, which is
// rebuilt by the next compile and link: about 10x slower compiles and links, ~9 s of render-thread
// time per boot for the ~440 programs the shader-program cache links (13.6% of profiled busy
// time). Port enhancement, default on: the hint is dropped. SOA_GL_RELEASE_SHADER_COMPILER=1
// passes it through to the host like the guest does.
bool release_shader_compiler_passthrough() {
    static const bool on = [] {
        return env::env_on("SOA_GL_RELEASE_SHADER_COMPILER");
    }();
    return on;
}
void host_glReleaseShaderCompiler() {
    if (release_shader_compiler_passthrough()) s_glReleaseShaderCompiler();
}

// The framebuffer that stands for the window while presenting: 0, or with offscreen presentation
// (headless) an FBO of the window's size on the current context.
GLuint present_target(int ww, int wh) {
    if (!egl_emu::hooks()->offscreen_present()) return 0;
    std::lock_guard lk(g_fbo_mutex);
    StandIn& f = g_fbos[egl_emu::current_context()].present;
    if (!f.fbo || f.w != ww || f.h != wh) alloc_stand_in(f, ww, wh, false, "offscreen window");
    return f.fbo;
}

// Blits the emulated default framebuffer to the window, preserving aspect ratio.
void present_scaled() {
    GLuint fbo = default_fbo();
    if (!fbo) return;
    GfxHooks* hooks = egl_emu::hooks();
    int ww = 0, wh = 0;
    hooks->drawable_size(&ww, &wh);
    GLint draw_fb, read_fb, scissor, rasterizer_discard;
    GLboolean mask[4];
    GLfloat clear[4];
    s_glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &draw_fb);
    s_glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &read_fb);
    scissor = s_glIsEnabled(GL_SCISSOR_TEST);
    rasterizer_discard = s_glIsEnabled(GL_RASTERIZER_DISCARD);
    s_glGetBooleanv(GL_COLOR_WRITEMASK, mask);
    s_glGetFloatv(GL_COLOR_CLEAR_VALUE, clear);
    s_glDisable(GL_SCISSOR_TEST);
    s_glDisable(GL_RASTERIZER_DISCARD);
    s_glColorMask(1, 1, 1, 1);
    GLuint target = present_target(ww, wh);
    s_glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target);
    s_glClearColor(0, 0, 0, 1);
    s_glClear(GL_COLOR_BUFFER_BIT);
    // letterbox
    double sa = (double)fb_width() / fb_height(), da = (double)ww / std::max(1, wh);
    int dw = ww, dh = wh;
    if (da > sa) dw = (int)(wh * sa + 0.5);
    else dh = (int)(ww / sa + 0.5);
    int dx = (ww - dw) / 2, dy = (wh - dh) / 2;
    hooks->set_viewport_rect(dx, dy, dw, dh);
    s_glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    s_glBlitFramebuffer(0, 0, fb_width(), fb_height(), dx, dy, dx + dw, dy + dh, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    hooks->draw_overlay(ww, wh, target);
    // restore
    s_glBindFramebuffer(GL_DRAW_FRAMEBUFFER, draw_fb);
    s_glBindFramebuffer(GL_READ_FRAMEBUFFER, read_fb);
    if (scissor) s_glEnable(GL_SCISSOR_TEST);
    if (rasterizer_discard) s_glEnable(GL_RASTERIZER_DISCARD);
    s_glColorMask(mask[0], mask[1], mask[2], mask[3]);
    s_glClearColor(clear[0], clear[1], clear[2], clear[3]);
}

}  // namespace

namespace gles {

void on_make_current() {
    void* ctx = egl_emu::current_context();
    if (!ctx) return;
    GLuint fb = default_fbo();
    // Framebuffer 0 means the current draw surface's: a binding of 0 or of another surface's
    // stand-in on this context moves to the new surface's stand-in (0 without one).
    GLuint others[2];
    {
        std::lock_guard lk(g_fbo_mutex);
        auto it = g_fbos.find(ctx);
        others[0] = it == g_fbos.end() ? 0 : it->second.surface[0].fbo;
        others[1] = it == g_fbos.end() ? 0 : it->second.surface[1].fbo;
    }
    auto is_default = [&](GLint b) { return b == 0 || (others[0] && (GLuint)b == others[0]) || (others[1] && (GLuint)b == others[1]); };
    GLint draw = 0, read = 0;
    s_glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &draw);
    s_glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &read);
    if (is_default(draw) && (GLuint)draw != fb) s_glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fb);
    if (is_default(read) && (GLuint)read != fb) s_glBindFramebuffer(GL_READ_FRAMEBUFFER, fb);
}

bool present_and_swap() {
    GfxHooks* hooks = egl_emu::hooks();
    hooks->before_swap();
    present_scaled();
    bool ok = hooks->swap_window();
    hooks->after_swap();
    if (GLuint fb = default_fbo()) {
        GLint cur = 0;
        s_glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &cur);
        if (cur == 0) s_glBindFramebuffer(GL_FRAMEBUFFER, fb);
    }
    return ok;
}

void forget_context(void* ctx) {
    std::lock_guard lk(g_fbo_mutex);
    g_fbos.erase(ctx);
}

}  // namespace gles

void register_gles(Hle& h) {
#define GL_ENTRY(name)                                                  \
    s_##name = (decltype(s_##name))eglGetProcAddress(#name);           \
    glh::name = s_##name;                                              \
    h.fn(#name, &gl_thunk<&s_##name>);
#include "soaruntime/hle/gl_functions.inc"
#undef GL_ENTRY
    // Translated entry points: the guest thunk and glh:: (native code) share the host_ function.
#define GL_TRANSLATED(name, thunk)          \
    glh::name = &host_##name;               \
    h.fn(#name, &gl_thunk<&s_##name, thunk>);
    GL_TRANSLATED(glGetString, th_glGetString)
    GL_TRANSLATED(glCompressedTexImage2D, wrap<&host_glCompressedTexImage2D>())
    GL_TRANSLATED(glCompressedTexSubImage2D, wrap<&host_glCompressedTexSubImage2D>())
    GL_TRANSLATED(glTexStorage2D, wrap<&host_glTexStorage2D>())
    GL_TRANSLATED(glMapBufferRange, wrap<&host_glMapBufferRange>())
    GL_TRANSLATED(glBufferData, wrap<&host_glBufferData>())
    GL_TRANSLATED(glBufferSubData, wrap<&host_glBufferSubData>())
    GL_TRANSLATED(glUnmapBuffer, wrap<&host_glUnmapBuffer>())
    GL_TRANSLATED(glBindFramebuffer, wrap<&host_glBindFramebuffer>())
    GL_TRANSLATED(glRenderbufferStorage, wrap<&host_glRenderbufferStorage>())
    GL_TRANSLATED(glViewport, wrap<&host_glViewport>())
    GL_TRANSLATED(glFramebufferTexture2D, wrap<&host_glFramebufferTexture2D>())
    GL_TRANSLATED(glGetIntegerv, wrap<&host_glGetIntegerv>())
    GL_TRANSLATED(glInvalidateFramebuffer, wrap<&host_glInvalidateFramebuffer>())
    GL_TRANSLATED(glDiscardFramebufferEXT, wrap<&host_glDiscardFramebufferEXT>())
    GL_TRANSLATED(glReleaseShaderCompiler, wrap<&host_glReleaseShaderCompiler>())
#undef GL_TRANSLATED
}

}  // namespace soa
