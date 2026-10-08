// platform370's language settings (platform370/src/lang_370.cpp; test-only, nothing native):
// docs/PLAN-english.md B1 and B7.
//
// platform370/lang: the client's CLanguage singleton as the booted client has it, against the
// command line: Default 0x100; Current 1 (en) with --lang en, else 0x100 (as shipped); Voice 0 with
// --voice-lang ja (the default: BAS:VoiceLanguage = 0 written before the client started, read back by
// CUIUtility::EffectiveSetting). With --lang ja platform370 hooked nothing (language_hooks() empty,
// no "[platform370 --lang" hook among hooked_functions()); with --lang en the CLanguage hook is there.
// The file names the client tries: CLanguage::PostfixLanguageCodeFilepath(path, Current()) gives
// Font/etc2/font-en.fpk with --lang en and the name unchanged with --lang ja, and
// PostfixLanguageCodeFilepath(Sound/Voice_x.spk, Voice()) the bare name (no -en voice probe).
// Passes in the plain --selftest run (--lang ja) and in `--selftest platform370/lang --lang en`
// (tests/tiers.json "selftest-lang-en").
//
// platform370/lang-strings, lang-wrap, lang-label-state, lang-cache, lang-story-scale: the E10, E12
// and E13 rules as functions (the hard-coded strings' table against data/english/client-strings.tsv;
// the wrap; the per-label state; the caches; the story scale), independent of --lang.
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <map>
#include <set>
#include <string>

#include "core/cpu.h"
#include "core/paths.h"
#include "native/common/test.h"
#include "platform370/platform370.h"

