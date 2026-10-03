#pragma once
// Local web pages in the game's web-view popups (--server inproc; webview_local.cpp). The desktop has no
// web view: SOAActivity.ShowWebView (jni/java_android.cpp) hands its URL here, and a page the
// local server hosts (server::web_page) is shown as text in the popup's page area instead.
#include <string>

namespace soa::webview {

// Called by SOAActivity.ShowWebView (overridden in webview_local.cpp): true when `url` is a page
// the local server hosts; its text is then shown in the CWebView being opened (the
// CWebView::OpenView hook).
bool open_local(const std::string& url);

// The web view prototype (webview_page_view.cpp; docs/webview.md): SOA_WEBVIEW=1.
bool page_view_enabled();
// ShowWebView's URL ("" = the close) and rectangle (game-screen pixels): true when the prototype
// handled it (a page the local server hosts as HTML, shown over the game; or the close of one).
bool page_view_show(const std::string& url, int x, int y, int w, int h);

}  // namespace soa::webview
