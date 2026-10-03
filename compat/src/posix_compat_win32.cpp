// compat/win32/posix_compat.h's functions (Windows only).
#ifdef _WIN32
#include "../win32/posix_compat.h"

#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <string.h>
#include <windows.h>

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
#endif
