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
    // download-3.7.0 beside the program wins (the program's folder is searched first)
    touch(root / "download-3.7.0/version.bin");
    touch(root / "download-3.7.0/sqlite/basmaster.sqlite3");
    fs::create_directories(root / "download-3.7.0/manifest");
    check(find_download_dir({r, r + "/game"}) == r + "/download-3.7.0", "the program's folder first");
    // the tree extracted straight into game/ (the canonical zip's layout: no top folder)
    fs::remove_all(root / "download-3.7.0");
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
