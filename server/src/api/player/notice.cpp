// The notice board's page (お知らせ; api/player/README.md). Port code, not guest behaviour; every
// rule carries its source label, (a) master data, (b) client-side evidence, (c) outside knowledge,
// (d) assumption. Rules in docs/server-rules.md#notice-board.
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
#include <soa/env.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "core/log.h"
#include "core/time.h"
#include "soaserver/native_test.h"
#include "soaserver/events.h"
#include "soaserver/config.h"
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

// (d) The page's own words in the server's language: English under --english
// (docs/server-rules.md#english), else Japanese. The leading marks (【】, ■, ・) stay in both: they
// are the page's markup (Page::html).
const char* tr(const char* ja, const char* en) { return config().english ? en : ja; }

// OnPlayerLoad: WebView                                   on Login, SimpleLogin, CreatePlayer, GetPlayer, NoLoginStart
// Rules: docs/server-rules.md#notice-board
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

// The page being built: its lines, unwrapped (text() wraps them for the label, html() marks them up
// for a web view).
struct Page {
    std::vector<std::string> lines;
    void line(const std::string& s) { lines.push_back(s); }
    std::string text() const {
        std::string t;
        for (auto& l : lines) t += wrap(l, kPageColumns) + "\n";
        return t;
    }
    std::string html() const;
};

std::string html_escape(const std::string& s) {
    std::string o;
    for (char ch : s) {
        if (ch == '&') o += "&amp;";
        else if (ch == '<') o += "&lt;";
        else if (ch == '>') o += "&gt;";
        else if (ch == '"') o += "&quot;";
        else o += ch;
    }
    return o;
}

// (d) The HTML form of the page: the same lines, marked up by their leading mark ("【...】" the
// title, "■" a section heading, "・" a list item, the rest paragraphs), in the look of the game's
// own local pages (the 3.8.0 APK's assets/*.html: a 640-px viewport, white text on dark grey, a (380-ok)
// dark heading bar), with inline CSS only (no resources to fetch).
std::string Page::html() const {
    std::string h = std::string("<!DOCTYPE html>\n<html lang=\"") + tr("ja", "en") + "\"><head><meta charset=\"utf-8\"><title>" +
                    tr("お知らせ", "Notices") +
                    "</title>\n"
                    "<meta name=\"viewport\" content=\"width=640, user-scalable=no\">\n<style>\n"
                    "body{margin:0;padding:24px 28px;background:#2a2c33;color:#f2f2f2;font-size:26px;line-height:1.5}\n"
                    "h1{margin:0 0 16px;padding:8px 0;background:#3c3c3c;border-top:2px solid #6aa7d8;border-bottom:2px solid #6aa7d8;"
                    "color:#fff;font-size:30px;text-align:center;font-weight:bold}\n"
                    "h2{margin:22px 0 6px;padding:4px 12px;border-left:8px solid #6aa7d8;background:#383b45;font-size:27px}\n"
                    "ul{margin:0;padding:0 0 0 1.2em}li{margin:2px 0}p{margin:4px 0}.clock{color:#c8d4e0}\n"
                    "</style></head><body>\n";
    bool in_list = false;
    auto close_list = [&] {
        if (in_list) h += "</ul>\n";
        in_list = false;
    };
    auto starts = [](const std::string& l, const char* p) { return l.rfind(p, 0) == 0; };
    for (auto& l : lines) {
        if (l.empty()) {
            close_list();
            continue;
        }
        if (starts(l, "【")) {
            close_list();
            std::string t = l.substr(3);
            if (t.size() >= 3 && t.compare(t.size() - 3, 3, "】") == 0) t.resize(t.size() - 3);
            h += "<h1>" + html_escape(t) + "</h1>\n";
        } else if (starts(l, "■")) {
            close_list();
            std::string t = l.substr(3);
            while (!t.empty() && t[0] == ' ') t.erase(0, 1);
            h += "<h2>" + html_escape(t) + "</h2>\n";
        } else if (starts(l, "・")) {
            if (!in_list) h += "<ul>\n";
            in_list = true;
            h += "<li>" + html_escape(l.substr(3)) + "</li>\n";
        } else {
            close_list();
            bool clock = starts(l, tr("日時", "Date")) || starts(l, tr("イベントカレンダー", "Event calendar"));
            h += std::string(clock ? "<p class=\"clock\">" : "<p>") + html_escape(l) + "</p>\n";
        }
    }
    close_list();
    return h + "</body></html>\n";
}

