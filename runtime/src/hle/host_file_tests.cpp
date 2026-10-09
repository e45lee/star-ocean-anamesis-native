// The guest's file calls keep Linux semantics on either host (hle/host_file.h): what the game's
// downloader relies on when it replaces a downloaded file (NAME.tmp renamed over NAME, which may be a
// read-only hard link into the shared pre-downloaded phone, or open). Also run by
// build/runtime/soaruntime_tests and build-win/runtime/soaruntime_tests.exe.
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <io.h>
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <atomic>
#include <filesystem>
#include <string>

#include "soaruntime/core/selftest.h"
#include "hle/host_file.h"

namespace soa {
namespace {

namespace fs = std::filesystem;

// a fresh directory under the host's temp dir, removed (read-only files too) at the end
struct TempDir {
    fs::path dir;
    TempDir() {
        static std::atomic<int> n{0};
        dir = fs::temp_directory_path() / ("soa-host-file-" + std::to_string((long long)fs::file_time_type::clock::now().time_since_epoch().count()) +
                                           "-" + std::to_string(n++));
        fs::create_directories(dir);
    }
    ~TempDir() {
        std::error_code ec;
        for (auto& e : fs::recursive_directory_iterator(dir, ec))
            if (e.is_regular_file(ec)) chmod(e.path().string().c_str(), 0666);
        fs::remove_all(dir, ec);
    }
    std::string operator/(const char* name) const { return (dir / name).string(); }
};

bool put(const std::string& path, const std::string& data) {
    FILE* f = hostfile::fopen(path.c_str(), "wb");
    if (!f) return false;
    bool ok = fwrite(data.data(), 1, data.size(), f) == data.size();
    return fclose(f) == 0 && ok;
}
std::string get(const std::string& path) {
    FILE* f = hostfile::fopen(path.c_str(), "rb");
    if (!f) return "<missing>";
    std::string s;
    char buf[256];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, n);
    fclose(f);
    return s;
}
std::string rest(FILE* f) {
    std::string s;
    char buf[256];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, n);
    return s;
}
bool exists(const std::string& path) {
    struct stat st;
    return stat(path.c_str(), &st) == 0;
}
bool hard_link(const std::string& target, const std::string& link) {
#ifdef _WIN32
    return CreateHardLinkA(link.c_str(), target.c_str(), nullptr) != 0;
#else
    return ::link(target.c_str(), link.c_str()) == 0;
#endif
}

RUNTIME_TEST("hle/host-file-rename-replaces") {
    TempDir d;
    std::string a = d / "master.tmp", b = d / "master";
    t.expect_eq(put(a, "new") && put(b, "old"), true, "files written");
    t.expect_eq(rename(a.c_str(), b.c_str()), 0, "rename over an existing file");
    t.expect_eq(get(b), std::string("new"), "the target has the new content");
    t.expect_eq(exists(a), false, "the source name is gone");
    t.expect_eq(rename(b.c_str(), (d / "renamed").c_str()), 0, "a plain rename");
    t.expect_eq(get(d / "renamed"), std::string("new"), "renamed content");
    errno = 0;
    t.expect_eq(rename((d / "nothing").c_str(), b.c_str()), -1, "a missing source fails");
    t.expect_eq(errno, ENOENT, "ENOENT");
}

// The shared phone's case: the target is a read-only hard link to a file other phones share.
RUNTIME_TEST("hle/host-file-read-only-hard-link") {
    TempDir d;
    std::string shared = d / "shared", target = d / "basmaster.sqlite3", tmp = d / "basmaster.sqlite3.tmp";
    t.expect_eq(put(shared, "shared master"), true, "shared file written");
    t.expect_eq(hard_link(shared, target), true, "hard link made");
    t.expect_eq(chmod(shared.c_str(), 0444), 0, "made read-only (the Windows read-only attribute)");
    t.expect_eq(put(tmp, "downloaded master"), true, "the download written");
    t.expect_eq(rename(tmp.c_str(), target.c_str()), 0, "rename over a read-only target");
    t.expect_eq(get(target), std::string("downloaded master"), "the run's name has the download");
    t.expect_eq(get(shared), std::string("shared master"), "the shared file is untouched");
    // unlink / remove of a read-only link (the downloader's DeleteFile fallback)
    t.expect_eq(hard_link(shared, target + ".2"), true, "second link made");
    t.expect_eq(hostfile::unlink((target + ".2").c_str()), 0, "unlink of a read-only file");
    t.expect_eq(hard_link(shared, target + ".3"), true, "third link made");
    t.expect_eq(hostfile::remove((target + ".3").c_str()), 0, "remove of a read-only file");
    t.expect_eq(exists(target + ".2") || exists(target + ".3"), false, "the links are gone");
    t.expect_eq(get(shared), std::string("shared master"), "the shared file is still there");
    // writing through the read-only name is refused, as on Linux
    errno = 0;
    t.expect_eq(hostfile::fopen(shared.c_str(), "r+b") == nullptr, true, "no write open of a read-only file");
    t.expect_eq(errno, EACCES, "EACCES");
}

