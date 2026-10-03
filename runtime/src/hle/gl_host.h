#pragma once
// Host GLES entry points for native code (src/native), plus a GL call recorder for tests.
//
// Native replacements of guest render code must reach GL the same way the guest does through
// the HLE thunks, including the port's translations (e.g. binding framebuffer 0 binds the FBO
// that emulates Android's scaled window buffer; ETC1 uploads become ETC2). glh::<name> holds
// exactly that function: the raw host entry point, or the translating wrapper the guest thunk
// uses. They are filled in by register_gles() (gles.cpp).
//
// Call them through GLH(name, args...), which also honours the recorder: while a
// glh::Recorder is installed on a thread (glh::t_rec), GL calls on that thread, from guest code
// (HLE thunks) and native code (GLH) alike, are appended to it as text and NOT executed. Results
// are Recorder::result (0 by default), which is also stored in the first element of scalar
// out-parameters. Differential tests use this to compare the GL
// call streams of a guest function and its native replacement. It is off (nullptr) by default.
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl32.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

namespace soa::glh {

#define GL_ENTRY(name) extern decltype(&::name) name;
#include "hle/gl_functions.inc"
#undef GL_ENTRY

struct Recorder {
    std::vector<std::string> calls;
    int result = 0;  // what recorded calls return (integer results and scalar out-parameters)
};
extern thread_local Recorder* t_rec;

// Set by native code around calls that map buffers with glMapBufferRange(GL_MAP_WRITE_BIT) and
// then overwrite every byte of the mapped range before unmapping (the engine's
// BufferHandlerGL<>::Update, render_rd.cpp). The port's glMapBufferRange then adds
// GL_MAP_INVALIDATE_RANGE_BIT, which such a caller can't tell apart and which saves the host
// driver a GPU wait (gles.cpp). Recorded calls (Recorder) keep the caller's flags.
extern thread_local bool t_map_overwrites;

template <typename T>
inline void format_arg(std::string& s, T v) {
    char buf[48];
    if constexpr (std::is_same_v<T, float>) {
        uint32_t b;
        std::memcpy(&b, &v, 4);
        snprintf(buf, sizeof buf, "%gf/%08x", v, b);
    } else if constexpr (std::is_same_v<T, double>) {
        snprintf(buf, sizeof buf, "%g", v);
    } else if constexpr (std::is_same_v<T, const char*>) {
        // Strings (glGetUniformLocation names, ...) by content: callers' buffers differ.
        s += v ? "\"" + std::string(v) + "\"" : std::string("NULL");
        return;
    } else if constexpr (std::is_same_v<T, const char* const*>) {
        // glShaderSource: the (first) source string, not the caller's array.
        s += v && *v ? "[\"" + std::string(*v) + "\"...]" : std::string("NULL");
        return;
    } else if constexpr (std::is_pointer_v<T> && !std::is_const_v<std::remove_pointer_t<T>>) {
        s += "<out>";  // out-parameters: the callers' (stack) buffers differ
        return;
    } else if constexpr (std::is_pointer_v<T>) {
        snprintf(buf, sizeof buf, "%p", (const void*)v);
    } else if constexpr (std::is_signed_v<T>) {
        snprintf(buf, sizeof buf, "%lld", (long long)v);
    } else {
        snprintf(buf, sizeof buf, "%#llx", (unsigned long long)v);
    }
    s += buf;
}

// "glName(arg, arg, ...)" with each argument converted to the parameter type first.
template <typename... P>
std::string format_call(const char* name, const std::tuple<P...>& args) {
    std::string s = name;
    s += '(';
    std::apply([&](auto... a) {
        bool first = true;
        ((s += first ? "" : ", ", first = false, format_arg(s, a)), ...);
    }, args);
    s += ')';
    return s;
}

// While recording, calls aren't executed; scalar out-parameters read back as 0 (first element),
// so code that inspects results (compile status, bindings) behaves the same on both sides.
template <typename... P>
void zero_outs(const std::tuple<P...>& args, int value) {
    std::apply([value](auto... a) {
        auto one = [value](auto v) {
            using T = decltype(v);
            if constexpr (std::is_pointer_v<T>) {
                using E = std::remove_pointer_t<T>;
                if constexpr (!std::is_const_v<E> && std::is_arithmetic_v<E>)
                    if (v) *v = (E)value;
            }
        };
        (one(a), ...);
    }, args);
}

template <typename P, typename A>
inline P conv(A a) {
    if constexpr (std::is_pointer_v<P> && std::is_integral_v<A>) return reinterpret_cast<P>(static_cast<uintptr_t>(a));
    else return static_cast<P>(a);
}

template <typename R, typename... P, typename... A>
inline R call(R (*fn)(P...), const char* name, A... a) {
    if (t_rec) [[unlikely]] {
        std::tuple<P...> args{conv<P>(a)...};
        t_rec->calls.push_back(format_call(name, args));
        zero_outs(args, t_rec->result);
        if constexpr (std::is_integral_v<R>) return (R)t_rec->result;
        else if constexpr (!std::is_void_v<R>) return R{};
        else return;
    }
    return fn(conv<P>(a)...);
}

}  // namespace soa::glh

#define GLH(name, ...) ::soa::glh::call(::soa::glh::name, #name __VA_OPT__(, ) __VA_ARGS__)