// (a) The open event areas, named by master_event_area.name_message_id (notice_page, step 2).
void add_event_areas(ext::Ctx& ctx, ServerTime now, EventTime event_now, Page& page) {
    auto areas = events::open_areas(ctx, now, event_now);
    page.line(tr("■ 開催中のイベント (", "■ Events now on (") + std::to_string(areas.size()) + ")");
    int shown = 0;
    for (const auto& area : areas) {
        if (shown == kMaxListedAreas) {
            page.line(config().english ? "  and " + std::to_string(areas.size() - shown) + " more"
                                       : "  ほか " + std::to_string(areas.size() - shown) + " 件");
            break;
        }
        std::string name;
        ctx.m.q("select name_message_id from master_event_area where id = ?", {area.id},
                [&](const Row& area_row) { name = ext::display_text(ctx.m, area_row.s("name_message_id")); });
        page.line("・" + (name.empty() ? area.label : name));
        shown++;
    }
    if (areas.empty()) page.line(tr("・なし", "・None"));
}

// (a) The login bonuses running at the server clock with the day reached (api/daily/login_bonus.cpp's
// table) (notice_page, step 3).
void add_login_bonuses(ext::Ctx& ctx, ServerTime now, Page& page) {
    page.line(tr("■ ログインボーナス", "■ Login bonuses"));
    int bonuses = 0;
    ctx.m.q("select id, name_message_id, opened_at, closed_at from master_login_bonus order by order_id", {}, [&](const Row& bonus_row) {
        if (!open_at(bonus_row.s("opened_at"), bonus_row.s("closed_at"), now)) return;
        int64_t day = ctx.st.one("select ifnull(max(day_index), 0) from login_bonus where id = ?", {bonus_row.i("id")});
        std::string day_text = !day ? "" : config().english ? " (day " + std::to_string(day) + ")" : " " + std::to_string(day) + "日目";
        page.line("・" + ext::display_text(ctx.m, bonus_row.s("name_message_id")) + day_text);
        bonuses++;
    });
    if (!bonuses) page.line(tr("・なし", "・None"));
}

// The notice page: (d) what it lists is the server's choice.
Page notice_lines(ext::Ctx& ctx) {
    Page page;
    ServerTime now = ctx.now();
    EventTime event_now = ctx.event_now();
    // 1. the clocks
    page.line(tr("【お知らせ】", "【Notices】"));
    page.line(tr("このゲームはローカルサーバーで動作しています。", "This game is running on a local server."));
    page.line(tr("日時: ", "Date: ") + format_local(now.v, "%Y/%m/%d %H:%M"));
    if (format_local(event_now.v, "%Y/%m/%d") != format_local(now.v, "%Y/%m/%d"))
        page.line(tr("イベントカレンダー: ", "Event calendar: ") + format_local(event_now.v, "%Y/%m/%d"));
    page.line("");
    // 2. the open event areas
    add_event_areas(ctx, now, event_now, page);
    page.line("");
    // 3. the login bonuses
    add_login_bonuses(ctx, now, page);
    page.line("");
    // 4. the present box
    int64_t presents = ctx.st.one("select count(*) from presents where received_at is null", {});
    page.line(config().english ? "■ Present box: " + std::to_string(presents) + (presents == 1 ? " item" : " items")
                               : "■ プレゼントBOX: " + std::to_string(presents) + " 件");
    return page;
}

