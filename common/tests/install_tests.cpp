// The install-dir lookup of common/include/soa/install.h (part of soa_env_tests): the download tree
// and APK candidates on a scratch tree, the APK choice with a stand-in zip probe, the executable's
// folder.
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

#include <soa/install.h>

namespace {
int g_failures = 0;
void check(bool ok, const std::string& what) {
    fprintf(stderr, "%s  %s\n", ok ? "ok  " : "FAIL", what.c_str());
    if (!ok) g_failures++;
}
void touch(const std::filesystem::path& p) {
    std::filesystem::create_directories(p.parent_path());
    std::ofstream(p) << "x";
}
}  // namespace

int install_tests() {
    namespace fs = std::filesystem;
    using namespace soa::install;
    fs::path root = fs::temp_directory_path() / ("soa-install-test-" + std::to_string(rand()));
    std::string r = root.generic_string();
    fs::create_directories(root / "game");
    check(find_download_dir({r, r + "/game"}).empty(), "no download tree: none found");
    // a tree: version.bin + manifest/ + sqlite/basmaster.sqlite3, in a subfolder of game/ named anything
    touch(root / "game/my-data/version.bin");
    touch(root / "game/my-data/sqlite/basmaster.sqlite3");
    check(find_download_dir({r, r + "/game"}).empty(), "no manifest/: not a download tree");
    fs::create_directories(root / "game/my-data/manifest");
    check(is_download_dir(r + "/game/my-data"), "version.bin + manifest/ + sqlite/basmaster.sqlite3: a download tree");
    check(find_download_dir({r, r + "/game"}) == r + "/game/my-data", "found in a subfolder of game/, any name");
    // a tree beside the program wins (the program's folder is searched first)
    touch(root / "beside/version.bin");
    touch(root / "beside/sqlite/basmaster.sqlite3");
    fs::create_directories(root / "beside/manifest");
    check(find_download_dir({r, r + "/game"}) == r + "/beside", "the program's folder first");
    // the tree extracted straight into game/ (the canonical zip's layout: no top folder)
    fs::remove_all(root / "beside");
    // (rename, not fs::rename: on Windows `rename` is posix_compat.h's, which std::filesystem's can't share a name with)
    auto mv = [](const fs::path& a, const fs::path& b) { check(rename(a.string().c_str(), b.string().c_str()) == 0, "rename " + a.string()); };
    mv(root / "game/my-data", root / "g2");
    for (auto& e : fs::directory_iterator(root / "g2")) mv(e.path(), root / "game" / e.path().filename());
    check(find_download_dir({r, r + "/game"}) == r + "/game", "the tree extracted into game/ itself");
    // APKs: top level only, the canonical name first in each dir; the probe decides
    touch(root / "game/a-other.apk");
    touch(root / "game" / kApk370Name);
    touch(root / "game/Character/cp0202_b07a.apk");  // a download bundle: never looked at
    touch(root / "z.APK");
    auto c = apk_candidates({r, r + "/game"});
    check(c.size() == 3 && c[0] == r + "/z.APK" && c[1] == r + "/game/" + kApk370Name && c[2] == r + "/game/a-other.apk",
          "apk_candidates: top level, program folder first, canonical name first, any case");
    std::vector<std::string> notes;
    auto probe = [&](const std::string& p) -> int64_t {
        if (p == r + "/z.APK") return -1;                      // not the game's
        if (p == r + "/game/" + kApk370Name) return 12345;      // another version
        return (int64_t)kLib370Size;                            // a-other.apk: 3.7.0 under any name
    };
    check(find_apk_370({r, r + "/game"}, probe, &notes) == r + "/game/a-other.apk", "find_apk_370: the 3.7.0 one, whatever its name");
    check(notes.size() == 2, "find_apk_370: the two others noted");
    check(find_apk_370({r + "/nowhere"}, probe).empty(), "find_apk_370: nothing");
    // the executable
    std::string exe = exe_path(), dir = exe_dir();
    check(!exe.empty() && is_file(exe), "exe_path: this test's executable");
    check(!dir.empty() && exe.rfind(dir + "/", 0) == 0 && exe.find('\\') == std::string::npos, "exe_dir: its folder, '/' separators");
    check(missing_hint().find(dir + "/game") != std::string::npos, "missing_hint names DIR/game");
    fs::remove_all(root);
    return g_failures;
}

namespace {
using Roots = std::vector<std::string>;
std::string show(const Roots& v) {
    std::string s;
    for (auto& e : v) s += (s.empty() ? "" : ", ") + e;
    return "[" + s + "]";
}
void check_roots(const soa::install::RepoRoots& got, const Roots& want, const std::string& what) {
    check(got.all == want, what + ": " + show(got.all) + (got.all == want ? "" : " (want " + show(want) + ")"));
}
}  // namespace

