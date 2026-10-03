// Local web pages in the game's web-view popups (--server inproc; client change, docs/client-changes.md
// "Notice board page"). Port code, not a transcription.
//
// CWebView::OpenView(type, on_close, bool) lays out the popup (layout dialog4), asks
// WebViewUtility::GetWebInfo for the page's URL and calls BAS::WebView(url, x, y, w, h, ...),
// which on Android overlays a native WebView on the popup's page area (window/Panel_1). The
// desktop has no web view, so SOAActivity.ShowWebView (overridden below) asks open_local()
// whether the local server hosts the URL (server::web_page); if so, the hook below puts the
// page's text into the page area as a label, cloned from the popup's own "今日は表示しない"
// label (window/box/Text), so it is drawn with the game's font. The label belongs to the layout
// and goes away with the popup.
#include "native/ui/webview_local.h"

#include <cstring>
#include <string>

#include "core/cpu.h"
#include "core/log.h"
#include "core/options.h"
#include "jni/jvm.h"
#include "native/common/guest_std.h"
#include "native/common/native.h"
#include "soaserver/server.h"

namespace soa::webview {
namespace {

bool g_in_open = false;    // inside CWebView::OpenView
bool g_have_page = false;  // ShowWebView asked for a local page during it
std::string g_page;

bool on() { return options().server.enabled; }

u64 S(const char* s) { return guest::sym(s); }

// CCocosNode::SearchByTreeName(const std::string&) (guest code).
u64 search_by_tree_name(u64 root, const char* path) {
    static u64 fn = S("_ZN9Framework5Cocos10CCocosNode16SearchByTreeNameERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE");
    guest::String s;
    s.init(path);
    u64 r = guest_call(fn, {root, (u64)&s});
    s.destroy();
    return r;
}

// The page area's label: a clone of window/box/Text in window/Panel_1, anchored top-left.
void show_page(u64 view, const std::string& text) {
    u64 vt = *(u64*)view;
    u64 root = guest_call(*(u64*)(vt + 0x58), {view});  // the popup's layout node (as OpenView gets it)
    if (!root) return;
    u64 src = search_by_tree_name(root, "window/box/Text");
    u64 panel = search_by_tree_name(root, "window/Panel_1");
    if (!src || !panel) {
        LOGW("webview", "local page: the popup has no %s", src ? "window/Panel_1" : "window/box/Text");
        return;
    }
    u64 label = guest_call(*(u64*)(*(u64*)src + 0x28), {src, 0});  // CCocosLabel::Clone(nullptr)
    if (!label) return;
    // The page area's top-left, 24 units in, in world coordinates (as OpenView measures the web
    // view's rect: the panel's world position is its centre, its size = layout size x scale).
    // World y grows downwards here (SetWorldPosition), and the label's anchor (0, 0) puts its first
    // row's top-left there (found on screen: anchor y 1 aligned the block's last row instead).
    static u64 world_pos = S("_ZNK9Framework5Cocos10CCocosNode16GetWorldPositionEb");
    static u64 layout_size = S("_ZNK9Framework5Cocos10CCocosNode13GetLayoutSizeEv");
    static u64 set_world = S("_ZN9Framework5Cocos10CCocosNode16SetWorldPositionERKNS_8CVector2E");
    const float* wp = (const float*)(u64)guest_call(world_pos, {panel, 1});
    const float* ls = (const float*)(u64)guest_call(layout_size, {panel});
    if (!wp || !ls) return;
    float cx = wp[0], cy = wp[1], w = ls[0] * *(float*)(panel + 0x9c), h = ls[1] * *(float*)(panel + 0xa0);
    float* anchor = (float*)(label + 0x84);
    anchor[0] = 0.0f;
    anchor[1] = 0.0f;
    alignas(8) float at[2] = {cx - w * 0.5f + 24.0f, cy - h * 0.5f + 24.0f};
    static u64 set_text = S("_ZN9Framework5Cocos11CCocosLabel7SetTextERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE");
    guest::String s;
    s.init(text);
    guest_call(set_text, {label, (u64)&s});
    s.destroy();
    static u64 add_child = S("_ZN9Framework5Cocos10CCocosNode8AddChildEPS1_");
    guest_call(add_child, {panel, label});
    guest_call(set_world, {label, (u64)at});
    LOGI("webview", "local page shown (%zu bytes; page area %.0fx%.0f at %.0f,%.0f)", text.size(), w, h, cx, cy);
}

u64 g_orig_open = 0;
void h_open_view(Cpu& c) {
    u64 view = c.x(0);
    g_in_open = true;
    g_have_page = false;
    GuestArgs a;
    a.ints = {c.x(0), c.x(1), c.x(2), c.x(3)};
    guest_call(g_orig_open, a);
    g_in_open = false;
    if (g_have_page) show_page(view, g_page);
    g_have_page = false;
}
NATIVE_FUNCTION_ORIG_IF("_ZN8CWebView8OpenViewENS_8ViewTypeENSt6__ndk18functionIFvvEEEb", h_open_view,
                        "CWebView::OpenView (in-process server: local pages as text)", &on, &g_orig_open);

}  // namespace

bool open_local(const std::string& url) {
    if (!on() || !g_in_open) return false;
    std::string text;
    if (!server::web_page(url, &text)) return false;
    g_page = text;
    g_have_page = true;
    return true;
}

// SOAActivity.ShowWebView (runtime/src/jni/java_android.cpp, which logs "not supported") asks
// open_local() first (a runtime JVM override: jni::add_class_installer).
static bool g_show_webview_override = jni::add_class_installer([](jni::Vm& vm) {
    vm.override_method("com/square_enix/android_googleplay/StarOceanj/SOAActivity", "ShowWebView", "(Ljava/lang/String;IIIIZLjava/lang/String;ZIII)V",
                       [](jni::Object* self, const jni::Args& a, const jni::Impl& original) -> u64 {
                           // the web view prototype (SOA_WEBVIEW=1): the page as HTML over the game
                           if (page_view_enabled()) {
                               LOGI("java", "ShowWebView(%s, %d, %d, %d, %d, useBrowser %d, post %zu bytes, editable %d, close %dx%d, %d)",
                                    jni::jstr(a[0]).c_str(), (int)(s32)a[1], (int)(s32)a[2], (int)(s32)a[3], (int)(s32)a[4], (int)(a[5] & 1),
                                    jni::jstr(a[6]).size(), (int)(a[7] & 1), (int)(s32)a[8], (int)(s32)a[9], (int)(s32)a[10]);
                               if (page_view_show(jni::jstr(a[0]), (s32)a[1], (s32)a[2], (s32)a[3], (s32)a[4])) return 0;
                           }
                           // in-process: a page the local server hosts is shown as text in the popup
                           if (open_local(jni::jstr(a[0]))) {
                               LOGI("java", "ShowWebView(%s): local page", jni::jstr(a[0]).c_str());
                               return 0;
                           }
                           return original ? original(self, a) : 0;
                       });
});

}  // namespace soa::webview
