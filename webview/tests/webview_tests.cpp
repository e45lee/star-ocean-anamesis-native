// libsoawebview's tests: `build/webview/soawebview_tests` (exit status 0 = PASS). Pure functions
// (line breaking, the viewport meta, URL resolution, the CSS simplifier) and one render: a Japanese
// paragraph wraps inside its box, and a link is found by a tap.
#include <cstdio>
#include <string>
#include <vector>

#include "soawebview/page.h"

namespace {

int g_fail = 0;

void expect(bool ok, const char* what) {
    if (!ok) {
        printf("FAIL %s\n", what);
        g_fail++;
    }
}

std::vector<std::string> words(const char* text) {
    std::vector<std::string> out;
    soa::webview::split_text_ja(
        text, [&](const char* w) { out.push_back(w); }, [&](const char*) { out.push_back(" "); });
    return out;
}

void test_split() {
    // kana and ideographs break between characters; closing punctuation stays with what precedes,
    // opening brackets with what follows
    auto w = words("ゲームを「開始」する。");
    // ("ー" may not start a line: it stays with "ゲ")
    std::vector<std::string> want = {"ゲー", "ム", "を", "「開", "始」", "す", "る。"};
    expect(w == want, "split: kana, brackets, prolonged sound mark, full stop");
    // Latin words keep their spaces; a Latin run next to kana breaks at the boundary
    w = words("STAR OCEANのお知らせ");
    want = {"STAR", " ", "OCEAN", "の", "お", "知", "ら", "せ"};
    expect(w == want, "split: Latin and kana");
    // small kana may not start a line
    w = words("ちょっと");
    want = {"ちょっ", "と"};
    expect(w == want, "split: small kana");
}

void test_viewport() {
    using soa::webview::viewport_width;
    expect(viewport_width("<html><head><meta name=\"viewport\" content=\"width=640, user-scalable=no\"></head>") == 640, "viewport: width=640");
    expect(viewport_width("<head><meta name=\"viewport\" content=\"width=device-width, user-scalable=no\"></head>") == 0, "viewport: device-width");
    expect(viewport_width("<head><meta charset=\"utf-8\"></head><body>width=5</body>") == 0, "viewport: none");
}

void test_urls() {
    using soa::webview::resolve_url;
    expect(resolve_url("http://h/help/index.html?t=1", "images/a.png") == "http://h/help/images/a.png", "url: relative");
    expect(resolve_url("http://h/help/index.html", "../css/c.css") == "http://h/css/c.css", "url: dot-dot");
    expect(resolve_url("file:///a/b/kiyaku.html", "css/common.css") == "file:///a/b/css/common.css", "url: file");
}

void test_css() {
    std::string css = soa::webview::simplify_css("body { margin: 0; color: #333 }\n@media (width>=40rem) { p { padding-inline: 4px } }");
    expect(css.find("body{margin:0;color:#333;}") != std::string::npos, "css: plain rule kept");
    expect(css.find("@media (min-width:640px){p{padding-left:4px;padding-right:4px;}}") != std::string::npos, "css: range query, logical property");
}

void test_render() {
    // a long Japanese paragraph in a 300-px view must wrap into several lines, not overflow as one
    std::string para;
    for (int i = 0; i < 40; i++) para += "あいうえお";
    std::string html = "<html><head><title>テスト</title></head><body style=\"margin:0\"><p style=\"margin:0\">" + para +
                       "</p><p><a href=\"next.html\">次へ</a></p></body></html>";
    soa::webview::WebPage page([](const std::string&) { return soa::webview::FetchResult{404, "", "none"}; });
    page.load(html, "http://soa-local.invalid/test/index.html", 300, 400, 1.0f);
    expect(page.loaded(), "render: loaded");
    expect(page.title() == "テスト", "render: title");
    // 200 characters at 16 px in 300 px: about 11 lines of ~19 px
    expect(page.content_height() > 150, "render: the paragraph wraps");
    std::vector<uint8_t> px(300 * 400 * 4);
    page.draw(px.data(), 300, 400, 0, true);
    int dark = 0;
    for (size_t i = 0; i < px.size(); i += 4)
        if (px[i] < 128) dark++;
    // without a font nothing is drawn; that is reported, not failed (a font is a host package)
    if (dark == 0) printf("note: no text drawn (no font found?)\n");
    // the link: find it by scanning taps down the left edge
    std::string hit;
    for (int y = 0; y < 400 && hit.empty(); y += 4) hit = page.tap(8, y, 0);
    expect(hit == "http://soa-local.invalid/test/next.html", "render: a tap on the link");
}

}  // namespace

int main() {
    test_split();
    test_viewport();
    test_urls();
    test_css();
    test_render();
    printf("%s (%d failure%s)\n", g_fail ? "FAIL" : "PASS", g_fail, g_fail == 1 ? "" : "s");
    return g_fail ? 1 : 0;
}
