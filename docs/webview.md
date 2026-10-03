# The web view

This file covers the in-game web pages of STAR OCEAN: anamnesis 3.7.0: the notice board (お知らせ), terms (利用規約), help (ヘルプ), legal notices, banners and forms. It has four parts:

- what the client does with them;
- what content still exists now that the online service is gone;
- the design of a real web view for the port, the emulator and the viewer, reusing the renderer from the Dragalia Lost project;
- a staged plan.

A working prototype is on branch `port/webview`, off by default (`SOA_WEBVIEW=1`; "The prototype" below).

Source labels follow `docs/server-rules.md`: (a) master data, (b) client-side evidence (decompile, jadx, logs), (c) outside knowledge, (d) assumption or our choice.

## 1. What the 3.7.0 client does

### The Java side (`SOAActivity`, jadx of the 3.7.0 APK) (b)

The whole contract is three Java methods and one static flag. Compared with Dragalia's `CWebViewPlugin`, there are no load callbacks to the game, no JavaScript bridge the native side reads, and no history.

| Call | What the phone does |
|---|---|
| `ShowWebView(String url, int x, int y, int w, int h, boolean useBaseBrowser, String postData, boolean isEditable, int closeW, int closeH, int closeTotalH)` | **`url != null` and no view open:** sets `n = true` (`IsShowingWebView`), then on the UI thread builds a `WebView`. Settings: `useWideViewPort` + `loadWithOverviewMode`, JavaScript on, cache and cookies cleared, long press disabled. It loads `url` (`loadUrl`), or POSTs `postData` to it (`postUrl`) when `postData` isn't empty. The view goes in one of two containers. **`isEditable` false:** a `PopupWindow` of `w`×`h` at (`x`, `y`) (gravity top-left) over the game. The game draws its own frame and 閉じる button around it. **`isEditable` true:** an `AlertDialog` holding the web view (height `h`) and an Android close `ImageButton` (`dialog_close_button`, scaled to `closeW`×`closeH`). The close button sets `n = false` and dismisses the dialog, and so does Back (the dialog's cancel). **`url == null`:** dismisses either container and sets `n = false` (the game's close). **`url` given while a view is already open:** ignored. |
| `IsShowingWebView()Z` | `n` |
| `SetRootURI(String url)` | Keeps the URL's domain (the last three labels) plus its first path segment as `z`. In the `PopupWindow` view's `shouldOverrideUrlLoading`, when `useBaseBrowser` (`x`) is set, a link whose URL doesn't contain `z` stops loading and opens the system browser (`ACTION_VIEW`). Other links load in the view. The `AlertDialog` view has no such rule. |
| `OpenBrowser(String url)` | `ACTION_VIEW`: the system browser |

- `onPageStarted`, `onPageFinished` and `onReceivedError` only log. Nothing is reported back to native code.
- `SOAActivity.resize(float)` is a `@JavascriptInterface`, but no `addJavascriptInterface` call exists, so it is dead code.

### The native side (3.7.0 decompile: `tools/decomp.sh --v370`) (b)

- **`BAS::WebView(url, x, y, w, h, useBrowser, post, editable, closeW, closeH, closeTotal)`**
  - Calls `SetWebViewRootURI(url)` when `useBrowser` is set, then `Platform::Android::WebView_Android` → `ShowWebView`.
  - `BAS::WebViewError()` and `BAS::WebViewHidden()` are constant 0. On Android the game never learns of a load error.
- **`CWebView::OpenView(ViewType type, std::function<void()> on_close, bool editable)`** builds the dialog (layout `dialog4`) and calls `BAS::WebView`.
  - **Rectangle:** the page area's node gives it, from its world position and layout size × scale, divided by `CCocosDirector::ms_DisplayScale`. The height is less `ms_HeaderHeight`.
  - **Flags:** `useBrowser` = 1 for the types 1, 0xf, 0x11, 0x12 and 0x13. For type 1 (the notice board) the "今日は表示しない" box is shown.
  - **Dialog mode:** `editable` false opens the game dialog in mode 0 (the game's 閉じる); true opens mode 2.
  - **Measured in the port** (729×1296 window, game screen 810×1440): `ShowWebView(url, 0, 85, 810, 1092, useBrowser 1, post 0 bytes, editable 0, …)`. The page area is the full width from y 85, 1092 pixels tall. In the non-editable mode the three close-button ints are not set by the caller: garbage registers.
- **`CWebView::Progress`** (every frame, while the dialog is open):
  - **Editable mode:** when `IsShowingWebView()` turns false (the Android close button), it runs the close functor and calls `BAS::WebView(nullptr, …)`.
  - **Both modes:** the game's own close (`ForceClose`, or its 閉じる → `ToRelease`) calls `BAS::WebView(nullptr, …)`. In the logs that is `ShowWebView()` with an empty URL.
  - **Game loop:** the game keeps running and presenting frames while a web view is open.
- **`WebViewUtility::GetWebInfo(ViewType, string url)`** turns a type into a URL.
  - **Lookup:** the key is looked up in the server's `WebView` list (`CWebViewInfo`, CParameterManager+0x6120: `[{key, value}]`), then `CommonWebView` (+0x6b90), then `CommonWebSite` (+0x6be0). Some types use `master_global` instead (`CParameterUtility::FindGlobalStringWithKey`), and some use the URL the caller passes.
  - **Cache buster:** most types get `"?" + CTimeUtility::NowDate2MD5()` appended. That is the `?<40 hex>` seen in the logs.
  - **Missing key:** the URL is `http://www.tri-ace.co.jp/` (a string in the lib). The port's ヘルプ opened `http://www.tri-ace.co.jp/?b114d7…`, because the local server sends only `information` (observed).
- **`WebViewUtility::OpenBrowser(type)`** sends `GetWebInfo`'s URL to `BAS::OpenBrowser` → `SOAActivity.OpenBrowser`. `OpenBrowserFromDirectURL(url)` sends the URL as given.

### Every view type and who opens it (b)

Sources: call sites found by `tools/callers.py`; the type is the `w1`/`w0` constant at each call site. The `CWebView::OpenView` callers labelled `vector<COtherMenu::TopMenuLine>…` and `CUIChangeCommonResource` thunks by the symbol table are lambdas of those screens.

| Type | Key (source) | Opened by | Mode | URL extras |
|---|---|---|---|---|
| 0 | `kiyaku` (`WebView`) | new player's terms (`CPlayerInitializeMenu::OpenUsersGuidView`, `Progress_Release_Client` ×2); その他 → 利用規約 | popup | `?md5` |
| 1, 0x13 | `information` | the notice board (`CNoticeBoard::Progress`: login popups, side menu お知らせ); the title's お知らせ (0x13) | popup, useBrowser | the key's value has a pattern replaced (`Replace`), then `?md5` |
| 2 | `tokutei` | shops (`CDirectItemShop::CreateTabList`, item and coin shop): 特定商取引法に基づく表示 | popup | `?md5` |
| 3 | `shikin` | the same shops: 資金決済法に基づく表示 | popup | `?md5` |
| 4 | `bridge_user` | その他, the title: data transfer (引き継ぎ) | other menu: **editable** | `{UUID}` → `CUIUtility::GetUUID`, the game type id substituted |
| 5 | `lobi` | (no OpenView caller found) | | |
| 6 | `copyright` | その他 → 権利表記 | popup | `?md5` |
| 7 | `pay_back_support_site` (`master_global`) | その他, `CRefundDialog` (refund support) | **editable** | POST data `tagname=…&k=<md5>` built from a crypted parameter |
| 8 | (the passed URL) | | | `?md5` |
| 9 | `credit` | その他 → クレジット | popup | `?md5` |
| 10 | `help` | その他 → ヘルプ | popup | `?md5` |
| 0xc | `title_button_game_site` (`master_global`) | title and その他: **browser** (`OpenBrowser`) | | |
| 0xd | `title_button_osusume_game` (`master_global`) | title: **browser** | | |
| 0xe | `bridge_backup` | the title's data transfer | **editable** | like 4 |
| 0xf, 0x14 | (the passed URL) | banners (`CBannerBehavior::GetBannerLink` → `CDialogManager::OpenWebView`: `master_banner.url`), gacha rates (`CGachaBoxDetail`, `CGacha::CallRateWebView`), achievements | popup, useBrowser (0xf); a banner is editable when its form flag is set (`cset eq`) | |
| 0x10 | `twitter` | その他: **browser** | | |
| 0x11 | `opening` | その他 → オープニングムービー? (the 3.8.0 APK has `movie_index.html`) | popup, useBrowser | `?md5` |
| 0x12 | `comic` | その他 → 公式漫画 | popup, useBrowser | `?md5` |
| 0x15 | a crypted parameter (CParameterManager+0xa908) | `CRefundDialog` | popup | |
| 0x16 | `pay_back_site` (`master_global`) | `CRefundDialog` (refund form) | **editable** | POST `tagname=…&k=…` |

**Editable** means the `AlertDialog` with the Android close button. Those are the forms, where the user types into the page; they need `IsShowingWebView` and `postData`.

### What the desktop does today (b, observed)

- **The runtime** (`runtime/src/jni/java_android.cpp`) logs `ShowWebView(url) not supported`. `IsShowingWebView` is always false, and `OpenBrowser` / `SetRootURI` are logged only. soa-emu and soa-viewer behave this way.
- **soa-emu over soa-server:** the notice board's popup is empty. Its URL is `http://soa-local.invalid/notice?…`, which no host serves.
- **soa, in-process server** (`port/src/native/ui/webview_local.cpp`, a client change in `docs/client-changes.md`): for the one URL the local server hosts, `server::web_page` returns plain text. A wrapper around `CWebView::OpenView` clones the popup's "今日は表示しない" label into the page area and sets that text on it. The text has no layout or scrolling, and is wrapped at 48 columns by the server.
- **soa-viewer (3.8.0):** the terms, copyright and credits pages are `file:///android_asset/*.html` (`master_global` `local_html_*_by_android`), and they show an empty frame.

## 2. What content exists

| Screen | Original source | What's left | Recommended source |
|---|---|---|---|
| Notice board (お知らせ, type 1/0x13) | `production-cache.webview.so-ana.com/information/…` (c) | Nothing. **Wayback has no snapshot** of any JP `information/` page; `/information/detail/<id>.html` returns no capture at all. Only two NA-host pages are archived (`production-cache.webview.na.so-ana.com/information/list.html`, `…/detail/56002.html`). | **The local server's page** (server-first, (d)): built from its state (open events, login bonus, present box). It already exists as text and now also as HTML (`server::web_document`, below). |
| Banner details (0xf: 1,715 `master_banner.url` → `information/detail/<id>.html`, 53 `form*.square-enix.com`) | same host (a) | Nothing archived | A server page per banner, generated from `master_banner` (name, period, image under `B/` in the download), or one "this notice is no longer available" page (d) |
| Terms (利用規約, 0) | server-supplied `kiyaku` URL (b) | The **3.8.0 XAPK's `assets/kiyaku.html`**: the offline edition's terms, `ユーザー規約（… オフライン版）`. Not in the 3.7.0 APK, which has no HTML assets. | 3.8.0's `kiyaku.html` + `css/common.css` + `images/`, served by the server under the 3.7.0 key, with a departure note: these are the offline edition's terms (d) |
| Copyright (6), credit (9), comic (0x12), opening (0x11) | server-supplied URLs | 3.8.0 XAPK: `copyright_android.html`, `credit.html`, `comic_index.html` (its banners link to the official site), `movie_index.html` | Those files, served the same way |
| 特定商取引法 / 資金決済法 (2, 3) | server-supplied | 3.8.0 XAPK `tokutei.html`, `shikin.html` | Those files |
| Inquiry, age (no 3.7.0 type) | | 3.8.0 `inquiry.html` ("仮設置": a placeholder), `nenrei.html` | Not needed |
| Help (ヘルプ, 10) | `production-cache.webview.so-ana.com/help/…` (c) | **Wayback has the help site**: `help/index.html` and 17 topic pages (about, battle, character, deepspace, favor, follow, gacha, home, item, mission, sevens_star, stamina, stone, title, tower, twineclipse, worldboss), `css/common.css` and about 33 images, captured 2016–2020 (the latest on 2020-02-10). `about.html` was fetched once to check (200, Japanese, `width=device-width`; the topics are CSS `:checked` toggles, no JavaScript). Nothing was downloaded in bulk. | Optional: the user fetches the archived set once into a local directory (not committed), and the server serves it from there. Otherwise a small server help page. |
| Data transfer, refund (4, 7, 0xe, 0x16) | `sqex-bridge.jp`, `support.jp.square-enix.com` forms | Dead services (c) | A server page saying the service has ended (d). The forms can't work. |
| Browser links (0xc, 0xd, 0x10, the comic banners) | external sites | | Log them, as today. Optionally print the URL on the page or in a host notification; never open a browser silently. |

The 3.8.0 pages are Square Enix files and stay out of git. The server reads them where they already are: the viewer's XAPK extraction, or `--apk-dir`.

## 3. Design

### Where it lives

```
webview/                 libsoawebview: the page renderer (no runtime, JNI or GL dependency)
  include/soawebview/page.h   WebPage, Fetch, simplify_css, resolve_url, viewport_width, split_text_ja
  src/page.cpp             litehtml's document_container drawn in software (Dragalia's)
  src/css_simplify.cpp     the CSS simplifier (Dragalia's, unchanged)
  src/url.cpp              resolve_url (Dragalia's, + file:// bases)
  src/fonts.cpp            host fonts, Japanese first (stb_truetype)
  src/image.cpp            stb_image (PNG, JPEG, GIF, BMP)
  src/text_ja.cpp          Japanese line breaking, the viewport meta (new)
  tools/render.cpp         soa-webview-render: an HTML file -> PNG
  tests/webview_tests.cpp  soawebview_tests
runtime/src/app/page_overlay.{h,cpp}   a host-drawn picture over the game + input capture (generic)
<the Java side>          ShowWebView / IsShowingWebView / SetRootURI / OpenBrowser over both
```

- **The renderer is a separate library:** soa, soa-emu and soa-viewer all need it, and so can the server's tests and an offline tool. It depends only on litehtml and stb, never on the runtime.
- **The host side is in the runtime:** drawing over the frame and taking touches are the host loop's (`app/`). The Java behaviour belongs with the other `SOAActivity` answers.
- **Target home of the Java side:** `runtime/src/jni/java_android.cpp`'s `ShowWebView` grows into a `runtime/src/frontend/webview.cpp` that every host gets, as Dragalia's `webview_dl.cpp` did for the `CWebViewPlugin`. The page renderer is reached through a fetch callback.
- **In the prototype** the Java side sits in the port (`port/src/native/ui/webview_page_view.cpp`), because its only content source is the in-process server.

### The vcpkg port

- `cmake/vcpkg-ports/litehtml/` is the Dragalia Lost project's overlay port, copied whole: litehtml 0.10 + gumbo, with these patches:
  - `use-vcpkg-gumbo` and `fix-relative-includes`, vcpkg's own;
  - `flex-column-line-cross-size`, a flex fix;
  - `mingw-snprintf`: on Windows litehtml's `t_snprintf` passes `_snprintf_s`'s arguments in the wrong order. It is kept for the planned MinGW-w64 Windows runner. The test `tests/snprintf_s_args.c` is the minimal reproduction (upstream fixed it after v0.10 in d4cbcba).
- **One difference from Dragalia's copy:** `mingw-snprintf.patch`'s hunk header reads `@@ -1,16 +1,11 @@`. Dragalia's a4c1697 added a comment line to the hunk without updating its count, so `git apply` (and with it vcpkg) rejects Dragalia's current file as corrupt. This is noted in the port's `vcpkg.json` `$comment`. **Keep the two in sync.**
- `CMakeLists.txt` adds `VCPKG_OVERLAY_PORTS` (`cmake/vcpkg-triplets/` is untouched). `vcpkg.json` adds `litehtml` and `stb`. libwebp isn't needed: this game's pages have PNG, JPEG and GIF only.

### The renderer (from Dragalia, with changes for this game)

Dragalia's `webview_page.cpp` is reused nearly verbatim: litehtml's container drawn in software into RGBA, rounded fills and borders, gradients, images scaled with object-fit cover, links found by a tap, and the CSS simplifier. The changes:

- **Japanese line breaking.** litehtml 0.10 breaks only at white space and around U+4E00–9FCC ideographs, so a kana or katakana run was one unbreakable word that overflowed its box. `split_text_ja` (a `split_text` override) breaks between any two characters when one is CJK (kana, ideographs, CJK punctuation, full-width forms, Hangul), with the basic kinsoku rules: no break before closing punctuation, small kana or ー, and none after opening brackets.
- **The wide-viewport mode.** `SOAActivity` sets `useWideViewPort` + `loadWithOverviewMode`. A page whose viewport meta names a width (the APK's pages: `width=640`) is laid out that many CSS pixels wide and scaled to the view. Other pages use the phone's density: (d) 2.625, i.e. 420 dpi on a 1080-wide phone, scaled to the game screen.
- **Fonts, Japanese first.** The regular face is a host Japanese font:
  - `SOA_WEBVIEW_FONT`;
  - IPAex Gothic, Noto Sans CJK, `fonts-japanese-gothic`, IPA Gothic, Droid Sans Fallback;
  - DejaVu / Liberation as the Latin fallback.
  - Bold is Noto CJK Bold if installed, else synthetic. Without a font, pages draw no text, with a warning. The README setup should list `fonts-ipaexfont` or `fonts-noto-cjk`, as the keyboard text box does.
- **Language** ja-JP. **WebP is left out.**

**Fonts, later:** the keyboard's text box (`runtime/src/app/text_overlay.cpp`, branch `port/text-overlay2`) uses FreeType and its own search for the same fonts (`SOA_FONT`, IPAex, Noto CJK, Droid, `fc-match :lang=ja`). Two stacks for one job is one too many. Plan:

1. Move the search into a shared `runtime/src/app/fonts.{h,cpp}` (or a tiny library both link) that returns paths.
2. Then either keep stb_truetype for pages (simple, no hinting) or switch `fonts.cpp` to FreeType once it is in `vcpkg.json` (better small-size quality, `.ttc` faces by index).
3. One environment variable, `SOA_FONT`, for both.

### Drawing over the game, shared with the text box

- **Both overlays draw from `GfxHooks::draw_overlay`** (`runtime/src/app/host.cpp`), after the movie and **before** the screenshot read-back, so `shot:` includes them. With nothing shown, neither makes a GL call.
- **The web view needs no idle presenting.** The game keeps presenting while a web view is open (`CWebView::Progress` runs each frame). The text box does need it (`hle/gfx.h` `present_again`), because the game blocks its logic thread while its keyboard is open.
- **Different GL paths:**
  - The web view's picture is opaque, as Android's `WebView` is, so it is a plain texture → `glBlitFramebuffer` into the letterboxed viewport (Dragalia's code).
  - The text box needs blending, so it draws a quad with a small program.
  - They can share a helper later: "upload an RGBA picture, put it at a game-screen rectangle, blend or not".
- **The prototype's module** is `runtime/src/app/page_overlay.{h,cpp}`:
  - `show(rect, rgba)` / `hide()` / `visible()`;
  - `draw(...)`, called from `draw_overlay`;
  - `touch(action, x, y)` and `wheel(x, y, dy)`, called from the host's `push_touch` and wheel handling.
- **Input:** a touch that starts inside the rectangle belongs to the page until it ends, so neither a drag (scroll) nor a tap (a link) reaches the game. The wheel over it scrolls it. Outside the rectangle everything goes to the game as before, so the game's own 閉じる below the page area works. This is Android's `PopupWindow` behaviour. The text box takes keys, not touches, so the two don't conflict.
- **Merge note:** `port/text-overlay2` and this branch both add one line to `Gfx::draw_overlay` in `host.cpp`. Expect a trivial merge.

### What the server serves (server-first)

The pages are the server's: the client asks for a URL and the server answers it. Today `server::web_page(url)` returns plain text for `http://soa-local.invalid/notice`, and `server::web_document(url)` (new) returns that page as HTML (`text/html; charset=utf-8`). The plan:

1. **Serve over HTTP on the CDN router.** Mount a `/webview/` route on `server/net`'s `HttpRouter`, next to `mount_cdn`: `/webview/information` (the notice), `/webview/banner/<id>`, `/webview/apk/<file>` (the 3.8.0 pages and their `css/` and `images/`), `/webview/help/…` (an optional local Wayback copy). The router is the one soa-server serves on `--http` and the one the in-process server installs as platform370's HTTP backend.
2. **Hand out URLs on that host.** The `WebView` list (state key `WebView`, (b)) sends every key the client looks up (`information`, `kiyaku`, `help`, `copyright`, `credit`, `comic`, `opening`, `tokutei`, `shikin`, and `bridge_user` / `bridge_backup` / pay-back pages saying "ended"). The values are `http://production-game.so-ana.com/webview/<key>`: the client's own CDN host, which platform370 already maps (`NetConfig::hosts`). soa-emu over soa-server then gets the pages from soa-server, and soa in-process gets them from the same router. `soa-local.invalid` goes, and soa-emu's notice board stops being empty.
3. **Fetch through the same path.** The web view's `Fetch` goes through platform370's HTTP client (`http_370.cpp`, the backend or the socket to `--http`), so the page, its CSS and its images are all server answers. soa-viewer (3.8.0, no server) fetches `file:///android_asset/…` from its APK.
4. **The label stand-in can go** once the web view is the default. It is a client change (`webview_local.cpp`), and its `docs/client-changes.md` entry goes with it.

The cache buster `?<md5>` is ignored by the router (the query isn't part of the route). The `information` value's replaced pattern still needs checking in `GetWebInfo` (what is replaced with what) before the server sends a URL that contains it.

### Departures from the phone (to document in `docs/client-changes.md` when it ships)

These are platform behaviour, not game code, so most belong in the runtime's README rather than in client changes:

- **No JavaScript** (none of the known pages need it: the APK pages have no `<script>`; help uses CSS toggles) and **no forms or POST**. The editable forms are dead services anyway.
- **CSS:** CSS 2.1 + flexbox (litehtml 0.10). The help site's `:checked` toggles need either a `:checked` → `[checked]` rewrite in the simplifier plus a tap on a `<label>` toggling its input's attribute, or the server opening every section.
- **Fonts:** host fonts (IPAex / Noto), not Android's Noto Sans CJK JP.
- **Opaque:** the view is drawn opaque.
- **Links:** links the server doesn't host are logged, not opened in a browser (the phone opens one when `useBrowser` is set and the link is off the root URI).

## 4. The prototype (branch `port/webview`)

Off by default. `SOA_WEBVIEW=1` turns it on in soa with the in-process server.

### What it does

- **Opening.** `SOAActivity.ShowWebView` (the port's existing override in `webview_local.cpp`) logs every argument. For a URL the local server hosts (`server::web_document`: today the notice board), it lays the HTML out with libsoawebview at the rectangle the game asks for, draws it, and hands the picture to `app::page_overlay`. The guest's own popup (frame, 閉じる, 今日は表示しない) is untouched.
- **Input.** A drag in the page scrolls it, the wheel scrolls it, and a tap follows a link (a local page loads; anything else is logged).
- **Closing.** `ShowWebView(null)` (the game's 閉じる) removes the page.
- **Without the variable** nothing changes: the label stand-in, the "not supported" logs, and no overlay call.

### Results

Screenshots are in `/home/fish/.claude/jobs/ac4802d9/tmp/webview/`:

- `run2/shots/02a-notice-webview.png`: **in game**. After login the notice board shows the server's HTML page, laid out over the popup's page area (0, 85, 810×1092 on the 810×1440 game screen) with the game's 閉じる and 今日は表示しない around it. 閉じる closes it (`ShowWebView()` → `webview: closed`).
- `run1/shots/02-notice.png`: the same popup with today's label stand-in, for comparison.
- `notice-render.png`: the same HTML rendered offline (`soa-webview-render`). The HTML came from `SOA_NOTICE_HTML_DUMP=… soa-server --selftest player/notice`.
- `apk-kiyaku-screen.png`, `apk-kiyaku.png`, `apk-comic_index-top.png`, `apk-credit.png`, `apk-copyright_android.png`, `apk-tokutei.png`: the 3.8.0 APK's pages (Japanese terms wrapped with kinsoku, the comic banner images, the CSS header bar).

Not tried in game:

- scrolling: the notice page, 973 px, fits its 1092-px area; scrolling is Dragalia's logic; offline `--screen --scroll 3000` of the terms renders the right slice (`apk-kiyaku-scroll3000.png`);
- link taps in game (offline, `--tap 360:460` on `comic_index.html` finds the first banner's link: `http://www.jp.square-enix.com/soa/nichijo/`);
- the editable mode.

### The render tool

`build/webview/soa-webview-render PAGE OUT.png [--width W] [--height H] [--screen] [--scroll Y] [--url URL] [--map PREFIX=DIR] [--tap X:Y]`

It renders a local HTML file the way the web view would, at a view size in device pixels. For example, the terms at the notice board's size:

```
build/webview/soa-webview-render work/extracted/com.square_enix.android_googleplay.StarOceanj/assets/kiyaku.html /tmp/kiyaku.png --width 810 --height 1092 --screen
```

`SOA_WEBVIEW_DUMP_CSS=FILE` appends each stylesheet as litehtml gets it, after the simplifier.

### Tests

- `build/webview/soawebview_tests` covers line breaking, the viewport meta, URLs, the simplifier, and a render: a Japanese paragraph wraps, and a tap finds a link.
- The server test `player/notice` checks the page's HTML form.

## 5. Effort and staged plan

Estimates are for one agent and include gates and docs.

| Stage | Work | Estimate |
|---|---|---|
| W0 (done) | This investigation; litehtml through vcpkg; the renderer ported with Japanese breaking and wide viewport; offline tool and tests; the notice board as HTML in game behind `SOA_WEBVIEW` | — |
| W1 | **Server pages over HTTP:** the `/webview/` route on the CDN router; the `WebView` list with every key; the notice and an "ended" page; the 3.8.0 APK pages from `--apk-dir` / the viewer's XAPK; banner pages from `master_banner`. Tests per route; `docs/server-rules.md` labels | 0.5–1 day |
| W2 | **The Java side in the runtime** (`frontend/webview.cpp`) for every host: `ShowWebView` both modes, `IsShowingWebView` (the editable mode's close: an Android-style close button drawn under the page, Back closes it), `SetRootURI` / `OpenBrowser` link policy, `postData` logged. Fetch through platform370's HTTP client (soa, soa-emu) or the APK (soa-viewer, `file:///android_asset`). Render on a worker thread, as Dragalia does, not on the logic thread. Turn it on by default; retire the label stand-in. Gates: smoke, viewer and emulator boots, the session scripts that close the notice board (`flowctl.py login-popups` waits for `ShowWebView(http`) | 1–1.5 days |
| W3 | **Fonts shared with the text box** (one search, FreeType or stb), README setup | 0.5 day |
| W4 | **Help:** an optional local copy of the Wayback help site (a fetch script the user runs once; nothing committed); the `:checked` toggles (simplifier rewrite + label taps) | 0.5 day |
| W5 | Polish: kinetic scrolling, a scroll bar, the tap highlight, the dialog close button's art (`dialog_close_button` from the APK's resources) | optional |

Risks:

- litehtml's CSS coverage for the help site (images and toggles; the APK pages render well);
- the `information` URL pattern replacement, which needs a decompile read;
- merging with the text box's `host.cpp` changes (small).