namespace soa {
namespace {

constexpr const char* kPostfix = "_ZN9CLanguage27PostfixLanguageCodeFilepathERN9Framework13TStaticStringILm256EEENS_9tLanguageEb";

std::string postfixed(TestContext& t, const char* name, u32 lang) {
    char path[256] = {};
    std::strncpy(path, name, sizeof path - 1);
    t.call(kPostfix, {(u64)path, lang, 0});
    return path;
}

NATIVE_TEST("platform370/lang") {
    const bool en = platform370::language() == "en";
    u64 inst = *(const u64*)t.sym("_ZN9Framework10TSingletonI9CLanguageE11m_pInstanceE");
    if (!inst) {
        t.fail("no CLanguage instance (CGame::OnInitialize didn't run?)");
        return;
    }
    const u32* f = (const u32*)inst;
    const u32 want_current = en ? 1 : 0x100;
    if (f[0] != 0x100) t.fail("CLanguage Default %#x, want 0x100", f[0]);
    if (f[1] != want_current) t.fail("CLanguage Current %#x, want %#x (--lang %s)", f[1], want_current, platform370::language().c_str());
    // --voice-lang ja (the selftest's default): BAS:VoiceLanguage 0, so Voice 0
    if (f[2] != 0) t.fail("CLanguage Voice %#x, want 0 (--voice-lang ja)", f[2]);

    bool hooked = false;
    for (const HookedFunction& h : hooked_functions())
        if (h.name && std::strstr(h.name, "[platform370 --lang")) hooked = true;
    if (en != hooked) t.fail("platform370's language hooks %s with --lang %s", hooked ? "installed" : "missing", platform370::language().c_str());
    // --lang en: CLanguage::CLanguage, CCocosLabel::SetText (hard-coded strings), DrawSelf (wrap), its D1 / D0
    // (the per-label state), CEventScenario::ParseMessage and CEventScenarioMessageWindow::Change (the story fit)
    if (platform370::language_hooks().size() != (en ? 7u : 0u)) t.fail("language_hooks() has %zu entries", platform370::language_hooks().size());

    std::string font = postfixed(t, "Font/etc2/font.fpk", f[1]);
    std::string want_font = en ? "Font/etc2/font-en.fpk" : "Font/etc2/font.fpk";
    if (font != want_font) t.fail("PostfixLanguageCodeFilepath(font, Current) = %s, want %s", font.c_str(), want_font.c_str());
    std::string voice = postfixed(t, "Sound/Voice_TS_1010.spk", f[2]);
    if (voice != "Sound/Voice_TS_1010.spk") t.fail("PostfixLanguageCodeFilepath(voice, Voice) = %s, want the bare name", voice.c_str());
}

// data/english/client-strings.tsv: message_id -> en (the master's encoding: \n as two characters).
std::map<std::string, std::string> client_strings(TestContext& t) {
    std::map<std::string, std::string> m;
    std::string path = find_repo_file("data/english/client-strings.tsv");
    std::ifstream in(path);
    if (!in) {
        t.fail("data/english/client-strings.tsv not found");
        return m;
    }
    std::string line;
    std::getline(in, line);
    if (line != "message_id\ten\tnote") t.fail("client-strings.tsv: header \"%s\"", line.c_str());
    std::string last;
    while (std::getline(in, line)) {
        size_t a = line.find('\t'), b = line.find('\t', a + 1);
        if (a == std::string::npos || b == std::string::npos) {
            t.fail("client-strings.tsv: malformed line \"%s\"", line.c_str());
            continue;
        }
        std::string id = line.substr(0, a);
        if (id <= last) t.fail("client-strings.tsv: %s not sorted", id.c_str());
        if (id.rfind("port_en_", 0) != 0) t.fail("client-strings.tsv: %s isn't a port_en_ id", id.c_str());
        last = id;
        m[id] = line.substr(a + 1, b - a - 1);
    }
    return m;
}

// As StringDB::Get: the two characters \n become a line break.
std::string unescape(std::string s) {
    for (size_t p; (p = s.find("\\n")) != std::string::npos;) s.replace(p, 2, "\n");
    return s;
}

// The hard-coded strings' table (platform370 text_370.cpp) against client-strings.tsv, and the
// replacement rule: literal -> its English; a format with its number; no row -> the Japanese stays.
NATIVE_TEST("platform370/lang-strings") {
    std::map<std::string, std::string> tsv = client_strings(t);
    std::set<std::string> ids;
    for (const auto& h : platform370::text::hard_coded()) {
        ids.insert(h.id);
        if (!tsv.count(h.id)) t.fail("%s isn't in client-strings.tsv", h.id);
    }
    for (const auto& [id, en] : tsv)
        if (!ids.count(id)) t.fail("client-strings.tsv's %s isn't in the client's table", id.c_str());
    auto lookup = [&](const char* id, std::string* out) {
        auto it = tsv.find(id);
        if (it == tsv.end()) return false;
        *out = unescape(it->second);
        return true;
    };
    auto none = [](const char*, std::string*) { return false; };
    struct Case {
        const char* in;
        const char* want;  // nullptr: not replaced
    } cases[] = {
        {"閉じる", "Close"},
        {"フィルター", "Filter"},
        {"並び替え", "Sort"},
        {"？？？", "???"},
        {"LV12習得", "Learned at Lv. 12"},
        {"LV習得", nullptr},
        {"LVx2習得", nullptr},
        {"空き容量が不足しています。\n512MBの空きが必要です。", "Not enough free storage.\n512 MB of free space is needed."},
        {"空き容量が不足しています。\n容量を確保して再起動してください。", "Not enough free storage.\nFree up some space and restart the game."},
        {"装備の入れ替えを行います\nよろしいですか？", "Equipment will be swapped.\nProceed?"},
        {"閉じる ", nullptr},
        {"とじる", nullptr},
        {"", nullptr},
    };
    for (const Case& c : cases) {
        std::string out;
        bool got = platform370::text::english_for(c.in, lookup, &out);
        if (got != (c.want != nullptr) || (got && out != c.want)) t.fail("english_for(\"%s\") = %s \"%s\"", c.in, got ? "true" : "false", out.c_str());
        std::string o2;
        if (platform370::text::english_for(c.in, none, &o2)) t.fail("english_for(\"%s\") without a master row replaced it", c.in);
    }
    // a format whose English lost its %d (or has another conversion) keeps the Japanese
    auto bad = [](const char*, std::string* out) { return *out = "Learned at %s", true; };
    std::string o3;
    if (platform370::text::english_for("LV3習得", bad, &o3)) t.fail("english_for took an English with %%s");
}

// The label wrap's options (platform370 text_370.cpp maybe_wrap: soa::text::break_lines with the
// existing breaks kept and Japanese lines left alone) with a fixed-advance measure: 10 per byte. The
// breaker's own rules are common/tests/line_break_vectors.tsv (soa_text_tests).
NATIVE_TEST("platform370/lang-wrap") {
    auto m = [](std::string_view s) { return 10.0 * (double)s.size(); };
    soa::text::BreakOptions o;
    o.keep_breaks = true, o.skip_japanese = true, o.tags_are_words = false;
    struct Case {
        const char* in;
        double budget;
        const char* want;
    } cases[] = {
        {"aaa bbb ccc", 75, "aaa bbb\nccc"},
        {"aaa bbb ccc", 110, "aaa bbb ccc"},
        {"aaa bbb ccc", 30, "aaa\nbbb\nccc"},
        {"aaaaaaaaaa bb", 50, "aaaaaaaaaa\nbb"},              // a word wider than the room stays whole
        {"aaaaaaaaaaaa", 50, "aaaaaaaaaaaa"},                // no space
        {"aa bb\ncc dd ee ff", 50, "aa bb\ncc dd\nee ff"},  // each \n line on its own
        {"スタミナ は 既に 全回復 しています", 50, "スタミナ は 既に 全回復 しています"},  // Japanese: as the original
        {"HP 100 回復 and more words here", 50, "HP 100 回復 and more words here"},
        {"", 50, ""},
        {"a b\n\nc d", 20, "a\nb\n\nc\nd"},
    };
    for (const Case& c : cases) {
        std::string out = soa::text::break_lines(c.in, c.budget, m, o);
        if (out != c.want) t.fail("break_lines(\"%s\", %g) = \"%s\", want \"%s\"", c.in, c.budget, out.c_str(), c.want);
    }
}

// What the hooks remember per label (text::LabelStates; Part 1 of the text cleanup): a label's
// state dies with it. A freed label whose address a new label reuses must not hand the new one the
// old text's original (a re-wrap from the wrong text) or "restore" the old label's box. forget() is
// what the hooked CCocosLabel destructors (D0 / D1) call.
NATIVE_TEST("platform370/lang-label-state") {
    platform370::text::LabelStates st;
    const uint64_t a = 0x1000;
    std::string orig;
    st.set(a, "short\nline", "short line");
    if (!st.original_of(a, "short\nline", &orig) || orig != "short line") t.fail("original_of after set");
    if (st.original_of(a, "another text", &orig)) t.fail("original_of for a text the hook didn't set");
    st.keep_box(a, {0, 1, 0, 0});
    st.keep_box(a, {1, 1, 480, 55});  // the first box kept is the label's own
    st.forget(a);                      // ~CCocosLabel
    if (st.original_of(a, "short\nline", &orig)) t.fail("a reused address inherited the old label's text");
    platform370::text::LabelStates::Box b{};
    if (st.take_box(a, &b)) t.fail("a reused address got the old label's box back");
    if (st.size() != 0) t.fail("forget left %zu entries", st.size());
    st.keep_box(a, {0, 1, 12, 34});
    st.keep_box(a, {1, 1, 480, 55});
    if (!st.take_box(a, &b) || b.custom != 0 || b.w != 12 || b.h != 34) t.fail("take_box gave a box other than the label's own");
    if (st.take_box(a, &b)) t.fail("take_box twice");
    st.mark_story(a);
    if (!st.is_story(a) || st.is_story(a + 8)) t.fail("is_story");
    st.forget(a);
    if (st.is_story(a) || st.size() != 0) t.fail("forget kept the story mark");
}

// The text code's caches (text::LruCache) are bounded: the least recently used entry goes.
NATIVE_TEST("platform370/lang-cache") {
    platform370::text::LruCache<std::string> c(3);
    for (int i = 0; i < 3; i++) c.put("k" + std::to_string(i), "v" + std::to_string(i));
    std::string v;
    if (!c.get("k0", &v) || v != "v0") t.fail("get k0");  // k0 now the most recent
    c.put("k3", "v3");                                     // k1 goes
    if (c.size() != 3) t.fail("size %zu, want 3", c.size());
    if (c.get("k1", &v)) t.fail("k1 still cached");
    if (!c.get("k0", &v) || !c.get("k2", &v) || !c.get("k3", &v) || v != "v3") t.fail("the recent entries went");
    c.put("k3", "w3");
    if (!c.get("k3", &v) || v != "w3" || c.size() != 3) t.fail("put of an existing key");
}

// E13's scale (text::story_scale) on a fixed measure: 10 per byte, lines 40 apart and 30 high
// (h = 40 n - 10, Show's FontSize 30 + spacing 10), a 600 x 150 box (four lines).
NATIVE_TEST("platform370/lang-story-scale") {
    auto m = [](std::string_view s) {
        double w = 0, n = 1, cur = 0;
        for (char ch : s) {
            if (ch == '\n') n++, cur = 0;
            else w = std::max(w, cur += 10);
        }
        return soa::text::Extent{w, 40 * n - 10};
    };
    struct Case {
        const char* in;
        double scale;
    } cases[] = {
        {"one line", 1},
        {"a\nb\nc\nd", 1},               // four lines: fits
        {"a\nb\nc\nd\ne", 150.0 / 190},  // five lines: 190 high
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 600.0 / 700},  // too wide
        {"", 1},
    };
    for (const Case& c : cases) {
        double k = platform370::text::story_scale(c.in, m, 600, 150);
        if (std::fabs(k - c.scale) > 1e-9) t.fail("story_scale(\"%s\") = %g, want %g", c.in, k, c.scale);
    }
}

// E10's room from a label's layout (text::layout_room, english.md 7.15): world rectangles, y down,
// anchors as the nodes hold them (ay from the top).
NATIVE_TEST("platform370/lang-layout-room") {
    using platform370::text::layout_room;
    using platform370::text::NodeRect;
    using platform370::text::RoomBy;
    struct Case {
        const char* what;
        NodeRect self;
        bool has_parent;
        NodeRect parent;
        std::vector<NodeRect> siblings;
        double k;
        RoomBy by;
    } cases[] = {
        // a header title (left-anchored at 47) and its description (left-anchored at 330, anchored
        // at its top): the title ends before the description
        {"title", {47, 152, 0, 0.5, 340, 30, true}, false, {}, {{330, 143, 0, 0, 360, 18, true}}, (330 - 47 - 6) / 340.0, RoomBy::sibling},
        // the description is not bounded by the title (it grows away from it)
        {"description", {330, 143, 0, 0, 360, 18, true}, false, {}, {{47, 152, 0, 0.5, 340, 30, true}}, 1, RoomBy::none},
        // a sibling hanging below the label's row (anchored at its top, under the label)
        {"below", {47, 152, 0, 0.5, 340, 30, true}, false, {}, {{330, 160, 0, 0, 360, 18, true}}, 1, RoomBy::none},
        // a centred button text and the icon on its left; the button is its parent
        {"button", {380, 100, 0.5, 0.5, 330, 30, true}, true, {360, 100, 0.5, 0.5, 500, 90, false}, {{200, 100, 0.5, 0.5, 64, 64, false}},
         (380 - 232 - 6) / 165.0, RoomBy::sibling},
        // two table cells that face each other (left- and right-anchored) share the gap: one scale
        {"cell left", {184, 50, 0, 0.5, 78, 24, true}, false, {}, {{425, 50, 1, 0.5, 193, 24, true}}, (425 - 184 - 6) / 271.0, RoomBy::sibling},
        {"cell right", {425, 50, 1, 0.5, 193, 24, true}, false, {}, {{184, 50, 0, 0.5, 78, 24, true}}, (425 - 184 - 6) / 271.0, RoomBy::sibling},
        // a plate behind the label (it spans the label's anchor) is not in the way
        {"plate", {22, 12, 0, 0.5, 300, 24, true}, false, {}, {{140, 12, 0.5, 0.5, 280, 24, false}}, 1, RoomBy::none},
        // a sibling on another row is not in the way
        {"row", {22, 12, 0, 0.5, 300, 24, true}, false, {}, {{100, 60, 0.5, 0.5, 45, 45, false}}, 1, RoomBy::none},
        // a label wider than the icon it is centred on: its parent's box
        {"icon", {100, 50, 0.5, 0.5, 120, 24, true}, true, {100, 50, 0.5, 0.5, 96, 96, false}, {}, (148 - 6 - 100) / 60.0, RoomBy::parent},
        // a parent that doesn't hold the label's anchor is not its frame
        {"outside", {300, 50, 0, 0.5, 120, 24, true}, true, {100, 50, 0.5, 0.5, 96, 96, false}, {}, 1, RoomBy::none},
        // a sibling that would need less than kMinSiblingScale overlaps by design
        {"by design", {22, 12, 0, 0.5, 300, 24, true}, false, {}, {{60, 12, 0, 0.5, 40, 24, false}}, 1, RoomBy::none},
        // the nearer of two bounds wins
        {"nearest", {22, 12, 0, 0.5, 300, 24, true}, true, {150, 12, 0.5, 0.5, 300, 24, false}, {{280, 12, 0, 0.5, 30, 24, false}},
         (280 - 22 - 6) / 300.0, RoomBy::sibling},
    };
    for (const Case& c : cases) {
        platform370::text::LayoutRoom r = layout_room(c.self, c.has_parent ? &c.parent : nullptr, c.siblings);
        if (std::fabs(r.k - c.k) > 1e-9 || r.by != c.by) t.fail("layout_room(%s) = %g by %d, want %g by %d", c.what, r.k, (int)r.by, c.k, (int)c.by);
    }
    // the free band: a list row (parent, y 820..910) with its name above the description; a plate
    // behind the description doesn't end it
    NodeRect desc{130, 886, 0, 0.5, 700, 21, true}, row{360, 865, 0.5, 0.5, 622, 90, false};
    platform370::text::LayoutRoom r = layout_room(desc, &row, {{130, 860, 0, 0.5, 300, 26, true}, {360, 880, 0.5, 0.5, 600, 60, false}});
    if (r.by != RoomBy::parent || r.frame_top != 873 || r.frame_bottom != 910)
        t.fail("layout_room(row) band %g..%g by %d, want 873..910 by parent", r.frame_top, r.frame_bottom, (int)r.by);
}

// --lang en on the booted client: the hooked CCocosLabel::SetText on a stand-in label (only its
// text, +0x230, and its flags, +0xcc, are written) with the client's real StringDB. The selftest
// boots on the APK's built-in master, which has no port_en_* rows, so every literal keeps its
// Japanese (the fallback a server without --english gives), and other texts pass unchanged; booted
// with --data on a phone whose downloaded master has the rows, the literals are replaced. With --lang ja: nothing to do (platform370/lang checks that nothing is hooked).
NATIVE_TEST("platform370/lang-live") {
    if (platform370::language() != "en") return;
    std::string v;
    if (!platform370::text::master_text("sys_close", &v) || v.empty()) t.fail("StringDB sys_close not found");
    fprintf(stderr, "  platform370/lang-live: StringDB sys_close = %s\n", v.c_str());
    // A phone whose master has the port_en_* rows (a download from a server with --english; the
    // selftest-live session at home): the literals are replaced (english_for over the real StringDB).
    bool rows = platform370::text::master_text("port_en_close", &v);
    if (rows) fprintf(stderr, "  platform370/lang-live: the master has port_en_* rows: 閉じる -> %s\n", v.c_str());
    const char* set_text =
        "_ZN9Framework5Cocos11CCocosLabel7SetTextERKNSt6__ndk112basic_stringIcNS2_11char_traitsIcEENS_13CSTLAllocatorIcNS_"
        "22CSTLStringAllocatorInfEEEEE";
    for (const char* in : {"閉じる", "LV12習得", "Close", "フィルター"}) {
        alignas(16) static u8 label[0x300];
        std::memset(label, 0, sizeof label);
        alignas(8) u8 str[24] = {};
        size_t n = std::strlen(in);
        str[0] = (u8)(n << 1);
        std::memcpy(str + 1, in, n);
        t.call(set_text, {(u64)label, (u64)str});
        const u8* got = label + 0x230;
        std::string out = (got[0] & 1) ? std::string(*(const char* const*)(got + 16), *(const u64*)(got + 8))
                                       : std::string((const char*)got + 1, got[0] >> 1);
        std::string exp = in;
        if (rows) platform370::text::english_for(in, platform370::text::master_text, &exp);
        if (rows && exp == in && std::string(in) != "Close") t.fail("no English for \"%s\" on a master with the rows", in);
        if (out != exp) t.fail("SetText(\"%s\") set \"%s\", want \"%s\"", in, out.c_str(), exp.c_str());
    }
}

}  // namespace
}  // namespace soa
