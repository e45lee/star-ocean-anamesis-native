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
// through the original SetText). The width is the client's own measure, CDirectAofTextRenderer::
// CalcStringRect(text, FontSize, +0x260) on the label's renderer (+0xe8), in the label's units, as
// DrawSelf measures it. The room:
//   - a label with IsCustomSize (+0x280) and a size (+0x94 > 0): its box width, which DrawSelf
//     would otherwise shrink the text into (+0x282) or overflow;
//   - any other label (its size follows its text): the room on the screen, from the label's world
//     position, scale and anchor (+0x84) to the edges of the 720-wide design area, so a line never
//     runs off the screen.
// Lines with Japanese (kana, kanji, full-width forms) are left alone, as is a single word wider than
// the room, tag-mode labels (+0x281; their <font> markup) and texts without a space.
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "core/log.h"
#include "internal.h"
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

// ---- E10 (b): the wrap ---------------------------------------------------------------------------
namespace {
// Kana, kanji, CJK punctuation, full-width forms: a Japanese line (left as the original lays it out).
bool has_japanese(std::string_view s) {
    for (size_t i = 0; i < s.size(); i++) {
        unsigned char c = (unsigned char)s[i];
        if (c < 0xe0 || c >= 0xf0 || i + 2 >= s.size()) continue;
        unsigned cp = ((c & 0x0f) << 12) | (((unsigned char)s[i + 1] & 0x3f) << 6) | ((unsigned char)s[i + 2] & 0x3f);
        if ((cp >= 0x3000 && cp <= 0x30ff) || (cp >= 0x4e00 && cp <= 0x9fff) || (cp >= 0xff00 && cp <= 0xffef)) return true;
    }
    return false;
}
}  // namespace

std::string wrap(std::string_view text, float budget, const Measure& measure) {
    std::string out;
    size_t start = 0;
    while (start <= text.size()) {
        size_t nl = text.find('\n', start);
        std::string_view line = text.substr(start, nl == std::string_view::npos ? std::string_view::npos : nl - start);
        if (line.find(' ') == std::string_view::npos || has_japanese(line) || measure(line) <= budget) {
            out.append(line);
        } else {
            // greedy: words joined while the line fits; a word wider than the room stays whole
            std::string cur;
            size_t p = 0;
            bool first_line = true;
            while (p <= line.size()) {
                size_t sp = line.find(' ', p);
                std::string_view word = line.substr(p, sp == std::string_view::npos ? std::string_view::npos : sp - p);
                std::string cand = cur.empty() ? std::string(word) : cur + " " + std::string(word);
                if (!cur.empty() && measure(cand) > budget) {
                    if (!first_line) out += '\n';
                    out += cur;
                    first_line = false;
                    cur = std::string(word);
                } else {
                    cur = cand;
                }
                if (sp == std::string_view::npos) break;
                p = sp + 1;
            }
            if (!first_line) out += '\n';
            out += cur;
        }
        if (nl == std::string_view::npos) break;
        out += '\n';
        start = nl + 1;
    }
    return out;
}

}  // namespace text

namespace {

// ---- the guest side -----------------------------------------------------------------------------
constexpr const char* kSetText =
    "_ZN9Framework5Cocos11CCocosLabel7SetTextERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_"
    "22CSTLStringAllocatorInfEEEEE";
constexpr const char* kDrawSelf = "_ZN9Framework5Cocos11CCocosLabel8DrawSelfEv";
constexpr const char* kCalcStringRect = "_ZNK9Framework22CDirectAofTextRenderer14CalcStringRectEPKcff";
constexpr const char* kGetWorldMatrix = "_ZNK9Framework5Cocos10CCocosNode14GetWorldMatrixEb";
constexpr const char* kPutPRS = "_ZNK9Framework7CMatrix6PutPRSEPNS_7CVectorEPNS_11CQuaternionES2_";
constexpr const char* kParamManager = "_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE";
constexpr const char* kPStringDB = "_ZNK17CParameterManager9pStringDBEv";
constexpr const char* kStringDBGet = "_ZN8StringDB3GetEPKcPb";
constexpr const char* kFree = "_ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv";
// The entries the hooks expect (3.7.0): SetText stp x25, x24, [sp, #-0x40]!; stp x23, x22, [sp, #0x10];
// DrawSelf stp d15, d14, [sp, #-0xa0]!; stp d13, d12, [sp, #0x10].
constexpr u32 kSetTextEntry[2] = {0xa9bc63f9, 0xa9015bf7}, kDrawSelfEntry[2] = {0x6db63bef, 0x6d0133ed};

// CCocosLabel fields (work/decomp/enc_label: the constructor, Read_TextObjectData, DrawSelf).
constexpr u64 kAnchorX = 0x84, kWidth = 0x94, kRenderer = 0xe8, kText = 0x230, kFontSize = 0x258, kSpacing = 0x260;
constexpr u64 kHeight = 0x98, kCustomSize = 0x280, kTagMode = 0x281, kShrink = 0x282;
// The design area's width in world units (the scene root of every layout is 720 wide).
constexpr float kScreenW = 720.f, kMargin = 12.f;

u64 g_set_text = 0, g_draw_self = 0, g_calc = 0, g_world = 0, g_prs = 0, g_pm = 0, g_pstringdb = 0, g_get = 0, g_free = 0;

// A guest libc++ string (24 bytes): short form when bit 0 of byte 0 is clear.
std::string_view guest_string(u64 s) {
    const u8* p = (const u8*)s;
    if (!(p[0] & 1)) return {(const char*)p + 1, (size_t)(p[0] >> 1)};
    return {*(const char* const*)(p + 16), *(const u64*)(p + 8)};
}
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
    std::string_view v = guest_string((u64)res);
    bool ok = found != 0;
    if (ok) *out = std::string(v);
    if (res[0] & 1) guest_call(g_free, {*(const u64*)(res + 16)});
    return ok;
}

