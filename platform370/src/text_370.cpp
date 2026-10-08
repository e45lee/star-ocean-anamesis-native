// --lang en, the client's text (platform370::install_language; docs/PLAN-english.md E10;
// docs/client-changes.md "English mode"). Installed only with --lang en: with --lang ja the client
// is exactly as shipped.
//
// E10 (a), the hard-coded strings. libSOA.so shows 14 Japanese literals that are not master text
// (docs/english.md 1.5), from 10 functions: CErrorHandlerWrap::StrageShort, CGameDataDownloadError::
// Initialize / Progress, CMascotSelectDialog::Open, CDetailDialog_Other::Start (and 5 more
// CDetailDialog sites), CDetailDialog_Character::SetBattleSkillParam2 (and two lambdas),
// CPartyCompositionWeaponList / CPartyCompositionAccessoryList lambdas, CSortDialogWrapper::
// StartDialogFromProperty, CItemAlchemyPotal::InitializePotal. clang copied the literals' tails into
// the instructions (movk / byte stores), so neither .rodata nor a per-function patch of the
// literal reaches them all. Every one of them reaches the screen through one function,
// Framework::Cocos::CCocosLabel::SetText(std::string const&) (ELF 0x11d43c4): CUIUtility::SetText /
// SetButtonText / SetLabelText call it, CDialog's message and buttons are set on their labels
// through it, and CSortDialogWrapper and the LV%d習得 sites call it directly (work/decomp
// enc_e10 / enc_callees / enc_label). So that one function is hooked: when the text it is given is
// one of the literals (or one of the two formats with its number), it is replaced by the English of
// a new master_text id `port_en_*` (StringDB::Get; data/english/client-strings.tsv lists them; the
// server's English master carries them). When the master has no such row (a server without
// --english, the APK's built-in master before the first download) StringDB answers "not found" and
// the Japanese stays. Not covered: CPlayerInfo::Initialize's プレイヤー用ダミーネーム, a default
// value of the player's name property that the server's player data replaces before any screen
// shows it (it is never given to a label).
//
// E10 (b), word wrap. The client breaks lines only at \n (TTextCompositor<Utf8>::ComposeString_):
// a long English line runs off its box or the screen (english.md 2, experiment 2). CCocosLabel::
// DrawSelf (ELF 0x1eaca74) is hooked: before the original lays the label out, a line of its text
// that is wider than the label's room is broken at spaces (the text is set again with \n in it,
// through the original SetText), by the shared breaker (soa/line_break.h break_lines: existing breaks
// kept, Japanese lines left alone). The width is the client's own measure, CDirectAofTextRenderer::
// CalcStringRect(text, FontSize, line spacing) on the label's renderer, in the label's units, as
// DrawSelf measures it. The room:
//   - a label with IsCustomSize and a size: its box width, which DrawSelf would otherwise shrink the
//     text into or overflow;
//   - any other label (its size follows its text): the room on the screen, from the label's world
//     position, scale and anchor to the edges of the 720-wide design area, so a line never runs off
//     the screen.
// Lines with Japanese (kana, kanji, full-width forms) are left alone, as is a single word wider than
// the room, tag-mode labels (their <font> markup) and texts without a space.
//
// E12, the home's speech box (talk_menu_gp|talk_menu_talkmode/talk_frame/talk_text): instead of the
// wrap above, an English line is fitted to the box the Japanese was written for (480 x two lines):
// breaks collapsed, re-broken at the box's width, shrunk by DrawSelf's own fit (fit_talk below;
// english.md 7.11).
//
// E13, the story message window: the font of a message over the window's four lines is scaled down
// so the whole message fits (h_window_change below; english.md 7.13). The data breaks story lines;
// this code only scales them, and the E10 wrap leaves the window's labels alone.
//
// Who breaks what (english.md 7.13): master rows are broken by the data where the Japanese row has
// breaks (english_text.py finish), every other label by E10 at run time; the home's two talk labels
// by E12 at run time (their breaks are the box's, Global's are dropped); story lines by the data only
// (story_finish, the same breaker and the font's advances), the client only scales them (E13).
//
// The labels' fields are the recovered layout (platform370/cocos_layout.h). What the hooks remember
// per label (text::LabelStates) is forgotten by the label's destructor (CCocosLabel D0 / D1, hooked),
// so a reused address never inherits it; the results caches are bounded (text::LruCache).
#include <algorithm>
#include <atomic>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <soa/env.h>
#include <soa/line_break.h>

#include "core/cpu.h"
#include "core/loader.h"
#include "core/log.h"
#include "internal.h"
#include "platform370/cocos_layout.h"
#include "platform370/platform370.h"

