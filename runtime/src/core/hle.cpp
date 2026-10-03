#include "core/hle.h"

#include <cstdarg>
#include <cstring>
#include <mutex>
#include <vector>

#include "core/log.h"

namespace soa {

LogLevel g_log_level = LogLevel::Info;

static std::mutex g_log_mutex;

void log_write(LogLevel lvl, const char* tag, const char* fmt, ...) {
    static const char* names[] = {"T", "D", "I", "W", "E"};
    char buf[4096];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    std::lock_guard lk(g_log_mutex);
    fprintf(stderr, "%s/%s: %s\n", names[(int)lvl], tag, buf);
}

void fatal(const char* fmt, ...) {
    char buf[4096];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    fprintf(stderr, "FATAL: %s\n", buf);
    fflush(stderr);
    abort();
}

Hle& Hle::get() {
    static Hle h;
    return h;
}

namespace {
// Each missing import gets its own thunk; the thunk looks up its name from the PC-derived index.
void missing_thunk(Cpu& c) {
    const char* n = thunk_name_at(c.pc() - 4);
    LOGE("hle", "called unimplemented import '%s'", n ? n : "?");
    dump_guest_state(c);
    fatal("unimplemented import %s", n ? n : "?");
}
}  // namespace

u64 Hle::missing(const std::string& name) {
    auto it = syms_.find(name);
    if (it != syms_.end()) return it->second;
    const char* n = strdup(name.c_str());
    u64 a = make_thunk(n, missing_thunk);
    syms_[name] = a;
    return a;
}

HostFn Hle::override_fn(const std::string& name, HostFn f) {
    HostFn prev = host_fn(name);
    const char* n = strdup(name.c_str());  // the thunk keeps its name
    syms_[name] = make_thunk(n, f);
    fns_[name] = f;
    return prev;
}

static std::vector<std::function<void(Hle&)>>& registrars() {
    static std::vector<std::function<void(Hle&)>> v;
    return v;
}

bool hle_add_registrar(std::function<void(Hle&)> fn) {
    registrars().push_back(std::move(fn));
    return true;
}

void hle_init() {
    auto& h = Hle::get();
    register_libc(h);
    register_libc_stdio(h);
    register_libc_thread(h);
    register_libc_misc(h);
    register_libm(h);
    register_gles(h);
    register_egl(h);
    register_android(h);
    register_opensles(h);
#ifdef _WIN32
    register_libc_win32(h);
#endif
    for (auto& fn : registrars()) fn(h);  // the host's (hle_add_registrar)
}

}  // namespace soa
