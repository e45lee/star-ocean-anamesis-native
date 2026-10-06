#pragma once
// soa-webview-render's command line (cli.cpp; the shared rules: common/include/soa/cli.h).
// render.cpp acts on the result.
#include <string>
#include <utility>
#include <vector>

namespace soa::webview {

struct RenderArgs {
    std::string page, out;  // PAGE ("-": stdin), OUT.png
    std::string url;        // --url (empty: file://<PAGE's absolute path>, render.cpp)
    int width = 1000, height = 1400, scroll = 0, tap_x = -1, tap_y = -1;
    float zoom = 2.625f;
    bool screen = false;
    std::vector<std::pair<std::string, std::string>> maps;  // --map PREFIX=DIR, in order
};

// -1: go on; else the exit status (0 after --help, 2 after an error, which it printed). `names`:
// every option name it defines (tests/cli).
int parse_render_args(int argc, const char* const* argv, RenderArgs& a, std::vector<std::string>* names = nullptr);

}  // namespace soa::webview
