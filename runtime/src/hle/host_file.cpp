// The guest's file calls with Linux semantics on either host: hle/host_file.h.
#include "hle/host_file.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#ifdef _WIN32
#include <io.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>

#else
#include <unistd.h>
#endif

namespace soa::hostfile {

#ifndef _WIN32

int open(const char* path, int oflag, int pmode) { return ::open(path, oflag, (mode_t)pmode); }
FILE* fopen(const char* path, const char* mode) { return ::fopen(path, mode); }
int unlink(const char* path) { return ::unlink(path); }
int remove(const char* path) { return ::remove(path); }

#else

namespace {

// (the values of winbase.h for Windows 10 1809, defined here: MinGW's headers gate them on
// _WIN32_WINNT)
constexpr DWORD kDispositionDelete = 0x1, kDispositionPosix = 0x2, kDispositionIgnoreReadOnly = 0x10;
constexpr int kFileDispositionInfoEx = 21;  // FILE_INFO_BY_HANDLE_CLASS

constexpr DWORD kShareAll = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;

int fail(DWORD e) {
    switch (e) {
    case ERROR_FILE_NOT_FOUND:
    case ERROR_PATH_NOT_FOUND:
    case ERROR_INVALID_NAME:
    case ERROR_INVALID_DRIVE:
    case ERROR_BAD_NETPATH:
    case ERROR_BAD_PATHNAME: errno = ENOENT; break;
    case ERROR_FILE_EXISTS:
    case ERROR_ALREADY_EXISTS: errno = EEXIST; break;
    case ERROR_DIR_NOT_EMPTY: errno = ENOTEMPTY; break;
    case ERROR_DIRECTORY: errno = ENOTDIR; break;
    case ERROR_NOT_SAME_DEVICE: errno = EXDEV; break;
    case ERROR_TOO_MANY_OPEN_FILES: errno = EMFILE; break;
    case ERROR_DISK_FULL:
    case ERROR_HANDLE_DISK_FULL: errno = ENOSPC; break;
    case ERROR_FILENAME_EXCED_RANGE: errno = ENAMETOOLONG; break;
    case ERROR_INVALID_PARAMETER: errno = EINVAL; break;
    default: errno = EACCES; break;  // ACCESS_DENIED, SHARING_VIOLATION, LOCK_VIOLATION, ...
    }
    return -1;
}

// FILE_INFO_BY_HANDLE_CLASS values MinGW may not declare
bool set_info(HANDLE h, int cls, const void* p, size_t n) {
    return SetFileInformationByHandle(h, (FILE_INFO_BY_HANDLE_CLASS)cls, (LPVOID)p, (DWORD)n) != 0;
}
// the file system has no POSIX semantics (FAT, some network drives): the classic call instead
bool no_posix(DWORD e) { return e == ERROR_INVALID_PARAMETER || e == ERROR_NOT_SUPPORTED || e == ERROR_INVALID_FUNCTION; }

bool is_dir(const char* path) {
    DWORD a = GetFileAttributesA(path);
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY) && !(a & FILE_ATTRIBUTE_REPARSE_POINT);
}

}  // namespace

