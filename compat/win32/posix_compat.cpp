// posix_compat.h's functions (Windows only).
#ifdef _WIN32
#include "posix_compat.h"

#include <errno.h>
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

extern "C" int soa_gettid(void) { return (int)GetCurrentThreadId(); }

extern "C" int soa_setenv(const char* name, const char* value, int overwrite) {
    if (!name || !*name || strchr(name, '=')) return errno = EINVAL, -1;
    if (!overwrite && getenv(name)) return 0;
    return _putenv_s(name, value) == 0 ? 0 : -1;
}

extern "C" int soa_unsetenv(const char* name) { return _putenv_s(name, "") == 0 ? 0 : -1; }
#endif
