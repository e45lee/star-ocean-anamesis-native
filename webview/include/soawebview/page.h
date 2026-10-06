#pragma once
// The web view's page renderer (docs/webview.md): an HTML document laid out by litehtml and drawn in
// software into an RGBA buffer. Text with stb_truetype from host fonts (a Japanese font first), images
// with stb_image (PNG, JPEG, GIF, BMP), stylesheets through a small CSS simplifier (simplify_css)
// that turns modern CSS litehtml lacks into what it knows. No JavaScript, no forms.
//
// Ported from the Dragalia Lost project's renderer (platformdl/src/webview_page.cpp, the same
// author); the changes for this game: Japanese line breaking (split_text: a break opportunity at
// every kana / ideograph / full-width character, with the basic kinsoku rules), the Android
// WebView's wide-viewport mode (a page's <meta name="viewport" content="width=N"> lays it out N CSS
// pixels wide, scaled to the view), Japanese fonts first, no WebP.
//
// A library of its own (libsoawebview): no runtime, JNI or GL dependency, so the runtime's overlay,
// the server's tests and the offline tool (soa-webview-render) can all use it. Not thread-safe: one
// thread uses a WebPage.
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace soa::webview {

// A GET of a page's resources (stylesheets, images): status (0 = network error) and body.
struct FetchResult {
    long status = 0;
    std::string body;
    std::string error;
};
using Fetch = std::function<FetchResult(const std::string& url)>;

// Log lines (level: 0 debug, 1 info, 2 warning, 3 error). Default: warnings and errors to stderr.
void set_log(std::function<void(int level, const std::string& msg)> log);

class WebPage {
public:
    explicit WebPage(Fetch fetch);
    ~WebPage();
    // Parses `html` (its URL `url`: the base of relative links), fetches its stylesheets and images,
    // and lays it out `width` device pixels wide; `zoom` device pixels per CSS pixel (the phone's
    // density, scaled to the view), unless the page's viewport meta names a width (wide-viewport
    // mode: the page is then laid out that many CSS pixels wide, zoom = width / N); `height` is the
    // view's (for vh units and the media queries).
    void load(const std::string& html, const std::string& url, int width, int height, float zoom);
    // Lays the loaded document out again for a new view size.
    void resize(int width, int height);
    bool loaded() const;
    int content_height() const;  // device pixels
    float zoom() const;          // device pixels per CSS pixel, as laid out
    std::string title() const;
    // Draws the view: `w` x `h` RGBA (top-down rows, straight alpha), the document scrolled down
    // `scroll_y` device pixels. `opaque`: on white (else on transparent).
    void draw(uint8_t* rgba, int w, int h, int scroll_y, bool opaque);
    // A tap at view pixel (x, y) with the document scrolled `scroll_y`: the URL of the link it hit
    // (resolved against the document's), or "".
    std::string tap(int x, int y, int scroll_y);

private:
    struct Impl;
    std::unique_ptr<Impl> d_;
};

// Rewrites a stylesheet into the CSS that litehtml 0.10 applies (css_simplify.cpp).
std::string simplify_css(const std::string& css);
// Resolves `ref` against `base` (RFC 3986, as a browser does for href/src).
std::string resolve_url(const std::string& base, const std::string& ref);
// The width a page's <meta name="viewport"> names in CSS pixels ("width=640"), or 0 (none, or
// device-width).
int viewport_width(const std::string& html);

// Japanese line breaking (split_text): calls on_word for each unbreakable run and on_space for each
// white-space character, as litehtml's document_container::split_text does, with a break
// opportunity between CJK characters too. Exposed for the tests.
void split_text_ja(const char* text, const std::function<void(const char*)>& on_word, const std::function<void(const char*)>& on_space);

}  // namespace soa::webview
