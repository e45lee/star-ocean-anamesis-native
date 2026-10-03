// The web view (docs/webview.md; on by default): SOAActivity.ShowWebView
// shows a page the local server hosts as HTML, laid out and drawn by libsoawebview (litehtml, the
// Dragalia Lost project's renderer) and put over the game by the host (app/page_overlay.h) at the
// rectangle the game asks for, as Android's WebView in a PopupWindow. Port code, platform side (the
// Java method, not game code): the 3.7.0 client's own CWebView popup, its 閉じる and its close call
// (ShowWebView(null)) are untouched.
//
// Behaviour (SOAActivity.ShowWebView, jadx; docs/webview.md "The Java side"):
//   ShowWebView(url, x, y, w, h, useBrowser, postData, isEditable, closeW, closeH, closeTotal):
//     url null (the game's close): the view goes; a url with a view already open: ignored (the
//     phone's `str != null && l == null && k == null`).
//   x, y, w, h: the view's rectangle in screen pixels (the game's screen here: platform().width x
//     height), the popup's page area (CWebView::OpenView).
//   Links: a page the local server hosts loads in the view; any other URL is logged (the phone opens
//     the browser for links off the page's root when useBrowser is set, SOAActivity.SetRootURI).
//   Input: a drag in the view scrolls it, a tap follows a link, the wheel scrolls.
// Not done (prototype): the isEditable mode (an AlertDialog with its own close button, used by the
// data-transfer and refund forms), POST bodies, IsShowingWebView, pages the server doesn't host.
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "android/platform.h"
#include "app/page_overlay.h"
#include "core/log.h"
#include "native/ui/webview_local.h"
#include "soaserver/server.h"
#include "soawebview/page.h"

namespace soa::webview {
namespace {

std::mutex g_m;
std::unique_ptr<WebPage> g_page;
int g_x = 0, g_y = 0, g_w = 0, g_h = 0;  // the view, game-screen pixels
int g_scroll = 0;
// the gesture in progress
float g_down_x = 0, g_down_y = 0;
int g_scroll0 = 0;
bool g_dragging = false;

// (d) A CSS pixel is the phone's density (2.625: a 420 dpi, 1080-wide phone) scaled to the game
// screen; a page with a viewport width (wide-viewport mode) overrides it (soawebview/page.h).
float device_zoom() {
    int W = platform().width.load();
    return 2.625f * (W > 0 ? W : 1080) / 1080.0f;
}

FetchResult fetch_local(const std::string& url) {
    FetchResult r;
    std::string type;
    if (server::web_document(url, &type, &r.body)) r.status = 200;
    else r.error = "not a page the local server hosts";
    return r;
}

// Draws the view at the current scroll and hands it to the host (g_m held).
void present() {
    if (!g_page) return;
    int max_scroll = std::max(0, g_page->content_height() - g_h);
    g_scroll = std::clamp(g_scroll, 0, max_scroll);
    std::vector<uint8_t> px((size_t)g_w * g_h * 4);
    g_page->draw(px.data(), g_w, g_h, g_scroll, true);
    app::page_overlay::show(g_x, g_y, g_w, g_h, g_w, g_h, std::move(px));
}

// Loads `url` into the view (g_m held): false when the local server doesn't host it.
bool load(const std::string& url) {
    std::string type, html;
    if (!server::web_document(url, &type, &html)) return false;
    if (!g_page) g_page = std::make_unique<WebPage>(fetch_local);
    g_page->load(html, url, g_w, g_h, device_zoom());
    g_scroll = 0;
    LOGI("webview", "page %s: %dx%d at %d,%d, zoom %.3f, %d px tall, \"%s\"", url.c_str(), g_w, g_h, g_x, g_y, g_page->zoom(),
         g_page->content_height(), g_page->title().c_str());
    present();
    return true;
}

void on_input(int kind, float x, float y, float dy) {
    std::lock_guard lk(g_m);
    if (!g_page) return;
    if (kind == 0) {
        g_down_x = x, g_down_y = y, g_scroll0 = g_scroll, g_dragging = false;
    } else if (kind == 2) {
        if (!g_dragging && std::hypot(x - g_down_x, y - g_down_y) > 8 * device_zoom()) g_dragging = true;
        if (g_dragging) {
            g_scroll = g_scroll0 - (int)std::lround(y - g_down_y);
            present();
        }
    } else if (kind == 1) {
        if (!g_dragging) {
            std::string link = g_page->tap((int)x, (int)y, g_scroll);
            if (!link.empty()) {
                LOGI("webview", "link %s", link.c_str());
                if (!load(link)) LOGI("webview", "link %s: not a local page (the phone opens the browser; not done here)", link.c_str());
            }
        }
        g_dragging = false;
    } else if (kind == 3) {
        g_scroll -= (int)std::lround(dy * 48 * device_zoom());
        present();
    }
}

}  // namespace

bool page_view_show(const std::string& url, int x, int y, int w, int h) {
    std::lock_guard lk(g_m);
    if (url.empty()) {
        if (!g_page) return false;  // not ours: the guest path (logged as before)
        LOGI("webview", "closed");
        g_page.reset();
        app::page_overlay::hide();
        return true;
    }
    if (g_page) {  // the phone ignores a second open while one is shown
        LOGI("webview", "ShowWebView(%s) while a view is open: ignored", url.c_str());
        return true;
    }
    if (w <= 0 || h <= 0) return false;
    g_x = x, g_y = y, g_w = w, g_h = h;
    app::page_overlay::set_input_handler(on_input);
    if (!load(url)) {
        g_page.reset();
        return false;
    }
    return true;
}

}  // namespace soa::webview
