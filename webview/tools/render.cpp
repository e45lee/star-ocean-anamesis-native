// soa-webview-render: renders a local HTML page with the web view's renderer (libsoawebview) into
// a PNG, the whole page or one view-sized screen of it. docs/webview.md "The render tool".
//
//   soa-webview-render PAGE OUT.png [--width W] [--height H] [--zoom Z] [--scroll Y] [--screen]
//                      [--url URL] [--map PREFIX=DIR]... [--tap X:Y]   (-h / --help: the options)
//
// The options and their defaults: cli.cpp (CLI11; --help lists them).
// Environment: SOA_WEBVIEW_DUMP_CSS=FILE appends each stylesheet as litehtml gets it (docs/webview.md).
#include <unistd.h>

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include <soa/env.h>

#include "cli.h"
#include "soawebview/page.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_STATIC
#include <stb_image_write.h>

namespace {

bool read_file(const std::string& path, std::string& out) {
    FILE* f = path == "-" ? stdin : fopen(path.c_str(), "rb");
    if (!f) return false;
    char buf[65536];
    for (size_t n; (n = fread(buf, 1, sizeof buf, f)) > 0;) out.append(buf, n);
    if (f != stdin) fclose(f);
    return true;
}

std::string url_path(std::string u) {  // the path part, %XX decoded, without ?query / #fragment
    size_t q = u.find_first_of("?#");
    if (q != std::string::npos) u.resize(q);
    std::string out;
    for (size_t i = 0; i < u.size(); i++) {
        if (u[i] == '%' && i + 2 < u.size()) {
            out += (char)strtol(u.substr(i + 1, 2).c_str(), nullptr, 16);
            i += 2;
        } else out += u[i];
    }
    return out;
}

}  // namespace

int main(int argc, char** argv) {
    soa::env::warn_removed_env("soa-webview-render", soa::env::kRender);
    soa::webview::RenderArgs args;
    if (int rc = soa::webview::parse_render_args(argc, argv, args); rc >= 0) return rc;
    const std::string& page = args.page;
    std::string url = args.url;
    const int width = args.width, height = args.height, scroll = args.scroll, tap_x = args.tap_x, tap_y = args.tap_y;
    const bool screen = args.screen;
    const auto& maps = args.maps;
    std::string html;
    if (!read_file(page, html)) return fprintf(stderr, "%s: can't read\n", page.c_str()), 1;
    if (url.empty() && page != "-") {
        char abs[PATH_MAX];
        url = std::string("file://") + (realpath(page.c_str(), abs) ? abs : page.c_str());
    }
    soa::webview::set_log([](int level, const std::string& msg) { fprintf(stderr, "[webview] %s\n", msg.c_str()); });
    soa::webview::WebPage wp([&maps](const std::string& u) {
        soa::webview::FetchResult r;
        std::string path;
        if (u.rfind("file://", 0) == 0) path = url_path(u.substr(7));
        for (auto& [prefix, dir] : maps)
            if (u.rfind(prefix, 0) == 0) path = dir + "/" + url_path(u.substr(prefix.size()));
        if (path.empty()) {
            r.error = "no local file for this URL (--map)";
            return r;
        }
        if (read_file(path, r.body)) r.status = 200;
        else r.status = 404, r.error = path + ": not found";
        return r;
    });
    wp.load(html, url, width, height, args.zoom);
    int h = screen ? height : std::max(1, std::min(wp.content_height(), 30000));
    std::vector<uint8_t> px((size_t)width * h * 4);
    wp.draw(px.data(), width, h, screen ? scroll : 0, true);
    printf("%s: %dx%d device px, zoom %.3f, content %d px tall, \"%s\"\n", page.c_str(), width, h, wp.zoom(), wp.content_height(), wp.title().c_str());
    if (tap_x >= 0) printf("tap %d:%d -> \"%s\"\n", tap_x, tap_y, wp.tap(tap_x, tap_y, screen ? scroll : 0).c_str());
    return stbi_write_png(args.out.c_str(), width, h, 4, px.data(), width * 4) ? 0 : 1;
}