// The notice page's text (the label of webview_local.cpp).
std::string notice_page(ext::Ctx& ctx) { return notice_lines(ctx).text(); }

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

// soaserver/server.h: the notice page as HTML, for a real web view (docs/webview.md).
bool web_document(const std::string& url, std::string* content_type, std::string* body) {
    if (url.rfind(kNoticeUrl, 0) != 0) return false;
    std::string page;
    bool ok = ext::with_live_server([&](ext::Ctx& ctx) { page = notice_lines(ctx).html(); });
    if (!ok) return false;
    LOGI("server", "web document %s: %zu bytes of HTML", url.c_str(), page.size());
    if (content_type) *content_type = "text/html; charset=utf-8";
    if (body) *body = page;
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
        // the HTML form: the same lines, marked up
        std::string h = notice_lines(ctx).html();
        t.expect_eq(h.find("<h1>お知らせ</h1>") != std::string::npos, true, "html title");
        t.expect_eq(h.find("<h2>開催中のイベント (" + std::to_string(n) + ")</h2>") != std::string::npos, true, "html events heading");
        t.expect_eq(h.find("<h2>プレゼントBOX: ") != std::string::npos, true, "html present box heading");
        if (const char* dump = env::env_str("SOA_NOTICE_HTML_DUMP")) {  // docs/webview.md: the page for soa-webview-render
            if (FILE* f = fopen(dump, "wb")) {
                fwrite(h.data(), 1, h.size(), f);
                fclose(f);
            }
        }
        ctx.st.exec("rollback");
    });
    if (!ran) t.fail("needs the 3.7.0 master (data/basmaster-3.7.0.sqlite3) and the seed save (data/saves/seed/Game.xml)");
}

// --english: the page's own words in English, <html lang="en">, the login bonus names from the
// English text table (here the fixture's "Login Bonus"); without it, the Japanese page.
NATIVE_TEST("player/notice-english") {
    std::string fixture = find_repo_file("server/tests/fixtures/english-fixture.tsv");
    if (fixture.empty()) return t.fail("server/tests/fixtures/english-fixture.tsv not found");
    const bool saved_english = config().english;
    const std::string saved_text = config().english_text;
    config().english = true;
    config().english_text = fixture;
    std::string h, p;
    bool ran = ext::with_scratch_server(t.rand_u64(), [&](ext::Ctx& ctx) {
        h = notice_lines(ctx).html();
        p = notice_page(ctx);
    });
    config().english = saved_english, config().english_text = saved_text;  // only these: the scratch server sets others
    if (!ran) return t.fail("needs the 3.7.0 master (data/basmaster-3.7.0.sqlite3) and the seed save (data/saves/seed/Game.xml)");
    t.expect_eq(h.find("<html lang=\"en\">") != std::string::npos, true, "html lang en");
    t.expect_eq(h.find("<title>Notices</title>") != std::string::npos && h.find("<h1>Notices</h1>") != std::string::npos, true, "title");
    t.expect_eq(h.find("<h2>Events now on (") != std::string::npos, true, "events heading");
    t.expect_eq(h.find("<h2>Login bonuses</h2>") != std::string::npos, true, "login bonus heading");
    t.expect_eq(h.find("<h2>Present box: ") != std::string::npos, true, "present box heading");
    t.expect_eq(h.find("<p class=\"clock\">Date: ") != std::string::npos, true, "the clock line");
    t.expect_eq(p.find("This game is running on a local server.") != std::string::npos, true, "the text form");
    t.expect_eq(p.find("お知らせ") == std::string::npos && p.find("ログインボーナス\n") == std::string::npos, true, "no Japanese headings");
}

}  // namespace

// The module's registrations, in their order (src/core/modules.cpp calls this; server/ARCHITECTURE.md
// "The module registry and its order").
void register_notice() { ext::add_player_load(load_notice); }

}  // namespace soa::server