namespace soa::platform370 {
namespace text {

// ---- E10 (a): the table ------------------------------------------------------------------------
// The literals as the client passes them (real line breaks), their new message ids and the
// function(s) they come from. data/english/client-strings.tsv holds the same ids with the English.
const std::vector<HardCoded>& hard_coded() {
    static const std::vector<HardCoded> t = {
        {"port_en_storage_short", "空き容量が不足しています。\n容量を確保して再起動してください。", "CErrorHandlerWrap::StrageShort"},
        {"port_en_download_storage_short", "空き容量が不足しています。\n%dMBの空きが必要です。", "CGameDataDownloadError::Progress"},
        {"port_en_close", "閉じる", "CGameDataDownloadError::Initialize"},
        {"port_en_mascot_select", "変更するホームマスコットを選択してください。", "CMascotSelectDialog::Open"},
        {"port_en_show_3d_model", "3Dモデル表示", "CDetailDialog_Other::Start, CDetailDialog sites"},
        {"port_en_skill_learn_lv", "LV%d習得", "CDetailDialog_Character::SetBattleSkillParam2, CPartyCompositionEvolution"},
        {"port_en_equip_swap_confirm", "装備の入れ替えを行います\nよろしいですか？", "CPartyCompositionWeaponList / AccessoryList"},
        {"port_en_sort_filter", "フィルター", "CSortDialogWrapper::StartDialogFromProperty"},
        {"port_en_sort_order", "並び替え", "CSortDialogWrapper::StartDialogFromProperty"},
        {"port_en_unknown_item", "？？？", "CItemAlchemyPotal::InitializePotal"},
    };
    return t;
}

namespace {
// "pre%dpost" matched against "pre<digits>post": the number, or false.
bool match_format(std::string_view fmt, std::string_view s, long* n) {
    size_t d = fmt.find("%d");
    std::string_view pre = fmt.substr(0, d), post = fmt.substr(d + 2);
    if (s.size() <= pre.size() + post.size() || s.substr(0, pre.size()) != pre || s.substr(s.size() - post.size()) != post) return false;
    std::string_view mid = s.substr(pre.size(), s.size() - pre.size() - post.size());
    if (mid.empty() || mid.size() > 9) return false;
    for (char ch : mid)
        if (ch < '0' || ch > '9') return false;
    *n = std::stol(std::string(mid));
    return true;
}
// An English template with exactly one %d and no other conversion ("%%" allowed).
bool one_int_template(const std::string& en) {
    int ints = 0;
    for (size_t i = 0; i < en.size(); i++)
        if (en[i] == '%') {
            if (i + 1 < en.size() && en[i + 1] == '%') i++;
            else if (i + 1 < en.size() && en[i + 1] == 'd') ints++, i++;
            else return false;
        }
    return ints == 1;
}
}  // namespace

bool english_for(std::string_view s, const Lookup& lookup, std::string* out) {
    for (const HardCoded& h : hard_coded()) {
        std::string_view ja = h.ja;
        bool fmt = ja.find("%d") != std::string_view::npos;
        long n = 0;
        if (fmt ? !match_format(ja, s, &n) : s != ja) continue;
        std::string en;
        if (!lookup(h.id, &en) || en.empty()) return false;  // no English row: the Japanese stays
        if (!fmt) {
            *out = en;
            return true;
        }
        if (!one_int_template(en)) return false;
        char buf[512];
        snprintf(buf, sizeof buf, en.c_str(), (int)n);
        *out = buf;
        return true;
    }
    return false;
}

// ---- shared state --------------------------------------------------------------------------------
double fit_scale(double tw, double th, double bw, double bh) {
    double k = 1;
    if (tw > bw && tw > 0) k = bw / tw;
    if (th > bh && th > 0 && bh / th < k) k = bh / th;
    return k;
}

bool LabelStates::original_of(uint64_t label, std::string_view current, std::string* original) {
    std::lock_guard<std::mutex> l(mu_);
    auto it = map_.find(label);
    if (it == map_.end() || !it->second.has_text || it->second.produced != current) return false;
    *original = it->second.original;
    return true;
}
void LabelStates::set(uint64_t label, std::string produced, std::string original) {
    std::lock_guard<std::mutex> l(mu_);
    Entry& e = map_[label];
    e.produced = std::move(produced), e.original = std::move(original), e.has_text = true;
}
void LabelStates::erase_text(uint64_t label) {
    std::lock_guard<std::mutex> l(mu_);
    auto it = map_.find(label);
    if (it == map_.end()) return;
    it->second.has_text = false, it->second.produced.clear(), it->second.original.clear();
    if (!it->second.has_box && !it->second.story) map_.erase(it);
}
void LabelStates::keep_box(uint64_t label, const Box& own) {
    std::lock_guard<std::mutex> l(mu_);
    Entry& e = map_[label];
    if (!e.has_box) e.box = own, e.has_box = true;
}
bool LabelStates::take_box(uint64_t label, Box* own) {
    std::lock_guard<std::mutex> l(mu_);
    auto it = map_.find(label);
    if (it == map_.end() || !it->second.has_box) return false;
    *own = it->second.box;
    it->second.has_box = false;
    if (!it->second.has_text && !it->second.story) map_.erase(it);
    return true;
}
void LabelStates::mark_story(uint64_t label) {
    std::lock_guard<std::mutex> l(mu_);
    map_[label].story = true;
}
bool LabelStates::is_story(uint64_t label) {
    std::lock_guard<std::mutex> l(mu_);
    auto it = map_.find(label);
    return it != map_.end() && it->second.story;
}
void LabelStates::forget(uint64_t label) {
    std::lock_guard<std::mutex> l(mu_);
    map_.erase(label);
}
size_t LabelStates::size() {
    std::lock_guard<std::mutex> l(mu_);
    return map_.size();
}
LabelStates& label_states() {
    static LabelStates s;
    return s;
}

double story_scale(std::string_view message, const soa::text::MeasureText& measure, double box_w, double box_h) {
    soa::text::Extent e = measure(message);
    return fit_scale(e.w, e.h, box_w, box_h);
}

}  // namespace text

namespace {

using cocos::CCocosLabel;
using soa::text::has_japanese;

// ---- the guest side -----------------------------------------------------------------------------
constexpr const char* kSetText =
    "_ZN9Framework5Cocos11CCocosLabel7SetTextERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_"
    "22CSTLStringAllocatorInfEEEEE";
constexpr const char* kDrawSelf = "_ZN9Framework5Cocos11CCocosLabel8DrawSelfEv";
constexpr const char* kLabelD1 = "_ZN9Framework5Cocos11CCocosLabelD1Ev";
constexpr const char* kLabelD0 = "_ZN9Framework5Cocos11CCocosLabelD0Ev";
constexpr const char* kParseMessage =
    "_ZN13EventScenario14CEventScenario12ParseMessageERNSt6__ndk111__wrap_iterIPNS0_12tCommandDataEEE";
constexpr const char* kWindowChange = "_ZN13EventScenario27CEventScenarioMessageWindow6ChangeEPKcS2_S2_";
constexpr const char* kCalcStringRect = "_ZNK9Framework22CDirectAofTextRenderer14CalcStringRectEPKcff";
constexpr const char* kGetWorldMatrix = "_ZNK9Framework5Cocos10CCocosNode14GetWorldMatrixEb";
constexpr const char* kPutPRS = "_ZNK9Framework7CMatrix6PutPRSEPNS_7CVectorEPNS_11CQuaternionES2_";
constexpr const char* kParamManager = "_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE";
constexpr const char* kPStringDB = "_ZNK17CParameterManager9pStringDBEv";
constexpr const char* kStringDBGet = "_ZN8StringDB3GetEPKcPb";
constexpr const char* kFree = "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv";
constexpr const char* kCryptName =
    "_ZN22CParameterPropertyBaseILj53EE11CryptStringINSt6__ndk112basic_stringIcNS2_11char_traitsIcEEN9Framework13CSTLAllocator"
    "IcNS6_22CSTLStringAllocatorInfEEEEEEEvRT_RKSB_";
// The entries the hooks expect (3.7.0's first two instructions): SetText stp x25, x24, [sp, #-0x40]!;
// stp x23, x22, [sp, #0x10]. DrawSelf stp d15, d14, [sp, #-0xa0]!; stp d13, d12, [sp, #0x10]. The
// label's D1 and D0 stp x19, x30, [sp, #-0x10]!; mov x19, x0. ParseMessage stp d9, d8, [sp, #-0x70]!;
// stp x28, x27, [sp, #0x10]. CEventScenarioMessageWindow::Change sub sp, sp, #0x70; str x26, [sp, #0x20].
constexpr u32 kSetTextEntry[2] = {0xa9bc63f9, 0xa9015bf7}, kDrawSelfEntry[2] = {0x6db63bef, 0x6d0133ed};
constexpr u32 kLabelDtorEntry[2] = {0xa9bf7bf3, 0xaa0003f3}, kParseMessageEntry[2] = {0x6db923e9, 0xa9016ffc};
constexpr u32 kChangeEntry[2] = {0xd101c3ff, 0xf90013fa};

// The design area's width in world units (the scene root of every layout is 720 wide).
constexpr float kScreenW = 720.f, kMargin = 12.f;

u64 g_set_text = 0, g_draw_self = 0, g_d1 = 0, g_d0 = 0, g_parse = 0, g_change = 0;
u64 g_calc = 0, g_world = 0, g_prs = 0, g_pm = 0, g_pstringdb = 0, g_get = 0, g_free = 0, g_crypt_name = 0;

CCocosLabel* as_label(u64 a) { return (CCocosLabel*)(uintptr_t)a; }

// A guest libc++ string (24 bytes) at `s`.
std::string_view guest_string(u64 s) { return ((const cocos::GuestString*)(uintptr_t)s)->view(); }
// A temporary guest string over host memory, for callees that only read it (SetText copies).
struct TempGuestString {
    alignas(8) u8 b[24] = {};
    explicit TempGuestString(const std::string& s) {
        if (s.size() < 23) {
            b[0] = (u8)(s.size() << 1);
            std::memcpy(b + 1, s.data(), s.size());
        } else {
            u64 w[3] = {((s.size() + 16) & ~15ull) | 1, s.size(), (u64)s.c_str()};
            std::memcpy(b, w, 24);
        }
    }
    u64 addr() const { return (u64)b; }
};
// A guest string a callee filled (x8 or an out argument): its text, and its heap freed.
std::string take_guest_string(u8* res) {
    std::string v(guest_string((u64)res));
    if (res[0] & 1) guest_call(g_free, {*(const u64*)(res + 16)});
    return v;
}

// StringDB::Get(id, &found) on the client's StringDB; false when there is none yet or no row.
bool stringdb_get(const char* id, std::string* out) {
    u64 pm = *(const u64*)g_pm;
    if (!pm) return false;
    u64 db = guest_call(g_pstringdb, {pm});
    if (!db) return false;
    alignas(8) u8 res[24] = {};
    u8 found = 0;
    u64 ints[3] = {db, (u64)id, (u64)&found};
    guest_call_raw(g_get, ints, 3, nullptr, 0, (u64)res);
    std::string v = take_guest_string(res);
    if (found) *out = std::move(v);
    return found != 0;
}

std::mutex g_mu;  // g_en, g_logged
std::unordered_map<std::string, std::string> g_en;  // port_en_* id -> English (10 ids: bounded)
std::unordered_set<std::string> g_logged;            // log-once keys (bounded by kLogOnce)
constexpr size_t kLogOnce = 4096;

// true the first time `key` is seen (while fewer than kLogOnce keys were logged): log lines once.
bool first_time(const std::string& key) {
    std::lock_guard<std::mutex> l(g_mu);
    return g_logged.size() < kLogOnce && g_logged.insert(key).second;
}

bool lookup_cached(const char* id, std::string* out) {
    {
        std::lock_guard<std::mutex> l(g_mu);
        auto it = g_en.find(id);
        if (it != g_en.end()) return *out = it->second, true;
    }
    if (!stringdb_get(id, out)) return false;
    std::lock_guard<std::mutex> l(g_mu);
    if (g_en.size() < 256) g_en[id] = *out;
    return true;
}

// The cheap pre-check: could this text be one of the literals? (their first bytes and lengths)
bool maybe_hard_coded(std::string_view s) {
    static const auto first = [] {
        std::vector<bool> f(256);
        for (const text::HardCoded& h : text::hard_coded()) f[(unsigned char)h.ja[0]] = true;
        return f;
    }();
    return s.size() >= 3 && s.size() <= 160 && first[(unsigned char)s[0]];
}

void set_text(u64 label, const std::string& s) {
    TempGuestString t(s);
    u64 ints[2] = {label, t.addr()};
    guest_call_raw(g_set_text, ints, 2, nullptr, 0, 0);
}

// u64* CCocosLabel::SetText(std::string const&): x0 label, x1 the text.
void h_set_text(Cpu& c) {
    u64 label = c.x(0), str = c.x(1);
    std::string_view s = guest_string(str);
    std::string en;
    if (maybe_hard_coded(s) && text::english_for(s, lookup_cached, &en)) {
        if (first_time(std::string(s)))
            LOGI("p370", "lang: hard-coded text \"%.*s\" -> \"%s\" (port_en_*, StringDB)", (int)s.size(), s.data(), en.c_str());
        TempGuestString t(en);
        u64 ints[2] = {label, t.addr()};
        c.set_x(0, guest_call_raw(g_set_text, ints, 2, nullptr, 0, 0).x0);
        return;
    }
    u64 ints[2] = {label, str};
    c.set_x(0, guest_call_raw(g_set_text, ints, 2, nullptr, 0, 0).x0);
}

// The size of `text` (all its lines) as DrawSelf measures it, in the label's units.
soa::text::Extent measure(u64 renderer, float font, float spacing, std::string_view text) {
    std::string z(text);
    float r[4] = {};
    u64 ints[2] = {renderer, (u64)z.c_str()};
    V128 v[2] = {};
    std::memcpy(&v[0], &font, 4);
    std::memcpy(&v[1], &spacing, 4);
    guest_call_raw(g_calc, ints, 2, v, 2, (u64)r);
    return {r[0], r[1]};
}
// A measure at the label's own font.
soa::text::MeasureText label_measure(const CCocosLabel* l) {
    u64 renderer = l->m_renderer;
    float font = l->m_fontSize, spacing = l->m_lineSpacing;
    return [=](std::string_view t) { return measure(renderer, font, spacing, t); };
}

struct Geometry {
    float x, y, scale, anchor;
};

// The room a label's lines may take, in its units (0: unknown, don't wrap).
float room(u64 label, Geometry* g) {
    const CCocosLabel* l = as_label(label);
    if (l->m_customSize && l->m_width > 0) return l->m_width;
    u64 m = guest_call(g_world, {label, 1});
    if (!m) return 0;
    alignas(16) float pos[4] = {}, scale[4] = {};
    guest_call(g_prs, {m, (u64)pos, 0, (u64)scale});
    float sx = scale[0] < 0 ? -scale[0] : scale[0];
    if (sx < 0.2f) return 0;  // opening animations: wait for the label's real size
    // A label that grows with its text is laid out from its anchor; one with the anchor at 0 and right
    // or centred alignment grows left or both ways (the menus' header descriptions: anchor 0,
    // HT_Right, the text ending at x), so its room is on that side.
    float ax = l->m_anchorX, x = pos[0];
    if (ax == 0 && l->m_hAlign == 2) ax = 1;
    else if (ax == 0 && l->m_hAlign == 1) ax = 0.5f;
    float right = kScreenW - kMargin - x, left = x - kMargin;
    float r = 1e9f;
    if (ax < 1) r = right / (1 - ax);
    if (ax > 0 && left / ax < r) r = left / ax;
    if (r < 48) return 0;  // off the screen, or scrolled away: leave it
    *g = {x, pos[1], sx, ax};
    return r / sx;
}

// Results by input: (text, room) -> wrapped; (talk text, box height) -> fitted; (font, spacing) ->
// a box height; (story message, font) -> its scale. Bounded (least recently used out).
text::LruCache<std::string> g_wrapped(4096), g_fitted(4096);
text::LruCache<double> g_heights(64), g_story_scales(4096);

// ---- E12: the home's speech box ------------------------------------------------------------------
// CHome::PlayTalk (@01aef4e8) writes the home and Talk Mode lines into talk_menu_gp/talk_frame/
// talk_text and talk_menu_talkmode/talk_frame/talk_text of UI/etc2/home.csf (the only code that
// names them): FontSize 24, no IsCustomSize, so the label takes its text's size and English lines of
// 3-7 lines run out of the 540x120 frame over the home's buttons (english.md 7.11). For these two
// labels only, an English text is laid out for the box the Japanese was written for: its line breaks
// collapsed, re-broken at the box's width and shrunk by DrawSelf's own fit (IsCustomSize +0x280 and
// shrink +0x282 switched on, the box at +0x94/+0x98) so it stays inside. A Japanese text (a row
// without English) gets the label's own fields back.
// The box: 480 wide, the placeholder's width in home.csf (20 full-width characters at FontSize 24;
// (b) client evidence, the layout data), and two lines high, as CalcStringRect measures two lines
// of the label's font (every Japanese home line is written for two lines; 7.11).
constexpr float kTalkBoxW = 480.f;

bool is_talk_text(const CCocosLabel* l) {
    if (l->name() != "talk_text") return false;
    const cocos::CCocosNode* frame = l->parent();
    if (!frame || frame->m_name.view() != "talk_frame") return false;
    const cocos::CCocosNode* menu = (const cocos::CCocosNode*)(uintptr_t)frame->m_parent;
    std::string_view m = menu ? menu->m_name.view() : std::string_view();
    return m == "talk_menu_gp" || m == "talk_menu_talkmode";
}

void set_box(CCocosLabel* l, const text::LabelStates::Box& b) {
    if (l->m_customSize == b.custom && l->m_shrink == b.shrink && l->m_width == b.w && l->m_height == b.h) return;
    l->m_customSize = b.custom, l->m_shrink = b.shrink;
    l->m_width = b.w, l->m_height = b.h;
    l->m_flags |= cocos::kRelayoutFlags;
}

// SOA_TEST_TALK_IDS=id,id,..: a test switch for the proof shots (docs/environment.md): each new line
// the game writes into the box is replaced by the master text of the next of these message ids
// (in turn, from the first again after the last), so a run shows chosen lines.
std::string test_talk_line() {
    static const std::vector<std::string> ids = soa::env::env_list("SOA_TEST_TALK_IDS");
    static std::atomic<size_t> next{0};
    if (ids.empty()) return {};
    std::string id = ids[next++ % ids.size()], v;
    if (!lookup_cached(id.c_str(), &v)) LOGW("p370", "lang: SOA_TEST_TALK_IDS: no master text %s", id.c_str());
    else LOGI("p370", "lang: SOA_TEST_TALK_IDS: the home talk line is %s", id.c_str());
    return v;
}

// Two lines of the label's font, as CalcStringRect measures them (cached per font and spacing).
double lines_height(const CCocosLabel* l, int lines) {
    std::string key = std::to_string(l->m_fontSize) + '/' + std::to_string(l->m_lineSpacing) + '/' + std::to_string(lines);
    double h;
    if (g_heights.get(key, &h)) return h;
    std::string probe = "\xef\xbc\x91";  // "１"
    for (int i = 1; i < lines; i++) probe += "\n\xef\xbc\x91";
    h = label_measure(l)(probe).h;
    g_heights.put(key, h);
    return h;
}

void fit_talk(u64 label) {
    CCocosLabel* l = as_label(label);
    text::LabelStates& st = text::label_states();
    std::string_view s = l->text();
    std::string src;
    bool ours = st.original_of(label, s, &src);
    if (!ours) src = std::string(s);
    if (!ours && !src.empty()) {
        std::string t = test_talk_line();
        if (!t.empty()) src = t;
    }
    if (!l->m_renderer || l->m_tagMode || src.empty() || has_japanese(src)) {
        text::LabelStates::Box own;
        if (st.take_box(label, &own)) set_box(l, own);
        st.erase_text(label);
        return;
    }
    double box_h = lines_height(l, 2);
    std::string key = src + '\x01' + std::to_string(box_h), out;
    if (!g_fitted.get(key, &out)) {
        soa::text::BoxFit f = soa::text::fit_box(src, kTalkBoxW, box_h, label_measure(l));
        out = f.text;
        g_fitted.put(key, out);
        if (first_time("\x02" + src)) {
            std::string shown = out;  // the lines as laid out, " | " between them
            for (size_t p = 0; (p = shown.find('\n', p)) != std::string::npos; p += 3) shown.replace(p, 1, " | ");
            LOGI("p370", "lang: fitted a home talk line to %.0fx%.0f at %.0f%% (font %.1f): \"%s\"", kTalkBoxW, box_h, f.scale * 100,
                 l->m_fontSize * f.scale, shown.c_str());
        }
    }
    st.keep_box(label, {l->m_customSize, l->m_shrink, l->m_width, l->m_height});
    st.set(label, out, src);  // (kept when out == src too: SOA_TEST_TALK_IDS tells its lines from the game's)
    set_box(l, {1, 1, kTalkBoxW, (float)box_h});
    if (out != s) set_text(label, out);
}

void story_draw(u64 label);  // (E13, below)
// The wrap's verdict for a short label shrunk on one line (a value no text has).
const std::string kShrinkOneLine = std::string("\x01shrink", 7);
void story_forget(u64 label);

// ---- E10 (b): the label wrap ---------------------------------------------------------------------
// The story message window's labels are E13's (the data breaks their lines, the window scales its
// font): the wrap leaves them alone, so a text revealed a character at a time is never broken
// differently from the whole line. Append's clones of the window's label are named "AppendMessage".
// The header description of a menu (UI/etc2/*_common.csf Node_1|Node_maintitle/Text_2,
// gacha_main.csf subtitle/text2): one line in the header bar beside the title.
bool is_header_description(const CCocosLabel* l) {
    std::string_view n = l->name();
    if (n != "Text_2" && n != "text2") return false;
    const cocos::CCocosNode* p = l->parent();
    std::string_view pn = p ? p->m_name.view() : std::string_view();
    return pn == "Node_1" || pn == "Node_maintitle" || pn == "subtitle";
}

// Labels that slide in are first drawn away from their place: a screen label is wrapped only once it
// is drawn twice at the same world x (until then it is laid out again each frame).
std::mutex g_x_mu;
std::unordered_map<u64, float> g_last_x;
bool settled(CCocosLabel* l, u64 label, float x) {
    std::lock_guard<std::mutex> lk(g_x_mu);
    auto it = g_last_x.find(label);
    if (it != g_last_x.end() && it->second == x) return true;
    if (g_last_x.size() > 65536) g_last_x.clear();  // (destroyed labels are dropped by forget_label)
    g_last_x[label] = x;
    l->m_flags |= cocos::kRelayoutFlags;
    return false;
}

void maybe_wrap(u64 label) {
    CCocosLabel* l = as_label(label);
    if (is_talk_text(l)) return fit_talk(label);
    if (l->name() == "AppendMessage") return;
    if (text::label_states().is_story(label)) return story_draw(label);
    std::string_view s = l->text();
    {
        // a label this hook boxed (a short label shrunk to one line) whose text changed: its own box back
        std::string boxed;
        text::LabelStates::Box own;
        if (!l->m_customSize || text::label_states().original_of(label, s, &boxed)) {
        } else if (text::label_states().take_box(label, &own)) {
            set_box(l, own);
            text::label_states().erase_text(label);
        }
    }
    if (s.size() < 12 || l->m_tagMode || !l->m_renderer) return;
    bool space = s.find(' ') != std::string_view::npos;
    if (!space && s.find('\n') == std::string_view::npos) return;
    std::string src;
    if (!text::label_states().original_of(label, s, &src)) {
        if (!space) return;
        src = std::string(s);
    }
    Geometry g{};
    float r = room(label, &g);
    if (r <= 0) return;
    if (!l->m_customSize && !settled(l, label, g.x)) return;
    std::string key = src + '\x01' + std::to_string((int)r), out;
    if (!g_wrapped.get(key, &out)) {
        auto m = label_measure(l);
        bool fixed = l->m_customSize && l->m_shrink && l->m_height > 0;
        if (fixed && src.find('\n') == std::string::npos) {
            // A fixed box that shrinks its text (Part 4): re-broken at the box for the fewest lines at
            // the largest scale, then DrawSelf's own shrink (fit_box, as the home's talk box).
            out = soa::text::fit_box(src, r, l->m_height, m).text;
        } else if (!l->m_customSize && src.find('\n') == std::string::npos &&
                   (is_header_description(l) ? m(src).w * 0.5 <= r : std::count(src.begin(), src.end(), ' ') < 3 && m(src).w * 0.6 <= r) &&
                   m(src).w > r) {
            // A menu's header description (one line in the header bar: the Japanese is one line) or a
            // short label (up to three words: a name, a caption, a checkbox's text) wider than its
            // room: kept on one line and shrunk into it (below; to at least 50% / 60%, else wrapped),
            // not broken into lines that hang below the bar or a column of words.
            out = kShrinkOneLine;
        } else {
            soa::text::BreakOptions o;
            o.keep_breaks = true, o.skip_japanese = true, o.tags_are_words = false, o.balance = true;
            out = soa::text::break_lines(src, r, [&](std::string_view line) { return m(line).w; }, o);
            // A fixed-size label with its own breaks: keep the wrap only when the text then shrinks
            // less (one-line boxes such as buttons read better shrunk than broken).
            if (out != src && fixed) {
                soa::text::Extent eo = m(out), es = m(src);
                if (text::fit_scale(eo.w, eo.h, r, l->m_height) <= text::fit_scale(es.w, es.h, r, l->m_height) + 0.01) out = src;
            }
        }
        g_wrapped.put(key, out);
        if (out != src && first_time(src))  // once per text (a sliding label is wrapped at each step)
            LOGI("p370", "lang: %s a %s label's line to %.0f (world x %.0f y %.0f, scale %.2f, anchor %.2f, align %u): \"%.*s\"",
                 out == kShrinkOneLine ? "shrank" : "wrapped", l->m_customSize ? "fixed-size" : "screen", r, g.x, g.y, g.scale, g.anchor,
                 l->m_hAlign, (int)std::min<size_t>(src.size(), 80), src.data());
    }
    if (out == kShrinkOneLine) {
        // the label made a fixed box of the room's width and its one line's height, shrinking
        text::label_states().keep_box(label, {l->m_customSize, l->m_shrink, l->m_width, l->m_height});
        text::label_states().set(label, src, src);
        set_box(l, {1, 1, r, (float)label_measure(l)(src).h});
        if (std::string_view(src) != s) set_text(label, src);
        return;
    }
    if (out == s) return;
    if (out == src) text::label_states().erase_text(label);
    else text::label_states().set(label, out, src);
    set_text(label, out);
}

void forget_label(u64 label) {
    text::label_states().forget(label);
    story_forget(label);
    std::lock_guard<std::mutex> lk(g_x_mu);
    g_last_x.erase(label);
}

// bool CCocosLabel::DrawSelf(): x0 label.
void h_draw_self(Cpu& c) {
    u64 label = c.x(0);
    maybe_wrap(label);
    u64 ints[1] = {label};
    c.set_x(0, guest_call_raw(g_draw_self, ints, 1, nullptr, 0, 0).x0);
}

// CCocosLabel::~CCocosLabel (D1, and D0, which frees): the label's state goes with it.
void h_label_d1(Cpu& c) {
    u64 label = c.x(0);
    forget_label(label);
    u64 ints[1] = {label};
    c.set_x(0, guest_call_raw(g_d1, ints, 1, nullptr, 0, 0).x0);
}
void h_label_d0(Cpu& c) {
    u64 label = c.x(0);
    forget_label(label);
    u64 ints[1] = {label};
    c.set_x(0, guest_call_raw(g_d0, ints, 1, nullptr, 0, 0).x0);
}

// ---- E13: the story message window ----------------------------------------------------------------
// The window (CEventScenarioMessageWindow; tc_msgwin, tc_parse, tc_mprint in work/decomp) draws a
// message in one label (the window's +0x80, the scene's +0x128) that Show sets to FontSize 30 and
// line spacing 10, revealed a character at a time (CMessagePrint). The client never breaks lines and
// never shrinks it, so an English message of more than the window's four lines ran out of it.
// CEventScenario::ParseMessage, at the scenario's load (InitializeFromBuffer), turns each message
// into commands: MessageChange with the text up to the first tag, then MessageAppend for each colour
// segment, a clone of the label (named AppendMessage) placed after the text before it, Append
// measuring at the label's FontSize and spacing. So:
//   - ParseMessage (hooked; the original runs unchanged) gives the whole message: its id is the
//     command's string (+8, an index into the scenario's string list at +0x298 / +0x2a0) and its text
//     StringDB's. Each of its tag-free runs is remembered as a key to the whole message.
//   - CEventScenarioMessageWindow::Change (hooked; the original runs with the same arguments) looks
//     its text up, measures the whole message at Show's font (tags drawn as nothing, <player> as the
//     player's name) and sets the label's FontSize and spacing to Show's times
//     k = min(1, box w / w, box h / h), the scale DrawSelf's shrink would give a fixed box; the clones
//     Append makes copy them, and Append places them at that font. k = 1 restores Show's values.
// The box: 4 lines (the window's height for the Japanese: no Japanese line has more) of the label's
// font, as CalcStringRect measures them, and 600 units wide (the 480 font px at FontSize 24 that
// docs/english.md 7.6 measured on screen, at FontSize 30). The data breaks the lines (english_text.py
// story_finish: a line over four window lines is broken wider for the scale it will get, so the two
// agree); this code never breaks a line. A message with Japanese in it is left as shipped.
constexpr float kStoryFont = 30.f, kStorySpacing = 10.f, kStoryBoxW = 600.f;
constexpr int kStoryLines = 4;
text::LruCache<std::string> g_story_message(8192);  // a tag-free run of a message -> the whole message

// The tag-free runs of a message (the texts Change may be given), "\n" as a line break.
std::vector<std::string> message_runs(const std::string& m) {
    std::vector<std::string> runs;
    std::string cur;
    for (size_t i = 0; i < m.size();) {
        size_t t = soa::text::tag_at(m, i);
        if (t) {
            if (!cur.empty()) runs.push_back(cur), cur.clear();
            i += t;
        } else {
            cur += m[i++];
        }
    }
    if (!cur.empty()) runs.push_back(cur);
    return runs;
}
std::string unescape_breaks(std::string s) {
    for (size_t p = 0; (p = s.find("\\n", p)) != std::string::npos;) s.replace(p, 2, "\n");
    return s;
}
// The player's name (CParameterManager +0x6f8, CryptString as ParseMessage reads it for <player>).
std::string player_name() {
    u64 pm = *(const u64*)g_pm;
    if (!pm || !g_crypt_name) return "";
    alignas(8) u8 out[24] = {};
    guest_call(g_crypt_name, {(u64)out, pm + 0x6f8});
    return take_guest_string(out);
}
// The message as drawn: <player> as the name, every other tag as nothing.
std::string drawn_message(const std::string& m, const std::string& name) {
    std::string out;
    for (size_t i = 0; i < m.size();) {
        size_t t = soa::text::tag_at(m, i);
        if (t) {
            if (std::string_view(m).substr(i, t) == "<player>") out += name;
            i += t;
        } else {
            out += m[i++];
        }
    }
    return out;
}

// void CEventScenario::ParseMessage(__wrap_iter<tCommandData*>&): x0 the scenario, x1 the iterator.
void h_parse_message(Cpu& c) {
    u64 scen = c.x(0), it = c.x(1);
    u64 cmd = it ? *(const u64*)it : 0;
    if (cmd) {
        float fi = *(const float*)(cmd + 8);
        u64 count = *(const u64*)(scen + 0x2a0);
        if (fi >= 0 && fi < 1e9f && (u64)fi < count) {
            u64 node = *(const u64*)(scen + 0x298);
            for (u64 k = (u64)fi; k > 0 && node; k--) node = *(const u64*)(node + 8);
            std::string m;
            if (node && stringdb_get(std::string(guest_string(node + 0x10)).c_str(), &m) && !has_japanese(m)) {
                m = unescape_breaks(m);
                std::string name = player_name();
                std::string with_name;  // the runs with <player> already the name (ParseMessage joins them)
                for (size_t p = 0; p < m.size();) {
                    if (m.compare(p, 8, "<player>") == 0) with_name += name, p += 8;
                    else with_name += m[p++];
                }
                for (const std::string& r : message_runs(m)) g_story_message.put(r, m);
                for (const std::string& r : message_runs(with_name)) g_story_message.put(r, m);
            }
        }
    }
    u64 ints[2] = {scen, it};
    c.set_x(0, guest_call_raw(g_parse, ints, 2, nullptr, 0, 0).x0);
}

// SOA_TEST_STORY_TEXTS=FILE: a test switch for the proof shots (docs/environment.md): each message
// the window shows is replaced by the next line of FILE (\n in it a line break; in turn).
std::string test_story_text() {
    static const std::vector<std::string> lines = [] {
        std::vector<std::string> v;
        const char* f = soa::env::env_str("SOA_TEST_STORY_TEXTS");
        if (!f || !*f) return v;
        std::ifstream in(f);
        for (std::string s; std::getline(in, s);)
            if (!s.empty()) v.push_back(unescape_breaks(s));
        if (v.empty()) LOGW("p370", "lang: SOA_TEST_STORY_TEXTS: no lines in %s", f);
        return v;
    }();
    static std::atomic<size_t> next{0};
    return lines.empty() ? std::string() : lines[next++ % lines.size()];
}

void set_font(CCocosLabel* l, float font, float spacing) {
    if (l->m_fontSize == font && l->m_lineSpacing == spacing) return;
    l->m_fontSize = font, l->m_lineSpacing = spacing;
    l->m_flags |= cocos::kFontFlags;
}

// The whole message the window's label shows, per label, until its scale is set (the label gets its
// renderer only when it is first drawn: Change may come before that).
std::mutex g_story_mu;
std::unordered_map<u64, std::string> g_story_pending;

// The label's font for `whole` (Show's font times the scale); false when it can't be measured yet.
bool fit_story(u64 label, const std::string& whole) {
    CCocosLabel* l = as_label(label);
    double k = 1;
    if (!has_japanese(whole)) {
        std::string drawn = drawn_message(whole, player_name());
        if (!g_story_scales.get(drawn, &k)) {
            if (!l->m_renderer) return false;
            set_font(l, kStoryFont, kStorySpacing);  // measured at Show's font
            double box_h = lines_height(l, kStoryLines);
            k = text::story_scale(drawn, label_measure(l), kStoryBoxW, box_h);
            g_story_scales.put(drawn, k);
            if (k < 1 && first_time("\x03" + drawn)) {
                std::string shown = drawn;
                for (size_t p = 0; (p = shown.find('\n', p)) != std::string::npos; p += 3) shown.replace(p, 1, " | ");
                LOGI("p370", "lang: shrank a story message to %.0f%% (font %.1f) to fit %.0fx%.0f: \"%.100s\"", k * 100, kStoryFont * k,
                     kStoryBoxW, box_h, shown.c_str());
            }
        }
    }
    set_font(l, (float)(kStoryFont * k), (float)(kStorySpacing * k));
    return true;
}

// The window's label is drawn: a message Change couldn't measure yet is fitted now.
void story_draw(u64 label) {
    std::string whole;
    {
        std::lock_guard<std::mutex> lk(g_story_mu);
        auto it = g_story_pending.find(label);
        if (it == g_story_pending.end()) return;
        whole = std::move(it->second);
        g_story_pending.erase(it);
    }
    fit_story(label, whole);
}
void story_forget(u64 label) {
    std::lock_guard<std::mutex> lk(g_story_mu);
    g_story_pending.erase(label);
}

// bool CEventScenarioMessageWindow::Change(const char* text, const char* name, const char* voice).
void h_window_change(Cpu& c) {
    u64 win = c.x(0), text_p = c.x(1);
    std::string test = text_p ? test_story_text() : std::string();
    if (!test.empty()) {
        LOGI("p370", "lang: SOA_TEST_STORY_TEXTS: the message is \"%.60s\"", test.c_str());
        text_p = (u64)test.c_str();
    }
    u64 label = *(const u64*)(win + 0x80);
    if (label && text_p) {
        text::label_states().mark_story(label);
        std::string seg = unescape_breaks((const char*)text_p), whole;
        if (!test.empty() || !g_story_message.get(seg, &whole)) whole = seg;
        if (fit_story(label, whole)) {
            story_forget(label);
        } else {
            set_font(as_label(label), kStoryFont, kStorySpacing);
            std::lock_guard<std::mutex> lk(g_story_mu);
            g_story_pending[label] = whole;
        }
    }
    u64 ints[4] = {win, text_p, c.x(2), c.x(3)};
    c.set_x(0, guest_call_raw(g_change, ints, 4, nullptr, 0, 0).x0);
}

}  // namespace

bool text::master_text(const char* id, std::string* out) { return g_get && stringdb_get(id, out); }

namespace {

bool entry_is(u64 a, const u32* w) { return a && ((const u32*)a)[0] == w[0] && ((const u32*)a)[1] == w[1]; }

}  // namespace

void detail::install_text(LoadedLib& lib, std::vector<std::string>& hooks) {
    u64 set_text = lib.sym(kSetText), draw = lib.sym(kDrawSelf), d1 = lib.sym(kLabelD1), d0 = lib.sym(kLabelD0);
    u64 parse = lib.sym(kParseMessage), change = lib.sym(kWindowChange);
    g_calc = lib.sym(kCalcStringRect), g_world = lib.sym(kGetWorldMatrix), g_prs = lib.sym(kPutPRS);
    g_pm = lib.sym(kParamManager), g_pstringdb = lib.sym(kPStringDB), g_get = lib.sym(kStringDBGet), g_free = lib.sym(kFree);
    g_crypt_name = lib.sym(kCryptName);
    if (!entry_is(set_text, kSetTextEntry) || !entry_is(draw, kDrawSelfEntry) || !entry_is(d1, kLabelDtorEntry) ||
        !entry_is(d0, kLabelDtorEntry) || !g_calc || !g_world || !g_prs || !g_pm || !g_pstringdb || !g_get || !g_free) {
        LOGW("p370", "lang: CCocosLabel::SetText / DrawSelf / ~CCocosLabel aren't 3.7.0's; no English strings or word wrap");
        return;
    }
    g_set_text = make_original_trampoline(set_text);
    g_draw_self = make_original_trampoline(draw);
    g_d1 = make_original_trampoline(d1);
    g_d0 = make_original_trampoline(d0);
    if (!g_set_text || !g_draw_self || !g_d1 || !g_d0) fatal("platform370: CCocosLabel::SetText / DrawSelf / ~CCocosLabel's prologue can't be relocated");
    hook_guest_function(set_text, "CCocosLabel::SetText [platform370 --lang en: hard-coded strings]", h_set_text);
    hook_guest_function(draw, "CCocosLabel::DrawSelf [platform370 --lang en: word wrap]", h_draw_self);
    hook_guest_function(d1, "CCocosLabel::~CCocosLabel D1 [platform370 --lang en: the label's text state]", h_label_d1);
    hook_guest_function(d0, "CCocosLabel::~CCocosLabel D0 [platform370 --lang en: the label's text state]", h_label_d0);
    for (const char* h : {kSetText, kDrawSelf, kLabelD1, kLabelD0}) hooks.push_back(h);
    LOGI("p370", "lang: CCocosLabel::SetText hooked at %#llx (the %u hard-coded strings -> port_en_* master text), DrawSelf at "
         "%#llx (word wrap at spaces), its destructors",
         (unsigned long long)(set_text - lib.base), (unsigned)text::hard_coded().size(), (unsigned long long)(draw - lib.base));
    if (!entry_is(parse, kParseMessageEntry) || !entry_is(change, kChangeEntry) || !g_crypt_name) {
        LOGW("p370", "lang: CEventScenario::ParseMessage / CEventScenarioMessageWindow::Change aren't 3.7.0's; story messages not fitted");
        return;
    }
    g_parse = make_original_trampoline(parse);
    g_change = make_original_trampoline(change);
    if (!g_parse || !g_change) fatal("platform370: ParseMessage / CEventScenarioMessageWindow::Change's prologue can't be relocated");
    hook_guest_function(parse, "CEventScenario::ParseMessage [platform370 --lang en: the story's whole messages]", h_parse_message);
    hook_guest_function(change, "CEventScenarioMessageWindow::Change [platform370 --lang en: story font fit]", h_window_change);
    hooks.push_back(kParseMessage);
    hooks.push_back(kWindowChange);
    LOGI("p370", "lang: ParseMessage and CEventScenarioMessageWindow::Change hooked (story messages fitted to the window's 4 lines)");
}

}  // namespace soa::platform370