// The repo roots (soa/install.h repo_roots_for): the release rule against the development one on a
// scratch tree. Both rules are run whatever this binary was built as (soa_env_tests is in build/ and
// build-release/ alike).
int repo_roots_tests() {
    const int failures_before = g_failures;
    namespace fs = std::filesystem;
    using namespace soa::install;
    fs::path base = fs::temp_directory_path() / ("soa-roots-test-" + std::to_string(rand()));
    fs::create_directories(base);
    const std::string t = canonical_path(base.string());
    // a checkout holding an unzipped package (work/pkg: soa, game/), a package outside any checkout
    touch(base / "checkout/port/CMakeLists.txt");
    fs::create_directories(base / "checkout/work/pkg/game");
    fs::create_directories(base / "outside/pkg/game");
    const std::string co = t + "/checkout", in_pkg = co + "/work/pkg", out_pkg = t + "/outside/pkg";
    const Roots in_dirs = {in_pkg, in_pkg + "/game"}, out_dirs = {out_pkg, out_pkg + "/game"};
    auto is_co = [](const std::string& d) { return is_file(d + "/port/CMakeLists.txt"); };

    // development: a checkout around the executable or the working directory is the repo
    RepoRoots r = repo_roots_for(false, "", in_pkg, out_pkg, in_dirs, is_co);
    check(r.root == co && r.how == "the executable", "dev: the checkout upwards from the executable");
    check_roots(r, {co, in_pkg, in_pkg + "/game"}, "dev, package inside a checkout");
    r = repo_roots_for(false, "", out_pkg, co + "/work", out_dirs, is_co);
    check(r.root == co && r.how == "the working directory", "dev: else upwards from the working directory");
    check_roots(r, {co, out_pkg, out_pkg + "/game"}, "dev, run from inside a checkout");
    r = repo_roots_for(false, "", out_pkg, out_pkg, out_dirs, is_co);
    check(r.root.empty(), "dev: no checkout anywhere");
    check_roots(r, {out_pkg, out_pkg + "/game", "."}, "dev, no checkout: install dirs, then the working directory");

    // release: never a checkout around it, only the install dirs
    r = repo_roots_for(true, "", in_pkg, co, in_dirs, is_co);
    check(r.root.empty() && r.how.empty(), "release: a checkout around the executable and the working directory is not the repo");
    check_roots(r, in_dirs, "release, package inside a checkout: the install dirs only");
    check(r.describe().find("release build") == 0 && r.describe().find(in_pkg + " and its game/") != std::string::npos,
          "release: the log line names the install dir: " + r.describe());
    r = repo_roots_for(true, "", out_pkg, co + "/work", out_dirs, is_co);
    check_roots(r, out_dirs, "release, run from inside a checkout: the install dirs only");
    r = repo_roots_for(true, "", out_pkg, out_pkg, {out_pkg}, is_co);
    check_roots(r, {out_pkg}, "release, no game/: the executable's folder only (no working directory)");

    // --repo DIR: honoured by both
    for (bool release : {false, true}) {
        const std::string tag = release ? "release" : "dev";
        r = repo_roots_for(release, co + "/work/..", out_pkg, out_pkg, out_dirs, is_co);
        check(r.root == co && r.how == "--repo", tag + ": --repo DIR (canonical)");
        check_roots(r, {co, out_pkg, out_pkg + "/game"}, tag + ", --repo: it, then the install dirs");
        r = repo_roots_for(release, t + "/missing", in_pkg, in_pkg, in_dirs, is_co);
        check(!r.warning.empty(), tag + ": --repo DIR missing: a warning");
        check_roots(r, release ? in_dirs : Roots{co, in_pkg, in_pkg + "/game"},
                    tag + ", --repo missing: " + (release ? "the install dirs only" : "the upward search as before"));
    }

    // a git worktree whose work/ links into the main checkout: that checkout too (with --repo in a
    // release build); needs symlinks (Windows without the privilege: skipped)
    touch(base / "main/port/CMakeLists.txt");
    fs::create_directories(base / "main/work");
    touch(base / "wt/port/CMakeLists.txt");
    std::error_code ec;
    fs::create_directory_symlink(base / "main/work", base / "wt/work", ec);
    if (!ec) {
        const std::string wt = t + "/wt", mn = t + "/main";
        r = repo_roots_for(false, "", wt + "/work", wt, {}, is_co);
        check(r.root == mn, "dev: upwards from inside the work/ link finds the main checkout itself: " + r.root);
        r = repo_roots_for(false, "", out_pkg, wt, out_dirs, is_co);
        check(r.main_checkout == mn, "dev: a worktree's main checkout");
        check_roots(r, {wt, mn, out_pkg, out_pkg + "/game"}, "dev, a worktree");
        r = repo_roots_for(true, wt, out_pkg, out_pkg, out_dirs, is_co);
        check_roots(r, {wt, mn, out_pkg, out_pkg + "/game"}, "release, --repo WORKTREE: its main checkout too");
        r = repo_roots_for(true, "", out_pkg, wt, out_dirs, is_co);
        check_roots(r, out_dirs, "release, run from a worktree: the install dirs only");
    } else {
        fprintf(stderr, "skip  the worktree cases (no symlink: %s)\n", ec.message().c_str());
    }
    // this process: the rule kReleasePackage picks
    r = repo_roots("", is_co);
    check(r.release == kReleasePackage, std::string("repo_roots: this build's rule (") + (kReleasePackage ? "release" : "development") + ")");
    fs::remove_all(base, ec);
    return g_failures - failures_before;
}
