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
//   - the 3.7.0 download: SOA-3.7.0-canonical-data.zip, its canonical form, read in place
//     (soa/game_files.h find_download: the zip-aware half, target soa_gamefiles); a folder holding
//     version.bin, manifest/ and sqlite/basmaster.sqlite3 (is_download_dir) works too, whatever it
//     is called: the install dir itself, or one of its immediate subfolders (the zip extracted into
//     game/, ...), and is taken first.
// The programs' own generated data (data/gacha_pools.sqlite3, data/saves/seed/Game.xml,
// standin-assets/) sits in the install dir at its repository path: the install dirs are the last
// "repo roots" the repo-file lookups search (repo_roots below: port core/paths.cpp, soa-server's
// repo_roots(), soa-emu, soa-viewer). In a release build (scripts/build.sh --release: the
// packages) they are the only ones unless --repo DIR names a checkout: a release build never uses a
// checkout around it.
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <functional>
#include <initializer_list>
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
// (another version's is another size) without inflating it.
inline constexpr const char* kLibEntry = "lib/arm64-v8a/libSOA.so";
inline constexpr uint64_t kLib370Size = 45988160u;
// The user's archive of the 3.7.0 download (the tree at its top level, stored), read in place
// without extracting it (soa/game_files.h find_download, soa/file_tree.h).
inline constexpr const char* kDataZipName = "SOA-3.7.0-canonical-data.zip";
// The download in a checkout (find_repo_file; docs/environment.md "How the programs find the game
// files"): the zip, read in place (an extracted folder is given with --download PATH).
inline constexpr const char* kRepoDownloadZip = "work/SOA-3.7.0-canonical-data.zip";
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

// ---- the repo roots ---------------------------------------------------------------------------
// Where the programs look for repo files (find_repo_file and the like: data/, apk/, work/,
// standin-assets/, server/tests/fixtures, ...), one rule for soa (port/src/core/paths.cpp),
// soa-server (server/app/main.cpp repo_roots()), soa-emu (emulator/src/main.cpp) and soa-viewer
// (emulator-viewer/src/main.cpp; its XAPK lookup):
//
//   development build (scripts/build.sh): `--repo DIR`; else the first checkout upwards from the
//     executable; else upwards from the working directory. With a checkout, also the main checkout
//     of a git worktree whose work/ is a symlink into it. Then the install dirs; without a checkout,
//     the working directory last.
//   release build (scripts/build.sh --release, which the packages are made from; README.md
//     "Packaging"): `--repo DIR` (and its main checkout) when given, then the install dirs.
//     Nothing else: no upward search from the executable or the working directory (the user,
//     2026-10-07): a package unzipped inside a checkout must behave as anywhere else, e.g. start a
//     fresh account instead of seeding from the checkout's data/saves/seed/Game.xml. (An unknown
//     executable path leaves the list empty; find_repo_file then looks relative to the working
//     directory, as for any program without roots.)
//
// kReleasePackage is SOA_RELEASE_PACKAGE, which the root CMakeLists.txt defines for a Release
// configure (only scripts/build.sh --release makes one); not NDEBUG.
#ifdef SOA_RELEASE_PACKAGE
inline constexpr bool kReleasePackage = true;
#else
inline constexpr bool kReleasePackage = false;
#endif

// `p` absolute with symlinks resolved, '/'-separated; "" when it doesn't exist.
inline std::string canonical_path(const std::string& p) {
    if (p.empty()) return "";
    std::error_code ec;
    std::filesystem::path c = std::filesystem::canonical(std::filesystem::path(p), ec);
    if (ec) return "";
    std::string s = c.generic_string();
    std::replace(s.begin(), s.end(), '\\', '/');
    return s;
}

// The folder holding `p` ('/'-separated), "" at the top.
inline std::string parent_dir(const std::string& p) {
    size_t s = p.find_last_of('/');
    if (s == std::string::npos) return "";
    return s == 0 ? "/" : p.substr(0, s);
}

// Is `dir` a checkout? (The rule's tests pass their own.)
using CheckoutTest = std::function<bool(const std::string& dir)>;

// Is `dir` a source checkout of this repository? One marker for every program: the root
// CMakeLists.txt and common/'s, the parts every program is built from. (Shell: scripts/lib/checkout.sh;
// Python: soa_save.paths.main_checkout.)
inline bool is_checkout(const std::string& dir) {
    return is_file(dir + "/CMakeLists.txt") && is_file(dir + "/common/CMakeLists.txt");
}

// The first directory from `dir` upwards that is a checkout, "" when none.
inline std::string checkout_upwards(std::string dir, const CheckoutTest& is_checkout) {
    while (!dir.empty()) {
        if (is_checkout(dir)) return dir;
        std::string up = parent_dir(dir);
        if (up == dir) break;
        dir = up;
    }
    return "";
}

// The main checkout of a git worktree (.claude/worktrees/NAME) whose work/ is a symlink into it
// (it holds the untracked files: apk/, data/basmaster-3.7.0.sqlite3, ...); "" otherwise.
inline std::string main_checkout_of(const std::string& root, const CheckoutTest& is_checkout) {
    std::error_code ec;
    if (root.empty() || !std::filesystem::is_symlink(std::filesystem::path(root + "/work"), ec)) return "";
    std::string w = canonical_path(root + "/work");
    std::string m = w.empty() ? "" : parent_dir(w);
    return !m.empty() && m != root && is_checkout(m) ? m : "";
}

