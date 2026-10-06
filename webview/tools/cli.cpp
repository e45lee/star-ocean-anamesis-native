// soa-webview-render's command line on CLI11 (cli.h; the shared rules: common/include/soa/cli.h).
// None of the shared option groups apply (no game files, checkout or log level).
#include "cli.h"

#include <climits>

#include <soa/cli.h>

namespace soa::webview {

int parse_render_args(int argc, const char* const* argv, RenderArgs& a, std::vector<std::string>* names) {
    CLI::App app{"Renders a local HTML page with the web view's renderer (libsoawebview) into a PNG, the whole page or one "
                 "view-sized screen of it. docs/webview.md \"The render tool\".",
                 "soa-webview-render"};
    cli::setup_app(app);
    app.add_option("PAGE", a.page, "the HTML file (\"-\": stdin)")->type_name("FILE")->required();
    app.add_option("OUT", a.out, "the PNG to write")->type_name("OUT.png")->required();
    const CLI::Validator positive = CLI::Range(1, INT_MAX).description("");
    app.add_option("--width", a.width, "the view's width in device pixels (default 1000)")->type_name("W")->check(positive);
    app.add_option("--height", a.height, "the view's height (default 1400); the PNG is the whole page's height unless --screen")
        ->type_name("H")
        ->check(positive);
    app.add_option("--zoom", a.zoom,
                   "device pixels per CSS pixel (default 2.625: a 1080-wide 420 dpi phone); a page whose viewport meta names a "
                   "width overrides it (Android's wide-viewport mode)")
        ->type_name("Z");
    app.add_flag("--screen", a.screen, "render one view-sized screen (--height tall) instead of the whole page");
    app.add_option("--scroll", a.scroll, "with --screen: the scroll position (device pixels)")->type_name("Y");
    app.add_option("--url", a.url, "the page's URL (default: file://<PAGE's absolute path>), the base of its links")->type_name("URL");
    app.add_option_function<std::vector<std::string>>(
           "--map",
           [&a](const std::vector<std::string>& v) {
               for (const std::string& m : v) {
                   size_t eq = m.find('=');
                   a.maps.emplace_back(m.substr(0, eq), m.substr(eq + 1));
               }
           },
           "serves URLs starting with PREFIX from DIR (e.g. http://soa-local.invalid/=webroot/; repeatable); file:// URLs "
           "are read from the disk")
        ->type_name("PREFIX=DIR")
        ->allow_extra_args(false)
        ->multi_option_policy(CLI::MultiOptionPolicy::TakeAll)
        ->check([](const std::string& m) { return m.find('=') == std::string::npos ? "expected PREFIX=DIR" : ""; });
    app.add_option_function<std::string>(
           "--tap",
           [&a](const std::string& v) {
               size_t c = v.find(':');
               long x = 0, y = 0;
               if (c == std::string::npos || !cli::parse_long_in(v.substr(0, c), INT_MIN, INT_MAX, &x) ||
                   !cli::parse_long_in(v.substr(c + 1), INT_MIN, INT_MAX, &y))
                   cli::bad_value("--tap", "expected X:Y, got \"" + v + "\"");
               a.tap_x = (int)x, a.tap_y = (int)y;
           },
           "also prints the link a tap at view pixel X:Y hits")
        ->type_name("X:Y");
    app.footer("Environment: SOA_WEBVIEW_DUMP_CSS=FILE appends each stylesheet as litehtml gets it (docs/webview.md).");
    cli::note_removed_env(app, env::kRender);

    if (names) *names = cli::option_names(app);
    return cli::parse(app, argc, argv);
}

}  // namespace soa::webview