// Linux lets a file be unlinked or renamed over while it is open; the open handle keeps the old
// content and the name is free at once.
RUNTIME_TEST("hle/host-file-open-files") {
    TempDir d;
    std::string a = d / "db", tmp = d / "db.tmp";
    t.expect_eq(put(a, "first"), true, "written");
    FILE* held = hostfile::fopen(a.c_str(), "rb");
    t.expect_eq(held != nullptr, true, "held open");
    t.expect_eq(put(tmp, "second"), true, "replacement written");
    t.expect_eq(rename(tmp.c_str(), a.c_str()), 0, "rename over an open file");
    t.expect_eq(get(a), std::string("second"), "the name has the new file");
    if (held) t.expect_eq(rest(held), std::string("first"), "the open handle still reads the old file");
    if (held) fclose(held);

    held = hostfile::fopen(a.c_str(), "rb");
    t.expect_eq(hostfile::unlink(a.c_str()), 0, "unlink of an open file");
    t.expect_eq(exists(a), false, "the name is gone at once");
    t.expect_eq(put(a, "third"), true, "and can be created again while the old one is open");
    t.expect_eq(get(a), std::string("third"), "the new file");
    if (held) t.expect_eq(rest(held), std::string("second"), "the old handle reads the unlinked file");
    if (held) fclose(held);

    // a file opened for writing (descriptor) renamed away while open
    int fd = hostfile::open((d / "log").c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    t.expect_eq(fd >= 0, true, "open(O_CREAT)");
    t.expect_eq(rename((d / "log").c_str(), (d / "log.old").c_str()), 0, "rename of an open file");
    if (fd >= 0) close(fd);
    t.expect_eq(exists(d / "log.old"), true, "renamed");
}

RUNTIME_TEST("hle/host-file-open-modes") {
    TempDir d;
    std::string a = d / "f";
    errno = 0;
    t.expect_eq(hostfile::fopen(a.c_str(), "rb") == nullptr, true, "r of a missing file fails");
    t.expect_eq(errno, ENOENT, "ENOENT");
    t.expect_eq(put(a, "abc"), true, "w creates");
    FILE* f = hostfile::fopen(a.c_str(), "ab");
    if (f) fputs("de", f), fclose(f);
    t.expect_eq(get(a), std::string("abcde"), "a appends");
    f = hostfile::fopen(a.c_str(), "r+b");
    if (f) fputs("X", f), fclose(f);
    t.expect_eq(get(a), std::string("Xbcde"), "r+ writes in place");
    t.expect_eq(put(a, "z"), true, "w truncates");
    t.expect_eq(get(a), std::string("z"), "truncated");
    errno = 0;
    t.expect_eq(hostfile::fopen(a.c_str(), "wx") == nullptr, true, "wx of an existing file fails");
    t.expect_eq(errno, EEXIST, "EEXIST");
    errno = 0;
    t.expect_eq(hostfile::open(a.c_str(), O_WRONLY | O_CREAT | O_EXCL, 0644), -1, "O_EXCL of an existing file fails");
    t.expect_eq(errno, EEXIST, "EEXIST");
    f = hostfile::fopen(a.c_str(), "re");
    t.expect_eq(f != nullptr, true, "re (O_CLOEXEC) opens");
    if (f) fclose(f);
    fs::create_directories(d.dir / "sub");
    errno = 0;
    t.expect_eq(hostfile::unlink((d / "sub").c_str()), -1, "unlink of a directory fails");
    t.expect_eq(hostfile::remove((d / "sub").c_str()), 0, "remove of an empty directory");
    t.expect_eq(exists(d / "sub"), false, "directory gone");
    errno = 0;
    t.expect_eq(hostfile::unlink((d / "missing").c_str()), -1, "unlink of a missing file fails");
    t.expect_eq(errno, ENOENT, "ENOENT");
}

// stderr unbuffered on every host (common/src/posix_compat_win32.cpp: msvcrt buffers it into a pipe
// or file, and the session drivers read the log as it comes)
RUNTIME_TEST("hle/host-file-stderr-unbuffered") {
#if defined(_WIN32) && !defined(_UCRT)
    t.expect_eq((stderr->_flag & _IONBF) != 0, true, "stderr is _IONBF");
#endif
}

}  // namespace
}  // namespace soa
