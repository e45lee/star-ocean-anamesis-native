#pragma once
// The install-dir lookup: where a packaged program (scripts/package.sh; README.md "Packaging") finds
// the user's game files when no flag names them. Header-only, beside soa/paths.h (target soa_env).
// Used by soa (port/src/core/paths.cpp, main.cpp), soa-server (server/app/main.cpp) and soa-emu
// (emulator/src/main.cpp); flags and a source checkout still come first in each.
//
// The install dirs are the folder the executable is stored in and its `game/` subfolder
// (install_dirs()). In them:
//   - the 3.7.0 APK: any top-level *.apk whose lib/arm64-v8a/libSOA.so is the 3.7.0 library (its
//     size; kApk370Name first). Never recursive: the download tree is full of *.apk asset bundles
//     (Character/cp0202_b07a.apk). The zip itself is read by the caller's zip library (the
//     runtime's ZipArchive in soa and soa-emu): this header only lists and checks candidates;
//   - the 3.7.0 download: a folder holding version.bin, manifest/ and sqlite/basmaster.sqlite3
//     (is_download_dir), whatever it is called: the install dir itself, or one of its immediate
//     subfolders (download-3.7.0, SOA_*, the user's SOA-3.7.0-canonical-data.zip extracted into
//     game/, ...); else that zip itself, unextracted (soa/game_files.h find_download: the
//     zip-aware half, target soa_gamefiles).
// The programs' own generated data (data/gacha_pools.sqlite3, data/saves/seed/Game.xml,
// standin-assets/) sits in the install dir at its repository path: the install dir is the last
// "repo root" the repo-file lookups search (port core/paths.cpp, soa-server's repo_roots()).
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <functional>
#include <string>
#include <system_error>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

namespace soa::install {

// The 3.7.0 APK as downloaded from APKPure (README.md "Game files"), the name tried first.
inline constexpr const char* kApk370Name = "STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk";
// The 3.7.0 client library inside it and its size, which tells the 3.7.0 APK from other versions'
// (3.8.0's is another size) without inflating it.
inline constexpr const char* kLibEntry = "lib/arm64-v8a/libSOA.so";
inline constexpr uint64_t kLib370Size = 45988160u;
// The user's archive of the 3.7.0 download (the tree at its top level, stored), read in place
// without extracting it (soa/game_files.h find_download, soa/file_tree.h).
inline constexpr const char* kDataZipName = "SOA-3.7.0-canonical-data.zip";
// What README.txt (the packages') calls the folder for the game files.
inline constexpr const char* kGameSubdir = "game";

inline bool is_dir(const std::string& p) {
    std::error_code ec;
    return !p.empty() && std::filesystem::is_directory(std::filesystem::path(p), ec);
}
inline bool is_file(const std::string& p) {
    std::error_code ec;
    return !p.empty() && std::filesystem::is_regular_file(std::filesystem::path(p), ec);
}

// The running executable's path ('/' separators on both platforms), "" when unknown.
inline std::string exe_path() {
#ifdef _WIN32
    wchar_t buf[32768];
    DWORD n = GetModuleFileNameW(nullptr, buf, (DWORD)(sizeof buf / sizeof buf[0]));
    if (n == 0 || n >= sizeof buf / sizeof buf[0]) return "";
    std::string s = std::filesystem::path(std::wstring(buf, n)).string();
#else
    std::error_code ec;
    std::string s = std::filesystem::read_symlink("/proc/self/exe", ec).string();
    if (ec) return "";
#endif
    std::replace(s.begin(), s.end(), '\\', '/');
    return s;
}

// The folder the executable is stored in ("" when unknown).
inline std::string exe_dir() {
    std::string p = exe_path();
    size_t s = p.find_last_of('/');
    if (s == std::string::npos) return "";
    return s == 0 ? "/" : p.substr(0, s);
}

// The install dirs, in lookup order: the executable's folder, then its game/ subfolder (when it
// exists).
inline std::vector<std::string> install_dirs() {
    std::vector<std::string> v;
    std::string d = exe_dir();
    if (d.empty()) return v;
    v.push_back(d);
    if (is_dir(d + "/" + kGameSubdir)) v.push_back(d + "/" + kGameSubdir);
    return v;
}

// The entries of `dir` (names only, sorted).
inline std::vector<std::string> list_dir(const std::string& dir) {
    std::vector<std::string> v;
    std::error_code ec;
    for (std::filesystem::directory_iterator it(std::filesystem::path(dir), ec), end; !ec && it != end; it.increment(ec))
        v.push_back(it->path().filename().string());
    std::sort(v.begin(), v.end());
    return v;
}

inline bool ends_with_ci(const std::string& s, const char* suffix) {
    size_t n = strlen(suffix);
    if (s.size() < n) return false;
    for (size_t i = 0; i < n; i++)
        if (tolower((unsigned char)s[s.size() - n + i]) != tolower((unsigned char)suffix[i])) return false;
    return true;
}

// ---- the game files ---------------------------------------------------------------------------
// The top-level *.apk files of `dirs`, in lookup order (kApk370Name first in each dir).
inline std::vector<std::string> apk_candidates(const std::vector<std::string>& dirs) {
    std::vector<std::string> v;
    for (auto& d : dirs) {
        if (is_file(d + "/" + kApk370Name)) v.push_back(d + "/" + kApk370Name);
        for (auto& n : list_dir(d))
            if (n != kApk370Name && ends_with_ci(n, ".apk") && is_file(d + "/" + n)) v.push_back(d + "/" + n);
    }
    return v;
}

// The first 3.7.0 APK among apk_candidates(dirs). `lib_size(apk)` is the caller's zip reader: the
// size of the APK's kLibEntry, or -1 when it isn't a zip with one. `notes` (if given) collects the
// candidates that were rejected, with the reason.
inline std::string find_apk_370(const std::vector<std::string>& dirs, const std::function<int64_t(const std::string&)>& lib_size,
                                std::vector<std::string>* notes = nullptr) {
    for (auto& p : apk_candidates(dirs)) {
        int64_t n = lib_size(p);
        if (n == (int64_t)kLib370Size) return p;
        if (notes)
            notes->push_back(p + (n < 0 ? ": not the game's APK (no " + std::string(kLibEntry) + ")"
                                        : ": another version of the game (its libSOA.so isn't 3.7.0's)"));
    }
    return "";
}

// Is `dir` a 3.7.0 download tree (the original CDN's files, as the game's downloader stores them)?
inline bool is_download_dir(const std::string& dir) {
    return is_file(dir + "/version.bin") && is_dir(dir + "/manifest") && is_file(dir + "/sqlite/basmaster.sqlite3");
}

// The first download tree among `dirs` themselves and their immediate subfolders
// (download-3.7.0 first, then the others by name).
inline std::string find_download_dir(const std::vector<std::string>& dirs) {
    for (auto& d : dirs) {
        if (is_download_dir(d)) return d;
        if (is_download_dir(d + "/download-3.7.0")) return d + "/download-3.7.0";
        for (auto& n : list_dir(d)) {
            std::string p = d + "/" + n;
            if (is_dir(p) && is_download_dir(p)) return p;
        }
    }
    return "";
}

// The one-line pointer the programs print when a game file is missing.
inline std::string missing_hint() {
    std::string d = exe_dir();
    return "put the game files in " + (d.empty() ? std::string(kGameSubdir) : d + "/" + kGameSubdir) +
           " (the 3.7.0 APK, and the 3.7.0 download: SOA-3.7.0-canonical-data.zip, zipped or extracted): see README.txt";
}

}  // namespace soa::install
