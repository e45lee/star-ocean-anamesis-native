// soa-webview-render: renders a local HTML page with the web view's renderer (libsoawebview) into
// a PNG, the whole page or one view-sized screen of it. docs/webview.md "The render tool".
//
//   soa-webview-render PAGE OUT.png [--width W] [--height H] [--zoom Z] [--scroll Y] [--screen]
//                      [--url URL] [--map PREFIX=DIR]... [--tap X:Y]
//
//   PAGE        an HTML file ("-": stdin)
//   --width     the view's width in device pixels (default 1000)
//   --height    the view's height (default 1400); the PNG is the whole page's height unless --screen
//   --zoom      device pixels per CSS pixel (default 2.625: a 1080-wide 420 dpi phone); a page whose
//               viewport meta names a width overrides it (Android's wide-viewport mode)
//   --url       the page's URL (default: file://<PAGE's absolute path>), the base of its links
//   --map       serves URLs starting with PREFIX from DIR (e.g. http://soa-local.invalid/=webroot/);
//               file:// URLs are read from the disk
//   --scroll    with --screen: the scroll position (device pixels)
//   --tap X:Y   also prints the link a tap at view pixel X:Y hits
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
    std::string page, out, url;
    int width = 1000, height = 1400, scroll = 0, tap_x = -1, tap_y = -1;
    float zoom = 2.625f;
    bool screen = false;
    std::vector<std::pair<std::string, std::string>> maps;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        auto val = [&]() -> std::string {
            if (i + 1 >= argc) {
                fprintf(stderr, "%s: needs a value\n", a.c_str());
                exit(2);
            }
            return argv[++i];
        };
        if (a == "--width") width = atoi(val().c_str());
        else if (a == "--height") height = atoi(val().c_str());
        else if (a == "--zoom") zoom = (float)atof(val().c_str());
        else if (a == "--scroll") scroll = atoi(val().c_str());
        else if (a == "--screen") screen = true;
        else if (a == "--url") url = val();
        else if (a == "--map") {
            std::string m = val();
            size_t eq = m.find('=');
            if (eq == std::string::npos) return fprintf(stderr, "--map PREFIX=DIR\n"), 2;
            maps.emplace_back(m.substr(0, eq), m.substr(eq + 1));
        } else if (a == "--tap") {
            if (sscanf(val().c_str(), "%d:%d", &tap_x, &tap_y) != 2) return fprintf(stderr, "--tap X:Y\n"), 2;
        } else if (page.empty()) page = a;
        else if (out.empty()) out = a;
        else return fprintf(stderr, "unexpected argument %s\n", a.c_str()), 2;
    }
    if (page.empty() || out.empty()) {
        fprintf(stderr, "usage: soa-webview-render PAGE OUT.png [--width W] [--height H] [--zoom Z] [--scroll Y] [--screen] [--url URL] "
                        "[--map PREFIX=DIR]... [--tap X:Y]\n");
        return 2;
    }
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
    wp.load(html, url, width, height, zoom);
    int h = screen ? height : std::max(1, std::min(wp.content_height(), 30000));
    std::vector<uint8_t> px((size_t)width * h * 4);
    wp.draw(px.data(), width, h, screen ? scroll : 0, true);
    printf("%s: %dx%d device px, zoom %.3f, content %d px tall, \"%s\"\n", page.c_str(), width, h, wp.zoom(), wp.content_height(), wp.title().c_str());
    if (tap_x >= 0) printf("tap %d:%d -> \"%s\"\n", tap_x, tap_y, wp.tap(tap_x, tap_y, screen ? scroll : 0).c_str());
    return stbi_write_png(out.c_str(), width, h, 4, px.data(), width * 4) ? 0 : 1;
}
