#pragma once
// The programs' default data directories (soa, soa-emu, soa-viewer; `--data DIR` overrides them).
// Header-only, beside soa/env.h (target soa_env, common/CMakeLists.txt).
//
//   Linux:   $HOME/.local/share/<linux_name>        (HOME unset: ./.local/share/<linux_name>)
//   Windows: %LOCALAPPDATA%\soa\<windows_name>      (LOCALAPPDATA unset: %USERPROFILE%\AppData\Local;
//                                                    neither: .\soa\<windows_name>)
// Windows has no HOME as a rule, so the Linux spelling put the saves under the launch directory
// (<launch dir>\.local\share\...). No migration: README.md "Windows" says how to move such a dir.
#include <cstdlib>
#include <string>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#endif

namespace soa {

// The rule itself, for both platforms (tests: common/tests/paths_tests.cpp).
inline std::string default_data_dir_for(bool windows, const char* home, const char* localappdata, const char* userprofile,
                                        const char* linux_name, const char* windows_name) {
    if (!windows) return std::string(home && *home ? home : ".") + "/.local/share/" + linux_name;
    std::string base;
    if (localappdata && *localappdata) base = localappdata;
    else if (userprofile && *userprofile) base = std::string(userprofile) + "\\AppData\\Local";
    else base = ".";
    while (base.size() > 1 && (base.back() == '\\' || base.back() == '/')) base.pop_back();
    return base + "\\soa\\" + windows_name;
}

// This platform's default data dir (it isn't created: make_dir_tree once `--data` is known).
inline std::string default_data_dir(const char* linux_name, const char* windows_name) {
#ifdef _WIN32
    return default_data_dir_for(true, nullptr, getenv("LOCALAPPDATA"), getenv("USERPROFILE"), linux_name, windows_name);
#else
    return default_data_dir_for(false, getenv("HOME"), nullptr, nullptr, linux_name, windows_name);
#endif
}

// mkdir -p (either separator on Windows; not the runtime's vfs make_dirs, whose programs link this too). False when the directory isn't there afterwards.
inline bool make_dir_tree(const std::string& path) {
#ifdef _WIN32
    auto sep = [](char c) { return c == '/' || c == '\\'; };
#else
    auto sep = [](char c) { return c == '/'; };
#endif
    for (size_t i = 1; i <= path.size(); i++) {
        if (i < path.size() && !sep(path[i])) continue;
        std::string p = path.substr(0, i);
        if (p.size() == 2 && p[1] == ':') continue;  // a drive ("C:")
#ifdef _WIN32
        _mkdir(p.c_str());  // (EEXIST for the existing ones)
#else
        mkdir(p.c_str(), 0755);
#endif
    }
    struct stat st;
    return stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

}  // namespace soa