std::mutex g_mu;
std::unordered_map<std::string, std::string> g_en;  // message id -> English (rows found; a miss is asked again)
std::unordered_set<std::string> g_logged;

bool lookup_cached(const char* id, std::string* out) {
    {
        std::lock_guard<std::mutex> l(g_mu);
        auto it = g_en.find(id);
        if (it != g_en.end()) return *out = it->second, true;
    }
    if (!stringdb_get(id, out)) return false;
    std::lock_guard<std::mutex> l(g_mu);
    g_en[id] = *out;
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

// u64* CCocosLabel::SetText(std::string const&): x0 label, x1 the text.
void h_set_text(Cpu& c) {
    u64 label = c.x(0), str = c.x(1);
    std::string_view s = guest_string(str);
    std::string en;
    if (maybe_hard_coded(s) && text::english_for(s, lookup_cached, &en)) {
        {
            std::lock_guard<std::mutex> l(g_mu);
            if (g_logged.insert(std::string(s)).second)
                LOGI("p370", "lang: hard-coded text \"%.*s\" -> \"%s\" (port_en_*, StringDB)", (int)s.size(), s.data(), en.c_str());
        }
        TempGuestString t(en);
        u64 ints[2] = {label, t.addr()};
        c.set_x(0, guest_call_raw(g_set_text, ints, 2, nullptr, 0, 0).x0);
        return;
    }
    u64 ints[2] = {label, str};
    c.set_x(0, guest_call_raw(g_set_text, ints, 2, nullptr, 0, 0).x0);
}

// The size of `text` (all its lines) as DrawSelf measures it, in the label's units.
struct Size {
    float w, h;
};
Size measure(u64 renderer, float font, float spacing, std::string_view text) {
    std::string z(text);
    float r[4] = {};
    u64 ints[2] = {renderer, (u64)z.c_str()};
    V128 v[2] = {};
    std::memcpy(&v[0], &font, 4);
    std::memcpy(&v[1], &spacing, 4);
    guest_call_raw(g_calc, ints, 2, v, 2, (u64)r);
    return {r[0], r[1]};
}
// DrawSelf's shrink of a fixed-size label: min(1, boxW / w, boxH / h).
float fit_scale(Size t, float bw, float bh) {
    float k = 1;
    if (t.w > bw && t.w > 0) k = bw / t.w;
    if (t.h > bh && t.h > 0 && bh / t.h < k) k = bh / t.h;
    return k;
}

thread_local float g_last_geom[4];  // the last room()'s world x, scale, anchor, y (for the log)

// The room a label's lines may take, in its units (0: unknown, don't wrap).
float room(u64 label) {
    const u8* l = (const u8*)label;
    float w = *(const float*)(l + kWidth);
    if (l[kCustomSize] && w > 0) return w;
    u64 m = guest_call(g_world, {label, 1});
    if (!m) return 0;
    alignas(16) float pos[4] = {}, scale[4] = {};
    guest_call(g_prs, {m, (u64)pos, 0, (u64)scale});
    float sx = scale[0] < 0 ? -scale[0] : scale[0];
    if (sx < 0.2f) return 0;  // opening animations: wait for the label's real size
    float ax = *(const float*)(l + kAnchorX), x = pos[0];
    float right = kScreenW - kMargin - x, left = x - kMargin;
    float room = 1e9f;
    if (ax < 1) room = right / (1 - ax);
    if (ax > 0 && left / ax < room) room = left / ax;
    if (room < 48) return 0;  // off the screen, or scrolled away: leave it
    g_last_geom[0] = x, g_last_geom[1] = sx, g_last_geom[2] = ax, g_last_geom[3] = pos[1];
    return room / sx;
}

// Wrapped texts by (text, room); per label, the text this hook set and the text it was made from, so
// a label that moves (a layout placing it after its first draw) is wrapped again from its original.
std::unordered_map<std::string, std::string> g_wrapped;
struct Set {
    std::string produced, original;
};
std::unordered_map<u64, Set> g_set;

void maybe_wrap(u64 label) {
    const u8* l = (const u8*)label;
    std::string_view s = guest_string(label + kText);
    if (s.size() < 12 || l[kTagMode]) return;
    bool space = s.find(' ') != std::string_view::npos;
    if (!space && s.find('\n') == std::string_view::npos) return;
    u64 renderer = *(const u64*)(l + kRenderer);
    if (!renderer) return;
    std::string src;
    {
        std::lock_guard<std::mutex> lk(g_mu);
        auto it = g_set.find(label);
        if (it != g_set.end() && it->second.produced == s) src = it->second.original;
        else if (!space) return;
        else src = std::string(s);
    }
    float r = room(label);
    if (r <= 0) return;
    std::string key = src + '\x01' + std::to_string((int)r);
    std::string out;
    bool cached = false;
    {
        std::lock_guard<std::mutex> lk(g_mu);
        auto it = g_wrapped.find(key);
        if (it != g_wrapped.end()) out = it->second, cached = true;
    }
    if (!cached) {
        float font = *(const float*)(l + kFontSize), spacing = *(const float*)(l + kSpacing);
        out = text::wrap(src, r, [&](std::string_view line) { return measure(renderer, font, spacing, line).w; });
        // A fixed-size label that shrinks its text to fit (+0x282): keep the wrap only when the text
        // then shrinks less (one-line boxes such as buttons read better shrunk than broken).
        float bh = *(const float*)(l + kHeight);
        if (out != src && l[kCustomSize] && l[kShrink] && bh > 0 &&
            fit_scale(measure(renderer, font, spacing, out), r, bh) <= fit_scale(measure(renderer, font, spacing, src), r, bh) + 0.01f)
            out = src;
        std::lock_guard<std::mutex> lk(g_mu);
        if (g_wrapped.size() > 4096) g_wrapped.clear();
        g_wrapped[key] = out;
        if (out != src && g_logged.insert(src).second)  // once per text (a sliding label is wrapped at each step)
            LOGI("p370", "lang: wrapped a %s label's line to %.0f (world x %.0f y %.0f, scale %.2f, anchor %.2f): \"%.*s\"",
                 l[kCustomSize] ? "fixed-size" : "screen", r, g_last_geom[0], g_last_geom[3], g_last_geom[1], g_last_geom[2],
                 (int)std::min<size_t>(src.size(), 80), src.data());
    }
    if (out == s) return;
    {
        std::lock_guard<std::mutex> lk(g_mu);
        if (out == src) g_set.erase(label);
        else {
            if (g_set.size() > 8192) g_set.clear();
            g_set[label] = {out, src};
        }
    }
    TempGuestString t(out);
    u64 ints[2] = {label, t.addr()};
    guest_call_raw(g_set_text, ints, 2, nullptr, 0, 0);
}

// bool CCocosLabel::DrawSelf(): x0 label.
void h_draw_self(Cpu& c) {
    u64 label = c.x(0);
    maybe_wrap(label);
    u64 ints[1] = {label};
    c.set_x(0, guest_call_raw(g_draw_self, ints, 1, nullptr, 0, 0).x0);
}

}  // namespace

