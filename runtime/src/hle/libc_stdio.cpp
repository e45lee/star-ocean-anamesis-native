// Bionic libc: stdio, printf/scanf, file descriptors, filesystem.
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <sys/ioctl.h>
#include <sys/select.h>
#include <syslog.h>
#endif
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include <algorithm>
#include <string>
#include <vector>

#include "core/hle.h"
#include "core/log.h"
#include "core/vfs.h"
#include "hle/format.h"
#include "hle/host_file.h"

namespace soa {
namespace {

// ---- FILE* ----
// Guest stdin/stdout/stderr are &__sF[0..2] (bionic FILE is 152 bytes on LP64).
constexpr size_t kBionicFileSize = 152;
alignas(16) u8 g_sF[3 * kBionicFileSize];

FILE* gfile(u64 p) {
    u64 b = (u64)g_sF;
    if (p >= b && p < b + sizeof g_sF) {
        switch ((p - b) / kBionicFileSize) {
        case 0: return stdin;
        case 1: return stdout;
        default: return stderr;
        }
    }
    return (FILE*)p;
}

void th_fopen(Cpu& c) {
    std::string hp = host_path(arg_str(c, 0));
    FILE* f = hostfile::fopen(hp.c_str(), arg_str(c, 1));
#ifdef _WIN32
    // Linux opens a directory for reading (reads then fail with EISDIR); the client tests its
    // download directory that way before the data check (fopen(".../files/", "rb")). Windows' CRT
    // refuses: a stream on NUL (reads: EOF) stands in.
    if (!f && !strpbrk(arg_str(c, 1), "wa+")) {
        std::string d = hp;
        while (d.size() > 3 && (d.back() == '/' || d.back() == '\\')) d.pop_back();  // (the CRT's stat refuses a trailing slash)
        struct stat st;
        if (stat(d.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) f = fopen("NUL", "rb");
    }
#endif
    LOGD("io", "fopen(%s -> %s, %s) = %p", arg_str(c, 0), hp.c_str(), arg_str(c, 1), (void*)f);
    ret_ptr(c, f);
}
void th_fclose(Cpu& c) { ret(c, (u64)(s64)fclose(gfile(c.x(0)))); }
void th_fflush(Cpu& c) { ret(c, (u64)(s64)fflush(c.x(0) ? gfile(c.x(0)) : nullptr)); }
void th_fgets(Cpu& c) { ret_ptr(c, fgets((char*)c.x(0), (int)c.x(1), gfile(c.x(2)))); }
void th_fputc(Cpu& c) { ret(c, (u64)(s64)fputc((int)c.x(0), gfile(c.x(1)))); }
void th_fread(Cpu& c) { ret(c, fread((void*)c.x(0), c.x(1), c.x(2), gfile(c.x(3)))); }
void th_fwrite(Cpu& c) { ret(c, fwrite((const void*)c.x(0), c.x(1), c.x(2), gfile(c.x(3)))); }
// The guest's long is 64-bit (LP64); fseeko/ftello keep the offset 64-bit on an LLP64 host too.
void th_fseek(Cpu& c) { ret(c, (u64)(s64)fseeko(gfile(c.x(0)), (off_t)(s64)c.x(1), (int)c.x(2))); }
void th_ftell(Cpu& c) { ret(c, (u64)(s64)ftello(gfile(c.x(0)))); }
void th_puts(Cpu& c) { ret(c, (u64)(s64)puts(arg_str(c, 0))); }
void th_putchar(Cpu& c) { ret(c, (u64)(s64)putchar((int)c.x(0))); }

void th_popen(Cpu& c) {
    LOGW("io", "popen(\"%s\") refused", arg_str(c, 0));
    errno = ENOSYS;
    ret(c, 0);
}
void th_pclose(Cpu& c) { ret(c, (u64)-1); }

// ---- printf family ----
void write_out(FILE* f, const std::string& s) { fwrite(s.data(), 1, s.size(), f); }

void th_printf(Cpu& c) {
    RegVa va(c, 1);
    auto s = guest_format(arg_str(c, 0), va);
    write_out(stdout, s);
    ret(c, s.size());
}
void th_fprintf(Cpu& c) {
    RegVa va(c, 2);
    auto s = guest_format(arg_str(c, 1), va);
    write_out(gfile(c.x(0)), s);
    ret(c, s.size());
}
void th_vfprintf(Cpu& c) {
    GuestVaList va(c.x(2));
    auto s = guest_format(arg_str(c, 1), va);
    write_out(gfile(c.x(0)), s);
    ret(c, s.size());
}
void th_sprintf(Cpu& c) {
    RegVa va(c, 2);
    auto s = guest_format(arg_str(c, 1), va);
    memcpy((void*)c.x(0), s.c_str(), s.size() + 1);
    ret(c, s.size());
}
void copy_bounded(u64 dst, size_t n, const std::string& s) {
    if (n == 0) return;
    size_t k = std::min(n - 1, s.size());
    memcpy((void*)dst, s.data(), k);
    ((char*)dst)[k] = 0;
}
void th_snprintf(Cpu& c) {
    RegVa va(c, 3);
    auto s = guest_format(arg_str(c, 2), va);
    copy_bounded(c.x(0), c.x(1), s);
    ret(c, s.size());
}
void th_vsnprintf(Cpu& c) {
    GuestVaList va(c.x(3));
    auto s = guest_format(arg_str(c, 2), va);
    copy_bounded(c.x(0), c.x(1), s);
    ret(c, s.size());
}
void th_vasprintf(Cpu& c) {
    GuestVaList va(c.x(2));
    auto s = guest_format(arg_str(c, 1), va);
    char* p = (char*)malloc(s.size() + 1);
    memcpy(p, s.c_str(), s.size() + 1);
    *(char**)c.x(0) = p;
    ret(c, s.size());
}
void th_swprintf(Cpu& c) {
    RegVa va(c, 3);
    auto s = guest_wformat((const wchar_t*)c.x(2), va);
    wchar_t* dst = (wchar_t*)c.x(0);
    size_t n = c.x(1);
    if (s.size() >= n) {
        if (n) {
            wmemcpy(dst, s.data(), n - 1);
            dst[n - 1] = 0;
        }
        ret(c, (u64)-1);
        return;
    }
    wmemcpy(dst, s.c_str(), s.size() + 1);
    ret(c, s.size());
}

void th_sscanf(Cpu& c) {
    RegVa va(c, 2);
    auto a = scanf_args(arg_str(c, 1), va);
    int r = sscanf(arg_str(c, 0), host_scanf_format(arg_str(c, 1)).c_str(), a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17],
                   a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
    ret(c, (u64)(s64)r);
}
void th_vsscanf(Cpu& c) {
    GuestVaList va(c.x(2));
    auto a = scanf_args(arg_str(c, 1), va);
    int r = sscanf(arg_str(c, 0), host_scanf_format(arg_str(c, 1)).c_str(), a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17],
                   a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
    ret(c, (u64)(s64)r);
}
void th_fscanf(Cpu& c) {
    RegVa va(c, 2);
    auto a = scanf_args(arg_str(c, 1), va);
    int r = fscanf(gfile(c.x(0)), host_scanf_format(arg_str(c, 1)).c_str(), a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17],
                   a[18], a[19], a[20], a[21], a[22], a[23], a[24], a[25], a[26], a[27], a[28], a[29], a[30], a[31]);
    ret(c, (u64)(s64)r);
}

void th_syslog(Cpu& c) {
    RegVa va(c, 2);
    auto s = guest_format(arg_str(c, 1), va);
    LOGI("syslog", "%s", s.c_str());
}

#ifndef _WIN32  // Windows: libc_win32.cpp (Linux open flags translated; guest fds are a table there)
// ---- file descriptors ----
// open(2) flag bits that differ between arm64 and x86-64.
constexpr int A64_O_DIRECTORY = 040000, A64_O_NOFOLLOW = 0100000, A64_O_DIRECT = 0200000, A64_O_LARGEFILE = 0400000;
int oflags_to_host(int f) {
    int out = f & ~(A64_O_DIRECTORY | A64_O_NOFOLLOW | A64_O_DIRECT | A64_O_LARGEFILE);
    if (f & A64_O_DIRECTORY) out |= O_DIRECTORY;
    if (f & A64_O_NOFOLLOW) out |= O_NOFOLLOW;
    if (f & A64_O_DIRECT) out |= O_DIRECT;
    return out;
}
int oflags_from_host(int f) {
    int out = f & ~(O_DIRECTORY | O_NOFOLLOW | O_DIRECT | 0100000 /*O_LARGEFILE*/);
    if (f & O_DIRECTORY) out |= A64_O_DIRECTORY;
    if (f & O_NOFOLLOW) out |= A64_O_NOFOLLOW;
    if (f & O_DIRECT) out |= A64_O_DIRECT;
    return out;
}

void th_open(Cpu& c) {
    std::string hp = host_path(arg_str(c, 0));
    int fd = open(hp.c_str(), oflags_to_host((int)c.x(1)), (mode_t)c.x(2));
    LOGD("io", "open(%s -> %s, %#x) = %d", arg_str(c, 0), hp.c_str(), (int)c.x(1), fd);
    ret(c, (u64)(s64)fd);
}
void th_fcntl(Cpu& c) {
    int fd = (int)c.x(0), cmd = (int)c.x(1);
    u64 a = c.x(2);
    int r;
    if (cmd == F_SETFL) r = fcntl(fd, cmd, oflags_to_host((int)a));
    else if (cmd == F_GETFL) {
        r = fcntl(fd, cmd);
        if (r >= 0) r = oflags_from_host(r);
    } else r = fcntl(fd, cmd, a);
    ret(c, (u64)(s64)r);
}
void th_ioctl(Cpu& c) { ret(c, (u64)(s64)ioctl((int)c.x(0), (unsigned long)c.x(1), (void*)c.x(2))); }
#endif

// ---- stat ----
struct BionicStat {
    u64 st_dev, st_ino;
    u32 st_mode, st_nlink, st_uid, st_gid;
    u64 st_rdev, pad1;
    s64 st_size;
    s32 st_blksize, pad2;
    s64 st_blocks;
    s64 atime, atime_ns, mtime, mtime_ns, ctime, ctime_ns;
    u32 unused[2];
};
static_assert(sizeof(BionicStat) == 128);
void to_bionic(const struct stat& s, u64 dst) {
    BionicStat b{};
    b.st_dev = s.st_dev;
    b.st_ino = s.st_ino;
    b.st_mode = s.st_mode;
    b.st_nlink = (u32)s.st_nlink;
    b.st_uid = s.st_uid;
    b.st_gid = s.st_gid;
    b.st_rdev = s.st_rdev;
    b.st_size = s.st_size;
#ifdef _WIN32  // no block size or nanoseconds in the CRT's stat
    b.st_blksize = 4096;
    b.st_blocks = (s.st_size + 511) / 512;
    b.atime = s.st_atime;
    b.mtime = s.st_mtime;
    b.ctime = s.st_ctime;
#else
    b.st_blksize = (s32)s.st_blksize;
    b.st_blocks = s.st_blocks;
    b.atime = s.st_atim.tv_sec;
    b.atime_ns = s.st_atim.tv_nsec;
    b.mtime = s.st_mtim.tv_sec;
    b.mtime_ns = s.st_mtim.tv_nsec;
    b.ctime = s.st_ctim.tv_sec;
    b.ctime_ns = s.st_ctim.tv_nsec;
#endif
    memcpy((void*)dst, &b, sizeof b);
}
void th_stat(Cpu& c) {
    struct stat s;
    int r = stat(host_path(arg_str(c, 0)).c_str(), &s);
    if (r == 0) to_bionic(s, c.x(1));
    LOGT("io", "stat(%s) = %d", arg_str(c, 0), r);
    ret(c, (u64)(s64)r);
}
void th_lstat(Cpu& c) {
    struct stat s;
    int r = lstat(host_path(arg_str(c, 0)).c_str(), &s);
    if (r == 0) to_bionic(s, c.x(1));
    ret(c, (u64)(s64)r);
}
#ifndef _WIN32
void th_fstat(Cpu& c) {
    struct stat s;
    int r = fstat((int)c.x(0), &s);
    if (r == 0) to_bionic(s, c.x(1));
    ret(c, (u64)(s64)r);
}
#endif

#define PATH1(name, expr)                                  \
    void th_##name(Cpu& c) {                               \
        std::string p0 = host_path(arg_str(c, 0));         \
        int r = expr;                                      \
        LOGT("io", #name "(%s) = %d", arg_str(c, 0), r);   \
        ret(c, (u64)(s64)r);                               \
    }
PATH1(access, access(p0.c_str(), (int)c.x(1)))
PATH1(mkdir, mkdir(p0.c_str(), (mode_t)c.x(1)))
PATH1(rmdir, rmdir(p0.c_str()))
PATH1(unlink, hostfile::unlink(p0.c_str()))
PATH1(remove, hostfile::remove(p0.c_str()))
#ifndef _WIN32
PATH1(utimes, utimes(p0.c_str(), (const struct timeval*)c.x(1)))
#endif
void th_rename(Cpu& c) {
    std::string a = host_path(arg_str(c, 0)), b = host_path(arg_str(c, 1));
    int r = rename(a.c_str(), b.c_str());  // (soa_rename on Windows: POSIX semantics, hle/host_file.h)
    LOGT("io", "rename(%s, %s) = %d", arg_str(c, 0), arg_str(c, 1), r);
    ret(c, (u64)(s64)r);
}
#ifndef _WIN32
void th_readlink(Cpu& c) {
    std::string a = host_path(arg_str(c, 0));
    ret(c, (u64)readlink(a.c_str(), (char*)c.x(1), c.x(2)));
}
#endif
void th_getcwd(Cpu& c) {
    char* buf = (char*)c.x(0);
    size_t n = c.x(1);
    if (!buf) {
        ret_ptr(c, strdup("/"));
        return;
    }
    if (n < 2) {
        errno = ERANGE;
        ret(c, 0);
        return;
    }
    strcpy(buf, "/");
    ret_ptr(c, buf);
}

// ---- fts (bionic FTSENT layout) ----
struct BionicFtsent {
    u64 fts_cycle, fts_parent, fts_link;
    s64 fts_number;
    u64 fts_pointer, fts_accpath, fts_path;
    s32 fts_errno, fts_symfd;
    u64 fts_pathlen, fts_namelen, fts_ino, fts_dev;
    u32 fts_nlink;
    s16 fts_level;
    u16 fts_info, fts_flags, fts_instr;
    u64 fts_statp;
    char fts_name[1];
};
static_assert(offsetof(BionicFtsent, fts_statp) == 112);
enum { FTS_D_ = 1, FTS_DNR_ = 4, FTS_DP_ = 6, FTS_F_ = 8, FTS_NS_ = 10, FTS_SL_ = 12 };

struct FtsHandle {
    std::vector<BionicFtsent*> ents;
    size_t idx = 0;
};

BionicFtsent* make_ent(const std::string& gpath, const std::string& name, int level, int info, const struct stat* st) {
    size_t sz = sizeof(BionicFtsent) + name.size() + 1;
    auto* e = (BionicFtsent*)calloc(1, sz);
    char* path = strdup(gpath.c_str());
    e->fts_path = e->fts_accpath = (u64)path;
    e->fts_pathlen = gpath.size();
    e->fts_namelen = name.size();
    e->fts_level = (s16)level;
    e->fts_info = (u16)info;
    memcpy(e->fts_name, name.c_str(), name.size() + 1);
    if (st) {
        auto* bs = (BionicStat*)calloc(1, sizeof(BionicStat));
        to_bionic(*st, (u64)bs);
        e->fts_statp = (u64)bs;
        e->fts_ino = st->st_ino;
        e->fts_dev = st->st_dev;
        e->fts_nlink = (u32)st->st_nlink;
    }
    return e;
}

void fts_walk(FtsHandle& h, const std::string& gpath, const std::string& name, int level) {
    std::string hp = host_path(gpath.c_str());
    struct stat st;
    if (lstat(hp.c_str(), &st) != 0) {
        h.ents.push_back(make_ent(gpath, name, level, FTS_NS_, nullptr));
        return;
    }
    if (S_ISDIR(st.st_mode)) {
        h.ents.push_back(make_ent(gpath, name, level, FTS_D_, &st));
        DIR* d = opendir(hp.c_str());
        if (!d) {
            h.ents.back()->fts_info = FTS_DNR_;
            return;
        }
        std::vector<std::string> names;
        while (dirent* de = readdir(d))
            if (strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) names.push_back(de->d_name);
        closedir(d);
        std::sort(names.begin(), names.end());
        for (auto& n : names) fts_walk(h, gpath + "/" + n, n, level + 1);
        h.ents.push_back(make_ent(gpath, name, level, FTS_DP_, &st));
    } else {
        h.ents.push_back(make_ent(gpath, name, level, S_ISLNK(st.st_mode) ? FTS_SL_ : FTS_F_, &st));
    }
}

void th_fts_open(Cpu& c) {
    auto* h = new FtsHandle();
    for (char** p = (char**)c.x(0); p && *p; p++) {
        std::string g = *p;
        while (g.size() > 1 && g.back() == '/') g.pop_back();
        auto slash = g.rfind('/');
        fts_walk(*h, g, slash == std::string::npos ? g : g.substr(slash + 1), 0);
    }
    ret_ptr(c, h);
}
void th_fts_read(Cpu& c) {
    auto* h = (FtsHandle*)c.x(0);
    ret_ptr(c, h->idx < h->ents.size() ? h->ents[h->idx++] : nullptr);
}
void th_fts_close(Cpu& c) {
    auto* h = (FtsHandle*)c.x(0);
    for (auto* e : h->ents) {
        free((void*)e->fts_path);
        free((void*)e->fts_statp);
        free(e);
    }
    delete h;
    ret(c, 0);
}

}  // namespace

void* bionic_sF() { return g_sF; }
void to_bionic_stat(const struct stat& s, u64 dst) { to_bionic(s, dst); }

void register_libc_stdio(Hle& h) {
    h.data("__sF", g_sF);
    h.fn("fopen", th_fopen);
    h.fn("fclose", th_fclose);
    h.fn("fflush", th_fflush);
    h.fn("fgets", th_fgets);
    h.fn("fputc", th_fputc);
    h.fn("fread", th_fread);
    h.fn("fwrite", th_fwrite);
    h.fn("fseek", th_fseek);
    h.fn("ftell", th_ftell);
    h.fn("puts", th_puts);
    h.fn("putchar", th_putchar);
    h.fn("popen", th_popen);
    h.fn("pclose", th_pclose);
    h.fn("printf", th_printf);
    h.fn("fprintf", th_fprintf);
    h.fn("vfprintf", th_vfprintf);
    h.fn("sprintf", th_sprintf);
    h.fn("snprintf", th_snprintf);
    h.fn("vsnprintf", th_vsnprintf);
    h.fn("vasprintf", th_vasprintf);
    h.fn("swprintf", th_swprintf);
    h.fn("sscanf", th_sscanf);
    h.fn("vsscanf", th_vsscanf);
    h.fn("fscanf", th_fscanf);
    h.fn("syslog", th_syslog);
    h.fn("openlog", [](Cpu&) {});
    h.fn("closelog", [](Cpu&) {});

#ifndef _WIN32
    h.fn("open", th_open);
    h.fn("fcntl", th_fcntl);
    h.fn("ioctl", th_ioctl);
    HLE_WRAP(h, close);
    HLE_WRAP(h, read);
    HLE_WRAP(h, write);
    HLE_WRAP(h, lseek64);
    HLE_WRAP(h, fsync);
    HLE_WRAP(h, ftruncate);
    HLE_WRAP(h, fchmod);
    HLE_WRAP(h, fchown);
    HLE_WRAP(h, pipe);
    HLE_WRAP(h, select);
#endif
    h.fn("stat", th_stat);
    h.fn("lstat", th_lstat);
#ifndef _WIN32
    h.fn("fstat", th_fstat);
#endif
    h.fn("access", th_access);
    h.fn("mkdir", th_mkdir);
    h.fn("rmdir", th_rmdir);
    h.fn("unlink", th_unlink);
    h.fn("remove", th_remove);
#ifndef _WIN32
    h.fn("utimes", th_utimes);
#endif
    h.fn("rename", th_rename);
#ifndef _WIN32
    h.fn("readlink", th_readlink);
#endif
    h.fn("getcwd", th_getcwd);
    h.fn("fts_open", th_fts_open);
    h.fn("fts_read", th_fts_read);
    h.fn("fts_close", th_fts_close);
}

}  // namespace soa
