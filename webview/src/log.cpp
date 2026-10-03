// libsoawebview's log lines (soawebview/page.h set_log).
#include <cstdarg>
#include <cstdio>
#include <functional>
#include <mutex>
#include <string>

#include "internal.h"

namespace soa::webview {
namespace {
std::mutex g_m;
std::function<void(int, const std::string&)> g_log;
}  // namespace

void set_log(std::function<void(int level, const std::string& msg)> fn) {
    std::lock_guard lk(g_m);
    g_log = std::move(fn);
}

void log(int level, const char* fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    std::lock_guard lk(g_m);
    if (g_log) g_log(level, buf);
    else if (level >= 2) fprintf(stderr, "[webview] %s\n", buf);
}

}  // namespace soa::webview
