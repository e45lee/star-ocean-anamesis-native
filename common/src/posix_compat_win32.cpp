// common/win32/posix_compat.h's functions, and soa/install.h's exe_path_win32 (Windows only).
#ifdef _WIN32
#include "../win32/posix_compat.h"

#include <ctype.h>
#include <errno.h>
#include <io.h>
#include <string.h>
#include <windows.h>

#include "soa/install.h"

#include <stddef.h>

#include <atomic>
#include <string>
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

// POSIX rename: the target replaced when it exists, also when it is open (shared for delete) or
// read-only (Linux needs only a writable directory), with POSIX semantics: the old file stays
// readable through its open handles. FILE_RENAME_FLAG_REPLACE_IF_EXISTS | POSIX_SEMANTICS |
// IGNORE_READONLY_ATTRIBUTE (Windows 10 1809+, NTFS); where the file system has no such flags,
// MoveFileEx (which refuses an open or read-only target). The guest's rename is this one too
// (runtime/src/hle/host_file.h: the game's downloader renames NAME.tmp over NAME).
extern "C" int soa_rename(const char* from, const char* to) {
    auto fail = [](DWORD e) {
        errno = e == ERROR_FILE_NOT_FOUND || e == ERROR_PATH_NOT_FOUND || e == ERROR_INVALID_NAME ? ENOENT
                : e == ERROR_ACCESS_DENIED || e == ERROR_SHARING_VIOLATION || e == ERROR_LOCK_VIOLATION ? EACCES
                : e == ERROR_DIR_NOT_EMPTY ? ENOTEMPTY
                : e == ERROR_NOT_SAME_DEVICE ? EXDEV
                : e == ERROR_FILE_EXISTS || e == ERROR_ALREADY_EXISTS ? EEXIST
                : EIO;
        return -1;
    };
    // (the values of winbase.h / ntifs.h, here because MinGW gates them on _WIN32_WINNT and lacks
    // the read-only one)
    constexpr DWORD kReplace = 0x1, kPosix = 0x2, kIgnoreReadOnly = 0x40;
    constexpr int kFileRenameInfoEx = 22;  // FILE_INFO_BY_HANDLE_CLASS
    auto wide = [](const char* s) {        // (ANSI, as the CRT's own path calls)
        int n = MultiByteToWideChar(CP_ACP, 0, s, -1, nullptr, 0);
        std::wstring w(n > 0 ? n - 1 : 0, L'\0');
        if (n > 1) MultiByteToWideChar(CP_ACP, 0, s, -1, w.data(), n);
        return w;
    };
    // the target as a full path (the call takes a relative one against the source's directory)
    std::wstring t = wide(to);
    DWORD n = GetFullPathNameW(t.c_str(), 0, nullptr, nullptr);
    if (n == 0) return fail(GetLastError());
    std::wstring full(n, L'\0');
    full.resize(GetFullPathNameW(t.c_str(), n, full.data(), nullptr));
    HANDLE h = CreateFileA(from, DELETE | SYNCHRONIZE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                           OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, nullptr);
    if (h == INVALID_HANDLE_VALUE) return fail(GetLastError());
    // FILE_RENAME_INFO: Flags (a union with ReplaceIfExists), RootDirectory, FileNameLength, FileName
    std::vector<unsigned char> buf(offsetof(FILE_RENAME_INFO, FileName) + (full.size() + 1) * sizeof(WCHAR));
    auto* ri = reinterpret_cast<FILE_RENAME_INFO*>(buf.data());
    *reinterpret_cast<DWORD*>(ri) = kReplace | kPosix | kIgnoreReadOnly;
    ri->RootDirectory = nullptr;
    ri->FileNameLength = (DWORD)(full.size() * sizeof(WCHAR));
    memcpy(ri->FileName, full.c_str(), (full.size() + 1) * sizeof(WCHAR));
    bool ok = SetFileInformationByHandle(h, (FILE_INFO_BY_HANDLE_CLASS)kFileRenameInfoEx, buf.data(), (DWORD)buf.size());
    DWORD e = ok ? 0 : GetLastError();
    CloseHandle(h);
    if (ok) return 0;
    // no POSIX rename on this file system, or another volume
    if (e == ERROR_INVALID_PARAMETER || e == ERROR_NOT_SUPPORTED || e == ERROR_INVALID_FUNCTION || e == ERROR_NOT_SAME_DEVICE) {
        if (MoveFileExW(wide(from).c_str(), full.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED)) return 0;
        e = GetLastError();
    }
    return fail(e);
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

// stderr unbuffered, as C and Linux have it. msvcrt.dll (the C runtime of the distribution's
// MinGW-w64 GCC) buffers stderr fully (4 KB) when it is a pipe or a file, not a console: a program
// run from WSL, a script or a test harness then showed its log only in 4 KB pieces and at exit. The
// session drivers wait on log lines (the runtime's "I/perf" line every 10 s), so a quiet stretch,
// such as the client's data check after a download, read as a hung client ("no frame-rate line
// for 120s"). Every program that links
// soa_compat gets this before main().
namespace {
__attribute__((constructor(101))) void unbuffer_stderr() { setvbuf(stderr, nullptr, _IONBF, 0); }
}  // namespace
// soa/install.h: the running executable's path, "" when unknown.
std::string soa::install::exe_path_win32() {
    std::vector<wchar_t> buf(32768);
    DWORD n = GetModuleFileNameW(nullptr, buf.data(), (DWORD)buf.size());
    if (n == 0 || n >= buf.size()) return "";
    return std::filesystem::path(std::wstring(buf.data(), n)).string();
}
#endif
