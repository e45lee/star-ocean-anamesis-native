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
// platform370/lang-strings and platform370/lang-wrap: the E10 rules as functions (the hard-coded
// strings' table against data/english/client-strings.tsv; the wrap), independent of --lang.
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
    // --lang en: CLanguage::CLanguage, CCocosLabel::SetText (hard-coded strings), CCocosLabel::DrawSelf (wrap)
    if (platform370::language_hooks().size() != (en ? 3u : 0u)) t.fail("language_hooks() has %zu entries", platform370::language_hooks().size());

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

// The wrap rule (platform370 text_370.cpp) with a fixed-advance measure: 10 per byte.
NATIVE_TEST("platform370/lang-wrap") {
    auto m = [](std::string_view s) { return 10.f * (float)s.size(); };
    struct Case {
        const char* in;
        float budget;
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
        std::string out = platform370::text::wrap(c.in, c.budget, m);
        if (out != c.want) t.fail("wrap(\"%s\", %g) = \"%s\", want \"%s\"", c.in, c.budget, out.c_str(), c.want);
    }
}

// The home speech box's fit (E12, text_370.cpp fit_box) with a fixed-advance measure: 10 per byte,
// lines 30 apart and 24 high (h = 30 n - 6).
NATIVE_TEST("platform370/lang-fit-box") {
    auto m = [](std::string_view s) {
        float w = 0, n = 1, cur = 0;
        for (char ch : s) {
            if (ch == '\n') n++, cur = 0;
            else w = std::max(w, cur += 10);
        }
        return platform370::text::Extent{w, 30 * n - 6};
    };
    struct Case {
        const char* in;
        const char* want;
        float scale;
    } cases[] = {
        {"aaa bbb", "aaa bbb", 1},                                // fits as it is
        {"aaa\nbbb", "aaa bbb", 1},                               // the line break collapsed
        {"aaaa bbbb cccc", "aaaa bbbb\ncccc", 1},                  // two lines at full size
        {"aaa  \n  bbb", "aaa bbb", 1},                           // the white space around a break goes
        {"aaaa bbbb cccc dddd eeee", "aaaa bbbb cccc\ndddd eeee", 100.f / 140},  // 3 lines at full size: 2 wider ones, shrunk
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 100.f / 510},  // one word: shrunk to the width
        {"", "", 1},
    };
    for (const Case& c : cases) {
        platform370::text::BoxFit f = platform370::text::fit_box(c.in, 100, 54, m);
        if (f.text != c.want || std::fabs(f.scale - c.scale) > 1e-4f)
            t.fail("fit_box(\"%s\") = \"%s\" at %g, want \"%s\" at %g", c.in, f.text.c_str(), f.scale, c.want, c.scale);
        platform370::text::Extent e = m(f.text);
        if (e.w * f.scale > 100.01f || e.h * f.scale > 54.01f) t.fail("fit_box(\"%s\") leaves the box", c.in);
    }
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
