// The notice board's page (お知らせ; api/player/README.md). Port code, not guest behaviour; every
// rule carries its source label, (a) master data, (b) client-side evidence, (c) outside knowledge,
// (d) assumption. Rules in docs/server-rules.md "Notice board page".
//
// (b) The notice board (CNoticeBoard, the first popup 3.7.0's login arms; also the home side
// menu's お知らせ) opens CWebView::OpenView(1). Its URL comes from WebViewUtility::GetWebInfo(1),
// which looks the key "information" up in the server's `WebView` list (CWebViewInfo, an array of
// CWebViewInfoElement {key, value}, CParameterManager+0x6120) and falls back to other lists; the
// URL then goes to BAS::WebView -> SOAActivity.ShowWebView. 3.7.0's server sent the URL of its
// online notice pages (c), which are gone.
//
// So the server sends its own page's URL, kNoticeUrl (d), and hosts the page: web_page() answers
// it with plain text, which the port's stand-in for the Android web view shows in the popup
// (native/ui/webview_local.cpp, a client change). The page is built from the server
// state when it is opened: the event areas open now (events::open_areas, the same list the
// event menu shows), the login bonus's day and the present box.
#include <cstdio>
#include <ctime>
#include <string>

#include "core/log.h"
#include "core/time.h"
#include "soaserver/native_test.h"
#include "soaserver/events.h"
#include "soaserver/ext.h"
#include "core/modules.h"

