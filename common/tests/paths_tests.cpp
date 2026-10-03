// The default data directories of common/include/soa/paths.h, both platforms' rules on either host
// (part of soa_env_tests).
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include <soa/paths.h>

namespace {
int g_failures = 0;
void check(bool ok, const std::string& what) {
    fprintf(stderr, "%s  %s\n", ok ? "ok  " : "FAIL", what.c_str());
    if (!ok) g_failures++;
}
}  // namespace

int paths_tests() {
    using soa::default_data_dir_for;
    check(default_data_dir_for(false, "/home/u", nullptr, nullptr, "soa-linux-370", "port-370") == "/home/u/.local/share/soa-linux-370",
          "Linux: $HOME/.local/share/NAME");
    check(default_data_dir_for(false, nullptr, "C:\\x", nullptr, "soa-viewer-380", "viewer-380") == "./.local/share/soa-viewer-380",
          "Linux: HOME unset -> ./.local/share (LOCALAPPDATA ignored)");
    check(default_data_dir_for(true, "/home/u", "C:\\Users\\u\\AppData\\Local", nullptr, "soa-linux-370", "port-370") ==
              "C:\\Users\\u\\AppData\\Local\\soa\\port-370",
          "Windows: %LOCALAPPDATA%\\soa\\NAME (HOME ignored)");
    check(default_data_dir_for(true, nullptr, "C:\\L\\", nullptr, "a", "emulator-370\\phone") == "C:\\L\\soa\\emulator-370\\phone",
          "Windows: a trailing separator dropped");
    check(default_data_dir_for(true, nullptr, "", "C:\\Users\\u", "a", "viewer-380") == "C:\\Users\\u\\AppData\\Local\\soa\\viewer-380",
          "Windows: LOCALAPPDATA unset -> %USERPROFILE%\\AppData\\Local");
    check(default_data_dir_for(true, nullptr, nullptr, nullptr, "a", "viewer-380") == ".\\soa\\viewer-380", "Windows: neither -> .");
#ifdef _WIN32
    _putenv_s("LOCALAPPDATA", "C:\\soa-paths-test");
    check(soa::default_data_dir("x", "port-370") == "C:\\soa-paths-test\\soa\\port-370", "this host: LOCALAPPDATA");
#else
    setenv("HOME", "/soa-paths-test", 1);
    check(soa::default_data_dir("soa-linux-370", "x") == "/soa-paths-test/.local/share/soa-linux-370", "this host: HOME");
#endif
    // make_dir_tree: parents created, an existing dir fine
    std::string base = std::string(getenv("TMPDIR") && *getenv("TMPDIR") ? getenv("TMPDIR") : "/tmp") + "/soa-paths-test-" +
                       std::to_string((long long)time(nullptr));
#ifdef _WIN32
    if (getenv("TEMP")) base = std::string(getenv("TEMP")) + "\\soa-paths-test-" + std::to_string((long long)time(nullptr));
    std::string deep = base + "\\a/b\\c";
#else
    std::string deep = base + "/a/b/c";
#endif
    check(soa::make_dir_tree(deep), "make_dir_tree: a new tree");
    check(soa::make_dir_tree(deep), "make_dir_tree: again (exists)");
    struct stat st;
    check(stat(deep.c_str(), &st) == 0 && S_ISDIR(st.st_mode), "make_dir_tree: the dir is there");
    for (std::string d : {deep, base + "/a/b", base + "/a", base}) rmdir(d.c_str());
    return g_failures;
}
