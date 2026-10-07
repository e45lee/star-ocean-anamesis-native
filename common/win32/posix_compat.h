// The POSIX calls our code makes that MinGW-w64 lacks or spells differently (port/PLAN.md 5b, W).
// Force-included (-include) into every source of a target that links soa_compat, on Windows
// only (common/CMakeLists.txt), so portable code keeps its POSIX spelling. No <windows.h> here: its
// macros (min/max, ERROR, ...) would leak into every file; what needs Win32 goes in
// common/src/posix_compat_win32.cpp.
//
// The missing functions are inline wrappers under their real names (no macros: a macro would also
// rename members and other namespaces' functions of that name), over the soa_* implementations.
// `rename` alone stays a macro: the C runtime has its own (which won't replace a file), declared
// in <stdio.h>.
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
// stdio before `#define rename` below: libstdc++'s <cstdio> #undefs rename (back to the C runtime's,
// which won't replace a file), so it must have run, and its include guard set, before the define.
// The define also renames std::filesystem::rename: call rename(), never std::filesystem::rename.
#ifdef __cplusplus
#include <cstdio>
#else
#include <stdio.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#ifndef O_CLOEXEC
#define O_CLOEXEC _O_NOINHERIT
#endif
#ifndef SIGPIPE
#define SIGPIPE 13  // never raised on Windows; signal(SIGPIPE, ...) just fails
#endif
#ifndef SIGTRAP
#define SIGTRAP 5  // Linux's number (the GDB stub reports signals by it)
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
// rename with POSIX semantics: replaces an existing target, also an open or read-only one.
int soa_rename(const char* from, const char* to);
// gettid: the Win32 thread id.
int soa_gettid(void);
// pread: a positional read (ReadFile with an offset; the descriptor's position is left alone).
ssize_t soa_pread(int fd, void* buf, size_t n, long long offset);
// strptime for the numeric directives our code uses (%Y %m %d %H %M %S %y %e %j %%, whitespace).
char* soa_strptime(const char* s, const char* fmt, struct tm* tm);
// setenv / unsetenv over _putenv_s.
int soa_setenv(const char* name, const char* value, int overwrite);
int soa_unsetenv(const char* name);
// mkdtemp: a new directory from a template ending in XXXXXX (mingw-w64 has it only from version
// 12; Ubuntu 24.04's is 11).
char* soa_mkdtemp(char* tmpl);
#ifdef __cplusplus
}
#endif

#define rename soa_rename

static inline char* realpath(const char* path, char* resolved) { return soa_realpath(path, resolved); }
static inline ssize_t pread(int fd, void* buf, size_t n, long long offset) { return soa_pread(fd, buf, n, offset); }
static inline char* strptime(const char* s, const char* fmt, struct tm* tm) { return soa_strptime(s, fmt, tm); }
static inline int gettid(void) { return soa_gettid(); }
static inline int setenv(const char* name, const char* value, int overwrite) { return soa_setenv(name, value, overwrite); }
static inline int unsetenv(const char* name) { return soa_unsetenv(name); }
#if __MINGW64_VERSION_MAJOR < 12  // (mingw-w64 12 has its own)
static inline char* mkdtemp(char* tmpl) { return soa_mkdtemp(tmpl); }
#endif
// no symlinks: lstat is stat
static inline int lstat(const char* path, struct stat* st) { return stat(path, st); }

#ifdef __cplusplus
// mkdir(path, mode): MinGW's mkdir takes the path only.
inline int mkdir(const char* path, int /*mode*/) { return _mkdir(path); }
#endif
// No users: everything runs as uid 0.
static inline int getuid(void) { return 0; }
// glibc's malloc_usable_size: the CRT heap's block size.
static inline size_t malloc_usable_size(void* p) { return _msize(p); }

#endif  // _WIN32