namespace soa::server {
namespace {

using ext::Row;

// (d) The URL of the local notice page (no host serves it: web_page() answers it in process).
constexpr const char* kNoticeUrl = "http://soa-local.invalid/notice";
// (d) The page's width in columns (a full-width character counts 2): about 25 full-width
// characters per row at the label's size, measured on screen.
constexpr int kPageColumns = 48;
// (d) At most this many open event areas are listed by name; the rest are counted.
constexpr int kMaxListedAreas = 12;

// OnPlayerLoad: WebView                                   on Login, SimpleLogin, CreatePlayer, GetPlayer, NoLoginStart
// Rules: docs/server-rules.md "Notice board page"
//
//   (b) The notice board's URL is the value of key "information" in WebView (above).
//   (b) `WebView` is a state key (docs/api.md "Player state": not reset between responses), so the
//       full-state player responses carry it.
//   (d) The value is the local page's URL, kNoticeUrl.
// Adds: data.WebView = [{key: "information", value: kNoticeUrl}].
void load_notice(ext::Ctx&, const Request&, Value& data) {
    Value list = Value::array();
    Value entry = Value::object();
    entry["key"] = "information";
    entry["value"] = kNoticeUrl;
    list.push(entry);
    data["WebView"] = list;
}

// Breaks a line into rows of at most `width` columns (a full-width character counts 2), so the
// page fits the popup (kPageColumns).
std::string wrap(const std::string& line, int width) {
    std::string out, row;
    int cols = 0;
    for (size_t i = 0; i < line.size();) {
        unsigned char ch = (unsigned char)line[i];
        size_t n = ch < 0x80 ? 1 : ch < 0xe0 ? 2 : ch < 0xf0 ? 3 : 4;
        int w = n == 1 ? 1 : 2;
        if (cols + w > width) {
            out += row + "\n";
            row = "  ";
            cols = 2;
        }
        row.append(line, i, n);
        cols += w;
        i += n;
    }
    return out + row;
}

// A local time in a strftime format (the page's own formats, not the server's format_time).
std::string format_local(int64_t t, const char* fmt) {
    time_t tt = (time_t)t;
    struct tm tm;
    localtime_r(&tt, &tm);
    char b[64];
    strftime(b, sizeof b, fmt, &tm);
    return b;
}

// The page being built: wrapped lines.
struct Page {
    std::string text;
    void line(const std::string& s) { text += wrap(s, kPageColumns) + "\n"; }
};

// (a) The open event areas, named by master_event_area.name_message_id (notice_page, step 2).
void add_event_areas(ext::Ctx& ctx, int64_t now, int64_t event_now, Page& page) {
    auto areas = events::open_areas(ctx, now, event_now);
    page.line("■ 開催中のイベント (" + std::to_string(areas.size()) + ")");
    int shown = 0;
    for (const auto& area : areas) {
        if (shown == kMaxListedAreas) {
            page.line("  ほか " + std::to_string(areas.size() - shown) + " 件");
            break;
        }
        std::string name;
        ctx.m.q("select name_message_id from master_event_area where id = ?", {area.id},
                [&](const Row& area_row) { name = ext::text(ctx.m, area_row.s("name_message_id")); });
        page.line("・" + (name.empty() ? area.label : name));
        shown++;
    }
    if (areas.empty()) page.line("・なし");
}

// (a) The login bonuses running at the server clock with the day reached (api/daily/login_bonus.cpp's
// table) (notice_page, step 3).
void add_login_bonuses(ext::Ctx& ctx, int64_t now, Page& page) {
    page.line("■ ログインボーナス");
    int bonuses = 0;
    ctx.m.q("select id, name_message_id, opened_at, closed_at from master_login_bonus order by order_id", {}, [&](const Row& bonus_row) {
        if (!open_at(bonus_row.s("opened_at"), bonus_row.s("closed_at"), now)) return;
        int64_t day = ctx.st.one("select ifnull(max(day), 0) from login_bonus where id = ?", {bonus_row.i("id")});
        page.line("・" + ext::text(ctx.m, bonus_row.s("name_message_id")) + (day ? " " + std::to_string(day) + "日目" : ""));
        bonuses++;
    });
    if (!bonuses) page.line("・なし");
}

// The notice page's text: (d) what it lists is the server's choice.
std::string notice_page(ext::Ctx& ctx) {
    Page page;
    int64_t now = ctx.now(), event_now = ctx.event_now();
    // 1. the clocks
    page.line("【お知らせ】");
    page.line("このゲームはローカルサーバーで動作しています。");
    page.line("日時: " + format_local(now, "%Y/%m/%d %H:%M"));
    if (format_local(event_now, "%Y/%m/%d") != format_local(now, "%Y/%m/%d")) page.line("イベントカレンダー: " + format_local(event_now, "%Y/%m/%d"));
    page.line("");
    // 2. the open event areas
    add_event_areas(ctx, now, event_now, page);
    page.line("");
    // 3. the login bonuses
    add_login_bonuses(ctx, now, page);
    page.line("");
    // 4. the present box
    int64_t presents = ctx.st.one("select count(*) from presents where received_at is null", {});
    page.line("■ プレゼントBOX: " + std::to_string(presents) + " 件");
    return page.text;
}

}  // namespace

// soaserver/server.h: the page of a URL the local server hosts (only the notice page, kNoticeUrl and
// any query the client appends), built from the live server's state when the popup opens. The
// port's web view stand-in calls it (port/src/native/ui/webview_local.cpp).
bool web_page(const std::string& url, std::string* out) {
    if (url.rfind(kNoticeUrl, 0) != 0) return false;
    std::string page;
    bool ok = ext::with_live_server([&](ext::Ctx& ctx) { page = notice_page(ctx); });
    if (!ok) return false;
    LOGI("server", "web page %s: %zu bytes", url.c_str(), page.size());
    if (out) *out = page;
    return true;
}

namespace {

// The player load carries WebView {information: the local page}, and the page lists the open
// event areas, the login bonus and the present box.
NATIVE_TEST("player/notice") {
    bool ran = ext::with_scratch_server(t.rand_u64(), [&](ext::Ctx& ctx) {
        ctx.st.exec("begin");
        Request login_req;
        login_req.method = "Login";
        Value data = Value::object();
        ext::player_load(ctx, login_req, data);
        const Value* web_view = data.find("WebView");
        bool found = false;
        if (web_view && web_view->type == Value::Arr)
            for (auto& entry : web_view->arr)
                if (entry.find("key") && entry.find("key")->s == "information") found = entry.find("value")->s == kNoticeUrl;
        t.expect_eq(found, true, "WebView information -> the local page");
        std::string p = notice_page(ctx);
        t.expect_eq(p.find("■ 開催中のイベント") != std::string::npos, true, "events section");
        t.expect_eq(p.find("■ プレゼントBOX") != std::string::npos, true, "present box line");
        size_t n = events::open_areas(ctx, ctx.now(), ctx.event_now()).size();
        t.expect_eq(p.find("(" + std::to_string(n) + ")") != std::string::npos, true, "the open area count");
        // rows fit: no row wider than the wrap width
        size_t start = 0;
        while (start < p.size()) {
            size_t e = p.find('\n', start);
            if (e == std::string::npos) e = p.size();
            int cols = 0;
            for (size_t i = start; i < e;) {
                unsigned char ch = (unsigned char)p[i];
                size_t k = ch < 0x80 ? 1 : ch < 0xe0 ? 2 : ch < 0xf0 ? 3 : 4;
                cols += k == 1 ? 1 : 2;
                i += k;
            }
            if (cols > kPageColumns) t.fail("row of %d columns", cols);
            start = e + 1;
        }
        t.expect_eq(wrap("abc", 2), std::string("ab\n  c"), "wrap");
        ctx.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master (data/basmaster-3.7.0.sqlite3) and the seed save (data/saves/seed/Game.xml)");
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_notice() { ext::add_player_load(load_notice); }

}  // namespace soa::server
