// common/win32/posix_compat.h's functions (Windows only).
#ifdef _WIN32
#include "../win32/posix_compat.h"

#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <string.h>
#include <pthread.h>
#include <windows.h>

#include <atomic>
#include <vector>

extern "C" char* soa_realpath(const char* path, char* resolved) {
    char full[PATH_MAX];
    if (!strcmp(path, "/proc/self/exe")) {  // Linux's link to the running executable
        DWORD n = GetModuleFileNameA(nullptr, full, sizeof full);
        if (n == 0 || n >= sizeof full) return nullptr;
    } else if (!_fullpath(full, path, sizeof full)) {
        return nullptr;
    }
    struct stat st;
    if (stat(full, &st) != 0) return nullptr;  // POSIX: the path must exist (errno from stat)
    for (char* p = full; *p; p++)
        if (*p == '\\') *p = '/';
    if (!resolved) return _strdup(full);
    memcpy(resolved, full, strlen(full) + 1);
    return resolved;
}

extern "C" int soa_rename(const char* from, const char* to) {
    if (MoveFileExA(from, to, MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED)) return 0;
    DWORD e = GetLastError();
    errno = e == ERROR_FILE_NOT_FOUND || e == ERROR_PATH_NOT_FOUND ? ENOENT : e == ERROR_ACCESS_DENIED ? EACCES : EIO;
    return -1;
}

extern "C" ssize_t soa_pread(int fd, void* buf, size_t n, long long offset) {
    HANDLE h = (HANDLE)_get_osfhandle(fd);
    if (h == INVALID_HANDLE_VALUE) return errno = EBADF, -1;
    OVERLAPPED ov{};
    ov.Offset = (DWORD)offset;
    ov.OffsetHigh = (DWORD)((unsigned long long)offset >> 32);
    DWORD got = 0;
    if (!ReadFile(h, buf, (DWORD)(n > 0x7fffffff ? 0x7fffffff : n), &got, &ov)) {
        if (GetLastError() == ERROR_HANDLE_EOF) return 0;
        return errno = EIO, -1;
    }
    return (ssize_t)got;
}

extern "C" char* soa_strptime(const char* s, const char* fmt, struct tm* tm) {
    auto num = [&](int maxd, int* out) {
        int v = 0, d = 0;
        while (d < maxd && *s >= '0' && *s <= '9') v = v * 10 + (*s++ - '0'), d++;
        if (!d) return false;
        *out = v;
        return true;
    };
    for (; *fmt; fmt++) {
        if (isspace((unsigned char)*fmt)) {
            while (isspace((unsigned char)*s)) s++;
            continue;
        }
        if (*fmt != '%') {
            if (*s++ != *fmt) return nullptr;
            continue;
        }
        int v;
        switch (*++fmt) {
        case 'Y': if (!num(4, &v)) return nullptr; tm->tm_year = v - 1900; break;
        case 'y': if (!num(2, &v)) return nullptr; tm->tm_year = v < 69 ? v + 100 : v; break;
        case 'm': if (!num(2, &v)) return nullptr; tm->tm_mon = v - 1; break;
        case 'd': case 'e': while (*s == ' ') s++; if (!num(2, &v)) return nullptr; tm->tm_mday = v; break;
        case 'H': if (!num(2, &v)) return nullptr; tm->tm_hour = v; break;
        case 'M': if (!num(2, &v)) return nullptr; tm->tm_min = v; break;
        case 'S': if (!num(2, &v)) return nullptr; tm->tm_sec = v; break;
        case 'j': if (!num(3, &v)) return nullptr; tm->tm_yday = v - 1; break;
        case '%': if (*s++ != '%') return nullptr; break;
        default: return nullptr;  // not needed by our code
        }
    }
    return (char*)s;
}

extern "C" int soa_gettid(void) { return (int)GetCurrentThreadId(); }

extern "C" int soa_setenv(const char* name, const char* value, int overwrite) {
    if (!name || !*name || strchr(name, '=')) return errno = EINVAL, -1;
    if (!overwrite && getenv(name)) return 0;
    return _putenv_s(name, value) == 0 ? 0 : -1;
}

extern "C" int soa_unsetenv(const char* name) { return _putenv_s(name, "") == 0 ? 0 : -1; }

extern "C" char* soa_mkdtemp(char* tmpl) {
    size_t n = tmpl ? strlen(tmpl) : 0;
    if (n < 6 || strcmp(tmpl + n - 6, "XXXXXX") != 0) return errno = EINVAL, nullptr;
    static const char kChars[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    static std::atomic<unsigned long long> counter{0};
    for (int attempt = 0; attempt < 1000; attempt++) {
        unsigned long long v = GetTickCount64() * 0x9e3779b97f4a7c15ull ^ ((unsigned long long)GetCurrentProcessId() << 32) ^
                               (counter++ * 0xbf58476d1ce4e5b9ull);
        for (size_t i = n - 6; i < n; i++, v /= 36) tmpl[i] = kChars[v % 36];
        if (_mkdir(tmpl) == 0) return tmpl;
        if (errno != EEXIST) return nullptr;
    }
    return errno = EEXIST, nullptr;
}

#if defined(__GNUC__) && !defined(__clang__)
// thread_local destructors for GCC on MinGW (its TLS is emulated, libgcc's emutls). libstdc++'s
// __cxa_thread_atexit runs them from a winpthreads key destructor whose key is created after
// emutls' own, and winpthreads runs key destructors in key order: emutls frees a thread's TLS
// blocks first, then the destructors run on freed memory (seen as soaruntime_tests crashing in
// ~ThreadState under Wine). This replacement (it takes the place of libstdc++'s: the linker finds
// it in soa_compat first) keeps each thread's destructors in a key created at start-up, before any
// emulated TLS is touched, so they run while the blocks are alive; the main thread's at exit().
// (clang, llvm-mingw, has native TLS: none of this.)
namespace {
struct ThreadDtor {
    void (*fn)(void*);
    void* obj;
};
using ThreadDtors = std::vector<ThreadDtor>;
pthread_key_t g_dtor_key;
bool g_dtor_key_ok = false;

void run_thread_dtors(void* p) {
    auto* v = (ThreadDtors*)p;
    while (!v->empty()) {  // in reverse order of construction; a destructor may register more
        ThreadDtor d = v->back();
        v->pop_back();
        d.fn(d.obj);
    }
    delete v;
}

__attribute__((constructor(101))) void init_thread_dtors() {
    g_dtor_key_ok = pthread_key_create(&g_dtor_key, run_thread_dtors) == 0;
    atexit([] {  // the main thread's (no key destructor runs for it)
        if (auto* v = (ThreadDtors*)pthread_getspecific(g_dtor_key)) {
            pthread_setspecific(g_dtor_key, nullptr);
            run_thread_dtors(v);
        }
    });
}
}  // namespace

extern "C" int __cxa_thread_atexit(void (*fn)(void*), void* obj, void* /*dso*/) {
    if (!g_dtor_key_ok) return -1;
    auto* v = (ThreadDtors*)pthread_getspecific(g_dtor_key);
    if (!v) {
        v = new ThreadDtors;
        pthread_setspecific(g_dtor_key, v);
    }
    v->push_back({fn, obj});
    return 0;
}
#endif
#endif