bool text::master_text(const char* id, std::string* out) { return g_get && stringdb_get(id, out); }

namespace {

bool entry_is(u64 a, const u32* w) { return a && ((const u32*)a)[0] == w[0] && ((const u32*)a)[1] == w[1]; }

}  // namespace

void detail::install_text(LoadedLib& lib, std::vector<std::string>& hooks) {
    u64 set_text = lib.sym(kSetText), draw = lib.sym(kDrawSelf);
    g_calc = lib.sym(kCalcStringRect), g_world = lib.sym(kGetWorldMatrix), g_prs = lib.sym(kPutPRS);
    g_pm = lib.sym(kParamManager), g_pstringdb = lib.sym(kPStringDB), g_get = lib.sym(kStringDBGet), g_free = lib.sym(kFree);
    if (!entry_is(set_text, kSetTextEntry) || !entry_is(draw, kDrawSelfEntry) || !g_calc || !g_world || !g_prs || !g_pm ||
        !g_pstringdb || !g_get || !g_free) {
        LOGW("p370", "lang: CCocosLabel::SetText / DrawSelf aren't 3.7.0's; no English strings or word wrap");
        return;
    }
    g_set_text = make_original_trampoline(set_text);
    g_draw_self = make_original_trampoline(draw);
    if (!g_set_text || !g_draw_self) fatal("platform370: CCocosLabel::SetText / DrawSelf's prologue can't be relocated");
    hook_guest_function(set_text, "CCocosLabel::SetText [platform370 --lang en: hard-coded strings]", h_set_text);
    hook_guest_function(draw, "CCocosLabel::DrawSelf [platform370 --lang en: word wrap]", h_draw_self);
    hooks.push_back(kSetText);
    hooks.push_back(kDrawSelf);
    LOGI("p370", "lang: CCocosLabel::SetText hooked at %#llx (the %u hard-coded strings -> port_en_* master text) and DrawSelf at "
         "%#llx (word wrap at spaces)",
         (unsigned long long)(set_text - lib.base), (unsigned)text::hard_coded().size(), (unsigned long long)(draw - lib.base));
}

}  // namespace soa::platform370
