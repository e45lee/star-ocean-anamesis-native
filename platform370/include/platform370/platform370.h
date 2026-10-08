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
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <utility>

#include <soa/line_break.h>

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
// The line breaking itself is soa::text (common/include/soa/line_break.h): break_lines (the label
// wrap: keep_breaks, skip_japanese) and fit_box (the boxes).

// DrawSelf's shrink of a fixed-size label: min(1, box w / text w, box h / text h).
double fit_scale(double text_w, double text_h, double box_w, double box_h);

// A bounded, thread-safe cache of the text code's results (least recently used out first).
template <class V>
class LruCache {
public:
    explicit LruCache(size_t capacity) : cap_(capacity) {}
    bool get(const std::string& key, V* out) {
        std::lock_guard<std::mutex> l(mu_);
        auto it = map_.find(key);
        if (it == map_.end()) return false;
        order_.splice(order_.begin(), order_, it->second);
        *out = it->second->second;
        return true;
    }
    void put(const std::string& key, V value) {
        std::lock_guard<std::mutex> l(mu_);
        auto it = map_.find(key);
        if (it != map_.end()) {
            it->second->second = std::move(value);
            order_.splice(order_.begin(), order_, it->second);
            return;
        }
        order_.emplace_front(key, std::move(value));
        map_[key] = order_.begin();
        if (map_.size() > cap_) {
            map_.erase(order_.back().first);
            order_.pop_back();
        }
    }
    size_t size() {
        std::lock_guard<std::mutex> l(mu_);
        return map_.size();
    }

private:
    size_t cap_;
    std::mutex mu_;
    std::list<std::pair<std::string, V>> order_;
    std::unordered_map<std::string, typename std::list<std::pair<std::string, V>>::iterator> map_;
};

// What the hooks remember per guest label (thread-safe): the text a hook set and the text it was
// made from (so a label laid out again is re-wrapped from its original, not from our result), and
// a label's own box while E12 switched it to a fixed box. Keyed by the label's guest address, so the
// label's destructor (CCocosLabel D0/D1, hooked) calls forget(): a freed label's address reused by a
// new label never inherits the old label's text or "restores" the old label's box.
class LabelStates {
public:
    struct Box {
        uint8_t custom, shrink;
        float w, h;
    };
    // The original a hook made `current` from, when `current` is what a hook set on this label.
    bool original_of(uint64_t label, std::string_view current, std::string* original);
    // A hook set `produced` (made from `original`) on the label.
    void set(uint64_t label, std::string produced, std::string original);
    void erase_text(uint64_t label);
    // The label's own box, kept the first time a hook changes it.
    void keep_box(uint64_t label, const Box& own);
    // The kept box (and forgets it): false when the hook never changed this label's box.
    bool take_box(uint64_t label, Box* own);
    // The kept box, still kept: false when the hook never changed this label's box.
    bool peek_box(uint64_t label, Box* own);
    // A label marked as the story message window's (E13): the label wrap leaves it alone.
    void mark_story(uint64_t label);
    bool is_story(uint64_t label);
    // The label is destroyed: everything about it goes.
    void forget(uint64_t label);
    size_t size();

private:
    struct Entry {
        std::string produced, original;
        bool has_text = false, has_box = false, story = false;
        Box box{};
    };
    std::mutex mu_;
    std::unordered_map<uint64_t, Entry> map_;
};
LabelStates& label_states();

// E13, the story message window: the font scale at which a whole message (its lines as the data
// broke them; tags drawn as nothing) fits the window's box, and the box (in the label's units at the
// window's own FontSize 30 and line spacing 10, CEventScenarioMessageWindow::Show).
double story_scale(std::string_view message, const soa::text::MeasureText& measure, double box_w, double box_h);

// E10, the room a label's layout gives it (english.md 7.15): a node's rectangle in world units, y
// down; (x, y) is its anchor point, (ax, ay) the anchor as the node holds it (+0x84; ay from the top:
// Cocos Studio's AnchorPoint 1 reads 0), w x h its size.
// For a label, w is the natural width of its text (unshrunk) and `label` is set: a label sibling
// grows from its anchor too, so two labels that face each other share the gap between them.
struct NodeRect {
    double x, y, ax, ay, w, h;
    bool label;
    double left() const { return x - ax * w; }
    double right() const { return left() + w; }
    double top() const { return y - ay * h; }
    double centre_y() const { return top() + h / 2; }
};
enum class RoomBy { none, parent, sibling };
struct LayoutRoom {
    double k = 1;  // the largest scale of the label's natural width that keeps it in its room (1: fits)
    RoomBy by = RoomBy::none;
    // the free band above and below the label (world y): its frame's box and the siblings above and
    // below it over its width (+-1e9: none)
    double frame_top = -1e9, frame_bottom = 1e9;
};
constexpr double kLayoutGap = 6;           // world units kept between a label and a sibling
constexpr double kLayoutPad = 6;           // and inside its parent's box
constexpr double kMinSiblingScale = 0.4;   // a sibling that would need less is overlapped by design
constexpr double kMinParentScale = 0.3;    // (the same for a parent box)
// The scale k at which `self` (a label, its text at its natural width) runs neither into a shown
// sibling on its row (the label's vertical centre within half a height of the sibling's; a sibling
// that spans the label's anchor, such as a background plate, is not in the way) nor out of the box
// of `parent` (when the parent has a size and holds the label's anchor). A label grows from its
// anchor: only the part of it on a sibling's side counts. Siblings and the parent are given shown
// (hidden ones left out by the caller).
LayoutRoom layout_room(const NodeRect& self, const NodeRect* parent, const std::vector<NodeRect>& siblings);
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