struct RepoRoots {
    std::string root;               // the checkout (absolute), "" when none
    std::string how;                // how it was found: "--repo", "the executable", "the working directory"
    std::string main_checkout;      // a worktree's main checkout (main_checkout_of), "" when none
    std::vector<std::string> all;   // the roots to search, in order
    std::string warning;            // "--repo DIR: not found" when the given dir doesn't exist
    bool release = false;           // found by the release rule

    // One line for the programs' logs.
    std::string describe() const {
        if (!root.empty())
            return "repo " + root + " (from " + how + ")" + (main_checkout.empty() ? "" : ", main checkout " + main_checkout);
        std::string dirs = all.empty() || all[0] == "." ? std::string("(nothing)") : all[0];
        if (all.size() > 1 && all[1] != ".") dirs += " and its " + std::string(kGameSubdir) + "/";
        if (release) return "release build: no source checkout is searched (only --repo DIR); data files are looked up in " + dirs;
        return "no source checkout: data files are looked up in " + dirs + ", then the working directory";
    }
};

// The rule itself, for given inputs (tests: common/tests/install_tests.cpp). `given` is --repo
// ("" when not given), `exe_dir` the executable's folder, `cwd` the working directory, `installs`
// install_dirs().
inline RepoRoots repo_roots_for(bool release, const std::string& given, const std::string& exe_dir, const std::string& cwd,
                                const std::vector<std::string>& installs, const CheckoutTest& is_checkout) {
    RepoRoots r;
    r.release = release;
    if (!given.empty()) {
        r.root = canonical_path(given);
        r.how = "--repo";
        if (r.root.empty()) r.warning = "--repo " + given + ": not found";
    }
    if (r.root.empty() && !release) {
        r.root = checkout_upwards(canonical_path(exe_dir), is_checkout);
        r.how = "the executable";
    }
    if (r.root.empty() && !release) {
        r.root = checkout_upwards(canonical_path(cwd), is_checkout);
        r.how = "the working directory";
    }
    if (r.root.empty()) r.how.clear();
    if (!r.root.empty()) {
        r.all.push_back(r.root);
        r.main_checkout = main_checkout_of(r.root, is_checkout);
        if (!r.main_checkout.empty()) r.all.push_back(r.main_checkout);
    }
    // then the install dirs: a packaged program's data files (data/gacha_pools.sqlite3,
    // data/saves/seed/Game.xml, standin-assets/) sit at their repo paths there; in a checkout's
    // build dir (build/port/, ...) there are none
    for (auto& d : installs)
        if (std::find(r.all.begin(), r.all.end(), d) == r.all.end()) r.all.push_back(d);
    // a development build without a checkout: the working directory last (as before)
    if (r.root.empty() && !release && !r.all.empty()) r.all.push_back(".");
    return r;
}

// This process's repo roots (kReleasePackage's rule).
inline RepoRoots repo_roots(const std::string& given, const CheckoutTest& checkout = is_checkout) {
    std::error_code ec;
    std::filesystem::path cwd = std::filesystem::current_path(ec);
    return repo_roots_for(kReleasePackage, given, exe_dir(), ec ? std::string() : cwd.generic_string(), install_dirs(), checkout);
}

// The first `rel` under one of `roots` (in order), "" when none has it.
inline std::string find_in_roots(const std::vector<std::string>& roots, const std::string& rel) {
    std::error_code ec;
    for (auto& r : roots)
        if (std::filesystem::exists(std::filesystem::path(r + "/" + rel), ec)) return r + "/" + rel;
    return "";
}

// The programs' repo-file lookup (their find_repo_file): the first of `rels` (in order) under one
// of `roots` (in order: all roots for a rel before the next rel); with no roots at all, `rel`
// itself, relative to the working directory. "" when none exists.
inline std::string find_file(const std::vector<std::string>& roots, std::initializer_list<const char*> rels) {
    std::error_code ec;
    for (const char* rel : rels) {
        if (roots.empty()) {
            if (std::filesystem::exists(std::filesystem::path(rel), ec)) return rel;
            continue;
        }
        if (std::string p = find_in_roots(roots, rel); !p.empty()) return p;
    }
    return "";
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

// The top-level files of `dirs` whose name ends in `ext` (any case), in lookup order (each dir's
// sorted). soa-viewer's XAPK lookup uses it with ".xapk" (emulator-viewer/src/main.cpp find_xapk).
inline std::vector<std::string> files_with_ext(const std::vector<std::string>& dirs, const char* ext) {
    std::vector<std::string> v;
    for (auto& d : dirs)
        for (auto& n : list_dir(d))
            if (ends_with_ci(n, ext) && is_file(d + "/" + n)) v.push_back(d + "/" + n);
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

// The first download tree among `dirs` themselves and their immediate subfolders (by name).
inline std::string find_download_dir(const std::vector<std::string>& dirs) {
    for (auto& d : dirs) {
        if (is_download_dir(d)) return d;
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
