#pragma once
// platform370: the 3.7.0 platform layer (platform370/README.md). What the 3.7.0 online client
// (work/libSOA-3.7.0.so) needs from the platform under it that the runtime (runtime/, built for
// the offline build's import and Java lists) doesn't give: the 3.7.0-only Java answers, the fmod import,
// the device clock, the native patch that hides master_global.service_stop_day, and the network
// glue (the host/port redirect and the AskaActivity HTTP client) that takes the client to
// soa-server.
//
// It plugs into the runtime only through its extension points (runtime/README.md). A host calls,
// in this order:
//
//   platform370::Config cfg; ...;      // from its options
//   platform370::install(cfg);          // before hle_init() and jni::Vm::get().init()
//   ... vfs_init, cpu_global_init, hle_init(), jni::Vm::get().init() ...
//   LoadedLib* lib = load_library(path);
//   platform370::install_patches(*lib); // after load_library, before run_initializers
//   ... (a host with natives: install_native_functions(*lib) here; README "Hosts with natives")
//   run_initializers(*lib);
//
// Used by soa-emu (emulator/src/main.cpp) and the port (soa, port/src/main.cpp; since P1, docs/history/PLAN-rebase-370.md).
#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace soa {
struct LoadedLib;
}

namespace soa::platform370 {

// Where the client's network goes (net_370.cpp, http_370.cpp; emulator/README.md "Networking").
struct NetConfig {
    // The game server (the client's production-game.so-ana.com:443): soa-server's --listen.
    std::string server_host = "127.0.0.1";
    int server_port = 44300;
    // soa-server's --http: where https:// / http:// URLs to a mapped host go, as plain HTTP.
    std::string http_host;  // "" = server_host
    int http_port = 44380;
    // The lobby (the client's <game host>:4001); "" / 0 = not redirected.
    std::string lobby_host;
    int lobby_port = 0;
    // Host names the client resolves -> the address they resolve to ("" = server_host).
    // production-game.so-ana.com is always mapped (to server_host unless named here). Keys are
    // lower case.
    std::map<std::string, std::string> hosts;
};

struct Config {
    // What GetApplicationVersion answers (device_config().app_version): the APK's versionName.
    // "" leaves device_config() alone.
    std::string app_version = "3.7.0";