int open(const char* path, int oflag, int pmode) {
    DWORD access = 0;
    switch (oflag & (_O_RDONLY | _O_WRONLY | _O_RDWR)) {
    case _O_WRONLY: access = GENERIC_WRITE; break;
    case _O_RDWR: access = GENERIC_READ | GENERIC_WRITE; break;
    default: access = GENERIC_READ; break;
    }
    DWORD disp;
    if ((oflag & _O_CREAT) && (oflag & _O_EXCL)) disp = CREATE_NEW;
    else if ((oflag & _O_CREAT) && (oflag & _O_TRUNC)) disp = OPEN_ALWAYS;  // (truncated below: CREATE_ALWAYS would reset the attributes)
    else if (oflag & _O_CREAT) disp = OPEN_ALWAYS;
    else if (oflag & _O_TRUNC) disp = TRUNCATE_EXISTING;
    else disp = OPEN_EXISTING;
    if (oflag & _O_TRUNC) access |= GENERIC_WRITE;  // (TRUNCATE_EXISTING needs it; Linux truncates an O_RDONLY | O_TRUNC open too)
    // a new file without write permission is created read-only (as the CRT's _open does)
    DWORD attrs = (oflag & _O_CREAT) && !(pmode & _S_IWRITE) ? FILE_ATTRIBUTE_READONLY : FILE_ATTRIBUTE_NORMAL;
    SECURITY_ATTRIBUTES sa{sizeof sa, nullptr, (oflag & _O_NOINHERIT) ? FALSE : TRUE};
    HANDLE h = CreateFileA(path, access, kShareAll, &sa, disp, attrs, nullptr);
    if (h == INVALID_HANDLE_VALUE) {
        DWORD e = GetLastError();
        // a directory: Linux opens one for reading; the CRT refuses one as EACCES (kept: the
        // directory case of fopen is handled by its caller)
        return fail(e);
    }
    if ((oflag & _O_CREAT) && (oflag & _O_TRUNC) && GetLastError() == ERROR_ALREADY_EXISTS) {
        FILE_END_OF_FILE_INFO eof{};
        if (!set_info(h, FileEndOfFileInfo, &eof, sizeof eof)) {
            DWORD e = GetLastError();
            CloseHandle(h);
            return fail(e);
        }
    }
    int fd = _open_osfhandle((intptr_t)h, oflag & (_O_RDONLY | _O_WRONLY | _O_RDWR | _O_APPEND));
    if (fd < 0) {
        CloseHandle(h);
        errno = EMFILE;
        return -1;
    }
    return fd;
}

FILE* fopen(const char* path, const char* mode) {
    int oflag = 0;
    bool plus = strchr(mode, '+') != nullptr;
    switch (mode[0]) {
    case 'r': oflag = plus ? _O_RDWR : _O_RDONLY; break;
    case 'w': oflag = (plus ? _O_RDWR : _O_WRONLY) | _O_CREAT | _O_TRUNC; break;
    case 'a': oflag = (plus ? _O_RDWR : _O_WRONLY) | _O_CREAT | _O_APPEND; break;
    default: errno = EINVAL; return nullptr;
    }
    if (strchr(mode, 'x')) oflag |= _O_EXCL;
    if (strchr(mode, 'e')) oflag |= _O_NOINHERIT;  // O_CLOEXEC
    int fd = open(path, oflag | _O_BINARY, _S_IREAD | _S_IWRITE);
    if (fd < 0) return nullptr;
    // the stream's own mode: the CRT's letters only (no 'x' / 'e'), binary
    char m[4] = {mode[0], 0, 0, 0};
    size_t i = 1;
    if (plus) m[i++] = '+';
    m[i] = 'b';
    FILE* f = _fdopen(fd, m);
    if (!f) {
        int e = errno;
        _close(fd);
        errno = e;
    }
    return f;
}

int unlink(const char* path) {
    if (is_dir(path)) {
        errno = EISDIR;  // (Linux unlink of a directory)
        return -1;
    }
    HANDLE h = CreateFileA(path, DELETE, kShareAll, nullptr, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT, nullptr);
    if (h == INVALID_HANDLE_VALUE) return fail(GetLastError());
    struct {
        DWORD Flags;
    } ex{kDispositionDelete | kDispositionPosix | kDispositionIgnoreReadOnly};
    bool ok = set_info(h, kFileDispositionInfoEx, &ex, sizeof ex);
    DWORD e = ok ? 0 : GetLastError();
    if (!ok && no_posix(e)) {
        FILE_DISPOSITION_INFO d{TRUE};
        ok = set_info(h, FileDispositionInfo, &d, sizeof d);
        e = ok ? 0 : GetLastError();
    }
    CloseHandle(h);
    return ok ? 0 : fail(e);
}

int remove(const char* path) {
    if (is_dir(path)) return RemoveDirectoryA(path) ? 0 : fail(GetLastError());
    return unlink(path);
}

#endif

}  // namespace soa::hostfile
