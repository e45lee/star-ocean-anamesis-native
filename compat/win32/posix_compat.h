// The POSIX calls our code makes that MinGW-w64 lacks or spells differently (port/PLAN.md 5b, W).
// Force-included (-include) into every source of a target that links soa_compat, on Windows
// only (cmake/win32.cmake), so portable code keeps its POSIX spelling. No <windows.h> here: its
// macros (min/max, ERROR, ...) would leak into every file; what needs Win32 goes in posix_compat.cpp.
//
// Semantics differ where Windows has no equivalent: no symlinks (lstat is stat, S_ISLNK is false),
// no file modes (mkdir ignores the mode), no SIGPIPE (sockets don't raise it: MSG_NOSIGNAL is 0).
#pragma once
#ifdef _WIN32

#include <direct.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <malloc.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifndef O_CLOEXEC
#define O_CLOEXEC _O_NOINHERIT
#endif
#ifndef SIGPIPE
#define SIGPIPE 13  // never raised on Windows; signal(SIGPIPE, ...) just fails
#endif
#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif
#ifndef S_ISLNK
#define S_ISLNK(m) 0
#endif
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#ifdef __cplusplus
extern "C" {
#endif
// realpath: the absolute path with '/' separators (our code splits paths at '/'); NULL when the
// path doesn't exist, like POSIX. `resolved` (if not NULL) holds PATH_MAX bytes. "/proc/self/exe"
// is the running executable, as on Linux.
char* soa_realpath(const char* path, char* resolved);
// rename with POSIX semantics: replaces an existing target (MoveFileEx).
int soa_rename(const char* from, const char* to);
// gettid: the Win32 thread id.
int soa_gettid(void);
// setenv / unsetenv over _putenv_s.
int soa_setenv(const char* name, const char* value, int overwrite);
int soa_unsetenv(const char* name);
#ifdef __cplusplus
}
#endif

#define realpath soa_realpath
#define rename soa_rename
#define gettid soa_gettid
#define setenv soa_setenv
#define unsetenv soa_unsetenv
#define lstat stat

#ifdef __cplusplus
// mkdir(path, mode): MinGW's mkdir takes the path only.
inline int mkdir(const char* path, int /*mode*/) { return _mkdir(path); }
#endif
// glibc's malloc_usable_size: the CRT heap's block size.
static inline size_t malloc_usable_size(void* p) { return _msize(p); }

#endif  // _WIN32