    // The 3.7.0-only jb.Aska.AskaActivity methods (Play Games, achievements, location,
    // notifications), answered like a phone without those services (java_370.cpp).
    bool java = true;
    // The imports 3.7.0 has and the runtime lacks: fmod (hle_370.cpp). Without it the client's
    // fmod calls hit an unbound import.
    bool imports = true;
    // The device clock (hle_370.cpp): the time / gettimeofday / clock_gettime / syscall
    // (clock_gettime) overrides. With device_clock "host" they add an offset of 0.
    bool clock = true;
    // "host" (the host's real time) or "YYYY-MM-DD HH:MM:SS" (local time): the phone's clock at
    // install(); it runs on from there. Needs `clock`.
    std::string device_clock = "host";
    // The native patches (patch_370.cpp, install_patches): master_global.service_stop_day is
    // hidden, so the client runs on the real date; the sale-stopped dialog (OpenBuyEndDialog) opens
    // the coin shop instead. false = --no-patch.
    bool patch = true;
    // The client's language (lang_370.cpp, install_language; docs/client-changes.md "English mode"):
    // "ja" (default) leaves the client as shipped (CLanguage is 0x100, "no language", in all three
    // fields, and nothing is hooked); "en" sets CLanguage::Current to 1 (en) after CGame::OnInitialize
    // builds it, so every file load tries name-en.ext before name.ext (docs/english.md 6.3); the
    // hard-coded Japanese strings show port_en_* master text and long lines break at spaces
    // (text_370.cpp). Independent of `patch`. --lang.
    std::string lang = "ja";
    // The voice language (install_language): "ja" (default) writes BAS:VoiceLanguage = 0 into the
    // phone's Game.xml before the client starts, so the Voice_*.spk packs resolve to the Japanese
    // (bare) names with no -en probe; "keep" leaves the save's value. --voice-lang.
    std::string voice_lang = "ja";
    // The network glue: the name/port redirect (getaddrinfo / gethostbyname / connect, with the
    // Bionic<->glibc ai_flags and EAI_* fixes; net_370.cpp) and the host HTTP client behind the
    // AskaActivity HTTP methods (http_370.cpp). Off for a host whose client never reaches the
    // network (the port's in-process server: the FakeApiCaller route).
    bool net = true;
    bool http = true;
    NetConfig netcfg;
};

// Registers the enabled pieces with the runtime's extension points (hle_add_registrar,
// jni::add_class_installer) and applies app_version and the device clock. Call once, before
// hle_init() and jni::Vm::get().init(). fatal() on a malformed device_clock.
void install(const Config& cfg);

// The patch's outcome (install_patches).
enum class PatchStatus {
    Disabled,  // Config::patch false (or install() not called)
    Hooked,    // FindGlobalStringWithKey hooked: service_stop_day is hidden
    NotFound,  // the library's FindGlobalStringWithKey isn't 3.7.0's (missing, or its entry differs:
               // e.g. another hook is on it already); nothing patched
};
// Applies the native patch when Config::patch is set. Call after load_library, before any guest
// code runs (run_initializers) and before a host's own guest-function hooks.
PatchStatus install_patches(LoadedLib& lib);

// The language settings (Config::lang, Config::voice_lang): with lang "en" hooks
// CLanguage::CLanguage (Current = en) and CCocosLabel::SetText / DrawSelf (the hard-coded strings,
// word wrap; text_370.cpp); with voice_lang "ja"
// writes BAS:VoiceLanguage = 0 into DATA/data/shared_prefs/Game.xml. Call after vfs_init and
// install_patches, before any guest code runs (run_initializers) and before a host's natives.
// With lang "ja" and voice_lang "keep" it does nothing.
void install_language(LoadedLib& lib);
// Config::lang as install() got it ("ja" before install()).
const std::string& language();
// The guest functions install_language hooked (empty with --lang ja), for the selftests.
const std::vector<std::string>& language_hooks();

// --lang en's text (text_370.cpp), exposed for the selftests.
namespace text {
// The client's hard-coded Japanese strings (docs/english.md 1.5): the new master_text id that
// carries the English, the literal as the client passes it (real line breaks; "%d" in the two
// formats), the functions it comes from. data/english/client-strings.tsv has the same ids.
struct HardCoded {
    const char* id;
    const char* ja;
    const char* where;
};
const std::vector<HardCoded>& hard_coded();
// A master_text lookup: true and the text when the row exists.
using Lookup = std::function<bool(const char* id, std::string* text)>;
// When `s` is one of the literals (a format with its number), its English through `lookup` (a
// format's English must have exactly one %d); false otherwise, or when there is no English.
bool english_for(std::string_view s, const Lookup& lookup, std::string* out);
// The client's own StringDB::Get(id) (--lang en only; false before --lang en's install or when the
// master has no such row).
bool master_text(const char* id, std::string* out);
// Kana, kanji, CJK punctuation or full-width forms in `s`.
bool has_japanese(std::string_view s);
// The width of one line.
using Measure = std::function<float(std::string_view line)>;
// `text` with each line wider than `budget` broken at spaces (greedily); lines with Japanese (kana,
// kanji, full-width forms) or without a space stay, and so does a word wider than the budget.
std::string wrap(std::string_view text, float budget, const Measure& measure);
// The size of a whole (multi-line) text, as CDirectAofTextRenderer::CalcStringRect gives it.
struct Extent {
    float w, h;
};
using MeasureText = std::function<Extent(std::string_view text)>;
// A text laid out for a fixed box that shrinks its text to fit (the home's speech box, E12): the
// text with its line breaks collapsed to spaces and re-broken at spaces, and the scale DrawSelf's
// shrink then gives it (min(1, w / text w, h / text h)). The break width is the box's width over
// the scale of the fewest lines whose height fits (n lines at scale min(1, h / height of n lines)),
// so the shrunk text uses the whole width; no minimum: a text that needs a tiny font gets it.
struct BoxFit {
    std::string text;
    float scale;
};
BoxFit fit_box(std::string_view text, float box_w, float box_h, const MeasureText& measure);
}  // namespace text

// The patch's rule, for a host that replaces CParameterUtility::FindGlobalStringWithKey itself
// (the port's native): true for the master_global keys the patch answers with "" (today only
// "service_stop_day"), when Config::patch is on.
bool hides_global_key(std::string_view key);

// The network settings install() was given (net_370.cpp / http_370.cpp read them).
const NetConfig& net_config();
// The address a mapped name resolves to, or "" when `name` isn't mapped.
std::string mapped_address(const std::string& name);

// ---- the HTTP backend (http_370.cpp) ---------------------------------------------------------
// By default the AskaActivity HTTP client opens a TCP connection for every request (to
// netcfg.http_* for a mapped host). A host that has the server in its own process (the port's
// --server inproc) installs an HttpBackend instead: requests to a mapped host (mapped_address(host)
// != "") are then handed to it as calls, with no socket; other URLs still go over sockets.

// One request, as the client sent it.
struct HttpBackendRequest {
    std::string method;  // "GET" / "POST"
    std::string url;     // the full URL
    std::string host;    // the URL's host (mapped)
    std::string target;  // path + "?" + query, as on the request line
    std::vector<std::pair<std::string, std::string>> headers;  // Host, User-Agent, Connection; Content-Type/-Length for POST
    std::string body;    // POST content
};

// A response body read in pieces (bundles run to hundreds of MB): ReadHttpResponse reads it as the
// client asks for more.
class HttpBodyReader {
public:
    virtual ~HttpBodyReader() = default;
    virtual std::int64_t read(void* buf, std::size_t n) = 0;  // > 0 bytes read, 0 at the end, < 0 on an error
};

struct HttpBackendResponse {
    int status = 0;
    // The header fields (no status line). Content-Length, Transfer-Encoding and Connection are
    // dropped; the client gets Content-Length: `length`.
    std::vector<std::pair<std::string, std::string>> headers;
    std::uint64_t length = 0;  // the body's length
    // The body: `body` (in memory), then, when set, `reader` for the rest (length - body.size() bytes).
    std::string body;
    std::unique_ptr<HttpBodyReader> reader;
};

class HttpBackend {
public:
    virtual ~HttpBackend() = default;
    // Answers `req` (true), or fails like a connection that couldn't be made (false). Called on
    // the client's network thread(s): must be thread-safe.
    virtual bool handle(const HttpBackendRequest& req, HttpBackendResponse& resp) = 0;
};

// Installs the backend for mapped hosts (nullptr = sockets, the default). The backend must outlive
// every request; it may be installed before or after install(). Read at each request.
void set_http_backend(HttpBackend* backend);
HttpBackend* http_backend();

}  // namespace soa::platform370
